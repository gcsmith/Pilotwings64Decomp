#include "common.h"
#include <uv_audio.h>
#include <uv_vector.h>
#include "kernel/code_8170.h"
#include "code_9A960.h"
#include "demo.h"
#include "game.h"
#include "hang_glider.h"
#include "hud.h"
#include "snd.h"

STATIC_DATA EventCallbackInfo sHgSoundEventCbInfo;
STATIC_DATA Unk803599D0 sHgSound_80368318;

// forward declarations
STATIC_FUNC void hgSoundEventHandler(s32, void*, s32);
STATIC_FUNC void hgSoundEvent12_18(HangGliderData*);
STATIC_FUNC void hgSoundEvent19(HangGliderData*);
STATIC_FUNC void hgSoundEvent22(HangGliderData*);
STATIC_FUNC void hgSoundEvent22Sub(HangGliderData*);
STATIC_FUNC void hgSoundEvent13(HangGliderData*);

void hgSoundInit(HangGliderData* hg) {
    hg->unk328 = hg->unk324 = 0.0f;
    sHgSound_80368318.count = 4;
    sHgSound_80368318.unk4[0].x = 0.00f, sHgSound_80368318.unk4[0].y = 0.0f;
    sHgSound_80368318.unk4[1].x = 0.01f, sHgSound_80368318.unk4[1].y = 0.4f;
    sHgSound_80368318.unk4[2].x = 9.00f, sHgSound_80368318.unk4[2].y = 0.8f;
    sHgSound_80368318.unk4[3].x = 10.0f, sHgSound_80368318.unk4[3].y = 1.0f;
    // stereo wind sfx
    hg->unk322 = sndMakeDev(SFX_MOVEMENT_WIND);
    hg->unk323 = sndMakeDev(SFX_MOVEMENT_WIND);
    hg->unk321 = sndMakeDev(0x20);
    sHgSoundEventCbInfo.cb = hgSoundEventHandler;
    sHgSoundEventCbInfo.arg = hg;
    hg->unk318 = 0xFFFFFFC0;
    uvEventMaxCb(sHgSoundEventCbInfo, 1, 0xD, 0x12, 0x13, 0x10, 0xC, 0x16, 0x24);
}

STATIC_FUNC void hgSoundEventHandler(s32 event, void* userData, s32 eventData) {
    f32 sp44;
    f32 sp40;
    f32 var_fa1;
    f32 temp_ft0;
    s32 temp_v0;
    HangGliderData* hg = userData;

    if (eventData != 0) {
        _uvAssertMsg("eventData == 0", "gsound.c", 98);
    }
    switch (event) {
    case 16:
        break;
    case 13:
        hgSoundEvent13(hg);
        break;
    case 12:
        hgSoundEvent12_18(hg);
        break;
    case 19:
        hgSoundEvent19(hg);
        break;
    case 18:
        hgSoundEvent12_18(hg);
        break;
    case 22:
        hgSoundEvent22(hg);
        break;
    case 1:
        if (hg->unk318 & 1) {
            break;
        }
        if ((hg->unk80 == 1) && (hg->unk31C == 0) && (hg->unk240 < 0.4f)) {
            hg->unk31C = 1;
            sndPlaySfx(SFX_HANG_AIR_BRAKE);
        }
        if (hg->unk80 == 0) {
            hg->unk31C = 0;
        }

        if (hg->unk324 < D_8034F850) {
            temp_v0 = hudGet_8031DA9C();
            if ((temp_v0 == 0x157) || (temp_v0 == 0x15C)) {
                hg->unk324 = D_8034F850 + 1.0f;
                sndPlaySfx(SFX_UI_WARNING);
            }
        }

        var_fa1 = ABS_NOEQ(hg->unk200.y) * 0.03f;
        if (var_fa1 < 0.0f) {
            var_fa1 = 0.0f;
        } else if (var_fa1 > 1.0f) {
            var_fa1 = 1.0f;
        }
        temp_ft0 = demoRandF() - 0.5f;
        sp44 = (1.3f * var_fa1) + 0.4f + (temp_ft0 * 0.3f);
        var_fa1 = (0.03f * uvVec3Len(&hg->unk200)) * (((demoRandF() * 0.4f) - 0.5f) + 1.0);
        if (var_fa1 < 0.0f) {
            var_fa1 = 0.0f;
        } else if (var_fa1 > 1.0f) {
            var_fa1 = 1.0f;
        }
        sp40 = 0.8f * var_fa1;
        func_8033F904(hg->unk322, sp44, sp40, -0.5f);

        var_fa1 = ABS_NOEQ(hg->unk200.y) * 0.03f;
        if (var_fa1 < 0.0f) {
            var_fa1 = 0.0f;
        } else if (var_fa1 > 1.0f) {
            var_fa1 = 1.0f;
        }
        temp_ft0 = demoRandF() - 0.5f;
        sp44 = (1.3f * var_fa1) + 0.4f + (temp_ft0 * 0.3f);
        var_fa1 = (0.03f * uvVec3Len(&hg->unk200)) * (((demoRandF() * 0.4f) - 0.5f) + 1.0);
        if (var_fa1 < 0.0f) {
            var_fa1 = 0.0f;
        } else if (var_fa1 > 1.0f) {
            var_fa1 = 1.0f;
        }
        sp40 = 0.8f * var_fa1;
        func_8033F904(hg->unk323, sp44, sp40, 0.5f);
        var_fa1 = hg->unkF0;
        //! @fakematch to get sp40 on the stack but unused
        if (sp40 < 0.0f) {
            sp40 = 0.0f;
        } else if (sp40 > 1.0f) {
            sp40 = 1.0f;
        }

        sp44 = ((1.0f - var_fa1) * 0.4f) + 0.8f;
        sp40 = var_fa1;
        func_8033F904(hg->unk321, sp44, sp40, hg->unk68 * 0.5f);
        break;
    default:
        _uvDebugPrintf("Got unknown event type %d\n", event);
        break;
    }
}

STATIC_FUNC void hgSoundEvent12_18(HangGliderData* hg) {
    hg->unk318 |= 1;
    func_8033F904(hg->unk322, 1.0f, 0.0f, 0.0f);
    func_8033F904(hg->unk323, 1.0f, 0.0f, 0.0f);
    func_8033F904(hg->unk321, 1.0f, 0.0f, 0.0f);
}

STATIC_FUNC void hgSoundEvent19(HangGliderData* hg) {
    hg->unk318 &= 0xFFFFFFFE;
}

STATIC_FUNC void hgSoundEvent22(HangGliderData* hg) {
    Unk80362690_Unk0* sp34;
    s32 sfxId;
    f32 pitch;

    sp34 = &D_80362690->unkC[D_80362690->unk9C];
    if (hg->unk8C == 3) {
        if (!(hg->unk318 & 0x2)) {
            hg->unk318 |= 0x2;
            sndPlaySfx(0x36);
            if (!(hg->unk318 & 0x10)) {
                sndSetMusic(7);
                func_8033F964(0);
                func_8033FCD0(sp34->veh);
            }
            hgSoundEvent12_18(hg);
        }
    } else {
        if (hg->unk8C == 2) {
            if (!(hg->unk318 & 0x10)) {
                hg->unk318 |= 0x10;
                sndGetPilotScream(&sfxId, &pitch);
                sndPlaySfxVolPitchPan(sfxId, 1.0f, pitch, 0.0f);
                sndSetMusic(7);
                func_8033F964(0);
                func_8033FCD0(sp34->veh);
                uvEventPost(0x12, 0);
            }
        }
        if (hg->unk8E != 0) {
            hgSoundEvent22Sub(hg);
        } else if (!(hg->unk318 & 0x10)) {
            hg->unk318 = -0x40;
        }
    }
}

STATIC_FUNC void hgSoundEvent22Sub(HangGliderData* hg) {
    f32 temp_fs0;
    f32 temp_fv0;
    f32 var_fv1;
    s32 soid;
    s32 i;
    s32 modelId;
    Vec3F* vec;

    if (D_8034F850 < hg->unk328) {
        return;
    }

    if (hg->unk8C != 2) {
        hg->unk328 = D_8034F850 + 0.5f;
    } else {
        hg->unk328 = (demoRandF() * 0.5f) + D_8034F850;
    }

    for (i = 0; i < hg->unk8E; i++) {
        temp_fv0 = hg->unkCC[i];
        if (temp_fv0 > 0 /*.0f*/) {
            var_fv1 = temp_fv0;
        } else {
            var_fv1 = -temp_fv0;
        }
        temp_fs0 = func_80313F08(&sHgSound_80368318, var_fv1);
        switch (hg->unk91[i]) {
        case 4:
            continue;
        case 1:
            if (hg->unk8D != 0) {
                sndPlaySfxVolPitchPan(0x17, temp_fs0, 1.0f, 0.0f);
            }
            break;
        default:
            break;
        case 2:
            if (hg->unk8D != 0) {
                sndPlaySfxVolPitchPan(0x16, temp_fs0, 1.0f, 0.0f);
            }
            break;
        case 8:
            vec = &hg->unk9C[i];
            soid = uvSobjGetPt(D_80362690->terraId, vec->x, vec->y, vec->z);
            if (soid != -1) {
                modelId = uvSobj_8022D1E4(soid);
                if (MODEL_IS_TREE(modelId)) {
                    sndPlaySfxVolPitchPan(0x39, temp_fs0, 1.0f, 0.0f);
                } else if (hg->unk8D != 0) {
                    sndPlaySfxVolPitchPan(0x18, temp_fs0, 1.0f, 0.0f);
                }
            }
            break;
        }
        if (hg->unk95[i] == 3) {
            sndPlaySfxVolPitchPan(0xC, temp_fs0, 1.0f, 0.0f);
        } else {
            sndPlaySfxVolPitchPan(0x35, temp_fs0, 1.0f, 0.0f);
        }
    }
}

STATIC_FUNC void hgSoundEvent13(HangGliderData* hg) {
    hg->unk322 = func_8033F8CC(hg->unk322);
    hg->unk323 = func_8033F8CC(hg->unk323);
    hg->unk321 = func_8033F8CC(hg->unk321);
    uvEventRemoveCb(sHgSoundEventCbInfo, 1, 0xD, 0x12, 0x13, 0x10, 0xC, 0x16, 0x24);
}
