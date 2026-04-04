#ifndef APP_MISSI_H
#define APP_MISSI_H

#include <uv_vector.h>

s32 missiIsActive(void);
void missiLoadLStates(void);
void missiDeinitLStates(void);
f32 missiGetInterval(void);
void missiGetCurPos(Vec3F* pos);
void missiSetInterval(f32 interval);
void missiInit(void);
void missiStateSave(void);
void missiStateRestore(void);
void missiInitState(void);
s32 missiInProximity(void);
void missiLoadEFrost(void);
void missiDeinitEFrost(void);
void missiGetInitPos(Vec3F* pos);

#endif // APP_MISSI_H
