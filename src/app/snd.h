#ifndef APP_SND_H
#define APP_SND_H

#include <PR/ultratypes.h>
#include <uv_matrix.h>

extern u16 D_803505B0;

void sndInit(void);
void func_8033F6F8(Mtx4F*, Mtx4F*);
void func_8033F748(u16);
void sndPlaySfxVolPitchPan(u8, f32, f32, f32);
void sndPlaySfx(u8);
u8 sndMakeDev(s32);
u8 func_8033F8CC(u8);
void func_8033F904(u8, f32, f32, f32);
void func_8033F964(u8);
void func_8033FA88(f32);
void func_8033FAD4(f32);
void func_8033FB14(void);
void sndGetPilotScream(s32*, f32*);
void func_8033FCD0(u16);
void func_8033FA88(f32);
void func_8033FD94(u16, f32, f32);

enum Sfx {
    /* 0x00 */ SFX_UI_MOVE_CHIME, // main menu chime
    /* 0x01 */ SFX_UI_CANCEL,
    /* 0x02 */ SFX_UNK_002,
    /* 0x03 */ SFX_UNK_003,
    /* 0x04 */ SFX_UI_PAUSE,
    /* 0x05 */ SFX_UI_HUD_CHIME,
    /* 0x06 */ SFX_UNK_006,
    /* 0x07 */ SFX_UNK_007,
    /* 0x08 */ SFX_UNK_008,
    /* 0x09 */ SFX_UNK_009,
    /* 0x0A */ SFX_UNK_010,
    /* 0x0B */ SFX_UNK_011,
    /* 0x0C */ SFX_UNK_012,
    /* 0x0D */ SFX_UNK_013,
    /* 0x0E */ SFX_UNK_014,
    /* 0x0F */ SFX_UI_TEST_START, // also used for rings
    /* 0x10 */ SFX_UNK_016,
    /* 0x11 */ SFX_GOAL_GONG,
    /* 0x12 */ SFX_UNK_018,
    /* 0x13 */ SFX_MOVEMENT_WIND, // used with two emitters for stereo effect
    /* 0x14 */ SFX_UNK_020,
    /* 0x15 */ SFX_UNK_021,
    /* 0x16 */ SFX_UNK_022,
    /* 0x17 */ SFX_UNK_023,
    /* 0x18 */ SFX_UNK_024,
    /* 0x19 */ SFX_UNK_025,
    /* 0x1A */ SFX_WATER_SPLASH,
    /* 0x1B */ SFX_UNK_027,
    /* 0x1C */ SFX_UNK_028,
    /* 0x1D */ SFX_PILOT_GOOSE_SCREAM,
    /* 0x1E */ SFX_RB_ENGINE,
    /* 0x1F */ SFX_UNK_031,
    /* 0x20 */ SFX_UNK_032,
    /* 0x21 */ SFX_UNK_033,
    /* 0x22 */ SFX_UNK_034,
    /* 0x23 */ SFX_RB_FLY_UP,   // gliding up sfx as altitude increases
    /* 0x24 */ SFX_RB_FLY_DOWN, // gliding down
    /* 0x25 */ SFX_UNK_037,
    /* 0x26 */ SFX_UNK_038,
    /* 0x27 */ SFX_UNK_039,
    /* 0x28 */ SFX_UNK_040,
    /* 0x29 */ SFX_UNK_041,
    /* 0x2A */ SFX_UNK_042,
    /* 0x2B */ SFX_UNK_043,
    /* 0x2C */ SFX_UNK_044,
    /* 0x2D */ SFX_UNK_045,
    /* 0x2E */ SFX_UNK_046,
    /* 0x2F */ SFX_GYRO_MISSILE_FIRE,
    /* 0x30 */ SFX_UNK_048,
    /* 0x31 */ SFX_UNK_049,
    /* 0x32 */ SFX_UNK_050,
    /* 0x33 */ SFX_UNK_051,
    /* 0x34 */ SFX_UNK_052,
    /* 0x35 */ SFX_UNK_053,
    /* 0x36 */ SFX_CRASH_LANDING_REVEAL,
    /* 0x37 */ SFX_UNK_055,
    /* 0x38 */ SFX_UNK_056,
    /* 0x39 */ SFX_UNK_057,
    /* 0x3A */ SFX_UNK_058,
    /* 0x3B */ SFX_UNK_059,
    /* 0x3C */ SFX_UNK_060,
    /* 0x3D */ SFX_QUICK_SWISH, // "64" logo fly-in and pilot head shake 
    /* 0x3E */ SFX_UNK_062,
    /* 0x3F */ SFX_UNK_063,
    /* 0x40 */ SFX_UNK_064,
    /* 0x41 */ SFX_UNK_065,
    /* 0x42 */ SFX_UNK_066,
    /* 0x43 */ SFX_UNK_067,
    /* 0x44 */ SFX_UNK_068,
    /* 0x45 */ SFX_UNK_069,
    /* 0x46 */ SFX_UNK_070,
    /* 0x47 */ SFX_UNK_071,
    /* 0x48 */ SFX_UNK_072,
    /* 0x49 */ SFX_UNK_073,
    /* 0x4A */ SFX_UNK_074,
    /* 0x4B */ SFX_UNK_075,
    /* 0x4C */ SFX_UI_MAP_MOVE,
    /* 0x4D */ SFX_UNK_077,
    /* 0x4E */ SFX_UNK_078,
    /* 0x4F */ SFX_UNK_079,
    /* 0x50 */ SFX_UNK_080,
    /* 0x51 */ SFX_UNK_081,
    /* 0x52 */ SFX_UNK_082,
    /* 0x53 */ SFX_PILOT_IBIS_SCREAM,
    /* 0x54 */ SFX_UNK_084,
    /* 0x55 */ SFX_PILOT_LARK_SCREAM,
    /* 0x56 */ SFX_PILOT_HAWK_SCREAM,
    /* 0x57 */ SFX_PILOT_KIWI_SCREAM,
    /* 0x58 */ SFX_PILOT_ROBIN_SCREAM,
    /* 0x59 */ SFX_UI_TARGET_APPEAR,
    /* 0x5A */ SFX_UNK_090,
    /* 0x5B */ SFX_UNK_091,
    /* 0x5C */ SFX_HANG_AIR_BRAKE,
    /* 0x5D */ SFX_UNK_093,
    /* 0x5E */ SFX_UNK_094,
    /* 0x5F */ SFX_UNK_095,
    /* 0x60 */ SFX_UNK_096,
    /* 0x61 */ SFX_PILOT_LARK_SELECT,
    /* 0x62 */ SFX_PILOT_KIWI_SELECT,
    /* 0x63 */ SFX_PILOT_GOOSE_SELECT,
    /* 0x64 */ SFX_PILOT_IBIS_SELECT,
    /* 0x65 */ SFX_PILOT_HAWK_SELECT,
    /* 0x66 */ SFX_PILOT_ROBIN_SELECT,
    /* 0x67 */ SFX_UI_CAMERA_MOVE,
    /* 0x68 */ SFX_MISSI_ROAR,
    /* 0x69 */ SFX_UI_POINT_PENALTY, // also max photo count?
    /* 0x6A */ SFX_UNK_106,
    /* 0x6B */ SFX_UNK_107,
    /* 0x6C */ SFX_UNK_108,
    /* 0x6D */ SFX_UI_FUEL_ADDED,
    /* 0x6E */ SFX_UI_CONFIRM,
    /* 0x6F */ SFX_UNK_111,
    /* 0x70 */ SFX_UNK_112,
    /* 0x71 */ SFX_UI_VIEW_MAP,
    /* 0x72 */ SFX_UI_HINT,
    /* 0x73 */ SFX_UI_SCORING,
    /* 0x74 */ SFX_UI_SELECT_MOVE, // 808 cowbell
    /* 0x75 */ SFX_UI_CONTROL,
    /* 0x76 */ SFX_UNK_118,        // duplicate of SFX_UI_HINT
    /* 0x77 */ SFX_UNK_119
};

#endif // APP_SND_H
