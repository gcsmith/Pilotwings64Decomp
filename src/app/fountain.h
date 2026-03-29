#ifndef APP_FOUNTAIN_H
#define APP_FOUNTAIN_H

#include <uv_vector.h>

s32 fountainIsActive(void);
void fountainInit(void);
void fountainLoad(void);
void fountainDeinit(void);
f32 fountainGetInterval(void);
void fountainGetPos(Vec3F* pos);
void fountainSetInterval(f32 interval);
void fountainStateSave(void);
void fountainStateRestore(void);

#endif // APP_FOUNTAIN_H
