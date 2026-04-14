#include "common.h"
#include "rocket_belt.h"
#include <uv_memory.h>
#include <uv_model.h>
#include "app/demo.h"
#include "app/fdr.h"
#include "app/hud.h"
#include "app/shadow.h"
#include "app/snd.h"
#include "app/text_data.h"
#include "app/code_66F70.h"
#include "app/code_9A960.h"
#include "app/code_B2900.h"

Unk803599D0 D_80371070;
Unk803599D0 D_803710C8;

void rocketBeltLoadPilot(u8 pilot, RocketBeltData*);
void func_80326E40(RocketBeltData*);

void rocketBeltInit(void) {
    D_80371070.count = 8;
    D_80371070.unk4[0].x = 0.0f, D_80371070.unk4[0].y = 0.0f;
    D_80371070.unk4[1].x = 0.2f, D_80371070.unk4[1].y = 0.0f;
    D_80371070.unk4[2].x = 0.4f, D_80371070.unk4[2].y = 0.04f;
    D_80371070.unk4[3].x = 0.6f, D_80371070.unk4[3].y = 0.12f;
    D_80371070.unk4[4].x = 0.7f, D_80371070.unk4[4].y = 0.24f;
    D_80371070.unk4[5].x = 0.8f, D_80371070.unk4[5].y = 0.36f;
    D_80371070.unk4[6].x = 0.9f, D_80371070.unk4[6].y = 0.65f;
    D_80371070.unk4[7].x = 1.0f, D_80371070.unk4[7].y = 1.0f;
    D_803710C8.count = 8;
    D_803710C8.unk4[0].x = 0.0f, D_803710C8.unk4[0].y = 0.0f;
    D_803710C8.unk4[1].x = 0.2f, D_803710C8.unk4[1].y = 0.04f;
    D_803710C8.unk4[2].x = 0.4f, D_803710C8.unk4[2].y = 0.16f;
    D_803710C8.unk4[3].x = 0.6f, D_803710C8.unk4[3].y = 0.36f;
    D_803710C8.unk4[4].x = 0.7f, D_803710C8.unk4[4].y = 0.49f;
    D_803710C8.unk4[5].x = 0.8f, D_803710C8.unk4[5].y = 0.64f;
    D_803710C8.unk4[6].x = 0.9f, D_803710C8.unk4[6].y = 0.81f;
    D_803710C8.unk4[7].x = 1.0f, D_803710C8.unk4[7].y = 1.0f;
}

void rocketBeltLoadLevel(u8 contIdx, u8 pilot, RocketBeltData* rbData, Camera* camera) {
    uvMemSet(rbData, 0, sizeof(RocketBeltData));
    rocketBeltLoadPilot(pilot, rbData);
    shadow_80334454(MODEL_RB_SHADOW_COLUMN, MODEL_RB_SHADOW);
    shadow_803342F0(0.0f);
    shadow_803342FC(rbData->unk25C.z + 0.1f);
    shadow_803343D8(1);
    rbData->unk6 = uvDobjAllocIdx();
    uvDobjModel(rbData->unk6, MODEL_MULTI_COLORED_CUBE);
    uvDobjState(rbData->unk6, 0x22);
    rbData->objId = uvDobjAllocIdx();
    rbData->unk2 = 2;
    uvDobjModel(rbData->objId, rbData->modelId);
    uvDobjPosm(rbData->objId, 0, &rbData->unk10);
    uvDobjState(rbData->objId, rbData->unk2);
    rbData->contIdx = contIdx;
    rbData->camera = camera;
    rbData->unk4 = 0xFFFF;
    func_80326F30(rbData);
    func_80328420(rbData);
    rbSoundInit(rbData);
}

void rocketBeltEnterLeave(RocketBeltData* rbData) {
    Vec3F sp44;
    Vec3F sp38;
    u8 sp37;
    s32 sp30;

    db_getstart(&rbData->unk10, &rbData->unk1DC, &sp37, &rbData->unkF8);
    uvDobjPosm(rbData->objId, 0, &rbData->unk10);
    if (sp37 != 0) {
        rbData->unk90 = 0;
        rbData->unkE9 = 0;
    } else {
        rbData->unk90 = 1;
        rbData->unkE9 = 1;
    }
    if (rbData->unk90 != 0) {
        sp30 = 1;
        sp44.x = sp38.x = rbData->unk10.m[3][0];
        sp44.y = sp38.y = rbData->unk10.m[3][1];
        sp44.z = rbData->unk10.m[3][2] + 0.5f;
        sp38.z = rbData->unk10.m[3][2] - 0.5f;
        db_getgnd(&sp44, &sp38, &sp30, &rbData->unk100, &rbData->unk104, &rbData->unk108);
        rbData->unkE9 = 1;
        rbData->unk10.m[3][2] = rbData->unk104 - rbData->unk25C.z;
    } else {
        rbData->unkE9 = 0;
    }
    func_80328538(rbData);
    rbData->unk80 = 0;
    rbData->unk33B = 0;
    rbData->unkEB = 0;
    rbData->unkEC = 0;
    rbData->unkED = 0;
    rbData->unkEE = 0;
    rbData->unkEA = 0;
    rbData->unkEF = 1;
    rbData->unk2 = 2;
    rbData->unk88 = 0.0f;
    rbData->unk8C = 0.0f;
    rbData->unk344 = 0.0f;
    rbData->unk34C = 0.0f;
    rbData->unk354 = 0.0f;
    rbData->unk350 = 0.0f;
    rbData->unk348 = 0.0f;
    rbData->unk358 = 0.0f;
    rbData->unk33C = 0.0f;
    rbData->unk8 = 0.0f;
    rbData->unk68 = 0.0f;
    rbData->unk6C = 0.0f;
    rbData->unk35C = 0.0f;
    rbData->unk360 = 0.0f;
    rbData->unk364 = 0.0f;
    rbData->unk368 = 0.0f;
    rbData->unk36C = 0.0f;
    rbData->unk370 = 0.0f;
    func_80326E40(rbData);
    rbData->unk5C = 4;
    rbData->unk60 = 0.8f;
    rbData->unk54 = 0.0f;
    rbData->unk58 = 0.0f;
    rbData->camera->unk0 = 0x6C;
    rbData->camera->unk1 = 4;
    rbData->camera->unk4 = rbData->objId;
    rbData->camera->unk6 = rbData->unk2;
    rbData->camera->unk68.x = rbData->unk2B0;
    rbData->camera->unk68.y = rbData->unk2B4;
    rbData->camera->unk68.z = rbData->unk2B8;
    rbData->camera->unk74 = 0.0f;
    rbData->camera->unk1B4 = 6.0f;
    uvModelGetProps(rbData->modelId, MODEL_PROP_UNK1(&rbData->camera->unk8), MODEL_PROP_END);
    func_802D45C4(rbData->camera, rbData->unk60);
}

void func_80325100(RocketBeltData* rbData) {
    uvDobjModel(rbData->objId, MODEL_WORLD);
    rbData->contIdx = -1;
    rbData->objId = 0xFFFF;
    uvDobjModel(rbData->unk6, MODEL_WORLD);
    rbData->unk6 = 0xFFFF;
    func_80327380(rbData);
    shadow_80334C70();
}

void rocketBeltMovementFrame(RocketBeltData* rbData, u8 gameState) {
    f32 spB4;
    f32 var_fv0_3;
    HUDState* hud;
    Mtx4F sp6C;
    f32 stickX;
    f32 stickY;
    s32 buttons;
    u16 sp5E;
    u16 sp5C;
    u16 sp5A;
    u8 sp59;
    f32 sp3C[7];

    if (rbData->unk90 == 3) {
        func_80325E1C(rbData);
        return;
    }
    if (fdr_802E6B5C() != 4) {
        shadow_803343D8(1);
        if (gameState == GAME_STATE_RESULTS) {
            fdr_802E65AC(&rbData->unk10, &D_80362690->terraId, &stickX, &stickY, &buttons);
        } else {
            stickX = demoGetInputs(rbData->contIdx, INPUT_AXIS_X);
            stickY = demoGetInputs(rbData->contIdx, INPUT_AXIS_Y);
            buttons = demoGetButtons(rbData->contIdx);
        }
        rbData->unk68 = stickX;
        rbData->unk6C = stickY;
        if ((rbData->unk8 > 0.0f) || (buttons & (A_BUTTON | B_BUTTON))) {
            rbData->unk8 += D_8034F854;
        }

        rbData->unk70 = func_80313F08(&D_80371070, ABS_NOEQ(stickX));
        if (stickX < 0.0f) {
            rbData->unk70 = -rbData->unk70;
        }

        rbData->unk74 = func_80313F08(&D_803710C8, ABS_NOEQ(stickY));
        if (stickY < 0.0f) {
            rbData->unk74 = -rbData->unk74;
        }
        rbData->unk81 = 0;
        rbData->unk80 = 0;
        if (buttons & Z_TRIG) {
            if (rbData->unkF8 > 0.0f) {
                rbData->unk80 = 1;
            }
            rbData->unk81 = 3;
            spB4 = 0.0f;
            var_fv0_3 = 18.0f;
        } else if (buttons & A_BUTTON) {
            spB4 = 2.0f;
            var_fv0_3 = 18.0f;
            rbData->unk81 = 1;
        } else if (buttons & B_BUTTON) {
            spB4 = 1.0f;
            var_fv0_3 = 18.0f;
            rbData->unk81 = 2;
        } else {
            var_fv0_3 = 12.0f;
            spB4 = 0.0f;
        }
        if (rbData->unkF8 > 0.0f) {
            rbData->unk78 = func_80313AF4(spB4, rbData->unk78, var_fv0_3);
        } else {
            rbData->unk78 = 0.0f;
        }
        if ((demoButtonPress(rbData->contIdx, R_TRIG) != 0) && (gameState != GAME_STATE_RESULTS)) {
            if (rbData->unk5C != 1) {
                if (rbData->unk58 == 1.5707961f) {
                    rbData->unk58 = 0.0f;
                } else {
                    rbData->unk58 = 1.5707961f;
                }
            }
            rbData->unk5C = 4;
            rbData->unk60 = 0.8f;
            if (gameState != GAME_STATE_RESULTS) {
                sndPlaySfxVolPitchPan(0x67, 0.3f, 0.65f, 0.0f);
            }
            func_802D5884(rbData->camera, rbData->unk5C);
            func_802D45C4(rbData->camera, rbData->unk60);
        }
        if (gameState != GAME_STATE_RESULTS) {
            if ((rbData->unk90 == 2) || (rbData->unk90 == 3)) {
                func_802D5884(rbData->camera, 6);
            } else {
                func_802D5884(rbData->camera, rbData->unk5C);
            }
            func_802D45C4(rbData->camera, rbData->unk60);
        }
        if (rbData->unkEF == 0) {
            if (buttons & 2) {
                spB4 += 2.0f;
            } else if (buttons & 1) {
                spB4 += -2.0f;
            } else {
                spB4 = 0.0f;
            }
            rbData->unk88 = func_80313AF4(spB4, rbData->unk88, 3.0f);
            if (demoButtonPress(rbData->contIdx, D_CBUTTONS) != 0) {
                if ((gameState != GAME_STATE_RESULTS) && (rbData->unk58 > -1.5707961f)) {
                    sndPlaySfxVolPitchPan(0x67, 0.3f, 1.0f, 0.0f);
                }
                rbData->unk58 -= 0.39269903f;
                rbData->unk58 = MAX(rbData->unk58, -1.5707961f);
            }
            if (demoButtonPress(rbData->contIdx, U_CBUTTONS) != 0) {
                if ((gameState != GAME_STATE_RESULTS) && (rbData->unk58 < 1.5707961f)) {
                    sndPlaySfxVolPitchPan(0x67, 0.3f, 1.0f, 0.0f);
                }
                rbData->unk58 += 0.39269903f;
                rbData->unk58 = MIN(rbData->unk58, 1.5707961f);
            }
            rbData->unk8C = -rbData->unk54;
        } else {
            if (demoButtonPress(rbData->contIdx, U_CBUTTONS) != 0) {
                if ((gameState != GAME_STATE_RESULTS) && (rbData->unk58 < 1.4835297f)) {
                    sndPlaySfxVolPitchPan(0x67, 0.3f, 1.0f, 0.0f);
                }
                rbData->unk58 += 0.39269903f;
                rbData->unk58 = MIN(rbData->unk58, 1.5707961f);
            }
            if (demoButtonPress(rbData->contIdx, D_CBUTTONS) != 0) {
                if ((gameState != GAME_STATE_RESULTS) && (rbData->unk58 > -1.4835297f)) {
                    sndPlaySfxVolPitchPan(0x67, 0.3f, 1.0f, 0.0f);
                }
                rbData->unk58 -= 0.39269903f;
                rbData->unk58 = MAX(rbData->unk58, -1.5707961f);
            }
            if (buttons & 2) {
                spB4 = 2.0f;
            } else if (buttons & 1) {
                spB4 = -2.0f;
            } else {
                spB4 = 0.0f;
            }
            rbData->unk88 = func_80313AF4(spB4, rbData->unk88, 3.0f);
            rbData->unk8C = 0.0f;
        }
        if (gameState != GAME_STATE_RESULTS) {
            func_8032867C(rbData);
        }
        if (rbData->unk90 == 3) {
            fdr_802E66DC();
        }
        if (gameState != GAME_STATE_RESULTS) {
            sp59 = 0;
            if (rbData->unk80 != 0) {
                sp59 = 1;
            }
            if (rbData->unkF8 > 0.0f) {
                sp59 += 2;
            }
            sp3C[0] = rbData->unk78;
            sp3C[1] = rbData->unk7C;
            sp3C[2] = rbData->unk344;
            sp3C[3] = rbData->unk34C;
            sp3C[4] = rbData->unk350;
            sp3C[5] = rbData->unk354;
            sp3C[6] = rbData->unk358;
            fdr_802E682C(sp3C, ARRAY_COUNT(sp3C), sp59);
        } else {
            fdr_802E6870(sp3C, ARRAY_COUNT(sp3C), &sp59);
            rbData->unk78 = sp3C[0];
            rbData->unk7C = sp3C[1];
            rbData->unk344 = sp3C[2];
            rbData->unk34C = sp3C[3];
            rbData->unk350 = sp3C[4];
            rbData->unk354 = sp3C[5];
            rbData->unk358 = sp3C[6];
            if (sp59 & 1) {
                rbData->unk80 = 1;
            } else {
                rbData->unk80 = 0;
            }
            if (sp59 & 2) {
                rbData->unkF8 = 1.0f;
            } else {
                rbData->unkF8 = 0.0f;
            }
        }
        func_80327040(rbData, gameState);
        uvDobjPosm(rbData->objId, 0, &rbData->unk10);
        shadow_803344BC(&rbData->unk10, rbData->unkFC);
        uvMat4SetIdentity(&sp6C);
        sp6C.m[3][0] = rbData->unk10.m[3][0];
        sp6C.m[3][1] = rbData->unk10.m[3][1];
        sp6C.m[3][2] = 0.0f;
        uvDobjPosm(rbData->unk6, 0, &sp6C);
        if (gameState != GAME_STATE_RESULTS) {
            rbData->unk54 = func_80313AF4(rbData->unk58, rbData->unk54, 3.0f);
            rbData->camera->unk1B0 = rbData->unk54;
            rbData->camera->unk78 = rbData->unk88;
            rbData->camera->unk7C = rbData->unk8C;
            rbData->camera->unk4 = rbData->objId;
            rbData->camera->unk6 = rbData->unk2;
            rbData->camera->unk228 = rbData->unkFC;
            uvMat4Copy(&rbData->camera->unk80, &rbData->unk10);
            if ((rbData->unk5C == 1) && (rbData->unk90 != 2) && (gameState != GAME_STATE_RESULTS)) {
                rbData->unkEF = 0;
            } else {
                rbData->unkEF = 1;
            }
            if (rbData->camera->unk148 != 0) {
                rbData->unkEF = 1;
            }
            func_80326E40(rbData);
            hud = hudGetState();
            if ((rbData->unk90 != 2) && (rbData->unk90 != 3)) {
                uvMat4Copy(&hud->unk28, &rbData->unk10);
                hud->renderFlags = 4;
                hud->fuel = rbData->unkF8;
                hud->att.heading = rbData->unk10.m[3][2];
                hud->elapsedTime = rbData->unk8;
                hud->unk8C = rbData->unk1E8.z * 4.0f * 0.7f;
                hud->altitude = rbData->unkFC * 0.7f;
                hud->altSeaLevel = rbData->unk10.m[3][2] * 0.7f;
                if (rbData->unkE9 != 0) {
                    hud->speed = 0.0f;
                } else {
                    hud->speed = rbData->unk1F4 * 3.6f * 0.7f;
                }
                if (rbData->unk91 != 0) {
                    sndPlaySfx(0x69);
                }
                if ((rbData->unk91 != 0) && (hud->unkB40[0] == -1)) {
                    hudWarningText(TEXT_OFF_2, 1.5f, 8.0f);
                } else {
                    if ((rbData->unkF8 <= 0.0f) && (rbData->unkEC == 0)) {
                        hudWarningText(TEXT_FUEL_OUT, 1.5f, 8.0f);
                        rbData->unkEC = 1;
                    } else if ((rbData->unkF8 < 0.15f) && (rbData->unkEB == 0)) {
                        hudWarningText(TEXT_FUEL_WAR, 1.5f, 8.0f);
                        rbData->unkEB = 1;
                    } else if ((func_8032C080(NULL) != 0) && (rbData->unkED == 0) && ((rbData->unk90 != 2)) && (rbData->unk90 != 3)) {
                        hudText_8031D8E0(TEXT_LAND_MOW, 1.5f, 8.0f);
                        rbData->unkED = 1;
                    } else if ((taskGet_80346468() != 0) && (rbData->unkEE == 0)) {
                        hudText_8031D8E0(TEXT_GOAL, 1.5f, 8.0f);
                        rbData->unkEE = 1;
                    } else if (rbData->unk90 == 4) {
                        if (rbData->unk64 != 0) {
                            hudText_8031D8E0(TEXT_LAND_OK, 1.5f, 8.0f);
                        } else {
                            hudText_8031D8E0(TEXT_LAND_OUT, 1.5f, 8.0f);
                        }
                    }
                }
            } else {
                hud->renderFlags = 0;
            }
        }
        func_802E06AC(&rbData->unk10);
        taskGetClsVehTest(&sp5E, &sp5C, &sp5A);
        if (sp5E == 1) {
            if (func_802E08F4(rbData->unk10.m[3][0], rbData->unk10.m[3][1], rbData->unk10.m[3][2]) != 0) {
                if (rbData->unk38D == 0) {
                    rbData->unk38D = 1;
                    sndPlaySfx(0x6D);
                }
                hudWarningText(-1, 0.0f, 0.0f);
                rbData->unkEB = 0;
                rbData->unkEC = 0;
                rbData->unkF8 = 1.0f;
            } else {
                rbData->unk38D = 0;
            }
        }
        if (D_80362690->unkC[D_80362690->unk9C].unk7B != 0) {
            rbData->unkF8 = 1.0f;
        }
        if (gameState != GAME_STATE_RESULTS) {
            if (rbData->unk90 == 3) {
                fdr_802E66DC();
            }
            fdr_802E65AC(&rbData->unk10, &D_80362690->terraId, &stickX, &stickY, &buttons);
        }
    }
}

void func_80325E1C(RocketBeltData* rbData) {
    Vec3F sp5C;
    Vec3F sp50;
    Vec3F sp44;
    Vec3F* sp40;
    f32 sp3C;
    s32 sp38;
    s32 sp34;
    u8 sp33;

    func_802D5884(rbData->camera, 3);
    hudGetState()->renderFlags = 0;

    if (rbData->unk2 & 4) {
        rbData->unk2 &= ~4;
    }
    uvDobjState(rbData->objId, rbData->unk2);
    rbData->unkEF = 1;
    func_80326E40(rbData);
    if ((rbData->unkE8 == 0) && (rbData->unk33A == 0)) {
        sp5C.x = rbData->unk10.m[3][0];
        sp50.x = rbData->unk374.x;
        sp5C.y = rbData->unk10.m[3][1];
        sp50.y = rbData->unk374.y;
        sp5C.z = rbData->unk10.m[3][2];
        sp50.z = rbData->unk374.z;
        sp34 = rbData->unk380;
        sp33 = db_getgnd(&sp50, &sp5C, &sp34, &sp38, &sp3C, &sp44);
        if (sp33 != 0) {
            sp40 = func_802E02EC();
        } else {
            sp40 = &sp5C;
            sp5C.z = sp3C;
        }
        func_802E05CC(&rbData->unk10, sp40, &sp44, 1);
        if (func_802E0C30(sp33, sp38) != 0) {
            rbData->unkE8 = 1;
        }
        uvDobjPosm(rbData->objId, 0, &rbData->unk10);
        uvMat4Copy(&rbData->camera->unk80, &rbData->unk10);
    }
    shadow_803343D8(0);
    func_80327614(rbData);
}

void rocketBeltLoadPilot(u8 pilot, RocketBeltData* rbData) {
    switch (pilot) {
    case PILOT_LARK:
        rbData->unk250.x = -0.025f, rbData->unk250.y = 0.097f, rbData->unk250.z = 0.675f;
        rbData->unk25C.x = 0.0f, rbData->unk25C.y = 0.0f, rbData->unk25C.z = -0.745f;
        rbData->unk268.x = 0.0f, rbData->unk268.y = 0.442f, rbData->unk268.z = 0.0f;
        rbData->unk274.x = 0.0f, rbData->unk274.y = -0.27f, rbData->unk274.z = 0.0f;
        rbData->unk280.x = -0.54f, rbData->unk280.y = 0.0f, rbData->unk280.z = 0.0f;
        rbData->unk28C.x = 0.54f, rbData->unk28C.y = 0.0f, rbData->unk28C.z = 0.0f;
        rbData->unk298 = -0.124f;
        rbData->unk29C = 0.1f;
        rbData->unk2A0 = -0.745f;
        rbData->unk2A4 = 0.072f;
        rbData->unk2A8 = 0.1f;
        rbData->unk2AC = -0.745f;
        rbData->unk2B0 = -0.025f;
        rbData->unk2B4 = 0.307f;
        rbData->unk2B8 = 0.478f;
        rbData->unk2BC.x = 0.015f;
        rbData->unk2BC.y = 0.006f;
        rbData->unk2BC.z = -0.25f;
        rbData->unk2C8.x = -0.028f;
        rbData->unk2C8.y = 0.006f;
        rbData->unk2C8.z = -0.25f;
        rbData->modelId = MODEL_RB_LARK;
        rbData->unk2DF = 1;
        rbData->unk2D6 = 2;
        rbData->unk2D7 = 3;
        rbData->unk2D8 = 4;
        rbData->unk2D9 = 5;
        rbData->unk2DA = 6;
        rbData->unk2DB = 7;
        rbData->unk2DC = 10;
        rbData->unk2DD = 8;
        rbData->unk2DE = 12;
        rbData->unk2E0 = 11;
        rbData->unk2E1 = 9;
        rbData->unk2E2 = 0x36;
        rbData->unk2E3 = 0x35;
        rbData->unk2E4 = 16.0f;
        rbData->unk2E8 = 0.0f;
        rbData->unk2EC = 6.0f;
        rbData->unk2F0 = 0.5f;
        rbData->unk2F4 = 1.0f;
        rbData->unk2F8 = 10.5f;
        rbData->unk2FC = 0.34f;
        rbData->unk300 = 0.31f;
        rbData->unk304 = 9.0f;
        rbData->unk308 = 5.0f;
        rbData->unk30C = 2.0f;
        rbData->unk310 = 0.1f;
        rbData->unk314 = 0.7f;
        rbData->unk318 = 0.00675f;
        rbData->unk31C = 0.00f;
        rbData->unk320 = 0.001f;
        rbData->unk324 = 0.03f;
        rbData->unk328 = 0.35f;
        rbData->unk32C = 9.6f;
        rbData->unk330 = 9.6f;
        rbData->unk334 = 16.0f;
        break;
    case PILOT_GOOSE:
        rbData->unk250.x = -0.001f, rbData->unk250.y = 0.172f, rbData->unk250.z = 0.782f;
        rbData->unk25C.x = 0.0f, rbData->unk25C.y = 0.0f, rbData->unk25C.z = -1.336f;
        rbData->unk268.x = 0.0f, rbData->unk268.y = 0.647f, rbData->unk268.z = 0.0f;
        rbData->unk274.x = 0.0f, rbData->unk274.y = -0.341f, rbData->unk274.z = 0.0f;
        rbData->unk280.x = -0.73f, rbData->unk280.y = 0.0f, rbData->unk280.z = 0.0f;
        rbData->unk28C.x = 0.73f, rbData->unk28C.y = 0.0f, rbData->unk28C.z = 0.0f;
        rbData->unk298 = -0.235f;
        rbData->unk29C = 0.018f;
        rbData->unk2A0 = -1.336f;
        rbData->unk2A4 = 0.233f;
        rbData->unk2A8 = 0.018f;
        rbData->unk2AC = -1.336f;
        rbData->unk2B0 = 0.0f;
        rbData->unk2B4 = 0.315f;
        rbData->unk2B8 = 0.603f;
        rbData->unk2BC.x = 0.041f;
        rbData->unk2BC.y = 0.008f;
        rbData->unk2BC.z = -0.358f;
        rbData->unk2C8.x = -0.04f;
        rbData->unk2C8.y = 0.008f;
        rbData->unk2C8.z = -0.358f;
        rbData->modelId = MODEL_RB_GOOSE;
        rbData->unk2DF = 1;
        rbData->unk2D6 = 2;
        rbData->unk2D7 = 3;
        rbData->unk2D8 = 4;
        rbData->unk2D9 = 5;
        rbData->unk2DA = 6;
        rbData->unk2DB = 7;
        rbData->unk2DC = 10;
        rbData->unk2DD = 8;
        rbData->unk2DE = 12;
        rbData->unk2E0 = 11;
        rbData->unk2E1 = 9;
        rbData->unk2E2 = 0x36;
        rbData->unk2E3 = 0x35;
        rbData->unk2E4 = 19.5f;
        rbData->unk2E8 = 0.0f;
        rbData->unk2EC = 6.0f;
        rbData->unk2F0 = 0.5f;
        rbData->unk2F4 = 1.0f;
        rbData->unk2F8 = 10.5f;
        rbData->unk2FC = 0.34f;
        rbData->unk300 = 0.31f;
        rbData->unk304 = 9.0f;
        rbData->unk308 = 5.0f;
        rbData->unk30C = 2.0f;
        rbData->unk310 = 0.1f;
        rbData->unk314 = 1.2f;
        rbData->unk318 = 0.00825f;
        rbData->unk31C = 0.00f;
        rbData->unk320 = 0.001f;
        rbData->unk324 = 0.03f;
        rbData->unk328 = 0.65f;
        rbData->unk32C = 4.8f;
        rbData->unk330 = 4.8f;
        rbData->unk334 = 9.6f;
        break;
    case PILOT_HAWK:
        rbData->unk250.x = 0.003f, rbData->unk250.y = 0.187f, rbData->unk250.z = 0.634f;
        rbData->unk25C.x = 0.0f, rbData->unk25C.y = 0.0f, rbData->unk25C.z = -1.221f;
        rbData->unk268.x = 0.0f, rbData->unk268.y = 0.698f, rbData->unk268.z = 0.0f;
        rbData->unk274.x = 0.0f, rbData->unk274.y = -0.43f, rbData->unk274.z = 0.0f;
        rbData->unk280.x = -0.819f, rbData->unk280.y = 0.0f, rbData->unk280.z = 0.0f;
        rbData->unk28C.x = 0.819f, rbData->unk28C.y = 0.0f, rbData->unk28C.z = 0.0f;
        rbData->unk298 = -0.148f;
        rbData->unk29C = 0.078f;
        rbData->unk2A0 = -1.221f;
        rbData->unk2A4 = 0.153f;
        rbData->unk2A8 = 0.078f;
        rbData->unk2AC = -1.221f;
        rbData->unk2B0 = 0.002f;
        rbData->unk2B4 = 0.325f;
        rbData->unk2B8 = 0.52f;
        rbData->unk2BC.x = 0.046f;
        rbData->unk2BC.y = 0.01f;
        rbData->unk2BC.z = -0.408f;
        rbData->unk2C8.x = -0.046f;
        rbData->unk2C8.y = 0.01f;
        rbData->unk2C8.z = -0.408f;
        rbData->modelId = MODEL_RB_HAWK;
        rbData->unk2DF = 1;
        rbData->unk2D6 = 2;
        rbData->unk2D7 = 3;
        rbData->unk2D8 = 4;
        rbData->unk2D9 = 5;
        rbData->unk2DA = 6;
        rbData->unk2DB = 7;
        rbData->unk2DC = 10;
        rbData->unk2DD = 8;
        rbData->unk2DE = 12;
        rbData->unk2E0 = 11;
        rbData->unk2E1 = 9;
        rbData->unk2E2 = 0x36;
        rbData->unk2E3 = 0x35;
        rbData->unk2E4 = 17.5f;
        rbData->unk2E8 = 0.0f;
        rbData->unk2EC = 6.0f;
        rbData->unk2F0 = 0.5f;
        rbData->unk2F4 = 1.0f;
        rbData->unk2F8 = 10.5f;
        rbData->unk2FC = 0.34f;
        rbData->unk300 = 0.31f;
        rbData->unk304 = 9.0f;
        rbData->unk308 = 5.0f;
        rbData->unk30C = 2.0f;
        rbData->unk310 = 0.1f;
        rbData->unk314 = 1.0f;
        rbData->unk318 = 0.0075f;
        rbData->unk31C = 0.00f;
        rbData->unk320 = 0.001f;
        rbData->unk324 = 0.03f;
        rbData->unk328 = 0.5f;
        rbData->unk32C = 8.0f;
        rbData->unk330 = 8.0f;
        rbData->unk334 = 17.6f;
        break;
    case PILOT_KIWI:
        rbData->unk250.x = 0.002f, rbData->unk250.y = 0.084f, rbData->unk250.z = 0.706f;
        rbData->unk25C.x = 0.0f, rbData->unk25C.y = 0.0f, rbData->unk25C.z = -0.827f;
        rbData->unk268.x = 0.0f, rbData->unk268.y = 0.426f, rbData->unk268.z = 0.0f;
        rbData->unk274.x = 0.0f, rbData->unk274.y = -0.261f, rbData->unk274.z = 0.0f;
        rbData->unk280.x = -0.479f, rbData->unk280.y = 0.0f, rbData->unk280.z = 0.0f;
        rbData->unk28C.x = 0.479f, rbData->unk28C.y = 0.0f, rbData->unk28C.z = 0.0f;
        rbData->unk298 = -0.012f;
        rbData->unk29C = 0.294f;
        rbData->unk2A0 = -0.828f;
        rbData->unk2A4 = 0.101f;
        rbData->unk2A8 = 0.127f;
        rbData->unk2AC = -0.83f;
        rbData->unk2B0 = 0.002f;
        rbData->unk2B4 = 0.308f;
        rbData->unk2B8 = 0.473f;
        rbData->unk2BC.x = 0.027f;
        rbData->unk2BC.y = 0.006f;
        rbData->unk2BC.z = -0.239f;
        rbData->unk2C8.x = -0.027f;
        rbData->unk2C8.y = 0.006f;
        rbData->unk2C8.z = -0.239f;
        rbData->modelId = MODEL_RB_KIWI;
        rbData->unk2DF = 1;
        rbData->unk2D6 = 2;
        rbData->unk2D7 = 3;
        rbData->unk2D8 = 4;
        rbData->unk2D9 = 5;
        rbData->unk2DA = 6;
        rbData->unk2DB = 7;
        rbData->unk2DC = 10;
        rbData->unk2DD = 8;
        rbData->unk2DE = 12;
        rbData->unk2E0 = 11;
        rbData->unk2E1 = 9;
        rbData->unk2E2 = 0x36;
        rbData->unk2E3 = 0x35;
        rbData->unk2E4 = 16.0f;
        rbData->unk2E8 = 0.0f;
        rbData->unk2EC = 6.0f;
        rbData->unk2F0 = 0.5f;
        rbData->unk2F4 = 1.0f;
        rbData->unk2F8 = 10.5f;
        rbData->unk2FC = 0.34f;
        rbData->unk300 = 0.31f;
        rbData->unk304 = 9.0f;
        rbData->unk308 = 5.0f;
        rbData->unk30C = 2.0f;
        rbData->unk310 = 0.1f;
        rbData->unk314 = 0.7f;
        rbData->unk318 = 0.00675f;
        rbData->unk31C = 0.00f;
        rbData->unk320 = 0.001f;
        rbData->unk324 = 0.03f;
        rbData->unk328 = 0.35f;
        rbData->unk32C = 9.6f;
        rbData->unk330 = 9.6f;
        rbData->unk334 = 16.0f;
        break;
    case PILOT_IBIS:
        rbData->unk250.x = -0.002f, rbData->unk250.y = 0.085f, rbData->unk250.z = 0.799f;
        rbData->unk25C.x = 0.0f, rbData->unk25C.y = 0.0f, rbData->unk25C.z = -1.36f;
        rbData->unk268.x = 0.0f, rbData->unk268.y = 0.586f, rbData->unk268.z = 0.0f;
        rbData->unk274.x = 0.0f, rbData->unk274.y = -0.314f, rbData->unk274.z = 0.0f;
        rbData->unk280.x = -0.666f, rbData->unk280.y = 0.0f, rbData->unk280.z = 0.0f;
        rbData->unk28C.x = 0.666f, rbData->unk28C.y = 0.0f, rbData->unk28C.z = 0.0f;
        rbData->unk298 = -0.286f;
        rbData->unk29C = 0.085f;
        rbData->unk2A0 = -1.36f;
        rbData->unk2A4 = 0.271f;
        rbData->unk2A8 = 0.085f;
        rbData->unk2AC = -1.36f;
        rbData->unk2B0 = 0.0f;
        rbData->unk2B4 = 0.212f;
        rbData->unk2B8 = 0.599f;
        rbData->unk2BC.x = 0.038f;
        rbData->unk2BC.y = 0.008f;
        rbData->unk2BC.z = -0.332f;
        rbData->unk2C8.x = -0.037f;
        rbData->unk2C8.y = 0.008f;
        rbData->unk2C8.z = -0.332f;
        rbData->modelId = MODEL_RB_IBIS;
        rbData->unk2DF = 1;
        rbData->unk2D6 = 2;
        rbData->unk2D7 = 3;
        rbData->unk2D8 = 4;
        rbData->unk2D9 = 5;
        rbData->unk2DA = 6;
        rbData->unk2DB = 7;
        rbData->unk2DC = 10;
        rbData->unk2DD = 8;
        rbData->unk2DE = 12;
        rbData->unk2E0 = 11;
        rbData->unk2E1 = 9;
        rbData->unk2E2 = 0x36;
        rbData->unk2E3 = 0x35;
        rbData->unk2E4 = 19.5f;
        rbData->unk2E8 = 0.0f;
        rbData->unk2EC = 6.0f;
        rbData->unk2F0 = 0.5f;
        rbData->unk2F4 = 1.0f;
        rbData->unk2F8 = 10.5f;
        rbData->unk2FC = 0.34f;
        rbData->unk300 = 0.31f;
        rbData->unk304 = 9.0f;
        rbData->unk308 = 5.0f;
        rbData->unk30C = 2.0f;
        rbData->unk310 = 0.1f;
        rbData->unk314 = 1.2f;
        rbData->unk318 = 0.00825f;
        rbData->unk31C = 0.00f;
        rbData->unk320 = 0.001f;
        rbData->unk324 = 0.03f;
        rbData->unk328 = 0.65f;
        rbData->unk32C = 4.8f;
        rbData->unk330 = 4.8f;
        rbData->unk334 = 9.6f;
        break;
    case PILOT_ROBIN:
        rbData->unk250.x = -0.001f, rbData->unk250.y = 0.095f, rbData->unk250.z = 0.844f;
        rbData->unk25C.x = 0.0f, rbData->unk25C.y = 0.0f, rbData->unk25C.z = -1.076f;
        rbData->unk268.x = 0.0f, rbData->unk268.y = 0.563f, rbData->unk268.z = 0.0f;
        rbData->unk274.x = 0.0f, rbData->unk274.y = -0.433f, rbData->unk274.z = 0.0f;
        rbData->unk280.x = -0.737f, rbData->unk280.y = 0.0f, rbData->unk280.z = 0.0f;
        rbData->unk28C.x = 0.737f, rbData->unk28C.y = 0.0f, rbData->unk28C.z = 0.0f;
        rbData->unk298 = -0.149f;
        rbData->unk29C = 0.094f;
        rbData->unk2A0 = -1.076f;
        rbData->unk2A4 = 0.147f;
        rbData->unk2A8 = 0.094f;
        rbData->unk2AC = -1.076f;
        rbData->unk2B0 = 0.0f;
        rbData->unk2B4 = 0.217f;
        rbData->unk2B8 = 0.621f;
        rbData->unk2BC.x = 0.042f;
        rbData->unk2BC.y = 0.022f;
        rbData->unk2BC.z = -0.31f;
        rbData->unk2C8.x = -0.041f;
        rbData->unk2C8.y = 0.022f;
        rbData->unk2C8.z = -0.31f;
        rbData->modelId = MODEL_RB_ROBIN;
        rbData->unk2DF = 1;
        rbData->unk2D6 = 2;
        rbData->unk2D7 = 3;
        rbData->unk2D8 = 4;
        rbData->unk2D9 = 5;
        rbData->unk2DA = 6;
        rbData->unk2DB = 7;
        rbData->unk2DC = 10;
        rbData->unk2DD = 8;
        rbData->unk2DE = 12;
        rbData->unk2E0 = 11;
        rbData->unk2E1 = 9;
        rbData->unk2E2 = 0x36;
        rbData->unk2E3 = 0x35;
        rbData->unk2E4 = 17.5f;
        rbData->unk2E8 = 0.0f;
        rbData->unk2EC = 6.0f;
        rbData->unk2F0 = 0.5f;
        rbData->unk2F4 = 1.0f;
        rbData->unk2F8 = 10.5f;
        rbData->unk2FC = 0.34f;
        rbData->unk300 = 0.31f;
        rbData->unk304 = 9.0f;
        rbData->unk308 = 5.0f;
        rbData->unk30C = 2.0f;
        rbData->unk310 = 0.1f;
        rbData->unk314 = 1.0f;
        rbData->unk318 = 0.0075f;
        rbData->unk31C = 0.00f;
        rbData->unk320 = 0.001f;
        rbData->unk324 = 0.03f;
        rbData->unk328 = 0.5f;
        rbData->unk32C = 8.0f;
        rbData->unk330 = 8.0f;
        rbData->unk334 = 17.6f;
        break;
    default:
        break;
    }
}

void func_80326E40(RocketBeltData* rbData) {
    if (rbData->unkEF != 0) {
        rbData->unk2 &= ~4;
        uvDobjProps(rbData->objId, 4, rbData->unk2DE, 0);
        if (rbData->modelId == MODEL_RB_KIWI) {
            uvDobjProps(rbData->objId, 4, 0xD, 0);
            uvDobjProps(rbData->objId, 4, 0xE, 0);
        }
    } else {
        rbData->unk2 |= 4;
        uvDobjProps(rbData->objId, 5, rbData->unk2DE, 0);
        if (rbData->modelId == MODEL_RB_KIWI) {
            uvDobjProps(rbData->objId, 5, 0xD, 0);
            uvDobjProps(rbData->objId, 5, 0xE, 0);
        }
    }
    uvDobjState(rbData->objId, rbData->unk2);
}
