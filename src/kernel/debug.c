#include "common.h"
#include <uv_controller.h>
#include <uv_graphics.h>
#include <uv_util.h>
#include <uv_debug.h>

// this entire file was compiled with `-mips1 -O1 -g`
// asm_processor doesn't currently work with `-mips1` and `-g`
// so wrapping everything in NON_MATCHING until those details are worked out

typedef struct {
    f64 unk0;
    s32 unk8;
    u8 padC[4];
} Unk802B92A0_Unk0;

typedef struct {
    Unk802B92A0_Unk0 unk0[30];
} Unk802B92A0;

extern Unk802B92A0 D_802B92A0[];
extern s32 gSchedRingIdx;
extern s32 D_802B9C18[];

// forward declarations
void func_8023217C(u8, u8);
void func_802323A8(u8, u8);
void func_80232554(u8);
void func_80232738(u8);
void func_80233FC8(char* fmt, ...);

#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/nonmatchings/kernel/debug/func_80231AC0.s")
#else
f64 func_80231AC0(void) {
    Unk802B92A0_Unk0* sp14;
    s32 sp10;
    s32 spC;
    s32 sp8;
    f64 sp0;

    spC = (gSchedRingIdx + 1) % 5;
    sp8 = 0;
    for (sp10 = 0; sp10 < D_802B9C18[spC]; sp10++) {
        sp14 = &D_802B92A0[spC].unk0[sp10];
        if (sp8 == 0) {
            if (sp14->unk8 == 0x2A) {
                sp8 = 1;
                sp0 = sp14->unk0;
            }
        } else {
            if ((sp8 != 0) && (sp14->unk8 == 0x30)) {
                return sp14->unk0 - sp0;
            }
        }
    }
    return 0.0;
}
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/debug/func_80231C10.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/debug/func_80231C9C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/debug/func_80231F04.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/debug/D_8024F350.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/debug/func_8023217C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/debug/func_802323A8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/debug/func_80232554.s")

#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/nonmatchings/kernel/debug/func_80232738.s")
#else
void func_80232738(u8 arg0) {
    if (arg0 & 0x02) {
        _uvDebugPrintf("tris: %d   ", uvGfxGetCnt(1));
    }
    if (arg0 & 0x01) {
        _uvDebugPrintf("vtx xfms: %d   ", uvGfxGetCnt(0));
    }
    if (arg0 & 0x04) {
        _uvDebugPrintf("mtx loads: %d   ", uvGfxGetCnt(2));
    }
    if (arg0 & 0x10) {
        func_80233FC8("txt loads: %d   ", uvGfxGetCnt(4));
    }
    if (arg0 & 0x08) {
        _uvDebugPrintf("mtx load-mults: %d   ", uvGfxGetCnt(3));
    }
    if (arg0 != 0x00) {
        _uvDebugPrintf("\n");
    }
    // possibly some unused strings after "\n":
    // "frame time %f\n"
    // "started at %f\n"
    // "finished at %f\n"
    // "\n\n"
}
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/debug/func_8023286C.s")

#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/nonmatchings/kernel/debug/func_80232EBC.s")
#else
void func_80232EBC(void) {
}
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/debug/func_80232ECC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/debug/func_80233310.s")

void func_802333AC(u8);
#pragma GLOBAL_ASM("asm/nonmatchings/kernel/debug/func_802333AC.s")

#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/nonmatchings/kernel/debug/func_8023345C.s")
#else
void func_8023345C(u8 arg0, u8 arg1, u8 arg2) {
    if (arg1 == 1) {
        func_802333AC(arg0);
    } else if (arg1 == 2) {
        func_8023217C(arg0, arg2);
    } else {
        func_802323A8(arg0, arg2);
    }
}
#endif

#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/nonmatchings/kernel/debug/uvDbgCnt.s")
#else
void uvDbgCnt(u8 arg0, u8 arg1) {
    if (arg0 == 0) {
        return;
    } else {
        if (arg1 == 1) {
            _uvDebugPrintf("uvDbgCnt: bar count not supported\n");
        } else if (arg1 == 2) {
            func_80232554(arg0);
        } else if (arg1 == 3) {
            func_80232738(arg0);
        }
    }
}
#endif

#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/nonmatchings/kernel/debug/func_80233590.s")
#else
void func_80233590(void) {
    u8* sp2C;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    f32 sp1C;

    sp2C = (u8*)0x80200000;
    sp20 = 0.0f;
    sp1C = 0.0f;
    while (uvIOUpdate() != 0) {
        sp28 = uvControllerGetStick(0, 0);
        sp24 = uvControllerGetStick(0, 1);
        sp20 += sp28 * sp28 * sp28 * 8.0f;
        sp1C += sp24 * sp24 * sp24 * 128.0f;
        if (sp20 > 40.0f) {
            sp20 = 0.0f, sp1C += 1.0f;
        }
        if (sp20 < 0.0f) {
            sp20 = 40.0f, sp1C -= 1.0f;
        }
        if (sp1C < 0.0f) {
            sp1C = 0.0f;
        }
        if (sp1C > 6553.6f) {
            sp1C = 6553.6f;
        }
        sp2C = ((u8*)0x80000000) + ((s32)sp20 * 0x10) + ((s32)sp1C * 0x140 * 2);
        uvGfxBegin();
        uvGfxEnd();
        osViSwapBuffer(sp2C);
        if (uvControllerButtonPress(0, Z_TRIG) != 0) {
            break;
        }
        if (uvControllerButtonPress(0, START_BUTTON) != 0) {
            break;
        }

        if (uvControllerButtonPress(0, A_BUTTON) != 0) {
            _uvDebugPrintf("Address: 0x%x\n", sp2C);
        }
    }
}
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/debug/func_80233810.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/debug/func_80233878.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/debug/func_802338A8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/debug/func_802339B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/debug/func_80233A40.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/debug/func_80233D04.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/debug/func_80233DB8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/debug/func_80233FC8.s")
