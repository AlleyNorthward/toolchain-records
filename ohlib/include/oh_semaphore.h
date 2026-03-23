#ifndef OH_SEMAPHORE_H
#define OH_SEMAPHORE_H

extern "C"{
    #include "hi_sem.h"
}

/*
@author 巷北
@time 2026/3/14 18:56
@describe
好了, 摸到套路了, 感觉十分固定化了, 整体上十分整洁
这些操作系统上的抽象api接口找到编写技巧了, 感觉还不错, 甚至有些简单...
现在接口命名都是统一的, 内部逻辑也是一样的, 不用担心意外, 因为
api底层都预防了, 所以我只是设计了一下log日志, 能够打印详细信息, 
比如说错误码, 可以根据错误码找到对应api的返回宏, 根据宏名分析错误原因.
大部分错误信息还是能解决的.
将接口封装之后, 剩下的就是整个运行过程了, 这跟设计没有关系, 全是对语言的
理解. 有些东西是不可控的, 比如说操作系统运行原理, 可能会存在一些小问题, 
但几乎都是可控的.
*/

namespace ohkit{

class Semaphore{
private:
    hi_u32 id;

public:
    Semaphore();
    ~Semaphore();
    hi_void create(hi_u16 init_value);
    hi_void bcreate(hi_u8 init_vaule);
    hi_void destory();
    hi_void wait(hi_u32 timeout_ms);
    hi_void signal();

public:
    hi_u32 getId()const{return id;};
};

}

#endif