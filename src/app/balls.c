#include "common.h"
#include <uv_audio.h>
#include <uv_dobj.h>
#include <uv_event.h>
#include <uv_level.h>
#include <uv_math.h>
#include <uv_memory.h>
#include <uv_model.h>
#include "balls.h"
#include "code_61A60.h"
#include "code_66160.h"
#include "code_7FED0.h"
#include "code_9A960.h"
#include "hud.h"

// .data
// list of model ids
s32 D_8034E810[] = { 0xF4, 0xF5, 0xF6 };

// .bss
extern f32 D_80359388; // always set to 5.3241148?
extern LevelBALS* sRefBALS;

// forward declarations
void ballsMotionUpdate(ParsedBALS*);
void ballsFrameUpdateOne(ParsedBALS*);
s32 balls_802CB6D4(ParsedBALS*);
s32 balls_802CC0D4(u8 objId);

// called during startup, during test load menu, and while init any level
void ballsInit(void) {
    ParsedBALS* pb;
    s32 i;

    for (pb = gBalls, i = 0; i < ARRAY_COUNT(gBalls); i++, pb++) {
        pb->idx = i;
        pb->objId = 0xFFFF;
        pb->unk95 = 0;
        pb->unk94 = 0;
        pb->unk64 = 0.0f;
        pb->unk97 = 0;
        pb->unk80 = 0.0f;
        pb->unk1A8 = 0xFF;
        pb->unk5C = 1e7f;
    }
    gBallCount = 0;
    sRefBALS = NULL;
    gBallSplitCount = 0;
}

// called during init of test that has a ball (e.g. RP Balloon tests)
// called for once for each ball (Balloon Rush 1x, Balloon Bonanza 2x)
void ballsInitBall(ParsedBALS* pb) {
    f32 temp_fv1;
    f32 temp_fa0;
    pb->unk5C = 1e7f;
    pb->unkA0.unk0 = 3;
    temp_fv1 = D_80359388;
    temp_fa0 = -D_80359388;
    pb->unkA0.unk4[0].unk0 = 1;
    pb->unkA0.unk4[0].unk28.x = temp_fa0;
    pb->unkA0.unk4[1].unk0 = 1;
    pb->unkA0.unk4[1].unk28.y = temp_fa0;
    pb->unkA0.unk4[2].unk0 = 1;
    pb->unkA0.unk4[2].unk28.z = temp_fa0;
    pb->unkA0.unk4[0].unk1C.x = temp_fv1;
    pb->unkA0.unk4[1].unk1C.y = temp_fv1;
    pb->unkA0.unk4[2].unk1C.z = temp_fv1;
    pb->unkA0.unk4[0].unk28.y = 0.0f;
    pb->unkA0.unk4[0].unk28.z = 0.0f;
    pb->unkA0.unk4[0].unk1C.y = 0.0f;
    pb->unkA0.unk4[0].unk1C.z = 0.0f;
    pb->unkA0.unk4[1].unk28.x = 0.0f;
    pb->unkA0.unk4[1].unk28.z = 0.0f;
    pb->unkA0.unk4[1].unk1C.x = 0.0f;
    pb->unkA0.unk4[1].unk1C.z = 0.0f;
    pb->unkA0.unk4[2].unk28.x = 0.0f;
    pb->unkA0.unk4[2].unk28.y = 0.0f;
    pb->unkA0.unk4[2].unk1C.x = 0.0f;
    pb->unkA0.unk4[2].unk1C.y = 0.0f;
    pb->objId = uvDobjAllocIdx();
    if (pb->unk96 != 0) {
        pb->unk8A = 3;
    } else {
        pb->unk8A = 0;
    }
    uvDobjState(pb->objId, pb->unk8A);
    if (pb->unk78 >= 3u) {
        _uvDebugPrintf("balls: bad vrep %d for ball\n", pb->unk78);
        pb->unk78 = 0;
    }
    uvDobjModel(pb->objId, D_8034E810[pb->unk78]);
    uvDobjProps(pb->objId, 3, (f64)pb->unk7C, 0);
    if (pb->unk95 == 0) {
        uvMat4Scale(&pb->unk4, pb->unk7C, pb->unk7C, pb->unk7C);
    }
    uvDobjPosm(pb->objId, 0, &pb->unk4);
}

// called once during test init if balls loaded
void balls_802CAF50(void) {
    s32 i;

    for (i = 0; i < (gBallCount + gBallSplitCount); i++) {
        if (D_80362690->unk0[D_80362690->unk9C].unkC.unk8 == gBalls[i].unk60) {
            gBalls[i].unk96 = 1;
            if (gBalls[i].objId != 0xFFFF) {
                uvDobjSetState(gBalls[i].objId, 3);
            }
            if (gBalls[i].unk1A8 != 0xFF) {
                hud_8031A874(gBalls[i].unk1A8);
            }
        } else {
            gBalls[i].unk96 = 0;
            if (gBalls[i].objId != 0xFFFF) {
                uvDobjClearState(gBalls[i].objId, 3);
            }
            if (gBalls[i].unk1A8 != 0xFF) {
                hud_8031A810(gBalls[i].unk1A8);
            }
        }
    }
}

// called from task.c to load BALS data for test. always called no matter veh, class, test
// even called again after pause + check-map + continue
void ballsLoad(void) {
    s32 i;
    ParsedBALS* pb;
    LevelBALS* ball;

    if (D_80362690->unkA0) {
        gBallCount = levelDataGetBALS(&sRefBALS);
        if (gBallCount >= 0x15) {
            _uvDebugPrintf("balls : too many balls defined in level [%d]\n", gBallCount);
            gBallCount = 0;
        } else if (gBallCount != 0) {
            uvLevelAppend(0x11);
            uvModelGetProps(0xF4, 1, &D_80359388, 0);
            for (i = 0; i < (gBallCount + gBallSplitCount); i++) {
                ball = &sRefBALS[i];
                pb = &gBalls[i];
                if (pb->unk94 != 0) {
                    continue;
                }

                if (pb->unk95 == 0) {
                    pb->unk94 = 0;
                    pb->unk44.z = 0.0f;
                    pb->unk44.y = 0.0f;
                    pb->unk44.x = 0.0f;
                    pb->unk50.z = 0.0f;
                    pb->unk50.y = 0.0f;
                    pb->unk50.x = 0.0f;
                    pb->unk60 = (u8)ball->unk18;
                    pb->unk96 = 1;
                    if (ball->unk21 != 0) {
                        pb->unk79 = 5;
                    } else {
                        pb->unk79 = 0;
                    }
                    pb->unk84 = ball->unk1C;
                    pb->unk70 = ball->unk24;
                    pb->unk6C = ball->unk28;
                    pb->unk68 = ball->unk2C;
                    pb->unk8C = ball->unk34;
                    pb->unk90 = ball->unk38;
                    pb->unk7C = ball->scale;
                    pb->unk78 = ball->type;
                    pb->unk98 = ball->unk3C;
                    pb->unk9C = ball->unk40;
                    uvMat4SetIdentity(&pb->unk4);
                    pb->unk4.m[3][0] = ball->pos.x;
                    pb->unk4.m[3][1] = ball->pos.y;
                    pb->unk4.m[3][2] = ball->pos.z;
                    ballsInitBall(&gBalls[i]);
                    pb->unk95 = 1;
                    pb->unk1A8 = hud_8031A6C8(ball->pos.x, ball->pos.y, ball->pos.z);
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
void ballsMotionUpdate(ParsedBALS* pb) {
    f32 dx;
    f32 dy;

    dx = -pb->unk98 * pb->unk44.x * pb->unk44.x;
    if (pb->unk44.x < 0.0f) {
        dx = -dx;
    }

    dy = -pb->unk98 * pb->unk44.y * pb->unk44.y;
    if (pb->unk44.y < 0.0f) {
        dy = -dy;
    }

    pb->unk50.x += dx;
    pb->unk50.y += dy;
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
    ParsedBALS* ptr;
    s32 i;

    if (D_80362690->unkA0) {
        for (i = 0; i < gBallCount + gBallSplitCount; i++) {
            ptr = &gBalls[i];
            if (ptr->objId == 0xFFFF) {
                continue;
            }
            if (ptr->unk96 == 0) {
                continue;
            }
            if (ptr->unk80 > 0.0f) {
                ptr->unk80 -= D_8034F854;
            }
            if ((ptr->unk6C > 0.0f) && (ptr->unk94 == 0)) {
                ballsFrameUpdateOne(ptr);
            }
        }
    }
}

// updates ball motion
// not called for balls that are motionless
void ballsFrameUpdateOne(ParsedBALS* pb) {
    f32 ts;
    f32 temp_fv0_2;
    f32 grav;

    pb->unk50.x = 0.0f;
    pb->unk50.y = 0.0f;
    pb->unk50.z = 0.0f;

    ts = D_8034F854;

    ballsMotionUpdate(pb);
    if (balls_802CB6D4(pb) == 0) {
        if (pb->unk9C == 0.0f) {
            grav = 9.8f;
        } else {
            grav = pb->unk9C;
        }
        pb->unk50.z -= grav;
    }

    temp_fv0_2 = pb->unk44.z;
    pb->unk44.x += pb->unk50.x * ts;
    pb->unk44.y += pb->unk50.y * ts;
    pb->unk44.z += pb->unk50.z * ts;
    pb->unk4.m[3][0] += pb->unk44.x * ts;
    pb->unk4.m[3][1] += pb->unk44.y * ts;
    pb->unk4.m[3][2] += pb->unk44.z * ts;
    if ((pb->unk44.z < 0.0f) && ((pb->unk44.z * temp_fv0_2) < 0.0f)) {
        pb->unk5C = pb->unk4.m[3][2];
    }

    func_802E07D8(&pb->unk4);
    uvDobjPosm(pb->objId, 0, &pb->unk4);
    if (pb->unk1A8 != 0xFF) {
        hud_8031A794(pb->unk1A8, pb->unk4.m[3][0], pb->unk4.m[3][1], pb->unk4.m[3][2]);
    }
}

s32 balls_802CB6D4(ParsedBALS* pb) {
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

    if (func_802DB050(&pb->unkA0, &sp5C, pb->objId, pb->unk8A, &pb->unk4) <= 0) {
        return 0;
    }
    idx = func_802DBF10(&pb->unkA0, &sp5C, &sp1B8, &sp1AC);
    if ((sp5C.unk4[idx].unk4 != 1) && (sp5C.unk4[idx].unk4 != 4)) {
        var_fv1 = pb->unk6C;
    } else {
        if (pb->unk5C - sp1B8.z < (10.0f + D_80359388 * pb->unk7C)) {
            var_fv1 = 1.25f;
        } else if (pb->unk5C - sp1B8.z < (11.0f + D_80359388 * pb->unk7C)) {
            var_fv1 = 1.0f;
        } else {
            var_fv1 = pb->unk6C;
        }
    }
    var_fa0 = uvVec3Dot(&pb->unk44, &sp1AC);
    if (uvAbs((s32)var_fa0) < 5.0f) {
        var_fa0 = -5.0f;
    }
    if (var_fa0 < 0.0f) {
        pb->unk44.x -= (2.0f * var_fa0) * sp1AC.x;
        pb->unk44.y -= (2.0f * var_fa0) * sp1AC.y;
        pb->unk44.z -= (2.0f * var_fa0) * sp1AC.z;
        pb->unk50.x = 0.0f;
        pb->unk50.y = 0.0f;
        pb->unk50.z = 0.0f;
        pb->unk44.x *= var_fv1;
        pb->unk44.y *= var_fv1;
        pb->unk44.z *= var_fv1;
    }
    if (uvVec3Len(&pb->unk44) > 1.0f) {
        if (((uvVec3Len(&pb->unk44) / var_fa0) < 0.5f) && ((pb->unk64 + 0.25f) < D_8034F850)) {
            pb->unk64 = D_8034F850;
            obj_id = uvEmitterLookup();
            uvEmitterFromModel(obj_id, 0x37);
            uvEmitterProp(obj_id, 1, 0.0f, 2, 500.0f, 5, 0x38, 0);
            uvEmitterSetMatrix(obj_id, &pb->unk4);
            uvEmitterTrigger(obj_id);
        }
    }
    return 1;
}

void balls_802CB9B4(ParsedBALS* pb) {
    LevelBALS* ball;
    ParsedBALS* alloc;
    f32 temp_fs0;
    s32 i;
    s32 pad;
    f32 sp90;
    f32 sp8C;
    f32 sp88;

    for (i = 0; i < pb->unk79; i++) {
        if ((gBallCount + gBallSplitCount) < ARRAY_COUNT(gBalls)) {
            alloc = &gBalls[gBallSplitCount + gBallCount];
            gBallSplitCount++;
            *alloc = *pb;
            ball = &sRefBALS[pb->idx];
            alloc->unk70 = ball->unk48;
            alloc->unk6C = ball->unk4C;
            alloc->unk68 = ball->unk50;
            alloc->unk8C = ball->unk54;
            alloc->unk90 = ball->unk58;
            alloc->unk7C = ball->unk5C;
            alloc->unk78 = ball->pad44[0];
            alloc->unk98 = ball->unk60;
            alloc->unk9C = ball->unk64;
            alloc->unk79 = 0;

            temp_fs0 = i * (6.2831855f / pb->unk79); // 2*pi or DEG_TO_RAD(360)
            func_803134D0(pb->unk7C * D_80359388, temp_fs0, 0.0f, &sp90, &sp8C, &sp88);
            uvMat4LocalTranslate(&alloc->unk4, sp90, sp8C, sp88);
            func_803134D0(alloc->unk84, temp_fs0, 0.0f, &sp90, &sp8C, &sp88);
            alloc->unk44.x = sp90;
            alloc->unk44.y = sp8C;
            alloc->unk44.z = 0.0f;
            alloc->unk1A8 = hud_8031A6C8(sp90, sp8C, sp88);
            if (alloc->unk6C == 0) {
                alloc->unk6C = 1.0f;
            }
            alloc->unk80 = 0.5f;
            alloc->unk97 = 1;
            alloc->unk95 = 0;
            ballsInitBall(alloc);
            alloc->unk95 = 1;
        }
    }
}

s32 ballsCollision(ParsedBALS* pb, Unk802D3658_Unk1228* arg1, Vec3F* arg2) {
    f32 temp_fv0_2;
    Vec3F sp48;
    u8 sp47;

    if (pb->unk96 == 0) {
        return 0;
    }
    sp48.x = pb->unk44.x - arg2->x;
    sp48.y = pb->unk44.y - arg2->y;
    sp48.z = pb->unk44.z - arg2->z;
    pb->unk74 = uvVec3Len(&sp48);
    if (pb->unk70 < pb->unk74) {
        func_802F996C(pb->unk4.m[3][0], pb->unk4.m[3][1], pb->unk4.m[3][2], (2.0f * D_80359388 * pb->unk7C));
        uvDobjModel(pb->objId, 0xFFFF);
        pb->objId = 0xFFFF;
        if (pb->unk1A8 != 0xFF) {
            hud_8031A8E0(pb->unk1A8);
            pb->unk1A8 = 0xFF;
        }
        if (pb->unk79 != 0) {
            hudText_8031D8E0(0x16C, 1.5f, 8.0f);
            balls_802CB9B4(pb);
        } else {
            hudText_8031D8E0(8, 1.5f, 8.0f);
        }
        pb->unk94 = 1;
        sp47 = uvEmitterLookup();
        uvEmitterFromModel(sp47, 0x38);
        uvEmitterProp(sp47, 1, 0.0f, 2, 500.0f, 5, 0x38, 0);
        uvEmitterSetMatrix(sp47, &pb->unk4);
        uvEmitterTrigger(sp47);
        return 1;
    } else {
        temp_fv0_2 = (pb->unk74 / (1.0f + pb->unk68));
        pb->unk44.x -= temp_fv0_2 * arg1->unk1C.x;
        pb->unk44.y -= temp_fv0_2 * arg1->unk1C.y;
        pb->unk44.z -= temp_fv0_2 * arg1->unk1C.z;
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
                if ((unk4->unk8 == gBalls[j].objId) && (gBalls[j].unk80 <= 0.0f)) {
                    if (ballsCollision(&gBalls[j], unk4, arg1) != 0) {
                        return 0.0f;
                    }
                    var_s2++;
                    break;
                }
            }
        }
    }

    if (balls_802CC0D4(objId) == 0) {
        return 1.0f;
    }
    if ((gBalls[j].unk70 < gBalls[j].unk74) || (gBalls[j].unk80 > 0.0f)) {
        return 0.0f;
    }

    temp_fv1 = gBalls[j].unk68;
    return temp_fv1 / (1.0f + temp_fv1);
}

s32 ballsGet_802CC064(void) {
    s32 count;
    s32 i;

    count = 0;
    for (i = 0; i < gBallCount + gBallSplitCount; i++) {
        if (gBalls[i].unk94 != 0) {
            count += gBalls[i].unk8C;
        }
    }
    return count;
}

s32 balls_802CC0D4(u8 objId) {
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

u8 ballsGet_802CC15C(void) {
    s32 i;
    s32 ret;

    ret = TRUE;
    for (i = 0; i < gBallCount + gBallSplitCount; i++) {
        if (gBalls[i].unk94 == 0) {
            ret = FALSE;
            break;
        }
    }
    return ret;
}
