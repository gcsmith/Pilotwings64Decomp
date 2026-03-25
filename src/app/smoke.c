#include "common.h"
#include "code_9A960.h"
#include "demo.h"
#include "smoke.h"
#include <uv_fx.h>
#include <uv_matrix.h>
#include <uv_model.h>
#include <libc/stdarg.h>

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    Vec3F unk10;
    s16 unk1C;
    s16 pad1E;
} Smoke_Unk0; // size = 0x20

typedef struct {
    Smoke_Unk0 unk0[10];
    f32 unk140;
    f32 unk144;
    f32 unk148;
    Vec3F unk14C;
    Vec3F unk158;
    s32 pad164;
    f32 unk168;
    Vec3F unk16C;
    u8 unk178[3];
    u8 unk17B;
    s16 created;
    s16 unk17E;
} Smoke; // size = 0x180

Smoke sSmokeObjects[12];

// forward declarations
void smokePuffAdd(Smoke*, Smoke_Unk0*);

void smokeInit(void) {
    Smoke* smoke;
    s32 i;
    s32 j;

    for (i = 0; i < ARRAY_COUNT(sSmokeObjects); i++) {
        smoke = &sSmokeObjects[i];
        smoke->created = FALSE;
        // clang-format off: needs to be on one line to match
        for (j = 0; j < ARRAY_COUNT(smoke->unk0); j++) { smoke->unk0[j].unk1C = 0xFF; }
        // clang-format on
    }
}

void func_80336600(void) {
    Smoke_Unk0* var_s0;
    Smoke* smoke;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv1;
    f32 temp_fs0;
    f32 temp_fs1;
    u8 var_s3;
    Mtx4F spC0;
    f32 x;
    f32 y;
    f32 z;
    s32 i;
    s32 j;

    uvMat4SetIdentity(&spC0);
    for (i = 0; i < ARRAY_COUNT(sSmokeObjects); i++) {
        smoke = &sSmokeObjects[i];
        if (smoke->created == FALSE) {
            continue;
        }
        var_s3 = 0;
        smoke->unk144 += D_8034F854;
        if ((smoke->unk168 <= smoke->unk144) && (smoke->unk144 < smoke->unk148)) {
            smokePuffAdd(smoke, &smoke->unk0[smoke->unk17B]);
            smoke->unk168 = smoke->unk144 + (smoke->unk140 / 10 /*0.0f*/);
            smoke->unk17B++;
            if (smoke->unk17B >= 10) {
                smoke->unk17B = 0;
            }
        }
        for (j = 0; j < ARRAY_COUNT(smoke->unk0); j++) {
            var_s0 = &smoke->unk0[j];
            if (var_s0->unk1C == 0xFF) {
                continue;
            }

            var_s0->unk0 += D_8034F854;
            if (smoke->unk140 < var_s0->unk0) {
                uvFxProps(var_s0->unk1C, FX_11(0), FX_END);
                var_s0->unk1C = 0xFF;
                continue;
            }
            temp_fv1 = var_s0->unk4 * (var_s0->unk0 / smoke->unk140) * 10.0f;
            temp_fa0 = var_s0->unk8 * (var_s0->unk0 / smoke->unk140) * 10.0f;
            temp_fs1 = var_s0->unkC * (var_s0->unk0 / smoke->unk140) * 10.0f;
            temp_fs0 = SQ(var_s0->unk0 / smoke->unk140);
            uvFxProps(var_s0->unk1C, FX_7(1.0 - temp_fs0), FX_3(temp_fv1, temp_fa0, temp_fs1), FX_END);

            x = temp_fs0;
            y = temp_fs0;
            z = temp_fs0;
            x *= smoke->unk158.x;
            y *= smoke->unk158.y;
            z *= smoke->unk158.z;
            if (smoke->unk17E != 0) {
                spC0.m[3][0] = smoke->unk14C.x + (smoke->unk16C.x * x);
                spC0.m[3][1] = smoke->unk14C.y + (smoke->unk16C.y * y);
                spC0.m[3][2] = (smoke->unk14C.z + (smoke->unk16C.z * z)) - (temp_fs1 * 0.5f);
            } else {
                spC0.m[3][0] = var_s0->unk10.x + (smoke->unk16C.x * x);
                spC0.m[3][1] = var_s0->unk10.y + (smoke->unk16C.y * y);
                spC0.m[3][2] = (var_s0->unk10.z + (smoke->unk16C.z * z)) - (temp_fs1 * 0.5f);
            }
            func_8021A4D8(var_s0->unk1C, &spC0);
            var_s3++;
        }
        if (var_s3 == 0) {
            smoke->created = FALSE;
        }
    }
}

s32 smokeCreate(void) {
    Smoke* smoke;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sSmokeObjects); i++) {
        if (sSmokeObjects[i].created == FALSE) {
            break;
        }
    }

    if (i == ARRAY_COUNT(sSmokeObjects)) {
        _uvDebugPrintf("smoke create : out of smoke effects\n");
        return -1;
    }

    smoke = &sSmokeObjects[i];
    smoke->unk178[0] = 0xFF;
    smoke->unk178[1] = 0xFF;
    smoke->unk178[2] = 0xFF;
    smoke->unk158.f[0] = 10.0f;
    smoke->unk158.f[1] = 10.0f;
    smoke->unk158.f[2] = 10.0f;
    smoke->unk140 = 10.0f;
    smoke->unk14C.f[0] = 0.0f;
    smoke->unk14C.f[1] = 0.0f;
    smoke->unk14C.f[2] = 0.0f;
    smoke->unk148 = 10000.0f;
    smoke->unk144 = 0.0f;
    smoke->unk168 = 0.0f;
    smoke->unk16C.f[0] = 0 /*.0f*/;
    smoke->unk16C.f[1] = 0 /*.0f*/;
    smoke->unk16C.f[2] = 1.0f;
    smoke->unk17B = 0;
    smoke->created = TRUE;
    smoke->unk17E = 0;
    return i;
}

void smokeProps(s32 smokeIdx, ...) {
    va_list args;
    Smoke* smoke;
    f32 temp_fv0;
    s32 propertyType;

    if (smokeIdx < 0 || smokeIdx > ARRAY_COUNT(sSmokeObjects)) {
        _uvDebugPrintf("smoke_pos : smoke id [%d]out of range\n", smokeIdx);
        return;
    }
    if (smokeIdx == 0xFF) {
        return;
    }
    smoke = &sSmokeObjects[smokeIdx];
    if (smoke->created == FALSE) {
        return;
    }

    va_start(args, smokeIdx);
    while (TRUE) {
        propertyType = (s16)va_arg(args, s32);
        switch (propertyType) {
        case 1:
            smoke->unk178[0] = (u16)va_arg(args, s32);
            smoke->unk178[1] = (u16)va_arg(args, s32);
            smoke->unk178[2] = (u16)va_arg(args, s32);
            break;
        case 9:
            smoke->unk158.f[0] = va_arg(args, f64);
            smoke->unk158.f[1] = va_arg(args, f64);
            smoke->unk158.f[2] = va_arg(args, f64);
            break;
        case 2:
            temp_fv0 = va_arg(args, f64);
            smoke->unk158.f[0] = temp_fv0;
            smoke->unk158.f[1] = temp_fv0;
            smoke->unk158.f[2] = temp_fv0;
            break;
        case 3:
            smoke->unk140 = va_arg(args, f64);
            break;
        case 4:
            smoke->unk148 = va_arg(args, f64);
            break;
        case 5:
            smoke->unk16C.f[0] = va_arg(args, f64);
            smoke->unk16C.f[1] = va_arg(args, f64);
            smoke->unk16C.f[2] = va_arg(args, f64);
            break;
        case 6:
            smoke->unk14C.f[0] = va_arg(args, f64);
            smoke->unk14C.f[1] = va_arg(args, f64);
            smoke->unk14C.f[2] = va_arg(args, f64);
            break;
        case 7:
            smoke->unk17E = va_arg(args, s32);
            break;
        case 8:
            if ((u16)va_arg(args, s32) == 0) {
                smokeDelete(smokeIdx);
                return;
            }
            break;
        default:
            _uvDebugPrintf("smoke_props: Unknown property type %d\n", propertyType);
            return;
        case 0:
            return;
        }
    }
}

void smokeGetProps(s32 smokeIdx, ...) {
    va_list args;
    Smoke* smoke;
    s32 propertyType;

    if (smokeIdx < 0 || smokeIdx > ARRAY_COUNT(sSmokeObjects)) {
        _uvDebugPrintf("smoke_pos : smoke id [%d]out of range\n", smokeIdx);
        return;
    }

    if (smokeIdx == 0xFF) {
        return;
    }

    smoke = &sSmokeObjects[smokeIdx];
    va_start(args, smokeIdx);
    while (TRUE) {
        propertyType = (s16)va_arg(args, s32);
        switch (propertyType) {
        case 1:
            *va_arg(args, u8*) = smoke->unk178[0];
            *va_arg(args, u8*) = smoke->unk178[1];
            *va_arg(args, u8*) = smoke->unk178[2];
            break;
        case 2:
            *va_arg(args, f32*) = smoke->unk158.f[0];
            break;
        case 9:
            *va_arg(args, f32*) = smoke->unk158.f[0];
            *va_arg(args, f32*) = smoke->unk158.f[1];
            *va_arg(args, f32*) = smoke->unk158.f[2];
            break;
        case 3:
            *va_arg(args, f32*) = smoke->unk140;
            break;
        case 4:
            *va_arg(args, f32*) = smoke->unk148;
            break;
        case 5:
            *va_arg(args, f32*) = smoke->unk16C.f[0];
            *va_arg(args, f32*) = smoke->unk16C.f[1];
            *va_arg(args, f32*) = smoke->unk16C.f[2];
            break;
        case 6:
            *va_arg(args, f32*) = smoke->unk14C.f[0];
            *va_arg(args, f32*) = smoke->unk14C.f[1];
            *va_arg(args, f32*) = smoke->unk14C.f[2];
            break;
        case 7:
            *va_arg(args, s16*) = smoke->unk17E;
            break;
        case 8:
            *va_arg(args, s16*) = smoke->created;
            break;
        default:
            _uvDebugPrintf("smoke_getprops: Unknown property type %d\n", propertyType);
            return;
        case 0:
            return;
        }
    }
}

void smokeDeleteAll(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sSmokeObjects); i++) {
        smokeDelete(i);
    }
}

void smokeDelete(s32 smokeIdx) {
    Smoke* smoke;
    Smoke_Unk0* var_s0;
    s32 i;

    if (smokeIdx < 0 || smokeIdx > ARRAY_COUNT(sSmokeObjects)) {
        _uvDebugPrintf("smoke_delete : smoke id [%d]out of range\n", smokeIdx);
        return;
    }

    smoke = &sSmokeObjects[smokeIdx];
    if (smoke->created == FALSE) {
        return;
    }

    smoke->created = FALSE;
    for (i = 0; i < ARRAY_COUNT(smoke->unk0); i++) {
        var_s0 = &smoke->unk0[i];
        if (var_s0->unk1C != 0xFF) {
            uvFxProps(var_s0->unk1C, FX_11(0), FX_END);
            var_s0->unk1C = 0xFF;
        }
    }
}

void smokePuffAdd(Smoke* smoke, Smoke_Unk0* arg1) {
    f32 var_fa0;
    f32 var_fv1;

    if (arg1->unk1C != 0xFF) {
        uvFxProps(arg1->unk1C, FX_11(0), FX_END);
        arg1->unk1C = 0xFF;
    }
    arg1->unk1C = func_8021EFF0(7);
    if (arg1->unk1C == 0xFF) {
        _uvDebugPrintf("puff_add : out of uv effects\n");
        return;
    }
    uvModelGet(arg1->unk1C, 7);
    arg1->unk4 = (smoke->unk158.f[0] / 10.0f) * ((demoRandF() * 0.4) + 0.8);
    arg1->unk8 = (smoke->unk158.f[1] / 10.0f) * ((demoRandF() * 0.4) + 0.8);
    arg1->unkC = (smoke->unk158.f[2] / 10.0f) * ((demoRandF() * 0.4) + 0.8);
    arg1->unk0 = 0.0f;
    arg1->unk10.f[0] = smoke->unk14C.f[0];
    arg1->unk10.f[1] = smoke->unk14C.f[1];
    arg1->unk10.f[2] = smoke->unk14C.f[2];
    var_fa0 = smoke->unk158.f[1] < smoke->unk158.f[0] ? smoke->unk158.f[0] : smoke->unk158.f[1];
    var_fv1 = smoke->unk158.f[2] < var_fa0 ? var_fa0 : smoke->unk158.f[2];

    var_fa0 = var_fv1 * 50.0f;
    var_fv1 = ((s32)(demoRandF() * 3.0 + 0.5) * 90);
    uvFxProps(arg1->unk1C, FX_1(10000.0f), FX_19(var_fa0), FX_8(0x138), FX_15(var_fv1),
              FX_5(smoke->unk178[0] / 255.0, smoke->unk178[1] / 255.0, smoke->unk178[2] / 255.0, 1.0f), FX_END);
}

void smokeCreateTerra(void) {
    s32 smokeIdx;
    switch (D_80362690->terraId) {
    case 0:
        smokeIdx = smokeCreate();
        smokeProps(smokeIdx, SMOKE_FX_5(0.0f, 1.0f, 1.0f), SMOKE_FX_6(-260.0, -120.0, 19.0), SMOKE_FX_END);
        smokeIdx = smokeCreate();
        smokeProps(smokeIdx, SMOKE_FX_5(0.0f, 1.0f, 1.0f), SMOKE_FX_6(120.0, 280.05, 47.0), SMOKE_FX_END);
        smokeIdx = smokeCreate();
        smokeProps(smokeIdx, SMOKE_FX_5(0.0f, 2.0f, 1.0f), SMOKE_FX_6(-319.4, 385.4, 17.0), SMOKE_FX_END);
        return;
    case 1:
        smokeIdx = smokeCreate();
        smokeProps(smokeIdx, SMOKE_FX_5(-1.0f, 0.0f, 1.0f), SMOKE_FX_2(35.0f), SMOKE_FX_6(-1329.05, 1232.9, 7.0), SMOKE_FX_END);
        smokeIdx = smokeCreate();
        smokeProps(smokeIdx, SMOKE_FX_5(-1.0f, 0.0f, 1.0f), SMOKE_FX_2(25.0f), SMOKE_FX_6(-1728.65, -254.84, 31.31), SMOKE_FX_END);
        smokeIdx = smokeCreate();
        smokeProps(smokeIdx, SMOKE_FX_5(-1.0f, 0.0f, 1.0f), SMOKE_FX_2(25.0f), SMOKE_FX_6(-1470.8, -391.2, 58.25), SMOKE_FX_END);
        smokeIdx = smokeCreate();
        smokeProps(smokeIdx, SMOKE_FX_5(0.0f, -1.0f, 1.0f), SMOKE_FX_2(25.0f), SMOKE_FX_6(171.0, 1335.5, 14.4), SMOKE_FX_END);
        smokeIdx = smokeCreate();
        smokeProps(smokeIdx, SMOKE_FX_5(0.0f, -1.0f, 1.0f), SMOKE_FX_2(25.0f), SMOKE_FX_6(78.80000000000001, 1360.5, 14.4), SMOKE_FX_END);
        return;
    case 3:
        smokeIdx = smokeCreate();
        smokeProps(smokeIdx, SMOKE_FX_5(0.0f, 0.0f, 1.0f), SMOKE_FX_2(100.0), SMOKE_FX_6(2400.0, -563.0, 86.0), SMOKE_FX_END);
        smokeIdx = smokeCreate();
        smokeProps(smokeIdx, SMOKE_FX_5(-1.0f, 0.0f, 1.0f), SMOKE_FX_2(20.0), SMOKE_FX_6(-592.0, 1060.7, 94.5), SMOKE_FX_END);
        smokeIdx = smokeCreate();
        smokeProps(smokeIdx, SMOKE_FX_5(-1.0f, 0.0f, 1.0f), SMOKE_FX_2(20.0), SMOKE_FX_6(750.39, 235.6, 106.4), SMOKE_FX_END);
        smokeIdx = smokeCreate();
        smokeProps(smokeIdx, SMOKE_FX_5(-1.0f, 0.0f, 1.0f), SMOKE_FX_2(20.0), SMOKE_FX_6(151.2, -1026.22, 93.14), SMOKE_FX_END);
        return;
    case 7:
        smokeIdx = smokeCreate();
        smokeProps(smokeIdx, SMOKE_FX_5(-1.0f, 0.0f, 1.0f), SMOKE_FX_1(0, 0, 0), SMOKE_FX_6(-913.62, 200.17, 8.5), SMOKE_FX_END);
        smokeIdx = smokeCreate();
        smokeProps(smokeIdx, SMOKE_FX_5(-1.0f, 0.0f, 1.0f), SMOKE_FX_1(0, 0, 0), SMOKE_FX_6(-431.6, 1522.2, 21.2), SMOKE_FX_END);
        smokeIdx = smokeCreate();
        smokeProps(smokeIdx, SMOKE_FX_5(-1.0f, 0.0f, 1.0f), SMOKE_FX_2(20.0), SMOKE_FX_1(0, 0, 0), SMOKE_FX_6(-319.0, -1686.9, 29.0), SMOKE_FX_END);
        smokeIdx = smokeCreate();
        smokeProps(smokeIdx, SMOKE_FX_5(-1.0f, 0.0f, 1.0f), SMOKE_FX_2(20.0), SMOKE_FX_1(0, 0, 0), SMOKE_FX_6(-166.39999999999998, -1600.0, 24.9),
                   SMOKE_FX_END);
        smokeIdx = smokeCreate();
        smokeProps(smokeIdx, SMOKE_FX_5(-1.0f, 0.0f, 1.0f), SMOKE_FX_2(20.0), SMOKE_FX_1(0, 0, 0), SMOKE_FX_6(-393.6, -930.8, 94.7), SMOKE_FX_END);
        return;
    default:
        _uvDebugPrintf("smoke_create : unknown terra id %d\n", D_80362690->terraId);
        return;
    case 2:
        return;
    }
}
