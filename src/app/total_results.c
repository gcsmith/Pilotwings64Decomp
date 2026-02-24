#include "common.h"
#include <uv_font.h>
#include <uv_geometry.h>
#include <uv_graphics.h>
#include <uv_level.h>
#include "cannonball.h"
#include "code_99D40.h"
#include "code_9A960.h"
#include "code_B2900.h"
#include "menu.h"
#include "save.h"
#include "text_data.h"
#include "total_results.h"

static s16 sTestPtsStr0[8];
static s16 sTestPtsStr1[8];
static s16 sTestPtsStr2[8];
static s16 sTestPtsStr3[6];

static s16* sMedalName;
static s32 sUnused_8037AD20[2];
static s16 sTotalPtsStr[5];
static s16 D_8037AD32_pad;
static s16* sTotPtUnitStr;
static s16 D_8037AD38[5];
static u8 D_8037AD42;
static s32 D_8037AD44_pad;
static s16* sTestPtUnitStr[4];
static char sMedalNameCopy[24];

static const char* sStageMedalName[][5] = {
    { "E_S3_BLONDS", "E_S3_SILVER", "E_S3_GOLD", "E_S3_PERFECT", "E_S3_GREAT" },
    { "A_S3_BLONDS", "A_S3_SILVER", "A_S3_GOLD", "A_S3_PERFECT", "A_S3_GREAT" },
    { "B_S3_BLONDS", "B_S3_SILVER", "B_S3_GOLD", "B_S3_PERFECT", "B_S3_GREAT" },
    { "P_S3_BLONDS", "P_S3_SILVER", "P_S3_GOLD", "P_S3_PERFECT", "P_S3_GREAT" },
};

static const char* sBonusMedalName[] = { "BONUS_S3_BLONDS", "BONUS_S3_SILVER", "BONUS_S3_GOLD", "BONUS_S3_PERFECT", "BONUS_S3_GREAT" };

static s32 sResultNextMenu = 0x5B; // "Next"

static s32 sResultRetryQuitMenu[3] = {
    0x189, // Retry
    0x166, // Another test
    0x01D  // Quit
};

static s32 sResultRetryQuitIdx = 0;

static s16* sTestPtsStr[4] = { sTestPtsStr0, sTestPtsStr1, sTestPtsStr2, sTestPtsStr3 };

// forward declarations
void totResultInit(void);
void totResultCreateMenu(void);
void totResultDeinit(void);
s32 totResultMenuChoose(void);
void totResultDrawTally(void);

u8 totResult_80346FC0(Unk80362690_Unk0_UnkC* arg0) {
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    s32 temp_v0;
    u16 veh;

    veh = arg0->veh;
    if (veh == VEHICLE_CANNONBALL) {
        sp28 = func_8032C174(&sp2C, D_80359AAE, 4);
        temp_v0 = func_8032C174(&sp24, D_80359AAA, 4);
        if ((sp28 < temp_v0) || ((sp28 == 3) && (temp_v0 == 3) && (sp24 == 0))) {
            return TRUE;
        }
        return FALSE;
    }
    return D_80364210[D_80362690->unk9C].unk0[arg0->cls].unk0[arg0->test][veh + 1].result.unk0 == 4;
}

s32 totResultHandler(void) {
    s32 sp1C;

    totResultInit();
    while (!(sp1C = totResultMenuChoose())) {
        uvGfxBegin();
        totResultDrawTally();
        uvGfxEnd();
    }
    totResultDeinit();
    return sp1C;
}

s32 totResult_80347150(s32 arg0) {
    Unk80362690_Unk0_UnkC* unkC;

    unkC = &D_80362690->unk0[D_80362690->unk9C].unkC;
    if (arg0 < 0) {
        return arg0;
    }
    if (totResult_80346FC0(&D_80362690->unk0[D_80362690->unk9C].unkC)) {
        return 6;
    }
    if (unkC->veh <= VEHICLE_GYROCOPTER) { // HG/RP/GC
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
    Unk80362690_Unk0_UnkC* temp_s4;
    s32 temp_v0;
    s32 var_a0;
    s32 var_s5;
    const char* var_a1;
    char* var_v0_2;
    s32 var_v1;
    s32 sp50;
    Unk80364210* sp4C;
    u8 temp_t5;
    u8* var_v1_3;
    s32 i;

    temp_s4 = &D_80362690->unk0[D_80362690->unk9C].unkC;
    var_s5 = 0;
    sp4C = &D_80364210[D_80362690->unk9C];
    sUnused_8037AD20[0] = 0;

    for (i = 0; i < ARRAY_COUNT(sTestPtsStr); i++) {
        sTestPtsStr[i][0] = sTestPtsStr[i][1] = sTestPtsStr[i][2] = -3;
        sTestPtsStr[i][3] = 0xFFE;
        sTestPtsStr[i][4] = -1;
    }

    for (i = 0; i < levelGetTestCount(temp_s4->cls, temp_s4->veh); i++) {
        temp_v0 = func_8032BE1C(sp4C, temp_s4->cls, i, temp_s4->veh);
        if (temp_v0 != 127) {
            var_s5 += temp_v0;
            textFmtInt(sTestPtsStr[i], temp_v0, 3);
        }
        var_a0 = (temp_v0 == 1) ? 0x8A : 0x131; // "pt." : "pts."
        sTestPtUnitStr[i] = textGetDataByIdx(var_a0);
    }

    if (temp_s4->veh <= VEHICLE_GYROCOPTER) { // HG/RP/GC
        var_v1 = temp_s4->cls;
    } else { // bonus: CB/SD/JH/BD
        var_v1 = temp_s4->veh + 1;
    }
    D_8037AD42 = func_8032C174(&sp50, var_s5, var_v1);
    textFmtInt(sTotalPtsStr, var_s5, 3);
    var_a0 = (var_s5 == 1) ? 0x8A : 0x131; // "pt." : "pts."
    sTotPtUnitStr = textGetDataByIdx(var_a0);
    textFmtInt(D_8037AD38, sp50, 3);
    var_v1 = D_8037AD42;
    if ((var_v1 == 3) && (sp50 == 0)) {
        var_v1 = D_8037AD42 = 4;
    }
    if (temp_s4->veh <= VEHICLE_GYROCOPTER) { // HG/RP/GC
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
    Unk80362690_Unk0_UnkC* temp_a0;

    if (totResult_80346FC0(&D_80362690->unk0[D_80362690->unk9C].unkC)) {
        menuCreateItems(170, 2, 6, 1.0f, 1.0f, &sResultNextMenu, 1);
        return;
    }
    temp_a0 = &D_80362690->unk0[D_80362690->unk9C].unkC;

    sResultRetryQuitIdx = 0;
    sResultRetryQuitMenu[sResultRetryQuitIdx++] = 0x189; // Retry
    // Only show "Another test" for non-bonus vehicles HG/RP/GC and class A/B/Pilot
    if ((temp_a0->veh <= VEHICLE_GYROCOPTER) && (temp_a0->cls != CLASS_BEGINNER)) {
        sResultRetryQuitMenu[sResultRetryQuitIdx++] = 0x166; // Another test
    }
    sResultRetryQuitMenu[sResultRetryQuitIdx++] = 0x1D; // Quit
    menuCreateItems(170, 2, 6, 1.0f, 1.0f, sResultRetryQuitMenu, sResultRetryQuitIdx);
}

void totResultDeinit(void) {
}

s32 totResultMenuChoose(void) {
    Unk80362690_Unk0_UnkC* sp1C;
    s32 temp_v0;

    sp1C = &D_80362690->unk0[D_80362690->unk9C].unkC;
    if (totResult_80347150(menu_8030B668()) == 3) {
        func_80312FF8(4);
    } else {
        func_80312FF8(5);
    }
    temp_v0 = totResult_80347150(menu_8030B50C());
    switch (temp_v0) {
    case 3:
        return 4;
    case 4:
        return 2;
    case 5:
        return 0xB;
    case 6:
        if (totResult_80346FC0(sp1C)) {
            return 0xE;
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
#endif
void totResultDrawTally(void) {
    Unk80362690_Unk0_UnkC* sp6C;
    s32 len;
    s32 x2;
    s32 x1;
    s32 y;
    s32 offset;
    s32 i;
    s32 numTests;

    offset = 0;
    sp6C = &D_80362690->unk0[D_80362690->unk9C].unkC;
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
    uvFont_8021956C(0xD2, 0xD2, 0xD2, 0xFF);
    uvFont_80219550(1.0, 1.0);

    y = 180;
    if (sMedalName != NULL) {
        do {
            len = func_80219874(28, y, &sMedalName[offset], 0xFF, 0xFFE);
            offset += len;
            y -= 16;
        } while (sMedalName[offset] != -1);
    } else {
        _uvDebugPrintf("Missing or bad kanji string in level total, %s\n", sMedalNameCopy);
    }

    if (sp6C->veh == VEHICLE_CANNONBALL) {
        func_80219874(202, 116, sTotalPtsStr, 3, 0xFFE);
        func_80219874(236, 116, sTotPtUnitStr, 4, 0xFFE);
    } else {
        numTests = levelGetTestCount(sp6C->cls, sp6C->veh);
        for (i = 0; i < numTests; i++) {
            y = ((numTests * 16) + 100) - 16 * i;
            func_80219874(202, y, sTestPtsStr[i], 3, 0xFFE);
            func_80219874(236, y, sTestPtUnitStr[i], 4, 0xFFE);
        }
    }

    if ((numTests != 1) && (sp6C->veh != VEHICLE_CANNONBALL)) {
        func_80219874(202, 100, sTotalPtsStr, 3, 0xFFE);
        func_80219874(236, 100, sTotPtUnitStr, 4, 0xFFE);
    }
    if (D_8037AD42 != 4) {
        func_80219874(128, 68, D_8037AD38, 3, 0xFFE);
    }
    menuInit();
    uvFont_80219EA8();
}
#if defined(__clang__)
#pragma GCC diagnostic pop
#endif
