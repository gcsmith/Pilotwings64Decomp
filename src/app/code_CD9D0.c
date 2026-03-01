#include "common.h"
#include <uv_font.h>
#include <uv_graphics.h>
#include <libc/stdarg.h>

void func_803464A0(char* arg0, ...) {
    s32 var_s2;
    char* var_s0;
    va_list args;

    var_s2 = 0x96;
    uvGfxClearScreen(0U, 0U, 0U, 0xFFU);
    uvFontSet(5);
    uvFont_80219550(1.0, 1.0);
    uvFont_8021956C(0xFFU, 0xFFU, 0xFFU, 0xFFU);
    uvFont_80219ACC(0xA0 - (uvFontWidth(arg0) / 2), 0xC8, arg0);
    uvFontSet(3);
    uvFont_80219550(1.0, 1.0);
    va_start(args, arg0);
    while ((var_s0 = va_arg(args, char*))) {
        uvFont_80219ACC(0xA0 - (uvFontWidth(var_s0) / 2), var_s2, var_s0);
        var_s2 = (var_s2 - func_80219828()) - 3;
    }
}
