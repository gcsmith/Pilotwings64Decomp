#ifndef PILOTWINGS64_UV_GEOMETRY
#define PILOTWINGS64_UV_GEOMETRY

#include <PR/ultratypes.h>
#include <uv_util.h>

#define UV_GEOM_NUM_VERTICES 0x320

typedef struct uvVertex {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s8 unkC;
    s8 unkD;
    s8 unkE;
    s8 unkF;
} uvVertex_t;

typedef uvVertex_t uvVertexArray_t[UV_GEOM_NUM_VERTICES];

void uvVtxInit(void);
s16  uvVtx(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8);
void uvVtxReset(u8 flip);
void uvVtxBeginPoly(void);
void uvBeginGrid(void);
void uvBeginTmesh(void);
void uvEndTmesh(void);
void uvEndGridWide(s16 arg0, s16 arg1, u8 arg2, s32 arg3);
void uvEndGrid(s32 arg0, s32 arg1, u8 arg2, u8 arg3);
void uvVtxRect(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void uvVtxEndPoly(void);

#endif // PILOTWINGS64_UV_GEOMETRY

