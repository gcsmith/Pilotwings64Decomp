#include "common.h"
#include <uv_dobj.h>
#include <uv_janim.h>
#include <uv_math.h>
#include <uv_matrix.h>
#include <uv_model.h>
#include "birdman.h"
#include "code_9A960.h"
#include "demo.h"

void bird_802CE190(BirdmanData* arg0, u8 arg1) {
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

    if (arg0->unk2D0 <= 0.1f) {
        if ((arg0->unk2BC > 0.195f) || (arg0->unk2BC < 0.175f)) {
            arg0->unk2BC += (0.1f * D_8034F854);
            arg0->unk2D0 = 0.1f;
        } else {
            arg0->unk2BC += (arg0->unk2D0 * D_8034F854);
        }
    } else {
        arg0->unk2BC += arg0->unk2D0 * D_8034F854;
    }
    if (arg0->unk2BC >= 1.0f) {
        arg0->unk2BC -= (s32)arg0->unk2BC;
    }
    if ((arg0->unk224 > 47.5f) && (arg0->unkE8 > 0.7f)) {
        temp_fv1_2 = (arg0->unk224 / 20.0f) + 1.1f;
        switch (arg0->unk2CC) {
        case 26:
            arg0->unk2C4 += temp_fv1_2 * D_8034F854;
            if (arg0->unk2C4 > 1.0f) {
                arg0->unk2C4 = 1.0f;
                arg0->unk2CC = 27;
                arg0->unk2C8 = (f32)(demoRandF() + 25.0f);
            }
            break;
        case 27:
            arg0->unk2C8 = (f32)(arg0->unk2C8 - D_8034F854);
            if (arg0->unk2C8 < 0.0f) {
                arg0->unk2CC = 28;
            }
            break;
        case 28:
            arg0->unk2C4 -= temp_fv1_2 * D_8034F854;
            if (arg0->unk2C4 < 0.0f) {
                arg0->unk2CC = 26;
                arg0->unk2C4 = 0.0f;
            }
            break;
        }
    } else {
        if (arg0->unk2C4 > 0.0f) {
            arg0->unk2C4 = arg0->unk2C4 - (1.1f * D_8034F854);
            if (arg0->unk2C4 < 0.0f) {
                arg0->unk2C4 = 0.0f;
                arg0->unk2CC = 26;
            }
        }
    }
    func_80200B00(arg0->objId, arg0->unk2B8, arg0->unk2BC);
    uvDobjGetPosm(arg0->objId, arg0->unk2F8, &sp558);
    uvMat4RotateAxis(&sp558, arg0->unk2D4 * 0.66f, 'x');
    uvDobjPosm(arg0->objId, arg0->unk2F8, &sp558);
    uvDobjGetPosm(arg0->objId, arg0->unk2F9, &sp558);
    uvMat4RotateAxis(&sp558, arg0->unk2D4 * 0.66f, 'x');
    uvDobjPosm(arg0->objId, arg0->unk2F9, &sp558);
    arg0->unk2D8 = arg0->unk2D4;
    if (arg0->unk2C4 != 0.0f) {
        uvDobj_802180DC(arg0->objId, &sp3A8);
        uvJanimPoseLine(&sp1F8, arg0->unk2C0, 0.0f);
        func_802006FC(&sp48, &sp3A8, &sp1F8, arg0->unk2C4);
        func_80200638(arg0->objId, &sp48);
    }
    uvModelGetPosm(arg0->unk3F4, arg0->unk3F7, &sp558);
    uvMat4RotateAxis(&sp558, ((arg0->unkE8 * -0.5f) + arg0->unkF0) - (0.7f * arg0->unkD0), 'x');
    uvMat4RotateAxis(&sp558, arg0->unkEC - arg0->unkE4, 'z');
    uvDobjPosm(arg0->objId, arg0->unk3F7, &sp558);
    if (arg0->unk3F4 == 320) {
        sp34 = arg0->unk200.z / 5.0f;
        if (sp34 < -1.0f) {
            sp34 = -1.0f;
        } else if (sp34 > 1.0f) {
            sp34 = 1.0f;
        }
        sp30 = ((uvCosF(arg0->unkE4) * arg0->unk200.x) / 10.0f) + ((uvSinF(arg0->unkE4) * arg0->unk200.y) / 10.0f);
        if (sp30 < -1.5f) {
            sp30 = -1.5f;
        } else if (sp30 > 1.5f) {
            sp30 = 1.5f;
        }
        arg0->unk2E0 = func_80313AF4(((uvRandF_RANLUX() * 0.2f) + 0.8f) * sp34, arg0->unk2E0, 15.0f);
        uvRandF_RANLUX();
        arg0->unk2E8 = func_80313AF4(sp30, arg0->unk2E8, 15.0f);
        arg0->unk2E4 = func_80313AF4(((uvRandF_RANLUX() * 0.2f) + 0.8f) * sp34, arg0->unk2E4, 15.0f);
        uvRandF_RANLUX();
        arg0->unk2EC = func_80313AF4(sp30, arg0->unk2EC, 15.0f);
        uvModelGetPosm(arg0->unk3F4, 0x18, &sp558);
        uvMat4RotateAxis(&sp558, arg0->unk2E0, 'x');
        uvMat4RotateAxis(&sp558, arg0->unk2E8, 'z');
        uvDobjPosm(arg0->objId, 0x18, &sp558);
        uvModelGetPosm(arg0->unk3F4, 0x17, &sp558);
        uvMat4RotateAxis(&sp558, arg0->unk2E4, 'x');
        uvMat4RotateAxis(&sp558, arg0->unk2EC, 'z');
        uvDobjPosm(arg0->objId, 0x17, &sp558);
    }
    if (arg1 != 6) {
        arg0->unk2FC = func_80313AF4(uvSinF(arg0->unkD0) * (2.0f * arg0->unk24C), arg0->unk2FC, 0.5f);
        if (arg0->unk2FC < -1.047f) {
            arg0->unk2FC = -1.047f;
        } else if (arg0->unk2FC > 1.047f) {
            arg0->unk2FC = 1.047f;
        }
        arg0->unk300 = func_80313AF4(-arg0->unk228.z, arg0->unk300, 2.0f);
        if (arg0->unk300 > 12.0f) {
            arg0->unk300 = 12.0f;
        } else if (arg0->unk300 < -12.0f) {
            arg0->unk300 = -12.0f;
        }
        sp40 = arg0->unk300 * -0.07f;
        if (sp40 < -1.5707961f) { // DEG_TO_RAD(-90)
            sp40 = -1.5707961f;
        } else if (sp40 > 1.0471975f) { // DEG_TO_RAD(60)
            sp40 = 1.0471975f;
        }
        var_fa0 = arg0->unk228.x * 0.02f;
        if (var_fa0 < -0.3490658f) { // DEG_TO_RAD(-20)
            var_fa0 = -0.3490658f;
        } else if (var_fa0 > 0.3490658f) { // DEG_TO_RAD(20)
            var_fa0 = 0.3490658f;
        }
        arg0->unk308 = func_80313AF4(var_fa0, arg0->unk308, 2.0f);
        arg0->unk304 = func_80313AF4(sp40, arg0->unk304, 5.0f);
    }
    uvModelGetPosm(arg0->unk3F4, arg0->unk3F8, &sp558);
    uvMat4RotateAxis(&sp558, arg0->unk304, 'x');
    uvMat4RotateAxis(&sp558, arg0->unk308, 'y');
    uvDobjPosm(arg0->objId, arg0->unk3F8, &sp558);
    uvModelGetPosm(arg0->unk3F4, arg0->unk3F9, &sp558);
    uvMat4RotateAxis(&sp558, arg0->unk304, 'x');
    uvMat4RotateAxis(&sp558, arg0->unk308, 'y');
    uvDobjPosm(arg0->objId, arg0->unk3F9, &sp558);
    uvModelGetPosm(arg0->unk3F4, arg0->unk3F6, &sp558);
    uvMat4RotateAxis(&sp558, arg0->unk2FC, 'z');
    uvDobjPosm(arg0->objId, arg0->unk3F6, &sp558);
    if (arg0->unk105 != 0) {
        uvModelGetPosm(arg0->unk3F4, arg0->unk3F8, &sp558);
        uvDobjPosm(arg0->objId, arg0->unk3F8, &sp558);
        uvModelGetPosm(arg0->unk3F4, arg0->unk3F9, &sp558);
        uvDobjPosm(arg0->objId, arg0->unk3F9, &sp558);
        uvModelGetPosm(arg0->unk3F4, arg0->unk3F6, &sp558);
        uvDobjPosm(arg0->objId, arg0->unk3F6, &sp558);
        uvModelGetPosm(arg0->unk3F4, 5, &sp558);
        uvDobjPosm(arg0->objId, 5, &sp558);
    }
}

void bird_802CEA60(BirdmanData* arg0) {
    Mtx4F sp28;
    f32 sp24;
    f32 sp20;

    sp20 = uvCosF(12.5f * D_8034F850);
    sp24 = uvSinF(10.3f * D_8034F850) * (0.8f * sp20);
    uvModelGetPosm(arg0->unk3F4, arg0->unk3F8, &sp28);
    uvMat4RotateAxis(&sp28, sp24 + 0.2f, 'x');
    uvDobjPosm(arg0->objId, arg0->unk3F8, &sp28);
    uvModelGetPosm(arg0->unk3F4, arg0->unk3F9, &sp28);
    uvMat4RotateAxis(&sp28, 0.2f - sp24, 'x');
    uvDobjPosm(arg0->objId, arg0->unk3F9, &sp28);
}

void bird_802CEB68(BirdmanData* arg0, s32 arg1) {
    if (arg0->unk104 == 2) {
        bird_802CEA60(arg0);
    }
}
