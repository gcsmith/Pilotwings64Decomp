#include "common.h"
#include <uv_dobj.h>
#include <uv_janim.h>
#include <uv_level.h>
#include <uv_math.h>
#include <uv_matrix.h>
#include <uv_model.h>
#include <uv_sobj.h>
#include "kernel/code_8170.h"
#include "app/balls.h"
#include "app/demo.h"
#include "app/hud.h"
#include "app/save.h"
#include "app/shadow.h"
#include "app/snd.h"
#include "app/splash.h"
#include "app/code_61A60.h"
#include "app/code_66160.h"
#include "app/code_D1ED0.h"

typedef struct Unk80362690_Unk0_UnkC_Unk6C_Unk18 {
    u8 pad0[0x138];
    Vec3F unk138;
} Unk80362690_Unk0_UnkC_Unk6C_Unk18;

typedef struct Unk80362690_Unk0_UnkC_Unk6C {
    u16 unk0;
    u8 pad2[0xE];
    f32 unk10;
    f32 unk14;
    Unk80362690_Unk0_UnkC_Unk6C_Unk18* unk18;
    f32 unk1C;
    u8 pad20[0x4];
    f32 unk24;
    f32 unk28;
    u8 pad2C[0x4];
    Vec3F unk30;
    u8 unk3C[0x10];
    u8 unk4C;
    u8 unk4D;
    u8 pad4E[0x1];
    u8 unk4F;
    u8 unk50;
    u8 pad51[0xF];
    s32 unk60;
    f32 unk64;
    f32 unk68;
    f32 unk6C;
    f32 unk70;
    Mtx4F unk74;
    Mtx4F unkB4;
    Vec3F unkF4;
    Vec3F unk100;
    Vec3F unk10C;
    Vec3F unk118;
    Vec3F unk124;
    f32 unk130;
    Vec3F unk134;
    Vec3F unk140;
    Vec3F unk14C;
    u8 pad158[0x4];
    Vec3F unk15C;
    Vec3F unk168;
    Vec3F unk174;
    u8 pad180[0x4];
    Vec3F unk184;
    f32 unk190;
    f32 unk194;
    s32 unk198;
    s32 unk19C;
    u8 pad1A0[0x18];
    f64 unk1B8;
    f64 unk1C0;
    f64 unk1C8;
    u8 pad1D0[0x1B4];
    Unk80371120 unk384;
    s32 unk534;
    u8 pad538[0x4];
    f32 unk53C;
    f32 unk540;
    f32 unk544;
    f32 unk548;
    f32 unk54C;
    f32 unk550;
    f32 unk554;
    f32 unk558;
    u8 unk55C;
    f32 unk560;
    f32 unk564;
    f32 unk568;
    u8 unk56C;
    f32 unk570;
    f32 unk574;
    f32 unk578;
    u8 unk57C;
    f32 unk580;
    f32 unk584;
    f32 unk588;
    u8 unk58C;
    f32 unk590;
    f32 unk594;
    f32 unk598;
    u8 pad58C[0x4];
    f32 unk5A0;
    u8 pad5A4[0x4];
    f32 unk5A8;
    u8 pad5AC[0x4];
    f32 unk5B0;
    u8 pad5B4[0x4];
    f32 unk5B8;
    u8 pad5BC[0x4];
    f32 unk5C0;
    f32 unk5C4;
    u8 pad5C8[0x4];
    f32 unk5CC;
    u8 pad5D0[0x4];
    f32 unk5D4;
    f32 unk5D8;
    u8 pad5DC[0x4];
    f32 unk5E0;
    u16 unk5E4;
    Vec3F unk5E8;
    u8 pad5F4[0xC];
    Vec3F unk600;
    Vec3F unk60C;
    Vec3F unk618;
    Vec3F unk624;
    u8 pad630[0xC];
    f32 unk63C;
    f32 unk640;
    f32 unk644;
    f32 unk648;
    u8 pad64C[0x4];
    u8 unk650;
    u8 unk651;
    u8 unk652;
    u8 unk653;
    u8 unk654;
    u8 unk655;
    u8 unk656;
    u8 unk657;
    u8 unk658;
    u8 unk659;
    u8 unk65A;
    u8 unk65B;
    u8 unk65C;
    u8 unk65D;
    u8 unk65E[0x12];
    Vec3F unk670;
    s32 unk67C;
} Unk80362690_Unk0_UnkC_Unk6C;

extern Unk802D3658_Unk111C D_80368C00;
extern Unk802D3658_Unk111C D_80368D08;
extern Unk802D3658_Unk111C D_80368E10;
extern Unk802D3658_Unk1224 D_80368F18;

void func_802FD114(Unk80362690_Unk0_UnkC_Unk6C* arg0);

f32 func_802FB660(Unk80362690_Unk0_UnkC_Unk6C* arg0) {
    f32 sp34;
    f32 sp30;
    f32 sp2C;

    sp34 = MIN(arg0->unk5CC, arg0->unk5D4) + arg0->unk140.y;

    sp30 = (180.0f - sp34) - (180.0f + arg0->unk5C0);
    sp2C = (90.0f - sp30) + arg0->unk5D8;

    arg0->unk6C = (uvCosF(arg0->unk140.y * 0.01745329f) * arg0->unk63C) + (uvCosF(sp34 * 0.01745329f) * arg0->unk640) + (uvCosF(sp30 * 0.01745329f) * arg0->unk644) + (uvCosF(sp2C * 0.01745329f) * arg0->unk648);

    return arg0->unk6C;
}

s32 func_802FB784(Unk80362690_Unk0_UnkC_Unk6C* arg0, f32 arg1) {
    f32 temp_fv0;
    f32 temp_fv1;

    temp_fv0 = uvSqrtF(SQ(arg0->unk168.x) + SQ(arg0->unk168.y) + SQ(arg0->unk168.z));
    if (temp_fv0 > 0.0001f) {
        temp_fv1 = arg0->unk168.z / temp_fv0;
    } else {
        return 0;
    }

    if (FABS(temp_fv1) < arg1) {
        return 1;
    }
    return 0;
}

void func_802FB82C(Unk80362690_Unk0_UnkC_Unk6C* arg0) {
    if (arg0->unk50 == 0) {
        arg0->unk50 = 1;
        arg0->unk4F = 0;
    }
}

void func_802FB84C(Unk80362690_Unk0_UnkC_Unk6C* arg0, f32 arg1, s32 arg2) {
    if (arg2 == 1) {
        arg0->unk548 = (((arg1 - -15.0f) / 50.0f) * 180.0f) + 180.0f;
    } else {
        arg0->unk548 = ((50.0f - (arg1 - -15.0f)) / 50.0f) * 180.0f;
    }
    arg0->unk54C = 1.0f;
}

void func_802FB8CC(Unk80362690_Unk0_UnkC_Unk6C* arg0, f32 arg1, s32 arg2, s32 arg3) {
    f32 var_fv0;

    arg0->unk55C = arg3;
    if (arg3 != 0) {
        var_fv0 = 235.0f;
    } else {
        var_fv0 = 95.0f;
    }
    if (arg2 == 1) {
        arg0->unk550 = (((arg1 - -85.0f) / var_fv0) * 180.0f) + 180.0f;
    } else {
        arg0->unk550 = ((var_fv0 - (arg1 - -85.0f)) / var_fv0) * 180.0f;
    }
    arg0->unk558 = uvSinF(arg0->unk550);
    arg0->unk554 = 1.0f;
}

void func_802FB988(Unk80362690_Unk0_UnkC_Unk6C* arg0, f32 arg1, s32 arg2, s32 arg3) {
    f32 var_fv0;

    arg0->unk56C = arg3;
    if (arg3 != 0) {
        var_fv0 = 235.0f;
    } else {
        var_fv0 = 95.0f;
    }
    if (arg2 == 1) {
        arg0->unk560 = (((arg1 - -85.0f) / var_fv0) * 180.0f) + 180.0f;
    } else {
        arg0->unk560 = ((var_fv0 - (arg1 - -85.0f)) / var_fv0) * 180.0f;
    }
    arg0->unk568 = uvSinF(arg0->unk560);
    arg0->unk564 = 1.0f;
}

void func_802FBA44(Unk80362690_Unk0_UnkC_Unk6C* arg0, f32 arg1, s32 arg2, s32 arg3) {
    f32 var_fv0;
    f32 var_fv1;

    arg0->unk57C = arg3;
    if (arg3 == 3) {
        var_fv0 = 145.0f;
        var_fv1 = arg1 - -55.0f;
    } else if (arg3 == 2) {
        var_fv0 = 110.0f;
        var_fv1 = arg1 - -55.0f;
    } else if (arg3 == 1) {
        var_fv0 = 80.0f;
        var_fv1 = arg1 - -45.0f;
    } else {
        var_fv0 = 45.0f;
        var_fv1 = arg1 - -30.0f;
    }
    if (arg2 == 1) {
        arg0->unk570 = ((var_fv1 / var_fv0) * 180.0f) + 180.0f;
    } else {
        arg0->unk570 = ((var_fv0 - var_fv1) / var_fv0) * 180.0f;
    }
    arg0->unk574 = 1.0f;
    arg0->unk578 = (demoRandF() * 0.029999971f) + 0.97f;
}

void func_802FBB58(Unk80362690_Unk0_UnkC_Unk6C* arg0, f32 arg1, s32 arg2, s32 arg3) {
    f32 var_fv0;
    f32 var_fv1;

    arg0->unk58C = arg3;
    if (arg3 == 3) {
        var_fv0 = 145.0f;
        var_fv1 = arg1 - -55.0f;
    } else if (arg3 == 2) {
        var_fv0 = 110.0f;
        var_fv1 = arg1 - -55.0f;
    } else if (arg3 == 1) {
        var_fv0 = 80.0f;
        var_fv1 = arg1 - -45.0f;
    } else {
        var_fv0 = 45.0f;
        var_fv1 = arg1 - -30.0f;
    }
    if (arg2 == 1) {
        arg0->unk580 = ((var_fv1 / var_fv0) * 180.0f) + 180.0f;
    } else {
        arg0->unk580 = ((var_fv0 - var_fv1) / var_fv0) * 180.0f;
    }
    arg0->unk584 = 1.0f;
    arg0->unk588 = (demoRandF() * 0.029999971f) + 0.97f;
}

void func_802FBC6C(Unk80362690_Unk0_UnkC_Unk6C* arg0) {
    arg0->unk4D = 3;
    arg0->unk4C = 3;
    arg0->unk5E0 = 0.0f;
    if (arg0->unk4F == 0) {
        snd_play_sfx(0x17);
    }
}

void func_802FBCA8(Unk80362690_Unk0_UnkC_Unk6C* arg0, u8 arg1, f32 arg2, u8 arg3) {
    Mtx4F sp20;

    uvDobjGetPosm(arg0->unk0, arg1, &sp20);
    uvMat4RotateAxis(&sp20, arg2 * 0.01745329f, arg3);
    uvDobjPosm(arg0->unk0, arg1, &sp20);
}

void func_802FBD1C(Unk80362690_Unk0_UnkC_Unk6C* arg0, u8 arg1, f32 arg2, u8 arg3) {
    Mtx4F sp20;

    uvModelGetPosm(arg0->unk5E4, arg1, &sp20);
    uvMat4RotateAxis(&sp20, arg2 * 0.01745329f, arg3);
    uvDobjPosm(arg0->unk0, arg1, &sp20);
}

void func_802FBD90(Unk80362690_Unk0_UnkC_Unk6C* arg0) {
    func_80200638(arg0->unk0, &arg0->unk384);
    arg0->unk590 = 0.0f;
    arg0->unk598 = 0.0f;
    arg0->unk594 = 0.0f;
    arg0->unk5C0 = 0.0f;
    arg0->unk5C4 = 0.0f;
    arg0->unk5A0 = 0.0f;
    arg0->unk5A8 = 0.0f;
    arg0->unk5B0 = 0.0f;
    arg0->unk5B8 = 0.0f;
    arg0->unk5E0 = 0.0f;
    arg0->unk5D4 = 0.0f;
    arg0->unk5CC = 0.0f;
    func_802FBD1C(arg0, arg0->unk651, 0.0f, 120);
    func_802FBD1C(arg0, arg0->unk650, 0.0f, 120);
    func_802FBD1C(arg0, arg0->unk653, 0.0f, 120);
    func_802FBD1C(arg0, arg0->unk652, 0.0f, 120);
    func_802FBD1C(arg0, arg0->unk65A, 0.0f, 120);
    func_802FBD1C(arg0, arg0->unk65C, 0.0f, 120);
    func_802FBD1C(arg0, arg0->unk65B, 0.0f, 120);
    func_802FBD1C(arg0, arg0->unk654, 0.0f, 120);
    func_802FBD1C(arg0, arg0->unk657, 0.0f, 120);
    func_802FBD1C(arg0, arg0->unk655, 0.0f, 120);
    func_802FBD1C(arg0, arg0->unk658, 0.0f, 120);
    func_802FBD1C(arg0, arg0->unk656, 0.0f, 120);
    func_802FBD1C(arg0, arg0->unk659, 0.0f, 120);
}

void func_802FBEFC(Unk80362690_Unk0_UnkC_Unk6C* arg0, f32 arg1) {
    Mtx4F sp30;
    Unk803599D0* sp2C;

    if (arg0->unk4F == 0) {
        sp2C = levelGet_80345C80();
        hudWarningText(0x4F, 1.5f, 8.0f);
        snd_play_sfx(0x69);
        arg0->unk4F = 1;

        D_80364210[D_80362690->unk9C].unk0[0].unk0[0][1].unk8 = D_80364210[D_80362690->unk9C].unk0[0].unk0[0][1].unk8 - sp2C[11].unk30;
        if (D_80364210[D_80362690->unk9C].unk0[0].unk0[0][1].unk8 < -0x64) {
            D_80364210[D_80362690->unk9C].unk0[0].unk0[0][1].unk8 = -0x64;
        }
        arg0->unk534++;
        func_80341E30();
        uvMat4SetIdentity(&sp30);
        sp30.m[3][0] = arg0->unkF4.x;
        sp30.m[3][1] = arg0->unkF4.y;
        sp30.m[3][2] = arg1;
        splash_add(&sp30, 0.75f);
        snd_play_sfx(0x1A);
    }
}

void func_802FC018(Unk80362690_Unk0_UnkC_Unk6C* arg0) {
    Vec3F sp2C;
    f32 sp28;
    f32 sp24;

    if (arg0->unk168.z > 0.85) {
        sp28 = 1.0f - (2.0f * uvRandF_RANLUX());
        sp24 = 1.0f - (2.0f * uvRandF_RANLUX());
        uvVec3Copy(&sp2C, &arg0->unk15C);
        func_8034B2B0(&sp2C);
        
        if (FABS(sp28) < 0.3f) {
            sp28 = 0.3f;
        }
        
        if (FABS(sp24) < 0.3f) {
            sp24 = 0.3f;
        }
        arg0->unk15C.x = arg0->unk15C.x + (5.0f * sp28);
        arg0->unk15C.y = arg0->unk15C.y + (5.0f * sp24);
        arg0->unk15C.z = arg0->unk15C.z + 5.0f;
    } else {
        arg0->unk15C.x = arg0->unk15C.x * -1.0f;
        arg0->unk15C.y = arg0->unk15C.y * -1.0f;
        arg0->unk15C.z = arg0->unk15C.z * -1.0f;
    }
}

s32 func_802FC184(Unk80362690_Unk0_UnkC_Unk6C* arg0, f32* arg1, Vec3F* arg2) {
    Vec3F sp44;
    s32 sp40;
    s32 sp3C;
    Vec3F* sp38;
    s32 temp_v0_2;
    u32 temp_v0_3;

    sp3C = 0;
    sp38 = func_802E02EC();
    arg2->x = 0.0f;
    arg2->y = 0.0f;
    arg2->z = 1.0f;

    sp40 = db_getgnd(&arg0->unk670, &arg0->unkF4, &arg0->unk67C, &arg0->unk60, arg1, arg2);
    if (((arg0->unk60 != 0) && (arg0->unk60 == -1)) || ((arg0->unk60 != -1) && (func_802DC8E4(arg0->unk60) != 0))) {
        sp3C = 2;
        arg2->x = 0.0f;
        arg2->y = 0.0f;
        arg2->z = 1.0f;
    } else if (sp40 != 0) {
        sp3C = 1;

        temp_v0_2 = uvSobjGetPt(D_80362690->unk0[0].unk6, sp38->x, sp38->y, sp38->z);
        if (temp_v0_2 != -1) {
            temp_v0_3 = uvSobj_8022D1E4(temp_v0_2);
            if ((temp_v0_3 == 0x18) || (temp_v0_3 == 0x5C) || (temp_v0_3 == 0x5D) || (temp_v0_3 == 0x5E) || (temp_v0_3 == 0x5F) || (temp_v0_3 == 0x60) || (temp_v0_3 == 0x22) || (temp_v0_3 == 0x23) || (temp_v0_3 == 0x24) || (temp_v0_3 == 0x97) || (temp_v0_3 == 0xAB)) {
                sp3C = 3;
            } else {
                sp3C = 4;
            }
        }
    }
    if (sp40 != 0) {
        sp44.x = arg0->unk670.x - sp38->x;
        sp44.y = arg0->unk670.y - sp38->y;
        sp44.z = arg0->unk670.z - sp38->z;
        if (uvVec3Dot(&sp44, arg2) < 0.0f) {
            arg2->x *= -1.0f;
            arg2->y *= -1.0f;
            arg2->z *= -1.0f;
        }
    }
    return sp3C;
}

s32 func_802FC3B4(Unk80362690_Unk0_UnkC_Unk6C* arg0, s32 arg1, Vec3F* arg2, Vec3F* arg3) {
    Unk802D3658_Unk1228* var_s1;
    s32 i;
    Vec3F sp54;
    s32 ret;
    Unk802D3658_Unk1228* var_v0;
    f32 var_fv1;
    f32 temp_fv0;
    s32 temp_v0_2;
    u32 temp_v0_3;

    var_fv1 = 1e7f;
    var_s1 = NULL;

    for (i = 0; i < arg1; i++) {
        var_v0 = &D_80368F18.unk4[i];
        temp_fv0 = func_8034AF48(arg0->unk670, var_v0->unkC);
        if (temp_fv0 < var_fv1) {
            var_fv1 = temp_fv0;
            var_s1 = var_v0;
        }
    }
    if (var_s1 != NULL) {
        arg0->unk134.x = var_s1->unkC.x;
        arg0->unk134.y = var_s1->unkC.y;
        arg0->unk134.z = var_s1->unkC.z;
        arg2->x = var_s1->unkC.x;
        arg2->y = var_s1->unkC.y;
        arg2->z = var_s1->unkC.z;
        arg3->x = var_s1->unk1C.x;
        arg3->y = var_s1->unk1C.y;
        arg3->z = var_s1->unk1C.z;
        sp54.x = arg0->unk670.x - arg2->x;
        sp54.y = arg0->unk670.y - arg2->y;
        sp54.z = arg0->unk670.z - arg2->z;
        if (uvVec3Dot(&sp54, arg3) < 0.0f) {
            arg3->x *= -1.0f;
            arg3->y *= -1.0f;
            arg3->z *= -1.0f;
        }

        switch (var_s1->unk4) {
            case 1:
                return 1;
            case 8:
                temp_v0_2 = uvSobjGetPt(D_80362690->unk0[0].unk6, arg2->x, arg2->y, arg2->z);
                if (temp_v0_2 != -1) {
                    temp_v0_3 = uvSobj_8022D1E4(temp_v0_2);
                    if ((temp_v0_3 == 0x18) || (temp_v0_3 == 0x5C) || (temp_v0_3 == 0x5D) || (temp_v0_3 == 0x5E) || (temp_v0_3 == 0x5F) || (temp_v0_3 == 0x60) || (temp_v0_3 == 0x22) || (temp_v0_3 == 0x23) || (temp_v0_3 == 0x24) || (temp_v0_3 == 0x97) || (temp_v0_3 == 0xAB)) {
                        return 3;
                    }
                    return 4;
                }
                return 4;
            case 2:
                if (balls_802CC0D4(var_s1->unk8) != 0) {
                    ballsPopped(var_s1->unk8, &arg0->unk15C, &D_80368F18);
                    break;
                }
                return 5;
            case 4:
                return 2;
            default:
                return 1;
        }
    }

    return 0;
}

s32 func_802FC694(Unk80362690_Unk0_UnkC_Unk6C* arg0, Unk802D3658_Unk111C* arg1, Unk802D3658_Unk1224* arg2, u16 arg3, u8 arg4, Mtx4F* arg5) {
    Unk802D3658_Unk1224 sp84;
    s32 var_s1;
    s32 i;
    s32 sp78;
    s32 pad;
    Unk802D3658_Unk1228* var_s0;
    s32 temp_v1;
    Vec3F sp60;

    sp78 = func_802DB050(arg1, &sp84, arg3, arg4, arg5);
    var_s1 = 0;
    for (i = 0; i < sp78; i++) {
        var_s0 = &sp84.unk4[i];
        if (func_802DCA00(var_s0->unk8) != 0) {
            temp_v1 = uvTerraGetState(D_80362690->unk0[0].unk6, var_s0->unk8) & 0xFFF;
            if ((temp_v1 != 0xB0) && (temp_v1 != 0x67)) {
                arg2->unk4[var_s1++] = sp84.unk4[i];
            } else {
                sp60.x = arg0->unk670.x - var_s0->unkC.x;
                sp60.y = arg0->unk670.y - var_s0->unkC.y;
                sp60.z = arg0->unk670.z - var_s0->unkC.z;
                if (uvVec3Dot(&sp60, &var_s0->unk1C) >= 0.0f) {
                    arg2->unk4[var_s1++] = sp84.unk4[i];
                    continue;
                }
            }
        } else {
            arg2->unk4[var_s1++] = sp84.unk4[i];
        }
    }
    return var_s1;
}

s32 func_802FC8B0(Unk80362690_Unk0_UnkC_Unk6C* arg0) {
    Vec3F sp6C;
    Unk802D3658_Unk1228* var_s0;
    Unk802D3658_Unk1228* var_s6;
    f32 temp_fv0;
    f32 var_fs0;
    s32 temp_v0;
    s32 i;

    var_fs0 = 1e7f;
    var_s6 = NULL;
    sp6C.x = arg0->unk134.x + (arg0->unk168.x * 0.05f);
    sp6C.y = arg0->unk134.y + (arg0->unk168.y * 0.05f);
    sp6C.z = arg0->unk134.z + (arg0->unk168.z * 0.05f);
    D_80368E10.unk0 = 1;
    D_80368E10.unk4[0].unk0 = 0;
    uvVec3Copy(&D_80368E10.unk4[0].unk4, &arg0->unkF4);
    uvVec3Copy(&D_80368E10.unk4[0].unk10, &sp6C);
    temp_v0 = func_802FC694(arg0, &D_80368E10, &D_80368F18, arg0->unk0, arg0->unk4C, &arg0->unk74);
    if (temp_v0 != 0) {
        for (i = 0; i < temp_v0; i++) {
            var_s0 = &D_80368F18.unk4[i];
            temp_fv0 = func_8034AF48(arg0->unk134, var_s0->unkC);
            if (temp_fv0 < var_fs0) {
                var_fs0 = temp_fv0;
                var_s6 = var_s0;
            }
        }
        arg0->unkF4.x = (arg0->unk134.x + var_s6->unkC.x) * 0.5f;
        arg0->unkF4.y = (arg0->unk134.y + var_s6->unkC.y) * 0.5f;
        arg0->unkF4.z = (arg0->unk134.z + var_s6->unkC.z) * 0.5f;
        return 1;
    }
    return 0;
}

s32 func_802FCA8C(Unk80362690_Unk0_UnkC_Unk6C* arg0, Vec3F* arg1, Vec3F* arg2) {
    s32 temp_v0;

    D_80368E10.unk0 = 1;
    D_80368E10.unk4[0].unk0 = 0;
    uvVec3Copy(&D_80368E10.unk4[0].unk4, &arg0->unkF4);
    uvVec3Copy(&D_80368E10.unk4[0].unk10, &arg0->unk670);
    temp_v0 = func_802FC694(arg0, &D_80368E10, &D_80368F18, arg0->unk0, arg0->unk4C, &arg0->unk74);
    if (temp_v0 != 0) {
        return func_802FC3B4(arg0, temp_v0, arg1, arg2);
    }
    return 0;
}

s32 func_802FCB3C(Unk80362690_Unk0_UnkC_Unk6C* arg0, Vec3F* arg1, Vec3F* arg2) {
    s32 pad;
    s32 temp_v0;
    Vec3F sp2C = { 0.0f, 0.0f, 0.0f };

    D_80368D08.unk0 = 1;
    D_80368D08.unk4[0].unk0 = 1;

    uvVec3Copy(&D_80368D08.unk4[0].unk28, &sp2C);
    uvVec3Copy(&D_80368D08.unk4[0].unk1C, &arg0->unk5E8);
    temp_v0 = func_802FC694(arg0, &D_80368D08, &D_80368F18, arg0->unk0, arg0->unk4C, &arg0->unk74);
    if (temp_v0 != 0) {
        return func_802FC3B4(arg0, temp_v0, arg1, arg2);
    }
    return 0;
}

void func_802FCC0C(Unk80362690_Unk0_UnkC_Unk6C* arg0) {

    arg0->unkF4.x = arg0->unk118.x;
    arg0->unkF4.y = arg0->unk118.y;
    arg0->unkF4.z = arg0->unk118.z;
    arg0->unk140.x = arg0->unk124.x;
    arg0->unk140.y = arg0->unk124.y;
    arg0->unk140.z = arg0->unk124.z;
    arg0->unk68 = arg0->unk130;
    arg0->unk168.x = arg0->unk10C.x;
    arg0->unk168.y = arg0->unk10C.y;
    arg0->unk168.z = arg0->unk10C.z;
    arg0->unk4C = 9;
    arg0->unk65D = 0;
    arg0->unk100.x = 0.0f;
    arg0->unk100.y = 0.0f;
    arg0->unk100.z = 0.0f;
    arg0->unk1C0 = 0.0;
    arg0->unk1C8 = 0.0;
    arg0->unk30.x = arg0->unkF4.x - arg0->unk18->unk138.x;
    arg0->unk30.y = arg0->unkF4.y - arg0->unk18->unk138.y;
    arg0->unk30.z = arg0->unkF4.z - arg0->unk18->unk138.z;
    arg0->unk1C = func_8034B2B0(&arg0->unk30);
    arg0->unk24 = func_8034A9A0(arg0->unk30.y, arg0->unk30.x) * 57.29578f;

    while ((arg0->unk24 + 270.0f) > 180.0f) {
        arg0->unk24 -= 360.0f;
    }
    while ((arg0->unk24 + 270.0f) < -180.0f) {
        arg0->unk24 += 360.0f;
    }
    while (arg0->unk140.x > 180.0f) {
        arg0->unk140.x -= 360.0f;
    }
    while (arg0->unk140.x < -180.0f) {
        arg0->unk140.x += 360.0f;
    }
    if (arg0->unk140.x < (arg0->unk24 + 270.0f)) {
        arg0->unk28 = -1.0f;
    } else {
        arg0->unk28 = 1.0f;
    }
}

s32 func_802FCE38(Unk80362690_Unk0_UnkC_Unk6C* arg0) {
    s32 i;
    s32 pad;
    Vec3F sp4C;
    Vec3F sp40;

    if (func_802FCA8C(arg0, &sp4C, &sp40) != 0) {

        for (i = 0; i < 5; i++) {
            arg0->unkF4.x += sp40.x * 0.05f;
            arg0->unkF4.y += sp40.y * 0.05f;
            arg0->unkF4.z += sp40.z * 0.05f;
            if (func_802FCA8C(arg0, &sp4C, &sp40) == 0) {
                break;
            }
        }

        if (i == 5) {
            func_802FCC0C(arg0);
        }
        return 1;
    }

    if ((arg0->unk140.y < 45.0f) && (arg0->unk140.y > -45.0f)) {
        if (func_802FCB3C(arg0, &sp4C, &sp40) != 0) {
            for (i = 0; i < 5; i++) {
                arg0->unkF4.x += sp40.x * 0.05f;
                arg0->unkF4.y += sp40.y * 0.05f;
                arg0->unkF4.z += sp40.z * 0.05f;
                if ((func_802FCB3C(arg0, &sp4C, &sp40) == 0) && (func_802FCA8C(arg0, &sp4C, &sp40) == 0)) {
                    break;
                }
            }
            if (i == 5) {
                func_802FCC0C(arg0);
            }
            return 1;
        }
        return 0;
    }
    return 0;
}

f32 func_802FD010(Unk80362690_Unk0_UnkC_Unk6C* arg0) {
    return func_802FB660(arg0) + arg0->unk68;
}

void func_802FD038(Unk80362690_Unk0_UnkC_Unk6C* arg0) {
    Vec3F sp24 = { 0.0f, 0.0f, 0.0f };

    D_80368C00.unk0 = 3;
    D_80368C00.unk4[0].unk0 = 1;
    uvVec3Copy(&D_80368C00.unk4[0].unk28, &sp24);
    uvVec3Copy(&D_80368C00.unk4[0].unk1C, &arg0->unk5E8);
    D_80368C00.unk4[1].unk0 = 1;
    uvVec3Copy(&D_80368C00.unk4[1].unk1C, &arg0->unk618);
    uvVec3Copy(&D_80368C00.unk4[1].unk28, &arg0->unk624);
    D_80368C00.unk4[2].unk0 = 1;
    uvVec3Copy(&D_80368C00.unk4[2].unk1C, &arg0->unk600);
    uvVec3Copy(&D_80368C00.unk4[2].unk28, &arg0->unk60C);
    func_802FD114(arg0);
}

f32 D_8034F3C8[3] = { 0, 0, -1.0f };

void func_802FD114(Unk80362690_Unk0_UnkC_Unk6C* arg0) {
    Unk80362690_Unk0_UnkC* var_v1;
    Vec3F sp38;
    f32 temp_fv0;

    var_v1 = &D_80362690->unk0[D_80362690->unk9C].unkC;
    switch (var_v1->pilot) {
    case 0:
    case 3:
        arg0->unk190 = 0.7f;
        arg0->unk194 = 0.9f;
        break;
    case 1:
    case 4:
        arg0->unk190 = 1.4f;
        arg0->unk194 = 1.2f;
        break;
    case 2:
    case 5:
        arg0->unk190 = 1.0f;
        arg0->unk194 = 1.0f;
        break;
    }
    arg0->unk19C = 0;
    func_803343D8(1);
    arg0->unk4D = 3;
    arg0->unk4C = 3;
    arg0->unk50 = 0;
    arg0->unk198 = 0;
    arg0->unk4F = 0;
    arg0->unk53C = 0.0f;
    arg0->unk540 = 0.0f;
    arg0->unk6C = 0.0f;
    arg0->unk70 = 0.0f;
    arg0->unk1B8 = 0.0;
    func_802FBD90(arg0);
    uvDobj_802180DC(arg0->unk0, &arg0->unk384);
    
    arg0->unk140.z = 0.0f;
    arg0->unk140.y = 0.0f;
    arg0->unk140.x = 0.0f;
    arg0->unk15C.z = 0.0f;
    arg0->unk15C.y = 0.0f;
    arg0->unk15C.x = 0.0f;
    arg0->unk14C.z = 0.0f;
    arg0->unk14C.y = 0.0f;
    arg0->unk14C.x = 0.0f;
    arg0->unk184.z = 0.0f;
    arg0->unk184.y = 0.0f;
    arg0->unk184.x = 0.0f;
    arg0->unk100.x = 0.0f;
    arg0->unk100.y = 0.0f;
    arg0->unk100.z = 0.0f;
    arg0->unk174.x = arg0->unk174.y = 0.0f;
    arg0->unk168.z = 1.0f;
    arg0->unk168.x = arg0->unk168.y = 0.0f;
    arg0->unk174.z = 1.0f;
    arg0->unk544 = 0.0f;
    db_getstart(&arg0->unk74, &sp38, NULL, NULL);
    uvDobjPosm((s32) arg0->unk0, 0, &arg0->unk74);
    uvMat4InvertTranslationRotation(&arg0->unkB4, &arg0->unk74);
    arg0->unk67C = 1;
    func_8034AF94(&arg0->unk74, &arg0->unkF4, &arg0->unk140);
    arg0->unk670.x = arg0->unk74.m[3][0];
    arg0->unk670.y = arg0->unk74.m[3][1];
    arg0->unk670.z = arg0->unk74.m[3][2];
    func_802FC184(arg0, &arg0->unk68, &arg0->unk168);
    arg0->unk65D = 0;
    arg0->unk64 = 0.0f;
    temp_fv0 = func_802FD010(arg0);
    arg0->unk74.m[3][2] = temp_fv0;
    arg0->unkF4.z = temp_fv0;
    arg0->unk670.z = temp_fv0;
    uvMat4InvertTranslationRotation(&arg0->unkB4, &arg0->unk74);
    arg0->unk130 = arg0->unk68;
    arg0->unk118.x = arg0->unkF4.x;
    arg0->unk118.y = arg0->unkF4.y;
    arg0->unk118.z = arg0->unkF4.z;
    arg0->unk124.x = arg0->unk140.x;
    arg0->unk124.y = arg0->unk140.y;
    arg0->unk124.z = arg0->unk140.z;
    arg0->unk10C.x = arg0->unk168.x;
    arg0->unk10C.y = arg0->unk168.y;
    arg0->unk10C.z = arg0->unk168.z;
}

void func_802FD388(Unk80362690_Unk0_UnkC_Unk6C* arg0) {
    arg0->unk140.x -= (arg0->unk14 * FABS(arg0->unk14)) * 5.0;
}

void func_802FD3E0(Unk80362690_Unk0_UnkC_Unk6C* arg0) {
    f32 sp94;
    s32 pad;
    Vec3F sp84;
    Vec3F sp78;
    Mtx4F sp38;

    arg0->unk540 = arg0->unk10 * 60.0;
    sp94 = uvSinF(arg0->unk540 * 0.01745329f);
    sp84.z = uvCosF(arg0->unk540 * 0.01745329f);
    sp84.x = 0.0f;
    sp84.y = sp94;
    sp78.x = arg0->unk140.x;
    func_8034AACC(&sp78, arg0->unk168);
    arg0->unk544 = sp78.y;
    func_8034B210(arg0->unkF4, sp78, &sp38);
    func_8034ABB0(&sp38, &arg0->unk184, &sp84);
    arg0->unk140.y = ((-arg0->unk53C * 0.75f) - ((arg0->unk540 / 60.0) * 20.0)) + arg0->unk544;
    arg0->unk140.z = sp78.z;
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_82B90/func_802FD55C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_82B90/func_802FD794.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_82B90/func_802FD8C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_82B90/func_802FDF8C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_82B90/func_802FE054.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_82B90/func_802FE1A8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_82B90/func_802FE2FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_82B90/func_802FE564.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_82B90/func_802FE7A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_82B90/func_802FE9DC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_82B90/func_802FEAD0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_82B90/func_802FEBC4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_82B90/func_802FEEC0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_82B90/func_802FF1BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_82B90/func_802FF5B4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_82B90/func_802FF654.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_82B90/func_802FFB3C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_82B90/func_80300018.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_82B90/func_80300448.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_82B90/func_8030055C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_82B90/func_80300624.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_82B90/func_803006E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_82B90/func_8030089C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_82B90/func_80300B04.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_82B90/func_80300E78.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_82B90/func_80301090.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_82B90/func_803014A8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_82B90/func_80301AF8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_82B90/func_80301C58.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_82B90/func_80301D28.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_82B90/func_80301F70.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_82B90/func_80302484.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_82B90/func_803029CC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_82B90/func_80302BA0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_82B90/func_80303028.s")
