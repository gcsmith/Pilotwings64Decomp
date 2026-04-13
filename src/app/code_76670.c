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

void hangGliderLoadLevel(u8 contIdx, u8 pilot, HangGliderData* hgData, Camera* camera) {
    uvMemSet(hgData, 0, sizeof(HangGliderData));
    hangGliderLoadPilot(pilot, hgData);
    hgData->objId = uvDobjAllocIdx();
    hgData->unk2 = 2;
    uvDobjModel(hgData->objId, hgData->modelId);
    uvDobjPosm(hgData->objId, 0, &hgData->unk10);
    uvDobjState(hgData->objId, hgData->unk2);
    shadow_80334454(MODEL_HG_SHADOW_COLUMN, MODEL_HG_SHADOW);
    shadow_803342F0(1.0f);
    shadow_803342FC(-2.0f);
    shadow_803343D8(1);
    hangGlider_802F2190(hgData);
    func_802EE530(hgData);
    hgSoundInit(hgData);
    app_firstfunc(pilot);
    hgData->contIdx = contIdx;
    hgData->camera = camera;
    hgData->unk4 = 0;
}

void func_802EF328(HangGliderData* hgData) {
    uvDobjModel(hgData->objId, MODEL_WORLD);
    hgData->contIdx = -1;
    hgData->objId = -1;
    shadow_80334C70();
}

void hangGliderEnterLeave(HangGliderData* hgData) {
    Vec3F sp44;
    Vec3F sp38;
    u8 sp37;
    s32 sp30;

    db_getstart(&hgData->unk10, &hgData->unk18C, &sp37, NULL);
    if (sp37 != 0) {
        hgData->unk8C = 0;
    } else {
        hgData->unk8C = 1;
    }
    if (hgData->unk8C == 1) {
        sp30 = 1;
        sp44.x = sp38.x = hgData->unk10.m[3][0];
        sp44.y = sp38.y = hgData->unk10.m[3][1];
        sp44.z = hgData->unk10.m[3][2] + 0.5f;
        sp38.z = hgData->unk10.m[3][2] - 0.5f;
        db_getgnd(&sp44, &sp38, &sp30, &hgData->unkFC, &hgData->unkF4, &hgData->unk100);
        hgData->unk10.m[3][2] = hgData->unkF4 - hgData->unk2B8.z;
    }
    hgData->unk2 = 2;
    uvDobjModel(hgData->objId, hgData->modelId);
    uvDobjPosm(hgData->objId, 0, &hgData->unk10);
    uvDobjState(hgData->objId, hgData->unk2);
    hgData->unk80 = 0;
    hgData->unk251 = 0;
    hgData->unk60 = 0.0f;
    hgData->unk64 = 0.0f;
    hgData->unk68 = 0.0f;
    hgData->unk6C = 0.0f;
    hgData->unk70 = 0.0f;
    hgData->unk74 = 0.0f;
    hgData->unk78 = 0.0f;
    hgData->unk7C = 0.0f;
    hgData->unk88 = 0.0f;
    hgData->unk84 = 0.0f;
    hgData->unk254 = 0.0f;
    hgData->unk8 = 0.0f;
    hgData->unk260 = 0.0f;
    hgData->unk258 = 0.0f;
    hgData->unk264 = 0.0f;
    hgData->unk25C = 0.0f;
    hangGlider_802F2370(hgData);
    func_802EE530(hgData);
    hgData->unk54 = 0;
    hgData->unk58 = 1.0f;
    hgData->camera->unk1 = 0;
    hgData->camera->unk0 = 0x29;
    hgData->camera->unk4 = hgData->objId;
    hgData->camera->unk6 = hgData->unk2;
    hgData->camera->unk48 = 0.23f;
    hgData->camera->unk4C = 1.0f;
    hgData->camera->unk5C = 0.f;
    hgData->camera->unk60 = -6.0f;
    hgData->camera->unk64 = 0.5f;
    hgData->camera->unk50 = 0.0f;
    hgData->camera->unk54 = 1.8f;
    hgData->camera->unk58 = 18.0f;
    hgData->camera->unk228 = 0.0f;
    uvModelGetProps(hgData->modelId, MODEL_PROP_UNK1(&hgData->camera->unk8), MODEL_PROP_END);
    func_802D45C4(hgData->camera, hgData->unk58);
}

void hangGliderMovementFrame(HangGliderData* hgData, u8 gameState) {
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

    if (hgData->unk8C == 3) {
        func_802F041C(hgData);
        return;
    }
    if (fdr_802E6B5C() != 4) {
        hgData->unk8 += D_8034F854;
        shadow_803343D8(1);
        func_80339C8C(hgData);
        if (gameState == GAME_STATE_RESULTS) {
            fdr_802E65AC(&hgData->unk10, &D_80362690->terraId, &stickX, &stickY, &buttons);
        } else {
            stickX = demoGetInputs(hgData->contIdx, INPUT_AXIS_X);
            stickY = demoGetInputs(hgData->contIdx, INPUT_AXIS_Y);
            buttons = demoGetButtons(hgData->contIdx);

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
            hgData->unk60 = func_80313AF4(0.0f, hgData->unk60, 3.0f);
            hgData->unk64 = func_80313AF4(0.0f, hgData->unk64, 3.0f);
        } else {
            hgData->unk60 = func_80313AF4(stickX, hgData->unk60, 3.0f);
            hgData->unk64 = func_80313AF4(stickY, hgData->unk64, 3.0f);
        }

        if (hgData->unk8C != 2) {
            if (buttons & (A_BUTTON | B_BUTTON)) {
                hgData->unk80 = 1;
            } else {
                hgData->unk80 = 0;
            }
        } else {
            hgData->unk80 = 0;
        }
        if (gameState != GAME_STATE_RESULTS) {
            hangGlider_802F24BC(hgData);
        }
        //! @bug uninitialised variable
        if (sp5B == 0) {
            if (buttons & R_CBUTTONS) {
                if (hgData->unk74 > -0.5f) {
                    hgData->unk70 = -0.5f;
                } else {
                    hgData->unk70 = -1.1f;
                }
            } else if (buttons & L_CBUTTONS) {
                if (hgData->unk74 < 0.5f) {
                    hgData->unk70 = 0.5f;
                } else {
                    hgData->unk70 = 1.1f;
                }
            } else {
                if (ABS_NOEQ(hgData->unk74) > 0.5f) {
                    hgData->unk70 = 0.0f;
                }
            }
            if (hgData->unk74 > 0.0f) {
                if (hgData->unk74 < hgData->unk70) {
                    hgData->unk74 += 2.0f * D_8034F854;
                } else {
                    hgData->unk74 -= 3.0f * D_8034F854;
                }

                if (hgData->unk74 < 0.0f) {
                    hgData->unk74 = 0.0f;
                } else if (hgData->unk74 > 1.0f) {
                    hgData->unk74 = 1.0f;
                }
            } else if (hgData->unk74 < 0.0f) {
                if (hgData->unk70 < hgData->unk74) {
                    hgData->unk74 -= 2.0f * D_8034F854;
                } else {
                    hgData->unk74 += 3.0f * D_8034F854;
                }

                if (hgData->unk74 < -1.0f) {
                    hgData->unk74 = -1.0f;
                } else if (hgData->unk74 > 0.0f) {
                    hgData->unk74 = 0.0f;
                }
            } else {
                if (hgData->unk70 != 0.0f) {
                    if (hgData->unk74 < hgData->unk70) {
                        hgData->unk74 += 2.0f * D_8034F854;
                    } else {
                        hgData->unk74 -= 2.0f * D_8034F854;
                    }
                }
            }
            hgData->unk68 = hgData->unk74;
            if (buttons & U_CBUTTONS) {
                if (hgData->unk7C > -0.5f) {
                    hgData->unk78 = -0.5f;
                } else {
                    hgData->unk78 = -1.1f;
                }
            } else if (buttons & D_CBUTTONS) {
                if (hgData->unk7C < 0.5f) {
                    hgData->unk78 = 0.5f;
                } else {
                    hgData->unk78 = 1.1f;
                }
            } else {
                if (ABS_NOEQ(hgData->unk7C) > 0.5f) {
                    hgData->unk78 = 0.0f;
                }
            }
            if (hgData->unk7C > 0.0f) {
                if (hgData->unk7C < hgData->unk78) {
                    hgData->unk7C += 2.0f * D_8034F854;
                } else {
                    hgData->unk7C -= 3.0f * D_8034F854;
                }

                if (hgData->unk7C < 0.0f) {
                    hgData->unk7C = 0.0f;
                } else if (hgData->unk7C > 1.0f) {
                    hgData->unk7C = 1.0f;
                }
            } else if (hgData->unk7C < 0.0f) {
                if (hgData->unk78 < hgData->unk7C) {
                    hgData->unk7C -= 2.0f * D_8034F854;
                } else {
                    hgData->unk7C += 3.0f * D_8034F854;
                }

                if (hgData->unk7C < -1.0f) {
                    hgData->unk7C = -1.0f;
                } else if (hgData->unk7C > 0.0f) {
                    hgData->unk7C = 0.0f;
                }
            } else {
                if (hgData->unk78 != 0.0f) {
                    if (hgData->unk7C < hgData->unk78) {
                        hgData->unk7C += 2.0f * D_8034F854;
                    } else {
                        hgData->unk7C -= 2.0f * D_8034F854;
                    }
                }
            }
            hgData->unk6C = hgData->unk7C;
        } else {
            hgData->unk68 = func_80313AF4(demoGetInputs(hgData->contIdx, INPUT_AXIS_X) * -2.0f, hgData->unk68, 3.0f);
            hgData->unk6C = func_80313AF4(demoGetInputs(hgData->contIdx, INPUT_AXIS_Y) * -1.0f, hgData->unk6C, 3.0f);
        }

        if (hgData->unk80 != 0) {
            if (hgData->unk80 == 0) {
                hgData->unk84 = 0.0f;
            } else {
                hgData->unk84 += 2.0f * D_8034F854;
            }
            hgData->unk88 = func_80313F08(&D_80367FB8, hgData->unk84);

            hgData->camera->unk50 += 0.250f * D_8034F854;
            if (hgData->camera->unk50 < 0.0f) {
                hgData->camera->unk50 = 0.0f;
            } else if (hgData->camera->unk50 > 0.25f) {
                hgData->camera->unk50 = 0.25f;
            }
        } else {
            hgData->unk84 = 0.0f;
            hgData->unk88 -= D_8034F854;
            if (hgData->unk88 < 0.0f) {
                hgData->unk88 = 0.0f;
            }
            hgData->camera->unk50 -= 0.5f * D_8034F854;
            if (hgData->camera->unk50 < 0.0f) {
                hgData->camera->unk50 = 0.0f;
            } else if (hgData->camera->unk50 > 1.0f) {
                hgData->camera->unk50 = 1.0f;
            }
        }
        if ((demoButtonPress(hgData->contIdx, R_TRIG) != 0) && (gameState != GAME_STATE_RESULTS)) {
            if (hgData->unk54 == 1) {
                sndPlaySfxVolPitchPan(0x6A, 1.0f, 0.5f, 0.0f);
                hgData->unk54 = 0;
                hgData->unk58 = 1;
                shadow_80334454(MODEL_HG_SHADOW_COLUMN, MODEL_HG_SHADOW);
            } else {
                sndPlaySfxVolPitchPan(0x6A, 1.0f, 0.5f, 0.0f);
                hgData->unk54 = 1;
                hgData->unk58 = hgData->unk274;
                shadow_80334454(MODEL_HG_SHADOW, MODEL_HG_SHADOW);
            }
        }
        if (hgData->unk8C == 2) {
            shadow_803343D8(1);
        }
        if (gameState != GAME_STATE_RESULTS) {
            if ((hgData->unk8C == 2) || (hgData->unk8C == 3)) {
                func_802D5884(hgData->camera, 6);
            } else {
                func_802D5884(hgData->camera, hgData->unk54);
            }
            func_802D45C4(hgData->camera, hgData->unk58);
        } else {
            func_802D5884(hgData->camera, 5);
        }
        if (gameState != GAME_STATE_RESULTS) {
            sp5A = 0;
            if (hgData->unk8C == 0) {
                sp5A += 1;
            }
            if (hgData->unk80 != 0) {
                sp5A += 2;
            }
            sp3C[0] = hgData->unk88;
            sp3C[1] = hgData->unk1B0;
            sp3C[2] = hgData->unk18C.y;
            sp3C[3] = hgData->unkF8;
            sp3C[4] = hgData->unk21C;
            fdr_802E682C(sp3C, ARRAY_COUNT(sp3C), sp5A);
        } else {
            fdr_802E6870(sp3C, ARRAY_COUNT(sp3C), &sp5A);
            hgData->unk8C = 4;
            hgData->unk80 = 0;
            if (sp5A & 1) {
                hgData->unk8C = 0;
            }
            if (sp5A & 2) {
                hgData->unk80++;
            }
            hgData->unk88 = sp3C[0];
            hgData->unk1B0 = sp3C[1];
            hgData->unk18C.y = sp3C[2];
            hgData->unkF8 = sp3C[3];
            hgData->unk21C = (s32)sp3C[4];
        }
        func_802EE640(hgData);
        uvDobjPosm(hgData->objId, 0, &hgData->unk10);
        shadow_803344BC(&hgData->unk10, hgData->unkF8);
        if (gameState != GAME_STATE_RESULTS) {
            if (hgData->unk54 == 1) {
                hgData->unk2 |= 4;
            } else {
                if (hgData->unk2 & 4) {
                    hgData->unk2 &= ~4;
                }
            }
            uvDobjState(hgData->objId, hgData->unk2);
            hgData->camera->unk1A4 = hgData->unk18C.y;
            hgData->camera->unk78 = hgData->unk68;
            hgData->camera->unk7C = hgData->unk6C;
            hgData->camera->unk4 = hgData->objId;
            hgData->camera->unk6 = hgData->unk2;
            hgData->camera->unk68.x = hgData->unk268.x;
            hgData->camera->unk68.y = hgData->unk268.y;
            hgData->camera->unk68.z = hgData->unk268.z;
            hgData->camera->unk74 = hgData->unk278;
            hgData->camera->unk228 = hgData->unkF8;
            uvMat4Copy(&hgData->camera->unk80, &hgData->unk10);
            temp_a2 = hudGetState();
            if ((hgData->unk8C == 2) || (hgData->unk8C == 3)) {
                temp_a2->renderFlags = 0;
            } else {
                uvMat4Copy(&temp_a2->unk28, &hgData->unk10);
                temp_a2->renderFlags = 2;
                temp_a2->att.heading = hgData->unk10.m[3][2];
                temp_a2->elapsedTime = hgData->unk8;
                temp_a2->unk8C = hgData->unk1A4.z * 8.0f * 0.7f;
                temp_a2->altitude = hgData->unkF8 * 0.7f;
                temp_a2->altSeaLevel = hgData->unk10.m[3][2] * 0.7f;
                temp_a2->speed = hgData->unk1B0 * 3.6f * 0.7f;
                if (hgData->unk8C == 4) {
                    temp_a2->speed = 0.0f;
                }
                if ((hgData->unk8C == 4) || (hgData->unk8C == 1)) {
                    temp_a2->altitude = 0.0f;
                }
                if ((hgData->unk1B0 < 8) && (hgData->unkE9 == 0) && (hgData->unk80 == 0) && (hgData->unkF8 >= 4.0f) && (hgData->unk8C == 0) &&
                    (temp_a2->unkB40[0] == -1)) {
                    hudWarningText(0x15C, 1.5f, 8.0f);
                } else if ((hgData->unkE9 != 0) && (hgData->unkF8 >= 4.0f) && (hgData->unk8C == 0) && (temp_a2->unkB40[0] == -1)) {
                    hudWarningText(0x157, 1.5f, 8.0f);
                }
            }
        }
        func_802E06AC(&hgData->unk10);
        if (gameState != GAME_STATE_RESULTS) {
            if (hgData->unk8C == 3) {
                fdr_802E66DC();
            }
            fdr_802E65AC(&hgData->unk10, &D_80362690->terraId, &stickX, &stickY, &buttons);
        }
    }
}

void func_802F03C4(HangGliderData* hgData) {
    hgData->camera->unk1 = 0xFF;
    hgData->camera->unk20 = -1.0f;
    func_802D5884(hgData->camera, hgData->unk54);
    func_802D45C4(hgData->camera, hgData->unk58);
}

void func_802F041C(HangGliderData* hgData) {
    f32 sp6C;
    Vec3F sp60;
    Vec3F sp54;
    Vec3F sp48;
    Vec3F* var_a1;
    f32 sp40;
    s32 sp3C;
    s32 sp38;
    u8 sp37;

    if (hgData->unk250 == 0) {
        sp60.x = hgData->unk10.m[3][0];
        sp54.x = hgData->unk308.x;
        sp60.y = hgData->unk10.m[3][1];
        sp54.y = hgData->unk308.y;
        sp60.z = hgData->unk10.m[3][2];
        sp54.z = hgData->unk308.z;
        sp38 = hgData->unk314;
        sp37 = db_getgnd(&sp54, &sp60, &sp38, &sp3C, &sp40, &sp48);
        if (sp37 != 0) {
            var_a1 = func_802E02EC();
        } else {
            var_a1 = &sp60;
            sp60.z = sp40;
        }
        func_802E05CC(&hgData->unk10, var_a1, &sp48, 2);
        if (func_802E0C30(sp37, sp3C) != 0) {
            hgData->unkE8 = 1;
        }
        if (hgData->unkE8 != 0) {
            uvDobjPosm(hgData->objId, 0, &hgData->unk10);
            uvMat4Copy(&hgData->camera->unk80, &hgData->unk10);
        } else {
            switch (hgData->modelId) {
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
            uvMat4LocalTranslate(&hgData->unk10, 0.0f, 0.0f, sp6C);
            uvDobjModel(hgData->objId, hgData->crashModelId);
            uvDobjPosm(hgData->objId, 0, &hgData->unk10);
            uvMat4Copy(&hgData->camera->unk80, &hgData->unk10);
        }
    }
    if (hgData->unkE8 != 0) {
        hgData->camera->unk190 = 12.0f;
    } else {
        hgData->camera->unk190 = 6.0f;
    }
    func_802D5884(hgData->camera, 3);
    hudGetState()->renderFlags = 0;
    shadow_803343D8(0);
    func_802EEF0C(hgData);
}

void hangGliderLoadPilot(u8 pilot, HangGliderData* hgData) {
    switch (pilot) {
    case PILOT_LARK:
        hgData->modelId = MODEL_HG_LARK;
        hgData->crashModelId = MODEL_HG_LARK_CRASHED;
        hgData->unk2E4 = 4;
        hgData->unk2E5 = 14;
        hgData->unk2E6 = 15;
        hgData->unk2E7 = 16;
        hgData->unk268.x = 0.0f;
        hgData->unk268.y = -1.0f;
        hgData->unk268.z = 0.01f;
        hgData->unk27C.x = -0.698f;
        hgData->unk27C.y = 0.295f;
        hgData->unk27C.z = -0.921f;
        hgData->unk288.x = 0.695f;
        hgData->unk288.y = 0.295f;
        hgData->unk288.z = -0.921f;
        hgData->unk294.x = 0.0f;
        hgData->unk294.y = 1.674f;
        hgData->unk294.z = 0.398f;
        hgData->unk2A0.x = -4.281f;
        hgData->unk2A0.y = -0.972f;
        hgData->unk2A0.z = 0.596f;
        hgData->unk2AC.x = 4.277f;
        hgData->unk2AC.y = -0.972f;
        hgData->unk2AC.z = 0.596f;
        hgData->unk2B8.x = -0.11f;
        hgData->unk2B8.y = 0.084f;
        hgData->unk2B8.z = -1.641f;
        hgData->unk2C4 = 0.11f;
        hgData->unk2C8 = 0.084f;
        hgData->unk2CC = -1.641f;
        hgData->unk2D0 = 0.0f;
        hgData->unk2D4 = -0.838f;
        hgData->unk2D8 = -0.629f;
        hgData->unk274 = 0.654f;
        hgData->unk278 = -0.2f;
        hgData->unk2DC = 1.7f;
        hgData->unk2E8 = 15;
        hgData->unk2E9 = 12;
        hgData->unk2EA = 13;
        hgData->unk2EB = 11;
        hgData->unk2EC = 14;
        hgData->unk2ED = 16;
        hgData->unk2EE = 17;
        hgData->unk2F0 = 1.0f;
        hgData->unk2FC = 0.8f;
        hgData->unk300 = 0.8f;
        hgData->unk2F4 = 1.2f;
        hgData->unk2F8 = 1.2f;
        hgData->unk304 = 0.7f;
        break;
    case PILOT_GOOSE:
        hgData->modelId = MODEL_HG_GOOSE;
        hgData->crashModelId = MODEL_HG_GOOSE_CRASHED;
        hgData->unk2E4 = 4;
        hgData->unk2E5 = 11;
        hgData->unk2E6 = 12;
        hgData->unk2E7 = 13;
        hgData->unk268.x = 0.0f;
        hgData->unk268.y = -0.845f;
        hgData->unk268.z = 0.005f;
        hgData->unk27C.x = -0.588f;
        hgData->unk27C.y = 0.266f;
        hgData->unk27C.z = -0.791f;
        hgData->unk288.x = 0.595f;
        hgData->unk288.y = 0.266f;
        hgData->unk288.z = -0.791f;
        hgData->unk294.x = 0.004f;
        hgData->unk294.y = 1.213f;
        hgData->unk294.z = 0.321f;
        hgData->unk2A0.x = -3.724f;
        hgData->unk2A0.y = -0.808f;
        hgData->unk2A0.z = 0.499f;
        hgData->unk2AC.x = 3.714f;
        hgData->unk2AC.y = -0.808f;
        hgData->unk2AC.z = 0.499f;
        hgData->unk2B8.x = -0.083f;
        hgData->unk2B8.y = 0.179f;
        hgData->unk2B8.z = -1.753f;
        hgData->unk2C4 = 0.083f;
        hgData->unk2C8 = 0.179f;
        hgData->unk2CC = -1.753f;
        hgData->unk2D0 = 0.0f;
        hgData->unk2D4 = -1.222f;
        hgData->unk2D8 = -0.59f;
        hgData->unk274 = 0.654f;
        hgData->unk278 = -0.2f;
        hgData->unk2DC = 1.7f;
        hgData->unk2E8 = 22;
        hgData->unk2E9 = 19;
        hgData->unk2EA = 20;
        hgData->unk2EB = 18;
        hgData->unk2EC = 21;
        hgData->unk2ED = 23;
        hgData->unk2EE = 24;
        hgData->unk2F0 = 1.0f;
        hgData->unk2F4 = 1.0f;
        hgData->unk2F8 = 1.0f;
        hgData->unk2FC = 1.0f;
        hgData->unk300 = 1.0f;
        hgData->unk304 = 1.0f;
        break;
    case PILOT_HAWK:
        hgData->modelId = MODEL_HG_HAWK;
        hgData->crashModelId = MODEL_HG_HAWK_CRASHED;
        hgData->unk2E4 = 4;
        hgData->unk2E5 = 11;
        hgData->unk2E6 = 12;
        hgData->unk2E7 = 13;
        hgData->unk268.x = 0.0f;
        hgData->unk268.y = -0.96f;
        hgData->unk268.z = 0.032f;
        hgData->unk27C.x = -0.912f;
        hgData->unk27C.y = 0.303f;
        hgData->unk27C.z = -0.823f;
        hgData->unk288.x = 0.899f;
        hgData->unk288.y = 0.303f;
        hgData->unk288.z = -0.823f;
        hgData->unk294.x = 0.0f;
        hgData->unk294.y = 1.456f;
        hgData->unk294.z = 0.297f;
        hgData->unk2A0.x = -3.643f;
        hgData->unk2A0.y = -0.796f;
        hgData->unk2A0.z = 0.476f;
        hgData->unk2AC.x = 3.643f;
        hgData->unk2AC.y = -0.796f;
        hgData->unk2AC.z = 0.476f;
        hgData->unk2B8.x = -0.9f;
        hgData->unk2B8.y = 0.111f;
        hgData->unk2B8.z = -1.502f;
        hgData->unk2C4 = 0.9f;
        hgData->unk2C8 = 0.111f;
        hgData->unk2CC = -1.502f;
        hgData->unk2D0 = 0.0f;
        hgData->unk2D4 = -0.863f;
        hgData->unk2D8 = -0.606f;
        hgData->unk274 = 0.654f;
        hgData->unk278 = -0.2f;
        hgData->unk2DC = 1.7f;
        hgData->unk2E8 = 29;
        hgData->unk2E9 = 26;
        hgData->unk2EA = 27;
        hgData->unk2EB = 25;
        hgData->unk2EC = 28;
        hgData->unk2ED = 30;
        hgData->unk2EE = 31;
        hgData->unk2F0 = 1.0f;
        hgData->unk2F4 = 0.8f;
        hgData->unk2F8 = 0.8f;
        hgData->unk2FC = 1.2f;
        hgData->unk300 = 1.2f;
        hgData->unk304 = 1.2f;
        break;
    case PILOT_KIWI:
        hgData->modelId = MODEL_HG_KIWI;
        hgData->crashModelId = MODEL_HG_KIWI_CRASHED;
        hgData->unk2E4 = 4;
        hgData->unk2E5 = 14;
        hgData->unk2E6 = 15;
        hgData->unk2E7 = 16;
        hgData->unk268.x = 0.0f;
        hgData->unk268.y = -1.005f;
        hgData->unk268.z = -0.02f;
        hgData->unk27C.x = -0.701f;
        hgData->unk27C.y = 0.387f;
        hgData->unk27C.z = -0.942f;
        hgData->unk288.x = 0.701f;
        hgData->unk288.y = 0.387f;
        hgData->unk288.z = -0.942f;
        hgData->unk294.x = 0.0f;
        hgData->unk294.y = 1.311f;
        hgData->unk294.z = 0.276f;
        hgData->unk2A0.x = -4.34f;
        hgData->unk2A0.y = -1.029f;
        hgData->unk2A0.z = 0.57f;
        hgData->unk2AC.x = 4.34f;
        hgData->unk2AC.y = -1.029f;
        hgData->unk2AC.z = 0.57f;
        hgData->unk2B8.x = 0.0f;
        hgData->unk2B8.y = -0.068f;
        hgData->unk2B8.z = -1.567f;
        hgData->unk2C4 = 0.0f;
        hgData->unk2C8 = 0.068f;
        hgData->unk2CC = -1.567f;
        hgData->unk2D0 = 0.0f;
        hgData->unk2D4 = -0.543f;
        hgData->unk2D8 = -0.766f;
        hgData->unk274 = 0.654f;
        hgData->unk278 = -0.2f;
        hgData->unk2DC = 1.7f;
        hgData->unk2E8 = 32;
        hgData->unk2E9 = 35;
        hgData->unk2EA = 36;
        hgData->unk2EB = 33;
        hgData->unk2EC = 34;
        hgData->unk2ED = 37;
        hgData->unk2EE = 38;
        hgData->unk2F0 = 1.0f;
        hgData->unk2FC = 0.8f;
        hgData->unk300 = 0.8f;
        hgData->unk2F4 = 1.2f;
        hgData->unk2F8 = 1.2f;
        hgData->unk304 = 0.7f;
        break;
    case PILOT_IBIS:
        hgData->modelId = MODEL_HG_IBIS;
        hgData->crashModelId = MODEL_HG_IBIS_CRASHED;
        hgData->unk2E4 = 4;
        hgData->unk2E5 = 14;
        hgData->unk2E6 = 15;
        hgData->unk2E7 = 16;
        hgData->unk268.x = 0.0f;
        hgData->unk268.y = -1.07f;
        hgData->unk268.z = 0.04f;
        hgData->unk27C.x = -0.688f;
        hgData->unk27C.y = 0.31f;
        hgData->unk27C.z = -0.887f;
        hgData->unk288.x = 0.688f;
        hgData->unk288.y = 0.31f;
        hgData->unk288.z = -0.887f;
        hgData->unk294.x = 0.0f;
        hgData->unk294.y = 1.723f;
        hgData->unk294.z = 0.325f;
        hgData->unk2A0.x = -4.225f;
        hgData->unk2A0.y = -0.89f;
        hgData->unk2A0.z = 0.715f;
        hgData->unk2AC.x = 4.226f;
        hgData->unk2AC.y = -0.89f;
        hgData->unk2AC.z = 0.666f;
        hgData->unk2B8.x = -0.0f;
        hgData->unk2B8.y = -0.06f;
        hgData->unk2B8.z = -1.683f;
        hgData->unk2C4 = 0.0f;
        hgData->unk2C8 = 0.06f;
        hgData->unk2CC = -1.683f;
        hgData->unk2D0 = 0.0f;
        hgData->unk2D4 = -0.924f;
        hgData->unk2D8 = -0.668f;
        hgData->unk274 = 0.654f;
        hgData->unk278 = -0.2f;
        hgData->unk2DC = 1.7f;
        hgData->unk2E8 = 39;
        hgData->unk2E9 = 42;
        hgData->unk2EA = 43;
        hgData->unk2EB = 40;
        hgData->unk2EC = 41;
        hgData->unk2ED = 44;
        hgData->unk2EE = 45;
        hgData->unk2F0 = 1.0f;
        hgData->unk2F4 = 1.0f;
        hgData->unk2F8 = 1.0f;
        hgData->unk2FC = 1.0f;
        hgData->unk300 = 1.0f;
        hgData->unk304 = 1.0f;
        break;
    case PILOT_ROBIN:
        hgData->modelId = MODEL_HG_ROBIN;
        hgData->crashModelId = MODEL_HG_ROBIN_CRASHED;
        hgData->unk2E4 = 4;
        hgData->unk2E5 = 11;
        hgData->unk2E6 = 12;
        hgData->unk2E7 = 13;
        hgData->unk268.x = 0.0f;
        hgData->unk268.y = -1.005f;
        hgData->unk268.z = -0.083f;
        hgData->unk27C.x = -0.685f;
        hgData->unk27C.y = 0.223f;
        hgData->unk27C.z = -0.986f;
        hgData->unk288.x = 0.685f;
        hgData->unk288.y = 0.223f;
        hgData->unk288.z = -0.986f;
        hgData->unk294.x = 0.001f;
        hgData->unk294.y = 1.662f;
        hgData->unk294.z = 0.23f;
        hgData->unk2A0.x = -4.206f;
        hgData->unk2A0.y = -0.202f;
        hgData->unk2A0.z = 0.574f;
        hgData->unk2AC.x = 4.207f;
        hgData->unk2AC.y = -0.202f;
        hgData->unk2AC.z = 0.574f;
        hgData->unk2B8.x = 0.0f;
        hgData->unk2B8.y = -0.094f;
        hgData->unk2B8.z = -1.578f;
        hgData->unk2C4 = 0.0f;
        hgData->unk2C8 = 0.094f;
        hgData->unk2CC = -1.578f;
        hgData->unk2D0 = 0.0f;
        hgData->unk2D4 = -0.82f;
        hgData->unk2D8 = -0.858f;
        hgData->unk274 = 0.654f;
        hgData->unk278 = -0.2f;
        hgData->unk2DC = 1.7f;
        hgData->unk2E8 = 46;
        hgData->unk2E9 = 49;
        hgData->unk2EA = 50;
        hgData->unk2EB = 47;
        hgData->unk2EC = 48;
        hgData->unk2ED = 51;
        hgData->unk2EE = 52;
        hgData->unk2F0 = 1.0f;
        hgData->unk2F4 = 0.8f;
        hgData->unk2F8 = 0.8f;
        hgData->unk2FC = 1.2f;
        hgData->unk300 = 1.2f;
        hgData->unk304 = 1.2f;
        break;
    default:
        break;
    }
}
