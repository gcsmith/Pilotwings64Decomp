#ifndef APP_CODE_9A960_H
#define APP_CODE_9A960_H

#include <uv_matrix.h>
#include <uv_vector.h>
#include "task.h"

typedef struct {
    Vec3F pos;
    Vec4F quat;
} Unk803136C4_Arg0;

typedef struct {
    s32 count;
    Vec4F unk4[7]; // may be larger
} Unk80313FD0; // size = unknown

extern f32 D_8034F850; // related to time
extern f32 D_8034F854; // dynamic frame time?

void func_80313430(f32 x, f32 y, f32 z, f32* rho, f32* theta, f32* phi);
void func_803134D0(f32 rho, f32 theta, f32 phi, f32* x, f32* y, f32* z);
void func_80313570(Mtx4F* mat, f32* tx, f32* ty, f32* tz, f32* rz, f32* rx, f32* ry);
void func_80313640(f32 tx, f32 ty, f32 tz, f32 rz, f32 rx, f32 ry, Mtx4F* mat);
void func_803136C4(Unk803136C4_Arg0* quat, Mtx4F* mtx);
void func_803138A0(Mtx4F*, Mtx4F*, Mtx4F*, f32);
f32 func_80313AF4(f32, f32, f32);
f32 func_80313BAC(f32, f32, f32);
void func_80313C94(Vec3F*, Vec3F*, f32);
void func_80313D74(void);
void func_80313E0C(f32);
void func_80313E18(Vec3F*, Mtx4F*);
f32 func_80313F08(Unk803599D0*, f32);
void func_80313FD0(Unk80313FD0*, f32, Vec3F*);
s32 func_80314114(s32, s32, s32);
void func_80314154(void);
void func_803141E4(void);
void func_8031420C(f32, f32, f32, f32*, f32*, f32*);
f32 func_8031385C(Mtx4F*, Mtx4F*);

#endif // APP_CODE_9A960_H
