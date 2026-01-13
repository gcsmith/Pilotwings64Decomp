#include <uv_graphics.h>
#include <uv_memory.h>

typedef struct UnkStruct_gfx_8b {
    s32 unk0;
    s32 unk4;
} UnkStruct_gfx_8b_t;

typedef struct UnkStruct_gfx_16b {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u32 unkC;
} UnkStruct_gfx_16b_t;

extern s32 D_80249230;
extern f32 D_8024921C;
extern s32 D_802491E8;
extern UnkStruct_gfx_8b_t* D_80298AB0;
extern UnkStruct_gfx_16b_t D_802B5300[];
extern UnkStruct_gfx_16b_t D_802B5304[];
extern UnkStruct_gfx_16b_t D_802B5308[];
extern UnkStruct_gfx_16b_t D_802B530C[];

extern u16 D_8024920C;
extern s16 D_80249218;
extern u8 D_802A9988[];

extern s32 gGfxStateStackData;
extern u32 gGfxStateStack[];
extern u8 gGfxStateStackIdx;

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80220960.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/uvGfxBegin.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80220CA0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80220E0C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80220F2C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80220FF8.s")

// #pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_802210C4.s")
void func_802210C4(s32 arg0) {
    UnkStruct_gfx_8b_t* temp_v1;

    temp_v1 = D_80298AB0++;
    temp_v1->unk4 = arg0;
    temp_v1->unk0 = 0x06000000;
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_802210E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/uvGfxStateDraw.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80221A78.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/uvClampFunction.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/uvProcessLooks.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80222100.s")

// #pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80222170.s")
void func_80222170(s32 arg0) {
    D_80249230 = arg0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/uvGfxEnd.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_802228F0.s")

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

// #pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_802233C4.s")
void* func_802233C4(void) {
    return &D_802A9988[(D_8024920C * 0x5780) + (D_80249218 << 6)];
}

// #pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80223408.s")
void func_80223408(f32 arg0) {
    D_8024921C = arg0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80223414.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_8022345C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_802234F4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_802235A4.s")

// #pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_802236A8.s")
void func_802236A8(void) {
    UnkStruct_gfx_8b_t* temp_v1;

    temp_v1 = D_80298AB0++;
    temp_v1->unk4 = 0;
    temp_v1->unk0 = 0xBD000000;
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_802236CC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/uvGfxGetCnt.s")

// #pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/uvGfxStatePush.s")
void uvGfxStatePush(void) {
    if (gGfxStateStackIdx >= 0x1F) {
        _uvDebugPrintf("uvGfxStatePush: stack full\n");
        return;
    }
    gGfxStateStack[gGfxStateStackIdx++] = gGfxStateStackData;
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/uvGfxStatePop.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_802239B4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_802239EC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80223A28.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80223A64.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80223B80.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80223BB8.s")

// #pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80223BF4.s")
void func_80223BF4(s32 arg0) {
    D_802491E8 = arg0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80223C00.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/uvCopyFrameBuf.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80223E80.s")

// #pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80223F30.s")
void func_80223F30(s32 arg0) {
    if ((arg0 >= 0) && (arg0 <= 0)) {
        D_802B5300[arg0].unk0 = 0;
    }
}

// #pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80223F54.s")
s32 func_80223F54(s32 arg0) {
    return D_802B5308[arg0].unk0;
}

// #pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80223F68.s")
s32 func_80223F68(s32 arg0) {
    return D_802B5304[arg0].unk0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80223F7C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80224170.s")

// #pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_8022427C.s")
void func_8022427C(u32 arg0) {
    D_802B530C[arg0].unk0 = 0xC;
}
