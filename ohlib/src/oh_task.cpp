#include "oh_log_utils.h"
#include "oh_task.h"

namespace ohkit {
Task::Task(const hi_task_attr &attr): id(0), taskAttr(attr) {
  LOGD("Task Constructor Running.");
}
hi_void Task::create(taskFunc func, hi_void *args) {
  hi_u32 ret = hi_task_create(&id, &taskAttr, func, args);
  LOG_RET(ret, "Task Create", id);
}

Task::~Task(){
    LOG_RET(OH_D, "This is Task Destructor, depend on destory func", id);
    destory();
}

hi_void Task::destory() {
  hi_u32 ret = hi_task_delete(id);

  LOG_RET(ret, "Task Delete. If show ERROR, may duplicate deletion.", id);
}

hi_void Task::suspend() {
  hi_u32 ret = hi_task_suspend(id);
  LOG_RET(ret, "Task Suspend", id);
}

hi_void Task::resume() {
  hi_u32 ret = hi_task_resume(id);
  LOG_RET(ret, "Task Resume", id);
}

hi_void Task::getPriority(hi_u32 *priority) {
  hi_u32 ret = hi_task_get_priority(id, priority);
  LOG_RET(ret, "Get Task Priority", id);
}

hi_void Task::setPriority(hi_u32 priority) {
  hi_u32 ret = hi_task_set_priority(id, priority);
  LOG_RET(ret, "Set Task Priority Success", id);
}

hi_void Task::sysLock(){
  hi_task_lock();
  LOGD("Task Locked by Sys. Not Mutex.");
}

hi_void Task::sysUnlock(){
  hi_task_unlock();
  LOGD("Task UnLocked by Sys. Not Mutex.");
}

hi_void Task::sleep(hi_u32 ms){
  LOGI("Task Sleep %u ms", ms);
  hi_u32 ret = hi_sleep(ms);

  if(ret == HI_ERR_SUCCESS){
    LOGD("Task Sleep %u ms Success.", ms);
  } else{
    LOGE("Task Sleep %u ms Failed.", ms);
  }
}
} // namespace ohkit
