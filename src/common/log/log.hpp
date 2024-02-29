

#include <map>
#include <ostream>
#include <sstream>
#include <string>
#include <pthread.h>
#include <sys/time.h>

namespace common 
{

typedef enum {
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL
} LOG_LEVEL;

class Log{
public:
    /**
     * @brief 新建一个log对象
     * @param level log的级别
     */
    Log(const LOG_LEVEL level = LOG_LEVEL::WARN);

    ~Log();

    template <class T>
    Log &operator<<(T msg);

    void output(const LOG_LEVEL level, const char *prefix, const char *f, ...);

private:
    const LOG_LEVEL log_level_;
    pthread_mutex_t mutex_;
    std::map<LOG_LEVEL, std::string> prefix_map_;

}; // class Log


extern Log *g_log;
#define MAX_LOG_HEADER_SIZE 1024
#define LOG_HEAD_SIZE 128

#define LOG_HEAD(prefix, level)                                            \
  if (common::g_log) {                                                     \
    struct timeval tv;                                                     \
    gettimeofday(&tv, NULL);                                               \
    struct tm *p = localtime(&tv.tv_sec);                                  \
    char time_head[LOG_HEAD_SIZE] = {0};                                   \
    if (p) {                                                               \
      int usec = (int)tv.tv_usec;                                          \
      snprintf(time_head, LOG_HEAD_SIZE,                                   \
          "%04d-%02d-%02d %02d:%02d:%02u.%06d",                            \
          p->tm_year + 1900,                                               \
          p->tm_mon + 1,                                                   \
          p->tm_mday,                                                      \
          p->tm_hour,                                                      \
          p->tm_min,                                                       \
          p->tm_sec,                                                       \
          usec);                                                           \
    }                                                                      \
    snprintf(prefix,                                                       \
        sizeof(prefix),                                                    \
        "[%s %s@%s:%u] >> ",                                               \
        time_head,                                                         \
        __FUNCTION__,                                                      \
        __FILE_NAME__,                                                     \
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

#define LOG_DEBUG(fmt, ...) LOG_OUTPUT(common::LOG_LEVEL::DEBUG, fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...) LOG_OUTPUT(common::LOG_LEVEL::INFO, fmt, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...) LOG_OUTPUT(common::LOG_LEVEL::WARN, fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) LOG_OUTPUT(common::LOG_LEVEL::ERROR, fmt, ##__VA_ARGS__)
#define LOG_FATAL(fmt, ...) LOG_OUTPUT(common::LOG_LEVEL::FATAL, fmt, ##__VA_ARGS__)

}; // namespace common