#include <uv_graphics.h>
#include "code_A8C30.h"

void func_80321760(void);
s32 func_8032232C(void);
s32 func_80322464(void);
void func_803226DC(void);

s32 func_80321700(void) {
    func_80321760();
    while (func_80322464() == 0) {
        uvGfxBegin();
        func_803226DC();
        uvGfxEnd();
    }
    return func_8032232C();
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_A8C30/func_80321760.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_A8C30/func_8032232C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_A8C30/func_80322464.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_A8C30/func_803226DC.s")
