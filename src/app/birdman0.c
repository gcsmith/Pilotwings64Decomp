#include "common.h"
#include <uv_dobj.h>
#include <uv_event.h>
#include <uv_memory.h>
#include <uv_model.h>
#include "birdman.h"
#include "bmsound.h"
#include "camera.h"
#include "code_66F70.h"
#include "game.h"
#include "code_7FE00.h"
#include "code_9A960.h"
#include "demo.h"
#include "fdr.h"
#include "hud.h"
#include "shadow.h"
#include "snap.h"
#include "snd.h"
#include "task.h"

Unk803599D0 D_80359390;
u8 D_803593E4;

// forward declarations
void birdLoadPilot(u8, BirdmanData* bmData);
void bird_802CE0A4(BirdmanData* bmData);

// called during game boot
void birdInit(void) {
    D_80359390.count = 8;
    D_80359390.unk4[0].x = 0.0f, D_80359390.unk4[0].y = 0.0f;
    D_80359390.unk4[1].x = 0.2f, D_80359390.unk4[1].y = 0.04f;
    D_80359390.unk4[2].x = 0.4f, D_80359390.unk4[2].y = 0.16f;
    D_80359390.unk4[3].x = 0.6f, D_80359390.unk4[3].y = 0.36f;
    D_80359390.unk4[4].x = 0.7f, D_80359390.unk4[4].y = 0.49f;
    D_80359390.unk4[5].x = 0.8f, D_80359390.unk4[5].y = 0.64f;
    D_80359390.unk4[6].x = 0.9f, D_80359390.unk4[6].y = 0.81f;
    D_80359390.unk4[7].x = 1.0f, D_80359390.unk4[7].y = 1.0f;
}

// called when starting one of the birdman levels, either from bonus menu or bonus star
void birdLoadLevel(u8 contIdx, u8 pilot, BirdmanData* bmData, Camera* camera) {
    uvMemSet(bmData, 0, sizeof(BirdmanData));
    birdLoadPilot(pilot, bmData);
    bmData->objId = uvDobjAllocIdx();
    bmData->unk2 = 2;
    uvDobjModel(bmData->objId, bmData->unk3F4);
    uvDobjPosm(bmData->objId, 0, &bmData->unk10);
    uvDobjState(bmData->objId, bmData->unk2);
    uvMat4Copy(&bmData->unk50, &bmData->unk10);
    shadow_80334454(MODEL_BIRDMAN_SHADOW_COLUMN, MODEL_BIRDMAN_SHADOW);
    shadow_803342F0(1.0f);
    shadow_803342FC(-2.0f);
    shadow_803343D8(1);
    bmData->contIdx = contIdx;
    bmData->unk2F0 = 0;
    bmData->unk2CC = 0x1A;
    bmData->unk4 = 0;
    bmData->camera = camera;
    bmData->unk2BC = 0.0f;
    bmData->unk2C4 = 0.0f;
    bmData->unk2D0 = 0.0f;
    bmData->unk2D4 = 0.0f;
    bmData->unk2D8 = 0.0f;
    bmData->unk2DC = 0.0f;
    uvModelGetProps(bmData->unk3F4, MODEL_PROP_UNK1(&camera->unk8), MODEL_PROP_END);
    bird_802CEBA0(bmData);
    bmSoundInit(bmData);
}

// called when entering or exiting a birdman level
void birdEnterLeave(BirdmanData* bmData) {
    db_getstart(&bmData->unk10, &bmData->unk200, NULL, NULL);
    uvDobjPosm(bmData->objId, 0, &bmData->unk10);
    uvMat4Copy(&bmData->unk50, &bmData->unk10);
    bird_802CECB8(bmData);
    bmData->unk104 = 0;
    bmData->unk105 = 0;
    bmData->unk2 = 2;
    bmData->unk290 = 1;
    bmData->unkEC = 0.0f;
    bmData->unkF0 = 0.0f;
    bmData->unk8 = 0.0f;
    bmData->unk2FC = 0.0f;
    bmData->unk300 = 0.0f;
    bmData->unk304 = 0.0f;
    bmData->unk308 = 0.0f;
    bmData->unk2E8 = 0.0f;
    bmData->unk2E0 = 0.0f;
    bmData->unk2EC = 0.0f;
    bmData->unk2E4 = 0.0f;
    bird_802CE0A4(bmData);
    bmData->unkD8 = 0;
    bmData->unkDC = 1.0f;
    bmData->camera->unk1 = bmData->unkD8;
    bmData->camera->unk4 = bmData->objId;
    bmData->camera->unk6 = bmData->unk2;
    bmData->camera->unk0 = 1;
    bmData->camera->unk74 = 0.0f;
    bmData->camera->unk5C = 0;
    bmData->camera->unk60 = -3.5f;
    bmData->camera->unk64 = 0.5f;
    bmData->camera->unk54 = 3.0f;
    bmData->camera->unk58 = 6.5f;
    bmData->camera->unk48 = 0.0125f;
    bmData->camera->unk4C = 1.0f;
    bmData->camera->unk50 = 0.0f;
    bmData->camera->unk228 = 0.0f;
    D_803593E4 = 0;
    func_802D45C4(bmData->camera, bmData->unkDC);
}

// called when exiting a birdman level
void bird_802CC51C(Unk802CC51C* bmData) {
    uvDobjModel(bmData->objId, MODEL_WORLD);
    bmData->unkC = 0xFFFF;
    bmData->objId = 0xFFFF;
    shadow_80334C70();
}

// called every frame in a birdman stage
// handles controller input and motion updates
void birdMovementFrame(BirdmanData* bmData, u8 gameState) {
    f32 sp7C;
    f32 sp78;
    f32 pad;
    s32 buttons;
    HUDState* hud;
    s32 sp68;
    f32 temp_fv0;
    f32 sp4C[6];
    f32 var_fa0;
    s32 pad2;
    f32 var_fv0;
    f32 var_fv1;

    sp68 = 0;
    if (bmData->unk104 == 2) {
        bird_802CD0F8(bmData);
        return;
    }
    if (fdr_802E6B5C() != 4) {
        bmData->unk8 += D_8034F854;
        if (D_80362690->unkC[D_80362690->unk9C].unk7B == 0) {
            func_80339E1C(bmData);
        }
        if (gameState == GAME_STATE_RESULTS) {
            fdr_802E65AC(&bmData->unk10, &D_80362690->terraId, &sp7C, &sp78, &buttons);
        } else {
            sp7C = demoGetInputs(bmData->contIdx, INPUT_AXIS_X);
            sp78 = demoGetInputs(bmData->contIdx, INPUT_AXIS_Y);
            buttons = demoGetButtons(bmData->contIdx);
            if (sp7C > 0.0f) {
                var_fv0 = sp7C;
            } else {
                var_fv0 = -sp7C;
            }
            temp_fv0 = func_80313F08(&D_80359390, var_fv0);
            if (sp7C >= 0.0f) {
                sp7C = temp_fv0;
            } else {
                sp7C = -temp_fv0;
            }
            if (sp78 > 0.0f) {
                var_fv0 = sp78;
            } else {
                var_fv0 = -sp78;
            }
            temp_fv0 = func_80313F08(&D_80359390, var_fv0);
            if (sp78 >= 0.0f) {
                sp78 = temp_fv0;
            } else {
                sp78 = -temp_fv0;
            }
        }
        if (D_803593E4 != 0) {
            bmData->unkE4 = func_80313AF4(0.0f, bmData->unkE4, 3.0f);
            bmData->unkE8 = func_80313AF4(0.0f, bmData->unkE8, 3.0f);
        } else {
            bmData->unkE4 = func_80313AF4(sp7C, bmData->unkE4, 3.0f);
            bmData->unkE8 = func_80313AF4(sp78, bmData->unkE8, 3.0f);
        }
        if (demoButtonPress(bmData->contIdx, A_BUTTON)) {
            sp68 = 1;
            bmData->unk2DC -= 0.25f;
        }
        if (demoButtonPress(bmData->contIdx, B_BUTTON)) {
            sp68 = 1;
            bmData->unk2DC += 0.25f;
        }
        bmData->unk2DC = func_80313AF4(0.0f, bmData->unk2DC, 1.0f);
        bmData->unk2D4 += bmData->unk2DC * D_8034F854;
        if (bmData->unk2D4 < 0.f) {
            bmData->unk2D4 = 0.f;
        }
        if (bmData->unk2D4 > 1.5707f) {
            bmData->unk2D4 = 1.5707f;
        }
        if (sp68 != 0) {
            bmData->unk2D0 += 9.0f * D_8034F854;
            if (bmData->unk2D0 > 3.8f) {
                bmData->unk2D0 = 3.8f;
            }
        } else {
            bmData->unk2D0 = func_80313AF4(0.0f, bmData->unk2D0, 0.5f);
            bmData->unk2D4 = func_80313AF4(0.0f, bmData->unk2D4, 0.4f);
        }
        if (gameState != GAME_STATE_RESULTS) {
            bird_802CEDF8(bmData);
        }
        bird_802CE190(bmData, gameState);
        if (gameState != GAME_STATE_RESULTS) {
            sp4C[0] = bmData->unkD0;
            sp4C[1] = bmData->unk2D0;
            sp4C[2] = bmData->unk2D4;
            sp4C[3] = (f32)bmData->unk2C0;
            sp4C[4] = bmData->unk304;
            sp4C[5] = bmData->unk308;
            fdr_802E682C(sp4C, ARRAY_COUNT(sp4C), 0);
        } else {
            fdr_802E6870(sp4C, ARRAY_COUNT(sp4C), NULL);
            bmData->unkD0 = sp4C[0];
            bmData->unk2D0 = sp4C[1];
            bmData->unk2D4 = sp4C[2];
            bmData->unk2C0 = (u8)sp4C[3];
            bmData->unk304 = sp4C[4];
            bmData->unk308 = sp4C[5];
        }
        if (gameState != GAME_STATE_RESULTS) {
            bmData->unkD0 = -1.57f;
            if (bmData->unk224 < 25.0f) {
                var_fa0 = (((25.0f - bmData->unk224) * 1.57f) / 25.0f) + -1.57f;
                if ((bmData->unk16C < 4.0f) && (bmData->unk224 < 10.0f)) {
                    bmData->unkD0 = (((4.0f - bmData->unk16C) * 1.57f) / 2.5f) + -1.57f;
                }
                if (var_fa0 < bmData->unkD0) {
                    bmData->unkD0 = bmData->unkD0;
                } else {
                    bmData->unkD0 = var_fa0;
                }
            }
            if (bmData->unkD0 > 0.0f) {
                bmData->unkD0 = 0.0f;
            }
        }
        uvMat4SetIdentity(&bmData->unk90);
        uvMat4RotateAxis(&bmData->unk90, bmData->unkD0, 'x');
        uvMat4Mul(&bmData->unk50, &bmData->unk90, &bmData->unk10);
        uvDobjPosm(bmData->objId, 0, &bmData->unk50);
        shadow_803344BC(&bmData->unk10, bmData->unk16C);
        if (bmData->unk224 > 25.0f) {
            bmData->camera->unk48 = 0.0125f;
            bmData->camera->unk5C = 0.0f;
            bmData->camera->unk60 = -3.5f;
            bmData->camera->unk64 = 0.5f;
        } else {
            var_fa0 = -bmData->unkD0 / 1.57f;
            var_fv1 = bmData->unk224 / 25.0f;
            if (var_fa0 < 0.0f) {
                var_fa0 = 0.0f;
            } else if (var_fa0 > 1.0f) {
                var_fa0 = 1.0f;
            }
            if (var_fv1 < 0.0f) {
                var_fv1 = 0.0f;
            } else if (var_fv1 > 1.0f) {
                var_fv1 = 1.0f;
            }
            if (var_fv1 < var_fa0) {
                var_fv0 = var_fa0;
            } else {
                var_fv0 = var_fv1;
            }
            bmData->camera->unk48 = ((1.0f - var_fv0) * 0.15f) + (var_fv0 * 0.0125f);
            bmData->camera->unk5C = 0 * var_fv0;

            bmData->camera->unk60 = (2.5f * var_fv0) + -6.0f;
            bmData->camera->unk64 = (0.4f * var_fv0) + 0.1f;
        }
        if (D_803593E4 == 0) {
            if (buttons & L_CBUTTONS) {
                var_fa0 = 1.5707963f;
            } else if (buttons & R_CBUTTONS) {
                var_fa0 = -1.5707963f;
            } else {
                var_fa0 = 0.0f;
            }
            bmData->unkEC = func_80313AF4(var_fa0, bmData->unkEC, 1.1f);
            if (buttons & D_CBUTTONS) {
                var_fa0 = 1.5707963f;
            } else if (buttons & U_CBUTTONS) {
                var_fa0 = -1.5707963f;
            } else {
                var_fa0 = 0.0f;
            }
            bmData->unkF0 = func_80313AF4(var_fa0, bmData->unkF0, 1.1f);
        } else {
            bmData->unkEC = func_80313AF4(demoGetInputs(bmData->contIdx, 0) * -1.5707963f, bmData->unkEC, 3.0f);
            bmData->unkF0 = func_80313AF4(demoGetInputs(bmData->contIdx, 1) * -1.5707963f, bmData->unkF0, 3.0f);
        }
        if (demoButtonPress(bmData->contIdx, R_TRIG) && (gameState != GAME_STATE_RESULTS) && (bmData->unk104 != 1)) {
            D_803593E4 = 0;
            if (bmData->unkD8 == 1) {
                sndPlaySfxVolPitchPan(0x6A, 1.0f, 0.5f, 0.0f);
                bmData->unkD8 = 0;
                bmData->unkDC = 1.0f;
                shadow_80334454(MODEL_BIRDMAN_SHADOW_COLUMN, MODEL_BIRDMAN_SHADOW);
                bmData->unk290 = 1;
                bird_802CE0A4(bmData);
            } else {
                sndPlaySfxVolPitchPan(0x6A, 1.0f, 0.5f, 0.0f);
                bmData->unkD8 = 1;
                bmData->unkDC = 0.8f;
                shadow_80334454(MODEL_BIRDMAN_SHADOW_COLUMN, MODEL_BIRDMAN_SHADOW);
                bmData->unk290 = 0;
                bird_802CE0A4(bmData);
            }
            func_802D5884(bmData->camera, bmData->unkD8);
            func_802D45C4(bmData->camera, bmData->unkDC);
        }
        if (gameState != GAME_STATE_RESULTS) {
            bmData->camera->unk4 = bmData->objId;
            bmData->camera->unk6 = bmData->unk2;
            bmData->camera->unk78 = bmData->unkEC;
            bmData->camera->unk7C = bmData->unkF0;
            bmData->camera->unk228 = bmData->unk16C;
            uvMat4LocalToWorld(&bmData->unk90, &bmData->camera->unk68, &bmData->unk294);
            uvMat4Copy(&bmData->camera->unk80, &bmData->unk10);
            if (bmData->unk104 == 1) {
                func_802D5884(bmData->camera, 6);
                bmData->unk2 = 2;
                uvDobjState(bmData->objId, bmData->unk2);
            } else {
                func_802D5884(bmData->camera, bmData->unkD8);
            }
            func_802D45C4(bmData->camera, bmData->unkDC);
        }
        if ((bmData->unkD8 == 1) && (bmData->unk104 != 1) && (gameState != GAME_STATE_RESULTS)) {
            bmData->unk290 = 0;
        } else {
            bmData->unk290 = 1;
        }
        if (bmData->camera->unk148 != 0) {
            bmData->unk290 = 1;
        }
        bird_802CE0A4(bmData);
        if (gameState != GAME_STATE_RESULTS) {
            hud = hudGetState();
            uvMat4Copy(&hud->unk28, &bmData->unk10);
            hud->renderFlags = HUD_RENDER_BIRDMAN;
            hud->att.heading = bmData->unk10.m[3][2];
            hud->elapsedTime = bmData->unk8;
            hud->unk8C = bmData->unk218.z * 4.0f * 0.7f;
            hud->altitude = bmData->unk16C * 0.7f;
            hud->altSeaLevel = bmData->unk10.m[3][2] * 0.7f;
            hud->speed = bmData->unk224 * 3.6f * 0.7f;
        }
        if ((bmData->unk104 == 1) || (bmData->unk104 == 2)) {
            hud->renderFlags = 0;
        }
        func_802E06AC(&bmData->unk10);
        if (gameState != GAME_STATE_RESULTS) {
            if (bmData->unk104 == 2) {
                fdr_802E66DC();
            }
            fdr_802E65AC(&bmData->unk10, &D_80362690->terraId, &sp7C, &sp78, &buttons);
        }
    }
}

void bird_802CD0F8(BirdmanData* bmData) {
    f32 x;
    f32 y;
    f32 z;
    Vec3F sp60;
    Vec3F sp54;
    Vec3F sp48;
    Vec3F* var_a1;
    f32 sp40;
    s32 sp3C;
    s32 sp38;
    u8 sp37;

    if (bmData->unk2F0 == 0) {
        bmData->unk2F0 = 1;
        sp60.x = bmData->unk10.m[3][0];
        sp54.x = bmData->unk400.x;
        sp60.y = bmData->unk10.m[3][1];
        sp54.y = bmData->unk400.y;
        sp60.z = bmData->unk10.m[3][2];
        sp54.z = bmData->unk400.z;
        sp38 = bmData->unk40C;
        sp37 = db_getgnd(&sp54, &sp60, &sp38, &sp3C, &sp40, &sp48);
        if (sp37 != 0) {
            var_a1 = func_802E02EC();
        } else {
            var_a1 = &sp60;
            sp60.z = sp40;
        }
        func_802E05CC(&bmData->unk10, var_a1, &sp48, 1);
        if (func_802E0C30(sp37, sp3C) != 0) {
            bmData->unk15C = 1;
        }
        uvDobjPosm(bmData->objId, 0, &bmData->unk10);
        uvMat4Copy(&bmData->camera->unk80, &bmData->unk10);
        if (bmData->unk15C != 0) {
            sndPlaySfx(SFX_WATER_SPLASH);
            uvEventPost(0x12, 0);
            x = bmData->unk10.m[3][0];
            y = bmData->unk10.m[3][1];
            z = bmData->unk10.m[3][2];
            func_802F8AB8(x, y, z, 1.0f, &bmData->unk218);
            bmData->camera->unk6 = bmData->unk2 = 0;
            uvDobjState(bmData->objId, bmData->unk2);
            uvMat4Copy(&bmData->camera->unk80, &bmData->unk10);
        } else {
            bmData->unk2 = 2;
            uvDobjState(bmData->objId, bmData->unk2);
        }
        bmData->unk290 = 1;
        bird_802CE0A4(bmData);
        shadow_803343D8(0);
    }
    func_802D5884(bmData->camera, 3);
    hudGetState()->renderFlags = 0;
    if (bmData->unk15C != 0) {
        bmData->camera->unk190 = 12.0f;
    } else {
        bmData->camera->unk190 = 6.0f;
    }
    bird_802CEA60(bmData);
}

// called during birdman init to setup pilot specific parameters
void birdLoadPilot(u8 pilot, BirdmanData* bmData) {
    switch (pilot) {
    case PILOT_LARK:
        bmData->unk294.x = 0;
        bmData->unk294.y = -0.1625f;
        bmData->unk294.z = 0.2869f;
        bmData->unk3F4 = MODEL_BIRDMAN_LARK;
        bmData->unk3F7 = 0x16;
        bmData->unk3F6 = 1;
        bmData->unk3F8 = 2;
        bmData->unk3F9 = 5;
        bmData->unk2F8 = 0xF;
        bmData->unk2F9 = 8;
        bmData->unk2A0 = 0.6f;
        bmData->unk2A4 = 1.0f;
        bmData->unk2B0 = 0.8f;
        bmData->unk2B4 = 0.8f;
        bmData->unk2B8 = 0x44;
        bmData->unk2C0 = 0x45;
        bmData->unk2AC = 1.2f;
        bmData->unk2A8 = 1.2f;
        bmData->unk320.x = 0.0f;
        bmData->unk320.y = 0.021f;
        bmData->unk320.z = 0.675f;
        bmData->unk32C.x = -4.281f;
        bmData->unk32C.y = -0.972f;
        bmData->unk32C.z = 0.596f;
        bmData->unk338.x = 4.277f;
        bmData->unk338.y = -0.972f;
        bmData->unk344.y = 0.0f;
        bmData->unk344.x = 0.0f;
        bmData->unk338.z = 0.596f;
        bmData->unk344.z = -0.745f;
        bmData->unk350.count = 7;
        bmData->unk350.unk4[0].x = 0.0f;
        bmData->unk350.unk4[0].y = -1.426f;
        bmData->unk350.unk4[0].z = -0.098f;
        bmData->unk350.unk4[0].w = -0.018f;
        bmData->unk350.unk4[1].x = 0.125f;
        bmData->unk350.unk4[1].y = -1.368f;
        bmData->unk350.unk4[1].z = -0.401f;
        bmData->unk350.unk4[1].w = -0.084f;
        bmData->unk350.unk4[2].x = 0.25f;
        bmData->unk350.unk4[2].y = -1.019f;
        bmData->unk350.unk4[2].z = -0.815f;
        bmData->unk350.unk4[2].w = -0.234f;
        bmData->unk350.unk4[3].x = 0.625f;
        bmData->unk350.unk4[3].y = -1.271f;
        bmData->unk350.unk4[3].z = -0.175f;
        bmData->unk350.unk4[3].w = -0.158f;
        bmData->unk350.unk4[4].x = 0.75f;
        bmData->unk350.unk4[4].y = -1.133f;
        bmData->unk350.unk4[4].z = 0.561f;
        bmData->unk350.unk4[4].w = -0.274f;
        bmData->unk350.unk4[5].x = 0.875f;
        bmData->unk350.unk4[5].y = -1.12f;
        bmData->unk350.unk4[5].z = 0.6f;
        bmData->unk350.unk4[5].w = -0.127f;
        bmData->unk350.unk4[6].x = 1.0f;
        bmData->unk350.unk4[6].y = -1.426f;
        bmData->unk350.unk4[6].z = -0.098f;
        bmData->unk350.unk4[6].w = -0.018f;
        break;
    case PILOT_GOOSE:
        bmData->unk294.x = 0;
        bmData->unk294.y = -0.0994f;
        bmData->unk294.z = 0.2577f;
        bmData->unk3F4 = MODEL_BIRDMAN_GOOSE;
        bmData->unk3F7 = 0x16;
        bmData->unk3F6 = 1;
        bmData->unk3F8 = 2;
        bmData->unk3F9 = 5;
        bmData->unk2F8 = 0xF;
        bmData->unk2F9 = 8;
        bmData->unk2A0 = 0.6f;
        bmData->unk2A4 = 1.0f;
        bmData->unk2AC = 1.0f;
        bmData->unk2A8 = 1.0f;
        bmData->unk2B0 = 1.0f;
        bmData->unk2B4 = 1.0f;
        bmData->unk2B8 = 0x46;
        bmData->unk2C0 = 0x47;
        bmData->unk320.x = 0.0f;
        bmData->unk320.y = 0.108f;
        bmData->unk320.z = 0.653f;
        bmData->unk32C.x = -3.724f;
        bmData->unk32C.y = -0.808f;
        bmData->unk32C.z = 0.499f;
        bmData->unk338.x = 3.714f;
        bmData->unk338.y = -0.808f;
        bmData->unk338.z = 0.499f;
        bmData->unk344.y = 0.0f;
        bmData->unk344.x = 0.0f;
        bmData->unk344.z = -1.645f;
        bmData->unk350.count = 7;
        bmData->unk350.unk4[0].x = 0.0f;
        bmData->unk350.unk4[0].y = -1.457f;
        bmData->unk350.unk4[0].z = -0.05f;
        bmData->unk350.unk4[0].w = 0.491f;
        bmData->unk350.unk4[1].x = 0.125f;
        bmData->unk350.unk4[1].y = -1.416f;
        bmData->unk350.unk4[1].z = -0.426f;
        bmData->unk350.unk4[1].w = 0.377f;
        bmData->unk350.unk4[2].x = 0.25f;
        bmData->unk350.unk4[2].y = -0.864f;
        bmData->unk350.unk4[2].z = -1.022f;
        bmData->unk350.unk4[2].w = 0.137f;
        bmData->unk350.unk4[3].x = 0.625f;
        bmData->unk350.unk4[3].y = -1.439f;
        bmData->unk350.unk4[3].z = -0.011f;
        bmData->unk350.unk4[3].w = 0.486f;
        bmData->unk350.unk4[4].x = 0.75f;
        bmData->unk350.unk4[4].y = -1.249f;
        bmData->unk350.unk4[4].z = 0.762f;
        bmData->unk350.unk4[4].w = 0.202f;
        bmData->unk350.unk4[5].x = 0.875f;
        bmData->unk350.unk4[5].y = -1.152f;
        bmData->unk350.unk4[5].z = 0.767f;
        bmData->unk350.unk4[5].w = 0.312f;
        bmData->unk350.unk4[6].x = 1.0f;
        bmData->unk350.unk4[6].y = -1.457f;
        bmData->unk350.unk4[6].z = -0.05f;
        bmData->unk350.unk4[6].w = 0.491f;
        break;
    case PILOT_HAWK:
        bmData->unk294.x = 0;
        bmData->unk294.y = -0.07084f;
        bmData->unk294.z = 0.57865f;
        bmData->unk3F4 = MODEL_BIRDMAN_HAWK;
        bmData->unk3F7 = 0x16;
        bmData->unk3F6 = 1;
        bmData->unk3F8 = 2;
        bmData->unk3F9 = 5;
        bmData->unk2F8 = 0xF;
        bmData->unk2F9 = 8;
        bmData->unk2A0 = 0.6f;
        bmData->unk2A4 = 1.0f;
        bmData->unk2B0 = 1.2f;
        bmData->unk2B4 = 1.2f;
        bmData->unk2B8 = 0x48;
        bmData->unk2C0 = 0x49;
        bmData->unk2AC = 0.8f;
        bmData->unk2A8 = 0.8f;
        bmData->unk320.x = 0.0f;
        bmData->unk320.y = 0.108f;
        bmData->unk320.z = 0.627f;
        bmData->unk32C.x = -3.643f;
        bmData->unk32C.y = -0.796f;
        bmData->unk32C.z = 0.476f;
        bmData->unk338.x = 3.643f;
        bmData->unk338.y = -0.796f;
        bmData->unk338.z = 0.476f;
        bmData->unk344.y = 0.0f;
        bmData->unk344.x = 0.0f;
        bmData->unk344.z = -1.228f;
        bmData->unk350.count = 7;
        bmData->unk350.unk4[0].x = 0.0f;
        bmData->unk350.unk4[0].y = -1.826f;
        bmData->unk350.unk4[0].z = -0.06f;
        bmData->unk350.unk4[0].w = 0.217f;
        bmData->unk350.unk4[1].x = 0.125f;
        bmData->unk350.unk4[1].y = -1.689f;
        bmData->unk350.unk4[1].z = -0.606f;
        bmData->unk350.unk4[1].w = 0.158f;
        bmData->unk350.unk4[2].x = 0.25f;
        bmData->unk350.unk4[2].y = -1.074f;
        bmData->unk350.unk4[2].z = -1.247f;
        bmData->unk350.unk4[2].w = -0.01f;
        bmData->unk350.unk4[3].x = 0.625f;
        bmData->unk350.unk4[3].y = -1.804f;
        bmData->unk350.unk4[3].z = -0.068f;
        bmData->unk350.unk4[3].w = 0.407f;
        bmData->unk350.unk4[4].x = 0.75f;
        bmData->unk350.unk4[4].y = -1.519f;
        bmData->unk350.unk4[4].z = 0.881f;
        bmData->unk350.unk4[4].w = 0.208f;
        bmData->unk350.unk4[5].x = 0.875f;
        bmData->unk350.unk4[5].y = -1.415f;
        bmData->unk350.unk4[5].z = 0.89f;
        bmData->unk350.unk4[5].w = 0.392f;
        bmData->unk350.unk4[6].y = -1.826f;
        bmData->unk350.unk4[6].z = -0.06f;
        bmData->unk350.unk4[6].x = 1.0f;
        bmData->unk350.unk4[6].w = 0.217f;
        break;
    case PILOT_KIWI:
        bmData->unk294.x = 0;
        bmData->unk294.y = 0.0015f;
        bmData->unk294.z = 0.1942f;
        bmData->unk3F4 = MODEL_BIRDMAN_KIWI;
        bmData->unk3F7 = 0x16;
        bmData->unk3F6 = 1;
        bmData->unk3F8 = 2;
        bmData->unk3F9 = 5;
        bmData->unk2F8 = 0xF;
        bmData->unk2F9 = 8;
        bmData->unk2A0 = 0.6f;
        bmData->unk2A4 = 1.0f;
        bmData->unk2B0 = 0.8f;
        bmData->unk2B4 = 0.8f;
        bmData->unk2B8 = 0x4A;
        bmData->unk2C0 = 0x45;
        bmData->unk2AC = 1.2f;
        bmData->unk2A8 = 1.2f;
        bmData->unk320.x = 0.0f;
        bmData->unk320.y = 0.021f;
        bmData->unk320.z = 0.672f;
        bmData->unk32C.x = -4.34f;
        bmData->unk32C.y = -1.029f;
        bmData->unk32C.z = 0.57f;
        bmData->unk338.x = 4.34f;
        bmData->unk338.y = -1.029f;
        bmData->unk344.y = 0.0f;
        bmData->unk344.x = 0.0f;
        bmData->unk338.z = 0.57f;
        bmData->unk344.z = -0.861f;
        bmData->unk350.count = 7;
        bmData->unk350.unk4[0].x = 0.0f;
        bmData->unk350.unk4[0].y = -1.426f;
        bmData->unk350.unk4[0].z = -0.098f;
        bmData->unk350.unk4[0].w = -0.018f;
        bmData->unk350.unk4[1].x = 0.125f;
        bmData->unk350.unk4[1].y = -1.368f;
        bmData->unk350.unk4[1].z = -0.401f;
        bmData->unk350.unk4[1].w = -0.084f;
        bmData->unk350.unk4[2].x = 0.25f;
        bmData->unk350.unk4[2].y = -1.019f;
        bmData->unk350.unk4[2].z = -0.815f;
        bmData->unk350.unk4[2].w = -0.234f;
        bmData->unk350.unk4[3].x = 0.625f;
        bmData->unk350.unk4[3].y = -1.271f;
        bmData->unk350.unk4[3].z = -0.175f;
        bmData->unk350.unk4[3].w = -0.158f;
        bmData->unk350.unk4[4].x = 0.75f;
        bmData->unk350.unk4[4].y = -1.133f;
        bmData->unk350.unk4[4].z = 0.561f;
        bmData->unk350.unk4[4].w = -0.274f;
        bmData->unk350.unk4[5].x = 0.875f;
        bmData->unk350.unk4[5].y = -1.12f;
        bmData->unk350.unk4[5].z = 0.6f;
        bmData->unk350.unk4[5].w = -0.127f;
        bmData->unk350.unk4[6].x = 1.0f;
        bmData->unk350.unk4[6].y = -1.426f;
        bmData->unk350.unk4[6].z = -0.098f;
        bmData->unk350.unk4[6].w = -0.018f;
        break;
    case PILOT_IBIS:
        bmData->unk294.x = 0;
        bmData->unk294.y = 0.0024f;
        bmData->unk294.z = 0.3577f;
        bmData->unk3F4 = MODEL_BIRDMAN_IBIS;
        bmData->unk3F7 = 0x16;
        bmData->unk3F6 = 1;
        bmData->unk3F8 = 2;
        bmData->unk3F9 = 5;
        bmData->unk2F8 = 0xF;
        bmData->unk2F9 = 8;
        bmData->unk2A0 = 0.6f;
        bmData->unk2A4 = 1.0f;
        bmData->unk2AC = 1.0f;
        bmData->unk2A8 = 1.0f;
        bmData->unk2B0 = 1.0f;
        bmData->unk2B4 = 1.0f;
        bmData->unk2B8 = 0x4B;
        bmData->unk2C0 = 0x47;
        bmData->unk320.x = 0.0f;
        bmData->unk320.y = 0.108f;
        bmData->unk320.z = 0.731f;
        bmData->unk32C.x = -4.225f;
        bmData->unk32C.y = -0.89f;
        bmData->unk32C.z = 0.715f;
        bmData->unk338.x = 4.226f;
        bmData->unk338.y = -0.89f;
        bmData->unk338.z = 0.666f;
        bmData->unk344.y = 0.0f;
        bmData->unk344.x = 0.0f;
        bmData->unk344.z = -1.427f;
        bmData->unk350.count = 7;
        bmData->unk350.unk4[0].x = 0.0f;
        bmData->unk350.unk4[0].y = -1.457f;
        bmData->unk350.unk4[0].z = -0.05f;
        bmData->unk350.unk4[0].w = 0.491f;
        bmData->unk350.unk4[1].x = 0.125f;
        bmData->unk350.unk4[1].y = -1.416f;
        bmData->unk350.unk4[1].z = -0.426f;
        bmData->unk350.unk4[1].w = 0.377f;
        bmData->unk350.unk4[2].x = 0.25f;
        bmData->unk350.unk4[2].y = -0.864f;
        bmData->unk350.unk4[2].z = -1.022f;
        bmData->unk350.unk4[2].w = 0.137f;
        bmData->unk350.unk4[3].x = 0.625f;
        bmData->unk350.unk4[3].y = -1.439f;
        bmData->unk350.unk4[3].z = -0.011f;
        bmData->unk350.unk4[3].w = 0.486f;
        bmData->unk350.unk4[4].x = 0.75f;
        bmData->unk350.unk4[4].y = -1.249f;
        bmData->unk350.unk4[4].z = 0.762f;
        bmData->unk350.unk4[4].w = 0.202f;
        bmData->unk350.unk4[5].x = 0.875f;
        bmData->unk350.unk4[5].y = -1.152f;
        bmData->unk350.unk4[5].z = 0.767f;
        bmData->unk350.unk4[5].w = 0.312f;
        bmData->unk350.unk4[6].x = 1.0f;
        bmData->unk350.unk4[6].y = -1.457f;
        bmData->unk350.unk4[6].z = -0.05f;
        bmData->unk350.unk4[6].w = 0.491f;
        break;
    case PILOT_ROBIN:
        bmData->unk294.x = 0;
        bmData->unk294.y = -0.0991f;
        bmData->unk294.z = 0.4056f;
        bmData->unk3F4 = MODEL_BIRDMAN_ROBIN;
        bmData->unk3F7 = 0x16;
        bmData->unk3F6 = 1;
        bmData->unk3F8 = 2;
        bmData->unk3F9 = 5;
        bmData->unk2F8 = 0xF;
        bmData->unk2F9 = 8;
        bmData->unk2A0 = 0.6f;
        bmData->unk2A4 = 1.0f;
        bmData->unk2AC = 0.8f;
        bmData->unk2A8 = 0.8f;
        bmData->unk2B0 = 1.2f;
        bmData->unk2B8 = 0x4C;
        bmData->unk2C0 = 0x49;
        bmData->unk2B4 = 1.2f;
        bmData->unk320.x = 0.0f;
        bmData->unk320.y = 0.108f;
        bmData->unk320.z = 0.782f;
        bmData->unk32C.x = -4.206f;
        bmData->unk32C.y = -0.202f;
        bmData->unk32C.z = 0.574f;
        bmData->unk338.x = 4.207f;
        bmData->unk338.y = -0.202f;
        bmData->unk344.y = 0.0f;
        bmData->unk344.x = 0.0f;
        bmData->unk338.z = 0.574f;
        bmData->unk344.z = -1.138f;
        bmData->unk350.count = 7;
        bmData->unk350.unk4[0].x = 0.0f;
        bmData->unk350.unk4[0].y = -1.826f;
        bmData->unk350.unk4[0].z = -0.06f;
        bmData->unk350.unk4[0].w = 0.217f;
        bmData->unk350.unk4[1].x = 0.125f;
        bmData->unk350.unk4[1].y = -1.689f;
        bmData->unk350.unk4[1].z = -0.606f;
        bmData->unk350.unk4[1].w = 0.158f;
        bmData->unk350.unk4[2].x = 0.25f;
        bmData->unk350.unk4[2].y = -1.074f;
        bmData->unk350.unk4[2].z = -1.247f;
        bmData->unk350.unk4[2].w = -0.01f;
        bmData->unk350.unk4[3].x = 0.625f;
        bmData->unk350.unk4[3].y = -1.804f;
        bmData->unk350.unk4[3].z = -0.068f;
        bmData->unk350.unk4[3].w = 0.407f;
        bmData->unk350.unk4[4].x = 0.75f;
        bmData->unk350.unk4[4].y = -1.519f;
        bmData->unk350.unk4[4].z = 0.881f;
        bmData->unk350.unk4[4].w = 0.208f;
        bmData->unk350.unk4[5].x = 0.875f;
        bmData->unk350.unk4[5].y = -1.415f;
        bmData->unk350.unk4[5].z = 0.89f;
        bmData->unk350.unk4[5].w = 0.392f;
        bmData->unk350.unk4[6].x = 1.0f;
        bmData->unk350.unk4[6].y = -1.826f;
        bmData->unk350.unk4[6].z = -0.06f;
        bmData->unk350.unk4[6].w = 0.217f;
        break;
    default:
        break;
    }
}

// called every frame during birdman
void bird_802CE0A4(BirdmanData* bmData) {
    if (bmData->unk290 != 0) {
        bmData->unk2 &= ~4;
        uvDobjProps(bmData->objId, 4, bmData->unk3F7, 0);
        if (bmData->unk3F4 == MODEL_BIRDMAN_KIWI) {
            uvDobjProps(bmData->objId, 4, 0x17, 0);
            uvDobjProps(bmData->objId, 4, 0x18, 0);
        }
    } else {
        bmData->unk2 |= 4;
        uvDobjProps(bmData->objId, 5, bmData->unk3F7, 0);
        if (bmData->unk3F4 == MODEL_BIRDMAN_KIWI) {
            uvDobjProps(bmData->objId, 5, 0x17, 0);
            uvDobjProps(bmData->objId, 5, 0x18, 0);
        }
    }
    uvDobjState(bmData->objId, bmData->unk2);
}
