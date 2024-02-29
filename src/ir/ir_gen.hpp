#pragma once

#include "ir.hpp"
#include <vector>
#include <map>
#include <string>

namespace ir {
// 作用域
class Scope {
public:
    // 进入一个新的作用域
    void enter();

    // 离开一个作用域
    void leave();

    // 检测是否在全局作用域
    bool is_global();

    // 加入一个符号
    bool push(const std::string &name, Value *value);

    // 查找一个符号
    Value *find(const std::string &name);

private:
    // 栈式存储分配
    // 是一个 vector, 每个元素相当于作用域 map, 作用域 map 中存储了当前作用域的符号
    std::vector<std::map<std::string, Value *>> symbols_;
};
} // namespace ir