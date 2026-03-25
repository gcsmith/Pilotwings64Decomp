#ifndef APP_SPATH_H
#define APP_SPATH_H

#include <PR/ultratypes.h>
#include <uv_matrix.h>

s32 spathLoadFile(s32);
void spathUpdate(Mtx4F*, s32, f32, f32);
void spathUpdate2(Mtx4F*, s32, f32, f32, f32);
void spathFree(s32);

#endif // APP_SPATH_H
