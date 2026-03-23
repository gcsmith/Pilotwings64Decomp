#ifndef APP_CODE_72B70_H
#define APP_CODE_72B70_H

#include <uv_matrix.h>
#include <uv_dobj.h>
#include "birdman.h"
#include "gyrocopter.h"
#include "hang_glider.h"
#include "level.h"
#include "rocket_belt.h"
#include "save.h"
#include "skydiving.h"

extern Unk80364210 D_80364210[];

typedef struct {
    u8 unk0[0x44];
} Unk80367710_Unk4; // size = 0x44

typedef struct {
    u8 testCount;
    u8 pad1[3];
    Unk80367710_Unk4 unk4[5];
} Unk80367710;

typedef struct {
    u16 pilot; // PilotId
    u16 veh; // VehicleId
    u16 cls; // ClassId: Beg/A/B/Pilot (or level for bonus)
    u16 test; // test number (or target for CB)
    u16 unk8;
    u8 unkA;
    u8 padB[0x20 - 0xB];
    f32 unk20;
    u8 pad24[0x2C-0x24];
    Mtx4F unk2C;
    void* vehicleData;
    Unk802D3658_Arg0 *unk70;
    Unk80364210 *unk74;
    u8 pad78[0x7A - 0x78];
    u8 unk7A;
    u8 unk7B;
    u8 pad7C[0x80 - 0x7C];
    s32 unk80;
    s32 unk84;
    u8 unk88;
    u8 unk89;
    u8 unk8A;
    u8 unk8B;
} Unk80362690_Unk0;

typedef struct {
    s32 unk0;
    u16 map;
    u16 terraId;
    u16 unk8;
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

void func_802EB9C0(void);
void func_802EBBB8(void);
void func_802EBC30(void);
s32 func_802EC50C(Unk80362690*);
s32 func_802ECE94(Unk80362690*);
void func_802EDD9C(Unk80362690_Unk0*, Mtx4F*);
void func_802EDDEC(Mtx4F*);
void func_802EDAF0(void*, Mtx4F*, f32, f32, f32, f32, f32, u32, s32, s32, s32);
void func_802EE14C(s32);

#endif // APP_CODE_72B70_H
