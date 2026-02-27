#include "common.h"
#include "credits.h"
#include <uv_vector.h>

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
    { 300.0f, 0.20000000298023224f, 0.6108651757240295f },
    { 500.0f, -1.3707962036132812f, 0.6981316208839417f },
    { 340.0f,  3.4000000953674316f, 0.6108651757240295f }
};

u16 D_8034F480[][2] = {
    { 0x21, 0xDC },
    { 0x1F, 0xDC },
    { 0x20, 0xDC },
    { 0x22, 0xDC },
    { 0x23, 0xDC },
    { 0x24, 0xDC },
    { 0x25, 0xDC },
    { 0x2D, 0xDC },
};

u16 D_8034F4A0[][2] = {
    { 0x27, 0xDC },
    { 0x28, 0xDC },
    { 0x26, 0xDC },
    { 0x2A, 0xDC },
    { 0x2B, 0xDC },
    { 0x2C, 0xDC },
    { 0x29, 0xDC }
};

u16 D_8034F4BC[] = { 0xEB, 0x13B, 0x125, 0x1B5 };

s32 D_8034F4C4 = 0x1720000;

u16 D_8034F4C8[] = { 0x129, 0x10D, 0xE0, 0xE0, 0x0129, 0x0129, 0x0129, 0xE0 };

u16 D_8034F4D8[] = { 0x9E, 0x9D, 0x07, 0x93 };

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

#pragma GLOBAL_ASM("asm/nonmatchings/app/credits/func_8030C1C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/credits/func_8030C22C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/credits/func_8030C54C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/credits/func_8030C61C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/credits/func_8030C6A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/credits/func_8030CB10.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/credits/func_8030CB60.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/credits/func_8030CC48.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/credits/func_8030CCFC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/credits/credits_8030CDA0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/credits/func_8030D1D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/credits/func_8030D208.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/credits/creditsScene.s")
