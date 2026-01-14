#ifndef PILOTWINGS64_UV_MEMORY
#define PILOTWINGS64_UV_MEMORY

#include <ultra64.h>
#include <uv_util.h>

typedef struct {
    float unk0;
    u16 uvVersion;
    u16 UVMD;
    u16 UVCT;
    u16 UVTX;
    u16 UVEN;
    u16 UVLT;
    u16 UVTR;
    u16 UVSQ;
    u16 UVLV;
    u16 UVAN;
    u16 UVFT;
    u16 UVBT;
    u16 unk1C;
    u16 UVSX;
    u16 UVTP;
    u16 unk22;
} UVBlockCounts;

typedef struct {
    void* UVSY;
    void* UVMD[0x190];
    void* UVCT[0x80];
    void* UVTX[0x1F4];
    void* UVEN[0x20];
    void* UVLT[4];
    void* UVTR[0xA];
    void* UVSQ[0xA];
    void* UVLV[0x96];
    void* UVAN[0xAA];
    void* UVFT[0x14];
    void* UVBT[0x7D];
    void* unk1838[0x80];
    void* UVSX[1];
    void* UVTP[1];
} UVBlockOffsets;

extern void* D_802B53C0;
extern UVBlockCounts gUVBlockCounts; // D_802B53C8
extern UVBlockOffsets gUVBlockOffsets; // D_802B53F0

void uvMemInitBlocks(void);

void func_8022A47C(void);

void _uvMediaCopy(void* vAddr, void* devAddr, u32 nbytes);
void _uvDMA(void* vAddr, u32 devAddr, u32 nbytes);

void uvMemScanBlocks(void);

s32 _uvJumpHeap(u32* arg0);

u64 uvMemRead(void* vAddr, u32 nbytes);
void uvMemSet(void* vAddr, u8 value, u32 nbytes);

s32 uvMemCmp(u8* lhs, u8* rhs, u32 count);

s32 _uvMemOverAlloc(u32 size, u32 alignment);
s32 _uvMemAlloc(u32 size, u32 alignment);

void _uvMemGetBlocks(u32 arg0, u32 arg1);

void _uvMemFreeScratch(void *addr);
void *_uvMemGetScratch(u32 size);

void uvLevelInit(void);
s32 _uvMemAllocAlign8(u32 size);

#endif // PILOTWINGS64_UV_MEMORY
