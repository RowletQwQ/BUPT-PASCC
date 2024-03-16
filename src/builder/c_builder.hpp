#pragma once

#include "builder/builder.hpp"

namespace builder {

class CBuilder : public Builder {
public:
    void build(ir::Module &program) override;
    void output(std::ofstream &out) override;
private:
    std::string code_;
};


} // namespace builder
