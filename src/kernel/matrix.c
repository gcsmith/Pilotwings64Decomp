#include <uv_matrix.h>

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/matrix/_uvDbMstackReset.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/matrix/_uvDbMstackTop.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/matrix/_uvDbMstackPush.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/matrix/_uvDbMstackPop.s")

void uvMat4Copy(Mtx4F_t m_dst, Mtx4F_t m_src) {
    m_dst[0][0] = m_src[0][0];
    m_dst[0][1] = m_src[0][1];
    m_dst[0][2] = m_src[0][2];
    m_dst[0][3] = m_src[0][3];

    m_dst[1][0] = m_src[1][0];
    m_dst[1][1] = m_src[1][1];
    m_dst[1][2] = m_src[1][2];
    m_dst[1][3] = m_src[1][3];

    m_dst[2][0] = m_src[2][0];
    m_dst[2][1] = m_src[2][1];
    m_dst[2][2] = m_src[2][2];
    m_dst[2][3] = m_src[2][3];

    m_dst[3][0] = m_src[3][0];
    m_dst[3][1] = m_src[3][1];
    m_dst[3][2] = m_src[3][2];
    m_dst[3][3] = m_src[3][3];
}

void uvMat4CopyXYZ(Mtx4F_t m_dst, Mtx4F_t m_src) {
    m_dst[0][0] = m_src[0][0];
    m_dst[0][1] = m_src[0][1];
    m_dst[0][2] = m_src[0][2];

    m_dst[1][0] = m_src[1][0];
    m_dst[1][1] = m_src[1][1];
    m_dst[1][2] = m_src[1][2];

    m_dst[2][0] = m_src[2][0];
    m_dst[2][1] = m_src[2][1];
    m_dst[2][2] = m_src[2][2];
}

void uvMat4Init(Mtx* mat, Mtx init) {
    mat->m[0][0] = init.m[0][0];
    mat->m[0][1] = init.m[0][1];
    mat->m[0][2] = init.m[0][2];
    mat->m[0][3] = init.m[0][3];
    mat->m[1][0] = init.m[1][0];
    mat->m[1][1] = init.m[1][1];
    mat->m[1][2] = init.m[1][2];
    mat->m[1][3] = init.m[1][3];
    mat->m[2][0] = init.m[2][0];
    mat->m[2][1] = init.m[2][1];
    mat->m[2][2] = init.m[2][2];
    mat->m[2][3] = init.m[2][3];
    mat->m[3][0] = init.m[3][0];
    mat->m[3][1] = init.m[3][1];
    mat->m[3][2] = init.m[3][2];
    mat->m[3][3] = init.m[3][3];
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/matrix/func_80228180.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/matrix/func_80228440.s")

void uvMat4SetIdentity(Mtx4F_t mat) {
    mat[0][0] = 1.0f;
    mat[0][1] = 0.0f;
    mat[0][2] = 0.0f;
    mat[0][3] = 0.0f;

    mat[1][0] = 0.0f;
    mat[1][1] = 1.0f;
    mat[1][2] = 0.0f;
    mat[1][3] = 0.0f;

    mat[2][0] = 0.0f;
    mat[2][1] = 0.0f;
    mat[2][2] = 1.0f;
    mat[2][3] = 0.0f;

    mat[3][0] = 0.0f;
    mat[3][1] = 0.0f;
    mat[3][2] = 0.0f;
    mat[3][3] = 1.0f;
}

void uvMat4SetUnk1(Mtx_t mat) {
    mat[0][0] = 0x10000;
    mat[0][1] = 0;
    mat[0][2] = 1;
    mat[0][3] = 0;

    mat[1][1] = 0x10000;
    mat[1][0] = 0;
    mat[1][3] = 1;
    mat[1][2] = 0;

    mat[2][0] = 0;
    mat[2][1] = 0;
    mat[2][2] = 0;
    mat[2][3] = 0;

    mat[3][0] = 0;
    mat[3][1] = 0;
    mat[3][2] = 0;
    mat[3][3] = 0;
}

void uvMat4Mul(Mtx4F_t m_dst, Mtx4F_t mat1, Mtx4F_t mat2) {
    float unused1, unused2; // stack
    float (*pmat)[4];
    Mtx4F_t m_scratch;

    pmat = m_dst;
    if (mat1 == m_dst || mat2 == m_dst) {
        pmat = m_scratch;
    }
    (pmat)[0][0] = mat1[0][0] * mat2[0][0] + mat1[0][1] * mat2[1][0] + mat1[0][2] * mat2[2][0] + mat1[0][3] * mat2[3][0];
    (pmat)[0][1] = mat1[0][0] * mat2[0][1] + mat1[0][1] * mat2[1][1] + mat1[0][2] * mat2[2][1] + mat1[0][3] * mat2[3][1];
    (pmat)[0][2] = mat1[0][0] * mat2[0][2] + mat1[0][1] * mat2[1][2] + mat1[0][2] * mat2[2][2] + mat1[0][3] * mat2[3][2];
    (pmat)[0][3] = mat1[0][0] * mat2[0][3] + mat1[0][1] * mat2[1][3] + mat1[0][2] * mat2[2][3] + mat1[0][3] * mat2[3][3];
    (pmat)[1][0] = mat1[1][0] * mat2[0][0] + mat1[1][1] * mat2[1][0] + mat1[1][2] * mat2[2][0] + mat1[1][3] * mat2[3][0];
    (pmat)[1][1] = mat1[1][0] * mat2[0][1] + mat1[1][1] * mat2[1][1] + mat1[1][2] * mat2[2][1] + mat1[1][3] * mat2[3][1];
    (pmat)[1][2] = mat1[1][0] * mat2[0][2] + mat1[1][1] * mat2[1][2] + mat1[1][2] * mat2[2][2] + mat1[1][3] * mat2[3][2];
    (pmat)[1][3] = mat1[1][0] * mat2[0][3] + mat1[1][1] * mat2[1][3] + mat1[1][2] * mat2[2][3] + mat1[1][3] * mat2[3][3];
    (pmat)[2][0] = mat1[2][0] * mat2[0][0] + mat1[2][1] * mat2[1][0] + mat1[2][2] * mat2[2][0] + mat1[2][3] * mat2[3][0];
    (pmat)[2][1] = mat1[2][0] * mat2[0][1] + mat1[2][1] * mat2[1][1] + mat1[2][2] * mat2[2][1] + mat1[2][3] * mat2[3][1];
    (pmat)[2][2] = mat1[2][0] * mat2[0][2] + mat1[2][1] * mat2[1][2] + mat1[2][2] * mat2[2][2] + mat1[2][3] * mat2[3][2];
    (pmat)[2][3] = mat1[2][0] * mat2[0][3] + mat1[2][1] * mat2[1][3] + mat1[2][2] * mat2[2][3] + mat1[2][3] * mat2[3][3];
    (pmat)[3][0] = mat1[3][0] * mat2[0][0] + mat1[3][1] * mat2[1][0] + mat1[3][2] * mat2[2][0] + mat1[3][3] * mat2[3][0];
    (pmat)[3][1] = mat1[3][0] * mat2[0][1] + mat1[3][1] * mat2[1][1] + mat1[3][2] * mat2[2][1] + mat1[3][3] * mat2[3][1];
    (pmat)[3][2] = mat1[3][0] * mat2[0][2] + mat1[3][1] * mat2[1][2] + mat1[3][2] * mat2[2][2] + mat1[3][3] * mat2[3][2];
    (pmat)[3][3] = mat1[3][0] * mat2[0][3] + mat1[3][1] * mat2[1][3] + mat1[3][2] * mat2[2][3] + mat1[3][3] * mat2[3][3];
    if (mat1 == m_dst || mat2 == m_dst) {
        uvMat4Copy(m_dst, m_scratch);
    }
}

void uvMat4MulBA(Mtx4F_t m_dst, Mtx4F_t mat1, Mtx4F_t mat2) {
    float unused1, unused2; // stack
    float (*pmat)[4];
    Mtx4F_t m_scratch;

    pmat = m_dst;
    if (mat1 == m_dst || mat2 == m_dst) {
        pmat = m_scratch;
    }
    (pmat)[0][0] = mat2[0][0] * mat1[0][0] + mat2[0][1] * mat1[1][0] + mat2[0][2] * mat1[2][0] + mat2[0][3] * mat1[3][0];
    (pmat)[0][1] = mat2[0][0] * mat1[0][1] + mat2[0][1] * mat1[1][1] + mat2[0][2] * mat1[2][1] + mat2[0][3] * mat1[3][1];
    (pmat)[0][2] = mat2[0][0] * mat1[0][2] + mat2[0][1] * mat1[1][2] + mat2[0][2] * mat1[2][2] + mat2[0][3] * mat1[3][2];
    (pmat)[0][3] = mat2[0][0] * mat1[0][3] + mat2[0][1] * mat1[1][3] + mat2[0][2] * mat1[2][3] + mat2[0][3] * mat1[3][3];
    (pmat)[1][0] = mat2[1][0] * mat1[0][0] + mat2[1][1] * mat1[1][0] + mat2[1][2] * mat1[2][0] + mat2[1][3] * mat1[3][0];
    (pmat)[1][1] = mat2[1][0] * mat1[0][1] + mat2[1][1] * mat1[1][1] + mat2[1][2] * mat1[2][1] + mat2[1][3] * mat1[3][1];
    (pmat)[1][2] = mat2[1][0] * mat1[0][2] + mat2[1][1] * mat1[1][2] + mat2[1][2] * mat1[2][2] + mat2[1][3] * mat1[3][2];
    (pmat)[1][3] = mat2[1][0] * mat1[0][3] + mat2[1][1] * mat1[1][3] + mat2[1][2] * mat1[2][3] + mat2[1][3] * mat1[3][3];
    (pmat)[2][0] = mat2[2][0] * mat1[0][0] + mat2[2][1] * mat1[1][0] + mat2[2][2] * mat1[2][0] + mat2[2][3] * mat1[3][0];
    (pmat)[2][1] = mat2[2][0] * mat1[0][1] + mat2[2][1] * mat1[1][1] + mat2[2][2] * mat1[2][1] + mat2[2][3] * mat1[3][1];
    (pmat)[2][2] = mat2[2][0] * mat1[0][2] + mat2[2][1] * mat1[1][2] + mat2[2][2] * mat1[2][2] + mat2[2][3] * mat1[3][2];
    (pmat)[2][3] = mat2[2][0] * mat1[0][3] + mat2[2][1] * mat1[1][3] + mat2[2][2] * mat1[2][3] + mat2[2][3] * mat1[3][3];
    (pmat)[3][0] = mat2[3][0] * mat1[0][0] + mat2[3][1] * mat1[1][0] + mat2[3][2] * mat1[2][0] + mat2[3][3] * mat1[3][0];
    (pmat)[3][1] = mat2[3][0] * mat1[0][1] + mat2[3][1] * mat1[1][1] + mat2[3][2] * mat1[2][1] + mat2[3][3] * mat1[3][1];
    (pmat)[3][2] = mat2[3][0] * mat1[0][2] + mat2[3][1] * mat1[1][2] + mat2[3][2] * mat1[2][2] + mat2[3][3] * mat1[3][2];
    (pmat)[3][3] = mat2[3][0] * mat1[0][3] + mat2[3][1] * mat1[1][3] + mat2[3][2] * mat1[2][3] + mat2[3][3] * mat1[3][3];
    if (mat1 == m_dst || mat2 == m_dst) {
        uvMat4Copy(m_dst, m_scratch);
    }
}

void uvMat4RotateAxis(Mtx4F_t mat, float angle, char axis) {
    float sp6C;
    float fv0;
    float unused1;
    float unused2;
    Mtx4F_t m_scratch;

    if (angle != 0.0f) {
        sp6C = func_80229EC0(angle);
        fv0 = func_8022A080(angle);
        switch (axis) {
        case 'x':
            m_scratch[0][0] = mat[0][0];
            m_scratch[0][1] = mat[0][1];
            m_scratch[0][2] = mat[0][2];
            m_scratch[0][3] = mat[0][3];
            m_scratch[1][0] = (fv0 * mat[1][0]) + (sp6C * mat[2][0]);
            m_scratch[1][1] = (fv0 * mat[1][1]) + (sp6C * mat[2][1]);
            m_scratch[1][2] = (fv0 * mat[1][2]) + (sp6C * mat[2][2]);
            m_scratch[1][3] = (fv0 * mat[1][3]) + (sp6C * mat[2][3]);
            m_scratch[2][0] = (fv0 * mat[2][0]) - (sp6C * mat[1][0]);
            m_scratch[2][1] = (fv0 * mat[2][1]) - (sp6C * mat[1][1]);
            m_scratch[2][2] = (fv0 * mat[2][2]) - (sp6C * mat[1][2]);
            m_scratch[2][3] = (fv0 * mat[2][3]) - (sp6C * mat[1][3]);
            m_scratch[3][0] = mat[3][0];
            m_scratch[3][1] = mat[3][1];
            m_scratch[3][2] = mat[3][2];
            m_scratch[3][3] = mat[3][3];
            break;
        case 'y':
            m_scratch[0][0] = (fv0 * mat[0][0]) - (sp6C * mat[2][0]);
            m_scratch[0][1] = (fv0 * mat[0][1]) - (sp6C * mat[2][1]);
            m_scratch[0][2] = (fv0 * mat[0][2]) - (sp6C * mat[2][2]);
            m_scratch[0][3] = (fv0 * mat[0][3]) - (sp6C * mat[2][3]);
            m_scratch[1][0] = mat[1][0];
            m_scratch[1][1] = mat[1][1];
            m_scratch[1][2] = mat[1][2];
            m_scratch[1][3] = mat[1][3];
            m_scratch[2][0] = (sp6C * mat[0][0]) + (fv0 * mat[2][0]);
            m_scratch[2][1] = (sp6C * mat[0][1]) + (fv0 * mat[2][1]);
            m_scratch[2][2] = (sp6C * mat[0][2]) + (fv0 * mat[2][2]);
            m_scratch[2][3] = (sp6C * mat[0][3]) + (fv0 * mat[2][3]);
            m_scratch[3][0] = mat[3][0];
            m_scratch[3][1] = mat[3][1];
            m_scratch[3][2] = mat[3][2];
            m_scratch[3][3] = mat[3][3];
            break;
        case 'z':
            m_scratch[0][0] = (fv0 * mat[0][0]) + (sp6C * mat[1][0]);
            m_scratch[0][1] = (fv0 * mat[0][1]) + (sp6C * mat[1][1]);
            m_scratch[0][2] = (fv0 * mat[0][2]) + (sp6C * mat[1][2]);
            m_scratch[0][3] = (fv0 * mat[0][3]) + (sp6C * mat[1][3]);
            m_scratch[1][0] = (fv0 * mat[1][0]) - (sp6C * mat[0][0]);
            m_scratch[1][1] = (fv0 * mat[1][1]) - (sp6C * mat[0][1]);
            m_scratch[1][2] = (fv0 * mat[1][2]) - (sp6C * mat[0][2]);
            m_scratch[1][3] = (fv0 * mat[1][3]) - (sp6C * mat[0][3]);
            m_scratch[2][0] = mat[2][0];
            m_scratch[2][1] = mat[2][1];
            m_scratch[2][2] = mat[2][2];
            m_scratch[2][3] = mat[2][3];
            m_scratch[3][0] = mat[3][0];
            m_scratch[3][1] = mat[3][1];
            m_scratch[3][2] = mat[3][2];
            m_scratch[3][3] = mat[3][3];
            break;
        }
        uvMat4Copy(mat, m_scratch);
    }
}

void uvMat4UnkOp2(Mtx4F_t mat, float arg1, float arg2, float arg3) {
    float unused1, unused2; // for stack
    Mtx4F_t tmpmat;
    tmpmat[0][0] = mat[0][0];
    tmpmat[0][1] = mat[0][1];
    tmpmat[0][2] = mat[0][2];
    tmpmat[0][3] = mat[0][3];
    tmpmat[1][0] = mat[1][0];
    tmpmat[1][1] = mat[1][1];
    tmpmat[1][2] = mat[1][2];
    tmpmat[1][3] = mat[1][3];
    tmpmat[2][0] = mat[2][0];
    tmpmat[2][1] = mat[2][1];
    tmpmat[2][2] = mat[2][2];
    tmpmat[2][3] = mat[2][3];
    tmpmat[3][0] = (arg1 * mat[0][0]) + (arg2 * mat[1][0]) + (arg3 * mat[2][0]) + mat[3][0];
    tmpmat[3][1] = (arg1 * mat[0][1]) + (arg2 * mat[1][1]) + (arg3 * mat[2][1]) + mat[3][1];
    tmpmat[3][2] = (arg1 * mat[0][2]) + (arg2 * mat[1][2]) + (arg3 * mat[2][2]) + mat[3][2];
    tmpmat[3][3] = (arg1 * mat[0][3]) + (arg2 * mat[1][3]) + (arg3 * mat[2][3]) + mat[3][3];
    uvMat4Copy(mat, tmpmat);
}

void uvMat4UnkOp3(Mtx4F_t mat, float arg1, float arg2, float arg3) {
    float unused1, unused2; // for stack
    Mtx4F_t scaled;

    scaled[0][0] = mat[0][0] * arg1;
    scaled[0][1] = mat[0][1] * arg1;
    scaled[0][2] = mat[0][2] * arg1;
    scaled[0][3] = mat[0][3] * arg1;
    scaled[1][0] = mat[1][0] * arg2;
    scaled[1][1] = mat[1][1] * arg2;
    scaled[1][2] = mat[1][2] * arg2;
    scaled[1][3] = mat[1][3] * arg2;
    scaled[2][0] = mat[2][0] * arg3;
    scaled[2][1] = mat[2][1] * arg3;
    scaled[2][2] = mat[2][2] * arg3;
    scaled[2][3] = mat[2][3] * arg3;
    scaled[3][0] = mat[3][0];
    scaled[3][1] = mat[3][1];
    scaled[3][2] = mat[3][2];
    scaled[3][3] = mat[3][3];
    uvMat4Copy(mat, scaled);
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/matrix/uvMat4UnkOp4.s")

void uvMat4UnkOp5(Mtx4F_t mat, Vec3F_t* vec1, Vec3F_t* vec2) {
    float tmp0 = vec2->f[0];
    float tmp1 = vec2->f[1];
    float tmp2 = vec2->f[2];
    vec1->f[0] = tmp0 * mat[0][0] + tmp1 * mat[1][0] + tmp2 * mat[2][0] + mat[3][0];
    vec1->f[1] = tmp0 * mat[0][1] + tmp1 * mat[1][1] + tmp2 * mat[2][1] + mat[3][1];
    vec1->f[2] = tmp0 * mat[0][2] + tmp1 * mat[1][2] + tmp2 * mat[2][2] + mat[3][2];
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/matrix/func_80229AA0.s")

void uvMat4SetUnk2(Mtx4F_t mat, float arg1, float arg2, float arg3, float arg4, float arg5, float arg6) {
    float two5 = 2.0f * arg5;
    mat[0][0] = two5 / (arg2 - arg1);
    mat[1][1] = two5 / (arg4 - arg3);
    mat[2][0] = (arg2 + arg1) / (arg2 - arg1);
    mat[2][1] = (arg4 + arg3) / (arg4 - arg3);
    mat[2][2] = -(arg6 + arg5) / (arg6 - arg5);
    mat[2][3] = -1.0f;
    mat[3][2] = -(two5 * arg6) / (arg6 - arg5);
    if (0) { } // fakematch
    mat[3][3] = 0.0f;
    mat[3][1] = 0.0f;
    mat[3][0] = 0.0f;
    mat[1][3] = 0.0f;
    mat[1][2] = 0.0f;
    mat[1][0] = 0.0f;
    mat[0][3] = 0.0f;
    mat[0][2] = 0.0f;
    mat[0][1] = 0.0f;
}

void uvMat4Viewport(Mtx4F_t mat, float arg1, float arg2, float arg3, float arg4) {
    float tmp21 = arg2 - arg1;
    float tmp43 = arg4 - arg3;
    mat[0][0] = 2.0f / tmp21;
    mat[1][1] = 2.0f / tmp43;
    mat[2][2] = -1.0f;
    mat[3][0] = -(arg2 + arg1) / tmp21;
    mat[3][1] = -(arg4 + arg3) / tmp43;
    mat[0][1] = 0.0f;
    mat[0][2] = 0.0f;
    mat[0][3] = 0.0f;
    mat[1][0] = 0.0f;
    mat[1][2] = 0.0f;
    mat[1][3] = 0.0f;
    mat[2][0] = 0.0f;
    mat[2][1] = 0.0f;
    mat[2][3] = 0.0f;
    mat[3][2] = 0.0f;
    mat[3][3] = 1.0f;
}

void uvMat4SetUnk4(Mtx4F_t mat, float arg1, float arg2, float arg3, float arg4) {
    mat[0][0] = 1.0f - (2.0f * (arg2 * arg2 + arg3 * arg3));
    mat[0][1] = 2.0f * (arg1 * arg2 - arg3 * arg4);
    mat[0][2] = 2.0f * (arg3 * arg1 + arg2 * arg4);
    mat[1][0] = 2.0f * (arg1 * arg2 + arg3 * arg4);
    mat[1][1] = 1.0f - (2.0f * (arg3 * arg3 + arg1 * arg1));
    mat[1][2] = 2.0f * (arg2 * arg3 - arg1 * arg4);
    mat[2][0] = 2.0f * (arg3 * arg1 - arg2 * arg4);
    mat[2][1] = 2.0f * (arg2 * arg3 + arg1 * arg4);
    mat[2][2] = 1.0f - (2.0f * (arg2 * arg2 + arg1 * arg1));
}

