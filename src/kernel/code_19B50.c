#include "common.h"
#include <uv_filesystem.h>
#include <uv_graphics.h>
#include <uv_memory.h>

typedef struct {
    u32 pad0;
    u32 pad4;
    s32 imageRef;
    u32 padC;
} ParsedBITM;

typedef struct {
    void* strg;
    u32 pad4;
    s8 unk8;
    s8 unk9;
    u16 unkA;
    ParsedBITM* bitm;
    void* imag[0x2C]; // unknown size, 0x2C based on mem alloc in uvParseTopUVFT
                      // (0xC0 allocated)
} ParsedUVFT;

// clang-format off
static s16 D_80248E20 = 0x0000;
static s16 D_80248E24[] = {
    0x0000, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000, 0x0000, 0x0000,
    0x0001, 0x1234, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0001, 0x0294, 0x1F08, 0x000F, 0x0080,
};
static u8 D_80248E50[] = {
    0x03, 0x00, 0x00, 0x00, 0x80, 0x26, 0xA0, 0x40, 0x80, 0x26,
    0xA3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

static u8 D_80248E64 = 0xFF;
static u8 D_80248E68 = 0xFF;
static u8 D_80248E6C = 0xFF;
static u8 D_80248E70 = 0xFF;
static u8 D_80248E74 = 0x00;
static u8 D_80248E78 = 0x00;

static f32 D_80248E7C = 1;
static f32 D_80248E80 = 1;
static u32 D_80248E84 = 0;
static u32 D_80248E88 = 8;
static u32 D_80248E8C = 0;
static u32 D_80248E90 = 0;
static u32 D_80248E94 = 0;
// clang-format on

extern u32 D_802B69E4;

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_19B50/func_80218BA0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_19B50/func_80218CA4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_19B50/uvSeqModel.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_19B50/uvSeqProps.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_19B50/func_80218F88.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_19B50/func_8021902C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_19B50/func_80219240.s")

ParsedUVFT* uvParseTopUVFT(s32 arg0) {
    ParsedUVFT* ret;
    s32 temp_v0;
    u32 nbytes;
    s32* srcAddr;
    s32 i;
    s32 imagCount;
    s32 bitmCount;
    u32 tag;

    imagCount = 0;
    ret = (ParsedUVFT*)_uvMemAlloc(sizeof(ParsedUVFT), 4);
    temp_v0 = uvFileReadHeader((&D_802B69E4)[arg0]);
    while ((tag = uvFileReadBlock(temp_v0, &nbytes, (void**)&srcAddr, 1)) != NULL) {
        switch (tag) {
        case 'STRG':
            ret->strg = _uvMemAlloc(nbytes, 4);
            _uvMediaCopy((void*)ret->strg, srcAddr, nbytes);
            break;
        case 'FRMT':
            ret->unk8 = srcAddr[0];
            ret->unk9 = srcAddr[1];
            break;
        case 'BITM':
            bitmCount = nbytes / sizeof(ParsedBITM);
            ret->bitm = (ParsedBITM*)_uvMemAlloc(nbytes, 8);
            _uvMediaCopy((void*)ret->bitm, srcAddr, nbytes);
            break;
        case 'IMAG':
            ret->imag[imagCount] = _uvMemAlloc(nbytes, 8);
            _uvMediaCopy((void*)ret->imag[imagCount], srcAddr, nbytes);
            imagCount++;
            break;
        default:
            break;
        }
    }

    uvFile_80223F30(temp_v0);
    // update indexes to pointers allocated above
    for (i = 0; i < bitmCount; i++) {
        ret->bitm[i].imageRef = ret->imag[ret->bitm[i].imageRef];
    }
    return ret;
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_19B50/uvFontSet.s")

void uvFont_80219550(f64 arg0, f64 arg1) {
    D_80248E7C = (f32)arg0;
    D_80248E80 = (f32)arg1;
}

void uvFont_8021956C(u8 arg0, u8 arg1, u8 arg2, u8 arg3) {
    D_80248E64 = arg0;
    D_80248E68 = arg1;
    D_80248E6C = arg2;
    D_80248E70 = arg3;
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_19B50/func_802195A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_19B50/func_802195DC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_19B50/func_802196B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_19B50/func_802196EC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_19B50/uvFontWidth.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_19B50/func_80219828.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_19B50/func_80219874.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_19B50/uvFont_80219ACC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_19B50/func_80219CC0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_19B50/func_80219DA4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_19B50/uvFont_80219EA8.s")
