#include "common.h"
#include <uv_font.h>
#include <uv_geometry.h>
#include <uv_matrix.h>
#include <uv_memory.h>
#include <uv_sprite.h>
#include <uv_texture.h>
#include <uv_vector.h>
#include "app/demo.h"
#include "app/game.h"
#include "app/snd.h"
#include "app/text_data.h"
#include "app/code_9A960.h"
#include "app/code_B2900.h"
#include "app/code_D2B10.h"
#include "uv_graphics.h"

s32 D_8036A8A0;

u8 D_8034F420[][4] = {
    { 0, 3, 1, 2 },
    { 0, 2, 3, 1 },
    { 0, 1, 2, 3 },
    { 2, 1, 3, 0 },
    { 1, 0, 3, 2 },
    { 0, 1, 2, 0 },
    { 0, 3, 1, 2 }
};

u8 D_8034F43C[] = { 0, 2, 4, 9 };

s16 D_8034F440[] = { 0, 0x28, 0x51, 0xA5, 0, 0, 0, 0 };

Vec3F D_8034F450[] = {
    { 120.0f,                 0.0f, 0.7853980660438538f },
    { 300.0f,                 0.2f, 0.6108651757240295f },
    { 500.0f, -1.3707962036132812f, 0.6981316208839417f },
    { 340.0f,                 3.4f, 0.6108651757240295f }
};

// blitId, x offset
u16 D_8034F480[][2] = {
    { BLIT_ID_21, 220 },
    { BLIT_ID_1F, 220 },
    { BLIT_ID_20, 220 },
    { BLIT_ID_22, 220 },
    { BLIT_ID_23, 220 },
    { BLIT_ID_24, 220 },
    { BLIT_ID_25, 220 },
    { BLIT_ID_2D, 220 },
};

// blitId, x offset
u16 D_8034F4A0[][2] = {
    { BLIT_ID_27, 220 },
    { BLIT_ID_28, 220 },
    { BLIT_ID_26, 220 },
    { BLIT_ID_2A, 220 },
    { BLIT_ID_2B, 220 },
    { BLIT_ID_2C, 220 },
    { BLIT_ID_29, 220 }
};

u16 D_8034F4BC[] = { 0xEB, 0x13B, 0x125, 0x1B5, 0x172 };

u16 D_8034F4C8[] = { 0x129, 0x10D, 0xE0, 0xE0, 0x0129, 0x0129, 0x0129, 0xE0 };

u16 D_8034F4D8[] = { 0x9E, 0x9D, 0x07, 0x93 };

void func_8030C22C(void);
void func_8030C54C(void);
s32 func_8030C61C(void);
void func_8030C6A0(void);
void func_8030CB10(void);

s32 func_8030C1C0(void) {
    s32 gameState;

    func_8030C22C();
    uvGfxBegin();
    func_8030CB10();
    uvGfxEnd();
    do {
        uvGfxBegin();
        func_8030CB10();
        uvGfxEnd();
        gameState = func_8030C61C();
    } while (gameState == 0);

    func_8030C54C();
    return gameState;
}

void func_8030C22C(void) {
    Mtx4F spA8;
    Mtx4F sp68;
    Camera* temp_s1;
    Unk80362690_Unk0* temp_s0;
    s32 sp5C;
    s32 var_v1;
    f32 sp54;
    f32 sp50;
    f32 sp4C;

    temp_s0 = &D_80362690->unkC[D_80362690->unk9C];
    temp_s1 = temp_s0->unk70;
    uvLevelInit();
    uvLevelAppend(D_8034F43C[D_8034F420[temp_s0->veh][temp_s0->cls]]);
    uvLevelAppend(0xB);
    uvLevelAppend(0x87);
    uvLevelAppend(0x5C);
    textLoadBlock(0x42);
    func_80204BD4(temp_s1->unk22C, 1, 1.0f);
    func_80204A8C(temp_s1->unk22C, 1);
    uvChanEnv(temp_s1->unk22C, 0x17);
    func_80204C94(temp_s1->unk22C, -0.7009346f, 0.7009346f, -0.5f, 0.5f, 1.0f, 4000.0f);
    func_80204AB0(temp_s1->unk22C, 1, func_8030C6A0);
    sp5C = D_8034F420[temp_s0->veh][temp_s0->cls];
    D_8036A8A0 = uvDobjAllocIdx();
    uvDobjModel(D_8036A8A0, D_8034F440[sp5C]);
    uvMat4SetIdentity(&spA8);
    uvMat4SetIdentity(&sp68);
    func_803134D0(D_8034F450[sp5C].x, D_8034F450[sp5C].y, D_8034F450[sp5C].z, &sp54, &sp50, &sp4C);
    uvMat4LocalTranslate(&spA8, sp54, sp50, sp4C);
    uvMat4UnkOp6(&temp_s1->unk108, &sp68, &spA8);
    uvDobjPosm(D_8036A8A0, 0, &sp68);
    func_80204B34(temp_s1->unk22C, &temp_s1->unk108);
    // clang-format off
    uvSprtProps(0,
        SPRT_PROP_3(1),
        SPRT_PROP_POS((SCREEN_WIDTH / 2) - (D_8034F4A0[temp_s0->veh][1] / 2), 220),
        SPRT_PROP_BLIT(D_8034F4A0[temp_s0->veh][0]),
        SPRT_PROP_FAST_COPY(0),
        SPRT_PROP_TRANSPARENT(1),
        SPRT_PROP_END
    );
    // clang-format on
    if (IS_MAIN_VEHICLE(temp_s0->veh)) {
        var_v1 = temp_s0->cls;
    } else {
        var_v1 = temp_s0->cls + 4;
    }
    if (temp_s0->veh == VEHICLE_BIRDMAN) {
        var_v1 = 7;
    }
    // clang-format off
    uvSprtProps(1,
        SPRT_PROP_3(1),
        SPRT_PROP_POS((SCREEN_WIDTH / 2) - (D_8034F480[var_v1][1] / 2), 190),
        SPRT_PROP_BLIT(D_8034F480[var_v1][0]),
        SPRT_PROP_FAST_COPY(0),
        SPRT_PROP_TRANSPARENT(1),
        SPRT_PROP_END
    );
    // clang-format on
}

void func_8030C54C(void) {
    Camera* sp2C;

    sp2C = D_80362690->unkC[D_80362690->unk9C].unk70;
    uvDobjModel(D_8036A8A0, 0xFFFF);
    func_80204AB0(sp2C->unk22C, 0, NULL);
    func_80204AB0(sp2C->unk22C, 1, func_8034B6F8);
    // clang-format off
    uvSprtProps(0,
        SPRT_PROP_FAST_COPY(1),
        SPRT_PROP_TRANSPARENT(0),
        SPRT_PROP_3(0),
        SPRT_PROP_END
    );
    uvSprtProps(1,
        SPRT_PROP_FAST_COPY(1),
        SPRT_PROP_TRANSPARENT(0),
        SPRT_PROP_3(0),
        SPRT_PROP_END
    );
    // clang-format on
}

s32 func_8030C61C(void) {
    s32 ret;

    ret = 0;
    demo_80323020();
    if (demoButtonPress(D_80362690->unk9C, A_BUTTON | START_BUTTON) != 0) {
        ret = GAME_STATE_TEST_DETAILS;
        sndPlaySfx(SFX_UI_CONFIRM);
        func_8033FB14();
    } else if (demoButtonPress(D_80362690->unk9C, B_BUTTON) != 0) {
        ret = GAME_STATE_PILOT_SELECT;
        sndPlaySfx(SFX_UI_CANCEL);
    }
    return ret;
}

void func_8030C6A0(void) {
    Unk80362690_Unk0* sp74;
    s16* sp70;
    s16* sp6C;
    s16* sp68;
    s32 pad;
    s16 sp5C[3];
    s32 sp58;
    s32 var_v1;
    s32 sp50;
    s32 sp4C;
    s32 pad2[2];

    sp74 = &D_80362690->unkC[D_80362690->unk9C];
    if (IS_MAIN_VEHICLE(sp74->veh)) {
        sp58 = sp74->cls;
    } else {
        sp58 = sp74->veh + 1;
    }
    var_v1 = levelSetPointsToNextMedal(&sp50, levelGetTotalPoints(&D_80364210[D_80362690->unk9C], sp74->cls, sp74->veh), sp58);

    if ((var_v1 == 3) && (sp50 == 0)) {
        // FAKE
        if (sp50) { }
        var_v1 = 4;
    }

    sp6C = textGetDataByIdx(D_8034F4BC[var_v1]);
    sp68 = textGetDataByIdx(D_8034F4C8[sp58]);
    sp70 = textGetDataByIdx(D_8034F4D8[D_8034F420[sp74->veh][sp74->cls]]);
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
    textFmtInt(sp5C, sp50, ARRAY_COUNT(sp5C));
    uvSprtDraw(0);
    uvSprtDraw(1);
    uvFontSet(6);
    uvFontScale(1.0, 1.0);
    uvFontColor(250, 250, 250, 255);
    func_80219874(((160 - (func_802196B0(sp70) / 2)) + 8.0f), 0x78, sp70, 0x28, 0xFFE);
    if (sp74->veh != 6) {
        uvFontSet(6);
        uvFontScale(1.0, 1.0);
        uvFontColor(200, 200, 0, 255);
        func_80219874(((160 - (func_802196B0(sp68) / 2)) + 8.0f), 0x4B, sp68, 0x28, 0xFFE);
        uvFontSet(6);
        uvFontScale(1.0, 1.0);
        uvFontColor(180, 180, 250, 255);
        if (var_v1 != 4) {
            sp4C = 160 - ((func_802196B0(sp6C) + 0x24) / 2);
            func_80219874(sp4C + 0x24, 0x23, sp6C, 0x28, 0xFFE);
            func_80219874(sp4C, 0x23, sp5C, 0x28, 0xFFE);
        } else {
            func_80219874(((160 - (func_802196B0(sp6C) / 2)) + 8.0f), 0x23, sp6C, 0x28, 0xFFE);
        }
    }
    uvFontGenDlist();
}

void func_8030CB10(void) {
    Camera* var_v1 = D_80362690->unkC[D_80362690->unk9C].unk70;

    func_80204FC4(var_v1->unk22C);
    func_8034B6F8();
}
