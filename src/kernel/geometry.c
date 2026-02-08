#include <uv_geometry.h>
#include <uv_graphics.h>

// TODO FIXME fix for gSPTextureRectangle, maybe due to older f3d ucode?
#undef G_RDPHALF_1
#undef G_RDPHALF_2
#define G_RDPHALF_1 (G_IMMFIRST - 12)
#define G_RDPHALF_2 (G_IMMFIRST - 13)

extern uvVertexArray_t gGeomVertexData[];
extern uvVertex_t* gGeomVertexPtrs;
extern s16 gGeomVertexToggle;
extern s16 gGeomVertexCount;
extern s16 gGeomFirstTmesh;
extern s16 gGeomFirstPoly;
extern s16 gGeomFirstGrid;

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/geometry/uvVtxInit.s")

s16 uvVtx(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8) {
    uvVertex_t* vtx;

    vtx = &gGeomVertexPtrs[gGeomVertexCount];
    if (gGeomVertexCount >= UV_GEOM_NUM_VERTICES) {
        _uvDebugPrintf("uvVtx: out of dynamic vertices\n");
        return gGeomVertexCount;
    }
    gGeomVertexCount += 1;
    vtx->unk0 = arg0;
    vtx->unk2 = arg1;
    vtx->unk4 = arg2;
    vtx->unk8 = arg3;
    vtx->unkA = arg4;
    vtx->unkC = arg5;
    vtx->unkD = arg6;
    vtx->unkE = arg7;
    vtx->unkF = arg8;
    return (s16)(gGeomVertexCount - 1);
}

void uvVtxReset(u8 flip) {
    gGeomVertexCount = 0;
    if (flip) {
        gGeomVertexToggle ^= 1;
        gGeomVertexPtrs = (uvVertex_t*)&gGeomVertexData[gGeomVertexToggle];
    }
}

void uvVtxBeginPoly(void) {
    gGeomFirstPoly = gGeomVertexCount;
}

void uvBeginGrid(void) {
    gGeomFirstGrid = gGeomVertexCount;
}

void uvBeginTmesh(void) {
    gGeomFirstTmesh = gGeomVertexCount;
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/geometry/uvEndTmesh.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/geometry/uvEndGridWide.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/geometry/uvEndGrid.s")

void uvVtxRect(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg0 < 0) {
        arg0 = 0;
    } else if (arg0 >= 0x141) {
        arg0 = 0x140;
    }
    if (arg2 < 0) {
        arg2 = 0;
    } else if (arg2 >= 0x141) {
        arg2 = 0x140;
    }
    if (arg1 < 0) {
        arg1 = 0;
    } else if (arg1 >= 0xF1) {
        arg1 = 0xF0;
    }
    if (arg3 < 0) {
        arg3 = 0;
    } else if (arg3 >= 0xF1) {
        arg3 = 0xF0;
    }
    gDPPipeSync(gGfxDisplayListHead++);
    gDPSetRenderMode(gGfxDisplayListHead++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPPipeSync(gGfxDisplayListHead++);
    gSPTextureRectangle(gGfxDisplayListHead++, arg0 << 2, (0xF0 - arg1) << 2, arg2 << 2, (0xF0 - arg3) << 2, 1, 0, 0, 0x20, 0x20);
    gDPPipeSync(gGfxDisplayListHead++);
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/geometry/uvVtxEndPoly.s")

