#include "common.h"
#include <uv_graphics.h>
#include <uv_memory.h>
#include <libc/stdarg.h>

LevelData* gGfxUnkPtrs = NULL;
s32 D_80248DD4 = -1;
s32 D_80248DD8 = 0x00000000;

extern s32 D_802634C4;
extern s32 D_802634C8[];
extern f32 D_80263548[];
extern Vec3F D_802635C8[];

extern f32 D_80263748;
extern f32 D_8026374C;
extern f32 D_80263750;
extern f32 D_80263754;
extern f32 D_80263758;
extern f32 D_8026375C;
extern f32 D_80263760;
extern f32 D_80263764;
extern f32 D_80263768;
extern f32 D_8026376C;
extern f32 D_80263770;
extern f32 D_80263774;
extern s32 D_802B8934;

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
    } else {
        if (arg6 < arg5) {
            var_fv0 = arg5;
            var_fv1 = arg8;
        } else {
            var_fv0 = arg6;
            var_fv1 = arg9;
        }
    }

    switch (arg0) {
        case 4:
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
            break;
        case 2:
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
            break;
        case 1:
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
            break;
    }
}

void func_8020921C(s32 arg0, s32 arg1, s32 arg2, void* arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9) {
    s32 i;
    f32 spB0;
    f32 spAC;
    f32 spA8;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    u16* var_s0;
    u8* var_v0;
    f32 temp_fv1;
    f32 temp_fa0;
    s32 pad;
    f32 sp84;
    f32 sp80;
    f32 sp7C;
    f32 sp78;
    s32 pad2[2];

    switch (arg0) {
        case 4:
            var_s0 = arg3;
            sp50 = (1.0f - arg7) * arg4;
            sp4C = (1.0f - arg8) * arg5;
            sp48 = (1.0f - arg9) * arg6;
            for (i = 0; i < arg2 / 2; i++) {
                func_80207630((f32) ((s32) (var_s0[i] & 0xF800) >> 0xB) / 31.0f, (f32) ((s32) (var_s0[i] & 0x7C0) >> 6) / 31.0f, (f32) ((s32) (var_s0[i] & 0x3E) >> 1) / 31.0f, &spB0, &spAC, &spA8);
                func_80207410((arg7 * spB0) + sp50, (arg8 * spAC) + sp4C, (arg9 * spA8) + sp48, &sp80, &sp7C, &sp78);
                sp80 *= 31.0f;
                sp7C *= 31.0f;
                sp78 *= 31.0f;
                var_s0[i] = ((s32)sp80 << 11) | ((s32)sp7C << 6) | ((s32)sp78 << 1) | (var_s0[i] & 1);
            }
            break;
        case 2:
            switch (arg1) {
                case 4:
                    temp_fv1 = (1.0f - arg9) * arg6 * 7.0f;
                    var_v0 = arg3;
                    for (i = 0; i < arg2; i++) {
                        temp_fa0 = (var_v0[i] & 0xE) >> 1;
                        var_v0[i] = (var_v0[i] & 0xF1) | (((s32) ((arg9 * temp_fa0) + temp_fv1)) << 1);
                        temp_fa0 = (var_v0[i] & 0xE0) >> 5;
                        //! @bug sp84 uninitialised!
                        var_v0[i] = (((s32) ((arg9 * temp_fa0) + sp84)) << 5) | (var_v0[i] & 0x1F);
                    }
                    break;
                case 8:
                    temp_fv1 = (1.0f - arg9) * arg6 * 15.0f;
                    var_v0 = arg3;
                    for (i = 0; i < arg2; i++) {
                        temp_fa0 = (var_v0[i] & 0xF0) >> 4;
                        var_v0[i] = ((((s32) ((arg9 * temp_fa0) + temp_fv1)) & 0xF) << 4) | (var_v0[i] & 0xF);
                    }
                    break;
                case 16:
                    temp_fv1 = (1.0f - arg9) * arg6 * 255.0f;
                    var_s0 = arg3;
                    for (i = 0; i < arg2 / 2; i++) {
                        temp_fa0 = (var_s0[i] & 0xFF00) >> 8;
                        var_s0[i] = ((((s32) ((arg9 * temp_fa0) + temp_fv1)) & 0xFF) << 8) | (var_s0[i] & 0xFF);
                    }
                    break;
            }
            break;
        case 1:
            switch (arg1) {
                case 4:
                    temp_fv1 = (1.0f - arg9) * arg6 * 15.0f;
                    var_v0 = arg3;
                    for (i = 0; i < arg2; i++) {
                        temp_fa0 = var_v0[i] & 0xF;
                        var_v0[i] = (var_v0[i] & 0xF0) | (((s32) ((arg9 * temp_fa0) + temp_fv1)) & 0xF);
                        temp_fa0 = (var_v0[i] & 0xF0) >> 4;
                        var_v0[i] = ((((s32) ((arg9 * temp_fa0) + temp_fv1)) & 0xF) << 4) | (var_v0[i] & 0xF);
                    }
                    break;
                case 8:
                    temp_fv1 = (1.0f - arg9) * arg6 * 255.0f;
                    var_v0 = arg3;
                    for (i = 0; i < arg2; i++) {
                        temp_fa0 = var_v0[i];
                        var_v0[i] = (arg9 * temp_fa0) + temp_fv1;
                    }
                    break;
                case 16:
                    temp_fv1 = (1.0f - arg9) * arg6 * 65535.0f;
                    var_s0 = arg3;
                    for (i = 0; i < arg2 / 2; i++) {
                        temp_fa0 = var_s0[i];
                        var_s0[i] = (arg9 * temp_fa0) + temp_fv1;
                    }
                    break;
            }
            break;
    }
}

void func_8020ABAC(Vtx* arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    s32 i;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 temp_fs3;
    f32 temp_fs5;
    f32 sp40;
    f32 sp3C;
    Vtx* temp_a3;
    f32 temp_fa0;
    f32 var_fv0;

    temp_ft4 = arg5 * arg5 * arg5;
    temp_ft5 = arg6 * arg6 * arg6;
    temp_fs3 = arg7 * arg7 * arg7;
    temp_fs5 = (1.0f - temp_ft4) * 255.0f * arg2;
    sp40 = (1.0f - temp_ft5) * 255.0f * arg3;
    sp3C = (1.0f - temp_fs3) * 255.0f * arg4;
    arg2 = arg2 * ((1.0f - arg5) * 255.0f);
    arg3 = arg3 * ((1.0f - arg6) * 255.0f);
    arg4 = arg4 * ((1.0f - arg7) * 255.0f);

    for (i = 0; i < arg1; i++) {
        temp_a3 = &arg0[i];
        temp_fa0 = temp_a3->v.cn[0];
        if (temp_a3->v.flag != 0) {
            var_fv0 = (arg5 * temp_fa0) + arg2;
        } else {
            var_fv0 = (temp_ft4 * temp_fa0) + temp_fs5;
        }
        temp_a3->v.cn[0] = var_fv0;
        temp_fa0 = temp_a3->v.cn[1];
        if (temp_a3->v.flag != 0) {
            var_fv0 = (arg6 * temp_fa0) + arg3;
        } else {
            var_fv0 = (temp_ft5 * temp_fa0) + sp40;
        }
        temp_a3->v.cn[1] = var_fv0;
        temp_fa0 = temp_a3->v.cn[2];
        if (temp_a3->v.flag != 0) {
            var_fv0 = (arg7 * temp_fa0) + arg4;
        } else {
            var_fv0 = (temp_fs3 * temp_fa0) + sp3C;
        }
        temp_a3->v.cn[2] = var_fv0;
    }
}

void func_8020B4AC(Vtx* arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    s32 i;
    Vtx* temp_s0;
    f32 spBC;
    f32 spB8;
    f32 spB4;
    f32 var_fa0;
    f32 var_fa1;
    f32 var_fv0;
    f32 spA4;
    f32 spA0;
    f32 sp9C;
    f32 sp98;
    f32 sp94;
    f32 sp90;
    f32 temp_fs4;
    s32 pad;

    temp_fs4 = arg7 * arg7 * arg7;
    sp98 = (1.0f - arg5) * arg2;
    sp90 = (1.0f - arg6) * arg3;
    sp94 = (1.0f - temp_fs4) * arg4;
    arg2 = (1.0f - arg5) * arg2;
    arg3 = (1.0f - arg6) * arg3;
    arg4 = (1.0f - arg7) * arg4;
    for (i = 0; i < arg1; i++) {
        temp_s0 = &arg0[i];

        func_80207630(temp_s0->v.cn[0] / 255.0f, temp_s0->v.cn[1] / 255.0f, temp_s0->v.cn[2] / 255.0f, &spBC, &spB8, &spB4);
        if (temp_s0->v.flag != 0) {
            var_fa0 = (arg5 * spBC) + arg2;
            var_fa1 = (arg6 * spB8) + arg3;
            var_fv0 = (arg7 * spB4) + arg4;
        } else {
            var_fa0 = (arg5 * spBC) + sp98;
            var_fa1 = (arg6 * spB8) + sp90;
            var_fv0 = (temp_fs4 * spB4) + sp94;
        }
        func_80207410(var_fa0, var_fa1, var_fv0, &spA4, &spA0, &sp9C);
        temp_s0->v.cn[0] = spA4 * 255.0f;
        temp_s0->v.cn[1] = spA0 * 255.0f;
        temp_s0->v.cn[2] = sp9C * 255.0f;
    }
}

void func_8020B894(s32 arg0, s32 arg1, s32 arg2, void* arg3, f32 arg4, f32 arg5, f32 arg6) {
    f32 var_fv1;
    u16* var_a1;
    u8* var_a0;
    s32 i;
    f32 r;
    f32 g;
    f32 b;
    f32 temp_fa0;

    if (arg5 < arg4) {
        if (arg6 < arg4) {
            var_fv1 = arg4;
        } else {
            var_fv1 = arg6;
        }
    } else {
        if (arg6 < arg5) {
            var_fv1 = arg5;
        } else {
            var_fv1 = arg6;
        }
    }
    if (arg0 != 1) {
        if (arg0 != 2) {
            if (arg0 == 4) {
                var_a1 = arg3;
                for (i = 0; i < arg2 / 2; i++) {
                    r = (var_a1[i] & 0xF800) >> 11;
                    g = (var_a1[i] & 0x7C0) >> 6;
                    b = (var_a1[i] & 0x3E) >> 1;
                    var_a1[i] = ((s32) (r * arg4) << 11) | ((s32) (g * arg5) << 6) | ((s32) (b * arg6) << 1) | (var_a1[i] & 1);
                }
            }
        } else {
            switch (arg1) {
                case 4:
                    var_a0 = arg3;
                    for (i = 0; i < arg2; i++) {
                        temp_fa0 = (var_a0[i] & 0xE) >> 1;
                        var_a0[i] = (var_a0[i] & 0xF1) | (((s32) (var_fv1 * temp_fa0)) << 1);
                        temp_fa0 = (var_a0[i] & 0xE0) >> 5;
                        var_a0[i] = (((s32) (var_fv1 * temp_fa0)) << 5) | (var_a0[i] & 0x1F);
                    }
                    break;
                case 8:
                    var_a0 = arg3;
                    for (i = 0; i < arg2; i++) {
                        temp_fa0 = (var_a0[i] & 0xF0) >> 4;
                        var_a0[i] = ((((s32) (var_fv1 * temp_fa0)) & 0xF) << 4) | (var_a0[i] & 0xF);
                    }
                    break;
                case 16:
                    var_a1 = arg3;
                    for (i = 0; i < arg2 / 2; i++) {
                        temp_fa0 = (var_a1[i] & 0xFF00) >> 8;
                        var_a1[i] = ((((s32) (var_fv1 * temp_fa0)) & 0xFF) << 8) | (var_a1[i] & 0xFF);
                    }
                    break;
            }
        }
    } else {
        switch (arg1) {
            case 4:
                var_a0 = arg3;
                for (i = 0; i < arg2; i++) {
                    temp_fa0 = var_a0[i] & 0xF;
                    var_a0[i] = (var_a0[i] & 0xF0) | (((s32) (var_fv1 * temp_fa0)) & 0xF);
                    temp_fa0 = (var_a0[i] & 0xF0) >> 4;
                    var_a0[i] = ((((s32) (var_fv1 * temp_fa0)) & 0xF) << 4) | (var_a0[i] & 0xF);
                }
                break;
            case 8:
                var_a0 = arg3;
                for (i = 0; i < arg2; i++) {
                    temp_fa0 = var_a0[i];
                    var_a0[i] = var_fv1 * temp_fa0;
                }
                break;
            case 16:
                var_a1 = arg3;
                for (i = 0; i < arg2 / 2; i++) {
                    temp_fa0 = var_a1[i];
                    var_a1[i] = var_fv1 * temp_fa0;
                }
                break;
        }
    }
}

void func_8020D0D8(s32 arg0, s32 arg1, s32 arg2, void* arg3, f32 arg4, f32 arg5, f32 arg6) {
    s32 i;
    f32 sp90;
    f32 sp8C;
    f32 sp88;
    u16* var_s0;
    u8* var_v0;
    f32 temp_fv1;
    f32 temp_fa0;
    s32 pad;
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    s32 pad2[2];

    switch (arg0) {
        case 4:
            var_s0 = arg3;
            for (i = 0; i < arg2 / 2; i++) {
                func_80207630(((s32) (var_s0[i] & 0xF800) >> 0xB) / 31.0f, ((s32) (var_s0[i] & 0x7C0) >> 6) / 31.0f, ((s32) (var_s0[i] & 0x3E) >> 1) / 31.0f, &sp90, &sp8C, &sp88);
                func_80207410(arg4 * sp90, arg5 * sp8C, arg6 * sp88, &sp70, &sp6C, &sp68);
                sp70 *= 31.0f;
                sp6C *= 31.0f;
                sp68 *= 31.0f;
                var_s0[i] = ((s32)sp70 << 11) | ((s32)sp6C << 6) | ((s32)sp68 << 1) | (var_s0[i] & 1);
            }
            break;
        case 2:
            switch (arg1) {
                case 4:
                    var_v0 = arg3;
                    for (i = 0; i < arg2; i++) {
                        temp_fa0 = (var_v0[i] & 0xE) >> 1;
                        var_v0[i] = (var_v0[i] & 0xF1) | (((s32) (arg6 * temp_fa0)) << 1);
                        temp_fa0 = (var_v0[i] & 0xE0) >> 5;
                        var_v0[i] = (((s32) (arg6 * temp_fa0)) << 5) | (var_v0[i] & 0x1F);
                    }
                    break;
                case 8:
                    var_v0 = arg3;
                    for (i = 0; i < arg2; i++) {
                        temp_fa0 = (var_v0[i] & 0xF0) >> 4;
                        var_v0[i] = ((((s32) (arg6 * temp_fa0)) & 0xF) << 4) | (var_v0[i] & 0xF);
                    }
                    break;
                case 16:
                    var_s0 = arg3;
                    for (i = 0; i < arg2 / 2; i++) {
                        temp_fa0 = (var_s0[i] & 0xFF00) >> 8;
                        var_s0[i] = ((((s32) (arg6 * temp_fa0)) & 0xFF) << 8) | (var_s0[i] & 0xFF);
                    }
                    break;
            }
            break;
        case 1:
            switch (arg1) {
                case 4:
                    var_v0 = arg3;
                    for (i = 0; i < arg2; i++) {
                        temp_fa0 = var_v0[i] & 0xF;
                        var_v0[i] = (var_v0[i] & 0xF0) | (((s32) (arg6 * temp_fa0)) & 0xF);
                        temp_fa0 = (var_v0[i] & 0xF0) >> 4;
                        var_v0[i] = ((((s32) (arg6 * temp_fa0)) & 0xF) << 4) | (var_v0[i] & 0xF);
                    }
                    break;
                case 8:
                    var_v0 = arg3;
                    for (i = 0; i < arg2; i++) {
                        temp_fa0 = var_v0[i];
                        var_v0[i] = arg6 * temp_fa0;
                    }
                    break;
                case 16:
                    var_s0 = arg3;
                    for (i = 0; i < arg2 / 2; i++) {
                        temp_fa0 = var_s0[i];
                        var_s0[i] = arg6 * temp_fa0;
                    }
                    break;
            }
            break;
    }
}

void func_8020E760(Vtx* arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    s32 i;
    Vtx* temp_a3;
    f32 temp_fa0;
    f32 var_fv0;

    for (i = 0; i < arg1; i++) {
        temp_a3 = &arg0[i];
        temp_fa0 = temp_a3->v.cn[0];
        if (temp_a3->v.flag != 0) {
            var_fv0 = arg2 * temp_fa0;
        } else {
            var_fv0 = arg2 * arg2 * arg2 * temp_fa0;
        }
        temp_a3->v.cn[0] = var_fv0;
        temp_fa0 = temp_a3->v.cn[1];
        if (temp_a3->v.flag != 0) {
            var_fv0 = arg3 * temp_fa0;
        } else {
            var_fv0 = arg3 * arg3 * arg3 * temp_fa0;
        }
        temp_a3->v.cn[1] = var_fv0;
        temp_fa0 = temp_a3->v.cn[2];
        if (temp_a3->v.flag != 0) {
            var_fv0 = arg4 * temp_fa0;
        } else {
            var_fv0 = arg4 * arg4 * arg4 * temp_fa0;
        }
        temp_a3->v.cn[2] = var_fv0;
    }
}

void func_8020EF20(Vtx* arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    s32 i;
    Vtx* temp_s0;
    f32 spBC;
    f32 spB8;
    f32 spB4;
    f32 var_fa0;
    f32 var_fa1;
    f32 var_fv0;
    f32 spA4;
    f32 spA0;
    f32 sp9C;

    for (i = 0; i < arg1; i++) {
        temp_s0 = &arg0[i];

        func_80207630(temp_s0->v.cn[0] / 255.0f, temp_s0->v.cn[1] / 255.0f, temp_s0->v.cn[2] / 255.0f, &spBC, &spB8, &spB4);
        if (temp_s0->v.flag != 0) {
            var_fa0 = arg2 * spBC;
            var_fa1 = arg3 * spB8;
            var_fv0 = arg4 * spB4;
        } else {
            var_fa0 = arg2 * spBC;
            var_fa1 = arg3 * spB8;
            var_fv0 = arg4 * arg4 * arg4 * spB4;
        }
        func_80207410(var_fa0, var_fa1, var_fv0, &spA4, &spA0, &sp9C);
        temp_s0->v.cn[0] = spA4 * 255.0f;
        temp_s0->v.cn[1] = spA0 * 255.0f;
        temp_s0->v.cn[2] = sp9C * 255.0f;
    }
}

void func_8020F298(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv1;
    s32 i;

    D_80263760 = arg1;
    D_80263764 = arg2;
    D_80263768 = arg3;
    D_8026376C = arg4;
    D_80263770 = arg5;
    D_80263774 = arg6;
    D_80248DD4 = 0;
    uvGfxWaitForMesg();

    for (i = 0; i < 128; i++) {
        ParsedUVCT* temp_v0 = gGfxUnkPtrs->contours[i];
        if (temp_v0 == NULL) {
            continue;
        }
        if (temp_v0->unk28 != 0.0f) {
            temp_fv0 = 1.0f - (temp_v0->unk28 * arg4);
            temp_fv1 = 1.0f - (temp_v0->unk28 * arg5);
            temp_fa0 = 1.0f - (temp_v0->unk28 * arg6);
            if (arg0 == 0) {
                func_8020ABAC(temp_v0->vtx, temp_v0->vtxCount, arg1, arg2, arg3, temp_fv0, temp_fv1, temp_fa0);
            } else {
                func_8020B4AC(temp_v0->vtx, temp_v0->vtxCount, arg1, arg2, arg3, temp_fv0, temp_fv1, temp_fa0);
            }
        }
    }

    for (i = 0; i < 400; i++) {
        ParsedUVMD* temp_v0 = gGfxUnkPtrs->models[i];
        if (temp_v0 == NULL) {
            continue;
        }
        if (temp_v0->unk24 != 0.0f) {
            temp_fv0 = 1.0f - (temp_v0->unk24 * arg4);
            temp_fv1 = 1.0f - (temp_v0->unk24 * arg5);
            temp_fa0 = 1.0f - (temp_v0->unk24 * arg6);
            if (arg0 == 0) {
                func_8020ABAC(temp_v0->vtx, temp_v0->vtxCount, arg1, arg2, arg3, temp_fv0, temp_fv1, temp_fa0);
            } else {
                func_8020B4AC(temp_v0->vtx, temp_v0->vtxCount, arg1, arg2, arg3, temp_fv0, temp_fv1, temp_fa0);
            }
        }
    }

    if (D_802B8934 != 0) {
        return;
    }

    for (i = 0; i < 500; i++) {
        ParsedUVTX* temp_v0 = gGfxUnkPtrs->textures[i];
        if (temp_v0 == NULL) {
            continue;
        }
        if (temp_v0->unk28 != 0) {
            temp_fv0 = 1.0f - (temp_v0->unk28 * arg4);
            temp_fv1 = 1.0f - (temp_v0->unk28 * arg5);
            temp_fa0 = 1.0f - (temp_v0->unk28 * arg6);
            if (arg0 == 0) {
                func_802077BC(temp_v0->unk22, temp_v0->unkE, temp_v0->size, temp_v0->unk0, arg1, arg2, arg3, temp_fv0, temp_fv1, temp_fa0);
            } else {
                func_8020921C(temp_v0->unk22, temp_v0->unkE, temp_v0->size, temp_v0->unk0, arg1, arg2, arg3, temp_fv0, temp_fv1, temp_fa0);
            }
        }
    }
}

void func_8020F5A4(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    if (arg0 == 1) {
        func_8020F298(arg0, D_80263754, D_80263758, D_8026375C, arg1, arg2, arg3);
    } else {
        func_8020F298(arg0, D_80263748, D_8026374C, D_80263750, arg1, arg2, arg3);
    }
}

void func_8020F630(s32 arg0) {
    f32 var_fv1;
    f32 var_fa0;
    f32 var_fa1;
    s32 i;

    uvGfxWaitForMesg();

    for (i = 0; i < 128; i++) {
        ParsedUVCT* temp_v0 = gGfxUnkPtrs->contours[i];
        if (temp_v0 == NULL) {
            continue;
        }
        if (temp_v0->unk28 != 0.0f) {
            if (arg0 == 0) {
                var_fv1 = 1.0f - ((1.0f - D_80263748) * temp_v0->unk28);
                var_fa0 = 1.0f - ((1.0f - D_8026374C) * temp_v0->unk28);
                var_fa1 = 1.0f - ((1.0f - D_80263750) * temp_v0->unk28);
                func_8020E760(temp_v0->vtx, temp_v0->vtxCount, var_fv1, var_fa0, var_fa1);
            } else {
                var_fv1 = 1.0f - ((1.0f - D_80263754) * temp_v0->unk28);
                var_fa0 = 1.0f - ((1.0f - D_80263758) * temp_v0->unk28);
                var_fa1 = 1.0f - ((1.0f - D_8026375C) * temp_v0->unk28);
                func_8020EF20(temp_v0->vtx, temp_v0->vtxCount, var_fv1, var_fa0, var_fa1);
            }
        }
    }

    for (i = 0; i < 400; i++) {
        ParsedUVMD* temp_v0 = gGfxUnkPtrs->models[i];
        if (temp_v0 == NULL) {
            continue;
        }
        if (temp_v0->unk24 != 0.0f) {
            if (arg0 == 0) {
                var_fv1 = 1.0f - ((1.0f - D_80263748) * temp_v0->unk24);
                var_fa0 = 1.0f - ((1.0f - D_8026374C) * temp_v0->unk24);
                var_fa1 = 1.0f - ((1.0f - D_80263750) * temp_v0->unk24);
                func_8020E760(temp_v0->vtx, temp_v0->vtxCount, var_fv1, var_fa0, var_fa1);
            } else {
                var_fv1 = 1.0f - ((1.0f - D_80263754) * temp_v0->unk24);
                var_fa0 = 1.0f - ((1.0f - D_80263758) * temp_v0->unk24);
                var_fa1 = 1.0f - ((1.0f - D_8026375C) * temp_v0->unk24);
                func_8020EF20(temp_v0->vtx, temp_v0->vtxCount, var_fv1, var_fa0, var_fa1);
            }
        }
    }

    if (D_802B8934 != 0) {
        return;
    }

    for (i = 0; i < 500; i++) {
        ParsedUVTX* temp_v0 = gGfxUnkPtrs->textures[i];
        if (temp_v0 == NULL) {
            continue;
        }
        if (temp_v0->unk28 != 0.0f) {
            if (arg0 == 0) {
                var_fv1 = 1.0f - ((1.0f - D_80263748) * temp_v0->unk28);
                var_fa0 = 1.0f - ((1.0f - D_8026374C) * temp_v0->unk28);
                var_fa1 = 1.0f - ((1.0f - D_80263750) * temp_v0->unk28);
                func_8020B894(temp_v0->unk22, temp_v0->unkE, temp_v0->size, temp_v0->unk0, var_fv1, var_fa0, var_fa1);
            } else {
                var_fv1 = 1.0f - ((1.0f - D_80263754) * temp_v0->unk28);
                var_fa0 = 1.0f - ((1.0f - D_80263758) * temp_v0->unk28);
                var_fa1 = 1.0f - ((1.0f - D_8026375C) * temp_v0->unk28);
                func_8020D0D8(temp_v0->unk22, temp_v0->unkE, temp_v0->size, temp_v0->unk0, var_fv1, var_fa0, var_fa1);
            }
        }
    }
}

void func_8020F99C(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    if (arg0 == 1) {
        D_80263754 = arg1;
        D_80263758 = arg2;
        D_8026375C = arg3;
    } else {
        D_80263748 = arg1;
        D_8026374C = arg2;
        D_80263750 = arg3;
    }
}

void func_8020F9F4(void) {
    gGfxUnkPtrs = &gLevelData;
}

ParsedUVTR* uvTerraGetBox(s32 arg0) {
    ParsedUVTR* temp_v1;

    temp_v1 = gGfxUnkPtrs->terras[arg0];
    if (temp_v1 == NULL) {
        _uvDebugPrintf("uvTerraGetBox: terra %d not defined for level\n", arg0);
    }
    return temp_v1;
}

void uvModelGetPosm(s32 arg0, s32 arg1, Mtx4F* arg2) {
    ParsedUVMD* temp_v0;

    temp_v0 = gGfxUnkPtrs->models[arg0];
    if (temp_v0 == NULL) {
        _uvDebugPrintf("uvModelGetPosm: model %d not defined for level\n", arg0);
        return;
    }
    if (arg1 >= temp_v0->unk8->unk4) {
        _uvDebugPrintf("uvModelGetPosm: there are not %d parts defined for model %d\n", arg1, arg0);
        return;
    }

    uvMat4Copy(arg2, &temp_v0->unk14[arg1]);
    arg2->m[3][0] /= temp_v0->unk20;
    arg2->m[3][1] /= temp_v0->unk20;
    arg2->m[3][2] /= temp_v0->unk20;
}

void uvModelGetProps(s32 arg0, ...) {
    ParsedUVMD* temp_s2;
    s32 var_a0;
    s32 var_v0;
    s32 property;
    va_list args;
    s32 i;

    if (arg0 == 0xFFFF) {
        return;
    }
    temp_s2 = gGfxUnkPtrs->models[arg0];
    va_start(args, arg0);
    if (temp_s2 == NULL) {
        _uvDebugPrintf("uvModelGetProps: model %d not defined for level\n", arg0);
        return;
    }

    while (TRUE) {
        property = va_arg(args, s32);
        switch (property) {
            case 0:
                return;
            case 2:
                *va_arg(args, s32*) = temp_s2->unk10;
                break;
            case 5:
                if (temp_s2->unk8->unk0->unk0->state & 0x02000000) {
                    var_v0 = 1;
                } else {
                    var_v0 = 0;
                }

                *va_arg(args, u8*) = var_v0;
                break;
            case 4:
                *va_arg(args, s32*) = temp_s2->unk8->unk4;
                break;
            case 3:
                var_a0 = 0;
                for (i = 0; i < temp_s2->unk8->unk4; i++) {
                    var_a0 += temp_s2->unk8->unk0[i].unkC;
                }

                *va_arg(args, s32*) = var_a0;
                break;
            case 1:
                *va_arg(args, f32*) = temp_s2->unk1C;
                break;
            default:
                _uvDebugPrintf("uvModelGetProps: Unknown property type %d\n", property);
                break;
        }
    }
}

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

void uvDbColorModel(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    ParsedUVMD* temp_v0;

    temp_v0 = gGfxUnkPtrs->models[arg0];
    if (temp_v0 == NULL) {
        _uvDebugPrintf("uvDbColorModel: model %d not in level\n", arg0);
        return;
    }

    uvGfxWaitForMesg();
    func_8020ABAC(temp_v0->vtx, temp_v0->vtxCount, arg1, arg2, arg3, arg4, arg4, arg4);
}
