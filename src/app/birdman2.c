#include "common.h"
#include <uv_math.h>
#include <uv_matrix.h>
#include <uv_vector.h>
#include "birdman.h"
#include "code_61A60.h"
#include "code_66160.h"
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
void bird_802CF24C(BirdmanData*);
void bird_802CF5B4(BirdmanData*);
void bird_802CF640(BirdmanData*);
s32 bird_802CF76C(BirdmanData*);
void bird_802CF8A4(BirdmanData*);
void bird_802CFAC8(BirdmanData*);
void bird_802CFEA8(BirdmanData*);
void bird_802CFF74(BirdmanData*);
void bird_802D0080(BirdmanData*);
void bird_802D0ABC(BirdmanData*);
f32 bird_802D08F8(Unk8034E824*, f32, f32);
f32 bird_802D0A28(Unk8034E934*, f32);

void bird_802CEBA0(BirdmanData* arg0) {
    Vec3F sp2C;
    s32 pad;

    sp2C = D_8034E9D4;
    D_803593F0.unk0 = 4;
    D_803593F0.unk4[0].unk0 = 1;
    uvVec3Copy(&D_803593F0.unk4[0].unk28, &arg0->unk32C);
    uvVec3Copy(&D_803593F0.unk4[0].unk1C, &arg0->unk320);
    D_803593F0.unk4[1].unk0 = 1;
    uvVec3Copy(&D_803593F0.unk4[1].unk28, &arg0->unk338);
    uvVec3Copy(&D_803593F0.unk4[1].unk1C, &arg0->unk320);
    D_803593F0.unk4[2].unk0 = 1;
    uvVec3Copy(&D_803593F0.unk4[2].unk28, &sp2C);
    uvVec3Copy(&D_803593F0.unk4[2].unk1C, &arg0->unk320);
    D_803593F0.unk4[3].unk0 = 1;
    uvVec3Copy(&D_803593F0.unk4[3].unk28, &sp2C);
    uvVec3Copy(&D_803593F0.unk4[3].unk1C, &arg0->unk344);
    bird_802CECB8(arg0);
    D_8035963C = 0xF7F8;
}

void bird_802CECB8(BirdmanData* arg0) {
    s32 pad;

    arg0->unk170 = 0;
    arg0->unk174.z = 1.0f;
    arg0->unk168 = 0.0f;
    arg0->unk16C = 0.0f;
    arg0->unk174.y = 0.0f;
    arg0->unk174.x = 0.0f;
    arg0->unk228.z = 0.0f;
    arg0->unk228.y = 0.0f;
    arg0->unk228.x = 0.0f;
    arg0->unk218.z = 0.0f;
    arg0->unk218.y = 0.0f;
    arg0->unk218.x = 0.0f;
    arg0->unk234.z = 0.0f;
    arg0->unk234.y = 0.0f;
    arg0->unk234.x = 0.0f;
    arg0->unk250.z = 0.0f;
    arg0->unk250.y = 0.0f;
    arg0->unk250.x = 0.0f;
    arg0->unk25C.y = 0.0f;
    arg0->unk24C = 0.0f;
    arg0->unk248 = arg0->unk24C;
    arg0->unk244 = arg0->unk24C;
    arg0->unk25C.x = 0.0f;
    arg0->unk268.y = 0.0f;
    arg0->unk268.x = 0.0f;
    arg0->unk25C.z = 1.0f;
    arg0->unk268.z = -9.8f;
    arg0->unk274.x = 0.0f;
    arg0->unk274.y = 0.0f;
    arg0->unk274.z = 0.0f;
    arg0->unk224 = 0.0f;
    arg0->unk240 = 0.0f;
    arg0->unk280 = 0.0f;
    arg0->unk106 = 0;
    arg0->unk15C = 0;
    arg0->unkE0 = 0;
    arg0->unk160 = 0.0f;

    uvMat4Copy(&arg0->unk1C0, &arg0->unk10);
    arg0->unk1C0.m[3][0] = 0.0f;
    arg0->unk1C0.m[3][1] = 0.0f;
    arg0->unk1C0.m[3][2] = 0.0f;
    uvMat4LocalToWorld(&arg0->unk1C0, &arg0->unk218, &arg0->unk200);
    uvVec3Normal(&arg0->unk20C, &arg0->unk200);
    arg0->unk224 = uvVec3Len(&arg0->unk218);
    arg0->unk40C = 1;
    arg0->unk400.x = arg0->unk10.m[3][0];
    arg0->unk400.y = arg0->unk10.m[3][1];
    arg0->unk400.z = arg0->unk10.m[3][2];
}

void bird_802CEDF8(BirdmanData* arg0) {
    Vec3F sp44;
    s32 pad;

    uvMat4Copy(&arg0->unk1C0, &arg0->unk10);
    arg0->unk1C0.m[3][0] = 0.0f;
    arg0->unk1C0.m[3][1] = 0.0f;
    arg0->unk1C0.m[3][2] = 0.0f;
    uvMat4InvertTranslationRotation(&arg0->unk180, &arg0->unk1C0);
    uvMat4LocalToWorld(&arg0->unk180, &arg0->unk200, &arg0->unk218);
    bird_802CF8A4(arg0);
    bird_802CFF74(arg0);
    bird_802CFEA8(arg0);
    if (arg0->unk104 != 1) {
        bird_802CFAC8(arg0);
    }
    if (arg0->unk105 == 0) {
        switch (arg0->unk104) {
        case 2:
            return;
        case 0:
            bird_802CF24C(arg0);
            break;
        case 1:
            bird_802CF640(arg0);
            break;
        case 3:
            bird_802CF5B4(arg0);
            break;
        default:
            break;
        }
    } else {
        arg0->unk250.z = -arg0->unk2B4 * 5.6f * arg0->unkE4;
        func_80313E18(&arg0->unk25C, &arg0->unk10);
        arg0->unk200.x = func_80313AF4(0.0f, arg0->unk200.x, 10.0f);
        arg0->unk200.y = func_80313AF4(0.0f, arg0->unk200.y, 10.0f);
        arg0->unk200.z = func_80313AF4(0.0f, arg0->unk200.z, 10.0f);
        arg0->unk244 = func_80313AF4(0.0f, arg0->unk244, 10.0f);
        arg0->unk248 = func_80313AF4(0.0f, arg0->unk248, 10.0f);
        arg0->unk24C = func_80313AF4(0.0f, arg0->unk24C, 10.0f);
        arg0->unk218.x = func_80313AF4(0.0f, arg0->unk218.x, 10.0f);
        arg0->unk218.y = func_80313AF4(0.0f, arg0->unk218.y, 10.0f);
        arg0->unk218.z = func_80313AF4(0.0f, arg0->unk218.z, 10.0f);
        arg0->unk234.z = 0.0f;
        arg0->unk234.y = 0.0f;
        arg0->unk234.x = 0.0f;
        arg0->unk228.z = 0.0f;
        arg0->unk228.y = 0.0f;
        arg0->unk228.x = 0.0f;
        arg0->unk250.y = 0.0f;
        arg0->unk250.x = 0.0f;
        if (arg0->unk2D0 > 1.9f) {
            arg0->unk105 = 0;
            arg0->unk164 = 2.5f;
        }
    }

    if (arg0->unk105 == 0) {
        sp44.x = arg0->unk10.m[2][0];
        sp44.y = arg0->unk10.m[2][1];
        sp44.z = arg0->unk10.m[2][2];
    } else {
        sp44.x = arg0->unk174.x;
        sp44.y = arg0->unk174.y;
        sp44.z = arg0->unk174.z;
    }
    func_80313C94(&sp44, &arg0->unk25C, 2.0f);
    uvMat4LocalToWorld(&arg0->unk1C0, &arg0->unk234, &arg0->unk228);
    arg0->unk218.x += D_8034F854 * arg0->unk234.x;
    arg0->unk218.y += D_8034F854 * arg0->unk234.y;
    arg0->unk218.z += D_8034F854 * arg0->unk234.z;
    arg0->unk244 += D_8034F854 * arg0->unk250.x;
    arg0->unk248 += D_8034F854 * arg0->unk250.y;
    arg0->unk24C += D_8034F854 * arg0->unk250.z;
    uvMat4LocalTranslate(&arg0->unk10, arg0->unk200.x * D_8034F854, arg0->unk200.y * D_8034F854, arg0->unk200.z * D_8034F854);
    uvMat4RotateAxis(&arg0->unk10, arg0->unk24C * D_8034F854, 'z');
    uvMat4RotateAxis(&arg0->unk10, arg0->unk244 * D_8034F854, 'x');
    uvMat4RotateAxis(&arg0->unk10, arg0->unk248 * D_8034F854, 'y');
    arg0->unk228.x = 0.0f;
    arg0->unk228.y = 0.0f;
    arg0->unk228.z = 0.0f;
    arg0->unk250.x = 0.0f;
    arg0->unk250.y = 0.0f;
    arg0->unk250.z = 0.0f;
    if (arg0->unk104 != 3) {
        bird_802D0ABC(arg0);
    }
    bird_802CF76C(arg0);
    if (arg0->unk104 != 2) {
        bird_802D0080(arg0);
    }
    arg0->unk224 = uvVec3Len(&arg0->unk218);
    arg0->unk240 = uvVec3Len(&arg0->unk234);
}

void bird_802CF24C(BirdmanData* arg0) {
    f32 var_fa1;
    f32 var_fa0;
    f32 var_fv0;
    f32 temp_fv0;
    f32 var_fv1;

    var_fv1 = uvSqrtF(SQ(arg0->unk10.m[1][0]) + SQ(arg0->unk10.m[1][1])) * 0.8f;
    if (arg0->unk274.y > 0.0f) {
        var_fa1 = arg0->unk274.y * 0.2f * var_fv1;
    } else {
        var_fa1 = arg0->unkE8 * var_fv1;
    }

    arg0->unk250.x += -arg0->unk2B0 * 6.4f * var_fa1;
    temp_fv0 = uvSqrtF(SQ(arg0->unk10.m[0][0]) + SQ(arg0->unk10.m[0][1]));
    var_fa1 = arg0->unkE4 * (temp_fv0 * 0.9f);

    if (ABS_NOEQ(arg0->unk200.y) < 20.0f) {
        var_fa1 *= ABS_NOEQ(arg0->unk200.y) / 20.0f;
    }

    if (arg0->unk224 > 35.0f) {
        var_fv0 = 20.0f / (arg0->unk224 - 15.0f);
        if (var_fv0 < 0.25f) {
            var_fv0 = 0.25f;
        } else if (var_fv0 > 1.0f) {
            var_fv0 = 1.0f;
        }
        var_fa1 *= var_fv0;
    }
    arg0->unk250.y += uvSinF(-arg0->unkD0) * arg0->unk2B4 * 5.6f * var_fa1;
    arg0->unk250.z -= uvCosF(-arg0->unkD0) * arg0->unk2B4 * 5.6f * arg0->unkE4;
    arg0->unk244 = func_80313AF4(0.0f, arg0->unk244, 3.0f);
    arg0->unk248 = func_80313AF4(0.0f, arg0->unk248, 3.0f);
    arg0->unk24C = func_80313AF4(0.0f, arg0->unk24C, 3.0f);

    var_fv1 = uvSqrtF(SQ(arg0->unk268.y) + SQ(arg0->unk268.z + (arg0->unk2A4 * 9.8f)));
    if (arg0->unk268.y < 0.0f) {
        var_fv1 = -var_fv1;
        var_fv1 *= 0.34f;
    } else {
        var_fv1 *= 0.34f;
    }

    var_fa0 = uvSqrtF(SQ(arg0->unk268.x) + SQ(arg0->unk268.z + (arg0->unk2A4 * 9.8f))) * 0.29f;

    if (arg0->unk268.x > 0.0f) {
        var_fa0 = -var_fa0;
    }

    arg0->unk250.x += var_fv1;
    arg0->unk250.y += var_fa0;
    var_fa1 = SQ(arg0->unk200.x);
    if (arg0->unk200.x < 0.0f) {
        var_fa1 = -var_fa1;
    }
    arg0->unk24C -= 0.005f * var_fa1;
}

void bird_802CF5B4(BirdmanData* arg0) {
    arg0->unk228.x = arg0->unk200.x * -0.2f;
    arg0->unk228.y = arg0->unk200.y * -0.2f;
    arg0->unk228.z = arg0->unk200.z * -0.2f;
    arg0->unk244 = func_80313AF4(0.0f, arg0->unk244, 3.0f);
    arg0->unk248 = func_80313AF4(0.0f, arg0->unk248, 3.0f);
    arg0->unk24C = func_80313AF4(0.0f, arg0->unk24C, 3.0f);
}

void bird_802CF640(BirdmanData* arg0) {
    Vec3F sp3C;
    Vec3F sp30;

    if (arg0->unk160 == 0.0f) {
        arg0->unk160 = D_8034F850;
    }
    sp3C.x = 0.0f;
    sp3C.y = 0.0f;
    sp3C.z = -0.5f;
    sp30.x = arg0->unk268.x * 0.2f;
    sp30.y = arg0->unk268.y * 0.2f;
    sp30.z = arg0->unk268.z * 0.2f;
    func_802DC1DC(&arg0->unk250, &sp3C, &sp30, 0.5f, 0.5f, 0.5f);
    arg0->unk244 = func_80313AF4(0.0f, arg0->unk244, 0.35f);
    arg0->unk248 = func_80313AF4(0.0f, arg0->unk248, 0.35f);
    arg0->unk24C = func_80313AF4(0.0f, arg0->unk24C, 0.35f);
    if ((D_8034F850 - arg0->unk160) > 3.75f) {
        arg0->unk104 = 2;
    }
    arg0->unk105 = 0;
}

s32 bird_802CF76C(BirdmanData* arg0) {
    s32 pad;
    u8 temp_v0_2;
    f32* temp_s1; // TODO: double-check unk10 types
    s32 sp38;
    Vec3F* sp34;

    temp_s1 = arg0->unk10.m[3];
    sp38 = arg0->unk40C;
    temp_v0_2 = db_getgnd(&arg0->unk400, (Vec3F*)temp_s1, &sp38, &arg0->unk170, &arg0->unk168, &arg0->unk174);
    arg0->unk16C = temp_s1[2] - arg0->unk168;
    if (temp_v0_2 != 0) {
        arg0->unk106 = temp_v0_2;
        if (arg0->unk106 == 4) {
            arg0->unk15C = 1;
            arg0->unk104 = 2;
        } else {
            arg0->unk104 = 1;
        }
        sp34 = func_802E02EC();
        func_802E05CC(&arg0->unk10, sp34, &arg0->unk174, 0);
        uvVec3Copy(&arg0->unk150, sp34);
        arg0->unk4 = D_8035963C;
    }
    if (arg0->unk104 != 2) {
        arg0->unk400.x = temp_s1[0];
        arg0->unk400.y = temp_s1[1];
        arg0->unk400.z = temp_s1[2];
    }
    if (arg0->unk15C != 0) {
        return 0;
    }
    if (arg0->unk16C > 2.5f) {
        return 0;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/birdman2/bird_802CF8A4.s")

void bird_802CFAC8(BirdmanData* arg0) {
    f32 var_ft5;
    f32 temp_fa0;
    f32 var_ft4;
    f32 var_fa0_3;
    f32 var_fv0;
    f32 temp_fv0_2;
    f32 var_fa1;
    f32 var_fa0;

    if (arg0->unk274.y > 0.0f) {
        var_fv0 = arg0->unk274.y;
    } else {
        var_fv0 = -arg0->unk274.y;
    }
    if (var_fv0 > 0.1f) {
        var_fa1 = -arg0->unk274.y;
        var_fa0 = arg0->unk274.z;
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
        var_ft5 = D_8034E820 * 3.0f * temp_fv0_2 * arg0->unk274.z * arg0->unk274.z;
        if (var_ft5 < -10.0f) {
            var_ft5 = -10.0f;
        }
        if (var_ft5 > 200.0f) {
            var_ft5 = 200.0f;
        }
    } else {
        var_ft5 = 0.0f;
    }
    if (arg0->unk2D4 < 0.5f) {
        if (arg0->unk224 < 30.0f) {
            var_ft4 = uvCosF(arg0->unk2D4) * 1.3856f * arg0->unk2D0 * arg0->unk2D0;
            temp_fa0 = 2.25f * var_ft4;
        } else {
            var_ft4 = uvCosF(arg0->unk2D4) * 0.6928f * arg0->unk2D0 * arg0->unk2D0;
            temp_fa0 = 2.75f * var_ft4;
            if (arg0->unk200.z > 30.0f) {
                temp_fa0 = 0.0f;
            } else if (arg0->unk200.z > 20.0f) {
                temp_fa0 *= 1.0f - ((arg0->unk200.z - 20.0f) / 10.0f);
            }
        }
    } else {
        if (arg0->unk274.y > 0.0f) {
            var_ft4 = 0.0f;
        } else {
            f32 temp_ft3 = uvSinF(arg0->unk2D4) * -0.064950004f;
            f32 temp = arg0->unk274.y;
            var_ft4 = temp_ft3 * temp * temp;
        }
        temp_fa0 = 2.0f * uvSinF(arg0->unk2D4) * arg0->unk2D0 * arg0->unk2D0;
        if (arg0->unk224 > 15.0f) {
            temp_fa0 = 0.0f;
        } else {
            temp_fa0 *= (1.0f - (arg0->unk224 / 15.0f));
        }
    }
    var_ft5 += temp_fa0;
    if (arg0->unk10.m[3][2] > 875.0f) {
        var_fv0 = 1.0f - ((arg0->unk10.m[3][2] - 875.0f) / 75.0f);
        if (var_fv0 < 0) {
            var_fv0 = 0;
        }
    } else {
        var_fv0 = 1.0f;
    }
    var_ft5 *= var_fv0;
    var_ft4 *= var_fv0;
    arg0->unk228.z += var_ft5;
    arg0->unk228.y += var_ft4;
}

void bird_802CFEA8(BirdmanData* arg0) {
    Vec3F sp2C;
    Vec3F sp20;

    if (arg0->unk105 == 0) {
        if (arg0->unk104 != 1) {
            func_802E1754(arg0->unk10.m[3][0], arg0->unk10.m[3][1], arg0->unk10.m[3][2], &sp20);
            sp20.z *= arg0->unk2A8;
            uvMat4LocalToWorld(&arg0->unk180, &sp2C, &sp20);
        } else {
            sp2C.z = 0.0f;
            sp2C.y = 0.0f;
            sp2C.x = 0.0f;
            sp20.z = 0.0f;
            sp20.y = 0.0f;
            sp20.x = 0.0f;
        }
        arg0->unk274.x = sp2C.x - arg0->unk200.x;
        arg0->unk274.y = sp2C.y - arg0->unk200.y;
        arg0->unk274.z = sp2C.z - arg0->unk200.z;
    }
}

void bird_802CFF74(BirdmanData* arg0) {
    Vec3F sp24;
    f32 temp_fv0;

    if (arg0->unk105 == 0) {
        sp24.x = 0.0f;
        sp24.y = 0.0f;
        sp24.z = -arg0->unk2A4 * 9.8f;
        uvMat4LocalToWorld(&arg0->unk180, &arg0->unk268, &sp24);
        if (arg0->unk164 > 0.0f) {
            if (arg0->unk16C < 3.0f) {
                temp_fv0 = arg0->unk16C / 3.0f;
                arg0->unk268.x *= temp_fv0;
                arg0->unk268.y *= temp_fv0;
                arg0->unk268.z *= temp_fv0;
            }
            arg0->unk164 -= D_8034F854;
        }
        arg0->unk228.x += arg0->unk268.x;
        arg0->unk228.y += arg0->unk268.y;
        arg0->unk228.z += arg0->unk268.z;
    }
}

void bird_802D0080(BirdmanData* arg0) {
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
        arg0->unk140[i] = 0.0f;
        arg0->unk108[i] = 0;
    }
    arg0->unk106 = 0;
    arg0->unk15C = 0;
    sp258 = 0;
    sp26B = func_802DB050(&D_803593F0, &D_803594F8, arg0->objId, arg0->unk2, &arg0->unk10);
    arg0->unk107 = sp26B;

    for (i = 0; i < sp26B; i++) {
        temp_s1 = &D_803594F8.unk4[i];
        func_802DC814(temp_s1, (Vec3F*)arg0->unk10.m[3]);
        func_802DBE64(&D_803593F0, &D_803594F8, i, &arg0->unk180);
        uvVec3Copy(&arg0->unk110[i], &temp_s1->unkC);
        arg0->unk10C[i] = temp_s1->unk0;
        arg0->unk108[i] = temp_s1->unk4;
        arg0->unk140[i] = uvVec3Dot(&arg0->unk200, &temp_s1->unk34);
        switch (temp_s1->unk4) {
        case 2:
            var_fs2 = var_fs1 = ballsPopped(temp_s1->surfaceId, &arg0->unk218, &D_803594F8);
            if (var_fs1 == 0.0f) {
                return;
            }
            break;
        case 4:
            if (arg0->unk104 != 1) {
                arg0->unk104 = 0;
            }
            arg0->unk15C = 1;
            arg0->unk106 = 0;
            break;
        case 1:
        case 8:
            if ((temp_s1->unk4 == 8) && (func_802DC97C(temp_s1->surfaceId) != 0)) {
                func_8033F758(0x39, 1.0f, 1.0f, 0.0f);
            }
            if ((arg0->unk164 > 1.0f) && (arg0->unk16C < 3.0f) && (temp_s1->unk0 == 3)) {
                return;
            }
            if ((arg0->unk105 != 0) && (arg0->unk104 != 1)) {
                uvVec3Copy(&sp24C, &arg0->unk200);
                func_802DC074(&arg0->unk1C0, &arg0->unk200, &arg0->unk218, &temp_s1->unk34, 0.5f);
                temp_fv0 = ABS_NOEQ(sp24C.x - arg0->unk200.x);
                if (temp_fv0 < 0.1f) {
                    temp_fv1 = ABS_NOEQ(sp24C.y - arg0->unk200.y);
                    if (temp_fv1 < 0.1f) {
                        temp_fa0 = ABS_NOEQ(sp24C.y - arg0->unk200.z);
                        if (temp_fa0 < 0.1f) {
                            arg0->unk200.x += temp_s1->unk34.x;
                            arg0->unk200.y += temp_s1->unk34.y;
                            arg0->unk200.z += temp_s1->unk34.z;
                            uvMat4LocalToWorld(&arg0->unk1C0, &arg0->unk218, &arg0->unk200);
                            return;
                        }
                    }
                }
                arg0->unk10.m[3][0] += 0.01f * arg0->unk174.x;
                arg0->unk10.m[3][1] += 0.01f * arg0->unk174.y;
                arg0->unk10.m[3][2] += 0.01f * arg0->unk174.z;
                return;
            }

            var_fv1 = ABS_NOEQ(arg0->unk218.z * 2.52f);
            var_fa0 = ABS_NOEQ(arg0->unk218.y * 2.52f);
            if ((temp_s1->unk0 == 3) && (arg0->unk104 == 0) && (var_fv1 < 50.0f)) {
                arg0->unk106 = 0;
                var_fs2 = 0.0f;
                var_fs1 = 0.0f;
                temp_v1 = arg0->unk104;
                if (temp_v1 == 0) {
                    if ((var_fa0 > 50.0f) && (D_8034F850 > 2.0f)) {
                        arg0->unk104 = 1;
                    } else if (arg0->unk105 == 0) {
                        arg0->unk2D0 = 0.0f;
                        arg0->unk105 = 1;
                        arg0->unk10.m[3][0] += 0.025f * arg0->unk174.x;
                        arg0->unk10.m[3][1] += 0.025f * arg0->unk174.y;
                        arg0->unk10.m[3][2] = (arg0->unk168 - arg0->unk344.z) + (0.025f * arg0->unk174.z);
                        arg0->unk218.x = 0.0f;
                        arg0->unk218.y = 0.0f;
                        arg0->unk218.z = 0.0f;
                        arg0->unk200.x = 0.0f;
                        arg0->unk200.y = 0.0f;
                        arg0->unk200.z = 0.0f;
                        arg0->unk234.x = 0.0f;
                        arg0->unk234.y = 0.0f;
                        arg0->unk234.z = 0.0f;
                        arg0->unk228.x = 0.0f;
                        arg0->unk228.y = 0.0f;
                        arg0->unk228.z = 0.0f;
                    }
                }
            } else {
                arg0->unk106 = temp_s1->unk4;
                arg0->unk104 = 1;
                var_fs2 = 0.5f;
                var_fs1 = 0.7f;
                if (arg0->unkE0 != 0) {
                    arg0->unk4 = 0xF7FB;
                } else {
                    arg0->unk4 = D_8035963C;
                }
                if (arg0->unk224 < 2.0f) {
                    var_fs2 *= arg0->unk224 / 2.0f;
                    var_fs1 *= arg0->unk224 / 2.0f;
                }
                if (arg0->unk106 == 4) {
                    arg0->unk15C = 1;
                }
            }
            break;
        default:
            _uvDebugPrintf("bmmot : unknown collision type [%d]\n", temp_s1->unk4);
            break;
        }

        if ((arg0->unk105 == 0) && (temp_s1->unk4 != 4)) {
            sp27C.x = -arg0->unk200.x;
            sp27C.y = -arg0->unk200.y;
            sp27C.z = -arg0->unk200.z;
            func_802DC1DC(&arg0->unk250, &temp_s1->unk28, &sp27C, 20.0f * var_fs1, 5.6f * var_fs1, 9.2f * var_fs1);
            func_802DC074(&arg0->unk1C0, &arg0->unk200, &arg0->unk218, &temp_s1->unk34, var_fs2);
        }
        if (arg0->unk104 != 2) {
            if ((temp_s1->unk4 != 4) && (arg0->unk105 == 0)) {
                if ((temp_s1->unk4 == 2) && (balls_802CC0D4(temp_s1->surfaceId) != 0)) {
                    break;
                }
                temp_v0_3 = &D_803593F0.unk4[temp_s1->unk0];
                func_802DCA5C(&temp_v0_3->unk28, &temp_v0_3->unk1C, &temp_s1->unk28, &temp_s1->unk34, &sp240);
                sp234.x = arg0->unk10.m[3][0];
                sp234.y = arg0->unk10.m[3][1];
                sp234.z = arg0->unk10.m[3][2];
                uvMat4Copy(&sp1E8, &arg0->unk10);
                uvMat4LocalTranslate(&sp1E8, sp240.x, sp240.y, sp240.z);
                sp228.x = sp1E8.m[3][0];
                sp228.y = sp1E8.m[3][1];
                sp228.z = sp1E8.m[3][2];
                func_802DB224(&spA4, 0xFF, arg0->objId, arg0->unk2, &sp234, &sp228);
                if (spA4.unk0 > 0) {
                    sp258++;
                } else {
                    uvMat4LocalTranslate(&arg0->unk10, sp240.x, sp240.y, sp240.z);
                    arg0->unk400.x = arg0->unk10.m[3][0];
                    arg0->unk400.y = arg0->unk10.m[3][1];
                    arg0->unk400.z = arg0->unk10.m[3][2];
                }
            }
        }
    }

    if (sp26B && (sp258 == sp26B)) {
        arg0->unk104 = 2;
        _uvDebugPrintf("birdman: you got stuck - forcing an instant crash\n");
    }
}

f32 bird_802D08F8(Unk8034E824* arg0, f32 arg1, f32 arg2) {
    s32 i;
    Vec2F p0;
    Vec2F p1;
    f32 a;
    Vec2F q0;
    Vec2F q1;
    f32 sum0;
    f32 sum1;

    for (i = 0; i < ARRAY_COUNT(arg0->unk0); i++) {
        if (arg1 < arg0->unk0[i].x) {
            break;
        }
    }
    if ((i == 0) || (i == ARRAY_COUNT(arg0->unk0))) {
        return 0.0f;
    }
    p0.x = arg0->unk0[i - 1].x;
    p1.x = arg0->unk0[i].x;
    p0.y = arg0->unk0[i - 1].y;
    p1.y = arg0->unk0[i].y;
    a = (p1.x - arg1) / (p1.x - p0.x);
    sum0 = (a * p0.y) + ((1.0f - a) * p1.y);

    for (i = 0; i < ARRAY_COUNT(arg0->unkB8); i++) {
        if (arg2 < arg0->unkB8[i].x) {
            break;
        }
    }
    if ((i == 0) || (i == ARRAY_COUNT(arg0->unkB8))) {
        return 0.0f;
    }
    q0.x = arg0->unkB8[i - 1].x;
    q1.x = arg0->unkB8[i].x;
    q0.y = arg0->unkB8[i - 1].y;
    q1.y = arg0->unkB8[i].y;
    a = (q1.x - arg2) / (q1.x - q0.x);
    sum1 = (a * q0.y) + ((1.0f - a) * q1.y);
    return sum1 * sum0;
}

f32 bird_802D0A28(Unk8034E934* arg0, f32 arg1) {
    f32 x1;
    f32 x0;
    f32 y0;
    f32 y1;
    f32 a;
    f32 b;
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
    a = (x1 - arg1) / (x1 - x0);
    b = 1.0f - a;
    return (a * y0) + (b * y1);
}

void bird_802D0ABC(BirdmanData* arg0) {
    Mtx4F* temp_s2;
    Mtx4F sp44;
    Vec3F sp38;

    func_80313FD0(&arg0->unk350, arg0->unk2BC, &sp38);
    temp_s2 = &arg0->unk90;
    uvMat4LocalToWorld(temp_s2, &D_803593F0.unk4[0].unk28, &sp38);
    uvVec3Copy(&sp38, &arg0->unk320);
    uvMat4LocalToWorld(temp_s2, &D_803593F0.unk4[0].unk1C, &sp38);
    func_80313FD0(&arg0->unk350, arg0->unk2BC, &sp38);
    sp38.x = -sp38.x;
    uvMat4LocalToWorld(temp_s2, &D_803593F0.unk4[1].unk28, &sp38);
    uvVec3Copy(&sp38, &arg0->unk320);
    uvMat4LocalToWorld(temp_s2, &D_803593F0.unk4[1].unk1C, &sp38);
    uvMat4Copy(&sp44, temp_s2);
    uvMat4RotateAxis(&sp44, arg0->unk304, 'x');
    uvMat4RotateAxis(&sp44, arg0->unk308, 'y');
    uvMat4LocalToWorld(&sp44, &D_803593F0.unk4[3].unk1C, &arg0->unk344);
    uvVec3Copy(&sp38, &arg0->unk320);
    uvMat4LocalToWorld(temp_s2, &D_803593F0.unk4[2].unk1C, &sp38);
}
