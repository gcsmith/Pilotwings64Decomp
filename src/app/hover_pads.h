#ifndef APP_HOVER_PADS_H
#define APP_HOVER_PADS_H

#include <PR/ultratypes.h>
#include <uv_matrix.h>

typedef struct {
    u16 objId;
    u8 pad2[2];
    Mtx4F pose;
    u8 type;
    u8 points;
    u8 pad46[2];
    f32 fuelAdded;
    u8 nextHoverPadCount;
    u8 pad4D[3];
    s32 nextHoverPads[5];
    f32 unk64;
    u8 wasLandedOn;
    u8 initialized;
    u8 unk6A;
    u8 active;
    u8 unk6C; // similar active flag, only written
    u8 radarIdx;
    u8 pad6E[2];
} HoverPad; // size = 0x70

extern HoverPad gHoverPads[20];

void hoverPadInit(void);
void hoverPad_80309868(void);
void hoverPadLoad(void);
void hoverPadActivateNext(s32 hoverIdx);
void hoverPadFrameUpdate(Mtx4F*);
void hoverPadLanded(s32 hoverIdx);
f32 hoverPadGetAltitude(s32 hoverIdx);
f32 hoverPadGetFuel(s32 hoverIdx);
s32 hoverPadGetLandedIdx(s32 objId, s32);
void hoverPadDeinit(void);
u8 hoverPadGetCount(void);
s16 hoverPadGetPoints(void);

#endif // APP_HOVER_PADS_H
