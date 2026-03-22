#ifndef ALL_TASK_H
#define ALL_TASK_H

#ifdef __cplusplus
extern "C" {
#endif
#include "hi_task.h"

hi_task_attr createTaskAttr(hi_u16 task_prio, hi_u32 stack_size,
                            hi_char *task_name);

#ifdef __cplusplus
}
#endif

#endif
