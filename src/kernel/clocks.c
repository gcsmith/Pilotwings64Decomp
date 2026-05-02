#include <uv_clocks.h>

u32 gClockTicks;
s32 gClockWraps;
uvClockState_t gClockState[UV_CLKID_COUNT];

void uvClkInit(void) {
    gClockTicks = osGetCount();
    gClockWraps = 0;
}

void uvClkUpdate(void) {
    u32 count = osGetCount();
    if ((gClockTicks > 0xF0000000) && (count < 0x10000000)) {
        gClockWraps += 1;
    }
    gClockTicks = count;
}

f64 uvClkGetSec(s32 clkId) {
    f64 secsFromWraps;
    f64 secsFromTicks;

    if (clkId >= UV_CLKID_COUNT) {
        _uvDebugPrintf("uvClkGetSec: unknown clock %d\n", clkId);
        return 0.0;
    }

    uvClkUpdate();
    secsFromWraps = gClockWraps - gClockState[clkId].wraps;
    secsFromWraps *= UV_CLK_WRAP_SECS;
    secsFromTicks = ((f64)gClockTicks - gClockState[clkId].ticks) / UV_CLK_TICK_FREQ;

    return secsFromWraps + secsFromTicks;
}

void uvClkReset(s32 clkId) {
    uvClockState_t* clock;

    uvClkUpdate();
    clock = &gClockState[clkId];
    clock->ticks = gClockTicks;
    clock->wraps = gClockWraps;
}

