#include <uv_clocks.h>
#include <uv_sched.h>

#define VIDEO_MSG 666
#define RSP_DONE_MSG 667
#define RDP_DONE_MSG 668
#define PRE_NMI_MSG 669

extern OSViMode osViModeTable[];
extern s32 gNmiAsserted;
extern u8 gSchedRspStatus;
extern u8 gSchedRdpStatus;
extern OSSched gSchedInst;
extern s32 gSchedRingIdx;
extern OSMesgQueue gSchedMsgQ;
extern OSMesgQueue D_802C3920;
extern s32 D_802B9C00[];
extern s32 D_802B9C18[];
extern double D_802B9C30[];
extern OSScTask* D_802B9C58;
extern OSScTask* D_802B9C60[];
extern u8 D_802B9C68;
extern u8 D_802B9C6B;
extern u8 D_802B9C6C;
extern u8 D_802B9C6D;
extern u8 D_802B9C6E;
extern u8 D_802B9C6F;
extern u8 D_802B9C70;
extern s32 D_802B9C74;
extern s32 D_802B9C7C;
extern s32 D_802B9C84;
extern s32 D_802B9C88;

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/sched/func_8022B0A0.s")

void _uvScDoneGfx(void) {
    OSScTask* scTask = D_802B9C60[D_802B9C6E];

    if (gNmiAsserted == 0) {
        if (scTask == NULL) {
            _uvDebugPrintf("_uvScDoneGfx -- no gfx task\n");
            _uvScLogIntoRing();
            return;
        }
        if (D_802B9C6C == 0) {
            if ((gSchedRspStatus == 'g') || (gSchedRdpStatus != 0)) {
                _uvDebugPrintf("_uvScDoneGfx:  rsp [%c]    rdp [%c]\n", gSchedRspStatus, gSchedRdpStatus);
            } else {
                func_8022C3C0(0, 0x32);
                osSendMesg(scTask->msgQ, scTask->msg, 1);
                D_802B9C68 = 1;
                osViSwapBuffer(scTask->framebuffer);
                D_802B9C60[D_802B9C6E] = NULL;
            }
        }
    }
}

void _uvScDoneAud(void) {
    if (D_802B9C58 == NULL) {
        _uvDebugPrintf("_uvScDoneAud: no audio task\n");
        return;
    }
    func_8022C3C0(1, 0x2C);
    if (gNmiAsserted == 0) {
        osSendMesg(D_802B9C58->msgQ, D_802B9C58->msg, 1);
    }
    D_802B9C58 = NULL;
    if (D_802B9C60[D_802B9C6E] != 0) {
        _uvScRunGfx();
    }
}

void _uvScRunAud(void) {
    if (gNmiAsserted == 0) {
        if (D_802B9C58 == NULL) {
            _uvDebugPrintf("_uvScRunAud -- no audio task\n");
            return;
        }
        gSchedRspStatus = 'a';
        func_8022C3C0(1, 0x29);
        osWritebackDCacheAll();
        osSpTaskLoad(&D_802B9C58->list);
        osSpTaskStartGo(&D_802B9C58->list);
    }
}

void _uvScRunGfx(void) {
    OSScTask* scTask;

    scTask = D_802B9C60[D_802B9C6E];
    if ((gNmiAsserted == 0) || (D_802B9C6C != 0)) {
        if (scTask == NULL) {
            _uvDebugPrintf("_uvScRunGfx -- no gfx task\n");
            return;
        }
        if ((gSchedRspStatus != 'g') && ((D_802B9C6C != 0) || (gSchedRdpStatus != 'g'))) {
            if (osViGetCurrentFramebuffer() == osViGetNextFramebuffer()) {
                gSchedRspStatus = 'g';
                if (D_802B9C6C == 0) {
                    D_802B9C74 += 1;
                    gSchedRdpStatus = 'g';
                }
                func_8022C3C0(1, 0x2A);
                D_802B9C6C = D_802B9C6B = 0;
                osWritebackDCacheAll();
                osSpTaskLoad(&scTask->list);
                osSpTaskStartGo(&scTask->list);
            }
        }
    }
}

void _uvScDlistRecover(void) {
    _uvDebugPrintf("Recovered from a bad display list\n");

    IO_WRITE(SP_STATUS_REG, 0x2902);
    if (gSchedRspStatus != 0) {
        osSendMesg(&gSchedMsgQ, (OSMesg)RSP_DONE_MSG, 0);
    }
    if (gSchedRdpStatus != 0) {
        osSendMesg(&gSchedMsgQ, (OSMesg)RDP_DONE_MSG, 0);
    }
}

void _uvScCreateScheduler(OSSched* sc, void* stack, s32 priority, u8 mode, u8 numFields) {
    ((OSScTask*)D_802B9C60)->state = 0;
    ((OSScTask*)D_802B9C60)->next = 0;
    D_802B9C58 = 0;
    D_802B9C68 = 0;
    gSchedRspStatus = 0;
    gSchedRdpStatus = 0;
    D_802B9C6B = 0;
    D_802B9C6C = 0;
    D_802B9C6D = 0;
    D_802B9C6E = 0;
    D_802B9C6F = 0;
    D_802B9C70 = 0;
    D_802B9C74 = 0;
    gSchedRingIdx = 0;
    D_802B9C7C = 0;
    gNmiAsserted = 0;
    D_802B9C84 = 1;
    D_802B9C88 = 1;

    if ((sc && sc) != 0) { } // fakematch

    sc->clientList = 0;
    sc->curRSPTask = 0;
    sc->curRDPTask = 0;
    sc->frameCount = 0;
    sc->audioListHead = 0;
    sc->gfxListHead = 0;
    sc->audioListTail = (OSScTask*)&sc->audioListHead;
    sc->gfxListTail = (OSScTask*)&sc->gfxListHead;
    sc->retraceMsg.type = OS_SC_RETRACE_MSG;
    sc->prenmiMsg.type = OS_SC_PRE_NMI_MSG;

    osCreateMesgQueue(&sc->interruptQ, sc->intBuf, OS_SC_MAX_MESGS);
    osCreateMesgQueue(&sc->cmdQ, sc->cmdMsgBuf, OS_SC_MAX_MESGS);
    osCreateViManager(OS_PRIORITY_VIMGR);
    osViSetMode(&osViModeTable[mode]);
    osViSwapBuffer((void*)0x80100000);
    osViBlack(TRUE);
    osSetEventMesg(OS_EVENT_SP, &sc->interruptQ, (OSMesg)RSP_DONE_MSG);
    osSetEventMesg(OS_EVENT_DP, &sc->interruptQ, (OSMesg)RDP_DONE_MSG);
    osSetEventMesg(OS_EVENT_PRENMI, &sc->interruptQ, (OSMesg)PRE_NMI_MSG);
    osViSetEvent(&sc->interruptQ, (OSMesg)VIDEO_MSG, (u32)numFields);

    osCreateThread(&sc->thread, 4, _uvScMain, (void*)sc, stack, priority);
    osStartThread(&sc->thread);

    func_80206150(6);
    func_8022C34C();
}

void _uvScAddClient(OSSched* sc, OSScClient* client, OSMesgQueue* mq) {
    client->msgQ = mq;
    client->next = sc->clientList;
    sc->clientList = (OSScClient*)client;
}

OSMesgQueue* _uvScGetCmdQ(OSSched* s) {
    return &s->cmdQ;
}

void _uvScMain(void* arg0) {
    OSMesg msg;
    msg = NULL;

    while (1) {
        osRecvMesg(&gSchedMsgQ, &msg, 1);

        switch ((int)msg) {
        case VIDEO_MSG:
            _uvScHandleRetrace();
            break;
        case RSP_DONE_MSG:
            _uvScHandleRSP();
            break;
        case RDP_DONE_MSG:
            _uvScHandleRDP();
            break;
        case PRE_NMI_MSG:
            _uvScHandleNMI();
            break;
        default:
            _uvDebugPrintf("unknown sched interrupt mesg: 0x%x\n", msg);
            break;
        }
    }
}

void _uvScHandleRetrace(void) {
    OSScTask* msg;
    u32 taskType;
    OSScClient* var_s0;

    msg = NULL;
    func_80205FFC();
    if (gNmiAsserted == 0) {
        D_802B9C84 = 1;
        if (gSchedRspStatus) {
            D_802B9C70 += 1;
        } else {
            D_802B9C70 = 0;
        }

        if (gSchedRdpStatus) {
            D_802B9C6F += 1;
        } else {
            D_802B9C6F = 0;
        }
        if (D_802B9C70 >= 51) {
            _uvDebugPrintf("RSP timeout on %c, sending wakeup...\n", gSchedRspStatus);
            _uvScDlistRecover();
            return;
        }
        if ((D_802B9C70 + 50) < D_802B9C6F) {
            D_802B9C6F = 0;
            _uvDebugPrintf("RDP timeout on %c [%d], sending wakeup...\n", gSchedRdpStatus, gSchedRdpStatus);
            _uvScLogIntoRing();
            osSendMesg(&gSchedMsgQ, (OSMesg)0x29C, 0);
            return;
        }
        if (gSchedRspStatus == 'a') {
            _uvDebugPrintf("_uvScHandleRetrace: audio still busy\n");
            return;
        }
        if (D_802B9C68 != 0) {
            D_802B9C68 = 0;
            func_8022C34C();
            D_802B9C6E ^= 1;
        }

        while (osRecvMesg(&D_802C3920, (void*)&msg, 0) != -1) {
            if (msg == NULL) {
                _uvDebugPrintf("received message with task of 0\n");
                break;
            }
            taskType = msg->list.t.type;
            if (taskType == M_GFXTASK) {
                D_802B9C60[D_802B9C6D] = msg;
                D_802B9C6D ^= 1;
            } else if (taskType == M_AUDTASK) {
                D_802B9C58 = msg;
            } else {
                _uvDebugPrintf("_uvScHandleRetrace: unkown task type 0x%x\n", msg);
            }
        }

        if (D_802B9C58 != NULL) {
            if (gSchedRspStatus == 'g') {
                if (D_802B9C6C != 0) {
                    _uvDebugPrintf("_uvScHandleRetrace:  2nd yield\n");
                }
                if (D_802B9C6B != 0) {
                    _uvDebugPrintf("_uvScHandleRetrace: gfx task didn't yield\n");
                    _uvScDlistRecover();
                    return;
                }
                D_802B9C6B = 1;
                func_8022C3C0(1, 0x31);
                osSpTaskYield();
            } else {
                _uvScRunAud();
            }
        } else if (D_802B9C60[D_802B9C6E] != NULL) {
            _uvScRunGfx();
        }
        var_s0 = gSchedInst.clientList;
        while (var_s0 != NULL) {
            osSendMesg(var_s0->msgQ, &gSchedInst, 0);
            var_s0 = var_s0->next;
        }
    }
}

void _uvScHandleRSP(void) {
    if (gSchedRspStatus == 0) {
        _uvDebugPrintf("_uvScHandleRSP -- state error, should have been busy\n");
        return;
    }

    D_802B9C70 = 0;
    if (gSchedRspStatus == 'a') {
        gSchedRspStatus = 0;
        _uvScDoneAud();
        return;
    }

    gSchedRspStatus = 0;
    if (D_802B9C6B != 0) {
        if (osSpTaskYielded(&D_802B9C60[D_802B9C6E]->list) != 0) {
            D_802B9C6C = 1;
            func_8022C3C0(1, 0x2D);
            if (gNmiAsserted != 0) {
                D_802B9C58 = 0;
                D_802B9C6B = 0;
                _uvScRunGfx();
                return;
            }

        } else {
            func_8022C3C0(1, 0x2B);
        }

        D_802B9C6B = 0;
        if (D_802B9C58 != 0) {
            _uvScRunAud();
        }
    } else {
        func_8022C3C0(1, 0x2B);
    }

    if ((gSchedRspStatus != 'g') && (gSchedRdpStatus == 0)) {
        _uvScDoneGfx();
    }
}

void _uvScHandleRDP(void) {
    gSchedRdpStatus = 0;
    D_802B9C6F = 0;
    func_8022C3C0(1, 0x30);
    if ((gSchedRspStatus != 'g') && (D_802B9C6C == 0)) {
        _uvScDoneGfx();
    }
}

void _uvScHandleNMI(void) {
    gNmiAsserted = 1;
    osViBlack(1);
}

void func_8022BEB8(s32 arg0) {
    D_802B9C88 = arg0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/sched/_uvScLogCpuEvent.s")

void _uvScLogIntoRing(void) {
    s32 ring;
    s32 iter;

    _uvDebugPrintf("logging into ring %d\n", gSchedRingIdx);
    for (iter = 0; iter < 5; iter++) {
        ring = (gSchedRingIdx + iter + 1) % 5;
        _uvDebugPrintf("============== ring %d   start time: %f ==============\n", ring, D_802B9C30[ring]);
        _uvScLogCpuEvent(ring);
    };
    D_802B9C84 = 0;
}

void func_8022C34C(void) {
    gSchedRingIdx = gSchedRingIdx + 1;
    if (gSchedRingIdx >= 5) {
        gSchedRingIdx = 0;
    }
    D_802B9C30[gSchedRingIdx] = uvClkGetSec(6);
    D_802B9C18[gSchedRingIdx] = 0;
    D_802B9C00[gSchedRingIdx] = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/sched/func_8022C3C0.s")
