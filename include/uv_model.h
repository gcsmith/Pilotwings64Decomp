#ifndef UV_MODEL_H
#define UV_MODEL_H

#include <uv_matrix.h>

s32 uvModelGet(s32, s32);
void uvModelGetProps(u16, s32, void*, s32);
void uvModelGetPosm(s32 model, s32 part, Mtx4F*);

#endif // UV_MODEL_H
