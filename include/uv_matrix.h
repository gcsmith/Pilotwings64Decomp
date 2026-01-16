#ifndef PILOTWINGS64_UV_MATRIX
#define PILOTWINGS64_UV_MATRIX

#include <ultra64.h>
#include <uv_math.h>
#include <uv_util.h>

typedef float Mtx4F_t[4][4];

typedef union {
    Mtx4F_t mf;
    struct {
        float xx, yx, zx, wx,
              xy, yy, zy, wy,
              xz, yz, zz, wz,
              xw, yw, zw, ww;
    };
} MtxF;

void uvMat4Copy(Mtx4F_t m_dst, Mtx4F_t m_src);
void uvMat4CopyXYZ(Mtx4F_t m_dst, Mtx4F_t m_src);
void uvMat4Init(Mtx *mat, Mtx init);
void uvMat4SetIdentity(Mtx4F_t mat);
void uvMat4SetUnk1(Mtx_t mat);

// matrix multiplication: m_dst = mat1 x mat2
// if m_dst is either mat1 or mat2, uses stack matrix
void uvMat4Mul(Mtx4F_t m_dst, Mtx4F_t mat1, Mtx4F_t mat2);

// matrix multiplication: m_dst = mat2 x mat1
// if m_dst is either mat1 or mat2, uses stack matrix
void uvMat4MulBA(Mtx4F_t m_dst, Mtx4F_t mat1, Mtx4F_t mat2);

void uvMat4RotateAxis(Mtx4F_t mat, float angle, char axis);
void uvMat4UnkOp2(Mtx4F_t mat, float arg1, float arg2, float arg3);
void uvMat4UnkOp3(Mtx4F_t mat, float arg1, float arg2, float arg3);
void uvMat4UnkOp5(Mtx4F_t mat, Vec3F_t *vec1, Vec3F_t *vec2);
void uvMat4SetUnk2(Mtx4F_t mat, float arg1, float arg2, float arg3, float arg4, float arg5, float arg6);
void uvMat4Viewport(Mtx4F_t mat, float arg1, float arg2, float arg3, float arg4);
void uvMat4SetUnk4(Mtx4F_t mat, float arg1, float arg2, float arg3, float arg4);

float func_80229EC0(float);
float func_8022A080(float);

#endif // PILOTWINGS64_UV_MATRIX

