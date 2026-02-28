#include "common.h"
#include "code_C9B60.h"
#include "code_99D40.h"
#include "code_9A960.h"
#include "code_A6000.h"
#include "code_A64C0.h"
#include "code_D2B10.h"
#include "menu.h"
#include "snd.h"
#include "spath.h"
#include "user_paths.h"
#include <uv_graphics.h>
#include <uv_matrix.h>
#include <uv_dobj.h>
#include <uv_memory.h>
#include <uv_audio.h>

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
    u8 pad1AC[0x1EC - 0x1AC];
    Mtx4F unk1EC;
    f32 unk22C;
    u8 pad230[0x23C - 0x230];
    f32 unk23C;
    Unk8037DCA0* unk240[6];
    u16 unk258[6];
    u8 pad264;
    s8 unk265;
    s8 unk266;
} Unk80378CE0; // size = 0x268

// .data
u8 D_80350690 = 1;
s32 D_80350694 = 1;
s32 D_80350698[] = { 0x188, 0x4E };

// .bss
extern f32 D_8034F850;
extern f32 D_8034F854;
extern Unk80378CE0* D_80378CE0;
extern f32 D_80378CE4;

// forward decls
static void func_803427FC(void);
static void func_80343294(void);
/* static */ s32 func_80343550(void);
/* static */ void introSceneRunner(void);
/* static */ void func_80344258(s32);
/* static */ void func_803433A4(void);

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
        uvMat4RotateAxis(&D_80378CE0->unk1EC, var_fs0, 0x7A);
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
        func_8033F748(var_v0 & 0xFFFF);
        func_8033F964(0);
        func_8033FA88(0.75f);
        func_8033FCD0(0xFFU);
    }
}

/* static */ void func_80342D2C(void) {
    s32 allocIdx;
    s32 pad[5];
    f32 sp2FC;
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
    uvMat4RotateAxis(&D_80378CE0->unk16C, -1.4835305f, 0x78);
    uvMat4RotateAxis(&D_80378CE0->unk16C, 3.141594f, 0x79);

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

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_C9B60/func_803433A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_C9B60/func_803434E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_C9B60/func_80343550.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_C9B60/introSceneRunner.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_C9B60/func_80343B5C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_C9B60/func_80343C44.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_C9B60/func_80343E84.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_C9B60/func_8034411C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_C9B60/func_80344258.s")
