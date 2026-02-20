#include "common.h"
#include "code_52230.h"

// .data
// list of model ids
s32 D_8034E810[] = {0xF4, 0xF5, 0xF6};

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_52230/func_802CAD00.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_52230/func_802CADE8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_52230/func_802CAF50.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_52230/func_802CB094.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_52230/func_802CB2FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_52230/func_802CB35C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_52230/func_802CB3F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_52230/func_802CB56C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_52230/func_802CB6D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_52230/func_802CB9B4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_52230/ballsCollision.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_52230/ballsPhysics.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_52230/func_802CC064.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_52230/func_802CC0D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_52230/func_802CC13C.s")

u8 func_802CC15C(void) {
    s32 i;
    s32 ret;

    ret = 1;
    for (i = 0; i < D_80357210 + D_80357211; i++) {
        if (D_80357218[i].unk94 == 0) {
            ret = 0;
            break;
        }
    }
    return ret;
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_52230/func_802CC1B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_52230/func_802CC270.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_52230/func_802CC39C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_52230/func_802CC51C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_52230/func_802CC55C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_52230/func_802CD0F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_52230/func_802CD2E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_52230/func_802CE0A4.s")
