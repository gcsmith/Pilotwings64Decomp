#include "PR/os_internal.h"
#include "PR/ultraerror.h"
#include "PR/rcp.h"
#include "PRinternal/osint.h"

s32 osAiSetNextBuffer(void* bufPtr, u32 size) {
    static u8 hdwrBugFlag = FALSE;
    void* bptr;

    bptr = bufPtr;
    if (hdwrBugFlag != 0) {
        bptr = (u8*)bufPtr - 0x2000;
    }
    
    if (((s32) ((u32)bufPtr + size) & 0x3FFF) == 0x2000) {
        hdwrBugFlag = 1;
    } else {
        hdwrBugFlag = 0;
    }
    
    if (__osAiDeviceBusy() != 0) {
        return -1;
    }
    
    IO_WRITE(AI_DRAM_ADDR_REG, osVirtualToPhysical(bptr));
    IO_WRITE(AI_LEN_REG, size);
    return 0;
}

