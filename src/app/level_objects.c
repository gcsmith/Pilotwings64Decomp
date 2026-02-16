#include "common.h"
#include <uv_filesystem.h>
#include <uv_graphics.h>
#include <uv_level.h>
#include <uv_math.h>
#include <uv_matrix.h>
#include <uv_memory.h>
#include "code_58E0.h"
#include "code_52230.h"
#include "code_58B00.h"
#include "code_597E0.h"
#include "code_59D80.h"
#include "code_68220.h"
#include "code_69BF0.h"
#include "code_6ACE0.h"
#include "code_6ECD0.h"
#include "code_722D0.h"
#include "code_72910.h"
#include "code_72B70.h"
#include "code_78620.h"
#include "code_81490.h"
#include "code_82520.h"
#include "code_905C0.h"
#include "code_9A960.h"
#include "code_9C080.h"
#include "code_A7460.h"
#include "code_B2900.h"
#include "code_B6FE0.h"
#include "code_BB820.h"
#include "code_CB7C0.h"
#include "code_D2D50.h"
#include "code_D3810.h"
#include "code_D4290.h"
#include "mem.h"
#include "pads.h"
#include "rings.h"
#include "snap.h"
#include "snd.h"
#include "thermals.h"

typedef struct {
    void* unk0;
    void* unk4;
    u8 unk8;
    u8 pad9[0x3];
} Unk803798E0;

typedef struct {
    u8 unk0[0x30];
} Unk8037AA88;

extern LevelCommObjects* D_8035078C;
extern u8 gLevelClassU8;
extern u8 gLevelVehicleU8;
extern u8 gLevelTestU8;
extern u8 D_8035079C;
extern u8 D_803507A0;
extern u8 D_803507A4;
extern u8 gMapLookup[];
extern u8 D_803507AC[];

extern Unk803798E0 D_803798E0[MAX_CLASSES][MAX_TESTS][VEHICLE_COUNT];

extern LevelCommObjects gLevelCommObjs;

// begins 0x8037AA78
extern s32 gLevelClass;   // code refers "level" | Beg./A/B/Pilot | Bonus Level 1/2/3 | Birdman map
extern s32 gLevelTest;    // code refers "stage" | Test# within class | Birdman time-of-day
extern s32 gLevelVehicle; // vehicle selected
extern Unk8037AA88 D_8037AA88[];

void level_803449B0(void) {
    s32 classIdx, testIdx, vehIdx;
    LevelCommObjects* obj;
    Unk803798E0* temp_s0_2;
    s32 i;
    u8 sp88[0x28];
    u8 sp60[0x28];

    thermInit();
    func_803232F0();
    func_8034CD60();
    func_802D22B0();
    func_802CAD00();
    func_80316DC0();
    func_80344290();
    func_803097E0();
    func_802D2850();
    func_80337DB8();
    func_802E37B0();
    func_802EB3E0();
    func_8032FAB0();
    func_802FAF80();
    func_80335B94();
    func_802E79D8();
    func_802EB0BC();
    func_80315474();
    func_8034C224();
    func_80315550();
    func_802F1FA0();
    func_802D20F0();
    func_80320810();
    func_8034C848();

    for (classIdx = 0; classIdx < MAX_CLASSES; classIdx++) {
        for (testIdx = 0; testIdx < MAX_TESTS; testIdx++) {
            for (vehIdx = 0; vehIdx < VEHICLE_COUNT; vehIdx++) {
                D_803798E0[classIdx][testIdx][vehIdx].unk8 = 0xFF;
                D_803798E0[classIdx][testIdx][vehIdx].unk0 = 0;
                D_803798E0[classIdx][testIdx][vehIdx].unk4 = 0;
            }
        }
    }

    for (i = 0; i < 0x3D; i++) {
        obj = levelLoadCommObj(i);
        classIdx = obj->comm.classNum;
        testIdx = obj->comm.testNum;
        vehIdx = obj->comm.vehNum;
        _uvMediaCopy(sp88, (void*)obj->dataNAME, 0x28);
        if (classIdx >= MAX_CLASSES) {
            _uvDebugPrintf("\ntask : level index out of range - current limit %d\n", MAX_CLASSES - 1);
        }
        if (testIdx >= MAX_TESTS) {
            _uvDebugPrintf("\ntask : stage index out of range - current limit %d\n", MAX_TESTS - 1);
        }
        if (vehIdx >= VEHICLE_COUNT) {
            _uvDebugPrintf("\ntask : vehicle index out of range - current limit %d\n", VEHICLE_COUNT - 1);
        }
        temp_s0_2 = &D_803798E0[classIdx][testIdx][vehIdx];
        if (temp_s0_2->unk8 != 0xFF) {
            _uvMediaCopy(sp60, (void*)temp_s0_2->unk0, 0x28);
            _uvDebugPrintf("task : oops! redefining [%s] idx:%d veh:%d stage:%d lev:%d -> [%s]\n", sp60, temp_s0_2->unk8, vehIdx, (s32)testIdx, (s32)classIdx,
                           sp88);
        }
        temp_s0_2->unk8 = i;
        temp_s0_2->unk0 = obj->dataNAME;
        temp_s0_2->unk4 = obj->dataJPTX;
        if ((vehIdx == 6) && (testIdx == 0)) {
            _uvMediaCopy(&D_8037AA88[classIdx], (void*)obj->dataTPAD, 0x30);
        }
    }
}

s32 levelIsValidIndex(s32 classIdx, s32 testIdx, s32 vehicle) {
    if (D_803798E0[classIdx][testIdx][vehicle].unk8 == 0xFF) {
        return 0;
    }
    return 1;
}

// performs toupper() on an array of characters
void strToUpper(char* str, s32 length) {
    int i;

    for (i = 0; i < length; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - ('a' - 'A');
        }
    }
}

s32 level_80344E0C(s32 classIdx, s32 testIdx, s32 vehicle, char* arg3, char* arg4) {
    u8 sp48[0x28];
    u8 sp20[0x28];
    Unk803798E0* sp18;

    sp18 = &D_803798E0[classIdx][testIdx][vehicle];
    if (sp18->unk8 == 0xFF) {
        return 0;
    }
    _uvMediaCopy(&sp48, (void*)sp18->unk0, sizeof(sp48));
    _uvMediaCopy(arg3, arg3, sizeof(sp48));
    _uvMediaCopy(&sp20, (void*)sp18->unk4, sizeof(sp20));
    _uvMediaCopy(arg4, &sp20, sizeof(sp20));
    strToUpper(arg3, 0x28);
    strToUpper(arg4, 0x28);
    return 1;
}

s32 levelGetTestCount(s32 classIdx, s32 vehicle) {
    s32 testCount;
    s32 i;

    testCount = 0;
    if (classIdx > MAX_CLASSES) {
        return 0;
    }
    if (vehicle > VEHICLE_COUNT) {
        return 0;
    }

    for (i = 0; i < MAX_TESTS; i++) {
        if (D_803798E0[classIdx][i][vehicle].unk8 != 0xFF) {
            testCount++;
        }
    }
    return testCount;
}

s32 level_80344FC8(s32 classIdx, s32 vehicle, s32 testIdx, u16* map, u16* arg4, u16* arg5) {
    u8 tmp8;

    gLevelClass = classIdx;
    gLevelVehicle = vehicle;
    gLevelTest = testIdx;

    if (classIdx > MAX_CLASSES) {
        return 0;
    }
    if (vehicle > VEHICLE_COUNT) {
        return 0;
    }
    if (testIdx > MAX_TESTS) {
        return 0;
    }

    tmp8 = D_803798E0[classIdx][testIdx][vehicle].unk8;
    if (tmp8 == 0xFF) {
        return 0;
    }
    D_8035078C = levelLoadCommObj(tmp8);
    gLevelClassU8 = (u8)classIdx;
    gLevelVehicleU8 = (u8)vehicle;
    gLevelTestU8 = (u8)testIdx;

    *map = gMapLookup[D_8035078C->comm.unk3];
    switch (*map) {
    case MAP_CRESCENT_ISLAND:
        *arg4 = 1;
        break;
    case MAP_LITTLE_STATES:
        *arg4 = 3;
        break;
    case MAP_HOLIDAY_ISLAND:
        *arg4 = 0;
        break;
    case MAP_EVER_FROST_ISLAND:
        *arg4 = 7;
        break;
    default:
        _uvDebugPrintf("task load : unknown db level [%d]\n", *map);
        *map = 3;
        *arg4 = 1;
        break;
    }

    thermInit();
    func_803232F0();
    func_8034CD60();
    func_802D22B0();
    func_802CAD00();
    func_80316DC0();
    func_80344290();
    func_803097E0();
    func_802D2850();
    func_80337DB8();
    func_802E37B0();
    func_8032FAB0();
    func_802EB3E0();
    func_802FAF80();
    func_802E79D8();
    func_802EB0BC();
    func_80335B94();
    func_80315474();
    func_80315550();
    func_8034C224();
    func_802F1FA0();
    func_802D20F0();
    func_80320810();
    func_8034C848();
    D_8035079C = 1;
    D_803507A0 = 0;
    D_80362690->unk0[D_80362690->unk9C].unkC.unk8 = 0;
    *arg5 = func_802E12B4();
    return 1;
}

void level_8034528C(void) {
    u16 sp1E;

    sp1E = D_80362690->unk0[D_80362690->unk9C].unkC.unk2;
    D_8035079C = 1;
    wind_render();
    therm_8034662C();
    func_80316E40();
    func_802E1278();
    func_802EB598();
    if (D_803507A0 == 0) {
        func_803239B4();
        func_802CB094();
        func_803442F8();
        func_80309A64();
        func_802D2ACC();
        func_802E3A5C();
        func_802FB22C();
        if ((sp1E != 3) && (sp1E != 4)) {
            func_802D23EC();
        }
    }
    D_803507A4 = 0;
}

void level_8034536C(void) {
    level_803453AC();
    therm_80346B84();
    func_8034D4AC();
    func_8031776C();
    func_802EB5E4();
}

void level_803453AC(void) {
    u16 sp1E;

    sp1E = D_80362690->unk0[D_80362690->unk9C].unkC.unk2;
    if (D_8035079C != 0) {
        func_80324A34();
        func_802CB35C();
        func_8034467C();
        func_80309FFC();
        func_802D3030();
        func_803383FC();
        func_802E3E6C();
        func_802FB518();
        if ((sp1E != 3) && (sp1E != 4)) {
            func_802D27CC();
        }
        D_8035079C = 0;
    }
}

s32 level_80345464(Unk80345464_Arg0* arg0, s32 arg1) {
    u16 sp1E;
    s32 sp18;
    s32 temp_v0;

    sp1E = D_80362690->unk0[D_80362690->unk9C].unkC.unk2;
    sp18 = 0;
    therm_8034695C();
    func_8034D548();
    func_802E15F0();
    func_802CB3F8();
    func_802E3F7C();
    func_80317634(arg0);
    func_8034450C(arg0);
    func_80309D64(arg0);
    if ((sp1E != 3) && (sp1E != 4)) {
        bonusStar_802D25AC(arg0);
    }
    func_802EB424(arg0, arg1);
    func_802E344C(arg0);
    if (func_802D2E48() == 1) {
        D_803507A4 = 1;
        sp18 = 1;
        D_80362690->unk0[0].unkC.unk2 = 1;
        if (D_80362690->unk0[0].unkC.unk2 != 0) {
            func_8033F748(9);
            func_8033F964(0);
            func_8033FCD0(D_80362690->unk0[0].unkC.unk2);
        }
    }
    if (func_803243D8(arg0) == 1) {
        D_803507A4 = 1;
        sp18 = 1;
        D_80362690->unk0[0].unkC.unk2 = 1;
        if (D_80362690->unk0[0].unkC.unk2 != 0) {
            func_8033F748(9);
            func_8033F964(0);
            func_8033FCD0(D_80362690->unk0[0].unkC.unk2);
        }
    }
    if ((D_80362690->unk0[D_80362690->unk9C].unkC.unk2 == 5) && (func_802FB308(D_80362690->unk0[D_80362690->unk9C].unkC.unk6C) == 1)) {
        sp18 = 1;
    }
    temp_v0 = level_803456D8(arg0);
    switch (temp_v0) {
    case 1:
        level_80345A24();
        func_802EDDEC(arg0);
        break;
    case 2:
        func_802EDDEC(arg0);
        break;
    }
    if ((D_80362690->unkA0 != 0) && (levelGet_80346364() == 3) && (func_8032C080(0) != 0)) {
        D_803507A0 = 1;
        level_803453AC();
        D_80362690->unkA0 = 0;
    }
    return sp18;
}

s32 level_803456D8(Unk80345464_Arg0* arg0) {
    LevelTPTS* sp8C;
    f32 temp_fv0;
    u8 temp_v0;
    u8 var_s1;
    u8 sp85;
    Vec3F sp78;
    Vec3F sp6C;
    f32 temp_fv1;
    s32 temp_v0_2;
    s32 var_s2;
    LevelTPTS* temp_s0;

    var_s2 = -1;
    temp_v0 = levelGetTPTS(&sp8C);
    if (temp_v0 == 0) {
        return 0;
    }

    for (var_s1 = 0; var_s1 < temp_v0; var_s1++) {
        temp_s0 = &sp8C[var_s1];
        sp78.x = arg0->unk30 - temp_s0->unk4_X;
        sp78.y = arg0->unk34 - temp_s0->unk8_Y;
        sp78.z = arg0->unk38 - temp_s0->unkC_Z;
        if (uvVec3Len(&sp78) <= temp_s0->unk14) {
            sp6C.x = uvCosF((temp_s0->unk10 + 90.0f) * 0.01745329f);
            sp6C.y = uvSinF((temp_s0->unk10 + 90.0f) * 0.01745329f);
            sp6C.z = 0.0f;
            temp_fv0 = uvVec3Dot(&sp6C, &sp78);
            if (temp_fv0 > 0.0f) {
                temp_s0->unk1C = D_8034F850;
            } else {
                temp_s0->unk24 = D_8034F850;
            }
            if (temp_s0->unk0 == 0) {
                if (temp_fv0 > 0.0f) {
                    var_s2 = temp_s0->unk18;
                } else {
                    var_s2 = temp_s0->unk20;
                }
                sp85 = var_s1;
            } else {
                temp_fv1 = temp_s0->unk1C;
                if (temp_fv1 > 0.0f) {
                    if ((temp_s0->unk24 > 0.0f) && (temp_s0->unk24 < temp_fv1)) {
                        if (temp_fv0 > 0.0f) {
                            var_s2 = temp_s0->unk18;
                        } else {
                            var_s2 = temp_s0->unk20;
                        }
                        sp85 = var_s1;
                    }
                }
            }
        } else {
            temp_s0->unk24 = 0.0f;
            temp_s0->unk1C = 0.0f;
        }
    }
    if (var_s2 == -1) {
        return 0;
    }
    D_80362690->unk0[D_80362690->unk9C].unkC.unk8 = (u16)var_s2;
    temp_v0_2 = level_80346370(var_s2);
    temp_s0 = &sp8C[sp85];
    uvChanTerra(D_80362690->unk0[D_80362690->unk9C].unkC.unk70->unk22C, temp_v0_2);
    if (temp_v0_2 != D_80362690->unk0[0].unk6) {
        D_80362690->unk0[0].unk6 = (u16)temp_v0_2;
        arg0->unk30 = arg0->unk30 + temp_s0->unk28_X;
        arg0->unk34 = arg0->unk34 + temp_s0->unk2C_Y;
        arg0->unk38 = arg0->unk38 + temp_s0->unk30_Z;
        return 1;
    }
    if ((temp_s0->unk18 == -1) || (temp_s0->unk20 == -1)) {
        arg0->unk30 = arg0->unk30 + temp_s0->unk28_X;
        arg0->unk34 = arg0->unk34 + temp_s0->unk2C_Y;
        arg0->unk38 = arg0->unk38 + temp_s0->unk30_Z;
        return 2;
    }
    return 0;
}

void level_80345A24(void) {
    u16 sp1E;

    sp1E = D_80362690->unk0[D_80362690->unk9C].unkC.unk2;
    func_80323364();
    if ((sp1E != 3) && (sp1E != 4)) {
        func_802D22D8();
    }
    func_802CAF50();
    func_80309868();
    func_802D28D8();
    func_802FAFF0();
}

s32 levelDataGetTHER(LevelTHER** data) {
    *data = D_8035078C->dataTHER;
    return D_8035078C->comm.countTHER;
}

s32 levelDataGetLWIN(void** data) {
    *data = D_8035078C->dataLWIN;
    return D_8035078C->comm.countLWIN;
}

s32* func_80345AEC(void) {
    return &D_8035078C->comm.unk10;
}

s32 levelDataGetTPAD(void** data) {
    *data = D_8035078C->dataTPAD;
    return D_8035078C->comm.countTPAD;
}

s32 levelDataGetCNTG(void** data) {
    *data = D_8035078C->dataCNTG;
    return D_8035078C->comm.countCNTG;
}

s32 levelDataGetOBSV(LevelOBSV** data) {
    *data = D_8035078C->dataOBSV;
    return D_8035078C->comm.countOBSV;
}

// TODO: how is this different than levelGetLPAD from level.c?
s32 levelDataGetLPAD(void** data) {
    *data = D_8035078C->dataLPAD;
    return D_8035078C->comm.countLPAD;
}

s32 levelDataGetLSTP(void** data) {
    *data = D_8035078C->dataLSTP;
    return D_8035078C->comm.countLSTP;
}

s32 levelDataGetRNGS(void** data) {
    *data = D_8035078C->dataRNGS;
    return D_8035078C->comm.countRNGS;
}

s32 levelDataGetBALS(void** data) {
    *data = D_8035078C->dataBALS;
    return D_8035078C->comm.countBALS;
}

s32 levelDataGetTARG(void** data) {
    *data = D_8035078C->dataTARG;
    return D_8035078C->comm.countTARG;
}

s32 levelDataGetHPAD(void** data) {
    *data = D_8035078C->dataHPAD;
    return D_8035078C->comm.countHPAD;
}

s32 levelDataGetBTGT(LevelBTGT** data) {
    *data = D_8035078C->dataBTGT;
    return D_8035078C->comm.countBTGT;
}

s32 levelDataGetPHTS(void** data) {
    *data = D_8035078C->dataPHTS;
    return D_8035078C->comm.countPHTS;
}

s32 levelDataGetFALC(void** data) {
    if (data != NULL) {
        *data = D_8035078C->dataFALC;
    }
    return D_8035078C->comm.countFALC;
}

s32* levelGet_80345C80(void) {
    return &D_8035078C->comm.unk48;
}

s32* levelGet_80345C90(void) {
    return &D_8035078C->comm.unk2C;
}

f32 levelGet_80345CA0(void) {
    return D_8035078C->comm.unk44;
}

s32* levelGet_80345CB0(void) {
    return &D_8035078C->comm.unk8;
}

void levelGet_80345CC0(f32* arg0, f32* arg1) {
    *arg0 = D_8035078C->comm.unk404;
    *arg1 = D_8035078C->comm.unk408;
}

LevelCommObjects* levelLoadCommObj(u32 arg0) {
    void* sp34;
    s32 idx;
    u32 size;
    u32 tag;
    void* data;
    LevelCommObjects* dst;

    dst = &gLevelCommObjs;
    sp34 = func_802314D0(D_803507AC[arg0], 2);
    idx = uvFileReadHeader((s32)sp34);
    uvMemSet(&gLevelCommObjs, 0, sizeof(gLevelCommObjs));

    while ((tag = uvFileReadBlock(idx, &size, &data, 2)) != 0) {
        switch (tag) {
        case 'JPTX': // 0x4A505458
            dst->dataJPTX = data;
            break;
        case 'NAME': // 0x4E414D45
            dst->dataNAME = data;
            break;
        case 'INFO': // 0x494E464F
            dst->dataINFO = data;
            break;
        case 'COMM': // 0x434F4D4D
            _uvMediaCopy(&dst->comm, data, sizeof(dst->comm));
            mem_init();
            dst->dataTPAD = mem_get(dst->comm.countTPAD * 0x30);
            dst->dataLPAD = mem_get(dst->comm.countLPAD * 0x30);
            dst->dataLSTP = mem_get(dst->comm.countLSTP * 0x24);
            dst->dataLWIN = mem_get(dst->comm.countLWIN * 0x54);
            dst->dataRNGS = mem_get(dst->comm.countRNGS * 0x84);
            dst->dataTHER = mem_get(dst->comm.countTHER * sizeof(LevelTHER));
            dst->dataBALS = mem_get(dst->comm.countBALS * 0x68);
            dst->dataTARG = mem_get(dst->comm.countTARG * 0x20);
            dst->dataHPAD = mem_get(dst->comm.countHPAD * 0x40);
            dst->dataBTGT = mem_get(dst->comm.countBTGT * 0x1C);
            dst->dataPHTS = mem_get(dst->comm.countPHTS * 0x14);
            dst->dataFALC = mem_get(dst->comm.countFALC * 0xAC);
            dst->dataCNTG = mem_get(dst->comm.countCNTG * 0x1C);
            dst->dataSDFM = mem_get(dst->comm.countSDFM * 0x4C);
            dst->dataHOPD = mem_get(dst->comm.countHOPD * 0x20);
            dst->dataOBSV = mem_get(dst->comm.countOBSV * sizeof(LevelOBSV));
            break;
        case 'THER': // 0x54484552
            _uvMediaCopy(dst->dataTHER, data, size);
            break;
        case 'LWIN': // 0x4C57494E
            _uvMediaCopy(dst->dataLWIN, data, size);
            break;
        case 'TPAD': // 0x54504144
            _uvMediaCopy(dst->dataTPAD, data, size);
            break;
        case 'LPAD': // 0x4C504144
            _uvMediaCopy(dst->dataLPAD, data, size);
            break;
        case 'LSTP': // 0x4C535450
            _uvMediaCopy(dst->dataLSTP, data, size);
            break;
        case 'RNGS': // 0x524E4753
            _uvMediaCopy(dst->dataRNGS, data, size);
            break;
        case 'BALS': // 0x42414C53
            _uvMediaCopy(dst->dataBALS, data, size);
            break;
        case 'PHTS': // 0x50485453
            _uvMediaCopy(dst->dataPHTS, data, size);
            break;
        case 'HOPD': // 0x484F5044
            _uvMediaCopy(dst->dataHOPD, data, size);
            break;
        case 'TARG': // 0x54415247
            _uvMediaCopy(dst->dataTARG, data, size);
            break;
        case 'HPAD': // 0x48504144
            _uvMediaCopy(dst->dataHPAD, data, size);
            break;
        case 'BTGT': // 0x42544754
            _uvMediaCopy(dst->dataBTGT, data, size);
            break;
        case 'FALC': // 0x46414C43
            _uvMediaCopy(dst->dataFALC, data, size);
            break;
        case 'CNTG': // 0x434E5447
            _uvMediaCopy(dst->dataCNTG, data, size);
            break;
        case 'SDFM': // 0x5344464D
            _uvMediaCopy(dst->dataSDFM, data, size);
            break;
        case 'OBSV': // 0x4F425356
            _uvMediaCopy(dst->dataOBSV, data, size);
            break;
        }
    }
    uvFile_80223F30(idx);
    return &gLevelCommObjs;
}

void level_803462D4(u16 idx) {
    Unk8037AA88* src;
    if (idx > 3) {
        _uvDebugPrintf("task_birdpad : level out of valid range [%d] - set to 0\n", idx);
        idx = 0;
    }
    src = &D_8037AA88[idx];
    _uvMediaCopy((void*)D_8035078C->dataTPAD, src, 0x30);
}

void levelGetClsVehTest(s16* classIdx, s16* vehIdx, s16* testIdx) {
    *classIdx = (s16)gLevelClass;
    *vehIdx = (s16)gLevelVehicle;
    *testIdx = (s16)gLevelTest;
}

u8 levelGet_80346364(void) {
    return gLevelCommObjs.comm.unk4;
}

// level_80346370 does not initialize the return value `ret`
#if defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsometimes-uninitialized"
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif
s32 level_80346370(s32 terra) {
    s32 ret;
    switch (D_80362690->unk0[0].map) {
    case MAP_CRESCENT_ISLAND:
        switch (terra) {
        case 0:
            ret = 1;
            break;
        case 1:
            ret = 2;
            break;
        case 2:
            ret = 7;
            break;
        default:
            _uvDebugPrintf("task : unknown CISLAND terra selection [%d]\n", terra);
            break;
        }
        break;
    case MAP_LITTLE_STATES:
        ret = 3;
        break;
    case MAP_HOLIDAY_ISLAND:
        ret = 0;
        break;
    case MAP_EVER_FROST_ISLAND:
        switch (terra) {
        case 0:
            ret = 7;
            break;
        case 1:
            ret = 8;
            break;
        default:
            _uvDebugPrintf("task : unknown ARCTIC level terra selection [%d]\n", terra);
            break;
        }
        break;
    default:
        _uvDebugPrintf("task : unknown level for terra selection [%d]\n", D_80362690->unk0[0].map);
        break;
    }
    return ret;
}
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif

u8 levelGet_80346468(void) {
    return D_803507A4;
}

s32 levelDataGetHOPD(LevelHOPD** data) {
    *data = D_8035078C->dataHOPD;
    return D_8035078C->comm.countHOPD;
}
