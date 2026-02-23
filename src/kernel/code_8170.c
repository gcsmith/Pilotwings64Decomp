#include "common.h"
#include <uv_graphics.h>

uvGfxUnkStruct* gGfxUnkPtrs = NULL;
s32 D_80248DD4 = 0xFFFFFFFF;
s32 D_80248DD8 = 0x00000000;

extern s32 D_802634C4;
extern s32 D_802634C8[];
extern f32 D_80263548[];
extern Vec3F D_802635C8[];

void func_802071C0(s32 arg0) {
    D_80248DD8 = arg0;
}

void _uvDbSortHits(void) {
    f32 temp_fa1;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_fa0;
    s32 temp_a3;
    s32 i;
    s32 j;

    if (D_802634C4 >= 0x20) {
        _uvDebugPrintf("_uvDbSortHits: too many hits\n");
        return;
    }

    for (i = 0; i < D_802634C4; i++) {
        if (D_80263548[i] == 2.0f) {
            continue;
        }
        for (j = i + 1; j < D_802634C4; j++) {
            if (FABS(D_80263548[i] - D_80263548[j]) < 0.001f) {
                D_80263548[i] = 2.0f;
                D_80263548[j] = 2.0f;
            }
        }
    }
    for (i = 0; i < D_802634C4; i++) {
        for (j = i; j < D_802634C4; j++) {

            if (D_80263548[j] < D_80263548[i]) {
                temp_fv0 = D_80263548[i];
                D_80263548[i] = D_80263548[j];
                D_80263548[j] = temp_fv0;

                temp_a3 = D_802634C8[i];
                temp_fa1 = D_802635C8[i].x;
                temp_ft4 = D_802635C8[i].y;
                temp_ft5 = D_802635C8[i].z;

                D_802634C8[i] = D_802634C8[j];
                D_802634C8[j] = temp_a3;

                D_802635C8[i].x = D_802635C8[j].x;
                D_802635C8[i].y = D_802635C8[j].y;
                D_802635C8[i].z = D_802635C8[j].z;
                D_802635C8[j].x = temp_fa1;
                D_802635C8[j].y = temp_ft4;
                D_802635C8[j].z = temp_ft5;
            }
        }
    }
    while (D_802634C4 != 0) {
        if (D_80263548[D_802634C4 - 1] != 2.0f) {
            break;
        }
        D_802634C4--;
    }
}

void func_80207410(f32 arg0, f32 arg1, f32 arg2, f32* arg3, f32* arg4, f32* arg5) {
    s32 temp_ft3;
    f32 temp_ft1;

    if (arg1 <= 0.0001f) {
        *arg3 = arg2;
        *arg4 = arg2;
        *arg5 = arg2;
        return;
    }
    if (arg0 < 0.0f) {
        arg0 += 1.0f;
    }
    if (arg0 == 1.0f) {
        arg0 = 0;
    }

    arg0 *= 6.0f;
    temp_ft3 = (s32) arg0;
    temp_ft1 = arg0 - temp_ft3;
    
    switch (temp_ft3) {
        case 0:
            *arg3 = arg2;
            *arg4 = (1.0f - (arg1 * (1.0f - temp_ft1))) * arg2;
            *arg5 = (1.0f - arg1) * arg2;
            break;
        case 1:
            *arg3 = (1.0f - (arg1 * temp_ft1)) * arg2;
            *arg4 = arg2;
            *arg5 = (1.0f - arg1) * arg2;
            break;
        case 2:
            *arg3 = (1.0f - arg1) * arg2;
            *arg4 = arg2;
            *arg5 = (1.0f - (arg1 * (1.0f - temp_ft1))) * arg2;
            break;
        case 3:
            *arg3 = (1.0f - arg1) * arg2;
            *arg4 = (1.0f - (arg1 * temp_ft1)) * arg2;
            *arg5 = arg2;
            break;
        case 4:
            *arg3 = (1.0f - (arg1 * (1.0f - temp_ft1))) * arg2;
            *arg4 = (1.0f - arg1) * arg2;
            *arg5 = arg2;
            break;
        case 5:
            *arg3 = arg2;
            *arg4 = (1.0f - arg1) * arg2;
            *arg5 = (1.0f - (arg1 * temp_ft1)) * arg2;
            break;
        default:
            break;
    }
}

void func_80207630(f32 arg0, f32 arg1, f32 arg2, f32* arg3, f32* arg4, f32* arg5) {
    f32 var_fv0;
    f32 var_fv1;

    var_fv0 = arg0;
    var_fv1 = arg0;
    if (arg0 < arg1) {
        var_fv0 = arg1;
    }
    if (arg1 < arg0) {
        var_fv1 = arg1;
    }
    if (var_fv0 < arg2) {
        var_fv0 = arg2;
    }
    if (arg2 < var_fv1) {
        var_fv1 = arg2;
    }
    *arg5 = var_fv0;
    if (var_fv0 == var_fv1) {
        *arg4 = 0.0f;
        *arg3 = -1.0f;
        return;
    }

    *arg4 = (var_fv0 - var_fv1) / var_fv0;
    if (arg0 == var_fv0) {
        *arg3 = ((var_fv0 - arg2) / (var_fv0 - var_fv1)) - ((var_fv0 - arg1) / (var_fv0 - var_fv1));
    } else if (arg1 == var_fv0) {
        *arg3 = ((var_fv0 - arg0) / (var_fv0 - var_fv1)) - ((var_fv0 - arg2) / (var_fv0 - var_fv1)) + 2.0f;
    } else if (arg2 == var_fv0) {
        *arg3 = ((var_fv0 - arg1) / (var_fv0 - var_fv1)) - ((var_fv0 - arg0) / (var_fv0 - var_fv1)) + 4.0f;
    }
    *arg3 *= 60.0f;

    if (*arg3 < 0.0f) {
        *arg3 += 360.0f;
    }
    *arg3 /= 360.0f;
}

void func_802077BC(s32 arg0, s32 arg1, s32 arg2, void* arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9) {
    u8* var_a0;
    u16* var_a1;
    f32 var_fv0;
    f32 var_fv1;
    s32 i;
    f32 temp_fa0;
    f32 r;
    f32 g;
    f32 b;

    if (arg5 < arg4) {
        if (arg6 < arg4) {
            var_fv0 = arg4;
            var_fv1 = arg7;
        } else {
            var_fv0 = arg6;
            var_fv1 = arg9;
        }
    } else if (arg6 < arg5) {
        var_fv0 = arg5;
        var_fv1 = arg8;
    } else {
        var_fv0 = arg6;
        var_fv1 = arg9;
    }

    if (arg0 != 1) {
        if (arg0 != 2) {
            if (arg0 == 4) {
                arg4 *= (1.0f - arg7) * 31.0f;
                arg5 *= (1.0f - arg8) * 31.0f;
                arg6 *= (1.0f - arg9) * 31.0f;
                var_a1 = arg3;
                for (i = 0; i < arg2 / 2; i++) {
                    r = ((var_a1[i] & 0xF800) >> 11);
                    g = ((var_a1[i] & 0x7C0) >> 6);
                    b = ((var_a1[i] & 0x3E) >> 1);
                    var_a1[i] = ((s32) ((arg7 * r) + arg4) << 11) | ((s32) ((arg8 * g) + arg5) << 6) | ((s32) ((arg9 * b) + arg6) << 1) | (var_a1[i] & 1);
                }
            }
        } else {
            switch (arg1) {
                case 4:
                    var_fv0 *= (1.0f - var_fv1) * 7.0f;
                    var_a0 = arg3;
                    for (i = 0; i < arg2; i++) {
                        temp_fa0 = (var_a0[i] & 0xE) >> 1;
                        var_a0[i] = (var_a0[i] & 0xF1) | ((s32) ((var_fv1 * temp_fa0) + var_fv0) << 1);
                        temp_fa0 = (var_a0[i] & 0xE0) >> 5;
                        var_a0[i] = ((s32) ((var_fv1 * temp_fa0) + var_fv0) << 5) | (var_a0[i] & 0x1F);
                    }
                    break;
                case 8:
                    var_fv0 *= (1.0f - var_fv1) * 15.0f;
                    var_a0 = arg3;
                    for (i = 0; i < arg2; i++) {
                        temp_fa0 = (var_a0[i] & 0xF0) >> 4;
                        var_a0[i] = (((s32) ((var_fv1 * temp_fa0) + var_fv0) & 0xF) << 4) | (var_a0[i] & 0xF);
                    }
                    break;
                case 16:
                    var_fv0 *= (1.0f - var_fv1) * 255.0f;
                    var_a1 = arg3;
                    for (i = 0; i < arg2 / 2; i++) {
                        temp_fa0 = (var_a1[i] & 0xFF00) >> 8;
                        var_a1[i] = (((s32) ((var_fv1 * temp_fa0) + var_fv0) & 0xFF) << 8) | (var_a1[i] & 0xFF);
                    }
                    break;
            }
        }
    } else {
        switch (arg1) {
            case 4:
                var_fv0 *= (1.0f - var_fv1) * 15.0f;
                var_a0 = arg3;
                for (i = 0; i < arg2; i++) {
                    temp_fa0 = (var_a0[i] & 0xF);
                    var_a0[i] = (var_a0[i] & 0xF0) | ((s32) ((var_fv1 * temp_fa0) + var_fv0) & 0xF);
                    temp_fa0 = (var_a0[i] & 0xF0) >> 4;
                    var_a0[i] = (((s32) ((var_fv1 * temp_fa0) + var_fv0) & 0xF) << 4) | (var_a0[i] & 0xF);
                }
                break;
            case 8:
                var_fv0 *= (1.0f - var_fv1) * 255.0f;
                var_a0 = arg3;
                for (i = 0; i < arg2; i++) {
                    temp_fa0 = var_a0[i];
                    var_a0[i] = (var_fv1 * temp_fa0) + var_fv0;
                }
                break;
            case 16:
                var_fv0 *= (1.0f - var_fv1) * 65535.0f;
                var_a1 = arg3;
                for (i = 0; i < arg2 / 2; i++) {
                    temp_fa0 = var_a1[i];
                    var_a1[i] = (var_fv1 * temp_fa0) + var_fv0;
                }
                break;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/func_8020921C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/func_8020ABAC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/func_8020B4AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/func_8020B894.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/func_8020D0D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/func_8020E760.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/func_8020EF20.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/func_8020F298.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/func_8020F5A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/func_8020F630.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/func_8020F99C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/func_8020F9F4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/uvTerraGetBox.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/uvModelGetPosm.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/uvModelGetProps.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/uvTerraGetPt.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/uvTerraGetSeg.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/uvTerraGetColor.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/uvTerraGetState.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/uvTerraGetPlane.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/_uvSurfGetNorm.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/uvSobjGetPt.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/uvSobjGetSeg.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/func_80212008.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/func_8021215C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/func_80212480.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/func_80212604.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/func_80212788.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/func_802129B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/func_80212FF4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/func_80213364.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/func_802133C8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/func_802134F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/func_80213790.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/func_802139C8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/func_80213C24.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/func_80213EE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/func_802140BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/func_802141CC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/func_80214450.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/func_80214840.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/func_80214900.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/func_80214B3C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/func_80214C64.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/_uvSegInMboxs.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/func_802153D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/func_80215BC4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/func_80215CBC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/func_80215D7C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/func_80215E7C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/uvDbColorModel.s")
