#include "common.h"
#include <uv_dobj.h>
#include <uv_math.h>
#include <uv_model.h>
#include <uv_texture.h>
#include <uv_util.h>
#include "bonus.h"
#include "code_72B70.h"
#include "code_9A960.h"
#include "level.h"
#include "snd.h"
#include "task.h"

typedef struct {
    u16 objId;
    u8 pad2[2];
    Mtx4F unk4;
    f32 unk44;
    u8 unk48;
    u8 loadVeh;
    u8 pad4A[2];
    s32 unk4C;
} BonusStar;

LevelBNUS* gRefBNUS;
u8 gBonusStarCount;
BonusStar gBonusStars[2];

void bonusInit(void) {
    s32 i;
    for (i = 0; i < ARRAY_COUNT(gBonusStars); i++) {
        gBonusStars[i].objId = 0xFFFF;
    }
}

void bonusUpdateState(void) {
    BonusStar* star;
    s32 i;

    for (i = 0; i < gBonusStarCount; i++) {
        star = &gBonusStars[i];
        if (D_80362690->unkC[D_80362690->unk9C].unk8 == gRefBNUS[i].unk18) {
            star->unk4C = 1;
            if (star->objId != 0xFFFF) {
                uvDobjSetState(star->objId, 0x2);
            }
        } else {
            star->unk4C = 0;
            if (star->objId != 0xFFFF) {
                uvDobjClearState(star->objId, 0x2);
            }
        }
    }
}

void bonusLoad(void) {
    BonusStar* var_s1;
    s32 i;
    LevelBNUS* temp_s0;

    if (D_80362690->unkA0 != 0) {
        gBonusStarCount = levelGetBNUS(&gRefBNUS);
        if (gBonusStarCount > ARRAY_COUNT(gBonusStars)) {
            _uvDebugPrintf("bonus : too many bonuses defined in level [%d]\n", gBonusStarCount);
            gBonusStarCount = 0;
            return;
        }
        if (gBonusStarCount != 0) {
            uvLevelAppend(0xF);
            bonusUpdateState();
            for (i = 0; i < gBonusStarCount; i++) {
                temp_s0 = &gRefBNUS[i];
                var_s1 = &gBonusStars[i];
                var_s1->objId = uvDobjAllocIdx();
                var_s1->unk48 = 0;
                var_s1->loadVeh = VEHICLE_COUNT;
                uvDobjModel(var_s1->objId, 0xF2);
                uvModelGetProps(0xF2, 1, &var_s1->unk44, 0);
                uvDobjState(var_s1->objId, (var_s1->unk4C != 0) ? 2 : 0);
                func_80313640(temp_s0->pos.x, temp_s0->pos.y, temp_s0->pos.z, temp_s0->unkC * 0.0174533f, temp_s0->unk10 * 0.0174533f,
                              temp_s0->unk14 * 0.0174533f, // DEG_TO_RAD(1)
                              &var_s1->unk4);
                uvDobjPosm(var_s1->objId, 0, &var_s1->unk4);
            }
        }
    }
}

void bonusFrameUpdate(Mtx4F* arg0) {
    s32 i;
    BonusStar* star;
    f32 px, py, pz;
    f32 dx, dy, dz;

    // rotate star about 'z' axis
    for (i = 0; i < gBonusStarCount; i++) {
        star = &gBonusStars[i];
        if (star->unk4C == 0) {
            continue;
        }
        if (star->objId != 0xFFFF) {
            uvMat4RotateAxis(&star->unk4, 6.2831855f * D_8034F854, 'z');
            uvDobjPosm(star->objId, 0, &star->unk4);
        }
    }

    // if not already in birdman
    if ((D_80362690->unk0 != VEHICLE_BIRDMAN) && (D_80362690->unkC[D_80362690->unk9C].unkA == 1)) {
        px = arg0->m[3][0];
        py = arg0->m[3][1];
        pz = arg0->m[3][2];
        for (i = 0; i < gBonusStarCount; i++) {
            star = &gBonusStars[i];
            if (star->unk4C == 0) {
                continue;
            }
            if (star->objId != 0xFFFF) {
                // if in proximity to star
                dx = star->unk4.m[3][0] - px;
                dy = star->unk4.m[3][1] - py;
                dz = star->unk4.m[3][2] - pz;
                if (uvLength3D(dx, dy, dz) < star->unk44) {
                    // play *gong* sound
                    snd_play_sfx(0x11);
                    // change to birdman
                    star->loadVeh = VEHICLE_BIRDMAN;
                    star->unk48 = 1;
                    func_802EE14C(star->loadVeh);
                }
            }
        }
    }
}

void bonusDeinit(void) {
    s32 i;
    for (i = 0; i < gBonusStarCount; i++) {
        if (gBonusStars[i].objId != 0xFFFF) {
            uvDobjModel(gBonusStars[i].objId, MODEL_WORLD);
            gBonusStars[i].objId = 0xFFFF;
        }
    }
}
