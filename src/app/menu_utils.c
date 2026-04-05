#include "common.h"
#include <uv_controller.h>
#include <uv_font.h>
#include <uv_geometry.h>
#include <uv_graphics.h>
#include "code_9A960.h"
#include "demo.h"
#include "game.h"
#include "menu_utils.h"
#include "snd.h"

static s32 sMenuItemCount;
static s32 sMenuFont;
static f32 sMenuScaleX;
static f32 sMenuScaleY;
static s32 sMenuPosX;
static s32 sMenuPosY;
void (*gFcnDrawMenuItem)(s16, s16, s16);
static char** sMenuItems;
static s32 sMenuCurSelect;
static s32 sMenuPrevSelect;
static s32 sMenuAdj;
static s32 sMenuStickCenter;
static u8 sMenuButtonMode;

// Color RGB for selected menu item
static u8 sMenuFontSelR;
static u8 sMenuFontSelG;
static u8 sMenuFontSelB;

// Color RGB for non-selected menu item
static u8 sMenuFontR;
static u8 sMenuFontG;
static u8 sMenuFontB;

// Color RGB for graphics
static u8 sMenuGfxR;
static u8 sMenuGfxG;
static u8 sMenuGfxB;

static u8 sMenuSoundFlags;

void menuUtilCreate(s32 x, s32 y, s32 font, f32 xScale, f32 yScale, char** menuItems, s32 itemCount) {
    sMenuPosX = x;
    sMenuPosY = y;
    sMenuItemCount = itemCount;
    sMenuFont = font;
    sMenuItems = menuItems;
    sMenuScaleX = xScale;
    sMenuScaleY = yScale;
    gFcnDrawMenuItem = NULL;
    sMenuAdj = sMenuStickCenter = 0;
    sMenuPrevSelect = sMenuCurSelect = 0;
    uvFontSet(font);
    uvFontScale(xScale, yScale);
    menuUtilSetColors(MENU_COLOR_SELECTED, 0xFF, 0xFF, 0x00);
    menuUtilSetColors(MENU_COLOR_ITEM, 0xFF, 0xFF, 0xFF);
    menuUtilSetColors(MENU_COLOR_GRAPHICS, 0xFF, 0xFF, 0x00);
    sMenuSoundFlags = MENU_SOUND_CHANGE | MENU_SOUND_BACK | MENU_SOUND_SELECT;
}

s32 menuUtilCheckInputs(void) {
    f32 stickY;
    s32 menuItemChanged;

    menuItemChanged = FALSE;
    demo_80323020();
    if (demoButtonPress(D_80362690->unk9C, (sMenuButtonMode == 1) ? START_BUTTON : B_BUTTON)) {
        if (sMenuSoundFlags & MENU_SOUND_BACK) {
            sndPlaySfx(SFX_UI_CANCEL);
            func_8033FB14();
        }
        return -1;
    }

    if (demoButtonPress(D_80362690->unk9C, (sMenuButtonMode == 1) ? A_BUTTON : START_BUTTON | A_BUTTON)) {
        if (sMenuSoundFlags & MENU_SOUND_SELECT) {
            sndPlaySfx(SFX_UI_CONFIRM);
            func_8033FB14();
        }
        return sMenuCurSelect;
    }

    stickY = demoGetInputs(D_80362690->unk9C, INPUT_AXIS_Y);
    sMenuAdj = 0;
    if (FABS(stickY) < 0.75f) {
        sMenuStickCenter = FALSE;
    } else if (!sMenuStickCenter) {
        if (stickY > 0.75f) {
            sMenuAdj = -1;
            sMenuStickCenter = TRUE;
        } else if (stickY < -0.75f) {
            sMenuAdj = 1;
            sMenuStickCenter = TRUE;
        }
    }

    sMenuCurSelect += sMenuAdj;
    if (sMenuCurSelect < 0) {
        sMenuCurSelect = sMenuItemCount - 1;
    }
    if (sMenuCurSelect >= sMenuItemCount) {
        sMenuCurSelect = 0;
    }
    if (sMenuCurSelect != sMenuPrevSelect) {
        sMenuPrevSelect = sMenuCurSelect;
        if (sMenuSoundFlags & MENU_SOUND_CHANGE) {
            func_8033F758(0, 1.0f, 1.03f, 0);
            func_8033FB14();
        }
        menuItemChanged = TRUE;
    }

    if (menuItemChanged) {
        return -3;
    } else {
        return -2;
    }
}

void menuUtilInit(void) {
    sMenuItems = NULL;
}

void menuUtilRender(void) {
    s32 temp_a3;
    s32 var_s1;
    s32 posY;
    s32 fontHeight;
    s32 i;
    s32 halfWidth;
    Mtx4F spA8;
    Mtx4F sp68;

    uvGfxSetViewport(0, 0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);
    uvMat4SetOrtho(&spA8, 0.0f, SCREEN_WIDTH - 1, 0.0f, SCREEN_HEIGHT - 1);
    uvGfxMtxProjPushF(&spA8);
    uvMat4SetIdentity(&sp68);
    uvGfxMtxViewLoad(&sp68, 1);
    uvFontSet(sMenuFont);
    uvFontScale(sMenuScaleX, sMenuScaleY);
    fontHeight = uvFontHeight();
    halfWidth = (s32)(uvFontWidth("A") * 0.5f);
    posY = ((sMenuItemCount - sMenuCurSelect) * (fontHeight + 1)) + sMenuPosY + 5;
    uvVtxBeginPoly();
    uvVtx(sMenuPosX, posY, 0, 0, 0, sMenuGfxR, sMenuGfxG, sMenuGfxB, 0xFF);
    uvVtx(sMenuPosX + halfWidth, posY + ((fontHeight - (4.0f * sMenuScaleY)) / 2), 0, 0, 0, sMenuGfxR, sMenuGfxG, sMenuGfxB, 0xFF);
    uvVtx(sMenuPosX, posY + (fontHeight - (4.0f * sMenuScaleY)), 0, 0, 0, sMenuGfxR, sMenuGfxG, sMenuGfxB, 0xFF);
    uvVtxEndPoly();
    uvGfxMtxViewPop();
    var_s1 = ((fontHeight + 1) * sMenuItemCount) + sMenuPosY;
    for (i = 0; i < sMenuItemCount; i++) {
        if (i == sMenuCurSelect) {
            uvFontColor(sMenuFontSelR, sMenuFontSelG, sMenuFontSelB, 0xFF);
        } else {
            uvFontColor(sMenuFontR, sMenuFontG, sMenuFontB, 0xFF);
        }
        temp_a3 = sMenuPosX + halfWidth + 3;
        if (gFcnDrawMenuItem != NULL) {
            gFcnDrawMenuItem(temp_a3, var_s1, i);
        } else {
            uvFontPrintStr(temp_a3, var_s1, sMenuItems[i]);
        }
        var_s1 -= fontHeight + 1;
    }
}

s32 menuUtilGetCurItem(void) {
    return sMenuCurSelect;
}

void menuUtilSetCurItem(s32 selection) {
    sMenuCurSelect = sMenuPrevSelect = selection;
}

void menuUtilSetColors(MenuColorSet colorSet, u8 r, u8 g, u8 b) {
    switch (colorSet) {
    case MENU_COLOR_SELECTED:
        sMenuFontSelR = r;
        sMenuFontSelG = g;
        sMenuFontSelB = b;
        break;
    case MENU_COLOR_ITEM:
        sMenuFontR = r;
        sMenuFontG = g;
        sMenuFontB = b;
        break;
    case MENU_COLOR_GRAPHICS:
        sMenuGfxR = r;
        sMenuGfxG = g;
        sMenuGfxB = b;
        break;
    }
}

void menuUtilSetSoundFlags(s32 soundFlags) {
    sMenuSoundFlags = soundFlags;
}

void menuUtilSetButtonMode(s32 buttonMode) {
    sMenuButtonMode = buttonMode;
}

// unused, sets menu font colors based on input and func_8031420C
void menuUtil_80313010(f32 arg0) {
    f32 sp2C;
    f32 sp28;
    f32 sp24;

    func_8031420C(arg0, 1.0f, 1.0f, &sp2C, &sp28, &sp24);
    menuUtilSetColors(MENU_COLOR_ITEM, 255.0f * sp2C, 255.0f * sp28, 255.0f * sp24);

    arg0 += 0.05f;
    if (arg0 > 1.0f) {
        arg0 -= 1.0f;
    }
    func_8031420C(arg0, 1.0f, 1.0f, &sp2C, &sp28, &sp24);
    menuUtilSetColors(MENU_COLOR_SELECTED, 255.0f * sp2C, 255.0f * sp28, 255.0f * sp24);
}
