#ifndef APP_MIST_H
#define APP_MIST_H

#include <PR/ultratypes.h>
#include <uv_matrix.h>
#include <uv_vector.h>

void mistInit(void);
void mist_803144D0(Mtx4F*, Vec3F*);
void mistUpdate(Mtx4F*, f32);
void mistDeinit(void);

#endif // APP_MIST_H
