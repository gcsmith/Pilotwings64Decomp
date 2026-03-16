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
#include "app/snd.h"
#include "app/toys.h"
#include "app/code_66160.h"
#include "app/code_7FED0.h"
#include "app/code_9A960.h"
#include "app/code_B2900.h"

s32 D_8034F380 = 0;
s32 D_8034F384 = 0;

extern Unk803599D0 D_80368880;

void func_802F7224(GyrocopterData* arg0);
void func_802F6DC8(GyrocopterData* arg0, u8 arg1);
s32 func_802F6E74(GyrocopterData* arg0);
s32 func_802F6EE0(GyrocopterData* arg0);
void func_802F7178(GyrocopterData* arg0, Mtx4F* arg1);
void func_802F764C(GyrocopterData* arg0);

void func_802F5A00(void) {
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

void func_802F5AE0(u8 contIdx, u8 pilot, GyrocopterData* arg2, Unk802D3658_Arg0* arg3) {

    uvMemSet(arg2, 0, sizeof(GyrocopterData));
    func_802F7854(pilot, arg2);
    arg2->objId = uvDobjAllocIdx();
    arg2->unk2 = 2;
    arg2->unk5D = 1;
    arg2->unk4 = 0;
    uvDobjModel(arg2->objId, arg2->unk56C);
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
    arg2->unkD1 = 0;
    arg2->unk738 = 0.0f;
    arg2->unk60 = 0.0f;
    arg2->unk64 = 0.0f;
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

    db_getstart(&arg0->unk10, &arg0->unk190, &sp5F, &arg0->unkD8);
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
    uvDobjModel(arg0->objId, arg0->unk56C);
    uvDobjPosm(arg0->objId, 0, &arg0->unk10);
    uvDobjState(arg0->objId, arg0->unk2);
    arg0->unkB0 = 0.0f;
    arg0->unkAC = 0.0f;
    arg0->unkB4 = 0.0f;
    arg0->unk5E = 0;
    arg0->unk60 = 0.0f;
    arg0->unk64 = 0.0f;
    arg0->unk663 = 0;
    arg0->unk664 = 0.0f;
    arg0->unk5D = 1;
    arg0->unk8 = 0.0f;

    for (i = 0; i < 2; i++) {
        arg0->unk688[i].unk48 = 0;
        arg0->unk688[i].unk44 = 0.0f;
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
    uvModelGetProps(arg0->unk56C, 1, &arg0->unk58->unk8, 0);
    func_802D45C4(arg0->unk58, arg0->unk68);
}

void func_802F5F80(GyrocopterData* arg0) {
    GyrocopterData_Unk688* var_s0;
    s32 i;

    uvDobjModel(arg0->objId, MODEL_WORLD);
    arg0->contIdx = 0xFFFF;
    arg0->objId = 0xFFFF;
    func_802F5304(arg0);

    for (i = 0; i < 2; i++) {
        var_s0 = &arg0->unk688[i];
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

void gyrocopterMovementFrame(GyrocopterData* arg0, u8 arg1) {
    s32 pad[2];
    HUDState* sp74;
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

        if (arg1 == 6) {
            func_802E65AC(&arg0->unk10, &D_80362690->unk0[0].terraId, &xAxisInput, &yAxisInput, &buttons);
        } else {
            xAxisInput = demoGetInputs(arg0->contIdx, INPUT_AXIS_X);
            yAxisInput = demoGetInputs(arg0->contIdx, INPUT_AXIS_Y);
            buttons = demoGetButtons(arg0->contIdx);
        }

        if ((arg0->unk8 > 0.0f) || (buttons & A_BUTTON)) {
            arg0->unk8 += D_8034F854;
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
                if (arg0->unkD1 == 0) {
                    arg0->unkD1 = 1;
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
            if (arg0->unkD8 <= 0.0f) {
                arg0->unk5F = 2;
            }
            break;
        case 1:
        case 2:
            if ((arg0->unk5F == 2) && (arg0->unkB0 == 0.0f) && (arg0->unk1A8 < 0.1f)) {
                arg0->unkB0 = 0.0f;
                arg0->unkD1 = 0;
            } else {
                if (buttons & A_BUTTON) {
                    arg0->unkB0 += arg0->unk648 * D_8034F854;
                    if ((arg0->unkD1 == 0) && (arg0->unkD8 > 0.0f)) {
                        arg0->unkD1 = 1;
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

        if (arg1 != 6) {
            func_8030399C(arg0);
        }
        func_802F50CC(arg0);
        func_802F7224(arg0);
        uvDobjPosm(arg0->objId, 0, &arg0->unk10);
        if (arg1 != 6) {
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
        if ((demoButtonPress(arg0->contIdx, R_TRIG) != 0) && (arg1 != 6)) {
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
        if (arg1 != 6) {
            if ((arg0->unkC0 == 2) || (arg0->unkC0 == 3)) {
                func_802D5884(arg0->unk58, 6);
            } else {
                func_802D5884(arg0->unk58, arg0->unk5C);
            }
            func_802D45C4(arg0->unk58, arg0->unk68);
        } else {
            func_802D5884(arg0->unk58, 5);
        }
        if (D_80362690->unk0[D_80362690->unk9C].unkC.unk7B != 0) {
            arg0->unkD8 = 1.0f;
        }
        if ((arg0->unk5C == 1) && (arg0->unkC0 != 2) && (arg1 != 6)) {
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
        if (arg1 != 6) {
            arg0->unk58->unk1A4 = arg0->unk190.y;
            arg0->unk58->unk78 = arg0->unkB8;
            arg0->unk58->unk7C = arg0->unkBC;
            arg0->unk58->unk6 = arg0->unk2;
            arg0->unk58->unk228 = arg0->unkDC;
            uvMat4Copy(&arg0->unk58->unk80, &arg0->unk10);
            sp74 = hudGetState();
            uvMat4Copy(&sp74->unk28, &arg0->unk10);
            sp74->renderFlags = 8;
            if (arg0->unk5E != 0) {
                sp74->renderFlags |= 0x200;
            } else {
                if (sp74->renderFlags & 0x200) {
                    sp74->renderFlags &= ~0x200;
                }
            }
            sp74->unkC6C = arg0->unk60;
            sp74->unkC70 = arg0->unk64;
            sp74->elapsedTime = arg0->unk8;
            sp74->fuel = arg0->unkD8;
            sp74->att.heading = arg0->unk10.m[3][2];
            sp74->unk8C = arg0->unk19C.z * 16.0f * 0.7f;
            sp74->altitude = arg0->unkDC * 0.7f;
            sp74->altSeaLevel = arg0->unk10.m[3][2] * 0.7f;
            sp74->speed = arg0->unk1A8 * 3.6f * 0.7f;
            if (sp74->fuel > 0.0f) {
                sp74->power = arg0->unkB4;
            } else {
                sp74->power -= D_8034F854;
                if (sp74->power < 0.0f) {
                    sp74->power = 0.0f;
                } else if (sp74->power > 1.0f) {
                    sp74->power = 1.0f;
                }
            }
            if (sp74->power < 0.0f) {
                sp74->power = 0.0f;
            }
            if (arg0->unkC1 != 0) {
                hudWarningText(0x148, 1.5f, 8.0f);
                snd_play_sfx(0x69);
            } else {
                if ((arg0->unkD8 <= 0.0f) && (arg0->unkD3 == 0)) {
                    hudWarningText(0x4A, 1.5f, 8.0f);
                    arg0->unkD3 = 1;
                } else if ((arg0->unkD8 < 0.15f) && (arg0->unkD2 == 0)) {
                    hudWarningText(0x17B, 1.5f, 8.0f);
                    arg0->unkD2 = 1;
                } else if ((func_8032C080(NULL) != 0) && (arg0->unkD4 == 0)) {
                    snd_play_sfx(5);
                    hudText_8031D8E0(0x1AA, 1.5f, 8.0f);
                    arg0->unkD4 = 1;
                } else if ((taskGet_80346468() != 0) && (arg0->unkD5 == 0)) {
                    hudText_8031D8E0(0x15D, 1.5f, 8.0f);
                    arg0->unkD5 = 1;
                }
            }
        }

        if ((arg0->unkC0 == 3) || (arg0->unkC0 == 2)) {
            sp74->renderFlags = 0;
        }
        func_803344BC(&arg0->unk10, arg0->unkDC);
        D_8034F380 = buttons;
        func_802E06AC(&arg0->unk10);
        if (arg1 != 6) {
            if (arg0->unkC0 == 3) {
                func_802E66DC();
            }
            func_802E65AC(&arg0->unk10, &D_80362690->unk0[0].terraId, &xAxisInput, &yAxisInput, &buttons);
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
        arg0->unk60 = 0.0f;
        temp_fv1 = arg0->unk58->unk3C * -0.105104235;
        temp_fa0 = (-arg0->unk58->unk3C * arg0->unk58->unk34) / arg0->unk58->unk20;
        arg0->unk64 = (107.0f * temp_fv1) / temp_fa0;
    }
}

s32 func_802F6E74(GyrocopterData* arg0) {
    s32 i;

    if ((D_8034F850 - arg0->unk738) < 0.5f) {
        return -1;
    }

    for (i = 0; i < 2; i++) {
        if (arg0->unk688[i].unk48 == 0) {
            break;
        }
    }

    if (i == 2) {
        return -1;
    }
    return i;
}

s32 func_802F6EE0(GyrocopterData* arg0) {
    GyrocopterData_Unk688* temp_s0;
    s32 temp_v0;

    temp_v0 = func_802F6E74(arg0);
    if (temp_v0 < 0) {
        return 0;
    }
    temp_s0 = &arg0->unk688[temp_v0];
    if (1) {}
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
    uvFxProps(temp_s0->unk4C, 1, 4.0f * D_8034F854, 5, 0.8f, 0.8f, 0.8f, 1.0f, 6, 0.2f, 0.2f, 0.2f, 0.0f, 3, 0.4f, 0.4f, 0.4f, 8, 0x147, 0);
    func_8021A4D8(temp_s0->unk4C, &temp_s0->unk0);
    uvFxProps(temp_s0->unk4E, 1, 8.0f, 3, 14.0f, 14.0f, 14.0f, 5, 1.0f, 0.8f, 0.0f, 1.0f, 0xA, temp_s0->unk0.m[3][0], temp_s0->unk0.m[3][1], temp_s0->unk0.m[3][2], 4, 1.0f, 1.0f, 1.0f, 0);
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
    GyrocopterData_Unk688* var_s0;
    s32 sp100;
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

    for (i = 0; i < 2; i++) {
        var_s0 = &arg0->unk688[i];
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
                        uvFxProps(var_s0->unk4E, 3, 2.0f, 2.0f, 2.0f, 4, 0.0f, 0.0f, 0.0f, 0);
                    }
                }
                if ((var_s0->unk44 + 5.0f) < D_8034F850) {
                    var_s0->unk48 = 3;
                    if (var_s0->unk4E != 0xFF) {
                        uvModelGet(var_s0->unk4E, 0xFF);
                        var_s0->unk4E = 0xFF;
                    }
                } else {
                    temp_v0_2 = func_802F9D28(arg0->objId, arg0->unk2, var_s0->unk0.m[3][0], var_s0->unk0.m[3][1], var_s0->unk0.m[3][2], temp_fs0, temp_fs1, temp_fs2, &sp100, &spFC, &spF8, &spF4);
                    if (temp_v0_2 != -1) {
                        var_s2 = 0;
                        func_802F8BF8(1, temp_v0_2, spF4, sp100, spFC, spF8);
                        var_s0->unk48 = 2;
                        if (temp_v0_2 != 4) {
                            targets_8034473C(spF4, 0);
                            var_s2 = falco_802E51E8(spF4, sp100, spFC, spF8);
                            func_80348418(spF4, sp100, spFC, spF8, 3);
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
    if ((arg0->unkD0 == 0) && (arg0->pad660[2] == 0)) {
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
                smoke_props(arg0->unk96, 8, 0, 0);
            }
        } else {
            if (arg0->unk96 != 0xFF) {
                smoke_props(arg0->unk96, 6, arg0->unk10.m[3][0], arg0->unk10.m[3][1], arg0->unk10.m[3][2], 0);
            }
            uvDobjModel(arg0->objId, arg0->unk56E);
            uvDobjPosm(arg0->objId, 0, &arg0->unk10);
        }
    }
    func_803343D8(0);
    func_802F5910(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_7CF30/func_802F7854.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_7CF30/func_802F88D0.s")
