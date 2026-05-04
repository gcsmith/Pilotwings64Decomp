#include "common.h"
#include <uv_controller.h>

ControllerInfo gControllerInfo[UV_MAX_CONTROLLERS];
extern s32 gControllerPattern;

void uvControllerInit(void) {
    s32 i;
    s32 j;
    u32 contPattern;
    s32 mask;

    for (i = 0; i < UV_MAX_CONTROLLERS; i++) {
        // clang-format off: needs to be on one line to match
        for (j = 0; j < UV_MAX_AXES; j++) { gControllerInfo[i].stickAxes[j] = 0.0f; }
        // clang-format on
        gControllerInfo[i].button = 0;
        gControllerInfo[i].prevButton = 0;
    }

    contPattern = uvContMesgInit();

    for (i = 0; i < UV_MAX_CONTROLLERS; i++) {
        mask = 1 << i;
        if (contPattern & mask) {
            gControllerInfo[i].enumerate = TRUE;
            gControllerInfo[i].connected = TRUE;
            gControllerPattern = contPattern;
        } else {
            gControllerInfo[i].enumerate = FALSE;
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
        if (gControllerInfo[i].enumerate == FALSE) {
            continue;
        }
        if (gControllerInfo[i].connected == TRUE) {
            if (uvControllerUpdate(i) == 0) {
                return 0;
            }
            continue;
        }
        _uvDebugPrintf("Unknown controller %d\n", i);
        return 0;
    }

    return 1;
}

s32 uvControllerUpdate(s32 contIdx) {
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
