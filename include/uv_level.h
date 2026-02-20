#ifndef UV_LEVEL_H
#define UV_LEVEL_H

#include <PR/ultratypes.h>
#include <uv_matrix.h>

#define MAX_CLASSES  8
#define MAX_TESTS    5

enum PilotId {
    PILOT_LARK = 0,
    PILOT_GOOSE = 1,
    PILOT_HAWK  = 2,
    PILOT_KIWI  = 3,
    PILOT_IBIS  = 4,
    PILOT_ROBIN = 5,
    PILOT_COUNT
};

enum VehicleId {
    VEHICLE_HANG_GLIDER = 0,
    VEHICLE_ROCKET_BELT = 1,
    VEHICLE_GYROCOPTER = 2,
    VEHICLE_CANNONBALL = 3,
    VEHICLE_SKY_DIVING = 4,
    VEHICLE_JUMBLE_HOPPER = 5,
    VEHICLE_BIRDMAN = 6,
    VEHICLE_COUNT
};

enum MapId {
    MAP_HOLIDAY_ISLAND = 1,
    MAP_CRESCENT_ISLAND = 3,
    MAP_LITTLE_STATES = 5,
    MAP_EVER_FROST_ISLAND = 10,
};

typedef struct {
    s32 unk0[12];
    f32 unk30;
    f32 unk34;
    f32 unk38;
} Unk80345464_Arg0;

typedef struct Unk802D3658_Unk230 {
    Mtx4F unk0;
    f32 unk40;
    struct Unk802D3658_Unk230* unk44;
    u8 unk48[4];
} Unk802D3658_Unk230;

typedef struct {
    s32 unk0;
    u8 pad4[0x18];
    Vec3F unk1C;
    Vec3F unk28;
} Unk802D3658_Unk1120;

typedef struct {
    s32 unk0;
    u8 pad4[0x24];
    Vec3F unk28;
    Vec3F unk34;
} Unk802D3658_Unk1228;

typedef struct {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u16 unk4;
    u8 unk6;
    u8 pad7;
    f32 unk8;
    u8 unkC;
    u8 unkD;
    u8 unkE;
    u8 unkF;
    u8 pad10[0x14 - 0x10];
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    s16 unk24;
    s16 unk26;
    s16 unk28;
    s16 unk2A;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    f32 unk40;
    f32 unk44;
    f32 unk48;
    f32 unk4C;
    f32 unk50;
    f32 unk54;
    f32 unk58;
    f32 unk5C;
    f32 unk60;
    f32 unk64;
    f32 unk68;
    f32 unk6C;
    f32 unk70;
    f32 unk74;
    f32 unk78;
    f32 unk7C;
    Mtx4F unk80; //  80: BF
    f32 unkC0;
    f32 unkC4;
    Mtx4F unkC8;  //  C8:107
    Mtx4F unk108; // 108:147
    u8 unk148;
    u8 pad149[3];
    Mtx4F unk14C; // 14C:18B
    f32 unk18C;
    f32 unk190;
    f32 unk194;
    f32 unk198;
    f32 unk19C;
    f32 unk1A0;
    f32 unk1A4;
    f32 unk1A8;
    f32 unk1AC;
    f32 unk1B0;
    f32 unk1B4;
    f32 unk1B8;
    Mtx4F unk1BC; // 1BC:1FB
    f32 unk1FC;
    f32 unk200;
    Vec3F unk204;
    Vec3F unk210;
    f32 unk21C;
    f32 unk220;
    f32 unk224;
    f32 unk228;
    u8 unk22C;
    u8 pad22D[0x230 - 0x22D];
    Unk802D3658_Unk230 unk230[50]; // 230:1107
    u8 pad1108[0x1114 - 0x1108];
    u8 unk1114;
    u8 pad1115[0x111C - 0x1115];

    s32 unk111C;
    Unk802D3658_Unk1120 unk1120[5]; // 1120:1223

    s32 unk1224;
    Unk802D3658_Unk1228 unk1228[5]; // 1228:1367

    f32 unk1368;
    f32 unk136C;
    f32 unk1370;
    f32 unk1374;
    f32 unk1378;
    s32 unk137C;
    f32 unk1380;
} Unk802D3658_Arg0;

typedef struct {
    u16 pad0;
    u16 unk2;
    u16 unk4;
    u16 unk6;
    u16 unk8;
    u8 padA[0x20-0xA];
    s32 unk20;
    u8 pad24[0x2C-0x24];
    Unk80345464_Arg0 unk2C;
    u32 pad68;
    s32 unk6C;
    Unk802D3658_Arg0 *unk70;
    s32 unk74;
    u8 pad78[0x7B - 0x78];
    u8 unk7B;
    u8 pad7C[0x8C-0x7C-0xC]; // fill out space to reach 0x8C size in parent struct
} Unk80362690_Unk0_UnkC;

typedef struct {
    s32 unk0;
    u16 map;
    u16 unk6;
    u16 unk8;
    u8 debugFlag;
    u8 unkB;
    Unk80362690_Unk0_UnkC unkC;
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
    Vec3F pos;
    Vec3F angle;
    u8 unk18;
    u8 padC[3];
} LevelBTGT;

typedef struct {
    u8 pad0[4];
    Vec3F pos;
    s32 unk10;
    f32 scale;
    f32 height;
    u8 pad1C[4];
} LevelHOPD;

typedef struct {
    u8 countESND;
    u8 countWOBJ;
    u8 countLPAD;
    u8 countTOYS;
    u8 countTPTS;
    u8 countAPTS;
    u8 countBNUS;
} LevelLEVL;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 unkC;
} LevelOBSV;

typedef struct {
    Vec3F pos;
    f32 scale;
    f32 height;
    s32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
} LevelTHER;

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
    u8 countESND;
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

typedef struct {
    struct {
        u8 classNum;
        u8 vehNum;
        u8 testNum;
        u8 unk3;
        u8 unk4;
        u8 unk5[0x3];
        u8 unk8[4];
        u8 unkC[4];
        s32 unk10;
        u8 unk14[0x18];
        s32 unk2C;
        u8 unk30[0x14];
        f32 unk44;
        s32 unk48;
        u8 unk4C[0x3B8];
        f32 unk404;
        f32 unk408;
        u8 unk40C[0x10];
        u8 countTHER; // count THER
        u8 countLWIN; // count LWIN
        u8 countTPAD; // count TPAD
        u8 countLPAD; // count LPAD
        u8 countLSTP; // count LSTP
        u8 countRNGS; // count RNGS
        u8 countBALS; // count BALS
        u8 countTARG; // count TARG
        u8 countHPAD; // count HPAD
        u8 countBTGT; // count BTGT
        u8 countPHTS; // count PHTS
        u8 countFALC; // count FALC
        u8 countSDFM; // count SDFM
        u8 countCNTG; // count CNTG
        u8 countHOPD; // count HOPD
        u8 countOBSV; // count OBSV
    } comm;
    void* dataNAME;      // ptr NAME
    void* dataINFO;      // ptr INFO
    void* dataJPTX;      // ptr JPTX
    LevelTHER* dataTHER; // ptr THER
    void* dataLWIN;      // ptr LWIN
    void* dataTPAD;      // ptr TPAD
    void* dataLPAD;      // ptr LPAD
    void* dataLSTP;      // ptr LSTP
    void* dataRNGS;      // ptr RNGS
    void* dataBALS;      // ptr BALS
    void* dataTARG;      // ptr TARG
    void* dataHPAD;      // ptr HPAD
    void* dataBTGT;      // ptr BTGT
    void* dataPHTS;      // ptr PHTS
    void* dataFALC;      // ptr FALC
    void* dataSDFM;      // ptr SDFM
    void* dataCNTG;      // ptr CNTG
    void* dataHOPD;      // ptr HOPD
    LevelOBSV* dataOBSV; // ptr OBSV
} LevelCommObjects;

extern Unk80362690* D_80362690;

void uvMemInitBlockHdr(void);
void uvLevelInit(void);
void uvLevelAppend(s32 level_id);
void uvMemLoadDS(u32 tag, s32 palette);
void uvMemLoadPal(s32 palette);

void levelLoad(u8 map, u8 pilot, u8 vehicle, s32 animateToys);
void level_8030B868(void);
void level_8030B964(void);
void level_8030BA60(void);
void levelComputeAppend(u8 pilot, u8 vehicle);
void level_8030BD20(void);
u8 levelGetWOBJ(void** data);
u8 levelGetTPTS(LevelTPTS** data);
u8 levelGetAPTS(void** data);
u8 levelGetLPAD(void** data);
u8 levelGetBNUS(void** data);
LevelObjects* levelLoadMapObjects(u8 mapIdx);

void level_803449B0(void);
s32 levelIsValidIndex(s32 classIdx, s32 testIdx, s32 vehicle);
s32 level_80344E0C(s32 classIdx, s32 testIdx, s32 vehicle, char* arg3, char* arg4);
s32 levelGetTestCount(s32 classIdx, s32 vehicle);
s32 level_80344FC8(s32 classIdx, s32 vehicle, s32 testIdx, u16* map, u16* arg4, u16* arg5);
void level_803453AC(void);
s32 level_80345464(Unk80345464_Arg0*, s32);
s32 level_803456D8(Unk80345464_Arg0*);
void level_80345A24(void);
s32* levelGet_80345C80(void);
s32* levelGet_80345C90(void);
f32 levelGet_80345CA0(void);
u8* levelGet_80345CB0(void);
void levelGet_80345CC0(f32* arg0, f32* arg1);
LevelCommObjects* levelLoadCommObj(u32 arg0);
void level_803462D4(u16 idx);
u8 levelGet_80346364(void);
s32 level_80346370(s32 terra);
void level_8034528C(void);
u8 levelGet_80346468(void);
s32 levelDataGetTHER(LevelTHER** data);
s32 levelDataGetLWIN(void** data);
s32 levelDataGetTPAD(void** data);
s32 levelDataGetCNTG(void** data);
s32 levelDataGetOBSV(LevelOBSV** data);
s32 levelDataGetLPAD(void** data);
s32 levelDataGetLSTP(void** data);
s32 levelDataGetRNGS(void** data);
s32 levelDataGetBALS(void** data);
s32 levelDataGetTARG(void** data);
s32 levelDataGetHPAD(void** data);
s32 levelDataGetBTGT(LevelBTGT** data);
s32 levelDataGetPHTS(void** data);
s32 levelDataGetFALC(void** data);
s32 levelDataGetHOPD(LevelHOPD** data);
void levelGetClsVehTest(u16* classIdx, u16* vehIdx, u16* testIdx);

#endif // UV_LEVEL_H
