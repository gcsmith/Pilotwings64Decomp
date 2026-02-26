#include <uv_clocks.h>
#include <uv_dobj.h>
#include <uv_event.h>
#include <uv_fx.h>
#include <uv_geometry.h>
#include <uv_graphics.h>
#include <uv_memory.h>
#include <uv_sched.h>
#include <uv_sprite.h>
#include <macros.h>
#include <libc/stdint.h>

void func_80218CA4(void);
void func_8021A298(void);

#define TASK_OUTPUT_BUFFER_SIZE 0x2000

u8 gGfxTaskOutputBuffer[TASK_OUTPUT_BUFFER_SIZE + 8];
u8* gGfxTaskOutputBufferStart;
u8* gGfxTaskOutputBufferEnd;
Gfx* gGfxDisplayListHead;
s32 D_80298AB8[2];
s32 D_80298AC0[2];
s32 D_80298AC8[2];
s32 D_80298AD0[2];
s32 D_80298AD8[2];
s32 gGfxLookCount;
LookAt D_80298AE8[2][UV_GFX_NUM_LOOKS];
u32 gGfxStateStackData;
u32 D_8029926C;
u8* gGfxFbPtrs[2];
u8* D_80299278;
Gfx gGfxDisplayListBase[2][4200];
uvGfxViewport_t gGfxViewports[4];
s16 gGfxViewX0;
s16 gGfxViewX1;
s16 gGfxViewY0;
s16 gGfxViewY1;
Mtx gGfxMstack[2][UV_GFX_NUM_MATRICES];
Mtx4F D_802B4888;
u32 gGfxStateStack[32];
u8 gGfxStateStackIdx;
UnkStruct_uvGfxInit* D_802B494C;
UnkStruct_uvGfxInit D_802B4950[2];
u8 gGfxYieldData[OS_YIELD_DATA_SIZE];

static Gfx gGfxDList1[] = {
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

static Gfx gGfxDList2[] = {
    gsSPSetGeometryMode(G_SHADE), gsDPSetCycleType(G_CYC_2CYCLE), gsDPSetTextureLOD(G_TL_TILE), gsDPSetCombineMode(G_CC_SHADE, G_CC_PASS2),
    gsSPEndDisplayList(),
};

static f32 D_802491D8[2] = { 0, 0 };
static s32 D_802491E0 = 0;
static s32 D_802491E4 = 0xFFFFFFFF;
static s32 D_802491E8 = 0;
static s32 D_802491EC = 0;
static void* gGfxFbCurrPtr = NULL;
static u8 D_802491F4 = 0; // [4] = { 0, 0, 0, 0 };
static s8 D_802491F8 = 0; // [4] = { 0, 0, 0, 0 };
static s8 D_802491FC = 1; // [4] = { 0, 0, 0, 0 };

s32 D_80249200 = 0;
s32 gGfxBeginFlag = 0;
f32 D_80249208 = 0;
u16 gGfxFbIndex = 0;
s32 gGfxElementCount = 0;
s32 D_80249214 = 0;
s16 gGfxMstackIdx = 0xFFFF;
f32 D_8024921C = -1;

UNUSED Vp D_80249220 = { 640, 480, 511, 0, 640, 480, 511, 0 };

static uvGfxCallback_t D_80249230 = NULL;

extern OSMesgQueue D_802C3B90;
extern s32 D_8024B260;
extern u64 gGfxDramStack[];
extern OSSched gSchedInst;
extern u8 D_80269B80[300];
extern s16 gGeomVertexCount;

#define ALIGNED_BUFFER(buffer) (((uintptr_t)(buffer) & 0xF) ? buffer + 8 : buffer)

void uvGfxInit(void) {
    u8 i;

    D_80298AB8[0] = D_80298AB8[1] = 0;
    D_80298AC0[0] = D_80298AC0[1] = 0;
    D_80298AC8[0] = D_80298AC8[1] = 0;
    D_80298AD0[0] = D_80298AD0[1] = 0;
    D_80298AD8[0] = D_80298AD8[1] = 0;
    gGfxFbPtrs[0] = 0x800DA800;
    gGfxFbPtrs[1] = 0x80100000;
    D_80299278 = 0x803DA800;
    gGfxFbIndex = 0;
    gGfxDisplayListHead = gGfxDisplayListBase[gGfxFbIndex];
    gGfxFbCurrPtr = gGfxFbPtrs[gGfxFbIndex];
    D_802B494C = &D_802B4950[gGfxFbIndex];
    // clang-format off: must preserve same line assignments
    gGfxViewX0 = 2; gGfxViewX1 = SCREEN_WIDTH - 2;
    gGfxViewY0 = 2; gGfxViewY1 = SCREEN_HEIGHT - 2;
    // clang-format on

    for (i = 0; i < 2; i++) {
        uvGfxClipViewport(i, gGfxViewX0, gGfxViewX1, gGfxViewY0, gGfxViewY1);
    }
    uvMat4SetIdentity(&D_802B4888);
    gGfxStateStackIdx = 0;
    D_802491D8[0] = D_802491D8[1] = 0.0f;
    uvGfxEnableGamma(0);
    gGfxTaskOutputBufferStart = ALIGNED_BUFFER(gGfxTaskOutputBuffer);
    gGfxTaskOutputBufferEnd = gGfxTaskOutputBufferStart + TASK_OUTPUT_BUFFER_SIZE;
}

void uvGfxBegin(void) {
    if (gGfxBeginFlag == 1) {
        _uvDebugPrintf("uvGfxBegin: 2 calls in a row.  Must call uvGfxEnd first\n");
        return;
    }
    gGfxBeginFlag = 1;
    uvEventPost(0, 0);
    gSPSegment(gGfxDisplayListHead++, 0x00, 0x00000000);
    gDPSetColorImage(gGfxDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, osVirtualToPhysical(gGfxFbCurrPtr));

    uvGfxResetState();
    func_80218CA4();
    uvSprt_802301A4();
    uvVtxReset(1);
    func_8021A298();

    D_80298AB8[gGfxFbIndex] = 0;
    D_80298AC0[gGfxFbIndex] = 0;
    D_80298AC8[gGfxFbIndex] = 0;
    D_80298AD0[gGfxFbIndex] = 0;
    D_80298AD8[gGfxFbIndex] = 0;
    gGfxLookCount = 0;
}

void uvGfxSetFogFactor(f32 arg0) {
    if (arg0 < 0.0f) {
        arg0 = 0.0f;
    } else if (arg0 > 0.996f) {
        arg0 = 0.996f;
    }

    D_80249208 = arg0;
    if (arg0 > 0.0f) {
        gSPSetGeometryMode(gGfxDisplayListHead++, G_FOG);
        gSPFogPosition(gGfxDisplayListHead++, (s32)(D_80249208 * 1000.0f), 1000);
    } else {
        gSPClearGeometryMode(gGfxDisplayListHead++, G_FOG);
    }
}

void uvGfxResetState(void) {
    if (D_80249208 > 0.0f) {
        gSPSetGeometryMode(gGfxDisplayListHead++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH);
    } else {
        gSPSetGeometryMode(gGfxDisplayListHead++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
    }
    gSPDisplayList(gGfxDisplayListHead++, &gGfxDList1);
    gDPSetDepthImage(gGfxDisplayListHead++, D_80299278);
    gDPSetDepthImage(gGfxDisplayListHead++, osVirtualToPhysical(D_80299278));

    gGfxStateStackData = GFX_STATE_400000 | GFX_STATE_100000 | GFX_STATE_20000 | 0xFFF;
    D_8029926C = 0xFFF;
    D_802491E0 = 0;
    D_802491E4 = -1;
    uvGfxSetFogFactor(D_80249208);
}

void uvGfxMtxView(Mtx src) {
    uvGfxMstackPushL(src);
    gSPMatrix(gGfxDisplayListHead++, osVirtualToPhysical(uvGfxMstackTop()), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    D_80298AD0[gGfxFbIndex]++;
}

void uvGfxMtxProj(Mtx src) {
    uvGfxMstackPushL(src);
    gSPMatrix(gGfxDisplayListHead++, osVirtualToPhysical(uvGfxMstackTop()), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    D_80298AD0[gGfxFbIndex]++;
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
    gSPDisplayList(gGfxDisplayListHead++, arg0->unk8);
    uvGfxMtxViewPop();

    gDPPipeSync(gGfxDisplayListHead++);
    gDPSetColorImage(gGfxDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, osVirtualToPhysical(gGfxFbCurrPtr));
    gDPSetCombineMode(gGfxDisplayListHead++, G_CC_SHADE, G_CC_PASS2);
    gDPSetRenderMode(gGfxDisplayListHead++, G_RM_PASS, G_RM_ZB_XLU_SURF2);
    gSPClearGeometryMode(gGfxDisplayListHead++, G_CULL_FRONT);
    gSPSetGeometryMode(gGfxDisplayListHead++, G_CULL_BACK);
    gSPDisplayList(gGfxDisplayListHead++, arg0->unk8);

    D_80298AB8[gGfxFbIndex] += arg0->unk4 * 2;
    D_80298AC0[gGfxFbIndex] += arg0->unk6 * 2;
}

void uvGfxStateDraw(uvGfxState_t* arg0) {
    u32 clearMode;
    u32 setMode;
    u16 textureId;
    uvGfxUnkStructTexture* sp68;
    u16 var_t1;
    s32 renderMask;
    u32 var_a1_2;
    u32 renderMode1;
    u32 renderMode2;
    u32 var_a3;

    var_a3 = arg0->state;
    if (D_80249208 > 0.0f) {
        var_a3 |= GFX_STATE_80000000 | GFX_STATE_20000;
    }
    var_a3 |= D_802491E0;
    var_a3 &= D_802491E4;

    if (var_a3 & GFX_STATE_2000000) {
        uvGfxStateDrawDL(arg0);
        return;
    }
    if (var_a3 != gGfxStateStackData) {
        gDPPipeSync(gGfxDisplayListHead++);
        if ((var_a3 & (GFX_STATE_80000000 | GFX_STATE_8000000 | GFX_STATE_200000 | GFX_STATE_100000 | GFX_STATE_80000 | GFX_STATE_40000 | GFX_STATE_20000)) !=
            (gGfxStateStackData &
             (GFX_STATE_80000000 | GFX_STATE_8000000 | GFX_STATE_200000 | GFX_STATE_100000 | GFX_STATE_80000 | GFX_STATE_40000 | GFX_STATE_20000))) {
            setMode = 0;
            clearMode = 0;
            if (var_a3 & GFX_STATE_8000000) {
                setMode = G_TEXTURE_GEN | G_LIGHTING;
            } else {
                clearMode = G_TEXTURE_GEN | G_LIGHTING;
            }
            if (var_a3 & GFX_STATE_100000) {
                setMode |= G_CULL_BACK;
            } else {
                clearMode |= G_CULL_BACK;
            }
            if (var_a3 & GFX_STATE_80000) {
                setMode |= G_CULL_FRONT;
            } else {
                clearMode |= G_CULL_FRONT;
            }
            if (var_a3 & GFX_STATE_20000) {
                setMode |= G_SHADING_SMOOTH;
            } else {
                clearMode |= G_SHADING_SMOOTH;
            }
            if (var_a3 & GFX_STATE_200000) {
                setMode |= G_ZBUFFER;
            } else {
                clearMode |= G_ZBUFFER;
            }
            if (var_a3 & GFX_STATE_80000000) {
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
        textureId = var_a3 & 0xFFF;

        if (textureId == 0xFFE) {
            textureId++;
        }

        if (textureId >= 0xFFF) {
            var_t1 = 0xFFF;
        } else {
            sp68 = gGfxUnkPtrs->unk910[textureId];
            if (sp68 == NULL) {
                _uvDebugPrintf("uvGfxStateDraw: texture %d not in level\n", textureId);
                var_t1 = 0xFFF;
                textureId = 0xFFF;
            } else {
                var_t1 = (sp68->unk12 & 0xF000) | textureId;
            }
        }

        if (D_8029926C != var_t1) {
            if (textureId >= 0xFFE) {
                gSPDisplayList(gGfxDisplayListHead++, gGfxDList2);
            } else {
                _uvTxtDraw(textureId);
                D_80298AC8[gGfxFbIndex]++;
                if (var_a3 & GFX_STATE_8000000) {
                    gDPSetCombineMode(gGfxDisplayListHead++, G_CC_DECALRGB, G_CC_DECALRGB2);
                    gSPTexture(gGfxDisplayListHead++, 0x7C0, 0x7C0, 0, 1, G_ON);
                }
            }
        }
        if (var_a3 & GFX_STATE_1000000) {
            var_a1_2 = 0x10;
        } else {
            var_a1_2 = 0;
        }

        uvGfx_80223A64(textureId, var_a1_2);

        renderMask = GFX_STATE_1000000 | GFX_STATE_800000 | GFX_STATE_400000 | GFX_STATE_200000;
        switch (var_a3 & renderMask) {
        case GFX_STATE_1000000 | GFX_STATE_800000 | GFX_STATE_400000:
        case GFX_STATE_1000000 | GFX_STATE_800000 | GFX_STATE_400000 | GFX_STATE_200000:
            renderMode2 = G_RM_AA_ZB_XLU_DECAL2;
            break;
        case GFX_STATE_1000000 | GFX_STATE_800000:
        case GFX_STATE_1000000 | GFX_STATE_800000 | GFX_STATE_200000:
            renderMode2 = G_RM_ZB_XLU_DECAL2;
            break;
        case GFX_STATE_1000000 | GFX_STATE_400000:
        case GFX_STATE_1000000 | GFX_STATE_400000 | GFX_STATE_200000:
            renderMode2 = G_RM_AA_ZB_OPA_DECAL2;
            break;
        case GFX_STATE_1000000:
        case GFX_STATE_1000000 | GFX_STATE_200000:
            renderMode2 = G_RM_ZB_OPA_DECAL2;
            break;
        case GFX_STATE_800000 | GFX_STATE_400000 | GFX_STATE_200000:
            if (textureId == 0xFFF) {
                renderMode2 = G_RM_AA_ZB_XLU_INTER2;
            } else if ((sp68->unk12 & 0x8000) || (sp68->unk22 == 1) || (var_a3 & 0x04000000)) {
                renderMode2 = G_RM_AA_ZB_XLU_SURF2;
            } else {
                renderMode2 = G_RM_AA_ZB_TEX_TERR2;
            }
            break;
        case GFX_STATE_800000 | GFX_STATE_400000:
            if (textureId == 0xFFF) {
                renderMode2 = G_RM_AA_XLU_SURF2;
            } else if (sp68->unk12 & 0x8000) {
                renderMode2 = G_RM_AA_XLU_SURF2;
            } else {
                renderMode2 = G_RM_AA_TEX_TERR2;
            }
            break;
        case GFX_STATE_800000 | GFX_STATE_200000:
            if (textureId == 0xFFF) {
                renderMode2 = G_RM_ZB_XLU_SURF2;
            } else {
                renderMode2 = G_RM_ZB_XLU_SURF2;
            }
            break;
        case GFX_STATE_400000 | GFX_STATE_200000:
            renderMode2 = G_RM_AA_ZB_OPA_TERR2;
            break;
        case GFX_STATE_200000:
            renderMode2 = G_RM_ZB_OPA_SURF2;
            break;
        case GFX_STATE_400000:
            renderMode2 = G_RM_AA_OPA_TERR2;
            break;
        case GFX_STATE_800000:
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
        if (var_a3 & GFX_STATE_80000000) {
            renderMode1 = G_RM_FOG_SHADE_A;
        } else {
            renderMode1 = G_RM_PASS;
        }
        if (var_a3 & GFX_STATE_10000000) {
            renderMode2 = Z_CMP | Z_UPD | IM_RD | CLR_ON_CVG | CVG_DST_SAVE | ZMODE_OPA | GBL_c2(G_BL_CLR_MEM, G_BL_A_FOG, G_BL_CLR_MEM, G_BL_A_MEM);
        }

        gDPSetRenderMode(gGfxDisplayListHead++, renderMode1, renderMode2);

        D_8029926C = var_t1;
        gGfxStateStackData = var_a3;
    }
    if ((var_a3 & GFX_STATE_80000000) && ((var_a3 & renderMask) == (GFX_STATE_800000 | GFX_STATE_400000 | GFX_STATE_200000))) {
        if (textureId == 0xFFF) {
            gDPSetCombineMode(gGfxDisplayListHead++, G_CC_SHADE, G_CC_PASS2);
        } else {
            gDPSetCombineMode(gGfxDisplayListHead++, G_CC_MODULATEIDECALA, G_CC_PASS2);
        }
    }
    if (arg0->unk8 != NULL) {
        gSPDisplayList(gGfxDisplayListHead++, arg0->unk8);

        D_80298AB8[gGfxFbIndex] += arg0->unk4;
        D_80298AC0[gGfxFbIndex] += arg0->unk6;
    }
}

void uvGfxPushMtxUnk(Mtx4F* arg0) {
    Mtx spC8;
    Mtx4F sp88;
    Mtx4F sp48;

    uvMat4Copy(&D_802B4888, arg0);
    uvMat4Copy(&sp48, &D_802B4888);
    uvMat4SetIdentity(&sp88);
    uvMat4RotateAxis(&sp88, -1.5707963f, 'x');
    uvMat4Mul(&D_802B4888, &sp48, &sp88);
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

    if (gGfxLookCount >= UV_GFX_NUM_LOOKS) {
        _uvDebugPrintf("too many looks\n");
        return;
    }

    uvMat4InvertTranslationRotation(&temp, &D_802B4888);
    uvGfxClampLook(&D_80298AE8[gGfxFbIndex][gGfxLookCount], temp.m[3][0], temp.m[3][1], temp.m[3][2], arg0->m[3][0], arg0->m[3][1], arg0->m[3][2], 0.0f, 1.0f,
                   0.0f);
    gSPLookAt(gGfxDisplayListHead++, &D_80298AE8[gGfxFbIndex][gGfxLookCount]);
    gGfxLookCount++;
}

void uvGfxMtxProjPushF(Mtx4F* arg0) {
    Mtx sp48;
    uvMat4CopyF2L(&sp48, arg0);
    uvGfxMtxProj(sp48);
}

void uvGfxSetCallback(uvGfxCallback_t cb) {
    D_80249230 = cb;
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

    if (gGfxBeginFlag == 0) {
        _uvDebugPrintf("uvGfxEnd: must be called after a uvGfxBegin()\n");
        return;
    }
    gGfxBeginFlag = 0;
    gDPFullSync(gGfxDisplayListHead++);
    gSPEndDisplayList(gGfxDisplayListHead++);
    gGfxElementCount = (gGfxDisplayListHead - (gGfxDisplayListBase[gGfxFbIndex]));

    if (gGfxElementCount >= 4200) {
        _uvDebugPrintf("display list overflow %d / %d\n", gGfxElementCount, 4200);
        return;
    }
    D_802B494C->fb = gGfxFbPtrs[gGfxFbIndex];
    D_802B494C->unk0 = 0;
    D_802B494C->msgQueue = &D_802C3B90;
    D_802B494C->unk54 = &D_8024B260;
    D_802B494C->unk8 = 0x53;
    task = &D_802B4950[gGfxFbIndex].task;
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
    func_8022C3C0(0, 0x2B);
    osSendMesg(_uvScGetCmdQ(&gSchedInst), D_802B494C, 1);
    uvEventPost(1, 0);
    if (D_80249214 == 0) {
        osViBlack(FALSE);
    } else if (D_80249200 != 0) {
        uvWaitForMesg(4);
    }
    D_80249200 = 1;
    fb = gGfxFbPtrs[gGfxFbIndex ^ 1];
    if (D_80249230 != NULL) {
        D_80249230(fb, D_80299278);
        osWritebackDCache(fb, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(u16));
    }
    D_802491D8[gGfxFbIndex] = (f32)uvClkGetSec(3);
    uvClkReset(3);
    func_8022C3C0(0, 0x2A);
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
        if (D_80263780[i].unk0 != 0xFFFF) {
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
    D_802B494C = &D_802B4950[gGfxFbIndex];
    gGfxFbCurrPtr = gGfxFbPtrs[gGfxFbIndex];
    gGfxDisplayListHead = gGfxDisplayListBase[gGfxFbIndex];
    D_80249214++;
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
    if (enable != 0) {
        gDPSetRenderMode(gGfxDisplayListHead++, G_RM_PASS, G_RM_AA_ZB_OPA_TERR2);
        gSPSetGeometryMode(gGfxDisplayListHead++, G_ZBUFFER);
        D_802491F4 = 1;
        gGfxStateStackData |= GFX_STATE_200000;
    } else {
        gDPSetRenderMode(gGfxDisplayListHead++, G_RM_PASS, G_RM_AA_OPA_TERR2);
        gSPClearGeometryMode(gGfxDisplayListHead++, G_ZBUFFER);
        D_802491F4 = 0;
        gGfxStateStackData &= ~GFX_STATE_200000;
    }
}

void uvGfxEnableCull(s32 enable_front, s32 enable_back) {
    if (enable_front != 0) {
        gSPSetGeometryMode(gGfxDisplayListHead++, G_CULL_FRONT);
        D_802491F8 = 1;
        gGfxStateStackData |= GFX_STATE_80000;
    } else {
        gSPClearGeometryMode(gGfxDisplayListHead++, G_CULL_FRONT);
        D_802491F8 = 0;
        gGfxStateStackData &= ~GFX_STATE_80000;
    }
    if (enable_back != 0) {
        gSPSetGeometryMode(gGfxDisplayListHead++, G_CULL_BACK);
        D_802491FC = 1;
        gGfxStateStackData |= GFX_STATE_100000;
    } else {
        gSPClearGeometryMode(gGfxDisplayListHead++, G_CULL_BACK);
        D_802491FC = 0;
        gGfxStateStackData &= ~GFX_STATE_100000;
    }
}

void uvGfxEnableLighting(s32 enable) {
    if (enable != 0) {
        gSPSetGeometryMode(gGfxDisplayListHead++, G_LIGHTING);
    } else {
        gSPClearGeometryMode(gGfxDisplayListHead++, G_LIGHTING);
    }
}

void uvGfxClipRect(uvGfxViewport_t* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 var_a2;
    s32 var_a3;

    arg0->x0 = arg1;
    arg0->x1 = arg2;
    arg0->y0 = arg3;
    arg0->y1 = arg4;
    if (arg0->x0 < 0) {
        arg0->x0 = 0;
    } else if (arg0->x0 > SCREEN_WIDTH) {
        arg0->x0 = SCREEN_WIDTH;
    }

    if (arg0->x1 < 0) {
        arg0->x1 = 0;
    } else if (arg0->x1 > SCREEN_WIDTH) {
        arg0->x1 = SCREEN_WIDTH;
    }

    if (arg0->y1 < 0) {
        arg0->y1 = 0;
    } else if (arg0->y1 > SCREEN_HEIGHT) {
        arg0->y1 = SCREEN_HEIGHT;
    }

    if (arg0->y0 < 0) {
        arg0->y0 = 0;
    } else if (arg0->y0 > SCREEN_HEIGHT) {
        arg0->y0 = SCREEN_HEIGHT;
    }

    arg0->unk0 = arg0->x0 - 5;
    if (arg0->unk0 < 0) {
        arg0->unk0 = 0;
    }
    arg0->unk2 = arg0->x1 + 5;
    if (arg0->unk2 > SCREEN_WIDTH - 1) {
        arg0->unk2 = SCREEN_WIDTH - 1;
    }
    arg0->unk4 = arg0->y0 - 5;
    if (arg0->unk4 < 0) {
        arg0->unk4 = 0;
    }
    arg0->unk6 = arg0->y1 + 5;
    if (arg0->unk6 > SCREEN_HEIGHT - 1) {
        arg0->unk6 = SCREEN_HEIGHT - 1;
    }

    var_a2 = arg0->unk2 - arg0->unk0;
    var_a3 = arg0->unk6 - arg0->unk4;

    arg0->vp.vp.vscale[0] = (var_a2 << 1);
    arg0->vp.vp.vscale[1] = (var_a3 << 1);
    arg0->vp.vp.vscale[2] = 0x1FF;
    arg0->vp.vp.vscale[3] = 0;
    arg0->vp.vp.vtrans[0] = (u16)((arg0->unk0 + (var_a2 >> 1)) & 0xFFFF) << 2;
    arg0->vp.vp.vtrans[1] = (u16)(((SCREEN_HEIGHT - arg0->unk4) - (var_a3 >> 1)) & 0xFFFF) << 2;
    arg0->vp.vp.vtrans[2] = 0x1FF;
    arg0->vp.vp.vtrans[3] = 0;
    gGfxViewX0 = arg0->x0;
    gGfxViewX1 = arg0->x1;
    gGfxViewY0 = arg0->y0;
    gGfxViewY1 = arg0->y1;
}

void uvGfxClipViewport(s32 vp_id, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    uvGfxClipRect(&gGfxViewports[vp_id], arg1, arg2, arg3, arg4);
}

void uvGfxSetViewport(s32 vp_id, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    uvGfxClipRect(&gGfxViewports[vp_id + 2], arg1, arg2, arg3, arg4);
    uvGfxViewport(vp_id + 2);
}

void uvGfxViewport(s32 vp_id) {
    uvGfxViewport_t* vp;
    vp = &gGfxViewports[vp_id];

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

void uvGfxSetUnkStateF(f32 arg0) {
    D_8024921C = arg0;
}

f32 uvGfxGetUnkStateF(void) {
    if (D_8024921C > 0.0f) {
        return D_8024921C;
    }
    return D_802491D8[gGfxFbIndex ^ 1];
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
    D_80298AD0[gGfxFbIndex]++;
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
    D_80298AD0[gGfxFbIndex]++;
    D_80298AD8[gGfxFbIndex]++;
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
    D_80298AD0[gGfxFbIndex]++;
    D_80298AD8[gGfxFbIndex]++;
}

void uvGfxMtxViewPop(void) {
    gSPPopMatrix(gGfxDisplayListHead++, G_MTX_MODELVIEW);
}

void uvGfx_802236CC(Mtx4F* arg0) {
    Mtx4F sp20;
    uvMat4MulBA(&sp20, &D_802B4888, arg0);
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
    D_80298AD0[gGfxFbIndex]++;
}

s32 uvGfxGetCnt(u32 arg0) {
    switch (arg0) {
    case GFX_COUNT_VTX_TRANSFORMS:
        return D_80298AB8[1 - gGfxFbIndex];
    case GFX_COUNT_TRIS:
        return D_80298AC0[1 - gGfxFbIndex];
    case GFX_COUNT_TXT_LOADS:
        return D_80298AC8[1 - gGfxFbIndex];
    case GFX_COUNT_MTX_LOADS:
        return D_80298AD0[1 - gGfxFbIndex];
    case GFX_COUNT_MTX_LOAD_MULTS:
        return D_80298AD8[1 - gGfxFbIndex];
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
    uvGfxState_t state;

    if (gGfxStateStackIdx == 0) {
        _uvDebugPrintf("uvGfxStatePop: stack empty\n");
    } else {
        --gGfxStateStackIdx;
        newState = gGfxStateStack[gGfxStateStackIdx];
        state.state = newState;
        state.unk8 = NULL;
        uvGfxStateDraw(&state);
    }
}

void uvGfxSetFlags(s32 flags) {
    s32 newState;
    uvGfxState_t sp20;

    newState = flags | gGfxStateStackData;
    if (newState != gGfxStateStackData) {
        sp20.state = newState;
        sp20.unk8 = NULL;
        uvGfxStateDraw(&sp20);
    }
}

void uvGfxClearFlags(s32 flags) {
    s32 newState;
    uvGfxState_t sp20;

    newState = ~flags & gGfxStateStackData;
    if (newState != gGfxStateStackData) {
        sp20.state = newState;
        sp20.unk8 = NULL;
        uvGfxStateDraw(&sp20);
    }
}

void uvGfx_80223A28(u32 flags) {
    uvGfxState_t sp20;
    s32 pad;

    sp20.unk8 = NULL;
    sp20.state = (gGfxStateStackData & ~0xFFF) | flags;
    uvGfxStateDraw(&sp20);
}

void uvGfx_80223A64(s32 arg0, s32 arg1) {
    u32 var_v0;
    u32 var_a0;

    var_v0 = gGfxStateStackData & GFX_STATE_1000000;
    if (arg1 != 0) {
        var_v0 ^= GFX_STATE_1000000;
    }
    if (arg0 == 0xFFF) {
        var_a0 = gGfxStateStackData & 0xFFF;
        if (var_a0 == 0xFFF) {
            if (var_v0 == 0) {
                return;
            }
        }
        gSPTextureL(gGfxDisplayListHead++, 0, 0, 0, arg1, G_TX_RENDERTILE, G_OFF);

    } else if (arg1 != 0) {
        Gfx* temp_v0 = gGfxUnkPtrs->unk910[arg0]->unk4;
        GFX_PATCH_DL(gGfxDisplayListHead, temp_v0, arg1);
        gGfxDisplayListHead++;
    } else if (var_v0 != 0) {
        Gfx* temp_v0 = gGfxUnkPtrs->unk910[arg0]->unk4;
        GFX_PATCH_DL(gGfxDisplayListHead, temp_v0, 0);
        gGfxDisplayListHead++;
    }
}

void uvGfxWaitForMesg(void) {
    if (D_80249200 != 0) {
        uvWaitForMesg(UV_MESG_GFX);
        D_80249200 = 0;
    }
}

void uvGfxEnableGamma(s32 enable) {
    D_802491EC = enable;
    if (enable != 0) {
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

