#ifndef APP_HOVER_PADS_H
#define APP_HOVER_PADS_H

#include <PR/ultratypes.h>
#include <uv_matrix.h>

typedef struct {
    u16 objId;
    u8 pad2[2];
    Mtx4F unk4;
    u8 type;
    u8 unk45;
    u8 pad46[2];
    f32 unk48;
    u8 unk4C;
    u8 pad4D[3];
    s32 unk50[5]; // TODO: size
    f32 unk64;
    u8 unk68;
    u8 unk69;
    u8 unk6A;
    u8 unk6B;
    u8 unk6C;
    u8 unk6D;
    u8 pad6E[2];
} HoverPad; // size = 0x70

extern u8 gHoverPadCount;
extern HoverPad gHoverPads[20];

void hoverPadInit(void);
void hoverPad_80309868(void);
void hoverPadLoad(void);
void hoverPadFrameUpdate(Mtx4F*);
void hoverPadDeinit(void);
u8 hoverPad_8030A080(void);
s16 hoverPad_8030A0DC(void);

#endif // APP_HOVER_PADS_H
