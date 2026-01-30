#ifndef PILOTWINGS64_UV_GRAPHICS
#define PILOTWINGS64_UV_GRAPHICS

#include <PR/ultratypes.h>
#include <PR/gbi.h>
#include <uv_util.h>
#include <uv_matrix.h>

typedef struct {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    s32 unk8;
} uvGfxState_t;

void uvGfxInit(void);
void uvGfxBegin(void);
void uvGfxStateDraw(uvGfxState_t* arg0);
void uvGfxEnd(void);
s32 uvGfxGetCnt(u32 arg0);
void uvGfxStatePush(void);
void uvGfxStatePop(void);
void func_8022427C(s32 arg0);
s32 func_80223E80(s32 addr);
void func_80223B80(void);
void func_80223F30(s32 arg0);
u32 func_80223F7C(s32 idx, u32* sizeOut, void** arg2, s32 arg3);
void func_80230954(void);
void func_802210C4(Gfx* dl);
void func_80221A78(Mtx4F*);
void func_80222100(Mtx4F*);
void func_8022345C(Mtx4F*, s32);
void func_802236A8(void);
void uvGfxSetFlags(s32 flags);
void uvGfxClearFlags(s32 flags);
u32 func_80224170(s32 arg0, void* arg1, void** arg2, u32 tag, s32 palette, s32 arg5);
void uvGfxClearScreen(u8 r, u8 g, u8 b, u8 a);

void uvClampFunction(LookAt*, f32, f32, f32, f32, f32, f32, f32, f32, f32);
void uvGfxPushMtxView(Mtx src);
void uvGfxPushMtxProj(Mtx src);

void uvGfxMstackPushUnk(Mtx4F* src);
void uvGfxMstackPush(Mtx src);
Mtx* uvGfxMstackTop(void);

#endif // PILOTWINGS64_UV_GRAPHICS
