#ifndef APP_FERRY_H
#define APP_FERRY_H

#include <uv_vector.h>

s32 ferryIsActive(void);
void ferryInit(void);
void ferryLoad(void);
void ferryDeinit(void);
f32 ferryGetInterval(void);
void ferryGetPos(Vec3F* pos);
void ferrySetInterval(f32 interval);
void ferryStateSave(void);
void ferryStateRestore(void);

#endif // APP_FERRY_H
