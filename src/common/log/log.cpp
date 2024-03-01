#include "common/log/log.hpp"
#include <cstdarg>
#include <iostream>
#include <ostream>
#include <string>

namespace common {

Log *g_log = nullptr;

Log::Log(const LogLevel level)
    : log_level_(level)
{
    pthread_mutex_init(&mutex_, NULL);
    prefix_map_[DEBUG] = "DEBUG";
    prefix_map_[INFO] = "INFO";
    prefix_map_[WARN] = "WARN";
    prefix_map_[ERROR] = "ERROR";
    prefix_map_[FATAL] = "FATAL";
}

Log::~Log()
{
    pthread_mutex_destroy(&mutex_);
}

template <class T>
Log &Log::operator<<(T msg)
{
    pthread_mutex_lock(&mutex_);
    std::cout << msg;
    pthread_mutex_unlock(&mutex_);
    return *this;
}

void Log::output(const common::LogLevel level, const char *prefix, const char *f, ...)
{
    if (level < log_level_)
    {
        return;
    }
    pthread_mutex_lock(&mutex_);
    char buf[MAX_LOG_HEADER_SIZE << 2] = {0};
    va_list args;
    va_start(args, f);
    vsnprintf(buf, MAX_LOG_HEADER_SIZE, f, args);
    va_end(args);
    std::cout << prefix_map_[level] << " " <<prefix << " " << buf << "\n";
    pthread_mutex_unlock(&mutex_);
    if (level == FATAL)
    {
        exit(1);
    }
}

}; // namespace common