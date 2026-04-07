#include "common.h"
#include "ball_target.h"
#include "balls.h"
#include "game.h"
#include "code_82520.h"
#include "code_94E60.h"
#include "code_9A960.h"
#include "code_B2900.h"
#include "falco.h"
#include "hover_pads.h"
#include "rings.h"
#include "snap.h"
#include "skydiving.h"
#include "targets.h"
#include "task.h"

// .data
Unk80364210* D_8034FBD0 = NULL;
// required points for medal, first = bronze, second = silver, third = gold
MedalPointRequirement gMedalPointRequirements[MAX_CLASSES] = {
    {  70,  80,  90 }, // beginner class
    { 140, 160, 180 }, // class A
    { 210, 240, 270 }, // class B
    { 210, 240, 270 }, // pilot class
    {  70,  80,  90 }, // cannonball?
    {  70,  80,  90 }, // sky diving?
    {  70,  80,  90 }, // jumble hopper?
    {   0,   0,   0 }
};

// forward decls
STATIC_FUNC u8 func_8032BF54(void);

void func_8032B3D0(Unk80364210* arg0) {
    s32 pad[7];
    Unk80364210_Unk0_Unk0* var_s0;
    s32 vehIdx;
    s32 testIdx;
    s32 classIdx;

    arg0->unk38 = 0;
    for (classIdx = 0; classIdx != MAX_CLASSES; classIdx++) {
        arg0->unk40[classIdx].unk690 = 0;
        for (testIdx = 0; testIdx != MAX_TESTS; testIdx++) {
            for (vehIdx = 0; vehIdx != VEHICLE_COUNT; vehIdx++) {
                var_s0 = &arg0->unk40[classIdx].unk0[testIdx][vehIdx];
                var_s0->unk2C = 0x7F;
                var_s0->unk24 = 0;
                var_s0->unk22 = var_s0->unk24;
                var_s0->unk2E = var_s0->unk24;
                var_s0->unk1A = var_s0->unk24;
                var_s0->unk16 = var_s0->unk24;
                var_s0->unk14 = var_s0->unk24;
                var_s0->unk18 = var_s0->unk24;
                var_s0->unk6 = var_s0->unk24;
                var_s0->unk12 = var_s0->unk24;
                var_s0->unkE = var_s0->unk24;
                var_s0->unkC = var_s0->unk24;
                var_s0->unkA = var_s0->unk24;
                var_s0->unk8 = var_s0->unk24;
                var_s0->unk4 = var_s0->unk24;
                if (taskIsValidIndex(classIdx, testIdx, vehIdx) != 0) {
                    var_s0->unk0 = 1;
                } else {
                    var_s0->unk0 = 0;
                }
            }
        }
    }
}

void func_8032B508(Unk80364210* arg0) {
    arg0->unk38 = 0;
    arg0->unk24 = 0;
    arg0->unk2C = 0;
    arg0->unk30 = 0;
    arg0->unk3C = 0;
    arg0->unk3D = 0;
    arg0->unk34 = 0;
    arg0->unk0 = 0;
    arg0->unk4 = 0.0f;
    arg0->unk14 = 0.0f;
    arg0->unk18 = 0.0f;
    arg0->unk1C = 0.0f;
    arg0->unk20 = 0.0f;
    arg0->unk8 = 10000.0f;
    arg0->landedDist = 10000.0f;
    arg0->unk10 = 10000.0f;
    D_8034FBD0 = arg0;
}

s32 func_8032B560(Unk80364210* arg0, u8 classIdx, u8 testIdx, u8 vehIdx) {
    Unk80345C80* sp74;
    s32 pad_sp70;
    s32 pad_sp6C;
    s16 sp6A;
    f32 sp64;
    f32 sp60;
    s32 pad_sp5C;
    s32 pad_sp58;
    s32 pad_sp54;
    s32 sp50;
    s32 sp4C;
    Unk80364210_Unk0_Unk0* temp_v1;
    s32 sp44;
    s32 tempPoints;
    s32 sp3C;

    sp74 = taskGet_80345C80();
    if (D_80362690->unkA1 != 0) {
        arg0->unk0 = 0x3F3E0;
    }
    if (arg0->unk3C != 0) {
        arg0->unk0 = 0x3F7F8;
    }
    switch (taskGet_80346364()) {
    case 0:
        break;
    case 1:
        if (arg0->unk3C != 0) {
            arg0->unk0 = 0;
        }
        break;
    case 2:
        if (func_8032BF54() != 0) {
            arg0->unk0 &= ~0x800;
        }
        break;
    case 3:
        if (func_8032C080(&sp4C) == 0) {
            arg0->unk0 &= ~0x800;
        }
        break;
    case 4:
        if (arg0->unk18 < sp74->unk3C8) {
            arg0->unk0 &= ~0x800;
        }
        break;
    }
    temp_v1 = &arg0->unk40[classIdx].unk0[testIdx][vehIdx];
    if (temp_v1) { }
    temp_v1->unk4 = 0;
    sp64 = 0.0f;
    if ((arg0->unk0 & 2) && (sp74->unk0.count > 0)) {
        sp64 = func_80313F08(&sp74->unk0, arg0->unk8);
        temp_v1->unk4 = sp64 + 0.001f;
    }
    temp_v1->unk2 = 0;
    sp60 = 0.0f;
    if (arg0->unk0 & 1) {
        if (sp74->unk0.count > 0) {
            sp60 = func_80313F08(&sp74->unk0, arg0->landedDist);
        }
        temp_v1->unk2 = sp60 + 0.001f;
    }
    temp_v1->unk6 = 0;
    if ((arg0->unk0 & 4) && sp74->unk150.count > 0) {
        temp_v1->unk6 = func_80313F08(&sp74->unk150, arg0->unk10) + 0.001f;
    }
    temp_v1->unk8 = 0;
    if ((arg0->unk0 & 8) && sp74->unk54.count > 0) {
        temp_v1->unk8 = func_80313F08(&sp74->unk54, arg0->unk14) + 0.001f;
    }
    temp_v1->unkA = 0;
    if ((arg0->unk0 & 0x10) && sp74->unkA8.count > 0) {
        temp_v1->unkA = func_80313F08(&sp74->unkA8, arg0->unk18) + 0.001f;
    }
    temp_v1->unkE = 0;
    if (arg0->unk0 & 0x20) {
        temp_v1->unkE = ringsGetPoints(&temp_v1->unk28);
    }
    temp_v1->unk14 = 0;
    if (arg0->unk0 & 0x100) {
        temp_v1->unk14 = targets_80344948();
    }
    temp_v1->unk16 = 0;
    if (arg0->unk0 & 0x200) {
        temp_v1->unk16 = ballsGetPoints();
    }
    temp_v1->unkC = 0;
    if ((arg0->unk0 & 0x800) && sp74->unkFC.count > 0) {
        temp_v1->unkC = func_80313F08(&sp74->unkFC, arg0->unk1C);
    }
    temp_v1->unk12 = 0;
    if (arg0->unk0 & 0x80) {
        temp_v1->unk12 = arg0->unk2C;
    }
    temp_v1->unk18 = 0;
    if (arg0->unk0 & 0x400) {
        temp_v1->unk18 = arg0->unk30 * sp74->unk3B4;
    }
    if (temp_v1->unk18 < -0x64) {
        temp_v1->unk18 = -0x64;
    }
    temp_v1->unk1A = 0;
    if (arg0->unk0 & 0x1000) {
        temp_v1->unk1A = skydivingGetPoints(1);
    }
    temp_v1->unk1C = 0;
    if (arg0->unk0 & 0x2000) {
        temp_v1->unk1C = func_80338614();
    }
    temp_v1->unk1E = 0;
    if (arg0->unk0 & 0x4000) {
        temp_v1->unk1E = hoverPadGetPoints();
    }
    temp_v1->unk20 = 0;
    if (arg0->unk0 & 0x8000) {
        temp_v1->unk20 = falco_802E5818();
    }
    temp_v1->unk22 = 0;
    if (arg0->unk0 & 0x10000) {
        temp_v1->unk22 = ballTgtCount_59();
    }
    temp_v1->unk24 = 0;
    if (arg0->unk0 & 0x20000) {
        temp_v1->unk24 = func_802FB5FC();
    }

    sp6A = temp_v1->unk8 + temp_v1->unk14 + temp_v1->unkC + temp_v1->unkA + temp_v1->unkE + temp_v1->unk12 + temp_v1->unk18 + temp_v1->unk16 + temp_v1->unk6 +
           temp_v1->unk1A + temp_v1->unk1C + temp_v1->unk1E + temp_v1->unk20 + temp_v1->unk22 + temp_v1->unk24 + arg0->unk38;
    if (arg0->landedDist != 10000.0f) {
        temp_v1->unk4 = (sp64 * sp60) + 0.5f;
        temp_v1->unk2 = 0;
    }
    sp6A += temp_v1->unk4;
    if (sp6A < 0) {
        sp6A = 0;
    } else if (sp6A > 100) {
        sp6A = 100;
    }
    if (IS_BONUS_VEHICLE(vehIdx)) {
        sp50 = vehIdx + 1;
    } else {
        sp50 = classIdx;
    }
    sp44 = levelGetTotalPoints(arg0, classIdx, vehIdx);
    temp_v1->unk0 = 1;
    if (sp6A == temp_v1->unk2C && levelSetPointsToNextMedal(&sp4C, sp44, sp50) == MEDAL_NONE) {
        if (sp4C == 0) {
            temp_v1->unk0 = 4;
        }
    } else if (temp_v1->unk2C < sp6A || temp_v1->unk2C == 0x7F) {
        if (temp_v1->unk2C == 0x7F) {
            temp_v1->unk2C = 0;
        }
        sp3C = levelSetPointsToNextMedal(&sp4C, sp44, sp50);
        temp_v1->unk2E = 1;
        temp_v1->unk2C = sp6A;
        tempPoints = levelGetTotalPoints(arg0, classIdx, vehIdx);
        if (levelSetPointsToNextMedal(&sp4C, tempPoints, sp50) != sp3C || (sp3C == 3 && sp4C == 0)) {
            temp_v1->unk0 = 4;
        } else {
            temp_v1->unk0 = 1;
        }
    } else {
        temp_v1->unk2E = 0;
        temp_v1->unk0 = 1;
    }
    pad_sp6C = (taskGet_80345C80()->unk3B8 < sp6A) ? TRUE : FALSE;
    return pad_sp6C;
}

// calculates the total amount of points for the given class + vehicle index
s32 levelGetTotalPoints(Unk80364210* arg0, s32 classIdx, s32 vehIdx) {
    s16 points;
    s32 testIdx;
    s32 pointsSum;
    Unk80364210_Unk0_Unk0* var_s0;

    pointsSum = 0;
    for (testIdx = 0; testIdx < taskGetTestCount(classIdx, vehIdx); testIdx++) {
        var_s0 = &arg0->unk40[classIdx].unk0[testIdx][vehIdx];
        points = var_s0->unk2C;
        if (points == 0x7F) {
            points = 0;
        }
        pointsSum += points;
    }
    return pointsSum;
}

Unk80364210* func_8032BE10(void) {
    return D_8034FBD0;
}

u8 testGetPointCount(Unk80364210* arg0, u8 classIdx, u8 testIdx, u8 vehIdx) {
    return arg0->unk40[classIdx].unk0[testIdx][vehIdx].unk2C;
}

s32 func_8032BE8C(Unk80364210* arg0, u8 classIdx, u8 vehIdx) {
    s32 testIdx;
    s32 success;
    int invalidPointCount = 0x7F;

    success = TRUE;
    for (testIdx = 0; testIdx < taskGetTestCount(classIdx, vehIdx); testIdx++) {
        s32 pointCount = testGetPointCount(arg0, classIdx, testIdx, vehIdx);
        if (pointCount == invalidPointCount) {
            success = FALSE;
            break;
        }
    }
    return success;
}

STATIC_FUNC u8 func_8032BF54(void) {
    void* tmp;

    tmp = NULL;
    if (taskGet_80346364() != 2) {
        return 0;
    }
    return (ringsGetCleared() != taskGetRNGS((TaskRNGS**)&tmp) || targets_803448F4() != taskGetTARG((TaskTARG**)&tmp) || ballsGetAllPopped() == 0 ||
            hoverPadGetCount() != taskGetHPAD((TaskHPAD**)&tmp) || falco_802E57C4() != D_8035A5F0 || ballTgtCount_5B() != taskGetBTGT((TaskBTGT**)&tmp) ||
            func_802FB5A0() != taskGetHOPD((TaskHOPD**)&tmp));
}

u8 func_8032C080(s32* arg0) {
    Unk80345C80* sp2C;
    s32 var_v1;
    s32 pad;

    sp2C = taskGet_80345C80();
    if (taskGet_80346364() != 3) {
        if (arg0 != NULL) {
            *arg0 = -1;
        }
        return 0;
    }
    var_v1 = sp2C->unk3C4 - (ballTgtCount_5B() + (falco_802E57C4() + (hoverPadGetCount() + (targets_803448F4() + (ringsGetCleared() + func_802FB5A0())))));
    if (var_v1 < 0) {
        var_v1 = 0;
    }
    if (arg0 != NULL) {
        *arg0 = var_v1;
    }
    return !(var_v1 > 0);
}

s32 levelSetPointsToNextMedal(s32* pointsToNextMedal, u16 points, u8 classIdx) {
    Unk80362690_Unk0* unkC;
    s32 i;
    u16 requiredPoints;

    unkC = &D_80362690->unkC[D_80362690->unk9C];

    for (i = 0; i < 3; i++) {
        requiredPoints = ((u16*)&gMedalPointRequirements[classIdx])[i];
        if (requiredPoints > points) {
            break;
        }
    }

    if (i == 3) {
        if (IS_MAIN_VEHICLE(unkC->veh)) {
            *pointsToNextMedal = 100 * taskGetTestCount(classIdx, unkC->veh) - points;
        } else {
            *pointsToNextMedal = 100 - points;
        }
        return 3;
    } else {
        *pointsToNextMedal = requiredPoints - points;
        return i;
    }
}

s32 func_8032C27C(void) {
    Unk80364210* temp_s3;
    s32 classIdx;
    s32 vehIdx;
    s32 success;
    s32 maxClassIdx;

    temp_s3 = &D_80364210[D_80362690->unk9C];
    success = TRUE;
    for (vehIdx = 0; vehIdx < VEHICLE_COUNT; vehIdx++) {
        if (vehIdx == VEHICLE_BIRDMAN) {
            continue;
        }
        maxClassIdx = vehIdx < VEHICLE_CANNONBALL ? CLASS_COUNT : CLASS_PILOT;
        for (classIdx = 0; classIdx < maxClassIdx; classIdx++) {
            if (vehIdx == VEHICLE_CANNONBALL) {
                if (levelGetTotalPoints(temp_s3, classIdx, vehIdx) != 100) {
                    success = FALSE;
                }
            } else {
                if (levelGetTotalPoints(temp_s3, classIdx, vehIdx) != (taskGetTestCount(classIdx, vehIdx) * 100)) {
                    success = FALSE;
                }
            }
        }
    }
    return success;
}

// returns the highest medal earned on task(s?), flags controls which medal to determine
// if flags has bit 2 set it checks for the normal medals, otherwise for extra mode medals
s32 func_8032C3C4(Unk80364210* arg0, u16 flags) {
    s32 temp_v0;
    s32 medalPointRequirementIdx;
    s32 classIdx;
    s32 vehIdx;
    s32 resultMedal;
    s32 maxClassIdx;
    s32 targetVehIdx;
    s32 initialVehIdx;
    s32 classMedal;
    MedalPointRequirement* medalPointRequirements;

    if (flags & 1) {
        initialVehIdx = VEHICLE_HANG_GLIDER;
    } else {
        initialVehIdx = VEHICLE_CANNONBALL;
    }

    if (flags & 2) {
        targetVehIdx = VEHICLE_COUNT;
    } else {
        targetVehIdx = VEHICLE_CANNONBALL;
    }

    if (initialVehIdx == targetVehIdx) {
        return MEDAL_BRONZE;
    }

    resultMedal = MEDAL_NONE;
    for (vehIdx = initialVehIdx; vehIdx < targetVehIdx; vehIdx++) {
        if (vehIdx != VEHICLE_BIRDMAN) {
            maxClassIdx = IS_MAIN_VEHICLE(vehIdx) ? CLASS_COUNT : CLASS_PILOT;
            for (classIdx = 0; classIdx < maxClassIdx; classIdx++) {
                temp_v0 = levelGetTotalPoints(arg0, classIdx, vehIdx);
                if (IS_MAIN_VEHICLE(vehIdx)) {
                    medalPointRequirementIdx = classIdx;
                } else {
                    medalPointRequirementIdx = classIdx + 4;
                }
                medalPointRequirements = &gMedalPointRequirements[medalPointRequirementIdx];
                if (temp_v0 < medalPointRequirements->bronze) {
                    classMedal = MEDAL_BRONZE;
                } else if (temp_v0 < medalPointRequirements->silver) {
                    classMedal = MEDAL_SILVER;
                } else if (temp_v0 < medalPointRequirements->gold) {
                    classMedal = MEDAL_GOLD;
                } else {
                    classMedal = MEDAL_NONE;
                }
                if (classMedal < resultMedal) {
                    resultMedal = classMedal;
                }
            }
        }
    }

    return resultMedal;
}
