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
    u8 pad9[0xC - 0x9];
    Mtx4F unkC;
    Mtx4F unk4C[8];
    f32 unk24C;
    f32 unk250;
    f32 unk254;
} Toy; // size = 0x258

extern u8 gToyCount;
extern Toy gToys[20];

void toyInit(void) {
    s32 i;

    gToyCount = 0;
    for (i = 0; i < ARRAY_COUNT(gToys); i++) {
        gToys[i].unk24C = 0.0f;
        gToys[i].unk250 = 0.0f;
        gToys[i].unk254 = 0.0f;
    }
}

s32 toy_80347C2C(Vec3F arg0, Toy* arg3) {
    f32 dx;
    f32 dy;
    s32 terraId;
    s32 toyModel;
    u8 toyType;

    terraId = uvSobjGetPt(D_80362690->terraId, arg0.x, arg0.y, arg0.z);
    if (terraId == -1) {
        return -1;
    }

    toyModel = uvSobj_8022D1E4(terraId);
    switch (toyModel) {
    case 0xC:
        toyType = 1;
        break;
    case 0x9:
        toyType = 0;
        break;
    case 0xD:
        toyType = 2;
        break;
    case 0x54:
        toyType = 3;
        break;
    case 0x55:
    case 0x99:
        toyType = 4;
        break;
    default:
        _uvDebugPrintf("Found unknown toy model %d\n", toyModel);
        return -1;
    }

    arg3->terraId = terraId;
    arg3->toyType = toyType;
    switch (toyType) {
    case 4:
        break;
    case 2:
        uvSobj_8022D168(terraId, 0, &arg3->unkC);
        break;
    case 0:
        uvSobj_8022D168(terraId, 1, &arg3->unkC);
        break;
    case 1:
        uvSobj_8022D168(terraId, 1, &arg3->unkC);
        uvSobj_8022D168(terraId, 2, &arg3->unk4C[0]);
        uvSobj_8022D168(terraId, 3, &arg3->unk4C[1]);
        uvSobj_8022D168(terraId, 4, &arg3->unk4C[2]);
        uvSobj_8022D168(terraId, 5, &arg3->unk4C[3]);
        uvSobj_8022D168(terraId, 6, &arg3->unk4C[4]);
        uvSobj_8022D168(terraId, 7, &arg3->unk4C[5]);
        uvSobj_8022D168(terraId, 8, &arg3->unk4C[6]);
        uvSobj_8022D168(terraId, 9, &arg3->unk4C[7]);
        break;
    case 3:
        uvSobj_8022D168(terraId, 1, &arg3->unkC);
        uvSobj_8022D168(terraId, 2, &arg3->unk4C[0]);
        uvSobj_8022D168(terraId, 3, &arg3->unk4C[1]);
        dx = arg3->unk4C[0].m[3][0] - arg3->unkC.m[3][0];
        dy = arg3->unk4C[0].m[3][1] - arg3->unkC.m[3][1];
        arg3->unk24C = uvSqrtF(uvAbs(SQ(dx) - SQ(dy))); //! @bug integer ABS
        arg3->unk250 = arg3->unkC.m[3][2] - arg3->unk4C[0].m[3][2];
        arg3->unk254 = demoRandF() * 6.2831855f;
        break;
    }
    return 0;
}

void toyAnimate(Toy* toy) {
    s32 i;
    f32 temp_fv0;
    Mtx4F sp40;
    f32 temp_fs0;
    Mtx4F* mtx0;

    switch (toy->toyType) {
    case 2:
        uvMat4RotateAxis(&toy->unkC, 0.6981316f * D_8034F854, 'y');
        uvSobjPosm(toy->terraId, 0, &toy->unkC);
        break;
    case 0:
        uvMat4RotateAxis(&toy->unkC, 0.1745329f * D_8034F854, 'z');
        uvSobjPosm(toy->terraId, 1, &toy->unkC);
        break;
    case 1:
        temp_fv0 = 0.29670593f * D_8034F854;
        uvMat4RotateAxis(&toy->unkC, temp_fv0, 'y');
        uvSobjPosm(toy->terraId, 1, &toy->unkC);
        for (i = 0; i < ARRAY_COUNT(toy->unk4C); i++) {
            uvMat4RotateAxis(&toy->unk4C[i], -temp_fv0, 'y');
        }
        uvSobjPosm(toy->terraId, 2, &toy->unk4C[0]);
        uvSobjPosm(toy->terraId, 3, &toy->unk4C[1]);
        uvSobjPosm(toy->terraId, 4, &toy->unk4C[2]);
        uvSobjPosm(toy->terraId, 5, &toy->unk4C[3]);
        uvSobjPosm(toy->terraId, 6, &toy->unk4C[4]);
        uvSobjPosm(toy->terraId, 7, &toy->unk4C[5]);
        uvSobjPosm(toy->terraId, 8, &toy->unk4C[6]);
        uvSobjPosm(toy->terraId, 9, &toy->unk4C[7]);
        break;
    case 3:
        toy->unk254 += 1.1344639f * D_8034F854;
        if (toy->unk254 > 6.2831855f) {
            toy->unk254 -= 6.2831855f;
        }
        temp_fs0 = toy->unk254;
        uvMat4Copy(&sp40, &toy->unkC);
        uvMat4RotateAxis(&sp40, temp_fs0 + 4.712389f, 'x');
        uvSobjPosm(toy->terraId, 1, &sp40);
        temp_fs0 = uvAtan2F(uvSinF(temp_fs0) * 1.16, toy->unk24C);
        uvMat4Copy(&sp40, &toy->unk4C[0]);
        uvMat4RotateAxis(&sp40, temp_fs0, 'x');
        uvSobjPosm(toy->terraId, 2, &sp40);
        uvMat4Copy(&sp40, &toy->unk4C[1]);
        uvMat4RotateAxis(&sp40, -temp_fs0, 'x');
        uvSobjPosm(toy->terraId, 3, &sp40);
        break;
    default:
        _uvDebugPrintf("Update got an unknown toy type\n");
        break;
    case 4:
        break;
    }
}

s32 toy_8034819C(s32 arg0, s32 arg1, s32 toy) {
    ProxAnim* tmp;

    switch (arg1) {
    case 0:
        tmp = proxAnimGetHandle(arg0);
        if (toy_80347C2C(tmp->pos, (Toy*)toy) == -1) {
            return -1;
        }
        break;
    case 1:
    default:
        break;
    }
    return 0;
}

s32 toy_80348214(s32 arg0, f32 arg1, s32 arg2) {
    Toy* toy;
    s32 res;

    toy = (Toy*)arg2;
    res = 0;
    if ((proxAnimGetRange(arg0) > 100.0f) && (toy->toyType != 4)) {
        res = 2;
    } else {
        toyAnimate(toy);
    }
    return res;
}

void toyLoad(LevelTOYS* lvlToy) {
    Toy* toy;

    if (gToyCount >= ARRAY_COUNT(gToys)) {
        _uvDebugPrintf("Too many toys on level, only %d will be created\n", ARRAY_COUNT(gToys));
        return;
    }

    toy = &gToys[gToyCount];
    gToys[gToyCount].unk0 = proxAnimAddCallback(toy_80348214, toy_8034819C, lvlToy->pos, 100.0f, 0.0f, (s32)toy);
    if (gToys[gToyCount].unk250 == 1.0f) {
        uvSobjModel(toy->terraId, 0x55);
    }
    gToyCount++;
}

void toy_803483AC(void) {
    s32 i;

    for (i = 0; i < gToyCount; i++) {
        proxAnimDeleteCallback(gToys[i].unk0);
    }
    gToyCount = 0;
}

void toy_80348418(s32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4) {
    Toy* toy;
    s32 fxId;
    s32 i;

    for (i = 0; i < gToyCount; i++) {
        if (arg0 == gToys[i].terraId) {
            break;
        }
    }
    if (i != gToyCount) {
        toy = &gToys[i];
        if (toy->toyType == 4) {
            fxId = func_8021EFF0(8);
            if (fxId != 0xFF) {
                uvModelGet(fxId, 8);
                uvFxProps(fxId, FX_3(5.0f, 5.0f, 5.0f), FX_1(3.0f), FX_4(2.0f, 2.0f, 2.0f), FX_10(arg1, arg2, arg3), FX_END);
            }
            toy->unk24C += 1.0f;
            if ((s32)toy->unk24C >= arg4) {
                if (toy->unk250 == 0.0f) {
                    uvSobjModel(toy->terraId, 0x55);
                    toy->unk250 = 1.0f;
                } else {
                    uvSobjModel(toy->terraId, 0x99);
                    toy->unk250 = 0.0f;
                }
                toy->unk24C = 0.0f;
            }
        }
    }
}
