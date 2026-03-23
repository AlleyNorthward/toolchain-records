#include "oh_pwm.h"
#include "oh_log_utils.h"
#include "iot_errno.h"

#define CLK_160M        160000000
#define DUTY_MAX        100
#define DUTY_MIN        0
#define SHORT_MAX       0xFFFF

namespace ohkit{

static hi_bool is_set_pwm_clock = false;

Pwm::Pwm(PwmAttr& config_):config(config_){
    LOG_RET(OH_W, "Pwm Constructor", config.id);
}

Pwm::~Pwm(){
    hi_u32 ret = hi_pwm_deinit(config.port);
    LOG_RET(ret, "Pwm Destroctor", config.id);
}

hi_void Pwm::init(){
    hi_u32 ret;
    ret = IoTGpioInit(config.id);
    LOG_RET(ret, "In Pwm init Func, IoTGpioInit", config.id);
    ret = hi_io_set_func((hi_io_name)config.id, config.func_val);
    LOG_RET(ret, "In Pwm init Func, hi_io_set_func", config.id);

    if(!is_set_pwm_clock){
        ret = hi_pwm_set_clock(config.clk);
        LOG_RET(ret, "In Pwm init Func, hi_pwm_set_clock", config.id);
        is_set_pwm_clock = true;
    }

    ret = hi_pwm_init(config.port);
    LOG_RET(ret, "In Pwm init Func, hi_pwm_init", config.id);
}

hi_void Pwm::start(hi_u16 duty, hi_u16 freq){
    LOG_RET(hi_pwm_start(config.port, duty, freq), "Pwm Start", config.id);
}

hi_void Pwm::stop(){
    LOG_RET(hi_pwm_stop(config.port), "Pwm Stop", config.id);
}

PwmLed::PwmLed(Pwm& pwm_):pwm(pwm_){
    LOG_RET(OH_W, "PwmLed Constructor", pwm.getConfig().id);
}

hi_void PwmLed::init(){
    pwm.init();
    LOG_RET(OH_W, "In PwmLed init Func", pwm.getConfig().id);
}

hi_void PwmLed::on(hi_u16 duty, hi_u16 freq){
    pwm.start(duty, freq);
    LOG_RET(OH_W, "In PwmLed on Func", pwm.getConfig().id);
}

hi_void PwmLed::off(){
    pwm.stop();
    LOG_RET(OH_W, "In PwmLed off Func", pwm.getConfig().id);
}

PwmBeep::PwmBeep(Pwm& pwm_):pwm(pwm_){
    LOG_RET(OH_W, "PwmBeep Constructor", pwm.getConfig().id);
}

hi_void PwmBeep::init(){
    pwm.init();
    LOG_RET(OH_W, "In PwmBeep init Func", pwm.getConfig().id);
}

hi_void PwmBeep::on(hi_u16 duty, hi_u16 freq){
    pwm.start(duty, freq);
    LOG_RET(OH_W, "In PwmBeep on Func", pwm.getConfig().id);
}

hi_void PwmBeep::off(){
    pwm.stop();
    LOG_RET(OH_W, "In PwmBeep off Func", pwm.getConfig().id);
}

}