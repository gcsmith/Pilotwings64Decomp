#include "common.h"
#include "code_60020.h"
#include <uv_math.h>
#include <uv_model.h>
#include "app/demo.h"
#include "app/environment.h"
#include "app/pads.h"
#include "app/toys.h"
#include "app/code_61A60.h"
#include "app/code_66F70.h"
#include "app/code_9A960.h"
#include "app/code_B2900.h"

Unk802D3658_Unk111C D_80359AD0;

void func_802D9818(CannonballData*);
s32 func_802D9900(CannonballData*);
void func_802D9AB8(CannonballData*);
void func_802D9B40(CannonballData*);
void func_802D9BBC(CannonballData*);

void func_802D8AF0(CannonballData* cbData) {
    static f32 D_8034EA10 = 0.0f;
    static f32 D_8034EA14 = 0.0f;
    static f32 D_8034EA18 = 0.0f;
    static f32 D_8034EA1C = 0.0f;
    static f32 D_8034EA20 = 0.0f;
    static f32 D_8034EA24 = 0.0f;
    Mtx4F spD0;
    f32 var_fa1;
    s32 pad[12];
    f32 var_fv1;
    f32 sp94;
    f32 sp90;
    f32 sp8C;
    f32 sp88;
    f32 sp84;
    f32 sp80;
    f32 sp7C;
    f32 sp78;
    s32 pad2[16];
    f32 sp34;
    f32 temp_fa0;

    uvModelGetPosm(cbData->modelId, cbData->unk291, &spD0);
    uvMat4RotateAxis(&spD0, (cbData->unkBC * -0.7f) + cbData->unkCC, 'z');
    uvMat4RotateAxis(&spD0, (cbData->unkC0 * -0.5f) + cbData->unkD0, 'x');
    uvDobjPosm(cbData->objId, cbData->unk291, &spD0);
    D_8034EA10 = func_80313AF4(demoRandF(), D_8034EA10, 0.3f);
    D_8034EA14 = func_80313AF4(demoRandF(), D_8034EA14, 0.3f);
    var_fa1 = cbData->unk1C4.z * -0.025f;
    if (var_fa1 < 0.5f) {
        var_fa1 = 0.5f;
    } else if (var_fa1 > 1.0f) {
        var_fa1 = 1.0f;
    }

    // FAKE (unused)
    var_fv1 = cbData->unk1C4.z * -0.025f;
    if (var_fv1 < 0.5f) {
        var_fv1 = 0.5f;
    } else if (var_fv1 > 1.0f) {
        var_fv1 = 1.0f;
    }

    D_8034EA18 += var_fa1 * (9.6f + D_8034EA10) * D_8034F854;
    if (D_8034EA18 > 6.2831855f) {
        D_8034EA18 -= 6.2831855f;
    }

    sp94 = uvSinF(D_8034EA18) * (0.25f * var_fa1);
    sp90 = (uvCosF(D_8034EA18) * (0.25f * var_fa1)) + 0.3f;
    D_8034EA1C += var_fa1 * (9.6f + D_8034EA14) * D_8034F854;
    if (D_8034EA1C > 6.2831855f) {
        D_8034EA1C -= 6.2831855f;
    }

    sp8C = uvSinF(D_8034EA1C + 3.1415927f) * (0.25f * var_fa1);
    sp88 = (uvCosF(D_8034EA1C + 3.1415927f) * (0.25f * var_fa1)) - 0.3f;
    D_8034EA20 += var_fa1 * (12.5f - D_8034EA14) * D_8034F854;
    if (D_8034EA20 > 6.2831855f) {
        D_8034EA20 -= 6.2831855f;
    }

    sp84 = uvCosF(D_8034EA20) * (0.75f * var_fa1);
    sp80 = uvSinF(D_8034EA20) * (0.75f * var_fa1);
    D_8034EA24 += var_fa1 * (12.5f - D_8034EA10) * D_8034F854;
    if (D_8034EA24 > 6.2831855f) {
        D_8034EA24 -= 6.2831855f;
    }

    sp7C = uvCosF(1.5707963f - D_8034EA24) * (0.75f * var_fa1);
    sp78 = uvSinF(1.5707963f - D_8034EA24) * (0.75f * var_fa1);
    sp34 = (30.0f - cbData->unk1C4.z) / 60.0f;
    if (sp34 < 0.0f) {
        sp34 = 0.0f;
    } else if (sp34 > 1.0f) {
        sp34 = 1.0f;
    }

    uvModelGetPosm(cbData->modelId, cbData->unk28C, &spD0);
    temp_fa0 = 1.0f - sp34;

    uvMat4RotateAxis(&spD0, (sp34 * sp94) + (temp_fa0 * -0.34382984f), 'x');
    uvMat4RotateAxis(&spD0, (sp34 * sp90) + (temp_fa0 * 0), 'y');
    uvDobjPosm(cbData->objId, cbData->unk28C, &spD0);
    uvModelGetPosm(cbData->modelId, cbData->unk289, &spD0);
    uvMat4RotateAxis(&spD0, (sp34 * sp8C) + (temp_fa0 * -0.34382984f), 'x');
    uvMat4RotateAxis(&spD0, (sp34 * sp88) + (temp_fa0 * 0), 'y');
    uvDobjPosm(cbData->objId, cbData->unk289, &spD0);
    uvModelGetPosm(cbData->modelId, cbData->unk285, &spD0);
    uvMat4RotateAxis(&spD0, (sp34 * sp84) + (temp_fa0 * -1.3409363f), 'y');
    uvMat4RotateAxis(&spD0, (sp34 * sp80) + (temp_fa0 * 0), 'z');
    uvDobjPosm(cbData->objId, cbData->unk285, &spD0);
    uvModelGetPosm(cbData->modelId, cbData->unk287, &spD0);
    uvMat4RotateAxis(&spD0, (sp34 * sp7C) + (temp_fa0 * 1.3409363f), 'y');
    uvMat4RotateAxis(&spD0, (sp34 * sp78) + (temp_fa0 * 0), 'z');
    uvDobjPosm(cbData->objId, cbData->unk287, &spD0);
    uvModelGetPosm(cbData->modelId, cbData->unk28D, &spD0);
    uvMat4RotateAxis(&spD0, (temp_fa0 * 0) + (temp_fa0 * 0.4974188f), 'x');
    uvDobjPosm(cbData->objId, cbData->unk28D, &spD0);
    uvModelGetPosm(cbData->modelId, cbData->unk28A, &spD0);
    uvMat4RotateAxis(&spD0, (temp_fa0 * 0) + (temp_fa0 * 0.4974188f), 'x');
    uvDobjPosm(cbData->objId, cbData->unk28A, &spD0);
    uvModelGetPosm(cbData->modelId, cbData->unk286, &spD0);
    uvMat4RotateAxis(&spD0, (temp_fa0 * 0) + (temp_fa0 * 1.0344565f), 'z');
    uvDobjPosm(cbData->objId, cbData->unk286, &spD0);
    uvModelGetPosm(cbData->modelId, cbData->unk288, &spD0);
    uvMat4RotateAxis(&spD0, (temp_fa0 * 0) + (temp_fa0 * -1.0344565f), 'z');
    uvDobjPosm(cbData->objId, cbData->unk288, &spD0);
}

// Potential file split?
s32 padD_8034EA28 = 0;
s32 padD_8034EA2C = 0;

void func_802D9220(CannonballData* cbData) {
    f32 var_fs0;
    Mtx4F sp34;

    var_fs0 = (0.4f * uvCosF(12.5f * D_8034F850)) * uvSinF(10.3f * D_8034F850);
    uvModelGetPosm(cbData->modelId, cbData->unk28C, &sp34);
    uvMat4RotateAxis(&sp34, var_fs0 + 0.2f, 'x');
    uvDobjPosm(cbData->objId, cbData->unk28C, &sp34);
    uvModelGetPosm(cbData->modelId, cbData->unk289, &sp34);
    uvMat4RotateAxis(&sp34, 0.2f - var_fs0, 'x');
    uvDobjPosm(cbData->objId, cbData->unk289, &sp34);
    var_fs0 = uvCosF(6.0f * D_8034F850) * 1.5f;
    if (var_fs0 > 0.0f) {
        var_fs0 = -var_fs0;
    }
    uvModelGetPosm(cbData->modelId, cbData->unk28D, &sp34);
    uvMat4RotateAxis(&sp34, var_fs0, 'x');
    uvDobjPosm(cbData->objId, cbData->unk28D, &sp34);
    uvModelGetPosm(cbData->modelId, cbData->unk28A, &sp34);
    uvMat4RotateAxis(&sp34, var_fs0, 'x');
    uvDobjPosm(cbData->objId, cbData->unk28A, &sp34);
    uvModelGetPosm(cbData->modelId, cbData->unk28E, &sp34);
    uvMat4RotateAxis(&sp34, -0.7f, 'x');
    uvDobjPosm(cbData->objId, cbData->unk28E, &sp34);
    uvModelGetPosm(cbData->modelId, cbData->unk28B, &sp34);
    uvMat4RotateAxis(&sp34, -0.7f, 'x');
    uvDobjPosm(cbData->objId, cbData->unk28B, &sp34);
}

void func_802D9430(CannonballData* cbData) {
    Vec3F sp24 = { 0.0f, 0.0f, 0.0f };

    D_80359AD0.unk0 = 3;
    uvVec3Copy(&D_80359AD0.unk4[0].unk28, &cbData->unk230);
    uvVec3Copy(&D_80359AD0.unk4[0].unk1C, &cbData->unk224);
    uvVec3Copy(&D_80359AD0.unk4[1].unk28, &cbData->unk254);
    uvVec3Copy(&D_80359AD0.unk4[1].unk1C, &cbData->unk260);
    uvVec3Copy(&D_80359AD0.unk4[2].unk28, &cbData->unk248);
    uvVec3Copy(&D_80359AD0.unk4[2].unk1C, &cbData->unk23C);
    func_802D94EC(cbData);
}

void func_802D94EC(CannonballData* cbData) {
    s32 pad;

    cbData->unk11C = 0;
    cbData->unk1D4.x = 0.0f;
    cbData->unk1D4.y = 0.0f;
    cbData->unk1D4.z = 0.0f;
    cbData->unk1E0.x = 0.0f;
    cbData->unk1E0.y = 0.0f;
    cbData->unk1E0.z = 0.0f;
    cbData->unk1F0.x = 0.0f;
    cbData->unk1F0.y = 0.0f;
    cbData->unk1F0.z = 0.0f;
    cbData->unk1FC.x = 0.0f;
    cbData->unk1FC.y = 0.0f;
    cbData->unk1FC.z = 0.0f;
    cbData->unk214.x = 0.0f;
    cbData->unk214.y = 0.0f;
    cbData->unk214.z = 0.0f;
    cbData->unk208.x = 0.0f;
    cbData->unk208.y = 0.0f;
    cbData->unk208.z = 0.0f;
    cbData->unk12C.x = 0.0f;
    cbData->unk12C.y = 0.0f;
    cbData->unk12C.z = 1.0f;
    cbData->unk1D0 = 0.0f;
    cbData->unk1EC = 0.0f;
    cbData->unkBC = 0.0f;
    cbData->unkC0 = 0.0f;

    uvMat4Copy(&cbData->unk178, &cbData->unk14);
    cbData->unk178.m[3][0] = 0.0f;
    cbData->unk178.m[3][1] = 0.0f;
    cbData->unk178.m[3][2] = 0.0f;
    uvMat4LocalToWorld(&cbData->unk178, &cbData->unk1C4, &cbData->unk1B8);
    cbData->unk2A0 = 1;
    cbData->unk294.x = cbData->unk14.m[3][0];
    cbData->unk294.y = cbData->unk14.m[3][1];
    cbData->unk294.z = cbData->unk14.m[3][2];
}

void func_802D95D8(CannonballData* cbData) {
    uvMat4Copy(&cbData->unk178, &cbData->unk14);
    cbData->unk178.m[3][0] = 0.0f;
    cbData->unk178.m[3][1] = 0.0f;
    cbData->unk178.m[3][2] = 0.0f;
    uvMat4InvertTranslationRotation(&cbData->unk138, &cbData->unk178);
    uvMat4LocalToWorld(&cbData->unk138, &cbData->unk1D4, &cbData->unk1E0);
    uvMat4LocalToWorld(&cbData->unk138, &cbData->unk1B8, &cbData->unk1C4);
    cbData->unk1D4.x = 0.0f;
    cbData->unk1D4.y = 0.0f;
    cbData->unk1D4.z = 0.0f;
    cbData->unk1FC.x = 0.0f;
    cbData->unk1FC.y = 0.0f;
    cbData->unk1FC.z = 0.0f;
    func_802D9AB8(cbData);
    func_802D9BBC(cbData);
    func_802D9B40(cbData);
    if (cbData->unkD4 == 1) {
        func_802D9818(cbData);
        uvMat4LocalToWorld(&cbData->unk178, &cbData->unk1E0, &cbData->unk1D4);
        cbData->unk1C4.x += D_8034F854 * cbData->unk1E0.x;
        cbData->unk1C4.y += D_8034F854 * cbData->unk1E0.y;
        cbData->unk1C4.z += D_8034F854 * cbData->unk1E0.z;
        cbData->unk1F0.x += D_8034F854 * cbData->unk1FC.x;
        cbData->unk1F0.y += D_8034F854 * cbData->unk1FC.y;
        cbData->unk1F0.z += D_8034F854 * cbData->unk1FC.z;
        uvMat4LocalTranslate(&cbData->unk14, cbData->unk1B8.x * D_8034F854, cbData->unk1B8.y * D_8034F854, cbData->unk1B8.z * D_8034F854);
        uvMat4RotateAxis(&cbData->unk14, cbData->unk1F0.z * D_8034F854, 'z');
        uvMat4RotateAxis(&cbData->unk14, cbData->unk1F0.x * D_8034F854, 'x');
        uvMat4RotateAxis(&cbData->unk14, cbData->unk1F0.y * D_8034F854, 'y');
        func_802D9900(cbData);
        cbData->unk1D0 = uvVec3Len(&cbData->unk1C4);
        cbData->unk1EC = uvVec3Len(&cbData->unk1E0);
    }
}

void func_802D9818(CannonballData* cbData) {
    Vec3F sp4C;
    Vec3F sp40;
    Vec3F sp34;
    Vec3F sp28;
    Vec3F sp1C;

    if (cbData->unk1D0 < 1.0f) {
        return;
    }
    sp4C.x = cbData->unk1C4.x / cbData->unk1D0;
    sp4C.y = cbData->unk1C4.y / cbData->unk1D0;
    sp4C.z = cbData->unk1C4.z / cbData->unk1D0;
    sp40.x = 0.0f;
    sp40.y = 0.0f;
    sp40.z = 1.0f;
    sp34.x = sp4C.x;
    sp34.y = sp4C.y;
    sp34.z = sp4C.z;
    uvVec3Cross(&sp28, &sp34, &sp40);
    uvVec3Normal(&sp28, &sp28);
    uvVec3Cross(&sp1C, &sp34, &sp28);
    cbData->unk14.m[0][0] = sp28.x;
    cbData->unk14.m[0][1] = sp28.y;
    cbData->unk14.m[0][2] = sp28.z;
    cbData->unk14.m[1][0] = sp1C.x;
    cbData->unk14.m[1][1] = sp1C.y;
    cbData->unk14.m[1][2] = sp1C.z;
    cbData->unk14.m[2][0] = sp34.x;
    cbData->unk14.m[2][1] = sp34.y;
    cbData->unk14.m[2][2] = sp34.z;
}

s32 func_802D9900(CannonballData* cbData) {
    f32 sp5C;
    Vec3F* sp30;
    Vec3F sp4C;
    s32 sp48;
    f32 temp_fv0;
    s32 temp_v0;
    s32 pad[2];

    sp30 = (Vec3F*)cbData->unk14.m[3];
    cbData->unk120 = 1000000.0f;
    temp_v0 = db_getgnd(&cbData->unk294, sp30, &cbData->unk2A0, &sp48, &sp5C, &sp4C);
    temp_fv0 = sp30->z - sp5C;
    if (temp_fv0 <= cbData->unk120) {
        cbData->unk120 = temp_fv0;
        cbData->unk124 = sp48;
        cbData->unk128 = sp5C;
        cbData->unk12C.x = sp4C.x;
        cbData->unk12C.y = sp4C.y;
        cbData->unk12C.z = sp4C.z;
    }
    if (temp_v0 != 0) {
        cbData->unkD4 = 2;
        cbData->unkD5 = temp_v0;
        switch (temp_v0) {
        case 4:
            cbData->unk11C = 1;
            break;
        case 2:
            func_8032BE10()->unk8 = padsCannonTgtDist(cbData->unk14.m[3][0], cbData->unk14.m[3][1], cbData->unk14.m[3][2], sp48);
            break;
        case 8:
            toy_80348418(cbData->unk124, cbData->unk14.m[3][0], cbData->unk14.m[3][1], cbData->unk14.m[3][2], 1);
            break;
        case 1:
            if (func_802DC8E4(cbData->unk124) != 0) {
                cbData->unk11C = 1;
            }
            break;
        }
        func_802E05CC(&cbData->unk14, func_802E02EC(), &cbData->unk12C, 1);
        uvVec3Copy(&cbData->unk110, func_802E02EC());
    }
    cbData->unk294.x = sp30->x;
    cbData->unk294.y = sp30->y;
    cbData->unk294.z = sp30->z;
    if (cbData->unkD4 == 2) {
        return 0;
    }
    return 1;
}

void func_802D9AB8(CannonballData* cbData) {
    f32 var_fa0;
    f32 var_fv0;
    f32 var_fv1;

    var_fv0 = cbData->unk1B8.x * -0.001f * cbData->unk1B8.x;
    if (cbData->unk1B8.x < 0.0f) {
        var_fv0 = -var_fv0;
    }
    var_fv1 = cbData->unk1B8.y * -0.001f * cbData->unk1B8.y;
    if (cbData->unk1B8.y < 0.0f) {
        var_fv1 = -var_fv1;
    }
    var_fa0 = cbData->unk1B8.z * -0.001f * cbData->unk1B8.z;
    if (cbData->unk1B8.z < 0.0f) {
        var_fa0 = -var_fa0;
    }
    cbData->unk1D4.x += var_fv0;
    cbData->unk1D4.y += var_fv1;
    cbData->unk1D4.z += var_fa0;
}

void func_802D9B40(CannonballData* cbData) {
    Vec3F sp1C;

    sp1C.x = 0.0f;
    sp1C.y = 0.0f;
    sp1C.z = -cbData->unk27C;
    uvMat4LocalToWorld(&cbData->unk138, &cbData->unk208, &sp1C);
    cbData->unk1D4.x += cbData->unk208.x;
    cbData->unk1D4.y += cbData->unk208.y;
    cbData->unk1D4.z += cbData->unk208.z;
}

void func_802D9BBC(CannonballData* cbData) {
    Vec3F sp34;
    Vec3F sp28;

    env_802E1754(cbData->unk14.m[3][0], cbData->unk14.m[3][1], cbData->unk14.m[3][2], &sp28);
    uvMat4LocalToWorld(&cbData->unk138, &sp34, &sp28);
    cbData->unk214.x = sp34.x - cbData->unk1B8.x;
    cbData->unk214.y = sp34.y - cbData->unk1B8.y;
    cbData->unk214.z = sp34.z - cbData->unk1B8.z;
    cbData->unk1D4.x += cbData->unk278 * sp34.x;
    cbData->unk1D4.y += cbData->unk278 * sp34.y;
    cbData->unk1D4.z += cbData->unk278 * sp34.z;
    cbData->unk1E0.x += cbData->unk278 * sp28.x;
    cbData->unk1E0.y += cbData->unk278 * sp28.y;
    cbData->unk1E0.z += cbData->unk278 * sp28.z;
}
