#include "common.h"
#include "kernel/code_1AF80.h"

// clang-format off
static u16 D_80248EA0[] = {
    0x0000, 0x0000, 0x0064, 0x0000, 0x0047, 0xFFB9, 0x0000, 0xFF9C,
    0xFFB9, 0xFFB9, 0xFF9C, 0x0000, 0xFFB9, 0x0047, 0x0000, 0x0064,
    0x0047, 0x0047,
};

static u16 D_80248EC4[] = {
    0x0064, 0x0000, 0xFF9C, 0x0000, 0x0064, 0x0000, 0x0064, 0x00C8,
    0xFF9C, 0x00C8,
};

static u16 D_80248ED8[] = {
    0x0000, 0x0000,
};

static u16 D_80248EDC[] = {
    0x0064, 0x0000, 0x005C, 0xFFDA, 0x0047, 0xFFB9, 0x0026, 0xFFA4,
    0x0000, 0xFF9C, 0xFFDA, 0xFFA4, 0xFFB9, 0xFFB9, 0xFFA4, 0xFFDA,
    0xFF9C, 0x0000, 0xFFA4, 0x0026, 0xFFB9, 0x0047, 0xFFDA, 0x005C,
    0x0000, 0x0064, 0x0026, 0x005C, 0x0047, 0x0047, 0x005C, 0x0026,
};

static u16 D_80248F1C[] = {
    0x0000, 0x0000, 0x0064, 0x0000, 0x0000, 0x0064, 0xFF9C, 0x0000,
    0x0000, 0xFF9C,
};

static u16 D_80248F30[] = {
    0x0064, 0x0000,
};

static u32 D_80248F34[] = {
    0xFFDF0000, 0x00000000, 0xFFDF000E, 0x00000000, 0xFFDF001D, 0x00000000,
    0xFFDF002B, 0x00000000, 0xFFDF0039, 0x00000000, 0xFFDF0047, 0x00000000,
    0xFFDF0056, 0x00000000, 0xFFDF0064, 0x00000000, 0xFFE70000, 0x00000000,
    0xFFE7000E, 0x00000000, 0xFFE7001D, 0x3E99999A, 0xFFE7002B, 0x00000000,
    0xFFE70039, 0x3E99999A, 0xFFE70047, 0x3ECCCCCD, 0xFFE70056, 0x00000000,
    0xFFE70064, 0x00000000, 0xFFEF0000, 0x00000000, 0xFFEF000E, 0x3E99999A,
    0xFFEF001D, 0x3ECCCCCD, 0xFFEF002B, 0x3F19999A, 0xFFEF0039, 0x3F4CCCCD,
    0xFFEF0047, 0x3F19999A, 0xFFEF0056, 0x3F000000, 0xFFEF0064, 0x00000000,
    0xFFF80000, 0x3F666666, 0xFFF8000E, 0x3F666666, 0xFFF8001D, 0x3F333333,
    0xFFF8002B, 0x3F4CCCCD, 0xFFF80039, 0x3F333333, 0xFFF80047, 0x3F333333,
    0xFFF80056, 0x3F19999A, 0xFFF80064, 0x00000000, 0x00000000, 0x3F666666,
    0x0000000E, 0x3F4CCCCD, 0x0000001D, 0x3F4CCCCD, 0x0000002B, 0x3F666666,
    0x00000039, 0x3F4CCCCD, 0x00000047, 0x3F4CCCCD, 0x00000056, 0x3E4CCCCD,
    0x00000064, 0x00000000, 0x00080000, 0x00000000, 0x0008000E, 0x3E4CCCCD,
    0x0008001D, 0x3F666666, 0x0008002B, 0x3F333333, 0x00080039, 0x3F000000,
    0x00080047, 0x3F19999A, 0x00080056, 0x00000000, 0x00080064, 0x00000000,
    0x00110000, 0x00000000, 0x0011000E, 0x00000000, 0x0011001D, 0x3ECCCCCD,
    0x0011002B, 0x3E4CCCCD, 0x00110039, 0x3DCCCCCD, 0x00110047, 0x3F000000,
    0x00110056, 0x3DCCCCCD, 0x00110064, 0x00000000, 0x00190000, 0x00000000,
    0x0019000E, 0x00000000, 0x0019001D, 0x00000000, 0x0019002B, 0x00000000,
    0x00190039, 0x00000000, 0x00190047, 0x00000000, 0x00190056, 0x00000000,
    0x00190064, 0x00000000,
};

static u32 D_80249134[] = {
    0x00000000, 0x00000000, 0x00000000,
};
// clang-format on

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_1AF80/func_80219FD0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_1AF80/func_8021A038.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_1AF80/func_8021A0CC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_1AF80/func_8021A298.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_1AF80/func_8021A2C8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_1AF80/func_8021A304.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_1AF80/func_8021A334.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_1AF80/func_8021A4D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_1AF80/D_8024D880.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_1AF80/uvFxProps.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_1AF80/uvFxGetProps.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_1AF80/uvModelGet.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_1AF80/func_8021BE28.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_1AF80/func_8021C4F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_1AF80/func_8021C74C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_1AF80/func_8021C87C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_1AF80/func_8021D700.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_1AF80/func_8021D8E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_1AF80/func_8021DAF8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_1AF80/func_8021DD30.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_1AF80/func_8021E608.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_1AF80/func_8021E7E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_1AF80/func_8021EA38.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_1AF80/_uvFxDraw.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_1AF80/func_8021EFF0.s")
