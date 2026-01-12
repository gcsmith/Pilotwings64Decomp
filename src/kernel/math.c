#include <stdlib.h>
#include <uv_matrix.h>

extern s32 gRandLcgState;
extern s32 gRandluxState1;
extern s32 gRandluxState2;

void uvRandSeed(s32 seed) {
    gRandLcgState = seed;
}

f32 uvRandF_RANLUX(void) {
    ldiv_t result;
    s32 var_v1;

    result = ldiv(gRandluxState1, 0xD1A4);
    gRandluxState1 = (result.rem * 0x9C4E) - (result.quot * 0x2FB3);
    if (gRandluxState1 < 0) {
        gRandluxState1 = gRandluxState1 + 0x7FFFFFAB;
    }
    result = ldiv(gRandluxState2, 0xCE26);
    gRandluxState2 = (result.rem * 0x9EF4) - (result.quot * 0xECF);
    if (gRandluxState2 < 0) {
        gRandluxState2 = gRandluxState2 + 0x7FFFFF07;
    }
    var_v1 = gRandluxState1 - gRandluxState2;
    if (var_v1 <= 0) {
        var_v1 += 0x7FFFFFAA;
    }
    return (f32) (var_v1 - 1) / 2.1474835e9f;
}

#if 1
#pragma GLOBAL_ASM("asm/nonmatchings/kernel/math/uvRandF_LCG.s")
#else
f32 uvRandF_LCG(void) {
    gRandLcgState = (gRandLcgState * 0x41C64E6D) + 0x3039;
    if (((gRandLcgState >> 0x10) & 0x7FFF) < 0) {
        return ((gRandLcgState >> 0x10) & 0x7FFF) + 4294967296.0f;
    }
    return ((gRandLcgState >> 0x10) & 0x7FFF) / 32767.0f;
}

#endif

s32 uvAbs(s32 x) {
    if (x > 0) {
        return x;
    } else {
        return -x;
    }
}

f32 uvVec3Len(Vec3F_t v) {
    f32 x = v[0];
    f32 y = v[1];
    f32 z = v[2];
    return SqrtF((x * x) + (y * y) + (z * z));
}

f32 uvVec2Dot(Vec3F_t v0, Vec3F_t v1) {
    return (v0[1] * v1[1]) + (v1[0] * v0[0]);
}

#if 1
#pragma GLOBAL_ASM("asm/nonmatchings/kernel/math/uvVec3Dot.s")
#else
f32 uvVec3Dot(Vec3F_t v0, Vec3F_t v1) {
    return (v0[0] * v1[0]) + (v0[1] * v1[1]) + (v1[2] * v0[2]);
}
#endif

void uvVec3Copy(Vec3F_t vdst, Vec3F_t vsrc) {
    vdst[0] = vsrc[0];
    vdst[1] = vsrc[1];
    vdst[2] = vsrc[2];
}

f32 uvVec3ScalarProj(Vec3F_t v0, Vec3F_t v1) {
    f32 len;
    f32 dot;

    dot = uvVec3Dot(v0, v1);
    len = uvVec3Len(v0);
    return dot / (uvVec3Len(v1) * len);
}

void uvVec3Cross(Vec3F_t vd, Vec3F_t va, Vec3F_t vb) {
    f32 ax = va[0], ay = va[1], az = va[2];
    f32 bx = vb[0], by = vb[1], bz = vb[2];

    vd[0] =  ((ay * bz) - (az * by));
    vd[1] = -((ax * bz) - (az * bx));
    vd[2] =  ((ax * by) - (ay * bx));
}

void uvVec3Add(Vec3F_t vd, Vec3F_t va, Vec3F_t vb) {
    vd[0] = vb[0] + va[0];
    vd[1] = vb[1] + va[1];
    vd[2] = vb[2] + va[2];
}

void uvVec3Mul(Vec3F_t vd, Vec3F_t va, f32 sb) {
    vd[0] = va[0] * sb;
    vd[1] = va[1] * sb;
    vd[2] = va[2] * sb;
}

s32 uvVec3Normal(Vec3F_t vd, Vec3F_t va) {
    f32 ax = va[0], ay = va[1], az = va[2];
    f32 len, len_inv;

    len = SqrtF((ax * ax) + (ay * ay) + (az * az));
    if (len == 0.0f) {
        return 0;
    }
    len_inv = 1.0f / len;
    vd[0] = (f32) (ax * len_inv);
    vd[1] = (f32) (ay * len_inv);
    vd[2] = (f32) (az * len_inv);
    return 1;
}

