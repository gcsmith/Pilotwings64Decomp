#ifndef PILOTWINGS64_UV_UTILS_H
#define PILOTWINGS64_UV_UTILS_H

#include <uv_common.h>

void uvRandSeed(s32 seed);
f32  uvRandF_RANLUX(void);
f32  uvRandF_LCG(void);
s32  uvAbs(s32 x);

#endif // PILOTWINGS64_UV_UTILS_H

