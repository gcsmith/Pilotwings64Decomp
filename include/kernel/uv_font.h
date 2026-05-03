#ifndef PILOTWINGS64_UV_FONT_H
#define PILOTWINGS64_UV_FONT_H

#include <uv_common.h>

void uvFontSet(s32 fontId);
void uvFontScale(f64 x, f64 y);
void uvFontColor(u8 r, u8 g, u8 b, u8 a);
s32 uvFontStr16Width(s16* str16);
s32 uvFontWidth(const char* str);
s32 uvFontHeight(void);
s32 uvFontPrintStr16(s32 x, s32 y, s16* str16, s32 strLen, s32 end);
void uvFontPrintStr(s32 x, s32 y, const char* str);
void uvFontGenDlist(void);

#endif // PILOTWINGS64_UV_FONT_H

