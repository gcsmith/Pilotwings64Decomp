#include "common.h"

#include <uv_geometry.h>
#include <uv_graphics.h>
#include <uv_level.h>
#include <uv_math.h>
#include <uv_matrix.h>
#include <uv_sprite.h>
#include <uv_string.h>
#include <uv_vector.h>
#include "demo.h"
#include "code_68220.h"
#include "code_9A960.h"
#include "hud.h"
#include "pads.h"
#include "snap.h"
#include "snd.h"
#include "text_data.h"
#include "thermals.h"

// number of frames to render for camera shutter animation
#define CAMERA_SHUTTER_FRAMES 3

// hang glider speeds below this value will be highlighted larger red/amber font
#define HIGHLIGHT_SPEED_BELOW 36

typedef struct {
    s16 unk0;
    s16 unk2;
} Unk8034F93C;

extern f32 D_8034F910;
extern s32 D_8034F914;
extern s32 D_8034F938;
extern Unk8034F93C D_8034F93C[3];
extern Unk8034F93C D_8034F95C[4];

extern HUDState gHudState;

extern Vec2F gRadarThermCirc[17];
extern u8 D_8036D224;

// forward declarations
void hud_8031A378(void);
void hud_8031E628(f32 arg0, f32* arg1, f32* arg2);
void hudDemoController(void);
void hudDrawBirdman(HUDState*);
void hudDrawBox(HUDState*);
void hudDrawCannonball(HUDState*);
void hudDrawGyrocopter(HUDState*);
void hudGenThermCircle(void);
void hudDrawHangGlider(HUDState*);
void hudDrawJumbleHopper(HUDState*);
void hudDrawLowFuel(HUDState*);
void hudDrawRocketPack(HUDState*);
void hudDrawSkyDiving(HUDState*);
void hudDrawStartText(HUDState*);
void hudDrawRect(s32 x, s32 y, s32 width, s32 height, s32 penWidth, u8 r, u8 g, u8 b, u8 a);
void hudDrawPhotoCount(void);
void hudRadarWaypoint(f32 dist, f32 bearing, s32 type, s32 below, f32 heading, u8 alpha);
void hudRadarThermal(f32 xOff, f32 yOff, f32 scale, u8 r, u8 g, u8 b, u8 a, f32 arg7);
void hudSeaLevel(s32 x, s32 y, s32 alt);
void hudDrawSpeed(s32 x, s32 y, s32 speed, s32 highlightLowSpeed);
void hudDrawAltimeter(s32 x, s32 y, s32);
void hudDrawCamera(HUDState* hud);
void hudDrawFuel(s32 x, s32 y, f32 fuel);
void hudDrawRadar(s32 x, s32 y, f32, f32, f32, f32, HUDRadar*);
void hudDrawThrottle(s32 x, s32 y, f32 power);
void hudDrawAimReticle(s32 x, s32 y, s32 flag);
void hudDrawTimer(s32 x, s32 y, f32 timeSecF);
void hudDemoContButton(s32 spriteId, s32 x, s32 y);

void hudInit(void) {
    D_8034F914 = 0;
    D_8036D224 = 1;
    D_8034F910 = 0.0f;
    gHudState.renderFlags = 0;
    gHudState.unkC = 0;
    gHudState.unk14 = 0.0f;
    gHudState.unkB40[0] = -1;
    gHudState.unkBCC = 1;
    gHudState.unkBD0[0] = -1;
    gHudState.unkC5C = 1;
    gHudState.unkC74 = 0;
    gHudState.unkC60 = 0;
    gHudState.unkBB8 = 0.0f;
    gHudState.unkBBC = 0.0f;
    gHudState.unkBC0 = 0.0f;
    gHudState.unkBC4 = 0.0f;
    gHudState.unkBC8 = -1.0f;
    gHudState.unkC48 = 0.0f;
    gHudState.unkC4C = 0.0f;
    gHudState.unkC50 = 0.0f;
    gHudState.unkC54 = 0.0f;
    gHudState.unkC58 = -1.0f;
    gHudState.unkC68 = -100.0f;
    gHudState.unkC6C = 0.0f;
    gHudState.unkC70 = 0.0f;
    hud_8031A378();
    uvSprtProps(0, 3, 1, 1, 16, 8, 5, 0x11D, 0);
    uvSprtProps(1, 3, 1, 1, 32, 32, 5, 0x126, 0);
    uvSprtProps(2, 3, 1, 1, 32, 32, 5, 0x127, 0);
    uvSprtProps(3, 3, 1, 1, 16, 128, 5, 0x128, 0);
    uvSprtProps(4, 3, 1, 1, 32, 8, 5, 0x11E, 0);
    uvSprtProps(5, 3, 1, 1, 32, 8, 5, 0x121, 0);
    uvSprtProps(6, 3, 1, 1, 64, 8, 5, 0x11F, 0);
    uvSprtProps(7, 3, 1, 1, 32, 8, 5, 0x129, 0);
    uvSprtProps(8, 3, 1, 1, 32, 32, 5, 0x13D, 0);
    uvSprtProps(9, 3, 1, 1, 130, 100, 5, 0x137, 0);
    uvSprtProps(0xA, 3, 1, 1, 32, 8, 5, 0x120, 0);
    if (gHudState.showController) {
        uvLevelAppend(0x54);
        uvSprtProps(0xB, 3, 1, 2, 20, 200, 9, 0xB, 0);
        uvSprtProps(0xC, 3, 1, 2, 20, 200, 9, 0xC, 0);
        uvSprtProps(0xE, 3, 1, 2, 20, 200, 9, 0x16, 0);
        uvSprtProps(0xF, 3, 1, 2, 20, 200, 9, 0x17, 0);
        uvSprtProps(0xD, 3, 1, 2, 20, 200, 9, 0x18, 0);
        uvSprtProps(0x10, 3, 1, 2, 20, 200, 9, 0x1A, 0);
        uvSprtProps(0x11, 3, 1, 2, 20, 200, 9, 0x19, 0);
        uvSprtProps(0x12, 3, 1, 2, 20, 200, 9, 0x1B, 0);
    }
}

HUDState* hudGetState(void) {
    return &gHudState;
}

void hudMainRender(void) {
    Mtx4F sp98;
    Mtx4F sp58;
    Vec3F windVec;
    HUDState* hud;
    s32 pad[2];

    hud = &gHudState;
    if ((hud->renderFlags & HUD_RENDER_DISABLE) == 0x0) {
        if ((hud->unkC50 != 0.0f) && (hud->unkC54 < gHudState.unk14)) {
            hud->unkC5C = !hud->unkC5C;
            hud->unkC54 = (1.0f / hud->unkC50) + gHudState.unk14;
        }
        if ((hud->unkBC0 != 0.0f) && (hud->unkBC4 < gHudState.unk14)) {
            hud->unkBCC = !hud->unkBCC;
            hud->unkBC4 = (1.0f / hud->unkBC0) + gHudState.unk14;
        }
        if (gHudState.renderFlags & HUD_RENDER_ANY_VEHICLE) {
            if (gHudState.unk28.m[0][0] != 0.0f) {
                func_80313570(&gHudState.unk28, &gHudState.att.x, &gHudState.att.y, &gHudState.att.heading, &gHudState.att.pitch, &gHudState.unk78,
                              &gHudState.unk7C);
            } else {
                gHudState.att.x = gHudState.att.y = gHudState.att.heading = 0.0f;
                gHudState.att.pitch = gHudState.unk78 = gHudState.unk7C = 0.0f;
            }
            func_802E1754(gHudState.att.x, gHudState.att.y, gHudState.att.heading, &windVec);
            if ((windVec.x == 0.0f) && (windVec.y == 0.0f)) {
                gHudState.radar.windSpeed = gHudState.radar.windDir = 0.0f;
            } else {
                gHudState.radar.windSpeed = uvSqrtF((windVec.x * windVec.x) + (windVec.y * windVec.y));
                gHudState.radar.windDir = uvAtan2F(-windVec.x / gHudState.radar.windSpeed, windVec.y / gHudState.radar.windSpeed);
                gHudState.radar.windSpeed /= 5.0f;
                if (gHudState.radar.windSpeed < 0.0f) {
                    gHudState.radar.windSpeed = 0.0f;
                } else if (gHudState.radar.windSpeed > 0.88945f) {
                    gHudState.radar.windSpeed = 0.88945f;
                }
                gHudState.radar.windDir -= gHudState.att.pitch;
                if (gHudState.radar.windDir > 3.1415927f) {
                    gHudState.radar.windDir -= 6.2831855f;
                }
                if (gHudState.radar.windDir <= 3.1415927f) {
                    gHudState.radar.windDir += 6.2831855f;
                }
            }
        }
        uvGfxSetViewport(0, 0, 320, 0, 240);
        uvMat4Viewport(&sp98, -0.5f, 319.5f, -0.5f, 239.5f);
        uvGfxMtxProjPushF(&sp98);
        uvMat4SetIdentity(&sp58);
        uvGfxMtxViewLoad(&sp58, 1);
        uvGfxEnableZBuffer(0);
        if (gHudState.unkC60 != 0) {
            hudDrawBox(&gHudState);
        }
        if (gHudState.unkC64 < (gHudState.unk14 - gHudState.unkC68)) {
            if (gHudState.renderFlags & HUD_RENDER_HANG_GLIDER) {
                hudDrawHangGlider(&gHudState);
            } else if (gHudState.renderFlags & HUD_RENDER_ROCKET_PACK) {
                hudDrawRocketPack(&gHudState);
            } else if (gHudState.renderFlags & HUD_RENDER_GYROCOPTER) {
                hudDrawGyrocopter(&gHudState);
            } else if (gHudState.renderFlags & HUD_RENDER_CANNONBALL) {
                hudDrawCannonball(&gHudState);
            } else if (gHudState.renderFlags & HUD_RENDER_SKYDIVING) {
                hudDrawSkyDiving(&gHudState);
            } else if (gHudState.renderFlags & HUD_RENDER_JUMBLE_HOPPER) {
                hudDrawJumbleHopper(&gHudState);
            } else if (gHudState.renderFlags & HUD_RENDER_BIRDMAN) {
                hudDrawBirdman(&gHudState);
            }
            hudDrawLowFuel(&gHudState);
            hudDrawStartText(&gHudState);
            if (gHudState.showController != 0) {
                hudDemoController();
            }
        }
        gHudState.unkC++;
        gHudState.unk14 += D_8034F854;
        uvFont_80219EA8();
        uvGfxMtxViewPop();
    }
}

void hudDrawHangGlider(HUDState* hud) {
    hudDrawPhotoCount();
    hudDrawSpeed(27, 37, (s32)hud->speed, 1);
    hudSeaLevel(235, 37, (s32)hud->altSeaLevel);
    hudDrawAltimeter(250, 129, (s32)hud->altitude);
    hudDrawRadar(215, 222, hud->att.x, hud->att.y, hud->att.heading, hud->att.pitch, &hud->radar);
    hudDrawTimer(27, 222, hud->elapsedTime);
    hudDrawCamera(hud);
}

void hudDrawRocketPack(HUDState* hud) {
    hudSeaLevel(235, 37, (s32)hud->altSeaLevel);
    hudDrawAltimeter(250, 129, (s32)hud->altitude);
    hudDrawRadar(215, 222, hud->att.x, hud->att.y, hud->att.heading, hud->att.pitch, &hud->radar);
    hudDrawSpeed(27, 37, (s32)hud->speed, 0);
    hudDrawFuel(98, 37, hud->fuel);
    hudDrawTimer(27, 222, hud->elapsedTime);
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/hud/hudDrawCannonball.s")

void hudDrawSkyDiving(HUDState* hud) {
    // for sky diving, unk4 means alpha channel for the clouds that appear during
    // the transition from diving formations and landing. it transitions 00->FF->00
    if (hud->cloudFade != 0) {
        uvGfxStatePush();
        uvGfxSetFlags(0x800FFF);
        uvVtxBeginPoly();
        uvVtx(10, 18, 0, 0, 0, 0xFF, 0xFF, 0xFF, hud->cloudFade);
        uvVtx(310, 18, 0, 0, 0, 0xFF, 0xFF, 0xFF, hud->cloudFade);
        uvVtx(310, 232, 0, 0, 0, 0xFF, 0xFF, 0xFF, hud->cloudFade);
        uvVtx(10, 232, 0, 0, 0, 0xFF, 0xFF, 0xFF, hud->cloudFade);
        uvVtxEndPoly();
        uvGfxStatePop();
    } else {
        hudDrawAltimeter(250, 129, (s32)hud->altitude);
        hudSeaLevel(235, 37, (s32)hud->altSeaLevel);
        hudDrawTimer(27, 222, hud->elapsedTime);
        hudDrawRadar(215, 222, hud->att.x, hud->att.y, hud->att.heading, hud->att.pitch, &hud->radar);
    }
}

void hudDrawJumbleHopper(HUDState* hud) {
    hudDrawSpeed(27, 37, (s32)hud->speed, 0);
    hudSeaLevel(235, 37, (s32)hud->altSeaLevel);
    hudDrawAltimeter(250, 129, (s32)hud->altitude);
    hudDrawRadar(215, 222, hud->att.x, hud->att.y, hud->att.heading, hud->att.pitch, &hud->radar);
    hudDrawTimer(27, 222, hud->elapsedTime);
}

void hudDrawBirdman(HUDState* hud) {
    if (D_80362690->unk0[D_80362690->unk9C].unkC.unk7B == 0) {
        hudDrawPhotoCount();
    }
    hudSeaLevel(235, 37, (s32)hud->altSeaLevel);
    hudDrawAltimeter(250, 129, (s32)hud->altitude);
    hudDrawSpeed(27, 37, (s32)hud->speed, 0);
    if (D_80362690->unk0[D_80362690->unk9C].unkC.unk7B == 0) {
        hudDrawCamera(hud);
    }
}

void hudDrawCamera(HUDState* hud) {
    s32 x;

    if (hud->cameraState & HUD_CAM_RENDER_RETICLE) {
        uvSprtProps(9, 2, 0x5F, 0xAF, 7, 0xFF, 0, 0, 0x78, 0);
        uvSprtDraw(9);
        if (D_8034F914 == 0) {
            func_8033F7F8(0x43);
            D_8034F914 = 1;
        }
    } else if (hud->cameraState & HUD_CAM_RENDER_SHUTTER) {
        hud->cameraState = CAMERA_SHUTTER_FRAMES; // state now means # frames to render shutter
    } else if (hud->cameraState != 0) {
        // field is count down for rendering black rects for shutter
        if (hud->cameraState != 0) {
            x = (CAMERA_SHUTTER_FRAMES - hud->cameraState) * (240 / CAMERA_SHUTTER_FRAMES);
        } else {
            x = hud->cameraState * (240 / CAMERA_SHUTTER_FRAMES);
        }
        uvGfx_80223A28(0xFFF);
        uvVtxRect(0, 239, x, 0);
        uvVtxRect(319 - x, 239, 319, 0);
        hud->cameraState--;
        D_8034F914 = 0;
    }
}

void hudDrawGyrocopter(HUDState* hud) {
    hudDrawSpeed(27, 37, (s32)hud->speed, 0);
    hudSeaLevel(235, 37, (s32)hud->altSeaLevel);
    hudDrawAltimeter(250, 129, (s32)hud->altitude);
    hudDrawRadar(215, 222, hud->att.x, hud->att.y, hud->att.heading, hud->att.pitch, &hud->radar);
    hudDrawFuel(98, 37, hud->fuel);
    hudDrawThrottle(27, 82, hud->power);
    hudDrawTimer(27, 222, hud->elapsedTime);
    if (hud->renderFlags & HUD_RENDER_RETICLE) {
        hudDrawAimReticle((s32)hud->unkC6C, (s32)hud->unkC70, 0);
    }
}

void hudGenThermCircle(void) {
    f32 angle;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gRadarThermCirc) - 1; i++) {
        angle = (f32)i * 0.3926991f; // DEG_TO_RAD(22.5) or (360.0/16)
        gRadarThermCirc[i].x = uvSinF(angle);
        gRadarThermCirc[i].y = uvCosF(angle);
    }
    gRadarThermCirc[ARRAY_COUNT(gRadarThermCirc) - 1] = gRadarThermCirc[0];
}

void hud_8031A2CC(void) {
    HUDRadar* radar = &gHudState.radar;
    s32 i;

    radar->unk4 = 0;
    D_8036D224 = 1;

    for (i = 0; i < ARRAY_COUNT(radar->waypoints); i++) {
        radar->waypoints[i].unk1C = 0xFE;
        radar->waypoints[i].unk14 = 0;
        radar->waypoints[i].unk18 = 0xFF;
    }
}

void hud_8031A378(void) {
    HUDRadar* radar = &gHudState.radar;
    s32 idx;
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    s32 i;
    LevelHOPD* hopd;
    LevelBTGT* btgt;

    idx = 0;
    for (i = 0; i < levelDataGetHOPD(&hopd); i++) {
        radar->goals[idx].x = hopd[i].pos.x;
        radar->goals[idx].y = hopd[i].pos.y;
        radar->goals[idx].unkC = 0;
        idx++;
    }

    for (i = 0; i < levelDataGetBTGT(&btgt); i++) {
        radar->goals[idx].x = btgt[i].pos.x;
        radar->goals[idx].y = btgt[i].pos.y;
        radar->goals[idx].unkC = 0;
        idx++;
    }

    for (i = 0; i < gLandingPadCount; i++) {
        if (gLandingPads[i].unk14 == 0) {
            continue;
        }
        radar->goals[idx].x = gLandingPads[i].x;
        radar->goals[idx].y = gLandingPads[i].y;
        radar->goals[idx].unkC = 0;
        idx++;
    }

    for (i = 0; i < gLandingStripCount; i++) {
        radar->goals[idx].x = gLandingStrips[i].x;
        radar->goals[idx].y = gLandingStrips[i].y;
        func_80313430(gLandingStrips[i].unkC - gLandingStrips[i].unk0, gLandingStrips[i].unk10 - gLandingStrips[i].unk4, 0.0f, &sp74, &sp70, &sp6C);
        radar->goals[idx].unk8 = sp70;
        radar->goals[idx].unkC = 1;
        idx++;
    }
    radar->goalCount = idx;

    for (i = 0; i < gThermalCount; i++) {
        radar->therms[i].pos.x = gThermals[i].pos.x;
        radar->therms[i].pos.y = gThermals[i].pos.y;
        radar->therms[i].pos.z = gThermals[i].pos.z;
        radar->therms[i].scale = gThermals[i].scale;
    }

    hudGenThermCircle();
}

void hud_8031A66C(s32 idx, s32 arg1) {
    HUDRadar* radar = &gHudState.radar;
    s32 temp_v0;
    s32 var_v1;

    if (radar->waypoints[idx].unk14 > 0) {
        var_v1 = radar->waypoints[idx].unk14;
    } else {
        var_v1 = -radar->waypoints[idx].unk14;
    }

    if (var_v1 != arg1) {
        radar->waypoints[idx].unk14 = arg1;
        if (arg1 == 0) {
            radar->waypoints[idx].unk18 = 0xFF;
        }
    }
}

s32 hud_8031A6C8(f32 arg0, f32 arg1, f32 arg2) {
    HUDRadar* radar = &gHudState.radar;
    s32 idx;
    s32 i;

    idx = -1;
    for (i = 0; i < ARRAY_COUNT(gHudState.radar.waypoints); i++) {
        if (radar->waypoints[i].unk1C == 0xFE) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        _uvDebugPrintf("Panel: Too many radar targets requested (%d)\n", ARRAY_COUNT(gHudState.radar.waypoints));
        return 0xFF;
    }

    radar->waypoints[idx].unk0 = arg0;
    radar->waypoints[idx].unk4 = arg1;
    radar->waypoints[idx].unk14 = 0;
    radar->waypoints[idx].unk18 = 0xFF;
    radar->waypoints[idx].unk8 = arg2;
    radar->waypoints[idx].unk1C = D_8036D224 - 1;
    if (radar->unk4 < idx) {
        radar->unk4 = idx;
    }
    return idx;
}

void hud_8031A794(s32 idx, f32 arg1, f32 arg2, f32 arg3) {
    HUDRadar* radar = &gHudState.radar;

    if ((idx >= ARRAY_COUNT(gHudState.radar.waypoints)) || (idx < 0)) {
        _uvDebugPrintf("Panel: Bad index passed to movetarget %d\n", idx);
        return;
    }

    if (radar->waypoints[idx].unk1C != 0xFE) {
        radar->waypoints[idx].unk0 = arg1;
        radar->waypoints[idx].unk4 = arg2;
        radar->waypoints[idx].unk8 = arg3;
    }
}

void hud_8031A810(s32 idx) {
    HUDRadar* radar = &gHudState.radar;

    if ((idx >= ARRAY_COUNT(gHudState.radar.waypoints)) || (idx < 0)) {
        _uvDebugPrintf("Panel: Bad index passed to movetarget %d\n", idx);
        return;
    }

    if (radar->waypoints[idx].unk1C != 0xFE) {
        radar->waypoints[idx].unk1C = 0xFF;
    }
}

void hud_8031A874(s32 idx) {
    HUDRadar* radar = &gHudState.radar;

    if ((idx >= ARRAY_COUNT(gHudState.radar.waypoints)) || (idx < 0)) {
        _uvDebugPrintf("Panel: Bad index passed to movetarget %d\n", idx);
        return;
    }

    if (radar->waypoints[idx].unk1C == 0xFF) {
        radar->waypoints[idx].unk1C = D_8036D224 - 1;
    }
}

void hud_8031A8E0(s32 idx) {
    HUDRadar* radar = &gHudState.radar;

    if ((idx >= ARRAY_COUNT(gHudState.radar.waypoints)) || (idx < 0)) {
        _uvDebugPrintf("Panel: Bad index passed to movetarget %d\n", idx);
        return;
    }

    if (radar->waypoints[idx].unk1C != 0xFE) {
        radar->waypoints[idx].unk1C = 0xFE;
    } else {
        _uvDebugPrintf("Panel: Target removed which did not exist (%d)\n", idx);
    }
}

void hudDrawThrottle(s32 x, s32 y, f32 power) {
    Mtx4F rot;
    UNUSED s16* fakePtr;
    s16 y1;
    s16 y2;
    s16 pad;
    s16 xOffset;
    s16 yOffset;
    f32 angle;

    // fakematch
    fakePtr = &y2;
    fakePtr = &y1;

    uvSprtProps(1, 2, x, y, 0);
    uvSprtProps(2, 2, x + 31, y, 0);
    uvSprtDraw(1);
    uvSprtDraw(2);

    xOffset = x + 18;
    yOffset = y - 18;
    uvMat4SetIdentity(&rot);
    uvMat4UnkOp2(&rot, (f32)xOffset, (f32)yOffset, 0.0f);
    angle = (power - 0.5f) * 3.1415927f; // angle in range [-pi/2, pi/2]
    uvMat4RotateAxis(&rot, -angle, 'z');
    uvGfxMtxViewLoad(&rot, 1);

    // needle black rect + tri
    uvVtxBeginPoly();
    uvVtx(-2, -3, 0, 0, 0, 0, 0, 0, 0xFF);
    uvVtx(2, -3, 0, 0, 0, 0, 0, 0, 0xFF);
    uvVtx(2, 6, 0, 0, 0, 0, 0, 0, 0xFF);
    uvVtx(-2, 6, 0, 0, 0, 0, 0, 0, 0xFF);
    uvVtxEndPoly();

    y1 = 6;
    y2 = 10;
    uvVtxBeginPoly();
    uvVtx(-4, y1, 0, 0, 0, 0, 0, 0, 0xFF);
    uvVtx(4, y1, 0, 0, 0, 0, 0, 0, 0xFF);
    uvVtx(0, y2, 0, 0, 0, 0, 0, 0, 0xFF);
    uvVtxEndPoly();

    // needle white rect + tri
    uvVtxBeginPoly();
    uvVtx(-1, -2, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    uvVtx(1, -2, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    uvVtx(1, 6, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    uvVtx(-1, 6, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    uvVtxEndPoly();

    y1 = 6;
    y2 = 9;
    uvVtxBeginPoly();
    uvVtx(-3, y1, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    uvVtx(3, y1, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    uvVtx(0, y2, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    uvVtxEndPoly();
    uvGfxMtxViewPop();
}

void hudDrawRadar(s32 x, s32 y, f32 xOff, f32 yOff, f32 heading, f32 pitch, HUDRadar* radar) {
    Mtx4F sp108;
    Mtx4F spC8;
    f32 temp_fa0;
    f32 temp_fa1_2;
    f32 temp_fs0;
    f32 dist;
    f32 temp_fv0_3;
    f32 temp_fv1;
    s32 spAC;
    f32 tmpF1;
    f32 tmpF2;
    f32 var_fa1;
    f32 var_fv1;
    f32 sp98;
    f32 sp94;
    f32 sp90;
    s32 temp_s0;
    s32 temp_ft1;
    s32 temp_ft3;
    s32 temp_ft3_2;
    f32 sp58;
    s32 pad4;
    f32 sp74;
    f32 sp70;
    s32 i;
    s32 j;
    s16 tmp;
    s32 idx;

    uvMat4SetIdentity(&spC8);
    uvMat4UnkOp2(&spC8, (f32)(x + 35), (f32)(y - 35), 0);
    uvGfxMtxViewLoad(&spC8, 1);

    uvGfxStatePush();
    uvGfxSetFlags(0x800000);
    uvGfxClearFlags(0x600000);
    uvGfx_80223A28(0x124);
    uvVtxBeginPoly();
    uvVtx(-35, -35, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    uvVtx(0, -35, 0, 1088, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    uvVtx(0, 0, 0, 1088, 1088, 0xFF, 0xFF, 0xFF, 0xFF);
    uvVtx(-35, 0, 0, 0, 1088, 0xFF, 0xFF, 0xFF, 0xFF);
    uvVtxEndPoly();

    uvGfx_80223A28(0x125);
    uvVtxBeginPoly();
    uvVtx(0, -35, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    uvVtx(35, -35, 0, 1088, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    uvVtx(35, 0, 0, 1088, 1088, 0xFF, 0xFF, 0xFF, 0xFF);
    uvVtx(0, 0, 0, 0, 1088, 0xFF, 0xFF, 0xFF, 0xFF);
    uvVtxEndPoly();

    uvGfx_80223A28(0x123);
    uvVtxBeginPoly();
    uvVtx(0, 0, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    uvVtx(35, 0, 0, 1088, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    uvVtx(35, 35, 0, 1088, 1088, 0xFF, 0xFF, 0xFF, 0xFF);
    uvVtx(0, 35, 0, 0, 1088, 0xFF, 0xFF, 0xFF, 0xFF);
    uvVtxEndPoly();

    uvGfx_80223A28(0x122);
    uvVtxBeginPoly();
    uvVtx(-35, 0, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    uvVtx(0, 0, 0, 1088, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    uvVtx(0, 35, 0, 1088, 1088, 0xFF, 0xFF, 0xFF, 0xFF);
    uvVtx(-35, 35, 0, 0, 1088, 0xFF, 0xFF, 0xFF, 0xFF);
    uvVtxEndPoly();
    uvGfxStatePop();

    uvMat4SetIdentity(&sp108);
    sp58 = -pitch;
    uvMat4RotateAxis(&sp108, sp58, 'z');
    uvGfxMtxViewMul(&sp108, 1);

    uvGfxStatePush();
    uvGfxSetFlags(0x800000);
    uvGfxClearFlags(0x600000);
    uvVtxBeginPoly();
    uvVtx(0, 0, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    uvVtx(1, 0, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    uvVtx(1, 20, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    uvVtx(0, 20, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    uvVtxEndPoly();
    uvGfxStatePop();
    uvGfxMtxViewPop();

    temp_fs0 = (s16)(uvSinF(sp58) * -25.0f);
    temp_fv1 = (s16)(uvCosF(sp58) * 25.0f);
    temp_ft3 = temp_fv1 - 4.0f;
    spAC = temp_fv1 + 4.0f;
    uvGfxStatePush();
    uvGfxSetFlags(0x800000);
    uvGfxClearFlags(0x600000);
    uvGfx_80223A28(0x136);
    uvVtxBeginPoly();
    uvVtx(temp_fs0 - 4.0f, temp_ft3, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    uvVtx(temp_fs0 + 4.0f, temp_ft3, 0, 224, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    uvVtx(temp_fs0 + 4.0f, spAC, 0, 224, 224, 0xFF, 0xFF, 0xFF, 0xFF);
    uvVtx(temp_fs0 - 4.0f, spAC, 0, 0, 224, 0xFF, 0xFF, 0xFF, 0xFF);
    uvVtxEndPoly();
    uvGfxStatePop();

    if (radar->windSpeed > 0.0f) {
        uvMat4SetIdentity(&sp108);
        uvMat4RotateAxis(&sp108, radar->windDir, 'z');
        uvGfxMtxViewMul(&sp108, 1);
        tmp = radar->windSpeed * 30.0f;
        temp_s0 = tmp;
        uvGfxStatePush();
        uvGfxClearFlags(0x600000);
        uvVtxBeginPoly();
        uvVtx(-2, -1, 0, 0, 0, 0x00, 0x2E, 0x4D, 0xFF);
        uvVtx(2, -1, 0, 0, 0, 0x00, 0x2E, 0x4D, 0xFF);
        uvVtx(2, temp_s0 + 1, 0, 0, 0, 0x00, 0x2E, 0x4D, 0xFF);
        uvVtx(-2, temp_s0 + 1, 0, 0, 0, 0x00, 0x2E, 0x4D, 0xFF);
        uvVtxEndPoly();

        uvVtxBeginPoly();
        uvVtx(-4, temp_s0, 0, 0, 0, 0x00, 0x2E, 0x4D, 0xFF);
        uvVtx(4, temp_s0, 0, 0, 0, 0x00, 0x2E, 0x4D, 0xFF);
        uvVtx(0, temp_s0 + 6, 0, 0, 0, 0x00, 0x2E, 0x4D, 0xFF);
        uvVtxEndPoly();

        uvVtxBeginPoly();
        uvVtx(-1, -1, 0, 0, 0, 0x00, 0xA2, 0xFF, 0xFF);
        uvVtx(1, -1, 0, 0, 0, 0x00, 0xA2, 0xFF, 0xFF);
        uvVtx(1, temp_s0 + 1, 0, 0, 0, 0x00, 0xA2, 0xFF, 0xFF);
        uvVtx(-1, temp_s0 + 1, 0, 0, 0, 0x00, 0xA2, 0xFF, 0xFF);
        uvVtxEndPoly();

        uvVtxBeginPoly();
        uvVtx(-2, temp_s0, 0, 0, 0, 0x00, 0xA2, 0xFF, 0xFF);
        uvVtx(2, temp_s0, 0, 0, 0, 0x00, 0xA2, 0xFF, 0xFF);
        uvVtx(0, temp_s0 + 5, 0, 0, 0, 0x00, 0xA2, 0xFF, 0xFF);
        uvVtxEndPoly();

        uvVtxBeginPoly();
        uvVtx(0, 0, 0, 0, 0, 0x00, 0xFF, 0xFF, 0xFF);
        uvVtx(1, 0, 0, 0, 0, 0x00, 0xFF, 0xFF, 0xFF);
        uvVtx(1, temp_s0 + 3, 0, 0, 0, 0x00, 0xFF, 0xFF, 0xFF);
        uvVtx(0, temp_s0 + 3, 0, 0, 0, 0x00, 0xFF, 0xFF, 0xFF);
        uvVtxEndPoly();
        uvGfxStatePop();
        uvGfxMtxViewPop();
    }

    uvGfxStatePush();
    uvGfxSetFlags(0x800000);
    uvGfxClearFlags(0x600000);
    for (i = 0; i < gThermalCount; i++) {
        temp_fs0 = radar->therms[i].pos.x - xOff;
        sp70 = radar->therms[i].scale;
        sp74 = radar->therms[i].pos.y - yOff;
        dist = uvSqrtF(SQ(temp_fs0) + SQ(sp74)) - sp70;
        if (dist < 800.0f) {
            temp_fs0 *= 0.0375f;
            sp74 *= 0.0375f;
            sp70 *= 0.0375f;
            hudRadarThermal(temp_fs0, sp74, sp70, 0xFF, 0x64, 0, 0x96, sp58);
        }
    }
    uvGfxStatePop();

    for (i = 0; i <= radar->unk4; i++) {
        temp_fa0 = radar->waypoints[i].unk0 - xOff;
        var_fa1 = radar->waypoints[i].unk4 - yOff;
        if ((temp_fa0 == 0.0f) && (var_fa1 == 0.0f)) {
            sp94 = 0.0f;
            sp98 = 0.001f;
        } else {
            func_80313430(temp_fa0, var_fa1, 0, &sp98, &sp94, &sp90);
        }
        sp94 -= pitch;
        sp94 -= 1.5707963f;
        if (sp94 > 3.1415927f) {
            sp94 -= 6.2831855f;
        }
        if (sp94 <= -3.1415927f) {
            sp94 += 6.2831855f;
        }
        radar->waypoints[i].unkC = sp98;
        radar->waypoints[i].unk10 = sp94;
    }

    D_8036D224++;
    if (D_8036D224 > 0xFD) {
        D_8036D224 = 1;
    }

    for (i = 0; i < 10; i++) {
        var_fv1 = 50000.0f;
        for (j = 0; j <= radar->unk4; j++) {
            if (radar->waypoints[j].unk1C != 0xFE && radar->waypoints[j].unk1C != 0xFF && D_8036D224 != radar->waypoints[j].unk1C) {
                if (radar->waypoints[j].unkC < var_fv1) {
                    var_fv1 = radar->waypoints[j].unkC;
                    idx = j;
                }
            }
        }

        if (var_fv1 == 50000.0f) {
            break;
        }

        temp_fv0_3 = radar->waypoints[idx].unk8 - heading;
        if (radar->waypoints[idx].unk14 > 0) {
            radar->waypoints[idx].unk18 -= 50;
            if (radar->waypoints[idx].unk18 < 0) {
                radar->waypoints[idx].unk14 = -1;
                radar->waypoints[idx].unk18 = 0;
            }
        } else if (radar->waypoints[idx].unk14 < 0) {
            radar->waypoints[idx].unk18 += 50;
            if (radar->waypoints[idx].unk18 > 0xFF) {
                radar->waypoints[idx].unk14 = 1;
                radar->waypoints[idx].unk18 = 0xFF;
            }
        }
        hudRadarWaypoint(radar->waypoints[idx].unkC, radar->waypoints[idx].unk10, 0, temp_fv0_3 >= 0.0f ? 0 : 1, 0.0f, (u8)radar->waypoints[idx].unk18);
        radar->waypoints[idx].unk1C = D_8036D224;
    }

    for (i = 0; i < radar->goalCount; i++) {
        tmpF1 = radar->goals[i].x - xOff;
        tmpF2 = radar->goals[i].y - yOff;
        func_80313430(tmpF1, tmpF2, 0, &sp98, &sp94, &sp90);
        sp94 -= pitch;
        sp94 -= 1.5707963f;
        if (sp94 > 3.1415927f) {
            sp94 -= 6.2831855f;
        }
        if (sp94 <= -3.1415927f) {
            sp94 += 6.2831855f;
        }
        if (radar->goals[i].unkC == 1) {
            temp_fv0_3 = radar->goals[i].unk8;
            temp_fv0_3 -= pitch;
            temp_fv0_3 -= 1.5707963f;
            if (temp_fv0_3 > 3.1415927f) {
                sp94 -= 6.2831855f;
            }
            if (temp_fv0_3 <= -3.1415927f) {
                sp94 += 6.2831855f;
            }
            hudRadarWaypoint(sp98, sp94, 2, 0, temp_fv0_3, 0xFF);
        } else {
            hudRadarWaypoint(sp98, sp94, 1, 0, 0.0f, 0xFF);
        }
    }
    uvSprtProps(0, 2, x + 31, y - 33, 0);
    uvSprtDraw(0);
    uvGfxMtxViewPop();
}

void hudDemoContButton(s32 spriteId, s32 x, s32 y) {
    uvSprtProps(spriteId, 2, x + 20, 200 - y, 0);
    uvSprtDraw(spriteId);
}

void hudDemoController(void) {
    s32 screenX;
    s32 screenY;
    f32 stickX;
    f32 stickY;
    s32 buttons;

    buttons = demoGetButtons(0);
    uvSprtDraw(0xB);
    stickX = demoGetInputs(0, INPUT_AXIS_X);
    stickY = demoGetInputs(0, INPUT_AXIS_Y);
    screenX = stickX * 4.0 + 37.0;
    screenY = -stickY * 4.0 + 39.0;
    hudDemoContButton(0xC, screenX, screenY);

    if (buttons & A_BUTTON) {
        hudDemoContButton(0xF, 56, 27);
    }
    if (buttons & B_BUTTON) {
        hudDemoContButton(0xF, 50, 21);
    }
    if (buttons & U_CBUTTONS) {
        hudDemoContButton(0xE, 62, 14);
    }
    if (buttons & D_CBUTTONS) {
        hudDemoContButton(0xE, 62, 23);
    }
    if (buttons & L_CBUTTONS) {
        hudDemoContButton(0xE, 57, 18);
    }
    if (buttons & R_CBUTTONS) {
        hudDemoContButton(0xE, 66, 18);
    }
    if (buttons & U_JPAD) {
        hudDemoContButton(0xD, 14, 18);
    }
    if (buttons & D_JPAD) {
        hudDemoContButton(0xD, 14, 28);
    }
    if (buttons & L_JPAD) {
        hudDemoContButton(0xD, 9, 23);
    }
    if (buttons & R_JPAD) {
        hudDemoContButton(0xD, 18, 23);
    }
    if (buttons & L_TRIG) {
        hudDemoContButton(0x10, 7, 6);
    }
    if (buttons & R_TRIG) {
        hudDemoContButton(0x11, 56, 6);
    }
    if (buttons & Z_TRIG) {
        hudDemoContButton(0x12, 3, 52);
    }
}

void hudDrawSpeed(s32 x, s32 y, s32 speed, s32 highlightLowSpeed) {
    char str[12];
    s32 numX;

    y += 8;
    uvSprtProps(5, 2, x + 4, y - 18, 7, 0xFF, 0xFF, 0xFF, 0xFF, 0);
    uvSprtDraw(5);
    if ((speed < HIGHLIGHT_SPEED_BELOW) && (highlightLowSpeed)) {
        uvFontSet(7);
        numX = x - 5;
    } else {
        uvFontSet(8);
        numX = x;
    }
    uvFont_8021956C(0xFF, 0xFF, 0xFF, 0xFF);
    uvFont_80219550(1.0, 1.0);
    uvSprintf(str, "%3d", speed);
    uvFont_80219ACC(numX, y - 16, str);
    uvFontSet(8);
    uvFont_80219ACC(x + 33, y - 16, "k");
}

void hudDrawFuel(s32 x, s32 y, f32 fuel) {
    s16 curX1;
    s16 curX2;
    s16 curY1;
    s16 curY2;
    s16 curY3;
    s16 sy;
    s16 sx;
    s16 fuelScale;
    s32 pad2;

    sy = y - 8;
    sx = x;
    curX1 = sx - 3;
    curY1 = sy - 3;
    curY2 = sy + 11;
    curX2 = sx + 130;
    uvGfxStatePush();
    uvGfxSetFlags(0x800000);
    uvGfxClearFlags(0x600000);
    uvGfx_80223A28(0xFFF);
    uvVtxBeginPoly();
    uvVtx(curX1, curY1, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0x00);
    uvVtx(curX2, curY1, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0x00);
    uvVtx(curX2, curY2, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0x00);
    uvVtx(curX1, curY2, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0x00);
    uvVtxEndPoly();
    uvGfxStatePop();

    curX1 = sx + 127;
    curY1 = sy + 8;
    curX2 = sx;
    curY2 = sy;
    uvGfxStatePush();
    uvGfxClearFlags(0xE00000);
    uvVtxBeginPoly();
    uvVtx(curX2, curY2, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    uvVtx(curX1, curY2, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    uvVtx(curX1, curY1, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    uvVtx(curX2, curY1, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    uvVtxEndPoly();

    curX1 = sx + 1;
    curY1 = sy + 1;
    curY3 = sy + 7;
    curY2 = ((s32)(curY3 - curY1) / 2) + curY1;
    fuelScale = (s16)(fuel * 125.0f);
    curX2 = sx + fuelScale + 1;
    uvVtxBeginPoly();
    uvVtx(curX1, curY1, 0, 0, 0, 0xC6, 0xB5, 0x00, 0xFF);
    uvVtx(curX2, curY1, 0, 0, 0, 0xC6, 0xB5, 0x00, 0xFF);
    uvVtx(curX2, curY2, 0, 0, 0, 0xFE, 0xF7, 0x32, 0xFF);
    uvVtx(curX1, curY2, 0, 0, 0, 0xFE, 0xF7, 0x32, 0xFF);
    uvVtxEndPoly();

    uvVtxBeginPoly();
    uvVtx(curX1, curY2, 0, 0, 0, 0xFE, 0xF7, 0x32, 0xFF);
    uvVtx(curX2, curY2, 0, 0, 0, 0xFE, 0xF7, 0x32, 0xFF);
    uvVtx(curX2, curY3, 0, 0, 0, 0xEA, 0xD5, 0x00, 0xFF);
    uvVtx(curX1, curY3, 0, 0, 0, 0xEA, 0xD5, 0x00, 0xFF);
    uvVtxEndPoly();

    curX1 = sx + 126;
    uvVtxBeginPoly();
    uvVtx(curX2, curY1, 0, 0, 0, 0x01, 0x00, 0x9B, 0xFF);
    uvVtx(curX1, curY1, 0, 0, 0, 0x01, 0x00, 0x9B, 0xFF);
    uvVtx(curX1, curY2, 0, 0, 0, 0x00, 0x6B, 0xFF, 0xFF);
    uvVtx(curX2, curY2, 0, 0, 0, 0x00, 0x6B, 0xFF, 0xFF);
    uvVtxEndPoly();

    uvVtxBeginPoly();
    uvVtx(curX2, curY2, 0, 0, 0, 0x00, 0x6B, 0xFF, 0xFF);
    uvVtx(curX1, curY2, 0, 0, 0, 0x00, 0x6B, 0xFF, 0xFF);
    uvVtx(curX1, curY3, 0, 0, 0, 0x01, 0x00, 0xBA, 0xFF);
    uvVtx(curX2, curY3, 0, 0, 0, 0x01, 0x00, 0xBA, 0xFF);
    uvVtxEndPoly();
    uvGfxStatePop();

    uvSprtProps(7, 2, x, y - 10, 7, 0xFF, 0xFF, 0xFF, 0xFF, 0);
    uvSprtDraw(7);
}

void hudDrawAltimeter(s32 x, s32 y, s32 altitude) {
    s32 pad32;
    s16 sp72;
    s16 pad16;
    s16 curY;
    s16 sp6C;
    s16 curX;
    s16 dx;
    s16 dy;
    s16 curX2;
    s16 curY2;
    s32 sp40;
    f32 altNorm;
    char str[12];

    if (altitude <= 99.0f) {
        curY = y - 85;
        uvGfxStatePush();
        uvGfxSetFlags(0x800000);
        uvGfxClearFlags(0x600000);
        uvGfx_80223A28(0xFFF);
        uvVtxBeginPoly();
        dx = x;
        dy = y;
        curX = dx + 22;
        curX2 = dx + 38;
        curY2 = dy + 6;
        uvVtx(curX, curY, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0x00);
        uvVtx(curX2, curY, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0x00);
        uvVtx(curX2, curY2, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0x00);
        uvVtx(curX, curY2, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0x00);
        uvVtxEndPoly();
        uvGfxStatePop();

        uvSprtProps(3, 2, x + 27, y, 0);
        uvSprtDraw(3);

        uvGfxStatePush();
        uvGfxClearFlags(0xE00000);
        altNorm = altitude / 99.0f;
        if (altNorm > 1.0f) {
            altNorm = 1.0f;
        }
        if (altNorm < 0.0f) {
            altNorm = 0.0f;
        }
        uvVtxBeginPoly();
        curX = dx + 27;
        curY2 = ((s32)(altNorm * 81.0f) + y) - 0x51;
        sp40 = (s32)curY2;
        uvVtx(curX, curY2, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
        curX2 = dx + 33;
        uvVtx(curX2, curY2, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
        curY = curY2 + 1;
        uvVtx(curX2, curY, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
        uvVtx(curX, curY, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
        uvVtxEndPoly();

        curY = y - 81;
        uvVtxBeginPoly();
        curX = dx + 28;
        uvVtx(curX, curY, 0, 0, 0, 0xC8, 0x00, 0x00, 0xFF);
        curX2 = dx + 32;
        uvVtx(curX2, curY, 0, 0, 0, 0xC8, 0x00, 0x00, 0xFF);
        uvVtx(curX2, curY2, 0, 0, 0, 0xC8, 0x00, 0x00, 0xFF);
        uvVtx(curX, curY2, 0, 0, 0, 0xC8, 0x00, 0x00, 0xFF);
        uvVtxEndPoly();

        uvGfxStatePop();
        if (altitude <= 50.0f) {
            sp72 = dx - 9;
            sp6C = sp40 + 14;
        } else {
            sp72 = dx + 1;
            sp6C = sp40 + 9;
        }
        uvGfxStatePush();
        uvGfxSetFlags(0x800000);
        uvGfxClearFlags(0x600000);
        uvGfx_80223A28(0xFFF);
        uvVtxBeginPoly();
        uvVtx(sp72 - 5, sp40 - 5, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0);
        curX = dx + 23;
        uvVtx(curX + 5, sp40 - 5, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0);
        uvVtx(curX + 5, sp6C + 5, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0);
        uvVtx(sp72 - 5, sp6C + 5, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0);
        uvVtxEndPoly();
        uvGfxStatePop();

        uvGfxStatePush();
        uvGfxClearFlags(0xE00000);
        uvGfx_80223A28(0xFFF);
        uvVtxBeginPoly();
        uvVtx(sp72, sp40, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
        uvVtx(curX, sp40, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
        uvVtx(curX, sp6C, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
        uvVtx(sp72, sp6C, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
        uvVtxEndPoly();

        uvVtxBeginPoly();
        uvVtx(curX, sp40, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
        uvVtx((s16)(dx + 26), sp40, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
        uvVtx(curX, (s16)(sp40 + 3), 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
        uvVtxEndPoly();
        uvGfxStatePop();

        uvFontSet(1);
        uvFont_8021956C(0xC8, 0x00, 0x00, 0xFF); // red
        uvSprintf(str, "%2dm", altitude);
        if (altitude <= 50.0f) {
            uvFont_80219550(1.5, 1.5);
            uvFont_80219ACC(dx - 6, sp40 - 1, str);
        } else {
            uvFont_80219550(1.0, 1.0);
            uvFont_80219ACC(dx + 3, sp40 - 1, str);
        }
    }
}

void hudSeaLevel(s32 x, s32 y, s32 alt) {
    char str[12];

    y += 8;
    uvSprtProps(6, 2, x, y - 0x12, 7, 0xFF, 0xFF, 0xFF, 0xFF, 0);
    uvSprtDraw(6);
    uvFontSet(8);
    if (alt < 0) {
        alt = 0;
    }
    if (alt >= 10000) {
        alt = 9999;
    }
    uvFont_8021956C(0xFF, 0xFF, 0xFF, 0xFF);
    uvFont_80219550(1.0, 1.0);
    uvSprintf(str, "%4d", alt);
    x -= 8;
    uvFont_80219ACC(x + 9, y - 0x10, str);
    uvFont_80219ACC(x + 0x34, y - 0x10, "m");
}

#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/nonmatchings/app/hud/hudDrawTimer.s")
#else
// rom size changes when this gets compiled in, probably related to static var and .bss
void hudDrawTimer(s32 x, s32 y, f32 timeSecF) {
    static s32 D_8034F938 = 0;
    s32 timeMs;
    s32 timeSec;
    s32 dispHundth;
    s32 dispSec;
    s32 adjHundth;
    char timeStr[12];

    if (timeSecF != 0.0f) {
        if (timeSecF < (D_8034F910 + 0.083f)) {
            timeSecF = D_8034F910;
            adjHundth = 0;
        } else {
            D_8034F910 = timeSecF;
            adjHundth = 1;
        }
    }
    timeMs = (s32)(timeSecF * 1000.0f);
    if (timeMs >= 3600000) {
        timeMs = 3599999;
    }
    timeSec = (timeMs / 1000);
    dispHundth = (timeMs / 10) - (timeSec * 100);
    if ((timeMs != 3599999) && (timeSecF != 0.0f) && adjHundth) {
        if (D_8034F938 >= 4) {
            D_8034F938 = 0;
        }
        D_8034F938 += 1;
        dispHundth += D_8034F938;
        if (dispHundth >= 100) {
            dispHundth -= 100;
        }
    }
    uvSprtProps(4, 2, x, y, 7, 0xFF, 0xFF, 0xFF, 0xFF, 0);
    uvSprtDraw(4);
    uvFontSet(8);
    x += 36;
    y -= 12;
    uvFont_8021956C(0xFF, 0xFF, 0xFF, 0xFF);
    uvFont_80219550(1.0, 1.0);
    dispSec = timeSec - ((timeSec / 60) * 60);
    uvSprintf(timeStr, "%02d'%02d\"%02d", timeSec / 60, dispSec, dispHundth);
    uvFont_80219ACC(x, y, timeStr);
}
#endif

void hudDrawAimReticle(s32 x, s32 y, s32 flag) {
    s16 centerX;
    s16 centerY;

    centerX = x + 160;
    centerY = y + 125;
    if (flag == 0) {
        uvSprtProps(8, 2, centerX - 16, centerY + 16, 7, 0xFF, 0xFF, 0x00, 0xFF, 0);
    } else {
        uvSprtProps(8, 2, centerX - 16, centerY + 16, 7, 0x00, 0x00, 0x00, 0xFF, 0);
    }
    uvSprtDraw(8);
}

// called when fading screen to white and back after a crash
// unkC60:
//   1: fade to white while crashing
//   2: fade from white back to crash site
//   3: fade to black when??
//   4: fade from black when??
void hudDrawBox(HUDState* hud) {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    f32 tmp;
    f32 alphaF;
    s32 invAlpha;

    switch (hud->unkC60) {
    case 1:
        invAlpha = 1, r = g = b = 0xFF;
        break;
    case 2:
        invAlpha = 0, r = g = b = 0xFF;
        break;
    case 3:
        invAlpha = 1, r = g = b = 0x00;
        break;
    case 4:
        invAlpha = 0, r = g = b = 0x00;
        break;
    default:
        return;
    }

    if (hud->unkC64 == 0.0f) {
        alphaF = 1.0f;
    } else {
        tmp = (gHudState.unk14 - hud->unkC68) / hud->unkC64;
        alphaF = tmp * tmp * tmp;
        if (alphaF < 0.0f) {
            alphaF = 0.0f;
        } else if (alphaF > 1.0f) {
            alphaF = 1.0f;
        }
    }
    if (invAlpha) {
        a = (u8)(255.0f * alphaF);
    } else {
        a = (u8)((1.0f - alphaF) * 255.0f);
    }
    uvGfxStatePush();
    uvGfxSetFlags(0xC00000);
    uvGfxClearFlags(0x200000);
    uvGfx_80223A28(0xFFF);
    uvVtxBeginPoly();
    uvVtx(10, 18, 0, 0, 0, r, g, b, a);
    uvVtx(310, 18, 0, 0, 0, r, g, b, a);
    uvVtx(310, 232, 0, 0, 0, r, g, b, a);
    uvVtx(10, 232, 0, 0, 0, r, g, b, a);
    uvVtxEndPoly();
    uvGfxStatePop();
}

void hudText_8031D8E0(s16 arg0, f32 arg1, f32 arg2) {
    s16* temp_v0;
    s32 i;
    const u16 END_VALUE = -1;

    if (arg0 == -1) {
        gHudState.unkBD0[0] = -1;
        gHudState.unkC5E = -1;
        return;
    }

    temp_v0 = textGetDataByIdx(arg0);
    gHudState.unkC5E = arg0;
    if (gHudState.unkBD0[0] != -1) {
        gHudState.unkC58 = gHudState.unk14 + 0.2f;
    }

    for (i = 0; i < ARRAY_COUNT(gHudState.unkBD0); i++) {
        gHudState.unkBD0[i] = temp_v0[i];
        // temp_v0 is s16, so comparing with 0xFFFF is always false.
        // this is a bug that IDO does not warn about, but modern compilers do.
        if (temp_v0[i] == END_VALUE) {
            break;
        }
    }

    gHudState.unkC5C = 1;
    gHudState.unkC48 = arg1;
    gHudState.unkC4C = gHudState.unk14;
    gHudState.unkC50 = arg2;
}

void hudWarningText(s16 arg0, f32 arg1, f32 arg2) {
    s16* temp_v0;
    s16* var_a0;
    s32 i;
    const u16 END_VALUE = -1;

    if (arg0 == -1) {
        gHudState.unkB40[0] = -1;
        gHudState.unkBCE = -1;
        return;
    }

    temp_v0 = textGetDataByIdx(arg0);
    gHudState.unkBCE = arg0;
    if (gHudState.unkB40[0] != -1) {
        gHudState.unkBC8 = gHudState.unk14 + 0.2f;
    }

    for (i = 0; i < ARRAY_COUNT(gHudState.unkB40); i++) {
        gHudState.unkB40[i] = temp_v0[i];
        // temp_v0 is s16, so comparing with 0xFFFF is always false.
        // this is a bug that IDO does not warn about, but modern compilers do.
        if (temp_v0[i] == END_VALUE) {
            break;
        }
    }

    gHudState.unkBCC = 1;
    gHudState.unkBB8 = arg1;
    gHudState.unkBBC = gHudState.unk14;
    gHudState.unkBC0 = arg2;
}

s16 hudGet_8031DA90(void) {
    return gHudState.unkC5E;
}

s16 hudGet_8031DA9C(void) {
    return gHudState.unkBCE;
}

void hud_8031DAA8(u8 arg0, f32 arg1) {
    gHudState.unkC60 = arg0;
    gHudState.unkC64 = arg1;
    gHudState.unkC68 = (f32)gHudState.unk14;
    if (arg0 == 1) {
        hudDemoControllerEn(0);
    }
}

void hudDrawLowFuel(HUDState* hud) {
    if ((hud->unkB40[0] != -1) && !(gHudState.unk14 < hud->unkBC8)) {
        if (hud->unkBB8 < (gHudState.unk14 - hud->unkBBC)) {
            hud->unkBCE = -1;
            hud->unkB40[0] = -1;
            return;
        }
        uvFontSet(6);
        uvFont_80219550(1.0, 1.0);
        if (hud->unkBCC != 0) {
            uvFont_8021956C(0xFF, 0xFF, 0xFF, 0xFF); // white
        } else {
            uvFont_8021956C(0xFF, 0x00, 0x00, 0xFF); // red
        }
        func_80219874(160 - ((func_802196B0(&hud->unkB40[0]) - 16) / 2), 125, &hud->unkB40[0], 0x28, 0xFFE);
    }
}

void hudDrawStartText(HUDState* hud) {
    if ((hud->unkBD0[0] != -1) && !(gHudState.unk14 < hud->unkC58)) {
        if (hud->unkC48 < (gHudState.unk14 - hud->unkC4C)) {
            hud->unkC5E = -1;
            hud->unkBD0[0] = -1;
            return;
        }
        uvFontSet(6);
        uvFont_80219550(1.0, 1.0);
        if (hud->unkC5C != 0) {
            uvFont_8021956C(0xFF, 0xFF, 0xFF, 0xFF); // white
        } else {
            uvFont_8021956C(0x00, 0x28, 0xFF, 0xFF); // blue
        }
        func_80219874(160 - ((func_802196B0(&hud->unkBD0[0]) - 16) / 2), 140, &hud->unkBD0[0], 0x28, 0xFFE);
    }
}

void hudRadarThermal(f32 xOff, f32 yOff, f32 scale, u8 r, u8 g, u8 b, u8 a, f32 arg7) {
    s32 var_s0;
    s32 var_s1;
    s32 var_s2;
    f32 vx;
    f32 vy;
    Vec2F* temp_v0;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fv0;
    f32 temp_fv1;

    var_s0 = 0x10;
    var_s1 = 0;
    temp_fs0 = uvSinF(arg7);
    temp_fs1 = uvCosF(arg7);
    uvBeginTmesh();
    var_s2 = 0;
    do {
        if (var_s2 != 0) {
            temp_v0 = &gRadarThermCirc[var_s0];
            temp_fv0 = (temp_v0->x * scale) + xOff;
            temp_fv1 = (temp_v0->y * scale) + yOff;
            vx = (temp_fv0 * temp_fs1) - (temp_fv1 * temp_fs0);
            vy = (temp_fv0 * temp_fs0) + (temp_fv1 * temp_fs1);
            hud_8031E628(31.0f, &vx, &vy);
            uvVtx(vx, vy, 0, 0, 0, r, g, b, a);
            if (var_s0 <= 0) {
                var_s0 = 0x10;
            }
            var_s0 -= 1;
        } else {
            var_s1 += 1;
            if (var_s1 >= 0x10) {
                var_s1 = 0;
            }
            temp_v0 = &gRadarThermCirc[var_s1];
            temp_fv0 = (temp_v0->x * scale) + xOff;
            temp_fv1 = (temp_v0->y * scale) + yOff;
            vx = (temp_fv0 * temp_fs1) - (temp_fv1 * temp_fs0);
            vy = (temp_fv0 * temp_fs0) + (temp_fv1 * temp_fs1);
            hud_8031E628(31.0f, &vx, &vy);
            uvVtx(vx, vy, 0, 0, 0, r, g, b, a);
        }
        var_s2 = !var_s2;
    } while (var_s0 >= var_s1);
    uvEndTmesh();
}

// sets union field for camera state
void hudSetCameraState(s32 state) {
    gHudState.cameraState = state;
}

void hudRadarWaypoint(f32 dist, f32 bearing, s32 type, s32 below, f32 heading, u8 alpha) {
    Mtx4F sp70;
    u8 r;
    u8 g;
    s16 a;
    s16 pad1;
    s16 wptX;
    s16 wptY;
    s32 i;

    a = alpha;
    switch (type) {
    case 0:
        if (below) {
            r = 0x00, g = 0xFF; // green
        } else {
            r = 0xFF, g = 0xFF; // yellow
        }
        break;
    case 1:
    case 2:
        r = 0xFF, g = 0x00; // red
        break;
    default:
        return;
    }
    if (dist > 800.0f) {
        uvMat4SetIdentity(&sp70);
        uvMat4RotateAxis(&sp70, bearing, 'z');
        uvMat4UnkOp2(&sp70, 0.0f, 30.0f, 0.0f);
        uvGfxMtxViewMul(&sp70, 1);
        if (dist >= 1000.0f) {
            uvVtxBeginPoly();
            for (i = 0; i < 3; i++) {
                uvVtx(D_8034F95C[i].unk0 * 3, (D_8034F95C[i].unk2 * 3) + 1, 0, 0, 0, 0, 0, 0, a);
            }
            uvVtxEndPoly();

            uvVtxBeginPoly();
            for (i = 0; i < 3; i++) {
                uvVtx(D_8034F95C[i].unk0 * 2, (D_8034F95C[i].unk2 * 2) + 2, 0, 0, 0, r, g, 0, a);
            }
            uvVtxEndPoly();
        }
        if (dist >= 900.0f) {
            uvVtxBeginPoly();
            for (i = 0; i < 3; i++) {
                uvVtx(D_8034F95C[i].unk0 * 3, (D_8034F95C[i].unk2 * 3) - 1, 0, 0, 0, 0, 0, 0, a);
            }
            uvVtxEndPoly();

            uvVtxBeginPoly();
            for (i = 0; i < 3; i++) {
                uvVtx(D_8034F95C[i].unk0 * 2, D_8034F95C[i].unk2 * 2, 0, 0, 0, r, g, 0, a);
            }
            uvVtxEndPoly();
        }
        uvVtxBeginPoly();
        for (i = 0; i < 3; i++) {
            uvVtx(D_8034F95C[i].unk0 * 5, (D_8034F95C[i].unk2 * 5) - 5, 0, 0, 0, 0, 0, 0, a);
        }
        uvVtxEndPoly();

        uvVtxBeginPoly();
        for (i = 0; i < 3; i++) {
            uvVtx(D_8034F95C[i].unk0 * 4, (D_8034F95C[i].unk2 * 4) - 4, 0, 0, 0, r, g, 0, a);
        }
        uvVtxEndPoly();
        uvGfxMtxViewPop();
    } else {
        dist *= 0.0375f;
        wptX = (s16)(s32)(uvSinF(bearing) * -dist);
        wptY = (s16)(s32)(uvCosF(bearing) * dist);
        if (type != 2) {
            if (alpha > 150) {
                uvVtxBeginPoly();
                for (i = 0; i < 4; i++) {
                    uvVtx(D_8034F93C[i].unk0 * 3 + wptX, (D_8034F93C[i].unk2 * 3) + wptY, 0, 0, 0, 0, 0, 0, alpha);
                }
                uvVtxEndPoly();

                uvVtxBeginPoly();
                for (i = 0; i < 4; i++) {
                    uvVtx(D_8034F93C[i].unk0 * 2 + wptX, (D_8034F93C[i].unk2 * 2) + wptY, 0, 0, 0, r, g, 0, alpha);
                }
                uvVtxEndPoly();
            }
        } else {
            uvMat4SetIdentity(&sp70);
            uvMat4UnkOp2(&sp70, (f32)wptX, (f32)wptY, 0.0f);
            uvMat4RotateAxis(&sp70, heading, 'z');
            uvGfxMtxViewMul(&sp70, 1);

            uvVtxBeginPoly();
            for (i = 0; i < 4; i++) {
                uvVtx(D_8034F93C[i].unk0 * 3, D_8034F93C[i].unk2 * 6, 0, 0, 0, 0, 0, 0, a);
            }
            uvVtxEndPoly();

            uvVtxBeginPoly();
            for (i = 0; i < 4; i++) {
                uvVtx(D_8034F93C[i].unk0 * 2, D_8034F93C[i].unk2 * 5, 0, 0, 0, r, g, 0, a);
            }
            uvVtxEndPoly();
            uvGfxMtxViewPop();
        }
    }
}

void hud_8031E628(f32 arg0, f32* arg1, f32* arg2) {
    f32 a2tmp;
    f32 length;
    f32 a1tmp;
    f32 scale;

    a2tmp = *arg2;
    a1tmp = *arg1;
    length = uvSqrtF(SQ(a2tmp) + SQ(a1tmp));
    if (arg0 < length) {
        scale = arg0 / length;
        *arg1 *= scale;
        *arg2 *= scale;
    }
}

// draws open rectangle at location+bounds and pen width+color
void hudDrawRect(s32 x, s32 y, s32 width, s32 height, s32 penWidth, u8 r, u8 g, u8 b, u8 a) {
    uvVtxBeginPoly();
    uvVtx(x, y, 0, 0, 0, r, g, b, a);
    uvVtx(x + width, y, 0, 0, 0, r, g, b, a);
    uvVtx(x + width, y + penWidth, 0, 0, 0, r, g, b, a);
    uvVtx(x, y + penWidth, 0, 0, 0, r, g, b, a);
    uvVtxEndPoly();

    uvVtxBeginPoly();
    uvVtx(x, y, 0, 0, 0, r, g, b, a);
    uvVtx(x + penWidth, y, 0, 0, 0, r, g, b, a);
    uvVtx(x + penWidth, y + height, 0, 0, 0, r, g, b, a);
    uvVtx(x, y + height, 0, 0, 0, r, g, b, a);
    uvVtxEndPoly();

    uvVtxBeginPoly();
    uvVtx(x, y + height - penWidth, 0, 0, 0, r, g, b, a);
    uvVtx(x + width, y + height - penWidth, 0, 0, 0, r, g, b, a);
    uvVtx(x + width, y + height, 0, 0, 0, r, g, b, a);
    uvVtx(x, y + height, 0, 0, 0, r, g, b, a);
    uvVtxEndPoly();

    if (1) { // fakematch
        uvVtxBeginPoly();
        uvVtx(x + width - penWidth, y, 0, 0, 0, r, g, b, a);
        uvVtx(x + width, y, 0, 0, 0, r, g, b, a);
        uvVtx(x + width, y + height, 0, 0, 0, r, g, b, a);
        uvVtx(x + width - penWidth, y + height, 0, 0, 0, r, g, b, a);
        uvVtxEndPoly();
    }
}

void hudDrawPhotoCount(void) {
    char str[12];
    (void)snapGetPhotoCount();
    uvFontSet(8);
    uvFont_8021956C(0xFF, 0xFF, 0xFF, 0xFF);
    uvFont_80219550(1.0, 1.0);
    uvSprintf(str, "%d", snapGetPhotoCount());
    uvFont_80219ACC(0xA0, 30, str);
    uvSprtProps(0xA, 2, 150, 28, 7, 0xFF, 0xFF, 0xFF, 0xFF, 0);
    uvSprtDraw(0xA);
}

void hudDemoControllerEn(u8 enable) {
    gHudState.showController = enable;
}
