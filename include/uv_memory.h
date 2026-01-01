#ifndef PILOTWINGS64_UV_MEMORY
#define PILOTWINGS64_UV_MEMORY

#include <ultra64.h>

void _uvDebugPrintf(char* fmt, ...);
void _uvAssertMsg(char* expr, char* filename, s32 line);

void _uvMediaCopy(void* vAddr, void* devAddr, u32 nbytes);
void _uvDMA(void* vAddr, u32 devAddr, u32 nbytes);

u64 uvMemRead(void* vAddr, u32 nbytes);
void uvMemSet(void* vAddr, u8 value, u32 nbytes);

#endif // PILOTWINGS64_UV_MEMORY

