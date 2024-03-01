#include "ir/ir.hpp"

namespace ir {

GlobalIdentifier::GlobalIdentifier(const std::string &name, Module *m,
                                   Type *type, bool is_const, Literal *init_val)
    : Value(m->get_pointer_type(type), name), is_const_(is_const),
      init_val_(init_val) {
  m->add_global_identifier(this);
}

Function::Function(FunctionType *type, const std::string &name, Module *m) : Value(type, name), parent_(m), seq_cnt_(0) {
        m->add_function(this);
        size_t num_args = type->args_.size();
        use_ret_cnt = 0;
        for (size_t i = 0; i < num_args; i++) {
            args_.push_back(new Argument(type->args_[i], "", this, i));
        }
    }
} // namespace ir
