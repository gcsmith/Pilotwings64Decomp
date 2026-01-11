#ifndef PILOTWINGS64_UV_MEMORY
#define PILOTWINGS64_UV_MEMORY

#include <ultra64.h>
#include <uv_util.h>

void uvMemInitBlocks(void);

void func_8022A47C(void);

void _uvMediaCopy(void* vAddr, void* devAddr, u32 nbytes);
void _uvDMA(void* vAddr, u32 devAddr, u32 nbytes);

void uvSysInit(void);

s32 _uvJumpHeap(u32* arg0);

u64 uvMemRead(void* vAddr, u32 nbytes);
void uvMemSet(void* vAddr, u8 value, u32 nbytes);

s32 uvMemCmp(u8* lhs, u8* rhs, u32 count);

s32 _uvMemOverAlloc(u32 size, u32 alignment);
s32 _uvMemAlloc(u32 size, u32 alignment);

void _uvMemGetBlocks(u32 arg0, u32 arg1);

void _uvMemFreeScratch(void *addr);
void *_uvMemGetScratch(u32 size);

#endif // PILOTWINGS64_UV_MEMORY
