#include "common.h"
#include <uv_dobj.h>
#include <uv_math.h>
#include <uv_matrix.h>
#include <uv_texture.h>
#include <uv_vector.h>
#include "balls.h"
#include "ball_target.h"
#include "macros.h"
#include "snd.h"
#include "task.h"

#define BALL_ID_NONE 0xFF

typedef struct {
    u16 objId;
    Vec3F position;
    Mtx4F pose;
    f32 radius;
    f32 height;
    u8 unk58;
    u8 goalPoints;
    u8 ballIdInGoal;
    u8 isBallInGoal;
    u8 goalInitialized;
    u8 goalInTerra;
} BallTarget;

STATIC_DATA TaskBTGT* sRefBTGT;
STATIC_DATA u8 sBallTgtCount;
STATIC_DATA BallTarget sBallTgts[5];

void ballTgtInit(void) {
    s32 i;
    for (i = 0; i < ARRAY_COUNT(sBallTgts); i++) {
        sBallTgts[i].objId = OBJ_INVALID;
        sBallTgts[i].isBallInGoal = FALSE;
        sBallTgts[i].goalInitialized = FALSE;
        sBallTgts[i].ballIdInGoal = BALL_ID_NONE;
    }
}

void ballTgtUpdateState(void) {
    BallTarget* target;
    s32 i;

    for (i = 0; i < sBallTgtCount; i++) {
        target = &sBallTgts[i];
        if (D_80362690->unkC[D_80362690->unk9C].unk8 == sRefBTGT[i].terra) {
            target->goalInTerra = TRUE;
            if (target->objId != OBJ_INVALID) {
                uvDobjSetState(target->objId, 0x2);
            }
        } else {
            _uvDebugPrintf("btgts_terra : %d btgt not in terra\n", i);
            target->goalInTerra = FALSE;
            if (target->objId != OBJ_INVALID) {
                uvDobjClearState(target->objId, 0x2);
            }
        }
    }
}

void ballTgtInitDobj(BallTarget* bt) {
    f32 dist;
    s32 modelId;

    bt->objId = uvDobjAllocIdx();
    modelId = (bt->isBallInGoal) ? MODEL_GREEN_BLUE_GOAL_0 : MODEL_GREEN_BLUE_GOAL_1;
    uvDobjModel(bt->objId, modelId);
    uvMat4SetIdentity(&bt->pose);
    bt->pose.m[0][0] = bt->radius;
    bt->pose.m[1][1] = bt->radius;
    bt->pose.m[2][2] = bt->height;
    bt->pose.m[3][0] = bt->position.x;
    bt->pose.m[3][1] = bt->position.y;
    bt->pose.m[3][2] = bt->position.z;
    dist = MAX(bt->radius, bt->height);
    uvDobjProps(bt->objId, 3, dist, 0);
    uvDobjState(bt->objId, 2);
    uvDobjPosm(bt->objId, 0, &bt->pose);
}

void ballTgtLoad(void) {
    BallTarget* bt;
    TaskBTGT* btgt;
    s32 i;

    if (D_80362690->unkA0 == 0) {
        return;
    }

    sBallTgtCount = taskGetBTGT(&sRefBTGT);
    if (sBallTgtCount > ARRAY_COUNT(sBallTgts)) {
        _uvDebugPrintf("btgts : too many btgts defined in level [%d]\n", sBallTgtCount);
        sBallTgtCount = 0;
        return;
    }

    if (sBallTgtCount != 0) {
        uvLevelAppend(0x10);
        for (i = 0; i < sBallTgtCount; i++) {
            btgt = &sRefBTGT[i];
            bt = &sBallTgts[i];
            if (bt->isBallInGoal) {
                continue;
            }
            if (!bt->goalInitialized) {
                bt->unk58 = btgt->unk18;
                bt->goalPoints = btgt->goalPoints;
                bt->radius = btgt->radius;
                bt->height = btgt->height;
                uvVec3Copy(&bt->position, &btgt->pos);
                bt->goalInitialized = TRUE;
            }
            ballTgtInitDobj(bt);
        }
        ballTgtUpdateState();
    }
}

void ballTgt_802D2C20(BallTarget* bt) {
    Ball* ball;
    f32 goalRadius;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 dist;
    f32 ballSize;
    s32 sfxPlayed;
    s32 i;

    sfxPlayed = FALSE;
    for (i = 0; i < gBallCount + gBallSplitCount; i++) {
        ball = &gBalls[i];
        if ((ball->hasPopped) || (!ball->active)) {
            continue;
        }
        dx = bt->position.x - ball->pose.m[3][0];
        dy = bt->position.y - ball->pose.m[3][1];
        dz = bt->position.z - ball->pose.m[3][2];
        dist = uvSqrtF(SQ(dx) + SQ(dy));
        goalRadius = bt->radius - 0.25f;
        ballSize = ball->scale * D_80359388;
        if (((dist - ballSize) <= goalRadius) && ((ballSize + dist) >= goalRadius)) {
            sfxPlayed = TRUE;
            sndPlaySfx(SFX_UNK_055);
            dx = -(dx / dist);
            dy = -(dy / dist);
            dist = uvSqrtF(SQ(ball->velocity.x) + SQ(ball->velocity.y));
            ball->velocity.x -= dist * dx;
            ball->velocity.y -= dist * dy;
        }
        ballSize = ball->scale * D_80359388;
        if (bt->height <= (ballSize + dz)) {
            if (!sfxPlayed) {
                sndPlaySfx(SFX_UNK_055);
            }
            ball->velocity.z = -ball->velocity.z;
        }
    }
}

s32 ballTgtInGoal(void) {
    BallTarget* bt;
    Ball* ball;
    f32 dz;
    f32 dx;
    f32 dy;
    f32 dist;
    s32 ret;
    s32 i;
    s32 j;

    ret = FALSE;
    if (D_80362690->unkA0 == 0) {
        return ret;
    }

    for (i = 0; i < sBallTgtCount; i++) {
        bt = &sBallTgts[i];
        if (!bt->goalInTerra) {
            continue;
        }

        if (bt->isBallInGoal) {
            ballTgt_802D2C20(bt);
        } else {
            for (j = 0; j < gBallCount + gBallSplitCount; j++) {
                ball = &gBalls[j];
                if ((ball->hasPopped) || (!ball->active)) {
                    continue;
                }
                dx = bt->position.x - ball->pose.m[3][0];
                dy = bt->position.y - ball->pose.m[3][1];
                dz = bt->position.z - ball->pose.m[3][2];
                dist = uvSqrtF(SQ(dx) + SQ(dy));
                if ((dist < bt->radius) && (dz < bt->height)) {
                    bt->isBallInGoal = TRUE;
                    ret = TRUE;
                    sndPlaySfx(SFX_GOAL_GONG);
                    uvDobjModel(bt->objId, MODEL_WORLD);
                    ballTgtInitDobj(bt);
                    bt->ballIdInGoal = j;
                }
            }
        }
    }
    return ret;
}

void ballTgtDeinit(void) {
    BallTarget* bt;
    s32 i;

    for (i = 0; i < sBallTgtCount; i++) {
        bt = &sBallTgts[i];
        if (bt->objId != OBJ_INVALID) {
            uvDobjModel(bt->objId, MODEL_WORLD);
            bt->objId = OBJ_INVALID;
        }
    }
}

u8 ballTgtGetGoalCount(void) {
    s32 i;
    u8 count;

    count = 0;
    for (i = 0; i < sBallTgtCount; i++) {
        count += (sBallTgts[i].isBallInGoal) ? 1 : 0;
    }
    return count;
}

s16 ballTgtGetScore(void) {
    s32 scoreSum;
    s32 i;

    scoreSum = 0;
    for (i = 0; i < sBallTgtCount; i++) {
        scoreSum += (sBallTgts[i].isBallInGoal) ? sBallTgts[i].goalPoints : 0;
    }
    return scoreSum;
}
