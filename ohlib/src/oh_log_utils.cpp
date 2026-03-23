#include "oh_log_utils.h"
#include "oh_log.h"
#include "hi_errno.h"

namespace ohkit{

hi_void logRet(hi_u32 ret, const char* msg, const char* func, const char* file, hi_u32 line, hi_u32 id){
    switch(ret){
        case HI_ERR_SUCCESS:
            LOGI("%s Running Success. Id is [%u]. In File: %s, Func: %s, Line: %u. return code: [0x%x].", msg, id, file, func, line, ret);
            break;
        case HI_ERR_TASK_CREATE_FAIL:
            LOGE("%s Running Failed. Id is [%u]. InFile: %s, Func: %s, Line: %u. return code: [0x%x].", msg, id, file, func, line, ret);
            break;
        case HI_ERR_TASK_INVALID_PARAM:
            LOGE("Invalid Param. msg is %s.Id is [%u]. InFile: %s, Func: %s, Line: %u. return code: [0x%x].", msg, id, file, func, line, ret);
            break;

        case OH_S:
            LOGI("%s Running Success. Id is [%u]. In File: %s, Func: %s, Line: %u. return code: [0x%x].", msg, id, file, func, line, ret);
            break;
        case OH_E:
            LOGE("%s Running Failed. Id is [%u]. InFile: %s, Func: %s, Line: %u. retrun code: [0x%x].", msg, id, file, func, line, ret);
            break;
        case OH_W:
            LOGW("%s. Id is [%u]. InFile: %s, Func: %s, Line: %u. retrun code: [0x%x].", msg, id, file, func, line, ret);
            break;
        case OH_D:
            LOGD("%s. Id is [%u]. InFile: %s, Func: %s, Line: %u. return code: [0x%x].", msg, id, file, func, line, ret);
            break;

        default:
            LOGE("This is the default log. See hi_errno.h. Details: msg: %s. Id: [%u]. InFile: %s, Func: %s, Line: %u. return code: [0x%x].", msg, id, file, func, line, ret);
            break;
    }
}

}