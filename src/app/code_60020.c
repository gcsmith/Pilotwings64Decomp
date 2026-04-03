#include "common.h"
#include "code_60020.h"
#include <uv_math.h>
#include <uv_model.h>
#include "app/demo.h"
#include "app/environment.h"
#include "app/pads.h"
#include "app/toys.h"
#include "app/code_61A60.h"
#include "app/code_66160.h"
#include "app/code_9A960.h"
#include "app/code_B2900.h"

Unk802D3658_Unk111C D_80359AD0;

void func_802D9818(CannonballData*);
s32 func_802D9900(CannonballData*);
void func_802D9AB8(CannonballData*);
void func_802D9B40(CannonballData*);
void func_802D9BBC(CannonballData*);

void func_802D8AF0(CannonballData* arg0) {
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

    uvModelGetPosm(arg0->modelId, arg0->unk291, &spD0);
    uvMat4RotateAxis(&spD0, (arg0->unkBC * -0.7f) + arg0->unkCC, 'z');
    uvMat4RotateAxis(&spD0, (arg0->unkC0 * -0.5f) + arg0->unkD0, 'x');
    uvDobjPosm(arg0->objId, arg0->unk291, &spD0);
    D_8034EA10 = func_80313AF4(demoRandF(), D_8034EA10, 0.3f);
    D_8034EA14 = func_80313AF4(demoRandF(), D_8034EA14, 0.3f);
    var_fa1 = arg0->unk1C4.z * -0.025f;
    if (var_fa1 < 0.5f) {
        var_fa1 = 0.5f;
    } else if (var_fa1 > 1.0f) {
        var_fa1 = 1.0f;
    }
    // FAKE
    var_fv1 = arg0->unk1C4.z * -0.025f;

    D_8034EA18 += var_fa1 * (9.6f + D_8034EA10) * D_8034F854;
    if (D_8034EA18 > 6.2831855f) {
        D_8034EA18 -= 6.2831855f;
    }

    // FAKE
    if (var_fv1) { }

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
    sp34 = (30.0f - arg0->unk1C4.z) / 60.0f;
    if (sp34 < 0.0f) {
        sp34 = 0.0f;
    } else if (sp34 > 1.0f) {
        sp34 = 1.0f;
    }

    uvModelGetPosm(arg0->modelId, arg0->unk28C, &spD0);
    temp_fa0 = 1.0f - sp34;

    uvMat4RotateAxis(&spD0, (sp34 * sp94) + (temp_fa0 * -0.34382984f), 'x');
    uvMat4RotateAxis(&spD0, (sp34 * sp90) + (temp_fa0 * 0), 'y');
    uvDobjPosm(arg0->objId, arg0->unk28C, &spD0);
    uvModelGetPosm(arg0->modelId, arg0->unk289, &spD0);
    uvMat4RotateAxis(&spD0, (sp34 * sp8C) + (temp_fa0 * -0.34382984f), 'x');
    uvMat4RotateAxis(&spD0, (sp34 * sp88) + (temp_fa0 * 0), 'y');
    uvDobjPosm(arg0->objId, arg0->unk289, &spD0);
    uvModelGetPosm(arg0->modelId, arg0->unk285, &spD0);
    uvMat4RotateAxis(&spD0, (sp34 * sp84) + (temp_fa0 * -1.3409363f), 'y');
    uvMat4RotateAxis(&spD0, (sp34 * sp80) + (temp_fa0 * 0), 'z');
    uvDobjPosm(arg0->objId, arg0->unk285, &spD0);
    uvModelGetPosm(arg0->modelId, arg0->unk287, &spD0);
    uvMat4RotateAxis(&spD0, (sp34 * sp7C) + (temp_fa0 * 1.3409363f), 'y');
    uvMat4RotateAxis(&spD0, (sp34 * sp78) + (temp_fa0 * 0), 'z');
    uvDobjPosm(arg0->objId, arg0->unk287, &spD0);
    uvModelGetPosm(arg0->modelId, arg0->unk28D, &spD0);
    uvMat4RotateAxis(&spD0, (temp_fa0 * 0) + (temp_fa0 * 0.4974188f), 'x');
    uvDobjPosm(arg0->objId, arg0->unk28D, &spD0);
    uvModelGetPosm(arg0->modelId, arg0->unk28A, &spD0);
    uvMat4RotateAxis(&spD0, (temp_fa0 * 0) + (temp_fa0 * 0.4974188f), 'x');
    uvDobjPosm(arg0->objId, arg0->unk28A, &spD0);
    uvModelGetPosm(arg0->modelId, arg0->unk286, &spD0);
    uvMat4RotateAxis(&spD0, (temp_fa0 * 0) + (temp_fa0 * 1.0344565f), 'z');
    uvDobjPosm(arg0->objId, arg0->unk286, &spD0);
    uvModelGetPosm(arg0->modelId, arg0->unk288, &spD0);
    uvMat4RotateAxis(&spD0, (temp_fa0 * 0) + (temp_fa0 * -1.0344565f), 'z');
    uvDobjPosm(arg0->objId, arg0->unk288, &spD0);
}

// Potential file split?
s32 padD_8034EA28 = 0;
s32 padD_8034EA2C = 0;

void func_802D9220(CannonballData* arg0) {
    f32 var_fs0;
    Mtx4F sp34;

    var_fs0 = (0.4f * uvCosF(12.5f * D_8034F850)) * uvSinF(10.3f * D_8034F850);
    uvModelGetPosm(arg0->modelId, arg0->unk28C, &sp34);
    uvMat4RotateAxis(&sp34, var_fs0 + 0.2f, 'x');
    uvDobjPosm(arg0->objId, arg0->unk28C, &sp34);
    uvModelGetPosm(arg0->modelId, arg0->unk289, &sp34);
    uvMat4RotateAxis(&sp34, 0.2f - var_fs0, 'x');
    uvDobjPosm(arg0->objId, arg0->unk289, &sp34);
    var_fs0 = uvCosF(6.0f * D_8034F850) * 1.5f;
    if (var_fs0 > 0.0f) {
        var_fs0 = -var_fs0;
    }
    uvModelGetPosm(arg0->modelId, arg0->unk28D, &sp34);
    uvMat4RotateAxis(&sp34, var_fs0, 'x');
    uvDobjPosm(arg0->objId, arg0->unk28D, &sp34);
    uvModelGetPosm(arg0->modelId, arg0->unk28A, &sp34);
    uvMat4RotateAxis(&sp34, var_fs0, 'x');
    uvDobjPosm(arg0->objId, arg0->unk28A, &sp34);
    uvModelGetPosm(arg0->modelId, arg0->unk28E, &sp34);
    uvMat4RotateAxis(&sp34, -0.7f, 'x');
    uvDobjPosm(arg0->objId, arg0->unk28E, &sp34);
    uvModelGetPosm(arg0->modelId, arg0->unk28B, &sp34);
    uvMat4RotateAxis(&sp34, -0.7f, 'x');
    uvDobjPosm(arg0->objId, arg0->unk28B, &sp34);
}

void func_802D9430(CannonballData* arg0) {
    Vec3F sp24 = { 0.0f, 0.0f, 0.0f };

    D_80359AD0.unk0 = 3;
    uvVec3Copy(&D_80359AD0.unk4[0].unk28, &arg0->unk230);
    uvVec3Copy(&D_80359AD0.unk4[0].unk1C, &arg0->unk224);
    uvVec3Copy(&D_80359AD0.unk4[1].unk28, &arg0->unk254);
    uvVec3Copy(&D_80359AD0.unk4[1].unk1C, &arg0->unk260);
    uvVec3Copy(&D_80359AD0.unk4[2].unk28, &arg0->unk248);
    uvVec3Copy(&D_80359AD0.unk4[2].unk1C, &arg0->unk23C);
    func_802D94EC(arg0);
}

void func_802D94EC(CannonballData* arg0) {
    s32 pad;

    arg0->unk11C = 0;
    arg0->unk1D4.x = 0.0f;
    arg0->unk1D4.y = 0.0f;
    arg0->unk1D4.z = 0.0f;
    arg0->unk1E0.x = 0.0f;
    arg0->unk1E0.y = 0.0f;
    arg0->unk1E0.z = 0.0f;
    arg0->unk1F0.x = 0.0f;
    arg0->unk1F0.y = 0.0f;
    arg0->unk1F0.z = 0.0f;
    arg0->unk1FC.x = 0.0f;
    arg0->unk1FC.y = 0.0f;
    arg0->unk1FC.z = 0.0f;
    arg0->unk214.x = 0.0f;
    arg0->unk214.y = 0.0f;
    arg0->unk214.z = 0.0f;
    arg0->unk208.x = 0.0f;
    arg0->unk208.y = 0.0f;
    arg0->unk208.z = 0.0f;
    arg0->unk12C.x = 0.0f;
    arg0->unk12C.y = 0.0f;
    arg0->unk12C.z = 1.0f;
    arg0->unk1D0 = 0.0f;
    arg0->unk1EC = 0.0f;
    arg0->unkBC = 0.0f;
    arg0->unkC0 = 0.0f;

    uvMat4Copy(&arg0->unk178, &arg0->unk14);
    arg0->unk178.m[3][0] = 0.0f;
    arg0->unk178.m[3][1] = 0.0f;
    arg0->unk178.m[3][2] = 0.0f;
    uvMat4LocalToWorld(&arg0->unk178, &arg0->unk1C4, &arg0->unk1B8);
    arg0->unk2A0 = 1;
    arg0->unk294.x = arg0->unk14.m[3][0];
    arg0->unk294.y = arg0->unk14.m[3][1];
    arg0->unk294.z = arg0->unk14.m[3][2];
}

void func_802D95D8(CannonballData* arg0) {
    uvMat4Copy(&arg0->unk178, &arg0->unk14);
    arg0->unk178.m[3][0] = 0.0f;
    arg0->unk178.m[3][1] = 0.0f;
    arg0->unk178.m[3][2] = 0.0f;
    uvMat4InvertTranslationRotation(&arg0->unk138, &arg0->unk178);
    uvMat4LocalToWorld(&arg0->unk138, &arg0->unk1D4, &arg0->unk1E0);
    uvMat4LocalToWorld(&arg0->unk138, &arg0->unk1B8, &arg0->unk1C4);
    arg0->unk1D4.x = 0.0f;
    arg0->unk1D4.y = 0.0f;
    arg0->unk1D4.z = 0.0f;
    arg0->unk1FC.x = 0.0f;
    arg0->unk1FC.y = 0.0f;
    arg0->unk1FC.z = 0.0f;
    func_802D9AB8(arg0);
    func_802D9BBC(arg0);
    func_802D9B40(arg0);
    if (arg0->unkD4 == 1) {
        func_802D9818(arg0);
        uvMat4LocalToWorld(&arg0->unk178, &arg0->unk1E0, &arg0->unk1D4);
        arg0->unk1C4.x += D_8034F854 * arg0->unk1E0.x;
        arg0->unk1C4.y += D_8034F854 * arg0->unk1E0.y;
        arg0->unk1C4.z += D_8034F854 * arg0->unk1E0.z;
        arg0->unk1F0.x += D_8034F854 * arg0->unk1FC.x;
        arg0->unk1F0.y += D_8034F854 * arg0->unk1FC.y;
        arg0->unk1F0.z += D_8034F854 * arg0->unk1FC.z;
        uvMat4LocalTranslate(&arg0->unk14, arg0->unk1B8.x * D_8034F854, arg0->unk1B8.y * D_8034F854, arg0->unk1B8.z * D_8034F854);
        uvMat4RotateAxis(&arg0->unk14, arg0->unk1F0.z * D_8034F854, 'z');
        uvMat4RotateAxis(&arg0->unk14, arg0->unk1F0.x * D_8034F854, 'x');
        uvMat4RotateAxis(&arg0->unk14, arg0->unk1F0.y * D_8034F854, 'y');
        func_802D9900(arg0);
        arg0->unk1D0 = uvVec3Len(&arg0->unk1C4);
        arg0->unk1EC = uvVec3Len(&arg0->unk1E0);
    }
}

void func_802D9818(CannonballData* arg0) {
    Vec3F sp4C;
    Vec3F sp40;
    Vec3F sp34;
    Vec3F sp28;
    Vec3F sp1C;

    if (arg0->unk1D0 < 1.0f) {
        return;
    }
    sp4C.x = arg0->unk1C4.x / arg0->unk1D0;
    sp4C.y = arg0->unk1C4.y / arg0->unk1D0;
    sp4C.z = arg0->unk1C4.z / arg0->unk1D0;
    sp40.x = 0.0f;
    sp40.y = 0.0f;
    sp40.z = 1.0f;
    sp34.x = sp4C.x;
    sp34.y = sp4C.y;
    sp34.z = sp4C.z;
    uvVec3Cross(&sp28, &sp34, &sp40);
    uvVec3Normal(&sp28, &sp28);
    uvVec3Cross(&sp1C, &sp34, &sp28);
    arg0->unk14.m[0][0] = sp28.x;
    arg0->unk14.m[0][1] = sp28.y;
    arg0->unk14.m[0][2] = sp28.z;
    arg0->unk14.m[1][0] = sp1C.x;
    arg0->unk14.m[1][1] = sp1C.y;
    arg0->unk14.m[1][2] = sp1C.z;
    arg0->unk14.m[2][0] = sp34.x;
    arg0->unk14.m[2][1] = sp34.y;
    arg0->unk14.m[2][2] = sp34.z;
}

s32 func_802D9900(CannonballData* arg0) {
    f32 sp5C;
    Vec3F* sp30;
    Vec3F sp4C;
    s32 sp48;
    f32 temp_fv0;
    s32 temp_v0;
    s32 pad[2];

    sp30 = (Vec3F*)arg0->unk14.m[3];
    arg0->unk120 = 1000000.0f;
    temp_v0 = db_getgnd(&arg0->unk294, sp30, &arg0->unk2A0, &sp48, &sp5C, &sp4C);
    temp_fv0 = sp30->z - sp5C;
    if (temp_fv0 <= arg0->unk120) {
        arg0->unk120 = temp_fv0;
        arg0->unk124 = sp48;
        arg0->unk128 = sp5C;
        arg0->unk12C.x = sp4C.x;
        arg0->unk12C.y = sp4C.y;
        arg0->unk12C.z = sp4C.z;
    }
    if (temp_v0 != 0) {
        arg0->unkD4 = 2;
        arg0->unkD5 = temp_v0;
        switch (temp_v0) {
        case 4:
            arg0->unk11C = 1;
            break;
        case 2:
            func_8032BE10()->unk8 = padsCannonTgtDist(arg0->unk14.m[3][0], arg0->unk14.m[3][1], arg0->unk14.m[3][2], sp48);
            break;
        case 8:
            toy_80348418(arg0->unk124, arg0->unk14.m[3][0], arg0->unk14.m[3][1], arg0->unk14.m[3][2], 1);
            break;
        case 1:
            if (func_802DC8E4(arg0->unk124) != 0) {
                arg0->unk11C = 1;
            }
            break;
        }
        func_802E05CC(&arg0->unk14, func_802E02EC(), &arg0->unk12C, 1);
        uvVec3Copy(&arg0->unk110, func_802E02EC());
    }
    arg0->unk294.x = sp30->x;
    arg0->unk294.y = sp30->y;
    arg0->unk294.z = sp30->z;
    if (arg0->unkD4 == 2) {
        return 0;
    }
    return 1;
}

void func_802D9AB8(CannonballData* arg0) {
    f32 var_fa0;
    f32 var_fv0;
    f32 var_fv1;

    var_fv0 = arg0->unk1B8.x * -0.001f * arg0->unk1B8.x;
    if (arg0->unk1B8.x < 0.0f) {
        var_fv0 = -var_fv0;
    }
    var_fv1 = arg0->unk1B8.y * -0.001f * arg0->unk1B8.y;
    if (arg0->unk1B8.y < 0.0f) {
        var_fv1 = -var_fv1;
    }
    var_fa0 = arg0->unk1B8.z * -0.001f * arg0->unk1B8.z;
    if (arg0->unk1B8.z < 0.0f) {
        var_fa0 = -var_fa0;
    }
    arg0->unk1D4.x += var_fv0;
    arg0->unk1D4.y += var_fv1;
    arg0->unk1D4.z += var_fa0;
}

void func_802D9B40(CannonballData* arg0) {
    Vec3F sp1C;

    sp1C.x = 0.0f;
    sp1C.y = 0.0f;
    sp1C.z = -arg0->unk27C;
    uvMat4LocalToWorld(&arg0->unk138, &arg0->unk208, &sp1C);
    arg0->unk1D4.x += arg0->unk208.x;
    arg0->unk1D4.y += arg0->unk208.y;
    arg0->unk1D4.z += arg0->unk208.z;
}

void func_802D9BBC(CannonballData* arg0) {
    Vec3F sp34;
    Vec3F sp28;

    func_802E1754(arg0->unk14.m[3][0], arg0->unk14.m[3][1], arg0->unk14.m[3][2], &sp28);
    uvMat4LocalToWorld(&arg0->unk138, &sp34, &sp28);
    arg0->unk214.x = sp34.x - arg0->unk1B8.x;
    arg0->unk214.y = sp34.y - arg0->unk1B8.y;
    arg0->unk214.z = sp34.z - arg0->unk1B8.z;
    arg0->unk1D4.x += arg0->unk278 * sp34.x;
    arg0->unk1D4.y += arg0->unk278 * sp34.y;
    arg0->unk1D4.z += arg0->unk278 * sp34.z;
    arg0->unk1E0.x += arg0->unk278 * sp28.x;
    arg0->unk1E0.y += arg0->unk278 * sp28.y;
    arg0->unk1E0.z += arg0->unk278 * sp28.z;
}
