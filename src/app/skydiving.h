#ifndef APP_SKYDIVING_H
#define APP_SKYDIVING_H

#include "code_72B70.h"

typedef struct {
    u16 objId;
    u8 unk2;
    u8 pad3[0xD];
    Mtx4F unk10;
    u8 pad50[0x2C4];
} SkyDivingData;

void skydivingInit(void);
s16 skydivingGetPoints(s32);
void skydivingEnterLeave(SkyDivingData*);
void skydivingMovementFrame(SkyDivingData*, u8);

#endif // APP_SKYDIVING_H
