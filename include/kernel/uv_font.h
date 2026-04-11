#ifndef UV_FONT_H
#define UV_FONT_H

#include <PR/ultratypes.h>
#include <uv_graphics.h>

typedef struct Unk80289380 {
    s32 x;
    s32 y;
    f32 scaleX;
    f32 scaleY;
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    s16 unk14[44];
    ParsedUVFT* unk6C;
} Unk80289380; // size = 0x70

void uvFontSet(s32);
s32 uvFontWidth(char*);
void uvFontScale(f64, f64);
void uvFontColor(u8 r, u8 g, u8 b, u8 a);
s32 func_802196B0(s16*);
s32 func_80219874(s32, s32, s16*, s32, s32);
void uvFontPrintStr(s32 x, s32 y, char* str);
void uvFontGenDlist(void);
s32 uvFontHeight(void);

#endif // UV_FONT_H
