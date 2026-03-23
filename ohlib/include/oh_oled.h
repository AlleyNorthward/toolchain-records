#ifndef OH_OLED_H
#define OH_OLED_H

extern "C"{
    #include "oled.h"
    #include "spi_screen.h"
}

/*
@author 巷北
@time 2026/3/17 15:47
@describe
由于这部分内容呢, 是完全写死了的, 所以一开始就是想专门初始化, 
但现在想了想, 还是算了吧, 抓们抽象定义一个类吧, 这样是比较好
一些的, 哈哈.
算了算了, 还是写死了, 要不然栈上又有一些开销, 这部分没必要.
*/

namespace ohkit{

class Oled{
private:

public:
    Oled();
    hi_void init();
    hi_void reset();
    hi_void clear(hi_u8 dat);
};

}

#endif