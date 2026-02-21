#include "common.h"
#include <uv_janim.h>
#include <uv_dobj.h>
#include <uv_matrix.h>
#include <uv_model.h>
#include <uv_level.h>
#include "code_9A960.h"
#include "code_D2D50.h"
#include "hud.h"
#include "proxanim.h"

// .data
extern s32 D_803509C0;   // = 0xFFFF
extern s32 D_803509C4;   // = 0xFFFF
extern s32 D_803509C8;   // = 0xFF
extern s32 D_803509CC;   // = 0
extern f32 D_803509D0;   // = 0.0f
extern f32 D_803509D4;   // = 0
extern s32 D_803509D8;   // = 0
extern Vec3F D_803509DC; // { 750.0f, 100.0f, 4.5f }

// .bss
extern Mtx4F D_8037F380;
extern Mtx4F D_8037F3C0;
extern Mtx4F D_8037F400;
extern f32 D_8037F430;
extern f32 D_8037F434;
extern f32 D_8037F438;
// no D_8037F43C
extern f32 D_8037F440;
extern f32 D_8037F444;
extern f32 D_8037F448;
extern s32 D_8037F44C;

s32 func_8034B820(void) {
    return D_803509D8;
}

static void func_8034B82C(void) {
    Mtx4F spF0;
    Mtx4F spB0;
    Mtx4F sp70;
    Mtx4F sp30;
    s32 v1;
    s32 v0;
    f32 sp24;

    uvMat4SetIdentity(&sp70);
    uvMat4RotateAxis(&sp70, D_803509D0 * 0.01745329f, 'z');
    uvMat4Mul(&spB0, &D_8037F380, &sp70);
    if (D_803509C4 != 0xFFFF) {
        uvMat4Mul(&D_8037F400, &spB0, &D_8037F3C0);
        uvDobjPosm(D_803509C4, 0, &D_8037F400);
    }
    uvMat4SetIdentity(&spF0);
    uvMat4UnkOp2(&spF0, 0.0f, 0.0f, D_803509D4);
    uvMat4Mul(&sp30, &spB0, &spF0);
    uvMat4Mul(&D_8037F400, &sp30, &D_8037F3C0);
    uvDobjPosm(D_803509C0, 0, &D_8037F400);

    v0 = (D_803509D0 + 15.0f) / 30;
    v1 = (s32)(D_803509D0 + 15.0f) % 30;
    if (v0 % 2) {
        sp24 = (30.0f - v1) / 30.0f;
    } else {
        sp24 = v1 / 30.0f;
    }
    func_80200B00(D_803509C0, 0, 1.0f - sp24);
    if (D_803509C8 != 0xFF) {
        hud_8031A794(D_803509C8, D_8037F430, D_8037F434, D_8037F438);
    }
    uvModelGetPosm(0xD7, 1, &spB0);
    uvMat4UnkOp3(&spB0, 2.0 * sp24, 2.0 * sp24, 2.0 * sp24);
    uvDobjPosm(D_803509C0, 1, &spB0);
}

static void func_8034BA68(void) {
    if (D_8037F440 == 1.0f) {
        D_803509D4 += 4.0f * D_8034F854;
        if (D_803509D4 > 0 /*.0f*/) {
            D_8037F440 = 0.0f;
            D_803509D4 = 0 /*.0f*/;
        }
        D_803509D0 += 10.0f * D_8034F854;
        if (D_803509D0 > 360.0f) {
            D_803509D0 -= 360.0f;
        }
        func_8034B82C();
        return;
    }
    if (D_8037F440 == 2.0f) {
        D_803509D4 -= 4.0f * D_8034F854;
        if (D_803509D4 < -25.0f) {
            D_8037F440 = 3.0f;
        }
        D_803509D0 += 10.0f * D_8034F854;
        if (D_803509D0 > 360.0f) {
            D_803509D0 -= 360.0f;
        }
        func_8034B82C();
        return;
    }
    if (D_8037F440 == 0.0f) {
        D_803509D0 += 10.0f * D_8034F854;
        if (D_803509D0 > 360.0f) {
            D_803509D0 -= 360.0f;
        }
        func_8034B82C();
    }
}

static s32 func_8034BC68(s32 arg0, s32 arg1, s32 arg2) {
    switch (arg1) {
    case 0:
        uvDobjState(D_803509C0, 3);
        if (D_803509C4 != 0xFFFF) {
            uvDobjState(D_803509C4, 0x22);
        }
        uvMat4SetIdentity(&D_8037F380);
        uvMat4UnkOp2(&D_8037F380, 75.0f, 0.0f, 0.0f);
        uvMat4SetIdentity(&D_8037F3C0);
        uvMat4UnkOp2(&D_8037F3C0, 750.0f, 100.0f, 4.5f);
        func_8034B82C();
        break;
    case 2:
        uvDobjState(D_803509C0, 0);
        if (D_803509C4 != 0xFFFF) {
            uvDobjState(D_803509C4, 0);
        }
        if (D_803509C8 != 0xFF) {
            hud_8031A874(D_803509C8);
        }
        break;
    case 3:
        uvDobjState(D_803509C0, 3);
        if (D_803509C4 != 0xFFFF) {
            uvDobjState(D_803509C4, 0x22);
        }
        if (D_803509C8 != 0xFF) {
            hud_8031A874(D_803509C8);
        }
        break;
    }
    return 0;
}

static s32 func_8034BDCC(s32 arg0, s32 arg1, s32 arg2) {
    s32 pad;
    s32 sp18;

    sp18 = 0;
    if (func_80321420(arg0) > 450.0f) {
        if (D_803509D8 != 0) {
            D_8037F440 = 2.0f;
            func_8034BA68();
            if (D_8037F440 == 3.0f) {
                D_803509D8 = 0;
            }
        } else {
            sp18 = 2;
            uvDobjState(D_803509C0, 0);
        }
    } else {
        if ((D_8037F440 == 2.0f) || (D_803509D8 == 0)) {
            D_803509D8 = 1;
            D_8037F440 = 1.0f;
            uvDobjState(D_803509C0, 3);
        }
        func_8034BA68();
    }
    return sp18;
}

void func_8034BEDC(void) {
    u16 sp46;
    u16 sp44;
    u16 sp42;
    s32 var_v1;
    Vec3F sp30 = D_803509DC;

    D_803509C4 = uvDobjAllocIdx();
    if (D_803509C4 != 0xFFFF) {
        uvDobjModel(D_803509C4, 0xD8);
        uvDobjState(D_803509C4, 0);
    }
    D_803509C0 = uvDobjAllocIdx();
    if (D_803509C0 == 0xFFFF) {
        if (D_803509C4 != 0xFFFF) {
            uvDobjModel(D_803509C4, 0xFFFF);
            D_803509C4 = 0xFFFF;
        }
    } else {
        uvDobjModel(D_803509C0, 0xD7);
        uvDobjState(D_803509C0, 0);
        D_803509CC = func_80321210(func_8034BDCC, func_8034BC68, sp30, 450.0f, 0.0f, 4);
        D_803509D0 = 0.0f;
        levelGetClsVehTest(&sp46, &sp44, &sp42);
        var_v1 = (sp42 == 0 && sp46 == 1 && sp44 == 0) || (sp42 == 1 && sp46 == 2 && sp44 == 0) || (sp42 == 2 && sp46 == 3 && sp44 == 0);
        if (var_v1) {
            D_803509C8 = hud_8031A6C8(750.0f, 100.0f, 4.5f);
            return;
        }
        D_803509C8 = 0xFF;
    }
}

void func_8034C0BC(void) {
    if (D_803509C0 == 0xFFFF) {
        return;
    }

    uvDobjModel(D_803509C0, 0xFFFF);
    D_803509C0 = 0xFFFF;
    if (D_803509C4 != 0xFFFF) {
        uvDobjModel(D_803509C4, 0xFFFF);
        D_803509C4 = 0xFFFF;
    }
    func_803212DC(D_803509CC);
    D_803509CC = 0;
    if (D_803509C8 != 0xFF) {
        hud_8031A8E0(D_803509C8);
    }
    D_803509C8 = 0xFF;
}

f32 func_8034C154(void) {
    return D_803509D0 / 360.0f;
}

void func_8034C16C(Vec3F* arg0) {
    if (D_803509C0 == 0xFFFF) {
        arg0->f[0] = 825.0f;
        arg0->f[1] = 100.0f;
        arg0->f[2] = 4.5f;
        return;
    }
    arg0->f[0] = D_8037F400.m[3][0];
    arg0->f[1] = D_8037F400.m[3][1];
    arg0->f[2] = D_8037F400.m[3][2];
}

void func_8034C1CC(f32 arg0) {
    if (D_803509C0 != 0xFFFF) {
        D_8037F440 = 0.0f;
        D_803509D0 = arg0 * 360.0f;
        D_803509D4 = 0 /*.0f*/;
        func_8034B82C();
    }
}

void func_8034C224(void) {
    D_8037F440 = 1.0f;
    D_803509D8 = 0;
    D_803509D4 = -25.0f;
    D_803509D0 = 0.0f;
}

void func_8034C25C(void) {
    D_8037F444 = D_803509D4;
    D_8037F448 = D_803509D0;
    D_8037F44C = D_8037F440;
}

void func_8034C298(void) {
    D_803509D4 = D_8037F444;
    D_803509D0 = D_8037F448;
    D_8037F440 = D_8037F44C;
}
