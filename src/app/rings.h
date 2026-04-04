#ifndef APP_RINGS_H
#define APP_RINGS_H

#include <PR/ultratypes.h>
#include <uv_matrix.h>

typedef struct {
    u16 objId;
    u8 pad2[2];
    Mtx4F pose;
    Mtx4F unk44;
    Mtx4F curPose;
    Mtx4F posMtx0;
    Mtx4F posMtx1;
    u8 type2;
    u8 type;
    u8 scoreType;
    u8 ringSubtype; // 1 = bonus ring
    u8 points;
    u8 childCount;
    u8 pad14A[2];
    s32 children[5]; // TODO: size
    u8 timedChildrenCount;
    u8 pad161[3];
    s32 timedChildren[5]; // TODO: size
    u8 untimed; // is timed ring?
    u8 pad179[3];
    f32 timeRingDuration;
    f32 timeRemaining;
    u8 size;
    u8 pad185[3];
    f32 rotationRate0;
    f32 translation;
    u8 rotAxis0;
    u8 pad191[3];
    f32 rotationRateTimedOut1;
    f32 rotationRateTiming1;
    f32 rotationRate1;
    u8 rotAxis1;
    u8 pad1A1[3];
    f32 rotation0;
    f32 rotation1;
    f32 time1AC;
    f32 time1B0;
    u8 consumedType;
    u8 initialized;
    u8 unk1B6;
    u8 isActive;
    u8 rotationType1;
    u8 unk1B9; // similar isActive flag, only written
    u8 unk1BA; // unused, copied from RNGS
    char name[0xF]; // TODO: size?
    u8 radarIdx;
    u8 pad1CB[1];
} Ring; // size = 0x1CC

extern Ring gRings[30];

void ringsInit(void);
void rings_80323364(void);
void ringsLoad(void);
s32 rings_803243D8(Mtx4F*);
void ringsDeinit(void);
u8 ringsGetCleared(void);
s16 ringsGetPoints(f32*);

#endif // APP_RINGS_H
