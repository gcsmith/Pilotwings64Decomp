#include "common.h"
#include "code_61A60.h"
#include "code_66F70.h"
#include "code_7FE00.h"
#include "game.h"
#include "splash.h"
#include "kernel/code_8170.h"
#include <uv_fx.h>
#include <uv_matrix.h>
#include <uv_model.h>

typedef struct Unk8034F390 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    struct Unk8034F390* next;
} Unk8034F390;

Unk8034F390 D_803688E0[20];
f32 D_80368B10;
f32 D_80368B14;
f32 D_80368B18;

Unk8034F390* D_8034F390 = NULL;

// forward declarations
void func_802F8C40(Unk8034F390*);
void func_802F9104(Unk8034F390*);
void func_802F9150(Unk8034F390*);
void func_802F9364(Unk8034F390*);
void func_802F9540(Unk8034F390*);

void func_802F88D0(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_803688E0) - 1; i++) {
        D_803688E0[i].unk0 = -1;
        D_803688E0[i].next = &D_803688E0[i + 1];
    }

    D_803688E0[i].unk0 = -1;
    D_803688E0[i].next = D_803688E0;
    D_8034F390 = D_803688E0;
}

void func_802F89A0(Camera* camera) {
    s32 i;

    D_80368B10 = camera->unk108.m[1][0];
    D_80368B14 = camera->unk108.m[1][1];
    D_80368B18 = camera->unk108.m[1][2];
    D_8034F390 = D_803688E0;
    for (i = 0; i < ARRAY_COUNT(D_803688E0); i++) {
        if (D_8034F390->unk0 != -1) {
            switch (D_8034F390->unk4) {
            case 0:
                func_802F8C40(D_8034F390);
                break;
            case 2:
                func_802F9150(D_8034F390);
                break;
            case 3:
                func_802F9364(D_8034F390);
                break;
            case 4:
                func_802F9104(D_8034F390);
                break;
            case 1:
                func_802F9540(D_8034F390);
                break;
            }
            D_8034F390->unk0 = -1;
        }
        D_8034F390 = D_8034F390->next;
    }
}

void func_802F8AB8(f32 arg0, f32 arg1, f32 arg2, f32 arg3, Vec3F* arg4) {
    Mtx4F sp18;

    uvMat4SetIdentity(&sp18);
    sp18.m[3][0] = arg0;
    sp18.m[3][1] = arg1;
    sp18.m[3][2] = arg2;
    splashAdd(&sp18, arg3);
}

void func_802F8B0C(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    u8 sp80;

    sp80 = func_8021EFF0(8);
    if (sp80 != 0xFF) {
        uvModelGet(sp80, 8);
        // clang-format off
        uvFxProps(
            sp80,
            FX_PROP_3(1.5f * arg3, 1.5f * arg3, arg3),
            FX_PROP_1(3.0f),
            FX_PROP_4(2.0f, 2.0f, 2.0f),
            FX_PROP_10(arg0, arg1, arg2),
            FX_PROP_END
        );
        // clang-format on
    }
}

void func_802F8BF8(s32 arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    D_8034F390->unk0 = arg0;
    D_8034F390->unk4 = arg1;
    D_8034F390->unk8 = arg2;
    D_8034F390->unkC = arg3;
    D_8034F390->unk10 = arg4;
    D_8034F390->unk14 = arg5;
}

void func_802F8C40(Unk8034F390* arg0) {
    f32 sp11C;
    f32 sp118;
    f32 sp114;
    f32 temp_fs1;
    f32 temp_fs2;
    f32 temp_fs3;
    f32 sp104;
    f32 sp100;
    f32 spFC;
    f32 spF8;
    f32 spF4;
    u8 spF3;
    u8 spF2;
    u8 spF1;
    f32 temp_fs0;
    s32 temp_v0;

    switch (arg0->unk0) {
    case 0:
        temp_fs0 = 5.0f;
        break;
    case 3:
        temp_fs0 = 30.0f;
        break;
    case 2:
        temp_fs0 = 20.0f;
        break;
    case 1:
        temp_fs0 = 40.0f;
        break;
    case 4:
        temp_fs0 = 8.0f;
        break;
    }
    sp11C = -D_80368B10 * 0.3f * temp_fs0;
    sp118 = -D_80368B14 * 0.3f * temp_fs0;
    sp114 = -D_80368B18 * 0.3f * temp_fs0;
    sp104 = 0.1f * temp_fs0;
    sp100 = 2.0f * sp104;

    // clang-format off
    temp_fs1 = arg0->unkC, temp_fs2 = arg0->unk10, temp_fs3 = arg0->unk14; temp_fs0 *= 2.0f;
    func_802F9BF8(2, temp_fs1, temp_fs2, temp_fs3, temp_fs0, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
    temp_fs1 += sp11C; temp_fs2 += sp118; temp_fs3 += sp114; temp_fs0 *= 0.6f;
    func_802F9BF8(2, temp_fs1, temp_fs2, temp_fs3, temp_fs0, 0.5f, 0.0f, 1.0f, 0.7f, 0.0f, 1.0f);
    // clang-format on

    if (arg0->unk0 == 1) {
        uvTerraGetColor(D_80362690->terraId, arg0->unk8, &spF3, &spF2, &spF1);
        spFC = spF3 * 0.0039215684f;
        spF8 = spF2 * 0.0039215684f;
        spF4 = spF1 * 0.0039215684f;
        temp_v0 = func_8021EFF0(8);
        if (temp_v0 != 0xFF) {
            uvModelGet(temp_v0, 8);
            // clang-format off
            uvFxProps(
                temp_v0,
                FX_PROP_3(1.5f, 1.5f, 1.5f),
                FX_PROP_1(4.0f),
                FX_PROP_4(2.0f, 2.0f, 2.0f),
                FX_PROP_5(spFC, spF8, spF4, 1.0f),
                FX_PROP_10(temp_fs1, temp_fs2, temp_fs3),
                FX_PROP_END
            );
            // clang-format on
        }
    }
    // clang-format off
    temp_fs1 += sp104 + sp11C; temp_fs2 += sp118 - sp104; temp_fs3 += sp104 + sp114; temp_fs0 *= 0.5f;
    func_802F9BF8(2, temp_fs1, temp_fs2, temp_fs3, temp_fs0, 0.6f, 0.1f, 1.0f, 0.5f, 0.0f, 1.0f);
    temp_fs1 += sp11C - sp100; temp_fs2 += sp118 - sp104; temp_fs3 += sp114; temp_fs0 *= 1.3f;
    func_802F9BF8(2, temp_fs1, temp_fs2, temp_fs3, temp_fs0, 0.5f, 0.3f, 1.0f, 1.0f, 1.0f, 1.0f);
    temp_fs1 += sp104 + sp11C; temp_fs2 += sp100 + sp118; temp_fs3 += sp114; temp_fs0 *= 0.62f;
    func_802F9BF8(2, temp_fs1, temp_fs2, temp_fs3, temp_fs0, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f);
    // clang-format on
}

void func_802F9104(Unk8034F390* arg0) {
    Vec3F sp24;

    sp24.f[0] = 0.0f;
    sp24.f[1] = 0.0f;
    sp24.f[2] = -3.0f;
    func_802F8AB8(arg0->unkC, arg0->unk10, arg0->unk14, 30.0f, &sp24);
}

void func_802F9150(Unk8034F390* arg0) {
    f32 sp94;
    f32 sp90;
    s32 sp8C;

    switch (arg0->unk0) {
    case 0:
        sp94 = 6.0f;
        sp90 = 0.2f;
        break;
    case 3:
        sp94 = 12.0f;
        sp90 = 0.3f;
        break;
    case 2:
        sp94 = 15.0f;
        sp90 = 0.3f;
        break;
    case 1:
        sp94 = 20.0f;
        sp90 = 0.3f;
        break;
    case 4:
        sp94 = 6.0f;
        sp90 = 0.2f;
        break;
    }
    func_802F9BF8(2, arg0->unkC + D_80368B10, arg0->unk10 + D_80368B14, arg0->unk14 + D_80368B18, sp94, sp90, 0.0f, 1.0f, 0.5f, 0.0f, 0.7f);
    if (arg0->unk0 == 1) {
        sp8C = func_8021EFF0(8);
        if (sp8C != 0xFF) {
            sp8C = sp8C;
            uvModelGet(sp8C, 8);
            // clang-format off
            uvFxProps(
                sp8C,
                FX_PROP_3(1.5f, 1.5f, 1.5f),
                FX_PROP_1(4.0f),
                FX_PROP_4(2.0f, 2.0f, 2.0f),
                FX_PROP_10(arg0->unkC, arg0->unk10, arg0->unk14),
                FX_PROP_END
            );
            // clang-format on
        }
    }
}

void func_802F9364(Unk8034F390* arg0) {
    f32 spBC;
    f32 spB8;
    u8 spB0;

    switch (arg0->unk0) {
    case 3:
        spBC = 10.0f;
        spB8 = 0.3f;
        break;
    case 1:
        spBC = 9.0f;
        spB8 = 0.2f;
        break;
    case 2:
        spBC = 8.0f;
        spB8 = 0.2f;
        break;
    case 0:
        spBC = 7.0f;
        spB8 = 0.2f;
        break;
    case 4:
        spBC = 5.0f;
        spB8 = 0.3f;
        break;
    }
    spB0 = func_8021EFF0(2);
    if (spB0 != 0xFF) {
        uvModelGet(spB0, 2);
        // clang-format off
        uvFxProps(
            spB0,
            FX_PROP_3(spBC, spBC, spBC),
            FX_PROP_5(1.0f, 1.0f, 1.0f, 0.8f),
            FX_PROP_6(1.0f, 0.5f, 0.0f, 0.0f),
            FX_PROP_1(spB8),
            FX_PROP_10(arg0->unkC + D_80368B10, arg0->unk10 + D_80368B14, arg0->unk14 + D_80368B18),
            FX_PROP_END
        );
        // clang-format on
    }
}

void func_802F9540(Unk8034F390* arg0) {
    f32 sp3C;
    f32 sp38;

    switch (arg0->unk0) {
    case 0:
        sp3C = 0.0f;
        sp38 = 0.0f;
        break;
    case 3:
        sp3C = 0.0f;
        sp38 = 0.0f;
        break;
    case 2:
        sp3C = 10.0f;
        sp38 = 0.3f;
        break;
    case 1:
        sp3C = 20.0f;
        sp38 = 0.3f;
        break;
    case 4:
        sp3C = 0.0f;
        sp38 = 0.0f;
        break;
    }
    func_802F9BF8(2, arg0->unkC, arg0->unk10, arg0->unk14, sp3C, sp38, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
}

void func_802F9638(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 spCC;
    f32 spC8;
    f32 temp_fs5;
    f32 spC0;
    f32 spBC;
    u8 v0;

    spCC = -D_80368B10 * 0.05f * arg3;
    spC8 = -D_80368B14 * 0.05f * arg3;
    temp_fs5 = -D_80368B18 * 0.05f * arg3;

    spC0 = 0.1f * arg3;
    spBC = spC0 + spC0;
    arg2 = func_802DFA40(arg0, arg1) + (0.25f * arg3);
    arg3 = (arg3 * 2.0f);
    arg0 += spCC;
    arg1 += spC8;
    arg2 += temp_fs5;
    arg3 *= 0.6f;
    func_802F9BF8(2, arg0, arg1, arg2, arg3, 0.5f, 0.0f, 1.0f, 0.7f, 0.0f, 1.0f);
    arg0 += spC0 + spCC;
    arg1 += spC8 - spC0;
    arg2 += (spC0 + temp_fs5);
    arg3 *= 0.5f;
    func_802F9BF8(2, arg0, arg1, arg2, arg3, 0.6f, 0.1f, 1.0f, 0.5f, 0.0f, 1.0f);
    arg0 += (spCC - spBC);
    arg1 += spC8 - spC0;
    arg2 += temp_fs5;
    arg3 *= 1.3f;
    func_802F9BF8(2, arg0, arg1, arg2, arg3, 0.5f, 0.3f, 1.0f, 1.0f, 1.0f, 1.0f);
    arg0 += spC0 + spCC;
    arg1 += (spBC + spC8);
    arg2 += temp_fs5;
    arg3 *= 0.62f;
    func_802F9BF8(2, arg0, arg1, arg2, arg3, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f);
    v0 = func_8021EFF0(8);
    if (v0 != 0xFF) {
        uvModelGet(v0, 8);
        // clang-format off
        uvFxProps(
            v0,
            FX_PROP_3(1.5f * arg3, 1.5f * arg3, arg3),
            FX_PROP_1(4.0f),
            FX_PROP_4(2.0f, 2.0f, 2.0f),
            FX_PROP_10(arg0, arg1, arg2),
            FX_PROP_END
        );
        // clang-format on
    }
}

void func_802F996C(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 sp84;
    f32 temp_fs5;
    f32 sp7C;
    f32 sp78;
    f32 sp74;

    sp84 = -D_80368B10 * 0.1f * arg3;
    temp_fs5 = -D_80368B14 * 0.1f * arg3;
    sp7C = -D_80368B18 * 0.1f * arg3;
    sp78 = 0.05f * arg3;
    sp74 = 2.0f * sp78;

    // clang-format off
    arg0 += sp78 + sp84; arg1 += temp_fs5 - sp78; arg2 += sp78 + sp7C; arg3 *= 0.5f;
    func_802F9BF8(2, arg0, arg1, arg2, arg3, 0.3f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f);
    arg0 += sp78 + sp84; arg1 += -sp78 + temp_fs5; arg2 += sp78 + sp7C; arg3 *= 0.5f;
    func_802F9BF8(2, arg0, arg1, arg2, arg3, 0.6f, 0.2f, 1.0f, 0.5f, 0.0f, 1.0f);
    arg0 += sp84 - sp74; arg1 += temp_fs5; arg2 += sp7C; arg3 *= 1.3f;
    func_802F9BF8(2, arg0, arg1, arg2, arg3, 0.3f, 0.4f, 0.7f, 0.3f, 0.0f, 1.0f);
    arg0 += sp78 + sp84; arg1 += sp74 + temp_fs5; arg2 += -sp78 + sp7C; arg3 *= 0.62f;
    func_802F9BF8(2, arg0, arg1, arg2, arg3, 0.3f, 0.6f, 1.0f, 0.2f, 0.0f, 1.0f);
    // clang-format on
}

u8 func_802F9BF8(u8 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 arg10) {
    u8 spCF;

    spCF = func_8021EFF0(arg0);
    if (spCF != 0xFF) {
        uvModelGet(spCF, arg0);
        // clang-format off
        uvFxProps(
            spCF,
            FX_PROP_3(arg4, arg4, arg4),
            FX_PROP_1(arg5),
            FX_PROP_10(arg1, arg2, arg3),
            FX_PROP_2(arg6),
            FX_PROP_5(arg7, arg8, arg9, arg10),
            FX_PROP_6(0.0f, 0.0f, 0.0f, 0.0f),
            FX_PROP_END
        );
        // clang-format on
    }

    return spCF;
}

s32 func_802F9D28(u8 arg0, u8 arg1, f32 x1, f32 y1, f32 z2, f32 x2, f32 y2, f32 z1, f32* ox, f32* oy, f32* oz, s32* oSurfaceId) {
    Vec3F sp1E4;
    Vec3F sp1D8;
    Unk802D3658_Unk1224 sp94;
    Unk802D3658_Unk1228* temp_v0;
    f32 var_fs0;
    s32 var_s0;
    s32 i;
    s32 sp80;
    f32 sp7C;
    Vec3F sp70;

    var_s0 = -1;
    sp1E4.f[0] = x1;
    sp1D8.f[0] = x2;
    sp1E4.f[1] = y1;
    sp1D8.f[1] = y2;
    sp1D8.f[2] = z1;
    sp1E4.f[2] = z2;
    func_802DB224(&sp94, 0xFFU, arg0, arg1, &sp1D8, &sp1E4);
    if (sp94.unk0 == 0) {
        return -1;
    }
    var_fs0 = 1.0f;
    for (i = 0; i < sp94.unk0; i++) {
        temp_v0 = &sp94.unk4[i];
        if (sp94.unk4[i].unk18 <= var_fs0) {
            var_fs0 = temp_v0->unk18;
            *ox = temp_v0->unkC.x;
            *oy = temp_v0->unkC.y;
            *oz = temp_v0->unkC.z;
            *oSurfaceId = temp_v0->surfaceId;
            switch (temp_v0->collisionType) {
            case 1:
                if (func_802DC8E4(temp_v0->surfaceId) != 0) {
                    var_s0 = 4;
                } else {
                    var_s0 = 0;
                }
                break;
            case 2:
                var_s0 = 3;
                break;
            case 4:
                var_s0 = 4;
                if ((func_802DFB48(1, *ox, *oy, *oz, &sp80, &sp7C, &sp70) != 0) && ((sp7C - *oz) > 0.1f)) {
                    *oz = sp7C;
                    var_s0 = 0;
                }
                break;
            case 8:
                var_s0 = 2;
                break;
            default:
                _uvDebugPrintf("hit : unknown collision type [%d]\n", temp_v0->collisionType);
                break;
            }
        }
    }
    return var_s0;
}
