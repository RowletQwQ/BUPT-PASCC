#pragma once

#include <string>
namespace ir {
    class Module;
} // namespace ir

namespace opt {

/**
 * @brief 优化器的接口类
 * @details 不同优化器均需要继承自此类
 */
class Optimize {
public:
    Optimize() = default;
    virtual ~Optimize() = default;
    /**
     * @brief 优化中间代码
     * @param program 中间代码
     * @details 接受中间代码，对其进行优化
     */
    virtual void optimize(ir::Module &program) = 0;
    virtual std::string get_name() = 0;
}; // class Optimize

} // namespace opt