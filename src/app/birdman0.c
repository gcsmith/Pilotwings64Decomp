#include "common.h"
#include <uv_dobj.h>
#include <uv_event.h>
#include <uv_memory.h>
#include <uv_model.h>
#include "birdman.h"
#include "bmsound.h"
#include "code_5A6A0.h"
#include "code_66160.h"
#include "code_72B70.h"
#include "code_7FED0.h"
#include "code_9A960.h"
#include "demo.h"
#include "fdr.h"
#include "hud.h"
#include "shadow.h"
#include "snap.h"
#include "snd.h"
#include "task.h"

extern Unk803599D0 D_80359390;
extern u8 D_803593E4;

// forward declarations
void bird_802CD0F8(VehicleData*);
void bird_802CD2E8(u8, VehicleData*);
void bird_802CE0A4(VehicleData*);

// called during game boot
void bird_802CC1B0(void) {
    D_80359390.unk0 = 8;
    D_80359390.unk4 = 0.0f;
    D_80359390.unk8 = 0.0f;
    D_80359390.unkC = 0.2f;
    D_80359390.unk10 = 0.04f;
    D_80359390.unk14 = 0.4f;
    D_80359390.unk18 = 0.16f;
    D_80359390.unk1C = 0.6f;
    D_80359390.unk20 = 0.36f;
    D_80359390.unk24 = 0.7f;
    D_80359390.unk28 = 0.49f;
    D_80359390.unk2C = 0.8f;
    D_80359390.unk30 = 0.64f;
    D_80359390.unk34 = 0.9f;
    D_80359390.unk38 = 0.81f;
    D_80359390.unk40 = 1.0f;
    D_80359390.unk3C = 1.0f;
}

// called when starting one of the birdman levels, either from bonus menu or bonus star
void bird_802CC270(u8 arg0, u8 pilot, VehicleData* arg2, Unk802D3658_Arg0* arg3) {
    uvMemSet(arg2, 0, 0x424);
    bird_802CD2E8(pilot, arg2);
    arg2->unk0 = uvDobjAllocIdx();
    arg2->unk2 = 2;
    uvDobjModel(arg2->unk0, arg2->unk3F4);
    uvDobjPosm(arg2->unk0, 0, &arg2->unk10);
    uvDobjState(arg2->unk0, arg2->unk2);
    uvMat4Copy(&arg2->unk50, &arg2->unk10);
    func_80334454(0x13D, 0x13C);
    func_803342F0(1.0f);
    func_803342FC(-2.0f);
    func_803343D8(1);
    arg2->controller = arg0;
    arg2->unk2F0 = 0;
    arg2->unk2CC = 0x1A;
    arg2->unk4 = 0;
    arg2->unkD4 = arg3;
    arg2->unk2BC = 0.0f;
    arg2->unk2C4 = 0.0f;
    arg2->unk2D0 = 0.0f;
    arg2->unk2D4 = 0.0f;
    arg2->unk2D8 = 0.0f;
    arg2->unk2DC = 0.0f;
    uvModelGetProps(arg2->unk3F4, 1, &arg3->unk8, 0);
    bird_802CEBA0(arg2);
    bmSoundInit(arg2);
}

// called when entering or exiting a birdman level
void birdEnterLeave(VehicleData* arg0) {
    db_getstart(&arg0->unk10, &arg0->unk200, NULL, NULL);
    uvDobjPosm(arg0->unk0, 0, &arg0->unk10);
    uvMat4Copy(&arg0->unk50, &arg0->unk10);
    bird_802CECB8(arg0);
    arg0->unk104 = 0;
    arg0->unk105 = 0;
    arg0->unk2 = 2;
    arg0->unk290 = 1;
    arg0->unkEC = 0.0f;
    arg0->unkF0 = 0.0f;
    arg0->unk8 = 0.0f;
    arg0->unk2FC = 0.0f;
    arg0->unk300 = 0.0f;
    arg0->unk304 = 0.0f;
    arg0->unk308 = 0.0f;
    arg0->unk2E8 = 0.0f;
    arg0->unk2E0 = 0.0f;
    arg0->unk2EC = 0.0f;
    arg0->unk2E4 = 0.0f;
    bird_802CE0A4(arg0);
    arg0->unkD8 = 0;
    arg0->unkDC = 1.0f;
    arg0->unkD4->unk1 = arg0->unkD8;
    arg0->unkD4->unk4 = arg0->unk0;
    arg0->unkD4->unk6 = arg0->unk2;
    arg0->unkD4->unk0 = 1;
    arg0->unkD4->unk74 = 0.0f;
    arg0->unkD4->unk5C = 0;
    arg0->unkD4->unk60 = -3.5f;
    arg0->unkD4->unk64 = 0.5f;
    arg0->unkD4->unk54 = 3.0f;
    arg0->unkD4->unk58 = 6.5f;
    arg0->unkD4->unk48 = 0.0125f;
    arg0->unkD4->unk4C = 1.0f;
    arg0->unkD4->unk50 = 0.0f;
    arg0->unkD4->unk228 = 0.0f;
    D_803593E4 = 0;
    func_802D45C4(arg0->unkD4, arg0->unkDC);
}

// called when exiting a birdman level
void bird_802CC51C(Unk802CC51C* arg0) {
    uvDobjModel(arg0->objId, 0xFFFF);
    arg0->unkC = 0xFFFF;
    arg0->objId = 0xFFFF;
    func_80334C70();
}

// called every frame in a birdman stage
// handles controller input and motion updates
void birdMovementFrame(VehicleData* arg0, u8 arg1) {
    f32 sp7C;
    f32 sp78;
    f32 pad;
    s32 buttons;
    HUDState* sp6C;
    s32 sp68;
    f32 temp_fv0;
    f32 sp4C[6];
    f32 var_fa0;
    s32 pad2;
    f32 var_fv0;
    f32 var_fv1;

    sp68 = 0;
    if (arg0->unk104 == 2) {
        bird_802CD0F8(arg0);
        return;
    }
    if (func_802E6B5C() != 4) {
        arg0->unk8 += D_8034F854;
        if (D_80362690->unk0[D_80362690->unk9C].unkC.unk7B == 0) {
            func_80339E1C(arg0);
        }
        if (arg1 == 6) {
            func_802E65AC(&arg0->unk10, &D_80362690->unk0[0].terraId, &sp7C, &sp78, &buttons);
        } else {
            sp7C = demoGetInputs(arg0->controller, INPUT_AXIS_X);
            sp78 = demoGetInputs(arg0->controller, INPUT_AXIS_Y);
            buttons = demoGetButtons(arg0->controller);
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
            arg0->unkE4 = func_80313AF4(0.0f, arg0->unkE4, 3.0f);
            arg0->unkE8 = func_80313AF4(0.0f, arg0->unkE8, 3.0f);
        } else {
            arg0->unkE4 = func_80313AF4(sp7C, arg0->unkE4, 3.0f);
            arg0->unkE8 = func_80313AF4(sp78, arg0->unkE8, 3.0f);
        }
        if (demoButtonPress(arg0->controller, A_BUTTON)) {
            sp68 = 1;
            arg0->unk2DC -= 0.25f;
        }
        if (demoButtonPress(arg0->controller, B_BUTTON)) {
            sp68 = 1;
            arg0->unk2DC += 0.25f;
        }
        arg0->unk2DC = func_80313AF4(0.0f, arg0->unk2DC, 1.0f);
        arg0->unk2D4 += arg0->unk2DC * D_8034F854;
        if (arg0->unk2D4 < 0.f) {
            arg0->unk2D4 = 0.f;
        }
        if (arg0->unk2D4 > 1.5707f) {
            arg0->unk2D4 = 1.5707f;
        }
        if (sp68 != 0) {
            arg0->unk2D0 += 9.0f * D_8034F854;
            if (arg0->unk2D0 > 3.8f) {
                arg0->unk2D0 = 3.8f;
            }
        } else {
            arg0->unk2D0 = func_80313AF4(0.0f, arg0->unk2D0, 0.5f);
            arg0->unk2D4 = func_80313AF4(0.0f, arg0->unk2D4, 0.4f);
        }
        if (arg1 != 6) {
            bird_802CEDF8(arg0);
        }
        bird_802CE190(arg0, arg1);
        if (arg1 != 6) {
            sp4C[0] = arg0->unkD0;
            sp4C[1] = arg0->unk2D0;
            sp4C[2] = arg0->unk2D4;
            sp4C[3] = (f32)arg0->unk2C0;
            sp4C[4] = arg0->unk304;
            sp4C[5] = arg0->unk308;
            func_802E682C(sp4C, ARRAY_COUNT(sp4C), 0);
        } else {
            func_802E6870(sp4C, ARRAY_COUNT(sp4C), NULL);
            arg0->unkD0 = sp4C[0];
            arg0->unk2D0 = sp4C[1];
            arg0->unk2D4 = sp4C[2];
            arg0->unk2C0 = (u8)sp4C[3];
            arg0->unk304 = sp4C[4];
            arg0->unk308 = sp4C[5];
        }
        if (arg1 != 6) {
            arg0->unkD0 = -1.57f;
            if (arg0->unk224 < 25.0f) {
                var_fa0 = (((25.0f - arg0->unk224) * 1.57f) / 25.0f) + -1.57f;
                if ((arg0->unk16C < 4.0f) && (arg0->unk224 < 10.0f)) {
                    arg0->unkD0 = (((4.0f - arg0->unk16C) * 1.57f) / 2.5f) + -1.57f;
                }
                if (var_fa0 < arg0->unkD0) {
                    arg0->unkD0 = arg0->unkD0;
                } else {
                    arg0->unkD0 = var_fa0;
                }
            }
            if (arg0->unkD0 > 0.0f) {
                arg0->unkD0 = 0.0f;
            }
        }
        uvMat4SetIdentity(&arg0->unk90);
        uvMat4RotateAxis(&arg0->unk90, arg0->unkD0, 'x');
        uvMat4Mul(&arg0->unk50, &arg0->unk90, &arg0->unk10);
        uvDobjPosm(arg0->unk0, 0, &arg0->unk50);
        func_803344BC(&arg0->unk10, arg0->unk16C);
        if (arg0->unk224 > 25.0f) {
            arg0->unkD4->unk48 = 0.0125f;
            arg0->unkD4->unk5C = 0.0f;
            arg0->unkD4->unk60 = -3.5f;
            arg0->unkD4->unk64 = 0.5f;
        } else {
            var_fa0 = -arg0->unkD0 / 1.57f;
            var_fv1 = arg0->unk224 / 25.0f;
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
            arg0->unkD4->unk48 = ((1.0f - var_fv0) * 0.15f) + (var_fv0 * 0.0125f);
            arg0->unkD4->unk5C = 0 * var_fv0;

            arg0->unkD4->unk60 = (2.5f * var_fv0) + -6.0f;
            arg0->unkD4->unk64 = (0.4f * var_fv0) + 0.1f;
        }
        if (D_803593E4 == 0) {
            if (buttons & L_CBUTTONS) {
                var_fa0 = 1.5707963f;
            } else if (buttons & R_CBUTTONS) {
                var_fa0 = -1.5707963f;
            } else {
                var_fa0 = 0.0f;
            }
            arg0->unkEC = func_80313AF4(var_fa0, arg0->unkEC, 1.1f);
            if (buttons & D_CBUTTONS) {
                var_fa0 = 1.5707963f;
            } else if (buttons & U_CBUTTONS) {
                var_fa0 = -1.5707963f;
            } else {
                var_fa0 = 0.0f;
            }
            arg0->unkF0 = func_80313AF4(var_fa0, arg0->unkF0, 1.1f);
        } else {
            arg0->unkEC = func_80313AF4(demoGetInputs(arg0->controller, 0) * -1.5707963f, arg0->unkEC, 3.0f);
            arg0->unkF0 = func_80313AF4(demoGetInputs(arg0->controller, 1) * -1.5707963f, arg0->unkF0, 3.0f);
        }
        if (demoButtonPress(arg0->controller, R_TRIG) && (arg1 != 6) && (arg0->unk104 != 1)) {
            D_803593E4 = 0;
            if (arg0->unkD8 == 1) {
                func_8033F758(0x6A, 1.0f, 0.5f, 0.0f);
                arg0->unkD8 = 0;
                arg0->unkDC = 1.0f;
                func_80334454(0x13D, 0x13C);
                arg0->unk290 = 1;
                bird_802CE0A4(arg0);
            } else {
                func_8033F758(0x6A, 1.0f, 0.5f, 0.0f);
                arg0->unkD8 = 1;
                arg0->unkDC = 0.8f;
                func_80334454(0x13D, 0x13C);
                arg0->unk290 = 0;
                bird_802CE0A4(arg0);
            }
            func_802D5884(arg0->unkD4, arg0->unkD8);
            func_802D45C4(arg0->unkD4, arg0->unkDC);
        }
        if (arg1 != 6) {
            arg0->unkD4->unk4 = arg0->unk0;
            arg0->unkD4->unk6 = arg0->unk2;
            arg0->unkD4->unk78 = arg0->unkEC;
            arg0->unkD4->unk7C = arg0->unkF0;
            arg0->unkD4->unk228 = arg0->unk16C;
            uvMat4LocalToWorld(&arg0->unk90, &arg0->unkD4->unk68, &arg0->unk294);
            uvMat4Copy(&arg0->unkD4->unk80, &arg0->unk10);
            if (arg0->unk104 == 1) {
                func_802D5884(arg0->unkD4, 6);
                arg0->unk2 = 2;
                uvDobjState(arg0->unk0, arg0->unk2);
            } else {
                func_802D5884(arg0->unkD4, arg0->unkD8);
            }
            func_802D45C4(arg0->unkD4, arg0->unkDC);
        }
        if ((arg0->unkD8 == 1) && (arg0->unk104 != 1) && (arg1 != 6)) {
            arg0->unk290 = 0;
        } else {
            arg0->unk290 = 1;
        }
        if (arg0->unkD4->unk148 != 0) {
            arg0->unk290 = 1;
        }
        bird_802CE0A4(arg0);
        if (arg1 != 6) {
            sp6C = hudGetState();
            uvMat4Copy(&sp6C->unk28, &arg0->unk10);
            sp6C->renderFlags = HUD_RENDER_BIRDMAN;
            sp6C->att.heading = arg0->unk10.m[3][2];
            sp6C->elapsedTime = arg0->unk8;
            sp6C->unk8C = arg0->unk218.z * 4.0f * 0.7f;
            sp6C->altitude = arg0->unk16C * 0.7f;
            sp6C->altSeaLevel = arg0->unk10.m[3][2] * 0.7f;
            sp6C->speed = arg0->unk224 * 3.6f * 0.7f;
        }
        if ((arg0->unk104 == 1) || (arg0->unk104 == 2)) {
            sp6C->renderFlags = 0;
        }
        func_802E06AC(&arg0->unk10);
        if (arg1 != 6) {
            if (arg0->unk104 == 2) {
                func_802E66DC();
            }
            func_802E65AC(&arg0->unk10, &D_80362690->unk0[0].terraId, &sp7C, &sp78, &buttons);
        }
    }
}

void bird_802CD0F8(VehicleData* arg0) {
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

    if (arg0->unk2F0 == 0) {
        arg0->unk2F0 = 1;
        sp60.x = arg0->unk10.m[3][0];
        sp54.x = arg0->unk400.x;
        sp60.y = arg0->unk10.m[3][1];
        sp54.y = arg0->unk400.y;
        sp60.z = arg0->unk10.m[3][2];
        sp54.z = arg0->unk400.z;
        sp38 = arg0->unk40C;
        sp37 = db_getgnd(&sp54, &sp60, &sp38, &sp3C, &sp40, &sp48);
        if (sp37 != 0) {
            var_a1 = func_802E02EC();
        } else {
            var_a1 = &sp60;
            sp60.z = sp40;
        }
        func_802E05CC(&arg0->unk10, var_a1, &sp48, 1);
        if (func_802E0C30(sp37, sp3C) != 0) {
            arg0->unk15C = 1;
        }
        uvDobjPosm(arg0->unk0, 0, &arg0->unk10);
        uvMat4Copy(&arg0->unkD4->unk80, &arg0->unk10);
        if (arg0->unk15C != 0) {
            snd_play_sfx(0x1A);
            uvEventPost(0x12, 0);
            x = arg0->unk10.m[3][0];
            y = arg0->unk10.m[3][1];
            z = arg0->unk10.m[3][2];
            func_802F8AB8(x, y, z, 1.0f, &arg0->unk218.x);
            arg0->unkD4->unk6 = arg0->unk2 = 0;
            uvDobjState(arg0->unk0, arg0->unk2);
            uvMat4Copy(&arg0->unkD4->unk80, &arg0->unk10);
        } else {
            arg0->unk2 = 2;
            uvDobjState(arg0->unk0, arg0->unk2);
        }
        arg0->unk290 = 1;
        bird_802CE0A4(arg0);
        func_803343D8(0);
    }
    func_802D5884(arg0->unkD4, 3);
    hudGetState()->renderFlags = 0;
    if (arg0->unk15C != 0) {
        arg0->unkD4->unk190 = 12.0f;
    } else {
        arg0->unkD4->unk190 = 6.0f;
    }
    bird_802CEA60(arg0);
}

// called during birdman init to setup pilot specific parameters
void bird_802CD2E8(u8 pilot, VehicleData* arg1) {
    switch (pilot) {
    case PILOT_LARK:
        arg1->unk294.x = 0;
        arg1->unk294.y = -0.1625f;
        arg1->unk294.z = 0.2869f;
        arg1->unk3F4 = 0x13B;
        arg1->unk3F7 = 0x16;
        arg1->unk3F6 = 1;
        arg1->unk3F8 = 2;
        arg1->unk3F9 = 5;
        arg1->unk2F8 = 0xF;
        arg1->unk2F9 = 8;
        arg1->unk2A0 = 0.6f;
        arg1->unk2A4 = 1.0f;
        arg1->unk2B0 = 0.8f;
        arg1->unk2B4 = 0.8f;
        arg1->unk2B8 = 0x44;
        arg1->unk2C0 = 0x45;
        arg1->unk2AC = 1.2f;
        arg1->unk2A8 = 1.2f;
        arg1->unk320.x = 0.0f;
        arg1->unk320.y = 0.021f;
        arg1->unk320.z = 0.675f;
        arg1->unk32C.x = -4.281f;
        arg1->unk32C.y = -0.972f;
        arg1->unk32C.z = 0.596f;
        arg1->unk338.x = 4.277f;
        arg1->unk338.y = -0.972f;
        arg1->unk344.y = 0.0f;
        arg1->unk344.x = 0.0f;
        arg1->unk338.z = 0.596f;
        arg1->unk344.z = -0.745f;
        arg1->unk350 = 7;
        arg1->unk354 = 0.0f;
        arg1->unk358 = -1.426f;
        arg1->unk35C = -0.098f;
        arg1->unk360 = -0.018f;
        arg1->unk364 = 0.125f;
        arg1->unk368 = -1.368f;
        arg1->unk36C = -0.401f;
        arg1->unk370 = -0.084f;
        arg1->unk374 = 0.25f;
        arg1->unk378 = -1.019f;
        arg1->unk37C = -0.815f;
        arg1->unk380 = -0.234f;
        arg1->unk384 = 0.625f;
        arg1->unk388 = -1.271f;
        arg1->unk38C = -0.175f;
        arg1->unk390 = -0.158f;
        arg1->unk394 = 0.75f;
        arg1->unk398 = -1.133f;
        arg1->unk39C = 0.561f;
        arg1->unk3A0 = -0.274f;
        arg1->unk3A4 = 0.875f;
        arg1->unk3A8 = -1.12f;
        arg1->unk3AC = 0.6f;
        arg1->unk3B0 = -0.127f;
        arg1->unk3B4 = 1.0f;
        arg1->unk3B8 = -1.426f;
        arg1->unk3BC = -0.098f;
        arg1->unk3C0 = -0.018f;
        break;
    case PILOT_GOOSE:
        arg1->unk294.x = 0;
        arg1->unk294.y = -0.0994f;
        arg1->unk294.z = 0.2577f;
        arg1->unk3F4 = 0x13E;
        arg1->unk3F7 = 0x16;
        arg1->unk3F6 = 1;
        arg1->unk3F8 = 2;
        arg1->unk3F9 = 5;
        arg1->unk2F8 = 0xF;
        arg1->unk2F9 = 8;
        arg1->unk2A0 = 0.6f;
        arg1->unk2A4 = 1.0f;
        arg1->unk2AC = 1.0f;
        arg1->unk2A8 = 1.0f;
        arg1->unk2B0 = 1.0f;
        arg1->unk2B4 = 1.0f;
        arg1->unk2B8 = 0x46;
        arg1->unk2C0 = 0x47;
        arg1->unk320.x = 0.0f;
        arg1->unk320.y = 0.108f;
        arg1->unk320.z = 0.653f;
        arg1->unk32C.x = -3.724f;
        arg1->unk32C.y = -0.808f;
        arg1->unk32C.z = 0.499f;
        arg1->unk338.x = 3.714f;
        arg1->unk338.y = -0.808f;
        arg1->unk338.z = 0.499f;
        arg1->unk344.y = 0.0f;
        arg1->unk344.x = 0.0f;
        arg1->unk344.z = -1.645f;
        arg1->unk350 = 7;
        arg1->unk354 = 0.0f;
        arg1->unk358 = -1.457f;
        arg1->unk35C = -0.05f;
        arg1->unk360 = 0.491f;
        arg1->unk364 = 0.125f;
        arg1->unk368 = -1.416f;
        arg1->unk36C = -0.426f;
        arg1->unk370 = 0.377f;
        arg1->unk374 = 0.25f;
        arg1->unk378 = -0.864f;
        arg1->unk37C = -1.022f;
        arg1->unk380 = 0.137f;
        arg1->unk384 = 0.625f;
        arg1->unk388 = -1.439f;
        arg1->unk38C = -0.011f;
        arg1->unk390 = 0.486f;
        arg1->unk394 = 0.75f;
        arg1->unk398 = -1.249f;
        arg1->unk39C = 0.762f;
        arg1->unk3A0 = 0.202f;
        arg1->unk3A4 = 0.875f;
        arg1->unk3A8 = -1.152f;
        arg1->unk3AC = 0.767f;
        arg1->unk3B0 = 0.312f;
        arg1->unk3B4 = 1.0f;
        arg1->unk3B8 = -1.457f;
        arg1->unk3BC = -0.05f;
        arg1->unk3C0 = 0.491f;
        break;
    case PILOT_HAWK:
        arg1->unk294.x = 0;
        arg1->unk294.y = -0.07084f;
        arg1->unk294.z = 0.57865f;
        arg1->unk3F4 = 0x13F;
        arg1->unk3F7 = 0x16;
        arg1->unk3F6 = 1;
        arg1->unk3F8 = 2;
        arg1->unk3F9 = 5;
        arg1->unk2F8 = 0xF;
        arg1->unk2F9 = 8;
        arg1->unk2A0 = 0.6f;
        arg1->unk2A4 = 1.0f;
        arg1->unk2B0 = 1.2f;
        arg1->unk2B4 = 1.2f;
        arg1->unk2B8 = 0x48;
        arg1->unk2C0 = 0x49;
        arg1->unk2AC = 0.8f;
        arg1->unk2A8 = 0.8f;
        arg1->unk320.x = 0.0f;
        arg1->unk320.y = 0.108f;
        arg1->unk320.z = 0.627f;
        arg1->unk32C.x = -3.643f;
        arg1->unk32C.y = -0.796f;
        arg1->unk32C.z = 0.476f;
        arg1->unk338.x = 3.643f;
        arg1->unk338.y = -0.796f;
        arg1->unk338.z = 0.476f;
        arg1->unk344.y = 0.0f;
        arg1->unk344.x = 0.0f;
        arg1->unk344.z = -1.228f;
        arg1->unk350 = 7;
        arg1->unk354 = 0.0f;
        arg1->unk358 = -1.826f;
        arg1->unk35C = -0.06f;
        arg1->unk360 = 0.217f;
        arg1->unk364 = 0.125f;
        arg1->unk368 = -1.689f;
        arg1->unk36C = -0.606f;
        arg1->unk370 = 0.158f;
        arg1->unk374 = 0.25f;
        arg1->unk378 = -1.074f;
        arg1->unk37C = -1.247f;
        arg1->unk380 = -0.01f;
        arg1->unk384 = 0.625f;
        arg1->unk388 = -1.804f;
        arg1->unk38C = -0.068f;
        arg1->unk390 = 0.407f;
        arg1->unk394 = 0.75f;
        arg1->unk398 = -1.519f;
        arg1->unk39C = 0.881f;
        arg1->unk3A0 = 0.208f;
        arg1->unk3A4 = 0.875f;
        arg1->unk3A8 = -1.415f;
        arg1->unk3AC = 0.89f;
        arg1->unk3B0 = 0.392f;
        arg1->unk3B8 = -1.826f;
        arg1->unk3BC = -0.06f;
        arg1->unk3B4 = 1.0f;
        arg1->unk3C0 = 0.217f;
        break;
    case PILOT_KIWI:
        arg1->unk294.x = 0;
        arg1->unk294.y = 0.0015f;
        arg1->unk294.z = 0.1942f;
        arg1->unk3F4 = 0x140;
        arg1->unk3F7 = 0x16;
        arg1->unk3F6 = 1;
        arg1->unk3F8 = 2;
        arg1->unk3F9 = 5;
        arg1->unk2F8 = 0xF;
        arg1->unk2F9 = 8;
        arg1->unk2A0 = 0.6f;
        arg1->unk2A4 = 1.0f;
        arg1->unk2B0 = 0.8f;
        arg1->unk2B4 = 0.8f;
        arg1->unk2B8 = 0x4A;
        arg1->unk2C0 = 0x45;
        arg1->unk2AC = 1.2f;
        arg1->unk2A8 = 1.2f;
        arg1->unk320.x = 0.0f;
        arg1->unk320.y = 0.021f;
        arg1->unk320.z = 0.672f;
        arg1->unk32C.x = -4.34f;
        arg1->unk32C.y = -1.029f;
        arg1->unk32C.z = 0.57f;
        arg1->unk338.x = 4.34f;
        arg1->unk338.y = -1.029f;
        arg1->unk344.y = 0.0f;
        arg1->unk344.x = 0.0f;
        arg1->unk338.z = 0.57f;
        arg1->unk344.z = -0.861f;
        arg1->unk350 = 7;
        arg1->unk354 = 0.0f;
        arg1->unk358 = -1.426f;
        arg1->unk35C = -0.098f;
        arg1->unk360 = -0.018f;
        arg1->unk364 = 0.125f;
        arg1->unk368 = -1.368f;
        arg1->unk36C = -0.401f;
        arg1->unk370 = -0.084f;
        arg1->unk374 = 0.25f;
        arg1->unk378 = -1.019f;
        arg1->unk37C = -0.815f;
        arg1->unk380 = -0.234f;
        arg1->unk384 = 0.625f;
        arg1->unk388 = -1.271f;
        arg1->unk38C = -0.175f;
        arg1->unk390 = -0.158f;
        arg1->unk394 = 0.75f;
        arg1->unk398 = -1.133f;
        arg1->unk39C = 0.561f;
        arg1->unk3A0 = -0.274f;
        arg1->unk3A4 = 0.875f;
        arg1->unk3A8 = -1.12f;
        arg1->unk3AC = 0.6f;
        arg1->unk3B0 = -0.127f;
        arg1->unk3B4 = 1.0f;
        arg1->unk3B8 = -1.426f;
        arg1->unk3BC = -0.098f;
        arg1->unk3C0 = -0.018f;
        break;
    case PILOT_IBIS:
        arg1->unk294.x = 0;
        arg1->unk294.y = 0.0024f;
        arg1->unk294.z = 0.3577f;
        arg1->unk3F4 = 0x141;
        arg1->unk3F7 = 0x16;
        arg1->unk3F6 = 1;
        arg1->unk3F8 = 2;
        arg1->unk3F9 = 5;
        arg1->unk2F8 = 0xF;
        arg1->unk2F9 = 8;
        arg1->unk2A0 = 0.6f;
        arg1->unk2A4 = 1.0f;
        arg1->unk2AC = 1.0f;
        arg1->unk2A8 = 1.0f;
        arg1->unk2B0 = 1.0f;
        arg1->unk2B4 = 1.0f;
        arg1->unk2B8 = 0x4B;
        arg1->unk2C0 = 0x47;
        arg1->unk320.x = 0.0f;
        arg1->unk320.y = 0.108f;
        arg1->unk320.z = 0.731f;
        arg1->unk32C.x = -4.225f;
        arg1->unk32C.y = -0.89f;
        arg1->unk32C.z = 0.715f;
        arg1->unk338.x = 4.226f;
        arg1->unk338.y = -0.89f;
        arg1->unk338.z = 0.666f;
        arg1->unk344.y = 0.0f;
        arg1->unk344.x = 0.0f;
        arg1->unk344.z = -1.427f;
        arg1->unk350 = 7;
        arg1->unk354 = 0.0f;
        arg1->unk358 = -1.457f;
        arg1->unk35C = -0.05f;
        arg1->unk360 = 0.491f;
        arg1->unk364 = 0.125f;
        arg1->unk368 = -1.416f;
        arg1->unk36C = -0.426f;
        arg1->unk370 = 0.377f;
        arg1->unk374 = 0.25f;
        arg1->unk378 = -0.864f;
        arg1->unk37C = -1.022f;
        arg1->unk380 = 0.137f;
        arg1->unk384 = 0.625f;
        arg1->unk388 = -1.439f;
        arg1->unk38C = -0.011f;
        arg1->unk390 = 0.486f;
        arg1->unk394 = 0.75f;
        arg1->unk398 = -1.249f;
        arg1->unk39C = 0.762f;
        arg1->unk3A0 = 0.202f;
        arg1->unk3A4 = 0.875f;
        arg1->unk3A8 = -1.152f;
        arg1->unk3AC = 0.767f;
        arg1->unk3B0 = 0.312f;
        arg1->unk3B4 = 1.0f;
        arg1->unk3B8 = -1.457f;
        arg1->unk3BC = -0.05f;
        arg1->unk3C0 = 0.491f;
        break;
    case PILOT_ROBIN:
        arg1->unk294.x = 0;
        arg1->unk294.y = -0.0991f;
        arg1->unk294.z = 0.4056f;
        arg1->unk3F4 = 0x142;
        arg1->unk3F7 = 0x16;
        arg1->unk3F6 = 1;
        arg1->unk3F8 = 2;
        arg1->unk3F9 = 5;
        arg1->unk2F8 = 0xF;
        arg1->unk2F9 = 8;
        arg1->unk2A0 = 0.6f;
        arg1->unk2A4 = 1.0f;
        arg1->unk2AC = 0.8f;
        arg1->unk2A8 = 0.8f;
        arg1->unk2B0 = 1.2f;
        arg1->unk2B8 = 0x4C;
        arg1->unk2C0 = 0x49;
        arg1->unk2B4 = 1.2f;
        arg1->unk320.x = 0.0f;
        arg1->unk320.y = 0.108f;
        arg1->unk320.z = 0.782f;
        arg1->unk32C.x = -4.206f;
        arg1->unk32C.y = -0.202f;
        arg1->unk32C.z = 0.574f;
        arg1->unk338.x = 4.207f;
        arg1->unk338.y = -0.202f;
        arg1->unk344.y = 0.0f;
        arg1->unk344.x = 0.0f;
        arg1->unk338.z = 0.574f;
        arg1->unk344.z = -1.138f;
        arg1->unk350 = 7;
        arg1->unk354 = 0.0f;
        arg1->unk358 = -1.826f;
        arg1->unk35C = -0.06f;
        arg1->unk360 = 0.217f;
        arg1->unk364 = 0.125f;
        arg1->unk368 = -1.689f;
        arg1->unk36C = -0.606f;
        arg1->unk370 = 0.158f;
        arg1->unk374 = 0.25f;
        arg1->unk378 = -1.074f;
        arg1->unk37C = -1.247f;
        arg1->unk380 = -0.01f;
        arg1->unk384 = 0.625f;
        arg1->unk388 = -1.804f;
        arg1->unk38C = -0.068f;
        arg1->unk390 = 0.407f;
        arg1->unk394 = 0.75f;
        arg1->unk398 = -1.519f;
        arg1->unk39C = 0.881f;
        arg1->unk3A0 = 0.208f;
        arg1->unk3A4 = 0.875f;
        arg1->unk3A8 = -1.415f;
        arg1->unk3AC = 0.89f;
        arg1->unk3B0 = 0.392f;
        arg1->unk3B4 = 1.0f;
        arg1->unk3B8 = -1.826f;
        arg1->unk3BC = -0.06f;
        arg1->unk3C0 = 0.217f;
        break;
    default:
        break;
    }
}

// called every frame during birdman
void bird_802CE0A4(VehicleData* arg0) {
    if (arg0->unk290 != 0) {
        arg0->unk2 &= 0xFFFB;
        uvDobjProps(arg0->unk0, 4, arg0->unk3F7, 0);
        if (arg0->unk3F4 == 0x140) {
            uvDobjProps(arg0->unk0, 4, 0x17, 0);
            uvDobjProps(arg0->unk0, 4, 0x18, 0);
        }
    } else {
        arg0->unk2 |= 4;
        uvDobjProps(arg0->unk0, 5, arg0->unk3F7, 0);
        if (arg0->unk3F4 == 0x140) {
            uvDobjProps(arg0->unk0, 5, 0x17, 0);
            uvDobjProps(arg0->unk0, 5, 0x18, 0);
        }
    }
    uvDobjState(arg0->unk0, arg0->unk2);
}
