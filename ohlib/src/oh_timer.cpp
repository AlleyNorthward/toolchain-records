#include "oh_timer.h"
#include "oh_log_utils.h"

namespace ohkit{

Timer::Timer():id(0){
    LOGD("Timer Constructor Running.");
}

Timer::~Timer(){
    LOG_RET(OH_W, "This is Timer Destructor, depend on destory func", id);
    destory();
}

hi_void Timer::create(){
    hi_u32 ret = hi_timer_create(&id);
    LOG_RET(ret, "Timer Create", id);
}

hi_void Timer::start(hi_timer_type type, hi_u32 expire, hi_timer_callback_f timer_func, hi_u32 data){
    hi_u32 ret = hi_timer_start(id, type, expire, timer_func, data);
    isrunning = true;
    LOG_RET(ret, "Timer Start", id);
}

hi_void Timer::stop(){
    hi_u32 ret = hi_timer_stop(id);
    isrunning = false;
    LOG_RET(ret, "Timer Stop", id);
}

hi_void Timer::destory(){
    // 删除定时器后, id不为0.
    hi_u32 ret;

    if(isrunning){
        LOGW("Delete Timer, but not stop timer. isrunning:%d, in File: %s, Func: %s, Line: %d.", isrunning, __FILE__, __func__, __LINE__);
        stop();
        isrunning = false;
    }

    ret = hi_timer_delete(id);
    LOG_RET(ret, "Timer Destory. If show ERROR, may duplicate deletion.", id);
}

}