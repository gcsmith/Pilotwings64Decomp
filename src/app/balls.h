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

typedef struct {
    u16 objId;
    u8 pad2[0xA];
    u16 unkC;
} Unk802CC51C;

extern u8 gBallCount; // initial ball count. never decremented
extern u8 gBallSplitCount; // split ball count (5 after first split, 10 after second). never decremented
extern ParsedBALS gBalls[20]; // array of balls loaded

void ballsInit(void);
void balls_802CAF50(void);
void ballsLoad(void);
void ballsDeinit(void);
void ballsFrameUpdate(void);
u8 ballsGet_802CC15C(void);

// these should be split from this file
void bird_802CC1B0(void);
void bird_802CC270(u8, u8 pilot, Unk80367704*, Unk802D3658_Arg0*);
void bird_802CC39C(Unk80367704*);
void bird_802CC51C(Unk802CC51C*);
void bird_802CC55C(Unk80367704*, u8);
void bird_802CD0F8(Unk80367704*);

#endif // APP_BALLS_H
