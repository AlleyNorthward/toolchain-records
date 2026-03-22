#include "oh_task.h"

namespace oh {
Task::Task(const hi_task_attr &attr) : taskId(0), taskAttr(attr) {}
Task::hi_void createTask(taskFunc func, hi_void *args) {
  hi_u32 ret;
  ret = hi_task_create(&taskId, &taskAttr, func, args);

  if (ret != HI_ERR_SUCCESS) {
    printf("Create test task failed [%u]\r\n", ret);
  }
}

Task::hi_void deleteTask() {
  hi_u32 ret;
  ret = hi_task_delete(taskId);

  if (ret != HI_ERR_SUCCESS) {
    printf("Delete test task failed [%u]\r\n", ret);
  }
}

Task::hi_void suspendTask() {
  hi_u32 ret;
  ret = hi_task_suspend(taskId);
  if (ret != HI_ERR_SUCCESS) {
    printf("Suspend test task failed [%u]\r\n", ret);
  }
}

Task::hi_void resumeTask() {
  hi_u32 ret;
  ret = hi_task_resume(taskId);
  if (ret != HI_ERR_SUCCESS) {
    printf("Resume test task failed [%u]\r\n", ret);
  }
}

Task::hi_void getTaskPriority(hi_u32 *priority) {
  hi_u32 ret;
  ret = hi_task_get_priority(taskId, priority);
  if (ret != HI_ERR_SUCCESS) {
    printf("Get task priority failed [%u]\r\n", ret);
  }
}

Task::hi_void setTaskPriority(hi_u32 priority) {
  hi_u32 ret;
  ret = hi_task_set_priority(taskId, priority);
  if (ret != HI_ERR_SUCCESS) {
    printf("Set task priority failed [%u]\r\n", ret);
  }
}
} // namespace oh
