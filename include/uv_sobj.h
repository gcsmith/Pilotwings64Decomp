#ifndef UV_SOBJ_H
#define UV_SOBJ_H

#include <PR/ultratypes.h>
#include <uv_graphics.h>
#include <uv_matrix.h>

typedef struct UnkSobjDraw {
    u16 unk0;
    Mtx* unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    u16 unk14;
} UnkSobjDraw;

void uvSobjsDraw(UnkStruct_80204D94*, Mtx4F*, u16, u16, UnkSobjDraw*, u16, u8, s32);
u8 uvSobj_8022C7B8(uvGfxUnkStructModel*, f32);
void uvSobj_8022C8D0(UnkSobjDraw*, uvGfxUnkStructModel*, u8, Mtx4F*);
void uvSobj_8022CC28(UnkSobjDraw*, uvGfxUnkStructModel*, u8, f32, f32);
UnkSobjDraw* uvSobjLoadTerra(u32 soid);
void uvSobjPosm(u32 soid, s32 dstIdx, Mtx4F* src);
void uvSobj_8022D168(u32 soid, s32 srcIdx, Mtx4F* dst);
u16 uvSobj_8022D1E4(u32 soid);
void uvSobjModel(u32 soid, s32);

#endif // UV_SOBJ_H
