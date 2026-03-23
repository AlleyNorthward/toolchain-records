#include "oh_msgqueue.h"
#include "oh_log_utils.h"

namespace ohkit{

MsgQueue::MsgQueue():id(0){
    LOGD("MsgQueue Constructor Running.");
}

MsgQueue::~MsgQueue(){
    LOG_RET(OH_W, "This is MsgQueue Destructor, depend on destory func", id);
    destory();
}

hi_void MsgQueue::create(hi_u16 queue_len, hi_u32 msg_size){
    hi_u32 ret = hi_msg_queue_create(&id, queue_len, msg_size);
    LOG_RET(ret, "MsgQueue Create", id);
}

hi_void MsgQueue::destory(){
    hi_u32 ret = hi_msg_queue_delete(id);
    LOG_RET(ret, "MsgQueue Delete. If show ERROR, may duplicate deletion.", id);
}

hi_void MsgQueue::send_oh(hi_pvoid msg, hi_u32 timeout_ms, hi_u32 msg_size){
    hi_u32 ret = hi_msg_queue_send(id, msg, timeout_ms, msg_size);
    LOG_RET(ret, "MsgQueue Send", id);

}

hi_void MsgQueue::wait_oh(HI_OUT hi_pvoid msg, hi_u32 timeout_ms, hi_u32* msg_size){
    hi_u32 ret = hi_msg_queue_wait(id, msg, timeout_ms, msg_size);
    LOG_RET(ret, "MsgQueue Wait", id);
}

hi_u32 MsgQueue::getMsgNum() const{
    hi_u32 ret = hi_msg_queue_get_msg_num(id);
    LOG_RET(OH_W, "MsgQueue getMsgNum. See return code.", id);
    return ret;
}

hi_u32 MsgQueue::getMsgTotal()const{
    hi_u32 ret = hi_msg_queue_get_msg_total(id);
    LOG_RET(OH_W, "MsgQueue getMsgTotal. See return code.", id);
    return ret;
}

hi_void MsgQueue::sendMsgToFront(hi_pvoid msg, hi_u32 msg_size, hi_u32 timeout_ms)const{
    hi_u32 ret = hi_msg_queue_send_msg_to_front(id, msg, msg_size, timeout_ms);
    LOG_RET(ret, "MsgQueue Send Msg To Front", id);
}

}