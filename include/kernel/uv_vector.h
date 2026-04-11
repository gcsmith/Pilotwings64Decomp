#ifndef PILOTWINGS64_UV_VECTOR
#define PILOTWINGS64_UV_VECTOR

#include <ultra64.h>
#include <uv_util.h>

typedef struct {
    union {
        struct { f32 x, y; };
        f32 f[2];
    };
} Vec2F;

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

f32  uvVec3Len(Vec3F *v);
f32  uvVec2Dot(Vec3F *v0, Vec3F *v1);
f32  uvVec3Dot(Vec3F *v0, Vec3F *v1);
void uvVec3Copy(Vec3F *vdst, Vec3F *vsrc);
f32  uvVec3ScalarProj(Vec3F *v0, Vec3F *v1);
void uvVec3Cross(Vec3F* vd, Vec3F* va, Vec3F* vb);
void uvVec3Add(Vec3F *vd, Vec3F *va, Vec3F *vb);
void uvVec3Mul(Vec3F *vd, Vec3F *va, f32 sb);
s32  uvVec3Normal(Vec3F *vd, Vec3F *va);

#endif // PILOTWINGS64_UV_VECTOR

