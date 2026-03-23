#ifndef OH_TASK_H
#define OH_TASK_H

extern "C" {
  #include "hi_task.h"
}

/*
@author 巷北
@time 2026/3/14 17:07
@describe
这是Task类, 对hi 的api 进行了封装. 
@question
如果任务的回调函数(taskFunc), 一直执行, 可以正常删除任务. 如果回调函数执行结束, 就不需要删除任务了. 
我这里采用了RAII设计思想, 析构函数总会删除任务, 所以会存在日志ERROR错误, 但影响不大.
另外, 全局静态Task对象存在问题(无法正常编译, 问题不知), 只能是主任务栈上临时变量(栈上静态对象也不行, 语言层面问题)
*/

namespace ohkit {
class Task {
private:
  hi_u32 id;
  const hi_task_attr taskAttr;
  using taskFunc = hi_void *(*)(hi_void *);

public:
  Task(const hi_task_attr& attr);
  ~Task();
  hi_void create(taskFunc func, hi_void *args);
  hi_void suspend();
  hi_void resume();
  hi_void getPriority(hi_u32 *priority);
  hi_void setPriority(hi_u32 priority);
  static hi_void sleep(hi_u32 ms);
  static hi_void sysLock();
  static hi_void sysUnlock();
  hi_void destory();

public:
  hi_u32 getId()const{return id;};
};
} // namespace oh

#endif
