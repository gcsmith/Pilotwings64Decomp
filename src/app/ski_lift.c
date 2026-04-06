#include "common.h"
#include <uv_dobj.h>
#include <uv_vector.h>
#include "proxanim.h"
#include "ski_lift.h"
#include "spath.h"

typedef struct {
    s32 objId;
    f32 interval;
} LiftChair;

static LiftChair sSkiLift[20];
static s32 sSkiLiftProxId;
static s32 sSkiLiftActive;
static s32 sSkiLiftSpathId;

STATIC_FUNC void skiLiftUpdate(void) {
    s32 i;
    Mtx4F pose;

    for (i = 0; i < ARRAY_COUNT(sSkiLift); i++) {
        if (sSkiLift[i].objId != 0xFFFF) {
            sSkiLift[i].interval += 0.03f;
            if (sSkiLift[i].interval >= 100.0f) {
                sSkiLift[i].interval -= 100.0f;
            }
            spathScaleUpdate(&pose, sSkiLiftSpathId, sSkiLift[i].interval, 1.0f, 512.0f);
            uvDobjPosm(sSkiLift[i].objId, 0, &pose);
        }
    }
}

STATIC_FUNC s32 skiLiftProxEventCb(UNUSED s32 proxId, s32 eventType, UNUSED s32 clientData) {
    s32 i;

    switch (eventType) {
    case 0:
        break;
    case 2:
        for (i = 0; i < ARRAY_COUNT(sSkiLift); i++) {
            uvDobjState(sSkiLift[i].objId, 0);
        }
        break;
    case 3:
        for (i = 0; i < ARRAY_COUNT(sSkiLift); i++) {
            uvDobjState(sSkiLift[i].objId, 3);
        }
        break;
    }

    return 0;
}

STATIC_FUNC s32 skiLiftProxAnimCb(s32 proxId, UNUSED f32 timeout, UNUSED s32 clientData) {
    s32 i;
    s32 ret;

    ret = 0;
    if (proxAnimGetRange(proxId) > 1500.0f) {
        if (sSkiLiftActive) {
            skiLiftUpdate();
            sSkiLiftActive = FALSE;
        } else {
            ret = 2;
            for (i = 0; i < ARRAY_COUNT(sSkiLift); i++) {
                uvDobjState(sSkiLift[i].objId, 0);
            }
        }
    } else {
        if (!sSkiLiftActive) {
            sSkiLiftActive = TRUE;
            for (i = 0; i < ARRAY_COUNT(sSkiLift); i++) {
                uvDobjState(sSkiLift[i].objId, 3);
            }
        }
        skiLiftUpdate();
    }
    return ret;
}

void skiLiftLoad(void) {
    LiftChair* chair;
    Vec3F pos = { -207.927f, -897.804f, 112.643f };
    s32 i;

    sSkiLiftSpathId = spathLoadFile(4);
    sSkiLiftProxId = proxAnimAddCallback(skiLiftProxAnimCb, skiLiftProxEventCb, pos, 1500.0f, 0.0f, 0);
    for (i = 0; i < ARRAY_COUNT(sSkiLift); i++) {
        sSkiLift[i].objId = uvDobjAllocIdx();
        if (sSkiLift[i].objId != 0xFFFF) {
            sSkiLift[i].interval = (i / 20.0f) * 100.0f;
            uvDobjModel(sSkiLift[i].objId, MODEL_SKI_LIFT_CHAIR);
            uvDobjState(sSkiLift[i].objId, 3);
            skiLiftUpdate();
        }
    }
}

void skiLiftDeinit(void) {
    s32 i;

    spathFree(sSkiLiftSpathId);
    proxAnimDeleteCallback(sSkiLiftProxId);
    for (i = 0; i < ARRAY_COUNT(sSkiLift); i++) {
        if (sSkiLift[i].objId != 0xFFFF) {
            uvDobjModel(sSkiLift[i].objId, MODEL_WORLD);
            sSkiLift[i].objId = 0xFFFF;
        }
    }
}
