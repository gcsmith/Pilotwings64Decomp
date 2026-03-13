#ifndef APP_PADS_H
#define APP_PADS_H

#include <uv_matrix.h>
#include <uv_vector.h>

typedef struct {
    u8 unk0[4];
    Vec3F pos;
    f32 unk10;
    u8 unk14;
    u8 unk15;
    u8 unk16;
    u8 unk17;
} LandingPad; // size = 0x18

typedef struct {
    Vec3F pos;
    Vec3F unkC;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 unk30;
    f32 unk34;
    u8 unk38;
    u8 unk39;
    u8 pad3A[2];
} LandingStrip; // size = 0x3C

extern u8 gLandingPadCount; // count of gLandingPads
extern u8 gLandingStripCount; // count of gLandingStrips
extern LandingPad gLandingPads[14]; // parsed landing pad data, also copied to HUD
extern LandingStrip gLandingStrips[2]; // parsed landing strip data, also copied to HUD

void padsInit(void);
void padsLoad(void);
void padsFrameUpdate(Mtx4F*);
void padsDeinit(void);
f32 func_80317978(f32, f32, f32, u8*);

#endif // APP_PADS_H
