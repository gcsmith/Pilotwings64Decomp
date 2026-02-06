#ifndef PILOTWINGS64_UV_GRAPHICS
#define PILOTWINGS64_UV_GRAPHICS

#include <PR/ultratypes.h>
#include <PR/gbi.h>
#include <uv_util.h>
#include <uv_matrix.h>

#define UV_GFX_NUM_MATRICES 0x15E
#define UV_GFX_NUM_LOOKS 0x1E

#define GFX_PATCH_DL(pkt, patchDL, patchArg)                                   \
{                                                                              \
    Gfx *_g = (Gfx *)(pkt);                                                    \
    _g->words.w0 = (patchDL->words.w0 & 0xFF00FFFF) | _SHIFTL(patchArg, 16, 8);\
    _g->words.w1 = patchDL->words.w1;                                          \
}

typedef void (*uvGfxCallback_t)(void *, s32); 

typedef struct {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    s32 unk8;
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
    u8 pad[0x58];
} UnkStruct_uvGfxInit;

typedef struct {
    s32 unk0;
    Gfx *unk4;
} uvGfxUnkStruct2;

typedef struct {
    u8 pad0[0x910];
    uvGfxUnkStruct2 *unk910[1];
} uvGfxUnkStruct;

extern Gfx* gGfxDisplayListHead;

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
void uvGfx_80223A28(s32 flags);
void uvGfx_80223A64(s32 arg0, s32 arg1);
void uvGfxWaitForMesg(void);
void uvGfxEnableGamma(s32 enable);
void uvGfxSetUnkState0(s32 arg0);
void uvGfx_80223C00(void);
void uvCopyFrameBuf(s32 fb_id);

void uvFontSet(s32);
void uvFont_80219550(f64, f64);
void uvFont_8021956C(u8, u8, u8, u8);
s32 uvFontWidth(char*);
void uvFont_80219EA8(void);
void uvFont_80219ACC(s32, s32, char*);

#endif // PILOTWINGS64_UV_GRAPHICS
