#include <uv_audio.h>
#include <uv_clocks.h>
#include <uv_dobj.h>
#include <uv_fx.h>
#include <uv_geometry.h>
#include <uv_graphics.h>
#include <uv_memory.h>
#include <uv_sched.h>
#include <uv_sprite.h>
#include <uv_system.h>
#include <macros.h>
#include <libc/stdint.h>

#define TASK_OUTPUT_BUFFER_SIZE 0x2000

u8 gGfxTaskOutputBuffer[TASK_OUTPUT_BUFFER_SIZE + 8];
u8* gGfxTaskOutputBufferStart;
u8* gGfxTaskOutputBufferEnd;
Gfx* gGfxDisplayListHead;
s32 gGfxNumVtxTransforms[2];
s32 gGfxNumTriangles[2];
s32 gGfxNumTxtLoads[2];
s32 gGfxNumMtxLoads[2];
s32 gGfxNumMtxLoadMults[2];
s32 gGfxNumLooks;
LookAt gGfxLooks[2][UV_GFX_NUM_LOOKS];
u32 gGfxStateStackData;
u32 gGfxBoundTexture;
u8* gGfxFbPtrs[2];
u8* D_80299278;
Gfx gGfxDisplayListBase[2][4200];
uvGfxViewport_t gGfxViewports[4];
s16 gGfxViewX0;
s16 gGfxViewX1;
s16 gGfxViewY0;
s16 gGfxViewY1;
Mtx gGfxMstack[2][UV_GFX_NUM_MATRICES];
Mtx4F gGfxLookTransform;
u32 gGfxStateStack[32];
u8 gGfxStateStackIdx;
OSScTask* gGfxTaskPtr;
OSScTask gGfxTasks[2];
u8 gGfxYieldData[OS_YIELD_DATA_SIZE];

STATIC_DATA Gfx gGfxDList1[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPPipelineMode(G_PM_NPRIMITIVE),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_PASS2),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetDepthSource(G_ZS_PIXEL),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetColorDither(G_CD_MAGICSQ),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureConvert(G_TC_FILT),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_OFF),
    gsSPEndDisplayList(),
};

STATIC_DATA Gfx gGfxDList2[] = {
    gsSPSetGeometryMode(G_SHADE), gsDPSetCycleType(G_CYC_2CYCLE), gsDPSetTextureLOD(G_TL_TILE), gsDPSetCombineMode(G_CC_SHADE, G_CC_PASS2),
    gsSPEndDisplayList(),
};

STATIC_DATA f32 gGfxFrameTime[2] = { 0, 0 };
STATIC_DATA s32 D_802491E0 = 0;
STATIC_DATA s32 D_802491E4 = 0xFFFFFFFF;
STATIC_DATA s32 D_802491E8 = 0;
STATIC_DATA s32 gGfxGammaEnabled = FALSE;
STATIC_DATA void* gGfxFbCurrPtr = NULL;
STATIC_DATA u8 gGfxZBufferEnabled = FALSE;   // [4] = { 0, 0, 0, 0 };
STATIC_DATA s8 gGfxCullFrontEnabled = FALSE; // [4] = { 0, 0, 0, 0 };
STATIC_DATA s8 gGfxCullBackEnabled = TRUE;   // [4] = { 0, 0, 0, 0 };

s32 gGfxSyncNeeded = FALSE;
s32 gGfxBeginFlag = FALSE;
f32 gGfxFogFactor = 0;
u16 gGfxFbIndex = 0;
s32 gGfxElementCount = 0;
s32 gGfxFrameCount = 0;
s16 gGfxMstackIdx = 0xFFFF;
f32 gGfxFrameTimeFixed = -1;

UNUSED Vp D_80249220 = { 640, 480, 511, 0, 640, 480, 511, 0 };

STATIC_DATA uvGfxCallback_t gGfxCallback = NULL;

extern OSMesgQueue D_802C3B90;
extern u64 gGfxDramStack[];
extern u8 D_80269B80[300];
extern s16 gGeomVertexCount;

#define ALIGNED_BUFFER(buffer) (((uintptr_t)(buffer) & 0xF) ? buffer + 8 : buffer)

void uvGfxInit(void) {
    u8 i;

    gGfxNumVtxTransforms[0] = gGfxNumVtxTransforms[1] = 0;
    gGfxNumTriangles[0] = gGfxNumTriangles[1] = 0;
    gGfxNumTxtLoads[0] = gGfxNumTxtLoads[1] = 0;
    gGfxNumMtxLoads[0] = gGfxNumMtxLoads[1] = 0;
    gGfxNumMtxLoadMults[0] = gGfxNumMtxLoadMults[1] = 0;
    gGfxFbPtrs[0] = 0x800DA800;
    gGfxFbPtrs[1] = 0x80100000;
    D_80299278 = 0x803DA800;
    gGfxFbIndex = 0;
    gGfxDisplayListHead = gGfxDisplayListBase[gGfxFbIndex];
    gGfxFbCurrPtr = gGfxFbPtrs[gGfxFbIndex];
    gGfxTaskPtr = &gGfxTasks[gGfxFbIndex];
    // clang-format off: must preserve same line assignments
    gGfxViewX0 = 2; gGfxViewX1 = SCREEN_WIDTH - 2;
    gGfxViewY0 = 2; gGfxViewY1 = SCREEN_HEIGHT - 2;
    // clang-format on

    for (i = 0; i < 2; i++) {
        uvGfxClipViewport(i, gGfxViewX0, gGfxViewX1, gGfxViewY0, gGfxViewY1);
    }
    uvMat4SetIdentity(&gGfxLookTransform);
    gGfxStateStackIdx = 0;
    gGfxFrameTime[0] = gGfxFrameTime[1] = 0.0f;
    uvGfxEnableGamma(0);
    gGfxTaskOutputBufferStart = ALIGNED_BUFFER(gGfxTaskOutputBuffer);
    gGfxTaskOutputBufferEnd = gGfxTaskOutputBufferStart + TASK_OUTPUT_BUFFER_SIZE;
}

void uvGfxBegin(void) {
    if (gGfxBeginFlag == TRUE) {
        _uvDebugPrintf("uvGfxBegin: 2 calls in a row.  Must call uvGfxEnd first\n");
        return;
    }
    gGfxBeginFlag = TRUE;
    uvEventPost(0, 0);
    gSPSegment(gGfxDisplayListHead++, 0x00, 0x00000000);
    gDPSetColorImage(gGfxDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, osVirtualToPhysical(gGfxFbCurrPtr));

    uvGfxResetState();
    uvSeqUpdateAll();
    uvSprt_802301A4();
    uvVtxReset(1);
    uvFx_8021A298();

    gGfxNumVtxTransforms[gGfxFbIndex] = 0;
    gGfxNumTriangles[gGfxFbIndex] = 0;
    gGfxNumTxtLoads[gGfxFbIndex] = 0;
    gGfxNumMtxLoads[gGfxFbIndex] = 0;
    gGfxNumMtxLoadMults[gGfxFbIndex] = 0;
    gGfxNumLooks = 0;
}

void uvGfxSetFogFactor(f32 factor) {
    if (factor < 0.0f) {
        factor = 0.0f;
    } else if (factor > 0.996f) {
        factor = 0.996f;
    }

    gGfxFogFactor = factor;
    if (factor > 0.0f) {
        gSPSetGeometryMode(gGfxDisplayListHead++, G_FOG);
        gSPFogPosition(gGfxDisplayListHead++, (s32)(gGfxFogFactor * 1000.0f), 1000);
    } else {
        gSPClearGeometryMode(gGfxDisplayListHead++, G_FOG);
    }
}

void uvGfxResetState(void) {
    if (gGfxFogFactor > 0.0f) {
        gSPSetGeometryMode(gGfxDisplayListHead++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH);
    } else {
        gSPSetGeometryMode(gGfxDisplayListHead++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
    }
    gSPDisplayList(gGfxDisplayListHead++, &gGfxDList1);
    gDPSetDepthImage(gGfxDisplayListHead++, D_80299278);
    gDPSetDepthImage(gGfxDisplayListHead++, osVirtualToPhysical(D_80299278));

    gGfxStateStackData = GFX_STATE_AA | GFX_STATE_CULL_BACK | GFX_STATE_GOURAUD | GFX_STATE_TEXTURE_NONE;
    gGfxBoundTexture = GFX_STATE_TEXTURE_NONE;
    D_802491E0 = 0;
    D_802491E4 = -1;
    uvGfxSetFogFactor(gGfxFogFactor);
}

void uvGfxMtxView(Mtx src) {
    uvGfxMstackPushL(src);
    gSPMatrix(gGfxDisplayListHead++, osVirtualToPhysical(uvGfxMstackTop()), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gGfxNumMtxLoads[gGfxFbIndex]++;
}

void uvGfxMtxProj(Mtx src) {
    uvGfxMstackPushL(src);
    gSPMatrix(gGfxDisplayListHead++, osVirtualToPhysical(uvGfxMstackTop()), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gGfxNumMtxLoads[gGfxFbIndex]++;
}

void uvGfxDisplayList(Gfx* dl) {
    gSPDisplayList(gGfxDisplayListHead++, dl);
}

void uvGfxStateDrawDL(uvGfxState_t* arg0) {
    Mtx4F temp;

    gDPPipeSync(gGfxDisplayListHead++);
    gSPClearGeometryMode(gGfxDisplayListHead++, G_CULL_BACK | G_LIGHTING);
    gSPSetGeometryMode(gGfxDisplayListHead++, G_ZBUFFER | G_SHADE | G_CULL_FRONT);
    gDPSetCycleType(gGfxDisplayListHead++, G_CYC_2CYCLE);
    gDPSetTextureLOD(gGfxDisplayListHead++, G_TL_TILE);
    gDPSetCombineLERP(gGfxDisplayListHead++, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED);
    gDPPipeSync(gGfxDisplayListHead++);
    gDPSetRenderMode(gGfxDisplayListHead++, G_RM_PASS, G_RM_ZB_XLU_SURF2);
    gDPSetColorImage(gGfxDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, osVirtualToPhysical(D_80299278));

    uvMat4SetIdentity(&temp);
    uvGfxMtxViewMul(&temp, 1);
    gSPDisplayList(gGfxDisplayListHead++, arg0->dlist);
    uvGfxMtxViewPop();

    gDPPipeSync(gGfxDisplayListHead++);
    gDPSetColorImage(gGfxDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, osVirtualToPhysical(gGfxFbCurrPtr));
    gDPSetCombineMode(gGfxDisplayListHead++, G_CC_SHADE, G_CC_PASS2);
    gDPSetRenderMode(gGfxDisplayListHead++, G_RM_PASS, G_RM_ZB_XLU_SURF2);
    gSPClearGeometryMode(gGfxDisplayListHead++, G_CULL_FRONT);
    gSPSetGeometryMode(gGfxDisplayListHead++, G_CULL_BACK);
    gSPDisplayList(gGfxDisplayListHead++, arg0->dlist);

    gGfxNumVtxTransforms[gGfxFbIndex] += arg0->xfmCount * 2;
    gGfxNumTriangles[gGfxFbIndex] += arg0->triCount * 2;
}

void uvGfxStateDraw(uvGfxState_t* arg0) {
    u32 clearMode;
    u32 setMode;
    u16 textureId;
    ParsedUVTX* uvtx;
    u16 var_t1;
    s32 renderMask;
    u32 var_a1_2;
    u32 renderMode1;
    u32 renderMode2;
    u32 var_a3;

    var_a3 = arg0->state;
    if (gGfxFogFactor > 0.0f) {
        var_a3 |= GFX_STATE_FOG | GFX_STATE_GOURAUD;
    }
    var_a3 |= D_802491E0;
    var_a3 &= D_802491E4;

    if (var_a3 & GFX_STATE_2000000) {
        uvGfxStateDrawDL(arg0);
        return;
    }
    if (var_a3 != gGfxStateStackData) {
        gDPPipeSync(gGfxDisplayListHead++);
        if ((var_a3 & GFX_STATE_MODE_MASK) != (gGfxStateStackData & GFX_STATE_MODE_MASK)) {
            setMode = 0;
            clearMode = 0;
            if (var_a3 & GFX_STATE_LIGHTING) {
                setMode = G_TEXTURE_GEN | G_LIGHTING;
            } else {
                clearMode = G_TEXTURE_GEN | G_LIGHTING;
            }
            if (var_a3 & GFX_STATE_CULL_BACK) {
                setMode |= G_CULL_BACK;
            } else {
                clearMode |= G_CULL_BACK;
            }
            if (var_a3 & GFX_STATE_CULL_FRONT) {
                setMode |= G_CULL_FRONT;
            } else {
                clearMode |= G_CULL_FRONT;
            }
            if (var_a3 & GFX_STATE_GOURAUD) {
                setMode |= G_SHADING_SMOOTH;
            } else {
                clearMode |= G_SHADING_SMOOTH;
            }
            if (var_a3 & GFX_STATE_ZBUFFER) {
                setMode |= G_ZBUFFER;
            } else {
                clearMode |= G_ZBUFFER;
            }
            if (var_a3 & GFX_STATE_FOG) {
                setMode |= G_FOG;
            } else {
                clearMode |= G_FOG;
            }
            if (clearMode != 0) {
                gSPClearGeometryMode(gGfxDisplayListHead++, clearMode);
            }
            if (setMode != 0) {
                gSPSetGeometryMode(gGfxDisplayListHead++, setMode);
            }
        }
        textureId = var_a3 & GFX_STATE_TEXTURE_MASK;

        if (textureId == 0xFFE) {
            textureId++;
        }

        if (textureId >= GFX_STATE_TEXTURE_NONE) {
            var_t1 = GFX_STATE_TEXTURE_NONE;
        } else {
            uvtx = gGfxUnkPtrs->textures[textureId];
            if (uvtx == NULL) {
                _uvDebugPrintf("uvGfxStateDraw: texture %d not in level\n", textureId);
                var_t1 = GFX_STATE_TEXTURE_NONE;
                textureId = GFX_STATE_TEXTURE_NONE;
            } else {
                var_t1 = (uvtx->unk12 & 0xF000) | textureId;
            }
        }

        if (gGfxBoundTexture != var_t1) {
            if (textureId >= 0xFFE) {
                gSPDisplayList(gGfxDisplayListHead++, gGfxDList2);
            } else {
                _uvTxtDraw(textureId);
                gGfxNumTxtLoads[gGfxFbIndex]++;
                if (var_a3 & GFX_STATE_LIGHTING) {
                    gDPSetCombineMode(gGfxDisplayListHead++, G_CC_DECALRGB, G_CC_DECALRGB2);
                    gSPTexture(gGfxDisplayListHead++, 0x7C0, 0x7C0, 0, 1, G_ON);
                }
            }
        }
        if (var_a3 & GFX_STATE_DECAL) {
            var_a1_2 = 0x10;
        } else {
            var_a1_2 = 0;
        }

        uvGfxTextureDL(textureId, var_a1_2);

        renderMask = GFX_STATE_DECAL | GFX_STATE_XLU | GFX_STATE_AA | GFX_STATE_ZBUFFER;
        switch (var_a3 & renderMask) {
        case GFX_STATE_DECAL | GFX_STATE_XLU | GFX_STATE_AA:
        case GFX_STATE_DECAL | GFX_STATE_XLU | GFX_STATE_AA | GFX_STATE_ZBUFFER:
            renderMode2 = G_RM_AA_ZB_XLU_DECAL2;
            break;
        case GFX_STATE_DECAL | GFX_STATE_XLU:
        case GFX_STATE_DECAL | GFX_STATE_XLU | GFX_STATE_ZBUFFER:
            renderMode2 = G_RM_ZB_XLU_DECAL2;
            break;
        case GFX_STATE_DECAL | GFX_STATE_AA:
        case GFX_STATE_DECAL | GFX_STATE_AA | GFX_STATE_ZBUFFER:
            renderMode2 = G_RM_AA_ZB_OPA_DECAL2;
            break;
        case GFX_STATE_DECAL:
        case GFX_STATE_DECAL | GFX_STATE_ZBUFFER:
            renderMode2 = G_RM_ZB_OPA_DECAL2;
            break;
        case GFX_STATE_XLU | GFX_STATE_AA | GFX_STATE_ZBUFFER:
            if (textureId == GFX_STATE_TEXTURE_NONE) {
                renderMode2 = G_RM_AA_ZB_XLU_INTER2;
            } else if ((uvtx->unk12 & 0x8000) || (uvtx->unk22 == 1) || (var_a3 & 0x04000000)) {
                renderMode2 = G_RM_AA_ZB_XLU_SURF2;
            } else {
                renderMode2 = G_RM_AA_ZB_TEX_TERR2;
            }
            break;
        case GFX_STATE_XLU | GFX_STATE_AA:
            if (textureId == GFX_STATE_TEXTURE_NONE) {
                renderMode2 = G_RM_AA_XLU_SURF2;
            } else if (uvtx->unk12 & 0x8000) {
                renderMode2 = G_RM_AA_XLU_SURF2;
            } else {
                renderMode2 = G_RM_AA_TEX_TERR2;
            }
            break;
        case GFX_STATE_XLU | GFX_STATE_ZBUFFER:
            if (textureId == GFX_STATE_TEXTURE_NONE) {
                renderMode2 = G_RM_ZB_XLU_SURF2;
            } else {
                renderMode2 = G_RM_ZB_XLU_SURF2;
            }
            break;
        case GFX_STATE_AA | GFX_STATE_ZBUFFER:
            renderMode2 = G_RM_AA_ZB_OPA_TERR2;
            break;
        case GFX_STATE_ZBUFFER:
            renderMode2 = G_RM_ZB_OPA_SURF2;
            break;
        case GFX_STATE_AA:
            renderMode2 = G_RM_AA_OPA_TERR2;
            break;
        case GFX_STATE_XLU:
            renderMode2 = G_RM_XLU_SURF2;
            break;
        case 0x0:
            renderMode2 = G_RM_OPA_SURF2;
            break;
        default:
            _uvDebugPrintf("uvGfxStateDraw: unknown case 0x%x\n", var_a3 & renderMask);
            renderMode2 = G_RM_OPA_SURF2;
            break;
        }
        if (var_a3 & GFX_STATE_FOG) {
            renderMode1 = G_RM_FOG_SHADE_A;
        } else {
            renderMode1 = G_RM_PASS;
        }
        if (var_a3 & GFX_STATE_10000000) {
            renderMode2 = Z_CMP | Z_UPD | IM_RD | CLR_ON_CVG | CVG_DST_SAVE | ZMODE_OPA | GBL_c2(G_BL_CLR_MEM, G_BL_A_FOG, G_BL_CLR_MEM, G_BL_A_MEM);
        }

        gDPSetRenderMode(gGfxDisplayListHead++, renderMode1, renderMode2);

        gGfxBoundTexture = var_t1;
        gGfxStateStackData = var_a3;
    }
    if ((var_a3 & GFX_STATE_FOG) && ((var_a3 & renderMask) == (GFX_STATE_XLU | GFX_STATE_AA | GFX_STATE_ZBUFFER))) {
        if (textureId == GFX_STATE_TEXTURE_NONE) {
            gDPSetCombineMode(gGfxDisplayListHead++, G_CC_SHADE, G_CC_PASS2);
        } else {
            gDPSetCombineMode(gGfxDisplayListHead++, G_CC_MODULATEIDECALA, G_CC_PASS2);
        }
    }
    if (arg0->dlist != NULL) {
        gSPDisplayList(gGfxDisplayListHead++, arg0->dlist);

        gGfxNumVtxTransforms[gGfxFbIndex] += arg0->xfmCount;
        gGfxNumTriangles[gGfxFbIndex] += arg0->triCount;
    }
}

void uvGfxPushMtxUnk(Mtx4F* arg0) {
    Mtx spC8;
    Mtx4F sp88;
    Mtx4F sp48;

    uvMat4Copy(&gGfxLookTransform, arg0);
    uvMat4Copy(&sp48, &gGfxLookTransform);
    uvMat4SetIdentity(&sp88);
    uvMat4RotateAxis(&sp88, -1.5707963f, 'x');
    uvMat4Mul(&gGfxLookTransform, &sp48, &sp88);
    uvMat4SetIdentityL(&spC8);
    uvGfxMtxView(spC8);
}

void uvGfxClampLook(LookAt* lookAt, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9) {
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 temp_fv0_2;

    sp58 = arg4 - arg1;
    sp54 = arg5 - arg2;
    sp50 = arg6 - arg3;

    temp_fv0_2 = sqrtf(SQ(sp58) + SQ(sp54) + SQ(sp50));
    if (temp_fv0_2 != 0.0f) {
        sp5C = -1.0f / temp_fv0_2;
    } else {
        // clang-format off
        sp5C = -255.0f; \
        _uvDebugPrintf("clamping 1\n");
        // clang-format on
    }
    sp58 *= sp5C;
    sp54 *= sp5C;
    sp50 *= sp5C;

    sp4C = (arg8 * sp50) - (arg9 * sp54);
    sp48 = (arg9 * sp58) - (arg7 * sp50);
    sp44 = (arg7 * sp54) - (arg8 * sp58);

    temp_fv0_2 = sqrtf(SQ(sp4C) + SQ(sp48) + SQ(sp44));
    if (temp_fv0_2 != 0.0f) {
        sp5C = 1.0f / temp_fv0_2;
    } else {
        // clang-format off
        sp5C = 255.0f; \
        _uvDebugPrintf("clamping 1\n");
        // clang-format on
    }
    sp4C *= sp5C;
    sp48 *= sp5C;
    sp44 *= sp5C;

    arg7 = (sp54 * sp44) - (sp50 * sp48);
    arg8 = (sp50 * sp4C) - (sp58 * sp44);
    arg9 = (sp58 * sp48) - (sp54 * sp4C);

    temp_fv0_2 = sqrtf(SQ(arg7) + SQ(arg8) + SQ(arg9));
    if (temp_fv0_2 != 0.0f) {
        sp5C = 1.0f / temp_fv0_2;
    } else {
        // clang-format off
        sp5C = 255.0f; \
        _uvDebugPrintf("clamping 1\n");
        // clang-format on
    }
    arg7 *= sp5C;
    arg8 *= sp5C;
    arg9 *= sp5C;

    lookAt->l[0].l.dir[0] = (s32)MIN(sp4C * 128.0, 127.0) & 0xFF;
    lookAt->l[0].l.dir[1] = (s32)MIN(sp48 * 128.0, 127.0) & 0xFF;
    lookAt->l[0].l.dir[2] = (s32)MIN(sp44 * 128.0, 127.0) & 0xFF;

    lookAt->l[1].l.dir[0] = (s32)MIN(arg7 * 128.0, 127.0) & 0xFF;
    lookAt->l[1].l.dir[1] = (s32)MIN(arg8 * 128.0, 127.0) & 0xFF;
    lookAt->l[1].l.dir[2] = (s32)MIN(arg9 * 128.0, 127.0) & 0xFF;
    lookAt->l[0].l.col[0] = 0;
    lookAt->l[0].l.col[1] = 0;
    lookAt->l[0].l.col[2] = 0;
    lookAt->l[0].l.pad1 = 0;
    lookAt->l[0].l.colc[0] = 0;
    lookAt->l[0].l.colc[1] = 0;
    lookAt->l[0].l.colc[2] = 0;
    lookAt->l[0].l.pad2 = 0;
    lookAt->l[1].l.col[0] = 0;
    lookAt->l[1].l.col[1] = 128;
    lookAt->l[1].l.col[2] = 0;
    lookAt->l[1].l.pad1 = 0;
    lookAt->l[1].l.colc[0] = 0;
    lookAt->l[1].l.colc[1] = 128;
    lookAt->l[1].l.colc[2] = 0;
    lookAt->l[1].l.pad2 = 0;
}

void uvGfxLookAt(Mtx4F* arg0) {
    Mtx4F temp;

    if (gGfxNumLooks >= UV_GFX_NUM_LOOKS) {
        _uvDebugPrintf("too many looks\n");
        return;
    }

    uvMat4InvertTranslationRotation(&temp, &gGfxLookTransform);
    uvGfxClampLook(&gGfxLooks[gGfxFbIndex][gGfxNumLooks], temp.m[3][0], temp.m[3][1], temp.m[3][2], arg0->m[3][0], arg0->m[3][1], arg0->m[3][2], 0.0f, 1.0f,
                   0.0f);
    gSPLookAt(gGfxDisplayListHead++, &gGfxLooks[gGfxFbIndex][gGfxNumLooks]);
    gGfxNumLooks++;
}

void uvGfxMtxProjPushF(Mtx4F* arg0) {
    Mtx sp48;
    uvMat4CopyF2L(&sp48, arg0);
    uvGfxMtxProj(sp48);
}

void uvGfxSetCallback(uvGfxCallback_t cb) {
    gGfxCallback = cb;
}

void uvGfxEnd(void) {
    static s32 sDisplayListNumElements = 4000;
    static s32 sDisplayListNumDBMtxs = 294;
    static s32 sObjectNumPartTransforms = 200;
    static s32 sObjectNumDobjs = 100;
    static s32 D_80249244 = 120;
    static s32 sGeomNumDBVtxs = 800;
    static s32 D_8024924C = 0;
    s32 i;
    s32 pad[4];
    u8* fb;
    s32 var_a2;
    s32 var_t0;
    s32 var_t1;
    s32 var_a1;
    OSTask* task;

    if (gGfxBeginFlag == FALSE) {
        _uvDebugPrintf("uvGfxEnd: must be called after a uvGfxBegin()\n");
        return;
    }
    gGfxBeginFlag = FALSE;
    gDPFullSync(gGfxDisplayListHead++);
    gSPEndDisplayList(gGfxDisplayListHead++);
    gGfxElementCount = (gGfxDisplayListHead - (gGfxDisplayListBase[gGfxFbIndex]));

    if (gGfxElementCount >= 4200) {
        _uvDebugPrintf("display list overflow %d / %d\n", gGfxElementCount, 4200);
        return;
    }
    gGfxTaskPtr->framebuffer = gGfxFbPtrs[gGfxFbIndex];
    gGfxTaskPtr->next = NULL;
    gGfxTaskPtr->msgQ = &D_802C3B90;
    gGfxTaskPtr->msg = &D_8024B260;
    gGfxTaskPtr->flags = OS_SC_SWAPBUFFER | OS_SC_PARALLEL_TASK | OS_SC_NEEDS_RSP | OS_SC_NEEDS_RDP;
    task = &gGfxTasks[gGfxFbIndex].list;
    task->t.type = M_GFXTASK;
    task->t.flags = 0;
    task->t.ucode_boot = (u64*)rspbootTextStart;
    task->t.ucode_boot_size = (uintptr_t)rspbootTextEnd - (uintptr_t)rspbootTextStart;
    task->t.ucode = (u64*)gspF3DEX_fifoTextStart;
    task->t.ucode_data = (u64*)gspF3DEX_fifoDataStart;
    task->t.ucode_size = SP_UCODE_SIZE;
    task->t.ucode_data_size = SP_UCODE_DATA_SIZE;
    task->t.dram_stack = gGfxDramStack;
    task->t.dram_stack_size = SP_DRAM_STACK_SIZE8;
    task->t.data_ptr = (u64*)gGfxDisplayListBase[gGfxFbIndex];
    task->t.data_size = gGfxElementCount * sizeof(Gfx);
    task->t.yield_data_ptr = (u64*)gGfxYieldData;
    task->t.yield_data_size = OS_YIELD_DATA_SIZE;
    task->t.ucode = (u64*)gspFast3DTextStart;
    task->t.ucode_data = (u64*)gspFast3DDataStart;
    task->t.output_buff = (u64*)gGfxTaskOutputBufferStart;
    task->t.output_buff_size = (u64*)gGfxTaskOutputBufferEnd;
    uvSc_8022C3C0(0, 0x2B);
    osSendMesg(_uvScGetCmdQ(&gSchedInst), gGfxTaskPtr, 1);
    uvEventPost(1, 0);
    if (gGfxFrameCount == 0) {
        osViBlack(FALSE);
    } else if (gGfxSyncNeeded != FALSE) {
        uvWaitForMesg(UV_MESG_GFX);
    }
    gGfxSyncNeeded = TRUE;
    fb = gGfxFbPtrs[gGfxFbIndex ^ 1];
    if (gGfxCallback != NULL) {
        gGfxCallback(fb, D_80299278);
        osWritebackDCache(fb, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(u16));
    }
    gGfxFrameTime[gGfxFbIndex] = (f32)uvClkGetSec(UV_CLKID_GFX);
    uvClkReset(UV_CLKID_GFX);
    uvSc_8022C3C0(0, 0x2A);
    var_a2 = 0;
    var_t0 = 0;
    var_t1 = 0;
    var_a1 = FALSE;

    for (i = 0; i < 300; i++) {
        if (D_80269B80[i] != 0) {
            var_a2++;
        }
    }

    for (i = 0; i < 100; i++) {
        if (D_80263780[i].modelId != 0xFFFF) {
            var_t0++;
        }
    }

    for (i = 0; i < 120; i++) {
        if (D_8028B400[i].unk4 != 0) {
            var_t1++;
        }
    }
    if (sDisplayListNumElements < gGfxElementCount) {
        sDisplayListNumElements = gGfxElementCount;
        var_a1 = TRUE;
    }
    if (sDisplayListNumDBMtxs < gGfxMstackIdx) {
        sDisplayListNumDBMtxs = gGfxMstackIdx;
        var_a1 = TRUE;
    }
    if (sObjectNumPartTransforms < var_a2) {
        sObjectNumPartTransforms = var_a2;
        var_a1 = TRUE;
    }
    if (sObjectNumDobjs < var_t0) {
        sObjectNumDobjs = var_t0;
        var_a1 = TRUE;
    }
    if (D_80249244 < var_t1) {
        D_80249244 = var_t1;
        var_a1 = TRUE;
    }
    if (sGeomNumDBVtxs < gGeomVertexCount) {
        sGeomNumDBVtxs = gGeomVertexCount;
        var_a1 = TRUE;
    }
    if (var_a1) {
        _uvDebugPrintf("\nGFXEND :\n");
        _uvDebugPrintf("DL_ELEMENTS :  %d", sDisplayListNumElements);
        if (sDisplayListNumElements == gGfxElementCount) {
            _uvDebugPrintf(" <==== WINNER");
        }

        _uvDebugPrintf("\n");
        _uvDebugPrintf("DL_NDBMTXS  :  %d", sDisplayListNumDBMtxs);
        if (sDisplayListNumDBMtxs == gGfxMstackIdx) {
            _uvDebugPrintf(" <==== WINNER");
        }
        _uvDebugPrintf("\n");
        _uvDebugPrintf("OBJ_NPXFMS  :  %d", sObjectNumPartTransforms);
        if (var_a2 == sObjectNumPartTransforms) {
            _uvDebugPrintf(" <==== WINNER");
        }
        _uvDebugPrintf("\n");
        _uvDebugPrintf("OBJ_NDOBJS  :  %d", sObjectNumDobjs);
        if (var_t0 == sObjectNumDobjs) {
            _uvDebugPrintf(" <==== WINNER");
        }
        _uvDebugPrintf("\n");
        _uvDebugPrintf("FX_NFX      :  %d", D_80249244);
        if (var_t1 == D_80249244) {
            _uvDebugPrintf(" <==== WINNER");
        }
        _uvDebugPrintf("\n");
        _uvDebugPrintf("GEOM_NDBVTXS:  %d", sGeomNumDBVtxs);
        if (sGeomNumDBVtxs == gGeomVertexCount) {
            _uvDebugPrintf(" <==== WINNER");
        }
        _uvDebugPrintf("\n");
    }

    gGfxFbIndex ^= 1;
    gGfxMstackIdx = -1;
    gGfxTaskPtr = &gGfxTasks[gGfxFbIndex];
    gGfxFbCurrPtr = gGfxFbPtrs[gGfxFbIndex];
    gGfxDisplayListHead = gGfxDisplayListBase[gGfxFbIndex];
    gGfxFrameCount++;
}

void uvGfxClearScreen(u8 r, u8 g, u8 b, u8 a) {
    gDPPipeSync(gGfxDisplayListHead++);
    gDPSetCycleType(gGfxDisplayListHead++, G_CYC_FILL);
    gDPSetColorImage(gGfxDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, osVirtualToPhysical(gGfxFbCurrPtr));
    gDPSetFillColor(gGfxDisplayListHead++, GPACK_RGBA5551(r, g, b, a) << 16 | GPACK_RGBA5551(r, g, b, a));
    gDPFillRectangle(gGfxDisplayListHead++, gGfxViewX0, (SCREEN_HEIGHT - gGfxViewY1), (gGfxViewX1 - 1), (SCREEN_HEIGHT - 1 - gGfxViewY0));
    gDPPipeSync(gGfxDisplayListHead++);
    gDPSetCycleType(gGfxDisplayListHead++, G_CYC_2CYCLE);
}

void uvGfx_80222A98(void) {
    gDPSetScissor(gGfxDisplayListHead++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    gDPPipeSync(gGfxDisplayListHead++);
    gDPSetRenderMode(gGfxDisplayListHead++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPPipeSync(gGfxDisplayListHead++);
    gDPSetCycleType(gGfxDisplayListHead++, G_CYC_FILL);
    gDPPipeSync(gGfxDisplayListHead++);
    gDPSetFillColor(gGfxDisplayListHead++, GPACK_RGBA5551(255, 255, 240, 0) << 16 | GPACK_RGBA5551(255, 255, 240, 0));
    gDPPipeSync(gGfxDisplayListHead++);
    gDPSetColorImage(gGfxDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, osVirtualToPhysical(D_80299278));
    gDPPipeSync(gGfxDisplayListHead++);
    gDPFillRectangle(gGfxDisplayListHead++, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);
    gDPPipeSync(gGfxDisplayListHead++);
    gDPSetColorImage(gGfxDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, osVirtualToPhysical(gGfxFbCurrPtr));
    gDPPipeSync(gGfxDisplayListHead++);
    gDPSetCycleType(gGfxDisplayListHead++, G_CYC_2CYCLE);
    gDPPipeSync(gGfxDisplayListHead++);
}

void uvGfxEnableZBuffer(s32 enable) {
    if (enable != FALSE) {
        gDPSetRenderMode(gGfxDisplayListHead++, G_RM_PASS, G_RM_AA_ZB_OPA_TERR2);
        gSPSetGeometryMode(gGfxDisplayListHead++, G_ZBUFFER);
        gGfxZBufferEnabled = TRUE;
        gGfxStateStackData |= GFX_STATE_ZBUFFER;
    } else {
        gDPSetRenderMode(gGfxDisplayListHead++, G_RM_PASS, G_RM_AA_OPA_TERR2);
        gSPClearGeometryMode(gGfxDisplayListHead++, G_ZBUFFER);
        gGfxZBufferEnabled = FALSE;
        gGfxStateStackData &= ~GFX_STATE_ZBUFFER;
    }
}

void uvGfxEnableCull(s32 enable_front, s32 enable_back) {
    if (enable_front != FALSE) {
        gSPSetGeometryMode(gGfxDisplayListHead++, G_CULL_FRONT);
        gGfxCullFrontEnabled = TRUE;
        gGfxStateStackData |= GFX_STATE_CULL_FRONT;
    } else {
        gSPClearGeometryMode(gGfxDisplayListHead++, G_CULL_FRONT);
        gGfxCullFrontEnabled = FALSE;
        gGfxStateStackData &= ~GFX_STATE_CULL_FRONT;
    }
    if (enable_back != 0) {
        gSPSetGeometryMode(gGfxDisplayListHead++, G_CULL_BACK);
        gGfxCullBackEnabled = TRUE;
        gGfxStateStackData |= GFX_STATE_CULL_BACK;
    } else {
        gSPClearGeometryMode(gGfxDisplayListHead++, G_CULL_BACK);
        gGfxCullBackEnabled = FALSE;
        gGfxStateStackData &= ~GFX_STATE_CULL_BACK;
    }
}

void uvGfxEnableLighting(s32 enable) {
    if (enable != 0) {
        gSPSetGeometryMode(gGfxDisplayListHead++, G_LIGHTING);
    } else {
        gSPClearGeometryMode(gGfxDisplayListHead++, G_LIGHTING);
    }
}

void uvGfxClipRect(uvGfxViewport_t* vp, s32 x0, s32 x1, s32 y0, s32 y1) {
    s32 var_a2;
    s32 var_a3;

    vp->x0 = x0;
    vp->x1 = x1;
    vp->y0 = y0;
    vp->y1 = y1;
    if (vp->x0 < 0) {
        vp->x0 = 0;
    } else if (vp->x0 > SCREEN_WIDTH) {
        vp->x0 = SCREEN_WIDTH;
    }

    if (vp->x1 < 0) {
        vp->x1 = 0;
    } else if (vp->x1 > SCREEN_WIDTH) {
        vp->x1 = SCREEN_WIDTH;
    }

    if (vp->y1 < 0) {
        vp->y1 = 0;
    } else if (vp->y1 > SCREEN_HEIGHT) {
        vp->y1 = SCREEN_HEIGHT;
    }

    if (vp->y0 < 0) {
        vp->y0 = 0;
    } else if (vp->y0 > SCREEN_HEIGHT) {
        vp->y0 = SCREEN_HEIGHT;
    }

    vp->unk0 = vp->x0 - 5;
    if (vp->unk0 < 0) {
        vp->unk0 = 0;
    }
    vp->unk2 = vp->x1 + 5;
    if (vp->unk2 > SCREEN_WIDTH - 1) {
        vp->unk2 = SCREEN_WIDTH - 1;
    }
    vp->unk4 = vp->y0 - 5;
    if (vp->unk4 < 0) {
        vp->unk4 = 0;
    }
    vp->unk6 = vp->y1 + 5;
    if (vp->unk6 > SCREEN_HEIGHT - 1) {
        vp->unk6 = SCREEN_HEIGHT - 1;
    }

    var_a2 = vp->unk2 - vp->unk0;
    var_a3 = vp->unk6 - vp->unk4;

    vp->vp.vp.vscale[0] = (var_a2 << 1);
    vp->vp.vp.vscale[1] = (var_a3 << 1);
    vp->vp.vp.vscale[2] = 0x1FF;
    vp->vp.vp.vscale[3] = 0;
    vp->vp.vp.vtrans[0] = (u16)((vp->unk0 + (var_a2 >> 1)) & 0xFFFF) << 2;
    vp->vp.vp.vtrans[1] = (u16)(((SCREEN_HEIGHT - vp->unk4) - (var_a3 >> 1)) & 0xFFFF) << 2;
    vp->vp.vp.vtrans[2] = 0x1FF;
    vp->vp.vp.vtrans[3] = 0;
    gGfxViewX0 = vp->x0;
    gGfxViewX1 = vp->x1;
    gGfxViewY0 = vp->y0;
    gGfxViewY1 = vp->y1;
}

void uvGfxClipViewport(s32 vpId, s32 x0, s32 x1, s32 y0, s32 y1) {
    uvGfxClipRect(&gGfxViewports[vpId], x0, x1, y0, y1);
}

void uvGfxSetViewport(s32 vpId, s32 x0, s32 x1, s32 y0, s32 y1) {
    uvGfxClipRect(&gGfxViewports[vpId + 2], x0, x1, y0, y1);
    uvGfxViewport(vpId + 2);
}

void uvGfxViewport(s32 vpId) {
    uvGfxViewport_t* vp;
    vp = &gGfxViewports[vpId];

    gSPViewport(gGfxDisplayListHead++, OS_PHYSICAL_TO_K0(&vp->vp));
    gDPSetScissor(gGfxDisplayListHead++, G_SC_NON_INTERLACE, vp->x0, SCREEN_HEIGHT - vp->y1, vp->x1, SCREEN_HEIGHT - vp->y0);
    gGfxViewX0 = vp->x0;
    gGfxViewX1 = vp->x1;
    gGfxViewY0 = vp->y0;
    gGfxViewY1 = vp->y1;
}

void uvGfxMstackPushF(Mtx4F* src) {
    gGfxMstackIdx++;
    if (gGfxMstackIdx >= UV_GFX_NUM_MATRICES) {
        _uvDebugPrintf("gfx : too many double buffered matrices [%d]\n", gGfxMstackIdx);
        gGfxMstackIdx--;
        return;
    }
    uvMat4CopyF2L(&gGfxMstack[gGfxFbIndex][gGfxMstackIdx], src);
}

void uvGfxMstackPushL(Mtx src) {
    gGfxMstackIdx++;
    if (gGfxMstackIdx >= UV_GFX_NUM_MATRICES) {
        _uvDebugPrintf("gfx : too many double buffered matrices [%d]\n", gGfxMstackIdx);
        gGfxMstackIdx--;
        return;
    }
    uvMat4CopyL(&gGfxMstack[gGfxFbIndex][gGfxMstackIdx], src);
}

Mtx* uvGfxMstackTop(void) {
    return &gGfxMstack[gGfxFbIndex][gGfxMstackIdx];
}

void uvGfxSetFrameTime(f32 sec) {
    gGfxFrameTimeFixed = sec;
}

f32 uvGfxGetFrameTime(void) {
    if (gGfxFrameTimeFixed > 0.0f) {
        return gGfxFrameTimeFixed;
    }
    return gGfxFrameTime[gGfxFbIndex ^ 1];
}

void uvGfxMtxViewLoad(Mtx4F* src, s32 push) {
    s32 flags;

    uvGfxMstackPushF(src);
    if (push != 0) {
        flags = G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_PUSH;
    } else {
        flags = G_MTX_MODELVIEW | G_MTX_LOAD;
    }
    gSPMatrix(gGfxDisplayListHead++, osVirtualToPhysical(uvGfxMstackTop()), flags);
    gGfxNumMtxLoads[gGfxFbIndex]++;
}

void uvGfxMtxViewMul(Mtx4F* src, s32 push) {
    s32 flags;

    uvGfxMstackPushF(src);
    if (push != 0) {
        flags = G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH;
    } else {
        flags = G_MTX_MODELVIEW | G_MTX_MUL;
    }
    gSPMatrix(gGfxDisplayListHead++, osVirtualToPhysical(uvGfxMstackTop()), flags);
    gGfxNumMtxLoads[gGfxFbIndex]++;
    gGfxNumMtxLoadMults[gGfxFbIndex]++;
}

void uvGfx_802235A4(Mtx src, u8 push) {
    s32 flags;

    uvGfxMstackPushL(src);
    if (push != 0) {
        flags = G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH;
    } else {
        flags = G_MTX_MODELVIEW | G_MTX_MUL;
    }
    gSPMatrix(gGfxDisplayListHead++, osVirtualToPhysical(uvGfxMstackTop()), flags);
    gGfxNumMtxLoads[gGfxFbIndex]++;
    gGfxNumMtxLoadMults[gGfxFbIndex]++;
}

void uvGfxMtxViewPop(void) {
    gSPPopMatrix(gGfxDisplayListHead++, G_MTX_MODELVIEW);
}

void uvGfx_802236CC(Mtx4F* arg0) {
    Mtx4F sp20;
    uvMat4MulBA(&sp20, &gGfxLookTransform, arg0);
    if (sp20.m[3][0] < -2.1e9f) {
        sp20.m[3][0] = -2.1e9f;
    } else if (sp20.m[3][0] > 2.1e9f) {
        sp20.m[3][0] = 2.1e9f;
    }
    if (sp20.m[3][1] < -2.1e9f) {
        sp20.m[3][1] = -2.1e9f;
    } else if (sp20.m[3][1] > 2.1e9f) {
        sp20.m[3][1] = 2.1e9f;
    }
    if (sp20.m[3][2] < -2.1e9f) {
        sp20.m[3][2] = -2.1e9f;
    } else if (sp20.m[3][2] > 2.1e9f) {
        sp20.m[3][2] = 2.1e9f;
    }
    uvGfxMstackPushF(&sp20);
    gSPMatrix(gGfxDisplayListHead++, osVirtualToPhysical(uvGfxMstackTop()), G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gGfxNumMtxLoads[gGfxFbIndex]++;
}

s32 uvGfxGetCnt(u32 arg0) {
    switch (arg0) {
    case GFX_COUNT_VTX_TRANSFORMS:
        return gGfxNumVtxTransforms[1 - gGfxFbIndex];
    case GFX_COUNT_TRIS:
        return gGfxNumTriangles[1 - gGfxFbIndex];
    case GFX_COUNT_TXT_LOADS:
        return gGfxNumTxtLoads[1 - gGfxFbIndex];
    case GFX_COUNT_MTX_LOADS:
        return gGfxNumMtxLoads[1 - gGfxFbIndex];
    case GFX_COUNT_MTX_LOAD_MULTS:
        return gGfxNumMtxLoadMults[1 - gGfxFbIndex];
    default:
        _uvDebugPrintf("uvGfxGetCnt: no such count type %d", arg0);
        return 0;
    }
}

void uvGfxStatePush(void) {
    if (gGfxStateStackIdx >= ARRAY_COUNT(gGfxStateStack) - 1) {
        _uvDebugPrintf("uvGfxStatePush: stack full\n");
        return;
    }
    gGfxStateStack[gGfxStateStackIdx++] = gGfxStateStackData;
}

void uvGfxStatePop(void) {
    u32 newState;
    uvGfxState_t gfxState;

    if (gGfxStateStackIdx == 0) {
        _uvDebugPrintf("uvGfxStatePop: stack empty\n");
    } else {
        --gGfxStateStackIdx;
        newState = gGfxStateStack[gGfxStateStackIdx];
        gfxState.state = newState;
        gfxState.dlist = NULL;
        uvGfxStateDraw(&gfxState);
    }
}

void uvGfxSetFlags(s32 flags) {
    u32 newState;
    uvGfxState_t gfxState;

    newState = flags | gGfxStateStackData;
    if (newState != gGfxStateStackData) {
        gfxState.state = newState;
        gfxState.dlist = NULL;
        uvGfxStateDraw(&gfxState);
    }
}

void uvGfxClearFlags(s32 flags) {
    u32 newState;
    uvGfxState_t gfxState;

    newState = ~flags & gGfxStateStackData;
    if (newState != gGfxStateStackData) {
        gfxState.state = newState;
        gfxState.dlist = NULL;
        uvGfxStateDraw(&gfxState);
    }
}

void uvGfxBindTexture(s32 flags) {
    uvGfxState_t gfxState;
    s32 pad;

    gfxState.dlist = NULL;
    gfxState.state = (gGfxStateStackData & ~GFX_STATE_TEXTURE_MASK) | flags;
    uvGfxStateDraw(&gfxState);
}

void uvGfxTextureDL(s32 textureId, s32 xparam) {
    u32 var_v0;
    u32 currTextureId;

    var_v0 = gGfxStateStackData & GFX_STATE_DECAL;
    if (xparam != 0) {
        var_v0 ^= GFX_STATE_DECAL;
    }
    if (textureId == GFX_STATE_TEXTURE_NONE) {
        currTextureId = gGfxStateStackData & GFX_STATE_TEXTURE_MASK;
        if (currTextureId == GFX_STATE_TEXTURE_NONE) {
            if (var_v0 == 0) {
                return;
            }
        }
        gSPTextureL(gGfxDisplayListHead++, 0, 0, 0, xparam, G_TX_RENDERTILE, G_OFF);
    } else if (xparam != 0) {
        Gfx* dlist = gGfxUnkPtrs->textures[textureId]->dlist;
        GFX_PATCH_DL(gGfxDisplayListHead, dlist, xparam);
        gGfxDisplayListHead++;
    } else if (var_v0 != 0) {
        Gfx* dlist = gGfxUnkPtrs->textures[textureId]->dlist;
        GFX_PATCH_DL(gGfxDisplayListHead, dlist, 0);
        gGfxDisplayListHead++;
    }
}

void uvGfxWaitForMesg(void) {
    if (gGfxSyncNeeded != FALSE) {
        uvWaitForMesg(UV_MESG_GFX);
        gGfxSyncNeeded = FALSE;
    }
}

void uvGfxEnableGamma(s32 enable) {
    gGfxGammaEnabled = enable;
    if (enable != FALSE) {
        osViSetSpecialFeatures(OS_VI_GAMMA_ON);
    } else {
        osViSetSpecialFeatures(OS_VI_GAMMA_OFF);
    }
}

void uvGfxSetUnkState0(s32 arg0) {
    D_802491E8 = arg0;
}

void uvGfx_80223C00(void) {
    gDPPipeSync(gGfxDisplayListHead++);
    gDPSetRenderMode(gGfxDisplayListHead++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPPipeSync(gGfxDisplayListHead++);
    gDPSetCycleType(gGfxDisplayListHead++, G_CYC_FILL);
    gDPPipeSync(gGfxDisplayListHead++);
    gDPSetFillColor(gGfxDisplayListHead++, GPACK_RGBA5551(0, 0, 0, 0) << 16 | GPACK_RGBA5551(0, 0, 0, 0));
    gDPPipeSync(gGfxDisplayListHead++);
    gDPSetColorImage(gGfxDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, osVirtualToPhysical(D_80299278));
    gDPPipeSync(gGfxDisplayListHead++);
    gDPFillRectangle(gGfxDisplayListHead++, 2, 120, 310, 235);
    gDPPipeSync(gGfxDisplayListHead++);
    gDPPipeSync(gGfxDisplayListHead++);
    gDPSetCycleType(gGfxDisplayListHead++, G_CYC_2CYCLE);
    gDPPipeSync(gGfxDisplayListHead++);
    gDPSetColorImage(gGfxDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, osVirtualToPhysical(gGfxFbCurrPtr));
    gDPPipeSync(gGfxDisplayListHead++);
}

void uvCopyFrameBuf(s32 fb_id) {
    u8* src;
    u8* dst;

    if (fb_id < 0 || fb_id > 1) {
        _uvDebugPrintf("uvCopyFrameBuf: Buffer %d out of range\n", fb_id);
        return;
    }
    if (fb_id == 1) {
        fb_id = gGfxFbIndex;
    } else {
        fb_id = gGfxFbIndex ^ 1;
    }
    src = gGfxFbPtrs[fb_id];
    dst = gGfxFbPtrs[fb_id ^ 1];
    _uvMediaCopy(dst, src, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(u16));
}

