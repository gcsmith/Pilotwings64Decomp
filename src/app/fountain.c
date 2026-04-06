#include "common.h"
#include <uv_dobj.h>
#include "code_9A960.h"
#include "fountain.h"
#include "hud.h"
#include "macros.h"
#include "proxanim.h"
#include "task.h"

static s32 sFountainObjId = 0xFFFF;
static s32 sFountainRadarId = 0xFF;
static s32 sFountainActive = FALSE;
static Vec3F sFountainInitPos = { -288.0f, -99.0f, 5.75f };

static Mtx4F sFountainPose;
static s32 sFountainProxId;
static s32 sFountainState;
static f32 sFountainScale;
static f32 sFountainScaleCopy;
static s32 sFountainStateCopy;

s32 fountainIsActive(void) {
    return sFountainActive;
}

STATIC_FUNC void fountainUpdatePose(void) {
    Mtx4F scaleMtx;
    Mtx4F pose;

    uvMat4SetIdentity(&scaleMtx);
    uvMat4Scale(&scaleMtx, sFountainScale, sFountainScale, sFountainScale);
    uvDobjProps(sFountainObjId, 3, sFountainScale, 0);
    uvMat4Mul(&pose, &scaleMtx, &sFountainPose);
    uvDobjPosm(sFountainObjId, 0, &pose);
}

STATIC_FUNC void fountainUpdate(void) {
    if (sFountainState == 0) {
        sFountainScale += 0.1f * D_8034F854;
        if (sFountainScale > 0.7f) {
            sFountainScale = 0.7f;
            sFountainState = 2;
        }
    } else if (sFountainState == 1) {
        sFountainScale -= 0.1f * D_8034F854;
        if (sFountainScale < 0.0f) {
            sFountainScale = 0.0f;
            sFountainState = 2;
        }
    }
    fountainUpdatePose();
}

STATIC_FUNC s32 fountainProxEventCb(UNUSED s32 proxId, s32 eventType, UNUSED s32 clientData) {
    switch (eventType) {
    case 0:
        if (sFountainObjId != 0xFFFF) {
            uvDobjState(sFountainObjId, 2);
        }
        break;
    case 2:
        if (sFountainRadarId != 0xFF) {
            hud_8031A874(sFountainRadarId);
        }
        uvDobjState(sFountainObjId, 0);
        break;
    case 3:
        if (sFountainRadarId != 0xFF) {
            hud_8031A874(sFountainRadarId);
        }
        uvDobjState(sFountainObjId, 2);
        break;
    }
    return 0;
}

STATIC_FUNC s32 fountainProxAnimCb(s32 proxId, UNUSED f32 timeout, UNUSED s32 clientData) {
    f32 val;
    s32 sp18;

    sp18 = 0;
    val = proxAnimGetRange(proxId);
    if (val > 350.0f) {
        if (sFountainActive) {
            sFountainState = 1;
            fountainUpdate();
            if (sFountainState == 2) {
                sFountainActive = FALSE;
            }
        } else {
            sp18 = 2;
            uvDobjState(sFountainObjId, 0);
        }
    } else {
        if ((sFountainState == 1) || !sFountainActive) {
            sFountainActive = TRUE;
            sFountainState = 0;
            uvDobjState(sFountainObjId, 2);
        }
        fountainUpdate();
    }
    return sp18;
}

void fountainInit(void) {
    sFountainActive = FALSE;
    sFountainScale = 0.0f;
}

void fountainLoad(void) {
    u16 cls;
    u16 veh;
    u16 test;
    s32 showHudWaypoint;
    Vec3F pos;

    pos = sFountainInitPos;
    sFountainObjId = uvDobjAllocIdx();
    if (sFountainObjId != 0xFFFF) {
        uvDobjModel(sFountainObjId, MODEL_DOUBLE_WATER_FOUNTAIN);
        uvDobjState(sFountainObjId, 0);
        sFountainProxId = proxAnimAddCallback(fountainProxAnimCb, fountainProxEventCb, pos, 350.0f, 0.0f, 5);
        taskGetClsVehTest(&cls, &veh, &test);
        showHudWaypoint = (test == 0 && cls == CLASS_A && veh == VEHICLE_HANG_GLIDER) || (test == 1 && cls == CLASS_B && veh == VEHICLE_HANG_GLIDER) ||
                          (test == 2 && cls == CLASS_PILOT && veh == VEHICLE_HANG_GLIDER);
        if (showHudWaypoint) {
            sFountainRadarId = hudAddWaypoint(-288.0f, -99.0f, 5.75f);
        } else {
            sFountainRadarId = 0xFF;
        }
        uvMat4SetIdentity(&sFountainPose);
        uvMat4LocalTranslate(&sFountainPose, -288.0f, -99.0f, 5.75f);
        fountainUpdatePose();
    }
}

void fountainDeinit(void) {
    if (sFountainObjId == 0xFFFF) {
        return;
    }

    uvDobjModel(sFountainObjId, 0xFFFF);
    sFountainObjId = 0xFFFF;
    proxAnimDeleteCallback(sFountainProxId);
    sFountainProxId = 0;
    if (sFountainRadarId != 0xFF) {
        hud_8031A8E0(sFountainRadarId);
    }
    sFountainRadarId = 0xFF;
}

f32 fountainGetInterval(void) {
    return sFountainScale / 0.7f;
}

void fountainGetPos(Vec3F* pos) {
    pos->x = -288.0f;
    pos->y = -99.0f;
    pos->z = 15.55f;
}

void fountainSetInterval(f32 interval) {
    if (sFountainObjId != 0xFFFF) {
        sFountainScale = interval * 0.7f;
        fountainUpdatePose();
    }
}

void fountainStateSave(void) {
    sFountainScaleCopy = sFountainScale;
    sFountainStateCopy = sFountainState;
}

void fountainStateRestore(void) {
    sFountainScale = sFountainScaleCopy;
    sFountainState = sFountainStateCopy;
}

void fountainInitUpdate(void) {
    fountainStateRestore();
    fountainUpdate();
}
