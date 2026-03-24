#include "common.h"
#include <uv_audio.h>
#include <uv_dobj.h>
#include <uv_event.h>
#include <uv_math.h>
#include <uv_memory.h>
#include <uv_model.h>
#include <uv_texture.h>
#include "balls.h"
#include "code_61A60.h"
#include "code_66160.h"
#include "code_7FE00.h"
#include "code_9A960.h"
#include "hud.h"
#include "task.h"

// .data
// list of model ids
s32 gBallModelIdLookup[] = { MODEL_BALL_ORANGE, MODEL_BALL_GREEN, MODEL_BALL_BLUE };

// .bss
u8 gBallCount;
u8 gBallSplitCount;
Ball gBalls[20];
f32 D_80359388; // always set to 5.3241148?
TaskBALS* sRefBALS;

// forward declarations
void ballsMotionUpdate(Ball*);
void ballsFrameUpdateOne(Ball*);
s32 balls_802CB6D4(Ball*);

// called during startup, during test load menu, and while init any level
void ballsInit(void) {
    Ball* ball;
    s32 i;

    for (ball = gBalls, i = 0; i < ARRAY_COUNT(gBalls); i++, ball++) {
        ball->idx = i;
        ball->objId = 0xFFFF;
        ball->initialized = 0;
        ball->hasPopped = FALSE;
        ball->unk64 = 0.0f;
        ball->unk97 = 0;
        ball->time80 = 0.0f;
        ball->radarIdx = 0xFF;
        ball->unk5C = 1e7f;
    }
    gBallCount = 0;
    sRefBALS = NULL;
    gBallSplitCount = 0;
}

// called during init of test that has a ball (e.g. RP Balloon tests)
// called for once for each ball (Balloon Rush 1x, Balloon Bonanza 2x)
void ballsInitBall(Ball* ball) {
    f32 temp_fv1;
    f32 temp_fa0;
    ball->unk5C = 1e7f;
    ball->unkA0.unk0 = 3;
    temp_fv1 = D_80359388;
    temp_fa0 = -D_80359388;
    ball->unkA0.unk4[0].unk0 = 1;
    ball->unkA0.unk4[0].unk28.x = temp_fa0;
    ball->unkA0.unk4[1].unk0 = 1;
    ball->unkA0.unk4[1].unk28.y = temp_fa0;
    ball->unkA0.unk4[2].unk0 = 1;
    ball->unkA0.unk4[2].unk28.z = temp_fa0;
    ball->unkA0.unk4[0].unk1C.x = temp_fv1;
    ball->unkA0.unk4[1].unk1C.y = temp_fv1;
    ball->unkA0.unk4[2].unk1C.z = temp_fv1;
    ball->unkA0.unk4[0].unk28.y = 0.0f;
    ball->unkA0.unk4[0].unk28.z = 0.0f;
    ball->unkA0.unk4[0].unk1C.y = 0.0f;
    ball->unkA0.unk4[0].unk1C.z = 0.0f;
    ball->unkA0.unk4[1].unk28.x = 0.0f;
    ball->unkA0.unk4[1].unk28.z = 0.0f;
    ball->unkA0.unk4[1].unk1C.x = 0.0f;
    ball->unkA0.unk4[1].unk1C.z = 0.0f;
    ball->unkA0.unk4[2].unk28.x = 0.0f;
    ball->unkA0.unk4[2].unk28.y = 0.0f;
    ball->unkA0.unk4[2].unk1C.x = 0.0f;
    ball->unkA0.unk4[2].unk1C.y = 0.0f;
    ball->objId = uvDobjAllocIdx();
    if (ball->active) {
        ball->unk8A = 3;
    } else {
        ball->unk8A = 0;
    }
    uvDobjState(ball->objId, ball->unk8A);
    if (ball->type >= (u32)ARRAY_COUNT(gBallModelIdLookup)) {
        _uvDebugPrintf("balls: bad vrep %d for ball\n", ball->type);
        ball->type = 0;
    }
    uvDobjModel(ball->objId, gBallModelIdLookup[ball->type]);
    uvDobjProps(ball->objId, 3, (f64)ball->scale, 0);
    if (ball->initialized == 0) {
        uvMat4Scale(&ball->pose, ball->scale, ball->scale, ball->scale);
    }
    uvDobjPosm(ball->objId, 0, &ball->pose);
}

// called once during test init if balls loaded
void balls_802CAF50(void) {
    s32 i;

    for (i = 0; i < (gBallCount + gBallSplitCount); i++) {
        if (D_80362690->unkC[D_80362690->unk9C].unk8 == gBalls[i].unk60) {
            gBalls[i].active = TRUE;
            if (gBalls[i].objId != 0xFFFF) {
                uvDobjSetState(gBalls[i].objId, 3);
            }
            if (gBalls[i].radarIdx != 0xFF) {
                hud_8031A874(gBalls[i].radarIdx);
            }
        } else {
            gBalls[i].active = FALSE;
            if (gBalls[i].objId != 0xFFFF) {
                uvDobjClearState(gBalls[i].objId, 3);
            }
            if (gBalls[i].radarIdx != 0xFF) {
                hud_8031A810(gBalls[i].radarIdx);
            }
        }
    }
}

// called from task.c to load BALS data for test. always called no matter veh, class, test
// even called again after pause + check-map + continue
void ballsLoad(void) {
    s32 i;
    Ball* ball;
    TaskBALS* bals;

    if (D_80362690->unkA0) {
        gBallCount = taskGetBALS(&sRefBALS);
        if (gBallCount >= 0x15) {
            _uvDebugPrintf("balls : too many balls defined in level [%d]\n", gBallCount);
            gBallCount = 0;
        } else if (gBallCount != 0) {
            uvLevelAppend(0x11);
            uvModelGetProps(0xF4, 1, &D_80359388, 0);
            for (i = 0; i < (gBallCount + gBallSplitCount); i++) {
                bals = &sRefBALS[i];
                ball = &gBalls[i];
                if (ball->hasPopped) {
                    continue;
                }

                if (ball->initialized == 0) {
                    ball->hasPopped = FALSE;
                    ball->velocity.z = 0.0f;
                    ball->velocity.y = 0.0f;
                    ball->velocity.x = 0.0f;
                    ball->acceleration.z = 0.0f;
                    ball->acceleration.y = 0.0f;
                    ball->acceleration.x = 0.0f;
                    ball->unk60 = bals->unk18;
                    ball->active = TRUE;
                    if (bals->willSplit) {
                        ball->childBallCount = 5;
                    } else {
                        ball->childBallCount = 0;
                    }
                    ball->unk84 = bals->unk1C;
                    ball->unk70 = bals->unk24;
                    ball->unk6C = bals->unk28;
                    ball->unk68 = bals->unk2C;
                    ball->points = bals->points;
                    ball->unk90 = bals->unk38;
                    ball->scale = bals->scale;
                    ball->type = bals->type;
                    ball->dragCoef = bals->dragCoef;
                    ball->gravity = bals->gravity;
                    uvMat4SetIdentity(&ball->pose);
                    ball->pose.m[3][0] = bals->pos.x;
                    ball->pose.m[3][1] = bals->pos.y;
                    ball->pose.m[3][2] = bals->pos.z;
                    ballsInitBall(&gBalls[i]);
                    ball->initialized = 1;
                    ball->radarIdx = hudAddWaypoint(bals->pos.x, bals->pos.y, bals->pos.z);
                } else {
                    ballsInitBall(&gBalls[i]);
                }
            }
            balls_802CAF50();
        }
    }
}

// called for each ball with motion
// not called prior to splitting, called 5x per frame after split
// ball pushing test called 1x per frame
void ballsMotionUpdate(Ball* ball) {
    f32 dvx;
    f32 dvy;

    dvx = -ball->dragCoef * ball->velocity.x * ball->velocity.x;
    if (ball->velocity.x < 0.0f) {
        dvx = -dvx;
    }

    dvy = -ball->dragCoef * ball->velocity.y * ball->velocity.y;
    if (ball->velocity.y < 0.0f) {
        dvy = -dvy;
    }

    ball->acceleration.x += dvx;
    ball->acceleration.y += dvy;
}

// called from task.c at level exit
// deinits and balls loaded
void ballsDeinit(void) {
    s32 i;

    for (i = 0; i < gBallCount + gBallSplitCount; i++) {
        if (gBalls[i].objId != 0xFFFF) {
            uvDobjModel(gBalls[i].objId, 0xFFFF);
            gBalls[i].objId = 0xFFFF;
        }
    }
}

// called every frame regardless of vehicle
// iterates through balls loaded and updates
void ballsFrameUpdate(void) {
    Ball* ball;
    s32 i;

    if (D_80362690->unkA0) {
        for (i = 0; i < gBallCount + gBallSplitCount; i++) {
            ball = &gBalls[i];
            if (ball->objId == 0xFFFF) {
                continue;
            }
            if (!ball->active) {
                continue;
            }
            if (ball->time80 > 0.0f) {
                ball->time80 -= D_8034F854;
            }
            if ((ball->unk6C > 0.0f) && !ball->hasPopped) {
                ballsFrameUpdateOne(ball);
            }
        }
    }
}

// updates ball motion
// not called for balls that are motionless
void ballsFrameUpdateOne(Ball* ball) {
    f32 ts;
    f32 temp_fv0_2;
    f32 grav;

    ball->acceleration.x = 0.0f;
    ball->acceleration.y = 0.0f;
    ball->acceleration.z = 0.0f;

    ts = D_8034F854;

    ballsMotionUpdate(ball);
    if (balls_802CB6D4(ball) == 0) {
        if (ball->gravity == 0.0f) {
            grav = 9.8f;
        } else {
            grav = ball->gravity;
        }
        ball->acceleration.z -= grav;
    }

    temp_fv0_2 = ball->velocity.z;
    ball->velocity.x += ball->acceleration.x * ts;
    ball->velocity.y += ball->acceleration.y * ts;
    ball->velocity.z += ball->acceleration.z * ts;
    ball->pose.m[3][0] += ball->velocity.x * ts;
    ball->pose.m[3][1] += ball->velocity.y * ts;
    ball->pose.m[3][2] += ball->velocity.z * ts;
    if ((ball->velocity.z < 0.0f) && ((ball->velocity.z * temp_fv0_2) < 0.0f)) {
        ball->unk5C = ball->pose.m[3][2];
    }

    func_802E07D8(&ball->pose);
    uvDobjPosm(ball->objId, 0, &ball->pose);
    if (ball->radarIdx != 0xFF) {
        hudMoveWaypoint(ball->radarIdx, ball->pose.m[3][0], ball->pose.m[3][1], ball->pose.m[3][2]);
    }
}

s32 balls_802CB6D4(Ball* ball) {
    f32 temp_fv0;
    Vec3F sp1B8;
    Vec3F sp1AC;
    f32 var_fa0;
    f32 var_fv1;
    f32 temp_fv1;
    Unk802D3658_Unk1224 sp5C;
    s32 pad;
    s32 pad2;
    u8 obj_id;
    u8 idx;

    if (func_802DB050(&ball->unkA0, &sp5C, ball->objId, ball->unk8A, &ball->pose) <= 0) {
        return 0;
    }
    idx = func_802DBF10(&ball->unkA0, &sp5C, &sp1B8, &sp1AC);
    if ((sp5C.unk4[idx].unk4 != 1) && (sp5C.unk4[idx].unk4 != 4)) {
        var_fv1 = ball->unk6C;
    } else {
        if (ball->unk5C - sp1B8.z < (10.0f + D_80359388 * ball->scale)) {
            var_fv1 = 1.25f;
        } else if (ball->unk5C - sp1B8.z < (11.0f + D_80359388 * ball->scale)) {
            var_fv1 = 1.0f;
        } else {
            var_fv1 = ball->unk6C;
        }
    }
    var_fa0 = uvVec3Dot(&ball->velocity, &sp1AC);
    if (uvAbs((s32)var_fa0) < 5.0f) {
        var_fa0 = -5.0f;
    }
    if (var_fa0 < 0.0f) {
        ball->velocity.x -= (2.0f * var_fa0) * sp1AC.x;
        ball->velocity.y -= (2.0f * var_fa0) * sp1AC.y;
        ball->velocity.z -= (2.0f * var_fa0) * sp1AC.z;
        ball->acceleration.x = 0.0f;
        ball->acceleration.y = 0.0f;
        ball->acceleration.z = 0.0f;
        ball->velocity.x *= var_fv1;
        ball->velocity.y *= var_fv1;
        ball->velocity.z *= var_fv1;
    }
    if (uvVec3Len(&ball->velocity) > 1.0f) {
        if (((uvVec3Len(&ball->velocity) / var_fa0) < 0.5f) && ((ball->unk64 + 0.25f) < D_8034F850)) {
            ball->unk64 = D_8034F850;
            obj_id = uvEmitterLookup();
            uvEmitterFromModel(obj_id, 0x37);
            uvEmitterProp(obj_id, 1, 0.0f, 2, 500.0f, 5, 0x38, 0);
            uvEmitterSetMatrix(obj_id, &ball->pose);
            uvEmitterTrigger(obj_id);
        }
    }
    return 1;
}

void balls_802CB9B4(Ball* ball) {
    TaskBALS* bals;
    Ball* splitBall;
    f32 temp_fs0;
    s32 i;
    s32 pad;
    f32 sp90;
    f32 sp8C;
    f32 sp88;

    for (i = 0; i < ball->childBallCount; i++) {
        if ((gBallCount + gBallSplitCount) < ARRAY_COUNT(gBalls)) {
            splitBall = &gBalls[gBallSplitCount + gBallCount];
            gBallSplitCount++;
            *splitBall = *ball;
            bals = &sRefBALS[ball->idx];
            splitBall->unk70 = bals->unk48;
            splitBall->unk6C = bals->unk4C;
            splitBall->unk68 = bals->unk50;
            splitBall->points = bals->unk54;
            splitBall->unk90 = bals->unk58;
            splitBall->scale = bals->unk5C;
            splitBall->type = bals->unk44;
            splitBall->dragCoef = bals->unk60;
            splitBall->gravity = bals->splitBallGravity;
            splitBall->childBallCount = 0;

            temp_fs0 = i * (6.2831855f / ball->childBallCount); // 2*pi or DEG_TO_RAD(360)
            func_803134D0(ball->scale * D_80359388, temp_fs0, 0.0f, &sp90, &sp8C, &sp88);
            uvMat4LocalTranslate(&splitBall->pose, sp90, sp8C, sp88);
            func_803134D0(splitBall->unk84, temp_fs0, 0.0f, &sp90, &sp8C, &sp88);
            splitBall->velocity.x = sp90;
            splitBall->velocity.y = sp8C;
            splitBall->velocity.z = 0.0f;
            splitBall->radarIdx = hudAddWaypoint(sp90, sp8C, sp88);
            if (splitBall->unk6C == 0) {
                splitBall->unk6C = 1.0f;
            }
            splitBall->time80 = 0.5f;
            splitBall->unk97 = 1;
            splitBall->initialized = 0;
            ballsInitBall(splitBall);
            splitBall->initialized = 1;
        }
    }
}

s32 ballsCollision(Ball* ball, Unk802D3658_Unk1228* arg1, Vec3F* arg2) {
    f32 temp_fv0_2;
    Vec3F sp48;
    u8 sp47;

    if (!ball->active) {
        return 0;
    }
    sp48.x = ball->velocity.x - arg2->x;
    sp48.y = ball->velocity.y - arg2->y;
    sp48.z = ball->velocity.z - arg2->z;
    ball->dist = uvVec3Len(&sp48);
    if (ball->unk70 < ball->dist) {
        func_802F996C(ball->pose.m[3][0], ball->pose.m[3][1], ball->pose.m[3][2], (2.0f * D_80359388 * ball->scale));
        uvDobjModel(ball->objId, 0xFFFF);
        ball->objId = 0xFFFF;
        if (ball->radarIdx != 0xFF) {
            hud_8031A8E0(ball->radarIdx);
            ball->radarIdx = 0xFF;
        }
        if (ball->childBallCount != 0) {
            hudText_8031D8E0(0x16C, 1.5f, 8.0f); // "Balloon has split"
            balls_802CB9B4(ball);
        } else {
            hudText_8031D8E0(0x08, 1.5f, 8.0f); // "Balloon cleared"
        }
        ball->hasPopped = TRUE;
        sp47 = uvEmitterLookup();
        uvEmitterFromModel(sp47, 0x38);
        uvEmitterProp(sp47, 1, 0.0f, 2, 500.0f, 5, 0x38, 0);
        uvEmitterSetMatrix(sp47, &ball->pose);
        uvEmitterTrigger(sp47);
        return 1;
    } else {
        temp_fv0_2 = (ball->dist / (1.0f + ball->unk68));
        ball->velocity.x -= temp_fv0_2 * arg1->unk1C.x;
        ball->velocity.y -= temp_fv0_2 * arg1->unk1C.y;
        ball->velocity.z -= temp_fv0_2 * arg1->unk1C.z;
        return 0;
    }
}

f32 ballsPopped(u8 objId, Vec3F* arg1, Unk802D3658_Unk1224* arg2) {
    Unk802D3658_Unk1228* unk4;
    s32 j; // var_s0;
    s32 i; // var_s3;
    s32 count;
    f32 temp_fv1;
    u8 var_s2;

    var_s2 = 0;
    count = arg2->unk0;

    for (i = 0; i < count; i++) {
        unk4 = &arg2->unk4[i];
        if ((unk4->unk4 == 2) && (var_s2 == 0)) {
            for (j = 0; j < gBallCount + gBallSplitCount; j++) {
                if ((unk4->surfaceId == gBalls[j].objId) && (gBalls[j].time80 <= 0.0f)) {
                    if (ballsCollision(&gBalls[j], unk4, arg1) != 0) {
                        return 0.0f;
                    }
                    var_s2++;
                    break;
                }
            }
        }
    }

    if (ballsObjIdExists(objId) == 0) {
        return 1.0f;
    }
    if ((gBalls[j].unk70 < gBalls[j].dist) || (gBalls[j].time80 > 0.0f)) {
        return 0.0f;
    }

    temp_fv1 = gBalls[j].unk68;
    return temp_fv1 / (1.0f + temp_fv1);
}

s32 ballsGetPoints(void) {
    s32 count;
    s32 i;

    count = 0;
    for (i = 0; i < gBallCount + gBallSplitCount; i++) {
        if (gBalls[i].hasPopped) {
            count += gBalls[i].points;
        }
    }
    return count;
}

s32 ballsObjIdExists(u8 objId) {
    s32 i;

    for (i = 0; i < gBallCount + gBallSplitCount; i++) {
        if (objId == gBalls[i].objId) {
            break;
        }
    }
    if (i == gBallCount + gBallSplitCount) {
        return FALSE;
    }
    return TRUE;
}

u8 ballsGetCount(void) {
    return gBallCount + gBallSplitCount;
}

u8 ballsGetAllPopped(void) {
    s32 i;
    s32 ret;

    ret = TRUE;
    for (i = 0; i < gBallCount + gBallSplitCount; i++) {
        if (!gBalls[i].hasPopped) {
            ret = FALSE;
            break;
        }
    }
    return ret;
}
