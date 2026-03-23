#include "oh_event.h"
#include "oh_log_utils.h"

namespace ohkit{

hi_bool Event::isinit = false;

Event::Event():id(0){
    LOGD("Event Constructor Running.");
}

Event::~Event(){
    LOG_RET(OH_W, "This is Event Destructor, depend on destory func", id);
    destory();
}

hi_void Event::init(hi_u8 max_event_cnt, hi_pvoid event_space){
    hi_u32 ret = hi_event_init(max_event_cnt, event_space);
    LOG_RET(ret, "Event Pool", OH_DEFAULT_ID);
    Event::isinit = true;
}

hi_void Event::create(){
    hi_u32 ret = hi_event_create(&id);
    LOG_RET(ret, "Event Create", id);
}

hi_void Event::send(hi_u32 event_bits){
    hi_u32 ret = hi_event_send(id, event_bits);
    LOG_RET(ret, "Event Send", id);
}

hi_void Event::wait(hi_u32 mask, HI_OUT hi_u32* event_bits, hi_u32 timeout, hi_u32 flag){
    hi_u32 ret = hi_event_wait(id, mask, event_bits, timeout, flag);
    LOG_RET(ret, "Event Wait", id);
}

hi_void Event::clear(hi_u32 event_bits){
    hi_u32 ret = hi_event_clear(id, event_bits);
    LOG_RET(ret, "Event clear", id);
}

hi_void Event::destory(){
    hi_u32 ret = hi_event_delete(id);
    LOG_RET(ret, "Event Delete. If show ERROR, may duplicate deletion.", id);
}

}