#include "common.h"

#include <uv_geometry.h>
#include <uv_graphics.h>
#include <uv_level.h>
#include <uv_math.h>
#include <uv_matrix.h>
#include <uv_sprite.h>
#include <uv_string.h>
#include <uv_vector.h>
#include "code_68220.h"
#include "code_9A960.h"
#include "code_C9440.h"
#include "hud.h"
#include "snap.h"
#include "snd.h"

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

extern u8 D_8036D224;
extern Vec2F D_8036C520[16];
extern Vec2F D_8036C5A0[]; // guess

// forward declarations
void hud_8031A378(void);
void hud_8031E628(f32 arg0, f32* arg1, f32* arg2);
void hudDemoController(void);
void hudDrawBirdman(HUDState*);
void hudDrawBox(HUDState*);
void hudDrawCannonball(HUDState*);
void hudDrawGyrocopter(HUDState*);
void hudDrawHangGlider(HUDState*);
void hudDrawJumbleHopper(HUDState*);
void hudDrawLowFuel(HUDState*);
void hudDrawRocketPack(HUDState*);
void hudDrawSkyDiving(HUDState*);
void hudDrawStartText(HUDState*);
void hudDrawPhotoCount(void);
void hudSeaLevel(s32 x, s32 y, s32 alt);
void hudDrawSpeed(s32 x, s32 y, s32, s32);
void hud_8031C900(s32 x, s32 y, s32);
void hud_80319FEC(HUDState* hud);
void hudDrawFuel(s32 x, s32 y, s32);
void hudDrawRadar(s32 x, s32 y, f32, f32, f32, f32, f32*);
void hudDrawThrottle(s32 x, s32 y, f32);
void hudMissileReticle(s32 x, s32 y, s32 flag);
void hudTimer(s32 x, s32 y, f32 timeSecF);

void hudInit(void) {
    D_8034F914 = 0;
    D_8036D224 = 1;
    D_8034F910 = 0.0f;
    gHudState.unk0 = 0;
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
    Vec3F sp4C;
    HUDState* hud;
    s32 pad[2];

    hud = &gHudState;
    if ((hud->unk0 & 0x400) == 0x0) {
        if ((hud->unkC50 != 0.0f) && (hud->unkC54 < gHudState.unk14)) {
            hud->unkC5C = !hud->unkC5C;
            hud->unkC54 = (1.0f / hud->unkC50) + gHudState.unk14;
        }
        if ((hud->unkBC0 != 0.0f) && (hud->unkBC4 < gHudState.unk14)) {
            hud->unkBCC = !hud->unkBCC;
            hud->unkBC4 = (1.0f / hud->unkBC0) + gHudState.unk14;
        }
        if (gHudState.unk0 & 0xFE) {
            if (gHudState.unk28.m[0][0] != 0.0f) {
                func_80313570(&gHudState.unk28, &gHudState.unk68, &gHudState.unk6C, &gHudState.unk70, &gHudState.unk74, &gHudState.unk78, &gHudState.unk7C);
            } else {
                gHudState.unk70 = 0.0f;
                gHudState.unk7C = 0.0f;
                gHudState.unk6C = (f32)gHudState.unk70;
                gHudState.unk78 = (f32)gHudState.unk7C;
                gHudState.unk68 = (f32)gHudState.unk6C;
                gHudState.unk74 = (f32)gHudState.unk78;
            }
            func_802E1754(gHudState.unk68, gHudState.unk6C, gHudState.unk70, &sp4C);
            if ((sp4C.x == 0.0f) && (sp4C.y == 0.0f)) {
                gHudState.unkB38 = 0.0f;
                gHudState.unkB3C = (f32)gHudState.unkB38;
            } else {
                gHudState.unkB3C = uvSqrtF((sp4C.x * sp4C.x) + (sp4C.y * sp4C.y));
                gHudState.unkB38 = uvAtan2F(-sp4C.x / gHudState.unkB3C, sp4C.y / gHudState.unkB3C);
                gHudState.unkB3C = (f32)(gHudState.unkB3C / 5.0f);
                if (gHudState.unkB3C < 0.0f) {
                    gHudState.unkB3C = 0.0f;
                } else if (gHudState.unkB3C > 0.88945f) {
                    gHudState.unkB3C = 0.88945f;
                }
                gHudState.unkB38 = (f32)(gHudState.unkB38 - gHudState.unk74);
                if (gHudState.unkB38 > 3.1415927f) {
                    gHudState.unkB38 = (f32)(gHudState.unkB38 - 6.2831855f);
                }
                if (gHudState.unkB38 <= 3.1415927f) {
                    gHudState.unkB38 = (f32)(gHudState.unkB38 + 6.2831855f);
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
            if (gHudState.unk0 & 0x02) {
                hudDrawHangGlider(&gHudState);
            } else if (gHudState.unk0 & 0x04) {
                hudDrawRocketPack(&gHudState);
            } else if (gHudState.unk0 & 0x08) {
                hudDrawGyrocopter(&gHudState);
            } else if (gHudState.unk0 & 0x10) {
                hudDrawCannonball(&gHudState);
            } else if (gHudState.unk0 & 0x20) {
                hudDrawSkyDiving(&gHudState);
            } else if (gHudState.unk0 & 0x40) {
                hudDrawJumbleHopper(&gHudState);
            } else if (gHudState.unk0 & 0x80) {
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
    hudDrawSpeed(27, 37, (s32)hud->unk88, 1);
    hudSeaLevel(235, 37, (s32)hud->unk84);
    hud_8031C900(250, 129, (s32)hud->unk80);
    hudDrawRadar(215, 222, hud->unk68, hud->unk6C, hud->unk70, hud->unk74, &hud->unk90);
    hudTimer(27, 222, hud->unk10);
    hud_80319FEC(hud);
}

void hudDrawRocketPack(HUDState* hud) {
    hudSeaLevel(235, 37, (s32)hud->unk84);
    hud_8031C900(250, 129, (s32)hud->unk80);
    hudDrawRadar(215, 222, hud->unk68, hud->unk6C, hud->unk70, hud->unk74, &hud->unk90);
    hudDrawSpeed(27, 37, (s32)hud->unk88, 0);
    hudDrawFuel(98, 37, hud->pad1C);
    hudTimer(27, 222, hud->unk10);
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/hud/hudDrawCannonball.s")

void hudDrawSkyDiving(HUDState* hud) {
    if (hud->unk4 != 0) {
        uvGfxStatePush();
        uvGfxSetFlags(0x800FFF);
        uvVtxBeginPoly();
        uvVtx(10, 18, 0, 0, 0, 0xFF, 0xFF, 0xFF, hud->unk4);
        uvVtx(310, 18, 0, 0, 0, 0xFF, 0xFF, 0xFF, hud->unk4);
        uvVtx(310, 232, 0, 0, 0, 0xFF, 0xFF, 0xFF, hud->unk4);
        uvVtx(10, 232, 0, 0, 0, 0xFF, 0xFF, 0xFF, hud->unk4);
        uvVtxEndPoly();
        uvGfxStatePop();
    } else {
        hud_8031C900(250, 129, (s32)hud->unk80);
        hudSeaLevel(235, 37, (s32)hud->unk84);
        hudTimer(27, 222, hud->unk10);
        hudDrawRadar(215, 222, hud->unk68, hud->unk6C, hud->unk70, hud->unk74, &hud->unk90);
    }
}

void hudDrawJumbleHopper(HUDState* hud) {
    hudDrawSpeed(27, 37, (s32)hud->unk88, 0);
    hudSeaLevel(235, 37, (s32)hud->unk84);
    hud_8031C900(250, 129, (s32)hud->unk80);
    hudDrawRadar(215, 222, hud->unk68, hud->unk6C, hud->unk70, hud->unk74, &hud->unk90);
    hudTimer(27, 222, hud->unk10);
}

void hudDrawBirdman(HUDState* hud) {
    if (D_80362690->unk0[D_80362690->unk9C].unkC.unk7B == 0) {
        hudDrawPhotoCount();
    }
    hudSeaLevel(235, 37, (s32)hud->unk84);
    hud_8031C900(250, 129, (s32)hud->unk80);
    hudDrawSpeed(27, 37, (s32)hud->unk88, 0);
    if (D_80362690->unk0[D_80362690->unk9C].unkC.unk7B == 0) {
        hud_80319FEC(hud);
    }
}

#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/nonmatchings/app/hud/hud_80319FEC.s")
#else
void hud_80319FEC(HUDState* hud) {
    s32 x;

    if (hud->unk4 & 0x80000000) {
        uvSprtProps(9, 2, 0x5F, 0xAF, 7, 0xFF, 0, 0, 0x78, 0);
        uvSprtDraw(9);
        if (D_8034F914 == 0) {
            func_8033F7F8(0x43);
            D_8034F914 = 1;
        }
    } else if (hud->unk4 & 0x40000000) {
        hud->unk4 = 3;
    } else if (hud->unk4 != 0) {
        if (hud->unk4 != 0) {
            x = (hud->unk4 * -80) + 240;
        } else {
            x = hud->unk4 * 80;
        }
        uvGfx_80223A28(0xFFF);
        uvVtxRect(0, 239, x, 0);
        uvVtxRect(319 - x, 239, 319, 0);
        hud->unk4--;
        D_8034F914 = 0;
    }
}
#endif

void hudDrawGyrocopter(HUDState* hud) {
    hudDrawSpeed(27, 37, (s32)hud->unk88, 0);
    hudSeaLevel(235, 37, (s32)hud->unk84);
    hud_8031C900(250, 129, (s32)hud->unk80);
    hudDrawRadar(215, 222, hud->unk68, hud->unk6C, hud->unk70, hud->unk74, &hud->unk90);
    hudDrawFuel(98, 37, hud->pad1C);
    hudDrawThrottle(27, 82, hud->unk18);
    hudTimer(27, 222, hud->unk10);
    if (hud->unk0 & 0x200) {
        hudMissileReticle((s32)hud->unkC6C, (s32)hud->unkC70, 0);
    }
}

#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/nonmatchings/app/hud/hud_8031A224.s")
#else
void hud_8031A224(void) {
    f32 angle;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_8036C520); i++) {
        angle = (f32)i * 0.3926991f; // DEG_TO_RAD(22.5) or (360.0/16)
        D_8036C520[i].x = uvSinF(angle);
        D_8036C520[i].y = uvCosF(angle);
    }
    D_8036C5A0[0] = D_8036C520[0];
}
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/app/hud/hud_8031A2CC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/hud/hud_8031A378.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/hud/hud_8031A66C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/hud/hud_8031A6C8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/hud/hud_8031A794.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/hud/hud_8031A810.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/hud/hud_8031A874.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/hud/hud_8031A8E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/hud/hudDrawThrottle.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/hud/hudDrawRadar.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/hud/hud_8031BE88.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/hud/hudDemoController.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/hud/hudDrawSpeed.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/hud/hudDrawFuel.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/hud/hud_8031C900.s")

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
#pragma GLOBAL_ASM("asm/nonmatchings/app/hud/hudTimer.s")
#else
void hudTimer(s32 x, s32 y, f32 timeSecF) {
    s32 timeMs;     // var_v1;
    s32 timeHundth; // temp_a0;
    s32 temp_v1;
    s32 timeSec;   // temp_lo;
    s32 adjHundth; // sp44;
    char timeStr[12];
    s32* ptr;

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
    timeHundth = (timeMs / 10) - (timeSec * 100);
    if ((timeMs != 3599999) && (timeSecF != 0.0f) && adjHundth) {
        temp_v1 = D_8034F938;
        if (temp_v1 >= 4) {
            temp_v1 = 0;
        }
        temp_v1 += 1;
        timeHundth += temp_v1;
        D_8034F938 = temp_v1;
        if (timeHundth >= 100) {
            timeHundth -= 100;
        }
    }
    uvSprtProps(4, 2, x, y, 7, 0xFF, 0xFF, 0xFF, 0xFF, 0);
    uvSprtDraw(4);
    uvFontSet(8);
    x += 36;
    y -= 12;
    uvFont_8021956C(0xFF, 0xFF, 0xFF, 0xFF);
    uvFont_80219550(1.0, 1.0);
    uvSprintf(timeStr, "%02d'%02d\"%02d", timeSec / 60, timeSec - ((timeSec / 60) * 60), timeHundth);
    uvFont_80219ACC(x, y, timeStr);
}
#endif

void hudMissileReticle(s32 x, s32 y, s32 flag) {
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

    temp_v0 = func_80342198(arg0);
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

    temp_v0 = func_80342198(arg0);
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

void hudRadarThermal(f32 arg0, f32 arg1, f32 arg2, u8 r, u8 g, u8 b, u8 a, f32 arg7) {
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
            temp_v0 = &D_8036C520[var_s0];
            temp_fv0 = (temp_v0->x * arg2) + arg0;
            temp_fv1 = (temp_v0->y * arg2) + arg1;
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
            temp_v0 = &D_8036C520[var_s1];
            temp_fv0 = (temp_v0->x * arg2) + arg0;
            temp_fv1 = (temp_v0->y * arg2) + arg1;
            vx = (temp_fv0 * temp_fs1) - (temp_fv1 * temp_fs0);
            vy = (temp_fv0 * temp_fs0) + (temp_fv1 * temp_fs1);
            hud_8031E628(31.0f, &vx, &vy);
            uvVtx(vx, vy, 0, 0, 0, r, g, b, a);
        }
        var_s2 = !var_s2;
    } while (var_s0 >= var_s1);
    uvEndTmesh();
}

void hud_8031DF68(s32 arg0) {
    gHudState.unk4 = arg0;
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

void hud_8031E69C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8) {
    uvVtxBeginPoly();
    uvVtx(arg0, arg1, 0, 0, 0, arg5, arg6, arg7, arg8);
    uvVtx(arg0 + arg2, arg1, 0, 0, 0, arg5, arg6, arg7, arg8);
    uvVtx(arg0 + arg2, arg1 + arg4, 0, 0, 0, arg5, arg6, arg7, arg8);
    uvVtx(arg0, arg1 + arg4, 0, 0, 0, arg5, arg6, arg7, arg8);
    uvVtxEndPoly();

    uvVtxBeginPoly();
    uvVtx(arg0, arg1, 0, 0, 0, arg5, arg6, arg7, arg8);
    uvVtx(arg0 + arg4, arg1, 0, 0, 0, arg5, arg6, arg7, arg8);
    uvVtx(arg0 + arg4, arg1 + arg3, 0, 0, 0, arg5, arg6, arg7, arg8);
    uvVtx(arg0, arg1 + arg3, 0, 0, 0, arg5, arg6, arg7, arg8);
    uvVtxEndPoly();

    uvVtxBeginPoly();
    uvVtx(arg0, arg1 + arg3 - arg4, 0, 0, 0, arg5, arg6, arg7, arg8);
    uvVtx(arg0 + arg2, arg1 + arg3 - arg4, 0, 0, 0, arg5, arg6, arg7, arg8);
    uvVtx(arg0 + arg2, arg1 + arg3, 0, 0, 0, arg5, arg6, arg7, arg8);
    uvVtx(arg0, arg1 + arg3, 0, 0, 0, arg5, arg6, arg7, arg8);
    uvVtxEndPoly();

    if (1) { // fakematch
        uvVtxBeginPoly();
        uvVtx(arg0 + arg2 - arg4, arg1, 0, 0, 0, arg5, arg6, arg7, arg8);
        uvVtx(arg0 + arg2, arg1, 0, 0, 0, arg5, arg6, arg7, arg8);
        uvVtx(arg0 + arg2, arg1 + arg3, 0, 0, 0, arg5, arg6, arg7, arg8);
        uvVtx(arg0 + arg2 - arg4, arg1 + arg3, 0, 0, 0, arg5, arg6, arg7, arg8);
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
