#ifndef APP_SKYDIVING_H
#define APP_SKYDIVING_H

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
    u8 pad50[0x20];
    u8 unk70;
    u8 pad71[0xFB];
    f32 unk16C;
    u8 pad170[0xC0];
    Vec3F unk230;
    u8 pad23C[0x88];
    f32 unk2C4;
    u8 pad2C8[0x50];
} SkyDivingData;

void skydivingInit(void);
s16 skydivingGetPoints(s32);

void func_8032FACC(u8 contIdx, u8 pilot, SkyDivingData* arg2, Unk802D3658_Arg0* arg3);
void skydivingEnterLeave(SkyDivingData*);
void skydivingMovementFrame(SkyDivingData*, u8);

#endif // APP_SKYDIVING_H
