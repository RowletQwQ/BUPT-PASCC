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



    // ----------------- IrGenerator -----------------
    void visit(ExprStmt &stmt) {
        
    }
    void visit(RelExprStmt &stmt) {
        
    }
    void visit(AddExprStmt &stmt) {
        
    }
    void visit(MulExprStmt &stmt) {
        
    }
    void visit(UnaryExprStmt &stmt) {
        
    }
    void visit(PrimaryExprStmt &stmt) {
        
    }
    void visit(ValueStmt &stmt) {
        
    }
    void visit(NumberStmt &stmt) {
        
    }
    void visit(StrStmt &stmt) {
        
    }
    void visit(LValStmt &stmt) {
        
    }
    void visit(FuncCallStmt &stmt) {
        
    }
    void visit(PeriodStmt &stmt) {
        
    }
    void visit(ConstDeclStmt &stmt) {
        
    }
    void visit(VarDeclStmt &stmt) {
        
    }
    void visit(FuncHeadDeclStmt &stmt) {
        
    }
    void visit(FuncBodyDeclStmt &stmt) {
        
    }
    void visit(FuncDeclStmt &stmt) {
        
    }
    void visit(AssignStmt &stmt) {
        
    }
    void visit(IfStmt &stmt) {
        
    }
    void visit(ForStmt &stmt) {
        
    }
    void visit(ReadFuncStmt &stmt) {
        
    }
    void visit(WriteFuncStmt &stmt) {
        
    }
    void visit(ProgramHeadStmt &stmt) {
        
    }
    void visit(ProgramBodyStmt &stmt) {
        
    }
    void visit(ProgramStmt &stmt) {
        
    }
} // namespace ir