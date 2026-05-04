#include "common.h"
#include <uv_anim.h>
#include <uv_dobj.h>
#include <uv_math.h>
#include <uv_matrix.h>
#include <uv_model.h>
#include <uv_utils.h>
#include "birdman.h"
#include "code_9A960.h"
#include "demo.h"

void bird_802CE190(BirdmanData* bmData, u8 gameState) {
    Mtx4F sp558;
    Unk80371120 sp3A8;
    Unk80371120 sp1F8;
    Unk80371120 sp48;
    f32 temp_fv1_2;
    f32 sp40;
    f32 var_fa0;
    s32 pad;
    f32 sp34;
    f32 sp30;

    if (bmData->unk2D0 <= 0.1f) {
        if ((bmData->unk2BC > 0.195f) || (bmData->unk2BC < 0.175f)) {
            bmData->unk2BC += (0.1f * D_8034F854);
            bmData->unk2D0 = 0.1f;
        } else {
            bmData->unk2BC += (bmData->unk2D0 * D_8034F854);
        }
    } else {
        bmData->unk2BC += bmData->unk2D0 * D_8034F854;
    }
    if (bmData->unk2BC >= 1.0f) {
        bmData->unk2BC -= (s32)bmData->unk2BC;
    }
    if ((bmData->unk224 > 47.5f) && (bmData->unkE8 > 0.7f)) {
        temp_fv1_2 = (bmData->unk224 / 20.0f) + 1.1f;
        switch (bmData->unk2CC) {
        case 26:
            bmData->unk2C4 += temp_fv1_2 * D_8034F854;
            if (bmData->unk2C4 > 1.0f) {
                bmData->unk2C4 = 1.0f;
                bmData->unk2CC = 27;
                bmData->unk2C8 = (f32)(demoRandF() + 25.0f);
            }
            break;
        case 27:
            bmData->unk2C8 = (f32)(bmData->unk2C8 - D_8034F854);
            if (bmData->unk2C8 < 0.0f) {
                bmData->unk2CC = 28;
            }
            break;
        case 28:
            bmData->unk2C4 -= temp_fv1_2 * D_8034F854;
            if (bmData->unk2C4 < 0.0f) {
                bmData->unk2CC = 26;
                bmData->unk2C4 = 0.0f;
            }
            break;
        }
    } else {
        if (bmData->unk2C4 > 0.0f) {
            bmData->unk2C4 = bmData->unk2C4 - (1.1f * D_8034F854);
            if (bmData->unk2C4 < 0.0f) {
                bmData->unk2C4 = 0.0f;
                bmData->unk2CC = 26;
            }
        }
    }
    uvJanim_80200B00(bmData->objId, bmData->unk2B8, bmData->unk2BC);
    uvDobjGetPosm(bmData->objId, bmData->unk2F8, &sp558);
    uvMat4RotateAxis(&sp558, bmData->unk2D4 * 0.66f, 'x');
    uvDobjPosm(bmData->objId, bmData->unk2F8, &sp558);
    uvDobjGetPosm(bmData->objId, bmData->unk2F9, &sp558);
    uvMat4RotateAxis(&sp558, bmData->unk2D4 * 0.66f, 'x');
    uvDobjPosm(bmData->objId, bmData->unk2F9, &sp558);
    bmData->unk2D8 = bmData->unk2D4;
    if (bmData->unk2C4 != 0.0f) {
        uvDobj_802180DC(bmData->objId, &sp3A8);
        uvJanimPoseLine(&sp1F8, bmData->unk2C0, 0.0f);
        uvJanim_802006FC(&sp48, &sp3A8, &sp1F8, bmData->unk2C4);
        uvJanim_80200638(bmData->objId, &sp48);
    }
    uvModelGetPosm(bmData->unk3F4, bmData->unk3F7, &sp558);
    uvMat4RotateAxis(&sp558, ((bmData->unkE8 * -0.5f) + bmData->unkF0) - (0.7f * bmData->unkD0), 'x');
    uvMat4RotateAxis(&sp558, bmData->unkEC - bmData->unkE4, 'z');
    uvDobjPosm(bmData->objId, bmData->unk3F7, &sp558);
    if (bmData->unk3F4 == 320) {
        sp34 = bmData->unk200.z / 5.0f;
        if (sp34 < -1.0f) {
            sp34 = -1.0f;
        } else if (sp34 > 1.0f) {
            sp34 = 1.0f;
        }
        sp30 = ((uvCosF(bmData->unkE4) * bmData->unk200.x) / 10.0f) + ((uvSinF(bmData->unkE4) * bmData->unk200.y) / 10.0f);
        if (sp30 < -1.5f) {
            sp30 = -1.5f;
        } else if (sp30 > 1.5f) {
            sp30 = 1.5f;
        }
        bmData->unk2E0 = func_80313AF4(((uvRandF_RANLUX() * 0.2f) + 0.8f) * sp34, bmData->unk2E0, 15.0f);
        uvRandF_RANLUX();
        bmData->unk2E8 = func_80313AF4(sp30, bmData->unk2E8, 15.0f);
        bmData->unk2E4 = func_80313AF4(((uvRandF_RANLUX() * 0.2f) + 0.8f) * sp34, bmData->unk2E4, 15.0f);
        uvRandF_RANLUX();
        bmData->unk2EC = func_80313AF4(sp30, bmData->unk2EC, 15.0f);
        uvModelGetPosm(bmData->unk3F4, 0x18, &sp558);
        uvMat4RotateAxis(&sp558, bmData->unk2E0, 'x');
        uvMat4RotateAxis(&sp558, bmData->unk2E8, 'z');
        uvDobjPosm(bmData->objId, 0x18, &sp558);
        uvModelGetPosm(bmData->unk3F4, 0x17, &sp558);
        uvMat4RotateAxis(&sp558, bmData->unk2E4, 'x');
        uvMat4RotateAxis(&sp558, bmData->unk2EC, 'z');
        uvDobjPosm(bmData->objId, 0x17, &sp558);
    }
    if (gameState != GAME_STATE_RESULTS) {
        bmData->unk2FC = func_80313AF4(uvSinF(bmData->unkD0) * (2.0f * bmData->unk24C), bmData->unk2FC, 0.5f);
        if (bmData->unk2FC < -1.047f) {
            bmData->unk2FC = -1.047f;
        } else if (bmData->unk2FC > 1.047f) {
            bmData->unk2FC = 1.047f;
        }
        bmData->unk300 = func_80313AF4(-bmData->unk228.z, bmData->unk300, 2.0f);
        if (bmData->unk300 > 12.0f) {
            bmData->unk300 = 12.0f;
        } else if (bmData->unk300 < -12.0f) {
            bmData->unk300 = -12.0f;
        }
        sp40 = bmData->unk300 * -0.07f;
        if (sp40 < -1.5707961f) { // DEG_TO_RAD(-90)
            sp40 = -1.5707961f;
        } else if (sp40 > 1.0471975f) { // DEG_TO_RAD(60)
            sp40 = 1.0471975f;
        }
        var_fa0 = bmData->unk228.x * 0.02f;
        if (var_fa0 < -0.3490658f) { // DEG_TO_RAD(-20)
            var_fa0 = -0.3490658f;
        } else if (var_fa0 > 0.3490658f) { // DEG_TO_RAD(20)
            var_fa0 = 0.3490658f;
        }
        bmData->unk308 = func_80313AF4(var_fa0, bmData->unk308, 2.0f);
        bmData->unk304 = func_80313AF4(sp40, bmData->unk304, 5.0f);
    }
    uvModelGetPosm(bmData->unk3F4, bmData->unk3F8, &sp558);
    uvMat4RotateAxis(&sp558, bmData->unk304, 'x');
    uvMat4RotateAxis(&sp558, bmData->unk308, 'y');
    uvDobjPosm(bmData->objId, bmData->unk3F8, &sp558);
    uvModelGetPosm(bmData->unk3F4, bmData->unk3F9, &sp558);
    uvMat4RotateAxis(&sp558, bmData->unk304, 'x');
    uvMat4RotateAxis(&sp558, bmData->unk308, 'y');
    uvDobjPosm(bmData->objId, bmData->unk3F9, &sp558);
    uvModelGetPosm(bmData->unk3F4, bmData->unk3F6, &sp558);
    uvMat4RotateAxis(&sp558, bmData->unk2FC, 'z');
    uvDobjPosm(bmData->objId, bmData->unk3F6, &sp558);
    if (bmData->unk105 != 0) {
        uvModelGetPosm(bmData->unk3F4, bmData->unk3F8, &sp558);
        uvDobjPosm(bmData->objId, bmData->unk3F8, &sp558);
        uvModelGetPosm(bmData->unk3F4, bmData->unk3F9, &sp558);
        uvDobjPosm(bmData->objId, bmData->unk3F9, &sp558);
        uvModelGetPosm(bmData->unk3F4, bmData->unk3F6, &sp558);
        uvDobjPosm(bmData->objId, bmData->unk3F6, &sp558);
        uvModelGetPosm(bmData->unk3F4, 5, &sp558);
        uvDobjPosm(bmData->objId, 5, &sp558);
    }
}

void bird_802CEA60(BirdmanData* bmData) {
    Mtx4F sp28;
    f32 sp24;
    f32 sp20;

    sp20 = uvCosF(12.5f * D_8034F850);
    sp24 = uvSinF(10.3f * D_8034F850) * (0.8f * sp20);
    uvModelGetPosm(bmData->unk3F4, bmData->unk3F8, &sp28);
    uvMat4RotateAxis(&sp28, sp24 + 0.2f, 'x');
    uvDobjPosm(bmData->objId, bmData->unk3F8, &sp28);
    uvModelGetPosm(bmData->unk3F4, bmData->unk3F9, &sp28);
    uvMat4RotateAxis(&sp28, 0.2f - sp24, 'x');
    uvDobjPosm(bmData->objId, bmData->unk3F9, &sp28);
}

void bird_802CEB68(BirdmanData* bmData, s32 arg1) {
    if (bmData->unk104 == 2) {
        bird_802CEA60(bmData);
    }
}
