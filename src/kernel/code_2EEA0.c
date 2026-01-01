#include <uv_memory.h>

s32 func_8022E2D4(s32 arg0);
void func_8022E2DC(char arg0);

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
void app_entrypoint(s32);                              /* extern */
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
void _uvDebugPrintf(char *fmt, ...) {
}

// #pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2EEA0/_uvDMA.s")
extern s32 D_802B9C80;
extern OSIoMesg D_802C32A8;
extern OSMesgQueue D_802C32C0;

void _uvDMA(void* vAddr, u32 devAddr, u32 nbytes) {
    s32 dest = vAddr;
    if (D_802B9C80 == 0) {
        if (dest % 8) {
            _uvDebugPrintf("_uvDMA: RAM address not 8 byte aligned 0x%x\n", dest);
            return;
        }
        if ((s32)devAddr % 2) {
            _uvDebugPrintf("_uvDMA: ROM address not 2 byte aligned 0x%x\n", devAddr);
            return;
        }
        if ((u32)osMemSize < nbytes) {
            _uvDebugPrintf("_uvDMA: nbytes invalid %d\n", (s32) nbytes);
            return;
        }
        if (nbytes & 1) {
            nbytes = (nbytes + 1) & ~1;
        }
        osWritebackDCache((void* )dest, (s32)nbytes);
        osPiStartDma(&D_802C32A8, 0, 0, devAddr, (void*) dest, nbytes, &D_802C32C0);
        osInvalDCache((void*)dest, (s32)nbytes);
        func_8022E2DC(0);
    }
}

// #pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2EEA0/_uvAssertMsg.s")
void _uvAssertMsg(char* expr, char* filename, s32 line) {
    _uvDebugPrintf("%s:%d  %s\n", filename, line, expr);
}

