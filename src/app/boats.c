#include "common.h"
#include <uv_dobj.h>
#include <uv_math.h>
#include <uv_matrix.h>
#include <uv_model.h>
#include <uv_utils.h>
#include "boats.h"
#include "code_9A960.h"
#include "env_sound.h"
#include "level.h"
#include "macros.h"
#include "proxanim.h"

typedef struct {
    s32 objId0;
    s32 modelId;
    s32 objId8;
    s32 partId;
    f32 pathAngle;    // angle on boat's circular path [0-360] (degrees)
    f32 pathVelocity; // angular velocity around boat's circular path (degrees)
    Vec3F pos;
    f32 translateX;
    f32 roll;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    s32 unk40;
    s32 active;
} Boat; // size = 0x48

STATIC_DATA Boat sBoats[2];

// forward declarations
STATIC_FUNC void boatsSetupEnvSound(s32);

STATIC_FUNC void boatsUpdate(s32 boatId) {
    Mtx4F pose;
    Boat* boat;
    Mtx4F modelPose;
    f32 modelRot;

    boat = &sBoats[boatId];
    //! @bug partId is s32, but comparison with float
    if ((f32)boat->partId >= 0.0f) {
        boat->unk38 = (f32)(boat->unk38 - (9.8 * D_8034F854 * 0.75));
        boat->unk34 += boat->unk38 * D_8034F854 * 0.75f;
        if (boat->unk34 <= 0.0f) {
            boat->unk38 = uvRandF_RANLUX() * boat->unk3C;
            boat->unk34 = 0;
        }
        if (boat->unk38 > 0.0f) {
            modelRot = ((2.0f * boat->unk34) / boat->unk30) * boat->unk2C;
            if (boat->unk2C < modelRot) {
                modelRot = boat->unk2C;
            }
        } else {
            modelRot = (boat->unk34 / boat->unk30) * boat->unk2C;
            if (boat->unk2C < modelRot) {
                modelRot = boat->unk2C;
            }
        }
        uvModelGetPosm(boat->modelId, boat->partId, &modelPose);
        if (boat->pathVelocity > 0.0f) {
            uvMat4RotateAxis(&modelPose, modelRot * 0.01745329f, 'x'); // almost DEG_TO_RAD(1)
        } else {
            uvMat4RotateAxis(&modelPose, -modelRot * 0.01745329f, 'x'); // almost DEG_TO_RAD(1)
        }
        uvMat4LocalTranslate(&modelPose, 0.0f, 0.0f, boat->unk34);
        uvDobjPosm(boat->objId0, boat->partId, &modelPose);
    }
    boat->pathAngle += boat->pathVelocity * D_8034F854;
    if (boat->pathAngle > 360.0) {
        boat->pathAngle = (f32)(boat->pathAngle - 360.0);
    }
    uvMat4SetIdentity(&pose);
    uvMat4LocalTranslate(&pose, boat->pos.x, boat->pos.y, boat->pos.z);
    uvMat4RotateAxis(&pose, boat->pathAngle * 0.01745329f, 'z'); // almost DEG_TO_RAD(1)
    uvMat4LocalTranslate(&pose, boat->translateX, 0.0f, 0.0f);

    if (FABS(boat->roll) > 0.0f) {
        uvMat4RotateAxis(&pose, boat->roll * 0.01745329f, 'y'); // almost DEG_TO_RAD(1)
    }
    if (boat->objId0 != 0xFFFF) {
        uvDobjPosm(boat->objId0, 0, &pose);
    }
    if (boat->objId8 != 0xFFFF) {
        uvDobjPosm(boat->objId8, 0, &pose);
    }
}

STATIC_FUNC s32 boatsProxEventCb(UNUSED s32 proxId, s32 eventType, UNUSED s32 clientData) {
    s32 i;
    switch (eventType) {
    case 0:
        break;
    case 2:
        for (i = 0; i < ARRAY_COUNT(sBoats); i++) {
            uvDobjState(sBoats[i].objId0, 0);
        }
        break;
    case 3:
        for (i = 0; i < ARRAY_COUNT(sBoats); i++) {
            uvDobjState(sBoats[i].objId0, 3);
        }
        break;
    }
    return 0;
}

STATIC_FUNC s32 boatsProxAnimCb(s32 proxId, UNUSED f32 timeout, UNUSED s32 clientData) {
    ProxAnim* tmp;
    s32 idx;
    s32 res;
    s32 pad;
    Boat* boat;

    res = 0;
    tmp = proxAnimGetHandle(proxId);
    idx = tmp->clientData;
    boat = &sBoats[idx];
    if (proxAnimGetRange(proxId) > 1500.0f) {
        if (boat->active) {
            boatsUpdate(idx);
            boat->active = FALSE;
        } else {
            res = 2;
        }
    } else {
        if (!boat->active) {
            boat->active = TRUE;
        }
        boatsUpdate(idx);
    }
    return res;
}

void boatsLoadCrescent(void) {
    Boat* boat;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sBoats); i++) {
        boat = &sBoats[i];
        switch (i) {
        case 0:
            boat->objId8 = uvDobjAllocIdx();
            if (boat->objId8 != 0xFFFF) {
                uvDobjModel(boat->objId8, MODEL_BLUE_CUBOID);
                uvDobjState(boat->objId8, 0x22);
            }
            break;
        case 1:
            boat->objId8 = 0xFFFF;
            break;
        }
        boat->objId0 = uvDobjAllocIdx();
        if (boat->objId0 != 0xFFFF) {
            boat->unk3C = 0.0f;
            switch (i) {
            case 0:
                boat->modelId = 3;
                boat->unk3C = 7.0f;
                boat->unk38 = 7.0f;
                boat->unk34 = 0.0f;
                boat->partId = 1;
                boat->pathVelocity = -4.0f;
                boat->unk30 = 1.5f;
                boat->unk2C = 10.0f;
                boat->roll = -5.0f;
                uvDobjModel(boat->objId0, MODEL_YELLOW_SPEED_BOAT);
                uvDobjState(boat->objId0, 3);
                boat->translateX = 400.0f;
                boat->pos.f[0] = 400.0f;
                boat->pos.f[2] = 0.0f;
                boat->pos.f[1] = -300.0f;
                break;
            case 1:
                boat->modelId = 0x29;
                boat->pathVelocity = 2.0f;
                boat->partId = -1;
                boat->roll = 0.0f;
                uvDobjModel(boat->objId0, MODEL_RED_WHITE_BLUE_YACHT);
                uvDobjState(boat->objId0, 3);
                boat->translateX = 275.0f;
                boat->pos.f[2] = 0.0f;
                boat->pos.f[0] = 300.0f;
                boat->pos.f[1] = -200.0f;
                break;
            }
            boat->unk40 = proxAnimAddCallback(boatsProxAnimCb, boatsProxEventCb, boat->pos, 1500.0f, 0.0f, i);
            boatsUpdate(i);
            boatsSetupEnvSound(i);
        }
    }
}

void boatsLoadHoliday(void) {
    Boat* boat;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sBoats); i++) {
        boat = &sBoats[i];
        switch (i) {
        case 0:
            boat->objId8 = uvDobjAllocIdx();
            if (boat->objId8 != 0xFFFF) {
                uvDobjModel(boat->objId8, MODEL_BLUE_CUBOID);
                uvDobjState(boat->objId8, 0x22);
            }
            break;
        case 1:
            boat->objId8 = 0xFFFF;
            break;
        }
        boat->objId0 = uvDobjAllocIdx();
        if (boat->objId0 != 0xFFFF) {
            boat->unk3C = 0.0f;
            switch (i) {
            case 0:
                boat->modelId = 3;
                boat->unk3C = 7.0f;
                boat->unk38 = 7.0f;
                boat->unk34 = 0.0f;
                boat->partId = 1;
                boat->pathVelocity = -4.0f;
                boat->unk30 = 1.5f;
                boat->unk2C = 10.0f;
                boat->roll = -5.0f;
                uvDobjModel(boat->objId0, MODEL_YELLOW_SPEED_BOAT);
                uvDobjState(boat->objId0, 3);
                boat->translateX = 300.0f;
                boat->pos.x = -600.0f;
                boat->pos.y = -600.0f;
                boat->pos.z = 0.0f;
                break;
            case 1:
                boat->modelId = 1;
                boat->pathVelocity = 2.0f;
                boat->partId = -1;
                boat->roll = 15.0f;
                uvDobjModel(boat->objId0, MODEL_WHITE_SAIL_BOAT_WITH_RED_LOGO);
                uvDobjState(boat->objId0, 3);
                boat->translateX = 300.0f;
                boat->pos.z = 0.0f;
                boat->pos.x = 700.0f;
                boat->pos.y = -500.0f;
                break;
            }
            boat->unk40 = proxAnimAddCallback(boatsProxAnimCb, boatsProxEventCb, boat->pos, 1500.0f, 0.0f, i);
            boatsUpdate(i);
            boatsSetupEnvSound(i);
        }
    }
}

STATIC_FUNC void boatsSetupEnvSound(s32 boatId) {
    LevelESND envSnd;
    Boat* boat;
    s32 valid;

    boat = &sBoats[boatId];
    if (boat->objId0 != 0xFFFF) {
        if (boat->modelId == 0x29) {
            envSnd.sndId = 0x16;
            envSnd.unk5C = 1.6f;
        } else if (boat->modelId == 3) {
            envSnd.sndId = 0x15;
            envSnd.unk5C = 2.0f;
        } else {
            return;
        }
        valid = boatsGetPose(boatId, &envSnd.unk0);
        envSnd.unk64 = 0;
        envSnd.unk74 = 8;
        envSnd.unk70 = 0;
        envSnd.unk60 = 1.0f;
        envSnd.unk68 = 0.0f;
        envSnd.unk6C = 200.0f;
        if (valid) {
            envSoundLoad(&envSnd);
        }
    }
}

s32 boatsGetPose(s32 boatId, Mtx4F* pose) {
    s32 objId;
    objId = sBoats[boatId].objId0;
    if (objId == 0xFFFF) {
        return FALSE;
    } else {
        uvDobjGetPosm(objId, 0, pose);
        return TRUE;
    }
}

void boatsDeinit(void) {
    s32 i;
    for (i = 0; i < ARRAY_COUNT(sBoats); i++) {
        if (sBoats[i].objId8 != 0xFFFF) {
            uvDobjModel(sBoats[i].objId8, MODEL_WORLD);
            sBoats[i].objId8 = 0xFFFF;
        }
        if (sBoats[i].objId0 != 0xFFFF) {
            uvDobjModel(sBoats[i].objId0, MODEL_WORLD);
            sBoats[i].objId0 = 0xFFFF;
            proxAnimDeleteCallback(sBoats[i].unk40);
        }
    }
}

void boatsInit(void) {
    s32 i;
    for (i = 0; i < ARRAY_COUNT(sBoats); i++) {
        sBoats[i].pathAngle = 0.0f;
        sBoats[i].objId0 = 0xFFFF;
        sBoats[i].objId8 = 0xFFFF;
    }
}

void boatsGetObjData(s32 boatId, s32* objId, f32* interval, Vec3F* pos) {
    Mtx4F sp28;
    Boat* boat;

    boat = &sBoats[boatId];
    if (boat->objId0 != 0xFFFF) {
        *objId = boat->objId0;
        *interval = boat->pathAngle / 360.0f;
        uvDobjGetPosm(*objId, 0, &sp28);
        pos->x = sp28.m[3][0];
        pos->y = sp28.m[3][1];
        pos->z = sp28.m[3][2];
    } else {
        *objId = 0xFFFF;
        *interval = 0.0f;
        pos->x = 0.0f;
        pos->y = 0.0f;
        pos->z = 0.0f;
    }
}

void boatsUpdateInterval(s32 boatId, f32 interval) {
    if (sBoats[boatId].objId0 != 0xFFFF) {
        uvDobjState(sBoats[boatId].objId0, 3);
        if (sBoats[boatId].objId8 != 0xFFFF) {
            uvDobjState(sBoats[boatId].objId8, 0x22);
        }
        sBoats[boatId].pathAngle = (f32)(interval * 360.0f);
        sBoats[boatId].unk34 = 1.0f;
        sBoats[boatId].unk38 = (f32)(D_8034F854 * 9.8 * 0.75);
        boatsUpdate(boatId);
    }
}
