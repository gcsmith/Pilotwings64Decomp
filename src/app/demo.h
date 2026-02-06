#ifndef APP_DEMO_H
#define APP_DEMO_H

#include <PR/ultratypes.h>

typedef struct {
    f32 time;
    u32 inputs;
} DemoRecordingEntry;

enum InputAxis {
    INPUT_AXIS_0 = 0, // X or Z?
    INPUT_AXIS_1 = 1 // X or Z?
};

f32 demoRecGetStickX(DemoRecordingEntry* entry);
f32 demoRecGetStickY(DemoRecordingEntry* entry);
u32 demoRecGetButtons(DemoRecordingEntry* entry);
void demoPackInputs(DemoRecordingEntry* entry, f32 stickX, f32 stickY, u32 buttons);
s32 demo_803229EC(s32 arg0, s32 arg1);
s32 demoGet_80322B60(void);
s32 demoGet_80322B6C(void);
s32 demoGet_80322B78(void);
s32 demoGet_80322B84(void);
void demoAllocate(void);
void demoInit(void);
s32 demo_80322D60(s32 arg0, s32 arg1);
void demoSetRecMode(s32 mode);
s32 demoGetRecMode(void);
void demoLogInput(void);
s32 demoGetEntryIndex(f32 curTime);
s32 demo_80323020(void);
f32 demoGetInputs(s32 contIdx, s32 axis);
s32 demoGetButtons(s32 contIdx);
s32 demoButtonCheck(s32 contIdx, s32 buttonMask);
int demoButtonPress(s32 contIdx, s32 buttonMask);
int demoButtonRelease(s32 idx, s32 button);
f32 demoRandF(void);

#endif // APP_DEMO_H
