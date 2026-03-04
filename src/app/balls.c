#include "common.h"
#include <uv_audio.h>
#include <uv_dobj.h>
#include <uv_event.h>
#include <uv_level.h>
#include <uv_math.h>
#include <uv_memory.h>
#include <uv_model.h>
#include "balls.h"
#include "birdman.h"
#include "bmsound.h"
#include "code_556C0.h"
#include "code_5A6A0.h"
#include "code_61A60.h"
#include "code_66160.h"
#include "code_72B70.h"
#include "code_7FED0.h"
#include "code_9A960.h"
#include "demo.h"
#include "fdr.h"
#include "hud.h"
#include "shadow.h"
#include "snap.h"
#include "snd.h"

// .data
// list of model ids
s32 D_8034E810[] = { 0xF4, 0xF5, 0xF6 };

// .bss
extern f32 D_80359388; // always set to 5.3241148?
extern LevelBALS* sRefBALS;
// part of split file?
extern Unk803599D0 D_80359390;
extern u8 D_803593E4;

// forward declarations
void ballsMotionUpdate(ParsedBALS*);
void ballsFrameUpdateOne(ParsedBALS*);
s32 balls_802CB6D4(ParsedBALS*);
s32 balls_802CC0D4(u8 objId);
void bird_802CD0F8(Unk80367704*);
void bird_802CD2E8(u8, Unk80367704*);
void bird_802CE0A4(Unk80367704*);

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

// called during game boot
void bird_802CC1B0(void) {
    D_80359390.unk0 = 8;
    D_80359390.unk4 = 0.0f;
    D_80359390.unk8 = 0.0f;
    D_80359390.unkC = 0.2f;
    D_80359390.unk10 = 0.04f;
    D_80359390.unk14 = 0.4f;
    D_80359390.unk18 = 0.16f;
    D_80359390.unk1C = 0.6f;
    D_80359390.unk20 = 0.36f;
    D_80359390.unk24 = 0.7f;
    D_80359390.unk28 = 0.49f;
    D_80359390.unk2C = 0.8f;
    D_80359390.unk30 = 0.64f;
    D_80359390.unk34 = 0.9f;
    D_80359390.unk38 = 0.81f;
    D_80359390.unk40 = 1.0f;
    D_80359390.unk3C = 1.0f;
}

// called when starting one of the birdman levels, either from bonus menu or bonus star
void bird_802CC270(u8 arg0, u8 pilot, Unk80367704* arg2, Unk802D3658_Arg0* arg3) {
    uvMemSet(arg2, 0, 0x424);
    bird_802CD2E8(pilot, arg2);
    arg2->unk0 = uvDobjAllocIdx();
    arg2->unk2 = 2;
    uvDobjModel(arg2->unk0, arg2->unk3F4);
    uvDobjPosm(arg2->unk0, 0, &arg2->unk10);
    uvDobjState(arg2->unk0, arg2->unk2);
    uvMat4Copy(&arg2->unk50, &arg2->unk10);
    func_80334454(0x13D, 0x13C);
    func_803342F0(1.0f);
    func_803342FC(-2.0f);
    func_803343D8(1);
    arg2->controller = arg0;
    arg2->unk2F0 = 0;
    arg2->unk2CC = 0x1A;
    arg2->unk4 = 0;
    arg2->unkD4 = arg3;
    arg2->unk2BC = 0.0f;
    arg2->unk2C4 = 0.0f;
    arg2->unk2D0 = 0.0f;
    arg2->unk2D4 = 0.0f;
    arg2->unk2D8 = 0.0f;
    arg2->unk2DC = 0.0f;
    uvModelGetProps(arg2->unk3F4, 1, &arg3->unk8, 0);
    func_802CEBA0(arg2);
    func_802D0BF0(arg2);
}

// called when entering or exiting a birdman level
void bird_802CC39C(Unk80367704* arg0) {
    db_getstart(&arg0->unk10, &arg0->unk200, NULL, NULL);
    uvDobjPosm((s32)arg0->unk0, 0, &arg0->unk10);
    uvMat4Copy(&arg0->unk50, &arg0->unk10);
    func_802CECB8(arg0);
    arg0->unk104 = 0;
    arg0->unk105 = 0;
    arg0->unk2 = 2;
    arg0->unk290 = 1;
    arg0->unkEC = 0.0f;
    arg0->unkF0 = 0.0f;
    arg0->unk8 = 0.0f;
    arg0->unk2FC = 0.0f;
    arg0->unk300 = 0.0f;
    arg0->unk304 = 0.0f;
    arg0->unk308 = 0.0f;
    arg0->unk2E8 = 0.0f;
    arg0->unk2E0 = 0.0f;
    arg0->unk2EC = 0.0f;
    arg0->unk2E4 = 0.0f;
    bird_802CE0A4(arg0);
    arg0->unkD8 = 0;
    arg0->unkDC = 1.0f;
    arg0->unkD4->unk1 = arg0->unkD8;
    arg0->unkD4->unk4 = arg0->unk0;
    arg0->unkD4->unk6 = arg0->unk2;
    arg0->unkD4->unk0 = 1;
    arg0->unkD4->unk74 = 0.0f;
    arg0->unkD4->unk5C = 0;
    arg0->unkD4->unk60 = -3.5f;
    arg0->unkD4->unk64 = 0.5f;
    arg0->unkD4->unk54 = 3.0f;
    arg0->unkD4->unk58 = 6.5f;
    arg0->unkD4->unk48 = 0.0125f;
    arg0->unkD4->unk4C = 1.0f;
    arg0->unkD4->unk50 = 0.0f;
    arg0->unkD4->unk228 = 0.0f;
    D_803593E4 = 0;
    func_802D45C4(arg0->unkD4, arg0->unkDC);
}

// called when exiting a birdman level
void bird_802CC51C(Unk802CC51C* arg0) {
    uvDobjModel(arg0->objId, 0xFFFF);
    arg0->unkC = 0xFFFF;
    arg0->objId = 0xFFFF;
    func_80334C70();
}

// called every frame in a birdman stage
// handles controller input and motion updates
void bird_802CC55C(Unk80367704* arg0, u8 arg1) {
    f32 sp7C;
    f32 sp78;
    f32 pad;
    s32 buttons;
    HUDState* sp6C;
    s32 sp68;
    f32 temp_fv0;
    f32 sp4C[6];
    f32 var_fa0;
    s32 pad2;
    f32 var_fv0;
    f32 var_fv1;

    sp68 = 0;
    if (arg0->unk104 == 2) {
        bird_802CD0F8(arg0);
        return;
    }
    if (func_802E6B5C() != 4) {
        arg0->unk8 += D_8034F854;
        if (D_80362690->unk0[D_80362690->unk9C].unkC.unk7B == 0) {
            func_80339E1C(arg0);
        }
        if (arg1 == 6) {
            func_802E65AC(&arg0->unk10, &D_80362690->unk0[0].unk6, &sp7C, &sp78, &buttons);
        } else {
            sp7C = demoGetInputs(arg0->controller, INPUT_AXIS_X);
            sp78 = demoGetInputs(arg0->controller, INPUT_AXIS_Y);
            buttons = demoGetButtons(arg0->controller);
            if (sp7C > 0.0f) {
                var_fv0 = sp7C;
            } else {
                var_fv0 = -sp7C;
            }
            temp_fv0 = func_80313F08(&D_80359390, var_fv0);
            if (sp7C >= 0.0f) {
                sp7C = temp_fv0;
            } else {
                sp7C = -temp_fv0;
            }
            if (sp78 > 0.0f) {
                var_fv0 = sp78;
            } else {
                var_fv0 = -sp78;
            }
            temp_fv0 = func_80313F08(&D_80359390, var_fv0);
            if (sp78 >= 0.0f) {
                sp78 = temp_fv0;
            } else {
                sp78 = -temp_fv0;
            }
        }
        if (D_803593E4 != 0) {
            arg0->unkE4 = func_80313AF4(0.0f, arg0->unkE4, 3.0f);
            arg0->unkE8 = func_80313AF4(0.0f, arg0->unkE8, 3.0f);
        } else {
            arg0->unkE4 = func_80313AF4(sp7C, arg0->unkE4, 3.0f);
            arg0->unkE8 = func_80313AF4(sp78, arg0->unkE8, 3.0f);
        }
        if (demoButtonPress(arg0->controller, A_BUTTON)) {
            sp68 = 1;
            arg0->unk2DC -= 0.25f;
        }
        if (demoButtonPress(arg0->controller, B_BUTTON)) {
            sp68 = 1;
            arg0->unk2DC += 0.25f;
        }
        arg0->unk2DC = func_80313AF4(0.0f, arg0->unk2DC, 1.0f);
        arg0->unk2D4 += arg0->unk2DC * D_8034F854;
        if (arg0->unk2D4 < 0.f) {
            arg0->unk2D4 = 0.f;
        }
        if (arg0->unk2D4 > 1.5707f) {
            arg0->unk2D4 = 1.5707f;
        }
        if (sp68 != 0) {
            arg0->unk2D0 += 9.0f * D_8034F854;
            if (arg0->unk2D0 > 3.8f) {
                arg0->unk2D0 = 3.8f;
            }
        } else {
            arg0->unk2D0 = func_80313AF4(0.0f, arg0->unk2D0, 0.5f);
            arg0->unk2D4 = func_80313AF4(0.0f, arg0->unk2D4, 0.4f);
        }
        if (arg1 != 6) {
            func_802CEDF8(arg0);
        }
        func_802CE190(arg0, arg1);
        if (arg1 != 6) {
            sp4C[0] = arg0->unkD0;
            sp4C[1] = arg0->unk2D0;
            sp4C[2] = arg0->unk2D4;
            sp4C[3] = (f32)arg0->unk2C0;
            sp4C[4] = arg0->unk304;
            sp4C[5] = arg0->unk308;
            func_802E682C(sp4C, ARRAY_COUNT(sp4C), 0);
        } else {
            func_802E6870(sp4C, ARRAY_COUNT(sp4C), NULL);
            arg0->unkD0 = sp4C[0];
            arg0->unk2D0 = sp4C[1];
            arg0->unk2D4 = sp4C[2];
            arg0->unk2C0 = (u8)sp4C[3];
            arg0->unk304 = sp4C[4];
            arg0->unk308 = sp4C[5];
        }
        if (arg1 != 6) {
            arg0->unkD0 = -1.57f;
            if (arg0->unk224 < 25.0f) {
                var_fa0 = (((25.0f - arg0->unk224) * 1.57f) / 25.0f) + -1.57f;
                if ((arg0->unk16C < 4.0f) && (arg0->unk224 < 10.0f)) {
                    arg0->unkD0 = (((4.0f - arg0->unk16C) * 1.57f) / 2.5f) + -1.57f;
                }
                if (var_fa0 < arg0->unkD0) {
                    arg0->unkD0 = arg0->unkD0;
                } else {
                    arg0->unkD0 = var_fa0;
                }
            }
            if (arg0->unkD0 > 0.0f) {
                arg0->unkD0 = 0.0f;
            }
        }
        uvMat4SetIdentity(&arg0->unk90);
        uvMat4RotateAxis(&arg0->unk90, arg0->unkD0, 'x');
        uvMat4Mul(&arg0->unk50, &arg0->unk90, &arg0->unk10);
        uvDobjPosm(arg0->unk0, 0, &arg0->unk50);
        func_803344BC(&arg0->unk10, arg0->unk16C);
        if (arg0->unk224 > 25.0f) {
            arg0->unkD4->unk48 = 0.0125f;
            arg0->unkD4->unk5C = 0.0f;
            arg0->unkD4->unk60 = -3.5f;
            arg0->unkD4->unk64 = 0.5f;
        } else {
            var_fa0 = -arg0->unkD0 / 1.57f;
            var_fv1 = arg0->unk224 / 25.0f;
            if (var_fa0 < 0.0f) {
                var_fa0 = 0.0f;
            } else if (var_fa0 > 1.0f) {
                var_fa0 = 1.0f;
            }
            if (var_fv1 < 0.0f) {
                var_fv1 = 0.0f;
            } else if (var_fv1 > 1.0f) {
                var_fv1 = 1.0f;
            }
            if (var_fv1 < var_fa0) {
                var_fv0 = var_fa0;
            } else {
                var_fv0 = var_fv1;
            }
            arg0->unkD4->unk48 = ((1.0f - var_fv0) * 0.15f) + (var_fv0 * 0.0125f);
            arg0->unkD4->unk5C = 0 * var_fv0;

            arg0->unkD4->unk60 = (2.5f * var_fv0) + -6.0f;
            arg0->unkD4->unk64 = (0.4f * var_fv0) + 0.1f;
        }
        if (D_803593E4 == 0) {
            if (buttons & L_CBUTTONS) {
                var_fa0 = 1.5707963f;
            } else if (buttons & R_CBUTTONS) {
                var_fa0 = -1.5707963f;
            } else {
                var_fa0 = 0.0f;
            }
            arg0->unkEC = func_80313AF4(var_fa0, arg0->unkEC, 1.1f);
            if (buttons & D_CBUTTONS) {
                var_fa0 = 1.5707963f;
            } else if (buttons & U_CBUTTONS) {
                var_fa0 = -1.5707963f;
            } else {
                var_fa0 = 0.0f;
            }
            arg0->unkF0 = func_80313AF4(var_fa0, arg0->unkF0, 1.1f);
        } else {
            arg0->unkEC = func_80313AF4(demoGetInputs(arg0->controller, 0) * -1.5707963f, arg0->unkEC, 3.0f);
            arg0->unkF0 = func_80313AF4(demoGetInputs(arg0->controller, 1) * -1.5707963f, arg0->unkF0, 3.0f);
        }
        if (demoButtonPress(arg0->controller, R_TRIG) && (arg1 != 6) && (arg0->unk104 != 1)) {
            D_803593E4 = 0;
            if (arg0->unkD8 == 1) {
                func_8033F758(0x6A, 1.0f, 0.5f, 0.0f);
                arg0->unkD8 = 0;
                arg0->unkDC = 1.0f;
                func_80334454(0x13D, 0x13C);
                arg0->unk290 = 1;
                bird_802CE0A4(arg0);
            } else {
                func_8033F758(0x6A, 1.0f, 0.5f, 0.0f);
                arg0->unkD8 = 1;
                arg0->unkDC = 0.8f;
                func_80334454(0x13D, 0x13C);
                arg0->unk290 = 0;
                bird_802CE0A4(arg0);
            }
            func_802D5884(arg0->unkD4, arg0->unkD8);
            func_802D45C4(arg0->unkD4, arg0->unkDC);
        }
        if (arg1 != 6) {
            arg0->unkD4->unk4 = arg0->unk0;
            arg0->unkD4->unk6 = arg0->unk2;
            arg0->unkD4->unk78 = arg0->unkEC;
            arg0->unkD4->unk7C = arg0->unkF0;
            arg0->unkD4->unk228 = arg0->unk16C;
            uvMat4LocalToWorld(&arg0->unk90, &arg0->unkD4->unk68, &arg0->unk294);
            uvMat4Copy(&arg0->unkD4->unk80, &arg0->unk10);
            if (arg0->unk104 == 1) {
                func_802D5884(arg0->unkD4, 6);
                arg0->unk2 = 2;
                uvDobjState(arg0->unk0, arg0->unk2);
            } else {
                func_802D5884(arg0->unkD4, arg0->unkD8);
            }
            func_802D45C4(arg0->unkD4, arg0->unkDC);
        }
        if ((arg0->unkD8 == 1) && (arg0->unk104 != 1) && (arg1 != 6)) {
            arg0->unk290 = 0;
        } else {
            arg0->unk290 = 1;
        }
        if (arg0->unkD4->unk148 != 0) {
            arg0->unk290 = 1;
        }
        bird_802CE0A4(arg0);
        if (arg1 != 6) {
            sp6C = hudGetState();
            uvMat4Copy(&sp6C->unk28, &arg0->unk10);
            sp6C->renderFlags = 0x80;
            sp6C->att.heading = arg0->unk10.m[3][2];
            sp6C->elapsedTime = arg0->unk8;
            sp6C->unk8C = arg0->unk220 * 4.0f * 0.7f;
            sp6C->altitude = arg0->unk16C * 0.7f;
            sp6C->altSeaLevel = arg0->unk10.m[3][2] * 0.7f;
            sp6C->speed = arg0->unk224 * 3.6f * 0.7f;
        }
        if ((arg0->unk104 == 1) || (arg0->unk104 == 2)) {
            sp6C->renderFlags = 0;
        }
        func_802E06AC(&arg0->unk10);
        if (arg1 != 6) {
            if (arg0->unk104 == 2) {
                func_802E66DC();
            }
            func_802E65AC(&arg0->unk10, &D_80362690->unk0[0].unk6, &sp7C, &sp78, &buttons);
        }
    }
}

void bird_802CD0F8(Unk80367704* arg0) {
    f32 x;
    f32 y;
    f32 z;
    Vec3F sp60;
    Vec3F sp54;
    Mtx4F* temp_a0;
    Vec3F* var_a1;
    f32 sp48;
    Mtx4F* sp2C;
    f32 sp40;
    s32 sp3C;
    s32 sp38;
    u8 sp37;
    u8 temp_v0;
    u8 temp6;

    if (arg0->unk2F0 == 0) {
        arg0->unk2F0 = 1;
        sp60.x = arg0->unk10.m[3][0];
        sp54.x = arg0->unk400;
        sp60.y = arg0->unk10.m[3][1];
        sp54.y = arg0->unk404;
        sp60.z = arg0->unk10.m[3][2];
        sp54.z = arg0->unk408;
        sp38 = arg0->unk40C;
        temp_v0 = db_getgnd(&sp54, &sp60, &sp38, &sp3C, &sp40, &sp48);
        sp37 = temp_v0;
        if (temp_v0 != 0) {
            var_a1 = func_802E02EC();
        } else {
            var_a1 = &sp60;
            sp60.z = sp40;
        }
        temp_a0 = &arg0->unk10;
        sp2C = temp_a0;
        func_802E05CC(temp_a0, var_a1, &sp48, 1);
        if (func_802E0C30(sp37, sp3C) != 0) {
            arg0->unk15C = 1;
        }
        uvDobjPosm(arg0->unk0, 0, sp2C);
        uvMat4Copy(&arg0->unkD4->unk80, sp2C);
        if (arg0->unk15C != 0) {
            snd_play_sfx(0x1A);
            uvEventPost(0x12, 0);
            x = arg0->unk10.m[3][0];
            y = arg0->unk10.m[3][1];
            z = arg0->unk10.m[3][2];
            func_802F8AB8(x, y, z, 1.0f, &arg0->unk218);
            arg0->unkD4->unk6 = arg0->unk2 = 0;
            uvDobjState(arg0->unk0, arg0->unk2);
            uvMat4Copy(&arg0->unkD4->unk80, sp2C);
        } else {
            arg0->unk2 = 2;
            uvDobjState(arg0->unk0, arg0->unk2);
        }
        arg0->unk290 = 1;
        bird_802CE0A4(arg0);
        func_803343D8(0);
    }
    func_802D5884(arg0->unkD4, 3);
    hudGetState()->renderFlags = 0;
    if (arg0->unk15C != 0) {
        arg0->unkD4->unk190 = 12.0f;
    } else {
        arg0->unkD4->unk190 = 6.0f;
    }
    func_802CEA60(arg0);
}

// called during birdman init to setup pilot specific parameters
void bird_802CD2E8(u8 pilot, Unk80367704* arg1) {
    switch (pilot) {
    case PILOT_LARK:
        arg1->unk294.x = 0;
        arg1->unk294.y = -0.1625f;
        arg1->unk294.z = 0.2869f;
        arg1->unk3F4 = 0x13B;
        arg1->unk3F7 = 0x16;
        arg1->unk3F6 = 1;
        arg1->unk3F8 = 2;
        arg1->unk3F9 = 5;
        arg1->unk2F8 = 0xF;
        arg1->unk2F9 = 8;
        arg1->unk2A0 = 0.6f;
        arg1->unk2A4 = 1.0f;
        arg1->unk2B0 = 0.8f;
        arg1->unk2B4 = 0.8f;
        arg1->unk2B8 = 0x44;
        arg1->unk2C0 = 0x45;
        arg1->unk2AC = 1.2f;
        arg1->unk2A8 = 1.2f;
        arg1->unk320 = 0.0f;
        arg1->unk324 = 0.021f;
        arg1->unk328 = 0.675f;
        arg1->unk32C = -4.281f;
        arg1->unk330 = -0.972f;
        arg1->unk334 = 0.596f;
        arg1->unk338 = 4.277f;
        arg1->unk33C = -0.972f;
        arg1->unk348 = 0.0f;
        arg1->unk344 = 0.0f;
        arg1->unk340 = 0.596f;
        arg1->unk34C = -0.745f;
        arg1->unk350 = 7;
        arg1->unk354 = 0.0f;
        arg1->unk358 = -1.426f;
        arg1->unk35C = -0.098f;
        arg1->unk360 = -0.018f;
        arg1->unk364 = 0.125f;
        arg1->unk368 = -1.368f;
        arg1->unk36C = -0.401f;
        arg1->unk370 = -0.084f;
        arg1->unk374 = 0.25f;
        arg1->unk378 = -1.019f;
        arg1->unk37C = -0.815f;
        arg1->unk380 = -0.234f;
        arg1->unk384 = 0.625f;
        arg1->unk388 = -1.271f;
        arg1->unk38C = -0.175f;
        arg1->unk390 = -0.158f;
        arg1->unk394 = 0.75f;
        arg1->unk398 = -1.133f;
        arg1->unk39C = 0.561f;
        arg1->unk3A0 = -0.274f;
        arg1->unk3A4 = 0.875f;
        arg1->unk3A8 = -1.12f;
        arg1->unk3AC = 0.6f;
        arg1->unk3B0 = -0.127f;
        arg1->unk3B4 = 1.0f;
        arg1->unk3B8 = -1.426f;
        arg1->unk3BC = -0.098f;
        arg1->unk3C0 = -0.018f;
        break;
    case PILOT_GOOSE:
        arg1->unk294.x = 0;
        arg1->unk294.y = -0.0994f;
        arg1->unk294.z = 0.2577f;
        arg1->unk3F4 = 0x13E;
        arg1->unk3F7 = 0x16;
        arg1->unk3F6 = 1;
        arg1->unk3F8 = 2;
        arg1->unk3F9 = 5;
        arg1->unk2F8 = 0xF;
        arg1->unk2F9 = 8;
        arg1->unk2A0 = 0.6f;
        arg1->unk2A4 = 1.0f;
        arg1->unk2AC = 1.0f;
        arg1->unk2A8 = 1.0f;
        arg1->unk2B0 = 1.0f;
        arg1->unk2B4 = 1.0f;
        arg1->unk2B8 = 0x46;
        arg1->unk2C0 = 0x47;
        arg1->unk320 = 0.0f;
        arg1->unk324 = 0.108f;
        arg1->unk328 = 0.653f;
        arg1->unk32C = -3.724f;
        arg1->unk330 = -0.808f;
        arg1->unk334 = 0.499f;
        arg1->unk338 = 3.714f;
        arg1->unk33C = -0.808f;
        arg1->unk340 = 0.499f;
        arg1->unk348 = 0.0f;
        arg1->unk344 = 0.0f;
        arg1->unk34C = -1.645f;
        arg1->unk350 = 7;
        arg1->unk354 = 0.0f;
        arg1->unk358 = -1.457f;
        arg1->unk35C = -0.05f;
        arg1->unk360 = 0.491f;
        arg1->unk364 = 0.125f;
        arg1->unk368 = -1.416f;
        arg1->unk36C = -0.426f;
        arg1->unk370 = 0.377f;
        arg1->unk374 = 0.25f;
        arg1->unk378 = -0.864f;
        arg1->unk37C = -1.022f;
        arg1->unk380 = 0.137f;
        arg1->unk384 = 0.625f;
        arg1->unk388 = -1.439f;
        arg1->unk38C = -0.011f;
        arg1->unk390 = 0.486f;
        arg1->unk394 = 0.75f;
        arg1->unk398 = -1.249f;
        arg1->unk39C = 0.762f;
        arg1->unk3A0 = 0.202f;
        arg1->unk3A4 = 0.875f;
        arg1->unk3A8 = -1.152f;
        arg1->unk3AC = 0.767f;
        arg1->unk3B0 = 0.312f;
        arg1->unk3B4 = 1.0f;
        arg1->unk3B8 = -1.457f;
        arg1->unk3BC = -0.05f;
        arg1->unk3C0 = 0.491f;
        break;
    case PILOT_HAWK:
        arg1->unk294.x = 0;
        arg1->unk294.y = -0.07084f;
        arg1->unk294.z = 0.57865f;
        arg1->unk3F4 = 0x13F;
        arg1->unk3F7 = 0x16;
        arg1->unk3F6 = 1;
        arg1->unk3F8 = 2;
        arg1->unk3F9 = 5;
        arg1->unk2F8 = 0xF;
        arg1->unk2F9 = 8;
        arg1->unk2A0 = 0.6f;
        arg1->unk2A4 = 1.0f;
        arg1->unk2B0 = 1.2f;
        arg1->unk2B4 = 1.2f;
        arg1->unk2B8 = 0x48;
        arg1->unk2C0 = 0x49;
        arg1->unk2AC = 0.8f;
        arg1->unk2A8 = 0.8f;
        arg1->unk320 = 0.0f;
        arg1->unk324 = 0.108f;
        arg1->unk328 = 0.627f;
        arg1->unk32C = -3.643f;
        arg1->unk330 = -0.796f;
        arg1->unk334 = 0.476f;
        arg1->unk338 = 3.643f;
        arg1->unk33C = -0.796f;
        arg1->unk340 = 0.476f;
        arg1->unk348 = 0.0f;
        arg1->unk344 = 0.0f;
        arg1->unk34C = -1.228f;
        arg1->unk350 = 7;
        arg1->unk354 = 0.0f;
        arg1->unk358 = -1.826f;
        arg1->unk35C = -0.06f;
        arg1->unk360 = 0.217f;
        arg1->unk364 = 0.125f;
        arg1->unk368 = -1.689f;
        arg1->unk36C = -0.606f;
        arg1->unk370 = 0.158f;
        arg1->unk374 = 0.25f;
        arg1->unk378 = -1.074f;
        arg1->unk37C = -1.247f;
        arg1->unk380 = -0.01f;
        arg1->unk384 = 0.625f;
        arg1->unk388 = -1.804f;
        arg1->unk38C = -0.068f;
        arg1->unk390 = 0.407f;
        arg1->unk394 = 0.75f;
        arg1->unk398 = -1.519f;
        arg1->unk39C = 0.881f;
        arg1->unk3A0 = 0.208f;
        arg1->unk3A4 = 0.875f;
        arg1->unk3A8 = -1.415f;
        arg1->unk3AC = 0.89f;
        arg1->unk3B0 = 0.392f;
        arg1->unk3B8 = -1.826f;
        arg1->unk3BC = -0.06f;
        arg1->unk3B4 = 1.0f;
        arg1->unk3C0 = 0.217f;
        break;
    case PILOT_KIWI:
        arg1->unk294.x = 0;
        arg1->unk294.y = 0.0015f;
        arg1->unk294.z = 0.1942f;
        arg1->unk3F4 = 0x140;
        arg1->unk3F7 = 0x16;
        arg1->unk3F6 = 1;
        arg1->unk3F8 = 2;
        arg1->unk3F9 = 5;
        arg1->unk2F8 = 0xF;
        arg1->unk2F9 = 8;
        arg1->unk2A0 = 0.6f;
        arg1->unk2A4 = 1.0f;
        arg1->unk2B0 = 0.8f;
        arg1->unk2B4 = 0.8f;
        arg1->unk2B8 = 0x4A;
        arg1->unk2C0 = 0x45;
        arg1->unk2AC = 1.2f;
        arg1->unk2A8 = 1.2f;
        arg1->unk320 = 0.0f;
        arg1->unk324 = 0.021f;
        arg1->unk328 = 0.672f;
        arg1->unk32C = -4.34f;
        arg1->unk330 = -1.029f;
        arg1->unk334 = 0.57f;
        arg1->unk338 = 4.34f;
        arg1->unk33C = -1.029f;
        arg1->unk348 = 0.0f;
        arg1->unk344 = 0.0f;
        arg1->unk340 = 0.57f;
        arg1->unk34C = -0.861f;
        arg1->unk350 = 7;
        arg1->unk354 = 0.0f;
        arg1->unk358 = -1.426f;
        arg1->unk35C = -0.098f;
        arg1->unk360 = -0.018f;
        arg1->unk364 = 0.125f;
        arg1->unk368 = -1.368f;
        arg1->unk36C = -0.401f;
        arg1->unk370 = -0.084f;
        arg1->unk374 = 0.25f;
        arg1->unk378 = -1.019f;
        arg1->unk37C = -0.815f;
        arg1->unk380 = -0.234f;
        arg1->unk384 = 0.625f;
        arg1->unk388 = -1.271f;
        arg1->unk38C = -0.175f;
        arg1->unk390 = -0.158f;
        arg1->unk394 = 0.75f;
        arg1->unk398 = -1.133f;
        arg1->unk39C = 0.561f;
        arg1->unk3A0 = -0.274f;
        arg1->unk3A4 = 0.875f;
        arg1->unk3A8 = -1.12f;
        arg1->unk3AC = 0.6f;
        arg1->unk3B0 = -0.127f;
        arg1->unk3B4 = 1.0f;
        arg1->unk3B8 = -1.426f;
        arg1->unk3BC = -0.098f;
        arg1->unk3C0 = -0.018f;
        break;
    case PILOT_IBIS:
        arg1->unk294.x = 0;
        arg1->unk294.y = 0.0024f;
        arg1->unk294.z = 0.3577f;
        arg1->unk3F4 = 0x141;
        arg1->unk3F7 = 0x16;
        arg1->unk3F6 = 1;
        arg1->unk3F8 = 2;
        arg1->unk3F9 = 5;
        arg1->unk2F8 = 0xF;
        arg1->unk2F9 = 8;
        arg1->unk2A0 = 0.6f;
        arg1->unk2A4 = 1.0f;
        arg1->unk2AC = 1.0f;
        arg1->unk2A8 = 1.0f;
        arg1->unk2B0 = 1.0f;
        arg1->unk2B4 = 1.0f;
        arg1->unk2B8 = 0x4B;
        arg1->unk2C0 = 0x47;
        arg1->unk320 = 0.0f;
        arg1->unk324 = 0.108f;
        arg1->unk328 = 0.731f;
        arg1->unk32C = -4.225f;
        arg1->unk330 = -0.89f;
        arg1->unk334 = 0.715f;
        arg1->unk338 = 4.226f;
        arg1->unk33C = -0.89f;
        arg1->unk340 = 0.666f;
        arg1->unk348 = 0.0f;
        arg1->unk344 = 0.0f;
        arg1->unk34C = -1.427f;
        arg1->unk350 = 7;
        arg1->unk354 = 0.0f;
        arg1->unk358 = -1.457f;
        arg1->unk35C = -0.05f;
        arg1->unk360 = 0.491f;
        arg1->unk364 = 0.125f;
        arg1->unk368 = -1.416f;
        arg1->unk36C = -0.426f;
        arg1->unk370 = 0.377f;
        arg1->unk374 = 0.25f;
        arg1->unk378 = -0.864f;
        arg1->unk37C = -1.022f;
        arg1->unk380 = 0.137f;
        arg1->unk384 = 0.625f;
        arg1->unk388 = -1.439f;
        arg1->unk38C = -0.011f;
        arg1->unk390 = 0.486f;
        arg1->unk394 = 0.75f;
        arg1->unk398 = -1.249f;
        arg1->unk39C = 0.762f;
        arg1->unk3A0 = 0.202f;
        arg1->unk3A4 = 0.875f;
        arg1->unk3A8 = -1.152f;
        arg1->unk3AC = 0.767f;
        arg1->unk3B0 = 0.312f;
        arg1->unk3B4 = 1.0f;
        arg1->unk3B8 = -1.457f;
        arg1->unk3BC = -0.05f;
        arg1->unk3C0 = 0.491f;
        break;
    case PILOT_ROBIN:
        arg1->unk294.x = 0;
        arg1->unk294.y = -0.0991f;
        arg1->unk294.z = 0.4056f;
        arg1->unk3F4 = 0x142;
        arg1->unk3F7 = 0x16;
        arg1->unk3F6 = 1;
        arg1->unk3F8 = 2;
        arg1->unk3F9 = 5;
        arg1->unk2F8 = 0xF;
        arg1->unk2F9 = 8;
        arg1->unk2A0 = 0.6f;
        arg1->unk2A4 = 1.0f;
        arg1->unk2AC = 0.8f;
        arg1->unk2A8 = 0.8f;
        arg1->unk2B0 = 1.2f;
        arg1->unk2B8 = 0x4C;
        arg1->unk2C0 = 0x49;
        arg1->unk2B4 = 1.2f;
        arg1->unk320 = 0.0f;
        arg1->unk324 = 0.108f;
        arg1->unk328 = 0.782f;
        arg1->unk32C = -4.206f;
        arg1->unk330 = -0.202f;
        arg1->unk334 = 0.574f;
        arg1->unk338 = 4.207f;
        arg1->unk33C = -0.202f;
        arg1->unk348 = 0.0f;
        arg1->unk344 = 0.0f;
        arg1->unk340 = 0.574f;
        arg1->unk34C = -1.138f;
        arg1->unk350 = 7;
        arg1->unk354 = 0.0f;
        arg1->unk358 = -1.826f;
        arg1->unk35C = -0.06f;
        arg1->unk360 = 0.217f;
        arg1->unk364 = 0.125f;
        arg1->unk368 = -1.689f;
        arg1->unk36C = -0.606f;
        arg1->unk370 = 0.158f;
        arg1->unk374 = 0.25f;
        arg1->unk378 = -1.074f;
        arg1->unk37C = -1.247f;
        arg1->unk380 = -0.01f;
        arg1->unk384 = 0.625f;
        arg1->unk388 = -1.804f;
        arg1->unk38C = -0.068f;
        arg1->unk390 = 0.407f;
        arg1->unk394 = 0.75f;
        arg1->unk398 = -1.519f;
        arg1->unk39C = 0.881f;
        arg1->unk3A0 = 0.208f;
        arg1->unk3A4 = 0.875f;
        arg1->unk3A8 = -1.415f;
        arg1->unk3AC = 0.89f;
        arg1->unk3B0 = 0.392f;
        arg1->unk3B4 = 1.0f;
        arg1->unk3B8 = -1.826f;
        arg1->unk3BC = -0.06f;
        arg1->unk3C0 = 0.217f;
        break;
    default:
        break;
    }
}

// called every frame during birdman
void bird_802CE0A4(Unk80367704* arg0) {
    if (arg0->unk290 != 0) {
        arg0->unk2 &= 0xFFFB;
        uvDobjProps(arg0->unk0, 4, arg0->unk3F7, 0);
        if (arg0->unk3F4 == 0x140) {
            uvDobjProps(arg0->unk0, 4, 0x17, 0);
            uvDobjProps(arg0->unk0, 4, 0x18, 0);
        }
    } else {
        arg0->unk2 |= 4;
        uvDobjProps(arg0->unk0, 5, arg0->unk3F7, 0);
        if (arg0->unk3F4 == 0x140) {
            uvDobjProps(arg0->unk0, 5, 0x17, 0);
            uvDobjProps(arg0->unk0, 5, 0x18, 0);
        }
    }
    uvDobjState(arg0->unk0, arg0->unk2);
}
