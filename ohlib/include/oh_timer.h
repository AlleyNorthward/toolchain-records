#ifndef OH_TIMER_H
#define OH_TIMER_H

extern "C"{
    #include "hi_timer.h"
}

/*
@author 巷北
@time 2026/3/14 11:46
@describe
这是一个定时器类. 遵循RAII, 但是不清楚 栈延期delete和手动delete区别. 
建议还是手动stop, 手动delete, 提前释放资源.
*/

#define OH_ONCE             HI_TIMER_TYPE_ONCE
#define OH_PERIOD           HI_TIMER_TYPE_PERIOD

namespace ohkit{

class Timer{
private:
    hi_u32 id;
    hi_bool isrunning = false;
    hi_bool isdelete = false;

public:
    Timer();
    ~Timer();
    hi_void create();
    hi_void start(hi_timer_type type, hi_u32 expire, hi_timer_callback_f timer_func, hi_u32 data);
    hi_void stop();
    hi_void destory();

public:
    hi_u32 getId()const{return id;};
};

}

#endif