#ifndef APP_ROCKET_BELT_H
#define APP_ROCKET_BELT_H

#include "game.h"

typedef struct {
    u16 objId;
    u8 unk2;
    u8 pad3[0x1];
    u16 unk4;
    u8 pad6[0x2];
    f32 unk8;
    u8 padC[0x4];
    Mtx4F unk10;
    u8 pad50[0x14];
    u8 unk64;
    u8 pad65[0x81 - 0x65];
    u8 unk81;
    u8 pad82[6];
    f32 unk88;
    u8 pad8C[4];
    u8 unk90;
    u8 unk91;
    u8 unk92;
    u8 unk93[4];
    u8 unk97[4];
    u8 pad9B[0xCC - 0x9B];
    f32 unkCC[4];
    u8 padDC[0xC];
    u8 unkE8;
    u8 padE9[2];
    u8 unkEB;
    u8 unkEC;
    u8 padED[0xB];
    f32 unkF8;
    u8 padFC[0x18];
    f32 unk114;
    u8 pad118[0xD8];
    f32 unk1F0;
    f32 unk1F4;
    u8 pad1F8[0x244 - 0x1F8];
    Vec3F unk244;
    u8 pad250[0x374 - 0x250];
    Vec3F unk374;
    u8 pad380[4];
    s32 unk384;
    u8 unk388;
    u8 unk389;
    u8 unk38A;
    u8 unk38B;
    u8 unk38C;
    u8 pad38D[0x90 - 0x8D];
    f32 unk390;
    f32 unk394;
    f32 unk398;
} RocketBeltData;

void rocketBeltInit(void);
void func_80324DB4(u8 contIdx, u8 pilot, RocketBeltData* arg2, Camera* arg3);
void rocketBeltEnterLeave(RocketBeltData*);
void func_80325100(RocketBeltData*);
void rocketBeltMovementFrame(RocketBeltData*, u8);
void func_80325E1C(RocketBeltData*);
void func_803273C8(RocketBeltData*, u8);

void rbSoundInit(RocketBeltData* rbData);

#endif // APP_ROCKET_BELT_H
