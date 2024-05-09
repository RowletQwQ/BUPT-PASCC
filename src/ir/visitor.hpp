#pragma once
#include "ir/ir.hpp"
namespace ir {

class BinaryInst;
class UnaryInst;
class CompareInst;
class StoreInst;
class LoadInst;
class ReadInst;
class WriteInst;
class CallInst;
class ReturnInst;
class BreakInst;
class ContinueInst;
class ContinueIncInst;
class BranchInst;
class Module;
class BasicBlock;
class Function;

class IrVisitor {
public:
    virtual void visit(const BinaryInst* inst) = 0;
    virtual void visit(const UnaryInst* inst) = 0;
    virtual void visit(const CompareInst* inst) = 0;
    virtual void visit(const StoreInst* inst) = 0;
    virtual void visit(const LoadInst* inst) = 0;
    virtual void visit(const ReadInst* inst) = 0;
    virtual void visit(const WriteInst* inst) = 0;
    virtual void visit(const CallInst* inst) = 0;
    virtual void visit(const ReturnInst* inst) = 0;
    virtual void visit(const BreakInst* inst) = 0;
    virtual void visit(const ContinueInst* inst) = 0;
    virtual void visit(const ContinueIncInst* inst) = 0;
    virtual void visit(const BranchInst* inst) = 0;
    virtual void visit(const Module* module) = 0;
    virtual void visit(const BasicBlock* bb) = 0;
    virtual void visit(const Function* func) = 0;
};

} // namespace ir