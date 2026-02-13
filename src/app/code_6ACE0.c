#include "common.h"
#include "code_6ACE0.h"

typedef struct {
    u8 pad0[0x254];
    u8 unk254;
    u8 pad255[0x258 - 0x255];
} Unk8035A5F8;

extern Unk8035A5F8 D_8035A5F8[];

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_6ACE0/func_802E37B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_6ACE0/func_802E38F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_6ACE0/func_802E3A5C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_6ACE0/func_802E3E6C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_6ACE0/func_802E3F7C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_6ACE0/func_802E43C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_6ACE0/func_802E45B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_6ACE0/func_802E478C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_6ACE0/func_802E4794.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_6ACE0/func_802E49B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_6ACE0/func_802E4AA8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_6ACE0/func_802E4E70.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_6ACE0/func_802E51E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_6ACE0/func_802E55A0.s")

s32 func_802E57C4(void) {
    s32 ret;
    s32 i;

    ret = 0;
    for (i = 0; i < D_8035A5F0; i++) {
        ret += D_8035A5F8[i].unk254;
    }
    return ret;
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_6ACE0/func_802E5818.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_6ACE0/func_802E587C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_6ACE0/func_802E5AFC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_6ACE0/func_802E5BF8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_6ACE0/func_802E5D78.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_6ACE0/func_802E5F44.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_6ACE0/func_802E5F90.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_6ACE0/func_802E60A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_6ACE0/func_802E60E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_6ACE0/func_802E6128.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_6ACE0/func_802E6184.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_6ACE0/func_802E61E4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_6ACE0/func_802E6224.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_6ACE0/func_802E6284.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_6ACE0/func_802E62E4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_6ACE0/func_802E6344.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_6ACE0/func_802E6380.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_6ACE0/func_802E63BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_6ACE0/func_802E64E0.s")
