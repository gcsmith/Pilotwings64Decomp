#include "common.h"
#include <uv_audio.h>
#include <uv_event.h>
#include <uv_sobj.h>
#include "kernel/code_8170.h"
#include "app/demo.h"
#include "app/gyrocopter.h"
#include "app/hud.h"
#include "app/snd.h"
#include "app/code_9A960.h"

EventCallbackInfo D_80369E50;
Unk803599D0 D_80369E58;
Unk803599D0 D_80369EB0;

void hsound_callback(s32 eventType, void*, s32 eventData);
void func_8030ABF8(GyrocopterData* arg0);
void func_8030ADCC(GyrocopterData* arg0);
void func_8030AEA0(GyrocopterData* arg0);
void func_8030AEB0(GyrocopterData* arg0);
void func_8030B168(GyrocopterData* arg0);

void func_8030A140(GyrocopterData* arg0) {
    s32 i;

    arg0->unk679 = 0;
    arg0->unk68C = 0.0f;
    arg0->unk680 = 0.0f;
    arg0->unk684 = 0.0f;
    arg0->unk688 = 0.0f;

    D_80369E58.count = 4;
    D_80369E58.unk4[0].x = 0.f;
    D_80369E58.unk4[0].y = 0.0f;
    D_80369E58.unk4[1].x = 0.01f;
    D_80369E58.unk4[1].y = 0.4f;
    D_80369E58.unk4[2].x = 9.0f;
    D_80369E58.unk4[2].y = 0.8f;
    D_80369E58.unk4[3].x = 10.0f;
    D_80369E58.unk4[3].y = 1.0f;

    D_80369EB0.count = 3; //! @bug: indexes should be [0-2]
    D_80369EB0.unk4[1].x = 10.f;
    D_80369EB0.unk4[1].y = 0.5f;
    D_80369EB0.unk4[2].x = 100.0f;
    D_80369EB0.unk4[2].y = 1.0f;
    D_80369EB0.unk4[3].x = 400.0f;
    D_80369EB0.unk4[3].y = 1.8f;

    arg0->unk67C = sndMakeDev(0x1F);
    arg0->unk67D = sndMakeDev(0x42);
    arg0->unk67A = sndMakeDev(0x13);
    arg0->unk67B = sndMakeDev(0x13);

    for (i = 0; i < 2; i++) {
        arg0->unk690[i].unk50 = uvEmitterLookup();
        if (arg0->unk690[i].unk50 != 0xFF) {
            uvEmitterFromModel(arg0->unk690[i].unk50, 0x2F);
            uvEmitterSetUnk70(arg0->unk690[i].unk50, 0.6f);
            uvEmitterProp(arg0->unk690[i].unk50, 1, 0.0f, 2, 1000.0f, 5, 0x18, 0);
        }
    }
    D_80369E50.cb = &hsound_callback;
    D_80369E50.arg = arg0;
    arg0->unk678 = 0xC0;
    uvEventMaxCb(D_80369E50, 1, 0xD, 0x12, 0x13, 0x16, 0xC, 0x10, 0x24);
}

void hsound_callback(s32 eventType, void* arg1, s32 eventData) {
    s32 i;
    f32 sp98;
    f32 temp_ft5;
    f32 sp90;
    f32 temp_fv1;
    GyrocopterData* gyrocopterData = (GyrocopterData*)arg1;
    GyrocopterData_Unk690 sp34;

    if (eventData != 0) {
        _uvDebugPrintf("hsound Callback got non-zero eventData\n");
    }
    switch (eventType) {
    case 13:
        func_8030B168(gyrocopterData);
        break;
    case 12:
        func_8030ADCC(gyrocopterData);
        break;
    case 19:
        func_8030AEA0(gyrocopterData);
        break;
    case 18:
        func_8030ADCC(gyrocopterData);
        break;
    case 22:
        func_8030ABF8(gyrocopterData);
        break;
    case 16:
        break;
    case 1:
        if (gyrocopterData->unk678 & 1) {
            break;
        }
        if (gyrocopterData->hasLowFuel && (hudGet_8031DA9C() == 0x17B) && (gyrocopterData->unk684 < D_8034F850)) {
            gyrocopterData->unk684 = D_8034F850 + 0.2f;
            func_8033F758(0x6C, 0.8f, 0.707f, 0.0f);
        }
        if (gyrocopterData->hasLowFuel && (hudGet_8031DA9C() == 0x4A) && (gyrocopterData->unk688 < D_8034F850)) {
            gyrocopterData->unk688 = D_8034F850 + 0.2f;
            func_8033F758(0x6C, 0.8f, 0.707f, 0.0f);
        }

        sp90 = ABS_NOEQ(gyrocopterData->unk364.y) * 0.03f;
        if (sp90 < 0.0f) {
            sp90 = 0.0f;
        } else if (sp90 > 1.0f) {
            sp90 = 1.0f;
        }

        temp_ft5 = demoRandF() - 0.5f;
        sp98 = (1.3f * sp90) + 0.4f + (temp_ft5 * 0.3f);
        sp90 = (0.03f * uvVec3Len(&gyrocopterData->unk364)) * (((demoRandF() * 0.4f) - 0.5f) + 1.0);
        if (sp90 < 0.0f) {
            sp90 = 0.0f;
        } else if (sp90 > 1.0f) {
            sp90 = 1.0f;
        }
        func_8033F904(gyrocopterData->unk67A, sp98, 0.50f * sp90, -0.5f);

        sp90 = ABS_NOEQ(gyrocopterData->unk364.y) * 0.03f;

        if (sp90 < 0.0f) {
            sp90 = 0.0f;
        } else if (sp90 > 1.0f) {
            sp90 = 1.0f;
        }
        temp_ft5 = demoRandF() - 0.5f;
        sp98 = (1.3f * sp90) + 0.4f;
        sp90 = (0.03f * uvVec3Len(&gyrocopterData->unk364)) * (((demoRandF() * 0.4f) - 0.5f) + 1.0);
        if (sp90 < 0.0f) {
            sp90 = 0.0f;
        } else if (sp90 > 1.0f) {
            sp90 = 1.0f;
        }
        func_8033F904(gyrocopterData->unk67B, sp98, 0.50f * sp90, 0.500f);
        if (gyrocopterData->usingFuel) {
            if (gyrocopterData->unk679 < 0xD) {
                if (gyrocopterData->unk680 < D_8034F850) {
                    gyrocopterData->unk679++;
                    if (gyrocopterData->unk679 % 2) {
                        gyrocopterData->unk680 = (demoRandF() * 0.3f) + D_8034F850;
                    } else {
                        gyrocopterData->unk680 = ((demoRandF() * 1.5f) / gyrocopterData->unk679) + D_8034F850;
                    }
                }
            }
        } else if (gyrocopterData->fuel == 0.0f) {
            if (gyrocopterData->unk679 > 0) {
                if (gyrocopterData->unk680 < D_8034F850) {
                    gyrocopterData->unk679--;
                    if (gyrocopterData->unk679 % 2) {
                        gyrocopterData->unk680 = (demoRandF() * 0.3f) + D_8034F850;
                    } else {
                        gyrocopterData->unk680 = ((demoRandF() * 1.5f) / gyrocopterData->unk679) + D_8034F850;
                    }
                }
            }
        } else {
            gyrocopterData->unk679 = 0;
        }
        sp98 = (demoRandF() * 0.2f) + 0.5f + (0.5f * gyrocopterData->unkB4);
        temp_fv1 = (demoRandF() * 0.2f) + 0.75f;
        if (gyrocopterData->unk679 % 2) {
            func_8033F904(gyrocopterData->unk67C, sp98, temp_fv1, gyrocopterData->unkB8 * 0.5f);
        } else {
            func_8033F904(gyrocopterData->unk67C, sp98, temp_fv1 * 0.25f, gyrocopterData->unkB8 * 0.5f);
        }

        sp98 = func_80313F08(&D_80369EB0, gyrocopterData->unkE8) + (demoRandF() * 0.2f);
        if (sp98 >= 0.5f) {
            func_8033F904(gyrocopterData->unk67D, sp98, (demoRandF() * 0.2f) + 0.6f, gyrocopterData->unkB8 * 0.5f);
        } else {
            func_8033F904(gyrocopterData->unk67D, 1.0f, 0.0f, gyrocopterData->unkB8 * 0.5f);
        }

        for (i = 0; i < 2; i++) {
            sp34 = gyrocopterData->unk690[i];
            if (sp34.unk48 == 0) {
                uvEmitterSetUnk70(sp34.unk50, 0.0f);
                uvEmitterRelease(sp34.unk50);
            } else if (sp34.unk48 == 1) {
                uvEmitterSetUnk70(sp34.unk50, 1.0f);
                uvEmitterSetMatrix(sp34.unk50, &sp34.unk0);
                if ((sp34.unk48 == 1) && (sp34.unk4F == 0)) {
                    uvEmitterTrigger(sp34.unk50);
                }
            } else {
                uvEmitterSetMatrix(sp34.unk50, &sp34.unk0);
            }
        }
        break;
    default:
        _uvDebugPrintf("Got unknown event type %d\n", eventType);
        break;
    }
}

void func_8030ABF8(GyrocopterData* arg0) {
    Unk80362690_Unk0* sp34;
    s32 sp30;
    f32 sp2C;

    sp34 = &D_80362690->unkC[D_80362690->unk9C];
    if (arg0->unkC0 == 3) {
        if (!(arg0->unk678 & 2)) {
            arg0->unk678 |= 2;
            func_8030ADCC(arg0);
            sndPlaySfx(0x3F);
            if (!(arg0->unk678 & 0x10)) {
                func_8033F748(0xF);
                func_8033F964(0);
                func_8033FCD0(sp34->veh);
            }
        }
    } else {
        if (arg0->unkC0 == 2) {
            if (!(arg0->unk678 & 0x10)) {
                arg0->unk678 |= 0x10;
                sndGetPilot(&sp30, &sp2C);
                func_8033F758(sp30, 1.0f, sp2C, 0.0f);
                func_8033F748(0xF);
                func_8033F964(0);
                func_8033FCD0(sp34->veh);
                func_8030ADCC(arg0);
            }
        }
        if ((arg0->unkC0 == 4) && (arg0->unk50 != -1)) {
            if (!(arg0->unk678 & 0x20)) {
                arg0->unk678 |= 0x20;
                if ((arg0->unk6C != 0) && (arg0->unk4 == 0xFFFF)) {
                    func_8033F748(0xD);
                } else {
                    func_8033F748(0xE);
                }
                func_8033F964(0);
                func_8033FCD0(sp34->veh);
                func_8030ADCC(arg0);
            }
        }
        if (arg0->unk544 != 0) {
            func_8030AEB0(arg0);
        } else if (!(arg0->unk678 & 0x10)) {
            arg0->unk678 = 0xC0;
        }
    }
}

void func_8030ADCC(GyrocopterData* arg0) {
    s32 i;

    arg0->unk678 |= 1;
    func_8033F904(arg0->unk67C, 1.0f, 0.0f, 0.0f);
    func_8033F904(arg0->unk67A, 1.0f, 0.0f, 0.0f);
    func_8033F904(arg0->unk67B, 1.0f, 0.0f, 0.0f);
    func_8033F904(arg0->unk67D, 1.0f, 0.0f, 0.0f);

    for (i = 0; i < 2; i++) {
        func_8033F904(arg0->unk690[i].unk50, 1.0f, 0.0f, 0.0f);
    }
}

void func_8030AEA0(GyrocopterData* arg0) {
    arg0->unk678 &= ~1;
}

void func_8030AEB0(GyrocopterData* arg0) {
    s32 i;
    f32 temp_fs0;
    s32 soid;
    s32 modelId;

    if (D_8034F850 < (arg0->unk68C + 0.5f)) {
        return;
    }
    arg0->unk68C = D_8034F850;
    for (i = 0; i < arg0->unk544; i++) {
        temp_fs0 = func_80313F08(&D_80369E58, ABS_NOEQ(arg0->unk564[i]));
        switch (arg0->unk545[i]) {
        case 4:
            if ((arg0->unkD0 != 0) && (arg0->unkC0 == 3)) {
                if (!(arg0->unk678 & 4)) {
                    arg0->unk678 |= 4;
                    sndPlaySfx(0x1A);
                }
            }
            break;
        case 1:
            if (arg0->unkC1 != 0) {
                func_8033F758(0x17, temp_fs0, 1.0f, 0.0f);
            }
            break;
        case 2:
            if (arg0->unkC1 != 0) {
                func_8033F758(0x16, temp_fs0, 1.0f, 0.0f);
            }
            break;
        case 8:
            soid = uvSobjGetPt(D_80362690->terraId, arg0->unk54C[i].x, arg0->unk54C[i].y, arg0->unk54C[i].z);
            if (soid != -1) {
                modelId = uvSobj_8022D1E4(soid);
                if (MODEL_IS_TREE(modelId)) {
                    func_8033F758(0x39, temp_fs0, 1.0f, 0.0f);
                } else if (arg0->unkC1 != 0) {
                    func_8033F758(0x18, temp_fs0, 1.0f, 0.0f);
                }
            }
            break;
        }
        if (arg0->unk547[i] == 1) {
            func_8033F758(0xB, temp_fs0, 1.0f, 0.0f);
        } else {
            func_8033F758(8, temp_fs0, 1.0f, 0.0f);
        }
    }
}

void func_8030B168(GyrocopterData* arg0) {
    s32 i;

    arg0->unk67C = func_8033F8CC(arg0->unk67C);
    arg0->unk67A = func_8033F8CC(arg0->unk67A);
    arg0->unk67B = func_8033F8CC(arg0->unk67B);
    arg0->unk67D = func_8033F8CC(arg0->unk67D);

    for (i = 0; i < 2; i++) {
        arg0->unk690[i].unk50 = func_8033F8CC(arg0->unk690[i].unk50);
    }
    uvEventRemoveCb(D_80369E50, 1, 0xD, 0x12, 0x13, 0x16, 0xC, 0x10, 0x24);
}

void func_8030B240(Mtx4F* arg0) {
    u8 sp3F;

    sp3F = sndMakeDev(0x30);
    uvEmitterProp(sp3F, 1, 0.0f, 2, 2000.0f, 5, 0x38, 0);
    uvEmitterSetUnk70(sp3F, 1.0f);
    uvEmitterSetUnk74(sp3F, 1.0f);
    uvEmitterSetMatrix(sp3F, arg0);
}
