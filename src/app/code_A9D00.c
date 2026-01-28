#include "common.h"
#include <uv_controller.h>
#include <uv_util.h>

extern f32 D_8034F850;
extern f32 D_8036DA34;
extern f32 D_8036DA38;
extern s32 D_8034FAD0;

void func_80322DA8(s32);

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_A9D00/func_803227D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_A9D00/func_80322828.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_A9D00/func_80322880.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_A9D00/func_80322890.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_A9D00/func_803229EC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_A9D00/func_80322B60.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_A9D00/func_80322B6C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_A9D00/func_80322B78.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_A9D00/func_80322B84.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_A9D00/func_80322B90.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_A9D00/func_80322BE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_A9D00/func_80322D60.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_A9D00/func_80322DA8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_A9D00/func_80322EB0.s")

void func_80322EBC(void) {
    if (D_8034FAD0 == 1) {
        _uvDebugPrintf("%.10f(%.10f, %.10f)0x%x\n", D_8034F850 - D_8036DA34, uvControllerGetStick(0, 0), uvControllerGetStick(0, 1), uvControllerGetButton(0));
    }
    if (D_8036DA38 <= D_8034F850) {
        func_80322DA8(0);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_A9D00/func_80322F7C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_A9D00/func_80323020.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_A9D00/func_803230B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_A9D00/func_80323164.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_A9D00/func_803231A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_A9D00/func_803231E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_A9D00/func_80323240.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_A9D00/func_803232A0.s")
