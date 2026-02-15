#include "common.h"
#include <uv_math.h>
#include <uv_matrix.h>
#include <uv_vector.h>
#include <uv_model.h>
#include <uv_graphics.h>
#include "code_D1ED0.h"
#include "kernel/code_1AF80.h"

f32 func_8034A9A0(f32 arg0, f32 arg1) {
    f32 temp_fv0;

    temp_fv0 = uvSqrtF(SQ(arg0) + SQ(arg1));
    arg0 /= temp_fv0;
    arg1 /= temp_fv0;
    return uvAtan2F(arg0, arg1);
}

void func_8034A9E8(Vec3F arg0, Vec3F* arg3) {
    Vec3F sp5C;
    Mtx4F sp1C;

    arg3->x = -(func_8034A9A0(arg0.x, arg0.y) * RADIAN_TO_ANGLE_FACTOR);
    func_8034AD6C(-arg3->x, 0.0f, 0.0f, &sp1C);
    func_8034ABB0(&sp1C, &sp5C, &arg0);
    arg3->y = func_8034A9A0(sp5C.f[2], sp5C.f[1]) * RADIAN_TO_ANGLE_FACTOR;
    arg3->z = 0.0f;
}

f32 func_8034AA80(f32 arg0) {
    return func_8034A9A0(uvSqrtF(1.0f - (arg0 * arg0)), arg0) * RADIAN_TO_ANGLE_FACTOR;
}

void func_8034AACC(Vec3F* arg0, Vec3F arg1) {
    Vec3F sp24;
    f32 sp20;
    f32 sp1C;

    sp20 = uvSinF(arg0->x * 0.0174533f); // almost DEG_TO_RAD(1)
    sp1C = uvCosF(arg0->x * 0.0174533f); // almost DEG_TO_RAD(1)
    sp24.f[0] = -sp20;
    sp24.f[1] = sp1C;
    sp24.f[2] = 0.0f;
    arg0->y = func_8034AA80(uvVec3Dot(&sp24, &arg1)) - 90.0f;
    sp24.f[0] = sp1C;
    sp24.f[1] = sp20;
    sp24.f[2] = 0.0f;
    arg0->z = 90.0f - func_8034AA80(uvVec3Dot(&sp24, &arg1));
}

void func_8034ABB0(Mtx4F* arg0, Vec3F* arg1, Vec3F* arg2) {
    f32 x = arg2->f[0];
    f32 y = arg2->f[1];
    f32 z = arg2->f[2];
    arg1->f[0] = (x * arg0->m[0][0]) + (y * arg0->m[1][0]) + (z * arg0->m[2][0]);
    arg1->f[1] = (x * arg0->m[0][1]) + (y * arg0->m[1][1]) + (z * arg0->m[2][1]);
    arg1->f[2] = (x * arg0->m[0][2]) + (y * arg0->m[1][2]) + (z * arg0->m[2][2]);
}

void func_8034AC34(Mtx4F* arg0, Vec4F* arg1, Vec4F* arg2) {
    f32 x = arg2->f[0];
    f32 y = arg2->f[1];
    f32 z = arg2->f[2];
    f32 w = arg2->f[3];
    arg1->f[0] = (x * arg0->m[0][0]) + (y * arg0->m[1][0]) + (z * arg0->m[2][0]) + (w * arg0->m[3][0]);
    arg1->f[1] = (x * arg0->m[0][1]) + (y * arg0->m[1][1]) + (z * arg0->m[2][1]) + (w * arg0->m[3][1]);
    arg1->f[2] = (x * arg0->m[0][2]) + (y * arg0->m[1][2]) + (z * arg0->m[2][2]) + (w * arg0->m[3][2]);
    arg1->f[3] = (x * arg0->m[0][3]) + (y * arg0->m[1][3]) + (z * arg0->m[2][3]) + (w * arg0->m[3][3]);
}

s32 func_8034AD14(f32 arg0) {
    f32 temp_fv0;

    temp_fv0 = (s32)arg0;
    if ((arg0 - temp_fv0) > 0.5f) {
        return (s32)temp_fv0 + 1;
    }
    return temp_fv0;
}

void func_8034AD6C(f32 arg0, f32 arg1, f32 arg2, Mtx4F* arg3) {
    f32 var_fs2;
    f32 var_fs3;
    f32 var_fa1;
    f32 sp5C;
    f32 var_fs1;
    f32 sp50;
    f32 var_ft4;
    f32 var_ft5;

    if (arg0 == 0.0f) {
        var_fs2 = 1.0f;
        var_fs3 = 0.0f;
    } else {
        var_fs3 = uvSinF(arg0 * 0.0174533f); // almost DEG_TO_RAD(1)
        var_fs2 = uvCosF(arg0 * 0.0174533f); // almost DEG_TO_RAD(1)
    }

    if (arg1 == 0.0f) {
        var_fa1 = 1.0f;
        var_fs1 = 0.0f;
    } else {
        var_fs1 = uvSinF(arg1 * 0.0174533f); // almost DEG_TO_RAD(1)
        var_fa1 = uvCosF(arg1 * 0.0174533f); // almost DEG_TO_RAD(1)
    }

    if (arg2 == 0.0f) {
        sp5C = 1.0f;
        sp50 = 0.0f;
        var_ft4 = sp50 * var_fs1;
        var_ft5 = sp5C * var_fs1;
    } else {
        sp50 = uvSinF(arg2 * 0.0174533f); // almost DEG_TO_RAD(1)
        sp5C = uvCosF(arg2 * 0.0174533f); // almost DEG_TO_RAD(1)
        var_ft4 = sp50 * var_fs1;
        var_ft5 = sp5C * var_fs1;
    }

    arg3->m[0][0] = (sp5C * var_fs2) - (var_ft4 * var_fs3);
    arg3->m[1][0] = -var_fa1 * var_fs3;
    arg3->m[2][0] = (sp50 * var_fs2) + (var_ft5 * var_fs3);
    arg3->m[3][0] = 0.0f;
    arg3->m[0][1] = (sp5C * var_fs3) + (var_ft4 * var_fs2);
    arg3->m[1][1] = var_fa1 * var_fs2;
    arg3->m[2][1] = (sp50 * var_fs3) - (var_ft5 * var_fs2);
    arg3->m[3][1] = 0.0f;
    arg3->m[0][2] = -sp50 * var_fa1;
    arg3->m[1][2] = var_fs1;
    arg3->m[2][2] = sp5C * var_fa1;
    arg3->m[3][2] = 0.0f;
    arg3->m[0][3] = 0.0f;
    arg3->m[1][3] = 0.0f;
    arg3->m[2][3] = 0.0f;
    arg3->m[3][3] = 1.0f;
}

f32 func_8034AF48(Vec3F arg0, Vec3F arg3) {
    return SQ(arg0.x - arg3.x) + SQ(arg0.y - arg3.y) + SQ(arg0.z - arg3.z);
}

void func_8034AF94(Mtx4F* arg0, Vec3F* arg1, Vec3F* arg2) {
    Vec3F sp84;
    Vec3F sp78;
    Vec3F sp6C;
    Mtx4F sp2C;

    sp78.f[0] = 0.0f;
    sp78.f[1] = 1.0f;
    sp78.f[2] = 0.0f;
    func_8034ABB0(arg0, &sp84, &sp78);
    arg2->x = -(func_8034A9A0(sp84.x, sp84.y) * RADIAN_TO_ANGLE_FACTOR);
    func_8034AD6C(-arg2->x, 0.0f, 0.0f, &sp2C);
    func_8034ABB0(&sp2C, &sp6C, &sp84);
    arg2->y = func_8034A9A0(sp6C.z, sp6C.y) * RADIAN_TO_ANGLE_FACTOR;
    sp78.f[0] = 1.0f;
    sp78.f[1] = 0.0f;
    sp78.f[2] = 0.0f;
    func_8034ABB0(arg0, &sp84, &sp78);
    func_8034ABB0(&sp2C, &sp6C, &sp84);
    func_8034AD6C(0.0f, -arg2->y, 0.0f, &sp2C);
    func_8034ABB0(&sp2C, &sp84, &sp6C);
    arg2->z = -(func_8034A9A0(sp84.z, sp84.x) * RADIAN_TO_ANGLE_FACTOR);
    arg1->x = arg0->m[3][0];
    arg1->y = arg0->m[3][1];
    arg1->z = arg0->m[3][2];
    while (arg2->x < 0.0f) {
        arg2->x += 360.0f;
    }
    while (arg2->x >= 360.0f) {
        arg2->x -= 360.0f;
    }
    while (arg2->y < 0.0f) {
        arg2->y += 360.0f;
    }
    while (arg2->y >= 360.0f) {
        arg2->y -= 360.0f;
    }
    while (arg2->z < 0.0f) {
        arg2->z += 360.0f;
    }
    while (arg2->z >= 360.0f) {
        arg2->z -= 360.0f;
    }
}

void func_8034B210(Vec3F arg0, Vec3F arg3, Mtx4F* arg6) {
    func_8034AD6C(arg3.x, arg3.y, arg3.z, arg6);
    arg6->m[3][0] = arg0.x;
    arg6->m[3][1] = arg0.y;
    arg6->m[3][2] = arg0.z;
}

void func_8034B268(Vec3F arg0, Vec3F arg3, Vec3F* arg6) {
    arg6->x = arg0.x - arg3.x;
    arg6->y = arg0.y - arg3.y;
    arg6->z = arg0.z - arg3.z;
}

f32 func_8034B2B0(Vec3F* arg0) {
    f32 temp_fv0 = uvSqrtF(SQ(arg0->x) + SQ(arg0->y) + SQ(arg0->z));
    if (temp_fv0 > 0.0f) {
        arg0->f[0] *= 1.0f / temp_fv0;
        arg0->f[1] *= 1.0f / temp_fv0;
        arg0->f[2] *= 1.0f / temp_fv0;
    } else {
        arg0->f[0] = arg0->f[1] = arg0->f[2] = 0.0f;
    }
    return temp_fv0;
}

void func_8034B354(s32 arg0, Vec3F arg1, Vec3F* arg4) {
    Mtx4F sp108;
    Mtx4F spC8;
    Mtx4F sp88;
    Mtx4F sp48;
    Vec4F sp38;
    Vec4F sp28;
    Vec3F sp1C;

    func_80205724(arg0, 2, &spC8);
    func_80205724(arg0, 3, &sp108);
    uvMat4SetIdentity(&sp88);
    uvMat4RotateAxis(&sp88, -1.570797f, 'x');
    uvMat4Mul(&sp48, &sp88, &spC8);
    uvMat4Mul(&sp88, &sp108, &sp48);
    sp38.f[0] = arg1.x;
    sp38.f[1] = arg1.y;
    sp38.f[2] = arg1.z;
    sp38.f[3] = 1.0f;
    func_8034AC34(&sp88, &sp28, (Vec4F*)&sp38);
    sp1C.f[0] = sp28.f[0] / sp28.f[3];
    sp1C.f[1] = sp28.f[1] / sp28.f[3];
    arg4->x = 160.0f * (sp1C.f[0] + 1.0f);
    arg4->y = 120.0f * (sp1C.f[1] + 1.0f);
    arg4->z = sp28.f[2];
}

s32 func_8034B464(s32 arg0) {
    s32 sp1C;

    sp1C = func_8021EFF0();
    if (sp1C == 0xFF) {
        return 0xFF;
    }

    if (arg0 == 2 || arg0 == 4 || arg0 == 6) {
        if (uvModelGet(sp1C, arg0) == 0) {
            uvModelGet(sp1C, 0xFF);
            return 0xFF;
        }
    }

    return sp1C;
}

void func_8034B4DC(Vec3F arg0, Mtx4F* arg3) {
    Mtx4F sp58;
    Vec3F sp4C;
    Vec3F sp40;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 sp34;
    f32 sp30;

    sp40.f[0] = arg0.x;
    sp40.f[1] = arg0.y;
    sp40.f[2] = arg0.z;
    func_8034B2B0(&sp40);
    temp_fs0 = -sp40.f[0];
    temp_fs1 = sp40.f[1];
    uvMat4SetIdentity(&sp58);
    sp58.m[0][0] = temp_fs1;
    sp58.m[0][1] = -temp_fs0;
    sp58.m[1][0] = temp_fs0;
    sp58.m[1][1] = temp_fs1;
    func_8034ABB0(&sp58, &sp4C, &arg0);
    sp4C.f[0] = 0.0f;
    func_8034B2B0(&sp4C);
    sp34 = sp4C.f[2];
    sp30 = sp4C.f[1];
    uvMat4SetIdentity(arg3);
    arg3->m[0][0] = temp_fs1;
    arg3->m[0][1] = temp_fs0;
    arg3->m[1][0] = -sp30 * temp_fs0;
    arg3->m[1][1] = sp30 * temp_fs1;
    arg3->m[2][0] = sp34 * temp_fs0;
    arg3->m[2][1] = -sp34 * temp_fs1;
    arg3->m[1][2] = sp34;
    arg3->m[2][2] = sp30;
}
