#include "common.h"
#include "macros.h"
#include <uv_dobj.h>
#include <uv_math.h>
#include <uv_model.h>
#include <uv_sched.h>
#include <uv_util.h>
#include <libc/stdarg.h>
#include <uv_graphics.h>
#include "kernel/code_58E0.h"

// TODO FIXME fix for gSPPerspNormalize, due to older f3d ucode
#undef gSPPerspNormalize
#define gSPPerspNormalize(pkt, s)                   \
    {                                               \
        Gfx* _g = (Gfx*)(pkt);                      \
                                                    \
        _g->words.w0 = _SHIFTL(G_RDPHALF_1, 24, 8); \
        _g->words.w1 = (s);                         \
    }

s32 func_80206F64(void*, f32, f32, f32, f32);
void func_80215E7C(uvGfxUnkStructModel*);

extern u8 D_80269B80[300];
extern u16 D_80269CB0[100];
extern u16 D_80269F08;
extern u16 D_80269F0A;
extern Mtx4F D_80265080[300];

void uvDobjModel(s32 objId, s32 mdlId) {
    uvGfxUnkStructModel** temp_a3;
    Unk80263780* var_t2;
    s32 var_v0_3;
    s32 i;
    s32 j;
    u8 temp_t0;
    u8 var_a3_2;

    var_t2 = &D_80263780[objId];
    temp_a3 = gGfxUnkPtrs->unkC8;

    if (mdlId == var_t2->unk0) {
        return;
    }

    if (objId >= 100) {
        _uvDebugPrintf("uvDobjModel - invalid object id number [%d]\n", objId);
        return;
    }
    if (mdlId == 0xFFFF) {
        temp_t0 = temp_a3[var_t2->unk0]->unk18;

        for (i = 0; i < temp_t0; i++) {
            D_80269B80[var_t2->unk2[i]] = 0;
        }

        var_t2->unk0 = 0xFFFF;
        for (i = 0; i < D_80269F0A; i++) {
            if (objId == D_80269CB0[i]) {
                for (j = i; j < D_80269F0A; j++) {
                    D_80269CB0[j] = D_80269CB0[j + 1];
                }
                D_80269F0A--;
            }
        }
    } else {
        if (gGfxUnkPtrs->unkC8[mdlId] == NULL) {
            _uvDebugPrintf("uvDobjModel ( %d, %d ) -- model does not exist in level\n", objId, mdlId);
            return;
        }
        var_t2->unk3C = 0;
        var_t2->unk38 = temp_a3[mdlId]->unk1C;

        if (var_t2->unk0 == 0xFFFF) {
            temp_t0 = 0;
        } else {
            if (temp_a3[var_t2->unk0] != NULL) {
                temp_t0 = temp_a3[var_t2->unk0]->unk18;
            } else {
                temp_t0 = 0;
                j = -1;
                for (i = 0; i < 25; i++) {
                    if (j >= var_t2->unk2[i]) {
                        break;
                    }
                    j = var_t2->unk2[i];
                    D_80269B80[j] = 0;
                    if (j) { }
                }
            }
        }

        var_a3_2 = temp_a3[mdlId]->unk18;

        if (var_a3_2 < temp_t0) {
            for (i = temp_t0 - 1; i >= var_a3_2; i--) {
                D_80269B80[var_t2->unk2[i]] = 0;
            }
        } else {
            if (temp_t0 < var_a3_2) {
                var_v0_3 = 0;
                for (i = temp_t0; i < var_a3_2; i++) {
                    for (j = var_v0_3; j < 300; j++) {
                        if (D_80269B80[j] == 0) {
                            break;
                        }
                    }

                    if (j == 300) {
                        _uvDebugPrintf("uvDobjModel : WARNING not enough DL part transforms\n");
                        return;
                    }

                    D_80269B80[j] = 1;
                    var_t2->unk2[i] = j;
                    var_v0_3 = j + 1;
                }
            }
        }

        var_t2->unk2[var_a3_2] = 0;

        for (i = 0; i < var_a3_2; i++) {
            uvMat4Copy(&D_80265080[var_t2->unk2[i]], (u32)temp_a3[mdlId]->unk14 + i * sizeof(Mtx4F));
        }
        var_t2->unk0 = mdlId;
        var_t2->unk34 = 3;
    }
}

void uvDobjProps(s32 objId, ...) {
    s16 a1;
    f32 f0;
    Unk80263780* temp_s1;
    s32 var_v0;
    s32 var_v1;
    va_list args;

    if (objId >= 0x64) {
        _uvDebugPrintf("uvDobjProps - invalid object id number [%d]\n", objId);
        return;
    }

    temp_s1 = &D_80263780[objId];
    if (temp_s1->unk0 == 0xFFFF) {
        _uvDebugPrintf("uvDobjProps: cannot be set before mod id\n");
        return;
    }

    va_start(args, objId);
    while (1) {
        a1 = va_arg(args, s32);
        switch (a1) {
        case 0:
            return;
        case 3:
            f0 = va_arg(args, f64);
            temp_s1->unk38 = gGfxUnkPtrs->unkC8[temp_s1->unk0]->unk1C * f0;
            break;
        case 4:
            var_v0 = va_arg(args, s32);
            temp_s1->unk3C &= ~(1 << var_v0);
            break;
        case 5:
            var_v0 = va_arg(args, s32);
            temp_s1->unk3C |= (1 << var_v0);
            break;
        default:
            _uvDebugPrintf("uvDobjProps: unknown property [%d]\n", a1);
            break;
        }
    }
    va_end(args);
}

void uvDobjPosm(s32 objId, s32 part, Mtx4F* src) {
    uvGfxUnkStructModel* temp_v1;
    Unk80263780* temp_v0;
    f32 temp_fv0;

    if (objId >= 0x65) {
        _uvDebugPrintf("uvDobjPosm - invalid object id number [%d]\n", objId);
        return;
    }
    temp_v0 = &D_80263780[objId];
    if (temp_v0->unk0 >= 0x190) {
        _uvDebugPrintf("uvDobjPosm: null object id %d\n", objId);
        return;
    }

    uvMat4Copy(&D_80265080[temp_v0->unk2[part]], src);

    temp_v1 = gGfxUnkPtrs->unkC8[temp_v0->unk0];
    if (temp_v1 == NULL) {
        _uvDebugPrintf("uvDobjPosm: model %d not in level\n", temp_v0->unk0);
        return;
    }
    if (part >= temp_v1->unk8->unk4) {
        _uvDebugPrintf("uvDobjPosm: part %d not defined for model %d in obj %d\n", part, temp_v0->unk0, objId);
        return;
    }
    if (part == 0) {
        if (temp_v1->unk20 != 1.0f) {
            temp_fv0 = 1.0f / temp_v1->unk20;
            uvMat4Scale(&D_80265080[temp_v0->unk2[part]], temp_fv0, temp_fv0, temp_fv0);
        }
    } else {
        D_80265080[temp_v0->unk2[part]].m[3][0] *= temp_v1->unk20;
        D_80265080[temp_v0->unk2[part]].m[3][1] *= temp_v1->unk20;
        D_80265080[temp_v0->unk2[part]].m[3][2] *= temp_v1->unk20;
    }
}

void uvDobjGetPosm(s32 objId, s32 arg1, Mtx4F* dst) {
    Unk80263780* sp24;
    uvGfxUnkStructModel* temp_v0;

    if (objId >= 0x65) {
        _uvDebugPrintf("uvDobjPosm - invalid object id number [%d]\n", objId);
        return;
    }
    sp24 = &D_80263780[objId];
    if (sp24->unk0 >= 0x190) {
        _uvDebugPrintf("uvDobjGetPosm: null object id %d\n", objId);
        return;
    }
    uvMat4Copy(dst, &D_80265080[sp24->unk2[arg1]]);
    temp_v0 = gGfxUnkPtrs->unkC8[sp24->unk0];
    if (arg1 == 0) {
        if (temp_v0->unk20 != 1.0f) {
            uvMat4Scale(dst, temp_v0->unk20, temp_v0->unk20, temp_v0->unk20);
        }
    } else {
        dst->m[3][0] /= temp_v0->unk20;
        dst->m[3][1] /= temp_v0->unk20;
        dst->m[3][2] /= temp_v0->unk20;
    }
}

void uvDobjState(s32 objId, s32 arg1) {
    s32 i;
    s32 j;

    if (objId >= 0x65) {
        _uvDebugPrintf("uvDobjState - invalid object id number [%d]\n", objId);
        return;
    }
    if (arg1 & 4) {
        for (i = 0; i < D_80269F0A; i++) {
            if (objId == D_80269CB0[i]) {
                break;
            }
        }
        if (i == D_80269F0A) {
            D_80269CB0[i] = objId;
            D_80269F0A++;
        }
    } else {
        for (i = 0; i < D_80269F0A; i++) {
            if (objId == D_80269CB0[i]) {
                for (j = i; j < D_80269F0A; j++) {
                    D_80269CB0[j] = D_80269CB0[j + 1];
                }
                D_80269F0A--;
            }
        }
    }
    D_80263780[objId].unk34 = arg1;
}

void uvDobjSetState(s32 objId, s32 flags) {
    if (objId >= 0x65) {
        _uvDebugPrintf("uvDobjSetState: no dobj %d\n", objId);
        return;
    }

    D_80263780[objId].unk34 |= flags;
}

void uvDobjClearState(s32 objId, s32 flags) {
    if (objId >= 0x65) {
        _uvDebugPrintf("uvDobjSetState: no dobj %d\n", objId);
        return;
    }

    D_80263780[objId].unk34 &= ~flags;
}

s32 uvDobjAllocIdx(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_80263780); i++) {
        if (D_80263780[i].unk0 == 0xFFFF) {
            return i;
        }
    }
    return 0xFFFF;
}

void uvDobjInit(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_80263780); i++) {
        D_80263780[i].unk0 = 0xFFFF;
    }

    for (i = 0; i < ARRAY_COUNT(D_80269CB0); i++) {
        D_80269CB0[i] = 0xFFFF;
    }

    for (i = 0; i < ARRAY_COUNT(D_80269B80); i++) {
        D_80269B80[i] = 0;
    }

    for (i = 0; i < ARRAY_COUNT(D_80265080); i++) {
        uvMat4SetIdentity(&D_80265080[i]);
    }
    D_80269F0A = 0;
}

void _uvDobjsDraw(UnkStruct_80204D94* arg0, s32 arg1) {
    Unk80263780* var_s2;
    s32 i;
    f32 temp_fv0_2;
    f32 temp_fv1;
    s32 var_v1;
    s32 var_a0;
    u8 spBF;
    f32 temp_fv0;
    f32 temp_fs5;
    s32 pad;
    f32 temp_fs1;
    f32 temp_fs2;
    f32 temp_fs0;
    f32 spA0;
    f32 sp9C;
    f32 sp98;
    uvGfxUnkStructModel* temp_s1;
    Mtx4F* temp_v0_2;

    D_80269F08 = 0;
    spA0 = arg0->unk110.m[3][0];
    sp9C = arg0->unk110.m[3][1];
    sp98 = arg0->unk110.m[3][2];

    for (i = 0; i < 100; i++) {
        var_s2 = &D_80263780[i];
        if (var_s2->unk0 == 0xFFFF) {
            continue;
        }
        if (!(var_s2->unk34 & 2) || (var_s2->unk34 & 4)) {
            continue;
        }
        temp_s1 = gGfxUnkPtrs->unkC8[var_s2->unk0];
        if (temp_s1 == NULL) {
            _uvDebugPrintf("_uvDobjsDraw: model %d not in level\n", var_s2->unk0);
            continue;
        }
        uvModelGetProps(var_s2->unk0, 5, &spBF, 0);
        if (spBF - arg1 != 0) {
            continue;
        }
        temp_v0_2 = &D_80265080[var_s2->unk2[0]];
        temp_fv0 = temp_v0_2->m[3][0];
        temp_fs5 = temp_v0_2->m[3][1];

        temp_fs1 = temp_v0_2->m[3][0] - spA0;
        temp_fs2 = temp_v0_2->m[3][1] - sp9C;
        temp_fs0 = temp_v0_2->m[3][2] - sp98;
        temp_fv0_2 = uvSqrtF(SQ(temp_fs1) + SQ(temp_fs2) + SQ(temp_fs0));
        temp_fv1 = var_s2->unk38;
        if ((temp_fv0_2 < (arg0->unk1FC + temp_fv1)) && (func_80206F64(arg0->unk2E0, temp_fs1, temp_fs2, temp_fs0, temp_fv1) != 0)) {
            if (arg0->unk204 == 1.0f) {
                var_v1 = uvDobj_80217AB4(temp_s1, temp_fv0_2);
            } else {
                var_v1 = uvDobj_80217AB4(temp_s1, arg0->unk204 * temp_fv0_2);
            }
            if (var_v1 == 0xFF) {
                continue;
            }
            if (arg1 != 0) {
                uvDobj_80217B4C(var_s2, temp_s1, var_v1);
            } else if (temp_s1->unk8[var_v1].unk5 != 0) {
                if (temp_s1->unk11 & 1) {
                    var_a0 = 3;
                } else {
                    var_a0 = -3;
                }
                _uvSortAdd(var_a0, temp_fv0_2, var_s2, arg0, temp_fv0, temp_fs5, var_v1, temp_fs1, temp_fs2);
            } else {
                if (temp_s1->unk11 & 1) {
                    var_a0 = 2;
                } else {
                    var_a0 = -2;
                }
                _uvSortAdd(var_a0, temp_fv0_2, var_s2, arg0, temp_fv0, temp_fs5, var_v1);
            }
        }
    }
}

void uvDobj_8021771C(UnkStruct_80204D94* arg0) {
    uvGfxUnkStructModel* temp_s0;
    Unk80263780* temp_s1;
    s32 i;
    s32 pad;
    Mtx4F sp128;
    Mtx spE8;
    f32 temp_fs2;
    f32 temp_fs3;
    f32 temp_fs4;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fa0;
    f32 var_fs0;
    f32 temp_fv1_x;
    f32 temp_fa0_x;
    f32 temp_fa1_x;
    f32 temp_ft4_x;
    u8 var_v0;

    if (D_80269F0A == 0) {
        return;
    }
    uvGfx_80222A98();
    uvGfxEnableZBuffer(TRUE);
    for (i = 0; i < D_80269F0A; i++) {
        temp_s1 = &D_80263780[D_80269CB0[i]];
        if (temp_s1->unk0 == 0xFFFF) {
            continue;
        }
        if (!(temp_s1->unk34 & 2)) {
            continue;
        }
        temp_s0 = gGfxUnkPtrs->unkC8[temp_s1->unk0];

        temp_fs3 = D_80265080[temp_s1->unk2[0]].m[3][0] - arg0->unk110.m[3][0];
        temp_fs4 = D_80265080[temp_s1->unk2[0]].m[3][1] - arg0->unk110.m[3][1];
        temp_fv0 = D_80265080[temp_s1->unk2[0]].m[3][2] - arg0->unk110.m[3][2];
        temp_fv0_2 = uvSqrtF(SQ(temp_fs3) + SQ(temp_fs4) + SQ(temp_fv0));

        temp_fa0 = temp_fv0_2 - temp_s1->unk38;
        temp_fs2 = temp_s1->unk38 + temp_fv0_2;
        if (temp_fa0 > 0.1f) {
            var_fs0 = temp_fa0;
        } else {
            var_fs0 = 0.1f;
        }
        temp_fv1_x = arg0->unk1E8 * (var_fs0 / arg0->unk1F8);
        temp_fa0_x = arg0->unk1EC * (var_fs0 / arg0->unk1F8);
        temp_ft4_x = arg0->unk1F4 * (var_fs0 / arg0->unk1F8);
        temp_fa1_x = arg0->unk1F0 * (var_fs0 / arg0->unk1F8);
        uvMat4SetFrustrum(&sp128, temp_fv1_x, temp_fa0_x, temp_fa1_x, temp_ft4_x, var_fs0, temp_fs2);
        uvMat4CopyF2L(&spE8, &sp128);
        uvGfxMtxProj(spE8);
        gSPPerspNormalize(gGfxDisplayListHead++, (s16)(131072.0f / (temp_fs2 + var_fs0)));

        if (arg0->unk204 == 1.0f) {
            var_v0 = uvDobj_80217AB4(temp_s0, temp_fv0_2);
        } else {
            var_v0 = uvDobj_80217AB4(temp_s0, arg0->unk204 * temp_fv0_2);
        }

        if (var_v0 == 0xFF) {
            continue;
        }

        if (temp_s0->unk8[var_v0].unk5 != 0) {
            uvDobj_80217E24(temp_s1, temp_s0, var_v0, temp_fs3, temp_fs4);
        } else {
            uvDobj_80217B4C(temp_s1, temp_s0, var_v0);
        }
        gSPPopMatrix(gGfxDisplayListHead++, G_MTX_PROJECTION);
    }
}

u8 uvDobj_80217AB4(uvGfxUnkStructModel* arg0, f32 arg1) {
    u8 temp_v1;
    u8 i;
    f32* temp_v0;

    temp_v0 = arg0->unkC;
    temp_v1 = arg0->unk10;
    if (temp_v0[temp_v1 - 1] <= arg1) {
        return 0xFF;
    }

    for (i = temp_v1; i > 0; i--) {
        if (temp_v0[i - 1] < arg1) {
            return i;
        }
    }
    return 0;
}

extern s32 D_80269D78[];

s32 uvDobj_80217B34(s32** arg0) {
    *arg0 = D_80269D78;
    return D_80269F08;
}

extern s32 D_80248DD8;

void uvDobj_80217B4C(Unk80263780* arg0, uvGfxUnkStructModel* arg1, u8 arg2) {
    uvGfxUnkStruct10* temp_s2;
    uvGfxUnkStruct8* temp_s7;
    s32 i;
    s32 j;
    s32 temp_s3;
    s32 temp_v1;
    Mtx4F sp50;

    D_80269D78[D_80269F08] = arg0 - D_80263780;
    D_80269F08++;
    if (arg0->unk34 & 8) {
        uvGfx_80223C00();
    }

    temp_s7 = &arg1->unk8[arg2];
    for (i = 0; i < temp_s7->unk4; i++) {
        temp_s2 = &temp_s7->unk0[i];
        if (i == 0) {
            uvGfx_802236CC(&D_80265080[arg0->unk2[0]]);
        } else {
            uvGfxMtxViewMul(&D_80265080[arg0->unk2[i]], 1);
        }
        if (temp_s2->unkD != 0) {
            uvGfxLookAt(&D_80265080[arg0->unk2[i]]);
        }
        if (!(arg0->unk3C & (1 << i))) {
            for (j = 0; j < temp_s2->unk4; j++) {
                if (arg0->unk34 & 0x20) {
                    temp_s3 = temp_s2->unk0[j].state;
                    temp_s2->unk0[j].state |= GFX_STATE_10000000;
                    uvGfxStateDraw(&temp_s2->unk0[j]);
                    temp_s2->unk0[j].state = temp_s3;
                } else {
                    uvGfxStateDraw(&temp_s2->unk0[j]);
                }
            }
        }
        if (i == temp_s7->unk4 - 1) {
            break;
        }
        temp_v1 = temp_s7->unk0[i].unk6 - temp_s7->unk0[i + 1].unk6;
        for (j = 0; j <= temp_v1; j++) {
            uvGfxMtxViewPop();
        }
    }
    temp_v1 = temp_s7->unk0[temp_s7->unk4 - 1].unk6;
    for (i = 0; i <= temp_v1; i++) {
        uvGfxMtxViewPop();
    }
    if (D_80248DD8 != 0) {
        uvMat4Copy(&sp50, &D_80265080[arg0->unk2[0]]);
        uvMat4Scale(&sp50, arg1->unk20, arg1->unk20, arg1->unk20);
        uvGfx_802236CC(&sp50);
        func_80215E7C(arg1);
        uvGfxMtxViewPop();
    }
}

void uvDobj_80217E24(Unk80263780* arg0, uvGfxUnkStructModel* arg1, u8 arg2, f32 arg3, f32 arg4) {
    uvGfxUnkStruct10* temp_s2;
    uvGfxUnkStruct8* temp_s5;
    Mtx4F* temp_s7;
    s32 i;
    s32 j;
    s32 temp_v1;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 var_fv1;

    sp54 = arg1->unk20;
    D_80269D78[D_80269F08] = arg0 - D_80263780;
    D_80269F08++;
    temp_s5 = &arg1->unk8[arg2];
    temp_s7 = &D_80265080[arg0->unk2[0]];
    sp50 = temp_s7->m[0][0];
    sp4C = temp_s7->m[0][1];
    sp48 = temp_s7->m[1][0];
    sp44 = temp_s7->m[1][1];

    var_fv1 = MAX(1.0f, uvSqrtF(SQ(arg3) + SQ(arg4)));

    arg3 /= var_fv1;
    arg4 /= var_fv1;

    temp_s7->m[0][0] = -arg4 / sp54;
    temp_s7->m[0][1] = arg3 / sp54;
    temp_s7->m[1][1] = -arg4 / sp54;
    temp_s7->m[1][0] = -arg3 / sp54;

    for (i = 0; i < temp_s5->unk4; i++) {
        temp_s2 = &temp_s5->unk0[i];
        if (i == 0) {
            uvGfx_802236CC(&D_80265080[arg0->unk2[i]]);
        } else {
            uvGfxMtxViewMul(&D_80265080[arg0->unk2[i]], 1);
        }

        for (j = 0; j < temp_s2->unk4; j++) {
            uvGfxStateDraw(&temp_s2->unk0[j]);
        }
        if (i == temp_s5->unk4 - 1) {
            break;
        }
        temp_v1 = temp_s5->unk0[i].unk6 - temp_s5->unk0[i + 1].unk6;
        for (j = 0; j <= temp_v1; j++) {
            uvGfxMtxViewPop();
        }
    }
    temp_v1 = temp_s5->unk0[temp_s5->unk4 - 1].unk6;
    for (i = 0; i <= temp_v1; i++) {
        uvGfxMtxViewPop();
    }
    temp_s7->m[0][0] = sp50;
    temp_s7->m[0][1] = sp4C;
    temp_s7->m[1][0] = sp48;
    temp_s7->m[1][1] = sp44;
}

void uvDobj_802180DC(s32 arg0, Unk80371120* arg1) {
    Unk80263780* var_s2;
    s32 i;
    uvGfxUnkStructModel* temp_v0;
    Unk8022B0A0* var_s3;

    var_s2 = &D_80263780[arg0];
    temp_v0 = gGfxUnkPtrs->unkC8[var_s2->unk0];
    var_s3 = arg1->unk0;

    if (temp_v0->unk18 > 1) {
        arg1->unk1AC = temp_v0->unk18 - 1;
    } else {
        arg1->unk1AC = 0;
    }

    for (i = 0; i < arg1->unk1AC; i++, var_s3++) {
        func_8022B0A0(var_s3, &D_80265080[var_s2->unk2[i + 1]]);
        arg1->unk190[i] = i + 1;
    }
}
