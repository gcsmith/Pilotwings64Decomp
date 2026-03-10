#ifndef APP_BALL_TARGET_H
#define APP_BALL_TARGET_H

#include <PR/ultratypes.h>

void ballTgtInit(void);
void ballTgtUpdateState(void);
void ballTgtLoad(void);
s32 ballTgtInGoal(void);
void ballTgtDeinit(void);
u8 ballTgtCount_5B(void);
s16 ballTgtCount_59(void);

#endif // APP_BALL_TARGET_H
