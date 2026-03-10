#include "common.h"

// unused?
s32 D_80350610 = 0xD;
f32 D_80350614[] = { 310.0f, 34.0f, 151.0f, 350.6f, 62.64f, 167.0f, 240.0f, 123.0f, 121.47f, 344.58f, 154.2f, 159.3f };
// doesn't really exist, is just to indicate end of D_80350614
s32 D_80350644 = 0;

#pragma GLOBAL_ASM("asm/nonmatchings/app/snow/snow_create.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/snow/snow_draw.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/snow/snow_update.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/snow/func_803404D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/snow/func_803405C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/snow/func_803405E4.s")
