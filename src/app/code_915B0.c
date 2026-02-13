#include "common.h"
#include "code_915B0.h"

u8 func_8030A080(void) {
    u8 ret;
    s32 i;

    ret = 0;
    for (i = 0; i < D_80369584; i++) {
        ret += (D_80369588[i].unk68 != 0) ? 1 : 0;
    }
    return ret;
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_915B0/func_8030A0DC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_915B0/D_80353880.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_915B0/D_80353894.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_915B0/D_803538C4.s")
