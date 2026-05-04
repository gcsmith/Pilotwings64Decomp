#include "common.h"
#include "code_64730.h"
#include "code_66160.h"
#include "code_A64C0.h"
#include "code_A8C30.h"
#include "code_B2900.h"
#include "credits.h"
#include "env_sound.h"
#include "environment.h"
#include "demo.h"
#include "snd.h"
#include "task.h"
#include "text_data.h"
#include "user_paths.h"
#include <uv_dobj.h>
#include <uv_environment.h>
#include <uv_graphics.h>
#include <uv_sprite.h>
#include <uv_texture.h>
#include <uv_memory.h>

// .data
s32 D_8034F980[] = { 0x4E, 0x4F, 0x50, 0x51, 0x52, 0x53, 0x0905030A, 0x0207010A, 0x09000000 };
Vec3F D_8034F9A4[][2] = {
    {       { 12.28, -167.19, 15.2 }, { 20.98, -11.84, 2.61 } },
    {      { -560.74, 75.13, 77.12 }, { -87.87, 17.58, 2.54 } },
    {     { 125.45, 532.12, 149.18 },  { 127.91, 9.05, 2.63 } },
    {     { 955.21, 503.54, 153.87 },  { 140.52, 1.23, 3.34 } },
    {    { 2925.98, 677.54, 174.87 },  { -59.35, 13.3, 0.33 } },
    {     { 955.21, 503.54, 153.87 },  { 140.52, 1.23, 3.34 } },
    { { -1271.04, -1722.94, 256.05 },  { -35.48, 6.51, 0.33 } },
    {     { -750.70, 721.75, 80.28 }, { -108.37, 9.92, 2.62 } },
    {  { -2668.57, -895.48, 263.01 }, { -80.30, 17.45, 0.32 } },
    {     { -1419.9, 871.2, 639.72 },  { 65.62, 15.32, 0.32 } },
    {     { 955.21, 503.54, 153.87 },  { 140.52, 1.23, 3.34 } },
    {     { 572.89, 2230.43, 51.83 },  { 158.53, 6.61, 2.64 } },
};

// .bss
f32 D_8036D8E0;
s16 D_8036D8E8[6];
s16 D_8036D8F8[6];
Unk8037DCA0* D_8036D908[6];
Mtx4F D_8036D920;
Mtx4F D_8036D960;
Mtx4F D_8036D9A0;
Mtx4F D_8036D9E0;
s32 D_8036DA20;
u8 D_8036DA24;

// forward declarations
void func_80321760(void); // init function
s32 func_8032232C(void);  // deinit function
s32 func_80322464(void);  // update function
void func_803226DC(void); // draw function

s32 func_80321700(void) {
    func_80321760();
    while (func_80322464() == 0) {
        uvGfxBegin();
        func_803226DC();
        uvGfxEnd();
    }
    return func_8032232C();
}

void func_80321760(void) {
    Unk80362690_Unk0* sp3D4;
    s32 temp2;
    s16 temp;
    s16 temp_a0_2;
    s16 sp3CA;
    s16 sp3C8;
    s16 sp3C6;
    s16 sp3C4;
    s16 j;
    s16 i;
    s32 sp3BC;
    Mtx4F sp37C;
    Unk803136C4_Arg0 sp360;
    Camera* camera;
    Mtx4F sp31C;

    D_8036D8E0 = 0.0f;
    D_8036DA24 = 1;
    camera = D_80362690->unkC[D_80362690->unk9C].unk70;
    camera->clipNear = 1.0f;
    uvChan_80204C94(camera->unk22C, camera->clipX0, camera->clipX1, camera->clipY0, camera->clipY1, 1.0f, camera->clipFar);
    camera_802D4514(camera);
    uvMat4SetIdentity(&sp31C);
    sp3D4 = &D_80362690->unkC[D_80362690->unk9C];
    uvLevelInit();
    envSoundInit();
    taskInitTest(sp3D4->cls, sp3D4->veh, sp3D4->test, &D_80362690->map, &D_80362690->terraId, &D_80362690->envId);
    uvLevelInit();
    textLoadBlock(0x42);
    envLoadTerrainPal(D_80362690->envId);
    switch (D_80362690->map) {
    case MAP_LITTLE_STATES:
        switch (sp3D4->veh) {
        case VEHICLE_HANG_GLIDER:
            D_80362690->terraId = 6;
            uvLevelAppend(8);
            break;
        case VEHICLE_ROCKET_BELT:
            D_80362690->terraId = 4;
            uvLevelAppend(6);
            break;
        case VEHICLE_GYROCOPTER:
            D_80362690->terraId = 5;
            uvLevelAppend(7);
            break;
        default:
            D_80362690->terraId = 6;
            uvLevelAppend(8);
            break;
        }
        break;
    case MAP_HOLIDAY_ISLAND:
    case MAP_CRESCENT_ISLAND:
    case MAP_EVER_FROST_ISLAND:
        uvLevelAppend(D_80362690->map);
        break;
    }
    env_802E1444(D_80362690->envId);
    uvChanTerra(sp3D4->unk70->unk22C, D_80362690->terraId);
    uvChan_80204A8C(sp3D4->unk70->unk22C, 3);
    uvEnvProps(D_80362690->envId, ENV_PROP_FOG_FACTOR(0.0f), ENV_PROP_END);
    uvLevelAppend(D_8034EE84[sp3D4->veh]);
    if (IS_BONUS_VEHICLE(sp3D4->veh)) {
        switch (sp3D4->cls) {
        case CLASS_BEGINNER:
            uvLevelAppend(0x61);
            sp3C4 = 0x23;
            break;
        case CLASS_A:
            uvLevelAppend(0x62);
            sp3C4 = 0x24;
            break;
        default:
        case CLASS_B:
            uvLevelAppend(0x63);
            sp3C4 = 0x25;
            break;
        }
    } else {
        switch (sp3D4->cls) {
        case CLASS_BEGINNER:
            uvLevelAppend(0x5F);
            sp3C4 = 0x21;
            break;
        case CLASS_A:
            uvLevelAppend(0x5D);
            sp3C4 = 0x1F;
            break;
        case CLASS_B:
            uvLevelAppend(0x5E);
            sp3C4 = 0x20;
            break;
        case CLASS_PILOT:
            uvLevelAppend(0x60);
            sp3C4 = 0x22;
            break;
        default:
            uvLevelAppend(0x5F);
            sp3C4 = 0x21;
            break;
        }
    }
    switch (sp3D4->veh) {
    case VEHICLE_HANG_GLIDER:
        uvLevelAppend(0x65);
        sp3C6 = 0x27;
        break;
    case VEHICLE_ROCKET_BELT:
        uvLevelAppend(0x66);
        sp3C6 = 0x28;
        break;
    case VEHICLE_GYROCOPTER:
        uvLevelAppend(0x64);
        sp3C6 = 0x26;
        break;
    case VEHICLE_CANNONBALL:
        uvLevelAppend(0x67);
        sp3C6 = 0x2A;
        break;
    case VEHICLE_SKY_DIVING:
        uvLevelAppend(0x69);
        sp3C6 = 0x2B;
        break;
    case VEHICLE_JUMBLE_HOPPER:
        uvLevelAppend(0x6A);
        sp3C6 = 0x2C;
        break;
    case VEHICLE_BIRDMAN:
        uvLevelAppend(0x68);
        sp3C6 = 0x29;
        break;
    default:
        uvLevelAppend(0x65);
        sp3C6 = 0x27;
        break;
    }
    temp2 = levelGetTotalPoints(&D_80364210[D_80362690->unk9C], sp3D4->cls, sp3D4->veh);
    temp2 = levelSetPointsToNextMedal(&sp3BC, temp2, IS_MAIN_VEHICLE(sp3D4->veh) ? sp3D4->cls : VEHICLE_SKY_DIVING);
    switch ((s16)temp2) {
    case 1:
        sp3C8 = 0x44;
        uvLevelAppend(0x6B);
        break;
    case 2:
        sp3C8 = 0x45;
        uvLevelAppend(0x6C);
        break;
    case 3:
        if (sp3BC > 0) {
            sp3C8 = 0x46;
            uvLevelAppend(0x6D);
        } else {
            // perfect score? sp3BC is points to next medal, if it's 0 we got a perfect score
            sp3C8 = 0x47;
            uvLevelAppend(0x6E);
        }
        break;
    default:
        sp3C8 = 0x44;
        uvLevelAppend(0x6B);
        _uvDebugPrintf("fell through to default case\n");
        break;
    }
    uvLevelAppend(0x6F);
    for (i = 0; i < ARRAY_COUNT(D_8036D8F8); i++) {
        D_8036D8F8[i] = i;
    }
    D_8036D8F8[5] = sp3D4->pilot;
    D_8036D8F8[sp3D4->pilot] = 5;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            temp_a0_2 = (demoRandF() * 4.0f) + 0.5f;
            temp = D_8036D8F8[temp_a0_2];
            D_8036D8F8[temp_a0_2] = D_8036D8F8[j];
            D_8036D8F8[j] = temp;
        }
    }
    for (i = 0; i < ARRAY_COUNT(D_8036D8E8); i++) {
        D_8036D8E8[i] = uvDobjAllocIdx();
        sp3CA = D_8034EE30[sp3D4->veh][D_8036D8F8[i]];
        uvDobjModel(D_8036D8E8[i], sp3CA);
        D_8036D908[i] = userPath_8034A4F8(D_8034F980[i]);
        D_8036D908[i]->unk352 = D_8036D8E8[i];
        func_8031EF60(D_8036D908[i], sp3CA);
        userPath_8034A950((D_8036D908[i])->unk4C, &sp360);
        func_803136C4(&sp360, &sp37C);
        uvDobjPosm(D_8036D8E8[i], 0, &sp37C);
        uvDobjState(D_8036D8E8[i], 2);
        userPath_8034A8B0(D_8036D908[i], 0U, 0.0f);
    }
    uvMat4SetIdentity(&camera->unk108);
    if (IS_MAIN_VEHICLE(sp3D4->veh)) {
        i = (sp3D4->cls * 3) + sp3D4->veh;
    } else {
        i = ((u8*)D_8034F980)[(sp3D4->cls + sp3D4->veh * 3) + 15];
        D_8036D8E0 = 12.0f;
    }
    if (i > 11) {
        _uvDebugPrintf("WARNING:  No camera coords set up for level %d, vehicle %d\n", sp3D4->cls, sp3D4->veh);
        i = 11;
    }
    uvMat4SetIdentity(&D_8036D9E0);
    uvMat4SetIdentity(&D_8036D960);
    uvMat4SetIdentity(&D_8036D920);
    uvMat4SetIdentity(&D_8036D9A0);
    uvMat4RotateAxis(&D_8036D9E0, D_8034F9A4[i][1].f[0] * 0.0174533f, 'z');
    uvMat4RotateAxis(&D_8036D9E0, -(D_8034F9A4[i][1].f[1] * 0.0174533f), 'x');
    D_8036D9E0.m[3][0] = D_8034F9A4[i]->f[0];
    D_8036D9E0.m[3][1] = D_8034F9A4[i]->f[1];
    D_8036D9E0.m[3][2] = D_8034F9A4[i]->f[2];
    uvMat4Copy(&camera->unk108, &D_8036D9E0);
    uvMat4RotateAxis(&D_8036D9A0, D_8034F9A4[i][1].f[0] * 0.0174533f, 'z');
    uvMat4RotateAxis(&D_8036D9A0, -(D_8034F9A4[i][1].f[1] * 0.0174533f), 'x');
    D_8036D960.m[3][0] = D_8034F9A4[i]->f[0];
    D_8036D960.m[3][1] = D_8034F9A4[i]->f[1];
    D_8036D960.m[3][2] = D_8034F9A4[i]->f[2];
    switch (sp3D4->veh) {
    case VEHICLE_HANG_GLIDER:
        uvMat4RotateAxis(&D_8036D920, -1.4835305f, 'x');
        uvMat4RotateAxis(&D_8036D920, 3.141594f, 'y');
        break;
    case VEHICLE_GYROCOPTER:
        uvMat4RotateAxis(&D_8036D920, -1.4835305f, 'x');
        uvMat4RotateAxis(&D_8036D920, 3.141594f, 'y');
        D_8036D960.m[3][2] -= 0.75f;
        break;
    default:
    case VEHICLE_ROCKET_BELT:
    case VEHICLE_CANNONBALL:
    case VEHICLE_SKY_DIVING:
    case VEHICLE_JUMBLE_HOPPER:
    case VEHICLE_BIRDMAN:
        uvMat4RotateAxis(&D_8036D920, 3.141594f, 'z');
        uvMat4RotateAxis(&D_8036D920, -2.268929f, 'x');
        break;
    }
    D_8036DA20 = sp3D4->veh;
    func_8031EF90(D_8036DA20);
    // clang-format off
    uvSprtProps(0,
        SPRT_PROP_ENABLED(TRUE),
        SPRT_PROP_BLIT(sp3C6),
        SPRT_PROP_TRANSPARENT(1),
        SPRT_PROP_FAST_COPY(0),
        SPRT_PROP_END
    );
    temp2 = 0xA0 - (uvSprtGetWidth(0) / 2);
    uvSprtProps(0, SPRT_PROP_POS(temp2, 220), SPRT_PROP_END);
    uvSprtProps(1,
        SPRT_PROP_ENABLED(TRUE),
        SPRT_PROP_BLIT(sp3C4),
        SPRT_PROP_TRANSPARENT(1),
        SPRT_PROP_FAST_COPY(0),
        SPRT_PROP_END
    );
    temp2 = 0xA0 - (uvSprtGetWidth(1) / 2);
    uvSprtProps(1, SPRT_PROP_POS(temp2, 190), SPRT_PROP_END);
    uvSprtProps(2,
        SPRT_PROP_ENABLED(TRUE),
        SPRT_PROP_BLIT(sp3C8),
        SPRT_PROP_TRANSPARENT(1),
        SPRT_PROP_FAST_COPY(0),
        SPRT_PROP_END
    );
    temp2 = 0xA0 - (uvSprtGetWidth(2) / 2);
    uvSprtProps(2, SPRT_PROP_POS(temp2, 98), SPRT_PROP_END);
    uvSprtProps(3,
        SPRT_PROP_ENABLED(TRUE),
        SPRT_PROP_BLIT(BLIT_ID_48),
        SPRT_PROP_TRANSPARENT(1),
        SPRT_PROP_FAST_COPY(0),
        SPRT_PROP_END
    );
    temp2 = 0xA0 - (uvSprtGetWidth(3) / 2);
    uvSprtProps(3, SPRT_PROP_POS(temp2, 50), SPRT_PROP_END);
    // clang-format on
    sndSetMusic(BGM_CONGRATS);
    sndSetMusicState(MUS_STATE_PLAY_SEQ);
}

s32 func_8032232C(void) {
    s16 i;

    for (i = 0; i < ARRAY_COUNT(D_8036D908); i++) {
        if (D_8036D908[i] != NULL) {
            func_8031EF68(D_8036D908[i]);
        }
        D_8036D908[i] = NULL;
        uvDobjModel(D_8036D8E8[i], 0xFFFF);
        userPathFree(i);
    }

    uvSprtProps(0, SPRT_PROP_ENABLED(FALSE), SPRT_PROP_END);
    uvSprtProps(1, SPRT_PROP_ENABLED(FALSE), SPRT_PROP_END);
    uvSprtProps(2, SPRT_PROP_ENABLED(FALSE), SPRT_PROP_END);
    uvSprtProps(3, SPRT_PROP_ENABLED(FALSE), SPRT_PROP_END);
    taskDeinitLevel();
    func_8031FE18(D_8036DA20);
    sndSetMusicState(MUS_STATE_STOP_SEQ);

    if (D_80362690->unkA8 < credits_8030CC48()) {
        creditsMainRender();
        return 0;
    }

    return 11;
}

s32 func_80322464(void) {
    Camera* camera;
    Mtx4F sp64;
    s32 i;

    camera = D_80362690->unkC[D_80362690->unk9C].unk70;
    demo_80323020();
    func_80313D74();
    D_8036D8E0 += D_8034F854;
    if (demoButtonPress(D_80362690->unk9C, A_BUTTON | B_BUTTON | START_BUTTON) != 0) {
        if (demoButtonPress(D_80362690->unk9C, A_BUTTON | START_BUTTON) != 0) {
            sndPlaySfx(SFX_UI_CONFIRM);
        }

        if (D_8036DA24 == 0) {
            return 1;
        }

        D_8036DA24 = 0;
    }

    for (i = 0; i < ARRAY_COUNT(D_8036D8F8); i++) {
        userPath_8034A8B0(D_8036D908[i], 1U, D_8036D8E0 / 12.0f);
        uvDobjGetPosm((D_8036D908[i])->unk352, 0, &sp64);
        uvMat4MulBA(&sp64, &D_8036D9A0, &sp64);
        uvMat4Mul(&sp64, &D_8036D920, &sp64);
        sp64.m[3][0] += D_8036D960.m[3][0];
        sp64.m[3][1] += D_8036D960.m[3][1];
        sp64.m[3][2] += D_8036D960.m[3][2];
        uvDobjPosm(D_8036D908[i]->unk352, 0, &sp64);
        func_8031FA0C(D_8036DA20, i, D_8036D8F8[i], (D_8036D908[i])->unk352, &sp64, &camera->unk108);
    }

    if (D_8036D8E0 > 12.25f || D_8036DA24 == 0) {
        func_8031FD70(0.0f);
        if (D_8036DA24 != 0) {
            D_8036DA24 = 0;
        }
    }

    return 0;
}

void func_803226DC(void) {
    Camera* camera = D_80362690->unkC[D_80362690->unk9C].unk70;
    uvChan_80204B34(camera->unk22C, &camera->unk108);
    uvChan_80204FC4(camera->unk22C);
    if (D_8036D8E0 > 12.0f || D_8036DA24 == 0) {
        screenDrawBoxSetup();
        uvGfxSetFlags(GFX_STATE_AA);
        screenDrawBox(0, 0, 0x13F, 0xEF, 0U, 0U, 0U, 0x66U);
        func_802DFA18();
        uvSprtDraw(0);
        uvSprtDraw(1);
        uvSprtDraw(2);
        uvSprtDraw(3);
    }
}
