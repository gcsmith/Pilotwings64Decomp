#ifndef APP_PADS_H
#define APP_PADS_H

#include <uv_level.h>

typedef struct {
    u8 unk0[4];
    f32 x;
    f32 y;
    s32 unkC;
    u8 unk10[4];
    u8 unk14;
    u8 pad15[3];
} LandingPad;

typedef struct {
    f32 unk0;
    f32 unk4;
    u8 pad8[4];
    f32 unkC;
    f32 unk10;
    u8 pad14[0x10];
    f32 x;
    f32 y;
    u8 unk2C[0x10];
} LandingStrip;

extern u8 gLandingPadCount; // count of gLandingPads
extern u8 gLandingStripCount; // count of gLandingStrips
extern LandingPad gLandingPads[14]; // parsed landing pad data, also copied to HUD
extern LandingStrip gLandingStrips[2]; // parsed landing strip data, also copied to HUD

void func_80316DC0(void);
void func_80316E40(void);
void func_80317634(Unk80345464_Arg0*);
void func_8031776C(void);

#endif // APP_PADS_H
