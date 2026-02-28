#ifndef PILOTWINGS64_UV_AUDIO
#define PILOTWINGS64_UV_AUDIO

#include <ultra64.h>
#include <uv_matrix.h>
#include <uv_sched.h>
#include <uv_util.h>

#define AUDIO_BUF_SIZE 0x4B00
#define DMA_BUF_SIZE 0x800
#define NUM_DMA_BUFFERS 48
#define NUM_DMA_MESSAGES 48
#define AUDIO_QUIT_MSG 10
#define EXTRA_SAMPLES 100
#define OUTPUT_RATE 22050
#define FRAME_LAG 2
#define MAX_MESGS 8

typedef struct uvaEmitter {
/* 00 */ Mtx4F m1;
/* 40 */ Vec3F unk40;
/* 4C */ Vec3F unk4C;
/* 58 */ Vec3F unk58;
/* 64 */ Vec3F unk64;
/* 70 */ Vec4F unk70;
/* 80 */ f32 unk80;
/* 84 */ f32 unk84;
/* 88 */ s32 priority;
/* 8C */ u8 sound;
/* 8D */ u8 unk8D;
/* 8E */ u8 unk8E;
/* 8F */ u8 unk8F;
/* 90 */ f32 near;
/* 94 */ f32 far;
/* 98 */ s32 unk98;
/* 9C */ f32 playPitch;
/* A0 */ s32 playState;
/* A4 */ s32 playVolume;
/* A8 */ s32 state;
/* AC */ u8 playVoice;
/* AD */ u8 playPan;
/* AE */ u8 playMix;
/* AF */ u8 playTimeout;
} uvaEmitter_t;

typedef struct UnkStruct_80200144 {
    Mtx4F mat;
    f32 unk40;
    f32 unk44;
    f32 unk48;
    s32 unk4C;
} UnkStruct_80200144_t;

extern UnkStruct_80200144_t D_80250E80[];

typedef struct {
    ALLink node;
    u32 startAddr;
    u32 lastFrame;
    char *ptr;
} AMDMABuffer;

typedef struct {
    u8 initialized;
    AMDMABuffer *firstUsed;
    AMDMABuffer *firstFree;
} AMDMAState;

typedef union {    
    struct {
        short     type;
    } gen;
    struct {
        short     type;
        struct    AudioInfo *info;
    } done;
    OSScMsg       app;
} AudioMsg;

typedef struct AudioInfo {
    s16* data;
    s16 frameSamples;
    OSScTask task;
    AudioMsg msg;
} AudioInfo; // size 0x80

typedef struct AMAudioMgr {
    Acmd* ACMDList[2];
    AudioInfo* audioInfo[3];
    OSThread thread;
    OSMesgQueue audioFrameMsgQ;
    OSMesg audioFrameMsgBuf[MAX_MESGS];
    OSMesgQueue audioReplyMsgQ;
    OSMesg audioReplyMsgBuf[MAX_MESGS];
    ALGlobals g;
} AMAudioMgr;

// This is what OSIoMesg should be!
typedef struct uvOSIoMesg {
    OSIoMesgHdr  hdr;       /* Message header */
    void        *dramAddr;  /* RDRAM buffer address (DMA) */
    u32          devAddr;   /* Device buffer address (DMA) */
    u32          size;      /* DMA transfer size in bytes */
} uvOSIoMesg;

void uvSysInitAudio(void);
void amCreateAudioMgr(ALSynConfig* c, OSPri priority);

void uvEmitterPrintf(const char* fmt, ...);
void uvEmitterInitTable(void);
void uvEmitterInit(uvaEmitter_t*);
u8   uvEmitterLookup(void);
void uvEmitterFromModel(u8 obj_id, u8 mdl_id);
void uvEmitterSetMatrix(u8 obj_id, Mtx4F* src);
void uvEmitterGetMatrix(u8 obj_id, Mtx4F* dst);
void uvEmitter_80201494(u8 obj_id, Vec3F arg1, Vec3F arg4);
void uvEmitterSetUnk70(u8 obj_id, f32 arg1);
f32  uvEmitterGetUnk70(u8 obj_id);
void uvEmitterSetUnk78(u8 obj_id, f32 arg1);
void uvEmitterSetUnk74(u8 obj_id, f32 arg1);
void uvEmitterSetPri(u8 obj_id, s32 pri);
void uvEmitterProp(u8 obj_id, ...);
void uvEmitterTrigger(u8 obj_id);
void uvEmitterRelease(u8 obj_id);
void uvEmitterStatus(u8 arg0);

void _uvaSoundBegin(void);
void _uvaSoundEnd(void);
void uvEmitterFlush(u16 arg0);
void uvEmitter_80201D08(u8 obj_id, u16 arg1);
void _uvaUpdatePlayList(u8 obj_id);
void _uvaPlaylistRemove(u8 obj_id);
void _uvaPlay(void);
void _uvaStartVoice(u8 obj_id);
void _uvaUpdateVoice(u8 obj_id);
void _uvaStopVoice(u8 voice_id);
void _uvaStatus(u8 obj_id);

void uvaSeqPlay(void);
void uvaSeqSetTempo(f32 tempo);
void uvaSeqSetVol(f32 vol);
void uvaSeqStop(void);

#endif // PILOTWINGS64_UV_AUDIO
