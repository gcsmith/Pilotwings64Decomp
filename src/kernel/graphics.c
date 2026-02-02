#include <uv_geometry.h>
#include <uv_graphics.h>
#include <uv_memory.h>
#include <uv_sched.h>
#include <uv_sprite.h>

void func_80218CA4(void);
void func_8021A298(void);
void uvEventPost(s32, s32);

extern Gfx D_80249140[];
extern f32 D_802491D8[];
extern s32 D_802491E0;
extern s32 D_802491E4;
extern s32 D_802491E8;
extern s32 D_802491EC;
extern u8 D_802491F4;
extern s8 D_802491F8;
extern s8 D_802491FC;
extern s32 D_80249200;
extern f32 D_80249208;
extern f32 D_8024921C;
extern s32 D_80249230;

extern u8 D_80296AA0[];
extern u8 D_80296AA8[];
extern u8* D_80298AA8;
extern u8* D_80298AAC;
extern s32 D_80298AB8[];
extern s32 D_80298AC0[];
extern s32 D_80298AC8[];
extern s32 D_80298AD0[];
extern s32 D_80298AD8[];

typedef Mtx MtxStack_t[UV_GFX_NUM_MATRICES];

extern s32 gGfxBeginFlag;
extern void* gGfxFbCurrPtr;
extern u16 gGfxFbIndex;
extern s32 gGfxLookCount;
extern s16 gGfxMstackIdx;
extern MtxStack_t gGfxMstack[2];
extern u8* gGfxFbPtrs[2];
extern s32 D_8029926C;
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
        uvGfx_80223094(i, gGfxViewX0, gGfxViewX1, gGfxViewY0, gGfxViewY1);
    }
    uvMat4SetIdentity(&D_802B4888);
    gGfxStateStackIdx = 0;
    D_802491D8[1] = 0.0f;
    D_802491D8[0] = (f32)D_802491D8[1];
    uvGfxEnableGamma(0);
    D_80298AA8 = ((s32)&D_80296AA0 & 0xF) ? D_80296AA8 : D_80296AA0;
    D_80298AAC = D_80298AA8 + 0x2000;
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

    uvGfx_80220E0C();
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

#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/uvGfxSetFogFactor.s")
#else
void uvGfxSetFogFactor(f32 arg0) {
    if (arg0 < 0.0f) {
        arg0 = 0.0f;
    } else if (arg0 > 0.996f) {
        arg0 = 0.996f;
    }

    D_80249208 = arg0;
    if (arg0 > 0.0f) {
        gSPSetGeometryMode(gGfxDisplayListHead++, G_FOG);
        gSPFogFactor(gGfxDisplayListHead++, (((s32)(D_80249208 * 1000.0f) * -0x100) + 0x1F400) / (s32)(0x3E8 - (s32)(D_80249208 * 1000.0f)),
                     0x1F400 / (s32)(0x3E8 - (s32)(D_80249208 * 1000.0f)));
    } else {
        gSPClearGeometryMode(gGfxDisplayListHead++, G_FOG);
    }
}
#endif

void uvGfx_80220E0C(void) {
    if (D_80249208 > 0.0f) {
        gSPSetGeometryMode(gGfxDisplayListHead++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH);
    } else {
        gSPSetGeometryMode(gGfxDisplayListHead++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
    }
    gSPDisplayList(gGfxDisplayListHead++, &D_80249140);
    gDPSetDepthImage(gGfxDisplayListHead++, D_80299278);
    gDPSetDepthImage(gGfxDisplayListHead++, osVirtualToPhysical(D_80299278));

    gGfxStateStackData = 0x520FFF;
    D_8029926C = 0xFFF;
    D_802491E0 = 0;
    D_802491E4 = -1;
    uvGfxSetFogFactor(D_80249208);
}

void uvGfxPushMtxView(Mtx src) {
    uvGfxMstackPush(src);
    gSPMatrix(gGfxDisplayListHead++, osVirtualToPhysical(uvGfxMstackTop()), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    D_80298AD0[gGfxFbIndex]++;
}

void uvGfxPushMtxProj(Mtx arg0) {
    uvGfxMstackPush(arg0);
    gSPMatrix(gGfxDisplayListHead++, osVirtualToPhysical(uvGfxMstackTop()), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    D_80298AD0[gGfxFbIndex]++;
}

void uvGfxDisplayList(Gfx* dl) {
    gSPDisplayList(gGfxDisplayListHead++, dl);
}

void uvGfx_802210E8(uvGfxState_t* arg0) {
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
    uvGfx_802234F4(&temp, 1);
    gSPDisplayList(gGfxDisplayListHead++, (s32)arg0->unk8);
    uvGfx_802236A8();

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

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/uvGfxStateDraw.s")

void uvGfxPushMtxUnk(Mtx4F* arg0) {
    Mtx4F spC8;
    Mtx4F sp88;
    Mtx4F sp48;

    uvMat4Copy(&D_802B4888, arg0);
    uvMat4Copy(&sp48, &D_802B4888);
    uvMat4SetIdentity(&sp88);
    uvMat4RotateAxis(&sp88, -1.5707963f, 0x78);
    uvMat4Mul(&D_802B4888, &sp48, &sp88);
    uvMat4SetUnk1(&spC8);
    uvGfxPushMtxView(*(Mtx*)&spC8);
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/uvGfxClampLook.s")

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

void uvGfx_80222100(Mtx4F* arg0) {
    Mtx4F sp48;
    uvMat4CopyF2L(&sp48, arg0);
    uvGfxPushMtxProj(*(Mtx*)&sp48);
}

void uvGfx_80222170(s32 arg0) {
    D_80249230 = arg0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/uvGfxEnd.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/uvGfxClipViewport.s")

void uvGfx_80223094(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    uvGfxClipViewport(&gGfxViewports[arg0], arg1, arg2, arg3, arg4);
}

void uvGfx_802230CC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    uvGfxClipViewport(&gGfxViewports[arg0 + 2], arg1, arg2, arg3, arg4);
    uvGfxSetViewport(arg0 + 2);
}

void uvGfxSetViewport(s32 vp_id) {
    uvGfxViewport_t* vp;
    vp = &gGfxViewports[vp_id];

    gSPViewport(gGfxDisplayListHead++, (u32)vp + 0x80000010);
    gDPSetScissor(gGfxDisplayListHead++, G_SC_NON_INTERLACE, vp->x0, 0xF0 - vp->y1, vp->x1, 0xF0 - vp->y0);
    gGfxViewX0 = vp->x0;
    gGfxViewX1 = vp->x1;
    gGfxViewY0 = vp->y0;
    gGfxViewY1 = vp->y1;
}

void uvGfxMstackPushUnk(Mtx4F* src) {
    gGfxMstackIdx += 1;
    if (gGfxMstackIdx >= UV_GFX_NUM_MATRICES) {
        _uvDebugPrintf("gfx : too many double buffered matrices [%d]\n", gGfxMstackIdx);
        gGfxMstackIdx -= 1;
        return;
    }
    uvMat4CopyF2L((Mtx4F*)&gGfxMstack[gGfxFbIndex][gGfxMstackIdx], src);
}

void uvGfxMstackPush(Mtx src) {
    gGfxMstackIdx += 1;
    if (gGfxMstackIdx >= UV_GFX_NUM_MATRICES) {
        _uvDebugPrintf("gfx : too many double buffered matrices [%d]\n", gGfxMstackIdx);
        gGfxMstackIdx -= 1;
        return;
    }
    uvMat4CopyL((Mtx4F*)&gGfxMstack[gGfxFbIndex][gGfxMstackIdx], src);
}

Mtx* uvGfxMstackTop(void) {
    return &gGfxMstack[gGfxFbIndex][gGfxMstackIdx];
}

void uvGfx_80223408(f32 arg0) {
    D_8024921C = arg0;
}

f32 uvGfx_80223414(void) {
    if (D_8024921C > 0.0f) {
        return D_8024921C;
    }
    return D_802491D8[gGfxFbIndex ^ 1];
}

void uvGfx_8022345C(Mtx4F* src, s32 push) {
    s32 flags;

    uvGfxMstackPushUnk(src);
    if (push != 0) {
        flags = G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_PUSH;
    } else {
        flags = G_MTX_MODELVIEW | G_MTX_LOAD;
    }
    gSPMatrix(gGfxDisplayListHead++, osVirtualToPhysical(uvGfxMstackTop()), flags);
    D_80298AD0[gGfxFbIndex]++;
}

void uvGfx_802234F4(Mtx4F* src, s32 push) {
    s32 flags;

    uvGfxMstackPushUnk(src);
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

    uvGfxMstackPush(src);
    if (push != 0) {
        flags = G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH;
    } else {
        flags = G_MTX_MODELVIEW | G_MTX_MUL;
    }
    gSPMatrix(gGfxDisplayListHead++, osVirtualToPhysical(uvGfxMstackTop()), flags);
    D_80298AD0[gGfxFbIndex]++;
    D_80298AD8[gGfxFbIndex]++;
}

void uvGfx_802236A8(void) {
    gSPPopMatrix(gGfxDisplayListHead++, G_MTX_MODELVIEW);
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/uvGfx_802236CC.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/uvGfx_80223A64.s")

void uvGfx_80223B80(void) {
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

void uvGfx_80223BF4(s32 arg0) {
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
    _uvMediaCopy(dst, src, 0x25800U);
}

