#include "common.h"

void uvSqrtF(f32 value) {
    sqrtf(value);
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/math/func_80229EC0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/math/func_8022A080.s")

void uvLength2D(f32 x, f32 y) {
    uvSqrtF(SQ(x) + SQ(y));
}

void uvLength3D(f32 x, f32 y, f32 z) {
    uvSqrtF(SQ(x) + SQ(y) + SQ(z));
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/math/func_8022A27C.s")

