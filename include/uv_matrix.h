#ifndef PILOTWINGS64_UV_MATRIX
#define PILOTWINGS64_UV_MATRIX

#include <ultra64.h>
#include <uv_vector.h>
#include <uv_util.h>

typedef union {
    float m[4][4];
    struct {
        float xx, yx, zx, wx,
              xy, yy, zy, wy,
              xz, yz, zz, wz,
              xw, yw, zw, ww;
    };
} Mtx4F;

typedef struct Mtx_u {
    u16 i[4][4];
    u16 f[4][4];
} Mtx_u;

typedef union {
    Mtx_t m;
    Mtx_u u;
    long long int force_structure_alignment;
} uvMtx;

#define MTX_TO_PART(mtx) (*(Mtx_u*)&(mtx))
#define L2F(mtx, i1, i2) ((((s16)MTX_TO_PART(mtx).i[(i1)][(i2)] << 0x10) | ((s16)MTX_TO_PART(mtx).f[(i1)][(i2)] & 0xFFFF)) / 65536.0f)

void _uvDbMstackReset(void);
Mtx4F* _uvDbMstackTop(void);
void _uvDbMstackPush(Mtx4F* src);
void _uvDbMstackPop(void);

void uvMat4Copy(Mtx4F* dst, Mtx4F* src);
void uvMat4CopyXYZ(Mtx4F* dst, Mtx4F* src);
void uvMat4CopyL(Mtx* dst, Mtx src);
void uvMat4CopyL2F(Mtx4F* dst, Mtx src);
void uvMat4CopyF2L(Mtx* dst, Mtx4F* src);
void uvMat4SetIdentity(Mtx4F* dst);
void uvMat4SetIdentityL(Mtx* dst);

// matrix multiplication: dst = mat1 x mat2
// if dst is either mat1 or mat2, uses stack matrix
void uvMat4Mul(Mtx4F* dst, Mtx4F* src1, Mtx4F* src2);

// matrix multiplication: dst = mat2 x mat1
// if dst is either mat1 or mat2, uses stack matrix
void uvMat4MulBA(Mtx4F* dst, Mtx4F* src1, Mtx4F* src2);

// axis is usually defined as the string 'x', 'y' or 'z' which is hex 0x78, 0x79 and 0x7A respectively
void uvMat4RotateAxis(Mtx4F* dst, float angle, char axis);
void uvMat4LocalTranslate(Mtx4F* dst, float x, float y, float z);
void uvMat4Scale(Mtx4F* dst, float scaleX, float scaleY, float scaleZ);
void uvMat4InvertTranslationRotation(Mtx4F* dst, Mtx4F* mat2);
void uvMat4LocalToWorld(Mtx4F* src, Vec3F *dst, Vec3F *vec2);
void uvMat4UnkOp6(Mtx4F* dst, Mtx4F* src1, Mtx4F* src2);
void uvMat4SetFrustrum(Mtx4F* dst, float left, float right, float top, float bottom, float near, float far);
void uvMat4SetOrtho(Mtx4F* dst, float left, float right, float top, float bottom);
void uvMat4SetQuaternionRotation(Mtx4F* dst, float arg1, float arg2, float arg3, float arg4);

#endif // PILOTWINGS64_UV_MATRIX

