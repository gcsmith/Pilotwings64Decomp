#include "common.h"
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

static s16 D_803718F0[8];
static s16 D_80371900[8];
static s16 D_80371910[8];
static s16 D_80371920[6]; // TODO: why only 0xC bytes?
static f32 D_8037192C;
static s16* D_80371930;
static u8 D_80371934;
// pad 3
static const char* D_80371938;
static s16* D_8037193C;
static s16 D_80371940[8];
static s16 D_80371950[5];
static u8 D_8037195A[3];

static const char* D_8034FC40[6][4][3] = {
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

static const char* D_8034FD60[6][4][3] = {
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

static u8 D_8034FE80[6][4][3][4] = {
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

static s32 D_8034FFA0[] = {
    // gResultsMenu
    0x0E, // "Check photo"
    0x60, // "Replay"
    0x5B  // "Next"
};

static s16* D_8034FFAC[] = {
    D_803718F0,
    D_80371900,
    D_80371910,
    D_80371920,
};

static s32 D_8034FFBC = 0;
static s32 D_8034FFC0 = 0;

// forward declarations
u8 func_8032DE14(void);
u8 func_8032DE74(void);
void func_8032E060(s32);
void func_8032E698(void);
s32 func_8032E6B8(s32);
void func_8032E940(s32);
void func_8032EF10(s32);

s32 func_8032DD50(s32 arg0) {
    Unk80362690_Unk0_UnkC* unkC;
    s32 var_v1;

    unkC = &D_80362690->unk0[D_80362690->unk9C].unkC;
    func_8032E060(arg0);

    while ((var_v1 = func_8032E6B8(arg0)) == 0) {
        uvGfxBegin();
        func_80204FC4((s32)unkC->unk70->unk22C);
        func_8032E940(arg0);
        uvGfxEnd();
    }

    func_8032E698();

    // FIXME: Unk80362690_Unk0_UnkC is wrong, indexing 15 in 4-byte buffer to match
    // was: temp_sw->pad8B
    if ((unkC->unk2 == 3) && (unkC->pad7C[0xF] != 0)) {
        unkC->pad7C[0xF] = 0;
    }
    return var_v1;
}

u8 func_8032DE14(void) {
    Unk80362690_Unk0_UnkC* unkC;

    unkC = &D_80362690->unk0[D_80362690->unk9C].unkC;
    if (D_80362690->unk0[D_80362690->unk9C].unkC.unk7B != 0) {
        return 0;
    }
    return (unkC->unk2 == 0 || unkC->unk2 == 6);
}

u8 func_8032DE74(void) {
    Unk80362690_Unk0_UnkC* unkC;
    s32 var_v1;

    unkC = &D_80362690->unk0[D_80362690->unk9C].unkC;
    var_v1 = (unkC->unk2 == 0 || unkC->unk2 == 1 || unkC->unk2 == 2 || unkC->unk2 == 6);
    if (levelDataGetFALC(NULL) != 0) {
        var_v1 = 0;
    }
    return var_v1;
}

// populates menu at results screen, showing Check Photo/Replay/Next
void func_8032DF08(void) {
    s32 idx;
    u8* ptr;
    u8 val = 0xE; // fakematch?

    idx = 0;
    if (func_8032DE14() != 0) {
        ptr = levelGet_80345CB0();
        if (ptr[1] == 1) {
            func_803405E4();
        }
        D_8034FFA0[0] = val; // Check Photo
        idx = 1;
    }
    if (func_8032DE74()) {
        D_8034FFA0[idx++] = 0x60; // Replay
    }
    D_8034FFA0[idx++] = 0x5B; // Next
    menuCreateItems(170, 2, 6, 1.0f, 1.0f, D_8034FFA0, idx);
    if (func_8032DE14() && !func_8033F62C()) {
        menu_8030B69C(1);
    }
    func_80312FF8(5);
}

s32 func_8032E000(s32 idx) {
    if (idx < 0) {
        return idx;
    }
    switch (D_8034FFA0[idx]) {
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

void func_8032E060(s32 arg0) {
    s32 val;
    Unk80362690_Unk0_UnkC* unkC;
    s32 i;
    const char* var_s0;
    s32 var_a1;
    s32 var_s3; // point total (out of 100)?
    s16* temp_t0;
    s32 temp_a2;
    s32 strIdx;

    unkC = &D_80362690->unk0[D_80362690->unk9C].unkC;
    var_s3 = 0;
    if (unkC->unk2 == 6) {
        if (arg0 != 0) {
            var_s0 = "BD_ALL_S2";
        } else {
            var_s0 = "BD_ALL_S1";
        }
    } else if (arg0 != 0) {
        var_s0 = D_8034FC40[unkC->unk2][unkC->unk4][unkC->unk6];
    } else {
        var_s0 = D_8034FD60[unkC->unk2][unkC->unk4][unkC->unk6];
    }
    D_80371930 = textGetDataByName(var_s0);
    if (D_80371930 == NULL) {
        D_80371934 = 1;
        D_80371938 = var_s0;
    } else {
        D_80371934 = 0;
    }
    D_8037192C = (arg0 == 0) ? 1.5f : 0.0f;
    if (arg0 != 0) {
        func_8032DF08();
        for (i = 0; i < ARRAY_COUNT(D_8034FFAC); i++) {
            temp_a2 = D_8034FE80[unkC->unk2][unkC->unk4][unkC->unk6][i];
            // unkC->unk4 is class, p40->unk6 * unkC->unk2 is test * vehicle?
            temp_t0 = &D_80364210[D_80362690->unk9C].unk0[unkC->unk4].unk0[unkC->unk6][unkC->unk2 + 1].unk10;
            D_8034FFAC[i][0] = D_8034FFAC[i][1] = D_8034FFAC[i][2] = -3;
            D_8034FFAC[i][3] = 0xFFE;
            D_8034FFAC[i][4] = -1;
            switch (temp_a2) {
            case 1:
                var_a1 = temp_t0[3];
                break;
            case 2:
                var_a1 = temp_t0[2];
                break;
            case 3:
                var_a1 = temp_t0[6];
                break;
            case 4:
                var_a1 = temp_t0[7];
                break;
            case 5:
                var_a1 = temp_t0[11];
                break;
            case 6:
                var_a1 = temp_t0[5];
                break;
            case 7:
                var_a1 = temp_t0[10];
                break;
            case 8:
                var_a1 = temp_t0[16];
                break;
            case 9:
                var_a1 = temp_t0[15];
                break;
            case 11:
                var_a1 = temp_t0[14];
                break;
            case 12:
                var_a1 = D_80364210[D_80362690->unk9C].unk0[unkC->unk4].unk0[0][unkC->unk2 + 1].unk14;
                break;
            case 13:
                var_a1 = D_80364210[D_80362690->unk9C].unk0[unkC->unk4].unk0[1][unkC->unk2 + 1].unk14;
                break;
            case 14:
                var_a1 = D_80364210[D_80362690->unk9C].unk0[unkC->unk4].unk0[2][unkC->unk2 + 1].unk14;
                break;
            case 15:
                var_a1 = D_80364210[D_80362690->unk9C].unk0[unkC->unk4].unk0[3][unkC->unk2 + 1].unk14;
                break;
            case 16:
                var_a1 = temp_t0[13];
                break;
            default:
                continue;
            }

            if (var_a1 == 0x7F) {
                D_8034FFAC[i][0] = D_8034FFAC[i][1] = -3;
                D_8034FFAC[i][1] = 0xFFE;
                D_8034FFAC[i][2] = -1;
            } else {
                var_s3 += var_a1;
                textFmtInt(D_8034FFAC[i], var_a1, 3);
            }
        }

        if (D_80364210[D_80362690->unk9C].unk0[0].unk0[0][1].unk8 != 0) {
            textFmtInt(D_80371940, -D_80364210[D_80362690->unk9C].unk0[0].unk0[0][1].unk8, 3);
            var_s3 += D_80364210[D_80362690->unk9C].unk0[0].unk0[0][1].unk8; // unk38
        } else {
            textFmtInt(D_80371940, (s32)-temp_t0[12], 3);
            var_s3 += temp_t0[12];
        }
        if (var_s3 < 0) {
            var_s3 = 0;
        }
        textFmtInt(D_80371950, var_s3, 3);
        strIdx = (var_s3 == 1) ? 0x8A : 0x131; // "pt." : "pts."
        D_8037193C = textGetDataByIdx(strIdx);
    }
    D_8034FFBC = 0;
}

void func_8032E698(void) {
    func_80312FF8(7);
}

s32 func_8032E6B8(s32 arg0) {
    Unk80362690_Unk0_UnkC* unkC;
    s32 sp18;
    s32 temp_v0_2;

    unkC = &D_80362690->unk0[D_80362690->unk9C].unkC;
    sp18 = 0;
    func_80313D74();
    D_8037192C += D_8034F854;
    if (D_8037192C > 1.5f) {
        D_8037192C = 1.5f;
    }
    if ((arg0 != 0) && (D_8037192C > 0.75f)) {
        sp18 = menu_8030B50C();
        temp_v0_2 = func_8032E000(sp18);
        switch (temp_v0_2) {
        case 2:
            if (D_80362690->unk0[D_80362690->unk9C].unkC.unk7B != 0) {
                return 0xB;
            }
            menuSetProps();
            // FIXME: unkC->pad8B
            if (((unkC->unk2 != 3) || (unkC->pad7C[0xF] != 0)) && (unkC->unk2 != 6)) {
                sp18 = func_803470EC();
            } else {
                sp18 = 2;
            }
            D_8037192C = 1.5f;
            break;
        case 1:
            func_8032C540(D_80362690);
            func_8032EF10(unkC->unk2);
            sp18 = 0;
            D_8037192C = 1.5f;
            break;
        case 0:
            if (func_8033E3A8(2) != 0) {
                // FIXME: unkC->pad8A
                saveFileWrite((s32)unkC->pad7C[0xE]);
            }
            sp18 = 0;
            D_8037192C = 1.5f;
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
            sp18 = 0;
            break;
        }
    } else {
        if (arg0 == 0) {
            D_8037192C = 1.5f;
            demo_80323020();
            if (demoButtonPress(D_80362690->unk9C, A_BUTTON | B_BUTTON | START_BUTTON) != 0) {
                sp18 = 1;
                if (demoButtonPress(D_80362690->unk9C, A_BUTTON | START_BUTTON) != 0) {
                    func_8033F7F8(0x73);
                } else if (demoButtonPress(D_80362690->unk9C, CONT_B) != 0) {
                    func_8033F7F8(1);
                }
            }
        }
    }
    return sp18;
}

void func_8032E940(s32 arg0) {
    Unk80362690_Unk0_UnkC* unkC;
    s32 alpha;
    s32 var_a0;
    s32 var_s1;
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
    spAC = (f32)(1.0 - (f64)((1.5f - D_8037192C) / 1.5f));
    uvVtxBeginPoly();
    alpha = (s32)(130.0f * spAC);
    uvVtx(0, 240, 0, 0, 0, 0, 0, 0, alpha);
    uvVtx(0, 0, 0, 0, 0, 0, 0, 0, alpha);
    uvVtx(320, 0, 0, 0, 0, 0, 0, 0, alpha);
    uvVtx(320, 240, 0, 0, 0, 0, 0, 0, alpha);
    uvVtxEndPoly();
    uvGfxClearFlags(GFX_STATE_400000);
    if ((D_8034FFBC == 0) && (unkC->unk2 != 6)) {
        uvVtxBeginPoly();
        alpha = (s32)(255.0f * spAC);
        uvVtx(0x24, 0x78, 0, 0, 0, 0xD2, 0xD2, 0xD2, alpha);
        uvVtx(0x24, 0x77, 0, 0, 0, 0xD2, 0xD2, 0xD2, alpha);
        uvVtx(0x110, 0x77, 0, 0, 0, 0xD2, 0xD2, 0xD2, alpha);
        uvVtx(0x110, 0x78, 0, 0, 0, 0xD2, 0xD2, 0xD2, alpha);
        uvVtxEndPoly();
    }
    func_803141E4();
    if ((spAC >= 0.5f) && (arg0 != 0)) {
        menuInit();
    }
    if (D_80371934 != 0) {
        uvFontSet(0);
        uvFont_8021956C(0xD2, 0x00, 0xD2, 0xFF);
        uvFont_80219550(1.0, 1.0);
        uvSprintf(sp48, "STR MISSING %s", D_80371938);
        uvFont_80219ACC(0x14, 0x64, sp48);
    } else {
        uvFontSet(6);
        alpha = (s32)(255.0f * spAC);
        uvFont_8021956C(0xD2, 0xD2, 0xD2, alpha);
        uvFont_80219550(1.0, 1.0);

        var_s1 = D_8034FFBC ? 168 : 180;
        var_a0 = D_8034FFBC ? 44 : 28;

        if (D_80371930 != NULL) {
            do {
                var_s2 += func_80219874(var_a0, var_s1, &D_80371930[var_s2], 0xFF, 0xFFE);
                var_s1 -= 16;
            } while (D_80371930[var_s2] != -1);
        } else {
            _uvDebugPrintf("Null Kanji string in screv screen\n");
        }
    }
    if ((arg0 != 0) && (D_8034FFBC == 0) && (unkC->unk2 != 6)) {
        uvFontSet(6);
        alpha = (s32)(255.0f * spAC);
        uvFont_8021956C(0xD2, 0xD2, 0xD2, alpha);
        uvFont_80219550(1.0, 1.0);

        for (i = 0, var_s1 = 116; i < 4; i++, var_s1 += 16) {
            func_80219874(180, var_s1, D_8034FFAC[i], 3, 0xFFE);
        }

        if ((unkC->unk2 == 3) || (unkC->unk2 == 0) || (unkC->unk2 == 4)) {
            func_80219874(180, 100, &D_80371950, 3, 0xFFE);
            func_80219874(216, 100, D_8037193C, 4, 0xFFE);
        } else {
            func_80219874(180, 84, D_80371950, 3, 0xFFE);
            func_80219874(216, 84, D_8037193C, 4, 0xFFE);
        }

        if ((unkC->unk2 != 3) && (unkC->unk2 != 0) && (unkC->unk2 != 4)) {
            func_80219874(180, 100, D_80371940, 4, 0xFFE);
        }
    }
    uvFont_80219EA8();
}

void func_8032EF10(s32 arg0) {
    s16* text;
    char str[256];
    s32 i;

    if (D_8034FFC0 == 0) {
        for (i = 0; i < 3; i++) {
            D_8037195A[i] = (s8)((s32)((uvRandF_RANLUX() * 14.0f) + 0.5f) + 1);
        }
        D_8034FFC0 = 1;
    }

    if (arg0 >= 3) {
        return;
    }

    D_8037195A[arg0]++;
    if (D_8037195A[arg0] >= 16) {
        D_8037195A[arg0] = 1;
    }
    uvSprintf(str, "%s_%d_A", D_80350998[arg0], D_8037195A[arg0]);
    text = textGetDataByName(str);
    if (text == NULL) {
        _uvDebugPrintf("Could not find %s in jtext\n", str);
    } else {
        D_80371930 = text;
        D_8034FFBC = 1;
    }
}
