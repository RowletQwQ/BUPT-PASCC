#pragma once

#include "ir/ir.hpp"
#include "ast/visitor.hpp"
#include "ast/stmt.hpp"

#include <memory>
#include <vector>
#include <map>
#include <string>


namespace ir {

/**
 * @brief 作用域类
 * 
*/
class Scope {
public:
    // 进入一个新的作用域
    void enter();

    // 进入循环作用域
    void enter_loop(std::weak_ptr<BasicBlock> cond,std::weak_ptr<BasicBlock> body_bb, 
        std::weak_ptr<BasicBlock> brk_bb, bool is_while_stmt);

    // 获取循环作用域的循环体
    std::weak_ptr<BasicBlock> get_loop_body();

    // 获取循环作用域的循环跳出
    std::weak_ptr<BasicBlock> get_loop_brk();

    // 获取循环作用域的循环条件
    std::weak_ptr<BasicBlock> get_loop_cond();

    // 检测是否在循环作用域
    bool is_in_loop() { 
        return loop_cond_stack_.size() > 0;
    }

    // 离开循环作用域
    void leave_loop();

    // 离开一个作用域
    void leave();

    // 检测是否在全局作用域
    bool is_global();

    bool is_while_stmt() {
        return is_while_stmt_;
    }

    // 加入一个符号
    void push(const std::string &name, std::shared_ptr<Value> value);

    // 查找一个符号
    std::shared_ptr<Value> find(const std::string &name);

    // 当前作用域的函数
    std::shared_ptr<Function> current_f_ = nullptr;

    // 打印作用域的符号
    void print();
private:
    // 栈式存储分配
    // 是一个 vector, 每个元素相当于作用域 map, 作用域 map 中存储了当前作用域的符号
    std::vector<std::map<std::string, std::shared_ptr<Value>>> symbols_;

    // 循环栈
    std::vector<std::weak_ptr<BasicBlock>> loop_cond_stack_;
    std::vector<std::weak_ptr<BasicBlock>> loop_body_stack_;
    std::vector<std::weak_ptr<BasicBlock>> loop_brk_stack_;
    bool is_while_stmt_ = false;
};


/**
 * @brief 中间代码生成器
 * 继承 StmtVisitor, 生成中间代码
*/
class IRGenerator : public StmtVisitor {
public:
    // 语句访问者
    void visit(ExprStmt &stmt) override;
    void visit(RelExprStmt &stmt) override;
    void visit(AddExprStmt &stmt) override;
    void visit(MulExprStmt &stmt) override;
    void visit(UnaryExprStmt &stmt) override;
    void visit(PrimaryExprStmt &stmt) override;
    void visit(ValueStmt &stmt) override;
    void visit(NumberStmt &stmt) override;
    void visit(StrStmt &stmt) override;
    void visit(LValStmt &stmt) override;
    void visit(FuncCallStmt &stmt) override;
    void visit(PeriodStmt &stmt) override;
    void visit(ConstDeclStmt &stmt) override;
    void visit(VarDeclStmt &stmt) override;
    void visit(FuncHeadDeclStmt &stmt) override;
    void visit(FuncBodyDeclStmt &stmt) override;
    void visit(FuncDeclStmt &stmt) override;
    void visit(AssignStmt &stmt) override;
    void visit(IfStmt &stmt) override;
    void visit(ForStmt &stmt) override;
    void visit(WhileStmt &stmt) override;
    void visit(ReadFuncStmt &stmt) override;
    void visit(WriteFuncStmt &stmt) override;
    void visit(BreakStmt &stmt) override;
    void visit(ContinueStmt &stmt) override;
    void visit(ProgramHeadStmt &stmt) override;
    void visit(ProgramBodyStmt &stmt) override;
    void visit(ProgramStmt &stmt) override;

    Module get_ir() { return module_; }

    Scope scope_; // 作用域
    Module module_; // 中间代码

    void show_result() {
        std::cout << "全局标识符如下:" << std::endl;

        for (const auto &global : module_.global_identifiers_) {
            if (global->is_const_) {
                std::cout << "const " + global->type_->print() << " " << global->name_ << " = " << global->init_val_->print() << std::endl;
            } else {
                std::string s = global->type_->print();
                int ps = s.find(" ");
                if (ps == std::string::npos) {
                    std::cout << global->type_->print() << " " << global->name_ << std::endl;
                } else {
                    std::cout << s.substr(0, ps) << " " << global->name_ << s.substr(ps + 1) << std::endl;
                }
            }
        }
        // 外层遍历函数
        std::cout << "----------------------------------------------------------------------------------------------------------" << "\n";
        for (int i = 0; i < module_.functions_.size(); i++) {
            std::weak_ptr<Function> func = module_.functions_[i];
            std::cout << "第 " << i + 1  << " 个函数信息如下：" << std::endl;
            std::cout << "函数头：" << func.lock()->print() << std::endl;
            std::cout << "局部标识符如下:" << std::endl;
            for (const auto &local : func.lock()->local_identifiers_) {
                if (local->is_const_) {
                    std::cout << local->type_->print() << " " << local->name_ << " = " << local->init_val_->print() << std::endl;
                } else {
                    std::cout << local->type_->print() << " " << local->name_ << std::endl;
                }
            }
            std::cout << "基本块如下:" << std::endl;
            std::cout << "\n";
            for (int j = 0; j < func.lock()->basic_blocks_.size(); j++) {
                std::shared_ptr<BasicBlock> bb = func.lock()->basic_blocks_[j];
                std::cout << "第 " << j + 1 << " 个基本块信息如下：" << std::endl;
                std::cout << "基本块名：" << bb->name_ << std::endl;
                std::cout << "指令列表如下：" << std::endl;
                for (int k = 0; k < bb->instructions_.size(); k++) {
                    std::shared_ptr<Instruction> inst = bb->instructions_[k];
                    std::cout << inst->print() << "\t";
                }
                std::cout << "\n\n";
            }
            
            std::cout << "----------------------------------------------------------------------------------------------------------" << "\n";
        }
    }
    
    IRGenerator() {
        // 进入全局作用域
        scope_.enter();
    }
};



} // namespace ir