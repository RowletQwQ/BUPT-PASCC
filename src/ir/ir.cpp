#include "ir/ir.hpp"
#include <memory>

namespace ir {

FunctionType::FunctionType(std::shared_ptr<Type> result, std::vector<std::shared_ptr<Type> > params) : Type(Type::FunctionTID) {
        result_ = result; // 返回值类型
        for (std::shared_ptr<Type> p : params) {
            args_.push_back(p); // 参数列表类型
        }
}


LiteralArray::LiteralArray(std::shared_ptr<ArrayType> ty, const std::vector<std::shared_ptr<Literal> > &val) : Literal(ty) {
        this->const_array.assign(val.begin(), val.end());
}

Instruction::Instruction(std::shared_ptr<Type> ty, OpID id, unsigned num_ops, std::shared_ptr<BasicBlock> parent, bool before)
      : Value(ty, ""), op_id_(id), num_ops_(num_ops), parent_(parent) {
        operands_.resize(num_ops_, nullptr); // 此句不能删去！否则operands_为空时无法用set_operand设置操作数，而只能用push_back设置操作数！
        use_pos_.resize(num_ops_);

        // TODO: 处理 before
    }

GlobalIdentifier::GlobalIdentifier(const char *name, std::shared_ptr<Module> m,
                                   std::shared_ptr<Type> type, bool is_const, std::shared_ptr<Literal> init_val)
    : Value(m->get_pointer_type(type), name), is_const_(is_const),
      init_val_(init_val), parent_(m){}

void GlobalIdentifier::init(){
    parent_.lock()->add_global_identifier(std::static_pointer_cast<GlobalIdentifier>(get_this()));
}

Function::Function(std::shared_ptr<FunctionType> type, const char *name, std::shared_ptr<Module> m) 
        : Value(type, name), parent_(m), seq_cnt_(0), func_type_(type) {}

void Function::init(){
    size_t num_args = func_type_.lock()->args_.size();
    use_ret_cnt = 0;
    for (size_t i = 0; i < num_args; i++) {
        args_.push_back(std::make_shared<Argument>(func_type_.lock()->args_[i], "", std::static_pointer_cast<Function>(get_this()), i));
    }
    parent_.lock()->add_function(std::static_pointer_cast<Function>(get_this()));
}

} // namespace ir
