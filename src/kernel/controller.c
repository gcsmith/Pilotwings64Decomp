#include "common.h"
#include <uv_controller.h>
#include <uv_util.h>

extern s32 gControllerPattern;
extern ControllerInfo gControllerInfo[6];

void uvControllerInit(void) {
    s32 i;
    s32 j;
    u32 contPattern;
    s32 mask;

    // 6 controllers and 3 axes on the stick
    for (i = 0; i < 6; i++) {
        // clang-format off: needs to be on one line to match
        for (j = 0; j < 3; j++) { gControllerInfo[i].stickAxes[j] = 0.0f; }
        // clang-format on
        gControllerInfo[i].button = 0;
        gControllerInfo[i].prevButton = 0;
    }

    contPattern = uvContMesgInit();

    for (i = 0; i < 6; i++) {
        mask = 1 << i;
        if (contPattern & mask) {
            gControllerInfo[i].unk18 = 1;
            gControllerInfo[i].unk0 = 1;
            gControllerPattern = contPattern;
        } else {
            gControllerInfo[i].unk18 = 0;
        }
    }
}

s32 uvControllerCheckInserted(s32 contIdx) {
    s32 mask = 1 << contIdx;
    if (gControllerPattern & mask) {
        return 1;
    }
    return 0;
}

s32 uvIOUpdate(void) {
    s32 i;

    if (gControllerPattern == 0) {
        _uvDebugPrintf("uvIOUpdate: please plug in controller and restart game\n");
        return 1;
    }

    for (i = 0; i < ARRAY_COUNT(gControllerInfo); i++) {
        if (gControllerInfo[i].unk18 == 0) {
            continue;
        }
        if (gControllerInfo[i].unk0 == 1) {
            if (func_80224548(i) == 0) {
                return 0;
            }
            continue;
        }
        _uvDebugPrintf("Unknown controller %d\n", i);
        return 0;
    }

    return 1;
}

s32 func_80224548(s32 contIdx) {
    // uvReadController returns 0 (failure) or 1 (success)
    // unsure of the original intent of this comparison
    if (uvReadController(&gControllerInfo[contIdx], contIdx) < 0) {
        return 0;
    }
    return 1;
}

f32 uvControllerGetStick(s32 contIdx, s32 axis) {
    return gControllerInfo[contIdx].stickAxes[axis];
}

s32 uvControllerButtonCheck(s32 idx, s32 mask) {
    if (gControllerInfo[idx].button & mask) {
        return 1;
    }
    return 0;
}

s32 uvControllerGetButton(s32 idx) {
    return gControllerInfo[idx].button;
}

s32 uvControllerButtonPress(s32 idx, s32 button) {
    if ((gControllerInfo[idx].button & button) && !(gControllerInfo[idx].prevButton & button)) {
        return 1;
    }
    return 0;
}

s32 uvControllerButtonRelease(s32 idx, s32 button) {
    if (!(gControllerInfo[idx].button & button) && (gControllerInfo[idx].prevButton & button)) {
        return 1;
    }
    return 0;
}
