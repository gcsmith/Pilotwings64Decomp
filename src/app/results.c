#include "common.h"
#include <uv_font.h>
#include <uv_geometry.h>
#include <uv_graphics.h>
#include <uv_level.h>
#include <uv_math.h>
#include <uv_string.h>
#include "code_99D40.h"
#include "code_9A960.h"
#include "code_B3A70.h"
#include "code_CE4F0.h"
#include "code_CFC40.h"
#include "demo.h"
#include "menu.h"
#include "save.h"
#include "snap.h"
#include "snow.h"
#include "snd.h"
#include "results.h"
#include "text_data.h"

static s16 sPtsTally0[8];
static s16 sPtsTally1[8];
static s16 sPtsTally2[8];
static s16 sPtsTally3[6]; // TODO: why only 0xC bytes?
static f32 sScreenFadeDuration;
static s16* sReplayTipText;
static u8 sTipTextMissing;
// pad 3
static const char* sTipTextId;
static s16* sPtsLabelStr;
static s16 sPtsDeductedStr[8];
static s16 sTotalPointsStr[5];
static u8 sVehTipIdx[3];

static const char* sResultTestNames2[6][4][3] = {
    {
     { "HG_E_S2", NULL, NULL },
     { "HG_A1_S2", "HG_A2_S2", NULL },
     { "HG_B1_S2", "HG_B2_S2", "HG_B3_S2" },
     { "HG_P1_S2", "HG_P2_S2", "HG_P3_S2" },
     },
    {
     { "RP_E_S2", NULL, NULL },
     { "RP_A1_S2", "RP_A2_S2", NULL },
     { "RP_B1_S2", "RP_B2_S2", "RP_B3_S2" },
     { "RP_P1_S2", "RP_P2_S2", "RP_P3_S2" },
     },
    {
     { "GC_E_S2", NULL, NULL },
     { "GC_A1_S2", "GC_A2_S2", NULL },
     { "GC_B1_S2", "GC_B2_S2", "GC_B3_S2" },
     { "GC_P1_S2", "GC_P2_S2", "GC_P3_S2" },
     },
    {
     { "CB_L123_S2", "CB_L123_S2", "CB_L123_S2" },
     { "CB_L123_S2", "CB_L123_S2", "CB_L123_S2" },
     { "CB_L123_S2", "CB_L123_S2", "CB_L123_S2" },
     { "CB_L123_S2", "CB_L123_S2", "CB_L123_S2" },
     },
    {
     { "SD_L123_S2", "SD_L123_S2", "SD_L123_S2" },
     { "SD_L123_S2", "SD_L123_S2", "SD_L123_S2" },
     { "SD_L123_S2", "SD_L123_S2", "SD_L123_S2" },
     { "SD_L123_S2", "SD_L123_S2", "SD_L123_S2" },
     },
    {
     { "HP_L123_S2", "HP_L123_S2", "HP_L123_S2" },
     { "HP_L123_S2", "HP_L123_S2", "HP_L123_S2" },
     { "HP_L123_S2", "HP_L123_S2", "HP_L123_S2" },
     { "HP_L123_S2", "HP_L123_S2", "HP_L123_S2" },
     },
};

static const char* sResultTestNames1[6][4][3] = {
    {
     { "HG_E_S1", NULL, NULL },
     { "HG_A1_S1", "HG_A2_S1", NULL },
     { "HG_B1_S1", "HG_B2_S1", "HG_B3_S1" },
     { "HG_P1_S1", "HG_P2_S1", "HG_P3_S1" },
     },
    {
     { "RP_E_S1", NULL, NULL },
     { "RP_A1_S1", "RP_A2_S1", NULL },
     { "RP_B1_S1", "RP_B2_S1", "RP_B3_S1" },
     { "RP_P1_S1", "RP_P2_S1", "RP_P3_S1" },
     },
    {
     { "GC_E_S1", NULL, NULL },
     { "GC_A1_S1", "GC_A2_S1", NULL },
     { "GC_B1_S1", "GC_B2_S1", "GC_B3_S1" },
     { "GC_P1_S1", "GC_P2_S1", "GC_P3_S1" },
     },
    {
     { "CB_L123_S1", "CB_L123_S1", "CB_L123_S1" },
     { "CB_L123_S1", "CB_L123_S1", "CB_L123_S1" },
     { "CB_L123_S1", "CB_L123_S1", "CB_L123_S1" },
     { NULL, NULL, NULL },
     },
    {
     { "SD_L123_S1", "SD_L123_S1", "SD_L123_S1" },
     { "SD_L123_S1", "SD_L123_S1", "SD_L123_S1" },
     { "SD_L123_S1", "SD_L123_S1", "SD_L123_S1" },
     { "SD_L123_S1", "SD_L123_S1", "SD_L123_S1" },
     },
    {
     { "HP_L1_S1", "HP_L1_S1", "HP_L1_S1" },
     { "HP_L2_S1", "HP_L2_S1", "HP_L2_S1" },
     { "HP_L3_S1", "HP_L3_S1", "HP_L3_S1" },
     { NULL, NULL, NULL },
     }
};

// array of results point types by vehicle:class:test:points
// each value is a type of points to score, 0x0 means none
// e.g. RP:beginner:1 has 0x01 (Impact) 0x02 (Accuracy) 0x03 (Time) 0x05 (Balloon)
static u8 sResultPtTypes[6][4][3][4] = {
    //  Test 1                      Test 2                      Test 3
    { { { 0x01, 0x02, 0x04, 0x00 }, { 0x00, 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00, 0x00 } },
     { { 0x01, 0x02, 0x0B, 0x00 }, { 0x01, 0x02, 0x04, 0x00 }, { 0x00, 0x00, 0x00, 0x00 } },
     { { 0x01, 0x02, 0x03, 0x00 }, { 0x01, 0x02, 0x0B, 0x00 }, { 0x01, 0x02, 0x03, 0x00 } },
     { { 0x01, 0x02, 0x06, 0x00 }, { 0x01, 0x02, 0x03, 0x04 }, { 0x01, 0x02, 0x0B, 0x00 } } },
    { { { 0x01, 0x02, 0x03, 0x05 }, { 0x00, 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00, 0x00 } },
     { { 0x01, 0x02, 0x03, 0x04 }, { 0x01, 0x02, 0x03, 0x09 }, { 0x00, 0x00, 0x00, 0x00 } },
     { { 0x01, 0x02, 0x03, 0x05 }, { 0x01, 0x02, 0x04, 0x00 }, { 0x03, 0x00, 0x00, 0x00 } },
     { { 0x03, 0x00, 0x00, 0x00 }, { 0x03, 0x00, 0x00, 0x00 }, { 0x01, 0x02, 0x03, 0x09 } } },
    { { { 0x01, 0x02, 0x03, 0x04 }, { 0x00, 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00, 0x00 } },
     { { 0x01, 0x02, 0x03, 0x04 }, { 0x01, 0x02, 0x03, 0x07 }, { 0x00, 0x00, 0x00, 0x00 } },
     { { 0x01, 0x02, 0x03, 0x04 }, { 0x01, 0x02, 0x03, 0x07 }, { 0x01, 0x02, 0x03, 0x08 } },
     { { 0x01, 0x02, 0x03, 0x04 }, { 0x01, 0x02, 0x03, 0x07 }, { 0x01, 0x02, 0x03, 0x08 } } },
    { { { 0x0F, 0x0E, 0x0D, 0x0C }, { 0x0F, 0x0E, 0x0D, 0x0C }, { 0x0F, 0x0E, 0x0D, 0x0C } },
     { { 0x0F, 0x0E, 0x0D, 0x0C }, { 0x0F, 0x0E, 0x0D, 0x0C }, { 0x0F, 0x0E, 0x0D, 0x0C } },
     { { 0x0F, 0x0E, 0x0D, 0x0C }, { 0x0F, 0x0E, 0x0D, 0x0C }, { 0x0F, 0x0E, 0x0D, 0x0C } },
     { { 0x0F, 0x0E, 0x0D, 0x0C }, { 0x0F, 0x0E, 0x0D, 0x0C }, { 0x0F, 0x0E, 0x0D, 0x0C } } },
    { { { 0x01, 0x02, 0x10, 0x00 }, { 0x01, 0x02, 0x10, 0x00 }, { 0x01, 0x02, 0x10, 0x00 } },
     { { 0x01, 0x02, 0x10, 0x00 }, { 0x01, 0x02, 0x10, 0x00 }, { 0x01, 0x02, 0x10, 0x00 } },
     { { 0x01, 0x02, 0x10, 0x00 }, { 0x01, 0x02, 0x10, 0x00 }, { 0x01, 0x02, 0x10, 0x00 } },
     { { 0x01, 0x02, 0x10, 0x00 }, { 0x01, 0x02, 0x10, 0x00 }, { 0x01, 0x02, 0x10, 0x00 } } },
    { { { 0x03, 0x00, 0x00, 0x00 }, { 0x03, 0x00, 0x00, 0x00 }, { 0x03, 0x00, 0x00, 0x00 } },
     { { 0x03, 0x00, 0x00, 0x00 }, { 0x03, 0x00, 0x00, 0x00 }, { 0x03, 0x00, 0x00, 0x00 } },
     { { 0x03, 0x00, 0x00, 0x00 }, { 0x03, 0x00, 0x00, 0x00 }, { 0x03, 0x00, 0x00, 0x00 } },
     { { 0x03, 0x00, 0x00, 0x00 }, { 0x03, 0x00, 0x00, 0x00 }, { 0x03, 0x00, 0x00, 0x00 } } }
};

static s32 sResultMenu[] = {
    0x0E, // "Check photo"
    0x60, // "Replay"
    0x5B  // "Next"
};

static s16* sPtsTallyStr[] = {
    sPtsTally0,
    sPtsTally1,
    sPtsTally2,
    sPtsTally3,
};

static s32 sReplayTipSet = FALSE;
static s32 sVehTipIsInit = FALSE;

// forward declarations
void resultSumTally(s32);
void result_8032E698(void);
s32 resultMenuChoose(s32);
void resultDrawTally(s32);
void resultGenTipText(s32);

s32 resultHandler(s32 arg0) {
    Unk80362690_Unk0_UnkC* unkC;
    s32 var_v1;

    unkC = &D_80362690->unk0[D_80362690->unk9C].unkC;
    resultSumTally(arg0);

    while ((var_v1 = resultMenuChoose(arg0)) == 0) {
        uvGfxBegin();
        func_80204FC4((s32)unkC->unk70->unk22C);
        resultDrawTally(arg0);
        uvGfxEnd();
    }

    result_8032E698();

    // FIXME: Unk80362690_Unk0_UnkC is wrong, indexing 15 in 4-byte buffer to match
    // was: temp_sw->pad8B
    if ((unkC->veh == VEHICLE_CANNONBALL) && (unkC->pad7C[0xF] != 0)) {
        unkC->pad7C[0xF] = 0;
    }
    return var_v1;
}

u8 resultListPhoto(void) {
    Unk80362690_Unk0_UnkC* unkC;

    unkC = &D_80362690->unk0[D_80362690->unk9C].unkC;
    if (D_80362690->unk0[D_80362690->unk9C].unkC.unk7B != 0) {
        return 0;
    }
    return (unkC->veh == VEHICLE_HANG_GLIDER || unkC->veh == VEHICLE_BIRDMAN);
}

u8 resultListReplay(void) {
    Unk80362690_Unk0_UnkC* unkC;
    s32 ret;

    unkC = &D_80362690->unk0[D_80362690->unk9C].unkC;
    ret = (unkC->veh == VEHICLE_HANG_GLIDER || unkC->veh == VEHICLE_ROCKET_BELT || unkC->veh == VEHICLE_GYROCOPTER || unkC->veh == VEHICLE_BIRDMAN);
    if (levelDataGetFALC(NULL) != 0) {
        ret = 0;
    }
    return ret;
}

// populates menu at results screen, showing Check Photo/Replay/Next
void resultGenMenu(void) {
    s32 idx;
    u8* ptr;
    u8 val = 0xE; // fakematch?

    idx = 0;
    if (resultListPhoto()) {
        ptr = levelGet_80345CB0();
        if (ptr[1] == 1) {
            func_803405E4();
        }
        sResultMenu[0] = val; // Check Photo
        idx = 1;
    }
    if (resultListReplay()) {
        sResultMenu[idx++] = 0x60; // Replay
    }
    sResultMenu[idx++] = 0x5B; // Next
    menuCreateItems(170, 2, 6, 1.0f, 1.0f, sResultMenu, idx);
    if (resultListPhoto() && !func_8033F62C()) {
        menu_8030B69C(1);
    }
    func_80312FF8(5);
}

s32 resultMenuItemLookup(s32 idx) {
    if (idx < 0) {
        return idx;
    }
    switch (sResultMenu[idx]) {
    case 0xE: // Check Photo
        return 0;
    case 0x60: // Replay
        return 1;
    case 0x5B: // Next
        return 2;
    default:
        return -1;
    }
}

void resultSumTally(s32 arg0) {
    s32 val;
    Unk80362690_Unk0_UnkC* unkC;
    s32 i;
    const char* var_s0;
    s32 pts;
    s32 ptsTotal;
    s16* scores;
    s32 ptType;
    s32 strIdx;

    unkC = &D_80362690->unk0[D_80362690->unk9C].unkC;
    ptsTotal = 0;
    if (unkC->veh == VEHICLE_BIRDMAN) {
        if (arg0 != 0) {
            var_s0 = "BD_ALL_S2";
        } else {
            var_s0 = "BD_ALL_S1";
        }
    } else if (arg0 != 0) {
        var_s0 = sResultTestNames2[unkC->veh][unkC->cls][unkC->test];
    } else {
        var_s0 = sResultTestNames1[unkC->veh][unkC->cls][unkC->test];
    }
    sReplayTipText = textGetDataByName(var_s0);
    if (sReplayTipText == NULL) {
        sTipTextMissing = TRUE;
        sTipTextId = var_s0;
    } else {
        sTipTextMissing = FALSE;
    }
    sScreenFadeDuration = (arg0 == 0) ? 1.5f : 0.0f;
    if (arg0 != 0) {
        resultGenMenu();
        for (i = 0; i < ARRAY_COUNT(sPtsTallyStr); i++) {
            ptType = sResultPtTypes[unkC->veh][unkC->cls][unkC->test][i];
            // unkC->unk4 is class, p40->unk6 * unkC->unk2 is test * vehicle?
            scores = D_80364210[D_80362690->unk9C].unk0[unkC->cls].unk0[unkC->test][unkC->veh + 1].scores;
            sPtsTallyStr[i][0] = sPtsTallyStr[i][1] = sPtsTallyStr[i][2] = -3;
            sPtsTallyStr[i][3] = 0xFFE;
            sPtsTallyStr[i][4] = -1;
            switch (ptType) {
            case 1:
                pts = scores[3];
                break;
            case 2:
                pts = scores[2];
                break;
            case 3:
                pts = scores[6];
                break;
            case 4:
                pts = scores[7];
                break;
            case 5:
                pts = scores[11];
                break;
            case 6:
                pts = scores[5];
                break;
            case 7:
                pts = scores[10];
                break;
            case 8:
                pts = scores[16];
                break;
            case 9:
                pts = scores[15];
                break;
            case 11:
                pts = scores[14];
                break;
            case 12:
                pts = D_80364210[D_80362690->unk9C].unk0[unkC->cls].unk0[0][unkC->veh + 1].scores[2];
                break;
            case 13:
                pts = D_80364210[D_80362690->unk9C].unk0[unkC->cls].unk0[1][unkC->veh + 1].scores[2];
                break;
            case 14:
                pts = D_80364210[D_80362690->unk9C].unk0[unkC->cls].unk0[2][unkC->veh + 1].scores[2];
                break;
            case 15:
                pts = D_80364210[D_80362690->unk9C].unk0[unkC->cls].unk0[3][unkC->veh + 1].scores[2];
                break;
            case 16:
                pts = scores[13];
                break;
            default:
                continue;
            }

            if (pts == 0x7F) {
                sPtsTallyStr[i][0] = sPtsTallyStr[i][1] = -3;
                sPtsTallyStr[i][1] = 0xFFE;
                sPtsTallyStr[i][2] = -1;
            } else {
                ptsTotal += pts;
                textFmtInt(sPtsTallyStr[i], pts, 3);
            }
        }

        if (D_80364210[D_80362690->unk9C].unk0[0].unk0[0][1].unk8 != 0) {
            textFmtInt(sPtsDeductedStr, -D_80364210[D_80362690->unk9C].unk0[0].unk0[0][1].unk8, 3);
            ptsTotal += D_80364210[D_80362690->unk9C].unk0[0].unk0[0][1].unk8; // unk38
        } else {
            textFmtInt(sPtsDeductedStr, -scores[12], 3);
            ptsTotal += scores[12];
        }
        if (ptsTotal < 0) {
            ptsTotal = 0;
        }
        textFmtInt(sTotalPointsStr, ptsTotal, 3);
        strIdx = (ptsTotal == 1) ? 0x8A : 0x131; // "pt." : "pts."
        sPtsLabelStr = textGetDataByIdx(strIdx);
    }
    sReplayTipSet = FALSE;
}

void result_8032E698(void) {
    func_80312FF8(7);
}

s32 resultMenuChoose(s32 arg0) {
    Unk80362690_Unk0_UnkC* unkC;
    s32 ret;
    s32 item;

    unkC = &D_80362690->unk0[D_80362690->unk9C].unkC;
    ret = 0;
    func_80313D74();
    sScreenFadeDuration += D_8034F854;
    if (sScreenFadeDuration > 1.5f) {
        sScreenFadeDuration = 1.5f;
    }
    if ((arg0 != 0) && (sScreenFadeDuration > 0.75f)) {
        ret = menu_8030B50C();
        item = resultMenuItemLookup(ret);
        switch (item) {
        case 2:
            if (D_80362690->unk0[D_80362690->unk9C].unkC.unk7B != 0) {
                return 0xB;
            }
            menuSetProps();
            // FIXME: unkC->pad8B
            if (((unkC->veh != VEHICLE_CANNONBALL) || (unkC->pad7C[0xF] != 0)) && (unkC->veh != VEHICLE_BIRDMAN)) {
                ret = func_803470EC();
            } else {
                ret = 2;
            }
            sScreenFadeDuration = 1.5f;
            break;
        case 1:
            func_8032C540(D_80362690);
            resultGenTipText(unkC->veh);
            ret = 0;
            sScreenFadeDuration = 1.5f;
            break;
        case 0:
            if (func_8033E3A8(2) != 0) {
                // FIXME: unkC->pad8A
                saveFileWrite((s32)unkC->pad7C[0xE]);
            }
            ret = 0;
            sScreenFadeDuration = 1.5f;
            break;
        case 3:
            return 4;
        case 4:
            return 2;
        case 5:
            return 0xB;
        case 6:
            return 2;
        case -3:
        case -2:
        case -1:
            ret = 0;
            break;
        }
    } else {
        if (arg0 == 0) {
            sScreenFadeDuration = 1.5f;
            demo_80323020();
            if (demoButtonPress(D_80362690->unk9C, A_BUTTON | B_BUTTON | START_BUTTON) != 0) {
                ret = 1;
                if (demoButtonPress(D_80362690->unk9C, A_BUTTON | START_BUTTON) != 0) {
                    func_8033F7F8(0x73);
                } else if (demoButtonPress(D_80362690->unk9C, CONT_B) != 0) {
                    func_8033F7F8(1);
                }
            }
        }
    }
    return ret;
}

void resultDrawTally(s32 arg0) {
    Unk80362690_Unk0_UnkC* unkC;
    s32 alpha;
    s32 x;
    s32 y;
    s32 var_s2;
    s32 i;
    s32 pad;
    s32 pad2;
    f32 spAC;
    char sp48[100];

    var_s2 = 0;
    unkC = &D_80362690->unk0[D_80362690->unk9C].unkC;
    func_80314154();
    uvGfxSetFlags(GFX_STATE_400000);
    spAC = (f32)(1.0 - (f64)((1.5f - sScreenFadeDuration) / 1.5f));
    uvVtxBeginPoly();
    alpha = (s32)(130.0f * spAC);
    uvVtx(0, SCREEN_HEIGHT, 0, 0, 0, 0, 0, 0, alpha);
    uvVtx(0, 0, 0, 0, 0, 0, 0, 0, alpha);
    uvVtx(SCREEN_WIDTH, 0, 0, 0, 0, 0, 0, 0, alpha);
    uvVtx(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 0, 0, 0, 0, alpha);
    uvVtxEndPoly();
    uvGfxClearFlags(GFX_STATE_400000);
    if (!sReplayTipSet && (unkC->veh != VEHICLE_BIRDMAN)) {
        uvVtxBeginPoly();
        alpha = (s32)(255.0f * spAC);
        uvVtx(36, 120, 0, 0, 0, 0xD2, 0xD2, 0xD2, alpha);
        uvVtx(36, 119, 0, 0, 0, 0xD2, 0xD2, 0xD2, alpha);
        uvVtx(272, 119, 0, 0, 0, 0xD2, 0xD2, 0xD2, alpha);
        uvVtx(272, 120, 0, 0, 0, 0xD2, 0xD2, 0xD2, alpha);
        uvVtxEndPoly();
    }
    func_803141E4();
    if ((spAC >= 0.5f) && (arg0 != 0)) {
        menuInit();
    }
    if (sTipTextMissing) {
        uvFontSet(0);
        uvFont_8021956C(0xD2, 0x00, 0xD2, 0xFF);
        uvFont_80219550(1.0, 1.0);
        uvSprintf(sp48, "STR MISSING %s", sTipTextId);
        uvFont_80219ACC(0x14, 0x64, sp48);
    } else {
        uvFontSet(6);
        alpha = (s32)(255.0f * spAC);
        uvFont_8021956C(0xD2, 0xD2, 0xD2, alpha);
        uvFont_80219550(1.0, 1.0);

        y = sReplayTipSet ? 168 : 180;
        x = sReplayTipSet ? 44 : 28;

        if (sReplayTipText != NULL) {
            do {
                var_s2 += func_80219874(x, y, &sReplayTipText[var_s2], 0xFF, 0xFFE);
                y -= 16;
            } while (sReplayTipText[var_s2] != -1);
        } else {
            _uvDebugPrintf("Null Kanji string in screv screen\n");
        }
    }
    if ((arg0 != 0) && !sReplayTipSet && (unkC->veh != VEHICLE_BIRDMAN)) {
        uvFontSet(6);
        alpha = (s32)(255.0f * spAC);
        uvFont_8021956C(0xD2, 0xD2, 0xD2, alpha);
        uvFont_80219550(1.0, 1.0);

        for (i = 0, y = 116; i < ARRAY_COUNT(sPtsTallyStr); i++, y += 16) {
            func_80219874(180, y, sPtsTallyStr[i], 3, 0xFFE);
        }

        if ((unkC->veh == VEHICLE_CANNONBALL) || (unkC->veh == VEHICLE_HANG_GLIDER) || (unkC->veh == VEHICLE_SKY_DIVING)) {
            func_80219874(180, 100, sTotalPointsStr, 3, 0xFFE);
            func_80219874(216, 100, sPtsLabelStr, 4, 0xFFE);
        } else {
            func_80219874(180, 84, sTotalPointsStr, 3, 0xFFE);
            func_80219874(216, 84, sPtsLabelStr, 4, 0xFFE);
        }

        if ((unkC->veh != VEHICLE_CANNONBALL) && (unkC->veh != VEHICLE_HANG_GLIDER) && (unkC->veh != VEHICLE_SKY_DIVING)) {
            func_80219874(180, 100, sPtsDeductedStr, 4, 0xFFE);
        }
    }
    uvFont_80219EA8();
}

void resultGenTipText(s32 veh) {
    s16* text;
    char str[256];
    s32 i;

    // lazy initialization with random hint text id
    if (!sVehTipIsInit) {
        for (i = 0; i < ARRAY_COUNT(sVehTipIdx); i++) {
            sVehTipIdx[i] = (s8)((s32)((uvRandF_RANLUX() * 14.0f) + 0.5f) + 1);
        }
        sVehTipIsInit = TRUE;
    }

    if (veh >= 3) {
        return;
    }

    sVehTipIdx[veh]++;
    if (sVehTipIdx[veh] >= 16) {
        sVehTipIdx[veh] = 1;
    }
    uvSprintf(str, "%s_%d_A", gVehShortNames[veh], sVehTipIdx[veh]);
    text = textGetDataByName(str);
    if (text == NULL) {
        _uvDebugPrintf("Could not find %s in jtext\n", str);
    } else {
        sReplayTipText = text;
        sReplayTipSet = TRUE;
    }
}
