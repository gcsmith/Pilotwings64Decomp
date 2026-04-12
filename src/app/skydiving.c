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

void skydivingLoadPilot(u8 pilot, SkyDivingData* arg1);
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

void func_8032FACC(u8 contIdx, u8 pilot, SkyDivingData* arg2, Camera* arg3) {
    uvMemSet(arg2, 0, sizeof(SkyDivingData));
    skydivingLoadPilot(pilot, arg2);
    arg2->objId = uvDobjAllocIdx();
    arg2->unk2 = 2;
    uvDobjModel(arg2->objId, arg2->unk1C0);
    uvDobjPosm(arg2->objId, 0, &arg2->unk10);
    uvDobjState(arg2->objId, arg2->unk2);
    arg2->contIdx = contIdx;
    arg2->unk50 = arg3;
    arg2->unk22F = 0;
    arg2->unk4 = 0xFFFF;
    arg2->unk1AC = 0.0f;
    arg2->unk1B0 = 0.0f;
    arg2->unk1B4 = 0.0f;
    arg2->unk1B8 = 0.0f;
    arg2->unk1BC = 0.0f;
    arg2->unk5C = 0.0f;
    arg2->unk60 = 0.0f;
    arg2->unk64 = 0.0f;
    arg2->unk250 = 11.0f;
    arg2->unk254 = 1.0f;
    func_80332C60(arg2);
    sdSoundInit(arg2);
    db_getstart(&arg2->unk10, &arg2->unk154, NULL, NULL);
    arg2->unk10.m[3][2] -= 1000.0f;
    arg2->unk2B8 = arg2->unk10.m[3][0];
    arg2->unk2BC = arg2->unk10.m[3][1];
    arg2->unk2C0 = arg2->unk10.m[3][2];
    func_803329C0(arg2);
}

void skydivingEnterLeave(SkyDivingData* arg0) {
    if (D_80362690->state == GAME_STATE_RESULTS) {
        return;
    }
    arg0->unk310 = D_80362690->terraId;
    D_80362690->terraId = 9;
    uvChanTerra(arg0->unk50->unk22C, 9);
    uvChanEnv(arg0->unk50->unk22C, 1);
    db_getstart(&arg0->unk10, &arg0->unk154, NULL, NULL);
    arg0->unk10.m[3][2] -= 1000.0f;
    uvDobjPosm(arg0->objId, 0, &arg0->unk10);
    arg0->unk2B8 = arg0->unk10.m[3][0];
    arg0->unk2BC = arg0->unk10.m[3][1];
    arg0->unk2C0 = arg0->unk10.m[3][2];
    func_80332D94(arg0);
    arg0->unk70 = 0;
    arg0->unk25C = 0;
    arg0->unk68 = 0.0f;
    arg0->unk6C = 0.0f;
    arg0->unk26C = 0.0f;
    arg0->unk298 = 0.0f;
    arg0->unk284 = 0.0f;
    arg0->unk2B4 = 0.0f;
    arg0->unk288 = 0.0f;
    arg0->unk2C4 = 0.0f;
    arg0->unk268 = 1.0f;
    D_80371960 = 0;
    D_80371964 = 0;
    D_80371968 = 0;
    arg0->unk258 = &D_8034FFD0[D_80362690->unkC[D_80362690->unk9C].cls];
    arg0->unk2 = 2;
    uvDobjState(arg0->objId, arg0->unk2);
    arg0->unk58 = 0.5f;
    arg0->unk50->unk1 = arg0->unk54 = 5;
    arg0->unk50->unk4 = arg0->objId;
    arg0->unk50->unk6 = arg0->unk2;
    arg0->unk50->unk68.x = arg0->unk20C;
    arg0->unk50->unk68.y = arg0->unk210;
    arg0->unk50->unk68.z = arg0->unk214;
    arg0->unk50->unk74 = 0.0f;
    arg0->unk50->unk1B4 = 5.0f;
    arg0->unk50->unk1B8 = 6.0f;
    arg0->unk50->unk228 = 0.0f;
    arg0->unk50->unk8 = 1.0f;
    arg0->unk27A = 0;
    arg0->unk294 = 0.5f;
    arg0->unk290 = 0.5f;
    func_802D45C4(arg0->unk50, arg0->unk58);
    padsDeinit();
    level_8030B964();
}

void func_8032FE4C(SkyDivingData* arg0) {
    if (arg0->shadowObjId != 0xFFFF) {
        uvDobjModel(arg0->shadowObjId, 0xFFFF);
    }
    uvDobjModel(arg0->objId, 0xFFFF);
    arg0->contIdx = 0xFFFF;
    arg0->objId = 0xFFFF;
    func_80332950();
}

void func_8032FEAC(SkyDivingData* arg0, s32 arg1, u8 arg2) {
    s32 var_a0;
    Mtx4F sp34;
    f32 var_fa0;

    uvMat4Copy(&sp34, &arg0->unk10);
    sp34.m[3][0] = arg0->unk10.m[3][0] + ((2.0f * D_8034F854) * arg0->unk160.x);
    sp34.m[3][1] = arg0->unk10.m[3][1] + ((2.0f * D_8034F854) * arg0->unk160.y);
    sp34.m[3][2] = arg0->unk10.m[3][2] + ((2.0f * D_8034F854) * arg0->unk160.z);
    sp34.m[1][0] = 2.0f;
    sp34.m[1][1] = 2.0f;
    sp34.m[1][2] = 2.0f;
    if ((arg0->unk26C <= D_8034F850) && (arg0->unk10.m[3][2] > 100.0f) && (arg0->unk70 == 0)) {
        mist_803144D0(&sp34, NULL);
        arg0->unk26C = (D_8034F850 + 0.25f) - (ABS_NOEQ(arg0->unk274) * 0.25f);
    }
    uvMat4SetIdentity(&sp34);
    var_a0 = 0;
    if (arg0->unk264 == 1.0f) {
        if (arg0->unk10.m[3][2] < 100.0f) {
            var_a0 = 255 - (s32)(SQ(arg0->unk10.m[3][2] / 100.0f) * 255.0f);
        }
    } else {
        if (arg0->unk10.m[3][2] > 950.0f) {
            var_a0 = 255 - (s32)(((1000.0f - arg0->unk10.m[3][2]) * 255.0f) / 50.0f);
        }
    }
    if (var_a0 < 0) {
        var_a0 = 0;
    } else if (var_a0 > 255) {
        var_a0 = 255;
    }
    hudSetCameraState(var_a0);
    if ((arg0->unk264 != 1.0f) && (arg0->unk27A == 0) && (arg0->unk10.m[3][2] < 900.0f) && (arg0->unk25C == 0)) {
        sndPlaySfx(5);
        hudWarningText(0x132, 3.0f, 8.0f);
        arg0->unk25C = 1;
    }
    if (arg0->unk70 == 0) {
        arg1 &= ~0xF;
    }
    if (arg1 & 2) {
        var_fa0 = 1.5707963f;
    } else if (arg1 & 1) {
        var_fa0 = -1.5707963f;
    } else {
        var_fa0 = 0.0f;
    }
    arg0->unk68 = func_80313AF4(var_fa0, arg0->unk68, 2.0f);
    if (arg1 & 4) {
        var_fa0 = 0.7853981f;
    } else if (arg1 & 8) {
        var_fa0 = -0.7853981f;
    } else {
        var_fa0 = 0.0f;
    }
    arg0->unk6C = func_80313AF4(var_fa0, arg0->unk6C, 2.0f);
    if (arg2 != 6) {
        arg0->unk54 = 4;
        arg0->unk50->unk4 = arg0->objId;
        arg0->unk50->unk6 = arg0->unk2;
        arg0->unk50->unk78 = arg0->unk68;
        arg0->unk50->unk7C = arg0->unk6C;
        arg0->unk50->unk0 = 0;
        sp34.m[3][0] = arg0->unk10.m[3][0];
        sp34.m[3][1] = arg0->unk10.m[3][1];
        sp34.m[3][2] = arg0->unk10.m[3][2];
        if (arg0->unk70 != 0) {
            arg0->unk50->unk0 |= 8;
        }
        if (arg0->unk70 == 0) {
            arg0->unk50->unk1B4 = func_80313AF4(1.5f - ((arg0->unk160.z - -7.0f) * 0.2f), arg0->unk50->unk1B4, 5.0f);
            uvMat4RotateAxis(&sp34, -1.5707963f, 'x');
            uvMat4RotateAxis(&sp34, arg0->unk5C, 'y');
            arg0->unk50->unk1B0 = 1.5707963f;
        } else if (arg0->unk70 == 1) {
            arg0->unk50->unk1B4 = func_80313AF4(26.5f - ((arg0->unk160.z - -7.0f) * 1.8f), arg0->unk50->unk1B4, 5.0f);
            uvMat4RotateAxis(&sp34, -arg0->unk5C, 'z');
            if (demoButtonPress(0, R_TRIG) != 0) {
                sndPlaySfxVolPitchPan(0x67, 0.3f, 0.65f, 0.0f);
                if (arg0->unk290 == 1.0f) {
                    arg0->unk290 = 0.5f;
                } else {
                    arg0->unk290 = 1.0f;
                }
            }
            arg0->unk294 = func_80313AF4(arg0->unk290, arg0->unk294, 1.0f);
            arg0->unk50->unk1B0 = uvCosF(arg0->unk298 * 6.2831855f) * (arg0->unk294 * 1.5707963f);
            if (arg0->unk298 > 0.52f) {
                arg0->unk298 = func_80313AF4(0.5f, arg0->unk298, 2.0f);
                if (arg0->unk50->unk108.m[3][2] < 2.0f) {
                    arg0->unk50->unk108.m[3][2] = 2.0f;
                }
            } else {
                arg0->unk298 = func_80313AF4(0.0f, arg0->unk298, 0.3f);
            }
            sp34.m[3][2] += 2.0f;
        } else if (arg0->unk70 == 4) {
            arg0->unk50->unk1B4 = func_80313AF4(6.0f, arg0->unk50->unk1B4, 1.0f);
            if (arg0->unk50->unk1B4 <= 6.2f) {
                arg0->unk70 = 2;
            }
        } else if (arg0->unk70 == 5) {
            arg0->unk50->unk1B4 = func_80313AF4(6.0f, arg0->unk50->unk1B4, 1.0f);
            if (arg0->unk50->unk1B4 <= 6.2f) {
                arg0->unk70 = 3;
            }
            uvMat4CopyXYZ(&sp34, &arg0->unk10);
        }
        if ((D_80371960 != 0) && (arg0->unk264 == 1.0f)) {
            sp34.m[3][0] = func_80313AF4(sp34.m[3][0], arg0->unk50->unk80.m[3][0], 5.0f);
            sp34.m[3][1] = func_80313AF4(sp34.m[3][1], arg0->unk50->unk80.m[3][1], 5.0f);
        }
        uvMat4Copy(&arg0->unk50->unk80, &sp34);
        func_802D5884(arg0->unk50, arg0->unk54);
    }
    arg0->unk50->unk228 = (arg0->unk50->unk108.m[3][2] - D_80371970[0].unk10.m[3][2]) - 1.5f;
}

void func_803305D4(SkyDivingData* arg0) {
    s32 i;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fv0;
    f32 var_fs0;
    f32 var_fs3;
    f32 var_fs4;
    f32 sp68;

    sp68 = (3.1415925f * D_8034F854) / 0.6f;
    arg0->unk2B4 -= sp68;
    if (arg0->unk2B4 < 0.0f) {
        sp68 += arg0->unk2B4;
    }

    var_fs3 = 0.0f;
    var_fs4 = 0.0f;

    for (i = 0; i < 3; i++) {
        var_fs3 += arg0->unk258->unk0[i];
        var_fs4 += arg0->unk258->unk10[i];
    }
    var_fs3 += arg0->unk258->unkC;
    var_fs4 += arg0->unk258->unk1C;
    var_fs3 *= 0.25f;
    var_fs4 *= 0.25f;
    var_fs3 += arg0->unk2B8;
    var_fs4 += arg0->unk2BC;

    arg0->unk50->unk80.m[3][0] = func_80313AF4(var_fs3, arg0->unk50->unk80.m[3][0], 3.0f);
    arg0->unk50->unk80.m[3][1] = func_80313AF4(var_fs4, arg0->unk50->unk80.m[3][1], 3.0f);

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
    temp_fs0 = arg0->unk10.m[3][0] - var_fs3;
    temp_fs1 = arg0->unk10.m[3][1] - var_fs4;
    temp_fv0 = uvSqrtF(SQ(temp_fs0) + SQ(temp_fs1));
    if (temp_fv0 != 0.0f) {
        temp_fs0 /= temp_fv0;
        temp_fs1 /= temp_fv0;
        var_fs0 = uvAtan2F(temp_fs1, temp_fs0) + sp68;
    } else {
        var_fs0 = 0.0f;
    }
    arg0->unk10.m[3][0] = (uvCosF(var_fs0) * temp_fv0) + var_fs3;
    arg0->unk10.m[3][1] = (uvSinF(var_fs0) * temp_fv0) + var_fs4;
    uvMat4RotateAxis(&arg0->unk10, -sp68, 'y');
    uvDobjPosm(arg0->objId, 0, &arg0->unk10);
    arg0->unk2B4 -= sp68;
    if (arg0->unk2B4 <= 0.0f) {
        func_80331EB8(arg0);
        arg0->unk2B4 = 0.0f;
        arg0->unk288 = 0.0f;
    }
}

void skydivingMovementFrame(SkyDivingData* arg0, u8 gameState) {
    f32 stickX;
    f32 stickY;
    s32 buttons;
    Mtx4F sp34;

    if (arg0->unk2B4 > 0.0f) {
        func_803305D4(arg0);
        return;
    }

    if (arg0->unk70 == 3) {
        func_803316B0(arg0);
        return;
    }
    if ((arg0->unk70 == 4) || (arg0->unk70 == 5)) {
        skydivingLand(arg0);
        func_8032FEAC(arg0, 0, gameState);
        return;
    }
    if (fdr_802E6B5C() != 4) {
        if (gameState == GAME_STATE_RESULTS) {
            buttons = 0;
            stickY = 0.0f;
            stickX = 0.0f;
        } else {
            stickX = demoGetInputs(arg0->contIdx, INPUT_AXIS_X);
            stickY = demoGetInputs(arg0->contIdx, INPUT_AXIS_Y);
            buttons = demoGetButtons(arg0->contIdx);
        }
        arg0->unk270 = stickX;
        arg0->unk274 = stickY;
        if (stickY < 0.0f) {
            arg0->unk274 *= 0.75f;
        }
        if (gameState != GAME_STATE_RESULTS) {
            func_80332E90(arg0);
        }
        func_8032F3DC(arg0);
        if ((arg0->unk70 == 1) && (arg0->unk270 != 0.0f)) {
            if (D_8037196C == 0) {
                sndPlaySfxVolPitchPan(0x5F, 0.5f, 0.25f, 0.0f);
                D_8037196C = 1;
            }
        } else {
            D_8037196C = 0;
        }
        if (arg0->unk70 == 0) {
            arg0->unk64 = func_80313AF4(stickX, arg0->unk64, 1.0f);
        } else {
            arg0->unk64 = func_80313AF4(0.0f, arg0->unk64, 1.0f);
        }

        uvMat4Copy(&sp34, &arg0->unk10);
        uvMat4RotateAxis(&sp34, arg0->unk64 * 0.6f, 'z');
        uvDobjPosm(arg0->objId, 0, &sp34);
        func_803322CC(arg0);
        if (gameState != GAME_STATE_RESULTS) {
            func_803318D4(arg0);
        }
        func_8032FEAC(arg0, buttons, gameState);
        func_80331FE4(arg0);
        arg0->unk24C = 0;
        padsLandedPadStrip(arg0->unk10.m[3][0], arg0->unk10.m[3][1], arg0->unk10.m[3][2], &arg0->unk24C);
        if (arg0->unk24C != 0) {
            arg0->unk4 |= 4;
        } else {
            arg0->unk4 &= ~4;
        }
        if (gameState != GAME_STATE_RESULTS) {
            if (arg0->unk70 == 3) {
                fdr_802E66DC();
            }
            fdr_802E65AC(&arg0->unk10, &D_80362690->terraId, &stickX, &stickY, &buttons);
        }
    }
}

void skydivingLoadPilot(u8 pilot, SkyDivingData* arg1) {
    switch (pilot) {
    case PILOT_LARK:
        arg1->unk1C4.x = -0.025f, arg1->unk1C4.y = 0.097f, arg1->unk1C4.z = 0.675f;
        arg1->unk1D0.x = 0.0f, arg1->unk1D0.y = 0.0f, arg1->unk1D0.z = -0.745f;
        arg1->unk1DC.x = -0.027f, arg1->unk1DC.y = 0.442f, arg1->unk1DC.z = 0.012f;
        arg1->unk1E8.x = -0.024f, arg1->unk1E8.y = -0.27f, arg1->unk1E8.z = 0.101f;
        arg1->unk1F4.x = -0.54f, arg1->unk1F4.y = -0.156f, arg1->unk1F4.z = 0.105f;
        arg1->unk200.x = 0.486f, arg1->unk200.y = -0.156f, arg1->unk200.z = 0.105f;
        arg1->unk20C = -0.025f;
        arg1->unk210 = 0.307f;
        arg1->unk214 = 0.478f;
        arg1->unk218 = 0.6f;
        arg1->unk1C0 = MODEL_SKYDIVING_LARK;
        arg1->unk278 = MODEL_PARACHUTE_LARK;
        arg1->unk227 = 5;
        arg1->unk21C = 1;
        arg1->unk21D = 3;
        arg1->unk21E = 9;
        arg1->unk21F = 10;
        arg1->unk220 = 11;
        arg1->unk221 = 6;
        arg1->unk222 = 7;
        arg1->unk223 = 8;
        arg1->unk226 = 12;
        arg1->unk228 = 18;
        arg1->unk229 = 19;
        arg1->unk22A = 17;
        arg1->unk22B = 16;
        arg1->unk22E = 15;
        arg1->unk22C = 4;
        arg1->unk22D = 7;
        arg1->unk1A4 = 0x50;
        arg1->unk1A0 = 0x52;
        arg1->unk1A2 = 0x51;
        arg1->unk1A6 = 0x54;
        arg1->unk1A8 = 0x53;
        arg1->unk2A0 = 1.5f;
        arg1->unk2A8 = 1.0f;
        arg1->unk2AC = 1.0f;
        arg1->unk2B0 = 1.0f;
        break;
    case PILOT_GOOSE:
        arg1->unk1C4.x = -0.001f, arg1->unk1C4.y = 0.172f, arg1->unk1C4.z = 0.782f;
        arg1->unk1D0.x = 0.0f, arg1->unk1D0.y = 0.0f, arg1->unk1D0.z = -1.336f;
        arg1->unk1DC.x = 0.001f, arg1->unk1DC.y = 0.647f, arg1->unk1DC.z = -0.002f;
        arg1->unk1E8.x = -0.001f, arg1->unk1E8.y = -0.341f, arg1->unk1E8.z = 0.19f;
        arg1->unk1F4.x = -0.722f, arg1->unk1F4.y = -0.178f, arg1->unk1F4.z = 0.148f;
        arg1->unk200.x = 0.73f, arg1->unk200.y = -0.178f, arg1->unk200.z = 0.148f;
        arg1->unk20C = 0.0f;
        arg1->unk210 = 0.315f;
        arg1->unk214 = 0.603f;
        arg1->unk218 = 0.6f;
        arg1->unk1C0 = MODEL_SKYDIVING_GOOSE;
        arg1->unk278 = MODEL_PARACHUTE_GOOSE;
        arg1->unk227 = 5;
        arg1->unk21C = 1;
        arg1->unk21D = 3;
        arg1->unk21E = 9;
        arg1->unk21F = 10;
        arg1->unk220 = 11;
        arg1->unk221 = 6;
        arg1->unk223 = 8;
        arg1->unk226 = 12;
        arg1->unk228 = 18;
        arg1->unk222 = 7;
        arg1->unk229 = 19;
        arg1->unk22A = 17;
        arg1->unk22B = 16;
        arg1->unk22E = 15;
        arg1->unk22C = 4;
        arg1->unk22D = 7;
        arg1->unk1A4 = 0x56;
        arg1->unk1A0 = 0x58;
        arg1->unk1A2 = 0x57;
        arg1->unk1A6 = 0x5A;
        arg1->unk1A8 = 0x59;
        arg1->unk2A0 = 1.8f;
        arg1->unk2A8 = 1.150f;
        arg1->unk2AC = 0.850f;
        arg1->unk2B0 = 1.1500f;
        break;
    case PILOT_HAWK:
        arg1->unk1C4.x = 0.003f, arg1->unk1C4.y = 0.187f, arg1->unk1C4.z = 0.634f;
        arg1->unk1D0.x = 0.0f, arg1->unk1D0.y = 0.0f, arg1->unk1D0.z = -1.221f;
        arg1->unk1DC.x = -0.01f, arg1->unk1DC.y = 0.698f, arg1->unk1DC.z = -0.013f;
        arg1->unk1E8.x = -0.004f, arg1->unk1E8.y = -0.43f, arg1->unk1E8.z = -0.117f;
        arg1->unk1F4.x = -0.819f, arg1->unk1F4.y = -0.245f, arg1->unk1F4.z = 0.069f;
        arg1->unk200.x = 0.837f, arg1->unk200.y = -0.245f, arg1->unk200.z = 0.069f;
        arg1->unk20C = 0.002f;
        arg1->unk210 = 0.325f;
        arg1->unk214 = 0.52f;
        arg1->unk218 = 0.6f;
        arg1->unk1C0 = MODEL_SKYDIVING_HAWK;
        arg1->unk278 = MODEL_PARACHUTE_HAWK;
        arg1->unk227 = 5;
        arg1->unk21C = 1;
        arg1->unk21D = 3;
        arg1->unk21E = 9;
        arg1->unk21F = 10;
        arg1->unk220 = 11;
        arg1->unk221 = 6;
        arg1->unk222 = 7;
        arg1->unk223 = 8;
        arg1->unk226 = 12;
        arg1->unk228 = 18;
        arg1->unk229 = 19;
        arg1->unk22A = 17;
        arg1->unk22B = 16;
        arg1->unk22E = 15;
        arg1->unk22C = 4;
        arg1->unk22D = 7;
        arg1->unk1A4 = 0x5B;
        arg1->unk1A0 = 0x5D;
        arg1->unk1A2 = 0x5C;
        arg1->unk1A6 = 0x5F;
        arg1->unk1A8 = 0x5E;
        arg1->unk2A0 = 1.6f;
        arg1->unk2A8 = 0.85f;
        arg1->unk2AC = 1.150f;
        arg1->unk2B0 = 0.85f;
        break;
    case PILOT_KIWI:
        arg1->unk1C4.x = 0.002f, arg1->unk1C4.y = 0.084f, arg1->unk1C4.z = 0.706f;
        arg1->unk1D0.x = 0.0f, arg1->unk1D0.y = 0.0f, arg1->unk1D0.z = -0.828f;
        arg1->unk1DC.x = 0.0f, arg1->unk1DC.y = 0.426f, arg1->unk1DC.z = 0.03f;
        arg1->unk1E8.x = 0.0f, arg1->unk1E8.y = -0.261f, arg1->unk1E8.z = 0.107f;
        arg1->unk1F4.x = -0.479f, arg1->unk1F4.y = -0.153f, arg1->unk1F4.z = 0.079f;
        arg1->unk200.x = 0.489f, arg1->unk200.y = -0.153f, arg1->unk200.z = 0.079f;
        arg1->unk20C = 0.002f;
        arg1->unk210 = 0.308f;
        arg1->unk214 = 0.473f;
        arg1->unk218 = 0.6f;
        arg1->unk1C0 = MODEL_SKYDIVING_KIWI;
        arg1->unk278 = MODEL_PARACHUTE_KIWI;
        arg1->unk227 = 5;
        arg1->unk21C = 1;
        arg1->unk21D = 3;
        arg1->unk21E = 9;
        arg1->unk21F = 10;
        arg1->unk220 = 11;
        arg1->unk221 = 6;
        arg1->unk223 = 8;
        arg1->unk226 = 12;
        arg1->unk228 = 18;
        arg1->unk222 = 7;
        arg1->unk229 = 19;
        arg1->unk22A = 17;
        arg1->unk22B = 16;
        arg1->unk22E = 15;
        arg1->unk22C = 4;
        arg1->unk22D = 7;
        arg1->unk1A4 = 0x60;
        arg1->unk1A0 = 0x4D;
        arg1->unk1A2 = 0x61;
        arg1->unk1A6 = 0x63;
        arg1->unk1A8 = 0x62;
        arg1->unk2A0 = 1.4f;
        arg1->unk2A8 = 1.0f;
        arg1->unk2AC = 1.0f;
        arg1->unk2B0 = 1.0f;
        break;
    case PILOT_IBIS:
        arg1->unk1C4.x = -0.002f, arg1->unk1C4.y = 0.085f, arg1->unk1C4.z = 0.799f;
        arg1->unk1D0.x = 0.f, arg1->unk1D0.y = 0.0f, arg1->unk1D0.z = -1.36f;
        arg1->unk1DC.x = 0.0f, arg1->unk1DC.y = 0.586f, arg1->unk1DC.z = -0.034f;
        arg1->unk1E8.x = 0.0f, arg1->unk1E8.y = -0.314f, arg1->unk1E8.z = 0.091f;
        arg1->unk1F4.x = -0.666f, arg1->unk1F4.y = -0.164f, arg1->unk1F4.z = 0.141f;
        arg1->unk200.x = 0.678f, arg1->unk200.y = -0.164f, arg1->unk200.z = 0.141f;
        arg1->unk20C = 0.0f;
        arg1->unk210 = 0.212f;
        arg1->unk214 = 0.599f;
        arg1->unk218 = 0.6f;
        arg1->unk1C0 = MODEL_SKYDIVING_IBIS;
        arg1->unk278 = MODEL_PARACHUTE_IBIS;
        arg1->unk227 = 5;
        arg1->unk21C = 1;
        arg1->unk21D = 3;
        arg1->unk21E = 9;
        arg1->unk21F = 10;
        arg1->unk220 = 11;
        arg1->unk221 = 6;
        arg1->unk223 = 8;
        arg1->unk226 = 12;
        arg1->unk228 = 18;
        arg1->unk222 = 7;
        arg1->unk229 = 19;
        arg1->unk22A = 17;
        arg1->unk22B = 16;
        arg1->unk22E = 15;
        arg1->unk22C = 4;
        arg1->unk22D = 7;
        arg1->unk1A4 = 0x64;
        arg1->unk1A0 = 0x4E;
        arg1->unk1A2 = 0x65;
        arg1->unk1A6 = 0x67;
        arg1->unk1A8 = 0x66;
        arg1->unk2A0 = 1.8f;
        arg1->unk2A8 = 1.150f;
        arg1->unk2AC = 0.850f;
        arg1->unk2B0 = 1.15f;
        break;
    case PILOT_ROBIN:
        arg1->unk1C4.x = -0.001f, arg1->unk1C4.y = 0.095f, arg1->unk1C4.z = 0.844f;
        arg1->unk1D0.x = 0.0f, arg1->unk1D0.y = 0.0f, arg1->unk1D0.z = -1.076f;
        arg1->unk1DC.x = 0.0f, arg1->unk1DC.y = 0.563f, arg1->unk1DC.z = -0.018f;
        arg1->unk1E8.x = 0.0f, arg1->unk1E8.y = -0.433f, arg1->unk1E8.z = 0.155f;
        arg1->unk1F4.x = -0.737f, arg1->unk1F4.y = -0.266f, arg1->unk1F4.z = 0.112f;
        arg1->unk200.x = 0.751f, arg1->unk200.y = -0.266f, arg1->unk200.z = 0.112f;
        arg1->unk20C = 0.0f;
        arg1->unk210 = 0.217f;
        arg1->unk214 = 0.621f;
        arg1->unk218 = 0.6f;
        arg1->unk1C0 = MODEL_SKYDIVING_ROBIN;
        arg1->unk278 = MODEL_PARACHUTE_ROBIN;
        arg1->unk227 = 5;
        arg1->unk21C = 1;
        arg1->unk21D = 3;
        arg1->unk21E = 9;
        arg1->unk21F = 10;
        arg1->unk220 = 11;
        arg1->unk221 = 6;
        arg1->unk222 = 7;
        arg1->unk223 = 8;
        arg1->unk226 = 12;
        arg1->unk228 = 18;
        arg1->unk229 = 19;
        arg1->unk22A = 17;
        arg1->unk22B = 16;
        arg1->unk22E = 15;
        arg1->unk22C = 4;
        arg1->unk22D = 7;
        arg1->unk1A4 = 0x68;
        arg1->unk1A0 = 0x4F;
        arg1->unk1A2 = 0x69;
        arg1->unk1A6 = 0x6B;
        arg1->unk1A8 = 0x6A;
        arg1->unk2A0 = 1.6f;
        arg1->unk2A8 = 0.85f;
        arg1->unk2AC = 1.15f;
        arg1->unk2B0 = 0.85f;
        break;
    }
    uvModelGetPosm(arg1->unk278, arg1->unk228, &arg1->unk2D0);
}

void func_803316B0(SkyDivingData* arg0) {
    f32 var_fv1;
    f32 x;
    f32 y;
    f32 z;

    if (arg0->unk22F == 0) {
        arg0->unk22F = 1;
        if (arg0->unkB8 != 0) {
            if (arg0->unk27A != 0) {
                var_fv1 = 5.0f;
            } else {
                var_fv1 = 2.0f;
            }
            if (arg0->unk50->unk108.m[3][2] > 0.0f) {
                x = arg0->unk10.m[3][0];
                y = arg0->unk10.m[3][1];
                z = arg0->unk10.m[3][2];
                func_802F8AB8(x, y, z, var_fv1, &arg0->unk160);
            }
            arg0->unk2 = 0;
            arg0->unk50->unk6 = 0;
            uvDobjState(arg0->objId, arg0->unk2);
            uvMat4Copy(&arg0->unk50->unk80, &arg0->unk10);
        }
    }
    hudGetState()->renderFlags = 0;
    func_8032F47C(arg0);
}

void skydivingLand(SkyDivingData* arg0) {
    TaskLPAD* sp34;
    u8 temp_v0;
    f32 temp_ft4;
    f32 temp_fa1;

    if (arg0->unk2C4 == 0.0f) {
        sndPlaySfx(0x48);
        temp_v0 = taskGetLPAD(&sp34);
        if (temp_v0 != 1) {
            _uvDebugPrintf("sdive_land: tell mikep != 1 pad\n");
        } else {
            temp_ft4 = sp34->pos.x;
            temp_fa1 = sp34->pos.y;
            D_80371964 = uvSqrtF(SQ(arg0->unk10.m[3][0] - temp_ft4) + SQ(arg0->unk10.m[3][1] - temp_fa1));
        }
        D_80371968 = -arg0->unk160.z;
        arg0->unk2C4 = -arg0->unk160.z;
    }

    if ((arg0->unk70 != 5) && (arg0->unk70 != 3)) {
        if (D_80371964 >= 0x1A) {
            hudText_8031D8E0(0xB2, 1.5f, 8.0f);
            arg0->unk25E = 0;
        } else {
            hudText_8031D8E0(0xCB, 1.5f, 8.0f);
            arg0->unk25E = 1;
        }
    }
    hudGetState()->renderFlags = 0;
    func_8032F47C(arg0);
}

void func_803318D4(SkyDivingData* arg0) {
    HUDState* temp_v0;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_ft4;
    s32 i;

    temp_v0 = hudGetState();
    uvMat4Copy(&temp_v0->unk28, &arg0->unk10);
    temp_v0->renderFlags = HUD_RENDER_SKYDIVING;
    temp_v0->unk8C = arg0->unk160.z * 4.0f * 0.7f;
    temp_v0->speed = arg0->unk16C * 3.6f * 0.7f;
    temp_v0->att.x = arg0->unk10.m[3][0];
    temp_v0->att.y = arg0->unk10.m[3][1];
    temp_v0->att.heading = arg0->unk10.m[3][2];
    temp_v0->att.pitch = arg0->unk5C;
    temp_v0->elapsedTime = D_8034F850;
    temp_v0->altSeaLevel = arg0->unk10.m[3][2];
    if (arg0->unk264 == 1.0f) {
        temp_v0->altitude = 101.0f;
    } else {
        temp_v0->altitude = arg0->unk280;
    }
    if (arg0->unk264 == 1.0f) {
        temp_v0->altSeaLevel += 1000.0f;
    }
    if (arg0->unk258 != NULL) {
        for (i = 0; i < 3; i++) {
            temp_fa0 = (200.0f * (D_80371970[i].unk10.m[3][0] - arg0->unk10.m[3][0])) + arg0->unk10.m[3][0];
            temp_fa1 = (200.0f * (D_80371970[i].unk10.m[3][1] - arg0->unk10.m[3][1])) + arg0->unk10.m[3][1];
            temp_ft4 = D_80371970[i].unk10.m[3][2];

            hudMoveWaypoint(D_80371970[i].unk70, temp_fa0, temp_fa1, temp_ft4);
        }
        return;
    }
    temp_v0->radar.unk4 = 0;
}

s32 skydivingGetPoints(s32 arg0) {
    switch (arg0) {
    case 1:
        return D_80371960;
    case 2:
        return D_80371964;
    case 3:
        return D_80371968;
    default:
        _uvDebugPrintf("sdive_getpoints: unknown type %d\n", arg0);
        return 0;
    }
}

void func_80331AE4(SkyDivingData* arg0) {
    uvDobjModel(arg0->objId, arg0->unk278);
    uvDobjState(arg0->objId, arg0->unk2);
    arg0->unk70 = 1;
    arg0->unk58 = 1.57f;
    arg0->unk160.x = 0.0f;
    arg0->unk160.y = 0.0f;
    arg0->unk160.z = 0.0f;
    func_802D45C4(arg0->unk50, arg0->unk58);
    arg0->unk298 = 1.0f;
    arg0->unk29C = 0.1f;
    arg0->unk27A = 1;
    sndPlaySfx(0x49);
    arg0->unk21F = 0xA;
    arg0->unk222 = 0xD;
}

void skydivingBelow(SkyDivingData* arg0) {
    s32 var_a1;
    s32 i;

    func_802D45C4(arg0->unk50, arg0->unk58);
    arg0->unk160.x = 0.0f;
    arg0->unk160.y = 0.0f;
    arg0->unk160.z = 0.0f;
    arg0->unk10.m[3][2] = 1000.0f;
    D_80362690->terraId = arg0->unk310;
    uvChanTerra(arg0->unk50->unk22C, D_80362690->terraId);
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
        uvChanEnv(arg0->unk50->unk22C, var_a1);
    }
    for (i = 0; i < 3; i++) {
        if (D_80371970[i].unk0 != 0xFFFF) {
            uvDobjModel(D_80371970[i].unk0, 0xFFFF);
            D_80371970[i].unk0 = 0xFFFF;
        }

        if (arg0->shadowObjId != 0xFFFF) {
            uvDobjModel(arg0->shadowObjId, 0xFFFF);
        }
    }
    arg0->unk258 = 0;
    arg0->unk264 = arg0->unk10.m[3][2] * 0.05f;
    padsLoad();
    level_8030B868();

    if (D_80371960 != 0x32) {
        for (i = 0; i < 3; i++) {
            hud_8031A8E0(D_80371970[i].unk70);
        }
    }
}

s32 func_80331D58(SkyDivingData* arg0) {
    Unk8034FFD0* temp_v0;

    temp_v0 = arg0->unk258;

    if (temp_v0->unk38 < ABS_NOEQ(-arg0->unk5C - temp_v0->unk2C)) {
        return 0;
    }

    if (temp_v0->unk3C < ABS_NOEQ(arg0->unk60 - 1.5707963f)) {
        return 0;
    }

    if (temp_v0->unk30 < uvSqrtF(SQ(arg0->unk10.m[3][0] - (temp_v0->unkC + arg0->unk2B8)) + SQ(arg0->unk10.m[3][1] - (temp_v0->unk1C + arg0->unk2BC)))) {
        return 0;
    }

    if (temp_v0->unk34 < ABS_NOEQ(arg0->unk10.m[3][2] - D_80371970[0].unk10.m[3][2])) {
        return 0;
    }
    return 1;
}

void func_80331EB8(SkyDivingData* arg0) {
    s32 i;

    if (arg0->unk258->unk48 == 0xFF) {
        arg0->unk258 = NULL;
        for (i = 0; i < 3; i++) {
            hud_8031A8E0(D_80371970[i].unk70);
        }
    } else {
        arg0->unk258 = &D_8034FFD0[arg0->unk258->unk48];
    }

    for (i = 0; i < 3; i++) {
        D_80371970[i].unkC += -10.0f;
        D_80371970[i].unk4 += 8.0f * uvCosF(i * 1.5707963f);
        D_80371970[i].unk8 += 8.0f * uvSinF(i * 1.5707963f);
    }
}

void func_80331FE4(SkyDivingData* arg0) {
    static s32 D_80371B40;
    s16 sp2E;
    s16* sp28;

    sp2E = -1;
    if (arg0->unk258 != NULL) {
        arg0->unk288 += D_8034F854;
        arg0->unkB9 = func_80331D58(arg0);
        if (arg0->unkB9) {
            if (arg0->unk260 < 0.0f) {
                D_80371B40 = 3;
                arg0->unk260 = D_8034F850;
            }
            if ((D_8034F850 - arg0->unk260) > 0.1f) {
                arg0->unk288 = 100.0f;
            }
            uvFontSet(6);
            uvFontScale(1.0, 1.0);
            uvFontColor(0xFF, 0xFF, 0, 0xFF);

            if ((D_8034F850 - arg0->unk260) < (0.3333f * arg0->unk258->unk40)) {
                if (D_80371B40 == 3) {
                    D_80371B40--;
                    sndPlaySfxVolPitchPan(0x59, 0.8f, 1.0f, 0.0f);
                }
                sp2E = 9;
            } else if ((D_8034F850 - arg0->unk260) < (0.6667f * arg0->unk258->unk40)) {
                if (D_80371B40 == 2) {
                    D_80371B40--;
                    sndPlaySfxVolPitchPan(0x59, 0.8f, 1.0f, 0.0f);
                }
                sp2E = 0x76;
            } else if ((D_8034F850 - arg0->unk260) < arg0->unk258->unk40) {
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

            if (arg0->unk258->unk40 <= (D_8034F850 - arg0->unk260)) {
                D_80371960 += arg0->unk258->unk44;
                arg0->unk2B4 = 12.566371f;
                arg0->unk260 = -1.0f;
                hudWarningText(6, 1.5f, 8.0f);
                sndPlaySfx(SFX_UI_TEST_START);
            }
        } else {
            arg0->unk260 = -1.0f;
        }
    }
}

void func_803322CC(SkyDivingData* arg0) {
    f32 var_fs0;
    f32 var_fs1;
    f32 var_fs3;
    Unk80371970* spC8;
    Mtx4F sp88;
    Unk8034FFD0* temp_v0;
    s32 i;

    temp_v0 = arg0->unk258;
    if (temp_v0 == NULL) {
        return;
    }

    for (i = 0; i < 3; i++) {
        spC8 = &D_80371970[i];
        spC8->unk4 = func_80313AF4((arg0->unk2B8 + temp_v0->unk0[i]) - spC8->unk10.m[3][0], spC8->unk4, 1.0f);
        spC8->unk8 = func_80313AF4((arg0->unk2BC + temp_v0->unk10[i]) - spC8->unk10.m[3][1], spC8->unk8, 1.0f);
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
        var_fs1 = (arg0->unk10.m[3][2] - spC8->unk10.m[3][2]) + 1.57f;

        if (var_fs1 < -0.5f) {
            var_fs1 = -0.5f;
        } else if (var_fs1 > 2.5f) {
            var_fs1 = 2.5f;
        }
        var_fs0 = 1.0f;
        if (arg0->unkB9) {
            var_fs0 = arg0->unk288 * var_fs0;
            if (var_fs0 < 0.0f) {
                var_fs0 = 0.0f;
            } else if (var_fs0 > 1.0f) {
                var_fs0 = 1.0f;
            }
            var_fs1 += var_fs0 * uvCosF((i + 6.0f) * D_8034F850);
        } else {
            var_fs0 = spC8->unk10.m[3][2] - arg0->unk10.m[3][2];
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
        if ((spC8->unk10.m[3][2] - arg0->unk10.m[3][2]) > var_fs0) {
            spC8->unk10.m[3][2] = arg0->unk10.m[3][2] + var_fs0;
        } else if ((spC8->unk10.m[3][2] - arg0->unk10.m[3][2]) < -var_fs0) {
            spC8->unk10.m[3][2] = arg0->unk10.m[3][2] - var_fs0;
        }
        uvDobjPosm(spC8->unk0, 0, &spC8->unk10);
    }

    if (arg0->unk284 < 0.0f) {
        arg0->unk284 -= D_8034F854;
        if (arg0->unk284 < -0.25f) {
            arg0->unk284 = 0.001f;
            uvDobjState(arg0->shadowObjId, 2);
        }
    } else {
        arg0->unk284 += D_8034F854;
        if (arg0->unk284 > 0.25f) {
            arg0->unk284 = -0.001f;
            uvDobjState(arg0->shadowObjId, 0);
        }
    }

    if ((arg0->unk288 > 50.0f) || ((D_80371960 != 0) && (arg0->unk288 < 4.0f))) {
        uvDobjState(arg0->shadowObjId, 0);
    }
    uvMat4SetIdentity(&sp88);
    uvMat4Scale(&sp88, 0.7f, 0.7f, 0.7f);
    sp88.m[3][0] = arg0->unk258->unkC + arg0->unk2B8;
    sp88.m[3][1] = arg0->unk258->unk1C + arg0->unk2BC;
    sp88.m[3][2] = spC8->unk10.m[3][2];
    uvMat4RotateAxis(&sp88, arg0->unk258->unk2C, 'z');
    uvDobjPosm(arg0->shadowObjId, 0, &sp88);
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

void func_803329C0(SkyDivingData* arg0) {
    Unk80371970* temp_fp;
    s32 i;
    Unk80371120 sp78;

    for (i = 0; i < 3; i++) {
        temp_fp = &D_80371970[i];
        switch (i) {
        case 0:
            if ((arg0->unk1C0 == MODEL_SKYDIVING_LARK) || (arg0->unk1C0 == MODEL_SKYDIVING_GOOSE) || (arg0->unk1C0 == MODEL_SKYDIVING_HAWK)) {
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
            if ((arg0->unk1C0 == MODEL_SKYDIVING_LARK) || (arg0->unk1C0 == MODEL_SKYDIVING_GOOSE) || (arg0->unk1C0 == MODEL_SKYDIVING_HAWK)) {
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
            if ((arg0->unk1C0 == MODEL_SKYDIVING_LARK) || (arg0->unk1C0 == MODEL_SKYDIVING_GOOSE) || (arg0->unk1C0 == MODEL_SKYDIVING_HAWK)) {
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
        temp_fp->unk10.m[3][0] = arg0->unk2B8;
        temp_fp->unk10.m[3][1] = arg0->unk2BC;
        temp_fp->unk10.m[3][2] = arg0->unk2C0 - 5.0f;
        temp_fp->unk50 = 0.0f;
        temp_fp->unk70 = hudAddWaypoint(temp_fp->unk10.m[3][0], temp_fp->unk10.m[3][1], temp_fp->unk10.m[3][2]);
    }
    arg0->shadowObjId = uvDobjAllocIdx();
    uvDobjModel(arg0->shadowObjId, MODEL_SKYDIVING_SHADOW);
    uvDobjState(arg0->shadowObjId, 2);
}
