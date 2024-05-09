
#pragma once
#include "builder/builder.hpp"
#include "ir/visitor.hpp"

namespace builder {
namespace riscv {

class Module {

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
    void build(ir::Module &program) override;
    void output(std::ofstream &out) override;
};

} // namespace riscv
} // namespace builder