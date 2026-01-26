#ifndef PILOTWINGS64_UV_GRAPHICS
#define PILOTWINGS64_UV_GRAPHICS

#include <PR/ultratypes.h>
#include <uv_util.h>
#include <uv_matrix.h>

void func_80220960(void);
void uvGfxBegin(void);
void uvGfxStateDraw(void *arg0);
void uvGfxEnd(void);
s32 uvGfxGetCnt(u32 arg0);
void uvGfxStatePush(void);
void uvGfxStatePop(void);
void uvMemLoadDS(s32);
void func_8022427C(s32 arg0);
s32 func_80223E80(s32 addr);
void func_80223B80(void);
void func_80223F30(s32 arg0);
u32 func_80223F7C(s32 idx, u32* sizeOut, void** arg2, s32 arg3);
void func_80230954(void);
void func_80221A78(Mtx4F_t);
void func_80222100(Mtx4F_t);
void func_802236A8(void);
void uvGfxSetFlags(s32 flags);
void uvGfxClearFlags(s32 flags);
u32 func_80224170(s32 arg0, void* arg1, void** arg2, u32 tag, s32 palette, s32 arg5);
void func_802228F0(u8 r, u8 g, u8 b, u8 a);

#endif // PILOTWINGS64_UV_GRAPHICS
