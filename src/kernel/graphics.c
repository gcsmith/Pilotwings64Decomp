#include <uv_clocks.h>
#include <uv_dobj.h>
#include <uv_event.h>
#include <uv_geometry.h>
#include <uv_graphics.h>
#include <uv_memory.h>
#include <uv_sched.h>
#include <uv_sprite.h>
#include <macros.h>
#include <libc/stdint.h>

void func_80218CA4(void);
void func_8021A298(void);

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
f32 D_80249220 = 1.880898581e-37;
f32 D_80249224 = 9.367220608e-38;
f32 D_80249228 = 1.880898581e-37;
f32 D_8024922C = 9.367220608e-38;

static uvGfxCallback_t D_80249230 = NULL;

extern uvGfxUnkStruct* gGfxUnkPtrs;
extern u8 D_80296AA0[];
extern u8 D_80296AA8[];
extern u8* gGfxTaskOutputBufferStart;
extern u8* gGfxTaskOutputBufferEnd;
extern s32 D_80298AB8[];
extern s32 D_80298AC0[];
extern s32 D_80298AC8[];
extern s32 D_80298AD0[];
extern s32 D_80298AD8[];

typedef Mtx MtxStack_t[UV_GFX_NUM_MATRICES];

extern s32 gGfxLookCount;
extern MtxStack_t gGfxMstack[2];
extern u8* gGfxFbPtrs[2];
extern u32 D_8029926C;
extern u8* D_80299278;

extern uvGfxViewport_t gGfxViewports[];
extern s16 gGfxViewX0;
extern s16 gGfxViewX1;
extern s16 gGfxViewY0;
extern s16 gGfxViewY1;

extern s32 D_80298ABC[];
extern s32 D_80298AC4[];
extern s32 D_80298ACC[];
extern s32 D_80298AD4[];
extern s32 D_80298ADC[];

typedef LookAt uvLookStorage_t[UV_GFX_NUM_LOOKS];
extern uvLookStorage_t D_80298AE8[2];

extern s32 gGfxStateStackData;
extern u32 gGfxStateStack[];
extern u8 gGfxStateStackIdx;

extern Mtx4F D_802B4888;
extern UnkStruct_uvGfxInit* D_802B494C;
extern UnkStruct_uvGfxInit D_802B4950[];

typedef Gfx uvDisplayListBuf_t[0x1068];
extern uvDisplayListBuf_t gGfxDisplayListBase[2];

extern OSMesgQueue D_802C3B90;
extern s32 D_8024B260;
extern u64 gGfxDramStack[];
extern u8 gGfxYieldData[];
extern OSSched gSchedInst;
extern u8 D_80269B80[300];
extern s16 gGeomVertexCount;

typedef struct {
    u8 pad0[0x4];
    u8 unk4;
    u8 pad5[0xAB];
} unk8028B400;

extern unk8028B400 D_8028B400[120];

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
    gGfxViewX0 = 2; gGfxViewX1 = 0x13E;
    gGfxViewY0 = 2; gGfxViewY1 = 0xEE;
    // clang-format on

    for (i = 0; i < 2; i++) {
        uvGfxClipViewport(i, gGfxViewX0, gGfxViewX1, gGfxViewY0, gGfxViewY1);
    }
    uvMat4SetIdentity(&D_802B4888);
    gGfxStateStackIdx = 0;
    D_802491D8[1] = 0.0f;
    D_802491D8[0] = (f32)D_802491D8[1];
    uvGfxEnableGamma(0);
    gGfxTaskOutputBufferStart = ((s32)&D_80296AA0 & 0xF) ? D_80296AA8 : D_80296AA0;
    gGfxTaskOutputBufferEnd = gGfxTaskOutputBufferStart + 0x2000;
}

void uvGfxBegin(void) {
    if (gGfxBeginFlag == 1) {
        _uvDebugPrintf("uvGfxBegin: 2 calls in a row.  Must call uvGfxEnd first\n");
        return;
    }
    gGfxBeginFlag = 1;
    uvEventPost(0, 0);
    gSPSegment(gGfxDisplayListHead++, 0x00, 0x00000000);
    gDPSetColorImage(gGfxDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, osVirtualToPhysical(gGfxFbCurrPtr));

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

    gGfxStateStackData = 0x520FFF;
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

void uvGfxMtxProj(Mtx arg0) {
    uvGfxMstackPushL(arg0);
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
    gDPSetColorImage(gGfxDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, osVirtualToPhysical(D_80299278));

    uvMat4SetIdentity(&temp);
    uvGfxMtxViewMul(&temp, 1);
    gSPDisplayList(gGfxDisplayListHead++, (s32)arg0->unk8);
    uvGfxMtxViewPop();

    gDPPipeSync(gGfxDisplayListHead++);
    gDPSetColorImage(gGfxDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, osVirtualToPhysical(gGfxFbCurrPtr));
    gDPSetCombineMode(gGfxDisplayListHead++, G_CC_SHADE, G_CC_PASS2);
    gDPSetRenderMode(gGfxDisplayListHead++, G_RM_PASS, G_RM_ZB_XLU_SURF2);
    gSPClearGeometryMode(gGfxDisplayListHead++, G_CULL_FRONT);
    gSPSetGeometryMode(gGfxDisplayListHead++, G_CULL_BACK);
    gSPDisplayList(gGfxDisplayListHead++, (s32)arg0->unk8);

    D_80298AB8[gGfxFbIndex] += arg0->unk4 * 2;
    D_80298AC0[gGfxFbIndex] += arg0->unk6 * 2;
}

void uvGfxStateDraw(uvGfxState_t* arg0) {
    u32 clearMode;
    u32 setMode;
    u16 var_t2;
    uvGfxUnkStruct2* sp68;
    u16 var_t1;
    s32 sp60;
    u32 var_a1_2;
    u32 renderMode1;
    u32 renderMode2;
    u32 var_a3;

    var_a3 = arg0->unk0;
    if (D_80249208 > 0.0f) {
        var_a3 |= 0x80020000;
    }
    var_a3 |= D_802491E0;
    var_a3 &= D_802491E4;

    if (var_a3 & 0x02000000) {
        uvGfxStateDrawDL(arg0);
        return;
    }
    if (var_a3 != (u32)gGfxStateStackData) {
        gDPPipeSync(gGfxDisplayListHead++);
        if ((var_a3 & 0x883E0000) != (gGfxStateStackData & 0x883E0000)) {
            setMode = 0;
            clearMode = 0;
            if (var_a3 & 0x08000000) {
                setMode = G_TEXTURE_GEN | G_LIGHTING;
            } else {
                clearMode = G_TEXTURE_GEN | G_LIGHTING;
            }
            if (var_a3 & 0x100000) {
                setMode |= G_CULL_BACK;
            } else {
                clearMode |= G_CULL_BACK;
            }
            if (var_a3 & 0x80000) {
                setMode |= G_CULL_FRONT;
            } else {
                clearMode |= G_CULL_FRONT;
            }
            if (var_a3 & 0x20000) {
                setMode |= G_SHADING_SMOOTH;
            } else {
                clearMode |= G_SHADING_SMOOTH;
            }
            if (var_a3 & 0x200000) {
                setMode |= G_ZBUFFER;
            } else {
                clearMode |= G_ZBUFFER;
            }
            if (var_a3 & 0x80000000) {
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
        var_t2 = var_a3 & 0xFFF;

        if (var_t2 == 0xFFE) {
            var_t2++;
        }

        if (var_t2 >= 0xFFF) {
            var_t1 = 0xFFF;
        } else {
            sp68 = gGfxUnkPtrs->unk910[var_t2];
            if (sp68 == NULL) {
                _uvDebugPrintf("uvGfxStateDraw: texture %d not in level\n", var_t2);
                var_t1 = 0xFFF;
                var_t2 = 0xFFF;
            } else {
                var_t1 = (sp68->unk12 & 0xF000) | var_t2;
            }
        }

        if (D_8029926C != var_t1) {
            if (var_t2 >= 0xFFE) {
                gSPDisplayList(gGfxDisplayListHead++, gGfxDList2);
            } else {
                _uvTxtDraw(var_t2);
                D_80298AC8[gGfxFbIndex]++;
                if (var_a3 & 0x08000000) {
                    gDPSetCombineMode(gGfxDisplayListHead++, G_CC_DECALRGB, G_CC_DECALRGB2);
                    gSPTexture(gGfxDisplayListHead++, 0x7C0, 0x7C0, 0, 1, G_ON);
                }
            }
        }
        if (var_a3 & 0x01000000) {
            var_a1_2 = 0x10;
        } else {
            var_a1_2 = 0;
        }

        uvGfx_80223A64(var_t2, var_a1_2);

        sp60 = 0x01E00000;
        switch (var_a3 & sp60) {
        case 0x1C00000:
        case 0x1E00000:
            renderMode2 = G_RM_AA_ZB_XLU_DECAL2;
            break;
        case 0x1800000:
        case 0x1A00000:
            renderMode2 = G_RM_ZB_XLU_DECAL2;
            break;
        case 0x1400000:
        case 0x1600000:
            renderMode2 = G_RM_AA_ZB_OPA_DECAL2;
            break;
        case 0x1000000:
        case 0x1200000:
            renderMode2 = G_RM_ZB_OPA_DECAL2;
            break;
        case 0xE00000:
            if (var_t2 == 0xFFF) {
                renderMode2 = G_RM_AA_ZB_XLU_INTER2;
            } else if ((sp68->unk12 & 0x8000) || (sp68->unk22 == 1) || (var_a3 & 0x04000000)) {
                renderMode2 = G_RM_AA_ZB_XLU_SURF2;
            } else {
                renderMode2 = G_RM_AA_ZB_TEX_TERR2;
            }
            break;
        case 0xC00000:
            if (var_t2 == 0xFFF) {
                renderMode2 = G_RM_AA_XLU_SURF2;
            } else if (sp68->unk12 & 0x8000) {
                renderMode2 = G_RM_AA_XLU_SURF2;
            } else {
                renderMode2 = G_RM_AA_TEX_TERR2;
            }
            break;
        case 0xA00000:
            if (var_t2 == 0xFFF) {
                renderMode2 = G_RM_ZB_XLU_SURF2;
            } else {
                renderMode2 = G_RM_ZB_XLU_SURF2;
            }
            break;
        case 0x600000:
            renderMode2 = G_RM_AA_ZB_OPA_TERR2;
            break;
        case 0x200000:
            renderMode2 = G_RM_ZB_OPA_SURF2;
            break;
        case 0x400000:
            renderMode2 = G_RM_AA_OPA_TERR2;
            break;
        case 0x800000:
            renderMode2 = G_RM_XLU_SURF2;
            break;
        case 0x0:
            renderMode2 = G_RM_OPA_SURF2;
            break;
        default:
            _uvDebugPrintf("uvGfxStateDraw: unknown case 0x%x\n", var_a3 & sp60);
            renderMode2 = G_RM_OPA_SURF2;
            break;
        }
        if (var_a3 & 0x80000000) {
            renderMode1 = G_RM_FOG_SHADE_A;
        } else {
            renderMode1 = G_RM_PASS;
        }
        if (var_a3 & 0x10000000) {
            renderMode2 = Z_CMP | Z_UPD | IM_RD | CLR_ON_CVG | CVG_DST_SAVE | ZMODE_OPA | GBL_c2(G_BL_CLR_MEM, G_BL_A_FOG, G_BL_CLR_MEM, G_BL_A_MEM);
        }

        gDPSetRenderMode(gGfxDisplayListHead++, renderMode1, renderMode2);

        D_8029926C = var_t1;
        gGfxStateStackData = var_a3;
    }
    if ((var_a3 & 0x80000000) && ((var_a3 & sp60) == 0xE00000)) {
        if (var_t2 == 0xFFF) {
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
    Mtx4F spC8;
    Mtx4F sp88;
    Mtx4F sp48;

    uvMat4Copy(&D_802B4888, arg0);
    uvMat4Copy(&sp48, &D_802B4888);
    uvMat4SetIdentity(&sp88);
    uvMat4RotateAxis(&sp88, -1.5707963f, 'x');
    uvMat4Mul(&D_802B4888, &sp48, &sp88);
    uvMat4SetUnk1(&spC8);
    uvGfxMtxView(*(Mtx*)&spC8);
}

void uvGfxClampLook(LookAt* arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9) {
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

    arg0->l[0].l.dir[0] = (s32)MIN(sp4C * 128.0, 127.0) & 0xFF;
    arg0->l[0].l.dir[1] = (s32)MIN(sp48 * 128.0, 127.0) & 0xFF;
    arg0->l[0].l.dir[2] = (s32)MIN(sp44 * 128.0, 127.0) & 0xFF;

    arg0->l[1].l.dir[0] = (s32)MIN(arg7 * 128.0, 127.0) & 0xFF;
    arg0->l[1].l.dir[1] = (s32)MIN(arg8 * 128.0, 127.0) & 0xFF;
    arg0->l[1].l.dir[2] = (s32)MIN(arg9 * 128.0, 127.0) & 0xFF;
    arg0->l[0].l.col[0] = 0;
    arg0->l[0].l.col[1] = 0;
    arg0->l[0].l.col[2] = 0;
    arg0->l[0].l.pad1 = 0;
    arg0->l[0].l.colc[0] = 0;
    arg0->l[0].l.colc[1] = 0;
    arg0->l[0].l.colc[2] = 0;
    arg0->l[0].l.pad2 = 0;
    arg0->l[1].l.col[0] = 0;
    arg0->l[1].l.col[1] = 0x80;
    arg0->l[1].l.col[2] = 0;
    arg0->l[1].l.pad1 = 0;
    arg0->l[1].l.colc[0] = 0;
    arg0->l[1].l.colc[1] = 0x80;
    arg0->l[1].l.colc[2] = 0;
    arg0->l[1].l.pad2 = 0;
}

void uvGfxLookAt(Mtx4F* arg0) {
    Mtx4F temp;

    if (gGfxLookCount >= UV_GFX_NUM_LOOKS) {
        _uvDebugPrintf("too many looks\n");
        return;
    }

    uvMat4UnkOp4(&temp, &D_802B4888);
    uvGfxClampLook(&D_80298AE8[gGfxFbIndex][gGfxLookCount], temp.m[3][0], temp.m[3][1], temp.m[3][2], arg0->m[3][0], arg0->m[3][1], arg0->m[3][2], 0.0f, 1.0f,
                   0.0f);
    gSPLookAt(gGfxDisplayListHead++, &D_80298AE8[gGfxFbIndex][gGfxLookCount]);
    gGfxLookCount += 1;
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
    static s32 D_80249234 = 0x00000FA0;
    static s32 D_80249238 = 0x00000126;
    static s32 D_8024923C = 0x000000C8;
    static s32 D_80249240 = 0x00000064;
    static s32 D_80249244 = 0x00000078;
    static s32 D_80249248 = 0x00000320;
    static s32 D_8024924C = 0x00000000;
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
        osWritebackDCache(fb, 0x25800);
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
    if (D_80249234 < gGfxElementCount) {
        D_80249234 = gGfxElementCount;
        var_a1 = TRUE;
    }
    if (D_80249238 < gGfxMstackIdx) {
        D_80249238 = gGfxMstackIdx;
        var_a1 = TRUE;
    }
    if (D_8024923C < var_a2) {
        D_8024923C = var_a2;
        var_a1 = TRUE;
    }
    if (D_80249240 < var_t0) {
        D_80249240 = var_t0;
        var_a1 = TRUE;
    }
    if (D_80249244 < var_t1) {
        D_80249244 = var_t1;
        var_a1 = TRUE;
    }
    if (D_80249248 < gGeomVertexCount) {
        D_80249248 = gGeomVertexCount;
        var_a1 = TRUE;
    }
    if (var_a1) {
        _uvDebugPrintf("\nGFXEND :\n");
        _uvDebugPrintf("DL_ELEMENTS :  %d", D_80249234);
        if (D_80249234 == gGfxElementCount) {
            _uvDebugPrintf(" <==== WINNER");
        }

        _uvDebugPrintf("\n");
        _uvDebugPrintf("DL_NDBMTXS  :  %d", D_80249238);
        if (D_80249238 == gGfxMstackIdx) {
            _uvDebugPrintf(" <==== WINNER");
        }
        _uvDebugPrintf("\n");
        _uvDebugPrintf("OBJ_NPXFMS  :  %d", D_8024923C);
        if (var_a2 == D_8024923C) {
            _uvDebugPrintf(" <==== WINNER");
        }
        _uvDebugPrintf("\n");
        _uvDebugPrintf("OBJ_NDOBJS  :  %d", D_80249240);
        if (var_t0 == D_80249240) {
            _uvDebugPrintf(" <==== WINNER");
        }
        _uvDebugPrintf("\n");
        _uvDebugPrintf("FX_NFX      :  %d", D_80249244);
        if (var_t1 == D_80249244) {
            _uvDebugPrintf(" <==== WINNER");
        }
        _uvDebugPrintf("\n");
        _uvDebugPrintf("GEOM_NDBVTXS:  %d", D_80249248);
        if (D_80249248 == gGeomVertexCount) {
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
    gDPSetColorImage(gGfxDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, osVirtualToPhysical(gGfxFbCurrPtr));
    gDPSetFillColor(gGfxDisplayListHead++, GPACK_RGBA5551(r, g, b, a) << 16 | GPACK_RGBA5551(r, g, b, a));
    gDPFillRectangle(gGfxDisplayListHead++, gGfxViewX0, (0xF0 - gGfxViewY1), (gGfxViewX1 - 1), (0xEF - gGfxViewY0));
    gDPPipeSync(gGfxDisplayListHead++);
    gDPSetCycleType(gGfxDisplayListHead++, G_CYC_2CYCLE);
}

void uvGfx_80222A98(void) {
    gDPSetScissor(gGfxDisplayListHead++, G_SC_NON_INTERLACE, 0, 0, 320, 240);
    gDPPipeSync(gGfxDisplayListHead++);
    gDPSetRenderMode(gGfxDisplayListHead++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPPipeSync(gGfxDisplayListHead++);
    gDPSetCycleType(gGfxDisplayListHead++, G_CYC_FILL);
    gDPPipeSync(gGfxDisplayListHead++);
    gDPSetFillColor(gGfxDisplayListHead++, 0xFFFCFFFC);
    gDPPipeSync(gGfxDisplayListHead++);
    gDPSetColorImage(gGfxDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, osVirtualToPhysical(D_80299278));
    gDPPipeSync(gGfxDisplayListHead++);
    gDPFillRectangle(gGfxDisplayListHead++, 0, 0, 319, 239);
    gDPPipeSync(gGfxDisplayListHead++);
    gDPSetColorImage(gGfxDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, osVirtualToPhysical(gGfxFbCurrPtr));
    gDPPipeSync(gGfxDisplayListHead++);
    gDPSetCycleType(gGfxDisplayListHead++, G_CYC_2CYCLE);
    gDPPipeSync(gGfxDisplayListHead++);
}

void uvGfxEnableZBuffer(s32 enable) {
    if (enable != 0) {
        gDPSetRenderMode(gGfxDisplayListHead++, G_RM_PASS, G_RM_AA_ZB_OPA_TERR2);
        gSPSetGeometryMode(gGfxDisplayListHead++, G_ZBUFFER);
        D_802491F4 = 1;
        gGfxStateStackData |= 0x200000;
    } else {
        gDPSetRenderMode(gGfxDisplayListHead++, G_RM_PASS, G_RM_AA_OPA_TERR2);
        gSPClearGeometryMode(gGfxDisplayListHead++, G_ZBUFFER);
        D_802491F4 = 0;
        gGfxStateStackData &= 0xFFDFFFFF;
    }
}

void uvGfxEnableCull(s32 enable_front, s32 enable_back) {
    if (enable_front != 0) {
        gSPSetGeometryMode(gGfxDisplayListHead++, G_CULL_FRONT);
        D_802491F8 = 1;
        gGfxStateStackData |= 0x80000;
    } else {
        gSPClearGeometryMode(gGfxDisplayListHead++, G_CULL_FRONT);
        D_802491F8 = 0;
        gGfxStateStackData &= 0xFFF7FFFF;
    }
    if (enable_back != 0) {
        gSPSetGeometryMode(gGfxDisplayListHead++, G_CULL_BACK);
        D_802491FC = 1;
        gGfxStateStackData |= 0x100000;
    } else {
        gSPClearGeometryMode(gGfxDisplayListHead++, G_CULL_BACK);
        D_802491FC = 0;
        gGfxStateStackData &= 0xFFEFFFFF;
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
    } else if (arg0->x0 > 320) {
        arg0->x0 = 320;
    }

    if (arg0->x1 < 0) {
        arg0->x1 = 0;
    } else if (arg0->x1 > 320) {
        arg0->x1 = 320;
    }

    if (arg0->y1 < 0) {
        arg0->y1 = 0;
    } else if (arg0->y1 > 240) {
        arg0->y1 = 240;
    }

    if (arg0->y0 < 0) {
        arg0->y0 = 0;
    } else if (arg0->y0 > 240) {
        arg0->y0 = 240;
    }

    arg0->unk0 = arg0->x0 - 5;
    if (arg0->unk0 < 0) {
        arg0->unk0 = 0;
    }
    arg0->unk2 = arg0->x1 + 5;
    if (arg0->unk2 > 319) {
        arg0->unk2 = 319;
    }
    arg0->unk4 = arg0->y0 - 5;
    if (arg0->unk4 < 0) {
        arg0->unk4 = 0;
    }
    arg0->unk6 = arg0->y1 + 5;
    if (arg0->unk6 > 239) {
        arg0->unk6 = 239;
    }

    var_a2 = arg0->unk2 - arg0->unk0;
    var_a3 = arg0->unk6 - arg0->unk4;

    arg0->vp.vp.vscale[0] = (var_a2 << 1);
    arg0->vp.vp.vscale[1] = (var_a3 << 1);
    arg0->vp.vp.vscale[2] = 0x1FF;
    arg0->vp.vp.vscale[3] = 0;
    arg0->vp.vp.vtrans[0] = (u16)((arg0->unk0 + (var_a2 >> 1)) & 0xFFFF) << 2;
    arg0->vp.vp.vtrans[1] = (u16)(((240 - arg0->unk4) - (var_a3 >> 1)) & 0xFFFF) << 2;
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

    gSPViewport(gGfxDisplayListHead++, (u32)vp + 0x80000010);
    gDPSetScissor(gGfxDisplayListHead++, G_SC_NON_INTERLACE, vp->x0, 0xF0 - vp->y1, vp->x1, 0xF0 - vp->y0);
    gGfxViewX0 = vp->x0;
    gGfxViewX1 = vp->x1;
    gGfxViewY0 = vp->y0;
    gGfxViewY1 = vp->y1;
}

void uvGfxMstackPushF(Mtx4F* src) {
    gGfxMstackIdx += 1;
    if (gGfxMstackIdx >= UV_GFX_NUM_MATRICES) {
        _uvDebugPrintf("gfx : too many double buffered matrices [%d]\n", gGfxMstackIdx);
        gGfxMstackIdx -= 1;
        return;
    }
    uvMat4CopyF2L(&gGfxMstack[gGfxFbIndex][gGfxMstackIdx], src);
}

void uvGfxMstackPushL(Mtx src) {
    gGfxMstackIdx += 1;
    if (gGfxMstackIdx >= UV_GFX_NUM_MATRICES) {
        _uvDebugPrintf("gfx : too many double buffered matrices [%d]\n", gGfxMstackIdx);
        gGfxMstackIdx -= 1;
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
    case 0:
        return D_80298ABC[0 - gGfxFbIndex];
    case 1:
        return D_80298AC4[0 - gGfxFbIndex];
    case 4:
        return D_80298ACC[0 - gGfxFbIndex];
    case 2:
        return D_80298AD4[0 - gGfxFbIndex];
    case 3:
        return D_80298ADC[0 - gGfxFbIndex];
    default:
        _uvDebugPrintf("uvGfxGetCnt: no such count type %d", arg0);
        return 0;
    }
}

void uvGfxStatePush(void) {
    if (gGfxStateStackIdx >= 0x1F) {
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
        state.unk0 = newState;
        state.unk8 = 0;
        uvGfxStateDraw(&state);
    }
}

void uvGfxSetFlags(s32 flags) {
    s32 newState;
    uvGfxState_t sp20;

    newState = flags | gGfxStateStackData;
    if (newState != gGfxStateStackData) {
        sp20.unk0 = newState;
        sp20.unk8 = 0;
        uvGfxStateDraw(&sp20);
    }
}

void uvGfxClearFlags(s32 flags) {
    s32 newState;
    uvGfxState_t sp20;

    newState = ~flags & gGfxStateStackData;
    if (newState != gGfxStateStackData) {
        sp20.unk0 = newState;
        sp20.unk8 = 0;
        uvGfxStateDraw(&sp20);
    }
}

void uvGfx_80223A28(s32 flags) {
    uvGfxState_t sp20;
    s32 pad;

    sp20.unk8 = 0;
    sp20.unk0 = (gGfxStateStackData & ~0xFFF) | flags;
    uvGfxStateDraw(&sp20);
}

void uvGfx_80223A64(s32 arg0, s32 arg1) {
    s32 var_v0;
    u32 var_a0;

    var_v0 = gGfxStateStackData & 0x01000000;
    if (arg1 != 0) {
        var_v0 ^= 0x01000000;
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
    gDPSetFillColor(gGfxDisplayListHead++, 0x00000000);
    gDPPipeSync(gGfxDisplayListHead++);
    gDPSetColorImage(gGfxDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, osVirtualToPhysical(D_80299278));
    gDPPipeSync(gGfxDisplayListHead++);
    gDPFillRectangle(gGfxDisplayListHead++, 2, 120, 310, 235);
    gDPPipeSync(gGfxDisplayListHead++);
    gDPPipeSync(gGfxDisplayListHead++);
    gDPSetCycleType(gGfxDisplayListHead++, G_CYC_2CYCLE);
    gDPPipeSync(gGfxDisplayListHead++);
    gDPSetColorImage(gGfxDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, osVirtualToPhysical(gGfxFbCurrPtr));
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
    _uvMediaCopy(dst, src, 0x25800);
}

