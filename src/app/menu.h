#ifndef APP_MENU_H
#define APP_MENU_H

#include <PR/ultratypes.h>

void menuCreateVarHeight(s32 x, s32 y, s32 font, f32 xscale, f32 yscale, s32* items, s32 count);
void menuCreateItems(s32 x, s32 y, s32 font, f32 xscale, f32 yscale, s32* items, s32 itemCount);
s32 menuCheckInputs(void);
void menuRender(void);
void menuDeinit(void);
s32 menu_8030B668(void);
void menuSetItem(s32 idx, s16* str);
void menu_8030B69C(s32);

#endif // APP_MENU_H
