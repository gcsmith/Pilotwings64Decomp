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
    s32 unk0;
    u8 pad[0x4];
    s32 unk8;
    u8* fb;
    OSTask task;
    OSMesgQueue* msgQueue;
    void* unk54;
} UnkStruct_uvGfxInit; // size: 0x58

typedef struct UnkTileStruct40 {
    u8 pad0[0x10];
    struct UnkSobjDraw* unk10;
} UnkTileStruct40;

typedef struct uvUnkTileStruct {
    u8 pad0[0x40];
    UnkTileStruct40* unk40;
    u8 pad44[0x4];
} uvUnkTileStruct;

typedef struct uvGfxUnkStructTerra {
    f32 unk0;
    f32 unk4;
    u8 pad8[0x4];
    f32 unkC;
    f32 unk10;
    u8 pad14[0x4];
    u8 unk18;
    f32 unk1C;
    f32 unk20;
    u8 pad24[0x4];
    uvUnkTileStruct* unk28;
} uvGfxUnkStructTerra;

typedef struct UnkGfxEnv_Unk30 {
    u16 modelId;
    u8 flag;
} UnkGfxEnv_Unk30;

typedef struct uvGfxUnkStructEnv {
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
    u8 unk34;
    void (*unk38)(void);
} uvGfxUnkStructEnv;

typedef struct {
    void* unk0;
    Gfx *unk4;
    u8 pad8[0x2];
    u16 width;
    u16 height;
    u8 unkE;
    u8 padF[0x3];
    u16 unk12;
    u16 unk14;
    struct unk_UVTX_1C* unk18;
    struct unk_UVTX_1C* unk1C;
    u8 pad20[0x2];
    u8 unk22;
} uvGfxUnkStructTexture;

typedef struct uvGfxUnkStruct10 {
    uvGfxState_t* unk0;
    u8 unk4;
    u8 pad5[0x1];
    u8 unk6;
    u8 pad7[0x6];
    u8 unkD;
    u8 padE[0x2];
} uvGfxUnkStruct10;

typedef struct uvGfxUnkStruct8 {
    uvGfxUnkStruct10* unk0;
    u8 unk4;
    u8 unk5;
    u8 pad6[0x2];
} uvGfxUnkStruct8;

typedef struct {
    u8 pad0[0x8];
    uvGfxUnkStruct8* unk8;
    f32* unkC;
    u8 unk10;
    u8 unk11;
    u8 pad12[0x2];
    void* unk14;
    u8 unk18;
    u8 pad19[0x3];
    f32 unk1C;
    f32 unk20;
} uvGfxUnkStructModel;

typedef struct {
    Vec4F unk0;
    u32 unk10_0 : 15;
    u32 unk10_15 : 1;
    u32 pad12_0 : 16;
} Unk8037DCA0_UnkC; // size = 0x14

typedef struct uvGfxUnkStructAnim0 {
    struct uvGfxUnkStructAnim0* unk0;
    u16 unk4;
    u8 pad6[0x2];
    s32 unk8;
    Unk8037DCA0_UnkC* unkC;
} uvGfxUnkStructAnim0;

typedef struct {
    struct uvGfxUnkStructAnim0* unk0;
    u8 pad4[0x2];
    u16 unk6;
    u8 unk8;
    u8 unk9;
} uvGfxUnkStructAnimation;

typedef struct {
    u8 pad0[0x2];
    s16 bmfmt;
    s16 bitdepth;
    s16 width;
    s16 height;
    u8 padA[0x2];
    s16 texelHeight;
    s16 nbitmaps;
    u8 pad10[0x4];
    Bitmap* bitmap;
} uvGfxUnkStructBlit;

typedef struct {
    u8 pad0[0x4];
    uvGfxUnkStructTerra *unk4[1];
    u8 pad8[0x28];
    void *unk30[1];
    u8 pad34[0x10];
    uvGfxUnkStructEnv *unk44[1];
    u8 pad48[0x80];
    uvGfxUnkStructModel *unkC8[1];
    u8 padCC[0x844];
    uvGfxUnkStructTexture *unk910[1];
    u8 pad914[0x7D0];
    void *unk10E4[1];
    u8 pad10E8[0x28];
    uvGfxUnkStructAnimation* unk1110[1];
    u8 pad1114[0x2FC];
    uvGfxUnkStructBlit* unk1410[1];
    u8 pad1414[0x1F4];
    f32 unk1608;
} uvGfxUnkStruct;

extern Gfx* gGfxDisplayListHead;
extern uvGfxUnkStruct* gGfxUnkPtrs;

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

// TODO from kernel/code_19B50.c -- split into uv_font.h?
void uvFontSet(s32);
void uvFont_80219550(f64, f64);
void uvFont_8021956C(u8, u8, u8, u8);
s32 uvFontWidth(char*);
s32 func_802196B0(void*);
s32 func_80219874(s32 x, s32 y, void*, s32, s32);
void uvFont_80219EA8(void);
void uvFont_80219ACC(s32, s32, char*);

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
