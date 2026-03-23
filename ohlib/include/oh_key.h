#ifndef OH_KEY_H
#define OH_KEY_H

extern "C"{
    #include "hi_gpio.h"
    #include "hi_io.h"
    #include "iot_gpio.h"
}

namespace ohkit{

enum class KeyState{
    OH_KEY_OFF = 0,
    OH_KEY_ON
};

class Key{
private:
    hi_gpio_idx id;
    using keyFunc = hi_void (*)(hi_void *);

public:
    Key(hi_gpio_idx id_);
    hi_void init(hi_u8 func_val, hi_gpio_dir dir, hi_io_pull pull_val);
    hi_void singlePress(keyFunc func, hi_void* args, hi_bool is_high_level = false);
    hi_void longPress(keyFunc func, hi_void* args, hi_bool is_high_level = false);
    hi_u8 read();
    const hi_char* readStr();
};

}

#endif