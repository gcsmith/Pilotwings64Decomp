#include "common.h"
#include "rings.h"

extern u8 D_8036DA74; // count of rings stored in D_8036DA78

#pragma GLOBAL_ASM("asm/nonmatchings/app/rings/func_803232F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/rings/func_80323364.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/rings/func_803234A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/rings/func_80323720.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/rings/func_80323864.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/rings/func_8032390C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/rings/func_803239B4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/rings/func_80323DCC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/rings/func_80323FFC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/rings/func_803243D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/rings/func_80324A34.s")

u8 func_80324AF4(void) {
    u8 ret;
    s32 i;

    ret = 0;
    for (i = 0; i < D_8036DA74; i++) {
        ret += (D_8036DA78[i].unk1B4 != 0) ? 1 : 0;
    }
    return ret;
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/rings/func_80324B60.s")
