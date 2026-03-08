#include "common.h"
#include <uv_event.h>
#include "bmsound.h"
#include "code_5A6A0.h"
#include "code_72B70.h"
#include "code_9A960.h"
#include "demo.h"
#include "snd.h"

EventCallbackInfo gBmSoundCbInfo;
Unk803599D0 D_80359648;

// forward declarations
void bmSoundCallback(s32 eventType, void*, s32 eventData);
void bmSound_802D112C(Unk80367704*);
void bmSound_802D12C4(Unk80367704*);
void bmSound_802D1320(Unk80367704*);
void bmSound_802D1334(Unk80367704*);
void bmSound_802D1534(Unk80367704*);

void bmSoundInit(Unk80367704* arg0) {
    arg0->unk41C = 0.0f;
    D_80359648.unk0 = 4;
    D_80359648.unk4 = 0;
    D_80359648.unk8 = 0.0f;
    D_80359648.unkC = 0.01f;
    D_80359648.unk10 = 0.4f;
    D_80359648.unk14 = 9.0f;
    D_80359648.unk18 = 0.8f;
    D_80359648.unk1C = 10.0f;
    D_80359648.unk20 = 1.0f;
    arg0->unk414 = snd_makedev(0x13);
    arg0->unk415 = snd_makedev(0x13);
    gBmSoundCbInfo.cb = bmSoundCallback;
    gBmSoundCbInfo.arg = arg0;
    arg0->unk410 = 0xFFFFFFC0;
    uvEventMaxCb(gBmSoundCbInfo, 1, 0xD, 0x12, 0x13, 0x16, 0xC, 0x10, 0x24);
}

void bmSoundCallback(s32 eventType, void* arg1, s32 eventData) {
    f32 sp3C;
    f32 temp_fv0;
    f32 var_fa1;
    f32 temp_ft3;
    Unk80367704* a1;
    f32 sp28;

    a1 = (Unk80367704*)arg1;

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
                func_8033F758(0x4D, sp28, 1.0f, 0.0f);
            }
            a1->unk420 = a1->unk2BC;
        }
        break;
    default:
        _uvDebugPrintf("Got unknown event type %d\n", eventType);
        break;
    }
}

void bmSound_802D112C(Unk80367704* arg0) {
    Unk80362690_Unk0_UnkC* sp34;
    s32 sp30;
    f32 sp2C;

    sp34 = &D_80362690->unk0[D_80362690->unk9C].unkC;
    if (arg0->unk104 == 2) {
        if (!(arg0->unk410 & 0x02)) {
            arg0->unk410 |= 0x02;
            snd_play_sfx(0x36);
            if (!(arg0->unk410 & 0x10)) {
                func_8033F748(0x1B);
                func_8033F964(0);
                func_8033FCD0(sp34->veh);
            }
            bmSound_802D12C4(arg0);
        }
    } else {
        if (arg0->unk104 == 1) {
            if (!(arg0->unk410 & 0x10)) {
                arg0->unk410 |= 0x10;
                snd_getpilot(&sp30, &sp2C);
                func_8033F758(sp30, 1.0f, sp2C, 0.0f);
                func_8033F748(0x1B);
                func_8033F964(0);
                func_8033FCD0(sp34->veh);
                bmSound_802D12C4(arg0);
            }
        }
        if (arg0->unk104 == 3) {
            if (!(arg0->unk410 & 0x20)) {
                arg0->unk410 |= 0x20;
                func_8033F748(0x1A);
                func_8033F964(0);
                func_8033FCD0(sp34->veh);
                bmSound_802D12C4(arg0);
            }
        }
        if (arg0->unk107 != 0) {
            bmSound_802D1334(arg0);
            return;
        }
        if (!(arg0->unk410 & 0x10)) {
            arg0->unk410 = 0xFFFFFFC0;
        }
    }
}

void bmSound_802D12C4(Unk80367704* arg0) {
    arg0->unk410 |= 1;
    func_8033F904(arg0->unk414, 1.0f, 0.0f, 0.0f);
    func_8033F904(arg0->unk415, 1.0f, 0.0f, 0.0f);
}

void bmSound_802D1320(Unk80367704* arg0) {
    arg0->unk410 &= 0xFFFFFFFE;
}

void bmSound_802D1334(Unk80367704* arg0) {
    f32 temp_fv1;
    s32 i;

    if (!(D_8034F850 < (arg0->unk41C + 0.5f))) {
        arg0->unk41C = D_8034F850;
        for (i = 0; i < arg0->unk107; i++) {
            temp_fv1 = func_80313F08(&D_80359648, FABS(arg0->unk140[i]));
            switch (arg0->unk108[i]) {
            case 4:
                if ((arg0->unk15C != 0) && (arg0->unk104 == 2)) {
                    if (!(arg0->unk410 & 0x04)) {
                        arg0->unk410 |= 0x04;
                        snd_play_sfx(0x1A);
                    }
                }
                break;
            case 1:
                if (arg0->unk106 != 0) {
                    func_8033F758(0x17, temp_fv1, 1, 0);
                }
                break;
            case 2:
                if (arg0->unk106 != 0) {
                    func_8033F758(0x16, temp_fv1, 1, 0);
                }
                break;
            case 8:
                if (arg0->unk106 != 0) {
                    func_8033F758(0x18, temp_fv1, 1, 0);
                }
                break;
            }
        }
    }
}

void bmSound_802D1534(Unk80367704* arg0) {
    arg0->unk414 = func_8033F8CC(arg0->unk414);
    arg0->unk415 = func_8033F8CC(arg0->unk415);
    uvEventRemoveCb(gBmSoundCbInfo, 1, 0xD, 0x12, 0x13, 0x16, 0xC, 0x10, 0x24);
}
