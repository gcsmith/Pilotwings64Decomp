#include "common.h"
#include <uv_graphics.h>
#include <uv_math.h>
#include <uv_matrix.h>
#include <uv_vector.h>
#include "camera.h"
#include "code_61A60.h"
#include "code_72010.h"
#include "code_9A960.h"
#include "code_D1ED0.h"
#include "demo.h"
#include "environment.h"
#include "task.h"

// TODO: Unk802D472C_SP60 needs to be merged with some combination of Unk802D3658_Unk1224/8
typedef struct {
    s32 unk0;
    u8 pad4[0x1C - 0x4];
    volatile f32 unk1C; // volatile needed to avoid s0 usage
    u8 pad20[0x40 - 0x20];
} Unk802D472C_SP60;

// .data
f32 D_8034E9E0 = 1.0f;
u8 D_8034E9E4 = 0;
s32 pad_D_8034E9E8 = 0;

// .bss
Unk803599D0 D_803599D0;

// forward declarations
STATIC_FUNC s32 func_802D408C(Camera* camera);
STATIC_FUNC void func_802D3658(Camera* camera);
STATIC_FUNC void func_802D3790(Camera* camera);
STATIC_FUNC void func_802D3BE8(Camera* camera);
STATIC_FUNC void func_802D3FA4(Camera* camera);
STATIC_FUNC void func_802D41D8(Camera* camera);
STATIC_FUNC void func_802D46A4(Camera* camera, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
STATIC_FUNC void func_802D532C(Camera* camera);
STATIC_FUNC void func_802D559C(Camera* camera);
STATIC_FUNC s32 func_802D4CA4(Camera* camera, Mtx4F*);
STATIC_FUNC void func_802D58EC(Camera* camera, Mtx4F*);
STATIC_FUNC void func_802D4274(Camera* camera);

void func_802D3170(u8 unkIndex, Camera* camera) {
    f32 one;
    one = 1.0f;
    func_80204A8C(unkIndex, 3);
    func_802EAAE0(&camera->unk230);
    camera->unk2 = camera->unk1;
    camera->unk0 = 0;
    camera->unk24 = 10;
    camera->unk26 = 310;
    camera->unk28 = 18;
    camera->unk2A = 232;
    camera->unk3C = 1.0f;
    camera->unk40 = 2000.0f;
    camera->unk2C = one * -0.4906542f;
    camera->unk30 = one * 0.4906542f;
    camera->unk34 = one * -0.35f;
    camera->unk38 = one * 0.35f;
    camera->unk48 = 0.7f;
    camera->unk4C = 0.6f;
    camera->unk5C = 0.0f;
    camera->unk60 = -4.0f;
    camera->unk64 = -1.0f;
    camera->unk54 = 1.8f;
    camera->unk58 = 10.0f;
    camera->unk50 = 0.0f;
    camera->unk68.x = 0;
    camera->unkD = 1;
    camera->unk68.y = -1.2f;
    camera->unk68.z = -0.2f;
    camera->unk74 = -0.1f;
    camera->unk190 = 6.0f;
    camera->unk194 = 0.0f;
    camera->unk19C = 0.5f;
    camera->unk198 = 0.52359873f; // almost DEG_TO_RAD(30)
    camera->unkE = 1;
    camera->unkC = 1;
    camera->unk1A8 = 0.0f;
    camera->unk1AC = 0.0f;
    camera->unk1B0 = 0.0f;
    camera->unk200 = 0.0f;
    camera->unk204.x = 0.0f;
    camera->unk204.y = 0.0f;
    camera->unk204.z = 0.0f;
    camera->unk21C = 0.0f;
    camera->unk220 = 0.0f;
    camera->unk20 = 0.0f;
    camera->unk14 = 0.0f;
    camera->unk1C = 1;
    camera->unk78 = 0.0f;
    camera->unk7C = 0.0f;
    camera->unk1B4 = 6.0f;
    camera->unk1B8 = 6.0f;
    camera->unk22C = unkIndex;
    camera->unk1A4 = 0.0f;
    camera->unk224 = 1;
    camera->unk1114 = 1;
    camera->unk4 = 0xFFFF;
    camera->unk6 = 0;
    camera->unk148 = 0;
    camera->unkF = 0;
    camera->unk8 = 16.0f;
    camera->unk1A0 = 0.1f;
    camera->unk137C = 0;
    camera->unk108.m[3][2] = 0.0f;
    camera->unk1380 = 0.0f;
    camera->unk1374 = 6.0f;
    camera->unk1378 = 30.0f;
    uvMat4SetIdentity(&camera->unk80);
    func_802D46A4(camera, camera->unk24, camera->unk26, camera->unk28, camera->unk2A);
    func_802D45C4(camera, 1);
    D_803599D0.count = 6;
    D_803599D0.unk4[0].x = 0.0f;
    D_803599D0.unk4[0].y = 0.0f;
    D_803599D0.unk4[1].x = 5.0f;
    D_803599D0.unk4[1].y = 5.0f;
    D_803599D0.unk4[2].x = 10.0f;
    D_803599D0.unk4[2].y = 9.0f;
    D_803599D0.unk4[3].x = 15.0f;
    D_803599D0.unk4[3].y = 12.0f;
    D_803599D0.unk4[4].x = 20.0f;
    D_803599D0.unk4[4].y = 13.5f;
    D_803599D0.unk4[5].x = 25.0f;
    D_803599D0.unk4[5].y = 14.5f;
}

void func_802D3444(Camera* camera) {
    Mtx4F sp28;

    camera->unk14 += D_8034F854;
    if (camera->unk1 != 5) {
        uvMat4Copy(&sp28, &camera->unk80);
        uvMat4LocalTranslate(&sp28, camera->unk5C, camera->unk60, camera->unk64);
        func_802EAC18(&camera->unk230, camera->unk14, &sp28);
        if (camera->unkD != 0) {
            func_802EABAC(&camera->unk230, camera->unk14, &sp28);
            camera->unkD = 0;
        }
        camera->unk1AC = uvAtan2F(camera->unk80.m[0][0], camera->unk80.m[0][1]) - 1.5707963f; // almost DEG_TO_RAD(90)
        if ((camera->unk1AC - camera->unk1A8) > 1.5707964f) {                                 // matches DEG_TO_RAD(90)
            camera->unk1A8 = camera->unk1A8 + 6.2831855f;                                     // matches DEG_TO_RAD(360)
        }
        if ((camera->unk1AC - camera->unk1A8) < -1.5707964f) { // matches DEG_TO_RAD(-90)
            camera->unk1A8 -= 6.2831855f;                      // matches DEG_TO_RAD(360)
        }
        if (camera->unkC != 0) {
            camera->unk1A8 = camera->unk1AC;
            camera->unkC = 0;
        } else {
            camera->unk1A8 = func_80313AF4(camera->unk1AC, camera->unk1A8, camera->unk1B8);
        }

        if (func_802D408C(camera) != 0) {
            func_802D41D8(camera);
            return;
        }

        switch (camera->unk1) {
        case 9:
            func_802D3790(camera);
            return;
        case 0:
            func_802D3BE8(camera);
            return;
        case 1:
            func_802D3FA4(camera);
            return;
        case 3:
            func_802D4274(camera);
            return;
        case 4:
            func_802D532C(camera);
            return;
        case 7:
            func_802D532C(camera);
            return;
        case 6:
            func_802D3658(camera);
            return;
        case 8:
            func_802D559C(camera);
            break;
        }
    }
}

STATIC_FUNC void func_802D3658(Camera* camera) {
    Mtx4F sp30;
    f32 temp_fa0;

    uvMat4UnkOp6(&sp30, &camera->unk80, &camera->unk108);
    uvMat4Copy(&camera->unk108, &sp30);
    temp_fa0 = uvSqrtF(SQ(camera->unk108.m[3][0] - camera->unk80.m[3][0]) + SQ(camera->unk108.m[3][1] - camera->unk80.m[3][1]) +
                       SQ(camera->unk108.m[3][2] - camera->unk80.m[3][2])) -
               (2.0f * camera->unk54);
    if (temp_fa0 < 0.0f) {
        camera->unk108.m[3][0] += camera->unk108.m[1][0] * temp_fa0;
        camera->unk108.m[3][1] += camera->unk108.m[1][1] * temp_fa0;
        camera->unk108.m[3][2] += camera->unk108.m[1][2] * temp_fa0;
        (void)func_802D472C(camera, &camera->unk108);
    }
    if (camera->unk0 & 0x08) {
        (void)func_802D472C(camera, &camera->unk108);
    }
    if (camera->unk0 & 0x20) {
        (void)func_802D4A30(camera, &camera->unk108);
    }
    if (camera->unk0 & 0x40) {
        (void)func_802D4CA4(camera, &camera->unk108);
    }
}

STATIC_FUNC void func_802D3790(Camera* camera) {
    Vec3F spBC;
    Vec3F spB0;
    Vec3F spA4;
    Vec3F sp98;
    Vec3F sp8C;
    Mtx4F sp4C;
    f32 temp_fv1_2;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 var_fv0;

    spBC.x = camera->unk80.m[3][0];
    spBC.y = camera->unk80.m[3][1];
    spBC.z = camera->unk80.m[3][2];
    spB0.x = camera->unkC0;
    spB0.y = 0.0f;
    spB0.z = 0.0f;
    func_8034B210(spBC, spB0, &sp4C);
    sp8C.x = 0.0f;
    sp8C.z = 0.0f;
    sp8C.y = -1.0f;
    func_8034ABB0(&sp4C, &sp98, &sp8C);
    func_8034B2B0(&sp98);
    if (camera->unk137C == 0) {
        var_fv0 = camera->unkC4 * 0.9f;
        if (camera->unk1378 < var_fv0) {
            var_fv0 = camera->unk1378;
        } else if (var_fv0 < -camera->unk1378) {
            var_fv0 = -camera->unk1378;
        }
        temp_fv1_2 = camera->unk1380;
        if ((var_fv0 - temp_fv1_2) > 3.0f) {
            var_fv0 = temp_fv1_2 + 3.0f;
        } else if ((temp_fv1_2 - var_fv0) > 3.0f) {
            var_fv0 = temp_fv1_2 - 3.0f;
        }
        camera->unk1380 = var_fv0;
        spA4.z = (-uvSinF(var_fv0 * 0.0174533f) * camera->unk1374) + spBC.z; // almost DEG_TO_RAD(1)
        temp_fa1 = spA4.z - spBC.z;
        temp_fv0 = uvSqrtF(SQ(camera->unk1374) + SQ(temp_fa1));
        spA4.x = (sp98.x * temp_fv0) + spBC.x;
        spA4.y = (sp98.y * temp_fv0) + spBC.y;
        sp98.x = spBC.x - spA4.x;
        sp98.y = spBC.y - spA4.y;
        sp98.z = spBC.z - spA4.z;
        func_8034B4DC(sp98, &camera->unk108);
        camera->unk108.m[3][0] = spA4.x;
        camera->unk108.m[3][1] = spA4.y;
        camera->unk108.m[3][2] = spA4.z;
        uvMat4RotateAxis(&camera->unk108, camera->unk78 * 0.5f, 'z');
        uvMat4RotateAxis(&camera->unk108, camera->unk7C * 0.5f, 'x');
        func_802D58EC(camera, &camera->unk108);
        if (camera->unk0 & 0x08) {
            func_802D472C(camera, &camera->unk108);
        }
        if (camera->unk0 & 0x20) {
            (void)func_802D4A30(camera, &camera->unk108);
        }
        if (camera->unk0 & 0x40) {
            func_802D4CA4(camera, &camera->unk108);
        }
    } else if (camera->unk137C == 1) {
        func_8034AD6C(camera->unkC0, 0.0f, 0.0f, &camera->unk108);
        camera->unk108.m[3][0] = spBC.x;
        camera->unk108.m[3][1] = spBC.y;
        camera->unk108.m[3][2] = spBC.z;
        uvMat4LocalTranslate(&camera->unk108, camera->unk68.x, camera->unk68.y, camera->unk68.z);
        uvMat4RotateAxis(&camera->unk108, camera->unk78 * 0.5f, 'z');
        uvMat4RotateAxis(&camera->unk108, camera->unk7C * 0.5f, 'x');
    }

    temp_fv0 = uvSqrtF(SQ(camera->unk108.m[0][0]) + SQ(camera->unk108.m[0][1]) + SQ(camera->unk108.m[0][2]));
    camera->unk108.m[0][0] /= temp_fv0;
    camera->unk108.m[0][1] /= temp_fv0;
    camera->unk108.m[0][2] /= temp_fv0;

    temp_fv0 = uvSqrtF(SQ(camera->unk108.m[1][0]) + SQ(camera->unk108.m[1][1]) + SQ(camera->unk108.m[1][2]));
    camera->unk108.m[1][0] /= temp_fv0;
    camera->unk108.m[1][1] /= temp_fv0;
    camera->unk108.m[1][2] /= temp_fv0;

    temp_fv0 = uvSqrtF(SQ(camera->unk108.m[2][0]) + SQ(camera->unk108.m[2][1]) + SQ(camera->unk108.m[2][2]));
    camera->unk108.m[2][0] /= temp_fv0;
    camera->unk108.m[2][1] /= temp_fv0;
    camera->unk108.m[2][2] /= temp_fv0;
}

STATIC_FUNC void func_802D3BE8(Camera* camera) {
    Mtx4F sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 temp_fv0;
    f32 temp_fv1;
    Vec3F sp40;
    f32 temp_ft4_2;
    f32 temp_ft5_2;

    func_802EAC9C(&camera->unk230, camera->unk14 - camera->unk48, &camera->unkC8);
    sp40.x = camera->unkC8.m[2][0] * 0.3f;
    sp40.y = camera->unkC8.m[2][1] * 0.3f;
    sp40.z = (camera->unkC8.m[2][2] * 0.3f) + 0.7f;
    uvVec3Normal(&sp40, &sp40);
    func_80313E18(&sp40, &camera->unkC8);
    if (camera->unk0 & 0x01) {
        sp5C = camera->unkC8.m[3][0] - camera->unk80.m[3][0];
        sp58 = camera->unkC8.m[3][1] - camera->unk80.m[3][1];
        sp54 = camera->unkC8.m[3][2] - camera->unk80.m[3][2];
        temp_fv0 = uvSqrtF(SQ(sp5C) + SQ(sp58) + SQ(sp54));
        if (temp_fv0 > 0.0f) {
            sp5C /= temp_fv0;
            sp58 /= temp_fv0;
            sp54 /= temp_fv0;
        }

        if (temp_fv0 < camera->unk54) {
            temp_fv1 = camera->unk54 - temp_fv0;
            camera->unkC8.m[3][0] += temp_fv1 * sp5C;
            camera->unkC8.m[3][1] += temp_fv1 * sp58;
            camera->unkC8.m[3][2] += temp_fv1 * sp54;
        } else if (camera->unk58 < temp_fv0) {
            temp_fv1 = temp_fv0 - camera->unk58;
            camera->unkC8.m[3][0] -= temp_fv1 * sp5C;
            camera->unkC8.m[3][1] -= temp_fv1 * sp58;
            camera->unkC8.m[3][2] -= temp_fv1 * sp54;
        }
    }

    if (camera->unk0 & 0x02) {
        if (camera->unk1A4 < 15.0f) {
            camera->unkC8.m[3][2] += 4.0f * (1.0f - (FABS(camera->unk1A4) / 15.0f));
        }
    }

    if (camera->unk50 != 0.0f) {
        if (camera->unk50 < 0.0f) {
            camera->unk50 = 0.0f;
        } else if (camera->unk50 > 1.0f) {
            camera->unk50 = 1.0f;
        }

        sp5C = camera->unkC8.m[3][0] - camera->unk80.m[3][0];
        sp58 = camera->unkC8.m[3][1] - camera->unk80.m[3][1];
        sp54 = camera->unkC8.m[3][2] - camera->unk80.m[3][2];

        temp_ft4_2 = uvSqrtF((SQ(sp5C) + SQ(sp58)) + SQ(sp54));
        temp_ft5_2 = camera->unkC8.m[3][2];
        camera->unkC8.m[3][2] = (camera->unk50 * ((temp_ft4_2 * 0.9659283f) + temp_ft5_2)) + ((1 - camera->unk50) * temp_ft5_2);
    }

    uvMat4UnkOp6(&sp60, &camera->unk80, &camera->unkC8);
    func_802D58EC(camera, &sp60);
    if (camera->unk4C > 0.0f) {
        func_803138A0(&camera->unk108, &camera->unkC8, &sp60, camera->unk4C);
    } else {
        uvMat4Copy(&camera->unk108, &sp60);
    }
    uvMat4RotateAxis(&camera->unk108, camera->unk78 * 0.5f, 'z');
    uvMat4RotateAxis(&camera->unk108, camera->unk7C * 0.5f, 'x');
    if (func_802D472C(camera, &camera->unkC8) != 0) {
        uvMat4UnkOp6(&camera->unk108, &camera->unk80, &camera->unkC8);
    }
}

STATIC_FUNC void func_802D3FA4(Camera* camera) {
    Vec3F sp24;

    uvMat4Copy(&camera->unk108, &camera->unk80);
    uvMat4LocalTranslate(&camera->unk108, camera->unk68.x, camera->unk68.y, camera->unk68.z);
    uvMat4RotateAxis(&camera->unk108, camera->unk74, 'x');
    if (camera->unk0 & 0x04) {
        sp24.x = camera->unk108.m[2][0] * 0.2f;
        sp24.y = camera->unk108.m[2][1] * 0.2f;
        sp24.z = (camera->unk108.m[2][2] * 0.2f) + 0.8f;
        uvVec3Normal(&sp24, &sp24);
        func_80313E18(&sp24, &camera->unk108);
    }
    uvMat4RotateAxis(&camera->unk108, camera->unk78, 'z');
    uvMat4RotateAxis(&camera->unk108, camera->unk7C, 'x');
    (void)func_802D4A30(camera, &camera->unk108);
}

STATIC_FUNC s32 func_802D408C(Camera* camera) {
    f32 argX;
    f32 argY;
    f32 argZ;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 length;
    TaskOBSV* obsv;
    s32 i;
    u8 countOBSV;
    u8 tmp;

    argX = camera->unk80.m[3][0];
    argY = camera->unk80.m[3][1];
    argZ = camera->unk80.m[3][2];
    camera->unk18C = 1000000.0f;
    countOBSV = taskGetOBSV(&obsv) & 0xFF; // extra & 0xFF for matching

    for (i = 0; i < countOBSV; i++) {
        dx = obsv[i].x - argX;
        dy = obsv[i].y - argY;
        dz = obsv[i].z - argZ;
        length = uvLength3D(dx, dy, dz);
        if (length < obsv[i].unkC) {
            camera->unk18C = length;
            break;
        }
    }
    if (i < countOBSV) {
        camera->unk1 = 2;
        uvMat4SetIdentity(&camera->unk14C);
        camera->unk14C.m[3][0] = obsv[i].x;
        camera->unk14C.m[3][1] = obsv[i].y;
        camera->unk14C.m[3][2] = obsv[i].z;
        camera->unk148 = 1;
        return 1;
    }
    camera->unk148 = 0;
    return 0;
}

STATIC_FUNC void func_802D41D8(Camera* camera) {
    f32 var_fv0;

    uvMat4UnkOp6(&camera->unk108, &camera->unk80, &camera->unk14C);
    var_fv0 = (camera->unk18C * 0.02f) + 0.5f;
    if (var_fv0 < 1.0f) {
        var_fv0 = 1.0f;
    } else if (var_fv0 > 4.0f) {
        var_fv0 = 4.0f;
    }
    func_802D45C4(camera, var_fv0);
}

STATIC_FUNC void func_802D4274(Camera* camera) {
    static f32 D_80359A24;
    Mtx4F sp70; // 70:AF
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 var_fs0;

    if (camera->unkE != 0) {
        camera->unkE = 0;
        sp6C = camera->unk108.m[3][0] - camera->unk80.m[3][0];
        sp68 = camera->unk108.m[3][1] - camera->unk80.m[3][1];
        sp64 = camera->unk108.m[3][2] - camera->unk80.m[3][2];
        var_fs0 = uvSqrtF(SQ(sp6C) + SQ(sp68) + SQ(sp64));
        if (var_fs0 > 0.01f) {
            sp6C /= var_fs0;
            sp68 /= var_fs0;
            sp64 /= var_fs0;
            camera->unk194 = uvAtan2F(sp68, sp6C);
            D_80359A24 = var_fs0;
        } else {
            camera->unk194 = 0.0f;
            D_80359A24 = camera->unk190;
        }
    } else {
        camera->unk194 += camera->unk19C * D_8034F854;
        D_80359A24 = func_80313AF4(camera->unk190, D_80359A24, 1.0f);
    }
    uvMat4SetIdentity(&sp70);
    var_fs0 = camera->unk198;

    while (var_fs0 <= 1.5706216f) { // should be DEG_TO_RAD(90)
        func_803134D0(D_80359A24, camera->unk194, var_fs0, &sp6C, &sp68, &sp64);
        sp70.m[3][0] = camera->unk80.m[3][0] + sp6C;
        sp70.m[3][1] = camera->unk80.m[3][1] + sp68;
        sp70.m[3][2] = camera->unk80.m[3][2] + sp64;

        if (func_802D472C(camera, &sp70) == 0) {
            break;
        }
        if (var_fs0 == 1.5706216f) { // almost DEG_TO_RAD(90)
            break;
        }
        var_fs0 += 0.01745329f; // almost DEG_TO_RAD(1)
        if (var_fs0 < 0.0f) {
            var_fs0 = 0.0f;
        } else if (var_fs0 > 1.5706216f) { // almost DEG_TO_RAD(90)
            var_fs0 = 1.5706216f;          // almost DEG_TO_RAD(90)
        }
    }
    if (camera->unk198 < var_fs0) {
        camera->unk198 = var_fs0;
    }
    uvMat4UnkOp6(&camera->unk108, &camera->unk80, &sp70);
    func_802D4A30(camera, &camera->unk108);
}

void func_802D4514(Camera* camera) {
    f32 var_fv0;
    f32 temp;
    f32 temp3;
    f32 temp4;
    f32 temp2;
    Camera* ptr;

    var_fv0 = (camera->unk3C * 1.5f) / camera->unk20;
    temp = (var_fv0 * 1.1f) * camera->unk2C;
    temp2 = (var_fv0 * 1.1f) * camera->unk30;
    temp3 = (var_fv0 * 1.1f) * camera->unk34;
    temp4 = (var_fv0 * 1.1f) * camera->unk38;

    ptr = camera;
    ptr->unk111C.unk0 = 2;
    camera->unk111C.unk4[0].unk28.f[2] = 0.0f;
    camera->unk111C.unk4[0].unk28.f[1] = ptr->unk3C * 1.5f;
    camera->unk111C.unk4[0].unk28.f[0] = temp;
    camera->unk111C.unk4[0].unk1C.f[1] = ptr->unk3C * 1.5f;
    camera->unk111C.unk4[0].unk1C.f[0] = temp2;
    camera->unk111C.unk4[0].unk1C.f[2] = 0.0f;
    camera->unk111C.unk4[0].unk0 = 1;
    camera->unk111C.unk4[1].unk28.f[2] = temp3;
    camera->unk111C.unk4[1].unk28.f[1] = camera->unk3C * 1.5f;
    camera->unk111C.unk4[1].unk1C.f[1] = camera->unk3C * 1.5f;
    camera->unk111C.unk4[1].unk28.f[0] = 0.0f;
    camera->unk111C.unk4[1].unk1C.f[0] = 0.0f;
    camera->unk111C.unk4[1].unk1C.f[2] = temp4;
    camera->unk111C.unk4[1].unk0 = 1;
}

void func_802D45C4(Camera* camera, f32 arg1) {
    f32 temp_fv0_2;
    f32 a;
    f32 b;
    f32 d;
    f32 sp34;
    f32 e;
    f32 c;

    if (arg1 != camera->unk20) {
        if (arg1 == -1.0f) {
            arg1 = camera->unk20;
        }
        temp_fv0_2 = camera->unk3C / arg1;
        camera->unk20 = arg1;
        camera->unk1C = arg1;

        a = camera->unk2C * temp_fv0_2;
        b = camera->unk30 * temp_fv0_2;
        c = camera->unk34 * temp_fv0_2;
        d = camera->unk38 * temp_fv0_2;
        sp34 = camera->unk3C;
        e = camera->unk40;
        func_80204C94(camera->unk22C, a, b, c, d, sp34, e);
        func_802D4514(camera);
        D_8034E9E0 = sp34;
    }
}

STATIC_FUNC void func_802D46A4(Camera* camera, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    s16 temp_a1;
    s16 temp_a2;
    s16 temp_a3;
    s16 temp_v0;

    camera->unk24 = arg1;
    temp_a1 = camera->unk24;
    camera->unk26 = arg2;
    temp_a2 = camera->unk26;
    camera->unk28 = arg3;
    temp_a3 = camera->unk28;
    camera->unk2A = arg4;
    temp_v0 = camera->unk2A;
    camera->unk44 = ((temp_a2 - temp_a1) / (f32)(temp_v0 - temp_a3));
    func_80204D94(camera->unk22C, temp_a1, temp_a2, temp_a3, (s32)temp_v0);
}

s32 func_802D472C(Camera* camera, Mtx4F* arg1) {
    f32 temp_fv0;
    f32 temp_fv1;
    Vec3F sp1B4;
    Vec3F sp1A8;
    s32 temp_v0;
    s32 i;
    Unk802D472C_SP60 sp60[5];
    f32 dx; // sp5C;
    f32 dy; // var_fs0;
    f32 dz; // var_fs1;
    s32 pad3;
    f32 sp4C;

    sp4C = 1.0f;

    pad3 = camera->unk0;
    // this is weird
    if ((pad3 == 0) & 0x08) {
        return 0;
    }

    sp1A8.x = camera->unk80.m[3][0];
    sp1A8.y = camera->unk80.m[3][1];
    sp1A8.z = camera->unk80.m[3][2];

    sp1B4.x = arg1->m[3][0];
    sp1B4.y = arg1->m[3][1];
    sp1B4.z = arg1->m[3][2];

    dx = sp1B4.x - sp1A8.x;
    dy = sp1B4.y - sp1A8.y;
    dz = sp1B4.z - sp1A8.z;
    temp_fv0 = uvSqrtF(SQ(dx) + SQ(dy) + SQ(dz));

    if (temp_fv0 > 0.0f) {
        dx /= temp_fv0;
        dy /= temp_fv0;
        dz /= temp_fv0;
    }
    if (camera->unk0 & 0x10) {
        sp1A8.x += camera->unk8 * dx;
        sp1A8.y += camera->unk8 * dy;
        sp1A8.z += camera->unk8 * dz;
    }
    temp_v0 = func_802DB224((Unk802D3658_Unk1224*)&sp60, 0xD, camera->unk4, camera->unk6, &sp1A8, &sp1B4);
    if (temp_v0 == 0) {
        return 0;
    }

    for (i = 0; i < temp_v0; i++) {
        if (sp60[i].unk1C < sp4C) {
            sp4C = sp60[i].unk1C;
        }
    }

    if (sp4C != 1.0f) {
        dx = (sp1B4.x - sp1A8.x) * sp4C;
        dy = (sp1B4.y - sp1A8.y) * sp4C;
        dz = (sp1B4.z - sp1A8.z) * sp4C;
        temp_fv0 = uvSqrtF(SQ(dx) + SQ(dy) + SQ(dz));
        if (camera->unk1A0 < temp_fv0) {
            temp_fv1 = temp_fv0 - camera->unk1A0;
            dx /= temp_fv0;
            dx *= temp_fv1;
            arg1->m[3][0] = sp1A8.x + dx;
            dy /= temp_fv0;
            dy *= temp_fv1;
            arg1->m[3][1] = sp1A8.y + dy;
            dz /= temp_fv0;
            dz *= temp_fv1;
            arg1->m[3][2] = sp1A8.z + dz;
        }
    }
    return 1;
}

s32 func_802D4A30(Camera* camera, Mtx4F* arg1) {
    s32 sp2A4;
    s32 pad;
    Unk802D3658_Unk1120* temp_s2;
    Unk802D3658_Unk1228* var_s3;
    Unk802D3658_Unk1224 sp154;
    Vec3F sp148;
    Vec3F sp13C;
    Vec3F sp130;
    Mtx4F spF0; // F0:12F
    Mtx4F spB0; // B0:EF
    Mtx4F sp70; // 70:AF
    s32 i;

    sp2A4 = func_802DB050(&camera->unk111C, &camera->unk1224, camera->unk4, camera->unk6, arg1);
    if (sp2A4 == 0) {
        return 0;
    }
    uvMat4Copy(&spF0, arg1);
    spF0.m[3][1] = 0.0f;
    spF0.m[3][0] = 0.0f;
    spF0.m[3][2] = 0.0f;
    uvMat4InvertTranslationRotation(&spB0, &spF0);

    for (i = 0; i < sp2A4; i++) {
        var_s3 = &camera->unk1224.unk4[i];
        temp_s2 = &camera->unk111C.unk4[var_s3->unk0];
        func_802DBE64(&camera->unk111C, &camera->unk1224, i, &spB0);
        func_802DCA5C(&temp_s2->unk28, &temp_s2->unk1C, &var_s3->unk28, &var_s3->unk34, &sp148);
        sp13C.x = arg1->m[3][0] + (arg1->m[1][0] * 1.5f * camera->unk3C);
        sp13C.y = arg1->m[3][1] + (arg1->m[1][1] * 1.5f * camera->unk3C);
        sp13C.z = arg1->m[3][2] + (arg1->m[1][2] * 1.5f * camera->unk3C);
        uvMat4Copy(&sp70, arg1);
        uvMat4LocalTranslate(&sp70, sp148.x, sp148.y, sp148.z);
        sp130.x = sp70.m[3][0] + (arg1->m[1][0] * 1.5f * camera->unk3C);
        sp130.y = sp70.m[3][1] + (arg1->m[1][1] * 1.5f * camera->unk3C);
        sp130.z = sp70.m[3][2] + (arg1->m[1][2] * 1.5f * camera->unk3C);
        (void)func_802DB224(&sp154, 9, camera->unk4, camera->unk6, &sp13C, &sp130);
        if (sp154.unk0 > 0) {
            return -1;
        }
        uvMat4LocalTranslate(arg1, sp148.x, sp148.y, sp148.z);
    }

    return 1;
}

STATIC_FUNC s32 func_802D4CA4(Camera* camera, Mtx4F* arg1) {
    Mtx4F sp30;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv1;

    if ((D_8034F850 - camera->unk18) > 0.5f) {
        temp_fv0 = arg1->m[3][0] - camera->unk80.m[3][0];
        temp_fv1 = arg1->m[3][1] - camera->unk80.m[3][1];
        temp_fa1 = arg1->m[3][2] - camera->unk80.m[3][2];
        if (camera->unk8 < uvSqrtF(SQ(temp_fv0) + SQ(temp_fv1) + SQ(temp_fa1))) {
            return 0;
        }
        camera->unk18 = D_8034F850;
    }
    uvMat4SetIdentity(&sp30);
    sp30.m[3][0] = camera->unk80.m[3][0] + (camera->unk80.m[1][0] * (4.0f * camera->unk8));
    sp30.m[3][1] = camera->unk80.m[3][1] + (camera->unk80.m[1][1] * (4.0f * camera->unk8));
    sp30.m[3][2] = camera->unk80.m[3][2] + (camera->unk80.m[1][2] * (4.0f * camera->unk8));
    uvMat4UnkOp6(arg1, &camera->unk80, &sp30);
    (void)func_802D472C(camera, arg1);
    return 1;
}

void func_802D4DE8(Camera* camera, u8 arg1) {
    Mtx4F sp20;
    if (!arg1) {
        camera->unk148 = 0;
        camera->unkC = 1;
        camera->unkD = 1;
        camera->unk50 = 0.0f;
        camera->unk21C = 0.0f;
        camera->unk220 = 0.0f;
        camera->unk200 = 0.0f;
        camera->unk204.x = 0.0f;
        camera->unk204.y = 0.0f;
        camera->unk204.z = 0.0f;
        camera->unk2 = camera->unk1;
        camera->unk18 = -1.0f;
        camera->unk1A0 = 0.1f;
        camera->unk1FC = -100.0f;
        uvMat4Copy(&sp20, &camera->unk80);
        uvMat4LocalTranslate(&sp20, camera->unk5C, camera->unk60, camera->unk64);
        func_802EABAC(&camera->unk230, 0.0f, &sp20);
        uvMat4Copy(&sp20, &camera->unk1BC);
        camera->unk1114 = 1;
        camera->unkF++;
    }
}

void func_802D4ECC(Camera* camera, Mtx4F* arg1) {
    f32 z;
    f32 x;
    f32 y;
    s32 i;
    Unk802D3658_Unk230_Unk0* arr;

    x = arg1->m[3][0] - camera->unk80.m[3][0];
    y = arg1->m[3][1] - camera->unk80.m[3][1];
    z = arg1->m[3][2] - camera->unk80.m[3][2];

    arr = camera->unk230.unk0;
    for (i = 0; i < ARRAY_COUNT(camera->unk230.unk0); i++) {
        arr[i].unk0.m[3][0] += x;
        arr[i].unk0.m[3][1] += y;
        arr[i].unk0.m[3][2] += z;
    }

    camera->unkC8.m[3][0] += x;
    camera->unkC8.m[3][1] += y;
    camera->unkC8.m[3][2] += z;

    uvMat4Copy(&camera->unk80, arg1);
}

void func_802D50D0(Camera* camera) {
    f32 var_fv1;
    f32 var_ft4;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_4;
    f32 a, b, c, d, e;
    f32 temp_fv1;

    var_ft4 = 3.0f;
    if ((camera->unk1 == 5) || (D_80362690->state != GAME_STATE_TEST_UPDATE)) {
        if (D_8034E9E4 != 0) {
            temp_fv0 = 1.0f / camera->unk20;
            a = camera->unk2C * temp_fv0;
            b = camera->unk30 * temp_fv0;
            c = camera->unk34 * temp_fv0;
            d = camera->unk38 * temp_fv0;
            e = camera->unk40;
            func_80204C94(camera->unk22C, a, b, c, d, 1.0f, e);
            D_8034E9E0 = 1.0f;
            D_8034E9E4 = 0;
        }
    } else {
        if ((D_80362690->terraId == 2) || (D_80362690->terraId == 8)) {
            var_ft4 = 1.0f;
        }
        if (camera->unk1 == 1) {
            var_fv1 = 3.0f;
        } else if (camera->unk1 == 3) {
            var_fv1 = 0.5f;
        } else {
            temp_fv0_2 = camera->unk108.m[3][0] - camera->unk80.m[3][0];
            temp_fv1 = camera->unk108.m[3][1] - camera->unk80.m[3][1];
            temp_fa1 = camera->unk108.m[3][2] - camera->unk80.m[3][2];
            var_fv1 = uvSqrtF(SQ(temp_fv0_2) + SQ(temp_fv1) + SQ(temp_fa1)) - camera->unk8;
        }
        if (camera->unk228 < var_fv1) {
            var_fv1 = camera->unk228;
        }
        if (var_ft4 < var_fv1) {
            var_fv1 = var_ft4;
        }
        if (var_fv1 < 0.5f) {
            var_fv1 = 0.5f;
        }
        if (!(var_fv1 < (D_8034E9E0 + 0.1f)) || !((D_8034E9E0 - 0.1f) < var_fv1)) {
            temp_fv0_4 = var_fv1 / camera->unk20;
            a = camera->unk2C * temp_fv0_4;
            b = camera->unk30 * temp_fv0_4;
            c = camera->unk34 * temp_fv0_4;
            d = camera->unk38 * temp_fv0_4;
            e = camera->unk40;
            func_80204C94(camera->unk22C, a, b, c, d, var_fv1, e);
            D_8034E9E0 = var_fv1;
            D_8034E9E4 = 1;
        }
    }
}

// func_802D532C does not initialize sp30, sp34, sp38
#if defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsometimes-uninitialized"
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif
STATIC_FUNC void func_802D532C(Camera* camera) {
    Mtx4F sp80; // 80:BF
    Mtx4F sp40; // 40:7F
    f32 var_fa0;
    s32 sp38;
    s32 sp34;
    s32 sp30;
    f32 var_fa0_2;

    uvMat4SetIdentity(&sp80);
    sp80.m[3][0] = camera->unk80.m[3][0];
    sp80.m[3][1] = camera->unk80.m[3][1];
    sp80.m[3][2] = camera->unk80.m[3][2];
    if (camera->unk1AC < camera->unk1A8) {
        var_fa0 = camera->unk1A8 - camera->unk1AC;
    } else {
        var_fa0 = -(camera->unk1A8 - camera->unk1AC);
    }
    if (var_fa0 < 0.005f) {
        var_fa0_2 = camera->unk1AC;
    } else {
        var_fa0_2 = camera->unk1A8;
    }
    uvMat4RotateAxis(&sp80, -var_fa0_2, 'z');
    uvMat4RotateAxis(&sp80, -camera->unk1B0, 'x');
    uvMat4LocalTranslate(&sp80, 0.0f, -camera->unk1B4, 0.0f);
    if (camera->unk0 & 0x08) {
        sp38 = func_802D472C(camera, &sp80);
    }
    if (camera->unk0 & 0x20) {
        sp34 = func_802D4A30(camera, &sp80);
    }
    if ((camera->unk0 & 0x40) && (sp34 != -1)) {
        sp30 = func_802D4CA4(camera, &sp80);
    }
    if (sp34 == -1) {
        camera->unk1FC = D_8034F850;
    }
    if ((D_8034F850 - camera->unk1FC) < 2.0f) {
        uvMat4Copy(&sp80, &camera->unk1BC);
    }
    if ((sp38 == 0) && (sp34 == 0) && (sp30 == 0)) {
        uvMat4Copy(&camera->unk1BC, &sp80);
    }
    if (camera->unk1 == 7) {
        uvMat4Copy(&sp40, &camera->unk80);
        sp40.m[3][0] = camera->unk1368;
        sp40.m[3][1] = camera->unk136C;
        sp40.m[3][2] = camera->unk1370;
        uvMat4UnkOp6(&camera->unk108, &sp40, &sp80);
    } else {
        uvMat4UnkOp6(&camera->unk108, &camera->unk80, &sp80);
    }
    uvMat4RotateAxis(&camera->unk108, camera->unk78 * 0.5f, 'z');
    uvMat4RotateAxis(&camera->unk108, camera->unk7C * 0.5f, 'x');
    func_802D58EC(camera, &camera->unk108);
}
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif

STATIC_FUNC void func_802D559C(Camera* camera) {
    Mtx4F sp48; // 48:87
    f32 temp_fa0;
    f32 temp_fa0_2;
    f32 temp_fv0;
    f32 tmpX;
    f32 tmpY;
    f32 tmpZ;
    s32 temp_v0;

    if ((D_8034F850 - camera->unk200) > 3.0f) {
        temp_fv0 = uvVec3Len(&camera->unk204);
        if (temp_fv0 > 0.0f) {
            temp_fa0 = (temp_fv0 * 0.5f) * 3.0f;
            if (temp_fa0 < 10.0f) {
                temp_fa0 = 10.0f;
            } else if (temp_fa0 > 500.0f) {
                temp_fa0 = 500.0f;
            }
            camera->unk210.x = camera->unk80.m[3][0] + ((camera->unk204.x / temp_fv0) * temp_fa0);
            camera->unk210.y = camera->unk80.m[3][1] + ((camera->unk204.y / temp_fv0) * temp_fa0);
            camera->unk210.z = camera->unk80.m[3][2] + ((camera->unk204.z / temp_fv0) * temp_fa0);
            if (demoRandF() > 0.5f) {
                camera->unk210.x += 2.0f * camera->unk80.m[0][0];
                camera->unk210.y += 2.0f * camera->unk80.m[0][1];
            } else {
                camera->unk210.x -= 2.0f * camera->unk80.m[0][0];
                camera->unk210.y -= 2.0f * camera->unk80.m[0][1];
            }
            camera->unk200 = D_8034F850;
        } else {
            camera->unk210.x = camera->unk80.m[3][0] + (camera->unk108.m[1][0] * 10.0f);
            camera->unk210.y = camera->unk80.m[3][1] + (camera->unk108.m[1][1] * 10.0f);
            camera->unk210.z = camera->unk80.m[3][2] + (camera->unk108.m[1][2] * 10.0f);
        }
    }
    uvMat4SetIdentity(&sp48);
    sp48.m[3][0] = camera->unk210.x;
    sp48.m[3][1] = camera->unk210.y;
    sp48.m[3][2] = camera->unk210.z;
    tmpX = sp48.m[3][0] - camera->unk80.m[3][0];
    tmpY = sp48.m[3][1] - camera->unk80.m[3][1];
    tmpZ = sp48.m[3][2] - camera->unk80.m[3][2];
    temp_fa0_2 = uvSqrtF(SQ(tmpX) + SQ(tmpY) + SQ(tmpZ));
    temp_fa0_2 = 0.02f * temp_fa0_2 + 0.5f;
    if (temp_fa0_2 < 1.0f) {
        temp_fa0_2 = 1.0f;
    } else if (temp_fa0_2 > 4.0f) {
        temp_fa0_2 = 4.0f;
    }
    func_802D45C4(camera, temp_fa0_2);
    uvMat4UnkOp6(&camera->unk108, &camera->unk80, &sp48);
    temp_v0 = func_802D472C(camera, &sp48);
    if (temp_v0 != 0) {
        camera->unk210.z += 2.0f;
        sp48.m[3][2] += 2.0f;
        uvMat4UnkOp6(&camera->unk108, &camera->unk80, &sp48);
    }
}

void func_802D5884(Camera* camera, u8 arg1) {
    if (arg1 != camera->unk1) {
        camera->unk2 = camera->unk1;
        camera->unk1 = arg1;
        if (arg1 == 3) {
            camera->unk198 = 0.52359873f; // almost DEG_TO_RAD(30)
            camera->unk194 = uvAtan2F(camera->unk80.m[0][0], camera->unk80.m[0][1]);
            camera->unkE = 1;
        }
    }
}

STATIC_FUNC void func_802D58EC(Camera* camera, Mtx4F* arg1) {
    Mtx4F sp88; // 88:C7
    Mtx4F sp48; // 48:87
    Vec3F sp3C;
    Vec3F sp30;
    f32 var_fa0;

    env_802E1754(arg1->m[3][0], arg1->m[3][1], arg1->m[3][2], &sp3C);
    uvMat4Copy(&sp88, arg1);
    sp88.m[3][0] = sp88.m[3][1] = sp88.m[3][2] = 0.0f;

    uvMat4InvertTranslationRotation(&sp48, &sp88);
    uvMat4LocalToWorld(&sp48, &sp30, &sp3C);

    var_fa0 = func_80313F08(&D_803599D0, FABS(2.5f * sp30.x)) * camera->unk224;
    if (sp30.x < 0.0f) {
        var_fa0 = -var_fa0;
    }
    camera->unk21C = func_80313AF4(var_fa0, camera->unk21C, 1.0f);
    uvMat4RotateAxis(arg1, camera->unk21C * 0.01745329f, 'z'); // almost DEG_TO_RAD(1)

    var_fa0 = func_80313F08(&D_803599D0, FABS(2.5f * sp30.z)) * (camera->unk224 * 0.5f);
    if (sp30.z > 0.0f) {
        var_fa0 = -var_fa0;
    }
    camera->unk220 = func_80313AF4(var_fa0, camera->unk220, 1.0f);
    uvMat4RotateAxis(arg1, camera->unk220 * 0.01745329f, 'x'); // almost DEG_TO_RAD(1)
}
