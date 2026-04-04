#include "common.h"
#include <uv_math.h>
#include "kernel/code_8170.h"
#include "code_61A60.h"
#include "code_66F70.h"
#include "code_9A960.h"
#include "task.h"

Vec3F D_80359D70;
u32 D_80359D7C;

f32 func_802DFA40(f32 arg0, f32 arg1) {
    s32* sp6C;
    u8 temp_v0;
    u8 i;
    f32 sp64;
    f32 var_fs0;
    Vec3F sp54;

    temp_v0 = uvTerraGetPt(D_80362690->terraId, arg0, arg1, &sp6C);
    if (temp_v0 == 0) {
        return 0.0f;
    }

    var_fs0 = -1000000.0f;
    for (i = 0; i < temp_v0; i++) {
        uvTerraGetPlane(D_80362690->terraId, sp6C[i], arg0, arg1, &sp64, &sp54);
        if (var_fs0 < sp64) {
            var_fs0 = sp64;
        }
    }
    return var_fs0;
}

s32 func_802DFB48(s32 arg0, f32 arg1, f32 arg2, f32 arg3, s32* arg4, f32* arg5, Vec3F* arg6) {
    s32* spB4;
    u8 temp_v0;
    u8 i;
    f32 spAC;
    f32 var_fs2;
    f32 var_fs3;
    Vec3F sp98;
    f32 sp94;
    f32 sp90;
    f32 sp8C;
    f32 sp88;
    f32 sp84;
    f32 sp80;
    s32 sp7C;
    s32 sp78;

    temp_v0 = uvTerraGetPt(D_80362690->terraId, arg1, arg2, &spB4);
    if (temp_v0 == 0) {
        return 0;
    }

    var_fs2 = 1000000.0f;
    var_fs3 = -1000000.0f;
    spAC = -1500000.0f;
    for (i = 0; i < temp_v0; i++) {
        uvTerraGetPlane(D_80362690->terraId, spB4[i], arg1, arg2, &spAC, &sp98);
        if ((spAC <= arg3) && (var_fs3 < spAC) && (spAC != -1500000.0f)) {
            var_fs3 = spAC;
            sp7C = spB4[i];
            sp8C = sp98.x;
            sp90 = sp98.y;
            sp94 = sp98.z;
        }
        if ((arg3 <= spAC) && (spAC < var_fs2) && (spAC != -1500000.0f)) {
            var_fs2 = spAC;
            sp78 = spB4[i];
            sp80 = sp98.x;
            sp84 = sp98.y;
            sp88 = sp98.z;
        }
    }
    if (arg0 == 0) {
        if (FABS(arg3 - var_fs3) < FABS(arg3 - var_fs2)) {
            arg0 = 2;
        } else {
            arg0 = 1;
        }
    }
    if (arg0 == 2) {
        if (var_fs3 == -1000000.0f) {
            arg6->y = 0.0f;
            arg6->x = 0.0f;
            arg6->z = 1.0f;
            *arg5 = 0.0f;
            return 0;
        } else {
            *arg4 = sp7C;
            *arg5 = var_fs3;
            arg6->x = sp8C;
            arg6->y = sp90;
            arg6->z = sp94;
            return 1;
        }
    } else if (arg0 == 1) {
        if (var_fs2 == 1000000.0f) {
            return 0;
        }
        *arg4 = sp78;
        *arg5 = var_fs2;
        arg6->x = sp80;
        arg6->y = sp84;
        arg6->z = sp88;
        return 1;
    }
    return 0;
}

// db_getgnd does not always initialize the sp11F
#if defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsometimes-uninitialized"
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif
u8 db_getgnd(Vec3F* arg0, Vec3F* arg1, s32* arg2, s32* arg3, f32* arg4, Vec3F* arg5) {
    u8 sp11F;
    u8 var_a3;
    u16 s0;
    s32 var_v0;
    Unk802D3658_Unk1228 spD8;
    Unk802D3658_Unk1228* spD4;
    Unk802D3658_Unk1228 sp94;
    Unk802D3658_Unk1228 sp54;
    s32 sp50;
    s32 sp4C;
    Vec3F sp40;
    s32 temp;

    if ((arg1->x != arg0->x) || (arg1->y != arg0->y) || (arg1->z != arg0->z)) {
        var_v0 = func_802DB38C(&spD8, arg0, arg1);
        if (var_v0 == 0) {
            var_v0 = func_802DBCB0(&spD8, arg0, arg1);
        }
        if (var_v0 == 0) {
            var_v0 = func_802DB9B8(&spD8, arg0, arg1);
        }
        if (var_v0 == 0) {
            var_v0 = func_802DB6D4(&spD8, arg0, arg1);
        }
        if (var_v0 != 0) {
            s0 = spD8.unk4;
            *arg3 = spD8.surfaceId;
            *arg4 = spD8.unkC.z;
            uvVec3Copy(arg5, &spD8.unk1C);
            if (*arg2 == 2) {
                *arg2 = 1;
            } else {
                *arg2 = 2;
            }
            uvVec3Copy(&D_80359D70, &spD8.unkC);
            return s0;
        }
    }
    sp40.x = arg1->x;
    sp40.y = arg1->y;
    spD4 = NULL;
    if (*arg2 == 1) {
        sp40.z = arg1->z - 50.0f;
        sp11F = func_802DFB48(2, arg1->x, arg1->y, arg1->z, arg3, arg4, arg5);
    } else if (*arg2 == 2) {
        sp40.z = arg1->z + 50.0f;
        sp11F = func_802DFB48(1, arg1->x, arg1->y, arg1->z, arg3, arg4, arg5);
    } else {
        _uvDebugPrintf("db_getgnd : invalid state [%d]\n", *arg2);
        // @bug? should maybe return here as sp11F is not set but read
    }
    sp50 = func_802DB6D4(&sp94, arg1, &sp40);
    sp4C = func_802DB9B8(&sp54, arg1, &sp40);
    if ((sp11F == 0) && (sp50 == 0) && (sp4C == 0)) {
        sp11F = temp = func_802DFB48(*arg2, arg1->x, arg1->y, arg1->z, arg3, arg4, arg5);
        if (temp) {
            if (*arg2 == 1) {
                *arg2 = 2;
            } else if (*arg2 == 2) {
                *arg2 = 1;
            }
        }
    }
    if ((sp50 != 0) && (sp4C == 0)) {
        spD4 = &sp94;
    } else if ((sp4C != 0) && (sp50 == 0)) {
        spD4 = &sp54;
    } else if ((sp50 != 0) && (sp4C != 0)) {
        if (sp94.unk18 < sp54.unk18) {
            spD4 = &sp94;
        } else {
            spD4 = &sp54;
        }
    }
    if ((sp11F) && (spD4 != NULL)) {
        if ((spD4->unk18 * 50.0f) < FABS(arg1->z - *arg4)) {
            sp11F = 0;
        } else {
            spD4 = NULL;
        }
    }
    if (spD4 != NULL) {
        *arg3 = spD4->surfaceId;
        D_80359D7C = spD4->unk4;
        if (*arg2 == 1) {
            *arg4 = arg1->z - (50.0f * spD4->unk18);
        } else {
            *arg4 = arg1->z + (50.0f * spD4->unk18);
        }
        uvVec3Copy(arg5, &spD4->unk1C);
    } else if (sp11F == 0) {
        *arg3 = -1;
        *arg4 = 0.0f;
        arg5->x = 0.0f;
        arg5->y = 0.0f;
        arg5->z = 1.0f;
        D_80359D7C = 4;
        if (arg1->z < 0.0f) {
            *arg2 = 2;
        } else {
            *arg2 = 1;
        }
    } else {
        D_80359D7C = 1;
    }
    return 0;
}
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif

Vec3F* func_802E02EC(void) {
    return &D_80359D70;
}

u32 func_802E02F8(void) {
    return D_80359D7C;
}

void db_getstart(Mtx4F* arg0, Vec3F* arg1, u8* arg2, f32* fuel) {
    Vec3F pos;
    Vec3F ang;
    TaskTPAD* sp44;
    TaskTPAD* first;
    ParsedUVTR* sp3C;
    s32 idx;
    u8 temp_v1;

    temp_v1 = taskGetTPAD(&sp44);
    if (temp_v1 == 0) {
        _uvDebugPrintf("db_getstart :  no starting pads in task!!!\n");
        sp3C = uvTerraGetBox(D_80362690->terraId);
        uvMat4SetIdentity(arg0);
        arg0->m[3][0] = (sp3C->unk0.unk0 + sp3C->unk0.unkC) * 0.5f;
        arg0->m[3][1] = (sp3C->unk0.unk4 + sp3C->unk0.unk10) * 0.5f;
        arg0->m[3][2] = sp3C->unk0.unk14;
        if (arg2 != NULL) {
            *arg2 = 1;
        }
        if (fuel != NULL) {
            *fuel = 0.0f;
        }
    } else {
        if (temp_v1 > 1) {
            _uvDebugPrintf("db_getstart : too many starting pad! picking first\n");
        }
        first = &sp44[0];
        pos.x = first->pos.x;
        pos.y = first->pos.y;
        pos.z = first->pos.z;
        ang.x = first->angle.x;
        ang.y = first->angle.y;
        ang.z = first->angle.z;
        func_80313640(pos.x, pos.y, pos.z, ang.x * 0.0174533f, ang.y * 0.0174533f, ang.z * 0.0174533f, arg0); // almost DEG_TO_RAD(1)
        arg1->x = first->unk1C.x;
        arg1->y = first->unk1C.y;
        arg1->z = first->unk1C.z;
        if (arg2 != NULL) {
            *arg2 = first->unk28;
        }
        if (fuel != NULL) {
            *fuel = first->unk2C;
        }
    }
}

void func_802E0484(Mtx4F* arg0, Mtx4F* arg1, f32 arg2) {
    f32 sp6C;
    Vec3F sp60;
    s32 sp5C;
    f32 temp_fv0;
    Vec3F sp4C;
    Vec3F sp40;
    s32 sp3C;
    Vec3F* sp38;
    f32 sp34;
    f32 sp30;
    f32 sp2C;

    sp4C.x = arg0->m[3][0];
    sp4C.y = arg0->m[3][1];
    sp4C.z = arg0->m[3][2];
    sp40.x = arg1->m[3][0];
    sp40.y = arg1->m[3][1];
    sp40.z = arg1->m[3][2];
    sp3C = 1;
    if (db_getgnd(&sp4C, &sp40, &sp3C, &sp5C, &sp6C, &sp60) == 0) {
        arg0->m[3][2] = sp6C + arg2;
        return;
    }

    sp38 = func_802E02EC();
    sp34 = arg1->m[3][0] - arg0->m[3][0];
    sp30 = arg1->m[3][1] - arg0->m[3][1];
    sp2C = arg1->m[3][2] - arg0->m[3][2];
    temp_fv0 = uvSqrtF(SQ(sp34) + SQ(sp30) + SQ(sp2C));
    if (temp_fv0 != 0.0f) {
        sp34 /= temp_fv0;
        sp30 /= temp_fv0;
        sp2C /= temp_fv0;
    }
    arg0->m[3][0] = sp38->x + sp34;
    arg0->m[3][1] = sp38->y + sp30;
    arg0->m[3][2] = sp38->z + sp2C;
}

void func_802E05CC(Mtx4F* arg0, Vec3F* arg1, Vec3F* arg2, u16 arg3) {
    Vec3F sp2C;
    f32 pad;

    arg0->m[3][0] = arg1->x + (0.2f * arg2->x);
    arg0->m[3][1] = arg1->y + (0.2f * arg2->y);
    arg0->m[3][2] = arg1->z + (0.2f * arg2->z);
    if (arg3 != 1) {
        if (arg3 == 2) {
            sp2C.x = arg2->x;
            sp2C.y = arg2->y;
            sp2C.z = arg2->z;
            func_80313E18(&sp2C, arg0);
        }
    } else {
        sp2C.x = -arg2->x;
        sp2C.y = -arg2->y;
        sp2C.z = -arg2->z;
        func_80313E18(&sp2C, arg0);
    }
}

u8 func_802E06AC(Mtx4F* arg0) {
    f32 pad;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_4;
    f32 sp24;
    f32 sp20;
    u8 var_v1;
    ParsedUVTR* temp_v0;

    var_v1 = 0;
    sp24 = arg0->m[3][0];
    sp20 = arg0->m[3][1];

    temp_v0 = uvTerraGetBox(D_80362690->terraId);

    temp_fv0 = temp_v0->unk0.unk0 - 2000.0f - sp24;
    if (temp_fv0 > 0.0f) {
        var_v1 = 1;
        sp24 = (temp_v0->unk0.unkC + 2000.0f) - temp_fv0;
    } else {
        temp_fv0_2 = sp24 - (temp_v0->unk0.unkC + 2000.0f);
        if (temp_fv0_2 > 0.0f) {
            sp24 = temp_v0->unk0.unk0 - 2000.0f + temp_fv0_2;
            var_v1 = 1;
        }
    }

    temp_fv0 = temp_v0->unk0.unk4 - 2000.0f - sp20;
    if (temp_fv0 > 0.0f) {
        var_v1 = 1;
        sp20 = (temp_v0->unk0.unk10 + 2000.0f) - temp_fv0;
    } else {
        temp_fv0_4 = sp20 - (temp_v0->unk0.unk10 + 2000.0f);
        if (temp_fv0_4 > 0.0f) {
            sp20 = temp_v0->unk0.unk4 - 2000.0f + temp_fv0_4;
            var_v1 = 1;
        }
    }
    if (var_v1 != 0) {
        arg0->m[3][0] = sp24;
        arg0->m[3][1] = sp20;
        func_802EDDEC(arg0);
    }
    return var_v1;
}

u8 func_802E07D8(Mtx4F* arg0) {
    f32 pad;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 sp24;
    f32 sp20;
    u8 sp1F;
    ParsedUVTR* temp_v0;

    sp24 = arg0->m[3][0];
    sp20 = arg0->m[3][1];
    sp1F = 0;

    temp_v0 = uvTerraGetBox(D_80362690->terraId);
    temp_fv0 = temp_v0->unk0.unk0 - 2000.0f - sp24;
    if (temp_fv0 > 0.0f) {
        sp1F = 1;
        sp24 = (temp_v0->unk0.unkC + 2000.0f) - temp_fv0;
    } else {
        temp_fv0_2 = sp24 - (temp_v0->unk0.unkC + 2000.0f);
        if (temp_fv0_2 > 0.0f) {
            sp24 = temp_v0->unk0.unk0 - 2000.0f + temp_fv0_2;
            sp1F = 1;
        }
    }

    temp_fv0_3 = temp_v0->unk0.unk4 - 2000.0f - sp20;
    if (temp_fv0_3 > 0.0f) {
        sp1F = 1;
        sp20 = (temp_v0->unk0.unk10 + 2000.0f) - temp_fv0_3;
    } else {
        temp_fv0_2 = sp20 - (temp_v0->unk0.unk10 + 2000.0f);
        if (temp_fv0_2 > 0.0f) {
            sp20 = temp_v0->unk0.unk4 - 2000.0f + temp_fv0_2;
            sp1F = 1;
        }
    }

    if (sp1F != 0) {
        arg0->m[3][0] = sp24;
        arg0->m[3][1] = sp20;
    }
    return sp1F;
}

s32 func_802E08F4(f32 arg0, f32 arg1, f32 arg2) {
    f32 sp4;
    f32 temp_fa1;
    f32 temp_ft4;
    f32 temp_fv0;
    f32 temp_fv1;

    temp_fv1 = arg0 - 1972.1f;
    temp_ft4 = arg1 - -1105.6f;
    sp4 = (temp_fv1 * 0.987688f) + (temp_ft4 * 0.188924f);
    temp_fa1 = (-temp_fv1 * 0.188924f) + (temp_ft4 * 0.987688f);
    temp_fv0 = arg2 - 32.0f;
    if (FABS(sp4) <= 10.0f && FABS(temp_fa1) <= 10.0f && FABS(temp_fv0) <= 2.0f) {
        return 1;
    }

    temp_fv1 = arg0 - 1954.9f;
    temp_ft4 = arg1 - -1020.0f;
    sp4 = (temp_fv1 * 0.987688f) + (temp_ft4 * 0.188924f);
    temp_fa1 = (-temp_fv1 * 0.188924f) + (temp_ft4 * 0.987688f);
    temp_fv0 = arg2 - 32.0f;
    if (FABS(sp4) <= 10.0f && FABS(temp_fa1) <= 10.0f && FABS(temp_fv0) <= 2.0f) {
        return 1;
    }

    temp_fv1 = arg0 - 2067.3f;
    temp_ft4 = arg1 - -977.9f;
    sp4 = (temp_fv1 * 0.562083f) + (temp_ft4 * -0.827081f);
    temp_fa1 = (-temp_fv1 * -0.827081f) + (temp_ft4 * 0.562083f);
    temp_fv0 = arg2 - 42.0f;
    if (FABS(sp4) <= 10.0f && FABS(temp_fa1) <= 10.0f && FABS(temp_fv0) <= 2.0f) {
        return 1;
    }

    return 0;
}

u8 func_802E0C30(u8 arg0, s32 arg1) {
    u8 ret;

    ret = 0;
    if ((arg0 == 4) || ((arg0 != 0) && (arg1 == -1))) {
        ret = 1;
    } else if (arg0 == 0) {
        if (func_802E02F8() == 4) {
            ret = 1;
        } else if ((func_802E02F8() == 1) && ((arg1 == -1) || (func_802DC8E4(arg1) != 0))) {
            ret = 1;
        }
    }
    return ret;
}
