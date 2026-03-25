#include "common.h"
#include <uv_dobj.h>
#include <uv_math.h>
#include <uv_matrix.h>
#include <uv_texture.h>
#include <uv_vector.h>
#include "balls.h"
#include "ball_target.h"
#include "snd.h"
#include "task.h"

typedef struct {
    u16 objId;
    u8 pad2[0x2];
    Vec3F unk4;
    Mtx4F unk10;
    f32 unk50;
    f32 unk54;
    u8 unk58;
    u8 unk59;
    u8 unk5A;
    u8 unk5B;
    u8 unk5C;
    u8 unk5D;
    u8 pad5E[0x60 - 0x5E];
} BallTarget;

static TaskBTGT* sRefBTGT;
static u8 sBallTgtCount;
static BallTarget sBallTgts[5];

void ballTgtInit(void) {
    s32 i;
    for (i = 0; i < ARRAY_COUNT(sBallTgts); i++) {
        sBallTgts[i].objId = 0xFFFF;
        sBallTgts[i].unk5B = 0x00;
        sBallTgts[i].unk5C = 0x00;
        sBallTgts[i].unk5A = 0xFF;
    }
}

void ballTgtUpdateState(void) {
    BallTarget* var_s0;
    s32 i;

    for (i = 0; i < sBallTgtCount; i++) {
        var_s0 = &sBallTgts[i];
        if (D_80362690->unkC[D_80362690->unk9C].unk8 == sRefBTGT[i].unkC) {
            var_s0->unk5D = 1;
            if (var_s0->objId != 0xFFFF) {
                uvDobjSetState(var_s0->objId, 0x2);
            }
        } else {
            _uvDebugPrintf("btgts_terra : %d btgt not in terra\n", i);
            var_s0->unk5D = 0;
            if (var_s0->objId != 0xFFFF) {
                uvDobjClearState(var_s0->objId, 0x2);
            }
        }
    }
}

void ballTgtInitDobj(BallTarget* bt) {
    f32 var_fa0;
    s32 modelId;

    bt->objId = uvDobjAllocIdx();
    modelId = (bt->unk5B) ? MODEL_GREEN_BLUE_GOAL_0 : MODEL_GREEN_BLUE_GOAL_1;
    uvDobjModel(bt->objId, modelId);
    uvMat4SetIdentity(&bt->unk10);
    bt->unk10.m[0][0] = bt->unk50;
    bt->unk10.m[1][1] = bt->unk50;
    bt->unk10.m[2][2] = bt->unk54;
    bt->unk10.m[3][0] = bt->unk4.x;
    bt->unk10.m[3][1] = bt->unk4.y;
    bt->unk10.m[3][2] = bt->unk4.z;
    var_fa0 = MAX(bt->unk50, bt->unk54);
    uvDobjProps(bt->objId, 3, var_fa0, 0);
    uvDobjState(bt->objId, 2);
    uvDobjPosm(bt->objId, 0, &bt->unk10);
}

void ballTgtLoad(void) {
    BallTarget* bt;
    TaskBTGT* lvlBt;
    s32 i;

    if (D_80362690->unkA0 == 0) {
        return;
    }

    sBallTgtCount = taskGetBTGT(&sRefBTGT);
    if (sBallTgtCount > 5) {
        _uvDebugPrintf("btgts : too many btgts defined in level [%d]\n", sBallTgtCount);
        sBallTgtCount = 0;
        return;
    }

    if (sBallTgtCount != 0) {
        uvLevelAppend(0x10);
        for (i = 0; i < sBallTgtCount; i++) {
            lvlBt = &sRefBTGT[i];
            bt = &sBallTgts[i];
            if (bt->unk5B != 0) {
                continue;
            }
            if (bt->unk5C == 0) {
                bt->unk58 = lvlBt->unk18;
                bt->unk59 = lvlBt->unk19;
                bt->unk50 = lvlBt->unk10;
                bt->unk54 = lvlBt->unk14;
                uvVec3Copy(&bt->unk4, &lvlBt->pos);
                bt->unk5C = 1;
            }
            ballTgtInitDobj(bt);
        }
        ballTgtUpdateState();
    }
}

void ballTgt_802D2C20(BallTarget* bt) {
    Ball* ball;
    f32 temp_fa0;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 dist;
    f32 var_fv1;
    s32 var_s2;
    s32 i;

    var_s2 = 0;
    for (i = 0; i < gBallCount + gBallSplitCount; i++) {
        ball = &gBalls[i];
        if ((ball->hasPopped != 0) || (ball->active == 0)) {
            continue;
        }
        dx = bt->unk4.x - ball->pose.m[3][0];
        dy = bt->unk4.y - ball->pose.m[3][1];
        dz = bt->unk4.z - ball->pose.m[3][2];
        dist = uvSqrtF(SQ(dx) + SQ(dy));
        temp_fa0 = bt->unk50 - 0.25f;
        var_fv1 = ball->scale * D_80359388;
        if (((dist - var_fv1) <= temp_fa0) && ((var_fv1 + dist) >= temp_fa0)) {
            var_s2 = 1;
            snd_play_sfx(0x37);
            dx = -(dx / dist);
            dy = -(dy / dist);
            dist = uvSqrtF(SQ(ball->velocity.x) + SQ(ball->velocity.y));
            ball->velocity.x -= dist * dx;
            ball->velocity.y -= dist * dy;
        }
        var_fv1 = ball->scale * D_80359388;
        if (bt->unk54 <= (var_fv1 + dz)) {
            if (var_s2 == 0) {
                snd_play_sfx(0x37);
            }
            ball->velocity.z = -ball->velocity.z;
        }
    }
}

s32 ballTgtInGoal(void) {
    BallTarget* target;
    Ball* ball;
    f32 dz;
    f32 dx;
    f32 dy;
    f32 dist;
    s32 ret; // var_s4;
    s32 i;
    s32 j;

    ret = 0;
    if (D_80362690->unkA0 == 0) {
        return ret;
    }

    for (i = 0; i < sBallTgtCount; i++) {
        target = &sBallTgts[i];
        if (target->unk5D == 0) {
            continue;
        }

        if (target->unk5B != 0) {
            ballTgt_802D2C20(target);
        } else {
            for (j = 0; j < gBallCount + gBallSplitCount; j++) {
                ball = &gBalls[j];
                if ((ball->hasPopped != 0) || (ball->active == 0)) {
                    continue;
                }
                dx = target->unk4.x - ball->pose.m[3][0];
                dy = target->unk4.y - ball->pose.m[3][1];
                dz = target->unk4.z - ball->pose.m[3][2];
                dist = uvSqrtF(SQ(dx) + SQ(dy));
                if ((dist < target->unk50) && (dz < target->unk54)) {
                    target->unk5B = 1;
                    ret = 1;
                    snd_play_sfx(0x11);
                    uvDobjModel(target->objId, MODEL_WORLD);
                    ballTgtInitDobj(target);
                    target->unk5A = j;
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
        if (bt->objId != 0xFFFF) {
            uvDobjModel(bt->objId, MODEL_WORLD);
            bt->objId = 0xFFFF;
        }
    }
}

u8 ballTgtCount_5B(void) {
    s32 i;
    u8 ret;

    ret = 0;
    for (i = 0; i < sBallTgtCount; i++) {
        ret += (sBallTgts[i].unk5B != 0) ? 1 : 0;
    }
    return ret;
}

s16 ballTgtCount_59(void) {
    BallTarget* bt;
    s32 sum;
    s32 i;

    sum = 0;
    for (i = 0; i < sBallTgtCount; i++) {
        bt = &sBallTgts[i];
        sum += (bt->unk5B) ? bt->unk59 : 0;
    }
    return sum;
}
