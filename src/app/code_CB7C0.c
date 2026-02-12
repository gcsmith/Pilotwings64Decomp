#include "common.h"
#include "code_CB7C0.h"

extern u8 D_80378CF4;

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_CB7C0/func_80344290.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_CB7C0/func_803442F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_CB7C0/func_8034450C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_CB7C0/func_8034467C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_CB7C0/func_8034473C.s")

u8 func_803448F4(void) {
    u8 ret;
    s32 i;

    ret = 0;
    for (i = 0; i < D_80378CF4; i++) {
        ret += D_80378CF8[i].unk46;
    }
    return ret;
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_CB7C0/func_80344948.s")
