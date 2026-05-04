#include "common.h"
#include <uv_audio.h>
#include "bmsound.h"
#include "camera.h"
#include "game.h"
#include "code_9A960.h"
#include "demo.h"
#include "snd.h"

STATIC_DATA EventCallbackInfo sBmSoundCbInfo;
STATIC_DATA Unk803599D0 D_80359648;

// forward declarations
void bmSoundCallback(s32 eventType, void*, s32 eventData);
void bmSound_802D112C(BirdmanData*);
void bmSound_802D12C4(BirdmanData*);
void bmSound_802D1320(BirdmanData*);
void bmSound_802D1334(BirdmanData*);
void bmSound_802D1534(BirdmanData*);

void bmSoundInit(BirdmanData* bmData) {
    bmData->unk41C = 0.0f;
    D_80359648.count = 4;
    D_80359648.unk4[0].x = 0;
    D_80359648.unk4[0].y = 0.0f;
    D_80359648.unk4[1].x = 0.01f;
    D_80359648.unk4[1].y = 0.4f;
    D_80359648.unk4[2].x = 9.0f;
    D_80359648.unk4[2].y = 0.8f;
    D_80359648.unk4[3].x = 10.0f;
    D_80359648.unk4[3].y = 1.0f;
    // stereo wind sfx
    bmData->unk414 = sndMakeDev(SFX_MOVEMENT_WIND);
    bmData->unk415 = sndMakeDev(SFX_MOVEMENT_WIND);
    sBmSoundCbInfo.cb = bmSoundCallback;
    sBmSoundCbInfo.arg = bmData;
    bmData->unk410 = ~0x3F;
    uvEventMaxCb(sBmSoundCbInfo, 1, 0xD, 0x12, 0x13, 0x16, 0xC, 0x10, 0x24);
}

void bmSoundCallback(s32 eventType, void* arg1, s32 eventData) {
    f32 sp3C;
    f32 temp_fv0;
    f32 var_fa1;
    f32 temp_ft3;
    BirdmanData* a1;
    f32 sp28;

    a1 = (BirdmanData*)arg1;

    if (eventData != 0) {
        _uvDebugPrintf("bmsound Callback got non-zero eventData\n");
    }
    switch (eventType) {
    case 13:
        bmSound_802D1534(a1);
        break;
    case 12:
        bmSound_802D12C4(a1);
        break;
    case 19:
        bmSound_802D1320(a1);
        break;
    case 18:
        bmSound_802D12C4(a1);
        break;
    case 22:
        bmSound_802D112C(a1);
        break;
    case 16:
        break;
    case 1:
        if (!(a1->unk410 & 0x01)) {
            sp28 = FABS(a1->unk274.y);
            var_fa1 = sp28 * 0.02f;
            if (var_fa1 < 0) {
                var_fa1 = 0;
            } else if (var_fa1 > 1.0f) {
                var_fa1 = 1.0f;
            }
            temp_ft3 = (demoRandF() - 0.5f);
            sp3C = (1.3f * var_fa1) + 0.4f + (temp_ft3 * 0.3f);
            sp28 = uvVec3Len(&a1->unk274);
            var_fa1 = (f32)((((demoRandF() * 0.4f) - 0.5f) + 1.0) * (0.02f * sp28));
            if (var_fa1 < 0.0f) {
                var_fa1 = 0.0f;
            } else if (var_fa1 > 1.0f) {
                var_fa1 = 1.0f;
            }
            func_8033F904(a1->unk414, sp3C, var_fa1, -0.5f);

            // effectively copy of code above with following differences:
            //  - demoRandF() * 0.0f (not used)
            //  - func_8033F904() un414/-0.5f -> unk415/0.5f
            sp28 = FABS(a1->unk274.y);
            var_fa1 = sp28 * 0.02f;
            if (var_fa1 < 0) {
                var_fa1 = 0;
            } else if (var_fa1 > 1.0f) {
                var_fa1 = 1.0f;
            }
            temp_ft3 = demoRandF();
            sp3C = (1.3f * var_fa1) + 0.4f + (temp_ft3 * 0.0f);
            sp28 = uvVec3Len(&a1->unk274);
            var_fa1 = (f32)((((demoRandF() * 0.4f) - 0.5f) + 1.0) * (0.02f * sp28));
            if (var_fa1 < 0) {
                var_fa1 = 0;
            } else if (var_fa1 > 1.0f) {
                var_fa1 = 1.0f;
            }
            func_8033F904(a1->unk415, sp3C, var_fa1, 0.5f);

            if ((a1->unk420 < 0.4f) && (a1->unk2BC >= 0.4f) && (a1->unk2CC != 0x1B)) {
                temp_fv0 = (a1->unk2D0 / 3.8f) + 0.4f;
                sp28 = (temp_fv0 > 1.0f) ? 1.0f : temp_fv0;
                sndPlaySfxVolPitchPan(0x4D, sp28, 1.0f, 0.0f);
            }
            a1->unk420 = a1->unk2BC;
        }
        break;
    default:
        _uvDebugPrintf("Got unknown event type %d\n", eventType);
        break;
    }
}

void bmSound_802D112C(BirdmanData* bmData) {
    Unk80362690_Unk0* sp34;
    s32 sfxId;
    f32 pitch;

    sp34 = &D_80362690->unkC[D_80362690->unk9C];
    if (bmData->unk104 == 2) {
        if (!(bmData->unk410 & 0x02)) {
            bmData->unk410 |= 0x02;
            sndPlaySfx(0x36);
            if (!(bmData->unk410 & 0x10)) {
                sndSetMusic(BGM_BIRDMAN_CRASH);
                sndSetMusicState(MUS_STATE_PLAY_SEQ);
                func_8033FCD0(sp34->veh);
            }
            bmSound_802D12C4(bmData);
        }
    } else {
        if (bmData->unk104 == 1) {
            if (!(bmData->unk410 & 0x10)) {
                bmData->unk410 |= 0x10;
                sndGetPilotScream(&sfxId, &pitch);
                sndPlaySfxVolPitchPan(sfxId, 1.0f, pitch, 0.0f);
                sndSetMusic(BGM_BIRDMAN_CRASH);
                sndSetMusicState(MUS_STATE_PLAY_SEQ);
                func_8033FCD0(sp34->veh);
                bmSound_802D12C4(bmData);
            }
        }
        if (bmData->unk104 == 3) {
            if (!(bmData->unk410 & 0x20)) {
                bmData->unk410 |= 0x20;
                sndSetMusic(BGM_BIRDMAN_LAND_OK); // this is never played
                sndSetMusicState(MUS_STATE_PLAY_SEQ);
                func_8033FCD0(sp34->veh);
                bmSound_802D12C4(bmData);
            }
        }
        if (bmData->unk107 != 0) {
            bmSound_802D1334(bmData);
            return;
        }
        if (!(bmData->unk410 & 0x10)) {
            bmData->unk410 = ~0x3F;
        }
    }
}

void bmSound_802D12C4(BirdmanData* bmData) {
    bmData->unk410 |= 1;
    func_8033F904(bmData->unk414, 1.0f, 0.0f, 0.0f);
    func_8033F904(bmData->unk415, 1.0f, 0.0f, 0.0f);
}

void bmSound_802D1320(BirdmanData* bmData) {
    bmData->unk410 &= ~1;
}

void bmSound_802D1334(BirdmanData* bmData) {
    f32 temp_fv1;
    s32 i;

    if (!(D_8034F850 < (bmData->unk41C + 0.5f))) {
        bmData->unk41C = D_8034F850;
        for (i = 0; i < bmData->unk107; i++) {
            temp_fv1 = func_80313F08(&D_80359648, FABS(bmData->unk140[i]));
            switch (bmData->unk108[i]) {
            case 4:
                if ((bmData->unk15C != 0) && (bmData->unk104 == 2)) {
                    if (!(bmData->unk410 & 0x04)) {
                        bmData->unk410 |= 0x04;
                        sndPlaySfx(SFX_WATER_SPLASH);
                    }
                }
                break;
            case 1:
                if (bmData->unk106 != 0) {
                    sndPlaySfxVolPitchPan(0x17, temp_fv1, 1, 0);
                }
                break;
            case 2:
                if (bmData->unk106 != 0) {
                    sndPlaySfxVolPitchPan(0x16, temp_fv1, 1, 0);
                }
                break;
            case 8:
                if (bmData->unk106 != 0) {
                    sndPlaySfxVolPitchPan(0x18, temp_fv1, 1, 0);
                }
                break;
            }
        }
    }
}

void bmSound_802D1534(BirdmanData* bmData) {
    bmData->unk414 = func_8033F8CC(bmData->unk414);
    bmData->unk415 = func_8033F8CC(bmData->unk415);
    uvEventRemoveCb(sBmSoundCbInfo, 1, 0xD, 0x12, 0x13, 0x16, 0xC, 0x10, 0x24);
}
