#include "common.h"

#include <uv_geometry.h>
#include <uv_graphics.h>
#include <uv_level.h>
#include <uv_math.h>
#include <uv_sprite.h>
#include <uv_string.h>
#include "code_C9440.h"
#include "hud.h"
#include "snap.h"

typedef struct {
    s16 unk0;
    s16 unk2;
} Unk8034F93C;

typedef struct {
    f32 unk0;
    f32 unk4;
} Unk8036C520;

extern f32 D_8034F910;
extern s32 D_8034F914;
extern s32 D_8034F938;
extern Unk8034F93C D_8034F93C[3];
extern Unk8034F93C D_8034F95C[4];

extern HUDState gHudState;

extern u8 D_8036D224;
extern Unk8036C520 D_8036C520[];

// forward declarations
void hud_8031A378(void);
void hud_8031E628(f32 arg0, f32* arg1, f32* arg2);
void hudDemoControllerEn(u8 enable);

void hudInit(void) {
    D_8034F914 = 0;
    D_8036D224 = 1;
    D_8034F910 = 0.0f;
    gHudState.unk0 = 0;
    gHudState.padC = 0;
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

#pragma GLOBAL_ASM("asm/nonmatchings/app/hud/hudMainRender.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/hud/hudDrawHangGlider.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/hud/hudDrawRocketPack.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/hud/hudDrawCannonball.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/hud/hudDrawSkyDiving.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/hud/hudDrawJumbleHopper.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/hud/hudDrawBirdman.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/hud/hud_80319FEC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/hud/hudDrawGyrocopter.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/hud/hud_8031A224.s")

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
    Unk8036C520* temp_v0;
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
            temp_fv0 = (temp_v0->unk0 * arg2) + arg0;
            temp_fv1 = (temp_v0->unk4 * arg2) + arg1;
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
            temp_fv0 = (temp_v0->unk0 * arg2) + arg0;
            temp_fv1 = (temp_v0->unk4 * arg2) + arg1;
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

void hud_8031DF74(f32 arg0, f32 arg1, s32 arg2, s32 arg3, f32 arg4, u8 arg5) {
    Mtx4F sp70;
    u8 sp6F;
    u8 sp6E;
    s16 tmp5;
    s16 pad1;
    s16 sp68;
    s16 sp66;
    s32 i;

    tmp5 = arg5;
    switch (arg2) {
    case 0:
        if (arg3 != 0) {
            sp6F = 0x00, sp6E = 0xFF;
        } else {
            sp6F = 0xFF, sp6E = 0xFF;
        }
        break;
    case 1:
    case 2:
        sp6F = 0xFF, sp6E = 0x00;
        break;
    default:
        return;
    }
    if (arg0 > 800.0f) {
        uvMat4SetIdentity(&sp70);
        uvMat4RotateAxis(&sp70, arg1, 'z');
        uvMat4UnkOp2(&sp70, 0.0f, 30.0f, 0.0f);
        uvGfxMtxViewMul(&sp70, 1);
        if (arg0 >= 1000.0f) {
            uvVtxBeginPoly();
            for (i = 0; i < 3; i++) {
                uvVtx(D_8034F95C[i].unk0 * 3, (D_8034F95C[i].unk2 * 3) + 1, 0, 0, 0, 0, 0, 0, tmp5);
            }
            uvVtxEndPoly();

            uvVtxBeginPoly();
            for (i = 0; i < 3; i++) {
                uvVtx(D_8034F95C[i].unk0 * 2, (D_8034F95C[i].unk2 * 2) + 2, 0, 0, 0, sp6F, sp6E, 0, tmp5);
            }
            uvVtxEndPoly();
        }
        if (arg0 >= 900.0f) {
            uvVtxBeginPoly();
            for (i = 0; i < 3; i++) {
                uvVtx(D_8034F95C[i].unk0 * 3, (D_8034F95C[i].unk2 * 3) - 1, 0, 0, 0, 0, 0, 0, tmp5);
            }
            uvVtxEndPoly();

            uvVtxBeginPoly();
            for (i = 0; i < 3; i++) {
                uvVtx(D_8034F95C[i].unk0 * 2, D_8034F95C[i].unk2 * 2, 0, 0, 0, sp6F, sp6E, 0, tmp5);
            }
            uvVtxEndPoly();
        }
        uvVtxBeginPoly();
        for (i = 0; i < 3; i++) {
            uvVtx(D_8034F95C[i].unk0 * 5, (D_8034F95C[i].unk2 * 5) - 5, 0, 0, 0, 0, 0, 0, tmp5);
        }
        uvVtxEndPoly();

        uvVtxBeginPoly();
        for (i = 0; i < 3; i++) {
            uvVtx(D_8034F95C[i].unk0 * 4, (D_8034F95C[i].unk2 * 4) - 4, 0, 0, 0, sp6F, sp6E, 0, tmp5);
        }
        uvVtxEndPoly();
        uvGfxMtxViewPop();
    } else {
        arg0 *= 0.0375f;
        sp68 = (s16)(s32)(uvSinF(arg1) * -arg0);
        sp66 = (s16)(s32)(uvCosF(arg1) * arg0);
        if (arg2 != 2) {
            if (arg5 > 150) {
                uvVtxBeginPoly();
                for (i = 0; i < 4; i++) {
                    uvVtx(D_8034F93C[i].unk0 * 3 + sp68, (D_8034F93C[i].unk2 * 3) + sp66, 0, 0, 0, 0, 0, 0, arg5);
                }
                uvVtxEndPoly();

                uvVtxBeginPoly();
                for (i = 0; i < 4; i++) {
                    uvVtx(D_8034F93C[i].unk0 * 2 + sp68, (D_8034F93C[i].unk2 * 2) + sp66, 0, 0, 0, sp6F, sp6E, 0, arg5);
                }
                uvVtxEndPoly();
            }
        } else {
            uvMat4SetIdentity(&sp70);
            uvMat4UnkOp2(&sp70, (f32)sp68, (f32)sp66, 0.0f);
            uvMat4RotateAxis(&sp70, arg4, 'z');
            uvGfxMtxViewMul(&sp70, 1);

            uvVtxBeginPoly();
            for (i = 0; i < 4; i++) {
                uvVtx(D_8034F93C[i].unk0 * 3, D_8034F93C[i].unk2 * 6, 0, 0, 0, 0, 0, 0, tmp5);
            }
            uvVtxEndPoly();

            uvVtxBeginPoly();
            for (i = 0; i < 4; i++) {
                uvVtx(D_8034F93C[i].unk0 * 2, D_8034F93C[i].unk2 * 5, 0, 0, 0, sp6F, sp6E, 0, tmp5);
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
    uvFont_80219ACC(0xA0, 0x1E, str);
    uvSprtProps(0xA, 2, 0x96, 0x1C, 7, 0xFF, 0xFF, 0xFF, 0xFF, 0);
    uvSprtDraw(0xA);
}

void hudDemoControllerEn(u8 enable) {
    gHudState.showController = enable;
}
