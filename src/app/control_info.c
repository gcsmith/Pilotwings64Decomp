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

STATIC_DATA ControlInfoLabel sControlInfoHangGlider[] = {
    { 223, 108,   BLIT_CONT_INFO_FLARE_LANDING },
    { 220, 178,        BLIT_CONT_INFO_Z_BUTTON },
    { 221, 196,      BLIT_CONT_INFO_SNAP_PHOTO },
    {  46, 163, BLIT_CONT_INFO_CONTROL_VEHICLE },
};

STATIC_DATA ControlInfoLabel sControlInfoGyrocopter[] = {
    { 227,  98,    BLIT_CONT_INFO_INC_THROTTLE },
    { 227, 146,    BLIT_CONT_INFO_DEC_THROTTLE },
    { 193, 179,        BLIT_CONT_INFO_Z_BUTTON },
    { 193, 198,   BLIT_CONT_INFO_FIRE_MISSILES },
    {  46, 163, BLIT_CONT_INFO_CONTROL_VEHICLE },
};

STATIC_DATA ControlInfoLabel sControlInfoRocketBelt[] = {
    { 230, 126,        BLIT_CONT_INFO_WEAK_JET },
    { 230, 104,      BLIT_CONT_INFO_STRONG_JET },
    { 216, 167,        BLIT_CONT_INFO_Z_BUTTON },
    { 216, 185,       BLIT_CONT_INFO_AIR_BRAKE },
    {  46, 163, BLIT_CONT_INFO_CONTROL_VEHICLE },
};

STATIC_DATA ControlInfoLabel sControlInfoCannonball[] = {
    { 251, 104,        BLIT_CONT_INFO_FIRE },
    {  38, 179, BLIT_CONT_INFO_ADJUST_FIRE },
};

STATIC_DATA ControlInfoLabel sControlInfoSkydiving[] = {
    { 223, 106,             BLIT_CONT_INFO_FLARE },
    { 218, 161,        BLIT_CONT_INFO_OPEN_CHUTE },
    {  59, 200,     BLIT_CONT_INFO_TILT_BACKWARD },
    {  59, 180,      BLIT_CONT_INFO_TILT_FORWARD },
    {  59, 159,   BLIT_CONT_INFO_TURN_LEFT_RIGHT },
    {  30, 159, BLIT_CONT_INFO_LEFT_RIGHT_ARROWS },
    {  38, 180,          BLIT_CONT_INFO_UP_ARROW },
    {  38, 201,        BLIT_CONT_INFO_DOWN_ARROW },
};

STATIC_DATA ControlInfoLabel sControlInfoJumbleHopper[] = {
    { 222, 104, BLIT_CONT_INFO_CHANGE_JUMP_ALTITUDE },
    {  59, 179,    BLIT_CONT_INFO_ADJUST_LEFT_RIGHT },
    {  59, 198,   BLIT_CONT_INFO_ADJUST_JUMP_ANGLES },
    {  27, 179,    BLIT_CONT_INFO_LEFT_RIGHT_ARROWS },
    {  35, 195,             BLIT_CONT_INFO_UP_ARROW },
    {  35, 208,           BLIT_CONT_INFO_DOWN_ARROW },
};

STATIC_DATA ControlInfoLabel sControlInfoBirdman[] = {
    { 228,  99,      BLIT_CONT_INFO_FLAP_WINGS },
    { 228, 131,     BLIT_CONT_INFO_BRAKE_HOVER },
    { 220, 178,        BLIT_CONT_INFO_Z_BUTTON },
    { 220, 196,      BLIT_CONT_INFO_SNAP_PHOTO },
    {  46, 163, BLIT_CONT_INFO_CONTROL_VEHICLE },
};

STATIC_DATA ControlInfoLabelGroup sControlInfoVeh[] = {
    {   ARRAY_COUNT(sControlInfoHangGlider),   sControlInfoHangGlider },
    {   ARRAY_COUNT(sControlInfoRocketBelt),   sControlInfoRocketBelt },
    {   ARRAY_COUNT(sControlInfoGyrocopter),   sControlInfoGyrocopter },
    {   ARRAY_COUNT(sControlInfoCannonball),   sControlInfoCannonball },
    {    ARRAY_COUNT(sControlInfoSkydiving),    sControlInfoSkydiving },
    { ARRAY_COUNT(sControlInfoJumbleHopper), sControlInfoJumbleHopper },
    {      ARRAY_COUNT(sControlInfoBirdman),      sControlInfoBirdman },
};

// clang-format off: disable formatter to show -1 terminator
STATIC_DATA s16 D_8034EC10[] = {
    0x7A, 0x35, 0x9E, 0x35, -1,
    0x9D, 0x35, 0x9D, 0x64, -1,
    0xBE, 0x24, 0xBE, 0x46, -1,
    0xF4, 0x48, 0xF4, 0x5D, -1,
    0xF4, 0x5C, 0xC6, 0x5C, -1,
    -1
};

// hang glider
STATIC_DATA s16 D_8034EC44[] = {
    0xD5, 0xC3, 0xB0, 0x93, -1,
    0x9C, 0x7C, 0x4B, 0x7C, 0x4B, 0x9F, -1,
    0xDC, 0x7C, 0xB2, 0x7C, -1,
    0xB3, 0x7C, 0xB3, 0x67, -1,
    0xBD, 0x7C, 0xBD, 0x70, -1,
    -1
 };

// gyrocopter
STATIC_DATA s16 D_8034EC7C[] = {
    0xB2, 0x67, 0xB2, 0x99, 0xDF, 0x99, -1,
    0xBC, 0x6E, 0xDF, 0x6E, -1,
    0xBB, 0xCB, 0xAF, 0x98, -1,
    0x9C, 0x7C, 0x4B, 0x7C, 0x4B, 0x9F, -1,
    -1
};

// rocket belt
STATIC_DATA s16 D_8034ECB0[] = {
    0xB2, 0x67, 0xB2, 0x84, 0xE1, 0x84, -1,
    0xBC, 0x6E, 0xE1, 0x6E, -1,
    0xAF, 0x98, 0xD0, 0xBD, -1,
    0x9C, 0x7C, 0x4B, 0x7C, 0x4B, 0x9F, -1,
    -1
};

// cannonball
STATIC_DATA s16 D_8034ECE4[] = {
    0x9C, 0x7C, 0x4B, 0x7C, 0x4B, 0xAD, -1,
    0xBC, 0x6E, 0xF5, 0x6E, -1,
    -1
};

// skydiving
STATIC_DATA s16 D_8034ED00[] = {
    0xB2, 0x67, 0xB2, 0xA7, 0xD2, 0xA7, -1,
    0xBC, 0x6F, 0xDA, 0x6F, -1,
    0x9C, 0x7C, 0x4B, 0x7C, 0x4B, 0x99, -1,
    -1
};

// jumble hopper
STATIC_DATA s16 D_8034ED28[] = {
    0x4B, 0xAB, 0x4B, 0x80, 0x9B, 0x80, -1,
    0xBC, 0x6E, 0xDA, 0x6E, -1,
    -1
};

// birdman
STATIC_DATA s16 D_8034ED44[] = {
    0xB2, 0x67, 0xB2, 0x89, 0xDF, 0x89, -1,
    0xBC, 0x6E, 0xDF, 0x6E, -1,
    0xAF, 0x98, 0xD5, 0xC3, -1,
    0x9C, 0x7C, 0x4B, 0x7C, 0x4B, 0x9F, -1,
    -1
};
// clang-format on

STATIC_DATA s16* D_8034ED78[] = { D_8034EC44, D_8034ECB0, D_8034EC7C, D_8034ECE4, D_8034ED00, D_8034ED28, D_8034ED44 };

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
    s32 temp_s3;
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
        temp_s3 = i + 0x15;
        temp_s1 = &sControlInfoVeh[temp_s7->veh].labels[i];
        // clang-format off
        uvSprtProps(temp_s3,
            SPRT_PROP_ENABLED(TRUE),
            SPRT_PROP_BLIT(temp_s1->blitId),
            SPRT_PROP_END
        );
        uvSprtProps(temp_s3,
            SPRT_PROP_POS(temp_s1->x, SCREEN_HEIGHT - temp_s1->y),
            SPRT_PROP_END
        );
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
    uvGfxEnableCull(0, 1);
    func_803141E4();
}

void contInfoDeinit(void) {
    uvSprtProps(0x1E, SPRT_PROP_ENABLED(FALSE), SPRT_PROP_END);
}

