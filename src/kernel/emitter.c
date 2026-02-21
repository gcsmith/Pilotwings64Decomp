#include <macros.h>
#include <uv_audio.h>
#include <uv_math.h>
#include <libc/stdarg.h>

#define VOICE_PLAYLIST_COUNT 16

u8 sEmitterPlaylistObjects[VOICE_PLAYLIST_COUNT];
u8 sEmitterVoiceObjects[VOICE_PLAYLIST_COUNT];
s32 sNumPlaylistEmitters;
uvaEmitter_t gSndEmitterTable[256];

extern ALSndPlayer* gSndPlayer;
extern ALSndId* gSndVoiceTable;
extern ALBank* D_8026120C;

void uvEmitterPrintf(const char* fmt, ...) {
}

void uvEmitterInitTable(void) {
    s32 i;
    for (i = 0; i < 0xFF; i++) {
        uvEmitterInit(&gSndEmitterTable[i]);
    }
    uvEmitterInit(&gSndEmitterTable[255]);
}

void uvEmitterInit(uvaEmitter_t* obj) {
    Mtx4F temp;

    uvMat4SetIdentity(&temp);
    obj->playVoice = 0x11;
    obj->playState = 0;
    obj->playVolume = 0x7FFF;
    obj->playPan = 0x40;
    obj->playMix = 0;
    obj->playTimeout = 0;
    obj->playPitch = 1.0f;

    uvMat4Copy(&obj->m1, &temp);
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

    uvEmitterPrintf("looking for emitter\n");
    for (var_v1 = 0; var_v1 < 0xFF; var_v1++) {
        if (gSndEmitterTable[var_v1].sound == 0xFF) {
            uvEmitterPrintf("Returning emitter %d\n", var_v1);
            return var_v1;
        }
    }
    _uvDebugPrintf("no free emitters\n");
    return 0xFF;
}

void uvEmitterFromModel(u8 obj_id, u8 mdl_id) {
    uvEmitterPrintf("assigning model %d to emitter %d\n", mdl_id, obj_id);
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

void uvEmitterSetMatrix(u8 obj_id, Mtx4F* src) {
    if (obj_id < 0xFF) {
        uvMat4Copy(&gSndEmitterTable[obj_id].m1, src);
    }
}

void uvEmitterGetMatrix(u8 obj_id, Mtx4F* dst) {
    if (obj_id < 0xFF) {
        uvMat4Copy(dst, &gSndEmitterTable[obj_id].m1);
    }
}

void uvEmitter_80201494(u8 obj_id, Vec3F arg1, Vec3F arg4) {
    Vec3F sp44;
    f32 temp_fv0;
    uvaEmitter_t* obj;

    if (obj_id >= 0xFF) {
        return;
    }

    obj = &gSndEmitterTable[obj_id];
    uvVec3Copy(&obj->unk40, &arg1);
    uvVec3Copy(&obj->unk4C, &arg4);
    obj->unk64.x = (obj->unk4C.x + obj->unk40.x) * 0.5f;
    obj->unk64.y = (obj->unk4C.y + obj->unk40.y) * 0.5f;
    obj->unk64.z = (obj->unk4C.z + obj->unk40.z) * 0.5f;
    sp44.z = obj->unk4C.x - obj->unk40.x;
    sp44.y = obj->unk4C.y - obj->unk40.y;
    sp44.x = obj->unk4C.z - obj->unk40.z;
    temp_fv0 = uvSqrtF(SQ(sp44.z) + SQ(sp44.y) + SQ(sp44.x));
    if (temp_fv0 != 0.0f) {
        obj->unk58.x = sp44.z / temp_fv0;
        obj->unk58.y = sp44.y / temp_fv0;
        obj->unk58.z = sp44.x / temp_fv0;
    }
}

void uvEmitterSetUnk70(u8 obj_id, f32 arg1) {
    if (obj_id < 0xFF) {
        gSndEmitterTable[obj_id].unk70.x = arg1;
    }
}

f32 uvEmitterGetUnk70(u8 obj_id) {
    if (obj_id >= 0xFF) {
        return 0.0f;
    }
    return gSndEmitterTable[obj_id].unk70.x;
}

void uvEmitterSetUnk78(u8 obj_id, f32 arg1) {
    if (obj_id < 0xFF) {
        gSndEmitterTable[obj_id].unk70.z = arg1;
    }
}

void uvEmitterSetUnk74(u8 obj_id, f32 arg1) {
    if (obj_id < 0xFF) {
        gSndEmitterTable[obj_id].unk70.y = arg1;
    }
}

void uvEmitterSetPri(u8 obj_id, s32 pri) {
    if (obj_id < 0xFF) {
        gSndEmitterTable[obj_id].priority = pri;
    }
}

void uvEmitterProp(u8 obj_id, ...) {
    f32 temp_fv0;
    uvaEmitter_t* obj;
    s32 propertyType;
    va_list args;

    if (obj_id >= 0xFF || obj_id == 0xFF) {
        return;
    }
    obj = &gSndEmitterTable[obj_id];

    // passing an object that undergoes default argument promotion to 'va_start'
    // has undefined behavior (e.g. u8, u16, f32)
#if defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wvarargs"
#endif
    va_start(args, obj_id);
#if defined(__clang__)
#pragma GCC diagnostic pop
#endif

    while (TRUE) {
        propertyType = va_arg(args, s32);
        switch (propertyType) {
        case 0:
            return;
        case 1:
            temp_fv0 = va_arg(args, f64);
            obj->near = SQ(temp_fv0);
            break;
        case 2:
            temp_fv0 = va_arg(args, f64);
            obj->far = SQ(temp_fv0);
            break;
        case 4:
            obj->unk84 = va_arg(args, f64);
            break;
        case 3:
            obj->unk80 = va_arg(args, f64);
            break;
        case 5:
            obj->unk98 = va_arg(args, s32);
            break;
        default:
            uvEmitterPrintf("Unknown property type 0x%x\n", propertyType);
            return;
        }
    }
}

void uvEmitterTrigger(u8 obj_id) {
    if (obj_id < 0xFF) {
        uvEmitterPrintf("\nemitter %d triggered\n", obj_id);
        gSndEmitterTable[obj_id].state = 0x10;
    }
}

void uvEmitterRelease(u8 obj_id) {
    if (obj_id < 0xFF) {
        uvEmitterPrintf("\nreleasing trigger on %d\n", obj_id);

        if (gSndEmitterTable[obj_id].playVoice != 0x11) {
            _uvaStopVoice(gSndEmitterTable[obj_id].playVoice);
        }
        gSndEmitterTable[obj_id].state = 0;
        gSndEmitterTable[obj_id].playVoice = 0x11;
        gSndEmitterTable[obj_id].playState = 0;
        gSndEmitterTable[obj_id].playTimeout = 0;
        if (gSndEmitterTable[obj_id].unk98 & 0x20) {
            uvEmitterInit(&gSndEmitterTable[obj_id]);
        }
    }
}

void uvEmitterStatus(u8 arg0) {
    u8 i;
    u8 emitterCount;

    for (i = 0, emitterCount = 0; i < 255; i++) {
        if (gSndEmitterTable[i].sound != 0xFF) {
            if (arg0 != 0) {
                gSndEmitterTable[i].unk98 |= 0x20;
                uvEmitterRelease(i);
            }
            emitterCount++;
        }
    }
    if (emitterCount > 0) {
        _uvDebugPrintf("@@@  %d Emitters %s\n", emitterCount, (arg0 != 0) ? "released" : "still in use");
    }
    if (sNumPlaylistEmitters > 0) {
        _uvDebugPrintf("###  %d emitters on active playlist\n", sNumPlaylistEmitters);
    }
}

void _uvaSoundBegin(void) {
    s32 i;

    uvEmitterPrintf("\nsoundBegin\n");

    for (i = 0; i < VOICE_PLAYLIST_COUNT; i++) {
        sEmitterPlaylistObjects[i] = 255;
        sEmitterVoiceObjects[i] = 255;
    }

    sNumPlaylistEmitters = 0;
}

void _uvaSoundEnd(void) {
    uvEmitterPrintf("\nsoundEnd\n");
    _uvaPlay();
}

void uvEmitterFlush(u16 arg0) {
    s32 i;

    for (i = 0; i < 255; i++) {
        if ((gSndEmitterTable[i].playState == 1) || (gSndEmitterTable[i].playState == 2) || (gSndEmitterTable[i].playState == 8) ||
            (gSndEmitterTable[i].state == 0x10)) {
            if (gSndEmitterTable[i].playState == 2) {
                gSndEmitterTable[i].playTimeout++;
            }
            uvEmitter_80201D08(i, arg0);
            if (((gSndEmitterTable[i].playVolume + gSndEmitterTable[i].priority) == 0) ||
                ((gSndEmitterTable[i].playState == 2) && (gSndEmitterTable[i].playTimeout >= 5))) {
                uvEmitterPrintf("Flushing object %d due to timeout or zero priority\n", i);
                if (gSndEmitterTable[i].unk98 & 0x10) {
                    uvEmitterRelease(i);
                } else {
                    uvEmitterRelease(i);
                    uvEmitterTrigger(i);
                }
            } else {
                _uvaUpdatePlayList(i);
            }
        }
    }
}

// variable 'sp84' is used uninitialized whenever 'if' condition is true. see @bug below
#if defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsometimes-uninitialized"
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif
void uvEmitter_80201D08(u8 obj_id, u16 arg1) {
    s32 pan;
    f32 spB8;
    Vec3F spAC;
    Vec3F spA0;
    Vec3F sp94;
    Vec3F sp88;
    f32 sp84;
    f32 temp_fv0;
    f32 var_fa0;
    Mtx4F sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    uvaEmitter_t* obj;
    s32 sp28;

    sp38 = D_80250E80[arg1].unk40;
    sp34 = D_80250E80[arg1].unk48;
    sp30 = D_80250E80[arg1].unk4C;
    obj = &gSndEmitterTable[obj_id];
    sp28 = obj->unk98;
    uvMat4Copy(&sp3C, &D_80250E80[arg1].mat);
    if (sp28 & 8) {
        spA0.x = sp3C.m[0][0];
        spA0.y = sp3C.m[0][1];
        spA0.z = sp3C.m[0][2];
        spAC.x = sp3C.m[3][0];
        spAC.y = sp3C.m[3][1];
        spAC.z = sp3C.m[3][2];
        if (sp28 & 2) {
            sp94.x = spAC.x - obj->unk40.x;
            sp94.y = spAC.y - obj->unk40.y;
            sp94.z = spAC.z - obj->unk40.z;
            if (uvVec3Dot(&sp94, &obj->unk58) < 0.0f) {
                sp84 = SQ(sp94.x) + SQ(sp94.y) + SQ(sp94.z);
            } else {
                sp88.x = -obj->unk58.x;
                sp88.y = -obj->unk58.y;
                sp88.z = -obj->unk58.z;
                sp94.x = spAC.x - obj->unk4C.x;
                sp94.y = spAC.y - obj->unk4C.y;
                sp94.z = spAC.z - obj->unk4C.z;
                temp_fv0 = uvVec3Dot(&sp94, &sp88);
                if (temp_fv0 < 0.0f) {
                    sp84 = SQ(sp94.x) + SQ(sp94.y) + SQ(sp94.z);
                } else {
                    sp94.x = spAC.x - ((temp_fv0 * sp88.x) + obj->unk4C.x);
                    sp94.y = spAC.y - ((temp_fv0 * sp88.y) + obj->unk4C.y);
                    sp94.z = spAC.z - ((temp_fv0 * sp88.z) + obj->unk4C.z);
                    sp84 = SQ(sp94.x) + SQ(sp94.y) + SQ(sp94.z);
                }
            }
        } else if (sp28 & 1) {
            //! @bug sp84 is uninitialised in this code path
        } else {
            sp94.x = obj->m1.m[3][0] - sp3C.m[3][0];
            sp94.y = obj->m1.m[3][1] - sp3C.m[3][1];
            sp94.z = obj->m1.m[3][2] - sp3C.m[3][2];
            sp84 = SQ(sp94.x) + SQ(sp94.y) + SQ(sp94.z);
        }

        if (obj->far < sp84) {
            obj->playPan = 0x40;
            obj->playVolume = 0;
            obj->playPitch = obj->unk70.y;
            return;
        }

        if (sp84 <= obj->near) {
            spB8 = obj->unk70.x;
        } else {
            spB8 = (obj->unk70.x * (obj->far - sp84)) / (obj->far - obj->near);
        }
        if ((sp30 != 1.0f) && (sp84 != 0.0f)) {
            var_fa0 = uvVec3ScalarProj(&sp94, &spA0);

            if (sp84 < obj->near) {
                var_fa0 *= sp84 / obj->near;
            }
            if (sp28 & 2) {
                var_fa0 *= -1.0f;
            }
            pan = (s32)((1.0f + var_fa0) * 64.0f);
            if (pan == 0x80) {
                pan = 0x7F;
            }
        } else {
            pan = 0x40;
        }
    } else {
        spB8 = obj->unk70.x;
        if (sp30 != 1) {
            pan = (s32)((obj->unk70.z + 1.0f) * 64.0f);
            if (pan == 0x80) {
                pan = 0x7F;
            }
        } else {
            pan = 0x40;
        }
    }
    if (sp28 & 4) {
        obj->playMix = (s32)(sp34 * 127.0f);
    } else {
        obj->playMix = (s32)(obj->unk70.w * 127.0f);
    }
    obj->playPan = pan;
    obj->playPitch = obj->unk70.y;
    obj->playVolume = (s32)(spB8 * sp38 * 32767.0f);
}
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif

void _uvaUpdatePlayList(u8 obj_id) {
    s32 i;
    s32 j;
    s32 priority;
    s32 newPriority;
    s32 var_s7;

    var_s7 = FALSE;
    uvEmitterPrintf("\ninserting object %d in playlist\n", obj_id);

    if ((gSndEmitterTable[obj_id].unk98 & 0x10) && (gSndEmitterTable[obj_id].playState == 8) &&
        (uvEmitterPrintf("CHECKING if to delete oneshot object %d\n", obj_id), alSndpSetSound(gSndPlayer, gSndVoiceTable[gSndEmitterTable[obj_id].playVoice]),
         (alSndpGetState(gSndPlayer) == 0))) {
        _uvaStopVoice(gSndEmitterTable[obj_id].playVoice);
        gSndEmitterTable[obj_id].playVoice = 0x11;
        gSndEmitterTable[obj_id].playState = 0;
        if (gSndEmitterTable[obj_id].unk98 & 0x20) {
            uvEmitterPrintf("Object %d expunged due to finish\n", obj_id);
            uvEmitterInit(&gSndEmitterTable[obj_id]);
        }
        return;
    }
    if (sNumPlaylistEmitters == 0) {
        uvEmitterPrintf("object %d first in list\n", obj_id);
        sEmitterPlaylistObjects[0] = obj_id;
        sNumPlaylistEmitters++;
        if (gSndEmitterTable[obj_id].playVoice != 0x11) {
            uvEmitterPrintf("object %d (1st in list) already has a voice\n", obj_id);
            sEmitterVoiceObjects[gSndEmitterTable[obj_id].playVoice] = obj_id;
        }
        uvEmitterPrintf("_uvaUpdatePlayList finished for object %d\n", obj_id);
        return;
    }
    priority = gSndEmitterTable[obj_id].priority + gSndEmitterTable[obj_id].playVolume;
    uvEmitterPrintf("priority = %d for object %d\n", priority, obj_id);

    for (i = 0; (i < sNumPlaylistEmitters) && !var_s7; i++) {
        uvEmitterPrintf("i = %d\n", i);

        newPriority = gSndEmitterTable[sEmitterPlaylistObjects[i]].playVolume + gSndEmitterTable[sEmitterPlaylistObjects[i]].priority;
        uvEmitterPrintf("new Priority %d\n", newPriority);
        if (priority >= newPriority) {
            var_s7 = TRUE;
            uvEmitterPrintf("inserting in playlist\n");
            if (sNumPlaylistEmitters == VOICE_PLAYLIST_COUNT) {
                uvEmitterPrintf("flushing last item in playlist - %d\n", sEmitterPlaylistObjects[sNumPlaylistEmitters - 1]);

                if (gSndEmitterTable[sEmitterPlaylistObjects[sNumPlaylistEmitters - 1]].playVoice != 0x11) {
                    sEmitterVoiceObjects[gSndEmitterTable[sEmitterPlaylistObjects[sNumPlaylistEmitters - 1]].playVoice] = 0xFF;
                    uvEmitterPrintf("object %d had voice already\n", obj_id);
                }
                _uvaPlaylistRemove(sEmitterPlaylistObjects[sNumPlaylistEmitters - 1]);
            }

            for (j = sNumPlaylistEmitters; j > i; j--) {
                sEmitterPlaylistObjects[j] = sEmitterPlaylistObjects[j - 1];
            }
            sEmitterPlaylistObjects[i] = obj_id;
            if (gSndEmitterTable[obj_id].playVoice != 0x11) {
                sEmitterVoiceObjects[gSndEmitterTable[obj_id].playVoice] = obj_id;
                uvEmitterPrintf("object %d had voice already\n", obj_id);
            }
        }
    }
    if (!var_s7 && (i == VOICE_PLAYLIST_COUNT)) {
        uvEmitterPrintf("object %d flushed\n", obj_id);
        if (gSndEmitterTable[obj_id].playVoice != 0x11) {
            sEmitterVoiceObjects[gSndEmitterTable[obj_id].playVoice] = 0xFF;
        }
        _uvaPlaylistRemove(obj_id);
        return;
    }
    if (!var_s7 && (i == sNumPlaylistEmitters)) {
        uvEmitterPrintf("object %d last in list\n", obj_id);
        sEmitterPlaylistObjects[i] = obj_id;
        sNumPlaylistEmitters++;
        if (gSndEmitterTable[obj_id].playVoice != 0x11) {
            uvEmitterPrintf("object %d (last in list) already has a voice\n", obj_id);
            sEmitterVoiceObjects[gSndEmitterTable[obj_id].playVoice] = obj_id;
        }
        uvEmitterPrintf("_uvaUpdatePlayList finished for object %d\n", obj_id);
        return;
    }
    if (sNumPlaylistEmitters < VOICE_PLAYLIST_COUNT) {
        sNumPlaylistEmitters++;
    }
    uvEmitterPrintf("%d used voices\n", sNumPlaylistEmitters);
    uvEmitterPrintf("exiting _uvaUpdatePlayList\n");
}

void _uvaPlaylistRemove(u8 obj_id) {
    uvaEmitter_t* obj = &gSndEmitterTable[obj_id];

    uvEmitterPrintf("\nRemoving object %d from playlist\n", obj_id);
    if (obj->unk98 & 0x10) {
        uvEmitterRelease(obj_id);
        return;
    }

    if (obj->playVoice != 0x11) {
        _uvaStopVoice(obj->playVoice);
        obj->playVoice = 0x11;
        obj->playState = 0;
        obj->playTimeout = 0;
    }
    uvEmitterTrigger(obj_id);
}

void _uvaPlay(void) {
    s32 i;
    s32 j;

    uvEmitterPrintf("\n_uvaPlay %d voices busy\n", sNumPlaylistEmitters);

    for (i = 0; i < sNumPlaylistEmitters; i++) {
        uvEmitterPrintf("playing object %d\n", sEmitterPlaylistObjects[i]);
        _uvaStatus(sEmitterPlaylistObjects[i]);

        if (gSndEmitterTable[sEmitterPlaylistObjects[i]].playState == 0) {
            j = 0;
            while (sEmitterVoiceObjects[j] != 0xFF && j < 15) {
                j++;
            }

            uvEmitterPrintf("object %d getting a new voice: %d, j = %d\n", sEmitterPlaylistObjects[i], sEmitterVoiceObjects[j], j);

            sEmitterVoiceObjects[j] = sEmitterPlaylistObjects[i];
            gSndEmitterTable[sEmitterPlaylistObjects[i]].playVoice = j;
            _uvaStartVoice(sEmitterPlaylistObjects[i]);
        }
        if (gSndEmitterTable[sEmitterPlaylistObjects[i]].playState == 1) {
            _uvaStartVoice(sEmitterPlaylistObjects[i]);
        }
        if (gSndEmitterTable[sEmitterPlaylistObjects[i]].playState == 2) {
            uvEmitterPrintf("Checking if object %d is playing\n", sEmitterPlaylistObjects[i]);
            alSndpSetSound(gSndPlayer, gSndVoiceTable[gSndEmitterTable[sEmitterPlaylistObjects[i]].playVoice]);
            if (alSndpGetState(gSndPlayer) == 1) {
                uvEmitterPrintf("object %d is playing\n", sEmitterPlaylistObjects[i]);
                gSndEmitterTable[sEmitterPlaylistObjects[i]].playState = 8;
                gSndEmitterTable[sEmitterPlaylistObjects[i]].playTimeout = 0;
            }
        }

        if (gSndEmitterTable[sEmitterPlaylistObjects[i]].playState == 8) {
            _uvaUpdateVoice(sEmitterPlaylistObjects[i]);
        }
    }
}

void _uvaStartVoice(u8 obj_id) {
    ALInstrument* instrument;

    uvEmitterPrintf("\n_uvaStartVoice object %d -- voice %d\n", obj_id, gSndEmitterTable[obj_id].playVoice);
    gSndEmitterTable[obj_id].playState = 1;
    alSndpSetSound(gSndPlayer, gSndVoiceTable[gSndEmitterTable[obj_id].playVoice]);
    if (alSndpGetState(gSndPlayer) != 0) {
        alSndpStop(gSndPlayer);
        return;
    }
    alSndpDeallocate(gSndPlayer, gSndVoiceTable[gSndEmitterTable[obj_id].playVoice]);
    instrument = D_8026120C->instArray[gSndEmitterTable[obj_id].sound];
    gSndVoiceTable[gSndEmitterTable[obj_id].playVoice] = alSndpAllocate(gSndPlayer, instrument->soundArray[0]);
    alSndpSetSound(gSndPlayer, gSndVoiceTable[gSndEmitterTable[obj_id].playVoice]);
    if (gSndVoiceTable[gSndEmitterTable[obj_id].playVoice] >= 0) {
        _uvaUpdateVoice(obj_id);
        alSndpPlay(gSndPlayer);
        gSndEmitterTable[obj_id].playState = 2;
        gSndEmitterTable[obj_id].state = 0;
    }
}

void _uvaUpdateVoice(u8 obj_id) {
    uvaEmitter_t* obj;

    obj = &gSndEmitterTable[obj_id];
    uvEmitterPrintf("\n  updating voice %d on object %d\n", obj->playVoice, obj_id);

    alSndpSetSound(gSndPlayer, gSndVoiceTable[obj->playVoice]);
    alSndpSetVol(gSndPlayer, obj->playVolume);
    alSndpSetPitch(gSndPlayer, obj->playPitch);
    alSndpSetFXMix(gSndPlayer, obj->playMix);
    alSndpSetPan(gSndPlayer, obj->playPan);
}

void _uvaStopVoice(u8 voice_id) {
    if (voice_id < VOICE_PLAYLIST_COUNT) {
        uvEmitterPrintf("stopping voice%d\n", voice_id);
        alSndpSetSound(gSndPlayer, gSndVoiceTable[voice_id]);
        if (alSndpGetState(gSndPlayer) == 1) {
            alSndpSetVol(gSndPlayer, 0);
        }
        alSndpStop(gSndPlayer);
        return;
    }
    uvEmitterPrintf("%d is not a valid voice\n", voice_id);
}

void _uvaStatus(u8 obj_id) {
    uvaEmitter_t* obj;

    obj = &gSndEmitterTable[obj_id];
    uvEmitterPrintf("-----object %d------\n", obj_id);
    uvEmitterPrintf("playVoice  = %d\n", obj->playVoice);
    uvEmitterPrintf("playState  = %d\n", obj->playState);
    uvEmitterPrintf("playTimeout= %d\n", obj->playTimeout);
    uvEmitterPrintf("playVolume = %d\n", obj->playVolume);
    uvEmitterPrintf("playPitch  = %f\n", obj->playPitch);
    uvEmitterPrintf("playPan    = %d\n", obj->playPan);
    uvEmitterPrintf("near       = %f\n", obj->near);
    uvEmitterPrintf("far        = %f\n", obj->far);
    uvEmitterPrintf("sound      = %d\n", obj->sound);
    uvEmitterPrintf("priority   = %d\n", obj->priority);
    uvEmitterPrintf("state      = %d\n", obj->state);
}

