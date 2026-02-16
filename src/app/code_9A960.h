#ifndef APP_CODE_9A960_H
#define APP_CODE_9A960_H

#include <uv_matrix.h>
#include "code_5A6A0.h"

extern f32 D_8034F850; // .data related to time
extern f32 D_8034F854; // .data ≈ 0.017, dynamic frame time?

void func_80313430(f32 arg0, f32 arg1, f32 arg2, f32* arg3, f32* arg4, f32* arg5);
void func_80313570(Mtx4F*, f32*, f32*, f32*, f32*, f32*, f32*);
void func_80313640(f32 tx, f32 ty, f32 tz, f32 rz, f32 rx, f32 ry, Mtx4F* mat);
f32 func_80313AF4(f32, f32, f32);
f32 func_80313F08(Unk803599D0*, f32);
void func_80313E0C(f32);
void func_80313D74(void);
void func_803138A0(Mtx4F*, Mtx4F*, Mtx4F*, f32);
void func_803134D0(f32, f32, f32, f32*, f32*, f32*);
void func_80313E18(Vec3F*, Mtx4F*);
void func_80314154(void);
void func_803141E4(void);

#endif // APP_CODE_9A960_H
