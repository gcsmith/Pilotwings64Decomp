#include <uv_geometry.h>
#include <uv_graphics.h>
#include <macros.h>

// TODO FIXME fix for gSPTextureRectangle, maybe due to older f3d ucode?
#undef G_RDPHALF_1
#undef G_RDPHALF_2
#define G_RDPHALF_1 (G_IMMFIRST - 12)
#define G_RDPHALF_2 (G_IMMFIRST - 13)

Vtx gGeomVertexData[2][UV_GEOM_NUM_VERTICES];
Vtx* gGeomVertexPtrs;
s16 gGeomVertexToggle;
s16 gGeomVertexCount;
s16 gGeomFirstTmesh;
s16 gGeomFirstPoly;
s16 gGeomFirstGrid;
f32 D_80296A90;
f32 D_80296A94;
UNUSED s32 D_80296A98;
s8 D_80296A9C;

extern u16 gGfxFbIndex;

void uvVtxInit(void) {
    s32 i;

    gGeomVertexToggle = gGfxFbIndex;
    gGeomVertexPtrs = gGeomVertexData[gGeomVertexToggle];

    for (i = 0; i < UV_GEOM_NUM_VERTICES; i++) {
        gGeomVertexData[0][i].v.ob[0] = 0;
        gGeomVertexData[0][i].v.ob[1] = 0;
        gGeomVertexData[0][i].v.ob[2] = 0;
        gGeomVertexData[0][i].v.flag = 0xFF;
        gGeomVertexData[0][i].v.tc[0] = 0;
        gGeomVertexData[0][i].v.tc[1] = 0;
        gGeomVertexData[0][i].v.cn[0] = 255;
        gGeomVertexData[0][i].v.cn[1] = 255;
        gGeomVertexData[0][i].v.cn[2] = 255;
        gGeomVertexData[0][i].v.cn[3] = 255;
    }

    for (i = 0; i < UV_GEOM_NUM_VERTICES; i++) {
        gGeomVertexData[1][i].v.ob[0] = 0;
        gGeomVertexData[1][i].v.ob[1] = 0;
        gGeomVertexData[1][i].v.ob[2] = 0;
        gGeomVertexData[1][i].v.flag = 0xFF;
        gGeomVertexData[1][i].v.tc[0] = 0;
        gGeomVertexData[1][i].v.tc[1] = 0;
        gGeomVertexData[1][i].v.cn[0] = 255;
        gGeomVertexData[1][i].v.cn[1] = 255;
        gGeomVertexData[1][i].v.cn[2] = 255;
        gGeomVertexData[1][i].v.cn[3] = 255;
    }

    gGeomVertexCount = 0;
    D_80296A90 = 1.0f;
    D_80296A94 = 1.0f;
    D_80296A9C = 0;
}

s16 uvVtx(s32 x, s32 y, s32 z, s32 s, s32 t, s32 r, s32 g, s32 b, s32 a) {
    Vtx* vtx;

    vtx = &gGeomVertexPtrs[gGeomVertexCount];
    if (gGeomVertexCount >= UV_GEOM_NUM_VERTICES) {
        _uvDebugPrintf("uvVtx: out of dynamic vertices\n");
        return gGeomVertexCount;
    }
    gGeomVertexCount += 1;
    vtx->v.ob[0] = x;
    vtx->v.ob[1] = y;
    vtx->v.ob[2] = z;
    vtx->v.tc[0] = s;
    vtx->v.tc[1] = t;
    vtx->v.cn[0] = r;
    vtx->v.cn[1] = g;
    vtx->v.cn[2] = b;
    vtx->v.cn[3] = a;
    return gGeomVertexCount - 1;
}

void uvVtxReset(u8 flip) {
    gGeomVertexCount = 0;
    if (flip) {
        gGeomVertexToggle ^= 1;
        gGeomVertexPtrs = gGeomVertexData[gGeomVertexToggle];
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

void uvEndTmesh(void) {
    s16 var_a3;
    s16 var_t3;
    s16 var_t4;
    s16 i;
    u8 var_t0;

    var_t3 = gGeomVertexCount - gGeomFirstTmesh;
    var_t0 = 0;
    if (var_t3 < 3) {
        _uvDebugPrintf("uvEndTmesh: not enough vertices -- 3 required\n");
        return;
    }
    var_t4 = gGeomFirstTmesh;
    while (var_t3 > 0) {
        if (var_t3 < 16) {
            var_a3 = var_t3;
        } else {
            var_a3 = 16;
        }

        gSPVertex(gGfxDisplayListHead++, OS_PHYSICAL_TO_K0(&gGeomVertexPtrs[var_t4]), var_a3, 0);
        var_t3 -= var_a3;
        var_a3 -= 2;
        var_t4 += var_a3;

        for (i = 0; i < var_a3; i++) {
            if (var_t0) {
                gSP1Triangle(gGfxDisplayListHead++, i, i + 2, i + 1, 0);
            } else {
                gSP1Triangle(gGfxDisplayListHead++, i, i + 1, i + 2, 0);
            }
            var_t0 ^= 1;
        }
    }
}

void uvEndGridWide(s16 arg0, s16 arg1, u8 arg2, u8 arg3) {
    s32 var_s3;
    s32 var_s4;
    s32 temp_a3;
    s32 var_t1;
    s32 var_t2;
    s32 var_t3;
    s32 var_t4;
    s32 i;
    s32 j;
    s32 pad;

    var_t1 = 0;
    var_t2 = 0;
    var_t3 = 0;
    var_s4 = gGeomFirstGrid;

    for (i = 0; i < (arg1 + arg3) - 1; i++) {
        var_t4 = 1;

        if (arg1 == i + 1) {
            var_s3 = 0;
        } else {
            var_s3 = arg0 + var_s4;
        }
        for (j = 0; j < arg0 * 2; j++) {
            if (var_t4) {
                temp_a3 = var_t2;
                var_t2 = var_t1;
                var_t1 = var_t3 % 16;
                gSPVertex(gGfxDisplayListHead++, OS_PHYSICAL_TO_K0(&gGeomVertexPtrs[var_s4] + j / 2), 1, var_t1);
                var_t3++;
                if (j >= 2) {
                    gSP1Triangle(gGfxDisplayListHead++, temp_a3, var_t2, var_t1, 0);
                }
            } else {
                temp_a3 = var_t2;
                var_t2 = var_t1;
                var_t1 = var_t3 % 16;
                gSPVertex(gGfxDisplayListHead++, OS_PHYSICAL_TO_K0(&gGeomVertexPtrs[var_s3] + j / 2), 1, var_t1);
                var_t3++;
                if (j >= 2) {
                    gSP1Triangle(gGfxDisplayListHead++, temp_a3, var_t1, var_t2, 0);
                }
            }
            var_t4 ^= 1;
        }
        if (arg2) {
            temp_a3 = var_t2;
            var_t2 = var_t1;
            var_t1 = var_t3 % 16;
            gSPVertex(gGfxDisplayListHead++, OS_PHYSICAL_TO_K0(&gGeomVertexPtrs[var_s4]), 1, var_t1);
            var_t3++;
            gSP1Triangle(gGfxDisplayListHead++, temp_a3, var_t2, var_t1, 0);

            temp_a3 = var_t2;
            var_t2 = var_t1;
            var_t1 = var_t3 % 16;
            gSPVertex(gGfxDisplayListHead++, OS_PHYSICAL_TO_K0(&gGeomVertexPtrs[var_s3]), 1, var_t1);
            var_t3++;
            gSP1Triangle(gGfxDisplayListHead++, temp_a3, var_t1, var_t2, 0);
        }
        var_s4 += arg0;
    }
}

void uvEndGrid(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 i;
    s32 j;
    u8 spC7;
    u8 spC6;
    u8 spC5;
    u8 spC4;
    u8 spC3;
    s16 spC0;
    u8 spBC[2];

    if (arg1 < arg0) {
        spC7 = arg1;
        spC6 = arg0;
        spC5 = arg3;
        spC4 = arg2;
    } else {
        spC7 = arg0;
        spC6 = arg1;
        spC5 = arg2;
        spC4 = arg3;
    }

    if (spC7 >= 9) {
        uvEndGridWide(spC7, spC6, spC4, spC5);
        return;
    }

    if (spC6 < 2) {
        _uvDebugPrintf("uvEndGrid: not enough rows or columns\n");
        return;
    }
    spBC[0] = 0;
    spBC[1] = spC7;
    spC0 = gGeomFirstGrid;

    gSPVertex(gGfxDisplayListHead++, OS_PHYSICAL_TO_K0(&gGeomVertexPtrs[spC0]), spC7, spBC[0]);

    spC0 += spC7;

    spC3 = 1;
    for (i = 1; i < spC6; i++) {
        gSPVertex(gGfxDisplayListHead++, OS_PHYSICAL_TO_K0(&gGeomVertexPtrs[spC0]), spC7, spBC[spC3]);

        if (spC3) {
            for (j = 0; j < spC7 - 1; j++) {
                gSP1Triangle(gGfxDisplayListHead++, j, j + spC7, j + spC7 + 1, 0);
                gSP1Triangle(gGfxDisplayListHead++, j, j + spC7 + 1, j + 1, 0);
            }

            if (spC5) {
                gSP1Triangle(gGfxDisplayListHead++, j, j + spC7, spC7, 0);
                gSP1Triangle(gGfxDisplayListHead++, j, spC7, 0, 0);
            }
        } else {
            for (j = 0; j < spC7 - 1; j++) {
                gSP1Triangle(gGfxDisplayListHead++, j + spC7, j, j + 1, 0);
                gSP1Triangle(gGfxDisplayListHead++, j + spC7, j + 1, j + spC7 + 1, 0);
            }
            if (spC5) {
                gSP1Triangle(gGfxDisplayListHead++, j + spC7, 0, spC7, 0);
                gSP1Triangle(gGfxDisplayListHead++, j + spC7, j, 0, 0);
            }
        }
        spC0 += spC7;
        spC3 ^= 1;
    }

    if (spC4) {
        gSPVertex(gGfxDisplayListHead++, OS_PHYSICAL_TO_K0(&gGeomVertexPtrs[gGeomFirstGrid]), spC7, spBC[0]);

        for (j = 0; j < spC7 - 1; j++) {
            gSP1Triangle(gGfxDisplayListHead++, j + spC7, j, j + 1, 0);
            gSP1Triangle(gGfxDisplayListHead++, j + spC7, j + 1, j + spC7 + 1, 0);
        }

        if (spC5) {
            gSP1Triangle(gGfxDisplayListHead++, j + spC7, 0, spC7, 0);
            gSP1Triangle(gGfxDisplayListHead++, j + spC7, j, 0, 0);
        }
    }
}

void uvVtxRect(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg0 < 0) {
        arg0 = 0;
    } else if (arg0 > 320) {
        arg0 = 320;
    }
    if (arg2 < 0) {
        arg2 = 0;
    } else if (arg2 > 320) {
        arg2 = 320;
    }
    if (arg1 < 0) {
        arg1 = 0;
    } else if (arg1 > 240) {
        arg1 = 240;
    }
    if (arg3 < 0) {
        arg3 = 0;
    } else if (arg3 > 240) {
        arg3 = 240;
    }
    gDPPipeSync(gGfxDisplayListHead++);
    gDPSetRenderMode(gGfxDisplayListHead++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPPipeSync(gGfxDisplayListHead++);
    gSPTextureRectangle(gGfxDisplayListHead++, arg0 << 2, (240 - arg1) << 2, arg2 << 2, (240 - arg3) << 2, 1, 0, 0, 0x20, 0x20);
    gDPPipeSync(gGfxDisplayListHead++);
}

void uvVtxEndPoly(void) {
    s16 var_a2;
    s16 var_t4;
    s16 var_t5;
    s16 var_v0;
    s16 i;

    var_t4 = gGeomVertexCount - gGeomFirstPoly;
    var_t5 = gGeomFirstPoly;
    if (var_t4 < 3) {
        _uvDebugPrintf("uvVtxEndPoly: not enough vertices\n");
        return;
    }

    while (var_t4 > 0) {
        if (var_t5 == gGeomFirstPoly) {
            if (var_t4 < 16) {
                var_v0 = var_t4;
            } else {
                var_v0 = 16;
            }
            gSPVertex(gGfxDisplayListHead++, OS_PHYSICAL_TO_K0(&gGeomVertexPtrs[var_t5]), var_v0, 0);
            var_a2 = var_v0 - 2;
        } else {
            if (var_t4 >= 15) {
                var_v0 = 15;
                gSPVertex(gGfxDisplayListHead++, OS_PHYSICAL_TO_K0(&gGeomVertexPtrs[var_t5]), 14, 1);
                gSP1Triangle(gGfxDisplayListHead++, 0, 15, 1, 0);
                gSPVertex(gGfxDisplayListHead++, (((u32)(&gGeomVertexPtrs[var_t5]) + 0x80000000)) + 14 * sizeof(Vtx), 1, 15);
            } else {
                var_v0 = var_t4;
                gSPVertex(gGfxDisplayListHead++, OS_PHYSICAL_TO_K0(&gGeomVertexPtrs[var_t5]), var_v0, 1);
                gSP1Triangle(gGfxDisplayListHead++, 0, 15, 1, 0);
            }
            var_a2 = var_v0 - 1;
        }
        var_t5 += var_v0;
        var_t4 -= var_v0;
        for (i = 0; i < var_a2; i++) {
            gSP1Triangle(gGfxDisplayListHead++, 0, i + 1, i + 2, 0);
        }
    }
}
