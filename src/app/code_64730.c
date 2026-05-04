#include "common.h"
#include "code_64730.h"
#include "code_66160.h"
#include "code_9A960.h"
#include "code_D2B10.h"
#include "demo.h"
#include "file_menu.h"
#include "snd.h"
#include "task.h"
#include "code_64730.h"
#include "text_data.h"
#include <uv_anim.h>
#include <uv_dobj.h>
#include <uv_font.h>
#include <uv_memory.h>
#include <uv_model.h>
#include <uv_sprite.h>
#include <uv_texture.h>

f32 D_80359CA0;
f32 D_80359CA4;
Mtx4F D_80359CA8;
Mtx4F D_80359CE8;
Mtx4F D_80359D28;
s8 D_80359D68;
s8 D_80359D69;
s8 D_80359D6A;

s8 D_8034EDA0 = 0;
s8 D_8034EDA4[] = { 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

f32 D_8034EDBC = 0.0f;

u8 D_8034EDC0 = 0xFF;
u8 D_8034EDC4 = 0xFF;
s32 D_8034EDC8 = 0xFFFF;
s32 D_8034EDCC = 0xFFFF;
f32 D_8034EDD0 = 0.0f;
f32 D_8034EDD4 = 0.0f;
f32 D_8034EDD8 = 0.0f;

Unk803599D0 D_8034EDDC[] = {
    8, 0.36f, 0.0f, 0.412f, 0.1f, 0.465f, 0.25f, 0.517f, 0.475f, 0.568f, 0.5f, 0.62f, 0.475f, 0.673f, 0.25f, 0.725f, 0.0f, 0, 0, 0, 0
};

s16 D_8034EE30[VEHICLE_COUNT][PILOT_COUNT] = {
    {               MODEL_HG_LARK,               MODEL_HG_GOOSE,               MODEL_HG_HAWK,               MODEL_HG_KIWI,               MODEL_HG_IBIS,MODEL_HG_ROBIN                                                                                                                                                       },
    {               MODEL_RB_LARK,               MODEL_RB_GOOSE,               MODEL_RB_HAWK,               MODEL_RB_KIWI,               MODEL_RB_IBIS,        MODEL_RB_ROBIN },
    {             MODEL_GYRO_LARK,             MODEL_GYRO_GOOSE,             MODEL_GYRO_HAWK,             MODEL_GYRO_KIWI,             MODEL_GYRO_IBIS,      MODEL_GYRO_ROBIN },
    { MODEL_CANNONB_LARK_LAUNCHED, MODEL_CANNONB_GOOSE_LAUNCHED, MODEL_CANNONB_HAWK_LAUNCHED, MODEL_CANNONB_KIWI_LAUNCHED, MODEL_CANNONB_IBIS_LAUNCHED,
     MODEL_CANNONB_ROBIN_LAUNCHED                                                                                                                                            },
    {        MODEL_PARACHUTE_LARK,        MODEL_PARACHUTE_GOOSE,        MODEL_PARACHUTE_HAWK,        MODEL_PARACHUTE_KIWI,        MODEL_PARACHUTE_IBIS, MODEL_PARACHUTE_ROBIN },
    {          MODEL_JUMBLEH_LARK,          MODEL_JUMBLEH_GOOSE,          MODEL_JUMBLEH_HAWK,          MODEL_JUMBLEH_KIWI,          MODEL_JUMBLEH_IBIS,   MODEL_JUMBLEH_ROBIN },
    {          MODEL_BIRDMAN_LARK,          MODEL_BIRDMAN_GOOSE,          MODEL_BIRDMAN_HAWK,          MODEL_BIRDMAN_KIWI,          MODEL_BIRDMAN_IBIS,   MODEL_BIRDMAN_ROBIN },
};

u8 D_8034EE84[8] = {
    0x4C, 0x4D, 0x4B, 0x51, 0x50, 0x4F, 0x4E, 0x00,
};

f32 D_8034EE8C[] = {
    -0.745f, -1.336f, -1.221f, -0.828f, -1.36f, -1.076f, -0.745f, -1.336f, -1.0f, -1.0f, -1.0f, -1.0f,
};

f32 D_8034EEBC[] = {
    -0.745f, -1.336f, -1.221f, -0.828f, -1.36f, -1.076f,
};

// forward declarations
STATIC_FUNC void func_802DD57C(Camera* camera);
STATIC_FUNC s32 func_802DD8E8(Camera* camera, Unk80367868*, s32);
STATIC_FUNC void func_802DE5B0(Camera* camera, Unk80367868*);
STATIC_FUNC void func_802DE964(Camera*, Unk80367868*, s32);

// handles the pilot selection. Returns -1 on failure? Otherwise returns selected pilot id
s32 func_802DD200(Camera* camera, Unk80367868* arg1) {
    s32 result;
    s32 selectedPilot;

    func_802DD57C(camera);
    // @fake
    func_802DD8E8(camera, arg1, arg1->unk4[D_8034EDC0].pilot * 0);
    uvGfxBegin();
    func_802DE5B0(camera, arg1);
    uvGfxEnd();
    do {
        uvGfxBegin();
        func_802DE5B0(camera, arg1);
        uvGfxEnd();
        // @fake
        result = func_802DD8E8(camera, arg1, 1) ^ 0;
    } while (result == 7);
    func_802DE964(camera, arg1, 0);
    if (result == 8) {
        return -1;
    }
    selectedPilot = arg1->unk4[D_8034EDC0].pilot;
    switch (selectedPilot) {
    case PILOT_LARK:
        sndPlaySfx(SFX_PILOT_LARK_SELECT);
        selectedPilot = arg1->unk4[D_8034EDC0].pilot;
        break;
    case PILOT_GOOSE:
        sndPlaySfx(SFX_PILOT_GOOSE_SELECT);
        selectedPilot = arg1->unk4[D_8034EDC0].pilot;
        break;
    case PILOT_HAWK:
        sndPlaySfx(SFX_PILOT_HAWK_SELECT);
        selectedPilot = arg1->unk4[D_8034EDC0].pilot;
        break;
    case PILOT_KIWI:
        sndPlaySfx(SFX_PILOT_KIWI_SELECT);
        selectedPilot = arg1->unk4[D_8034EDC0].pilot;
        break;
    case PILOT_IBIS:
        sndPlaySfx(SFX_PILOT_IBIS_SELECT);
        selectedPilot = arg1->unk4[D_8034EDC0].pilot;
        break;
    case PILOT_ROBIN:
        sndPlaySfx(SFX_PILOT_ROBIN_SELECT);
        selectedPilot = arg1->unk4[D_8034EDC0].pilot;
        break;
    }
    return selectedPilot;
}

STATIC_FUNC void func_802DD42C(void) {
    uvSprtDraw(0);
}

STATIC_FUNC void func_802DD44C(void) {
    Mtx4F sp88;
    Mtx4F sp48;
    s32 i;

    for (i = 1; i < 7; i++) {
        uvSprtDraw(i);
    }
    uvGfxSetViewport(0, 0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);
    uvMat4SetOrtho(&sp88, 0.0f, SCREEN_WIDTH - 1.0f, 0.0f, SCREEN_HEIGHT - 1.0f);
    uvGfxMtxProjPushF(&sp88);
    uvMat4SetIdentity(&sp48);
    uvGfxMtxViewLoad(&sp48, 1);
    func_802DEE44(D_80359CA0 + 0.5, D_80359CA4 + 0.5, 0x35, 0x3E, 3, 0xFF, 0xFF, 0, 0xFF, 0xFF, 0);
    uvGfxMtxViewPop();
    func_8034B6F8();
}

STATIC_FUNC void func_802DD57C(Camera* camera) {
    Unk80362690_Unk0* sp3C;

    sp3C = &D_80362690->unkC[D_80362690->unk9C];
    uvLevelInit();
    uvLevelAppend(0x70);
    uvLevelAppend(D_8034EE84[sp3C->veh]);
    textLoadBlock(0x42);
    // clang-format off
    uvSprtProps(0,
        SPRT_PROP_ENABLED(TRUE),
        SPRT_PROP_POS(0, SCREEN_HEIGHT),
        SPRT_PROP_BLIT(BLIT_ID_43),
        SPRT_PROP_END
    );
    uvSprtProps(1,
        SPRT_PROP_ENABLED(TRUE),
        SPRT_PROP_POS(29, 202),
        SPRT_PROP_BLIT(BLIT_ID_3D),
        SPRT_PROP_END
    );
    uvSprtProps(2,
        SPRT_PROP_ENABLED(TRUE),
        SPRT_PROP_POS(82, 202),
        SPRT_PROP_BLIT(BLIT_ID_40),
        SPRT_PROP_END
    );
    uvSprtProps(3,
        SPRT_PROP_ENABLED(TRUE),
        SPRT_PROP_POS(29, 140),
        SPRT_PROP_BLIT(BLIT_ID_3E),
        SPRT_PROP_END
    );
    uvSprtProps(4,
        SPRT_PROP_ENABLED(TRUE),
        SPRT_PROP_POS(82, 140),
        SPRT_PROP_BLIT(0x41),
        SPRT_PROP_END
    );
    uvSprtProps(5,
        SPRT_PROP_ENABLED(TRUE),
        SPRT_PROP_POS(29, 78),
        SPRT_PROP_BLIT(BLIT_ID_3F),
        SPRT_PROP_END
    );
    uvSprtProps(6,
        SPRT_PROP_ENABLED(TRUE),
        SPRT_PROP_POS(82, 78),
        SPRT_PROP_BLIT(BLIT_ID_42),
        SPRT_PROP_END
    );
    // clang-format on
    uvChan_80204BD4(camera->unk22C, 1, 1.0f);
    uvChan_80204A8C(camera->unk22C, 1);
    uvChan_80204C94(camera->unk22C, -0.3504673f, 0.3504673f, -0.25f, 0.25f, 0.5f, 100.0f);
    uvChanEnv(camera->unk22C, 0xFFFF);
    uvChan_80204AB0(camera->unk22C, 0, func_802DD42C);
    uvChan_80204AB0(camera->unk22C, 1, func_802DD44C);
    D_80359CA0 = (D_8034EDA0 * 0x35) + 0x1A;
    D_80359CA4 = 0x90 - (*D_8034EDA4 * 0x3E);
    D_80359D68 = D_80359D69 = D_80359D6A = 0;
    uvMat4SetIdentity(&camera->unk108);
    uvMat4LocalTranslate(&camera->unk108, 0.0f, 0.0f, -0.5f);
    uvMat4RotateAxis(&camera->unk108, 0.2f, 'x');
    D_8034EDC4 = 0xFF;
    D_80362690->unkA3 = 0;
}

STATIC_FUNC s32 func_802DD8E8(Camera* camera, Unk80367868* arg1, s32 arg2) {
    f32 sp10C;
    f32 var_fv0;
    u8* temp;
    Unk80367868_Unk4* sp100;
    u16 spFE;
    Unk80362690_Unk0* spF8;
    Mtx4F spB8;
    Mtx4F sp78;
    Mtx4F sp38;

    spF8 = &D_80362690->unkC[D_80362690->unk9C];
    demo_80323020();
    func_80313D74();
    sp10C = demoGetInputs(D_80362690->unk9C, INPUT_AXIS_X);
    var_fv0 = demoGetInputs(D_80362690->unk9C, INPUT_AXIS_Y);
    D_80359D68 = D_80359D69 = 0;
    if (ABS_NOEQ(sp10C) < 0.75f && ABS_NOEQ(var_fv0) < 0.75f) {
        D_80359D6A = 0;
    } else if (D_80359D6A == 0) {
        if (sp10C > 0.75f) {
            D_80359D68 = 1;
            D_80359D6A = 1;
        }
        if (sp10C < -0.75f) {
            D_80359D68 = -1;
            D_80359D6A = 1;
        }
        if (var_fv0 > 0.75f) {
            D_80359D69 = -1;
            D_80359D6A = 1;
        }
        if (var_fv0 < -0.75f) {
            D_80359D69 = 1;
            D_80359D6A = 1;
        }
    }
    D_8034EDA0 += D_80359D68;
    *D_8034EDA4 += D_80359D69;
    if (D_8034EDA0 < 0) {
        D_8034EDA0 = 0;
    } else if (D_8034EDA0 >= 2) {
        D_8034EDA0 = 1;
    }
    if (*D_8034EDA4 < 0) {
        *D_8034EDA4 = 0;
    } else if (*D_8034EDA4 >= 3) {
        *D_8034EDA4 = 2;
    }
    D_80359CA0 = (D_8034EDA0 * 0x35) + 0x1A;
    D_80359CA4 = 0x90 - (*D_8034EDA4 * 0x3E);
    D_8034EDD4 += 0.7f * D_8034F854;
    D_8034EDD8 += 7.0f * D_8034F854;
    if (D_8034EDD4 > 6.2831855f) {
        D_8034EDD4 -= 6.2831855f;
    }
    if (D_8034EDD8 > 6.2831855f) {
        D_8034EDD8 -= 6.2831855f;
    }
    if ((D_8034EDC0 != (((*D_8034EDA4) * 2) + ((0, D_8034EDA0)))) || (D_8034EDC4 != 0)) {
        if (D_8034EDC4 != 0) {
            D_8034EDC4 = 0;
        } else {
            sndPlaySfx(SFX_UI_SELECT_MOVE);
        }
        D_8034EDC0 = (*D_8034EDA4 * 2) + D_8034EDA0;
        sp100 = &arg1->unk4[D_8034EDC0];
        if (D_8034EDC8 != 0xFFFF) {
            uvDobjModel(D_8034EDC8, 0xFFFF);
        }
        D_8034EDC8 = uvDobjAllocIdx();
        if (D_8034EDC8 != 0xFFFF) {
            uvDobjModel(D_8034EDC8, D_8034EE30[spF8->veh][sp100->pilot]);
        }
        if (D_8034EDC8 != 0xFFFF) {
            uvMat4SetIdentity(&D_80359CA8);
            uvMat4LocalTranslate(&D_80359CA8, 0.78f, 3.5f, 0.0f);
            switch (spF8->veh) {
            default:
                var_fv0 = 0.2f;
                break;
            case VEHICLE_ROCKET_BELT:
                var_fv0 = -0.8f - D_8034EE8C[sp100->pilot];
                break;
            case VEHICLE_SKY_DIVING:
            case VEHICLE_JUMBLE_HOPPER:
                var_fv0 = -0.8f - D_8034EEBC[sp100->pilot];
                break;
            }
            uvMat4LocalTranslate(&D_80359CA8, 0.0f, 0.0f, var_fv0);
            if (spF8->veh == VEHICLE_GYROCOPTER) {
                uvMat4LocalTranslate(&D_80359CA8, 0.0f, 0.0f, -0.5f);
            }
            uvMat4RotateAxis(&D_80359CA8, 3.1415927f, 'z');
            if (spF8->veh == VEHICLE_BIRDMAN) {
                uvDobjGetPosm(D_8034EDC8, 0x16, &sp38);
                uvMat4RotateAxis(&sp38, 0.9424779f, 'x');
                uvDobjPosm(D_8034EDC8, 0x16, &sp38);
                uvMat4RotateAxis(&D_80359CA8, -1.5707961f, 'x');
            }
            uvDobjPosm(D_8034EDC8, 0, &D_80359CA8);
        }
        switch (D_8034EE30[spF8->veh][sp100->pilot]) {
        case MODEL_SKYDIVING_LARK:
            uvJanim_80200B00(D_8034EDC8, 0x56, 0.0f);
            break;
        case MODEL_SKYDIVING_GOOSE:
            uvJanim_80200B00(D_8034EDC8, 0x56, 0.0f);
            break;
        case MODEL_SKYDIVING_HAWK:
            uvJanim_80200B00(D_8034EDC8, 0x5B, 0.0f);
            break;
        case MODEL_SKYDIVING_KIWI:
            uvJanim_80200B00(D_8034EDC8, 0x60, 0.0f);
            break;
        case MODEL_SKYDIVING_IBIS:
            uvJanim_80200B00(D_8034EDC8, 0x64, 0.0f);
            break;
        case MODEL_SKYDIVING_ROBIN:
            uvJanim_80200B00(D_8034EDC8, 0x68, 0.0f);
            break;
        case MODEL_HG_LARK:
            uvJanim_80200EC0(D_8034EDC8, 0xF, 0.5f, 0.5f);
            break;
        case MODEL_HG_GOOSE:
            uvJanim_80200EC0(D_8034EDC8, 0x16, 0.5f, 0.5f);
            break;
        case MODEL_HG_HAWK:
            uvJanim_80200EC0(D_8034EDC8, 0x1D, 0.5f, 0.5f);
            break;
        case MODEL_HG_KIWI:
            uvJanim_80200EC0(D_8034EDC8, 0x20, 0.5f, 0.5f);
            break;
        case MODEL_HG_IBIS:
            uvJanim_80200EC0(D_8034EDC8, 0x27, 0.5f, 0.5f);
            break;
        case MODEL_HG_ROBIN:
            uvJanim_80200EC0(D_8034EDC8, 0x2E, 0.5f, 0.5f);
            break;
        }
        if (spF8->veh == 3) {
            switch (D_8034EE30[spF8->veh][sp100->pilot]) {
            case MODEL_CANNONB_LARK_LAUNCHED:
                D_8034EDD0 = 3.9f;
                spFE = 0x3E;
                break;
            case MODEL_CANNONB_GOOSE_LAUNCHED:
                D_8034EDD0 = 3.7f;
                spFE = 0x3F;
                break;
            case MODEL_CANNONB_HAWK_LAUNCHED:
                D_8034EDD0 = 3.8f;
                spFE = 0x40;
                break;
            case MODEL_CANNONB_KIWI_LAUNCHED:
                D_8034EDD0 = 3.9f;
                spFE = 0x41;
                break;
            case MODEL_CANNONB_IBIS_LAUNCHED:
                D_8034EDD0 = 3.7f;
                spFE = 0x42;
                break;
            case MODEL_CANNONB_ROBIN_LAUNCHED:
                D_8034EDD0 = 3.8f;
                spFE = 0x43;
                break;
            }
            if (D_8034EDCC != 0xFFFF) {
                uvDobjModel(D_8034EDCC, MODEL_WORLD);
            }
            D_8034EDCC = uvDobjAllocIdx();
            if (D_8034EDCC != 0xFFFF) {
                D_80359CA8.m[3][0] += 1.56;
                D_80359CA8.m[3][1] += 7.0f;
                uvDobjModel(D_8034EDCC, MODEL_CANNON_ON_PILLAR);
                uvDobjPosm(D_8034EDCC, 0, &D_80359CA8);
                uvMat4Copy(&D_80359CE8, &D_80359CA8);
                uvModelGetPosm(MODEL_CANNON_ON_PILLAR, 1, &D_80359D28);
                uvMat4RotateAxis(&D_80359D28, 0.3490658f, 'x');
                uvDobjPosm(D_8034EDCC, 1, &D_80359D28);
                uvMat4SetIdentity(&D_80359CA8);
                uvMat4RotateAxis(&D_80359CA8, -1.2217304f, 'x');
                uvJanim_80200B00(D_8034EDC8, (s32)spFE, 0.0f);
            }
        }
    }
    if (spF8->veh == VEHICLE_CANNONBALL && D_8034EDCC != 0xFFFF) {
        uvMat4Copy(&spB8, &D_80359CE8);
        uvMat4RotateAxis(&spB8, D_8034EDD4, 'z');
        uvDobjPosm(D_8034EDCC, 0, &spB8);
        uvMat4Mul(&sp78, &D_80359CA8, &spB8);
        uvMat4LocalTranslate(&sp78, 0.0f, 0.0f, D_8034EDD0);
        uvDobjPosm(D_8034EDC8, 0, &sp78);
    } else if (spF8->veh == VEHICLE_BIRDMAN) {
        uvMat4Copy(&spB8, &D_80359CA8);
        uvMat4RotateAxis(&spB8, D_8034EDD4, 'y');
        uvDobjPosm(D_8034EDC8, 0, &spB8);
    } else if (D_8034EDC8 != 0xFFFF) {
        uvMat4Copy(&spB8, &D_80359CA8);
        uvMat4RotateAxis(&spB8, D_8034EDD4, 'z');
        uvDobjPosm(D_8034EDC8, 0, &spB8);
    }
    if ((spF8->veh == VEHICLE_GYROCOPTER) && (D_8034EDC8 != 0xFFFF)) {
        // huh?
        temp = &arg1->unk4[D_8034EDC0].pilot;
        uvModelGetPosm(D_8034EE30[spF8->veh][*temp], 1, &spB8);
        uvMat4RotateAxis(&spB8, D_8034EDD8, 'z');
        uvDobjPosm(D_8034EDC8, 1, &spB8);
    }
    if (arg2 != 0) {
        if (demoButtonPress(D_80362690->unk9C, B_BUTTON) != 0) {
            sndPlaySfx(SFX_UI_CANCEL);
            return 8;
        }
        if (demoButtonPress(D_80362690->unk9C, A_BUTTON | START_BUTTON) != 0) {
            return arg1->unk4[D_8034EDC0].pilot;
        }
        return 7;
    }
    return 7;
}

STATIC_FUNC void func_802DE5B0(Camera* camera, Unk80367868* arg1) {
    static f32 D_8034EED4 = 0.0f;
    static f32 D_8034EED8 = 1.6f;
    s16* pilotName;
    s16* selectPilotText;
    s16 temp;
    f32 r;
    f32 g;
    f32 b;

    uvChan_80204B34(camera->unk22C, &camera->unk108);
    uvChan_80204FC4(camera->unk22C);
    uvFontSet(6);
    uvFontScale(1.0, 1.0);
    D_8034EED4 += D_8034EED8 * uvGfxGetFrameTime();
    if (D_8034EED4 > 1.0f) {
        D_8034EED4 = 1.0f;
        D_8034EED8 = -D_8034EED8;
    } else if (D_8034EED4 < 0.0f) {
        D_8034EED4 = 0.0f;
        D_8034EED8 = -D_8034EED8;
    }
    fileMenuColorLerp(D_8034EED4, 44.0f, 214.0f, 44.0f, 145.0f, 183.0f, 255.0f, &r, &g, &b);
    uvFontColor(r, g, b, 0xFF);
    selectPilotText = textGetDataByIdx(TEXT_PILOT_SEL);
    if (selectPilotText != NULL) {
        temp = ((SCREEN_WIDTH / 2) - (uvFontStr16Width(selectPilotText) / 2));
        uvFontPrintStr16(temp, 0xCE, selectPilotText, 0x14, 0xFFE);
    }
    pilotName = textGetDataByIdx(arg1->unk4[D_8034EDC0].textId);
    uvFontSet(6);
    uvFontColor(0xFF, 0xFF, 0xFF, 0xFF);
    uvFontScale(1.0, 1.0);
    uvFontPrintStr16(((425 - uvFontStr16Width(pilotName)) / 2) + 8, 30, pilotName, 0x14, 0xFFE);
    uvFontGenDlist();
}

STATIC_FUNC void func_802DE964(Camera* camera, Unk80367868* arg1, s32 arg2) {
    u16 spA6;
    Mtx4F sp64;
    f32 var_fs0;

    var_fs0 = 0.0f;
    if (arg2 != 0) {
        switch (arg1->unk4[D_8034EDC0].modelId) {
        case MODEL_PILOT_LARK:
            D_8034EDBC = 0.8f;
            spA6 = 0x6D;
            break;
        case MODEL_PILOT_GOOSE:
            D_8034EDBC = 0.35f;
            spA6 = 0x6E;
            break;
        case MODEL_PILOT_HAWK:
            D_8034EDBC = 0.2f;
            spA6 = 0x6F;
            break;
        case MODEL_PILOT_KIWI:
            D_8034EDBC = 0.75f;
            spA6 = 0x70;
            break;
        case MODEL_PILOT_IBIS:
            D_8034EDBC = 0.75f;
            spA6 = 0x71;
            break;
        case MODEL_PILOT_ROBIN:
            D_8034EDBC = 0.5f;
            spA6 = 0x72;
            break;
        }
        while (var_fs0 < 1.0f) {
            demo_80323020();
            if (demoButtonPress(D_80362690->unk9C, A_BUTTON | START_BUTTON) != 0) {
                break;
            }

            var_fs0 += D_8034F854 * D_8034EDBC;
            uvGfxBegin();
            uvMat4Copy(&sp64, &D_80359CA8);
            if (spA6 == 0x6D) {
                uvMat4LocalTranslate(&sp64, 0.0f, 0.0f, func_80313F08(D_8034EDDC, var_fs0));
            }
            uvDobjPosm(D_8034EDC8, 0, &sp64);
            uvJanim_80200B00(D_8034EDC8, spA6, var_fs0);
            uvChan_80204B34(camera->unk22C, &camera->unk108);
            uvChan_80204FC4(camera->unk22C);
            func_80313D74();
            uvGfxEnd();
        }
    }
    uvChan_80204AB0(camera->unk22C, 0, NULL);
    uvChan_80204AB0(camera->unk22C, 1, func_8034B6F8);
    if (D_8034EDC8 != 0xFFFF) {
        uvDobjModel(D_8034EDC8, MODEL_WORLD);
        D_8034EDC8 = 0xFFFF;
    }
    if (D_8034EDCC != 0xFFFF) {
        uvDobjModel(D_8034EDCC, MODEL_WORLD);
        D_8034EDCC = 0xFFFF;
    }
}
