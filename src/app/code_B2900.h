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

// could be part of / union within Unk80364210
typedef struct {
    s32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    s32 unk24;
    s32 pad28;
    s32 unk2C;
    s32 unk30;
    s32 unk34;
    s32 unk38;
    u8 unk3C;
    s8 unk3D;
} Unk8032B508;

typedef struct {
    u16 bronze;
    u16 silver;
    u16 gold;
} MedalPointRequirement;

extern MedalPointRequirement gMedalPointRequirements[];

void func_8032B3D0(Unk80364210*);
u8 func_8032C080(s32*);
void func_8032B560(s32, u8, u8, u8);
s32 levelGetTotalPoints(Unk80364210*, s32, s32);
Unk8032B508* func_8032BE10(void);
s32 testGetPointCount(Unk80364210*, u8, u8, u8);
s32 func_8032BE8C(Unk80364210*, u8, u8);
s32 levelSetPointsToNextMedal(s32*, u16, u8);
s32 func_8032C27C(void);
void func_8032B508(Unk8032B508* arg0);

#endif // APP_CODE_B2900_H
