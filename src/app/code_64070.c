#include "common.h"
#include "code_64070.h"
#include "code_9A960.h"
#include "demo.h"
#include "game.h"
#include "snd.h"
#include <uv_geometry.h>
#include <uv_graphics.h>
#include <uv_math.h>
#include <uv_sprite.h>

typedef struct {
    s16 unk0;
    u8 unk2;
    u16 unk4;
} Unk8034EBD8_Unk4;

typedef struct {
    u8 length;
    Unk8034EBD8_Unk4* unk4;
} Unk8034EBD8;

s32 D_80359C90;

Unk8034EBD8_Unk4 D_8034EB00[] = {
    { 0xDF, 0x6C, 0x4D },
    { 0xDC, 0xB2, 0x4E },
    { 0xDD, 0xC4, 0x4F },
    { 0x2E, 0xA3, 0x50 },
};

Unk8034EBD8_Unk4 D_8034EB18[] = {
    { 0xE3, 0x62, 0x52 },
    { 0xE3, 0x92, 0x51 },
    { 0xC1, 0xB3, 0x4E },
    { 0xC1, 0xC6, 0x53 },
    { 0x2E, 0xA3, 0x50 },
};

Unk8034EBD8_Unk4 D_8034EB38[] = {
    { 0xE6, 0x7E, 0x54 },
    { 0xE6, 0x68, 0x55 },
    { 0xD8, 0xA7, 0x4E },
    { 0xD8, 0xB9, 0x56 },
    { 0x2E, 0xA3, 0x50 },
};

Unk8034EBD8_Unk4 D_8034EB58[] = {
    { 0xFB, 0x68, 0x57 },
    { 0x26, 0xB3, 0x58 },
};

Unk8034EBD8_Unk4 D_8034EB64[] = {
    { 0xDF, 0x6A, 0x59 },
    { 0xDA, 0xA1, 0x5A },
    { 0x3B, 0xC8, 0x5B },
    { 0x3B, 0xB4, 0x5C },
    { 0x3B, 0x9F, 0x5D },
    { 0x1E, 0x9F, 0x5E },
    { 0x26, 0xB4, 0x5F },
    { 0x26, 0xC9, 0x60 },
};

Unk8034EBD8_Unk4 D_8034EB94[] = {
    { 0xDE, 0x68, 0x61 },
    { 0x3B, 0xB3, 0x62 },
    { 0x3B, 0xC6, 0x63 },
    { 0x1B, 0xB3, 0x5E },
    { 0x23, 0xC3, 0x5F },
    { 0x23, 0xD0, 0x60 },
};

Unk8034EBD8_Unk4 D_8034EBB8[] = {
    { 0xE4, 0x63, 0x64 },
    { 0xE4, 0x83, 0x65 },
    { 0xDC, 0xB2, 0x4E },
    { 0xDC, 0xC4, 0x4F },
    { 0x2E, 0xA3, 0x50 },
};

Unk8034EBD8 D_8034EBD8[] = {
    { 0x04, D_8034EB00 },
    { 0x05, D_8034EB38 },
    { 0x05, D_8034EB18 },
    { 0x02, D_8034EB58 },
    { 0x08, D_8034EB64 },
    { 0x06, D_8034EB94 },
    { 0x05, D_8034EBB8 },
};

// clang-format off: disable formatter to show -1 terminator
s16 D_8034EC10[] = {
    0x7A, 0x35, 0x9E, 0x35, -1,
    0x9D, 0x35, 0x9D, 0x64, -1,
    0xBE, 0x24, 0xBE, 0x46, -1,
    0xF4, 0x48, 0xF4, 0x5D, -1,
    0xF4, 0x5C, 0xC6, 0x5C, -1,
    -1
};

// hang glider
s16 D_8034EC44[] = {
    0xD5, 0xC3, 0xB0, 0x93, -1,
    0x9C, 0x7C, 0x4B, 0x7C, 0x4B, 0x9F, -1,
    0xDC, 0x7C, 0xB2, 0x7C, -1,
    0xB3, 0x7C, 0xB3, 0x67, -1,
    0xBD, 0x7C, 0xBD, 0x70, -1,
    -1
 };

// gyrocopter
s16 D_8034EC7C[] = {
    0xB2, 0x67, 0xB2, 0x99, 0xDF, 0x99, -1,
    0xBC, 0x6E, 0xDF, 0x6E, -1,
    0xBB, 0xCB, 0xAF, 0x98, -1,
    0x9C, 0x7C, 0x4B, 0x7C, 0x4B, 0x9F, -1,
    -1
};

// rocket belt
s16 D_8034ECB0[] = {
    0xB2, 0x67, 0xB2, 0x84, 0xE1, 0x84, -1,
    0xBC, 0x6E, 0xE1, 0x6E, -1,
    0xAF, 0x98, 0xD0, 0xBD, -1,
    0x9C, 0x7C, 0x4B, 0x7C, 0x4B, 0x9F, -1,
    -1
};

// cannonball
s16 D_8034ECE4[] = {
    0x9C, 0x7C, 0x4B, 0x7C, 0x4B, 0xAD, -1,
    0xBC, 0x6E, 0xF5, 0x6E, -1,
    -1
};

// skydiving
s16 D_8034ED00[] = {
    0xB2, 0x67, 0xB2, 0xA7, 0xD2, 0xA7, -1,
    0xBC, 0x6F, 0xDA, 0x6F, -1,
    0x9C, 0x7C, 0x4B, 0x7C, 0x4B, 0x99, -1,
    -1
};

// jumble hopper
s16 D_8034ED28[] = {
    0x4B, 0xAB, 0x4B, 0x80, 0x9B, 0x80, -1,
    0xBC, 0x6E, 0xDA, 0x6E, -1,
    -1
};

// birdman
s16 D_8034ED44[] = {
    0xB2, 0x67, 0xB2, 0x89, 0xDF, 0x89, -1,
    0xBC, 0x6E, 0xDF, 0x6E, -1,
    0xAF, 0x98, 0xD5, 0xC3, -1,
    0x9C, 0x7C, 0x4B, 0x7C, 0x4B, 0x9F, -1,
    -1
};
// clang-format on

s16* D_8034ED78[] = { D_8034EC44, D_8034ECB0, D_8034EC7C, D_8034ECE4, D_8034ED00, D_8034ED28, D_8034ED44 };

// forward declarations
void func_802DCBA0(void);
s32 func_802DCCF0(void);
void func_802DD0E4(void);
void func_802DD1CC(void);

void func_802DCB40(void) {
    func_802DCBA0();
    while (func_802DCCF0() == 0) {
        uvGfxBegin();
        func_802DD0E4();
        uvGfxEnd();
    }
    func_802DD1CC();
}

void func_802DCBA0(void) {
    Unk80362690_Unk0* temp_s7;
    s32 temp_s3;
    s32 i;
    s32 var_s2;
    Unk8034EBD8_Unk4* temp_s1;

    temp_s7 = &D_80362690->unkC[D_80362690->unk9C];
    uvSprtProps(0x1E, 3, 1, 2, 0, 0xF0, 9, 0x3B, 0);
    i = 0;
    D_80359C90 = D_8034EBD8[temp_s7->veh].length;
    for (i = 0; i < D_80359C90; i++) {
        temp_s3 = i + 0x15;
        temp_s1 = &D_8034EBD8[temp_s7->veh].unk4[i];
        uvSprtProps(temp_s3, 3, 1, 9, temp_s1->unk4, 0);
        uvSprtProps(temp_s3, 2, temp_s1->unk0, 0xF0 - temp_s1->unk2, 0);
    }
}

s32 func_802DCCF0(void) {
    demo_80323020();
    if (demoButtonPress(D_80362690->unk9C, A_BUTTON | START_BUTTON) != 0) {
        func_8033F758(0x75U, 1.0f, 0.8f, 0.0f);
        func_8033FB14();
        return 1;
    }

    if (demoButtonPress(D_80362690->unk9C, B_BUTTON) != 0) {
        sndPlaySfx(1U);
        func_8033FB14();
        return 1;
    }

    return 0;
}

void func_802DCD88(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 pad_sp6C;
    f32 sp68;
    f32 temp_fa0;
    f32 temp_fs0;
    f32 temp_fv0;
    f32 sp58;
    s32 sp54;
    s32 sp50;
    s32 sp4C;
    s32 sp48;

    arg1 = 0xF0 - arg1;
    arg3 = 0xF0 - arg3;
    sp68 = arg2 - arg0;
    temp_fs0 = arg3 - arg1;
    if (temp_fs0 < 0.0f) {
        arg0 ^= arg2;
        arg1 ^= arg3;
        arg2 ^= arg0;
        arg3 ^= arg1;
        arg0 ^= arg2;
        arg1 ^= arg3;
    }
    temp_fv0 = uvSqrtF(SQ(sp68) + SQ(temp_fs0));
    temp_fs0 /= temp_fv0;
    sp68 /= temp_fv0;
    temp_fa0 = uvAtan2F(temp_fs0, sp68) - 1.5707963f;
    sp58 = uvSinF(temp_fa0);
    temp_fv0 = uvCosF(temp_fa0);
    arg0 -= temp_fv0 + 0.5f;
    arg1 -= sp58 + 0.5f;
    arg2 -= temp_fv0 + 0.5f;
    arg3 -= sp58 + 0.5f;
    sp54 = arg0 + temp_fv0 + 0.5f;
    sp50 = arg1 + sp58 + 0.5f;
    sp4C = arg2 + temp_fv0 + 0.5f;
    sp48 = arg3 + sp58 + 0.5f;
    uvVtxBeginPoly();
    uvVtx(arg0, arg1, 0, 0, 0, 200, 200, 200, 255);
    uvVtx(sp54, sp50, 0, 0, 0, 200, 200, 200, 255);
    uvVtx(sp4C, sp48, 0, 0, 0, 200, 200, 200, 255);
    uvVtx(arg2, arg3, 0, 0, 0, 200, 200, 200, 255);
    uvVtxEndPoly();
}

void func_802DD01C(s16* arg0) {
    s32 temp_s0;
    s32 temp_s3;
    s32 var_s4;
    s32 var_s5;
    s32 i;

    while (1) {
        var_s5 = *(arg0++);
        if (var_s5 < 0) {
            break;
        }

        var_s4 = *(arg0++);
        i = 0;
        while (1) {
            temp_s0 = *(arg0++);
            if (temp_s0 < 0) {
                break;
            }

            temp_s3 = *(arg0++);
            func_802DCD88(var_s5, var_s4, temp_s0, temp_s3);
            var_s5 = temp_s0;
            var_s4 = temp_s3;
            i++;
            if (i == 21) {
                _uvDebugPrintf("Line length > 20 segments encountered, probably missing a -1\nat the end of a segment list\n");
                break;
            }
        }
    }
}

void func_802DD0E4(void) {
    s32 i;
    Unk80362690_Unk0* sp20;

    sp20 = &D_80362690->unkC[D_80362690->unk9C];
    uvSprtDraw(0x1E);
    for (i = 0; i < D_80359C90; i++) {
        uvSprtDraw(i + 0x15);
    }
    func_80314154();
    uvGfxEnableCull(0, 0);
    func_802DD01C(D_8034EC10);
    if (D_8034ED78[sp20->veh] != NULL) {
        func_802DD01C(D_8034ED78[sp20->veh]);
    }
    uvGfxEnableCull(0, 1);
    func_803141E4();
}

void func_802DD1CC(void) {
    uvSprtProps(0x1E, 3, 0, 0);
}
