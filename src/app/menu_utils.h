#ifndef APP_MENU_UTILS_H
#define APP_CODE_99D40_H

#include <PR/ultratypes.h>

typedef enum MenuColorSet {
    MENU_COLOR_SELECTED,
    MENU_COLOR_ITEM,
    MENU_COLOR_GRAPHICS
} MenuColorSet;

enum MenuSoundFlags {
    MENU_SOUND_SELECT = 0x1,
    MENU_SOUND_BACK   = 0x2,
    MENU_SOUND_CHANGE = 0x4
};

// function pointer to draw menu item
extern void (*gFcnDrawMenuItem)(s16, s16, s16);

void menuUtilCreate(s32 x, s32 y, s32 font, f32 xScale, f32 yScale, char** menuItems, s32 itemCount);
s32 menuUtilCheckInputs(void);
void menuUtilDeinit(void);
void menuUtilRender(void);
s32 menuUtilGetCurItem(void);
void menuUtilSetCurItem(s32 selection);
void menuUtilSetColors(MenuColorSet colorSet, u8 r, u8 g, u8 b);
void menuUtilSetSoundFlags(s32 soundFlags);
void menuUtilSetButtonMode(s32 buttonMode);

#endif // APP_MENU_UTILS_H
