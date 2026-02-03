#ifndef PILOTWINGS64_UV_MATH
#define PILOTWINGS64_UV_MATH

#include <ultra64.h>
#include <uv_util.h>

// from kernel/rand
void uvRandSeed(s32 seed);
f32  uvRandF_RANLUX(void);
f32  uvRandF_LCG(void);
s32  uvAbs(s32 x);

// from kernel/code_2AE50
f32 uvSqrtF(f32);
f32 func_80229EC0(f32 arg0);
f32 func_8022A080(f32 arg0);
f32 uvLength2D(f32 arg0, f32 arg1);
f32 uvLength3D(f32, f32, f32);
f32 func_8022A27C(f32 arg0, f32 arg1);

#endif // PILOTWINGS64_UV_MATH

