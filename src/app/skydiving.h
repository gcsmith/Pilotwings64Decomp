#ifndef APP_SKYDIVING_H
#define APP_SKYDIVING_H

#include "code_72B70.h"

void skydivingInit(void);
s16 skydivingGetPoints(s32);
void skydivingEnterLeave(VehicleData*);
void skydivingMovementFrame(VehicleData*, u8);

#endif // APP_SKYDIVING_H
