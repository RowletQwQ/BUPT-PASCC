#pragma once
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
class GlobalIdentifier;
class LiteralDouble;
class LiteralInt;
class LiteralString;
class LiteralChar;
class LiteralBool;
class LiteralArray;
class LiteralFloat;

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
    virtual void visit(const BasicBlock* bb) = 0;
    virtual void visit(const Function* func) = 0;
    virtual void visit(const GlobalIdentifier* global) = 0;
    virtual void visit(const LiteralDouble* literal) = 0;
    virtual void visit(const LiteralInt* literal) = 0;
    virtual void visit(const LiteralString* literal) = 0;
    virtual void visit(const LiteralChar* literal) = 0;
    virtual void visit(const LiteralBool* literal) = 0;
    virtual void visit(const LiteralArray* literal) = 0;
    virtual void visit(const LiteralFloat* literal) = 0;
};

} // namespace ir