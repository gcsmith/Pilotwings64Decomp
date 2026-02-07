#include <uv_graphics.h>
#include <uv_math.h>
#include <uv_matrix.h>
#include "macros.h"

#include "code_9A960.h"

void func_80313430(f32 arg0, f32 arg1, f32 arg2, f32* arg3, f32* arg4, f32* arg5) {
    f32 fake1, fake2, fake3;
    f32 sp20;

    sp20 = uvSqrtF((arg0 * arg0) + (arg1 * arg1));
    *arg3 = uvSqrtF((arg0 * arg0) + (arg1 * arg1) + (arg2 * arg2));
    *arg4 = uvMath_8022A27C(arg1 / *arg3, arg0 / *arg3);
    *arg5 = uvMath_8022A27C(arg2 / *arg3, sp20 / *arg3);
}

void func_803134D0(f32 arg0, f32 arg1, f32 arg2, f32* arg3, f32* arg4, f32* arg5) {
    f32 temp1;

    temp1 = uvCosF(arg1);
    *arg3 = uvCosF(arg2) * (arg0 * temp1);
    temp1 = uvSinF(arg1);
    *arg4 = uvCosF(arg2) * (arg0 * temp1);
    *arg5 = uvSinF(arg2) * arg0;
}

void func_80313570(Mtx4F* arg0, f32* arg1, f32* arg2, f32* arg3, f32* arg4, f32* arg5, f32* arg6) {
    *arg4 = uvMath_8022A27C(arg0->m[0][1], arg0->m[0][0]);
    *arg5 = -uvMath_8022A27C(arg0->m[1][2], uvSqrtF(SQ(arg0->m[1][0]) + SQ(arg0->m[1][1])));
    *arg6 = -uvMath_8022A27C(arg0->m[0][2], uvSqrtF(SQ(arg0->m[0][0]) + SQ(arg0->m[0][1])));
    *arg1 = arg0->m[3][0];
    *arg2 = arg0->m[3][1];
    *arg3 = arg0->m[3][2];
}

void func_80313640(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, Mtx4F* arg6) {
    uvMat4SetIdentity(arg6);
    uvMat4RotateAxis(arg6, arg3, 'z');
    uvMat4RotateAxis(arg6, arg4, 'x');
    uvMat4RotateAxis(arg6, arg5, 'y');
    arg6->m[3][0] = arg0;
    arg6->m[3][1] = arg1;
    arg6->m[3][2] = arg2;
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

    uvGfxSetViewport(0, 0, 0x140, 0, 0xF0);
    uvMat4Viewport(&sp60, 0.0f, 319.0f, 0.0f, 239.0f);
    uvGfxMtxProjPushF(&sp60);
    uvMat4SetIdentity(&sp20);
    uvGfxMtxViewLoad(&sp20, 1);
    uvGfxStatePush();
    uvGfxSetFlags(0x800000);
    uvGfxClearFlags(0x600000);
}

void func_803141E4(void) {
    uvGfxMtxViewPop();
    uvGfxStatePop();
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_9A960/func_8031420C.s")
