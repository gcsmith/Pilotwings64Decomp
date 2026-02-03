#include <macros.h>
#include <uv_math.h>
#include <uv_vector.h>

f32 uvVec3Len(Vec3F* v) {
    return uvSqrtF(SQ(v->x) + SQ(v->y) + SQ(v->z));
}

f32 uvVec2Dot(Vec3F* v0, Vec3F* v1) {
    return (v0->x * v1->x) + (v0->y * v1->y);
}

f32 uvVec3Dot(Vec3F* v0, Vec3F* v1) {
    return (v0->x * v1->x) + (v0->y * v1->y) + (v0->z * v1->z);
}

void uvVec3Copy(Vec3F* vdst, Vec3F* vsrc) {
    vdst->x = vsrc->x;
    vdst->y = vsrc->y;
    vdst->z = vsrc->z;
}

f32 uvVec3ScalarProj(Vec3F* v0, Vec3F* v1) {
    f32 len;
    f32 dot;

    dot = uvVec3Dot(v0, v1);
    len = uvVec3Len(v0);
    return dot / (uvVec3Len(v1) * len);
}

void uvVec3Cross(Vec3F* vd, Vec3F* va, Vec3F* vb) {
    f32 ax = va->x, ay = va->y, az = va->z;
    f32 bx = vb->x, by = vb->y, bz = vb->z;

    vd->x = ((ay * bz) - (az * by));
    vd->y = -((ax * bz) - (az * bx));
    vd->z = ((ax * by) - (ay * bx));
}

void uvVec3Add(Vec3F* vd, Vec3F* va, Vec3F* vb) {
    vd->x = va->x + vb->x;
    vd->y = va->y + vb->y;
    vd->z = va->z + vb->z;
}

void uvVec3Mul(Vec3F* vd, Vec3F* va, f32 sb) {
    vd->x = va->x * sb;
    vd->y = va->y * sb;
    vd->z = va->z * sb;
}

s32 uvVec3Normal(Vec3F* vd, Vec3F* va) {
    f32 ax = va->x, ay = va->y, az = va->z;
    f32 len, len_inv;

    len = uvSqrtF(SQ(ax) + SQ(ay) + SQ(az));
    if (len == 0.0f) {
        return 0;
    }
    len_inv = 1.0f / len;
    vd->x = ax * len_inv;
    vd->y = ay * len_inv;
    vd->z = az * len_inv;
    return 1;
}
