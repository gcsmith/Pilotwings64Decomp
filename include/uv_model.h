#ifndef UV_MODEL_H
#define UV_MODEL_H

#include <uv_matrix.h>

void uvModelGetProps(u16, s32, void*, s32);
void uvModelGetPosm(s32 model, s32 part, Mtx4F*);

#endif // UV_MODEL_H
