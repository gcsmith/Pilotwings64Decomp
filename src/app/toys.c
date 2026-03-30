#include "common.h"
#include <uv_fx.h>
#include <uv_math.h>
#include <uv_model.h>
#include <uv_sobj.h>
#include "kernel/code_8170.h"
#include "code_9A960.h"
#include "demo.h"
#include "proxanim.h"
#include "toys.h"

typedef struct {
    s32 unk0;
    s32 terraId;
    u8 toyType;
    u8 pad9[3];
    Mtx4F modelPose;
    Mtx4F partPose[8];
    f32 unk24C;
    f32 unk250;
    f32 unk254;
} Toy; // size = 0x258

typedef enum ToyType { ToyMerryGoRound = 0, ToyFerrisWheel = 1, ToyWaterWheel = 2, ToyPumpJack = 3, ToyMountRushmore = 4 } ToyType;

static u8 sToyCount;
static Toy sToys[20];

void toyInit(void) {
    s32 i;

    sToyCount = 0;
    for (i = 0; i < ARRAY_COUNT(sToys); i++) {
        sToys[i].unk24C = 0.0f;
        sToys[i].unk250 = 0.0f;
        sToys[i].unk254 = 0.0f;
    }
}

STATIC_FUNC s32 toy_80347C2C(Vec3F pos, Toy* toy) {
    f32 dx;
    f32 dy;
    s32 terraId;
    s32 toyModel;
    u8 toyType;

    terraId = uvSobjGetPt(D_80362690->terraId, pos.x, pos.y, pos.z);
    if (terraId == -1) {
        return -1;
    }

    toyModel = uvSobj_8022D1E4(terraId);
    switch (toyModel) {
    case MODEL_THEMEPARK_FERRIS_WHEEL:
        toyType = ToyFerrisWheel;
        break;
    case MODEL_THEMEPARK_MERRY_GO_ROUND:
        toyType = ToyMerryGoRound;
        break;
    case MODEL_VILLAGE_WATER_WHEEL:
        toyType = ToyWaterWheel;
        break;
    case MODEL_PUMP_JACK:
        toyType = ToyPumpJack;
        break;
    case MODEL_STONE_WARIO_HEAD:
    case MODEL_STONE_MARIO_HEAD:
        toyType = ToyMountRushmore;
        break;
    default:
        _uvDebugPrintf("Found unknown toy model %d\n", toyModel);
        return -1;
    }

    toy->terraId = terraId;
    toy->toyType = toyType;
    switch (toyType) {
    case ToyMountRushmore:
        break;
    case ToyWaterWheel:
        uvSobj_8022D168(terraId, 0, &toy->modelPose);
        break;
    case ToyMerryGoRound:
        uvSobj_8022D168(terraId, 1, &toy->modelPose);
        break;
    case ToyFerrisWheel:
        uvSobj_8022D168(terraId, 1, &toy->modelPose);
        uvSobj_8022D168(terraId, 2, &toy->partPose[0]);
        uvSobj_8022D168(terraId, 3, &toy->partPose[1]);
        uvSobj_8022D168(terraId, 4, &toy->partPose[2]);
        uvSobj_8022D168(terraId, 5, &toy->partPose[3]);
        uvSobj_8022D168(terraId, 6, &toy->partPose[4]);
        uvSobj_8022D168(terraId, 7, &toy->partPose[5]);
        uvSobj_8022D168(terraId, 8, &toy->partPose[6]);
        uvSobj_8022D168(terraId, 9, &toy->partPose[7]);
        break;
    case ToyPumpJack:
        uvSobj_8022D168(terraId, 1, &toy->modelPose);
        uvSobj_8022D168(terraId, 2, &toy->partPose[0]);
        uvSobj_8022D168(terraId, 3, &toy->partPose[1]);
        dx = toy->partPose[0].m[3][0] - toy->modelPose.m[3][0];
        dy = toy->partPose[0].m[3][1] - toy->modelPose.m[3][1];
        toy->unk24C = uvSqrtF(uvAbs(SQ(dx) - SQ(dy))); //! @bug integer ABS
        toy->unk250 = toy->modelPose.m[3][2] - toy->partPose[0].m[3][2];
        toy->unk254 = demoRandF() * 6.2831855f;
        break;
    }
    return 0;
}

STATIC_FUNC void toyAnimate(Toy* toy) {
    s32 i;
    f32 rot;
    Mtx4F sp40;
    f32 temp_fs0;
    Mtx4F* mtx0;

    switch (toy->toyType) {
    case ToyWaterWheel:
        uvMat4RotateAxis(&toy->modelPose, 0.6981316f * D_8034F854, 'y');
        uvSobjPosm(toy->terraId, 0, &toy->modelPose);
        break;
    case ToyMerryGoRound:
        uvMat4RotateAxis(&toy->modelPose, 0.1745329f * D_8034F854, 'z');
        uvSobjPosm(toy->terraId, 1, &toy->modelPose);
        break;
    case ToyFerrisWheel:
        rot = 0.29670593f * D_8034F854;
        uvMat4RotateAxis(&toy->modelPose, rot, 'y');
        uvSobjPosm(toy->terraId, 1, &toy->modelPose);
        for (i = 0; i < ARRAY_COUNT(toy->partPose); i++) {
            uvMat4RotateAxis(&toy->partPose[i], -rot, 'y');
        }
        uvSobjPosm(toy->terraId, 2, &toy->partPose[0]);
        uvSobjPosm(toy->terraId, 3, &toy->partPose[1]);
        uvSobjPosm(toy->terraId, 4, &toy->partPose[2]);
        uvSobjPosm(toy->terraId, 5, &toy->partPose[3]);
        uvSobjPosm(toy->terraId, 6, &toy->partPose[4]);
        uvSobjPosm(toy->terraId, 7, &toy->partPose[5]);
        uvSobjPosm(toy->terraId, 8, &toy->partPose[6]);
        uvSobjPosm(toy->terraId, 9, &toy->partPose[7]);
        break;
    case ToyPumpJack:
        toy->unk254 += 1.1344639f * D_8034F854;
        if (toy->unk254 > 6.2831855f) {
            toy->unk254 -= 6.2831855f;
        }
        temp_fs0 = toy->unk254;
        uvMat4Copy(&sp40, &toy->modelPose);
        uvMat4RotateAxis(&sp40, temp_fs0 + 4.712389f, 'x'); // DEG_TO_RAD(270)
        uvSobjPosm(toy->terraId, 1, &sp40);
        temp_fs0 = uvAtan2F(uvSinF(temp_fs0) * 1.16, toy->unk24C);
        uvMat4Copy(&sp40, &toy->partPose[0]);
        uvMat4RotateAxis(&sp40, temp_fs0, 'x');
        uvSobjPosm(toy->terraId, 2, &sp40);
        uvMat4Copy(&sp40, &toy->partPose[1]);
        uvMat4RotateAxis(&sp40, -temp_fs0, 'x');
        uvSobjPosm(toy->terraId, 3, &sp40);
        break;
    default:
        _uvDebugPrintf("Update got an unknown toy type\n");
        break;
    case ToyMountRushmore:
        break;
    }
}

STATIC_FUNC s32 toyProxEventCb(s32 proxId, s32 eventType, s32 arg) {
    ProxAnim* prox;

    switch (eventType) {
    case 0:
        prox = proxAnimGetHandle(proxId);
        if (toy_80347C2C(prox->pos, (Toy*)arg) == -1) {
            return -1;
        }
        break;
    case 1:
    default:
        break;
    }
    return 0;
}

STATIC_FUNC s32 toyProxAnimCb(s32 proxId, f32 timeout, s32 arg) {
    Toy* toy;
    s32 res;

    toy = (Toy*)arg;
    res = 0;
    if ((proxAnimGetRange(proxId) > 100.0f) && (toy->toyType != ToyMountRushmore)) {
        res = 2;
    } else {
        toyAnimate(toy);
    }
    return res;
}

void toyLoad(LevelTOYS* lvlToy) {
    Toy* toy;

    if (sToyCount >= ARRAY_COUNT(sToys)) {
        _uvDebugPrintf("Too many toys on level, only %d will be created\n", ARRAY_COUNT(sToys));
        return;
    }

    toy = &sToys[sToyCount];
    sToys[sToyCount].unk0 = proxAnimAddCallback(toyProxAnimCb, toyProxEventCb, lvlToy->pos, 100.0f, 0.0f, (s32)toy);
    if (sToys[sToyCount].unk250 == 1.0f) {
        uvSobjModel(toy->terraId, MODEL_STONE_WARIO_HEAD);
    }
    sToyCount++;
}

void toy_803483AC(void) {
    s32 i;

    for (i = 0; i < sToyCount; i++) {
        proxAnimDeleteCallback(sToys[i].unk0);
    }
    sToyCount = 0;
}

void toy_80348418(s32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4) {
    Toy* toy;
    s32 fxId;
    s32 i;

    for (i = 0; i < sToyCount; i++) {
        if (arg0 == sToys[i].terraId) {
            break;
        }
    }
    if (i == sToyCount) {
        return;
    }

    toy = &sToys[i];
    if (toy->toyType == ToyMountRushmore) {
        fxId = func_8021EFF0(8);
        if (fxId != 0xFF) {
            uvModelGet(fxId, 8);
            // clang-format off
            uvFxProps(
                fxId,
                FX_PROP_3(5.0f, 5.0f, 5.0f),
                FX_PROP_1(3.0f),
                FX_PROP_4(2.0f, 2.0f, 2.0f),
                FX_PROP_10(arg1, arg2, arg3),
                FX_PROP_END
            );
            // clang-format on
        }
        toy->unk24C += 1.0f;
        if ((s32)toy->unk24C >= arg4) {
            if (toy->unk250 == 0.0f) {
                uvSobjModel(toy->terraId, MODEL_STONE_WARIO_HEAD);
                toy->unk250 = 1.0f;
            } else {
                uvSobjModel(toy->terraId, MODEL_STONE_MARIO_HEAD);
                toy->unk250 = 0.0f;
            }
            toy->unk24C = 0.0f;
        }
    }
}
