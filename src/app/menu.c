#include "common.h"
#include <uv_graphics.h>
#include <uv_sprite.h>
#include "code_99D40.h"
#include "menu.h"
#include "text_data.h"

// forward declarations
static void menuCreate(s32 x, s32 y, s32 arg2, f32 xscale, f32 yscale, s32 itemCount);
static void menuDrawItem(s16 arg0, s16 arg1, s16 idx);

// arrays of pointers to 16-bit strings
// e.g. "Option" from main menu is 0x0078 0x0093 0x0097 0x008c 0x0092 0091 0x0ffe 0xffff
static s16* gMenuItems[5];
static s16 gMenuSpriteIdBase;
static s16 gMenuSpriteHeight;
static s16 gMenuCountVarHeight;

static void menuCreate(s32 x, s32 y, s32 arg2, f32 xscale, f32 yscale, s32 itemCount) {
    s32 i;

    gMenuSpriteHeight = 0;
    if (itemCount > ARRAY_COUNT(gMenuItems)) {
        _uvDebugPrintf("kmenu_init : too may elements in the menu [%d]\n", itemCount);
    }
    func_80312810(x, y, arg2, xscale, yscale, 0, itemCount);

    // clang-format off: needs to be on same line to match
    for (i = 0; i < ARRAY_COUNT(gMenuItems); i++) { gMenuItems[i] = NULL; }
    // clang-format on

    gFcnDrawMenuItem = &menuDrawItem;
}

// menuCreateVarHeight is unused, but serves as a wrapper for menuCreate
// it computes non-zero gMenuSpriteHeight, triggering different code paths below
void menuCreateVarHeight(s32 x, s32 y, s32 arg2, f32 xscale, f32 yscale, s32* items, s32 count) {
    s32 i;

    menuCreate(x, y, arg2, xscale, yscale, count);
    gMenuCountVarHeight = (s16)count;
    gMenuSpriteIdBase = 0xF;

    for (i = 0; i < count; i++) {
        uvSprtProps(gMenuSpriteIdBase + i, 3, 1, 2, x, ((gMenuSpriteHeight + 6) * i) + y, 9, items[i], 0);
        gMenuSpriteHeight = uvSprtGetHeight(gMenuSpriteIdBase + i);
    }
}

void menuCreateItems(s32 x, s32 y, s32 arg2, f32 xscale, f32 yscale, s32* items, s32 itemCount) {
    s32 temp_v0;
    s32 i;

    menuCreate(x, y, arg2, xscale, yscale, itemCount);

    for (i = 0; i < itemCount; i++) {
        gMenuItems[i] = textGetDataByIdx(items[i]);
    }
}

s32 menu_8030B50C(void) {
    return func_80312908();
}

void menuInit(void) {
    func_80312B5C();
}

void menuSetProps(void) {
    s32 i;

    func_80312B50();
    for (i = 0; i < gMenuCountVarHeight; i++) {
        uvSprtProps(gMenuSpriteIdBase + i, 3, 0, 0);
    }
}

static void menuDrawItem(s16 arg0, s16 arg1, s16 idx) {
    if (gMenuSpriteHeight != 0) {
        uvSprtProps(gMenuSpriteIdBase + idx, 2, arg0, arg1 + gMenuSpriteHeight + 2, 0);
        uvSprtDraw(gMenuSpriteIdBase + idx);
    } else {
        func_80219874(arg0, arg1, gMenuItems[idx], 100, 0xFFE);
    }
}

s32 menu_8030B668(void) {
    return func_80312F38();
}

void menuSetItem(s32 idx, s16* str) {
    gMenuItems[idx] = str;
}

void menu_8030B69C(s32 arg0) {
    func_80312F44(arg0);
}
