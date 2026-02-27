#ifndef PILOTWINGS64_UV_SCHED
#define PILOTWINGS64_UV_SCHED

#include <ultra64.h>
#include <PR/sched.h>
#include <uv_matrix.h>
#include <uv_util.h>

#define UV_MESG_DMA     0
#define UV_MESG_SCHED   2
#define UV_MESG_GFX     4

typedef struct Unk8022B0A0 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
} Unk8022B0A0; // size: 0x10

extern OSSched gSchedInst;

void uvWaitForMesg(char msg_type);

void _uvScDoneGfx(void);
void _uvScDoneAud(void);
void _uvScRunAud(void);
void _uvScRunGfx(void);
void _uvScDlistRecover(void);
void _uvScCreateScheduler(OSSched* sc, void* stack, s32 priority, u8 mode, u8 numFields);
void _uvScAddClient(OSSched *s, OSScClient *c, OSMesgQueue *msgQ);
OSMesgQueue* _uvScGetCmdQ(OSSched *s);
void _uvScMain(void* arg);
void _uvScHandleRetrace(void);
void _uvScHandleRSP(void);
void _uvScHandleRDP(void);
void _uvScHandleNMI(void);
void _uvScLogCpuEvent(s32 ring);
void _uvScLogIntoRing(void);
void func_8022B0A0(Unk8022B0A0* arg0, Mtx4F* arg1);
void func_8022BEB8(s32 arg0);
void func_8022C34C(void);
void func_8022C3C0(u8 arg0, s32 arg1);

#endif // PILOTWINGS64_UV_SCHED
