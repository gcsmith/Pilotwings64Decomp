#ifndef APP_WHALE_H
#define APP_WHALE_H

#include <PR/ultratypes.h>
#include <uv_vector.h>

s32 whaleIsActive(void);
void whaleLoad(void);
void whaleDeinit(void);
f32 whaleGetInterval(void);
void whaleGetPos(Vec3F* pos);
void whaleSetInterval(f32 interval);
void whaleInit(void);
void whaleStateSave(void);
void whaleStateRestore(void);

#endif // APP_WHALE_H
