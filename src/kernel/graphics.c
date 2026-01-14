#include <uv_graphics.h>
#include <uv_memory.h>
#include <uv_memory.h>

typedef struct UnkStruct_gfx_8b {
    s32 unk0;
    s32 unk4;
} UnkStruct_gfx_8b_t;

typedef struct UnkStruct_gfx_16b {
    u32 address;
    u32 tag;
    u32 unk8;
    u32 offset;
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
extern u8 D_802A9988[0xAF00];
extern u8* D_80299270[2];

extern s32 gGfxStateStackData;
extern u32 gGfxStateStack[];
extern u8 gGfxStateStackIdx;

// bss? start 0x8024DF10
extern char D_8024DF40[]; // = "Ran out of IFF file ids.  (IFF_NIFFS==%d)";

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80220960.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/uvGfxBegin.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80220CA0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80220E0C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80220F2C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80220FF8.s")

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
    UnkStruct_gfx_8b_t* temp_v1;

    temp_v1 = D_80298AB0++;
    temp_v1->unk4 = 0;
    temp_v1->unk0 = 0xBD000000;
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

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_802239B4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_802239EC.s")

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

#ifdef NON_MATCHING
#pragma GLOBAL_ASM("asm/nonmatchings/kernel/graphics/func_80223E80.s")
#else
// rodata mismatch
s32 func_80223E80(s32 addr) {
    UnkStruct_gfx_16b_t* ptr;
    s32 idx;

    ptr = D_802B5300;
    for (idx = 0; idx != 1; idx++) {
        if (ptr->address == 0) {
            break;
        }
        ptr++;
    }
    if (idx == 1) {
        _uvDebugPrintf(D_8024DF40, 1);
        return -1;
    }
    ptr->address = addr;
    ptr->unk8 = (u32)uvMemRead(addr + 4, 4) + 8;
    ptr->tag = (u32)uvMemRead(addr + 8, 4);
    func_8022427C(idx);
    return idx;
}
#endif

void func_80223F30(s32 arg0) {
    if ((arg0 >= 0) && (arg0 <= 0)) {
        D_802B5300[arg0].address = 0;
    }
}

s32 func_80223F54(s32 arg0) {
    return D_802B5308[arg0].address;
}

s32 func_80223F68(s32 arg0) {
    return D_802B5304[arg0].address;
}

s32 func_80223F7C(s32 idx, u32* sizeOut, void** arg2, s32 arg3) {
    u32 pad;
    s32 tag;
    u32 tmpSize;
    u32 size;
    void* scratchMem;
    u8* temp_v0;
    void* scratchMem2;
    UnkStruct_gfx_16b_t* dataInfo;

    dataInfo = &D_802B5300[idx];

    if (dataInfo->offset >= dataInfo->unk8) {
        return NULL;
    }
    if (sizeOut == NULL) {
        sizeOut = &tmpSize;
    }
    tag = (s32)uvMemRead((void*)(dataInfo->address + dataInfo->offset), 4);
    *sizeOut = (u32)uvMemRead((void*)(dataInfo->address + dataInfo->offset + 4), 4);
    *arg2 = (void*)(dataInfo->address + dataInfo->offset + 8);
    if (tag == 'GZIP') { // 0x475A4950
        size = (u32)uvMemRead((void*)(dataInfo->address + dataInfo->offset + 0xC), 4);
        if (!(arg3 & 2)) {
            scratchMem = _uvMemGetScratch(size);
            temp_v0 = D_80299270[D_8024920C];
            _uvMediaCopy((void*)temp_v0, *arg2, *sizeOut);
            mio0_decompress(&temp_v0[8], scratchMem);
            _uvMemFreeScratch(scratchMem);
            *arg2 = scratchMem;
            tag = (u32)uvMemRead((void*)(dataInfo->address + dataInfo->offset + 8), 4);
            dataInfo->offset += *sizeOut + 8;
            *sizeOut = size;
        }
    } else {
        if ((((u32)*arg2 & 0x80000000) != 0) == 0 && (arg3 & 0x1)) {
            scratchMem2 = _uvMemGetScratch(*sizeOut);
            _uvMemFreeScratch(scratchMem2);
            _uvMediaCopy(scratchMem2, *arg2, *sizeOut);
            *arg2 = scratchMem2;
        }
        dataInfo->offset += *sizeOut + 8;
    }
    return tag;
}

s32 func_80224170(s32 arg0, void* arg1, void** arg2, s32 tag, s32 palette, s32 arg5) {
    s32 currentPalette;
    s32 var_s1;
    s32 outTag;
    u32 offsetTemp;
    UnkStruct_gfx_16b_t* sp3C;

    sp3C = &D_802B5300[arg0];
    currentPalette = 0;
    offsetTemp = sp3C->offset;
    func_8022427C(arg0);
    if (palette <= 0) {
        var_s1 = arg5;
    } else {
        var_s1 = 2;
    }

    while ((outTag = func_80223F7C(arg0, (u32*)arg1, arg2, var_s1))) {
        if (outTag == tag) {
            if (currentPalette++ >= palette) {
                break;
            }
            if (currentPalette >= palette) {
                var_s1 = arg5;
            }
        }
    }
    sp3C->offset = offsetTemp;
    return outTag;
}

void func_8022427C(s32 arg0) {
    D_802B530C[arg0].address = 0xC;
}

