#include "common.h"
#include "jumble_hopper.h"
#include <uv_memory.h>
#include <uv_model.h>
#include "app/hud.h"
#include "app/demo.h"
#include "app/fdr.h"
#include "app/shadow.h"
#include "app/snd.h"
#include "app/task.h"
#include "app/camera.h"
#include "app/code_82B90.h"
#include "app/code_9A960.h"
#include "app/code_D1ED0.h"

Unk803599D0 D_80368B20;

void jumbleHopperLoadPilot(u8 pilot, JumbleHopperData* jhData);

void jumbleHopperInit(void) {
    D_80368B20.count = 8;
    D_80368B20.unk4[0].x = 0.0f, D_80368B20.unk4[0].y = 0.0f;
    D_80368B20.unk4[1].x = 0.2f, D_80368B20.unk4[1].y = 0.04f;
    D_80368B20.unk4[2].x = 0.4f, D_80368B20.unk4[2].y = 0.16f;
    D_80368B20.unk4[3].x = 0.6f, D_80368B20.unk4[3].y = 0.36f;
    D_80368B20.unk4[4].x = 0.7f, D_80368B20.unk4[4].y = 0.49f;
    D_80368B20.unk4[5].x = 0.8f, D_80368B20.unk4[5].y = 0.64f;
    D_80368B20.unk4[6].x = 0.9f, D_80368B20.unk4[6].y = 0.81f;
    D_80368B20.unk4[7].x = 1.0f, D_80368B20.unk4[7].y = 1.0f;
}

void jumbleHopperLoadLevel(u8 contIdx, u8 pilot, JumbleHopperData* jhData, Camera* camera) {
    uvMemSet(jhData, 0, sizeof(JumbleHopperData));
    jumbleHopperLoadPilot(pilot, jhData);
    jhData->objId = uvDobjAllocIdx();
    jhData->unk2 = 2;
    uvDobjModel(jhData->objId, jhData->modelId);
    uvDobjPosm(jhData->objId, 0, &jhData->unk74);
    uvDobjState(jhData->objId, jhData->unk2);
    shadow_80334454(MODEL_WORLD, MODEL_JUMBLEH_SHADOW);
    shadow_803342F0(0.0f);
    shadow_803342FC(0.0f);
    jhData->contIdx = contIdx;
    jhData->camera = camera;
    jhData->unk65E[0] = 0;
    jhData->unk4 = 0xFFFF;
    jhData->unk664 = 0.0f;
    jhData->unk66C = 0.0f;
    jhData->unk668 = 0.0f;
    jhData->unk3C = 0.0f;
    jhData->unk40 = 0.0f;
    func_802FD038(jhData);
}

void jumbleHopperEnterLeave(JumbleHopperData* jhData) {
    func_802FD114(jhData);
    jhData->unk4C = 0;
    jhData->unk2 = 2;
    jhData->unk534 = 0;
    jhData->unk538 = 0;
    jhData->unk3C = 0.0f;
    jhData->unk40 = 0.0f;
    jhData->unk8 = 0.0f;
    jhData->unk48 = 0.7f;
    jhData->unk44 = 9;
    jhData->camera->unk108.m[3][2] = 0.0f;
    jhData->camera->unk1380 = 0.0f;
    jhData->camera->unk1374 = 5.0f;
    jhData->camera->unk137C = 0;
    jhData->camera->unk1 = jhData->unk44;
    jhData->camera->unk4 = jhData->objId;
    jhData->camera->unk6 = jhData->unk2;
    jhData->camera->unk0 = 0x68;
    jhData->camera->unk1B4 = 6.0f;
    uvModelGetProps(jhData->modelId, MODEL_PROP_UNK1(&jhData->camera->unk8), MODEL_PROP_END);
    jhData->camera->unk68.x = jhData->unk630.x;
    jhData->camera->unk68.y = jhData->unk630.y;
    jhData->camera->unk68.z = jhData->unk630.z;
    jhData->camera->unk74 = 0.0f;
    jhData->camera->unk5C = 0;
    jhData->camera->unk60 = -5.0f;
    jhData->camera->unk64 = 0;
    jhData->camera->unk54 = 2.0f;
    jhData->camera->unk58 = 6.0f;
    jhData->camera->unk48 = 0.1f;
    jhData->camera->unk4C = 1.0f;
    jhData->camera->unk50 = 0.0f;
    func_802D45C4(jhData->camera, jhData->unk48);
}

void func_802FA290(JumbleHopperData* jhData) {
    uvDobjModel(jhData->objId, MODEL_WORLD);
    jhData->contIdx = 0xFFFF;
    jhData->objId = 0xFFFF;
    shadow_80334C70();
}

void jumbleHopperMovementFrame(JumbleHopperData* jhData, u8 gameState) {
    f32 xAxisInputs;
    f32 yAxisInputs;
    f32 var_fa0;
    s32 buttons;
    HUDState* hud;
    Mtx4F sp34;

    if (fdr_802E6B5C() != 4) {
        if (gameState == GAME_STATE_RESULTS) {
            fdr_802E65AC(&jhData->unk74, &D_80362690->terraId, &xAxisInputs, &yAxisInputs, &buttons);
        } else {
            xAxisInputs = demoGetInputs(jhData->contIdx, INPUT_AXIS_X);
            yAxisInputs = demoGetInputs(jhData->contIdx, INPUT_AXIS_Y);
            buttons = demoGetButtons(jhData->contIdx);
        }
        jhData->unk8 += D_8034F854;
        jhData->unk10 = func_80313F08(&D_80368B20, FABS(yAxisInputs));
        if (yAxisInputs < 0) {
            jhData->unk10 = -jhData->unk10;
        }
        jhData->unk14 = func_80313F08(&D_80368B20, FABS(xAxisInputs));
        if (xAxisInputs < 0) {
            jhData->unk14 = -jhData->unk14;
        }
        if ((buttons & A_BUTTON) && ((jhData->unk50 == 0) || (jhData->unk19C != 0))) {
            jhData->unk19C = 1;
        } else {
            jhData->unk19C = 0;
        }
        if (gameState != GAME_STATE_RESULTS) {
            func_80303028(jhData);
        }
        if (buttons & L_CBUTTONS) {
            var_fa0 = 1.5707963f;
        } else if (buttons & R_CBUTTONS) {
            var_fa0 = -1.5707963f;
        } else {
            var_fa0 = 0.0f;
        }
        jhData->unk3C = func_80313AF4(var_fa0, jhData->unk3C, 2.0f);
        if (buttons & D_CBUTTONS) {
            var_fa0 = 1.5707963f;
        } else if (buttons & U_CBUTTONS) {
            var_fa0 = -1.5707963f;
        } else {
            var_fa0 = 0.0f;
        }
        jhData->unk40 = func_80313AF4(var_fa0, jhData->unk40, 2.0f);
        if (demoButtonPress(jhData->contIdx, R_TRIG) != 0) {
            if ((jhData->unk44 == 9) && (jhData->camera->unk137C == 0)) {
                sndPlaySfxVolPitchPan(0x6A, 1.0f, 0.5f, 0.0f);
                jhData->unk44 = 9;
                jhData->camera->unk137C = 1;
            } else {
                sndPlaySfxVolPitchPan(0x6A, 1.0f, 0.5f, 0.0f);
                jhData->unk44 = 9;
                jhData->camera->unk137C = 0;
            }
        }
        if (gameState != GAME_STATE_RESULTS) {
            jhData->camera->unk4 = jhData->objId;
            jhData->camera->unk6 = jhData->unk2;
            jhData->camera->unk7C = jhData->unk40;
            jhData->camera->unk78 = jhData->unk3C;
            jhData->camera->unk228 = jhData->unk64;
            func_8034AD6C(jhData->unk140.x, 0.0f, 0.0f, &sp34);
            sp34.m[3][0] = jhData->unkF4.x;
            sp34.m[3][1] = jhData->unkF4.y;
            sp34.m[3][2] = jhData->unkF4.z + 1.0f;
            uvMat4Copy(&jhData->camera->unk80, &sp34);
            jhData->camera->unkC0 = jhData->unk140.x;
            jhData->camera->unkC4 = jhData->unk15C.z;
            if ((jhData->unk4C == 5) || (jhData->unk4C == 9) || (jhData->unk4C == 4) || (jhData->unk4C == 6) || (jhData->unk4C == 7) || (jhData->unk4C == 8)) {
                func_802D5884(jhData->camera, 6);
            } else {
                func_802D5884(jhData->camera, jhData->unk44);
            }
            func_802D45C4(jhData->camera, jhData->unk48);
        }
        if (gameState != GAME_STATE_RESULTS) {
            hud = hudGetState();
            uvMat4Copy(&hud->unk28, &jhData->unk74);
            hud->renderFlags = HUD_RENDER_JUMBLE_HOPPER;
            hud->att.heading = jhData->unk74.m[3][2];
            hud->elapsedTime = jhData->unk8;
            hud->unk8C = jhData->unk15C.z * 4.0f * 0.7f;
            hud->altitude = jhData->unk64 * 0.7f;
            hud->altSeaLevel = jhData->unk74.m[3][2] * 0.7f;
            hud->speed = jhData->unk180 * 3.6f * 0.7f;
        }
        if (gameState != GAME_STATE_RESULTS) {
            if (jhData->unk4C == 6) {
                fdr_802E66DC();
            }
            fdr_802E65AC(&jhData->unk74, &D_80362690->terraId, &xAxisInputs, &yAxisInputs, &buttons);
        }
    }
}

void jumbleHopperLoadPilot(u8 pilot, JumbleHopperData* jhData) {
    switch (pilot) {
    case PILOT_LARK:
        jhData->unk5E8.x = 0.0f, jhData->unk5E8.y = 0.0f, jhData->unk5E8.z = 0.7f;
        jhData->unk5F4.x = 0.0f, jhData->unk5F4.y = 0.0f, jhData->unk5F4.z = -0.745f;
        jhData->unk600.x = 0.0f, jhData->unk600.y = 0.45f, jhData->unk600.z = 0.0f;
        jhData->unk60C.x = 0.0f, jhData->unk60C.y = -0.25f, jhData->unk60C.z = 0.0f;
        jhData->unk618.x = -0.3f, jhData->unk618.y = 0.0f, jhData->unk618.z = 0.0f;
        jhData->unk624.x = 0.3f, jhData->unk624.y = 0.0f, jhData->unk624.z = 0.0f;
        jhData->unk630.x = -0.025f, jhData->unk630.y = 0.307f, jhData->unk630.z = 0.478f;
        jhData->unk63C = 0.504f;
        jhData->unk640 = 0.206f;
        jhData->unk644 = 0.169f;
        jhData->unk648 = 0.2f;
        jhData->unk64C = 0.6f;
        jhData->modelId = MODEL_JUMBLEH_LARK;
        jhData->unk65C = 7;
        jhData->unk65B = 1;
        jhData->unk650 = 5;
        jhData->unk651 = 3;
        jhData->unk652 = 6;
        jhData->unk653 = 4;
        jhData->unk654 = 8;
        jhData->unk655 = 9;
        jhData->unk656 = 10;
        jhData->unk657 = 11;
        jhData->unk658 = 12;
        jhData->unk659 = 13;
        jhData->unk65A = 2;
        break;
    case PILOT_GOOSE:
        jhData->unk5E8.x = 0.0f, jhData->unk5E8.y = 0.0f, jhData->unk5E8.z = 0.8f;
        jhData->unk5F4.x = 0.0f, jhData->unk5F4.y = 0.0f, jhData->unk5F4.z = -1.336f;
        jhData->unk600.x = 0.0f, jhData->unk600.y = 0.6f, jhData->unk600.z = 0.0f;
        jhData->unk60C.x = 0.0f, jhData->unk60C.y = 0.35f, jhData->unk60C.z = 0.0f;
        jhData->unk618.x = -0.35f, jhData->unk618.y = 0.0f, jhData->unk618.z = 0.0f;
        jhData->unk624.x = 0.35f, jhData->unk624.y = 0.0f, jhData->unk624.z = 0.0f;
        jhData->unk630.x = 0.0f, jhData->unk630.y = 0.315f, jhData->unk630.z = 0.603f;
        jhData->unk63C = 0.18100001f;
        jhData->unk640 = 0.527f;
        jhData->unk644 = 0.476f;
        jhData->unk648 = 0.5f;
        jhData->unk64C = 0.6f;
        jhData->modelId = MODEL_JUMBLEH_GOOSE;
        jhData->unk65C = 7;
        jhData->unk65B = 1;
        jhData->unk650 = 5;
        jhData->unk651 = 3;
        jhData->unk652 = 6;
        jhData->unk653 = 4;
        jhData->unk654 = 11;
        jhData->unk655 = 12;
        jhData->unk656 = 13;
        jhData->unk657 = 8;
        jhData->unk658 = 9;
        jhData->unk659 = 10;
        jhData->unk65A = 2;
        break;
    case PILOT_HAWK:
        jhData->unk5E8.x = 0.0f, jhData->unk5E8.y = 0.0f, jhData->unk5E8.z = 0.7f;
        jhData->unk5F4.x = 0.0f, jhData->unk5F4.y = 0.0f, jhData->unk5F4.z = -1.0f;
        jhData->unk600.x = 0.0f, jhData->unk600.y = 0.65f, jhData->unk600.z = 0.0f;
        jhData->unk60C.x = 0.0f, jhData->unk60C.y = -0.3f, jhData->unk60C.z = 0.0f;
        jhData->unk618.x = -0.5f, jhData->unk618.y = 0.0f, jhData->unk618.z = 0.0f;
        jhData->unk624.x = 0.5f, jhData->unk624.y = 0.0f, jhData->unk624.z = 0.0f;
        jhData->unk630.x = 0.002f, jhData->unk630.y = 0.325f, jhData->unk630.z = 0.52f;
        jhData->unk63C = 0.186f;
        jhData->unk640 = 0.381f;
        jhData->unk644 = 0.378f;
        jhData->unk648 = 0.3f;
        jhData->unk64C = 0.6f;
        jhData->modelId = MODEL_JUMBLEH_HAWK;
        jhData->unk65C = 7;
        jhData->unk65B = 1;
        jhData->unk650 = 3;
        jhData->unk651 = 5;
        jhData->unk652 = 4;
        jhData->unk653 = 6;
        jhData->unk654 = 8;
        jhData->unk655 = 9;
        jhData->unk656 = 10;
        jhData->unk657 = 11;
        jhData->unk658 = 12;
        jhData->unk659 = 13;
        jhData->unk65A = 2;
        break;
    case PILOT_KIWI:
        jhData->unk5E8.x = 0.0f, jhData->unk5E8.y = 0.0f, jhData->unk5E8.z = 0.7f;
        jhData->unk5F4.x = 0.0f, jhData->unk5F4.y = 0.0f, jhData->unk5F4.z = -1.0f;
        jhData->unk600.x = 0.0f, jhData->unk600.y = 0.45f, jhData->unk600.z = 0.0f;
        jhData->unk60C.x = 0.0f, jhData->unk60C.y = -0.3f, jhData->unk60C.z = 0.0f;
        jhData->unk618.x = -0.3f, jhData->unk618.y = 0.0f, jhData->unk618.z = 0.0f;
        jhData->unk624.x = 0.3f, jhData->unk624.y = 0.0f, jhData->unk624.z = 0.0f;
        jhData->unk630.x = 0.002f, jhData->unk630.y = 0.308f, jhData->unk630.z = 0.473f;
        jhData->unk63C = 0.334f;
        jhData->unk640 = 0.233f;
        jhData->unk644 = 0.297f;
        jhData->unk648 = .3f;
        jhData->unk64C = 0.6f;
        jhData->modelId = MODEL_JUMBLEH_KIWI;
        jhData->unk65C = 9;
        jhData->unk65B = 1;
        jhData->unk650 = 7;
        jhData->unk651 = 5;
        jhData->unk652 = 8;
        jhData->unk653 = 6;
        jhData->unk654 = 13;
        jhData->unk655 = 14;
        jhData->unk656 = 15;
        jhData->unk657 = 10;
        jhData->unk658 = 11;
        jhData->unk659 = 12;
        jhData->unk65A = 2;
        break;
    case PILOT_IBIS:
        jhData->unk5E8.x = 0.0f, jhData->unk5E8.y = 0.0f, jhData->unk5E8.z = 0.8f;
        jhData->unk5F4.x = .0f, jhData->unk5F4.y = 0.0f, jhData->unk5F4.z = -1.0f;
        jhData->unk600.x = 0.0f, jhData->unk600.y = 0.55f, jhData->unk600.z = 0.0f;
        jhData->unk60C.x = 0.0f, jhData->unk60C.y = -0.45f, jhData->unk60C.z = 0.0f;
        jhData->unk618.x = -0.35f, jhData->unk618.y = 0.0f, jhData->unk618.z = 0.0f;
        jhData->unk624.x = 0.35f, jhData->unk624.y = 0.0f, jhData->unk624.z = 0.0f;
        jhData->unk630.x = 0.0f, jhData->unk630.y = 0.212f, jhData->unk630.z = 0.599f;
        jhData->unk63C = 0.71500003f;
        jhData->unk640 = 0.526f;
        jhData->unk644 = 0.427f;
        jhData->unk648 = .3f;
        jhData->unk64C = 0.6f;
        jhData->modelId = MODEL_JUMBLEH_IBIS;
        jhData->unk65C = 7;
        jhData->unk65B = 1;
        jhData->unk650 = 3;
        jhData->unk651 = 5;
        jhData->unk652 = 4;
        jhData->unk653 = 6;
        jhData->unk654 = 11;
        jhData->unk655 = 12;
        jhData->unk656 = 13;
        jhData->unk657 = 8;
        jhData->unk658 = 9;
        jhData->unk659 = 10;
        jhData->unk65A = 2;
        break;
    case PILOT_ROBIN:
        jhData->unk5E8.x = 0.0f, jhData->unk5E8.y = 0.0f, jhData->unk5E8.z = 0.85f;
        jhData->unk5F4.x = 0.0f, jhData->unk5F4.y = 0.0f, jhData->unk5F4.z = -1.0f;
        jhData->unk600.x = 0.0f, jhData->unk600.y = 0.5f, jhData->unk600.z = 0.0f;
        jhData->unk60C.x = 0.0f, jhData->unk60C.y = -0.45f, jhData->unk60C.z = 0.0f;
        jhData->unk618.x = -0.35f, jhData->unk618.y = 0.0f, jhData->unk618.z = 0.0f;
        jhData->unk624.x = 0.35f, jhData->unk624.y = 0.0f, jhData->unk624.z = 0.0f;
        jhData->unk630.x = 0.0f, jhData->unk630.y = 0.217f, jhData->unk630.z = 0.621f;
        jhData->unk63C = 0.502f;
        jhData->unk640 = 0.508f;
        jhData->unk644 = 0.28f;
        jhData->unk648 = .3f;
        jhData->unk64C = 0.6f;
        jhData->modelId = MODEL_JUMBLEH_ROBIN;
        jhData->unk65C = 7;
        jhData->unk65B = 1;
        jhData->unk650 = 3;
        jhData->unk651 = 5;
        jhData->unk652 = 4;
        jhData->unk653 = 6;
        jhData->unk654 = 8;
        jhData->unk655 = 9;
        jhData->unk656 = 10;
        jhData->unk657 = 11;
        jhData->unk658 = 12;
        jhData->unk659 = 13;
        jhData->unk65A = 2;
        break;
    default:
        break;
    }
}
