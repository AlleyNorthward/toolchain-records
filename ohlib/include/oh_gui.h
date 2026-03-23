#ifndef OH_GUI_H
#define OH_GUI_H

extern "C"{
    #include "gui.h"
    #include <hi_types_base.h>
}

namespace ohkit{

class Gui{
public:
    Gui();
    hi_void drawPoint(hi_u8 x, hi_u8 y, hi_u8 color);
    hi_void fill(hi_u8 sx, hi_u8 sy, hi_u8 ex, hi_u8 ey, hi_u8 color);
    hi_void drawLine(hi_u8 x1, hi_u8 y1, hi_u8 x2, hi_u8 y2, hi_u8 color);
    hi_void drawRectangle(hi_u8 x1, hi_u8 y1, hi_u8 x2, hi_u8 y2, hi_u8 color);
    hi_void fillRectangle(hi_u8 x1, hi_u8 y1, hi_u8 x2, hi_u8 y2, hi_u8 color);
    hi_void drawCircle(hi_u8 xc, hi_u8 yc, hi_u8 color, hi_u8 r);
    hi_void fillCircle(hi_u8 xc, hi_u8 yc, hi_u8 color, hi_u8 r);
    hi_void drawTriangle(hi_u8 x0, hi_u8 y0, hi_u8 x1, hi_u8 y1, hi_u8 x2, hi_u8 y2, hi_u8 color);
    hi_void fillTriangle(hi_u8 x0, hi_u8 y0, hi_u8 x1, hi_u8 y1, hi_u8 x2, hi_u8 y2, hi_u8 color);
    hi_void showChar(hi_u8 x, hi_u8 y, hi_u8 chr, hi_u8 char_size, hi_u8 mode);
    hi_void showNum(hi_u8 x, hi_u8 y, hi_u32 num, hi_u8 len, hi_u8 size, hi_u8 mode);
    hi_void showString(hi_u8 x, hi_u8 y, const char* chr, hi_u8 size, hi_u8 mode);
    hi_void showFont16(hi_u8 x, hi_u8 y, const char* s, hi_u8 mode);
    hi_void showFont24(hi_u8 x, hi_u8 y, const char* s, hi_u8 mode);
    hi_void showFont32(hi_u8 x, hi_u8 y, const char* s, hi_u8 mode);
    hi_void showChinese(hi_u8 x, hi_u8 y, hi_u8 hsize, const char* str, hi_u8 mode);
    hi_void drawBmp(hi_u8 x, hi_u8 y, hi_u8 width, hi_u8 height, hi_u8 BMP[], hi_u8 mode);
};

}

#endif