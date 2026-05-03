#include <macros.h>
#include <uv_chan.h>
#include <uv_environment.h>
#include <uv_fx.h>
#include <uv_graphics.h>
#include <uv_math.h>
#include <uv_memory.h>
#include <uv_sobj.h>
#include <uv_terrain.h>
#include <libc/stdarg.h>
#include "kernel/code_7150.h"

UnkStruct_80204D94 D_80261730[2];
u8 D_80261E70[100];
UnkSortAdd D_80261ED8[100];
UnkSortAdd D_802629C8[60];
s32 D_80263058;
s32 D_8026305C;
u8 D_80263060[1040];

// TODO FIXME fix for gSPPerspNormalize, due to older f3d ucode
#undef gSPPerspNormalize
#define gSPPerspNormalize(pkt, s)                   \
    {                                               \
        Gfx* _g = (Gfx*)(pkt);                      \
                                                    \
        _g->words.w0 = _SHIFTL(G_RDPHALF_1, 24, 8); \
        _g->words.w1 = (s);                         \
    }

extern f32 gGfxFogFactor;

void func_80204930(void) {
    s32 i;
    s32 j;
    UnkStruct_80204D94* var_s0;

    for (i = 0; i < 2; i++) {
        var_s0 = &D_80261730[i];
        var_s0->unk0 = 0;
        var_s0->unk2 = 0;
        var_s0->unk4 = 0;

        for (j = 0; j < 1; j++) {
            var_s0->unk6[j] = 0xFF;
        }

        uvMat4SetIdentity(&var_s0->unk10);
        uvMat4SetIdentity(&var_s0->unk90);
        uvMat4SetIdentity(&var_s0->unk110);
        var_s0->unk1D0 = 0.0f;
        var_s0->unk1D4 = 0.0f;
        var_s0->unk1D8 = 0.0f;
        var_s0->unk1DC = 0.0f;
        var_s0->unk1E0 = 1.0f;
        var_s0->unk1E4 = 0.0f;
        var_s0->unk398 = NULL;
        var_s0->unk39C = NULL;
        var_s0->unk200 = 1.0f;
        var_s0->unk204 = 1.0f;
        var_s0->viewX0 = 0;
        var_s0->viewX1 = SCREEN_WIDTH;
        var_s0->viewY0 = 0;
        var_s0->viewY1 = SCREEN_HEIGHT;
        var_s0->unk394 = 0;
        func_80204D94(i, var_s0->viewX0, var_s0->viewX1, var_s0->viewY0, var_s0->viewY1);
    }
}

void func_80204A8C(s32 arg0, s32 arg1) {
    D_80261730[arg0].unk0 = arg1;
}

void func_80204AB0(s32 arg0, s32 arg1, void (*arg2)(void)) {
    if (arg1 != 0) {
        if (arg1 == 1) {
            D_80261730[arg0].unk39C = arg2;
        }
    } else {
        D_80261730[arg0].unk398 = arg2;
    }
}

void func_80204B08(s32 arg0, s32 arg1, s32 arg2) {
    D_80261730[arg0].unk6[arg1] = arg2;
}

void func_80204B34(s32 arg0, Mtx4F* arg1) {
    UnkStruct_80204D94* temp_s0;

    temp_s0 = &D_80261730[arg0];
    uvMat4Copy(&temp_s0->unk110, arg1);
    func_802057F4(&temp_s0->unk190, arg1);
    uvMat4CopyF2L(&temp_s0->unk150, &temp_s0->unk190);
    temp_s0->unk1D0 = arg1->m[3][0];
    temp_s0->unk1D4 = arg1->m[3][1];
    temp_s0->unk1D8 = arg1->m[3][2];
    temp_s0->unk1DC = arg1->m[1][0];
    temp_s0->unk1E0 = arg1->m[1][1];
    temp_s0->unk1E4 = arg1->m[1][2];
}

void func_80204BD4(s32 arg0, s32 arg1, f32 arg2) {
    switch (arg1) {
    case 0:
        D_80261730[arg0].unk200 = 1.0f / arg2;
        break;
    case 1:
        D_80261730[arg0].unk204 = 1.0f / arg2;
        break;
    }
}

void func_80204C54(s32 arg0, Mtx4F* arg1) {
    uvMat4Copy(&D_80261730[arg0].unk10, arg1);
}

void func_80204C94(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 near, f32 far) {
    UnkStruct_80204D94* temp_s0;
    temp_s0 = &D_80261730[arg0];
    temp_s0->unk1E8 = arg1;
    temp_s0->unk1EC = arg2;
    temp_s0->unk1F0 = arg3;
    temp_s0->unk1F4 = arg4;
    temp_s0->unk1F8 = near;
    temp_s0->unk1FC = far;
    uvMat4SetFrustrum(&temp_s0->unk10, arg1, arg2, arg3, arg4, near, far);
    uvMat4CopyF2L(&temp_s0->unk50, &temp_s0->unk10);
    uvMat4SetFrustrum(&temp_s0->unk90, arg1, arg2, arg3, arg4, near, 27000.0f);
    uvMat4CopyF2L(&temp_s0->unkD0, &temp_s0->unk90);
    func_802061A0(temp_s0);
}

void func_80204D94(s32 vpId, s32 x0, s32 x1, s32 y0, s32 y1) {
    UnkStruct_80204D94* temp_v0;
    temp_v0 = &D_80261730[vpId];
    temp_v0->viewX0 = x0;
    temp_v0->viewX1 = x1;
    temp_v0->viewY0 = y0;
    temp_v0->viewY1 = y1;
    uvGfxClipViewport(vpId, x0, x1, y0, y1);
}

void uvChanEnv(s32 arg0, s32 arg1) {
    if ((arg1 != 0xFFFF) && (gGfxUnkPtrs->environments[arg1] == NULL)) {
        _uvDebugPrintf("uvChanEnv: environment %d not in level\n", arg1);
        return;
    }
    D_80261730[arg0].unk2 = arg1;
}

void uvChanTerra(s32 arg0, s32 arg1) {
    if (gGfxUnkPtrs->terras[arg1] == NULL) {
        _uvDebugPrintf("uvChanTerra: terra %d not in level\n", arg1);
        return;
    }
    D_80261730[arg0].unk4 = arg1;
}

s32 func_80204EC0(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    f32 x, y, z, w;
    UnkStruct_80204D94* temp_v0;

    temp_v0 = &D_80261730[arg0];
    x = arg1 - temp_v0->unk110.m[3][0];
    y = arg2 - temp_v0->unk110.m[3][1];
    z = arg3 - temp_v0->unk110.m[3][2];
    w = arg4;
    if ((temp_v0->unk1FC + w) < uvSqrtF(SQ(x) + SQ(y) + SQ(z))) {
        return 0;
    }
    return func_80206F64(temp_v0->unk2E0, x, y, z, w);
}

u8* func_80204F9C(s32 arg0) {
    return (u8*)&D_80261730[arg0].unk374;
}

void func_80204FC4(s32 arg0) {
    func_80204FE4(arg0);
}

void func_80204FE4(s32 arg0) {
    UnkStruct_80204D94* temp_s0;
    ParsedUVTR* uvtr;
    s32 var_v0;
    f32 spC0;
    f32 spBC;
    f32 spB8;
    f32 spB4;
    f32 spB0;
    f32 spAC;
    f32 spA8;
    f32 temp_fv1;
    s32 spA0;

    D_80263058 = 0;
    D_8026305C = 0;
    temp_s0 = &D_80261730[arg0];

    if (temp_s0->unk0 == 0) {
        return;
    }
    if (temp_s0->unk398 != NULL) {
        temp_s0->unk398();
    }
    func_80206318(temp_s0);
    uvGfxMtxProj(temp_s0->unk50);
    uvGfxPushMtxUnk(&temp_s0->unk190);
    gSPPerspNormalize(gGfxDisplayListHead++, (s16)(131072.0f / (temp_s0->unk1FC + temp_s0->unk1F8)));
    uvGfxViewport(arg0);
    if (!(temp_s0->unk0 & 4)) {
        uvGfx_80222A98();
    }

    gSPClipRatio(gGfxDisplayListHead++, FRUSTRATIO_1);

    _uvEnvDraw(arg0, temp_s0->unk2);
    if (!(temp_s0->unk0 & 8)) {
        gSPClipRatio(gGfxDisplayListHead++, FRUSTRATIO_2);
    }
    gDPPipeSync(gGfxDisplayListHead++);
    gSPSetGeometryMode(gGfxDisplayListHead++, G_ZBUFFER);
    gSPSetGeometryMode(gGfxDisplayListHead++, G_SHADE);
    gDPSetCombineMode(gGfxDisplayListHead++, G_CC_SHADE, G_CC_PASS2);

    if (gGfxFogFactor > 0.0f) {
        gDPSetRenderMode(gGfxDisplayListHead++, G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2);
    } else {
        gDPSetRenderMode(gGfxDisplayListHead++, G_RM_PASS, G_RM_AA_ZB_OPA_SURF2);
    }
    if (temp_s0->unk0 & 2) {
        _uvTerraDraw(temp_s0, temp_s0->unk4);
        uvtr = gGfxUnkPtrs->terras[temp_s0->unk4];
        if (uvtr != NULL) {
            uvMemSet(D_80263060, 0, uvtr->unk18 * uvtr->unk19);
        }
    } else {
        uvtr = NULL;
    }
    func_8021EA38(temp_s0);
    _uvDobjsDraw(temp_s0, 0);

    if (FABS(0.996f - gGfxFogFactor) < 0.0001f) {
        var_v0 = 1;
    } else {
        var_v0 = 0;
    }
    if (var_v0 && (uvtr != NULL)) {
        spBC = temp_s0->unk1E8;
        spB8 = temp_s0->unk1EC;
        spB4 = temp_s0->unk1F0;
        spB0 = temp_s0->unk1F4;
        spAC = temp_s0->unk1F8;
        spA8 = temp_s0->unk1FC;
        temp_fv1 = temp_s0->unk1FC / (spAC * 50.0f);
        spC0 = temp_s0->unk1FC * 0.66667f;
        if (spC0 < uvtr->unk24) {
            spC0 = 1e11f;
        }
        func_80204C94(temp_s0 - D_80261730, spBC * temp_fv1, spB8 * temp_fv1, spB4 * temp_fv1, spB0 * temp_fv1, spAC * temp_fv1, spA8);
        uvGfxMtxProj(temp_s0->unk50);
        func_8022EE90(temp_s0, uvtr, spC0);
        uvGfxSetFogFactor(0.0f);
        spA0 = D_80263058;
        func_80205BFC();
        func_80205CE4(temp_s0, 0, spC0 - uvtr->unk24, 1e12f);
        func_80205CE4(temp_s0, 1, spC0 - uvtr->unk24, 1e12f);
        uvGfxResetState();
        uvGfx_80222A98();
        func_80204C94(temp_s0 - D_80261730, spBC, spB8, spB4, spB0, spAC, spA8);
        uvGfxMtxProj(temp_s0->unk50);
        func_8022EFB4(temp_s0, uvtr, spC0);
        if (spA0 != D_80263058) {
            func_80205BFC();
        }
        func_80205CE4(temp_s0, 0, 0.0f, spC0 - uvtr->unk24);
        func_80205CE4(temp_s0, 1, 0.0f, spC0 - uvtr->unk24);
    } else {
        if (uvtr != NULL) {
            func_8022EE90(temp_s0, uvtr, 0.0f);
        }
        func_80205BFC();
        func_80205CE4(temp_s0, 0, -1.0f, 1e12f);
        func_80205CE4(temp_s0, 1, -1.0f, 1e12f);
    }
    _uvDobjsDraw(temp_s0, 1);
    uvSprtDrawAll();
    uvDobj_8021771C(temp_s0);
    uvGfxResetState();
    if (temp_s0->unk39C != NULL) {
        temp_s0->unk39C();
    }
}

void func_80205724(s32 arg0, s32 arg1, Mtx4F* arg2) {
    switch (arg1) {
    case 1:
        uvMat4Copy(arg2, &D_80261730[arg0].unk110);
        return;
    case 2:
        uvMat4Copy(arg2, &D_80261730[arg0].unk10);
        return;
    case 3:
        uvMat4Copy(arg2, &D_80261730[arg0].unk190);
        return;
    }
}

void func_802057F4(Mtx4F* arg0, Mtx4F* arg1) {
    uvMat4InvertTranslationRotation(arg0, arg1);
}

void _uvSortAdd(s32 arg0, f32 arg1, void* arg2, UnkStruct_80204D94* arg3, f32 arg4, f32 arg5, ...) {
    UnkSortAdd* var_a1;
    ParsedUVTR* uvtr;
    s32 var_v1;
    s32 var_a0;
    va_list args;

    if (arg0 > 0) {
        if (D_80263058 >= 100) {
            _uvDebugPrintf("_uvSortAdd: sort list full %d\n", 100);
            return;
        }
        var_a1 = &D_80261ED8[D_80263058];
        D_80263058++;
    } else {
        if (D_8026305C >= 60) {
            _uvDebugPrintf("_uvSortAdd: dobj list full for %d\n", 60);
            return;
        }

        var_a1 = &D_802629C8[D_8026305C];
        D_8026305C++;
        arg0 = -arg0;
    }
    var_a1->unk0 = arg0;
    var_a1->unk4 = arg1;
    var_a1->unk10 = arg2;
    if (arg3->unk0 & 2) {
        uvtr = gGfxUnkPtrs->terras[arg3->unk4];
    } else {
        uvtr = NULL;
    }
    if (uvtr != NULL) {
        if ((arg4 < uvtr->unk0.unk0) || (uvtr->unk0.unkC <= arg4) || (arg5 < uvtr->unk0.unk4) || (uvtr->unk0.unk10 <= arg5)) {
            var_a1->unk14 = 0xFFFF;
        } else {
            var_v1 = (s32)(arg4 - uvtr->unk0.unk0) / (s32)uvtr->unk1C;
            var_a0 = (s32)(arg5 - uvtr->unk0.unk4) / (s32)uvtr->unk20;
            var_a1->unk14 = var_v1 + uvtr->unk18 * var_a0;
        }
    } else {
        var_a1->unk14 = 0xFFFF;
    }

    // passing an object that undergoes default argument promotion to 'va_start'
    // has undefined behavior (e.g. u8, u16, f32)
#if defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wvarargs"
#endif
    va_start(args, arg5);
#if defined(__clang__)
#pragma GCC diagnostic pop
#endif

    switch (arg0) {
    case 1:
        break;
    case 2:
        var_a1->unk1 = va_arg(args, s32);
        break;
    case 3:
        var_a1->unk1 = va_arg(args, s32);
        var_a1->unk8 = va_arg(args, f64);
        var_a1->unkC = va_arg(args, f64);
        break;
    case 4:
        var_a1->unk8 = va_arg(args, f64);
        var_a1->unkC = va_arg(args, f64);
        var_a1->unk18 = va_arg(args, Mtx4F*);
        var_a1->unk2 = va_arg(args, s32);
        var_a1->unk1 = va_arg(args, s32);
        break;
    }
}

void func_80205BFC(void) {
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_fv0;
    s32 i;
    s32 j;

    for (i = 0; i < D_80263058; i++) {
        var_fv0 = -1000000.0f;
        for (j = 0; j < D_80263058; j++) {
            temp_fv1 = D_80261ED8[j].unk4;
            if (var_fv0 < temp_fv1) {
                D_80261E70[i] = j;
                var_fv0 = temp_fv1;
            }
        }

        D_80261ED8[D_80261E70[i]].unk4 = -D_80261ED8[D_80261E70[i]].unk4;
    }
    for (i = 0; i < D_80263058; i++) {
        temp_fv0 = D_80261ED8[i].unk4;
        if (temp_fv0 < 0.0f) {
            D_80261ED8[i].unk4 = -temp_fv0;
        }
    }
}

void func_80205CE4(UnkStruct_80204D94* arg0, s32 arg1, f32 arg2, f32 arg3) {
    ParsedUVMD* uvmd;
    UnkSortAdd* var_s1;
    s32 i;
    s32 var_s6;

    if (arg1 != 0) {
        var_s6 = D_80263058;
    } else {
        var_s6 = D_8026305C;
    }

    for (i = 0; i < var_s6; i++) {
        if (arg1 != 0) {
            var_s1 = &D_80261ED8[D_80261E70[i]];
        } else {
            var_s1 = &D_802629C8[i];
        }

        if (var_s1->unk14 == 0xFFFF) {
            if ((var_s1->unk4 < arg2)) {
                continue;
            }
            if (arg3 <= var_s1->unk4) {
                continue;
            }
        } else if ((arg2 != -1.0f)) {
            if (((arg2 == 0.0f) && (D_80263060[var_s1->unk14] == 1))) {
                continue;
            }
            if (((arg2 != 0.0f) && (D_80263060[var_s1->unk14] == 0))) {
                continue;
            }
        }

        switch (var_s1->unk0) {
        case 2:
            uvmd = gGfxUnkPtrs->models[((Unk80263780*)(var_s1->unk10))->modelId];
            uvDobj_80217B4C((Unk80263780*)var_s1->unk10, uvmd, var_s1->unk1);
            break;
        case 3:
            uvDobj_80217E24((Unk80263780*)var_s1->unk10, gGfxUnkPtrs->models[((Unk80263780*)(var_s1->unk10))->modelId], var_s1->unk1, var_s1->unk8,
                            var_s1->unkC);
            break;
        case 1:
            uvGfxStatePush();
            uvGfxSetFlags(GFX_STATE_XLU | GFX_STATE_AA | GFX_STATE_ZBUFFER | GFX_STATE_GOURAUD | GFX_STATE_TEXTURE_NONE);
            uvGfxClearFlags(GFX_STATE_FOG | GFX_STATE_10000000 | GFX_STATE_LIGHTING | GFX_STATE_DECAL | GFX_STATE_CULL_BACK | GFX_STATE_40000);
            _uvFxDraw((UnkFxStruct*)var_s1->unk10 - D_8028B400, arg0);
            uvGfxStatePop();
            break;
        case 4:
            uvmd = gGfxUnkPtrs->models[((UnkSobjDraw*)(var_s1->unk10))->modelId];
            uvGfx_802236CC(var_s1->unk18);
            if (uvmd->lodTable[var_s1->unk1].billboard != FALSE) {
                uvSobj_8022CC28((UnkSobjDraw*)var_s1->unk10, uvmd, var_s1->unk1, var_s1->unk8, var_s1->unkC);
            } else {
                uvSobj_8022C8D0((UnkSobjDraw*)var_s1->unk10, uvmd, var_s1->unk1, var_s1->unk18);
            }
            uvGfxMtxViewPop();
            break;
        }
    }
}
