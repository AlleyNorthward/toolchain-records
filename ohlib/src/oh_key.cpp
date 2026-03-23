#include "oh_key.h"
#include "oh_log_utils.h"

namespace ohkit{

Key::Key(hi_gpio_idx id_):id(id_){
    LOG_RET(OH_W, "Key Constructor", id);
}

hi_void Key::init(hi_u8 func_val, hi_gpio_dir dir, hi_io_pull pull_val){
    hi_u32 ret;
    ret = IoTGpioInit(id);
    LOG_RET(ret, "In Key init Func, IoTGpioInit", id);
    ret = hi_io_set_func((hi_io_name)id, func_val);
    LOG_RET(ret, "In Key init Func, hi_io_set_func", id);
    ret = hi_gpio_set_dir(id, dir);
    LOG_RET(ret, "In Key init Fun, hi_gpio_set_dir", id);
    ret = hi_io_set_pull((hi_io_name)id, pull_val);
    LOG_RET(ret, "In Key init Fun, hi_io_set_pull", id);
}


hi_void Key::singlePress(keyFunc func, hi_void* args, hi_bool is_high_level){
    hi_u32 ret;
    if(is_high_level){
        ret = hi_gpio_register_isr_function(id, HI_INT_TYPE_EDGE, HI_GPIO_EDGE_RISE_LEVEL_HIGH, func, args);
        LOG_RET(ret, "Key singlePress high_level", id);
    } else {
        ret = hi_gpio_register_isr_function(id, HI_INT_TYPE_EDGE, HI_GPIO_EDGE_FALL_LEVEL_LOW, func, args);
        LOG_RET(ret, "Key singlePress low_level", id);
    }
}

hi_void Key::longPress(keyFunc func, hi_void* args, hi_bool is_high_level){
    hi_u32 ret;
    if(is_high_level){
        ret = hi_gpio_register_isr_function(id, HI_INT_TYPE_LEVEL, HI_GPIO_EDGE_RISE_LEVEL_HIGH, func, args);
        LOG_RET(ret, "Key longPress high_level", id);
    } else {
        ret = hi_gpio_register_isr_function(id, HI_INT_TYPE_LEVEL, HI_GPIO_EDGE_FALL_LEVEL_LOW, func, args);
        LOG_RET(ret, "Key longPress low_level", id);
    }
}

hi_u8 Key::read(){
    hi_gpio_value val;
    hi_gpio_get_input_val(id, &val);
    return (hi_u8)val;
}

const hi_char* Key::readStr(){
    hi_gpio_value val;
    hi_gpio_get_input_val(id, &val);

    return (!val) ? "1   " : "0   ";
}

}