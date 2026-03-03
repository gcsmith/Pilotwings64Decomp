#include "common.h"
#include <uv_dobj.h>
#include <uv_math.h>
#include <uv_matrix.h>
#include <uv_vector.h>
#include "code_9A960.h"
#include "code_A6000.h"

void uvPathPoseLine(Unk8037F098* arg0, Unk8037DCA0* arg1, f32 arg2) {
    Unk8037DCA0_UnkC* temp_a1;
    Unk8037DCA0_UnkC* temp_v0;
    UnkTranslatStruct_Unk8* temp_a1_2;
    UnkTranslatStruct_Unk8* temp_v1_3;
    f32 temp_fs0;
    f32 temp_ft4;
    f32 temp_fv0;
    f32 temp_fv1_2;
    f32 var_fa0;
    f32 var_fv0;
    f32 var_fv1;
    s32 temp_a3;
    s32 temp_ft2;
    s32 var_a0;
    u32 temp_v1;
    s32 pad1;
    s32 pad2;

    if (arg1->modelId == WORLD_MODEL_ID) {
        _uvDebugPrintf("uvPathPoseLine: Path has an invalid Model ID!\n");
        return;
    }

    var_fv0 = (f32)((u32)arg1->unk8 - 1);

    if (arg2 < 0.0f) {
        arg2 = (arg2 + 1.0f) - (s32)arg2;
    }
    if (arg1->unk24 != 0) {
        if (arg2 > 1.0f) {
            arg2 = 1.0f;
        }
    } else if (arg2 > 1.0f) {
        arg2 -= (s32)arg2;
    }
    arg2 *= var_fv0;
    temp_ft2 = (s32)arg2;

    temp_v1 = arg1->unk8;
    if (temp_ft2 + 1 == (s32)temp_v1) {
        var_a0 = temp_v1 - 1;
    } else {
        var_a0 = temp_ft2 + 1;
    }
    temp_ft4 = (f32)temp_ft2;
    temp_fv0 = (f32)var_a0;
    temp_v0 = &arg1->unkC[temp_ft2];
    temp_a1 = &arg1->unkC[var_a0];

    if (temp_fv0 == temp_ft4) {
        var_fv1 = 1.0f;
        var_fa0 = 0.0f;
    } else {
        var_fv1 = (temp_fv0 - arg2) * (1.0f / (temp_fv0 - temp_ft4));
        var_fa0 = 1.0f - var_fv1;
    }

    arg0->unk0->x = (temp_a1->unk0.x * var_fa0) + (temp_v0->unk0.x * var_fv1);
    arg0->unk0->y = (temp_a1->unk0.y * var_fa0) + (temp_v0->unk0.y * var_fv1);
    arg0->unk0->z = (temp_a1->unk0.z * var_fa0) + (temp_v0->unk0.z * var_fv1);
    arg0->unk0->w = (temp_a1->unk0.w * var_fa0) + (temp_v0->unk0.w * var_fv1);
    if (temp_v0->unk10_15) {
        temp_fv0 = uvSqrtF(SQ(arg0->unk0->w) + (SQ(arg0->unk0->x) + SQ(arg0->unk0->y) + SQ(arg0->unk0->z)));
        if (temp_fv0 != 0.0f) {
            temp_fv1_2 = 1.0f / temp_fv0;
            arg0->unk0->x *= temp_fv1_2;
            arg0->unk0->y *= temp_fv1_2;
            arg0->unk0->z *= temp_fv1_2;
            arg0->unk0->w *= temp_fv1_2;
        }
    }
    temp_v1 = arg1->unk18;
    if ((u32)temp_ft2 + 1 == temp_v1) {
        var_a0 = temp_v1 - 1;
    } else {
        var_a0 = temp_ft2 + 1;
    }
    temp_fv0 = (f32)var_a0;
    temp_v1_3 = &arg1->unk1C[temp_ft2];
    temp_a1_2 = &arg1->unk1C[var_a0];
    if (temp_fv0 == temp_ft4) {
        var_fv1 = 1.0f;
        var_fa0 = 0.0f;
    } else {
        var_fv1 = (temp_fv0 - arg2) * (1.0f / (temp_fv0 - temp_ft4));
        var_fa0 = 1.0f - var_fv1;
    }
    arg0->unk190->x = (temp_a1_2->unk0.x * var_fa0) + (temp_v1_3->unk0.x * var_fv1);
    arg0->unk190->y = (temp_a1_2->unk0.y * var_fa0) + (temp_v1_3->unk0.y * var_fv1);
    arg0->unk190->z = (temp_a1_2->unk0.z * var_fa0) + (temp_v1_3->unk0.z * var_fv1);
    arg0->unk2D8 = 1;
}

void func_8031EE48(s32 arg0, Unk8037F098* arg1, f32 arg2, f32 arg3, f32 arg4) {
    Mtx4F sp80;
    s32 i;
    Vec3F* vec;
    Vec4F* s1;
    s32 count;
    Unk803136C4_Arg0 sp54;

    count = arg1->unk2D8;
    for (i = 0, vec = arg1->unk190, s1 = arg1->unk0; i < count; i++, s1++, vec++) {
        sp54.unk0.x = vec->x;
        sp54.unk0.y = vec->y;
        sp54.unk0.z = vec->z;
        sp54.unkC.x = s1->x;
        sp54.unkC.y = s1->y;
        sp54.unkC.z = s1->z;
        sp54.unkC.w = s1->w;
        func_803136C4(&sp54, &sp80);
        uvMat4Scale(&sp80, arg2, arg3, arg4);
        uvDobjPosm(arg0, arg1->unk2BC[i], &sp80);
    }
}

void func_8031EF60(Unk8037DCA0* arg0, s32 arg1) {
    arg0->modelId = arg1;
}

void func_8031EF68(Unk8037DCA0* arg0) {
    if (arg0->modelId != WORLD_MODEL_ID) {
        arg0->modelId = WORLD_MODEL_ID;
    }
}
