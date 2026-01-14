#include <PR/os_internal.h>
#include <uv_graphics.h>
#include <uv_memory.h>
#include <uv_sched.h>

void Thread_App(void* arg);
void Thread_Kernel(void* arg);
void Thread_Render(void* arg);
void app_entrypoint(s32);
void uvSetVideoMode(void);
void func_8022E558(void);

extern u8 app_ROM_START[];
extern u8 app_ROM_END[];
extern u8 app_BSS_START[];
extern u8 app_BSS_END[];
extern u8 app_TEXT_START[];
extern u8 app_TEXT_END[];

extern OSSched gSchedInst;
extern OSThread gAppThread;
extern OSThread gRenderThread;

extern s32 gSchedStack[];
extern s32 gRenderThreadStack[];
extern s32 gAppThreadStack[];

extern s32 D_80249200;
extern OSMesgQueue gPiDmaQ;
extern OSMesgQueue gSiContQ;
extern OSMesgQueue D_802C3300;
extern OSMesgQueue gPiMgrCmdQ;
extern OSMesgQueue D_802C3B50;
extern OSMesgQueue D_802C3B90;

extern OSMesg gPiDmaBuf[];
extern OSMesg gPiMgrCmdBuf[];
extern OSMesg gSiContBuf[];
extern OSMesg D_802C3318[];
extern OSMesg D_802C3B68[];

extern OSContStatus gSiContStatus;
extern u8 gSiContPattern;

extern OSIoMesg gPiDmaBlockReq;
extern s32 gNmiAsserted;
extern s32 D_802C32A4;
extern s32 D_802C331C;

s32 func_8022E2D4(s32 arg0);
void func_8022E2DC(char arg0);

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/main/uvFileWrite.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/main/uvFileRead.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/main/uvSysInit.s")

s32 func_8022E2D4(s32 arg0) {
    return arg0;
}

void func_8022E2DC(char arg0) {
    switch (arg0) {
    case 0:
        osRecvMesg(&gPiDmaQ, NULL, 1);
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

void uvSetVideoMode(void) {
    s32 viMode;

    osCreateMesgQueue(&D_802C3B90, D_802C3B68, 0xA);
    // clang-format off: statements need to be on same line for matching
    switch (osTvType) {
    case 0:  viMode = 0x10; _uvDebugPrintf("PAL video mode\n"); break;
    case 1:  viMode = 0x02; _uvDebugPrintf("NTSC video mode\n"); break;
    default: viMode = 0x10; _uvDebugPrintf("PAL video mode\n"); break;
    }
    // clang-format on
    _uvScCreateScheduler(&gSchedInst, gSchedStack, 0x7F, viMode, 1);
    _uvScAddClient(&gSchedInst, (OSScClient*)gSchedStack, &D_802C3B50);
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/main/bootproc.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/main/func_8022E558.s")

void Thread_Render(void* arg) {
    void* sp1C;

    sp1C = NULL;
    osCreateMesgQueue(&D_802C3300, D_802C3318, 1);
    osSetEventMesg(OS_EVENT_FAULT, &D_802C3300, (void*)0x10);
    osRecvMesg(&D_802C3300, &sp1C, 1);
    D_802C331C = __osGetActiveQueue()->context.pc;
    while (1) {
        uvGfxBegin();
        func_8022E558();
        uvGfxEnd();
    }
}

void Thread_App(void* arg) {
    _uvMediaCopy(app_TEXT_START, app_ROM_START, app_ROM_END - app_ROM_START);
    uvMemSet(app_BSS_START, 0, app_BSS_END - app_BSS_START);
    app_entrypoint(arg);
}

void Thread_Kernel(void* arg) {
    osCreatePiManager(OS_PRIORITY_PIMGR, &gPiMgrCmdQ, gPiMgrCmdBuf, 8);
    osCreateMesgQueue(&gPiDmaQ, gPiDmaBuf, 1);
    osCreateThread(&gRenderThread, 0, Thread_Render, NULL, gRenderThreadStack, 0xFA);
    osStartThread(&gRenderThread);
    uvSetVideoMode();
    osCreateThread(&gAppThread, 6, Thread_App, arg, gAppThreadStack, 0xA);
    if (D_802C32A4 == 0) {
        osStartThread(&gAppThread);
    }
    osSetThreadPri(NULL, 0);
    while (1) { }
}

u8 func_8022EA80(void) {
    u8 temp;
    OSMesg sp68;
    OSMesgQueue sp50;
    OSTimer sp30;
    OSMesg sp2C;

    osCreateMesgQueue(&sp50, &sp68, 2);
    osSetTimer(&sp30, 0x1388, 0, &sp50, &sp68);
    osRecvMesg(&sp50, &sp2C, 1);
    osCreateMesgQueue(&gSiContQ, gSiContBuf, 3);
    osSetEventMesg(OS_EVENT_SI, &gSiContQ, (void*)0x33333333);
    osContInit(&gSiContQ, &gSiContPattern, &gSiContStatus);
    temp = gSiContPattern;
    return temp;
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/main/func_8022EB38.s")

void _uvDebugPrintf(char* fmt, ...) {
}

void _uvDMA(void* vAddr, u32 devAddr, u32 nbytes) {
    s32 dest = vAddr;
    if (gNmiAsserted == 0) {
        if (dest % 8) {
            _uvDebugPrintf("_uvDMA: RAM address not 8 byte aligned 0x%x\n", dest);
            return;
        }
        if ((s32)devAddr % 2) {
            _uvDebugPrintf("_uvDMA: ROM address not 2 byte aligned 0x%x\n", devAddr);
            return;
        }
        if ((u32)osMemSize < nbytes) {
            _uvDebugPrintf("_uvDMA: nbytes invalid %d\n", (s32)nbytes);
            return;
        }
        if (nbytes & 1) {
            nbytes = (nbytes + 1) & ~1;
        }
        osWritebackDCache((void*)dest, (s32)nbytes);
        osPiStartDma(&gPiDmaBlockReq, 0, 0, devAddr, (void*)dest, nbytes, &gPiDmaQ);
        osInvalDCache((void*)dest, (s32)nbytes);
        func_8022E2DC(0);
    }
}

void _uvAssertMsg(char* expr, char* filename, s32 line) {
    _uvDebugPrintf("%s:%d  %s\n", filename, line, expr);
}
