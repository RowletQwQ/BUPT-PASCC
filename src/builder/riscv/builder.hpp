
#pragma once
#include "builder/builder.hpp"
#include "builder/riscv/instruction.hpp"
#include "instruction.hpp"
#include "ir/visitor.hpp"
#include "operand.hpp"
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

namespace builder {
namespace riscv {

class BasicBlock {
public:
    std::shared_ptr<Label> label_;
    std::vector<std::shared_ptr<Instruction>> insts_; // 基本块中的指令
};

class Function {
public:
    std::shared_ptr<Label> label_;
    std::vector<std::shared_ptr<Instruction>> before_insts_; // 函数开始前的指令
    std::vector<std::shared_ptr<BasicBlock>> bbs_; // 函数所属的基本块
    std::vector<std::shared_ptr<Instruction>> after_insts_; // 函数结束后的指令
    std::string print() const;
};
class Module {
public:
    std::vector<std::shared_ptr<GlobalConst>> consts_; // 常量和已经定义的全局变量
    std::vector<std::shared_ptr<GlobalId>> global_vars_; // 未初始化的全局变量
    std::vector<std::shared_ptr<Function>> funcs_; // 函数
    void add_const(std::shared_ptr<GlobalConst> global);
    void add_func(std::shared_ptr<Function> func);
    void add_global(std::shared_ptr<GlobalId> global);
private:
    std::mutex const_mutex_;
    std::mutex func_mutex_;
    std::mutex global_mutex_;
};

class Scope {
public:
    enum PointerType {
        NotPointer,
        Int8,
        Int16,
        Int32,
        Int64,
        Float,
        Double,
    };
    Scope();
    // 进入一个新的作用域
    void enter();
    std::shared_ptr<Instruction> alloc_stack(int size);
    std::shared_ptr<Instruction> dealloc_stack(int size);
    // 离开当前作用域
    std::shared_ptr<Instruction> leave();
    // 加入一个符号
    void push(const std::string &name, std::shared_ptr<Operand> val);
    // 查找一个符号
    std::shared_ptr<Operand> find(const std::string &name);

    void touch_reg(int reg) {   
        reg_used_[reg] = true;
        reg_access_timestamp_[reg] = ++timestamp_;
    }

    bool is_reg_allocated(int reg) const {
        return reg_used_[reg];
    }

    void add_pointer(const std::string &name, PointerType type) {
        pointers_.back()[name] = type;
    }

private:
    // 作用域栈
    std::vector<bool> reg_used_;
    int timestamp_;
    std::vector<int> reg_access_timestamp_;
    std::vector<int> stack_size_;
    std::vector<std::map<std::string,PointerType> > pointers_;
    std::vector<std::map<std::string, std::shared_ptr<Operand>>> symbols_;
    std::map<std::string, int> global_symbols_;
};

class RiscvBuilder :public ir::IrVisitor,public Builder {
public:
    void visit(const ir::BinaryInst* inst) override;
    void visit(const ir::UnaryInst* inst) override;
    void visit(const ir::CompareInst* inst) override;
    void visit(const ir::StoreInst* inst) override;
    void visit(const ir::LoadInst* inst) override;
    void visit(const ir::ReadInst* inst) override;
    void visit(const ir::WriteInst* inst) override;
    void visit(const ir::CallInst* inst) override;
    void visit(const ir::ReturnInst* inst) override;
    void visit(const ir::BreakInst* inst) override;
    void visit(const ir::ContinueInst* inst) override;
    void visit(const ir::ContinueIncInst* inst) override;
    void visit(const ir::BranchInst* inst) override;
    void visit(const ir::BasicBlock* bb) override;
    void visit(const ir::Function* func) override;
    void visit(const ir::GlobalIdentifier* global) override;
    void visit(const ir::LiteralDouble* literal) override;
    void visit(const ir::LiteralInt* literal) override;
    void visit(const ir::LiteralString* literal) override;
    void visit(const ir::LiteralChar* literal) override;
    void visit(const ir::LiteralBool* literal) override;
    void visit(const ir::LiteralArray* literal) override;
    void visit(const ir::LiteralFloat* literal) override;
    void build(ir::Module &program) override;
    void output(std::ofstream &out) override;
    
private:
    std::unique_ptr<Module> modules_;
};

} // namespace riscv
} // namespace builder