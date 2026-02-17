#ifndef UV_SOBJ_H
#define UV_SOBJ_H

#include <PR/ultratypes.h>
#include <uv_matrix.h>

typedef struct UnkSobjDraw {
    u16 unk0;
    Mtx* unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    u16 unk14;
} UnkSobjDraw;

u8 func_8022C7B8(uvGfxUnkStructModel* arg0, f32 arg1);
void func_8022C8D0(UnkSobjDraw* arg0, uvGfxUnkStructModel* arg1, u8 arg2, Mtx4F* arg3);
void func_8022CC28(UnkSobjDraw* arg0, uvGfxUnkStructModel* arg1, u8 arg2, f32 arg3, f32 arg4);

#endif // UV_SOBJ_H
