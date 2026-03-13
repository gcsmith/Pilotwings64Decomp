#ifndef APP_BALLS_H
#define APP_BALLS_H

#include <PR/ultratypes.h>
#include <uv_level.h>
#include <uv_matrix.h>
#include "code_72B70.h"

typedef struct {
    u8 idx;
    u8 pad1[3];
    Mtx4F unk4;
    Vec3F unk44;
    Vec3F unk50; // ball velocity
    f32 unk5C;
    u8 unk60;
    u8 pad61[3];
    f32 unk64;
    f32 unk68;
    f32 unk6C;
    f32 unk70;
    f32 unk74;
    u8 unk78;
    u8 unk79;
    u8 pad7A[2];
    f32 unk7C;
    f32 unk80; // time related
    f32 unk84;
    u16 objId;
    u8 unk8A;
    u8 pad8B[1];
    s32 unk8C;
    s32 unk90;
    u8 unk94;
    u8 unk95;
    u8 unk96;
    u8 unk97;
    f32 unk98;
    f32 unk9C;
    Unk802D3658_Unk111C unkA0;
    u8 unk1A8;
    u8 pad1A9[0x1AC - 0x1A9];
} ParsedBALS; // size: 0x1AC

extern f32 D_80359388;
extern u8 gBallCount; // initial ball count. never decremented
extern u8 gBallSplitCount; // split ball count (5 after first split, 10 after second). never decremented
extern ParsedBALS gBalls[20]; // array of balls loaded

void ballsInit(void);
void balls_802CAF50(void);
void ballsLoad(void);
void ballsDeinit(void);
void ballsFrameUpdate(void);
s32 balls_802CC0D4(u8 objId);
u8 ballsGet_802CC15C(void);
f32 ballsPopped(u8 objId, Vec3F* arg1, Unk802D3658_Unk1224* arg2);
s32 ballsGet_802CC064(void);

#endif // APP_BALLS_H
