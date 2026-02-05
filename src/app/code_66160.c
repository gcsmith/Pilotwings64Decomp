#include <uv_graphics.h>
#include <uv_matrix.h>

#include "code_66160.h"

extern s32 D_80359D70;
extern s32 D_80359D7C;

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_66160/func_802DEC30.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_66160/func_802DED44.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_66160/func_802DEE44.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_66160/func_802DF03C.s")

void func_802DF988(void) {
    Mtx4F sp60;
    Mtx4F sp20;

    uvGfxStatePush();
    uvGfxSetFlags(0x800000);
    uvGfxClearFlags(0x600000);
    uvGfx_802230CC(0, 0, 0x140, 0, 0xF0);
    uvMat4Viewport(&sp20, 0.0f, 319.0f, 0.0f, 239.0f);
    uvGfx_80222100(&sp20);
    uvMat4SetIdentity(&sp60);
    uvGfx_8022345C(&sp60, 1);
}

void func_802DFA18(void) {
    uvGfx_802236A8();
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
