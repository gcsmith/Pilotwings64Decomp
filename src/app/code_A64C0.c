#include "common.h"
#include "snd.h"
#include <uv_memory.h>
#include <uv_audio.h>
#include <uv_fx.h>
#include <uv_model.h>
#include <uv_dobj.h>
#include <uv_matrix.h>

typedef struct {
    u8 unk0;
    u8 unk1;
    u16 pad2;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    u8 unk1C;
    u8 unk1D;
    u16 pad1E;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    f32 unk40;
    f32 unk44;
} Unk8036D230; // size = 0x48

typedef struct {
    u8 unk0;
    u8 unk1;
    u16 pad2;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    u8 unk1C;
    u8 unk1D;
    u16 pad1E;
} Unk8036D248; // size = 0x20

typedef struct {
    s32 unk0;
    s32 unk4;
    f32 unk8;
    f32 unkC;
} Unk8036D260; // size = 0x10

Unk8036D230* D_8036D230[6];
Unk8036D248* D_8036D248[6];
Unk8036D260* D_8036D260;

void func_8031EF90(s32 arg0) {
    Unk8036D230* temp_v0_2;
    Unk8036D248* temp_v0_5;
    s32 i;

    D_8036D260 = (Unk8036D260*)_uvMemAllocAlign8(sizeof(Unk8036D260));
    D_8036D260->unk0 = 0xFF;
    D_8036D260->unk4 = 0xFF;
    D_8036D260->unk8 = 0.0f;
    D_8036D260->unkC = 0.0f;
    switch (arg0) {
    case 2:
        D_8036D260->unk0 = uvEmitterLookup();
        D_8036D260->unk4 = uvEmitterLookup();
        uvEmitterFromModel(D_8036D260->unk0, 0x42U);
        uvEmitterFromModel(D_8036D260->unk4, 0x1FU);
        uvEmitterSetVol(D_8036D260->unk0, 1.0f);
        uvEmitterSetVol(D_8036D260->unk4, 1.0f);
        uvEmitterSetPitch(D_8036D260->unk0, 1.0f);
        uvEmitterSetPitch(D_8036D260->unk4, 0.5f);
        // clang-format off
        uvEmitterProps(D_8036D260->unk0,
            EMITTER_PROP_NEAR(0.0f),
            EMITTER_PROP_FAR(250.0f),
            EMITTER_PROP_ATTR(0),
            EMITTER_PROP_END
        );
        uvEmitterProps(D_8036D260->unk4,
            EMITTER_PROP_NEAR(0.0f),
            EMITTER_PROP_FAR(250.0f),
            EMITTER_PROP_ATTR(0),
            EMITTER_PROP_END
        );
        // clang-format on
        for (i = 0; i < ARRAY_COUNT(D_8036D230); i++) {
            temp_v0_2 = D_8036D230[i] = (Unk8036D230*)_uvMemAllocAlign8(sizeof(Unk8036D230));
            temp_v0_2->unk0 = uvFx_8021EFF0(3);
            uvModelGet(temp_v0_2->unk0, 3);
            temp_v0_2->unk1 = uvFx_8021EFF0(3);
            uvModelGet(temp_v0_2->unk1, 3);
            switch (i) {
            case 0:
                temp_v0_2->unkC = 0.208f;
                temp_v0_2->unk8 = 0.208f;
                temp_v0_2->unk18 = 0.208f;
                temp_v0_2->unk14 = 0.208f;
                temp_v0_2->unk4 = 0.522f;
                temp_v0_2->unk10 = 0.522f;
                temp_v0_2->unk20 = -0.03f;
                temp_v0_2->unk24 = -0.095f;
                temp_v0_2->unk28 = 1.6f;
                temp_v0_2->unk2C = 0.009f;
                temp_v0_2->unk30 = -0.67f;
                temp_v0_2->unk34 = 0.44f;
                temp_v0_2->unk1C = 1;
                temp_v0_2->unk1D = 2;
                temp_v0_2->unk38 = 3.866f;
                temp_v0_2->unk3C = 0.0959931f;
                temp_v0_2->unk40 = 1.038f;
                temp_v0_2->unk44 = 1.5707961f;
                break;
            case 1:
                temp_v0_2->unk4 = 0.522f;
                temp_v0_2->unkC = 0.208f;
                temp_v0_2->unk8 = 0.208f;
                temp_v0_2->unk10 = 0.522f;
                temp_v0_2->unk18 = 0.208f;
                temp_v0_2->unk14 = 0.208f;
                temp_v0_2->unk20 = -0.031f;
                temp_v0_2->unk24 = -0.021f;
                temp_v0_2->unk28 = 1.707f;
                temp_v0_2->unk2C = 0.005f;
                temp_v0_2->unk30 = -0.906f;
                temp_v0_2->unk34 = 0.459f;
                temp_v0_2->unk1C = 1;
                temp_v0_2->unk1D = 2;
                temp_v0_2->unk38 = 3.866f;
                temp_v0_2->unk3C = 0.0959931f;
                temp_v0_2->unk40 = 1.038f;
                temp_v0_2->unk44 = 1.5707961f;
                break;
            case 2:
                temp_v0_2->unk4 = 0.47f;
                temp_v0_2->unk8 = 0.412f;
                temp_v0_2->unkC = 0.188f;
                temp_v0_2->unk18 = 0.6f;
                temp_v0_2->unk14 = 0.6f;
                temp_v0_2->unk10 = 0.6f;
                temp_v0_2->unk20 = -0.02f;
                temp_v0_2->unk24 = -0.146f;
                temp_v0_2->unk28 = 1.65f;
                temp_v0_2->unk2C = 0.011f;
                temp_v0_2->unk30 = -0.733f;
                temp_v0_2->unk34 = 0.438f;
                temp_v0_2->unk1C = 1;
                temp_v0_2->unk1D = 2;
                temp_v0_2->unk38 = 3.866f;
                temp_v0_2->unk3C = 0.0959931f;
                temp_v0_2->unk40 = 1.038f;
                temp_v0_2->unk44 = 1.5707961f;
                break;
            case 3:
                temp_v0_2->unk4 = 0.6f;
                temp_v0_2->unk8 = 0.6f;
                temp_v0_2->unkC = 0.6f;
                temp_v0_2->unk10 = 0.6f;
                temp_v0_2->unk14 = 0.6f;
                temp_v0_2->unk18 = 0.6f;
                temp_v0_2->unk20 = -0.031f;
                temp_v0_2->unk24 = -0.096f;
                temp_v0_2->unk28 = 1.62f;
                temp_v0_2->unk2C = 0.009f;
                temp_v0_2->unk30 = -0.673f;
                temp_v0_2->unk34 = 0.443f;
                temp_v0_2->unk1C = 1;
                temp_v0_2->unk1D = 2;
                temp_v0_2->unk38 = 3.866f;
                temp_v0_2->unk3C = 0.0959931f;
                temp_v0_2->unk40 = 1.038f;
                temp_v0_2->unk44 = 1.5707961f;
                break;
            case 4:
                temp_v0_2->unk4 = 0.102f;
                temp_v0_2->unk8 = 0.086f;
                temp_v0_2->unkC = 0.22f;
                temp_v0_2->unk18 = 0.6f;
                temp_v0_2->unk14 = 0.6f;
                temp_v0_2->unk10 = 0.6f;
                temp_v0_2->unk20 = -0.031f;
                temp_v0_2->unk24 = -0.021f;
                temp_v0_2->unk28 = 1.707f;
                temp_v0_2->unk2C = 0.028f;
                temp_v0_2->unk30 = -0.892f;
                temp_v0_2->unk34 = 0.452f;
                temp_v0_2->unk1C = 1;
                temp_v0_2->unk1D = 2;
                temp_v0_2->unk38 = 3.866f;
                temp_v0_2->unk3C = 0.0959931f;
                temp_v0_2->unk40 = 1.038f;
                temp_v0_2->unk44 = 1.5707961f;
                break;
            case 5:
                temp_v0_2->unk4 = 0.102f;
                temp_v0_2->unk8 = 0.086f;
                temp_v0_2->unkC = 0.22f;
                temp_v0_2->unk18 = 0.6f;
                temp_v0_2->unk14 = 0.6f;
                temp_v0_2->unk10 = 0.6f;
                temp_v0_2->unk20 = -0.031f;
                temp_v0_2->unk24 = -0.146f;
                temp_v0_2->unk28 = 1.676f;
                temp_v0_2->unk2C = 0.011f;
                temp_v0_2->unk30 = -0.74f;
                temp_v0_2->unk34 = 0.442f;
                temp_v0_2->unk1C = 1;
                temp_v0_2->unk1D = 2;
                temp_v0_2->unk38 = 3.866f;
                temp_v0_2->unk3C = 0.0959931f;
                temp_v0_2->unk40 = 1.038f;
                temp_v0_2->unk44 = 1.5707961f;
                break;
            }
            // clang-format off
            uvFxProps(
                temp_v0_2->unk0,
                FX_PROP_5(temp_v0_2->unk4, temp_v0_2->unk8, temp_v0_2->unkC, 0.6f),
                FX_PROP_3(temp_v0_2->unk38, temp_v0_2->unk38, temp_v0_2->unk38),
                FX_PROP_END
            );
            uvFxProps(
                temp_v0_2->unk1,
                FX_PROP_5(temp_v0_2->unk10, temp_v0_2->unk14, temp_v0_2->unk18, 0.6f),
                FX_PROP_3(temp_v0_2->unk40, temp_v0_2->unk40, temp_v0_2->unk40),
                FX_PROP_END
            );
            // clang-format on
        }
        uvEmitterTrigger(D_8036D260->unk0);
        uvEmitterTrigger(D_8036D260->unk4);
        break;

    case 1:
        D_8036D260->unk0 = uvEmitterLookup();
        uvEmitterFromModel(D_8036D260->unk0, 0x1EU);
        D_8036D260->unk8 = 0.5f;
        uvEmitterSetVol(D_8036D260->unk0, 1.0f);
        uvEmitterSetPitch(D_8036D260->unk0, 1.0f);
        // clang-format off
        uvEmitterProps(D_8036D260->unk0,
            EMITTER_PROP_NEAR(0.0f),
            EMITTER_PROP_FAR(250.0f),
            EMITTER_PROP_ATTR(0),
            EMITTER_PROP_END
        );
        // clang-format on
        for (i = 0; i < ARRAY_COUNT(D_8036D248); i++) {
            temp_v0_5 = D_8036D248[i] = (Unk8036D248*)_uvMemAllocAlign8(sizeof(Unk8036D248));
            temp_v0_5->unk0 = uvFx_8021EFF0(2);
            uvModelGet(temp_v0_5->unk0, 2);
            temp_v0_5->unk1 = uvFx_8021EFF0(2);
            uvModelGet(temp_v0_5->unk1, 2);
            // clang-format off
            uvFxProps(
                temp_v0_5->unk0,
                FX_PROP_3(1.0f, 1.0f, 1.0f),
                FX_PROP_4(1.0f, 1.0f, 1.0f),
                FX_PROP_1(1e+20),
                FX_PROP_END
            );
            uvFxProps(
                temp_v0_5->unk1,
                FX_PROP_3(1.0f, 1.0f, 1.0f),
                FX_PROP_4(1.0f, 1.0f, 1.0f),
                FX_PROP_1(1e+20),
                FX_PROP_END
            );
            // clang-format on
            uvFxProps(temp_v0_5->unk0, FX_PROP_5(1.0f, 1.0f, 0.0f, 1.0f), FX_PROP_END);
            uvFxProps(temp_v0_5->unk1, FX_PROP_5(1.0f, 1.0f, 0.0f, 1.0f), FX_PROP_END);
            uvFxProps(temp_v0_5->unk0, FX_PROP_6(0.0f, 0.0f, 0.0f, 0.0f), FX_PROP_END);
            uvFxProps(temp_v0_5->unk1, FX_PROP_6(0.0f, 0.0f, 0.0f, 0.0f), FX_PROP_END);
            switch (i) {
            case 0:
                temp_v0_5->unk1C = 0xA;
                temp_v0_5->unk1D = 8;
                temp_v0_5->unk4 = 0.015f;
                temp_v0_5->unkC = -0.25f;
                temp_v0_5->unk8 = 0.006f;
                temp_v0_5->unk10 = -0.028f;
                temp_v0_5->unk18 = -0.25f;
                temp_v0_5->unk14 = 0.006f;
                break;
            case 1:
                temp_v0_5->unk1C = 0xA;
                temp_v0_5->unk1D = 8;
                temp_v0_5->unk4 = 0.041f;
                temp_v0_5->unk8 = 0.008f;
                temp_v0_5->unkC = -0.358f;
                temp_v0_5->unk10 = -0.04f;
                temp_v0_5->unk14 = 0.008f;
                temp_v0_5->unk18 = -0.358f;
                break;
            case 2:
                temp_v0_5->unk1C = 0xA;
                temp_v0_5->unk1D = 8;
                temp_v0_5->unk4 = 0.046f;
                temp_v0_5->unk8 = 0.01f;
                temp_v0_5->unkC = -0.408f;
                temp_v0_5->unk10 = -0.046f;
                temp_v0_5->unk14 = 0.01f;
                temp_v0_5->unk18 = -0.408f;
                break;
            case 3:
                temp_v0_5->unk1C = 0xA;
                temp_v0_5->unk1D = 8;
                temp_v0_5->unk4 = 0.027f;
                temp_v0_5->unk8 = 0.006f;
                temp_v0_5->unkC = -0.239f;
                temp_v0_5->unk10 = -0.027f;
                temp_v0_5->unk14 = 0.006f;
                temp_v0_5->unk18 = -0.239f;
                break;
            case 4:
                temp_v0_5->unk1C = 0xA;
                temp_v0_5->unk1D = 8;
                temp_v0_5->unk4 = 0.038f;
                temp_v0_5->unk8 = 0.008f;
                temp_v0_5->unkC = -0.332f;
                temp_v0_5->unk10 = -0.037f;
                temp_v0_5->unk14 = 0.008f;
                temp_v0_5->unk18 = -0.332f;
                break;
            case 5:
                temp_v0_5->unk1C = 0xA;
                temp_v0_5->unk1D = 8;
                temp_v0_5->unk4 = 0.042f;
                temp_v0_5->unk8 = 0.022f;
                temp_v0_5->unkC = -0.31f;
                temp_v0_5->unk10 = -0.041f;
                temp_v0_5->unk14 = 0.022f;
                temp_v0_5->unk18 = -0.31f;
                break;
            }
        }
        uvEmitterTrigger(D_8036D260->unk0);
        break;
    }
}

void func_8031FA0C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, Mtx4F* arg4, Mtx4F* arg5) {
    static Mtx4F D_8036D268;
    static f32 D_8036D2A8;
    Mtx4F sp48;
    f32 sp44;
    Unk8036D230* temp_s0;
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;
    Unk8036D248* sp30;

    switch (arg0) {
    case 2:
        temp_s0 = D_8036D230[arg2];
        if (temp_s0 == NULL) {
            return;
        }

        uvMat4Copy(&sp48, arg4);
        uvMat4LocalTranslate(&sp48, temp_s0->unk20, temp_s0->unk24, temp_s0->unk28);
        uvMat4RotateAxis(&sp48, temp_s0->unk3C, 'x');
        uvFx_8021A4D8(temp_s0->unk0, &sp48);
        uvMat4Copy(&sp48, arg4);
        uvMat4LocalTranslate(&sp48, temp_s0->unk2C, temp_s0->unk30, temp_s0->unk34);
        uvMat4RotateAxis(&sp48, temp_s0->unk44, 'x');
        uvFx_8021A4D8(temp_s0->unk1, &sp48);
        uvDobjProps(arg3, 5, temp_s0->unk1C, 0);
        break;

    case 1:
        sp30 = D_8036D248[arg2];
        if (sp30 == NULL) {
            return;
        }

        uvDobjGetPosm(arg3, sp30->unk1C, &sp48);
        uvMat4MulBA(&sp48, arg4, &sp48);
        uvMat4LocalTranslate(&sp48, sp30->unk4, sp30->unk8, sp30->unkC);
        uvFx_8021A4D8(sp30->unk0, &sp48);
        uvDobjGetPosm(arg3, sp30->unk1D, &sp48);
        uvMat4MulBA(&sp48, arg4, &sp48);
        uvMat4LocalTranslate(&sp48, sp30->unk10, sp30->unk14, sp30->unk18);
        uvFx_8021A4D8(sp30->unk1, &sp48);
        break;
    }

    if ((D_8036D260->unk0 == 0xFF) && (D_8036D260->unk4 == 0xFF)) {
        return;
    }

    if (arg1 == 0) {
        uvMat4Copy(&D_8036D268, arg4);
        temp_fv0 = arg5->m[3][0] - arg4->m[3][0];
        temp_fv1 = arg5->m[3][1] - arg4->m[3][1];
        temp_fa0 = arg5->m[3][2] - arg4->m[3][2];
        D_8036D2A8 = SQ(temp_fv0) + SQ(temp_fv1) + SQ(temp_fa0);
    } else {
        temp_fv0 = arg4->m[3][0] - arg5->m[3][0];
        temp_fv1 = arg4->m[3][1] - arg5->m[3][1];
        temp_fa0 = arg4->m[3][2] - arg5->m[3][2];
        if ((SQ(temp_fv0) + SQ(temp_fv1) + SQ(temp_fa0)) < D_8036D2A8) {
            uvMat4Copy(&D_8036D268, arg4);
            D_8036D2A8 = SQ(temp_fv0) + SQ(temp_fv1) + SQ(temp_fa0);
        }
    }
    if (arg1 == 5) {
        sp44 = 1.0f - (D_8036D2A8 / 800.0f);
        if (sp44 < 0.5f) {
            sp44 = 0.5f;
        }
        if (D_8036D260->unk0 != 0xFF) {
            uvEmitterSetMatrix(D_8036D260->unk0, &D_8036D268);
            uvEmitterSetVol(D_8036D260->unk0, sp44);
            uvEmitterSetPitch(D_8036D260->unk0, D_8036D260->unk8 + sp44);
        }
        if (D_8036D260->unk4 != 0xFF) {
            uvEmitterSetMatrix(D_8036D260->unk4, &D_8036D268);
            uvEmitterSetVol(D_8036D260->unk4, sp44);
            uvEmitterSetPitch(D_8036D260->unk4, D_8036D260->unkC + sp44);
        }
    }
}

void func_8031FD70(f32 arg0) {
    if (D_8036D260 == NULL) {
        return;
    }

    if (arg0 > 1.0f) {
        arg0 = 1.0f;
    } else if (arg0 <= 0.0f) {
        arg0 = 0.1f;
    }

    if (D_8036D260->unk0 != 0xFF) {
        uvEmitterSetVol(D_8036D260->unk0, arg0);
    }

    if (D_8036D260->unk4 != 0xFF) {
        uvEmitterSetVol(D_8036D260->unk4, arg0);
    }
}

void func_8031FE18(s32 arg0) {
    Unk8036D230* temp_s0;
    Unk8036D248* temp_s0_2;
    s32 i;

    if (D_8036D260 == NULL) {
        return;
    }

    func_8033F8CC(D_8036D260->unk0);
    func_8033F8CC(D_8036D260->unk4);
    switch (arg0) {
    case 2:
        for (i = 0; i < ARRAY_COUNT(D_8036D230); i++) {
            temp_s0 = D_8036D230[i];
            if (temp_s0 != NULL) {
                uvModelGet(temp_s0->unk0, 0xFF);
                temp_s0->unk0 = 0xFF;
                uvModelGet(temp_s0->unk1, 0xFF);
                temp_s0->unk1 = 0xFF;
            }
        }
        break;
    case 1:
        for (i = 0; i < ARRAY_COUNT(D_8036D248); i++) {
            temp_s0_2 = D_8036D248[i];
            if (temp_s0_2 != NULL) {
                uvModelGet(temp_s0_2->unk0, 0xFF);
                uvModelGet(temp_s0_2->unk1, 0xFF);
                temp_s0_2->unk0 = 0xFF;
                temp_s0_2->unk1 = 0xFF;
            }
        }
        break;
    }
    D_8036D260 = NULL;
}

