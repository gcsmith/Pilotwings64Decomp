#ifndef APP_CANNONBALL_H
#define APP_CANNONBALL_H

#include <PR/ultratypes.h>
#include <uv_matrix.h>
#include "code_5A6A0.h"

typedef struct {
    u16 unk0;
    u8 unk2;
    u8 pad3;
    u16 unk4;
    u8 pad6[0xA];
    u16 unk10;
    u8 pad12[2];
    s32 unk14;
    u8 pad18[0x3C];
    u16 unk54;
    u8 unk56;
    u8 pad57;
    s32 unk58;
    u8 pad5C[0x48];
    f32 unkA4;
    u8 padA8[8];
    Unk802D3658_Arg0* unkB0;
    u8 padB4[0x16C];
    s16 unk220;
    u8 pad222[2];
    f32 unk224;
    f32 unk228;
    f32 unk22C;
    f32 unk230;
    f32 unk234;
    f32 unk238;
    f32 unk23C;
    f32 unk240;
    f32 unk244;
    f32 unk248;
    f32 unk24C;
    f32 unk250;
    f32 unk254;
    f32 unk258;
    f32 unk25C;
    f32 unk260;
    f32 unk264;
    f32 unk268;
    f32 unk26C;
    f32 unk270;
    f32 unk274;
    f32 unk278;
    f32 unk27C;
    f32 unk280;
    u8 unk284;
    u8 unk285;
    u8 unk286;
    u8 unk287;
    u8 unk288;
    u8 unk289;
    u8 unk28A;
    u8 unk28B;
    u8 unk28C;
    u8 unk28D;
    u8 unk28E;
    u8 pad28F[2];
    u8 unk291;
    u8 unk292;
    u8 unk293;
    u8 pad294[0x2BC - 0x294];
} Unk802D5B50_Arg2;

void cannon_802D5A90(void);
void cannonLoadLevel(u8, u8 pilot, Unk802D5B50_Arg2*, Unk802D3658_Arg0*);
void cannon_802D5C5C(Unk802D5C5C_Arg0*);
void cannonEndTarget(Unk802D5B50_Arg2*);
void cannonMovementFrame(Unk802D5C5C_Arg0*, u8);
void cannonAimingFrame(Unk802D5C5C_Arg0*);
void cannonShoot(Unk802D5C5C_Arg0*);
void cannonPilotLand(Unk802D5C5C_Arg0*);
void cannonLoadPilot(u8 pilot, Unk802D5B50_Arg2*);
void cannon_802D8A40(u8 arg0, Unk802D5C5C_Arg0* arg1);
s32 cannonLoad802D77D8(Unk80362690* arg0, Unk802D3658_Arg0* arg1);
s32 cannonFrame802D7B7C(Unk80362690* arg0);

#endif // APP_CANNONBALL_H
