#include "common.h"
#include <uv_clocks.h>
#include <uv_fx.h>
#include <uv_geometry.h>
#include <uv_math.h>
#include <uv_model.h>
#include "demo.h"
#include "uv_vector.h"
#include "splash.h"

typedef struct {
    Mtx4F unk0;
    f32 size;
    s32 fxIds[10];
    u8 pad6C[4];
    f64 unk70;
    f64 unk78;
    s32 active;
    u8 pad84[4];
} SplashEffect; // size = 0x88

typedef struct {
    Mtx4F unk0;
    f32 curSize;
    f32 fade;
    f32 initSize;
    s32 active;
} SplashRipple; // size = 0x50

typedef struct {
    Vec3F unk0;
    f32 unkC;
} SplashRippleParams; // size = 0x10

static SplashRipple sSplashRipples[48];
static SplashRippleParams sSplashRippleParams[10];
static SplashEffect sSplashEffects[5];

STATIC_FUNC void splashDrawRipple(SplashRipple* ripple) {
    s32 nSize;
    s32 pSize;
    s32 alpha;

    alpha = (s32)(ripple->fade * 255.0f);
    pSize = (s32)(ripple->initSize * ripple->curSize * 100.0f);
    uvGfx_802236CC(&ripple->unk0);
    uvVtxBeginPoly();
    nSize = -pSize;
    uvVtx(nSize, nSize, 0, -1024, -1024, 255, 255, 255, alpha);
    uvVtx(pSize, nSize, 0, 1024, -1024, 255, 255, 255, alpha);
    uvVtx(pSize, pSize, 0, 1024, 1024, 255, 255, 255, alpha);
    uvVtx(nSize, pSize, 0, -1024, 1024, 255, 255, 255, alpha);
    uvVtxEndPoly();
    uvGfxMtxViewPop();
}

void splashDraw(void) {
    SplashRipple* ripple;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sSplashRipples); i++) {
        if (sSplashRipples[i].active) {
            break;
        }
    }
    if (i == ARRAY_COUNT(sSplashRipples)) {
        return;
    }

    uvGfxStatePush();
    uvGfx_80223A28(0x13C);
    uvGfxSetFlags(GFX_STATE_4000000 | GFX_STATE_800000 | GFX_STATE_400000 | GFX_STATE_200000);
    for (i = 0; i < ARRAY_COUNT(sSplashRipples); i++) {
        ripple = &sSplashRipples[i];
        if (ripple->active) {
            ripple->fade -= 0.02f;
            ripple->curSize += 0.01f;
            if ((ripple->fade < 0.0) || (ripple->curSize > 1.0)) {
                ripple->active = FALSE;
            } else {
                splashDrawRipple(ripple);
            }
        }
    }
    uvGfxStatePop();
}

void splashAddRipple(Mtx4F* mtx, f32 initSize) {
    SplashRipple* ripple;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sSplashRipples); i++) {
        if (!sSplashRipples[i].active) {
            break;
        }
    }
    if (i == ARRAY_COUNT(sSplashRipples)) {
        _uvDebugPrintf("out of ripples\n");
        return;
    }

    ripple = &sSplashRipples[i];
    uvMat4Copy(&ripple->unk0, mtx);
    uvMat4Scale(&ripple->unk0, 0.01f, 0.01f, 0.01f);
    ripple->initSize = initSize;
    ripple->curSize = 0.0f;
    ripple->fade = 1.0f;
    ripple->active = TRUE;
}

void splashAdd(Mtx4F* pos, f32 size) {
    s32 i;
    SplashEffect* effect;

    for (i = 0; i < ARRAY_COUNT(sSplashEffects); i++) {
        if (!sSplashEffects[i].active) {
            break;
        }
    }

    if (i == ARRAY_COUNT(sSplashEffects)) {
        _uvDebugPrintf("splash_add : out of splash effects\n");
        return;
    }
    //! @fakematch
    if (0) { }

    effect = &sSplashEffects[i];
    uvMat4Copy(&effect->unk0, pos);
    effect->size = size;
    for (i = 0; i < ARRAY_COUNT(effect->fxIds); i++) {
        effect->fxIds[i] = func_8021EFF0(7);
        if (effect->fxIds[i] != 0xFF) {
            uvModelGet(effect->fxIds[i], 7);
            // clang-format off
            uvFxProps(effect->fxIds[i],
                FX_PROP_1(sSplashRippleParams[i].unkC),
                FX_PROP_3(size * 0.6f, size * 0.6f, size),
                FX_PROP_END
            );
            // clang-format on
            if (i % 2) {
                uvFxProps(effect->fxIds[i], FX_PROP_8(0x13B), FX_PROP_END);
            } else {
                uvFxProps(effect->fxIds[i], FX_PROP_8(0x13A), FX_PROP_END);
            }
        }
    }
    effect->unk78 = effect->unk70 = uvClkGetSec(4);
    effect->active = TRUE;
}

void splashUpdate(void) {
    f64 temp_fs3;
    Mtx4F fxMtx;
    SplashEffect* effect;
    f32 temp_fs0;
    f32 angle;
    f32 var_fs2;
    f64 var_fa0;
    f64 tmp;
    f32 tmpRand;
    s32 i;
    s32 j;

    temp_fs3 = uvClkGetSec(4);
    for (i = 0; i < ARRAY_COUNT(sSplashEffects); i++) {
        effect = &sSplashEffects[i];
        if (!effect->active) {
            continue;
        }

        for (j = 0; j < ARRAY_COUNT(sSplashRippleParams); j++) {
            var_fa0 = (temp_fs3 - effect->unk70);
            if (sSplashRippleParams[j].unkC < var_fa0) {
                continue;
            }
            if (effect->fxIds[j] == 0xFF) {
                continue;
            }

            temp_fs0 = (f32)(var_fa0 / sSplashRippleParams[j].unkC);
            var_fs2 = (temp_fs0 <= 0.0) ? 0.0f : uvSqrtF(temp_fs0);
            uvFxProps(effect->fxIds[j], 7, 1.0 - SQ(temp_fs0), 0);
            uvMat4SetIdentity(&fxMtx);
            angle = ((f32)j / 10.0f) * 3.1415927f * 2 /*.0f*/;
            fxMtx.m[3][0] = (uvSinF(angle) * sSplashRippleParams[j].unk0.x * temp_fs0 * effect->size) + effect->unk0.m[3][0];
            fxMtx.m[3][1] = (uvCosF(angle) * sSplashRippleParams[j].unk0.y * temp_fs0 * effect->size) + effect->unk0.m[3][1];
            fxMtx.m[3][2] = (uvSinF(var_fs2 * 3.1415927f) * sSplashRippleParams[j].unk0.z * effect->size) + effect->unk0.m[3][2];
            func_8021A4D8(effect->fxIds[j], &fxMtx);
        }

        if (temp_fs3 - effect->unk70 < 3.5) {
            tmp = temp_fs3 - effect->unk78;
            if (tmp > 0.4) {
                uvMat4SetIdentity(&fxMtx);
                tmpRand = demoRandF() - 0.5f;
                fxMtx.m[3][0] = effect->unk0.m[3][0] + (tmpRand * effect->size);
                tmpRand = demoRandF() - 0.5f;
                fxMtx.m[3][1] = effect->unk0.m[3][1] + (tmpRand * effect->size);
                fxMtx.m[3][2] = effect->unk0.m[3][2] + 1.0f;
                tmpRand = ((demoRandF() * 0.7f) + 0.3f) * effect->size;
                splashAddRipple(&fxMtx, tmpRand);
                effect->unk78 = temp_fs3;
            }
        } else {
            effect->active = FALSE;
        }
    }
}

void splashInit(void) {
    SplashRipple* ripple;
    SplashEffect* effect;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sSplashEffects); i++) {
        effect = &sSplashEffects[i];
        effect->active = FALSE;
    }

    for (i = 0; i < ARRAY_COUNT(sSplashRipples); i++) {
        sSplashRipples[i].active = FALSE;
    }

    sSplashRippleParams[0].unk0.x = 0.6f;
    sSplashRippleParams[0].unk0.y = 0.6f;
    sSplashRippleParams[0].unk0.z = 0.6f;
    sSplashRippleParams[0].unkC = 1.3f;
    sSplashRippleParams[1].unk0.x = 0.4f;
    sSplashRippleParams[1].unk0.y = 0.4f;
    sSplashRippleParams[1].unk0.z = 0.4f;
    sSplashRippleParams[1].unkC = 1.1f;
    sSplashRippleParams[2].unk0.x = 0.4f;
    sSplashRippleParams[2].unk0.y = 0.4f;
    sSplashRippleParams[2].unk0.z = 0.8f;
    sSplashRippleParams[2].unkC = 1.9f;
    sSplashRippleParams[3].unk0.x = 0.55f;
    sSplashRippleParams[3].unk0.y = 0.55f;
    sSplashRippleParams[3].unk0.z = 0.5f;
    sSplashRippleParams[3].unkC = 1.4f;
    sSplashRippleParams[4].unk0.x = 0.1f;
    sSplashRippleParams[4].unk0.y = 0.1f;
    sSplashRippleParams[4].unk0.z = 0.1f;
    sSplashRippleParams[4].unkC = 1.0f;
    sSplashRippleParams[5].unk0.x = 0.5f;
    sSplashRippleParams[5].unk0.y = 0.5f;
    sSplashRippleParams[5].unk0.z = 1.0f;
    sSplashRippleParams[5].unkC = 2.0f;
    sSplashRippleParams[6].unk0.x = 0.4f;
    sSplashRippleParams[6].unk0.y = 0.4f;
    sSplashRippleParams[6].unk0.z = 0.4f;
    sSplashRippleParams[6].unkC = 1.2f;
    sSplashRippleParams[7].unk0.x = 0.5f;
    sSplashRippleParams[7].unk0.y = 0.5f;
    sSplashRippleParams[7].unk0.z = 0.6f;
    sSplashRippleParams[7].unkC = 1.8f;
    sSplashRippleParams[8].unk0.x = 0.5f;
    sSplashRippleParams[8].unk0.y = 0.5f;
    sSplashRippleParams[8].unk0.z = 0.5f;
    sSplashRippleParams[8].unkC = 1.1f;
    sSplashRippleParams[9].unk0.x = 0.2f;
    sSplashRippleParams[9].unk0.y = 0.2f;
    sSplashRippleParams[9].unk0.z = 0.2f;
    sSplashRippleParams[9].unkC = 1.6f;
}

void splashClear(void) {
    SplashEffect* effect;
    s32 i;
    s32 j;

    for (i = 0; i < ARRAY_COUNT(sSplashEffects); i++) {
        effect = &sSplashEffects[i];
        if (effect->active) {
            effect->active = FALSE;
            for (j = 0; j < ARRAY_COUNT(effect->fxIds); j++) {
                if (effect->fxIds[j] != 0xFF) {
                    uvFxProps(effect->fxIds[j], FX_PROP_11(0), FX_PROP_END);
                }
            }
        }
    }

    // clang-format off: needs to be on one line to match
    for (i = 0; i < ARRAY_COUNT(sSplashRipples); i++) { sSplashRipples[i].active = FALSE; }
    // clang-format on
}
