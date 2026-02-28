#include "common.h"
#include <uv_audio.h>
#include <uv_event.h>
#include <uv_filesystem.h>
#include <uv_memory.h>
#include <uv_sched.h>
#include <libc/stdint.h>
#include <libc/stddef.h>
#include <segment_symbols.h>
#include "code_1050.h"

ALCSPlayer gALCSPlayer;
ALSndPlayer gALSndPlayer;
AMAudioMgr __am;
u8 gAudioThreadStack[0x4000];
AMDMAState dmaState;
AMDMABuffer dmaBuffs[NUM_DMA_BUFFERS];
u32 audFrameCt;
s32 minFrameSize;
s32 frameSize;
s32 maxFrameSize;
uvOSIoMesg D_80260CF0[NUM_DMA_MESSAGES];
OSMesgQueue audDMAMessageQ;
OSMesg audDMAMessageBuf[NUM_DMA_MESSAGES];
OSMesgQueue D_80261188;
OSMesg D_802611A0[1];
ALHeap gAudioHeap;
ALSynConfig gALSynConfig;
ALSeqpConfig gALSeqpConfig;
ALSndpConfig gALSndpConfig;
ALBank* gAudioSXBank;
ALBank* gWaveTableBank;
ALInstrument* gAudioSXInst;
ALSndId* gSndVoiceTable;
ALSeqFile* gSeqFile;
u8* gSequenceData;

static s32 nextDMA = 0;
static s32 curAcmdList = 0;
static s32 D_80248C88 = 0;
static u8* gAudioHeapStart = 0x80000400;
ALSeqPlayer* gSeqPlayer = (ALSeqPlayer*)&gALCSPlayer;
ALSndPlayer* gSndPlayer = &gALSndPlayer;

static void __amMain(UNUSED void* arg);
static s32 __amDMA(s32 addr, s32 len, void* state);
static ALDMAproc __amDmaNew(AMDMAState** state);
static u32 __amHandleFrameMsg(AudioInfo* info, AudioInfo* lastInfo);
static void __amHandleDoneMsg(AudioInfo* info);
static void __clearAudioDMA(void);

void uvSysInitAudio(void) {
    s32 seqFileSize;
    s32 i;
    s32 maxSeqLen;

    maxSeqLen = 0;
    _uvDebugPrintf("uvSysInit : initializing audio system ... ");
    uvEmitterInitTable();
    func_802000A0();
    func_80202DA0();
    uvMemSet(gAudioHeapStart, 0, 0x413DC);
    alHeapInit(&gAudioHeap, gAudioHeapStart, 0x413DC);
    gALSynConfig.maxVVoices = 32;
    gALSynConfig.maxPVoices = 32;
    gALSynConfig.maxUpdates = 256;
    gALSynConfig.dmaproc = NULL;
    gALSynConfig.fxType = AL_FX_CUSTOM;
    gALSynConfig.outputRate = 0;
    gALSynConfig.heap = &gAudioHeap;
    if (gALSynConfig.fxType == AL_FX_CUSTOM) {
        // clang-format off
        s32 customFxParams[] = {
            8, /* section count */
            5200, /* total allocated memory (ms) */
            /*      input(ms)  output(ms)  fbcoef   ffcoef    gain    chorus rate  chorus delay low-pass filter */
            /* 1 */ 0,         1600,       9830,    -9830,    0xBB8,  0,           0,           0,
            /* 2 */ 64,        3600,       9830,    -9830,    0x7D0,  0,           0,           0x5000,
            /* 3 */ 656,       2048,       16384,   -16384,   0x23D6, 0,           0,           0,
            /* 4 */ 720,       1648,       8192,    -8192,    0,      0,           0,           0,
            /* 5 */ 2592,      4512,       16384,   -16384,   0x23D6, 0,           0,           0x6000,
            /* 6 */ 2656,      3808,       8192,    -8192,    0,      0,           0,           0,
            /* 7 */ 3808,      4288,       8192,    -8192,    0,      0,           0,           0,
            /* 8 */ 0,         4784,       18000,   0,        0,      0,           0,           0x7000,
        };
        // clang-format on
        gALSynConfig.params = customFxParams;
    }
    {
        ALSeqFile seqFile;
        amCreateAudioMgr(&gALSynConfig, 110);
        gALSeqpConfig.maxVoices = 16;
        gALSeqpConfig.maxEvents = 256;
        gALSeqpConfig.maxChannels = 16;
        gALSeqpConfig.heap = &gAudioHeap;
        gALSndpConfig.maxSounds = 16;
        gALSndpConfig.maxEvents = 256;
        gALSndpConfig.heap = &gAudioHeap;
        alSndpNew(gSndPlayer, &gALSndpConfig);
        alCSPNew((ALCSPlayer*)gSeqPlayer, &gALSeqpConfig);
        osSendMesg(&D_80261188, NULL, OS_MESG_BLOCK);
        _uvMediaCopy(&seqFile, SEGMENT_ROM_START(audio_seq), 0x8);
        seqFileSize = (seqFile.seqCount * sizeof(ALSeqData)) + offsetof(ALSeqFile, seqArray);
        gSeqFile = alHeapAlloc(&gAudioHeap, 1, seqFileSize);
        _uvMediaCopy(gSeqFile, SEGMENT_ROM_START(audio_seq), seqFileSize);
        alSeqFileNew(gSeqFile, SEGMENT_ROM_START(audio_seq));

        for (i = 0; i < gSeqFile->seqCount; i++) {
            if (gSeqFile->seqArray[i].len >= maxSeqLen) {
                maxSeqLen = gSeqFile->seqArray[i].len;
            }
        }
        if (maxSeqLen & 1) {
            maxSeqLen++;
        }
        gSequenceData = alHeapAlloc(&gAudioHeap, 1, maxSeqLen);
        _uvDebugPrintf("done\n");
    }
}

void amCreateAudioMgr(ALSynConfig* c, OSPri priority) {
    f32 fSize;
    s32 i;

    c->dmaproc = __amDmaNew;
    c->outputRate = osAiSetFrequency(OUTPUT_RATE);
    fSize = ((f32)c->outputRate * 1) / 60.0f;
    frameSize = (s32)fSize;
    if (frameSize < fSize) {
        frameSize++;
    }
    if (frameSize & 0xF) {
        frameSize = (frameSize & ~0xF) + 0x10;
    }
    minFrameSize = frameSize - 16;
    maxFrameSize = frameSize + EXTRA_SAMPLES + 16;
    alInit(&__am.g, c);
    dmaBuffs[0].node.prev = NULL;
    dmaBuffs[0].node.next = NULL;

    for (i = 0; i < ARRAY_COUNT(dmaBuffs) - 1; i++) {
        alLink(&dmaBuffs[i + 1].node, &dmaBuffs[i].node);
        dmaBuffs[i].ptr = alHeapAlloc(c->heap, 1, DMA_BUF_SIZE);
    }
    dmaBuffs[i].ptr = alHeapAlloc(c->heap, 1, DMA_BUF_SIZE);

    for (i = 0; i < 2; i++) {
        __am.ACMDList[i] = alHeapAlloc(c->heap, 1, AUDIO_BUF_SIZE);
    }

    for (i = 0; i < 3; i++) {
        __am.audioInfo[i] = alHeapAlloc(c->heap, 1, sizeof(AudioInfo));
        __am.audioInfo[i]->msg.done.type = OS_SC_DONE_MSG;
        __am.audioInfo[i]->msg.done.info = __am.audioInfo[i];
        __am.audioInfo[i]->data = alHeapAlloc(c->heap, 1, maxFrameSize * 4);
    }
    osCreateMesgQueue(&__am.audioReplyMsgQ, __am.audioReplyMsgBuf, ARRAY_COUNT(__am.audioReplyMsgBuf));
    osCreateMesgQueue(&__am.audioFrameMsgQ, __am.audioFrameMsgBuf, ARRAY_COUNT(__am.audioFrameMsgBuf));
    osCreateMesgQueue(&audDMAMessageQ, audDMAMessageBuf, ARRAY_COUNT(audDMAMessageBuf));
    osCreateMesgQueue(&D_80261188, D_802611A0, ARRAY_COUNT(D_802611A0));
    osCreateThread(&__am.thread, 3, __amMain, NULL, gAudioThreadStack + ARRAY_COUNT(gAudioThreadStack), priority);
    osStartThread(&__am.thread);
}

static void __amMain(void* entry) {
    s32 pad;
    s32 done = FALSE;
    AudioMsg* msg = NULL;
    s32 lastInfo = 0;
    OSScClient scClient;

    osRecvMesg(&D_80261188, (OSMesg*)&msg, OS_MESG_BLOCK);
    _uvScAddClient(&gSchedInst, &scClient, &__am.audioFrameMsgQ);
    while (!done) {
        osRecvMesg(&__am.audioFrameMsgQ, (OSMesg*)&msg, OS_MESG_BLOCK);
        func_8022C3C0(0, 0x29);
        switch (msg->gen.type) {
        case OS_SC_PRE_NMI_MSG:
            break;
        case OS_SC_RETRACE_MSG:
            if (__amHandleFrameMsg(__am.audioInfo[audFrameCt % 3], lastInfo) != 0) {
                osRecvMesg(&__am.audioReplyMsgQ, (OSMesg*)&msg, OS_MESG_BLOCK);
                __amHandleDoneMsg(msg->done.info);
                lastInfo = msg->done.info;
            }
            break;
        case AUDIO_QUIT_MSG:
            done = TRUE;
            break;
        }
    }
    alClose(&__am.g);
}

u32 __amHandleFrameMsg(AudioInfo* info, AudioInfo* previousInfo) {
    s16* audioPtr;
    Acmd* acmdPtr;
    s32 cmdLen;
    OSScTask* task;
    s32 samplesLeft;

    __clearAudioDMA();
    audioPtr = osVirtualToPhysical(info->data);
    if (previousInfo != NULL) {
        osAiSetNextBuffer(previousInfo->data, previousInfo->frameSamples << 2);
    }
    samplesLeft = osAiGetLength() >> 2;
    info->frameSamples = ((frameSize - samplesLeft + EXTRA_SAMPLES) + 16) & ~0xF;
    if (info->frameSamples < minFrameSize) {
        info->frameSamples = minFrameSize;
    }
    acmdPtr = alAudioFrame(__am.ACMDList[curAcmdList], &cmdLen, audioPtr, info->frameSamples);
    if (cmdLen == 0) {
        return 0;
    }
    info->task.next = NULL;
    info->task.msgQ = &__am.audioReplyMsgQ;
    info->task.msg = &info->msg;
    info->task.flags = OS_SC_NEEDS_RDP;

    task = &info->task;
    task->list.t.data_ptr = (u64*)__am.ACMDList[curAcmdList];
    task->list.t.data_size = (acmdPtr - __am.ACMDList[curAcmdList]) * sizeof(Acmd);
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
    curAcmdList ^= 1;
    return 1;
}

static void __amHandleDoneMsg(AudioInfo* task) {
    static s32 firstTime = TRUE;
    s32 samplesLeft = osAiGetLength() >> 2;

    if ((samplesLeft == 0) && !firstTime) {
        _uvDebugPrintf("audio: ai out of samples\n");
        firstTime = FALSE;
    }
}

static s32 __amDMA(s32 addr, s32 len, UNUSED void* state) {
    void* foundBuffer;
    AMDMABuffer* dmaPtr;
    AMDMABuffer* lastDmaPtr;
    s32 delta;
    s32 addrEnd;
    s32 buffEnd;

    dmaPtr = dmaState.firstUsed;
    lastDmaPtr = NULL;

    addrEnd = addr + len;

    while (dmaPtr) {
        buffEnd = dmaPtr->startAddr + DMA_BUF_SIZE;
        if ((u32)addr < dmaPtr->startAddr) {
            break;
        }

        if (buffEnd >= addrEnd) {
            dmaPtr->lastFrame = audFrameCt;
            foundBuffer = dmaPtr->ptr + addr - dmaPtr->startAddr;
            return osVirtualToPhysical(foundBuffer);
        }
        lastDmaPtr = dmaPtr;
        dmaPtr = (AMDMABuffer*)dmaPtr->node.next;
    }

    dmaPtr = dmaState.firstFree;

    dmaState.firstFree = (AMDMABuffer*)dmaPtr->node.next;
    alUnlink(&dmaPtr->node);
    if (lastDmaPtr != NULL) {
        alLink(&dmaPtr->node, &lastDmaPtr->node);
    } else if (dmaState.firstUsed != NULL) {
        lastDmaPtr = dmaState.firstUsed;
        dmaState.firstUsed = dmaPtr;
        dmaPtr->node.next = &lastDmaPtr->node;
        dmaPtr->node.prev = NULL;
        lastDmaPtr->node.prev = &dmaPtr->node;
    } else {
        dmaState.firstUsed = dmaPtr;
        dmaPtr->node.next = NULL;
        dmaPtr->node.prev = NULL;
    }

    foundBuffer = dmaPtr->ptr;
    delta = addr & 1;
    addr -= delta;
    dmaPtr->startAddr = addr;
    dmaPtr->lastFrame = audFrameCt;
    osPiStartDma((OSIoMesg*)&D_80260CF0[nextDMA++], OS_MESG_PRI_HIGH, OS_READ, addr, foundBuffer, DMA_BUF_SIZE, &audDMAMessageQ);
    return osVirtualToPhysical(foundBuffer) + delta;
}

static ALDMAproc __amDmaNew(AMDMAState** state) {
    if (dmaState.initialized == 0) {
        dmaState.firstUsed = NULL;
        dmaState.firstFree = dmaBuffs;
        dmaState.initialized = 1;
    }
    *state = &dmaState;
    return __amDMA;
}

static void __clearAudioDMA(void) {
    s32 i;
    OSIoMesg* iomsg = NULL;
    AMDMABuffer* dmaPtr;
    AMDMABuffer* nextPtr;

    for (i = 0; i < nextDMA; i++) {
        osRecvMesg(&audDMAMessageQ, (OSMesg*)&iomsg, OS_MESG_NOBLOCK);
    }

    dmaPtr = dmaState.firstUsed;
    while (dmaPtr) {
        nextPtr = (AMDMABuffer*)dmaPtr->node.next;

        if (dmaPtr->lastFrame + FRAME_LAG < audFrameCt) {
            if (dmaState.firstUsed == dmaPtr) {
                dmaState.firstUsed = (AMDMABuffer*)dmaPtr->node.next;
            }
            alUnlink(&dmaPtr->node);
            if (dmaState.firstFree) {
                alLink(&dmaPtr->node, &dmaState.firstFree->node);
            } else {
                dmaState.firstFree = dmaPtr;
                dmaPtr->node.next = 0;
                dmaPtr->node.prev = 0;
            }
        }
        dmaPtr = nextPtr;
    }

    nextDMA = 0;
    audFrameCt++;
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
    ALBankFile* bankFile;
    ALSound* sound;
    s32 i;
    s32 pad;

    func_80204438(gUVBlockOffsets.UVSX[arg0], &sp5C, &sp54, &sp58);
    bankFile = alHeapAlloc(&gAudioHeap, 1, SEGMENT_ROM_SIZE(audio_ctl));
    _uvMediaCopy(bankFile, SEGMENT_ROM_START(audio_ctl), SEGMENT_ROM_SIZE(audio_ctl));
    alBnkfNew(bankFile, SEGMENT_ROM_START(audio_tbl));
    gWaveTableBank = bankFile->bankArray[0];
    alSeqpSetBank(gSeqPlayer, gWaveTableBank);
    bankFile = alHeapAlloc(&gAudioHeap, 1, sp54);
    _uvMediaCopy(bankFile, sp5C, sp54);
    alBnkfNew(bankFile, sp58);
    gAudioSXBank = bankFile->bankArray[0];
    gAudioSXInst = gAudioSXBank->instArray[0];
    gSndVoiceTable = alHeapAlloc(&gAudioHeap, 1, gSndPlayer->frameTime * 2);

    sound = gAudioSXInst->soundArray[0];
    for (i = 0; i < gSndPlayer->frameTime; i++) {
        gSndVoiceTable[i] = alSndpAllocate(gSndPlayer, sound);
    }
}
