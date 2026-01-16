#include <PR/os_cont.h>
#include <PR/os_eeprom.h>
#include <PR/os_internal.h>
#include <PR/os_system.h>
#include <PR/os_host.h>
#include <uv_audio.h>
#include <uv_clocks.h>
#include <uv_graphics.h>
#include <uv_matrix.h>
#include <uv_memory.h>
#include <uv_sched.h>
#include <uv_texture.h>
#include <macros.h>

typedef struct {
    s32 unk0;
    f32 stickX;
    f32 stickY;
    s32 padC;
    s32 button;
    s32 prevButton;
} ControllerInfo;

// where is this ultralib piint.h header?
s32 osPiRawReadIo(u32 devAddr, u32* data);

void Thread_App(void* arg);
void Thread_Kernel(void* arg);
void Thread_Render(void* arg);
void app_entrypoint(s32);
void uvSetVideoMode(void);
void func_8022E558(void);

void func_80204930(void);
void func_8020F9F4(void);
void func_80217398(void);
void func_802242A0(void);
void func_80218700(void);
void func_80218BA0(void);
void func_80219FD0(void);
void func_8021F100(void);
void func_80230130(void);
void func_8021F368(void);

void uvVtx(s32, s32, s32, s32, s32, s32, s32, s32, s32);
void uvVtxEndPoly(void);

extern u8 app_ROM_START[];
extern u8 app_ROM_END[];
extern u8 app_VRAM[];
extern u8 app_VRAM_END[];
extern u8 app_TEXT_START[];
extern u8 app_TEXT_END[];
extern u8 app_DATA_START[];
extern u8 app_DATA_END[];
extern u8 app_RODATA_START[];
extern u8 app_RODATA_END[];
extern u8 app_BSS_START[];
extern u8 app_BSS_END[];

extern u8 kernel_TEXT_START[];
extern u8 kernel_TEXT_END[];
extern u8 kernel_DATA_START[];
extern u8 kernel_DATA_END[];
extern u8 kernel_RODATA_START[];
extern u8 kernel_RODATA_END[];
extern u8 kernel_BSS_START[];
extern u8 kernel_BSS_END[];
extern u8 kernel_VRAM[];
extern u8 kernel_VRAM_END[];

// ROM offsets of file system
extern u8 D_DF5B0[];
extern u8 D_618B70[];

extern OSSched gSchedInst;
extern OSThread gKernelThread;
extern OSThread gAppThread;
extern OSThread gRenderThread;

extern s32 gSchedStack[];
extern s32 gKernelThreadStack[];
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

extern s32 gEepromFound;
extern s32 D_802C5BB4;

extern OSContPad gControllerPads[];

s32 func_8022E2D4(s32 arg0);
void func_8022E2DC(char arg0);

s32 uvFileWrite(u8* dst, s32 offs, s32 nbytes) {
    if (gEepromFound == 0) {
        _uvDebugPrintf("uvFileWrite: no eeprom detected\n");
        return 0;
    }
    if (offs & 0x7) {
        _uvDebugPrintf("uvFileWrite: offs needs to be a multiple of 8\n");
        return 0;
    }
    if (nbytes & 0x7) {
        _uvDebugPrintf("uvFileWrite: nbytes needs to be a multiple of 8\n");
        return 0;
    }
    if ((offs + nbytes) > 0x208) {
        _uvDebugPrintf("uvFileWrite: offs [%d] + nbytes [%d]  > %d bytes\n", offs, nbytes, 0x208);
        return 0;
    }
    offs /= 8;
    if (osEepromLongWrite(&gSiContQ, offs, dst, nbytes) != 0) {
        _uvDebugPrintf("uvFileWrite: write error\n");
        return 0;
    }
    return nbytes;
}

s32 uvFileRead(u8* dst, s32 offs, s32 nbytes) {
    if (gEepromFound == 0) {
        _uvDebugPrintf("uvFileRead: no eeprom detected\n");
        return 0;
    }
    if (offs & 0x7) {
        _uvDebugPrintf("uvFileRead: offs needs to be a multiple of 8\n");
        return 0;
    }
    if (nbytes & 0x7) {
        _uvDebugPrintf("uvFileRead: nbytes needs to be a multiple of 8\n");
        return 0;
    }
    if (offs + nbytes > 0x208) {
        // devs used this `uvFileWrite` string, likely from copy-paste mistake
        _uvDebugPrintf("uvFileWrite: offs [%d] + nbytes [%d]  > %d bytes\n", offs, nbytes, 0x208);
        return 0;
    }
    offs /= 8;
    if (osEepromLongRead(&gSiContQ, offs, dst, nbytes) != 0) {
        _uvDebugPrintf("uvFileRead: read error\n");
        return 0;
    }
    return nbytes;
}

s32 uvSysInit(s32 arg0) {
    _uvDebugPrintf("\n\n");
    _uvDebugPrintf(" ------------------------------------------------------------------\n\n");
    _uvDebugPrintf("\t\t       UltraVision NU64  V1.5\n\n");
    _uvDebugPrintf("   Copyright (C)  1995  by  Paradigm Simulation Incorporated\n");
    _uvDebugPrintf("\t\t    All Rights Reserved Worldwide\n\n");
    _uvDebugPrintf(" ------------------------------------------------------------------\n\n");
    // clang-format off: easier to read on separate lines
    _uvDebugPrintf("kernel : [%7d ] bytes (%7d text, %7d data, %7d bss)\n",
                   kernel_VRAM_END - kernel_VRAM,
                   kernel_TEXT_END - kernel_TEXT_START,
                   kernel_RODATA_END - kernel_DATA_START,
                   kernel_BSS_END - kernel_BSS_START);
    _uvDebugPrintf("app    : [%7d ] bytes (%7d text, %7d data, %7d bss)\n",
                   app_VRAM_END - app_VRAM,
                   app_TEXT_END - app_TEXT_START,
                   app_RODATA_END - app_DATA_START,
                   app_BSS_END - app_BSS_START);
    _uvDebugPrintf("filesys: [%7d ] bytes (0x%08x - 0x%08x)\n",
                   (u32)D_618B70 - (u32)D_DF5B0,
                   D_DF5B0,
                   D_618B70);
    // clang-format on
    osViSetSpecialFeatures(OS_VI_DITHER_FILTER_ON);
    D_802C5BB4 = 0;
    func_80220960();
    func_80205FD0();
    func_802246A0();
    func_80204930();
    func_80218700();
    func_8020F9F4();
    func_80217398();
    func_802242A0();
    func_80218BA0();
    func_80219FD0();
    func_8021F100();
    func_80230130();
    func_80230954();
    uvMemInitBlocks();
    uvSysInitAudio();
    gEepromFound = osEepromProbe(&gSiContQ);
    if (gEepromFound == 0) {
        _uvDebugPrintf("uvSysInit : no EEPROM found -- read/writes will fail\n");
    }
    return arg0;
}

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

void bootproc(void* arg0) {
    u32 devAddr; // var_s1
    s32* var_v0;
    s32 pad;
    u8 sp3C[0x40];
    s32 i;

    for (var_v0 = (s32*)0x800DA800; var_v0 < (s32*)0x80100000; var_v0++) {
        *var_v0 = 0;
    }

    for (var_v0 = (s32*)0x80100000; var_v0 != (s32*)0x80125800; var_v0++) {
        *var_v0 = 0;
    }

    osInitialize();
    devAddr = 0xFFB000;
    for (i = 0; i < ARRAY_COUNT(sp3C); i += 4) {
        osPiRawReadIo(devAddr, (u32*)&sp3C[i]);
        devAddr += 4;
    }

    if (sp3C[0] == 0x2D) {
        if (sp3C[1] == 0x64) {
            D_802C32A4 = 1;
        } else if (sp3C[1] == 0x7A) {
            func_8022A47C();
        }
    }
    osCreateThread(&gKernelThread, 1, Thread_Kernel, arg0, gKernelThreadStack, 0xC);
    osStartThread(&gKernelThread);
}

void func_8022E558(void) {
    s16 temp_s3;
    s16 temp_s4;
    s16 spBA;
    u8 var_fp;
    u8 var_s6;
    u8 var_s7;
    Mtx4F_t sp74;

    uvGfxStatePush();
    uvGfxSetFlags(0x000FFF);
    uvGfxClearFlags(0xB00000);
    uvMat4Viewport(sp74, 0.0f, 320.0f, 0.0f, 240.0f);
    func_80222100(sp74);
    uvMat4SetIdentity(sp74);
    func_80221A78(sp74);
    func_8021F368();
    uvVtx(0xF, 0xF, 0, 0, 0, 0, 0x80, 0, 0xFF);
    uvVtx(0x50, 0xF, 0, 0, 0, 0, 0x80, 0, 0xFF);
    uvVtx(0x50, 0x8C, 0, 0, 0, 0, 0x80, 0, 0xFF);
    uvVtx(0xF, 0x8C, 0, 0, 0, 0, 0x80, 0, 0xFF);
    uvVtxEndPoly();

    for (spBA = 0; spBA < 32; spBA++) {
        if (D_802C331C & (1 << (0x1F - spBA))) {
            var_s6 = 0xFF;
            var_s7 = 0xFF;
            var_fp = 0xFF;
        } else {
            var_s6 = 0;
            var_s7 = 0;
            var_fp = 0;
        }
        func_8021F368();
        temp_s3 = ((spBA % 4) * 15) + 20;
        temp_s4 = (((0x1F - spBA) / 4) * 15) + 20;
        uvVtx(temp_s3, temp_s4, 0, 0, 0, var_fp, var_s7, var_s6, 0xFF);
        uvVtx(temp_s3 + 10, temp_s4, 0, 0, 0, var_fp, var_s7, var_s6, 0xFF);
        uvVtx(temp_s3 + 10, temp_s4 + 10, 0, 0, 0, var_fp, var_s7, var_s6, 0xFF);
        uvVtx(temp_s3, temp_s4 + 10, 0, 0, 0, var_fp, var_s7, var_s6, 0xFF);
        uvVtxEndPoly();
    }

    func_802236A8();
    uvGfxStatePop();
}

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

s32 uvReadController(ControllerInfo* contInfo, s32 contIdx) {
    void* sp34;
    OSContPad* contPad;
    s32 status;
    f32 correctedY;
    f32 correctedX;
    s32 prevButton;
    s8 stickX;
    s8 stickY;

    if (gNmiAsserted != 0) {
        return 0;
    }

    status = osContStartReadData(&gSiContQ);
    if (status & ~CONT_OVERRUN_ERROR) {
        contInfo->stickX = 0.0f;
        contInfo->stickY = 0.0f;
        contInfo->prevButton = contInfo->button;
        contInfo->button = 0;
        return 0;
    }

    osRecvMesg(&gSiContQ, &sp34, 1);
    osContGetReadData(&gControllerPads[0]);
    contPad = &gControllerPads[contIdx];
    stickX = contPad->stick_x;
    stickY = contPad->stick_y;

    if (stickX < 0) {
        if (stickX < -68) {
            stickX = -68;
        } else if (stickX > -7) {
            stickX = -7;
        }
        correctedX = (f32)(stickX + 7) / 61.0f;
    } else {
        if (stickX > 68) {
            stickX = 68;
        } else if (stickX < 7) {
            stickX = 7;
        }
        correctedX = (f32)(stickX - 7) / 61.0f;
    }

    if (stickY < 0) {
        if (stickY < -70) {
            stickY = -70;
        } else if (stickY > -7) {
            stickY = -7;
        }
        correctedY = (f32)(stickY + 7) / 63.0f;
    } else {
        if (stickY > 70) {
            stickY = 70;
        } else if (stickY < 7) {
            stickY = 7;
        }
        correctedY = (f32)(stickY - 7) / 63.0f;
    }
    contInfo->stickX = correctedX;
    contInfo->stickY = correctedY;
    contInfo->prevButton = (s32)contInfo->button;
    contInfo->button = (s32)contPad->button;
    return 1;
}

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
