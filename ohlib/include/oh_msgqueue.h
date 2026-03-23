#ifndef OH_MSGQUEUE_H
#define OH_MSGQUEUE_H

extern "C"{
    #include "hi_msg.h"
}

/*
@author 巷北
@time 2026/3/14 22:22
@question
正在使用中的消息队列, 无法正常删除, 栈结束后析构会Error. 
安全做法, 栈上的消息队列, 创建在使用它的任务之前, 
这样该消息队列一定在任务释放之后再释放, 线程安全.
全局的消息队列没有测试过. 理论上可行, 但是由于无法
创建全局静态任务, 所以也不敢100%保证, 哈哈.

刚才试了一下, 全局静态变量没问题.
*/

namespace ohkit{

class MsgQueue{
private:
    hi_u32 id;

public:
    MsgQueue();
    ~MsgQueue();
    hi_void create(hi_u16 queue_len, hi_u32 msg_size);
    hi_void destory();
    hi_void send_oh(hi_pvoid msg, hi_u32 timeout_ms, hi_u32 msg_size);
    hi_void wait_oh(HI_OUT hi_pvoid msg, hi_u32 timeout_ms, hi_u32* msg_size);
    hi_void sendMsgToFront(hi_pvoid msg, hi_u32 msg_size, hi_u32 timeout_ms)const;

public:
    hi_u32 getId() const{return id;}
    hi_bool isFull() const {return hi_msg_queue_is_full(id);};
    hi_u32 getMsgNum() const;
    hi_u32 getMsgTotal() const;
};

}

#endif