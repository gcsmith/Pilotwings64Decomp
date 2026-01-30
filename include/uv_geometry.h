#ifndef PILOTWINGS64_UV_GEOMETRY
#define PILOTWINGS64_UV_GEOMETRY

#include <PR/ultratypes.h>
#include <uv_util.h>

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

typedef uvVertex_t uvVertexArray_t[0x320];

s16 uvVtx(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8);
void uvVtxBeginPoly(void);
void uvBeginGrid(void);
void uvBeginTmesh(void);
void uvEndTmesh(void);
void uvVtxEndPoly(void);

#endif // PILOTWINGS64_UV_GEOMETRY

