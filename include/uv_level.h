#ifndef UV_LEVEL_H
#define UV_LEVEL_H

#include <PR/ultratypes.h>

#define MAX_CLASSES  8
#define MAX_TESTS    5
#define MAX_VEHICLES 7

typedef struct {
    u8 unk0[0x22C];
    u8 unk22C;
} Unk80362690_Unk0_Unk7C; // this could be Unk8037A600

typedef struct {
    s32 unk0;
    u16 unk4;
    u16 unk6;
    u16 unk8;
    u8 unkA[0x4];
    u16 unkE;
    s32 unk10;
    u16 unk14;
    u8 unk16[0x62];
    s32 unk78;
    Unk80362690_Unk0_Unk7C* unk7C;
    u8 unk80[0xC];
} Unk80362690_Unk0;

typedef struct {
    Unk80362690_Unk0 unk0[1];
    s32 unk8C;
    s32 unk90;
    s32 unk94;
    s32 unk98;
    s32 unk9C;
    u8 unkA0;
    u8 padA1[7];
    s32 unkA8;
} Unk80362690;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 unkC;
} LevelOBSV;

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
} LevelTPTS;

typedef struct {
    s32 unk0[4];
} LevelTOYS;

typedef struct {
    u8 unk0;
    u8 countWOBJ;
    u8 countLPAD;
    u8 countTOYS;
    u8 countTPTS;
    u8 countAPTS;
    u8 countBNUS;
    u8 pad7;
    void* dataWOBJ;
    void* dataLPAD;
    LevelTPTS* dataTPTS;
    LevelTOYS* dataTOYS;
    void* dataAPTS;
    void* dataBNUS;
} LevelObjects;

extern Unk80362690* D_80362690;

void func_8030B6C0(u8 arg0, u8 arg1, u8 arg2, s32 arg3);
void func_8030B868(void);
void func_8030B964(void);
void func_8030BA60(void);
void func_8030BA98(u8 pilot, u8 vehicle);
void func_8030BD20(void);
u8 levelGetWOBJ(void** data);
u8 levelGetTPTS(LevelTPTS** data);
u8 levelGetAPTS(void** data);
u8 levelGetLPAD(void** data);
u8 levelGetBNUS(void** data);
LevelObjects* func_8030BDC8(u8 arg0);

u8 levelDataGetTHER(void** data);
u8 levelDataGetLWIN(void** data);
u8 levelDataGetTPAD(void** data);
u8 levelDataGetCNTG(void** data);
u8 levelDataGetOBSV(LevelOBSV** data);
u8 levelDataGetLPAD(void** data);
u8 levelDataGetLSTP(void** data);
u8 levelDataGetRNGS(void** data);
u8 levelDataGetBALS(void** data);
u8 levelDataGetTARG(void** data);
u8 levelDataGetHPAD(void** data);
u8 levelDataGetBTGT(void** data);
u8 levelDataGetPHTS(void** data);
u8 levelDataGetFALC(void** data);
u8 levelDataGetHOPD(void** data);

#endif // UV_LEVEL_H
