#include "common.h"
#include "ball_target.h"

typedef struct {
    u8 pad0[0x5B];
    u8 unk5B;
    u8 pad5C[0x60 - 0x5C];
} Unk803597E8;

extern u8 D_803597E4;
extern Unk803597E8 D_803597E8[];

#pragma GLOBAL_ASM("asm/nonmatchings/app/ball_target/func_802D2850.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/ball_target/func_802D28D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/ball_target/func_802D29FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/ball_target/func_802D2ACC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/ball_target/func_802D2C20.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/ball_target/func_802D2E48.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/ball_target/func_802D3030.s")

u8 func_802D30B4(void) {
    s32 i;
    u8 ret;

    ret = 0;
    for (i = 0; i < D_803597E4; i++) {
        ret += (D_803597E8[i].unk5B != 0) ? 1 : 0;
    }
    return ret;
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/ball_target/func_802D3110.s")
