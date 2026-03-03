#include "common.h"
#include "code_61A60.h"
#include "code_9A960.h"

s32 D_8034EA40 = 0;
u16 D_8034EA44 = 0xFFFF;
s32 D_8034EA48 = 0;

// This struct should be used for Unk8034EA4C */
typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
} Unk8034EA4C;
f32 D_8034EA4C[] = {
    -68.08f,
    -302.14f,
    10.74f,
};

f32 D_8034EA58 = -0.0174533f; // almost DEG_TO_RAD(1)
f32 D_8034EA5C = 0.1f;
f32 padD_8034EA60 = 0.0f;

s32 D_8034EA64[] = { 0, 3, 1, 4, 2, 5 };
s32 D_8034EA7C[] = { 0x35, 0x14C, 0x9C, 0x1A7, 0x85, 0x128 };
s32 D_8034EA94[] = { 2, 2, 2, 2, 2, 2 };
Unk803599D0 D_8034EAAC = { 8, 0.36f, 0.0f, 0.412f, 0.1f, 0.465f, 0.25f, 0.517f, 0.475f, 0.568f, 0.5f, 0.62f, 0.475f, 0.673f, 0.25f, 0.725f, 0.0f, 0, 0, 0, 0 };

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DA530.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DA54C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DA574.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DA628.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DA684.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DA6E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DA9E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DAA34.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DAB18.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DB050.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DB224.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DB38C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DB6D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DB9B8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DBCB0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DBE10.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DBE64.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DBF10.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DC074.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DC1DC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DC380.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DC784.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DC814.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DC8E4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DC930.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DC97C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DCA00.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DCA5C.s")
