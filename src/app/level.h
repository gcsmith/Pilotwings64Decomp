#ifndef APP_LEVEL_H
#define APP_LEVEL_H

#include <PR/ultratypes.h>
#include <uv_vector.h>
#include "task.h"

typedef struct {
    u8 unk0;
    u8 pad1;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    u16 pad10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    s16 unk1E;
    s16 unk20;
    s16 unk22;
    s16 unk24;
    s16 pad26;
    s32 unk28;
    s16 unk2C;
    s16 unk2E;
} Unk80364210_Unk0_Unk0; // size = 0x30

typedef struct {
    Unk80364210_Unk0_Unk0 unk0[MAX_TESTS][VEHICLE_COUNT];
    s8 unk690;
    u8 pad691[0x694-0x691];
} Unk80364210_Unk0; // size = 0x694

typedef struct {
    s32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    s32 unk24;
    s32 pad28;
    s32 unk2C;
    s32 unk30;
    s32 unk34;
    s32 unk38;
    u8 unk3C;
    s8 unk3D;
    u8 pad3E;
    u8 pad3F;
    Unk80364210_Unk0 unk40[MAX_CLASSES];
} Unk80364210; // size = 0x34E0

typedef struct {
    Vec3F pos;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    s32 unk18;
} LevelBNUS; // size = 0x1C

typedef struct {
    Vec3F pos;
    f32 unkC;
    s32 unk10;
    u8 unk14;
    u8 pad15[3];
} PotentialLPAD; // size = 0x18

typedef struct {
    s32 unk0[4];
} LevelTOYS; // size = 0x10

typedef struct {
    u8 unk0;
    u8 unk1[3];
    f32 unk4_X;
    f32 unk8_Y;
    f32 unkC_Z;
    f32 unk10;
    f32 unk14;
    s32 unk18;
    f32 unk1C;
    s32 unk20;
    f32 unk24;
    f32 unk28_X;
    f32 unk2C_Y;
    f32 unk30_Z;
} LevelTPTS; // size = 0x34

typedef struct {
    u8 countESND;
    u8 countWOBJ;
    u8 countLPAD;
    u8 countTOYS;
    u8 countTPTS;
    u8 countAPTS;
    u8 countBNUS;
    u8 pad7;
    void* dataWOBJ;
    PotentialLPAD* dataLPAD;
    LevelTPTS* dataTPTS;
    LevelTOYS* dataTOYS;
    void* dataAPTS;
    LevelBNUS* dataBNUS;
} LevelObjects;

void levelLoad(u8 map, u8 pilot, u8 vehicle, s32 animateToys);
void level_8030B868(void);
void level_8030B964(void);
void level_8030BA60(void);
void levelComputeAppend(u8 pilot, u8 vehicle);
void level_8030BD20(void);
u8 levelGetWOBJ(void** data);
u8 levelGetTPTS(LevelTPTS** data);
u8 levelGetAPTS(void** data);
u8 levelGetLPAD(PotentialLPAD** data);
u8 levelGetBNUS(LevelBNUS** data);
LevelObjects* levelLoadMapObjects(u8 mapIdx);

#endif // APP_LEVEL_H
