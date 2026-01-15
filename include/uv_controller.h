#ifndef UV_CONTROLLER_H
#define UV_CONTROLLER_H

#include <PR/ultratypes.h>

typedef struct {
    u8 unk0;
    u8 pad1[3];
    f32 stickAxes[3];
    s32 button;
    s32 prevButton;
    u8 unk18;
    u8 pad19[3];
} ControllerInfo;

// from main
u8 uvContMesgInit(void);
s32 uvReadController(ControllerInfo* contInfo, s32 contIdx);

void uvControllerInit(void);
s32 uvControllerCheckInserted(s32 contIdx);
s32 uvIOUpdate(void);
s32 func_80224548(s32 contIdx);
f32 uvControllerGetStick(s32 contIdx, s32 axis);
s32 uvControllerButtonCheck(s32 idx, s32 mask);
s32 uvControllerGetButton(s32 idx);
s32 uvControllerButtonPress(s32 idx, s32 button);
s32 uvControllerButtonRelease(s32 idx, s32 button);

#endif // UV_CONTROLLER_H
