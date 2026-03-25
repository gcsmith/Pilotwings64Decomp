#include "common.h"
#include <uv_dobj.h>
#include <uv_math.h>
#include <uv_matrix.h>
#include <uv_texture.h>
#include <uv_vector.h>
#include "code_9A960.h"
#include "code_B2900.h"
#include "hud.h"
#include "level.h"
#include "macros.h"
#include "pads.h"
#include "task.h"

#define MAX_LANDING_PADS 14

typedef struct {
    u8 pad0[0x10];
    s32 unk10;
    u8 pad14[4];
} Unk8036C168; // size = 0x18

TaskLPAD* gRefLPAD;
TaskLSTP* gRefLSTP;
TaskTPAD* gRefTPAD;
TaskCNTG* gRefCNTG;
LevelLPAD* gRefPotLPAD;
Unk8036C168 D_8036C168[MAX_LANDING_PADS]; // written to, but unused
u8 gPotLandPadCount;
u8 gLandingPadCount;
u8 gLandingStripCount;
u8 gTakeoffPadCount;
u8 gCannonTargetCount;
TakeoffPad gTakeoffPads[3];
LandingPad gLandingPads[MAX_LANDING_PADS];
LandingStrip gLandingStrips[2];
CannonTarget gCannonTargets[1];
u16 gLandingPadObjIds[MAX_LANDING_PADS];

s8 gPadsInitialized = FALSE;
u16 gLandingPadModels[3] = { MODEL_LANDING_PAD_1, MODEL_LANDING_PAD_2, MODEL_LANDING_PAD_3 };

// forward declarations
f32 padsStripAlignment(f32, f32, f32, LandingStrip*);

void padsInit(void) {
    Unk8036C168* var_a0;
    LandingPad* pad;
    LandingStrip* strip;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gLandingPads); i++) {
        gLandingPads[i].initialized = FALSE;
        gLandingPads[i].isUsed = FALSE;
        D_8036C168[i].unk10 = 0;
    }
    for (i = 0; i < ARRAY_COUNT(gLandingStrips); i++) {
        gLandingStrips[i].initialized = FALSE;
        gLandingStrips[i].validStrip = FALSE;
    }
    gLandingStripCount = 0;
    gLandingPadCount = 0;
    gPotLandPadCount = 0;
    gTakeoffPadCount = 0;
    gCannonTargetCount = 0;
}

void padsLoad(void) {
    LandingPad* landPad;
    LandingStrip* landstrip;
    TaskLSTP* lstp;
    s32 pad1;
    LevelLPAD* plpad;
    TaskLPAD* lpad;
    f32 minDist;
    s32 var_s0;
    s32 j;
    s32 lpadIdx;
    s32 i;
    f32 dx;
    f32 dy;
    f32 dz;
    TaskCNTG* cntg;
    CannonTarget* cannonTarg;
    s32 pad0;
    Mtx4F pose;
    f32 dist;

    gPotLandPadCount = levelGetLPAD(&gRefPotLPAD);
    if (gPotLandPadCount > ARRAY_COUNT(gLandingPads)) {
        _uvDebugPrintf("pads : too many potential landing pads defined in level [%d]\n", gPotLandPadCount);
        gPotLandPadCount = 0;
        return;
    }

    gLandingPadCount = taskGetLPAD(&gRefLPAD);
    if (gLandingPadCount > ARRAY_COUNT(gLandingPads)) {
        _uvDebugPrintf("pads : too many landing pads defined in level [%d]\n", gLandingPadCount);
        gLandingPadCount = 0;
        return;
    }

    for (i = 0; i < gLandingPadCount; i++) {
        lpad = &gRefLPAD[i];
        landPad = &gLandingPads[i];
        uvVec3Copy(&landPad->pos, &lpad->pos);
        landPad->type = lpad->type;
    }

    for (i = 0; i < gLandingPadCount; i++) {
        landPad = &gLandingPads[i];
        minDist = 100.0f;
        lpadIdx = -1;
        for (j = 0; j < gPotLandPadCount; j++) {
            dx = landPad->pos.x - gRefPotLPAD[j].pos.x;
            dy = landPad->pos.y - gRefPotLPAD[j].pos.y;
            dz = landPad->pos.z - gRefPotLPAD[j].pos.z;
            dist = uvLength3D(dx, dy, dz);
            if ((dist < minDist) && !gRefPotLPAD[j].isUsed) {
                minDist = dist;
                lpadIdx = j;
            }
        }
        if ((lpadIdx != -1) && (D_80362690->unkC[D_80362690->unk9C].unk7B == 0)) {
            gLandingPads[i].pos.x = gRefPotLPAD[lpadIdx].pos.x;
            gLandingPads[i].pos.y = gRefPotLPAD[lpadIdx].pos.y;
            gLandingPads[i].pos.z = gRefPotLPAD[lpadIdx].pos.z;
            gRefPotLPAD[lpadIdx].isUsed = TRUE;
            gLandingPads[i].isUsed = gRefPotLPAD[lpadIdx].isUsed;
            gLandingPads[i].landingDistance = 30.0f;
            gLandingPads[i].idxLevelLPAD = lpadIdx;
            gRefPotLPAD[lpadIdx].type = gLandingPads[i].type;
        }
    }

    gLandingStripCount = taskGetLSTP(&gRefLSTP);
    if (gLandingStripCount > ARRAY_COUNT(gLandingStrips)) {
        _uvDebugPrintf("pads : too many landing strips defined in level [%d]\n", gLandingStripCount);
        gLandingStripCount = 0;
        return;
    }

    for (i = 0; i < gLandingStripCount; i++) {
        lstp = &gRefLSTP[i];
        landstrip = &gLandingStrips[i];
        landstrip->validStrip = lstp->validStrip;
        uvVec3Copy(&landstrip->pos0, &lstp->posUL);
        uvVec3Copy(&landstrip->pos1, &lstp->posLR);
        landstrip->midpoint.x = (landstrip->pos0.x + landstrip->pos1.x) * 0.5f;
        landstrip->midpoint.y = (landstrip->pos0.y + landstrip->pos1.y) * 0.5f;
        landstrip->midpoint.z = (landstrip->pos0.z + landstrip->pos1.z) * 0.5f;
        dx = landstrip->pos1.x - landstrip->pos0.x;
        dy = landstrip->pos1.y - landstrip->pos0.y;
        dz = landstrip->pos1.z - landstrip->pos0.z;
        dist = uvSqrtF(SQ(dx) + SQ(dy) + SQ(dz));
        landstrip->normal.x = dx / dist;
        landstrip->normal.y = dy / dist;
        landstrip->normal.z = dz / dist;
        landstrip->landingDistance = 0.5f * dist;
        landstrip->landingAlignment = lstp->landingAlignment;
        landstrip->initialized = TRUE;
    }

    gTakeoffPadCount = taskGetTPAD(&gRefTPAD);
    if (gTakeoffPadCount > ARRAY_COUNT(gTakeoffPads)) {
        _uvDebugPrintf("pads : too many takeoff pads defined in level [%d]\n", gTakeoffPadCount);
        gTakeoffPadCount = 0;
        return;
    }

    for (i = 0; i < gTakeoffPadCount; i++) {
        uvVec3Copy(&gTakeoffPads[i].pos, &gRefTPAD[i].pos);
    }

    for (i = 0; i < gPotLandPadCount; i++) {
        plpad = &gRefPotLPAD[i];
        if (plpad->isUsed) {
            uvLevelAppend(0x17);
            break;
        }
    }

    for (i = 0; i < gPotLandPadCount; i++) {
        uvMat4SetIdentity(&pose);
        gLandingPadObjIds[i] = uvDobjAllocIdx();
        if (gRefPotLPAD[i].isUsed) {
            uvDobjModel(gLandingPadObjIds[i], gLandingPadModels[gRefPotLPAD[i].type]);
        } else {
            uvDobjModel(gLandingPadObjIds[i], MODEL_LANDING_PAD_NOTARGET);
        }
        func_80313640(gRefPotLPAD[i].pos.x, gRefPotLPAD[i].pos.y, gRefPotLPAD[i].pos.z, gRefPotLPAD[i].angle, 0.0f, 0.0f, &pose);
        uvDobjPosm(gLandingPadObjIds[i], 0, &pose);
    }

    for (i = 0; i < gLandingPadCount; i++) {
        gLandingPads[i].initialized = TRUE;
    }

    for (i = 0; i < gLandingStripCount; i++) {
        gLandingStrips[i].initialized = TRUE;
    }

    if (D_80362690->unkC[D_80362690->unk9C].unk7B == 0) {
        gCannonTargetCount = taskGetCNTG(&gRefCNTG);
        if (gCannonTargetCount > ARRAY_COUNT(gCannonTargets)) {
            _uvDebugPrintf("pads : too many cannon targets defined in level [%d]\n", gCannonTargetCount);
            gCannonTargetCount = 0;
            return;
        }

        if (gCannonTargetCount) {
            uvLevelAppend(0x18);
        }

        for (i = 0; i < gCannonTargetCount; i++) {
            cntg = &gRefCNTG[i];
            cannonTarg = &gCannonTargets[i];
            cannonTarg->objId = uvDobjAllocIdx();
            cannonTarg->radarIdx = hudAddWaypoint(cntg->pos.x, cntg->pos.y, cntg->pos.z);
            switch (cntg->type) {
            case 0:
                uvDobjModel(cannonTarg->objId, MODEL_CANNONB_TARGET_2);
                cannonTarg->deltaZ = 35.0f;
                break;
            case 1:
                uvDobjModel(cannonTarg->objId, MODEL_CANNONB_TARGET_3);
                cannonTarg->deltaZ = 42.5f;
                break;
            case 2:
                uvDobjModel(cannonTarg->objId, MODEL_CANNONB_TARGET_4);
                cannonTarg->deltaZ = 50.0f;
                break;
            default:
                _uvDebugPrintf("pads : unknown cannon target type [%d]\n", cntg->type);
                uvDobjModel(cannonTarg->objId, MODEL_CANNONB_TARGET_4);
                cannonTarg->deltaZ = 50.0f;
                break;
            }
            func_80313640(cntg->pos.x, cntg->pos.y, cntg->pos.z, cntg->angle.x * 0.01745329f, cntg->angle.y * 0.01745329f, cntg->angle.z * 0.01745329f,
                          &cannonTarg->pose);
            uvDobjPosm(cannonTarg->objId, 0, &cannonTarg->pose);
        }
    }
}

void padsFrameUpdate(Mtx4F* pose) {
    TakeoffPad* var_s0;
    Unk80364210* temp_v0;
    f32 x;
    f32 y;
    f32 z;
    f32 dist;
    f32 minDist;
    f32 dx, dy, dz;
    s32 i;

    minDist = 1000000.0f;
    x = pose->m[3][0];
    y = pose->m[3][1];
    z = pose->m[3][2];
    temp_v0 = func_8032BE10();
    temp_v0->unk3D = 0;
    if ((gLandingPadCount > 0) || (gLandingStripCount > 0)) {
        temp_v0->unk8 = padsLandedPadStrip(x, y, z, &temp_v0->unk3D);
    }

    for (i = 0; i < gTakeoffPadCount; i++) {
        var_s0 = &gTakeoffPads[i];
        dx = var_s0->pos.x - x;
        dy = var_s0->pos.y - y;
        dz = var_s0->pos.z - z;
        dist = uvLength3D(dx, dy, dz);
        if (dist < minDist) {
            minDist = dist;
        }
    }
    if (func_8032BE10()->unk4 < minDist) {
        func_8032BE10()->unk4 = minDist;
    }
}

s32 padsUnused(void) {
    return 1;
}

void padsDeinit(void) {
    CannonTarget* cannonTarg;
    s32 i;

    for (i = 0; i < gPotLandPadCount; i++) {
        if (gLandingPadObjIds[i] != 0xFFFF) {
            uvDobjModel(gLandingPadObjIds[i], 0xFFFF);
            gLandingPadObjIds[i] = 0xFFFF;
        }
    }

    gPadsInitialized = FALSE;
    for (i = 0; i < gCannonTargetCount; i++) {
        cannonTarg = &gCannonTargets[i];
        if (cannonTarg->objId != 0xFFFF) {
            hud_8031A8E0(cannonTarg->radarIdx);
            uvDobjModel(cannonTarg->objId, 0xFFFF);
            cannonTarg->objId = 0xFFFF;
        }
    }
}

void padsInitLandingPads(void) {
    s32 i;
    Mtx4F pose;

    for (i = 0; i < gPotLandPadCount; i++) {
        if (gRefPotLPAD[i].isUsed) {
            uvDobjModel(gLandingPadObjIds[i], MODEL_LANDING_PAD_NOTARGET);
        }
        uvMat4SetIdentity(&pose);
        func_80313640(gRefPotLPAD[i].pos.x, gRefPotLPAD[i].pos.y, gRefPotLPAD[i].pos.z, gRefPotLPAD[i].angle, 0.0f, 0.0f, &pose);
        uvDobjPosm(gLandingPadObjIds[i], 0, &pose);
        gRefPotLPAD[i].isUsed = FALSE;
        gPadsInitialized = TRUE;
    }
}

f32 padsLandedPadStrip(f32 x, f32 y, f32 z, u8* outIdx) {
    LandingPad* landPad;
    LandingStrip* lstrip;
    f32 dx;
    f32 dist;
    f32 dy;
    f32 minDist;
    s32 i;

    minDist = 1000000.0f;

    for (i = 0; i < gLandingPadCount; i++) {
        landPad = &gLandingPads[i];
        if (landPad->isUsed) {
            dx = landPad->pos.x - x;
            dy = landPad->pos.y - y;
            dist = uvSqrtF(SQ(dx) + SQ(dy));
            if (dist < minDist) {
                minDist = dist;
            }
            if (dist < landPad->landingDistance) {
                *outIdx = i + 1;
            }
        }
    }

    for (i = 0; i < gLandingStripCount; i++) {
        lstrip = &gLandingStrips[i];
        if (lstrip->validStrip) {
            dx = lstrip->midpoint.x - x;
            dy = lstrip->midpoint.y - y;
            dist = uvSqrtF(SQ(dx) + SQ(dy));
            if (dist <= lstrip->landingDistance) {
                dist = padsStripAlignment(x, y, z, lstrip);
                if (dist < (lstrip->landingAlignment * 0.5f)) {
                    *outIdx = 0xFF;
                }
            }
            if (dist < minDist) {
                minDist = dist;
            }
        }
    }

    return minDist;
}

f32 padsCannonTgtDist(f32 x, f32 y, f32 z, u16 targetObjId) {
    Mtx4F sp48;
    Vec3F sp3C;
    Vec3F sp30;
    s32 i;
    s32 pad;

    for (i = 0; i < gCannonTargetCount; i++) {
        if (targetObjId == gCannonTargets[i].objId) {
            break;
        }
    }
    if (i == gCannonTargetCount) {
        return 1000.0f;
    }

    sp30.x = x;
    sp30.y = y;
    sp30.z = z;
    uvMat4InvertTranslationRotation(&sp48, &gCannonTargets[i].pose);
    uvMat4LocalToWorld(&sp48, &sp3C, &sp30);
    sp3C.y = 0.0f;
    sp3C.z -= gCannonTargets[i].deltaZ;
    return uvVec3Len(&sp3C);
}

f32 padsStripAlignment(f32 x, f32 y, f32 z, LandingStrip* lstrip) {
    f32 nx, ny, nz;
    f32 dx, dy, dz;
    f32 tx, ty, tz;
    f32 sum;
    f32 ret;

    nx = lstrip->normal.x;
    ny = lstrip->normal.y;
    nz = lstrip->normal.z;
    dx = (x - lstrip->pos0.x);
    dy = (y - lstrip->pos0.y);
    dz = (z - lstrip->pos0.z);
    sum = nx * dx + ny * dy + nz * dz;
    if (sum < 0.0f) {
        return 1000000.0f;
    }

    nx = -nx;
    ny = -ny;
    nz = -nz;
    dx = (x - lstrip->pos1.x);
    dy = (y - lstrip->pos1.y);
    dz = (z - lstrip->pos1.z);
    sum = nx * dx + ny * dy + nz * dz;
    if (sum < 0.0f) {
        return 1000000.0f;
    }

    tx = (lstrip->pos1.x + (nx * sum)) - x;
    ty = (lstrip->pos1.y + (ny * sum)) - y;
    tz = (lstrip->pos1.z + (nz * sum)) - z;
    ret = uvSqrtF(SQ(tx) + SQ(ty) + SQ(tz));
    return ret;
}
