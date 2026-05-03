#include "common.h"
#include <uv_anim.h>
#include <uv_dobj.h>
#include <uv_matrix.h>
#include <uv_model.h>
#include "code_9A960.h"
#include "hud.h"
#include "proxanim.h"
#include "task.h"
#include "whale.h"

// .data
STATIC_DATA s32 sWhaleObjId0 = 0xFFFF;
STATIC_DATA s32 sWhaleObjId4 = 0xFFFF;
STATIC_DATA s32 sWhaleRadarId = 0xFF;
STATIC_DATA s32 sWhaleProxId = 0;
STATIC_DATA f32 sWhalePathAngle = 0.0f;
STATIC_DATA f32 sWhaleDepth = 0;
STATIC_DATA s32 sWhaleActive = FALSE;
STATIC_DATA Vec3F sWhalePos = { 750.0f, 100.0f, 4.5f };

// .bss
STATIC_DATA Mtx4F sWhaleXlatMtx0;
STATIC_DATA Mtx4F sWhaleXlatMtx4;
STATIC_DATA Mtx4F sWhalePose;
STATIC_DATA f32 sWhaleState; //! @bug, f32 used as discrete state
STATIC_DATA f32 sWhaleDepthCopy;
STATIC_DATA f32 sWhalePathAngleCopy;
STATIC_DATA s32 sWhaleStateCopy;

s32 whaleIsActive(void) {
    return sWhaleActive;
}

STATIC_FUNC void whaleUpdate(void) {
    Mtx4F spF0;
    Mtx4F pose;
    Mtx4F pathMtx;
    Mtx4F sp30;
    s32 v1;
    s32 v0;
    f32 scale;

    uvMat4SetIdentity(&pathMtx);
    uvMat4RotateAxis(&pathMtx, sWhalePathAngle * 0.01745329f, 'z'); // almost DEG_TO_RAD(1)
    uvMat4Mul(&pose, &sWhaleXlatMtx0, &pathMtx);
    if (sWhaleObjId4 != 0xFFFF) {
        uvMat4Mul(&sWhalePose, &pose, &sWhaleXlatMtx4);
        uvDobjPosm(sWhaleObjId4, 0, &sWhalePose);
    }
    uvMat4SetIdentity(&spF0);
    uvMat4LocalTranslate(&spF0, 0.0f, 0.0f, sWhaleDepth);
    uvMat4Mul(&sp30, &pose, &spF0);
    uvMat4Mul(&sWhalePose, &sp30, &sWhaleXlatMtx4);
    uvDobjPosm(sWhaleObjId0, 0, &sWhalePose);

    v0 = (sWhalePathAngle + 15.0f) / 30;
    v1 = (s32)(sWhalePathAngle + 15.0f) % 30;
    if (v0 % 2) {
        scale = (30.0f - v1) / 30.0f;
    } else {
        scale = v1 / 30.0f;
    }
    func_80200B00(sWhaleObjId0, 0, 1.0f - scale);
    if (sWhaleRadarId != 0xFF) {
        hudMoveWaypoint(sWhaleRadarId, sWhalePose.m[3][0], sWhalePose.m[3][1], sWhalePose.m[3][2]);
    }
    uvModelGetPosm(MODEL_GREY_WHALE, 1, &pose);
    uvMat4Scale(&pose, 2.0 * scale, 2.0 * scale, 2.0 * scale);
    uvDobjPosm(sWhaleObjId0, 1, &pose);
}

STATIC_FUNC void whaleStateMachine(void) {
    if (sWhaleState == 1.0f) {
        sWhaleDepth += 4.0f * D_8034F854;
        if (sWhaleDepth > 0 /*.0f*/) {
            sWhaleState = 0.0f;
            sWhaleDepth = 0 /*.0f*/;
        }
        sWhalePathAngle += 10.0f * D_8034F854;
        if (sWhalePathAngle > 360.0f) {
            sWhalePathAngle -= 360.0f;
        }
        whaleUpdate();
        return;
    }
    if (sWhaleState == 2.0f) {
        sWhaleDepth -= 4.0f * D_8034F854;
        if (sWhaleDepth < -25.0f) {
            sWhaleState = 3.0f;
        }
        sWhalePathAngle += 10.0f * D_8034F854;
        if (sWhalePathAngle > 360.0f) {
            sWhalePathAngle -= 360.0f;
        }
        whaleUpdate();
        return;
    }
    if (sWhaleState == 0.0f) {
        sWhalePathAngle += 10.0f * D_8034F854;
        if (sWhalePathAngle > 360.0f) {
            sWhalePathAngle -= 360.0f;
        }
        whaleUpdate();
    }
}

STATIC_FUNC s32 whaleProxEventCb(UNUSED s32 proxId, s32 eventType, UNUSED s32 clientData) {
    switch (eventType) {
    case 0:
        uvDobjState(sWhaleObjId0, 3);
        if (sWhaleObjId4 != 0xFFFF) {
            uvDobjState(sWhaleObjId4, 0x22);
        }
        uvMat4SetIdentity(&sWhaleXlatMtx0);
        uvMat4LocalTranslate(&sWhaleXlatMtx0, 75.0f, 0.0f, 0.0f);
        uvMat4SetIdentity(&sWhaleXlatMtx4);
        uvMat4LocalTranslate(&sWhaleXlatMtx4, 750.0f, 100.0f, 4.5f);
        whaleUpdate();
        break;
    case 2:
        uvDobjState(sWhaleObjId0, 0);
        if (sWhaleObjId4 != 0xFFFF) {
            uvDobjState(sWhaleObjId4, 0);
        }
        if (sWhaleRadarId != 0xFF) {
            hud_8031A874(sWhaleRadarId);
        }
        break;
    case 3:
        uvDobjState(sWhaleObjId0, 3);
        if (sWhaleObjId4 != 0xFFFF) {
            uvDobjState(sWhaleObjId4, 0x22);
        }
        if (sWhaleRadarId != 0xFF) {
            hud_8031A874(sWhaleRadarId);
        }
        break;
    }
    return 0;
}

STATIC_FUNC s32 whaleProxAnimCb(s32 proxId, UNUSED f32 timeout, UNUSED s32 clientData) {
    f32 dist;
    s32 ret;

    ret = 0;
    dist = proxAnimGetRange(proxId);
    if (dist > 450.0f) {
        if (sWhaleActive) {
            sWhaleState = 2.0f;
            whaleStateMachine();
            if (sWhaleState == 3.0f) {
                sWhaleActive = FALSE;
            }
        } else {
            ret = 2;
            uvDobjState(sWhaleObjId0, 0);
        }
    } else {
        if ((sWhaleState == 2.0f) || !sWhaleActive) {
            sWhaleActive = TRUE;
            sWhaleState = 1.0f;
            uvDobjState(sWhaleObjId0, 3);
        }
        whaleStateMachine();
    }
    return ret;
}

void whaleLoad(void) {
    u16 class;
    u16 veh;
    u16 test;
    s32 showHudWaypoint;
    Vec3F pos = sWhalePos;

    sWhaleObjId4 = uvDobjAllocIdx();
    if (sWhaleObjId4 != 0xFFFF) {
        uvDobjModel(sWhaleObjId4, MODEL_BROWN_BOX);
        uvDobjState(sWhaleObjId4, 0);
    }
    sWhaleObjId0 = uvDobjAllocIdx();
    if (sWhaleObjId0 == 0xFFFF) {
        if (sWhaleObjId4 != 0xFFFF) {
            uvDobjModel(sWhaleObjId4, MODEL_WORLD);
            sWhaleObjId4 = 0xFFFF;
        }
    } else {
        uvDobjModel(sWhaleObjId0, MODEL_GREY_WHALE);
        uvDobjState(sWhaleObjId0, 0);
        sWhaleProxId = proxAnimAddCallback(whaleProxAnimCb, whaleProxEventCb, pos, 450.0f, 0.0f, 4);
        sWhalePathAngle = 0.0f;
        taskGetClsVehTest(&class, &veh, &test);
        showHudWaypoint = (test == 0 && class == CLASS_A && veh == VEHICLE_HANG_GLIDER) || (test == 1 && class == CLASS_B && veh == VEHICLE_HANG_GLIDER) ||
                          (test == 2 && class == CLASS_PILOT && veh == VEHICLE_HANG_GLIDER);
        if (showHudWaypoint) {
            sWhaleRadarId = hudAddWaypoint(750.0f, 100.0f, 4.5f);
        } else {
            sWhaleRadarId = 0xFF;
        }
    }
}

void whaleDeinit(void) {
    if (sWhaleObjId0 == 0xFFFF) {
        return;
    }

    uvDobjModel(sWhaleObjId0, MODEL_WORLD);
    sWhaleObjId0 = 0xFFFF;
    if (sWhaleObjId4 != 0xFFFF) {
        uvDobjModel(sWhaleObjId4, MODEL_WORLD);
        sWhaleObjId4 = 0xFFFF;
    }
    proxAnimDeleteCallback(sWhaleProxId);
    sWhaleProxId = 0;
    if (sWhaleRadarId != 0xFF) {
        hud_8031A8E0(sWhaleRadarId);
    }
    sWhaleRadarId = 0xFF;
}

f32 whaleGetInterval(void) {
    return sWhalePathAngle / 360.0f;
}

void whaleGetPos(Vec3F* pos) {
    if (sWhaleObjId0 == 0xFFFF) {
        pos->x = 825.0f;
        pos->y = 100.0f;
        pos->z = 4.5f;
    } else {
        pos->x = sWhalePose.m[3][0];
        pos->y = sWhalePose.m[3][1];
        pos->z = sWhalePose.m[3][2];
    }
}

void whaleSetInterval(f32 interval) {
    if (sWhaleObjId0 != 0xFFFF) {
        sWhaleState = 0.0f;
        sWhalePathAngle = interval * 360.0f;
        sWhaleDepth = 0 /*.0f*/;
        whaleUpdate();
    }
}

void whaleInit(void) {
    sWhaleState = 1.0f;
    sWhaleActive = FALSE;
    sWhaleDepth = -25.0f;
    sWhalePathAngle = 0.0f;
}

void whaleStateSave(void) {
    sWhaleDepthCopy = sWhaleDepth;
    sWhalePathAngleCopy = sWhalePathAngle;
    sWhaleStateCopy = sWhaleState;
}

void whaleStateRestore(void) {
    sWhaleDepth = sWhaleDepthCopy;
    sWhalePathAngle = sWhalePathAngleCopy;
    sWhaleState = sWhaleStateCopy;
}
