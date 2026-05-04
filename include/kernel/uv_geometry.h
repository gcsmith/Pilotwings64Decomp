#ifndef PILOTWINGS64_UV_GEOMETRY_H
#define PILOTWINGS64_UV_GEOMETRY_H

#include <uv_common.h>

#define UV_GEOM_NUM_VERTICES 0x320

void uvVtxInit(void);
s16 uvVtx(s32 x, s32 y, s32 z, s32 s, s32 t, s32 r, s32 g, s32 b, s32 a);
void uvVtxReset(u8 flip);
void uvVtxBeginPoly(void);
void uvBeginGrid(void);
void uvBeginTmesh(void);
void uvEndTmesh(void);
void uvEndGridWide(s16 arg0, s16 arg1, u8 arg2, u8 arg3);
void uvEndGrid(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void uvVtxRect(s32 x0, s32 y0, s32 x1, s32 y1);
void uvVtxEndPoly(void);

#endif // PILOTWINGS64_UV_GEOMETRY_H

