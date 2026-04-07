#ifndef APP_BALLS_H
#define APP_BALLS_H

#include <PR/ultratypes.h>
#include <uv_matrix.h>
#include "game.h"

typedef struct {
    u8 idx;
    u8 pad1[3];
    Mtx4F pose;
    Vec3F velocity;
    Vec3F acceleration;
    f32 unk5C;
    u8 unk60;
    u8 pad61[3];
    f32 unk64;
    f32 unk68;
    f32 unk6C;
    f32 unk70;
    f32 dist;
    u8 type;
    u8 childBallCount;
    u8 pad7A[2];
    f32 scale;
    f32 time80; // time related
    f32 unk84;
    u16 objId;
    u8 unk8A;
    u8 pad8B[1];
    s32 points;
    s32 unk90;
    u8 hasPopped;
    u8 initialized;
    u8 active;
    u8 unk97;
    f32 dragCoef;
    f32 gravity;
    Unk802D3658_Unk111C unkA0;
    u8 radarIdx;
    u8 pad1A9[3];
} Ball; // size: 0x1AC

extern f32 D_80359388;
extern u8 gBallCount; // initial ball count. never decremented
extern u8 gBallSplitCount; // split ball count (5 after first split, 10 after second). never decremented
extern Ball gBalls[20]; // array of balls loaded

void ballsInit(void);
void balls_802CAF50(void);
void ballsLoad(void);
void ballsDeinit(void);
void ballsFrameUpdate(void);
s32 ballsObjIdExists(u8 objId);
u8 ballsGetAllPopped(void);
f32 ballsPopped(u8 objId, Vec3F* arg1, Unk802D3658_Unk1224* arg2);
s32 ballsGetPoints(void);
u8 ballsGetCount(void);

#endif // APP_BALLS_H
