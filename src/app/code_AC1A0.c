#include "common.h"
#include "rocket_belt.h"
#include "app/demo.h"
#include "app/fdr.h"
#include "app/hud.h"
#include "app/shadow.h"
#include "app/snd.h"
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

void rocketBeltLoadLevel(u8 contIdx, u8 pilot, RocketBeltData* arg2, Camera* arg3) {

    uvMemSet(arg2, 0, sizeof(RocketBeltData));
    rocketBeltLoadPilot(pilot, arg2);
    shadow_80334454(MODEL_RB_SHADOW_COLUMN, MODEL_RB_SHADOW);
    shadow_803342F0(0.0f);
    shadow_803342FC(arg2->unk25C.z + 0.1f);
    shadow_803343D8(1);
    arg2->unk6 = uvDobjAllocIdx();
    uvDobjModel(arg2->unk6, MODEL_MULTI_COLORED_CUBE);
    uvDobjState(arg2->unk6, 0x22);
    arg2->objId = uvDobjAllocIdx();
    arg2->unk2 = 2;
    uvDobjModel(arg2->objId, arg2->unk2D4);
    uvDobjPosm(arg2->objId, 0, &arg2->unk10);
    uvDobjState(arg2->objId, arg2->unk2);
    arg2->contIdx = contIdx;
    arg2->unk50 = arg3;
    arg2->unk4 = 0xFFFF;
    func_80326F30(arg2);
    func_80328420(arg2);
    rbSoundInit(arg2);
}

void rocketBeltEnterLeave(RocketBeltData* arg0) {
    Vec3F sp44;
    Vec3F sp38;
    u8 sp37;
    s32 sp30;

    db_getstart(&arg0->unk10, &arg0->unk1DC, &sp37, &arg0->unkF8);
    uvDobjPosm(arg0->objId, 0, &arg0->unk10);
    if (sp37 != 0) {
        arg0->unk90 = 0;
        arg0->unkE9 = 0;
    } else {
        arg0->unk90 = 1;
        arg0->unkE9 = 1;
    }
    if (arg0->unk90 != 0) {
        sp30 = 1;
        sp44.x = sp38.x = arg0->unk10.m[3][0];
        sp44.y = sp38.y = arg0->unk10.m[3][1];
        sp44.z = arg0->unk10.m[3][2] + 0.5f;
        sp38.z = arg0->unk10.m[3][2] - 0.5f;
        db_getgnd(&sp44, &sp38, &sp30, &arg0->unk100, &arg0->unk104, &arg0->unk108);
        arg0->unkE9 = 1;
        arg0->unk10.m[3][2] = arg0->unk104 - arg0->unk25C.z;
    } else {
        arg0->unkE9 = 0;
    }
    func_80328538(arg0);
    arg0->unk80 = 0;
    arg0->unk33B = 0;
    arg0->unkEB = 0;
    arg0->unkEC = 0;
    arg0->unkED = 0;
    arg0->unkEE = 0;
    arg0->unkEA = 0;
    arg0->unkEF = 1;
    arg0->unk2 = 2;
    arg0->unk88 = 0.0f;
    arg0->unk8C = 0.0f;
    arg0->unk344 = 0.0f;
    arg0->unk34C = 0.0f;
    arg0->unk354 = 0.0f;
    arg0->unk350 = 0.0f;
    arg0->unk348 = 0.0f;
    arg0->unk358 = 0.0f;
    arg0->unk33C = 0.0f;
    arg0->unk8 = 0.0f;
    arg0->unk68 = 0.0f;
    arg0->unk6C = 0.0f;
    arg0->unk35C = 0.0f;
    arg0->unk360 = 0.0f;
    arg0->unk364 = 0.0f;
    arg0->unk368 = 0.0f;
    arg0->unk36C = 0.0f;
    arg0->unk370 = 0.0f;
    func_80326E40(arg0);
    arg0->unk5C = 4;
    arg0->unk60 = 0.8f;
    arg0->unk54 = 0.0f;
    arg0->unk58 = 0.0f;
    arg0->unk50->unk0 = 0x6C;
    arg0->unk50->unk1 = 4;
    arg0->unk50->unk4 = arg0->objId;
    arg0->unk50->unk6 = arg0->unk2;
    arg0->unk50->unk68.x = arg0->unk2B0;
    arg0->unk50->unk68.y = arg0->unk2B4;
    arg0->unk50->unk68.z = arg0->unk2B8;
    arg0->unk50->unk74 = 0.0f;
    arg0->unk50->unk1B4 = 6.0f;
    uvModelGetProps(arg0->unk2D4, 1, &arg0->unk50->unk8, 0);
    func_802D45C4(arg0->unk50, arg0->unk60);
}

void func_80325100(RocketBeltData* arg0) {
    uvDobjModel(arg0->objId, MODEL_WORLD);
    arg0->contIdx = -1;
    arg0->objId = 0xFFFF;
    uvDobjModel(arg0->unk6, MODEL_WORLD);
    arg0->unk6 = 0xFFFF;
    func_80327380(arg0);
    shadow_80334C70();
}

void rocketBeltMovementFrame(RocketBeltData* arg0, u8 gameState) {
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

    if (arg0->unk90 == 3) {
        func_80325E1C(arg0);
        return;
    }
    if (fdr_802E6B5C() != 4) {
        shadow_803343D8(1);
        if (gameState == GAME_STATE_RESULTS) {
            fdr_802E65AC(&arg0->unk10, &D_80362690->terraId, &stickX, &stickY, &buttons);
        } else {
            stickX = demoGetInputs(arg0->contIdx, INPUT_AXIS_X);
            stickY = demoGetInputs(arg0->contIdx, INPUT_AXIS_Y);
            buttons = demoGetButtons(arg0->contIdx);
        }
        arg0->unk68 = stickX;
        arg0->unk6C = stickY;
        if ((arg0->unk8 > 0.0f) || (buttons & (A_BUTTON | B_BUTTON))) {
            arg0->unk8 += D_8034F854;
        }
    
        arg0->unk70 = func_80313F08(&D_80371070, ABS_NOEQ(stickX));
        if (stickX < 0.0f) {
            arg0->unk70 = -arg0->unk70;
        }

        arg0->unk74 = func_80313F08(&D_803710C8, ABS_NOEQ(stickY));
        if (stickY < 0.0f) {
            arg0->unk74 = -arg0->unk74;
        }
        arg0->unk81 = 0;
        arg0->unk80 = 0;
        if (buttons & Z_TRIG) {
            if (arg0->unkF8 > 0.0f) {
                arg0->unk80 = 1;
            }
            arg0->unk81 = 3;
            spB4 = 0.0f;
            var_fv0_3 = 18.0f;
        } else if (buttons & A_BUTTON) {
            spB4 = 2.0f;
            var_fv0_3 = 18.0f;
            arg0->unk81 = 1;
        } else if (buttons & B_BUTTON) {
            spB4 = 1.0f;
            var_fv0_3 = 18.0f;
            arg0->unk81 = 2;
        } else {
            var_fv0_3 = 12.0f;
            spB4 = 0.0f;
        }
        if (arg0->unkF8 > 0.0f) {
            arg0->unk78 = func_80313AF4(spB4, arg0->unk78, var_fv0_3);
        } else {
            arg0->unk78 = 0.0f;
        }
        if ((demoButtonPress(arg0->contIdx, R_TRIG) != 0) && (gameState != GAME_STATE_RESULTS)) {
            if (arg0->unk5C != 1) {
                if (arg0->unk58 == 1.5707961f) {
                    arg0->unk58 = 0.0f;
                } else {
                    arg0->unk58 = 1.5707961f;
                }
            }
            arg0->unk5C = 4;
            arg0->unk60 = 0.8f;
            if (gameState != GAME_STATE_RESULTS) {
                func_8033F758(0x67, 0.3f, 0.65f, 0.0f);
            }
            func_802D5884(arg0->unk50, arg0->unk5C);
            func_802D45C4(arg0->unk50, arg0->unk60);
        }
        if (gameState != GAME_STATE_RESULTS) {
            if ((arg0->unk90 == 2) || (arg0->unk90 == 3)) {
                func_802D5884(arg0->unk50, 6);
            } else {
                func_802D5884(arg0->unk50, arg0->unk5C);
            }
            func_802D45C4(arg0->unk50, arg0->unk60);
        }
        if (arg0->unkEF == 0) {
            if (buttons & 2) {
                spB4 += 2.0f;
            } else if (buttons & 1) {
                spB4 += -2.0f;
            } else {
                spB4 = 0.0f;
            }
            arg0->unk88 = func_80313AF4(spB4, arg0->unk88, 3.0f);
            if (demoButtonPress(arg0->contIdx, D_CBUTTONS) != 0) {
                if ((gameState != GAME_STATE_RESULTS) && (arg0->unk58 > -1.5707961f)) {
                    func_8033F758(0x67, 0.3f, 1.0f, 0.0f);
                }
                arg0->unk58 -= 0.39269903f;
                arg0->unk58 = MAX(arg0->unk58, -1.5707961f);
            }
            if (demoButtonPress(arg0->contIdx, U_CBUTTONS) != 0) {
                if ((gameState != GAME_STATE_RESULTS) && (arg0->unk58 < 1.5707961f)) {
                    func_8033F758(0x67, 0.3f, 1.0f, 0.0f);
                }
                arg0->unk58 += 0.39269903f;
                arg0->unk58 = MIN(arg0->unk58, 1.5707961f);
            }
            arg0->unk8C = -arg0->unk54;
        } else {
            if (demoButtonPress(arg0->contIdx, U_CBUTTONS) != 0) {
                if ((gameState != GAME_STATE_RESULTS) && (arg0->unk58 < 1.4835297f)) {
                    func_8033F758(0x67, 0.3f, 1.0f, 0.0f);
                }
                arg0->unk58 += 0.39269903f;
                arg0->unk58 = MIN(arg0->unk58, 1.5707961f);
            }
            if (demoButtonPress(arg0->contIdx, D_CBUTTONS) != 0) {
                if ((gameState != GAME_STATE_RESULTS) && (arg0->unk58 > -1.4835297f)) {
                    func_8033F758(0x67, 0.3f, 1.0f, 0.0f);
                }
                arg0->unk58 -= 0.39269903f;
                arg0->unk58 = MAX(arg0->unk58, -1.5707961f);
            }
            if (buttons & 2) {
                spB4 = 2.0f;
            } else if (buttons & 1) {
                spB4 = -2.0f;
            } else {
                spB4 = 0.0f;
            }
            arg0->unk88 = func_80313AF4(spB4, arg0->unk88, 3.0f);
            arg0->unk8C = 0.0f;
        }
        if (gameState != GAME_STATE_RESULTS) {
            func_8032867C(arg0);
        }
        if (arg0->unk90 == 3) {
            fdr_802E66DC();
        }
        if (gameState != GAME_STATE_RESULTS) {
            sp59 = 0;
            if (arg0->unk80 != 0) {
                sp59 = 1;
            }
            if (arg0->unkF8 > 0.0f) {
                sp59 += 2;
            }
            sp3C[0] = arg0->unk78;
            sp3C[1] = arg0->unk7C;
            sp3C[2] = arg0->unk344;
            sp3C[3] = arg0->unk34C;
            sp3C[4] = arg0->unk350;
            sp3C[5] = arg0->unk354;
            sp3C[6] = arg0->unk358;
            fdr_802E682C(sp3C, ARRAY_COUNT(sp3C), sp59);
        } else {
            fdr_802E6870(sp3C, ARRAY_COUNT(sp3C), &sp59);
            arg0->unk78 = sp3C[0];
            arg0->unk7C = sp3C[1];
            arg0->unk344 = sp3C[2];
            arg0->unk34C = sp3C[3];
            arg0->unk350 = sp3C[4];
            arg0->unk354 = sp3C[5];
            arg0->unk358 = sp3C[6];
            if (sp59 & 1) {
                arg0->unk80 = 1;
            } else {
                arg0->unk80 = 0;
            }
            if (sp59 & 2) {
                arg0->unkF8 = 1.0f;
            } else {
                arg0->unkF8 = 0.0f;
            }
        }
        func_80327040(arg0, gameState);
        uvDobjPosm(arg0->objId, 0, &arg0->unk10);
        shadow_803344BC(&arg0->unk10, arg0->unkFC);
        uvMat4SetIdentity(&sp6C);
        sp6C.m[3][0] = arg0->unk10.m[3][0];
        sp6C.m[3][1] = arg0->unk10.m[3][1];
        sp6C.m[3][2] = 0.0f;
        uvDobjPosm(arg0->unk6, 0, &sp6C);
        if (gameState != GAME_STATE_RESULTS) {
            arg0->unk54 = func_80313AF4(arg0->unk58, arg0->unk54, 3.0f);
            arg0->unk50->unk1B0 = arg0->unk54;
            arg0->unk50->unk78 = arg0->unk88;
            arg0->unk50->unk7C = arg0->unk8C;
            arg0->unk50->unk4 = arg0->objId;
            arg0->unk50->unk6 = arg0->unk2;
            arg0->unk50->unk228 = arg0->unkFC;
            uvMat4Copy(&arg0->unk50->unk80, &arg0->unk10);
            if ((arg0->unk5C == 1) && (arg0->unk90 != 2) && (gameState != GAME_STATE_RESULTS)) {
                arg0->unkEF = 0;
            } else {
                arg0->unkEF = 1;
            }
            if (arg0->unk50->unk148 != 0) {
                arg0->unkEF = 1;
            }
            func_80326E40(arg0);
            hud = hudGetState();
            if ((arg0->unk90 != 2) && (arg0->unk90 != 3)) {
                uvMat4Copy(&hud->unk28, &arg0->unk10);
                hud->renderFlags = 4;
                hud->fuel = arg0->unkF8;
                hud->att.heading = arg0->unk10.m[3][2];
                hud->elapsedTime = arg0->unk8;
                hud->unk8C = arg0->unk1E8.z * 4.0f * 0.7f;
                hud->altitude = arg0->unkFC * 0.7f;
                hud->altSeaLevel = arg0->unk10.m[3][2] * 0.7f;
                if (arg0->unkE9 != 0) {
                    hud->speed = 0.0f;
                } else {
                    hud->speed = arg0->unk1F4 * 3.6f * 0.7f;
                }
                if (arg0->unk91 != 0) {
                    sndPlaySfx(0x69);
                }
                if ((arg0->unk91 != 0) && (hud->unkB40[0] == -1)) {
                    hudWarningText(0x4F, 1.5f, 8.0f);
                } else {
                    if ((arg0->unkF8 <= 0.0f) && (arg0->unkEC == 0)) {
                        hudWarningText(0x4A, 1.5f, 8.0f);
                        arg0->unkEC = 1;
                    } else if ((arg0->unkF8 < 0.15f) && (arg0->unkEB == 0)) {
                        hudWarningText(0x17B, 1.5f, 8.0f);
                        arg0->unkEB = 1;
                    } else if ((func_8032C080(NULL) != 0) && (arg0->unkED == 0) && ((arg0->unk90 != 2)) && (arg0->unk90 != 3)) {
                        hudText_8031D8E0(0xD4, 1.5f, 8.0f);
                        arg0->unkED = 1;
                    } else if ((taskGet_80346468() != 0) && (arg0->unkEE == 0)) {
                        hudText_8031D8E0(0x15D, 1.5f, 8.0f);
                        arg0->unkEE = 1;
                    } else if (arg0->unk90 == 4) {
                        if (arg0->unk64 != 0) {
                            hudText_8031D8E0(0xCB, 1.5f, 8.0f);
                        } else {
                            hudText_8031D8E0(0xB2, 1.5f, 8.0f);
                        }
                    }
                }
            } else {
                hud->renderFlags = 0;
            }
        }
        func_802E06AC(&arg0->unk10);
        taskGetClsVehTest(&sp5E, &sp5C, &sp5A);
        if (sp5E == 1) {
            if (func_802E08F4(arg0->unk10.m[3][0], arg0->unk10.m[3][1], arg0->unk10.m[3][2]) != 0) {
                if (arg0->unk38D == 0) {
                    arg0->unk38D = 1;
                    sndPlaySfx(0x6D);
                }
                hudWarningText(-1, 0.0f, 0.0f);
                arg0->unkEB = 0;
                arg0->unkEC = 0;
                arg0->unkF8 = 1.0f;
            } else {
                arg0->unk38D = 0;
            }
        }
        if (D_80362690->unkC[D_80362690->unk9C].unk7B != 0) {
            arg0->unkF8 = 1.0f;
        }
        if (gameState != GAME_STATE_RESULTS) {
            if (arg0->unk90 == 3) {
                fdr_802E66DC();
            }
            fdr_802E65AC(&arg0->unk10, &D_80362690->terraId, &stickX, &stickY, &buttons);
        }
    }
}

void func_80325E1C(RocketBeltData* arg0) {
    Vec3F sp5C;
    Vec3F sp50;
    Vec3F sp44;
    Vec3F* sp40;
    f32 sp3C;
    s32 sp38;
    s32 sp34;
    u8 sp33;

    func_802D5884(arg0->unk50, 3);
    hudGetState()->renderFlags = 0;

    if (arg0->unk2 & 4) {
        arg0->unk2 &= ~4;
    }
    uvDobjState(arg0->objId, arg0->unk2);
    arg0->unkEF = 1;
    func_80326E40(arg0);
    if ((arg0->unkE8 == 0) && (arg0->unk33A == 0)) {
        sp5C.x = arg0->unk10.m[3][0];
        sp50.x = arg0->unk374.x;
        sp5C.y = arg0->unk10.m[3][1];
        sp50.y = arg0->unk374.y;
        sp5C.z = arg0->unk10.m[3][2];
        sp50.z = arg0->unk374.z;
        sp34 = arg0->unk380;
        sp33 = db_getgnd(&sp50, &sp5C, &sp34, &sp38, &sp3C, &sp44);
        if (sp33 != 0) {
            sp40 = func_802E02EC();
        } else {
            sp40 = &sp5C;
            sp5C.z = sp3C;
        }
        func_802E05CC(&arg0->unk10, sp40, &sp44, 1);
        if (func_802E0C30(sp33, sp38) != 0) {
            arg0->unkE8 = 1;
        }
        uvDobjPosm(arg0->objId, 0, &arg0->unk10);
        uvMat4Copy(&arg0->unk50->unk80, &arg0->unk10);
    }
    shadow_803343D8(0);
    func_80327614(arg0);
}

void rocketBeltLoadPilot(u8 pilot, RocketBeltData* arg1) {

    switch (pilot) {
    case PILOT_LARK:
        arg1->unk250.x = -0.025f, arg1->unk250.y = 0.097f, arg1->unk250.z = 0.675f;
        arg1->unk25C.x = 0.0f, arg1->unk25C.y = 0.0f, arg1->unk25C.z = -0.745f;
        arg1->unk268.x = 0.0f, arg1->unk268.y = 0.442f, arg1->unk268.z = 0.0f;
        arg1->unk274.x = 0.0f, arg1->unk274.y = -0.27f, arg1->unk274.z = 0.0f;
        arg1->unk280.x = -0.54f, arg1->unk280.y = 0.0f, arg1->unk280.z = 0.0f;
        arg1->unk28C.x = 0.54f, arg1->unk28C.y = 0.0f, arg1->unk28C.z = 0.0f;
        arg1->unk298 = -0.124f;
        arg1->unk29C = 0.1f;
        arg1->unk2A0 = -0.745f;
        arg1->unk2A4 = 0.072f;
        arg1->unk2A8 = 0.1f;
        arg1->unk2AC = -0.745f;
        arg1->unk2B0 = -0.025f;
        arg1->unk2B4 = 0.307f;
        arg1->unk2B8 = 0.478f;
        arg1->unk2BC.x = 0.015f;
        arg1->unk2BC.y = 0.006f;
        arg1->unk2BC.z = -0.25f;
        arg1->unk2C8.x = -0.028f;
        arg1->unk2C8.y = 0.006f;
        arg1->unk2C8.z = -0.25f;
        arg1->unk2D4 = MODEL_RB_LARK;
        arg1->unk2DF = 1;
        arg1->unk2D6 = 2;
        arg1->unk2D7 = 3;
        arg1->unk2D8 = 4;
        arg1->unk2D9 = 5;
        arg1->unk2DA = 6;
        arg1->unk2DB = 7;
        arg1->unk2DC = 10;
        arg1->unk2DD = 8;
        arg1->unk2DE = 12;
        arg1->unk2E0 = 11;
        arg1->unk2E1 = 9;
        arg1->unk2E2 = 0x36;
        arg1->unk2E3 = 0x35;
        arg1->unk2E4 = 16.0f;
        arg1->unk2E8 = 0.0f;
        arg1->unk2EC = 6.0f;
        arg1->unk2F0 = 0.5f;
        arg1->unk2F4 = 1.0f;
        arg1->unk2F8 = 10.5f;
        arg1->unk2FC = 0.34f;
        arg1->unk300 = 0.31f;
        arg1->unk304 = 9.0f;
        arg1->unk308 = 5.0f;
        arg1->unk30C = 2.0f;
        arg1->unk310 = 0.1f;
        arg1->unk314 = 0.7f;
        arg1->unk318 = 0.00675f;
        arg1->unk31C = 0.00f;
        arg1->unk320 = 0.001f;
        arg1->unk324 = 0.03f;
        arg1->unk328 = 0.35f;
        arg1->unk32C = 9.6f;
        arg1->unk330 = 9.6f;
        arg1->unk334 = 16.0f;
        break;
    case PILOT_GOOSE:
        arg1->unk250.x = -0.001f, arg1->unk250.y = 0.172f, arg1->unk250.z = 0.782f;
        arg1->unk25C.x = 0.0f, arg1->unk25C.y = 0.0f, arg1->unk25C.z = -1.336f;
        arg1->unk268.x = 0.0f, arg1->unk268.y = 0.647f, arg1->unk268.z = 0.0f;
        arg1->unk274.x = 0.0f, arg1->unk274.y = -0.341f, arg1->unk274.z = 0.0f;
        arg1->unk280.x = -0.73f, arg1->unk280.y = 0.0f, arg1->unk280.z = 0.0f;
        arg1->unk28C.x = 0.73f, arg1->unk28C.y = 0.0f, arg1->unk28C.z = 0.0f;
        arg1->unk298 = -0.235f;
        arg1->unk29C = 0.018f;
        arg1->unk2A0 = -1.336f;
        arg1->unk2A4 = 0.233f;
        arg1->unk2A8 = 0.018f;
        arg1->unk2AC = -1.336f;
        arg1->unk2B0 = 0.0f;
        arg1->unk2B4 = 0.315f;
        arg1->unk2B8 = 0.603f;
        arg1->unk2BC.x = 0.041f;
        arg1->unk2BC.y = 0.008f;
        arg1->unk2BC.z = -0.358f;
        arg1->unk2C8.x = -0.04f;
        arg1->unk2C8.y = 0.008f;
        arg1->unk2C8.z = -0.358f;
        arg1->unk2D4 = MODEL_RB_GOOSE;
        arg1->unk2DF = 1;
        arg1->unk2D6 = 2;
        arg1->unk2D7 = 3;
        arg1->unk2D8 = 4;
        arg1->unk2D9 = 5;
        arg1->unk2DA = 6;
        arg1->unk2DB = 7;
        arg1->unk2DC = 10;
        arg1->unk2DD = 8;
        arg1->unk2DE = 12;
        arg1->unk2E0 = 11;
        arg1->unk2E1 = 9;
        arg1->unk2E2 = 0x36;
        arg1->unk2E3 = 0x35;
        arg1->unk2E4 = 19.5f;
        arg1->unk2E8 = 0.0f;
        arg1->unk2EC = 6.0f;
        arg1->unk2F0 = 0.5f;
        arg1->unk2F4 = 1.0f;
        arg1->unk2F8 = 10.5f;
        arg1->unk2FC = 0.34f;
        arg1->unk300 = 0.31f;
        arg1->unk304 = 9.0f;
        arg1->unk308 = 5.0f;
        arg1->unk30C = 2.0f;
        arg1->unk310 = 0.1f;
        arg1->unk314 = 1.2f;
        arg1->unk318 = 0.00825f;
        arg1->unk31C = 0.00f;
        arg1->unk320 = 0.001f;
        arg1->unk324 = 0.03f;
        arg1->unk328 = 0.65f;
        arg1->unk32C = 4.8f;
        arg1->unk330 = 4.8f;
        arg1->unk334 = 9.6f;
        break;
    case PILOT_HAWK:
        arg1->unk250.x = 0.003f, arg1->unk250.y = 0.187f, arg1->unk250.z = 0.634f;
        arg1->unk25C.x = 0.0f, arg1->unk25C.y = 0.0f, arg1->unk25C.z = -1.221f;
        arg1->unk268.x = 0.0f, arg1->unk268.y = 0.698f, arg1->unk268.z = 0.0f;
        arg1->unk274.x = 0.0f, arg1->unk274.y = -0.43f, arg1->unk274.z = 0.0f;
        arg1->unk280.x = -0.819f, arg1->unk280.y = 0.0f, arg1->unk280.z = 0.0f;
        arg1->unk28C.x = 0.819f, arg1->unk28C.y = 0.0f, arg1->unk28C.z = 0.0f;
        arg1->unk298 = -0.148f;
        arg1->unk29C = 0.078f;
        arg1->unk2A0 = -1.221f;
        arg1->unk2A4 = 0.153f;
        arg1->unk2A8 = 0.078f;
        arg1->unk2AC = -1.221f;
        arg1->unk2B0 = 0.002f;
        arg1->unk2B4 = 0.325f;
        arg1->unk2B8 = 0.52f;
        arg1->unk2BC.x = 0.046f;
        arg1->unk2BC.y = 0.01f;
        arg1->unk2BC.z = -0.408f;
        arg1->unk2C8.x = -0.046f;
        arg1->unk2C8.y = 0.01f;
        arg1->unk2C8.z = -0.408f;
        arg1->unk2D4 = MODEL_RB_HAWK;
        arg1->unk2DF = 1;
        arg1->unk2D6 = 2;
        arg1->unk2D7 = 3;
        arg1->unk2D8 = 4;
        arg1->unk2D9 = 5;
        arg1->unk2DA = 6;
        arg1->unk2DB = 7;
        arg1->unk2DC = 10;
        arg1->unk2DD = 8;
        arg1->unk2DE = 12;
        arg1->unk2E0 = 11;
        arg1->unk2E1 = 9;
        arg1->unk2E2 = 0x36;
        arg1->unk2E3 = 0x35;
        arg1->unk2E4 = 17.5f;
        arg1->unk2E8 = 0.0f;
        arg1->unk2EC = 6.0f;
        arg1->unk2F0 = 0.5f;
        arg1->unk2F4 = 1.0f;
        arg1->unk2F8 = 10.5f;
        arg1->unk2FC = 0.34f;
        arg1->unk300 = 0.31f;
        arg1->unk304 = 9.0f;
        arg1->unk308 = 5.0f;
        arg1->unk30C = 2.0f;
        arg1->unk310 = 0.1f;
        arg1->unk314 = 1.0f;
        arg1->unk318 = 0.0075f;
        arg1->unk31C = 0.00f;
        arg1->unk320 = 0.001f;
        arg1->unk324 = 0.03f;
        arg1->unk328 = 0.5f;
        arg1->unk32C = 8.0f;
        arg1->unk330 = 8.0f;
        arg1->unk334 = 17.6f;
        break;
    case PILOT_KIWI:
        arg1->unk250.x = 0.002f, arg1->unk250.y = 0.084f, arg1->unk250.z = 0.706f;
        arg1->unk25C.x = 0.0f, arg1->unk25C.y = 0.0f, arg1->unk25C.z = -0.827f;
        arg1->unk268.x = 0.0f, arg1->unk268.y = 0.426f, arg1->unk268.z = 0.0f;
        arg1->unk274.x = 0.0f, arg1->unk274.y = -0.261f, arg1->unk274.z = 0.0f;
        arg1->unk280.x = -0.479f, arg1->unk280.y = 0.0f, arg1->unk280.z = 0.0f;
        arg1->unk28C.x = 0.479f, arg1->unk28C.y = 0.0f, arg1->unk28C.z = 0.0f;
        arg1->unk298 = -0.012f;
        arg1->unk29C = 0.294f;
        arg1->unk2A0 = -0.828f;
        arg1->unk2A4 = 0.101f;
        arg1->unk2A8 = 0.127f;
        arg1->unk2AC = -0.83f;
        arg1->unk2B0 = 0.002f;
        arg1->unk2B4 = 0.308f;
        arg1->unk2B8 = 0.473f;
        arg1->unk2BC.x = 0.027f;
        arg1->unk2BC.y = 0.006f;
        arg1->unk2BC.z = -0.239f;
        arg1->unk2C8.x = -0.027f;
        arg1->unk2C8.y = 0.006f;
        arg1->unk2C8.z = -0.239f;
        arg1->unk2D4 = MODEL_RB_KIWI;
        arg1->unk2DF = 1;
        arg1->unk2D6 = 2;
        arg1->unk2D7 = 3;
        arg1->unk2D8 = 4;
        arg1->unk2D9 = 5;
        arg1->unk2DA = 6;
        arg1->unk2DB = 7;
        arg1->unk2DC = 10;
        arg1->unk2DD = 8;
        arg1->unk2DE = 12;
        arg1->unk2E0 = 11;
        arg1->unk2E1 = 9;
        arg1->unk2E2 = 0x36;
        arg1->unk2E3 = 0x35;
        arg1->unk2E4 = 16.0f;
        arg1->unk2E8 = 0.0f;
        arg1->unk2EC = 6.0f;
        arg1->unk2F0 = 0.5f;
        arg1->unk2F4 = 1.0f;
        arg1->unk2F8 = 10.5f;
        arg1->unk2FC = 0.34f;
        arg1->unk300 = 0.31f;
        arg1->unk304 = 9.0f;
        arg1->unk308 = 5.0f;
        arg1->unk30C = 2.0f;
        arg1->unk310 = 0.1f;
        arg1->unk314 = 0.7f;
        arg1->unk318 = 0.00675f;
        arg1->unk31C = 0.00f;
        arg1->unk320 = 0.001f;
        arg1->unk324 = 0.03f;
        arg1->unk328 = 0.35f;
        arg1->unk32C = 9.6f;
        arg1->unk330 = 9.6f;
        arg1->unk334 = 16.0f;
        break;
    case PILOT_IBIS:
        arg1->unk250.x = -0.002f, arg1->unk250.y = 0.085f, arg1->unk250.z = 0.799f;
        arg1->unk25C.x = 0.0f, arg1->unk25C.y = 0.0f, arg1->unk25C.z = -1.36f;
        arg1->unk268.x = 0.0f, arg1->unk268.y = 0.586f, arg1->unk268.z = 0.0f;
        arg1->unk274.x = 0.0f, arg1->unk274.y = -0.314f, arg1->unk274.z = 0.0f;
        arg1->unk280.x = -0.666f, arg1->unk280.y = 0.0f, arg1->unk280.z = 0.0f;
        arg1->unk28C.x = 0.666f, arg1->unk28C.y = 0.0f, arg1->unk28C.z = 0.0f;
        arg1->unk298 = -0.286f;
        arg1->unk29C = 0.085f;
        arg1->unk2A0 = -1.36f;
        arg1->unk2A4 = 0.271f;
        arg1->unk2A8 = 0.085f;
        arg1->unk2AC = -1.36f;
        arg1->unk2B0 = 0.0f;
        arg1->unk2B4 = 0.212f;
        arg1->unk2B8 = 0.599f;
        arg1->unk2BC.x = 0.038f;
        arg1->unk2BC.y = 0.008f;
        arg1->unk2BC.z = -0.332f;
        arg1->unk2C8.x = -0.037f;
        arg1->unk2C8.y = 0.008f;
        arg1->unk2C8.z = -0.332f;
        arg1->unk2D4 = MODEL_RB_IBIS;
        arg1->unk2DF = 1;
        arg1->unk2D6 = 2;
        arg1->unk2D7 = 3;
        arg1->unk2D8 = 4;
        arg1->unk2D9 = 5;
        arg1->unk2DA = 6;
        arg1->unk2DB = 7;
        arg1->unk2DC = 10;
        arg1->unk2DD = 8;
        arg1->unk2DE = 12;
        arg1->unk2E0 = 11;
        arg1->unk2E1 = 9;
        arg1->unk2E2 = 0x36;
        arg1->unk2E3 = 0x35;
        arg1->unk2E4 = 19.5f;
        arg1->unk2E8 = 0.0f;
        arg1->unk2EC = 6.0f;
        arg1->unk2F0 = 0.5f;
        arg1->unk2F4 = 1.0f;
        arg1->unk2F8 = 10.5f;
        arg1->unk2FC = 0.34f;
        arg1->unk300 = 0.31f;
        arg1->unk304 = 9.0f;
        arg1->unk308 = 5.0f;
        arg1->unk30C = 2.0f;
        arg1->unk310 = 0.1f;
        arg1->unk314 = 1.2f;
        arg1->unk318 = 0.00825f;
        arg1->unk31C = 0.00f;
        arg1->unk320 = 0.001f;
        arg1->unk324 = 0.03f;
        arg1->unk328 = 0.65f;
        arg1->unk32C = 4.8f;
        arg1->unk330 = 4.8f;
        arg1->unk334 = 9.6f;
        break;
    case PILOT_ROBIN:
        arg1->unk250.x = -0.001f, arg1->unk250.y = 0.095f, arg1->unk250.z = 0.844f;
        arg1->unk25C.x = 0.0f, arg1->unk25C.y = 0.0f, arg1->unk25C.z = -1.076f;
        arg1->unk268.x = 0.0f, arg1->unk268.y = 0.563f, arg1->unk268.z = 0.0f;
        arg1->unk274.x = 0.0f, arg1->unk274.y = -0.433f, arg1->unk274.z = 0.0f;
        arg1->unk280.x = -0.737f, arg1->unk280.y = 0.0f, arg1->unk280.z = 0.0f;
        arg1->unk28C.x = 0.737f, arg1->unk28C.y = 0.0f, arg1->unk28C.z = 0.0f;
        arg1->unk298 = -0.149f;
        arg1->unk29C = 0.094f;
        arg1->unk2A0 = -1.076f;
        arg1->unk2A4 = 0.147f;
        arg1->unk2A8 = 0.094f;
        arg1->unk2AC = -1.076f;
        arg1->unk2B0 = 0.0f;
        arg1->unk2B4 = 0.217f;
        arg1->unk2B8 = 0.621f;
        arg1->unk2BC.x = 0.042f;
        arg1->unk2BC.y = 0.022f;
        arg1->unk2BC.z = -0.31f;
        arg1->unk2C8.x = -0.041f;
        arg1->unk2C8.y = 0.022f;
        arg1->unk2C8.z = -0.31f;
        arg1->unk2D4 = MODEL_RB_ROBIN;
        arg1->unk2DF = 1;
        arg1->unk2D6 = 2;
        arg1->unk2D7 = 3;
        arg1->unk2D8 = 4;
        arg1->unk2D9 = 5;
        arg1->unk2DA = 6;
        arg1->unk2DB = 7;
        arg1->unk2DC = 10;
        arg1->unk2DD = 8;
        arg1->unk2DE = 12;
        arg1->unk2E0 = 11;
        arg1->unk2E1 = 9;
        arg1->unk2E2 = 0x36;
        arg1->unk2E3 = 0x35;
        arg1->unk2E4 = 17.5f;
        arg1->unk2E8 = 0.0f;
        arg1->unk2EC = 6.0f;
        arg1->unk2F0 = 0.5f;
        arg1->unk2F4 = 1.0f;
        arg1->unk2F8 = 10.5f;
        arg1->unk2FC = 0.34f;
        arg1->unk300 = 0.31f;
        arg1->unk304 = 9.0f;
        arg1->unk308 = 5.0f;
        arg1->unk30C = 2.0f;
        arg1->unk310 = 0.1f;
        arg1->unk314 = 1.0f;
        arg1->unk318 = 0.0075f;
        arg1->unk31C = 0.00f;
        arg1->unk320 = 0.001f;
        arg1->unk324 = 0.03f;
        arg1->unk328 = 0.5f;
        arg1->unk32C = 8.0f;
        arg1->unk330 = 8.0f;
        arg1->unk334 = 17.6f;
        break;
    default:
        break;
    }
}

void func_80326E40(RocketBeltData* arg0) {
    if (arg0->unkEF != 0) {
        arg0->unk2 &= ~4;
        uvDobjProps(arg0->objId, 4, arg0->unk2DE, 0);
        if (arg0->unk2D4 == MODEL_RB_KIWI) {
            uvDobjProps(arg0->objId, 4, 0xD, 0);
            uvDobjProps(arg0->objId, 4, 0xE, 0);
        }
    } else {
        arg0->unk2 |= 4;
        uvDobjProps(arg0->objId, 5, arg0->unk2DE, 0);
        if (arg0->unk2D4 == MODEL_RB_KIWI) {
            uvDobjProps(arg0->objId, 5, 0xD, 0);
            uvDobjProps(arg0->objId, 5, 0xE, 0);
        }
    }
    uvDobjState(arg0->objId, arg0->unk2);
}
