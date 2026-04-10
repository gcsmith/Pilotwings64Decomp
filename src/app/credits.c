#include "common.h"
#include "code_B2900.h"
#include "code_D2B10.h"
#include "credits.h"
#include "demo.h"
#include "demo_attitude.h"
#include "fire_effects.h"
#include "game.h"
#include "snd.h"
#include <uv_event.h>
#include <uv_vector.h>

typedef struct {
    const char* unk0;
    s32 unk4;
} Unk8034F4E0;

Unk8034F4E0 D_8034F4E0[] = {
    {            "NINTENDO STAFF", 0x10000 },
    {                  "DIRECTOR", 0x20000 },
    {               "MAKOTO WADA", 0x30000 },
    {               "CO DIRECTOR", 0x20000 },
    {            "YASUYUKI OYAGI", 0x30000 },
    {          "GRAPHIC DESIGNER", 0x20000 },
    {          "HIROAKI TAKENAKA", 0x30000 },
    {            "YOSHIYUKI KATO", 0x30000 },
    {         "SOUND ARRANGEMENT", 0x20000 },
    {           "AKITO NAKATSUKA", 0x30000 },
    {       "PROJECT ARRANGEMENT", 0x20000 },
    {         "SHIGEKI YAMASHIRO", 0x30000 },
    {             "HIRO NAKAMURA", 0x30000 },
    {              "DARREN SMITH", 0x30000 },
    {               "JIM WORNELL", 0x30000 },
    {            "PARADIGM STAFF", 0x10000 },
    {           "PROJECT MANAGER", 0x20000 },
    {              "DAVE GATCHEL", 0x30000 },
    {    "LEAD SOFTWARE ENGINEER", 0x20000 },
    {          "MIKE ENGELDINGER", 0x30000 },
    { "LEAD MODELING AND EFFECTS", 0x20000 },
    {               "WES HOFFMAN", 0x30000 },
    {      "SOFTWARE ENGINEERING", 0x20000 },
    {               "MIKE PANOFF", 0x30000 },
    {           "AARON HIGHTOWER", 0x30000 },
    {                 "JON DAVIS", 0x30000 },
    {           "STEVE LOTSPEICH", 0x30000 },
    {             "MIKE BIENVENU", 0x30000 },
    {                "SAM PERERA", 0x30000 },
    {             "STEVE FUHRMAN", 0x30000 },
    {                "ROB ROSSOW", 0x30000 },
    {             "CHRIS MUMFORD", 0x30000 },
    {             "RICHARD BAKER", 0x30000 },
    {    "MODELING AND ANIMATION", 0x20000 },
    {             "DAVID KRUEGER", 0x30000 },
    {                "GARY BANDY", 0x30000 },
    {                 "GREG GUTH", 0x30000 },
    {             "AUDIO SUPPORT", 0x20000 },
    {             "SCOTT GARGASH", 0x30000 },
    {                "ANU APPAJI", 0x30000 },
    {               "JOHN PERSER", 0x30000 },
    {         "MUSIC COMPOSITION", 0x20000 },
    {                  "DAN HESS", 0x30000 },
    { "PRODUCT MARKETING SUPPORT", 0x20000 },
    { "MATTHEW SHANNON YARBROUGH", 0x30000 },
    {            "SPECIAL THANKS", 0x20000 },
    {           "KIMIYOSHI FUKUI", 0x30000 },
    {                "KENJI MIKI", 0x30000 },
    {         "MASATO HATAKEYAMA", 0x30000 },
    {            "KENSUKE TANABE", 0x30000 },
    {           "NARUHISA KAWANO", 0x30000 },
    {              "EIJI ONOZUKA", 0x30000 },
    {             "SHIGEO KIMURA", 0x30000 },
    {               "HIRO YAMADA", 0x30000 },
    {            "KOJI MITSUNARI", 0x30000 },
    {              "KAZUNOBU ERI", 0x30000 },
    {        "YOSHITAKA YASUMOTO", 0x30000 },
    {        "TSUTOMU KOGANEZAWA", 0x30000 },
    {          "TAKAYUKI HASHIDA", 0x30000 },
    {              "SATOSHI KIRA", 0x30000 },
    {                          "", 0x30000 },
    {               "MIKE FUKUDA", 0x30000 },
    {         "MASAHITO WATANABE", 0x30000 },
    {          "MICHAEL KELBAUGH", 0x30000 },
    {                          "", 0x30000 },
    {                "RON TOUPAL", 0x30000 },
    {                 "RON PAIGE", 0x30000 },
    {                "DIANE ROTH", 0x30000 },
    {           "SHARON LINDHOLM", 0x30000 },
    {             "CHRIS JOHNSON", 0x30000 },
    {             "JANICE PANOFF", 0x30000 },
    {                          "", 0x30000 },
    {          "MARIO CLUB STAFF", 0x30000 },
    {                          "", 0x30000 },
    {       "NOA PRODUCT TESTING", 0x30000 },
    {                 "PRODUCERS", 0x20000 },
    {              "GENYO TAKEDA", 0x40000 },
    {          "SHIGERU MIYAMOTO", 0x40000 },
    {        "EXECUTIVE PRODUCER", 0x20000 },
    {          "HIROSHI YAMAUCHI", 0x30000 },
    {                          "", 0x30000 },
    {              "PRESENTED BY", 0x20000 },
    {                  "NINTENDO", 0x50000 },
    {                        NULL, 0x30000 },
};

f32 D_8034F780 = -32.0f;
u8 D_8034F784 = 1;
f32 D_8034F788 = 0.0f;
f32 D_8034F78C = -1.0f;
f32 D_8034F790 = 0.0f;
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

#pragma GLOBAL_ASM("asm/nonmatchings/app/credits/credits_8030CDA0.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/app/credits/creditsScene.s")
