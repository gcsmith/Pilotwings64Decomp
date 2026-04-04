#include "app/task.h"
#include "common.h"
#include <uv_dobj.h>
#include <uv_vector.h>
#include "code_9A960.h"
#include "game.h"
#include "glider_toys.h"
#include "proxanim.h"

typedef struct {
    s32 objId;
    f32 pathAngle;
    f32 pathVelocity;
    Vec3F pos;
    f32 translateX;
    s32 proxId;
    s32 active;
} GliderToy; // size = 0x24

static GliderToy sGliderToys[4];

STATIC_FUNC void gliderToyUpdate(s32 idx) {
    Mtx4F pose;
    GliderToy* glider;

    glider = &sGliderToys[idx];
    glider->pathAngle += glider->pathVelocity * D_8034F854;
    if (glider->pathAngle > 360.0) {
        glider->pathAngle = (f32)(glider->pathAngle - 360.0);
    }
    uvMat4SetIdentity(&pose);
    uvMat4LocalTranslate(&pose, glider->pos.x, glider->pos.y, glider->pos.z);
    uvMat4RotateAxis(&pose, glider->pathAngle * 0.01745329f, 'z'); // DEG_TO_RAD(1)
    uvMat4LocalTranslate(&pose, glider->translateX, 0.0f, 0.0f);
    uvMat4RotateAxis(&pose, -0.26179937f, 'y'); // DEG_TO_RAD(15)
    uvDobjPosm(glider->objId, 0, &pose);
}

STATIC_FUNC s32 gliderToyProxEventCb(UNUSED s32 proxId, s32 eventType, UNUSED s32 clientData) {
    GliderToy* glider;
    s32 i;

    switch (eventType) {
    case 0:
        break;
    case 2:
        for (i = 0; i < 4; i++) {
            glider = &sGliderToys[i];
            if (glider->objId != 0xFFFF) {
                uvDobjState(glider->objId, 0);
            }
        }
        break;
    case 3:
        for (i = 0; i < 4; i++) {
            glider = &sGliderToys[i];
            if (glider->objId != 0xFFFF) {
                uvDobjState(glider->objId, 2);
            }
        }
        break;
    }
    return 0;
}

STATIC_FUNC s32 gliderToyProxAnimCb(s32 proxId, UNUSED f32 timeout, UNUSED s32 clientData) {
    GliderToy* glider;
    s32 ret;
    s32 idx;
    f32 dist;

    ret = 0;
    idx = proxAnimGetHandle(proxId)->clientData;
    dist = proxAnimGetRange(proxId);
    if (dist > 2500.0f) {
        glider = &sGliderToys[idx];
        if (glider->active) {
            gliderToyUpdate(idx);
            glider->active = FALSE;
        } else {
            ret = 2;
            if (glider->objId != 0xFFFF) {
                uvDobjState(glider->objId, 0);
            }
        }
    } else {
        glider = &sGliderToys[idx];
        if (!glider->active) {
            glider->active = TRUE;
            if (glider->objId != 0xFFFF) {
                uvDobjState(glider->objId, 2);
            }
        }
        gliderToyUpdate(idx);
    }
    return ret;
}

STATIC_FUNC s32 gliderToyModelLookup(s32 idx) {
    Unk80362690_Unk0* unkC;
    unkC = &D_80362690->unkC[D_80362690->unk9C];
    switch (unkC->pilot) {
    case PILOT_LARK:
        switch (idx) {
        case 0:
            return MODEL_HG_GOOSE_LOWPOLY;
        case 1:
            return MODEL_HG_HAWK_LOWPOLY;
        case 2:
            return MODEL_HG_KIWI_LOWPOLY;
        case 3:
            return MODEL_HG_IBIS_LOWPOLY;
        case 4:
            return MODEL_HG_ROBIN_LOWPOLY;
        }
        break;
    case PILOT_GOOSE:
        switch (idx) {
        case 0:
            return MODEL_HG_LARK_LOWPOLY;
        case 1:
            return MODEL_HG_HAWK_LOWPOLY;
        case 2:
            return MODEL_HG_KIWI_LOWPOLY;
        case 3:
            return MODEL_HG_IBIS_LOWPOLY;
        case 4:
            return MODEL_HG_ROBIN_LOWPOLY;
        }
        break;
    case PILOT_HAWK:
        switch (idx) {
        case 0:
            return MODEL_HG_LARK_LOWPOLY;
        case 1:
            return MODEL_HG_GOOSE_LOWPOLY;
        case 2:
            return MODEL_HG_KIWI_LOWPOLY;
        case 3:
            return MODEL_HG_IBIS_LOWPOLY;
        case 4:
            return MODEL_HG_ROBIN_LOWPOLY;
        }
        break;
    case PILOT_KIWI:
        switch (idx) {
        case 0:
            return MODEL_HG_LARK_LOWPOLY;
        case 1:
            return MODEL_HG_GOOSE_LOWPOLY;
        case 2:
            return MODEL_HG_HAWK_LOWPOLY;
        case 3:
            return MODEL_HG_IBIS_LOWPOLY;
        case 4:
            return MODEL_HG_ROBIN_LOWPOLY;
        }
        break;
    case PILOT_IBIS:
        switch (idx) {
        case 0:
            return MODEL_HG_LARK_LOWPOLY;
        case 1:
            return MODEL_HG_GOOSE_LOWPOLY;
        case 2:
            return MODEL_HG_HAWK_LOWPOLY;
        case 3:
            return MODEL_HG_KIWI_LOWPOLY;
        case 4:
            return MODEL_HG_ROBIN_LOWPOLY;
        }
        break;
    case PILOT_ROBIN:
        switch (idx) {
        case 0:
            return MODEL_HG_LARK_LOWPOLY;
        case 1:
            return MODEL_HG_GOOSE_LOWPOLY;
        case 2:
            return MODEL_HG_HAWK_LOWPOLY;
        case 3:
            return MODEL_HG_KIWI_LOWPOLY;
        case 4:
            return MODEL_HG_IBIS_LOWPOLY;
        }
        break;
    }
    return 0;
}

void gliderToyLoadCrescent(void) {
    GliderToy* glider;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sGliderToys); i++) {
        sGliderToys[i].objId = 0xFFFF;
    }

    for (i = 0; i < ARRAY_COUNT(sGliderToys) - 1; i++) {
        glider = &sGliderToys[i];
        glider->objId = uvDobjAllocIdx();
        if (glider->objId != 0xFFFF) {
            switch (i) {
            case 0:
                glider->pathVelocity = 10.0f;
                uvDobjModel(glider->objId, gliderToyModelLookup(0));
                uvDobjState(glider->objId, 2);
                glider->translateX = 220.0f;
                glider->pos.x = -891.24f;
                glider->pos.y = 602.16f;
                glider->pos.z = 450.0f;
                break;
            case 1:
                glider->pathVelocity = 18.0f;
                uvDobjModel(glider->objId, gliderToyModelLookup(1));
                uvDobjState(glider->objId, 2);
                glider->translateX = 70.0f;
                glider->pos.x = 1100.06f;
                glider->pos.y = 686.22f;
                glider->pos.z = 250.0f;
                break;
            case 2:
                glider->pathVelocity = 18.0f;
                uvDobjModel(glider->objId, gliderToyModelLookup(2));
                uvDobjState(glider->objId, 2);
                glider->translateX = 90.0f;
                glider->pos.x = 1050.06f;
                glider->pos.y = 686.22f;
                glider->pos.z = 265.0f;
                break;
            }
            glider->proxId = proxAnimAddCallback(gliderToyProxAnimCb, gliderToyProxEventCb, glider->pos, 2500.0f, 0.0f, i);
            gliderToyUpdate(i);
        }
    }
}

void gliderToyLoadLStates(void) {
    GliderToy* glider;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sGliderToys); i++) {
        sGliderToys[i].objId = 0xFFFF;
    }

    for (i = 0; i < ARRAY_COUNT(sGliderToys); i++) {
        glider = &sGliderToys[i];
        glider->objId = uvDobjAllocIdx();
        if (glider->objId != 0xFFFF) {
            switch (i) {
            case 0:
                glider->pathVelocity = 17.0f;
                uvDobjModel(glider->objId, gliderToyModelLookup(0));
                uvDobjState(glider->objId, 2);
                glider->translateX = 30.0f;
                glider->pos.x = 1666.32f;
                glider->pos.y = -1099.06f;
                glider->pos.z = 100.0f;
                break;
            case 1:
                glider->pathVelocity = 13.0f;
                uvDobjModel(glider->objId, gliderToyModelLookup(1));
                uvDobjState(glider->objId, 2);
                glider->translateX = 60.0f;
                glider->pos.x = 3293.09f;
                glider->pos.y = 931.19f;
                glider->pos.z = 150.0f;
                break;
            case 2:
                glider->pathVelocity = 18.0f;
                uvDobjModel(glider->objId, gliderToyModelLookup(2));
                uvDobjState(glider->objId, 2);
                glider->translateX = 30.0f;
                glider->pos.x = -2294.23f;
                glider->pos.y = -791.48f;
                glider->pos.z = 150.0f;
                break;
            case 3:
                glider->pathVelocity = 18.0f;
                uvDobjModel(glider->objId, gliderToyModelLookup(3));
                uvDobjState(glider->objId, 2);
                glider->translateX = 50.0f;
                glider->pos.x = -2290.23f;
                glider->pos.y = -791.48f;
                glider->pos.z = 170.0f;
                break;
            }
            glider->proxId = proxAnimAddCallback(gliderToyProxAnimCb, gliderToyProxEventCb, glider->pos, 2500.0f, 0.0f, i);
            gliderToyUpdate(i);
        }
    }
}

void gliderToyLoadHoliday(void) {
    GliderToy* glider;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sGliderToys); i++) {
        sGliderToys[i].objId = 0xFFFF;
    }

    for (i = 0; i < ARRAY_COUNT(sGliderToys) - 1; i++) {
        glider = &sGliderToys[i];
        glider->objId = uvDobjAllocIdx();
        if (glider->objId != 0xFFFF) {
            switch (i) {
            case 0:
                glider->pathVelocity = 20.0f;
                uvDobjModel(glider->objId, gliderToyModelLookup(0));
                uvDobjState(glider->objId, 2);
                glider->translateX = 80.0f;
                glider->pos.x = -66.0f;
                glider->pos.y = 320.0f;
                glider->pos.z = 125.0f;
                break;
            case 1:
                glider->pathVelocity = 18.0f;
                uvDobjModel(glider->objId, gliderToyModelLookup(1));
                uvDobjState(glider->objId, 2);
                glider->translateX = 70.0f;
                glider->pos.x = -66.0f;
                glider->pos.y = 320.0f;
                glider->pos.z = 135.0f;
                break;
            case 2:
                glider->pathVelocity = 18.0f;
                uvDobjModel(glider->objId, gliderToyModelLookup(2));
                uvDobjState(glider->objId, 2);
                glider->translateX = 90.0f;
                glider->pos.x = -70.0f;
                glider->pos.y = 320.0f;
                glider->pos.z = 155.0f;
                break;
            }
            glider->proxId = proxAnimAddCallback(gliderToyProxAnimCb, gliderToyProxEventCb, glider->pos, 2500.0f, 0.0f, i);
            gliderToyUpdate(i);
        }
    }
}

void gliderToyLoadEFrost(void) {
    GliderToy* glider;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sGliderToys); i++) {
        sGliderToys[i].objId = 0xFFFF;
    }

    for (i = 0; i < ARRAY_COUNT(sGliderToys) - 1; i++) {
        glider = &sGliderToys[i];
        glider->objId = uvDobjAllocIdx();
        if (glider->objId != 0xFFFF) {
            switch (i) {
            case 0:
                glider->pathVelocity = 7.0f;
                uvDobjModel(glider->objId, gliderToyModelLookup(0));
                uvDobjState(glider->objId, 2);
                glider->translateX = 250.0f;
                glider->pos.x = 80.03f;
                glider->pos.y = -162.16f;
                glider->pos.z = 600.0f;
                break;
            case 1:
                glider->pathVelocity = 17.0f;
                uvDobjModel(glider->objId, gliderToyModelLookup(1));
                uvDobjState(glider->objId, 2);
                glider->translateX = 70.0f;
                glider->pos.x = 745.26f;
                glider->pos.y = 1107.29f;
                glider->pos.z = 150.0f;
                break;
            case 2:
                glider->pathVelocity = 17.0f;
                uvDobjModel(glider->objId, gliderToyModelLookup(2));
                uvDobjState(glider->objId, 2);
                glider->translateX = 100.0f;
                glider->pos.x = 800.26f;
                glider->pos.y = 1107.29f;
                glider->pos.z = 170.0f;
                break;
            }
            glider->proxId = proxAnimAddCallback(gliderToyProxAnimCb, gliderToyProxEventCb, glider->pos, 2500.0f, 0.0f, i);
            gliderToyUpdate(i);
        }
    }
}

void gliderToyInit(void) {
    GliderToy* glider;
    s32 i;
    for (i = 0; i < ARRAY_COUNT(sGliderToys); i++) {
        glider = &sGliderToys[i];
        glider->pathAngle = 0.0f;
        glider->objId = 0xFFFF;
    }
}

void gliderToyDeinit(void) {
    GliderToy* glider;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sGliderToys); i++) {
        glider = &sGliderToys[i];
        if (glider->objId != 0xFFFF) {
            uvDobjModel(glider->objId, 0xFFFF);
            glider->objId = 0xFFFF;
            proxAnimDeleteCallback(glider->proxId);
        }
    }
}

void gliderToyGetObjData(s32 idx, s32* objId, f32* interval, Vec3F* pos) {
    Mtx4F pose;
    GliderToy* glider;

    glider = &sGliderToys[idx];
    if (glider->objId != 0xFFFF) {
        *objId = glider->objId;
        *interval = glider->pathAngle / 360.0f;
        uvDobjGetPosm(*objId, 0, &pose);
        pos->x = pose.m[3][0];
        pos->y = pose.m[3][1];
        pos->z = pose.m[3][2];
    } else {
        *objId = 0xFFFF;
        *interval = 0.0f;
        pos->x = 0.0f;
        pos->y = 0.0f;
        pos->z = 0.0f;
    }
}

void gliderToySetInterval(s32 idx, f32 interval) {
    if (sGliderToys[idx].objId != 0xFFFF) {
        uvDobjState(sGliderToys[idx].objId, 2);
        sGliderToys[idx].pathAngle = interval * 360.0f;
        gliderToyUpdate(idx);
    }
}
