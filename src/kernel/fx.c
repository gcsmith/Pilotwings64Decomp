#include "common.h"
#include <uv_fx.h>
#include <uv_graphics.h>
#include <uv_math.h>
#include <uv_vector.h>
#include <libc/stdarg.h>

// clang-format off
static u16 D_80248EA0[] = {
    0x0000, 0x0000, 0x0064, 0x0000, 0x0047, 0xFFB9, 0x0000, 0xFF9C,
    0xFFB9, 0xFFB9, 0xFF9C, 0x0000, 0xFFB9, 0x0047, 0x0000, 0x0064,
    0x0047, 0x0047,
};

static u16 D_80248EC4[] = {
    0x0064, 0x0000, 0xFF9C, 0x0000, 0x0064, 0x0000, 0x0064, 0x00C8,
    0xFF9C, 0x00C8,
};

static u16 D_80248ED8[] = {
    0x0000, 0x0000,
};

static u16 D_80248EDC[] = {
    0x0064, 0x0000, 0x005C, 0xFFDA, 0x0047, 0xFFB9, 0x0026, 0xFFA4,
    0x0000, 0xFF9C, 0xFFDA, 0xFFA4, 0xFFB9, 0xFFB9, 0xFFA4, 0xFFDA,
    0xFF9C, 0x0000, 0xFFA4, 0x0026, 0xFFB9, 0x0047, 0xFFDA, 0x005C,
    0x0000, 0x0064, 0x0026, 0x005C, 0x0047, 0x0047, 0x005C, 0x0026,
};

static u16 D_80248F1C[] = {
    0x0000, 0x0000, 0x0064, 0x0000, 0x0000, 0x0064, 0xFF9C, 0x0000,
    0x0000, 0xFF9C,
};

static u16 D_80248F30[] = {
    0x0064, 0x0000,
};

static u32 D_80248F34[] = {
    0xFFDF0000, 0x00000000, 0xFFDF000E, 0x00000000, 0xFFDF001D, 0x00000000,
    0xFFDF002B, 0x00000000, 0xFFDF0039, 0x00000000, 0xFFDF0047, 0x00000000,
    0xFFDF0056, 0x00000000, 0xFFDF0064, 0x00000000, 0xFFE70000, 0x00000000,
    0xFFE7000E, 0x00000000, 0xFFE7001D, 0x3E99999A, 0xFFE7002B, 0x00000000,
    0xFFE70039, 0x3E99999A, 0xFFE70047, 0x3ECCCCCD, 0xFFE70056, 0x00000000,
    0xFFE70064, 0x00000000, 0xFFEF0000, 0x00000000, 0xFFEF000E, 0x3E99999A,
    0xFFEF001D, 0x3ECCCCCD, 0xFFEF002B, 0x3F19999A, 0xFFEF0039, 0x3F4CCCCD,
    0xFFEF0047, 0x3F19999A, 0xFFEF0056, 0x3F000000, 0xFFEF0064, 0x00000000,
    0xFFF80000, 0x3F666666, 0xFFF8000E, 0x3F666666, 0xFFF8001D, 0x3F333333,
    0xFFF8002B, 0x3F4CCCCD, 0xFFF80039, 0x3F333333, 0xFFF80047, 0x3F333333,
    0xFFF80056, 0x3F19999A, 0xFFF80064, 0x00000000, 0x00000000, 0x3F666666,
    0x0000000E, 0x3F4CCCCD, 0x0000001D, 0x3F4CCCCD, 0x0000002B, 0x3F666666,
    0x00000039, 0x3F4CCCCD, 0x00000047, 0x3F4CCCCD, 0x00000056, 0x3E4CCCCD,
    0x00000064, 0x00000000, 0x00080000, 0x00000000, 0x0008000E, 0x3E4CCCCD,
    0x0008001D, 0x3F666666, 0x0008002B, 0x3F333333, 0x00080039, 0x3F000000,
    0x00080047, 0x3F19999A, 0x00080056, 0x00000000, 0x00080064, 0x00000000,
    0x00110000, 0x00000000, 0x0011000E, 0x00000000, 0x0011001D, 0x3ECCCCCD,
    0x0011002B, 0x3E4CCCCD, 0x00110039, 0x3DCCCCCD, 0x00110047, 0x3F000000,
    0x00110056, 0x3DCCCCCD, 0x00110064, 0x00000000, 0x00190000, 0x00000000,
    0x0019000E, 0x00000000, 0x0019001D, 0x00000000, 0x0019002B, 0x00000000,
    0x00190039, 0x00000000, 0x00190047, 0x00000000, 0x00190056, 0x00000000,
    0x00190064, 0x00000000,
};

static u32 D_80249134[] = {
    0x00000000, 0x00000000, 0x00000000,
};
// clang-format on

typedef struct UnkModelTrail_Unk0 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
} UnkModelTrail_Unk0; // size = 0x18

typedef struct UnkModelTrail {
    UnkModelTrail_Unk0 unk0[10];
    Vec3F unkF0[10];
    f32 unk168[10];
    Vec3F unk190;
    u8 pad19C[0x18];
    Vec3F unk1B4;
    u8 pad1C0[0x4];
    Vec3F unk1C4;
    f32 unk1D0;
    f32 unk1D4;
    Vec3F unk1D8;
    s16 unk1E4;
    s16 unk1E6;
    s32 unk1E8;
    u8 unk1EC;
} UnkModelTrail; // size = 0x1F0
extern UnkModelTrail D_8028AC40[];

typedef struct UnkModelDebrisStructure {
    Vec3F unk0[20];
    Vec3F unkF0[20];
    f32 unk1E0[20];
    f32 unk230[20];
    f32 unk280[20];
    u8 unk2D0[20];
    u8 unk2E4;
} UnkModelDebrisStructure; // size = 0x2E8
extern UnkModelDebrisStructure D_8028A0A0[];

#define FLT_MAX 340282346638528859811704183484516925440.0f

void func_8021A038(UnkModelTrail* arg0);
s32 func_8021A334(f32 arg0, f32 arg1, f32 arg2, f32 arg3, u16 arg4);
void func_8021BE28(u16 arg0, Mtx4F* arg1);

void func_80219FD0(void) {
    s32 i;

    for (i = 0; i < 120; i++) {
        D_8028B400[i].unk4 = 0;
    }

    for (i = 0; i < 4; i++) {
        func_8021A038(&D_8028AC40[i]);
    }
}

void func_8021A038(UnkModelTrail* arg0) {
    s32 i;

    arg0->unk1E8 = 0;
    arg0->unk1E6 = 0;
    arg0->unk1EC = 0;
    arg0->unk1B4.x = arg0->unk1B4.y = arg0->unk1B4.z = 0.0f;
    arg0->unk1D0 = 17.0f / 6.0f;
    arg0->unk1E4 = 10;

    for (i = 0; i < 10; i++) {
        arg0->unkF0[i].x = 0.0f;
        arg0->unkF0[i].y = 0.0f;
        arg0->unkF0[i].z = 0.0f;
    }
}

void func_8021A0CC(UnkModelDebrisStructure* arg0) {
    s32 i;

    for (i = 0; i < 20; i++) {
        arg0->unk1E0[i] = ((2.0f * uvRandF_LCG()) - 1.0f) * 6.2831855f;
        arg0->unk280[i] = (uvRandF_LCG() * 3.2f) + 0.4f;
        arg0->unk230[i] = (uvRandF_LCG() * 5.8f) + 0.1f;
        arg0->unk0[i].x = (uvRandF_LCG() * 3.0f) - 1.5f;
        arg0->unk0[i].y = (uvRandF_LCG() * 3.0f) - 1.5f;
        arg0->unk0[i].z = uvRandF_LCG() - 0.5f;
        arg0->unkF0[i].x = (uvRandF_LCG() * 3.4f) - 1.7f;
        arg0->unkF0[i].y = (uvRandF_LCG() * 3.4f) - 1.7f;
        arg0->unkF0[i].z = (uvRandF_LCG() * 5.2f) + 0.4f;
        arg0->unkF0[i].x *= 20.0f;
        arg0->unkF0[i].y *= 20.0f;
        arg0->unkF0[i].z *= 20.0f;
        arg0->unk230[i] *= 20.0f;
        arg0->unk2D0[i] = 1;
    }
}

void func_8021A298(void) {
    s32 i;

    // clang-format off
    for (i = 0; i < 120; i++) { D_8028B400[i].unk5 = 0; }
    // clang-format on
}

s32 func_8021A2C8(s32 arg0) {
    if (D_8028B400[arg0].unk4 != 0) {
        return 0;
    }
    return 1;
}

void func_8021A304(f32 arg0, f32 arg1, f32 arg2, u16 arg3) {
    func_8021A334(arg0, arg1, arg2, 0.0f, arg3);
}

s32 func_8021A334(f32 arg0, f32 arg1, f32 arg2, f32 arg3, u16 arg4) {
    f32 temp_fa1;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 temp_fv0;
    s32 var_v1;
    UnkFxStruct* var_v0;
    s32 i;

    for (i = 0; i < 120; i++) {
        var_v0 = &D_8028B400[i];
        if ((var_v0->unk4 == 0) || !(var_v0->unk5C & arg4)) {
            continue;
        }
        temp_fv0 = SQ(var_v0->unk14 + arg3);
        temp_fa1 = SQ(var_v0->unk68.m[3][0] - arg0);
        if (temp_fv0 < temp_fa1) {
            continue;
        }
        temp_ft4 = SQ(var_v0->unk68.m[3][1] - arg1);
        if (temp_fv0 < temp_ft4) {
            continue;
        }

        temp_ft5 = SQ(var_v0->unk68.m[3][2] - arg2);
        if (temp_fv0 < temp_ft5) {
            continue;
        }
    
        if ((temp_fa1 + temp_ft4 + temp_ft5) <= temp_fv0) {
            return i;
        }
    }

    return 0xFF;
}

void func_8021A4D8(s32 arg0, Mtx4F* arg1) {
    UnkFxStruct* temp_v0;

    if (arg0 == 0xFF) {
        return;
    }

    if (D_8028B400[arg0].unk1 == 4) {
        func_8021BE28(arg0, arg1);
    } else {
        uvMat4Copy(&D_8028B400[arg0].unk68, arg1);
    }
}

void uvFxProps(s32 arg0, ...) {
    f32 var_fa0;
    f32 var_fv0;
    f32 temp_fv0;
    f32 temp_ft2;
    s16 propertyType;
    UnkFxStruct* var_a2;
    va_list args;
    UnkModelTrail* temp_v0;

    if (arg0 == 0xFF) {
        return;
    }
    var_a2 = &D_8028B400[arg0];
    va_start(args, arg0);
    // FAKE
    if (1) { } if (1) { } if (1) { }

    while (TRUE) {
        propertyType = va_arg(args, s32);
        switch (propertyType) {
            case 0:
                return;
            case 1:
                var_a2->unk8 = va_arg(args, f64);
                if (var_a2->unk1 == 4) {
                    temp_v0 = var_a2->unkA8;
                    temp_fv0 = uvGfxGetUnkStateF();
                    temp_ft2 = 10.0f;
                    if (temp_fv0 > 0.0f) {
                        temp_v0->unk1E4 = (s32) (var_a2->unk8 / temp_fv0);
                    } else {
                        temp_v0->unk1E4 = temp_ft2;
                    }
                    temp_v0->unk1D0 = (f32) (var_a2->unk55 - var_a2->unk59) / (f32) (temp_v0->unk1E4 * 9);
                }
                break;
            case 19:
                temp_fv0 = va_arg(args, f64);
                var_a2->unkAC = SQ(temp_fv0);
                break;
            case 2:
                var_a2->unkC = va_arg(args, f64);
                break;
            case 13:
                var_a2->unk2 = va_arg(args, s32);
                break;
            case 16:
                var_a2->unk5C = va_arg(args, s32);
                break;
            case 17:
                var_a2->unk60 = va_arg(args, s32);
                break;
            case 18:
                var_a2->unk64 = va_arg(args, s32);
                break;
            case 7:
                var_a2->unk48 = va_arg(args, f64);
                break;
            case 8:
                var_a2->unk50 = va_arg(args, s32);
                if ((var_a2->unk50 != 0xFFF) && (gGfxUnkPtrs->unk910[var_a2->unk50] == NULL)) {
                    _uvDebugPrintf(" uvFxProps: texture id %d not in level\n", var_a2->unk50);
                    var_a2->unk50 = 0xFFF;
                }
                break;
            case 15:
                var_a2->unk4C = va_arg(args, f64);
                break;
            case 3:
                var_a2->unk30 = va_arg(args, f64);
                var_a2->unk20 = var_a2->unk30 * 0.005f;
                var_a2->unk34 = va_arg(args, f64);
                var_a2->unk24 = var_a2->unk34 * 0.005f;
                var_a2->unk38 = va_arg(args, f64);
                var_a2->unk28 = var_a2->unk38 * 0.005f;

                var_fv0 = MAX(var_a2->unk30, var_a2->unk34);
                var_fa0 = MAX(var_a2->unk38, var_fv0);

                var_a2->unk14 = var_fa0;
                break;
            case 4:
                var_a2->unk3C = va_arg(args, f64);
                var_a2->unk40 = va_arg(args, f64);
                var_a2->unk44 = va_arg(args, f64);

                var_fv0 = MAX(var_a2->unk3C, var_a2->unk40);
                //! @bug should be checking max with unk44?
                var_fa0 = MAX(var_a2->unk3C, var_fv0);

                var_a2->unk18 = var_fa0;
                if (var_fa0 > 1.0f) {
                    var_a2->unk7 = 1;
                }
                break;
            case 5:
                var_a2->unk52 = (f32)va_arg(args, f64) * 255.0f;
                var_a2->unk53 = (f32)va_arg(args, f64) * 255.0f;
                var_a2->unk54 = (f32)va_arg(args, f64) * 255.0f;
                var_a2->unk55 = (f32)va_arg(args, f64) * 255.0f;
                if (var_a2->unk1 == 4) {
                    temp_v0 = var_a2->unkA8;
                    temp_v0->unk190.x = var_a2->unk52 - var_a2->unk56;
                    temp_v0->unk190.y = var_a2->unk53 - var_a2->unk57;
                    temp_v0->unk190.z = var_a2->unk54 - var_a2->unk58;
                    temp_v0->unk1D0 = (f32) (var_a2->unk55 - var_a2->unk59) / (f32) (temp_v0->unk1E4 * 9);
                }
                break;
            case 6:
                var_a2->unk56 = (f32)va_arg(args, f64) * 255.0f;
                var_a2->unk57 = (f32)va_arg(args, f64) * 255.0f;
                var_a2->unk58 = (f32)va_arg(args, f64) * 255.0f;
                var_a2->unk59 = (f32)va_arg(args, f64) * 255.0f;
                if (var_a2->unk1 == 4) {
                    temp_v0 = var_a2->unkA8;
                    temp_v0->unk190.x = var_a2->unk52 - var_a2->unk56;
                    temp_v0->unk190.y = var_a2->unk53 - var_a2->unk57;
                    temp_v0->unk190.z = var_a2->unk54 - var_a2->unk58;
                    temp_v0->unk1D0 = (f32) (var_a2->unk55 - var_a2->unk59) / (f32) (temp_v0->unk1E4 * 9);
                }
                break;
            case 10:
                var_a2->unk68.m[3][0] = va_arg(args, f64);
                var_a2->unk68.m[3][1] = va_arg(args, f64);
                var_a2->unk68.m[3][2] = va_arg(args, f64);
                break;
            case 11:
                var_a2->unk4 = va_arg(args, s32);
                if (var_a2->unk1 == 8) {
                    ((UnkModelDebrisStructure*)(var_a2->unkA8))->unk2E4 = 0;
                }
                break;
            case 12:
                var_a2->unk68.m[2][0] = va_arg(args, f64);
                var_a2->unk68.m[2][1] = va_arg(args, f64);
                var_a2->unk68.m[2][2] = va_arg(args, f64);
                break;
            case 14:
                var_a2->unk5A = va_arg(args, s32);
                break;
            default:
                _uvDebugPrintf("uvFxProps: Unknown property type %d\n", propertyType);
                return;
        }
    }
}

void uvFxGetProps(s32 arg0, ...) {
    UnkFxStruct* temp_s2;
    s16 propertyType;
    va_list args;

    if (arg0 == 0xFF) {
        return;
    }
    temp_s2 = &D_8028B400[arg0];
    va_start(args, arg0);

    while (TRUE) {
        propertyType = va_arg(args, s32);
        switch (propertyType) {
            case 0:
                return;
            case 1:
                *va_arg(args, f32*) = temp_s2->unk8;
                break;
            case 19:
                *va_arg(args, f32*) = uvSqrtF(temp_s2->unkAC);
                break;
            case 2:
                *va_arg(args, f32*) = temp_s2->unkC;
                break;
            case 13:
                *va_arg(args, s32*) = temp_s2->unk2;
                break;
            case 16:
                *va_arg(args, s16*) = temp_s2->unk5C;
                break;
            case 17:
                *va_arg(args, s32*) = temp_s2->unk60;
                break;
            case 18:
                *va_arg(args, s32*) = temp_s2->unk64;
                break;
            case 7:
                *va_arg(args, f32*) = temp_s2->unk48;
                break;
            case 8:
                *va_arg(args, s32*) = temp_s2->unk50;
                break;
            case 15:
                *va_arg(args, f32*) = temp_s2->unk4C;
                break;
            case 3:
                *va_arg(args, f32*) = temp_s2->unk30;
                *va_arg(args, f32*) = temp_s2->unk34;
                *va_arg(args, f32*) = temp_s2->unk38;
                break;
            case 5:
                *va_arg(args, f32*) = temp_s2->unk52 / 255.0f;
                *va_arg(args, f32*) = temp_s2->unk53 / 255.0f;
                *va_arg(args, f32*) = temp_s2->unk54 / 255.0f;
                *va_arg(args, f32*) = temp_s2->unk55 / 255.0f;
                break;
            case 6:
                *va_arg(args, f32*) = temp_s2->unk56 / 255.0f;
                *va_arg(args, f32*) = temp_s2->unk57 / 255.0f;
                *va_arg(args, f32*) = temp_s2->unk58 / 255.0f;
                *va_arg(args, f32*) = temp_s2->unk59 / 255.0f;
                break;
            case 10:
                *va_arg(args, f32*) = temp_s2->unk68.m[3][0];
                *va_arg(args, f32*) = temp_s2->unk68.m[3][1];
                *va_arg(args, f32*) = temp_s2->unk68.m[3][2];
                break;
            case 11:
                *va_arg(args, s32*) = temp_s2->unk4;
                break;
            case 12:
                *va_arg(args, f32*) = temp_s2->unk68.m[2][0];
                *va_arg(args, f32*) = temp_s2->unk68.m[2][1];
                *va_arg(args, f32*) = temp_s2->unk68.m[2][2];
                break;
            case 14:
                *va_arg(args, s32*) = temp_s2->unk5A;
                break;
            default:
                _uvDebugPrintf("uvFxGetProps: Unknown property type %d\n", propertyType);
                return;
        }
    }
}

s32 uvModelGet(s32 arg0, s32 modelId) {
    UnkFxStruct* var_v1;
    s32 i;
    s32 pad[3];

    var_v1 = &D_8028B400[arg0];
    if (arg0 == 255) {
        return 0;
    }
    if (modelId == 255) {
        if (var_v1->unk1 == 4) {
            ((UnkModelTrail*)(var_v1->unkA8))->unk1EC = 0;
        }
        if (var_v1->unk1 == 8) {
            ((UnkModelDebrisStructure*)(var_v1->unkA8))->unk2E4 = 0;
        }
        var_v1->unk4 = 0;
        var_v1->unk1 = modelId;
        return 1;
    }

    var_v1->unk6 = 0;
    var_v1->unk7 = 0;
    var_v1->unk52 = 255;
    var_v1->unk53 = 255;
    var_v1->unk54 = 255;
    var_v1->unk55 = 255;
    var_v1->unkA8 = NULL;
    var_v1->unk2 = 255;
    var_v1->unk50 = 0xFFF;
    var_v1->unk5A = 4;
    var_v1->unk5C = 0;
    var_v1->unk60 = 0;
    var_v1->unk64 = 0;
    var_v1->unk8 = var_v1->unk10 = 1.0f;
    var_v1->unkC = var_v1->unk1C = 0.0f;
    var_v1->unk20 = 0.005f;
    var_v1->unk24 = 0.005f;
    var_v1->unk28 = 0.005f;
    var_v1->unk30 = 1.0f;
    var_v1->unk34 = 1.0f;
    var_v1->unk38 = 1.0f;
    var_v1->unk3C = 1.0f;
    var_v1->unk40 = 1.0f;
    var_v1->unk44 = 1.0f;
    var_v1->unk18 = 1.0f;
    var_v1->unk48 = 1.0f;
    var_v1->unk4C = 0.0f;
    var_v1->unk14 = 0.5f;
    var_v1->unkAC = FLT_MAX;
    uvMat4SetIdentity(&var_v1->unk68);

    switch (modelId) {
        case 1:
            var_v1->unk0 = 2;
            var_v1->unk7 = 1;
            var_v1->unk6 = 0;
            var_v1->unk3C = 1.1f;
            var_v1->unk40 = 1.1f;
            var_v1->unk44 = 1.1f;
            var_v1->unk18 = 1.1f;
            break;
        case 4:
            var_v1->unk0 = 0;
            var_v1->unk8 = 1e20f;
            var_v1->unk52 = 255;
            var_v1->unk53 = 255;
            var_v1->unk54 = 255;
            var_v1->unk55 = 255;
            var_v1->unk56 = 128;
            var_v1->unk57 = 128;
            var_v1->unk58 = 128;
            var_v1->unk59 = 0;
            for (i = 0; i < 4; i++) {
                if (D_8028AC40[i].unk1EC == 0) {
                    func_8021A038(&D_8028AC40[i]);
                    var_v1->unkA8 = &D_8028AC40[i];
                    D_8028AC40[i].unk1EC = 1;
                    break;
                }
            }

            if (i == 4) {
                _uvDebugPrintf("uvModelGet: no more trails available\n");
                return 0;
            }
            uvMat4SetIdentity(&var_v1->unk68);
            uvMat4UnkOp3(&var_v1->unk68, 0.5f, 0.5f, 0.5f);
            break;
        case 6:
            var_v1->unk0 = 2;
            var_v1->unk8 = 1e20f;
            break;
        case 7:
            var_v1->unk0 = 3;
            var_v1->unk8 = 1e20f;
            break;
        case 2:
            var_v1->unk0 = 3;
            var_v1->unk52 = 255;
            var_v1->unk53 = 255;
            var_v1->unk54 = 0;
            var_v1->unk55 = 255;
            var_v1->unk56 = 255;
            var_v1->unk57 = 0;
            var_v1->unk58 = 0;
            var_v1->unk59 = 0;
            var_v1->unk7 = 1;
            var_v1->unk6 = 0;
            var_v1->unk3C = 1.1f;
            var_v1->unk40 = 1.1f;
            var_v1->unk44 = 1.1f;
            var_v1->unk18 = 1.1f;
            break;
        case 8:
            var_v1->unk0 = 0;
            var_v1->unk8 = 1e20f;
            var_v1->unk52 = 0;
            var_v1->unk53 = 0;
            var_v1->unk54 = 0;
            var_v1->unk55 = 0;
            var_v1->unk56 = 128;
            var_v1->unk57 = 128;
            var_v1->unk58 = 128;
            var_v1->unk59 = 0;

            for (i = 0; i < 4; i++) {
                if (D_8028A0A0[i].unk2E4 == 0) {
                    func_8021A0CC(&D_8028A0A0[i]);
                    var_v1->unkA8 = &D_8028A0A0[i];
                    D_8028A0A0[i].unk2E4 = 1;
                    break;
                }
            }

            if (i == 4) {
                _uvDebugPrintf("uvModelGet: no more debris structures available\n");
                return 0;
            }
            break;
        case 5:
            var_v1->unk0 = 3;
            var_v1->unk52 = 255;
            var_v1->unk53 = 0;
            var_v1->unk54 = 0;
            var_v1->unk55 = 255;
            var_v1->unk56 = 255;
            var_v1->unk57 = 255;
            var_v1->unk58 = 0;
            var_v1->unk59 = 128;
            var_v1->unk8 = 1e20f;
            break;
        case 3:
            var_v1->unk0 = 0;
            var_v1->unk52 = 150;
            var_v1->unk53 = 150;
            var_v1->unk54 = 150;
            var_v1->unk55 = 50;
            var_v1->unk8 = 1e20f;
            break;
        default:
            _uvDebugPrintf("uvFxModel: unknown model id: %d\n", modelId);
            return 0;
    }

    var_v1->unk1 = modelId;
    var_v1->unk4 = 1;
    var_v1->unk5 = 0;
    return 1;
}

void func_8021BE28(u16 arg0, Mtx4F* arg1) {
    UnkModelTrail* temp_v1;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 temp_fa0;
    f32 temp_fa1;
    s32 temp_hi;
    s32 temp_hi_2;
    UnkFxStruct* temp_v0;

    temp_v0 = &D_8028B400[arg0];
    temp_v0->unk4 = 1;
    temp_v1 = temp_v0->unkA8;
    temp_v1->unk1C4.x = arg1->m[3][0] * 2;
    temp_fv0 = temp_v1->unk1C4.x;
    temp_v1->unk1C4.y = arg1->m[3][1] * 2;
    temp_fv1 = temp_v1->unk1C4.y;
    temp_v1->unk1C4.z = arg1->m[3][2] * 2;
    temp_fa0 = temp_v1->unk1C4.z;
    temp_v1->unk1D4 = temp_v0->unk55;
    temp_hi = temp_v1->unk1E8 % 10;
    temp_v1->unk168[temp_hi] = temp_v0->unk55;
    if (temp_v1->unk1E8 == 0) {
        if (temp_v1->unk1E6 == 0) {
            temp_v1->unk1D8.x = temp_fv0;
            temp_v1->unk1D8.y = temp_fv1;
            temp_v1->unk1D8.z = temp_fa0;
        }
        if (temp_v1->unk1E4 <= 0.0f) {
            temp_v1->unk1E4 = 10;
        }

        temp_fa1 = ((f32)temp_v1->unk1E6 * 2 * temp_v0->unk34) / temp_v1->unk1E4;
        temp_v1->unk0[0].unk0 = (arg1->m[0][0] * temp_fa1) + temp_v1->unk1D8.x;
        temp_v1->unk0[0].unk2 = (arg1->m[0][1] * temp_fa1) + temp_v1->unk1D8.y;
        temp_v1->unk0[0].unk4 = (arg1->m[0][2] * temp_fa1) + temp_v1->unk1D8.z;
        temp_v1->unk0[0].unk6 = (arg1->m[2][0] * temp_fa1) + temp_v1->unk1D8.x;
        temp_v1->unk0[0].unk8 = (arg1->m[2][1] * temp_fa1) + temp_v1->unk1D8.y;
        temp_v1->unk0[0].unkA = (arg1->m[2][2] * temp_fa1) + temp_v1->unk1D8.z;
        temp_v1->unk0[0].unkC = temp_v1->unk1D8.x - (arg1->m[0][0] * temp_fa1);
        temp_v1->unk0[0].unkE = temp_v1->unk1D8.y - (arg1->m[0][1] * temp_fa1);
        temp_v1->unk0[0].unk10 = temp_v1->unk1D8.z - (arg1->m[0][2] * temp_fa1);
        temp_v1->unk0[0].unk12 = temp_v1->unk1D8.x - (arg1->m[2][0] * temp_fa1);
        temp_v1->unk0[0].unk14 = temp_v1->unk1D8.y - (arg1->m[2][1] * temp_fa1);
        temp_v1->unk0[0].unk16 = temp_v1->unk1D8.z - (arg1->m[2][2] * temp_fa1);
        temp_v1->unkF0[0].x = temp_v1->unk1D8.x / 2;
        temp_v1->unkF0[0].y = temp_v1->unk1D8.y / 2;
        temp_v1->unkF0[0].z = temp_v1->unk1D8.z / 2;
    } else if (temp_v1->unk1E8 > 0) {
        temp_fa1 = temp_v0->unk34 * 2 * temp_v1->unk1E4;
        temp_fv0 = temp_v1->unk1C4.x - arg1->m[1][0] * temp_fa1;
        temp_fv1 = temp_v1->unk1C4.y - arg1->m[1][1] * temp_fa1;
        temp_fa0 = temp_v1->unk1C4.z - arg1->m[1][2] * temp_fa1;
        temp_v1->unk0[temp_hi].unk0 = (arg1->m[0][0] * 2 * temp_v0->unk30) + temp_fv0;
        temp_v1->unk0[temp_hi].unk2 = (arg1->m[0][1] * 2 * temp_v0->unk34) + temp_fv1;
        temp_v1->unk0[temp_hi].unk4 = (arg1->m[0][2] * 2 * temp_v0->unk38) + temp_fa0;
        temp_v1->unk0[temp_hi].unk6 = (arg1->m[2][0] * 2 * temp_v0->unk30) + temp_fv0;
        temp_v1->unk0[temp_hi].unk8 = (arg1->m[2][1] * 2 * temp_v0->unk34) + temp_fv1;
        temp_v1->unk0[temp_hi].unkA = (arg1->m[2][2] * 2 * temp_v0->unk38) + temp_fa0;
        temp_v1->unk0[temp_hi].unkC = temp_fv0 - (arg1->m[0][0] * 2 * temp_v0->unk30);
        temp_v1->unk0[temp_hi].unkE = temp_fv1 - (arg1->m[0][1] * 2 * temp_v0->unk34);
        temp_v1->unk0[temp_hi].unk10 = temp_fa0 - (arg1->m[0][2] * 2 * temp_v0->unk38);
        temp_v1->unk0[temp_hi].unk12 = temp_fv0 - (arg1->m[2][0] * 2 * temp_v0->unk30);
        temp_v1->unk0[temp_hi].unk14 = temp_fv1 - (arg1->m[2][1] * 2 * temp_v0->unk34);
        temp_v1->unk0[temp_hi].unk16 = temp_fa0 - (arg1->m[2][2] * 2 * temp_v0->unk38);
        temp_v1->unkF0[temp_hi].x = temp_fv0 / 2;
        temp_v1->unkF0[temp_hi].y = temp_fv1 / 2;
        temp_v1->unkF0[temp_hi].z = temp_fa0 / 2;
    }
    temp_v1->unk1E6++;
    if (temp_v1->unk1E6 >= temp_v1->unk1E4) {
        temp_v1->unk1E6 = 0;
        temp_hi_2 = temp_v1->unk1E8 % 10;
        temp_v1->unk1E8++;
        temp_hi = temp_v1->unk1E8 % 10;
        temp_v1->unkF0[temp_hi].x = temp_v1->unk1D8.x / 2;
        temp_v1->unkF0[temp_hi].y = temp_v1->unk1D8.y / 2;
        temp_v1->unkF0[temp_hi].z = temp_v1->unk1D8.z / 2;
        temp_v1->unk1D8.x = temp_v1->unk1C4.x;
        temp_v1->unk1D8.y = temp_v1->unk1C4.y;
        temp_v1->unk1D8.z = temp_v1->unk1C4.z;
        
        temp_v1->unk168[temp_hi] = temp_v0->unk55;
        temp_v1->unk0[temp_hi].unk0 = temp_v1->unk0[temp_hi_2].unk0;
        temp_v1->unk0[temp_hi].unk2 = temp_v1->unk0[temp_hi_2].unk2;
        temp_v1->unk0[temp_hi].unk4 = temp_v1->unk0[temp_hi_2].unk4;
        temp_v1->unk0[temp_hi].unk6 = temp_v1->unk0[temp_hi_2].unk6;
        temp_v1->unk0[temp_hi].unk8 = temp_v1->unk0[temp_hi_2].unk8;
        temp_v1->unk0[temp_hi].unkA = temp_v1->unk0[temp_hi_2].unkA;
        temp_v1->unk0[temp_hi].unkC = temp_v1->unk0[temp_hi_2].unkC;
        temp_v1->unk0[temp_hi].unkE = temp_v1->unk0[temp_hi_2].unkE;
        temp_v1->unk0[temp_hi].unk10 = temp_v1->unk0[temp_hi_2].unk10;
        temp_v1->unk0[temp_hi].unk12 = temp_v1->unk0[temp_hi_2].unk12;
        temp_v1->unk0[temp_hi].unk14 = temp_v1->unk0[temp_hi_2].unk14;
        temp_v1->unk0[temp_hi].unk16 = temp_v1->unk0[temp_hi_2].unk16;
    }
}

void func_8021C4F8(u16 arg0) {
    UnkModelDebrisStructure* temp_fp;
    UnkFxStruct* temp_s0;
    s32 i;
    u8 spC3;
    u8 spC2;
    u8 spC1;
    Mtx4F sp80;

    temp_s0 = &D_8028B400[arg0];
    temp_fp = temp_s0->unkA8;
    spC3 = temp_s0->unk52;
    spC2 = temp_s0->unk53;
    spC1 = temp_s0->unk54;
    uvMat4Copy(&sp80, &temp_s0->unk68);
    uvGfx_802236CC(&sp80);
    uvGfxSetFlags(0xFFF);

    if (temp_s0->unk60 != 0) {
        uvGfxSetFlags(temp_s0->unk60);
    }
    if (temp_s0->unk64 != 0) {
        uvGfxClearFlags(temp_s0->unk64);
    }

    for (i = 0; i < 20; i++) {
        if (temp_fp->unk2D0[i] != 0) {
            uvMat4SetIdentity(&sp80);
            sp80.m[3][0] = temp_fp->unk0[i].x;
            sp80.m[3][1] = temp_fp->unk0[i].y;
            sp80.m[3][2] = temp_fp->unk0[i].z;
            uvMat4RotateAxis(&sp80, temp_fp->unk1E0[i] * 0.2f, 122);
            uvMat4RotateAxis(&sp80, temp_fp->unk1E0[i] * 0.37f, 120);
            uvGfxMtxViewMul(&sp80, 1);
            uvVtxBeginPoly();
            uvVtx(0, 2, 0, 0, 0, spC3, spC2, spC1, 230);
            uvVtx(1, -1, 0, 0, 0, spC3, spC2, spC1, 230);
            uvVtx(-2, -1, 0, 0, 0, spC3, spC2, spC1, 230);
            uvVtxEndPoly();
            uvGfxMtxViewPop();
        }
    }
    uvGfxMtxViewPop();
}

void func_8021C74C(u16 arg0) {
    UnkFxStruct* temp_t2;
    UnkModelDebrisStructure* temp_a2;
    s32 i;
    f32 temp_fv0;
    s32 var_t1;
    s32 pad[2];

    temp_t2 = &D_8028B400[arg0];
    temp_a2 = temp_t2->unkA8;
    temp_fv0 = uvGfxGetUnkStateF();
    var_t1 = TRUE;

    for (i = 0; i < 20; i++) {
        if (temp_a2->unk2D0[i] != 0) {
            var_t1 = FALSE;
            temp_a2->unk0[i].x += temp_a2->unkF0[i].x * temp_fv0;
            temp_a2->unk0[i].y += temp_a2->unkF0[i].y * temp_fv0;
            temp_a2->unk0[i].z += temp_a2->unkF0[i].z * temp_fv0;
            temp_a2->unkF0[i].z += -62.999996f * temp_fv0;
            temp_a2->unk1E0[i] += temp_a2->unk230[i] * temp_fv0;
            temp_a2->unk280[i] -= temp_fv0;
            if (temp_a2->unk280[i] <= 0.0f) {
                temp_a2->unk2D0[i] = 0;
            }
        }
    }
    if (var_t1) {
        temp_t2->unk4 = 0;
        temp_a2->unk2E4 = 0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_1AF80/func_8021C87C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_1AF80/func_8021D700.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_1AF80/func_8021D8E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_1AF80/func_8021DAF8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_1AF80/func_8021DD30.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_1AF80/func_8021E608.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_1AF80/func_8021E7E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_1AF80/func_8021EA38.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_1AF80/_uvFxDraw.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_1AF80/func_8021EFF0.s")
