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
#include "demo.h"
#include "menu.h"
#include "save.h"
#include "snap.h"
#include "snow.h"
#include "snd.h"
#include "results.h"
#include "text_data.h"

extern const char* D_8034FC40[6][4][3];
extern const char* D_8034FD60[6][4][3];
extern u8 D_8034FE80[6][4][3][4];
extern s32 D_8034FFA0[3]; // gResultsMenu
extern s16* D_8034FFAC[4];
extern s32 D_8034FFBC;
extern s32 D_8034FFC0;
extern const char* D_80350998[];

extern f32 D_8037192C;
extern u8 D_80371934;
extern const char* D_80371938;
extern s16* D_80371930;
extern s16* D_8037193C;
extern s16 D_80371940[];
extern s16 D_80371950[];
extern u8 D_8037195A[];

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

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_803556B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_803556B8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_803556C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_803556D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_803556DC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_803556E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_803556F4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355700.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_8035570C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355718.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355720.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_8035572C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355738.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355744.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355750.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_8035575C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355768.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355774.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355780.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355788.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355794.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_803557A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_803557AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_803557B8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_803557C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_803557D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_803557DC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_803557E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_803557F4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355800.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_8035580C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355818.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355824.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355830.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_8035583C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355848.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355854.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355860.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_8035586C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355878.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355884.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355890.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_8035589C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_803558A8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_803558B4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_803558C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_803558CC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_803558D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_803558E4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_803558F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_803558FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355908.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355914.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355920.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_8035592C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355938.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355944.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355950.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_8035595C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355968.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355974.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355980.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_8035598C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355998.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_803559A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_803559AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_803559B8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_803559C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_803559D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_803559DC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_803559E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_803559F4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355A00.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355A08.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355A14.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355A20.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355A2C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355A38.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355A44.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355A50.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355A5C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355A68.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355A70.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355A7C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355A88.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355A94.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355AA0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355AAC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355AB8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355AC4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355AD0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355ADC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355AE8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355AF4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355B00.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355B0C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355B18.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355B24.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355B30.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355B3C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355B48.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355B54.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355B60.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355B6C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355B78.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355B84.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355B90.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355B9C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355BA8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355BB4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355BC0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355BCC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355BD8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355BE4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355BF0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355BFC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355C08.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355C14.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355C20.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/results/D_80355C2C.s")

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
