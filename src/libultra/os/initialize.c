#include "PR/os_internal.h"
#include "PRinternal/piint.h"

typedef struct {
    /* 0x0 */ unsigned int inst1;
    /* 0x4 */ unsigned int inst2;
    /* 0x8 */ unsigned int inst3;
    /* 0xC */ unsigned int inst4;
} __osExceptionVector;
extern __osExceptionVector __osExceptionPreamble[];

OSTime osClockRate = OS_CLOCK_RATE;
u32 __osShutdown = 0;
u32 __osFinalrom;

void osInitialize(void) {
    u32 pifdata;
    u32 clock = 0;

    __osFinalrom = TRUE;

    __osSetSR(__osGetSR() | SR_CU1);
    __osSetFpcCsr(FPCSR_FS | FPCSR_EV | FPCSR_RM_RN);

    while (__osSiRawReadIo(PIF_RAM_END - 3, &pifdata)) { // last byte of joychannel ram
        ;
    }
    while (__osSiRawWriteIo(PIF_RAM_END - 3, pifdata | 8)) {
        ; // todo: magic contant
    }
    *(__osExceptionVector*)UT_VEC = *__osExceptionPreamble;
    *(__osExceptionVector*)XUT_VEC = *__osExceptionPreamble;
    *(__osExceptionVector*)ECC_VEC = *__osExceptionPreamble;
    *(__osExceptionVector*)E_VEC = *__osExceptionPreamble;
    osWritebackDCache((void*)UT_VEC, E_VEC - UT_VEC + sizeof(__osExceptionVector));
    osInvalICache((void*)UT_VEC, E_VEC - UT_VEC + sizeof(__osExceptionVector));
    osMapTLBRdb();
    osPiRawReadIo(4, &clock);
    clock &= ~0xf;
    if (clock != 0)
    {
        osClockRate = clock;
    }
    osClockRate = osClockRate * 3 / 4;

    if (osResetType == 0) { // cold reset
        bzero(osAppNMIBuffer, OS_APP_NMI_BUFSIZE);
    }
}

