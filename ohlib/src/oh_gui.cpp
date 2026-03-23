#include "oh_gui.h"
#include "oh_log_utils.h"

namespace ohkit{

Gui::Gui(){
    LOG_RET(OH_W, "In Gui Constructor", OH_DEFAULT_ID);
}

hi_void Gui::drawPoint(hi_u8 x, hi_u8 y, hi_u8 color){
    GUI_DrawPoint(x, y, color);
}

hi_void Gui::fill(hi_u8 sx, hi_u8 sy, hi_u8 ex, hi_u8 ey, hi_u8 color){
    GUI_Fill(sx, sy, ex, ey, color);
}

hi_void Gui::drawLine(hi_u8 x1, hi_u8 y1, hi_u8 x2, hi_u8 y2, hi_u8 color){
    GUI_DrawLine(x1, y1, x2, y2, color);
}

hi_void Gui::drawRectangle(hi_u8 x1, hi_u8 y1, hi_u8 x2, hi_u8 y2, hi_u8 color){
    GUI_DrawRectangle(x1, y1, x2, y2, color);
}

hi_void Gui::fillRectangle(hi_u8 x1, hi_u8 y1, hi_u8 x2, hi_u8 y2, hi_u8 color){
    GUI_FillRectangle(x1, y1, x2, y2, color);
}

hi_void Gui::drawCircle(hi_u8 xc, hi_u8 yc, hi_u8 color, hi_u8 r){
    GUI_DrawCircle(xc, yc, color, r);
}

hi_void Gui::fillCircle(hi_u8 xc, hi_u8 yc, hi_u8 color, hi_u8 r){
    GUI_FillCircle(xc, yc, color, r);
}

hi_void Gui::drawTriangle(hi_u8 x0, hi_u8 y0, hi_u8 x1, hi_u8 y1, hi_u8 x2, hi_u8 y2, hi_u8 color){
    GUI_DrawTriangel(x0, y0, x1, y1, x2, y2, color);
}

hi_void Gui::fillTriangle(hi_u8 x0, hi_u8 y0, hi_u8 x1, hi_u8 y1, hi_u8 x2, hi_u8 y2, hi_u8 color){
    GUI_FillTriangel(x0, y0, x1, y1, x2, y2, color);
}

hi_void Gui::showChar(hi_u8 x, hi_u8 y, hi_u8 chr, hi_u8 char_size, hi_u8 mode){
    GUI_ShowChar(x, y, chr, char_size, mode);
}

hi_void Gui::showNum(hi_u8 x, hi_u8 y, hi_u32 num, hi_u8 len, hi_u8 size, hi_u8 mode){
    GUI_ShowNum(x, y, num, len, size, mode);
}

hi_void Gui::showString(hi_u8 x, hi_u8 y, const char* chr, hi_u8 size, hi_u8 mode){
    GUI_ShowString(x, y, (const hi_u8*)chr, size, mode);
}

hi_void Gui::showFont16(hi_u8 x, hi_u8 y, const char* s, hi_u8 mode){
    GUI_ShowFont16(x, y, (const hi_u8*)s, mode);
}

hi_void Gui::showFont24(hi_u8 x, hi_u8 y, const char* s, hi_u8 mode){
    GUI_ShowFont24(x, y, (const hi_u8*)s, mode);
}

hi_void Gui::showFont32(hi_u8 x, hi_u8 y, const char* s, hi_u8 mode){
    GUI_ShowFont32(x, y, (const hi_u8*)s, mode);
}

hi_void Gui::showChinese(hi_u8 x, hi_u8 y, hi_u8 hsize, const char* str, hi_u8 mode){
    GUI_ShowCHinese(x, y, hsize, (const hi_u8*)str, mode);
}

hi_void Gui::drawBmp(hi_u8 x, hi_u8 y, hi_u8 width, hi_u8 height, hi_u8 BMP[], hi_u8 mode){
    GUI_DrawBMP(x, y, width, height, BMP, mode);
}

}