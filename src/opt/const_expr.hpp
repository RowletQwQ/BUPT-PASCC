#pragma once
#include "opt.hpp"
#include <string>

namespace opt {
class ConstExprOpt: public Optimize {
public:
    ConstExprOpt() = default;
    virtual ~ConstExprOpt() = default;
    void optimize(ir::Module &program) override;
    std::string get_name() override { return "ConstExprOpt"; }
private:
}; // class ConstExprOpt

} // namespace opt