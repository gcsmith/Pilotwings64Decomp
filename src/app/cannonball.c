#include "common.h"

#include <uv_audio.h>
#include <uv_controller.h>
#include <uv_dobj.h>
#include <uv_environment.h>
#include <uv_math.h>
#include <uv_matrix.h>
#include <uv_memory.h>
#include <uv_model.h>
#include <uv_graphics.h>
#include "cannonball.h"
#include "cbsound.h"
#include "camera.h"
#include "code_60020.h"
#include "code_66F70.h"
#include "code_72010.h"
#include "game.h"
#include "code_7FE00.h"
#include "code_9A960.h"
#include "code_B2900.h"
#include "code_B3A70.h"
#include "code_D2B10.h"
#include "demo.h"
#include "env_sound.h"
#include "environment.h"
#include "fdr.h"
#include "hud.h"
#include "proxanim.h"
#include "results.h"
#include "snd.h"
#include "task.h"
#include "test_menu.h"
#include "text_data.h"
#include "wind_objects.h"

// .data
f32 D_8034E9F0 = 0.0f;
u8 D_8034E9F4 = 0;
s32 D_8034E9F8 = 0;

// .bss likely owned by this file
Unk803599D0 D_80359A30;
u8 D_80359A84;
s32 D_80359A88[4];
s32 D_80359A98[4];
s32 D_80359AA8;
s32 D_80359AAC;

// forward declarations
s32 cannonEndShot(CannonballData*);
s32 cannonEndAllTgts(CannonballData*);

void cannonInit(void) {
    D_80359A30.count = 8;
    D_80359A30.unk4[0].x = 0.0f, D_80359A30.unk4[0].y = 0.0f;
    D_80359A30.unk4[1].x = 0.2f, D_80359A30.unk4[1].y = 0.04f;
    D_80359A30.unk4[2].x = 0.4f, D_80359A30.unk4[2].y = 0.16f;
    D_80359A30.unk4[3].x = 0.6f, D_80359A30.unk4[3].y = 0.36f;
    D_80359A30.unk4[4].x = 0.7f, D_80359A30.unk4[4].y = 0.49f;
    D_80359A30.unk4[5].x = 0.8f, D_80359A30.unk4[5].y = 0.64f;
    D_80359A30.unk4[6].x = 0.9f, D_80359A30.unk4[6].y = 0.81f;
    D_80359A30.unk4[7].x = 1.0f, D_80359A30.unk4[7].y = 1.0f;
}

// cannonLoadLevel is invoked when loading cannonball level
void cannonLoadLevel(u8 contIdx, u8 pilot, CannonballData* cbData, Camera* camera) {
    uvMemSet(cbData, 0, sizeof(CannonballData));
    cannonLoadPilot(pilot, cbData);
    cbData->objId = uvDobjAllocIdx();
    cbData->unk2 = 2;
    uvDobjModel(cbData->objId, cbData->modelId);
    uvDobjPosm(cbData->objId, 0, &cbData->unk14);
    uvDobjState(cbData->objId, cbData->unk2);
    cbData->unk54 = uvDobjAllocIdx();
    cbData->unk56 = 2;
    uvDobjModel(cbData->unk54, MODEL_CANNON_ON_PILLAR);
    uvDobjPosm(cbData->unk54, 0, &cbData->unk58);
    uvDobjState(cbData->unk54, cbData->unk56);
    cbData->camera = camera;
    camera->clipFar += 100.0f;
    cbData->unk10 = contIdx;
    cbData->unkA4 = 0.0f;
    cbData->unk293 = 0;
    cbData->unk4 = 2;
    func_802D9430(cbData);
    cbSoundInit(cbData);
}

// cannonLevelEnterLeave is invoked when loading and exiting cannonball level
void cannonLevelEnterLeave(CannonballData* cbData) {
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;

    if (cbData->unkE == 0) {
        db_getstart(&cbData->unk58, &cbData->unk1B8, NULL, NULL);
        uvDobjPosm(cbData->unk54, 0, &cbData->unk58);
        func_80313570(&cbData->unk58, &sp54, &sp50, &sp4C, &sp48, &sp44, &sp40);
        cbData->unk98 = sp48;
        cbData->xAxis = 0.52359873f; // almost DEG_TO_RAD(30)
        cbData->zAxis = 0.0f;
    }
    uvMat4Copy(&cbData->unk14, &cbData->unk58);
    uvDobjPosm(cbData->objId, 0, &cbData->unk14);
    func_802D94EC(cbData);
    cbData->unkCC = 0.0f;
    cbData->unkD0 = 0.0f;
    cbData->unkD4 = 0;
    cbData->unkC4 = 0;
    cbData->unkC8 = 0.0f;
    cbData->unk293 = 0;
    cbData->unk8 = 0.0f;
    cbData->unk2 = 2;
    cbData->unk56 = 2;
    uvDobjState(cbData->objId, cbData->unk2);
    uvDobjState(cbData->unk54, cbData->unk56);
    cbData->unkB4 = 5;
    cbData->unkB8 = 1.0f;
    cbData->camera->unk1 = cbData->unkB4;
    cbData->camera->unk4 = cbData->unk54;
    cbData->camera->unk6 = cbData->unk56;
    cbData->camera->unk0 = 0x20;
    cbData->camera->unk68.x = cbData->unk26C;
    cbData->camera->unk68.y = cbData->unk270;
    cbData->camera->unk68.z = cbData->unk274;
    cbData->camera->unk74 = 0.0f;
    cbData->camera->unk5C = 0;
    cbData->camera->unk60 = -1.0f;
    cbData->camera->unk64 = -2.0f;
    cbData->camera->unk54 = 2.0f;
    cbData->camera->unk58 = 6.0f;
    cbData->camera->unk48 = 0.06f;
    cbData->camera->unk4C = 1;
    cbData->camera->unk50 = 0.0f;
    cbData->camera->unk228 = 0.0f;
    uvModelGetProps(cbData->modelId, MODEL_PROP_UNK1(&cbData->camera->unk8), MODEL_PROP_END);
    camera_802D45C4(cbData->camera, cbData->unkB8);
    D_8034E9F0 = 4.712389f; // DEG_TO_RAD(270)
    D_8034E9F4 = 0;
    D_8034E9F8 = 0;
}

// cannonEndTarget is invoked at the end of a cannonball target
void cannonEndTarget(CannonballData* cbData) {
    uvDobjModel(cbData->objId, MODEL_WORLD);
    uvDobjModel(cbData->unk54, MODEL_WORLD);
    cbData->unk10 = 0xFFFF;
    cbData->objId = 0xFFFF;
    cbData->unk54 = 0xFFFF;
    cbData->camera->clipFar -= 100.0f;
}

// cannonMovementFrame called every frame while aiming cannon and while in flight
void cannonMovementFrame(CannonballData* cbData, u8 gameState) {
    f32 stickX;
    f32 stickY;
    s32 spE4;
    Camera* camera;
    f32 var_fa0;
    f32 var_fa0_2;
    f32 var_fv0;
    f32 var_fv0_2;
    f32 spC8[2];
    u8 spC7;
    HUDState* hud;
    u16 temp_v0_3;
    Mtx4F sp7C;
    Mtx4F sp3C;
    Mtx4F* sp2C;

    if (fdr_802E6B5C() == 4) {
        return;
    }

    cbData->unk8 += D_8034F854;
    cbData->unk11D = 0;
    if (gameState != GAME_STATE_RESULTS) {
        stickX = demoGetInputs(cbData->unk10, INPUT_AXIS_X);
        stickY = demoGetInputs(cbData->unk10, INPUT_AXIS_Y);
        spE4 = demoGetButtons(cbData->unk10);
    }
    sp2C = &cbData->unk14;
    fdr_802E65AC(&cbData->unk14, &D_80362690->terraId, &stickX, &stickY, &spE4);
    if (gameState != GAME_STATE_RESULTS) {
        spC8[0] = cbData->zAxis;
        spC8[1] = cbData->xAxis;
        spC7 = (cbData->unkD4 * 2) | (cbData->unkC4 & 1);
        fdr_802E682C(spC8, ARRAY_COUNT(spC8), spC7);
    } else {
        fdr_802E6870(spC8, ARRAY_COUNT(spC8), &spC7);
        cbData->zAxis = spC8[0];
        cbData->xAxis = spC8[1];
        cbData->unkD4 = spC7 >> 1;
        cbData->unkC4 = spC7 & 1;
    }
    if (stickX > 0.0f) {
        var_fv0 = stickX;
    } else {
        var_fv0 = -stickX;
    }
    cbData->unkBC = func_80313F08(&D_80359A30, var_fv0);
    if (stickX < 0 /*.0f*/) {
        cbData->unkBC = -cbData->unkBC;
    }
    if (stickY > 0.0f) {
        var_fv0_2 = stickY;
    } else {
        var_fv0_2 = -stickY;
    }
    cbData->unkC0 = func_80313F08(&D_80359A30, var_fv0_2);
    if (stickY < 0.0f) {
        cbData->unkC0 = -cbData->unkC0;
    }
    if ((spE4 & 0x8000) && (D_8034F850 >= 2.0f)) {
        cbData->unkC4 = 1;
    }
    if ((cbData->unkC4 != 0) && (cbData->unkC8 == 0.0f)) {
        cbData->unkC8 = D_8034F850;
    }
    if (cbData->unkD4 == 0) {
        cannonAimingFrame(cbData);
    }
    if ((gameState != GAME_STATE_RESULTS) && (cbData->unkD4 == 1)) {
        func_802D95D8(cbData);
    }
    if (cbData->unkD4 == 2) {
        cannonPilotLand(cbData);
    }
    func_802D8AF0(cbData);
    uvDobjPosm(cbData->objId, 0, sp2C);
    if (D_8034E9F4 != 0) {
        cbData->unkCC = 0.0f;
    } else {
        if (spE4 & 2) {
            var_fa0 = 1.5707963f; // DEG_TO_RAD(90)
        } else if (spE4 & 1) {
            var_fa0 = -1.5707963f; // -DEG_TO_RAD(90)
        } else {
            var_fa0 = 0.0f;
        }
        cbData->unkCC = func_80313AF4(var_fa0, cbData->unkCC, 2.0f);
    }
    if (D_8034E9F4 != 0) {
        cbData->unkD0 = 0.0f;
    } else {
        if (spE4 & 4) {
            var_fa0_2 = 1.5707963f; // DEG_TO_RAD(90)
        } else if (spE4 & 8) {
            var_fa0_2 = -1.5707963f; // -DEG_TO_RAD(90)
        } else {
            var_fa0_2 = 0.0f;
        }
        cbData->unkD0 = func_80313AF4(var_fa0_2, cbData->unkD0, 2.0f);
    }
    if (gameState != GAME_STATE_RESULTS) {
        if (cbData->unkD4 == 0 || (D_8034F850 - cbData->unkC8) < 0.5f) {
            cbData->unkB4 = 5;
            cbData->unkB8 = 1.0f;
            if (demoButtonPress(cbData->unk10, R_TRIG) != 0) {
                sndPlaySfxVolPitchPan(0x6A, 1.0f, 0.5f, 0);
                D_8034E9F4 = !D_8034E9F4;
            }
            if (!D_8034E9F4) {
                uvMat4Copy(&sp7C, &cbData->unk58);
                uvMat4RotateAxis(&sp7C, cbData->zAxis - cbData->unkCC, 'z');
                uvMat4LocalTranslate(&sp7C, 0.0f, -12.0f, 2.0f);
                uvMat4RotateAxis(&sp7C, cbData->xAxis * 0.3f, 'x');
                uvMat4Copy(&cbData->camera->unk108, &sp7C);
            } else {
                uvMat4Copy(&sp7C, &cbData->unk58);
                uvMat4RotateAxis(&sp7C, cbData->zAxis, 'z');
                uvMat4RotateAxis(&sp7C, cbData->xAxis, 'x');
                uvMat4LocalTranslate(&sp7C, 0.0f, 3.6000001f, 0.0f);
                uvMat4Copy(&cbData->camera->unk108, &sp7C);
            }
            uvMat4Copy(&sp3C, sp2C);
            uvMat4LocalTranslate(&sp3C, 0.0f, -4.0f, -1.0f);
            camera = cbData->camera;
            func_802EAC18(&camera->unk230, camera->unk14, &sp3C);
        } else {
            D_8034E9F4 = 0;
            if ((cbData->unkB4 == 5) && (cbData->unkD4 != 2)) {
                cbData->camera->unkD = 0;
                D_8034E9F8++;
                if (D_8034E9F8 == 3) {
                    cbData->unkB4 = 0;
                }
            }
            if (demoButtonPress(cbData->unk10, R_TRIG) != 0) {
                sndPlaySfxVolPitchPan(0x6A, 1.0f, 0.5f, 0);
                if (cbData->unkB4 == 0) {
                    cbData->unkB4 = 8;
                } else {
                    cbData->unkB4 = 0;
                    cbData->unkB8 = 1.0f;
                }
            }
        }
        cbData->camera->unk4 = cbData->objId;
        cbData->camera->unk6 = cbData->unk2;
        cbData->camera->unk78 = cbData->unkCC;
        cbData->camera->unk7C = cbData->unkD0;
        cbData->camera->unk204.x = cbData->unk1C4.x;
        cbData->camera->unk204.y = cbData->unk1C4.y;
        cbData->camera->unk204.z = cbData->unk1C4.z;
        cbData->camera->unk228 = cbData->unk120;
        uvMat4Copy(&cbData->camera->unk80, sp2C);
        camera_802D5884(cbData->camera, cbData->unkB4);
        camera_802D45C4(cbData->camera, cbData->unkB8);
    }
    if (gameState != GAME_STATE_RESULTS) {
        hud = hudGetState();
        if (cbData->unkD4 == 0) {
            uvMat4Copy(&hud->unk28, &cbData->unk58);
            uvMat4RotateAxis(&hud->unk28, cbData->zAxis, 'z');
        } else {
            uvMat4Copy(&hud->unk28, sp2C);
        }
        if ((cbData->unkB4 != 8) && (cbData->unkD4 != 2)) {
            hud->renderFlags = HUD_RENDER_CANNONBALL;
        } else {
            hud->renderFlags = 0;
        }
        hud->att.heading = cbData->unk14.m[3][2];
        hud->elapsedTime = cbData->unk8;
        hud->power = cbData->unkA4;
        hud->unk8C = cbData->unk1C4.z * 4.0f * 0.7f;
        hud->altitude = cbData->unk120 * 0.7f;
        hud->altSeaLevel = cbData->unk14.m[3][2] * 0.7f;
        hud->speed = cbData->unk1D0 * 3.6f * 0.7f;
        hud->unk20 = cbData->unk98 + cbData->zAxis;
        hud->unk24 = cbData->xAxis;
        hud->unk8 = 3 - cbData->unkE;
        if (D_8034E9F4 != 0) {
            hud->renderFlags |= HUD_RENDER_RETICLE;
        } else {
            if (hud->renderFlags & HUD_RENDER_RETICLE) {
                hud->renderFlags &= ~HUD_RENDER_RETICLE;
            }
        }
        hud->reticleX = hud->reticleY = 0.0f;
        hud->unkC74 = 0;
    }
}

#if defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsometimes-uninitialized"
#endif
// cannonAimingFrame called every frame while inside cannon
// controls the rate of rotation and Z-button presses
void cannonAimingFrame(CannonballData* cbData) {
    Mtx4F sp38;
    f32 sp34;

    if (D_8034F850 >= 2.0f) {
        D_8034E9F0 += 1.2f * D_8034F854;
    }
    if (D_8034E9F0 > 6.2831855f) { // little more than 2*PI or DEG_TO_RAD(360)
        D_8034E9F0 -= 6.2831855f;
    }
    if (D_8034E9F0 <= 1.5707964f) {                             // DEG_TO_RAD(90)
        sp34 = D_8034E9F0 / 1.5707964f;                         // DEG_TO_RAD(90)
    } else if (D_8034E9F0 <= 3.1415927f) {                      // PI or DEG_TO_RAD(180)
        sp34 = 1.0f - ((D_8034E9F0 - 1.5707964f) / 1.5707964f); // - DEG_TO_RAD(90) / DEG_TO_RAD(90)
    } else if (D_8034E9F0 <= 4.712389f) {                       // DEG_TO_RAD(270)
        sp34 = -(D_8034E9F0 - 3.1415927f) / 1.5707964f;         // - DEG_TO_RAD(180) / DEG_TO_RAD(90)
    } else if (D_8034E9F0 <= 6.2831855f) {                      // DEG_TO_RAD(360)
        // this block should just be `else` since `D_8034E9F0 > 6.2831855f` above
        sp34 = ((D_8034E9F0 - 4.712389f) / 1.5707964f) + -1.0f; // - DEG_TO_RAD(270) / DEG_TO_RAD(90)
    } else {
        // sp34 ends up being uninitalized here
    }

    cbData->unkA4 = (((1.5f * sp34) - (uvSinF(D_8034E9F0) * 0.5f)) * 0.5f) + 0.5f;
    if (demoButtonCheck(0, Z_TRIG) == 0) {
        cbData->zAxis -= 0.25f * cbData->unkBC * D_8034F854;
        cbData->xAxis -= 0.25f * cbData->unkC0 * D_8034F854;

        if (FABS(cbData->unkBC) > 0 || FABS(cbData->unkC0) > 0) {
            cbData->unk11D = 1;
        }
    } else {
        // square result, but maintain +/-
        sp34 = SQ(cbData->unkBC);
        if (cbData->unkBC < 0) {
            sp34 = -sp34;
        }
        cbData->zAxis -= (1.0f / 2.0f) * sp34 * D_8034F854; // if 0.5f, tries to reuse reg
        if (sp34 > 0) {
            cbData->unk11D = 1;
        }

        // square result, but maintain +/-
        sp34 = SQ(cbData->unkC0);
        if (cbData->unkC0 < 0) {
            sp34 = -sp34;
        }
        cbData->xAxis -= (1.0f / 2.0f) * sp34 * D_8034F854; // if 0.5f, tries to reuse reg
        if (sp34 > 0) {
            cbData->unk11D = 1;
        }
    }

    if (cbData->xAxis < -0.1745329f) { // almost DEG_TO_RAD(-10.0)
        cbData->xAxis = -0.1745329f;
    } else if (cbData->xAxis > 1.0471975f) { // almost DEG_TO_RAD(60.0)
        cbData->xAxis = 1.0471975f;
    }
    uvModelGetPosm(0x105, 1, &sp38);
    uvMat4RotateAxis(&sp38, cbData->zAxis, 'z');
    uvMat4RotateAxis(&sp38, cbData->xAxis, 'x');
    uvDobjPosm(cbData->unk54, 1, &sp38);
    uvModelGetPosm(0x105, 2, &sp38);
    uvMat4RotateAxis(&sp38, -cbData->xAxis + (1.44f * cbData->zAxis), 'x');
    uvDobjPosm(cbData->unk54, 2, &sp38);
    uvModelGetPosm(0x105, 3, &sp38);
    uvMat4RotateAxis(&sp38, -cbData->xAxis - (1.44f * cbData->zAxis), 'x');
    uvDobjPosm(cbData->unk54, 3, &sp38);
    if (D_80359A84 == 0) {
        switch (cbData->unkC) {
        case 0:
            hudText_8031D8E0(TEXT_C_TERGET_1, 2.0f, 0);
            break;
        case 1:
            hudText_8031D8E0(TEXT_C_TERGET_2, 2.0f, 0);
            break;
        case 2:
            hudText_8031D8E0(TEXT_C_TERGET_3, 2.0f, 0);
            break;
        case 3:
            hudText_8031D8E0(TEXT_C_TERGET_4, 2.0f, 0);
            break;
        default:
            hudText_8031D8E0(TEXT_C_TERGET_4, 2.0f, 0);
            break;
        }
        D_80359A84 = 1;
    }
    if (cbData->unkC4 != 0) {
        cannonShoot(cbData);
    } else {
        uvDobjState(cbData->objId, 0);
    }
}
#if defined(__clang__)
#pragma GCC diagnostic pop
#endif

// cannonShoot called when firing the cannon
void cannonShoot(CannonballData* cbData) {
    Mtx4F sp50;

    uvMat4Copy(&sp50, &cbData->unk58);
    uvMat4RotateAxis(&sp50, cbData->zAxis, 'z');
    uvMat4RotateAxis(&sp50, cbData->xAxis, 'x');
    uvMat4LocalTranslate(&sp50, 0.0f, 6.0f, 0.0f);
    func_802F9BF8(2, sp50.m[3][0], sp50.m[3][1], sp50.m[3][2], 20.0f, 0.3f, 0.0f, 1.0f, 0.8f, 0.0f, 1.0f);
    sndPlaySfx(0x4B);
    uvEmitterTrigger(cbData->unk2B4);
    cbData->unkD4 = 1;
    cbData->unk1B8.x = 0.0f;
    cbData->unk1B8.y = 0.0f;
    cbData->unk1B8.z = (cbData->unkA4 * 271.4f * cbData->unk280) + 2.5f;
    uvMat4Copy(&cbData->unk14, &sp50);
    uvMat4RotateAxis(&cbData->unk14, -1.5707963f, 'x');
    uvDobjState(cbData->objId, cbData->unk2);
    D_80359A84 = 0;
    func_802D9430(cbData);
}

// cannonPilotLand called when pilot lands on surface after being shot from cannon
void cannonPilotLand(CannonballData* cbData) {
    static Vec4F D_80359AB0;
    static Vec4F D_80359AC0;
    static f32 D_8034E9FC = 0.0f;
    Camera* camera;
    f32 temp_fv0_2;
    f32 var_fv1;
    f32 spB8;
    f32 z;
    Mtx4F sp74;
    Mtx4F sp34;

    if (cbData->unk293 == 0) {
        cbData->unk293 = 1;
        if (cbData->unk11C != 0) {
            z = cbData->unk14.m[3][2]; // forces going through f0, instead of a2 direct
            func_802F8AB8(cbData->unk14.m[3][0], cbData->unk14.m[3][1], z, 1.0f, &cbData->unk1C4);
            cbData->camera->unk6 = 0;
            cbData->unk2 = cbData->camera->unk6;
            uvDobjState(cbData->objId, cbData->unk2);
            uvMat4Copy(&cbData->camera->unk80, &cbData->unk14);
        }
        uvMat4Copy(&cbData->camera->unk80, &cbData->unk14);
        D_80359AB0.x = cbData->camera->unk108.m[3][0];
        D_80359AB0.y = cbData->camera->unk108.m[3][1];
        D_80359AB0.z = cbData->camera->unk108.m[3][2];
        D_80359AC0.x = cbData->unk14.m[3][0] + (cbData->unk12C.x * 100.0f);
        D_80359AC0.y = cbData->unk14.m[3][1] + (cbData->unk12C.y * 100.0f);
        D_80359AC0.z = cbData->unk14.m[3][2] + (cbData->unk12C.z * 100.0f);
        D_8034E9FC = 0;
    }
    cbData->unkB4 = 5;
    camera_802D5884(cbData->camera, cbData->unkB4);

    spB8 = D_8034E9FC * 0.5f;
    if (spB8 < 0.0f) {
        spB8 = 0.0f;
    } else if (spB8 > 0.99f) {
        spB8 = 0.99f;
    }
    D_8034E9FC += D_8034F854;
    uvMat4SetIdentity(&sp34);
    temp_fv0_2 = (1.0f - spB8);
    sp34.m[3][0] = (spB8 * D_80359AC0.x) + (temp_fv0_2 * D_80359AB0.x);
    sp34.m[3][1] = (spB8 * D_80359AC0.y) + (temp_fv0_2 * D_80359AB0.y);
    sp34.m[3][2] = (spB8 * D_80359AC0.z) + (temp_fv0_2 * D_80359AB0.z);
    uvMat4UnkOp6(&sp74, &cbData->unk14, &sp34);
    if (camera_802D472C(cbData->camera, &sp34) != 0) {
        uvMat4UnkOp6(&sp74, &cbData->unk14, &sp34);
    }
    camera_802D4A30(cbData->camera, &sp74);
    uvMat4Copy(&cbData->camera->unk108, &sp74);
    hudGetState()->renderFlags = 0;
    func_802D9220(cbData);
}

// cannonLoadPilot is invoked when loading cannonball level
void cannonLoadPilot(u8 pilot, CannonballData* cbData) {
    switch (pilot) {
    case PILOT_LARK:
        cbData->unk224.x = -0.025f, cbData->unk224.y = 0.097f, cbData->unk224.z = 0.675f;
        cbData->unk230.x = 0.0f, cbData->unk230.y = 0.0f, cbData->unk230.z = -0.745f;
        cbData->unk23C.x = -0.027f, cbData->unk23C.y = 0.442f, cbData->unk23C.z = 0.012f;
        cbData->unk248.x = -0.024f, cbData->unk248.y = -0.27f, cbData->unk248.z = 0.101f;
        cbData->unk254.x = -0.54f, cbData->unk254.y = -0.156f, cbData->unk254.z = 0.105f;
        cbData->unk260.x = 0.486f, cbData->unk260.y = -0.156f, cbData->unk260.z = 0.105f;
        cbData->unk26C = -0.025f;
        cbData->unk270 = 0.307f;
        cbData->unk274 = 0.478f;
        cbData->unk278 = 0.96f;
        cbData->unk280 = 0.8f;
        cbData->unk27C = 5.88f;
        cbData->modelId = MODEL_CANNONB_LARK_LAUNCHED;
        cbData->unk292 = 1;
        cbData->unk285 = 0xA;
        cbData->unk286 = 0xB;
        cbData->unk287 = 8;
        cbData->unk288 = 9;
        cbData->unk289 = 2;
        cbData->unk28A = 3;
        cbData->unk28B = 4;
        cbData->unk28C = 5;
        cbData->unk28D = 6;
        cbData->unk28E = 7;
        cbData->unk291 = 0xC;
        cbData->unk284 = 0x3E;
        break;
    case PILOT_GOOSE:
        cbData->unk224.x = -0.001f, cbData->unk224.y = 0.172f, cbData->unk224.z = 0.782f;
        cbData->unk230.x = 0.0f, cbData->unk230.y = 0.0f, cbData->unk230.z = -1.336f;
        cbData->unk23C.x = 0.001f, cbData->unk23C.y = 0.647f, cbData->unk23C.z = -0.002f;
        cbData->unk248.x = -0.001f, cbData->unk248.y = -0.341f, cbData->unk248.z = 0.19f;
        cbData->unk254.x = -0.722f, cbData->unk254.y = -0.178f, cbData->unk254.z = 0.148f;
        cbData->unk260.x = 0.73f, cbData->unk260.y = -0.178f, cbData->unk260.z = 0.148f;
        cbData->unk26C = 0.0f;
        cbData->unk270 = 0.315f;
        cbData->unk274 = 0.603f;
        cbData->unk278 = 0.8f;
        cbData->unk280 = 1.0f;
        cbData->unk27C = 9.8f;
        cbData->modelId = MODEL_CANNONB_GOOSE_LAUNCHED;
        cbData->unk292 = 6;
        cbData->unk285 = 2;
        cbData->unk286 = 3;
        cbData->unk287 = 4;
        cbData->unk288 = 5;
        cbData->unk289 = 0xA;
        cbData->unk28A = 0xB;
        cbData->unk28B = 0xC;
        cbData->unk28C = 7;
        cbData->unk28D = 8;
        cbData->unk28E = 9;
        cbData->unk291 = 1;
        cbData->unk284 = 0x3F;
        break;
    case PILOT_HAWK:
        cbData->unk224.x = 0.003f, cbData->unk224.y = 0.187f, cbData->unk224.z = 0.634f;
        cbData->unk230.x = 0.0f, cbData->unk230.y = 0.0f, cbData->unk230.z = -1.221f;
        cbData->unk23C.x = -0.01f, cbData->unk23C.y = 0.698f, cbData->unk23C.z = -0.013f;
        cbData->unk248.x = -0.004f, cbData->unk248.y = -0.43f, cbData->unk248.z = -0.117f;
        cbData->unk254.x = -0.819f, cbData->unk254.y = -0.245f, cbData->unk254.z = 0.069f;
        cbData->unk260.x = 0.837f, cbData->unk260.y = -0.245f, cbData->unk260.z = 0.069f;
        cbData->unk26C = 0.002f;
        cbData->unk270 = 0.325f;
        cbData->unk274 = 0.52f;
        cbData->unk278 = 0.64f;
        cbData->unk280 = 1.2f;
        cbData->unk27C = 13.72f;
        cbData->modelId = MODEL_CANNONB_HAWK_LAUNCHED;
        cbData->unk292 = 6;
        cbData->unk285 = 1;
        cbData->unk286 = 2;
        cbData->unk287 = 3;
        cbData->unk288 = 4;
        cbData->unk289 = 0xA;
        cbData->unk28A = 0xB;
        cbData->unk28B = 0xC;
        cbData->unk28C = 7;
        cbData->unk28D = 8;
        cbData->unk28E = 9;
        cbData->unk291 = 5;
        cbData->unk284 = 0x40;
        break;
    case PILOT_KIWI:
        cbData->unk224.x = 0.002f, cbData->unk224.y = 0.084f, cbData->unk224.z = 0.706f;
        cbData->unk230.x = 0.0f, cbData->unk230.y = 0.0f, cbData->unk230.z = -0.828f;
        cbData->unk23C.x = 0.0f, cbData->unk23C.y = 0.426f, cbData->unk23C.z = 0.03f;
        cbData->unk248.x = 0.0f, cbData->unk248.y = -0.261f, cbData->unk248.z = 0.107f;
        cbData->unk254.x = -0.479f, cbData->unk254.y = -0.153f, cbData->unk254.z = 0.079f;
        cbData->unk260.x = 0.489f, cbData->unk260.y = -0.153f, cbData->unk260.z = 0.079f;
        cbData->unk26C = 0.002f;
        cbData->unk270 = 0.308f;
        cbData->unk274 = 0.473f;
        cbData->unk278 = 0.96f;
        cbData->unk280 = 0.8f;
        cbData->unk27C = 5.88f;
        cbData->modelId = MODEL_CANNONB_KIWI_LAUNCHED;
        cbData->unk292 = 8;
        cbData->unk285 = 1;
        cbData->unk286 = 2;
        cbData->unk287 = 3;
        cbData->unk288 = 4;
        cbData->unk289 = 9;
        cbData->unk28A = 0xA;
        cbData->unk28B = 0xB;
        cbData->unk28C = 0xC;
        cbData->unk28D = 0xD;
        cbData->unk28E = 0xE;
        cbData->unk291 = 5;
        cbData->unk284 = 0x41;
        break;
    case PILOT_IBIS:
        cbData->unk224.x = -0.002f, cbData->unk224.y = 0.085f, cbData->unk224.z = 0.799f;
        cbData->unk230.x = 0, cbData->unk230.y = 0.0f, cbData->unk230.z = -1.36f;
        cbData->unk23C.x = 0.0f, cbData->unk23C.y = 0.586f, cbData->unk23C.z = -0.034f;
        cbData->unk248.x = 0.0f, cbData->unk248.y = -0.314f, cbData->unk248.z = 0.091f;
        cbData->unk254.x = -0.666f, cbData->unk254.y = -0.164f, cbData->unk254.z = 0.141f;
        cbData->unk260.x = 0.678f, cbData->unk260.y = -0.164f, cbData->unk260.z = 0.141f;
        cbData->unk26C = 0.0f;
        cbData->unk270 = 0.212f;
        cbData->unk274 = 0.599f;
        cbData->unk278 = 0.8f;
        cbData->unk280 = 1.0f;
        cbData->unk27C = 9.8f;
        cbData->modelId = MODEL_CANNONB_IBIS_LAUNCHED;
        cbData->unk292 = 6;
        cbData->unk285 = 2;
        cbData->unk286 = 3;
        cbData->unk287 = 4;
        cbData->unk288 = 5;
        cbData->unk289 = 0xA;
        cbData->unk28A = 0xB;
        cbData->unk28B = 0xC;
        cbData->unk28C = 7;
        cbData->unk28D = 8;
        cbData->unk28E = 9;
        cbData->unk291 = 1;
        cbData->unk284 = 0x42;
        break;
    case PILOT_ROBIN:
        cbData->unk224.x = -0.001f, cbData->unk224.y = 0.095f, cbData->unk224.z = 0.844f;
        cbData->unk230.x = 0.0f, cbData->unk230.y = 0.0f, cbData->unk230.z = -1.076f;
        cbData->unk23C.x = 0.0f, cbData->unk23C.y = 0.563f, cbData->unk23C.z = -0.018f;
        cbData->unk248.x = 0.0f, cbData->unk248.y = -0.433f, cbData->unk248.z = 0.155f;
        cbData->unk254.x = -0.737f, cbData->unk254.y = -0.266f, cbData->unk254.z = 0.112f;
        cbData->unk260.x = 0.751f, cbData->unk260.y = -0.266f, cbData->unk260.z = 0.112f;
        cbData->unk26C = 0.0f;
        cbData->unk270 = 0.217f;
        cbData->unk274 = 0.621f;
        cbData->unk278 = 0.64f;
        cbData->unk280 = 1.2f;
        cbData->unk27C = 13.72f;
        cbData->modelId = MODEL_CANNONB_ROBIN_LAUNCHED;
        cbData->unk292 = 6;
        cbData->unk285 = 2;
        cbData->unk286 = 3;
        cbData->unk287 = 4;
        cbData->unk288 = 5;
        cbData->unk289 = 7;
        cbData->unk28A = 8;
        cbData->unk28B = 9;
        cbData->unk28C = 0xA;
        cbData->unk28D = 0xB;
        cbData->unk28E = 0xC;
        cbData->unk291 = 1;
        cbData->unk284 = 0x43;
        break;
    }
}

s32 cannonLoad802D77D8(Unk80362690* arg0, CannonballData* cbData) {
    s32 i;
    Mtx4F sp3C;
    Unk80362690_Unk0* temp_s1;

    temp_s1 = &arg0->unkC[arg0->unk9C];
    if (temp_s1->test == 0) {
        D_80359AAC = levelGetTotalPoints(temp_s1->unk74, temp_s1->cls, temp_s1->veh);
        D_80359AA8 = 0;
        for (i = 0; i < 4; i++) {
            D_80359A98[i] = testGetPointCount(temp_s1->unk74, temp_s1->cls, i, temp_s1->veh);
            temp_s1->unk74->unk40[temp_s1->cls].unk0[i][temp_s1->veh].unk2C = 0x7F;
            temp_s1->unk74->unk40[temp_s1->cls].unk0[i][temp_s1->veh].unk4 = 0x7F;
        }
    }
    envSoundInit();
    sndSetMusicState(MUS_STATE_STOP_SEQ);
    hud_8031DAA8(0, 0.0f);
    temp_s1->test = 0;
    proxAnimDispatchInit();
    taskInitTest(temp_s1->cls, temp_s1->veh, temp_s1->test, &arg0->map, &arg0->terraId, &arg0->envId);
    levelLoad(arg0->map, temp_s1->pilot, temp_s1->veh, 1);
    hudInit();
    hud_8031A2CC();
    taskLoad();
    windObjLoad();
    uvChanTerra(temp_s1->unk70->unk22C, arg0->terraId);
    uvEnvFunc(arg0->envId, 0, env_802E0CF0);
    func_8034B5E0(temp_s1->unk70->unk22C, temp_s1->unk70);
    for (i = 0; i < 4; i++) {
        temp_s1->unk74->unk40[temp_s1->cls].unk0[i][temp_s1->veh].unk4 = 0x7F;
    }
    temp_s1->vehicleData = cbData;
    cannonLoadLevel(arg0->unk9C, temp_s1->pilot, cbData, temp_s1->unk70);
    cannonLevelEnterLeave(cbData);
    cbData->unkC = 0;
    cbData->unkE = 0;
    for (i = 0; i < 4; i++) {
        D_80359A88[i] = 0;
    }
    uvMat4Copy(&sp3C, &cbData->unk14);
    uvMat4RotateAxis(&sp3C, 1.5707961f, 'x');
    func_802EDD9C(temp_s1, &sp3C);
    camera_802D4DE8(temp_s1->unk70, 0);
    func_8032B508(temp_s1->unk74);
    func_80313E0C(0.0f);
    fdrSetBlen(1.0f);
    fdr_802E68B0(1);
    sndSetMusic(BGM_CANNONBALL);
    sndSetMusicState(MUS_STATE_PLAY_SEQ);
    func_8033FCD0(temp_s1->veh);
    uvEventPost(0xB, 0);
    D_80359A84 = 0;
    hudWarningText(TEXT_CANON_1, 1.5f, 8.0f);
    return GAME_STATE_TEST_UPDATE;
}

// cannonFrame802D7B7C called every frame while aiming cannon and while in flight before landing
s32 cannonFrame802D7B7C(Unk80362690* arg0) {
    Unk80362690_Unk0* temp_s0;
    CannonballData* temp_s1;
    Mtx4F sp58;
    f32 sp54;
    s32 sp50;
    s32 temp_v0;
    s32 i;

    temp_s0 = &arg0->unkC[arg0->unk9C];
    sp50 = 5;
    uvEventPost(0xE, 0);
    env_802E15F0();
    proxAnimUpdate();
    func_80313D74();
    temp_s1 = (CannonballData*)temp_s0->vehicleData;
    cannonMovementFrame(temp_s1, arg0->state);
    if (temp_s1->unkD4 != 0) {
        uvMat4Copy(&sp58, &temp_s1->unk14);
        uvMat4RotateAxis(&sp58, 1.5707961f, 'x');
    } else {
        uvMat4Copy(&sp58, &temp_s1->unk58);
        uvMat4RotateAxis(&sp58, temp_s1->zAxis, 'z');
        uvMat4RotateAxis(&sp58, temp_s1->xAxis, 'x');
    }
    func_802EDAF0(temp_s0, &sp58, temp_s1->unk120, temp_s1->unk1D0, 0.0f, 1.0f, temp_s1->unk4, temp_s1->unk8, 0, temp_s1->unk11C, 1);
    if (temp_s1->unkD4 == 2) {
        sp50 = 6;
    }
    uvEventPost(0x16, 0);
    taskFrameUpdate(&temp_s0->unk2C, temp_s0->unk20);
    func_8033F6F8(&temp_s0->unk70->unk108, &temp_s0->unk2C);
    uvGfxBegin();
    func_8034B624(temp_s0->unk70);
    uvGfxEnd();
    if (demoButtonPress(arg0->unk9C, START_BUTTON) != 0) {
        uvEventPost(0x12, 0);
        sp54 = D_8034F850;
        temp_v0 = func_8032CF28(arg0);
        switch (temp_v0) {
        case 0:
            break;
        case 1:
            uvEventPost(0x17, 0);
            func_8032CC44(arg0);
            uvEventPost(0x18, 0);
            break;
        case 3:
            D_8037DC84 = 1;
            for (i = 0; i < 4; i++) {
                temp_s0->unk74->unk40[temp_s0->cls].unk0[i][temp_s0->veh].unk2C = D_80359A98[i];
                temp_s0->unk74->unk40[temp_s0->cls].unk0[i][temp_s0->veh].unk4 = 0;
            }
            temp_s0->test = 0;
            func_802ECE94(arg0);
            sp50 = 2;
            break;
        }
        D_8034F850 = sp54;
        uvEventPost(0x13, 0);
    }
    return sp50;
}

// cannonLandedFrame called every frame after landing from cannon shot
s32 cannonLandedFrame(CannonballData* cbData) {
    static f32 D_8034EA00 = 0.0f;
    Unk80364210* temp_v1;
    Unk80362690_Unk0* temp_s0;
    u8 sp27;
    s32 points;

    temp_s0 = &D_80362690->unkC[D_80362690->unk9C];
    temp_v1 = func_8032BE10();
    if (0.0f == D_8034EA00) {
        D_8034EA00 = D_8034F850 + 3.0f;
        if (cbData->unkD5 == 2) {
            sp27 = 1;
        } else {
            sp27 = 0;
        }
        if (sp27) {
            temp_v1->unk0 = cbData->unk4;
            func_8032B560(temp_s0->unk74, temp_s0->cls, temp_s0->test, temp_s0->veh);

            points = temp_s0->unk74->unk40[temp_s0->cls].unk0[temp_s0->test][temp_s0->veh].unk4;
            if ((D_80359A88[cbData->unkC] < points) || points == 0x7F) {
                D_80359A88[cbData->unkC] = points;
            }
            temp_s0->unk74->unk40[temp_s0->cls].unk0[temp_s0->test][temp_s0->veh].unk4 = D_80359A88[cbData->unkC];
        } else {
            if (temp_s0->unk74->unk40[temp_s0->cls].unk0[temp_s0->test][temp_s0->veh].unk4 == 0x7F) {
                temp_s0->unk74->unk40[temp_s0->cls].unk0[temp_s0->test][temp_s0->veh].unk4 = 0;
            }
            points = 0;
        }
        if (!sp27) {
            hudText_8031D8E0(TEXT_C_MISS, 2.0f, 8.0f);
        } else {
            textFmtIntAt(textGetDataByIdx(TEXT_C_POINTS), points, 2, 0);
            hudText_8031D8E0(TEXT_C_POINTS, 2.0f, 8.0f);
            if (points == 25) {
                hudWarningText(TEXT_C_PERFECT, 2.0f, 8.0f);
                sndSetMusicState(MUS_STATE_STOP_SEQ);
                sndPlaySfx(SFX_GOAL_GONG);
            } else {
                sndPlaySfx(0x36);
                sndSetMusic(BGM_CANNONBALL_HIT);
                sndSetMusicState(MUS_STATE_PLAY_SEQ);
                func_8033FCD0(temp_s0->veh);
            }
        }
    }
    uvEventPost(0xC, 0);
    if (D_8034F850 < D_8034EA00) {
        cannonPilotLand(cbData);
        func_80313D74();
        taskFrameUpdate(&temp_s0->unk2C, temp_s0->unk20);
        uvGfxBegin();
        func_8034B624(temp_s0->unk70);
        uvGfxEnd();
        return GAME_STATE_RESULTS;
    }
    D_8034EA00 = 0.0f;
    if (cbData->unkE == 2 && cbData->unkC < 3) {
        sndSetMusic(BGM_RESULTS);
        sndSetMusicState(MUS_STATE_PLAY_SEQ);
        func_8033FCD0(temp_s0->veh);
        resultHandler(1);
    }
    if (cannonEndShot(cbData) != 0) {
        return GAME_STATE_TEST_UPDATE;
    }
    hudText_8031D8E0(-1, 0, 0.0f);
    hudWarningText(-1, 0.0f, 0.0f);
    return GAME_STATE_RESULTS_CB;
}

// cannonEndShot called once after landing before the cannon is reset for next shot
s32 cannonEndShot(CannonballData* cbData) {
    u16 sp2E;
    u16 sp2C;
    u16 sp2A;
    Unk80362690_Unk0* temp_s1;

    temp_s1 = &D_80362690->unkC[D_80362690->unk9C];
    if (cbData->unkE == 0xFF) {
        cbData->unkE = 0;
        cbData->unkC = 0;
        sp2E = 0xFF;
    } else {
        sp2E = cbData->unkC;
        cbData->unkE++;
        if (cbData->unkE > 2) {
            cbData->unkC++;
            cbData->unkE = 0;
            if (cbData->unkC >= 4) {
                temp_s1->test = 0;
                cannonEndAllTgts(cbData);
                return 0;
            }
            temp_s1->test++;
        }
    }

    sndSetMusic(BGM_CANNONBALL);
    sndSetMusicState(MUS_STATE_PLAY_SEQ);
    func_8033FCD0(temp_s1->veh);
    if (cbData->unkC != sp2E) {
        uvEventPost(0x19, 0);
        envSoundInit();
        sp2A = cbData->unkE;
        sp2C = cbData->unkC;
        taskDeinitLevel();
        windObjDeinit();
        proxAnimDispatchInit();
        level_8030BA60();
        cannonLevelEnterLeave(cbData);
        cannonEndTarget(cbData);
        taskInitTest(temp_s1->cls, temp_s1->veh, temp_s1->test, &D_80362690->map, &D_80362690->terraId, &D_80362690->envId);
        levelLoad(D_80362690->map, temp_s1->pilot, temp_s1->veh, 1);
        hudInit();
        hud_8031A2CC();
        taskLoad();
        windObjLoad();
        uvChanTerra(temp_s1->unk70->unk22C, D_80362690->terraId);
        uvEnvFunc(D_80362690->envId, 0, env_802E0CF0);
        cannonLoadLevel(D_80362690->unk9C, temp_s1->pilot, cbData, temp_s1->unk70);
        cannonLevelEnterLeave(cbData);
        cbData->unkE = sp2A;
        cbData->unkC = sp2C;
        func_8034B5E0(temp_s1->unk70->unk22C, temp_s1->unk70);
    }
    cannonLevelEnterLeave(cbData);
    camera_802D4DE8(cbData->camera, 0);
    func_80313E0C(0.0f);
    switch (cbData->unkE) {
    case 0:
        hudWarningText(TEXT_CANON_1, 1.5f, 8.0f);
        break;
    case 1:
        hudWarningText(TEXT_CANON_2, 1.5f, 8.0f);
        break;
    case 2:
        hudWarningText(TEXT_CANON_3, 1.5f, 8.0f);
        break;
    }
    return 1;
}

// cannonEndAllTgts called once after all four cannon targets are complete
s32 cannonEndAllTgts(CannonballData* cbData) {
    Unk80362690_Unk0* temp_s0;
    Mtx4F sp4C;
    s32 i;

    temp_s0 = &D_80362690->unkC[D_80362690->unk9C];
    uvEventPost(0xD, 0);
    sndSetMusic(BGM_RESULTS);
    sndSetMusicState(MUS_STATE_PLAY_SEQ);
    func_8033FCD0(temp_s0->veh);
    temp_s0->test = 0;
    temp_s0->unk8B = 1;
    for (i = 0; i < 4; i++) {
        D_80359AA8 += D_80359A88[i];
    }

    if (D_80359AA8 < D_80359AAC) {
        for (i = 0; i < 4; i++) {
            temp_s0->unk74->unk40[temp_s0->cls].unk0[i][temp_s0->veh].unk2C = D_80359A98[i];
        }
    }

    uvMat4Copy(&sp4C, &cbData->unk14);
    uvMat4RotateAxis(&sp4C, 1.5707961f, 'x');
    func_802EDAF0(temp_s0, &cbData->unk14, cbData->unk120, cbData->unk1D0, 0.0f, 1.0f, cbData->unk4, cbData->unk8, 0, cbData->unk11C, 5);
    saveFileWrite(temp_s0->unk8A);
    return 1;
}

void cannon_802D8A40(u8 arg0, CannonballData* cbData) {
    Unk80362690_Unk0* unkC;
    unkC = &D_80362690->unkC[D_80362690->unk9C];
    if (unkC->veh == 3) {
        if (arg0 == 1) {
            uvDobjState(cbData->objId, 0);
            uvDobjState(cbData->unk54, 0);
        } else {
            uvDobjState(cbData->objId, cbData->unk2);
            uvDobjState(cbData->unk54, cbData->unk56);
        }
    }
}
