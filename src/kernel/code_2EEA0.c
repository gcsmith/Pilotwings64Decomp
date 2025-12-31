#include "common.h"

s32 func_8022E2D4(s32 arg0);
void func_8022E2DC(char arg0);
void _uvDebugPrintf(char *arg, ...);
void _uvDMA(s32 arg0, s32 arg1, u32 arg2);
void _uvAssertMsg(char* arg0, char* arg1, s32 arg2);

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

// #pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2EEA0/Thread_Render.s")
OSThread* __osGetActiveQueue(void);                         /* extern */
void func_8022E558(void);                                  /* extern */
void uvGfxBegin(void);                                     /* extern */
void uvGfxEnd(void);                                       /* extern */
extern OSMesgQueue D_802C3300;
extern void* D_802C3318;
extern s32 D_802C331C;

void Thread_Render(void* arg0) {
    void* sp1C;

    sp1C = NULL;
    osCreateMesgQueue(&D_802C3300, &D_802C3318, 1);
    osSetEventMesg(0xCU, &D_802C3300, (void* )0x10);
    osRecvMesg(&D_802C3300, &sp1C, 1);
    D_802C331C = __osGetActiveQueue()->context.pc;
    while (1) {
        uvGfxBegin();
        func_8022E558();
        uvGfxEnd();
    }
}

// #pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2EEA0/Thread_App.s")
void _uvMediaCopy(void*, void*, s32);                        /* extern */
void app_entrypoint(s32);                              /* extern */
void uvMemSet(void*, u8, s32);                             /* extern */
extern u8 D_51E30;
extern s32 D_802CA900;
extern u8 D_803571F0;
extern u8 D_803805E0;
extern u8 D_DE720;

void Thread_App(void *arg0) {
    _uvMediaCopy(&D_802CA900, &D_51E30, &D_DE720 - &D_51E30);
    uvMemSet(&D_803571F0, 0, &D_803805E0 - &D_803571F0);
    app_entrypoint(arg0);
}

// #pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2EEA0/Thread_Kernel.s")
void Thread_App(void*);                             /* extern */
void Thread_Render(void*);                          /* extern */
void uvSetVideoMode(void);                                 /* extern */
extern s32 D_802BBC90;
extern s32 D_802C1C90;
extern s32 D_802C32A4;
extern void* D_802C32BC;
extern OSMesgQueue D_802C32C0;
extern void* D_802C3320;
extern OSMesgQueue D_802C3340;
extern OSThread D_802C3398;
extern OSThread D_802C3548;

void Thread_Kernel(void* arg0) {
    osCreatePiManager(0x96, &D_802C3340, &D_802C3320, 8);
    osCreateMesgQueue(&D_802C32C0, &D_802C32BC, 1);
    osCreateThread(&D_802C3548, 0, Thread_Render, NULL, &D_802BBC90, 0xFA);
    osStartThread(&D_802C3548);
    uvSetVideoMode();
    osCreateThread(&D_802C3398, 6, Thread_App, arg0, &D_802C1C90, 0xA);
    if (D_802C32A4 == 0) {
        osStartThread(&D_802C3398);
    }
    osSetThreadPri(NULL, 0);
    while(1) { }
}

// #pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2EEA0/func_8022EA80.s")
extern OSMesg D_802C32D8;
extern OSMesgQueue D_802C32E8;
extern OSContStatus D_802C3358;
extern u8 D_802C3394;

u8 func_8022EA80(void) {
    u8 temp;
    OSMesg sp68;
    OSMesgQueue sp50;
    OSTimer sp30;
    OSMesg sp2C;

    osCreateMesgQueue(&sp50, &sp68, 2);
    osSetTimer(&sp30, 0x1388, 0, &sp50, &sp68);
    osRecvMesg(&sp50, &sp2C, 1);
    osCreateMesgQueue(&D_802C32E8, &D_802C32D8, 3);
    osSetEventMesg(5U, &D_802C32E8, (void* )0x33333333);
    osContInit(&D_802C32E8, &D_802C3394, &D_802C3358);
    temp = D_802C3394;
    return temp;
}

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

// #pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2EEA0/_uvAssertMsg.s")
void _uvAssertMsg(char* arg0, char* arg1, s32 arg2) {
    _uvDebugPrintf("%s:%d  %s\n", arg1, arg2, arg0);
}

