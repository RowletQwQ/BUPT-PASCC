#pragma once

#include "ir/ir.hpp"
#include "ast/visitor.hpp"

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

    // 离开一个作用域
    void leave();

    // 检测是否在全局作用域
    bool is_global();

    // 加入一个符号
    bool push(const std::string &name, Value *value);

    // 查找一个符号
    Value *find(const std::string &name);

private:
    // 栈式存储分配
    // 是一个 vector, 每个元素相当于作用域 map, 作用域 map 中存储了当前作用域的符号
    std::vector<std::map<std::string, Value *>> symbols_;
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
    void visit(ReadFuncStmt &stmt) override;
    void visit(WriteFuncStmt &stmt) override;
    void visit(ProgramHeadStmt &stmt) override;
    void visit(ProgramBodyStmt &stmt) override;
    void visit(ProgramStmt &stmt) override;

    Module get_ir() { return module_; }

    Scope scope_; // 作用域
    Module module_; // 中间代码
    
    IRGenerator() {
        // TODO: 把 Pascal 的内建函数加入到中间代码中, 如 read, write 等


        // 进入全局作用域
        scope_.enter();
        // scope_.push("read", .....);
        // scope_.push("write", .....);
    }
};



} // namespace ir