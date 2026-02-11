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

void _uvDbMstackReset(void);
Mtx4F* _uvDbMstackTop(void);
void _uvDbMstackPush(Mtx4F* src);
void _uvDbMstackPop(void);

void uvMat4Copy(Mtx4F* dst, Mtx4F* src);
void uvMat4CopyXYZ(Mtx4F* dst, Mtx4F* src);
void uvMat4CopyL(Mtx4F* dst, Mtx src);
void uvMat4CopyL2F(Mtx4F* dst, Mtx src);
void uvMat4CopyF2L(Mtx4F* dst, Mtx4F* src);
void uvMat4SetIdentity(Mtx4F* dst);
void uvMat4SetUnk1(Mtx4F* dst);

// matrix multiplication: dst = mat1 x mat2
// if dst is either mat1 or mat2, uses stack matrix
void uvMat4Mul(Mtx4F* dst, Mtx4F* src1, Mtx4F* src2);

// matrix multiplication: dst = mat2 x mat1
// if dst is either mat1 or mat2, uses stack matrix
void uvMat4MulBA(Mtx4F* dst, Mtx4F* src1, Mtx4F* src2);

// axis is usually defined as the string 'x', 'y' or 'z' which is hex 0x78, 0x79 and 0x7A respectively
void uvMat4RotateAxis(Mtx4F* dst, float angle, char axis);
void uvMat4UnkOp2(Mtx4F* dst, float arg1, float arg2, float arg3);
void uvMat4UnkOp3(Mtx4F* dst, float arg1, float arg2, float arg3);
void uvMat4UnkOp4(Mtx4F* dst, Mtx4F* mat2);
void uvMat4UnkOp5(Mtx4F* dst, Vec3F *vec1, Vec3F *vec2);
void uvMat4UnkOp6(Mtx4F* dst, Mtx4F* src1, Mtx4F* src2);
void uvMat4SetUnk2(Mtx4F* dst, float arg1, float arg2, float arg3, float arg4, float arg5, float arg6);
void uvMat4Viewport(Mtx4F* dst, float arg1, float arg2, float arg3, float arg4);
void uvMat4SetUnk4(Mtx4F* dst, float arg1, float arg2, float arg3, float arg4);

#endif // PILOTWINGS64_UV_MATRIX

