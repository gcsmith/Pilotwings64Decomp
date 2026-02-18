#include <uv_math.h>
#include <uv_matrix.h>
#include <macros.h>

static s32 gMatrixStackIdx = 0;
extern Mtx4F gMatrixStack[100];

void _uvDbMstackReset(void) {
    gMatrixStackIdx = -1;
}

Mtx4F* _uvDbMstackTop(void) {
    return &gMatrixStack[gMatrixStackIdx];
}

void _uvDbMstackPush(Mtx4F* src) {
    gMatrixStackIdx = gMatrixStackIdx + 1;
    if (gMatrixStackIdx >= ARRAY_COUNT(gMatrixStack)) {
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

void uvMat4CopyL(Mtx* dst, Mtx src) {
    dst->m[0][0] = src.m[0][0];
    dst->m[0][1] = src.m[0][1];
    dst->m[0][2] = src.m[0][2];
    dst->m[0][3] = src.m[0][3];
    dst->m[1][0] = src.m[1][0];
    dst->m[1][1] = src.m[1][1];
    dst->m[1][2] = src.m[1][2];
    dst->m[1][3] = src.m[1][3];
    dst->m[2][0] = src.m[2][0];
    dst->m[2][1] = src.m[2][1];
    dst->m[2][2] = src.m[2][2];
    dst->m[2][3] = src.m[2][3];
    dst->m[3][0] = src.m[3][0];
    dst->m[3][1] = src.m[3][1];
    dst->m[3][2] = src.m[3][2];
    dst->m[3][3] = src.m[3][3];
}

void uvMat4CopyL2F(Mtx4F* dst, Mtx src) {
    Mtx4F* dst2 = dst;
    s32 pad;
    Mtx4F sp18;

    if (dst2 == (Mtx4F*)&src) {
        dst2 = &sp18;
    }
    dst2->m[0][0] = L2F(src, 0, 0);
    dst2->m[0][1] = L2F(src, 0, 1);
    dst2->m[0][2] = L2F(src, 0, 2);
    dst2->m[0][3] = L2F(src, 0, 3);
    dst2->m[1][0] = L2F(src, 1, 0);
    dst2->m[1][1] = L2F(src, 1, 1);
    dst2->m[1][2] = L2F(src, 1, 2);
    dst2->m[1][3] = L2F(src, 1, 3);
    dst2->m[2][0] = L2F(src, 2, 0);
    dst2->m[2][1] = L2F(src, 2, 1);
    dst2->m[2][2] = L2F(src, 2, 2);
    dst2->m[2][3] = L2F(src, 2, 3);
    dst2->m[3][0] = L2F(src, 3, 0);
    dst2->m[3][1] = L2F(src, 3, 1);
    dst2->m[3][2] = L2F(src, 3, 2);
    dst2->m[3][3] = L2F(src, 3, 3);

    if (dst2 == (Mtx4F*)&src) {
        uvMat4Copy(dst, &sp18);
    }
}

void uvMat4CopyF2L(Mtx* dst, Mtx4F* src) {
    Mtx_u* dst2;
    Mtx spA0;
    s32 xx;
    s32 yx;
    s32 zx;
    s32 wx;
    s32 xy;
    s32 yy;
    s32 zy;
    s32 wy;
    s32 xz;
    s32 yz;
    s32 zz;
    s32 wz;
    s32 xw;
    s32 yw;
    s32 zw;
    s32 ww;

    dst2 = (Mtx_u*)dst;
    if ((Mtx4F*)dst2 == src) {
        dst2 = (Mtx_u*)&spA0;
    }
    xx = (s32)((src->m[0][0] * 65536.0f) + 0.5f);
    dst2->i[0][0] = xx >> 0x10;
    dst2->f[0][0] = xx & 0xFFFF;
    yx = (s32)((src->m[0][1] * 65536.0f) + 0.5f);
    dst2->i[0][1] = yx >> 0x10;
    dst2->f[0][1] = yx & 0xFFFF;
    zx = (s32)((src->m[0][2] * 65536.0f) + 0.5f);
    dst2->i[0][2] = zx >> 0x10;
    dst2->f[0][2] = zx & 0xFFFF;
    wx = (s32)((src->m[0][3] * 65536.0f) + 0.5f);
    dst2->i[0][3] = wx >> 0x10;
    dst2->f[0][3] = wx & 0xFFFF;
    xy = (s32)((src->m[1][0] * 65536.0f) + 0.5f);
    dst2->i[1][0] = xy >> 0x10;
    dst2->f[1][0] = xy & 0xFFFF;
    yy = (s32)((src->m[1][1] * 65536.0f) + 0.5f);
    dst2->i[1][1] = yy >> 0x10;
    dst2->f[1][1] = yy & 0xFFFF;
    zy = (s32)((src->m[1][2] * 65536.0f) + 0.5f);
    dst2->i[1][2] = zy >> 0x10;
    dst2->f[1][2] = zy & 0xFFFF;
    wy = (s32)((src->m[1][3] * 65536.0f) + 0.5f);
    dst2->i[1][3] = wy >> 0x10;
    dst2->f[1][3] = wy & 0xFFFF;
    xz = (s32)((src->m[2][0] * 65536.0f) + 0.5f);
    dst2->i[2][0] = xz >> 0x10;
    dst2->f[2][0] = xz & 0xFFFF;
    yz = (s32)((src->m[2][1] * 65536.0f) + 0.5f);
    dst2->i[2][1] = yz >> 0x10;
    dst2->f[2][1] = yz & 0xFFFF;
    zz = (s32)((src->m[2][2] * 65536.0f) + 0.5f);
    dst2->i[2][2] = zz >> 0x10;
    dst2->f[2][2] = zz & 0xFFFF;
    wz = (s32)((src->m[2][3] * 65536.0f) + 0.5f);
    dst2->i[2][3] = wz >> 0x10;
    dst2->f[2][3] = wz & 0xFFFF;

    if (src->m[3][0] > 32767.0f) {
        dst2->i[3][0] = 0x7FFF;
        _uvDebugPrintf("s+12 overfow: %f\n", src->m[3][0]);
        *(s16*)1 = 0;
    } else if (src->m[3][0] < -32767.0f) {
        *(s16*)&dst2->i[3][0] = -0x8000;
        _uvDebugPrintf("s+12 overfow: %f\n", src->m[3][0]);
        *(s16*)1 = 0;
    } else {
        xw = (s32)((src->m[3][0] * 65536.0f) + 0.5f);
        dst2->i[3][0] = xw >> 0x10;
        dst2->f[3][0] = xw & 0xFFFF;
    }

    if (src->m[3][1] > 32767.0f) {
        dst2->i[3][1] = 0x7FFF;
        _uvDebugPrintf("s+13 overfow: %f\n", src->m[3][1]);
        *(s16*)1 = 0;
    } else if (src->m[3][1] < -32767.0f) {
        *(s16*)&dst2->i[3][1] = -0x8000;
        _uvDebugPrintf("s+13 overfow: %f\n", src->m[3][1]);
        *(s16*)1 = 0;
    } else {
        yw = (s32)((src->m[3][1] * 65536.0f) + 0.5f);
        dst2->i[3][1] = yw >> 0x10;
        dst2->f[3][1] = yw & 0xFFFF;
    }

    if (src->m[3][2] > 32767.0f) {
        dst2->i[3][2] = 0x7FFF;
        _uvDebugPrintf("s+14 overfow: %f\n", src->m[3][2]);
        *(s16*)1 = 0;
    } else if (src->m[3][2] < -32767.0f) {
        *(s16*)&dst2->i[3][2] = -0x8000;
        _uvDebugPrintf("s+14 overfow: %f\n", src->m[3][2]);
        *(s16*)1 = 0;
    } else {
        zw = (s32)((src->m[3][2] * 65536.0f) + 0.5f);
        dst2->i[3][2] = zw >> 0x10;
        dst2->f[3][2] = zw & 0xFFFF;
    }
    ww = (s32)((src->m[3][3] * 65536.0f) + 0.5f);
    dst2->i[3][3] = ww >> 0x10;
    dst2->f[3][3] = ww & 0xFFFF;
    if ((Mtx4F*)dst2 == src) {
        uvMat4CopyL(dst, spA0);
    }
}

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

void uvMat4SetIdentityL(Mtx* dst) {
    dst->m[0][0] = 0x10000;
    dst->m[0][1] = 0;
    dst->m[0][2] = 1;
    dst->m[0][3] = 0;

    dst->m[1][1] = 0x10000;
    dst->m[1][0] = 0;
    dst->m[1][3] = 1;
    dst->m[1][2] = 0;

    dst->m[2][0] = 0;
    dst->m[2][1] = 0;
    dst->m[2][2] = 0;
    dst->m[2][3] = 0;

    dst->m[3][0] = 0;
    dst->m[3][1] = 0;
    dst->m[3][2] = 0;
    dst->m[3][3] = 0;
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

void uvMat4LocalTranslate(Mtx4F* dst, float x, float y, float z) {
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
    temp.m[3][0] = (x * dst->m[0][0]) + (y * dst->m[1][0]) + (z * dst->m[2][0]) + dst->m[3][0];
    temp.m[3][1] = (x * dst->m[0][1]) + (y * dst->m[1][1]) + (z * dst->m[2][1]) + dst->m[3][1];
    temp.m[3][2] = (x * dst->m[0][2]) + (y * dst->m[1][2]) + (z * dst->m[2][2]) + dst->m[3][2];
    temp.m[3][3] = (x * dst->m[0][3]) + (y * dst->m[1][3]) + (z * dst->m[2][3]) + dst->m[3][3];
    uvMat4Copy(dst, &temp);
}

void uvMat4Scale(Mtx4F* dst, float scaleX, float scaleY, float scaleZ) {
    float unused1, unused2; // for stack
    Mtx4F scaled;

    scaled.m[0][0] = dst->m[0][0] * scaleX;
    scaled.m[0][1] = dst->m[0][1] * scaleX;
    scaled.m[0][2] = dst->m[0][2] * scaleX;
    scaled.m[0][3] = dst->m[0][3] * scaleX;
    scaled.m[1][0] = dst->m[1][0] * scaleY;
    scaled.m[1][1] = dst->m[1][1] * scaleY;
    scaled.m[1][2] = dst->m[1][2] * scaleY;
    scaled.m[1][3] = dst->m[1][3] * scaleY;
    scaled.m[2][0] = dst->m[2][0] * scaleZ;
    scaled.m[2][1] = dst->m[2][1] * scaleZ;
    scaled.m[2][2] = dst->m[2][2] * scaleZ;
    scaled.m[2][3] = dst->m[2][3] * scaleZ;
    scaled.m[3][0] = dst->m[3][0];
    scaled.m[3][1] = dst->m[3][1];
    scaled.m[3][2] = dst->m[3][2];
    scaled.m[3][3] = dst->m[3][3];
    uvMat4Copy(dst, &scaled);
}

void uvMat4InvertTranslationRotation(Mtx4F* dst, Mtx4F* mat2) {
    Mtx4F sp50;
    s32 i;
    s32 j;

    uvMat4Copy(&sp50, mat2);

    for (i = 0; i < 3; i++) {
        for (j = 0; j < i; j++) {
            sp50.m[i][j] = mat2->m[j][i];
            sp50.m[j][i] = mat2->m[i][j];
        }
    }

    sp50.m[3][0] = 0.0f;
    sp50.m[3][1] = 0.0f;
    sp50.m[3][2] = 0.0f;
    uvMat4LocalTranslate(&sp50, -mat2->m[3][0], -mat2->m[3][1], -mat2->m[3][2]);
    uvMat4Copy(dst, &sp50);
}

void uvMat4LocalToWorld(Mtx4F* src, Vec3F* dst, Vec3F* vec2) {
    float x = vec2->f[0];
    float y = vec2->f[1];
    float z = vec2->f[2];
    dst->f[0] = x * src->m[0][0] + y * src->m[1][0] + z * src->m[2][0] + src->m[3][0];
    dst->f[1] = x * src->m[0][1] + y * src->m[1][1] + z * src->m[2][1] + src->m[3][1];
    dst->f[2] = x * src->m[0][2] + y * src->m[1][2] + z * src->m[2][2] + src->m[3][2];
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

void uvMat4SetFrustrum(Mtx4F* dst, float left, float right, float top, float bottom, float near, float far) {
    dst->m[0][0] = (2.0f * near) / (right - left);
    dst->m[1][1] = (2.0f * near) / (bottom - top);
    dst->m[2][0] = (right + left) / (right - left);
    dst->m[2][1] = (bottom + top) / (bottom - top);
    dst->m[2][2] = -(far + near) / (far - near);
    dst->m[2][3] = -1.0f;
    dst->m[3][2] = -((2.0f * near) * far) / (far - near);
    if (0) { } // fakematch
    dst->m[0][1] = dst->m[0][2] = dst->m[0][3] = dst->m[1][0] = dst->m[1][2] = dst->m[1][3] = dst->m[3][0] = dst->m[3][1] = dst->m[3][3] = 0.0f;
}

void uvMat4SetOrtho(Mtx4F* dst, float left, float right, float top, float bottom) {
    dst->m[0][0] = 2.0f / (right - left);
    dst->m[1][1] = 2.0f / (bottom - top);
    dst->m[2][2] = -1.0f;
    dst->m[3][0] = -(right + left) / (right - left);
    dst->m[3][1] = -(bottom + top) / (bottom - top);
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

void uvMat4SetQuaternionRotation(Mtx4F* dst, float arg1, float arg2, float arg3, float arg4) {
    dst->m[0][0] = 1.0f - (2.0f * (SQ(arg2) + SQ(arg3)));
    dst->m[0][1] = 2.0f * (arg1 * arg2 - arg3 * arg4);
    dst->m[0][2] = 2.0f * (arg3 * arg1 + arg2 * arg4);
    dst->m[1][0] = 2.0f * (arg1 * arg2 + arg3 * arg4);
    dst->m[1][1] = 1.0f - (2.0f * (SQ(arg3) + SQ(arg1)));
    dst->m[1][2] = 2.0f * (arg2 * arg3 - arg1 * arg4);
    dst->m[2][0] = 2.0f * (arg3 * arg1 - arg2 * arg4);
    dst->m[2][1] = 2.0f * (arg2 * arg3 + arg1 * arg4);
    dst->m[2][2] = 1.0f - (2.0f * (SQ(arg2) + SQ(arg1)));
}

