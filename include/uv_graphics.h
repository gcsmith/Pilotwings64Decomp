#ifndef PILOTWINGS64_UV_GRAPHICS
#define PILOTWINGS64_UV_GRAPHICS

#include <PR/ultratypes.h>
#include <PR/gbi.h>
#include <uv_util.h>
#include <uv_matrix.h>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define UV_GFX_NUM_MATRICES 0x15E
#define UV_GFX_NUM_LOOKS 0x1E

#define GFX_STATE_20000 (1 << 17)
#define GFX_STATE_40000 (1 << 18)
#define GFX_STATE_80000 (1 << 19)
#define GFX_STATE_100000 (1 << 20)
#define GFX_STATE_200000 (1 << 21)
#define GFX_STATE_400000 (1 << 22)
#define GFX_STATE_800000 (1 << 23)
#define GFX_STATE_1000000 (1 << 24)
#define GFX_STATE_2000000 (1 << 25)
#define GFX_STATE_4000000 (1 << 26)
#define GFX_STATE_8000000 (1 << 27)
#define GFX_STATE_10000000 (1 << 28)
#define GFX_STATE_20000000 (1 << 29)
#define GFX_STATE_40000000 (1 << 30)
#define GFX_STATE_80000000 (1 << 31)

#define GFX_PATCH_DL(pkt, patchDL, patchArg)                                   \
{                                                                              \
    Gfx *_g = (Gfx *)(pkt);                                                    \
    _g->words.w0 = (patchDL->words.w0 & 0xFF00FFFF) | _SHIFTL(patchArg, 16, 8);\
    _g->words.w1 = patchDL->words.w1;                                          \
}

typedef enum {
    /* 0 */ GFX_COUNT_VTX_TRANSFORMS,
    /* 1 */ GFX_COUNT_TRIS,
    /* 2 */ GFX_COUNT_MTX_LOADS,
    /* 3 */ GFX_COUNT_MTX_LOAD_MULTS,
    /* 4 */ GFX_COUNT_TXT_LOADS,
} uvGfxCntType;

typedef void (*uvGfxCallback_t)(void *, s32); 

typedef struct {
    s32 state;
    s16 unk4;
    s16 unk6;
    Gfx* unk8;
} uvGfxState_t;

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 x0; // left?
    s16 x1; // right?
    s16 y0; // top?
    s16 y1; // bottom?
    Vp vp;
} uvGfxViewport_t;

typedef struct {
    u16 unk0;
    u16 unk2;
    u16 unk4;
    u16 unk6;
} Unk80225FBC_0x28_UnkC; // size = 0x10

typedef struct {
    s32 unk0;
    u16 unk4;
    u16 unk6;
    Gfx* dlist;
    Unk80225FBC_0x28_UnkC* unkC;
    u16 unk10;
    u16 unk12;
    u16 unk14;
    u16 pad16;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
} Unk80225FBC_0x28;

typedef struct {
    Vtx* vtx;
    u16 vtxCount;
    u16 pad6;
    Unk80225FBC_0x28* unk8;
    u16 unkC;
    u16 padE;
    struct UnkSobjDraw* unk10;
    u16 unk14;
    u16 pad16;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    f32 unk28;
} ParsedUVCT; // size = 0x28

typedef struct uvUnkTileStruct_Unk0 {
    u8 pad0[0x30];
    f32 unk30;
    f32 unk34;
    f32 unk38;
    u8 pad3C[0x4];
} uvUnkTileStruct_Unk0; // size = 0x40

typedef struct uvUnkTileStruct {
    uvUnkTileStruct_Unk0 unk0;
    ParsedUVCT* unk40;
    u8 unk44;
} uvUnkTileStruct; // size = 0x48

typedef struct uvUnkTeraStruct {
    f32 unk0;
    f32 unk4;
    u8 pad8[0x4];
    f32 unkC;
    f32 unk10;
    f32 unk14;
} uvUnkTeraStruct; // size = 0x18

typedef struct ParsedUVTR {
    uvUnkTeraStruct unk0;
    u8 unk18;
    u8 unk19;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    uvUnkTileStruct* unk28;
} ParsedUVTR; // size = 0x2C

typedef struct UnkGfxEnv_Unk30 {
    u16 modelId;
    u8 flag;
} UnkGfxEnv_Unk30;

typedef struct ParsedUVEN {
    u8 screenR;
    u8 screenG;
    u8 screenB;
    u8 screenA;
    u8 fogR;
    u8 fogG;
    u8 fogB;
    u8 fogA;
    u8 unk8;
    u8 unk9;
    u8 unkA;
    u8 unkB;
    u8 padC[0x8];
    f32 unk14;
    f32 unk18;
    u8 unk1C;
    u8 pad1D[0x11];
    u8 unk2E;
    struct UnkGfxEnv_Unk30* unk30;
    u8 count;
    void (*unk38)(void);
} ParsedUVEN; // size = 0x3C

typedef struct UnkUVMD_6 {
    u16 unk0;
    u16 unk2;
    u16 unk4;
} UnkUVMD_6; // size = 0x6

typedef struct UnkUVMD_24_Unk4 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
} UnkUVMD_24_Unk4;
typedef struct UnkUVMD_24 {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 pad3[0x1];
    UnkUVMD_24_Unk4 unk4;
    u16 unk1C;
    UnkUVMD_6* unk20;
} UnkUVMD_24;

typedef struct UnkUVMD_10 {
    uvGfxState_t* unk0;
    u8 unk4;
    u8 unk5;
    u8 unk6;
    UnkUVMD_24* unk8;
    u8 unkC;
    u8 unkD;
} UnkUVMD_10; // size = 0x10

typedef struct UnkUVMD_8 {
    UnkUVMD_10* unk0;
    u8 unk4;
    u8 unk5;
} UnkUVMD_8; // size = 0x8

typedef struct ParsedUVMD {
    Vtx* vtx;
    u16 vtxCount;
    UnkUVMD_8* unk8;
    f32* unkC;
    u8 unk10;
    u8 unk11;
    Mtx4F* unk14;
    u8 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
} ParsedUVMD; // size = 0x28

typedef struct UnkUVTX_1C {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    u8 unk18;
} UnkUVTX_1C; // size = 0x1C

typedef struct ParsedUVTX {
    void* unk0;
    Gfx* unk4;
    u16 size;
    u16 width;
    u16 height;
    u8 unkE;
    u8 unkF;
    u8 unk10;
    u16 unk12;
    u16 unk14;
    UnkUVTX_1C* unk18;
    UnkUVTX_1C* unk1C;
    u16 unk20;
    u8 unk22;
    u8 unk23;
    u8 unk24;
    u8 unk25;
    u8 unk26;
    f32 unk28;
} ParsedUVTX; // size = 0x2C

typedef struct ParsedUVSQ_Unk4 {
    u16 unk0;
    u8 unk2;
    f32 unk4;
} ParsedUVSQ_Unk4; // size = 0x8

typedef struct ParsedUVSQ {
    u8 count;
    ParsedUVSQ_Unk4* unk4;
    u8 unk8;
    u8 unk9;
    f32 unkC;
} ParsedUVSQ;

typedef struct uvGfxUnkStructSequence_Unk4 {
    u16 unk0;
    f32 unk4;
} uvGfxUnkStructSequence_Unk4; // size = 0x8

typedef struct uvGfxUnkStructSequence {
    u8 unk0;
    uvGfxUnkStructSequence_Unk4* unk4;
    u8 unk8;
    u8 unk9;
    f32 unkC;
} uvGfxUnkStructSequence;

typedef struct {
    Vec4F unk0;
    u32 unk10_0 : 15;
    u32 unk10_15 : 1;
    u32 pad12_0 : 16;
} Unk8037DCA0_UnkC; // size = 0x14

typedef struct ParsedUVAN_Unk0 {
    struct ParsedUVAN_Unk0* unk0;
    u16 unk4;
    u8 pad6[0x2];
    u32 unk8;
    Unk8037DCA0_UnkC* unkC;
} ParsedUVAN_Unk0;

typedef struct {
    struct ParsedUVAN_Unk0* unk0;
    u16 modelId;
    u16 unk6;
    u8 unk8;
    u8 unk9;
} ParsedUVAN;

typedef struct ParsedUVFT {
    char* str;
    u8 pad4[0x4];
    u8 bmfmt;
    u8 bmsiz;
    Bitmap* bitmap;
    void* imag[0x2C];
} ParsedUVFT; // size = 0x80

typedef struct uvGfxUnkStructFont {
    char* unk0;
    u8 pad4[0x4];
    u8 bmfmt;
    u8 bmsiz;
    Bitmap* unkC;
} uvGfxUnkStructFont;

typedef struct {
    u8 pad0[0x2];
    s16 bmfmt;
    s16 bitdepth;
    s16 width;
    s16 height;
    s16 unkA;
    s16 texelHeight;
    s16 nbitmaps;
    void* buf;
    Bitmap* bitmap;
} ParsedUVBT;

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

typedef struct uvLevelData {
    /* 0x0000 */ ParsedUVLV* level;
    /* 0x0004 */ ParsedUVTR* terras[LEVEL_TERRA_COUNT];
    /* 0x002C */ s32 terraCount;
    /* 0x0030 */ void* lights[LEVEL_LIGHT_COUNT];
    /* 0x0040 */ s32 lightCount;
    /* 0x0044 */ ParsedUVEN* environments[LEVEL_ENVIRONMENT_COUNT];
    /* 0x00C4 */ s32 environmentCount;
    /* 0x00C8 */ ParsedUVMD* models[LEVEL_MODEL_COUNT];
    /* 0x0708 */ s32 modelCount;
    /* 0x070C */ ParsedUVCT* contours[LEVEL_CONTOUR_COUNT];
    /* 0x090C */ s32 contourCount;
    /* 0x0910 */ ParsedUVTX* textures[LEVEL_TEXTURE_COUNT];
    /* 0x10E0 */ s32 textureCount;
    /* 0x10E4 */ ParsedUVSQ* sequences[LEVEL_SEQUENCE_COUNT];
    /* 0x110C */ s32 sequenceCount;
    /* 0x1110 */ ParsedUVAN* animations[LEVEL_ANIMATION_COUNT];
    /* 0x13B8 */ s32 animationCount;
    /* 0x13BC */ ParsedUVFT* fonts[LEVEL_FONT_COUNT];
    /* 0x140C */ s32 fontCount;
    /* 0x1410 */ ParsedUVBT* blits[LEVEL_BLIT_COUNT];
    /* 0x1604 */ s32 blitCount;
    /* 0x1608 */ f32 unk1608;
} uvLevelData; // size = 0x160C

extern Gfx* gGfxDisplayListHead;
extern uvLevelData* gGfxUnkPtrs;
extern u16 gGfxFbIndex;
extern u32 gGfxStateStackData;
extern u32 D_8029926C;

void uvGfxInit(void);
void uvGfxBegin(void);
void uvGfxSetFogFactor(f32 arg0);
void uvGfxResetState(void);
void uvGfxMtxView(Mtx src);
void uvGfxMtxProj(Mtx src);
void uvGfxDisplayList(Gfx* dl);
void uvGfxStateDrawDL(uvGfxState_t* arg0);
void uvGfxStateDraw(uvGfxState_t* arg0);
void uvGfxPushMtxUnk(Mtx4F*);
void uvGfxClampLook(LookAt*, f32, f32, f32, f32, f32, f32, f32, f32, f32);
void uvGfxLookAt(Mtx4F* arg0);
void uvGfxMtxProjPushF(Mtx4F*);
void uvGfxSetCallback(uvGfxCallback_t cb);
void uvGfxEnd(void);
void uvGfxClearScreen(u8 r, u8 g, u8 b, u8 a);
void uvGfx_80222A98(void);
void uvGfxEnableZBuffer(s32 enable);
void uvGfxEnableCull(s32 enable_front, s32 enable_back);
void uvGfxEnableLighting(s32 enable);
void uvGfxClipRect(uvGfxViewport_t* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void uvGfxClipViewport(s32 vp_id, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void uvGfxSetViewport(s32 vp_id, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void uvGfxViewport(s32 vp_id);
void uvGfxMstackPushF(Mtx4F* src);
void uvGfxMstackPushL(Mtx src);
Mtx* uvGfxMstackTop(void);
void uvGfxSetUnkStateF(f32 arg0);
f32  uvGfxGetUnkStateF(void);
void uvGfxMtxViewLoad(Mtx4F* src, s32 push);
void uvGfxMtxViewMul(Mtx4F* src, s32 push);
void uvGfx_802235A4(Mtx src, u8 push);
void uvGfxMtxViewPop(void);
void uvGfx_802236CC(Mtx4F *arg0);
s32  uvGfxGetCnt(u32 arg0);
void uvGfxStatePush(void);
void uvGfxStatePop(void);
void uvGfxSetFlags(s32 flags);
void uvGfxClearFlags(s32 flags);
void uvGfx_80223A28(u32 flags);
void uvGfx_80223A64(s32 arg0, s32 arg1);
void uvGfxWaitForMesg(void);
void uvGfxEnableGamma(s32 enable);
void uvGfxSetUnkState0(s32 arg0);
void uvGfx_80223C00(void);
void uvCopyFrameBuf(s32 fb_id);

// TODO from kernel/code_58E0 -- split into uv_???
typedef struct {
/* 000 */ u8 unk0;
/* 001 */ u8 unk1;
/* 002 */ u16 unk2;
/* 004 */ u16 unk4;
/* 006 */ u16 unk6[5]; // unknown size, might be up to 0x6 - 0x10
/* 010 */ Mtx4F unk10;
/* 050 */ Mtx unk50;
/* 090 */ Mtx4F unk90;
/* 0D0 */ Mtx unkD0;
/* 110 */ Mtx4F unk110;
/* 150 */ Mtx unk150;
/* 190 */ Mtx4F unk190;
/* 1D0 */ f32 unk1D0;
/* 1D4 */ f32 unk1D4;
/* 1D8 */ f32 unk1D8;
/* 1DC */ f32 unk1DC;
/* 1E0 */ f32 unk1E0;
/* 1E4 */ f32 unk1E4;
/* 1E8 */ f32 unk1E8;
/* 1EC */ f32 unk1EC;
/* 1F0 */ f32 unk1F0;
/* 1F4 */ f32 unk1F4;
/* 1F8 */ f32 unk1F8;
/* 1FC */ f32 unk1FC;
/* 200 */ f32 unk200;
/* 204 */ f32 unk204;
/* 208 */ u8 pad208[0xD8];
/* 2E0 */ u8 unk2E0[0x90];
/* 370 */ s32 unk370;
/* 374 */ s32 unk374;
/* 378 */ s32 unk378;
/* 37C */ s32 unk37C;
/* 380 */ s32 unk380;
/* 384 */ s32 unk384;
/* 388 */ s32 unk388;
/* 38C */ s16 unk38C;
/* 38E */ s16 unk38E;
/* 390 */ s16 unk390;
/* 392 */ s16 unk392;
/* 394 */ u32 pad394;
/* 398 */ void (*unk398)(void);
/* 39C */ void (*unk39C)(void);
} UnkStruct_80204D94; // size 3A0

extern UnkStruct_80204D94 D_80261730[];

void uvChanTerra(s32, s32);
void uvChanEnv(s32 arg0, s32 arg1);
void func_80204A8C(s32 arg0, s32 arg1);
void func_80204B08(s32 arg0, s32 arg1, s32 arg2);
void func_80204B34(s32 arg0, Mtx4F* arg1);
void func_80204C54(s32 arg0, Mtx4F *arg1);
void func_80204D94(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
u8*  func_80204F9C(s32 arg0);
void func_80204FC4(s32 arg0);
void func_80204FE4(s32 arg0);
void func_802057F4(Mtx4F *arg0, Mtx4F *arg1);
void func_80204AB0(s32 arg0, s32 arg1, void (*arg2)(void));
void func_80204BD4(s32 arg0, s32 arg1, f32 arg2);
void func_80204930(void);
void func_80205724(s32, s32, Mtx4F*);
void func_80204C94(s32, f32, f32, f32, f32, f32, f32);

#endif // PILOTWINGS64_UV_GRAPHICS
