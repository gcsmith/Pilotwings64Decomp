#ifndef UV_CONTROLLER_H
#define UV_CONTROLLER_H

#include <PR/os_cont.h>
#include <PR/ultratypes.h>

#define UV_MAX_CONTROLLERS 6
#define UV_MAX_AXES 3 

typedef struct {
    u8 connected;
    u8 pad1[3];
    f32 stickAxes[UV_MAX_AXES];
    s32 button;
    s32 prevButton;
    u8 enumerate; // same state as connected -- unused mechanism to disable?
    u8 pad19[3];
} ControllerInfo;

// from main
u8 uvContMesgInit(void);
s32 uvReadController(ControllerInfo* contInfo, s32 contIdx);

void uvControllerInit(void);
s32 uvControllerCheckInserted(s32 contIdx);
s32 uvIOUpdate(void);
s32 uvControllerUpdate(s32 contIdx);
f32 uvControllerGetStick(s32 contIdx, s32 axis);
s32 uvControllerButtonCheck(s32 idx, s32 mask);
s32 uvControllerGetButton(s32 idx);
s32 uvControllerButtonPress(s32 idx, s32 button);
s32 uvControllerButtonRelease(s32 idx, s32 button);

#endif // UV_CONTROLLER_H
