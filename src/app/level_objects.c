#include "common.h"
#include <uv_graphics.h>
#include <uv_level.h>
#include <uv_math.h>
#include <uv_matrix.h>
#include <uv_memory.h>

typedef struct {
    s32 unk0[12];
    f32 unk30;
    f32 unk34;
    f32 unk38;
} Unk80345464_Arg0;

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
    void* dataNAME; // ptr NAME
    void* dataINFO; // ptr INFO
    void* dataJPTX; // ptr JPTX
    void* dataTHER; // ptr THER
    void* dataLWIN; // ptr LWIN
    void* dataTPAD; // ptr TPAD
    void* dataLPAD; // ptr LPAD
    void* dataLSTP; // ptr LSTP
    void* dataRNGS; // ptr RNGS
    void* dataBALS; // ptr BALS
    void* dataTARG; // ptr TARG
    void* dataHPAD; // ptr HPAD
    void* dataBTGT; // ptr BTGT
    void* dataPHTS; // ptr PHTS
    void* dataFALC; // ptr FALC
    void* dataSDFM; // ptr SDFM
    void* dataCNTG; // ptr CNTG
    void* dataHOPD; // ptr HOPD
    void* dataOBSV; // ptr OBSV
} Unk8037A600;

typedef struct {
    u8 unk0[0x22C];
    u8 unk22C;
} Unk80362690_Unk0_Unk7C; // this could be Unk8037A600

typedef struct {
    void* unk0;
    u16 unk4;
    u16 unk6;
    u8 unk8[0x6];
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
} Unk80362690;

typedef struct {
    void* unk0;
    void* unk4;
    u8 unk8;
    u8 pad9[0x3];
} Unk803798E0;

typedef struct {
    u8 unk0[0x30];
} Unk8037AA88;

extern f32 D_8034F850;

extern Unk8037A600* D_8035078C;
extern u8 gLevelClassU8;
extern u8 gLevelVehicleU8;
extern u8 gLevelTestU8;
extern u8 D_8035079C;
extern u8 D_803507A0;
extern u8 D_803507A4;
extern u8 D_803507A8[];
extern u8 D_803507AC[];

extern Unk80362690* D_80362690;

extern Unk803798E0 D_803798E0[MAX_CLASSES][MAX_TESTS][MAX_VEHICLES];

extern Unk8037A600 D_8037A600;

// begins 0x8037AA78
extern s32 gLevelClass;   // code refers "level" | Beg./A/B/Pilot | Bonus Level 1/2/3 | Birdman map
extern s32 gLevelTest;    // code refers "stage" | Test# within class | Birdman time-of-day
extern s32 gLevelVehicle; // vehicle selected
extern Unk8037AA88 D_8037AA88[];

s32 func_802314D0(s32, s32, s32);
void func_802CAD00(void);
void func_802CAF50(void);
void func_802CB094(void);
void func_802CB35C(void);
void func_802CB3F8(void);
void func_802D20F0(void);
void func_802D22B0(void);
void func_802D22D8(void);
void func_802D23EC(void);
void func_802D25AC(Unk80345464_Arg0*);
void func_802D27CC(void);
void func_802D2850(void);
void func_802D28D8(void);
void func_802D2ACC(void);
s32 func_802D2E48(void);
void func_802D3030(void);
void func_802E1278(void);
u16 func_802E12B4(void);
void func_802E15F0(void);
void func_802E344C(Unk80345464_Arg0*);
void func_802E37B0(void);
void func_802E3A5C(void);
void func_802E3E6C(void);
void func_802E3F7C(void);
void func_802EB424(Unk80345464_Arg0*, s32);
void func_802E79D8(void);
void func_802EB0BC(void);
void func_802EB3E0(void);
void func_802EB598(void);
void func_802EB5E4(void);
void func_802EDDEC(Unk80345464_Arg0*);
void func_802F1FA0(void);
void func_802FAF80(void);
void func_802FAFF0(void);
void func_802FB22C(void);
s32 func_802FB308(s32);
void func_802FB518(void);
void func_803097E0(void);
void func_80309868(void);
void func_80309A64(void);
void func_80309D64(Unk80345464_Arg0*);
void func_80309FFC(void);
void* func_80312740(s32);
void func_803127BC(void);
void func_80315474(void);
void func_80315550(void);
void func_80316DC0(void);
void func_80316E40(void);
void func_80317634(Unk80345464_Arg0*);
void func_8031776C(void);
void func_80320810(void);
void func_803232F0(void);
void func_80323364(void);
void func_803239B4(void);
s32 func_803243D8(Unk80345464_Arg0*);
void func_80324A34(void);
s32 func_8032C080(s32);
void func_8032FAB0(void);
void func_80335B94(void);
void func_80337DB8(void);
void func_803383FC(void);
void func_8033F748(s32);
void func_8033F964(s32);
void func_8033FCD0(u16);
void func_80344290(void);
void func_803442F8(void);
void func_8034450C(Unk80345464_Arg0*);
void func_8034467C(void);
void func_803453AC(void);
s32 func_803456D8(Unk80345464_Arg0*);
void func_80345A24(void);
Unk8037A600* func_80345CE4(u32 arg0);
u8 func_80346364(void);
s32 func_80346370(s32);
void func_803465F0(void);
void func_8034662C(void);
void func_8034695C(void);
void func_80346B84(void);
void func_8034C224(void);
void func_8034C848(void);
void func_8034CD60(void);
void func_8034D4AC(void);
void func_8034D548(void);
void uvChanTerra(u8, s32);
void wind_render(void);

void func_803449B0(void) {
    s32 classIdx, testIdx, vehIdx;
    Unk8037A600* temp_v0;
    Unk803798E0* temp_s0_2;
    s32 i;
    u8 sp88[0x28];
    u8 sp60[0x28];

    func_803465F0();
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
            for (vehIdx = 0; vehIdx < MAX_VEHICLES; vehIdx++) {
                D_803798E0[classIdx][testIdx][vehIdx].unk8 = 0xFF;
                D_803798E0[classIdx][testIdx][vehIdx].unk0 = 0;
                D_803798E0[classIdx][testIdx][vehIdx].unk4 = 0;
            }
        }
    }

    for (i = 0; i < 0x3D; i++) {
        temp_v0 = func_80345CE4(i);
        classIdx = temp_v0->comm.classNum;
        testIdx = temp_v0->comm.testNum;
        vehIdx = temp_v0->comm.vehNum;
        _uvMediaCopy(sp88, (void*)temp_v0->dataNAME, 0x28);
        if (classIdx >= MAX_CLASSES) {
            _uvDebugPrintf("\ntask : level index out of range - current limit %d\n", MAX_CLASSES - 1);
        }
        if (testIdx >= MAX_TESTS) {
            _uvDebugPrintf("\ntask : stage index out of range - current limit %d\n", MAX_TESTS - 1);
        }
        if (vehIdx >= MAX_VEHICLES) {
            _uvDebugPrintf("\ntask : vehicle index out of range - current limit %d\n", MAX_VEHICLES - 1);
        }
        temp_s0_2 = &D_803798E0[classIdx][testIdx][vehIdx];
        if (temp_s0_2->unk8 != 0xFF) {
            _uvMediaCopy(sp60, (void*)temp_s0_2->unk0, 0x28);
            _uvDebugPrintf("task : oops! redefining [%s] idx:%d veh:%d stage:%d lev:%d -> [%s]\n", sp60, temp_s0_2->unk8, vehIdx, (s32)testIdx, (s32)classIdx,
                           sp88);
        }
        temp_s0_2->unk8 = i;
        temp_s0_2->unk0 = temp_v0->dataNAME;
        temp_s0_2->unk4 = temp_v0->dataJPTX;
        if ((vehIdx == 6) && (testIdx == 0)) {
            _uvMediaCopy(&D_8037AA88[classIdx], (void*)temp_v0->dataTPAD, 0x30);
        }
    }
}

s32 func_80344CD0(s32 classIdx, s32 testIdx, s32 vehicle) {
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

s32 func_80344E0C(s32 classIdx, s32 testIdx, s32 vehicle, char* arg3, char* arg4) {
    u8 sp48[0x28];
    u8 sp20[0x28];
    Unk803798E0* sp18;

    sp18 = &D_803798E0[classIdx][testIdx][vehicle];
    if (sp18->unk8 == 0xFF) {
        return 0;
    }
    _uvMediaCopy(&sp48, (void*)sp18->unk0, 0x28);
    _uvMediaCopy(arg3, arg3, 0x28);
    _uvMediaCopy(&sp20, (void*)sp18->unk4, 0x28);
    _uvMediaCopy(arg4, &sp20, 0x28);
    strToUpper(arg3, 0x28);
    strToUpper(arg4, 0x28);
    return 1;
}

s32 func_80344EF0(s32 classIdx, s32 vehicle) {
    s32 testCount;
    s32 i;

    testCount = 0;
    if (classIdx > MAX_CLASSES) {
        return 0;
    }
    if (vehicle > MAX_VEHICLES) {
        return 0;
    }

    for (i = 0; i < MAX_TESTS; i++) {
        if (D_803798E0[classIdx][i][vehicle].unk8 != 0xFF) {
            testCount++;
        }
    }
    return testCount;
}

s32 func_80344FC8(s32 classIdx, s32 vehicle, s32 testIdx, u16* arg3, u16* arg4, u16* arg5) {
    u8 tmp8;

    gLevelClass = classIdx;
    gLevelVehicle = vehicle;
    gLevelTest = testIdx;

    if (classIdx > MAX_CLASSES) {
        return 0;
    }
    if (vehicle > MAX_VEHICLES) {
        return 0;
    }
    if (testIdx > MAX_TESTS) {
        return 0;
    }

    tmp8 = D_803798E0[classIdx][testIdx][vehicle].unk8;
    if (tmp8 == 0xFF) {
        return 0;
    }
    D_8035078C = func_80345CE4(tmp8);
    gLevelClassU8 = (u8)classIdx;
    gLevelVehicleU8 = (u8)vehicle;
    gLevelTestU8 = (u8)testIdx;

    *arg3 = D_803507A8[D_8035078C->comm.unk3];
    switch (*arg3) {
    case 3:
        *arg4 = 1;
        break;
    case 5:
        *arg4 = 3;
        break;
    case 1:
        *arg4 = 0;
        break;
    case 10:
        *arg4 = 7;
        break;
    default:
        _uvDebugPrintf("task load : unknown db level [%d]\n", *arg3);
        *arg3 = 3;
        *arg4 = 1;
        break;
    }

    func_803465F0();
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
    D_80362690->unk0[D_80362690->unk9C].unk14 = 0;
    *arg5 = func_802E12B4();
    return 1;
}

void func_8034528C(void) {
    u16 sp1E;

    sp1E = D_80362690->unk0[D_80362690->unk9C].unkE;
    D_8035079C = 1;
    wind_render();
    func_8034662C();
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

void func_8034536C(void) {
    func_803453AC();
    func_80346B84();
    func_8034D4AC();
    func_8031776C();
    func_802EB5E4();
}

void func_803453AC(void) {
    u16 sp1E;

    sp1E = D_80362690->unk0[D_80362690->unk9C].unkE;
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

s32 func_80345464(Unk80345464_Arg0* arg0, s32 arg1) {
    u16 sp1E;
    s32 sp18;
    s32 temp_v0;

    sp1E = D_80362690->unk0[D_80362690->unk9C].unkE;
    sp18 = 0;
    func_8034695C();
    func_8034D548();
    func_802E15F0();
    func_802CB3F8();
    func_802E3F7C();
    func_80317634(arg0);
    func_8034450C(arg0);
    func_80309D64(arg0);
    if ((sp1E != 3) && (sp1E != 4)) {
        func_802D25AC(arg0);
    }
    func_802EB424(arg0, arg1);
    func_802E344C(arg0);
    if (func_802D2E48() == 1) {
        D_803507A4 = 1;
        sp18 = 1;
        D_80362690->unk0[0].unkE = 1;
        if (D_80362690->unk0[0].unkE != 0) {
            func_8033F748(9);
            func_8033F964(0);
            func_8033FCD0(D_80362690->unk0[0].unkE);
        }
    }
    if (func_803243D8(arg0) == 1) {
        D_803507A4 = 1;
        sp18 = 1;
        D_80362690->unk0[0].unkE = 1;
        if (D_80362690->unk0[0].unkE != 0) {
            func_8033F748(9);
            func_8033F964(0);
            func_8033FCD0(D_80362690->unk0[0].unkE);
        }
    }
    if ((D_80362690->unk0[D_80362690->unk9C].unkE == 5) && (func_802FB308(D_80362690->unk0[D_80362690->unk9C].unk78) == 1)) {
        sp18 = 1;
    }
    temp_v0 = func_803456D8(arg0);
    switch (temp_v0) {
    case 1:
        func_80345A24();
        func_802EDDEC(arg0);
        break;
    case 2:
        func_802EDDEC(arg0);
        break;
    }
    if ((D_80362690->unkA0 != 0) && (func_80346364() == 3) && (func_8032C080(0) != 0)) {
        D_803507A0 = 1;
        func_803453AC();
        D_80362690->unkA0 = 0;
    }
    return sp18;
}

s32 func_803456D8(Unk80345464_Arg0* arg0) {
    LevelTPTS* sp8C;
    f32 temp_fv0;
    u8 temp_v0;
    u8 var_s1;
    u8 sp85;
    Vec3F_t sp78;
    Vec3F_t sp6C;
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
            sp6C.x = func_8022A080((temp_s0->unk10 + 90.0f) * 0.01745329f);
            sp6C.y = func_80229EC0((temp_s0->unk10 + 90.0f) * 0.01745329f);
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
    D_80362690->unk0[D_80362690->unk9C].unk14 = (u16)var_s2;
    temp_v0_2 = func_80346370(var_s2);
    temp_s0 = &sp8C[sp85];
    uvChanTerra(D_80362690->unk0[D_80362690->unk9C].unk7C->unk22C, temp_v0_2);
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

void func_80345A24(void) {
    u16 sp1E;

    sp1E = D_80362690->unk0[D_80362690->unk9C].unkE;
    func_80323364();
    if ((sp1E != 3) && (sp1E != 4)) {
        func_802D22D8();
    }
    func_802CAF50();
    func_80309868();
    func_802D28D8();
    func_802FAFF0();
}

u8 levelDataGetTHER(void** data) {
    *data = D_8035078C->dataTHER;
    return D_8035078C->comm.countTHER;
}

u8 levelDataGetLWIN(void** data) {
    *data = D_8035078C->dataLWIN;
    return D_8035078C->comm.countLWIN;
}

s32* func_80345AEC(void) {
    return &D_8035078C->comm.unk10;
}

u8 levelDataGetTPAD(void** data) {
    *data = D_8035078C->dataTPAD;
    return D_8035078C->comm.countTPAD;
}

u8 levelDataGetCNTG(void** data) {
    *data = D_8035078C->dataCNTG;
    return D_8035078C->comm.countCNTG;
}

u8 levelDataGetOBSV(void** data) {
    *data = D_8035078C->dataOBSV;
    return D_8035078C->comm.countOBSV;
}

// TODO: how is this different than levelGetLPAD from level.c?
u8 levelDataGetLPAD(void** data) {
    *data = D_8035078C->dataLPAD;
    return D_8035078C->comm.countLPAD;
}

u8 levelDataGetLSTP(void** data) {
    *data = D_8035078C->dataLSTP;
    return D_8035078C->comm.countLSTP;
}

u8 levelDataGetRNGS(void** data) {
    *data = D_8035078C->dataRNGS;
    return D_8035078C->comm.countRNGS;
}

u8 levelDataGetBALS(void** data) {
    *data = D_8035078C->dataBALS;
    return D_8035078C->comm.countBALS;
}

u8 levelDataGetTARG(void** data) {
    *data = D_8035078C->dataTARG;
    return D_8035078C->comm.countTARG;
}

u8 levelDataGetHPAD(void** data) {
    *data = D_8035078C->dataHPAD;
    return D_8035078C->comm.countHPAD;
}

u8 levelDataGetBTGT(void** data) {
    *data = D_8035078C->dataBTGT;
    return D_8035078C->comm.countBTGT;
}

u8 levelDataGetPHTS(void** data) {
    *data = D_8035078C->dataPHTS;
    return D_8035078C->comm.countPHTS;
}

u8 levelDataGetFALC(void** data) {
    if (data != NULL) {
        *data = D_8035078C->dataFALC;
    }
    return D_8035078C->comm.countFALC;
}

s32* func_80345C80(void) {
    return &D_8035078C->comm.unk48;
}

s32* func_80345C90(void) {
    return &D_8035078C->comm.unk2C;
}

f32 func_80345CA0(void) {
    return D_8035078C->comm.unk44;
}

s32* func_80345CB0(void) {
    return &D_8035078C->comm.unk8;
}

void func_80345CC0(f32* arg0, f32* arg1) {
    *arg0 = D_8035078C->comm.unk404;
    *arg1 = D_8035078C->comm.unk408;
}

Unk8037A600* func_80345CE4(u32 arg0) {
    s32 sp34;
    s32 sp30;
    u32 sp2C;
    u32 tag;
    void* sp24;
    Unk8037A600* dst;

    dst = &D_8037A600;
    sp34 = func_802314D0((s32)D_803507AC[arg0], 2, arg0);
    sp30 = func_80223E80(sp34);
    uvMemSet(&D_8037A600, 0, sizeof(D_8037A600));

    while ((tag = func_80223F7C(sp30, &sp2C, &sp24, 2)) != 0) {
        switch (tag) {
        case 'JPTX': // 0x4A505458
            dst->dataJPTX = sp24;
            break;
        case 'NAME': // 0x4E414D45
            dst->dataNAME = sp24;
            break;
        case 'INFO': // 0x494E464F
            dst->dataINFO = sp24;
            break;
        case 'COMM': // 0x434F4D4D
            _uvMediaCopy(&dst->comm, sp24, sizeof(dst->comm));
            func_803127BC();
            dst->dataTPAD = func_80312740(dst->comm.countTPAD * 0x30);
            dst->dataLPAD = func_80312740(dst->comm.countLPAD * 0x30);
            dst->dataLSTP = func_80312740(dst->comm.countLSTP * 0x24);
            dst->dataLWIN = func_80312740(dst->comm.countLWIN * 0x54);
            dst->dataRNGS = func_80312740(dst->comm.countRNGS * 0x84);
            dst->dataTHER = func_80312740(dst->comm.countTHER * 0x28);
            dst->dataBALS = func_80312740(dst->comm.countBALS * 0x68);
            dst->dataTARG = func_80312740(dst->comm.countTARG * 0x20);
            dst->dataHPAD = func_80312740(dst->comm.countHPAD * 0x40);
            dst->dataBTGT = func_80312740(dst->comm.countBTGT * 0x1C);
            dst->dataPHTS = func_80312740(dst->comm.countPHTS * 0x14);
            dst->dataFALC = func_80312740(dst->comm.countFALC * 0xAC);
            dst->dataCNTG = func_80312740(dst->comm.countCNTG * 0x1C);
            dst->dataSDFM = func_80312740(dst->comm.countSDFM * 0x4C);
            dst->dataHOPD = func_80312740(dst->comm.countHOPD * 0x20);
            dst->dataOBSV = func_80312740(dst->comm.countOBSV * 0x10);
            break;
        case 'THER': // 0x54484552
            _uvMediaCopy(dst->dataTHER, sp24, sp2C);
            break;
        case 'LWIN': // 0x4C57494E
            _uvMediaCopy(dst->dataLWIN, sp24, sp2C);
            break;
        case 'TPAD': // 0x54504144
            _uvMediaCopy(dst->dataTPAD, sp24, sp2C);
            break;
        case 'LPAD': // 0x4C504144
            _uvMediaCopy(dst->dataLPAD, sp24, sp2C);
            break;
        case 'LSTP': // 0x4C535450
            _uvMediaCopy(dst->dataLSTP, sp24, sp2C);
            break;
        case 'RNGS': // 0x524E4753
            _uvMediaCopy(dst->dataRNGS, sp24, sp2C);
            break;
        case 'BALS': // 0x42414C53
            _uvMediaCopy(dst->dataBALS, sp24, sp2C);
            break;
        case 'PHTS': // 0x50485453
            _uvMediaCopy(dst->dataPHTS, sp24, sp2C);
            break;
        case 'HOPD': // 0x484F5044
            _uvMediaCopy(dst->dataHOPD, sp24, sp2C);
            break;
        case 'TARG': // 0x54415247
            _uvMediaCopy(dst->dataTARG, sp24, sp2C);
            break;
        case 'HPAD': // 0x48504144
            _uvMediaCopy(dst->dataHPAD, sp24, sp2C);
            break;
        case 'BTGT': // 0x42544754
            _uvMediaCopy(dst->dataBTGT, sp24, sp2C);
            break;
        case 'FALC': // 0x46414C43
            _uvMediaCopy(dst->dataFALC, sp24, sp2C);
            break;
        case 'CNTG': // 0x434E5447
            _uvMediaCopy(dst->dataCNTG, sp24, sp2C);
            break;
        case 'SDFM': // 0x5344464D
            _uvMediaCopy(dst->dataSDFM, sp24, sp2C);
            break;
        case 'OBSV': // 0x4F425356
            _uvMediaCopy(dst->dataOBSV, sp24, sp2C);
            break;
        }
    }
    func_80223F30(sp30);
    return &D_8037A600;
}

void func_803462D4(u16 idx) {
    Unk8037AA88* src;
    if (idx > 3) {
        _uvDebugPrintf("task_birdpad : level out of valid range [%d] - set to 0\n", idx);
        idx = 0;
    }
    src = &D_8037AA88[idx];
    _uvMediaCopy((void*)D_8035078C->dataTPAD, src, 0x30);
}

void func_8034633C(s16* classIdx, s16* vehIdx, s16* testIdx) {
    *classIdx = (s16)gLevelClass;
    *vehIdx = (s16)gLevelVehicle;
    *testIdx = (s16)gLevelTest;
}

u8 func_80346364(void) {
    return D_8037A600.comm.unk4;
}

// func_80346370 does not initialize the return value `ret`
#if defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsometimes-uninitialized"
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif
s32 func_80346370(s32 arg0) {
    s32 ret;
    switch (D_80362690->unk0[0].unk4) {
    case 3:
        switch (arg0) {
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
            _uvDebugPrintf("task : unknown CISLAND terra selection [%d]\n", arg0);
            break;
        }
        break;
    case 5:
        ret = 3;
        break;
    case 1:
        ret = 0;
        break;
    case 10:
        switch (arg0) {
        case 0:
            ret = 7;
            break;
        case 1:
            ret = 8;
            break;
        default:
            _uvDebugPrintf("task : unknown ARCTIC level terra selection [%d]\n", arg0);
            break;
        }
        break;
    default:
        _uvDebugPrintf("task : unknown level for terra selection [%d]\n", D_80362690->unk0[0].unk4);
        break;
    }
    return ret;
}
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif

u8 func_80346468(void) {
    return D_803507A4;
}

u8 levelDataGetHOPD(void** data) {
    *data = D_8035078C->dataHOPD;
    return D_8035078C->comm.countHOPD;
}
