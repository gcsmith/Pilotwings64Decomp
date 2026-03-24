#ifndef APP_PADS_H
#define APP_PADS_H

#include <uv_matrix.h>
#include <uv_vector.h>

typedef struct {
    u16 objId;
    u8 radarIdx;
    u8 pad3[1];
    Mtx4F pose;
    f32 deltaZ;
} CannonTarget; // size = 0x48

typedef struct {
    u8 unk0[4];
    Vec3F pos;
    f32 landingDistance;
    u8 isUsed;
    u8 initialized;
    u8 idxLevelLPAD;
    u8 type;
} LandingPad; // size = 0x18

typedef struct {
    Vec3F pos0;
    Vec3F pos1;
    Vec3F normal;
    Vec3F midpoint;
    f32 landingDistance;
    f32 landingAlignment;
    u8 validStrip;
    u8 initialized;
    u8 pad3A[2];
} LandingStrip; // size = 0x3C

typedef struct {
    Vec3F pos;
} TakeoffPad; // size = 0xC

extern u8 gLandingPadCount;
extern u8 gLandingStripCount;
extern LandingPad gLandingPads[14]; // parsed landing pad data, also copied to HUD
extern LandingStrip gLandingStrips[2]; // parsed landing strip data, also copied to HUD

void padsInit(void);
void padsLoad(void);
void padsFrameUpdate(Mtx4F* pose);
void padsDeinit(void);
void padsInitLandingPads(void);

// get distance to the specified cannon target ID
// returns distance if target found, else 1000.0f
f32 padsCannonTgtDist(f32 x, f32 y, f32 z, u16 targetObjId);

// get the index to the landing pad or strip which pilot landed on
// returns distance to the pad or strip if landed, else 1000000.0f
f32 padsLandedPadStrip(f32 x, f32 y, f32 z, u8* outIdx);

#endif // APP_PADS_H
