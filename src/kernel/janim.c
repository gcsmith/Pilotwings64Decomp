#include "common.h"
#include <uv_graphics.h>
#include <uv_janim.h>
#include <uv_matrix.h>
#include <uv_math.h>
#include <uv_memory.h>
#include <uv_model.h>
#include <uv_filesystem.h>

typedef struct UnkJAnimStruct2 {
    struct UnkJAnimStruct2* unk0;
    u16 unk4;
    u32 unk8;
    Unk8037DCA0_UnkC* unkC;
} UnkJAnimStruct2; // size = 0x10

typedef struct UnkJAnimStruct1 {
    struct UnkJAnimStruct2* unk0;
    u16 unk4;
    u16 unk6;
    u8 unk8;
    u8 unk9;
} UnkJAnimStruct1; // size = 0xC

void* uvJanimLoad(s32 arg0) {
    UnkJAnimStruct1* var_s3; // sp84
    s32 temp_v0;
    UnkJAnimStruct2* temp_v0_3;
    u32 sp78;
    void* sp74;
    s32 var_s2;
    UnkJAnimStruct2* var_s4;
    u32 i;
    u32 var_v0;
    UnkJAnimStruct1* temp_v0_2;
    UnkPartStruct_Unk8* var_v0_2;
    UnkCommStruct* temp1;
    UnkPartStruct* temp2;

    var_s4 = NULL;
    var_s2 = 0;
    temp_v0 = uvFileReadHeader(gUVBlockOffsets.UVAN[arg0]);
    var_v0 = uvFileReadBlock(temp_v0, &sp78, &sp74, 1);
    while (var_v0) {
        switch (var_v0) {
        case 'COMM':
            temp1 = sp74;
            var_s3 = _uvMemAlloc(sizeof(UnkJAnimStruct1), 4);
            var_s3->unk4 = temp1->unk10;
            var_s3->unk6 = 0;
            if (sp78 > 0x10) {
                var_s3->unk8 = temp1->unkC;
            } else {
                var_s3->unk8 = 1;
            }

            var_s3->unk8 = temp1->unkC;
            if (var_s3->unk8 <= 0) {
                var_s3->unk8 = 1;
            }
            var_s3->unk9 = (s8)((s32)((temp1->unk4 - temp1->unk0) + 1) / var_s3->unk8);
            if (var_s3->unk8 <= 0) {
                var_s3->unk8 = 1;
            }
            var_s2 = temp1->unk0;
            break;
        case 'PART':
            temp2 = sp74;
            temp_v0_3 = _uvMemAlloc(sizeof(UnkJAnimStruct2), 4);
            if (var_s4 != NULL) {
                var_s4->unk0 = temp_v0_3;
                var_s4 = temp_v0_3;
            } else {
                var_s3->unk0 = temp_v0_3;
                var_s4 = temp_v0_3;
            }

            temp_v0_3->unk8 = temp2->count;
            temp_v0_3->unk4 = temp2->unk4;
            temp_v0_3->unk0 = NULL;
            temp_v0_3->unkC = _uvMemAlloc(temp_v0_3->unk8 * sizeof(UnkPartStruct_Unk8), 4);
            if ((u32)temp2->unk8[0].unk12_5 != 1) {
                _uvDebugPrintf("ERROR: Animation data not quaternion format\n");
            }
            var_v0_2 = temp2->unk8;
            for (i = 0; i < var_s4->unk8; i++) {
                temp_v0_3->unkC[i].unk0.x = var_v0_2[i].unk0.x;
                temp_v0_3->unkC[i].unk0.y = var_v0_2[i].unk0.y;
                temp_v0_3->unkC[i].unk0.z = var_v0_2[i].unk0.z;
                temp_v0_3->unkC[i].unk0.w = var_v0_2[i].unk0.w;
                temp_v0_3->unkC[i].unk10_0 = var_v0_2[i].unk10 - var_s2;
                temp_v0_3->unkC[i].unk10_15 = var_v0_2[i].unk12_4;

                if (var_s3->unk6 <= (var_v0_2[i].unk10 - var_s2) + 1) {
                    var_s3->unk6 = (var_v0_2[i].unk10 - var_s2) + 1;
                }
            }
            break;
        }
        var_v0 = uvFileReadBlock(temp_v0, &sp78, &sp74, 1);
    }
    uvFile_80223F30(temp_v0);
    return var_s3;
}

void func_80200638(s32 arg0, Unk80371120* arg1) {
    Mtx4F sp58;
    s32 temp_s4;
    s32 i;
    s32 temp_s5;
    Unk8022B0A0* var_s1;

    temp_s4 = arg1->unk1AC;
    temp_s5 = D_80263780[arg0].unk0;
    var_s1 = arg1->unk0;

    for (i = 0; i < temp_s4; i++, var_s1++) {
        uvModelGetPosm(temp_s5, arg1->unk190[i], &sp58);
        uvMat4SetUnk4(&sp58, var_s1->unk0, var_s1->unk4, var_s1->unk8, var_s1->unkC);
        uvDobjPosm(arg0, arg1->unk190[i], &sp58);
    }
}

void func_802006FC(Unk80371120* arg0, Unk80371120* arg1, Unk80371120* arg2, f32 arg3) {
    Unk8022B0A0* var_s0;
    Unk8022B0A0* var_v0;
    Unk8022B0A0* var_v1;
    s32 pad;
    f32 var_ft5;
    s32 var_a2;
    s32 var_t1;
    s32 var_t2;
    s32 var_a3;
    s32 var_t0;
    f32 temp_fs0;
    f32 temp_fs2;
    f32 var_fv0;

    if (arg3 > 1.0f) {
        var_ft5 = 1.0f;
    } else {
        var_ft5 = arg3;
    }

    if (var_ft5 < 0.0f) {
        var_ft5 = 0.0f;
    }

    temp_fs0 = temp_fs2 = 1.0f - var_ft5;

    var_s0 = arg0->unk0;
    var_v0 = arg1->unk0;
    var_v1 = arg2->unk0;

    var_a2 = 0;
    var_t1 = 0;
    var_t2 = 0;
    var_a3 = arg1->unk1AC;
    var_t0 = arg2->unk1AC;

    while (((var_a3 != 0) || (var_t0 != 0)) && var_a2 < 25) {
        if ((var_a3 != 0) && (var_t0 != 0) && (arg1->unk190[var_t1] == arg2->unk190[var_t2])) {
            if (temp_fs2 == 1.0f) {
                var_s0->unk0 = var_v0->unk0;
                var_s0->unk4 = var_v0->unk4;
                var_s0->unk8 = var_v0->unk8;
                var_s0->unkC = var_v0->unkC;
            } else if (var_ft5 == 1.0f) {
                var_s0->unk0 = var_v1->unk0;
                var_s0->unk4 = var_v1->unk4;
                var_s0->unk8 = var_v1->unk8;
                var_s0->unkC = var_v1->unkC;
            } else {
                var_fv0 = var_v1->unkC * var_v0->unkC + (var_v0->unk0 * var_v1->unk0 + var_v0->unk4 * var_v1->unk4 + var_v0->unk8 * var_v1->unk8);
                if (var_fv0 < 0.0f) {
                    var_fv0 = -var_ft5;
                } else {
                    var_fv0 = var_ft5;
                }
                var_s0->unk0 = (var_v1->unk0 * var_fv0) + (var_v0->unk0 * temp_fs0);
                var_s0->unk4 = (var_v1->unk4 * var_fv0) + (var_v0->unk4 * temp_fs0);
                var_s0->unk8 = (var_v1->unk8 * var_fv0) + (var_v0->unk8 * temp_fs0);
                var_s0->unkC = (var_v1->unkC * var_fv0) + (var_v0->unkC * temp_fs0);
            }

            var_fv0 = uvSqrtF(SQ(var_s0->unkC) + (SQ(var_s0->unk0) + SQ(var_s0->unk4) + SQ(var_s0->unk8)));
            if (var_fv0 != 0.0f) {
                var_s0->unk0 /= var_fv0;
                var_s0->unk4 /= var_fv0;
                var_s0->unk8 /= var_fv0;
                var_s0->unkC /= var_fv0;
            }
            arg0->unk190[var_a2] = arg1->unk190[var_t1];

            var_a2++;
            var_s0++;
            var_t1++;
            var_a3--;
            var_v0++;
            var_t2++;
            var_t0--;
            var_v1++;
        } else if ((var_t0 != 0) && ((var_a3 == 0) || (arg2->unk190[var_t2] < arg1->unk190[var_t1]))) {
            var_t0--;
            if (var_ft5 > 0.0f) {
                var_s0->unk0 = var_v1->unk0;
                var_s0->unk4 = var_v1->unk4;
                var_s0->unk8 = var_v1->unk8;
                var_s0->unkC = var_v1->unkC;
                arg0->unk190[var_a2] = arg2->unk190[var_t2];
                var_a2++;
                var_s0++;
            }
            var_t2++;
            var_v1++;
        } else if ((var_a3 != 0) && ((var_t0 == 0) || (arg1->unk190[var_t1] < arg2->unk190[var_t2]))) {
            var_a3--;
            if (temp_fs2 > 0.0f) {
                var_s0->unk0 = var_v0->unk0;
                var_s0->unk4 = var_v0->unk4;
                var_s0->unk8 = var_v0->unk8;
                var_s0->unkC = var_v0->unkC;
                arg0->unk190[var_a2] = arg1->unk190[var_t1];
                var_a2++;
                var_s0++;
            }
            var_t1++;
            var_v0++;
        }
    }
    arg0->unk1AC = var_a2;
}

void func_80200B00(s32 arg0, s32 arg1, f32 arg2) {
    Unk80371120 sp18;

    uvJanimPoseLine(&sp18, arg1, arg2);
    func_80200638(arg0, &sp18);
}

void uvJanimPoseLine(Unk80371120* arg0, s32 arg1, f32 arg2) {
    Unk8022B0A0* var_s0;
    f32 temp_fv1;
    f32 var_fv0;
    f32 var_fv0_2;
    f32 var_fv1;
    f32 sp60;
    f32 sp5C;
    s32 temp_a1;
    s32 temp_ft1;
    s32 var_v1_2;
    u8* var_s2;
    Unk8037DCA0_UnkC* temp_v0;
    Unk8037DCA0_UnkC* var_a0;
    Unk8037DCA0_UnkC* var_a2;
    Unk8037DCA0_UnkC* var_v0;
    uvGfxUnkStructAnim0* var_s1;
    uvGfxUnkStructAnimation* temp_s4;
    s32 i;
    f32 temp_fv0;

    temp_s4 = gGfxUnkPtrs->unk1110[arg1];
    if (temp_s4 == NULL) {
        _uvDebugPrintf("uvJanimPoseLine : animation [%d] not defined in level\n", arg1);
        return;
    }
    temp_fv0 = temp_s4->unk6 - 1;
    if (arg2 < 0.0f) {
        arg2 = (arg2 + 1.0f) - (s32)arg2;
    }
    if (arg2 > 1.0f) {
        arg2 -= (s32)arg2;
    }
    arg2 *= temp_fv0;
    arg0->unk1AC = 0;
    var_s1 = temp_s4->unk0;
    var_s2 = arg0->unk190;
    var_s0 = arg0->unk0;
    while (var_s1 != NULL) {
        temp_a1 = var_s1->unk8;
        var_a0 = NULL;
        var_a2 = NULL;
        if (temp_a1 == temp_s4->unk6) {
            temp_ft1 = (s32)arg2;
            sp60 = (f32)temp_ft1;
            if (temp_a1 == temp_ft1 + 1) {
                var_v1_2 = temp_a1 - 1;
            } else {
                var_v1_2 = temp_ft1 + 1;
            }

            sp5C = var_v1_2;
            var_a0 = &var_s1->unkC[temp_ft1];
            var_a2 = &var_s1->unkC[var_v1_2];
        } else {
            var_v0 = var_s1->unkC;
            for (i = 0; i < temp_a1; i++) {
                var_fv0_2 = var_v0->unk10_0;

                if ((arg2 < var_fv0_2) && (var_a0 != NULL)) {
                    var_a2 = var_v0;
                    sp5C = var_fv0_2;
                    break;
                }
                if (arg2 <= var_fv0_2) {
                    var_a0 = var_v0;
                    var_a2 = var_v0;
                    sp5C = var_fv0_2;
                    sp60 = var_fv0_2;
                    break;
                }
                var_a0 = var_v0;
                var_v0++;
                sp60 = var_fv0_2;
            }
        }
        if (sp5C == sp60) {
            var_fv0 = 1.0f;
            var_fv1 = 0.0f;
        } else {
            var_fv0 = (sp5C - arg2) * (1.0f / (sp5C - sp60));
            var_fv1 = 1.0f - var_fv0;
        }
        var_s0->unk0 = (var_a2->unk0.x * var_fv1) + (var_a0->unk0.x * var_fv0);
        var_s0->unk4 = (var_a2->unk0.y * var_fv1) + (var_a0->unk0.y * var_fv0);
        var_s0->unk8 = (var_a2->unk0.z * var_fv1) + (var_a0->unk0.z * var_fv0);
        var_s0->unkC = (var_a2->unk0.w * var_fv1) + (var_a0->unk0.w * var_fv0);
        if (var_a0->unk10_15) {
            temp_fv1 = uvSqrtF(SQ(var_s0->unkC) + (SQ(var_s0->unk0) + SQ(var_s0->unk4) + SQ(var_s0->unk8)));
            if (temp_fv1 != 0.0f) {
                temp_fv1 = 1.0f / temp_fv1;
                var_s0->unk0 *= temp_fv1;
                var_s0->unk4 *= temp_fv1;
                var_s0->unk8 *= temp_fv1;
                var_s0->unkC *= temp_fv1;
            }
        }
        *var_s2 = var_s1->unk4;
        var_s2++;
        var_s0++;
        arg0->unk1AC++;
        var_s1 = var_s1->unk0;
    }
}

void func_80200EC0(s32 arg0, s32 arg1, f32 arg2, f32 arg3) {
    Unk80371120 sp18;

    uvJanimPoseGrid(&sp18, arg1, arg2, arg3);
    func_80200638(arg0, &sp18);
}

void uvJanimPoseGrid(Unk80371120* arg0, s32 arg1, f32 arg2, f32 arg3) {
    Unk80371120 sp1F0;
    Unk80371120 sp40;
    f32 sp3C;
    f32 sp38;
    uvGfxUnkStructAnimation* temp_a3;
    s32 var_a0;
    s32 var_a2;
    s32 pad;

    temp_a3 = gGfxUnkPtrs->unk1110[arg1];

    if (temp_a3 == NULL) {
        _uvDebugPrintf("uvJanimPoseGrid : animation [%d] not defined in level\n", arg1);
        return;
    }
    if (arg2 < 0.0f) {
        arg2 = (arg2 + 1.0f) - (s32)arg2;
    }
    if (arg2 > 1.0f) {
        arg2 -= (s32)arg2;
    }
    if (arg3 < 0.0f) {
        arg3 = (arg3 + 1.0f) - (s32)arg3;
    }
    if (arg3 > 1.0f) {
        arg3 -= (s32)arg3;
    }

    arg2 *= (temp_a3->unk9 - 1);
    arg3 *= (temp_a3->unk8 - 1);

    var_a2 = arg3;
    if ((temp_a3->unk8 - 1) < var_a2) {
        var_a2 = (temp_a3->unk8 - 1);
        var_a0 = (temp_a3->unk8 - 1);
    } else {
        if (var_a2 < (temp_a3->unk8 - 1)) {
            var_a0 = var_a2 + 1;
        } else {
            var_a0 = var_a2;
        }
    }

    sp3C = (f32)(temp_a3->unk9 * var_a2) + arg2;
    sp38 = (f32)(temp_a3->unk9 * var_a0) + arg2;

    if (temp_a3->unk6 < 2) {
        uvJanimPoseLine(arg0, arg1, 0.0f);
        return;
    }
    uvJanimPoseLine(&sp1F0, arg1, sp3C / (temp_a3->unk6 - 1));
    uvJanimPoseLine(&sp40, arg1, sp38 / (temp_a3->unk6 - 1));
    func_802006FC(arg0, &sp1F0, &sp40, arg3 - (s32)arg3);
}
