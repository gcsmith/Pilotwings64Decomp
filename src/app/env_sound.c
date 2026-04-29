#include "app/task.h"
#include "common.h"
#include <uv_audio.h>
#include <uv_event.h>
#include <uv_math.h>
#include "kernel/code_1050.h"
#include "boats.h"
#include "code_61A60.h"
#include "code_9A960.h"
#include "camera.h"
#include "demo.h"
#include "env_sound.h"
#include "environment.h"
#include "ferry.h"
#include "game.h"
#include "planes.h"
#include "shadow.h"
#include "shuttle.h"
#include "snd.h"

typedef struct {
    f32 unk0;
    u8 emitterId;
    u8 sndId;
    u8 unk6;
    u8 pad7[1];
} EnvSoundEmitter;

typedef struct {
    EnvSoundEmitter emitters[255];
    s32 unk7F8;
    s32 count;
    s32 flags;
} EnvSoundState; // size = 0x804

typedef struct {
    Mtx4F unk0;
    Vec3F unk40;
    Vec3F unk4C;
    u8 unk58;
    u8 pad59[3];
    f32 unk5C;
    f32 unk60;
    s32 unk64;
    f32 unk68;
    f32 unk6C;
    u8 unk70;
    u8 pad71[3];
    s32 unk74;
} Unk802E27A8_Arg0; // size = 0x78

STATIC_DATA s32 D_8034EF20 = 0;
STATIC_DATA s32 D_8034EF24 = 0;
STATIC_DATA s32 D_8034EF28 = 0;
STATIC_DATA s32 sEnvSoundIsInit = FALSE;
STATIC_DATA s32 sEnvSoundModelIdLookup[28] = { 0x0D, 0x0E, 0x2A, 0x25, 0x29, 0x0D, 0x40, 0x41, 0x14, 0x47, 0x21, 0x07, 0x21, 0x21,
                                               0x21, 0x21, 0x21, 0x21, 0x2F, 0x2F, 0x2F, 0x6B, 0x6B, 0x6B, 0x6B, 0x51, 0x6B, 0x00 };

STATIC_DATA EventCallbackInfo sEnvSoundEventCb;
STATIC_DATA EnvSoundState sEnvSoundState;
STATIC_DATA f32 sEnvSoundFutureTime; // time set +4 seconds, only set
STATIC_DATA u8 sEnvSoundStateCount[20];

// forward declarations
void envSound_802E2904(EnvSoundState*);
void envSound_802E2A00(s32 eventType, void* arg1, s32 eventData);
void envSound_802E3250(EnvSoundState*);
void envSound_802E3310(EnvSoundState*);
void envSound_802E3398(EnvSoundState*);

void envSoundInit(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sEnvSoundStateCount); i++) {
        sEnvSoundStateCount[i] = 0;
    }

    sEnvSoundFutureTime = 0.0f;
    sEnvSoundIsInit = TRUE;
    envSound_802E2904(&sEnvSoundState);
    sEnvSoundEventCb.cb = &envSound_802E2A00;
    sEnvSoundEventCb.arg = &sEnvSoundState;
    uvEventMaxCb(sEnvSoundEventCb, 1, 0xD, 0x12, 0x13, 0xB, 0x17, 0x18, 0x19, 0xC, 0xE, 0x24);
}

void envSoundLoad(LevelESND* arg0) {
    s32 idx;
    u8 emitterId;
    EnvSoundState* ptr = &sEnvSoundState;

    idx = ptr->count;

    if (!sEnvSoundIsInit) {
        return;
    }

    ptr->count++;
    ptr->emitters[idx].unk0 = arg0->unk60;
    ptr->emitters[idx].sndId = arg0->sndId;
    ptr->emitters[idx].unk6 = arg0->unk70;
    ptr->emitters[idx].emitterId = uvEmitterLookup();
    emitterId = ptr->emitters[idx].emitterId;
    uvEmitterFromModel(emitterId, sEnvSoundModelIdLookup[arg0->sndId]);
    uvEmitterSetMatrix(emitterId, &arg0->unk0);
    if (arg0->unk74 & 0x2) {
        uvEmitter_80201494(emitterId, arg0->unk40, arg0->unk4C);
    }
    uvEmitterSetVol(emitterId, arg0->unk60);
    uvEmitterSetPitch(emitterId, arg0->unk5C);
    uvEmitterSetPri(emitterId, arg0->unk64);
    // clang-format off
    uvEmitterProps(emitterId,
        EMITTER_PROP_ATTR(arg0->unk74),
        EMITTER_PROP_NEAR(arg0->unk68),
        EMITTER_PROP_FAR(arg0->unk6C),
        EMITTER_PROP_END
    );
    // clang-format on
}

void envSound_802E2904(EnvSoundState* arg0) {
    s32 i;

    for (i = 0; i < arg0->count; i++) {
        uvEmitterSetVol(arg0->emitters[i].emitterId, 0.0f);
        func_8033F8CC(arg0->emitters[i].emitterId);
    }

    for (i = 0; i < ARRAY_COUNT(arg0->emitters); i++) {
        arg0->emitters[i].emitterId = 0xFF;
        arg0->emitters[i].sndId = 0xFF;
        arg0->emitters[i].unk6 = 0xFF;
    }
    arg0->unk7F8 = 0xFF;
    arg0->count = 0;
    arg0->flags = 0xFFFFFFC0;
}

void envSound_802E2A00(s32 eventType, void* arg1, s32 eventData) {
    s32 i;
    EnvSoundState* esState;
    s32 sp26C;
    Mtx4F sp22C;
    Vec3F sp220;
    EnvSoundEmitter* emitter;
    f32 temp_fs0;
    f32 temp_fs1;
    Vec3F sp208;
    Mtx4F sp1C8;
    Vec3F sp1BC;
    Mtx4F sp17C;
    Vec3F sp170;
    Mtx4F sp130;
    Mtx4F spF0;
    s32 pad;
    Mtx4F spAC;
    Unk80362690* ptr;
    Vec3F sp9C;
    Mtx4F sp5C;

    esState = arg1;
    switch (eventType) {
    case 14:
        if (D_8034EF24 == 0) {
            D_8034EF24 = 1;
            D_8034EF20 = 0;
        }
        break;
    default:
        break;
    case 12:
        if (D_8034EF20 == 0) {
            D_8034EF20 = 1;
            D_8034EF24 = 0;
        }
        break;
    case 23:
        envSound_802E2904(esState);
        break;
    case 24:
        esState->unk7F8 = 0xFF;
        envSound_802E3310(esState);
        break;
    case 13:
        if (eventData == 0) {
            envSound_802E3398(esState);
        }
        break;
    case 25:
        envSound_802E3398(esState);
        break;
    case 19:
        if (D_8034EF24 == 0) {
            D_8034EF24 = 1;
            D_8034EF20 = 0;
            D_8034EF28 = 0;
            esState->unk7F8 = 0xFF;
        }
        break;
    case 18:
        if (D_8034EF20 == 0) {
            D_8034EF20 = 1;
            D_8034EF24 = 0;
        }
        break;
    case 1:
        if (esState->flags & 0x1) {
            break;
        }

        if (D_8034EF24 != 0) {
            D_8034EF28++;
        }

        if (D_80362690->terraId == 9) {
            D_8034EF28 = 0;
            break;
        }

        if (D_8034EF28 < 2) {
            break;
        }

        if (D_8034EF28 == 2) {
            envSound_802E3310(esState);
        }
        if (D_80362690->map == MAP_CRESCENT_ISLAND) {
            sp26C = D_80362690->unkC[D_80362690->unk9C].unk8;
            if (sp26C != esState->unk7F8) {
                envSound_802E3250(esState);
            }
        }

        for (i = 0; i < esState->count; i++) {
            emitter = &esState->emitters[i];
            if (D_8034EF20 != 0) {
                uvEmitterSetVol(emitter->emitterId, uvEmitterGetVol(emitter->emitterId) * 0.95f);
            } else {
                if ((sp26C == emitter->unk6) || (emitter->unk6 == 0xA)) {
                    switch (emitter->sndId) {
                    case 0:
                        temp_fs1 = ((demoRandF() - 0.5f) * 0.1f) + 0.8f;
                        temp_fs0 = ((demoRandF() - 0.5f) * 0.2f) + 0.9f;
                        uvEmitterSetPitch(emitter->emitterId, temp_fs1);
                        uvEmitterSetVol(emitter->emitterId, temp_fs0);
                        break;
                    case 1:
                        temp_fs1 = ((demoRandF() - 0.5f) * 0.1f) + 0.8f;
                        temp_fs0 = ((demoRandF() - 0.5f) * 0.1f) + 0.95f;
                        uvEmitterSetPitch(emitter->emitterId, temp_fs1);
                        uvEmitterSetVol(emitter->emitterId, temp_fs0);
                        break;
                    case 2:
                        temp_fs1 = ((demoRandF() - 0.5f) * 0.1f) + 0.8f;
                        uvEmitterSetPitch(emitter->emitterId, temp_fs1);
                        break;
                    case 3:
                        temp_fs1 = 1.0f;
                        temp_fs0 = ((demoRandF() - 0.5f) * 0.2f) + 0.9f;
                        uvEmitterSetPitch(emitter->emitterId, temp_fs1);
                        uvEmitterSetVol(emitter->emitterId, temp_fs0);
                        break;
                    case 4:
                        temp_fs1 = ((demoRandF() - 0.5f) * 0.1f) + 0.8f;
                        temp_fs0 = ((demoRandF() - 0.5f) * 0.2f) + 0.9f;
                        uvEmitterSetPitch(emitter->emitterId, temp_fs1);
                        uvEmitterSetVol(emitter->emitterId, temp_fs0);
                        break;
                    case 5:
                        temp_fs1 = ((demoRandF() - 0.5f) * 0.1f) + 1.8f;
                        temp_fs0 = ((demoRandF() - 0.5f) * 0.2f) + 0.7f;
                        uvEmitterSetPitch(emitter->emitterId, temp_fs1);
                        uvEmitterSetVol(emitter->emitterId, temp_fs0);
                        break;
                    case 9:
                        temp_fs1 = ((demoRandF() - 0.5f) * 0.1f) + 1.00f; // + 1.0f
                        temp_fs0 = ((demoRandF() - 0.5f) * 0.1f) + 0.95f;
                        uvEmitterSetPitch(emitter->emitterId, temp_fs1);
                        uvEmitterSetVol(emitter->emitterId, temp_fs0);
                        break;
                    case 11:
                        temp_fs1 = ((demoRandF() - 0.5f) * 0.1f) + 0.4f;
                        uvEmitterSetPitch(emitter->emitterId, temp_fs1);
                        break;
                    case 26:
                        ferryGetPos(&sp208);
                        sp1C8.m[3][0] = sp208.x;
                        sp1C8.m[3][1] = sp208.y;
                        sp1C8.m[3][2] = sp208.z;
                        uvEmitterSetMatrix(emitter->emitterId, &sp1C8);
                        break;
                    case 23:
                        planesGetPos(0, &sp1BC);
                        sp17C.m[3][0] = sp1BC.x;
                        sp17C.m[3][1] = sp1BC.y;
                        sp17C.m[3][2] = sp1BC.z;
                        uvEmitterSetMatrix(emitter->emitterId, &sp17C);
                        break;
                    case 24:
                        planesGetPos(1, &sp170);
                        sp130.m[3][0] = sp170.x;
                        sp130.m[3][1] = sp170.y;
                        sp130.m[3][2] = sp170.z;
                        uvEmitterSetMatrix(emitter->emitterId, &sp130);
                        break;
                    case 21:
                        if (boatsGetPose(0, &spF0) != 0) {
                            uvEmitterSetMatrix(emitter->emitterId, &spF0);
                        } else {
                            uvEmitterRelease(emitter->emitterId);
                        }
                        break;
                    case 22:
                        if (boatsGetPose(1, &spAC) != 0) {
                            uvEmitterSetMatrix(emitter->emitterId, &spAC);
                        } else {
                            uvEmitterRelease(emitter->emitterId);
                        }
                        break;
                    case 17:
                        uvEmitterGetMatrix(emitter->emitterId, &sp22C);
                        env_802E1754(sp22C.m[3][0], sp22C.m[3][1], sp22C.m[3][2], &sp220);
                        temp_fs1 = (sp220.y * 0.1f) + 0.25f;
                        temp_fs0 = sp220.y;
                        if (temp_fs0 < 0.0f) {
                            temp_fs0 = 0.0f;
                        } else if (temp_fs0 > 1.0f) {
                            temp_fs0 = 1.0f;
                        }
                        uvEmitterSetPitch(emitter->emitterId, temp_fs1);
                        uvEmitterSetVol(emitter->emitterId, temp_fs0);
                        break;
                    case 20:
                        switch (shuttleGetState()) {
                        case 0:
                            uvEmitterSetPitch(emitter->emitterId, 1.0f);
                            uvEmitterSetVol(emitter->emitterId, 0.0f);
                            break;
                        case 1:
                            uvEmitterSetPitch(emitter->emitterId, 0.20f); // 0.2f
                            uvEmitterSetVol(emitter->emitterId, 1.0f);
                            break;
                        case 2:
                            uvEmitterSetPitch(emitter->emitterId, 0.33f);
                            uvEmitterSetVol(emitter->emitterId, 1.0f);
                            shuttle_80335F24(&sp9C);
                            uvMat4SetIdentity(&sp5C);
                            sp5C.m[3][0] = sp9C.x;
                            sp5C.m[3][1] = sp9C.y;
                            sp5C.m[3][2] = sp9C.z;
                            uvEmitterSetMatrix(emitter->emitterId, &sp5C);
                            break;
                        case 3:
                            uvEmitterSetPitch(emitter->emitterId, 1.0f);
                            uvEmitterSetVol(emitter->emitterId, 0.5f);
                            shuttle_80335F24(&sp9C);
                            uvMat4SetIdentity(&sp5C);
                            sp5C.m[3][0] = sp9C.x;
                            sp5C.m[3][1] = sp9C.y;
                            sp5C.m[3][2] = sp9C.z;
                            uvEmitterSetMatrix(emitter->emitterId, &sp5C);
                            break;
                        case 4:
                            uvEmitterSetPitch(emitter->emitterId, 1.0f);
                            uvEmitterSetVol(emitter->emitterId, 0.0f);
                            break;
                        default:
                            _uvDebugPrintf("got unkown shuttle state\n");
                            break;
                        }
                        break;
                    case 6:
                    case 7:
                    case 8:
                    case 12:
                    case 14:
                    case 15:
                    case 16:
                    case 25:
                        break;
                    default:
                        _uvDebugPrintf("Got unknown sndId\n");
                        break;
                    }
                }
            }
        }
        break;
    }
}

void envSound_802E3250(EnvSoundState* arg0) {
    EnvSoundEmitter* var_s0;
    s32 i;
    s32 temp_s4;

    temp_s4 = D_80362690->unkC[D_80362690->unk9C].unk8;
    for (i = 0; i < arg0->count; i++) {
        var_s0 = &arg0->emitters[i];
        if (temp_s4 == var_s0->unk6) {
            uvEmitterTrigger(var_s0->emitterId);
        } else if (var_s0->unk6 != 0xA) {
            uvEmitterRelease(var_s0->emitterId);
        }
    }
    arg0->unk7F8 = temp_s4;
}

void envSound_802E3310(EnvSoundState* arg0) {
    EnvSoundEmitter* var_s0;
    s32 i;

    D_8034EF24 = 1;
    D_8034EF20 = 0;
    arg0->flags = 0xFFFFFFC0;
    for (i = 0; i < arg0->count; i++) {
        var_s0 = &arg0->emitters[i];
        uvEmitterSetVol(var_s0->emitterId, var_s0->unk0);
        uvEmitterTrigger(var_s0->emitterId);
    }
}

void envSound_802E3398(EnvSoundState* arg0) {
    D_8034EF20 = 0;
    D_8034EF24 = 0;
    D_8034EF28 = 0;
    sEnvSoundIsInit = FALSE;
    sEnvSoundFutureTime = 0.0f;
    envSound_802E2904(arg0);
    uvEventRemoveCb(sEnvSoundEventCb, 1, 0xD, 0x12, 0x13, 0xB, 0x17, 0x18, 0x19, 0xC, 0xE, 0x24);
}

void envSoundFrameUpdate(Mtx4F* arg0) {
    LevelAPTS* aptsRef;
    u8 aptCount;
    u8 i;
    LevelAPTS* apt;
    Vec3F sp1E8;
    Vec3F sp1DC;
    f32 temp_fs0;
    f32 temp_fv0;
    f32 var_ft0;
    s32 pad;
    Vec3F sp1C0;
    Vec3F sp1B4;
    Unk802D3658_Unk1224 sp70;

    aptCount = levelGetAPTS(&aptsRef);
    if ((aptCount == 0) || (sEnvSoundState.flags & 1)) {
        return;
    }

    for (i = 0; i < aptCount; i++) {
        apt = &aptsRef[i];
        sp1E8.x = arg0->m[3][0] - apt->pos.x;
        sp1E8.y = arg0->m[3][1] - apt->pos.y;
        sp1E8.z = arg0->m[3][2] - apt->pos.z;
        temp_fs0 = uvVec3Len(&sp1E8);
        sp1DC.x = uvCosF((apt->unkC + 90.0f) * 0.01745329f);
        sp1DC.y = uvSinF((apt->unkC + 90.0f) * 0.01745329f);
        sp1DC.z = 0.0f;
        temp_fv0 = uvVec3Dot(&sp1DC, &sp1E8);
        if (temp_fs0 <= apt->unk10) {
            switch (apt->unk14) {
            case 0:
                if (temp_fv0 > 0.0f) {
                    sEnvSoundStateCount[0] = 0;
                    var_ft0 = ((apt->unk1C - apt->unk18) * (apt->unk10 - temp_fs0)) / (2.0f * apt->unk10);
                } else {
                    sEnvSoundStateCount[0] = 1;
                    var_ft0 = ((apt->unk1C - apt->unk18) * (apt->unk10 + temp_fs0)) / (2.0f * apt->unk10);
                }
                func_80200180(0, 4, var_ft0, 0);
                break;
            case 1:
                sp1B4.x = sp1C0.x = arg0->m[3][0];
                sp1B4.y = sp1C0.y = arg0->m[3][1];
                sp1B4.z = arg0->m[3][2];
                sp1C0.z = apt->unk10 + sp1B4.z;
                if (func_802DB224(&sp70, 0xB, 0xFFFF, 0, &sp1B4, &sp1C0) != 0) {
                    sEnvSoundStateCount[1]++;
                } else {
                    if ((sEnvSoundStateCount[1] > 0) && (D_80362690->unkC[0].unkA != 4) && (D_80362690->unkC[0].veh != VEHICLE_JUMBLE_HOPPER)) {
                        if (sEnvSoundFutureTime < D_8034F850) {
                            sEnvSoundFutureTime = D_8034F850 + 4.0f;
                            sndPlaySfx(0x50);
                        }
                    }
                    sEnvSoundStateCount[1] = 0;
                }
                break;
            }
        } else if (apt->unk14 == 0) {
            if (sEnvSoundStateCount[0] == 0) {
                func_80200180(0, 4, apt->unk18, 0);
            } else {
                func_80200180(0, 4, apt->unk1C, 0);
            }
        }
    }
}

