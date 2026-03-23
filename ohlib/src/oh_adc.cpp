#include "oh_adc.h"
#include "oh_log_utils.h"

#define OH_DATA_MAX         (hi_u16)0xFFFF

namespace ohkit{

Adc::Adc():data(OH_DATA_MAX){
    LOG_RET(OH_W, "Adc Constructor", OH_DEFAULT_ID);
}

hi_void Adc::read(hi_adc_channel_index channel, hi_adc_equ_model_sel equ_model, hi_adc_cur_bais cur_bais, hi_u16 delay_cnt){
    hi_u32 ret = hi_adc_read(channel, &data, equ_model, cur_bais, delay_cnt);
    LOG_RET(ret, "Adc read", OH_DEFAULT_ID);
}

hi_float Adc::getVoltage(){
    hi_float voltage = data * 1.8 * 4 / 4096;
    return voltage;
}

}