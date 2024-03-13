#include "common/log/log.hpp"
#include <cstdarg>
#include <deque>
#include <iostream>
#include <mutex>
#include <ostream>
#include <queue>
#include <string>
#include <vector>

namespace common {


Log *g_log = nullptr;

enum LOG_COLOR {
	RED = 31,
	GREEN = 32,
	BLUE = 34,
	GRAY = 90,
	YELLOW = 93,
};

Log::Log(const LogLevel level)
    : log_level_(level)
{
    log_done = false;
    prefix_map_[DEBUG] = "\033[" + std::to_string(GRAY) + "mDEBUG\033[0m";
    prefix_map_[INFO] = "\033[" + std::to_string(GREEN) + "mINFO\033[0m";
    prefix_map_[WARN] = "\033[" + std::to_string(YELLOW) + "mWARN\033[0m";
    prefix_map_[ERROR] = "\033[" + std::to_string(RED) + "mERROR\033[0m";
    prefix_map_[FATAL] = "\033[" + std::to_string(RED) + "mFATAL\033[0m";
    log_thread_ = std::thread(&Log::log_thread, this);
}

Log::~Log()
{
    {
        std::lock_guard<std::mutex> lock(log_mutex);
        log_done = true;
    }
    log_cv.notify_all();
    if (log_thread_.joinable()) {
        log_thread_.join();
    }
}

template <class T>
Log &Log::operator<<(T msg)
{
    std::lock_guard<std::mutex> lock(log_mutex);
    std::cout << msg;
    return *this;
}

void Log::output(const common::LogLevel level, const char *prefix, const char *f, ...)
{
    if (level < log_level_)
    {
        return;
    }
    char buf[MAX_LOG_HEADER_SIZE << 2] = {0};
    va_list args;
    va_start(args, f);
    vsnprintf(buf, MAX_LOG_HEADER_SIZE, f, args);
    va_end(args);

    std::lock_guard<std::mutex> lock(log_mutex);
    log_queue.push({level, prefix, buf});
    log_cv.notify_one();
}

void Log::log_thread()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(log_mutex);
        log_cv.wait(lock, [this]{ return !log_queue.empty() || log_done; });

        if (log_queue.empty())
        {
            return;
        }

        LogMessage log = log_queue.front();
        log_queue.pop();
        lock.unlock();

        std::cout << prefix_map_[log.level] << " " << log.prefix << " " << log.message << "\n";

        if (log.level == FATAL)
        {
            exit(1);
        }
    }
}


}; // namespace common