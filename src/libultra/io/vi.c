#include "PRinternal/viint.h"
#include "PR/rcp.h"
#include "PR/os.h"

__OSViContext sViContexts[2] = { 0 };
__OSViContext* __osViCurr = &sViContexts[0];
__OSViContext* __osViNext = &sViContexts[1];
u32 sTvType = OS_TV_TYPE_NTSC;
u32 osViClock = VI_NTSC_CLOCK;

extern OSViMode osViModePalLan1;
extern OSViMode osViModeNtscLan1;

void __osViInit(void) {
#if !defined(VERSION_JP)
    sTvType = osTvType;
#endif

    bzero(sViContexts, sizeof(sViContexts));
    __osViCurr = &sViContexts[0];
    __osViNext = &sViContexts[1];
    __osViNext->retraceCount = 1;
    __osViCurr->retraceCount = 1;

#if defined(VERSION_JP)
    if (sTvType != 0) {
        __osViNext->modep = &osViModeNtscLan1;
        osViClock = VI_NTSC_CLOCK;
    } else {
        __osViNext->modep = &osViModePalLan1;
        osViClock = VI_PAL_CLOCK;
    }
#else
    if (sTvType == OS_TV_TYPE_NTSC) {
        __osViNext->modep = &osViModeNtscLan1;
        osViClock = VI_NTSC_CLOCK;
    } else {
        __osViNext->modep = &osViModePalLan1;
        osViClock = VI_MPAL_CLOCK;
    }
#endif

    __osViNext->state = VI_STATE_BLACK;
    __osViNext->control = __osViNext->modep->comRegs.ctrl;

    while (IO_READ(VI_CURRENT_REG) > 10) {
        ;
    }
    IO_WRITE(VI_STATUS_REG, 0);
    __osViSwapContext();
}

