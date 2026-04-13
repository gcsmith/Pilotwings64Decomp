#include "common.h"
#include <uv_math.h>
#include <uv_matrix.h>
#include <uv_vector.h>
#include "birdman.h"
#include "code_61A60.h"
#include "code_66F70.h"
#include "code_9A960.h"
#include "balls.h"
#include "environment.h"
#include "snd.h"

typedef struct {
    Vec2F unk0[23];
    Vec2F unkB8[11];
} Unk8034E824;

typedef struct {
    Vec2F unk0[20];
} Unk8034E934;

f32 D_8034E820 = 0.175f;

Unk8034E824 D_8034E824 = {
    {

     { -1.570797f, 0.0f },  { -0.26179948f, 0.005f }, { -0.2094396f, 0.01f }, { -0.1570797f, 0.02f }, { -0.0872665f, 0.05f }, { 0.0f, 0.1f },
     { 0.0523599f, 0.15f }, { 0.0698132f, 0.2f },     { 0.07679452f, 0.5f },  { 0.08028518f, 0.85f }, { 0.08552117f, 1.05f }, { 0.090757154f, 1.0f },
     { 0.1047198f, 0.85f }, { 0.1221731f, 1.05f },    { 0.1396264f, 1.43f },  { 0.1570797f, 1.65f },  { 0.174533f, 1.85f },   { 0.1919863f, 1.85f },
     { 0.2094396f, 1.15f }, { 0.26179948f, 0.8f },    { 0.31415939f, 0.5f },  { 0.52359897f, 0.5f },  { 1.570797f, 0.5f } },
    {

     { 0.0f, 0.0f },
     { 0.5f, 0.1f },
     { 5.0f, 0.25f },
     { 10.0f, 0.8f },
     { 20.0f, 1.0f },
     { 30.0f, 0.9f },
     { 35.0f, 0.75f },
     { 40.0f, 0.54f },
     { 50.0f, 0.35f },
     { 60.0f, 0.22f },
     { 100.0f, 0.0f } }
};

Unk8034E934 D_8034E934 = {
    { { 0.0f, 0.0f },   { 0.3f, 0.0f },   { 1.7f, 0.0f },   { 3.0f, 0.0f },   { 7.0f, 0.6f },   { 13.0f, -1.3f }, { 15.0f, -2.0f },
     { 18.0f, -2.2f }, { 20.0f, -2.5f }, { 21.0f, -1.8f }, { 23.9f, -1.0f }, { 24.0f, 0.0f },  { 24.1f, 1.0f },  { 25.0f, 2.0f },
     { 33.5f, 2.2f },  { 36.0f, 2.0f },  { 51.0f, 1.8f },  { 67.0f, 1.3f },  { 81.5f, 20.0f }, { 100.0f, 50.0f } }
};

// used in bird_802CEBA0
Vec3F D_8034E9D4 = { 0.0f, 0.0f, 0.0f };

Unk802D3658_Unk111C D_803593F0;
Unk802D3658_Unk1224 D_803594F8;
u16 D_8035963C;

// forward declarations
void bird_802CF24C(BirdmanData* bmData);
void bird_802CF5B4(BirdmanData* bmData);
void bird_802CF640(BirdmanData* bmData);
s32 bird_802CF76C(BirdmanData* bmData);
void bird_802CF8A4(BirdmanData* bmData);
void bird_802CFAC8(BirdmanData* bmData);
void bird_802CFEA8(BirdmanData* bmData);
void bird_802CFF74(BirdmanData* bmData);
void bird_802D0080(BirdmanData* bmData);
void bird_802D0ABC(BirdmanData* bmData);
f32 bird_802D08F8(Unk8034E824*, f32, f32);
f32 bird_802D0A28(Unk8034E934*, f32);

void bird_802CEBA0(BirdmanData* bmData) {
    Vec3F sp2C;
    s32 pad;

    sp2C = D_8034E9D4;
    D_803593F0.unk0 = 4;
    D_803593F0.unk4[0].unk0 = 1;
    uvVec3Copy(&D_803593F0.unk4[0].unk28, &bmData->unk32C);
    uvVec3Copy(&D_803593F0.unk4[0].unk1C, &bmData->unk320);
    D_803593F0.unk4[1].unk0 = 1;
    uvVec3Copy(&D_803593F0.unk4[1].unk28, &bmData->unk338);
    uvVec3Copy(&D_803593F0.unk4[1].unk1C, &bmData->unk320);
    D_803593F0.unk4[2].unk0 = 1;
    uvVec3Copy(&D_803593F0.unk4[2].unk28, &sp2C);
    uvVec3Copy(&D_803593F0.unk4[2].unk1C, &bmData->unk320);
    D_803593F0.unk4[3].unk0 = 1;
    uvVec3Copy(&D_803593F0.unk4[3].unk28, &sp2C);
    uvVec3Copy(&D_803593F0.unk4[3].unk1C, &bmData->unk344);
    bird_802CECB8(bmData);
    D_8035963C = 0xF7F8;
}

void bird_802CECB8(BirdmanData* bmData) {
    s32 pad;

    bmData->unk170 = 0;
    bmData->unk174.z = 1.0f;
    bmData->unk168 = 0.0f;
    bmData->unk16C = 0.0f;
    bmData->unk174.y = 0.0f;
    bmData->unk174.x = 0.0f;
    bmData->unk228.z = 0.0f;
    bmData->unk228.y = 0.0f;
    bmData->unk228.x = 0.0f;
    bmData->unk218.z = 0.0f;
    bmData->unk218.y = 0.0f;
    bmData->unk218.x = 0.0f;
    bmData->unk234.z = 0.0f;
    bmData->unk234.y = 0.0f;
    bmData->unk234.x = 0.0f;
    bmData->unk250.z = 0.0f;
    bmData->unk250.y = 0.0f;
    bmData->unk250.x = 0.0f;
    bmData->unk25C.y = 0.0f;
    bmData->unk24C = 0.0f;
    bmData->unk248 = bmData->unk24C;
    bmData->unk244 = bmData->unk24C;
    bmData->unk25C.x = 0.0f;
    bmData->unk268.y = 0.0f;
    bmData->unk268.x = 0.0f;
    bmData->unk25C.z = 1.0f;
    bmData->unk268.z = -9.8f;
    bmData->unk274.x = 0.0f;
    bmData->unk274.y = 0.0f;
    bmData->unk274.z = 0.0f;
    bmData->unk224 = 0.0f;
    bmData->unk240 = 0.0f;
    bmData->unk280 = 0.0f;
    bmData->unk106 = 0;
    bmData->unk15C = 0;
    bmData->unkE0 = 0;
    bmData->unk160 = 0.0f;

    uvMat4Copy(&bmData->unk1C0, &bmData->unk10);
    bmData->unk1C0.m[3][0] = 0.0f;
    bmData->unk1C0.m[3][1] = 0.0f;
    bmData->unk1C0.m[3][2] = 0.0f;
    uvMat4LocalToWorld(&bmData->unk1C0, &bmData->unk218, &bmData->unk200);
    uvVec3Normal(&bmData->unk20C, &bmData->unk200);
    bmData->unk224 = uvVec3Len(&bmData->unk218);
    bmData->unk40C = 1;
    bmData->unk400.x = bmData->unk10.m[3][0];
    bmData->unk400.y = bmData->unk10.m[3][1];
    bmData->unk400.z = bmData->unk10.m[3][2];
}

void bird_802CEDF8(BirdmanData* bmData) {
    Vec3F sp44;
    s32 pad;

    uvMat4Copy(&bmData->unk1C0, &bmData->unk10);
    bmData->unk1C0.m[3][0] = 0.0f;
    bmData->unk1C0.m[3][1] = 0.0f;
    bmData->unk1C0.m[3][2] = 0.0f;
    uvMat4InvertTranslationRotation(&bmData->unk180, &bmData->unk1C0);
    uvMat4LocalToWorld(&bmData->unk180, &bmData->unk200, &bmData->unk218);
    bird_802CF8A4(bmData);
    bird_802CFF74(bmData);
    bird_802CFEA8(bmData);
    if (bmData->unk104 != 1) {
        bird_802CFAC8(bmData);
    }
    if (bmData->unk105 == 0) {
        switch (bmData->unk104) {
        case 2:
            return;
        case 0:
            bird_802CF24C(bmData);
            break;
        case 1:
            bird_802CF640(bmData);
            break;
        case 3:
            bird_802CF5B4(bmData);
            break;
        default:
            break;
        }
    } else {
        bmData->unk250.z = -bmData->unk2B4 * 5.6f * bmData->unkE4;
        func_80313E18(&bmData->unk25C, &bmData->unk10);
        bmData->unk200.x = func_80313AF4(0.0f, bmData->unk200.x, 10.0f);
        bmData->unk200.y = func_80313AF4(0.0f, bmData->unk200.y, 10.0f);
        bmData->unk200.z = func_80313AF4(0.0f, bmData->unk200.z, 10.0f);
        bmData->unk244 = func_80313AF4(0.0f, bmData->unk244, 10.0f);
        bmData->unk248 = func_80313AF4(0.0f, bmData->unk248, 10.0f);
        bmData->unk24C = func_80313AF4(0.0f, bmData->unk24C, 10.0f);
        bmData->unk218.x = func_80313AF4(0.0f, bmData->unk218.x, 10.0f);
        bmData->unk218.y = func_80313AF4(0.0f, bmData->unk218.y, 10.0f);
        bmData->unk218.z = func_80313AF4(0.0f, bmData->unk218.z, 10.0f);
        bmData->unk234.z = 0.0f;
        bmData->unk234.y = 0.0f;
        bmData->unk234.x = 0.0f;
        bmData->unk228.z = 0.0f;
        bmData->unk228.y = 0.0f;
        bmData->unk228.x = 0.0f;
        bmData->unk250.y = 0.0f;
        bmData->unk250.x = 0.0f;
        if (bmData->unk2D0 > 1.9f) {
            bmData->unk105 = 0;
            bmData->unk164 = 2.5f;
        }
    }

    if (bmData->unk105 == 0) {
        sp44.x = bmData->unk10.m[2][0];
        sp44.y = bmData->unk10.m[2][1];
        sp44.z = bmData->unk10.m[2][2];
    } else {
        sp44.x = bmData->unk174.x;
        sp44.y = bmData->unk174.y;
        sp44.z = bmData->unk174.z;
    }
    func_80313C94(&sp44, &bmData->unk25C, 2.0f);
    uvMat4LocalToWorld(&bmData->unk1C0, &bmData->unk234, &bmData->unk228);
    bmData->unk218.x += D_8034F854 * bmData->unk234.x;
    bmData->unk218.y += D_8034F854 * bmData->unk234.y;
    bmData->unk218.z += D_8034F854 * bmData->unk234.z;
    bmData->unk244 += D_8034F854 * bmData->unk250.x;
    bmData->unk248 += D_8034F854 * bmData->unk250.y;
    bmData->unk24C += D_8034F854 * bmData->unk250.z;
    uvMat4LocalTranslate(&bmData->unk10, bmData->unk200.x * D_8034F854, bmData->unk200.y * D_8034F854, bmData->unk200.z * D_8034F854);
    uvMat4RotateAxis(&bmData->unk10, bmData->unk24C * D_8034F854, 'z');
    uvMat4RotateAxis(&bmData->unk10, bmData->unk244 * D_8034F854, 'x');
    uvMat4RotateAxis(&bmData->unk10, bmData->unk248 * D_8034F854, 'y');
    bmData->unk228.x = 0.0f;
    bmData->unk228.y = 0.0f;
    bmData->unk228.z = 0.0f;
    bmData->unk250.x = 0.0f;
    bmData->unk250.y = 0.0f;
    bmData->unk250.z = 0.0f;
    if (bmData->unk104 != 3) {
        bird_802D0ABC(bmData);
    }
    bird_802CF76C(bmData);
    if (bmData->unk104 != 2) {
        bird_802D0080(bmData);
    }
    bmData->unk224 = uvVec3Len(&bmData->unk218);
    bmData->unk240 = uvVec3Len(&bmData->unk234);
}

void bird_802CF24C(BirdmanData* bmData) {
    f32 var_fa1;
    f32 var_fa0;
    f32 var_fv0;
    f32 temp_fv0;
    f32 var_fv1;

    var_fv1 = uvSqrtF(SQ(bmData->unk10.m[1][0]) + SQ(bmData->unk10.m[1][1])) * 0.8f;
    if (bmData->unk274.y > 0.0f) {
        var_fa1 = bmData->unk274.y * 0.2f * var_fv1;
    } else {
        var_fa1 = bmData->unkE8 * var_fv1;
    }

    bmData->unk250.x += -bmData->unk2B0 * 6.4f * var_fa1;
    temp_fv0 = uvSqrtF(SQ(bmData->unk10.m[0][0]) + SQ(bmData->unk10.m[0][1]));
    var_fa1 = bmData->unkE4 * (temp_fv0 * 0.9f);

    if (ABS_NOEQ(bmData->unk200.y) < 20.0f) {
        var_fa1 *= ABS_NOEQ(bmData->unk200.y) / 20.0f;
    }

    if (bmData->unk224 > 35.0f) {
        var_fv0 = 20.0f / (bmData->unk224 - 15.0f);
        if (var_fv0 < 0.25f) {
            var_fv0 = 0.25f;
        } else if (var_fv0 > 1.0f) {
            var_fv0 = 1.0f;
        }
        var_fa1 *= var_fv0;
    }
    bmData->unk250.y += uvSinF(-bmData->unkD0) * bmData->unk2B4 * 5.6f * var_fa1;
    bmData->unk250.z -= uvCosF(-bmData->unkD0) * bmData->unk2B4 * 5.6f * bmData->unkE4;
    bmData->unk244 = func_80313AF4(0.0f, bmData->unk244, 3.0f);
    bmData->unk248 = func_80313AF4(0.0f, bmData->unk248, 3.0f);
    bmData->unk24C = func_80313AF4(0.0f, bmData->unk24C, 3.0f);

    var_fv1 = uvSqrtF(SQ(bmData->unk268.y) + SQ(bmData->unk268.z + (bmData->unk2A4 * 9.8f)));
    if (bmData->unk268.y < 0.0f) {
        var_fv1 = -var_fv1;
        var_fv1 *= 0.34f;
    } else {
        var_fv1 *= 0.34f;
    }

    var_fa0 = uvSqrtF(SQ(bmData->unk268.x) + SQ(bmData->unk268.z + (bmData->unk2A4 * 9.8f))) * 0.29f;

    if (bmData->unk268.x > 0.0f) {
        var_fa0 = -var_fa0;
    }

    bmData->unk250.x += var_fv1;
    bmData->unk250.y += var_fa0;
    var_fa1 = SQ(bmData->unk200.x);
    if (bmData->unk200.x < 0.0f) {
        var_fa1 = -var_fa1;
    }
    bmData->unk24C -= 0.005f * var_fa1;
}

void bird_802CF5B4(BirdmanData* bmData) {
    bmData->unk228.x = bmData->unk200.x * -0.2f;
    bmData->unk228.y = bmData->unk200.y * -0.2f;
    bmData->unk228.z = bmData->unk200.z * -0.2f;
    bmData->unk244 = func_80313AF4(0.0f, bmData->unk244, 3.0f);
    bmData->unk248 = func_80313AF4(0.0f, bmData->unk248, 3.0f);
    bmData->unk24C = func_80313AF4(0.0f, bmData->unk24C, 3.0f);
}

void bird_802CF640(BirdmanData* bmData) {
    Vec3F sp3C;
    Vec3F sp30;

    if (bmData->unk160 == 0.0f) {
        bmData->unk160 = D_8034F850;
    }
    sp3C.x = 0.0f;
    sp3C.y = 0.0f;
    sp3C.z = -0.5f;
    sp30.x = bmData->unk268.x * 0.2f;
    sp30.y = bmData->unk268.y * 0.2f;
    sp30.z = bmData->unk268.z * 0.2f;
    func_802DC1DC(&bmData->unk250, &sp3C, &sp30, 0.5f, 0.5f, 0.5f);
    bmData->unk244 = func_80313AF4(0.0f, bmData->unk244, 0.35f);
    bmData->unk248 = func_80313AF4(0.0f, bmData->unk248, 0.35f);
    bmData->unk24C = func_80313AF4(0.0f, bmData->unk24C, 0.35f);
    if ((D_8034F850 - bmData->unk160) > 3.75f) {
        bmData->unk104 = 2;
    }
    bmData->unk105 = 0;
}

s32 bird_802CF76C(BirdmanData* bmData) {
    s32 pad;
    u8 temp_v0_2;
    f32* temp_s1; // TODO: double-check unk10 types
    s32 sp38;
    Vec3F* sp34;

    temp_s1 = bmData->unk10.m[3];
    sp38 = bmData->unk40C;
    temp_v0_2 = db_getgnd(&bmData->unk400, (Vec3F*)temp_s1, &sp38, &bmData->unk170, &bmData->unk168, &bmData->unk174);
    bmData->unk16C = temp_s1[2] - bmData->unk168;
    if (temp_v0_2 != 0) {
        bmData->unk106 = temp_v0_2;
        if (bmData->unk106 == 4) {
            bmData->unk15C = 1;
            bmData->unk104 = 2;
        } else {
            bmData->unk104 = 1;
        }
        sp34 = func_802E02EC();
        func_802E05CC(&bmData->unk10, sp34, &bmData->unk174, 0);
        uvVec3Copy(&bmData->unk150, sp34);
        bmData->unk4 = D_8035963C;
    }
    if (bmData->unk104 != 2) {
        bmData->unk400.x = temp_s1[0];
        bmData->unk400.y = temp_s1[1];
        bmData->unk400.z = temp_s1[2];
    }
    if (bmData->unk15C != 0) {
        return 0;
    }
    if (bmData->unk16C > 2.5f) {
        return 0;
    }
    return 1;
}

void bird_802CF8A4(BirdmanData* bmData) {
    Vec3F sp3C;
    Vec3F sp30;
    f32 var_fv1;
    f32 var_fa1;

    if (bmData->unk224 < 1.0f) {
        return;
    }
    sp3C.x = bmData->unk10.m[2][0];
    sp3C.y = bmData->unk10.m[2][1];
    sp3C.z = bmData->unk10.m[2][2];
    sp30.x = bmData->unk200.x / bmData->unk224;
    sp30.y = bmData->unk200.y / bmData->unk224;
    sp30.z = bmData->unk200.z / bmData->unk224;
    var_fv1 = ABS_NOEQ(uvVec3Dot(&sp3C, &sp30));
    if (var_fv1 < 0.1f) {
        var_fv1 = 0.1f;
    }

    var_fv1 *= bird_802D0A28(&D_8034E934, bmData->unk224);
    var_fv1 *= bmData->unk2AC;
    var_fa1 = -var_fv1 * 0.003f;
    var_fv1 = 1.0f;

    // FAKE
    sp3C.x = (var_fa1 * 1.0f) * bmData->unk200.x * bmData->unk200.x;
    if (bmData->unk200.x < 0.0f) {
        sp3C.x = -sp3C.x;
    }
    sp3C.y = (var_fa1 * 1.0f) * bmData->unk200.y * bmData->unk200.y;
    if (bmData->unk200.y < 0.0f) {
        sp3C.y = -sp3C.y;
    }

    if (bmData->unk224 < 10.0f) {
        var_fv1 *= 0;
        var_fa1 = -var_fv1 * 0.0030f;
    }
    sp3C.z = (var_fa1 * 1.0f) * bmData->unk200.z * bmData->unk200.z;
    if (bmData->unk200.z < 0.0f) {
        sp3C.z *= -1.0f;
    }
    bmData->unk228.x += sp3C.x;
    bmData->unk228.y += sp3C.y;
    bmData->unk228.z += sp3C.z;
}

void bird_802CFAC8(BirdmanData* bmData) {
    f32 var_ft5;
    f32 temp_fa0;
    f32 var_ft4;
    f32 var_fa0_3;
    f32 var_fv0;
    f32 temp_fv0_2;
    f32 var_fa1;
    f32 var_fa0;

    if (bmData->unk274.y > 0.0f) {
        var_fv0 = bmData->unk274.y;
    } else {
        var_fv0 = -bmData->unk274.y;
    }
    if (var_fv0 > 0.1f) {
        var_fa1 = -bmData->unk274.y;
        var_fa0 = bmData->unk274.z;
        temp_fv0_2 = uvSqrtF(SQ(var_fa1) + SQ(var_fa0));
        if (temp_fv0_2 > 0.01f) {
            var_fa1 /= temp_fv0_2;
            var_fa0 /= temp_fv0_2;
            if (var_fa1 < 0.0f) {
                var_fa1 = -var_fa1;
            }
        } else {
            var_fa1 = 1.0f;
            var_fa0 = 0.0f;
        }
        temp_fv0_2 = bird_802D08F8(&D_8034E824, uvAtan2F(var_fa0, var_fa1), temp_fv0_2);
        var_ft5 = D_8034E820 * 3.0f * temp_fv0_2 * bmData->unk274.z * bmData->unk274.z;
        if (var_ft5 < -10.0f) {
            var_ft5 = -10.0f;
        }
        if (var_ft5 > 200.0f) {
            var_ft5 = 200.0f;
        }
    } else {
        var_ft5 = 0.0f;
    }
    if (bmData->unk2D4 < 0.5f) {
        if (bmData->unk224 < 30.0f) {
            var_ft4 = uvCosF(bmData->unk2D4) * 1.3856f * bmData->unk2D0 * bmData->unk2D0;
            temp_fa0 = 2.25f * var_ft4;
        } else {
            var_ft4 = uvCosF(bmData->unk2D4) * 0.6928f * bmData->unk2D0 * bmData->unk2D0;
            temp_fa0 = 2.75f * var_ft4;
            if (bmData->unk200.z > 30.0f) {
                temp_fa0 = 0.0f;
            } else if (bmData->unk200.z > 20.0f) {
                temp_fa0 *= 1.0f - ((bmData->unk200.z - 20.0f) / 10.0f);
            }
        }
    } else {
        if (bmData->unk274.y > 0.0f) {
            var_ft4 = 0.0f;
        } else {
            f32 temp_ft3 = uvSinF(bmData->unk2D4) * -0.064950004f;
            f32 temp = bmData->unk274.y;
            var_ft4 = temp_ft3 * temp * temp;
        }
        temp_fa0 = 2.0f * uvSinF(bmData->unk2D4) * bmData->unk2D0 * bmData->unk2D0;
        if (bmData->unk224 > 15.0f) {
            temp_fa0 = 0.0f;
        } else {
            temp_fa0 *= (1.0f - (bmData->unk224 / 15.0f));
        }
    }
    var_ft5 += temp_fa0;
    if (bmData->unk10.m[3][2] > 875.0f) {
        var_fv0 = 1.0f - ((bmData->unk10.m[3][2] - 875.0f) / 75.0f);
        if (var_fv0 < 0) {
            var_fv0 = 0;
        }
    } else {
        var_fv0 = 1.0f;
    }
    var_ft5 *= var_fv0;
    var_ft4 *= var_fv0;
    bmData->unk228.z += var_ft5;
    bmData->unk228.y += var_ft4;
}

void bird_802CFEA8(BirdmanData* bmData) {
    Vec3F sp2C;
    Vec3F sp20;

    if (bmData->unk105 == 0) {
        if (bmData->unk104 != 1) {
            env_802E1754(bmData->unk10.m[3][0], bmData->unk10.m[3][1], bmData->unk10.m[3][2], &sp20);
            sp20.z *= bmData->unk2A8;
            uvMat4LocalToWorld(&bmData->unk180, &sp2C, &sp20);
        } else {
            sp2C.z = 0.0f;
            sp2C.y = 0.0f;
            sp2C.x = 0.0f;
            sp20.z = 0.0f;
            sp20.y = 0.0f;
            sp20.x = 0.0f;
        }
        bmData->unk274.x = sp2C.x - bmData->unk200.x;
        bmData->unk274.y = sp2C.y - bmData->unk200.y;
        bmData->unk274.z = sp2C.z - bmData->unk200.z;
    }
}

void bird_802CFF74(BirdmanData* bmData) {
    Vec3F sp24;
    f32 temp_fv0;

    if (bmData->unk105 == 0) {
        sp24.x = 0.0f;
        sp24.y = 0.0f;
        sp24.z = -bmData->unk2A4 * 9.8f;
        uvMat4LocalToWorld(&bmData->unk180, &bmData->unk268, &sp24);
        if (bmData->unk164 > 0.0f) {
            if (bmData->unk16C < 3.0f) {
                temp_fv0 = bmData->unk16C / 3.0f;
                bmData->unk268.x *= temp_fv0;
                bmData->unk268.y *= temp_fv0;
                bmData->unk268.z *= temp_fv0;
            }
            bmData->unk164 -= D_8034F854;
        }
        bmData->unk228.x += bmData->unk268.x;
        bmData->unk228.y += bmData->unk268.y;
        bmData->unk228.z += bmData->unk268.z;
    }
}

void bird_802D0080(BirdmanData* bmData) {
    Vec3F sp27C;
    f32 var_fs2;
    f32 var_fs1;
    s32 temp_v1;
    Unk802D3658_Unk1120* temp_v0_3;
    u8 sp26B;
    u8 i;
    Unk802D3658_Unk1228* temp_s1;
    f32 var_fv1;
    f32 var_fa0;
    s32 sp258;
    Vec3F sp24C;
    Vec3F sp240;
    Vec3F sp234;
    Vec3F sp228;
    Mtx4F sp1E8;
    Unk802D3658_Unk1224 spA4;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 temp_fa0;

    for (i = 0; i < 4; i++) {
        bmData->unk140[i] = 0.0f;
        bmData->unk108[i] = 0;
    }
    bmData->unk106 = 0;
    bmData->unk15C = 0;
    sp258 = 0;
    sp26B = func_802DB050(&D_803593F0, &D_803594F8, bmData->objId, bmData->unk2, &bmData->unk10);
    bmData->unk107 = sp26B;

    for (i = 0; i < sp26B; i++) {
        temp_s1 = &D_803594F8.unk4[i];
        func_802DC814(temp_s1, (Vec3F*)bmData->unk10.m[3]);
        func_802DBE64(&D_803593F0, &D_803594F8, i, &bmData->unk180);
        uvVec3Copy(&bmData->unk110[i], &temp_s1->unkC);
        bmData->unk10C[i] = temp_s1->unk0;
        bmData->unk108[i] = temp_s1->collisionType;
        bmData->unk140[i] = uvVec3Dot(&bmData->unk200, &temp_s1->unk34);
        switch (temp_s1->collisionType) {
        case 2:
            var_fs2 = var_fs1 = ballsPopped(temp_s1->surfaceId, &bmData->unk218, &D_803594F8);
            if (var_fs1 == 0.0f) {
                return;
            }
            break;
        case 4:
            if (bmData->unk104 != 1) {
                bmData->unk104 = 0;
            }
            bmData->unk15C = 1;
            bmData->unk106 = 0;
            break;
        case 1:
        case 8:
            if ((temp_s1->collisionType == 8) && (func_802DC97C(temp_s1->surfaceId) != 0)) {
                sndPlaySfxVolPitchPan(0x39, 1.0f, 1.0f, 0.0f);
            }
            if ((bmData->unk164 > 1.0f) && (bmData->unk16C < 3.0f) && (temp_s1->unk0 == 3)) {
                return;
            }
            if ((bmData->unk105 != 0) && (bmData->unk104 != 1)) {
                uvVec3Copy(&sp24C, &bmData->unk200);
                func_802DC074(&bmData->unk1C0, &bmData->unk200, &bmData->unk218, &temp_s1->unk34, 0.5f);
                temp_fv0 = ABS_NOEQ(sp24C.x - bmData->unk200.x);
                if (temp_fv0 < 0.1f) {
                    temp_fv1 = ABS_NOEQ(sp24C.y - bmData->unk200.y);
                    if (temp_fv1 < 0.1f) {
                        temp_fa0 = ABS_NOEQ(sp24C.y - bmData->unk200.z);
                        if (temp_fa0 < 0.1f) {
                            bmData->unk200.x += temp_s1->unk34.x;
                            bmData->unk200.y += temp_s1->unk34.y;
                            bmData->unk200.z += temp_s1->unk34.z;
                            uvMat4LocalToWorld(&bmData->unk1C0, &bmData->unk218, &bmData->unk200);
                            return;
                        }
                    }
                }
                bmData->unk10.m[3][0] += 0.01f * bmData->unk174.x;
                bmData->unk10.m[3][1] += 0.01f * bmData->unk174.y;
                bmData->unk10.m[3][2] += 0.01f * bmData->unk174.z;
                return;
            }

            var_fv1 = ABS_NOEQ(bmData->unk218.z * 2.52f);
            var_fa0 = ABS_NOEQ(bmData->unk218.y * 2.52f);
            if ((temp_s1->unk0 == 3) && (bmData->unk104 == 0) && (var_fv1 < 50.0f)) {
                bmData->unk106 = 0;
                var_fs2 = 0.0f;
                var_fs1 = 0.0f;
                temp_v1 = bmData->unk104;
                if (temp_v1 == 0) {
                    if ((var_fa0 > 50.0f) && (D_8034F850 > 2.0f)) {
                        bmData->unk104 = 1;
                    } else if (bmData->unk105 == 0) {
                        bmData->unk2D0 = 0.0f;
                        bmData->unk105 = 1;
                        bmData->unk10.m[3][0] += 0.025f * bmData->unk174.x;
                        bmData->unk10.m[3][1] += 0.025f * bmData->unk174.y;
                        bmData->unk10.m[3][2] = (bmData->unk168 - bmData->unk344.z) + (0.025f * bmData->unk174.z);
                        bmData->unk218.x = 0.0f;
                        bmData->unk218.y = 0.0f;
                        bmData->unk218.z = 0.0f;
                        bmData->unk200.x = 0.0f;
                        bmData->unk200.y = 0.0f;
                        bmData->unk200.z = 0.0f;
                        bmData->unk234.x = 0.0f;
                        bmData->unk234.y = 0.0f;
                        bmData->unk234.z = 0.0f;
                        bmData->unk228.x = 0.0f;
                        bmData->unk228.y = 0.0f;
                        bmData->unk228.z = 0.0f;
                    }
                }
            } else {
                bmData->unk106 = temp_s1->collisionType;
                bmData->unk104 = 1;
                var_fs2 = 0.5f;
                var_fs1 = 0.7f;
                if (bmData->unkE0 != 0) {
                    bmData->unk4 = 0xF7FB;
                } else {
                    bmData->unk4 = D_8035963C;
                }
                if (bmData->unk224 < 2.0f) {
                    var_fs2 *= bmData->unk224 / 2.0f;
                    var_fs1 *= bmData->unk224 / 2.0f;
                }
                if (bmData->unk106 == 4) {
                    bmData->unk15C = 1;
                }
            }
            break;
        default:
            _uvDebugPrintf("bmmot : unknown collision type [%d]\n", temp_s1->collisionType);
            break;
        }

        if ((bmData->unk105 == 0) && (temp_s1->collisionType != 4)) {
            sp27C.x = -bmData->unk200.x;
            sp27C.y = -bmData->unk200.y;
            sp27C.z = -bmData->unk200.z;
            func_802DC1DC(&bmData->unk250, &temp_s1->unk28, &sp27C, 20.0f * var_fs1, 5.6f * var_fs1, 9.2f * var_fs1);
            func_802DC074(&bmData->unk1C0, &bmData->unk200, &bmData->unk218, &temp_s1->unk34, var_fs2);
        }
        if (bmData->unk104 != 2) {
            if ((temp_s1->collisionType != 4) && (bmData->unk105 == 0)) {
                if ((temp_s1->collisionType == 2) && ballsObjIdExists(temp_s1->surfaceId)) {
                    break;
                }
                temp_v0_3 = &D_803593F0.unk4[temp_s1->unk0];
                func_802DCA5C(&temp_v0_3->unk28, &temp_v0_3->unk1C, &temp_s1->unk28, &temp_s1->unk34, &sp240);
                sp234.x = bmData->unk10.m[3][0];
                sp234.y = bmData->unk10.m[3][1];
                sp234.z = bmData->unk10.m[3][2];
                uvMat4Copy(&sp1E8, &bmData->unk10);
                uvMat4LocalTranslate(&sp1E8, sp240.x, sp240.y, sp240.z);
                sp228.x = sp1E8.m[3][0];
                sp228.y = sp1E8.m[3][1];
                sp228.z = sp1E8.m[3][2];
                func_802DB224(&spA4, 0xFF, bmData->objId, bmData->unk2, &sp234, &sp228);
                if (spA4.unk0 > 0) {
                    sp258++;
                } else {
                    uvMat4LocalTranslate(&bmData->unk10, sp240.x, sp240.y, sp240.z);
                    bmData->unk400.x = bmData->unk10.m[3][0];
                    bmData->unk400.y = bmData->unk10.m[3][1];
                    bmData->unk400.z = bmData->unk10.m[3][2];
                }
            }
        }
    }

    if (sp26B && (sp258 == sp26B)) {
        bmData->unk104 = 2;
        _uvDebugPrintf("birdman: you got stuck - forcing an instant crash\n");
    }
}

f32 bird_802D08F8(Unk8034E824* unkState, f32 arg1, f32 arg2) {
    s32 i;
    Vec2F p0;
    Vec2F p1;
    f32 a;
    Vec2F q0;
    Vec2F q1;
    f32 sum0;
    f32 sum1;

    for (i = 0; i < ARRAY_COUNT(unkState->unk0); i++) {
        if (arg1 < unkState->unk0[i].x) {
            break;
        }
    }
    if ((i == 0) || (i == ARRAY_COUNT(unkState->unk0))) {
        return 0.0f;
    }
    p0.x = unkState->unk0[i - 1].x;
    p1.x = unkState->unk0[i].x;
    p0.y = unkState->unk0[i - 1].y;
    p1.y = unkState->unk0[i].y;
    a = (p1.x - arg1) / (p1.x - p0.x);
    sum0 = (a * p0.y) + ((1.0f - a) * p1.y);

    for (i = 0; i < ARRAY_COUNT(unkState->unkB8); i++) {
        if (arg2 < unkState->unkB8[i].x) {
            break;
        }
    }
    if ((i == 0) || (i == ARRAY_COUNT(unkState->unkB8))) {
        return 0.0f;
    }
    q0.x = unkState->unkB8[i - 1].x;
    q1.x = unkState->unkB8[i].x;
    q0.y = unkState->unkB8[i - 1].y;
    q1.y = unkState->unkB8[i].y;
    a = (q1.x - arg2) / (q1.x - q0.x);
    sum1 = (a * q0.y) + ((1.0f - a) * q1.y);
    return sum1 * sum0;
}

f32 bird_802D0A28(Unk8034E934* unkState, f32 arg1) {
    f32 x1;
    f32 x0;
    f32 y0;
    f32 y1;
    f32 a;
    f32 b;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(unkState->unk0); i++) {
        if (arg1 < unkState->unk0[i].x) {
            break;
        }
    }
    if ((i == 0) || (i == ARRAY_COUNT(unkState->unk0))) {
        return 0.0f;
    }

    x0 = unkState->unk0[i - 1].x;
    x1 = unkState->unk0[i].x;
    y0 = unkState->unk0[i - 1].y;
    y1 = unkState->unk0[i].y;
    a = (x1 - arg1) / (x1 - x0);
    b = 1.0f - a;
    return (a * y0) + (b * y1);
}

void bird_802D0ABC(BirdmanData* bmData) {
    Mtx4F* temp_s2;
    Mtx4F sp44;
    Vec3F sp38;

    func_80313FD0(&bmData->unk350, bmData->unk2BC, &sp38);
    temp_s2 = &bmData->unk90;
    uvMat4LocalToWorld(temp_s2, &D_803593F0.unk4[0].unk28, &sp38);
    uvVec3Copy(&sp38, &bmData->unk320);
    uvMat4LocalToWorld(temp_s2, &D_803593F0.unk4[0].unk1C, &sp38);
    func_80313FD0(&bmData->unk350, bmData->unk2BC, &sp38);
    sp38.x = -sp38.x;
    uvMat4LocalToWorld(temp_s2, &D_803593F0.unk4[1].unk28, &sp38);
    uvVec3Copy(&sp38, &bmData->unk320);
    uvMat4LocalToWorld(temp_s2, &D_803593F0.unk4[1].unk1C, &sp38);
    uvMat4Copy(&sp44, temp_s2);
    uvMat4RotateAxis(&sp44, bmData->unk304, 'x');
    uvMat4RotateAxis(&sp44, bmData->unk308, 'y');
    uvMat4LocalToWorld(&sp44, &D_803593F0.unk4[3].unk1C, &bmData->unk344);
    uvVec3Copy(&sp38, &bmData->unk320);
    uvMat4LocalToWorld(temp_s2, &D_803593F0.unk4[2].unk1C, &sp38);
}
