#include "common/log/log.hpp"
#include "ir/ir_gen.hpp"
#include <iostream>
#include <ostream>

int main(){
    common::g_log = new common::Log(common::LOG_LEVEL::WARN);
    // LOG_DEBUG("Debug message");
    // LOG_DEBUG("Debug message")
    // LOG_INFO("Info message");
    // LOG_WARN("Warn message");
    // LOG_ERROR("Error message");
    // LOG_FATAL("Fatal message");
    delete common::g_log;
    return 0;
}