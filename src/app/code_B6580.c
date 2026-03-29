#include "common.h"
#include "code_9A960.h"
#include "code_B6580.h"
#include "demo.h"
#include <uv_matrix.h>
#include <uv_janim.h>
#include <uv_math.h>
#include <uv_model.h>

STATIC_FUNC void func_8032F050(Unk8032F050* arg0) {
    f32 sp574;
    Unk80371120 sp3C4;
    Unk80371120 sp214;
    Unk80371120 sp64;
    Mtx4F sp24;

    if (arg0->unk29C < 1.0f) {
        arg0->unk29C = func_80313AF4(1.0f, arg0->unk29C, 1.0f);
        uvMat4Copy(&sp24, &arg0->unk2D0);
        uvMat4Scale(&sp24, arg0->unk29C, arg0->unk29C, arg0->unk29C);
        uvDobjPosm(arg0->unk0, arg0->unk229, &sp24);
        uvDobjPosm(arg0->unk0, arg0->unk228, &sp24);
    }
    if (demoButtonCheck(0, A_BUTTON) != 0) {
        uvJanimPoseLine(&sp214, arg0->unk1A6, 1.0f);
    } else {
        sp574 = (1.0f - arg0->unk270) * 0.5f;
        uvJanimPoseLine(&sp214, arg0->unk1A8, sp574);
    }
    sp574 = 2.5f * D_8034F854;
    uvDobj_802180DC(arg0->unk0, &sp64);
    func_802006FC(&sp3C4, &sp64, &sp214, sp574);
    func_80200638(arg0->unk0, &sp3C4);
}

STATIC_FUNC void func_8032F188(Unk8032F050* arg0) {
    f32 sp8DC;
    f32 var_fa0;
    f32 sp8D4;
    Unk80371120 sp724;
    Unk80371120 sp574;
    Unk80371120 sp3C4;
    Unk80371120 sp214;
    Unk80371120 sp64;
    Mtx4F sp24;

    if (arg0->unk268 < 1.0f) {
        uvJanimPoseLine(&sp574, arg0->unk1A2, 1.0f);
    } else {
        if (arg0->unk60 > 1.5707964f) { // DEG_TO_RAD(90)
            if (uvCosF(arg0->unk60) > 0.0f) {
                sp8DC = uvCosF(arg0->unk60);
            } else {
                sp8DC = -uvCosF(arg0->unk60);
            }
        } else {
            sp8DC = 0.0f;
        }
        uvJanimPoseLine(&sp214, arg0->unk1A4, 1.0f);
        uvJanimPoseLine(&sp64, arg0->unk1A0, 1.0f);
        func_802006FC(&sp574, &sp64, &sp214, sp8DC);
    }
    sp8DC = 5.0f * D_8034F854;
    uvDobj_802180DC(arg0->unk0, &sp3C4);
    func_802006FC(&sp724, &sp3C4, &sp574, sp8DC);
    func_80200638(arg0->unk0, &sp724);
    var_fa0 = 0.0f;
    if ((arg0->unkB9 != 0) && (arg0->unk70 == 1)) {
        sp8D4 = arg0->unk288;
        if (sp8D4 < 0.0f) {
            sp8D4 = 0.0f;
        } else if (sp8D4 > 2.0f) {
            sp8D4 = 2.0f;
        }
        var_fa0 = uvSinF(7.5f * D_8034F850) * sp8D4;
    }
    arg0->unk1AC = func_80313AF4(var_fa0, arg0->unk1AC, 1.0f);
    arg0->unk1B0 = func_80313AF4(arg0->unk270 * -1.2f, arg0->unk1B0, 3.0f);
    uvModelGetPosm(arg0->unk1C0, arg0->unk226, &sp24);
    uvMat4RotateAxis(&sp24, arg0->unk1B0, 'z');
    uvMat4RotateAxis(&sp24, arg0->unk1AC, 'x');
    uvDobjPosm(arg0->unk0, arg0->unk226, &sp24);
}

void func_8032F3DC(Unk8032F050* arg0) {
    Mtx4F sp28;

    uvMat4SetIdentity(&sp28);
    uvMat4RotateAxis(&sp28, -arg0->unk5C, 'z');
    uvMat4RotateAxis(&sp28, -arg0->unk60, 'x');
    uvMat4CopyXYZ(&arg0->unk10, &sp28);
    if (arg0->unk70 == 0) {
        func_8032F188(arg0);
    } else if (arg0->unk70 == 1) {
        func_8032F050(arg0);
    }
}

void func_8032F47C(Unk8032F050* arg0) {
    f32 sp2A4;
    Mtx4F sp264;
    Mtx4F sp224;
    Mtx4F sp1E4;
    f32 var_fv1;
    Unk80371120 sp30;
    f32 sp2C;

    if (((arg0->unk70 == 3) || (arg0->unk70 == 5)) && (arg0->unk27A == 0)) {
        arg0->unk2CC += D_8034F854;
        uvMat4SetIdentity(&sp224);
        sp224.m[3][0] = arg0->unk10.m[3][0];
        sp224.m[3][1] = arg0->unk10.m[3][1];
        sp224.m[3][2] = arg0->unk10.m[3][2];
        uvMat4RotateAxis(&sp224, 3.1415927f, 'x'); // PI or DEG_TO_RAD(180)
        uvDobjPosm(arg0->unk0, 0, &sp224);
        sp2C = uvCosF(12.5f * D_8034F850);
        sp2A4 = uvSinF(10.3f * D_8034F850) * (0.4f * sp2C);
        uvModelGetPosm(arg0->unk1C0, arg0->unk221, &sp264);
        uvMat4RotateAxis(&sp264, sp2A4 + 0.2f, 'x');
        uvDobjPosm(arg0->unk0, arg0->unk221, &sp264);
        uvModelGetPosm(arg0->unk1C0, arg0->unk21E, &sp264);
        uvMat4RotateAxis(&sp264, 0.2f - sp2A4, 'x');
        uvDobjPosm(arg0->unk0, arg0->unk21E, &sp264);
        sp2A4 = uvCosF(6.0f * D_8034F850) * 1.5f;
        if (sp2A4 > 0.0f) {
            sp2A4 = -sp2A4;
        }
        uvModelGetPosm(arg0->unk1C0, arg0->unk222, &sp264);
        uvMat4RotateAxis(&sp264, sp2A4, 'x');
        uvDobjPosm(arg0->unk0, arg0->unk222, &sp264);
        uvModelGetPosm(arg0->unk1C0, arg0->unk21F, &sp264);
        uvMat4RotateAxis(&sp264, sp2A4, 'x');
        uvDobjPosm(arg0->unk0, arg0->unk21F, &sp264);
        uvModelGetPosm(arg0->unk1C0, arg0->unk223, &sp264);
        uvMat4RotateAxis(&sp264, -0.7f, 'x');
        uvDobjPosm(arg0->unk0, arg0->unk223, &sp264);
        uvModelGetPosm(arg0->unk1C0, arg0->unk220, &sp264);
        uvMat4RotateAxis(&sp264, -0.7f, 'x');
        uvDobjPosm(arg0->unk0, arg0->unk220, &sp264);
    }

    if (arg0->unk70 == 4) {
        if (arg0->unk2D0.m[3][2] > -2.0f) {
            arg0->unk2D0.m[3][1] -= 5.0f * D_8034F854;
            arg0->unk2D0.m[3][2] -= D_8034F854;
        }
        uvDobjPosm(arg0->unk0, arg0->unk228, &arg0->unk2D0);
        uvDobjGetPosm(arg0->unk0, arg0->unk228, &sp1E4);
        uvDobjProps(arg0->unk0, 5, arg0->unk229, 0);
        uvDobjProps(arg0->unk0, 5, arg0->unk22A, 0);
        uvDobjProps(arg0->unk0, 5, arg0->unk22B, 0);
        uvDobjProps(arg0->unk0, 5, arg0->unk22C, 0);
        uvDobjProps(arg0->unk0, 5, arg0->unk22D, 0);
        arg0->unk2C8 += 5.0f * D_8034F854;
        if (arg0->unk2C8 > 1.0f) {
            arg0->unk2C8 = -1.0f;
        }
        if (arg0->unk2C8 < -1.0f) {
            arg0->unk2C8 = 1.0f;
        }
        var_fv1 = FABS(arg0->unk2C8);
        uvJanimPoseLine(&sp30, 0x55, var_fv1);
        func_80200638(arg0->unk0, &sp30);
        uvDobjPosm(arg0->unk0, arg0->unk228, &sp1E4);
    }

    if ((arg0->unk70 == 5) && (arg0->unk27A != 0)) {
        uvMat4Copy(&sp224, &arg0->unk10);
        uvMat4RotateAxis(&sp224, -1.5707963f, 'x'); // -DEG_TO_RAD(90)
        uvDobjPosm(arg0->unk0, 0, &sp224);
        if (arg0->unk2D0.m[3][1] > -2.0f) {
            arg0->unk2D0.m[3][2] -= 5.0f * D_8034F854;
            arg0->unk2D0.m[3][1] = arg0->unk2D0.m[3][1] - D_8034F854;
        }
        uvJanimPoseLine(&sp30, 0x55, 1.0f);
        func_80200638(arg0->unk0, &sp30);
        sp2A4 = uvCosF(6.0f * D_8034F850) * 1.5f;
        if (sp2A4 > 0.0f) {
            sp2A4 = -sp2A4;
        }
        uvModelGetPosm(arg0->unk278, arg0->unk222, &sp264);
        uvMat4RotateAxis(&sp264, sp2A4, 'x');
        uvDobjPosm(arg0->unk0, arg0->unk222, &sp264);
        sp2A4 = uvSinF(6.0f * D_8034F850) * 1.5f;
        if (sp2A4 > 0.0f) {
            sp2A4 = -sp2A4;
        }
        uvModelGetPosm(arg0->unk278, arg0->unk21F, &sp264);
        uvMat4RotateAxis(&sp264, sp2A4, 'x');
        uvDobjPosm(arg0->unk0, arg0->unk21F, &sp264);
        uvDobjPosm(arg0->unk0, arg0->unk228, &arg0->unk2D0);
        uvDobjProps(arg0->unk0, 5, arg0->unk229, 0);
        uvDobjProps(arg0->unk0, 5, arg0->unk22A, 0);
        uvDobjProps(arg0->unk0, 5, arg0->unk22B, 0);
        uvDobjProps(arg0->unk0, 5, arg0->unk22C, 0);
        uvDobjProps(arg0->unk0, 5, arg0->unk22D, 0);
    }
}
