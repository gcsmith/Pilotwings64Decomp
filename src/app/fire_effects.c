#include "common.h"
#include "fire_effects.h"

s32 D_8034F120 = 0xFFFFFFFF;

// .bss
extern s32 D_80362620;
extern s32 D_80362624;

void func_802E9FD0(void) {
    D_80362620 = 0;
    D_80362624 = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/fire_effects/func_802E9FE4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/fire_effects/fx_create.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/fire_effects/func_802EA824.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/fire_effects/fx_create_fire.s")
