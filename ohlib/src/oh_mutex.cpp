#include "oh_log_utils.h"
#include "oh_mutex.h"

namespace ohkit{

Mutex::Mutex():id(0){
    LOGD("Mutex Constructor Running.");
}

Mutex::~Mutex(){
    LOG_RET(OH_D, "This is Mutex Destructor, depend on destory func.", id);
    destory();
}

hi_void Mutex::create(){
    hi_u32 ret = hi_mux_create(&id);
    LOG_RET(ret, "Create Mutex", id);
}

hi_void Mutex::lock(hi_u32 timeout_ms){
    hi_u32 ret = hi_mux_pend(id, timeout_ms);
    LOG_RET(ret, "Lock", id);
}

hi_void Mutex::unlock(){
    hi_u32 ret = hi_mux_post(id);
    LOG_RET(ret, "Unlock", id);
}

hi_void Mutex::destory(){
    hi_u32 ret = hi_mux_delete(id);
    LOG_RET(ret, "Delete mutex. If show ERROR, may duplicate deletion.", id);
}

LockGuard::LockGuard(Mutex& mutex, hi_u32 timeout_ms):_mutex(mutex){
    _mutex.lock(timeout_ms);
    LOG_RET(OH_D, "LockGuard Running Success", OH_DEFAULT_ID);
}

}