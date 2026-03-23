#include "oh_motor.h"
#include "oh_log_utils.h"

namespace ohkit{

Motor::Motor(hi_gpio_idx id_):id(id_){
    LOG_RET(OH_W, "Motor Constructor", id);
}

hi_void Motor::init(hi_u8 func_val, hi_gpio_dir dir){
    hi_u32 ret;
    ret = IoTGpioInit(id);
    LOG_RET(ret, "In Montor init Func, IoTGpioInit", id);
    ret = hi_io_set_func((hi_io_name)id, func_val);
    LOG_RET(ret, "In Montor init Func, hi_io_set_func", id);
    hi_gpio_set_dir(id, dir);
    LOG_RET(ret, "In Montor init Fun, hi_gpio_set_dir", id);
}

hi_void Motor::start(hi_bool is_high_level){
    hi_gpio_value val = HI_GPIO_VALUE0;
    if(is_high_level)
        val = HI_GPIO_VALUE1;

    hi_gpio_set_ouput_val(id, val);
}

hi_void Motor::stop(hi_bool is_high_level){
    hi_gpio_value val = HI_GPIO_VALUE1;
    if(is_high_level)
        val = HI_GPIO_VALUE0;

    hi_gpio_set_ouput_val(id, val);
}

}