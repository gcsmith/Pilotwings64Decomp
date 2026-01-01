#include <uv_memory.h>

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2B370/func_8022A3C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2B370/func_8022A47C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2B370/uvSysInit.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2B370/func_8022A5F4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2B370/_uvJumpHeap.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2B370/_uvMediaCopy.s")

// #pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2B370/uvMemRead.s")
u64 uvMemRead(void* vAddr, u32 nbytes) {
    u64 out;
    u64 temp1;
    s64 temp2;
    u8* src;

    src = vAddr;
    if ((nbytes != 1) && (nbytes != 2) && (nbytes != 4) && (nbytes != 8)) {
        _uvDebugPrintf("uvMemRead was called with an invalid size\n");
        out = 0;
    } else if ((u32)src & 0x80000000) {
        out = src[0];
        if (nbytes >= 2U) {
            temp1 = out << 8;
            out = temp1 | src[1];
        }
        if (nbytes >= 3U) {
            temp1 = out << 16;
            out = temp1 | (src[2] << 8) | src[3];
        }
        if (nbytes >= 5U) {
            temp1 = out << 32;
            out = temp1 | (src[4] << 0x18) | (src[5] << 0x10) | (src[6] << 8) | src[7];
        }
    } else {
        _uvMediaCopy(&temp2, src, nbytes);
        out = uvMemRead((u8*)&temp2, nbytes);
    }
    return out;
}

// #pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2B370/uvMemSet.s")
void uvMemSet(void* vAddr, u8 value, u32 nbytes) {
    u32 count;
    u8* dest;

    count = 0;
    if (nbytes != 0) {
        dest = vAddr;
        do {
            count += 1;
            *dest++ = value;
        } while (count < nbytes);
    }
}


#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2B370/func_8022AAB4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2B370/_uvMemOverAlloc.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2B370/_uvMemAlloc.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2B370/_uvMemFreeScratch.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2B370/_uvMemGetScratch.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2B370/_uvMemGetBlocks.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2B370/uvLevelInit.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2B370/func_8022B078.s")
