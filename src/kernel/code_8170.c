#include "common.h"
#include <uv_dobj.h>
#include <uv_geometry.h>
#include <uv_graphics.h>
#include <uv_math.h>
#include <uv_memory.h>
#include <uv_sobj.h>
#include <libc/stdarg.h>
#include "kernel/code_8170.h"
#include "kernel/code_2FE40.h"

u32 D_802634C0;
s32 D_802634C4;
s32 D_802634C8[HIT_COUNT];
f32 D_80263548[HIT_COUNT];
Vec3F D_802635C8[HIT_COUNT];
f32 D_80263748;
f32 D_8026374C;
f32 D_80263750;
f32 D_80263754;
f32 D_80263758;
f32 D_8026375C;
f32 D_80263760;
f32 D_80263764;
f32 D_80263768;
f32 D_8026376C;
f32 D_80263770;
f32 D_80263774;

uvLevelData* gGfxUnkPtrs = NULL;
s32 D_80248DD4 = -1;
s32 D_80248DD8 = 0;

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

    if (D_802634C4 >= HIT_COUNT) {
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
    temp_ft3 = (s32)arg0;
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
            var_a1[i] = ((s32)((arg7 * r) + arg4) << 11) | ((s32)((arg8 * g) + arg5) << 6) | ((s32)((arg9 * b) + arg6) << 1) | (var_a1[i] & 1);
        }
        break;
    case 2:
        switch (arg1) {
        case 4:
            var_fv0 *= (1.0f - var_fv1) * 7.0f;
            var_a0 = arg3;
            for (i = 0; i < arg2; i++) {
                temp_fa0 = (var_a0[i] & 0xE) >> 1;
                var_a0[i] = (var_a0[i] & 0xF1) | ((s32)((var_fv1 * temp_fa0) + var_fv0) << 1);
                temp_fa0 = (var_a0[i] & 0xE0) >> 5;
                var_a0[i] = ((s32)((var_fv1 * temp_fa0) + var_fv0) << 5) | (var_a0[i] & 0x1F);
            }
            break;
        case 8:
            var_fv0 *= (1.0f - var_fv1) * 15.0f;
            var_a0 = arg3;
            for (i = 0; i < arg2; i++) {
                temp_fa0 = (var_a0[i] & 0xF0) >> 4;
                var_a0[i] = (((s32)((var_fv1 * temp_fa0) + var_fv0) & 0xF) << 4) | (var_a0[i] & 0xF);
            }
            break;
        case 16:
            var_fv0 *= (1.0f - var_fv1) * 255.0f;
            var_a1 = arg3;
            for (i = 0; i < arg2 / 2; i++) {
                temp_fa0 = (var_a1[i] & 0xFF00) >> 8;
                var_a1[i] = (((s32)((var_fv1 * temp_fa0) + var_fv0) & 0xFF) << 8) | (var_a1[i] & 0xFF);
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
                var_a0[i] = (var_a0[i] & 0xF0) | ((s32)((var_fv1 * temp_fa0) + var_fv0) & 0xF);
                temp_fa0 = (var_a0[i] & 0xF0) >> 4;
                var_a0[i] = (((s32)((var_fv1 * temp_fa0) + var_fv0) & 0xF) << 4) | (var_a0[i] & 0xF);
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
            func_80207630((f32)((s32)(var_s0[i] & 0xF800) >> 0xB) / 31.0f, (f32)((s32)(var_s0[i] & 0x7C0) >> 6) / 31.0f,
                          (f32)((s32)(var_s0[i] & 0x3E) >> 1) / 31.0f, &spB0, &spAC, &spA8);
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
                var_v0[i] = (var_v0[i] & 0xF1) | (((s32)((arg9 * temp_fa0) + temp_fv1)) << 1);
                temp_fa0 = (var_v0[i] & 0xE0) >> 5;
                //! @bug sp84 uninitialised!
                var_v0[i] = (((s32)((arg9 * temp_fa0) + sp84)) << 5) | (var_v0[i] & 0x1F);
            }
            break;
        case 8:
            temp_fv1 = (1.0f - arg9) * arg6 * 15.0f;
            var_v0 = arg3;
            for (i = 0; i < arg2; i++) {
                temp_fa0 = (var_v0[i] & 0xF0) >> 4;
                var_v0[i] = ((((s32)((arg9 * temp_fa0) + temp_fv1)) & 0xF) << 4) | (var_v0[i] & 0xF);
            }
            break;
        case 16:
            temp_fv1 = (1.0f - arg9) * arg6 * 255.0f;
            var_s0 = arg3;
            for (i = 0; i < arg2 / 2; i++) {
                temp_fa0 = (var_s0[i] & 0xFF00) >> 8;
                var_s0[i] = ((((s32)((arg9 * temp_fa0) + temp_fv1)) & 0xFF) << 8) | (var_s0[i] & 0xFF);
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
                var_v0[i] = (var_v0[i] & 0xF0) | (((s32)((arg9 * temp_fa0) + temp_fv1)) & 0xF);
                temp_fa0 = (var_v0[i] & 0xF0) >> 4;
                var_v0[i] = ((((s32)((arg9 * temp_fa0) + temp_fv1)) & 0xF) << 4) | (var_v0[i] & 0xF);
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
    switch (arg0) {
    case 4:
        var_a1 = arg3;
        for (i = 0; i < arg2 / 2; i++) {
            r = (var_a1[i] & 0xF800) >> 11;
            g = (var_a1[i] & 0x7C0) >> 6;
            b = (var_a1[i] & 0x3E) >> 1;
            var_a1[i] = ((s32)(r * arg4) << 11) | ((s32)(g * arg5) << 6) | ((s32)(b * arg6) << 1) | (var_a1[i] & 1);
        }
        break;
    case 2:
        switch (arg1) {
        case 4:
            var_a0 = arg3;
            for (i = 0; i < arg2; i++) {
                temp_fa0 = (var_a0[i] & 0xE) >> 1;
                var_a0[i] = (var_a0[i] & 0xF1) | (((s32)(var_fv1 * temp_fa0)) << 1);
                temp_fa0 = (var_a0[i] & 0xE0) >> 5;
                var_a0[i] = (((s32)(var_fv1 * temp_fa0)) << 5) | (var_a0[i] & 0x1F);
            }
            break;
        case 8:
            var_a0 = arg3;
            for (i = 0; i < arg2; i++) {
                temp_fa0 = (var_a0[i] & 0xF0) >> 4;
                var_a0[i] = ((((s32)(var_fv1 * temp_fa0)) & 0xF) << 4) | (var_a0[i] & 0xF);
            }
            break;
        case 16:
            var_a1 = arg3;
            for (i = 0; i < arg2 / 2; i++) {
                temp_fa0 = (var_a1[i] & 0xFF00) >> 8;
                var_a1[i] = ((((s32)(var_fv1 * temp_fa0)) & 0xFF) << 8) | (var_a1[i] & 0xFF);
            }
            break;
        }
        break;
    case 1:
        switch (arg1) {
        case 4:
            var_a0 = arg3;
            for (i = 0; i < arg2; i++) {
                temp_fa0 = var_a0[i] & 0xF;
                var_a0[i] = (var_a0[i] & 0xF0) | (((s32)(var_fv1 * temp_fa0)) & 0xF);
                temp_fa0 = (var_a0[i] & 0xF0) >> 4;
                var_a0[i] = ((((s32)(var_fv1 * temp_fa0)) & 0xF) << 4) | (var_a0[i] & 0xF);
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
        break;
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
            func_80207630(((s32)(var_s0[i] & 0xF800) >> 0xB) / 31.0f, ((s32)(var_s0[i] & 0x7C0) >> 6) / 31.0f, ((s32)(var_s0[i] & 0x3E) >> 1) / 31.0f, &sp90,
                          &sp8C, &sp88);
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
                var_v0[i] = (var_v0[i] & 0xF1) | (((s32)(arg6 * temp_fa0)) << 1);
                temp_fa0 = (var_v0[i] & 0xE0) >> 5;
                var_v0[i] = (((s32)(arg6 * temp_fa0)) << 5) | (var_v0[i] & 0x1F);
            }
            break;
        case 8:
            var_v0 = arg3;
            for (i = 0; i < arg2; i++) {
                temp_fa0 = (var_v0[i] & 0xF0) >> 4;
                var_v0[i] = ((((s32)(arg6 * temp_fa0)) & 0xF) << 4) | (var_v0[i] & 0xF);
            }
            break;
        case 16:
            var_s0 = arg3;
            for (i = 0; i < arg2 / 2; i++) {
                temp_fa0 = (var_s0[i] & 0xFF00) >> 8;
                var_s0[i] = ((((s32)(arg6 * temp_fa0)) & 0xFF) << 8) | (var_s0[i] & 0xFF);
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
                var_v0[i] = (var_v0[i] & 0xF0) | (((s32)(arg6 * temp_fa0)) & 0xF);
                temp_fa0 = (var_v0[i] & 0xF0) >> 4;
                var_v0[i] = ((((s32)(arg6 * temp_fa0)) & 0xF) << 4) | (var_v0[i] & 0xF);
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

ParsedUVTR* uvTerraGetBox(s32 terraId) {
    ParsedUVTR* temp_v1;

    temp_v1 = gGfxUnkPtrs->terras[terraId];
    if (temp_v1 == NULL) {
        _uvDebugPrintf("uvTerraGetBox: terra %d not defined for level\n", terraId);
    }
    return temp_v1;
}

void uvModelGetPosm(s32 modelId, s32 partIndex, Mtx4F* arg2) {
    ParsedUVMD* temp_v0;

    temp_v0 = gGfxUnkPtrs->models[modelId];
    if (temp_v0 == NULL) {
        _uvDebugPrintf("uvModelGetPosm: model %d not defined for level\n", modelId);
        return;
    }
    if (partIndex >= temp_v0->unk8->unk4) {
        _uvDebugPrintf("uvModelGetPosm: there are not %d parts defined for model %d\n", partIndex, modelId);
        return;
    }

    uvMat4Copy(arg2, &temp_v0->unk14[partIndex]);
    arg2->m[3][0] /= temp_v0->unk20;
    arg2->m[3][1] /= temp_v0->unk20;
    arg2->m[3][2] /= temp_v0->unk20;
}

void uvModelGetProps(s32 modelId, ...) {
    ParsedUVMD* temp_s2;
    s32 var_a0;
    s32 var_v0;
    s32 property;
    va_list args;
    s32 i;

    if (modelId == 0xFFFF) {
        return;
    }
    temp_s2 = gGfxUnkPtrs->models[modelId];
    va_start(args, modelId);
    if (temp_s2 == NULL) {
        _uvDebugPrintf("uvModelGetProps: model %d not defined for level\n", modelId);
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
            if (temp_s2->unk8->unk0->unk0->state & GFX_STATE_2000000) {
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

u32 uvTerraGetPt(s32 terraId, f32 arg1, f32 arg2, s32** arg3) {
    f32 sp94;
    f32 sp90;
    f32 sp8C;
    ParsedUVTR* temp_s0;
    u16 i;
    uvUnkTileStruct* var_v0;
    u16 j;
    ParsedUVCT* temp_s4;
    u16 sp76;
    u32 var_s2;
    u16 sp6E;
    Unk80225FBC_0x28* temp_s1;
    Unk80225FBC_0x28_UnkC* temp_v0;

    temp_s0 = gGfxUnkPtrs->terras[terraId];
    var_s2 = 0;
    if (temp_s0 == NULL) {
        _uvDebugPrintf("uvTerraGetPt: terra %d not defined for level\n", terraId);
    }
    if (func_80212FF4(temp_s0, arg1, arg2, 0.0f, &sp94, &sp90, &sp8C, &sp6E, &sp76, 0) == 0) {
        return *arg3 = NULL;
    }
    var_v0 = &temp_s0->unk28[sp6E];
    temp_s4 = var_v0->unk40;
    if (temp_s4 == NULL) {
        return *arg3 = NULL;
    }

    sp94 *= gGfxUnkPtrs->unk1608;
    sp90 *= gGfxUnkPtrs->unk1608;
    sp8C *= gGfxUnkPtrs->unk1608;
    for (i = 0; i < temp_s4->unkC; i++) {
        temp_s1 = &temp_s4->unk8[i];
        if (!(temp_s1->unk12 & sp76)) {
            continue;
        }

        for (j = 0; j < temp_s1->unk10; j++) {
            temp_v0 = &temp_s1->unkC[j];
            if (!(temp_v0->unk6 & sp76)) {
                continue;
            }
            if (func_80212480(sp94, sp90, temp_s4->vtx, temp_v0->unk0, temp_v0->unk2, temp_v0->unk4, 1.0f) == 0) {
                continue;
            }
            D_802634C8[var_s2] = ((sp6E & 0x3FF) << 22) + ((i & 0x3FF) << 12) + (j & 0xFFF);
            var_s2++;
            if (var_s2 >= HIT_COUNT) {
                break;
            }
        }
    }
    *arg3 = D_802634C8;
    return var_s2;
}

s32 uvTerraGetSeg(s32 terraId, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, s32** arg7, f32** arg8) {
    ParsedUVTR* sp184;
    ParsedUVCT* temp_s4;
    uvUnkTileStruct* temp_s1;
    Unk80225FBC_0x28* temp_s1_2;
    Unk80225FBC_0x28_UnkC* temp_v0_2;
    f32 sp170;
    f32 sp16C;
    f32 sp168;
    f32 sp164;
    f32 sp160;
    f32 sp15C;
    u16 sp15A;
    u16 sp158;
    u16 sp156;
    u16 sp154;
    f32 var_fa0;
    f32 var_fa1;
    f32 var_ft4;
    f32 var_ft5;
    s32 sp140;
    s32 sp13C;
    s32 temp_s5;
    u8 var_s3;
    u16 var_s0;
    s32 var_v0;
    s32 var_v1;
    f32 sp128;
    f32 sp124;
    f32 sp120;
    f32 sp11C;
    f32 sp118;
    f32 sp114;
    f32 sp110;
    f32 sp10C;
    f32 sp108;
    f32 sp104;
    f32 sp100;
    f32 spFC;
    f32 spF8;
    f32 spF4;
    f32 spF0;
    f32 spEC;
    f32 spE8;
    f32 temp1;
    f32 temp2;
    f32 temp3;
    f32 temp_fs0;
    f32 temp_fs2;
    f32 temp_fs3;
    s32 i;
    s32 j;
    s32 k;
    s32 l;
    f32 temp_fv0;
    f32 temp_fv1;
    u8 spB7;
    u8 spB6;
    u8 temp_s0;
    u8 temp_t3;

    var_s3 = 0;
    if ((arg1 == arg4) && (arg2 == arg5) && (arg3 == arg6)) {
        *arg7 = NULL;
        *arg8 = NULL;
        return 0;
    }
    sp184 = gGfxUnkPtrs->terras[terraId];
    if (sp184 == NULL) {
        _uvDebugPrintf("uvTerraGetSeg: terra %d not defined for level\n", terraId);
    }

    sp128 = sp184->unk1C;
    sp124 = sp184->unk20;
    spFC = arg1;
    spF8 = arg2;
    spF4 = arg4;
    spF0 = arg5;
    temp_fs2 = arg4 - arg1;
    temp_fs3 = arg5 - arg2;
    temp_fs0 = arg6 - arg3;
    func_802141CC(&arg1, &arg2, &arg4, &arg5, sp184->unk0.unk0, sp184->unk0.unkC, sp184->unk0.unk4, sp184->unk0.unk10);
    if (arg1 == sp184->unk0.unkC) {
        arg1 -= 0.0001f * sp128;
    }
    if (arg4 == sp184->unk0.unkC) {
        arg4 -= 0.0001f * sp128;
    }
    if (arg2 == sp184->unk0.unk10) {
        arg2 -= 0.0001f * sp124;
    }
    if (arg5 == sp184->unk0.unk10) {
        arg5 -= 0.0001f * sp124;
    }

    if ((spFC != arg1) && (temp_fs2 != 0.0f)) {
        arg3 += temp_fs0 * ((arg1 - spFC) / temp_fs2);
    } else if ((spF8 != arg2) && (temp_fs3 != 0.0f)) {
        arg3 += temp_fs0 * ((arg2 - spF8) / temp_fs3);
    }
    if ((spF4 != arg4) && (temp_fs2 != 0.0f)) {
        arg6 += temp_fs0 * ((arg4 - spF4) / temp_fs2);
    } else if ((spF0 != arg5) && (temp_fs3 != 0.0f)) {
        arg6 += temp_fs0 * ((arg5 - spF0) / temp_fs3);
    }
    temp1 = arg4 - arg1;
    temp2 = arg5 - arg2;
    temp3 = arg6 - arg3;
    if ((temp1 == 0.0f) && (temp2 == 0.0f) && (temp3 == 0.0f)) {
        *arg7 = NULL;
        *arg8 = NULL;
        return 0;
    }
    temp_s0 = func_80212FF4(sp184, arg1, arg2, arg3, &sp170, &sp16C, &sp168, &sp15A, &sp156, 0);
    temp_t3 = func_80212FF4(sp184, arg4, arg5, arg6, &sp164, &sp160, &sp15C, &sp158, &sp154, 0);
    if ((temp_s0 == 0) && (temp_t3 == 0)) {
        *arg7 = NULL;
        *arg8 = NULL;
        return 0;
    }
    if (sp15A == sp158) {
        spB7 = TRUE;
        if (sp156 == sp154) {
            spB6 = TRUE;
        } else {
            spB6 = FALSE;
        }
    } else {
        spB7 = FALSE;
        spB6 = FALSE;
    }
    if (spB7) {
        var_v1 = var_v0 = (s32)((arg1 - sp184->unk0.unk0) / sp128);
        sp140 = sp13C = (s32)((arg2 - sp184->unk0.unk4) / sp124);
    } else {
        if (arg4 < arg1) {
            var_ft4 = arg4;
            var_ft5 = arg1;
        } else {
            var_ft4 = arg1;
            var_ft5 = arg4;
        }
        if (arg5 < arg2) {
            var_fa0 = arg5;
            var_fa1 = arg2;
        } else {
            var_fa1 = arg5;
            var_fa0 = arg2;
        }

        var_v1 = (s32)((var_ft4 - sp184->unk0.unk0) / sp128);
        var_v0 = (s32)((var_ft5 - sp184->unk0.unk0) / sp128);
        sp140 = (s32)((var_fa0 - sp184->unk0.unk4) / sp124);
        sp13C = (s32)((var_fa1 - sp184->unk0.unk4) / sp124);
        if (var_v1 < 0) {
            var_v1 = 0;
        }

        if (var_v0 >= sp184->unk18) {
            var_v0 = sp184->unk18 - 1;
        }
        if (sp140 < 0) {
            sp140 = 0;
        }

        if (sp13C >= sp184->unk19) {
            sp13C = sp184->unk19 - 1;
        }
    }

    for (i = var_v1; i <= var_v0; i++) {
        for (j = sp140; j <= sp13C; j++) {
            temp_s5 = (sp184->unk18 * j) + i;
            temp_s1 = &sp184->unk28[temp_s5];
            if (temp_s1 == NULL) {
                continue;
            }
            temp_s4 = temp_s1->unk40;
            if (temp_s4 == NULL) {
                continue;
            }

            sp10C = arg1;
            sp104 = arg2;
            sp108 = arg4;
            sp100 = arg5;
            spEC = arg3 - temp_s1->unk0.unk38;
            spE8 = arg6 - temp_s1->unk0.unk38;

            sp11C = temp_s1->unk0.unk30 - (0.5f * sp128);
            sp118 = temp_s1->unk0.unk30 + (0.5f * sp128);
            sp110 = temp_s1->unk0.unk34 + (0.5f * sp124);
            sp114 = temp_s1->unk0.unk34 - (0.5f * sp124);
            if (func_802140BC(arg1, arg2, arg4, arg5, sp11C, sp118, sp114, sp110) == 0) {
                continue;
            }
            if (!spB7) {
                func_80214450(&sp10C, &sp104, &spEC, &sp108, &sp100, &spE8, sp11C, sp118, sp114, sp110);
                if ((sp10C == sp108) && (sp104 == sp100) && (spEC == spE8)) {
                    continue;
                }
                var_s0 = 0;
                if (sp10C == sp118) {
                    var_s0 |= 1;
                }
                if (sp104 == sp110) {
                    var_s0 |= 2;
                }
                func_80212FF4(sp184, sp10C, sp104, spEC, &sp170, &sp16C, &sp168, &sp15A, &sp156, var_s0);
                var_s0 = 0;
                if (sp108 == sp118) {
                    var_s0 |= 1;
                }
                if (sp100 == sp110) {
                    var_s0 |= 2;
                }
                func_80212FF4(sp184, sp108, sp100, spE8, &sp164, &sp160, &sp15C, &sp158, &sp154, var_s0);
                if (sp156 != sp154) {
                    sp154 = func_80214900(sp10C, sp104, sp108, sp100, sp170, sp16C, sp164, sp160, sp11C, sp118, sp110, sp114, temp_s1);
                }
            }

            if (!spB6) {
                sp154 = func_80214900(sp10C, sp104, sp108, sp100, sp170, sp16C, sp164, sp160, sp11C, sp118, sp110, sp114, temp_s1);
            }
            if (sp154 == 0) {
                continue;
            }

            sp170 *= gGfxUnkPtrs->unk1608;
            sp164 *= gGfxUnkPtrs->unk1608;
            sp16C *= gGfxUnkPtrs->unk1608;
            sp160 *= gGfxUnkPtrs->unk1608;
            sp168 *= gGfxUnkPtrs->unk1608;
            sp15C *= gGfxUnkPtrs->unk1608;
            for (k = 0; k < temp_s4->unkC; k++) {
                temp_s1_2 = &temp_s4->unk8[k];
                if (!(temp_s1_2->unk12 & sp154)) {
                    continue;
                }

                for (l = 0; l < temp_s1_2->unk10; l++) {
                    temp_v0_2 = &temp_s1_2->unkC[l];
                    if (!(temp_v0_2->unk6 & sp154)) {
                        continue;
                    }
                    if (func_802129B0(sp170, sp16C, sp168, sp164, sp160, sp15C, temp_s4->vtx, temp_v0_2->unk0, temp_v0_2->unk2, temp_v0_2->unk4, 1.0f,
                                      &sp120) == 0) {
                        continue;
                    }
                    if (temp_fs2 != 0.0f) {
                        sp120 = ((((sp108 - sp10C) * sp120) + sp10C) - spFC) / temp_fs2;
                    } else if (temp_fs3 != 0.0f) {
                        sp120 = ((((sp100 - sp104) * sp120) + sp104) - spF8) / temp_fs3;
                    }

                    if (sp120 < 0.0f) {
                        sp120 = 0.0f;
                    } else if (sp120 > 1.0f) {
                        sp120 = 1.0f;
                    }
                    D_802634C8[var_s3] = ((temp_s5 & 0x3FF) << 22) + ((k & 0x3FF) << 12) + (l & 0xFFF);
                    D_80263548[var_s3] = sp120;
                    var_s3++;
                    if (var_s3 >= HIT_COUNT) {
                        break;
                    }
                }
            }
        }
    }
    *arg7 = D_802634C8;
    *arg8 = D_80263548;
    return var_s3;
}

void uvTerraGetColor(s32 terraId, u32 surfaceId, u8* arg2, u8* arg3, u8* arg4) {
    ParsedUVCT* temp_a0;
    ParsedUVTR* temp_v0;
    ParsedUVTX* temp_v0_3;
    Unk80225FBC_0x28* temp_v0_2;
    Unk80225FBC_0x28_UnkC* temp_v1_2;
    Vtx* vtx;
    s32 temp_t1;
    uvUnkTileStruct* temp_v1;

    if (surfaceId == -1) {
        _uvDebugPrintf("uvTerraGetColor: null surface id\n");
        return;
    }
    temp_v0 = gGfxUnkPtrs->terras[terraId];
    if (temp_v0 == NULL) {
        _uvDebugPrintf("uvTerraGetColor: terra %d not defined for level\n", terraId);
        return;
    }
    temp_v1 = &temp_v0->unk28[(surfaceId >> 22) & 0x3FF];
    if (temp_v1 == NULL) {
        _uvDebugPrintf("uvTerraGetColor: bad surfce id [0x%x]\n", surfaceId);
        return;
    }
    temp_a0 = temp_v1->unk40;
    if (temp_a0 == NULL) {
        _uvDebugPrintf("uvTerraGetColor: bad surfce id [0x%x]\n", surfaceId);
        return;
    }
    temp_v0_2 = &temp_a0->unk8[(surfaceId >> 12) & 0x3FF];
    temp_v1_2 = &temp_v0_2->unkC[surfaceId & 0xFFF];
    if ((temp_v0_2->unk0 & 0xFFF) != 0xFFF) {
        temp_v0_3 = gGfxUnkPtrs->textures[temp_v0_2->unk0 & 0xFFF];
        if (temp_v0_3->unk22 == 4) {
            *arg2 = temp_v0_3->unk23;
            *arg3 = temp_v0_3->unk24;
            *arg4 = temp_v0_3->unk25;
            return;
        }
    }
    vtx = temp_a0->vtx;
    *arg2 = (vtx[temp_v1_2->unk0].v.cn[0] + vtx[temp_v1_2->unk2].v.cn[0] + vtx[temp_v1_2->unk4].v.cn[0]) / 3;
    *arg3 = (vtx[temp_v1_2->unk0].v.cn[1] + vtx[temp_v1_2->unk2].v.cn[1] + vtx[temp_v1_2->unk4].v.cn[1]) / 3;
    *arg4 = (vtx[temp_v1_2->unk0].v.cn[2] + vtx[temp_v1_2->unk2].v.cn[2] + vtx[temp_v1_2->unk4].v.cn[2]) / 3;
}

s32 uvTerraGetState(s32 terraId, u32 surfaceId) {
    ParsedUVCT* temp_a2;
    ParsedUVTR* temp_v0;
    s32 temp_t9;
    uvUnkTileStruct* temp_a0;
    Unk80225FBC_0x28* temp_v1;

    if (surfaceId == -1) {
        _uvDebugPrintf("uvTerraGetState: null surface id\n", surfaceId);
        return 0xFFF;
    }
    temp_v0 = gGfxUnkPtrs->terras[terraId];
    if (temp_v0 == NULL) {
        _uvDebugPrintf("uvTerraGetState: terra %d not defined for level\n", terraId);
        return 0xFFF;
    }
    temp_t9 = (surfaceId >> 22) & 0x3FF;
    if ((temp_t9) >= (temp_v0->unk18 * temp_v0->unk19)) {
        _uvDebugPrintf("uvTerraGetState: bad surface id [0x%x]\n", surfaceId);
        return 0xFFF;
    }
    temp_a0 = &temp_v0->unk28[(temp_t9)];
    if (temp_a0 == NULL) {
        _uvDebugPrintf("uvTerraGetState: bad surface id [0x%x]\n", surfaceId);
        return 0xFFF;
    }
    temp_a2 = temp_a0->unk40;
    if (temp_a2 == NULL) {
        _uvDebugPrintf("uvTerraGetState: bad surface id [0x%x]\n", surfaceId);
        return 0xFFF;
    }
    temp_v1 = &temp_a2->unk8[(surfaceId >> 12) & 0x3FF];
    return temp_v1->unk0;
}

void uvTerraGetPlane(s32 terraId, u32 surfaceId, f32 px, f32 py, f32* arg4, Vec3F* arg5) {
    ParsedUVCT* temp_v0;
    uvUnkTileStruct* sp70;
    ParsedUVTR* temp_a0;
    Unk80225FBC_0x28_UnkC* temp_s2;
    Vtx* sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    u16 sp56;
    u16 sp54;
    Unk80225FBC_0x28* temp_v1;
    f32 temp_ft5;
    f32 temp_fa0;
    f32 temp_fa1;

    if (surfaceId == -1) {
        _uvDebugPrintf("uvTerraGetPlane : null surface id\n");
        return;
    }
    temp_a0 = gGfxUnkPtrs->terras[terraId];
    if (temp_a0 == NULL) {
        _uvDebugPrintf("uvTerraGetPlane : terra [%d] not in level\n", terraId);
        return;
    }
    sp70 = &temp_a0->unk28[(surfaceId >> 22) & 0x3FF];
    temp_v0 = sp70->unk40;
    temp_v1 = &temp_v0->unk8[(surfaceId >> 12) & 0x3FF];

    temp_s2 = &temp_v1->unkC[surfaceId & 0xFFF];
    sp64 = temp_v0->vtx;
    func_80212FF4(temp_a0, px, py, 0.0f, &sp60, &sp5C, &sp58, &sp56, &sp54, 0);
    sp60 *= gGfxUnkPtrs->unk1608;
    sp5C *= gGfxUnkPtrs->unk1608;
    sp58 *= gGfxUnkPtrs->unk1608;
    if (_uvSurfGetNorm(sp64, temp_s2->unk0, temp_s2->unk2, temp_s2->unk4, arg5) == 0) {
        _uvDebugPrintf("uvTerraGetPlane:  terra[%d]  sid[0x%x] is bad - px:%.2f , py:%.2f\n", terraId, surfaceId, px, py);
        arg5->x = 0.0f;
        arg5->y = 0.0f;
        arg5->z = 1.0f;
    }

    temp_ft5 = sp64[temp_s2->unk0].v.ob[0];
    temp_fa0 = sp64[temp_s2->unk0].v.ob[1];
    temp_fa1 = sp64[temp_s2->unk0].v.ob[2];
    if (arg5->z != 0.0f) {
        *arg4 = (((arg5->x * (temp_ft5 - sp60)) + (arg5->y * (temp_fa0 - sp5C))) / arg5->z) + temp_fa1;
        *arg4 /= gGfxUnkPtrs->unk1608;
        *arg4 += sp70->unk0.unk38;
    }

    if (sp70->unk44 != 0) {
        func_80214840(-sp70->unk44, &arg5->x, &arg5->y);
    }
}

s32 _uvSurfGetNorm(Vtx* arg0, s32 vtxId0, s32 vtxId1, s32 vtxId3, Vec3F* arg4) {
    Vec3F sp44;
    Vec3F sp38;
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;

    temp_fv0 = arg0[vtxId0].v.ob[0];
    temp_fv1 = arg0[vtxId0].v.ob[1];
    temp_fa0 = arg0[vtxId0].v.ob[2];
    sp44.x = arg0[vtxId1].v.ob[0] - temp_fv0;
    sp44.y = arg0[vtxId1].v.ob[1] - temp_fv1;
    sp44.z = arg0[vtxId1].v.ob[2] - temp_fa0;
    sp38.x = arg0[vtxId3].v.ob[0] - temp_fv0;
    sp38.y = arg0[vtxId3].v.ob[1] - temp_fv1;
    sp38.z = arg0[vtxId3].v.ob[2] - temp_fa0;
    uvVec3Cross(arg4, &sp44, &sp38);
    if (uvVec3Normal(arg4, arg4) == 0) {
        _uvDebugPrintf("_uvSurfGetNorm : bad surface normal\n");
        _uvDebugPrintf("vtx ids %d %d %d\n", vtxId0, vtxId1, vtxId3);
        _uvDebugPrintf(" VTX 0 : %d %d %d\n", arg0[vtxId0].v.ob[0], arg0[vtxId0].v.ob[1], arg0[vtxId0].v.ob[2]);
        _uvDebugPrintf(" VTX 1 : %d %d %d\n", arg0[vtxId1].v.ob[0], arg0[vtxId1].v.ob[1], arg0[vtxId1].v.ob[2]);
        _uvDebugPrintf(" VTX 2 : %d %d %d\n", arg0[vtxId3].v.ob[0], arg0[vtxId3].v.ob[1], arg0[vtxId3].v.ob[2]);
        return 0;
    }
    return 1;
}

s32 uvSobjGetPt(s32 terraId, f32 arg1, f32 arg2, f32 arg3) {
    u16 sp7E;
    u16 sp7C;
    f32 sp78;
    f32 sp74;
    f32 sp70;
    ParsedUVCT* temp_v0;
    ParsedUVMD* temp_s1;
    ParsedUVTR* temp_s0;
    u32 i;
    uvUnkTileStruct* temp_s4;
    UnkSobjDraw* temp_s0_2;

    temp_s0 = gGfxUnkPtrs->terras[terraId];
    if (temp_s0 == NULL) {
        _uvDebugPrintf("uvSobjGetPt: terra %d not defined for level\n", terraId);
        return -1;
    }
    if (func_80212FF4(temp_s0, arg1, arg2, arg3, &sp78, &sp74, &sp70, &sp7C, &sp7E, 0) == 0) {
        return -1;
    }
    temp_s4 = &temp_s0->unk28[sp7C];
    temp_v0 = temp_s4->unk40;
    if (temp_v0 == NULL) {
        return -1;
    }

    for (i = 0; i < temp_s4->unk40->unk14; i++) {
        temp_s0_2 = &temp_s4->unk40->unk10[i];
        if (!(sp7E & temp_s0_2->unk14)) {
            continue;
        }
        temp_s1 = gGfxUnkPtrs->models[temp_s0_2->unk0];
        if (func_80213364(sp78, sp74, sp70, temp_s0_2->unk8, temp_s0_2->unkC, temp_s0_2->unk10, temp_s1->unk1C) != 0) {
            if (temp_s1->unk11 & 2) {
                if (func_802134F8(sp78, sp74, sp70, temp_s0_2) >= 0) {
                    return ((terraId & 0xFF) << 24) | ((sp7C & 0xFFF) << 12) | (i & 0xFFF);
                }
            } else {
                return ((terraId & 0xFF) << 24) | ((sp7C & 0xFFF) << 12) | (i & 0xFFF);
            }
        }
    }

    return -1;
}

s32 uvSobjGetSeg(s32 terraId, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, s32** arg7, f32** arg8, Vec3F** arg9) {
    u16 sp16E;
    u16 sp16C;
    u16 k;
    ParsedUVTR* sp164;
    ParsedUVMD* temp_s1;
    UnkSobjDraw* temp_s0_2;
    uvUnkTileStruct* temp_s3;
    f32 sp154;
    f32 sp150;
    f32 sp14C;
    f32 sp148;
    f32 sp144;
    f32 sp140;
    u16 sp13E;
    u16 sp13C;
    u16 sp13A;
    u16 sp138;
    s32 temp_v0_2;
    s32 sp130;
    s32 sp12C;
    s32 sp128;
    s32 sp124;
    f32 var_fa0;
    f32 var_fa1;
    f32 var_ft4;
    f32 var_ft5;
    f32 sp110;
    f32 sp10C;
    f32 sp108;
    f32 temp_fs4;
    f32 temp_fs5;
    f32 spFC;
    f32 spF8;
    f32 spF4;
    f32 spF0;
    f32 spEC;
    f32 spE8;
    f32 spE4;
    f32 spE0;
    f32 temp_fs0_2;
    f32 temp_fs1_2;
    f32 temp_fs2_2;
    f32 temp_fs3;
    f32 spCC;
    f32 spC8;
    f32 spC4;
    f32 spC0;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fs2;
    u8 spB3;
    u8 spB2;
    u8 temp_s0;
    u8 temp_t7;
    u16 temp_t6;

    D_802634C4 = 0;
    sp164 = gGfxUnkPtrs->terras[terraId];
    if (sp164 == NULL) {
        _uvDebugPrintf("uvSobjGetSeg: terra %d not defined for level\n", terraId);
        return 0;
    }
    if ((arg1 == arg4) && (arg2 == arg5) && (arg3 == arg6)) {
        if (arg6 != 0.0f) {
            arg6 *= 1.0001f;
        } else {
            arg6 += 0.0001f;
        }
    }
    sp110 = sp164->unk1C;
    sp10C = sp164->unk20;
    spCC = arg1;
    spC8 = arg2;
    spC4 = arg4;
    spC0 = arg5;
    temp_fs0 = arg4 - arg1;
    temp_fs1 = arg5 - arg2;
    temp_fs2 = arg6 - arg3;
    func_802141CC(&arg1, &arg2, &arg4, &arg5, sp164->unk0.unk0, sp164->unk0.unkC, sp164->unk0.unk4, sp164->unk0.unk10);
    if (arg1 == sp164->unk0.unkC) {
        arg1 -= 0.0001f * sp110;
    }
    if (arg4 == sp164->unk0.unkC) {
        arg4 -= 0.0001f * sp110;
    }
    if (arg2 == sp164->unk0.unk10) {
        arg2 -= 0.0001f * sp10C;
    }
    if (arg5 == sp164->unk0.unk10) {
        arg5 -= 0.0001f * sp10C;
    }
    if ((spCC != arg1) && (temp_fs0 != 0.0f)) {
        arg3 += temp_fs2 * ((arg1 - spCC) / temp_fs0);
    } else if ((spC8 != arg2) && (temp_fs1 != 0.0f)) {
        arg3 += temp_fs2 * ((arg2 - spC8) / temp_fs1);
    }
    if ((spC4 != arg4) && (temp_fs0 != 0.0f)) {
        arg6 += temp_fs2 * ((arg4 - spC4) / temp_fs0);
    } else if ((spC0 != arg5) && (temp_fs1 != 0.0f)) {
        arg6 += temp_fs2 * ((arg5 - spC0) / temp_fs1);
    }
    if ((arg1 == arg4) && (arg2 == arg5) && (arg3 == arg6)) {
        temp_v0_2 = uvSobjGetPt(terraId, arg1, arg2, arg3);
        if (temp_v0_2 == -1) {
            *arg7 = NULL;
            *arg8 = NULL;
            *arg9 = NULL;
            return 0;
        }
        D_802634C8[0] = temp_v0_2;
        D_80263548[0] = 0.0f;
        D_802635C8[0].x = 0.0f;
        D_802635C8[0].y = 0.0f;
        D_802635C8[0].z = 1.0f;
        *arg7 = D_802634C8;
        *arg8 = D_80263548;
        *arg9 = D_802635C8;
    }

    temp_s0 = func_80212FF4(sp164, arg1, arg2, arg3, &sp154, &sp150, &sp14C, &sp13E, &sp13A, 0);
    temp_t7 = func_80212FF4(sp164, arg4, arg5, arg6, &sp148, &sp144, &sp140, &sp13C, &sp138, 0);
    if ((temp_s0 == 0) && (temp_t7 == 0)) {
        *arg7 = NULL;
        *arg8 = NULL;
        return 0;
    }
    if (sp13E == sp13C) {
        spB3 = TRUE;
        if (sp13A == sp138) {
            spB2 = TRUE;
        } else {
            spB2 = FALSE;
        }
    } else {
        spB3 = FALSE;
        spB2 = FALSE;
    }
    if (spB3) {
        sp130 = sp12C = (s32)((arg1 - sp164->unk0.unk0) / sp110);
        sp128 = sp124 = (s32)((arg2 - sp164->unk0.unk4) / sp10C);
    } else {
        var_fa0 = arg1;
        var_fa1 = arg1;
        var_ft4 = arg2;
        var_ft5 = arg2;
        if (arg4 < arg1) {
            var_fa1 = arg4;
        } else {
            var_fa0 = arg4;
        }
        if (arg5 < arg2) {
            var_ft5 = arg5;
        } else {
            var_ft4 = arg5;
        }

        sp130 = (s32)((var_fa1 - sp164->unk0.unk0) / sp110);
        sp12C = (s32)((var_fa0 - sp164->unk0.unk0) / sp110);
        sp128 = (s32)((var_ft5 - sp164->unk0.unk4) / sp10C);
        sp124 = (s32)((var_ft4 - sp164->unk0.unk4) / sp10C);
        if (sp130 < 0) {
            sp130 = 0;
        }

        if (sp12C > sp164->unk18 - 1) {
            sp12C = sp164->unk18 - 1;
        }
        if (sp128 < 0) {
            sp128 = 0;
        }

        if (sp124 > sp164->unk19 - 1) {
            sp124 = sp164->unk19 - 1;
        }
    }

    for (sp16E = sp130; sp16E <= sp12C; sp16E++) {
        for (sp16C = sp128; sp16C <= sp124; sp16C++) {
            temp_t6 = ((sp16C * sp164->unk18) + sp16E);
            temp_s3 = &sp164->unk28[temp_t6];
            if (temp_s3 == NULL) {
                continue;
            }
            if (temp_s3->unk40 == NULL) {
                continue;
            }

            // clang-format off
            spF4 = arg1; \
            spEC = arg2; \
            spE4 = arg3; \
            spF0 = arg4; \
            spE8 = arg5; \
            spE0 = arg6;
            // clang-format on
            temp_fs4 = temp_s3->unk0.unk30 - (0.5f * sp110);
            temp_fs5 = temp_s3->unk0.unk30 + (0.5f * sp110);
            spF8 = temp_s3->unk0.unk34 + (0.5f * sp10C);
            spFC = temp_s3->unk0.unk34 - (0.5f * sp10C);
            if (!spB3) {
                func_80214450(&spF4, &spEC, &spE4, &spF0, &spE8, &spE0, temp_fs4, temp_fs5, spFC, spF8);
            }
            temp_fs0_2 = spF4 - temp_s3->unk0.unk30;
            temp_fs1_2 = spF0 - temp_s3->unk0.unk30;
            temp_fs2_2 = spEC - temp_s3->unk0.unk34;
            temp_fs3 = spE8 - temp_s3->unk0.unk34;
            if ((spF4 == spF0) && (spEC == spE8) && (spE4 == spE0)) {
                continue;
            }

            if (!spB2) {
                sp138 = func_80214900(spF4, spEC, spF0, spE8, sp154, sp150, sp148, sp144, temp_fs4, temp_fs5, spF8, spFC, temp_s3);
            }

            for (k = 0; k < temp_s3->unk40->unk14; k++) {
                temp_s0_2 = &temp_s3->unk40->unk10[k];
                if (!(sp138 & temp_s0_2->unk14)) {
                    continue;
                }
                temp_s1 = gGfxUnkPtrs->models[temp_s0_2->unk0];
                if (func_80214C64(temp_fs0_2, temp_fs2_2, spE4, temp_fs1_2, temp_fs3, spE0, temp_s0_2->unk8, temp_s0_2->unkC, temp_s0_2->unk10, temp_s1->unk1C,
                                  &sp108) != 0) {
                    if (!(temp_s1->unk11 & 2)) {
                        D_802634C8[D_802634C4] = ((terraId & 0xFF) << 24) | ((temp_t6 & 0xFFF) << 12) | (k & 0xFFF);
                        D_80263548[D_802634C4] = sp108;
                        func_80215BC4(arg1, arg2, arg3, arg4, arg5, arg6, sp108, temp_s3->unk0.unk30 + temp_s0_2->unk8, temp_s3->unk0.unk34 + temp_s0_2->unkC,
                                      temp_s3->unk0.unk38 + temp_s0_2->unk10, &D_802635C8[D_802634C4]);
                        D_802634C4++;
                        if (D_802634C4 >= HIT_COUNT) {
                            break;
                        }
                    } else {
                        D_802634C0 = ((terraId & 0xFF) << 24) | ((temp_t6 & 0xFFF) << 12) | (k & 0xFFF);
                        func_80213C24(temp_fs0_2, temp_fs2_2, spE4, temp_fs1_2, temp_fs3, spE0, temp_s0_2);
                    }
                }
            }
        }
    }
    *arg7 = D_802634C8;
    *arg8 = D_80263548;
    *arg9 = D_802635C8;
    _uvDbSortHits();
    return D_802634C4;
}

s32 func_80212008(f32 arg0, f32 arg1, f32 arg2) {
    Mtx4F* temp_v0;
    ParsedUVMD* temp_s1;
    Unk80263780* temp_s0;
    u16 i;

    for (i = 0; i < 100; i++) {
        temp_s0 = &D_80263780[i];
        if ((temp_s0->unk0 == 0xFFFF) || !(temp_s0->unk34 & 1)) {
            continue;
        }
        temp_v0 = &D_80265080[temp_s0->unk2[0]];
        temp_s1 = gGfxUnkPtrs->models[temp_s0->unk0];
        if (func_80213364(arg0, arg1, arg2, temp_v0->m[3][0], temp_v0->m[3][1], temp_v0->m[3][2], temp_s0->unk38) != 0) {
            if (!(temp_s1->unk11 & 2)) {
                return i;
            }
            if (func_80213790(arg0, arg1, arg2, temp_s0) >= 0) {
                return i;
            }
        }
    }
    return 0xFFFF;
}

s32 func_8021215C(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32** arg6, f32** arg7, Vec3F** arg8) {
    ParsedUVMD* temp_s3;
    u16 i;
    Mtx4F* temp_s0;
    Unk80263780* temp_s1;
    u16 temp_v0;
    f32 sp98;

    D_802634C4 = 0;
    if ((arg0 == arg3) && (arg1 == arg4) && (arg2 == arg5)) {
        temp_v0 = func_80212008(arg0, arg1, arg2);
        if (temp_v0 == 0xFFFF) {
            *arg6 = NULL;
            *arg7 = NULL;
            *arg8 = NULL;
            return 0;
        }
        D_802634C8[0] = temp_v0;
        D_80263548[0] = 0.0f;
        D_802635C8[0].x = 0.0f;
        D_802635C8[0].y = 0.0f;
        D_802635C8[0].z = 1.0f;
        *arg6 = D_802634C8;
        *arg7 = D_80263548;
        *arg8 = D_802635C8;
        return 1;
    }

    for (i = 0; i < 100; i++) {
        temp_s1 = &D_80263780[i];

        if ((temp_s1->unk0 == 0xFFFF) || !(temp_s1->unk34 & 1)) {
            continue;
        }
        temp_s0 = &D_80265080[temp_s1->unk2[0]];
        temp_s3 = gGfxUnkPtrs->models[temp_s1->unk0];
        if (func_80214C64(arg0, arg1, arg2, arg3, arg4, arg5, temp_s0->m[3][0], temp_s0->m[3][1], temp_s0->m[3][2], temp_s1->unk38, &sp98) == 0) {
            continue;
        }
        if (!(temp_s3->unk11 & 2)) {
            D_802634C8[D_802634C4] = i;
            D_80263548[D_802634C4] = sp98;
            func_80215BC4(arg0, arg1, arg2, arg3, arg4, arg5, sp98, temp_s0->m[3][0], temp_s0->m[3][1], temp_s0->m[3][2], &D_802635C8[D_802634C4]);

            D_802634C4++;
            if (D_802634C4 >= HIT_COUNT) {
                break;
            }
            continue;
        }
        D_802634C0 = i;

        func_802139C8(arg0, arg1, arg2, arg3, arg4, arg5, temp_s1);
    }
    *arg6 = D_802634C8;
    *arg7 = D_80263548;
    *arg8 = D_802635C8;
    _uvDbSortHits();
    return D_802634C4;
}

s32 func_80212480(f32 arg0, f32 arg1, Vtx* vtx, u16 arg3, u16 arg4, u16 arg5, f32 arg6) {
    f32 temp_fa0;
    f32 var_fv0;
    f32 var_fv1;
    f32 var_ft4;
    f32 var_ft5;
    f32 var_fs0;
    f32 var_fs1;

    var_fv0 = vtx[arg3].v.ob[0];
    var_fv1 = vtx[arg3].v.ob[1];
    var_ft4 = vtx[arg4].v.ob[0];
    var_ft5 = vtx[arg4].v.ob[1];
    var_fs0 = vtx[arg5].v.ob[0];
    var_fs1 = vtx[arg5].v.ob[1];
    if (arg6 != 1.0f) {
        temp_fa0 = 1.0f / arg6;
        var_fv0 *= temp_fa0;
        var_fv1 *= temp_fa0;
        var_ft4 *= temp_fa0;
        var_ft5 *= temp_fa0;
        var_fs0 *= temp_fa0;
        var_fs1 *= temp_fa0;
    }
    if (((arg1 - var_fv1) * (var_ft4 - var_fv0)) < ((arg0 - var_fv0) * (var_ft5 - var_fv1))) {
        return 0;
    }
    if (((arg1 - var_ft5) * (var_fs0 - var_ft4)) < ((arg0 - var_ft4) * (var_fs1 - var_ft5))) {
        return 0;
    }

    if (((arg1 - var_fs1) * (var_fv0 - var_fs0)) < ((arg0 - var_fs0) * (var_fv1 - var_fs1))) {
        return 0;
    }

    return 1;
}

s32 func_80212604(f32 arg0, f32 arg1, Vtx* arg2, u16 arg3, u16 arg4, u16 arg5, f32 arg6) {
    f32 temp_fa0;
    f32 var_fv0;
    f32 var_fv1;
    f32 var_ft4;
    f32 var_ft5;
    f32 var_fs0;
    f32 var_fs1;

    var_fv0 = arg2[arg3].v.ob[0];
    var_fv1 = arg2[arg3].v.ob[1];
    var_ft4 = arg2[arg4].v.ob[0];
    var_ft5 = arg2[arg4].v.ob[1];
    var_fs0 = arg2[arg5].v.ob[0];
    var_fs1 = arg2[arg5].v.ob[1];
    if (arg6 != 1.0f) {
        temp_fa0 = 1.0f / arg6;
        var_fv0 *= temp_fa0;
        var_fv1 *= temp_fa0;
        var_ft4 *= temp_fa0;
        var_ft5 *= temp_fa0;
        var_fs0 *= temp_fa0;
        var_fs1 *= temp_fa0;
    }
    if (((arg0 - var_fv0) * (var_ft5 - var_fv1)) < ((arg1 - var_fv1) * (var_ft4 - var_fv0))) {
        return 0;
    }
    if (((arg0 - var_ft4) * (var_fs1 - var_ft5)) < ((arg1 - var_ft5) * (var_fs0 - var_ft4))) {
        return 0;
    }

    if (((arg0 - var_fs0) * (var_fv1 - var_fs1)) < ((arg1 - var_fs1) * (var_fv0 - var_fs0))) {
        return 0;
    }

    return 1;
}

s32 func_80212788(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 arg10, f32 arg11, f32 arg12,
                  f32 arg13, f32 arg14) {
    s32 pad;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv1;

    temp_fv0 = arg0 - arg6;
    temp_fv1 = arg1 - arg7;
    temp_fa0 = arg2 - arg8;
    temp_fa1 = arg9 - arg6;
    temp_ft4 = arg10 - arg7;
    temp_ft5 = arg11 - arg8;
    if ((((((temp_fv1 * temp_ft5) - (temp_fa0 * temp_ft4)) * arg3) - (((temp_fv0 * temp_ft5) - (temp_fa0 * temp_fa1)) * arg4)) +
         (((temp_fv0 * temp_ft4) - (temp_fv1 * temp_fa1)) * arg5)) > 0.0f) {
        return 0;
    }

    temp_fv0 = arg0 - arg9;
    temp_fv1 = arg1 - arg10;
    temp_fa0 = arg2 - arg11;
    temp_fa1 = arg12 - arg9;
    temp_ft4 = arg13 - arg10;
    temp_ft5 = arg14 - arg11;
    if ((((((temp_fv1 * temp_ft5) - (temp_fa0 * temp_ft4)) * arg3) - (((temp_fv0 * temp_ft5) - (temp_fa0 * temp_fa1)) * arg4)) +
         (((temp_fv0 * temp_ft4) - (temp_fv1 * temp_fa1)) * arg5)) > 0.0f) {
        return 0;
    }

    temp_fv0 = arg0 - arg12;
    temp_fv1 = arg1 - arg13;
    temp_fa0 = arg2 - arg14;
    temp_fa1 = arg6 - arg12;
    temp_ft4 = arg7 - arg13;
    temp_ft5 = arg8 - arg14;
    if ((((((temp_fv1 * temp_ft5) - (temp_fa0 * temp_ft4)) * arg3) - (((temp_fv0 * temp_ft5) - (temp_fa0 * temp_fa1)) * arg4)) +
         (((temp_fv0 * temp_ft4) - (temp_fv1 * temp_fa1)) * arg5)) > 0.0f) {
        return 0;
    }

    return 1;
}

s32 func_802129B0(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, Vtx* vtx, u16 arg7, u16 arg8, u16 arg9, f32 arg10, f32* arg11) {
    f32 temp_fv0;
    f32 spE0;
    f32 spDC;
    f32 var_fa0;
    f32 var_fa1;
    f32 var_ft4;
    f32 spCC;
    f32 spC8;
    f32 spC4;
    f32 spC0;
    f32 spBC;
    f32 spB8;
    f32 spB4;
    f32 spB0;
    f32 spAC;
    Vec3F spA0;
    Vec3F sp94;
    Vec3F sp88;
    f32 temp_fa0;
    s32 pad[2];
    f32 var_ft5;
    f32 var_fv0;
    f32 var_fv1;

    spCC = vtx[arg7].v.ob[0];
    spC8 = vtx[arg7].v.ob[1];
    spC4 = vtx[arg7].v.ob[2];
    spC0 = vtx[arg8].v.ob[0];
    spBC = vtx[arg8].v.ob[1];
    spB8 = vtx[arg8].v.ob[2];
    spB4 = vtx[arg9].v.ob[0];
    spB0 = vtx[arg9].v.ob[1];
    spAC = vtx[arg9].v.ob[2];
    if (arg10 != 1.0f) {
        temp_fv0 = 1.0f / arg10;
        spCC *= temp_fv0;
        spC8 *= temp_fv0;
        spC4 *= temp_fv0;
        spC0 *= temp_fv0;
        spBC *= temp_fv0;
        spB8 *= temp_fv0;
        spB4 *= temp_fv0;
        spB0 *= temp_fv0;
        spAC *= temp_fv0;
    }
    var_ft5 = arg0;
    var_fa1 = arg1;
    var_fv1 = arg2;
    var_ft4 = arg0;
    var_fa0 = arg1;
    var_fv0 = arg2;
    if (arg3 < var_ft4) {
        var_ft4 = arg3;
    } else {
        var_ft5 = arg3;
    }
    if (arg4 < arg1) {
        var_fa0 = arg4;
    } else {
        var_fa1 = arg4;
    }
    if (arg5 < arg2) {
        var_fv0 = arg5;
    } else {
        var_fv1 = arg5;
    }
    if (((spC4 < var_fv0) && (spB8 < var_fv0) && (spAC < var_fv0)) || ((var_fv1 < spC4) && (var_fv1 < spB8) && (var_fv1 < spAC)) ||
        ((spC8 < var_fa0) && (spBC < var_fa0) && (spB0 < var_fa0)) || ((var_fa1 < spC8) && (var_fa1 < spBC) && (var_fa1 < spB0)) ||
        ((spCC < var_ft4) && (spC0 < var_ft4) && (spB4 < var_ft4)) || ((var_ft5 < spCC) && (var_ft5 < spC0) && (var_ft5 < spB4))) {
        return 0;
    }
    spA0.x = spC0 - spCC;
    sp94.x = spB4 - spCC;
    spA0.y = spBC - spC8;
    sp94.y = spB0 - spC8;
    spA0.z = spB8 - spC4;
    sp94.z = spAC - spC4;
    uvVec3Cross(&sp88, &spA0, &sp94);
    uvVec3Normal(&sp88, &sp88);

    spDC = ((spCC - arg0) * sp88.x) + ((spC8 - arg1) * sp88.y) + ((spC4 - arg2) * sp88.z);

    spE0 = ((arg3 - arg0) * sp88.x) + ((arg4 - arg1) * sp88.y) + ((arg5 - arg2) * sp88.z);

    if (spE0 != 0.0f) {
        temp_fa0 = spDC / spE0;
    } else {
        return 0;
    }

    if ((temp_fa0 < 0.0f) || (temp_fa0 > 1.0f)) {
        return 0;
    }
    if (sp88.z == 0.0f) {
        if (func_80212788(((arg3 - arg0) * temp_fa0) + arg0, ((arg4 - arg1) * temp_fa0) + arg1, ((arg5 - arg2) * temp_fa0) + arg2, sp88.x, sp88.y, sp88.z, spCC,
                          spC8, spC4, spC0, spBC, spB8, spB4, spB0, spAC) != 0) {
            *arg11 = spDC / spE0;
            return 1;
        }
        *arg11 = 0.0f;
        return 0;
    }
    if (sp88.z > 0.0f) {
        if (func_80212480(((arg3 - arg0) * temp_fa0) + arg0, ((arg4 - arg1) * temp_fa0) + arg1, vtx, arg7, arg8, arg9, arg10) != 0) {
            *arg11 = spDC / spE0;
            return 1;
        }
        *arg11 = 0.0f;
        return 0;
    }
    if (func_80212604(((arg3 - arg0) * temp_fa0) + arg0, ((arg4 - arg1) * temp_fa0) + arg1, vtx, arg7, arg8, arg9, arg10) != 0) {
        *arg11 = spDC / spE0;
        return 1;
    }
    *arg11 = 0.0f;
    return 0;
}

s32 func_80212FF4(ParsedUVTR* arg0, f32 arg1, f32 arg2, f32 arg3, f32* arg4, f32* arg5, f32* arg6, u16* arg7, u16* arg8, u8 arg9) {
    f32 sp44;
    f32 sp40;
    f32 temp_ft4;
    f32 temp_fv0;
    f32 temp_fa0;
    f32 temp_fa1;
    u16 var_a2;
    u16 var_v0;
    u16 var_v0_3;
    u16 var_v1;
    u8 var_v0_2;

    *arg4 = arg1;
    *arg5 = arg2;
    *arg6 = arg3;
    sp44 = arg0->unk1C;
    sp40 = arg0->unk20;
    temp_fa0 = sp44 * 0.5f;
    temp_fa1 = sp40 * 0.5f;
    temp_ft4 = arg0->unk0.unk0;
    var_a2 = (s32)(arg1 - temp_ft4) / (s32)sp44;

    if (arg9 & 1) {
        var_a2 -= 1;
    }
    temp_fv0 = arg0->unk0.unk4;
    var_v0 = (s32)(arg2 - temp_fv0) / (s32)sp40;
    if (arg9 & 2) {
        var_v0 -= 1;
    }

    if ((var_a2 >= arg0->unk18) || (var_v0 >= arg0->unk19)) {
        return 0;
    }

    *arg7 = var_a2 + (var_v0 * arg0->unk18);

    *arg4 = ((arg1 - (var_a2 * sp44)) - temp_ft4) - temp_fa0;

    *arg5 = ((arg2 - (var_v0 * sp40)) - temp_fv0) - temp_fa1;

    if (*arg4 < -temp_fa0) {
        var_v0_2 = 1;
    } else if (temp_fa0 <= *arg4) {
        var_v0_2 = 1;
    } else if (*arg5 < -temp_fa1) {
        var_v0_2 = 1;
    } else if (temp_fa1 <= *arg5) {
        var_v0_2 = 1;
    } else {
        var_v0_2 = 0;
    }

    func_80214840(arg0->unk28[*arg7].unk44, arg4, arg5);
    if (var_v0_2) {
        *arg8 = 0;
    } else {
        var_v0_3 = (s32)(((*arg4 + temp_fa0) * 4.0f) / sp44);
        var_v1 = (s32)(((*arg5 + temp_fa1) * 4.0f) / sp40);
        if (var_v0_3 == 4) {
            var_v0_3 = 3;
        }

        if (var_v1 == 4) {
            var_v1 = 3;
        }
        *arg8 = 0x8000 >> ((var_v1 * 4) + (var_v0_3 % 4));
    }
    return 1;
}

u8 func_80213364(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    if ((SQ(arg0 - arg3) + SQ(arg1 - arg4) + SQ(arg2 - arg5)) <= SQ(arg6)) {
        return 1;
    }
    return 0;
}

s16 func_802133C8(f32 arg0, f32 arg1, f32 arg2, Mtx4F* arg3, UnkUVMD_24* arg4, u8 arg5) {
    Mtx4F sp60;
    Vec3F sp54;
    UnkUVMD_24* temp_s1;
    u16 i;
    s16 var_s3;
    s32 pad[2];

    if (arg4 == NULL) {
        return -1;
    }
    if (arg5 == 0) {
        return -1;
    }
    sp54.x = arg0;
    sp54.y = arg1;
    sp54.z = arg2;
    uvMat4InvertTranslationRotation(&sp60, arg3);
    uvMat4LocalToWorld(&sp60, &sp54, &sp54);
    var_s3 = -1;
    for (i = 0; i < arg5; i++) {
        temp_s1 = &arg4[i];
        if (func_80215CBC(sp54.x, sp54.y, sp54.z, &temp_s1->unk4) == 0) {
            i += temp_s1->unk1;
            continue;
        }
        if (temp_s1->unk2 != 0) {
            var_s3 = -1;
        } else {
            var_s3 = i;
        }

        if (temp_s1->unk1 == 0) {
            break;
        }
    }
    return var_s3;
}

s32 func_802134F8(f32 arg0, f32 arg1, f32 arg2, UnkSobjDraw* arg3) {
    ParsedUVMD* temp_fp;
    UnkUVMD_8* temp_s6;
    s32 temp_s5;
    s16 i;
    s16 j;
    f32 temp_fv0;
    Mtx4F spA4;
    s16 temp_s1;
    s16 temp_v0;

    temp_fp = gGfxUnkPtrs->models[arg3->unk0];
    temp_s6 = temp_fp->unk8;
    temp_s5 = temp_s6->unk4;
    _uvDbMstackReset();

    for (i = 0; i < temp_s5; i++) {
        uvMat4CopyL2F(&spA4, arg3->unk4[i]);
        if (i == 0) {
            temp_fv0 = temp_fp->unk20 / gGfxUnkPtrs->unk1608;
            uvMat4Scale(&spA4, temp_fv0, temp_fv0, temp_fv0);
            spA4.m[3][0] /= gGfxUnkPtrs->unk1608;
            spA4.m[3][1] /= gGfxUnkPtrs->unk1608;
            spA4.m[3][2] /= gGfxUnkPtrs->unk1608;
        } else {
            spA4.m[3][0] = 0.0f;
            spA4.m[3][1] = 0.0f;
            spA4.m[3][2] = 0.0f;
        }
        _uvDbMstackPush(&spA4);
        temp_v0 = func_802133C8(arg0, arg1, arg2, _uvDbMstackTop(), temp_s6->unk0[i].unk8, temp_s6->unk0[i].unkC);
        if (temp_v0 >= 0) {
            return temp_v0;
        }
        if (i == temp_s5 - 1) {
            break;
        }
        temp_s1 = temp_s6->unk0[i].unk6 - temp_s6->unk0[i + 1].unk6;
        for (j = 0; j <= temp_s1; j++) {
            _uvDbMstackPop();
        }
    }

    temp_s1 = temp_s6->unk0[temp_s6->unk4 - 1].unk6;
    for (i = 0; i <= temp_s1; i++) {
        _uvDbMstackPop();
    }
    return -1;
}

s32 func_80213790(f32 arg0, f32 arg1, f32 arg2, Unk80263780* arg3) {
    ParsedUVMD* temp_s5;
    UnkUVMD_8* temp_fp;
    s32 temp_s6;
    s16 i;
    s16 j;
    f32 temp_fv0;
    Mtx4F sp74;
    s16 temp_s1;
    s16 temp_v0;

    temp_s5 = gGfxUnkPtrs->models[arg3->unk0];
    temp_fp = temp_s5->unk8;
    temp_s6 = temp_fp->unk4;
    _uvDbMstackReset();

    for (i = 0; i < temp_s6; i++) {
        uvMat4Copy(&sp74, &D_80265080[arg3->unk2[i]]);
        if (i == 0) {
            temp_fv0 = temp_s5->unk20 * (arg3->unk38 / temp_s5->unk1C);
            uvMat4Scale(&sp74, temp_fv0, temp_fv0, temp_fv0);
        } else {
            sp74.m[3][0] = 0.0f;
            sp74.m[3][1] = 0.0f;
            sp74.m[3][2] = 0.0f;
        }
        _uvDbMstackPush(&sp74);
        temp_v0 = func_802133C8(arg0, arg1, arg2, _uvDbMstackTop(), temp_fp->unk0[i].unk8, temp_fp->unk0[i].unkC);
        if (temp_v0 >= 0) {
            return temp_v0;
        }
        if (i == temp_s6 - 1) {
            break;
        }

        temp_s1 = temp_fp->unk0[i].unk6 - temp_fp->unk0[i + 1].unk6;
        for (j = 0; j <= temp_s1; j++) {
            _uvDbMstackPop();
        }
    }

    temp_s1 = temp_fp->unk0[temp_fp->unk4 - 1].unk6;
    for (i = 0; i <= temp_s1; i++) {
        _uvDbMstackPop();
    }
    return -1;
}

s32 func_802139C8(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, Unk80263780* arg6) {
    s16 spE6;
    s16 temp_s1;
    ParsedUVMD* temp_s5;
    UnkUVMD_8* temp_s6;
    s16 i;
    s16 j;
    Mtx4F sp98;
    f32 temp_fv0;

    temp_s5 = gGfxUnkPtrs->models[arg6->unk0];
    temp_s6 = temp_s5->unk8;
    spE6 = temp_s6->unk4;
    _uvDbMstackReset();

    for (i = 0; i < spE6; i++) {
        uvMat4Copy(&sp98, &D_80265080[arg6->unk2[i]]);
        if (i == 0) {
            temp_fv0 = temp_s5->unk20 * (arg6->unk38 / temp_s5->unk1C);
            uvMat4Scale(&sp98, temp_fv0, temp_fv0, temp_fv0);
        } else {
            sp98.m[3][0] = 0.0f;
            sp98.m[3][1] = 0.0f;
            sp98.m[3][2] = 0.0f;
        }
        _uvDbMstackPush(&sp98);
        _uvSegInMboxs(arg0, arg1, arg2, arg3, arg4, arg5, _uvDbMstackTop(), temp_s6->unk0[i].unk8, temp_s6->unk0[i].unkC, temp_s5);
        if (i == spE6 - 1) {
            break;
        }
        temp_s1 = temp_s6->unk0[i].unk6 - temp_s6->unk0[i + 1].unk6;
        for (j = 0; j <= temp_s1; j++) {
            _uvDbMstackPop();
        }
    }
    temp_s1 = temp_s6->unk0[temp_s6->unk4 - 1].unk6;
    for (i = 0; i <= temp_s1; i++) {
        _uvDbMstackPop();
    }

    return -1;
}

s32 func_80213C24(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, UnkSobjDraw* arg6) {
    s16 sp106;
    s16 temp_s1;
    ParsedUVMD* temp_s6;
    UnkUVMD_8* temp_s5;
    s16 i;
    s16 j;
    Mtx4F spB8;
    f32 temp_fv0;

    temp_s6 = gGfxUnkPtrs->models[arg6->unk0];
    temp_s5 = temp_s6->unk8;
    sp106 = temp_s5->unk4;
    _uvDbMstackReset();

    for (i = 0; i < sp106; i++) {
        uvMat4CopyL2F(&spB8, arg6->unk4[i]);
        if (i == 0) {
            temp_fv0 = temp_s6->unk20 / gGfxUnkPtrs->unk1608;
            uvMat4Scale(&spB8, temp_fv0, temp_fv0, temp_fv0);
            spB8.m[3][0] /= gGfxUnkPtrs->unk1608;
            spB8.m[3][1] /= gGfxUnkPtrs->unk1608;
            spB8.m[3][2] /= gGfxUnkPtrs->unk1608;
        } else {
            spB8.m[3][0] = 0.0f;
            spB8.m[3][1] = 0.0f;
            spB8.m[3][2] = 0.0f;
        }
        _uvDbMstackPush(&spB8);
        _uvSegInMboxs(arg0, arg1, arg2, arg3, arg4, arg5, _uvDbMstackTop(), temp_s5->unk0[i].unk8, temp_s5->unk0[i].unkC, temp_s6);
        if (i == sp106 - 1) {
            break;
        }

        temp_s1 = temp_s5->unk0[i].unk6 - temp_s5->unk0[i + 1].unk6;
        for (j = 0; j <= temp_s1; j++) {
            _uvDbMstackPop();
        }
    }

    temp_s1 = temp_s5->unk0[temp_s5->unk4 - 1].unk6;
    for (i = 0; i <= temp_s1; i++) {
        _uvDbMstackPop();
    }
    return -1;
}

s32 func_80213EE0(f32 arg0, f32 arg1, f32 arg2, f32 arg3, Mtx4F* arg4, UnkUVMD_24* arg5, u8 arg6) {
    Mtx4F sp50;
    Vec3F sp44;
    s16 var_a2;
    u8 i;
    u8 var_v0;
    UnkUVMD_24* temp_a0;
    UnkUVMD_24_Unk4* temp_v0;

    if (arg5 == NULL) {
        return 1;
    }
    if (arg6 == 0) {
        return 1;
    }
    sp44.x = arg0;
    sp44.y = arg1;
    sp44.z = arg2;

    uvMat4InvertTranslationRotation(&sp50, arg4);
    uvMat4LocalToWorld(&sp50, &sp44, &sp44);
    var_a2 = -1;

    for (i = 0; i < arg6; i++) {
        temp_a0 = &arg5[i];
        temp_v0 = &temp_a0->unk4;

        if (sp44.x + arg3 < temp_v0->unk0) {
            var_v0 = 0;
        } else if (temp_v0->unkC < sp44.x - arg3) {
            var_v0 = 0;
        } else if (sp44.y + arg3 < temp_v0->unk4) {
            var_v0 = 0;
        } else if (temp_v0->unk10 < sp44.y - arg3) {
            var_v0 = 0;
        } else if (sp44.z + arg3 < temp_v0->unk8) {
            var_v0 = 0;
        } else if (temp_v0->unk14 < sp44.z - arg3) {
            var_v0 = 0;
        } else {
            var_v0 = 1;
        }

        if (!var_v0) {
            i += temp_a0->unk1;
            continue;
        }
        if (temp_a0->unk2 != 0) {
            var_a2 = -1;
        } else {
            var_a2 = i;
        }
        if (temp_a0->unk1 == 0) {
            break;
        }
    }
    return var_a2;
}

s32 func_802140BC(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    if (arg0 < arg2) {
        if (arg2 < arg4) {
            return 0;
        }
        if (arg5 < arg0) {
            return 0;
        }
    } else {
        if (arg0 < arg4) {
            return 0;
        }
        if (arg5 < arg2) {
            return 0;
        }
    }
    if (arg1 < arg3) {
        if (arg3 < arg6) {
            return 0;
        }
        if (arg7 < arg1) {
            return 0;
        }
    } else {
        if (arg1 < arg6) {
            return 0;
        }
        if (arg7 < arg3) {
            return 0;
        }
    }
    return 1;
}

void func_802141CC(f32* arg0, f32* arg1, f32* arg2, f32* arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    f32 temp_ft5;
    f32 sp10;
    f32 var_fa0;
    f32 var_fa1;
    f32 var_fv0;
    f32 var_fv1;

    var_fv0 = *arg0;
    var_fv1 = *arg1;
    var_fa0 = *arg2;
    var_fa1 = *arg3;
    if (var_fa0 == var_fv0) {
        if (var_fv0 < arg4) {
            var_fa0 = arg4;
            var_fv0 = arg4;
        } else if (arg5 < var_fv0) {
            var_fa0 = arg5;
            var_fv0 = arg5;
        }
        if (var_fv1 < arg6) {
            var_fv1 = arg6;
        } else if (arg7 < var_fv1) {
            var_fv1 = arg7;
        }
        if (var_fa1 < arg6) {
            var_fa1 = arg6;
        } else if (arg7 < var_fa1) {
            var_fa1 = arg7;
        }
        *arg0 = var_fv0;
        *arg1 = var_fv1;
        *arg2 = var_fa0;
        *arg3 = var_fa1;
    } else {
        temp_ft5 = (var_fa1 - var_fv1) / (var_fa0 - var_fv0);
        sp10 = var_fa1 - (temp_ft5 * var_fa0);
        if (var_fv0 < arg4) {
            var_fv1 = (temp_ft5 * arg4) + sp10;
            var_fv0 = arg4;
        } else if (arg5 < var_fv0) {
            var_fv1 = (temp_ft5 * arg5) + sp10;
            var_fv0 = arg5;
        }
        if (var_fv1 < arg6) {
            var_fv1 = arg6;
            if (temp_ft5 != 0.0f) {
                var_fv0 = (arg6 - sp10) / temp_ft5;
            }
        } else if (arg7 < var_fv1) {
            var_fv1 = arg7;
            if (temp_ft5 != 0.0f) {
                var_fv0 = (arg7 - sp10) / temp_ft5;
            }
        }
        if (var_fa0 < arg4) {
            var_fa0 = arg4;
            var_fa1 = (temp_ft5 * arg4) + sp10;
        } else if (arg5 < var_fa0) {
            var_fa0 = arg5;
            var_fa1 = (temp_ft5 * arg5) + sp10;
        }
        if (var_fa1 < arg6) {
            var_fa1 = arg6;
            if (temp_ft5 != 0.0f) {
                var_fa0 = (arg6 - sp10) / temp_ft5;
            }
        } else if (arg7 < var_fa1) {
            var_fa1 = arg7;
            if (temp_ft5 != 0.0f) {
                var_fa0 = (arg7 - sp10) / temp_ft5;
            }
        }
        *arg0 = var_fv0;
        *arg1 = var_fv1;
        *arg2 = var_fa0;
        *arg3 = var_fa1;
    }
}

void func_80214450(f32* arg0, f32* arg1, f32* arg2, f32* arg3, f32* arg4, f32* arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9) {
    f32 temp_ft4;
    f32 temp_fv0;
    f32 var_fs0;
    f32 var_fs3;
    f32 var_fs2;
    f32 var_fs1;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;

    // clang-format off
    var_fs0 = *arg0; \
    var_fs2 = *arg1; \
    sp4C = *arg2;    \
    var_fs3 = *arg3; \
    var_fs1 = *arg4; \
    sp48 = *arg5;
    // clang-format on

    sp44 = var_fs3 - var_fs0;
    sp40 = var_fs1 - var_fs2;
    sp3C = sp48 - sp4C;

    if (var_fs3 == var_fs0) {
        if (var_fs0 < arg6) {
            var_fs3 = arg6;
            var_fs0 = arg6;
        } else if (arg7 < var_fs0) {
            var_fs3 = arg7;
            var_fs0 = arg7;
        }
        if (var_fs2 < arg8) {
            var_fs2 = arg8;
        } else if (arg9 < var_fs2) {
            var_fs2 = arg9;
        }
        if (var_fs1 < arg8) {
            var_fs1 = arg8;
        } else if (arg9 < var_fs1) {
            var_fs1 = arg9;
        }
        *arg0 = var_fs0;
        *arg1 = var_fs2;
        *arg3 = var_fs3;
        *arg4 = var_fs1;
    } else {
        temp_fv0 = (var_fs1 - var_fs2) / (var_fs3 - var_fs0);
        temp_ft4 = var_fs1 - (temp_fv0 * var_fs3);
        if (var_fs0 < arg6) {
            var_fs2 = (temp_fv0 * arg6) + temp_ft4;
            var_fs0 = arg6;
        } else if (arg7 < var_fs0) {
            var_fs2 = (temp_fv0 * arg7) + temp_ft4;
            var_fs0 = arg7;
        }
        if (var_fs2 < arg8) {
            var_fs2 = arg8;
            if (temp_fv0 != 0.0f) {
                var_fs0 = (arg8 - temp_ft4) / temp_fv0;
            }
        } else if (arg9 < var_fs2) {
            var_fs2 = arg9;
            if (temp_fv0 != 0.0f) {
                var_fs0 = (arg9 - temp_ft4) / temp_fv0;
            }
        }
        if (var_fs3 < arg6) {
            var_fs1 = (temp_fv0 * arg6) + temp_ft4;
            var_fs3 = arg6;
        } else if (arg7 < var_fs3) {
            var_fs1 = (temp_fv0 * arg7) + temp_ft4;
            var_fs3 = arg7;
        }
        if (var_fs1 < arg8) {
            var_fs1 = arg8;
            if (temp_fv0 != 0.0f) {
                var_fs3 = (arg8 - temp_ft4) / temp_fv0;
            }
        } else if (arg9 < var_fs1) {
            var_fs1 = arg9;
            if (temp_fv0 != 0.0f) {
                var_fs3 = (arg9 - temp_ft4) / temp_fv0;
            }
        }

        if ((var_fs0 != *arg0) && (sp44 != 0.0f)) {
            sp4C += sp3C * ((var_fs0 - *arg0) / sp44);
        } else if ((var_fs2 != *arg1) && (sp40 != 0.0f)) {
            sp4C += sp3C * ((var_fs2 - *arg1) / sp40);
        }
        if ((var_fs3 != *arg3) && (sp44 != 0.0f)) {
            sp48 += sp3C * ((var_fs3 - *arg3) / sp44);
        } else if ((var_fs1 != *arg4) && (sp40 != 0.0f)) {
            sp48 += sp3C * ((var_fs1 - *arg4) / sp40);
        }
        *arg0 = var_fs0;
        *arg1 = var_fs2;
        *arg2 = sp4C;
        *arg3 = var_fs3;
        *arg4 = var_fs1;
        *arg5 = sp48;
    }
}

void func_80214840(s16 arg0, f32* arg1, f32* arg2) {
    f32 temp_fv0;
    f32 temp_fv1;

    // clang-format off
    temp_fv0 = *arg1; \
    temp_fv1 = *arg2;
    // clang-format on

    if (arg0 < 0) {
        arg0 += 4;
    } else if (arg0 >= 4) {
        arg0 %= 4;
    }
    switch (arg0) {
    case 0:
        *arg1 = temp_fv0;
        *arg2 = temp_fv1;
        break;
    case 1:
        *arg1 = temp_fv1;
        *arg2 = -temp_fv0;
        break;
    case 2:
        *arg1 = -temp_fv0;
        *arg2 = -temp_fv1;
        break;
    case 3:
        *arg1 = -temp_fv1;
        *arg2 = temp_fv0;
        break;
    }
}

u16 func_80214900(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 arg10, f32 arg11,
                  uvUnkTileStruct* arg12) {
    f32 sp50;
    f32 sp4C;
    f32 sp40;
    f32 sp38;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 var_fs0;
    f32 var_fs1;
    f32 var_fs2;
    f32 var_ft4;
    f32 var_ft5;
    s32 i;
    u16 sp5A;
    u16 sp58;
    u16 temp_v0;
    u16 temp_t4;

    sp5A = 0;
    sp58 = 0;
    sp50 = arg9 - arg8;
    sp4C = arg10 - arg11;

    if (arg4 < arg6) {
        var_ft5 = arg4;
        var_fs0 = arg6;
    } else {
        var_ft5 = arg6;
        var_fs0 = arg4;
    }

    if (arg5 < arg7) {
        var_fs1 = arg5;
        var_fs2 = arg7;
    } else {
        var_fs1 = arg7;
        var_fs2 = arg5;
    }

    temp_fa0 = 0.25f * sp50;
    var_ft4 = 2.0f * temp_fa0;
    sp38 = -temp_fa0;

    temp_fa1 = 0.25f * sp4C;
    sp40 = -temp_fa1;

    for (i = 0; (sp38 <= var_ft4) && (i < 4); i++) {
        if ((var_ft5 <= sp38) && ((sp38 - temp_fa0) <= var_fs0)) {
            sp58 |= 0x8888 >> i;
        }
        sp38 += temp_fa0;
    }
    temp_fv0 = 2.0f * temp_fa1;

    for (i = 0; (sp40 <= temp_fv0) && (i < 4); i++) {
        if ((var_fs1 <= sp40) && ((sp40 - temp_fa1) <= var_fs2)) {
            sp5A |= 0xF000 >> (i * 4);
        }
        sp40 += temp_fa1;
    }
    if (arg2 != arg0) {
        sp40 = (arg3 - arg1) / (arg2 - arg0);
        var_ft4 = arg3 - (sp40 * arg2);
    } else {
        sp40 = 2140143600.0f;
        var_ft4 = arg2;
    }

    temp_t4 = sp5A & sp58;
    temp_v0 = func_80214B3C(sp50, sp4C, arg12, sp40, var_ft4);

    return temp_t4 & temp_v0;
}

u16 func_80214B3C(f32 arg0, f32 arg1, uvUnkTileStruct* arg2, f32 arg3, f32 arg4) {
    s32 pad[2];
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    s32 pad2;
    u16 sp52;
    s16 sp50;
    s16 sp4E;

    sp52 = -1;

    sp64 = arg2->unk0.unk30 - (0.5f * arg0);
    sp60 = arg2->unk0.unk30 + (0.5f * arg0);
    sp5C = arg2->unk0.unk34 + (0.5f * arg1);
    sp58 = arg2->unk0.unk34 - (0.5f * arg1);
    uvComputeLineEndP(&sp50, &sp4E, &sp52, sp64, sp60, sp5C, sp58, arg4, arg3, 1.0f / arg3, 0, 15.0f / arg0, 15.0f / arg1);
    if (sp50 >= 0) {
        sp52 &= func_8022F62C(arg2->unk44, sp50, sp4E, 0);
        sp52 &= func_8022F62C(arg2->unk44, sp50, sp4E, 1);
    }
    return sp52;
}

u8 func_80214C64(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, f32* arg10) {
    f32 a;
    f32 b;
    f32 c;
    f32 root1;
    f32 root2;
    f32 discriminant;
    s32 temp_v0;
    s32 var_v1;
    s32 pad[2];
    s32 sp44;
    s32 pad2[2];

    a = SQ(arg3 - arg0) + SQ(arg4 - arg1) + SQ(arg5 - arg2);

    if (a == 0.0f) {
        temp_v0 = func_80213364(arg0, arg1, arg2, arg6, arg7, arg8, arg9);
        if (temp_v0 != 0) {
            *arg10 = 0.0f;
        }
        return temp_v0;
    }
    b = 2.0f * (((arg3 - arg0) * (arg0 - arg6)) + ((arg4 - arg1) * (arg1 - arg7)) + ((arg5 - arg2) * (arg2 - arg8)));

    c = (SQ(arg0 - arg6) + SQ(arg1 - arg7) + SQ(arg2 - arg8)) - SQ(arg9);

    sp44 = 0;
    if (uvSqrtF(SQ(arg0 - arg6) + SQ(arg1 - arg7) + SQ(arg2 - arg8)) < arg9) {
        sp44 = 1;
    }

    if ((uvSqrtF(SQ(arg3 - arg6) + SQ(arg4 - arg7) + SQ(arg5 - arg8)) < arg9) && (sp44 != 0)) {
        *arg10 = 0.0f;
        return 1;
    }

    if (SQ(b) < (4.0f * a * c)) {
        return 0;
    }
    discriminant = uvSqrtF(SQ(b) - (4.0f * a * c));

    root1 = (-b - discriminant) / (2.0f * a);
    root2 = (-b + discriminant) / (2.0f * a);

    sp44 = 0;
    var_v1 = 0;
    if ((root1 >= 0.0f) && (root1 <= 1.0f)) {
        sp44 = 1;
    }
    if ((root2 >= 0.0f) && (root2 <= 1.0f)) {
        var_v1 = 1;
    }
    if ((sp44 != 0) && (var_v1 != 0)) {
        if (root1 < root2) {
            *arg10 = root1;
        } else {
            *arg10 = root2;
        }
        return 1;
    }
    if (sp44 != 0) {
        *arg10 = root1;
        return 1;
    }

    if (var_v1 != 0) {
        *arg10 = root2;
        return 1;
    }

    return 0;
}

s32 _uvSegInMboxs(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, Mtx4F* arg6, UnkUVMD_24* arg7, u8 arg8, ParsedUVMD* arg9) {
    Mtx4F spB8;
    Vec3F spAC;
    Vec3F spA0;
    UnkUVMD_24* temp_s3;
    Vec3F* temp_a1;
    s32 var_v0;
    f32 sp90;
    f32 sp8C;
    f32 sp88;
    s16 sp86;
    s16 i;
    s16 j;
    s16 sp80;
    s16 sp7E;
    u8 temp_s0;

    if (arg7 == NULL) {
        return -1;
    }
    if (arg8 == 0) {
        return -1;
    }

    uvMat4InvertTranslationRotation(&spB8, arg6);
    spAC.x = arg0;
    spAC.y = arg1;
    spAC.z = arg2;
    spA0.x = arg3;
    spA0.y = arg4;
    spA0.z = arg5;
    uvMat4LocalToWorld(&spB8, &spAC, &spAC);
    uvMat4LocalToWorld(&spB8, &spA0, &spA0);

    for (i = 0; i < arg8; i++) {
        if (arg7[i].unk2 != 0) {
            _uvDebugPrintf("_uvSegInMboxs: warning, hollow no longer supported\n");
            return -1;
        }
    }

    sp86 = 0;
    for (i = 0; i < arg8; i++) {
        temp_s3 = &arg7[i];
        temp_s0 = func_802153D8(spAC.x, spAC.y, spAC.z, spA0.x, spA0.y, spA0.z, &temp_s3->unk4, &sp8C, &sp88, &sp80, &sp7E);

        if (temp_s0 == 0) {
            i += temp_s3->unk1;
            continue;
        }

        if (temp_s3->unk1 != 0) {
            continue;
        }

        if (temp_s3->unk1C != 0) {
            for (j = 0; j < temp_s3->unk1C; j++) {
                if (func_802129B0(spAC.x, spAC.y, spAC.z, spA0.x, spA0.y, spA0.z, arg9->vtx, temp_s3->unk20[j].unk0, temp_s3->unk20[j].unk2,
                                  temp_s3->unk20[j].unk4, arg9->unk20, &sp90) != 0) {
                    D_802634C8[D_802634C4] = D_802634C0;
                    D_80263548[D_802634C4] = sp90;
                    _uvSurfGetNorm(arg9->vtx, temp_s3->unk20[j].unk0, temp_s3->unk20[j].unk2, temp_s3->unk20[j].unk4, &D_802635C8[D_802634C4]);
                    arg6->m[3][0] = 0.0f;
                    arg6->m[3][1] = 0.0f;
                    arg6->m[3][2] = 0.0f;
                    uvMat4LocalToWorld(arg6, &D_802635C8[D_802634C4], &D_802635C8[D_802634C4]);
                    D_802634C4++;
                    sp86++;
                }
            }
        } else {
            func_80215D7C(arg6, sp80, &D_802635C8[D_802634C4]);

            D_802634C8[D_802634C4] = D_802634C0;
            if (temp_s0 == 1) {
                D_80263548[D_802634C4] = sp8C;
            } else if (temp_s0 == 2) {
                D_80263548[D_802634C4] = sp8C;
                D_802634C4++;
                D_802634C8[D_802634C4] = D_802634C0;
                func_80215D7C(arg6, sp7E, &D_802635C8[D_802634C4]);
                D_80263548[D_802634C4] = sp88;
            } else if (temp_s0 == 3) {
                D_80263548[D_802634C4] = 1.0f;
            }
            D_802634C4++;
            sp86++;
        }
    }

    if (sp86 != 0) {
        return sp86;
    }
    return -1;
}

u8 func_802153D8(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, UnkUVMD_24_Unk4* arg6, f32* arg7, f32* arg8, s16* arg9, s16* arg10) {
    s32 i;
    f32* sp5C[2];
    s16* sp54[2];
    s32 pad[2];
    f32 var_fa0;
    f32 sp44;
    f32 sp40;
    f32 var_fa1;
    f32 sp38;
    f32 sp34;
    f32 var_fv1;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 temp_fa0;
    f32 temp_fa1;

    i = 0;

    sp5C[0] = arg7;
    sp5C[1] = arg8;
    sp54[0] = arg9;
    sp54[1] = arg10;
    if (arg3 < arg0) {
        sp44 = arg0;
        sp38 = arg3;
    } else {
        sp44 = arg3;
        sp38 = arg0;
    }
    if (arg4 < arg1) {
        sp40 = arg1;
        sp34 = arg4;
    } else {
        sp40 = arg4;
        sp34 = arg1;
    }
    if (arg5 < arg2) {
        var_fa1 = arg2;
        var_fv1 = arg5;
    } else {
        // clang-format off
        var_fa1 = arg5; \
        var_fv1 = arg2;
        // clang format on
    }

    if (sp44 < arg6->unk0) {
        *sp54[i] = -1;
        return 0;
    }

    if (arg6->unkC < sp38) {
        *sp54[i] = 1;
        return 0;
    }

    if (sp40 < arg6->unk4) {
        *sp54[i] = -2;
        return 0;
    }

    if (arg6->unk10 < sp34) {
        *sp54[i] = 2;
        return 0;
    }

    if (var_fa1 < arg6->unk8) {
        *sp54[i] = -3;
        return 0;
    }

    if (arg6->unk14 < var_fv1) {
        *sp54[i] = 3;
        return 0;
    }
    if ((sp44 <= arg6->unkC) && (arg6->unk0 <= sp38) && (sp40 <= arg6->unk10) && (arg6->unk4 <= sp34) && (var_fa1 <= arg6->unk14) && (arg6->unk8 <= var_fv1)) {
        *sp54[i] = -1;
        return 3;
    }

    temp_fa1 = arg3 - arg0;
    temp_fa0 = arg4 - arg1;
    temp_fv1 = arg5 - arg2;

    if (var_fv1 <= arg6->unk8) {
        if (temp_fv1 == 0.0f) {
            var_fa0 = 0.0f;
        } else {
            var_fa0 = (arg6->unk8 - arg2) / temp_fv1;
        }
        temp_fv0 = (var_fa0 * temp_fa1) + arg0;
        if ((arg6->unk0 <= temp_fv0) && (temp_fv0 <= arg6->unkC)) {
            temp_fv0 = (var_fa0 * temp_fa0) + arg1;
            if ((arg6->unk4 <= temp_fv0) && (temp_fv0 <= arg6->unk10)) {
                *sp5C[i] = var_fa0;
                *sp54[i] = -3;
                i++;
                if (i == 2) {
                    return 2;
                }
            }
        }
    }

    if (arg6->unk14 <= var_fa1) {
        if (temp_fv1 == 0.0f) {
            var_fa0 = 0.0f;
        } else {
            var_fa0 = (arg6->unk14 - arg2) / temp_fv1;
        }
        temp_fv0 = (var_fa0 * temp_fa1) + arg0;
        if ((arg6->unk0 <= temp_fv0) && (temp_fv0 <= arg6->unkC)) {
            temp_fv0 = (var_fa0 * temp_fa0) + arg1;
            if ((arg6->unk4 <= temp_fv0) && (temp_fv0 <= arg6->unk10)) {
                *sp5C[i] = var_fa0;
                *sp54[i] = 3;
                i++;
                if (i == 2) {
                    return 2;
                }
            }
        }
    }

    if (sp34 <= arg6->unk4) {
        if (temp_fa0 == 0.0f) {
            var_fa0 = 0.0f;
        } else {
            var_fa0 = (arg6->unk4 - arg1) / temp_fa0;
        }
        temp_fv0 = (var_fa0 * temp_fa1) + arg0;
        if ((arg6->unk0 <= temp_fv0) && (temp_fv0 <= arg6->unkC)) {
            temp_fv0 = (var_fa0 * temp_fv1) + arg2;
            if ((arg6->unk8 <= temp_fv0) && (temp_fv0 <= arg6->unk14)) {
                *sp5C[i] = var_fa0;
                *sp54[i] = -2;
                i++;
                if (i == 2) {
                    return 2;
                }
            }
        }
    }

    if (arg6->unk10 <= sp40) {
        if (temp_fa0 == 0.0f) {
            var_fa0 = 0.0f;
        } else {
            var_fa0 = (arg6->unk10 - arg1) / temp_fa0;
        }
        temp_fv0 = (var_fa0 * temp_fa1) + arg0;
        if ((arg6->unk0 <= temp_fv0) && (temp_fv0 <= arg6->unkC)) {
            temp_fv0 = (var_fa0 * temp_fv1) + arg2;
            if ((arg6->unk8 <= temp_fv0) && (temp_fv0 <= arg6->unk14)) {
                *sp5C[i] = var_fa0;
                *sp54[i] = 2;
                i++;
                if (i == 2) {
                    return 2;
                }
            }
        }
    }

    if (sp38 <= arg6->unk0) {
        if (temp_fa1 == 0.0f) {
            var_fa0 = 0.0f;
        } else {
            var_fa0 = (arg6->unk0 - arg0) / temp_fa1;
        }
        temp_fv0 = (var_fa0 * temp_fv1) + arg2;
        if ((arg6->unk8 <= temp_fv0) && (temp_fv0 <= arg6->unk14)) {
            temp_fv0 = (var_fa0 * temp_fa0) + arg1;
            if ((arg6->unk4 <= temp_fv0) && (temp_fv0 <= arg6->unk10)) {
                *sp5C[i] = var_fa0;
                *sp54[i] = -1;
                i++;
                if (i == 2) {
                    return 2;
                }
            }
        }
    }

    if (arg6->unkC <= sp44) {
        if (temp_fa1 == 0.0f) {
            var_fa0 = 0.0f;
        } else {
            var_fa0 = (arg6->unkC - arg0) / temp_fa1;
        }
        temp_fv0 = (var_fa0 * temp_fv1) + arg2;
        if ((arg6->unk8 <= temp_fv0) && (temp_fv0 <= arg6->unk14)) {
            temp_fv0 = (var_fa0 * temp_fa0) + arg1;
            if ((arg6->unk4 <= temp_fv0) && (temp_fv0 <= arg6->unk10)) {
                *sp5C[i] = var_fa0;
                *sp54[i] = 1;
                i++;
                if (i == 2) {
                    return 2;
                }
            }
        }
    }

    return i;
}

void func_80215BC4(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, Vec3F* arg10) {
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    f32 temp_fv0;

    sp24 = (((arg3 - arg0) * arg6) + arg0) - arg7;
    sp20 = (((arg4 - arg1) * arg6) + arg1) - arg8;
    sp1C = (((arg5 - arg2) * arg6) + arg2) - arg9;

    temp_fv0 = uvSqrtF(SQ(sp24) + SQ(sp20) + SQ(sp1C));
    if (temp_fv0 != 0.0f) {
        sp24 = sp24 / temp_fv0;
        sp20 = sp20 / temp_fv0;
        sp1C = sp1C / temp_fv0;
    } else {
        sp24 = 0.0f;
        sp20 = 0.0f;
        sp1C = 1.0f;
    }
    arg10->f[0] = sp24;
    arg10->f[1] = sp20;
    arg10->f[2] = sp1C;
}

s32 func_80215CBC(f32 arg0, f32 arg1, f32 arg2, UnkUVMD_24_Unk4* arg3) {
    if (arg0 < arg3->unk0) {
        return 0;
    }
    if (arg3->unkC < arg0) {
        return 0;
    }
    if (arg1 < arg3->unk4) {
        return 0;
    }
    if (arg3->unk10 < arg1) {
        return 0;
    }
    if (arg2 < arg3->unk8) {
        return 0;
    }
    if (arg3->unk14 < arg2) {
        return 0;
    }
    return 1;
}

void func_80215D7C(Mtx4F* arg0, s16 arg1, Vec3F* arg2) {
    switch (arg1) {
        case -1:
            arg2->x = -arg0->m[0][0];
            arg2->y = -arg0->m[0][1];
            arg2->z = -arg0->m[0][2];
            break;
        case 1:
            arg2->x = arg0->m[0][0];
            arg2->y = arg0->m[0][1];
            arg2->z = arg0->m[0][2];
            break;
        case -2:
            arg2->x = -arg0->m[1][0];
            arg2->y = -arg0->m[1][1];
            arg2->z = -arg0->m[1][2];
            break;
        case 2:
            arg2->x = arg0->m[1][0];
            arg2->y = arg0->m[1][1];
            arg2->z = arg0->m[1][2];
            break;
        case -3:
            arg2->x = -arg0->m[2][0];
            arg2->y = -arg0->m[2][1];
            arg2->z = -arg0->m[2][2];
            break;
        case 3:
            arg2->x = arg0->m[2][0];
            arg2->y = arg0->m[2][1];
            arg2->z = arg0->m[2][2];
            break;
        default:
            break;
    }
}

void func_80215E7C(ParsedUVMD* arg0) {
    s32 i;
    s32 j;
    s32 var_s1;
    UnkUVMD_6* temp_v0;
    Mtx4F spD8;
    UnkUVMD_24* spD4;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fs2;
    f32 temp_fs3;
    f32 temp_fs4;
    f32 temp_fs5;
    u8 spBB;
    u8 spBA;
    u8 spB9;
    s32 spB4;
    s32 spB0;
    s32 spAC;

    uvGfxStatePush();
    uvGfxClearFlags(GFX_STATE_1000000 | GFX_STATE_400000 | GFX_STATE_200000);
    uvGfxSetFlags(GFX_STATE_800000 | GFX_STATE_20000 | 0xFFF);
    uvMat4SetIdentity(&spD8);
    uvMat4Scale(&spD8, 1.0f / arg0->unk20, 1.0f / arg0->unk20, 1.0f / arg0->unk20);
    uvGfxMtxViewMul(&spD8, 1);

    for (i = 0; i < arg0->unk8->unk0->unkC; i++) {
        spD4 = &arg0->unk8->unk0->unk8[i];
        var_s1 = 0;
        for (j = 0; j < spD4->unk1C; j++) {
            temp_v0 = &spD4->unk20[j];
            spB4 = temp_v0->unk0;
            spB0 = temp_v0->unk2;
            spAC = temp_v0->unk4;
            switch (var_s1 % 8) {
                case 0:
                    spBB = 0;
                    spBA = 0;
                    spB9 = 0;
                    break;
                case 1:
                    spBB = 0;
                    spBA = 0;
                    spB9 = 255;
                    break;
                case 2:
                    spBB = 0;
                    spBA = 255;
                    spB9 = 0;
                    break;
                case 3:
                    spBB = 0;
                    spBA = 255;
                    spB9 = 255;
                    break;
                case 4:
                    spBB = 255;
                    spBA = 0;
                    spB9 = 0;
                    break;
                case 5:
                    spBB = 255;
                    spBA = 0;
                    spB9 = 255;
                    break;
                case 6:
                    spBB = 255;
                    spBA = 255;
                    spB9 = 0;
                    break;
                case 7:
                    spBB = 255;
                    spBA = 255;
                    spB9 = 255;
                    break;
            }
            var_s1++;
            uvVtxBeginPoly();
            uvVtx(arg0->vtx[spB4].v.ob[0], arg0->vtx[spB4].v.ob[1], arg0->vtx[spB4].v.ob[2], 0, 0, spBB, spBA, spB9, 255);
            uvVtx(arg0->vtx[spB0].v.ob[0], arg0->vtx[spB0].v.ob[1], arg0->vtx[spB0].v.ob[2], 0, 0, spBB, spBA, spB9, 255);
            uvVtx(arg0->vtx[spAC].v.ob[0], arg0->vtx[spAC].v.ob[1], arg0->vtx[spAC].v.ob[2], 0, 0, spBB, spBA, spB9, 255);
            uvVtxEndPoly();
        }
        if (spD4->unk1C == 0) {
            if (spD4->unk2 != 0) {
                spB9 = 0;
                spBA = 0;
                spBB = 255;
            } else {
                spB9 = 255;
                spBA = 255;
                spBB = 255;
            }

            temp_fs0 = spD4->unk4.unk0 * arg0->unk20;
            temp_fs1 = spD4->unk4.unk4 * arg0->unk20;
            temp_fs2 = spD4->unk4.unk8 * arg0->unk20;
            temp_fs3 = spD4->unk4.unkC * arg0->unk20;
            temp_fs4 = spD4->unk4.unk10 * arg0->unk20;
            temp_fs5 = spD4->unk4.unk14 * arg0->unk20;
            uvVtxBeginPoly();
            uvVtx(temp_fs0, temp_fs1, temp_fs2, 0, 0, 255, spBA, spB9, 120);
            uvVtx(temp_fs0, temp_fs4, temp_fs2, 0, 0, 255, spBA, spB9, 120);
            uvVtx(temp_fs3, temp_fs4, temp_fs2, 0, 0, 255, spBA, spB9, 120);
            uvVtx(temp_fs3, temp_fs1, temp_fs2, 0, 0, 255, spBA, spB9, 120);
            uvVtxEndPoly();
            uvVtxBeginPoly();
            uvVtx(temp_fs0, temp_fs1, temp_fs5, 0, 0, 255, spBA, spB9, 120);
            uvVtx(temp_fs3, temp_fs1, temp_fs5, 0, 0, 255, spBA, spB9, 120);
            uvVtx(temp_fs3, temp_fs4, temp_fs5, 0, 0, 255, spBA, spB9, 120);
            uvVtx(temp_fs0, temp_fs4, temp_fs5, 0, 0, 255, spBA, spB9, 120);
            uvVtxEndPoly();
            uvVtxBeginPoly();
            uvVtx(temp_fs0, temp_fs4, temp_fs2, 0, 0, 255, spBA, spB9, 120);
            uvVtx(temp_fs0, temp_fs1, temp_fs2, 0, 0, 255, spBA, spB9, 120);
            uvVtx(temp_fs0, temp_fs1, temp_fs5, 0, 0, 255, spBA, spB9, 120);
            uvVtx(temp_fs0, temp_fs4, temp_fs5, 0, 0, 255, spBA, spB9, 120);
            uvVtxEndPoly();
            uvVtxBeginPoly();
            uvVtx(temp_fs3, temp_fs4, temp_fs2, 0, 0, 255, spBA, spB9, 120);
            uvVtx(temp_fs3, temp_fs4, temp_fs5, 0, 0, 255, spBA, spB9, 120);
            uvVtx(temp_fs3, temp_fs1, temp_fs5, 0, 0, 255, spBA, spB9, 120);
            uvVtx(temp_fs3, temp_fs1, temp_fs2, 0, 0, 255, spBA, spB9, 120);
            uvVtxEndPoly();
            uvVtxBeginPoly();
            uvVtx(temp_fs0, temp_fs1, temp_fs2, 0, 0, 255, spBA, spB9, 120);
            uvVtx(temp_fs3, temp_fs1, temp_fs2, 0, 0, 255, spBA, spB9, 120);
            uvVtx(temp_fs3, temp_fs1, temp_fs5, 0, 0, 255, spBA, spB9, 120);
            uvVtx(temp_fs0, temp_fs1, temp_fs5, 0, 0, 255, spBA, spB9, 120);
            uvVtxEndPoly();
            uvVtxBeginPoly();
            uvVtx(temp_fs0, temp_fs4, temp_fs2, 0, 0, 255, spBA, spB9, 120);
            uvVtx(temp_fs0, temp_fs4, temp_fs5, 0, 0, 255, spBA, spB9, 120);
            uvVtx(temp_fs3, temp_fs4, temp_fs5, 0, 0, 255, spBA, spB9, 120);
            uvVtx(temp_fs3, temp_fs4, temp_fs2, 0, 0, 255, spBA, spB9, 120);
            uvVtxEndPoly();
        }
    }

    uvGfxMtxViewPop();
    uvGfxStatePop();
}

void uvDbColorModel(s32 modelId, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    ParsedUVMD* temp_v0;

    temp_v0 = gGfxUnkPtrs->models[modelId];
    if (temp_v0 == NULL) {
        _uvDebugPrintf("uvDbColorModel: model %d not in level\n", modelId);
        return;
    }

    uvGfxWaitForMesg();
    func_8020ABAC(temp_v0->vtx, temp_v0->vtxCount, arg1, arg2, arg3, arg4, arg4, arg4);
}
