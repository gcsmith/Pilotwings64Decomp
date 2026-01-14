#include <macros.h>
#include <stdlib.h>
#include <uv_matrix.h>

extern u32 gRandLcgState;
extern s32 gRanluxState1;
extern s32 gRanluxState2;

void uvRandSeed(s32 seed) {
    gRandLcgState = seed;
}

f32 uvRandF_RANLUX(void) {
    ldiv_t result;
    s32 var_v1;

    result = ldiv(gRanluxState1, 0xD1A4);
    gRanluxState1 = (result.rem * 0x9C4E) - (result.quot * 0x2FB3);
    if (gRanluxState1 < 0) {
        gRanluxState1 = gRanluxState1 + 0x7FFFFFAB;
    }
    result = ldiv(gRanluxState2, 0xCE26);
    gRanluxState2 = (result.rem * 0x9EF4) - (result.quot * 0xECF);
    if (gRanluxState2 < 0) {
        gRanluxState2 = gRanluxState2 + 0x7FFFFF07;
    }
    var_v1 = gRanluxState1 - gRanluxState2;
    if (var_v1 <= 0) {
        var_v1 += 0x7FFFFFAA;
    }
    return (f32)(var_v1 - 1) / 2.1474835e9f;
}

f32 uvRandF_LCG(void) {
    gRandLcgState = (gRandLcgState * 0x41C64E6D) + 0x3039;
    if (((gRandLcgState >> 0x10) & 0x7FFF) < 0) {
        return ((gRandLcgState >> 0x10) & 0x7FFF) + 4294967296.0f;
    }
    return ((gRandLcgState >> 0x10) & 0x7FFF) / 32767.0f;
}

s32 uvAbs(s32 x) {
    if (x > 0) {
        return x;
    }

    return -x;
}

f32 uvVec3Len(Vec3F_t* v) {
    return SqrtF(SQ(v->x) + SQ(v->y) + SQ(v->z));
}

f32 uvVec2Dot(Vec3F_t* v0, Vec3F_t* v1) {
    return (v0->x * v1->x) + (v0->y * v1->y);
}

f32 uvVec3Dot(Vec3F_t* v0, Vec3F_t* v1) {
    return (v0->x * v1->x) + (v0->y * v1->y) + (v0->z * v1->z);
}

void uvVec3Copy(Vec3F_t* vdst, Vec3F_t* vsrc) {
    vdst->x = vsrc->x;
    vdst->y = vsrc->y;
    vdst->z = vsrc->z;
}

f32 uvVec3ScalarProj(Vec3F_t* v0, Vec3F_t* v1) {
    f32 len;
    f32 dot;

    dot = uvVec3Dot(v0, v1);
    len = uvVec3Len(v0);
    return dot / (uvVec3Len(v1) * len);
}

void uvVec3Cross(Vec3F_t* vd, Vec3F_t* va, Vec3F_t* vb) {
    f32 ax = va->x, ay = va->y, az = va->z;
    f32 bx = vb->x, by = vb->y, bz = vb->z;

    vd->x = ((ay * bz) - (az * by));
    vd->y = -((ax * bz) - (az * bx));
    vd->z = ((ax * by) - (ay * bx));
}

void uvVec3Add(Vec3F_t* vd, Vec3F_t* va, Vec3F_t* vb) {
    vd->x = va->x + vb->x;
    vd->y = va->y + vb->y;
    vd->z = va->z + vb->z;
}

void uvVec3Mul(Vec3F_t* vd, Vec3F_t* va, f32 sb) {
    vd->x = va->x * sb;
    vd->y = va->y * sb;
    vd->z = va->z * sb;
}

s32 uvVec3Normal(Vec3F_t* vd, Vec3F_t* va) {
    f32 ax = va->x, ay = va->y, az = va->z;
    f32 len, len_inv;

    len = SqrtF(SQ(ax) + SQ(ay) + SQ(az));
    if (len == 0.0f) {
        return 0;
    }
    len_inv = 1.0f / len;
    vd->x = ax * len_inv;
    vd->y = ay * len_inv;
    vd->z = az * len_inv;
    return 1;
}
