#include "common.h"
#include <uv_font.h>
#include <uv_graphics.h>
#include <uv_sprite.h>
#include "menu.h"
#include "menu_utils.h"
#include "text_data.h"

// forward declarations
STATIC_FUNC void menuCreate(s32 x, s32 y, s32 arg2, f32 xscale, f32 yscale, s32 itemCount);
STATIC_FUNC void menuDrawItem(s16 x, s16 y, s16 idx);

// arrays of pointers to 16-bit strings
// e.g. "Option" from main menu is 0x0078 0x0093 0x0097 0x008c 0x0092 0091 0x0ffe 0xffff
static s16* sMenuItems[5];
static s16 sMenuSpriteIdBase;
static s16 sMenuSpriteHeight;
static s16 sMenuCountVarHeight;

STATIC_FUNC void menuCreate(s32 x, s32 y, s32 font, f32 xscale, f32 yscale, s32 itemCount) {
    s32 i;

    sMenuSpriteHeight = 0;
    if (itemCount > ARRAY_COUNT(sMenuItems)) {
        _uvDebugPrintf("kmenu_init : too may elements in the menu [%d]\n", itemCount);
    }
    menuUtilCreate(x, y, font, xscale, yscale, 0, itemCount);

    // clang-format off: needs to be on same line to match
    for (i = 0; i < ARRAY_COUNT(sMenuItems); i++) { sMenuItems[i] = NULL; }
    // clang-format on

    gFcnDrawMenuItem = &menuDrawItem;
}

// menuCreateVarHeight is unused, but serves as a wrapper for menuCreate
// it computes non-zero sMenuSpriteHeight, triggering different code paths below
void menuCreateVarHeight(s32 x, s32 y, s32 font, f32 xscale, f32 yscale, s32* items, s32 count) {
    s32 i;

    menuCreate(x, y, font, xscale, yscale, count);
    sMenuCountVarHeight = (s16)count;
    sMenuSpriteIdBase = 0xF;

    for (i = 0; i < count; i++) {
        // clang-format off
        uvSprtProps(sMenuSpriteIdBase + i,
            SPRT_PROP_ENABLED(TRUE),
            SPRT_PROP_POS(x, ((sMenuSpriteHeight + 6) * i) + y),
            SPRT_PROP_BLIT(items[i]),
            SPRT_PROP_END
        );
        // clang-format on
        sMenuSpriteHeight = uvSprtGetHeight(sMenuSpriteIdBase + i);
    }
}

void menuCreateItems(s32 x, s32 y, s32 font, f32 xscale, f32 yscale, s32* items, s32 itemCount) {
    s32 temp_v0;
    s32 i;

    menuCreate(x, y, font, xscale, yscale, itemCount);

    for (i = 0; i < itemCount; i++) {
        sMenuItems[i] = textGetDataByIdx(items[i]);
    }
}

s32 menuCheckInputs(void) {
    return menuUtilCheckInputs();
}

void menuRender(void) {
    menuUtilRender();
}

void menuDeinit(void) {
    s32 i;

    menuUtilDeinit();
    for (i = 0; i < sMenuCountVarHeight; i++) {
        uvSprtProps(sMenuSpriteIdBase + i, SPRT_PROP_ENABLED(FALSE), SPRT_PROP_END);
    }
}

STATIC_FUNC void menuDrawItem(s16 x, s16 y, s16 idx) {
    if (sMenuSpriteHeight != 0) {
        uvSprtProps(sMenuSpriteIdBase + idx, SPRT_PROP_POS(x, y + sMenuSpriteHeight + 2), SPRT_PROP_END);
        uvSprtDraw(sMenuSpriteIdBase + idx);
    } else {
        uvFontPrintStr16(x, y, sMenuItems[idx], 100, 0xFFE);
    }
}

s32 menu_8030B668(void) {
    return menuUtilGetCurItem();
}

void menuSetItem(s32 idx, s16* str) {
    sMenuItems[idx] = str;
}

void menu_8030B69C(s32 arg0) {
    menuUtilSetCurItem(arg0);
}
