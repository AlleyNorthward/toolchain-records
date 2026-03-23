#ifndef OH_EVENT_H
#define OH_EVENT_H

extern "C"{
    #include "hi_event.h"
}

namespace ohkit{

class Event{
private:
    hi_u32 id;
    static hi_bool isinit;

public:
    Event();
    ~Event();
    static hi_void init(hi_u8 max_event_cnt = 4, hi_pvoid event_space = nullptr);
    hi_void create();
    hi_void send(hi_u32 event_bits);
    hi_void wait(hi_u32 mask, HI_OUT hi_u32 *event_bits, hi_u32 timeout, hi_u32 flag);
    hi_void clear(hi_u32 event_bits);
    hi_void destory();

public:
    hi_u32 getId()const{return id;};
};

}

#endif