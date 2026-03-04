#include "common.h"
#include <uv_dobj.h>
#include <uv_math.h>
#include <uv_vector.h>
#include "code_61A60.h"
#include "code_9A960.h"

s32 D_8034EA40 = 0;
u16 D_8034EA44 = 0xFFFF;
s32 D_8034EA48 = 0;

// This struct should be used for Unk8034EA4C */
typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
} Unk8034EA4C;
f32 D_8034EA4C[] = {
    -68.08f,
    -302.14f,
    10.74f,
};

f32 D_8034EA58 = -0.0174533f; // almost DEG_TO_RAD(1)
f32 D_8034EA5C = 0.1f;
f32 padD_8034EA60 = 0.0f;

s32 D_8034EA64[] = { 0, 3, 1, 4, 2, 5 };
s32 D_8034EA7C[] = { 0x35, 0x14C, 0x9C, 0x1A7, 0x85, 0x128 };
s32 D_8034EA94[] = { 2, 2, 2, 2, 2, 2 };
Unk803599D0 D_8034EAAC = { 8, 0.36f, 0.0f, 0.412f, 0.1f, 0.465f, 0.25f, 0.517f, 0.475f, 0.568f, 0.5f, 0.62f, 0.475f, 0.673f, 0.25f, 0.725f, 0.0f, 0, 0, 0, 0 };

// forward declarations
s32 func_802DB38C(Unk802D3658_Unk1228*, Vec3F*, Vec3F*);
s32 func_802DB6D4(Unk802D3658_Unk1228*, Vec3F*, Vec3F*);
s32 func_802DB9B8(Unk802D3658_Unk1228*, Vec3F*, Vec3F*);
s32 func_802DBCB0(Unk802D3658_Unk1228*, Vec3F*, Vec3F*);

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DA530.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DA54C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DA574.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DA628.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DA684.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DA6E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DA9E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DAA34.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DAB18.s")

s32 func_802DB050(Unk802D3658_Unk111C* arg0, Unk802D3658_Unk1224* arg1, u16 arg2, u8 arg3, Mtx4F* arg4) {
    Unk802D3658_Unk1120* var_s5;
    Vec3F* var_s4;
    s32 i;
    Unk802D3658_Unk1228* temp_s0;

    if ((arg2 != 0xFFFF) && (arg3 & 1)) {
        uvDobjState(arg2, arg3 - 1);
    }
    arg1->unk0 = 0;
    for (i = 0; i < arg0->unk0; i++) {
        var_s5 = &arg0->unk4[i];
        if (var_s5->unk0 != 0) {
            uvMat4LocalToWorld(arg4, &var_s5->unk4, &var_s5->unk1C);
            uvMat4LocalToWorld(arg4, &var_s5->unk10, &var_s5->unk28);
        }
        var_s4 = &var_s5->unk4;
        temp_s0 = &arg1->unk4[arg1->unk0];
        if (func_802DB6D4(temp_s0, &var_s5->unk10, var_s4) != 0) {
            temp_s0->unk0 = i;
            arg1->unk0++;
        } else if (func_802DB9B8(temp_s0, &var_s5->unk10, var_s4) != 0) {
            temp_s0->unk0 = i;
            arg1->unk0++;
        } else if (func_802DB38C(temp_s0, &var_s5->unk10, var_s4) != 0) {
            temp_s0->unk0 = i;
            arg1->unk0++;
        } else if (func_802DBCB0(temp_s0, &var_s5->unk10, var_s4) != 0) {
            temp_s0->unk0 = i;
            arg1->unk0++;
        }
    }
    if (arg2 != 0xFFFF) {
        uvDobjState(arg2, (s32)arg3);
    }
    return arg1->unk0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DB224.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DB38C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DB6D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DB9B8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DBCB0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DBE10.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DBE64.s")

s32 func_802DBF10(Unk802D3658_Unk111C* arg0, Unk802D3658_Unk1224* arg1, Vec3F* arg2, Vec3F* arg3) {
    s32 pad[8];
    s32 ret;
    Unk802D3658_Unk1228* unk4;
    Vec3F* temp_v0;
    Vec3F* temp_v1;
    f32 temp_fa1;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fs2;
    f32 temp_ft4;
    f32 temp_fv0;
    f32 curLen;
    f32 emp_fv1;
    f32 minLen;
    s32 i;

    minLen = 1000000.0f;

    for (i = 0; i < arg1->unk0; i++) {
        unk4 = &arg1->unk4[i];
        temp_fv0 = unk4->unk18;
        temp_v0 = &arg0->unk4[unk4->unk0].unk10;
        temp_v1 = &arg0->unk4[unk4->unk0].unk4;
        temp_fs0 = temp_v0->x + ((temp_v1->x - temp_v0->x) * temp_fv0);
        temp_fs1 = temp_v0->y + ((temp_v1->y - temp_v0->y) * temp_fv0);
        temp_fs2 = temp_v0->z + ((temp_v1->z - temp_v0->z) * temp_fv0);
        curLen = uvSqrtF(SQ(temp_fs0) + SQ(temp_fs1) + SQ(temp_fs2));
        if (curLen < minLen) {
            ret = i;
            arg2->x = temp_fs0;
            arg2->y = temp_fs1;
            arg2->z = temp_fs2;
            minLen = curLen;
            arg3->x = unk4->unk1C.x;
            arg3->y = unk4->unk1C.y;
            arg3->z = unk4->unk1C.z;
        }
    }
    return ret;
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DC074.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DC1DC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DC380.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DC784.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DC814.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DC8E4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DC930.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DC97C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DCA00.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_61A60/func_802DCA5C.s")
