#include "common.h"
#include <uv_filesystem.h>
#include <uv_graphics.h>
#include <uv_level.h>
#include <uv_memory.h>
#include <uv_util.h>
#include "code_58B00.h"
#include "code_68220.h"
#include "code_69BF0.h"
#include "code_6ECD0.h"
#include "code_722D0.h"
#include "code_78620.h"
#include "code_9C080.h"
#include "code_9CF50.h"
#include "code_A7460.h"
#include "code_BB820.h"
#include "code_BD670.h"
#include "code_CE4F0.h"
#include "code_D2D50.h"
#include "code_D3810.h"
#include "text_data.h"

typedef struct {
    s32 unk0;
} Unk8034F410;

extern s32 D_8034F400;
extern s32 D_8034F404;
extern LevelObjects* D_8034F408;
extern s32 gLevelCurMap;
extern Unk8034F410 D_8034F410[];

// likely arrays of structs for level data
extern s32 gLevelWOBJ;
extern s32 gLevelLPAD;
extern LevelTPTS gLevelTPTS;
extern LevelTOYS gLevelTOYS;
extern s32 gLevelAPTS;
extern s32 gLevelBNUS;
extern LevelObjects gLevelObjects;

void levelLoad(u8 map, u8 pilot, u8 vehicle, s32 animateToys) {
    s32 i;

    gLevelCurMap = map;
    uvLevelInit();
    textLoadBlock(0x42);
    env_loadtpal(D_80362690->unk0[0].unk8);
    uvLevelAppend(map);
    switch (map) {
    case MAP_HOLIDAY_ISLAND:
        D_8034F408 = levelLoadMapObjects(0);
        break;
    case MAP_CRESCENT_ISLAND:
        D_8034F408 = levelLoadMapObjects(1);
        break;
    case MAP_LITTLE_STATES:
        D_8034F408 = levelLoadMapObjects(2);
        break;
    case MAP_EVER_FROST_ISLAND:
        D_8034F408 = levelLoadMapObjects(3);
        break;
    }
    uvLevelAppend(0x1A);
    if (animateToys) {
        for (i = 0; i < (s32)gLevelObjects.countTOYS; i++) {
            func_80348280(&gLevelObjects.dataTOYS[i]);
        }
        D_8034F400 = 1;
    } else {
        D_8034F400 = 0;
    }
    if ((vehicle == VEHICLE_HANG_GLIDER) || (vehicle == VEHICLE_BIRDMAN)) {
        uvLevelAppend(0x1B);
    }
    levelComputeAppend(pilot, vehicle);
    uvLevelAppend(0xC);
    uvLevelAppend(0xD);
    uvLevelAppend(0x2E);
    func_802E1444(D_80362690->unk0[0].unk8);
    if (animateToys != 0) {
        level_8030B868();
    }
}

void level_8030B868(void) {
    if (D_8034F404 == 0) {
        if (1) { // fakematch
            D_8034F404 = 1;
        }
        switch (gLevelCurMap) {
        case MAP_HOLIDAY_ISLAND:
            func_802F1AE8();
            func_802D1CE8();
            break;
        case MAP_CRESCENT_ISLAND:
            func_8034BEDC();
            func_802EB0D4();
            func_802D1A74();
            func_802F15C8();
            break;
        case MAP_LITTLE_STATES:
            func_80335BE4();
            func_802E79F0();
            func_803151AC();
            func_802F182C();
            func_80320534();
            break;
        case MAP_EVER_FROST_ISLAND:
            func_80315D68();
            func_80315734();
            func_803363E0();
            func_802F1D3C();
            func_8034C964();
            break;
        }
    }
}

void level_8030B964(void) {
    if (D_8034F404 != 0) {
        if (1) { // fakematch
            D_8034F404 = 0;
        }
        switch (gLevelCurMap) {
        case MAP_HOLIDAY_ISLAND:
            func_802F1FF0();
            func_802D206C();
            break;
        case MAP_CRESCENT_ISLAND:
            func_8034C0BC();
            func_802EB270();
            func_802D206C();
            func_802F1FF0();
            break;
        case MAP_LITTLE_STATES:
            func_80335E44();
            func_802E7C28();
            func_8031531C();
            func_802F1FF0();
            func_8032079C();
            break;
        case MAP_EVER_FROST_ISLAND:
            func_80315E3C();
            func_8031596C();
            func_8033651C();
            func_802F1FF0();
            func_8034CB80();
            break;
        }
    }
}

void level_8030BA60(void) {
    if (D_8034F400 != 0) {
        func_803483AC();
        level_8030B964();
    }
}

void levelComputeAppend(u8 pilot, u8 vehicle) {
    s32 var_a2;

    var_a2 = -1;
    // clang-format off: compress switch statements
    switch (pilot) {
    case PILOT_LARK:
        switch (vehicle) {
        case VEHICLE_HANG_GLIDER:   var_a2 = 0x1C; break;
        case VEHICLE_ROCKET_BELT:   var_a2 = 0x22; break;
        case VEHICLE_GYROCOPTER:    var_a2 = 0x28; break;
        case VEHICLE_CANNONBALL:    var_a2 = 0x2F; break;
        case VEHICLE_SKY_DIVING:    var_a2 = 0x3B; break;
        case VEHICLE_BIRDMAN:       var_a2 = 0x35; break;
        case VEHICLE_JUMBLE_HOPPER: var_a2 = 0x41; break;
        }
        break;
    case PILOT_GOOSE:
        switch (vehicle) {
        case VEHICLE_HANG_GLIDER:   var_a2 = 0x1D; break;
        case VEHICLE_ROCKET_BELT:   var_a2 = 0x23; break;
        case VEHICLE_GYROCOPTER:    var_a2 = 0x29; break;
        case VEHICLE_CANNONBALL:    var_a2 = 0x30; break;
        case VEHICLE_SKY_DIVING:    var_a2 = 0x3C; break;
        case VEHICLE_BIRDMAN:       var_a2 = 0x36; break;
        case VEHICLE_JUMBLE_HOPPER: var_a2 = 0x42; break;
        }
        break;
    case PILOT_HAWK:
        switch (vehicle) {
        case VEHICLE_HANG_GLIDER:   var_a2 = 0x1E; break;
        case VEHICLE_ROCKET_BELT:   var_a2 = 0x24; break;
        case VEHICLE_GYROCOPTER:    var_a2 = 0x2A; break;
        case VEHICLE_CANNONBALL:    var_a2 = 0x31; break;
        case VEHICLE_SKY_DIVING:    var_a2 = 0x3D; break;
        case VEHICLE_BIRDMAN:       var_a2 = 0x37; break;
        case VEHICLE_JUMBLE_HOPPER: var_a2 = 0x43; break;
        }
        break;
    case PILOT_KIWI:
        switch (vehicle) {
        case VEHICLE_HANG_GLIDER:   var_a2 = 0x1F; break;
        case VEHICLE_ROCKET_BELT:   var_a2 = 0x25; break;
        case VEHICLE_GYROCOPTER:    var_a2 = 0x2B; break;
        case VEHICLE_CANNONBALL:    var_a2 = 0x32; break;
        case VEHICLE_SKY_DIVING:    var_a2 = 0x3E; break;
        case VEHICLE_BIRDMAN:       var_a2 = 0x38; break;
        case VEHICLE_JUMBLE_HOPPER: var_a2 = 0x44; break;
        }
        break;
    case PILOT_IBIS:
        switch (vehicle) {
        case VEHICLE_HANG_GLIDER:   var_a2 = 0x20; break;
        case VEHICLE_ROCKET_BELT:   var_a2 = 0x26; break;
        case VEHICLE_GYROCOPTER:    var_a2 = 0x2C; break;
        case VEHICLE_CANNONBALL:    var_a2 = 0x33; break;
        case VEHICLE_SKY_DIVING:    var_a2 = 0x3F; break;
        case VEHICLE_BIRDMAN:       var_a2 = 0x39; break;
        case VEHICLE_JUMBLE_HOPPER: var_a2 = 0x45; break;
        }
        break;
    case PILOT_ROBIN:
        switch (vehicle) {
        case VEHICLE_HANG_GLIDER:   var_a2 = 0x21; break;
        case VEHICLE_ROCKET_BELT:   var_a2 = 0x27; break;
        case VEHICLE_GYROCOPTER:    var_a2 = 0x2D; break;
        case VEHICLE_CANNONBALL:    var_a2 = 0x34; break;
        case VEHICLE_SKY_DIVING:    var_a2 = 0x40; break;
        case VEHICLE_BIRDMAN:       var_a2 = 0x3A; break;
        case VEHICLE_JUMBLE_HOPPER: var_a2 = 0x46; break;
        }
        break;
    }
    // clang-format on
    if (var_a2 == -1) {
        _uvDebugPrintf("level : can't compute level append - pilsel:%d vehsel:%d\n", pilot, vehicle);
    } else {
        uvLevelAppend(var_a2);
    }
}

void level_8030BD20(void) {
}

u8 levelGetWOBJ(void** data) {
    *data = D_8034F408->dataWOBJ;
    return D_8034F408->countWOBJ;
}

u8 levelGetTPTS(LevelTPTS** data) {
    *data = D_8034F408->dataTPTS;
    return D_8034F408->countTPTS;
}

u8 levelGetAPTS(void** data) {
    *data = D_8034F408->dataAPTS;
    return D_8034F408->countAPTS;
}

u8 levelGetLPAD(void** data) {
    *data = D_8034F408->dataLPAD;
    return D_8034F408->countLPAD;
}

u8 levelGetBNUS(void** data) {
    *data = D_8034F408->dataBNUS;
    return D_8034F408->countBNUS;
}

LevelObjects* levelLoadMapObjects(u8 mapIdx) {
    s32 i;
    s32 idx;  // spC0
    u32 size; // spBC
    u32 tag;
    u8* srcPtr; // spB4
    Unk802E27A8_Arg0 sp3C;
    LevelLEVL* ptr;
    LevelObjects* temp;
    u8 tmp8;

    idx = uvFileReadHeader((s32)func_802314D0(D_8034F410[mapIdx].unk0, 2));
    temp = &gLevelObjects;
    uvMemSet((void*)temp, 0, sizeof(LevelObjects));
    gLevelObjects.dataWOBJ = &gLevelWOBJ;
    gLevelObjects.dataLPAD = &gLevelLPAD;
    gLevelObjects.dataTOYS = &gLevelTOYS;
    gLevelObjects.dataTPTS = &gLevelTPTS;
    gLevelObjects.dataAPTS = &gLevelAPTS;
    gLevelObjects.dataBNUS = &gLevelBNUS;

    while ((tag = uvFileReadBlock(idx, &size, (void**)&srcPtr, 1)) != 0) {
        switch (tag) {
        case 'ESND': // 0x45534E44
            for (i = 0; i < temp->countESND; i++) {
                _uvMediaCopy(&sp3C, srcPtr, sizeof(sp3C));
                srcPtr += sizeof(sp3C);
                func_802E27A8(&sp3C);
            }
            break;
        case 'WOBJ': // 0x574F424A
            _uvMediaCopy(temp->dataWOBJ, srcPtr, size);
            break;
        case 'LPAD': // 0x4C504144
            _uvMediaCopy(temp->dataLPAD, srcPtr, size);
            break;
        case 'TOYS': // 0x544F5953
            _uvMediaCopy(temp->dataTOYS, srcPtr, size);
            break;
        case 'TPTS': // 0x54505453
            _uvMediaCopy(temp->dataTPTS, srcPtr, size);
            break;
        case 'APTS': // 0x41505453
            _uvMediaCopy(temp->dataAPTS, srcPtr, size);
            break;
        case 'BNUS': // 0x424E5553
            _uvMediaCopy(temp->dataBNUS, srcPtr, size);
            break;
        case 'LEVL': // 0x4C45564C
            ptr = (LevelLEVL*)srcPtr;
            temp->countESND = ptr->countESND;
            if (temp->countESND >= 255) {
                _uvAssertMsg("dst_level -> level . nenvsnds < NENV_SNDS", "level.c", 639);
            }

            temp->countWOBJ = ptr->countWOBJ;
            if (temp->countWOBJ >= 16) {
                _uvAssertMsg("dst_level -> level . nwobjs < LEVEL_NWOBJS", "level.c", 642);
            }
            if (temp->countWOBJ >= 17) {
                _uvDebugPrintf("level : too many wind objects defined in level [%d]\n", temp->countWOBJ);
                temp->countWOBJ = 0;
            }

            temp->countLPAD = ptr->countLPAD;
            if (temp->countLPAD >= 15) {
                _uvDebugPrintf("level : too many potential landing pads defined in level [%d]\n", temp->countLPAD);
                temp->countLPAD = 0;
            }

            temp->countTOYS = ptr->countTOYS;
            if (temp->countTOYS >= 17) {
                _uvDebugPrintf("level : too many toys in level [%d]\n", temp->countTOYS);
                temp->countTOYS = 0;
            }

            temp->countTPTS = ptr->countTPTS;
            if (temp->countTPTS >= 17) {
                _uvDebugPrintf("level : too many terra switch points in level [%d]\n", temp->countTPTS);
                temp->countTPTS = 0;
            }

            temp->countAPTS = ptr->countAPTS;
            if (temp->countAPTS >= 21) {
                _uvDebugPrintf("level : too many audio switch points in level [%d]\n", temp->countAPTS);
                temp->countAPTS = 0;
            }

            temp->countBNUS = ptr->countBNUS;
            if (temp->countBNUS >= 3) {
                _uvDebugPrintf("level : too many bonus objects level [%d]\n", temp->countBNUS);
                temp->countBNUS = 0;
            }
            break;
        }
    }
    uvFile_80223F30(idx);
    return &gLevelObjects;
}
