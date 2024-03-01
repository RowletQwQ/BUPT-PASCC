#pragma once

namespace ir {

namespace opt {
    class Optimize;
} // namespace optimize


// 值
class Value {
};

/**
 * @brief 程序
 * @details 用于表示一个可执行程序，作为中间代码使用
 */
class Program {
    friend class opt::Optimize;
};

} // namespace ir