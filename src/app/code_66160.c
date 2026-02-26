#include <uv_geometry.h>
#include <uv_graphics.h>
#include <uv_matrix.h>

#include "code_66160.h"

extern s32 D_80359D70;
extern s32 D_80359D7C;

void func_802DEC30(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 arg10, s32 arg11, s32 arg12,
                   s32 arg13) {
    uvVtxBeginPoly();
    uvVtx(arg0, arg1, 0, 0, 0, arg8, arg9, arg10, 0xFF);
    uvVtx(arg2, arg3, 0, 0, 0, arg8, arg9, arg10, 0xFF);
    uvVtx(arg4, arg5, 0, 0, 0, arg11, arg12, arg13, 0xFF);
    uvVtx(arg6, arg7, 0, 0, 0, arg11, arg12, arg13, 0xFF);
    uvVtxEndPoly();
}

void screenDrawBox(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7) {
    uvVtxBeginPoly();
    uvVtx(arg0, arg1, 0, 0, 0, arg4, arg5, arg6, arg7);
    uvVtx(arg2, arg1, 0, 0, 0, arg4, arg5, arg6, arg7);
    uvVtx(arg2, arg3, 0, 0, 0, arg4, arg5, arg6, arg7);
    uvVtx(arg0, arg3, 0, 0, 0, arg4, arg5, arg6, arg7);
    uvVtxEndPoly();
}

void func_802DEE44(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 arg10) {
    s32 temp_s0 = arg0 + arg2;
    s32 temp_s1 = arg1 + arg3;
    s32 temp_s2 = arg0 + arg4;
    s32 temp_s3 = temp_s1 - arg4;
    s32 temp_s4 = temp_s0 - arg4;
    s32 temp_s5 = arg1 + arg4;

    uvGfxStatePush();
    uvGfxSetFlags(GFX_STATE_800000 | 0xFFF);
    uvGfxClearFlags(GFX_STATE_400000 | GFX_STATE_200000 | GFX_STATE_100000);
    func_802DEC30(temp_s0, temp_s1, arg0, temp_s1, temp_s2, temp_s3, temp_s4, temp_s3, arg5, arg6, arg7, arg8, arg9, arg10);
    func_802DEC30(temp_s4, temp_s3, temp_s4, temp_s5, temp_s0, arg1, temp_s0, temp_s1, arg5, arg6, arg7, arg8, arg9, arg10);
    func_802DEC30(temp_s4, temp_s5, temp_s2, temp_s5, arg0, arg1, temp_s0, arg1, arg5, arg6, arg7, arg8, arg9, arg10);
    func_802DEC30(arg0, temp_s1, arg0, arg1, temp_s2, temp_s5, temp_s2, temp_s3, arg5, arg6, arg7, arg8, arg9, arg10);
    uvGfxStatePop();
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_66160/screenDrawBox2.s")

void screenDrawBoxSetup(void) {
    Mtx4F sp60;
    Mtx4F sp20;

    uvGfxStatePush();
    uvGfxSetFlags(GFX_STATE_800000);
    uvGfxClearFlags(GFX_STATE_400000 | GFX_STATE_200000);
    uvGfxSetViewport(0, 0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);
    uvMat4SetOrtho(&sp20, 0.0f, SCREEN_WIDTH - 1, 0.0f, SCREEN_HEIGHT - 1);
    uvGfxMtxProjPushF(&sp20);
    uvMat4SetIdentity(&sp60);
    uvGfxMtxViewLoad(&sp60, 1);
}

void func_802DFA18(void) {
    uvGfxMtxViewPop();
    uvGfxStatePop();
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_66160/func_802DFA40.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_66160/func_802DFB48.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_66160/db_getgnd.s")

s32* func_802E02EC(void) {
    return &D_80359D70;
}

s32 func_802E02F8(void) {
    return D_80359D7C;
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_66160/db_getstart.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_66160/func_802E0484.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_66160/func_802E05CC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_66160/func_802E06AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_66160/func_802E07D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_66160/func_802E08F4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_66160/func_802E0C30.s")
