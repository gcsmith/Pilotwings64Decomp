#include <macros.h>
#include <uv_font.h>
#include <uv_geometry.h>
#include <uv_graphics.h>
#include <uv_memory.h>
#include <uv_sprite.h>
#include <uv_texture.h>
#include "code_94E60.h"
#include "code_9A960.h"
#include "code_B2900.h"
#include "code_D2B10.h"
#include "credits.h"
#include "file_menu.h"
#include "menu.h"
#include "menu_utils.h"
#include "save.h"
#include "text_data.h"

// forward declarations
STATIC_FUNC s32 fileMenuPrintText(s32*, s32);

// file select menu item ids
static s32 sFileMenuTextIds[] = {
    0x00BD, // File 1
    0x0051, // File 2
    0x0054  // Erase File
};
static s32 sFileMenuConfirm[] = {
    0x0126, // No
    0x0086  // Yes
};
static s32 sFileMenuCurMenu = 0;
static s32 sFileMenu_8034F0F8 = 0;
static Vec3F sFileMenu_8034F0FC[2] = {
    {     -68.08f, -302.14f, 10.74f }, // position
    { -0.0174533f,     0.1f,   0.0f }  // rotation,  almost -DEG_TO_RAD(1)
};

static u8 sFileMenu_803624E0[3];
static u8 sFileMenu_803624E3;
static f32 sFileColorR1;
static f32 sFileColorR2;
static f32 sFileColorG1;
static f32 sFileColorG2;
static f32 sFileColorB1;
static f32 sFileColorB2;

s32 fileMenuTopRender(void) {
    s32 gameState;

    fileMenu_802E94E0();
    uvGfxBegin();
    fileMenu_802E9AE0();
    uvGfxEnd();
    do {
        uvGfxBegin();
        fileMenu_802E9AE0();
        uvGfxEnd();
        gameState = fileMenuSubRender();
    } while (gameState == -1);
    fileMenuSetProps();
    return gameState;
}

void fileMenu_802E8AF0(void) {
    s32 texId;
    Unk80364210* temp_s6;
    s32 tmp;
    s32 temp_s2;
    s32 temp_s5;
    s32 temp_s7;
    s32 k;
    s32 temp_v0;
    s32 i; // var_s0;
    u8 var_s1_3;
    s32 j;

    // clang-format off
    for (i = 0; i < 12; i++) {
        uvSprtProps(i,
            SPRT_PROP_3(1),
            SPRT_PROP_DIM(38, 22),
            SPRT_PROP_POS(((i % 3) * 40) + 93, 123 - ((i / 3) * 25)),
            SPRT_PROP_COLOR(0xFF, 0xFF, 0xFF, 0xFF),
            SPRT_PROP_TEX_ID(0x148),
            SPRT_PROP_END
        );
    }
    for (i = 0; i < 3; i++) {
        uvSprtProps(i + 12,
            SPRT_PROP_3(1),
            SPRT_PROP_DIM(38, 22),
            SPRT_PROP_POS(229, 98 - (25 * i)),
            SPRT_PROP_COLOR(0xFF, 0xFF, 0xFF, 0xFF),
            SPRT_PROP_TEX_ID(0x148),
            SPRT_PROP_END
        );
    }
    // clang-format on

    temp_s6 = &D_80364210[D_80362690->unk9C];
    for (j = 0; j < 3; j++) {
        for (k = 0; k < 4; k++) {
            temp_s2 = levelGetTotalPoints(temp_s6, k, j);
            temp_v0 = func_8032BE8C(temp_s6, k, j);
            if ((temp_s2 >= gMedalPointRequirements[k].gold) && (temp_v0 != 0)) {
                texId = 0x14B; // gold medal sprite
            } else if ((temp_s2 >= gMedalPointRequirements[k].silver) && (temp_v0 != 0)) {
                texId = 0x14A; // silver medal sprite
            } else if ((temp_s2 >= gMedalPointRequirements[k].bronze) && (temp_v0 != 0)) {
                texId = 0x149; // bronze medal sprite
            } else {
                texId = 0x148; // no medal sprite
            }
            uvSprtProps(k * 3 + j, SPRT_PROP_TEX_ID(texId), SPRT_PROP_END);
        }
    }

    for (i = 0; i < 3; i++) {
        temp_s2 = levelGetTotalPoints(temp_s6, i + 1, 0);
        temp_s5 = levelGetTotalPoints(temp_s6, i + 1, 1);
        temp_s7 = levelGetTotalPoints(temp_s6, i + 1, 2);
        // clang-format off
        uvSprtProps(i + 0xC,
            SPRT_PROP_3(1),
            SPRT_PROP_TEX_ID(0x148),
            SPRT_PROP_END
        );
        // clang-format on
        if (func_8032BE8C(temp_s6, i + 1, 0) && func_8032BE8C(temp_s6, i + 1, 1) && func_8032BE8C(temp_s6, i + 1, 2) &&
            temp_s2 >= gMedalPointRequirements[i + 1].silver && temp_s5 >= gMedalPointRequirements[i + 1].silver &&
            temp_s7 >= gMedalPointRequirements[i + 1].silver) {
            sFileMenu_803624E0[i] = 0;
        } else {
            sFileMenu_803624E0[i] = 1;
        }
    }

    sFileMenu_803624E3 = 0;
    var_s1_3 = 1;
    for (i = 0; i < 3; i++) {
        if (levelGetTotalPoints(temp_s6, 0, i) < gMedalPointRequirements[0].silver) {
            var_s1_3 = 0;
            break;
        }
    }
    sFileMenu_803624E3 = var_s1_3;
    if (!(var_s1_3 & 0xFF)) {
        for (i = 0; i < 3; i++) {
            if (sFileMenu_803624E0[i] == 0) {
                if ((levelGetTotalPoints(temp_s6, 0, i + 3) >= gMedalPointRequirements[i + 4].silver) &&
                    (levelGetTotalPoints(temp_s6, 1, i + 3) >= gMedalPointRequirements[i + 4].silver) &&
                    (levelGetTotalPoints(temp_s6, 2, i + 3) >= gMedalPointRequirements[i + 4].silver)) {
                    sFileMenu_803624E3 = 1;
                    break;
                }
            }
        }
    }
}

void fileMenu_802E8FF4(s32 arg0) {
    func_8032B3D0(&D_80364210[D_80362690->unk9C]);

    D_80362690->unkC[D_80362690->unk9C].unk8A = arg0;
    saveFileLoad(arg0);
    D_80362690->unkA8 = credits_8030CC48();
    fileMenu_802E8AF0();
}

void fileMenuSetup(s32 menu) {
    if (sFileMenuCurMenu != -1) {
        menuSetProps();
    }
    switch (menu) {
    case 0:
        menuCreateItems(fileMenuSetText(), 135, 6, 1.0f, 1.0f, sFileMenuTextIds, 3);
        sFileColorR1 = 44.0f;
        sFileColorG1 = 214.0f;
        sFileColorB1 = 44.0f;
        sFileColorR2 = 145.0f;
        sFileColorG2 = 183.0f;
        sFileColorB2 = 255.0f;
        break;
    case 1:
        menuCreateItems(fileMenuEraseFile(), 142, 6, 1.0f, 1.0f, sFileMenuTextIds, 2);
        sFileColorR1 = 255.0f;
        sFileColorG1 = 10.0f;
        sFileColorB1 = 10.0f;
        sFileColorR2 = 255.0f;
        sFileColorG2 = 108.0f;
        sFileColorB2 = 10.0f;
        break;
    case 2:
        menuCreateItems(fileMenuPrintText(sFileMenuConfirm, 2), 140, 6, 1.0f, 1.0f, sFileMenuConfirm, 2);
        sFileColorR1 = 255.0f;
        sFileColorG1 = 10.0f;
        sFileColorB1 = 10.0f;
        sFileColorR2 = 255.0f;
        sFileColorG2 = 108.0f;
        sFileColorB2 = 10.0f;
        break;
    }
    sFileMenuCurMenu = menu;
    menuUtilSetColors(MENU_COLOR_SELECTED, 0xD2, 0xD2, 0);
    menuUtilSetColors(MENU_COLOR_ITEM, 0xD2, 0xD2, 0xD2);
    menuUtilSetColors(MENU_COLOR_GRAPHICS, 0xD2, 0xD2, 0);
}

void fileMenuSetProps(void) {
    s32 i;

    for (i = 0; i < 15; i++) {
        uvSprtProps(i, SPRT_PROP_3(0), SPRT_PROP_END);
    }
    menuSetProps();
}

STATIC_FUNC s32 fileMenuPrintText(s32* textIds, s32 arg1) {
    s32 curVal;
    s32 i;
    s32 maxVal;

    maxVal = 0;
    uvFontSet(6);
    uvFontScale(1.0, 1.0);
    for (i = 0; i < arg1; i++) {
        curVal = uvFontStr16Width(textGetDataByIdx(textIds[i])) - 16;
        if (curVal > maxVal) {
            maxVal = curVal;
        }
    }
    return 144 - (maxVal / 2);
}

s32 fileMenuSetText(void) {
    if (!saveFileHasData(0)) {
        sFileMenuTextIds[0] = 0x17D; // File 1 ... New
    } else {
        saveFileLoad(0);
        if (func_8032C27C() != 0) {
            sFileMenuTextIds[0] = 0x8B; // File 1 ... Perfect
        } else {
            sFileMenuTextIds[0] = 0x116; // File 1 ... Continue
        }
    }

    if (!saveFileHasData(1)) {
        sFileMenuTextIds[1] = 0x181; // File 2 ... New
    } else {
        saveFileLoad(1);
        if (func_8032C27C() != 0) {
            sFileMenuTextIds[1] = 0x8E; // File 2 ... Perfect
        } else {
            sFileMenuTextIds[1] = 0x117; // File 2 ... Continue
        }
    }

    return fileMenuPrintText(sFileMenuTextIds, 3);
}

s32 fileMenuEraseFile(void) {
    fileMenuSetText();
    return fileMenuPrintText(sFileMenuTextIds, 2);
}

void fileMenu_802E94E0(void) {
    Camera* unk70;

    unk70 = D_80362690->unkC[D_80362690->unk9C].unk70;
    uvLevelInit();
    uvLevelAppend(0x48);
    uvLevelAppend(1);
    uvLevelAppend(0x72);
    textLoadBlock(0x42);
    // clang-format off
    uvSprtProps(0x10,
        SPRT_PROP_3(1),
        SPRT_PROP_BLIT(BLIT_ID_49),
        SPRT_PROP_END
    );
    uvSprtProps(0x10, SPRT_PROP_POS(42, uvSprtGetHeight(0x10) + 23), SPRT_PROP_END);
    uvSprtProps(0x11,
        SPRT_PROP_3(1),
        SPRT_PROP_BLIT(BLIT_ID_4A),
        SPRT_PROP_END
    );
    uvSprtProps(0x11, SPRT_PROP_POS(226, uvSprtGetHeight(0x11) + 23), SPRT_PROP_END);
    uvSprtProps(0x12,
        SPRT_PROP_3(1),
        SPRT_PROP_BLIT(BLIT_ID_4B),
        SPRT_PROP_END
    );
    uvSprtProps(0x12, SPRT_PROP_POS(226, uvSprtGetHeight(0x12) + 127), SPRT_PROP_END);
    // clang-format on
    fileMenu_802E8AF0();
    sFileMenuCurMenu = -1;
    fileMenuSetup(0);

    menu_8030B69C(D_80362690->unkC[D_80362690->unk9C].unk8A);
    fileMenu_802E8FF4(D_80362690->unkC[D_80362690->unk9C].unk8A);
    func_80204BD4(unk70->unk22C, 1, 1.0f);
    func_80204A8C(unk70->unk22C, 3);
    uvChanTerra(unk70->unk22C, 0);
    func_80204C94(unk70->unk22C, -0.4906542f, 0.4906542f, -0.35f, 0.35f, 1.0f, 2000.0f);
    uvChanEnv(unk70->unk22C, 2);
    func_80204AB0(unk70->unk22C, 0, 0);
    func_80204AB0(unk70->unk22C, 1, 0);
    func_80313640(sFileMenu_8034F0FC[0].x, sFileMenu_8034F0FC[0].y, sFileMenu_8034F0FC[0].z, sFileMenu_8034F0FC[1].x, sFileMenu_8034F0FC[1].y,
                  sFileMenu_8034F0FC[1].z, &unk70->unk108);
    func_80204B34(unk70->unk22C, &unk70->unk108);
    menuUtilSetColors(MENU_COLOR_SELECTED, 0xD2, 0xD2, 0);
    menuUtilSetColors(MENU_COLOR_ITEM, 0xD2, 0xD2, 0xD2);
    menuUtilSetColors(MENU_COLOR_GRAPHICS, 0xD2, 0xD2, 0);
    D_8034F7C0 = 1;
}

s32 fileMenuChoose(void) {
    s32 menuChoice;
    s32 ret;

    ret = -1;
    menuChoice = menuCheckInputs();
    switch (menuChoice) {
    case 0:
    case 1:
        ret = GAME_STATE_VEHICLE_CLASS_SELECT;
        break;
    case 2:
        fileMenuSetup(1);
        menu_8030B69C(0);
        fileMenu_802E8FF4(0);
        break;
    case -1:
        ret = GAME_STATE_TITLE;
        break;
    case -3:
        menuChoice = menu_8030B668();
        if ((menuChoice == 0) || (menuChoice == 1)) {
            fileMenu_802E8FF4(menuChoice);
        } else {
            func_8032B3D0(&D_80364210[D_80362690->unk9C]);
            fileMenu_802E8AF0();
        }
        break;
    }
    return ret;
}

s32 fileMenu_802E9890(void) {
    s32 menuChoice;

    menuChoice = menuCheckInputs();
    switch (menuChoice) {
    case 0:
    case 1:
        sFileMenu_8034F0F8 = menuChoice;
        fileMenuSetup(2);
        break;
    case -1:
        fileMenuSetup(0);
        menu_8030B69C(0);
        fileMenu_802E8FF4(0);
        break;
    case -3:
        menuChoice = menu_8030B668();
        switch (menuChoice) {
        case 0:
        case 1:
            fileMenu_802E8FF4(menuChoice);
            break;
        default:
            func_8032B3D0(&D_80364210[D_80362690->unk9C]);
            fileMenu_802E8AF0();
            break;
        }
    }
    return -1;
}

s32 fileMenu_802E9980(void) {
    s32 menuChoice;

    menuChoice = menuCheckInputs();
    switch (menuChoice) {
    case -1:
    case 0:
        fileMenuSetup(0);
        menu_8030B69C(0);
        fileMenu_802E8FF4(0);
        break;
    case 1:
        saveFile_802E89D4(sFileMenu_8034F0F8);
        fileMenuSetup(0);
        menu_8030B69C(sFileMenu_8034F0F8);
        fileMenu_802E8FF4(sFileMenu_8034F0F8);
        break;
    }
    return -1;
}

// renders one of three menus
s32 fileMenuSubRender(void) {
    s32 ret;

    ret = -1;
    switch (sFileMenuCurMenu) {
    case 0:
        ret = fileMenuChoose();
        break;
    case 1:
        ret = fileMenu_802E9890();
        break;
    case 2:
        ret = fileMenu_802E9980();
        break;
    }
    return ret;
}

// interpolates between 3 pairs of values over interval `v`
// used to cycle through colors in header of file select
void fileMenuColorLerp(f32 v, f32 x1, f32 y1, f32 z1, f32 x2, f32 y2, f32 z2, f32* xout, f32* yout, f32* zout) {
    *xout = ((x2 - x1) * v) + x1;
    *yout = ((y2 - y1) * v) + y1;
    *zout = ((z2 - z1) * v) + z1;
}

void fileMenu_802E9AE0(void) {
    static f32 sFileMenuFadeTime = 0.0f; // current time for text color fading
    static f32 sFileMenuFadeRate = 1.6f; // rate at which text fades
    s32 i;
    s32 pad;
    f32 r;
    f32 g;
    f32 b;
    s16* titleStr;
    Camera* unk70;

    unk70 = D_80362690->unkC[D_80362690->unk9C].unk70;
    func_80204FC4(unk70->unk22C);
    func_80314154();
    uvGfxSetFlags(GFX_STATE_400000);
    uvVtxBeginPoly();
    uvVtx(0, SCREEN_HEIGHT, 0, 0, 0, 0x00, 0x00, 0x00, 0x64);
    uvVtx(0, 0, 0, 0, 0, 0x00, 0x00, 0x00, 0x64);
    uvVtx(SCREEN_WIDTH, 0, 0, 0, 0, 0x00, 0x00, 0x00, 0x64);
    uvVtx(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 0, 0x00, 0x00, 0x00, 0x64);
    uvVtxEndPoly();
    uvGfxClearFlags(GFX_STATE_400000);
    func_803141E4();
    uvSprtDraw(0x10);
    uvSprtDraw(0x11);
    if (sFileMenu_803624E3 != 0) {
        uvSprtDraw(0x12);
    }

    for (i = 0; i < 12; i++) {
        uvSprtDraw(i);
    }
    for (i = 0; i < 3; i++) {
        if (sFileMenu_803624E0[i] != 0) {
            uvSprtDraw(i + 0xC);
        }
    }

    menuRender();
    uvFontSet(6);
    uvFontScale(1.0, 1.0);

    sFileMenuFadeTime += sFileMenuFadeRate * uvGfxGetUnkStateF();

    if (sFileMenuFadeTime > 1.0f) {
        sFileMenuFadeTime = 1.0f;
        sFileMenuFadeRate = -sFileMenuFadeRate;
    } else if (sFileMenuFadeTime < 0.0f) {
        sFileMenuFadeTime = 0.0f;
        sFileMenuFadeRate = -sFileMenuFadeRate;
    }

    fileMenuColorLerp(sFileMenuFadeTime, sFileColorR1, sFileColorG1, sFileColorB1, sFileColorR2, sFileColorG2, sFileColorB2, &r, &g, &b);
    uvFontColor(r, g, b, 0xFF);
    switch (sFileMenuCurMenu) {
    case 0:
        titleStr = textGetDataByIdx(0x23); // SELECT FILE
        break;
    case 1:
        titleStr = textGetDataByIdx(0xBA); // Which file will be erased?
        break;
    case 2:
        titleStr = textGetDataByIdx(0x101); // Are you sure?
        break;
    }
    uvFontPrintStr16((SCREEN_WIDTH / 2) - (uvFontStr16Width(titleStr) / 2), 206, titleStr, 0x3C, 0xFFE);
    uvFontGenDlist();
    func_8034B6F8();
}
