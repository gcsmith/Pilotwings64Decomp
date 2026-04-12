#include "common.h"
#include <uv_font.h>
#include <uv_graphics.h>
#include <libc/stdarg.h>

// unused printf-like interface to print to screen
void func_803464A0(char* fmt, ...) {
    s32 yScreen;
    char* str;
    va_list args;

    yScreen = 150;
    uvGfxClearScreen(0x00, 0x00, 0x00, 0xFF); // black
    uvFontSet(5);
    uvFontScale(1.0, 1.0);
    uvFontColor(0xFF, 0xFF, 0xFF, 0xFF); // white
    uvFontPrintStr((SCREEN_WIDTH / 2) - (uvFontWidth(fmt) / 2), 200, fmt);
    uvFontSet(3);
    uvFontScale(1.0, 1.0);
    va_start(args, fmt);
    while ((str = va_arg(args, char*))) {
        uvFontPrintStr((SCREEN_WIDTH / 2) - (uvFontWidth(str) / 2), yScreen, str);
        yScreen = (yScreen - uvFontHeight()) - 3;
    }
}
