#ifndef PILOTWINGS64_UV_CLOCKS
#define PILOTWINGS64_UV_CLOCKS

#include <ultra64.h>
#include <uv_util.h>

#define UV_CLK_WRAP_SECS 93.875101696
#define UV_CLK_TICK_FREQ 45751932.284543216

#define UV_CLKID_GFX      3 // used exclusively in kernel/graphics
#define UV_CLKID_APP      4 // used in various places in the app segment
#define UV_CLKID_TXT      5 // used exclusively in kernel/texture
#define UV_CLKID_SCHED    6 // used exclusively in kernel/sched
#define UV_CLKID_SEQ      7 // used exclusively in kernel/seq
#define UV_CLKID_COUNT    8

typedef struct uvClockState {
    u32 wraps;  // number of times counter has wrapped around / overflowed
    u32 ticks;  // number of clock ticks
} uvClockState_t;

void uvClkInit(void);
void uvClkUpdate(void);
f64 uvClkGetSec(s32 clkId);
void uvClkReset(s32 clkId);

#endif // PILOTWINGS64_UV_CLOCKS

