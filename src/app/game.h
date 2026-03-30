#ifndef APP_GAME_H
#define APP_GAME_H

#include <uv_matrix.h>
#include <uv_dobj.h>
#include "birdman.h"
#include "gyrocopter.h"
#include "hang_glider.h"
#include "level.h"
#include "rocket_belt.h"
#include "save.h"
#include "skydiving.h"

typedef enum GameState {
    /*  0 */ GAME_STATE_TITLE,
    /*  1 */ GAME_STATE_1,
    /*  2 */ GAME_STATE_TEST_DETAILS,
    /*  3 */ GAME_STATE_PILOT_SELECT,
    /*  4 */ GAME_STATE_TEST_SETUP,
    /*  5 */ GAME_STATE_TEST_UPDATE,
    /*  6 */ GAME_STATE_RESULTS,
    /*  7 */ GAME_STATE_OPTIONS,
    /*  8 */ GAME_STATE_DEMO_PILOT,
    /*  9 */ GAME_STATE_DEMO_TEST_SETUP,
    /* 10 */ GAME_STATE_FILE_MENU,
    /* 11 */ GAME_STATE_VEHICLE_CLASS_SELECT,
    /* 12 */ GAME_STATE_TEST_OVERVIEW,
    /* 13 */ GAME_STATE_RESULTS_CB,
    /* 14 */ GAME_STATE_CONGRATULATIONS,
    /* 15 */ GAME_STATE_CREDITS,
    /* 16 */ GAME_STATE_COUNT,
} GameState;

extern Unk80364210 D_80364210[];

typedef struct Unk80367710_Unk4 {
    u8 unk0;
    u8 pad1[0x43];
} Unk80367710_Unk4;

typedef struct Unk80367710 {
    u8 testCount;
    u8 pad1[0x3];
    Unk80367710_Unk4 unk4[5];
} Unk80367710;

typedef struct Unk80367868_Unk4 {
    u8 pilot;
    u16 modelId;
    s32 pad4[0x11];
    u16 unk48; // text
    u8 pad4A[0x2];
} Unk80367868_Unk4;

typedef struct Unk80367868 {
    u8 unk0;
    u8 pad1[0x3];
    Unk80367868_Unk4 unk4[PILOT_COUNT];
} Unk80367868;

typedef struct {
    u16 pilot; // PilotId
    u16 veh; // VehicleId
    u16 cls; // ClassId: Beg/A/B/Pilot (or level for bonus)
    u16 test; // test number (or target for CB)
    u16 unk8;
    u8 unkA;
    u8 padB[0x1];
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    Mtx4F unk2C;
    void* vehicleData;
    Camera *unk70;
    Unk80364210 *unk74;
    u8 unk78;
    u8 unk79;
    u8 unk7A;
    u8 unk7B;
    u8 unk7C;
    u8 pad7D[0x80 - 0x7D];
    f32 unk80;
    s32 unk84;
    s16 smokeId;
    u8 unk8A;
    u8 unk8B;
} Unk80362690_Unk0;

typedef struct {
    s32 state;
    u16 map;
    u16 terraId;
    u16 envId;
    u8 debugFlag;
    u8 unkB;
    Unk80362690_Unk0 unkC[1];
    s32 unk98;
    s32 unk9C;
    u8 unkA0;
    u8 unkA1;
    u8 unkA2;
    u8 unkA3;
    u8 unkA4;
    u8 padA5[3];
    s32 unkA8;
} Unk80362690;

extern Unk80362690* D_80362690;

void gameInit(void);
void func_802EBBB8(void);
void gameUpdate(void);
s32 gameUpdateStateTestSetup(Unk80362690*);
void func_802ECE94(Unk80362690*);
void func_802EDD9C(Unk80362690_Unk0*, Mtx4F*);
void func_802EDDEC(Mtx4F*);
void func_802EDAF0(Unk80362690_Unk0*, Mtx4F*, f32, f32, f32, f32, f32, u16, u8, u8, u8);
void func_802EE14C(u16);

#endif // APP_GAME_H
