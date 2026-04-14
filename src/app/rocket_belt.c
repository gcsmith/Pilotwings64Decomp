#include "common.h"
#include "rocket_belt.h"
#include <uv_math.h>
#include <uv_vector.h>
#include "app/balls.h"
#include "app/demo.h"
#include "app/demo_attitude.h"
#include "app/environment.h"
#include "app/hover_pads.h"
#include "app/hud.h"
#include "app/snd.h"
#include "app/text_data.h"
#include "app/wind_objects.h"
#include "app/code_61A60.h"
#include "app/code_66F70.h"
#include "app/code_B2900.h"

Unk802D3658_Unk111C D_80371630;
Unk802D3658_Unk1224 D_80371738;
s32 D_8037187C;
s32 D_80371880;

void func_80328A14(RocketBeltData*);
void func_80328CA0(RocketBeltData*);
void func_80328D74(RocketBeltData*);
void func_80328F44(RocketBeltData*);
void func_80329120(RocketBeltData*);
void func_803291A8(RocketBeltData*);
void func_8032923C(RocketBeltData*);
void func_80329628(RocketBeltData*);
void func_8032975C(RocketBeltData*);
void func_8032A4A8(RocketBeltData*);

void func_80328420(RocketBeltData* rbData) {
    Vec3F sp24 = { 0.0f, 0.0f, 0.0f };

    D_80371630.unk0 = 4;
    D_80371630.unk4[0].unk0 = 1;
    uvVec3Copy(&D_80371630.unk4[0].unk28, &sp24);
    uvVec3Copy(&D_80371630.unk4[0].unk1C, &rbData->unk250);
    D_80371630.unk4[1].unk0 = 1;
    uvVec3Copy(&D_80371630.unk4[1].unk28, &sp24);
    uvVec3Copy(&D_80371630.unk4[1].unk1C, &rbData->unk25C);
    D_80371630.unk4[2].unk0 = 1;
    uvVec3Copy(&D_80371630.unk4[2].unk28, &rbData->unk280);
    uvVec3Copy(&D_80371630.unk4[2].unk1C, &rbData->unk28C);
    D_80371630.unk4[3].unk0 = 1;
    uvVec3Copy(&D_80371630.unk4[3].unk28, &rbData->unk274);
    uvVec3Copy(&D_80371630.unk4[3].unk1C, &rbData->unk268);
    rbData->unk1E8.x = rbData->unk1E8.y = rbData->unk1E8.z = 0.0f;
    func_80328538(rbData);
}

s32 padD_8034FBBC[5] = { 0 };

void func_80328538(RocketBeltData* rbData) {
    s32 pad;

    rbData->unk1E8.x = 0.0f;
    rbData->unk1E8.y = 0.0f;
    rbData->unk1E8.z = 0.0f;
    rbData->unk1F8.x = 0.0f;
    rbData->unk1F8.y = 0.0f;
    rbData->unk1F8.z = 0.0f;
    rbData->unk204.x = 0.0f;
    rbData->unk204.y = 0.0f;
    rbData->unk204.z = 0.0f;
    rbData->unk214.x = 0.0f;
    rbData->unk214.y = 0.0f;
    rbData->unk214.z = 0.0f;
    rbData->unk220.x = 0.0f;
    rbData->unk220.y = 0.0f;
    rbData->unk220.z = 0.0f;
    rbData->unk244.x = 0.0f;
    rbData->unk244.y = 0.0f;
    rbData->unk244.z = 0.0f;
    rbData->unk22C.x = 0.0f;
    rbData->unk22C.y = 0.0f;
    rbData->unk22C.z = 1.0f;
    rbData->unk238.x = 0.0f;
    rbData->unk238.y = 0.0f;
    rbData->unk238.z = -9.8f;
    rbData->unk108.x = 0.0f;
    rbData->unk108.y = 0.0f;
    rbData->unk108.z = 1.0f;
    rbData->unk1F4 = 0.0f;
    rbData->unk210 = 0.0f;
    rbData->unk70 = 0.0f;
    rbData->unk74 = 0.0f;
    rbData->unk78 = 0.0f;
    rbData->unk7C = 0.0f;
    rbData->unk84 = 0.0f;
    rbData->unkF4 = 0.0f;
    rbData->unk114 = 0.0f;
    rbData->unk118 = 0.0f;
    rbData->unk80 = 0;
    rbData->unk91 = 0;
    rbData->unkE8 = 0;
    rbData->unkF0 = -1;
    rbData->unk64 = 0;

    uvMat4Copy(&rbData->unk15C, &rbData->unk10);
    rbData->unk15C.m[3][0] = 0.0f;
    rbData->unk15C.m[3][1] = 0.0f;
    rbData->unk15C.m[3][2] = 0.0f;
    uvMat4LocalToWorld(&rbData->unk15C, &rbData->unk1E8, &rbData->unk1DC);
    rbData->unk380 = 1;
    rbData->unk374.x = rbData->unk10.m[3][0];
    rbData->unk374.y = rbData->unk10.m[3][1];
    rbData->unk374.z = rbData->unk10.m[3][2];
    D_8037187C = 0;
    D_80371880 = 0;
}

extern f32 D_8034F850;
extern f32 D_8034F854;

void func_8032867C(RocketBeltData* rbData) {
    Vec3F sp3C;

    uvMat4Copy(&rbData->unk15C, &rbData->unk10);
    rbData->unk15C.m[3][0] = 0.0f;
    rbData->unk15C.m[3][1] = 0.0f;
    rbData->unk15C.m[3][2] = 0.0f;
    uvMat4InvertTranslationRotation(&rbData->unk11C, &rbData->unk15C);
    uvMat4LocalToWorld(&rbData->unk11C, &rbData->unk1F8, &rbData->unk204);
    uvMat4LocalToWorld(&rbData->unk11C, &rbData->unk1DC, &rbData->unk1E8);
    rbData->unk1F8.x = 0.0f;
    rbData->unk1F8.y = 0.0f;
    rbData->unk1F8.z = 0.0f;
    rbData->unk220.x = 0.0f;
    rbData->unk220.y = 0.0f;
    rbData->unk220.z = 0.0f;
    func_803291A8(rbData);
    func_80329120(rbData);
    func_80329628(rbData);
    if ((rbData->unk91 == 0) && (rbData->unk90 != 2)) {
        func_8032923C(rbData);
    }

    switch (rbData->unk90) {
    case 3:
        return;
    case 0:
        func_80328A14(rbData);
        break;
    default:
        break;
    case 1:
        func_80328CA0(rbData);
        break;
    case 2:
        func_80328D74(rbData);
        break;
    }
    if (rbData->unk84 > 0.0f) {
        sp3C.x = 0.0f;
        sp3C.y = 0.0f;
        sp3C.z = 1.0f;
        func_80313C94(&sp3C, &rbData->unk22C, 1.5f);
    } else if (rbData->unkE9 == 0) {
        rbData->unk22C.x = rbData->unk10.m[2][0];
        rbData->unk22C.y = rbData->unk10.m[2][1];
        rbData->unk22C.z = rbData->unk10.m[2][2];
    } else {
        sp3C.x = rbData->unk108.x;
        sp3C.y = rbData->unk108.y;
        sp3C.z = rbData->unk108.z;
        func_80313C94(&sp3C, &rbData->unk22C, 1.0f);
    }
    uvMat4LocalToWorld(&rbData->unk15C, &rbData->unk204, &rbData->unk1F8);
    rbData->unk1E8.x += D_8034F854 * rbData->unk204.x;
    rbData->unk1E8.y += D_8034F854 * rbData->unk204.y;
    rbData->unk1E8.z += D_8034F854 * rbData->unk204.z;
    rbData->unk214.x += D_8034F854 * rbData->unk220.x;
    rbData->unk214.y += D_8034F854 * rbData->unk220.y;
    rbData->unk214.z += D_8034F854 * rbData->unk220.z;
    uvMat4LocalTranslate(&rbData->unk10, rbData->unk1DC.x * D_8034F854, rbData->unk1DC.y * D_8034F854, rbData->unk1DC.z * D_8034F854);
    uvMat4RotateAxis(&rbData->unk10, rbData->unk214.z * D_8034F854, 'z');
    uvMat4RotateAxis(&rbData->unk10, rbData->unk214.x * D_8034F854, 'x');
    uvMat4RotateAxis(&rbData->unk10, rbData->unk214.y * D_8034F854, 'y');
    func_8032A4A8(rbData);
    func_80328F44(rbData);
    if (rbData->unk90 != 3) {
        func_8032975C(rbData);
    }
    if (rbData->unk90 == 2) {
        rbData->unk91 = 0;
    }
    rbData->unk1F4 = uvVec3Len(&rbData->unk1E8);
    rbData->unk210 = uvVec3Len(&rbData->unk204);
    if (D_80362690->unkA4 != 0) {
        demoAttUpdate(D_8034F850, &rbData->unk10);
    }
}

void func_80328A14(RocketBeltData* rbData) {
    f32 temp_fv1;
    f32 var_fv1;
    s32 pad[3];
    f32 var_fa1;

    temp_fv1 = rbData->unkFC + rbData->unk25C.z;
    rbData->unk220.z -= rbData->unk2F8 * rbData->unk70;
    if (temp_fv1 > 1.5f) {
        rbData->unk4 |= 4;
        rbData->unkEA = 1;
    }

    if (rbData->unkF0 >= 0) {
        temp_fv1 = (rbData->unk10.m[3][2] - hoverPadGetAltitude(rbData->unkF0)) + rbData->unk25C.z;
        if (ABS_NOEQ(temp_fv1) > 1.5f) {
            hoverPadLanded(rbData->unkF0);
            rbData->unkF0 = -1;
        }
    }
    if (rbData->unk84 > 0.0f) {
        rbData->unk220.y = 0.0f;
        rbData->unk220.x = 0.0f;
        func_80313E18(&rbData->unk22C, &rbData->unk10);
    } else {
        if (rbData->unk78 > 0.0f) {
            var_fa1 = uvSqrtF(SQ(rbData->unk10.m[1][0]) + SQ(rbData->unk10.m[1][1])) * rbData->unk2F0;
            temp_fv1 = rbData->unk78 * var_fa1 * rbData->unk74;
            rbData->unk220.x += -rbData->unk2EC * temp_fv1;
            temp_fv1 = rbData->unk78 * var_fa1 * rbData->unk70;
            rbData->unk220.y += rbData->unk2F4 * temp_fv1;
        }
        var_fa1 = uvSqrtF(SQ(rbData->unk238.y) + SQ(rbData->unk238.z + 9.8f)) * rbData->unk2FC;
        if (rbData->unk238.y < 0.0f) {
            var_fa1 = -var_fa1;
        }

        var_fv1 = uvSqrtF(SQ(rbData->unk238.x) + SQ(rbData->unk238.z + 9.8f)) * rbData->unk300;
        if (rbData->unk238.x > 0.0f) {
            var_fv1 = -var_fv1;
        }
        rbData->unk220.x += var_fa1;
        rbData->unk220.y += var_fv1;
    }
    rbData->unk214.x = func_80313BAC(0.0f, rbData->unk214.x, rbData->unk308);
    rbData->unk214.y = func_80313AF4(0.0f, rbData->unk214.y, rbData->unk308);
    rbData->unk214.z = func_80313AF4(0.0f, rbData->unk214.z, rbData->unk304);
    rbData->unk1F8.x -= rbData->unk328 * rbData->unk1DC.x * rbData->unk78;
}

void func_80328CA0(RocketBeltData* rbData) {
    f32 temp_fv0;
    f32 temp_fv1;
    f32 temp_ft4;

    temp_fv0 = rbData->unk1DC.x * -1.2f;
    temp_fv1 = rbData->unk1DC.y * -1.2f;
    temp_ft4 = rbData->unk1DC.z * -1.2f;
    rbData->unk1F8.x += temp_fv0;
    rbData->unk1F8.y += temp_fv1;
    rbData->unk1F8.z += temp_ft4;
    rbData->unk214.x = func_80313AF4(0.0f, rbData->unk214.x, rbData->unk30C);
    rbData->unk214.y = func_80313AF4(0.0f, rbData->unk214.y, rbData->unk30C);
    rbData->unk214.z = func_80313AF4(0.0f, rbData->unk214.z, rbData->unk30C);
    if ((rbData->unk1F4 < 0.8f) && (rbData->unkEA != 0)) {
        rbData->unk90 = 4;
    }
}

void func_80328D74(RocketBeltData* rbData) {
    f32 var_fs0;

    rbData->unk84 = 0.0f;
    if (rbData->unkF4 == 0.0f) {
        if (uvVec3Len(&rbData->unk214) < 0.78539807f) {
            var_fs0 = (demoRandF() + 1.0f) * 21.8f;
            if (demoRandF() < 0.5f) {
                var_fs0 = -var_fs0;
            }
            rbData->unk220.x = rbData->unk32C * var_fs0;
            var_fs0 = (demoRandF() + 1.0f) * 21.8f;
            if (demoRandF() < 0.5f) {
                var_fs0 = -var_fs0;
            }
            rbData->unk220.y = rbData->unk330 * var_fs0;
            var_fs0 = (demoRandF() + 1.0f) * 10.9f;
            if (demoRandF() < 0.5f) {
                var_fs0 = -var_fs0;
            }
            rbData->unk220.z = rbData->unk334 * var_fs0;
        }
        rbData->unkF4 = D_8034F850;
    }
    rbData->unk214.x = func_80313AF4(0.0f, rbData->unk214.x, rbData->unk310);
    rbData->unk214.y = func_80313AF4(0.0f, rbData->unk214.y, rbData->unk310);
    rbData->unk214.z = func_80313AF4(0.0f, rbData->unk214.z, rbData->unk310);
    if ((D_8034F850 - rbData->unkF4) >= 3.75f) {
        rbData->unk90 = 3;
    }
}

void func_80328F44(RocketBeltData* rbData) {
    f32 sp5C;
    s32 pad;
    Vec3F sp4C;
    s32 sp48;
    Vec3F* sp2C;
    f32 temp_fv0;
    Vec3F* sp3C;
    u8 sp3B;
    s32 sp34;

    rbData->unkFC = 1000000.0f;
    sp5C = 0.0f;
    sp34 = rbData->unk380;
    sp2C = (Vec3F*)rbData->unk10.m[3];
    sp3B = db_getgnd(&rbData->unk374, sp2C, &sp34, &sp48, &sp5C, &sp4C);

    temp_fv0 = sp2C->z - sp5C;
    if (temp_fv0 <= rbData->unkFC) {
        rbData->unkFC = temp_fv0;
        rbData->unk100 = sp48;
        rbData->unk104 = sp5C;
        rbData->unk108.x = sp4C.x;
        rbData->unk108.y = sp4C.y;
        rbData->unk108.z = sp4C.z;
    }
    rbData->unk91 = sp3B;
    switch (sp3B) {
    case 4:
        sp3C = func_802E02EC();
        func_802E05CC(&rbData->unk10, sp3C, &sp4C, 0);
        uvVec3Copy(&rbData->unkDC, sp3C);
        rbData->unk90 = 3;
        if (sp3B == 4) {
            rbData->unkE8 = 1;
        }
        rbData->unk91 = 0;
        break;
    case 1:
    case 8:
        sp3C = func_802E02EC();
        func_802E05CC(&rbData->unk10, sp3C, &sp4C, 0);
        break;
    case 2:
        if (ballsObjIdExists(rbData->unk100) == 0) {
            sp3C = func_802E02EC();
            func_802E05CC(&rbData->unk10, sp3C, &sp4C, 0);
            uvVec3Copy(&rbData->unkDC, sp3C);
        } else {
            rbData->unk91 = 0;
        }
        break;
    }
    if (rbData->unk90 != 3) {
        rbData->unk374.x = sp2C->x;
        rbData->unk374.y = sp2C->y;
        rbData->unk374.z = sp2C->z;
    }
}

void func_80329120(RocketBeltData* rbData) {
    f32 var_fa0;
    f32 var_fa1;
    f32 var_fv0;

    var_fv0 = -rbData->unk318 * rbData->unk1DC.x * rbData->unk1DC.x;
    if (rbData->unk1DC.x < 0.0f) {
        var_fv0 = -var_fv0;
    }

    var_fa0 = -rbData->unk318 * rbData->unk1DC.y * rbData->unk1DC.y;
    if (rbData->unk1DC.y < 0.0f) {
        var_fa0 = -var_fa0;
    }

    var_fa1 = -rbData->unk318 * rbData->unk1DC.z * rbData->unk1DC.z;
    if (rbData->unk1DC.z < 0.0f) {
        var_fa1 = -var_fa1;
    }
    rbData->unk1F8.x += var_fv0;
    rbData->unk1F8.y += var_fa0;
    rbData->unk1F8.z += var_fa1;
}

void func_803291A8(RocketBeltData* rbData) {
    Vec3F sp1C;

    sp1C.x = 0.0f;
    sp1C.y = 0.0f;
    sp1C.z = -9.8f;
    uvMat4LocalToWorld(&rbData->unk11C, &rbData->unk238, &sp1C);
    if (rbData->unk84 > 0.0f) {
        return;
    }
    rbData->unk1F8.x += rbData->unk238.x;
    rbData->unk1F8.y += rbData->unk238.y;
    rbData->unk1F8.z += rbData->unk238.z;
}

void func_8032923C(RocketBeltData* rbData) {
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    f32 var_ft4;
    f32 var_fv0;
    f32 var_fv1;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 temp_fv1;
    f32 temp_fa0;
    f32 temp_ft4;

    func_80313570(&rbData->unk10, &sp5C, &sp58, &sp54, &sp50, &sp4C, &sp48);
    if (rbData->unk80 != 0) {
        rbData->unkF8 -= rbData->unk324 * D_8034F854;
        rbData->unk7C = uvCosF(20.0f * D_8034F850) * 1.5707964f;
        if (rbData->unkF8 > 0.0f) {
            rbData->unk1F8.z = 0.0f;
            rbData->unk1F8.y = 0.0f;
            rbData->unk1F8.x = 0.0f;
            if (rbData->unk1F4 > 0.0f) {
                temp_fv1 = (rbData->unk1DC.x / rbData->unk1F4);
                temp_fa0 = (rbData->unk1DC.y / rbData->unk1F4);
                temp_ft4 = (rbData->unk1DC.z / rbData->unk1F4);
                rbData->unk1F4 -= 59.6f * D_8034F854;
                if (rbData->unk1F4 < 0.0f) {
                    rbData->unk1F4 = 0.0f;
                }
                rbData->unk1DC.x = rbData->unk1F4 * temp_fv1;
                rbData->unk1DC.y = rbData->unk1F4 * temp_fa0;
                rbData->unk1DC.z = rbData->unk1F4 * temp_ft4;
                uvMat4LocalToWorld(&rbData->unk15C, &rbData->unk1E8, &rbData->unk1DC);
            }
            rbData->unk84 = 1.0f;
        } else {
            rbData->unk84 = 0.0f;
        }
    } else {
        rbData->unk7C = sp4C - (rbData->unk74 * 1.5707964f);
        rbData->unk84 -= 3.3333f * D_8034F854;
        if (rbData->unk84 < 0.0f) {
            rbData->unk84 = 0.0f;
        } else if (rbData->unk84 > 1.0f) {
            rbData->unk84 = 1.0f;
        }
    }

    if ((rbData->unk81 == 1) || (rbData->unk81 == 2)) {
        rbData->unk84 = 0.0f;
    }

    if (rbData->unk78 > 1.0f) {
        rbData->unkF8 -= ((rbData->unk320 * 2.5f) + rbData->unk31C) * D_8034F854;
    } else if (rbData->unk78 > 0.0f) {
        rbData->unkF8 -= (rbData->unk320 + rbData->unk31C) * D_8034F854;
    }
    if (rbData->unkF8 < 0.0f) {
        rbData->unkF8 = 0.0f;
    }
    if (rbData->unkF8 <= 0.0f) {
        return;
    }

    var_ft4 = rbData->unk2E8 + (rbData->unk78 * rbData->unk2E4);
    if (rbData->unk10.m[3][2] > 928.5f) {
        var_fv0 = 1.0f - ((rbData->unk10.m[3][2] - 928.5f) / 105.5f);
        if (rbData->unk1E8.z < 0.0f) {
            var_fv0 = 1.0f;
        } else {
            rbData->unk1E8.z *= var_fv0;
        }
        var_ft4 *= var_fv0;
    }

    if (rbData->unk1F4 > 80.0f) {
        var_fv1 = 1.0f - ((rbData->unk1F4 - 80.0f) / 40.0f);
        if (var_fv1 < 0.0f) {
            var_fv1 = 0.0f;
        } else if (var_fv1 > 1.0f) {
            var_fv1 = 1.0f;
        }
        var_ft4 *= var_fv1;
    }

    sp74 = 0.0f;
    sp70 = uvSinF(rbData->unk7C) * -var_ft4;
    sp6C = uvCosF(rbData->unk7C) * var_ft4;
    rbData->unk1F8.x += sp74;
    rbData->unk1F8.y += sp70;
    rbData->unk1F8.z += sp6C;
}

void func_80329628(RocketBeltData* rbData) {
    Vec3F sp34;
    Vec3F sp28;

    if ((rbData->unk84 > 0.0f) || (rbData->unkE9 != 0)) {
        sp34.x = sp34.y = sp34.z = 0.0f;
        sp28.x = sp28.y = sp28.z = 0.0f;
    } else {
        env_802E1754(rbData->unk10.m[3][0], rbData->unk10.m[3][1], rbData->unk10.m[3][2], &sp28);
        uvMat4LocalToWorld(&rbData->unk11C, &sp34, &sp28);
    }

    rbData->unk244.x = sp34.x - rbData->unk1DC.x;
    rbData->unk244.y = sp34.y - rbData->unk1DC.y;
    rbData->unk244.z = sp34.z - rbData->unk1DC.z;
    rbData->unk1F8.x += rbData->unk314 * sp34.x;
    rbData->unk1F8.y += rbData->unk314 * sp34.y;
    rbData->unk1F8.z += rbData->unk314 * sp34.z;
    rbData->unk204.x += rbData->unk314 * sp28.x;
    rbData->unk204.y += rbData->unk314 * sp28.y;
    rbData->unk204.z += rbData->unk314 * sp28.z;
}

void func_8032975C(RocketBeltData* rbData) {
    Vec3F sp2AC;
    Vec3F sp2A0;
    f32 sp29C;
    f32 sp298;
    f32 sp294;
    f32 sp290;
    f32 sp28C;
    f32 sp288;
    s32 i;
    s32 pad;
    u8 sp27F;
    u8 sp27E;
    u8 sp27D;
    u8 sp27C;
    s32 sp278;
    s32 sp274;
    f32 temp_fv1;
    Unk802D3658_Unk1120* temp_v0_7;
    s32 sp268;
    Unk802D3658_Unk1228* var_s1;
    Vec3F sp258;
    Vec3F sp24C;
    Vec3F sp240;
    Mtx4F sp200;
    Unk802D3658_Unk1224 spBC;

    sp27C = sp27D = 0;
    sp278 = -1;
    for (i = 0; i < 4; i++) {
        rbData->unkCC[i] = 0.0f;
        rbData->unk93[i] = 0;
    }
    // FAKE
    if (1) { }
    rbData->unkE9 = 0;
    rbData->unkE8 = 0;
    rbData->unk64 = 0;
    sp268 = 0;

    sp27F = rbData->unk92 = func_802DB050(&D_80371630, &D_80371738, rbData->objId, rbData->unk2, &rbData->unk10);

    if ((rbData->unkFC + rbData->unk25C.z) > 0.5f) {
        D_80371880 = 1;
    }
    if (sp27F) {
        D_8037187C++;
        if (D_8037187C > 1) {
            D_8037187C = 1;
        }
    } else {
        D_8037187C--;
        if (D_8037187C < 0) {
            D_8037187C = 0;
        }
    }
    if (D_8037187C == 0) {
        sp27E = 0;
    } else {
        sp27E = 1;
    }
    if ((D_80371880 != 0) && (sp27F)) {
        D_8037187C = sp27E = D_80371880 = 0;
    }

    for (i = 0; i < sp27F; i++) {
        var_s1 = &D_80371738.unk4[i];
        if ((var_s1->collisionType != 2) || ((var_s1->collisionType == 2) && (ballsObjIdExists(var_s1->surfaceId) == 0))) {
            func_802DC814(var_s1, (Vec3F*)rbData->unk10.m[3]);
        }
        func_802DBE64(&D_80371630, &D_80371738, i, &rbData->unk11C);
        uvVec3Copy(&rbData->unk9C[i], &var_s1->unkC);
        rbData->unk97[i] = var_s1->unk0;
        rbData->unk93[i] = var_s1->collisionType;
        rbData->unkCC[i] = uvVec3Dot(&rbData->unk1DC, &var_s1->unk34);
        sp2AC.x = -rbData->unk1DC.x;
        sp2AC.y = -rbData->unk1DC.y;
        sp2AC.z = -rbData->unk1DC.z;

        switch (var_s1->collisionType) {
        case 4:
            if ((rbData->unk90 != 3) && (rbData->unk90 != 2)) {
                rbData->unk90 = 0;
            }
            rbData->unkE8 = 1;
            rbData->unk91 = 0;
            return;
        case 1:
        case 8:
        case 2:
            if (var_s1->collisionType == 2) {
                sp274 = windObjIsLoadedId(var_s1->surfaceId);
                if (sp274 == 0) {
                    sp278 = hoverPadGetLandedIdx(var_s1->surfaceId, rbData->unk1F4);
                    if ((sp278 < 0) && (sp27C == 0) && (sp274 == 0)) {
                        sp29C = sp298 = ballsPopped(var_s1->surfaceId, &rbData->unk1E8, &D_80371738);
                        if (sp29C != 0.0f) {
                            sp27C++;
                            break;
                        }
                        return;
                    }
                }
            }

            sp28C = uvVec3Len(&rbData->unk1E8);
            sp294 = -uvVec3Dot(&rbData->unk1E8, &rbData->unk108);
            sp288 = SQ(sp28C) - SQ(sp294);
            if (sp288 > 0.0f) {
                sp290 = uvSqrtF(sp288);
            } else {
                sp290 = 0.0f;
            }
            if (var_s1->unk0 != 1) {
                sp29C = 0.4f;
                sp298 = 1.0f;
                if (D_8037187C == 0) {
                    rbData->unk91 = var_s1->collisionType;
                }
                if (sp27C) {
                    rbData->unk91 = 0;
                }

                if ((ABS_NOEQ(sp294) > 21.8f) && (sp27C == 0)) {
                    rbData->unk90 = 2;
                    rbData->unk91 = 0;
                }
                break;
            }
            rbData->unk64 = func_8032BE10()->unk3D;
            if (ABS_NOEQ(rbData->unk214.x) > 0.11f) {
                sp27D = 1;
            }
            if (sp294 > 21.8f) {
                rbData->unk90 = 2;
                rbData->unk91 = 0;
                rbData->unk4 &= ~4;
                rbData->unk114 = 1000.0f;
                rbData->unk118 = 1000.00f;
                sp29C = 0.4f;
                sp298 = 1.0f;
            } else if (sp294 > 7.93f) {
                if (sp290 > 7.93f) {
                    rbData->unk91 = var_s1->collisionType;
                    rbData->unk4 &= ~4;
                    sp29C = 0.4f;
                    sp298 = 1.0f;
                } else {
                    if (sp27D != 0) {
                        sp29C = 0.2f;
                        sp298 = 0.5f;
                        if (rbData->unk78 <= 0.0f) {
                            if (sp27E == 0) {
                                rbData->unk91 = var_s1->collisionType;
                            }
                            rbData->unkE9 = 1;
                            sp29C = 0.10f;
                        }
                    } else if (rbData->unk64 != 0) {
                        rbData->unk91 = 0;
                        sp29C = 0.2f;
                        sp298 = 0.5f;
                        rbData->unk90 = 4;
                        rbData->unk118 = sp290;
                        rbData->unk114 = sp294;
                    } else {
                        sp29C = 0.2f;
                        sp298 = 1.0f;
                        rbData->unk91 = var_s1->collisionType;
                    }
                }
            } else if (sp290 > 7.93f) {
                rbData->unk4 &= ~4;
                sp298 = 1.0f;
                sp29C = 0.4f;
            } else if (sp27D != 0) {
                sp29C = 0.2f;
                sp298 = 0.0f;
                if (rbData->unk78 <= 0.0f) {
                    rbData->unkE9 = 1;
                }
                if (!sp27E) {
                    rbData->unk91 = var_s1->collisionType;
                    sp29C = 0.10f;
                }
                if ((rbData->unkF8 <= 0.0f) && (rbData->unkE9 != 0) && (rbData->unk90 != 2)) {
                    sp29C = 0.2f;
                    sp298 = 0.5f;
                    rbData->unk90 = 4;
                    rbData->unk4 &= ~4;
                }
            } else if (rbData->unk64 != 0) {
                rbData->unk91 = 0;
                sp29C = 0.10f;
                sp298 = 0.5f;
                rbData->unk90 = 4;
                rbData->unkE9 = 1;
                rbData->unk114 = sp294;
                rbData->unk118 = sp290;
            } else {
                sp29C = 0.2f;
                sp298 = 0.0f;
                if ((sp278 >= 0) && (rbData->unkF0 < 0)) {
                    rbData->unkF0 = sp278;
                    rbData->unkF8 += hoverPadGetFuel(sp278);
                    hoverPadActivateNext(rbData->unkF0);
                    hudText_8031D8E0(TEXT_P_CLR, 1.5f, 8.0f);

                    if (rbData->unkF8 < 0.0f) {
                        rbData->unkF8 = 0.0f;
                    } else if (rbData->unkF8 > 1.0f) {
                        rbData->unkF8 = 1.0f;
                    }
                    if (rbData->unkF8 >= 0.15f) {
                        rbData->unkEB = 0;
                    }
                    rbData->unkEC = 0;
                } else if (rbData->unk78 <= 0.0f) {
                    rbData->unkE9 = 1;
                }
                if (!sp27E && (rbData->unkF0 < 0)) {
                    rbData->unk91 = var_s1->collisionType;
                }
                if ((rbData->unkF8 <= 0.0f) && (rbData->unkE9 != 0)) {
                    sp29C = 0.1f;
                    sp298 = 0.5f;
                    rbData->unk90 = 4;
                    rbData->unk4 &= ~4;
                    rbData->unk4 &= ~0x800;
                }
            }
            break;
        default:
            _uvDebugPrintf("rpmot : unknown collision type [%d]\n", var_s1->collisionType);
            break;
        }
        if (var_s1->collisionType == 8) {
            if ((func_802DC97C(var_s1->surfaceId) != 0) && (var_s1->unk1C.z > 0.9f)) {
                sp298 = 1.0f;
                var_s1->unk34.x = 0.5f - uvRandF_RANLUX();
                var_s1->unk34.y = 0.5f - uvRandF_RANLUX();
                var_s1->unk34.z = 0.5f;
                uvVec3Normal(&var_s1->unk34, &var_s1->unk34);
                uvMat4LocalToWorld(&rbData->unk15C, &var_s1->unk1C, &var_s1->unk34);
                sp29C = 1.0f - (ABS_NOEQ(rbData->unk1E8.z) * 0.5f);
                if (sp29C < 0.9f) {
                    sp29C = 0.9f;
                } else if (sp29C > 1.0f) {
                    sp29C = 1.0f;
                }
                rbData->unkE9 = 0;
            }
            if (func_802DC97C(var_s1->surfaceId) != 0) {
                sndPlaySfxVolPitchPan(0x39, 1.0f, 1.0f, 0.0f);
            }
        }

        if ((rbData->unkE9 != 0) && (rbData->unk90 != 2)) {
            if (var_s1->unk1C.z < 0.9f) {
                sp298 = 1.0f;
            } else {
                sp298 = (((1.0f - var_s1->unk1C.z) / 0.1f) * 0.100000024f) + 0.9f;
            }
            func_802DC784(&rbData->unk11C, &rbData->unk1DC, &rbData->unk1E8, &var_s1->unk1C, sp298);
            if ((rbData->unk1DC.y < 0.5f) && (rbData->unk108.z > 0.96)) {
                func_80313E18(&rbData->unk22C, &rbData->unk10);
            }
        } else {
            if (rbData->unk90 == 2) {
                sp298 = 1.0f;
            }
            func_802DC1DC(&rbData->unk220, &var_s1->unk28, &sp2AC, rbData->unk32C * sp298, rbData->unk330 * sp298, rbData->unk334 * sp298);
            uvVec3Copy(&sp2A0, &rbData->unk1DC);
            func_802DC074(&rbData->unk15C, &rbData->unk1DC, &rbData->unk1E8, &var_s1->unk34, sp29C);

            if ((ABS_NOEQ(sp2A0.x - rbData->unk1DC.x) < 0.1f) && (ABS_NOEQ(sp2A0.y - rbData->unk1DC.y) < 0.1f) &&
                (ABS_NOEQ(sp2A0.y - rbData->unk1DC.z) < 0.1f)) {
                rbData->unk1DC.x += var_s1->unk34.x;
                rbData->unk1DC.y += var_s1->unk34.y;
                rbData->unk1DC.z += var_s1->unk34.z;
                uvMat4LocalToWorld(&rbData->unk15C, &rbData->unk1E8, &rbData->unk1DC);
            }
        }
        if (rbData->unk90 != 3) {
            if ((var_s1->collisionType == 2) && (ballsObjIdExists(var_s1->surfaceId) != 0)) {
                break;
            }
            temp_v0_7 = &D_80371630.unk4[var_s1->unk0];
            func_802DCA5C(&temp_v0_7->unk28, &temp_v0_7->unk1C, &var_s1->unk28, &var_s1->unk34, &sp258);
            sp24C.x = rbData->unk10.m[3][0];
            sp24C.y = rbData->unk10.m[3][1];
            sp24C.z = rbData->unk10.m[3][2];
            uvMat4Copy(&sp200, &rbData->unk10);
            uvMat4LocalTranslate(&sp200, sp258.x, sp258.y, sp258.z);
            sp240.x = sp200.m[3][0];
            sp240.y = sp200.m[3][1];
            sp240.z = sp200.m[3][2];
            func_802DB224(&spBC, 0xFF, rbData->objId, rbData->unk2, &sp24C, &sp240);
            if (spBC.unk0 > 0) {
                sp268++;
            } else {
                uvMat4LocalTranslate(&rbData->unk10, sp258.x, sp258.y, sp258.z);
                rbData->unk374.x = rbData->unk10.m[3][0];
                rbData->unk374.y = rbData->unk10.m[3][1];
                rbData->unk374.z = rbData->unk10.m[3][2];
            }
        }
    }

    if (sp27F && (sp268 == sp27F)) {
        rbData->unk90 = 3;
        _uvDebugPrintf("rpmot : you got stuck - forcing an instant crash\n");
    }
    if ((!sp27F) && ((rbData->unk90 != 3) && (rbData->unk90 != 2))) {
        rbData->unk90 = 0;
    }
}

void func_8032A4A8(RocketBeltData* rbData) {
    f32 var_fs0;
    f32 sp28;
    f32 sp24;
    f32 sp20;

    sp28 = rbData->unk25C.z;

    var_fs0 = ABS_NOEQ(rbData->unk344);
    if (var_fs0 < 0.1f) {
        sp20 = 0.0f;
        sp24 = 0.0f;
    } else {
        sp24 = rbData->unk344;
        var_fs0 = ABS_NOEQ(rbData->unk34C);
        if (var_fs0 < 0.1f) {
            sp20 = 0.0f;
        } else {
            sp20 = rbData->unk34C;
        }
    }
    D_80371630.unk4[1].unk0 = 1;
    var_fs0 = uvSinF(sp24);
    D_80371630.unk4[1].unk1C.y = (rbData->unk25C.y - ((0.5f * sp28) * var_fs0)) - (uvSinF(sp20) * (0.5f * sp28));
    var_fs0 = uvCosF(sp24);
    D_80371630.unk4[1].unk1C.z = (uvCosF(sp20) * (0.4f * sp28)) + ((0.2f * sp28) + ((0.4f * sp28) * var_fs0));
}
