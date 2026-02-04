#include "macros.h"
#include <uv_graphics.h>
#include <uv_memory.h>

typedef struct {
    u32 address;
    u32 tag;
    u32 unk8;
    u32 offset;
} Unk802B5300;

extern u16 gGfxFbIndex;
extern u8* gGfxFbPtrs[2];
extern Unk802B5300 D_802B5300[1];

s32 func_80223E80(s32 addr) {
    Unk802B5300* ptr;
    s32 idx;

    ptr = D_802B5300;
    for (idx = 0; idx != ARRAY_COUNT(D_802B5300); idx++) {
        if (ptr->address == 0) {
            break;
        }
        ptr++;
    }
    if (idx == ARRAY_COUNT(D_802B5300)) {
        _uvDebugPrintf("Ran out of IFF file ids.  (IFF_NIFFS==%d)", 1);
        return -1;
    }
    ptr->address = addr;
    ptr->unk8 = (u32)uvMemRead(addr + 4, 4) + 8;
    ptr->tag = (u32)uvMemRead(addr + 8, 4);
    func_8022427C(idx);
    return idx;
}

void func_80223F30(s32 idx) {
    if ((idx >= 0) && (idx < ARRAY_COUNT(D_802B5300))) {
        D_802B5300[idx].address = 0;
    }
}

s32 func_80223F54(s32 idx) {
    return D_802B5300[idx].unk8;
}

s32 func_80223F68(s32 idx) {
    return D_802B5300[idx].tag;
}

u32 func_80223F7C(s32 idx, u32* sizeOut, void** arg2, s32 arg3) {
    u32 pad;
    u32 tag;
    u32 tmpSize;
    u32 size;
    void* scratchMem;
    u8* temp_v0;
    void* scratchMem2;
    Unk802B5300* dataInfo;

    dataInfo = &D_802B5300[idx];

    if (dataInfo->offset >= dataInfo->unk8) {
        return NULL;
    }
    if (sizeOut == NULL) {
        sizeOut = &tmpSize;
    }
    tag = (u32)uvMemRead((void*)(dataInfo->address + dataInfo->offset), 4);
    *sizeOut = (u32)uvMemRead((void*)(dataInfo->address + dataInfo->offset + 4), 4);
    *arg2 = (void*)(dataInfo->address + dataInfo->offset + 8);
    if (tag == 'GZIP') { // 0x475A4950
        size = (u32)uvMemRead((void*)(dataInfo->address + dataInfo->offset + 0xC), 4);
        if (!(arg3 & 2)) {
            scratchMem = _uvMemGetScratch(size);
            temp_v0 = gGfxFbPtrs[gGfxFbIndex];
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

u32 func_80224170(s32 idx, void* arg1, void** arg2, u32 tag, s32 palette, s32 arg5) {
    s32 currentPalette;
    s32 var_s1;
    u32 outTag;
    u32 offsetTemp;
    Unk802B5300* sp3C;

    sp3C = &D_802B5300[idx];
    currentPalette = 0;
    offsetTemp = sp3C->offset;
    func_8022427C(idx);
    if (palette <= 0) {
        var_s1 = arg5;
    } else {
        var_s1 = 2;
    }

    while ((outTag = func_80223F7C(idx, (u32*)arg1, arg2, var_s1))) {
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

void func_8022427C(s32 idx) {
    D_802B5300[idx].offset = 0xC;
}
