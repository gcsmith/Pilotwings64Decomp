#include "common.h"
#include "code_7CF30.h"
#include <uv_fx.h>
#include <uv_math.h>
#include <uv_memory.h>
#include <uv_model.h>
#include "gyrocopter.h"
#include "app/demo.h"
#include "app/environment.h"
#include "app/falco.h"
#include "app/fdr.h"
#include "app/hsound.h"
#include "app/hud.h"
#include "app/shadow.h"
#include "app/smoke.h"
#include "app/snd.h"
#include "app/targets.h"
#include "app/toys.h"
#include "app/code_66160.h"
#include "app/code_7C4C0.h"
#include "app/code_7FE00.h"
#include "app/code_9A960.h"
#include "app/code_B2900.h"

s32 D_8034F380 = 0;
s32 D_8034F384 = 0;

Unk803599D0 D_80368880;

void func_802F7224(GyrocopterData* arg0);
void func_802F6DC8(GyrocopterData* arg0, u8 arg1);
s32 func_802F6E74(GyrocopterData* arg0);
s32 func_802F6EE0(GyrocopterData* arg0);
void func_802F7178(GyrocopterData* arg0, Mtx4F* arg1);
void gyrocopterLoadPilot(u8 pilot, GyrocopterData* arg1);

void gyrocopterInit(void) {
    func_802F4F90();
    D_8034F384 = 0;
    D_80368880.unk0 = 8;
    D_80368880.unk4 = 0.0f;
    D_80368880.unk8 = 0.0f;
    D_80368880.unkC = 0.2f;
    D_80368880.unk10 = 0.04f;
    D_80368880.unk14 = 0.4f;
    D_80368880.unk18 = 0.16f;
    D_80368880.unk1C = 0.6f;
    D_80368880.unk20 = 0.36f;
    D_80368880.unk24 = 0.7f;
    D_80368880.unk28 = 0.49f;
    D_80368880.unk2C = 0.8f;
    D_80368880.unk30 = 0.64f;
    D_80368880.unk34 = 0.9f;
    D_80368880.unk38 = 0.81f;
    D_80368880.unk3C = 1.0f, D_80368880.unk40 = 1.0f;
}

void func_802F5AE0(u8 contIdx, u8 pilot, GyrocopterData* arg2, Camera* arg3) {
    uvMemSet(arg2, 0, sizeof(GyrocopterData));
    gyrocopterLoadPilot(pilot, arg2);
    arg2->objId = uvDobjAllocIdx();
    arg2->unk2 = 2;
    arg2->unk5D = 1;
    arg2->unk4 = 0;
    uvDobjModel(arg2->objId, arg2->modelId);
    uvDobjPosm(arg2->objId, 0, &arg2->unk10);
    uvDobjState(arg2->objId, arg2->unk2);
    func_80334454(MODEL_GYRO_SHADOW_COLUMN, MODEL_GYRO_SHADOW);
    func_803342F0(1.0f);
    func_803342FC(0.0f);
    func_803343D8(1);
    func_802F4F98(arg2);
    func_8030A140(arg2);
    func_80303230(arg2);
    arg2->contIdx = contIdx;
    arg2->unk58 = arg3;
    arg2->unk5E = 0;
    arg2->unk5F = 1;
    arg2->usingFuel = FALSE;
    arg2->unk738 = 0.0f;
    arg2->reticleX = 0.0f;
    arg2->reticleY = 0.0f;
    D_8034F380 = 0;
}

void gyrocopterEnterLeave(GyrocopterData* arg0) {
    Vec3F sp6C;
    Vec3F sp60;
    u8 sp5F;
    s32 sp58;
    s32 i;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv1;
    f32 temp_fa0;

    db_getstart(&arg0->unk10, &arg0->unk190, &sp5F, &arg0->fuel);
    if (sp5F != 0) {
        arg0->unkC0 = 0;
        arg0->unkB4 = 0.5f;
        arg0->unkF0 = (arg0->unkB4 * 94.24764f) + 10.47196f;
    } else {
        arg0->unkC0 = 1;
        arg0->unkF0 = 0.0f;
        arg0->unkB4 = 0.0f;
    }
    if (arg0->unkC0 == 1) {
        sp58 = 1;
        sp6C.x = sp60.x = arg0->unk10.m[3][0];
        sp6C.y = sp60.y = arg0->unk10.m[3][1];
        sp6C.z = arg0->unk10.m[3][2] + 0.5f;
        sp60.z = arg0->unk10.m[3][2] - 0.5f;
        db_getgnd(&sp6C, &sp60, &sp58, &arg0->unkF8, &arg0->unkFC, &arg0->unk100);
        sp44 = arg0->unk5EC[0].z - arg0->unk5EC[1].z;
        sp48 = arg0->unk5EC[0].y - arg0->unk5EC[1].y;
        arg0->unk5F = 0;
        arg0->unkDC = 0.0f;
        temp_fv0_2 = uvSqrtF(SQ(sp44) + SQ(sp48));
        sp4C = sp44 / temp_fv0_2;
        sp50 = sp48 / temp_fv0_2;
        temp_fv0_3 = uvSqrtF(SQ(arg0->unk5EC[1].y) + SQ(arg0->unk5EC[1].z));

        temp_fv1 = -arg0->unk5EC[1].z / temp_fv0_3;
        temp_fa0 = -arg0->unk5EC[1].y / temp_fv0_3;
        arg0->unk10.m[3][2] = (arg0->unkFC + (temp_fv0_3 * ((sp50 * temp_fv1) + (sp4C * temp_fa0)))) - 0.05f;
        arg0->unk10.m[2][2] = sp50;
        arg0->unk10.m[1][2] = sp4C;
        arg0->unk10.m[1][0] *= sp50;
        arg0->unk10.m[1][1] *= sp50;
        arg0->unk10.m[2][0] *= sp4C;
        arg0->unk10.m[2][1] *= -sp4C;
    } else {
        arg0->unk5F = 1;
    }
    arg0->unk2 = 2;
    uvDobjModel(arg0->objId, arg0->modelId);
    uvDobjPosm(arg0->objId, 0, &arg0->unk10);
    uvDobjState(arg0->objId, arg0->unk2);
    arg0->unkB0 = 0.0f;
    arg0->unkAC = 0.0f;
    arg0->unkB4 = 0.0f;
    arg0->unk5E = 0;
    arg0->reticleX = 0.0f;
    arg0->reticleY = 0.0f;
    arg0->unk663 = 0;
    arg0->unk664 = 0.0f;
    arg0->unk5D = 1;
    arg0->elapsedTime = 0.0f;

    for (i = 0; i < ARRAY_COUNT(arg0->unk690); i++) {
        arg0->unk690[i].unk48 = 0;
        arg0->unk690[i].unk44 = 0.0f;
    }
    func_80303714(arg0);
    arg0->unk5C = 0;
    arg0->unk68 = 0.8f;
    arg0->unk58->unk0 = 0x29;
    arg0->unk58->unk224 = 0.2f;
    arg0->unk58->unk4 = arg0->objId;
    arg0->unk58->unk6 = arg0->unk2;
    arg0->unk58->unk48 = 0.06f;
    arg0->unk58->unk4C = 1.0f;
    arg0->unk58->unk5C = arg0->unk628;
    arg0->unk58->unk60 = arg0->unk62C;
    arg0->unk58->unk64 = arg0->unk630;
    arg0->unk58->unk68.x = arg0->unk634;
    arg0->unk58->unk68.y = arg0->unk638;
    arg0->unk58->unk68.z = arg0->unk63C;
    arg0->unk58->unk74 = 0.0f;
    arg0->unk58->unk54 = 1.8f;
    arg0->unk58->unk58 = 7.9f;
    arg0->unk58->unk228 = 0.0f;
    uvModelGetProps(arg0->modelId, 1, &arg0->unk58->unk8, 0);
    func_802D45C4(arg0->unk58, arg0->unk68);
}

void func_802F5F80(GyrocopterData* arg0) {
    GyrocopterData_Unk690* var_s0;
    s32 i;

    uvDobjModel(arg0->objId, MODEL_WORLD);
    arg0->contIdx = 0xFFFF;
    arg0->objId = 0xFFFF;
    func_802F5304(arg0);

    for (i = 0; i < ARRAY_COUNT(arg0->unk690); i++) {
        var_s0 = &arg0->unk690[i];
        if (var_s0->unk4E != 0xFF) {
            uvModelGet(var_s0->unk4E, 0xFF);
        }
        if (var_s0->unk4C != 0xFF) {
            uvModelGet(var_s0->unk4C, 0xFF);
        }
        if (var_s0->unk4D != 0xFF) {
            uvModelGet(var_s0->unk4D, 0xFF);
        }
    }
    func_80334C70();
}

void gyrocopterMovementFrame(GyrocopterData* arg0, u8 gameState) {
    s32 pad[2];
    HUDState* hud;
    f32 xAxisInput;
    f32 yAxisInput;
    s32 buttons;
    u8 sp67;
    s32 temp_v0_3;
    f32 var_fa0;
    f32 var_fa0_2;
    f32 var_fv0_4;
    f32 sp48[3];

    if (arg0->unkC0 == 3) {
        func_802F764C(arg0);
        return;
    }
    if (func_802E6B5C() != 4) {
        func_803343D8(1);

        if (gameState == GAME_STATE_RESULTS) {
            func_802E65AC(&arg0->unk10, &D_80362690->terraId, &xAxisInput, &yAxisInput, &buttons);
        } else {
            xAxisInput = demoGetInputs(arg0->contIdx, INPUT_AXIS_X);
            yAxisInput = demoGetInputs(arg0->contIdx, INPUT_AXIS_Y);
            buttons = demoGetButtons(arg0->contIdx);
        }

        if ((arg0->elapsedTime > 0.0f) || (buttons & A_BUTTON)) {
            arg0->elapsedTime += D_8034F854;
        }

        arg0->unk9C = func_80313F08(&D_80368880, ABS_NOEQ(xAxisInput));
        if (xAxisInput < 0.0f) {
            arg0->unk9C = -arg0->unk9C;
        }

        arg0->unkA0 = func_80313F08(&D_80368880, ABS_NOEQ(yAxisInput));
        if (yAxisInput < 0.0f) {
            arg0->unkA0 = -arg0->unkA0;
        }

        if ((arg0->unkC0 == 0) || (arg0->unkC0 == 2)) {
            arg0->unk5F = 1;
        } else {
            if (arg0->unk5F != 0) {
                arg0->unk5F = 2;
            }
        }
        switch (arg0->unk5F) {
        case 0:
            if (buttons & A_BUTTON) {
                arg0->unkB0 += arg0->unk654 * D_8034F854;
                if (!arg0->usingFuel) {
                    arg0->usingFuel = TRUE;
                }
            }
            if (buttons & B_BUTTON) {
                arg0->unkB0 -= arg0->unk658 * D_8034F854;
            }
            if (!(buttons & (A_BUTTON | B_BUTTON))) {
                arg0->unkB0 -= arg0->unk65C * D_8034F854;
            }

            if (arg0->unkB0 < 0.0f) {
                arg0->unkB0 = 0.0f;
            } else if (arg0->unkB0 > 1.0f) {
                arg0->unkB0 = 1.0f;
            }
            arg0->unk9C = 0.0f;
            if (arg0->fuel <= 0.0f) {
                arg0->unk5F = 2;
            }
            break;
        case 1:
        case 2:
            if ((arg0->unk5F == 2) && (arg0->unkB0 == 0.0f) && (arg0->unk1A8 < 0.1f)) {
                arg0->unkB0 = 0.0f;
                arg0->usingFuel = FALSE;
            } else {
                if (buttons & A_BUTTON) {
                    arg0->unkB0 += arg0->unk648 * D_8034F854;
                    if (!arg0->usingFuel && (arg0->fuel > 0.0f)) {
                        arg0->usingFuel = TRUE;
                    }
                }
                if (buttons & B_BUTTON) {
                    arg0->unkB0 -= arg0->unk64C * D_8034F854;
                }
                if (!(buttons & (A_BUTTON | B_BUTTON))) {
                    if (arg0->unkB0 > 0.5f) {
                        arg0->unkB0 -= arg0->unk650 * D_8034F854;
                        if (arg0->unkB0 < 0.5f) {
                            arg0->unkB0 = 0.5f;
                        }
                    } else if (arg0->unkB0 < 0.5f) {
                        arg0->unkB0 += arg0->unk650 * D_8034F854;
                        if (arg0->unkB0 > 0.5f) {
                            arg0->unkB0 = 0.5f;
                        }
                    }
                }
            }
            if (arg0->unkB0 < 0.0f) {
                arg0->unkB0 = 0.0f;
            } else if (arg0->unkB0 > 1.0f) {
                arg0->unkB0 = 1.0f;
            }
            break;
        }
        arg0->unkB4 = arg0->unkB0;
        if ((arg0->unkC0 == 0) && (arg0->unkDC > 1.0f) && (ABS_NOEQ(arg0->unkB8) <= 0.12217303f) && (ABS_NOEQ(arg0->unkBC) <= 0.12217303f)) {
            temp_v0_3 = func_80314114(D_8034F380, buttons, Z_TRIG);
            switch (temp_v0_3) {
            default:
                break;
            case 1:
                if (func_802F6E74(arg0) >= 0) {
                    func_802F6DC8(arg0, 1);
                }
                break;
            case 0:
                if ((buttons & Z_TRIG) && (func_802F6E74(arg0) >= 0)) {
                    func_802F6DC8(arg0, 1);
                }
                break;
            case -1:
                if (arg0->unk5E != 0) {
                    func_802F6DC8(arg0, 0);
                    func_802F6EE0(arg0);
                }
                break;
            }
        } else {
            func_802F6DC8(arg0, 0);
        }
        if (buttons & Z_TRIG) {
            sp67 = 1;
        } else {
            sp67 = 0;
        }
        if (buttons & R_CBUTTONS) {
            if (!sp67) {
                var_fa0 = -1.5707961f;
            } else {
                var_fa0 = -0.10471974f;
            }
        } else if (buttons & L_CBUTTONS) {
            if (!sp67) {
                var_fa0 = 1.5707961f;
            } else {
                var_fa0 = 0.10471974f;
            }
        } else {
            var_fa0 = 0.0f;
        }
        if (!sp67) {
            var_fv0_4 = 2.0f;
        } else {
            var_fv0_4 = 3.0f;
        }
        if (!sp67) {
            arg0->unkB8 = func_80313BAC(var_fa0, arg0->unkB8, var_fv0_4);
        } else {
            arg0->unkB8 = func_80313AF4(var_fa0, arg0->unkB8, var_fv0_4);
        }

        if (buttons & U_CBUTTONS) {
            if (!sp67) {
                var_fa0 = -1.5707961f;
            } else {
                var_fa0 = -0.10471974f;
            }
        } else if (buttons & D_CBUTTONS) {
            if (!sp67) {
                var_fa0 = 1.5707961f;
            } else {
                var_fa0 = 0.10471974f;
            }
        } else {
            var_fa0 = 0.0f;
        }
        if (!sp67) {
            var_fv0_4 = 2.0f;
        } else {
            var_fv0_4 = 3.0f;
        }
        if (!sp67) {
            arg0->unkBC = func_80313BAC(var_fa0, arg0->unkBC, var_fv0_4);
        } else {
            arg0->unkBC = func_80313AF4(var_fa0, arg0->unkBC, var_fv0_4);
        }

        if (gameState != GAME_STATE_RESULTS) {
            func_8030399C(arg0);
        }
        func_802F50CC(arg0);
        func_802F7224(arg0);
        uvDobjPosm(arg0->objId, 0, &arg0->unk10);
        if (gameState != GAME_STATE_RESULTS) {
            sp48[0] = arg0->unkDC;
            sp48[1] = arg0->unkE8;
            sp48[2] = arg0->unkF0;
            func_802E682C(sp48, ARRAY_COUNT(sp48), 0);
        } else {
            func_802E6870(sp48, ARRAY_COUNT(sp48), NULL);
            arg0->unkDC = sp48[0];
            arg0->unkE8 = sp48[1];
            arg0->unkF0 = sp48[2];
        }
        if ((demoButtonPress(arg0->contIdx, R_TRIG) != 0) && (gameState != GAME_STATE_RESULTS)) {
            if (arg0->unk5C == 1) {
                func_8033F758(0x6A, 1.0f, 0.5f, 0.0f);
                arg0->unk5C = 0;
                arg0->unk68 = 0.8f;
            } else {
                func_8033F758(0x6A, 1.0f, 0.5f, 0.0f);
                arg0->unk5C = 1;
                arg0->unk68 = 0.8f;
            }
        }
        if (gameState != GAME_STATE_RESULTS) {
            if ((arg0->unkC0 == 2) || (arg0->unkC0 == 3)) {
                func_802D5884(arg0->unk58, 6);
            } else {
                func_802D5884(arg0->unk58, arg0->unk5C);
            }
            func_802D45C4(arg0->unk58, arg0->unk68);
        } else {
            func_802D5884(arg0->unk58, 5);
        }
        if (D_80362690->unkC[D_80362690->unk9C].unk7B != 0) {
            arg0->fuel = 1.0f;
        }
        if ((arg0->unk5C == 1) && (arg0->unkC0 != 2) && (gameState != GAME_STATE_RESULTS)) {
            arg0->unk5D = 0;
        } else {
            arg0->unk5D = 1;
        }
        if (arg0->unk5D != 0) {
            arg0->unk2 |= 2;
            uvDobjState(arg0->objId, arg0->unk2);
        } else {
            if (arg0->unk2 & 2) {
                arg0->unk2 &= ~2;
            }
            uvDobjState(arg0->objId, arg0->unk2);
        }
        if (gameState != GAME_STATE_RESULTS) {
            arg0->unk58->unk1A4 = arg0->unk190.y;
            arg0->unk58->unk78 = arg0->unkB8;
            arg0->unk58->unk7C = arg0->unkBC;
            arg0->unk58->unk6 = arg0->unk2;
            arg0->unk58->unk228 = arg0->unkDC;
            uvMat4Copy(&arg0->unk58->unk80, &arg0->unk10);
            hud = hudGetState();
            uvMat4Copy(&hud->unk28, &arg0->unk10);
            hud->renderFlags = HUD_RENDER_GYROCOPTER;
            if (arg0->unk5E != 0) {
                hud->renderFlags |= HUD_RENDER_RETICLE;
            } else {
                if (hud->renderFlags & HUD_RENDER_RETICLE) {
                    hud->renderFlags &= ~HUD_RENDER_RETICLE;
                }
            }
            hud->reticleX = arg0->reticleX;
            hud->reticleY = arg0->reticleY;
            hud->elapsedTime = arg0->elapsedTime;
            hud->fuel = arg0->fuel;
            hud->att.heading = arg0->unk10.m[3][2];
            hud->unk8C = arg0->unk19C.z * 16.0f * 0.7f;
            hud->altitude = arg0->unkDC * 0.7f;
            hud->altSeaLevel = arg0->unk10.m[3][2] * 0.7f;
            hud->speed = arg0->unk1A8 * 3.6f * 0.7f;
            if (hud->fuel > 0.0f) {
                hud->power = arg0->unkB4;
            } else {
                hud->power -= D_8034F854;
                if (hud->power < 0.0f) {
                    hud->power = 0.0f;
                } else if (hud->power > 1.0f) {
                    hud->power = 1.0f;
                }
            }
            if (hud->power < 0.0f) {
                hud->power = 0.0f;
            }
            if (arg0->unkC1 != 0) {
                hudWarningText(0x148, 1.5f, 8.0f);
                sndPlaySfx(0x69);
            } else {
                if ((arg0->fuel <= 0.0f) && !arg0->fuelEmpty) {
                    hudWarningText(0x4A, 1.5f, 8.0f);
                    arg0->fuelEmpty = TRUE;
                } else if ((arg0->fuel < 0.15f) && !arg0->hasLowFuel) {
                    hudWarningText(0x17B, 1.5f, 8.0f);
                    arg0->hasLowFuel = TRUE;
                } else if ((func_8032C080(NULL) != 0) && !arg0->pleaseLandShown) {
                    sndPlaySfx(5);
                    hudText_8031D8E0(0x1AA, 1.5f, 8.0f);
                    arg0->pleaseLandShown = TRUE;
                } else if ((taskGet_80346468() != 0) && !arg0->unkD5) {
                    hudText_8031D8E0(0x15D, 1.5f, 8.0f);
                    arg0->unkD5 = TRUE;
                }
            }
        }

        if ((arg0->unkC0 == 3) || (arg0->unkC0 == 2)) {
            hud->renderFlags = 0;
        }
        func_803344BC(&arg0->unk10, arg0->unkDC);
        D_8034F380 = buttons;
        func_802E06AC(&arg0->unk10);
        if (gameState != GAME_STATE_RESULTS) {
            if (arg0->unkC0 == 3) {
                func_802E66DC();
            }
            func_802E65AC(&arg0->unk10, &D_80362690->terraId, &xAxisInput, &yAxisInput, &buttons);
        }
    }
}

void func_802F6DC8(GyrocopterData* arg0, u8 arg1) {
    f32 temp_fv1;
    f32 temp_fa0;

    arg0->unk5E = arg1;
    if (arg1 != 0) {
        if (D_8034F384 == 0) {
            func_8033F758(0x59, 0.7f, 1.0f, 0.0f);
            D_8034F384 = 1;
        }
        arg0->reticleX = 0.0f;
        temp_fv1 = arg0->unk58->unk3C * -0.105104235;
        temp_fa0 = (-arg0->unk58->unk3C * arg0->unk58->unk34) / arg0->unk58->unk20;
        arg0->reticleY = (107.0f * temp_fv1) / temp_fa0;
    }
}

s32 func_802F6E74(GyrocopterData* arg0) {
    s32 i;

    if ((D_8034F850 - arg0->unk738) < 0.5f) {
        return -1;
    }

    for (i = 0; i < ARRAY_COUNT(arg0->unk690); i++) {
        if (arg0->unk690[i].unk48 == 0) {
            break;
        }
    }

    if (i == ARRAY_COUNT(arg0->unk690)) {
        return -1;
    }
    return i;
}

s32 func_802F6EE0(GyrocopterData* arg0) {
    GyrocopterData_Unk690* temp_s0;
    s32 temp_v0;

    temp_v0 = func_802F6E74(arg0);
    if (temp_v0 < 0) {
        return 0;
    }
    temp_s0 = &arg0->unk690[temp_v0];
    // FAKE
    if (1) { }
    temp_s0->unk4D = temp_s0->unk4C;
    temp_s0->unk4C = func_8021EFF0(4);
    if (temp_s0->unk4C != 0xFF) {
        uvModelGet(temp_s0->unk4C, 4);
    } else {
        return 0;
    }
    temp_s0->unk4E = func_8021EFF0(2);
    if (temp_s0->unk4E != 0xFF) {
        uvModelGet(temp_s0->unk4E, 2);
    } else {
        uvModelGet(temp_s0->unk4C, 0xFF);
        return 0;
    }

    func_802F7178(arg0, &temp_s0->unk0);
    temp_s0->unk40 = arg0->unk1A8 + 20.0f;
    temp_s0->unk48 = 1;
    temp_s0->unk44 = D_8034F850;
    arg0->unk738 = D_8034F850;
    uvFxProps(temp_s0->unk4C, FX_1(4.0f * D_8034F854), FX_5(0.8f, 0.8f, 0.8f, 1.0f), FX_6(0.2f, 0.2f, 0.2f, 0.0f), FX_3(0.4f, 0.4f, 0.4f), FX_8(0x147), FX_END);
    func_8021A4D8(temp_s0->unk4C, &temp_s0->unk0);
    uvFxProps(temp_s0->unk4E, FX_1(8.0f), FX_3(14.0f, 14.0f, 14.0f), FX_5(1.0f, 0.8f, 0.0f, 1.0f),
              FX_10(temp_s0->unk0.m[3][0], temp_s0->unk0.m[3][1], temp_s0->unk0.m[3][2]), FX_4(1.0f, 1.0f, 1.0f), FX_END);
    D_8034F384 = 0;
    return 1;
}

void func_802F7178(GyrocopterData* arg0, Mtx4F* arg1) {
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv1;

    uvMat4Copy(arg1, &arg0->unk58->unk108);
    uvMat4RotateAxis(arg1, -0.10471974f, 'x');
    temp_fv0 = arg0->unk10.m[3][0] - arg0->unk58->unk108.m[3][0];
    temp_fv1 = arg0->unk10.m[3][1] - arg0->unk58->unk108.m[3][1];
    temp_fa1 = arg0->unk10.m[3][2] - arg0->unk58->unk108.m[3][2];
    uvMat4LocalTranslate(arg1, 0.0f, 2.0f * uvSqrtF(SQ(temp_fv0) + SQ(temp_fv1) + SQ(temp_fa1)), 0.0f);
}

void func_802F7224(GyrocopterData* arg0) {
    GyrocopterData_Unk690* var_s0;
    f32 sp100;
    f32 spFC;
    f32 spF8;
    s32 spF4;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fs2;
    f32 temp_ft4;
    s32 temp_v0_2;
    Vec3F spD4;
    s32 var_s2;
    s32 i;

    func_802E1754(arg0->unk10.m[3][0], arg0->unk10.m[3][1], arg0->unk10.m[3][2], &spD4);

    for (i = 0; i < ARRAY_COUNT(arg0->unk690); i++) {
        var_s0 = &arg0->unk690[i];
        if (var_s0->unk48 == 2) {
            if ((D_8034F850 - var_s0->unk44) > 2.0f) {
                var_s0->unk48 = 0;
            }
        } else {
            if (var_s0->unk48 == 3) {
                if ((D_8034F850 - var_s0->unk44) > 2.0f) {
                    var_s0->unk48 = 0;
                }
            } else if (var_s0->unk48 == 1) {
                var_s0->unk40 += 200.0f * D_8034F854;
                if (var_s0->unk40 > 300.0f) {
                    var_s0->unk40 = 300.0f;
                }
                temp_fs0 = var_s0->unk0.m[3][0];
                temp_fs1 = var_s0->unk0.m[3][1];
                temp_fs2 = var_s0->unk0.m[3][2];
                temp_ft4 = var_s0->unk40 / 300.0f;
                var_s0->unk0.m[3][0] += var_s0->unk0.m[1][0] * var_s0->unk40 * D_8034F854;
                var_s0->unk0.m[3][1] += var_s0->unk0.m[1][1] * var_s0->unk40 * D_8034F854;
                var_s0->unk0.m[3][2] += var_s0->unk0.m[1][2] * var_s0->unk40 * D_8034F854;
                var_s0->unk0.m[3][0] += 6.0f * spD4.x * temp_ft4 * D_8034F854;
                var_s0->unk0.m[3][1] += 6.0f * spD4.y * temp_ft4 * D_8034F854;
                var_s0->unk0.m[3][2] += 6.0f * spD4.z * temp_ft4 * D_8034F854;
                if (var_s0->unk4C != 0xFF) {
                    func_8021A4D8(var_s0->unk4C, &var_s0->unk0);
                }
                if (var_s0->unk4E != 0xFF) {
                    func_8021A4D8(var_s0->unk4E, &var_s0->unk0);
                    if ((var_s0->unk44 + 0.2f) < D_8034F850) {
                        uvFxProps(var_s0->unk4E, FX_3(2.0f, 2.0f, 2.0f), FX_4(0.0f, 0.0f, 0.0f), FX_END);
                    }
                }
                if ((var_s0->unk44 + 5.0f) < D_8034F850) {
                    var_s0->unk48 = 3;
                    if (var_s0->unk4E != 0xFF) {
                        uvModelGet(var_s0->unk4E, 0xFF);
                        var_s0->unk4E = 0xFF;
                    }
                } else {
                    temp_v0_2 = func_802F9D28(arg0->objId, arg0->unk2, var_s0->unk0.m[3][0], var_s0->unk0.m[3][1], var_s0->unk0.m[3][2], temp_fs0, temp_fs1,
                                              temp_fs2, &sp100, &spFC, &spF8, &spF4);
                    if (temp_v0_2 != -1) {
                        var_s2 = 0;
                        func_802F8BF8(1, temp_v0_2, spF4, sp100, spFC, spF8);
                        var_s0->unk48 = 2;
                        if (temp_v0_2 != 4) {
                            targets_8034473C(spF4, 0);
                            var_s2 = falco_802E51E8(spF4, sp100, spFC, spF8);
                            toy_80348418(spF4, sp100, spFC, spF8, 3);
                        }
                        if (var_s2 == 0) {
                            func_8030B240(&var_s0->unk0);
                        }
                        if (var_s0->unk4E != 0xFF) {
                            uvModelGet(var_s0->unk4E, 0xFF);
                            var_s0->unk4E = 0xFF;
                        }
                    }
                }
            }
        }
    }
}

void func_802F764C(GyrocopterData* arg0) {
    Vec3F sp74;
    Vec3F sp68;
    Vec3F sp5C;
    Vec3F* var_a1;
    f32 sp54;
    s32 sp50;
    s32 sp4C;
    u8 sp4B;

    func_802D5884(arg0->unk58, 3);
    hudGetState()->renderFlags = 0;
    if (arg0->unkD0 != 0) {
        arg0->unk58->unk6 = 0;
        arg0->unk2 = arg0->unk58->unk6;
        uvDobjState(arg0->objId, arg0->unk2);
        arg0->unk58->unk190 = 12.0f;
    } else {
        arg0->unk58->unk190 = 6.0f;
    }
    if ((arg0->unkD0 == 0) && (arg0->unk662 == 0)) {
        sp74.x = arg0->unk10.m[3][0];
        sp68.x = arg0->unk668.x;
        sp74.y = arg0->unk10.m[3][1];
        sp68.y = arg0->unk668.y;
        sp74.z = arg0->unk10.m[3][2];
        sp68.z = arg0->unk668.z;
        sp4C = arg0->unk674;
        sp4B = db_getgnd(&sp68, &sp74, &sp4C, &sp50, &sp54, &sp5C);
        if (sp4B) {
            var_a1 = func_802E02EC();
        } else {
            var_a1 = &sp74;
            sp74.z = sp54;
        }
        func_802E05CC(&arg0->unk10, var_a1, &sp5C, 2);
        uvDobjPosm(arg0->objId, 0, &arg0->unk10);
        uvMat4Copy(&arg0->unk58->unk80, &arg0->unk10);
        if (func_802E0C30(sp4B, sp50) != 0) {
            arg0->unkD0 = 1;
            if (arg0->unk96 != 0xFF) {
                smokeProps(arg0->unk96, SMOKE_FX_8(0), SMOKE_FX_END);
            }
        } else {
            if (arg0->unk96 != 0xFF) {
                smokeProps(arg0->unk96, SMOKE_FX_6(arg0->unk10.m[3][0], arg0->unk10.m[3][1], arg0->unk10.m[3][2]), SMOKE_FX_END);
            }
            uvDobjModel(arg0->objId, arg0->crashModelId);
            uvDobjPosm(arg0->objId, 0, &arg0->unk10);
        }
    }
    func_803343D8(0);
    func_802F5910(arg0);
}

void gyrocopterLoadPilot(u8 pilot, GyrocopterData* arg1) {
    switch (pilot) {
    case PILOT_LARK:
        arg1->modelId = MODEL_GYRO_LARK;
        arg1->crashModelId = MODEL_GYRO_LARK_CRASHED;
        arg1->unk570 = 3;
        arg1->unk573 = 1;
        arg1->unk574 = 2;
        arg1->unk571 = 4;
        arg1->unk572 = 5;
        arg1->unk594 = 3.866f;
        arg1->unk598 = 0.0959931f;
        arg1->unk5A8 = 1.038f;
        arg1->unk5AC = 1.5707961f;
        arg1->unk590 = 0x37;
        arg1->unk591 = 0x39;
        arg1->unk592 = 0x38;
        arg1->unk640 = 110.0f;
        arg1->unk644 = 0.3490659f;
        arg1->unk648 = 0.25f;
        arg1->unk64C = 0.25f;
        arg1->unk650 = 0.125f;
        arg1->unk654 = 0.25f;
        arg1->unk658 = 0.25f;
        arg1->unk65C = 0.0625f;
        arg1->unk59C.x = -0.03f;
        arg1->unk59C.y = -0.095f;
        arg1->unk59C.z = 1.6f;
        arg1->unk5B0 = 0.009f;
        arg1->unk5B4 = -0.67f;
        arg1->unk5B8 = 0.44f;
        arg1->unk5BC.x = 0.001f;
        arg1->unk5BC.y = 1.362f;
        arg1->unk5BC.z = -0.003f;
        arg1->unk5C8.x = 0.006f;
        arg1->unk5C8.y = -1.334f;
        arg1->unk5C8.z = 0.141f;
        arg1->unk5D4 = -0.839f;
        arg1->unk5D8 = 0.0f;
        arg1->unk5DC = -0.234f;
        arg1->unk5E0 = 0.853f;
        arg1->unk5E4 = 0.0f;
        arg1->unk5E8 = -0.234f;
        arg1->unk5EC[0].x = 0.005f;
        arg1->unk5EC[0].y = 1.261f;
        arg1->unk5EC[0].z = -0.299f;
        arg1->unk5EC[3].x = 0.007f;
        arg1->unk5EC[3].y = -1.123f;
        arg1->unk5EC[3].z = -0.278f;
        arg1->unk5EC[1].x = -0.762f;
        arg1->unk5EC[1].y = -0.026f;
        arg1->unk5EC[1].z = -0.375f;
        arg1->unk5EC[2].x = 0.776f;
        arg1->unk5EC[2].y = -0.026f;
        arg1->unk5EC[2].z = -0.375f;
        arg1->unk61C = 0.0f;
        arg1->unk620 = -0.034f;
        arg1->unk624 = -0.099f;
        arg1->unk628 = 0.00f;
        arg1->unk62C = -4.45f;
        arg1->unk630 = 1.2f;
        arg1->unk634 = 0.0050f;
        arg1->unk638 = 0.455f;
        arg1->unk63C = 0.648f;
        arg1->unk538.x = 0.006f;
        arg1->unk538.y = 0.296f;
        arg1->unk538.z = 0.0f;
        arg1->unk578 = 0.522f, arg1->unk57C = 0.208f, arg1->unk580 = 0.208f;
        arg1->unk584 = 0.522f, arg1->unk588 = 0.208f, arg1->unk58C = 0.208f;
        break;
    case PILOT_GOOSE:
        arg1->modelId = MODEL_GYRO_GOOSE;
        arg1->crashModelId = MODEL_GYRO_GOOSE_CRASHED;
        arg1->unk570 = 3;
        arg1->unk573 = 1;
        arg1->unk574 = 2;
        arg1->unk571 = 4;
        arg1->unk572 = 5;
        arg1->unk594 = 3.866f;
        arg1->unk598 = 0.0959931f;
        arg1->unk5A8 = 1.038f;
        arg1->unk5AC = 1.5707961f;
        arg1->unk590 = 0x3A;
        arg1->unk591 = 0x3B;
        arg1->unk592 = 0x38;
        arg1->unk640 = 93.5f;
        arg1->unk644 = 0.4014257f;
        arg1->unk648 = 0.2f;
        arg1->unk64C = 0.2f;
        arg1->unk650 = 0.1f;
        arg1->unk654 = 0.2f;
        arg1->unk658 = 0.2f;
        arg1->unk65C = 0.05f;
        arg1->unk59C.x = -0.031f;
        arg1->unk59C.y = -0.021f;
        arg1->unk59C.z = 1.707f;
        arg1->unk5B0 = 0.005f;
        arg1->unk5B4 = -0.906f;
        arg1->unk5B8 = 0.459f;
        arg1->unk5BC.x = -0.001f;
        arg1->unk5BC.y = 1.96f;
        arg1->unk5BC.z = -0.039f;
        arg1->unk5C8.x = 0.005f;
        arg1->unk5C8.y = -1.868f;
        arg1->unk5C8.z = 0.142f;
        arg1->unk5D4 = -0.967f;
        arg1->unk5D8 = -0.146f;
        arg1->unk5DC = -0.251f;
        arg1->unk5E0 = 0.949f;
        arg1->unk5E4 = -0.146f;
        arg1->unk5E8 = -0.251f;
        arg1->unk5EC[0].x = 0.003f;
        arg1->unk5EC[0].y = 1.758f;
        arg1->unk5EC[0].z = -0.323f;
        arg1->unk5EC[3].x = 0.006f;
        arg1->unk5EC[3].y = -1.408f;
        arg1->unk5EC[3].z = -0.301f;
        arg1->unk5EC[1].x = -0.804f;
        arg1->unk5EC[1].y = -0.193f;
        arg1->unk5EC[1].z = -0.436f;
        arg1->unk5EC[2].x = 0.786f;
        arg1->unk5EC[2].y = -0.193f;
        arg1->unk5EC[2].z = -0.436f;
        arg1->unk61C = 0.0f;
        arg1->unk620 = -0.172f;
        arg1->unk624 = -0.121f;
        arg1->unk628 = 0.00f;
        arg1->unk62C = -4.45f;
        arg1->unk630 = 1.2f;
        arg1->unk634 = 0.002f;
        arg1->unk638 = 0.397f;
        arg1->unk63C = 0.678f;
        arg1->unk538.x = -0.006f;
        arg1->unk538.y = 0.295f;
        arg1->unk538.z = 0.0f;
        arg1->unk578 = 0.522f, arg1->unk57C = 0.208f, arg1->unk580 = 0.208f;
        arg1->unk584 = 0.522f, arg1->unk588 = 0.208f, arg1->unk58C = 0.208f;
        break;
    case PILOT_HAWK:
        arg1->modelId = MODEL_GYRO_HAWK;
        arg1->crashModelId = MODEL_GYRO_HAWK_CRASHED;
        arg1->unk570 = 3;
        arg1->unk573 = 1;
        arg1->unk574 = 2;
        arg1->unk571 = 4;
        arg1->unk572 = 5;
        arg1->unk594 = 3.866f;
        arg1->unk598 = 0.0959931f;
        arg1->unk5A8 = 1.038f;
        arg1->unk5AC = 1.5707961f;
        arg1->unk590 = 0x3C;
        arg1->unk591 = 0x3D;
        arg1->unk592 = 0x38;
        arg1->unk640 = 126.5f;
        arg1->unk644 = 0.296706f;
        arg1->unk648 = 0.325f;
        arg1->unk64C = 0.325f;
        arg1->unk650 = 0.1625f;
        arg1->unk654 = 0.325f;
        arg1->unk658 = 0.325f;
        arg1->unk65C = 0.08125f;
        arg1->unk59C.x = -0.02f;
        arg1->unk59C.y = -0.146f;
        arg1->unk59C.z = 1.65f;
        arg1->unk5B0 = 0.011f;
        arg1->unk5B4 = -0.733f;
        arg1->unk5B8 = 0.438f;
        arg1->unk5BC.x = 0.0f;
        arg1->unk5BC.y = 1.214f;
        arg1->unk5BC.z = -0.179f;
        arg1->unk5C8.x = 0.011f;
        arg1->unk5C8.y = -1.585f;
        arg1->unk5C8.z = 0.474f;
        arg1->unk5D4 = -1.025f;
        arg1->unk5D8 = -0.039f;
        arg1->unk5DC = -0.267f;
        arg1->unk5E0 = 1.021f;
        arg1->unk5E4 = -0.039f;
        arg1->unk5E8 = -0.267f;
        arg1->unk5EC[0].x = 0.009f;
        arg1->unk5EC[0].y = 1.243f;
        arg1->unk5EC[0].z = -0.429f;
        arg1->unk5EC[3].x = 0.012f;
        arg1->unk5EC[3].y = -1.237f;
        arg1->unk5EC[3].z = -0.317f;
        arg1->unk5EC[1].x = -0.863f;
        arg1->unk5EC[1].y = -0.085f;
        arg1->unk5EC[1].z = -0.451f;
        arg1->unk5EC[2].x = 0.859f;
        arg1->unk5EC[2].y = -0.085f;
        arg1->unk5EC[2].z = -0.451f;
        arg1->unk61C = 0.0f;
        arg1->unk620 = -0.047f;
        arg1->unk624 = -0.104f;
        arg1->unk628 = 0.00f;
        arg1->unk62C = -4.45f;
        arg1->unk630 = 1.2f;
        arg1->unk634 = 0.0090f;
        arg1->unk638 = 0.374f;
        arg1->unk63C = 0.71f;
        arg1->unk538.x = 0.005f;
        arg1->unk538.y = 0.247f;
        arg1->unk538.z = 0.0f;
        arg1->unk578 = 0.47f, arg1->unk57C = 0.412f, arg1->unk580 = 0.188f;
        arg1->unk584 = 0.6f, arg1->unk588 = 0.6f, arg1->unk58C = 0.6f;
        break;
    case PILOT_KIWI:
        arg1->modelId = MODEL_GYRO_KIWI;
        arg1->crashModelId = MODEL_GYRO_KIWI_CRASHED;
        arg1->unk570 = 3;
        arg1->unk573 = 1;
        arg1->unk574 = 2;
        arg1->unk571 = 4;
        arg1->unk572 = 5;
        arg1->unk594 = 3.866f;
        arg1->unk598 = 0.0959931f;
        arg1->unk5A8 = 1.038f;
        arg1->unk5AC = 1.5707961f;
        arg1->unk590 = 0x37;
        arg1->unk591 = 0x39;
        arg1->unk592 = 0x38;
        arg1->unk640 = 110.0f;
        arg1->unk644 = 0.3490659f;
        arg1->unk648 = 0.25f;
        arg1->unk64C = 0.25f;
        arg1->unk650 = 0.125f;
        arg1->unk654 = 0.25f;
        arg1->unk658 = 0.25f;
        arg1->unk65C = 0.0625f;
        arg1->unk59C.x = -0.031f;
        arg1->unk59C.y = -0.096f;
        arg1->unk59C.z = 1.62f;
        arg1->unk5B0 = 0.0090f;
        arg1->unk5B4 = -0.673f;
        arg1->unk5B8 = 0.443f;
        arg1->unk5BC.x = 0.002f;
        arg1->unk5BC.y = 1.37f;
        arg1->unk5BC.z = -0.003f;
        arg1->unk5C8.x = 0.007f;
        arg1->unk5C8.y = -1.341f;
        arg1->unk5C8.z = 0.142f;
        arg1->unk5D4 = -0.843f;
        arg1->unk5D8 = 0.179f;
        arg1->unk5DC = -0.235f;
        arg1->unk5E0 = 0.858f;
        arg1->unk5E4 = 0.179f;
        arg1->unk5E8 = -0.235f;
        arg1->unk5EC[0].x = 0.005f;
        arg1->unk5EC[0].y = 1.268f;
        arg1->unk5EC[0].z = -0.3f;
        arg1->unk5EC[3].x = 0.008f;
        arg1->unk5EC[3].y = -1.129f;
        arg1->unk5EC[3].z = -0.28f;
        arg1->unk5EC[1].x = -0.765f;
        arg1->unk5EC[1].y = -0.027f;
        arg1->unk5EC[1].z = -0.377f;
        arg1->unk5EC[2].x = 0.78f;
        arg1->unk5EC[2].y = -0.027f;
        arg1->unk5EC[2].z = -0.377f;
        arg1->unk61C = 0.0f;
        arg1->unk620 = -0.034f;
        arg1->unk624 = -0.101f;
        arg1->unk628 = 0.00f;
        arg1->unk62C = -4.45f;
        arg1->unk630 = 1.2f;
        arg1->unk634 = 0.00f;
        arg1->unk638 = 0.385f;
        arg1->unk63C = 0.568f;
        arg1->unk538.x = 0.006f;
        arg1->unk538.y = 0.297f;
        arg1->unk538.z = 0.0f;
        arg1->unk578 = 0.6f, arg1->unk57C = 0.6f, arg1->unk580 = 0.6f;
        arg1->unk584 = 0.6f, arg1->unk588 = 0.6f, arg1->unk58C = 0.6f;
        break;
    case PILOT_IBIS:
        arg1->modelId = MODEL_GYRO_IBIS;
        arg1->crashModelId = MODEL_GYRO_IBIS_CRASHED;
        arg1->unk570 = 3;
        arg1->unk573 = 1;
        arg1->unk574 = 2;
        arg1->unk571 = 4;
        arg1->unk572 = 5;
        arg1->unk594 = 3.866f;
        arg1->unk598 = 0.0959931f;
        arg1->unk5A8 = 1.038f;
        arg1->unk5AC = 1.5707961f;
        arg1->unk590 = 0x3A;
        arg1->unk591 = 0x3B;
        arg1->unk592 = 0x38;
        arg1->unk640 = 93.5f;
        arg1->unk644 = 0.4014257f;
        arg1->unk648 = 0.2f;
        arg1->unk64C = 0.2f;
        arg1->unk650 = 0.1f;
        arg1->unk654 = 0.2f;
        arg1->unk658 = 0.2f;
        arg1->unk65C = 0.05f;
        arg1->unk59C.x = -0.031f;
        arg1->unk59C.y = -0.021f;
        arg1->unk59C.z = 1.707f;
        arg1->unk5B0 = 0.028f;
        arg1->unk5B4 = -0.892f;
        arg1->unk5B8 = 0.452f;
        arg1->unk5BC.x = -0.001f;
        arg1->unk5BC.y = 1.966f;
        arg1->unk5BC.z = -0.038f;
        arg1->unk5C8.x = 0.005f;
        arg1->unk5C8.y = -1.872f;
        arg1->unk5C8.z = 0.142f;
        arg1->unk5D4 = -0.969f;
        arg1->unk5D8 = -0.146f;
        arg1->unk5DC = -0.252f;
        arg1->unk5E0 = 0.951f;
        arg1->unk5E4 = -0.146f;
        arg1->unk5E8 = -0.252f;
        arg1->unk5EC[0].x = 0.003f;
        arg1->unk5EC[0].y = 1.762f;
        arg1->unk5EC[0].z = -0.323f;
        arg1->unk5EC[3].x = 0.006f;
        arg1->unk5EC[3].y = -1.412f;
        arg1->unk5EC[3].z = -0.302f;
        arg1->unk5EC[1].x = -0.806f;
        arg1->unk5EC[1].y = -0.193f;
        arg1->unk5EC[1].z = -0.437f;
        arg1->unk5EC[2].x = 0.788f;
        arg1->unk5EC[2].y = -0.193f;
        arg1->unk5EC[2].z = -0.437f;
        arg1->unk61C = 0.0f;
        arg1->unk620 = -0.172f;
        arg1->unk624 = -0.118f;
        arg1->unk628 = 0.00f;
        arg1->unk62C = -4.45f;
        arg1->unk630 = 1.2f;
        arg1->unk634 = 0.001f;
        arg1->unk638 = 0.381f;
        arg1->unk63C = 0.623f;
        arg1->unk538.x = -0.003f;
        arg1->unk538.y = 0.296f;
        arg1->unk538.z = 0.0f;
        arg1->unk578 = 0.102f, arg1->unk57C = 0.086f, arg1->unk580 = 0.22f;
        arg1->unk584 = 0.6f, arg1->unk588 = 0.6f, arg1->unk58C = 0.6f;
        break;
    case PILOT_ROBIN:
        arg1->modelId = MODEL_GYRO_ROBIN;
        arg1->crashModelId = MODEL_GYRO_ROBIN_CRASHED;
        arg1->unk570 = 3;
        arg1->unk573 = 1;
        arg1->unk574 = 2;
        arg1->unk571 = 4;
        arg1->unk572 = 5;
        arg1->unk594 = 3.866f;
        arg1->unk598 = 0.0959931f;
        arg1->unk5A8 = 1.038f;
        arg1->unk5AC = 1.5707961f;
        arg1->unk590 = 0x3C;
        arg1->unk591 = 0x3D;
        arg1->unk592 = 0x38;
        arg1->unk640 = 126.5f;
        arg1->unk644 = 0.296706f;
        arg1->unk648 = 0.325f;
        arg1->unk64C = 0.325f;
        arg1->unk650 = 0.1625f;
        arg1->unk654 = 0.325f;
        arg1->unk658 = 0.325f;
        arg1->unk65C = 0.08125f;
        arg1->unk59C.x = -0.031f;
        arg1->unk59C.y = -0.146f;
        arg1->unk59C.z = 1.676f;
        arg1->unk5B0 = 0.011f;
        arg1->unk5B4 = -0.74f;
        arg1->unk5B8 = 0.442f;
        arg1->unk5BC.x = 0.0f;
        arg1->unk5BC.y = 1.227f;
        arg1->unk5BC.z = -0.18f;
        arg1->unk5C8.x = 0.011f;
        arg1->unk5C8.y = -1.601f;
        arg1->unk5C8.z = 0.478f;
        arg1->unk5D4 = -1.03f;
        arg1->unk5D8 = -0.039f;
        arg1->unk5DC = -0.27f;
        arg1->unk5E0 = 1.032f;
        arg1->unk5E4 = -0.039f;
        arg1->unk5E8 = -0.27f;
        arg1->unk5EC[0].x = 0.0090f;
        arg1->unk5EC[0].y = 1.255f;
        arg1->unk5EC[0].z = -0.433f;
        arg1->unk5EC[3].x = 0.012f;
        arg1->unk5EC[3].y = -1.25f;
        arg1->unk5EC[3].z = -0.32f;
        arg1->unk5EC[1].x = -0.867f;
        arg1->unk5EC[1].y = -0.086f;
        arg1->unk5EC[1].z = -0.455f;
        arg1->unk5EC[2].x = 0.868f;
        arg1->unk5EC[2].y = -0.086f;
        arg1->unk5EC[2].z = -0.455f;
        arg1->unk61C = 0.0f;
        arg1->unk620 = -0.05f;
        arg1->unk624 = -0.077f;
        arg1->unk628 = 0.00f;
        arg1->unk62C = -4.45f;
        arg1->unk630 = 1.2f;
        arg1->unk634 = 0.013f;
        arg1->unk638 = 0.384f;
        arg1->unk63C = 0.62f;
        arg1->unk538.x = 0.006f;
        arg1->unk538.y = 0.249f;
        arg1->unk538.z = 0.0f;
        arg1->unk578 = 0.102f, arg1->unk57C = 0.086f, arg1->unk580 = 0.22f;
        arg1->unk584 = 0.6f, arg1->unk588 = 0.6f, arg1->unk58C = 0.6f;
        break;
    default:
        break;
    }
}
