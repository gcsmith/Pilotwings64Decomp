#include "common.h"
#include "code_9A960.h"
#include "control_info.h"
#include "demo.h"
#include "game.h"
#include "snd.h"
#include <uv_geometry.h>
#include <uv_graphics.h>
#include <uv_math.h>
#include <uv_sprite.h>

typedef struct {
    s16 x;
    u8 y;
    u16 blitId;
} ControlInfoLabel;

typedef struct {
    u8 count;
    ControlInfoLabel* labels;
} ControlInfoLabelGroup;

STATIC_DATA s32 sControlInfoCount;

// clang-format off
STATIC_DATA ControlInfoLabel sControlInfoHangGlider[] = {
#if defined(VERSION_JP)
    { 222, 123, BLIT_J_41 },
    { 224, 137, BLIT_J_42 },
    { 243, 153, BLIT_J_43 },
    { 229, 196, BLIT_J_44 },
    { 220, 212, BLIT_J_45 },
    {  63, 194, BLIT_J_46 },
    {  46, 180, BLIT_J_47 },
#else  // VERSION_US
    { 223, 108, BLIT_CONT_INFO_FLARE_LANDING },
    { 220, 178, BLIT_CONT_INFO_Z_BUTTON },
    { 221, 196, BLIT_CONT_INFO_SNAP_PHOTO },
    {  46, 163, BLIT_CONT_INFO_CONTROL_VEHICLE },
#endif
};

STATIC_DATA ControlInfoLabel sControlInfoGyrocopter[] = {
#if defined(VERSION_JP)
    { 237, 107, BLIT_J_48 },
    { 236, 123, BLIT_J_4A },
    { 237, 147, BLIT_J_48 },
    { 237, 163, BLIT_J_49 },
    { 198, 196, BLIT_J_44 },
    { 190, 211, BLIT_J_4B },
    {  63, 194, BLIT_J_46 },
    {  46, 180, BLIT_J_47 },
#else  // VERSION_US
    { 227,  98, BLIT_CONT_INFO_INC_THROTTLE },
    { 227, 146, BLIT_CONT_INFO_DEC_THROTTLE },
    { 193, 179, BLIT_CONT_INFO_Z_BUTTON },
    { 193, 198, BLIT_CONT_INFO_FIRE_MISSILES },
    {  46, 163, BLIT_CONT_INFO_CONTROL_VEHICLE },
#endif
};

STATIC_DATA ControlInfoLabel sControlInfoRocketBelt[] = {
#if defined(VERSION_JP)
    { 236, 124, BLIT_J_4E },
    { 252, 124, BLIT_J_4D },
    { 252, 156, BLIT_J_4D },
    { 236, 156, BLIT_J_4C },
    { 229, 196, BLIT_J_44 },
    { 220, 212, BLIT_J_4F },
    {  63, 194, BLIT_J_46 },
    {  46, 180, BLIT_J_47 },
#else  // VERSION_US
    { 230, 126, BLIT_CONT_INFO_WEAK_JET },
    { 230, 104, BLIT_CONT_INFO_STRONG_JET },
    { 216, 167, BLIT_CONT_INFO_Z_BUTTON },
    { 216, 185, BLIT_CONT_INFO_AIR_BRAKE },
    {  46, 163, BLIT_CONT_INFO_CONTROL_VEHICLE },
#endif
};

STATIC_DATA ControlInfoLabel sControlInfoCannonball[] = {
#if defined(VERSION_JP)
    { 235, 134, BLIT_J_50 },
    {  61, 196, BLIT_J_52 },
    {  28, 180, BLIT_J_51 },
#else  // VERSION_US
    { 251, 104, BLIT_CONT_INFO_FIRE },
    {  38, 179, BLIT_CONT_INFO_ADJUST_FIRE },
#endif
};

STATIC_DATA ControlInfoLabel sControlInfoSkydiving[] = {
#if defined(VERSION_JP)
    { 222, 123, BLIT_J_41 },
    { 224, 137, BLIT_J_42 },
    { 243, 153, BLIT_J_43 },
    { 220, 195, BLIT_J_53 },
    { 221, 211, BLIT_J_54 },
    {  60, 212, BLIT_J_55 },
    {  60, 192, BLIT_J_56 },
    {  76, 172, BLIT_J_57 },
#else  // VERSION_US
    { 223, 106, BLIT_CONT_INFO_FLARE },
    { 218, 161, BLIT_CONT_INFO_OPEN_CHUTE },
    {  59, 200, BLIT_CONT_INFO_TILT_BACKWARD },
    {  59, 180, BLIT_CONT_INFO_TILT_FORWARD },
    {  59, 159, BLIT_CONT_INFO_TURN_LEFT_RIGHT },
    {  30, 159, BLIT_CONT_INFO_LEFT_RIGHT_ARROWS },
    {  38, 180, BLIT_CONT_INFO_UP_ARROW },
    {  38, 201, BLIT_CONT_INFO_DOWN_ARROW },
#endif
};

STATIC_DATA ControlInfoLabel sControlInfoJumbleHopper[] = {
#if defined(VERSION_JP)
    {  61, 211, BLIT_J_58 },
    { 221, 147, BLIT_J_58 },
    {  77, 171, BLIT_J_58 },
    {  77, 190, BLIT_J_59 },
    { 125, 212, BLIT_J_5A },
#else  // VERSION_US
    { 222, 104, BLIT_CONT_INFO_CHANGE_JUMP_ALTITUDE },
    {  59, 179, BLIT_CONT_INFO_ADJUST_LEFT_RIGHT },
    {  59, 198, BLIT_CONT_INFO_ADJUST_JUMP_ANGLES },
    {  27, 179, BLIT_CONT_INFO_LEFT_RIGHT_ARROWS },
    {  35, 195, BLIT_CONT_INFO_UP_ARROW },
    {  35, 208, BLIT_CONT_INFO_DOWN_ARROW },
#endif
};

STATIC_DATA ControlInfoLabel sControlInfoBirdman[] = {
#if defined(VERSION_JP)
    { 222, 116, BLIT_J_5B },
    { 220, 139, BLIT_J_4F },
    { 224, 153, BLIT_J_5C },
    { 229, 196, BLIT_J_44 },
    { 220, 212, BLIT_J_45 },
    {  63, 194, BLIT_J_46 },
    {  46, 180, BLIT_J_47 },
#else  // VERSION_US
    { 228,  99, BLIT_CONT_INFO_FLAP_WINGS },
    { 228, 131, BLIT_CONT_INFO_BRAKE_HOVER },
    { 220, 178, BLIT_CONT_INFO_Z_BUTTON },
    { 220, 196, BLIT_CONT_INFO_SNAP_PHOTO },
    {  46, 163, BLIT_CONT_INFO_CONTROL_VEHICLE },
#endif
};
// clang-format on

STATIC_DATA ControlInfoLabelGroup sControlInfoVeh[] = {
    {   ARRAY_COUNT(sControlInfoHangGlider),   sControlInfoHangGlider },
    {   ARRAY_COUNT(sControlInfoRocketBelt),   sControlInfoRocketBelt },
    {   ARRAY_COUNT(sControlInfoGyrocopter),   sControlInfoGyrocopter },
    {   ARRAY_COUNT(sControlInfoCannonball),   sControlInfoCannonball },
    {    ARRAY_COUNT(sControlInfoSkydiving),    sControlInfoSkydiving },
    { ARRAY_COUNT(sControlInfoJumbleHopper), sControlInfoJumbleHopper },
    {      ARRAY_COUNT(sControlInfoBirdman),      sControlInfoBirdman },
};

#if defined(VERSION_JP)
typedef struct {
    u8 unk0;
    // pad1
    s16 unk2;
    u8 unk4;
    // pad5
    u16 unk6;
    u16 unk8;
    u16 unkA;
} Unk80341584_unk4;

typedef struct {
    u8 unk0;
    // pad3
    Unk80341584_unk4* unk4;
} Unk80341584;

Unk80341584_unk4 D_80341524[] = {
    { 0x1, 0x1E, 0xAA, 0x151, 0xB, 0xB },
    { 0x3, 0x2B, 0xAA, 0x151, 0xB, 0xB },
    { 0x0, 0x1E, 0xBE, 0x151, 0xB, 0xB },
    { 0x2, 0x1E, 0xD2, 0x151, 0xB, 0xB }
};

Unk80341584_unk4 D_80341554[] = {
    { 0x1, 0x1E, 0xAA, 0x151, 0xB, 0xB },
    { 0x3, 0x2E, 0xAA, 0x151, 0xB, 0xB },
    { 0x0, 0x1E, 0xCC, 0x151, 0xB, 0xB },
    { 0x2, 0x1E, 0xD9, 0x151, 0xB, 0xB }
};

Unk80341584 D_80341584[] = {
    { 0x00,       NULL },
    { 0x00,       NULL },
    { 0x00,       NULL },
    { 0x00,       NULL },
    { 0x04, D_80341524 },
    { 0x04, D_80341554 },
    { 0x00,       NULL }
};
#endif

// clang-format off: disable formatter to show -1 terminator
STATIC_DATA s16 D_8034EC10[] = {
#if defined(VERSION_JP)
    0x72, 0x2D, 0x9C, 0x2D, 0x9C, 0x65, -1,
    0xBC, 0x28, 0xBC, 0x49, -1,
    0xC4, 0x5F, 0xDE, 0x5F, 0xDE, 0x3D, -1,
    -1
#else // VERSION_US
    0x7A, 0x35, 0x9E, 0x35, -1,
    0x9D, 0x35, 0x9D, 0x64, -1,
    0xBE, 0x24, 0xBE, 0x46, -1,
    0xF4, 0x48, 0xF4, 0x5D, -1,
    0xF4, 0x5C, 0xC6, 0x5C, -1,
    -1
#endif
};

// hang glider
STATIC_DATA s16 D_8034EC44[] = {
#if defined(VERSION_JP)
    0xD9, 0xCD, 0xC3, 0xCD, 0xB0, 0x93, -1,
    0x64, 0xAC, 0x88, 0xAC, 0x88, 0x7F, 0x9B, 0x7F, -1,
    0xDB, 0x7D, 0xBC, 0x7D, 0xBC, 0x6F, -1,
    0xBB, 0x7D, 0xB3, 0x7D, 0xB3, 0x67, -1,
    -1
#else // VERSION_US
    0xD5, 0xC3, 0xB0, 0x93, -1,
    0x9C, 0x7C, 0x4B, 0x7C, 0x4B, 0x9F, -1,
    0xDC, 0x7C, 0xB2, 0x7C, -1,
    0xB3, 0x7C, 0xB3, 0x67, -1,
    0xBD, 0x7C, 0xBD, 0x70, -1,
    -1
#endif
 };

// gyrocopter
STATIC_DATA s16 D_8034EC7C[] = {
#if defined(VERSION_JP)
    0xB2, 0x68, 0xB2, 0x8D, 0xE9, 0x8D, -1,
    0xBC, 0x6F, 0xE7, 0x6F, -1,
    0xBD, 0xC1, 0xAF, 0x98, -1,
    0x64, 0xAC, 0x87, 0xAC, 0x87, 0x7F, 0x9B, 0x7F, -1,
    -1
#else // VERSION_US
    0xB2, 0x67, 0xB2, 0x99, 0xDF, 0x99, -1,
    0xBC, 0x6E, 0xDF, 0x6E, -1,
    0xBB, 0xCB, 0xAF, 0x98, -1,
    0x9C, 0x7C, 0x4B, 0x7C, 0x4B, 0x9F, -1,
    -1
#endif
};

// rocket belt
STATIC_DATA s16 D_8034ECB0[] = {
#if defined(VERSION_JP)
    0xBC, 0x6F, 0xDC, 0x6F, 0xDC, 0x75, 0xE9, 0x75, -1,
    0xD9, 0xCD, 0xC3, 0xCD, 0xB0, 0x93, -1,
    0x64, 0xAC, 0x87, 0xAC, 0x87, 0x7F, 0x9B, 0x7F, -1,
    0xB2, 0x67, 0xB2, 0x95, 0xE9, 0x95, -1,
    -1
#else // VERSION_US
    0xB2, 0x67, 0xB2, 0x84, 0xE1, 0x84, -1,
    0xBC, 0x6E, 0xE1, 0x6E, -1,
    0xAF, 0x98, 0xD0, 0xBD, -1,
    0x9C, 0x7C, 0x4B, 0x7C, 0x4B, 0x9F, -1,
    -1
#endif
};

// cannonball
STATIC_DATA s16 D_8034ECE4[] = {
#if defined(VERSION_JP)
    0x74, 0xAC, 0x86, 0xAC, 0x86, 0x7F, 0x9A, 0x7F, -1,
    0xE6, 0x7D, 0xBC, 0x7D, 0xBC, 0x6F, -1,
    -1
#else // VERSION_US
    0x9C, 0x7C, 0x4B, 0x7C, 0x4B, 0xAD, -1,
    0xBC, 0x6E, 0xF5, 0x6E, -1,
    -1
#endif
};

// skydiving
STATIC_DATA s16 D_8034ED00[] = {
#if defined(VERSION_JP)
    0xD7, 0xC1, 0xB1, 0xC1, 0xB1, 0x67, -1,
    0xDB, 0x7D, 0xBB, 0x7D, 0xBB, 0x6F, -1,
    0x49, 0x97, 0x49, 0x80, 0x9B, 0x80, -1,
    -1,
#else // VERSION_US
    0xB2, 0x67, 0xB2, 0xA7, 0xD2, 0xA7, -1,
    0xBC, 0x6F, 0xDA, 0x6F, -1,
    0x9C, 0x7C, 0x4B, 0x7C, 0x4B, 0x99, -1,
    -1
#endif
};

// jumble hopper
STATIC_DATA s16 D_8034ED28[] = {
#if defined(VERSION_JP)
    0x49, 0x99, 0x49, 0x80, 0x9B, 0x80, -1,
    0xBA, 0x71, 0xBA, 0x8D, 0xD8, 0x8D, -1,
    -1
#else // VERSION_US
    0x4B, 0xAB, 0x4B, 0x80, 0x9B, 0x80, -1,
    0xBC, 0x6E, 0xDA, 0x6E, -1,
    -1
#endif
};

// birdman
STATIC_DATA s16 D_8034ED44[] = {
#if defined(VERSION_JP)
    0xBB, 0x6E, 0xD9, 0x6E, -1,
    0xD9, 0xCD, 0xC3, 0xCD, 0xB0, 0x93, -1,
    0x64, 0xAC, 0x87, 0xAC, 0x87, 0x7F, 0x9B, 0x7F, -1,
    0xB1, 0x67, 0xB1, 0x85, 0xD9, 0x85, -1,
    -1
#else // VERSION_US
    0xB2, 0x67, 0xB2, 0x89, 0xDF, 0x89, -1,
    0xBC, 0x6E, 0xDF, 0x6E, -1,
    0xAF, 0x98, 0xD5, 0xC3, -1,
    0x9C, 0x7C, 0x4B, 0x7C, 0x4B, 0x9F, -1,
    -1
#endif
};
// clang-format on

STATIC_DATA s16* D_8034ED78[] = { D_8034EC44, D_8034ECB0, D_8034EC7C, D_8034ECE4, D_8034ED00, D_8034ED28, D_8034ED44 };

#if defined(VERSION_JP)
s16 D_80341768[] = { 0xED, 0x95, -1 };

s16 D_80341770[] = { 0x33, 0xBD, -1 };

s16 D_80341778[] = { 0x3A, 0xA6, 0x3F, 0xA6, 0x44, 0xA6, 0x2D, 0xBA, 0x32, 0xBA, 0x37, 0xBA, 0x2D, 0xCE, 0x32, 0xCE, 0x37, 0xCE, 0xED, 0x95, -1 };

s16 D_803417A4[] = { 0x3D, 0xA6, 0x42, 0xA6, 0x47, 0xA6, 0x2D, 0xCE, 0x32, 0xCE, 0x37, 0xCE, -1 };

void* D_803417C0[] = { D_80341768, NULL, NULL, D_80341770, D_80341778, D_803417A4, NULL, NULL };
#endif

// forward declarations
void contInfoInit(void);
s32 contInfoUpdate(void);
void contInfoDraw(void);
void contInfoDeinit(void);

void contInfoMainRender(void) {
    contInfoInit();
    while (contInfoUpdate() == 0) {
        uvGfxBegin();
        contInfoDraw();
        uvGfxEnd();
    }
    contInfoDeinit();
}

void contInfoInit(void) {
    Unk80362690_Unk0* temp_s7;
    s32 i;
    s32 var_s2;
    ControlInfoLabel* temp_s1;

    temp_s7 = &D_80362690->unkC[D_80362690->unk9C];
    // clang-format off
    uvSprtProps(0x1E,
        SPRT_PROP_ENABLED(TRUE),
        SPRT_PROP_POS(0, SCREEN_HEIGHT),
        SPRT_PROP_BLIT(BLIT_N64_CONTROLLER_INFOGRAPHIC),
        SPRT_PROP_END
    );
    // clang-format on
    i = 0;
    sControlInfoCount = sControlInfoVeh[temp_s7->veh].count;
    for (i = 0; i < sControlInfoCount; i++) {
        temp_s1 = &sControlInfoVeh[temp_s7->veh].labels[i];
        // clang-format off
        uvSprtProps(i + 0x15,
            SPRT_PROP_ENABLED(TRUE),
            SPRT_PROP_BLIT(temp_s1->blitId),
            SPRT_PROP_END
        );
#if defined(VERSION_JP)
        uvSprtProps(i + 0x15,
            SPRT_PROP_POS(temp_s1->x, (uvSprtGetHeight(i + 0x15) - temp_s1->y) + SCREEN_HEIGHT),
            SPRT_PROP_END
        );
#else // VERSION_US
        uvSprtProps(i + 0x15,
            SPRT_PROP_POS(temp_s1->x, SCREEN_HEIGHT - temp_s1->y),
            SPRT_PROP_END
        );
#endif
        // clang-format on
    }
}

s32 contInfoUpdate(void) {
    demo_80323020();
    if (demoButtonPress(D_80362690->unk9C, A_BUTTON | START_BUTTON) != 0) {
        sndPlaySfxVolPitchPan(SFX_UI_CONTROL, 1.0f, 0.8f, 0.0f);
        func_8033FB14();
        return 1;
    }

    if (demoButtonPress(D_80362690->unk9C, B_BUTTON) != 0) {
        sndPlaySfx(SFX_UI_CANCEL);
        func_8033FB14();
        return 1;
    }

    return 0;
}

#if defined(VERSION_JP)
// https://decomp.me/scratch/HJdgY
#pragma GLOBAL_ASM("asm/nonmatchings/app/control_info/contInfo_802CEFA8.s")

void contInfo_802CF0CC(s32 arg0) {
    Unk80341584_unk4* temp_s1;
    f32 temp_fs0;
    s32 var_s3;

    for (var_s3 = 0; var_s3 < D_80341584[arg0].unk0; var_s3++) {
        temp_s1 = &D_80341584[arg0].unk4[var_s3];
        uvGfxStatePush();
        uvGfxSetFlags(GFX_STATE_XLU);
        uvGfxClearFlags(GFX_STATE_AA | GFX_STATE_ZBUFFER);
        uvGfxBindTexture(temp_s1->unk6);
        uvVtxBeginPoly();
        temp_fs0 = (SCREEN_HEIGHT - temp_s1->unk4);
        switch (temp_s1->unk0) {
        case 0:
            uvVtx(temp_s1->unk2, temp_fs0, 0, 0, 0, 255, 255, 255, 255);
            uvVtx(temp_s1->unk2 + temp_s1->unk8, temp_fs0, 0, temp_s1->unk8 << 5, 0, 255, 255, 255, 255);
            uvVtx(temp_s1->unk2 + temp_s1->unk8, (temp_s1->unkA + temp_fs0), 0, temp_s1->unk8 << 5, temp_s1->unkA << 5, 255, 255, 255, 255);
            uvVtx(temp_s1->unk2, (temp_s1->unkA + temp_fs0), 0, 0, temp_s1->unkA << 5, 255, 255, 255, 255);
            break;
        case 1:
            uvVtx(temp_s1->unk2, temp_fs0, 0, 0, temp_s1->unk8 << 5, 255, 255, 255, 255);
            uvVtx(temp_s1->unk2 + temp_s1->unkA, temp_fs0, 0, 0, 0, 255, 255, 255, 255);
            uvVtx(temp_s1->unk2 + temp_s1->unkA, (temp_s1->unk8 + temp_fs0), 0, temp_s1->unkA << 5, 0, 255, 255, 255, 255);
            uvVtx(temp_s1->unk2, (temp_s1->unk8 + temp_fs0), 0, temp_s1->unkA << 5, temp_s1->unk8 << 5, 255, 255, 255, 255);
            break;
        case 2:
            uvVtx(temp_s1->unk2, temp_fs0, 0, 0, temp_s1->unkA << 5, 255, 255, 255, 255);
            uvVtx(temp_s1->unk2 + temp_s1->unk8, temp_fs0, 0, temp_s1->unk8 << 5, temp_s1->unkA << 5, 255, 255, 255, 255);
            uvVtx(temp_s1->unk2 + temp_s1->unk8, (temp_s1->unk8 + temp_fs0), 0, temp_s1->unk8 << 5, 0, 255, 255, 255, 255);
            uvVtx(temp_s1->unk2, (temp_s1->unk8 + temp_fs0), 0, 0, 0, 255, 255, 255, 255);
            break;
        case 3:
            uvVtx(temp_s1->unk2, temp_fs0, 0, 0, 0, 255, 255, 255, 255);
            uvVtx(temp_s1->unk2 + temp_s1->unkA, temp_fs0, 0, 0, temp_s1->unk8 << 5, 255, 255, 255, 255);
            uvVtx(temp_s1->unk2 + temp_s1->unkA, (temp_s1->unk8 + temp_fs0), 0, temp_s1->unkA << 5, temp_s1->unk8 << 5, 255, 255, 255, 255);
            uvVtx(temp_s1->unk2, (temp_s1->unk8 + temp_fs0), 0, temp_s1->unkA << 5, 0, 255, 255, 255, 255);
            break;
        }
        uvVtxEndPoly();
        uvGfxStatePop();
    }
}

// https://decomp.me/scratch/99x3U
#pragma GLOBAL_ASM("asm/nonmatchings/app/control_info/contInfo_802CF758.s")
void contInfo_802CF758(void*);
#endif

void contInfoDrawLineSeg(s32 x0, s32 y0, s32 x1, s32 y1) {
    f32 x_off, ux, uy, angle, length, y_off;
    s32 x2, y2, x3, y3;

    y0 = SCREEN_HEIGHT - y0;
    y1 = SCREEN_HEIGHT - y1;
    ux = x1 - x0;
    uy = y1 - y0;
    if (uy < 0.0f) {
        SWAP_XOR(x0, x1);
        SWAP_XOR(y0, y1);
    }

    length = uvSqrtF(SQ(ux) + SQ(uy));
    ux /= length;
    uy /= length;

    angle = uvAtan2F(uy, ux) - PW_PI_2;
    y_off = uvSinF(angle);
    x_off = uvCosF(angle);

    x0 -= x_off + 0.5f;
    y0 -= y_off + 0.5f;
    x1 -= x_off + 0.5f;
    y1 -= y_off + 0.5f;

    x2 = x0 + x_off + 0.5f;
    y2 = y0 + y_off + 0.5f;
    x3 = x1 + x_off + 0.5f;
    y3 = y1 + y_off + 0.5f;

    uvVtxBeginPoly();
    uvVtx(x0, y0, 0, 0, 0, 200, 200, 200, 255);
    uvVtx(x2, y2, 0, 0, 0, 200, 200, 200, 255);
    uvVtx(x3, y3, 0, 0, 0, 200, 200, 200, 255);
    uvVtx(x1, y1, 0, 0, 0, 200, 200, 200, 255);
    uvVtxEndPoly();

#if defined(VERSION_JP)
    uvVtxBeginPoly();
    uvVtx(x0 + 1, y0 + 1, 0, 0, 0, 0, 0, 0, 255);
    uvVtx(x2 + 1, y2 + 1, 0, 0, 0, 0, 0, 0, 255);
    uvVtx(x3 + 1, y3 + 1, 0, 0, 0, 0, 0, 0, 255);
    uvVtx(x1 + 1, y1 + 1, 0, 0, 0, 0, 0, 0, 255);
    uvVtxEndPoly();
#endif
}

void contInfoDrawLineStrip(s16* coords) {
    s32 x0, y0, x1, y1, count;

    while (1) {
        x0 = *coords++;
        if (x0 < 0) {
            break;
        }

        y0 = *coords++;
        count = 0;
        while (1) {
            x1 = *coords++;
            if (x1 < 0) {
                break;
            }

            y1 = *coords++;
            contInfoDrawLineSeg(x0, y0, x1, y1);
            x0 = x1;
            y0 = y1;
            if (++count == 21) {
                _uvDebugPrintf("Line length > 20 segments encountered, probably missing a -1\nat the end of a segment list\n");
                break;
            }
        }
    }
}

void contInfoDraw(void) {
    s32 i;
    Unk80362690_Unk0* sp20;

    sp20 = &D_80362690->unkC[D_80362690->unk9C];
    uvSprtDraw(0x1E);
    for (i = 0; i < sControlInfoCount; i++) {
        uvSprtDraw(i + 0x15);
    }
    func_80314154();
    uvGfxEnableCull(0, 0);
    contInfoDrawLineStrip(D_8034EC10);
    if (D_8034ED78[sp20->veh] != NULL) {
        contInfoDrawLineStrip(D_8034ED78[sp20->veh]);
    }
#if defined(VERSION_JP)
    if (D_803417C0[sp20->veh] != NULL) {
        contInfo_802CF758(D_803417C0[sp20->veh]);
    }
    if (D_80341584[sp20->veh].unk0 != 0) {
        contInfo_802CF0CC(sp20->veh);
    }
#endif
    uvGfxEnableCull(0, 1);
    func_803141E4();
}

void contInfoDeinit(void) {
    uvSprtProps(0x1E, SPRT_PROP_ENABLED(FALSE), SPRT_PROP_END);
}
