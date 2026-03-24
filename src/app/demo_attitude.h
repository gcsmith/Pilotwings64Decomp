#ifndef APP_DEMO_ATTITUDE_H
#define APP_DEMO_ATTITUDE_H

#include <uv_matrix.h>

void demoAttInit(s32 userFileIdx);
void demoAttLoadPos(void);
void demoAttGetMtxRT(Mtx4F* mat, f32* tx, f32* ty, f32* tz, f32* rz, f32* rx, f32* ry);
void demoAttPrintRecord(void);
f32 demoPositionLerp(f32 a, f32 b, f32 t);
f32 demoAngleLerp(f32 a, f32 b, f32 t);
void demoAttUpdate(f32 curTime, Mtx4F* mat);
void demoAtt_80320FBC(void);
void demoAttPrintRT(Mtx4F* mat);

#endif // APP_DEMO_ATTITUDE_H
