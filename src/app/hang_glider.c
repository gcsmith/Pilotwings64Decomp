#include "common.h"
#include <uv_math.h>
#include <uv_matrix.h>
#include <uv_util.h>
#include <uv_vector.h>
#include "balls.h"
#include "code_61A60.h"
#include "code_66F70.h"
#include "demo_attitude.h"
#include "environment.h"
#include "game.h"
#include "hang_glider.h"
#include "hud.h"
#include "pads.h"
#include "rings.h"
#include "task.h"
#include "snd.h"

typedef struct {
    Vec2F unk0[23];
    Vec2F unkB8[10];
} Unk8034F1C8; // size = 0x108

typedef struct {
    Vec2F unk0[20];
} Unk8034F2D0;

static Unk802D3658_Unk111C D_803680A0;
static Unk802D3658_Unk1224 D_803681A8;
static Vec3F D_803682F0;
static u16 sHgClassId;
static u16 sHgVehicleId;
static u16 sHgTestId;
static f32 D_80368304;
static f32 D_80368308;
static u16 D_8036830C;

static f32 D_8034F1C0 = 10000.0f;
static s32 D_8034F1C4 = 0;

static Unk8034F1C8 D_8034F1C8 = {
    { { -1.570797f, 0.0f },      { -0.26179948f, 0.005f },  { -0.209439605f, 0.01f },
     { -0.1570796966f, 0.02f }, { -0.0872664973f, 0.03f }, { 0.0f, 0.1f },
     { 0.05235990136f, 0.4f },  { 0.06981319934f, 0.4f },  { 0.07679452002f, 0.5f },
     { 0.08028517663f, 0.85f }, { 0.08552116900f, 1.05f }, { 0.09075715392f, 1.0f },
     { 0.10471980273f, 0.85f }, { 0.12217310070f, 1.05f }, { 0.13962639868f, 1.43f },
     { 0.15707969665f, 1.65f }, { 0.17453299462f, 1.85f }, { 0.19198629260f, 1.85f },
     { 0.20943960547f, 1.15f }, { 0.26179948449f, 0.8f },  { 0.31415939331f, 0.5f },
     { 0.52359896898f, 0.5f },  { 1.57079696655f, 0.5f } },
    { { 0.0f, 0.0f },
     { 0.5f, 1.0f },
     { 5.0f, 1.0f },
     { 20.0f, 1.0f },
     { 30.0f, 0.9f },
     { 35.0f, 0.75f },
     { 40.0f, 0.54f },
     { 50.0f, 0.35f },
     { 60.0f, 0.12f },
     { 100.0f, 0.0f } }
};

static Unk8034F2D0 D_8034F2D0 = {
    { { 0.0f, 0.0f },   { 0.3f, 0.6f },   { 1.7f, 0.6f },   { 3.0f, 0.6f },   { 7.0f, 0.6f },   { 13.0f, -1.3f }, { 15.0f, -2.0f },
     { 18.0f, -2.2f }, { 20.0f, -2.5f }, { 21.0f, -1.8f }, { 23.9f, -1.0f }, { 24.0f, 0.0f },  { 24.1f, 1.0f },  { 25.0f, 1.8f },
     { 33.5f, 2.5f },  { 36.0f, 0.5f },  { 51.0f, 0.5f },  { 61.0f, 0.5f },  { 61.5f, 20.0f }, { 100.0f, 50.0f } }
};

// forward declarations
STATIC_FUNC void hangGlider_802F2804(HangGliderData*);
STATIC_FUNC void hangGlider_802F2F94(HangGliderData*);
STATIC_FUNC void hangGlider_802F3030(HangGliderData*);
STATIC_FUNC void hangGlider_802F3154(HangGliderData*);
STATIC_FUNC s32 hangGlider_802F32EC(HangGliderData*);
STATIC_FUNC void hangGlider_802F3470(HangGliderData*);
STATIC_FUNC void hangGlider_802F3694(HangGliderData*);
STATIC_FUNC void hangGlider_802F391C(HangGliderData*);
STATIC_FUNC void hangGlider_802F39F8(HangGliderData*);
STATIC_FUNC void hangGlider_802F3A80(HangGliderData*);
STATIC_FUNC f32 hangGlider_802F41AC(Unk8034F1C8*, f32, f32);
STATIC_FUNC void hangGlider_802F4370(HangGliderData*);
STATIC_FUNC f32 hangGlider_802F42DC(Unk8034F2D0*, f32);

void hangGlider_802F2190(HangGliderData* hgData) {
    u8 temp_v0;

    D_803680A0.unk0 = 4;
    D_803680A0.unk4[0].unk0 = 1;
    uvVec3Copy(&D_803680A0.unk4[0].unk28, &hgData->unk2A0);
    uvVec3Copy(&D_803680A0.unk4[0].unk1C, &hgData->unk294);
    D_803680A0.unk4[1].unk0 = 1;
    uvVec3Copy(&D_803680A0.unk4[1].unk28, &hgData->unk2AC);
    uvVec3Copy(&D_803680A0.unk4[1].unk1C, &hgData->unk294);
    D_803680A0.unk4[2].unk0 = 1;
    uvVec3Copy(&D_803680A0.unk4[2].unk28, &hgData->unk27C);
    uvVec3Copy(&D_803680A0.unk4[2].unk1C, &hgData->unk288);
    D_803680A0.unk4[3].unk0 = 1;
    uvVec3Copy(&D_803680A0.unk4[3].unk28, &hgData->unk294);
    uvVec3Copy(&D_803680A0.unk4[3].unk1C, &hgData->unk2B8);
    hangGlider_802F2370(hgData);
    D_8036830C = 0xF7F8;
    taskGetClsVehTest(&sHgClassId, &sHgVehicleId, &sHgTestId);
    if ((sHgClassId == CLASS_A) && (sHgTestId == 1)) {
        D_80368304 = 0.28f;
        D_80368308 = 1.15f;
    } else {
        D_80368304 = 0.0f;
        D_80368308 = 1.0f;
    }
    D_8034F1C0 = 10000.0f;
    D_8034F1C4 = 0;
    temp_v0 = taskGet_80346364();
    switch (temp_v0) {
    case 3:
        D_8034F1C4 = taskGet_80345C80()->unk3C4;
        return;
    case 4:
        D_8034F1C0 = taskGet_80345C80()->unk3C8;
        return;
    }
}

void hangGlider_802F2370(HangGliderData* hgData) {
    hgData->unkFC = 0;
    hgData->unk8F = 0;
    hgData->unk90 = 0;
    hgData->unkF4 = 0.0f;
    hgData->unkF8 = 0.0f;
    hgData->unk100.x = hgData->unk100.y = 0.0f;
    hgData->unk100.z = 1.0f;
    hgData->unk1B4.x = hgData->unk1B4.y = hgData->unk1B4.z = 0.0f;
    hgData->unk1A4.x = hgData->unk1A4.y = hgData->unk1A4.z = 0.0f;
    hgData->unk1C0.x = hgData->unk1C0.y = hgData->unk1C0.z = 0.0f;
    hgData->unk1D8 = 0.0f;
    hgData->unk1D4 = 0.0f;
    hgData->unk1D0 = 0.0f;
    hgData->unk1DC.x = hgData->unk1DC.y = hgData->unk1DC.z = 0.0f;
    hgData->unk1E8.x = hgData->unk1E8.y = 0.0f;
    hgData->unk1E8.z = 1.0f;
    hgData->unk1F4.x = hgData->unk1F4.y = 0.0f;
    hgData->unk1F4.z = -9.8f;
    hgData->unk200.x = hgData->unk200.y = hgData->unk200.z = 0.0f;
    hgData->unk1B0 = 0.0f;
    hgData->unk1CC = 0.0f;
    hgData->unk20C = 0.0f;
    hgData->unkF0 = 0.0f;
    hgData->unkEC = 0.0f;
    hgData->unk8D = 0;
    hgData->unkE8 = 0;
    hgData->unkE9 = 0;
    hgData->unk5C = 0;
    uvMat4Copy(&hgData->unk14C, &hgData->unk10);
    hgData->unk14C.m[3][0] = 0.0f;
    hgData->unk14C.m[3][1] = 0.0f;
    hgData->unk14C.m[3][2] = 0.0f;
    uvMat4LocalToWorld(&hgData->unk14C, &hgData->unk1A4, &hgData->unk18C);
    uvVec3Normal(&hgData->unk198, &hgData->unk18C);
    hgData->unk1B0 = uvVec3Len(&hgData->unk1A4);
    hgData->unk314 = 1;
    hgData->unk308.x = hgData->unk10.m[3][0];
    hgData->unk308.y = hgData->unk10.m[3][1];
    hgData->unk308.z = hgData->unk10.m[3][2];
}

void hangGlider_802F24BC(HangGliderData* hgData) {
    Vec3F sp34;

    uvMat4Copy(&hgData->unk14C, &hgData->unk10);
    hgData->unk14C.m[3][0] = 0.0f;
    hgData->unk14C.m[3][1] = 0.0f;
    hgData->unk14C.m[3][2] = 0.0f;
    uvMat4InvertTranslationRotation(&hgData->unk10C, &hgData->unk14C);
    uvMat4LocalToWorld(&hgData->unk10C, &hgData->unk18C, &hgData->unk1A4);
    hangGlider_802F3470(hgData);
    hangGlider_802F39F8(hgData);
    hangGlider_802F391C(hgData);
    if ((hgData->unk8D == 0) && (hgData->unk8C != 2) && (hgData->unkE9 == 0)) {
        hangGlider_802F3694(hgData);
    }
    switch (hgData->unk8C) {
    case 3:
        return;
    case 1:
        hangGlider_802F3154(hgData);
    default:
        break;
    case 0:
        hangGlider_802F2804(hgData);
        break;
    case 2:
        hangGlider_802F3030(hgData);
        break;
    case 4:
        hangGlider_802F2F94(hgData);
        break;
    }

    if (hgData->unk8C == 0) {
        sp34.x = hgData->unk10.m[2][0];
        sp34.y = hgData->unk10.m[2][1];
        sp34.z = hgData->unk10.m[2][2];
    } else {
        sp34.x = hgData->unk100.x;
        sp34.y = hgData->unk100.y;
        sp34.z = hgData->unk100.z;
    }
    func_80313C94(&sp34, &hgData->unk1E8, 2.0f);
    uvMat4LocalToWorld(&hgData->unk14C, &hgData->unk1C0, &hgData->unk1B4);
    hgData->unk1A4.x += D_8034F854 * hgData->unk1C0.x;
    hgData->unk1A4.y += D_8034F854 * hgData->unk1C0.y;
    hgData->unk1A4.z += D_8034F854 * hgData->unk1C0.z;
    hgData->unk1D0 += D_8034F854 * hgData->unk1DC.x;
    hgData->unk1D4 += D_8034F854 * hgData->unk1DC.y;
    hgData->unk1D8 += D_8034F854 * hgData->unk1DC.z;
    uvMat4LocalTranslate(&hgData->unk10, hgData->unk18C.x * D_8034F854, hgData->unk18C.y * D_8034F854, hgData->unk18C.z * D_8034F854);
    uvMat4RotateAxis(&hgData->unk10, hgData->unk1D8 * D_8034F854, 'z');
    uvMat4RotateAxis(&hgData->unk10, hgData->unk1D0 * D_8034F854, 'x');
    uvMat4RotateAxis(&hgData->unk10, hgData->unk1D4 * D_8034F854, 'y');
    hgData->unk1B4.x = 0.0f;
    hgData->unk1B4.y = 0.0f;
    hgData->unk1B4.z = 0.0f;
    hgData->unk1DC.x = 0.0f;
    hgData->unk1DC.y = 0.0f;
    hgData->unk1DC.z = 0.0f;
    if (hgData->unk8C != 4) {
        hangGlider_802F32EC(hgData);
    }
    if ((hgData->unk8C != 4) && (hgData->unk8C != 3)) {
        hangGlider_802F3A80(hgData);
    }
    hgData->unk1B0 = uvVec3Len(&hgData->unk1A4);
    hgData->unk1CC = uvVec3Len(&hgData->unk1C0);
    if (D_80362690->unkA4 != 0) {
        demoAttUpdate(D_8034F850, &hgData->unk10);
    }
}

STATIC_FUNC void hangGlider_802F2804(HangGliderData* hgData) {
    f32 temp_fv1;
    f32 temp_fv0;
    f32 var_fa1;
    f32 var_fv0;
    f32 sp24;
    f32 var_fa0;
    f32 var_ft0;
    f32 sp18;

    if ((hgData->unkE9 == 0) && (hgData->unk1B0 < 4.0f)) {
        hgData->unkE9 = 1;
    } else if ((hgData->unkE9 != 0) && (hgData->unk1B0 > 12.0f)) {
        hgData->unkE9 = 0;
    }
    if (hgData->unk1B0 < 8.0f) {
        if (hgData->unk1B0 > 4.0f) {
            var_fv0 = ABS_NOEQ(hgData->unk1B0);
            temp_fv1 = 1.0f - ((var_fv0 - 4.0f) / 4 /*.0f*/);
            hgData->unkF0 = SQ(temp_fv1);
        } else {
            hgData->unkF0 = 1.0f;
        }
    } else {
        hgData->unkF0 = 0.0f;
    }
    if (hgData->unkF8 < 0.2f) {
        hgData->unkE9 = 0;
    }
    if ((D_8034F1C4 > 0) && (ringsGetCleared() >= D_8034F1C4)) {
        hudText_8031D8E0(0xD4, 1.5f, 8.0f);
        D_8034F1C4 = 0;
        sndPlaySfx(SFX_UNK_005);
    }

    temp_fv1 = uvSqrtF(SQ(hgData->unk10.m[1][0]) + SQ(hgData->unk10.m[1][1])) * 0.8f;
    if (hgData->unk200.y > 0.0f) {
        var_fa1 = (hgData->unkF0 + (0.2f * hgData->unk200.y)) * temp_fv1;
    } else {
        var_fa1 = (((1.0f - hgData->unkF0) * hgData->unk64) + hgData->unkF0) * temp_fv1;
    }
    if ((sHgClassId == 1) && (sHgTestId == 1)) {
        if ((hgData->unk1B0 > 51.0f) && (hgData->unkF4 < 60.0f) && (hgData->unk64 < -0.8)) {
            var_fa1 *= 2.0f;
            D_80368304 = 0.0f;
        }
        if (hgData->unkF4 > 470.0f) {
            if (hgData->unk64 > 0.8) {
                var_fa1 *= 2.0f * hgData->unk64;
            }
        }
    }

    hgData->unk1DC.x += -hgData->unk2FC * 4 /*.0f*/ * (var_fa1 + D_80368304);
    temp_fv1 = uvSqrtF(SQ(hgData->unk10.m[0][0]) + SQ(hgData->unk10.m[0][1])) * 0.5f;
    if (hgData->unk80 != 0) {
        temp_fv1 *= 0.3f;
    }
    var_fa1 = hgData->unk60 * temp_fv1;
    if ((sHgClassId == 1) && (sHgTestId == 1) && (hgData->unk1B0 > 51.0f) && (hgData->unkF4 < 60.0f)) {
        var_fv0 = ABS_NOEQ(hgData->unk60);
        if (var_fv0 > 0.8) {
            var_fv0 = ABS_NOEQ(hgData->unk60);
            var_fa1 *= 3.0f * var_fv0;
            D_80368308 = 1.0f;
        }
    }
    hgData->unk1DC.y += hgData->unk300 * 5.6f * (var_fa1 * D_80368308);
    if (hgData->unkF0 > 0.0f) {
        sp18 = hgData->unkF0 * 5.0f;
        hgData->unk1DC.y += sp18 * uvSinF(uvSinF(hgData->unkF0 * 0.179f * D_8034F850) * 3.1f * D_8034F850);
    }
    if (hgData->unk80 != 0) {
        if (hgData->unk88 > 0.65f) {
            hgData->unk1DC.x += 5.0f * (hgData->unk88 - 0.65f);
        } else if (hgData->unk88 > 0.0f) {
            hgData->unk1DC.x += 7.07f * hgData->unk88;
        }
    }

    hgData->unk1D0 = func_80313AF4(0.0f, hgData->unk1D0, 3.0f);
    hgData->unk1D4 = func_80313AF4(0.0f, hgData->unk1D4, 3.0f);
    hgData->unk1D8 = func_80313AF4(0.0f, hgData->unk1D8, 3.0f);

    sp24 = uvSqrtF(SQ(hgData->unk1F4.y) + SQ(hgData->unk1F4.z + (hgData->unk2F0 * 9.8f)));
    if (hgData->unk1F4.y < 0.0f) {
        sp24 = -sp24;
        sp24 *= 0.34f;
    } else {
        sp24 *= 0.34f;
    }
    if (hgData->unkE9 != 0) {
        sp24 = 0.0f;
    }

    var_fa0 = uvSqrtF(SQ(hgData->unk1F4.x) + SQ(hgData->unk1F4.z + (hgData->unk2F0 * 9.8f))) * 0.29f;
    if ((hgData->unk1B0 > 22.0f) && (D_80368304 != 0.0f)) {
        var_fv0 = hgData->unk1B0 / 22.0f;
        if (var_fv0 > 2.0f) {
            var_fv0 = 2.0f;
        }
        sp24 /= var_fv0;
    }
    if ((hgData->unk1B0 > 22.0f) && (D_80368308 != 1.0f)) {
        var_fv0 = hgData->unk1B0 / 22.0f;
        if (var_fv0 > 2.0f) {
            var_fv0 = 2.0f;
        }
        var_fa0 /= var_fv0;
    }
    if (hgData->unk1F4.x > 0.0f) {
        var_fa0 = -var_fa0;
    }

    var_fa1 = SQ(hgData->unk18C.x);
    hgData->unk1DC.x += sp24;
    hgData->unk1DC.y += var_fa0;
    if (hgData->unk18C.x < 0.0f) {
        var_fa1 = -var_fa1;
    }
    hgData->unk1D8 -= 0.005f * var_fa1;
}

STATIC_FUNC void hangGlider_802F2F94(HangGliderData* hgData) {
    hgData->unk1B4.x = hgData->unk18C.x * -0.2f;
    hgData->unk1B4.y = hgData->unk18C.y * -0.2f;
    hgData->unk1B4.z = hgData->unk18C.z * -0.2f;
    hgData->unk1D0 = func_80313AF4(0.0f, hgData->unk1D0, 3.0f);
    hgData->unk1D4 = func_80313AF4(0.0f, hgData->unk1D4, 3.0f);
    hgData->unk1D8 = func_80313AF4(0.0f, hgData->unk1D8, 3.0f);
    hgData->unk10.m[3][2] = hgData->unkF4 - hgData->unk2B8.z;
}

STATIC_FUNC void hangGlider_802F3030(HangGliderData* hgData) {
    Vec3F sp3C;
    Vec3F sp30;

    if (hgData->unkEC == 0.0f) {
        hgData->unkEC = D_8034F850;
    }
    sp3C.x = 0.0f;
    sp3C.y = 0.0f;
    sp3C.z = -0.5f;
    sp30.x = hgData->unk1F4.x * (1.0f / 2.0f);
    sp30.y = hgData->unk1F4.y * (1.0f / 2.0f);
    sp30.z = hgData->unk1F4.z * (1.0f / 2.0f);
    func_802DC1DC(&hgData->unk1DC, &sp3C, &sp30, 0.5f, 0.5f, 0.5f);
    hgData->unk1D0 = func_80313AF4(0.0f, hgData->unk1D0, 0.7f);
    hgData->unk1D4 = func_80313AF4(0.0f, hgData->unk1D4, 0.7f);
    hgData->unk1D8 = func_80313AF4(0.0f, hgData->unk1D8, 0.7f);
    if ((D_8034F850 - hgData->unkEC) > 3.75f) {
        hgData->unk8C = 3;
    }
}

STATIC_FUNC void hangGlider_802F3154(HangGliderData* hgData) {
    hgData->unk1D0 = func_80313AF4(0.0f, hgData->unk1D0, 15.0f);
    hgData->unk1D4 = func_80313AF4(0.0f, hgData->unk1D4, 15.0f);
    hgData->unk1D8 = func_80313AF4(0.0f, hgData->unk1D8, 15.0f);
    if (D_8034F850 <= 2) {
        if (hgData->unkF8 > 2.0f) {
            hgData->unk8C = 0;
        }
    } else {
        if (hgData->unkF8 > 10.0f) {
            padsLandedPadStrip(hgData->unk10.m[3][0], hgData->unk10.m[3][1], hgData->unk10.m[3][2], &hgData->unk5C);
            if (hgData->unk5C == 0) {
                hgData->unk8C = 0;
                hgData->unk90 = 0;
            }
        }
        if ((hgData->unk1B0 < 1.50f) && ((hgData->unkF8 + hgData->unk2B8.z) < 0.2f)) {
            padsLandedPadStrip(hgData->unk10.m[3][0], hgData->unk10.m[3][1], hgData->unk10.m[3][2], &hgData->unk5C);
            if (hgData->unk5C != 0) {
                hgData->unk4 = 0xFFFF;
                hudText_8031D8E0(0xCB, 1.5f, 8.0f);
            } else {
                hgData->unk4 = D_8036830C;
                hudText_8031D8E0(0xB2, 1.5f, 8.0f);
            }
            hgData->unk8C = 4;
            hgData->unk10.m[3][2] = hgData->unkF4 - hgData->unk2B8.z;
        }
    }
}

STATIC_FUNC s32 hangGlider_802F32EC(HangGliderData* hgData) {
    Vec3F sp44;
    s32 var_v0;
    s32 sp3C;
    u8 temp_v1;
    Vec3F* sp34;

    sp44.x = hgData->unk10.m[3][0];
    sp44.y = hgData->unk10.m[3][1];
    sp44.z = hgData->unk10.m[3][2];
    sp3C = hgData->unk314;
    temp_v1 = db_getgnd(&hgData->unk308, &sp44, &sp3C, &hgData->unkFC, &hgData->unkF4, &hgData->unk100);
    hgData->unkF8 = sp44.z - hgData->unkF4;
    if (D_8034F1C0 < hgData->unk10.m[3][2]) {
        hudText_8031D8E0(0xCC, 1.5f, 8.0f);
        D_8034F1C0 = 10000.0f;
        sndPlaySfx(SFX_UNK_005);
    }
    if (temp_v1 != 0) {
        hgData->unk8D = temp_v1;
        hgData->unk8C = 3;
        if (temp_v1 == 4) {
            hgData->unkE8 = 1;
        }
        sp34 = func_802E02EC();
        func_802E05CC(&hgData->unk10, sp34, &hgData->unk100, 0);
        uvVec3Copy(&hgData->unkDC, sp34);
        hgData->unk4 = D_8036830C;
    }
    if (hgData->unk8C != 3) {
        hgData->unk308.x = sp44.x;
        hgData->unk308.y = sp44.y;
        hgData->unk308.z = sp44.z;
    }
    if (hgData->unkE8 != 0) {
        return 0;
    }
    if (hgData->unkF8 > 0.2f) {
        return 0;
    }
    return 1;
}

STATIC_FUNC void hangGlider_802F3470(HangGliderData* hgData) {
    Vec3F sp3C;
    Vec3F sp30;
    f32 var_fv1;
    f32 sp2C;
    f32 var_fa1;

    if (hgData->unk1B0 < 0.1f) {
        return;
    }
    sp3C.x = hgData->unk10.m[2][0];
    sp3C.y = hgData->unk10.m[2][1];
    sp3C.z = hgData->unk10.m[2][2];
    sp30.x = hgData->unk18C.x / hgData->unk1B0;
    sp30.y = hgData->unk18C.y / hgData->unk1B0;
    sp30.z = hgData->unk18C.z / hgData->unk1B0;
    var_fv1 = ABS_NOEQ(uvVec3Dot(&sp3C, &sp30));
    if (var_fv1 < 0.1f) {
        var_fv1 = 0.1f;
    }

    var_fv1 *= hangGlider_802F42DC(&D_8034F2D0, hgData->unk1B0);
    var_fv1 *= hgData->unk2F4;
    var_fa1 = -var_fv1 * 0.003f;
    var_fv1 = 1.0f;

    sp3C.x = (var_fa1 * 1.0f) * hgData->unk18C.x * hgData->unk18C.x;
    if (hgData->unk18C.x < 0.0f) {
        sp3C.x = -sp3C.x;
    }

    sp3C.y = (var_fa1 * 1.0f) * hgData->unk18C.y * hgData->unk18C.y;
    if (hgData->unk18C.y < 0.0f) {
        sp3C.y = -sp3C.y;
    }

    if (hgData->unk1B0 < 10.0f) {
        var_fv1 *= 0;
        var_fa1 = -var_fv1 * 0.0030f;
    }

    sp3C.z = (var_fa1 * 1.0f) * hgData->unk18C.z * hgData->unk18C.z;
    if (hgData->unk18C.z < 0.0f) {
        sp3C.z *= -1.0f;
    }
    hgData->unk1B4.x += sp3C.x;
    hgData->unk1B4.y += sp3C.y;
    hgData->unk1B4.z += sp3C.z;
}

STATIC_FUNC void hangGlider_802F3694(HangGliderData* hgData) {
    f32 sp34;
    f32 tmp;
    f32 tmp2;
    f32 tmp3;
    f32 var_fa0_3;
    f32 sp20;
    f32 sp1C;
    f32 sp18;
    f32 var_fv0;

    var_fa0_3 = ABS_NOEQ(hgData->unk200.y);
    if (var_fa0_3 < 0.1f) {
        return;
    }

    sp1C = -hgData->unk200.y;
    sp18 = hgData->unk200.z;
    sp20 = uvSqrtF(SQ(sp1C) + SQ(sp18));
    if (sp20 > 0.01f) {
        sp18 /= sp20;
        sp1C /= sp20;
        if (sp1C < 0.0f) {
            sp1C = -sp1C;
        }
    } else {
        sp1C = 0.0f;
        sp18 = 1.0f;
    }
    tmp = uvAtan2F(sp18, sp1C);
    tmp2 = hangGlider_802F41AC(&D_8034F1C8, tmp, sp20);
    sp34 = 3.0f * tmp2 * hgData->unk200.z * hgData->unk200.z;
    if (sp34 < -10.0f) {
        sp34 = -10.0f;
    }
    if (sp34 > 200.0f) {
        sp34 = 200.0f;
    }

    if (hgData->unk10.m[3][2] > 1000.0f) {
        var_fv0 = 1.0f - ((hgData->unk10.m[3][2] - 1000.0f) / 100.0f);
        if (var_fv0 < 0.0f) {
            var_fv0 = 0.0f;
        }
        sp34 *= var_fv0;
    }
    var_fa0_3 = ABS_NOEQ(hgData->unk88);
    sp34 *= (1.0f - (uvSqrtF(var_fa0_3) * 0.87f));
    if ((hgData->unk88 != 0) && (hgData->unk200.y < 0.0f)) {
        hgData->unk1B4.y -= 0.25f * sp34;
    }
    if (hgData->unkE9 != 0) {
        tmp3 = 1.0f - ((hgData->unk18C.y * 0.5f) / 12.0f);
        sp34 *= tmp3;
    }
    hgData->unk1B4.z += sp34;
}

STATIC_FUNC void hangGlider_802F391C(HangGliderData* hgData) {
    Vec3F sp2C;
    Vec3F sp20;

    if (hgData->unk8C != 2) {
        env_802E1754(hgData->unk10.m[3][0], hgData->unk10.m[3][1], hgData->unk10.m[3][2], &sp20);
        sp20.x *= hgData->unk2F8;
        sp20.y *= hgData->unk2F8;
        sp20.z *= hgData->unk2F8;
        uvMat4LocalToWorld(&hgData->unk10C, &sp2C, &sp20);
    } else {
        sp2C.x = sp2C.y = sp2C.z = 0.0f;
        sp20.x = sp20.y = sp20.z = 0.0f;
    }
    hgData->unk200.x = sp2C.x - hgData->unk18C.x;
    hgData->unk200.y = sp2C.y - hgData->unk18C.y;
    hgData->unk200.z = sp2C.z - hgData->unk18C.z;
}

STATIC_FUNC void hangGlider_802F39F8(HangGliderData* hgData) {
    Vec3F sp1C;

    sp1C.x = 0.0f;
    sp1C.y = 0.0f;
    sp1C.z = -hgData->unk2F0 * 9.8f;
    uvMat4LocalToWorld(&hgData->unk10C, &hgData->unk1F4, &sp1C);
    hgData->unk1B4.x += hgData->unk1F4.x;
    hgData->unk1B4.y += hgData->unk1F4.y;
    hgData->unk1B4.z += hgData->unk1F4.z;
}

STATIC_FUNC void hangGlider_802F3A80(HangGliderData* hgData) {
    Vec3F sp24C;
    f32 sp248;
    f32 sp244;
    f32 sp240;
    f32 sp23C;
    u8 sp23B;
    u8 i;
    Unk802D3658_Unk1120* temp_v0_4;
    Unk802D3658_Unk1228* temp_s1;
    Unk80362690_Unk0* unkC;
    s32 sp228;
    s32 sp224;
    Vec3F sp218;
    Vec3F sp20C;
    Vec3F sp200;
    Mtx4F sp1C0;
    Unk802D3658_Unk1224 sp7C;

    hangGlider_802F4370(hgData);
    for (i = 0; i < 4; i++) {
        hgData->unkCC[i] = 0.0f;
        hgData->unk91[i] = 0;
    }

    hgData->unk8D = 0;
    hgData->unkE8 = 0;
    sp224 = 0;
    hgData->unk8E = sp23B = func_802DB050(&D_803680A0, &D_803681A8, hgData->objId, hgData->unk2, &hgData->unk10);

    for (i = 0; i < sp23B; i++) {
        temp_s1 = &D_803681A8.unk4[i];
        func_802DC814(temp_s1, (Vec3F*)hgData->unk10.m[3]);
        func_802DBE64(&D_803680A0, &D_803681A8, i, &hgData->unk10C);
        uvVec3Copy(&hgData->unk9C[i], &temp_s1->unkC);
        hgData->unk95[i] = temp_s1->unk0;
        hgData->unk91[i] = temp_s1->collisionType;
        hgData->unkCC[i] = uvVec3Dot(&hgData->unk18C, &temp_s1->unk34);
        switch (temp_s1->collisionType) {
        case 2:
            sp248 = sp244 = ballsPopped(temp_s1->surfaceId, &hgData->unk1A4, &D_803681A8);
            if (sp244 != 0.00f) {
                break;
            }
            return;
        case 4:
            break;
        case 1:
        case 8:
            sp23C = ABS_NOEQ(hgData->unk1A4.z * 2.52f);
            sp240 = ABS_NOEQ(hgData->unk1A4.y * 2.520f); // different rodata float literal
            if (((temp_s1->unk0 == 3) && ((hgData->unk88 > 0.75f) || (hgData->unk8C == 1)) && (sp23C < 50.0f) && (sp240 < 50.0f)) || (D_8034F850 < 2.0f)) {
                sp228 = hgData->unk8C;
                hgData->unk8D = 0;
                hgData->unk8C = 1;
                sp244 = 0.0f;
                if (D_8034F850 < 2.0f) {
                    sp248 = 1.0f;
                } else {
                    sp248 = 0.53f;
                }
                padsLandedPadStrip(hgData->unk10.m[3][0], hgData->unk10.m[3][1], hgData->unk10.m[3][2], &hgData->unk5C);
                if (sp228 == 0) {
                    if ((sp23C < 15.0f) && (sp240 < 15.0f)) {
                        unkC = &D_80362690->unkC[hgData->contIdx];
                        unkC->unk24 = sp23C;
                        if (hgData->unk5C != 0) {
                            hgData->unk4 = 0xFFFF;
                        } else {
                            hgData->unk4 = D_8036830C;
                        }
                    } else if (D_8034F850 > 2.0f) {
                        unkC = &D_80362690->unkC[hgData->contIdx];
                        unkC->unk24 = sp23C;
                    }
                }
            } else {
                hgData->unk8D = temp_s1->collisionType;
                hgData->unk8C = 2;
                sp248 = 0.8f;
                sp244 = 0.7f;
                if (hgData->unk5C != 0) {
                    hgData->unk4 = 0xF7FB;
                } else {
                    hgData->unk4 = D_8036830C;
                }
                if (hgData->unk1B0 < 2 /*.0f*/) {
                    sp248 = 0.8f;
                    sp248 *= hgData->unk1B0 * 0.5f;
                    sp244 = 0.7f;
                    sp244 *= hgData->unk1B0 * 0.5f;
                }
            }
            break;
        default:
            _uvDebugPrintf("gmot : unknown collision type [%d]\n", temp_s1->collisionType);
            break;
        }

        if (temp_s1->collisionType != 4) {
            if ((hgData->unk8C != 4) && ((hgData->unk8C != 1) || (hgData->unk1B0 >= 0.5f))) {
                sp24C.x = -hgData->unk18C.x;
                sp24C.y = -hgData->unk18C.y;
                sp24C.z = -hgData->unk18C.z;
                func_802DC1DC(&hgData->unk1DC, &temp_s1->unk28, &sp24C, 4.0f * sp244, 1.2f * sp244, 2.0f * sp244);
                func_802DC074(&hgData->unk14C, &hgData->unk18C, &hgData->unk1A4, &temp_s1->unk34, sp248);
                if (D_8034F850 > 2.0f) {
                    hgData->unk90++;
                }
                if (hgData->unk90 >= 91) {
                    hgData->unk8C = 2;
                }
            }
        }

        if (hgData->unk8C != 3) {
            if (temp_s1->collisionType != 4) {
                if ((temp_s1->collisionType == 2) && ballsObjIdExists(temp_s1->surfaceId)) {
                    break;
                }
                temp_v0_4 = &D_803680A0.unk4[temp_s1->unk0];
                func_802DCA5C(&temp_v0_4->unk28, &temp_v0_4->unk1C, &temp_s1->unk28, &temp_s1->unk34, &sp218);
                sp20C.x = hgData->unk10.m[3][0];
                sp20C.y = hgData->unk10.m[3][1];
                sp20C.z = hgData->unk10.m[3][2];
                uvMat4Copy(&sp1C0, &hgData->unk10);
                uvMat4LocalTranslate(&sp1C0, sp218.x, sp218.y, sp218.z);
                sp200.x = sp1C0.m[3][0];
                sp200.y = sp1C0.m[3][1];
                sp200.z = sp1C0.m[3][2];
                func_802DB224(&sp7C, 0xFF, hgData->objId, hgData->unk2, &sp20C, &sp200);
                if (sp7C.unk0 > 0) {
                    sp224++;
                } else {
                    uvMat4LocalTranslate(&hgData->unk10, sp218.x, sp218.y, sp218.z);
                    hgData->unk308.x = hgData->unk10.m[3][0];
                    hgData->unk308.y = hgData->unk10.m[3][1];
                    hgData->unk308.z = hgData->unk10.m[3][2];
                }
            }
        }
    }
    if ((hgData->unkE8 == 0) && (sp23B) && (sp224 == sp23B)) {
        hgData->unk8C = 3;
        _uvDebugPrintf("glider: you got stuck - forcing an instant crash\n");
    }
}

STATIC_FUNC f32 hangGlider_802F41AC(Unk8034F1C8* arg0, f32 arg1, f32 arg2) {
    s32 i;
    f32 x0;
    f32 x1;
    f32 y1;
    f32 y0;
    f32 unkB8_x0;
    f32 unkB8_x1;
    f32 unkB8_y0;
    f32 unkB8_y1;
    f32 temp_ft0;
    f32 temp_ft2;
    f32 tmp3;

    for (i = 0; i < ARRAY_COUNT(arg0->unk0); i++) {
        if (arg1 < arg0->unk0[i].x) {
            break;
        }
    }

    if ((i == 0) || (i == ARRAY_COUNT(arg0->unk0))) {
        return 0.0f;
    }

    x0 = arg0->unk0[i - 1].x;
    x1 = arg0->unk0[i].x;
    y0 = arg0->unk0[i - 1].y;
    y1 = arg0->unk0[i].y;
    temp_ft0 = (x1 - arg1) / (x1 - x0);
    tmp3 = (temp_ft0 * y0) + ((1.0f - temp_ft0) * y1);

    for (i = 0; i < ARRAY_COUNT(arg0->unkB8); i++) {
        if (arg2 < arg0->unkB8[i].x) {
            break;
        }
    }
    if ((i == 0) || (i == ARRAY_COUNT(arg0->unkB8))) {
        return 0.0f;
    }
    unkB8_x0 = arg0->unkB8[i - 1].x;
    unkB8_x1 = arg0->unkB8[i].x;
    unkB8_y0 = arg0->unkB8[i - 1].y;
    unkB8_y1 = arg0->unkB8[i].y;
    temp_ft2 = (unkB8_x1 - arg2) / (unkB8_x1 - unkB8_x0);
    return ((temp_ft2 * unkB8_y0) + ((1.0f - temp_ft2) * unkB8_y1)) * tmp3;
}

STATIC_FUNC f32 hangGlider_802F42DC(Unk8034F2D0* arg0, f32 arg1) {
    f32 x0;
    f32 x1;
    f32 y0;
    f32 y1;
    f32 temp_ft3;
    f32 tmp;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(arg0->unk0); i++) {
        if (arg1 < arg0->unk0[i].x) {
            break;
        }
    }
    if ((i == 0) || (i == ARRAY_COUNT(arg0->unk0))) {
        return 0.0f;
    }
    x0 = arg0->unk0[i - 1].x;
    x1 = arg0->unk0[i].x;
    y0 = arg0->unk0[i - 1].y;
    y1 = arg0->unk0[i].y;
    temp_ft3 = (x1 - arg1) / (x1 - x0);
    tmp = (1.0f - temp_ft3) * y1;
    return tmp + (temp_ft3 * y0);
}

STATIC_FUNC void hangGlider_802F4370(HangGliderData* hgData) {
    f32 temp_fv1;

    if ((hgData->unk21C == 3) || (hgData->unk21C == 4)) {
        hgData->unk20C = hgData->unk240;
    } else {
        hgData->unk20C += 0.5f * D_8034F854;
    }
    if (hgData->unk20C < 0.0f) {
        hgData->unk20C = 0.0f;
    } else if (hgData->unk20C > 1.0f) {
        hgData->unk20C = 1.0f;
    }

    temp_fv1 = 1.0f - hgData->unk20C;
    D_803682F0.x = 0.0f;
    D_803682F0.y = (hgData->unk27C.y * temp_fv1) + (hgData->unk20C * hgData->unk2B8.y);
    D_803682F0.z = (hgData->unk27C.z * temp_fv1) + (hgData->unk20C * hgData->unk2B8.z);
    D_803680A0.unk4[3].unk1C.x = D_803682F0.x;
    D_803680A0.unk4[3].unk1C.y = D_803682F0.y;
    D_803680A0.unk4[3].unk1C.z = D_803682F0.z;
}
