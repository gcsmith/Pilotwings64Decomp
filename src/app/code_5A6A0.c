#include "common.h"
#include <uv_graphics.h>
#include <uv_level.h>
#include <uv_math.h>
#include <uv_matrix.h>
#include <uv_vector.h>
#include "code_5A6A0.h"
#include "code_68220.h"
#include "code_72010.h"
#include "code_9A960.h"
#include "demo.h"

typedef struct {
    s32 unk0;
    u8 pad4[0x1C - 0x4];
    volatile f32 unk1C; // volatile needed to avoid s0 usage
    u8 pad20[0x40 - 0x20];
} Unk802D472C_SP60;

extern f32 D_8034E9E0;
extern u8 D_8034E9E4;
extern f32 D_8034F854;
extern Unk803599D0 D_803599D0;
extern f32 D_80359A24;

void func_80204C94(u8, f32, f32, f32, f32, f32, f32);
void func_802D4514(Unk802D3658_Arg0*);
void func_802D45C4(Unk802D3658_Arg0*, f32);
s32 func_802D472C(Unk802D3658_Arg0*, Mtx4F*);
s32 func_802D4CA4(Unk802D3658_Arg0*, Mtx4F*);
void func_802D58EC(Unk802D3658_Arg0*, Mtx4F*);
s32 func_802DB050(s32*, s32*, u16, u8, Mtx4F*);
s32 func_802DB224(s32*, s32, u16, u8, Vec3F*, Vec3F*);
void func_802DBE64(void*, void*, s32, Mtx4F*);
void func_802DCA5C(Vec3F*, Vec3F*, Vec3F*, Vec3F*, Vec3F*);
void func_802EAAE0(Unk802D3658_Unk230*);
void func_802EABAC(Unk802D3658_Unk230*, f32, Mtx4F*);
void func_802EAC9C(Unk802D3658_Unk230*, f32, Mtx4F*);
void func_803134D0(f32, f32, f32, f32*, f32*, f32*);
void func_803138A0(Mtx4F*, Mtx4F*, Mtx4F*, f32);
f32 func_80313AF4(f32, f32, f32);
void func_80313E18(Vec3F*, Mtx4F*);
f32 func_80313F08(Unk803599D0*, f32);
void func_8034ABB0(Mtx4F*, Vec3F*, Vec3F*);
void func_8034AD6C(f32, f32, f32, Mtx4F*);
void func_8034B210(Vec3F, Vec3F, Mtx4F*);
void func_8034B2B0(Vec3F*);
void func_8034B4DC(Vec3F, Mtx4F*);

// forward declarations
s32 func_802D408C(Unk802D3658_Arg0* arg0);
void func_802D3658(Unk802D3658_Arg0* arg0);
void func_802D3790(Unk802D3658_Arg0* arg0);
void func_802D3BE8(Unk802D3658_Arg0* arg0);
void func_802D3FA4(Unk802D3658_Arg0* arg0);
void func_802D41D8(Unk802D3658_Arg0* arg0);
void func_802D4274(Unk802D3658_Arg0* arg0);
void func_802D46A4(Unk802D3658_Arg0* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
void func_802D532C(Unk802D3658_Arg0* arg0);
void func_802D559C(Unk802D3658_Arg0* arg0);

void func_802D3170(u8 arg0, Unk802D3658_Arg0* arg1) {
    f32 one;
    one = 1.0f;
    func_80204A8C(arg0, 3);
    func_802EAAE0(arg1->unk230);
    arg1->unk2 = arg1->unk1;
    arg1->unk0 = 0;
    arg1->unk24 = 10;
    arg1->unk26 = 310;
    arg1->unk28 = 18;
    arg1->unk2A = 232;
    arg1->unk3C = 1.0f;
    arg1->unk40 = 2000.0f;
    arg1->unk2C = one * -0.4906542f;
    arg1->unk30 = one * 0.4906542f;
    arg1->unk34 = one * -0.35f;
    arg1->unk38 = one * 0.35f;
    arg1->unk48 = 0.7f;
    arg1->unk4C = 0.6f;
    arg1->unk5C = 0.0f;
    arg1->unk60 = -4.0f;
    arg1->unk64 = -1.0f;
    arg1->unk54 = 1.8f;
    arg1->unk58 = 10.0f;
    arg1->unk50 = 0.0f;
    arg1->unk68 = 0;
    arg1->unkD = 1;
    arg1->unk6C = -1.2f;
    arg1->unk70 = -0.2f;
    arg1->unk74 = -0.1f;
    arg1->unk190 = 6.0f;
    arg1->unk194 = 0.0f;
    arg1->unk19C = 0.5f;
    arg1->unk198 = 0.52359873f; // almost DEG_TO_RAD(30)
    arg1->unkE = 1;
    arg1->unkC = 1;
    arg1->unk1A8 = 0.0f;
    arg1->unk1AC = 0.0f;
    arg1->unk1B0 = 0.0f;
    arg1->unk200 = 0.0f;
    arg1->unk204.x = 0.0f;
    arg1->unk204.y = 0.0f;
    arg1->unk204.z = 0.0f;
    arg1->unk21C = 0.0f;
    arg1->unk220 = 0.0f;
    arg1->unk20 = 0.0f;
    arg1->unk14 = 0.0f;
    arg1->unk1C = 1;
    arg1->unk78 = 0.0f;
    arg1->unk7C = 0.0f;
    arg1->unk1B4 = 6.0f;
    arg1->unk1B8 = 6.0f;
    arg1->unk22C = arg0;
    arg1->unk1A4 = 0.0f;
    arg1->unk224 = 1;
    arg1->unk1114 = 1;
    arg1->unk4 = 0xFFFF;
    arg1->unk6 = 0;
    arg1->unk148 = 0;
    arg1->unkF = 0;
    arg1->unk8 = 16.0f;
    arg1->unk1A0 = 0.1f;
    arg1->unk137C = 0;
    arg1->unk108.m[3][2] = 0.0f;
    arg1->unk1380 = 0.0f;
    arg1->unk1374 = 6.0f;
    arg1->unk1378 = 30.0f;
    uvMat4SetIdentity(&arg1->unk80);
    func_802D46A4(arg1, arg1->unk24, arg1->unk26, arg1->unk28, arg1->unk2A);
    func_802D45C4(arg1, 1);
    D_803599D0.unk0 = 6;
    D_803599D0.unk4 = 0.0f;
    D_803599D0.unk8 = 0.0f;
    D_803599D0.unkC = 5.0f;
    D_803599D0.unk10 = 5.0f;
    D_803599D0.unk14 = 10.0f;
    D_803599D0.unk18 = 9.0f;
    D_803599D0.unk1C = 15.0f;
    D_803599D0.unk20 = 12.0f;
    D_803599D0.unk24 = 20.0f;
    D_803599D0.unk28 = 13.5f;
    D_803599D0.unk2C = 25.0f;
    D_803599D0.unk30 = 14.5f;
}

void func_802D3444(Unk802D3658_Arg0* arg0) {
    Mtx4F sp28;

    arg0->unk14 += D_8034F854;
    if (arg0->unk1 != 5) {
        uvMat4Copy(&sp28, &arg0->unk80);
        uvMat4UnkOp2(&sp28, arg0->unk5C, arg0->unk60, arg0->unk64);
        func_802EAC18(arg0->unk230, arg0->unk14, &sp28);
        if (arg0->unkD != 0) {
            func_802EABAC(arg0->unk230, arg0->unk14, &sp28);
            arg0->unkD = 0;
        }
        arg0->unk1AC = uvAtan2F(arg0->unk80.m[0][0], arg0->unk80.m[0][1]) - 1.5707963f; // almost DEG_TO_RAD(90)
        if ((arg0->unk1AC - arg0->unk1A8) > 1.5707964f) {                               // matches DEG_TO_RAD(90)
            arg0->unk1A8 = arg0->unk1A8 + 6.2831855f;                                   // matches DEG_TO_RAD(360)
        }
        if ((arg0->unk1AC - arg0->unk1A8) < -1.5707964f) { // matches DEG_TO_RAD(-90)
            arg0->unk1A8 -= 6.2831855f;                    // matches DEG_TO_RAD(360)
        }
        if (arg0->unkC != 0) {
            arg0->unk1A8 = arg0->unk1AC;
            arg0->unkC = 0;
        } else {
            arg0->unk1A8 = func_80313AF4(arg0->unk1AC, arg0->unk1A8, arg0->unk1B8);
        }

        if (func_802D408C(arg0) != 0) {
            func_802D41D8(arg0);
            return;
        }

        switch (arg0->unk1) {
        case 9:
            func_802D3790(arg0);
            return;
        case 0:
            func_802D3BE8(arg0);
            return;
        case 1:
            func_802D3FA4(arg0);
            return;
        case 3:
            func_802D4274(arg0);
            return;
        case 4:
            func_802D532C(arg0);
            return;
        case 7:
            func_802D532C(arg0);
            return;
        case 6:
            func_802D3658(arg0);
            return;
        case 8:
            func_802D559C(arg0);
            break;
        }
    }
}

void func_802D3658(Unk802D3658_Arg0* arg0) {
    Mtx4F sp30;
    f32 temp_fa0;

    uvMat4UnkOp6(&sp30, &arg0->unk80, &arg0->unk108);
    uvMat4Copy(&arg0->unk108, &sp30);
    temp_fa0 = uvSqrtF(SQ(arg0->unk108.m[3][0] - arg0->unk80.m[3][0]) + SQ(arg0->unk108.m[3][1] - arg0->unk80.m[3][1]) +
                       SQ(arg0->unk108.m[3][2] - arg0->unk80.m[3][2])) -
               (2.0f * arg0->unk54);
    if (temp_fa0 < 0.0f) {
        arg0->unk108.m[3][0] += arg0->unk108.m[1][0] * temp_fa0;
        arg0->unk108.m[3][1] += arg0->unk108.m[1][1] * temp_fa0;
        arg0->unk108.m[3][2] += arg0->unk108.m[1][2] * temp_fa0;
        (void)func_802D472C(arg0, &arg0->unk108);
    }
    if (arg0->unk0 & 0x08) {
        (void)func_802D472C(arg0, &arg0->unk108);
    }
    if (arg0->unk0 & 0x20) {
        (void)func_802D4A30(arg0, &arg0->unk108);
    }
    if (arg0->unk0 & 0x40) {
        (void)func_802D4CA4(arg0, &arg0->unk108);
    }
}

void func_802D3790(Unk802D3658_Arg0* arg0) {
    Vec3F spBC;
    Vec3F spB0;
    Vec3F spA4;
    Vec3F sp98;
    Vec3F sp8C;
    Mtx4F sp4C;
    f32 temp_fv1_2;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 var_fv0;

    spBC.x = arg0->unk80.m[3][0];
    spBC.y = arg0->unk80.m[3][1];
    spBC.z = arg0->unk80.m[3][2];
    spB0.x = arg0->unkC0;
    spB0.y = 0.0f;
    spB0.z = 0.0f;
    func_8034B210(spBC, spB0, &sp4C);
    sp8C.x = 0.0f;
    sp8C.z = 0.0f;
    sp8C.y = -1.0f;
    func_8034ABB0(&sp4C, &sp98, &sp8C);
    func_8034B2B0(&sp98);
    if (arg0->unk137C == 0) {
        var_fv0 = arg0->unkC4 * 0.9f;
        if (arg0->unk1378 < var_fv0) {
            var_fv0 = arg0->unk1378;
        } else if (var_fv0 < -arg0->unk1378) {
            var_fv0 = -arg0->unk1378;
        }
        temp_fv1_2 = arg0->unk1380;
        if ((var_fv0 - temp_fv1_2) > 3.0f) {
            var_fv0 = temp_fv1_2 + 3.0f;
        } else if ((temp_fv1_2 - var_fv0) > 3.0f) {
            var_fv0 = temp_fv1_2 - 3.0f;
        }
        arg0->unk1380 = var_fv0;
        spA4.z = (-uvSinF(var_fv0 * 0.0174533f) * arg0->unk1374) + spBC.z; // almost DEG_TO_RAD(1)
        temp_fa1 = spA4.z - spBC.z;
        temp_fv0 = uvSqrtF(SQ(arg0->unk1374) + SQ(temp_fa1));
        spA4.x = (sp98.x * temp_fv0) + spBC.x;
        spA4.y = (sp98.y * temp_fv0) + spBC.y;
        sp98.x = spBC.x - spA4.x;
        sp98.y = spBC.y - spA4.y;
        sp98.z = spBC.z - spA4.z;
        func_8034B4DC(sp98, &arg0->unk108);
        arg0->unk108.m[3][0] = spA4.x;
        arg0->unk108.m[3][1] = spA4.y;
        arg0->unk108.m[3][2] = spA4.z;
        uvMat4RotateAxis(&arg0->unk108, arg0->unk78 * 0.5f, 'z');
        uvMat4RotateAxis(&arg0->unk108, arg0->unk7C * 0.5f, 'x');
        func_802D58EC(arg0, &arg0->unk108);
        if (arg0->unk0 & 0x08) {
            func_802D472C(arg0, &arg0->unk108);
        }
        if (arg0->unk0 & 0x20) {
            (void)func_802D4A30(arg0, &arg0->unk108);
        }
        if (arg0->unk0 & 0x40) {
            func_802D4CA4(arg0, &arg0->unk108);
        }
    } else if (arg0->unk137C == 1) {
        func_8034AD6C(arg0->unkC0, 0.0f, 0.0f, &arg0->unk108);
        arg0->unk108.m[3][0] = spBC.x;
        arg0->unk108.m[3][1] = spBC.y;
        arg0->unk108.m[3][2] = spBC.z;
        uvMat4UnkOp2(&arg0->unk108, arg0->unk68, arg0->unk6C, arg0->unk70);
        uvMat4RotateAxis(&arg0->unk108, arg0->unk78 * 0.5f, 'z');
        uvMat4RotateAxis(&arg0->unk108, arg0->unk7C * 0.5f, 'x');
    }

    temp_fv0 = uvSqrtF(SQ(arg0->unk108.m[0][0]) + SQ(arg0->unk108.m[0][1]) + SQ(arg0->unk108.m[0][2]));
    arg0->unk108.m[0][0] /= temp_fv0;
    arg0->unk108.m[0][1] /= temp_fv0;
    arg0->unk108.m[0][2] /= temp_fv0;

    temp_fv0 = uvSqrtF(SQ(arg0->unk108.m[1][0]) + SQ(arg0->unk108.m[1][1]) + SQ(arg0->unk108.m[1][2]));
    arg0->unk108.m[1][0] /= temp_fv0;
    arg0->unk108.m[1][1] /= temp_fv0;
    arg0->unk108.m[1][2] /= temp_fv0;

    temp_fv0 = uvSqrtF(SQ(arg0->unk108.m[2][0]) + SQ(arg0->unk108.m[2][1]) + SQ(arg0->unk108.m[2][2]));
    arg0->unk108.m[2][0] /= temp_fv0;
    arg0->unk108.m[2][1] /= temp_fv0;
    arg0->unk108.m[2][2] /= temp_fv0;
}

void func_802D3BE8(Unk802D3658_Arg0* arg0) {
    Mtx4F sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 temp_fv0;
    f32 temp_fv1;
    Vec3F sp40;
    f32 temp_ft4_2;
    f32 temp_ft5_2;

    func_802EAC9C(arg0->unk230, arg0->unk14 - arg0->unk48, &arg0->unkC8);
    sp40.x = arg0->unkC8.m[2][0] * 0.3f;
    sp40.y = arg0->unkC8.m[2][1] * 0.3f;
    sp40.z = (arg0->unkC8.m[2][2] * 0.3f) + 0.7f;
    uvVec3Normal(&sp40, &sp40);
    func_80313E18(&sp40, &arg0->unkC8);
    if (arg0->unk0 & 0x01) {
        sp5C = arg0->unkC8.m[3][0] - arg0->unk80.m[3][0];
        sp58 = arg0->unkC8.m[3][1] - arg0->unk80.m[3][1];
        sp54 = arg0->unkC8.m[3][2] - arg0->unk80.m[3][2];
        temp_fv0 = uvSqrtF(SQ(sp5C) + SQ(sp58) + SQ(sp54));
        if (temp_fv0 > 0.0f) {
            sp5C /= temp_fv0;
            sp58 /= temp_fv0;
            sp54 /= temp_fv0;
        }

        if (temp_fv0 < arg0->unk54) {
            temp_fv1 = arg0->unk54 - temp_fv0;
            arg0->unkC8.m[3][0] += temp_fv1 * sp5C;
            arg0->unkC8.m[3][1] += temp_fv1 * sp58;
            arg0->unkC8.m[3][2] += temp_fv1 * sp54;
        } else if (arg0->unk58 < temp_fv0) {
            temp_fv1 = temp_fv0 - arg0->unk58;
            arg0->unkC8.m[3][0] -= temp_fv1 * sp5C;
            arg0->unkC8.m[3][1] -= temp_fv1 * sp58;
            arg0->unkC8.m[3][2] -= temp_fv1 * sp54;
        }
    }

    if (arg0->unk0 & 0x02) {
        if (arg0->unk1A4 < 15.0f) {
            arg0->unkC8.m[3][2] += 4.0f * (1.0f - (FABS(arg0->unk1A4) / 15.0f));
        }
    }

    if (arg0->unk50 != 0.0f) {
        if (arg0->unk50 < 0.0f) {
            arg0->unk50 = 0.0f;
        } else if (arg0->unk50 > 1.0f) {
            arg0->unk50 = 1.0f;
        }

        sp5C = arg0->unkC8.m[3][0] - arg0->unk80.m[3][0];
        sp58 = arg0->unkC8.m[3][1] - arg0->unk80.m[3][1];
        sp54 = arg0->unkC8.m[3][2] - arg0->unk80.m[3][2];

        temp_ft4_2 = uvSqrtF((SQ(sp5C) + SQ(sp58)) + SQ(sp54));
        temp_ft5_2 = arg0->unkC8.m[3][2];
        arg0->unkC8.m[3][2] = (arg0->unk50 * ((temp_ft4_2 * 0.9659283f) + temp_ft5_2)) + ((1 - arg0->unk50) * temp_ft5_2);
    }

    uvMat4UnkOp6(&sp60, &arg0->unk80, &arg0->unkC8);
    func_802D58EC(arg0, &sp60);
    if (arg0->unk4C > 0.0f) {
        func_803138A0(&arg0->unk108, &arg0->unkC8, &sp60, arg0->unk4C);
    } else {
        uvMat4Copy(&arg0->unk108, &sp60);
    }
    uvMat4RotateAxis(&arg0->unk108, arg0->unk78 * 0.5f, 'z');
    uvMat4RotateAxis(&arg0->unk108, arg0->unk7C * 0.5f, 'x');
    if (func_802D472C(arg0, &arg0->unkC8) != 0) {
        uvMat4UnkOp6(&arg0->unk108, &arg0->unk80, &arg0->unkC8);
    }
}

void func_802D3FA4(Unk802D3658_Arg0* arg0) {
    Vec3F sp24;

    uvMat4Copy(&arg0->unk108, &arg0->unk80);
    uvMat4UnkOp2(&arg0->unk108, arg0->unk68, arg0->unk6C, arg0->unk70);
    uvMat4RotateAxis(&arg0->unk108, arg0->unk74, 'x');
    if (arg0->unk0 & 0x04) {
        sp24.x = arg0->unk108.m[2][0] * 0.2f;
        sp24.y = arg0->unk108.m[2][1] * 0.2f;
        sp24.z = (arg0->unk108.m[2][2] * 0.2f) + 0.8f;
        uvVec3Normal(&sp24, &sp24);
        func_80313E18(&sp24, &arg0->unk108);
    }
    uvMat4RotateAxis(&arg0->unk108, arg0->unk78, 'z');
    uvMat4RotateAxis(&arg0->unk108, arg0->unk7C, 'x');
    (void)func_802D4A30(arg0, &arg0->unk108);
}

s32 func_802D408C(Unk802D3658_Arg0* arg0) {
    f32 argX;
    f32 argY;
    f32 argZ;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 length;
    LevelOBSV* sp58;
    s32 i;
    u8 countOBSV;
    u8 tmp;

    argX = arg0->unk80.m[3][0];
    argY = arg0->unk80.m[3][1];
    argZ = arg0->unk80.m[3][2];
    arg0->unk18C = 1000000.0f;
    countOBSV = levelDataGetOBSV(&sp58) & 0xFF; // extra & 0xFF for matching

    for (i = 0; i < countOBSV; i++) {
        dx = sp58[i].x - argX;
        dy = sp58[i].y - argY;
        dz = sp58[i].z - argZ;
        length = uvLength3D(dx, dy, dz);
        if (length < sp58[i].unkC) {
            arg0->unk18C = length;
            break;
        }
    }
    if (i < countOBSV) {
        arg0->unk1 = 2;
        uvMat4SetIdentity(&arg0->unk14C);
        arg0->unk14C.m[3][0] = sp58[i].x;
        arg0->unk14C.m[3][1] = sp58[i].y;
        arg0->unk14C.m[3][2] = sp58[i].z;
        arg0->unk148 = 1;
        return 1;
    }
    arg0->unk148 = 0;
    return 0;
}

void func_802D41D8(Unk802D3658_Arg0* arg0) {
    f32 var_fv0;

    uvMat4UnkOp6(&arg0->unk108, &arg0->unk80, &arg0->unk14C);
    var_fv0 = (arg0->unk18C * 0.02f) + 0.5f;
    if (var_fv0 < 1.0f) {
        var_fv0 = 1.0f;
    } else if (var_fv0 > 4.0f) {
        var_fv0 = 4.0f;
    }
    func_802D45C4(arg0, var_fv0);
}

#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/nonmatchings/app/code_5A6A0/func_802D4274.s")
#else
// rom size changes when this gets compiled in, probably some .bss/.data mapping problem related to static var
void func_802D4274(Unk802D3658_Arg0* arg0) {
    static f32 D_80359A24;

    Mtx4F sp70; // 70:AF
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 var_fs0;

    if (arg0->unkE != 0) {
        arg0->unkE = 0;
        sp6C = arg0->unk108.m[3][0] - arg0->unk80.m[3][0];
        sp68 = arg0->unk108.m[3][1] - arg0->unk80.m[3][1];
        sp64 = arg0->unk108.m[3][2] - arg0->unk80.m[3][2];
        var_fs0 = uvSqrtF(SQ(sp6C) + SQ(sp68) + SQ(sp64));
        if (var_fs0 > 0.01f) {
            sp6C /= var_fs0;
            sp68 /= var_fs0;
            sp64 /= var_fs0;
            arg0->unk194 = func_8022A27C(sp68, sp6C);
            D_80359A24 = var_fs0;
        } else {
            arg0->unk194 = 0.0f;
            D_80359A24 = arg0->unk190;
        }
    } else {
        arg0->unk194 += arg0->unk19C * D_8034F854;
        D_80359A24 = func_80313AF4(arg0->unk190, D_80359A24, 1.0f);
    }
    uvMat4SetIdentity(&sp70);
    var_fs0 = arg0->unk198;

    while (var_fs0 <= 1.5706216f) { // should be DEG_TO_RAD(90)
        func_803134D0(D_80359A24, arg0->unk194, var_fs0, &sp6C, &sp68, &sp64);
        sp70.m[3][0] = arg0->unk80.m[3][0] + sp6C;
        sp70.m[3][1] = arg0->unk80.m[3][1] + sp68;
        sp70.m[3][2] = arg0->unk80.m[3][2] + sp64;

        if (func_802D472C(arg0, &sp70) == 0) {
            break;
        }
        if (var_fs0 == 1.5706216f) { // almost DEG_TO_RAD(90)
            break;
        }
        var_fs0 += 0.01745329f; // almost DEG_TO_RAD(1)
        if (var_fs0 < 0.0f) {
            var_fs0 = 0.0f;
        } else if (var_fs0 > 1.5706216f) { // almost DEG_TO_RAD(90)
            var_fs0 = 1.5706216f;          // almost DEG_TO_RAD(90)
        }
    }
    if (arg0->unk198 < var_fs0) {
        arg0->unk198 = var_fs0;
    }
    uvMat4UnkOp6(&arg0->unk108, &arg0->unk80, &sp70);
    (void)func_802D4A30(arg0, arg0->unk108.m);
}
#endif

void func_802D4514(Unk802D3658_Arg0* arg0) {
    f32 var_fv0;
    f32 temp;
    f32 temp3;
    f32 temp4;
    f32 temp2;
    Unk802D3658_Arg0* ptr;

    var_fv0 = (arg0->unk3C * 1.5f) / arg0->unk20;
    temp = (var_fv0 * 1.1f) * arg0->unk2C;
    temp2 = (var_fv0 * 1.1f) * arg0->unk30;
    temp3 = (var_fv0 * 1.1f) * arg0->unk34;
    temp4 = (var_fv0 * 1.1f) * arg0->unk38;

    ptr = arg0;
    ptr->unk111C = 2;
    arg0->unk1120[0].unk28.f[2] = 0.0f;
    arg0->unk1120[0].unk28.f[1] = ptr->unk3C * 1.5f;
    arg0->unk1120[0].unk28.f[0] = temp;
    arg0->unk1120[0].unk1C.f[1] = ptr->unk3C * 1.5f;
    arg0->unk1120[0].unk1C.f[0] = temp2;
    arg0->unk1120[0].unk1C.f[2] = 0.0f;
    arg0->unk1120[0].unk0 = 1;
    arg0->unk1120[1].unk28.f[2] = temp3;
    arg0->unk1120[1].unk28.f[1] = arg0->unk3C * 1.5f;
    arg0->unk1120[1].unk1C.f[1] = arg0->unk3C * 1.5f;
    arg0->unk1120[1].unk28.f[0] = 0.0f;
    arg0->unk1120[1].unk1C.f[0] = 0.0f;
    arg0->unk1120[1].unk1C.f[2] = temp4;
    arg0->unk1120[1].unk0 = 1;
}

void func_802D45C4(Unk802D3658_Arg0* arg0, f32 arg1) {
    f32 temp_fv0_2;
    f32 a;
    f32 b;
    f32 d;
    f32 sp34;
    f32 e;
    f32 c;

    if (arg1 != arg0->unk20) {
        if (arg1 == -1.0f) {
            arg1 = arg0->unk20;
        }
        temp_fv0_2 = arg0->unk3C / arg1;
        arg0->unk20 = arg1;
        arg0->unk1C = arg1;

        a = arg0->unk2C * temp_fv0_2;
        b = arg0->unk30 * temp_fv0_2;
        c = arg0->unk34 * temp_fv0_2;
        d = arg0->unk38 * temp_fv0_2;
        sp34 = arg0->unk3C;
        e = arg0->unk40;
        func_80204C94(arg0->unk22C, a, b, c, d, sp34, e);
        func_802D4514(arg0);
        D_8034E9E0 = sp34;
    }
}

void func_802D46A4(Unk802D3658_Arg0* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    s16 temp_a1;
    s16 temp_a2;
    s16 temp_a3;
    s16 temp_v0;

    arg0->unk24 = arg1;
    temp_a1 = arg0->unk24;
    arg0->unk26 = arg2;
    temp_a2 = arg0->unk26;
    arg0->unk28 = arg3;
    temp_a3 = arg0->unk28;
    arg0->unk2A = arg4;
    temp_v0 = arg0->unk2A;
    arg0->unk44 = ((temp_a2 - temp_a1) / (f32)(temp_v0 - temp_a3));
    func_80204D94(arg0->unk22C, temp_a1, temp_a2, temp_a3, (s32)temp_v0);
}

s32 func_802D472C(Unk802D3658_Arg0* arg0, Mtx4F* arg1) {
    f32 temp_fv0;
    f32 temp_fv1;
    Vec3F sp1B4;
    Vec3F sp1A8;
    s32 temp_v0;
    s32 i;
    Unk802D472C_SP60 sp60[5];
    f32 dx; // sp5C;
    f32 dy; // var_fs0;
    f32 dz; // var_fs1;
    s32 pad3;
    f32 sp4C;

    sp4C = 1.0f;

    pad3 = arg0->unk0;
    // this is weird
    if ((pad3 == 0) & 0x08) {
        return 0;
    }

    sp1A8.x = arg0->unk80.m[3][0];
    sp1A8.y = arg0->unk80.m[3][1];
    sp1A8.z = arg0->unk80.m[3][2];

    sp1B4.x = arg1->m[3][0];
    sp1B4.y = arg1->m[3][1];
    sp1B4.z = arg1->m[3][2];

    dx = sp1B4.x - sp1A8.x;
    dy = sp1B4.y - sp1A8.y;
    dz = sp1B4.z - sp1A8.z;
    temp_fv0 = uvSqrtF(SQ(dx) + SQ(dy) + SQ(dz));

    if (temp_fv0 > 0.0f) {
        dx /= temp_fv0;
        dy /= temp_fv0;
        dz /= temp_fv0;
    }
    if (arg0->unk0 & 0x10) {
        sp1A8.x += arg0->unk8 * dx;
        sp1A8.y += arg0->unk8 * dy;
        sp1A8.z += arg0->unk8 * dz;
    }
    temp_v0 = func_802DB224(&sp60[0].unk0, 0xD, arg0->unk4, arg0->unk6, &sp1A8, &sp1B4);
    if (temp_v0 == 0) {
        return 0;
    }

    for (i = 0; i < temp_v0; i++) {
        if (sp60[i].unk1C < sp4C) {
            sp4C = sp60[i].unk1C;
        }
    }

    if (sp4C != 1.0f) {
        dx = (sp1B4.x - sp1A8.x) * sp4C;
        dy = (sp1B4.y - sp1A8.y) * sp4C;
        dz = (sp1B4.z - sp1A8.z) * sp4C;
        temp_fv0 = uvSqrtF(SQ(dx) + SQ(dy) + SQ(dz));
        if (arg0->unk1A0 < temp_fv0) {
            temp_fv1 = temp_fv0 - arg0->unk1A0;
            dx /= temp_fv0;
            dx *= temp_fv1;
            arg1->m[3][0] = sp1A8.x + dx;
            dy /= temp_fv0;
            dy *= temp_fv1;
            arg1->m[3][1] = sp1A8.y + dy;
            dz /= temp_fv0;
            dz *= temp_fv1;
            arg1->m[3][2] = sp1A8.z + dz;
        }
    }
    return 1;
}

s32 func_802D4A30(Unk802D3658_Arg0* arg0, Mtx4F* arg1) {
    s32 sp2A4;
    u8 pad[0x144];
    Unk802D3658_Unk1120* temp_s2;
    Unk802D3658_Unk1228* var_s3;
    s32 sp154;
    Vec3F sp148;
    Vec3F sp13C;
    Vec3F sp130;
    Mtx4F spF0; // F0:12F
    Mtx4F spB0; // B0:EF
    Mtx4F sp70; // 70:AF
    s32 i;

    sp2A4 = func_802DB050(&arg0->unk111C, &arg0->unk1224, arg0->unk4, arg0->unk6, arg1);
    if (sp2A4 == 0) {
        return 0;
    }
    uvMat4Copy(&spF0, arg1);
    spF0.m[3][1] = 0.0f;
    spF0.m[3][0] = 0.0f;
    spF0.m[3][2] = 0.0f;
    uvMat4UnkOp4(&spB0, &spF0);

    for (i = 0; i < sp2A4; i++) {
        var_s3 = &arg0->unk1228[i];
        temp_s2 = &arg0->unk1120[var_s3->unk0];
        func_802DBE64(&arg0->unk111C, &arg0->unk1224, i, &spB0);
        func_802DCA5C(&temp_s2->unk28, &temp_s2->unk1C, &var_s3->unk28, &var_s3->unk34, &sp148);
        sp13C.x = arg1->m[3][0] + (arg1->m[1][0] * 1.5f * arg0->unk3C);
        sp13C.y = arg1->m[3][1] + (arg1->m[1][1] * 1.5f * arg0->unk3C);
        sp13C.z = arg1->m[3][2] + (arg1->m[1][2] * 1.5f * arg0->unk3C);
        uvMat4Copy(&sp70, arg1);
        uvMat4UnkOp2(&sp70, sp148.x, sp148.y, sp148.z);
        sp130.x = sp70.m[3][0] + (arg1->m[1][0] * 1.5f * arg0->unk3C);
        sp130.y = sp70.m[3][1] + (arg1->m[1][1] * 1.5f * arg0->unk3C);
        sp130.z = sp70.m[3][2] + (arg1->m[1][2] * 1.5f * arg0->unk3C);
        (void)func_802DB224(&sp154, 9, arg0->unk4, arg0->unk6, &sp13C, &sp130);
        if (sp154 > 0) {
            return -1;
        }
        uvMat4UnkOp2(arg1, sp148.x, sp148.y, sp148.z);
    }

    return 1;
}

s32 func_802D4CA4(Unk802D3658_Arg0* arg0, Mtx4F* arg1) {
    Mtx4F sp30;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv1;

    if ((D_8034F850 - arg0->unk18) > 0.5f) {
        temp_fv0 = arg1->m[3][0] - arg0->unk80.m[3][0];
        temp_fv1 = arg1->m[3][1] - arg0->unk80.m[3][1];
        temp_fa1 = arg1->m[3][2] - arg0->unk80.m[3][2];
        if (arg0->unk8 < uvSqrtF(SQ(temp_fv0) + SQ(temp_fv1) + SQ(temp_fa1))) {
            return 0;
        }
        arg0->unk18 = D_8034F850;
    }
    uvMat4SetIdentity(&sp30);
    sp30.m[3][0] = arg0->unk80.m[3][0] + (arg0->unk80.m[1][0] * (4.0f * arg0->unk8));
    sp30.m[3][1] = arg0->unk80.m[3][1] + (arg0->unk80.m[1][1] * (4.0f * arg0->unk8));
    sp30.m[3][2] = arg0->unk80.m[3][2] + (arg0->unk80.m[1][2] * (4.0f * arg0->unk8));
    uvMat4UnkOp6(arg1, &arg0->unk80, &sp30);
    (void)func_802D472C(arg0, arg1);
    return 1;
}

void func_802D4DE8(Unk802D3658_Arg0* arg0, u8 arg1) {
    Mtx4F sp20;
    if (!arg1) {
        arg0->unk148 = 0;
        arg0->unkC = 1;
        arg0->unkD = 1;
        arg0->unk50 = 0.0f;
        arg0->unk21C = 0.0f;
        arg0->unk220 = 0.0f;
        arg0->unk200 = 0.0f;
        arg0->unk204.x = 0.0f;
        arg0->unk204.y = 0.0f;
        arg0->unk204.z = 0.0f;
        arg0->unk2 = arg0->unk1;
        arg0->unk18 = -1.0f;
        arg0->unk1A0 = 0.1f;
        arg0->unk1FC = -100.0f;
        uvMat4Copy(&sp20, &arg0->unk80);
        uvMat4UnkOp2(&sp20, arg0->unk5C, arg0->unk60, arg0->unk64);
        func_802EABAC(arg0->unk230, 0.0f, &sp20);
        uvMat4Copy(&sp20, &arg0->unk1BC);
        arg0->unk1114 = 1;
        arg0->unkF++;
    }
}

void func_802D4ECC(Unk802D3658_Arg0* arg0, Mtx4F* arg1) {
    f32 z;
    f32 x;
    f32 y;
    s32 i;
    Unk802D3658_Unk230* arr;

    x = arg1->m[3][0] - arg0->unk80.m[3][0];
    y = arg1->m[3][1] - arg0->unk80.m[3][1];
    z = arg1->m[3][2] - arg0->unk80.m[3][2];

    arr = arg0->unk230;
    for (i = 0; i < ARRAY_COUNT(arg0->unk230); i++) {
        arr[i].unk0.m[3][0] += x;
        arr[i].unk0.m[3][1] += y;
        arr[i].unk0.m[3][2] += z;
    }

    arg0->unkC8.m[3][0] += x;
    arg0->unkC8.m[3][1] += y;
    arg0->unkC8.m[3][2] += z;

    uvMat4Copy(&arg0->unk80, arg1);
}

void func_802D50D0(Unk802D3658_Arg0* arg0) {
    f32 var_fv1;
    f32 var_ft4;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_4;
    f32 a, b, c, d, e;
    f32 temp_fv1;

    var_ft4 = 3.0f;
    if ((arg0->unk1 == 5) || (D_80362690->unk0[0].unk0 != 5)) {
        if (D_8034E9E4 != 0) {
            temp_fv0 = 1.0f / arg0->unk20;
            a = arg0->unk2C * temp_fv0;
            b = arg0->unk30 * temp_fv0;
            c = arg0->unk34 * temp_fv0;
            d = arg0->unk38 * temp_fv0;
            e = arg0->unk40;
            func_80204C94(arg0->unk22C, a, b, c, d, 1.0f, e);
            D_8034E9E0 = 1.0f;
            D_8034E9E4 = 0;
        }
    } else {
        if ((D_80362690->unk0[0].unk6 == 2) || (D_80362690->unk0[0].unk6 == 8)) {
            var_ft4 = 1.0f;
        }
        if (arg0->unk1 == 1) {
            var_fv1 = 3.0f;
        } else if (arg0->unk1 == 3) {
            var_fv1 = 0.5f;
        } else {
            temp_fv0_2 = arg0->unk108.m[3][0] - arg0->unk80.m[3][0];
            temp_fv1 = arg0->unk108.m[3][1] - arg0->unk80.m[3][1];
            temp_fa1 = arg0->unk108.m[3][2] - arg0->unk80.m[3][2];
            var_fv1 = uvSqrtF(SQ(temp_fv0_2) + SQ(temp_fv1) + SQ(temp_fa1)) - arg0->unk8;
        }
        if (arg0->unk228 < var_fv1) {
            var_fv1 = arg0->unk228;
        }
        if (var_ft4 < var_fv1) {
            var_fv1 = var_ft4;
        }
        if (var_fv1 < 0.5f) {
            var_fv1 = 0.5f;
        }
        if (!(var_fv1 < (D_8034E9E0 + 0.1f)) || !((D_8034E9E0 - 0.1f) < var_fv1)) {
            temp_fv0_4 = var_fv1 / arg0->unk20;
            a = arg0->unk2C * temp_fv0_4;
            b = arg0->unk30 * temp_fv0_4;
            c = arg0->unk34 * temp_fv0_4;
            d = arg0->unk38 * temp_fv0_4;
            e = arg0->unk40;
            func_80204C94(arg0->unk22C, a, b, c, d, var_fv1, e);
            D_8034E9E0 = var_fv1;
            D_8034E9E4 = 1;
        }
    }
}

// func_802D532C does not initialize sp30, sp34, sp38
#if defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsometimes-uninitialized"
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif
void func_802D532C(Unk802D3658_Arg0* arg0) {
    Mtx4F sp80; // 80:BF
    Mtx4F sp40; // 40:7F
    f32 var_fa0;
    s32 sp38;
    s32 sp34;
    s32 sp30;
    f32 var_fa0_2;

    uvMat4SetIdentity(&sp80);
    sp80.m[3][0] = arg0->unk80.m[3][0];
    sp80.m[3][1] = arg0->unk80.m[3][1];
    sp80.m[3][2] = arg0->unk80.m[3][2];
    if (arg0->unk1AC < arg0->unk1A8) {
        var_fa0 = arg0->unk1A8 - arg0->unk1AC;
    } else {
        var_fa0 = -(arg0->unk1A8 - arg0->unk1AC);
    }
    if (var_fa0 < 0.005f) {
        var_fa0_2 = arg0->unk1AC;
    } else {
        var_fa0_2 = arg0->unk1A8;
    }
    uvMat4RotateAxis(&sp80, -var_fa0_2, 'z');
    uvMat4RotateAxis(&sp80, -arg0->unk1B0, 'x');
    uvMat4UnkOp2(&sp80, 0.0f, -arg0->unk1B4, 0.0f);
    if (arg0->unk0 & 0x08) {
        sp38 = func_802D472C(arg0, &sp80);
    }
    if (arg0->unk0 & 0x20) {
        sp34 = func_802D4A30(arg0, &sp80);
    }
    if ((arg0->unk0 & 0x40) && (sp34 != -1)) {
        sp30 = func_802D4CA4(arg0, &sp80);
    }
    if (sp34 == -1) {
        arg0->unk1FC = D_8034F850;
    }
    if ((D_8034F850 - arg0->unk1FC) < 2.0f) {
        uvMat4Copy(&sp80, &arg0->unk1BC);
    }
    if ((sp38 == 0) && (sp34 == 0) && (sp30 == 0)) {
        uvMat4Copy(&arg0->unk1BC, &sp80);
    }
    if (arg0->unk1 == 7) {
        uvMat4Copy(&sp40, &arg0->unk80);
        sp40.m[3][0] = arg0->unk1368;
        sp40.m[3][1] = arg0->unk136C;
        sp40.m[3][2] = arg0->unk1370;
        uvMat4UnkOp6(&arg0->unk108, &sp40, &sp80);
    } else {
        uvMat4UnkOp6(&arg0->unk108, &arg0->unk80, &sp80);
    }
    uvMat4RotateAxis(&arg0->unk108, arg0->unk78 * 0.5f, 'z');
    uvMat4RotateAxis(&arg0->unk108, arg0->unk7C * 0.5f, 'x');
    func_802D58EC(arg0, &arg0->unk108);
}
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif

void func_802D559C(Unk802D3658_Arg0* arg0) {
    Mtx4F sp48; // 48:87
    f32 temp_fa0;
    f32 temp_fa0_2;
    f32 temp_fv0;
    f32 tmpX;
    f32 tmpY;
    f32 tmpZ;
    s32 temp_v0;

    if ((D_8034F850 - arg0->unk200) > 3.0f) {
        temp_fv0 = uvVec3Len(&arg0->unk204);
        if (temp_fv0 > 0.0f) {
            temp_fa0 = (temp_fv0 * 0.5f) * 3.0f;
            if (temp_fa0 < 10.0f) {
                temp_fa0 = 10.0f;
            } else if (temp_fa0 > 500.0f) {
                temp_fa0 = 500.0f;
            }
            arg0->unk210.x = arg0->unk80.m[3][0] + ((arg0->unk204.x / temp_fv0) * temp_fa0);
            arg0->unk210.y = arg0->unk80.m[3][1] + ((arg0->unk204.y / temp_fv0) * temp_fa0);
            arg0->unk210.z = arg0->unk80.m[3][2] + ((arg0->unk204.z / temp_fv0) * temp_fa0);
            if (demoRandF() > 0.5f) {
                arg0->unk210.x += 2.0f * arg0->unk80.m[0][0];
                arg0->unk210.y += 2.0f * arg0->unk80.m[0][1];
            } else {
                arg0->unk210.x -= 2.0f * arg0->unk80.m[0][0];
                arg0->unk210.y -= 2.0f * arg0->unk80.m[0][1];
            }
            arg0->unk200 = D_8034F850;
        } else {
            arg0->unk210.x = arg0->unk80.m[3][0] + (arg0->unk108.m[1][0] * 10.0f);
            arg0->unk210.y = arg0->unk80.m[3][1] + (arg0->unk108.m[1][1] * 10.0f);
            arg0->unk210.z = arg0->unk80.m[3][2] + (arg0->unk108.m[1][2] * 10.0f);
        }
    }
    uvMat4SetIdentity(&sp48);
    sp48.m[3][0] = arg0->unk210.x;
    sp48.m[3][1] = arg0->unk210.y;
    sp48.m[3][2] = arg0->unk210.z;
    tmpX = sp48.m[3][0] - arg0->unk80.m[3][0];
    tmpY = sp48.m[3][1] - arg0->unk80.m[3][1];
    tmpZ = sp48.m[3][2] - arg0->unk80.m[3][2];
    temp_fa0_2 = uvSqrtF(SQ(tmpX) + SQ(tmpY) + SQ(tmpZ));
    temp_fa0_2 = 0.02f * temp_fa0_2 + 0.5f;
    if (temp_fa0_2 < 1.0f) {
        temp_fa0_2 = 1.0f;
    } else if (temp_fa0_2 > 4.0f) {
        temp_fa0_2 = 4.0f;
    }
    func_802D45C4(arg0, temp_fa0_2);
    uvMat4UnkOp6(&arg0->unk108, &arg0->unk80, &sp48);
    temp_v0 = func_802D472C(arg0, &sp48);
    if (temp_v0 != 0) {
        arg0->unk210.z += 2.0f;
        sp48.m[3][2] += 2.0f;
        uvMat4UnkOp6(&arg0->unk108, &arg0->unk80, &sp48);
    }
}

void func_802D5884(Unk802D3658_Arg0* arg0, u8 arg1) {
    if (arg1 != arg0->unk1) {
        arg0->unk2 = arg0->unk1;
        arg0->unk1 = arg1;
        if (arg1 == 3) {
            arg0->unk198 = 0.52359873f; // almost DEG_TO_RAD(30)
            arg0->unk194 = uvAtan2F(arg0->unk80.m[0][0], arg0->unk80.m[0][1]);
            arg0->unkE = 1;
        }
    }
}

void func_802D58EC(Unk802D3658_Arg0* arg0, Mtx4F* arg1) {
    Mtx4F sp88; // 88:C7
    Mtx4F sp48; // 48:87
    Vec3F sp3C;
    Vec3F sp30;
    f32 var_fa0;

    func_802E1754(arg1->m[3][0], arg1->m[3][1], arg1->m[3][2], &sp3C);
    uvMat4Copy(&sp88, arg1);
    sp88.m[3][0] = sp88.m[3][1] = sp88.m[3][2] = 0.0f;

    uvMat4UnkOp4(&sp48, &sp88);
    uvMat4UnkOp5(&sp48, &sp30, &sp3C);

    var_fa0 = func_80313F08(&D_803599D0, FABS(2.5f * sp30.x)) * arg0->unk224;
    if (sp30.x < 0.0f) {
        var_fa0 = -var_fa0;
    }
    arg0->unk21C = func_80313AF4(var_fa0, arg0->unk21C, 1.0f);
    uvMat4RotateAxis(arg1, arg0->unk21C * 0.01745329f, 'z'); // almost DEG_TO_RAD(1)

    var_fa0 = func_80313F08(&D_803599D0, FABS(2.5f * sp30.z)) * (arg0->unk224 * 0.5f);
    if (sp30.z > 0.0f) {
        var_fa0 = -var_fa0;
    }
    arg0->unk220 = func_80313AF4(var_fa0, arg0->unk220, 1.0f);
    uvMat4RotateAxis(arg1, arg0->unk220 * 0.01745329f, 'x'); // almost DEG_TO_RAD(1)
}
