#include "oh_semaphore.h"
#include "oh_log_utils.h"

namespace ohkit{

Semaphore::Semaphore():id(0){
    LOGD("Semaphore Constructor Running.");
}

Semaphore::~Semaphore(){
    LOG_RET(OH_W, "This is Semaphore Destructor, depend on destory func", id);
    destory();
}

hi_void Semaphore::create(hi_u16 init_value){
    hi_u32 ret = hi_sem_create(&id, init_value);
    LOG_RET(ret, "Semaphore Create", id);
}

hi_void Semaphore::bcreate(hi_u8 init_value){
    hi_u32 ret = hi_sem_bcreate(&id, init_value);
    LOG_RET(ret, "Semaphore bCreate", id);
}

hi_void Semaphore::destory(){
    hi_u32 ret = hi_sem_delete(id);
    LOG_RET(ret, "Semaphore Delete. If show ERROR, may duplicate deletion.", id);

}

hi_void Semaphore::wait(hi_u32 timeout_ms){
    hi_u32 ret = hi_sem_wait(id, timeout_ms);
    LOG_RET(ret, "Semaphore Wait", id);
}

hi_void Semaphore::signal(){
    hi_u32 ret = hi_sem_signal(id);
    LOG_RET(ret, "Semaphore Singal", id);
}

}