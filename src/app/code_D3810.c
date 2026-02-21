#include "common.h"
#include "code_D3810.h"
#include "code_9A960.h"
#include <uv_dobj.h>
#include <uv_matrix.h>
#include <uv_model.h>
#include <uv_janim.h>
#include "proxanim.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    Vec3F unk8;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
} Unk8037F450;

// .data
extern s32 D_803509F0;   // = 0;
extern Vec3F D_803509F8; // = {1156.66f, 1770.82f, 0.0f};

// .bss
extern Unk8037F450 D_8037F450[5];
extern s32 D_8037F504;

static void func_8034C2E0(s32 arg0) {
    Mtx4F sp30;
    s32 v1;
    s32 v0;
    f32 sp24;

    uvMat4SetIdentity(&sp30);
    uvMat4UnkOp2(&sp30, D_8037F450[arg0].unk8.x, D_8037F450[arg0].unk8.y, D_8037F450[arg0].unk8.z);
    uvMat4UnkOp2(&sp30, 0.0f, 0.0f, D_8037F450[arg0].unk20);
    uvMat4RotateAxis(&sp30, D_8037F450[arg0].unk1C * 0.01745329f, 'z');
    uvMat4UnkOp2(&sp30, D_8037F450[arg0].unk14, 0.0f, 0.0f);
    uvDobjPosm(D_8037F450[arg0].unk0, 0, &sp30);
    if (D_8037F450[arg0].unk4 != 0xFFFF) {
        uvMat4SetIdentity(&sp30);
        uvMat4UnkOp2(&sp30, D_8037F450[arg0].unk8.x, D_8037F450[arg0].unk8.y, D_8037F450[arg0].unk8.z);
        uvMat4RotateAxis(&sp30, D_8037F450[arg0].unk1C * 0.01745329f, 'z');
        uvMat4UnkOp2(&sp30, D_8037F450[arg0].unk14, 0.0f, 0.0f);
        uvDobjPosm(D_8037F450[arg0].unk4, 0, &sp30);
    }

    v0 = ((D_8037F450[arg0].unk1C + 15.0f) / 30);
    v1 = (s32)(D_8037F450[arg0].unk1C + 15.0f) % 30;

    if (v0 % 2) {
        sp24 = (30.0f - v1) / 30.0f;
    } else {
        sp24 = v1 / 30.0f;
    }
    func_80200B00(D_8037F450[arg0].unk0, 0, 1.0f - sp24);
    uvModelGetPosm(0xD7, 1, &sp30);
    uvMat4UnkOp3(&sp30, 2.0 * sp24, 2.0 * sp24, 2.0 * sp24);
    uvDobjPosm(D_8037F450[arg0].unk0, 1, &sp30);
}

static void func_8034C520(void) {
    Unk8037F450* var_s0;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_8037F450); i++) {
        if (D_8037F450[i].unk18 == 1.0f) {
            D_8037F450[i].unk20 += 4.0f * D_8034F854;
            if (D_8037F450[i].unk20 > 0.0f) {
                D_8037F450[i].unk18 = 2.0f;
                D_8037F450[i].unk20 = 0.0f;
            }
            D_8037F450[i].unk1C += 10.0f * D_8034F854;
            if (D_8037F450[i].unk1C > 360.0f) {
                D_8037F450[i].unk1C -= 360.0f;
            }
            func_8034C2E0(i);
        } else if (D_8037F450[i].unk18 == 2.0f) {
            D_8037F450[i].unk20 -= 4.0f * D_8034F854;
            if (D_8037F450[i].unk20 < -25.0f) {
                D_8037F450[i].unk18 = 1.0f;
            }
            D_8037F450[i].unk1C += 10.0f * D_8034F854;
            if (D_8037F450[i].unk1C > 360.0f) {
                D_8037F450[i].unk1C -= 360.0f;
            }
            func_8034C2E0(i);
        }
    }
}

static s32 func_8034C6CC(s32 arg0, s32 arg1, s32 arg2) {
    Unk8037F450* var_s0;
    s32 i;

    switch (arg1) {
    case 0:
        for (i = 0; i < ARRAY_COUNT(D_8037F450); i++) {
            var_s0 = &D_8037F450[i];
            uvDobjState(var_s0->unk0, 3);
            if (var_s0->unk4 != 0xFFFF) {
                uvDobjState(var_s0->unk4, 0x22);
            }
        }
        break;
    case 2:
        for (i = 0; i < ARRAY_COUNT(D_8037F450); i++) {
            var_s0 = &D_8037F450[i];
            uvDobjState(var_s0->unk0, 0);
            if (var_s0->unk4 != 0xFFFF) {
                uvDobjState(var_s0->unk4, 0);
            }
        }
        break;
    case 3:
        for (i = 0; i < ARRAY_COUNT(D_8037F450); i++) {
            var_s0 = &D_8037F450[i];
            uvDobjState(var_s0->unk0, 3);
            if (var_s0->unk4 != 0xFFFF) {
                uvDobjState(var_s0->unk4, 0x22);
            }
        }
        break;
    }
    return 0;
}

static s32 func_8034C7F0(s32 arg0, s32 arg1, s32 arg2) {
    s32 pad;
    s32 sp18;

    sp18 = 0;
    if (func_80321420(arg0) > 1750.0f) {
        sp18 = 2;
    } else {
        func_8034C520();
    }
    return sp18;
}

void func_8034C848(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_8037F450); i++) {
        switch (i) {
        case 0:
            D_8037F450[i].unk1C = 10.0f;
            D_8037F450[i].unk20 = -25.0f;
            D_8037F450[i].unk18 = 1.0f;
            break;
        case 1:
            D_8037F450[i].unk1C = 20.0f;
            D_8037F450[i].unk20 = -5.0f;
            D_8037F450[i].unk18 = 1.0f;
            break;
        case 2:
            D_8037F450[i].unk1C = 50.0f;
            D_8037F450[i].unk20 = 0.0f;
            D_8037F450[i].unk18 = 1.0f;
            break;
        case 3:
            D_8037F450[i].unk1C = 85.0f;
            D_8037F450[i].unk20 = -15.0f;
            D_8037F450[i].unk18 = 1.0f;
            break;
        case 4:
            D_8037F450[i].unk1C = 110.0f;
            D_8037F450[i].unk20 = -15.0f;
            D_8037F450[i].unk18 = 2.0f;
            break;
        }
        D_8037F450[i].unk0 = 0xFFFF;
        D_8037F450[i].unk4 = 0xFFFF;
    }
}

void func_8034C964(void) {
    s32 i;
    Vec3F sp70 = D_803509F8;

    D_803509F0 = func_80321210(func_8034C7F0, func_8034C6CC, sp70, 1750.0f, 0.0f, 0);
    for (i = 0; i < ARRAY_COUNT(D_8037F450); i++) {
        D_8037F450[i].unk4 = uvDobjAllocIdx();
        if (D_8037F450[i].unk4 != 0xFFFF) {
            uvDobjModel(D_8037F450[i].unk4, 0xD8);
            uvDobjState(D_8037F450[i].unk4, 0);
        }
        D_8037F450[i].unk0 = uvDobjAllocIdx();
        if (D_8037F450[i].unk0 == 0xFFFF) {
            if (D_8037F450[i].unk4 != 0xFFFF) {
                uvDobjModel(D_8037F450[i].unk4, 0xFFFF);
                D_8037F450[i].unk4 = 0xFFFF;
            }
        } else {
            uvDobjModel(D_8037F450[i].unk0, 0xD7);
            uvDobjState(D_8037F450[i].unk0, 0);
            switch (i) {
            case 0:
                D_8037F450[i].unk14 = 195.0f;
                D_8037F450[i].unk8.f[0] = 1156.66f;
                D_8037F450[i].unk8.f[1] = 1770.82f;
                D_8037F450[i].unk8.f[2] = 0.0f;
                break;
            case 1:
                D_8037F450[i].unk8.f[0] = 1156.66f;
                D_8037F450[i].unk8.f[1] = 1770.82f;
                D_8037F450[i].unk8.f[2] = 0.0f;
                D_8037F450[i].unk14 = 220.0f;
                break;
            case 2:
                D_8037F450[i].unk8.f[0] = 1156.66f;
                D_8037F450[i].unk8.f[1] = 1770.82f;
                D_8037F450[i].unk8.f[2] = 0.0f;
                D_8037F450[i].unk14 = 230.0f;
                break;
            case 3:
                D_8037F450[i].unk14 = 180.0f;
                D_8037F450[i].unk8.f[0] = 1156.66f;
                D_8037F450[i].unk8.f[1] = 1770.82f;
                D_8037F450[i].unk8.f[2] = 0.0f;
                break;
            case 4:
                D_8037F450[i].unk14 = 210.0f;
                D_8037F450[i].unk8.f[0] = 1156.66f;
                D_8037F450[i].unk8.f[1] = 1770.82f;
                D_8037F450[i].unk8.f[2] = 0.0f;
                break;
            }
        }
    }
}

void func_8034CB80(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_8037F450); i++) {
        if (D_8037F450[i].unk0 != 0xFFFF) {
            uvDobjModel(D_8037F450[i].unk0, 0xFFFF);
            D_8037F450[i].unk0 = 0xFFFF;
            if (D_8037F450[i].unk4 != 0xFFFF) {
                uvDobjModel(D_8037F450[i].unk4, 0xFFFF);
                D_8037F450[i].unk4 = 0xFFFF;
            }
        }
    }
    func_803212DC(D_803509F0);
    D_803509F0 = 0;
}

void func_8034CC10(s32 arg0, s32* arg1, f32* arg2, Vec3F* arg3) {
    Mtx4F sp28;
    Unk8037F450* temp_v0;
    s32 temp_v1;

    if (D_8037F450[arg0].unk0 != 0xFFFF) {
        *arg1 = D_8037F450[arg0].unk0;
        *arg2 = D_8037F450[arg0].unk1C / 360.0f;
        uvDobjGetPosm(*arg1, 0, &sp28);
        arg3->f[0] = sp28.m[3][0];
        arg3->f[1] = sp28.m[3][1];
        arg3->f[2] = sp28.m[3][2];
        return;
    }
    *arg1 = 0xFFFF;
    *arg2 = 0.0f;
    arg3->f[0] = 0.0f;
    arg3->f[1] = 0.0f;
    arg3->f[2] = 0.0f;
}

void func_8034CCC4(s32 arg0, f32 arg1) {
    if (D_8037F450[arg0].unk0 == 0xFFFF) {
        return;
    }

    uvDobjState(D_8037F450[arg0].unk0, 3);
    if (D_8037F450[arg0].unk4 != 0xFFFF) {
        uvDobjState(D_8037F450[arg0].unk4, 0x22);
    }
    D_8037F450[arg0].unk1C = arg1 * 360.0f;
    func_8034C2E0(arg0);
}
