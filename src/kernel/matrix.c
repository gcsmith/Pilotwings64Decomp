#include <uv_math.h>
#include <uv_matrix.h>

extern s32 gMatrixStackIdx;
extern Mtx4F gMatrixStack[];

void _uvDbMstackReset(void) {
    gMatrixStackIdx = -1;
}

Mtx4F* _uvDbMstackTop(void) {
    return &gMatrixStack[gMatrixStackIdx];
}

void _uvDbMstackPush(Mtx4F* src) {
    gMatrixStackIdx = gMatrixStackIdx + 1;
    if (gMatrixStackIdx >= 0x64) {
        _uvDebugPrintf("_uvDbMstackPush: stack full\n");
        return;
    }
    if (gMatrixStackIdx == 0) {
        uvMat4Copy(&gMatrixStack[gMatrixStackIdx], src);
        return;
    }
    uvMat4MulBA(&gMatrixStack[gMatrixStackIdx], &gMatrixStack[gMatrixStackIdx - 1], src);
}

void _uvDbMstackPop(void) {
    if (gMatrixStackIdx < 0) {
        _uvDebugPrintf("_uvDbMstackPop: stack empty\n");
        return;
    }
    gMatrixStackIdx -= 1;
}

void uvMat4Copy(Mtx4F* dst, Mtx4F* src) {
    dst->m[0][0] = src->m[0][0];
    dst->m[0][1] = src->m[0][1];
    dst->m[0][2] = src->m[0][2];
    dst->m[0][3] = src->m[0][3];

    dst->m[1][0] = src->m[1][0];
    dst->m[1][1] = src->m[1][1];
    dst->m[1][2] = src->m[1][2];
    dst->m[1][3] = src->m[1][3];

    dst->m[2][0] = src->m[2][0];
    dst->m[2][1] = src->m[2][1];
    dst->m[2][2] = src->m[2][2];
    dst->m[2][3] = src->m[2][3];

    dst->m[3][0] = src->m[3][0];
    dst->m[3][1] = src->m[3][1];
    dst->m[3][2] = src->m[3][2];
    dst->m[3][3] = src->m[3][3];
}

void uvMat4CopyXYZ(Mtx4F* dst, Mtx4F* src) {
    dst->m[0][0] = src->m[0][0];
    dst->m[0][1] = src->m[0][1];
    dst->m[0][2] = src->m[0][2];

    dst->m[1][0] = src->m[1][0];
    dst->m[1][1] = src->m[1][1];
    dst->m[1][2] = src->m[1][2];

    dst->m[2][0] = src->m[2][0];
    dst->m[2][1] = src->m[2][1];
    dst->m[2][2] = src->m[2][2];
}

void uvMat4CopyL(Mtx4F* dst, Mtx src) {
    *(long*)&dst->m[0][0] = src.m[0][0];
    *(long*)&dst->m[0][1] = src.m[0][1];
    *(long*)&dst->m[0][2] = src.m[0][2];
    *(long*)&dst->m[0][3] = src.m[0][3];
    *(long*)&dst->m[1][0] = src.m[1][0];
    *(long*)&dst->m[1][1] = src.m[1][1];
    *(long*)&dst->m[1][2] = src.m[1][2];
    *(long*)&dst->m[1][3] = src.m[1][3];
    *(long*)&dst->m[2][0] = src.m[2][0];
    *(long*)&dst->m[2][1] = src.m[2][1];
    *(long*)&dst->m[2][2] = src.m[2][2];
    *(long*)&dst->m[2][3] = src.m[2][3];
    *(long*)&dst->m[3][0] = src.m[3][0];
    *(long*)&dst->m[3][1] = src.m[3][1];
    *(long*)&dst->m[3][2] = src.m[3][2];
    *(long*)&dst->m[3][3] = src.m[3][3];
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/matrix/uvMat4CopyL2F.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/matrix/uvMat4CopyF2L.s")

void uvMat4SetIdentity(Mtx4F* dst) {
    dst->m[0][0] = 1.0f;
    dst->m[0][1] = 0.0f;
    dst->m[0][2] = 0.0f;
    dst->m[0][3] = 0.0f;

    dst->m[1][0] = 0.0f;
    dst->m[1][1] = 1.0f;
    dst->m[1][2] = 0.0f;
    dst->m[1][3] = 0.0f;

    dst->m[2][0] = 0.0f;
    dst->m[2][1] = 0.0f;
    dst->m[2][2] = 1.0f;
    dst->m[2][3] = 0.0f;

    dst->m[3][0] = 0.0f;
    dst->m[3][1] = 0.0f;
    dst->m[3][2] = 0.0f;
    dst->m[3][3] = 1.0f;
}

void uvMat4SetUnk1(Mtx4F* dst) {
    *(long*)&dst->m[0][0] = 0x10000;
    *(long*)&dst->m[0][1] = 0;
    *(long*)&dst->m[0][2] = 1;
    *(long*)&dst->m[0][3] = 0;

    *(long*)&dst->m[1][1] = 0x10000;
    *(long*)&dst->m[1][0] = 0;
    *(long*)&dst->m[1][3] = 1;
    *(long*)&dst->m[1][2] = 0;

    *(long*)&dst->m[2][0] = 0;
    *(long*)&dst->m[2][1] = 0;
    *(long*)&dst->m[2][2] = 0;
    *(long*)&dst->m[2][3] = 0;

    *(long*)&dst->m[3][0] = 0;
    *(long*)&dst->m[3][1] = 0;
    *(long*)&dst->m[3][2] = 0;
    *(long*)&dst->m[3][3] = 0;
}

void uvMat4Mul(Mtx4F* dst, Mtx4F* src1, Mtx4F* src2) {
    float unused1, unused2; // stack
    Mtx4F* pdst;
    Mtx4F temp;

    pdst = dst;
    if (src1 == dst || src2 == dst) {
        pdst = &temp;
    }
    pdst->m[0][0] = src1->m[0][0] * src2->m[0][0] + src1->m[0][1] * src2->m[1][0] + src1->m[0][2] * src2->m[2][0] + src1->m[0][3] * src2->m[3][0];
    pdst->m[0][1] = src1->m[0][0] * src2->m[0][1] + src1->m[0][1] * src2->m[1][1] + src1->m[0][2] * src2->m[2][1] + src1->m[0][3] * src2->m[3][1];
    pdst->m[0][2] = src1->m[0][0] * src2->m[0][2] + src1->m[0][1] * src2->m[1][2] + src1->m[0][2] * src2->m[2][2] + src1->m[0][3] * src2->m[3][2];
    pdst->m[0][3] = src1->m[0][0] * src2->m[0][3] + src1->m[0][1] * src2->m[1][3] + src1->m[0][2] * src2->m[2][3] + src1->m[0][3] * src2->m[3][3];
    pdst->m[1][0] = src1->m[1][0] * src2->m[0][0] + src1->m[1][1] * src2->m[1][0] + src1->m[1][2] * src2->m[2][0] + src1->m[1][3] * src2->m[3][0];
    pdst->m[1][1] = src1->m[1][0] * src2->m[0][1] + src1->m[1][1] * src2->m[1][1] + src1->m[1][2] * src2->m[2][1] + src1->m[1][3] * src2->m[3][1];
    pdst->m[1][2] = src1->m[1][0] * src2->m[0][2] + src1->m[1][1] * src2->m[1][2] + src1->m[1][2] * src2->m[2][2] + src1->m[1][3] * src2->m[3][2];
    pdst->m[1][3] = src1->m[1][0] * src2->m[0][3] + src1->m[1][1] * src2->m[1][3] + src1->m[1][2] * src2->m[2][3] + src1->m[1][3] * src2->m[3][3];
    pdst->m[2][0] = src1->m[2][0] * src2->m[0][0] + src1->m[2][1] * src2->m[1][0] + src1->m[2][2] * src2->m[2][0] + src1->m[2][3] * src2->m[3][0];
    pdst->m[2][1] = src1->m[2][0] * src2->m[0][1] + src1->m[2][1] * src2->m[1][1] + src1->m[2][2] * src2->m[2][1] + src1->m[2][3] * src2->m[3][1];
    pdst->m[2][2] = src1->m[2][0] * src2->m[0][2] + src1->m[2][1] * src2->m[1][2] + src1->m[2][2] * src2->m[2][2] + src1->m[2][3] * src2->m[3][2];
    pdst->m[2][3] = src1->m[2][0] * src2->m[0][3] + src1->m[2][1] * src2->m[1][3] + src1->m[2][2] * src2->m[2][3] + src1->m[2][3] * src2->m[3][3];
    pdst->m[3][0] = src1->m[3][0] * src2->m[0][0] + src1->m[3][1] * src2->m[1][0] + src1->m[3][2] * src2->m[2][0] + src1->m[3][3] * src2->m[3][0];
    pdst->m[3][1] = src1->m[3][0] * src2->m[0][1] + src1->m[3][1] * src2->m[1][1] + src1->m[3][2] * src2->m[2][1] + src1->m[3][3] * src2->m[3][1];
    pdst->m[3][2] = src1->m[3][0] * src2->m[0][2] + src1->m[3][1] * src2->m[1][2] + src1->m[3][2] * src2->m[2][2] + src1->m[3][3] * src2->m[3][2];
    pdst->m[3][3] = src1->m[3][0] * src2->m[0][3] + src1->m[3][1] * src2->m[1][3] + src1->m[3][2] * src2->m[2][3] + src1->m[3][3] * src2->m[3][3];
    if (src1 == dst || src2 == dst) {
        uvMat4Copy(dst, &temp);
    }
}

void uvMat4MulBA(Mtx4F* dst, Mtx4F* src1, Mtx4F* src2) {
    float unused1, unused2; // stack
    Mtx4F* pdst;
    Mtx4F temp;

    pdst = dst;
    if (src1 == dst || src2 == dst) {
        pdst = &temp;
    }
    pdst->m[0][0] = src2->m[0][0] * src1->m[0][0] + src2->m[0][1] * src1->m[1][0] + src2->m[0][2] * src1->m[2][0] + src2->m[0][3] * src1->m[3][0];
    pdst->m[0][1] = src2->m[0][0] * src1->m[0][1] + src2->m[0][1] * src1->m[1][1] + src2->m[0][2] * src1->m[2][1] + src2->m[0][3] * src1->m[3][1];
    pdst->m[0][2] = src2->m[0][0] * src1->m[0][2] + src2->m[0][1] * src1->m[1][2] + src2->m[0][2] * src1->m[2][2] + src2->m[0][3] * src1->m[3][2];
    pdst->m[0][3] = src2->m[0][0] * src1->m[0][3] + src2->m[0][1] * src1->m[1][3] + src2->m[0][2] * src1->m[2][3] + src2->m[0][3] * src1->m[3][3];
    pdst->m[1][0] = src2->m[1][0] * src1->m[0][0] + src2->m[1][1] * src1->m[1][0] + src2->m[1][2] * src1->m[2][0] + src2->m[1][3] * src1->m[3][0];
    pdst->m[1][1] = src2->m[1][0] * src1->m[0][1] + src2->m[1][1] * src1->m[1][1] + src2->m[1][2] * src1->m[2][1] + src2->m[1][3] * src1->m[3][1];
    pdst->m[1][2] = src2->m[1][0] * src1->m[0][2] + src2->m[1][1] * src1->m[1][2] + src2->m[1][2] * src1->m[2][2] + src2->m[1][3] * src1->m[3][2];
    pdst->m[1][3] = src2->m[1][0] * src1->m[0][3] + src2->m[1][1] * src1->m[1][3] + src2->m[1][2] * src1->m[2][3] + src2->m[1][3] * src1->m[3][3];
    pdst->m[2][0] = src2->m[2][0] * src1->m[0][0] + src2->m[2][1] * src1->m[1][0] + src2->m[2][2] * src1->m[2][0] + src2->m[2][3] * src1->m[3][0];
    pdst->m[2][1] = src2->m[2][0] * src1->m[0][1] + src2->m[2][1] * src1->m[1][1] + src2->m[2][2] * src1->m[2][1] + src2->m[2][3] * src1->m[3][1];
    pdst->m[2][2] = src2->m[2][0] * src1->m[0][2] + src2->m[2][1] * src1->m[1][2] + src2->m[2][2] * src1->m[2][2] + src2->m[2][3] * src1->m[3][2];
    pdst->m[2][3] = src2->m[2][0] * src1->m[0][3] + src2->m[2][1] * src1->m[1][3] + src2->m[2][2] * src1->m[2][3] + src2->m[2][3] * src1->m[3][3];
    pdst->m[3][0] = src2->m[3][0] * src1->m[0][0] + src2->m[3][1] * src1->m[1][0] + src2->m[3][2] * src1->m[2][0] + src2->m[3][3] * src1->m[3][0];
    pdst->m[3][1] = src2->m[3][0] * src1->m[0][1] + src2->m[3][1] * src1->m[1][1] + src2->m[3][2] * src1->m[2][1] + src2->m[3][3] * src1->m[3][1];
    pdst->m[3][2] = src2->m[3][0] * src1->m[0][2] + src2->m[3][1] * src1->m[1][2] + src2->m[3][2] * src1->m[2][2] + src2->m[3][3] * src1->m[3][2];
    pdst->m[3][3] = src2->m[3][0] * src1->m[0][3] + src2->m[3][1] * src1->m[1][3] + src2->m[3][2] * src1->m[2][3] + src2->m[3][3] * src1->m[3][3];
    if (src1 == dst || src2 == dst) {
        uvMat4Copy(dst, &temp);
    }
}

void uvMat4RotateAxis(Mtx4F* dst, float angle, char axis) {
    float sp6C;
    float fv0;
    float unused1;
    float unused2;
    Mtx4F temp;

    if (angle != 0.0f) {
        sp6C = uvSinF(angle);
        fv0 = uvCosF(angle);
        switch (axis) {
        case 'x':
            temp.m[0][0] = dst->m[0][0];
            temp.m[0][1] = dst->m[0][1];
            temp.m[0][2] = dst->m[0][2];
            temp.m[0][3] = dst->m[0][3];
            temp.m[1][0] = (fv0 * dst->m[1][0]) + (sp6C * dst->m[2][0]);
            temp.m[1][1] = (fv0 * dst->m[1][1]) + (sp6C * dst->m[2][1]);
            temp.m[1][2] = (fv0 * dst->m[1][2]) + (sp6C * dst->m[2][2]);
            temp.m[1][3] = (fv0 * dst->m[1][3]) + (sp6C * dst->m[2][3]);
            temp.m[2][0] = (fv0 * dst->m[2][0]) - (sp6C * dst->m[1][0]);
            temp.m[2][1] = (fv0 * dst->m[2][1]) - (sp6C * dst->m[1][1]);
            temp.m[2][2] = (fv0 * dst->m[2][2]) - (sp6C * dst->m[1][2]);
            temp.m[2][3] = (fv0 * dst->m[2][3]) - (sp6C * dst->m[1][3]);
            temp.m[3][0] = dst->m[3][0];
            temp.m[3][1] = dst->m[3][1];
            temp.m[3][2] = dst->m[3][2];
            temp.m[3][3] = dst->m[3][3];
            break;
        case 'y':
            temp.m[0][0] = (fv0 * dst->m[0][0]) - (sp6C * dst->m[2][0]);
            temp.m[0][1] = (fv0 * dst->m[0][1]) - (sp6C * dst->m[2][1]);
            temp.m[0][2] = (fv0 * dst->m[0][2]) - (sp6C * dst->m[2][2]);
            temp.m[0][3] = (fv0 * dst->m[0][3]) - (sp6C * dst->m[2][3]);
            temp.m[1][0] = dst->m[1][0];
            temp.m[1][1] = dst->m[1][1];
            temp.m[1][2] = dst->m[1][2];
            temp.m[1][3] = dst->m[1][3];
            temp.m[2][0] = (sp6C * dst->m[0][0]) + (fv0 * dst->m[2][0]);
            temp.m[2][1] = (sp6C * dst->m[0][1]) + (fv0 * dst->m[2][1]);
            temp.m[2][2] = (sp6C * dst->m[0][2]) + (fv0 * dst->m[2][2]);
            temp.m[2][3] = (sp6C * dst->m[0][3]) + (fv0 * dst->m[2][3]);
            temp.m[3][0] = dst->m[3][0];
            temp.m[3][1] = dst->m[3][1];
            temp.m[3][2] = dst->m[3][2];
            temp.m[3][3] = dst->m[3][3];
            break;
        case 'z':
            temp.m[0][0] = (fv0 * dst->m[0][0]) + (sp6C * dst->m[1][0]);
            temp.m[0][1] = (fv0 * dst->m[0][1]) + (sp6C * dst->m[1][1]);
            temp.m[0][2] = (fv0 * dst->m[0][2]) + (sp6C * dst->m[1][2]);
            temp.m[0][3] = (fv0 * dst->m[0][3]) + (sp6C * dst->m[1][3]);
            temp.m[1][0] = (fv0 * dst->m[1][0]) - (sp6C * dst->m[0][0]);
            temp.m[1][1] = (fv0 * dst->m[1][1]) - (sp6C * dst->m[0][1]);
            temp.m[1][2] = (fv0 * dst->m[1][2]) - (sp6C * dst->m[0][2]);
            temp.m[1][3] = (fv0 * dst->m[1][3]) - (sp6C * dst->m[0][3]);
            temp.m[2][0] = dst->m[2][0];
            temp.m[2][1] = dst->m[2][1];
            temp.m[2][2] = dst->m[2][2];
            temp.m[2][3] = dst->m[2][3];
            temp.m[3][0] = dst->m[3][0];
            temp.m[3][1] = dst->m[3][1];
            temp.m[3][2] = dst->m[3][2];
            temp.m[3][3] = dst->m[3][3];
            break;
        }
        uvMat4Copy(dst, &temp);
    }
}

void uvMat4UnkOp2(Mtx4F* dst, float arg1, float arg2, float arg3) {
    float unused1, unused2; // for stack
    Mtx4F temp;
    temp.m[0][0] = dst->m[0][0];
    temp.m[0][1] = dst->m[0][1];
    temp.m[0][2] = dst->m[0][2];
    temp.m[0][3] = dst->m[0][3];
    temp.m[1][0] = dst->m[1][0];
    temp.m[1][1] = dst->m[1][1];
    temp.m[1][2] = dst->m[1][2];
    temp.m[1][3] = dst->m[1][3];
    temp.m[2][0] = dst->m[2][0];
    temp.m[2][1] = dst->m[2][1];
    temp.m[2][2] = dst->m[2][2];
    temp.m[2][3] = dst->m[2][3];
    temp.m[3][0] = (arg1 * dst->m[0][0]) + (arg2 * dst->m[1][0]) + (arg3 * dst->m[2][0]) + dst->m[3][0];
    temp.m[3][1] = (arg1 * dst->m[0][1]) + (arg2 * dst->m[1][1]) + (arg3 * dst->m[2][1]) + dst->m[3][1];
    temp.m[3][2] = (arg1 * dst->m[0][2]) + (arg2 * dst->m[1][2]) + (arg3 * dst->m[2][2]) + dst->m[3][2];
    temp.m[3][3] = (arg1 * dst->m[0][3]) + (arg2 * dst->m[1][3]) + (arg3 * dst->m[2][3]) + dst->m[3][3];
    uvMat4Copy(dst, &temp);
}

void uvMat4UnkOp3(Mtx4F* dst, float arg1, float arg2, float arg3) {
    float unused1, unused2; // for stack
    Mtx4F scaled;

    scaled.m[0][0] = dst->m[0][0] * arg1;
    scaled.m[0][1] = dst->m[0][1] * arg1;
    scaled.m[0][2] = dst->m[0][2] * arg1;
    scaled.m[0][3] = dst->m[0][3] * arg1;
    scaled.m[1][0] = dst->m[1][0] * arg2;
    scaled.m[1][1] = dst->m[1][1] * arg2;
    scaled.m[1][2] = dst->m[1][2] * arg2;
    scaled.m[1][3] = dst->m[1][3] * arg2;
    scaled.m[2][0] = dst->m[2][0] * arg3;
    scaled.m[2][1] = dst->m[2][1] * arg3;
    scaled.m[2][2] = dst->m[2][2] * arg3;
    scaled.m[2][3] = dst->m[2][3] * arg3;
    scaled.m[3][0] = dst->m[3][0];
    scaled.m[3][1] = dst->m[3][1];
    scaled.m[3][2] = dst->m[3][2];
    scaled.m[3][3] = dst->m[3][3];
    uvMat4Copy(dst, &scaled);
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/matrix/uvMat4UnkOp4.s")

void uvMat4UnkOp5(Mtx4F* dst, Vec3F* vec1, Vec3F* vec2) {
    float tmp0 = vec2->f[0];
    float tmp1 = vec2->f[1];
    float tmp2 = vec2->f[2];
    vec1->f[0] = tmp0 * dst->m[0][0] + tmp1 * dst->m[1][0] + tmp2 * dst->m[2][0] + dst->m[3][0];
    vec1->f[1] = tmp0 * dst->m[0][1] + tmp1 * dst->m[1][1] + tmp2 * dst->m[2][1] + dst->m[3][1];
    vec1->f[2] = tmp0 * dst->m[0][2] + tmp1 * dst->m[1][2] + tmp2 * dst->m[2][2] + dst->m[3][2];
}

void uvMat4UnkOp6(Mtx4F* dst, Mtx4F* src1, Mtx4F* src2) {
    Vec3F v1;
    Vec3F v2;
    Vec3F v3;

    v1.f[0] = src1->m[3][0] - src2->m[3][0];
    v1.f[1] = src1->m[3][1] - src2->m[3][1];
    v1.f[2] = src1->m[3][2] - src2->m[3][2];
    if (uvVec3Normal(&v1, &v1) != 0) {
        v2.f[0] = src2->m[2][0];
        v2.f[1] = src2->m[2][1];
        v2.f[2] = src2->m[2][2];
        uvVec3Cross(&v3, &v1, &v2);
        if (uvVec3Normal(&v3, &v3) == 0) {
            v3.f[0] = src2->m[0][0];
            v3.f[1] = src2->m[0][1];
            v3.f[2] = 0.0f;
            uvVec3Normal(&v3, &v3);
        }
        uvVec3Cross(&v2, &v3, &v1);
        uvVec3Normal(&v2, &v2);
        dst->m[0][0] = v3.f[0];
        dst->m[0][1] = v3.f[1];
        dst->m[0][2] = v3.f[2];
        dst->m[1][0] = v1.f[0];
        dst->m[1][1] = v1.f[1];
        dst->m[1][2] = v1.f[2];
        dst->m[2][0] = v2.f[0];
        dst->m[2][1] = v2.f[1];
        dst->m[2][2] = v2.f[2];
        dst->m[3][0] = src2->m[3][0];
        dst->m[3][1] = src2->m[3][1];
        dst->m[3][2] = src2->m[3][2];
        dst->m[0][3] = 0.0f;
        dst->m[1][3] = 0.0f;
        dst->m[2][3] = 0.0f;
        dst->m[3][3] = 1.0f;
    }
}

void uvMat4SetUnk2(Mtx4F* dst, float arg1, float arg2, float arg3, float arg4, float arg5, float arg6) {
    float two5 = 2.0f * arg5;
    dst->m[0][0] = two5 / (arg2 - arg1);
    dst->m[1][1] = two5 / (arg4 - arg3);
    dst->m[2][0] = (arg2 + arg1) / (arg2 - arg1);
    dst->m[2][1] = (arg4 + arg3) / (arg4 - arg3);
    dst->m[2][2] = -(arg6 + arg5) / (arg6 - arg5);
    dst->m[2][3] = -1.0f;
    dst->m[3][2] = -(two5 * arg6) / (arg6 - arg5);
    if (0) { } // fakematch
    dst->m[3][3] = 0.0f;
    dst->m[3][1] = 0.0f;
    dst->m[3][0] = 0.0f;
    dst->m[1][3] = 0.0f;
    dst->m[1][2] = 0.0f;
    dst->m[1][0] = 0.0f;
    dst->m[0][3] = 0.0f;
    dst->m[0][2] = 0.0f;
    dst->m[0][1] = 0.0f;
}

void uvMat4Viewport(Mtx4F* dst, float arg1, float arg2, float arg3, float arg4) {
    float tmp21 = arg2 - arg1;
    float tmp43 = arg4 - arg3;
    dst->m[0][0] = 2.0f / tmp21;
    dst->m[1][1] = 2.0f / tmp43;
    dst->m[2][2] = -1.0f;
    dst->m[3][0] = -(arg2 + arg1) / tmp21;
    dst->m[3][1] = -(arg4 + arg3) / tmp43;
    dst->m[0][1] = 0.0f;
    dst->m[0][2] = 0.0f;
    dst->m[0][3] = 0.0f;
    dst->m[1][0] = 0.0f;
    dst->m[1][2] = 0.0f;
    dst->m[1][3] = 0.0f;
    dst->m[2][0] = 0.0f;
    dst->m[2][1] = 0.0f;
    dst->m[2][3] = 0.0f;
    dst->m[3][2] = 0.0f;
    dst->m[3][3] = 1.0f;
}

void uvMat4SetUnk4(Mtx4F* dst, float arg1, float arg2, float arg3, float arg4) {
    dst->m[0][0] = 1.0f - (2.0f * (arg2 * arg2 + arg3 * arg3));
    dst->m[0][1] = 2.0f * (arg1 * arg2 - arg3 * arg4);
    dst->m[0][2] = 2.0f * (arg3 * arg1 + arg2 * arg4);
    dst->m[1][0] = 2.0f * (arg1 * arg2 + arg3 * arg4);
    dst->m[1][1] = 1.0f - (2.0f * (arg3 * arg3 + arg1 * arg1));
    dst->m[1][2] = 2.0f * (arg2 * arg3 - arg1 * arg4);
    dst->m[2][0] = 2.0f * (arg3 * arg1 - arg2 * arg4);
    dst->m[2][1] = 2.0f * (arg2 * arg3 + arg1 * arg4);
    dst->m[2][2] = 1.0f - (2.0f * (arg2 * arg2 + arg1 * arg1));
}

