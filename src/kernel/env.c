#include "common.h"
#include <libc/stdarg.h>
#include <uv_graphics.h>

static Mtx4F D_80248DE0 = {
    1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1,
};

extern Mtx D_80269F10;

void uvEnvProps(s32 arg0, ...) {
    f32 temp_fs0;
    s32 property;
    uvGfxUnkStructEnv* temp_s1;
    va_list args;

    temp_s1 = gGfxUnkPtrs->unk44[arg0];
    va_start(args, arg0);
    if (temp_s1 == NULL) {
        _uvDebugPrintf("uvEnvProps: env %d not in level\n", arg0);
        return;
    }

    while (TRUE) {
        property = va_arg(args, s32);
        switch (property) {
        case 0:
            return;
        case 3:
            temp_fs0 = va_arg(args, f64);
            if ((temp_fs0 > 1.0f) || (temp_fs0 < 0.0f)) {
                _uvDebugPrintf("uvEnvProps: FOGFACT out of range [0,1] %f\n", temp_fs0);
            } else {
                uvGfxSetFogFactor(temp_fs0);
                if (temp_fs0 == 0.0f) {
                    temp_s1->unk1C = 0;
                } else {
                    temp_s1->unk1C = 1;
                }
                temp_s1->unk14 = (f32)(temp_fs0 * 1000.0f);
                temp_s1->unk18 = 1000.0f;
            }
            break;
        case 4:
            temp_s1->unk8 = va_arg(args, s32);
            temp_s1->unk9 = va_arg(args, s32);
            temp_s1->unkA = va_arg(args, s32);
            temp_s1->unkB = va_arg(args, s32);
            break;
        case 1:
            temp_s1->fogR = va_arg(args, s32);
            temp_s1->fogG = va_arg(args, s32);
            temp_s1->fogB = va_arg(args, s32);
            temp_s1->fogA = va_arg(args, s32);
            break;
        case 2:
            temp_s1->screenR = va_arg(args, s32);
            temp_s1->screenG = va_arg(args, s32);
            temp_s1->screenB = va_arg(args, s32);
            temp_s1->screenA = va_arg(args, s32);
            break;
        default:
            _uvDebugPrintf("uvEnvProps: unknown property %d\n", property);
            break;
        }
    }
}

void uvEnvProps2(s32 arg0, ...) {
    f32 var_fv1;
    s32 property;
    uvGfxUnkStructEnv* temp_s1;
    va_list args;

    temp_s1 = gGfxUnkPtrs->unk44[arg0];
    va_start(args, arg0);
    if (temp_s1 == NULL) {
        _uvDebugPrintf("uvEnvProps: env %d not in level\n", arg0);
        return;
    }

    while (TRUE) {
        property = va_arg(args, s32);
        switch (property) {
        case 0:
            return;
        case 3:
            if (temp_s1->unk18 != 0.0f) {
                var_fv1 = temp_s1->unk14 / temp_s1->unk18;
            } else {
                var_fv1 = 0.0f;
            }
            *va_arg(args, f32*) = var_fv1;
            break;
        case 4:
            *va_arg(args, u8*) = temp_s1->unk8;
            *va_arg(args, u8*) = temp_s1->unk9;
            *va_arg(args, u8*) = temp_s1->unkA;
            *va_arg(args, u8*) = temp_s1->unkB;
            break;
        case 1:
            *va_arg(args, u8*) = temp_s1->fogR;
            *va_arg(args, u8*) = temp_s1->fogG;
            *va_arg(args, u8*) = temp_s1->fogB;
            *va_arg(args, u8*) = temp_s1->fogA;
            break;
        case 2:
            //! @bug All values set to the red value?
            *va_arg(args, u8*) = temp_s1->screenR;
            *va_arg(args, u8*) = temp_s1->screenR;
            *va_arg(args, u8*) = temp_s1->screenR;
            *va_arg(args, u8*) = temp_s1->screenR;
            break;
        default:
            _uvDebugPrintf("uvEnvProps: unknown property %d\n", property);
            break;
        }
    }
}

void uvEnvFunc(s32 envId, s32 flag, void (*arg2)(void)) {
    uvGfxUnkStructEnv* temp_v0;

    temp_v0 = gGfxUnkPtrs->unk44[envId];
    if (temp_v0 == NULL) {
        _uvDebugPrintf("uvEnvFunc: environment %d not in level\n", envId);
        return;
    }
    if (flag == 0) {
        temp_v0->unk38 = arg2;
    } else {
        _uvDebugPrintf("uvEnvFunc: unknown what flag %d\n", flag);
    }
    uvMat4CopyF2L(&D_80269F10, &D_80248DE0);
}

void func_80218700(void) {
    uvMat4CopyF2L(&D_80269F10, &D_80248DE0);
}

void _uvEnvDraw(s32 arg0, s32 arg1) {
    uvGfxUnkStruct8* temp_v1;
    f32 var_fs1;
    s32 temp_a0_2;
    u8 temp_s1;
    uvGfxUnkStruct10* temp_s2;
    uvGfxUnkStructEnv* temp_s7;
    u32 i;
    u32 j;
    uvGfxUnkStructModel* temp_a0;
    UnkStruct_80204D94* var_v0;

    if (arg1 == 0xFFFF) {
        return;
    }

    temp_s7 = gGfxUnkPtrs->unk44[arg1];
    if (temp_s7 == NULL) {
        uvGfxClearScreen(0, 0, 0, 255);
        return;
    }
    if (temp_s7->unk1C != 0) {
        var_fs1 = temp_s7->unk14 / temp_s7->unk18;
    } else {
        var_fs1 = 0.0f;
    }
    uvGfxSetFogFactor(var_fs1);

    if (temp_s7->unk2E != 0) {
        uvGfxClearScreen(temp_s7->screenR, temp_s7->screenG, temp_s7->screenB, temp_s7->screenA);
    }

    var_v0 = &D_80261730[arg0];
    for (i = 0; i < temp_s7->unk34; i++) {
        temp_a0 = gGfxUnkPtrs->unkC8[temp_s7->unk30[i].modelId];
        if (temp_a0 == NULL) {
            _uvDebugPrintf("_uvEnvDraw: model %d not in level\n", temp_s7->unk30[i].modelId);
            return;
        }
        temp_s1 = temp_s7->unk30[i].flag;
        temp_v1 = temp_a0->unk8;
        temp_s2 = temp_v1->unk0;

        if (temp_s1 & 8) {
            D_80248DE0.m[3][0] = var_v0->unk110.m[3][0];
            D_80248DE0.m[3][1] = var_v0->unk110.m[3][1];
        } else {
            D_80248DE0.m[3][0] = D_80248DE0.m[3][1] = 0.0f;
        }

        gDPSetFogColor(gGfxDisplayListHead++, temp_s7->fogR, temp_s7->fogG, temp_s7->fogB, 255);
        if (temp_s1 & 4) {
            uvGfxSetFogFactor(var_fs1);
        } else {
            uvGfxSetFogFactor(0.0f);
        }

        if (temp_s1 & 2) {
            uvGfxMtxProj(var_v0->unkD0);
            uvGfxMtxView(var_v0->unk150);
        }
        uvGfx_802236CC(&D_80248DE0);

        for (j = 0; j < temp_s2->unk4; j++) {
            temp_a0_2 = temp_s2->unk0[j].unk0;
            if (!(temp_s1 & 1)) {
                temp_s2->unk0[j].unk0 &= ~0x200000;
            }
            uvGfxStateDraw(&temp_s2->unk0[j]);
            temp_s2->unk0[j].unk0 = temp_a0_2;
        }
        if (temp_s1 & 2) {
            uvGfxMtxProj(var_v0->unk50);
            uvGfxMtxView(D_80269F10);
        }
        uvGfxMtxViewPop();
    }

    uvGfxSetFogFactor(var_fs1);
    if (temp_s7->unk38 != NULL) {
        temp_s7->unk38();
    }
}
