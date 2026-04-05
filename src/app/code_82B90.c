#include "common.h"
#include "code_82B90.h"
#include <uv_dobj.h>
#include <uv_janim.h>
#include <uv_math.h>
#include <uv_matrix.h>
#include <uv_model.h>
#include <uv_sobj.h>
#include "kernel/code_8170.h"
#include "app/balls.h"
#include "app/demo.h"
#include "app/environment.h"
#include "app/hud.h"
#include "app/shadow.h"
#include "app/snd.h"
#include "app/splash.h"
#include "app/task.h"
#include "app/camera.h"
#include "app/code_61A60.h"
#include "app/code_66F70.h"
#include "app/jumble_hopper.h"
#include "app/code_9A960.h"
#include "app/code_D1ED0.h"

Unk802D3658_Unk111C D_80368C00;
Unk802D3658_Unk111C D_80368D08;
Unk802D3658_Unk111C D_80368E10;
Unk802D3658_Unk1224 D_80368F18;
u8 D_8036905C[5];

f32 func_802FB660(JumbleHopperData* arg0) {
    f32 sp34;
    f32 sp30;
    f32 sp2C;

    sp34 = MIN(arg0->unk5CC, arg0->unk5D4) + arg0->unk140.y;

    sp30 = (180.0f - sp34) - (180.0f + arg0->unk5C0);
    sp2C = (90.0f - sp30) + arg0->unk5D8;

    arg0->unk6C = (uvCosF(arg0->unk140.y * 0.01745329f) * arg0->unk63C) + (uvCosF(sp34 * 0.01745329f) * arg0->unk640) +
                  (uvCosF(sp30 * 0.01745329f) * arg0->unk644) + (uvCosF(sp2C * 0.01745329f) * arg0->unk648);

    return arg0->unk6C;
}

s32 func_802FB784(JumbleHopperData* arg0, f32 arg1) {
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

void func_802FB82C(JumbleHopperData* arg0) {
    if (arg0->unk50 == 0) {
        arg0->unk50 = 1;
        arg0->unk4F = 0;
    }
}

void func_802FB84C(JumbleHopperData* arg0, f32 arg1, s32 arg2) {
    if (arg2 == 1) {
        arg0->unk548 = (((arg1 - -15.0f) / 50.0f) * 180.0f) + 180.0f;
    } else {
        arg0->unk548 = ((50.0f - (arg1 - -15.0f)) / 50.0f) * 180.0f;
    }
    arg0->unk54C = 1.0f;
}

void func_802FB8CC(JumbleHopperData* arg0, f32 arg1, s32 arg2, s32 arg3) {
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

void func_802FB988(JumbleHopperData* arg0, f32 arg1, s32 arg2, s32 arg3) {
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

void func_802FBA44(JumbleHopperData* arg0, f32 arg1, s32 arg2, s32 arg3) {
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
    arg0->unk578 = (demoRandF() * (1.0f - 0.97f)) + 0.97f;
}

void func_802FBB58(JumbleHopperData* arg0, f32 arg1, s32 arg2, s32 arg3) {
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
    arg0->unk588 = (demoRandF() * (1.0f - 0.97f)) + 0.97f;
}

void func_802FBC6C(JumbleHopperData* arg0) {
    arg0->unk4D = 3;
    arg0->unk4C = 3;
    arg0->unk5E0 = 0.0f;
    if (arg0->unk4F == 0) {
        sndPlaySfx(0x17);
    }
}

void func_802FBCA8(JumbleHopperData* arg0, u8 arg1, f32 arg2, char axis) {
    Mtx4F sp20;

    uvDobjGetPosm(arg0->objId, arg1, &sp20);
    uvMat4RotateAxis(&sp20, arg2 * 0.01745329f, axis);
    uvDobjPosm(arg0->objId, arg1, &sp20);
}

void func_802FBD1C(JumbleHopperData* arg0, u8 arg1, f32 arg2, char axis) {
    Mtx4F sp20;

    uvModelGetPosm(arg0->modelId, arg1, &sp20);
    uvMat4RotateAxis(&sp20, arg2 * 0.01745329f, axis);
    uvDobjPosm(arg0->objId, arg1, &sp20);
}

void func_802FBD90(JumbleHopperData* arg0) {
    func_80200638(arg0->objId, &arg0->unk384);
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
    func_802FBD1C(arg0, arg0->unk651, 0.0f, 'x');
    func_802FBD1C(arg0, arg0->unk650, 0.0f, 'x');
    func_802FBD1C(arg0, arg0->unk653, 0.0f, 'x');
    func_802FBD1C(arg0, arg0->unk652, 0.0f, 'x');
    func_802FBD1C(arg0, arg0->unk65A, 0.0f, 'x');
    func_802FBD1C(arg0, arg0->unk65C, 0.0f, 'x');
    func_802FBD1C(arg0, arg0->unk65B, 0.0f, 'x');
    func_802FBD1C(arg0, arg0->unk654, 0.0f, 'x');
    func_802FBD1C(arg0, arg0->unk657, 0.0f, 'x');
    func_802FBD1C(arg0, arg0->unk655, 0.0f, 'x');
    func_802FBD1C(arg0, arg0->unk658, 0.0f, 'x');
    func_802FBD1C(arg0, arg0->unk656, 0.0f, 'x');
    func_802FBD1C(arg0, arg0->unk659, 0.0f, 'x');
}

void func_802FBEFC(JumbleHopperData* arg0, f32 arg1) {
    Mtx4F sp30;
    Unk803599D0* sp2C;

    if (arg0->unk4F == 0) {
        sp2C = &taskGet_80345C80()->unk0;
        hudWarningText(0x4F, 1.5f, 8.0f);
        sndPlaySfx(0x69);
        arg0->unk4F = 1;

        // TODO: fix array and/or struct
        D_80364210[D_80362690->unk9C].unk38 = D_80364210[D_80362690->unk9C].unk38 - sp2C[11].unk4[5].y;
        if (D_80364210[D_80362690->unk9C].unk38 < -100) {
            D_80364210[D_80362690->unk9C].unk38 = -100;
        }
        arg0->unk534++;
        splashClear();
        uvMat4SetIdentity(&sp30);
        sp30.m[3][0] = arg0->unkF4.x;
        sp30.m[3][1] = arg0->unkF4.y;
        sp30.m[3][2] = arg1;
        splashAdd(&sp30, 0.75f);
        sndPlaySfx(SFX_UNK_026);
    }
}

void func_802FC018(JumbleHopperData* arg0) {
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

s32 func_802FC184(JumbleHopperData* arg0, f32* arg1, Vec3F* arg2) {
    Vec3F sp44;
    s32 sp40;
    s32 sp3C;
    Vec3F* sp38;
    s32 soid;
    u32 modelId;

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

        soid = uvSobjGetPt(D_80362690->terraId, sp38->x, sp38->y, sp38->z);
        if (soid != -1) {
            modelId = uvSobj_8022D1E4(soid);
            if (MODEL_IS_TREE(modelId) || (modelId == MODEL_ROW_OF_5X_TREES) || (modelId == MODEL_TREE_SNOW_BILLBOARD)) {
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

s32 func_802FC3B4(JumbleHopperData* arg0, s32 arg1, Vec3F* arg2, Vec3F* arg3) {
    Unk802D3658_Unk1228* var_s1;
    s32 i;
    Vec3F sp54;
    s32 ret;
    Unk802D3658_Unk1228* var_v0;
    f32 var_fv1;
    f32 temp_fv0;
    s32 soid;
    u32 modelId;

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

        switch (var_s1->collisionType) {
        case 1:
            return 1;
        case 8:
            soid = uvSobjGetPt(D_80362690->terraId, arg2->x, arg2->y, arg2->z);
            if (soid != -1) {
                modelId = uvSobj_8022D1E4(soid);
                if ((modelId == 0x18) || (modelId == 0x5C) || (modelId == 0x5D) || (modelId == 0x5E) || (modelId == 0x5F) || (modelId == 0x60) ||
                    (modelId == 0x22) || (modelId == 0x23) || (modelId == 0x24) || (modelId == 0x97) || (modelId == 0xAB)) {
                    return 3;
                }
                return 4;
            }
            return 4;
        case 2:
            if (ballsObjIdExists(var_s1->surfaceId)) {
                ballsPopped(var_s1->surfaceId, &arg0->unk15C, &D_80368F18);
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

s32 func_802FC694(JumbleHopperData* arg0, Unk802D3658_Unk111C* arg1, Unk802D3658_Unk1224* arg2, u16 arg3, u8 arg4, Mtx4F* arg5) {
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
        if (func_802DCA00(var_s0->surfaceId) != 0) {
            temp_v1 = uvTerraGetState(D_80362690->terraId, var_s0->surfaceId) & 0xFFF;
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

s32 func_802FC8B0(JumbleHopperData* arg0) {
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
    temp_v0 = func_802FC694(arg0, &D_80368E10, &D_80368F18, arg0->objId, arg0->unk4C, &arg0->unk74);
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

s32 func_802FCA8C(JumbleHopperData* arg0, Vec3F* arg1, Vec3F* arg2) {
    s32 temp_v0;

    D_80368E10.unk0 = 1;
    D_80368E10.unk4[0].unk0 = 0;
    uvVec3Copy(&D_80368E10.unk4[0].unk4, &arg0->unkF4);
    uvVec3Copy(&D_80368E10.unk4[0].unk10, &arg0->unk670);
    temp_v0 = func_802FC694(arg0, &D_80368E10, &D_80368F18, arg0->objId, arg0->unk4C, &arg0->unk74);
    if (temp_v0 != 0) {
        return func_802FC3B4(arg0, temp_v0, arg1, arg2);
    }
    return 0;
}

s32 func_802FCB3C(JumbleHopperData* arg0, Vec3F* arg1, Vec3F* arg2) {
    s32 pad;
    s32 temp_v0;
    Vec3F sp2C = { 0.0f, 0.0f, 0.0f };

    D_80368D08.unk0 = 1;
    D_80368D08.unk4[0].unk0 = 1;

    uvVec3Copy(&D_80368D08.unk4[0].unk28, &sp2C);
    uvVec3Copy(&D_80368D08.unk4[0].unk1C, &arg0->unk5E8);
    temp_v0 = func_802FC694(arg0, &D_80368D08, &D_80368F18, arg0->objId, arg0->unk4C, &arg0->unk74);
    if (temp_v0 != 0) {
        return func_802FC3B4(arg0, temp_v0, arg1, arg2);
    }
    return 0;
}

void func_802FCC0C(JumbleHopperData* arg0) {
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
    arg0->unk30.x = arg0->unkF4.x - arg0->unk18->unk108.m[3][0];
    arg0->unk30.y = arg0->unkF4.y - arg0->unk18->unk108.m[3][1];
    arg0->unk30.z = arg0->unkF4.z - arg0->unk18->unk108.m[3][2];
    arg0->unk1C = func_8034B2B0(&arg0->unk30);
    arg0->unk24 = func_8034A9A0(arg0->unk30.y, arg0->unk30.x) * RADIAN_TO_ANGLE_FACTOR;

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

s32 func_802FCE38(JumbleHopperData* arg0) {
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

f32 func_802FD010(JumbleHopperData* arg0) {
    return func_802FB660(arg0) + arg0->unk68;
}

void func_802FD038(JumbleHopperData* arg0) {
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

void func_802FD114(JumbleHopperData* arg0) {
    Unk80362690_Unk0* var_v1;
    Vec3F sp38;
    f32 temp_fv0;

    var_v1 = &D_80362690->unkC[D_80362690->unk9C];
    switch (var_v1->pilot) {
    case PILOT_LARK:
    case PILOT_KIWI:
        arg0->unk190 = 0.7f;
        arg0->unk194 = 0.9f;
        break;
    case PILOT_GOOSE:
    case PILOT_IBIS:
        arg0->unk190 = 1.4f;
        arg0->unk194 = 1.2f;
        break;
    case PILOT_HAWK:
    case PILOT_ROBIN:
        arg0->unk190 = 1.0f;
        arg0->unk194 = 1.0f;
        break;
    }
    arg0->unk19C = 0;
    shadow_803343D8(1);
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
    uvDobj_802180DC(arg0->objId, &arg0->unk384);

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
    uvDobjPosm((s32)arg0->objId, 0, &arg0->unk74);
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

void func_802FD388(JumbleHopperData* arg0) {
    arg0->unk140.x -= (arg0->unk14 * FABS(arg0->unk14)) * 5.0;
}

void func_802FD3E0(JumbleHopperData* arg0) {
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

void func_802FD55C(JumbleHopperData* arg0, Vec3F arg1) {
    Vec3F sp4C;
    s32 pad[2];
    f32 temp_fv1;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv0_7;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    s32 pad2;

    arg0->unk59C = 1;

    arg0->unk5A0 = 90.0f - (demoRandF() * 135.0f);
    arg0->unk5A4 = 0;
    arg0->unk5A8 = 90.0f - (demoRandF() * 135.0f);
    arg0->unk5AC = 1;
    arg0->unk5B0 = demoRandF() * 70.0f;
    arg0->unk5B4 = 0;
    arg0->unk5B8 = demoRandF() * 70.0f;
    arg0->unk5C8 = 0;
    arg0->unk5CC = demoRandF() * 90.0f;
    arg0->unk5D0 = 1;
    arg0->unk5D4 = demoRandF() * 90.0f;
    arg0->unk5BC = 1;
    arg0->unk5C0 = demoRandF() * -90.0f;
    arg0->unk5C4 = demoRandF() * -90.0f;
    sp4C.x = -arg0->unk15C.x;
    sp4C.y = -arg0->unk15C.y;
    sp4C.z = -arg0->unk15C.z;
    if (func_8034B2B0(&sp4C) == 0.0) {
        sp4C.z = -1.0f;
    }

    func_8034B2B0(&arg0->unk168);
    temp_fv0_7 = uvVec3Dot(&arg0->unk168, &sp4C);
    temp_fv1 = (arg0->unk168.x * temp_fv0_7) + arg1.x;
    temp_fa0 = (arg0->unk168.y * temp_fv0_7) + arg1.y;
    temp_fa1 = (arg0->unk168.z * temp_fv0_7) + arg1.z;
    sp28 = (temp_fv1 - (arg1.x + sp4C.x)) + temp_fv1;
    sp2C = (temp_fa0 - (arg1.y + sp4C.y)) + temp_fa0;
    sp30 = (temp_fa1 - (arg1.z + sp4C.z)) + temp_fa1;
    arg0->unk15C.x = sp28 - arg1.x;
    arg0->unk15C.y = sp2C - arg1.y;
    arg0->unk15C.z = sp30 - arg1.z;

    arg0->unk15C.x *= arg0->unk180 * 0.35f;
    arg0->unk15C.y *= arg0->unk180 * 0.35f;
    arg0->unk15C.z *= arg0->unk180 * 0.35f;
}

void func_802FD794(JumbleHopperData* arg0) {
    arg0->unk1C0 += D_8034F854;

    if ((FABS(arg0->unk14) * 0.75) < arg0->unk1C0) {
        arg0->unk4C = 1;
        arg0->unk5E0 = 0.0f;
        arg0->unk1C0 = 0.0;
    }
    func_802FD3E0(arg0);
    func_802FD388(arg0);
    arg0->unk5D8 = ((-arg0->unk140.y - arg0->unk5C0) - arg0->unk5CC) + arg0->unk5E0;
    func_802FBD1C(arg0, arg0->unk659, arg0->unk5D8, 'x');
    arg0->unk5DC = ((-arg0->unk140.y - arg0->unk5C4) - arg0->unk5D4) + arg0->unk5E0;
    func_802FBD1C(arg0, arg0->unk656, arg0->unk5DC, 'x');
    arg0->unkF4.z = func_802FD010(arg0);
    func_802FCE38(arg0);
}

void func_802FD8C0(JumbleHopperData* arg0) {
    f32 var_fv1;

    func_802FD3E0(arg0);
    arg0->unk53C -= 390.0 * D_8034F854;
    if (arg0->unk53C < 0) {
        arg0->unk53C = 0.0f;
        arg0->unk1B8 = 0.0;
        arg0->unk130 = arg0->unk68;
        arg0->unk118.x = arg0->unkF4.x;
        arg0->unk118.y = arg0->unkF4.y;
        arg0->unk118.z = arg0->unkF4.z;
        arg0->unk4C = 2;
        arg0->unk50 = 0;
        arg0->unk124.x = arg0->unk140.x;
        arg0->unk124.y = arg0->unk140.y;
        arg0->unk124.z = arg0->unk140.z;
        arg0->unk10C.x = arg0->unk168.x;
        arg0->unk10C.y = arg0->unk168.y;
        arg0->unk10C.z = arg0->unk168.z;
        if (arg0->unk19C != 0) {
            arg0->unk198 = 1;
            if (arg0->unk540 > 0.0f) {
                var_fv1 = arg0->unk540 / 30.0;
                if (var_fv1 > 1.0f) {
                    var_fv1 = 2.0f - var_fv1;
                }
                arg0->unk1AC = func_8034AD14(2.0 * var_fv1);
            } else {
                var_fv1 = arg0->unk540 / -30.0;
                if (var_fv1 > 1.0f) {
                    var_fv1 = 2.0f - var_fv1;
                }
                arg0->unk1B0 = func_8034AD14(2.0 * var_fv1);
            }
            if ((arg0->unk1AC != 0) || (arg0->unk1B0 != 0)) {
                arg0->unk1A0 = 1;
            } else {
                arg0->unk1A0 = 0;
            }
        } else {
            arg0->unk198 = 0;
            arg0->unk1A0 = 0;
            arg0->unk1B0 = 0;
            arg0->unk1AC = 0;
        }
        arg0->unk1A4 = 0;
        sndPlaySfx(0x4A);
        arg0->unk15C.x = (f64)arg0->unk184.x * 30.0f * arg0->unk194;
        arg0->unk15C.y = (f64)arg0->unk184.y * 30.0f * arg0->unk194;
        arg0->unk15C.z = (f64)arg0->unk184.z * 30.0f * arg0->unk194;
        func_802FB84C(arg0, 0, 1);
        func_802FB8CC(arg0, arg0->unk5A0, 1, 0);
        func_802FB988(arg0, arg0->unk5A8, 1, 0);

        if (arg0->unk540 > 5.0f) {
            if (arg0->unk198 != 0) {
                func_802FBA44(arg0, 0.0f, 0, 2);
                func_802FBB58(arg0, 0.0f, 0, 2);
            } else {
                func_802FBA44(arg0, 0.0f, 0, 1);
                func_802FBB58(arg0, 0.0f, 0, 1);
            }
        } else if (arg0->unk540 < -5.0f) {
            if (arg0->unk198 != 0) {
                func_802FBA44(arg0, 0.0f, 1, 2);
                func_802FBB58(arg0, 0.0f, 1, 2);
            } else {
                func_802FBA44(arg0, 0.0f, 1, 1);
                func_802FBB58(arg0, 0.0f, 1, 1);
            }
        } else {
            func_802FBA44(arg0, 0.0f, 1, 0);
            func_802FBB58(arg0, 0.0f, 1, 0);
        }
    }
    func_802FBD1C(arg0, arg0->unk65A, -arg0->unk53C * 0.5f, 'x');
    arg0->unk5A0 += 390.0 * D_8034F854 * 1.222;
    if (arg0->unk5A0 > 0.0f) {
        arg0->unk5A0 = 0.0f;
    }
    func_802FBD1C(arg0, arg0->unk650, arg0->unk5A0, 'x');
    arg0->unk5A8 += 390.0 * D_8034F854 * 1.222;
    if (arg0->unk5A8 > 0.0f) {
        arg0->unk5A8 = 0.0f;
    }
    func_802FBD1C(arg0, arg0->unk651, arg0->unk5A8, 'x');
    arg0->unk5B0 += (390.0 * D_8034F854) * 2.0;
    if (arg0->unk5B0 > 0) {
        arg0->unk5B0 = 0.0f;
    }
    func_802FBD1C(arg0, arg0->unk652, arg0->unk5B0, 'x');
    arg0->unk5B8 += (390.0 * D_8034F854) * 2.0;
    if (arg0->unk5B8 > 0) {
        arg0->unk5B8 = 0.0f;
    }
    func_802FBD1C(arg0, arg0->unk653, arg0->unk5B8, 'x');
    arg0->unk5CC = arg0->unk53C * 2;
    func_802FBD1C(arg0, arg0->unk657, arg0->unk5CC, 'x');
    arg0->unk5D4 = arg0->unk53C * 2;
    func_802FBD1C(arg0, arg0->unk654, arg0->unk5D4, 'x');
    arg0->unk5C0 = arg0->unk53C * -2;
    func_802FBD1C(arg0, arg0->unk658, arg0->unk5C0, 'x');
    arg0->unk5C4 = arg0->unk53C * -2;
    func_802FBD1C(arg0, arg0->unk655, arg0->unk5C4, 'x');
    arg0->unk5E0 = arg0->unk53C - 65.0;
    arg0->unk5D8 = ((-arg0->unk140.y - arg0->unk5C0) - arg0->unk5CC) + arg0->unk5E0;
    func_802FBD1C(arg0, arg0->unk659, arg0->unk5D8, 'x');
    arg0->unk5DC = ((-arg0->unk140.y - arg0->unk5C4) - arg0->unk5D4) + arg0->unk5E0;
    func_802FBD1C(arg0, arg0->unk656, arg0->unk5DC, 'x');
    arg0->unkF4.z = func_802FD010(arg0);
    func_802FCE38(arg0);
}

void func_802FDF8C(JumbleHopperData* arg0, f32 arg1) {
    if (arg1 > 0.2f) {
        arg1 = 0.2f;
    } else if (arg1 < -0.2f) {
        arg1 = -0.2f;
    }
    arg0->unk598 -= arg1 * 25.0f;

    if (arg0->unk598 > 30.0f) {
        arg0->unk598 = 30.0f;
    } else if (arg0->unk598 < -30.0f) {
        arg0->unk598 = -30.0f;
    }
    func_802FBD1C(arg0, arg0->unk65B, arg0->unk598, 'z');
}

void func_802FE054(JumbleHopperData* arg0, f32 arg1) {
    if (arg1 > 0.2f) {
        arg1 = 0.2f;
    } else if (arg1 < -0.2f) {
        arg1 = -0.2f;
    }
    arg0->unk5A0 -= arg1 * 25.0f;

    if (arg0->unk5A0 > 10.0f) {
        arg0->unk5A0 = 10.0f;
        func_802FB8CC(arg0, 10.0f, 0, 0);
    } else if (arg0->unk5A0 < -85.0f) {
        arg0->unk5A0 = -85.0f;
        func_802FB8CC(arg0, -85.0f, 1, 0);
    }
    func_802FBD1C(arg0, arg0->unk650, arg0->unk5A0, 'x');

    arg0->unk5B0 = MAX(arg0->unk5A0, -35.0f);
    arg0->unk5B0 = MIN(arg0->unk5B0, 20.0f);

    func_802FBD1C(arg0, arg0->unk652, arg0->unk5B0, 'x');
}

void func_802FE1A8(JumbleHopperData* arg0, f32 arg1) {
    if (arg1 > 0.2f) {
        arg1 = 0.2f;
    } else if (arg1 < -0.2f) {
        arg1 = -0.2f;
    }
    arg0->unk5A8 -= arg1 * 25.0f;

    if (arg0->unk5A8 > 10.0f) {
        arg0->unk5A8 = 10.0f;
        func_802FB988(arg0, 10.0f, 0, 0);
    } else if (arg0->unk5A8 < -85.0f) {
        arg0->unk5A8 = -85.0f;
        func_802FB988(arg0, -85.0f, 1, 0);
    }
    func_802FBD1C(arg0, arg0->unk651, arg0->unk5A8, 'x');

    arg0->unk5B8 = MAX(arg0->unk5A8, -35.0f);
    arg0->unk5B8 = MIN(arg0->unk5B8, 20.0f);

    func_802FBD1C(arg0, arg0->unk653, arg0->unk5B8, 'x');
}

void func_802FE2FC(JumbleHopperData* arg0) {
    f32 temp_fv1;
    f32 temp_fa0;

    if (FABS(arg0->unk14) > 0.1) {
        arg0->unk590 -= arg0->unk14 * 700.0f * D_8034F854 * 0.6f;
        if (arg0->unk590 > 30.0f) {
            arg0->unk590 = 30.0f;
        } else if (arg0->unk590 < -30.0f) {
            arg0->unk590 = -30.0f;
        }
    } else {
        if (arg0->unk590 < 0) {
            arg0->unk590 = arg0->unk590 + (700.0f * D_8034F854 * 0.6f);
            if (arg0->unk590 > 0) {
                arg0->unk590 = 0;
            }
        } else if (arg0->unk590 > 0) {
            arg0->unk590 = arg0->unk590 - (700.0f * D_8034F854 * 0.6f);
            if (arg0->unk590 < 0) {
                arg0->unk590 = 0;
            }
        }
    }
    func_802FBD1C(arg0, arg0->unk65A, arg0->unk590, 'z');
    arg0->unk548 += 700.0f * D_8034F854;
    if (arg0->unk548 > 360.0f) {
        arg0->unk548 -= 360.0f;
    }
    arg0->unk54C *= 0.95f;
    temp_fv1 = 50.0f;
    temp_fa0 = (uvCosF(arg0->unk548 * 0.0174533f) * (temp_fv1 * 0.5f) * arg0->unk54C) + (-15.0f + (temp_fv1 * 0.5f));
    func_802FBCA8(arg0, arg0->unk65A, temp_fa0, 'x');
}

void func_802FE564(JumbleHopperData* arg0) {
    f32 temp_fv0;
    f32 var_fa1;
    f32 var_fv1;

    arg0->unk550 += 240.0f * D_8034F854;
    if (arg0->unk550 > 360.0f) {
        arg0->unk550 -= 360.0f;
    }

    if (arg0->unk55C) {
        temp_fv0 = uvSinF(arg0->unk550 * 0.0174533f);
        if ((temp_fv0 < 0.0f) && ((arg0->unk558 * temp_fv0) < 0.0f)) {
            arg0->unk55C = 0;
        }
        arg0->unk558 = temp_fv0;
    }
    if (arg0->unk55C != 0) {
        var_fa1 = 235.0f;
        arg0->unk554 *= 0.995f;
    } else {
        var_fa1 = 95.0f;
        arg0->unk554 *= 0.985f;
    }

    arg0->unk5A0 = (uvCosF(arg0->unk550 * 0.0174533f) * (var_fa1 * 0.5f) * arg0->unk554) + (-85.0f + (var_fa1 * 0.5f));
    func_802FBD1C(arg0, arg0->unk650, arg0->unk5A0, 'x');

    var_fv1 = MAX(arg0->unk5A0, -45.0f);
    var_fv1 = MIN(var_fv1, 20.0f);

    if (arg0->unk5B0 < var_fv1) {
        arg0->unk5B0 += 240.0f * D_8034F854 * 0.4f;
    }
    if (var_fv1 < arg0->unk5B0) {
        arg0->unk5B0 -= 240.0f * D_8034F854 * 0.4f;
    }
    func_802FBD1C(arg0, arg0->unk652, arg0->unk5B0, 'x');
}

void func_802FE7A0(JumbleHopperData* arg0) {
    f32 temp_fv0;
    f32 var_fa1;
    f32 var_fv1;

    arg0->unk560 += 240.0f * D_8034F854;
    if (arg0->unk560 > 360.0f) {
        arg0->unk560 -= 360.0f;
    }

    if (arg0->unk56C != 0) {
        temp_fv0 = uvSinF(arg0->unk560 * 0.0174533f);
        if ((temp_fv0 < 0.0f) && ((arg0->unk568 * temp_fv0) < 0.0f)) {
            arg0->unk56C = 0;
        }
        arg0->unk568 = temp_fv0;
    }
    if (arg0->unk56C != 0) {
        var_fa1 = 235.0f;
        arg0->unk564 *= 0.995f;
    } else {
        var_fa1 = 95.0f;
        arg0->unk564 *= 0.985f;
    }

    arg0->unk5A8 = (uvCosF(arg0->unk560 * 0.0174533f) * (var_fa1 * 0.5f) * arg0->unk564) + (-85.0f + (var_fa1 * 0.5f));
    func_802FBD1C(arg0, arg0->unk651, arg0->unk5A8, 'x');

    var_fv1 = MAX(arg0->unk5A8, -45.0f);
    var_fv1 = MIN(var_fv1, 20.0f);

    if (arg0->unk5B8 < var_fv1) {
        arg0->unk5B8 = arg0->unk5B8 + (240.0f * D_8034F854 * 0.4f);
    }
    if (var_fv1 < arg0->unk5B8) {
        arg0->unk5B8 -= 240.0f * D_8034F854 * 0.4f;
    }
    func_802FBD1C(arg0, arg0->unk653, arg0->unk5B8, 'x');
}

void func_802FE9DC(JumbleHopperData* arg0, f32 arg1) {
    if (arg1 > 0.1f) {
        arg1 = 0.1f;
    } else if (arg1 < -0.1f) {
        arg1 = -0.1f;
    }
    arg0->unk5CC += arg1 * 25.0f;

    if (arg0->unk5CC > 15.0f) {
        arg0->unk5CC = 15.0f;
        func_802FBA44(arg0, 15.0f, 0, 0);
    } else if (arg0->unk5CC < -30.0f) {
        arg0->unk5CC = -30.0f;
        func_802FBA44(arg0, -30.0f, 1, 0);
    }
    func_802FBD1C(arg0, arg0->unk657, arg0->unk5CC, 'x');
}

void func_802FEAD0(JumbleHopperData* arg0, f32 arg1) {
    if (arg1 > 0.1f) {
        arg1 = 0.1f;
    } else if (arg1 < -0.1f) {
        arg1 = -0.1f;
    }
    arg0->unk5D4 += arg1 * 25.0f;

    if (arg0->unk5D4 > 15.0f) {
        arg0->unk5D4 = 15.0f;
        func_802FBB58(arg0, 15.0f, 0, 0);
    } else if (arg0->unk5D4 < -30.0f) {
        arg0->unk5D4 = -30.0f;
        func_802FBB58(arg0, -30.0f, 1, 0);
    }
    func_802FBD1C(arg0, arg0->unk654, arg0->unk5D4, 'x');
}

void func_802FEBC4(JumbleHopperData* arg0) {
    f32 var_fv1;
    f32 temp_fv1;

    arg0->unk570 += 200.0f * D_8034F854;

    if (arg0->unk570 > 360.0f) {
        arg0->unk570 -= 360.0f;
    }

    if (arg0->unk57C == 3) {
        arg0->unk574 *= 0.99f * arg0->unk578;
        temp_fv1 = 145.0f;
        arg0->unk5CC = (uvCosF(arg0->unk570 * 0.0174533f) * (temp_fv1 * 0.5f) * arg0->unk574) + (-55.0f + (temp_fv1 * 0.5f));
    } else if (arg0->unk57C == 2) {
        arg0->unk574 *= 0.99f * arg0->unk578;
        temp_fv1 = 110.0f;
        arg0->unk5CC = (uvCosF(arg0->unk570 * 0.0174533f) * (temp_fv1 * 0.5f) * arg0->unk574) + (-55.0f + (temp_fv1 * 0.5f));
    } else if (arg0->unk57C == 1) {
        arg0->unk574 *= 0.985f * arg0->unk578;
        temp_fv1 = 80.0f;
        arg0->unk5CC = (uvCosF(arg0->unk570 * 0.0174533f) * (temp_fv1 * 0.5f) * arg0->unk574) + (-45.0f + (temp_fv1 * 0.5f));
    } else {
        arg0->unk574 *= 0.985f * arg0->unk578;
        temp_fv1 = 45.0f;
        arg0->unk5CC = (uvCosF(arg0->unk570 * 0.0174533f) * (temp_fv1 * 0.5f) * arg0->unk574) + (-30.0f + (temp_fv1 * 0.5f));
    }
    func_802FBD1C(arg0, arg0->unk657, arg0->unk5CC, 'x');

    if (arg0->unk5CC < 0.0f) {
        var_fv1 = arg0->unk5CC;
    } else {
        var_fv1 = 0.0f;
    }

    if (arg0->unk5C0 < var_fv1) {
        arg0->unk5C0 += 200.0f * D_8034F854 * 0.4f;
    }
    if (var_fv1 < arg0->unk5C0) {
        arg0->unk5C0 -= 200.0f * D_8034F854 * 0.4f;
    }
    func_802FBD1C(arg0, arg0->unk658, arg0->unk5C0, 'x');
}

void func_802FEEC0(JumbleHopperData* arg0) {
    f32 var_fv1;
    f32 temp_fv1;

    arg0->unk580 += 200.0f * D_8034F854;

    if (arg0->unk580 > 360.0f) {
        arg0->unk580 -= 360.0f;
    }

    if (arg0->unk58C == 3) {
        arg0->unk584 *= 0.99f * arg0->unk588;
        temp_fv1 = 145.0f;
        arg0->unk5D4 = (uvCosF(arg0->unk580 * 0.0174533f) * (temp_fv1 * 0.5f) * arg0->unk584) + (-55.0f + (temp_fv1 * 0.5f));
    } else if (arg0->unk58C == 2) {
        arg0->unk584 *= 0.99f * arg0->unk588;
        temp_fv1 = 110.0f;
        arg0->unk5D4 = (uvCosF(arg0->unk580 * 0.0174533f) * (temp_fv1 * 0.5f) * arg0->unk584) + (-55.0f + (temp_fv1 * 0.5f));
    } else if (arg0->unk58C == 1) {
        arg0->unk584 *= 0.985f * arg0->unk588;
        temp_fv1 = 80.0f;
        arg0->unk5D4 = (uvCosF(arg0->unk580 * 0.0174533f) * (temp_fv1 * 0.5f) * arg0->unk584) + (-45.0f + (temp_fv1 * 0.5f));
    } else {
        arg0->unk584 *= 0.985f * arg0->unk588;
        temp_fv1 = 45.0f;
        arg0->unk5D4 = (uvCosF(arg0->unk580 * 0.0174533f) * (temp_fv1 * 0.5f) * arg0->unk584) + (-30.0f + (temp_fv1 * 0.5f));
    }
    func_802FBD1C(arg0, arg0->unk654, arg0->unk5D4, 'x');

    if (arg0->unk5D4 < 0.0f) {
        var_fv1 = arg0->unk5D4;
    } else {
        var_fv1 = 0.0f;
    }

    if (arg0->unk5C4 < var_fv1) {
        arg0->unk5C4 += 200.0f * D_8034F854 * 0.4f;
    }
    if (var_fv1 < arg0->unk5C4) {
        arg0->unk5C4 -= 200.0f * D_8034F854 * 0.4f;
    }
    func_802FBD1C(arg0, arg0->unk655, arg0->unk5C4, 'x');
}

void func_802FF1BC(JumbleHopperData* arg0) {
    f32 temp;
    f32 var_fa1;

    var_fa1 = FABS(arg0->unk540);

    if (arg0->unk598 < 0) {
        arg0->unk598 += 10.0 * D_8034F854 * 3.0;
        if (arg0->unk598 > 0) {
            arg0->unk598 = 0;
        }
        func_802FBD1C(arg0, arg0->unk65B, arg0->unk598, 'z');
    } else if (arg0->unk598 > 0) {
        arg0->unk598 -= 10.0 * D_8034F854 * 3.0;
        if (arg0->unk598 < 0) {
            arg0->unk598 = 0;
        }
        func_802FBD1C(arg0, arg0->unk65B, arg0->unk598, 'z');
    }
    if (arg0->unk594 < 0) {
        arg0->unk594 += 10.0 * D_8034F854 * 3.0;
        if (arg0->unk594 > 0) {
            arg0->unk594 = 0;
        }
    } else if (arg0->unk594 > 0) {
        arg0->unk594 -= 10.0 * D_8034F854 * 3.0;
        if (arg0->unk594 < 0) {
            arg0->unk594 = 0;
        }
    }

    if (arg0->unk140.y < 0) {
        temp = (((2.0f * var_fa1) / 60.0) + 1.0);
        arg0->unk140.y += 10.0 * D_8034F854 * temp;
        if (arg0->unk140.y > 0) {
            arg0->unk140.y = 0;
        }
    } else if (arg0->unk140.y > 0) {
        temp = (((2.0f * var_fa1) / 60.0) + 1.0);
        arg0->unk140.y -= 10.0 * D_8034F854 * temp;
        if (arg0->unk140.y < 0) {
            arg0->unk140.y = 0;
        }
    }

    if (arg0->unk140.z < 0) {
        temp = (((2.0f * var_fa1) / 60.0) + 1.0);
        arg0->unk140.z += 10.0 * D_8034F854 * temp;
        if (arg0->unk140.z > 0) {
            arg0->unk140.z = 0;
        }
    } else if (arg0->unk140.z > 0) {
        temp = (((2.0f * var_fa1) / 60.0) + 1.0);
        arg0->unk140.z -= 10.0 * D_8034F854 * temp;
        if (arg0->unk140.z < 0) {
            arg0->unk140.z = 0;
        }
    }
}

void func_802FF5B4(JumbleHopperData* arg0) {
    func_802FBD1C(arg0, arg0->unk65C, arg0->unk594, 'x');
    arg0->unk5CC = arg0->unk594;
    arg0->unk5D4 = arg0->unk594;
    func_802FBD1C(arg0, arg0->unk657, arg0->unk594, 'x');
    func_802FBD1C(arg0, arg0->unk654, arg0->unk5D4, 'x');
    arg0->unk5C0 = -arg0->unk594;
    arg0->unk5C4 = -arg0->unk594;
    func_802FBD1C(arg0, arg0->unk658, -arg0->unk594, 'x');
    func_802FBD1C(arg0, arg0->unk655, arg0->unk5C4, 'x');
}

void func_802FF654(JumbleHopperData* arg0) {
    f32 var_fa0;

    if (arg0->unk1AC == 0) {
        return;
    }

    switch (arg0->unk1A4) {
    case 0:
        var_fa0 = FABS(uvSinF(arg0->unk140.y * 0.0174533f * 0.5f));
        arg0->unk1A8 = var_fa0 + 0.3f;
        arg0->unk140.y -= 300.0f * D_8034F854 * arg0->unk1A8;
        if (arg0->unk140.y < -180.0f) {
            arg0->unk594 = (arg0->unk140.y + 360.0f) * 0.5f;
            if (arg0->unk1AC >= 2) {
                arg0->unk1A4 = 1;
                sndPlaySfx(SFX_UNK_091);
                func_802FF5B4(arg0);
                break;
            }
            if (arg0->unk140.y < -240.0f) {
                arg0->unk1A4 = 3;
                sndPlaySfx(SFX_UNK_091);
                func_802FB8CC(arg0, arg0->unk5A0, 0, 0);
                func_802FB988(arg0, arg0->unk5A8, 0, 0);
                func_802FBA44(arg0, arg0->unk5CC, 0, 3);
                func_802FBB58(arg0, arg0->unk5D4, 0, 3);
            }
            func_802FBD1C(arg0, arg0->unk65C, arg0->unk594, 'x');
            break;
        }
        arg0->unk594 = arg0->unk140.y * -0.5f;
        func_802FF5B4(arg0);
        break;
    case 1:
        arg0->unk140.y -= 300.0f * D_8034F854 * arg0->unk1A8;
        if (arg0->unk140.y < -360.0f) {
            arg0->unk140.y += 360.0f;
            arg0->unk1A4 = 2;
            arg0->unk1AC--;
        }
        break;
    case 2:
        arg0->unk140.y -= 300.0f * D_8034F854 * arg0->unk1A8;
        if (arg0->unk140.y < -240.0f) {
            arg0->unk1A4 = 3;
            sndPlaySfx(SFX_UNK_091);
            func_802FB8CC(arg0, arg0->unk5A0, 0, 0);
            func_802FB988(arg0, arg0->unk5A8, 0, 0);
            func_802FBA44(arg0, arg0->unk5CC, 0, 3);
            func_802FBB58(arg0, arg0->unk5D4, 0, 3);
            arg0->unk594 = (arg0->unk140.y + 360.0f) * 0.5f;
            func_802FBD1C(arg0, arg0->unk65C, arg0->unk594, 'x');
        }
        break;
    case 3:
        var_fa0 = FABS(uvSinF(arg0->unk140.y * 0.0174533f * 0.5f));
        arg0->unk1A8 = var_fa0 + 0.3f;
        arg0->unk140.y -= 300.0f * D_8034F854 * arg0->unk1A8;
        if (arg0->unk140.y < -330.0f) {
            arg0->unk594 = (arg0->unk140.y + 360.0f) * 0.5f;
            arg0->unk140.y += 360.0f;
            arg0->unk1AC--;
        } else {
            arg0->unk594 = (arg0->unk140.y + 360.0f) * 0.5f;
        }
        func_802FBD1C(arg0, arg0->unk65C, arg0->unk594, 'x');
        func_802FE564(arg0);
        func_802FE7A0(arg0);
        func_802FEBC4(arg0);
        func_802FEEC0(arg0);
        break;
    }
}

void func_802FFB3C(JumbleHopperData* arg0) {
    f32 var_fa0;

    if (arg0->unk1B0 == 0) {
        return;
    }

    switch (arg0->unk1A4) {
    case 0:
        var_fa0 = FABS(uvSinF(arg0->unk140.y * 0.0174533f * 0.5f));
        arg0->unk1A8 = var_fa0 + 0.3f;
        arg0->unk140.y += 300.0f * D_8034F854 * arg0->unk1A8;
        if (arg0->unk140.y > 180.0f) {
            arg0->unk594 = (360.0f - arg0->unk140.y) * 0.5f;
            if (arg0->unk1B0 >= 2) {
                arg0->unk1A4 = 1;
                sndPlaySfx(SFX_UNK_091);
                func_802FF5B4(arg0);
                break;
            }
            if (arg0->unk140.y > 180.0f) {
                arg0->unk1A4 = 3;
                sndPlaySfx(SFX_UNK_091);
                func_802FB8CC(arg0, arg0->unk5A0, 0, 0);
                func_802FB988(arg0, arg0->unk5A8, 0, 0);
                func_802FBA44(arg0, arg0->unk5CC, 0, 3);
                func_802FBB58(arg0, arg0->unk5D4, 0, 3);
            }
            func_802FBD1C(arg0, arg0->unk65C, arg0->unk594, 'x');
            break;
        }
        arg0->unk594 = arg0->unk140.y * 0.5f;
        func_802FF5B4(arg0);
        break;
    case 1:
        arg0->unk140.y += 300.0f * D_8034F854 * arg0->unk1A8;
        if (arg0->unk140.y > 360.0f) {
            arg0->unk140.y -= 360.0f;
            arg0->unk1A4 = 2;
            arg0->unk1B0--;
        }
        break;
    case 2:
        arg0->unk140.y += 300.0f * D_8034F854 * arg0->unk1A8;
        if (arg0->unk140.y > 180.0f) {
            arg0->unk1A4 = 3;
            sndPlaySfx(SFX_UNK_091);
            func_802FB8CC(arg0, arg0->unk5A0, 0, 0);
            func_802FB988(arg0, arg0->unk5A8, 0, 0);
            func_802FBA44(arg0, arg0->unk5CC, 0, 3);
            func_802FBB58(arg0, arg0->unk5D4, 0, 3);
            arg0->unk594 = (360.0f - arg0->unk140.y) * 0.5f;
            func_802FBD1C(arg0, arg0->unk65C, arg0->unk594, 'x');
        }
        break;
    case 3:
        var_fa0 = FABS(uvSinF(arg0->unk140.y * 0.0174533f * 0.5f));
        arg0->unk1A8 = var_fa0 + 0.3f;
        arg0->unk140.y += 300.0f * D_8034F854 * arg0->unk1A8;
        if (arg0->unk140.y > 330.0f) {
            arg0->unk594 = (360.0f - arg0->unk140.y) * 0.5f;
            arg0->unk140.y -= 360.0f;
            arg0->unk1B0--;
        } else {
            arg0->unk594 = (360.0f - arg0->unk140.y) * 0.5f;
        }
        func_802FBD1C(arg0, arg0->unk65C, arg0->unk594, 'x');
        func_802FE564(arg0);
        func_802FE7A0(arg0);
        func_802FEBC4(arg0);
        func_802FEEC0(arg0);
        break;
    }
}

void func_80300018(JumbleHopperData* arg0) {
    f32 sp24;

    func_802FE2FC(arg0);
    if (arg0->unk1AC != 0) {
        func_802FF654(arg0);
        return;
    }
    if (arg0->unk1B0 != 0) {
        func_802FFB3C(arg0);
        return;
    }
    if (arg0->unk1A0 == 0) {
        if (arg0->unk50 != 0) {
            func_802FF1BC(arg0);
        }
        if (arg0->unk15C.z > 0.0) {
            sp24 = D_8034F854 * 390.0 * arg0->unk180 * 0.2;
            if (arg0->unk198 != 0) {
                arg0->unk5A0 += sp24;
                if (arg0->unk5A0 > 150.0f) {
                    arg0->unk5A0 = 150.0f;
                }
                func_802FBD1C(arg0, arg0->unk650, arg0->unk5A0, 'x');
                arg0->unk5A8 += sp24;
                if (arg0->unk5A8 > 150.0f) {
                    arg0->unk5A8 = 150.0f;
                }
                func_802FBD1C(arg0, arg0->unk651, arg0->unk5A8, 'x');
                func_802FB8CC(arg0, arg0->unk5A0, 0, 1);
                func_802FB988(arg0, arg0->unk5A8, 0, 1);
                arg0->unk5B0 -= sp24;
                if (arg0->unk5B0 < -45.0f) {
                    arg0->unk5B0 = -45.0f;
                }
                func_802FBD1C(arg0, arg0->unk652, arg0->unk5B0, 'x');
                arg0->unk5B8 -= sp24;
                if (arg0->unk5B8 < -45.0f) {
                    arg0->unk5B8 = -45.0f;
                }
                func_802FBD1C(arg0, arg0->unk653, arg0->unk5B8, 'x');
                func_802FEBC4(arg0);
                func_802FEEC0(arg0);
            } else if (FABS(arg0->unk14) > 0.1f) {
                func_802FDF8C(arg0, arg0->unk14);
                func_802FE054(arg0, arg0->unk14);
                func_802FE1A8(arg0, -arg0->unk14);
                func_802FE9DC(arg0, arg0->unk14);
                func_802FEAD0(arg0, -arg0->unk14);
            } else {
                func_802FE564(arg0);
                func_802FE7A0(arg0);
                func_802FEBC4(arg0);
                func_802FEEC0(arg0);
            }
        } else if (arg0->unk198 != 0) {
            func_802FE564(arg0);
            func_802FE7A0(arg0);
            func_802FEBC4(arg0);
            func_802FEEC0(arg0);
        } else if (FABS(arg0->unk14) > 0.1f) {
            func_802FDF8C(arg0, arg0->unk14);
            func_802FE054(arg0, arg0->unk14);
            func_802FE1A8(arg0, -arg0->unk14);
            func_802FE9DC(arg0, arg0->unk14);
            func_802FEAD0(arg0, -arg0->unk14);
        } else {
            func_802FE564(arg0);
            func_802FE7A0(arg0);
            func_802FEBC4(arg0);
            func_802FEEC0(arg0);
        }
    } else if (arg0->unk50 != 0) {
        func_802FF1BC(arg0);
        func_802FE564(arg0);
        func_802FE7A0(arg0);
        func_802FEBC4(arg0);
        func_802FEEC0(arg0);
    }
}

void func_80300448(JumbleHopperData* arg0) {
    Vec3F sp34 = { 0.0f, 0.0f, -1.0f };
    Vec3F sp28;

    uvVec3Cross(&sp28, &sp34, &arg0->unk168);
    uvVec3Cross(&arg0->unk15C, &arg0->unk168, &sp28);
    func_8034B2B0(&arg0->unk15C);
    if (arg0->unk15C.z > 0.0f) {
        arg0->unk15C.x *= -1.0f;
        arg0->unk15C.y *= -1.0f;
        arg0->unk15C.z *= -1.0f;
        arg0->unk168.x *= -1.0f;
        arg0->unk168.y *= -1.0f;
        arg0->unk168.z *= -1.0f;
    }
    arg0->unk15C.x *= arg0->unk180;
    arg0->unk15C.y *= arg0->unk180;
    arg0->unk15C.z *= arg0->unk180;
}

s32 func_8030055C(JumbleHopperData* arg0) {
    Vec3F sp2C;
    f32 var_fv1;

    uvVec3Copy(&sp2C, &arg0->unk15C);
    if (func_8034B2B0(&sp2C) > 15.0f) {
        if (uvVec3Dot(&arg0->unk168, &arg0->unk15C) > 0.0f) {
            var_fv1 = uvVec3Dot(&arg0->unk168, &arg0->unk15C);
        } else {
            var_fv1 = -uvVec3Dot(&arg0->unk168, &arg0->unk15C);
        }
        if (var_fv1 < 0.6f) {
            return 0;
        }
        return 1;
    }
    return 0;
}

void func_80300624(JumbleHopperData* arg0) {
    if ((func_8034AF48(arg0->unk100, arg0->unkF4) < 1.0f) && (uvVec3Dot(&arg0->unk168, &arg0->unk174) < 0.0)) {
        func_802FCC0C(arg0);
    }
    arg0->unk100.x = arg0->unkF4.x;
    arg0->unk100.y = arg0->unkF4.y;
    arg0->unk100.z = arg0->unkF4.z;
}

void func_803006E8(JumbleHopperData* arg0) {
    s32 sp44;
    Vec3F sp38;
    Vec3F sp2C;

    sp44 = func_802FCA8C(arg0, &sp38, &sp2C);
    if (sp44 == 0) {
        func_802FB82C(arg0);
        arg0->unk64 = (arg0->unkF4.z - arg0->unk6C) - arg0->unk68;
        return;
    }
    arg0->unk168.x = sp2C.x;
    arg0->unk168.y = sp2C.y;
    arg0->unk168.z = sp2C.z;
    func_8034B2B0(&arg0->unk168);
    arg0->unkF4.x = arg0->unk134.x + (arg0->unk168.x * 0.5f);
    arg0->unkF4.y = arg0->unk134.y + (arg0->unk168.y * 0.5f);
    arg0->unkF4.z = arg0->unk134.z + (arg0->unk168.z * 0.5f);
    func_802FC8B0(arg0);
    arg0->unk50 = 0;
    arg0->unk68 = arg0->unk134.z;
    arg0->unk64 = 0.0f;
    switch (sp44) {
    case 2:
    case 3:
        arg0->unk4C = 6;
        arg0->unkF4.x = arg0->unk670.x;
        arg0->unkF4.y = arg0->unk670.y;
        arg0->unkF4.z = arg0->unk670.z;
        func_802FBEFC(arg0, arg0->unk134.z);
        break;
    default:
        if (func_802FB784(arg0, 0.70710677f) == 0) {
            arg0->unk4C = 6;
            sndPlaySfx(SFX_UNK_054);
        } else if ((uvVec3Dot(&arg0->unk168, &arg0->unk174) < 0.0f) && (arg0->unk4D == 4)) {
            sndPlaySfx(SFX_UNK_054);
            func_802FCC0C(arg0);
        } else {
            func_80300448(arg0);
            func_80300624(arg0);
        }
        break;
    }
}

void func_8030089C(JumbleHopperData* arg0) {
    s32 sp44;
    Vec3F sp38;
    Vec3F sp2C;

    sp44 = func_802FCA8C(arg0, &sp38, &sp2C);
    if (sp44 == 0) {
        func_802FB82C(arg0);
        arg0->unk64 = (arg0->unkF4.z - arg0->unk6C) - arg0->unk68;
        return;
    }
    arg0->unk168.x = sp2C.x;
    arg0->unk168.y = sp2C.y;
    arg0->unk168.z = sp2C.z;
    func_8034B2B0(&arg0->unk168);
    arg0->unkF4.x = arg0->unk134.x + (arg0->unk168.x * 0.5f);
    arg0->unkF4.y = arg0->unk134.y + (arg0->unk168.y * 0.5f);
    arg0->unkF4.z = arg0->unk134.z + (arg0->unk168.z * 0.5f);
    func_802FC8B0(arg0);
    if (arg0->unk168.z < 0.0f) {
        sndPlaySfx(SFX_UNK_054);
        func_802FD55C(arg0, arg0->unkF4);
        func_80300624(arg0);
        return;
    }

    arg0->unk50 = 0;
    arg0->unk64 = 0.0f;
    arg0->unk68 = arg0->unk134.z;
    switch (sp44) {
    case 2:
        arg0->unk4C = 6;
        arg0->unkF4.x = arg0->unk670.x;
        arg0->unkF4.y = arg0->unk670.y;
        arg0->unkF4.z = arg0->unk670.z;
        func_802FBEFC(arg0, arg0->unk134.z);
        break;
    case 3:
        func_802FC018(arg0);
        sndPlaySfx(0x39);
        arg0->unkF4.x = arg0->unk670.x;
        arg0->unkF4.y = arg0->unk670.y;
        arg0->unkF4.z = arg0->unk670.z;
        break;
    default:
        sndPlaySfx(SFX_UNK_054);
        if (func_802FB784(arg0, 0.70710677f) != 0) {
            if (func_8030055C(arg0) != 0) {
                func_802FD55C(arg0, arg0->unkF4);
                func_80300624(arg0);
            } else {
                arg0->unk4C = 4;
                func_80300448(arg0);
                func_80300624(arg0);
            }
            break;
        }
        if (func_802FB784(arg0, 0.9063078f) != 0) {
            arg0->unk4C = 4;
            func_80300448(arg0);
            func_80300624(arg0);
        } else {
            arg0->unk4C = 6;
        }
        break;
    }
}

void func_80300B04(JumbleHopperData* arg0) {
    s32 sp44;
    Vec3F sp38;
    Vec3F sp2C;

    sp44 = func_802FCA8C(arg0, &sp38, &sp2C);
    if (sp44 == 0) {
        func_802FB82C(arg0);
        arg0->unk64 = (arg0->unkF4.z - arg0->unk6C) - arg0->unk68;
        return;
    }
    arg0->unk168.x = sp2C.x;
    arg0->unk168.y = sp2C.y;
    arg0->unk168.z = sp2C.z;

    func_8034B2B0(&arg0->unk168);

    if (arg0->unk168.z < 0.0f) {
        arg0->unkF4.x = arg0->unk134.x + (arg0->unk168.x * 0.5f);
        arg0->unkF4.y = arg0->unk134.y + (arg0->unk168.y * 0.5f);
        arg0->unkF4.z = arg0->unk134.z + (arg0->unk168.z * 0.5f);
        func_802FC8B0(arg0);
        arg0->unk4C = 5;
        func_802FD55C(arg0, arg0->unkF4);
        sndPlaySfx(SFX_UNK_054);
        return;
    }
    arg0->unk50 = 0;
    arg0->unk64 = 0.0f;
    arg0->unk68 = arg0->unk134.z;
    switch (sp44) {
    case 2:
        arg0->unkF4.x = arg0->unk134.x;
        arg0->unkF4.y = arg0->unk134.y;
        arg0->unkF4.z = func_802FB660(arg0) + arg0->unk134.z;
        func_802FBEFC(arg0, arg0->unkF4.z - arg0->unk6C);
        func_802FBC6C(arg0);
        break;
    case 3:
        arg0->unk4C = 5;
        func_802FC018(arg0);
        sndPlaySfx(0x39);
        arg0->unkF4.x = arg0->unk670.x;
        arg0->unkF4.y = arg0->unk670.y;
        arg0->unkF4.z = arg0->unk670.z;
        break;
    default:
        if (func_802FB784(arg0, 0.70710677f) != 0) {
            arg0->unkF4.x = arg0->unk134.x + (arg0->unk168.x * 0.5f);
            arg0->unkF4.y = arg0->unk134.y + (arg0->unk168.y * 0.5f);
            arg0->unkF4.z = arg0->unk134.z + (arg0->unk168.z * 0.5f);
            func_802FC8B0(arg0);
            sndPlaySfx(SFX_UNK_054);
            if (func_8030055C(arg0) != 0) {
                arg0->unk4C = 5;
                func_802FD55C(arg0, arg0->unkF4);
            } else {
                arg0->unk4C = 4;
                func_80300448(arg0);
            }
            break;
        }

        if ((arg0->unk140.y > 45.0f) || (arg0->unk140.y < -45.0f)) {
            arg0->unk4C = 6;
            sndPlaySfx(SFX_UNK_054);
            arg0->unkF4.x = arg0->unk134.x + (arg0->unk168.x * 0.5f);
            arg0->unkF4.y = arg0->unk134.y + (arg0->unk168.y * 0.5f);
            arg0->unkF4.z = arg0->unk134.z + (arg0->unk168.z * 0.5f);
            func_802FC8B0(arg0);
        } else {
            func_802FBC6C(arg0);
            arg0->unkF4.x = arg0->unk134.x;
            arg0->unkF4.y = arg0->unk134.y;
            arg0->unkF4.z = func_802FB660(arg0) + arg0->unk134.z;
            func_8034AACC(&arg0->unk140, arg0->unk168);
        }
        break;
    }
}

void func_80300E78(JumbleHopperData* arg0) {
    Vec3F sp1C;
    f32 var_fv0;

    if (arg0->unk19C != 0) {
        arg0->unk1B8 += D_8034F854;
        if (arg0->unk1B8 < 1.5) {
            var_fv0 = arg0->unk194 * 8.25;
        } else {
            var_fv0 = 0.0f;
            arg0->unk19C = 0;
        }
    } else {
        var_fv0 = 0.0f;
    }
    arg0->unk14C.x = arg0->unk184.x * var_fv0;
    arg0->unk14C.y = arg0->unk184.y * var_fv0;
    arg0->unk14C.z = (arg0->unk184.z * var_fv0) - (9.8 * arg0->unk190);
    env_802E1754(arg0->unkF4.x, arg0->unkF4.y, arg0->unkF4.z, &sp1C);
    arg0->unk14C.x += sp1C.x * 0.25f;
    arg0->unk14C.y += sp1C.y * 0.25f;
    arg0->unk14C.z += sp1C.z * 0.25f;
    arg0->unk15C.x += 2.0f * (arg0->unk14C.x * D_8034F854);
    arg0->unk15C.y += 2.0f * (arg0->unk14C.y * D_8034F854);
    arg0->unk15C.z += 2.0f * (arg0->unk14C.z * D_8034F854);
    arg0->unkF4.x += 2.0 * (arg0->unk15C.x * D_8034F854);
    arg0->unkF4.y += 2.0 * (arg0->unk15C.y * D_8034F854);
    arg0->unkF4.z += 2.0 * (arg0->unk15C.z * D_8034F854);
    func_80300018(arg0);
    func_80300B04(arg0);
}

void func_80301090(JumbleHopperData* arg0) {
    f32 var_fv1;

    var_fv1 = (65.0 - arg0->unk53C) / 65.0;
    if (var_fv1 < 0.01) {
        var_fv1 = 0.01f;
    }
    arg0->unk15C.x = 0;
    arg0->unk15C.y = 0;
    arg0->unk15C.z = 0;
    arg0->unk14C.x = 0;
    arg0->unk14C.y = 0;
    arg0->unk14C.z = 0;
    arg0->unk53C += 650.0 * D_8034F854 * var_fv1;
    if (arg0->unk53C > 65.0) {
        arg0->unk4C = 0;
        arg0->unk53C = 65.0f;
    }
    arg0->unk594 = 0.0f;
    func_802FBD1C(arg0, arg0->unk65C, 0.0f, 'z');
    func_802FBD1C(arg0, arg0->unk65A, -arg0->unk53C * 0.5f, 'x');
    arg0->unk5A0 -= 650.0 * D_8034F854 * 1.222;
    if (arg0->unk5A0 < -55.0f) {
        arg0->unk5A0 = -55.0f;
    }
    func_802FBD1C(arg0, arg0->unk650, arg0->unk5A0, 'x');
    arg0->unk5A8 -= 650.0 * D_8034F854 * 1.222;
    if (arg0->unk5A8 < -55.0f) {
        arg0->unk5A8 = -55.0f;
    }
    func_802FBD1C(arg0, arg0->unk651, arg0->unk5A8, 'x');
    arg0->unk5B0 -= 2.0 * (650.0 * D_8034F854);
    if (arg0->unk5B0 < -45.0f) {
        arg0->unk5B0 = -45.0f;
    }
    func_802FBD1C(arg0, arg0->unk652, arg0->unk5B0, 'x');
    arg0->unk5B8 -= 2.0 * (650.0 * D_8034F854);
    if (arg0->unk5B8 < -45.0f) {
        arg0->unk5B8 = -45.0f;
    }
    func_802FBD1C(arg0, arg0->unk653, arg0->unk5B8, 'x');
    arg0->unk5CC = arg0->unk53C * 2;
    func_802FBD1C(arg0, arg0->unk657, arg0->unk5CC, 'x');
    arg0->unk5D4 = arg0->unk53C * 2;
    func_802FBD1C(arg0, arg0->unk654, arg0->unk5D4, 'x');
    arg0->unk5C0 = arg0->unk53C * -2;
    func_802FBD1C(arg0, arg0->unk658, arg0->unk5C0, 'x');
    arg0->unk5C4 = arg0->unk53C * -2;
    func_802FBD1C(arg0, arg0->unk655, arg0->unk5C4, 'x');
    func_802FD388(arg0);
    func_802FD3E0(arg0);
    arg0->unk5E0 = arg0->unk53C - 65.0;
    arg0->unk5D8 = ((-arg0->unk140.y - arg0->unk5C0) - arg0->unk5CC) + arg0->unk5E0;
    func_802FBD1C(arg0, arg0->unk659, arg0->unk5D8, 'x');
    arg0->unk5DC = ((-arg0->unk140.y - arg0->unk5C4) - arg0->unk5D4) + arg0->unk5E0;
    func_802FBD1C(arg0, arg0->unk656, arg0->unk5DC, 'x');
    arg0->unkF4.z = func_802FD010(arg0);
    func_802FCE38(arg0);
}

void func_803014A8(JumbleHopperData* arg0, f32 arg1) {
    arg0->unk140.x += 150.0 * D_8034F854 * 2 * arg1;
    if (arg0->unk140.x > 360.0f) {
        arg0->unk140.x -= 360.0f;
    }
    arg0->unk140.y += 150.0 * D_8034F854 * arg1;

    if (arg0->unk140.y > 360.0f) {
        arg0->unk140.y -= 360.0f;
    }
    arg0->unk140.z += 150.0 * D_8034F854 * arg1;
    if (arg0->unk140.z > 360.0f) {
        arg0->unk140.z -= 360.0f;
    }
    if (arg0->unk59C != 0) {
        arg0->unk5A0 += 150.0 * D_8034F854;
        if (arg0->unk5A0 > 90.0f) {
            arg0->unk59C = 0;
        }
    } else {
        arg0->unk5A0 -= 150.0 * D_8034F854;
        if (arg0->unk5A0 < -45.0f) {
            arg0->unk59C = 1;
        }
    }
    func_802FBD1C(arg0, arg0->unk650, arg0->unk5A0, 'x');
    if (arg0->unk5A4 != 0) {
        arg0->unk5A8 += 150.0 * D_8034F854;
        if (arg0->unk5A8 > 90.0f) {
            arg0->unk5A4 = 0;
        }
    } else {
        arg0->unk5A8 -= 150.0 * D_8034F854;
        if (arg0->unk5A8 < -45.0f) {
            arg0->unk5A4 = 1;
        }
    }
    func_802FBD1C(arg0, arg0->unk651, arg0->unk5A8, 'x');
    if (arg0->unk5AC != 0) {
        arg0->unk5B0 += 150.0 * D_8034F854;
        if (arg0->unk5B0 > 70.0f) {
            arg0->unk5AC = 0;
        }
    } else {
        arg0->unk5B0 -= 150.0 * D_8034F854;
        if (arg0->unk5B0 < 0.0f) {
            arg0->unk5AC = 1;
        }
    }
    func_802FBD1C(arg0, arg0->unk652, arg0->unk5B0, 'x');
    if (arg0->unk5B4 != 0) {
        arg0->unk5B8 += 150.0 * D_8034F854;
        if (arg0->unk5B8 > 70.0f) {
            arg0->unk5B4 = 0;
        }
    } else {
        arg0->unk5B8 -= 150.0 * D_8034F854;
        if (arg0->unk5B8 < 0.0f) {
            arg0->unk5B4 = 1;
        }
    }
    func_802FBD1C(arg0, arg0->unk653, arg0->unk5B8, 'x');
    if (arg0->unk5C8 != 0) {
        arg0->unk5CC += 150.0 * D_8034F854;
        if (arg0->unk5CC > 90.0f) {
            arg0->unk5C8 = 0;
        }
    } else {
        arg0->unk5CC -= 150.0 * D_8034F854;
        if (arg0->unk5CC < 0.0f) {
            arg0->unk5C8 = 1;
        }
    }
    func_802FBD1C(arg0, arg0->unk657, arg0->unk5CC, 'x');
    if (arg0->unk5D0 != 0) {
        arg0->unk5D4 += 150.0 * D_8034F854;
        if (arg0->unk5D4 > 90.0f) {
            arg0->unk5D0 = 0;
        }
    } else {
        arg0->unk5D4 -= 150.0 * D_8034F854;
        if (arg0->unk5D4 < 0.0f) {
            arg0->unk5D0 = 1;
        }
    }
    func_802FBD1C(arg0, arg0->unk654, arg0->unk5D4, 'x');
    if (arg0->unk5BC != 0) {
        arg0->unk5C0 += 150.0 * D_8034F854;
        if (arg0->unk5C0 > -0.0f) {
            arg0->unk5BC = 0;
        }
        arg0->unk5C4 = arg0->unk5C0;
    } else {
        arg0->unk5C0 -= 150.0 * D_8034F854;
        if (arg0->unk5C0 < -45.0f) {
            arg0->unk5BC = 1;
        }
        arg0->unk5C4 = arg0->unk5C0;
    }
    func_802FBD1C(arg0, arg0->unk658, arg0->unk5C0, 'x');
    func_802FBD1C(arg0, arg0->unk655, arg0->unk5C4, 'x');
}

void func_80301AF8(JumbleHopperData* arg0) {
    Vec3F sp24;

    uvVec3Copy(&sp24, &arg0->unk15C);
    func_8034B2B0(&sp24);
    arg0->unk14C.x = sp24.x * 9.8;
    arg0->unk14C.y = sp24.y * 9.8;
    arg0->unk14C.z = sp24.z * 9.8;
    arg0->unk15C.x += 2.0f * (arg0->unk14C.x * D_8034F854);
    arg0->unk15C.y += 2.0f * (arg0->unk14C.y * D_8034F854);
    arg0->unk15C.z += 2.0f * (arg0->unk14C.z * D_8034F854);
    arg0->unkF4.x += 2.0f * (arg0->unk15C.x * D_8034F854);
    arg0->unkF4.y += 2.0f * (arg0->unk15C.y * D_8034F854);
    arg0->unkF4.z += 2.0f * (arg0->unk15C.z * D_8034F854);
    func_803006E8(arg0);
    func_803014A8(arg0, 0.5f);
    arg0->unk18->unk108.m[3][2] += 2.0f * D_8034F854;
}

void func_80301C58(JumbleHopperData* arg0) {
    arg0->unk14C.z = -9.8f;
    arg0->unk15C.z += 2.0f * (-9.8f * D_8034F854);
    arg0->unkF4.x += 2.0f * (arg0->unk15C.x * D_8034F854);
    arg0->unkF4.y += 2.0f * (arg0->unk15C.y * D_8034F854);
    arg0->unkF4.z += 2.0f * (arg0->unk15C.z * D_8034F854);
    func_8030089C(arg0);
    func_803014A8(arg0, 1.0f);
    arg0->unk18->unk108.m[3][2] += 2.0f * D_8034F854;
}

void func_80301D28(JumbleHopperData* arg0) {
    Vec3F sp34;
    Vec3F sp28;
    s32 pad;

    arg0->unk4C = 7;
    arg0->unk538++;
    arg0->unk65D = 0;
    arg0->unk1C0 = 0.0;
    shadow_803343D8(0);
    arg0->unk1B8 = 0.0;
    arg0->unk50 = 0;
    arg0->unk4F = 0;
    arg0->unk1AC = 0;
    arg0->unk1B0 = 0;
    arg0->unk53C = 0.0f;
    arg0->unkF4.x = arg0->unk134.x + (arg0->unk168.x * 0.5f * 0.5f);
    arg0->unk540 = 0.0f;
    arg0->unk5DC = 0.0f;
    arg0->unk5D8 = 0.0f;
    arg0->unk5C0 = 0.0f;
    arg0->unk5C4 = 0.0f;
    arg0->unkF4.y = arg0->unk134.y + (arg0->unk168.y * 0.5f * 0.5f);
    arg0->unk5A0 = 0.0f;
    arg0->unk5A8 = 0.0f;
    arg0->unk5E0 = 0.0f;
    arg0->unk5D4 = 0.0f;
    arg0->unk5CC = 0.0f;
    arg0->unk6C = 0.0f;
    arg0->unk5B0 = -45.0f;
    arg0->unkF4.z = arg0->unk134.z + (arg0->unk168.z * 0.5f * 0.5f);
    arg0->unk5B8 = -45.0f;
    func_802FC8B0(arg0);
    arg0->unk15C.x = arg0->unk15C.y = arg0->unk15C.z = 0.0f;
    arg0->unk14C.x = arg0->unk14C.y = arg0->unk14C.z = 0.0f;
    arg0->unk184.x = arg0->unk184.y = arg0->unk184.z = 0.0f;
    arg0->unk544 = 0.0f;
    arg0->unk20 = arg0->unk18->unk108.m[3][2];
    arg0->unk1D0 = 0.0f;
    uvDobj_802180DC(arg0->objId, &arg0->unk1D4);
    func_8034AF94(&arg0->unk18->unk108, &sp28, &sp34);
    if (sp34.y > 180.0f) {
        sp34.y -= 360.0f;
    }
    if (sp34.z > 180.0f) {
        sp34.z -= 360.0f;
    }
    if (sp34.y > 90.0f) {
        sp34.x += 180.0f;
        sp34.y = 180.0f - sp34.y;
        arg0->unk2C = sp34.z + 180.0f;
    } else if (sp34.y < -90.0f) {
        sp34.x += 180.0f;
        sp34.y = -180.0f - sp34.y;
        arg0->unk2C = sp34.z + 180.0f;
    } else {
        arg0->unk2C = sp34.z;
    }
}

void func_80301F70(JumbleHopperData* arg0) {
    Unk80371120 sp40;
    s32 i;
    f32 temp_fa0 = 20.0f;

    if (arg0->unk140.y < -90.0f) {
        arg0->unk140.y += 360.0f;
    } else if (arg0->unk140.y > 270.0f) {
        arg0->unk140.y -= 360.0f;
    }
    if (arg0->unk140.y < 90.0f) {
        arg0->unk140.y += 10.0 * D_8034F854 * temp_fa0;
        if (arg0->unk140.y > 90.0f) {
            arg0->unk140.y = 90.0f;
        }
    } else if (arg0->unk140.y > 90.0f) {
        arg0->unk140.y -= 10.0 * D_8034F854 * temp_fa0;
        if (arg0->unk140.y < 90.0f) {
            arg0->unk140.y = 0.0f;
        }
    }

    if (arg0->unk140.z < -180.0f) {
        arg0->unk140.z += 360.0f;
    } else if (arg0->unk140.z > 180.0f) {
        arg0->unk140.z -= 360.0f;
    }
    if (arg0->unk140.z < 0.0f) {
        arg0->unk140.z += 10.0 * D_8034F854 * temp_fa0;
        if (arg0->unk140.z > 0.0f) {
            arg0->unk140.z = 0.0f;
        }
    } else if (arg0->unk140.z > 0.0f) {
        arg0->unk140.z -= 10.0 * D_8034F854 * temp_fa0;
        if (arg0->unk140.z < 0.0f) {
            arg0->unk140.z = 0.0f;
        }
    }
    arg0->unk1D0 += D_8034F854 * 0.5 * temp_fa0;
    func_802006FC(&sp40, &arg0->unk1D4, &arg0->unk384, arg0->unk1D0);
    func_80200638(arg0->objId, &sp40);
    if ((arg0->unk1D0 > 1.0f) && (arg0->unk140.y == 90.0f) && (arg0->unk140.z == 0.0f)) {
        // clang-format off
        for (i = 0; i < ARRAY_COUNT(D_8036905C); i++) { D_8036905C[i] = 0; }
        // clang-format on
        arg0->unk4C = 8;
        arg0->unk1C0 = 0.0;
        arg0->unk30.x = arg0->unkF4.x - arg0->unk18->unk108.m[3][0];
        arg0->unk30.y = arg0->unkF4.y - arg0->unk18->unk108.m[3][1];
        arg0->unk30.z = arg0->unkF4.z - arg0->unk18->unk108.m[3][2];
        arg0->unk1C = func_8034B2B0(&arg0->unk30);
        arg0->unk24 = func_8034A9A0(arg0->unk30.y, arg0->unk30.x) * RADIAN_TO_ANGLE_FACTOR;
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
        arg0->unk1D0 = 0.0f;
    } else {
        arg0->unk18->unk108.m[3][2] += 2.0f * D_8034F854;
    }
}

void func_80302484(JumbleHopperData* arg0) {
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 temp_fv0;

    if (arg0->unk65D == 0) {
        arg0->unk24 += 100.0f * D_8034F854 * arg0->unk28;
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

        if (arg0->unk28 > 0.0f) {
            if (arg0->unk140.x < arg0->unk24 + 270.0f) {
                arg0->unk65D = 1;
                arg0->unk24 = arg0->unk140.x - 270.0f;
            }
        } else {
            if (arg0->unk24 + 270.0f < arg0->unk140.x) {
                arg0->unk65D = 1;
                arg0->unk24 = arg0->unk140.x - 270.0f;
            }
        }
    }

    if (arg0->unk18->unk1374 < arg0->unk1C) {
        arg0->unk1C -= 50.0f * D_8034F854;
        if (arg0->unk1C < arg0->unk18->unk1374) {
            arg0->unk1C = arg0->unk18->unk1374;
        }
    } else if (arg0->unk1C < arg0->unk18->unk1374) {
        arg0->unk1C += 50.0f * D_8034F854;
        if (arg0->unk18->unk1374 < arg0->unk1C) {
            arg0->unk1C = arg0->unk18->unk1374;
        }
    }
    arg0->unk18->unk108.m[3][0] = (-uvCosF(arg0->unk24 * 0.0174533f) * arg0->unk1C) + arg0->unkF4.x;
    arg0->unk18->unk108.m[3][1] = (-uvSinF(arg0->unk24 * 0.0174533f) * arg0->unk1C) + arg0->unkF4.y;

    arg0->unk20 -= 50.0f * D_8034F854;
    if (arg0->unk20 < arg0->unk68 + 1.0f) {
        arg0->unk20 = arg0->unk68 + 1.0f;
    }

    if (arg0->unk20 < arg0->unkF4.z) {
        arg0->unk20 = arg0->unkF4.z;
    }
    arg0->unk18->unk108.m[3][2] = arg0->unk20;

    if (arg0->unk2C > 0.0f) {
        arg0->unk2C -= 100.0f * D_8034F854;
        if (arg0->unk2C < 0.0f) {
            arg0->unk2C = 0.0f;
        }
    } else if (arg0->unk2C < 0.0f) {
        arg0->unk2C += 100.0f * D_8034F854;
        if (arg0->unk2C > 0.0f) {
            arg0->unk2C = 0.0f;
        }
    }

    sp2C = (arg0->unk18->unk108.m[3][2] - arg0->unkF4.z) / arg0->unk1C;
    sp28 = uvSqrtF(SQ(arg0->unk18->unk108.m[3][0] - arg0->unkF4.x) + SQ(arg0->unk18->unk108.m[3][1] - arg0->unkF4.y)) / arg0->unk1C;
    sp34 = uvSinF((arg0->unk24 + 270.0f) * 0.0174533f);
    sp30 = uvCosF((arg0->unk24 + 270.0f) * 0.0174533f);
    sp24 = uvSinF(arg0->unk2C * 0.0174533f);
    temp_fv0 = uvCosF(arg0->unk2C * 0.0174533f);
    arg0->unk18->unk108.m[0][0] = (temp_fv0 * sp30) - (sp24 * sp2C * sp34);
    arg0->unk18->unk108.m[0][1] = (temp_fv0 * sp34) + (sp24 * sp2C * sp30);
    arg0->unk18->unk108.m[0][2] = -sp24 * sp28;
    arg0->unk18->unk108.m[1][0] = -sp28 * sp34;
    arg0->unk18->unk108.m[1][1] = sp28 * sp30;
    arg0->unk18->unk108.m[1][2] = sp2C;
    arg0->unk18->unk108.m[2][0] = (sp24 * sp30) + (temp_fv0 * sp2C * sp34);
    arg0->unk18->unk108.m[2][1] = (sp24 * sp34) - (temp_fv0 * sp2C * sp30);
    arg0->unk18->unk108.m[2][2] = temp_fv0 * sp28;
}

void func_803029CC(JumbleHopperData* arg0) {
    s32 sp24;

    arg0->unk1C0 += D_8034F854;
    sp24 = 0;
    if (arg0->unk1C0 > 7.0) {
        sp24 = 1;
    }

    func_80302484(arg0);
    arg0->unk1C8 += D_8034F854;
    if (arg0->unk1C8 > 0.2) {
        arg0->unk2 = 2;
        uvDobjState(arg0->objId, 2);
        arg0->unk1C8 = 0.0;
    } else if (arg0->unk1C8 > 0.1) {
        arg0->unk2 = 0;
        uvDobjState(arg0->objId, 0);
    }
    if (((arg0->unk1C == arg0->unk18->unk1374) && (arg0->unk2C == 0.0f) && (arg0->unk65D != 0)) || (sp24 != 0)) {
        arg0->unk4C = 3;
        arg0->unk2 = 2;
        uvDobjState(arg0->objId, 2);
        arg0->unk1C0 = 0.0;
        func_802FBD90(arg0);
        shadow_803343D8(1);
        if (sp24 != 0) {
            if (arg0->unk1C != arg0->unk18->unk1374) {
                _uvDebugPrintf("Camera follow distance not right.");
            }
            if (arg0->unk2C != 0.0f) {
                _uvDebugPrintf("Camera not unrolled.");
            }
            if (arg0->unk65D == 0) {
                _uvDebugPrintf("Invalid heading.");
            }
        }
    }
}

void func_80302BA0(JumbleHopperData* arg0) {
    f32 temp_fa0 = 20.0f;
    s32 sp20;

    arg0->unk1C0 += D_8034F854;
    sp20 = 0;
    if (arg0->unk1C0 > 7.0) {
        sp20 = 1;
    }

    func_80302484(arg0);
    arg0->unk1D0 += D_8034F854 * 0.01 * temp_fa0;
    if (arg0->unk1D0 > 1.0f) {
        arg0->unk1D0 = 1.0f;
    }
    if ((arg0->unk1D0 > 0.3478261f) && (D_8036905C[0] == 0)) {
        sndPlaySfx(SFX_UNK_061);
        D_8036905C[0] = 1;
    } else if ((arg0->unk1D0 > 0.39130434f) && (D_8036905C[1] == 0)) {
        sndPlaySfx(SFX_UNK_061);
        D_8036905C[1] = 1;
    } else if ((arg0->unk1D0 > 0.43478262f) && (D_8036905C[2] == 0)) {
        sndPlaySfx(SFX_UNK_061);
        D_8036905C[2] = 1;
    } else if ((arg0->unk1D0 > 0.47826087f) && (D_8036905C[3] == 0)) {
        sndPlaySfx(SFX_UNK_061);
        D_8036905C[3] = 1;
    } else if ((arg0->unk1D0 > 0.5217391f) && (D_8036905C[4] == 0)) {
        sndPlaySfx(SFX_UNK_061);
        D_8036905C[4] = 1;
    }
    if (arg0->unk1D0 > 0.708f) {
        if (arg0->unk140.y > 0.0f) {
            arg0->unk140.y -= D_8034F854 * 10.0 * 20.0 * 0.8;
            arg0->unk5CC = (1.0f - arg0->unk1D0) * 45.0f;
            arg0->unk5D4 = (1.0f - arg0->unk1D0) * 45.0f;
            arg0->unk5C0 = (1.0f - arg0->unk1D0) * -45.0f;
            arg0->unk5D8 = 0.0f;
            arg0->unkF4.z = MAX(func_802FD010(arg0), arg0->unkF4.z);
        }
        if (arg0->unk140.y <= 0.0f) {
            arg0->unk140.y = 0.0f;
        }
    }
    func_80200B00(arg0->objId, 0x6C, arg0->unk1D0);
    if (((arg0->unk1D0 >= 0.0f) && (arg0->unk140.y == 0.0f) && (arg0->unk1C == arg0->unk18->unk1374) && (arg0->unk2C == 0.0f) && (arg0->unk65D != 0)) ||
        (sp20 != 0)) {
        arg0->unk4C = 3;
        arg0->unk1C0 = 0.0;
        func_802FBD90(arg0);
        shadow_803343D8(1);
        if (sp20 != 0) {
            if (arg0->unk140.y != 0.0f) {
                _uvDebugPrintf("Pitch not zeroed.");
            }
            if (arg0->unk1C != arg0->unk18->unk1374) {
                _uvDebugPrintf("Camera follow distance not right.");
            }
            if (arg0->unk2C != 0.0f) {
                _uvDebugPrintf("Camera not unrolled.");
            }
            if (arg0->unk65D == 0) {
                _uvDebugPrintf("Invalid heading.");
            }
        }
    }
    func_802FCE38(arg0);
}

void func_80303028(JumbleHopperData* arg0) {
    arg0->unkF4.x = arg0->unk74.m[3][0];
    arg0->unkF4.y = arg0->unk74.m[3][1];
    arg0->unkF4.z = arg0->unk74.m[3][2];
    switch (arg0->unk4C) {
    case 0:
        func_802FD794(arg0);
        break;
    case 1:
        func_802FD8C0(arg0);
        break;
    case 2:
        func_80300E78(arg0);
        break;
    case 3:
        func_80301090(arg0);
        break;
    case 5:
        func_80301C58(arg0);
        break;
    case 4:
        func_80301AF8(arg0);
        break;
    case 6:
        func_80301D28(arg0);
        break;
    case 7:
        func_80301F70(arg0);
        break;
    case 8:
        func_80302BA0(arg0);
        break;
    case 9:
        func_803029CC(arg0);
        break;
    }

    func_8034B210(arg0->unkF4, arg0->unk140, &arg0->unk74);
    uvDobjPosm(arg0->objId, 0, &arg0->unk74);

    if ((arg0->unk4C != 8) && (arg0->unk4C != 7)) {
        shadow_80334578(&arg0->unk74, arg0->unk64);
    }
    uvMat4InvertTranslationRotation(&arg0->unkB4, &arg0->unk74);
    arg0->unk180 = uvVec3Len(&arg0->unk15C);
    arg0->unk158 = uvVec3Len(&arg0->unk14C);
    arg0->unk670.x = arg0->unkF4.x;
    arg0->unk670.y = arg0->unkF4.y;
    arg0->unk670.z = arg0->unkF4.z;
    arg0->unk174.x = arg0->unk168.x;
    arg0->unk174.y = arg0->unk168.y;
    arg0->unk174.z = arg0->unk168.z;
    arg0->unk70 = arg0->unk6C;
    arg0->unk4D = arg0->unk4C;
    if (func_802E06AC(&arg0->unk74) != 0) {
        arg0->unkF4.x = arg0->unk74.m[3][0];
        arg0->unkF4.y = arg0->unk74.m[3][1];
        arg0->unkF4.z = arg0->unk74.m[3][2];
    }
}
