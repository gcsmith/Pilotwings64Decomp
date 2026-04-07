#include "common.h"
#include "rocket_belt.h"
#include <uv_math.h>
#include <uv_vector.h>
#include "app/balls.h"
#include "app/demo.h"
#include "app/demo_attitude.h"
#include "app/environment.h"
#include "app/hover_pads.h"
#include "app/code_66F70.h"

extern Unk802D3658_Unk111C D_80371630;
extern s32 D_8037187C;
extern s32 D_80371880;

void func_80328538(RocketBeltData*);
void func_80328A14(RocketBeltData*);
void func_80328CA0(RocketBeltData*);
void func_80328D74(RocketBeltData*);
void func_80328F44(RocketBeltData*);
void func_80329120(RocketBeltData*);
void func_803291A8(RocketBeltData*);
void func_8032923C(RocketBeltData*);
void func_80329628(RocketBeltData*);

void func_80328420(RocketBeltData* arg0) {
    Vec3F sp24 = { 0.0f, 0.0f, 0.0f };

    D_80371630.unk0 = 4;
    D_80371630.unk4[0].unk0 = 1;
    uvVec3Copy(&D_80371630.unk4[0].unk28, &sp24);
    uvVec3Copy(&D_80371630.unk4[0].unk1C, &arg0->unk250);
    D_80371630.unk4[1].unk0 = 1;
    uvVec3Copy(&D_80371630.unk4[1].unk28, &sp24);
    uvVec3Copy(&D_80371630.unk4[1].unk1C, &arg0->unk25C);
    D_80371630.unk4[2].unk0 = 1;
    uvVec3Copy(&D_80371630.unk4[2].unk28, &arg0->unk280);
    uvVec3Copy(&D_80371630.unk4[2].unk1C, &arg0->unk28C);
    D_80371630.unk4[3].unk0 = 1;
    uvVec3Copy(&D_80371630.unk4[3].unk28, &arg0->unk274);
    uvVec3Copy(&D_80371630.unk4[3].unk1C, &arg0->unk268);
    arg0->unk1E8.x = arg0->unk1E8.y = arg0->unk1E8.z = 0.0f;
    func_80328538(arg0);
}

s32 padD_8034FBBC[5] = { 0 };

void func_80328538(RocketBeltData* arg0) {
    s32 pad;

    arg0->unk1E8.x = 0.0f;
    arg0->unk1E8.y = 0.0f;
    arg0->unk1E8.z = 0.0f;
    arg0->unk1F8.x = 0.0f;
    arg0->unk1F8.y = 0.0f;
    arg0->unk1F8.z = 0.0f;
    arg0->unk204.x = 0.0f;
    arg0->unk204.y = 0.0f;
    arg0->unk204.z = 0.0f;
    arg0->unk214.x = 0.0f;
    arg0->unk214.y = 0.0f;
    arg0->unk214.z = 0.0f;
    arg0->unk220.x = 0.0f;
    arg0->unk220.y = 0.0f;
    arg0->unk220.z = 0.0f;
    arg0->unk244.x = 0.0f;
    arg0->unk244.y = 0.0f;
    arg0->unk244.z = 0.0f;
    arg0->unk22C.x = 0.0f;
    arg0->unk22C.y = 0.0f;
    arg0->unk22C.z = 1.0f;
    arg0->unk238.x = 0.0f;
    arg0->unk238.y = 0.0f;
    arg0->unk238.z = -9.8f;
    arg0->unk108.x = 0.0f;
    arg0->unk108.y = 0.0f;
    arg0->unk108.z = 1.0f;
    arg0->unk1F4 = 0.0f;
    arg0->unk210 = 0.0f;
    arg0->unk70 = 0.0f;
    arg0->unk74 = 0.0f;
    arg0->unk78 = 0.0f;
    arg0->unk7C = 0.0f;
    arg0->unk84 = 0.0f;
    arg0->unkF4 = 0.0f;
    arg0->unk114 = 0.0f;
    arg0->unk118 = 0.0f;
    arg0->unk80 = 0;
    arg0->unk91 = 0;
    arg0->unkE8 = 0;
    arg0->unkF0 = -1;
    arg0->unk64 = 0;

    uvMat4Copy(&arg0->unk15C, &arg0->unk10);
    arg0->unk15C.m[3][0] = 0.0f;
    arg0->unk15C.m[3][1] = 0.0f;
    arg0->unk15C.m[3][2] = 0.0f;
    uvMat4LocalToWorld(&arg0->unk15C, &arg0->unk1E8, &arg0->unk1DC);
    arg0->unk380 = 1;
    arg0->unk374.x = arg0->unk10.m[3][0];
    arg0->unk374.y = arg0->unk10.m[3][1];
    arg0->unk374.z = arg0->unk10.m[3][2];
    D_8037187C = 0;
    D_80371880 = 0;
}

extern f32 D_8034F850;
extern f32 D_8034F854;

void func_8032867C(RocketBeltData* arg0) {
    Vec3F sp3C;

    uvMat4Copy(&arg0->unk15C, &arg0->unk10);
    arg0->unk15C.m[3][0] = 0.0f;
    arg0->unk15C.m[3][1] = 0.0f;
    arg0->unk15C.m[3][2] = 0.0f;
    uvMat4InvertTranslationRotation(&arg0->unk11C, &arg0->unk15C);
    uvMat4LocalToWorld(&arg0->unk11C, &arg0->unk1F8, &arg0->unk204);
    uvMat4LocalToWorld(&arg0->unk11C, &arg0->unk1DC, &arg0->unk1E8);
    arg0->unk1F8.x = 0.0f;
    arg0->unk1F8.y = 0.0f;
    arg0->unk1F8.z = 0.0f;
    arg0->unk220.x = 0.0f;
    arg0->unk220.y = 0.0f;
    arg0->unk220.z = 0.0f;
    func_803291A8(arg0);
    func_80329120(arg0);
    func_80329628(arg0);
    if ((arg0->unk91 == 0) && (arg0->unk90 != 2)) {
        func_8032923C(arg0);
    }

    switch (arg0->unk90) {
        case 3:
            return;
        case 0:
            func_80328A14(arg0);
            break;
        default:
            break;
        case 1:
            func_80328CA0(arg0);
            break;
        case 2:
            func_80328D74(arg0);
            break;
    }
    if (arg0->unk84 > 0.0f) {
        sp3C.x = 0.0f;
        sp3C.y = 0.0f;
        sp3C.z = 1.0f;
        func_80313C94(&sp3C, &arg0->unk22C, 1.5f);
    } else if (arg0->unkE9 == 0) {
        arg0->unk22C.x = arg0->unk10.m[2][0];
        arg0->unk22C.y = arg0->unk10.m[2][1];
        arg0->unk22C.z = arg0->unk10.m[2][2];
    } else {
        sp3C.x = arg0->unk108.x;
        sp3C.y = arg0->unk108.y;
        sp3C.z = arg0->unk108.z;
        func_80313C94(&sp3C, &arg0->unk22C, 1.0f);
    }
    uvMat4LocalToWorld(&arg0->unk15C, &arg0->unk204, &arg0->unk1F8);
    arg0->unk1E8.x += D_8034F854 * arg0->unk204.x;
    arg0->unk1E8.y += D_8034F854 * arg0->unk204.y;
    arg0->unk1E8.z += D_8034F854 * arg0->unk204.z;
    arg0->unk214.x += D_8034F854 * arg0->unk220.x;
    arg0->unk214.y += D_8034F854 * arg0->unk220.y;
    arg0->unk214.z += D_8034F854 * arg0->unk220.z;
    uvMat4LocalTranslate(&arg0->unk10, arg0->unk1DC.x * D_8034F854, arg0->unk1DC.y * D_8034F854, arg0->unk1DC.z * D_8034F854);
    uvMat4RotateAxis(&arg0->unk10, arg0->unk214.z * D_8034F854, 'z');
    uvMat4RotateAxis(&arg0->unk10, arg0->unk214.x * D_8034F854, 'x');
    uvMat4RotateAxis(&arg0->unk10, arg0->unk214.y * D_8034F854, 'y');
    func_8032A4A8(arg0);
    func_80328F44(arg0);
    if (arg0->unk90 != 3) {
        func_8032975C(arg0);
    }
    if (arg0->unk90 == 2) {
        arg0->unk91 = 0;
    }
    arg0->unk1F4 = uvVec3Len(&arg0->unk1E8);
    arg0->unk210 = uvVec3Len(&arg0->unk204);
    if (D_80362690->unkA4 != 0) {
        demoAttUpdate(D_8034F850, &arg0->unk10);
    }
}

void func_80328A14(RocketBeltData* arg0) {
    f32 temp_fv1;
    f32 var_fv1;
    s32 pad[3];
    f32 var_fa1;

    temp_fv1 = arg0->unkFC + arg0->unk25C.z;
    arg0->unk220.z -= arg0->unk2F8 * arg0->unk70;
    if (temp_fv1 > 1.5f) {
        arg0->unk4 |= 4;
        arg0->unkEA = 1;
    }

    if (arg0->unkF0 >= 0) {
        temp_fv1 = (arg0->unk10.m[3][2] - hoverPadGetAltitude(arg0->unkF0)) + arg0->unk25C.z;
        if (ABS_NOEQ(temp_fv1) > 1.5f) {
            hoverPadLanded(arg0->unkF0);
            arg0->unkF0 = -1;
        }
    }
    if (arg0->unk84 > 0.0f) {
        arg0->unk220.y = 0.0f;
        arg0->unk220.x = 0.0f;
        func_80313E18(&arg0->unk22C, &arg0->unk10);
    } else {
        if (arg0->unk78 > 0.0f) {
            var_fa1 = uvSqrtF(SQ(arg0->unk10.m[1][0]) + SQ(arg0->unk10.m[1][1])) * arg0->unk2F0;
            temp_fv1 =  arg0->unk78 * var_fa1 * arg0->unk74;
            arg0->unk220.x += -arg0->unk2EC * temp_fv1;
            temp_fv1 =  arg0->unk78 * var_fa1 * arg0->unk70;
            arg0->unk220.y += arg0->unk2F4 * temp_fv1;
        }
        var_fa1 = uvSqrtF(SQ(arg0->unk238.y) + SQ(arg0->unk238.z + 9.8f)) * arg0->unk2FC;
        if (arg0->unk238.y < 0.0f) {
            var_fa1 = -var_fa1;
        }

        var_fv1 = uvSqrtF(SQ(arg0->unk238.x) + SQ(arg0->unk238.z + 9.8f)) * arg0->unk300;
        if (arg0->unk238.x > 0.0f) {
            var_fv1 = -var_fv1;
        }
        arg0->unk220.x += var_fa1;
        arg0->unk220.y += var_fv1;
    }
    arg0->unk214.x = func_80313BAC(0.0f, arg0->unk214.x, arg0->unk308);
    arg0->unk214.y = func_80313AF4(0.0f, arg0->unk214.y, arg0->unk308);
    arg0->unk214.z = func_80313AF4(0.0f, arg0->unk214.z, arg0->unk304);
    arg0->unk1F8.x -= arg0->unk328 * arg0->unk1DC.x * arg0->unk78;
}

void func_80328CA0(RocketBeltData* arg0) {
    f32 temp_fv0;
    f32 temp_fv1;
    f32 temp_ft4;
    
    temp_fv0 = arg0->unk1DC.x * -1.2f;
    temp_fv1 = arg0->unk1DC.y * -1.2f;
    temp_ft4 = arg0->unk1DC.z * -1.2f;
    arg0->unk1F8.x += temp_fv0;
    arg0->unk1F8.y += temp_fv1;
    arg0->unk1F8.z += temp_ft4;
    arg0->unk214.x = func_80313AF4(0.0f, arg0->unk214.x, arg0->unk30C);
    arg0->unk214.y = func_80313AF4(0.0f, arg0->unk214.y, arg0->unk30C);
    arg0->unk214.z = func_80313AF4(0.0f, arg0->unk214.z, arg0->unk30C);
    if ((arg0->unk1F4 < 0.8f) && (arg0->unkEA != 0)) {
        arg0->unk90 = 4;
    }
}

void func_80328D74(RocketBeltData* arg0) {
    f32 var_fs0;

    arg0->unk84 = 0.0f;
    if (arg0->unkF4 == 0.0f) {
        if (uvVec3Len(&arg0->unk214) < 0.78539807f) {
            var_fs0 = (demoRandF() + 1.0f) * 21.8f;
            if (demoRandF() < 0.5f) {
                var_fs0 = -var_fs0;
            }
            arg0->unk220.x = arg0->unk32C * var_fs0;
            var_fs0 = (demoRandF() + 1.0f) * 21.8f;
            if (demoRandF() < 0.5f) {
                var_fs0 = -var_fs0;
            }
            arg0->unk220.y = arg0->unk330 * var_fs0;
            var_fs0 = (demoRandF() + 1.0f) * 10.9f;
            if (demoRandF() < 0.5f) {
                var_fs0 = -var_fs0;
            }
            arg0->unk220.z = arg0->unk334 * var_fs0;
        }
        arg0->unkF4 = D_8034F850;
    }
    arg0->unk214.x = func_80313AF4(0.0f, arg0->unk214.x, arg0->unk310);
    arg0->unk214.y = func_80313AF4(0.0f, arg0->unk214.y, arg0->unk310);
    arg0->unk214.z = func_80313AF4(0.0f, arg0->unk214.z, arg0->unk310);
    if ((D_8034F850 - arg0->unkF4) >= 3.75f) {
        arg0->unk90 = 3;
    }
}

void func_80328F44(RocketBeltData* arg0) {
    f32 sp5C;
    s32 pad;
    Vec3F sp4C;
    s32 sp48;
    Vec3F* sp2C;
    f32 temp_fv0;
    Vec3F* sp3C;
    u8 sp3B;
    s32 sp34;

    arg0->unkFC = 1000000.0f;
    sp5C = 0.0f;
    sp34 = arg0->unk380;
    sp2C = (Vec3F* ) arg0->unk10.m[3];
    sp3B = db_getgnd(&arg0->unk374, sp2C, &sp34, &sp48, &sp5C, &sp4C);

    temp_fv0 = sp2C->z - sp5C;
    if (temp_fv0 <= arg0->unkFC) {
        arg0->unkFC = temp_fv0;
        arg0->unk100 = sp48;
        arg0->unk104 = sp5C;
        arg0->unk108.x = sp4C.x;
        arg0->unk108.y = sp4C.y;
        arg0->unk108.z = sp4C.z;
    }
    arg0->unk91 = sp3B;
    switch (sp3B) {
    case 4:
        sp3C = func_802E02EC();
        func_802E05CC(&arg0->unk10, sp3C, &sp4C, 0);
        uvVec3Copy(&arg0->unkDC, sp3C);
        arg0->unk90 = 3;
        if (sp3B == 4) {
            arg0->unkE8 = 1;
        }
        arg0->unk91 = 0;
        break;
    case 1:
    case 8:
        sp3C = func_802E02EC();
        func_802E05CC(&arg0->unk10, sp3C, &sp4C, 0);
        break;
    case 2:
        if (ballsObjIdExists(arg0->unk100) == 0) {
            sp3C = func_802E02EC();
            func_802E05CC(&arg0->unk10, sp3C, &sp4C, 0);
            uvVec3Copy(&arg0->unkDC, sp3C);
        } else {
            arg0->unk91 = 0;
        }
        break;
    }
    if (arg0->unk90 != 3) {
        arg0->unk374.x = sp2C->x;
        arg0->unk374.y = sp2C->y;
        arg0->unk374.z = sp2C->z;
    }
}

void func_80329120(RocketBeltData* arg0) {
    f32 var_fa0;
    f32 var_fa1;
    f32 var_fv0;

    var_fv0 = -arg0->unk318 * arg0->unk1DC.x * arg0->unk1DC.x;
    if (arg0->unk1DC.x < 0.0f) {
        var_fv0 = -var_fv0;
    }

    var_fa0 = -arg0->unk318 * arg0->unk1DC.y * arg0->unk1DC.y;
    if (arg0->unk1DC.y < 0.0f) {
        var_fa0 = -var_fa0;
    }

    var_fa1 = -arg0->unk318 * arg0->unk1DC.z * arg0->unk1DC.z;
    if (arg0->unk1DC.z < 0.0f) {
        var_fa1 = -var_fa1;
    }
    arg0->unk1F8.x += var_fv0;
    arg0->unk1F8.y += var_fa0;
    arg0->unk1F8.z += var_fa1;
}

void func_803291A8(RocketBeltData* arg0) {
    Vec3F sp1C;

    sp1C.x = 0.0f;
    sp1C.y = 0.0f;
    sp1C.z = -9.8f;
    uvMat4LocalToWorld(&arg0->unk11C, &arg0->unk238, &sp1C);
    if (arg0->unk84 > 0.0f) {
        return;
    }
    arg0->unk1F8.x += arg0->unk238.x;
    arg0->unk1F8.y += arg0->unk238.y;
    arg0->unk1F8.z += arg0->unk238.z;
}

void func_8032923C(RocketBeltData* arg0) {
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

    func_80313570(&arg0->unk10, &sp5C, &sp58, &sp54, &sp50, &sp4C, &sp48);
    if (arg0->unk80 != 0) {
        arg0->unkF8 -= arg0->unk324 * D_8034F854;
        arg0->unk7C = uvCosF(20.0f * D_8034F850) * 1.5707964f;
        if (arg0->unkF8 > 0.0f) {
            arg0->unk1F8.z = 0.0f;
            arg0->unk1F8.y = 0.0f;
            arg0->unk1F8.x = 0.0f;
            if (arg0->unk1F4 > 0.0f) {
                temp_fv1 = (arg0->unk1DC.x / arg0->unk1F4);
                temp_fa0 = (arg0->unk1DC.y / arg0->unk1F4);
                temp_ft4 = (arg0->unk1DC.z / arg0->unk1F4);
                arg0->unk1F4 -= 59.6f * D_8034F854;
                if (arg0->unk1F4 < 0.0f) {
                    arg0->unk1F4 = 0.0f;
                }
                arg0->unk1DC.x = arg0->unk1F4 * temp_fv1;
                arg0->unk1DC.y = arg0->unk1F4 * temp_fa0;
                arg0->unk1DC.z = arg0->unk1F4 * temp_ft4;
                uvMat4LocalToWorld(&arg0->unk15C, &arg0->unk1E8, &arg0->unk1DC);
            }
            arg0->unk84 = 1.0f;
        } else {
            arg0->unk84 = 0.0f;
        }
    } else {
        arg0->unk7C = sp4C - (arg0->unk74 * 1.5707964f);
        arg0->unk84 -= 3.3333f * D_8034F854;
        if (arg0->unk84 < 0.0f) {
            arg0->unk84 = 0.0f;
        } else if (arg0->unk84 > 1.0f) {
            arg0->unk84 = 1.0f;
        }
    }

    if ((arg0->unk81 == 1) || (arg0->unk81 == 2)) {
        arg0->unk84 = 0.0f;
    }

    if (arg0->unk78 > 1.0f) {
        arg0->unkF8 -= ((arg0->unk320 * 2.5f) + arg0->unk31C) * D_8034F854;
    } else if (arg0->unk78 > 0.0f) {
        arg0->unkF8 -= (arg0->unk320 + arg0->unk31C) * D_8034F854;
    }
    if (arg0->unkF8 < 0.0f) {
        arg0->unkF8 = 0.0f;
    }
    if (arg0->unkF8 <= 0.0f) {
        return;
    }

    var_ft4 = arg0->unk2E8 + (arg0->unk78 * arg0->unk2E4);
    if (arg0->unk10.m[3][2] > 928.5f) {
        var_fv0 = 1.0f - ((arg0->unk10.m[3][2] - 928.5f) / 105.5f);
        if (arg0->unk1E8.z < 0.0f) {
            var_fv0 = 1.0f;
        } else {
            arg0->unk1E8.z *= var_fv0;
        }
        var_ft4 *= var_fv0;
    }

    if (arg0->unk1F4 > 80.0f) {
        var_fv1 = 1.0f - ((arg0->unk1F4 - 80.0f) / 40.0f);
        if (var_fv1 < 0.0f) {
            var_fv1 = 0.0f;
        } else if (var_fv1 > 1.0f) {
            var_fv1 = 1.0f;
        }
        var_ft4 *= var_fv1;
    }

    sp74 = 0.0f;
    sp70 = uvSinF(arg0->unk7C) * -var_ft4;
    sp6C = uvCosF(arg0->unk7C) * var_ft4;
    arg0->unk1F8.x += sp74;
    arg0->unk1F8.y += sp70;
    arg0->unk1F8.z += sp6C;
}

void func_80329628(RocketBeltData* arg0) {
    Vec3F sp34;
    Vec3F sp28;

    if ((arg0->unk84 > 0.0f) || (arg0->unkE9 != 0)) {
        sp34.x = sp34.y = sp34.z = 0.0f;
        sp28.x = sp28.y = sp28.z = 0.0f;
    } else {
        env_802E1754(arg0->unk10.m[3][0], arg0->unk10.m[3][1], arg0->unk10.m[3][2], &sp28);
        uvMat4LocalToWorld(&arg0->unk11C, &sp34, &sp28);
    }

    arg0->unk244.x = sp34.x - arg0->unk1DC.x;
    arg0->unk244.y = sp34.y - arg0->unk1DC.y;
    arg0->unk244.z = sp34.z - arg0->unk1DC.z;
    arg0->unk1F8.x += arg0->unk314 * sp34.x;
    arg0->unk1F8.y += arg0->unk314 * sp34.y;
    arg0->unk1F8.z += arg0->unk314 * sp34.z;
    arg0->unk204.x += arg0->unk314 * sp28.x;
    arg0->unk204.y += arg0->unk314 * sp28.y;
    arg0->unk204.z += arg0->unk314 * sp28.z;
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/rocket_belt/func_8032975C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/rocket_belt/func_8032A4A8.s")
