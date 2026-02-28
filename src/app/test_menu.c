#include "common.h"
#include <uv_controller.h>
#include <uv_font.h>
#include <uv_geometry.h>
#include <uv_graphics.h>
#include <uv_level.h>
#include <uv_sprite.h>
#include <uv_string.h>
#include "code_52230.h"
#include "code_64070.h"
#include "code_66160.h"
#include "code_6ACE0.h"
#include "code_72B70.h"
#include "code_905C0.h"
#include "code_9A960.h"
#include "code_B2900.h"
#include "credits.h"
#include "demo.h"
#include "hud.h"
#include "map3d.h"
#include "results.h"
#include "rings.h"
#include "snap.h"
#include "snd.h"
#include "test_menu.h"
#include "text_data.h"

static f32 sSelMenuScreenX;
static f32 sSelMenuScreenY;
static s32 sStickDirX;
static s32 sStickDirY;
static s32 sStickIsHeld;
static s32 sMenuMinY;
static s32 sMenuMinX;
static s32 sMenuMaxY;
static s32 sMenuMaxX;
s32 D_8037DC84; // global, but not used in this file
static char sTestNumPtsStr[4];
static u16 sWidthNumPts;
static s16 sTestPtsX;
static s16* sTestNameText;
static s16* sTestHintText;
static char sTestNumStr[3];
static u8 sDrawTestPts;

static s32 D_80350970 = 3; // unused
static s32 sTestMenuState = 0;
static s8 sMenuCurX = 0;
static s8 sMenuCurY = 0;
static s8 D_80350980 = 0xFF; // unused
static u8 D_80350984 = 0xFF; // unused, only ever set to 0xFF
const char* gClassShortNames[4] = { "E", "A", "B", "P" };
const char* gVehShortNames[7] = { "HG", "RP", "GC", "EX", "EX", "EX", "BD" };
s32 gCurTestIdx = 0;
static s32 D_803509B8 = 0; // unused, only ever set to 0

// forward declarations
void testMenu_8034A428(void);

// returns true if test is one of the Shutter Bug tests
s32 testMenuShutterBug(void) {
    Unk80362690_Unk0_UnkC* unkC;

    unkC = &D_80362690->unk0[D_80362690->unk9C].unkC;
    if ((unkC->veh == VEHICLE_HANG_GLIDER) && (((unkC->cls == CLASS_A) && (gCurTestIdx == 0)) || ((unkC->cls == CLASS_B) && (gCurTestIdx == 1)) ||
                                               ((unkC->cls == CLASS_PILOT) && (gCurTestIdx == 2)))) {
        return TRUE;
    }
    return FALSE;
}

void testMenuInitText(s32 testIdx) {
    Unk80362690_Unk0_UnkC* unkC;
    s32 ptsWidth;
    s32 pts;
    s32 test;
    s32 numPts;
    s32 ptsAdded;
    char nameStr[20];
    char hintStr[20];

    ptsAdded = FALSE;
    unkC = &D_80362690->unk0[D_80362690->unk9C].unkC;
    if (unkC->veh <= VEHICLE_GYROCOPTER) {
        numPts = testGetPointCount(&D_80364210[D_80362690->unk9C], unkC->cls, testIdx, unkC->veh);
    } else {
        numPts = 0;
        if (unkC->veh >= VEHICLE_SKY_DIVING) {
            numPts = testGetPointCount(&D_80364210[D_80362690->unk9C], testIdx, 0, unkC->veh);
        } else {
            numPts = 0;
            for (test = 0; test < levelGetTestCount(unkC->cls, unkC->veh); test++) {
                pts = testGetPointCount(&D_80364210[D_80362690->unk9C], unkC->cls, test, unkC->veh);
                if (pts != 0x7F) {
                    numPts += pts;
                    ptsAdded = TRUE;
                }
            }
            if (!ptsAdded) {
                numPts = 0x7F;
            }
        }
    }

    if (numPts != 0x7F) {
        uvFontSet(3);
        uvFont_80219550(1.0, 1.0);
        uvSprintf(sTestNumPtsStr, "%d", numPts);
        sWidthNumPts = uvFontWidth(sTestNumPtsStr);
        uvFont_80219550(0.699999988079071045, 1.0);
        ptsWidth = uvFontWidth("PTS");
        sTestPtsX = 258 - (ptsWidth + sWidthNumPts) / 2;
        sDrawTestPts = TRUE;
    } else {
        sDrawTestPts = FALSE;
    }

    if ((unkC->veh == VEHICLE_BIRDMAN) || (unkC->veh <= VEHICLE_GYROCOPTER)) {
        uvSprintf(nameStr, "%s_%s_%d_N", gClassShortNames[unkC->cls], gVehShortNames[unkC->veh], testIdx + 1);
        uvSprintf(hintStr, "%s_%s_%d_H", gClassShortNames[unkC->cls], gVehShortNames[unkC->veh], testIdx + 1);
    } else {
        uvSprintf(nameStr, "%s_%s_%d_N", gClassShortNames[unkC->veh - 2], gVehShortNames[unkC->veh], testIdx + 1);
        uvSprintf(hintStr, "%s_%s_%d_H", gClassShortNames[unkC->veh - 2], gVehShortNames[unkC->veh], testIdx + 1);
    }
    sTestNameText = textGetDataByName(nameStr);
    sTestHintText = textGetDataByName(hintStr);
    if ((unkC->veh <= VEHICLE_GYROCOPTER) || (unkC->veh == VEHICLE_BIRDMAN)) {
        uvSprintf(sTestNumStr, "%d", testIdx + 1);
    } else {
        uvSprintf(sTestNumStr, "%d", 1);
    }
}

void testMenuInit(Unk80367710* arg0, s32 arg1) {
    Unk80362690_Unk0_UnkC* temp_v1;

    temp_v1 = &D_80362690->unk0[D_80362690->unk9C].unkC;
    if (arg1 != 2) {
        uvLevelInit();
        uvLevelAppend((s32)D_8034F43C[D_8034F420[temp_v1->veh][temp_v1->cls]]);
        uvLevelAppend(0xB);
        uvLevelAppend(0x5B);
        uvLevelAppend(0x87);
        uvLevelAppend(0x53);
        textLoadBlock(0x42);
    }

    D_803509B8 = 0;
    if (arg1 == 0) {
        if (D_80362690->unkA3 == 0) {
            gCurTestIdx = 0;
            D_80362690->unkA3 = 1;
        } else {
            gCurTestIdx++;
            if (gCurTestIdx >= arg0->testCount) {
                gCurTestIdx = 0;
            }
        }
        if ((temp_v1->veh != VEHICLE_BIRDMAN) && (temp_v1->veh >= VEHICLE_CANNONBALL)) {
            gCurTestIdx = temp_v1->cls;
        }
        if ((temp_v1->veh != VEHICLE_BIRDMAN) && (temp_v1->veh >= VEHICLE_CANNONBALL)) {
            temp_v1->cls = gCurTestIdx;
            temp_v1->test = 0;
        } else {
            temp_v1->test = gCurTestIdx;
        }
    }
    level_80344FC8(temp_v1->cls, temp_v1->veh, temp_v1->test, &D_80362690->unk0[0].map, &D_80362690->unk0[0].unk6, &D_80362690->unk0[0].unk8);
    map3d(D_80362690, 0);
    if (arg1 == 0) {
        sTestMenuState = 0;
    }
    uvSprtProps(0, 3, 1, 1, 0x40, 0x12, 9, 0xF, 7, 0xFF, 0xFF, 0xFF, 0xFF, 2, 0x32, 0x2E, 0);
    uvSprtProps(1, 3, 1, 1, 0x40, 0x12, 2, 0x32, 0x47, 7, 0xFF, 0xFF, 0xFF, 0xFF, 9, 0xE, 0);
    uvSprtProps(2, 3, 1, 1, 0x40, 0x12, 2, 0x80, 0x2E, 7, 0xFF, 0xFF, 0xFF, 0xFF, 9, 0x11, 0);
    uvSprtProps(3, 3, 1, 1, 0x40, 0x12, 2, 0x80, 0x47, 7, 0xFF, 0xFF, 0xFF, 0xFF, 9, 0x10, 0);
    uvSprtProps(4, 3, 1, 1, 0x40, 0x12, 7, 0xFF, 0xFF, 0xFF, 0xFF, 2, 0xCE, 0x2E, 9, 0x13, 0);
    uvSprtProps(5, 3, 1, 1, 0x40, 0x12, 2, 0xCE, 0x47, 7, 0xFF, 0xFF, 0xFF, 0xFF, 9, 0x12, 0);
    uvSprtProps(6, 3, 1, 2, 0x2B, 0xD4, 7, 0xFF, 0xFF, 0xFF, 0xFF, 9, 0x15, 0);
    uvSprtProps(7, 3, 1, 2, 0xEF, 0xD7, 7, 0xFF, 0xFF, 0xFF, 0xFF, 9, 0xD, 0);
    uvSprtProps(8, 3, 1, 1, 0x40, 0x12, 2, 0xCE, 0x47, 7, 0xFF, 0xFF, 0xFF, 0xFF, 9, 0x14, 0);
    uvSprtProps(9, 3, 1, 1, 0x40, 0x12, 2, 0x80, 0x47, 7, 0xFF, 0xFF, 0xFF, 0xFF, 9, 0x3C, 0);
    if (arg1 == 0) {
        sMenuCurX = 0;
        sMenuCurY = 1;
        sSelMenuScreenX = (sMenuCurX * 78) + 47;
        sSelMenuScreenY = (sMenuCurY * 25) + 26;
        sStickDirX = sStickDirY = 0;
        D_80350984 = 0xFF;
    }
    sDrawTestPts = FALSE;
    testMenuInitText(gCurTestIdx);
}

u8 testMenuHandler(Unk80367710* arg0) {
    Unk80362690_Unk0_UnkC* sp6C;
    s32 testIdxAdj;
    u32 sp64;
    s32 menuPrevX;
    s32 menuPrevY;
    f32 stickX;
    f32 stickY;
    Vec3F sp48; // passed to db_getstart, but result not used
    s32 var_a2;

    sp6C = &D_80362690->unk0[D_80362690->unk9C].unkC;
    testIdxAdj = 0;
    if (sTestMenuState == 1) {
        func_80311660(D_80362690->unk9C, 0);
        if (demoButtonPress(D_80362690->unk9C, A_BUTTON | B_BUTTON | START_BUTTON) != 0) {
            sTestMenuState = 0;
            if (demoButtonPress(D_80362690->unk9C, A_BUTTON | START_BUTTON) != 0) {
                snd_play_sfx(0x71);
            } else if (demoButtonPress(D_80362690->unk9C, B_BUTTON) != 0) {
                snd_play_sfx(1);
            }
            return 6;
        }
    } else {
        demo_80323020();
        if (sTestMenuState == 2) {
            if ((sp6C->cls == CLASS_BEGINNER) && (sp6C->veh <= VEHICLE_GYROCOPTER)) {
                sMenuMinX = 1;
                sMenuMaxX = 2;
            } else {
                sMenuMinX = 2;
                sMenuMaxX = 2;
            }
            sMenuMinY = 1;
            sMenuMaxY = 1;
        } else {
            sMenuMinY = 0;
            sMenuMaxY = 1;
            sMenuMinX = 0;
            sMenuMaxX = 2;
        }
        stickX = demoGetInputs(D_80362690->unk9C, INPUT_AXIS_X);
        stickY = demoGetInputs(D_80362690->unk9C, INPUT_AXIS_Y);
        sStickDirX = sStickDirY = 0;

        if (ABS_NOEQ(stickX) < 0.75f && ABS_NOEQ(stickY) < 0.75f) {
            sStickIsHeld = FALSE;
        } else if (!sStickIsHeld) {
            if (stickX > 0.75f) {
                sStickDirX = 1;
                sStickIsHeld = TRUE;
            }
            if (stickX < -0.75f) {
                sStickDirX = -1;
                sStickIsHeld = TRUE;
            }
            if (stickY > 0.75f) {
                sStickDirY = 1;
                sStickIsHeld = TRUE;
            }
            if (stickY < -0.75f) {
                sStickDirY = -1;
                sStickIsHeld = TRUE;
            }
        }

        menuPrevX = sMenuCurX;
        menuPrevY = sMenuCurY;
        sMenuCurX += sStickDirX;
        sMenuCurY += sStickDirY;

        if (sMenuCurX < sMenuMinX) {
            sMenuCurX = sMenuMinX;
        } else if (sMenuMaxX < sMenuCurX) {
            sMenuCurX = sMenuMaxX;
        }

        if (sMenuCurY < sMenuMinY) {
            sMenuCurY = sMenuMinY;
        } else if (sMenuMaxY < sMenuCurY) {
            sMenuCurY = sMenuMaxY;
        }

        if ((sTestMenuState != 2) && (sMenuCurX == 2) && (sMenuCurY == 0)) {
            if (!testMenuShutterBug()) {
                sMenuCurX = menuPrevX;
                sMenuCurY = menuPrevY;
            }
        }

        if ((menuPrevX != sMenuCurX) || (menuPrevY != sMenuCurY)) {
            func_8033F758(0, 1.0f, 1.03f, 0.0f);
        }
        sSelMenuScreenX = (sMenuCurX * 78) + 47;
        sSelMenuScreenY = (sMenuCurY * 25) + 26;
        sp64 = (sMenuCurX - sMenuMinX) + ((sMenuCurY - sMenuMinY) * ((sMenuMaxX - sMenuMinX) + 1));
        if (sTestMenuState != 2) {
            if (demoButtonPress(D_80362690->unk9C, R_CBUTTONS) != 0) {
                testIdxAdj = 1;
            } else if (demoButtonPress(D_80362690->unk9C, L_CBUTTONS) != 0) {
                testIdxAdj = -1;
            }

            if ((sp6C->veh != VEHICLE_BIRDMAN) && (sp6C->veh >= VEHICLE_CANNONBALL)) {
                testIdxAdj = 0;
            }
            if (testIdxAdj != 0) {
                var_a2 = gCurTestIdx;
                sMenuCurX = sMenuMinX;
                sMenuCurY = sMenuMaxY;
                sSelMenuScreenX = (sMenuCurX * 78) + 47;
                sSelMenuScreenY = (sMenuCurY * 25) + 26;
                sp64 = (sMenuCurX - sMenuMinX) + ((sMenuCurY - sMenuMinY) * ((sMenuMaxX - sMenuMinX) + 1));

                if ((sp6C->veh != VEHICLE_BIRDMAN) && (sp6C->veh >= VEHICLE_CANNONBALL)) {
                    if (gCurTestIdx == arg0->testCount - 1) {
                        gCurTestIdx = 0;
                    } else {
                        gCurTestIdx++;
                    }
                } else {
                    gCurTestIdx += testIdxAdj;
                    if (gCurTestIdx >= arg0->testCount) {
                        gCurTestIdx = 0;
                    }
                    if ((s16)gCurTestIdx < 0) { // TODO: cast is needed, why?
                        gCurTestIdx = arg0->testCount - 1;
                    }
                }
                if (gCurTestIdx != var_a2) {
                    func_8033F758(0x6A, 1.0f, 0.5f, 0.0f);
                    func_803122B4(D_80362690, 0);
                    if ((sp6C->veh != VEHICLE_BIRDMAN) && (sp6C->veh >= VEHICLE_CANNONBALL)) {
                        sp6C->cls = gCurTestIdx;
                        sp6C->test = 0;
                    } else {
                        sp6C->test = gCurTestIdx;
                    }
                    level_80344FC8(sp6C->cls, sp6C->veh, sp6C->test, &D_80362690->unk0[0].map, &D_80362690->unk0[0].unk6, &D_80362690->unk0[0].unk8);
                    map3d(D_80362690, 0);
                    testMenuInitText(sp6C->test);
                }
            }
        }

        if (demoButtonPress(D_80362690->unk9C, A_BUTTON | START_BUTTON) != 0) {
            if (sTestMenuState == 2) {
                if ((sp6C->cls == CLASS_BEGINNER) && (sp6C->veh <= VEHICLE_GYROCOPTER)) {
                    switch (sp64) {
                    case 0:
                        func_8033F758(0x72, 1.0f, 1.22f, 0.0f);
                        return 0xFE;
                    case 1:
                        func_8033F758(0x72, 1.0f, 1.22f, 0.0f);
                        sTestMenuState = 0;
                        break;
                    }
                } else {
                    if (sp64 == 0) {
                        func_8033F758(0x72, 1.0f, 1.22f, 0.0f);
                        sTestMenuState = 0;
                    }
                }
            } else {
                switch (sp64) {
                case 3:
                    snd_play_sfx(0xF);
                    return gCurTestIdx;
                case 0:
                    snd_play_sfx(0x73);
                    resultHandler(0);
                    break;
                case 4:
                    snd_play_sfx(0x71);
                    db_getstart(&sp6C->unk2C, &sp48, 0, 0);
                    testMenu_8034A428();
                    hud_8031A2CC();
                    D_80362690->unkA0 = 1;
                    func_803239B4();
                    func_80309A64();
                    func_802CB094();
                    func_802E3A5C();
                    func_802E3E6C();
                    func_80324A34();
                    func_80309FFC();
                    func_802CB35C();
                    D_80362690->unkA0 = 0;
                    func_8030FE80(D_80362690, 1);
                    testMenuInit(arg0, 2);
                    break;
                case 5:
                    func_8033F758(0x72, 1.0f, 1.22f, 0.0f);
                    sTestMenuState = 2;
                    break;
                case 2:
                    snd_play_sfx(0x6E);
                    func_8033FB14();
                    testMenu_8034A428();
                    func_8033E3A8(3);
                    testMenuInit(arg0, 1);
                    break;
                case 1:
                    func_8033F758(0x75, 1.0f, 0.8f, 0.0f);
                    testMenu_8034A428();
                    func_802DCB40();
                    testMenuInit(arg0, 2);
                    break;
                default:
                    break;
                }
            }
        } else {
            if (demoButtonPress(D_80362690->unk9C, B_BUTTON) != 0) {
                snd_play_sfx(1);
                if (sTestMenuState == 2) {
                    // these u8 values are needed to load integer literals at runtime
                    u16 col2ScreenX = (2 * 78) + 47;
                    u16 row1ScreenY = (1 * 25) + 26;
                    sTestMenuState = 0;
                    sMenuCurX = 2;
                    sMenuCurY = 1;
                    sSelMenuScreenX = col2ScreenX;
                    sSelMenuScreenY = row1ScreenY;
                } else {
                    return 0xFF;
                }
            }
        }
    }
    return 6;
}

void testMenuDraw(s32 arg0, u8 arg1, u8 arg2) {
    s32 pad1;
    s32 pad21;
    s32 var_s0;
    s32 idx;
    char* strIdAppend;
    u32 pad2;
    u32 strIdLen;
    s32 pad3;
    char sp8C[108];
    char strId[52];
    s16* sp54;
    s32 temp_a0;
    s32 temp_v0_3;
    Unk80362690_Unk0_UnkC* sp48;
    s32 var_a1;

    sp48 = &D_80362690->unk0[D_80362690->unk9C].unkC;
    if ((sp48->veh != VEHICLE_BIRDMAN) && (arg2 >= 3)) {
        level_80344E0C(arg1, 0, arg2, sp8C, strId);
    } else {
        level_80344E0C(arg1, gCurTestIdx, arg2, sp8C, strId);
    }
    strIdLen = uvStrlen(strId);
    if (strIdLen == 0) {
        uvSprintf(strId, "%s_%s_%d\n", gClassShortNames[sp48->cls], gVehShortNames[sp48->veh], gCurTestIdx + 1);
        strIdLen = uvStrlen(strId);
    }
    strIdAppend = &strId[strIdLen];
    strIdAppend[0] = '_';
    strIdAppend[1] = 'M';
    strIdAppend[2] = '\0';
    temp_a0 = arg0 + 264;
    func_8033F6F8(temp_a0, temp_a0);
    func_80311C68(D_80362690, 0);
    if (sTestMenuState != 1) {
        if (sTestMenuState != 2) {
            sp54 = textGetDataByName(strId);
        } else {
            sp54 = sTestHintText;
        }
        screenDrawBox2(38, 80, 244, 110, 2, 0, 0xA0, 0);
        screenDrawBox2(38, 195, 191, 25, 2, 0, 0xA0, 0);
        if (sp48->veh != VEHICLE_BIRDMAN) {
            screenDrawBox2(235, 195, 48, 25, 2, 0, 0xA0, 0);
        }
        func_80314154();

        if (sTestMenuState == 2) {
            if ((sp48->cls == CLASS_BEGINNER) && (sp48->veh <= VEHICLE_GYROCOPTER)) {
                uvSprtDraw(9);
            }
            uvSprtDraw(6);
            if (sp48->veh != VEHICLE_BIRDMAN) {
                uvSprtDraw(7);
            }
            uvSprtDraw(8);
        } else {
            for (var_s0 = 0; var_s0 < 8; var_s0++) {
                if ((var_s0 == 4) && (testMenuShutterBug() != 0)) {
                    uvSprtDraw(4);
                } else if ((var_s0 == 7) && (sp48->veh != VEHICLE_BIRDMAN)) {
                    uvSprtDraw(7);
                } else if ((var_s0 != 4) && (var_s0 != 7)) {
                    uvSprtDraw(var_s0);
                }
            }

            if (((sp48->veh == VEHICLE_BIRDMAN) || (sp48->veh <= VEHICLE_GYROCOPTER)) && (levelGetTestCount(sp48->cls, sp48->veh) >= 2)) {
                uvGfxStatePush();
                uvGfxSetFlags(GFX_STATE_800000);
                uvGfxClearFlags(GFX_STATE_400000 | GFX_STATE_200000);
                uvGfx_80223A28(0x11B);
                uvVtxBeginPoly();
                uvVtx(31, 142, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
                uvVtx(31, 127, 0, 0, 0x1E0, 0xFF, 0xFF, 0xFF, 0xFF);
                uvVtx(46, 127, 0, 0x1E0, 0x1E0, 0xFF, 0xFF, 0xFF, 0xFF);
                uvVtx(46, 142, 0, 0x1E0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
                uvVtxEndPoly();
                uvVtxBeginPoly();
                uvVtx(273, 142, 0, 0x1E0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
                uvVtx(273, 127, 0, 0x1E0, 0x1E0, 0xFF, 0xFF, 0xFF, 0xFF);
                uvVtx(288, 127, 0, 0, 0x1E0, 0xFF, 0xFF, 0xFF, 0xFF);
                uvVtx(288, 142, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
                uvVtxEndPoly();
                uvGfxStatePop();
            }
        }
        func_802DEE44((s32)((f64)sSelMenuScreenX + 0.5), (s32)((f64)sSelMenuScreenY + 0.5), 0x46, 0x18, 3, 0xC8, 0xC8, 0, 0x64, 0x64, 0);
        func_803141E4();
        uvFontSet(0);
        uvFont_80219550(1.0, 0.800000011920929);
        uvFont_8021956C(0xBE, 0xBE, 0xBE, 0xFF);
        uvFont_80219ACC(67, 200, sTestNumStr);
        if (sTestNameText != NULL) {
            uvFontSet(6);
            uvFont_8021956C(0xBE, 0xBE, 0xBE, 0xFF);
            uvFont_80219550(1.0, 1.0);
            func_80219874(79, 196, sTestNameText, 0xFF, 0xFFE);
        }
        if (sDrawTestPts && (sp48->veh != VEHICLE_BIRDMAN)) {
            uvFontSet(3);
            uvFont_8021956C(0xBE, 0xBE, 0xBE, 0xFF);
            uvFont_80219550(1.0, 1.0);
            uvFont_80219ACC((u16)sTestPtsX, 196, sTestNumPtsStr);
            uvFont_8021956C(0xAA, 0xAA, 0xAA, 0xFF);
            uvFont_80219550(0.699999988079071, 1.0);
            uvFont_80219ACC((u16)sTestPtsX + sWidthNumPts + 1, 196, "PTS");
        }
        if (sp54 != NULL) {
            uvFontSet(6);
            uvFont_8021956C(0xD2, 0xD2, 0xD2, 0xFF);
            uvFont_80219550(1.0, 1.0);
            idx = 0;
            for (var_a1 = 166; var_a1 > -114; var_a1 -= 14) {
                temp_v0_3 = func_80219874(46, var_a1, &sp54[idx], 0xFF, 0xFFE);
                if (temp_v0_3 == -1) {
                    break;
                }
                idx += temp_v0_3;
            }
        }
        uvFont_80219EA8();
    }
}

void testMenu_8034A428(void) {
    func_803122B4(D_80362690, 0);
}
