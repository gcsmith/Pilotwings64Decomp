#include "common.h"
#include <uv_dobj.h>
#include <uv_vector.h>
#include "code_9A960.h"
#include "env_sound.h"
#include "ferry.h"
#include "hud.h"
#include "level.h"
#include "proxanim.h"

static f32 sFerryInterval = 0.0f;
static s32 sFerryObjId = 0xFFFF;
static s32 sFerryProxId = 0xFFFFFFFF;
static s32 sFerryRadarId = 0xFF;
static s32 sFerryActive = FALSE;

static Vec3F sFerryInitPos = { 1150.0f, -2150.0f, 8.8f };

// .bss
static Mtx4F sFerryTranslate;
static Mtx4F sFerryTranslateX;
static Mtx4F sFerryPose;
static f32 sFerryIntervalCopy;

s32 ferryIsActive(void) {
    return sFerryActive;
}

void ferryUpdatePos(void) {
    Mtx4F intervalMtx;
    Mtx4F translateMtx;

    uvMat4SetIdentity(&intervalMtx);
    uvMat4RotateAxis(&intervalMtx, sFerryInterval * 0.01745329f, 'z');
    uvMat4Mul(&translateMtx, &sFerryTranslateX, &intervalMtx);
    uvMat4Mul(&sFerryPose, &translateMtx, &sFerryTranslate);
    uvDobjPosm(sFerryObjId, 0, &sFerryPose);
    if (sFerryRadarId != 0xFF) {
        hudMoveWaypoint(sFerryRadarId, sFerryPose.m[3][0], sFerryPose.m[3][1], sFerryPose.m[3][2]);
    }
}

STATIC_FUNC void ferryUpdate(void) {
    sFerryInterval += 5.0f * D_8034F854;
    if (sFerryInterval > 360.0) {
        sFerryInterval = (f32)(sFerryInterval - 360.0);
    }
    ferryUpdatePos();
}

STATIC_FUNC s32 ferryProxEventCb(s32 proxId, s32 eventType, s32 arg) {
    switch (eventType) {
    case 0:
        break;
    case 2:
        uvDobjState(sFerryObjId, 0);
        if (sFerryRadarId != 0xFF) {
            hud_8031A874(sFerryRadarId);
        }
        break;
    case 3:
        uvDobjState(sFerryObjId, 3);
        if (sFerryRadarId != 0xFF) {
            hud_8031A874(sFerryRadarId);
        }
        break;
    }
    return 0;
}

STATIC_FUNC s32 ferryProxAnimCb(s32 proxId, f32 timeout, s32 arg) {
    f32 val;
    s32 ret;

    ret = 0;
    val = proxAnimGetRange(proxId);
    if (val > 1200.0f) {
        sFerryActive = FALSE;
        ret = 2;
    } else {
        sFerryActive = TRUE;
        ferryUpdate();
    }
    return ret;
}

void ferryInit(void) {
    sFerryActive = FALSE;
    sFerryInterval = 0.0f;
}

void ferryLoad(void) {
    u16 cls;
    u16 veh;
    u16 test;
    s32 showHudWaypoint;
    LevelESND envSnd;
    Vec3F pos;

    pos = sFerryInitPos;
    sFerryObjId = uvDobjAllocIdx();
    if (sFerryObjId == 0xFFFF) {
        return;
    }

    uvDobjModel(sFerryObjId, MODEL_BIG_CRUISE_SHIP);
    sFerryProxId = proxAnimAddCallback(ferryProxAnimCb, ferryProxEventCb, pos, 1200.0f, 0.0f, 2);
    uvDobjState(sFerryObjId, 3);
    uvMat4SetIdentity(&sFerryTranslateX);
    uvMat4LocalTranslate(&sFerryTranslateX, 200.0f, 0.0f, 0.0f);
    uvMat4SetIdentity(&sFerryTranslate);
    uvMat4LocalTranslate(&sFerryTranslate, 1150.0f, -2150.0f, 8.8f);
    ferryUpdatePos();
    envSnd.sndId = 0x1A;
    uvMat4SetIdentity(&envSnd.unk0);
    envSnd.unk64 = 0;
    envSnd.unk74 = 8;
    envSnd.unk70 = 0;
    envSnd.unk5C = 1.0f;
    envSnd.unk60 = 1.0f;
    envSnd.unk0.m[3][0] = sFerryPose.m[3][0];
    envSnd.unk0.m[3][1] = sFerryPose.m[3][1];
    envSnd.unk0.m[3][2] = sFerryPose.m[3][2];
    envSnd.unk68 = 0.0f;
    envSnd.unk6C = 400.0f;
    envSoundLoad(&envSnd);
    taskGetClsVehTest(&cls, &veh, &test);
    showHudWaypoint = (test == 0 && cls == CLASS_A && veh == VEHICLE_HANG_GLIDER) || (test == 1 && cls == CLASS_B && veh == VEHICLE_HANG_GLIDER) ||
                      (test == 2 && cls == CLASS_PILOT && veh == VEHICLE_HANG_GLIDER);
    if (showHudWaypoint) {
        sFerryRadarId = hudAddWaypoint(sFerryPose.m[3][0], sFerryPose.m[3][1], sFerryPose.m[3][2]);
    } else {
        sFerryRadarId = 0xFF;
    }
}

void ferryDeinit(void) {
    if (sFerryObjId == 0xFFFF) {
        return;
    }

    uvDobjModel(sFerryObjId, 0xFFFF);
    sFerryObjId = 0xFFFF;
    proxAnimDeleteCallback(sFerryProxId);
    sFerryProxId = 0;
    if (sFerryRadarId != 0xFF) {
        hud_8031A8E0(sFerryRadarId);
    }
    sFerryRadarId = 0xFF;
}

f32 ferryGetInterval(void) {
    return sFerryInterval / 360.0f;
}

void ferryGetPos(Vec3F* pos) {
    if (sFerryObjId == 0xFFFF) {
        pos->x = 1350.0f;
        pos->y = -2150.0f;
        pos->z = 8.8f;
        return;
    } else {
        pos->x = sFerryPose.m[3][0];
        pos->y = sFerryPose.m[3][1];
        pos->z = sFerryPose.m[3][2];
    }
}

void ferrySetInterval(f32 interval) {
    if (sFerryObjId != 0xFFFF) {
        sFerryInterval = interval * 360.0f;
        ferryUpdatePos();
    }
}

void ferryStateSave(void) {
    sFerryIntervalCopy = sFerryInterval;
}

void ferryStateRestore(void) {
    sFerryInterval = sFerryIntervalCopy;
}
