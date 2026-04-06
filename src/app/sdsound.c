#include "common.h"
#include "game.h"
#include "code_9A960.h"
#include "demo.h"
#include "game.h"
#include "kernel/code_8170.h"
#include "sdsound.h"
#include "snd.h"
#include "task.h"
#include <uv_event.h>

EventCallbackInfo D_80371CB0;
Unk803599D0 D_80371CB8;

// forward declarations
STATIC_FUNC void sdSoundCallback(s32, void*, s32);
STATIC_FUNC void sdsound_80333D80(SkyDivingData*);
STATIC_FUNC void sdsound_80333DDC(SkyDivingData*);
STATIC_FUNC void sdsound_80333DF0(SkyDivingData*);
STATIC_FUNC void sdsound_80334258(SkyDivingData*);
STATIC_FUNC void sdsound_80333F68(SkyDivingData*);

void sdSoundInit(SkyDivingData* arg0) {
    arg0->unk248 = 0.0f;
    D_80371CB8.count = 4;
    D_80371CB8.unk4[0].x = 0 /*.0f*/;
    D_80371CB8.unk4[0].y = 0.0f;
    D_80371CB8.unk4[1].x = 0.01f;
    D_80371CB8.unk4[1].y = 0.4f;
    D_80371CB8.unk4[2].x = 9.0f;
    D_80371CB8.unk4[2].y = 0.8f;
    D_80371CB8.unk4[3].x = 10.0f;
    D_80371CB8.unk4[3].y = 1.0f;
    arg0->unk244 = sndMakeDev(0x13);
    arg0->unk245 = sndMakeDev(0x13);
    D_80371CB0.cb = sdSoundCallback;
    D_80371CB0.arg = arg0;
    arg0->unk240 = ~0x3F;
    uvEventMaxCb(D_80371CB0, 1, 13, 18, 19, 16, 12, 22, 36);
}

// event handler func
STATIC_FUNC void sdSoundCallback(s32 eventType, void* arg1, s32 eventData) {
    f32 sp3C;
    f32 temp_ft3;
    f32 sp34;
    SkyDivingData* skydivingData = (SkyDivingData*)arg1;
    s32 pad;

    if (eventData != 0) {
        _uvAssertMsg("eventData == 0", "sdsound.c", 88);
    }
    switch (eventType) {
    case 13:
        sdsound_80334258(skydivingData);
        return;
    case 12:
        sdsound_80333D80(skydivingData);
        return;
    case 19:
        sdsound_80333DDC(skydivingData);
        return;
    case 16:
        skydivingData->unk240 = ~0x3F;
        return;
    case 18:
        sdsound_80333D80(skydivingData);
        return;
    case 22:
        sdsound_80333DF0(skydivingData);
        return;
    case 1:
        if (skydivingData->unk240 & 1) {
            return;
        }

        sp34 = 0.02f * ABS_NOEQ(skydivingData->unk160.z);
        if (sp34 < 0.0f) {
            sp34 = 0.0f;
        } else if (sp34 > 1.0f) {
            sp34 = 1.0f;
        }
        temp_ft3 = demoRandF() - 0.5f;
        sp3C = (1.3f * sp34) + 0.4f + (temp_ft3 * 0.3f);
        sp34 = (0.02f * uvVec3Len(&skydivingData->unk160)) * (((demoRandF() * 0.4f) - 0.5f) + 1.0);
        if (sp34 < 0.0f) {
            sp34 = 0.0f;
        } else if (sp34 > 1.0f) {
            sp34 = 1.0f;
        }
        func_8033F904(skydivingData->unk244, sp3C, sp34, -0.5f);

        sp34 = 0.02f * ABS_NOEQ(skydivingData->unk160.z);
        if (sp34 < 0.0f) {
            sp34 = 0.0f;
        } else if (sp34 > 1.0f) {
            sp34 = 1.0f;
        }
        temp_ft3 = demoRandF() - 0.5f;
        sp3C = (1.3f * sp34) + 0.4f + (temp_ft3 * 0.3f);
        sp34 = (0.02f * uvVec3Len(&skydivingData->unk160)) * (((demoRandF() * 0.4f) - 0.5f) + 1.0);
        if (sp34 < 0.0f) {
            sp34 = 0.0f;
        } else if (sp34 > 1.0f) {
            sp34 = 1.0f;
        }
        func_8033F904(skydivingData->unk245, sp3C, sp34, 0.5f);
        return;
    default:
        _uvDebugPrintf("Got unknown event type %d\n", eventType);
        break;
    }
}

STATIC_FUNC void sdsound_80333D80(SkyDivingData* arg0) {
    arg0->unk240 |= 1;
    func_8033F904(arg0->unk244, 1.0f, 0.0f, 0.0f);
    func_8033F904(arg0->unk245, 1.0f, 0.0f, 0.0f);
}

STATIC_FUNC void sdsound_80333DDC(SkyDivingData* arg0) {
    arg0->unk240 &= ~1;
}

STATIC_FUNC void sdsound_80333DF0(SkyDivingData* arg0) {
    Unk80362690_Unk0* sp24;

    sp24 = &D_80362690->unkC[D_80362690->unk9C];
    if (arg0->unk70 == 3 || (arg0->unk70 == 5 && arg0->unk2CC < (1.01f * D_8034F854))) {
        if (arg0->unk240 & 2) {
            return;
        }

        arg0->unk240 |= 2;
        sndPlaySfx(SFX_UNK_054);
        if (sp24->unk7A != 0) {
            sndPlaySfx(SFX_UNK_026);
        }
        func_8033F748(0x16);
        func_8033F964(0);
        func_8033FCD0(sp24->veh);
        uvEventPost(0x12, 0);
        sdsound_80333D80(arg0);
        return;
    }

    if (arg0->unk72 != 0) {
        sdsound_80333F68(arg0);
    }

    if (arg0->unk70 == 2) {
        sndPlaySfx(0x48);
        if (arg0->unk25E == 1) {
            func_8033F748(0x14);
        } else {
            func_8033F748(0x15);
        }
        func_8033F964(0);
        func_8033FCD0(sp24->veh);
        uvEventPost(0x12, 0);
    } else {
        arg0->unk240 = ~0x3F;
    }
}

STATIC_FUNC void sdsound_80333F68(SkyDivingData* arg0) {
    s32 i;
    f32 temp_fs0;
    Unk80362690_Unk0* sp44;
    s32 modelId;
    s32 objId;

    sp44 = &D_80362690->unkC[D_80362690->unk9C];
    if (D_8034F850 < arg0->unk248) {
        return;
    }

    arg0->unk248 = D_8034F850 + 0.5f;
    for (i = 0; i < arg0->unk72; i++) {
        temp_fs0 = func_80313F08(&D_80371CB8, ABS_NOEQ(arg0->unkA0[i]));
        switch (arg0->unk73[i]) {
        case 4:
            if (arg0->unkB8 == 0) {
                continue;
            }
            if (arg0->unk240 & 4) {
                continue;
            }

            arg0->unk240 |= 4;
            sndPlaySfx(SFX_UNK_026);
            func_8033F748(0x16);
            func_8033F964(0);
            func_8033FCD0(sp44->veh);
            uvEventPost(0x12, 0);
            continue;
        case 1:
            if (arg0->unk71 != 0) {
                // @fake
                if (1) { }
                sndPlaySfxVolPitchPan(0x17, temp_fs0, 1.0f, 0.0f);
            }
            break;
        case 2:
            if (arg0->unk71 != 0) {
                sndPlaySfxVolPitchPan(0x16, temp_fs0, 1.0f, 0.0f);
            }
            break;
        case 8:
            objId = uvSobjGetPt(D_80362690->terraId, arg0->unk7C[i].x, arg0->unk7C[i].y, arg0->unk7C[i].z);
            if (objId == -1) {
                break;
            }

            modelId = uvSobj_8022D1E4(objId);
            if (MODEL_IS_TREE(modelId)) {
                sndPlaySfxVolPitchPan(0x39, temp_fs0, 1.0f, 0.0f);
            } else if (arg0->unk71 != 0) {
                sndPlaySfxVolPitchPan(0x18, temp_fs0, 1.0f, 0.0f);
            }
            break;
        }

        if (arg0->unk76[i] == 0) {
            sndPlaySfxVolPitchPan(0xC, temp_fs0, 1.0f, 0.0f);
        } else {
            sndPlaySfxVolPitchPan(0x35, temp_fs0, 1.0f, 0.0f);
        }
    }
}

STATIC_FUNC void sdsound_80334258(SkyDivingData* arg0) {
    arg0->unk244 = func_8033F8CC(arg0->unk244);
    arg0->unk245 = func_8033F8CC(arg0->unk245);
    uvEventRemoveCb(D_80371CB0, 1, 13, 18, 19, 16, 12, 22, 36);
}
