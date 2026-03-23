#include "oh_led.h"
#include "oh_log_utils.h"

namespace ohkit{

Led::Led(hi_gpio_idx id_):id(id_){
    LOG_RET(OH_W, "Led Constructor", id);
}

hi_void Led::init(hi_u8 func_val, hi_gpio_dir dir){
    hi_u32 ret;
    ret = IoTGpioInit(id);
    LOG_RET(ret, "In Led init Func, IoTGpioInit", id);
    ret = hi_io_set_func((hi_io_name)id, func_val);
    LOG_RET(ret, "In Led init Func, hi_io_set_func", id);
    hi_gpio_set_dir(id, dir);
    LOG_RET(ret, "In Led init Fun, hi_gpio_set_dir", id);
}

hi_void Led::on(hi_bool is_high_level){
    hi_gpio_value val = HI_GPIO_VALUE0;
    if(is_high_level)
        val = HI_GPIO_VALUE1;

    hi_gpio_set_ouput_val(id, val);
}

hi_void Led::off(hi_bool is_high_level){
    hi_gpio_value val = HI_GPIO_VALUE1;
    if(is_high_level)
        val = HI_GPIO_VALUE0;

    hi_gpio_set_ouput_val(id, val);
}

hi_void Led::spark(){
    hi_gpio_set_ouput_val(id, HI_GPIO_VALUE0);
    osDelay(LED_INTERVAL_TIME);
    hi_gpio_set_ouput_val(id, HI_GPIO_VALUE1);
    osDelay(LED_INTERVAL_TIME);
}

hi_void* Led::ledTaskFunc(hi_void* args){
    LedTask* lt = static_cast<LedTask*>(args);
    while(1){
        switch(lt->state){
            case LedState::OH_LED_ON:
                lt->led.on(lt->is_high_level);
                osDelay(LED_INTERVAL_TIME);
                break;
            case LedState::OH_LED_OFF:
                lt->led.off(lt->is_high_level);
                osDelay(LED_INTERVAL_TIME);
                break;
            case LedState::OH_LED_SPARK:
                lt->led.spark();
                break;
            default:
                osDelay(LED_INTERVAL_TIME);
                break;
        }
    }
}

}