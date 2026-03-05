#ifndef APP_CODE_B2900_H
#define APP_CODE_B2900_H

#include <PR/ultratypes.h>
#include "code_72B70.h"

enum Medals {
    MEDAL_BRONZE = 0,
    MEDAL_SILVER = 1,
    MEDAL_GOLD = 2,
    MEDAL_NONE = 3
};

typedef struct {
    u16 bronze;
    u16 silver;
    u16 gold;
} MedalPointRequirement;

extern MedalPointRequirement gMedalPointRequirements[MAX_CLASSES];

void func_8032B3D0(Unk80364210*);
u8 func_8032C080(s32*);
void func_8032B560(Unk80364210*, u8, u8, u8);
s32 levelGetTotalPoints(Unk80364210*, s32, s32);
Unk80364210* func_8032BE10(void);
u8 testGetPointCount(Unk80364210*, u8, u8, u8);
s32 func_8032BE8C(Unk80364210*, u8, u8);
s32 levelSetPointsToNextMedal(s32*, u16, u8);
s32 func_8032C27C(void);
void func_8032B508(Unk80364210* arg0);

#endif // APP_CODE_B2900_H
