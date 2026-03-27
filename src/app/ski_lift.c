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

STATIC_FUNC s32 skiLift_80336248(s32 arg0, s32 arg1, s32 arg2) {
    s32 i;

    switch (arg1) {
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

STATIC_FUNC s32 skiLift_803362EC(s32 arg0, f32 arg1, s32 arg2) {
    s32 i;
    s32 sp20;

    sp20 = 0;
    if (proxAnimGetRange(arg0) > 1500.0f) {
        if (sSkiLiftActive) {
            skiLiftUpdate();
            sSkiLiftActive = FALSE;
        } else {
            sp20 = 2;
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
    return sp20;
}

void skiLiftLoad(void) {
    LiftChair* var_s0;
    Vec3F sp50 = { -207.927f, -897.804f, 112.643f };
    s32 i;

    sSkiLiftSpathId = spathLoadFile(4);
    sSkiLiftProxId = proxAnimAddCallback(skiLift_803362EC, skiLift_80336248, sp50, 1500.0f, 0.0f, 0);
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
