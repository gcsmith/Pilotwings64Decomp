#include "common.h"
#include <uv_dobj.h>
#include "shadow.h"

extern s32 D_80350460;
extern s32 D_80350464;
extern s32 D_80350468;
extern s32 D_80350470;
extern f32 D_80350474;
extern f32 D_80350478;

// forward declarations
void func_80334308(u16, u16);

void func_803342F0(f32 arg0) {
    D_80350474 = arg0;
}

void func_803342FC(f32 arg0) {
    D_80350478 = arg0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/shadow/func_80334308.s")

void func_803343D8(s32 arg0) {
    if (D_80350470 != 0xFFFF) {
        if (arg0 != 0) {
            if (D_80350460 == 0) {
                uvDobjState(D_80350470, 2);
            }
            D_80350460 = 2;
        } else {
            if (D_80350460 != 0) {
                uvDobjState(D_80350470, 0);
            }
            D_80350460 = 0;
        }
    }
}

void func_80334454(u16 arg0, u16 arg1) {
    D_80350468 = arg0;
    D_80350464 = arg1;
    if (arg0 != 0xFFFF) {
        func_80334308(arg0, arg1);
    } else if (arg1 != 0xFFFF) {
        u32 a0 = arg1;
        func_80334308(a0, arg1);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/shadow/func_803344BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/shadow/func_80334578.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/shadow/func_803347D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/shadow/func_80334A38.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/shadow/func_80334C70.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/shadow/func_80334CC0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/shadow/func_80334CCC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/shadow/func_80335130.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/shadow/func_80335700.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/shadow/func_803358D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/shadow/func_80335AE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/shadow/func_80335AF4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/shadow/shadowInit.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/shadow/func_80335BE4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/shadow/func_80335E44.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/shadow/func_80335EE4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/shadow/func_80335F24.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/shadow/func_80335F84.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/shadow/func_80335FD8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/shadow/func_80336064.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/shadow/func_80336094.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/shadow/func_803360E8.s")
