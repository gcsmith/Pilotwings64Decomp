#include "common.h"

s32 func_8022E2D4(s32 arg0);
void func_8022E2DC(char arg0);
void _uvDebugPrintf(char *arg, ...);

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2EEA0/uvFileWrite.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2EEA0/uvFileRead.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2EEA0/uvSysInitEEPROM.s")

// #pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2EEA0/func_8022E2D4.s")
s32 func_8022E2D4(s32 arg0) {
    return arg0;
}

// #pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2EEA0/func_8022E2DC.s")
extern s32 D_80249200;
extern OSMesgQueue D_802C32C0;
extern OSMesgQueue D_802C3B50;
extern OSMesgQueue D_802C3B90;

void func_8022E2DC(char arg0) {
    switch (arg0) {                              
    case 0:
        osRecvMesg(&D_802C32C0, NULL, 1);
        return;
    case 2:
        osRecvMesg(&D_802C3B50, NULL, 1);
        return;
    case 4:
        osRecvMesg(&D_802C3B90, NULL, 1);
        D_80249200 = 0;
        return;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2EEA0/uvSetVideoMode.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2EEA0/bootproc.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2EEA0/func_8022E558.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2EEA0/Thread_Render.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2EEA0/Thread_App.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2EEA0/Thread_Kernel.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2EEA0/func_8022EA80.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2EEA0/func_8022EB38.s")

// #pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2EEA0/_uvDebugPrintf.s")
void _uvDebugPrintf(char *arg, ...) {
}

// #pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2EEA0/_uvDMA.s")
extern s32 D_802B9C80;
extern OSIoMesg D_802C32A8;
extern OSMesgQueue D_802C32C0;

void _uvDMA(s32 arg0, s32 arg1, u32 arg2) {

    if (D_802B9C80 == 0) {
        if (arg0 % 8) {
            _uvDebugPrintf("_uvDMA: RAM address not 8 byte aligned 0x%x\n", arg0);
            return;
        }
        if (arg1 % 2) {
            _uvDebugPrintf("_uvDMA: ROM address not 2 byte aligned 0x%x\n", arg1);
            return;
        }
        if ((u32) osMemSize < arg2) {
            _uvDebugPrintf("_uvDMA: nbytes invalid %d\n", (s32) arg2);
            return;
        }
        if (arg2 & 1) {
            arg2 = (arg2 + 1) & ~1;
        }
        osWritebackDCache((void* ) arg0, (s32) arg2);
        osPiStartDma(&D_802C32A8, 0, 0, (u32) arg1, (void* ) arg0, arg2, &D_802C32C0);
        osInvalDCache((void* ) arg0, (s32) arg2);
        func_8022E2DC(0);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2EEA0/func_8022EE5C.s")

