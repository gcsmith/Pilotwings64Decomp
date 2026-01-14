#include "common.h"
#include <uv_graphics.h>
#include <uv_memory.h>

typedef struct {
    u32 pad0;
    u32 pad4;
    s32 unk8;
    u32 padC;
} Unk80219270UnkC;

typedef struct {
    s32 unk0;
    u32 pad4;
    s8 unk8;
    s8 unk9;
    u16 unkA;
    Unk80219270UnkC* unkC;
    s32 unk10[0x2C]; // unknown size, 0x2C based on mem alloc in func_80219270
                     // (0xC0 allocated)
} Unk80219270;

extern u32 D_802B69E4;

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_19B50/func_80218BA0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_19B50/func_80218CA4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_19B50/uvSeqModel.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_19B50/uvSeqProps.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_19B50/func_80218F88.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_19B50/func_8021902C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_19B50/func_80219240.s")

Unk80219270* func_80219270(s32 arg0) {
    Unk80219270* ret;
    s32 temp_v0;
    u32 sp64;
    s32* sp60;
    s32 i;
    s32 var_s2;
    s32 sp54;
    s32 var_v0;

    var_s2 = 0;
    ret = (Unk80219270*)_uvMemAlloc(sizeof(Unk80219270), 4);
    temp_v0 = func_80223E80((&D_802B69E4)[arg0]);
    while ((var_v0 = func_80223F7C(temp_v0, &sp64, (void**)&sp60, 1)) != NULL) {
        switch (var_v0) {
        case 'STRG':
            ret->unk0 = _uvMemAlloc(sp64, 4);
            _uvMediaCopy((void*)ret->unk0, sp60, sp64);
            break;
        case 'FRMT':
            ret->unk8 = sp60[0];
            ret->unk9 = sp60[1];
            break;
        case 'BITM':
            sp54 = (s32)(sp64 >> 4);
            ret->unkC = (Unk80219270UnkC*)_uvMemAlloc(sp64, 8);
            _uvMediaCopy((void*)ret->unkC, sp60, sp64);
            break;
        case 'IMAG':
            ret->unk10[var_s2] = _uvMemAlloc(sp64, 8);
            _uvMediaCopy((void*)ret->unk10[var_s2], sp60, sp64);
            var_s2 += 1;
            break;
        default:
            break;
        }
    }

    func_80223F30(temp_v0);
    for (i = 0; i < sp54; i++) {
        ret->unkC[i].unk8 = ret->unk10[ret->unkC[i].unk8];
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
