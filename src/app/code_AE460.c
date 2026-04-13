#include "common.h"
#include "rocket_belt.h"
#include <uv_event.h>
#include <uv_fx.h>
#include <uv_janim.h>
#include <uv_math.h>
#include <uv_model.h>
#include "app/demo.h"
#include "app/fdr.h"
#include "app/shadow.h"
#include "app/snd.h"
#include "app/code_7FE00.h"

Unk80371120 D_80371120;
Unk80371120 D_803712D0;
Unk80371120 D_80371480;

void func_803277E0(RocketBeltData*);
void func_803279F0(RocketBeltData*);
void func_80327F30(RocketBeltData*, u8 gameState);

void func_80326F30(RocketBeltData* rbData) {
    rbData->unk338 = func_8021EFF0(2);
    uvModelGet(rbData->unk338, MODEL_BLUE_CUBOID);
    rbData->unk339 = func_8021EFF0(2);
    uvModelGet(rbData->unk339, MODEL_BLUE_CUBOID);
    uvFxProps(rbData->unk338, 3, 3.0f, 3.0f, 3.0f, 4, 1.0f, 1.0f, 1.0f, 1, 1e+20, 0);
    uvFxProps(rbData->unk339, 3, 3.0f, 3.0f, 3.0f, 4, 1.0f, 1.0f, 1.0f, 1, 1e+20, 0);
    rbData->unk33A = 0;
}

void func_80327040(RocketBeltData* rbData, u8 gameState) {
    Mtx4F sp40;
    f32 var_ft4;
    f32 var_fv1;

    func_803279F0(rbData);
    if ((rbData->unkF8 > 0.0f) && (rbData->unk90 != 4)) {
        func_80327F30(rbData, gameState);
    } else {
        func_803277E0(rbData);
    }
    rbData->unk35C = func_80313AF4((rbData->unk68 * -1.2f) + rbData->unk88, rbData->unk35C, 5.0f);
    var_ft4 = rbData->unk1DC.z / 20.0f;
    if (var_ft4 < -1.0f) {
        var_ft4 = -1.0f;
    } else if (var_ft4 > 1.0f) {
        var_ft4 = 1.0f;
    }
    rbData->unk360 = func_80313AF4((0.7f * var_ft4) + rbData->unk8C, rbData->unk360, 5.0f);
    // FAKE
    var_fv1 = rbData->unk1DC.x / 10.0f;
    if (var_fv1 < -1.0f) {
        var_fv1 = -1.0f;
    } else if (var_fv1 > 1.0f) {
        var_fv1 = 1.0f;
    }
    uvModelGetPosm(rbData->modelId, rbData->unk2DE, &sp40);
    uvMat4RotateAxis(&sp40, rbData->unk360, 'x');
    uvMat4RotateAxis(&sp40, rbData->unk35C, 'z');
    uvDobjPosm(rbData->objId, rbData->unk2DE, &sp40);
    if (rbData->modelId == MODEL_RB_KIWI) {
        var_ft4 = rbData->unk1DC.z / 10.0f;
        if (var_ft4 < -1.0f) {
            var_ft4 = -1.0f;
        } else if (var_ft4 > 1.0f) {
            var_ft4 = 1.0f;
        }
        var_fv1 = rbData->unk1DC.x / 10.0f;
        if (var_fv1 < -1.0f) {
            var_fv1 = -1.0f;
        } else if (var_fv1 > 1.0f) {
            var_fv1 = 1.0f;
        }
        rbData->unk368 = func_80313AF4(((0.800000011920929 + (0.2 * uvRandF_RANLUX())) * var_ft4) + ((0.800000011920929 + (0.2 * uvRandF_RANLUX())) * var_fv1),
                                       rbData->unk368, 20.0f);
        uvModelGetPosm(rbData->modelId, 0xE, &sp40);
        uvMat4RotateAxis(&sp40, rbData->unk368, 'x');
        uvDobjPosm(rbData->objId, 0xE, &sp40);

        rbData->unk370 = func_80313AF4(((0.800000011920929 + (0.2 * uvRandF_RANLUX())) * var_ft4) + ((0.800000011920929 + (0.2 * uvRandF_RANLUX())) * var_fv1),
                                       rbData->unk370, 20.0f);
        uvModelGetPosm(rbData->modelId, 0xD, &sp40);
        uvMat4RotateAxis(&sp40, rbData->unk370, 'x');
        uvDobjPosm(rbData->objId, 0xD, &sp40);
    }
}

void func_80327380(RocketBeltData* rbData) {
    uvModelGet(rbData->unk338, MODEL_BIG_ROCK_BOULDER);
    uvModelGet(rbData->unk339, MODEL_BIG_ROCK_BOULDER);
    rbData->unk338 = 0xFF;
    rbData->unk339 = 0xFF;
}

void func_803273C8(RocketBeltData* rbData, u8 arg1) {
    static f32 D_8034FBA0 = 0.0f;
    static f32 D_8034FBA4 = 0.5f;
    f32 var_fa1;
    u8 sp23;

    if (rbData->unk90 == 3) {
        func_80327614(rbData);
        return;
    }
    if ((fdr_802E6B5C() != 3) && (fdr_802E6B5C() != 4)) {
        if (rbData->unk33B == 0) {
            if (arg1 != 0) {
                D_8034FBA4 = 1.0f;
                rbData->unk33B = 2;
            } else {
                rbData->unk33B = 1;
                D_8034FBA4 = 0.8f;
            }
            rbData->unk33C = 0.0f;
            D_8034FBA0 = 0.0f;
            uvDobj_802180DC(rbData->objId, &D_80371120);
            rbData->unk80 = 0;
            rbData->unk78 = 0.0f;
            func_80327040(rbData, GAME_STATE_TEST_UPDATE);
        }

        var_fa1 = rbData->unk33C / 3.0f;

        // clang-format off
        if (var_fa1 < 0.0f) { var_fa1 = 0.0f; } else if (var_fa1 > 0.99f) { var_fa1 = 0.99f; }
        // clang-format on

        rbData->unk33C += D_8034F854;
        D_8034FBA0 += D_8034FBA4 * D_8034F854;
        if ((D_8034FBA0 >= 1.0f) && (D_8034FBA4 > 0.0f)) {
            D_8034FBA0 = 1.0f;
            D_8034FBA4 = -D_8034FBA4;
        }

        if (D_8034FBA0 <= 0.0f) {
            if (D_8034FBA4 < 0.0f) {
                D_8034FBA0 = 0.0f;
                D_8034FBA4 = -D_8034FBA4;
            }
        }
        switch (rbData->unk33B) {
        case 2:
            sp23 = rbData->unk2E2;
            break;
        case 1:
            sp23 = rbData->unk2E3;
            break;
        }

        uvJanimPoseLine(&D_803712D0, sp23, D_8034FBA0);
        func_802006FC(&D_80371480, &D_80371120, &D_803712D0, var_fa1);
        func_80200638(rbData->objId, &D_80371480);
    }
}

void func_80327614(RocketBeltData* rbData) {
    Mtx4F spD0;
    Mtx4F sp90;
    Mtx4F sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;

    if (rbData->unk33A == 0) {
        rbData->unk33A = 1;
        sp4C = rbData->unk10.m[3][0];
        sp48 = rbData->unk10.m[3][1];
        sp44 = rbData->unk10.m[3][2];
        if (rbData->unkE8 != 0) {
            sndPlaySfx(0x1A);
            uvEventPost(0x12, 0);
            func_802F8AB8(sp4C, sp48, sp44, 1.0f, &rbData->unk1E8);
            rbData->camera->unk6 = 0;
            rbData->unk2 = rbData->camera->unk6;
            uvDobjState(rbData->objId, rbData->unk2);
        }

        uvFxProps(rbData->unk338, 3, 0.0f, 0.0f, 0.0f, 0);
        uvFxProps(rbData->unk339, 3, 0.0f, 0.0f, 0.0f, 0);
        uvModelGetPosm(rbData->modelId, rbData->unk2E0, &spD0);
        uvModelGetPosm(rbData->modelId, rbData->unk2E1, &sp90);
        uvMat4Scale(&spD0, 1.0f, 1.0f, 0.0f);
        uvMat4Scale(&sp90, 1.0f, 1.0f, 0.0f);
        uvDobjPosm(rbData->objId, rbData->unk2E0, &spD0);
        uvDobjPosm(rbData->objId, rbData->unk2E1, &sp90);
        shadow_803343D8(0);
    }
    func_803277E0(rbData);
    uvModelGetPosm(rbData->modelId, rbData->unk2DE, &sp50);
    uvMat4RotateAxis(&sp50, uvCosF(8.0f * D_8034F850), 'z');
    uvDobjPosm(rbData->objId, rbData->unk2DE, &sp50);
}

void func_803277E0(RocketBeltData* rbData) {
    Mtx4F sp38;
    f32 var_fs0;

    var_fs0 = (0.4f * uvCosF(12.5f * D_8034F850)) * uvSinF(10.3f * D_8034F850);
    uvModelGetPosm(rbData->modelId, rbData->unk2D9, &sp38);
    uvMat4RotateAxis(&sp38, var_fs0 + 0.2f, 'x');
    uvDobjPosm(rbData->objId, rbData->unk2D9, &sp38);
    uvModelGetPosm(rbData->modelId, rbData->unk2D6, &sp38);
    uvMat4RotateAxis(&sp38, 0.2f - var_fs0, 'x');
    uvDobjPosm(rbData->objId, rbData->unk2D6, &sp38);
    var_fs0 = uvCosF(6.0f * D_8034F850) * 1.5f;
    if (var_fs0 > 0.0f) {
        var_fs0 = -var_fs0;
    }
    uvModelGetPosm(rbData->modelId, rbData->unk2DA, &sp38);
    uvMat4RotateAxis(&sp38, var_fs0, 'x');
    uvDobjPosm(rbData->objId, rbData->unk2DA, &sp38);
    uvModelGetPosm(rbData->modelId, rbData->unk2D7, &sp38);
    uvMat4RotateAxis(&sp38, var_fs0, 'x');
    uvDobjPosm(rbData->objId, rbData->unk2D7, &sp38);
    uvModelGetPosm(rbData->modelId, rbData->unk2DB, &sp38);
    uvMat4RotateAxis(&sp38, -0.7f, 'x');
    uvDobjPosm(rbData->objId, rbData->unk2DB, &sp38);
    uvModelGetPosm(rbData->modelId, rbData->unk2D8, &sp38);
    uvMat4RotateAxis(&sp38, -0.7f, 'x');
    uvDobjPosm(rbData->objId, rbData->unk2D8, &sp38);
}

void func_803279F0(RocketBeltData* rbData) {
    static f32 D_8034FBA8 = 0.0f;
    Mtx4F sp178;
    Mtx4F sp138;
    Mtx4F spF8;
    Mtx4F spB8;
    Mtx4F sp78;
    f32 sp74;
    Vec3F* temp_v0;

    uvModelGetPosm(rbData->modelId, rbData->unk2DC, &sp178);
    uvModelGetPosm(rbData->modelId, rbData->unk2DD, &sp138);
    uvModelGetPosm(rbData->modelId, rbData->unk2E0, &spF8);
    uvModelGetPosm(rbData->modelId, rbData->unk2E1, &spB8);
    uvMat4RotateAxis(&sp178, rbData->unk7C, 'x');
    uvDobjPosm(rbData->objId, rbData->unk2DC, &sp178);
    uvMat4RotateAxis(&sp138, rbData->unk7C, 'x');
    uvDobjPosm(rbData->objId, rbData->unk2DD, &sp138);
    if (rbData->unk80 != 0) {
        sp74 = 2.0f;
    } else {
        sp74 = ((1.0f - (demoRandF() * 0.7f)) + 0.7f + (0.5f * SQ(0.5f * (rbData->unk70 + 1.0f)))) * (0.6f * rbData->unk78);
    }
    D_8034FBA8 += 1.5f * sp74;
    uvFxProps(rbData->unk338, 3, sp74, sp74, sp74, 0);
    uvMat4RotateAxis(&spF8, -D_8034FBA8, 'z');
    if (rbData->unk80 == 0) {
        uvMat4Scale(&spF8, 1.5f * sp74, 1.5f * sp74, 3.5f * sp74);
    } else {
        uvMat4Scale(&spF8, 0.0f, 0.0f, 0.0f);
    }
    uvFxProps(rbData->unk339, 3, sp74, sp74, sp74, 0);
    uvMat4RotateAxis(&spB8, D_8034FBA8, 'z');
    if (rbData->unk80 == 0) {
        uvMat4Scale(&spB8, 1.5f * sp74, 1.5f * sp74, 3.5f * sp74);
    } else {
        uvMat4Scale(&spB8, 0.0f, 0.0f, 0.0f);
    }

    temp_v0 = &rbData->unk2BC;
    uvMat4MulBA(&sp78, &rbData->unk10, &sp178);
    uvMat4LocalTranslate(&sp78, temp_v0->x, temp_v0->y, temp_v0->z);
    func_8021A4D8(rbData->unk338, &sp78);
    temp_v0 = &rbData->unk2C8;
    uvMat4MulBA(&sp78, &rbData->unk10, &sp138);
    uvMat4LocalTranslate(&sp78, temp_v0->x, temp_v0->y, temp_v0->z);
    func_8021A4D8(rbData->unk339, &sp78);
    uvDobjPosm(rbData->objId, rbData->unk2E0, &spF8);
    uvDobjPosm(rbData->objId, rbData->unk2E1, &spB8);
    if (rbData->unk80 != 0) {
        uvFxProps(rbData->unk338, 5, 1.0f, 1.0f, 1.0f, 1.0f, 0);
        uvFxProps(rbData->unk339, 5, 1.0f, 1.0f, 1.0f, 1.0f, 0);
        uvFxProps(rbData->unk338, 6, 0.0f, 0.0f, 1.0f, 0.0f, 0);
        uvFxProps(rbData->unk339, 6, 0.0f, 0.0f, 1.0f, 0.0f, 0);
    } else if (rbData->unk78 > 1.0f) {
        uvFxProps(rbData->unk338, 5, 1.0f, 1.0f, 0.0f, 1.0f, 0);
        uvFxProps(rbData->unk339, 5, 1.0f, 1.0f, 0.0f, 1.0f, 0);
        uvFxProps(rbData->unk338, 6, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        uvFxProps(rbData->unk339, 6, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    } else {
        uvFxProps(rbData->unk338, 5, 1.0f, 0.8f, 0.0f, 1.0f, 0);
        uvFxProps(rbData->unk339, 5, 1.0f, 0.8f, 0.0f, 1.0f, 0);
        uvFxProps(rbData->unk338, 6, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        uvFxProps(rbData->unk339, 6, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    }
}

void func_80327F30(RocketBeltData* rbData, u8 gameState) {
    f32 var_fa0;
    f32 sp70;
    f32 sp6C;
    f32 var_fv0;
    Mtx4F sp28;

    if (gameState != GAME_STATE_RESULTS) {
        rbData->unk354 = func_80313AF4(rbData->unk214.z * 0.8f, rbData->unk354, 1.0f);
        if (rbData->unk354 < -0.9424779f) {
            rbData->unk354 = -0.9424779f;
        } else if (rbData->unk354 > 0.9424779f) {
            rbData->unk354 = 0.9424779f;
        }
        if (rbData->unkE9 == 0) {
            rbData->unk340 = func_80313AF4(rbData->unk1F8.y, rbData->unk340, 2.0f);
            if (rbData->unk340 > 12.0f) {
                rbData->unk340 = 12.0f;
            } else if (rbData->unk340 < -12.0f) {
                rbData->unk340 = -12.0f;
            }
            sp70 = rbData->unk340 * -0.2f;
            if (sp70 > 1.3962632f) {
                sp70 = 1.3962632f;
                sp6C = 0.0f;
            } else if (sp70 < -0.1745329f) {
                sp6C = (sp70 - -0.1745329f) * 3.0f;
                if (sp6C < -1.0471975f) {
                    sp6C = -1.0471975f;
                }
                sp70 = -0.1745329f;
            } else {
                sp6C = 0.0f;
            }
        } else {
            sp70 = 0.0f;
            sp6C = 0.0f;
        }
        var_fa0 = rbData->unk1F8.x * 0.02f;
        if (var_fa0 > 0.3490658f) {
            var_fa0 = 0.3490658f;
        } else if (var_fa0 < -0.3490658f) {
            var_fa0 = -0.3490658f;
        }
        rbData->unk348 = func_80313AF4(var_fa0, rbData->unk348, 2.0f);
        rbData->unk344 = func_80313AF4(sp70, rbData->unk344, 5.0f);
        rbData->unk34C = func_80313AF4(sp6C, rbData->unk34C, 5.0f);
        rbData->unk350 = rbData->unk1DC.z * -0.1f;
        if (rbData->unk350 < -1.2217304f) {
            rbData->unk350 = -1.2217304f;
        } else if (rbData->unk350 > 0.3490658f) {
            rbData->unk350 = 0.3490658f;
        }
        var_fv0 = (rbData->unkFC + rbData->unk25C.z) / 0.6f;
        if (var_fv0 < 0.0f) {
            var_fv0 = 0.0f;
        } else if (var_fv0 > 1.0f) {
            var_fv0 = 1.0f;
        }
        rbData->unk358 = 0.4f * var_fv0 * rbData->unk214.z;
        if (rbData->unk358 < -0.9424779f) {
            rbData->unk358 = -0.9424779f;
        } else if (rbData->unk358 > 0.9424779f) {
            rbData->unk358 = 0.9424779f;
        }
    }
    uvModelGetPosm(rbData->modelId, rbData->unk2D9, &sp28);
    uvMat4RotateAxis(&sp28, rbData->unk344 + rbData->unk358, 'x');
    uvMat4RotateAxis(&sp28, rbData->unk348, 'y');
    uvDobjPosm(rbData->objId, rbData->unk2D9, &sp28);
    uvModelGetPosm(rbData->modelId, rbData->unk2D6, &sp28);
    uvMat4RotateAxis(&sp28, rbData->unk344 - rbData->unk358, 'x');
    uvMat4RotateAxis(&sp28, rbData->unk348, 'y');
    uvDobjPosm(rbData->objId, rbData->unk2D6, &sp28);
    uvModelGetPosm(rbData->modelId, rbData->unk2DA, &sp28);
    uvMat4RotateAxis(&sp28, rbData->unk34C, 'x');
    uvDobjPosm(rbData->objId, rbData->unk2DA, &sp28);
    uvModelGetPosm(rbData->modelId, rbData->unk2D7, &sp28);
    uvMat4RotateAxis(&sp28, rbData->unk34C, 'x');
    uvDobjPosm(rbData->objId, rbData->unk2D7, &sp28);
    uvModelGetPosm(rbData->modelId, rbData->unk2DB, &sp28);
    uvMat4RotateAxis(&sp28, rbData->unk350, 'x');
    uvDobjPosm(rbData->objId, rbData->unk2DB, &sp28);
    uvModelGetPosm(rbData->modelId, rbData->unk2D8, &sp28);
    uvMat4RotateAxis(&sp28, rbData->unk350, 'x');
    uvDobjPosm(rbData->objId, rbData->unk2D8, &sp28);
    uvModelGetPosm(rbData->modelId, rbData->unk2DF, &sp28);
    uvMat4RotateAxis(&sp28, rbData->unk354, 'z');
    uvDobjPosm(rbData->objId, rbData->unk2DF, &sp28);
}
