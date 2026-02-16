#include <uv_clocks.h>

extern u32 D_80263470;
extern s32 D_80263474;
extern uvClockState_t D_80263478[];

void uvClkInit(void) {
    D_80263470 = osGetCount();
    D_80263474 = 0;
}

void uvClkUpdate(void) {
    u32 count;

    count = osGetCount();
    if ((D_80263470 >= 0xF0000001) && (count < 0x10000000)) {
        D_80263474 += 1;
    }
    D_80263470 = count;
}

f64 uvClkGetSec(s32 clk_id) {
    f64 var_fv1;
    f64 var_fa0;

    if (clk_id >= 8) {
        _uvDebugPrintf("uvClkGetSec: unknown clock %d\n", clk_id);
        return 0.0;
    }
    uvClkUpdate();
    var_fv1 = D_80263474 - D_80263478[clk_id].unk0;
    var_fv1 *= 93.875101696;

    var_fa0 = ((f64)D_80263470 - D_80263478[clk_id].unk4) / 45751932.284543216;

    return var_fv1 + var_fa0;
}

void uvClkReset(s32 clk_id) {
    uvClockState_t* temp_v0;

    uvClkUpdate();
    temp_v0 = &D_80263478[clk_id];
    temp_v0->unk4 = D_80263470;
    temp_v0->unk0 = D_80263474;
}

