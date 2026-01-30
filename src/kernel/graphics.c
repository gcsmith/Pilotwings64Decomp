#include <uv_graphics.h>
#include <uv_memory.h>
#include <uv_sched.h>

void func_80218CA4(void);
void func_8021A298(void);
void func_8021F30C(s32);
void func_80220E0C(void);
void func_802301A4(void);
void uvEventPost(s32, s32);

extern s32 D_802491E8;
extern s32 D_802491EC;
extern s32 D_80249200;
extern f32 D_8024921C;
extern s32 D_80249230;

extern s32 D_80298AB8[];
extern s32 D_80298AC0[];
extern s32 D_80298AC8[];
extern s32 D_80298AD0[];
extern s32 D_80298AD8[];

typedef Mtx MtxStack_t[0x15E];

extern s32 gGfxBeginFlag;
extern Gfx* gGfxDisplayListHead;
extern void* gGfxFbCurrPtr;
extern u16 gGfxFbIndex;
extern s32 gGfxLookCount;
extern s16 gGfxMstackIdx;
extern MtxStack_t gGfxMstack[2];
extern u8* gGfxFbPtrs[2];

extern s16 D_802A9980;
extern s16 D_802A9982;
extern s16 D_802A9984;
extern s16 D_802A9986;

extern s32 D_80298ABC[];
extern s32 D_80298AC4[];
extern s32 D_80298ACC[];
extern s32 D_80298AD4[];
extern s32 D_80298ADC[];

typedef LookAt uvLookStorage_t[0x1E];
extern uvLookStorage_t D_80298AE8[2];

extern s32 gGfxStateStackData;
extern u32 gGfxStateStack[];
extern u8 gGfxStateStackIdx;

extern Mtx4F D_802B4888;

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/uvGfxInit.s")

void uvGfxBegin(void) {
    if (gGfxBeginFlag == 1) {
        _uvDebugPrintf("uvGfxBegin: 2 calls in a row.  Must call uvGfxEnd first\n");
        return;
    }
    gGfxBeginFlag = 1;
    uvEventPost(0, 0);
    gSPSegment(gGfxDisplayListHead++, 0x00, 0x00000000);
    gDPSetColorImage(gGfxDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, osVirtualToPhysical(gGfxFbCurrPtr));

    func_80220E0C();
    func_80218CA4();
    func_802301A4();
    func_8021F30C(1);
    func_8021A298();

    D_80298AB8[gGfxFbIndex] = 0;
    D_80298AC0[gGfxFbIndex] = 0;
    D_80298AC8[gGfxFbIndex] = 0;
    D_80298AD0[gGfxFbIndex] = 0;
    D_80298AD8[gGfxFbIndex] = 0;
    gGfxLookCount = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80220CA0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80220E0C.s")

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

void func_802210C4(Gfx* dl) {
    gSPDisplayList(gGfxDisplayListHead++, dl);
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_802210E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/uvGfxStateDraw.s")

void func_80221A78(Mtx4F* arg0) {
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

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/uvClampFunction.s")

void uvProcessLooks(Mtx4F* arg0) {
    Mtx4F temp;

    if (gGfxLookCount >= 0x1E) {
        _uvDebugPrintf("too many looks\n");
        return;
    }

    uvMat4UnkOp4(&temp, &D_802B4888);
    uvClampFunction(&D_80298AE8[gGfxFbIndex][gGfxLookCount], temp.m[3][0], temp.m[3][1], temp.m[3][2], arg0->m[3][0], arg0->m[3][1], arg0->m[3][2], 0.0f, 1.0f,
                    0.0f);
    gSPLookAt(gGfxDisplayListHead++, &D_80298AE8[gGfxFbIndex][gGfxLookCount]);
    gGfxLookCount += 1;
}

void func_80222100(Mtx4F* arg0) {
    Mtx4F sp48;
    uvMat4SetUnk6(&sp48, arg0);
    uvGfxPushMtxProj(*(Mtx*)&sp48);
}

void func_80222170(s32 arg0) {
    D_80249230 = arg0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/uvGfxEnd.s")

void uvGfxClearScreen(u8 r, u8 g, u8 b, u8 a) {
    gDPPipeSync(gGfxDisplayListHead++);
    gDPSetCycleType(gGfxDisplayListHead++, G_CYC_FILL);
    gDPSetColorImage(gGfxDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, osVirtualToPhysical(gGfxFbCurrPtr));
    gDPSetFillColor(gGfxDisplayListHead++, GPACK_RGBA5551(r, g, b, a) << 16 | GPACK_RGBA5551(r, g, b, a));
    gDPFillRectangle(gGfxDisplayListHead++, D_802A9980, (0xF0 - D_802A9986), (D_802A9982 - 1), (0xEF - D_802A9984));
    gDPPipeSync(gGfxDisplayListHead++);
    gDPSetCycleType(gGfxDisplayListHead++, G_CYC_2CYCLE);
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80222A98.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80222C94.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80222D78.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80222E90.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80222EE8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80223094.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_802230CC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80223114.s")

void uvGfxMstackPushUnk(Mtx4F* src) {
    gGfxMstackIdx += 1;
    if (gGfxMstackIdx >= 0x15E) {
        _uvDebugPrintf("gfx : too many double buffered matrices [%d]\n", gGfxMstackIdx);
        gGfxMstackIdx -= 1;
        return;
    }
    uvMat4SetUnk6((Mtx4F*)&gGfxMstack[gGfxFbIndex][gGfxMstackIdx], src);
}

void uvGfxMstackPush(Mtx src) {
    gGfxMstackIdx += 1;
    if (gGfxMstackIdx >= 0x15E) {
        _uvDebugPrintf("gfx : too many double buffered matrices [%d]\n", gGfxMstackIdx);
        gGfxMstackIdx -= 1;
        return;
    }
    uvMat4CopyL((Mtx4F*)&gGfxMstack[gGfxFbIndex][gGfxMstackIdx], src);
}

Mtx* uvGfxMstackTop(void) {
    return &gGfxMstack[gGfxFbIndex][gGfxMstackIdx];
}

void func_80223408(f32 arg0) {
    D_8024921C = arg0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80223414.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_8022345C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_802234F4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_802235A4.s")

void func_802236A8(void) {
    gSPPopMatrix(gGfxDisplayListHead++, G_MTX_MODELVIEW);
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_802236CC.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/uvGfxStatePop.s")

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

void func_80223A28(s32 flags) {
    uvGfxState_t sp20;
    s32 pad;

    sp20.unk8 = 0;
    sp20.unk0 = (gGfxStateStackData & ~0xFFF) | flags;
    uvGfxStateDraw(&sp20);
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80223A64.s")

void func_80223B80(void) {
    if (D_80249200 != 0) {
        uvWaitForMesg(UV_MESG_GFX);
        D_80249200 = 0;
    }
}

void func_80223BB8(s32 arg0) {
    D_802491EC = arg0;
    if (arg0 != 0) {
        osViSetSpecialFeatures(1U);
        return;
    }
    osViSetSpecialFeatures(2U);
}

void func_80223BF4(s32 arg0) {
    D_802491E8 = arg0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80223C00.s")

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

