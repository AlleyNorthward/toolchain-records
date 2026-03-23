#ifndef OH_LED_H
#define OH_LED_H

extern "C"{
    #include "hi_gpio.h"
    #include "hi_io.h"
    #include "iot_gpio.h"
    #include "cmsis_os.h"
}

/*
@author 巷北
@time 2026/3/15 18:35

led灯管脚汇总
## wifi开发板.  2 7 8
## 风扇开发板   6

is_high_level 表示的含义是, 是否高电平点亮?
另外, 对于LedState而言, 这么标注出来, 不就都是低电平点亮了吗?

*/

#define LED_INTERVAL_TIME       30

namespace ohkit{

class Led;

enum class LedState{
    OH_LED_ON = 0,
    OH_LED_OFF,
    OH_LED_SPARK
};

struct LedTask{
    Led& led;
    LedState state;
    hi_bool is_high_level;
    LedTask(Led& _led, LedState _state, hi_bool _is_high_level = false):led(_led), state(_state), is_high_level(_is_high_level){};
};

class Led{
private:
    hi_gpio_idx id;

public:
    Led(hi_gpio_idx id_);
    hi_void init(hi_u8 func_val, hi_gpio_dir dir);
    // 默认都是低电平点亮
    hi_void on(hi_bool is_high_level = false);
    hi_void off(hi_bool is_high_level = false);
    hi_void spark();
    static hi_void* ledTaskFunc(hi_void* args);
};

}

#endif