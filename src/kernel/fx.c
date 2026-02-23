#include "common.h"
#include <uv_font.h>
#include <uv_fx.h>
#include <uv_geometry.h>
#include <uv_graphics.h>
#include <uv_math.h>
#include <uv_vector.h>
#include <libc/stdarg.h>
#include "kernel/code_58E0.h"

UnkModelDebrisStructure D_8028A0A0[4];
UnkModelTrail D_8028AC40[4];
UnkFxStruct D_8028B400[120];

// clang-format off
typedef struct Unk80248EA0 {
    s16 unk0;
    s16 unk2;
} Unk80248EA0;

static Unk80248EA0 D_80248EA0[] = {
    { 0, 0 }, { 100, 0 }, { 71, -71 }, { 0, -100 },
    { -71, -71 }, { -100, 0 }, { -71, 71 }, { 0, 100 },
    { 71, 71 }, { 100, 0 }, { -100, 0 }, { 100, 0 },
    { 100, 200 }, { -100, 200 }
};

static Unk80248EA0 D_80248ED8[] = {
    { 0, 0 }, { 100, 0 }, { 92, -38 }, { 71, -71}, { 38, -92 },
    { 0, -100 }, { -38, -92 }, { -71, -71}, { -92, -38 },
    { -100, 0 }, { -92, 38 }, { -71, 71}, { -38, 92 },
    { 0, 100 }, { 38, 92 }, { 71, 71}, { 92, 38 },
};

static Unk80248EA0 D_80248F1C[] = {
    { 0, 0 }, { 100, 0 }, { 0, 100 },
    { -100, 0 }, { 0, -100 }, { 100, 0 },
};

typedef struct Unk80248F34 {
    s16 unk0;
    s16 unk2;
    f32 unk4;
} Unk80248F34; // size = 0x8

static Unk80248F34 D_80248F34[] = {
    { -33,   0, 0.0f }, { -33,  14, 0.0f },
    { -33,  29, 0.0f }, { -33,  43, 0.0f },
    { -33,  57, 0.0f }, { -33,  71, 0.0f },
    { -33,  86, 0.0f }, { -33, 100, 0.0f },
    { -25,   0, 0.0f }, { -25,  14, 0.0f },
    { -25,  29, 0.3f }, { -25,  43, 0.0f },
    { -25,  57, 0.3f }, { -25,  71, 0.4f },
    { -25,  86, 0.0f }, { -25, 100, 0.0f },
    { -17,   0, 0.0f }, { -17,  14, 0.3f },
    { -17,  29, 0.4f }, { -17,  43, 0.6f },
    { -17,  57, 0.8f }, { -17,  71, 0.6f },
    { -17,  86, 0.5f }, { -17, 100, 0.0f },
    {  -8,   0, 0.9f }, {  -8,  14, 0.9f },
    {  -8,  29, 0.7f }, {  -8,  43, 0.8f },
    {  -8,  57, 0.7f }, {  -8,  71, 0.7f },
    {  -8,  86, 0.6f }, {  -8, 100, 0.0f },
    {   0,   0, 0.9f }, {   0,  14, 0.8f },
    {   0,  29, 0.8f }, {   0,  43, 0.9f },
    {   0,  57, 0.8f }, {   0,  71, 0.8f },
    {   0,  86, 0.2f }, {   0, 100, 0.0f },
    {   8,   0, 0.0f }, {   8,  14, 0.2f },
    {   8,  29, 0.9f }, {   8,  43, 0.7f },
    {   8,  57, 0.5f }, {   8,  71, 0.6f },
    {   8,  86, 0.0f }, {   8, 100, 0.0f },
    {  17,   0, 0.0f }, {  17,  14, 0.0f },
    {  17,  29, 0.4f }, {  17,  43, 0.2f },
    {  17,  57, 0.1f }, {  17,  71, 0.5f },
    {  17,  86, 0.1f }, {  17, 100, 0.0f },
    {  25,   0, 0.0f }, {  25,  14, 0.0f },
    {  25,  29, 0.0f }, {  25,  43, 0.0f },
    {  25,  57, 0.0f }, {  25,  71, 0.0f },
    {  25,  86, 0.0f }, {  25, 100, 0.0f },
};
// clang-format on

#define FLT_MAX 340282346638528859811704183484516925440.0f

void func_80219FD0(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_8028B400); i++) {
        D_8028B400[i].unk4 = 0;
    }

    for (i = 0; i < ARRAY_COUNT(D_8028AC40); i++) {
        func_8021A038(&D_8028AC40[i]);
    }
}

void func_8021A038(UnkModelTrail* arg0) {
    s32 i;

    arg0->unk1E8 = 0;
    arg0->unk1E6 = 0;
    arg0->unk1EC = 0;
    arg0->unk1B4.x = arg0->unk1B4.y = arg0->unk1B4.z = 0.0f;
    arg0->unk1D0 = 17.0f / 6.0f;
    arg0->unk1E4 = 10;

    for (i = 0; i < ARRAY_COUNT(arg0->unkF0); i++) {
        arg0->unkF0[i].x = 0.0f;
        arg0->unkF0[i].y = 0.0f;
        arg0->unkF0[i].z = 0.0f;
    }
}

void func_8021A0CC(UnkModelDebrisStructure* arg0) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(arg0->unk0); i++) {
        arg0->unk1E0[i] = ((2.0f * uvRandF_LCG()) - 1.0f) * 6.2831855f;
        arg0->unk280[i] = (uvRandF_LCG() * 3.2f) + 0.4f;
        arg0->unk230[i] = (uvRandF_LCG() * 5.8f) + 0.1f;
        arg0->unk0[i].x = (uvRandF_LCG() * 3.0f) - 1.5f;
        arg0->unk0[i].y = (uvRandF_LCG() * 3.0f) - 1.5f;
        arg0->unk0[i].z = uvRandF_LCG() - 0.5f;
        arg0->unkF0[i].x = (uvRandF_LCG() * 3.4f) - 1.7f;
        arg0->unkF0[i].y = (uvRandF_LCG() * 3.4f) - 1.7f;
        arg0->unkF0[i].z = (uvRandF_LCG() * 5.2f) + 0.4f;
        arg0->unkF0[i].x *= 20.0f;
        arg0->unkF0[i].y *= 20.0f;
        arg0->unkF0[i].z *= 20.0f;
        arg0->unk230[i] *= 20.0f;
        arg0->unk2D0[i] = 1;
    }
}

void func_8021A298(void) {
    s32 i;

    // clang-format off
    for (i = 0; i < ARRAY_COUNT(D_8028B400); i++) { D_8028B400[i].unk5 = 0; }
    // clang-format on
}

s32 func_8021A2C8(s32 fxId) {
    if (D_8028B400[fxId].unk4 != 0) {
        return 0;
    }
    return 1;
}

void func_8021A304(f32 arg0, f32 arg1, f32 arg2, u16 arg3) {
    func_8021A334(arg0, arg1, arg2, 0.0f, arg3);
}

s32 func_8021A334(f32 arg0, f32 arg1, f32 arg2, f32 arg3, u16 arg4) {
    f32 temp_fa1;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 temp_fv0;
    s32 var_v1;
    UnkFxStruct* var_v0;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_8028B400); i++) {
        var_v0 = &D_8028B400[i];
        if ((var_v0->unk4 == 0) || !(var_v0->unk5C & arg4)) {
            continue;
        }
        temp_fv0 = SQ(var_v0->unk14 + arg3);
        temp_fa1 = SQ(var_v0->unk68.m[3][0] - arg0);
        if (temp_fv0 < temp_fa1) {
            continue;
        }
        temp_ft4 = SQ(var_v0->unk68.m[3][1] - arg1);
        if (temp_fv0 < temp_ft4) {
            continue;
        }

        temp_ft5 = SQ(var_v0->unk68.m[3][2] - arg2);
        if (temp_fv0 < temp_ft5) {
            continue;
        }

        if ((temp_fa1 + temp_ft4 + temp_ft5) <= temp_fv0) {
            return i;
        }
    }

    return 0xFF;
}

void func_8021A4D8(s32 fxId, Mtx4F* arg1) {
    UnkFxStruct* temp_v0;

    if (fxId == 0xFF) {
        return;
    }

    if (D_8028B400[fxId].type == 4) {
        func_8021BE28(fxId, arg1);
    } else {
        uvMat4Copy(&D_8028B400[fxId].unk68, arg1);
    }
}

void uvFxProps(s32 fxId, ...) {
    f32 var_fa0;
    f32 var_fv0;
    f32 temp_fv0;
    f32 temp_ft2;
    s16 propertyType;
    UnkFxStruct* var_a2;
    va_list args;
    UnkModelTrail* temp_v0;

    if (fxId == 0xFF) {
        return;
    }
    var_a2 = &D_8028B400[fxId];
    va_start(args, fxId);
    // FAKE
    if (1) { }
    if (1) { }
    if (1) { }

    while (TRUE) {
        propertyType = va_arg(args, s32);
        switch (propertyType) {
        case 0:
            return;
        case 1:
            var_a2->unk8 = va_arg(args, f64);
            if (var_a2->type == 4) {
                temp_v0 = var_a2->unkA8;
                temp_fv0 = uvGfxGetUnkStateF();
                temp_ft2 = 10.0f;
                if (temp_fv0 > 0.0f) {
                    temp_v0->unk1E4 = (s32)(var_a2->unk8 / temp_fv0);
                } else {
                    temp_v0->unk1E4 = temp_ft2;
                }
                temp_v0->unk1D0 = (f32)(var_a2->unk55 - var_a2->unk59) / (f32)(temp_v0->unk1E4 * 9);
            }
            break;
        case 19:
            temp_fv0 = va_arg(args, f64);
            var_a2->unkAC = SQ(temp_fv0);
            break;
        case 2:
            var_a2->unkC = va_arg(args, f64);
            break;
        case 13:
            var_a2->unk2 = va_arg(args, s32);
            break;
        case 16:
            var_a2->unk5C = va_arg(args, s32);
            break;
        case 17:
            var_a2->unk60 = va_arg(args, s32);
            break;
        case 18:
            var_a2->unk64 = va_arg(args, s32);
            break;
        case 7:
            var_a2->unk48 = va_arg(args, f64);
            break;
        case 8:
            var_a2->unk50 = va_arg(args, s32);
            if ((var_a2->unk50 != 0xFFF) && (gGfxUnkPtrs->textures[var_a2->unk50] == NULL)) {
                _uvDebugPrintf(" uvFxProps: texture id %d not in level\n", var_a2->unk50);
                var_a2->unk50 = 0xFFF;
            }
            break;
        case 15:
            var_a2->unk4C = va_arg(args, f64);
            break;
        case 3:
            var_a2->unk30 = va_arg(args, f64);
            var_a2->unk20 = var_a2->unk30 * 0.005f;
            var_a2->unk34 = va_arg(args, f64);
            var_a2->unk24 = var_a2->unk34 * 0.005f;
            var_a2->unk38 = va_arg(args, f64);
            var_a2->unk28 = var_a2->unk38 * 0.005f;

            var_fv0 = MAX(var_a2->unk30, var_a2->unk34);
            var_fa0 = MAX(var_a2->unk38, var_fv0);

            var_a2->unk14 = var_fa0;
            break;
        case 4:
            var_a2->unk3C = va_arg(args, f64);
            var_a2->unk40 = va_arg(args, f64);
            var_a2->unk44 = va_arg(args, f64);

            var_fv0 = MAX(var_a2->unk3C, var_a2->unk40);
            //! @bug should be checking max with unk44?
            var_fa0 = MAX(var_a2->unk3C, var_fv0);

            var_a2->unk18 = var_fa0;
            if (var_fa0 > 1.0f) {
                var_a2->unk7 = 1;
            }
            break;
        case 5:
            var_a2->unk52 = (f32)va_arg(args, f64) * 255.0f;
            var_a2->unk53 = (f32)va_arg(args, f64) * 255.0f;
            var_a2->unk54 = (f32)va_arg(args, f64) * 255.0f;
            var_a2->unk55 = (f32)va_arg(args, f64) * 255.0f;
            if (var_a2->type == 4) {
                temp_v0 = var_a2->unkA8;
                temp_v0->unk190.x = var_a2->unk52 - var_a2->unk56;
                temp_v0->unk190.y = var_a2->unk53 - var_a2->unk57;
                temp_v0->unk190.z = var_a2->unk54 - var_a2->unk58;
                temp_v0->unk1D0 = (f32)(var_a2->unk55 - var_a2->unk59) / (f32)(temp_v0->unk1E4 * 9);
            }
            break;
        case 6:
            var_a2->unk56 = (f32)va_arg(args, f64) * 255.0f;
            var_a2->unk57 = (f32)va_arg(args, f64) * 255.0f;
            var_a2->unk58 = (f32)va_arg(args, f64) * 255.0f;
            var_a2->unk59 = (f32)va_arg(args, f64) * 255.0f;
            if (var_a2->type == 4) {
                temp_v0 = var_a2->unkA8;
                temp_v0->unk190.x = var_a2->unk52 - var_a2->unk56;
                temp_v0->unk190.y = var_a2->unk53 - var_a2->unk57;
                temp_v0->unk190.z = var_a2->unk54 - var_a2->unk58;
                temp_v0->unk1D0 = (f32)(var_a2->unk55 - var_a2->unk59) / (f32)(temp_v0->unk1E4 * 9);
            }
            break;
        case 10:
            var_a2->unk68.m[3][0] = va_arg(args, f64);
            var_a2->unk68.m[3][1] = va_arg(args, f64);
            var_a2->unk68.m[3][2] = va_arg(args, f64);
            break;
        case 11:
            var_a2->unk4 = va_arg(args, s32);
            if (var_a2->type == 8) {
                ((UnkModelDebrisStructure*)(var_a2->unkA8))->unk2E4 = 0;
            }
            break;
        case 12:
            var_a2->unk68.m[2][0] = va_arg(args, f64);
            var_a2->unk68.m[2][1] = va_arg(args, f64);
            var_a2->unk68.m[2][2] = va_arg(args, f64);
            break;
        case 14:
            var_a2->ditherProperty = va_arg(args, s32);
            break;
        default:
            _uvDebugPrintf("uvFxProps: Unknown property type %d\n", propertyType);
            return;
        }
    }
}

void uvFxGetProps(s32 fxId, ...) {
    UnkFxStruct* temp_s2;
    s16 propertyType;
    va_list args;

    if (fxId == 0xFF) {
        return;
    }
    temp_s2 = &D_8028B400[fxId];
    va_start(args, fxId);

    while (TRUE) {
        propertyType = va_arg(args, s32);
        switch (propertyType) {
        case 0:
            return;
        case 1:
            *va_arg(args, f32*) = temp_s2->unk8;
            break;
        case 19:
            *va_arg(args, f32*) = uvSqrtF(temp_s2->unkAC);
            break;
        case 2:
            *va_arg(args, f32*) = temp_s2->unkC;
            break;
        case 13:
            *va_arg(args, s32*) = temp_s2->unk2;
            break;
        case 16:
            *va_arg(args, s16*) = temp_s2->unk5C;
            break;
        case 17:
            *va_arg(args, s32*) = temp_s2->unk60;
            break;
        case 18:
            *va_arg(args, s32*) = temp_s2->unk64;
            break;
        case 7:
            *va_arg(args, f32*) = temp_s2->unk48;
            break;
        case 8:
            *va_arg(args, s32*) = temp_s2->unk50;
            break;
        case 15:
            *va_arg(args, f32*) = temp_s2->unk4C;
            break;
        case 3:
            *va_arg(args, f32*) = temp_s2->unk30;
            *va_arg(args, f32*) = temp_s2->unk34;
            *va_arg(args, f32*) = temp_s2->unk38;
            break;
        case 5:
            *va_arg(args, f32*) = temp_s2->unk52 / 255.0f;
            *va_arg(args, f32*) = temp_s2->unk53 / 255.0f;
            *va_arg(args, f32*) = temp_s2->unk54 / 255.0f;
            *va_arg(args, f32*) = temp_s2->unk55 / 255.0f;
            break;
        case 6:
            *va_arg(args, f32*) = temp_s2->unk56 / 255.0f;
            *va_arg(args, f32*) = temp_s2->unk57 / 255.0f;
            *va_arg(args, f32*) = temp_s2->unk58 / 255.0f;
            *va_arg(args, f32*) = temp_s2->unk59 / 255.0f;
            break;
        case 10:
            *va_arg(args, f32*) = temp_s2->unk68.m[3][0];
            *va_arg(args, f32*) = temp_s2->unk68.m[3][1];
            *va_arg(args, f32*) = temp_s2->unk68.m[3][2];
            break;
        case 11:
            *va_arg(args, s32*) = temp_s2->unk4;
            break;
        case 12:
            *va_arg(args, f32*) = temp_s2->unk68.m[2][0];
            *va_arg(args, f32*) = temp_s2->unk68.m[2][1];
            *va_arg(args, f32*) = temp_s2->unk68.m[2][2];
            break;
        case 14:
            *va_arg(args, s32*) = temp_s2->ditherProperty;
            break;
        default:
            _uvDebugPrintf("uvFxGetProps: Unknown property type %d\n", propertyType);
            return;
        }
    }
}

s32 uvModelGet(s32 fxId, s32 modelId) {
    UnkFxStruct* var_v1;
    s32 i;
    s32 pad[3];

    var_v1 = &D_8028B400[fxId];
    if (fxId == 0xFF) {
        return 0;
    }
    if (modelId == 0xFF) {
        if (var_v1->type == 4) {
            ((UnkModelTrail*)(var_v1->unkA8))->unk1EC = 0;
        }
        if (var_v1->type == 8) {
            ((UnkModelDebrisStructure*)(var_v1->unkA8))->unk2E4 = 0;
        }
        var_v1->unk4 = 0;
        var_v1->type = modelId;
        return 1;
    }

    var_v1->unk6 = 0;
    var_v1->unk7 = 0;
    var_v1->unk52 = 255;
    var_v1->unk53 = 255;
    var_v1->unk54 = 255;
    var_v1->unk55 = 255;
    var_v1->unkA8 = NULL;
    var_v1->unk2 = 255;
    var_v1->unk50 = 0xFFF;
    var_v1->ditherProperty = 4;
    var_v1->unk5C = 0;
    var_v1->unk60 = 0;
    var_v1->unk64 = 0;
    var_v1->unk8 = var_v1->unk10 = 1.0f;
    var_v1->unkC = var_v1->unk1C = 0.0f;
    var_v1->unk20 = 0.005f;
    var_v1->unk24 = 0.005f;
    var_v1->unk28 = 0.005f;
    var_v1->unk30 = 1.0f;
    var_v1->unk34 = 1.0f;
    var_v1->unk38 = 1.0f;
    var_v1->unk3C = 1.0f;
    var_v1->unk40 = 1.0f;
    var_v1->unk44 = 1.0f;
    var_v1->unk18 = 1.0f;
    var_v1->unk48 = 1.0f;
    var_v1->unk4C = 0.0f;
    var_v1->unk14 = 0.5f;
    var_v1->unkAC = FLT_MAX;
    uvMat4SetIdentity(&var_v1->unk68);

    switch (modelId) {
    case 1:
        var_v1->unk0 = 2;
        var_v1->unk7 = 1;
        var_v1->unk6 = 0;
        var_v1->unk3C = 1.1f;
        var_v1->unk40 = 1.1f;
        var_v1->unk44 = 1.1f;
        var_v1->unk18 = 1.1f;
        break;
    case 4:
        var_v1->unk0 = 0;
        var_v1->unk8 = 1e20f;
        var_v1->unk52 = 255;
        var_v1->unk53 = 255;
        var_v1->unk54 = 255;
        var_v1->unk55 = 255;
        var_v1->unk56 = 128;
        var_v1->unk57 = 128;
        var_v1->unk58 = 128;
        var_v1->unk59 = 0;
        for (i = 0; i < ARRAY_COUNT(D_8028AC40); i++) {
            if (D_8028AC40[i].unk1EC == 0) {
                func_8021A038(&D_8028AC40[i]);
                var_v1->unkA8 = &D_8028AC40[i];
                D_8028AC40[i].unk1EC = 1;
                break;
            }
        }

        if (i == ARRAY_COUNT(D_8028AC40)) {
            _uvDebugPrintf("uvModelGet: no more trails available\n");
            return 0;
        }
        uvMat4SetIdentity(&var_v1->unk68);
        uvMat4Scale(&var_v1->unk68, 0.5f, 0.5f, 0.5f);
        break;
    case 6:
        var_v1->unk0 = 2;
        var_v1->unk8 = 1e20f;
        break;
    case 7:
        var_v1->unk0 = 3;
        var_v1->unk8 = 1e20f;
        break;
    case 2:
        var_v1->unk0 = 3;
        var_v1->unk52 = 255;
        var_v1->unk53 = 255;
        var_v1->unk54 = 0;
        var_v1->unk55 = 255;
        var_v1->unk56 = 255;
        var_v1->unk57 = 0;
        var_v1->unk58 = 0;
        var_v1->unk59 = 0;
        var_v1->unk7 = 1;
        var_v1->unk6 = 0;
        var_v1->unk3C = 1.1f;
        var_v1->unk40 = 1.1f;
        var_v1->unk44 = 1.1f;
        var_v1->unk18 = 1.1f;
        break;
    case 8:
        var_v1->unk0 = 0;
        var_v1->unk8 = 1e20f;
        var_v1->unk52 = 0;
        var_v1->unk53 = 0;
        var_v1->unk54 = 0;
        var_v1->unk55 = 0;
        var_v1->unk56 = 128;
        var_v1->unk57 = 128;
        var_v1->unk58 = 128;
        var_v1->unk59 = 0;

        for (i = 0; i < ARRAY_COUNT(D_8028A0A0); i++) {
            if (D_8028A0A0[i].unk2E4 == 0) {
                func_8021A0CC(&D_8028A0A0[i]);
                var_v1->unkA8 = &D_8028A0A0[i];
                D_8028A0A0[i].unk2E4 = 1;
                break;
            }
        }

        if (i == ARRAY_COUNT(D_8028A0A0)) {
            _uvDebugPrintf("uvModelGet: no more debris structures available\n");
            return 0;
        }
        break;
    case 5:
        var_v1->unk0 = 3;
        var_v1->unk52 = 255;
        var_v1->unk53 = 0;
        var_v1->unk54 = 0;
        var_v1->unk55 = 255;
        var_v1->unk56 = 255;
        var_v1->unk57 = 255;
        var_v1->unk58 = 0;
        var_v1->unk59 = 128;
        var_v1->unk8 = 1e20f;
        break;
    case 3:
        var_v1->unk0 = 0;
        var_v1->unk52 = 150;
        var_v1->unk53 = 150;
        var_v1->unk54 = 150;
        var_v1->unk55 = 50;
        var_v1->unk8 = 1e20f;
        break;
    default:
        _uvDebugPrintf("uvFxModel: unknown model id: %d\n", modelId);
        return 0;
    }

    var_v1->type = modelId;
    var_v1->unk4 = 1;
    var_v1->unk5 = 0;
    return 1;
}

void func_8021BE28(u16 fxId, Mtx4F* arg1) {
    UnkModelTrail* temp_v1;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 temp_fa0;
    f32 temp_fa1;
    s32 temp_hi;
    s32 temp_hi_2;
    UnkFxStruct* temp_v0;

    temp_v0 = &D_8028B400[fxId];
    temp_v0->unk4 = 1;
    temp_v1 = temp_v0->unkA8;
    temp_v1->unk1C4.x = arg1->m[3][0] * 2;
    temp_fv0 = temp_v1->unk1C4.x;
    temp_v1->unk1C4.y = arg1->m[3][1] * 2;
    temp_fv1 = temp_v1->unk1C4.y;
    temp_v1->unk1C4.z = arg1->m[3][2] * 2;
    temp_fa0 = temp_v1->unk1C4.z;
    temp_v1->unk1D4 = temp_v0->unk55;
    temp_hi = temp_v1->unk1E8 % 10;
    temp_v1->unk168[temp_hi] = temp_v0->unk55;
    if (temp_v1->unk1E8 == 0) {
        if (temp_v1->unk1E6 == 0) {
            temp_v1->unk1D8.x = temp_fv0;
            temp_v1->unk1D8.y = temp_fv1;
            temp_v1->unk1D8.z = temp_fa0;
        }
        if (temp_v1->unk1E4 <= 0.0f) {
            temp_v1->unk1E4 = 10;
        }

        temp_fa1 = ((f32)temp_v1->unk1E6 * 2 * temp_v0->unk34) / temp_v1->unk1E4;
        temp_v1->unk0[0].unk0 = (arg1->m[0][0] * temp_fa1) + temp_v1->unk1D8.x;
        temp_v1->unk0[0].unk2 = (arg1->m[0][1] * temp_fa1) + temp_v1->unk1D8.y;
        temp_v1->unk0[0].unk4 = (arg1->m[0][2] * temp_fa1) + temp_v1->unk1D8.z;
        temp_v1->unk0[0].unk6 = (arg1->m[2][0] * temp_fa1) + temp_v1->unk1D8.x;
        temp_v1->unk0[0].unk8 = (arg1->m[2][1] * temp_fa1) + temp_v1->unk1D8.y;
        temp_v1->unk0[0].unkA = (arg1->m[2][2] * temp_fa1) + temp_v1->unk1D8.z;
        temp_v1->unk0[0].unkC = temp_v1->unk1D8.x - (arg1->m[0][0] * temp_fa1);
        temp_v1->unk0[0].unkE = temp_v1->unk1D8.y - (arg1->m[0][1] * temp_fa1);
        temp_v1->unk0[0].unk10 = temp_v1->unk1D8.z - (arg1->m[0][2] * temp_fa1);
        temp_v1->unk0[0].unk12 = temp_v1->unk1D8.x - (arg1->m[2][0] * temp_fa1);
        temp_v1->unk0[0].unk14 = temp_v1->unk1D8.y - (arg1->m[2][1] * temp_fa1);
        temp_v1->unk0[0].unk16 = temp_v1->unk1D8.z - (arg1->m[2][2] * temp_fa1);
        temp_v1->unkF0[0].x = temp_v1->unk1D8.x / 2;
        temp_v1->unkF0[0].y = temp_v1->unk1D8.y / 2;
        temp_v1->unkF0[0].z = temp_v1->unk1D8.z / 2;
    } else if (temp_v1->unk1E8 > 0) {
        temp_fa1 = temp_v0->unk34 * 2 * temp_v1->unk1E4;
        temp_fv0 = temp_v1->unk1C4.x - arg1->m[1][0] * temp_fa1;
        temp_fv1 = temp_v1->unk1C4.y - arg1->m[1][1] * temp_fa1;
        temp_fa0 = temp_v1->unk1C4.z - arg1->m[1][2] * temp_fa1;
        temp_v1->unk0[temp_hi].unk0 = (arg1->m[0][0] * 2 * temp_v0->unk30) + temp_fv0;
        temp_v1->unk0[temp_hi].unk2 = (arg1->m[0][1] * 2 * temp_v0->unk34) + temp_fv1;
        temp_v1->unk0[temp_hi].unk4 = (arg1->m[0][2] * 2 * temp_v0->unk38) + temp_fa0;
        temp_v1->unk0[temp_hi].unk6 = (arg1->m[2][0] * 2 * temp_v0->unk30) + temp_fv0;
        temp_v1->unk0[temp_hi].unk8 = (arg1->m[2][1] * 2 * temp_v0->unk34) + temp_fv1;
        temp_v1->unk0[temp_hi].unkA = (arg1->m[2][2] * 2 * temp_v0->unk38) + temp_fa0;
        temp_v1->unk0[temp_hi].unkC = temp_fv0 - (arg1->m[0][0] * 2 * temp_v0->unk30);
        temp_v1->unk0[temp_hi].unkE = temp_fv1 - (arg1->m[0][1] * 2 * temp_v0->unk34);
        temp_v1->unk0[temp_hi].unk10 = temp_fa0 - (arg1->m[0][2] * 2 * temp_v0->unk38);
        temp_v1->unk0[temp_hi].unk12 = temp_fv0 - (arg1->m[2][0] * 2 * temp_v0->unk30);
        temp_v1->unk0[temp_hi].unk14 = temp_fv1 - (arg1->m[2][1] * 2 * temp_v0->unk34);
        temp_v1->unk0[temp_hi].unk16 = temp_fa0 - (arg1->m[2][2] * 2 * temp_v0->unk38);
        temp_v1->unkF0[temp_hi].x = temp_fv0 / 2;
        temp_v1->unkF0[temp_hi].y = temp_fv1 / 2;
        temp_v1->unkF0[temp_hi].z = temp_fa0 / 2;
    }
    temp_v1->unk1E6++;
    if (temp_v1->unk1E6 >= temp_v1->unk1E4) {
        temp_v1->unk1E6 = 0;
        temp_hi_2 = temp_v1->unk1E8 % 10;
        temp_v1->unk1E8++;
        temp_hi = temp_v1->unk1E8 % 10;
        temp_v1->unkF0[temp_hi].x = temp_v1->unk1D8.x / 2;
        temp_v1->unkF0[temp_hi].y = temp_v1->unk1D8.y / 2;
        temp_v1->unkF0[temp_hi].z = temp_v1->unk1D8.z / 2;
        temp_v1->unk1D8.x = temp_v1->unk1C4.x;
        temp_v1->unk1D8.y = temp_v1->unk1C4.y;
        temp_v1->unk1D8.z = temp_v1->unk1C4.z;

        temp_v1->unk168[temp_hi] = temp_v0->unk55;
        temp_v1->unk0[temp_hi].unk0 = temp_v1->unk0[temp_hi_2].unk0;
        temp_v1->unk0[temp_hi].unk2 = temp_v1->unk0[temp_hi_2].unk2;
        temp_v1->unk0[temp_hi].unk4 = temp_v1->unk0[temp_hi_2].unk4;
        temp_v1->unk0[temp_hi].unk6 = temp_v1->unk0[temp_hi_2].unk6;
        temp_v1->unk0[temp_hi].unk8 = temp_v1->unk0[temp_hi_2].unk8;
        temp_v1->unk0[temp_hi].unkA = temp_v1->unk0[temp_hi_2].unkA;
        temp_v1->unk0[temp_hi].unkC = temp_v1->unk0[temp_hi_2].unkC;
        temp_v1->unk0[temp_hi].unkE = temp_v1->unk0[temp_hi_2].unkE;
        temp_v1->unk0[temp_hi].unk10 = temp_v1->unk0[temp_hi_2].unk10;
        temp_v1->unk0[temp_hi].unk12 = temp_v1->unk0[temp_hi_2].unk12;
        temp_v1->unk0[temp_hi].unk14 = temp_v1->unk0[temp_hi_2].unk14;
        temp_v1->unk0[temp_hi].unk16 = temp_v1->unk0[temp_hi_2].unk16;
    }
}

void func_8021C4F8(u16 arg0) {
    UnkModelDebrisStructure* temp_fp;
    UnkFxStruct* temp_s0;
    s32 i;
    u8 spC3;
    u8 spC2;
    u8 spC1;
    Mtx4F sp80;

    temp_s0 = &D_8028B400[arg0];
    temp_fp = temp_s0->unkA8;
    spC3 = temp_s0->unk52;
    spC2 = temp_s0->unk53;
    spC1 = temp_s0->unk54;
    uvMat4Copy(&sp80, &temp_s0->unk68);
    uvGfx_802236CC(&sp80);
    uvGfxSetFlags(0xFFF);

    if (temp_s0->unk60 != 0) {
        uvGfxSetFlags(temp_s0->unk60);
    }
    if (temp_s0->unk64 != 0) {
        uvGfxClearFlags(temp_s0->unk64);
    }

    for (i = 0; i < ARRAY_COUNT(temp_fp->unk0); i++) {
        if (temp_fp->unk2D0[i] != 0) {
            uvMat4SetIdentity(&sp80);
            sp80.m[3][0] = temp_fp->unk0[i].x;
            sp80.m[3][1] = temp_fp->unk0[i].y;
            sp80.m[3][2] = temp_fp->unk0[i].z;
            uvMat4RotateAxis(&sp80, temp_fp->unk1E0[i] * 0.2f, 122);
            uvMat4RotateAxis(&sp80, temp_fp->unk1E0[i] * 0.37f, ARRAY_COUNT(D_8028B400));
            uvGfxMtxViewMul(&sp80, 1);
            uvVtxBeginPoly();
            uvVtx(0, 2, 0, 0, 0, spC3, spC2, spC1, 230);
            uvVtx(1, -1, 0, 0, 0, spC3, spC2, spC1, 230);
            uvVtx(-2, -1, 0, 0, 0, spC3, spC2, spC1, 230);
            uvVtxEndPoly();
            uvGfxMtxViewPop();
        }
    }
    uvGfxMtxViewPop();
}

void func_8021C74C(u16 arg0) {
    UnkFxStruct* temp_t2;
    UnkModelDebrisStructure* temp_a2;
    s32 i;
    f32 temp_fv0;
    s32 var_t1;
    s32 pad[2];

    temp_t2 = &D_8028B400[arg0];
    temp_a2 = temp_t2->unkA8;
    temp_fv0 = uvGfxGetUnkStateF();
    var_t1 = TRUE;

    for (i = 0; i < ARRAY_COUNT(temp_a2->unk0); i++) {
        if (temp_a2->unk2D0[i] != 0) {
            var_t1 = FALSE;
            temp_a2->unk0[i].x += temp_a2->unkF0[i].x * temp_fv0;
            temp_a2->unk0[i].y += temp_a2->unkF0[i].y * temp_fv0;
            temp_a2->unk0[i].z += temp_a2->unkF0[i].z * temp_fv0;
            temp_a2->unkF0[i].z += -62.999996f * temp_fv0;
            temp_a2->unk1E0[i] += temp_a2->unk230[i] * temp_fv0;
            temp_a2->unk280[i] -= temp_fv0;
            if (temp_a2->unk280[i] <= 0.0f) {
                temp_a2->unk2D0[i] = 0;
            }
        }
    }
    if (var_t1) {
        temp_t2->unk4 = 0;
        temp_a2->unk2E4 = 0;
    }
}

#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/nonmatchings/kernel/fx/func_8021C87C.s")
void func_8021C87C(u16 arg0);
#else
void func_8021C87C(u16 arg0) {
    s16 i;
    s16 sp94;
    UnkModelTrail* temp_s6;
    u8 pad;
    u8 sp6C;
    u8 sp8D;
    u8 sp8C;
    u8 sp8B;
    u8 sp8A;
    s16 pad2;
    s16 var_fp;
    s16 j;
    s16 sp82;
    s16 sp80;
    s32 temp_a0;
    unk8028B400* sp70;
    s32 pad3;

    sp70 = &D_8028B400[arg0];
    temp_s6 = sp70->unkA8;
    if (sp70->unk4 == 0) {
        return;
    }
    i = temp_s6->unk1E8 % 10;
    if (temp_s6->unk1E8 < 9) {
        sp94 = temp_s6->unk1E8;
    } else {
        sp94 = 9;
    }
    sp8A = temp_s6->unk1D4;
    sp6C = temp_s6->unk168[i];
    if ((sp8A == sp6C) && (sp6C == 0)) {
        sp70->unk4 = 0;
        temp_s6->unk1EC = 0;
        return;
    }

    uvGfx_802236CC(&sp70->unk68);

    if ((sp70->unk50 != 0xFFF) && (gGfxUnkPtrs->textures[sp70->unk50] != NULL)) {
        sp82 = gGfxUnkPtrs->textures[sp70->unk50]->width << 5;
        sp80 = gGfxUnkPtrs->textures[sp70->unk50]->height << 5;
        uvGfx_80223A28(sp70->unk50);
    } else {
        uvGfxSetFlags(0xFFF);
        sp82 = sp80 = 0;
    }

    if (sp70->unk60 != 0) {
        uvGfxSetFlags(sp70->unk60);
    }

    if (sp70->unk64 != 0) {
        uvGfxClearFlags(sp70->unk64);
    }
    sp8D = sp70->unk52;
    sp8C = sp70->unk53;
    sp8B = sp70->unk54;

    uvVtxBeginPoly();
    uvVtx((s16)temp_s6->unk1C4.x, (s16)temp_s6->unk1C4.y, (s16)temp_s6->unk1C4.z, sp82 / 2, 0, sp8D, sp8C, sp8B, sp8A);
    if (sp94 > 0) {
        uvBeginTmesh();
    }
    uvVtx(temp_s6->unk0[i].unk6, temp_s6->unk0[i].unk8, temp_s6->unk0[i].unkA, 0, sp80, sp8D, sp8C, sp8B, sp6C);
    uvVtx(temp_s6->unk0[i].unk12, temp_s6->unk0[i].unk14, temp_s6->unk0[i].unk16, sp82, sp80, sp8D, sp8C, sp8B, sp6C);
    uvVtxEndPoly();
    var_fp = 1;

    for (i = 0; i < sp94; i++) {
        j = ((temp_s6->unk1E8 - i) + 9) % 10;
        sp8A = temp_s6->unk168[j];
        // FAKE
        if ((temp_s6->unk1E8 - i) / 10) { }
        if (!sp8A) {
            continue;
        }
        sp8D = ((temp_s6->unk190.x / 10.0f) * (10 - i)) + sp70->unk56;
        sp8C = ((temp_s6->unk190.y / 10.0f) * (10 - i)) + sp70->unk57;
        sp8B = ((temp_s6->unk190.z / 10.0f) * (10 - i)) + sp70->unk58;
        uvVtx(temp_s6->unk0[j].unk6, temp_s6->unk0[j].unk8, temp_s6->unk0[j].unkA, 0, sp80 * var_fp, sp8D, sp8C, sp8B, sp8A);
        uvVtx(temp_s6->unk0[j].unk12, temp_s6->unk0[j].unk14, temp_s6->unk0[j].unk16, sp82, sp80 * var_fp, sp8D, sp8C, sp8B, sp8A);

        var_fp++;
    }
    if (var_fp >= 2) {
        uvEndTmesh();
    }

    i = temp_s6->unk1E8 % 10;
    if (temp_s6->unk1E8 < 9) {
        sp94 = temp_s6->unk1E8;
    } else {
        sp94 = 9;
    }
    sp8A = temp_s6->unk1D4;
    sp6C = temp_s6->unk168[i];
    sp8D = sp70->unk52;
    sp8C = sp70->unk53;
    sp8B = sp70->unk54;
    uvVtxBeginPoly();
    uvVtx((s16)temp_s6->unk1C4.x, (s16)temp_s6->unk1C4.y, (s16)temp_s6->unk1C4.z, sp82 / 2, 0, sp8D, sp8C, sp8B, sp8A);
    if (sp94 > 0) {
        uvBeginTmesh();
    }

    uvVtx(temp_s6->unk0[i].unk0, temp_s6->unk0[i].unk2, temp_s6->unk0[i].unk4, 0, sp80, sp8D, sp8C, sp8B, sp6C);
    uvVtx(temp_s6->unk0[i].unkC, temp_s6->unk0[i].unkE, temp_s6->unk0[i].unk10, sp82, sp80, sp8D, sp8C, sp8B, sp6C);
    uvVtxEndPoly();
    var_fp = 1;

    for (i = 0; i < sp94; i++) {
        j = ((temp_s6->unk1E8 - i) + 9) % 10;
        sp8A = temp_s6->unk168[j];
        // FAKE
        if ((temp_s6->unk1E8 - i) / 10) { }
        if (!sp8A) {
            continue;
        }
        sp8D = ((temp_s6->unk190.x / 10.0f) * (10 - i)) + sp70->unk56;
        sp8C = ((temp_s6->unk190.y / 10.0f) * (10 - i)) + sp70->unk57;
        sp8B = ((temp_s6->unk190.z / 10.0f) * (10 - i)) + sp70->unk58;
        uvVtx(temp_s6->unk0[j].unk0, temp_s6->unk0[j].unk2, temp_s6->unk0[j].unk4, 0, sp80 * var_fp, sp8D, sp8C, sp8B, sp8A);
        uvVtx(temp_s6->unk0[j].unkC, temp_s6->unk0[j].unkE, temp_s6->unk0[j].unk10, sp82, sp80 * var_fp, sp8D, sp8C, sp8B, sp8A);
        var_fp++;
    }
    if (var_fp >= 2) {
        uvEndTmesh();
    }
    uvGfxMtxViewPop();
}
#endif

void func_8021D700(UnkModelTrail* arg0) {
    s32 i;

    if (uvGfxGetUnkStateF() < 0.00001f) {
        return;
    }

    for (i = 0; i < ARRAY_COUNT(arg0->unk168); i++) {
        if (arg0->unk168[i] > 0.0f) {
            arg0->unk168[i] -= arg0->unk1D0;
        }
        if (arg0->unk168[i] < 0.0f) {
            arg0->unk168[i] = 0.0f;
        }
    }

    if (arg0->unk1D4 > 0.0f) {
        arg0->unk1D4 -= arg0->unk1D0;
    }
    if (arg0->unk1D4 < 0.0f) {
        arg0->unk1D4 = 0.0f;
    }
}

void func_8021D8E0(u16 fxId) {
    UnkFxStruct* temp_s1;
    s32 i;
    f32 var_fs0;
    f32 spA0;
    f32 sp9C;
    f32 temp_fv0;
    f32 temp_fv1;
    Mtx4F sp54;

    temp_s1 = &D_8028B400[fxId];
    temp_fv1 = temp_s1->unk1C / temp_s1->unk8;
    if (temp_s1->unk8 >= 1e20) {
        var_fs0 = temp_s1->unk10 * 255.0f;
    } else {
        var_fs0 = (1.0f - SQ(temp_fv1)) * 255.0f * temp_s1->unk10;
    }
    spA0 = temp_s1->unk30 * temp_fv1 * 0.01f;
    sp9C = temp_s1->unk38 * temp_fv1 * 0.01f;
    uvMat4Copy(&sp54, &temp_s1->unk68);
    uvMat4Scale(&sp54, spA0, 1.0f, sp9C);
    uvGfx_802236CC(&sp54);
    uvBeginGrid();
    for (i = 0; i < ARRAY_COUNT(D_80248F34); i++) {
        temp_fv0 = D_80248F34[i].unk4 * var_fs0;
        uvVtx(D_80248F34[i].unk0, 0, D_80248F34[i].unk2, 0, 0, temp_s1->unk52, temp_s1->unk53, (s32)temp_s1->unk54, (u8)(temp_fv0));
    }
    uvEndGrid(8, 8, 0, 0);
    uvGfxMtxViewPop();
}

void func_8021DAF8(u16 fxId) {
    UnkFxStruct* temp_s1;
    f32 var_fa1;
    f32 temp_fv0;
    s32 i;

    temp_s1 = &D_8028B400[fxId];
    uvGfxSetFlags(0xFFF);
    if (temp_s1->unk60 != 0) {
        uvGfxSetFlags(temp_s1->unk60);
    }
    if (temp_s1->unk64 != 0) {
        uvGfxClearFlags(temp_s1->unk64);
    }

    if (temp_s1->unk8 >= 1e20) {
        var_fa1 = 0.0f;
    } else {
        var_fa1 = temp_s1->unk1C / temp_s1->unk8;
    }

    temp_s1->unk68.m[0][0] *= temp_s1->unk20;
    temp_s1->unk68.m[0][1] *= temp_s1->unk20;
    temp_s1->unk68.m[0][2] *= temp_s1->unk20;
    temp_s1->unk68.m[1][0] *= temp_s1->unk24;
    temp_s1->unk68.m[1][1] *= temp_s1->unk24;
    temp_s1->unk68.m[1][2] *= temp_s1->unk24;
    temp_s1->unk68.m[2][0] *= temp_s1->unk28;
    temp_s1->unk68.m[2][1] *= temp_s1->unk28;
    temp_s1->unk68.m[2][2] *= temp_s1->unk28;
    uvGfx_802236CC(&temp_s1->unk68);
    uvVtxBeginPoly();

    temp_fv0 = temp_s1->unk55 * (1.0f - SQ(var_fa1)) * temp_s1->unk10;

    uvVtx(D_80248EA0[0].unk0, 0, D_80248EA0[0].unk2, 0, 0, temp_s1->unk52, temp_s1->unk53, temp_s1->unk54, (s16)(temp_fv0));

    for (i = 9; i > 0; i--) {
        uvVtx(D_80248EA0[i].unk0, 0, D_80248EA0[i].unk2, 0, 0, temp_s1->unk56, temp_s1->unk57, temp_s1->unk58, temp_s1->unk59);
    }
    uvVtxEndPoly();
    uvGfxMtxViewPop();
}

void func_8021DD30(u16 fxId) {
    UnkFxStruct* temp_s0;
    Mtx4F sp94;
    ParsedUVTX* sp90;
    ParsedUVTX* sp8C;
    u8 sp8B;
    u16 var_a0;
    u16 sp86;
    u16 sp84;
    u16 sp82;
    u16 sp80;
    u16 sp7E;
    u16 sp7C;
    u16 sp7A;
    u16 sp78;
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    u16 temp_a0;
    u16 temp_v0;

    temp_s0 = &D_8028B400[fxId];
    if (temp_s0->unk2 != 0xFF) {
        var_a0 = func_80219240(temp_s0->unk2);
    } else {
        if (temp_s0->unk50 != 0xFFF) {
            var_a0 = temp_s0->unk50;
        } else {
            var_a0 = 0xFFF;
        }
    }
    if ((var_a0 != 0xFFF) && ((sp90 = gGfxUnkPtrs->textures[var_a0]) != NULL)) {
        sp8C = sp90;
        uvGfx_80223A28(var_a0);
        if (temp_s0->unk4C == 0.0f) {
            sp78 = 0;
            sp7A = 0;
            sp7C = sp90->width << 5;
            sp7E = 0;
            sp80 = sp8C->width << 5;
            sp82 = sp90->height << 5;
            sp84 = 0;
            sp86 = sp8C->height << 5;
        } else {
            sp74 = temp_s0->unk4C * 0.0174533f;
            sp6C = uvSinF(sp74);
            sp70 = uvCosF(sp74);
            temp_v0 = sp90->width << 4;
            temp_a0 = sp90->height << 4;

            sp78 = (-temp_v0 * sp70) + (temp_a0 * sp6C) + temp_v0;
            sp7A = (-temp_v0 * sp6C) - (temp_a0 * sp70) + temp_a0;
            sp7C = (temp_v0 * sp70) + (temp_a0 * sp6C) + temp_v0;
            sp7E = (temp_v0 * sp6C) - (temp_a0 * sp70) + temp_a0;
            sp80 = (temp_v0 * sp70) - (temp_a0 * sp6C) + temp_v0;
            sp82 = (temp_v0 * sp6C) + (temp_a0 * sp70) + temp_a0;
            sp84 = (-temp_v0 * sp70) - (temp_a0 * sp6C) + temp_v0;
            sp86 = (-temp_v0 * sp6C) + (temp_a0 * sp70) + temp_a0;
        }
    } else {
        uvGfxSetFlags(0xFFF);
        sp78 = 0;
        sp7A = 0;
        sp7C = 0;
        sp7E = 0;
        sp80 = 0;
        sp82 = 0;
        sp84 = 0;
        sp86 = 0;
    }

    if (temp_s0->unk60 != 0) {
        uvGfxSetFlags(temp_s0->unk60);
    }
    if (temp_s0->unk64 != 0) {
        uvGfxClearFlags(temp_s0->unk64);
    }
    uvMat4Copy(&sp94, &temp_s0->unk68);
    sp94.m[0][0] *= temp_s0->unk20;
    sp94.m[0][1] *= temp_s0->unk20;
    sp94.m[0][2] *= temp_s0->unk20;
    sp94.m[2][0] *= temp_s0->unk28;
    sp94.m[2][1] *= temp_s0->unk28;
    sp94.m[2][2] *= temp_s0->unk28;
    sp8B = temp_s0->unk48 * temp_s0->unk55;
    uvGfx_802236CC(&sp94);
    uvVtxBeginPoly();
    uvVtx(-100, 0, 0, sp78, sp7A, temp_s0->unk52, temp_s0->unk53, temp_s0->unk54, sp8B);
    uvVtx(100, 0, 0, sp7C, sp7E, temp_s0->unk52, temp_s0->unk53, temp_s0->unk54, sp8B);
    uvVtx(100, 0, 200, sp80, sp82, temp_s0->unk52, temp_s0->unk53, temp_s0->unk54, sp8B);
    uvVtx(-100, 0, 200, sp84, sp86, temp_s0->unk52, temp_s0->unk53, temp_s0->unk54, sp8B);
    uvVtxEndPoly();
    uvGfxMtxViewPop();
}

void func_8021E608(u16 fxId) {
    UnkFxStruct* temp_s1;
    Mtx4F sp4C;
    s32 i;

    temp_s1 = &D_8028B400[fxId];
    uvMat4Copy(&sp4C, &temp_s1->unk68);
    sp4C.m[0][0] *= temp_s1->unk20;
    sp4C.m[0][1] *= temp_s1->unk20;
    sp4C.m[0][2] *= temp_s1->unk20;
    sp4C.m[1][0] *= temp_s1->unk24;
    sp4C.m[1][1] *= temp_s1->unk24;
    sp4C.m[1][2] *= temp_s1->unk24;
    sp4C.m[2][0] *= temp_s1->unk28;
    sp4C.m[2][1] *= temp_s1->unk28;
    sp4C.m[2][2] *= temp_s1->unk28;
    uvGfx_802236CC(&sp4C);
    uvGfxSetFlags(0xFFF);
    if (temp_s1->unk60 != 0) {
        uvGfxSetFlags(temp_s1->unk60);
    }
    if (temp_s1->unk64 != 0) {
        uvGfxClearFlags(temp_s1->unk64);
    }
    uvVtxBeginPoly();
    uvVtx(D_80248F1C[0].unk0, 0, D_80248F1C[0].unk2, 0, 0, temp_s1->unk52, temp_s1->unk53, temp_s1->unk54, temp_s1->unk55);
    for (i = ARRAY_COUNT(D_80248F1C) - 1; i > 0; i--) {
        uvVtx(D_80248F1C[i].unk0, 0, D_80248F1C[i].unk2, 0, 0, temp_s1->unk56, temp_s1->unk57, temp_s1->unk58, temp_s1->unk59);
    }
    uvVtxEndPoly();
    uvGfxMtxViewPop();
}

void func_8021E7E0(u16 fxId) {
    UnkFxStruct* temp_s2;
    s32 sp98;
    u8 temp_t0;
    Mtx4F sp54;
    s32 i;

    temp_s2 = &D_8028B400[fxId];
    uvMat4Copy(&sp54, &temp_s2->unk68);
    sp54.m[0][0] *= temp_s2->unk20;
    sp54.m[0][1] *= temp_s2->unk20;
    sp54.m[0][2] *= temp_s2->unk20;
    sp54.m[1][0] *= temp_s2->unk24;
    sp54.m[1][1] *= temp_s2->unk24;
    sp54.m[1][2] *= temp_s2->unk24;
    uvGfx_802236CC(&sp54);
    uvGfxSetFlags(0xFFF);
    if (temp_s2->unk60 != 0) {
        uvGfxSetFlags(temp_s2->unk60);
    }
    if (temp_s2->unk64 != 0) {
        uvGfxClearFlags(temp_s2->unk64);
    }
    sp98 = temp_s2->unk1C * 20.0f;
    uvVtxBeginPoly();
    uvVtx(D_80248ED8[0].unk0, D_80248ED8[0].unk2, 0, 0, 0, temp_s2->unk52, temp_s2->unk53, temp_s2->unk54, temp_s2->unk55);
    for (i = 1; i < ARRAY_COUNT(D_80248ED8); i++) {
        temp_t0 = ((temp_s2->unk55 >> 2) << ((sp98 + i) % 4));
        uvVtx(D_80248ED8[i].unk0, D_80248ED8[i].unk2, 0, 0, 0, temp_s2->unk52, temp_s2->unk53, temp_s2->unk54, temp_t0);
    }
    temp_t0 = ((temp_s2->unk55 >> 2) << ((sp98 + 1) % 4));
    uvVtx(D_80248ED8[1].unk0, D_80248ED8[1].unk2, 0, 0, 0, temp_s2->unk52, temp_s2->unk53, temp_s2->unk54, temp_t0);
    uvVtxEndPoly();
    uvGfxMtxViewPop();
}

void func_8021EA38(UnkStruct_80204D94* arg0) {
    f32 temp_fa0;
    f32 temp_fs0;
    f32 temp_fs0_2;
    f32 temp_fs1;
    f32 temp_fs2;
    s32 i;
    UnkFxStruct* var_s0;

    uvGfxResetState();
    i = 0;
    for (i = 0; i < ARRAY_COUNT(D_8028B400); i++) {
        var_s0 = &D_8028B400[i];
        if (var_s0->unk4 == 0) {
            continue;
        }
        if (var_s0->type == 0xFF) {
            continue;
        }
        if (var_s0->unkC > 0.0f) {
            var_s0->unkC -= uvGfxGetUnkStateF();
            continue;
        }
        if (var_s0->type == 4) {
            func_8021D700(var_s0->unkA8);
            _uvSortAdd(1, 1.0f, var_s0, arg0, 1000000.0f, 1000000.0f);
            continue;
        }
        if (var_s0->unk5 == 0) {
            temp_fs0 = uvGfxGetUnkStateF();
            if (var_s0->type == 8) {
                func_8021C74C(i);
            }
            if (var_s0->unk7 != 0) {
                var_s0->unk20 *= 1.0f + ((var_s0->unk3C - 1.0f) * temp_fs0);
                var_s0->unk24 *= 1.0f + ((var_s0->unk40 - 1.0f) * temp_fs0);
                var_s0->unk28 *= 1.0f + ((var_s0->unk44 - 1.0f) * temp_fs0);
                var_s0->unk14 *= 1.0f + ((var_s0->unk18 - 1.0f) * temp_fs0);
            }
            var_s0->unk5 = 1;
            if (temp_fs0 != 0.0f) {
                var_s0->unk1C += temp_fs0;
            }
            if (var_s0->unk8 <= var_s0->unk1C) {
                var_s0->unk4 = 0;
                if (var_s0->type == 8) {
                    ((UnkModelDebrisStructure*)(var_s0->unkA8))->unk2E4 = 0;
                }
                continue;
            }
        }

        temp_fs0_2 = var_s0->unk68.m[3][0] - arg0->unk1D0;
        temp_fs1 = var_s0->unk68.m[3][1] - arg0->unk1D4;
        temp_fs2 = var_s0->unk68.m[3][2] - arg0->unk1D8;
        if (func_80206F64(arg0->unk2E0, temp_fs0_2, temp_fs1, temp_fs2, var_s0->unk14) == 0) {
            continue;
        }
        temp_fa0 = SQ(temp_fs0_2) + SQ(temp_fs1) + SQ(temp_fs2);
        if (var_s0->unkAC < temp_fa0) {
            continue;
        }
        _uvSortAdd(1, uvSqrtF(temp_fa0), var_s0, arg0, var_s0->unk68.m[3][0], var_s0->unk68.m[3][1]);
    }
}

void _uvFxDraw(u16 fxId, UnkStruct_80204D94* arg1) {
    f32 temp_fv1;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 var_fa0;
    s32 pad;
    UnkFxStruct* var_a2;

    var_a2 = &D_8028B400[fxId];
    if (var_a2->unk0 == 2) {
        temp_fv1 = var_a2->unk68.m[3][0] - arg1->unk1D0;
        temp_fa1 = var_a2->unk68.m[3][1] - arg1->unk1D4;
        temp_fv0 = uvSqrtF(SQ(temp_fv1) + SQ(temp_fa1));
        if (temp_fv0 != 0.0f) {
            var_fa0 = 1.0f / temp_fv0;
        } else {
            var_fa0 = 1.0f;
        }
        temp_fv1 *= var_fa0;
        temp_fa1 *= var_fa0;
        var_a2->unk10 = 1.0f;
        var_a2->unk68.m[0][2] = 0.0f;
        var_a2->unk68.m[1][2] = 0.0f;
        var_a2->unk68.m[2][0] = 0.0f;
        var_a2->unk68.m[2][1] = 0.0f;
        var_a2->unk68.m[0][1] = temp_fv1;
        var_a2->unk68.m[1][0] = temp_fv1;
        var_a2->unk68.m[2][2] = 1.0f;
        var_a2->unk68.m[1][1] = temp_fa1;
        var_a2->unk68.m[0][0] = -temp_fa1;
    } else if (var_a2->unk0 == 3) {
        uvMat4CopyXYZ(&var_a2->unk68, &arg1->unk110);
    }

    if (var_a2->ditherProperty != -1) {
        switch (var_a2->ditherProperty) {
        case 0:
            gDPSetColorDither(gGfxDisplayListHead++, G_CD_DISABLE);
            break;
        case 1:
            gDPSetColorDither(gGfxDisplayListHead++, G_CD_NOISE);
            break;
        case 2:
            gDPSetColorDither(gGfxDisplayListHead++, G_CD_MAGICSQ);
            break;
        case 3:
            gDPSetColorDither(gGfxDisplayListHead++, G_CD_BAYER);
            break;
        case 4:
            gDPSetColorDither(gGfxDisplayListHead++, G_CD_NOISE);
            break;
        default:
            _uvDebugPrintf("fx: unknown hw dither property\n");
            break;
        }
    }

    switch (var_a2->type) {
    case 1:
        func_8021D8E0(fxId);
        break;
    case 2:
        func_8021DAF8(fxId);
        break;
    case 8:
        func_8021C4F8(fxId);
        break;
    case 5:
        func_8021E608(fxId);
        break;
    case 3:
        func_8021E7E0(fxId);
        break;
    case 4:
        func_8021C87C(fxId);
        break;
    case 6:
    case 7:
        func_8021DD30(fxId);
        break;
    default:
        _uvDebugPrintf("_uvFxDraw: effect %d Unknown type: %d \n", fxId, var_a2->type);
        break;
    }
}

s32 func_8021EFF0(s32 type) {
    u16 i;

    if (type == 4) {
        for (i = 0; i < ARRAY_COUNT(D_8028AC40); i++) {
            if (D_8028AC40[i].unk1EC == 0) {
                break;
            }
        }
        if (i == ARRAY_COUNT(D_8028AC40)) {
            return 0xFF;
        }
    }
    if (type == 8) {
        for (i = 0; i < ARRAY_COUNT(D_8028A0A0); i++) {
            if (D_8028A0A0[i].unk2E4 == 0) {
                break;
            }
        }
        if (i == ARRAY_COUNT(D_8028A0A0)) {
            return 0xFF;
        }
    }

    for (i = 0; i < ARRAY_COUNT(D_8028B400); i++) {
        if (D_8028B400[i].unk4 == 0) {
            return i;
        }
    }
    return 0xFF;
}
