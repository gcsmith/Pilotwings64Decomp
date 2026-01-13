#ifndef PILOTWINGS64_UV_GRAPHICS
#define PILOTWINGS64_UV_GRAPHICS

#include <ultra64.h>
#include <uv_util.h>

void uvGfxBegin(void);
void uvGfxStateDraw(void *arg0);
void uvGfxEnd(void);
s32 uvGfxGetCnt(u32 arg0);
void uvGfxStatePush(void);
void uvGfxStatePop(void);
void func_8022427C(s32 arg0);
s32 func_80223E80(s32 addr);
void func_80223B80(void);
void func_80223F30(s32 arg0);
u32 func_80223F7C(s32 idx, u32* sizeOut, void** arg2, s32 arg3);

#endif // PILOTWINGS64_UV_GRAPHICS

