#include "common.h"
#include "skydiving.h"
#include <uv_font.h>
#include <uv_janim.h>
#include <uv_math.h>
#include <uv_memory.h>
#include <uv_model.h>
#include <uv_texture.h>
#include "app/demo.h"
#include "app/fdr.h"
#include "app/hud.h"
#include "app/mist.h"
#include "app/pads.h"
#include "app/sdsound.h"
#include "app/snd.h"
#include "app/text_data.h"
#include "app/code_66F70.h"
#include "app/code_7FE00.h"
#include "app/code_9A960.h"
#include "app/code_B6580.h"
#include "app/code_BA190.h"

s32 D_80371960;
s32 D_80371964;
s32 D_80371968;
s32 D_8037196C;
Unk80371970 D_80371970[4];

Unk8034FFD0 D_8034FFD0[] = {
    {
     { 0.0f, 1.5f, 0.0f },
     -1.5f,
     { 1.5f, 0.0f, -1.5f },
     0.0f,{ PW_PI, PW_PI_2, 0.0f },
     -PW_PI_2,
     0.7f,0.7f,
     0.1f,0.05f,
     2.0f,10,
     4, },
    {
     { 1.5f, 0.0f, 0.0f },
     -1.5f,
     { 0.0f, 1.5f, -1.5f },
     0.0f,       { -PW_PI_2, 0.0f, PW_PI },
     PW_PI_2, 0.7f,
     0.7f, 0.1f,
     0.05f, 2.0f,
     10,  10,
     },
    {
     { 0.0f, 1.5f, 0.0f },
     -1.5f,
     { 1.5f, 0.0f, -1.5f },
     0.0f,        { 0.0f, PW_PI_2, PW_PI },
     -PW_PI_2,
     0.7f, 0.7f,
     0.1f, 0.05f,
     2.0f, 10,
     8, },
    {
     { -1.5f, 0.0f, 1.5f },
     0.0f,     { 0.0f, 1.5f, 0.0f },
     -1.5f,
     { 0.0f, -PW_PI_2, PW_PI },
     PW_PI_2, 0.7f,
     0.7f, 0.1f,
     0.05f, 2.0f,
     10,   6,
     },
    {
     { -0.75f, 0.75f, 0.75f },
     -0.75f,
     { 0.75f, 0.75f, -0.75f },
     -0.75f,
     { -PW_PI_2, PW_PI_2, PW_PI_2 },
     -PW_PI_2,
     0.7f, 0.7f,
     0.1f, 0.05f,
     2.0f, 10,
     11, },
    {
     { -1.0f, -1.0f, 1.0f },
     1.0f,    { -1.5f, 0.0f, 0.0f },
     1.5f,     { 0.0f, -PW_PI_2, PW_PI_2 },
     PW_PI, 0.7f,
     0.7f, 0.1f,
     0.05f, 2.0f,
     10,   7,
     },
    {
     { -1.0f, 1.0f, 1.0f },
     -1.0f,
     { -1.5f, 1.5f, 0.0f },
     0.0f,        { 0.0f, PW_PI, PW_PI_2 },
     -PW_PI_2,
     0.7f, 0.7f,
     0.1f, 0.05f,
     2.0f, 10,
     255, },
    {
     { -1.0f, -2.0f, 2.0f },
     1.0f,    { -1.0f, 1.0f, 1.0f },
     -1.0f,
     { PW_PI_4, PW_PI_4, -PW_PI_4 },
     -PW_PI_4,
     0.7f, 0.7f,
     0.1f, 0.05f,
     2.0f, 10,
     13, },
    {
     { 1.0f, -1.0f, -2.5f },
     2.5f,     { 0.0f, 0.0f, 0.0f },
     0.0f,       { PW_PI, 0.0f, -PW_PI_2 },
     PW_PI_2, 0.7f,
     0.7f, 0.1f,
     0.05f, 2.0f,
     10,   5,
     },
    {
     { -1.0f, 2.5f, 1.0f },
     -2.5f,
     { 0.0f, 0.0f, 0.0f },
     0.0f,        { 0.0f, PW_PI_2, PW_PI },
     -PW_PI_2,
     0.7f, 0.7f,
     0.1f, 0.05f,
     2.0f, 10,
     14, },
    {
     { -2.0f, 0.75f, 2.0f },
     -0.75f,
     { 0.0f, 0.0f, 0.0f },
     0.0f,           { 0.0f, 0.0f, PW_PI },
     PW_PI, 0.7f,
     0.7f, 0.1f,
     0.05f, 2.0f,
     10,  12,
     },
    {
     { -1.0f, 3.0f, -3.0f },
     1.0f,     { 0.0f, 0.0f, 0.0f },
     0.0f, { -PW_PI_2, PW_PI_2, -PW_PI_2 },
     PW_PI_2, 0.7f,
     0.7f, 0.1f,
     0.05f, 2.0f,
     10,   3,
     },
    {
     { -0.0f, 0.75f, 0.0f },
     -0.75f,
     { -1.5f, 0.0f, 1.5f },
     0.0f,    { -PW_PI_2, PW_PI, PW_PI_2 },
     0.0f, 0.7f,
     0.7f, 0.1f,
     0.05f, 2.0f,
     10,   9,
     },
    {
     { -1.5f, 0.0f, 0.0f },
     1.5f, { 0.75f, 0.75f, -0.75f },
     -0.75f,
     { PW_PI_2, PW_PI, PW_PI_2 },
     PW_PI, 0.7f,
     0.7f, 0.1f,
     0.05f, 2.0f,
     10, 255,
     },
    {
     { -0.75f, 0.75f, 0.75f },
     -0.75f,
     { -1.5f, 1.5f, 0.0f },
     0.0f,        { 0.0f, -PW_PI_2, 0.0f },
     -PW_PI_2,
     0.7f, 0.7f,
     0.1f, 0.05f,
     2.0f, 10,
     255, }
};

void skydivingLoadPilot(u8 pilot, SkyDivingData* sdData);
void func_803316B0(SkyDivingData*);
void skydivingLand(SkyDivingData*);
void func_803318D4(SkyDivingData*);
void func_80331EB8(SkyDivingData*);
void func_80331FE4(SkyDivingData*);
void func_803322CC(SkyDivingData*);
void func_80332950(void);
void func_803329C0(SkyDivingData*);

void skydivingInit(void) {
    D_80371960 = 0;
    D_80371968 = 0;
    D_80371964 = 0;
}

void skydivingLoadLevel(u8 contIdx, u8 pilot, SkyDivingData* sdData, Camera* camera) {
    uvMemSet(sdData, 0, sizeof(SkyDivingData));
    skydivingLoadPilot(pilot, sdData);
    sdData->objId = uvDobjAllocIdx();
    sdData->unk2 = 2;
    uvDobjModel(sdData->objId, sdData->unk1C0);
    uvDobjPosm(sdData->objId, 0, &sdData->unk10);
    uvDobjState(sdData->objId, sdData->unk2);
    sdData->contIdx = contIdx;
    sdData->camera = camera;
    sdData->unk22F = 0;
    sdData->unk4 = 0xFFFF;
    sdData->unk1AC = 0.0f;
    sdData->unk1B0 = 0.0f;
    sdData->unk1B4 = 0.0f;
    sdData->unk1B8 = 0.0f;
    sdData->unk1BC = 0.0f;
    sdData->unk5C = 0.0f;
    sdData->unk60 = 0.0f;
    sdData->unk64 = 0.0f;
    sdData->unk250 = 11.0f;
    sdData->unk254 = 1.0f;
    func_80332C60(sdData);
    sdSoundInit(sdData);
    db_getstart(&sdData->unk10, &sdData->unk154, NULL, NULL);
    sdData->unk10.m[3][2] -= 1000.0f;
    sdData->unk2B8 = sdData->unk10.m[3][0];
    sdData->unk2BC = sdData->unk10.m[3][1];
    sdData->unk2C0 = sdData->unk10.m[3][2];
    func_803329C0(sdData);
}

void skydivingEnterLeave(SkyDivingData* sdData) {
    if (D_80362690->state == GAME_STATE_RESULTS) {
        return;
    }
    sdData->unk310 = D_80362690->terraId;
    D_80362690->terraId = 9;
    uvChanTerra(sdData->camera->unk22C, 9);
    uvChanEnv(sdData->camera->unk22C, 1);
    db_getstart(&sdData->unk10, &sdData->unk154, NULL, NULL);
    sdData->unk10.m[3][2] -= 1000.0f;
    uvDobjPosm(sdData->objId, 0, &sdData->unk10);
    sdData->unk2B8 = sdData->unk10.m[3][0];
    sdData->unk2BC = sdData->unk10.m[3][1];
    sdData->unk2C0 = sdData->unk10.m[3][2];
    func_80332D94(sdData);
    sdData->unk70 = 0;
    sdData->unk25C = 0;
    sdData->unk68 = 0.0f;
    sdData->unk6C = 0.0f;
    sdData->unk26C = 0.0f;
    sdData->unk298 = 0.0f;
    sdData->unk284 = 0.0f;
    sdData->unk2B4 = 0.0f;
    sdData->unk288 = 0.0f;
    sdData->unk2C4 = 0.0f;
    sdData->unk268 = 1.0f;
    D_80371960 = 0;
    D_80371964 = 0;
    D_80371968 = 0;
    sdData->unk258 = &D_8034FFD0[D_80362690->unkC[D_80362690->unk9C].cls];
    sdData->unk2 = 2;
    uvDobjState(sdData->objId, sdData->unk2);
    sdData->unk58 = 0.5f;
    sdData->camera->unk1 = sdData->unk54 = 5;
    sdData->camera->unk4 = sdData->objId;
    sdData->camera->unk6 = sdData->unk2;
    sdData->camera->unk68.x = sdData->unk20C;
    sdData->camera->unk68.y = sdData->unk210;
    sdData->camera->unk68.z = sdData->unk214;
    sdData->camera->unk74 = 0.0f;
    sdData->camera->unk1B4 = 5.0f;
    sdData->camera->unk1B8 = 6.0f;
    sdData->camera->unk228 = 0.0f;
    sdData->camera->unk8 = 1.0f;
    sdData->unk27A = 0;
    sdData->unk294 = 0.5f;
    sdData->unk290 = 0.5f;
    func_802D45C4(sdData->camera, sdData->unk58);
    padsDeinit();
    level_8030B964();
}

void func_8032FE4C(SkyDivingData* sdData) {
    if (sdData->shadowObjId != 0xFFFF) {
        uvDobjModel(sdData->shadowObjId, 0xFFFF);
    }
    uvDobjModel(sdData->objId, 0xFFFF);
    sdData->contIdx = 0xFFFF;
    sdData->objId = 0xFFFF;
    func_80332950();
}

void func_8032FEAC(SkyDivingData* sdData, s32 buttons, u8 gameState) {
    s32 var_a0;
    Mtx4F sp34;
    f32 var_fa0;

    uvMat4Copy(&sp34, &sdData->unk10);
    sp34.m[3][0] = sdData->unk10.m[3][0] + ((2.0f * D_8034F854) * sdData->unk160.x);
    sp34.m[3][1] = sdData->unk10.m[3][1] + ((2.0f * D_8034F854) * sdData->unk160.y);
    sp34.m[3][2] = sdData->unk10.m[3][2] + ((2.0f * D_8034F854) * sdData->unk160.z);
    sp34.m[1][0] = 2.0f;
    sp34.m[1][1] = 2.0f;
    sp34.m[1][2] = 2.0f;
    if ((sdData->unk26C <= D_8034F850) && (sdData->unk10.m[3][2] > 100.0f) && (sdData->unk70 == 0)) {
        mist_803144D0(&sp34, NULL);
        sdData->unk26C = (D_8034F850 + 0.25f) - (ABS_NOEQ(sdData->unk274) * 0.25f);
    }
    uvMat4SetIdentity(&sp34);
    var_a0 = 0;
    if (sdData->unk264 == 1.0f) {
        if (sdData->unk10.m[3][2] < 100.0f) {
            var_a0 = 255 - (s32)(SQ(sdData->unk10.m[3][2] / 100.0f) * 255.0f);
        }
    } else {
        if (sdData->unk10.m[3][2] > 950.0f) {
            var_a0 = 255 - (s32)(((1000.0f - sdData->unk10.m[3][2]) * 255.0f) / 50.0f);
        }
    }
    if (var_a0 < 0) {
        var_a0 = 0;
    } else if (var_a0 > 255) {
        var_a0 = 255;
    }
    hudSetCameraState(var_a0);
    if ((sdData->unk264 != 1.0f) && (sdData->unk27A == 0) && (sdData->unk10.m[3][2] < 900.0f) && (sdData->unk25C == 0)) {
        sndPlaySfx(5);
        hudWarningText(0x132, 3.0f, 8.0f);
        sdData->unk25C = 1;
    }
    if (sdData->unk70 == 0) {
        buttons &= ~0xF;
    }
    if (buttons & L_CBUTTONS) {
        var_fa0 = 1.5707963f;
    } else if (buttons & 1) {
        var_fa0 = -1.5707963f;
    } else {
        var_fa0 = 0.0f;
    }
    sdData->unk68 = func_80313AF4(var_fa0, sdData->unk68, 2.0f);
    if (buttons & 4) {
        var_fa0 = 0.7853981f;
    } else if (buttons & 8) {
        var_fa0 = -0.7853981f;
    } else {
        var_fa0 = 0.0f;
    }
    sdData->unk6C = func_80313AF4(var_fa0, sdData->unk6C, 2.0f);
    if (gameState != 6) {
        sdData->unk54 = 4;
        sdData->camera->unk4 = sdData->objId;
        sdData->camera->unk6 = sdData->unk2;
        sdData->camera->unk78 = sdData->unk68;
        sdData->camera->unk7C = sdData->unk6C;
        sdData->camera->unk0 = 0;
        sp34.m[3][0] = sdData->unk10.m[3][0];
        sp34.m[3][1] = sdData->unk10.m[3][1];
        sp34.m[3][2] = sdData->unk10.m[3][2];
        if (sdData->unk70 != 0) {
            sdData->camera->unk0 |= 8;
        }
        if (sdData->unk70 == 0) {
            sdData->camera->unk1B4 = func_80313AF4(1.5f - ((sdData->unk160.z - -7.0f) * 0.2f), sdData->camera->unk1B4, 5.0f);
            uvMat4RotateAxis(&sp34, -1.5707963f, 'x');
            uvMat4RotateAxis(&sp34, sdData->unk5C, 'y');
            sdData->camera->unk1B0 = 1.5707963f;
        } else if (sdData->unk70 == 1) {
            sdData->camera->unk1B4 = func_80313AF4(26.5f - ((sdData->unk160.z - -7.0f) * 1.8f), sdData->camera->unk1B4, 5.0f);
            uvMat4RotateAxis(&sp34, -sdData->unk5C, 'z');
            if (demoButtonPress(0, R_TRIG) != 0) {
                sndPlaySfxVolPitchPan(0x67, 0.3f, 0.65f, 0.0f);
                if (sdData->unk290 == 1.0f) {
                    sdData->unk290 = 0.5f;
                } else {
                    sdData->unk290 = 1.0f;
                }
            }
            sdData->unk294 = func_80313AF4(sdData->unk290, sdData->unk294, 1.0f);
            sdData->camera->unk1B0 = uvCosF(sdData->unk298 * 6.2831855f) * (sdData->unk294 * 1.5707963f);
            if (sdData->unk298 > 0.52f) {
                sdData->unk298 = func_80313AF4(0.5f, sdData->unk298, 2.0f);
                if (sdData->camera->unk108.m[3][2] < 2.0f) {
                    sdData->camera->unk108.m[3][2] = 2.0f;
                }
            } else {
                sdData->unk298 = func_80313AF4(0.0f, sdData->unk298, 0.3f);
            }
            sp34.m[3][2] += 2.0f;
        } else if (sdData->unk70 == 4) {
            sdData->camera->unk1B4 = func_80313AF4(6.0f, sdData->camera->unk1B4, 1.0f);
            if (sdData->camera->unk1B4 <= 6.2f) {
                sdData->unk70 = 2;
            }
        } else if (sdData->unk70 == 5) {
            sdData->camera->unk1B4 = func_80313AF4(6.0f, sdData->camera->unk1B4, 1.0f);
            if (sdData->camera->unk1B4 <= 6.2f) {
                sdData->unk70 = 3;
            }
            uvMat4CopyXYZ(&sp34, &sdData->unk10);
        }
        if ((D_80371960 != 0) && (sdData->unk264 == 1.0f)) {
            sp34.m[3][0] = func_80313AF4(sp34.m[3][0], sdData->camera->unk80.m[3][0], 5.0f);
            sp34.m[3][1] = func_80313AF4(sp34.m[3][1], sdData->camera->unk80.m[3][1], 5.0f);
        }
        uvMat4Copy(&sdData->camera->unk80, &sp34);
        func_802D5884(sdData->camera, sdData->unk54);
    }
    sdData->camera->unk228 = (sdData->camera->unk108.m[3][2] - D_80371970[0].unk10.m[3][2]) - 1.5f;
}

void func_803305D4(SkyDivingData* sdData) {
    s32 i;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fv0;
    f32 var_fs0;
    f32 var_fs3;
    f32 var_fs4;
    f32 sp68;

    sp68 = (3.1415925f * D_8034F854) / 0.6f;
    sdData->unk2B4 -= sp68;
    if (sdData->unk2B4 < 0.0f) {
        sp68 += sdData->unk2B4;
    }

    var_fs3 = 0.0f;
    var_fs4 = 0.0f;

    for (i = 0; i < 3; i++) {
        var_fs3 += sdData->unk258->unk0[i];
        var_fs4 += sdData->unk258->unk10[i];
    }
    var_fs3 += sdData->unk258->unkC;
    var_fs4 += sdData->unk258->unk1C;
    var_fs3 *= 0.25f;
    var_fs4 *= 0.25f;
    var_fs3 += sdData->unk2B8;
    var_fs4 += sdData->unk2BC;

    sdData->camera->unk80.m[3][0] = func_80313AF4(var_fs3, sdData->camera->unk80.m[3][0], 3.0f);
    sdData->camera->unk80.m[3][1] = func_80313AF4(var_fs4, sdData->camera->unk80.m[3][1], 3.0f);

    for (i = 0; i < 3; i++) {
        temp_fs0 = D_80371970[i].unk10.m[3][0] - var_fs3;
        temp_fs1 = D_80371970[i].unk10.m[3][1] - var_fs4;
        temp_fv0 = uvSqrtF(SQ(temp_fs0) + SQ(temp_fs1));
        if (temp_fv0 != 0.0f) {
            temp_fs0 /= temp_fv0;
            temp_fs1 /= temp_fv0;
            var_fs0 = uvAtan2F(temp_fs1, temp_fs0) + sp68;
        } else {
            var_fs0 = 0.0f;
        }
        D_80371970[i].unk10.m[3][0] = (uvCosF(var_fs0) * temp_fv0) + var_fs3;
        D_80371970[i].unk10.m[3][1] = (uvSinF(var_fs0) * temp_fv0) + var_fs4;
        uvMat4RotateAxis(&D_80371970[i].unk10, -sp68, 'y');
        uvDobjPosm(D_80371970[i].unk0, 0, &D_80371970[i].unk10);
    }
    temp_fs0 = sdData->unk10.m[3][0] - var_fs3;
    temp_fs1 = sdData->unk10.m[3][1] - var_fs4;
    temp_fv0 = uvSqrtF(SQ(temp_fs0) + SQ(temp_fs1));
    if (temp_fv0 != 0.0f) {
        temp_fs0 /= temp_fv0;
        temp_fs1 /= temp_fv0;
        var_fs0 = uvAtan2F(temp_fs1, temp_fs0) + sp68;
    } else {
        var_fs0 = 0.0f;
    }
    sdData->unk10.m[3][0] = (uvCosF(var_fs0) * temp_fv0) + var_fs3;
    sdData->unk10.m[3][1] = (uvSinF(var_fs0) * temp_fv0) + var_fs4;
    uvMat4RotateAxis(&sdData->unk10, -sp68, 'y');
    uvDobjPosm(sdData->objId, 0, &sdData->unk10);
    sdData->unk2B4 -= sp68;
    if (sdData->unk2B4 <= 0.0f) {
        func_80331EB8(sdData);
        sdData->unk2B4 = 0.0f;
        sdData->unk288 = 0.0f;
    }
}

void skydivingMovementFrame(SkyDivingData* sdData, u8 gameState) {
    f32 stickX;
    f32 stickY;
    s32 buttons;
    Mtx4F sp34;

    if (sdData->unk2B4 > 0.0f) {
        func_803305D4(sdData);
        return;
    }

    if (sdData->unk70 == 3) {
        func_803316B0(sdData);
        return;
    }
    if ((sdData->unk70 == 4) || (sdData->unk70 == 5)) {
        skydivingLand(sdData);
        func_8032FEAC(sdData, 0, gameState);
        return;
    }
    if (fdr_802E6B5C() != 4) {
        if (gameState == GAME_STATE_RESULTS) {
            buttons = 0;
            stickY = 0.0f;
            stickX = 0.0f;
        } else {
            stickX = demoGetInputs(sdData->contIdx, INPUT_AXIS_X);
            stickY = demoGetInputs(sdData->contIdx, INPUT_AXIS_Y);
            buttons = demoGetButtons(sdData->contIdx);
        }
        sdData->unk270 = stickX;
        sdData->unk274 = stickY;
        if (stickY < 0.0f) {
            sdData->unk274 *= 0.75f;
        }
        if (gameState != GAME_STATE_RESULTS) {
            func_80332E90(sdData);
        }
        func_8032F3DC(sdData);
        if ((sdData->unk70 == 1) && (sdData->unk270 != 0.0f)) {
            if (D_8037196C == 0) {
                sndPlaySfxVolPitchPan(0x5F, 0.5f, 0.25f, 0.0f);
                D_8037196C = 1;
            }
        } else {
            D_8037196C = 0;
        }
        if (sdData->unk70 == 0) {
            sdData->unk64 = func_80313AF4(stickX, sdData->unk64, 1.0f);
        } else {
            sdData->unk64 = func_80313AF4(0.0f, sdData->unk64, 1.0f);
        }

        uvMat4Copy(&sp34, &sdData->unk10);
        uvMat4RotateAxis(&sp34, sdData->unk64 * 0.6f, 'z');
        uvDobjPosm(sdData->objId, 0, &sp34);
        func_803322CC(sdData);
        if (gameState != GAME_STATE_RESULTS) {
            func_803318D4(sdData);
        }
        func_8032FEAC(sdData, buttons, gameState);
        func_80331FE4(sdData);
        sdData->unk24C = 0;
        padsLandedPadStrip(sdData->unk10.m[3][0], sdData->unk10.m[3][1], sdData->unk10.m[3][2], &sdData->unk24C);
        if (sdData->unk24C != 0) {
            sdData->unk4 |= 4;
        } else {
            sdData->unk4 &= ~4;
        }
        if (gameState != GAME_STATE_RESULTS) {
            if (sdData->unk70 == 3) {
                fdr_802E66DC();
            }
            fdr_802E65AC(&sdData->unk10, &D_80362690->terraId, &stickX, &stickY, &buttons);
        }
    }
}

void skydivingLoadPilot(u8 pilot, SkyDivingData* sdData) {
    switch (pilot) {
    case PILOT_LARK:
        sdData->unk1C4.x = -0.025f, sdData->unk1C4.y = 0.097f, sdData->unk1C4.z = 0.675f;
        sdData->unk1D0.x = 0.0f, sdData->unk1D0.y = 0.0f, sdData->unk1D0.z = -0.745f;
        sdData->unk1DC.x = -0.027f, sdData->unk1DC.y = 0.442f, sdData->unk1DC.z = 0.012f;
        sdData->unk1E8.x = -0.024f, sdData->unk1E8.y = -0.27f, sdData->unk1E8.z = 0.101f;
        sdData->unk1F4.x = -0.54f, sdData->unk1F4.y = -0.156f, sdData->unk1F4.z = 0.105f;
        sdData->unk200.x = 0.486f, sdData->unk200.y = -0.156f, sdData->unk200.z = 0.105f;
        sdData->unk20C = -0.025f;
        sdData->unk210 = 0.307f;
        sdData->unk214 = 0.478f;
        sdData->unk218 = 0.6f;
        sdData->unk1C0 = MODEL_SKYDIVING_LARK;
        sdData->unk278 = MODEL_PARACHUTE_LARK;
        sdData->unk227 = 5;
        sdData->unk21C = 1;
        sdData->unk21D = 3;
        sdData->unk21E = 9;
        sdData->unk21F = 10;
        sdData->unk220 = 11;
        sdData->unk221 = 6;
        sdData->unk222 = 7;
        sdData->unk223 = 8;
        sdData->unk226 = 12;
        sdData->unk228 = 18;
        sdData->unk229 = 19;
        sdData->unk22A = 17;
        sdData->unk22B = 16;
        sdData->unk22E = 15;
        sdData->unk22C = 4;
        sdData->unk22D = 7;
        sdData->unk1A4 = 0x50;
        sdData->unk1A0 = 0x52;
        sdData->unk1A2 = 0x51;
        sdData->unk1A6 = 0x54;
        sdData->unk1A8 = 0x53;
        sdData->unk2A0 = 1.5f;
        sdData->unk2A8 = 1.0f;
        sdData->unk2AC = 1.0f;
        sdData->unk2B0 = 1.0f;
        break;
    case PILOT_GOOSE:
        sdData->unk1C4.x = -0.001f, sdData->unk1C4.y = 0.172f, sdData->unk1C4.z = 0.782f;
        sdData->unk1D0.x = 0.0f, sdData->unk1D0.y = 0.0f, sdData->unk1D0.z = -1.336f;
        sdData->unk1DC.x = 0.001f, sdData->unk1DC.y = 0.647f, sdData->unk1DC.z = -0.002f;
        sdData->unk1E8.x = -0.001f, sdData->unk1E8.y = -0.341f, sdData->unk1E8.z = 0.19f;
        sdData->unk1F4.x = -0.722f, sdData->unk1F4.y = -0.178f, sdData->unk1F4.z = 0.148f;
        sdData->unk200.x = 0.73f, sdData->unk200.y = -0.178f, sdData->unk200.z = 0.148f;
        sdData->unk20C = 0.0f;
        sdData->unk210 = 0.315f;
        sdData->unk214 = 0.603f;
        sdData->unk218 = 0.6f;
        sdData->unk1C0 = MODEL_SKYDIVING_GOOSE;
        sdData->unk278 = MODEL_PARACHUTE_GOOSE;
        sdData->unk227 = 5;
        sdData->unk21C = 1;
        sdData->unk21D = 3;
        sdData->unk21E = 9;
        sdData->unk21F = 10;
        sdData->unk220 = 11;
        sdData->unk221 = 6;
        sdData->unk223 = 8;
        sdData->unk226 = 12;
        sdData->unk228 = 18;
        sdData->unk222 = 7;
        sdData->unk229 = 19;
        sdData->unk22A = 17;
        sdData->unk22B = 16;
        sdData->unk22E = 15;
        sdData->unk22C = 4;
        sdData->unk22D = 7;
        sdData->unk1A4 = 0x56;
        sdData->unk1A0 = 0x58;
        sdData->unk1A2 = 0x57;
        sdData->unk1A6 = 0x5A;
        sdData->unk1A8 = 0x59;
        sdData->unk2A0 = 1.8f;
        sdData->unk2A8 = 1.150f;
        sdData->unk2AC = 0.850f;
        sdData->unk2B0 = 1.1500f;
        break;
    case PILOT_HAWK:
        sdData->unk1C4.x = 0.003f, sdData->unk1C4.y = 0.187f, sdData->unk1C4.z = 0.634f;
        sdData->unk1D0.x = 0.0f, sdData->unk1D0.y = 0.0f, sdData->unk1D0.z = -1.221f;
        sdData->unk1DC.x = -0.01f, sdData->unk1DC.y = 0.698f, sdData->unk1DC.z = -0.013f;
        sdData->unk1E8.x = -0.004f, sdData->unk1E8.y = -0.43f, sdData->unk1E8.z = -0.117f;
        sdData->unk1F4.x = -0.819f, sdData->unk1F4.y = -0.245f, sdData->unk1F4.z = 0.069f;
        sdData->unk200.x = 0.837f, sdData->unk200.y = -0.245f, sdData->unk200.z = 0.069f;
        sdData->unk20C = 0.002f;
        sdData->unk210 = 0.325f;
        sdData->unk214 = 0.52f;
        sdData->unk218 = 0.6f;
        sdData->unk1C0 = MODEL_SKYDIVING_HAWK;
        sdData->unk278 = MODEL_PARACHUTE_HAWK;
        sdData->unk227 = 5;
        sdData->unk21C = 1;
        sdData->unk21D = 3;
        sdData->unk21E = 9;
        sdData->unk21F = 10;
        sdData->unk220 = 11;
        sdData->unk221 = 6;
        sdData->unk222 = 7;
        sdData->unk223 = 8;
        sdData->unk226 = 12;
        sdData->unk228 = 18;
        sdData->unk229 = 19;
        sdData->unk22A = 17;
        sdData->unk22B = 16;
        sdData->unk22E = 15;
        sdData->unk22C = 4;
        sdData->unk22D = 7;
        sdData->unk1A4 = 0x5B;
        sdData->unk1A0 = 0x5D;
        sdData->unk1A2 = 0x5C;
        sdData->unk1A6 = 0x5F;
        sdData->unk1A8 = 0x5E;
        sdData->unk2A0 = 1.6f;
        sdData->unk2A8 = 0.85f;
        sdData->unk2AC = 1.150f;
        sdData->unk2B0 = 0.85f;
        break;
    case PILOT_KIWI:
        sdData->unk1C4.x = 0.002f, sdData->unk1C4.y = 0.084f, sdData->unk1C4.z = 0.706f;
        sdData->unk1D0.x = 0.0f, sdData->unk1D0.y = 0.0f, sdData->unk1D0.z = -0.828f;
        sdData->unk1DC.x = 0.0f, sdData->unk1DC.y = 0.426f, sdData->unk1DC.z = 0.03f;
        sdData->unk1E8.x = 0.0f, sdData->unk1E8.y = -0.261f, sdData->unk1E8.z = 0.107f;
        sdData->unk1F4.x = -0.479f, sdData->unk1F4.y = -0.153f, sdData->unk1F4.z = 0.079f;
        sdData->unk200.x = 0.489f, sdData->unk200.y = -0.153f, sdData->unk200.z = 0.079f;
        sdData->unk20C = 0.002f;
        sdData->unk210 = 0.308f;
        sdData->unk214 = 0.473f;
        sdData->unk218 = 0.6f;
        sdData->unk1C0 = MODEL_SKYDIVING_KIWI;
        sdData->unk278 = MODEL_PARACHUTE_KIWI;
        sdData->unk227 = 5;
        sdData->unk21C = 1;
        sdData->unk21D = 3;
        sdData->unk21E = 9;
        sdData->unk21F = 10;
        sdData->unk220 = 11;
        sdData->unk221 = 6;
        sdData->unk223 = 8;
        sdData->unk226 = 12;
        sdData->unk228 = 18;
        sdData->unk222 = 7;
        sdData->unk229 = 19;
        sdData->unk22A = 17;
        sdData->unk22B = 16;
        sdData->unk22E = 15;
        sdData->unk22C = 4;
        sdData->unk22D = 7;
        sdData->unk1A4 = 0x60;
        sdData->unk1A0 = 0x4D;
        sdData->unk1A2 = 0x61;
        sdData->unk1A6 = 0x63;
        sdData->unk1A8 = 0x62;
        sdData->unk2A0 = 1.4f;
        sdData->unk2A8 = 1.0f;
        sdData->unk2AC = 1.0f;
        sdData->unk2B0 = 1.0f;
        break;
    case PILOT_IBIS:
        sdData->unk1C4.x = -0.002f, sdData->unk1C4.y = 0.085f, sdData->unk1C4.z = 0.799f;
        sdData->unk1D0.x = 0.f, sdData->unk1D0.y = 0.0f, sdData->unk1D0.z = -1.36f;
        sdData->unk1DC.x = 0.0f, sdData->unk1DC.y = 0.586f, sdData->unk1DC.z = -0.034f;
        sdData->unk1E8.x = 0.0f, sdData->unk1E8.y = -0.314f, sdData->unk1E8.z = 0.091f;
        sdData->unk1F4.x = -0.666f, sdData->unk1F4.y = -0.164f, sdData->unk1F4.z = 0.141f;
        sdData->unk200.x = 0.678f, sdData->unk200.y = -0.164f, sdData->unk200.z = 0.141f;
        sdData->unk20C = 0.0f;
        sdData->unk210 = 0.212f;
        sdData->unk214 = 0.599f;
        sdData->unk218 = 0.6f;
        sdData->unk1C0 = MODEL_SKYDIVING_IBIS;
        sdData->unk278 = MODEL_PARACHUTE_IBIS;
        sdData->unk227 = 5;
        sdData->unk21C = 1;
        sdData->unk21D = 3;
        sdData->unk21E = 9;
        sdData->unk21F = 10;
        sdData->unk220 = 11;
        sdData->unk221 = 6;
        sdData->unk223 = 8;
        sdData->unk226 = 12;
        sdData->unk228 = 18;
        sdData->unk222 = 7;
        sdData->unk229 = 19;
        sdData->unk22A = 17;
        sdData->unk22B = 16;
        sdData->unk22E = 15;
        sdData->unk22C = 4;
        sdData->unk22D = 7;
        sdData->unk1A4 = 0x64;
        sdData->unk1A0 = 0x4E;
        sdData->unk1A2 = 0x65;
        sdData->unk1A6 = 0x67;
        sdData->unk1A8 = 0x66;
        sdData->unk2A0 = 1.8f;
        sdData->unk2A8 = 1.150f;
        sdData->unk2AC = 0.850f;
        sdData->unk2B0 = 1.15f;
        break;
    case PILOT_ROBIN:
        sdData->unk1C4.x = -0.001f, sdData->unk1C4.y = 0.095f, sdData->unk1C4.z = 0.844f;
        sdData->unk1D0.x = 0.0f, sdData->unk1D0.y = 0.0f, sdData->unk1D0.z = -1.076f;
        sdData->unk1DC.x = 0.0f, sdData->unk1DC.y = 0.563f, sdData->unk1DC.z = -0.018f;
        sdData->unk1E8.x = 0.0f, sdData->unk1E8.y = -0.433f, sdData->unk1E8.z = 0.155f;
        sdData->unk1F4.x = -0.737f, sdData->unk1F4.y = -0.266f, sdData->unk1F4.z = 0.112f;
        sdData->unk200.x = 0.751f, sdData->unk200.y = -0.266f, sdData->unk200.z = 0.112f;
        sdData->unk20C = 0.0f;
        sdData->unk210 = 0.217f;
        sdData->unk214 = 0.621f;
        sdData->unk218 = 0.6f;
        sdData->unk1C0 = MODEL_SKYDIVING_ROBIN;
        sdData->unk278 = MODEL_PARACHUTE_ROBIN;
        sdData->unk227 = 5;
        sdData->unk21C = 1;
        sdData->unk21D = 3;
        sdData->unk21E = 9;
        sdData->unk21F = 10;
        sdData->unk220 = 11;
        sdData->unk221 = 6;
        sdData->unk222 = 7;
        sdData->unk223 = 8;
        sdData->unk226 = 12;
        sdData->unk228 = 18;
        sdData->unk229 = 19;
        sdData->unk22A = 17;
        sdData->unk22B = 16;
        sdData->unk22E = 15;
        sdData->unk22C = 4;
        sdData->unk22D = 7;
        sdData->unk1A4 = 0x68;
        sdData->unk1A0 = 0x4F;
        sdData->unk1A2 = 0x69;
        sdData->unk1A6 = 0x6B;
        sdData->unk1A8 = 0x6A;
        sdData->unk2A0 = 1.6f;
        sdData->unk2A8 = 0.85f;
        sdData->unk2AC = 1.15f;
        sdData->unk2B0 = 0.85f;
        break;
    }
    uvModelGetPosm(sdData->unk278, sdData->unk228, &sdData->unk2D0);
}

void func_803316B0(SkyDivingData* sdData) {
    f32 var_fv1;
    f32 x;
    f32 y;
    f32 z;

    if (sdData->unk22F == 0) {
        sdData->unk22F = 1;
        if (sdData->unkB8 != 0) {
            if (sdData->unk27A != 0) {
                var_fv1 = 5.0f;
            } else {
                var_fv1 = 2.0f;
            }
            if (sdData->camera->unk108.m[3][2] > 0.0f) {
                x = sdData->unk10.m[3][0];
                y = sdData->unk10.m[3][1];
                z = sdData->unk10.m[3][2];
                func_802F8AB8(x, y, z, var_fv1, &sdData->unk160);
            }
            sdData->unk2 = 0;
            sdData->camera->unk6 = 0;
            uvDobjState(sdData->objId, sdData->unk2);
            uvMat4Copy(&sdData->camera->unk80, &sdData->unk10);
        }
    }
    hudGetState()->renderFlags = 0;
    func_8032F47C(sdData);
}

void skydivingLand(SkyDivingData* sdData) {
    TaskLPAD* sp34;
    u8 temp_v0;
    f32 temp_ft4;
    f32 temp_fa1;

    if (sdData->unk2C4 == 0.0f) {
        sndPlaySfx(0x48);
        temp_v0 = taskGetLPAD(&sp34);
        if (temp_v0 != 1) {
            _uvDebugPrintf("sdive_land: tell mikep != 1 pad\n");
        } else {
            temp_ft4 = sp34->pos.x;
            temp_fa1 = sp34->pos.y;
            D_80371964 = uvSqrtF(SQ(sdData->unk10.m[3][0] - temp_ft4) + SQ(sdData->unk10.m[3][1] - temp_fa1));
        }
        D_80371968 = -sdData->unk160.z;
        sdData->unk2C4 = -sdData->unk160.z;
    }

    if ((sdData->unk70 != 5) && (sdData->unk70 != 3)) {
        if (D_80371964 >= 0x1A) {
            hudText_8031D8E0(0xB2, 1.5f, 8.0f);
            sdData->unk25E = 0;
        } else {
            hudText_8031D8E0(0xCB, 1.5f, 8.0f);
            sdData->unk25E = 1;
        }
    }
    hudGetState()->renderFlags = 0;
    func_8032F47C(sdData);
}

void func_803318D4(SkyDivingData* sdData) {
    HUDState* temp_v0;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_ft4;
    s32 i;

    temp_v0 = hudGetState();
    uvMat4Copy(&temp_v0->unk28, &sdData->unk10);
    temp_v0->renderFlags = HUD_RENDER_SKYDIVING;
    temp_v0->unk8C = sdData->unk160.z * 4.0f * 0.7f;
    temp_v0->speed = sdData->unk16C * 3.6f * 0.7f;
    temp_v0->att.x = sdData->unk10.m[3][0];
    temp_v0->att.y = sdData->unk10.m[3][1];
    temp_v0->att.heading = sdData->unk10.m[3][2];
    temp_v0->att.pitch = sdData->unk5C;
    temp_v0->elapsedTime = D_8034F850;
    temp_v0->altSeaLevel = sdData->unk10.m[3][2];
    if (sdData->unk264 == 1.0f) {
        temp_v0->altitude = 101.0f;
    } else {
        temp_v0->altitude = sdData->unk280;
    }
    if (sdData->unk264 == 1.0f) {
        temp_v0->altSeaLevel += 1000.0f;
    }
    if (sdData->unk258 != NULL) {
        for (i = 0; i < 3; i++) {
            temp_fa0 = (200.0f * (D_80371970[i].unk10.m[3][0] - sdData->unk10.m[3][0])) + sdData->unk10.m[3][0];
            temp_fa1 = (200.0f * (D_80371970[i].unk10.m[3][1] - sdData->unk10.m[3][1])) + sdData->unk10.m[3][1];
            temp_ft4 = D_80371970[i].unk10.m[3][2];

            hudMoveWaypoint(D_80371970[i].unk70, temp_fa0, temp_fa1, temp_ft4);
        }
        return;
    }
    temp_v0->radar.unk4 = 0;
}

s32 skydivingGetPoints(s32 type) {
    switch (type) {
    case 1:
        return D_80371960;
    case 2:
        return D_80371964;
    case 3:
        return D_80371968;
    default:
        _uvDebugPrintf("sdive_getpoints: unknown type %d\n", type);
        return 0;
    }
}

void func_80331AE4(SkyDivingData* sdData) {
    uvDobjModel(sdData->objId, sdData->unk278);
    uvDobjState(sdData->objId, sdData->unk2);
    sdData->unk70 = 1;
    sdData->unk58 = 1.57f;
    sdData->unk160.x = 0.0f;
    sdData->unk160.y = 0.0f;
    sdData->unk160.z = 0.0f;
    func_802D45C4(sdData->camera, sdData->unk58);
    sdData->unk298 = 1.0f;
    sdData->unk29C = 0.1f;
    sdData->unk27A = 1;
    sndPlaySfx(0x49);
    sdData->unk21F = 0xA;
    sdData->unk222 = 0xD;
}

void skydivingBelow(SkyDivingData* sdData) {
    s32 var_a1;
    s32 i;

    func_802D45C4(sdData->camera, sdData->unk58);
    sdData->unk160.x = 0.0f;
    sdData->unk160.y = 0.0f;
    sdData->unk160.z = 0.0f;
    sdData->unk10.m[3][2] = 1000.0f;
    D_80362690->terraId = sdData->unk310;
    uvChanTerra(sdData->camera->unk22C, D_80362690->terraId);
    if (D_80362690->terraId == 3) {
        uvLevelAppend(0x7D);
        var_a1 = 0xD;
    } else if (D_80362690->terraId == 1) {
        uvLevelAppend(0x78);
        var_a1 = 8;
    } else if (D_80362690->terraId == 7) {
        uvLevelAppend(0x83);
        var_a1 = 0x13;
    } else if (D_80362690->terraId == 0) {
        uvLevelAppend(0x73);
        var_a1 = 3;
    } else {
        _uvDebugPrintf("sdive_below: undefined environment\n");
        var_a1 = 0xFFFF;
    }
    if (var_a1 != 0xFFFF) {
        uvChanEnv(sdData->camera->unk22C, var_a1);
    }
    for (i = 0; i < 3; i++) {
        if (D_80371970[i].unk0 != 0xFFFF) {
            uvDobjModel(D_80371970[i].unk0, 0xFFFF);
            D_80371970[i].unk0 = 0xFFFF;
        }

        if (sdData->shadowObjId != 0xFFFF) {
            uvDobjModel(sdData->shadowObjId, 0xFFFF);
        }
    }
    sdData->unk258 = 0;
    sdData->unk264 = sdData->unk10.m[3][2] * 0.05f;
    padsLoad();
    level_8030B868();

    if (D_80371960 != 0x32) {
        for (i = 0; i < 3; i++) {
            hud_8031A8E0(D_80371970[i].unk70);
        }
    }
}

s32 func_80331D58(SkyDivingData* sdData) {
    Unk8034FFD0* temp_v0;

    temp_v0 = sdData->unk258;

    if (temp_v0->unk38 < ABS_NOEQ(-sdData->unk5C - temp_v0->unk2C)) {
        return 0;
    }

    if (temp_v0->unk3C < ABS_NOEQ(sdData->unk60 - 1.5707963f)) {
        return 0;
    }

    if (temp_v0->unk30 <
        uvSqrtF(SQ(sdData->unk10.m[3][0] - (temp_v0->unkC + sdData->unk2B8)) + SQ(sdData->unk10.m[3][1] - (temp_v0->unk1C + sdData->unk2BC)))) {
        return 0;
    }

    if (temp_v0->unk34 < ABS_NOEQ(sdData->unk10.m[3][2] - D_80371970[0].unk10.m[3][2])) {
        return 0;
    }
    return 1;
}

void func_80331EB8(SkyDivingData* sdData) {
    s32 i;

    if (sdData->unk258->unk48 == 0xFF) {
        sdData->unk258 = NULL;
        for (i = 0; i < 3; i++) {
            hud_8031A8E0(D_80371970[i].unk70);
        }
    } else {
        sdData->unk258 = &D_8034FFD0[sdData->unk258->unk48];
    }

    for (i = 0; i < 3; i++) {
        D_80371970[i].unkC += -10.0f;
        D_80371970[i].unk4 += 8.0f * uvCosF(i * 1.5707963f);
        D_80371970[i].unk8 += 8.0f * uvSinF(i * 1.5707963f);
    }
}

void func_80331FE4(SkyDivingData* sdData) {
    static s32 D_80371B40;
    s16 sp2E;
    s16* sp28;

    sp2E = -1;
    if (sdData->unk258 != NULL) {
        sdData->unk288 += D_8034F854;
        sdData->unkB9 = func_80331D58(sdData);
        if (sdData->unkB9) {
            if (sdData->unk260 < 0.0f) {
                D_80371B40 = 3;
                sdData->unk260 = D_8034F850;
            }
            if ((D_8034F850 - sdData->unk260) > 0.1f) {
                sdData->unk288 = 100.0f;
            }
            uvFontSet(6);
            uvFontScale(1.0, 1.0);
            uvFontColor(0xFF, 0xFF, 0, 0xFF);

            if ((D_8034F850 - sdData->unk260) < (0.3333f * sdData->unk258->unk40)) {
                if (D_80371B40 == 3) {
                    D_80371B40--;
                    sndPlaySfxVolPitchPan(0x59, 0.8f, 1.0f, 0.0f);
                }
                sp2E = 9;
            } else if ((D_8034F850 - sdData->unk260) < (0.6667f * sdData->unk258->unk40)) {
                if (D_80371B40 == 2) {
                    D_80371B40--;
                    sndPlaySfxVolPitchPan(0x59, 0.8f, 1.0f, 0.0f);
                }
                sp2E = 0x76;
            } else if ((D_8034F850 - sdData->unk260) < sdData->unk258->unk40) {
                if (D_80371B40 == 1) {
                    D_80371B40--;
                    sndPlaySfxVolPitchPan(0x59, 0.8f, 1.0f, 0.0f);
                }
                sp2E = 0x10A;
            }
            if (sp2E != -1) {
                sp28 = textGetDataByIdx(sp2E);
                uvFontPrintStr16(160 - ((uvFontStr16Width(sp28) - 16) / 2), 125, sp28, 0x14, 0xFFE);
            }

            if (sdData->unk258->unk40 <= (D_8034F850 - sdData->unk260)) {
                D_80371960 += sdData->unk258->unk44;
                sdData->unk2B4 = 12.566371f;
                sdData->unk260 = -1.0f;
                hudWarningText(6, 1.5f, 8.0f);
                sndPlaySfx(SFX_UI_TEST_START);
            }
        } else {
            sdData->unk260 = -1.0f;
        }
    }
}

void func_803322CC(SkyDivingData* sdData) {
    f32 var_fs0;
    f32 var_fs1;
    f32 var_fs3;
    Unk80371970* spC8;
    Mtx4F sp88;
    Unk8034FFD0* temp_v0;
    s32 i;

    temp_v0 = sdData->unk258;
    if (temp_v0 == NULL) {
        return;
    }

    for (i = 0; i < 3; i++) {
        spC8 = &D_80371970[i];
        spC8->unk4 = func_80313AF4((sdData->unk2B8 + temp_v0->unk0[i]) - spC8->unk10.m[3][0], spC8->unk4, 1.0f);
        spC8->unk8 = func_80313AF4((sdData->unk2BC + temp_v0->unk10[i]) - spC8->unk10.m[3][1], spC8->unk8, 1.0f);
        spC8->unkC = func_80313AF4(-21.7f, spC8->unkC, 1.0f);
        var_fs0 = func_80313AF4(temp_v0->unk20[i], spC8->unk50, 1.0f) - spC8->unk50;
        spC8->unk50 += var_fs0;
        if (spC8->unk50 > 3.1415927f) {
            spC8->unk50 -= 6.2831855f;
        } else if (spC8->unk50 < -3.1415927f) {
            spC8->unk50 += 6.2831855f;
        }

        uvMat4RotateAxis(&spC8->unk10, -var_fs0, 'y');
        spC8->unk10.m[3][0] += spC8->unk4 * D_8034F854;
        spC8->unk10.m[3][1] += spC8->unk8 * D_8034F854;
        spC8->unk10.m[3][2] += spC8->unkC * D_8034F854;
        spC8->unk64 = func_80313AF4(uvRandF_RANLUX() - 0.50f, spC8->unk64, 10.0f);
        spC8->unk68 = func_80313AF4(uvRandF_RANLUX() - 0.50f, spC8->unk68, 10.0f);
        spC8->unk6C = func_80313AF4(uvRandF_RANLUX() - 0.50f, spC8->unk6C, 10.0f);

        spC8->unk10.m[3][0] += 0.5f * spC8->unk64 * D_8034F854;
        spC8->unk10.m[3][1] += 0.5f * spC8->unk68 * D_8034F854;
        spC8->unk10.m[3][2] += 0.5f * spC8->unk6C * D_8034F854;
        var_fs3 = 0.0f;
        var_fs1 = (sdData->unk10.m[3][2] - spC8->unk10.m[3][2]) + 1.57f;

        if (var_fs1 < -0.5f) {
            var_fs1 = -0.5f;
        } else if (var_fs1 > 2.5f) {
            var_fs1 = 2.5f;
        }
        var_fs0 = 1.0f;
        if (sdData->unkB9) {
            var_fs0 = sdData->unk288 * var_fs0;
            if (var_fs0 < 0.0f) {
                var_fs0 = 0.0f;
            } else if (var_fs0 > 1.0f) {
                var_fs0 = 1.0f;
            }
            var_fs1 += var_fs0 * uvCosF((i + 6.0f) * D_8034F850);
        } else {
            var_fs0 = spC8->unk10.m[3][2] - sdData->unk10.m[3][2];
            if (var_fs0 < 0.0f) {
                var_fs0 = 0.0f;
            } else if (var_fs0 > 5.0f) {
                var_fs0 = 5.0f;
            }
            var_fs3 = uvSinF(((5.0f + var_fs0) - i) * D_8034F850) * var_fs0;
        }

        spC8->unk5C = func_80313AF4(var_fs1, spC8->unk5C, (uvRandF_RANLUX() * 0.2f) + 0.8f);
        spC8->unk60 = func_80313AF4(var_fs3, spC8->unk60, (uvRandF_RANLUX() * 0.2f) + 0.8f);
        uvModelGetPosm(spC8->unk54, spC8->unk58, &sp88);
        uvMat4RotateAxis(&sp88, spC8->unk5C, 'x');
        uvMat4RotateAxis(&sp88, spC8->unk60, 'z');
        uvDobjPosm(spC8->unk0, spC8->unk58, &sp88);
        var_fs0 = 20.0f;
        if ((spC8->unk10.m[3][2] - sdData->unk10.m[3][2]) > var_fs0) {
            spC8->unk10.m[3][2] = sdData->unk10.m[3][2] + var_fs0;
        } else if ((spC8->unk10.m[3][2] - sdData->unk10.m[3][2]) < -var_fs0) {
            spC8->unk10.m[3][2] = sdData->unk10.m[3][2] - var_fs0;
        }
        uvDobjPosm(spC8->unk0, 0, &spC8->unk10);
    }

    if (sdData->unk284 < 0.0f) {
        sdData->unk284 -= D_8034F854;
        if (sdData->unk284 < -0.25f) {
            sdData->unk284 = 0.001f;
            uvDobjState(sdData->shadowObjId, 2);
        }
    } else {
        sdData->unk284 += D_8034F854;
        if (sdData->unk284 > 0.25f) {
            sdData->unk284 = -0.001f;
            uvDobjState(sdData->shadowObjId, 0);
        }
    }

    if ((sdData->unk288 > 50.0f) || ((D_80371960 != 0) && (sdData->unk288 < 4.0f))) {
        uvDobjState(sdData->shadowObjId, 0);
    }
    uvMat4SetIdentity(&sp88);
    uvMat4Scale(&sp88, 0.7f, 0.7f, 0.7f);
    sp88.m[3][0] = sdData->unk258->unkC + sdData->unk2B8;
    sp88.m[3][1] = sdData->unk258->unk1C + sdData->unk2BC;
    sp88.m[3][2] = spC8->unk10.m[3][2];
    uvMat4RotateAxis(&sp88, sdData->unk258->unk2C, 'z');
    uvDobjPosm(sdData->shadowObjId, 0, &sp88);
}

void func_80332950(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if (D_80371970[i].unk0 != 0xFFFF) {
            uvDobjModel(D_80371970[i].unk0, 0xFFFF);
            D_80371970[i].unk0 = 0xFFFF;
        }
    }
}

void func_803329C0(SkyDivingData* sdData) {
    Unk80371970* temp_fp;
    s32 i;
    Unk80371120 sp78;

    for (i = 0; i < 3; i++) {
        temp_fp = &D_80371970[i];
        switch (i) {
        case 0:
            if ((sdData->unk1C0 == MODEL_SKYDIVING_LARK) || (sdData->unk1C0 == MODEL_SKYDIVING_GOOSE) || (sdData->unk1C0 == MODEL_SKYDIVING_HAWK)) {
                temp_fp->unk54 = MODEL_SKYDIVING_KIWI;
                temp_fp->unk58 = 0xC;
                temp_fp->unk56 = 0x4D;
            } else {
                temp_fp->unk54 = MODEL_SKYDIVING_LARK;
                temp_fp->unk58 = 0xC;
                temp_fp->unk56 = 0x52;
            }
            break;
        case 1:
            if ((sdData->unk1C0 == MODEL_SKYDIVING_LARK) || (sdData->unk1C0 == MODEL_SKYDIVING_GOOSE) || (sdData->unk1C0 == MODEL_SKYDIVING_HAWK)) {
                temp_fp->unk54 = MODEL_SKYDIVING_IBIS;
                temp_fp->unk58 = 0xC;
                temp_fp->unk56 = 0x4E;
            } else {
                temp_fp->unk54 = MODEL_SKYDIVING_GOOSE;
                temp_fp->unk58 = 0xC;
                temp_fp->unk56 = 0x58;
            }
            break;
        default:
            if ((sdData->unk1C0 == MODEL_SKYDIVING_LARK) || (sdData->unk1C0 == MODEL_SKYDIVING_GOOSE) || (sdData->unk1C0 == MODEL_SKYDIVING_HAWK)) {
                temp_fp->unk54 = MODEL_SKYDIVING_ROBIN;
                temp_fp->unk58 = 0xC;
                temp_fp->unk56 = 0x4F;
            } else {
                temp_fp->unk54 = MODEL_SKYDIVING_HAWK;
                temp_fp->unk58 = 0xC;
                temp_fp->unk56 = 0x5D;
            }
            break;
        }
        temp_fp->unk0 = uvDobjAllocIdx();
        uvDobjModel(temp_fp->unk0, temp_fp->unk54);
        uvDobjState(temp_fp->unk0, 2);
        uvJanimPoseLine(&sp78, temp_fp->unk56, 1.0f);
        func_80200638(temp_fp->unk0, &sp78);
        temp_fp->unk5C = 0.0f;
        temp_fp->unk60 = 0.0f;
        temp_fp->unk64 = 0.0f;
        temp_fp->unk68 = 0.0f;
        temp_fp->unk6C = 0.0f;
        uvMat4SetIdentity(&temp_fp->unk10);
        uvMat4RotateAxis(&temp_fp->unk10, -1.5707963f, 'x');
        temp_fp->unk4 = 0.0f;
        temp_fp->unk8 = 0.0f;
        temp_fp->unkC = -21.7f;
        temp_fp->unk10.m[3][0] = sdData->unk2B8;
        temp_fp->unk10.m[3][1] = sdData->unk2BC;
        temp_fp->unk10.m[3][2] = sdData->unk2C0 - 5.0f;
        temp_fp->unk50 = 0.0f;
        temp_fp->unk70 = hudAddWaypoint(temp_fp->unk10.m[3][0], temp_fp->unk10.m[3][1], temp_fp->unk10.m[3][2]);
    }
    sdData->shadowObjId = uvDobjAllocIdx();
    uvDobjModel(sdData->shadowObjId, MODEL_SKYDIVING_SHADOW);
    uvDobjState(sdData->shadowObjId, 2);
}
