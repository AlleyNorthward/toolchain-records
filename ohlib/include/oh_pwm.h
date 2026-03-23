#ifndef OH_PWM_H
#define OH_PWM_H

extern "C"{
    #include "hi_gpio.h"
    #include "hi_io.h"
    #include "hi_pwm.h"
    #include "iot_gpio.h"
}

/*
@author 巷北
@time 2026/3/16 14:19
@describe
思想上的抽象, 还是具体抽象? 对于这个pwm而言, 本身就是一个抽象类, 很多具体实例, 比如beep, led, 需要pwm这个功能, 
可是如何合理地进行建模呢? 抽象基类没法使用, 也为了避免过耦合, 所以打算采用组合的方式, 来进行灵活解耦, 
可是这样设计真的可以吗? 

自己抽象定义了PwmTypeDef, 在栈上维护这些信息, 这种额外的隐形小空间占用, 是不是可以避免呢?
duty -> ccr
freq -> aar

*/

namespace ohkit{

struct PwmAttr {
    hi_gpio_idx id;
    hi_u8 func_val;
    hi_pwm_clk_source clk;
    hi_pwm_port port;
};

class Pwm {
private:
    PwmAttr& config;

public:
    Pwm(PwmAttr& config_);
    ~Pwm();
    hi_void init();
    hi_void start(hi_u16 duty, hi_u16 freq);
    hi_void stop();

public:
    PwmAttr& getConfig()const{return config;}
};

class PwmLed{
private:
    Pwm& pwm;

public:
    PwmLed(Pwm& pwm_);
    hi_void init();
    hi_void on(hi_u16 duty, hi_u16 freq);
    hi_void off();
};

class PwmBeep{
private:
    Pwm& pwm;
public:
    PwmBeep(Pwm& pwm_);
    hi_void init();
    hi_void on(hi_u16 duty, hi_u16 freq);
    hi_void off();
};

}

#endif