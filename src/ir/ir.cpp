#include "ir/ir.hpp"
#include <deque>
#include <iterator>
#include <memory>
#include <iostream>
#include <stdlib.h>

namespace ir {
// 函数类型类相关函数实现
FunctionType::FunctionType(std::shared_ptr<Type> result, std::vector<std::shared_ptr<Type> > params) : Type(Type::FunctionTID, false) {
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
    {Instruction::OpID::Not, "~"},
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

std::string Instruction::op_to_string(OpID id) {
    if (op2str_.find(id) == op2str_.end()) {
        return "";
    }
    return op2str_[id];
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

void Function::add_basic_block(std::shared_ptr<BasicBlock> bb) {
    basic_blocks_.emplace_back(bb);
}

std::string BasicBlock::print() {
    std::string s;
    for (auto &inst : instructions_) {
        s += inst->print() + "\t";
    }
    return s;
}


std::shared_ptr<ir::Literal> ir::Literal::make_literal(bool val) {
    std::shared_ptr<Type> type;
    type = std::make_shared<BooleanType>(false);
    return std::make_shared<ir::LiteralBool>(type, val);
}

// 创建一个实数常量
std::shared_ptr<ir::Literal> ir::Literal::make_literal(double val) {
    std::string s = std::to_string(val);
    std::shared_ptr<Type> type;
    type = std::make_shared<RealType>(kDefaultRealBitWidth, false);
    return std::make_shared<LiteralDouble>(type, val, s);
}

// 创建一个整数常量
std::shared_ptr<ir::Literal> ir::Literal::make_literal(long val) {
    std::shared_ptr<Type> type;
    type = std::make_shared<IntegerType>(kDefaultIntegerBitWidth, false);
    return std::make_shared<LiteralInt>(type, val);
}


} // namespace ir
