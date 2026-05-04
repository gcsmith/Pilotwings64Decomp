#include "common.h"
#include <uv_audio.h>
#include "kernel/code_1050.h"
#include "demo.h"
#include "hud.h"
#include "rocket_belt.h"
#include "snd.h"

STATIC_DATA EventCallbackInfo sRbSoundEventCbInfo;
STATIC_DATA Unk803599D0 sRbSound_80371898;

STATIC_FUNC void rbSoundEventHandler(s32, void*, s32);
STATIC_FUNC void rbSoundEvent12_22(RocketBeltData* rbData);
STATIC_FUNC void rbSoundEvent12_18(RocketBeltData* rbData);
STATIC_FUNC void rbSoundEvent19(RocketBeltData* rbData);
STATIC_FUNC void rbSoundSubEvent(RocketBeltData* rbData);
STATIC_FUNC void rbSoundEvent13(RocketBeltData* rbData);

void rbSoundInit(RocketBeltData* rbData) {
    rbData->unk390 = 0.0f;
    rbData->unk394 = 0.0f;
    rbData->unk398 = 0.0f;
    sRbSound_80371898.count = 4;
    sRbSound_80371898.unk4[0].x = 00.0f, sRbSound_80371898.unk4[0].y = 0.0f;
    sRbSound_80371898.unk4[1].x = 02.0f, sRbSound_80371898.unk4[1].y = 0.4f;
    sRbSound_80371898.unk4[2].x = 09.0f, sRbSound_80371898.unk4[2].y = 0.8f;
    sRbSound_80371898.unk4[3].x = 10.0f, sRbSound_80371898.unk4[3].y = 1.0f;
    rbData->unk388 = sndMakeDev(SFX_RB_FLY_UP);
    rbData->unk389 = sndMakeDev(SFX_RB_FLY_DOWN);
    rbData->unk38A = sndMakeDev(SFX_MOVEMENT_WIND); // two emitters for stereo
    rbData->unk38B = sndMakeDev(SFX_MOVEMENT_WIND);
    rbData->unk38C = sndMakeDev(SFX_RB_ENGINE);
    uvEmitterProps(rbData->unk38C, EMITTER_PROP_ATTR(EMITTER_ATTR_4), EMITTER_PROP_END);
    uvEmitterSetPri(rbData->unk38C, 0x7FFF);
    sRbSoundEventCbInfo.cb = rbSoundEventHandler;
    sRbSoundEventCbInfo.arg = rbData;
    rbData->unk384 = ~0x3F;
    uvEventMaxCb(sRbSoundEventCbInfo, 1, 13, 18, 19, 16, 12, 22, 0x24);
}

STATIC_FUNC void rbSoundEventHandler(s32 event, void* userData, s32 eventData) {
    f32 sp4C;
    f32 sp48;
    f32 var_fa1;
    f32 var_fv0;
    f32 temp_ft1;
    RocketBeltData* rbData = userData;

    if (eventData != 0) {
        _uvAssertMsg("eventData == 0", "rpsound.c", 0x6F);
    }
    switch (event) {
    case 16:
        break;
    case 13:
        rbSoundEvent13(rbData);
        break;
    case 12:
        rbSoundEvent12_22(rbData);
        rbSoundEvent12_18(rbData);
        break;
    case 19:
        rbSoundEvent19(rbData);
        break;
    case 18:
        rbSoundEvent12_18(rbData);
        break;
    case 22:
        rbSoundEvent12_22(rbData);
        break;
    case 1:
        if ((rbData->unk384 & 1)) {
            break;
        }
        sp48 = 0.0f;
        if ((rbData->unkEB != 0) && (hudGet_8031DA9C() == 0x17B) && (rbData->unk394 < D_8034F850)) {
            rbData->unk394 = D_8034F850 + 0.2f;
            sndPlaySfxVolPitchPan(0x6C, 0.8f, 0.707f, sp48);
        }
        if ((rbData->unkEC != 0) && (hudGet_8031DA9C() == 0x4A) && (rbData->unk398 < D_8034F850)) {
            rbData->unk398 = D_8034F850 + 0.2f;
            sndPlaySfxVolPitchPan(0x6C, 0.8f, 0.707f, sp48);
        }

        var_fa1 = ABS_NOEQ(rbData->unk244.y) * 0.03f;
        if (var_fa1 < 0.0f) {
            var_fa1 = 0.0f;
        } else if (var_fa1 > 1.0f) {
            var_fa1 = 1.0f;
        }
        temp_ft1 = demoRandF() - 0.5f;
        sp4C = (1.3f * var_fa1) + 0.4f + (temp_ft1 * 0.3f);
        var_fa1 = (0.03f * uvVec3Len(&rbData->unk244)) * (((demoRandF() * 0.4f) - 0.5f) + 1.0);
        if (var_fa1 < 0.0f) {
            var_fa1 = 0.0f;
        } else if (var_fa1 > 1.0f) {
            var_fa1 = 1.0f;
        }
        sp48 = 0.6f * var_fa1;
        func_8033F904(rbData->unk38A, sp4C, sp48, -0.5f);

        var_fa1 = ABS_NOEQ(rbData->unk244.y) * 0.03f;
        if (var_fa1 < 0.0f) {
            var_fa1 = 0.0f;
        } else if (var_fa1 > 1.0f) {
            var_fa1 = 1.0f;
        }
        temp_ft1 = demoRandF() - 0.5f;
        sp4C = (1.3f * var_fa1) + 0.4f + (temp_ft1 * 0.3f);
        var_fa1 = (0.03f * uvVec3Len(&rbData->unk244)) * (((demoRandF() * 0.4f) - 0.5f) + 1.0);
        if (var_fa1 < 0.0f) {
            var_fa1 = 0.0f;
        } else if (var_fa1 > 1.0f) {
            var_fa1 = 1.0f;
        }
        sp48 = 0.6f * var_fa1;
        func_8033F904(rbData->unk38B, sp4C, sp48, 0.5f);

        var_fa1 = rbData->unk1E8.z * 0.06f;
        if (var_fa1 < -1.0f) {
            var_fa1 = -1.0f;
        } else if (var_fa1 > 1.0f) {
            var_fa1 = 1.0f;
        }
        sp4C = (ABS_NOEQ(var_fa1) * 0.3f) + 1.0f;
        var_fa1 = ABS_NOEQ(rbData->unk1E8.z * 0.06f);
        if (var_fa1 < 0.0f) {
            var_fa1 = 0.0f;
        } else if (var_fa1 > 1.0f) {
            var_fa1 = 1.0f;
        }
        sp48 = 0.17f * var_fa1 * var_fa1;
        if (rbData->unk1E8.z < 0.0f) {
            func_8033F904(rbData->unk388, sp4C, 0.0f, 0.0f);
            func_8033F904(rbData->unk389, sp4C, sp48, 0.0f);
        } else {
            func_8033F904(rbData->unk388, sp4C, sp48, 0.0f);
            func_8033F904(rbData->unk389, sp4C, 0.0f, 0.0f);
        }
        if (rbData->unkF8 > 0.0f) {
            switch (rbData->unk81) {
            case 0:
                sp4C = 1.0f;
                sp48 = 0.0f;
                break;
            case 1:
                sp4C = 1.0f;
                sp48 = 1.0f;
                break;
            case 2:
                sp48 = 0.6f;
                sp4C = 1.0f;
                break;
            case 3:
                sp48 = 1.0f;
                sp4C = 0.6f;
                break;
            }
            var_fv0 = rbData->unk88 * 0.5f;
            if (var_fv0 < -1.0f) {
                var_fv0 = -1.0f;
            } else if (var_fv0 > 1.0f) {
                var_fv0 = 1.0f;
            }
            func_8033F904(rbData->unk38C, sp4C, sp48, var_fv0);
        } else {
            func_8033F904(rbData->unk38C, 1.0f, 0.0f, 0.0f);
        }
        break;
    default:
        _uvDebugPrintf("rpsound : got unknown event type %d\n", event);
        break;
    }
}

STATIC_FUNC void rbSoundEvent12_22(RocketBeltData* rbData) {
    Unk80362690_Unk0* sp34;
    s32 sfxId;
    f32 pitch;

    sp34 = &D_80362690->unkC[D_80362690->unk9C];
    if (rbData->unk90 == 3) {
        if ((rbData->unk384 & 0x2) == 0) {
            rbData->unk384 |= 0x2;
            sndPlaySfx(0x36);
            if ((rbData->unk384 & 0x10) == 0) {
                sndSetMusic(0xB);
                func_8033F964(0);
                func_8033FCD0(sp34->veh);
            }
            rbSoundEvent12_18(rbData);
        }
    } else {
        if (rbData->unk90 == 2) {
            if ((rbData->unk384 & 0x10) == 0) {
                rbData->unk384 |= 0x10;
                sndGetPilotScream(&sfxId, &pitch);
                sndPlaySfxVolPitchPan(sfxId, 1.0f, pitch, 0.0f);
                sndSetMusic(0xB);
                func_8033F964(0);
                func_8033FCD0(sp34->veh);
                rbSoundEvent12_18(rbData);
            }
        }
        if ((rbData->unk90 == 4) && (D_80362690->state != 6)) {
            if ((rbData->unk384 & 0x2) == 0 && (rbData->unk384 & 0x10) == 0) {
                if (rbData->unk64 != 0) {
                    sndSetMusic(9);
                } else {
                    sndSetMusic(0xA);
                }
                func_8033F964(0);
                func_8033FCD0(sp34->veh);
                rbSoundEvent12_18(rbData);
            }
        }
        if (rbData->unk92 != 0) {
            rbSoundSubEvent(rbData);
        } else if ((rbData->unk384 & 0x10) == 0) {
            rbData->unk384 = ~0x3F;
        }
    }
}

STATIC_FUNC void rbSoundEvent12_18(RocketBeltData* rbData) {
    rbData->unk384 |= 1;
    func_8033F904(rbData->unk38C, 1.0f, 0.0f, 0.0f);
    func_8033F904(rbData->unk388, 1.0f, 0.0f, 0.0f);
    func_8033F904(rbData->unk389, 1.0f, 0.0f, 0.0f);
    func_8033F904(rbData->unk38A, 1.0f, 0.0f, 0.0f);
    func_8033F904(rbData->unk38B, 1.0f, 0.0f, 0.0f);
}

STATIC_FUNC void rbSoundEvent19(RocketBeltData* rbData) {
    rbData->unk384 &= ~1;
}

STATIC_FUNC void rbSoundSubEvent(RocketBeltData* rbData) {
    f32 temp_fs0;
    f32 var_fv1;
    s32 i;

    if (D_8034F850 < (rbData->unk390 + 0.5f)) {
        return;
    }
    rbData->unk390 = D_8034F850;

    for (i = 0; i < rbData->unk92; i++) {
        var_fv1 = ABS_NOEQ(rbData->unkCC[i]);
        temp_fs0 = func_80313F08(&sRbSound_80371898, var_fv1);
        switch (rbData->unk93[i]) {
        case 4:
            break;
        case 2:
            if (rbData->unk91) {
                sndPlaySfxVolPitchPan(0x16, temp_fs0, 1.0f, 0.0f);
            }
            break;
        case 1:
            if (rbData->unk91) {
                sndPlaySfxVolPitchPan(0x17, temp_fs0, 1.0f, 0.0f);
            }
            break;
        case 8:
            if (rbData->unk91) {
                sndPlaySfxVolPitchPan(0x18, temp_fs0, 1.0f, 0.0f);
            }
            break;
        }
        if (rbData->unk97[i] == 1) {
            sndPlaySfxVolPitchPan(0xC, temp_fs0, 1.0f, 0.0f);
        } else {
            sndPlaySfxVolPitchPan(0x35, temp_fs0, 1.0f, 0.0f);
        }
    }
}

STATIC_FUNC void rbSoundEvent13(RocketBeltData* rbData) {
    rbData->unk388 = func_8033F8CC(rbData->unk388);
    rbData->unk389 = func_8033F8CC(rbData->unk389);
    rbData->unk38C = func_8033F8CC(rbData->unk38C);
    rbData->unk38A = func_8033F8CC(rbData->unk38A);
    rbData->unk38B = func_8033F8CC(rbData->unk38B);
    func_80200180(0, 4, 0.0f, 0);
    uvEventRemoveCb(sRbSoundEventCbInfo, 1, 0xD, 0x12, 0x13, 0x10, 0xC, 0x16, 0x24);
}

