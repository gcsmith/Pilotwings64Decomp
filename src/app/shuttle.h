#ifndef APP_SHUTTLE_H
#define APP_SHUTTLE_H

#include <PR/ultratypes.h>
#include <uv_vector.h>

enum ShuttleState {
    SHUTTLE_STATE_0 = 0,
    SHUTTLE_STATE_1 = 1,
    SHUTTLE_STATE_2 = 2,
    SHUTTLE_STATE_3 = 3,
    SHUTTLE_STATE_4 = 4,
};

s32 shuttle_80334CC0(void);
void shuttleInit(void);
void shuttleLoad(void);
void shuttleDeinit(void);
f32 shuttle_80335EE4(void);
void shuttle_80335F24(Vec3F*);
s32 shuttleGetState(void);
void shuttle_80335FD8(f32);
void shuttle_80336064(void);
void shuttle_80336094(void);
void shuttle_803360E8(void);

#endif // APP_SHUTTLE_H
