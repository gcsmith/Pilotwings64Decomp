#include <stdlib.h>
#include <uv_math.h>

static u32 gRandLcgState = 1;
static s32 gRanluxState1 = 1;
static s32 gRanluxState2 = 1;

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

// Linear congruential generator with ANSI C base and multiplier
f32 uvRandF_LCG(void) {
    u32 val;
    gRandLcgState = (gRandLcgState * 1103515245) + 12345;
    val = (gRandLcgState >> 16) & 0x7FFF;
    return (f32)val / 0x7FFF;
}

s32 uvAbs(s32 x) {
    if (x > 0) {
        return x;
    }

    return -x;
}

