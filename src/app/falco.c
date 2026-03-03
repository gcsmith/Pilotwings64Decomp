#include "common.h"
#include "falco.h"

typedef struct {
    u8 pad0[0x254];
    u8 unk254;
    u8 pad255[0x258 - 0x255];
} Unk8035A5F8;

typedef struct {
    s32 unk0;
    void* unk4; // maybe f32 pointer
    s32 unk8;   // always 0, maybe a pointer to something?
} Unk8034EFB0;

// .data
f32 D_8034EFA0 = 0.0f;
s32 padD_8034EFA4[3] = { 0 };

extern f32 D_8035AF30;
extern f32 D_8035AF34;
extern f32 D_8035AF38;
extern f32 D_8035AF3C;

// referenced in D_8034F03C
Unk8034EFB0 D_8034EFB0 = { 0xA, &D_8035AF30, 0 };
Unk8034EFB0 D_8034EFBC = { 0x5, &D_8035AF34, 0 };
Unk8034EFB0 D_8034EFC8 = { 0x6, &D_8035AF30, 0 };
Unk8034EFB0 D_8034EFD4 = { 0x9, &D_8035AF38, 0 };
Unk8034EFB0 D_8034EFE0 = { 0x8, &D_8035AF3C, 0 };
Unk8034EFB0 D_8034EFEC = { 0x7, &D_8035AF3C, 0 };
Unk8034EFB0 D_8034EFF8 = { 0x4, &D_8035AF3C, 0 };
Unk8034EFB0 D_8034EF04 = { 0x3, &D_8035AF3C, 0 };

// .bss
extern Unk8035A5F8 D_8035A5F8[];

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/func_802E37B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/func_802E38F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/func_802E3A5C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/func_802E3E6C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/func_802E3F7C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/func_802E43C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/func_802E45B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/func_802E478C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/func_802E4794.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/func_802E49B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/func_802E4AA8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/func_802E4E70.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/func_802E51E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/func_802E55A0.s")

s32 func_802E57C4(void) {
    s32 ret;
    s32 i;

    ret = 0;
    for (i = 0; i < D_8035A5F0; i++) {
        ret += D_8035A5F8[i].unk254;
    }
    return ret;
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/func_802E5818.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/func_802E587C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/func_802E5AFC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/func_802E5BF8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/func_802E5D78.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/func_802E5F44.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/func_802E5F90.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/func_802E60A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/func_802E60E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/func_802E6128.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/func_802E6184.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/func_802E61E4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/func_802E6224.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/func_802E6284.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/func_802E62E4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/func_802E6344.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/func_802E6380.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/func_802E63BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/func_802E64E0.s")
