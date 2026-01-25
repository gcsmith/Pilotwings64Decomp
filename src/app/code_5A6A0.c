#include "common.h"
#include "uv_matrix.h"

extern f32 D_8034F854;

typedef struct Unk802D3658_Unk230 {
    MtxF unk0;
    f32 unk40;
    struct Unk802D3658_Unk230* unk44;
    u8 unk48[4];
} Unk802D3658_Unk230;

typedef struct {
    s32 unk0;
    u8 pad4[0x18];
    Vec3F_t unk1C;
    Vec3F_t unk28;
} Unk802D3658_Unk1120;

typedef struct {
    s32 unk0;
    u8 pad4[0x24];
    Vec3F_t unk28;
    Vec3F_t unk34;
} Unk802D3658_Unk1228;

typedef struct {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u16 unk4;
    u8 unk6;
    u8 pad7;
    f32 unk8;
    u8 unkC;
    u8 unkD;
    u8 unkE;
    u8 unkF;
    u8 pad10[0x14 - 0x10];
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    s16 unk24;
    s16 unk26;
    s16 unk28;
    s16 unk2A;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    f32 unk40;
    f32 unk44;
    f32 unk48;
    f32 unk4C;
    f32 unk50;
    f32 unk54;
    f32 unk58;
    f32 unk5C;
    f32 unk60;
    f32 unk64;
    f32 unk68;
    f32 unk6C;
    f32 unk70;
    f32 unk74;
    f32 unk78;
    f32 unk7C;
    MtxF unk80; //  80: BF
    u8 unkC0[0xC8 - 0xC0];
    MtxF unkC8; //  C8:107
    MtxF unk108; // 108:147
    u8 unk148;
    u8 pad149[3];
    MtxF unk14C; // 14C:18B
    f32 unk18C;
    f32 unk190;
    f32 unk194;
    f32 unk198;
    f32 unk19C;
    f32 unk1A0;
    f32 unk1A4;
    f32 unk1A8;
    f32 unk1AC;
    f32 unk1B0;
    f32 unk1B4;
    u8 pad1B8[0x1BC - 0x1B8];
    MtxF unk1BC; // 1BC:1FB
    f32 unk1FC;
    f32 unk200;
    f32 unk204;
    f32 unk208;
    f32 unk20C;
    u8 pad210[0xC];
    f32 unk21C;
    f32 unk220;
    f32 unk224;
    f32 unk228;
    u8 unk22C;
    u8 pad22D[0x230 - 0x22D];
    Unk802D3658_Unk230 unk230[50]; // 230:1107
    u8 pad1108[0x1114 - 0x1108];
    u8 unk1114;
    u8 pad1115[0x111C - 0x1115];

    s32 unk111C;
    Unk802D3658_Unk1120 unk1120[5]; // 1120:1223

    s32 unk1224;
    Unk802D3658_Unk1228 unk1228[5]; // 1228:1367

    f32 unk1368;
    f32 unk136C;
    f32 unk1370;
} Unk802D3658_Arg0;

f32 func_8022A27C(f32, f32);
f32 func_80313AF4(f32, f32, f32);
s32 func_802D472C(Unk802D3658_Arg0*, Mtx4F_t);
void func_80229AA0(Mtx4F_t arg0, Mtx4F_t arg1, Mtx4F_t arg2);
s32 func_802D4A30(Unk802D3658_Arg0*, Mtx4F_t);

void func_803134D0(f32, f32, f32, f32*, f32*, f32*);

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_5A6A0/func_802D3170.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_5A6A0/func_802D3444.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_5A6A0/func_802D3658.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_5A6A0/func_802D3790.s")

#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/nonmatchings/app/code_5A6A0/func_802D3BE8.s")
#else
// rom size changes when this gets compiled in, probably some .bss/.data mapping problem
void func_802D3BE8(Unk802D3658_Arg0* arg0) {
    MtxF sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 temp_fv0;
    f32 temp_fv1;
    Vec3F_t sp40;
    f32 temp_ft4_2;
    f32 temp_ft5_2;

    func_802EAC9C(arg0->unk230, arg0->unk14 - arg0->unk48, arg0->unkC8.mf);
    sp40.x = arg0->unkC8.mf[2][0] * 0.3f;
    sp40.y = arg0->unkC8.mf[2][1] * 0.3f;
    sp40.z = (arg0->unkC8.mf[2][2] * 0.3f) + 0.7f;
    uvVec3Normal(&sp40, &sp40);
    func_80313E18(&sp40, arg0->unkC8.mf);
    if (arg0->unk0 & 0x01) {
        sp5C = arg0->unkC8.mf[3][0] - arg0->unk80.mf[3][0];
        sp58 = arg0->unkC8.mf[3][1] - arg0->unk80.mf[3][1];
        sp54 = arg0->unkC8.mf[3][2] - arg0->unk80.mf[3][2];
        temp_fv0 = SqrtF(SQ(sp5C) + SQ(sp58) + SQ(sp54));
        if (temp_fv0 > 0.0f) {
            sp5C /= temp_fv0;
            sp58 /= temp_fv0;
            sp54 /= temp_fv0;
        }

        if (temp_fv0 < arg0->unk54) {
            temp_fv1 = arg0->unk54 - temp_fv0;
            arg0->unkC8.mf[3][0] += temp_fv1 * sp5C;
            arg0->unkC8.mf[3][1] += temp_fv1 * sp58;
            arg0->unkC8.mf[3][2] += temp_fv1 * sp54;
        } else if (arg0->unk58 < temp_fv0) {
            temp_fv1 = temp_fv0 - arg0->unk58;
            arg0->unkC8.mf[3][0] -= temp_fv1 * sp5C;
            arg0->unkC8.mf[3][1] -= temp_fv1 * sp58;
            arg0->unkC8.mf[3][2] -= temp_fv1 * sp54;
        }
    }
    if (arg0->unk0 & 0x02) {
        if (arg0->unk1A4 < 15.0f) {
            arg0->unkC8.mf[3][2] += 4.0f * (1.0f - (FABS(arg0->unk1A4) / 15.0f));
        }
    }

    if (arg0->unk50 != 0.0f) {
        if (arg0->unk50 < 0.0f) {
            arg0->unk50 = 0.0f;
        } else if (arg0->unk50 > 1.0f) {
            arg0->unk50 = 1.0f;
        }
        
        sp5C = arg0->unkC8.mf[3][0] - arg0->unk80.mf[3][0];
        sp58 = arg0->unkC8.mf[3][1] - arg0->unk80.mf[3][1];
        sp54 = arg0->unkC8.mf[3][2] - arg0->unk80.mf[3][2];

        temp_ft4_2 = SqrtF((SQ(sp5C) + SQ(sp58)) + SQ(sp54));
        temp_ft5_2 = arg0->unkC8.mf[3][2];
        arg0->unkC8.mf[3][2] = (arg0->unk50 * ((temp_ft4_2 * 0.9659283f) + temp_ft5_2)) + ((1 - arg0->unk50) * temp_ft5_2);
    }

    func_80229AA0(sp60.mf, arg0->unk80.mf, arg0->unkC8.mf);
    func_802D58EC(arg0, sp60.mf);
    if (arg0->unk4C > 0.0f) {
        func_803138A0(&arg0->unk108, arg0->unkC8.mf, sp60.mf, arg0->unk4C);
    } else {
        uvMat4Copy(arg0->unk108.mf, sp60.mf);
    }
    uvMat4RotateAxis(arg0->unk108.mf, arg0->unk78 * 0.5f, 'z');
    uvMat4RotateAxis(arg0->unk108.mf, arg0->unk7C * 0.5f, 'x');
    if (func_802D472C(arg0, arg0->unkC8.mf) != 0) {
        func_80229AA0(arg0->unk108.mf, arg0->unk80.mf, arg0->unkC8.mf);
    }
}
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_5A6A0/func_802D3FA4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_5A6A0/func_802D408C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_5A6A0/func_802D41D8.s")

#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/nonmatchings/app/code_5A6A0/func_802D4274.s")
#else
// rom size changes when this gets compiled in, probably some .bss/.data mapping problem
void func_802D4274(Unk802D3658_Arg0* arg0) {
    static f32 D_80359A24;

    MtxF sp70; // 70:AF
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 var_fs0;

    if (arg0->unkE != 0) {
        arg0->unkE = 0;
        sp6C = arg0->unk108.mf[3][0] - arg0->unk80.mf[3][0];
        sp68 = arg0->unk108.mf[3][1] - arg0->unk80.mf[3][1];
        sp64 = arg0->unk108.mf[3][2] - arg0->unk80.mf[3][2];
        var_fs0 = SqrtF(SQ(sp6C) + SQ(sp68) + SQ(sp64));
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
    uvMat4SetIdentity(sp70.mf);
    var_fs0 = arg0->unk198;

    while (var_fs0 <= 1.5706216f) { // should be DEG_TO_RAD(90)
        func_803134D0(D_80359A24, arg0->unk194, var_fs0, &sp6C, &sp68, &sp64);
        sp70.mf[3][0] = arg0->unk80.mf[3][0] + sp6C;
        sp70.mf[3][1] = arg0->unk80.mf[3][1] + sp68;
        sp70.mf[3][2] = arg0->unk80.mf[3][2] + sp64;

        if (func_802D472C(arg0, sp70.mf) == 0) {
            break;
        }
        if (var_fs0 == 1.5706216f) {
            break;
        }
        var_fs0 += 0.01745329f; // should be DEG_TO_RAD(10)
        if (var_fs0 < 0.0f) {
            var_fs0 = 0.0f;
        } else if (var_fs0 > 1.5706216f) {
            var_fs0 = 1.5706216f;
        }
    }
    if (arg0->unk198 < var_fs0) {
        arg0->unk198 = var_fs0;
    }
    func_80229AA0(arg0->unk108.mf, arg0->unk80.mf, sp70.mf);
    func_802D4A30(arg0, arg0->unk108.mf);
}
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_5A6A0/func_802D4514.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_5A6A0/func_802D45C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_5A6A0/func_802D46A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_5A6A0/func_802D472C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_5A6A0/func_802D4A30.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_5A6A0/func_802D4CA4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_5A6A0/func_802D4DE8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_5A6A0/func_802D4ECC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_5A6A0/func_802D50D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_5A6A0/func_802D532C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_5A6A0/func_802D559C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_5A6A0/func_802D5884.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_5A6A0/func_802D58EC.s")
