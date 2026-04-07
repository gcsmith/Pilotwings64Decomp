#include "common.h"
#include "cbsound.h"
#include <uv_audio.h>
#include <uv_event.h>
#include "app/demo.h"
#include "app/snd.h"
#include "app/code_9A960.h"

EventCallbackInfo D_80359BE0;
Unk803599D0 D_80359BE8;

void func_802D9E68(s32 eventType, void* arg1, s32 eventData);
void func_802DA1A8(CannonballData*);
void func_802DA228(CannonballData*);
void func_802DA23C(CannonballData*);
void func_802DA354(CannonballData*);
void func_802DA474(CannonballData*);

void cbSoundInit(CannonballData* arg0) {
    s32 pad;
    s32 sp48;
    f32 sp44;

    arg0->unk2A8 = 1.0f;
    arg0->unk2B8 = 0.0f;
    arg0->unk2A4 = 75.0f;
    D_80359BE8.count = 4;
    D_80359BE8.unk4[0].x = 0.f;
    D_80359BE8.unk4[0].y = 0.0f;
    D_80359BE8.unk4[1].x = 0.01f;
    D_80359BE8.unk4[1].y = 0.4f;
    D_80359BE8.unk4[2].x = 9.0f;
    D_80359BE8.unk4[2].y = 0.8f;
    D_80359BE8.unk4[3].x = 10.0f;
    D_80359BE8.unk4[3].y = 1.0f;
    arg0->unk2B0 = sndMakeDev(0x13);
    arg0->unk2B1 = sndMakeDev(0x13);
    arg0->unk2B4 = uvEmitterLookup();
    sndGetPilot(&sp48, &sp44);
    uvEmitterFromModel(arg0->unk2B4, sp48);
    uvEmitterSetUnk70(arg0->unk2B4, 1.0f);
    uvEmitterSetUnk74(arg0->unk2B4, sp44);
    uvEmitterProp(arg0->unk2B4, 1, 0.0f, 2, 5000.0f, 5, 0x10, 0);
    arg0->unk2B5 = sndMakeDev(0x4C);
    D_80359BE0.cb = func_802D9E68;
    D_80359BE0.arg = arg0;
    arg0->unk2AC = ~0x3F;
    uvEventMaxCb(D_80359BE0, 1, 0xD, 0x12, 0x13, 0x10, 0xC, 0x16, 0x19, 0x24);
}

void func_802D9E68(s32 eventType, void* arg1, s32 eventData) {
    f32 var_fv1;
    f32 var_fv0;
    f32 var_fa0;
    CannonballData* cannonballData = (CannonballData*)arg1;

    if (eventData != 0) {
        _uvAssertMsg("eventData == 0", "cbsound.c", 0x67);
    }
    switch (eventType) {
    case 13:
    case 25:
        func_802DA474(cannonballData);
        break;
    case 12:
        func_802DA1A8(cannonballData);
        break;
    case 19:
        func_802DA228(cannonballData);
        break;
    case 18:
        func_802DA1A8(cannonballData);
        break;
    case 22:
        func_802DA23C(cannonballData);
        break;
    case 16:
        break;
    case 1:
        if (cannonballData->unk2AC & 1) {
            break;
        }
        func_802DA354(cannonballData);
        if (cannonballData->unkD4 != 0) {
            var_fa0 = uvVec3Len(&cannonballData->unk214) * 0.004f;
            if (var_fa0 < 0.0f) {
                var_fa0 = 0.0f;
            } else if (var_fa0 > 1.0f) {
                var_fa0 = 1.0f;
            }

            var_fv1 = (demoRandF() * 0.3f) + 0.4f + (1.3f * var_fa0);
            var_fv0 = (demoRandF() * 0.2f) + (0.8f * var_fa0);
            func_8033F904(cannonballData->unk2B0, var_fv1, var_fv0, -0.5f);
            var_fv1 = (demoRandF() * 0.3f) + 0.4f + (1.3f * var_fa0);
            var_fv0 = (demoRandF() * 0.2f) + (0.8f * var_fa0);
            func_8033F904(cannonballData->unk2B1, var_fv1, var_fv0, 0.5f);
        } else {
            func_8033F904(cannonballData->unk2B0, 1.0f, 0.0f, 0.5f);
            func_8033F904(cannonballData->unk2B1, 1.0f, 0.0f, 0.5f);
        }
        if (cannonballData->unkD4 == 2) {
            uvEmitterRelease(cannonballData->unk2B4);
        }
        if (cannonballData->unkD4 == 0) {
            var_fv1 = (((cannonballData->zAxis - cannonballData->unkA8) + (cannonballData->xAxis - cannonballData->unkAC)) * 0.6f) + 0.6f;
            if (var_fv1 < 0.0f) {
                var_fv1 *= -1.0f;
            }

            if ((cannonballData->zAxis != cannonballData->unkA8) || (cannonballData->xAxis != cannonballData->unkAC)) {
                var_fv0 = 0.8f;
            } else {
                var_fv0 = 0.0f;
            }

            func_8033F904(cannonballData->unk2B5, var_fv1, var_fv0, 0.5f);
        } else {
            func_8033F904(cannonballData->unk2B5, 0.6f, 0.0f, 0.5f);
        }
        cannonballData->unkA8 = cannonballData->zAxis;
        cannonballData->unkAC = cannonballData->xAxis;
        break;
    default:
        _uvDebugPrintf("Got unknown event type %d\n", eventType);
        break;
    }
}

void func_802DA1A8(CannonballData* arg0) {
    arg0->unk2AC |= 1;
    func_8033F904(arg0->unk2B0, 1.0f, 0.0f, 0.0f);
    func_8033F904(arg0->unk2B1, 1.0f, 0.0f, 0.0f);
    func_8033F904(arg0->unk2B5, 1.0f, 0.0f, 0.0f);
}

void func_802DA228(CannonballData* arg0) {
    arg0->unk2AC &= ~1;
}

void func_802DA23C(CannonballData* arg0) {
    Unk80362690_Unk0* sp24;

    sp24 = &D_80362690->unkC[D_80362690->unk9C];
    if ((arg0->unkD4 == 2) && (arg0->unkD5 != 2)) {
        if (!(arg0->unk2AC & 2)) {
            sndPlaySfx(0x36);
            if ((arg0->unk11C != 0) && !(arg0->unk2AC & 2)) {
                sndPlaySfx(0x1A);
            }
            arg0->unk2AC |= 2;
            func_8033F748(0x12);
            func_8033F964(0);
            func_8033FCD0(sp24->veh);
            func_802DA1A8(arg0);
        }
    } else if ((arg0->unkD4 == 2) && (arg0->unkD5 == 2)) {
        if (!(arg0->unk2AC & 2)) {
            func_802DA1A8(arg0);
        }
    } else {
        arg0->unk2AC = ~0x3F;
    }
}

void func_802DA354(CannonballData* arg0) {
    switch (arg0->unkD4) {
    case 0:
        if (arg0->unk2A8 < D_8034F850) {
            arg0->unk2A8 += 0.75f;
            if (arg0->unk2A4 < 95.0f) {
                arg0->unk2A4 += 1.0f;
            } else if (arg0->unk2A4 > 96.0f) {
                arg0->unk2A4 = 75.0f;
            }
        }
        break;
    case 1:
        arg0->unk2A8 = 0.0f;
        arg0->unk2A4 = 165.0f;
        break;
    case 2:
        arg0->unk2A8 = 0.0f;
        arg0->unk2A4 = 75.0f;
        break;
    default:
        _uvDebugPrintf("unknown cball state\n");
        break;
    }
    uvaSeqSetTempo(arg0->unk2A4);
}

void func_802DA474(CannonballData* arg0) {
    arg0->unk2B0 = func_8033F8CC(arg0->unk2B0);
    arg0->unk2B1 = func_8033F8CC(arg0->unk2B1);
    arg0->unk2B4 = func_8033F8CC(arg0->unk2B4);
    arg0->unk2B5 = func_8033F8CC(arg0->unk2B5);
    uvEventRemoveCb(D_80359BE0, 1, 0xD, 0x12, 0x13, 0x10, 0xC, 0x16, 0x19, 0x24);
}
