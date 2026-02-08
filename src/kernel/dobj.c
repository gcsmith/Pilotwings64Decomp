#include "common.h"
#include <uv_dobj.h>
#include <uv_util.h>
#include <uv_graphics.h>

extern u16 D_80269CB0[100];
extern u16 D_80269F0A;

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/dobj/uvDobjModel.s")

void uvDobjProps(s32 arg0, s32 arg1, f64 arg2, s32 arg3) {
    s32 a1;
    f32 f0;
    s32 *new_var;
    s32 new_var2;
    s32 temp_s0;
    Unk80263780* temp_s1;
    s32 var_v0;
    s32 var_v1;

    // @fake
    new_var = &arg0;
    if (*new_var >= 0x64) {
        _uvDebugPrintf("uvDobjProps - invalid object id number [%d]\n", *new_var);
        return;
    }
    // @fake
    new_var2 = arg0;
    temp_s0 = (s32)&arg1;
    temp_s1 = &D_80263780[arg0];
    if (temp_s1->unk0 == 0xFFFF) {
        // @fake
        if (f0 && f0) {}
        _uvDebugPrintf("uvDobjProps: cannot be set before mod id\n", new_var2);
        return;
    }
    while (1) {
        temp_s0 = (temp_s0 + 3) & ~3;
        a1 = ((s16*)temp_s0)[1];
        temp_s0 += 4;
        switch (a1) {
        case 0:
            return;
        case 3:
            if (temp_s0 & 1) {
                temp_s0 += 7;
                var_v0 = temp_s0 - 0x16;
            } else {
                if (temp_s0 & 2) {
                    temp_s0 += 0xA;
                    var_v1 = temp_s0 - 0x28;
                } else {
                    temp_s0 = ((temp_s0 + 7) & ~7) + 8;
                    var_v1 = temp_s0;
                }
                var_v0 = var_v1;
            }
            f0 = (f32) ((f64*)var_v0)[-1];
            temp_s1->unk38 = ((f32**)gGfxUnkPtrs)[temp_s1->unk0 + 50][7] * f0;
            break;
        case 4:
            temp_s0 = (temp_s0 + 3) & ~3;
            var_v0 = ((s32*)temp_s0)[0];
            temp_s0 += 4;
            temp_s1->unk3C &= ~(1 << var_v0);
            break;
        case 5:
            temp_s0 = (temp_s0 + 3) & ~3;
            var_v0 = ((s32*)temp_s0)[0];
            temp_s0 += 4;
            temp_s1->unk3C |= (1 << var_v0);
            break;
        default:
            _uvDebugPrintf("uvDobjProps: unknown property [%d]\n", a1);
            break;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/dobj/uvDobjPosm.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/dobj/uvDobjGetPosm.s")

void uvDobjState(s32 arg0, s32 arg1) {
    s32 i;
    s32 j;

    if (arg0 >= 0x65) {
        _uvDebugPrintf("uvDobjState - invalid object id number [%d]\n", arg0);
        return;
    }
    if (arg1 & 4) {
        for (i = 0; i < D_80269F0A; i++) {
            if (arg0 == D_80269CB0[i]) {
                break;
            }
        }
        if (i == D_80269F0A) {
            D_80269CB0[i] = arg0;
            D_80269F0A++;
        }
    } else {
        for (i = 0; i < D_80269F0A; i++) {
            if (arg0 == D_80269CB0[i]) {
                for (j = i; j < D_80269F0A; j++) {
                    D_80269CB0[j] = D_80269CB0[j + 1];
                }
                D_80269F0A--;
            }
        }
    }
    D_80263780[arg0].unk34 = arg1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/dobj/uvDobjSetState.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/dobj/uvDobjSetState2.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/dobj/func_8021731C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/dobj/func_80217398.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/dobj/_uvDobjsDraw.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/dobj/func_8021771C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/dobj/func_80217AB4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/dobj/func_80217B34.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/dobj/func_80217B4C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/dobj/func_80217E24.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/dobj/func_802180DC.s")
