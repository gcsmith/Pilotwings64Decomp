#include "common.h"
#include <libc/stdarg.h>
#include <uv_graphics.h>
#include <uv_environment.h>

Mtx D_80269F10;

static Mtx4F D_80248DE0 = {
    1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1,
};

void uvEnvProps(s32 arg0, ...) {
    f32 temp_fs0;
    s32 property;
    ParsedUVEN* uven;
    va_list args;

    uven = gGfxUnkPtrs->environments[arg0];
    va_start(args, arg0);
    if (uven == NULL) {
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
                    uven->unk1C = 0;
                } else {
                    uven->unk1C = 1;
                }
                uven->unk14 = (f32)(temp_fs0 * 1000.0f);
                uven->unk18 = 1000.0f;
            }
            break;
        case 4:
            uven->unk8 = va_arg(args, s32);
            uven->unk9 = va_arg(args, s32);
            uven->unkA = va_arg(args, s32);
            uven->unkB = va_arg(args, s32);
            break;
        case 1:
            uven->fogR = va_arg(args, s32);
            uven->fogG = va_arg(args, s32);
            uven->fogB = va_arg(args, s32);
            uven->fogA = va_arg(args, s32);
            break;
        case 2:
            uven->screenR = va_arg(args, s32);
            uven->screenG = va_arg(args, s32);
            uven->screenB = va_arg(args, s32);
            uven->screenA = va_arg(args, s32);
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
    ParsedUVEN* uven;
    va_list args;

    uven = gGfxUnkPtrs->environments[arg0];
    va_start(args, arg0);
    if (uven == NULL) {
        _uvDebugPrintf("uvEnvProps: env %d not in level\n", arg0);
        return;
    }

    while (TRUE) {
        property = va_arg(args, s32);
        switch (property) {
        case 0:
            return;
        case 3:
            if (uven->unk18 != 0.0f) {
                var_fv1 = uven->unk14 / uven->unk18;
            } else {
                var_fv1 = 0.0f;
            }
            *va_arg(args, f32*) = var_fv1;
            break;
        case 4:
            *va_arg(args, u8*) = uven->unk8;
            *va_arg(args, u8*) = uven->unk9;
            *va_arg(args, u8*) = uven->unkA;
            *va_arg(args, u8*) = uven->unkB;
            break;
        case 1:
            *va_arg(args, u8*) = uven->fogR;
            *va_arg(args, u8*) = uven->fogG;
            *va_arg(args, u8*) = uven->fogB;
            *va_arg(args, u8*) = uven->fogA;
            break;
        case 2:
            //! @bug All values set to the red value?
            *va_arg(args, u8*) = uven->screenR;
            *va_arg(args, u8*) = uven->screenR;
            *va_arg(args, u8*) = uven->screenR;
            *va_arg(args, u8*) = uven->screenR;
            break;
        default:
            _uvDebugPrintf("uvEnvProps: unknown property %d\n", property);
            break;
        }
    }
}

void uvEnvFunc(s32 envId, s32 flag, void (*arg2)(void)) {
    ParsedUVEN* uven;

    uven = gGfxUnkPtrs->environments[envId];
    if (uven == NULL) {
        _uvDebugPrintf("uvEnvFunc: environment %d not in level\n", envId);
        return;
    }
    if (flag == 0) {
        uven->unk38 = arg2;
    } else {
        _uvDebugPrintf("uvEnvFunc: unknown what flag %d\n", flag);
    }
    uvMat4CopyF2L(&D_80269F10, &D_80248DE0);
}

void func_80218700(void) {
    uvMat4CopyF2L(&D_80269F10, &D_80248DE0);
}

void _uvEnvDraw(s32 arg0, s32 arg1) {
    uvModelLOD* currLod;
    f32 var_fs1;
    s32 temp_a0_2;
    u8 temp_s1;
    uvModelPart* currPart;
    ParsedUVEN* uven;
    u32 i;
    u32 j;
    ParsedUVMD* uvmd;
    UnkStruct_80204D94* var_v0;

    if (arg1 == 0xFFFF) {
        return;
    }

    uven = gGfxUnkPtrs->environments[arg1];
    if (uven == NULL) {
        uvGfxClearScreen(0, 0, 0, 255);
        return;
    }
    if (uven->unk1C != 0) {
        var_fs1 = uven->unk14 / uven->unk18;
    } else {
        var_fs1 = 0.0f;
    }
    uvGfxSetFogFactor(var_fs1);

    if (uven->unk2E != 0) {
        uvGfxClearScreen(uven->screenR, uven->screenG, uven->screenB, uven->screenA);
    }

    var_v0 = &D_80261730[arg0];
    for (i = 0; i < uven->count; i++) {
        uvmd = gGfxUnkPtrs->models[uven->unk30[i].modelId];
        if (uvmd == NULL) {
            _uvDebugPrintf("_uvEnvDraw: model %d not in level\n", uven->unk30[i].modelId);
            return;
        }
        temp_s1 = uven->unk30[i].flag;
        currLod = uvmd->lodTable;
        currPart = currLod->partTable;

        if (temp_s1 & 8) {
            D_80248DE0.m[3][0] = var_v0->unk110.m[3][0];
            D_80248DE0.m[3][1] = var_v0->unk110.m[3][1];
        } else {
            D_80248DE0.m[3][0] = D_80248DE0.m[3][1] = 0.0f;
        }

        gDPSetFogColor(gGfxDisplayListHead++, uven->fogR, uven->fogG, uven->fogB, 255);
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

        for (j = 0; j < currPart->stateCount; j++) {
            temp_a0_2 = currPart->stateTable[j].state;
            if (!(temp_s1 & 1)) {
                currPart->stateTable[j].state &= ~0x200000;
            }
            uvGfxStateDraw(&currPart->stateTable[j]);
            currPart->stateTable[j].state = temp_a0_2;
        }
        if (temp_s1 & 2) {
            uvGfxMtxProj(var_v0->unk50);
            uvGfxMtxView(D_80269F10);
        }
        uvGfxMtxViewPop();
    }

    uvGfxSetFogFactor(var_fs1);
    if (uven->unk38 != NULL) {
        uven->unk38();
    }
}
