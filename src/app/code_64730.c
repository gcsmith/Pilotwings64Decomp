#include "common.h"
#include "task.h"

s8 D_8034EDA0 = 0;
s8 D_8034EDA4[] = { 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

f32 D_8034EDBC = 0.0f;

u8 D_8034EDC0 = 0xFF;
u8 D_8034EDC4 = 0xFF;
s32 D_8034EDC8 = 0xFFFF;
s32 D_8034EDCC = 0xFFFF;
s32 D_8034EDD0 = 0;
s32 D_8034EDD4 = 0;
s32 D_8034EDD8 = 0;

Unk803599D0 D_8034EDDC[] = {
    8, 0.36f, 0.0f, 0.412f, 0.1f, 0.465f, 0.25f, 0.517f, 0.475f, 0.568f, 0.5f, 0.62f, 0.475f, 0.673f, 0.25f, 0.725f, 0.0f, 0, 0, 0, 0
};

s16 D_8034EE30[] = { 0x0110, 0x0114, 0x0116, 0x0118, 0x011A, 0x011C, 0x011E, 0x0122, 0x0123, 0x0124, 0x0125, 0x0126, 0x0127, 0x012B,
                     0x012D, 0x012F, 0x0131, 0x0133, 0x0135, 0x0136, 0x0137, 0x0138, 0x0139, 0x013A, 0x0144, 0x014A, 0x014C, 0x014D,
                     0x014E, 0x014F, 0x0150, 0x0152, 0x0153, 0x0154, 0x0155, 0x0156, 0x013B, 0x013E, 0x013F, 0x0140, 0x0141, 0x0142 };

u8 D_8034EE84[] = {
    0x4C, 0x4D, 0x4B, 0x51, 0x50, 0x4F, 0x4E, 0x00,
};

f32 D_8034EE8C[] = {
    -0.745f, -1.336f, -1.221f, -0.828f, -1.36f, -1.076f, -0.745f, -1.336f, -1.0f, -1.0f, -1.0f, -1.0f,
};

f32 D_8034EEBC[] = {
    -0.745f, -1.336f, -1.221f, -0.828f, -1.36f, -1.076f,
};

f32 D_8034EED4 = 0.0f;
f32 D_8034EED8 = 1.6f;

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_64730/func_802DD200.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_64730/func_802DD42C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_64730/func_802DD44C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_64730/func_802DD57C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_64730/func_802DD8E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_64730/func_802DE5B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_64730/func_802DE964.s")
