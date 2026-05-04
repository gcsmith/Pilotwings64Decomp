#include "common.h"
#include <libc/stdarg.h>
#include <uv_graphics.h>
#include <uv_environment.h>

Mtx D_80269F10;

STATIC_DATA Mtx4F D_80248DE0 = {
    1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1,
};

void uvEnvProps(s32 envId, ...) {
    f32 fogfact;
    s32 property;
    ParsedUVEN* uven;
    va_list args;

    uven = gGfxUnkPtrs->environments[envId];
    va_start(args, envId);
    if (uven == NULL) {
        _uvDebugPrintf("uvEnvProps: env %d not in level\n", envId);
        return;
    }

    while (TRUE) {
        property = va_arg(args, s32);
        switch (property) {
        case ENV_PROPID_END:
            return;
        case ENV_PROPID_FOG_FACTOR:
            fogfact = va_arg(args, f64);
            if ((fogfact > 1.0f) || (fogfact < 0.0f)) {
                _uvDebugPrintf("uvEnvProps: FOGFACT out of range [0,1] %f\n", fogfact);
            } else {
                uvGfxSetFogFactor(fogfact);
                if (fogfact == 0.0f) {
                    uven->fogEnabled = FALSE;
                } else {
                    uven->fogEnabled = TRUE;
                }
                uven->fogMin = (f32)(fogfact * 1000.0f);
                uven->fogMax = 1000.0f;
            }
            break;
        case ENV_PROPID_UNUSED:
            uven->unusedR = va_arg(args, s32);
            uven->unusedG = va_arg(args, s32);
            uven->unusedB = va_arg(args, s32);
            uven->unusedA = va_arg(args, s32);
            break;
        case ENV_PROPID_FOG_COLOR:
            uven->fogR = va_arg(args, s32);
            uven->fogG = va_arg(args, s32);
            uven->fogB = va_arg(args, s32);
            uven->fogA = va_arg(args, s32);
            break;
        case ENV_PROPID_SCREEN_COLOR:
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

void uvEnvGetProps(s32 envId, ...) {
    f32 fogfact;
    s32 property;
    ParsedUVEN* uven;
    va_list args;

    uven = gGfxUnkPtrs->environments[envId];
    va_start(args, envId);
    if (uven == NULL) {
        _uvDebugPrintf("uvEnvProps: env %d not in level\n", envId);
        return;
    }

    while (TRUE) {
        property = va_arg(args, s32);
        switch (property) {
        case ENV_PROPID_END:
            return;
        case ENV_PROPID_FOG_FACTOR:
            if (uven->fogMax != 0.0f) {
                fogfact = uven->fogMin / uven->fogMax;
            } else {
                fogfact = 0.0f;
            }
            *va_arg(args, f32*) = fogfact;
            break;
        case ENV_PROPID_UNUSED:
            *va_arg(args, u8*) = uven->unusedR;
            *va_arg(args, u8*) = uven->unusedG;
            *va_arg(args, u8*) = uven->unusedB;
            *va_arg(args, u8*) = uven->unusedA;
            break;
        case ENV_PROPID_FOG_COLOR:
            *va_arg(args, u8*) = uven->fogR;
            *va_arg(args, u8*) = uven->fogG;
            *va_arg(args, u8*) = uven->fogB;
            *va_arg(args, u8*) = uven->fogA;
            break;
        case ENV_PROPID_SCREEN_COLOR:
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

void uvEnvFunc(s32 envId, s32 flag, s32 (*callback)(void)) {
    ParsedUVEN* uven;

    uven = gGfxUnkPtrs->environments[envId];
    if (uven == NULL) {
        _uvDebugPrintf("uvEnvFunc: environment %d not in level\n", envId);
        return;
    }
    if (flag == 0) {
        uven->callback = callback;
    } else {
        _uvDebugPrintf("uvEnvFunc: unknown what flag %d\n", flag);
    }
    uvMat4CopyF2L(&D_80269F10, &D_80248DE0);
}

void uvEnvResetModelView(void) {
    uvMat4CopyF2L(&D_80269F10, &D_80248DE0);
}

void _uvEnvDraw(s32 arg0, s32 arg1) {
    uvModelLOD* currLod;
    f32 fogfact;
    s32 temp_a0_2;
    u8 modelFlag;
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
        uvGfxClearScreen(0x00, 0x00, 0x00, 0xFF);
        return;
    }
    if (uven->fogEnabled != FALSE) {
        fogfact = uven->fogMin / uven->fogMax;
    } else {
        fogfact = 0.0f;
    }
    uvGfxSetFogFactor(fogfact);

    if (uven->clearEnabled != FALSE) {
        uvGfxClearScreen(uven->screenR, uven->screenG, uven->screenB, uven->screenA);
    }

    var_v0 = &D_80261730[arg0];
    for (i = 0; i < uven->modelCount; i++) {
        uvmd = gGfxUnkPtrs->models[uven->modelTable[i].modelId];
        if (uvmd == NULL) {
            _uvDebugPrintf("_uvEnvDraw: model %d not in level\n", uven->modelTable[i].modelId);
            return;
        }
        modelFlag = uven->modelTable[i].flag;
        currLod = uvmd->lodTable;
        currPart = currLod->partTable;

        if (modelFlag & 8) {
            D_80248DE0.m[3][0] = var_v0->unk110.m[3][0];
            D_80248DE0.m[3][1] = var_v0->unk110.m[3][1];
        } else {
            D_80248DE0.m[3][0] = D_80248DE0.m[3][1] = 0.0f;
        }

        gDPSetFogColor(gGfxDisplayListHead++, uven->fogR, uven->fogG, uven->fogB, 255);
        if (modelFlag & 4) {
            uvGfxSetFogFactor(fogfact);
        } else {
            uvGfxSetFogFactor(0.0f);
        }

        if (modelFlag & 2) {
            uvGfxMtxProj(var_v0->unkD0);
            uvGfxMtxView(var_v0->unk150);
        }
        uvGfx_802236CC(&D_80248DE0);

        for (j = 0; j < currPart->stateCount; j++) {
            temp_a0_2 = currPart->stateTable[j].state;
            if (!(modelFlag & 1)) {
                currPart->stateTable[j].state &= ~0x200000;
            }
            uvGfxStateDraw(&currPart->stateTable[j]);
            currPart->stateTable[j].state = temp_a0_2;
        }
        if (modelFlag & 2) {
            uvGfxMtxProj(var_v0->unk50);
            uvGfxMtxView(D_80269F10);
        }
        uvGfxMtxViewPop();
    }

    uvGfxSetFogFactor(fogfact);
    if (uven->callback != NULL) {
        uven->callback();
    }
}
