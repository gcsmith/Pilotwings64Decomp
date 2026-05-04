#include "common.h"
#include <uv_dobj.h>
#include <uv_fx.h>
#include <uv_model.h>
#include <uv_vector.h>
#include "code_9A960.h"
#include "hud.h"
#include "missi.h"
#include "proxanim.h"
#include "snd.h"
#include "task.h"

STATIC_DATA s32 sMissiObjId = 0xFFFF;
STATIC_DATA s32 sMissiRadarIdLS = 0xFF;
STATIC_DATA s32 sMissiProxIdLS = 0;
STATIC_DATA f32 sMissiInterval = 180.0f;
STATIC_DATA f32 sMissiDepth = 0.0f;
STATIC_DATA s32 sMissiActive = FALSE;
STATIC_DATA s32 sMissiStateLoaded = TRUE;
STATIC_DATA s32 sMissiSoundPlayed = FALSE;
STATIC_DATA Vec3F sMissiInitPosLS = { 1725.0f, -659.0f, 28.0f };
STATIC_DATA s32 padD_8034F88C = 0;

STATIC_DATA Mtx4F sMissiAdjustment;
STATIC_DATA Mtx4F sMissiTranslate;
STATIC_DATA Mtx4F sMissiPose;
STATIC_DATA f32 sMissiState; //! @bug this state should be s32
STATIC_DATA f32 sMissiDepthCopy;
STATIC_DATA f32 sMissiIntervalCopy;
STATIC_DATA s32 sMissiStateCopy;

s32 missiIsActive(void) {
    return sMissiActive;
}

STATIC_FUNC void missiUpdatePos(void) {
    Mtx4F depthMtx;
    Mtx4F adjMtx;
    Mtx4F pathMtx;
    Mtx4F depthAdjMtx;
    f32 depthOffset;
    s32 tmpDiv;
    f32 depth;
    s32 temp_hi;
    s32 tmpInt;

    uvMat4SetIdentity(&pathMtx);
    uvMat4RotateAxis(&pathMtx, sMissiInterval * 0.01745329f, 'z');
    uvMat4Mul(&adjMtx, &sMissiAdjustment, &pathMtx);
    tmpDiv = (s32)((sMissiInterval + 30.0f) / 30);
    temp_hi = (s32)(sMissiInterval + 30.0f) % 30;
    if (tmpDiv % 2) {
        depth = (30.0f - temp_hi) / 30.0f;
    } else {
        depth = temp_hi / 30.0f;
    }
    depthOffset = 2.0f * depth;
    uvMat4SetIdentity(&depthMtx);
    uvMat4LocalTranslate(&depthMtx, 0.0f, 0.0f, sMissiDepth + depthOffset);
    uvMat4Mul(&depthAdjMtx, &adjMtx, &depthMtx);
    uvMat4Mul(&sMissiPose, &depthAdjMtx, &sMissiTranslate);
    uvDobjPosm(sMissiObjId, 0, &sMissiPose);
    if (sMissiRadarIdLS != 0xFF) {
        hudMoveWaypoint(sMissiRadarIdLS, sMissiPose.m[3][0], sMissiPose.m[3][1], sMissiPose.m[3][2]);
    }
}

STATIC_FUNC void missiUpdate(void) {
    if (sMissiState == 1.0f) {
        sMissiDepth += 4.0f * D_8034F854;
        if (sMissiDepth > 25.0f) {
            sMissiDepth = 25.0f;
            sMissiState = 0.0f;
        }
        sMissiInterval += 7.0f * D_8034F854;
        if (sMissiInterval > 360.0f) {
            sMissiInterval -= 360.0f;
        }
        missiUpdatePos();
    } else if (sMissiState == 2.0f) {
        sMissiDepth -= 4.0f * D_8034F854;
        if (sMissiDepth < 0.0f) {
            sMissiState = 3.0f;
        }
        sMissiInterval += 7.0f * D_8034F854;
        if (sMissiInterval > 360.0f) {
            sMissiInterval -= 360.0f;
        }
        missiUpdatePos();
    } else if (sMissiState == 0.0f) {
        sMissiInterval += 7.0f * D_8034F854;
        if (sMissiInterval > 360.0f) {
            sMissiInterval -= 360.0f;
        }
        missiUpdatePos();
    }
}

STATIC_FUNC s32 missiEventCbLStates(UNUSED s32 proxId, s32 eventType, UNUSED s32 clientData) {
    Mtx4F rotMtx;
    Mtx4F xlatMtx;

    switch (eventType) {
    case 0:
        uvDobjState(sMissiObjId, 3);
        uvMat4SetIdentity(&rotMtx);
        uvMat4RotateAxis(&rotMtx, 3.1415923f, 'z');
        uvMat4SetIdentity(&xlatMtx);
        uvMat4LocalTranslate(&xlatMtx, 20.0f, 0.0f, 0.0f);
        uvMat4Mul(&sMissiAdjustment, &rotMtx, &xlatMtx);
        uvMat4SetIdentity(&sMissiTranslate);
        uvMat4LocalTranslate(&sMissiTranslate, 1725.0f, -659.0f, 28.0f);
        missiUpdatePos();
        break;
    case 2:
        uvDobjState(sMissiObjId, 0);
        if (sMissiRadarIdLS != 0xFF) {
            hud_8031A874(sMissiRadarIdLS);
        }
        break;
    case 3:
        uvDobjState(sMissiObjId, 3);
        if (sMissiRadarIdLS != 0xFF) {
            hud_8031A874(sMissiRadarIdLS);
        }
        break;
    }
    return 0;
}

STATIC_FUNC s32 missiAnimCbLStates(s32 proxId, UNUSED f32 timeout, UNUSED s32 clientData) {
    f32 range;
    s32 ret;

    ret = 0;
    range = proxAnimGetRange(proxId);
    if (range > 500.0f) {
        sMissiSoundPlayed = FALSE;
        if (sMissiActive) {
            sMissiState = 2.0f;
            missiUpdate();
            if (sMissiState == 3.0f) {
                sMissiActive = FALSE;
            }
        } else {
            ret = 2;
            uvDobjState(sMissiObjId, 0);
        }
    } else {
        if ((sMissiState == 0.0f) && (range < 250.0) && !sMissiSoundPlayed && sMissiStateLoaded) {
            sndPlaySfx(SFX_MISSI_ROAR);
            sMissiSoundPlayed = TRUE;
        }
        if ((sMissiState == 2.0f) || !sMissiActive) {
            sMissiState = 1.0f;
            uvDobjState(sMissiObjId, 3);
            sMissiActive = TRUE;
        }
        missiUpdate();
    }
    return ret;
}

void missiLoadLStates(void) {
    u16 cls;
    u16 veh;
    u16 test;
    s32 showHudWaypoint;
    Vec3F pos;

    pos = sMissiInitPosLS;
    sMissiObjId = uvDobjAllocIdx();
    if (sMissiObjId != 0xFFFF) {
        uvDobjModel(sMissiObjId, MODEL_NESSIES_HEAD);
        uvDobjState(sMissiObjId, 0);
        sMissiProxIdLS = proxAnimAddCallback(missiAnimCbLStates, missiEventCbLStates, pos, 500.0f, 0.0f, 3);
        taskGetClsVehTest(&cls, &veh, &test);
        showHudWaypoint = (test == 0 && cls == CLASS_A && veh == VEHICLE_HANG_GLIDER) || (test == 1 && cls == CLASS_B && veh == VEHICLE_HANG_GLIDER) ||
                          (test == 2 && cls == CLASS_PILOT && veh == VEHICLE_HANG_GLIDER);
        if (showHudWaypoint) {
            sMissiRadarIdLS = hudAddWaypoint(1725.0f, -659.0f, 28.0f);
            return;
        }
        sMissiRadarIdLS = 0xFF;
    }
}

void missiDeinitLStates(void) {
    if (sMissiObjId == 0xFFFF) {
        return;
    }

    uvDobjModel(sMissiObjId, 0xFFFF);
    sMissiObjId = 0xFFFF;
    proxAnimDeleteCallback(sMissiProxIdLS);
    sMissiProxIdLS = 0;
    if (sMissiRadarIdLS != 0xFF) {
        hud_8031A8E0(sMissiRadarIdLS);
    }
    sMissiRadarIdLS = 0xFF;
}

f32 missiGetInterval(void) {
    return sMissiInterval / 360.0f;
}

void missiGetPos(Vec3F* pos) {
    if (sMissiObjId == 0xFFFF) {
        pos->x = 1745.0f;
        pos->y = -659.0f;
        pos->z = 57.0f;
    } else {
        pos->x = sMissiPose.m[3][0];
        pos->y = sMissiPose.m[3][1];
        pos->z = sMissiPose.m[3][2] + 2.0f;
    }
}

void missiSetInterval(f32 interval) {
    if (sMissiObjId == 0xFFFF) {
        return;
    }
    sMissiState = 0.0f;
    sMissiInterval = interval * 360.0f;
    sMissiDepth = 25.0f;
    missiUpdatePos();
}

void missiInit(void) {
    sMissiState = 1.0f;
    sMissiActive = FALSE;
    sMissiDepth = 0.0f;
    sMissiInterval = 180.0f;
    sMissiStateLoaded = TRUE;
    sMissiSoundPlayed = FALSE;
}

void missiStateSave(void) {
    sMissiDepthCopy = sMissiDepth;
    sMissiIntervalCopy = sMissiInterval;
    sMissiStateCopy = (s32)sMissiState;
    sMissiStateLoaded = FALSE;
}

void missiStateRestore(void) {
    sMissiDepth = sMissiDepthCopy;
    sMissiInterval = sMissiIntervalCopy;
    sMissiState = (f32)sMissiStateCopy;
    sMissiStateLoaded = TRUE;
}
