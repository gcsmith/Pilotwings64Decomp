#ifndef PILOTWINGS64_UV_MATH
#define PILOTWINGS64_UV_MATH

#include <ultra64.h>
#include <uv_util.h>

typedef struct {
    union {
        struct { f32 x, y, z; };
        f32 f[3];
    };
} Vec3F_t;

typedef struct {
    union {
        struct { f32 x, y, z, w; };
        f32 f[4];
    };
} Vec4F_t;

f32 SqrtF(f32);
void uvRandSeed(s32 seed);
f32 uvRandF(void);
s32 uvAbs(s32 x);
f32 uvVec3Len(Vec3F_t *v);
f32 uvVec2Dot(Vec3F_t *v0, Vec3F_t *v1);
f32 uvVec3Dot(Vec3F_t *v0, Vec3F_t *v1);
void uvVec3Copy(Vec3F_t *vdst, Vec3F_t *vsrc);
f32 uvVec3ScalarProj(Vec3F_t *v0, Vec3F_t *v1);
void uvVec3Add(Vec3F_t *vd, Vec3F_t *va, Vec3F_t *vb);
void uvVec3Mul(Vec3F_t *vd, Vec3F_t *va, f32 sb);
s32 uvVec3Normal(Vec3F_t *vd, Vec3F_t *va);

#endif // PILOTWINGS64_UV_MATH

