#include "common.h"
#include <uv_janim.h>
#include <uv_dobj.h>
#include <uv_matrix.h>
#include <uv_model.h>
#include "code_9A960.h"
#include "hud.h"
#include "proxanim.h"
#include "task.h"
#include "whale.h"

// .data
static s32 sWhaleObjId0 = 0xFFFF;
static s32 sWhaleObjId4 = 0xFFFF;
static s32 sWhaleRadarId = 0xFF;
static s32 sWhaleProxId = 0;
static f32 sWhalePathAngle = 0.0f;
static f32 sWhaleDepth = 0;
static s32 sWhaleActive = FALSE;
static Vec3F sWhalePos = { 750.0f, 100.0f, 4.5f };

// .bss
static Mtx4F D_8037F380;
static Mtx4F D_8037F3C0;
static Mtx4F sWhalePose;
static f32 sWhaleState; //! @bug, f32 used as discrete state
static f32 sWhaleDepthCopy;
static f32 sWhalePathAngleCopy;
static s32 sWhaleStateCopy;

s32 whaleIsActive(void) {
    return sWhaleActive;
}

STATIC_FUNC void whaleUpdate(void) {
    Mtx4F spF0;
    Mtx4F pose;
    Mtx4F sp70;
    Mtx4F sp30;
    s32 v1;
    s32 v0;
    f32 scale;

    uvMat4SetIdentity(&sp70);
    uvMat4RotateAxis(&sp70, sWhalePathAngle * 0.01745329f, 'z'); // almost DEG_TO_RAD(1)
    uvMat4Mul(&pose, &D_8037F380, &sp70);
    if (sWhaleObjId4 != 0xFFFF) {
        uvMat4Mul(&sWhalePose, &pose, &D_8037F3C0);
        uvDobjPosm(sWhaleObjId4, 0, &sWhalePose);
    }
    uvMat4SetIdentity(&spF0);
    uvMat4LocalTranslate(&spF0, 0.0f, 0.0f, sWhaleDepth);
    uvMat4Mul(&sp30, &pose, &spF0);
    uvMat4Mul(&sWhalePose, &sp30, &D_8037F3C0);
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

STATIC_FUNC s32 whale_8034BC68(s32 arg0, s32 arg1, s32 arg2) {
    switch (arg1) {
    case 0:
        uvDobjState(sWhaleObjId0, 3);
        if (sWhaleObjId4 != 0xFFFF) {
            uvDobjState(sWhaleObjId4, 0x22);
        }
        uvMat4SetIdentity(&D_8037F380);
        uvMat4LocalTranslate(&D_8037F380, 75.0f, 0.0f, 0.0f);
        uvMat4SetIdentity(&D_8037F3C0);
        uvMat4LocalTranslate(&D_8037F3C0, 750.0f, 100.0f, 4.5f);
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

STATIC_FUNC s32 whale_8034BDCC(s32 arg0, s32 arg1, s32 arg2) {
    s32 pad;
    s32 sp18;

    sp18 = 0;
    if (func_80321420(arg0) > 450.0f) {
        if (sWhaleActive) {
            sWhaleState = 2.0f;
            whaleStateMachine();
            if (sWhaleState == 3.0f) {
                sWhaleActive = FALSE;
            }
        } else {
            sp18 = 2;
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
    return sp18;
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
        sWhaleProxId = func_80321210(whale_8034BDCC, whale_8034BC68, pos, 450.0f, 0.0f, 4);
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
    func_803212DC(sWhaleProxId);
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
