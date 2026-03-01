#include "common.h"
#include "code_66160.h"
#include "code_99D40.h"
#include "code_9A960.h"
#include "code_A6000.h"
#include "code_A64C0.h"
#include "code_C9B60.h"
#include "code_D2B10.h"
#include "demo.h"
#include "menu.h"
#include "snd.h"
#include "spath.h"
#include "user_paths.h"
#include <uv_graphics.h>
#include <uv_matrix.h>
#include <uv_dobj.h>
#include <uv_memory.h>
#include <uv_audio.h>
#include <uv_clocks.h>
#include <uv_font.h>

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    Mtx4F unk2C;
    Mtx4F unk6C;
    Mtx4F unkAC;
    Mtx4F unkEC;
    Mtx4F unk12C;
    Mtx4F unk16C;
    Mtx4F unk1AC;
    Mtx4F unk1EC;
    f32 unk22C;
    f32 unk230;
    f32 unk234;
    f32 unk238;
    f32 unk23C;
    Unk8037DCA0* unk240[6];
    u16 unk258[6];
    u8 unk264;
    u8 unk265;
    u8 unk266;
} Unk80378CE0; // size = 0x268

// .data
u8 D_80350690 = 1;
s32 D_80350694 = 1;
s32 D_80350698[] = { 0x188, 0x4E };

// .bss
Unk80378CE0* D_80378CE0;
f32 D_80378CE4;

// forward decls
static void func_803427FC(void);
static void func_80343294(void);
static s32 func_80343550(void);
static void introSceneRunner(void);
static void func_803433A4(void);
static void func_80343B5C(void);
static void func_80343C44(void);
static void func_80343E84(void);
static void func_8034411C(void);

s32 func_80342630(void) {
    f32 var_fs0;
    f32 var_fs1;
    s32 var_s1;

    var_fs0 = 3.1415927f;
    var_fs1 = 0.0f;
    D_80378CE4 = 0 /*.0f*/;
    func_803427FC();

    do {
        uvMat4SetIdentity(&D_80378CE0->unk1EC);
        var_fs0 += D_80378CE0->unk23C * D_8034F854;
        uvMat4RotateAxis(&D_80378CE0->unk1EC, var_fs0, 'z');
        if (var_fs0 < -6.2831855f) {
            var_fs0 += 6.2831855f;
        }
        var_s1 = func_80343550();
        uvGfxBegin();
        introSceneRunner();
        uvGfxEnd();
        if (D_80378CE0->unk28 >= 7) {
            if (D_80378CE4 == 0.0f) {
                D_80378CE4 = D_8034F850 + 20.0f;
            }
            if (D_80378CE4 <= D_8034F850) {
                var_fs1 = 1.0f;
            }
        }
    } while (var_s1 == 0 && var_fs1 == 0.0f);

    D_80350694 += 1;
    func_80343294();
    if (var_fs1 != 0.0f) {
        var_s1 = 8;
    }

    return var_s1;
}

static void func_803427FC(void) {
    Mtx4F sp58;
    Unk802D3658_Arg0* sp54;
    s32 var_v0;

    D_80378CE0 = (Unk80378CE0*)_uvMemAllocAlign8(sizeof(Unk80378CE0));
    uvMemSet(D_80378CE0, 0U, 0x268U);
    uvSprtProps(1, 3, 1, 2, 0x21, 0x96, 9, 9, 0xA, 0, 0xB, 1, 0);
    uvSprtProps(3, 3, 1, 2, 0x11B, 0xD5, 9, 0xA, 0);
    uvSprtProps(4, 3, 1, 2, 0x21, 0x1E, 9, 0x1E, 0);
    sp54 = D_80362690->unk0[D_80362690->unk9C].unkC.unk70;
    func_80204BD4(sp54->unk22C, 1, 1.0f);
    func_80204A8C(sp54->unk22C, 1);
    uvChanEnv(sp54->unk22C, 0x17);
    func_80204C94(sp54->unk22C, -0.7009346f, 0.7009346f, -0.5f, 0.5f, 1.0f, 4000.0f);
    func_80204AB0(sp54->unk22C, 1, func_8034B6F8);
    D_80378CE0->unk14 = func_80340668(0x43);
    D_80378CE0->unk18 = func_80340668(0x44);
    D_80378CE0->unk1C = func_80340668(0x45);
    D_80378CE0->unk20 = func_80340668(0x46);
    D_80378CE0->unk24 = func_80340668(0x47);
    uvMat4SetIdentity(&sp54->unk108);
    spath_update(&sp54->unk108, D_80378CE0->unk14, 0, 1.0f);
    spath_update(&D_80378CE0->unk2C, D_80378CE0->unk18, 0, 1.0f);
    spath_update(&D_80378CE0->unk6C, D_80378CE0->unk18, 0, 1.0f);
    spath_update(&D_80378CE0->unkAC, D_80378CE0->unk18, 0, 1.0f);
    spath_update(&D_80378CE0->unkEC, D_80378CE0->unk18, 0, 1.0f);
    D_80378CE0->unk0 = uvDobjAllocIdx();
    uvDobjModel(D_80378CE0->unk0, 0x28);
    uvMat4SetIdentity(&sp58);
    uvDobjPosm(D_80378CE0->unk0, 0, &sp58);
    D_80378CE0->unk4 = uvDobjAllocIdx();
    uvDobjModel(D_80378CE0->unk4, 0x157);
    uvDobjPosm(D_80378CE0->unk4, 0, &D_80378CE0->unk2C);
    uvDobjState(D_80378CE0->unk4, 2);
    D_80378CE0->unk8 = uvDobjAllocIdx();
    uvDobjModel(D_80378CE0->unk8, 0xCD);
    uvDobjPosm(D_80378CE0->unk8, 0, &D_80378CE0->unk6C);
    uvDobjState(D_80378CE0->unk8, 2);
    D_80378CE0->unkC = uvDobjAllocIdx();
    uvDobjModel(D_80378CE0->unkC, 0x158);
    uvDobjPosm(D_80378CE0->unkC, 0, &D_80378CE0->unkAC);
    uvDobjState(D_80378CE0->unkC, 2);
    D_80378CE0->unk10 = uvDobjAllocIdx();
    uvDobjModel(D_80378CE0->unk10, 0x159);
    uvDobjPosm(D_80378CE0->unk10, 0, &D_80378CE0->unkEC);
    uvDobjState(D_80378CE0->unk10, 2);
    menuCreateItems(0x66, 0x3C, 6, 1.0f, 1.0f, D_80350698, 2);
    func_80312F5C(0, 0xFF, 0xFF, 0);
    func_80312F5C(1, 0xFF, 0xFF, 0xFF);
    func_80312F5C(2, 0xFF, 0xFF, 0);
    D_80378CE0->unk265 = D_80350690;
    D_80378CE0->unk266 = D_80350690;
    uvaSeqSetTempo(110.0f);
    if (D_80350690 != 0) {
        D_80378CE0->unk23C = -0.5236f;
        var_v0 = 0;
        D_80378CE0->unk22C = 0.0f;
        D_80378CE0->unk28 = 1;
    } else {
        D_80378CE0->unk23C = -0.17453f;
        D_80378CE0->unk22C = 16.65f;
        D_80378CE0->unk28 = 7;
        func_80344258(1);
        var_v0 = 1;
    }
    if (var_v0 != D_803505B0) {
        func_8033F748(var_v0);
        func_8033F964(0);
        func_8033FA88(0.75f);
        func_8033FCD0(0xFFU);
    }
}

static void func_80342D2C(void) {
    Unk803136C4_Arg0 sp2FC;
    s32 allocIdx;
    s32 i;

    D_80378CE0->unk240[0] = userPath_8034A4F8(0x48);
    D_80378CE0->unk240[1] = userPath_8034A4F8(0x49);
    D_80378CE0->unk240[2] = userPath_8034A4F8(0x4A);
    D_80378CE0->unk240[3] = userPath_8034A4F8(0x4B);
    D_80378CE0->unk240[4] = userPath_8034A4F8(0x4C);
    D_80378CE0->unk240[5] = userPath_8034A4F8(0x4D);
    func_8031EF60(D_80378CE0->unk240[0], 0x127);
    func_8031EF60(D_80378CE0->unk240[1], 0x12B);
    func_8031EF60(D_80378CE0->unk240[2], 0x12D);
    func_8031EF60(D_80378CE0->unk240[3], 0x12F);
    func_8031EF60(D_80378CE0->unk240[4], 0x131);
    func_8031EF60(D_80378CE0->unk240[5], 0x133);
    uvMat4SetIdentity(&D_80378CE0->unk16C);
    uvMat4RotateAxis(&D_80378CE0->unk16C, -1.4835305f, 'x');
    uvMat4RotateAxis(&D_80378CE0->unk16C, 3.141594f, 'y');

#define placeInUserPath(idx, modelId)                              \
    allocIdx = uvDobjAllocIdx();                                   \
    D_80378CE0->unk258[(idx)] = allocIdx;                          \
    D_80378CE0->unk240[(idx)]->unk352 = allocIdx;                  \
    uvDobjModel(D_80378CE0->unk258[(idx)], (modelId));             \
    userPath_8034A950(D_80378CE0->unk240[(idx)]->unk4C, &sp2FC);   \
    func_803136C4(&sp2FC, &D_80378CE0->unk12C);                    \
    uvDobjPosm(D_80378CE0->unk258[(idx)], 0, &D_80378CE0->unk12C); \
    uvDobjState(D_80378CE0->unk258[(idx)], 2);

    placeInUserPath(0, 0x127);
    placeInUserPath(1, 0x12B);
    placeInUserPath(2, 0x12D);
    placeInUserPath(3, 0x12F);
    placeInUserPath(4, 0x131);
    placeInUserPath(5, 0x133);

    for (i = 0; i < ARRAY_COUNT(D_80378CE0->unk240); i++) {
        userPath_8034A8B0(D_80378CE0->unk240[i], 0, 0.0f);
    }
    func_8031EF90(2);
}

static void func_80343294(void) {
    func_803433A4();
    uvDobjModel(D_80378CE0->unk0, WORLD_MODEL_ID);
    uvDobjModel(D_80378CE0->unk4, WORLD_MODEL_ID);
    uvDobjModel(D_80378CE0->unk8, WORLD_MODEL_ID);
    uvDobjModel(D_80378CE0->unkC, WORLD_MODEL_ID);
    uvDobjModel(D_80378CE0->unk10, WORLD_MODEL_ID);
    spath_free(D_80378CE0->unk14);
    spath_free(D_80378CE0->unk18);
    spath_free(D_80378CE0->unk1C);
    spath_free(D_80378CE0->unk20);
    spath_free(D_80378CE0->unk24);
    uvSprtProps(1, 3, 0, 0);
    uvSprtProps(2, 3, 0, 0);
    uvSprtProps(3, 3, 0, 0);
    uvSprtProps(4, 3, 0, 0);
    menuSetProps();
}

static void func_803433A4(void) {
    Unk8037DCA0* temp_a0;

    temp_a0 = D_80378CE0->unk240[0];
    if (temp_a0 != NULL) {
        func_8031EF68(temp_a0);
        uvDobjModel(D_80378CE0->unk258[0], WORLD_MODEL_ID);
        userPathFree(0);
        func_8031EF68(D_80378CE0->unk240[1]);
        uvDobjModel(D_80378CE0->unk258[1], WORLD_MODEL_ID);
        userPathFree(1);
        func_8031EF68(D_80378CE0->unk240[2]);
        uvDobjModel(D_80378CE0->unk258[2], WORLD_MODEL_ID);
        userPathFree(2);
        func_8031EF68(D_80378CE0->unk240[3]);
        uvDobjModel(D_80378CE0->unk258[3], WORLD_MODEL_ID);
        userPathFree(3);
        func_8031EF68(D_80378CE0->unk240[4]);
        uvDobjModel(D_80378CE0->unk258[4], WORLD_MODEL_ID);
        userPathFree(4);
        func_8031EF68(D_80378CE0->unk240[5]);
        uvDobjModel(D_80378CE0->unk258[5], WORLD_MODEL_ID);
        userPathFree(5);
        D_80378CE0->unk240[0] = NULL;
        D_80378CE0->unk240[1] = NULL;
        D_80378CE0->unk240[2] = NULL;
        D_80378CE0->unk240[3] = NULL;
        D_80378CE0->unk240[4] = NULL;
        D_80378CE0->unk240[5] = NULL;
        func_8031FE18(2);
    }
}

void func_803434E8(void) {
    uvClkReset(4);
    while (uvClkGetSec(4) < 1.0) { }
}

static s32 func_80343550(void) {
    s32 temp_v0;
    s32 sp18;

    sp18 = 0;
    func_80313D74();
    if (D_80350694 != 0 && D_80378CE0->unk28 < 7) {
        demo_80323020();
        if (demoButtonPress(D_80362690->unk9C, A_BUTTON | B_BUTTON | START_BUTTON) != 0) {
            if (demoButtonPress(D_80362690->unk9C, A_BUTTON | START_BUTTON) != 0) {
                snd_play_sfx(0x6EU);
            } else if (demoButtonPress(D_80362690->unk9C, B_BUTTON) != 0) {
                snd_play_sfx(1U);
            }
            if (D_80378CE0->unk264 != 0) {
                sp18 = 10;
            } else {
                D_80378CE0->unk264 = 1;
                D_80378CE0->unk23C = -0.17453f;
                D_80378CE0->unk22C = 16.65f;
                D_80378CE0->unk28 = 7;
                func_803433A4();
                if (D_803505B0 != 1) {
                    func_8033F964(1);
                    func_8033F748(1);
                    func_8033F964(0);
                }
                D_80378CE0->unk265 = 0;
                D_80378CE0->unk266 = 0;
            }
        }
    }

    switch (D_80378CE0->unk28) {
    case 1:
        if (D_80378CE0->unk22C > 4.65f) {
            D_80378CE0->unk28 = 2;
        }
        break;
    case 2:
        func_80342D2C();
        D_80378CE0->unk234 = D_80378CE0->unk22C;
        D_80378CE0->unk28 = 3;
        D_80378CE0->unk23C = -0.17453f;
        break;
    case 3:
        if (D_80378CE0->unk22C > 9.65f) {
            D_80378CE0->unk28 = 4;
            break;
        }
        break;
    case 4:
        func_803433A4();
        D_80378CE0->unk238 = D_80378CE0->unk22C;
        D_80378CE0->unk28 = 5;
        break;
    case 5:
        if (D_80378CE0->unk22C > 14.65f) {
            D_80378CE0->unk28 = 6;
            break;
        }
        break;
    case 6:
        D_80378CE0->unk28 = 7;
        D_80378CE0->unk230 = D_80378CE0->unk22C;
        break;
    case 8:
        if (uvClkGetSec(4) >= 1.0) {
            sp18 = 10;
        }
        break;
    }
    if (D_80378CE0->unk28 > 0) {
        func_80343B5C();
    }
    if (D_80378CE0->unk28 == 3) {
        func_80343C44();
    }
    if (D_80378CE0->unk28 >= 5) {
        func_80343E84();
    }
    if (D_80378CE0->unk28 >= 7) {
        func_8034411C();
    }
    if (D_80378CE0->unk22C >= 16.65f && D_80378CE0->unk28 != 8) {
        func_80312FF8(5);
        temp_v0 = menu_8030B50C();
        if (temp_v0 == -3) {
            D_80378CE0->unk22C = 16.65f;
            D_80378CE4 = 0.0f;
        }
        switch (temp_v0) {
        case 0:
            uvClkReset(4);
            D_80378CE0->unk28 = 8;
            break;
        case 1:
            sp18 = 7;
            break;
        case -1:
            break;
        }
    }
    D_80378CE0->unk22C += D_8034F854;
    return sp18;
}

static void introSceneRunner(void) {
    Unk802D3658_Arg0* temp = D_80362690->unk0[D_80362690->unk9C].unkC.unk70;
    s32 sp30;

    func_80204FC4(temp->unk22C);
    if (D_80378CE0->unk28 < 7) {
        return;
    }

    uvSprtDraw(1);
    uvSprtDraw(3);
    if ((D_80378CE0->unk22C - D_80378CE0->unk230) <= 2.0f) {
        sp30 = (s32)(((D_80378CE0->unk22C - D_80378CE0->unk230) * 80.0f) + 0.5f) * (1.0f / 2.0f);
        if (sp30 < 0) {
            sp30 = 0;
        }
        if (sp30 > 0x50) {
            sp30 = 0x50;
        }
    } else {
        sp30 = 0x50;
    }

    screenDrawBoxSetup();
    screenDrawBox(30, 18, 285, 34, 0, 0, 0, sp30);
    screenDrawBox(97, 76, 202, 118, 0, 0, 0, sp30);
    func_802DFA18();
    if (D_80378CE0->unk22C >= 16.65f) {
        menuInit();
    }

    uvFont_80219EA8();
    uvSprtDraw(4);
}

static void func_80343B5C(void) {
    f32 f0;
    Unk802D3658_Arg0* sp20;

    sp20 = D_80362690->unk0[D_80362690->unk9C].unkC.unk70;
    f0 = ((1.0 - ((4.65f - D_80378CE0->unk22C) / 4.65f)) * 100.0);
    spath_update(&sp20->unk108, D_80378CE0->unk14, f0, 1.0f);
    uvMat4Copy(&D_80378CE0->unk1AC, &sp20->unk108);
    uvMat4Mul(&sp20->unk108, &sp20->unk108, &D_80378CE0->unk1EC);
    func_80204B34(sp20->unk22C, &sp20->unk108);
}

static void func_80343C44(void) {
    s32 i;
    Mtx4F spCC;
    Mtx4F sp8C;
    Unk802D3658_Arg0* temp = D_80362690->unk0[D_80362690->unk9C].unkC.unk70;
    f32 f0;
    f32 var_fs0;

    f0 = D_80378CE0->unk22C - D_80378CE0->unk234;
    var_fs0 = (f0) / 5.0f;
    for (i = 0; i < ARRAY_COUNT(D_80378CE0->unk240); i++) {
        if (var_fs0 < 0.6f) {
            var_fs0 *= 1.25;
        } else {
            var_fs0 = ((var_fs0 - 0.6f) * 0.625f) + 0.75f;
        }
        userPath_8034A8B0(D_80378CE0->unk240[i], 1U, var_fs0);
        uvDobjGetPosm(D_80378CE0->unk240[i]->unk352, 0, &spCC);
        uvMat4Copy(&sp8C, &D_80378CE0->unk1AC);
        sp8C.m[3][0] = 0.0f;
        sp8C.m[3][1] = 0.0f;
        sp8C.m[3][2] = 0.0f;
        uvMat4MulBA(&spCC, &sp8C, &spCC);
        spCC.m[3][0] += D_80378CE0->unk1AC.m[3][0] - 15.0f;
        spCC.m[3][1] += D_80378CE0->unk1AC.m[3][1];
        spCC.m[3][2] += D_80378CE0->unk1AC.m[3][2];
        uvMat4Mul(&spCC, &D_80378CE0->unk16C, &spCC);
        uvMat4Mul(&spCC, &spCC, &D_80378CE0->unk1EC);
        uvDobjPosm(D_80378CE0->unk240[i]->unk352, 0, &spCC);
        func_8031FA0C(2, i, i, D_80378CE0->unk240[i]->unk352, &spCC, &temp->unk108);
    }
}

static void func_80343E84(void) {
    f32 sp2C;
    f32 temp_fs0;

    temp_fs0 = D_80378CE0->unk22C - D_80378CE0->unk238;
    if (temp_fs0 >= 0.0f) {
        sp2C = ((temp_fs0 - 0.0f) * 100.0f) / 1.5f;
        spath_update(&D_80378CE0->unk2C, D_80378CE0->unk18, sp2C, 1.0f);
        uvMat4Mul(&D_80378CE0->unk2C, &D_80378CE0->unk2C, &D_80378CE0->unk1EC);
        uvDobjPosm(D_80378CE0->unk4, 0, &D_80378CE0->unk2C);
    }
    if (temp_fs0 >= (0.5f * 3)) {
        sp2C = ((temp_fs0 - (0.5f * 3)) * 100.0f) / 2 /*.0f*/;
        spath_update(&D_80378CE0->unk6C, D_80378CE0->unk1C, sp2C, 1.0f);
        uvMat4Mul(&D_80378CE0->unk6C, &D_80378CE0->unk6C, &D_80378CE0->unk1EC);
        uvDobjPosm(D_80378CE0->unk8, 0, &D_80378CE0->unk6C);
    }
    if (temp_fs0 >= 3.5f) {
        sp2C = ((temp_fs0 - 3.5f) * 100.0f) / 0.5f;
        spath_update(&D_80378CE0->unkAC, D_80378CE0->unk20, sp2C, 1.0f);
        uvMat4Mul(&D_80378CE0->unkAC, &D_80378CE0->unkAC, &D_80378CE0->unk1EC);
        uvDobjPosm(D_80378CE0->unkC, 0, &D_80378CE0->unkAC);
        if ((D_80378CE0->unk265 != 0) && (sp2C > 40.0f)) {
            snd_play_sfx(0x3DU);
            D_80378CE0->unk265 = 0;
        }
    }
    if (temp_fs0 >= 4.0f) {
        sp2C = ((temp_fs0 - 4.0f) * 100.0f) / 0.5f;
        spath_update(&D_80378CE0->unkEC, D_80378CE0->unk24, sp2C, 1.0f);
        uvMat4Mul(&D_80378CE0->unkEC, &D_80378CE0->unkEC, &D_80378CE0->unk1EC);
        uvDobjPosm(D_80378CE0->unk10, 0, &D_80378CE0->unkEC);
        if ((D_80378CE0->unk266 != 0) && (sp2C > 47.0f)) {
            snd_play_sfx(0x3DU);
            D_80378CE0->unk266 = 0;
        }
    }
}

static void func_8034411C(void) {
    f32 temp_fv0;
    s32 var_s0;

    temp_fv0 = D_80378CE0->unk22C - D_80378CE0->unk230;
    if (temp_fv0 <= 2.0f) {
        var_s0 = (s32)((s32)((temp_fv0 * 255.0f) + 0.5f) * (1.0f / 2.0f));
        if (var_s0 < 0) {
            var_s0 = 0;
        }
        if (var_s0 > 0xFF) {
            var_s0 = 0xFF;
        }
    } else {
        var_s0 = 0xFF;
    }
    uvSprtProps(1, 7, 0xFF, 0xFF, 0xFF, var_s0, 0);
    uvSprtProps(2, 7, 0xFF, 0xFF, 0xFF, var_s0, 0);
    uvSprtProps(3, 7, 0xFF, 0xFF, 0xFF, var_s0, 0);
    uvSprtProps(4, 7, 0xFF, 0xFF, 0xFF, var_s0, 0);
}

void func_80344258(u8 arg0) {
    if (arg0) {
        D_80350690 = 1;
    } else {
        D_80350690 = 0;
    }
}

