#include "ir/ir.hpp"
#include <memory>
#include <iostream>

namespace ir {
// 函数类型类相关函数实现
FunctionType::FunctionType(std::shared_ptr<Type> result, std::vector<std::shared_ptr<Type> > params) : Type(Type::FunctionTID) {
        result_ = result; // 返回值类型
        for (std::shared_ptr<Type> p : params) {
            args_.push_back(p); // 参数列表类型
        }
}

// 指令类相关函数实现
std::map<Instruction::OpID, std::string> Instruction::op2str_ = {
    {Instruction::OpID::Call, "call"},
    {Instruction::OpID::Ret, "ret"},
    {Instruction::OpID::Br, "br"},
    {Instruction::OpID::Add, "+"},
    {Instruction::OpID::Sub, "-"},
    {Instruction::OpID::Mul, "*"},
    {Instruction::OpID::Div, "/"},
    {Instruction::OpID::Mod, "%"},
    {Instruction::OpID::And, "&&"},
    {Instruction::OpID::Or, "||"},
    {Instruction::OpID::OrElse, "OrElse"},
    {Instruction::OpID::AndThen, "AndThen"},
    {Instruction::OpID::Not, "!"},
    {Instruction::OpID::BitReverse, "~"},
    {Instruction::OpID::LogicalNot, "LogicalNot"},
    {Instruction::OpID::Bracket, "()"},
    {Instruction::OpID::Null, ""},
    {Instruction::OpID::Inc, "++"},
    {Instruction::OpID::Eq, "=="},
    {Instruction::OpID::Ne, "!="},
    {Instruction::OpID::Gt, ">"},
    {Instruction::OpID::Ge, ">="},
    {Instruction::OpID::Lt, "<"},
    {Instruction::OpID::Le, "<="},
    {Instruction::OpID::In, "In"},
    {Instruction::OpID::Assign, "="},
    {Instruction::OpID::Visit, "Visit"},
    {Instruction::OpID::Read, "Read"},
    {Instruction::OpID::Write, "Write"}
};

Instruction::Instruction(std::shared_ptr<Type> ty, OpID id, unsigned num_ops, std::weak_ptr<BasicBlock> bb, bool before)
    : Value(ty, ValueID::Instruction, ""), op_id_(id), num_ops_(num_ops), bb_(bb) {
        init();        
    }
Instruction::Instruction(const std::string name, std::shared_ptr<Type> ty, OpID id, unsigned num_ops, std::weak_ptr<BasicBlock> bb, bool before) 
    : Value(ty, ValueID::Instruction, name), op_id_(id), num_ops_(num_ops), bb_(bb) {
        init();
}
void Instruction::init() {
    operands_.resize(num_ops_, std::weak_ptr<Value>()); // 此句不能删去！否则operands_为空时无法用set_operand设置操作数，而只能用push_back设置操作数！
    use_pos_.resize(num_ops_);
}

// 全局标识符类相关函数实现
GlobalIdentifier::GlobalIdentifier(std::shared_ptr<Type> type, const std::string name, bool is_const, std::shared_ptr<Literal> init_val)
    : Value(type, ValueID::GlobalIdentifier, name), is_const_(is_const), init_val_(init_val) {
    }

// 局部标识符类相关函数实现
LocalIdentifier::LocalIdentifier(std::shared_ptr<Type> type, const std::string name,bool is_const, std::shared_ptr<Literal> init_val)
    : Value(type, ValueID::LocalIdentifier, name), is_const_(is_const), init_val_(init_val) {}

// 函数类相关函数实现
Function::Function(std::shared_ptr<FunctionType> type, const std::string name, std::vector<std::string> arg_name) 
    : Value(type, ValueID::Function, name), func_type_(type) {
        size_t num_args = func_type_.lock()->args_.size();
        for (size_t i = 0; i < num_args; i++) {
            args_.push_back(std::make_shared<Argument>(func_type_.lock()->args_[i], arg_name[i], i));
        }
    }
bool CompareInst::can_be_compared(const Type *t1, const Type *t2) {
    if(t1->is_number() && t2->is_number()) {
        return true;
    }
    return false;

}

bool BinaryInst::can_compute(const Type *t1, const Type *t2) {
    if(t1->get_tid() == t2->get_tid()) {
        return true;
    }
    if(t1->is_number() && t2->is_number()) {
        return true;
    }
    return false;
}

} // namespace ir
