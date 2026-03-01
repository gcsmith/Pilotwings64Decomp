#include "common.h"
#include "spath.h"

f32 D_80350650[] = { 2.0f, -2.0f, 1.0f, 1.0f, -3.0f, 3.0f, -2.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f };

#pragma GLOBAL_ASM("asm/nonmatchings/app/spath/spath_create.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/spath/func_80340668.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/spath/spath_free.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/spath/spath_update2.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/spath/spath_update.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/spath/func_80340CB8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/spath/func_80340E7C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/spath/func_80340FEC.s")
