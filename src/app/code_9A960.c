#include <uv_graphics.h>
#include <uv_math.h>
#include <uv_matrix.h>
#include "macros.h"

#include "code_9A960.h"

f32 D_8034F850 = 0.0f;
f32 D_8034F854 = 0.1000000015f;
s32 D_8034F858 = 0;

void func_80313430(f32 arg0, f32 arg1, f32 arg2, f32* arg3, f32* arg4, f32* arg5) {
    f32 fake1, fake2, fake3;
    f32 sp20;

    sp20 = uvSqrtF((arg0 * arg0) + (arg1 * arg1));
    *arg3 = uvSqrtF((arg0 * arg0) + (arg1 * arg1) + (arg2 * arg2));
    *arg4 = uvAtan2F(arg1 / *arg3, arg0 / *arg3);
    *arg5 = uvAtan2F(arg2 / *arg3, sp20 / *arg3);
}

void func_803134D0(f32 arg0, f32 arg1, f32 arg2, f32* arg3, f32* arg4, f32* arg5) {
    f32 temp1;

    temp1 = uvCosF(arg1);
    *arg3 = uvCosF(arg2) * (arg0 * temp1);
    temp1 = uvSinF(arg1);
    *arg4 = uvCosF(arg2) * (arg0 * temp1);
    *arg5 = uvSinF(arg2) * arg0;
}

// gets translation and rotation parameters from matrix
void func_80313570(Mtx4F* mat, f32* tx, f32* ty, f32* tz, f32* rz, f32* rx, f32* ry) {
    *rz = uvAtan2F(mat->m[0][1], mat->m[0][0]);
    *rx = -uvAtan2F(mat->m[1][2], uvSqrtF(SQ(mat->m[1][0]) + SQ(mat->m[1][1])));
    *ry = -uvAtan2F(mat->m[0][2], uvSqrtF(SQ(mat->m[0][0]) + SQ(mat->m[0][1])));
    *tx = mat->m[3][0];
    *ty = mat->m[3][1];
    *tz = mat->m[3][2];
}

// initializes matrix with given translation and rotation
void func_80313640(f32 tx, f32 ty, f32 tz, f32 rz, f32 rx, f32 ry, Mtx4F* mat) {
    uvMat4SetIdentity(mat);
    uvMat4RotateAxis(mat, rz, 'z');
    uvMat4RotateAxis(mat, rx, 'x');
    uvMat4RotateAxis(mat, ry, 'y');
    mat->m[3][0] = tx;
    mat->m[3][1] = ty;
    mat->m[3][2] = tz;
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_9A960/func_803136C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_9A960/func_8031385C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_9A960/func_803138A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_9A960/func_80313AF4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_9A960/func_80313BAC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_9A960/func_80313C94.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_9A960/func_80313D74.s")

void func_80313E0C(f32 arg0) {
    D_8034F850 = arg0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_9A960/func_80313E18.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_9A960/func_80313F08.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_9A960/func_80313FD0.s")

s32 func_80314114(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;

    temp_v0 = arg1 & arg2;
    if ((temp_v0 != 0) && !(arg0 & arg2)) {
        return 1;
    }
    if ((temp_v0 == 0) && (arg0 & arg2)) {
        return -1;
    }
    return 0;
}

void func_80314154(void) {
    Mtx4F sp60;
    Mtx4F sp20;

    uvGfxSetViewport(0, 0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);
    uvMat4SetOrtho(&sp60, 0.0f, SCREEN_WIDTH - 1, 0.0f, SCREEN_HEIGHT - 1);
    uvGfxMtxProjPushF(&sp60);
    uvMat4SetIdentity(&sp20);
    uvGfxMtxViewLoad(&sp20, 1);
    uvGfxStatePush();
    uvGfxSetFlags(GFX_STATE_800000);
    uvGfxClearFlags(GFX_STATE_400000 | GFX_STATE_200000);
}

void func_803141E4(void) {
    uvGfxMtxViewPop();
    uvGfxStatePop();
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_9A960/func_8031420C.s")
