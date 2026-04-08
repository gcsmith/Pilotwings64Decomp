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

void func_80326F30(RocketBeltData* arg0) {
    arg0->unk338 = func_8021EFF0(2);
    uvModelGet(arg0->unk338, MODEL_BLUE_CUBOID);
    arg0->unk339 = func_8021EFF0(2);
    uvModelGet(arg0->unk339, MODEL_BLUE_CUBOID);
    uvFxProps(arg0->unk338, 3, 3.0f, 3.0f, 3.0f, 4, 1.0f, 1.0f, 1.0f, 1, 1e+20, 0);
    uvFxProps(arg0->unk339, 3, 3.0f, 3.0f, 3.0f, 4, 1.0f, 1.0f, 1.0f, 1, 1e+20, 0);
    arg0->unk33A = 0;
}

void func_80327040(RocketBeltData* arg0, u8 gameState) {
    Mtx4F sp40;
    f32 var_ft4;
    f32 var_fv1;

    func_803279F0(arg0);
    if ((arg0->unkF8 > 0.0f) && (arg0->unk90 != 4)) {
        func_80327F30(arg0, gameState);
    } else {
        func_803277E0(arg0);
    }
    arg0->unk35C = func_80313AF4((arg0->unk68 * -1.2f) + arg0->unk88, arg0->unk35C, 5.0f);
    var_ft4 = arg0->unk1DC.z / 20.0f;
    if (var_ft4 < -1.0f) {
        var_ft4 = -1.0f;
    } else if (var_ft4 > 1.0f) {
        var_ft4 = 1.0f;
    }
    arg0->unk360 = func_80313AF4((0.7f * var_ft4) + arg0->unk8C, arg0->unk360, 5.0f);
    // FAKE
    var_fv1 = arg0->unk1DC.x / 10.0f;
    if (var_fv1 < -1.0f) {
        var_fv1 = -1.0f;
    } else if (var_fv1 > 1.0f) {
        var_fv1 = 1.0f;
    }
    uvModelGetPosm(arg0->unk2D4, arg0->unk2DE, &sp40);
    uvMat4RotateAxis(&sp40, arg0->unk360, 'x');
    uvMat4RotateAxis(&sp40, arg0->unk35C, 'z');
    uvDobjPosm(arg0->objId, arg0->unk2DE, &sp40);
    if (arg0->unk2D4 == MODEL_RB_KIWI) {
        var_ft4 = arg0->unk1DC.z / 10.0f;
        if (var_ft4 < -1.0f) {
            var_ft4 = -1.0f;
        } else if (var_ft4 > 1.0f) {
            var_ft4 = 1.0f;
        }
        var_fv1 = arg0->unk1DC.x / 10.0f;
        if (var_fv1 < -1.0f) {
            var_fv1 = -1.0f;
        } else if (var_fv1 > 1.0f) {
            var_fv1 = 1.0f;
        }
        arg0->unk368 = func_80313AF4(((0.800000011920929 + (0.2 * uvRandF_RANLUX())) * var_ft4) + ((0.800000011920929 + (0.2 * uvRandF_RANLUX())) * var_fv1),
                                     arg0->unk368, 20.0f);
        uvModelGetPosm(arg0->unk2D4, 0xE, &sp40);
        uvMat4RotateAxis(&sp40, arg0->unk368, 'x');
        uvDobjPosm(arg0->objId, 0xE, &sp40);

        arg0->unk370 = func_80313AF4(((0.800000011920929 + (0.2 * uvRandF_RANLUX())) * var_ft4) + ((0.800000011920929 + (0.2 * uvRandF_RANLUX())) * var_fv1),
                                     arg0->unk370, 20.0f);
        uvModelGetPosm(arg0->unk2D4, 0xD, &sp40);
        uvMat4RotateAxis(&sp40, arg0->unk370, 'x');
        uvDobjPosm(arg0->objId, 0xD, &sp40);
    }
}

void func_80327380(RocketBeltData* arg0) {
    uvModelGet(arg0->unk338, MODEL_BIG_ROCK_BOULDER);
    uvModelGet(arg0->unk339, MODEL_BIG_ROCK_BOULDER);
    arg0->unk338 = 0xFF;
    arg0->unk339 = 0xFF;
}

void func_803273C8(RocketBeltData* arg0, u8 arg1) {
    static f32 D_8034FBA0 = 0.0f;
    static f32 D_8034FBA4 = 0.5f;
    f32 var_fa1;
    u8 sp23;

    if (arg0->unk90 == 3) {
        func_80327614(arg0);
        return;
    }
    if ((fdr_802E6B5C() != 3) && (fdr_802E6B5C() != 4)) {
        if (arg0->unk33B == 0) {
            if (arg1 != 0) {
                D_8034FBA4 = 1.0f;
                arg0->unk33B = 2;
            } else {
                arg0->unk33B = 1;
                D_8034FBA4 = 0.8f;
            }
            arg0->unk33C = 0.0f;
            D_8034FBA0 = 0.0f;
            uvDobj_802180DC(arg0->objId, &D_80371120);
            arg0->unk80 = 0;
            arg0->unk78 = 0.0f;
            func_80327040(arg0, GAME_STATE_TEST_UPDATE);
        }

        var_fa1 = arg0->unk33C / 3.0f;

        // clang-format off
        if (var_fa1 < 0.0f) { var_fa1 = 0.0f; } else if (var_fa1 > 0.99f) { var_fa1 = 0.99f; }
        // clang-format on

        arg0->unk33C += D_8034F854;
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
        switch (arg0->unk33B) {
        case 2:
            sp23 = arg0->unk2E2;
            break;
        case 1:
            sp23 = arg0->unk2E3;
            break;
        }

        uvJanimPoseLine(&D_803712D0, sp23, D_8034FBA0);
        func_802006FC(&D_80371480, &D_80371120, &D_803712D0, var_fa1);
        func_80200638(arg0->objId, &D_80371480);
    }
}

void func_80327614(RocketBeltData* arg0) {
    Mtx4F spD0;
    Mtx4F sp90;
    Mtx4F sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;

    if (arg0->unk33A == 0) {
        arg0->unk33A = 1;
        sp4C = arg0->unk10.m[3][0];
        sp48 = arg0->unk10.m[3][1];
        sp44 = arg0->unk10.m[3][2];
        if (arg0->unkE8 != 0) {
            sndPlaySfx(0x1A);
            uvEventPost(0x12, 0);
            func_802F8AB8(sp4C, sp48, sp44, 1.0f, &arg0->unk1E8);
            arg0->unk50->unk6 = 0;
            arg0->unk2 = arg0->unk50->unk6;
            uvDobjState(arg0->objId, arg0->unk2);
        }

        uvFxProps(arg0->unk338, 3, 0.0f, 0.0f, 0.0f, 0);
        uvFxProps(arg0->unk339, 3, 0.0f, 0.0f, 0.0f, 0);
        uvModelGetPosm(arg0->unk2D4, arg0->unk2E0, &spD0);
        uvModelGetPosm(arg0->unk2D4, arg0->unk2E1, &sp90);
        uvMat4Scale(&spD0, 1.0f, 1.0f, 0.0f);
        uvMat4Scale(&sp90, 1.0f, 1.0f, 0.0f);
        uvDobjPosm(arg0->objId, arg0->unk2E0, &spD0);
        uvDobjPosm(arg0->objId, arg0->unk2E1, &sp90);
        shadow_803343D8(0);
    }
    func_803277E0(arg0);
    uvModelGetPosm(arg0->unk2D4, arg0->unk2DE, &sp50);
    uvMat4RotateAxis(&sp50, uvCosF(8.0f * D_8034F850), 'z');
    uvDobjPosm(arg0->objId, arg0->unk2DE, &sp50);
}

void func_803277E0(RocketBeltData* arg0) {
    Mtx4F sp38;
    f32 var_fs0;

    var_fs0 = (0.4f * uvCosF(12.5f * D_8034F850)) * uvSinF(10.3f * D_8034F850);
    uvModelGetPosm(arg0->unk2D4, arg0->unk2D9, &sp38);
    uvMat4RotateAxis(&sp38, var_fs0 + 0.2f, 'x');
    uvDobjPosm(arg0->objId, arg0->unk2D9, &sp38);
    uvModelGetPosm(arg0->unk2D4, arg0->unk2D6, &sp38);
    uvMat4RotateAxis(&sp38, 0.2f - var_fs0, 'x');
    uvDobjPosm(arg0->objId, arg0->unk2D6, &sp38);
    var_fs0 = uvCosF(6.0f * D_8034F850) * 1.5f;
    if (var_fs0 > 0.0f) {
        var_fs0 = -var_fs0;
    }
    uvModelGetPosm(arg0->unk2D4, arg0->unk2DA, &sp38);
    uvMat4RotateAxis(&sp38, var_fs0, 'x');
    uvDobjPosm(arg0->objId, arg0->unk2DA, &sp38);
    uvModelGetPosm(arg0->unk2D4, arg0->unk2D7, &sp38);
    uvMat4RotateAxis(&sp38, var_fs0, 'x');
    uvDobjPosm(arg0->objId, arg0->unk2D7, &sp38);
    uvModelGetPosm(arg0->unk2D4, arg0->unk2DB, &sp38);
    uvMat4RotateAxis(&sp38, -0.7f, 'x');
    uvDobjPosm(arg0->objId, arg0->unk2DB, &sp38);
    uvModelGetPosm(arg0->unk2D4, arg0->unk2D8, &sp38);
    uvMat4RotateAxis(&sp38, -0.7f, 'x');
    uvDobjPosm(arg0->objId, arg0->unk2D8, &sp38);
}

void func_803279F0(RocketBeltData* arg0) {
    static f32 D_8034FBA8 = 0.0f;
    Mtx4F sp178;
    Mtx4F sp138;
    Mtx4F spF8;
    Mtx4F spB8;
    Mtx4F sp78;
    f32 sp74;
    Vec3F* temp_v0;

    uvModelGetPosm(arg0->unk2D4, arg0->unk2DC, &sp178);
    uvModelGetPosm(arg0->unk2D4, arg0->unk2DD, &sp138);
    uvModelGetPosm(arg0->unk2D4, arg0->unk2E0, &spF8);
    uvModelGetPosm(arg0->unk2D4, arg0->unk2E1, &spB8);
    uvMat4RotateAxis(&sp178, arg0->unk7C, 'x');
    uvDobjPosm(arg0->objId, arg0->unk2DC, &sp178);
    uvMat4RotateAxis(&sp138, arg0->unk7C, 'x');
    uvDobjPosm(arg0->objId, arg0->unk2DD, &sp138);
    if (arg0->unk80 != 0) {
        sp74 = 2.0f;
    } else {
        sp74 = ((1.0f - (demoRandF() * 0.7f)) + 0.7f + (0.5f * SQ(0.5f * (arg0->unk70 + 1.0f)))) * (0.6f * arg0->unk78);
    }
    D_8034FBA8 += 1.5f * sp74;
    uvFxProps(arg0->unk338, 3, sp74, sp74, sp74, 0);
    uvMat4RotateAxis(&spF8, -D_8034FBA8, 'z');
    if (arg0->unk80 == 0) {
        uvMat4Scale(&spF8, 1.5f * sp74, 1.5f * sp74, 3.5f * sp74);
    } else {
        uvMat4Scale(&spF8, 0.0f, 0.0f, 0.0f);
    }
    uvFxProps(arg0->unk339, 3, sp74, sp74, sp74, 0);
    uvMat4RotateAxis(&spB8, D_8034FBA8, 'z');
    if (arg0->unk80 == 0) {
        uvMat4Scale(&spB8, 1.5f * sp74, 1.5f * sp74, 3.5f * sp74);
    } else {
        uvMat4Scale(&spB8, 0.0f, 0.0f, 0.0f);
    }

    temp_v0 = &arg0->unk2BC;
    uvMat4MulBA(&sp78, &arg0->unk10, &sp178);
    uvMat4LocalTranslate(&sp78, temp_v0->x, temp_v0->y, temp_v0->z);
    func_8021A4D8(arg0->unk338, &sp78);
    temp_v0 = &arg0->unk2C8;
    uvMat4MulBA(&sp78, &arg0->unk10, &sp138);
    uvMat4LocalTranslate(&sp78, temp_v0->x, temp_v0->y, temp_v0->z);
    func_8021A4D8(arg0->unk339, &sp78);
    uvDobjPosm(arg0->objId, arg0->unk2E0, &spF8);
    uvDobjPosm(arg0->objId, arg0->unk2E1, &spB8);
    if (arg0->unk80 != 0) {
        uvFxProps(arg0->unk338, 5, 1.0f, 1.0f, 1.0f, 1.0f, 0);
        uvFxProps(arg0->unk339, 5, 1.0f, 1.0f, 1.0f, 1.0f, 0);
        uvFxProps(arg0->unk338, 6, 0.0f, 0.0f, 1.0f, 0.0f, 0);
        uvFxProps(arg0->unk339, 6, 0.0f, 0.0f, 1.0f, 0.0f, 0);
    } else if (arg0->unk78 > 1.0f) {
        uvFxProps(arg0->unk338, 5, 1.0f, 1.0f, 0.0f, 1.0f, 0);
        uvFxProps(arg0->unk339, 5, 1.0f, 1.0f, 0.0f, 1.0f, 0);
        uvFxProps(arg0->unk338, 6, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        uvFxProps(arg0->unk339, 6, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    } else {
        uvFxProps(arg0->unk338, 5, 1.0f, 0.8f, 0.0f, 1.0f, 0);
        uvFxProps(arg0->unk339, 5, 1.0f, 0.8f, 0.0f, 1.0f, 0);
        uvFxProps(arg0->unk338, 6, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        uvFxProps(arg0->unk339, 6, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    }
}

void func_80327F30(RocketBeltData* arg0, u8 gameState) {
    f32 var_fa0;
    f32 sp70;
    f32 sp6C;
    f32 var_fv0;
    Mtx4F sp28;

    if (gameState != GAME_STATE_RESULTS) {
        arg0->unk354 = func_80313AF4(arg0->unk214.z * 0.8f, arg0->unk354, 1.0f);
        if (arg0->unk354 < -0.9424779f) {
            arg0->unk354 = -0.9424779f;
        } else if (arg0->unk354 > 0.9424779f) {
            arg0->unk354 = 0.9424779f;
        }
        if (arg0->unkE9 == 0) {
            arg0->unk340 = func_80313AF4(arg0->unk1F8.y, arg0->unk340, 2.0f);
            if (arg0->unk340 > 12.0f) {
                arg0->unk340 = 12.0f;
            } else if (arg0->unk340 < -12.0f) {
                arg0->unk340 = -12.0f;
            }
            sp70 = arg0->unk340 * -0.2f;
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
        var_fa0 = arg0->unk1F8.x * 0.02f;
        if (var_fa0 > 0.3490658f) {
            var_fa0 = 0.3490658f;
        } else if (var_fa0 < -0.3490658f) {
            var_fa0 = -0.3490658f;
        }
        arg0->unk348 = func_80313AF4(var_fa0, arg0->unk348, 2.0f);
        arg0->unk344 = func_80313AF4(sp70, arg0->unk344, 5.0f);
        arg0->unk34C = func_80313AF4(sp6C, arg0->unk34C, 5.0f);
        arg0->unk350 = arg0->unk1DC.z * -0.1f;
        if (arg0->unk350 < -1.2217304f) {
            arg0->unk350 = -1.2217304f;
        } else if (arg0->unk350 > 0.3490658f) {
            arg0->unk350 = 0.3490658f;
        }
        var_fv0 = (arg0->unkFC + arg0->unk25C.z) / 0.6f;
        if (var_fv0 < 0.0f) {
            var_fv0 = 0.0f;
        } else if (var_fv0 > 1.0f) {
            var_fv0 = 1.0f;
        }
        arg0->unk358 = 0.4f * var_fv0 * arg0->unk214.z;
        if (arg0->unk358 < -0.9424779f) {
            arg0->unk358 = -0.9424779f;
        } else if (arg0->unk358 > 0.9424779f) {
            arg0->unk358 = 0.9424779f;
        }
    }
    uvModelGetPosm(arg0->unk2D4, arg0->unk2D9, &sp28);
    uvMat4RotateAxis(&sp28, arg0->unk344 + arg0->unk358, 'x');
    uvMat4RotateAxis(&sp28, arg0->unk348, 'y');
    uvDobjPosm(arg0->objId, arg0->unk2D9, &sp28);
    uvModelGetPosm(arg0->unk2D4, arg0->unk2D6, &sp28);
    uvMat4RotateAxis(&sp28, arg0->unk344 - arg0->unk358, 'x');
    uvMat4RotateAxis(&sp28, arg0->unk348, 'y');
    uvDobjPosm(arg0->objId, arg0->unk2D6, &sp28);
    uvModelGetPosm(arg0->unk2D4, arg0->unk2DA, &sp28);
    uvMat4RotateAxis(&sp28, arg0->unk34C, 'x');
    uvDobjPosm(arg0->objId, arg0->unk2DA, &sp28);
    uvModelGetPosm(arg0->unk2D4, arg0->unk2D7, &sp28);
    uvMat4RotateAxis(&sp28, arg0->unk34C, 'x');
    uvDobjPosm(arg0->objId, arg0->unk2D7, &sp28);
    uvModelGetPosm(arg0->unk2D4, arg0->unk2DB, &sp28);
    uvMat4RotateAxis(&sp28, arg0->unk350, 'x');
    uvDobjPosm(arg0->objId, arg0->unk2DB, &sp28);
    uvModelGetPosm(arg0->unk2D4, arg0->unk2D8, &sp28);
    uvMat4RotateAxis(&sp28, arg0->unk350, 'x');
    uvDobjPosm(arg0->objId, arg0->unk2D8, &sp28);
    uvModelGetPosm(arg0->unk2D4, arg0->unk2DF, &sp28);
    uvMat4RotateAxis(&sp28, arg0->unk354, 'z');
    uvDobjPosm(arg0->objId, arg0->unk2DF, &sp28);
}
