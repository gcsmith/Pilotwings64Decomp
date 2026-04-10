#include "common.h"
#include "code_B2900.h"
#include "code_D2B10.h"
#include "credits.h"
#include "demo.h"
#include "demo_attitude.h"
#include "env_sound.h"
#include "environment.h"
#include "fire_effects.h"
#include "game.h"
#include "snd.h"
#include "text_data.h"
#include <uv_environment.h>
#include <uv_event.h>
#include <uv_font.h>
#include <uv_memory.h>
#include <uv_texture.h>
#include <uv_vector.h>

#define DOUBLE_ONE (2.0 - 1.0)

typedef struct {
    const char* unk0;
    s16 type;
    s16 unk6; // updated with some sort of row count or something?
} CreditLines;

CreditLines D_8034F4E0[] = {
    {            "NINTENDO STAFF", 1, 0 },
    {                  "DIRECTOR", 2, 0 },
    {               "MAKOTO WADA", 3, 0 },
    {               "CO DIRECTOR", 2, 0 },
    {            "YASUYUKI OYAGI", 3, 0 },
    {          "GRAPHIC DESIGNER", 2, 0 },
    {          "HIROAKI TAKENAKA", 3, 0 },
    {            "YOSHIYUKI KATO", 3, 0 },
    {         "SOUND ARRANGEMENT", 2, 0 },
    {           "AKITO NAKATSUKA", 3, 0 },
    {       "PROJECT ARRANGEMENT", 2, 0 },
    {         "SHIGEKI YAMASHIRO", 3, 0 },
    {             "HIRO NAKAMURA", 3, 0 },
    {              "DARREN SMITH", 3, 0 },
    {               "JIM WORNELL", 3, 0 },
    {            "PARADIGM STAFF", 1, 0 },
    {           "PROJECT MANAGER", 2, 0 },
    {              "DAVE GATCHEL", 3, 0 },
    {    "LEAD SOFTWARE ENGINEER", 2, 0 },
    {          "MIKE ENGELDINGER", 3, 0 },
    { "LEAD MODELING AND EFFECTS", 2, 0 },
    {               "WES HOFFMAN", 3, 0 },
    {      "SOFTWARE ENGINEERING", 2, 0 },
    {               "MIKE PANOFF", 3, 0 },
    {           "AARON HIGHTOWER", 3, 0 },
    {                 "JON DAVIS", 3, 0 },
    {           "STEVE LOTSPEICH", 3, 0 },
    {             "MIKE BIENVENU", 3, 0 },
    {                "SAM PERERA", 3, 0 },
    {             "STEVE FUHRMAN", 3, 0 },
    {                "ROB ROSSOW", 3, 0 },
    {             "CHRIS MUMFORD", 3, 0 },
    {             "RICHARD BAKER", 3, 0 },
    {    "MODELING AND ANIMATION", 2, 0 },
    {             "DAVID KRUEGER", 3, 0 },
    {                "GARY BANDY", 3, 0 },
    {                 "GREG GUTH", 3, 0 },
    {             "AUDIO SUPPORT", 2, 0 },
    {             "SCOTT GARGASH", 3, 0 },
    {                "ANU APPAJI", 3, 0 },
    {               "JOHN PERSER", 3, 0 },
    {         "MUSIC COMPOSITION", 2, 0 },
    {                  "DAN HESS", 3, 0 },
    { "PRODUCT MARKETING SUPPORT", 2, 0 },
    { "MATTHEW SHANNON YARBROUGH", 3, 0 },
    {            "SPECIAL THANKS", 2, 0 },
    {           "KIMIYOSHI FUKUI", 3, 0 },
    {                "KENJI MIKI", 3, 0 },
    {         "MASATO HATAKEYAMA", 3, 0 },
    {            "KENSUKE TANABE", 3, 0 },
    {           "NARUHISA KAWANO", 3, 0 },
    {              "EIJI ONOZUKA", 3, 0 },
    {             "SHIGEO KIMURA", 3, 0 },
    {               "HIRO YAMADA", 3, 0 },
    {            "KOJI MITSUNARI", 3, 0 },
    {              "KAZUNOBU ERI", 3, 0 },
    {        "YOSHITAKA YASUMOTO", 3, 0 },
    {        "TSUTOMU KOGANEZAWA", 3, 0 },
    {          "TAKAYUKI HASHIDA", 3, 0 },
    {              "SATOSHI KIRA", 3, 0 },
    {                          "", 3, 0 },
    {               "MIKE FUKUDA", 3, 0 },
    {         "MASAHITO WATANABE", 3, 0 },
    {          "MICHAEL KELBAUGH", 3, 0 },
    {                          "", 3, 0 },
    {                "RON TOUPAL", 3, 0 },
    {                 "RON PAIGE", 3, 0 },
    {                "DIANE ROTH", 3, 0 },
    {           "SHARON LINDHOLM", 3, 0 },
    {             "CHRIS JOHNSON", 3, 0 },
    {             "JANICE PANOFF", 3, 0 },
    {                          "", 3, 0 },
    {          "MARIO CLUB STAFF", 3, 0 },
    {                          "", 3, 0 },
    {       "NOA PRODUCT TESTING", 3, 0 },
    {                 "PRODUCERS", 2, 0 },
    {              "GENYO TAKEDA", 4, 0 },
    {          "SHIGERU MIYAMOTO", 4, 0 },
    {        "EXECUTIVE PRODUCER", 2, 0 },
    {          "HIROSHI YAMAUCHI", 3, 0 },
    {                          "", 3, 0 },
    {              "PRESENTED BY", 2, 0 },
    {                  "NINTENDO", 5, 0 },
    {                        NULL, 3, 0 },
};

f32 D_8034F780 = -32.0f;
u8 D_8034F784 = 1;
f32 D_8034F788 = 0.0f;
s32 D_8036A8B0;

s32 credits_8030CB60(s32 arg0) {
    s32 var_a2;
    s32 var_a1;
    s32 temp_v0;

    var_a2 = credits_8030CC48();
    if (arg0 != 0) {
        var_a1 = D_80362690->unkC[D_80362690->unk9C].unk8A;
        D_80362690->unkC[D_80362690->unk9C].unk8A = var_a1 == 0;
        saveFileLoad(D_80362690->unkC[D_80362690->unk9C].unk8A);
        temp_v0 = credits_8030CC48();
        if (var_a2 < temp_v0) {
            var_a2 = temp_v0;
        }
        var_a1 = D_80362690->unkC[D_80362690->unk9C].unk8A;
        D_80362690->unkC[D_80362690->unk9C].unk8A = var_a1 == 0;
        saveFileLoad(D_80362690->unkC[D_80362690->unk9C].unk8A);
    }
    return var_a2;
}

s32 credits_8030CC48(void) {
    if (func_8032C27C() != 0) {
        return 3;
    }
    if (func_8032C3C4(D_80362690->unkC[D_80362690->unk9C].unk74, 3) >= 3) {
        return 2;
    }
    if (func_8032C3C4(D_80362690->unkC[D_80362690->unk9C].unk74, 1) > 0) {
        return 1;
    }
    return 0;
}

s32 creditsMainRender(void) {
    D_8036A8B0 = credits_8030CC48();
    credits_8030CDA0(D_8036A8B0);
    while (credits_8030D208() == 0) {
        uvGfxBegin();
        creditsScene();
        func_8034B688();
        uvGfxEnd();
    }
    credits_8030D1D4();
    if (D_80362690->unkA8 < D_8036A8B0) {
        D_80362690->unkA8 = D_8036A8B0;
    }
    return 0;
}

void credits_8030CDA0(s32 timeOfDay) {
    Unk80362690_Unk0* sp2C;
    Camera* sp28;
    CreditLines* credLine;
    s32 prevType;
    s32 var_v0;
    s32 envId;
    f32 ft0;
    s32 i;

    D_8034F780 = -32.0f;
    D_8034F784 = 1;

    var_v0 = 0;
    prevType = D_8034F4E0[0].type;
    for (i = 0; D_8034F4E0[i].unk0 != NULL; i++) {
        credLine = &D_8034F4E0[i];
        if (prevType != credLine->type) {
            switch (prevType) {
            case 1:
                if (credLine->type != 3) {
                    var_v0 -= 40.0f;
                }
                break;
            case 2:
                if ((credLine->type != 3) && (credLine->type != 4) && (credLine->type != 5)) {
                    var_v0 -= 30.0f;
                }
                break;
            case 3:
            case 4:
            case 5:
                var_v0 -= 50.0f;
                break;
            }
            prevType = credLine->type;
        }

        credLine->unk6 = var_v0;
        switch (credLine->type) {
        case 1:
            var_v0 -= 30.0f;
            break;
        case 2:
            if (credLine->type != 5) { // case is always true
                var_v0 -= 30.0f;
            }
            break;
        case 3:
        case 5:
            var_v0 -= 30.0f;
            break;
        case 4:
            var_v0 -= 40.0f;
            break;
        }
    }
    ft0 = var_v0;
    D_8034F788 = -ft0 / 210.0f;

    sp28 = D_80362690->unkC[D_80362690->unk9C].unk70;
    sp2C = &D_80362690->unkC[D_80362690->unk9C];
    uvLevelInit();
    D_80362690->map = MAP_LITTLE_STATES;
    D_80362690->terraId = 3;
    switch (timeOfDay) {
    default:
        D_80362690->envId = 0x10;
        break;
    case 1:
        D_80362690->envId = 0x10;
        break;
    case 2:
        D_80362690->envId = 0xC;
        break;
    case 3:
        D_80362690->envId = 0x11;
        break;
    }
    envSoundInit();
    textLoadBlock(0x42);
    if (D_80362690->envId == 0x11) {
        envLoadTerrainPal(D_80362690->envId);
    }
    uvLevelAppend(5);
    func_8034B5E0(sp28->unk22C, sp28);
    envId = D_80362690->envId;
    env_802E1444((envId != 0) ? envId : 0x10);
    func_80204BD4(sp28->unk22C, 1, 1.0f);
    uvChanTerra(sp2C->unk70->unk22C, D_80362690->terraId);
    func_80204A8C(sp28->unk22C, 3);
    uvEnvFunc(D_80362690->envId, 0, env_802E0CF0);
    func_80204AB0(sp28->unk22C, 1, func_8034B6F8);
    func_80313640(-1419.9f, 871.2f, 639.72f, 1.1452856f, -0.2094396f, 0.0f, &sp28->unk108);
    fireFxInit();
    fireFxCreateAll();
    uvFontSet(0);
    uvFontScale(1.0, 1.0);
    demoAttInit(0x54);
    func_8033F748(0x1E);
    func_8033F964(0);
    func_8033FCD0(sp2C->veh);
}

void credits_8030D1D4(void) {
    uvEventPost(0xD, 0);
    func_8033F964(1U);
    fireFxDeinit();
}

s32 credits_8030D208(void) {
    demoAtt_80320FBC();
    demo_80323020();
    func_80313D74();
    if ((D_8034F784 == 0) && (demoButtonPress(D_80362690->unk9C, A_BUTTON | B_BUTTON | START_BUTTON) != 0)) {
        if (demoButtonPress(D_80362690->unk9C, A_BUTTON | START_BUTTON) != 0) {
            sndPlaySfx(SFX_UI_CONFIRM);
            return 1;
        }
        if (demoButtonPress(D_80362690->unk9C, B_BUTTON) != 0) {
            sndPlaySfx(SFX_UI_CANCEL);
        }
        return 1;
    }
    if (D_8034F784 != 0) {
        D_8034F780 += D_8034F788 * D_8034F854;
    }
    return 0;
}

void creditsScene(void) {
    static f32 D_8034F78C = -1.0f;
    static f32 D_8034F790 = 0.0f;
    Camera* var_v1;
    s32 i;
    s32 sp74;
    s32 sp70;
    s16* sp6C;
    s16* sp68;
    s16* sp64;
    s32 sp60;
    s32 var_s0;
    f32 sp58;
    f32 sp54;
    f32 sp50;

    var_v1 = D_80362690->unkC[D_80362690->unk9C].unk70;

    func_80204FC4(var_v1->unk22C);
    sp74 = (s32)(D_8034F780 + 0.5f);
    for (i = 0; D_8034F4E0[i].unk0 != NULL; i++) {
        sp70 = D_8034F4E0[i].unk6 + sp74;
        if ((sp70 >= -0x20) && (sp70 <= 0xF0)) {
            switch (D_8034F4E0[i].type) {
            case 1:
            case 5:
                uvFontScale(1, 1);
                uvFontColor(0x46, 0x46, 0xAA, 0xFF);
                uvFontSet(4);
                break;
            case 2:
                uvFontScale(1, 1);
                uvFontColor(0xD2, 0xD2, 0xD2, 0xFF);
                uvFontSet(3);
                break;
            case 3:
            case 4:
                uvFontScale(1, 1);
                uvFontColor(0xD2, 0xD2, 0, 0xFF);
                uvFontSet(4);
                break;
            }
            uvFontPrintStr(160 - (uvFontWidth(D_8034F4E0[i].unk0) / 2), sp70, D_8034F4E0[i].unk0);
        }
    }

    if (D_8036A8B0 != 1) {
        sp60 = 0x14;
    } else {
        sp60 = 0;
    }
    if (D_8034F784 == 0) {
        if (D_8034F78C == -1.0) {
            D_8034F78C = D_8034F850;
        }

        if ((D_8034F78C + DOUBLE_ONE) < D_8034F850) {
            var_s0 = 255;
        } else {
            var_s0 = ((D_8034F850 - D_8034F78C) * DOUBLE_ONE * 255.0);
        }
        if (D_8036A8B0 == 2) {
            sp6C = textGetDataByIdx(0x7E);
            sp68 = textGetDataByIdx(0x2C);
            sp64 = textGetDataByIdx(0x10B);
        } else if (D_8036A8B0 == 3) {
            sp6C = textGetDataByIdx(0xBB);
            sp68 = textGetDataByIdx(0x118);
            sp64 = textGetDataByIdx(0x18);
        } else {
            sp6C = NULL;
        }
        if (sp6C != NULL) {
            uvFontSet(6);
            uvFontScale(1.0, 1.0);
            D_8034F790 += 0.2f * uvGfxGetUnkStateF();
            while (D_8034F790 > 1.0f) {
                D_8034F790 -= 1.0f;
            }

            func_8031420C(D_8034F790, 1.0f, 1.0f, &sp58, &sp54, &sp50);
            uvFontColor(sp58 * 255.0f, sp54 * 255.0f, sp50 * 255.0f, var_s0);
            var_s0 *= 0;
            var_s0 += 90;
            func_80219874(168 - (func_802196B0(sp6C) / 2), var_s0, sp6C, 100, 0xFFE);
            var_s0 -= 20;
            func_80219874(168 - (func_802196B0(sp68) / 2), var_s0, sp68, 100, 0xFFE);
            var_s0 -= 40;
            func_80219874(168 - (func_802196B0(sp64) / 2), var_s0, sp64, 100, 0xFFE);
        }
    } else {
        D_8034F78C = -1.0f;
    }
    uvFontGenDlist();
    if (sp70 >= (sp60 + 100)) {
        D_8034F784 = 0;
    }
}

