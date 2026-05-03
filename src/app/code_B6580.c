#include "common.h"
#include "code_9A960.h"
#include "code_B6580.h"
#include "demo.h"
#include <uv_anim.h>
#include <uv_math.h>
#include <uv_matrix.h>
#include <uv_model.h>

STATIC_FUNC void func_8032F050(SkyDivingData* sdData) {
    f32 sp574;
    Unk80371120 sp3C4;
    Unk80371120 sp214;
    Unk80371120 sp64;
    Mtx4F sp24;

    if (sdData->unk29C < 1.0f) {
        sdData->unk29C = func_80313AF4(1.0f, sdData->unk29C, 1.0f);
        uvMat4Copy(&sp24, &sdData->unk2D0);
        uvMat4Scale(&sp24, sdData->unk29C, sdData->unk29C, sdData->unk29C);
        uvDobjPosm(sdData->objId, sdData->unk229, &sp24);
        uvDobjPosm(sdData->objId, sdData->unk228, &sp24);
    }
    if (demoButtonCheck(0, A_BUTTON) != 0) {
        uvJanimPoseLine(&sp214, sdData->unk1A6, 1.0f);
    } else {
        sp574 = (1.0f - sdData->unk270) * 0.5f;
        uvJanimPoseLine(&sp214, sdData->unk1A8, sp574);
    }
    sp574 = 2.5f * D_8034F854;
    uvDobj_802180DC(sdData->objId, &sp64);
    func_802006FC(&sp3C4, &sp64, &sp214, sp574);
    func_80200638(sdData->objId, &sp3C4);
}

STATIC_FUNC void func_8032F188(SkyDivingData* sdData) {
    f32 sp8DC;
    f32 var_fa0;
    f32 sp8D4;
    Unk80371120 sp724;
    Unk80371120 sp574;
    Unk80371120 sp3C4;
    Unk80371120 sp214;
    Unk80371120 sp64;
    Mtx4F sp24;

    if (sdData->unk268 < 1.0f) {
        uvJanimPoseLine(&sp574, sdData->unk1A2, 1.0f);
    } else {
        if (sdData->unk60 > 1.5707964f) { // DEG_TO_RAD(90)
            if (uvCosF(sdData->unk60) > 0.0f) {
                sp8DC = uvCosF(sdData->unk60);
            } else {
                sp8DC = -uvCosF(sdData->unk60);
            }
        } else {
            sp8DC = 0.0f;
        }
        uvJanimPoseLine(&sp214, sdData->unk1A4, 1.0f);
        uvJanimPoseLine(&sp64, sdData->unk1A0, 1.0f);
        func_802006FC(&sp574, &sp64, &sp214, sp8DC);
    }
    sp8DC = 5.0f * D_8034F854;
    uvDobj_802180DC(sdData->objId, &sp3C4);
    func_802006FC(&sp724, &sp3C4, &sp574, sp8DC);
    func_80200638(sdData->objId, &sp724);
    var_fa0 = 0.0f;
    if ((sdData->unkB9 != 0) && (sdData->unk70 == 1)) {
        sp8D4 = sdData->unk288;
        if (sp8D4 < 0.0f) {
            sp8D4 = 0.0f;
        } else if (sp8D4 > 2.0f) {
            sp8D4 = 2.0f;
        }
        var_fa0 = uvSinF(7.5f * D_8034F850) * sp8D4;
    }
    sdData->unk1AC = func_80313AF4(var_fa0, sdData->unk1AC, 1.0f);
    sdData->unk1B0 = func_80313AF4(sdData->unk270 * -1.2f, sdData->unk1B0, 3.0f);
    uvModelGetPosm(sdData->unk1C0, sdData->unk226, &sp24);
    uvMat4RotateAxis(&sp24, sdData->unk1B0, 'z');
    uvMat4RotateAxis(&sp24, sdData->unk1AC, 'x');
    uvDobjPosm(sdData->objId, sdData->unk226, &sp24);
}

void func_8032F3DC(SkyDivingData* sdData) {
    Mtx4F sp28;

    uvMat4SetIdentity(&sp28);
    uvMat4RotateAxis(&sp28, -sdData->unk5C, 'z');
    uvMat4RotateAxis(&sp28, -sdData->unk60, 'x');
    uvMat4CopyXYZ(&sdData->unk10, &sp28);
    if (sdData->unk70 == 0) {
        func_8032F188(sdData);
    } else if (sdData->unk70 == 1) {
        func_8032F050(sdData);
    }
}

void func_8032F47C(SkyDivingData* sdData) {
    f32 sp2A4;
    Mtx4F sp264;
    Mtx4F sp224;
    Mtx4F sp1E4;
    f32 var_fv1;
    Unk80371120 sp30;

    if (((sdData->unk70 == 3) || (sdData->unk70 == 5)) && (sdData->unk27A == 0)) {
        sdData->unk2CC += D_8034F854;
        uvMat4SetIdentity(&sp224);
        sp224.m[3][0] = sdData->unk10.m[3][0];
        sp224.m[3][1] = sdData->unk10.m[3][1];
        sp224.m[3][2] = sdData->unk10.m[3][2];
        uvMat4RotateAxis(&sp224, 3.1415927f, 'x'); // PI or DEG_TO_RAD(180)
        uvDobjPosm(sdData->objId, 0, &sp224);
        sp2A4 = (0.4f * uvCosF(12.5f * D_8034F850)) * uvSinF(10.3f * D_8034F850);
        uvModelGetPosm(sdData->unk1C0, sdData->unk221, &sp264);
        uvMat4RotateAxis(&sp264, sp2A4 + 0.2f, 'x');
        uvDobjPosm(sdData->objId, sdData->unk221, &sp264);
        uvModelGetPosm(sdData->unk1C0, sdData->unk21E, &sp264);
        uvMat4RotateAxis(&sp264, 0.2f - sp2A4, 'x');
        uvDobjPosm(sdData->objId, sdData->unk21E, &sp264);
        sp2A4 = uvCosF(6.0f * D_8034F850) * 1.5f;
        if (sp2A4 > 0.0f) {
            sp2A4 = -sp2A4;
        }
        uvModelGetPosm(sdData->unk1C0, sdData->unk222, &sp264);
        uvMat4RotateAxis(&sp264, sp2A4, 'x');
        uvDobjPosm(sdData->objId, sdData->unk222, &sp264);
        uvModelGetPosm(sdData->unk1C0, sdData->unk21F, &sp264);
        uvMat4RotateAxis(&sp264, sp2A4, 'x');
        uvDobjPosm(sdData->objId, sdData->unk21F, &sp264);
        uvModelGetPosm(sdData->unk1C0, sdData->unk223, &sp264);
        uvMat4RotateAxis(&sp264, -0.7f, 'x');
        uvDobjPosm(sdData->objId, sdData->unk223, &sp264);
        uvModelGetPosm(sdData->unk1C0, sdData->unk220, &sp264);
        uvMat4RotateAxis(&sp264, -0.7f, 'x');
        uvDobjPosm(sdData->objId, sdData->unk220, &sp264);
    }

    if (sdData->unk70 == 4) {
        if (sdData->unk2D0.m[3][2] > -2.0f) {
            sdData->unk2D0.m[3][1] -= 5.0f * D_8034F854;
            sdData->unk2D0.m[3][2] -= D_8034F854;
        }
        uvDobjPosm(sdData->objId, sdData->unk228, &sdData->unk2D0);
        uvDobjGetPosm(sdData->objId, sdData->unk228, &sp1E4);
        uvDobjProps(sdData->objId, 5, sdData->unk229, 0);
        uvDobjProps(sdData->objId, 5, sdData->unk22A, 0);
        uvDobjProps(sdData->objId, 5, sdData->unk22B, 0);
        uvDobjProps(sdData->objId, 5, sdData->unk22C, 0);
        uvDobjProps(sdData->objId, 5, sdData->unk22D, 0);
        sdData->unk2C8 += 5.0f * D_8034F854;
        if (sdData->unk2C8 > 1.0f) {
            sdData->unk2C8 = -1.0f;
        }
        if (sdData->unk2C8 < -1.0f) {
            sdData->unk2C8 = 1.0f;
        }
        var_fv1 = ABS_NOEQ(sdData->unk2C8);
        uvJanimPoseLine(&sp30, 0x55, var_fv1);
        func_80200638(sdData->objId, &sp30);
        uvDobjPosm(sdData->objId, sdData->unk228, &sp1E4);
    }

    if ((sdData->unk70 == 5) && (sdData->unk27A != 0)) {
        uvMat4Copy(&sp224, &sdData->unk10);
        uvMat4RotateAxis(&sp224, -1.5707963f, 'x'); // -DEG_TO_RAD(90)
        uvDobjPosm(sdData->objId, 0, &sp224);
        if (sdData->unk2D0.m[3][1] > -2.0f) {
            sdData->unk2D0.m[3][2] -= 5.0f * D_8034F854;
            sdData->unk2D0.m[3][1] = sdData->unk2D0.m[3][1] - D_8034F854;
        }
        uvJanimPoseLine(&sp30, 0x55, 1.0f);
        func_80200638(sdData->objId, &sp30);
        sp2A4 = uvCosF(6.0f * D_8034F850) * 1.5f;
        if (sp2A4 > 0.0f) {
            sp2A4 = -sp2A4;
        }
        uvModelGetPosm(sdData->unk278, sdData->unk222, &sp264);
        uvMat4RotateAxis(&sp264, sp2A4, 'x');
        uvDobjPosm(sdData->objId, sdData->unk222, &sp264);
        sp2A4 = uvSinF(6.0f * D_8034F850) * 1.5f;
        if (sp2A4 > 0.0f) {
            sp2A4 = -sp2A4;
        }
        uvModelGetPosm(sdData->unk278, sdData->unk21F, &sp264);
        uvMat4RotateAxis(&sp264, sp2A4, 'x');
        uvDobjPosm(sdData->objId, sdData->unk21F, &sp264);
        uvDobjPosm(sdData->objId, sdData->unk228, &sdData->unk2D0);
        uvDobjProps(sdData->objId, 5, sdData->unk229, 0);
        uvDobjProps(sdData->objId, 5, sdData->unk22A, 0);
        uvDobjProps(sdData->objId, 5, sdData->unk22B, 0);
        uvDobjProps(sdData->objId, 5, sdData->unk22C, 0);
        uvDobjProps(sdData->objId, 5, sdData->unk22D, 0);
    }
}
