#ifndef OH_ADC_H
#define OH_ADC_H

#include "hi_adc.h"

namespace ohkit{

class Adc{
private:
    hi_u16 data;

public:
    Adc();
    hi_void read(hi_adc_channel_index channel, hi_adc_equ_model_sel equ_model, hi_adc_cur_bais cur_bais, hi_u16 delay_cnt);

    hi_float getVoltage();
    hi_u16 getData()const{return data;}
};

}

#endif