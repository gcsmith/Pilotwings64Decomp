#ifndef APP_CODE_D2D50_H
#define APP_CODE_D2D50_H

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

#endif // APP_CODE_D2D50_H
