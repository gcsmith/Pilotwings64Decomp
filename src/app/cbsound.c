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
void func_802DA1A8(CannonballData* cbData);
void func_802DA228(CannonballData* cbData);
void func_802DA23C(CannonballData* cbData);
void func_802DA354(CannonballData* cbData);
void func_802DA474(CannonballData* cbData);

void cbSoundInit(CannonballData* cbData) {
    s32 pad;
    s32 sfxId;
    f32 pitch;

    cbData->unk2A8 = 1.0f;
    cbData->unk2B8 = 0.0f;
    cbData->unk2A4 = 75.0f;
    D_80359BE8.count = 4;
    D_80359BE8.unk4[0].x = 0.f;
    D_80359BE8.unk4[0].y = 0.0f;
    D_80359BE8.unk4[1].x = 0.01f;
    D_80359BE8.unk4[1].y = 0.4f;
    D_80359BE8.unk4[2].x = 9.0f;
    D_80359BE8.unk4[2].y = 0.8f;
    D_80359BE8.unk4[3].x = 10.0f;
    D_80359BE8.unk4[3].y = 1.0f;
    // stereo wind sfx
    cbData->unk2B0 = sndMakeDev(SFX_MOVEMENT_WIND);
    cbData->unk2B1 = sndMakeDev(SFX_MOVEMENT_WIND);
    cbData->unk2B4 = uvEmitterLookup();
    sndGetPilotScream(&sfxId, &pitch);
    uvEmitterFromModel(cbData->unk2B4, sfxId);
    uvEmitterSetVol(cbData->unk2B4, 1.0f);
    uvEmitterSetPitch(cbData->unk2B4, pitch);
    // clang-format off
    uvEmitterProps(cbData->unk2B4,
        EMITTER_PROP_NEAR(0.0f),
        EMITTER_PROP_FAR(5000.0f),
        EMITTER_PROP_ATTR(EMITTER_ATTR_ONESHOT),
        EMITTER_PROP_END
    );
    // clang-format on
    cbData->unk2B5 = sndMakeDev(SFX_UI_MAP_MOVE);
    D_80359BE0.cb = func_802D9E68;
    D_80359BE0.arg = cbData;
    cbData->unk2AC = ~0x3F;
    uvEventMaxCb(D_80359BE0, 1, 0xD, 0x12, 0x13, 0x10, 0xC, 0x16, 0x19, 0x24);
}

void func_802D9E68(s32 eventType, void* arg1, s32 eventData) {
    f32 var_fv1;
    f32 var_fv0;
    f32 var_fa0;
    CannonballData* cbData = (CannonballData*)arg1;

    if (eventData != 0) {
        _uvAssertMsg("eventData == 0", "cbsound.c", 0x67);
    }
    switch (eventType) {
    case 13:
    case 25:
        func_802DA474(cbData);
        break;
    case 12:
        func_802DA1A8(cbData);
        break;
    case 19:
        func_802DA228(cbData);
        break;
    case 18:
        func_802DA1A8(cbData);
        break;
    case 22:
        func_802DA23C(cbData);
        break;
    case 16:
        break;
    case 1:
        if (cbData->unk2AC & 1) {
            break;
        }
        func_802DA354(cbData);
        if (cbData->unkD4 != 0) {
            var_fa0 = uvVec3Len(&cbData->unk214) * 0.004f;
            if (var_fa0 < 0.0f) {
                var_fa0 = 0.0f;
            } else if (var_fa0 > 1.0f) {
                var_fa0 = 1.0f;
            }

            var_fv1 = (demoRandF() * 0.3f) + 0.4f + (1.3f * var_fa0);
            var_fv0 = (demoRandF() * 0.2f) + (0.8f * var_fa0);
            func_8033F904(cbData->unk2B0, var_fv1, var_fv0, -0.5f);
            var_fv1 = (demoRandF() * 0.3f) + 0.4f + (1.3f * var_fa0);
            var_fv0 = (demoRandF() * 0.2f) + (0.8f * var_fa0);
            func_8033F904(cbData->unk2B1, var_fv1, var_fv0, 0.5f);
        } else {
            func_8033F904(cbData->unk2B0, 1.0f, 0.0f, 0.5f);
            func_8033F904(cbData->unk2B1, 1.0f, 0.0f, 0.5f);
        }
        if (cbData->unkD4 == 2) {
            uvEmitterRelease(cbData->unk2B4);
        }
        if (cbData->unkD4 == 0) {
            var_fv1 = (((cbData->zAxis - cbData->unkA8) + (cbData->xAxis - cbData->unkAC)) * 0.6f) + 0.6f;
            if (var_fv1 < 0.0f) {
                var_fv1 *= -1.0f;
            }

            if ((cbData->zAxis != cbData->unkA8) || (cbData->xAxis != cbData->unkAC)) {
                var_fv0 = 0.8f;
            } else {
                var_fv0 = 0.0f;
            }

            func_8033F904(cbData->unk2B5, var_fv1, var_fv0, 0.5f);
        } else {
            func_8033F904(cbData->unk2B5, 0.6f, 0.0f, 0.5f);
        }
        cbData->unkA8 = cbData->zAxis;
        cbData->unkAC = cbData->xAxis;
        break;
    default:
        _uvDebugPrintf("Got unknown event type %d\n", eventType);
        break;
    }
}

void func_802DA1A8(CannonballData* cbData) {
    cbData->unk2AC |= 1;
    func_8033F904(cbData->unk2B0, 1.0f, 0.0f, 0.0f);
    func_8033F904(cbData->unk2B1, 1.0f, 0.0f, 0.0f);
    func_8033F904(cbData->unk2B5, 1.0f, 0.0f, 0.0f);
}

void func_802DA228(CannonballData* cbData) {
    cbData->unk2AC &= ~1;
}

void func_802DA23C(CannonballData* cbData) {
    Unk80362690_Unk0* sp24;

    sp24 = &D_80362690->unkC[D_80362690->unk9C];
    if ((cbData->unkD4 == 2) && (cbData->unkD5 != 2)) {
        if (!(cbData->unk2AC & 2)) {
            sndPlaySfx(0x36);
            if ((cbData->unk11C != 0) && !(cbData->unk2AC & 2)) {
                sndPlaySfx(SFX_WATER_SPLASH);
            }
            cbData->unk2AC |= 2;
            func_8033F748(0x12);
            func_8033F964(0);
            func_8033FCD0(sp24->veh);
            func_802DA1A8(cbData);
        }
    } else if ((cbData->unkD4 == 2) && (cbData->unkD5 == 2)) {
        if (!(cbData->unk2AC & 2)) {
            func_802DA1A8(cbData);
        }
    } else {
        cbData->unk2AC = ~0x3F;
    }
}

void func_802DA354(CannonballData* cbData) {
    switch (cbData->unkD4) {
    case 0:
        if (cbData->unk2A8 < D_8034F850) {
            cbData->unk2A8 += 0.75f;
            if (cbData->unk2A4 < 95.0f) {
                cbData->unk2A4 += 1.0f;
            } else if (cbData->unk2A4 > 96.0f) {
                cbData->unk2A4 = 75.0f;
            }
        }
        break;
    case 1:
        cbData->unk2A8 = 0.0f;
        cbData->unk2A4 = 165.0f;
        break;
    case 2:
        cbData->unk2A8 = 0.0f;
        cbData->unk2A4 = 75.0f;
        break;
    default:
        _uvDebugPrintf("unknown cball state\n");
        break;
    }
    uvaSeqSetTempo(cbData->unk2A4);
}

void func_802DA474(CannonballData* cbData) {
    cbData->unk2B0 = func_8033F8CC(cbData->unk2B0);
    cbData->unk2B1 = func_8033F8CC(cbData->unk2B1);
    cbData->unk2B4 = func_8033F8CC(cbData->unk2B4);
    cbData->unk2B5 = func_8033F8CC(cbData->unk2B5);
    uvEventRemoveCb(D_80359BE0, 1, 0xD, 0x12, 0x13, 0x10, 0xC, 0x16, 0x19, 0x24);
}

