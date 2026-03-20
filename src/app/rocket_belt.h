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
    u8 pad50[0x40];
    u8 unk90;
    u8 pad91[0x67];
    f32 unkF8;
    u8 padFC[0x18];
    f32 unk114;
    u8 pad118[0xDC];
    f32 unk1F4;
    u8 pad1F8[0x17C];
    Vec3F unk374;
    u8 pad380[0x1C];
} RocketBeltData;

void func_80324DB4(u8 contIdx, u8 pilot, RocketBeltData* arg2, Unk802D3658_Arg0* arg3);
void rocketBeltEnterLeave(RocketBeltData*);
void rocketBeltMovementFrame(RocketBeltData*, u8);
void func_80325E1C(RocketBeltData*);
void func_803273C8(RocketBeltData*, u8);

#endif // APP_ROCKET_BELT_H
