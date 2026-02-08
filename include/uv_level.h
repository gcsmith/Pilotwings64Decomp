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

typedef struct {
    u8 unk0[0x108];
    Mtx4F unk108;
    u8 unk148[0x22C - 0x148];
    u8 unk22C;
} Unk80362690_Unk0_Unk7C; // this could be Unk8037A600

typedef struct {
    s32 unk0;
    u16 map;
    u16 unk6;
    u16 unk8;
    u8 debugFlag;
    u8 unkB;
    u16 unkC[2];
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

typedef struct {
    struct {
        u8 classNum;
        u8 vehNum;
        u8 testNum;
        u8 unk3;
        u8 unk4;
        u8 unk5[0x3];
        s32 unk8;
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
    void* dataTHER;      // ptr THER
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
s32* levelGet_80345CB0(void);
void levelGet_80345CC0(f32* arg0, f32* arg1);
LevelCommObjects* levelLoadCommObj(u32 arg0);
void level_803462D4(u16 idx);
u8 levelGet_80346364(void);
s32 level_80346370(s32 terra);
u8 levelGet_80346468(void);
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
