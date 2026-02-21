#ifndef PILOTWINGS64_UV_MATH
#define PILOTWINGS64_UV_MATH

#include <PR/ultratypes.h>

// from kernel/rand
void uvRandSeed(s32 seed);
f32  uvRandF_RANLUX(void);
f32  uvRandF_LCG(void);
s32  uvAbs(s32 x);

// from kernel/math
f32 uvSqrtF(f32);
f32 uvSinF(f32 x);
f32 uvCosF(f32 x);
f32 uvLength2D(f32 x, f32 y);
f32 uvLength3D(f32 x, f32 y, f32 z);
f32 uvAtan2F(f32 y, f32 x);

#endif // PILOTWINGS64_UV_MATH

