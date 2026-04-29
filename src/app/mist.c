#include "common.h"
#include <uv_fx.h>
#include <uv_graphics.h>
#include <uv_math.h>
#include <uv_matrix.h>
#include <uv_model.h>
#include <uv_vector.h>
#include "mist.h"
#include "code_9A960.h"
#include "demo.h"
#include "game.h"

typedef struct {
    u8 fxId;
    u8 pad1[3];
    Mtx4F unk4;
    s32 unk44;
    f32 unk48;
    f32 unk4C;
    f32 unk50;
} Unk8036BE30;

STATIC_DATA Unk8036BE30 D_8036BE30[5];
STATIC_DATA Vec3F D_8036BFD8;
STATIC_DATA f32 D_8036BFE4;

void mistInit(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_8036BE30); i++) {
        D_8036BE30[i].fxId = 0xFF;
        D_8036BE30[i].unk44 = 0;
        D_8036BE30[i].unk48 = -3.0f;
    }

    D_8036BFD8.x = 0.0f;
    D_8036BFD8.y = 0.0f;
    D_8036BFD8.z = 0.0f;
    D_8036BFE4 = 0.0f;
}

void mist_803144D0(Mtx4F* arg0, Vec3F* arg1) {
    Unk8036BE30* var_s0;
    s32 i;
    s32 var_a2;
    f32 x;
    f32 y;
    f32 z;
    f32 pad;

    for (i = 0; i < ARRAY_COUNT(D_8036BE30); i++) {
        if (D_8036BFE4) { } //! @fakematch
        if (D_8036BE30[i].unk44 == 0) {
            break;
        }
    }

    if (i == ARRAY_COUNT(D_8036BE30)) {
        return;
    }
    var_s0 = &D_8036BE30[i];
    var_s0->fxId = func_8021EFF0(7);
    if (var_s0->fxId == 0xFF) {
        _uvDebugPrintf("mist : out of effects\n");
        return;
    }

    uvModelGet(var_s0->fxId, 7);
    var_s0->unk4C = (demoRandF() * 4.0f) + 5.0f;
    pad = var_s0->unk4C;
    // clang-format off
    uvFxProps(var_s0->fxId,
        FX_PROP_3(pad, pad, pad),
        FX_PROP_4(1.0f, 1.0f, 1.0f),
        FX_PROP_18(0x200000),
        FX_PROP_1(1e+20),
        FX_PROP_END
    );
    // clang-format on
    var_a2 = ((demoRandF() < 0.5f) ? 0x138 : 0x139);
    uvFxProps(var_s0->fxId, FX_PROP_8(var_a2), FX_PROP_END);
    var_s0->unk50 = (demoRandF() * 0.3f) + 0.3f;
    if (arg1 != NULL) {
        x = ((arg0->m[3][0] - arg1->x) + 5.0f) - (demoRandF() * 10.0f);
        y = ((arg0->m[3][1] - arg1->y) + 5.0f) - (demoRandF() * 10.0f);
        z = ((arg0->m[3][2] - arg1->z) + 2.6666667f) - (demoRandF() * 8.0f);
    } else {
        x = arg0->m[3][0] + (arg0->m[1][0] * ((2.0f * uvRandF_LCG()) - 1.0f));
        y = arg0->m[3][1] + (arg0->m[1][1] * ((2.0f * uvRandF_LCG()) - 1.0f));
        z = arg0->m[3][2] + (arg0->m[1][2] * ((2.0f * uvRandF_LCG()) - 1.0f));
    }
    uvMat4SetIdentity(&var_s0->unk4);
    var_s0->unk4.m[3][0] = x;
    var_s0->unk4.m[3][1] = y;
    var_s0->unk4.m[3][2] = z;
    func_8021A4D8(var_s0->fxId, &var_s0->unk4);
    var_s0->unk44 = 1;
    var_s0->unk48 = D_8036BFE4;
}

void mistUpdate(Mtx4F* arg0, f32 arg1) {
    Unk8036BE30* var_s0;
    s32 i;
    Vec3F sp84;
    f32 temp_fa0;
    f32 temp_fv1;
    f32 var_fv0;
    f32 var_fv1;
    f32 x, y, z;

    D_8036BFE4 += D_8034F854;
    if ((D_80362690->state == 5) && (arg0->m[3][2] > 25.0f) && (arg1 > 16.7f)) {
        sp84.x = D_8036BFD8.x - arg0->m[3][0];
        sp84.y = D_8036BFD8.y - arg0->m[3][1];
        sp84.z = D_8036BFD8.z - arg0->m[3][2];
        if (uvVec3Len(&sp84) > 12.5f) {
            sp84.x *= 3.0f;
            sp84.y *= 3.0f;
            sp84.z *= 3.0f;
            mist_803144D0(arg0, &sp84);
            D_8036BFD8.x = arg0->m[3][0];
            D_8036BFD8.y = arg0->m[3][1];
            D_8036BFD8.z = arg0->m[3][2];
        }
    }

    for (i = 0; i < ARRAY_COUNT(D_8036BE30); i++) {
        var_s0 = &D_8036BE30[i];
        if (var_s0->unk44 != 0) {
            x = var_s0->unk4.m[3][0];
            y = var_s0->unk4.m[3][1];
            z = var_s0->unk4.m[3][2];
            if ((func_80204EC0(0, x, y, z, var_s0->unk4C) == 0) || ((D_8036BFE4 - var_s0->unk48) > 3.0f)) {
                uvFxProps(var_s0->fxId, FX_PROP_11(0), FX_PROP_END);
                var_s0->unk44 = 0;
                var_s0->unk48 = -3.0f;
            } else {
                sp84.x = arg0->m[3][0] - var_s0->unk4.m[3][0];
                sp84.y = arg0->m[3][1] - var_s0->unk4.m[3][1];
                sp84.z = arg0->m[3][2] - var_s0->unk4.m[3][2];
                temp_fv1 = uvVec3Len(&sp84) / 25.0f;
                temp_fa0 = 1.0f - temp_fv1;
                if (temp_fv1 > 1.0f) {
                    temp_fa0 = 0.0f;
                } else if (temp_fa0 > 1.0f) {
                    temp_fa0 = 1.0f;
                }
                var_fv0 = 1.0f - ((D_8036BFE4 - var_s0->unk48) / 3.0f);
                if (var_fv0 < 0.0f) {
                    var_fv0 = 0.0f;
                } else if (var_fv0 > 1.0f) {
                    var_fv0 = 1.0f;
                }
                if (temp_fa0 < var_fv0) {
                    var_fv1 = var_s0->unk50 * temp_fa0;
                } else {
                    var_fv1 = var_s0->unk50 * var_fv0;
                }
                uvFxProps(var_s0->fxId, FX_PROP_7(var_fv1), FX_PROP_END);
            }
        }
    }
}

void mistDeinit(void) {
    s32 i;
    for (i = 0; i < ARRAY_COUNT(D_8036BE30); i++) {
        if (D_8036BE30[i].unk44 != 0) {
            uvFxProps(D_8036BE30[i].fxId, FX_PROP_11(0), FX_PROP_END);
            D_8036BE30[i].unk44 = 0;
        }
    }
    D_8036BFE4 = 0.0f;
}
