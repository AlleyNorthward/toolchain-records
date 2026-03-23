#ifndef OH_MUTEX_H
#define OH_MUTEX_H

extern "C" {
    #include "hi_mux.h"
}

/*
@author 巷北
@time 2026/3/14 17:14
@question
锁需要是全局静态锁, 任务最好是栈任务, 因为我自己使用的时候, 全局静态任务存在问题.
加锁使用LockGuard加锁, 而不是使用Mutex的方法. 加锁时, 采用{}, 这样线程安全, 结束时自动释放锁.
整体上来看, 锁是线程安全的, 遵循RAII设计思想, 尽量避免用户主动删除.
一. 谁加锁, 谁解锁. 比如, 任务1给锁1加锁, 任务3想给任务1的锁1解锁, 无法做到.
二. 任务删除, 需要不占用其他资源(锁, 信号量等). 所以, 任务1被锁1锁住了, 任务3也无法直接将任务1删除掉.
*/

namespace ohkit {

class Mutex{
private:
    hi_u32 id;
    Mutex(const Mutex&) = delete;
    Mutex& operator=(const Mutex&) = delete;

public:
    Mutex();
    ~Mutex();
    hi_void create();
    hi_void destory();
    hi_void lock(hi_u32 timeout_ms);
    hi_void unlock();

public:
    hi_u32 getId()const{return id;}
};

class LockGuard{
private:
    Mutex& _mutex;
public:
    LockGuard(Mutex &mutex, hi_u32 timeout_ms = HI_SYS_WAIT_FOREVER);
    ~LockGuard(){_mutex.unlock();}
};

}

#endif