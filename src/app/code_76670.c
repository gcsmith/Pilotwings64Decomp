#include "common.h"
#include "hang_glider.h"
#include <uv_memory.h>
#include <uv_model.h>
#include "app/demo.h"
#include "app/hud.h"
#include "app/fdr.h"
#include "app/shadow.h"
#include "app/snap.h"
#include "app/snd.h"
#include "app/code_51E30.h"
#include "app/code_66F70.h"

Unk803599D0 D_80367F60;
Unk803599D0 D_80367FB8;

void hangGliderLoadPilot(u8, HangGliderData*);

void hangGliderInit(void) {
    D_80367F60.count = 8;
    D_80367F60.unk4[0].x = 0.0f, D_80367F60.unk4[0].y = 0.0f;
    D_80367F60.unk4[1].x = 0.2f, D_80367F60.unk4[1].y = 0.04f;
    D_80367F60.unk4[2].x = 0.4f, D_80367F60.unk4[2].y = 0.16f;
    D_80367F60.unk4[3].x = 0.6f, D_80367F60.unk4[3].y = 0.36f;
    D_80367F60.unk4[4].x = 0.7f, D_80367F60.unk4[4].y = 0.49f;
    D_80367F60.unk4[5].x = 0.8f, D_80367F60.unk4[5].y = 0.64f;
    D_80367F60.unk4[6].x = 0.9f, D_80367F60.unk4[6].y = 0.81f;
    D_80367F60.unk4[7].x = 1.0f, D_80367F60.unk4[7].y = 1.0f;
    D_80367FB8.count = 4;
    D_80367FB8.unk4[0].x = 0.0f, D_80367FB8.unk4[0].y = 0.0f;
    D_80367FB8.unk4[1].x = 0.2f, D_80367FB8.unk4[1].y = 0.2f;
    D_80367FB8.unk4[2].x = 0.6f, D_80367FB8.unk4[2].y = -0.2f;
    D_80367FB8.unk4[3].x = 1.0f, D_80367FB8.unk4[3].y = 1.0f;
}

void hangGliderLoadLevel(u8 contIdx, u8 pilot, HangGliderData* arg2, Camera* arg3) {
    uvMemSet(arg2, 0, sizeof(HangGliderData));
    hangGliderLoadPilot(pilot, arg2);
    arg2->objId = uvDobjAllocIdx();
    arg2->unk2 = 2;
    uvDobjModel(arg2->objId, arg2->modelId);
    uvDobjPosm(arg2->objId, 0, &arg2->unk10);
    uvDobjState(arg2->objId, arg2->unk2);
    shadow_80334454(MODEL_HG_SHADOW_COLUMN, MODEL_HG_SHADOW);
    shadow_803342F0(1.0f);
    shadow_803342FC(-2.0f);
    shadow_803343D8(1);
    func_802F2190(arg2);
    func_802EE530(arg2);
    hgSoundInit(arg2);
    app_firstfunc(pilot);
    arg2->contIdx = contIdx;
    arg2->unk50 = arg3;
    arg2->unk4 = 0;
}

void func_802EF328(HangGliderData* arg0) {
    uvDobjModel(arg0->objId, MODEL_WORLD);
    arg0->contIdx = -1;
    arg0->objId = -1;
    shadow_80334C70();
}

void hangGliderEnterLeave(HangGliderData* arg0) {
    Vec3F sp44;
    Vec3F sp38;
    u8 sp37;
    s32 sp30;

    db_getstart(&arg0->unk10, &arg0->unk18C, &sp37, NULL);
    if (sp37 != 0) {
        arg0->unk8C = 0;
    } else {
        arg0->unk8C = 1;
    }
    if (arg0->unk8C == 1) {
        sp30 = 1;
        sp44.x = sp38.x = arg0->unk10.m[3][0];
        sp44.y = sp38.y = arg0->unk10.m[3][1];
        sp44.z = arg0->unk10.m[3][2] + 0.5f;
        sp38.z = arg0->unk10.m[3][2] - 0.5f;
        db_getgnd(&sp44, &sp38, &sp30, &arg0->unkFC, &arg0->unkF4, &arg0->unk100);
        arg0->unk10.m[3][2] = arg0->unkF4 - arg0->unk2B8.z;
    }
    arg0->unk2 = 2;
    uvDobjModel(arg0->objId, arg0->modelId);
    uvDobjPosm(arg0->objId, 0, &arg0->unk10);
    uvDobjState(arg0->objId, arg0->unk2);
    arg0->unk80 = 0;
    arg0->unk251 = 0;
    arg0->unk60 = 0.0f;
    arg0->unk64 = 0.0f;
    arg0->unk68 = 0.0f;
    arg0->unk6C = 0.0f;
    arg0->unk70 = 0.0f;
    arg0->unk74 = 0.0f;
    arg0->unk78 = 0.0f;
    arg0->unk7C = 0.0f;
    arg0->unk88 = 0.0f;
    arg0->unk84 = 0.0f;
    arg0->unk254 = 0.0f;
    arg0->unk8 = 0.0f;
    arg0->unk260 = 0.0f;
    arg0->unk258 = 0.0f;
    arg0->unk264 = 0.0f;
    arg0->unk25C = 0.0f;
    func_802F2370(arg0);
    func_802EE530(arg0);
    arg0->unk54 = 0;
    arg0->unk58 = 1.0f;
    arg0->unk50->unk1 = 0;
    arg0->unk50->unk0 = 0x29;
    arg0->unk50->unk4 = arg0->objId;
    arg0->unk50->unk6 = arg0->unk2;
    arg0->unk50->unk48 = 0.23f;
    arg0->unk50->unk4C = 1.0f;
    arg0->unk50->unk5C = 0.f;
    arg0->unk50->unk60 = -6.0f;
    arg0->unk50->unk64 = 0.5f;
    arg0->unk50->unk50 = 0.0f;
    arg0->unk50->unk54 = 1.8f;
    arg0->unk50->unk58 = 18.0f;
    arg0->unk50->unk228 = 0.0f;
    uvModelGetProps(arg0->modelId, 1, &arg0->unk50->unk8, 0);
    func_802D45C4(arg0->unk50, arg0->unk58);
}

void hangGliderMovementFrame(HangGliderData* arg0, u8 gameState) {
    s32 pad;
    HUDState* temp_a2;
    f32 stickX;
    f32 stickY;
    s32 buttons;
    u8 sp5B;
    u8 sp5A;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 sp3C[5];

    if (arg0->unk8C == 3) {
        func_802F041C(arg0);
        return;
    }
    if (fdr_802E6B5C() != 4) {
        arg0->unk8 += D_8034F854;
        shadow_803343D8(1);
        func_80339C8C(arg0);
        if (gameState == GAME_STATE_RESULTS) {
            fdr_802E65AC(&arg0->unk10, &D_80362690->terraId, &stickX, &stickY, &buttons);
        } else {
            stickX = demoGetInputs(arg0->contIdx, INPUT_AXIS_X);
            stickY = demoGetInputs(arg0->contIdx, INPUT_AXIS_Y);
            buttons = demoGetButtons(arg0->contIdx);

            temp_fv0 = func_80313F08(&D_80367F60, ABS_NOEQ(stickX));
            if (stickX >= 0.0f) {
                stickX = temp_fv0;
            } else {
                stickX = -temp_fv0;
            }
            temp_fv0_2 = func_80313F08(&D_80367F60, ABS_NOEQ(stickY));
            if (stickY >= 0.0f) {
                stickY = temp_fv0_2;
            } else {
                stickY = -temp_fv0_2;
            }
        }
        //! @bug uninitialised variable
        if (sp5B) {
            arg0->unk60 = func_80313AF4(0.0f, arg0->unk60, 3.0f);
            arg0->unk64 = func_80313AF4(0.0f, arg0->unk64, 3.0f);
        } else {
            arg0->unk60 = func_80313AF4(stickX, arg0->unk60, 3.0f);
            arg0->unk64 = func_80313AF4(stickY, arg0->unk64, 3.0f);
        }

        if (arg0->unk8C != 2) {
            if (buttons & (A_BUTTON | B_BUTTON)) {
                arg0->unk80 = 1;
            } else {
                arg0->unk80 = 0;
            }
        } else {
            arg0->unk80 = 0;
        }
        if (gameState != GAME_STATE_RESULTS) {
            func_802F24BC(arg0);
        }
        //! @bug uninitialised variable
        if (sp5B == 0) {
            if (buttons & R_CBUTTONS) {
                if (arg0->unk74 > -0.5f) {
                    arg0->unk70 = -0.5f;
                } else {
                    arg0->unk70 = -1.1f;
                }
            } else if (buttons & L_CBUTTONS) {
                if (arg0->unk74 < 0.5f) {
                    arg0->unk70 = 0.5f;
                } else {
                    arg0->unk70 = 1.1f;
                }
            } else {
                if (ABS_NOEQ(arg0->unk74) > 0.5f) {
                    arg0->unk70 = 0.0f;
                }
            }
            if (arg0->unk74 > 0.0f) {
                if (arg0->unk74 < arg0->unk70) {
                    arg0->unk74 += 2.0f * D_8034F854;
                } else {
                    arg0->unk74 -= 3.0f * D_8034F854;
                }

                if (arg0->unk74 < 0.0f) {
                    arg0->unk74 = 0.0f;
                } else if (arg0->unk74 > 1.0f) {
                    arg0->unk74 = 1.0f;
                }
            } else if (arg0->unk74 < 0.0f) {
                if (arg0->unk70 < arg0->unk74) {
                    arg0->unk74 -= 2.0f * D_8034F854;
                } else {
                    arg0->unk74 += 3.0f * D_8034F854;
                }

                if (arg0->unk74 < -1.0f) {
                    arg0->unk74 = -1.0f;
                } else if (arg0->unk74 > 0.0f) {
                    arg0->unk74 = 0.0f;
                }
            } else {
                if (arg0->unk70 != 0.0f) {
                    if (arg0->unk74 < arg0->unk70) {
                        arg0->unk74 += 2.0f * D_8034F854;
                    } else {
                        arg0->unk74 -= 2.0f * D_8034F854;
                    }
                }
            }
            arg0->unk68 = arg0->unk74;
            if (buttons & U_CBUTTONS) {
                if (arg0->unk7C > -0.5f) {
                    arg0->unk78 = -0.5f;
                } else {
                    arg0->unk78 = -1.1f;
                }
            } else if (buttons & D_CBUTTONS) {
                if (arg0->unk7C < 0.5f) {
                    arg0->unk78 = 0.5f;
                } else {
                    arg0->unk78 = 1.1f;
                }
            } else {
                if (ABS_NOEQ(arg0->unk7C) > 0.5f) {
                    arg0->unk78 = 0.0f;
                }
            }
            if (arg0->unk7C > 0.0f) {
                if (arg0->unk7C < arg0->unk78) {
                    arg0->unk7C += 2.0f * D_8034F854;
                } else {
                    arg0->unk7C -= 3.0f * D_8034F854;
                }

                if (arg0->unk7C < 0.0f) {
                    arg0->unk7C = 0.0f;
                } else if (arg0->unk7C > 1.0f) {
                    arg0->unk7C = 1.0f;
                }
            } else if (arg0->unk7C < 0.0f) {
                if (arg0->unk78 < arg0->unk7C) {
                    arg0->unk7C -= 2.0f * D_8034F854;
                } else {
                    arg0->unk7C += 3.0f * D_8034F854;
                }

                if (arg0->unk7C < -1.0f) {
                    arg0->unk7C = -1.0f;
                } else if (arg0->unk7C > 0.0f) {
                    arg0->unk7C = 0.0f;
                }
            } else {
                if (arg0->unk78 != 0.0f) {
                    if (arg0->unk7C < arg0->unk78) {
                        arg0->unk7C += 2.0f * D_8034F854;
                    } else {
                        arg0->unk7C -= 2.0f * D_8034F854;
                    }
                }
            }
            arg0->unk6C = arg0->unk7C;
        } else {
            arg0->unk68 = func_80313AF4(demoGetInputs(arg0->contIdx, INPUT_AXIS_X) * -2.0f, arg0->unk68, 3.0f);
            arg0->unk6C = func_80313AF4(demoGetInputs(arg0->contIdx, INPUT_AXIS_Y) * -1.0f, arg0->unk6C, 3.0f);
        }

        if (arg0->unk80 != 0) {
            if (arg0->unk80 == 0) {
                arg0->unk84 = 0.0f;
            } else {
                arg0->unk84 += 2.0f * D_8034F854;
            }
            arg0->unk88 = func_80313F08(&D_80367FB8, arg0->unk84);

            arg0->unk50->unk50 += 0.250f * D_8034F854;
            if (arg0->unk50->unk50 < 0.0f) {
                arg0->unk50->unk50 = 0.0f;
            } else if (arg0->unk50->unk50 > 0.25f) {
                arg0->unk50->unk50 = 0.25f;
            }
        } else {
            arg0->unk84 = 0.0f;
            arg0->unk88 -= D_8034F854;
            if (arg0->unk88 < 0.0f) {
                arg0->unk88 = 0.0f;
            }
            arg0->unk50->unk50 -= 0.5f * D_8034F854;
            if (arg0->unk50->unk50 < 0.0f) {
                arg0->unk50->unk50 = 0.0f;
            } else if (arg0->unk50->unk50 > 1.0f) {
                arg0->unk50->unk50 = 1.0f;
            }
        }
        if ((demoButtonPress(arg0->contIdx, R_TRIG) != 0) && (gameState != GAME_STATE_RESULTS)) {
            if (arg0->unk54 == 1) {
                sndPlaySfxVolPitchPan(0x6A, 1.0f, 0.5f, 0.0f);
                arg0->unk54 = 0;
                arg0->unk58 = 1;
                shadow_80334454(MODEL_HG_SHADOW_COLUMN, MODEL_HG_SHADOW);
            } else {
                sndPlaySfxVolPitchPan(0x6A, 1.0f, 0.5f, 0.0f);
                arg0->unk54 = 1;
                arg0->unk58 = arg0->unk274;
                shadow_80334454(MODEL_HG_SHADOW, MODEL_HG_SHADOW);
            }
        }
        if (arg0->unk8C == 2) {
            shadow_803343D8(1);
        }
        if (gameState != GAME_STATE_RESULTS) {
            if ((arg0->unk8C == 2) || (arg0->unk8C == 3)) {
                func_802D5884(arg0->unk50, 6);
            } else {
                func_802D5884(arg0->unk50, arg0->unk54);
            }
            func_802D45C4(arg0->unk50, arg0->unk58);
        } else {
            func_802D5884(arg0->unk50, 5);
        }
        if (gameState != GAME_STATE_RESULTS) {
            sp5A = 0;
            if (arg0->unk8C == 0) {
                sp5A += 1;
            }
            if (arg0->unk80 != 0) {
                sp5A += 2;
            }
            sp3C[0] = arg0->unk88;
            sp3C[1] = arg0->unk1B0;
            sp3C[2] = arg0->unk18C.y;
            sp3C[3] = arg0->unkF8;
            sp3C[4] = arg0->unk21C;
            fdr_802E682C(sp3C, ARRAY_COUNT(sp3C), sp5A);
        } else {
            fdr_802E6870(sp3C, ARRAY_COUNT(sp3C), &sp5A);
            arg0->unk8C = 4;
            arg0->unk80 = 0;
            if (sp5A & 1) {
                arg0->unk8C = 0;
            }
            if (sp5A & 2) {
                arg0->unk80++;
            }
            arg0->unk88 = sp3C[0];
            arg0->unk1B0 = sp3C[1];
            arg0->unk18C.y = sp3C[2];
            arg0->unkF8 = sp3C[3];
            arg0->unk21C = (s32)sp3C[4];
        }
        func_802EE640(arg0);
        uvDobjPosm(arg0->objId, 0, &arg0->unk10);
        shadow_803344BC(&arg0->unk10, arg0->unkF8);
        if (gameState != GAME_STATE_RESULTS) {
            if (arg0->unk54 == 1) {
                arg0->unk2 |= 4;
            } else {
                if (arg0->unk2 & 4) {
                    arg0->unk2 &= ~4;
                }
            }
            uvDobjState(arg0->objId, arg0->unk2);
            arg0->unk50->unk1A4 = arg0->unk18C.y;
            arg0->unk50->unk78 = arg0->unk68;
            arg0->unk50->unk7C = arg0->unk6C;
            arg0->unk50->unk4 = arg0->objId;
            arg0->unk50->unk6 = arg0->unk2;
            arg0->unk50->unk68.x = arg0->unk268.x;
            arg0->unk50->unk68.y = arg0->unk268.y;
            arg0->unk50->unk68.z = arg0->unk268.z;
            arg0->unk50->unk74 = arg0->unk278;
            arg0->unk50->unk228 = arg0->unkF8;
            uvMat4Copy(&arg0->unk50->unk80, &arg0->unk10);
            temp_a2 = hudGetState();
            if ((arg0->unk8C == 2) || (arg0->unk8C == 3)) {
                temp_a2->renderFlags = 0;
            } else {
                uvMat4Copy(&temp_a2->unk28, &arg0->unk10);
                temp_a2->renderFlags = 2;
                temp_a2->att.heading = arg0->unk10.m[3][2];
                temp_a2->elapsedTime = arg0->unk8;
                temp_a2->unk8C = arg0->unk1A4.z * 8.0f * 0.7f;
                temp_a2->altitude = arg0->unkF8 * 0.7f;
                temp_a2->altSeaLevel = arg0->unk10.m[3][2] * 0.7f;
                temp_a2->speed = arg0->unk1B0 * 3.6f * 0.7f;
                if (arg0->unk8C == 4) {
                    temp_a2->speed = 0.0f;
                }
                if ((arg0->unk8C == 4) || (arg0->unk8C == 1)) {
                    temp_a2->altitude = 0.0f;
                }
                if ((arg0->unk1B0 < 8) && (arg0->unkE9 == 0) && (arg0->unk80 == 0) && (arg0->unkF8 >= 4.0f) && (arg0->unk8C == 0) &&
                    (temp_a2->unkB40[0] == -1)) {
                    hudWarningText(0x15C, 1.5f, 8.0f);
                } else if ((arg0->unkE9 != 0) && (arg0->unkF8 >= 4.0f) && (arg0->unk8C == 0) && (temp_a2->unkB40[0] == -1)) {
                    hudWarningText(0x157, 1.5f, 8.0f);
                }
            }
        }
        func_802E06AC(&arg0->unk10);
        if (gameState != GAME_STATE_RESULTS) {
            if (arg0->unk8C == 3) {
                fdr_802E66DC();
            }
            fdr_802E65AC(&arg0->unk10, &D_80362690->terraId, &stickX, &stickY, &buttons);
        }
    }
}

void func_802F03C4(HangGliderData* arg0) {
    arg0->unk50->unk1 = 0xFF;
    arg0->unk50->unk20 = -1.0f;
    func_802D5884(arg0->unk50, arg0->unk54);
    func_802D45C4(arg0->unk50, arg0->unk58);
}

void func_802F041C(HangGliderData* arg0) {
    f32 sp6C;
    Vec3F sp60;
    Vec3F sp54;
    Vec3F sp48;
    Vec3F* var_a1;
    f32 sp40;
    s32 sp3C;
    s32 sp38;
    u8 sp37;

    if (arg0->unk250 == 0) {
        sp60.x = arg0->unk10.m[3][0];
        sp54.x = arg0->unk308.x;
        sp60.y = arg0->unk10.m[3][1];
        sp54.y = arg0->unk308.y;
        sp60.z = arg0->unk10.m[3][2];
        sp54.z = arg0->unk308.z;
        sp38 = arg0->unk314;
        sp37 = db_getgnd(&sp54, &sp60, &sp38, &sp3C, &sp40, &sp48);
        if (sp37 != 0) {
            var_a1 = func_802E02EC();
        } else {
            var_a1 = &sp60;
            sp60.z = sp40;
        }
        func_802E05CC(&arg0->unk10, var_a1, &sp48, 2);
        if (func_802E0C30(sp37, sp3C) != 0) {
            arg0->unkE8 = 1;
        }
        if (arg0->unkE8 != 0) {
            uvDobjPosm(arg0->objId, 0, &arg0->unk10);
            uvMat4Copy(&arg0->unk50->unk80, &arg0->unk10);
        } else {
            switch (arg0->modelId) {
            case MODEL_HG_LARK:
                sp6C = 0.878f;
                break;
            case MODEL_HG_GOOSE:
                sp6C = 0.762f;
                break;
            case MODEL_HG_HAWK:
                sp6C = 0.707f;
                break;
            case MODEL_HG_KIWI:
                sp6C = 0.766f;
                break;
            case MODEL_HG_IBIS:
                sp6C = 0.965f;
                break;
            case MODEL_HG_ROBIN:
                sp6C = 0.82f;
                break;
            }
            uvMat4LocalTranslate(&arg0->unk10, 0.0f, 0.0f, sp6C);
            uvDobjModel(arg0->objId, arg0->crashModelId);
            uvDobjPosm(arg0->objId, 0, &arg0->unk10);
            uvMat4Copy(&arg0->unk50->unk80, &arg0->unk10);
        }
    }
    if (arg0->unkE8 != 0) {
        arg0->unk50->unk190 = 12.0f;
    } else {
        arg0->unk50->unk190 = 6.0f;
    }
    func_802D5884(arg0->unk50, 3);
    hudGetState()->renderFlags = 0;
    shadow_803343D8(0);
    func_802EEF0C(arg0);
}

void hangGliderLoadPilot(u8 pilot, HangGliderData* arg1) {
    switch (pilot) {
    case PILOT_LARK:
        arg1->modelId = MODEL_HG_LARK;
        arg1->crashModelId = MODEL_HG_LARK_CRASHED;
        arg1->unk2E4 = 4;
        arg1->unk2E5 = 14;
        arg1->unk2E6 = 15;
        arg1->unk2E7 = 16;
        arg1->unk268.x = 0.0f;
        arg1->unk268.y = -1.0f;
        arg1->unk268.z = 0.01f;
        arg1->unk27C.x = -0.698f;
        arg1->unk27C.y = 0.295f;
        arg1->unk27C.z = -0.921f;
        arg1->unk288.x = 0.695f;
        arg1->unk288.y = 0.295f;
        arg1->unk288.z = -0.921f;
        arg1->unk294.x = 0.0f;
        arg1->unk294.y = 1.674f;
        arg1->unk294.z = 0.398f;
        arg1->unk2A0.x = -4.281f;
        arg1->unk2A0.y = -0.972f;
        arg1->unk2A0.z = 0.596f;
        arg1->unk2AC.x = 4.277f;
        arg1->unk2AC.y = -0.972f;
        arg1->unk2AC.z = 0.596f;
        arg1->unk2B8.x = -0.11f;
        arg1->unk2B8.y = 0.084f;
        arg1->unk2B8.z = -1.641f;
        arg1->unk2C4 = 0.11f;
        arg1->unk2C8 = 0.084f;
        arg1->unk2CC = -1.641f;
        arg1->unk2D0 = 0.0f;
        arg1->unk2D4 = -0.838f;
        arg1->unk2D8 = -0.629f;
        arg1->unk274 = 0.654f;
        arg1->unk278 = -0.2f;
        arg1->unk2DC = 1.7f;
        arg1->unk2E8 = 15;
        arg1->unk2E9 = 12;
        arg1->unk2EA = 13;
        arg1->unk2EB = 11;
        arg1->unk2EC = 14;
        arg1->unk2ED = 16;
        arg1->unk2EE = 17;
        arg1->unk2F0 = 1.0f;
        arg1->unk2FC = 0.8f;
        arg1->unk300 = 0.8f;
        arg1->unk2F4 = 1.2f;
        arg1->unk2F8 = 1.2f;
        arg1->unk304 = 0.7f;
        break;
    case PILOT_GOOSE:
        arg1->modelId = MODEL_HG_GOOSE;
        arg1->crashModelId = MODEL_HG_GOOSE_CRASHED;
        arg1->unk2E4 = 4;
        arg1->unk2E5 = 11;
        arg1->unk2E6 = 12;
        arg1->unk2E7 = 13;
        arg1->unk268.x = 0.0f;
        arg1->unk268.y = -0.845f;
        arg1->unk268.z = 0.005f;
        arg1->unk27C.x = -0.588f;
        arg1->unk27C.y = 0.266f;
        arg1->unk27C.z = -0.791f;
        arg1->unk288.x = 0.595f;
        arg1->unk288.y = 0.266f;
        arg1->unk288.z = -0.791f;
        arg1->unk294.x = 0.004f;
        arg1->unk294.y = 1.213f;
        arg1->unk294.z = 0.321f;
        arg1->unk2A0.x = -3.724f;
        arg1->unk2A0.y = -0.808f;
        arg1->unk2A0.z = 0.499f;
        arg1->unk2AC.x = 3.714f;
        arg1->unk2AC.y = -0.808f;
        arg1->unk2AC.z = 0.499f;
        arg1->unk2B8.x = -0.083f;
        arg1->unk2B8.y = 0.179f;
        arg1->unk2B8.z = -1.753f;
        arg1->unk2C4 = 0.083f;
        arg1->unk2C8 = 0.179f;
        arg1->unk2CC = -1.753f;
        arg1->unk2D0 = 0.0f;
        arg1->unk2D4 = -1.222f;
        arg1->unk2D8 = -0.59f;
        arg1->unk274 = 0.654f;
        arg1->unk278 = -0.2f;
        arg1->unk2DC = 1.7f;
        arg1->unk2E8 = 22;
        arg1->unk2E9 = 19;
        arg1->unk2EA = 20;
        arg1->unk2EB = 18;
        arg1->unk2EC = 21;
        arg1->unk2ED = 23;
        arg1->unk2EE = 24;
        arg1->unk2F0 = 1.0f;
        arg1->unk2F4 = 1.0f;
        arg1->unk2F8 = 1.0f;
        arg1->unk2FC = 1.0f;
        arg1->unk300 = 1.0f;
        arg1->unk304 = 1.0f;
        break;
    case PILOT_HAWK:
        arg1->modelId = MODEL_HG_HAWK;
        arg1->crashModelId = MODEL_HG_HAWK_CRASHED;
        arg1->unk2E4 = 4;
        arg1->unk2E5 = 11;
        arg1->unk2E6 = 12;
        arg1->unk2E7 = 13;
        arg1->unk268.x = 0.0f;
        arg1->unk268.y = -0.96f;
        arg1->unk268.z = 0.032f;
        arg1->unk27C.x = -0.912f;
        arg1->unk27C.y = 0.303f;
        arg1->unk27C.z = -0.823f;
        arg1->unk288.x = 0.899f;
        arg1->unk288.y = 0.303f;
        arg1->unk288.z = -0.823f;
        arg1->unk294.x = 0.0f;
        arg1->unk294.y = 1.456f;
        arg1->unk294.z = 0.297f;
        arg1->unk2A0.x = -3.643f;
        arg1->unk2A0.y = -0.796f;
        arg1->unk2A0.z = 0.476f;
        arg1->unk2AC.x = 3.643f;
        arg1->unk2AC.y = -0.796f;
        arg1->unk2AC.z = 0.476f;
        arg1->unk2B8.x = -0.9f;
        arg1->unk2B8.y = 0.111f;
        arg1->unk2B8.z = -1.502f;
        arg1->unk2C4 = 0.9f;
        arg1->unk2C8 = 0.111f;
        arg1->unk2CC = -1.502f;
        arg1->unk2D0 = 0.0f;
        arg1->unk2D4 = -0.863f;
        arg1->unk2D8 = -0.606f;
        arg1->unk274 = 0.654f;
        arg1->unk278 = -0.2f;
        arg1->unk2DC = 1.7f;
        arg1->unk2E8 = 29;
        arg1->unk2E9 = 26;
        arg1->unk2EA = 27;
        arg1->unk2EB = 25;
        arg1->unk2EC = 28;
        arg1->unk2ED = 30;
        arg1->unk2EE = 31;
        arg1->unk2F0 = 1.0f;
        arg1->unk2F4 = 0.8f;
        arg1->unk2F8 = 0.8f;
        arg1->unk2FC = 1.2f;
        arg1->unk300 = 1.2f;
        arg1->unk304 = 1.2f;
        break;
    case PILOT_KIWI:
        arg1->modelId = MODEL_HG_KIWI;
        arg1->crashModelId = MODEL_HG_KIWI_CRASHED;
        arg1->unk2E4 = 4;
        arg1->unk2E5 = 14;
        arg1->unk2E6 = 15;
        arg1->unk2E7 = 16;
        arg1->unk268.x = 0.0f;
        arg1->unk268.y = -1.005f;
        arg1->unk268.z = -0.02f;
        arg1->unk27C.x = -0.701f;
        arg1->unk27C.y = 0.387f;
        arg1->unk27C.z = -0.942f;
        arg1->unk288.x = 0.701f;
        arg1->unk288.y = 0.387f;
        arg1->unk288.z = -0.942f;
        arg1->unk294.x = 0.0f;
        arg1->unk294.y = 1.311f;
        arg1->unk294.z = 0.276f;
        arg1->unk2A0.x = -4.34f;
        arg1->unk2A0.y = -1.029f;
        arg1->unk2A0.z = 0.57f;
        arg1->unk2AC.x = 4.34f;
        arg1->unk2AC.y = -1.029f;
        arg1->unk2AC.z = 0.57f;
        arg1->unk2B8.x = 0.0f;
        arg1->unk2B8.y = -0.068f;
        arg1->unk2B8.z = -1.567f;
        arg1->unk2C4 = 0.0f;
        arg1->unk2C8 = 0.068f;
        arg1->unk2CC = -1.567f;
        arg1->unk2D0 = 0.0f;
        arg1->unk2D4 = -0.543f;
        arg1->unk2D8 = -0.766f;
        arg1->unk274 = 0.654f;
        arg1->unk278 = -0.2f;
        arg1->unk2DC = 1.7f;
        arg1->unk2E8 = 32;
        arg1->unk2E9 = 35;
        arg1->unk2EA = 36;
        arg1->unk2EB = 33;
        arg1->unk2EC = 34;
        arg1->unk2ED = 37;
        arg1->unk2EE = 38;
        arg1->unk2F0 = 1.0f;
        arg1->unk2FC = 0.8f;
        arg1->unk300 = 0.8f;
        arg1->unk2F4 = 1.2f;
        arg1->unk2F8 = 1.2f;
        arg1->unk304 = 0.7f;
        break;
    case PILOT_IBIS:
        arg1->modelId = MODEL_HG_IBIS;
        arg1->crashModelId = MODEL_HG_IBIS_CRASHED;
        arg1->unk2E4 = 4;
        arg1->unk2E5 = 14;
        arg1->unk2E6 = 15;
        arg1->unk2E7 = 16;
        arg1->unk268.x = 0.0f;
        arg1->unk268.y = -1.07f;
        arg1->unk268.z = 0.04f;
        arg1->unk27C.x = -0.688f;
        arg1->unk27C.y = 0.31f;
        arg1->unk27C.z = -0.887f;
        arg1->unk288.x = 0.688f;
        arg1->unk288.y = 0.31f;
        arg1->unk288.z = -0.887f;
        arg1->unk294.x = 0.0f;
        arg1->unk294.y = 1.723f;
        arg1->unk294.z = 0.325f;
        arg1->unk2A0.x = -4.225f;
        arg1->unk2A0.y = -0.89f;
        arg1->unk2A0.z = 0.715f;
        arg1->unk2AC.x = 4.226f;
        arg1->unk2AC.y = -0.89f;
        arg1->unk2AC.z = 0.666f;
        arg1->unk2B8.x = -0.0f;
        arg1->unk2B8.y = -0.06f;
        arg1->unk2B8.z = -1.683f;
        arg1->unk2C4 = 0.0f;
        arg1->unk2C8 = 0.06f;
        arg1->unk2CC = -1.683f;
        arg1->unk2D0 = 0.0f;
        arg1->unk2D4 = -0.924f;
        arg1->unk2D8 = -0.668f;
        arg1->unk274 = 0.654f;
        arg1->unk278 = -0.2f;
        arg1->unk2DC = 1.7f;
        arg1->unk2E8 = 39;
        arg1->unk2E9 = 42;
        arg1->unk2EA = 43;
        arg1->unk2EB = 40;
        arg1->unk2EC = 41;
        arg1->unk2ED = 44;
        arg1->unk2EE = 45;
        arg1->unk2F0 = 1.0f;
        arg1->unk2F4 = 1.0f;
        arg1->unk2F8 = 1.0f;
        arg1->unk2FC = 1.0f;
        arg1->unk300 = 1.0f;
        arg1->unk304 = 1.0f;
        break;
    case PILOT_ROBIN:
        arg1->modelId = MODEL_HG_ROBIN;
        arg1->crashModelId = MODEL_HG_ROBIN_CRASHED;
        arg1->unk2E4 = 4;
        arg1->unk2E5 = 11;
        arg1->unk2E6 = 12;
        arg1->unk2E7 = 13;
        arg1->unk268.x = 0.0f;
        arg1->unk268.y = -1.005f;
        arg1->unk268.z = -0.083f;
        arg1->unk27C.x = -0.685f;
        arg1->unk27C.y = 0.223f;
        arg1->unk27C.z = -0.986f;
        arg1->unk288.x = 0.685f;
        arg1->unk288.y = 0.223f;
        arg1->unk288.z = -0.986f;
        arg1->unk294.x = 0.001f;
        arg1->unk294.y = 1.662f;
        arg1->unk294.z = 0.23f;
        arg1->unk2A0.x = -4.206f;
        arg1->unk2A0.y = -0.202f;
        arg1->unk2A0.z = 0.574f;
        arg1->unk2AC.x = 4.207f;
        arg1->unk2AC.y = -0.202f;
        arg1->unk2AC.z = 0.574f;
        arg1->unk2B8.x = 0.0f;
        arg1->unk2B8.y = -0.094f;
        arg1->unk2B8.z = -1.578f;
        arg1->unk2C4 = 0.0f;
        arg1->unk2C8 = 0.094f;
        arg1->unk2CC = -1.578f;
        arg1->unk2D0 = 0.0f;
        arg1->unk2D4 = -0.82f;
        arg1->unk2D8 = -0.858f;
        arg1->unk274 = 0.654f;
        arg1->unk278 = -0.2f;
        arg1->unk2DC = 1.7f;
        arg1->unk2E8 = 46;
        arg1->unk2E9 = 49;
        arg1->unk2EA = 50;
        arg1->unk2EB = 47;
        arg1->unk2EC = 48;
        arg1->unk2ED = 51;
        arg1->unk2EE = 52;
        arg1->unk2F0 = 1.0f;
        arg1->unk2F4 = 0.8f;
        arg1->unk2F8 = 0.8f;
        arg1->unk2FC = 1.2f;
        arg1->unk300 = 1.2f;
        arg1->unk304 = 1.2f;
        break;
    default:
        break;
    }
}
