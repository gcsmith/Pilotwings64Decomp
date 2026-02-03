#include "common.h"
#include <math.h>

typedef struct {
    f64 d;
} Double;

typedef struct {
    f32 f;
} Float;

static const double D_8024E3A0[] = {
    1.0, -0.166666595504277565, 0.00833306624608215474, -0.000198096029019379492, 2.60578063796803717e-06,
};

// to make the code use the matching operand order, these should be float literals
// however, the compiler doubles D_8024E3C8, D_8024E3D0, D_8024E3D8 in .rodata
// if using `static const`, compiler places D_8024E3C8, D_8024E3D0, D_8024E3D8 in .data
#define USE_CONST_DATA
#ifdef USE_FLOAT_LITERAL
#define D_8024E3C8 0.318309886183790691
#define D_8024E3D0 3.14159262180328369
#define D_8024E3D8 3.17865095470563921e-08
#elif defined(USE_CONST_DATA)
static const Double D_8024E3C8 = { 0.318309886183790691 };
static const Double D_8024E3D0 = { 3.14159262180328369 };
static const Double D_8024E3D8 = { 3.17865095470563921e-08 };
static const Float zero = { 0.0f };
#endif

f32 uvSqrtF(f32 value) {
    return sqrtf(value);
}

f32 uvSinF(f32 x) {
    f64 dx;   // sp20
    f64 xsq;  // sp18
    f64 poly; // sp10
    f64 temp_fa1;
    s32 number; // sp8
    s32 ix;     // sp4

    ix = *(s32*)&x;

    if (((ix >> 22) & 0x1FF) < 0xFF) {
        dx = x;
        if (((ix >> 22) & 0x1FF) >= 0xE6) {
            xsq = SQ(dx);

            temp_fa1 = ((((D_8024E3A0[4] * xsq) + D_8024E3A0[3]) * xsq + D_8024E3A0[2]) * xsq + D_8024E3A0[1]);

            return (dx * xsq) * temp_fa1 + dx;
        }
        return x;
    }

    if (((ix >> 22) & 0x1FF) < 0x136) {
        dx = x;

        number = ROUNDF(dx * D_8024E3C8.d);

        dx -= ((poly = number) * D_8024E3D0.d);
        dx -= (poly * D_8024E3D8.d);
        xsq = dx * dx;

        temp_fa1 = ((((D_8024E3A0[4] * xsq) + D_8024E3A0[3]) * xsq + D_8024E3A0[2]) * xsq + D_8024E3A0[1]);

        if (!(number & 1)) {
            return (f32)((dx * xsq) * temp_fa1 + dx);
        } else {
            return -(f32)((dx * xsq) * temp_fa1 + dx);
        }
    }
    if (x != x) {
        return 2.1401436e9f;
    }
    return 0.0f;
}

f32 uvCosF(f32 x) {
    s32 ix = *(s32*)&x;
    f32 var_fv0;
    f64 fabsA0; // temp_fa0;
    f64 temp_fa1;
    f64 temp_ft4;
    f64 temp_fv0;
    f64 temp_fv1;
    s32 number;
    f32 temp;
    f64 poly;
    f64 dx;
    f64 xsq;

    // mask off exponent + mantissa MSbit of f32
    if (((ix >> 22) & 0x1FF) < 0x136) {
        dx = (f32)FABS(x);

        poly = dx * D_8024E3C8.d + 0.5;
        number = ROUNDF(poly);

        dx -= ((poly = (number - 0.5)) * D_8024E3D0.d);
        dx -= (poly * D_8024E3D8.d);
        xsq = dx * dx;

        temp_fa1 = ((((D_8024E3A0[4] * xsq) + D_8024E3A0[3]) * xsq + D_8024E3A0[2]) * xsq + D_8024E3A0[1]);

        if (!(number & 1)) {
            return (f32)((dx * xsq) * temp_fa1 + dx);
        } else {
            return -(f32)((dx * xsq) * temp_fa1 + dx);
        }
    }
    // NaN check
    if (x != x) {
        return 2.1401436e9f;
    }
    return 0.0f;
}

f32 uvLength2D(f32 x, f32 y) {
    return uvSqrtF(SQ(x) + SQ(y));
}

f32 uvLength3D(f32 x, f32 y, f32 z) {
    return uvSqrtF(SQ(x) + SQ(y) + SQ(z));
}

f32 uvMath_8022A27C(f32 arg0, f32 arg1) {
    s32 flag;
    f32 ret;
    f32 fabsA0;
    f32 fabsA1;
    f32 temp_ft5;
    f32 absdiff;

    if ((arg1 == 0.0f) && (arg0 == 0.0f)) {
        return 0.0f;
    }
    fabsA1 = FABS(arg1);
    fabsA0 = FABS(arg0);
    flag = 0;
    if (fabsA1 < fabsA0) {
        temp_ft5 = fabsA1;
        fabsA1 = fabsA0;
        fabsA0 = temp_ft5;
        flag = 1;
    }
    temp_ft5 = (fabsA0 / fabsA1);
    absdiff = FABS(fabsA0 - fabsA1);
    ret = (PW_PI_4 * (fabsA0 / fabsA1)) + (0.309f * absdiff * temp_ft5);

    temp_ft5 = 0; // fake store to prevent emitting additional mov instr.
    if (arg1 >= 0.0f) {
        if (flag) {
            ret = PW_PI_2 - ret;
        }
    } else if (flag) {
        ret = PW_PI_2 + ret;
    } else {
        ret = PW_PI - ret;
    }

    if (arg0 >= 0.0f) {
        return ret;
    } else {
        return -ret;
    }
}
