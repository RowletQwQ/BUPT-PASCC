
#pragma once

#include <fstream>
namespace ir {
    class Module;
} // namespace ir

namespace builder {

// Builder的接口类,不同目标代码的生成均需要继承自此类
class Builder {
public:
    Builder() = default;
    virtual ~Builder() = default;
    /**
     * @brief 构建目标代码
     * @param program 中间代码
     * @details 接受中间代码，生成目标代码，并保存在类内部
     */
    virtual void build(ir::Module &program) = 0;

    /**
     * @brief 输出目标代码
     * @details 输出目标代码到文件输出流
     */
    virtual void output(std::ofstream &out) = 0;

}; // class Builder

} // namespace builder
