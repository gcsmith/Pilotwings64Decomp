#include "common.h"
#include <uv_filesystem.h>
#include <uv_graphics.h>
#include <uv_memory.h>
#include <uv_texture.h>
#include <uv_util.h>
#include "boats.h"
#include "env_sound.h"
#include "environment.h"
#include "ferry.h"
#include "fountain.h"
#include "game.h"
#include "glider_toys.h"
#include "level.h"
#include "missi.h"
#include "oil.h"
#include "oil_plant.h"
#include "planes.h"
#include "shuttle.h"
#include "ski_lift.h"
#include "task.h"
#include "text_data.h"
#include "toys.h"
#include "whale.h"
#include "whale_pod.h"

STATIC_DATA s32 D_8034F400 = 0;
STATIC_DATA s32 D_8034F404 = 0;
STATIC_DATA LevelObjects* sLevelCurObjects = NULL;
STATIC_DATA s32 sLevelCurMap = 0;
STATIC_DATA s32 sLevelUserFileLookup[] = { 0, 1, 2, 3 };

// likely arrays of structs for level data
STATIC_DATA LevelWOBJ sLevelWOBJ[16];
STATIC_DATA LevelLPAD sLevelLPAD[14];
STATIC_DATA LevelTPTS sLevelTPTS[16];
STATIC_DATA LevelTOYS sLevelTOYS[16];
STATIC_DATA LevelAPTS sLevelAPTS[20];
STATIC_DATA LevelBNUS sLevelBNUS[2];
STATIC_DATA LevelObjects sLevelObjects;

void levelLoad(u8 map, u8 pilot, u8 vehicle, s32 animateToys) {
    s32 i;

    sLevelCurMap = map;
    uvLevelInit();
    textLoadBlock(0x42);
    envLoadTerrainPal(D_80362690->envId);
    uvLevelAppend(map);
    switch (map) {
    case MAP_HOLIDAY_ISLAND:
        sLevelCurObjects = levelLoadMapObjects(0);
        break;
    case MAP_CRESCENT_ISLAND:
        sLevelCurObjects = levelLoadMapObjects(1);
        break;
    case MAP_LITTLE_STATES:
        sLevelCurObjects = levelLoadMapObjects(2);
        break;
    case MAP_EVER_FROST_ISLAND:
        sLevelCurObjects = levelLoadMapObjects(3);
        break;
    }
    uvLevelAppend(0x1A);
    if (animateToys) {
        for (i = 0; i < (s32)sLevelObjects.countTOYS; i++) {
            toyLoad(&sLevelObjects.dataTOYS[i]);
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
    env_802E1444(D_80362690->envId);
    if (animateToys != 0) {
        level_8030B868();
    }
}

void level_8030B868(void) {
    if (D_8034F404 == 0) {
        if (1) { // fakematch
            D_8034F404 = 1;
        }
        switch (sLevelCurMap) {
        case MAP_HOLIDAY_ISLAND:
            gliderToyLoadHoliday();
            boatsLoadHoliday();
            break;
        case MAP_CRESCENT_ISLAND:
            whaleLoad();
            fountainLoad();
            boatsLoadCrescent();
            gliderToyLoadCrescent();
            break;
        case MAP_LITTLE_STATES:
            shuttleLoad();
            ferryLoad();
            missiLoadLStates();
            gliderToyLoadLStates();
            planesLoad();
            break;
        case MAP_EVER_FROST_ISLAND:
            oilInit();
            oilPlantLoad();
            skiLiftLoad();
            gliderToyLoadEFrost();
            whalePodLoad();
            break;
        }
    }
}

void level_8030B964(void) {
    if (D_8034F404 != 0) {
        if (1) { // fakematch
            D_8034F404 = 0;
        }
        switch (sLevelCurMap) {
        case MAP_HOLIDAY_ISLAND:
            gliderToyDeinit();
            boatsDeinit();
            break;
        case MAP_CRESCENT_ISLAND:
            whaleDeinit();
            fountainDeinit();
            boatsDeinit();
            gliderToyDeinit();
            break;
        case MAP_LITTLE_STATES:
            shuttleDeinit();
            ferryDeinit();
            missiDeinitLStates();
            gliderToyDeinit();
            planesDeinit();
            break;
        case MAP_EVER_FROST_ISLAND:
            oilDeinit();
            oilPlantDeinit();
            skiLiftDeinit();
            gliderToyDeinit();
            whalePodDeinit();
            break;
        }
    }
}

void level_8030BA60(void) {
    if (D_8034F400 != 0) {
        toyDeinit();
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

u8 levelGetWOBJ(LevelWOBJ** data) {
    *data = sLevelCurObjects->dataWOBJ;
    return sLevelCurObjects->countWOBJ;
}

u8 levelGetTPTS(LevelTPTS** data) {
    *data = sLevelCurObjects->dataTPTS;
    return sLevelCurObjects->countTPTS;
}

u8 levelGetAPTS(LevelAPTS** data) {
    *data = sLevelCurObjects->dataAPTS;
    return sLevelCurObjects->countAPTS;
}

u8 levelGetLPAD(LevelLPAD** data) {
    *data = sLevelCurObjects->dataLPAD;
    return sLevelCurObjects->countLPAD;
}

u8 levelGetBNUS(LevelBNUS** data) {
    *data = sLevelCurObjects->dataBNUS;
    return sLevelCurObjects->countBNUS;
}

LevelObjects* levelLoadMapObjects(u8 mapIdx) {
    s32 i;
    s32 idx;
    u32 size;
    u32 tag;
    u8* srcPtr;
    LevelESND esnd;
    LevelLEVL* ptr;
    LevelObjects* temp;
    u8 tmp8;

    idx = uvFileReadHeader((s32)uvUserFileRead(sLevelUserFileLookup[mapIdx], MEM_ROM_OFFSET));
    temp = &sLevelObjects;
    uvMemSet((void*)temp, 0, sizeof(LevelObjects));
    sLevelObjects.dataWOBJ = sLevelWOBJ;
    sLevelObjects.dataLPAD = sLevelLPAD;
    sLevelObjects.dataTOYS = sLevelTOYS;
    sLevelObjects.dataTPTS = sLevelTPTS;
    sLevelObjects.dataAPTS = sLevelAPTS;
    sLevelObjects.dataBNUS = sLevelBNUS;

    while ((tag = uvFileReadBlock(idx, &size, (void**)&srcPtr, 1)) != 0) {
        switch (tag) {
        case 'ESND': // 0x45534E44
            for (i = 0; i < temp->countESND; i++) {
                _uvMediaCopy(&esnd, srcPtr, sizeof(esnd));
                srcPtr += sizeof(esnd);
                envSoundLoad(&esnd);
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
            if (temp->countWOBJ > ARRAY_COUNT(sLevelWOBJ)) {
                _uvDebugPrintf("level : too many wind objects defined in level [%d]\n", temp->countWOBJ);
                temp->countWOBJ = 0;
            }

            temp->countLPAD = ptr->countLPAD;
            if (temp->countLPAD > ARRAY_COUNT(sLevelLPAD)) {
                _uvDebugPrintf("level : too many potential landing pads defined in level [%d]\n", temp->countLPAD);
                temp->countLPAD = 0;
            }

            temp->countTOYS = ptr->countTOYS;
            if (temp->countTOYS > ARRAY_COUNT(sLevelTOYS)) {
                _uvDebugPrintf("level : too many toys in level [%d]\n", temp->countTOYS);
                temp->countTOYS = 0;
            }

            temp->countTPTS = ptr->countTPTS;
            if (temp->countTPTS > ARRAY_COUNT(sLevelTPTS)) {
                _uvDebugPrintf("level : too many terra switch points in level [%d]\n", temp->countTPTS);
                temp->countTPTS = 0;
            }

            temp->countAPTS = ptr->countAPTS;
            if (temp->countAPTS > ARRAY_COUNT(sLevelAPTS)) {
                _uvDebugPrintf("level : too many audio switch points in level [%d]\n", temp->countAPTS);
                temp->countAPTS = 0;
            }

            temp->countBNUS = ptr->countBNUS;
            if (temp->countBNUS > ARRAY_COUNT(sLevelBNUS)) {
                _uvDebugPrintf("level : too many bonus objects level [%d]\n", temp->countBNUS);
                temp->countBNUS = 0;
            }
            break;
        }
    }
    uvFile_80223F30(idx);
    return &sLevelObjects;
}
