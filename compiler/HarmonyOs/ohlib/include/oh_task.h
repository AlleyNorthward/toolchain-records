#ifndef OH_TASK_H
#define OH_TASK_H

#include "hi_task.h"

namespace oh {
class Task {
private:
  hi_u32 taskId;
  const hi_task_attr taskAttr;
  using taskFunc = hi_void *(*)(hi_void *);

public:
  Task(const hi_task_attr& attr);
  hi_void createTask(taskFunc func, hi_void *args);
  hi_void deleteTask();
  hi_void suspendTask();
  hi_void resumeTask();
  hi_void getTaskPriority(hi_u32 *priority);
  hi_void setTaskPriority(hi_u32 priority);
};
} // namespace oh

#endif
