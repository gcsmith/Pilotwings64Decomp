#include "common.h"
#include <uv_graphics.h>
#include <uv_math.h>
#include <uv_matrix.h>
#include "code_9A960.h"
#include "task.h"

f32 D_8034F850 = 0.0f;          // current time
f32 D_8034F854 = 0.1000000015f; // actual time since last frame
s32 D_8034F858 = 0;             // frame counter

// cartesian to spherical
void func_80313430(f32 x, f32 y, f32 z, f32* rho, f32* theta, f32* phi) {
    f32 x2, y2, z2;
    f32 sp20;

    x2 = SQ(x);
    y2 = SQ(y);
    z2 = SQ(z);
    sp20 = uvSqrtF(x2 + y2);
    *rho = uvSqrtF(x2 + y2 + z2);
    *theta = uvAtan2F(y / *rho, x / *rho);
    *phi = uvAtan2F(z / *rho, sp20 / *rho);
}

// spherical to cartesian
void func_803134D0(f32 rho, f32 theta, f32 phi, f32* x, f32* y, f32* z) {
    f32 temp1;

    temp1 = uvCosF(theta);
    *x = uvCosF(phi) * (rho * temp1);
    temp1 = uvSinF(theta);
    *y = uvCosF(phi) * (rho * temp1);
    *z = uvSinF(phi) * rho;
}

// gets translation and rotation parameters from matrix
void func_80313570(Mtx4F* mat, f32* tx, f32* ty, f32* tz, f32* rz, f32* rx, f32* ry) {
    *rz = uvAtan2F(mat->m[0][1], mat->m[0][0]);
    *rx = -uvAtan2F(mat->m[1][2], uvSqrtF(SQ(mat->m[1][0]) + SQ(mat->m[1][1])));
    *ry = -uvAtan2F(mat->m[0][2], uvSqrtF(SQ(mat->m[0][0]) + SQ(mat->m[0][1])));
    *tx = mat->m[3][0];
    *ty = mat->m[3][1];
    *tz = mat->m[3][2];
}

// initializes matrix with given translation and rotation
void func_80313640(f32 tx, f32 ty, f32 tz, f32 rz, f32 rx, f32 ry, Mtx4F* mat) {
    uvMat4SetIdentity(mat);
    uvMat4RotateAxis(mat, rz, 'z');
    uvMat4RotateAxis(mat, rx, 'x');
    uvMat4RotateAxis(mat, ry, 'y');
    mat->m[3][0] = tx;
    mat->m[3][1] = ty;
    mat->m[3][2] = tz;
}

// create matrix from quaternion and position
void func_803136C4(Unk803136C4_Arg0* quat, Mtx4F* mtx) {
    f32 tx;
    f32 ty;
    f32 tz;
    f32 qx;
    f32 qy;
    f32 qz;
    f32 qw;

    tx = quat->pos.x, ty = quat->pos.y, tz = quat->pos.z;
    qx = quat->quat.x, qy = quat->quat.y, qz = quat->quat.z, qw = quat->quat.w;

    mtx->m[0][0] = 1.0f - (2.0f * (SQ(qy) + SQ(qz)));
    mtx->m[0][1] = 2.0f * ((qx * qy) - (qz * qw));
    mtx->m[0][2] = 2.0f * ((qz * qx) + (qy * qw));
    mtx->m[0][3] = 0.0f;

    mtx->m[1][0] = 2.0f * ((qx * qy) + (qz * qw));
    mtx->m[1][1] = 1.0f - (2.0f * (SQ(qz) + SQ(qx)));
    mtx->m[1][2] = 2.0f * ((qy * qz) - (qx * qw));
    mtx->m[1][3] = 0.0f;

    mtx->m[2][0] = 2.0f * ((qz * qx) - (qy * qw));
    mtx->m[2][1] = 2.0f * ((qy * qz) + (qx * qw));
    mtx->m[2][2] = 1.0f - (2.0f * (SQ(qy) + SQ(qx)));
    mtx->m[2][3] = 0.0f;

    mtx->m[3][0] = tx;
    mtx->m[3][1] = ty;
    mtx->m[3][2] = tz;
    mtx->m[3][3] = 1.0f;
}

f32 func_8031385C(Mtx4F* arg0, Mtx4F* arg1) {
    f32 dx = arg0->m[3][0] - arg1->m[3][0];
    f32 dy = arg0->m[3][1] - arg1->m[3][1];
    f32 dz = arg0->m[3][2] - arg1->m[3][2];
    return uvLength3D(dx, dy, dz);
}

void func_803138A0(Mtx4F* arg0, Mtx4F* arg1, Mtx4F* arg2, f32 arg3) {
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    Vec3F sp44;
    Vec3F sp38;
    Vec3F sp2C;

    sp5C = 1.0 - arg3;
    sp58 = (sp5C * arg1->m[3][0]) + (arg2->m[3][0] * arg3);
    sp54 = (sp5C * arg1->m[3][1]) + (arg2->m[3][1] * arg3);
    sp50 = (sp5C * arg1->m[3][2]) + (arg2->m[3][2] * arg3);

    sp44.x = (sp5C * arg1->m[1][0]) + (arg2->m[1][0] * arg3);
    sp44.y = (sp5C * arg1->m[1][1]) + (arg2->m[1][1] * arg3);
    sp44.z = (sp5C * arg1->m[1][2]) + (arg2->m[1][2] * arg3);
    uvVec3Normal(&sp44, &sp44);

    sp38.x = (sp5C * arg1->m[2][0]) + (arg2->m[2][0] * arg3);
    sp38.y = (sp5C * arg1->m[2][1]) + (arg2->m[2][1] * arg3);
    sp38.z = (sp5C * arg1->m[2][2]) + (arg2->m[2][2] * arg3);
    uvVec3Normal(&sp38, &sp38);

    uvVec3Cross(&sp2C, &sp44, &sp38);
    uvVec3Normal(&sp2C, &sp2C);
    uvVec3Cross(&sp44, &sp38, &sp2C);
    uvVec3Normal(&sp44, &sp44);
    uvVec3Cross(&sp38, &sp2C, &sp44);
    uvVec3Normal(&sp38, &sp38);

    arg0->m[0][0] = sp2C.x;
    arg0->m[0][1] = sp2C.y;
    arg0->m[0][2] = sp2C.z;
    arg0->m[0][3] = 0.0f;
    arg0->m[1][0] = sp44.x;
    arg0->m[1][1] = sp44.y;
    arg0->m[1][2] = sp44.z;
    arg0->m[1][3] = 0.0f;
    arg0->m[2][0] = sp38.x;
    arg0->m[2][1] = sp38.y;
    arg0->m[2][2] = sp38.z;
    arg0->m[2][3] = 0.0f;
    arg0->m[3][0] = sp58;
    arg0->m[3][1] = sp54;
    arg0->m[3][2] = sp50;
    arg0->m[3][3] = 1.0f;
}

f32 func_80313AF4(f32 arg0, f32 arg1, f32 arg2) {
    f32 temp_ft4;
    f32 var_fv0;

    var_fv0 = arg0 - arg1;
    if (FABS(var_fv0) < 0.00001f) {
        return arg0;
    }

    temp_ft4 = arg2 * var_fv0 * D_8034F854;
    if (FABS(var_fv0) < FABS(temp_ft4)) {
        arg1 = arg0;
    } else {
        arg1 += temp_ft4;
    }
    return arg1;
}

f32 func_80313BAC(f32 arg0, f32 arg1, f32 arg2) {
    f32 var_ft4;
    f32 var_fv0;
    f32 var_fv1_2;

    var_fv0 = arg0 - arg1;
    if (FABS(arg0 - arg1) < 0.00001f) {
        return arg0;
    }

    if (var_fv0 > 0.00f) {
        var_ft4 = arg2 * D_8034F854;
    } else {
        var_ft4 = -arg2 * D_8034F854;
    }

    if (FABS(var_fv0) < FABS(var_ft4)) {
        arg1 = arg0;
    } else {
        arg1 += var_ft4;
    }
    return arg1;
}

void func_80313C94(Vec3F* arg0, Vec3F* arg1, f32 arg2) {
    f32 sp24;
    f32 temp_fv0_2;
    f32 temp_fv1;

    sp24 = uvVec3Len(arg1);
    if (sp24 != 0.0f) {
        arg1->x = func_80313AF4(arg0->x, arg1->x, arg2);
        arg1->y = func_80313AF4(arg0->y, arg1->y, arg2);
        arg1->z = func_80313AF4(arg0->z, arg1->z, arg2);
        temp_fv0_2 = uvVec3Len(arg1);
        if (temp_fv0_2 != 0.0f) {
            temp_fv1 = sp24 / temp_fv0_2;
            arg1->x *= temp_fv1;
            arg1->y *= temp_fv1;
            arg1->z *= temp_fv1;
        }
    }
}

void func_80313D74(void) {
    f32 temp_fv0;

    temp_fv0 = uvGfxGetUnkStateF();
    if (temp_fv0 < 0.01f) {
        D_8034F854 = 0.01f;
    } else if (temp_fv0 > 0.1f) {
        D_8034F854 = 0.1f;
    } else {
        D_8034F854 = temp_fv0;
    }
    D_8034F850 += D_8034F854;
    D_8034F858 += 1;
}

void func_80313E0C(f32 arg0) {
    D_8034F850 = arg0;
}

void func_80313E18(Vec3F* arg0, Mtx4F* arg1) {
    Vec3F sp3C;
    Vec3F sp30;
    Vec3F sp24;

    uvVec3Copy(&sp3C, arg0);
    sp30.x = arg1->m[0][0];
    sp30.y = arg1->m[0][1];
    sp30.z = arg1->m[0][2];
    uvVec3Normal(&sp30, &sp30);
    uvVec3Cross(&sp24, &sp3C, &sp30);
    uvVec3Normal(&sp24, &sp24);
    uvVec3Cross(&sp30, &sp24, &sp3C);
    uvVec3Normal(&sp30, &sp30);
    arg1->m[0][0] = sp30.x;
    arg1->m[0][1] = sp30.y;
    arg1->m[0][2] = sp30.z;
    arg1->m[1][0] = sp24.x;
    arg1->m[1][1] = sp24.y;
    arg1->m[1][2] = sp24.z;
    arg1->m[2][0] = sp3C.x;
    arg1->m[2][1] = sp3C.y;
    arg1->m[2][2] = sp3C.z;
    arg1->m[0][3] = 0.0f;
    arg1->m[1][3] = 0.0f;
    arg1->m[2][3] = 0.0f;
}

f32 func_80313F08(Unk803599D0* arg0, f32 arg1) {
    Vec2F* prev;
    Vec2F* cur;
    f32 temp_fv1;
    s32 i;

    if (arg1 <= arg0->unk4[0].f[0]) {
        return arg0->unk4[0].f[1];
    }

    if (arg0->unk4[arg0->unk0 - 1].f[0] <= arg1) {
        return arg0->unk4[arg0->unk0 - 1].f[1];
    }

    for (i = 1; i < arg0->unk0 - 1; i++) {
        if (arg1 < arg0->unk4[i].f[0]) {
            break;
        }
    }
    prev = &arg0->unk4[i - 1];
    cur = &arg0->unk4[i];
    temp_fv1 = (arg1 - prev->f[0]) / (cur->f[0] - prev->f[0]);
    return (cur->f[1] * temp_fv1) + (prev->f[1] * (1.0f - temp_fv1));
}

void func_80313FD0(Unk80313FD0* arg0, f32 arg1, Vec3F* arg2) {
    Vec4F* prev;
    Vec4F* cur;
    f32 temp_fa1;
    f32 temp_fv0;
    s32 i;

    if (arg1 <= arg0->unk4[0].f[0]) {
        arg2->f[0] = arg0->unk4[0].f[1];
        arg2->f[1] = arg0->unk4[0].f[2];
        arg2->f[2] = arg0->unk4[0].f[3];
        return;
    }

    if (arg0->unk4[arg0->count - 1].f[0] <= arg1) {
        arg2->f[0] = arg0->unk4[arg0->count - 1].f[1];
        arg2->f[1] = arg0->unk4[arg0->count - 1].f[2];
        arg2->f[2] = arg0->unk4[arg0->count - 1].f[3];
    }

    for (i = 1; i < arg0->count - 1; i++) {
        if (arg1 < arg0->unk4[i].f[0]) {
            break;
        }
    }

    prev = &arg0->unk4[i - 1];
    cur = &arg0->unk4[i];
    temp_fv0 = (arg1 - prev->f[0]) / (cur->f[0] - prev->f[0]);
    temp_fa1 = 1.0f - temp_fv0;
    arg2->f[0] = (cur->f[1] * temp_fv0) + (prev->f[1] * temp_fa1);
    arg2->f[1] = (cur->f[2] * temp_fv0) + (prev->f[2] * temp_fa1);
    arg2->f[2] = (cur->f[3] * temp_fv0) + (prev->f[3] * temp_fa1);
}

s32 func_80314114(s32 arg0, s32 arg1, s32 arg2) {
    if ((arg1 & arg2) && !(arg0 & arg2)) {
        return 1;
    }
    if (!(arg1 & arg2) && (arg0 & arg2)) {
        return -1;
    }
    return 0;
}

void func_80314154(void) {
    Mtx4F sp60;
    Mtx4F sp20;

    uvGfxSetViewport(0, 0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);
    uvMat4SetOrtho(&sp60, 0.0f, SCREEN_WIDTH - 1, 0.0f, SCREEN_HEIGHT - 1);
    uvGfxMtxProjPushF(&sp60);
    uvMat4SetIdentity(&sp20);
    uvGfxMtxViewLoad(&sp20, 1);
    uvGfxStatePush();
    uvGfxSetFlags(GFX_STATE_800000);
    uvGfxClearFlags(GFX_STATE_400000 | GFX_STATE_200000);
}

void func_803141E4(void) {
    uvGfxMtxViewPop();
    uvGfxStatePop();
}

void func_8031420C(f32 arg0, f32 arg1, f32 arg2, f32* arg3, f32* arg4, f32* arg5) {
    f32 a0_frac;
    s32 a0_int;

    if (arg1 <= 0.0001f) {
        *arg3 = arg2;
        *arg4 = arg2;
        *arg5 = arg2;
        return;
    }

    if (arg0 < 0.0f) {
        arg0 += 1.0f;
    }
    if (arg0 == 1.0f) {
        arg0 = 0 /*.0f*/;
    }
    arg0 *= 6.0f;
    a0_int = (s32)arg0;
    a0_frac = arg0 - a0_int;
    switch (a0_int) {
    case 0:
        *arg3 = arg2;
        *arg4 = (1.0f - ((1.0f - a0_frac) * arg1)) * arg2;
        *arg5 = (1.0f - arg1) * arg2;
    default:
        break;
    case 1:
        *arg3 = (1.0f - (arg1 * a0_frac)) * arg2;
        *arg4 = arg2;
        *arg5 = (1.0f - arg1) * arg2;
        break;
    case 2:
        *arg3 = (1.0f - arg1) * arg2;
        *arg4 = arg2;
        *arg5 = (1.0f - ((1.0f - a0_frac) * arg1)) * arg2;
        break;
    case 3:
        *arg3 = (1.0f - arg1) * arg2;
        *arg4 = (1.0f - (arg1 * a0_frac)) * arg2;
        *arg5 = arg2;
        break;
    case 4:
        *arg3 = (1.0f - ((1.0f - a0_frac) * arg1)) * arg2;
        *arg4 = (1.0f - arg1) * arg2;
        *arg5 = arg2;
        break;
    case 5:
        *arg3 = arg2;
        *arg4 = (1.0f - arg1) * arg2;
        *arg5 = (1.0f - (arg1 * a0_frac)) * arg2;
        break;
    }
}
