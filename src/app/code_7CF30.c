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
#include "app/gyrocopter.h"
#include "app/hud.h"
#include "app/shadow.h"
#include "app/smoke.h"
#include "app/snd.h"
#include "app/targets.h"
#include "app/text_data.h"
#include "app/toys.h"
#include "app/code_66F70.h"
#include "app/code_7C4C0.h"
#include "app/code_7FE00.h"
#include "app/code_9A960.h"
#include "app/code_B2900.h"

s32 D_8034F380 = 0;
s32 D_8034F384 = 0;

Unk803599D0 D_80368880;

void func_802F7224(GyrocopterData* gcData);
void func_802F6DC8(GyrocopterData* gcData, u8 unkFlag);
s32 func_802F6E74(GyrocopterData* gcData);
s32 func_802F6EE0(GyrocopterData* gcData);
void func_802F7178(GyrocopterData* gcData, Mtx4F* mat);
void gyrocopterLoadPilot(u8 pilot, GyrocopterData* gcData);

void gyrocopterInit(void) {
    func_802F4F90();
    D_8034F384 = 0;
    D_80368880.count = 8;
    D_80368880.unk4[0].x = 0.0f, D_80368880.unk4[0].y = 0.0f;
    D_80368880.unk4[1].x = 0.2f, D_80368880.unk4[1].y = 0.04f;
    D_80368880.unk4[2].x = 0.4f, D_80368880.unk4[2].y = 0.16f;
    D_80368880.unk4[3].x = 0.6f, D_80368880.unk4[3].y = 0.36f;
    D_80368880.unk4[4].x = 0.7f, D_80368880.unk4[4].y = 0.49f;
    D_80368880.unk4[5].x = 0.8f, D_80368880.unk4[5].y = 0.64f;
    D_80368880.unk4[6].x = 0.9f, D_80368880.unk4[6].y = 0.81f;
    D_80368880.unk4[7].x = 1.0f, D_80368880.unk4[7].y = 1.0f;
}

void gyrocopterLoadLevel(u8 contIdx, u8 pilot, GyrocopterData* gcData, Camera* camera) {
    uvMemSet(gcData, 0, sizeof(GyrocopterData));
    gyrocopterLoadPilot(pilot, gcData);
    gcData->objId = uvDobjAllocIdx();
    gcData->unk2 = 2;
    gcData->unk5D = 1;
    gcData->unk4 = 0;
    uvDobjModel(gcData->objId, gcData->modelId);
    uvDobjPosm(gcData->objId, 0, &gcData->unk10);
    uvDobjState(gcData->objId, gcData->unk2);
    shadow_80334454(MODEL_GYRO_SHADOW_COLUMN, MODEL_GYRO_SHADOW);
    shadow_803342F0(1.0f);
    shadow_803342FC(0.0f);
    shadow_803343D8(1);
    func_802F4F98(gcData);
    func_8030A140(gcData);
    func_80303230(gcData);
    gcData->contIdx = contIdx;
    gcData->camera = camera;
    gcData->unk5E = 0;
    gcData->unk5F = 1;
    gcData->usingFuel = FALSE;
    gcData->unk738 = 0.0f;
    gcData->reticleX = 0.0f;
    gcData->reticleY = 0.0f;
    D_8034F380 = 0;
}

void gyrocopterEnterLeave(GyrocopterData* gcData) {
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

    db_getstart(&gcData->unk10, &gcData->unk190, &sp5F, &gcData->fuel);
    if (sp5F != 0) {
        gcData->unkC0 = 0;
        gcData->unkB4 = 0.5f;
        gcData->unkF0 = (gcData->unkB4 * 94.24764f) + 10.47196f;
    } else {
        gcData->unkC0 = 1;
        gcData->unkF0 = 0.0f;
        gcData->unkB4 = 0.0f;
    }
    if (gcData->unkC0 == 1) {
        sp58 = 1;
        sp6C.x = sp60.x = gcData->unk10.m[3][0];
        sp6C.y = sp60.y = gcData->unk10.m[3][1];
        sp6C.z = gcData->unk10.m[3][2] + 0.5f;
        sp60.z = gcData->unk10.m[3][2] - 0.5f;
        db_getgnd(&sp6C, &sp60, &sp58, &gcData->unkF8, &gcData->unkFC, &gcData->unk100);
        sp44 = gcData->unk5EC[0].z - gcData->unk5EC[1].z;
        sp48 = gcData->unk5EC[0].y - gcData->unk5EC[1].y;
        gcData->unk5F = 0;
        gcData->unkDC = 0.0f;
        temp_fv0_2 = uvSqrtF(SQ(sp44) + SQ(sp48));
        sp4C = sp44 / temp_fv0_2;
        sp50 = sp48 / temp_fv0_2;
        temp_fv0_3 = uvSqrtF(SQ(gcData->unk5EC[1].y) + SQ(gcData->unk5EC[1].z));

        temp_fv1 = -gcData->unk5EC[1].z / temp_fv0_3;
        temp_fa0 = -gcData->unk5EC[1].y / temp_fv0_3;
        gcData->unk10.m[3][2] = (gcData->unkFC + (temp_fv0_3 * ((sp50 * temp_fv1) + (sp4C * temp_fa0)))) - 0.05f;
        gcData->unk10.m[2][2] = sp50;
        gcData->unk10.m[1][2] = sp4C;
        gcData->unk10.m[1][0] *= sp50;
        gcData->unk10.m[1][1] *= sp50;
        gcData->unk10.m[2][0] *= sp4C;
        gcData->unk10.m[2][1] *= -sp4C;
    } else {
        gcData->unk5F = 1;
    }
    gcData->unk2 = 2;
    uvDobjModel(gcData->objId, gcData->modelId);
    uvDobjPosm(gcData->objId, 0, &gcData->unk10);
    uvDobjState(gcData->objId, gcData->unk2);
    gcData->unkB0 = 0.0f;
    gcData->unkAC = 0.0f;
    gcData->unkB4 = 0.0f;
    gcData->unk5E = 0;
    gcData->reticleX = 0.0f;
    gcData->reticleY = 0.0f;
    gcData->unk663 = 0;
    gcData->unk664 = 0.0f;
    gcData->unk5D = 1;
    gcData->elapsedTime = 0.0f;

    for (i = 0; i < ARRAY_COUNT(gcData->unk690); i++) {
        gcData->unk690[i].unk48 = 0;
        gcData->unk690[i].unk44 = 0.0f;
    }
    func_80303714(gcData);
    gcData->unk5C = 0;
    gcData->unk68 = 0.8f;
    gcData->camera->unk0 = 0x29;
    gcData->camera->unk224 = 0.2f;
    gcData->camera->unk4 = gcData->objId;
    gcData->camera->unk6 = gcData->unk2;
    gcData->camera->unk48 = 0.06f;
    gcData->camera->unk4C = 1.0f;
    gcData->camera->unk5C = gcData->unk628;
    gcData->camera->unk60 = gcData->unk62C;
    gcData->camera->unk64 = gcData->unk630;
    gcData->camera->unk68.x = gcData->unk634;
    gcData->camera->unk68.y = gcData->unk638;
    gcData->camera->unk68.z = gcData->unk63C;
    gcData->camera->unk74 = 0.0f;
    gcData->camera->unk54 = 1.8f;
    gcData->camera->unk58 = 7.9f;
    gcData->camera->unk228 = 0.0f;
    uvModelGetProps(gcData->modelId, MODEL_PROP_UNK1(&gcData->camera->unk8), MODEL_PROP_END);
    camera_802D45C4(gcData->camera, gcData->unk68);
}

void func_802F5F80(GyrocopterData* gcData) {
    GyrocopterData_Unk690* var_s0;
    s32 i;

    uvDobjModel(gcData->objId, MODEL_WORLD);
    gcData->contIdx = 0xFFFF;
    gcData->objId = 0xFFFF;
    func_802F5304(gcData);

    for (i = 0; i < ARRAY_COUNT(gcData->unk690); i++) {
        var_s0 = &gcData->unk690[i];
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
    shadow_80334C70();
}

void gyrocopterMovementFrame(GyrocopterData* gcData, u8 gameState) {
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

    if (gcData->unkC0 == 3) {
        func_802F764C(gcData);
        return;
    }
    if (fdr_802E6B5C() != 4) {
        shadow_803343D8(1);

        if (gameState == GAME_STATE_RESULTS) {
            fdr_802E65AC(&gcData->unk10, &D_80362690->terraId, &xAxisInput, &yAxisInput, &buttons);
        } else {
            xAxisInput = demoGetInputs(gcData->contIdx, INPUT_AXIS_X);
            yAxisInput = demoGetInputs(gcData->contIdx, INPUT_AXIS_Y);
            buttons = demoGetButtons(gcData->contIdx);
        }

        if ((gcData->elapsedTime > 0.0f) || (buttons & A_BUTTON)) {
            gcData->elapsedTime += D_8034F854;
        }

        gcData->unk9C = func_80313F08(&D_80368880, ABS_NOEQ(xAxisInput));
        if (xAxisInput < 0.0f) {
            gcData->unk9C = -gcData->unk9C;
        }

        gcData->unkA0 = func_80313F08(&D_80368880, ABS_NOEQ(yAxisInput));
        if (yAxisInput < 0.0f) {
            gcData->unkA0 = -gcData->unkA0;
        }

        if ((gcData->unkC0 == 0) || (gcData->unkC0 == 2)) {
            gcData->unk5F = 1;
        } else {
            if (gcData->unk5F != 0) {
                gcData->unk5F = 2;
            }
        }
        switch (gcData->unk5F) {
        case 0:
            if (buttons & A_BUTTON) {
                gcData->unkB0 += gcData->unk654 * D_8034F854;
                if (!gcData->usingFuel) {
                    gcData->usingFuel = TRUE;
                }
            }
            if (buttons & B_BUTTON) {
                gcData->unkB0 -= gcData->unk658 * D_8034F854;
            }
            if (!(buttons & (A_BUTTON | B_BUTTON))) {
                gcData->unkB0 -= gcData->unk65C * D_8034F854;
            }

            if (gcData->unkB0 < 0.0f) {
                gcData->unkB0 = 0.0f;
            } else if (gcData->unkB0 > 1.0f) {
                gcData->unkB0 = 1.0f;
            }
            gcData->unk9C = 0.0f;
            if (gcData->fuel <= 0.0f) {
                gcData->unk5F = 2;
            }
            break;
        case 1:
        case 2:
            if ((gcData->unk5F == 2) && (gcData->unkB0 == 0.0f) && (gcData->unk1A8 < 0.1f)) {
                gcData->unkB0 = 0.0f;
                gcData->usingFuel = FALSE;
            } else {
                if (buttons & A_BUTTON) {
                    gcData->unkB0 += gcData->unk648 * D_8034F854;
                    if (!gcData->usingFuel && (gcData->fuel > 0.0f)) {
                        gcData->usingFuel = TRUE;
                    }
                }
                if (buttons & B_BUTTON) {
                    gcData->unkB0 -= gcData->unk64C * D_8034F854;
                }
                if (!(buttons & (A_BUTTON | B_BUTTON))) {
                    if (gcData->unkB0 > 0.5f) {
                        gcData->unkB0 -= gcData->unk650 * D_8034F854;
                        if (gcData->unkB0 < 0.5f) {
                            gcData->unkB0 = 0.5f;
                        }
                    } else if (gcData->unkB0 < 0.5f) {
                        gcData->unkB0 += gcData->unk650 * D_8034F854;
                        if (gcData->unkB0 > 0.5f) {
                            gcData->unkB0 = 0.5f;
                        }
                    }
                }
            }
            if (gcData->unkB0 < 0.0f) {
                gcData->unkB0 = 0.0f;
            } else if (gcData->unkB0 > 1.0f) {
                gcData->unkB0 = 1.0f;
            }
            break;
        }
        gcData->unkB4 = gcData->unkB0;
        if ((gcData->unkC0 == 0) && (gcData->unkDC > 1.0f) && (ABS_NOEQ(gcData->unkB8) <= 0.12217303f) && (ABS_NOEQ(gcData->unkBC) <= 0.12217303f)) {
            temp_v0_3 = func_80314114(D_8034F380, buttons, Z_TRIG);
            switch (temp_v0_3) {
            default:
                break;
            case 1:
                if (func_802F6E74(gcData) >= 0) {
                    func_802F6DC8(gcData, 1);
                }
                break;
            case 0:
                if ((buttons & Z_TRIG) && (func_802F6E74(gcData) >= 0)) {
                    func_802F6DC8(gcData, 1);
                }
                break;
            case -1:
                if (gcData->unk5E != 0) {
                    func_802F6DC8(gcData, 0);
                    func_802F6EE0(gcData);
                }
                break;
            }
        } else {
            func_802F6DC8(gcData, 0);
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
            gcData->unkB8 = func_80313BAC(var_fa0, gcData->unkB8, var_fv0_4);
        } else {
            gcData->unkB8 = func_80313AF4(var_fa0, gcData->unkB8, var_fv0_4);
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
            gcData->unkBC = func_80313BAC(var_fa0, gcData->unkBC, var_fv0_4);
        } else {
            gcData->unkBC = func_80313AF4(var_fa0, gcData->unkBC, var_fv0_4);
        }

        if (gameState != GAME_STATE_RESULTS) {
            func_8030399C(gcData);
        }
        func_802F50CC(gcData);
        func_802F7224(gcData);
        uvDobjPosm(gcData->objId, 0, &gcData->unk10);
        if (gameState != GAME_STATE_RESULTS) {
            sp48[0] = gcData->unkDC;
            sp48[1] = gcData->unkE8;
            sp48[2] = gcData->unkF0;
            fdr_802E682C(sp48, ARRAY_COUNT(sp48), 0);
        } else {
            fdr_802E6870(sp48, ARRAY_COUNT(sp48), NULL);
            gcData->unkDC = sp48[0];
            gcData->unkE8 = sp48[1];
            gcData->unkF0 = sp48[2];
        }
        if ((demoButtonPress(gcData->contIdx, R_TRIG) != 0) && (gameState != GAME_STATE_RESULTS)) {
            if (gcData->unk5C == 1) {
                sndPlaySfxVolPitchPan(0x6A, 1.0f, 0.5f, 0.0f);
                gcData->unk5C = 0;
                gcData->unk68 = 0.8f;
            } else {
                sndPlaySfxVolPitchPan(0x6A, 1.0f, 0.5f, 0.0f);
                gcData->unk5C = 1;
                gcData->unk68 = 0.8f;
            }
        }
        if (gameState != GAME_STATE_RESULTS) {
            if ((gcData->unkC0 == 2) || (gcData->unkC0 == 3)) {
                camera_802D5884(gcData->camera, 6);
            } else {
                camera_802D5884(gcData->camera, gcData->unk5C);
            }
            camera_802D45C4(gcData->camera, gcData->unk68);
        } else {
            camera_802D5884(gcData->camera, 5);
        }
        if (D_80362690->unkC[D_80362690->unk9C].unk7B != 0) {
            gcData->fuel = 1.0f;
        }
        if ((gcData->unk5C == 1) && (gcData->unkC0 != 2) && (gameState != GAME_STATE_RESULTS)) {
            gcData->unk5D = 0;
        } else {
            gcData->unk5D = 1;
        }
        if (gcData->unk5D != 0) {
            gcData->unk2 |= 2;
            uvDobjState(gcData->objId, gcData->unk2);
        } else {
            if (gcData->unk2 & 2) {
                gcData->unk2 &= ~2;
            }
            uvDobjState(gcData->objId, gcData->unk2);
        }
        if (gameState != GAME_STATE_RESULTS) {
            gcData->camera->unk1A4 = gcData->unk190.y;
            gcData->camera->unk78 = gcData->unkB8;
            gcData->camera->unk7C = gcData->unkBC;
            gcData->camera->unk6 = gcData->unk2;
            gcData->camera->unk228 = gcData->unkDC;
            uvMat4Copy(&gcData->camera->unk80, &gcData->unk10);
            hud = hudGetState();
            uvMat4Copy(&hud->unk28, &gcData->unk10);
            hud->renderFlags = HUD_RENDER_GYROCOPTER;
            if (gcData->unk5E != 0) {
                hud->renderFlags |= HUD_RENDER_RETICLE;
            } else {
                if (hud->renderFlags & HUD_RENDER_RETICLE) {
                    hud->renderFlags &= ~HUD_RENDER_RETICLE;
                }
            }
            hud->reticleX = gcData->reticleX;
            hud->reticleY = gcData->reticleY;
            hud->elapsedTime = gcData->elapsedTime;
            hud->fuel = gcData->fuel;
            hud->att.heading = gcData->unk10.m[3][2];
            hud->unk8C = gcData->unk19C.z * 16.0f * 0.7f;
            hud->altitude = gcData->unkDC * 0.7f;
            hud->altSeaLevel = gcData->unk10.m[3][2] * 0.7f;
            hud->speed = gcData->unk1A8 * 3.6f * 0.7f;
            if (hud->fuel > 0.0f) {
                hud->power = gcData->unkB4;
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
            if (gcData->unkC1 != 0) {
                hudWarningText(TEXT_OFF_5, 1.5f, 8.0f);
                sndPlaySfx(SFX_UNK_105);
            } else {
                if ((gcData->fuel <= 0.0f) && !gcData->fuelEmpty) {
                    hudWarningText(TEXT_FUEL_OUT, 1.5f, 8.0f);
                    gcData->fuelEmpty = TRUE;
                } else if ((gcData->fuel < 0.15f) && !gcData->hasLowFuel) {
                    hudWarningText(TEXT_FUEL_WAR, 1.5f, 8.0f);
                    gcData->hasLowFuel = TRUE;
                } else if ((func_8032C080(NULL) != 0) && !gcData->pleaseLandShown) {
                    sndPlaySfx(SFX_UI_HUD_CHIME);
                    hudText_8031D8E0(TEXT_LAND_NOW2, 1.5f, 8.0f);
                    gcData->pleaseLandShown = TRUE;
                } else if ((taskGet_80346468() != 0) && !gcData->unkD5) {
                    hudText_8031D8E0(TEXT_GOAL, 1.5f, 8.0f);
                    gcData->unkD5 = TRUE;
                }
            }
        }

        if ((gcData->unkC0 == 3) || (gcData->unkC0 == 2)) {
            hud->renderFlags = 0;
        }
        shadow_803344BC(&gcData->unk10, gcData->unkDC);
        D_8034F380 = buttons;
        func_802E06AC(&gcData->unk10);
        if (gameState != GAME_STATE_RESULTS) {
            if (gcData->unkC0 == 3) {
                fdr_802E66DC();
            }
            fdr_802E65AC(&gcData->unk10, &D_80362690->terraId, &xAxisInput, &yAxisInput, &buttons);
        }
    }
}

void func_802F6DC8(GyrocopterData* gcData, u8 unkFlag) {
    f32 temp_fv1;
    f32 temp_fa0;

    gcData->unk5E = unkFlag;
    if (unkFlag != 0) {
        if (D_8034F384 == 0) {
            sndPlaySfxVolPitchPan(SFX_UI_TARGET_APPEAR, 0.7f, 1.0f, 0.0f);
            D_8034F384 = 1;
        }
        gcData->reticleX = 0.0f;
        temp_fv1 = gcData->camera->clipNear * -0.105104235;
        temp_fa0 = (-gcData->camera->clipNear * gcData->camera->clipY0) / gcData->camera->unk20;
        gcData->reticleY = (107.0f * temp_fv1) / temp_fa0;
    }
}

s32 func_802F6E74(GyrocopterData* gcData) {
    s32 i;

    if ((D_8034F850 - gcData->unk738) < 0.5f) {
        return -1;
    }

    for (i = 0; i < ARRAY_COUNT(gcData->unk690); i++) {
        if (gcData->unk690[i].unk48 == 0) {
            break;
        }
    }

    if (i == ARRAY_COUNT(gcData->unk690)) {
        return -1;
    }
    return i;
}

s32 func_802F6EE0(GyrocopterData* gcData) {
    GyrocopterData_Unk690* temp_s0;
    s32 temp_v0;

    temp_v0 = func_802F6E74(gcData);
    if (temp_v0 < 0) {
        return 0;
    }
    temp_s0 = &gcData->unk690[temp_v0];
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

    func_802F7178(gcData, &temp_s0->unk0);
    temp_s0->unk40 = gcData->unk1A8 + 20.0f;
    temp_s0->unk48 = 1;
    temp_s0->unk44 = D_8034F850;
    gcData->unk738 = D_8034F850;
    // clang-format off
    uvFxProps(
        temp_s0->unk4C,
        FX_PROP_1(4.0f * D_8034F854),
        FX_PROP_5(0.8f, 0.8f, 0.8f, 1.0f),
        FX_PROP_6(0.2f, 0.2f, 0.2f, 0.0f),
        FX_PROP_3(0.4f, 0.4f, 0.4f),
        FX_PROP_8(0x147),
        FX_PROP_END
    );
    func_8021A4D8(temp_s0->unk4C, &temp_s0->unk0);
    uvFxProps(
        temp_s0->unk4E,
        FX_PROP_1(8.0f),
        FX_PROP_3(14.0f, 14.0f, 14.0f),
        FX_PROP_5(1.0f, 0.8f, 0.0f, 1.0f),
        FX_PROP_10(temp_s0->unk0.m[3][0], temp_s0->unk0.m[3][1], temp_s0->unk0.m[3][2]),
        FX_PROP_4(1.0f, 1.0f, 1.0f),
        FX_PROP_END
    );
    // clang-format on
    D_8034F384 = 0;
    return 1;
}

void func_802F7178(GyrocopterData* gcData, Mtx4F* mat) {
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv1;

    uvMat4Copy(mat, &gcData->camera->unk108);
    uvMat4RotateAxis(mat, -0.10471974f, 'x');
    temp_fv0 = gcData->unk10.m[3][0] - gcData->camera->unk108.m[3][0];
    temp_fv1 = gcData->unk10.m[3][1] - gcData->camera->unk108.m[3][1];
    temp_fa1 = gcData->unk10.m[3][2] - gcData->camera->unk108.m[3][2];
    uvMat4LocalTranslate(mat, 0.0f, 2.0f * uvSqrtF(SQ(temp_fv0) + SQ(temp_fv1) + SQ(temp_fa1)), 0.0f);
}

void func_802F7224(GyrocopterData* gcData) {
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

    env_802E1754(gcData->unk10.m[3][0], gcData->unk10.m[3][1], gcData->unk10.m[3][2], &spD4);

    for (i = 0; i < ARRAY_COUNT(gcData->unk690); i++) {
        var_s0 = &gcData->unk690[i];
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
                        // clang-format off
                        uvFxProps(
                            var_s0->unk4E,
                            FX_PROP_3(2.0f, 2.0f, 2.0f),
                            FX_PROP_4(0.0f, 0.0f, 0.0f),
                            FX_PROP_END
                        );
                        // clang-format on
                    }
                }
                if ((var_s0->unk44 + 5.0f) < D_8034F850) {
                    var_s0->unk48 = 3;
                    if (var_s0->unk4E != 0xFF) {
                        uvModelGet(var_s0->unk4E, 0xFF);
                        var_s0->unk4E = 0xFF;
                    }
                } else {
                    temp_v0_2 = func_802F9D28(gcData->objId, gcData->unk2, var_s0->unk0.m[3][0], var_s0->unk0.m[3][1], var_s0->unk0.m[3][2], temp_fs0, temp_fs1,
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

void func_802F764C(GyrocopterData* gcData) {
    Vec3F sp74;
    Vec3F sp68;
    Vec3F sp5C;
    Vec3F* var_a1;
    f32 sp54;
    s32 sp50;
    s32 sp4C;
    u8 sp4B;

    camera_802D5884(gcData->camera, 3);
    hudGetState()->renderFlags = 0;
    if (gcData->unkD0 != 0) {
        gcData->camera->unk6 = 0;
        gcData->unk2 = gcData->camera->unk6;
        uvDobjState(gcData->objId, gcData->unk2);
        gcData->camera->unk190 = 12.0f;
    } else {
        gcData->camera->unk190 = 6.0f;
    }
    if ((gcData->unkD0 == 0) && (gcData->unk662 == 0)) {
        sp74.x = gcData->unk10.m[3][0];
        sp68.x = gcData->unk668.x;
        sp74.y = gcData->unk10.m[3][1];
        sp68.y = gcData->unk668.y;
        sp74.z = gcData->unk10.m[3][2];
        sp68.z = gcData->unk668.z;
        sp4C = gcData->unk674;
        sp4B = db_getgnd(&sp68, &sp74, &sp4C, &sp50, &sp54, &sp5C);
        if (sp4B) {
            var_a1 = func_802E02EC();
        } else {
            var_a1 = &sp74;
            sp74.z = sp54;
        }
        func_802E05CC(&gcData->unk10, var_a1, &sp5C, 2);
        uvDobjPosm(gcData->objId, 0, &gcData->unk10);
        uvMat4Copy(&gcData->camera->unk80, &gcData->unk10);
        if (func_802E0C30(sp4B, sp50) != 0) {
            gcData->unkD0 = 1;
            if (gcData->unk96 != 0xFF) {
                smokeProps(gcData->unk96, SMOKE_PROP_8(0), SMOKE_PROP_END);
            }
        } else {
            if (gcData->unk96 != 0xFF) {
                smokeProps(gcData->unk96, SMOKE_PROP_6(gcData->unk10.m[3][0], gcData->unk10.m[3][1], gcData->unk10.m[3][2]), SMOKE_PROP_END);
            }
            uvDobjModel(gcData->objId, gcData->crashModelId);
            uvDobjPosm(gcData->objId, 0, &gcData->unk10);
        }
    }
    shadow_803343D8(0);
    func_802F5910(gcData);
}

void gyrocopterLoadPilot(u8 pilot, GyrocopterData* gcData) {
    switch (pilot) {
    case PILOT_LARK:
        gcData->modelId = MODEL_GYRO_LARK;
        gcData->crashModelId = MODEL_GYRO_LARK_CRASHED;
        gcData->unk570 = 3;
        gcData->unk573 = 1;
        gcData->unk574 = 2;
        gcData->unk571 = 4;
        gcData->unk572 = 5;
        gcData->unk594 = 3.866f;
        gcData->unk598 = 0.0959931f;
        gcData->unk5A8 = 1.038f;
        gcData->unk5AC = 1.5707961f;
        gcData->unk590 = 0x37;
        gcData->unk591 = 0x39;
        gcData->unk592 = 0x38;
        gcData->unk640 = 110.0f;
        gcData->unk644 = 0.3490659f;
        gcData->unk648 = 0.25f;
        gcData->unk64C = 0.25f;
        gcData->unk650 = 0.125f;
        gcData->unk654 = 0.25f;
        gcData->unk658 = 0.25f;
        gcData->unk65C = 0.0625f;
        gcData->unk59C.x = -0.03f;
        gcData->unk59C.y = -0.095f;
        gcData->unk59C.z = 1.6f;
        gcData->unk5B0 = 0.009f;
        gcData->unk5B4 = -0.67f;
        gcData->unk5B8 = 0.44f;
        gcData->unk5BC.x = 0.001f;
        gcData->unk5BC.y = 1.362f;
        gcData->unk5BC.z = -0.003f;
        gcData->unk5C8.x = 0.006f;
        gcData->unk5C8.y = -1.334f;
        gcData->unk5C8.z = 0.141f;
        gcData->unk5D4 = -0.839f;
        gcData->unk5D8 = 0.0f;
        gcData->unk5DC = -0.234f;
        gcData->unk5E0 = 0.853f;
        gcData->unk5E4 = 0.0f;
        gcData->unk5E8 = -0.234f;
        gcData->unk5EC[0].x = 0.005f;
        gcData->unk5EC[0].y = 1.261f;
        gcData->unk5EC[0].z = -0.299f;
        gcData->unk5EC[3].x = 0.007f;
        gcData->unk5EC[3].y = -1.123f;
        gcData->unk5EC[3].z = -0.278f;
        gcData->unk5EC[1].x = -0.762f;
        gcData->unk5EC[1].y = -0.026f;
        gcData->unk5EC[1].z = -0.375f;
        gcData->unk5EC[2].x = 0.776f;
        gcData->unk5EC[2].y = -0.026f;
        gcData->unk5EC[2].z = -0.375f;
        gcData->unk61C = 0.0f;
        gcData->unk620 = -0.034f;
        gcData->unk624 = -0.099f;
        gcData->unk628 = 0.00f;
        gcData->unk62C = -4.45f;
        gcData->unk630 = 1.2f;
        gcData->unk634 = 0.0050f;
        gcData->unk638 = 0.455f;
        gcData->unk63C = 0.648f;
        gcData->unk538.x = 0.006f;
        gcData->unk538.y = 0.296f;
        gcData->unk538.z = 0.0f;
        gcData->unk578 = 0.522f, gcData->unk57C = 0.208f, gcData->unk580 = 0.208f;
        gcData->unk584 = 0.522f, gcData->unk588 = 0.208f, gcData->unk58C = 0.208f;
        break;
    case PILOT_GOOSE:
        gcData->modelId = MODEL_GYRO_GOOSE;
        gcData->crashModelId = MODEL_GYRO_GOOSE_CRASHED;
        gcData->unk570 = 3;
        gcData->unk573 = 1;
        gcData->unk574 = 2;
        gcData->unk571 = 4;
        gcData->unk572 = 5;
        gcData->unk594 = 3.866f;
        gcData->unk598 = 0.0959931f;
        gcData->unk5A8 = 1.038f;
        gcData->unk5AC = 1.5707961f;
        gcData->unk590 = 0x3A;
        gcData->unk591 = 0x3B;
        gcData->unk592 = 0x38;
        gcData->unk640 = 93.5f;
        gcData->unk644 = 0.4014257f;
        gcData->unk648 = 0.2f;
        gcData->unk64C = 0.2f;
        gcData->unk650 = 0.1f;
        gcData->unk654 = 0.2f;
        gcData->unk658 = 0.2f;
        gcData->unk65C = 0.05f;
        gcData->unk59C.x = -0.031f;
        gcData->unk59C.y = -0.021f;
        gcData->unk59C.z = 1.707f;
        gcData->unk5B0 = 0.005f;
        gcData->unk5B4 = -0.906f;
        gcData->unk5B8 = 0.459f;
        gcData->unk5BC.x = -0.001f;
        gcData->unk5BC.y = 1.96f;
        gcData->unk5BC.z = -0.039f;
        gcData->unk5C8.x = 0.005f;
        gcData->unk5C8.y = -1.868f;
        gcData->unk5C8.z = 0.142f;
        gcData->unk5D4 = -0.967f;
        gcData->unk5D8 = -0.146f;
        gcData->unk5DC = -0.251f;
        gcData->unk5E0 = 0.949f;
        gcData->unk5E4 = -0.146f;
        gcData->unk5E8 = -0.251f;
        gcData->unk5EC[0].x = 0.003f;
        gcData->unk5EC[0].y = 1.758f;
        gcData->unk5EC[0].z = -0.323f;
        gcData->unk5EC[3].x = 0.006f;
        gcData->unk5EC[3].y = -1.408f;
        gcData->unk5EC[3].z = -0.301f;
        gcData->unk5EC[1].x = -0.804f;
        gcData->unk5EC[1].y = -0.193f;
        gcData->unk5EC[1].z = -0.436f;
        gcData->unk5EC[2].x = 0.786f;
        gcData->unk5EC[2].y = -0.193f;
        gcData->unk5EC[2].z = -0.436f;
        gcData->unk61C = 0.0f;
        gcData->unk620 = -0.172f;
        gcData->unk624 = -0.121f;
        gcData->unk628 = 0.00f;
        gcData->unk62C = -4.45f;
        gcData->unk630 = 1.2f;
        gcData->unk634 = 0.002f;
        gcData->unk638 = 0.397f;
        gcData->unk63C = 0.678f;
        gcData->unk538.x = -0.006f;
        gcData->unk538.y = 0.295f;
        gcData->unk538.z = 0.0f;
        gcData->unk578 = 0.522f, gcData->unk57C = 0.208f, gcData->unk580 = 0.208f;
        gcData->unk584 = 0.522f, gcData->unk588 = 0.208f, gcData->unk58C = 0.208f;
        break;
    case PILOT_HAWK:
        gcData->modelId = MODEL_GYRO_HAWK;
        gcData->crashModelId = MODEL_GYRO_HAWK_CRASHED;
        gcData->unk570 = 3;
        gcData->unk573 = 1;
        gcData->unk574 = 2;
        gcData->unk571 = 4;
        gcData->unk572 = 5;
        gcData->unk594 = 3.866f;
        gcData->unk598 = 0.0959931f;
        gcData->unk5A8 = 1.038f;
        gcData->unk5AC = 1.5707961f;
        gcData->unk590 = 0x3C;
        gcData->unk591 = 0x3D;
        gcData->unk592 = 0x38;
        gcData->unk640 = 126.5f;
        gcData->unk644 = 0.296706f;
        gcData->unk648 = 0.325f;
        gcData->unk64C = 0.325f;
        gcData->unk650 = 0.1625f;
        gcData->unk654 = 0.325f;
        gcData->unk658 = 0.325f;
        gcData->unk65C = 0.08125f;
        gcData->unk59C.x = -0.02f;
        gcData->unk59C.y = -0.146f;
        gcData->unk59C.z = 1.65f;
        gcData->unk5B0 = 0.011f;
        gcData->unk5B4 = -0.733f;
        gcData->unk5B8 = 0.438f;
        gcData->unk5BC.x = 0.0f;
        gcData->unk5BC.y = 1.214f;
        gcData->unk5BC.z = -0.179f;
        gcData->unk5C8.x = 0.011f;
        gcData->unk5C8.y = -1.585f;
        gcData->unk5C8.z = 0.474f;
        gcData->unk5D4 = -1.025f;
        gcData->unk5D8 = -0.039f;
        gcData->unk5DC = -0.267f;
        gcData->unk5E0 = 1.021f;
        gcData->unk5E4 = -0.039f;
        gcData->unk5E8 = -0.267f;
        gcData->unk5EC[0].x = 0.009f;
        gcData->unk5EC[0].y = 1.243f;
        gcData->unk5EC[0].z = -0.429f;
        gcData->unk5EC[3].x = 0.012f;
        gcData->unk5EC[3].y = -1.237f;
        gcData->unk5EC[3].z = -0.317f;
        gcData->unk5EC[1].x = -0.863f;
        gcData->unk5EC[1].y = -0.085f;
        gcData->unk5EC[1].z = -0.451f;
        gcData->unk5EC[2].x = 0.859f;
        gcData->unk5EC[2].y = -0.085f;
        gcData->unk5EC[2].z = -0.451f;
        gcData->unk61C = 0.0f;
        gcData->unk620 = -0.047f;
        gcData->unk624 = -0.104f;
        gcData->unk628 = 0.00f;
        gcData->unk62C = -4.45f;
        gcData->unk630 = 1.2f;
        gcData->unk634 = 0.0090f;
        gcData->unk638 = 0.374f;
        gcData->unk63C = 0.71f;
        gcData->unk538.x = 0.005f;
        gcData->unk538.y = 0.247f;
        gcData->unk538.z = 0.0f;
        gcData->unk578 = 0.47f, gcData->unk57C = 0.412f, gcData->unk580 = 0.188f;
        gcData->unk584 = 0.6f, gcData->unk588 = 0.6f, gcData->unk58C = 0.6f;
        break;
    case PILOT_KIWI:
        gcData->modelId = MODEL_GYRO_KIWI;
        gcData->crashModelId = MODEL_GYRO_KIWI_CRASHED;
        gcData->unk570 = 3;
        gcData->unk573 = 1;
        gcData->unk574 = 2;
        gcData->unk571 = 4;
        gcData->unk572 = 5;
        gcData->unk594 = 3.866f;
        gcData->unk598 = 0.0959931f;
        gcData->unk5A8 = 1.038f;
        gcData->unk5AC = 1.5707961f;
        gcData->unk590 = 0x37;
        gcData->unk591 = 0x39;
        gcData->unk592 = 0x38;
        gcData->unk640 = 110.0f;
        gcData->unk644 = 0.3490659f;
        gcData->unk648 = 0.25f;
        gcData->unk64C = 0.25f;
        gcData->unk650 = 0.125f;
        gcData->unk654 = 0.25f;
        gcData->unk658 = 0.25f;
        gcData->unk65C = 0.0625f;
        gcData->unk59C.x = -0.031f;
        gcData->unk59C.y = -0.096f;
        gcData->unk59C.z = 1.62f;
        gcData->unk5B0 = 0.0090f;
        gcData->unk5B4 = -0.673f;
        gcData->unk5B8 = 0.443f;
        gcData->unk5BC.x = 0.002f;
        gcData->unk5BC.y = 1.37f;
        gcData->unk5BC.z = -0.003f;
        gcData->unk5C8.x = 0.007f;
        gcData->unk5C8.y = -1.341f;
        gcData->unk5C8.z = 0.142f;
        gcData->unk5D4 = -0.843f;
        gcData->unk5D8 = 0.179f;
        gcData->unk5DC = -0.235f;
        gcData->unk5E0 = 0.858f;
        gcData->unk5E4 = 0.179f;
        gcData->unk5E8 = -0.235f;
        gcData->unk5EC[0].x = 0.005f;
        gcData->unk5EC[0].y = 1.268f;
        gcData->unk5EC[0].z = -0.3f;
        gcData->unk5EC[3].x = 0.008f;
        gcData->unk5EC[3].y = -1.129f;
        gcData->unk5EC[3].z = -0.28f;
        gcData->unk5EC[1].x = -0.765f;
        gcData->unk5EC[1].y = -0.027f;
        gcData->unk5EC[1].z = -0.377f;
        gcData->unk5EC[2].x = 0.78f;
        gcData->unk5EC[2].y = -0.027f;
        gcData->unk5EC[2].z = -0.377f;
        gcData->unk61C = 0.0f;
        gcData->unk620 = -0.034f;
        gcData->unk624 = -0.101f;
        gcData->unk628 = 0.00f;
        gcData->unk62C = -4.45f;
        gcData->unk630 = 1.2f;
        gcData->unk634 = 0.00f;
        gcData->unk638 = 0.385f;
        gcData->unk63C = 0.568f;
        gcData->unk538.x = 0.006f;
        gcData->unk538.y = 0.297f;
        gcData->unk538.z = 0.0f;
        gcData->unk578 = 0.6f, gcData->unk57C = 0.6f, gcData->unk580 = 0.6f;
        gcData->unk584 = 0.6f, gcData->unk588 = 0.6f, gcData->unk58C = 0.6f;
        break;
    case PILOT_IBIS:
        gcData->modelId = MODEL_GYRO_IBIS;
        gcData->crashModelId = MODEL_GYRO_IBIS_CRASHED;
        gcData->unk570 = 3;
        gcData->unk573 = 1;
        gcData->unk574 = 2;
        gcData->unk571 = 4;
        gcData->unk572 = 5;
        gcData->unk594 = 3.866f;
        gcData->unk598 = 0.0959931f;
        gcData->unk5A8 = 1.038f;
        gcData->unk5AC = 1.5707961f;
        gcData->unk590 = 0x3A;
        gcData->unk591 = 0x3B;
        gcData->unk592 = 0x38;
        gcData->unk640 = 93.5f;
        gcData->unk644 = 0.4014257f;
        gcData->unk648 = 0.2f;
        gcData->unk64C = 0.2f;
        gcData->unk650 = 0.1f;
        gcData->unk654 = 0.2f;
        gcData->unk658 = 0.2f;
        gcData->unk65C = 0.05f;
        gcData->unk59C.x = -0.031f;
        gcData->unk59C.y = -0.021f;
        gcData->unk59C.z = 1.707f;
        gcData->unk5B0 = 0.028f;
        gcData->unk5B4 = -0.892f;
        gcData->unk5B8 = 0.452f;
        gcData->unk5BC.x = -0.001f;
        gcData->unk5BC.y = 1.966f;
        gcData->unk5BC.z = -0.038f;
        gcData->unk5C8.x = 0.005f;
        gcData->unk5C8.y = -1.872f;
        gcData->unk5C8.z = 0.142f;
        gcData->unk5D4 = -0.969f;
        gcData->unk5D8 = -0.146f;
        gcData->unk5DC = -0.252f;
        gcData->unk5E0 = 0.951f;
        gcData->unk5E4 = -0.146f;
        gcData->unk5E8 = -0.252f;
        gcData->unk5EC[0].x = 0.003f;
        gcData->unk5EC[0].y = 1.762f;
        gcData->unk5EC[0].z = -0.323f;
        gcData->unk5EC[3].x = 0.006f;
        gcData->unk5EC[3].y = -1.412f;
        gcData->unk5EC[3].z = -0.302f;
        gcData->unk5EC[1].x = -0.806f;
        gcData->unk5EC[1].y = -0.193f;
        gcData->unk5EC[1].z = -0.437f;
        gcData->unk5EC[2].x = 0.788f;
        gcData->unk5EC[2].y = -0.193f;
        gcData->unk5EC[2].z = -0.437f;
        gcData->unk61C = 0.0f;
        gcData->unk620 = -0.172f;
        gcData->unk624 = -0.118f;
        gcData->unk628 = 0.00f;
        gcData->unk62C = -4.45f;
        gcData->unk630 = 1.2f;
        gcData->unk634 = 0.001f;
        gcData->unk638 = 0.381f;
        gcData->unk63C = 0.623f;
        gcData->unk538.x = -0.003f;
        gcData->unk538.y = 0.296f;
        gcData->unk538.z = 0.0f;
        gcData->unk578 = 0.102f, gcData->unk57C = 0.086f, gcData->unk580 = 0.22f;
        gcData->unk584 = 0.6f, gcData->unk588 = 0.6f, gcData->unk58C = 0.6f;
        break;
    case PILOT_ROBIN:
        gcData->modelId = MODEL_GYRO_ROBIN;
        gcData->crashModelId = MODEL_GYRO_ROBIN_CRASHED;
        gcData->unk570 = 3;
        gcData->unk573 = 1;
        gcData->unk574 = 2;
        gcData->unk571 = 4;
        gcData->unk572 = 5;
        gcData->unk594 = 3.866f;
        gcData->unk598 = 0.0959931f;
        gcData->unk5A8 = 1.038f;
        gcData->unk5AC = 1.5707961f;
        gcData->unk590 = 0x3C;
        gcData->unk591 = 0x3D;
        gcData->unk592 = 0x38;
        gcData->unk640 = 126.5f;
        gcData->unk644 = 0.296706f;
        gcData->unk648 = 0.325f;
        gcData->unk64C = 0.325f;
        gcData->unk650 = 0.1625f;
        gcData->unk654 = 0.325f;
        gcData->unk658 = 0.325f;
        gcData->unk65C = 0.08125f;
        gcData->unk59C.x = -0.031f;
        gcData->unk59C.y = -0.146f;
        gcData->unk59C.z = 1.676f;
        gcData->unk5B0 = 0.011f;
        gcData->unk5B4 = -0.74f;
        gcData->unk5B8 = 0.442f;
        gcData->unk5BC.x = 0.0f;
        gcData->unk5BC.y = 1.227f;
        gcData->unk5BC.z = -0.18f;
        gcData->unk5C8.x = 0.011f;
        gcData->unk5C8.y = -1.601f;
        gcData->unk5C8.z = 0.478f;
        gcData->unk5D4 = -1.03f;
        gcData->unk5D8 = -0.039f;
        gcData->unk5DC = -0.27f;
        gcData->unk5E0 = 1.032f;
        gcData->unk5E4 = -0.039f;
        gcData->unk5E8 = -0.27f;
        gcData->unk5EC[0].x = 0.0090f;
        gcData->unk5EC[0].y = 1.255f;
        gcData->unk5EC[0].z = -0.433f;
        gcData->unk5EC[3].x = 0.012f;
        gcData->unk5EC[3].y = -1.25f;
        gcData->unk5EC[3].z = -0.32f;
        gcData->unk5EC[1].x = -0.867f;
        gcData->unk5EC[1].y = -0.086f;
        gcData->unk5EC[1].z = -0.455f;
        gcData->unk5EC[2].x = 0.868f;
        gcData->unk5EC[2].y = -0.086f;
        gcData->unk5EC[2].z = -0.455f;
        gcData->unk61C = 0.0f;
        gcData->unk620 = -0.05f;
        gcData->unk624 = -0.077f;
        gcData->unk628 = 0.00f;
        gcData->unk62C = -4.45f;
        gcData->unk630 = 1.2f;
        gcData->unk634 = 0.013f;
        gcData->unk638 = 0.384f;
        gcData->unk63C = 0.62f;
        gcData->unk538.x = 0.006f;
        gcData->unk538.y = 0.249f;
        gcData->unk538.z = 0.0f;
        gcData->unk578 = 0.102f, gcData->unk57C = 0.086f, gcData->unk580 = 0.22f;
        gcData->unk584 = 0.6f, gcData->unk588 = 0.6f, gcData->unk58C = 0.6f;
        break;
    default:
        break;
    }
}
