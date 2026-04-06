#include "common.h"
#include "game.h"
#include "kernel/code_1050.h"
#include "snd.h"
#include <uv_audio.h>
#include <uv_event.h>
#include <uv_math.h>
#include <uv_matrix.h>
#include <uv_seq.h>

Mtx4F D_80373E20;
Mtx4F D_80373E60;
Mtx4F D_80373EA0;
f32 D_80373EE0;
EventCallbackInfo D_80373EE8;

u16 D_803505B0 = 0xFF;
f32 D_803505B4 = 0.0f;
f32 D_803505B8 = 1.0f;
f32 D_803505BC = 0.0f;
u8 D_803505C0 = 0;
f32 D_803505C4[VEHICLE_COUNT][2] = {
    {  0.9f, 1.0f },
    {  0.8f, 1.0f },
    { 0.65f, 0.9f },
    {  1.0f, 0.5f },
    {  1.0f, 1.0f },
    {  1.0f, 1.0f },
    {  0.7f, 1.0f }
};
f32 D_803505FC[] = { 1.0f, 1.0f, 0.0f, 0.0f, 0.0f };

// forward declarations
void sndEvent(s32, void*, s32);

void sndInit(void) {
    uvMat4SetIdentity(&D_80373E20);
    uvMat4SetIdentity(&D_80373E60);
    uvMat4SetIdentity(&D_80373EA0);
    func_80200144(0, &D_80373E20);
    func_80200180(0, 2, 0.0f, 0);
    func_80204518(0);
    D_80373EE0 = 1.0f;
    D_80373EE8.cb = &sndEvent;
    D_80373EE8.arg = 0;
    uvEventMaxCb(D_80373EE8, 1, 36);
}

void func_8033F6F8(Mtx4F* arg0, Mtx4F* arg1) {
    uvMat4Copy(&D_80373E20, arg0);
    uvMat4Copy(&D_80373E60, arg1);
    func_80200144(0, &D_80373E20);
}

void func_8033F748(u16 arg0) {
    D_803505B0 = arg0;
}

void sndPlaySfxVolPitchPan(u8 sfxId, f32 vol, f32 pitch, f32 pan) {
    u8 temp_v0;

    temp_v0 = uvEmitterLookup();
    if (temp_v0 == 0xFF) {
        _uvDebugPrintf("snd : out of local fx emitter devices\n");
        return;
    }
    uvEmitterFromModel(temp_v0, sfxId);
    uvEmitterProp(temp_v0, 5, 0x30, 0);
    uvEmitterSetUnk70(temp_v0, vol);
    uvEmitterSetUnk74(temp_v0, pitch);
    uvEmitterSetUnk78(temp_v0, pan);
    uvEmitterTrigger(temp_v0);
}

void sndPlaySfx(u8 sfxId) {
    u8 temp_v0;

    temp_v0 = uvEmitterLookup();
    if (temp_v0 == 0xFF) {
        _uvDebugPrintf("snd : out of local fx emitter devices\n");
        return;
    }
    uvEmitterFromModel(temp_v0, sfxId);
    uvEmitterProp(temp_v0, 5, 0x30, 0);
    uvEmitterTrigger(temp_v0);
}

u8 sndMakeDev(s32 arg0) {
    u8 temp_v0;

    temp_v0 = uvEmitterLookup();
    if (temp_v0 == 0xFF) {
        _uvDebugPrintf("snd_makedev -- out of emitter devices\n");
        return 0xFF;
    }
    uvEmitterFromModel(temp_v0, arg0);
    uvEmitterSetUnk70(temp_v0, 0.0f);
    uvEmitterTrigger(temp_v0);
    return temp_v0;
}

u8 func_8033F8CC(u8 arg0) {
    if (arg0 != 0xFF) {
        uvEmitterFromModel(arg0, 0xFF);
    }

    return 0xFF;
}

void func_8033F904(u8 arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 temp_fv0;

    temp_fv0 = uvSqrtF(arg2);
    if (arg0 != 0xFF) {
        uvEmitterSetUnk70(arg0, temp_fv0);
        uvEmitterSetUnk74(arg0, arg1);
        uvEmitterSetUnk78(arg0, arg3);
    }
}

void func_8033F964(u8 arg0) {
    switch (arg0) {
    case 0:
        if (D_803505C0 != 0) {
            uvaSeqStop();
        }
        D_803505BC = 0.0f;
        D_803505C0 = 1;
        uvaSeqNew(D_803505B0);
        uvaSeqPlay();
        return;
    case 1:
        if (D_803505C0 != 0) {
            uvaSeqStop();
            D_803505BC = 0.0f;
            D_803505B4 = 0.0f;
            D_803505C0 = 0;
            return;
        }
        return;
    case 3:
        D_803505BC = 0.5f;
        if (D_803505C0 == 0) {
            D_803505B4 = 0 /*0.0f*/;
            uvaSeqNew(D_803505B0);
            uvaSeqPlay();
            D_803505C0 = 1;
            return;
        }
        break;
    case 2:
        D_803505BC = -0.5f;
        break;
    }
}

void func_8033FA88(f32 arg0) {
    if (D_803505C0 != 0) {
        func_80200180(0, 2, uvSqrtF(arg0), 0);
    }
}

void func_8033FAD4(f32 arg0) {
    D_80373EE0 = arg0;
    func_80200180(0, 1, uvSqrtF(arg0), 0);
}

void func_8033FB14(void) {
    _uvaSoundBegin();
    func_80200308(0);
    _uvaSoundEnd();
}

void sndEvent(s32 event, void* data, s32 eventData) {
    if (event != 1) {
        _uvAssertMsg("event == EVENT_FRM_END", "snd.c", 417);
    }
    if (data != NULL) {
        _uvAssertMsg("data == 0", "snd.c", 419);
    }
    if (eventData != 0) {
        _uvAssertMsg("eventData == 0", "snd.c", 421);
    }
    func_8033FB14();
}

void sndGetPilot(s32* soundId, f32* pitch) {
    Unk80362690_Unk0* temp = &D_80362690->unkC[D_80362690->unk9C];

    switch (temp->pilot) {
    case PILOT_LARK:
        *soundId = 0x55;
        *pitch = 1.1f;
        return;
    case PILOT_GOOSE:
        *soundId = 0x1D;
        *pitch = 1.0f;
        return;
    case PILOT_HAWK:
        *soundId = 0x56;
        *pitch = 0.6f;
        return;
    case PILOT_KIWI:
        *soundId = 0x57;
        *pitch = 0.96f;
        return;
    case PILOT_IBIS:
        *soundId = 0x53;
        *pitch = 1.0f;
        return;
    case PILOT_ROBIN:
        *soundId = 0x58;
        *pitch = 0.75f;
        return;
    default:
        _uvDebugPrintf("snd_getpilot:: Don't know scream for unknown pilot %d\n", temp->pilot);
        return;
    }
}

void func_8033FCD0(u16 arg0) {
    if (arg0 == 0xFF) {
        D_803505B8 = D_803505FC[0];
        D_803505B4 = D_803505FC[1];
    } else if (arg0 == 0xFE) {
        D_803505B8 = 0.0f;
        D_803505B4 = 1.0f;
    } else {
        D_803505B8 = D_803505C4[arg0][0];
        D_803505B4 = D_803505C4[arg0][1];
    }

    func_8033FAD4(D_803505B8);
    func_8033FA88(D_803505B4);
}

void func_8033FD94(u16 arg0, f32 arg1, f32 arg2) {
    s32 i;

    if (arg0 == 0xFF) {
        for (i = 0; i < ARRAY_COUNT(D_803505C4); i++) {
            D_803505C4[i][0] = arg1;
            D_803505C4[i][1] = arg2;
        }
        D_803505FC[0] = arg1;
        D_803505FC[1] = arg2;
    } else {
        D_803505C4[arg0][0] = arg1;
        D_803505C4[arg0][1] = arg2;
    }
}
