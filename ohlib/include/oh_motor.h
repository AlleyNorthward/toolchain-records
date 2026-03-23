#ifndef OH_MOTOR_H
#define OH_MOTOR_H

extern "C"{
    #include "hi_gpio.h"
    #include "hi_io.h"
    #include "iot_gpio.h"
    #include "cmsis_os.h"
}

/*
@author 巷北
@time 2026/3/16 9:14

电机跟小灯从代码上来看是一模一样的. 所以可以将基础部分抽象出来, 
而不是又重新对着写一遍. 
不过由于时间有限, 所以只能选择最简单的方案, 也就是对着写一遍, 哈哈.

*/

namespace ohkit{

enum class MotorState{
    OH_MOTOR_ON = 0,
    OH_LED_OFF,
};

class Motor{

private:
    hi_gpio_idx id;

public:
    Motor(hi_gpio_idx id_);
    hi_void init(hi_u8 func_val, hi_gpio_dir dir);

    hi_void start(hi_bool is_high_level = false);
    hi_void stop(hi_bool is_high_level = false);
};

}


#endif