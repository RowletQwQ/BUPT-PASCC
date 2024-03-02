#include "ir/ir_gen.hpp"

namespace ir {
    // ----------------- Scope -----------------
    // 进入一个新的作用域
    void Scope::enter() {
        symbols_.push_back(std::map<std::string, Value *>());
    }

    // 离开一个作用域
    void Scope::leave() {
        symbols_.pop_back();
    }

    // 检测是否在全局作用域
    bool Scope::is_global() {
        return symbols_.size() == 1;
    }

    // 加入一个符号
    bool Scope::push(const std::string &name, Value *value) {
        return symbols_.back().insert({name, value}).second;
    }

    // 查找一个符号
    Value *Scope::find(const std::string &name) {
        // 从栈顶开始查找
        for (auto it = symbols_.rbegin(); it != symbols_.rend(); ++it) {
            auto found = it->find(name);
            if (found != it->end()) {
                return found->second;
            }
        }
        return nullptr;
    }



    // ----------------- IRGenerator -----------------
    void IRGenerator::visit(ExprStmt &stmt) {
        
    }
    void IRGenerator::visit(RelExprStmt &stmt) {
        
    }
    void IRGenerator::visit(AddExprStmt &stmt) {
        
    }
    void IRGenerator::visit(MulExprStmt &stmt) {
        
    }
    void IRGenerator::visit(UnaryExprStmt &stmt) {
        
    }
    void IRGenerator::visit(PrimaryExprStmt &stmt) {
        
    }
    void IRGenerator::visit(ValueStmt &stmt) {
        
    }
    void IRGenerator::visit(NumberStmt &stmt) {
        
    }
    void IRGenerator::visit(StrStmt &stmt) {
        
    }
    void IRGenerator::visit(LValStmt &stmt) {
        
    }
    void IRGenerator::visit(FuncCallStmt &stmt) {
        
    }
    void IRGenerator::visit(PeriodStmt &stmt) {
        
    }
    void IRGenerator::visit(ConstDeclStmt &stmt) {
        
    }
    void IRGenerator::visit(VarDeclStmt &stmt) {
        
    }
    void IRGenerator::visit(FuncHeadDeclStmt &stmt) {
        
    }
    void IRGenerator::visit(FuncBodyDeclStmt &stmt) {
        
    }
    void IRGenerator::visit(FuncDeclStmt &stmt) {
        
    }
    void IRGenerator::visit(AssignStmt &stmt) {
        
    }
    void IRGenerator::visit(IfStmt &stmt) {
        
    }
    void IRGenerator::visit(ForStmt &stmt) {
        
    }
    void IRGenerator::visit(ReadFuncStmt &stmt) {
        
    }
    void IRGenerator::visit(WriteFuncStmt &stmt) {
        
    }
    void IRGenerator::visit(ProgramHeadStmt &stmt) {
        
    }
    void IRGenerator::visit(ProgramBodyStmt &stmt) {
        
    }
    void IRGenerator::visit(ProgramStmt &stmt) {
        
    }
} // namespace ir