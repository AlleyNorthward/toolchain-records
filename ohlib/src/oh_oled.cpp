#include "oh_oled.h"
#include "oh_log_utils.h"

namespace ohkit{

Oled::Oled(){
    LOG_RET(OH_W, "In Oled Constructor", OH_DEFAULT_ID);
}

hi_void Oled::init(){
    hi_u32 ret;
    ret = hi_io_set_func(HI_IO_NAME_GPIO_8, HI_IO_FUNC_GPIO_8_GPIO);
    LOG_RET(ret, "In Oled init func, hi_io_set_func", OH_DEFAULT_ID);
    ret = hi_gpio_set_dir(HI_GPIO_IDX_8, HI_GPIO_DIR_OUT);
    LOG_RET(ret, "In Oled init func, hi_gpio_set_dir", OH_DEFAULT_ID);
    ret = hi_io_set_func(HI_IO_NAME_GPIO_11, HI_IO_FUNC_GPIO_11_GPIO);
    LOG_RET(ret, "In Oled init func, hi_io_set_func", OH_DEFAULT_ID);
    ret = hi_gpio_set_dir(HI_GPIO_IDX_11, HI_GPIO_DIR_OUT);
    LOG_RET(ret, "In Oled init func, hi_gpio_set_dir", OH_DEFAULT_ID);

    ret = hi_spi_deinit(HI_SPI_ID_0);
    LOG_RET(ret, "In Oled init func, hi_spi_deinit", OH_DEFAULT_ID);
    screen_spi_master_init(HI_SPI_ID_0);

    OLED_Init();
    OLED_Clear(0);
}

hi_void Oled::reset(){
    OLED_Reset();
}

hi_void Oled::clear(hi_u8 dat){
    OLED_Clear(dat);
}
}