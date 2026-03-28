#ifndef APP_CANNONBALL_H
#define APP_CANNONBALL_H

#include <PR/ultratypes.h>
#include <uv_matrix.h>
#include <uv_vector.h>
#include "camera.h"
#include "game.h"

typedef struct {
    u16 objId;
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
    f32 zAxis;
    f32 xAxis;
    f32 unkA4;
    u8 padA8[8];
    Camera* unkB0;
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
    u8 padD6[0x110 - 0xD6];
    Vec3F unk110;
    u8 unk11C;
    s8 unk11D;
    f32 unk120;
    s32 unk124;
    f32 unk128;
    Vec3F unk12C;
    Mtx4F unk138;
    Mtx4F unk178;
    Vec3F unk1B8;
    Vec3F unk1C4;
    f32 unk1D0;
    Vec3F unk1D4;
    Vec3F unk1E0;
    f32 unk1EC;
    Vec3F unk1F0;
    Vec3F unk1FC;
    Vec3F unk208;
    Vec3F unk214;
    u16 modelId;
    u8 pad222[2];
    Vec3F unk224;
    Vec3F unk230;
    Vec3F unk23C;
    Vec3F unk248;
    Vec3F unk254;
    Vec3F unk260;
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
    Vec3F unk294;
    s32 unk2A0;
    f32 unk2A4;
    f32 unk2A8;
    s32 unk2AC;
    u8 unk2B0;
    u8 unk2B1;
    u8 pad2B2[0x2];
    u8 unk2B4;
    u8 unk2B5;
    u8 pad2B6[0x2];
    f32 unk2B8;
} CannonballData;

extern s32 D_80359AA8;
extern s32 D_80359AAC;

void cannonInit(void);
void cannonLoadLevel(u8, u8 pilot, CannonballData*, Camera*);
void cannonLevelEnterLeave(CannonballData*);
void cannonEndTarget(CannonballData*);
void cannonMovementFrame(CannonballData*, u8);
void cannonAimingFrame(CannonballData*);
void cannonShoot(CannonballData*);
void cannonPilotLand(CannonballData*);
void cannonLoadPilot(u8 pilot, CannonballData*);
void cannon_802D8A40(u8 arg0, CannonballData* arg1);
s32 cannonLoad802D77D8(Unk80362690* arg0, CannonballData* arg1);
s32 cannonFrame802D7B7C(Unk80362690* arg0);
s32 cannonLandedFrame(CannonballData*);

#endif // APP_CANNONBALL_H
