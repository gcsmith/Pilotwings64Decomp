#ifndef PILOTWINGS64_UV_MATH
#define PILOTWINGS64_UV_MATH

#include <ultra64.h>
#include <uv_util.h>

typedef struct {
    union {
        struct { f32 x, y, z; };
        f32 f[3];
    };
} Vec3F;

typedef struct {
    union {
        struct { f32 x, y, z, w; };
        f32 f[4];
    };
} Vec4F;

void uvRandSeed(s32 seed);
f32  uvRandF_RANLUX(void);
f32  uvRandF_LCG(void);
s32  uvAbs(s32 x);
f32  uvVec3Len(Vec3F *v);
f32  uvVec2Dot(Vec3F *v0, Vec3F *v1);
f32  uvVec3Dot(Vec3F *v0, Vec3F *v1);
void uvVec3Copy(Vec3F *vdst, Vec3F *vsrc);
f32  uvVec3ScalarProj(Vec3F *v0, Vec3F *v1);
void uvVec3Cross(Vec3F* vd, Vec3F* va, Vec3F* vb);
void uvVec3Add(Vec3F *vd, Vec3F *va, Vec3F *vb);
void uvVec3Mul(Vec3F *vd, Vec3F *va, f32 sb);
s32  uvVec3Normal(Vec3F *vd, Vec3F *va);

// from code_2AE50
f32 SqrtF(f32);
f32 func_80229EC0(f32 arg0);
f32 func_8022A080(f32 arg0);
f32 Length2D(f32 arg0, f32 arg1);
f32 Length3D(f32, f32, f32);
f32 func_8022A27C(f32 arg0, f32 arg1);

#endif // PILOTWINGS64_UV_MATH

