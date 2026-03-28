#include "common.h"

#include <uv_audio.h>
#include <uv_controller.h>
#include <uv_dobj.h>
#include <uv_environment.h>
#include <uv_event.h>
#include <uv_math.h>
#include <uv_matrix.h>
#include <uv_memory.h>
#include <uv_model.h>
#include <uv_graphics.h>
#include "cannonball.h"
#include "cbsound.h"
#include "camera.h"
#include "code_60020.h"
#include "code_66160.h"
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
    D_80359A30.unk0 = 8;
    D_80359A30.unk4 = 0.0f;
    D_80359A30.unk8 = 0.0f;
    D_80359A30.unkC = 0.2f;
    D_80359A30.unk10 = 0.04f;
    D_80359A30.unk14 = 0.4f;
    D_80359A30.unk18 = 0.16f;
    D_80359A30.unk1C = 0.6f;
    D_80359A30.unk20 = 0.36f;
    D_80359A30.unk24 = 0.7f;
    D_80359A30.unk28 = 0.49f;
    D_80359A30.unk2C = 0.8f;
    D_80359A30.unk30 = 0.64f;
    D_80359A30.unk34 = 0.9f;
    D_80359A30.unk38 = 0.81f;
    D_80359A30.unk40 = 1.0f;
    D_80359A30.unk3C = 1.0f;
}

// cannonLoadLevel is invoked when loading cannonball level
void cannonLoadLevel(u8 arg0, u8 pilot, CannonballData* arg2, Camera* arg3) {
    uvMemSet(arg2, 0, sizeof(CannonballData));
    cannonLoadPilot(pilot, arg2);
    arg2->objId = uvDobjAllocIdx();
    arg2->unk2 = 2;
    uvDobjModel(arg2->objId, arg2->modelId);
    uvDobjPosm(arg2->objId, 0, &arg2->unk14);
    uvDobjState(arg2->objId, arg2->unk2);
    arg2->unk54 = uvDobjAllocIdx();
    arg2->unk56 = 2;
    uvDobjModel(arg2->unk54, MODEL_CANNON_ON_PILLAR);
    uvDobjPosm(arg2->unk54, 0, &arg2->unk58);
    uvDobjState(arg2->unk54, arg2->unk56);
    arg2->unkB0 = arg3;
    arg3->unk40 += 100.0f;
    arg2->unk10 = arg0;
    arg2->unkA4 = 0.0f;
    arg2->unk293 = 0;
    arg2->unk4 = 2;
    func_802D9430(arg2);
    cbSoundInit(arg2);
}

// cannonLevelEnterLeave is invoked when loading and exiting cannonball level
void cannonLevelEnterLeave(CannonballData* arg0) {
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;

    if (arg0->unkE == 0) {
        db_getstart(&arg0->unk58, &arg0->unk1B8, NULL, NULL);
        uvDobjPosm(arg0->unk54, 0, &arg0->unk58);
        func_80313570(&arg0->unk58, &sp54, &sp50, &sp4C, &sp48, &sp44, &sp40);
        arg0->unk98 = sp48;
        arg0->xAxis = 0.52359873f; // almost DEG_TO_RAD(30)
        arg0->zAxis = 0.0f;
    }
    uvMat4Copy(&arg0->unk14, &arg0->unk58);
    uvDobjPosm(arg0->objId, 0, &arg0->unk14);
    func_802D94EC(arg0);
    arg0->unkCC = 0.0f;
    arg0->unkD0 = 0.0f;
    arg0->unkD4 = 0;
    arg0->unkC4 = 0;
    arg0->unkC8 = 0.0f;
    arg0->unk293 = 0;
    arg0->unk8 = 0.0f;
    arg0->unk2 = 2;
    arg0->unk56 = 2;
    uvDobjState(arg0->objId, arg0->unk2);
    uvDobjState(arg0->unk54, arg0->unk56);
    arg0->unkB4 = 5;
    arg0->unkB8 = 1.0f;
    arg0->unkB0->unk1 = arg0->unkB4;
    arg0->unkB0->unk4 = arg0->unk54;
    arg0->unkB0->unk6 = arg0->unk56;
    arg0->unkB0->unk0 = 0x20;
    arg0->unkB0->unk68.x = arg0->unk26C;
    arg0->unkB0->unk68.y = arg0->unk270;
    arg0->unkB0->unk68.z = arg0->unk274;
    arg0->unkB0->unk74 = 0.0f;
    arg0->unkB0->unk5C = 0;
    arg0->unkB0->unk60 = -1.0f;
    arg0->unkB0->unk64 = -2.0f;
    arg0->unkB0->unk54 = 2.0f;
    arg0->unkB0->unk58 = 6.0f;
    arg0->unkB0->unk48 = 0.06f;
    arg0->unkB0->unk4C = 1;
    arg0->unkB0->unk50 = 0.0f;
    arg0->unkB0->unk228 = 0.0f;
    uvModelGetProps(arg0->modelId, 1, &arg0->unkB0->unk8, 0);
    func_802D45C4(arg0->unkB0, arg0->unkB8);
    D_8034E9F0 = 4.712389f; // DEG_TO_RAD(270)
    D_8034E9F4 = 0;
    D_8034E9F8 = 0;
}

// cannonEndTarget is invoked at the end of a cannonball target
void cannonEndTarget(CannonballData* arg0) {
    uvDobjModel(arg0->objId, MODEL_WORLD);
    uvDobjModel(arg0->unk54, MODEL_WORLD);
    arg0->unk10 = 0xFFFF;
    arg0->objId = 0xFFFF;
    arg0->unk54 = 0xFFFF;
    arg0->unkB0->unk40 -= 100.0f;
}

// cannonMovementFrame called every frame while aiming cannon and while in flight
void cannonMovementFrame(CannonballData* arg0, u8 gameState) {
    f32 stickX;
    f32 stickY;
    s32 spE4;
    Camera* temp_v0;
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

    if (func_802E6B5C() == 4) {
        return;
    }

    arg0->unk8 += D_8034F854;
    arg0->unk11D = 0;
    if (gameState != GAME_STATE_RESULTS) {
        stickX = demoGetInputs(arg0->unk10, INPUT_AXIS_X);
        stickY = demoGetInputs(arg0->unk10, INPUT_AXIS_Y);
        spE4 = demoGetButtons(arg0->unk10);
    }
    sp2C = &arg0->unk14;
    func_802E65AC(&arg0->unk14, &D_80362690->terraId, &stickX, &stickY, &spE4);
    if (gameState != GAME_STATE_RESULTS) {
        spC8[0] = arg0->zAxis;
        spC8[1] = arg0->xAxis;
        spC7 = (arg0->unkD4 * 2) | (arg0->unkC4 & 1);
        func_802E682C(spC8, ARRAY_COUNT(spC8), spC7);
    } else {
        func_802E6870(spC8, ARRAY_COUNT(spC8), &spC7);
        arg0->zAxis = spC8[0];
        arg0->xAxis = spC8[1];
        arg0->unkD4 = spC7 >> 1;
        arg0->unkC4 = spC7 & 1;
    }
    if (stickX > 0.0f) {
        var_fv0 = stickX;
    } else {
        var_fv0 = -stickX;
    }
    arg0->unkBC = func_80313F08(&D_80359A30, var_fv0);
    if (stickX < 0 /*.0f*/) {
        arg0->unkBC = -arg0->unkBC;
    }
    if (stickY > 0.0f) {
        var_fv0_2 = stickY;
    } else {
        var_fv0_2 = -stickY;
    }
    arg0->unkC0 = func_80313F08(&D_80359A30, var_fv0_2);
    if (stickY < 0.0f) {
        arg0->unkC0 = -arg0->unkC0;
    }
    if ((spE4 & 0x8000) && (D_8034F850 >= 2.0f)) {
        arg0->unkC4 = 1;
    }
    if ((arg0->unkC4 != 0) && (arg0->unkC8 == 0.0f)) {
        arg0->unkC8 = D_8034F850;
    }
    if (arg0->unkD4 == 0) {
        cannonAimingFrame(arg0);
    }
    if ((gameState != GAME_STATE_RESULTS) && (arg0->unkD4 == 1)) {
        func_802D95D8(arg0);
    }
    if (arg0->unkD4 == 2) {
        cannonPilotLand(arg0);
    }
    func_802D8AF0(arg0);
    uvDobjPosm(arg0->objId, 0, sp2C);
    if (D_8034E9F4 != 0) {
        arg0->unkCC = 0.0f;
    } else {
        if (spE4 & 2) {
            var_fa0 = 1.5707963f; // DEG_TO_RAD(90)
        } else if (spE4 & 1) {
            var_fa0 = -1.5707963f; // -DEG_TO_RAD(90)
        } else {
            var_fa0 = 0.0f;
        }
        arg0->unkCC = func_80313AF4(var_fa0, arg0->unkCC, 2.0f);
    }
    if (D_8034E9F4 != 0) {
        arg0->unkD0 = 0.0f;
    } else {
        if (spE4 & 4) {
            var_fa0_2 = 1.5707963f; // DEG_TO_RAD(90)
        } else if (spE4 & 8) {
            var_fa0_2 = -1.5707963f; // -DEG_TO_RAD(90)
        } else {
            var_fa0_2 = 0.0f;
        }
        arg0->unkD0 = func_80313AF4(var_fa0_2, arg0->unkD0, 2.0f);
    }
    if (gameState != GAME_STATE_RESULTS) {
        if (arg0->unkD4 == 0 || (D_8034F850 - arg0->unkC8) < 0.5f) {
            arg0->unkB4 = 5;
            arg0->unkB8 = 1.0f;
            if (demoButtonPress(arg0->unk10, R_TRIG) != 0) {
                func_8033F758(0x6A, 1.0f, 0.5f, 0);
                D_8034E9F4 = !D_8034E9F4;
            }
            if (!D_8034E9F4) {
                uvMat4Copy(&sp7C, &arg0->unk58);
                uvMat4RotateAxis(&sp7C, arg0->zAxis - arg0->unkCC, 'z');
                uvMat4LocalTranslate(&sp7C, 0.0f, -12.0f, 2.0f);
                uvMat4RotateAxis(&sp7C, arg0->xAxis * 0.3f, 'x');
                uvMat4Copy(&arg0->unkB0->unk108, &sp7C);
            } else {
                uvMat4Copy(&sp7C, &arg0->unk58);
                uvMat4RotateAxis(&sp7C, arg0->zAxis, 'z');
                uvMat4RotateAxis(&sp7C, arg0->xAxis, 'x');
                uvMat4LocalTranslate(&sp7C, 0.0f, 3.6000001f, 0.0f);
                uvMat4Copy(&arg0->unkB0->unk108, &sp7C);
            }
            uvMat4Copy(&sp3C, sp2C);
            uvMat4LocalTranslate(&sp3C, 0.0f, -4.0f, -1.0f);
            temp_v0 = arg0->unkB0;
            func_802EAC18(temp_v0->unk230, temp_v0->unk14, &sp3C);
        } else {
            D_8034E9F4 = 0;
            if ((arg0->unkB4 == 5) && (arg0->unkD4 != 2)) {
                arg0->unkB0->unkD = 0;
                D_8034E9F8++;
                if (D_8034E9F8 == 3) {
                    arg0->unkB4 = 0;
                }
            }
            if (demoButtonPress(arg0->unk10, R_TRIG) != 0) {
                func_8033F758(0x6A, 1.0f, 0.5f, 0);
                if (arg0->unkB4 == 0) {
                    arg0->unkB4 = 8;
                } else {
                    arg0->unkB4 = 0;
                    arg0->unkB8 = 1.0f;
                }
            }
        }
        arg0->unkB0->unk4 = arg0->objId;
        arg0->unkB0->unk6 = arg0->unk2;
        arg0->unkB0->unk78 = arg0->unkCC;
        arg0->unkB0->unk7C = arg0->unkD0;
        arg0->unkB0->unk204.x = arg0->unk1C4.x;
        arg0->unkB0->unk204.y = arg0->unk1C4.y;
        arg0->unkB0->unk204.z = arg0->unk1C4.z;
        arg0->unkB0->unk228 = arg0->unk120;
        uvMat4Copy(&arg0->unkB0->unk80, sp2C);
        func_802D5884(arg0->unkB0, arg0->unkB4);
        func_802D45C4(arg0->unkB0, arg0->unkB8);
    }
    if (gameState != GAME_STATE_RESULTS) {
        hud = hudGetState();
        if (arg0->unkD4 == 0) {
            uvMat4Copy(&hud->unk28, &arg0->unk58);
            uvMat4RotateAxis(&hud->unk28, arg0->zAxis, 'z');
        } else {
            uvMat4Copy(&hud->unk28, sp2C);
        }
        if ((arg0->unkB4 != 8) && (arg0->unkD4 != 2)) {
            hud->renderFlags = HUD_RENDER_CANNONBALL;
        } else {
            hud->renderFlags = 0;
        }
        hud->att.heading = arg0->unk14.m[3][2];
        hud->elapsedTime = arg0->unk8;
        hud->power = arg0->unkA4;
        hud->unk8C = arg0->unk1C4.z * 4.0f * 0.7f;
        hud->altitude = arg0->unk120 * 0.7f;
        hud->altSeaLevel = arg0->unk14.m[3][2] * 0.7f;
        hud->speed = arg0->unk1D0 * 3.6f * 0.7f;
        hud->unk20 = arg0->unk98 + arg0->zAxis;
        hud->unk24 = arg0->xAxis;
        hud->unk8 = 3 - arg0->unkE;
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
void cannonAimingFrame(CannonballData* arg0) {
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

    arg0->unkA4 = (((1.5f * sp34) - (uvSinF(D_8034E9F0) * 0.5f)) * 0.5f) + 0.5f;
    if (demoButtonCheck(0, Z_TRIG) == 0) {
        arg0->zAxis -= 0.25f * arg0->unkBC * D_8034F854;
        arg0->xAxis -= 0.25f * arg0->unkC0 * D_8034F854;

        if (FABS(arg0->unkBC) > 0 || FABS(arg0->unkC0) > 0) {
            arg0->unk11D = 1;
        }
    } else {
        // square result, but maintain +/-
        sp34 = SQ(arg0->unkBC);
        if (arg0->unkBC < 0) {
            sp34 = -sp34;
        }
        arg0->zAxis -= (1.0f / 2.0f) * sp34 * D_8034F854; // if 0.5f, tries to reuse reg
        if (sp34 > 0) {
            arg0->unk11D = 1;
        }

        // square result, but maintain +/-
        sp34 = SQ(arg0->unkC0);
        if (arg0->unkC0 < 0) {
            sp34 = -sp34;
        }
        arg0->xAxis -= (1.0f / 2.0f) * sp34 * D_8034F854; // if 0.5f, tries to reuse reg
        if (sp34 > 0) {
            arg0->unk11D = 1;
        }
    }

    if (arg0->xAxis < -0.1745329f) { // almost DEG_TO_RAD(-10.0)
        arg0->xAxis = -0.1745329f;
    } else if (arg0->xAxis > 1.0471975f) { // almost DEG_TO_RAD(60.0)
        arg0->xAxis = 1.0471975f;
    }
    uvModelGetPosm(0x105, 1, &sp38);
    uvMat4RotateAxis(&sp38, arg0->zAxis, 'z');
    uvMat4RotateAxis(&sp38, arg0->xAxis, 'x');
    uvDobjPosm(arg0->unk54, 1, &sp38);
    uvModelGetPosm(0x105, 2, &sp38);
    uvMat4RotateAxis(&sp38, -arg0->xAxis + (1.44f * arg0->zAxis), 'x');
    uvDobjPosm(arg0->unk54, 2, &sp38);
    uvModelGetPosm(0x105, 3, &sp38);
    uvMat4RotateAxis(&sp38, -arg0->xAxis - (1.44f * arg0->zAxis), 'x');
    uvDobjPosm(arg0->unk54, 3, &sp38);
    if (D_80359A84 == 0) {
        switch (arg0->unkC) {
        case 0:
            hudText_8031D8E0(0x111, 2.0f, 0);
            break;
        case 1:
            hudText_8031D8E0(0x10, 2.0f, 0);
            break;
        case 2:
            hudText_8031D8E0(0xD5, 2.0f, 0);
            break;
        case 3:
            hudText_8031D8E0(0x1A2, 2.0f, 0);
            break;
        default:
            hudText_8031D8E0(0x1A2, 2.0f, 0);
            break;
        }
        D_80359A84 = 1;
    }
    if (arg0->unkC4 != 0) {
        cannonShoot(arg0);
    } else {
        uvDobjState(arg0->objId, 0);
    }
}
#if defined(__clang__)
#pragma GCC diagnostic pop
#endif

// cannonShoot called when firing the cannon
void cannonShoot(CannonballData* arg0) {
    Mtx4F sp50;

    uvMat4Copy(&sp50, &arg0->unk58);
    uvMat4RotateAxis(&sp50, arg0->zAxis, 'z');
    uvMat4RotateAxis(&sp50, arg0->xAxis, 'x');
    uvMat4LocalTranslate(&sp50, 0.0f, 6.0f, 0.0f);
    func_802F9BF8(2, sp50.m[3][0], sp50.m[3][1], sp50.m[3][2], 20.0f, 0.3f, 0.0f, 1.0f, 0.8f, 0.0f, 1.0f);
    sndPlaySfx(0x4B);
    uvEmitterTrigger(arg0->unk2B4);
    arg0->unkD4 = 1;
    arg0->unk1B8.x = 0.0f;
    arg0->unk1B8.y = 0.0f;
    arg0->unk1B8.z = (arg0->unkA4 * 271.4f * arg0->unk280) + 2.5f;
    uvMat4Copy(&arg0->unk14, &sp50);
    uvMat4RotateAxis(&arg0->unk14, -1.5707963f, 'x');
    uvDobjState(arg0->objId, arg0->unk2);
    D_80359A84 = 0;
    func_802D9430(arg0);
}

// cannonPilotLand called when pilot lands on surface after being shot from cannon
void cannonPilotLand(CannonballData* arg0) {
    static Vec4F D_80359AB0;
    static Vec4F D_80359AC0;
    static f32 D_8034E9FC = 0.0f;
    Camera* temp_v0;
    f32 temp_fv0_2;
    f32 var_fv1;
    f32 spB8;
    f32 z;
    Mtx4F sp74;
    Mtx4F sp34;

    if (arg0->unk293 == 0) {
        arg0->unk293 = 1;
        if (arg0->unk11C != 0) {
            z = arg0->unk14.m[3][2]; // forces going through f0, instead of a2 direct
            func_802F8AB8(arg0->unk14.m[3][0], arg0->unk14.m[3][1], z, 1.0f, &arg0->unk1C4);
            arg0->unkB0->unk6 = 0;
            arg0->unk2 = arg0->unkB0->unk6;
            uvDobjState(arg0->objId, arg0->unk2);
            uvMat4Copy(&arg0->unkB0->unk80, &arg0->unk14);
        }
        uvMat4Copy(&arg0->unkB0->unk80, &arg0->unk14);
        D_80359AB0.x = arg0->unkB0->unk108.m[3][0];
        D_80359AB0.y = arg0->unkB0->unk108.m[3][1];
        D_80359AB0.z = arg0->unkB0->unk108.m[3][2];
        D_80359AC0.x = arg0->unk14.m[3][0] + (arg0->unk12C.x * 100.0f);
        D_80359AC0.y = arg0->unk14.m[3][1] + (arg0->unk12C.y * 100.0f);
        D_80359AC0.z = arg0->unk14.m[3][2] + (arg0->unk12C.z * 100.0f);
        D_8034E9FC = 0;
    }
    arg0->unkB4 = 5;
    func_802D5884(arg0->unkB0, arg0->unkB4);

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
    uvMat4UnkOp6(&sp74, &arg0->unk14, &sp34);
    if (func_802D472C(arg0->unkB0, &sp34) != 0) {
        uvMat4UnkOp6(&sp74, &arg0->unk14, &sp34);
    }
    func_802D4A30(arg0->unkB0, &sp74);
    uvMat4Copy(&arg0->unkB0->unk108, &sp74);
    hudGetState()->renderFlags = 0;
    func_802D9220(arg0);
}

// cannonLoadPilot is invoked when loading cannonball level
void cannonLoadPilot(u8 pilot, CannonballData* arg1) {
    switch (pilot) {
    case PILOT_LARK:
        arg1->unk224.x = -0.025f, arg1->unk224.y = 0.097f, arg1->unk224.z = 0.675f;
        arg1->unk230.x = 0.0f, arg1->unk230.y = 0.0f, arg1->unk230.z = -0.745f;
        arg1->unk23C.x = -0.027f, arg1->unk23C.y = 0.442f, arg1->unk23C.z = 0.012f;
        arg1->unk248.x = -0.024f, arg1->unk248.y = -0.27f, arg1->unk248.z = 0.101f;
        arg1->unk254.x = -0.54f, arg1->unk254.y = -0.156f, arg1->unk254.z = 0.105f;
        arg1->unk260.x = 0.486f, arg1->unk260.y = -0.156f, arg1->unk260.z = 0.105f;
        arg1->unk26C = -0.025f;
        arg1->unk270 = 0.307f;
        arg1->unk274 = 0.478f;
        arg1->unk278 = 0.96f;
        arg1->unk280 = 0.8f;
        arg1->unk27C = 5.88f;
        arg1->modelId = MODEL_CANNONB_LARK_LAUNCHED;
        arg1->unk292 = 1;
        arg1->unk285 = 0xA;
        arg1->unk286 = 0xB;
        arg1->unk287 = 8;
        arg1->unk288 = 9;
        arg1->unk289 = 2;
        arg1->unk28A = 3;
        arg1->unk28B = 4;
        arg1->unk28C = 5;
        arg1->unk28D = 6;
        arg1->unk28E = 7;
        arg1->unk291 = 0xC;
        arg1->unk284 = 0x3E;
        break;
    case PILOT_GOOSE:
        arg1->unk224.x = -0.001f, arg1->unk224.y = 0.172f, arg1->unk224.z = 0.782f;
        arg1->unk230.x = 0.0f, arg1->unk230.y = 0.0f, arg1->unk230.z = -1.336f;
        arg1->unk23C.x = 0.001f, arg1->unk23C.y = 0.647f, arg1->unk23C.z = -0.002f;
        arg1->unk248.x = -0.001f, arg1->unk248.y = -0.341f, arg1->unk248.z = 0.19f;
        arg1->unk254.x = -0.722f, arg1->unk254.y = -0.178f, arg1->unk254.z = 0.148f;
        arg1->unk260.x = 0.73f, arg1->unk260.y = -0.178f, arg1->unk260.z = 0.148f;
        arg1->unk26C = 0.0f;
        arg1->unk270 = 0.315f;
        arg1->unk274 = 0.603f;
        arg1->unk278 = 0.8f;
        arg1->unk280 = 1.0f;
        arg1->unk27C = 9.8f;
        arg1->modelId = MODEL_CANNONB_GOOSE_LAUNCHED;
        arg1->unk292 = 6;
        arg1->unk285 = 2;
        arg1->unk286 = 3;
        arg1->unk287 = 4;
        arg1->unk288 = 5;
        arg1->unk289 = 0xA;
        arg1->unk28A = 0xB;
        arg1->unk28B = 0xC;
        arg1->unk28C = 7;
        arg1->unk28D = 8;
        arg1->unk28E = 9;
        arg1->unk291 = 1;
        arg1->unk284 = 0x3F;
        break;
    case PILOT_HAWK:
        arg1->unk224.x = 0.003f, arg1->unk224.y = 0.187f, arg1->unk224.z = 0.634f;
        arg1->unk230.x = 0.0f, arg1->unk230.y = 0.0f, arg1->unk230.z = -1.221f;
        arg1->unk23C.x = -0.01f, arg1->unk23C.y = 0.698f, arg1->unk23C.z = -0.013f;
        arg1->unk248.x = -0.004f, arg1->unk248.y = -0.43f, arg1->unk248.z = -0.117f;
        arg1->unk254.x = -0.819f, arg1->unk254.y = -0.245f, arg1->unk254.z = 0.069f;
        arg1->unk260.x = 0.837f, arg1->unk260.y = -0.245f, arg1->unk260.z = 0.069f;
        arg1->unk26C = 0.002f;
        arg1->unk270 = 0.325f;
        arg1->unk274 = 0.52f;
        arg1->unk278 = 0.64f;
        arg1->unk280 = 1.2f;
        arg1->unk27C = 13.72f;
        arg1->modelId = MODEL_CANNONB_HAWK_LAUNCHED;
        arg1->unk292 = 6;
        arg1->unk285 = 1;
        arg1->unk286 = 2;
        arg1->unk287 = 3;
        arg1->unk288 = 4;
        arg1->unk289 = 0xA;
        arg1->unk28A = 0xB;
        arg1->unk28B = 0xC;
        arg1->unk28C = 7;
        arg1->unk28D = 8;
        arg1->unk28E = 9;
        arg1->unk291 = 5;
        arg1->unk284 = 0x40;
        break;
    case PILOT_KIWI:
        arg1->unk224.x = 0.002f, arg1->unk224.y = 0.084f, arg1->unk224.z = 0.706f;
        arg1->unk230.x = 0.0f, arg1->unk230.y = 0.0f, arg1->unk230.z = -0.828f;
        arg1->unk23C.x = 0.0f, arg1->unk23C.y = 0.426f, arg1->unk23C.z = 0.03f;
        arg1->unk248.x = 0.0f, arg1->unk248.y = -0.261f, arg1->unk248.z = 0.107f;
        arg1->unk254.x = -0.479f, arg1->unk254.y = -0.153f, arg1->unk254.z = 0.079f;
        arg1->unk260.x = 0.489f, arg1->unk260.y = -0.153f, arg1->unk260.z = 0.079f;
        arg1->unk26C = 0.002f;
        arg1->unk270 = 0.308f;
        arg1->unk274 = 0.473f;
        arg1->unk278 = 0.96f;
        arg1->unk280 = 0.8f;
        arg1->unk27C = 5.88f;
        arg1->modelId = MODEL_CANNONB_KIWI_LAUNCHED;
        arg1->unk292 = 8;
        arg1->unk285 = 1;
        arg1->unk286 = 2;
        arg1->unk287 = 3;
        arg1->unk288 = 4;
        arg1->unk289 = 9;
        arg1->unk28A = 0xA;
        arg1->unk28B = 0xB;
        arg1->unk28C = 0xC;
        arg1->unk28D = 0xD;
        arg1->unk28E = 0xE;
        arg1->unk291 = 5;
        arg1->unk284 = 0x41;
        break;
    case PILOT_IBIS:
        arg1->unk224.x = -0.002f, arg1->unk224.y = 0.085f, arg1->unk224.z = 0.799f;
        arg1->unk230.x = 0, arg1->unk230.y = 0.0f, arg1->unk230.z = -1.36f;
        arg1->unk23C.x = 0.0f, arg1->unk23C.y = 0.586f, arg1->unk23C.z = -0.034f;
        arg1->unk248.x = 0.0f, arg1->unk248.y = -0.314f, arg1->unk248.z = 0.091f;
        arg1->unk254.x = -0.666f, arg1->unk254.y = -0.164f, arg1->unk254.z = 0.141f;
        arg1->unk260.x = 0.678f, arg1->unk260.y = -0.164f, arg1->unk260.z = 0.141f;
        arg1->unk26C = 0.0f;
        arg1->unk270 = 0.212f;
        arg1->unk274 = 0.599f;
        arg1->unk278 = 0.8f;
        arg1->unk280 = 1.0f;
        arg1->unk27C = 9.8f;
        arg1->modelId = MODEL_CANNONB_IBIS_LAUNCHED;
        arg1->unk292 = 6;
        arg1->unk285 = 2;
        arg1->unk286 = 3;
        arg1->unk287 = 4;
        arg1->unk288 = 5;
        arg1->unk289 = 0xA;
        arg1->unk28A = 0xB;
        arg1->unk28B = 0xC;
        arg1->unk28C = 7;
        arg1->unk28D = 8;
        arg1->unk28E = 9;
        arg1->unk291 = 1;
        arg1->unk284 = 0x42;
        break;
    case PILOT_ROBIN:
        arg1->unk224.x = -0.001f, arg1->unk224.y = 0.095f, arg1->unk224.z = 0.844f;
        arg1->unk230.x = 0.0f, arg1->unk230.y = 0.0f, arg1->unk230.z = -1.076f;
        arg1->unk23C.x = 0.0f, arg1->unk23C.y = 0.563f, arg1->unk23C.z = -0.018f;
        arg1->unk248.x = 0.0f, arg1->unk248.y = -0.433f, arg1->unk248.z = 0.155f;
        arg1->unk254.x = -0.737f, arg1->unk254.y = -0.266f, arg1->unk254.z = 0.112f;
        arg1->unk260.x = 0.751f, arg1->unk260.y = -0.266f, arg1->unk260.z = 0.112f;
        arg1->unk26C = 0.0f;
        arg1->unk270 = 0.217f;
        arg1->unk274 = 0.621f;
        arg1->unk278 = 0.64f;
        arg1->unk280 = 1.2f;
        arg1->unk27C = 13.72f;
        arg1->modelId = MODEL_CANNONB_ROBIN_LAUNCHED;
        arg1->unk292 = 6;
        arg1->unk285 = 2;
        arg1->unk286 = 3;
        arg1->unk287 = 4;
        arg1->unk288 = 5;
        arg1->unk289 = 7;
        arg1->unk28A = 8;
        arg1->unk28B = 9;
        arg1->unk28C = 0xA;
        arg1->unk28D = 0xB;
        arg1->unk28E = 0xC;
        arg1->unk291 = 1;
        arg1->unk284 = 0x43;
        break;
    }
}

s32 cannonLoad802D77D8(Unk80362690* arg0, CannonballData* arg1) {
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
    func_8033F964(1);
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
    uvEnvFunc(arg0->envId, 0, func_802E0CF0);
    func_8034B5E0(temp_s1->unk70->unk22C, temp_s1->unk70);
    for (i = 0; i < 4; i++) {
        temp_s1->unk74->unk40[temp_s1->cls].unk0[i][temp_s1->veh].unk4 = 0x7F;
    }
    temp_s1->vehicleData = arg1;
    cannonLoadLevel(arg0->unk9C, temp_s1->pilot, arg1, temp_s1->unk70);
    cannonLevelEnterLeave(arg1);
    arg1->unkC = 0;
    arg1->unkE = 0;
    for (i = 0; i < 4; i++) {
        D_80359A88[i] = 0;
    }
    uvMat4Copy(&sp3C, &arg1->unk14);
    uvMat4RotateAxis(&sp3C, 1.5707961f, 'x');
    func_802EDD9C(temp_s1, &sp3C);
    func_802D4DE8(temp_s1->unk70, 0);
    func_8032B508(temp_s1->unk74);
    func_80313E0C(0.0f);
    func_802E66F4(1.0f);
    func_802E68B0(1);
    func_8033F748(0x10);
    func_8033F964(0);
    func_8033FCD0(temp_s1->veh);
    uvEventPost(0xB, 0);
    D_80359A84 = 0;
    hudWarningText(0xDB, 1.5f, 8.0f);
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
    func_802E15F0();
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
s32 cannonLandedFrame(CannonballData* arg0) {
    static f32 D_8034EA00 = 0.0f;
    Unk80364210* temp_v1;
    Unk80362690_Unk0* temp_s0;
    u8 sp27;
    s32 var_a2;

    temp_s0 = &D_80362690->unkC[D_80362690->unk9C];
    temp_v1 = func_8032BE10();
    if (0.0f == D_8034EA00) {
        D_8034EA00 = D_8034F850 + 3.0f;
        if (arg0->unkD5 == 2) {
            sp27 = 1;
        } else {
            sp27 = 0;
        }
        if (sp27) {
            temp_v1->unk0 = arg0->unk4;
            func_8032B560(temp_s0->unk74, temp_s0->cls, temp_s0->test, temp_s0->veh);

            var_a2 = temp_s0->unk74->unk40[temp_s0->cls].unk0[temp_s0->test][temp_s0->veh].unk4;
            if ((D_80359A88[arg0->unkC] < var_a2) || var_a2 == 0x7F) {
                D_80359A88[arg0->unkC] = var_a2;
            }
            temp_s0->unk74->unk40[temp_s0->cls].unk0[temp_s0->test][temp_s0->veh].unk4 = D_80359A88[arg0->unkC];
        } else {
            if (temp_s0->unk74->unk40[temp_s0->cls].unk0[temp_s0->test][temp_s0->veh].unk4 == 0x7F) {
                temp_s0->unk74->unk40[temp_s0->cls].unk0[temp_s0->test][temp_s0->veh].unk4 = 0;
            }
            var_a2 = 0;
        }
        if (!sp27) {
            hudText_8031D8E0(0x14D, 2.0f, 8.0f);
        } else {
            textFmtIntAt(textGetDataByIdx(0x1AC), var_a2, 2, 0);
            hudText_8031D8E0(0x1AC, 2.0f, 8.0f);
            if (var_a2 == 0x19) {
                hudWarningText(0x16F, 2.0f, 8.0f);
                func_8033F964(1);
                sndPlaySfx(0x11);
            } else {
                sndPlaySfx(0x36);
                func_8033F748(0x11);
                func_8033F964(0);
                func_8033FCD0(temp_s0->veh);
            }
        }
    }
    uvEventPost(0xC, 0);
    if (D_8034F850 < D_8034EA00) {
        cannonPilotLand(arg0);
        func_80313D74();
        taskFrameUpdate(&temp_s0->unk2C, temp_s0->unk20);
        uvGfxBegin();
        func_8034B624(temp_s0->unk70);
        uvGfxEnd();
        return GAME_STATE_RESULTS;
    }
    D_8034EA00 = 0.0f;
    if (arg0->unkE == 2 && arg0->unkC < 3) {
        func_8033F748(0x1C);
        func_8033F964(0);
        func_8033FCD0(temp_s0->veh);
        resultHandler(1);
    }
    if (cannonEndShot(arg0) != 0) {
        return GAME_STATE_TEST_UPDATE;
    }
    hudText_8031D8E0(-1, 0, 0.0f);
    hudWarningText(-1, 0.0f, 0.0f);
    return GAME_STATE_RESULTS_CB;
}

// cannonEndShot called once after landing before the cannon is reset for next shot
s32 cannonEndShot(CannonballData* arg0) {
    u16 sp2E;
    u16 sp2C;
    u16 sp2A;
    Unk80362690_Unk0* temp_s1;

    temp_s1 = &D_80362690->unkC[D_80362690->unk9C];
    if (arg0->unkE == 0xFF) {
        arg0->unkE = 0;
        arg0->unkC = 0;
        sp2E = 0xFF;
    } else {
        sp2E = arg0->unkC;
        arg0->unkE++;
        if (arg0->unkE > 2) {
            arg0->unkC++;
            arg0->unkE = 0;
            if (arg0->unkC >= 4) {
                temp_s1->test = 0;
                cannonEndAllTgts(arg0);
                return 0;
            }
            temp_s1->test++;
        }
    }

    func_8033F748(0x10);
    func_8033F964(0);
    func_8033FCD0(temp_s1->veh);
    if (arg0->unkC != sp2E) {
        uvEventPost(0x19, 0);
        envSoundInit();
        sp2A = arg0->unkE;
        sp2C = arg0->unkC;
        taskDeinitLevel();
        windObjDeinit();
        proxAnimDispatchInit();
        level_8030BA60();
        cannonLevelEnterLeave(arg0);
        cannonEndTarget(arg0);
        taskInitTest(temp_s1->cls, temp_s1->veh, temp_s1->test, &D_80362690->map, &D_80362690->terraId, &D_80362690->envId);
        levelLoad(D_80362690->map, temp_s1->pilot, temp_s1->veh, 1);
        hudInit();
        hud_8031A2CC();
        taskLoad();
        windObjLoad();
        uvChanTerra(temp_s1->unk70->unk22C, D_80362690->terraId);
        uvEnvFunc(D_80362690->envId, 0, func_802E0CF0);
        cannonLoadLevel(D_80362690->unk9C, temp_s1->pilot, arg0, temp_s1->unk70);
        cannonLevelEnterLeave(arg0);
        arg0->unkE = sp2A;
        arg0->unkC = sp2C;
        func_8034B5E0(temp_s1->unk70->unk22C, temp_s1->unk70);
    }
    cannonLevelEnterLeave(arg0);
    func_802D4DE8(arg0->unkB0, 0);
    func_80313E0C(0.0f);
    switch (arg0->unkE) {
    case 0:
        hudWarningText(0xDB, 1.5f, 8.0f);
        break;
    case 1:
        hudWarningText(0x52, 1.5f, 8.0f);
        break;
    case 2:
        hudWarningText(0x1A8, 1.5f, 8.0f);
        break;
    }
    return 1;
}

// cannonEndAllTgts called once after all four cannon targets are complete
s32 cannonEndAllTgts(CannonballData* arg0) {
    Unk80362690_Unk0* temp_s0;
    Mtx4F sp4C;
    s32 i;

    temp_s0 = &D_80362690->unkC[D_80362690->unk9C];
    uvEventPost(0xD, 0);
    func_8033F748(0x1C);
    func_8033F964(0);
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

    uvMat4Copy(&sp4C, &arg0->unk14);
    uvMat4RotateAxis(&sp4C, 1.5707961f, 'x');
    func_802EDAF0(temp_s0, &arg0->unk14, arg0->unk120, arg0->unk1D0, 0.0f, 1.0f, arg0->unk4, arg0->unk8, 0, arg0->unk11C, 5);
    saveFileWrite(temp_s0->unk8A);
    return 1;
}

void cannon_802D8A40(u8 arg0, CannonballData* arg1) {
    Unk80362690_Unk0* unkC;
    unkC = &D_80362690->unkC[D_80362690->unk9C];
    if (unkC->veh == 3) {
        if (arg0 == 1) {
            uvDobjState(arg1->objId, 0);
            uvDobjState(arg1->unk54, 0);
        } else {
            uvDobjState(arg1->objId, arg1->unk2);
            uvDobjState(arg1->unk54, arg1->unk56);
        }
    }
}
