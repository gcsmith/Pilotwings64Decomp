#include "common.h"
#include <uv_dobj.h>
#include <uv_math.h>
#include "code_9A960.h"
#include "env_sound.h"
#include "planes.h"
#include "proxanim.h"
#include "spath.h"

typedef struct {
    s32 objId;
    s32 spathId;
    s32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    Vec3F pos;
    f32 unk30;
} Plane; // size = 0x34

static Plane sPlanes[2];
static s32 sPlaneInitialized[2];

STATIC_FUNC void planesUpdate(s32 idx) {
    Mtx4F pose;
    f32 time;
    f32 var_fa1;
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 temp_ft0;
    f32 sp5C;
    f32 temp_fv0;
    Vec3F sp4C;
    Vec3F sp40;

    if (!sPlaneInitialized[idx]) {
        sPlanes[idx].unkC = 0;
        if (sPlanes[idx].unk10 < sPlanes[idx].unkC) {
            sPlanes[idx].unkC -= sPlanes[idx].unk10;
        } else if (sPlanes[idx].unkC < 0.0f) {
            sPlanes[idx].unkC += sPlanes[idx].unk10;
        }
        time = (100.0f * sPlanes[idx].unkC) / sPlanes[idx].unk10;
        spathInterpolate(&sPlanes[idx].pos, &sPlanes[idx].unk18, &sPlanes[idx].unk1C, sPlanes[idx].spathId, time);
        temp_fv0 = sPlanes[idx].unk14;
        sPlanes[idx].pos.z = temp_fv0;
        sPlanes[idx].unk20 = 0.0f;
        sPlaneInitialized[idx] = TRUE;
    }

    //! @fakematch
    if (1) { }

    sPlanes[idx].unkC = sPlanes[idx].unkC + D_8034F854;
    if (sPlanes[idx].unk10 < sPlanes[idx].unkC) {
        sPlanes[idx].unkC -= sPlanes[idx].unk10;
    } else if (sPlanes[idx].unkC < 0.0f) {
        sPlanes[idx].unkC += sPlanes[idx].unk10;
    }

    time = (100.0f * sPlanes[idx].unkC) / sPlanes[idx].unk10;
    spathInterpolate(&sp40, &sp6C, &sp68, sPlanes[idx].spathId, time);

    if ((FABS(sp68 - sPlanes[idx].unk1C) / D_8034F854) > 0.1f) {
        if (sPlanes[idx].unk1C < sp68) {
            sp68 = sPlanes[idx].unk1C + (0.1f * D_8034F854);
        } else {
            sp68 = sPlanes[idx].unk1C - (0.1f * D_8034F854);
        }
    }

    if (sp40.z < sPlanes[idx].unk14) {
        sp40.z = sPlanes[idx].unk14;
    }
    sp4C.x = (sp40.x - sPlanes[idx].pos.x) / D_8034F854;
    sp4C.y = (sp40.y - sPlanes[idx].pos.y) / D_8034F854;
    sp4C.z = (sp40.z - sPlanes[idx].pos.z) / D_8034F854;
    temp_fv0 = uvVec3Len(&sp4C);
    temp_ft0 = (sp6C - sPlanes[idx].unk18) / D_8034F854;
    sp5C = (-sPlanes[idx].unk30 * temp_ft0) / temp_fv0;

    if (ABS_NOEQ(sp5C) > 0.00001f) {
        if (sp5C > 1.0f) {
            var_fa1 = 0.0f;
            sp5C = 1.0f;
        } else if (sp5C < -1.0f) {
            var_fa1 = 0.0f;
            sp5C = -1.0f;
        } else {
            var_fa1 = uvSqrtF(1.0f - SQ(sp5C));
        }
        sp64 = uvAtan2F(sp5C, var_fa1);
        if ((FABS(sp64 - sPlanes[idx].unk20) / D_8034F854) > 0.1f) {
            if (sPlanes[idx].unk20 < sp64) {
                sp64 = sPlanes[idx].unk20 + (0.1f * D_8034F854);
            } else {
                sp64 = sPlanes[idx].unk20 - (0.1f * D_8034F854);
            }
        }
        func_80313640(sp40.x, sp40.y, sp40.z, sp6C, sp68, sp64, &pose);
    } else {
        sp64 = 0.0f;
    }
    func_80313640(sp40.x, sp40.y, sp40.z, sp6C, sp68, sp64, &pose);
    uvDobjPosm(sPlanes[idx].objId, 0, &pose);
    sPlanes[idx].pos.x = sp40.x;
    sPlanes[idx].pos.y = sp40.y;
    sPlanes[idx].pos.z = sp40.z;
    sPlanes[idx].unk20 = sp64;
    sPlanes[idx].unk1C = sp68;
    sPlanes[idx].unk18 = sp6C;
}

void planesGetPos(s32 planeIdx, Vec3F* vec) {
    vec->x = sPlanes[planeIdx].pos.x;
    vec->y = sPlanes[planeIdx].pos.y;
    vec->z = sPlanes[planeIdx].pos.z;
}

STATIC_FUNC s32 planesProxEventCb(UNUSED s32 proxId, s32 eventType, UNUSED s32 clientData) {
    s32 i;

    switch (eventType) {
    case 0:
        break;
    case 2:
        for (i = 0; i < ARRAY_COUNT(sPlanes); i++) {
            uvDobjState(sPlanes[i].objId, 0);
        }
        break;
    case 3:
        for (i = 0; i < ARRAY_COUNT(sPlanes); i++) {
            uvDobjState(sPlanes[i].objId, 2);
        }
        break;
    }
    return 0;
}

STATIC_FUNC s32 planesProxAnimCb(s32 proxId, UNUSED f32 timeout, UNUSED s32 clientData) {
    s32 idx;
    ProxAnim* prox;
    s32 ret;
    f32 tmp;

    ret = 0;
    prox = proxAnimGetHandle(proxId);
    if (prox != NULL) {
        idx = prox->clientData;
        if (prox->active != 0) {
            tmp = proxAnimGetRange(proxId);
            if (tmp > 4000.0f) {
                ret = 2;
            } else {
                planesUpdate(idx);
            }
        }
    }
    return ret;
}

void planesLoad(void) {
    s32 i;
    Vec3F pos;
    LevelESND envSnd;

    for (i = 0; i < ARRAY_COUNT(sPlanes); i++) {
        sPlanes[i].objId = uvDobjAllocIdx();
        if (sPlanes[i].objId != 0xFFFF) {
            switch (i) {
            case 0:
                envSnd.sndId = 0x17;
                uvDobjModel(sPlanes[i].objId, MODEL_BIG_WHITE_RED_PLANE);
                uvDobjState(sPlanes[i].objId, 2);
                sPlanes[i].spathId = spathLoadFile(0x6D);
                sPlanes[i].unk10 = 120.0f;
                sPlanes[i].unk30 = 150.0f;
                sPlanes[i].unk14 = 42.43231f;
                pos.x = -1225.0f;
                pos.y = 454.0f;
                pos.z = 161.4f;
                break;
            case 1:
                envSnd.sndId = 0x18;
                uvDobjModel(sPlanes[i].objId, MODEL_YELLOW_WHITE_PLANE);
                uvDobjState(sPlanes[i].objId, 2);
                sPlanes[i].spathId = spathLoadFile(0x6E);
                sPlanes[i].unk10 = 120.0f;
                sPlanes[i].unk30 = 150.0f;
                sPlanes[i].unk14 = 33.757683f;
                pos.x = -211.85f;
                pos.y = 884.5f;
                pos.z = 224.3f;
                break;
            }
            uvMat4SetIdentity(&envSnd.unk0);
            envSnd.unk5C = 1.0f;
            envSnd.unk60 = 1.0f;
            envSnd.unk64 = 0;
            envSnd.unk68 = 0.0f;
            envSnd.unk6C = 200.0f;
            envSnd.unk74 = 8;
            envSnd.unk70 = 0;
            envSnd.unk0.m[3][0] = pos.x;
            envSnd.unk0.m[3][1] = pos.y;
            envSnd.unk0.m[3][2] = pos.z;
            envSoundLoad(&envSnd);
            sPlanes[i].unk8 = proxAnimAddCallback(planesProxAnimCb, planesProxEventCb, pos, 4000.0f, 0.0f, i);
            planesUpdate(i);
        }
    }
}

void planesDeinit(void) {
    Plane* plane;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sPlanes); i++) {
        plane = &sPlanes[i];
        if (plane->objId != 0xFFFF) {
            uvDobjModel(plane->objId, 0xFFFF);
            plane->objId = 0xFFFF;
            proxAnimDeleteCallback(plane->unk8);
            spathFree(plane->spathId);
        }
    }
}

void planesInit(void) {
    s32 i;
    for (i = 0; i < ARRAY_COUNT(sPlanes); i++) {
        sPlanes[i].objId = 0xFFFF;
        sPlaneInitialized[i] = FALSE;
    }
}

void planesGetObjData(s32 planeIdx, s32* objId, f32* arg2, Vec3F* vec) {
    Mtx4F pose;
    Plane* plane;

    plane = &sPlanes[planeIdx];
    if (plane->objId != 0xFFFF) {
        *objId = plane->objId;
        *arg2 = plane->unkC / plane->unk10;
        uvDobjGetPosm(*objId, 0, &pose);
        vec->x = pose.m[3][0];
        vec->y = pose.m[3][1];
        vec->z = pose.m[3][2];
    } else {
        *objId = 0xFFFF;
        *arg2 = 0.0f;
        vec->x = 0.0f;
        vec->y = 0.0f;
        vec->z = 0.0f;
    }
}

void planesUpdateInterval(s32 planeIdx, f32 interval) {
    Plane* plane;
    f32 temp_fs1;

    plane = &sPlanes[planeIdx];
    if (plane->objId != 0xFFFF) {
        uvDobjState(plane->objId, 2);
        temp_fs1 = plane->unk10 * interval;

        // this looks like for loop pattern with f32, but doesn't match
        plane->unkC = 0.0f;
        sPlaneInitialized[planeIdx] = FALSE;
        if (temp_fs1 > 0.0f) {
            do {
                planesUpdate(planeIdx);
                plane->unkC += 1.0f;
            } while (plane->unkC < temp_fs1);
        }

        plane->unkC = temp_fs1;
        planesUpdate(planeIdx);
    }
}
