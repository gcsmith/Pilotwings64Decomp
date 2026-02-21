#ifndef PILOTWINGS64_UV_MEMORY
#define PILOTWINGS64_UV_MEMORY

#include <ultra64.h>
#include <uv_util.h>
#include <uv_sprite.h>

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
    void* UVSY[1];
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


#define LEVEL_LIGHT_COUNT 4
#define LEVEL_ENVIRONMENT_COUNT 32
#define LEVEL_MODEL_COUNT 400
#define LEVEL_CONTOUR_COUNT 128
#define LEVEL_TEXTURE_COUNT 500
#define LEVEL_TERRA_COUNT 10
#define LEVEL_SEQUENCE_COUNT 10
#define LEVEL_ANIMATION_COUNT 170
#define LEVEL_FONT_COUNT 20
#define LEVEL_BLIT_COUNT 125

#define LEVEL_OBJECT_COUNT 1000

typedef struct ParsedUVLV {
    /* 0x00 */ u16* terraIds;
    /* 0x04 */ u16 terraCount;
    /* 0x08 */ u16* lightIds;
    /* 0x0C */ u16 lightCount;
    /* 0x10 */ u16* environmentIds;
    /* 0x14 */ u16 environmentCount;
    /* 0x18 */ u16* modelIds;
    /* 0x1C */ u16 modelCount;
    /* 0x20 */ u16* contourIds;
    /* 0x24 */ u16 contourCount;
    /* 0x28 */ u16* textureIds;
    /* 0x2C */ u16 textureCount;
    /* 0x30 */ u16* sequenceIds;
    /* 0x34 */ u16 sequenceCount;
    /* 0x38 */ u16* animationIds;
    /* 0x3C */ u16 animationCount;
    /* 0x40 */ u16* fontIds;
    /* 0x44 */ u16 fontCount;
    /* 0x48 */ u16* blitIds;
    /* 0x4C */ u16 blitCount;
} ParsedUVLV; // size = 0x4E

typedef struct LevelData {
    ParsedUVLV* level;
    void* terras[LEVEL_TERRA_COUNT];
    s32 terraCount;
    void* lights[LEVEL_LIGHT_COUNT];
    s32 lightCount;
    void* environments[LEVEL_ENVIRONMENT_COUNT];
    s32 environmentCount;
    void* models[LEVEL_MODEL_COUNT];
    s32 modelCount;
    void* contours[LEVEL_CONTOUR_COUNT];
    s32 contourCount;
    ParsedUVTX* textures[LEVEL_TEXTURE_COUNT];
    s32 textureCount;
    void* sequences[LEVEL_SEQUENCE_COUNT];
    s32 sequenceCount;
    void* animations[LEVEL_ANIMATION_COUNT];
    s32 animationCount;
    void* fonts[LEVEL_FONT_COUNT];
    s32 fontCount;
    void* blits[LEVEL_BLIT_COUNT];
    s32 blitCount;
    f32 unk1608;
} LevelData; // size = 0x160C

typedef struct unk_802B53C0 {
    u16 unk0;
    u16* unk4;
    u16* unk8;
} unk_802B53C0; // size >= 0x8

extern void* D_802B6E30[LEVEL_TEXTURE_COUNT];
extern LevelData gLevelData;
extern unk_802B53C0* D_802B53C0;

extern UVBlockCounts gUVBlockCounts; // D_802B53C8
extern UVBlockOffsets gUVBlockOffsets; // D_802B53F0

void mio0_decompress(void* src, u8* dst);

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

s32 uvFileWrite(u8* dst, s32 offs, s32 nbytes);
s32 uvFileRead(void* dst, s32 offs, s32 nbytes);

// TODO: from code_32480.c (filesystem?)
void* func_802314D0(s32 arg0, s32 arg1);

#endif // PILOTWINGS64_UV_MEMORY
