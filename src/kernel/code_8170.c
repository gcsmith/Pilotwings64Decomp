#include "common.h"
#include <uv_dobj.h>
#include <uv_graphics.h>
#include <uv_memory.h>
#include <uv_sobj.h>
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

extern u32 D_802634C0;

s32 func_80212480(f32, f32, Vtx*, u16, u16, u16, f32);
s32 func_80212FF4(ParsedUVTR*, f32, f32, f32, f32*, f32*, f32*, u16*, u16*, s32);
s32 _uvSurfGetNorm(Vtx*, s32, s32, s32, Vec3F*);
void func_80214840(s16, f32*, f32*);
s32 func_80213364(f32, f32, f32, f32, f32, f32, f32);
s32 func_802134F8(f32, f32, f32, UnkSobjDraw*);
s32 func_80213364(f32, f32, f32, f32, f32, f32, f32);
s32 func_80213790(f32, f32, f32, Unk80263780*);
void func_802139C8(f32, f32, f32, f32, f32, f32, Unk80263780*);
s32 func_80214C64(f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32*);
void func_80215BC4(f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, Vec3F*);

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

u32 uvTerraGetPt(s32 arg0, f32 arg1, f32 arg2, s32** arg3) {
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

    temp_s0 = gGfxUnkPtrs->terras[arg0];
    var_s2 = 0;
    if (temp_s0 == NULL) {
        _uvDebugPrintf("uvTerraGetPt: terra %d not defined for level\n", arg0);
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
            if (var_s2 >= 32) {
                break;
            }
        }
    }
    *arg3 = D_802634C8;
    return var_s2;
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/uvTerraGetSeg.s")

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
    temp_v1 = &temp_v0->unk28[(surfaceId >> 0x16) & 0x3FF];
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

void uvTerraGetPlane(s32 terraId, u32 surfaceId, f32 arg2, f32 arg3, f32* arg4, Vec3F* arg5) {
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
    func_80212FF4(temp_a0, arg2, arg3, 0.0f, &sp60, &sp5C, &sp58, &sp56, &sp54, 0);
    sp60 *= gGfxUnkPtrs->unk1608;
    sp5C *= gGfxUnkPtrs->unk1608;
    sp58 *= gGfxUnkPtrs->unk1608;
    if (_uvSurfGetNorm(sp64, temp_s2->unk0, temp_s2->unk2, temp_s2->unk4, arg5) == 0) {
        _uvDebugPrintf("uvTerraGetPlane:  terra[%d]  sid[0x%x] is bad - px:%.2f , py:%.2f\n", terraId, surfaceId, arg2, arg3);
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

s32 uvSobjGetPt(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
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

    temp_s0 = gGfxUnkPtrs->terras[arg0];
    if (temp_s0 == NULL) {
        _uvDebugPrintf("uvSobjGetPt: terra %d not defined for level\n", arg0);
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
                    return ((arg0 & 0xFF) << 24) | ((sp7C & 0xFFF) << 12) | (i & 0xFFF);
                }
            } else {
                return ((arg0 & 0xFF) << 24) | ((sp7C & 0xFFF) << 12) | (i & 0xFFF);
            }
        }
    }

    return -1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_8170/uvSobjGetSeg.s")

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
            if (D_802634C4 >= 32) {
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

s32 func_80212788(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 arg10, f32 arg11, f32 arg12, f32 arg13, f32 arg14) {
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
    if ((((((temp_fv1 * temp_ft5) - (temp_fa0 * temp_ft4)) * arg3) - (((temp_fv0 * temp_ft5) - (temp_fa0 * temp_fa1)) * arg4)) + (((temp_fv0 * temp_ft4) - (temp_fv1 * temp_fa1)) * arg5)) > 0.0f) {
        return 0;
    }

    temp_fv0 = arg0 - arg9;
    temp_fv1 = arg1 - arg10;
    temp_fa0 = arg2 - arg11;
    temp_fa1 = arg12 - arg9;
    temp_ft4 = arg13 - arg10;
    temp_ft5 = arg14 - arg11;
    if ((((((temp_fv1 * temp_ft5) - (temp_fa0 * temp_ft4)) * arg3) - (((temp_fv0 * temp_ft5) - (temp_fa0 * temp_fa1)) * arg4)) + (((temp_fv0 * temp_ft4) - (temp_fv1 * temp_fa1)) * arg5)) > 0.0f) {
        return 0;
    }

    temp_fv0 = arg0 - arg12;
    temp_fv1 = arg1 - arg13;
    temp_fa0 = arg2 - arg14;
    temp_fa1 = arg6 - arg12;
    temp_ft4 = arg7 - arg13;
    temp_ft5 = arg8 - arg14;
    if ((((((temp_fv1 * temp_ft5) - (temp_fa0 * temp_ft4)) * arg3) - (((temp_fv0 * temp_ft5) - (temp_fa0 * temp_fa1)) * arg4)) + (((temp_fv0 * temp_ft4) - (temp_fv1 * temp_fa1)) * arg5)) > 0.0f) {
        return 0;
    }
    
    return 1;
}

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
