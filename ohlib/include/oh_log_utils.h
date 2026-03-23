#ifndef OH_LOG_UTILS_H
#define OH_LOG_UTILS_H

#include "oh_log.h"
#include "hi_types_base.h"

#ifdef OH_LOG_ENABLE

#define LOGE(...)                   ohkit::Log::instance().error(__VA_ARGS__)
#define LOGW(...)                   ohkit::Log::instance().warn(__VA_ARGS__)
#define LOGI(...)                   ohkit::Log::instance().info(__VA_ARGS__)
#define LOGD(...)                   ohkit::Log::instance().debug(__VA_ARGS__)

#else

#define LOGE(...)
#define LOGW(...)
#define LOGI(...)
#define LOGD(...)

#endif

#define LOG_SET_LEVEL(level)        ohkit::Log::instance().setLevel(level)
#define OH_DEFAULT_ERROR_CODE       0xFFFFFFFF
#define OH_DEFAULT_ID               0xFFFFFFFF
#define OH_S                        0x00000001
#define OH_E                        0x00000002
#define OH_W                        0x00000003
#define OH_D                        0x00000004

namespace ohkit{

hi_void logRet(hi_u32 ret, const char* msg, const char* func, const char* file, hi_u32 line, hi_u32 id = OH_DEFAULT_ID);

}

#define LOG_RET(ret, msg, id)       ohkit::logRet(ret, msg, __func__, __FILE__, __LINE__, id);

#endif