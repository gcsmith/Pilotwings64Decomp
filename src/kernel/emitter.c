#include <macros.h>
#include <uv_audio.h>

extern ALSndPlayer* gSndPlayer;
extern ALSndId* gSndVoiceTable;
extern uvaEmitter_t gSndEmitterTable[];
extern uvaEmitter_t D_8025BE48;

void osSyncPrintf(const char* fmt, ...) {
}

void uvEmitterInitTable(void) {
    uvaEmitter_t *term = &D_8025BE48, *iter = gSndEmitterTable;
    do {
        uvEmitterInit(iter);
        iter++;
    } while (iter != term);
    uvEmitterInit(term);
}

void uvEmitterInit(uvaEmitter_t* obj) {
    Mtx4F_t temp;

    Mat4_SetIdentity(temp);
    obj->playVoice = 0x11;
    obj->playState = 0;
    obj->playVolume = 0x7FFF;
    obj->playPan = 0x40;
    obj->playMix = 0;
    obj->playTimeout = 0;
    obj->playPitch = 1.0f;

    Mat4_Copy(obj->m1, temp);
    obj->sound = 0xFF;
    obj->priority = 0;
    obj->unk98 = 0;
    obj->state = 0;

    obj->unk40.x = 0.0f;
    obj->unk40.y = 0.0f;
    obj->unk40.z = 0.0f;

    obj->unk4C.x = 0.0f;
    obj->unk4C.y = 0.0f;
    obj->unk4C.z = 0.0f;

    obj->unk70.x = 1.0f;
    obj->unk70.y = 1.0f;
    obj->unk70.z = 0.0f;
    obj->unk70.w = 0.0f;

    obj->unk80 = 0.0f;
    obj->unk84 = 0.0f;
    obj->near = 0.0f;
    obj->far = 1000.0f;
}

u8 uvEmitterLookup(void) {
    u8 var_v1;

    osSyncPrintf("looking for emitter\n");
    for (var_v1 = 0; var_v1 < 0xFF; var_v1++) {
        if (gSndEmitterTable[var_v1].sound == 0xFF) {
            osSyncPrintf("Returning emitter %d\n", var_v1);
            return var_v1;
        }
    }
    _uvDebugPrintf("no free emitters\n");
    return 0xFF;
}

void uvEmitterFromModel(u8 obj_id, u8 mdl_id) {
    osSyncPrintf("assigning model %d to emitter %d\n", mdl_id, obj_id);
    if (obj_id < 0xFF) {
        if (gSndEmitterTable[obj_id].playState != 0x11) {
            _uvaStopVoice(gSndEmitterTable[obj_id].playVoice);
            gSndEmitterTable[obj_id].playState = 0;
            gSndEmitterTable[obj_id].playVoice = 0x11U;
            gSndEmitterTable[obj_id].playTimeout = 0;
        }
        uvEmitterInit(&gSndEmitterTable[obj_id]);
        gSndEmitterTable[obj_id].sound = mdl_id;
    }
}

void uvEmitterSetMatrix(u8 obj_id, Mtx4F_t msrc) {
    if (obj_id < 0xFF) {
        Mat4_Copy(gSndEmitterTable[obj_id].m1, msrc);
    }
}

void uvEmitterGetMatrix(u8 obj_id, Mtx4F_t mdst) {
    if (obj_id < 0xFF) {
        Mat4_Copy(mdst, gSndEmitterTable[obj_id].m1);
    }
}

void func_80201494(u8 arg0, Vec3F_t arg1, Vec3F_t arg4) {
    Vec3F_t sp44;
    f32 temp_fv0;
    uvaEmitter_t* temp_s0;

    if (arg0 >= 0xFF) {
        return;
    }

    temp_s0 = &gSndEmitterTable[arg0];
    uvVec3Copy(&temp_s0->unk40, &arg1);
    uvVec3Copy(&temp_s0->unk4C, &arg4);
    temp_s0->unk64.x = (temp_s0->unk4C.x + temp_s0->unk40.x) * 0.5f;
    temp_s0->unk64.y = (temp_s0->unk4C.y + temp_s0->unk40.y) * 0.5f;
    temp_s0->unk64.z = (temp_s0->unk4C.z + temp_s0->unk40.z) * 0.5f;
    sp44.z = temp_s0->unk4C.x - temp_s0->unk40.x;
    sp44.y = temp_s0->unk4C.y - temp_s0->unk40.y;
    sp44.x = temp_s0->unk4C.z - temp_s0->unk40.z;
    temp_fv0 = SqrtF(SQ(sp44.z) + SQ(sp44.y) + SQ(sp44.x));
    if (temp_fv0 != 0.0f) {
        temp_s0->unk58.x = sp44.z / temp_fv0;
        temp_s0->unk58.y = sp44.y / temp_fv0;
        temp_s0->unk58.z = sp44.x / temp_fv0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/emitter/func_802015D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/emitter/func_80201614.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/emitter/func_8020165C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/emitter/func_80201698.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/emitter/func_802016D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/emitter/uvEmitterProp.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/emitter/uvEmitterTrigger.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/emitter/uvEmitterRelease.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/emitter/uvEmitterStatus.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/emitter/_uvaSoundBegin.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/emitter/_uvaSoundEnd.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/emitter/uvEmitterFlush.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/emitter/func_80201D08.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/emitter/_uvaUpdatePlayList.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/emitter/_uvaPlaylistRemove.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/emitter/_uvaPlay.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/emitter/_uvaStartVoice.s")

void _uvaUpdateVoice(u8 obj_id) {
    uvaEmitter_t* obj;

    obj = &gSndEmitterTable[obj_id];
    osSyncPrintf("\n  updating voice %d on object %d\n", obj->playVoice, obj_id);

    alSndpSetSound(gSndPlayer, gSndVoiceTable[obj->playVoice]);
    alSndpSetVol(gSndPlayer, obj->playVolume);
    alSndpSetPitch(gSndPlayer, obj->playPitch);
    alSndpSetFXMix(gSndPlayer, obj->playMix);
    alSndpSetPan(gSndPlayer, obj->playPan);
}

void _uvaStopVoice(u8 voice_id) {
    if (voice_id < 0x10) {
        osSyncPrintf("stopping voice%d\n", voice_id);
        alSndpSetSound(gSndPlayer, gSndVoiceTable[voice_id]);
        if (alSndpGetState(gSndPlayer) == 1) {
            alSndpSetVol(gSndPlayer, 0);
        }
        alSndpStop(gSndPlayer);
        return;
    }
    osSyncPrintf("%d is not a valid voice\n", voice_id);
}

void _uvaStatus(u8 obj_id) {
    uvaEmitter_t* obj;

    obj = &gSndEmitterTable[obj_id];
    osSyncPrintf("-----object %d------\n", obj_id);
    osSyncPrintf("playVoice  = %d\n", obj->playVoice);
    osSyncPrintf("playState  = %d\n", obj->playState);
    osSyncPrintf("playTimeout= %d\n", obj->playTimeout);
    osSyncPrintf("playVolume = %d\n", obj->playVolume);
    osSyncPrintf("playPitch  = %f\n", obj->playPitch);
    osSyncPrintf("playPan    = %d\n", obj->playPan);
    osSyncPrintf("near       = %f\n", obj->near);
    osSyncPrintf("far        = %f\n", obj->far);
    osSyncPrintf("sound      = %d\n", obj->sound);
    osSyncPrintf("priority   = %d\n", obj->priority);
    osSyncPrintf("state      = %d\n", obj->state);
}
