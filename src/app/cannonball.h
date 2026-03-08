#ifndef APP_CANNONBALL_H
#define APP_CANNONBALL_H

#include <PR/ultratypes.h>
#include <uv_level.h>
#include <uv_matrix.h>
#include "code_5A6A0.h"

typedef struct {
    u16 unk0;
    u8 unk2;
    u8 pad3;
    u16 unk4;
    u16 pad6;
    f32 unk8;
    u16 unkC;
    u16 unkE;
    u16 unk10;
    u16 pad12;
    Mtx4F unk14;
    u16 unk54;
    u8 unk56;
    u8 pad57;
    Mtx4F unk58;
    f32 unk98;
    union {
        f32 zxAxis[2];
        struct {
            f32 zAxis; // rotation intended here
            f32 xAxis;
        };
    };
    f32 unkA4;
    u8 padA8[8];
    Unk802D3658_Arg0* unkB0;
    u8 unkB4;
    u8 padB5[3];
    f32 unkB8;
    f32 unkBC;
    f32 unkC0;
    u8 unkC4;
    u8 padC5[3];
    f32 unkC8;
    f32 unkCC;
    f32 unkD0;
    u8 unkD4;
    u8 unkD5;
    u8 padD6[0x11C - 0xD6];
    u8 unk11C;
    s8 unk11D;
    f32 unk120;
    u8 pad124[0x12C - 0x124];
    f32 unk12C;
    f32 unk130;
    f32 unk134;
    u8 pad138[0x1B8 - 0x138];
    Vec3F unk1B8;
    f32 unk1C4;
    f32 unk1C8;
    f32 unk1CC;
    f32 unk1D0;
    u8 pad1D4[0x220 - 0x1D4];
    u16 modelId;
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
    u8 pad294[0x2B4 - 0x294];
    u8 unk2B4;
    u8 pad2B5[0x2BC-0x2B5];
} Unk802D5B50_Arg2;

extern u16 D_80359AAA;
extern u16 D_80359AAE;

void cannon_802D5A90(void);
void cannonLoadLevel(u8, u8 pilot, Unk802D5B50_Arg2*, Unk802D3658_Arg0*);
void cannon_802D5C5C(Unk802D5B50_Arg2*);
void cannonEndTarget(Unk802D5B50_Arg2*);
void cannonMovementFrame(Unk802D5B50_Arg2*, u8);
void cannonAimingFrame(Unk802D5B50_Arg2*);
void cannonShoot(Unk802D5B50_Arg2*);
void cannonPilotLand(Unk802D5B50_Arg2*);
void cannonLoadPilot(u8 pilot, Unk802D5B50_Arg2*);
void cannon_802D8A40(u8 arg0, Unk802D5B50_Arg2* arg1);
s32 cannonLoad802D77D8(Unk80362690* arg0, Unk802D3658_Arg0* arg1);
s32 cannonFrame802D7B7C(Unk80362690* arg0);

#endif // APP_CANNONBALL_H
