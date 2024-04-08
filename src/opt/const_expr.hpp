#pragma once
#include "opt.hpp"

namespace opt {
class ConstExprOpt: public Optimize {
public:
    ConstExprOpt() = default;
    virtual ~ConstExprOpt() = default;
    void optimize(ir::Module &program) override;


}; // class ConstExprOpt

} // namespace opt