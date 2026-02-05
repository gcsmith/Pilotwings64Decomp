#include <uv_graphics.h>
#include <uv_matrix.h>

#include "code_9A960.h"

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_9A960/func_80313430.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_9A960/func_803134D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_9A960/func_80313570.s")

void func_80313640(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, Mtx4F* arg6) {
    uvMat4SetIdentity(arg6);
    uvMat4RotateAxis(arg6, arg3, 0x7A);
    uvMat4RotateAxis(arg6, arg4, 0x78);
    uvMat4RotateAxis(arg6, arg5, 0x79);
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

    uvGfx_802230CC(0, 0, 0x140, 0, 0xF0);
    uvMat4Viewport(&sp60, 0.0f, 319.0f, 0.0f, 239.0f);
    uvGfx_80222100(&sp60);
    uvMat4SetIdentity(&sp20);
    uvGfx_8022345C(&sp20, 1);
    uvGfxStatePush();
    uvGfxSetFlags(0x800000);
    uvGfxClearFlags(0x600000);
}

void func_803141E4(void) {
    uvGfx_802236A8();
    uvGfxStatePop();
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_9A960/func_8031420C.s")
