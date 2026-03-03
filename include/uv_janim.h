#ifndef UV_JANIM_H
#define UV_JANIM_H

#include <PR/ultratypes.h>
#include <uv_dobj.h>

void* uvJanimLoad(s32);
void func_80200B00(s32, s32, f32);
void uvJanimPoseLine(Unk80371120*, s32, f32);
void uvJanimPoseGrid(Unk80371120*, s32, f32, f32);
void func_802006FC(Unk80371120*, Unk80371120*, Unk80371120*, f32);
void func_80200638(s32, Unk80371120*);

#endif // UV_JANIM_H
