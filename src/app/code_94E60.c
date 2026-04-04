#include "common.h"
#include "code_66160.h"
#include "code_9A960.h"
#include "code_B2900.h"
#include "code_D2B10.h"
#include "demo.h"
#include "file_menu.h"
#include "game.h"
#include "snd.h"
#include "text_data.h"
#include <uv_font.h>
#include <uv_geometry.h>
#include <uv_graphics.h>
#include <uv_memory.h>
#include <uv_sprite.h>
#include <uv_string.h>
#include <uv_texture.h>
#include <uv_vector.h>

f32 D_8036A8C0;
f32 D_8036A8C4;
s8 D_8036A8C8;
s8 D_8036A8C9;
s8 D_8036A8CA;
u8 D_8036A8CC[3];
s8 D_8036A8D0[CLASS_COUNT];
u8 D_8036A8D4[CLASS_COUNT];
u8 D_8036A8D8[CLASS_COUNT];

s8 D_8034F7A0 = 0;
s8 D_8034F7A4 = 0;
u8 D_8034F7A8 = 255;
u8 D_8034F7AC = 255;
u8 D_8034F7B0 = 0;
s8 D_8034F7B4 = 0;
u8 D_8034F7B8 = 0;
u8 D_8034F7BC = 0;
u8 D_8034F7C0 = 1;
Vec3F D_8034F7C4[2] = {
    {     -68.08f, -302.14f, 10.74f }, // position
    { -0.0174533f,     0.1f,   0.0f }  // rotation,  almost -DEG_TO_RAD(1)
};

// forward declarations
void func_8030E3EC(void);
void func_8030E9AC(void);
s32 func_8030EA54(void);
void func_8030F818(void);
u8 func_8030E7F4(void);
void func_8030F448(void);

// handle pilot select, returns next game state
s32 func_8030D930(void) {
    s32 nextGameState;

    func_8030E3EC();
    uvGfxBegin();
    func_8030F818();
    uvGfxEnd();
    do {
        uvGfxBegin();
        func_8030F818();
        uvGfxEnd();
        nextGameState = func_8030EA54();
    } while (nextGameState == -1);
    func_8030E9AC();
    if (nextGameState == -2) { // cancel
        nextGameState = GAME_STATE_FILE_MENU;
    } else if (nextGameState != 15) {
        nextGameState = GAME_STATE_PILOT_SELECT;
    }
    return nextGameState;
}

void func_8030D9C8(void) {
    u8* sp7C;
    Unk80364210* temp_s4;
    s32 temp_s0;
    s32 temp_v0;
    s32 var_s0;
    s32 classIdx;
    s32 i;
    s32 var_s6;
    s32 var_s3_2;
    s32 var_s6_2;

    for (i = 0; i < 12; i++) {
        uvSprtProps(i, 3, 1, 1, 46, 31, 2, ((i % 3) * 48) + 78, 161 - ((i / 3) * 34), 5, 332, 7, 255, 255, 255, 255, 0);
    }

    for (i = 0; i < ARRAY_COUNT(D_8036A8CC); i++) {
        uvSprtProps(i + 12, 3, 1, 1, 46, 31, 2, 236, 126 - (i * 34), 7, 255, 255, 255, 255, 5, 332, 0);
    }

    temp_s4 = &D_80364210[D_80362690->unk9C];
    for (var_s6 = 0; var_s6 < ARRAY_COUNT(D_8036A8CC); var_s6++) {
        for (classIdx = 0; classIdx < CLASS_COUNT; classIdx++) {
            temp_s0 = levelGetTotalPoints(temp_s4, classIdx, var_s6);
            temp_v0 = func_8032BE8C(temp_s4, classIdx, var_s6);
            if ((temp_s0 >= gMedalPointRequirements[classIdx].gold) && (temp_v0 != 0)) {
                var_s0 = 0x14E;
            } else if ((temp_s0 >= gMedalPointRequirements[classIdx].silver) && (temp_v0 != 0)) {
                var_s0 = 0x14F;
            } else {
                if ((temp_s0 >= gMedalPointRequirements[classIdx].bronze) && (temp_v0 != 0)) {
                    var_s0 = 0x150;
                } else {
                    var_s0 = 0x14D;
                }
            }
            uvSprtProps(var_s6 + classIdx * 3, 5, var_s0, 0);
            if (var_s0 == 0x14D) {
                break;
            }
        }

        // clang-format off
        if (D_8034F7BC != 0) { D_8036A8CC[var_s6] = 3; } else { D_8036A8CC[var_s6] = classIdx; }
        // clang-format on

        if (D_8036A8CC[var_s6] > 3) {
            D_8036A8CC[var_s6] = 3;
        }
    }
    if ((D_8036A8CC[0] == 0) || (D_8036A8CC[1] == 0) || (D_8036A8CC[2] == 0)) {
        for (i = 0; i < ARRAY_COUNT(D_8036A8CC); i++) {
            if (D_8036A8CC[i] > 0) {
                D_8034F7B4 = 0;
                uvSprtProps((D_8036A8CC[i] * ARRAY_COUNT(D_8036A8CC)) + i, 5, 332, 0);
                if (D_8034F7BC != 0) {
                    D_8036A8CC[i] = D_8036A8CC[i];
                } else {
                    D_8036A8CC[i] = 0;
                }
            }
        }
    }
    for (i = 0; i < ARRAY_COUNT(D_8036A8D8); i++) {
        var_s3_2 = TRUE;
        for (var_s0 = 0; var_s0 < 3; var_s0++) {
            if ((levelGetTotalPoints(temp_s4, i, var_s0) < gMedalPointRequirements[i].silver) || ((func_8032BE8C(temp_s4, i, var_s0) == 0))) {
                var_s3_2 = FALSE;
                break;
            }
        }
        D_8036A8D8[i] = var_s3_2;
    }
    D_8036A8D4[CLASS_BEGINNER] = D_8036A8D8[CLASS_BEGINNER];
    for (i = 1; i < ARRAY_COUNT(D_8036A8D8); i++) {
        var_s6_2 = TRUE;
        if (D_8036A8D8[i] != 0) {
            for (classIdx = 0; classIdx < CLASS_PILOT; classIdx++) {
                if (levelGetTotalPoints(temp_s4, classIdx, i + 2) < gMedalPointRequirements[4].silver) {
                    var_s6_2 = FALSE;
                    break;
                }
            }
            D_8036A8D4[i] = var_s6_2;
        } else {
            D_8036A8D4[i] = 0;
        }
    }
    D_8036A8D8[0] = func_8030E7F4();
}

void func_8030DED0(void) {
    Unk80364210* temp_s4;
    s32 temp_v0;
    s32 var_s0;
    s32 sp98;
    s32 var_s1_2;
    s32 i;
    s32 var_s3;
    s32 var_s7;
    s32 pad;

    for (i = 0; i < 9; i++) {
        uvSprtProps(i, 3, 1, 1, 46, 31, 2, ((i % 3) * 48) + 0x6D, 127 - ((i / 3) * 34), 5, 332, 7, 255, 255, 255, 255, 0);
    }
    for (i = 0; i < 4; i++) {
        uvSprtProps(i + 9, 3, 1, 1, 0x21, 0x1A, 2, 0x6D + (i * 36), 0xC3, 7, 255, 255, 255, 255, 5, 332, 0);
    }
    for (i = 0; i < 3; i++) {
        uvSprtProps(i + 13, 3, 1, 1, 46, 31, 2, 0x3D, 127 - (i * 34), 7, 255, 255, 255, 255, 5, 332, 0);
    }
    temp_s4 = &D_80364210[D_80362690->unk9C];
    for (i = CLASS_BEGINNER; i < CLASS_COUNT; i++) {
        var_s3 = TRUE;
        for (var_s0 = 0; var_s0 < 3; var_s0++) {
            if ((levelGetTotalPoints(temp_s4, i, var_s0) < gMedalPointRequirements[i].silver) || func_8032BE8C(temp_s4, i, var_s0) == 0) {
                var_s3 = FALSE;
                break;
            }
        }
        D_8036A8D8[i] = var_s3;
    }
    for (sp98 = 0; sp98 < ARRAY_COUNT(D_8036A8D8) - 1; sp98++) {
        if (D_8036A8D8[sp98 + 1] != 0) {
            for (var_s1_2 = 0; var_s1_2 < 3; var_s1_2++) {
                temp_v0 = levelGetTotalPoints(temp_s4, var_s1_2, sp98 + 3);
                if (temp_v0 >= gMedalPointRequirements[4].gold) {
                    var_s0 = 0x14E;
                } else if (temp_v0 >= gMedalPointRequirements[4].silver) {
                    var_s0 = 0x14F;
                } else {
                    if (temp_v0 >= gMedalPointRequirements[4].bronze) {
                        var_s0 = 0x150;
                    } else {
                        var_s0 = 0x14D;
                    }
                }
                uvSprtProps(sp98 * 3 + var_s1_2, 5, var_s0, 0);
                if (var_s0 == 0x14D) {
                    break;
                }
            }
            if (D_8034F7BC != 0) {
                D_8036A8D0[sp98] = 2;
            } else {
                D_8036A8D0[sp98] = var_s1_2;
            }
        } else if (D_8034F7BC != 0) {
            D_8036A8D0[sp98] = 2;
        } else {
            D_8036A8D0[sp98] = -1;
        }
        if ((u8)D_8036A8D0[sp98] > 2) {
            D_8036A8D0[sp98] = 2;
        }
    }
    D_8036A8D4[CLASS_BEGINNER] = D_8036A8D8[CLASS_BEGINNER];
    for (i = 1; i < ARRAY_COUNT(D_8036A8D8); i++) {
        var_s7 = TRUE;
        if (D_8036A8D8[i] != FALSE) {
            for (var_s1_2 = 0; var_s1_2 < 3; var_s1_2++) {
                if (levelGetTotalPoints(temp_s4, var_s1_2, i + 2) < gMedalPointRequirements[4].silver) {
                    var_s7 = FALSE;
                    break;
                }
            }
            D_8036A8D4[i] = var_s7;
        } else {
            D_8036A8D4[i] = FALSE;
        }
    }
    D_8036A8D8[0] = func_8030E7F4();
}

void func_8030E3EC(void) {
    Camera* camera;

    camera = D_80362690->unkC[D_80362690->unk9C].unk70;
    uvLevelInit();
    uvLevelAppend(1);
    uvLevelAppend(0x72);
    uvLevelAppend(0x4A);
    textLoadBlock(0x42); // "Failed"
    D_80362690->unkA3 = 0;
    D_8034F7BC = 0;
    uvSprtProps(17, 3, 1, 2, 28, 198, 9, 7, 0);
    uvSprtProps(18, 3, 1, 2, 233, 164, 9, 5, 0);
    uvSprtProps(19, 3, 1, 2, 58, 164, 9, 8, 0);
    uvSprtProps(20, 3, 1, 2, 58, 198, 9, 4, 0);
    uvSprtProps(21, 3, 1, 2, 233, 198, 9, 6, 0);
    if (D_8034F7C0 != 0) {
        D_8034F7A4 = 0;
        D_8034F7A0 = 0;
        D_8034F7B0 = 0;
        D_8034F7B8 = 0;
        D_8034F7C0 = 0;
    }
    if (D_8034F7B0 == 0) {
        func_8030D9C8();
    } else {
        func_8030DED0();
    }
    func_80204BD4(camera->unk22C, 1, 1.0f);
    func_80204A8C(camera->unk22C, 3);
    uvChanTerra(camera->unk22C, 0);
    func_80204C94(camera->unk22C, -0.4906542f, 0.4906542f, -0.35f, 0.35f, 1.0f, 2000.0f);
    uvChanEnv(camera->unk22C, 2);
    func_80204AB0(camera->unk22C, 0, NULL);
    func_80204AB0(camera->unk22C, 1, func_8030F448);
    func_80313640(D_8034F7C4->f[0], D_8034F7C4->f[1], D_8034F7C4->f[2], D_8034F7C4[1].f[0], D_8034F7C4[1].f[1], D_8034F7C4[1].f[2], &camera->unk108);
    func_80204B34(camera->unk22C, &camera->unk108);
    D_8034F7AC = 255;
    if (D_8034F7B0 == 0) {
        D_8036A8C0 = (D_8034F7A0 * 48) + 75;
        D_8036A8C4 = 127 - (D_8034F7A4 * 34);
    } else if (D_8034F7B8 == 0) {
        D_8036A8C0 = (D_8034F7A0 * 48) + 106;
        D_8036A8C4 = 93 - (D_8034F7A4 * 34);
    } else {
        D_8036A8C0 = (D_8034F7A0 * 36) + 106;
        D_8036A8C4 = 167.0f;
    }
    D_8036A8C8 = D_8036A8C9 = D_8036A8CA = 0;
}

u8 func_8030E7F4(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_8036A8D4); i++) {
        if (D_8036A8D4[i] != 0) {
            return TRUE;
        }
    }

    return FALSE;
}

s32 func_8030E860(s8* arg0) {
    s32 i;
    s32 ret;

    ret = -1;
    if (func_8030E7F4() == 0) {
        return ret;
    }

    if ((*arg0 == 1) && (D_8036A8D4[1] == 0) && (D_8036A8D4[2] != 0)) {
        *arg0 = 2;
    } else if ((*arg0 == 1) && (D_8036A8D4[2] == 0) && (D_8036A8D4[1] != 0)) {
        *arg0 = 1;
    } else if ((*arg0 == 2) && (D_8036A8D4[3] != 0)) {
        *arg0 = 3;
    } else if (D_8036A8D4[*arg0] == 0) {
        for (i = 0; i < ARRAY_COUNT(D_8036A8D4); i++) {
            if (D_8036A8D4[i] != 0) {
                *arg0 = i;
                break;
            }
        }
    }

    if (D_8036A8D4[*arg0] != 0) {
        ret = 0;
    }

    return ret;
}

void func_8030E9AC(void) {
    s32 i;
    Camera* camera;

    camera = D_80362690->unkC[D_80362690->unk9C].unk70;
    uvGfxMtxViewPop();
    for (i = 0; i < 15; i++) {
        uvSprtProps(i, 3, 0, 0);
    }
    func_80204AB0(camera->unk22C, 0, NULL);
    func_80204AB0(camera->unk22C, 1, func_8034B6F8);
}

s32 func_8030EA54(void) {
    f32 sp2C;
    f32 temp_fv0;
    s32 sp24;
    s32 sp20;
    s32 sp1C;
    Unk80362690_Unk0* sp18;

    demo_80323020();
    sp2C = demoGetInputs(D_80362690->unk9C, INPUT_AXIS_X);
    temp_fv0 = demoGetInputs(D_80362690->unk9C, INPUT_AXIS_Y);
    D_8036A8C8 = D_8036A8C9 = 0;
    if (ABS_NOEQ(sp2C) < 0.75f && ABS_NOEQ(temp_fv0) < 0.75f) {
        D_8036A8CA = 0;
    } else if (D_8036A8CA == 0) {
        if (sp2C > 0.75f) {
            D_8036A8C8 = 1;
            D_8036A8CA = 1;
        }
        if (sp2C < -0.75f) {
            D_8036A8C8 = -1;
            D_8036A8CA = 1;
        }
        if (temp_fv0 > 0.75f) {
            D_8036A8C9 = -1;
            D_8036A8CA = 1;
        }
        if (temp_fv0 < -0.75f) {
            D_8036A8C9 = 1;
            D_8036A8CA = 1;
        }
    }
    sp20 = D_8034F7A0;
    sp1C = D_8034F7A4;
    D_8034F7A0 += D_8036A8C8;
    D_8034F7A4 += D_8036A8C9;
    if (D_8034F7B0 == FALSE) {
        if (D_8034F7A4 < 0) {
            D_8034F7A4 = 0;
        }
        if (D_8036A8CC[sp20] < D_8034F7A4) {
            D_8034F7A4 = D_8036A8CC[sp20];
        }
        if (D_8034F7A0 < 0) {
            D_8034F7A0 = 0;
        } else {
            if ((D_8034F7A0 == 3) && (D_8034F7A4 >= 0) && ((D_8036A8D8[D_8034F7A4] != FALSE) || (D_8034F7BC != 0))) {
                D_8034F7B0 = TRUE;
                func_8030DED0();
                if (D_8034F7A4 == FALSE) {
                    D_8034F7A0 = FALSE;
                    D_8034F7A4 = func_8030E860(&D_8034F7A0);
                    if (D_8034F7A4 == -1) {
                        D_8034F7B0 = FALSE;
                        func_8030D9C8();
                    } else {
                        D_8034F7B8 = TRUE;
                    }
                } else {
                    D_8034F7A0 = 0;
                    D_8034F7A4 -= 1;
                }
            } else if (D_8034F7A0 == 3) {
                D_8034F7A0 = sp20;
            }
        }
        if (D_8036A8CC[D_8034F7A0] < D_8034F7A4) {
            D_8034F7A4 = D_8036A8CC[D_8034F7A0];
        }        
    } else if (D_8034F7B8 != FALSE) {
        D_8034F7A4 = 0;
        if (D_8036A8C9 == 1) {
            if ((sp20 == 1) || (sp20 == 2)) {
                D_8034F7A0 = 1;
            } else if (sp20 == 3) {
                D_8034F7A0 = 2;
            } else {
                D_8034F7A0 = 0;
            }

            for (sp24 = 1; sp24 < 4; sp24++) {
                if (D_8036A8D8[sp24] != FALSE) {
                    D_8034F7A4 = sp24 - 1;
                    D_8034F7B8 = FALSE;
                    break;
                }
            }

            if (D_8034F7B8 == TRUE) {
                D_8034F7A0 = sp20;
                D_8034F7A4 = 0;
                goto bail;
            }

            sndPlaySfx(0x74U);
            D_8034F7A8 = D_8034F7A0 + (D_8034F7A4 * 3);
            goto block_77;
        } else if (D_8036A8C8 == 1) {
            for (sp24 = sp20 + 1; sp24 < 4; sp24++) {
                if (D_8036A8D4[sp24] != FALSE) {
                    D_8034F7A0 = sp24;
                    break;
                }   
            }
            if (sp24 == 4) {
                D_8034F7A0 = sp20;
            }
        } else if (D_8036A8C8 == -1) {
            if (D_8034F7A0 < 0) {
                D_8034F7B0 = FALSE;
                D_8034F7B8 = FALSE;
                func_8030D9C8();
                D_8034F7A0 = 2;
                D_8034F7A4 = 0;
                goto bail;
            }

            for (sp24 = sp20 - 1; sp24 > -1; sp24--) {
                if (D_8036A8D4[sp24] != FALSE) {
                    D_8034F7A0 = sp24;
                    break;
                }
            }

            if (sp24 == -1) {
                D_8034F7B0 = FALSE;
                D_8034F7B8 = FALSE;
                func_8030D9C8();
                D_8034F7A0 = 2;
                D_8034F7A4 = 0;
            }
        }
    } else {
block_77:
        if (D_8034F7A4 > 2) {
            D_8034F7A4 = 2;
        }
        if (D_8034F7A0 < 0) {
            D_8034F7B0 = FALSE;
            func_8030D9C8();
            D_8034F7A0 = 2;
            D_8034F7A4 += 1;
            if (D_8036A8CC[D_8034F7A0] < D_8034F7A4) {
                D_8034F7A4 = D_8036A8CC[D_8034F7A0];
            }
        } else {
            if (D_8036A8D8[D_8034F7A4 + 1] == FALSE) {
                if (D_8036A8C9 == 0) {
                    D_8034F7A0 = sp20;
                    D_8034F7A4 = sp1C;
                } else {
                    sp24 = D_8034F7A4;
                    while ((sp24 >= 0) && (sp24 < 3)) {
                        if (D_8036A8D8[sp24 + 1] != FALSE) {
                            D_8034F7A4 = sp24;
                            break;
                        }
    
                        sp24 += D_8036A8C9;
                    }
                    if (D_8036A8D8[D_8034F7A4 + 1] == FALSE && (func_8030E7F4() != 0) && (D_8036A8C9 == -1)) {
                        D_8034F7A4 = -1;
                    } else if (sp24 != D_8034F7A4) {
                        D_8034F7A4 = sp1C;
                    }
                }
            }
            if (D_8034F7A4 < 0) {
                D_8034F7A4 = func_8030E860(&D_8034F7A0);
                if (D_8034F7A4 != 0) {
                    D_8034F7A4 = sp1C;
                } else {
                    sndPlaySfx(0x74U);
                    D_8034F7A8 = D_8034F7A0 + (D_8034F7A4 * 3);
                    D_8034F7B8 = TRUE;
                    goto bail;
                }
            }

            if (D_8034F7A4 > 2) {
                D_8034F7A4 = 2;
            }
            if ((u8)D_8036A8D0[sp1C] < D_8034F7A0) {
                D_8034F7A0 = (u8)D_8036A8D0[sp1C];
            }
            if ((u8)D_8036A8D0[D_8034F7A4] < D_8034F7A0) {
                D_8034F7A0 = (u8)D_8036A8D0[D_8034F7A4];
            }
            if (D_8034F7A0 >= 3) {
                D_8034F7A0 = 2;
                D_8034F7A0 = 2;
            }
        }
    }
    bail:
    if (D_8034F7B0 == FALSE) {
        D_8036A8C0 = (D_8034F7A0 * 48) + 75;
        D_8036A8C4 = 127 - (D_8034F7A4 * 34);
    } else if (D_8034F7B8 == FALSE) {
        D_8036A8C0 = (D_8034F7A0 * 48) + 106;
        D_8036A8C4 = 93 - (D_8034F7A4 * 34);
    } else {
        D_8036A8C0 = (D_8034F7A0 * 36) + 106;
        D_8036A8C4 = 167.0f;
    }
    if ((D_8034F7A0 + (D_8034F7A4 * 3)) != D_8034F7A8 || (D_8034F7AC != 0)) {
        if (D_8034F7AC != 0) {
            D_8034F7AC = 0;
        } else {
            sndPlaySfx(0x74U);
        }
        D_8034F7A8 = D_8034F7A0 + (D_8034F7A4 * 3);
    }
    if (demoButtonPress(D_80362690->unk9C, A_BUTTON | START_BUTTON) != 0) {
        sp18 = &D_80362690->unkC[D_80362690->unk9C];
        sndPlaySfx(0x6EU);
        if (D_8034F7B0 == FALSE) {
            sp18->cls = D_8034F7A4;
            sp18->veh = D_8034F7A0;
        } else if (D_8034F7B8 == FALSE) {
            sp18->veh = D_8034F7A4 + 3;
            sp18->cls = D_8034F7A0;
        } else {
            sp18->veh = 6;
            sp18->cls = D_8034F7A0;
        }
        return D_8034F7A8;
    }
    if (demoButtonPress(D_80362690->unk9C, B_BUTTON) != 0) {
        sndPlaySfx(1U);
        return -2;
    }
    return -1;
}
void func_8030F448(void) {
    s32 i;

    func_80314154();
    uvGfxSetFlags(GFX_STATE_400000);
    uvVtxBeginPoly();
    uvVtx(0, SCREEN_HEIGHT, 0, 0, 0, 0, 0, 0, 100);
    uvVtx(0, 0, 0, 0, 0, 0, 0, 0, 100);
    uvVtx(SCREEN_WIDTH, 0, 0, 0, 0, 0, 0, 0, 100);
    uvVtx(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 0, 0, 0, 0, 100);
    uvVtxEndPoly();
    uvGfxClearFlags(GFX_STATE_400000);
    func_803141E4();
    if (D_8034F7B0 == 0) {
        uvSprtDraw(17);
        uvSprtDraw(18);
        if ((D_8036A8D4[0] != 0) || (D_8036A8D4[1] != 0) || (D_8036A8D4[2] != 0) || (D_8036A8D4[3] != 0)) {
            uvSprtDraw(21);
        }
    } else {
        uvSprtDraw(19);
        uvSprtDraw(20);
    }
    if (D_8034F7B0 == 0) {
        for (i = 0; i < 12; i++) {
            uvSprtDraw(i);
        }

        for (i = 1; i < 4; i++) {
            if (D_8036A8D8[i] == FALSE) {
                uvSprtDraw(i + 11);
            }
        }
    } else {
        for (i = 0; i < 9; i++) {
            uvSprtDraw(i);
        }
        for (i = 0; i < 4; i++) {
            if (D_8036A8D4[i] == FALSE) {
                uvSprtDraw(i + 9);
            }
        }
        for (i = 1; i < 4; i++) {
            if (D_8036A8D8[i] == FALSE) {
                uvSprtDraw(i + 12);
            }
        }
    }

    func_80314154();
    if (D_8034F7B8 == 0) {
        func_802DEE44(D_8036A8C0 + 0.5, D_8036A8C4 + 0.5, 0x34, 0x26, 3, 0xFA, 0xFA, 0, 0xFA, 0xFA, 0);
    } else {
        func_802DEE44(D_8036A8C0 + 0.5, D_8036A8C4 + 0.5, 0x29, 0x20, 3, 0xFA, 0xFA, 0, 0xFA, 0xFA, 0);
    }
    uvGfx_80223A28(0xFFF);
    uvVtxRect(0, 18, 319, 0);
    uvVtxRect(0, 239, 319, 232);
    uvVtxRect(0, 232, 10, 18);
    uvVtxRect(310, 232, 319, 18);
    func_803141E4();
}

void func_8030F818(void) {
    static f32 D_8034F7DC = 0.0f;
    static f32 D_8034F7E0 = 1.6f;
    s32 temp_s1;
    s32 fontWidth;
    s32 var_s0;
    s32 var_s2;
    s32 var_s3;
    s32 var_s4;
    char spA4[4];
    s16* temp_v0;
    s32 sp9C;
    s32 sp98;
    s32 sp94;
    s32 var_v0;
    s32 var_v1;
    Unk80364210* sp88;
    f32 sp84;
    f32 sp80;
    f32 sp7C;
    Camera* camera;

    camera = D_80362690->unkC[D_80362690->unk9C].unk70;
    func_80204FC4(camera->unk22C);
    uvFontSet(6);
    uvFontScale(1.0, 1.0);
    D_8034F7DC += D_8034F7E0 * uvGfxGetUnkStateF();
    if (D_8034F7DC > 1.0f) {
        D_8034F7DC = 1.0f;
        D_8034F7E0 = -D_8034F7E0;
    } else if (D_8034F7DC < 0.0f) {
        D_8034F7DC = 0.0f;
        D_8034F7E0 = -D_8034F7E0;
    }
    fileMenuColorLerp(D_8034F7DC, 44.0f, 214.0f, 44.0f, 145.0f, 183.0f, 255.0f, &sp84, &sp80, &sp7C);
    uvFontColor(sp84, sp80, sp7C, 0xFFU);
    temp_v0 = textGetDataByIdx(0x105); // "SELECT VEHICLE & CLASS"
    func_80219874(0xA0 - (func_802196B0(temp_v0) / 2), 206, temp_v0, 40, 0xFFE);
    uvFontSet(3);
    uvFontScale(1.0, 1.0);
    fontWidth = uvFontWidth("A");
    sp88 = &D_80364210[D_80362690->unk9C];
    if (D_8034F7B0 != FALSE) {
        sp9C = 3;
    } else {
        sp9C = 0;
    }
    if (D_8034F7B0 != FALSE) {
        sp98 = 6;
    } else {
        sp98 = 3;
    }
    if (D_8034F7B0 != FALSE) {
        sp94 = 3;
    } else {
        sp94 = 4;
    }
    var_s3 = sp9C;
    while (var_s3 < sp98) {
        for (var_s2 = 0; var_s2 < sp94; var_s2++) {
            if (D_8034F7B0 == 0) {
                var_s4 = 0x83 - (var_s2 * 34);
                var_s0 = (var_s3 * 48) + 0x51;
            } else {
                var_s4 = 0x61 - ((var_s3 - sp9C) * 34);
                var_s0 = (var_s2 * 48) + 0x70;
            }
            temp_s1 = levelGetTotalPoints(sp88, var_s2, var_s3);
            if (var_s3 < 3) {
                var_v1 = var_s2;
            } else {
                var_v1 = 4;
            }
            if (temp_s1 >= gMedalPointRequirements[var_v1].bronze) {
                uvSprintf(spA4, "%d", temp_s1);
                if (temp_s1 < 100) {
                    var_s0 += fontWidth;
                }
                if (temp_s1 < 10) {
                    var_s0 += fontWidth;
                }
                uvFontSet(3);
                uvFontScale(1.0, 1.0);
                uvFontColor(0xBEU, 0xBEU, 0xBEU, 0xFFU);
                uvFontPrintStr(var_s0, var_s4, spA4);
                uvFontSet(3);
                uvFontScale(0.699999988079071, 1.0);
                uvFontColor(0xAAU, 0xAAU, 0xAAU, 0xFFU);
                if (D_8034F7B0 == 0) {
                    var_v0 = (var_s3 * 48) + 0x51;
                } else {
                    var_v0 = (var_s2 * 48) + 0x70;
                }
                uvFontPrintStr((fontWidth * 3) + var_v0, var_s4, "PTS");
            }
        }
        var_s3 += 1;
    }
    uvFontGenDlist();
}
