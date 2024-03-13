#pragma once

#include <map>
#include <mutex>
#include <ostream>
#include <queue>
#include <sstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <thread>
#include <condition_variable>


namespace common 
{

typedef enum {
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL
} LogLevel;

struct LogMessage {
    common::LogLevel level;
    std::string prefix;
    std::string message;
};

class Log{
public:
    /**
     * @brief 新建一个log对象
     * @param level log的级别
     */
    Log(const LogLevel level = LogLevel::WARN);

    ~Log();

    template <class T>
    Log &operator<<(T msg);

    /**
     * @brief 输出log
     * @param level log的级别
     * @param prefix log的前缀
     * @param f log的内容
     */
    void output(const LogLevel level, const char *prefix, const char *f, ...);

    void log_thread();

private:
    bool log_done = false;
    const LogLevel log_level_;
    std::queue<LogMessage> log_queue;
    std::mutex log_mutex;
    std::condition_variable log_cv;
    std::map<LogLevel, std::string> prefix_map_;
    std::thread log_thread_;

}; // class Log


extern Log *g_log;
#define MAX_LOG_HEADER_SIZE 1024
#define LOG_HEAD_SIZE 128

#define LOG_HEAD(prefix, level)                                            \
  if (common::g_log) {                                                     \
    auto now = std::chrono::system_clock::now();                            \
    auto now_time_t = std::chrono::system_clock::to_time_t(now);         \
    auto now_tm = std::localtime(&now_time_t);                     \
    auto now_since_epoch = now.time_since_epoch();                        \
    auto now_ms = std::chrono::duration_cast<std::chrono::microseconds>(now_since_epoch).count();\
    std::stringstream ss;                                               \
    ss << std::put_time(now_tm, "%Y-%m-%d %H:%M:%S")                    \
        << '.' << now_ms;                                                \
    std::string time_info = ss.str();                                    \
    char time_head[LOG_HEAD_SIZE] = {0};                                 \
    snprintf(time_head, LOG_HEAD_SIZE,                                   \
          "%s",                                                           \
          ss.str().c_str());                                              \
    snprintf(prefix,                                                       \
      sizeof(prefix),                                                    \
      "[%s %s@%s:%u] >> ",                                               \
      time_head,                                                         \
      __FUNCTION__,                                                      \
      __FILE__,                                                           \
      (int32_t)__LINE__                                                  \
      );                                                                 \
  }                                                                     

#define LOG_OUTPUT(level, fmt, ...)                                         \
  do {                                                                      \
    using namespace common;                                                 \
    if (common::g_log) {                                                            \
      char prefix[MAX_LOG_HEADER_SIZE] = {0};                               \
      LOG_HEAD(prefix, level);                                              \
      g_log->output(level, prefix, fmt, ##__VA_ARGS__);      \
    }                                                                       \
  } while (0)                                                               

#define LOG_DEBUG(fmt, ...) LOG_OUTPUT(common::LogLevel::DEBUG, fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...) LOG_OUTPUT(common::LogLevel::INFO, fmt, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...) LOG_OUTPUT(common::LogLevel::WARN, fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) LOG_OUTPUT(common::LogLevel::ERROR, fmt, ##__VA_ARGS__)
#define LOG_FATAL(fmt, ...) LOG_OUTPUT(common::LogLevel::FATAL, fmt, ##__VA_ARGS__)

}; // namespace common