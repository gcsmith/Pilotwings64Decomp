#include <uv_clocks.h>

extern u32 D_80263470;
extern s32 D_80263474;
extern uvClockState_t D_80263478[];

void func_80205FD0(void) {
    D_80263470 = osGetCount();
    D_80263474 = 0;
}

void func_80205FFC(void) {
    u32 count;

    count = osGetCount();
    if (((u32)D_80263470 >= 0xF0000001U) && (count < 0x10000000U)) {
        D_80263474 += 1;
    }
    D_80263470 = count;
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/clocks/uvClkGetSec.s")

void func_80206150(s32 clk_id) {
    uvClockState_t* temp_v0;

    func_80205FFC();
    temp_v0 = &D_80263478[clk_id];
    temp_v0->unk4 = (s32)D_80263470;
    temp_v0->unk0 = (s32)D_80263474;
}
