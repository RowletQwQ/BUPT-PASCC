#include "ir/ir.hpp"
#include <memory>

namespace ir {
// 函数类型类相关函数实现
FunctionType::FunctionType(std::shared_ptr<Type> result, std::vector<std::shared_ptr<Type> > params) : Type(Type::FunctionTID) {
        result_ = result; // 返回值类型
        for (std::shared_ptr<Type> p : params) {
            args_.push_back(p); // 参数列表类型
        }
}

// 指令类相关函数实现
Instruction::Instruction(std::shared_ptr<Type> ty, OpID id, unsigned num_ops, std::shared_ptr<BasicBlock> parent, bool before)
    : Value(ty, ""), op_id_(id), num_ops_(num_ops), parent_(parent) {
        init();        
    }
Instruction::Instruction(const std::string name, std::shared_ptr<Type> ty, OpID id, unsigned num_ops, std::shared_ptr<BasicBlock> parent, bool before) 
    : Value(ty, name), op_id_(id), num_ops_(num_ops), parent_(parent) {
        init();
}
void Instruction::init() {
    operands_.resize(num_ops_, nullptr); // 此句不能删去！否则operands_为空时无法用set_operand设置操作数，而只能用push_back设置操作数！
    use_pos_.resize(num_ops_);
    parent_.lock()->add_instruction(std::static_pointer_cast<Instruction>(get_this()));

}

// 全局标识符类相关函数实现
GlobalIdentifier::GlobalIdentifier(std::shared_ptr<Type> type, const std::string name, std::shared_ptr<Module> m, bool is_const, std::shared_ptr<Literal> init_val)
    : Value(type, name), is_const_(is_const), init_val_(init_val), parent_(m) {
        init();
    }
void GlobalIdentifier::init(){
    parent_.lock()->add_global_identifier(std::static_pointer_cast<GlobalIdentifier>(get_this()));
}

// 局部标识符类相关函数实现
LocalIdentifier::LocalIdentifier(std::shared_ptr<Type> type, const std::string name, std::shared_ptr<Function> f, bool is_const, std::shared_ptr<Literal> init_val)
    : Value(type, name), is_const_(is_const), init_val_(init_val), parent_(f) {
        init();
    }
void LocalIdentifier::init() {
    parent_.lock()->add_local_identifier(std::static_pointer_cast<LocalIdentifier>(get_this()));
}

// 函数类相关函数实现
Function::Function(std::shared_ptr<FunctionType> type, const std::string name, std::shared_ptr<Module> m) 
    : Value(type, name), parent_(m), func_type_(type) {
        init();
    }

void Function::init() {
    size_t num_args = func_type_.lock()->args_.size();
    for (size_t i = 0; i < num_args; i++) {
        args_.push_back(std::make_shared<Argument>(func_type_.lock()->args_[i], "", std::static_pointer_cast<Function>(get_this()), i));
    }
    parent_.lock()->add_function(std::static_pointer_cast<Function>(get_this()));
}

} // namespace ir
