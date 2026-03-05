#include "common.h"
#include <uv_level.h>
#include "ball_target.h"
#include "balls.h"
#include "code_72B70.h"
#include "code_82520.h"
#include "code_94E60.h"
#include "code_B2900.h"
#include "falco.h"
#include "hover_pads.h"
#include "rings.h"
#include "targets.h"

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
                if (levelIsValidIndex(classIdx, testIdx, vehIdx) != 0) {
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
    arg0->unkC = 10000.0f;
    arg0->unk10 = 10000.0f;
    D_8034FBD0 = arg0;
}

// https://decomp.me/scratch/cst2K
#pragma GLOBAL_ASM("asm/nonmatchings/app/code_B2900/func_8032B560.s")

// calculates the total amount of points for the given class + vehicle index
s32 levelGetTotalPoints(Unk80364210* arg0, s32 classIdx, s32 vehIdx) {
    s16 points;
    s32 testIdx;
    s32 pointsSum;
    Unk80364210_Unk0_Unk0* var_s0;

    pointsSum = 0;
    for (testIdx = 0; testIdx < levelGetTestCount(classIdx, vehIdx); testIdx++) {
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
    for (testIdx = 0; testIdx < levelGetTestCount(classIdx, vehIdx); testIdx++) {
        s32 pointCount = testGetPointCount(arg0, classIdx, testIdx, vehIdx);
        if (pointCount == invalidPointCount) {
            success = FALSE;
            break;
        }
    }
    return success;
}

u8 func_8032BF54(void) {
    void* tmp;

    tmp = NULL;
    if (levelGet_80346364() != 2) {
        return 0;
    }
    return (func_80324AF4() != levelDataGetRNGS(&tmp) || func_803448F4() != levelDataGetTARG(&tmp) || func_802CC15C() == 0 ||
            func_8030A080() != levelDataGetHPAD(&tmp) || func_802E57C4() != D_8035A5F0 || func_802D30B4() != levelDataGetBTGT((LevelBTGT**)&tmp) ||
            func_802FB5A0() != levelDataGetHOPD((LevelHOPD**)&tmp));
}

u8 func_8032C080(s32* arg0) {
    s32* sp2C;
    s32 var_v1;
    s32 pad;

    sp2C = levelGet_80345C80();
    if (levelGet_80346364() != 3) {
        if (arg0 != NULL) {
            *arg0 = -1;
        }
        return 0;
    }
    var_v1 = (((f32*)sp2C)[0xF1 /*unk3C4*/] -
              (f32)(func_802D30B4() + (func_802E57C4() + (func_8030A080() + (func_803448F4() + (func_80324AF4() + func_802FB5A0()))))));
    if (var_v1 < 0) {
        var_v1 = 0;
    }
    if (arg0 != NULL) {
        *arg0 = var_v1;
    }
    return !(var_v1 > 0);
}

s32 levelSetPointsToNextMedal(s32* pointsToNextMedal, u16 points, u8 classIdx) {
    Unk80362690_Unk0_UnkC* unkC;
    s32 i;
    u16 requiredPoints;

    unkC = &D_80362690->unk0[D_80362690->unk9C].unkC;

    for (i = 0; i < 3; i++) {
        requiredPoints = ((u16*)&gMedalPointRequirements[classIdx])[i];
        if (requiredPoints > points) {
            break;
        }
    }

    if (i == 3) {
        if (IS_MAIN_VEHICLE(unkC->veh)) {
            *pointsToNextMedal = 100 * levelGetTestCount(classIdx, unkC->veh) - points;
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
                if (levelGetTotalPoints(temp_s3, classIdx, vehIdx) != (levelGetTestCount(classIdx, vehIdx) * 100)) {
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

