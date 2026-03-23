#include "oh_log.h"
#include <stdarg.h>

namespace ohkit{

Log& Log::instance(){
    static Log instance;
    return instance;
}

void Log::info(const char* fmt, ...){
    if(_level < LogLevel::OH_INFO) return;
    va_list args;
    va_start(args, fmt);
    printf("[INFO] ");
    vprintf(fmt, args);
    printf("\r\n");
    va_end(args);
    printf("\r\n");
}

void Log::error(const char* fmt, ...){
    if(_level < LogLevel::OH_ERROR) return;

    va_list args;
    va_start(args, fmt);
    printf("[ERROR] ");
    vprintf(fmt, args);
    printf("\r\n");
    va_end(args);
    printf("\r\n");
}

void Log::debug(const char* fmt, ...){
    if(_level < LogLevel::OH_DEBUG) return;

    va_list args;
    va_start(args, fmt);
    printf("[DEBUG] ");
    vprintf(fmt, args);
    printf("\r\n");
    va_end(args);
    printf("\r\n");
}

void Log::warn(const char* fmt, ...){
    if(_level < LogLevel::OH_WARN) return;

    va_list args;
    va_start(args, fmt);
    printf("[WARNING] ");
    vprintf(fmt, args);
    printf("\r\n");
    va_end(args);
    printf("\r\n");
}

}