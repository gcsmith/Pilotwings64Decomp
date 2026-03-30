#ifndef APP_DEMO_H
#define APP_DEMO_H

#include <PR/ultratypes.h>

typedef struct {
    f32 time;
    u32 inputs;
} DemoRecordingEntry;

enum InputAxis {
    INPUT_AXIS_X = 0,
    INPUT_AXIS_Y = 1
};

f32 demoRecGetStickX(DemoRecordingEntry* entry);
f32 demoRecGetStickY(DemoRecordingEntry* entry);
u32 demoRecGetButtons(DemoRecordingEntry* entry);
void demoPackInputs(DemoRecordingEntry* entry, f32 stickX, f32 stickY, u32 buttons);
s32 demoGetUserFileIdx(s32 pilot, s32 veh);
s32 demoGetClassId(void);
s32 demoGetVehicleId(void);
s32 demoGet_80322B78(void);
s32 demoGetTestId(void);
void demoAllocate(void);
void demoInit(void);
void demoLoad(s32 pilot, s32 veh);
void demoSetRecMode(s32 mode);
s32 demoGetRecMode(void);
void demoLogInput(void);
s32 demoGetEntryIndex(f32 curTime);
s32 demo_80323020(void);
f32 demoGetInputs(s32 contIdx, s32 axis);
s32 demoGetButtons(s32 contIdx);
s32 demoButtonCheck(s32 contIdx, s32 buttonMask);
int demoButtonPress(s32 contIdx, s32 buttonMask);
int demoButtonRelease(s32 contIdx, s32 buttonMask);
f32 demoRandF(void);

#endif // APP_DEMO_H
