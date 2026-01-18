#include "common.h"
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
    temp_v0 = func_80223E80((&D_802B69E4)[arg0]);
    while ((tag = func_80223F7C(temp_v0, &nbytes, (void**)&srcAddr, 1)) != NULL) {
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

    func_80223F30(temp_v0);
    // update indexes to pointers allocated above
    for (i = 0; i < bitmCount; i++) {
        ret->bitm[i].imageRef = ret->imag[ret->bitm[i].imageRef];
    }
    return ret;
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_19B50/uvFontSet.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_19B50/func_80219550.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_19B50/func_8021956C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_19B50/func_802195A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_19B50/func_802195DC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_19B50/func_802196B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_19B50/func_802196EC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_19B50/func_802197EC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_19B50/func_80219828.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_19B50/func_80219874.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_19B50/func_80219ACC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_19B50/func_80219CC0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_19B50/func_80219DA4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_19B50/func_80219EA8.s")
