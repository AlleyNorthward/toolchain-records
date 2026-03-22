# 简介
这部分内容, 进行了抽象, 以期望能够更加优雅地调用, 而不是似是而非地, 模棱两可地进行.

# 基本任务抽象

~~~c
class Task{
private:
    hi_u32 taskId;
    const hi_task_attr taskAttr;
    using funcPointer = hi_void*(*)(hi_void*);
public:
    Task(const hi_task_attr& attr):taskId(0), taskAttr(attr){}
    hi_void createTask(funcPointer func, hi_void* args){
        hi_u32 ret;
        ret = hi_task_create(&taskId, &taskAttr, func, args);

        if(ret != HI_ERR_SUCCESS){
            printf("Create test task failed [%u]\r\n", ret);
        }
    }

    hi_void deleteTask(){
         hi_u32 ret;
         ret = hi_task_delete(taskId);

         if(ret != HI_ERR_SUCCESS){
            printf("Delete test task failed [%u]\r\n", ret);
         }
    }

    hi_void suspendTask(){
        hi_u32 ret;
        ret = hi_task_suspend(taskId);
        if(ret != HI_ERR_SUCCESS){
            printf("Suspend test task failed [%u]\r\n", ret);
        }
    }

    hi_void resumeTask(){
        hi_u32 ret;
        ret = hi_task_resume(taskId);
        if(ret != HI_ERR_SUCCESS){
            printf("Resume test task failed [%u]\r\n", ret);
        }
    }

    hi_void getTaskPriority(hi_u32* priority){
        hi_u32 ret;
        ret = hi_task_get_priority(taskId, priority);
        if(ret != HI_ERR_SUCCESS){
            printf("Get task priority failed [%u]\r\n", ret);
        }
    }

    hi_void setTaskPriority(hi_u32 priority){
        hi_u32 ret;
        ret = hi_task_set_priority(taskId, priority);
        if(ret != HI_ERR_SUCCESS){
            printf("Set task priority failed [%u]\r\n", ret);
        }
    }
};
~~~
注意, 这里只是简单地进行了一定的封装, 但是具体调用时, 但是没有具体实例的参考, 后面的任务方法调用, 可能就会存在问题, 但是自己一定需要明确, 什么是什么, 这样后续存在问题的话, 就可以自定义修改.

# 任务表属性
~~~c
#ifndef ALL_TASK_H
#define ALL_TASK_H

#ifdef __cplusplus
extern "C" {
#endif
#include "hi_task.h"

hi_task_attr createTaskAttr(hi_u16 task_prio, hi_u32 stack_size, hi_char* task_name);

#ifdef __cplusplus
}
#endif

#endif
~~~

上面是具体声明, 下面是属性创建实例

~~~c
#include "all_task.h"

hi_task_attr createTaskAttr(hi_u16 task_prio, hi_u32 stack_size, hi_char* task_name){
    hi_task_attr myTask = {
        .task_prio = task_prio,
        .stack_size = stack_size,
        .task_name = task_name,
    };
    return myTask;
}
~~~

# 放入系统回调宏中

~~~cpp
hi_void task_demo(void){
    const hi_task_attr taskAttr1 = createTaskAttr(20, 4096, "test_task");

    Task task1(taskAttr1);
    auto func = [](hi_void* arg)->hi_void*{
        while(1){
            sleep(2);
            printf("kp task example is running!\r\n");
        }
        return NULL;
    };
    task1.createTask(
        func,
        nullptr
    );
}

APP_FEATURE_INIT(task_demo);
~~~
这里采用的 `lambda`函数, 这样, 我们不需要在外面创建函数, 再传入函数指针了, 这样会比较混乱, 而是可以通过栈内自定义创建函数, 并且可以灵活地实例化对象, 从而达到自己理想的目标.











