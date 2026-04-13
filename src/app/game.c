#include "common.h"
#include "game.h"
#include <uv_controller.h>
#include <uv_environment.h>
#include <uv_event.h>
#include <uv_memory.h>
#include <uv_texture.h>
#include "app/cannonball.h"
#include "app/credits.h"
#include "app/demo.h"
#include "app/environment.h"
#include "app/env_sound.h"
#include "app/falco.h"
#include "app/fdr.h"
#include "app/file_menu.h"
#include "app/glider_toys.h"
#include "app/hud.h"
#include "app/jumble_hopper.h"
#include "app/options.h"
#include "app/pads.h"
#include "app/proxanim.h"
#include "app/results.h"
#include "app/shuttle.h"
#include "app/snap.h"
#include "app/snd.h"
#include "app/test_menu.h"
#include "app/text_data.h"
#include "app/thermals.h"
#include "app/toys.h"
#include "app/user_paths.h"
#include "app/wind.h"
#include "app/wind_objects.h"
#include "app/code_61A60.h"
#include "app/code_64730.h"
#include "app/code_7C4C0.h"
#include "app/code_7FE00.h"
#include "app/code_936F0.h"
#include "app/code_94E60.h"
#include "app/code_9A960.h"
#include "app/code_A8C30.h"
#include "app/code_B2900.h"
#include "app/code_B3A70.h"
#include "app/code_C9B60.h"
#include "app/code_D2B10.h"

Unk80362690* D_80362690;
Unk80362690 D_80362698;
u8 D_80362748[1][0x740]; // vehicle data buffer
Camera D_80362E88[1];
Unk80364210 D_80364210[1];
HangGliderData* D_803676F0;
GyrocopterData* D_803676F4;
RocketBeltData* D_803676F8;
CannonballData* D_803676FC;
SkyDivingData* D_80367700;
BirdmanData* D_80367704;
JumbleHopperData* D_80367708;
s32 D_8036770C;
Unk80367710 D_80367710;
Unk80367868 D_80367868;

s32 D_8034F160 = -1;
s32 D_8034F164 = 0;

typedef s32 (*GameStateUpdateFunc)(Unk80362690*);

s32 gameUpdateStateTitle(Unk80362690*);
s32 gameUpdateState1(Unk80362690*);
s32 gameUpdateStateTestDetails(Unk80362690*);
s32 gameUpdateStatePilotSelect(Unk80362690*);
s32 gameUpdateStateTestSetup(Unk80362690*);
s32 gameUpdateStateTestUpdate(Unk80362690*);
s32 gameUpdateStateResults(Unk80362690*);
s32 gameUpdateStateOptions(Unk80362690*);
s32 gameUpdateStateDemoPilot(Unk80362690*);
s32 gameUpdateStateDemoTestSetup(Unk80362690*);
s32 gameUpdateStateFileMenu(Unk80362690*);
s32 gameUpdateStateVehicleClassSelect(Unk80362690*);
s32 gameUpdateStateTestOverview(Unk80362690*);
s32 gameUpdateStateResultsCB(Unk80362690*);
s32 gameUpdateStateCongratulations(Unk80362690*);
s32 gameUpdateStateCredits(Unk80362690*);

GameStateUpdateFunc sGameStateUpdateFuncs[] = {
    gameUpdateStateTitle,              // GAME_STATE_TITLE
    gameUpdateState1,                  // GAME_STATE_1
    gameUpdateStateTestDetails,        // GAME_STATE_TEST_DETAILS
    gameUpdateStatePilotSelect,        // GAME_STATE_PILOT_SELECT
    gameUpdateStateTestSetup,          // GAME_STATE_TEST_SETUP
    gameUpdateStateTestUpdate,         // GAME_STATE_TEST_UPDATE
    gameUpdateStateResults,            // GAME_STATE_RESULTS
    gameUpdateStateOptions,            // GAME_STATE_OPTIONS
    gameUpdateStateDemoPilot,          // GAME_STATE_DEMO_PILOT
    gameUpdateStateDemoTestSetup,      // GAME_STATE_DEMO_TEST_SETUP
    gameUpdateStateFileMenu,           // GAME_STATE_FILE_MENU
    gameUpdateStateVehicleClassSelect, // GAME_STATE_VEHICLE_CLASS_SELECT
    gameUpdateStateTestOverview,       // GAME_STATE_TEST_OVERVIEW
    gameUpdateStateResultsCB,          // GAME_STATE_RESULTS_CB
    gameUpdateStateCongratulations,    // GAME_STATE_CONGRATULATIONS
    gameUpdateStateCredits,            // GAME_STATE_CREDITS
};

void gameInit(void) {
    Unk80362690_Unk0* temp_s0;
    s32 i;

    uvGfxEnableLighting(FALSE);
    D_80362690 = &D_80362698;
    D_80362690->state = GAME_STATE_TITLE;
    D_80362690->unk98 = 1;
    D_80362690->unk9C = 0;
    D_80362690->map = 0;
    D_80362690->terraId = 0;
    D_80362690->debugFlag = 0;
    D_80362690->unkA3 = 0;
    D_80362690->unkA2 = 0;
    D_80362690->unkA8 = 0;
    rocketBeltInit();
    cannonInit();
    skydivingInit();
    jumbleHopperInit();
    birdInit();
    hangGliderInit();
    gyrocopterInit();
    func_802F88D0();
    fdrInit();
    taskInit();
    envInit();
    sndInit();
    windObjInit();
    toyInit();
    proxAnimInit();
    falcoInit();
    userPathInit();
    func_80337D50();
    saveModuleInit();
    shuttleInit();
    gliderToyInit();

    for (i = 0; i < 1; i++) {
        temp_s0 = &D_80362690->unkC[i];
        temp_s0->unk70 = &D_80362E88[i];
        temp_s0->unk74 = &D_80364210[i];
        temp_s0->vehicleData = D_80362748[i];
        temp_s0->pilot = 0;
        temp_s0->veh = 0;
        temp_s0->cls = 0xFF;
        temp_s0->test = 0xFF;
        temp_s0->unk8B = 0;
        func_802D3170(i, &D_80362E88[i]);
        func_8032B3D0(&D_80364210[i]);
        func_8034B5E0(temp_s0->unk70->unk22C, temp_s0->unk70);
    }
}

void func_802EBBB8(void) {
    D_8034F160 = -1;
}

void func_802EBBC8(Unk80362690* arg0) {
    demoSetRecMode(0);
    func_802ECE94(arg0);
    arg0->unkA4 = FALSE;
    func_802DA54C();
    D_8036770C = 0;
    hudDemoControllerEn(FALSE);
    hudText_8031D8E0(-1, 0.0f, 0.0f);
    D_8034F160 = -1;
}

void gameUpdate(void) {
    if (D_80362690->state >= GAME_STATE_COUNT) {
        _uvDebugPrintf("Game: Bad state %d\n", D_80362690->state);
        return;
    }
    D_80362690->state = sGameStateUpdateFuncs[D_80362690->state](D_80362690);
}

s32 gameUpdateStateTitle(Unk80362690* arg0) {
    s32 gameState;

    if (uvControllerCheckInserted(0) == 0) {
        func_8032D90C();
    }
    uvEventPost(6, 0);
    if (D_8034F160 != 0x47) {
        D_8034F160 = 0x47;
        uvLevelInit();
        uvLevelAppend(0x47);
        uvLevelAppend(2);
        uvLevelAppend(0x87);
        textLoadBlock(0x42);
    }
    gameState = func_80342630();
    func_8032D51C(0);
    return gameState;
}

s32 gameUpdateStateOptions(Unk80362690* arg0) {
    if (D_8034F160 != 0x49) {
        uvLevelInit();
        uvLevelAppend(0x49);
        D_8034F160 = 0x49;
    }
    optionsTopRender();
    func_80344258(0);
    return GAME_STATE_TITLE;
}

void func_802EBD88(Unk80362690_Unk0* arg0, u8 arg1) {
    if (D_8034F164 != 0) {
        demoLoad(arg0->pilot, arg0->veh);
    } else {
        demoLoad(arg0->pilot, -1);
    }
    if (arg1 != 0) {
        arg0->test = demoGetTestId();
        arg0->cls = demoGetClassId();
        arg0->veh = demoGetVehicleId();
        arg0->unk8 = demoGet_80322B78();
    }
    D_8036770C = 0;
}

s32 gameUpdateStateDemoPilot(Unk80362690* arg0) {
    s32 gameState;

    D_8034F164 = 0;
    D_8034F160 = -1;
    hudDemoControllerEn(TRUE);
    arg0->unkC[arg0->unk9C].pilot = func_802DA530();
    func_802EBD88(&arg0->unkC[arg0->unk9C], 1);
    gameState = func_802DA574(arg0);
    if (gameState != GAME_STATE_DEMO_TEST_SETUP) {
        hudDemoControllerEn(FALSE);
    }
    return gameState;
}

s32 gameUpdateStateDemoTestSetup(Unk80362690* arg0) {
    s32 gameState;

    arg0->unkA4 = TRUE;
    gameState = gameUpdateStateTestSetup(arg0);
    func_8032D51C(0);
    return gameState;
}

s32 gameUpdateStateVehicleClassSelect(Unk80362690* arg0) {
    s32 gameState;

    if (D_803505B0 != 2) {
        func_8033F748(2);
        func_8033F964(0);
        func_8033FCD0(0xFF);
    }
    gameState = func_8030D930();
    func_8032D51C(0);
    return gameState;
}

s32 gameUpdateStateFileMenu(Unk80362690* arg0) {
    s32 gameState;

    hudText_8031D8E0(-1, 0.0f, 0.0f);
    hudWarningText(-1, 0.0f, 0.0f);
    uvLevelInit();
    uvLevelAppend(0x48);
    D_8034F160 = 0x48;
    textLoadBlock(0x42);
    if (D_803505B0 != 2) {
        func_8033F748(2);
        func_8033F964(0);
        func_8033FCD0(0xFF);
    }
    gameState = fileMenuTopRender();
    if (gameState == GAME_STATE_TITLE) {
        func_80344258(0);
    }
    func_8032D51C(0);
    return gameState;
}

s32 gameUpdateStateTestOverview(Unk80362690* arg0) {
    s32 gameState;

    if (D_803505B0 != 3) {
        func_8033F748(3);
        func_8033F964(0);
        func_8033FCD0(0xFF);
    }
    gameState = func_8030C1C0();
    D_8034F160 = -1;
    func_8032D51C(0);
    return gameState;
}

s32 gameUpdateStateResultsCB(Unk80362690* arg0) {
    s32 gameState;

    gameState = resultHandler(1);
    func_802ECE94(arg0);
    if (gameState == GAME_STATE_TEST_SETUP) {
        sndPlaySfx(SFX_UI_TEST_START);
    }
    return gameState;
}

s32 gameUpdateStateCongratulations(Unk80362690* arg0) {
    return func_80321700();
}

s32 gameUpdateStateCredits(Unk80362690* arg0) {
    func_802EBBB8();
    creditsMainRender();
    return GAME_STATE_TITLE;
}

s32 gameUpdateState1(Unk80362690* arg0) {
    Unk80362690_Unk0* sp1C;

    sp1C = &arg0->unkC[arg0->unk9C];
    uvEventPost(7, 0);
    sp1C->cls = CLASS_BEGINNER;
    return GAME_STATE_TEST_DETAILS;
}

s32 gameUpdateStateTestDetails(Unk80362690* arg0) {
    Unk80362690_Unk0* sp2C;
    s32 var_a1;
    s32 var_a2;
    s32 i;
    u8 sp1F;
    s32 gameState;
    Unk80367710* ptr = &D_80367710;

    sp2C = &arg0->unkC[arg0->unk9C];
    if (D_803505B0 != 3) {
        func_8033F748(3);
        func_8033F964(0);
        func_8033FCD0(0xFF);
    }
    uvEventPost(8, 0);
    if (IS_BONUS_VEHICLE(sp2C->veh) && (sp2C->veh != VEHICLE_BIRDMAN)) {
        var_a1 = 3;
    } else {
        var_a1 = taskGetTestCount(sp2C->cls, sp2C->veh);
    }

    for (i = 0, var_a2 = 0; i < var_a1; i++, var_a2++) {
        ptr->unk4[var_a2].unk0 = i;
    }

    ptr->testCount = var_a2;
    sp1F = testMenuMainRender(sp2C, ptr);
    func_8033FB14();
    if (sp1F == 0xFE) {
        gameState = GAME_STATE_DEMO_TEST_SETUP;
        D_8034F164 = 1;
        func_802EBD88(sp2C, 0);
    } else {
        if (sp1F == 0xFF) {
            gameState = GAME_STATE_PILOT_SELECT;
            D_8034F164 = 0;
        } else {
            if (IS_BONUS_VEHICLE(sp2C->veh) && (sp2C->veh != VEHICLE_BIRDMAN)) {
                sp2C->cls = sp1F;
            } else {
                sp2C->test = sp1F;
            }
            gameState = GAME_STATE_TEST_SETUP;
            D_8034F164 = 0;
        }
    }
    hudDemoControllerEn(D_8034F164);
    func_8032D51C(0);
    return gameState;
}

s32 gameUpdateStatePilotSelect(Unk80362690* arg0) {
    s32 i = 0;
    s32 pilot;
    Unk80362690_Unk0* sp1C;
    Unk80367868* ptr = &D_80367868;

    sp1C = &arg0->unkC[arg0->unk9C];
    if (D_803505B0 != 2) {
        func_8033F748(2);
        func_8033F964(0);
        func_8033FCD0(0xFF);
    }
    hudText_8031D8E0(-1, 0.0f, 0.0f);
    hudWarningText(-1, 0.0f, 0.0f);
    uvEventPost(9, 0);

    D_80367868.unk4[i].pilot = PILOT_LARK;
    D_80367868.unk4[i].modelId = MODEL_PILOT_LARK;
    D_80367868.unk4[i].textId = 0x35; // "LARK"
    i++;
    D_80367868.unk4[i].pilot = PILOT_KIWI;
    D_80367868.unk4[i].modelId = MODEL_PILOT_KIWI;
    D_80367868.unk4[i].textId = 0x14C; // "KIWI"
    i++;
    D_80367868.unk4[i].pilot = PILOT_GOOSE;
    D_80367868.unk4[i].modelId = MODEL_PILOT_GOOSE;
    D_80367868.unk4[i].textId = 0x9C; // "GOOSE"
    i++;
    D_80367868.unk4[i].pilot = PILOT_IBIS;
    D_80367868.unk4[i].modelId = MODEL_PILOT_IBIS;
    D_80367868.unk4[i].textId = 0x1A7; // "IBIS"
    i++;
    D_80367868.unk4[i].pilot = PILOT_HAWK;
    D_80367868.unk4[i].modelId = MODEL_PILOT_HAWK;
    D_80367868.unk4[i].textId = 0x85; // "HAWK"
    i++;
    D_80367868.unk4[i].pilot = PILOT_ROBIN;
    D_80367868.unk4[i].modelId = MODEL_PILOT_ROBIN;
    D_80367868.unk4[i].textId = 0x128; // "ROBIN"
    i++;

    ptr->unk0 = i;
    pilot = func_802DD200(sp1C->unk70, ptr);
    func_8032D51C(0);
    if (pilot == -1) {
        return GAME_STATE_VEHICLE_CLASS_SELECT;
    }
    sp1C->pilot = pilot;
    return GAME_STATE_TEST_OVERVIEW;
}

s32 gameUpdateStateTestSetup(Unk80362690* arg0) {
    Unk80362690_Unk0* temp_s0;
    f32 sp28;

    temp_s0 = &arg0->unkC[arg0->unk9C];
    sp28 = 1.0f;
    uvGfxClearScreen(0x00, 0x00, 0x00, 0xFF);
    uvGfxBegin();
    uvGfxEnd();
    uvGfxClearScreen(0x00, 0x00, 0x00, 0xFF);
    uvGfxBegin();
    uvGfxEnd();
    temp_s0->smokeId = -1;
    temp_s0->unk7B = 0;
    if (temp_s0->veh == VEHICLE_CANNONBALL) {
        D_803676FC = (CannonballData*)temp_s0->vehicleData;
        return cannonLoad802D77D8(arg0, D_803676FC);
    }
    if (arg0->unkA2 == 0) {
        envSoundInit();
        func_8033F964(1);
    }
    hud_8031A2CC();
    hudText_8031D8E0(-1, 0.0f, 0.0f);
    hudWarningText(-1, 0.0f, 0.0f);
    hud_8031DAA8(0, 0.0f);
    proxAnimDispatchInit();
    taskInitTest(temp_s0->cls, temp_s0->veh, temp_s0->test, &arg0->map, &arg0->terraId, &arg0->envId);
    levelLoad(arg0->map, temp_s0->pilot, temp_s0->veh, TRUE);
    uvChanTerra(temp_s0->unk70->unk22C, arg0->terraId);
    uvEnvFunc(arg0->envId, 0, env_802E0CF0);
    arg0->unkA0 = 1;
    taskLoad();
    windObjLoad();
    if (arg0->unkA2 == 0) {
        func_8034B5E0(temp_s0->unk70->unk22C, temp_s0->unk70);
    } else {
        D_8034F160 = -1;
    }
    switch (temp_s0->veh) {
    case VEHICLE_HANG_GLIDER:
        D_803676F0 = (HangGliderData*)temp_s0->vehicleData;
        hangGliderLoadLevel(arg0->unk9C, temp_s0->pilot, D_803676F0, temp_s0->unk70);
        hangGliderEnterLeave(D_803676F0);
        func_802EDD9C(temp_s0, &D_803676F0->unk10);
        if ((arg0->state != GAME_STATE_DEMO_PILOT) && (arg0->unkA2 == 0)) {
            func_8033F748(4);
        }
        sp28 = 0.5f;
        break;
    case VEHICLE_GYROCOPTER:
        D_803676F4 = (GyrocopterData*)temp_s0->vehicleData;
        gyrocopterLoadLevel(arg0->unk9C, temp_s0->pilot, D_803676F4, temp_s0->unk70);
        gyrocopterEnterLeave(D_803676F4);
        func_802EDD9C(temp_s0, &D_803676F4->unk10);
        if ((arg0->state != GAME_STATE_DEMO_PILOT) && (arg0->unkA2 == 0)) {
            func_8033F748(0xC);
        }
        break;
    case VEHICLE_ROCKET_BELT:
        D_803676F8 = (RocketBeltData*)temp_s0->vehicleData;
        rocketBeltLoadLevel(arg0->unk9C, temp_s0->pilot, D_803676F8, temp_s0->unk70);
        rocketBeltEnterLeave(D_803676F8);
        func_802EDD9C(temp_s0, &D_803676F8->unk10);
        if ((arg0->state != GAME_STATE_DEMO_PILOT) && (arg0->unkA2 == 0)) {
            func_8033F748(8);
        }
        sp28 = 0.5f;
        break;
    case VEHICLE_SKY_DIVING:
        D_80367700 = (SkyDivingData*)temp_s0->vehicleData;
        skydivingLoadLevel(arg0->unk9C, temp_s0->pilot, D_80367700, temp_s0->unk70);
        skydivingEnterLeave(D_80367700);
        func_802EDD9C(temp_s0, &D_80367700->unk10);
        if ((arg0->state != GAME_STATE_DEMO_PILOT) && (arg0->unkA2 == 0)) {
            func_8033F748(0x13);
        }
        sp28 = 0.5f;
        break;
    case VEHICLE_JUMBLE_HOPPER:
        D_80367708 = (JumbleHopperData*)temp_s0->vehicleData;
        jumbleHopperLoadLevel(arg0->unk9C, temp_s0->pilot, D_80367708, temp_s0->unk70);
        jumbleHopperEnterLeave(D_80367708);
        func_802EDD9C(temp_s0, &D_80367708->unk74);
        if ((arg0->state != GAME_STATE_DEMO_PILOT) && (arg0->unkA2 == 0)) {
            func_8033F748(0x17);
        }
        sp28 = 0.5f;
        break;
    case VEHICLE_BIRDMAN:
        D_80367704 = (BirdmanData*)temp_s0->vehicleData;
        birdLoadLevel(arg0->unk9C, temp_s0->pilot, D_80367704, temp_s0->unk70);
        birdEnterLeave(D_80367704);
        func_802EDD9C(temp_s0, &D_80367704->unk10);
        if ((arg0->state != GAME_STATE_DEMO_PILOT) && (arg0->unkA2 == 0)) {
            func_8033F748(0x19);
        }
        break;
    }
    hudInit();
    func_802D4DE8(temp_s0->unk70, 0);
    if (arg0->unkA2 == 0) {
        hudText_8031D8E0(0x16A, 1.5f, 8.0f);
    }
    arg0->unkA1 = 0;
    func_8032B508(temp_s0->unk74);
    func_80313E0C(0.0f);
    fdrSetBlen(sp28);
    fdr_802E68B0(1);
    if (arg0->unkA2 == 0) {
        func_8033F964(0);
        func_8033FCD0(temp_s0->veh);
    }
    uvEventPost(0xB, 0);
    return GAME_STATE_TEST_UPDATE;
}

s32 gameUpdateStateResults(Unk80362690* arg0) {
    Unk80362690_Unk0* temp_s0;
    s32 var_v1;
    f32 var_fs0;
    f32 sp38;

    temp_s0 = &arg0->unkC[arg0->unk9C];
    var_fs0 = 0.0f;
    uvEventPost(0xC, 0);
    if (arg0->unkA4) {
        func_802EBBC8(arg0);
        if (D_8034F164 != 0) {
            return GAME_STATE_TEST_DETAILS;
        }
        func_80344258(1);
        return GAME_STATE_TITLE;
    }

    if (temp_s0->veh == VEHICLE_CANNONBALL) {
        D_803676FC = (CannonballData*)D_80362748[arg0->unk9C];
        return cannonLandedFrame(D_803676FC);
    }

    if (temp_s0->unk79 != 0) {
        switch (temp_s0->veh) {
        case VEHICLE_HANG_GLIDER:
            func_802F041C(temp_s0->vehicleData);
            break;
        case VEHICLE_GYROCOPTER:
            func_802F764C(temp_s0->vehicleData);
            break;
        case VEHICLE_ROCKET_BELT:
            func_80325E1C(temp_s0->vehicleData);
            break;
        case VEHICLE_CANNONBALL:
            cannonPilotLand(temp_s0->vehicleData);
            break;
        case VEHICLE_BIRDMAN:
            bird_802CD0F8(temp_s0->vehicleData);
            break;
        }
    }
    temp_s0->unk78 = func_8032B560(temp_s0->unk74, temp_s0->cls, temp_s0->test, temp_s0->veh);
    if (temp_s0->unk7A != 0) {
        sp38 = 4.0f;
    } else if (temp_s0->unk79 != 0) {
        sp38 = 1.0f;
    } else {
        sp38 = 4.0f;
    }
    while (var_fs0 < sp38) {
        switch (temp_s0->veh) {
        case VEHICLE_HANG_GLIDER:
            func_802EEB00(temp_s0->vehicleData, temp_s0->unk78);
            break;
        case VEHICLE_GYROCOPTER:
            func_802F56B4(temp_s0->vehicleData, temp_s0->unk78);
            break;
        case VEHICLE_ROCKET_BELT:
            func_803273C8(temp_s0->vehicleData, temp_s0->unk78);
            break;
        case VEHICLE_CANNONBALL:
            cannonMovementFrame(temp_s0->vehicleData, arg0->state);
            break;
        case VEHICLE_SKY_DIVING:
            skydivingMovementFrame(temp_s0->vehicleData, arg0->state);
            break;
        case VEHICLE_BIRDMAN:
            bird_802CEB68(temp_s0->vehicleData, temp_s0->unk78);
            break;
        }
        uvGfxBegin();
        proxAnimUpdate();
        taskFrameUpdate(&temp_s0->unk2C, 0.0f);
        func_8034B624(temp_s0->unk70);
        func_80313D74();
        uvGfxEnd();
        var_fs0 += D_8034F854;
    }
    hudText_8031D8E0(-1, 0.0f, 0.0f);
    hudWarningText(-1, 0.0f, 0.0f);
    hudGetState()->renderFlags = 0;
    hud_8031DAA8(0, 0.0f);
    resultInit(1);
    while ((var_v1 = resultMenuChoose(1)) == 0) {
        switch (temp_s0->veh) {
        case VEHICLE_HANG_GLIDER:
            func_802EEB00(temp_s0->vehicleData, temp_s0->unk78);
            break;
        case VEHICLE_GYROCOPTER:
            func_802F56B4(temp_s0->vehicleData, temp_s0->unk78);
            break;
        case VEHICLE_ROCKET_BELT:
            func_803273C8(temp_s0->vehicleData, temp_s0->unk78);
            break;
        case VEHICLE_CANNONBALL:
            cannonMovementFrame(temp_s0->vehicleData, arg0->state);
            break;
        case VEHICLE_SKY_DIVING:
            skydivingMovementFrame(temp_s0->vehicleData, arg0->state);
            break;
        case VEHICLE_BIRDMAN:
            bird_802CEB68(temp_s0->vehicleData, temp_s0->unk78);
            break;
        }
        uvGfxBegin();
        proxAnimUpdate();
        taskFrameUpdate(&temp_s0->unk2C, 0.0f);
        func_8034B624(temp_s0->unk70);
        resultDrawTally(1);
        if (D_803505B0 != 0x1C) {
            uvEventPost(0x12, 0);
            func_8033F748(0x1C);
            func_8033F964(0);
            func_8033FCD0(0xFF);
        }
        uvGfxEnd();
    }

    resultDeinit();
    func_802ECE94(arg0);
    if (var_v1 == GAME_STATE_TEST_SETUP) {
        sndPlaySfx(SFX_UI_TEST_START);
    }
    return var_v1;
}

void func_802ECE94(Unk80362690* arg0) {
    Unk80362690_Unk0* temp_s0;

    temp_s0 = &arg0->unkC[arg0->unk9C];
    uvEventPost(0xD, 0);
    if (arg0->unkA2 == 0) {
        func_8033FCD0(0xFF);
    }
    if (temp_s0->vehicleData != NULL) {
        if (!arg0->unkA4 && (arg0->unkA2 == 0)) {
            saveFileWrite(temp_s0->unk8A);
        }
        switch (temp_s0->veh) {
        case VEHICLE_HANG_GLIDER:
            hangGliderEnterLeave(temp_s0->vehicleData);
            func_802EF328(temp_s0->vehicleData);
            break;
        case VEHICLE_GYROCOPTER:
            gyrocopterEnterLeave(temp_s0->vehicleData);
            func_802F5F80(temp_s0->vehicleData);
            break;
        case VEHICLE_ROCKET_BELT:
            rocketBeltEnterLeave(temp_s0->vehicleData);
            func_80325100(temp_s0->vehicleData);
            break;
        case VEHICLE_CANNONBALL:
            cannonLevelEnterLeave(temp_s0->vehicleData);
            cannonEndTarget(temp_s0->vehicleData);
            break;
        case VEHICLE_SKY_DIVING:
            skydivingEnterLeave(temp_s0->vehicleData);
            func_8032FE4C(temp_s0->vehicleData);
            break;
        case VEHICLE_JUMBLE_HOPPER:
            jumbleHopperEnterLeave(temp_s0->vehicleData);
            func_802FA290(temp_s0->vehicleData);
            break;
        case VEHICLE_BIRDMAN:
            birdEnterLeave(temp_s0->vehicleData);
            bird_802CC51C(temp_s0->vehicleData);
            break;
        }
        taskDeinitLevel();
        windObjDeinit();
        level_8030BA60();
        if (arg0->unkA2 == 0) {
            func_8033F964(1);
        }
        hud_8031DAA8(0, 0.0f);
        hudGetState()->renderFlags = 0;
        temp_s0->unk7C = 0;
        temp_s0->unk80 = 0.0f;
    }
}

s32 gameUpdateStateTestUpdate(Unk80362690* arg0) {
    Unk80362690_Unk0* sp6C;
    u8 sp6B;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    s32 gameState;
    s32 pad;
    s32 sp50;
    s32 sp4C;
    f32 sp48;
    f32 sp44;
    GyrocopterData* sp40;

    sp6C = &arg0->unkC[arg0->unk9C];
    gameState = GAME_STATE_TEST_UPDATE;
    if ((D_8036770C == 0) && arg0->unkA4 && (D_8036770C == 0)) {
        demoSetRecMode(2);
        D_8036770C = 1;
    }
    demoLogInput();
    uvEventPost(0xE, 0);
    if (arg0->unkA4 && ((demoGetRecMode() == 0) || ((sp50 = uvControllerButtonPress(arg0->unk9C, A_BUTTON | B_BUTTON | START_BUTTON)) != 0))) {
        sndPlaySfx(SFX_UI_CANCEL);
        func_802EBBC8(arg0);
        func_8032D51C(0);
        if (D_8034F164 != 0) {
            return 2;
        }
        if (sp50 != 0) {
            func_80344258(0);
        }
        return 0;
    }
    if (sp6C->veh == VEHICLE_CANNONBALL) {
        return cannonFrame802D7B7C(arg0);
    }
    proxAnimUpdate();
    level_8030BD20();
    env_802E15F0();
    func_802F89A0(D_80362E88);
    windObjFrameUpdate();

    switch (sp6C->veh) {
    case VEHICLE_HANG_GLIDER:
        D_803676F0 = (HangGliderData*)sp6C->vehicleData;
        hangGliderMovementFrame(D_803676F0, arg0->state);
        switch (D_803676F0->unk8C) {
        case 0:
            sp6B = 1;
            break;
        case 1:
            sp6B = 2;
            break;
        case 2:
            sp6B = 3;
            break;
        case 3:
            sp6B = 4;
            break;
        case 4:
            sp6B = 5;
            break;
        }
        func_802EDAF0(sp6C, &D_803676F0->unk10, D_803676F0->unk10.m[3][2], D_803676F0->unk1B0, sp6C->unk24, 1.0f, D_803676F0->unk8, D_803676F0->unk4,
                      D_803676F0->unk8D, D_803676F0->unkE8, sp6B);
        break;
    case VEHICLE_GYROCOPTER:
        D_803676F4 = (GyrocopterData*)sp6C->vehicleData;
        gyrocopterMovementFrame(D_803676F4, arg0->state);
        switch (D_803676F4->unkC0) {
        case 0:
            sp6B = 1;
            break;
        case 1:
            sp6B = 2;
            break;
        case 2:
            sp6B = 3;
            break;
        case 3:
            sp6B = 4;
            break;
        case 4:
            if (D_803676F4->unk5F == 0) {
                sp6B = 2;
            } else {
                sp6B = 5;
            }
            break;
        }
        func_802EDAF0(sp6C, &D_803676F4->unk10, D_803676F4->unk10.m[3][2], D_803676F4->unk1A8, D_803676F4->unk54, D_803676F4->fuel, D_803676F4->elapsedTime,
                      D_803676F4->unk4, D_803676F4->unkC1, D_803676F4->unkD0, sp6B);
        if (sp6B == 5) {
            sp6C->unkA = 5;
        }
        break;
    case VEHICLE_ROCKET_BELT:
        D_803676F8 = sp6C->vehicleData;
        rocketBeltMovementFrame(D_803676F8, arg0->state);
        switch (D_803676F8->unk90) {
        case 0:
            sp6B = 1;
            break;
        case 1:
            sp6B = 1;
            break;
        case 2:
            sp6B = 3;
            break;
        case 3:
            sp6B = 4;
            break;
        case 4:
            sp6B = 5;
            break;
        }
        func_802EDAF0(sp6C, &D_803676F8->unk10, D_803676F8->unk10.m[3][2], D_803676F8->unk1F4, D_803676F8->unk114, D_803676F8->unkF8, D_803676F8->unk8,
                      D_803676F8->unk4, D_803676F8->unk91, D_803676F8->unkE8, sp6B);
        break;
    case VEHICLE_SKY_DIVING:
        D_80367700 = (SkyDivingData*)sp6C->vehicleData;
        skydivingMovementFrame(D_80367700, arg0->state);
        switch (D_80367700->unk70) {
        case 0:
            sp6B = 1;
            break;
        case 1:
            sp6B = 1;
            break;
        case 4:
            sp6B = 1;
            break;
        case 5:
            sp6B = 1;
            break;
        case 2:
            sp6B = 5;
            break;
        case 3:
            sp6B = 4;
            break;
        }
        func_802EDAF0(sp6C, &D_80367700->unk10, D_80367700->unk10.m[3][2], D_80367700->unk16C, D_80367700->unk2C4, 1.0f, D_80367700->unk8, D_80367700->unk4, 0,
                      D_80367700->unkB8, sp6B);
        break;
    case VEHICLE_JUMBLE_HOPPER:
        D_80367708 = (JumbleHopperData*)sp6C->vehicleData;
        jumbleHopperMovementFrame(D_80367708, arg0->state);
        if (D_80367708->unk4C == 0xA) {
            sp6B = 5;
        } else {
            sp6B = 1;
        }
        func_802EDAF0(sp6C, &D_80367708->unk74, D_80367708->unk74.m[3][2], D_80367708->unk180, 0.0f, 1.0f, D_80367708->unk8, D_80367708->unk4, 0,
                      D_80367708->unk4F, sp6B);
        break;
    case VEHICLE_BIRDMAN:
        D_80367704 = (BirdmanData*)sp6C->vehicleData;
        birdMovementFrame(D_80367704, arg0->state);

        switch (D_80367704->unk104) {
        case 0:
            sp6B = 1;
            break;
        case 3:
            sp6B = 5;
            break;
        case 1:
            sp6B = 3;
            break;
        case 2:
            sp6B = 4;
            break;
        }

        func_802EDAF0(sp6C, &D_80367704->unk10, D_80367704->unk10.m[3][2], D_80367704->unk224, 0.0f, 1.0f, D_80367704->unk8, D_80367704->unk4, 0,
                      D_80367704->unk15C, sp6B);
        break;
    }
    if (sp6C->unkA == 5) {
        gameState = GAME_STATE_RESULTS;
    }

    switch (sp6C->unk7C) {
    case 1:
        if ((D_8034F850 - sp6C->unk80) >= 1.0f) {
            hud_8031DAA8(1, 2.5f);
            sp6C->unk7C = 2;
        }
        break;
    case 2:
        if ((D_8034F850 - sp6C->unk80) >= 3.5f) {
            sp6C->unk7C = 3;
        }
        break;
    case 3:
        if ((D_8034F850 - sp6C->unk80) >= 4.0f) {
            hud_8031DAA8(2, 0.5f);
            sp6C->unk7C = 4;
        }
        break;
    case 4:
        if ((D_8034F850 - sp6C->unk80) >= 4.5f) {
            gameState = GAME_STATE_RESULTS;
        }
        break;
    case 5:
        gameState = GAME_STATE_RESULTS;
        break;
    }
    uvEventPost(0x16, 0);
    if (taskFrameUpdate(&sp6C->unk2C, sp6C->unk20) == 1) {
        gameState = GAME_STATE_RESULTS;
    }
    func_8033F6F8(&sp6C->unk2C, &sp6C->unk2C);
    uvGfxBegin();
    func_8034B624(sp6C->unk70);
    uvGfxEnd();
    func_80313D74();
    if ((demoButtonPress(arg0->unk9C, START_BUTTON) != 0) && (demoButtonCheck(arg0->unk9C, A_BUTTON) == 0)) {
        if ((sp6C->unkA != 3) && (sp6C->unkA != 4)) {
            sp40 = (GyrocopterData*)sp6C->vehicleData;
            if (sp6C->veh == VEHICLE_GYROCOPTER) {
                sp4C = sp40->usingFuel;
                sp48 = sp40->unkE8;
                sp44 = sp40->unkF0;
                sp40->usingFuel = FALSE;
                sp40->unkE8 = 0.0f;
                sp40->unkF0 = 0.0f;
                func_802F50CC(sp40);
            }
            uvEventPost(0x12, 0);
            sp5C = D_8034F850;
            func_8033F964(2);

            switch (func_8032CF28(arg0)) {
            case 0:
                break;
            case 1:
                uvEventPost(0x17, 0);
                func_8032CC44(arg0);
                uvEventPost(0x18, 0);
                break;
            case 3:
                func_8032D51C(0);
                func_802ECE94(arg0);
                if (sp6C->unk7B == 0) {
                    D_8037DC84 = 1;
                }
                if (sp6C->unk7B != 0) {
                    gameState = GAME_STATE_VEHICLE_CLASS_SELECT;
                } else {
                    gameState = GAME_STATE_TEST_DETAILS;
                }
                sp6C->unk7B = 0;
                break;
            case 2:
                func_8032D51C(0);
                func_8033E3A8(1);
                if (sp6C->veh == VEHICLE_HANG_GLIDER) {
                    func_802F03C4(sp6C->vehicleData);
                }
                break;
            }
            func_8033F964(3);
            D_8034F850 = sp5C;
            uvEventPost(0x13, 0);
            if (sp6C->veh == VEHICLE_GYROCOPTER) {
                sp40->usingFuel = sp4C;
                sp40->unkE8 = sp48;
                sp40->unkF0 = sp44;
                func_802F50CC(sp40);
            }
        }
    }
    taskGet_80345CC0(&sp64, &sp60);
    if ((sp64 > 0.0f) && (sp64 < D_8034F850) && (arg0->unkA0 != 0)) {
        if ((sp6C->unkA != 3) && (sp6C->unkA != 4)) {
            hudText_8031D8E0(0xD4, 1.5f, 8.0f);
            sndPlaySfx(5);
            taskDeinit();
            arg0->unkA0 = 0;
        }
    }
    if ((sp60 > 0.0f) && (sp60 < D_8034F850)) {
        gameState = GAME_STATE_RESULTS;
        arg0->unkA1 = 1;
    }
    return gameState;
}

void func_802EDAF0(Unk80362690_Unk0* arg0, Mtx4F* arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, u16 arg7, u8 arg8, u8 arg9, u8 arg10) {
    Unk80364210* sp24;

    sp24 = func_8032BE10();
    arg0->unkC += func_8031385C(&arg0->unk2C, arg1);
    if (arg2 < arg0->unk10) {
        arg0->unk10 = arg0->unk10;
    } else {
        arg0->unk10 = arg2;
    }
    arg0->unk20 = arg3;
    arg0->unk24 = arg4;
    arg0->unk28 = arg5;
    arg0->unk7A = arg9;
    uvMat4Copy(&arg0->unk2C, arg1);
    if (arg10 == 2) {
        if ((arg3 < 0.1f) && (arg0->veh != VEHICLE_GYROCOPTER)) {
            arg0->unkA = 5;
        }
        arg0->unk14 += D_8034F854;
    }
    switch (arg10) {
    case 3:
        if (arg0->unkA == 1) {
            arg0->unk80 = D_8034F850;
            arg0->unk7C = 1;
        }
        if (arg0->unkA != 3) {
            arg0->unkA = 3;
        }
        break;
    case 4:
        if (arg0->unkA == 1) {
            arg0->unk7C = 5;
        }
        if (arg0->unkA != 4) {
            arg0->unkA = 4;
            sp24->unk3C = 1;
            arg0->unk79 = 1;
        }
        break;
    case 5:
        if (sp24->unk4 > 2.0f) {
            arg0->unkA = 5;
        }
        if (arg0->unk28 <= 0.0f) {
            arg0->unkA = 5;
        }
        break;
    }
    if ((arg8 != 0) && ((arg0->unk18 + 0.3f) < D_8034F850)) {
        arg0->unk18 = D_8034F850;
        sp24->unk30++;
    }
    if ((sp24->unk4 < 2.0f) && (sp24->unk14 < 2.0f)) {
        if (sp24->unk1C > 30.0f) {
            arg0->unkA = 5;
        }
        sp24->unk0 = 0;
    } else {
        sp24->unk0 = arg7;
        sp24->unk1C = arg6;
        sp24->unk14 = arg0->unkC;
        sp24->unk18 = arg0->unk10;
        sp24->unk10 = arg0->unk24;
        sp24->unk20 = arg0->unk28;
    }
}

void func_802EDD9C(Unk80362690_Unk0* arg0, Mtx4F* arg1) {
    arg0->unkA = 1;
    arg0->unk78 = 0;
    arg0->unk79 = 0;
    arg0->unk7A = 0;
    arg0->unk7B = 0;
    arg0->unkC = 0.0f;
    arg0->unk10 = 0.0f;
    arg0->unk14 = 0.0f;
    arg0->unk18 = 0.0f;
    arg0->unk1C = 0.0f;
    uvMat4Copy(&arg0->unk2C, arg1);
}

void func_802EDDEC(Mtx4F* arg0) {
    Mtx4F* sp54;
    Vec3F* sp50;
    u16 sp4E;
    u16 i;
    Vec3F sp40;

    switch (D_80362690->unkC[D_80362690->unk9C].veh) {
    case VEHICLE_HANG_GLIDER:
        D_803676F0 = (HangGliderData*)D_80362748[D_80362690->unk9C];
        sp54 = &D_803676F0->unk10;
        sp50 = &D_803676F0->unk308;
        sp4E = D_803676F0->objId;
        break;
    case VEHICLE_GYROCOPTER:
        D_803676F4 = (GyrocopterData*)D_80362748[D_80362690->unk9C];
        sp54 = &D_803676F4->unk10;
        sp50 = &D_803676F4->unk668;
        sp4E = D_803676F4->objId;
        for (i = 0; i < 4; i++) {
            sp40.x = D_803676F4->unk5EC[i].x;
            sp40.y = D_803676F4->unk5EC[i].y;
            sp40.z = 0.0f;
            uvMat4LocalToWorld(arg0, &D_803676F4->unk3B0[i].unk0, &sp40);
        }
        break;
    case VEHICLE_ROCKET_BELT:
        D_803676F8 = (RocketBeltData*)D_80362748[D_80362690->unk9C];
        sp54 = &D_803676F8->unk10;
        sp50 = &D_803676F8->unk374;
        sp4E = D_803676F8->objId;
        break;
    case VEHICLE_CANNONBALL:
        D_803676FC = (CannonballData*)D_80362748[D_80362690->unk9C];
        sp54 = &D_803676FC->unk14;
        sp50 = &D_803676FC->unk294;
        sp4E = D_803676FC->objId;
        break;
    case VEHICLE_SKY_DIVING:
        D_80367700 = (SkyDivingData*)D_80362748[D_80362690->unk9C];
        sp54 = &D_80367700->unk10;
        sp50 = &D_80367700->unk230;
        sp4E = D_80367700->objId;
        break;
    case VEHICLE_JUMBLE_HOPPER:
        D_80367708 = (JumbleHopperData*)D_80362748[D_80362690->unk9C];
        sp54 = &D_80367708->unk74;
        sp50 = &D_80367708->unk670;
        sp4E = D_80367708->objId;
        break;
    case VEHICLE_BIRDMAN:
        D_80367704 = (BirdmanData*)D_80362748[D_80362690->unk9C];
        sp54 = &D_80367704->unk10;
        sp50 = &D_80367704->unk400;
        sp4E = D_80367704->objId;
        break;
    }
    uvMat4Copy(sp54, arg0);
    sp50->x = arg0->m[3][0];
    sp50->y = arg0->m[3][1];
    sp50->z = arg0->m[3][2];
    uvDobjPosm(sp4E, 0, sp54);
    func_802D4ECC(D_80362690->unkC[D_80362690->unk9C].unk70, arg0);
}

void func_802EE14C(u16 veh) {
    s32 sp44;
    Unk80362690_Unk0* temp_s0;
    f32 sp3C;
    Vec3F sp30;

    temp_s0 = &D_80362690->unkC[D_80362690->unk9C];
    sp44 = 1;
    sp3C = 1.0f;
    if (veh == temp_s0->veh) {
        return;
    }
    uvEventPost(0xD, &sp44);
    switch (temp_s0->veh) {
    case VEHICLE_HANG_GLIDER:
        func_802EF328(temp_s0->vehicleData);
        break;
    case VEHICLE_GYROCOPTER:
        func_802F5F80(temp_s0->vehicleData);
        break;
    case VEHICLE_ROCKET_BELT:
        func_80325100(temp_s0->vehicleData);
        break;
    case VEHICLE_CANNONBALL:
        cannonEndTarget(temp_s0->vehicleData);
        break;
    case VEHICLE_SKY_DIVING:
        func_8032FE4C(temp_s0->vehicleData);
        break;
    case VEHICLE_JUMBLE_HOPPER:
        func_802FA290(temp_s0->vehicleData);
        break;
    case VEHICLE_BIRDMAN:
        bird_802CC51C(temp_s0->vehicleData);
        break;
    }
    temp_s0->veh = veh;
    levelComputeAppend(temp_s0->pilot, temp_s0->veh);
    taskBirdmanPad(temp_s0->cls);
    hudGetState()->renderFlags = 0;
    temp_s0->unk8 = 0;
    D_80362690->terraId = task_80346370(temp_s0->unk8);
    D_80362690->unkA0 = 0;
    uvChanTerra(temp_s0->unk70->unk22C, D_80362690->terraId);
    taskDeinit();
    thermDeinit();
    windDeinit();
    padsInitLandingPads();
    sp30.x = sp30.y = sp30.z = 0.0f;
    env_802E14E8(&sp30, 0.0f, 0.0f, 0.0f, 0.0f);
    switch (temp_s0->veh) {
    case VEHICLE_HANG_GLIDER:
        D_803676F0 = (HangGliderData*)temp_s0->vehicleData;
        hangGliderLoadLevel(D_80362690->unk9C, temp_s0->pilot, D_803676F0, temp_s0->unk70);
        hangGliderEnterLeave(D_803676F0);
        func_8033F748(4);
        sp3C = 0.5f;
        break;
    case VEHICLE_GYROCOPTER:
        D_803676F4 = (GyrocopterData*)temp_s0->vehicleData;
        gyrocopterLoadLevel(D_80362690->unk9C, temp_s0->pilot, D_803676F4, temp_s0->unk70);
        gyrocopterEnterLeave(D_803676F4);
        func_8033F748(0xC);
        break;
    case VEHICLE_ROCKET_BELT:
        D_803676F8 = (RocketBeltData*)temp_s0->vehicleData;
        rocketBeltLoadLevel(D_80362690->unk9C, temp_s0->pilot, D_803676F8, temp_s0->unk70);
        rocketBeltEnterLeave(D_803676F8);
        func_8033F748(8);
        sp3C = 0.5f;
        break;
    case VEHICLE_SKY_DIVING:
        D_80367700 = (SkyDivingData*)temp_s0->vehicleData;
        skydivingLoadLevel(D_80362690->unk9C, temp_s0->pilot, D_80367700, temp_s0->unk70);
        skydivingEnterLeave(D_80367700);
        func_8033F748(0x13);
        sp3C = 0.5f;
        break;
    case VEHICLE_JUMBLE_HOPPER:
        D_80367708 = (JumbleHopperData*)temp_s0->vehicleData;
        jumbleHopperLoadLevel(D_80362690->unk9C, temp_s0->pilot, D_80367708, temp_s0->unk70);
        jumbleHopperEnterLeave(D_80367708);
        func_8033F748(0x17);
        sp3C = 0.5f;
        break;
    case VEHICLE_BIRDMAN:
        D_80367704 = (BirdmanData*)temp_s0->vehicleData;
        birdLoadLevel(D_80362690->unk9C, temp_s0->pilot, D_80367704, temp_s0->unk70);
        birdEnterLeave(D_80367704);
        func_802EDD9C(temp_s0, &D_80367704->unk10);
        func_8033F748(0x19);
        uvLevelAppend(0x1B);
        break;
    }
    func_8033F964(1);
    func_8032D51C(1);
    func_8033F964(0);
    func_8033FCD0(temp_s0->veh);
    hud_8031DAA8(2, 1.0f);
    fdrSetBlen(sp3C);
    fdr_802E68B0(1);
    temp_s0->unk7B = 1;
}
