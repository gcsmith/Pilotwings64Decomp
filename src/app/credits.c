#include "common.h"
#include "credits.h"
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

#pragma GLOBAL_ASM("asm/nonmatchings/app/credits/func_8030CB60.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/credits/func_8030CC48.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/credits/func_8030CCFC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/credits/credits_8030CDA0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/credits/func_8030D1D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/credits/func_8030D208.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/credits/creditsScene.s")
