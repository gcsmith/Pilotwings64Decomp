#include "common.h"
#include <uv_dobj.h>
#include <uv_util.h>
#include <libc/stdarg.h>
#include <uv_graphics.h>

extern u16 D_80269CB0[100];
extern u16 D_80269F0A;
extern Mtx4F D_80265080[300];

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/dobj/uvDobjModel.s")

void uvDobjProps(s32 arg0, ...) {
    s16 a1;
    f32 f0;
    Unk80263780* temp_s1;
    s32 var_v0;
    s32 var_v1;
    va_list args;

    if (arg0 >= 0x64) {
        _uvDebugPrintf("uvDobjProps - invalid object id number [%d]\n", arg0);
        return;
    }

    temp_s1 = &D_80263780[arg0];
    if (temp_s1->unk0 == 0xFFFF) {
        _uvDebugPrintf("uvDobjProps: cannot be set before mod id\n");
        return;
    }

    va_start(args, arg0);
    while (1) {
        a1 = va_arg(args, s32);
        switch (a1) {
        case 0:
            return;
        case 3:
            f0 = va_arg(args, f64);
            temp_s1->unk38 = gGfxUnkPtrs->unkC8[temp_s1->unk0]->unk1C * f0;
            break;
        case 4:
            var_v0 = va_arg(args, s32);
            temp_s1->unk3C &= ~(1 << var_v0);
            break;
        case 5:
            var_v0 = va_arg(args, s32);
            temp_s1->unk3C |= (1 << var_v0);
            break;
        default:
            _uvDebugPrintf("uvDobjProps: unknown property [%d]\n", a1);
            break;
        }
    }
    va_end(args);
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/dobj/uvDobjPosm.s")

void uvDobjGetPosm(s32 arg0, s32 arg1, Mtx4F* arg2) {
    Unk80263780* sp24;
    uvGfxUnkStructC8* temp_v0;

    if (arg0 >= 0x65) {
        _uvDebugPrintf("uvDobjPosm - invalid object id number [%d]\n", arg0);
        return;
    }
    sp24 = &D_80263780[arg0];
    if (sp24->unk0 >= 0x190) {
        _uvDebugPrintf("uvDobjGetPosm: null object id %d\n", arg0);
        return;
    }
    uvMat4Copy(arg2, &D_80265080[sp24->unk2[arg1]]);
    temp_v0 = gGfxUnkPtrs->unkC8[sp24->unk0];
    if (arg1 == 0) {
        if (temp_v0->unk20 != 1.0f) {
            uvMat4UnkOp3(arg2, temp_v0->unk20, temp_v0->unk20, temp_v0->unk20);
        }
    } else {
        arg2->m[3][0] /= temp_v0->unk20;
        arg2->m[3][1] /= temp_v0->unk20;
        arg2->m[3][2] /= temp_v0->unk20;
    }
}

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
