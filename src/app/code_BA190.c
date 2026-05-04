#include "common.h"
#include "code_BA190.h"
#include <uv_math.h>
#include <uv_utils.h>
#include "app/demo.h"
#include "app/environment.h"
#include "app/code_66F70.h"
#include "app/code_9A960.h"

Unk802D3658_Unk111C D_80371B50;
Unk803599D0 D_80371C58;

void func_80332FCC(SkyDivingData*);
void func_80333384(SkyDivingData*);
s32 func_803335D0(SkyDivingData*);

void func_80332C60(SkyDivingData* sdData) {
    Vec3F sp24 = { 0.0f, 0.0f, 0.0f };

    D_80371B50.unk0 = 3;
    uvVec3Copy(&D_80371B50.unk4[0].unk28, &sdData->unk1D0);
    uvVec3Copy(&D_80371B50.unk4[0].unk1C, &sdData->unk1C4);
    uvVec3Copy(&D_80371B50.unk4[1].unk28, &sdData->unk1F4);
    uvVec3Copy(&D_80371B50.unk4[1].unk1C, &sdData->unk200);
    uvVec3Copy(&D_80371B50.unk4[2].unk28, &sdData->unk1E8);
    uvVec3Copy(&D_80371B50.unk4[2].unk1C, &sdData->unk1DC);
    func_80332D94(sdData);
    D_80371C58.count = 5;
    D_80371C58.unk4[0].x = 0.0f;
    D_80371C58.unk4[0].y = -10.0f;
    D_80371C58.unk4[1].x = 1.0f;
    D_80371C58.unk4[1].y = -2.0f;
    D_80371C58.unk4[2].x = 2.0f;
    D_80371C58.unk4[2].y = -2.0f;
    D_80371C58.unk4[3].x = 4.0f;
    D_80371C58.unk4[3].y = -5.0f;
    D_80371C58.unk4[4].x = 8.0f;
    D_80371C58.unk4[4].y = -20.0f;
}

void func_80332D94(SkyDivingData* sdData) {
    s32 pad;

    sdData->unk17C = 0.0f;
    sdData->unk180 = 0.0f;
    sdData->unk184 = 0.0f;
    sdData->unk194 = 0.0f;
    sdData->unk198 = 0.0f;
    sdData->unk19C = 0.0f;
    sdData->unk188 = 0.0f;
    sdData->unk18C = 0.0f;
    sdData->unk190 = -9.8f;
    sdData->unkC8 = 0.0f;
    sdData->unkCC = 0.0f;
    sdData->unk16C = 0.0f;
    sdData->unk178 = 0.0f;
    sdData->unk5C = 0.0f;
    sdData->unkD0 = 1.0f;
    sdData->unk60 = 1.5707963f;
    sdData->unkB8 = 0;
    // FAKE
    if (1) { }
    sdData->unk170 = sdData->unk2B8;
    sdData->unk174 = sdData->unk2BC;
    sdData->unk10.m[3][0] = sdData->unk2B8;
    sdData->unk10.m[3][1] = sdData->unk2BC;
    sdData->unk10.m[3][2] = sdData->unk2C0;
    sdData->unk264 = 1.0f;
    uvMat4Copy(&sdData->unk114, &sdData->unk10);
    sdData->unk114.m[3][0] = 0.0f;
    sdData->unk114.m[3][1] = 0.0f;
    sdData->unk114.m[3][2] = 0.0f;
    uvMat4LocalToWorld(&sdData->unk114, &sdData->unk160, &sdData->unk154);
    sdData->unk23C = 1;
    sdData->unk230.x = sdData->unk10.m[3][0];
    sdData->unk230.y = sdData->unk10.m[3][1];
    sdData->unk230.z = sdData->unk10.m[3][2];
}

void func_80332E90(SkyDivingData* sdData) {
    f32 temp_fv1;
    f32 temp_fa1;
    f32 temp_fv0;

    func_803335D0(sdData);
    switch (sdData->unk70) {
    case 0:
        func_80332FCC(sdData);
        break;
    case 1:
        func_80333384(sdData);
        break;
    default:
        return;
    }
    sdData->unk10.m[3][0] += D_8034F854 * sdData->unk160.x;
    sdData->unk10.m[3][1] += D_8034F854 * sdData->unk160.y;
    sdData->unk10.m[3][2] += D_8034F854 * sdData->unk160.z;
    if (sdData->unk264 == 1.0f) {
        temp_fv1 = sdData->unk10.m[3][0] - sdData->unk170;
        temp_fa1 = sdData->unk10.m[3][1] - sdData->unk174;
        temp_fv0 = uvSqrtF(SQ(temp_fv1) + SQ(temp_fa1));
        if (temp_fv0 > 20.0f) {
            sdData->unk10.m[3][0] = sdData->unk170 + ((20.0f * temp_fv1) / temp_fv0);
            sdData->unk10.m[3][1] = sdData->unk174 + ((20.0f * temp_fa1) / temp_fv0);
        }
    }
}

void func_80332FCC(SkyDivingData* sdData) {
    f32 temp_fv0;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    s32 sp24;
    f32 temp_fv1;
    f32 temp_fv0_2;

    sdData->unk5C += sdData->unk2A8 * 1.5f * D_8034F854 * sdData->unk270;

    if (sdData->unk5C > 3.1415927f) {
        sdData->unk5C -= 6.2831855f;
    } else if (sdData->unk5C < -3.1415927f) {
        sdData->unk5C += 6.2831855f;
    }
    if (demoButtonCheck(sdData->contIdx, B_BUTTON) != 0) {
        sdData->unk60 += 3.0f * D_8034F854 * sdData->unk274;
    } else {
        sdData->unk60 = func_80313AF4((sdData->unk274 + 1.0f) * 1.5707963f, sdData->unk60, 3.0f);
    }

    if (sdData->unk60 > 3.1415927f) {
        sdData->unk60 -= 6.2831855f;
    } else if (sdData->unk60 < -3.1415927f) {
        sdData->unk60 += 6.2831855f;
    }
    if (demoButtonCheck(sdData->contIdx, A_BUTTON) != 0) {
        sp24 = 1;
    } else {
        sp24 = 0;
    }
    if (sdData->unk264 > 1.0f) {
        sdData->unk264 = MAX(sdData->unk10.m[3][2] * 0.05f, 20.0f);
    }
    temp_fv0 = uvSinF(sdData->unk60 * -2.0f);
    if (temp_fv0 < 0.0f) {
        sp30 = -SQ(temp_fv0);
    } else {
        sp30 = SQ(temp_fv0);
    }
    sp30 *= (3.0f * sdData->unk264);
    sp2C = sdData->unk5C - 1.5707963f;
    sdData->unk160.x = uvCosF(sp2C) * sp30;
    sdData->unk160.y = uvSinF(-sp2C) * sp30;
    temp_fv0_2 = uvCosF(sdData->unk60);
    temp_fv1 = SQ(temp_fv0_2);
    sp28 = ((SQ(temp_fv1) + 0.500f) * -30.0f) + -7.0f;
    if (sp24 != 0) {
        sdData->unk268 = func_80313AF4(0.500f, sdData->unk268, 2.0f);
        sp28 *= sdData->unk268;
    } else {
        sdData->unk268 = 1.0f;
    }
    sdData->unk160.z = func_80313AF4(sp28, sdData->unk160.z, 3.0f);
    sdData->unk1B4 = func_80313AF4(uvRandF_RANLUX() - 0.50f, sdData->unk1B4, 10.0f);
    sdData->unk1B8 = func_80313AF4(uvRandF_RANLUX() - 0.50f, sdData->unk1B8, 10.0f);
    sdData->unk1BC = func_80313AF4(uvRandF_RANLUX() - 0.50f, sdData->unk1BC, 10.0f);
    sdData->unk10.m[3][0] += 0.5f * sdData->unk1B4 * D_8034F854;
    sdData->unk10.m[3][1] += 0.5f * sdData->unk1B8 * D_8034F854;
    sdData->unk10.m[3][2] += 0.5f * sdData->unk1BC * D_8034F854;
}

void func_80333384(SkyDivingData* sdData) {
    f32 temp_fs0;
    f32 var_fs0;
    f32 var_fs1;
    f32 var_fs2;
    Vec3F sp3C;

    sdData->unk5C += sdData->unk2A8 * 0.56f * 1.5f * D_8034F854 * sdData->unk270;

    if (sdData->unk5C > 3.1415927f) {
        sdData->unk5C -= 6.2831855f;
    } else if (sdData->unk5C < -3.1415927f) {
        sdData->unk5C += 6.2831855f;
    }
    sdData->unk60 = 0.0f;
    temp_fs0 = sdData->unk5C - 1.5707963f;
    var_fs1 = uvCosF(temp_fs0) * 20.0f;
    var_fs2 = uvSinF(-temp_fs0) * 20.0f;
    if (demoButtonCheck((s32)sdData->contIdx, A_BUTTON) != 0) {
        sdData->unk260 += D_8034F854;
        if (sdData->unk260 > 8.0f) {
            sdData->unk260 = 8.0f;
        }
        var_fs1 *= 0.25f;
        var_fs2 *= 0.25f;
        var_fs0 = func_80313F08(&D_80371C58, sdData->unk260);
    } else {
        sdData->unk260 -= 3.478261f * D_8034F854;
        if (sdData->unk260 < 0.0f) {
            sdData->unk260 = 0.0f;
        }
        var_fs0 = -10.0f;
    }
    env_802E1754(sdData->unk10.m[3][0], sdData->unk10.m[3][1], sdData->unk10.m[3][2], &sp3C);

    var_fs1 += sp3C.x;
    var_fs1 *= sdData->unk2B0;
    var_fs2 += sp3C.y;
    var_fs2 *= sdData->unk2B0;
    var_fs0 += sp3C.z;
    var_fs0 *= sdData->unk2AC;
    sdData->unk160.x = func_80313AF4(var_fs1, sdData->unk160.x, 1.0f);
    sdData->unk160.y = func_80313AF4(var_fs2, sdData->unk160.y, 1.0f);
    sdData->unk160.z = func_80313AF4(var_fs0, sdData->unk160.z, 3.0f);
}

s32 func_803335D0(SkyDivingData* sdData) {
    f32 sp6C;
    f32 temp_fv0;
    Vec3F sp5C;
    s32 sp58;
    Vec3F sp4C;
    s32 pad[2];
    u8 sp43;
    Vec3F sp34;

    if ((sdData->unk70 == 0) && (sdData->unk264 == 1.0f)) {
        if (sdData->unk10.m[3][2] <= 0.0f) {
            skydivingBelow(sdData);
        }
        return 1;
    }
    if ((sdData->unk70 == 0) && (demoButtonPress(0, B_BUTTON) != 0)) {
        func_80331AE4(sdData);
        return 1;
    }
    sp4C.x = sdData->unk10.m[3][0];
    sp4C.y = sdData->unk10.m[3][1];
    sp4C.z = sdData->unk10.m[3][2];
    sdData->unkBC = 1000000.0f;
    sp6C = 0.0f;
    sp43 = db_getgnd(&sdData->unk230, &sp4C, &sdData->unk23C, &sp58, &sp6C, &sp5C);

    temp_fv0 = sp4C.z - sp6C;
    if (sdData->unk264 != 1.0f) {
        sdData->unk280 = temp_fv0;
    } else {
        sdData->unk280 = 200.0f;
    }
    if (temp_fv0 <= sdData->unkBC) {
        sdData->unkBC = temp_fv0;
        sdData->unkC0 = sp58;
        sdData->unkC4 = sp6C;
        sdData->unkC8 = sp5C.x;
        sdData->unkCC = sp5C.y;
        sdData->unkD0 = sp5C.z;
    }
    if (sp43) {
        sp34.x = -sdData->unkC8;
        sp34.y = -sdData->unkCC;
        sp34.z = -sdData->unkD0;
        sdData->unk10.m[3][2] = sp6C;
        func_80313E18(&sp34, &sdData->unk10);
        if (sp43 == 4) {
            sdData->unkB8 = 1;
            sdData->unk70 = 3;
            uvDobjState(sdData->objId, 0);
        } else if (sp43 & 0xA) {
            sdData->unk70 = 5;
            if (sdData->unk27A != 0) {
                uvDobjProps(sdData->objId, 5, sdData->unk228, 0);
            }
            func_802E05CC(&sdData->unk10, func_802E02EC(), &sp5C, 0);
        } else if (sdData->unk70 == 0) {
            sdData->unk70 = 3;
        } else if (sdData->unk160.z < -11.0f) {
            sdData->unk70 = 5;
            sdData->unk10.m[3][2] += sdData->unk2A0;
        } else {
            sdData->unk70 = 4;
            sdData->unk10.m[3][2] += sdData->unk2A0;
        }
    }
    sdData->unk230.x = sp4C.x;
    sdData->unk230.y = sp4C.y;
    sdData->unk230.z = sp4C.z;
    if (sdData->unk70 == 3) {
        return 0;
    }
    return 1;
}
