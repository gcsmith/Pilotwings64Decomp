#include "common.h"
#include <uv_font.h>
#include <uv_geometry.h>
#include <uv_graphics.h>
#include "cannonball.h"
#include "code_9A960.h"
#include "code_B2900.h"
#include "menu.h"
#include "menu_utils.h"
#include "task.h"
#include "text_data.h"
#include "total_results.h"

STATIC_DATA s16 sTestPtsStr0[8];
STATIC_DATA s16 sTestPtsStr1[8];
STATIC_DATA s16 sTestPtsStr2[8];
STATIC_DATA s16 sTestPtsStr3[6];

STATIC_DATA s16* sMedalName;
STATIC_DATA s32 sUnused_8037AD20[2];
STATIC_DATA s16 sTotalPtsStr[5];
STATIC_DATA s16 D_8037AD32_pad;
STATIC_DATA s16* sTotPtUnitStr;
STATIC_DATA s16 D_8037AD38[5];
STATIC_DATA u8 D_8037AD42;
STATIC_DATA s32 D_8037AD44_pad;
STATIC_DATA s16* sTestPtUnitStr[4];
STATIC_DATA char sMedalNameCopy[24];

STATIC_DATA const char* sStageMedalName[][5] = {
    { "E_S3_BLONDS", "E_S3_SILVER", "E_S3_GOLD", "E_S3_PERFECT", "E_S3_GREAT" },
    { "A_S3_BLONDS", "A_S3_SILVER", "A_S3_GOLD", "A_S3_PERFECT", "A_S3_GREAT" },
    { "B_S3_BLONDS", "B_S3_SILVER", "B_S3_GOLD", "B_S3_PERFECT", "B_S3_GREAT" },
    { "P_S3_BLONDS", "P_S3_SILVER", "P_S3_GOLD", "P_S3_PERFECT", "P_S3_GREAT" },
};

STATIC_DATA const char* sBonusMedalName[] = { "BONUS_S3_BLONDS", "BONUS_S3_SILVER", "BONUS_S3_GOLD", "BONUS_S3_PERFECT", "BONUS_S3_GREAT" };

STATIC_DATA s32 sResultNextMenu[1] = { TEXT_NEXT_SGI };

STATIC_DATA s32 sResultsMenuItems[3] = { TEXT_RETRY_SGI, TEXT_ANOTHER_TASK_SGI, TEXT_QUIT_SGI };

STATIC_DATA s32 sResultsMenuCount = 0;

STATIC_DATA s16* sTestPtsStr[4] = { sTestPtsStr0, sTestPtsStr1, sTestPtsStr2, sTestPtsStr3 };

// forward declarations
void totResultInit(void);
void totResultCreateMenu(void);
void totResultDeinit(void);
s32 totResultMenuChoose(void);
void totResultDrawTally(void);

u8 totResult_80346FC0(Unk80362690_Unk0* arg0) {
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    s32 temp_v0;
    u16 veh;

    veh = arg0->veh;
    if (veh == VEHICLE_CANNONBALL) {
        sp28 = levelSetPointsToNextMedal(&sp2C, D_80359AAC, CLASS_COUNT);
        temp_v0 = levelSetPointsToNextMedal(&sp24, D_80359AA8, CLASS_COUNT);
        if ((sp28 < temp_v0) || ((sp28 == 3) && (temp_v0 == 3) && (sp24 == 0))) {
            return TRUE;
        }
        return FALSE;
    }
    return D_80364210[D_80362690->unk9C].unk40[arg0->cls].unk0[arg0->test][veh].unk0 == 4;
}

s32 totResultHandler(void) {
    s32 sp1C;

    totResultInit();
    while ((sp1C = totResultMenuChoose()) == 0) {
        uvGfxBegin();
        totResultDrawTally();
        uvGfxEnd();
    }
    totResultDeinit();
    return sp1C;
}

s32 totResult_80347150(s32 arg0) {
    Unk80362690_Unk0* unkC;

    unkC = &D_80362690->unkC[D_80362690->unk9C];
    if (arg0 < 0) {
        return arg0;
    }
    if (totResult_80346FC0(&D_80362690->unkC[D_80362690->unk9C])) {
        return 6;
    }
    if (IS_MAIN_VEHICLE(unkC->veh)) {
        if (unkC->cls == CLASS_BEGINNER) {
            switch (arg0) {
            case 0:
                return 3;
            case 1:
                return 5;
            }
        } else {
            switch (arg0) {
            case 0:
                return 3;
            case 1:
                return 4;
            case 2:
                return 5;
            }
        }
    } else { // bonus: CB/SD/JH/BD
        switch (arg0) {
        case 0:
            return 3;
        case 1:
            return 5;
        }
    }
    return -1;
}

void totResultInit(void) {
    Unk80362690_Unk0* temp_s4;
    s32 temp_v0;
    s32 textId;
    s32 var_s5;
    const char* var_a1;
    char* var_v0_2;
    s32 var_v1;
    s32 sp50;
    Unk80364210* sp4C;
    u8 temp_t5;
    u8* var_v1_3;
    s32 i;

    temp_s4 = &D_80362690->unkC[D_80362690->unk9C];
    var_s5 = 0;
    sp4C = &D_80364210[D_80362690->unk9C];
    sUnused_8037AD20[0] = 0;

    for (i = 0; i < ARRAY_COUNT(sTestPtsStr); i++) {
        sTestPtsStr[i][0] = sTestPtsStr[i][1] = sTestPtsStr[i][2] = -3;
        sTestPtsStr[i][3] = 0xFFE;
        sTestPtsStr[i][4] = -1;
    }

    for (i = 0; i < taskGetTestCount(temp_s4->cls, temp_s4->veh); i++) {
        temp_v0 = testGetPointCount(sp4C, temp_s4->cls, i, temp_s4->veh);
        if (temp_v0 != 127) {
            var_s5 += temp_v0;
            textFmtInt(sTestPtsStr[i], temp_v0, 3);
        }
        textId = (temp_v0 == 1) ? TEXT_PT : TEXT_PTS;
        sTestPtUnitStr[i] = textGetDataByIdx(textId);
    }

    if (IS_MAIN_VEHICLE(temp_s4->veh)) {
        var_v1 = temp_s4->cls;
    } else { // bonus: CB/SD/JH/BD
        var_v1 = temp_s4->veh + 1;
    }
    D_8037AD42 = levelSetPointsToNextMedal(&sp50, var_s5, var_v1);
    textFmtInt(sTotalPtsStr, var_s5, 3);
    textId = (var_s5 == 1) ? TEXT_PT : TEXT_PTS;
    sTotPtUnitStr = textGetDataByIdx(textId);
    textFmtInt(D_8037AD38, sp50, 3);
    var_v1 = D_8037AD42;
    if ((var_v1 == 3) && (sp50 == 0)) {
        var_v1 = D_8037AD42 = 4;
    }
    if (IS_MAIN_VEHICLE(temp_s4->veh)) {
        var_a1 = sStageMedalName[temp_s4->cls][var_v1];
    } else { // bonus: CB/SD/JH/BD
        var_a1 = sBonusMedalName[var_v1];
    }
    if (var_a1 != NULL) {
        for (i = 0; var_a1[i] != '\0'; i++) {
            sMedalNameCopy[i] = var_a1[i];
        }
    }
    sMedalName = textGetDataByName(var_a1);
    totResultCreateMenu();
}

void totResultCreateMenu(void) {
    Unk80362690_Unk0* temp_a0;

    if (totResult_80346FC0(&D_80362690->unkC[D_80362690->unk9C])) {
        menuCreateItems(170, 2, 6, 1.0f, 1.0f, sResultNextMenu, ARRAY_COUNT(sResultNextMenu));
        return;
    }
    temp_a0 = &D_80362690->unkC[D_80362690->unk9C];

    sResultsMenuCount = 0;
    sResultsMenuItems[sResultsMenuCount++] = TEXT_RETRY_SGI;
    // Only show "Another test" for non-bonus vehicles HG/RP/GC and class A/B/Pilot
    if ((IS_MAIN_VEHICLE(temp_a0->veh)) && (temp_a0->cls != CLASS_BEGINNER)) {
        sResultsMenuItems[sResultsMenuCount++] = TEXT_ANOTHER_TASK_SGI;
    }
    sResultsMenuItems[sResultsMenuCount++] = TEXT_QUIT_SGI;
    menuCreateItems(170, 2, 6, 1.0f, 1.0f, sResultsMenuItems, sResultsMenuCount);
}

void totResultDeinit(void) {
}

s32 totResultMenuChoose(void) {
    Unk80362690_Unk0* sp1C;
    s32 temp_v0;

    sp1C = &D_80362690->unkC[D_80362690->unk9C];
    if (totResult_80347150(menu_8030B668()) == 3) {
        menuUtilSetSoundFlags(MENU_SOUND_CHANGE);
    } else {
        menuUtilSetSoundFlags(MENU_SOUND_CHANGE | MENU_SOUND_SELECT);
    }
    temp_v0 = totResult_80347150(menuCheckInputs());
    switch (temp_v0) {
    case 3:
        return GAME_STATE_TEST_SETUP;
    case 4:
        return GAME_STATE_TEST_DETAILS;
    case 5:
        return GAME_STATE_VEHICLE_CLASS_SELECT;
    case 6:
        if (totResult_80346FC0(sp1C)) {
            return GAME_STATE_CONGRATULATIONS;
        }
    default:
        return 0;
    }
}

// draws overall test summary screen after objectives breakdown. e.g.:
// Test 1     100 pts
// Test 2     100 pts
// ------------------
// Total      200 pts
#if defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsometimes-uninitialized"
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif
void totResultDrawTally(void) {
    Unk80362690_Unk0* sp6C;
    s32 len;
    s32 x2;
    s32 x1;
    s32 y;
    s32 offset;
    s32 i;
    s32 numTests;

    offset = 0;
    sp6C = &D_80362690->unkC[D_80362690->unk9C];
    func_80204FC4(sp6C->unk70->unk22C);
    func_80314154();

    uvVtxBeginPoly();
    uvVtx(0, 240, 0, 0, 0, 0x00, 0x00, 0x00, 0x78);
    uvVtx(0, 0, 0, 0, 0, 0x00, 0x00, 0x00, 0x78);
    uvVtx(320, 0, 0, 0, 0, 0x00, 0x00, 0x00, 0x78);
    uvVtx(320, 240, 0, 0, 0, 0x00, 0x00, 0x00, 0x78);
    uvVtxEndPoly();

    x1 = 34;
    x2 = 272;
    y = 120;
    uvGfxClearFlags(0x400000);
    uvVtxBeginPoly();
    uvVtx(x1, y, 0, 0, 0, 0xD2, 0xD2, 0xD2, 0xFF);
    uvVtx(x1, y - 1, 0, 0, 0, 0xD2, 0xD2, 0xD2, 0xFF);
    uvVtx(x2, y - 1, 0, 0, 0, 0xD2, 0xD2, 0xD2, 0xFF);
    uvVtx(x2, y, 0, 0, 0, 0xD2, 0xD2, 0xD2, 0xFF);
    uvVtxEndPoly();

    func_803141E4();
    uvFontSet(6);
    uvFontColor(0xD2, 0xD2, 0xD2, 0xFF);
    uvFontScale(1.0, 1.0);

    y = 180;
    if (sMedalName != NULL) {
        do {
            len = uvFontPrintStr16(28, y, &sMedalName[offset], 0xFF, 0xFFE);
            offset += len;
            y -= 16;
        } while (sMedalName[offset] != -1);
    } else {
        _uvDebugPrintf("Missing or bad kanji string in level total, %s\n", sMedalNameCopy);
    }

    if (sp6C->veh == VEHICLE_CANNONBALL) {
        uvFontPrintStr16(202, 116, sTotalPtsStr, 3, 0xFFE);
        uvFontPrintStr16(236, 116, sTotPtUnitStr, 4, 0xFFE);
    } else {
        numTests = taskGetTestCount(sp6C->cls, sp6C->veh);
        for (i = 0; i < numTests; i++) {
            y = ((numTests * 16) + 100) - 16 * i;
            uvFontPrintStr16(202, y, sTestPtsStr[i], 3, 0xFFE);
            uvFontPrintStr16(236, y, sTestPtUnitStr[i], 4, 0xFFE);
        }
    }

    if ((numTests != 1) && (sp6C->veh != VEHICLE_CANNONBALL)) {
        uvFontPrintStr16(202, 100, sTotalPtsStr, 3, 0xFFE);
        uvFontPrintStr16(236, 100, sTotPtUnitStr, 4, 0xFFE);
    }
    if (D_8037AD42 != 4) {
        uvFontPrintStr16(128, 68, D_8037AD38, 3, 0xFFE);
    }
    menuRender();
    uvFontGenDlist();
}
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif
