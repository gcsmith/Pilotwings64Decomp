#ifndef PILOTWINGS64_UV_CLOCKS
#define PILOTWINGS64_UV_CLOCKS

#include <ultra64.h>
#include <uv_util.h>

typedef struct uvClockState {
    u32 unk0;
    u32 unk4;
} uvClockState_t;

void uvClkInit(void);
void uvClkUpdate(void);
f64 uvClkGetSec(s32 clk_id);
void uvClkReset(s32 clk_id);

#endif // PILOTWINGS64_UV_CLOCKS

