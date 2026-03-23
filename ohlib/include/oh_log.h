#ifndef OH_LOG_H
#define OH_LOG_H
#include <stdio.h>

namespace ohkit{

enum class LogLevel{
    OH_ERROR = 0,
    OH_WARN,
    OH_INFO,
    OH_DEBUG
};

class Log{
private:
    LogLevel _level = LogLevel::OH_DEBUG;
public:
    static Log& instance();
    void setLevel(LogLevel level){_level = level;};
    LogLevel level() const {return _level;}

    void info(const char* fmt, ...);
    void error(const char* fmt, ...);
    void debug(const char* fmt, ...);
    void warn(const char* fmt, ...);

private:
    Log() = default;
    ~Log() = default;
    Log(const Log&) = delete;
    Log& operator=(const Log&) = delete;
};

}

#endif