#include <uv_graphics.h>
#include <uv_memory.h>

typedef struct {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    s32 unk8;
    s32 unkC; // inferred from stack size, but not observed accessed
} Unk802239B4;

extern s32 D_80249230;
extern f32 D_8024921C;
extern s32 D_802491E8;
extern Gfx* D_80298AB0;

extern u16 D_8024920C;
extern s16 D_80249218;
extern u8 D_802A9988[0xAF00];
extern u8* D_80299270[2];

extern void* D_802491F0;
extern s16 D_802A9980;
extern s16 D_802A9982;
extern s16 D_802A9984;
extern s16 D_802A9986;

extern s32 gGfxStateStackData;
extern u32 gGfxStateStack[];
extern u8 gGfxStateStackIdx;

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80220960.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/uvGfxBegin.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80220CA0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80220E0C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80220F2C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80220FF8.s")

void func_802210C4(s32 dl) {
    gSPDisplayList(D_80298AB0++, dl);
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_802210E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/uvGfxStateDraw.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80221A78.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/uvClampFunction.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/uvProcessLooks.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80222100.s")

void func_80222170(s32 arg0) {
    D_80249230 = arg0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/uvGfxEnd.s")

void func_802228F0(u8 r, u8 g, u8 b, u8 a) {
    gDPPipeSync(D_80298AB0++);
    gDPSetCycleType(D_80298AB0++, G_CYC_FILL);
    gDPSetColorImage(D_80298AB0++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, osVirtualToPhysical(D_802491F0));
    gDPSetFillColor(D_80298AB0++, GPACK_RGBA5551(r, g, b, a) << 16 | GPACK_RGBA5551(r, g, b, a));
    gDPFillRectangle(D_80298AB0++, D_802A9980, (0xF0 - D_802A9986), (D_802A9982 - 1), (0xEF - D_802A9984));
    gDPPipeSync(D_80298AB0++);
    gDPSetCycleType(D_80298AB0++, G_CYC_2CYCLE);
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80222A98.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80222C94.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80222D78.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80222E90.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80222EE8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80223094.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_802230CC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80223114.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/uvGfxUnkMatrixOp.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/uvGfxUnkMatrixOp2.s")

void* func_802233C4(void) {
    return &D_802A9988[(D_8024920C * 0x5780) + (D_80249218 << 6)];
}

void func_80223408(f32 arg0) {
    D_8024921C = arg0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80223414.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_8022345C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_802234F4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_802235A4.s")

void func_802236A8(void) {
    gSPPopMatrix(D_80298AB0++, 0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_802236CC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/uvGfxGetCnt.s")

void uvGfxStatePush(void) {
    if (gGfxStateStackIdx >= 0x1F) {
        _uvDebugPrintf("uvGfxStatePush: stack full\n");
        return;
    }
    gGfxStateStack[gGfxStateStackIdx++] = gGfxStateStackData;
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/uvGfxStatePop.s")

void uvGfxSetFlags(s32 flags) {
    Unk802239B4 sp20;
    s32 newState;

    newState = flags | gGfxStateStackData;
    if (newState != gGfxStateStackData) {
        sp20.unk0 = newState;
        sp20.unk8 = 0;
        uvGfxStateDraw(&sp20);
    }
}

void uvGfxClearFlags(s32 flags) {
    Unk802239B4 sp20;
    s32 newState;

    newState = ~flags & gGfxStateStackData;
    if (newState != gGfxStateStackData) {
        sp20.unk0 = newState;
        sp20.unk8 = 0;
        uvGfxStateDraw(&sp20);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80223A28.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80223A64.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80223B80.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80223BB8.s")

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
        fb_id = D_8024920C;
    } else {
        fb_id = D_8024920C ^ 1;
    }
    src = D_80299270[fb_id];
    dst = D_80299270[fb_id ^ 1];
    _uvMediaCopy(dst, src, 0x25800U);
}
