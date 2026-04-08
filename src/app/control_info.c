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

static s32 sControlInfoCount;

static ControlInfoLabel sControlInfoHangGlider[] = {
    { 223, 108,   BLIT_CONT_INFO_FLARE_LANDING },
    { 220, 178,        BLIT_CONT_INFO_Z_BUTTON },
    { 221, 196,      BLIT_CONT_INFO_SNAP_PHOTO },
    {  46, 163, BLIT_CONT_INFO_CONTROL_VEHICLE },
};

static ControlInfoLabel sControlInfoGyrocopter[] = {
    { 227,  98,    BLIT_CONT_INFO_INC_THROTTLE },
    { 227, 146,    BLIT_CONT_INFO_DEC_THROTTLE },
    { 193, 179,        BLIT_CONT_INFO_Z_BUTTON },
    { 193, 198,   BLIT_CONT_INFO_FIRE_MISSILES },
    {  46, 163, BLIT_CONT_INFO_CONTROL_VEHICLE },
};

static ControlInfoLabel sControlInfoRocketBelt[] = {
    { 230, 126,        BLIT_CONT_INFO_WEAK_JET },
    { 230, 104,      BLIT_CONT_INFO_STRONG_JET },
    { 216, 167,        BLIT_CONT_INFO_Z_BUTTON },
    { 216, 185,       BLIT_CONT_INFO_AIR_BRAKE },
    {  46, 163, BLIT_CONT_INFO_CONTROL_VEHICLE },
};

static ControlInfoLabel sControlInfoCannonball[] = {
    { 251, 104,        BLIT_CONT_INFO_FIRE },
    {  38, 179, BLIT_CONT_INFO_ADJUST_FIRE },
};

static ControlInfoLabel sControlInfoSkydiving[] = {
    { 223, 106,             BLIT_CONT_INFO_FLARE },
    { 218, 161,        BLIT_CONT_INFO_OPEN_CHUTE },
    {  59, 200,     BLIT_CONT_INFO_TILT_BACKWARD },
    {  59, 180,      BLIT_CONT_INFO_TILT_FORWARD },
    {  59, 159,   BLIT_CONT_INFO_TURN_LEFT_RIGHT },
    {  30, 159, BLIT_CONT_INFO_LEFT_RIGHT_ARROWS },
    {  38, 180,          BLIT_CONT_INFO_UP_ARROW },
    {  38, 201,        BLIT_CONT_INFO_DOWN_ARROW },
};

static ControlInfoLabel sControlInfoJumbleHopper[] = {
    { 222, 104, BLIT_CONT_INFO_CHANGE_JUMP_ALTITUDE },
    {  59, 179,    BLIT_CONT_INFO_ADJUST_LEFT_RIGHT },
    {  59, 198,   BLIT_CONT_INFO_ADJUST_JUMP_ANGLES },
    {  27, 179,    BLIT_CONT_INFO_LEFT_RIGHT_ARROWS },
    {  35, 195,             BLIT_CONT_INFO_UP_ARROW },
    {  35, 208,           BLIT_CONT_INFO_DOWN_ARROW },
};

static ControlInfoLabel sControlInfoBirdman[] = {
    { 228,  99,      BLIT_CONT_INFO_FLAP_WINGS },
    { 228, 131,     BLIT_CONT_INFO_BRAKE_HOVER },
    { 220, 178,        BLIT_CONT_INFO_Z_BUTTON },
    { 220, 196,      BLIT_CONT_INFO_SNAP_PHOTO },
    {  46, 163, BLIT_CONT_INFO_CONTROL_VEHICLE },
};

static ControlInfoLabelGroup sControlInfoVeh[] = {
    {   ARRAY_COUNT(sControlInfoHangGlider),   sControlInfoHangGlider },
    {   ARRAY_COUNT(sControlInfoRocketBelt),   sControlInfoRocketBelt },
    {   ARRAY_COUNT(sControlInfoGyrocopter),   sControlInfoGyrocopter },
    {   ARRAY_COUNT(sControlInfoCannonball),   sControlInfoCannonball },
    {    ARRAY_COUNT(sControlInfoSkydiving),    sControlInfoSkydiving },
    { ARRAY_COUNT(sControlInfoJumbleHopper), sControlInfoJumbleHopper },
    {      ARRAY_COUNT(sControlInfoBirdman),      sControlInfoBirdman },
};

// clang-format off: disable formatter to show -1 terminator
static s16 D_8034EC10[] = {
    0x7A, 0x35, 0x9E, 0x35, -1,
    0x9D, 0x35, 0x9D, 0x64, -1,
    0xBE, 0x24, 0xBE, 0x46, -1,
    0xF4, 0x48, 0xF4, 0x5D, -1,
    0xF4, 0x5C, 0xC6, 0x5C, -1,
    -1
};

// hang glider
static s16 D_8034EC44[] = {
    0xD5, 0xC3, 0xB0, 0x93, -1,
    0x9C, 0x7C, 0x4B, 0x7C, 0x4B, 0x9F, -1,
    0xDC, 0x7C, 0xB2, 0x7C, -1,
    0xB3, 0x7C, 0xB3, 0x67, -1,
    0xBD, 0x7C, 0xBD, 0x70, -1,
    -1
 };

// gyrocopter
static s16 D_8034EC7C[] = {
    0xB2, 0x67, 0xB2, 0x99, 0xDF, 0x99, -1,
    0xBC, 0x6E, 0xDF, 0x6E, -1,
    0xBB, 0xCB, 0xAF, 0x98, -1,
    0x9C, 0x7C, 0x4B, 0x7C, 0x4B, 0x9F, -1,
    -1
};

// rocket belt
static s16 D_8034ECB0[] = {
    0xB2, 0x67, 0xB2, 0x84, 0xE1, 0x84, -1,
    0xBC, 0x6E, 0xE1, 0x6E, -1,
    0xAF, 0x98, 0xD0, 0xBD, -1,
    0x9C, 0x7C, 0x4B, 0x7C, 0x4B, 0x9F, -1,
    -1
};

// cannonball
static s16 D_8034ECE4[] = {
    0x9C, 0x7C, 0x4B, 0x7C, 0x4B, 0xAD, -1,
    0xBC, 0x6E, 0xF5, 0x6E, -1,
    -1
};

// skydiving
static s16 D_8034ED00[] = {
    0xB2, 0x67, 0xB2, 0xA7, 0xD2, 0xA7, -1,
    0xBC, 0x6F, 0xDA, 0x6F, -1,
    0x9C, 0x7C, 0x4B, 0x7C, 0x4B, 0x99, -1,
    -1
};

// jumble hopper
static s16 D_8034ED28[] = {
    0x4B, 0xAB, 0x4B, 0x80, 0x9B, 0x80, -1,
    0xBC, 0x6E, 0xDA, 0x6E, -1,
    -1
};

// birdman
static s16 D_8034ED44[] = {
    0xB2, 0x67, 0xB2, 0x89, 0xDF, 0x89, -1,
    0xBC, 0x6E, 0xDF, 0x6E, -1,
    0xAF, 0x98, 0xD5, 0xC3, -1,
    0x9C, 0x7C, 0x4B, 0x7C, 0x4B, 0x9F, -1,
    -1
};
// clang-format on

static s16* D_8034ED78[] = { D_8034EC44, D_8034ECB0, D_8034EC7C, D_8034ECE4, D_8034ED00, D_8034ED28, D_8034ED44 };

// forward declarations
void contInfo_802DCBA0(void);
s32 contInfo_802DCCF0(void);
void contInfo_802DD0E4(void);
void func_802DD1CC(void);

void contInfoMainRender(void) {
    contInfo_802DCBA0();
    while (contInfo_802DCCF0() == 0) {
        uvGfxBegin();
        contInfo_802DD0E4();
        uvGfxEnd();
    }
    func_802DD1CC();
}

void contInfo_802DCBA0(void) {
    Unk80362690_Unk0* temp_s7;
    s32 temp_s3;
    s32 i;
    s32 var_s2;
    ControlInfoLabel* temp_s1;

    temp_s7 = &D_80362690->unkC[D_80362690->unk9C];
    // clang-format off
    uvSprtProps(0x1E,
        SPRT_PROP_3(1),
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
            SPRT_PROP_3(1),
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

s32 contInfo_802DCCF0(void) {
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

void contInfo_802DCD88(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
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

    arg1 = SCREEN_HEIGHT - arg1;
    arg3 = SCREEN_HEIGHT - arg3;
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

void contInfo_802DD01C(s16* arg0) {
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
            contInfo_802DCD88(var_s5, var_s4, temp_s0, temp_s3);
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

void contInfo_802DD0E4(void) {
    s32 i;
    Unk80362690_Unk0* sp20;

    sp20 = &D_80362690->unkC[D_80362690->unk9C];
    uvSprtDraw(0x1E);
    for (i = 0; i < sControlInfoCount; i++) {
        uvSprtDraw(i + 0x15);
    }
    func_80314154();
    uvGfxEnableCull(0, 0);
    contInfo_802DD01C(D_8034EC10);
    if (D_8034ED78[sp20->veh] != NULL) {
        contInfo_802DD01C(D_8034ED78[sp20->veh]);
    }
    uvGfxEnableCull(0, 1);
    func_803141E4();
}

void func_802DD1CC(void) {
    uvSprtProps(0x1E, SPRT_PROP_3(0), SPRT_PROP_END);
}
