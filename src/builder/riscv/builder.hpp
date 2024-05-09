
#pragma once
#include "builder/builder.hpp"
#include "builder/riscv/instruction.hpp"
#include "ir/visitor.hpp"
#include <memory>
#include <mutex>
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
    std::vector<std::shared_ptr<BasicBlock>> bbs_; // 函数所属的基本块
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
    void visit(const ir::Module* module) override;
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