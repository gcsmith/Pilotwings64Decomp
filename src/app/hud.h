#ifndef APP_HUD_H
#define APP_HUD_H

#include <uv_matrix.h>

// for HUDState.renderFlags
#define HUD_RENDER_HANG_GLIDER   0x0002
#define HUD_RENDER_ROCKET_PACK   0x0004
#define HUD_RENDER_GYROCOPTER    0x0008
#define HUD_RENDER_CANNONBALL    0x0010
#define HUD_RENDER_SKYDIVING     0x0020
#define HUD_RENDER_JUMBLE_HOPPER 0x0040
#define HUD_RENDER_BIRDMAN       0x0080
#define HUD_RENDER_RETICLE       0x0200
#define HUD_RENDER_DISABLE       0x0400
#define HUD_RENDER_ANY_VEHICLE (HUD_RENDER_HANG_GLIDER | \
                                HUD_RENDER_ROCKET_PACK | \
                                HUD_RENDER_GYROCOPTER | \
                                HUD_RENDER_CANNONBALL | \
                                HUD_RENDER_SKYDIVING | \
                                HUD_RENDER_JUMBLE_HOPPER | \
                                HUD_RENDER_BIRDMAN)

// for HUDState.cameraState
#define HUD_CAM_RENDER_RETICLE 0x80000000
#define HUD_CAM_RENDER_SHUTTER 0x40000000

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    s32 unk14;
    s32 unk18;
    u8 unk1C;
    u8 pad1D[3];
} HUDRadar_Waypoint;

typedef struct {
    f32 x;
    f32 y;
    f32 unk8;
    s32 unkC;
} HUDRadar_Goals;

typedef struct {
    Vec3F pos;
    f32 scale;
} HUDRadar_Thermal;

typedef struct {
    s32 goalCount;
    s32 unk4;
    HUDRadar_Goals goals[10];
    HUDRadar_Waypoint waypoints[70];
    HUDRadar_Thermal therms[20];
    f32 windDir; // angle wind arrow points on HUD radar (0.0 is up, pi/2 is left)
    f32 windSpeed; // wind arrow length normalized [0.0, 1.0]
} HUDRadar;

typedef struct {
    f32 x;
    f32 y;
    f32 heading;
    f32 pitch;
} HUDAttitude;

typedef struct {
    u16 renderFlags;
    s16 pad2;
    union {
        s32 cameraState; // camera and shutter
        s32 cloudFade;   // skydiving cloud fade
    };
    s8 unk8;
    s8 pad9[3];
    s32 unkC;
    f32 elapsedTime;
    f32 unk14;
    f32 power;
    f32 fuel;
    f32 unk20;
    f32 unk24;
    Mtx4F unk28;
    HUDAttitude att;
    f32 unk78;
    f32 unk7C;
    f32 altitude;
    f32 altSeaLevel;
    f32 speed;
    f32 unk8C;
    HUDRadar radar;
    s16 unkB40[0x3C];
    f32 unkBB8;
    f32 unkBBC;
    f32 unkBC0;
    f32 unkBC4;
    f32 unkBC8;
    u8 unkBCC;
    u8 padBCD;
    s16 unkBCE;
    s16 unkBD0[0x3C];
    f32 unkC48;
    f32 unkC4C;
    f32 unkC50;
    f32 unkC54;
    f32 unkC58;
    u8 unkC5C;
    u8 padC5D;
    s16 unkC5E;
    u8 unkC60;
    u8 padC61[3];
    f32 unkC64;
    f32 unkC68;
    f32 unkC6C;
    f32 unkC70;
    s8 unkC74;
    u8 padC75[3];
    u8 showController;
} HUDState;

void hudInit(void);
HUDState* hudGetState(void);
void hudMainRender(void);
void hudText_8031D8E0(s16, f32, f32);
void hudWarningText(s16, f32, f32);
void hudDemoControllerEn(u8 enable);
void hudSetCameraState(s32 state);

#endif // APP_HUD_H
