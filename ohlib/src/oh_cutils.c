#include "oh_cutils.h"

hi_task_attr createTaskAttr(hi_u16 task_prio, hi_u32 stack_size, hi_char *task_name) {
  hi_task_attr myTask = {
      .task_prio = task_prio,
      .stack_size = stack_size,
      .task_name = task_name,
  };
  return myTask;
}
