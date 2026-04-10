#ifndef APP_TARGETS_H
#define APP_TARGETS_H

#include <PR/ultratypes.h>
#include <uv_matrix.h>
#include "task.h"

typedef struct {
    u16 objId; // alloc index?
    u8 pad2[0x4-0x2];
    Mtx4F unk4;
    u8 unk44;
    u8 unk45;
    u8 unk46;
    u8 unk47;
    u8 unk48;
    u8 pad49[0x4C - 0x49];
} MissileTarget; // size = 0x4C

extern MissileTarget sMissileTargets[40];
extern TaskObjects *D_8035078C;

void targetsInit(void);
void targetsLoad(void);
void targetsFrameUpdate(Mtx4F*);
void targetsDeinit(void);
u8 targets_803448F4(void);
f32 targets_8034473C(s32, s32);
s16 targets_80344948(void);

#endif // APP_TARGETS_H
