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
void func_8022427C(u32 arg0);
void func_80230954(void);
void func_80223B80(void);
s32 func_80223E80(void* addr);
void func_80223F30(s32 arg0);
s32 func_80223F7C(s32, u32*, void**, s32);
s32 func_80224170(s32, void*, void**, s32, s32, s32);

#endif // PILOTWINGS64_UV_GRAPHICS
