#include "common.h"
#include <uv_vector.h>

s8 D_8034F7A0 = 0;
s8 D_8034F7A4 = 0;
u8 D_8034F7A8 = 0xFF;
u8 D_8034F7AC[4] = { 0xFF, 0, 0, 0 };
u8 D_8034F7B0 = 0;
s8 D_8034F7B4[4] = { 0 }; // might be u8
u8 D_8034F7B8 = 0;
u8 D_8034F7BC = 0;
u8 D_8034F7C0[4] = { 1, 0, 0, 0 };
Vec3F D_8034F7C4[2] = {
    {     -68.08f, -302.14f, 10.74f }, // position
    { -0.0174533f,     0.1f,   0.0f }  // rotation,  almost -DEG_TO_RAD(1)
};
f32 D_8034F7DC = 0.0f;
f32 D_8034F7E0 = 1.6f;

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_94E60/func_8030D930.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_94E60/func_8030D9C8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_94E60/func_8030DED0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_94E60/func_8030E3EC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_94E60/func_8030E7F4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_94E60/func_8030E860.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_94E60/func_8030E9AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_94E60/func_8030EA54.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_94E60/func_8030F448.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_94E60/func_8030F818.s")
