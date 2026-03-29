#ifndef APP_ROCKET_BELT_H
#define APP_ROCKET_BELT_H

#include "code_72B70.h"

typedef struct {
    u16 objId;
    u8 unk2;
    u8 pad3[0xD];
    Mtx4F unk10;
    u8 pad50[0x34C];
} RocketBeltData;

void rocketBeltEnterLeave(RocketBeltData*);
void rocketBeltMovementFrame(RocketBeltData*, u8);

#endif // APP_ROCKET_BELT_H
