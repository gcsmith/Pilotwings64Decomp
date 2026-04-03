#include "common.h"
#include "code_BA190.h"
#include <uv_math.h>
#include "app/demo.h"
#include "app/environment.h"
#include "app/code_66160.h"
#include "app/code_9A960.h"

Unk802D3658_Unk111C D_80371B50;
Unk803599D0 D_80371C58;

void func_80332FCC(SkyDivingData*);
void func_80333384(SkyDivingData*);
s32 func_803335D0(SkyDivingData*);

void func_80332C60(SkyDivingData* arg0) {
    Vec3F sp24 = { 0.0f, 0.0f, 0.0f };

    D_80371B50.unk0 = 3;
    uvVec3Copy(&D_80371B50.unk4[0].unk28, &arg0->unk1D0);
    uvVec3Copy(&D_80371B50.unk4[0].unk1C, &arg0->unk1C4);
    uvVec3Copy(&D_80371B50.unk4[1].unk28, &arg0->unk1F4);
    uvVec3Copy(&D_80371B50.unk4[1].unk1C, &arg0->unk200);
    uvVec3Copy(&D_80371B50.unk4[2].unk28, &arg0->unk1E8);
    uvVec3Copy(&D_80371B50.unk4[2].unk1C, &arg0->unk1DC);
    func_80332D94(arg0);
    D_80371C58.unk0 = 5;
    D_80371C58.unk4 = 0.0f;
    D_80371C58.unk8 = -10.0f;
    D_80371C58.unk10 = -2.0f;
    D_80371C58.unk18 = -2.0f;
    D_80371C58.unkC = 1.0f;
    D_80371C58.unk14 = 2.0f;
    D_80371C58.unk1C = 4.0f;
    D_80371C58.unk20 = -5.0f;
    D_80371C58.unk24 = 8.0f;
    D_80371C58.unk28 = -20.0f;
}

void func_80332D94(SkyDivingData* arg0) {
    s32 pad;

    arg0->unk17C = 0.0f;
    arg0->unk180 = 0.0f;
    arg0->unk184 = 0.0f;
    arg0->unk194 = 0.0f;
    arg0->unk198 = 0.0f;
    arg0->unk19C = 0.0f;
    arg0->unk188 = 0.0f;
    arg0->unk18C = 0.0f;
    arg0->unk190 = -9.8f;
    arg0->unkC8 = 0.0f;
    arg0->unkCC = 0.0f;
    arg0->unk16C = 0.0f;
    arg0->unk178 = 0.0f;
    arg0->unk5C = 0.0f;
    arg0->unkD0 = 1.0f;
    arg0->unk60 = 1.5707963f;
    arg0->unkB8 = 0;
    // FAKE
    if (1) { }
    arg0->unk170 = arg0->unk2B8;
    arg0->unk174 = arg0->unk2BC;
    arg0->unk10.m[3][0] = arg0->unk2B8;
    arg0->unk10.m[3][1] = arg0->unk2BC;
    arg0->unk10.m[3][2] = arg0->unk2C0;
    arg0->unk264 = 1.0f;
    uvMat4Copy(&arg0->unk114, &arg0->unk10);
    arg0->unk114.m[3][0] = 0.0f;
    arg0->unk114.m[3][1] = 0.0f;
    arg0->unk114.m[3][2] = 0.0f;
    uvMat4LocalToWorld(&arg0->unk114, &arg0->unk160, &arg0->unk154);
    arg0->unk23C = 1;
    arg0->unk230.x = arg0->unk10.m[3][0];
    arg0->unk230.y = arg0->unk10.m[3][1];
    arg0->unk230.z = arg0->unk10.m[3][2];
}

void func_80332E90(SkyDivingData* arg0) {
    f32 temp_fv1;
    f32 temp_fa1;
    f32 temp_fv0;

    func_803335D0(arg0);
    switch (arg0->unk70) {
    case 0:
        func_80332FCC(arg0);
        break;
    case 1:
        func_80333384(arg0);
        break;
    default:
        return;
    }
    arg0->unk10.m[3][0] += D_8034F854 * arg0->unk160.x;
    arg0->unk10.m[3][1] += D_8034F854 * arg0->unk160.y;
    arg0->unk10.m[3][2] += D_8034F854 * arg0->unk160.z;
    if (arg0->unk264 == 1.0f) {
        temp_fv1 = arg0->unk10.m[3][0] - arg0->unk170;
        temp_fa1 = arg0->unk10.m[3][1] - arg0->unk174;
        temp_fv0 = uvSqrtF(SQ(temp_fv1) + SQ(temp_fa1));
        if (temp_fv0 > 20.0f) {
            arg0->unk10.m[3][0] = arg0->unk170 + ((20.0f * temp_fv1) / temp_fv0);
            arg0->unk10.m[3][1] = arg0->unk174 + ((20.0f * temp_fa1) / temp_fv0);
        }
    }
}

void func_80332FCC(SkyDivingData* arg0) {
    f32 temp_fv0;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    s32 sp24;
    f32 temp_fv1;
    f32 temp_fv0_2;

    arg0->unk5C += arg0->unk2A8 * 1.5f * D_8034F854 * arg0->unk270;

    if (arg0->unk5C > 3.1415927f) {
        arg0->unk5C -= 6.2831855f;
    } else if (arg0->unk5C < -3.1415927f) {
        arg0->unk5C += 6.2831855f;
    }
    if (demoButtonCheck(arg0->contIdx, B_BUTTON) != 0) {
        arg0->unk60 += 3.0f * D_8034F854 * arg0->unk274;
    } else {
        arg0->unk60 = func_80313AF4((arg0->unk274 + 1.0f) * 1.5707963f, arg0->unk60, 3.0f);
    }

    if (arg0->unk60 > 3.1415927f) {
        arg0->unk60 -= 6.2831855f;
    } else if (arg0->unk60 < -3.1415927f) {
        arg0->unk60 += 6.2831855f;
    }
    if (demoButtonCheck(arg0->contIdx, A_BUTTON) != 0) {
        sp24 = 1;
    } else {
        sp24 = 0;
    }
    if (arg0->unk264 > 1.0f) {
        arg0->unk264 = MAX(arg0->unk10.m[3][2] * 0.05f, 20.0f);
    }
    temp_fv0 = uvSinF(arg0->unk60 * -2.0f);
    if (temp_fv0 < 0.0f) {
        sp30 = -SQ(temp_fv0);
    } else {
        sp30 = SQ(temp_fv0);
    }
    sp30 *= (3.0f * arg0->unk264);
    sp2C = arg0->unk5C - 1.5707963f;
    arg0->unk160.x = uvCosF(sp2C) * sp30;
    arg0->unk160.y = uvSinF(-sp2C) * sp30;
    temp_fv0_2 = uvCosF(arg0->unk60);
    temp_fv1 = SQ(temp_fv0_2);
    sp28 = ((SQ(temp_fv1) + 0.500f) * -30.0f) + -7.0f;
    if (sp24 != 0) {
        arg0->unk268 = func_80313AF4(0.500f, arg0->unk268, 2.0f);
        sp28 *= arg0->unk268;
    } else {
        arg0->unk268 = 1.0f;
    }
    arg0->unk160.z = func_80313AF4(sp28, arg0->unk160.z, 3.0f);
    arg0->unk1B4 = func_80313AF4(uvRandF_RANLUX() - 0.50f, arg0->unk1B4, 10.0f);
    arg0->unk1B8 = func_80313AF4(uvRandF_RANLUX() - 0.50f, arg0->unk1B8, 10.0f);
    arg0->unk1BC = func_80313AF4(uvRandF_RANLUX() - 0.50f, arg0->unk1BC, 10.0f);
    arg0->unk10.m[3][0] += 0.5f * arg0->unk1B4 * D_8034F854;
    arg0->unk10.m[3][1] += 0.5f * arg0->unk1B8 * D_8034F854;
    arg0->unk10.m[3][2] += 0.5f * arg0->unk1BC * D_8034F854;
}

void func_80333384(SkyDivingData* arg0) {
    f32 temp_fs0;
    f32 var_fs0;
    f32 var_fs1;
    f32 var_fs2;
    Vec3F sp3C;

    arg0->unk5C += arg0->unk2A8 * 0.56f * 1.5f * D_8034F854 * arg0->unk270;

    if (arg0->unk5C > 3.1415927f) {
        arg0->unk5C -= 6.2831855f;
    } else if (arg0->unk5C < -3.1415927f) {
        arg0->unk5C += 6.2831855f;
    }
    arg0->unk60 = 0.0f;
    temp_fs0 = arg0->unk5C - 1.5707963f;
    var_fs1 = uvCosF(temp_fs0) * 20.0f;
    var_fs2 = uvSinF(-temp_fs0) * 20.0f;
    if (demoButtonCheck((s32)arg0->contIdx, A_BUTTON) != 0) {
        arg0->unk260 += D_8034F854;
        if (arg0->unk260 > 8.0f) {
            arg0->unk260 = 8.0f;
        }
        var_fs1 *= 0.25f;
        var_fs2 *= 0.25f;
        var_fs0 = func_80313F08(&D_80371C58, arg0->unk260);
    } else {
        arg0->unk260 -= 3.478261f * D_8034F854;
        if (arg0->unk260 < 0.0f) {
            arg0->unk260 = 0.0f;
        }
        var_fs0 = -10.0f;
    }
    func_802E1754(arg0->unk10.m[3][0], arg0->unk10.m[3][1], arg0->unk10.m[3][2], &sp3C);

    var_fs1 += sp3C.x;
    var_fs1 *= arg0->unk2B0;
    var_fs2 += sp3C.y;
    var_fs2 *= arg0->unk2B0;
    var_fs0 += sp3C.z;
    var_fs0 *= arg0->unk2AC;
    arg0->unk160.x = func_80313AF4(var_fs1, arg0->unk160.x, 1.0f);
    arg0->unk160.y = func_80313AF4(var_fs2, arg0->unk160.y, 1.0f);
    arg0->unk160.z = func_80313AF4(var_fs0, arg0->unk160.z, 3.0f);
}

s32 func_803335D0(SkyDivingData* arg0) {
    f32 sp6C;
    f32 temp_fv0;
    Vec3F sp5C;
    s32 sp58;
    Vec3F sp4C;
    s32 pad[2];
    u8 sp43;
    Vec3F sp34;

    if ((arg0->unk70 == 0) && (arg0->unk264 == 1.0f)) {
        if (arg0->unk10.m[3][2] <= 0.0f) {
            skydivingBelow(arg0);
        }
        return 1;
    }
    if ((arg0->unk70 == 0) && (demoButtonPress(0, B_BUTTON) != 0)) {
        func_80331AE4(arg0);
        return 1;
    }
    sp4C.x = arg0->unk10.m[3][0];
    sp4C.y = arg0->unk10.m[3][1];
    sp4C.z = arg0->unk10.m[3][2];
    arg0->unkBC = 1000000.0f;
    sp6C = 0.0f;
    sp43 = db_getgnd(&arg0->unk230, &sp4C, &arg0->unk23C, &sp58, &sp6C, &sp5C);

    temp_fv0 = sp4C.z - sp6C;
    if (arg0->unk264 != 1.0f) {
        arg0->unk280 = temp_fv0;
    } else {
        arg0->unk280 = 200.0f;
    }
    if (temp_fv0 <= arg0->unkBC) {
        arg0->unkBC = temp_fv0;
        arg0->unkC0 = sp58;
        arg0->unkC4 = sp6C;
        arg0->unkC8 = sp5C.x;
        arg0->unkCC = sp5C.y;
        arg0->unkD0 = sp5C.z;
    }
    if (sp43) {
        sp34.x = -arg0->unkC8;
        sp34.y = -arg0->unkCC;
        sp34.z = -arg0->unkD0;
        arg0->unk10.m[3][2] = sp6C;
        func_80313E18(&sp34, &arg0->unk10);
        if (sp43 == 4) {
            arg0->unkB8 = 1;
            arg0->unk70 = 3;
            uvDobjState(arg0->objId, 0);
        } else if (sp43 & 0xA) {
            arg0->unk70 = 5;
            if (arg0->unk27A != 0) {
                uvDobjProps(arg0->objId, 5, arg0->unk228, 0);
            }
            func_802E05CC(&arg0->unk10, func_802E02EC(), &sp5C, 0);
        } else if (arg0->unk70 == 0) {
            arg0->unk70 = 3;
        } else if (arg0->unk160.z < -11.0f) {
            arg0->unk70 = 5;
            arg0->unk10.m[3][2] += arg0->unk2A0;
        } else {
            arg0->unk70 = 4;
            arg0->unk10.m[3][2] += arg0->unk2A0;
        }
    }
    arg0->unk230.x = sp4C.x;
    arg0->unk230.y = sp4C.y;
    arg0->unk230.z = sp4C.z;
    if (arg0->unk70 == 3) {
        return 0;
    }
    return 1;
}
