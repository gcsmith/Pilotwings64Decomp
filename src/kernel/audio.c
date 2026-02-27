#include "common.h"
#include <uv_audio.h>
#include <uv_event.h>
#include <uv_filesystem.h>
#include <uv_memory.h>
#include <uv_sched.h>
#include <libc/stdint.h>
#include <libc/stddef.h>
#include "segment_symbols.h"

ALCSPlayer D_8025C5B0;
ALSndPlayer D_8025C630;
AMAudioMgr D_8025C688;
u8 gAudioThreadStack[0x4000];
AMDMAState D_80260910;
AMDMABuffer D_80260920[48];
u32 D_80260CE0;
s32 D_80260CE4;
s32 D_80260CE8;
s32 D_80260CEC;
uvOSIoMesg D_80260CF0[48];
OSMesgQueue D_802610B0;
OSMesg D_802610C8[48];
OSMesgQueue D_80261188;
OSMesg D_802611A0[1];
ALHeap D_802611A8;
ALSynConfig D_802611B8;
ALSeqpConfig D_802611E0;
ALSndpConfig D_80261200;
ALBank* D_8026120C;
ALBank* D_80261210;
ALInstrument* D_80261214;
ALSndId* gSndVoiceTable;
ALSeqFile* D_8026121C;
u8* D_80261220;

static s32 D_80248C80 = 0;
static s32 D_80248C84 = 0;
static s32 D_80248C88 = 0;
static u8* D_80248C8C = 0x80000400;
ALCSPlayer* gSeqPlayer = &D_8025C5B0;
ALSndPlayer* gSndPlayer = &D_8025C630;

void uvSysInitAudio(void) {
    s32 seqFileSize;
    s32 i;
    s32 var_s0;

    var_s0 = 0;
    _uvDebugPrintf("uvSysInit : initializing audio system ... ");
    uvEmitterInitTable();
    func_802000A0();
    func_80202DA0();
    uvMemSet(D_80248C8C, 0, 0x413DC);
    alHeapInit(&D_802611A8, D_80248C8C, 0x413DC);
    D_802611B8.maxVVoices = 32;
    D_802611B8.maxPVoices = 32;
    D_802611B8.maxUpdates = 256;
    D_802611B8.dmaproc = NULL;
    D_802611B8.fxType = AL_FX_CUSTOM;
    D_802611B8.outputRate = 0;
    D_802611B8.heap = &D_802611A8;
    if (D_802611B8.fxType == AL_FX_CUSTOM) {
        s32 customFxParams[] = {
            8, /* section count */
            5200, /* total allocated memory (ms) */
            /*      input(ms)  output(ms)  fbcoef   ffcoef    gain    chorus rate  chorus delay low-pass filter */
            /* 1 */ 0,         1600,       9830,    -9830,    3000,   0,           0,           0,
            /* 2 */ 64,        3600,       9830,    -9830,    2000,   0,           0,           0x5000,
            /* 3 */ 656,       2048,       16384,   -16384,   0x23D6, 0,           0,           0,
            /* 4 */ 720,       1648,       8192,    -8192,    0,      0,           0,           0,
            /* 5 */ 2592,      4512,       16384,   -16384,   0x23D6, 0,           0,           0x6000,
            /* 6 */ 2656,      3808,       8192,    -8192,    0,      0,           0,           0,
            /* 7 */ 3808,      4288,       8192,    -8192,    0,      0,           0,           0,
            /* 8 */ 0,         4784,       18000,   0,        0,      0,           0,           0x7000,
        };
        D_802611B8.params = customFxParams;
    }
    {
        ALSeqFile sp40;
        func_80203B08(&D_802611B8, 110);
        D_802611E0.maxVoices = 16;
        D_802611E0.maxEvents = 256;
        D_802611E0.maxChannels = 16;
        D_802611E0.heap = &D_802611A8;
        D_80261200.maxSounds = 16;
        D_80261200.maxEvents = 256;
        D_80261200.heap = &D_802611A8;
        alSndpNew(gSndPlayer, &D_80261200);
        alCSPNew(gSeqPlayer, &D_802611E0);
        osSendMesg(&D_80261188, NULL, OS_MESG_BLOCK);
        _uvMediaCopy(&sp40, SEGMENT_ROM_START(audio_seq), 0x8);
        seqFileSize = (sp40.seqCount * sizeof(ALSeqData)) + offsetof(ALSeqFile, seqArray);
        D_8026121C = alHeapAlloc(&D_802611A8, 1, seqFileSize);
        _uvMediaCopy(D_8026121C, SEGMENT_ROM_START(audio_seq), seqFileSize);
        alSeqFileNew(D_8026121C, SEGMENT_ROM_START(audio_seq));

        for (i = 0; i < D_8026121C->seqCount; i++) {
            if (D_8026121C->seqArray[i].len >= var_s0) {
                var_s0 = D_8026121C->seqArray[i].len;
            }
        }
        if (var_s0 & 1) {
            var_s0++;
        }
        D_80261220 = alHeapAlloc(&D_802611A8, 1, var_s0);
        _uvDebugPrintf("done\n");
    }
}

void func_80203B08(ALSynConfig* c, OSPri priority) {
    ALLink* var_s0;
    ALLink* var_s1;
    f32 frameSize;
    s32 temp_ft5;
    s32 temp_v0;
    s32 i;
    s32 var_v1;
    void** temp_t1;
    void** temp_v0_2;
    void** temp_v1;

    c->dmaproc = func_802042E4;
    c->outputRate = osAiSetFrequency(OUTPUT_RATE);
    frameSize = ((f32)c->outputRate * 1) / 60.0f;
    D_80260CE8 = (s32)frameSize;
    if (D_80260CE8 < frameSize) {
        D_80260CE8++;
    }
    if (D_80260CE8 & 0xF) {
        D_80260CE8 = (D_80260CE8 & ~0xF) + 0x10;
    }
    D_80260CE4 = D_80260CE8 - 16;
    D_80260CEC = D_80260CE8 + EXTRA_SAMPLES + 16;
    alInit(&D_8025C688.g, c);
    D_80260920[0].node.prev = NULL;
    D_80260920[0].node.next = NULL;

    for (i = 0; i < ARRAY_COUNT(D_80260920) - 1; i++) {
        alLink(&D_80260920[i + 1].node, &D_80260920[i].node);
        D_80260920[i].ptr = alHeapAlloc(c->heap, 1, DMA_BUF_SIZE);
    }
    D_80260920[i].ptr = alHeapAlloc(c->heap, 1, DMA_BUF_SIZE);

    for (i = 0; i < 2; i++) {
        D_8025C688.acmdList[i] = alHeapAlloc(c->heap, 1, AUDIO_BUF_SIZE);
    }

    for (i = 0; i < 3; i++) {
        D_8025C688.audioInfo[i] = alHeapAlloc(c->heap, 1, sizeof(AudioInfo));
        D_8025C688.audioInfo[i]->msg.done.type = OS_SC_DONE_MSG;
        D_8025C688.audioInfo[i]->msg.done.info = D_8025C688.audioInfo[i];
        D_8025C688.audioInfo[i]->data = alHeapAlloc(c->heap, 1, D_80260CEC * 4);
    }
    osCreateMesgQueue(&D_8025C688.audioReplyMsgQ, D_8025C688.audioReplyMsgBuf, ARRAY_COUNT(D_8025C688.audioReplyMsgBuf));
    osCreateMesgQueue(&D_8025C688.audioFrameMsgQ, D_8025C688.audioFrameMsgBuf, ARRAY_COUNT(D_8025C688.audioFrameMsgBuf));
    osCreateMesgQueue(&D_802610B0, D_802610C8, ARRAY_COUNT(D_802610C8));
    osCreateMesgQueue(&D_80261188, D_802611A0, ARRAY_COUNT(D_802611A0));
    osCreateThread(&D_8025C688.thread, 3, Thread_Audio, NULL, gAudioThreadStack + ARRAY_COUNT(gAudioThreadStack), priority);
    osStartThread(&D_8025C688.thread);
}

void Thread_Audio(void* entry) {
    s16 temp_v0;
    s32 done = FALSE;
    AudioMsg* msg = NULL;
    s32 var_s0 = 0;
    OSScClient sp48;

    osRecvMesg(&D_80261188, (OSMesg*)&msg, OS_MESG_BLOCK);
    _uvScAddClient(&gSchedInst, &sp48, &D_8025C688.audioFrameMsgQ);
    while (!done) {
        osRecvMesg(&D_8025C688.audioFrameMsgQ, (OSMesg*)&msg, OS_MESG_BLOCK);
        func_8022C3C0(0, 0x29);
        switch (msg->gen.type) {
        case OS_SC_PRE_NMI_MSG:
            break;
        case OS_SC_RETRACE_MSG:
            if (func_80203F4C(D_8025C688.audioInfo[D_80260CE0 % 3], var_s0) != 0) {
                osRecvMesg(&D_8025C688.audioReplyMsgQ, (OSMesg*)&msg, OS_MESG_BLOCK);
                uvGetSamples(msg->done.info);
                var_s0 = msg->done.info;
            }
            break;
        case AUDIO_QUIT_MSG:
            done = TRUE;
            break;
        }
    }
    alClose(&D_8025C688.g);
}

s32 func_80203F4C(AudioInfo* info, AudioInfo* previousTask) {
    s16* audioPtr;
    Acmd* acmdPtr;
    s32 cmdLen;
    OSScTask* task;
    s32 samplesLeft;

    func_8020431C();
    audioPtr = osVirtualToPhysical(info->data);
    if (previousTask != NULL) {
        osAiSetNextBuffer(previousTask->data, previousTask->frameSamples << 2);
    }
    samplesLeft = osAiGetLength() >> 2;
    info->frameSamples = ((D_80260CE8 - samplesLeft + EXTRA_SAMPLES) + 16) & ~0xF;
    if (info->frameSamples < D_80260CE4) {
        info->frameSamples = D_80260CE4;
    }
    acmdPtr = alAudioFrame(D_8025C688.acmdList[D_80248C84], &cmdLen, audioPtr, info->frameSamples);
    if (cmdLen == 0) {
        return 0;
    }
    info->task.next = NULL;
    info->task.msgQ = &D_8025C688.audioReplyMsgQ;
    info->task.msg = &info->msg;
    info->task.flags = OS_SC_NEEDS_RDP;

    task = &info->task;
    task->list.t.data_ptr = (u64*)D_8025C688.acmdList[D_80248C84];
    task->list.t.data_size = (acmdPtr - D_8025C688.acmdList[D_80248C84]) * sizeof(Acmd);
    task->list.t.type = M_AUDTASK;
    task->list.t.ucode_boot = (u64*)rspbootTextStart;
    task->list.t.ucode_boot_size = (u64*)((uintptr_t)rspbootTextEnd - (uintptr_t)rspbootTextStart);
    task->list.t.flags = 0;
    task->list.t.ucode = (u64*)aspMainTextStart;
    task->list.t.ucode_data = (u64*)aspMainDataStart;
    task->list.t.ucode_data_size = SP_UCODE_DATA_SIZE;
    task->list.t.yield_data_ptr = NULL;
    task->list.t.yield_data_size = 0;
    task->list.t.dram_stack_size = 0;
    task->list.t.dram_stack = NULL;
    func_8022C3C0(0, 0x2C);
    osSendMesg(_uvScGetCmdQ(&gSchedInst), &info->task, OS_MESG_BLOCK);
    D_80248C84 ^= 1;
    return 1;
}

void uvGetSamples(AudioInfo* task) {
    static s32 D_80248DA0 = TRUE;
    s32 samplesLeft = osAiGetLength() >> 2;

    if ((samplesLeft == 0) && !D_80248DA0) {
        _uvDebugPrintf("audio: ai out of samples\n");
        D_80248DA0 = FALSE;
    }
}

s32 func_80204168(s32 addr, s32 len, UNUSED void* state) {
    void* foundBuffer;
    AMDMABuffer* dmaPtr;
    AMDMABuffer* lastDmaPtr;
    s32 delta;
    s32 addrEnd;
    s32 buffEnd;

    dmaPtr = D_80260910.firstUsed;
    lastDmaPtr = NULL;

    addrEnd = addr + len;

    while (dmaPtr) {
        buffEnd = dmaPtr->startAddr + DMA_BUF_SIZE;
        if ((u32)addr < dmaPtr->startAddr) {
            break;
        }

        if (buffEnd >= addrEnd) {
            dmaPtr->lastFrame = D_80260CE0;
            foundBuffer = dmaPtr->ptr + addr - dmaPtr->startAddr;
            return osVirtualToPhysical(foundBuffer);
        }
        lastDmaPtr = dmaPtr;
        dmaPtr = (AMDMABuffer*)dmaPtr->node.next;
    }

    dmaPtr = D_80260910.firstFree;

    D_80260910.firstFree = (AMDMABuffer*)dmaPtr->node.next;
    alUnlink(&dmaPtr->node);
    if (lastDmaPtr != NULL) {
        alLink(&dmaPtr->node, &lastDmaPtr->node);
    } else if (D_80260910.firstUsed != NULL) {
        lastDmaPtr = D_80260910.firstUsed;
        D_80260910.firstUsed = dmaPtr;
        dmaPtr->node.next = &lastDmaPtr->node;
        dmaPtr->node.prev = NULL;
        lastDmaPtr->node.prev = &dmaPtr->node;
    } else {
        D_80260910.firstUsed = dmaPtr;
        dmaPtr->node.next = NULL;
        dmaPtr->node.prev = NULL;
    }

    foundBuffer = dmaPtr->ptr;
    delta = addr & 1;
    addr -= delta;
    dmaPtr->startAddr = addr;
    dmaPtr->lastFrame = D_80260CE0;
    osPiStartDma((OSIoMesg*)&D_80260CF0[D_80248C80++], OS_MESG_PRI_HIGH, OS_READ, addr, foundBuffer, DMA_BUF_SIZE, &D_802610B0);
    return osVirtualToPhysical(foundBuffer) + delta;
}

ALDMAproc func_802042E4(AMDMAState** state) {
    if (D_80260910.initialized == 0) {
        D_80260910.firstUsed = NULL;
        D_80260910.firstFree = D_80260920;
        D_80260910.initialized = 1;
    }
    *state = &D_80260910;
    return func_80204168;
}

void func_8020431C(void) {
    s32 i;
    OSIoMesg* iomsg = NULL;
    AMDMABuffer* dmaPtr;
    AMDMABuffer* nextPtr;

    for (i = 0; i < D_80248C80; i++) {
        osRecvMesg(&D_802610B0, (OSMesg*)&iomsg, OS_MESG_NOBLOCK);
    }

    dmaPtr = D_80260910.firstUsed;
    while (dmaPtr) {
        nextPtr = (AMDMABuffer*)dmaPtr->node.next;

        if (dmaPtr->lastFrame + FRAME_LAG < D_80260CE0) {
            if (D_80260910.firstUsed == dmaPtr) {
                D_80260910.firstUsed = (AMDMABuffer*)dmaPtr->node.next;
            }
            alUnlink(&dmaPtr->node);
            if (D_80260910.firstFree) {
                alLink(&dmaPtr->node, &D_80260910.firstFree->node);
            } else {
                D_80260910.firstFree = dmaPtr;
                dmaPtr->node.next = 0;
                dmaPtr->node.prev = 0;
            }
        }
        dmaPtr = nextPtr;
    }

    D_80248C80 = 0;
    D_80260CE0++;
}

void func_80204438(s32 arg0, void** arg1, u32* arg2, void** arg3) {
    s32 temp_v0;
    u32 var_v0;
    u32 sp44;
    void* sp40;

    temp_v0 = uvFileReadHeader(arg0);
    var_v0 = uvFileReadBlock(temp_v0, &sp44, &sp40, 0);
    while (var_v0 != 0) {
        switch (var_v0) {
        case '.TBL':
            *arg3 = sp40;
            break;
        case '.CTL':
            *arg1 = sp40;
            *arg2 = sp44;
            break;
        default:
            break;
        }
        var_v0 = uvFileReadBlock(temp_v0, &sp44, &sp40, 0);
    }
    uvFile_80223F30(temp_v0);
}

void func_80204518(s32 arg0) {
    void* sp5C;
    void* sp58;
    u32 sp54;
    ALBankFile* temp_v0;
    ALSound* temp_s3;
    s32 temp_s1;
    s32 i;

    func_80204438(gUVBlockOffsets.UVSX[arg0], &sp5C, &sp54, &sp58);
    temp_v0 = alHeapDBAlloc(NULL, 0, &D_802611A8, 1, SEGMENT_ROM_SIZE(audio_ctl));
    _uvMediaCopy(temp_v0, SEGMENT_ROM_START(audio_ctl), SEGMENT_ROM_SIZE(audio_ctl));
    alBnkfNew(temp_v0, SEGMENT_ROM_START(audio_tbl));
    D_80261210 = temp_v0->bankArray[0];
    alSeqpSetBank((ALSeqPlayer*)gSeqPlayer, D_80261210);
    temp_v0 = alHeapDBAlloc(NULL, 0, &D_802611A8, 1, sp54);
    _uvMediaCopy(temp_v0, sp5C, sp54);
    alBnkfNew(temp_v0, sp58);
    D_8026120C = temp_v0->bankArray[0];
    D_80261214 = D_8026120C->instArray[0];
    gSndVoiceTable = alHeapDBAlloc(NULL, 0, &D_802611A8, 1, gSndPlayer->frameTime * 2);

    temp_s3 = D_80261214->soundArray[0];
    for (i = 0; i < gSndPlayer->frameTime; i++) {
        gSndVoiceTable[i] = alSndpAllocate(gSndPlayer, temp_s3);
    }
}
