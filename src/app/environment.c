#include "app/cannonball.h"
#include "common.h"
#include "demo.h"
#include "environment.h"
#include "game.h"
#include "hud.h"
#include "jumble_hopper.h"
#include "kernel/code_8170.h"
#include "proxanim.h"
#include "shadow.h"
#include "snd.h"
#include "task.h"
#include "thermals.h"
#include "wind.h"
#include "wind_objects.h"
#include <uv_environment.h>
#include <uv_event.h>
#include <uv_geometry.h>
#include <uv_graphics.h>
#include <uv_math.h>
#include <uv_memory.h>
#include <uv_texture.h>

typedef struct {
    Vec3F unk0;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
} Unk80359D80; // size = 0x34

Unk80359D80 D_80359D80;
u8 D_80359DB4;

u8 D_8034EEE0[][3] = {
    { 0x63, 0x55, 0x55 },
    { 0x46, 0x52, 0x5D },
    { 0x46, 0x52, 0x5D },
    { 0x7B, 0x62, 0x52 },
    { 0x76, 0x5E, 0x4A },
    { 0x7D, 0x6A, 0x55 },
    { 0x76, 0x5E, 0x4A },
    { 0x7B, 0x62, 0x52 },
    { 0x63, 0x55, 0x55 }
};

f32 D_8034EEFC[] = { -180.0f, -170.0f, -12.0f, 40.0f, 65.0f, 90.0f, 105.0f, 140.0f, 180.0f };

// forward declarations
void env_802E1A80(s32);
void env_802E1C1C(s32);
void env_802E23E0(void);
void env_802E2504(void);

s32 env_802E0CF0(void) {
    f32 pad_sp174;
    f32 sp170;
    f32 sp16C;
    f32 pad_sp168;
    f32 pad_sp164;
    s32 pad_sp160;
    Vec3F sp154;
    f32 var_fv0;
    f32 sp14C;
    f32 sp148;
    Vec3F sp13C;
    Vec3F sp130;
    u8 pad[0x130 - 0x100]; // what's supposed to go here?
    f32 spFC;
    f32 spF8;
    f32 spF4;
    f32 var_fa1;
    f32 spEC;
    f32 spE8;
    Mtx4F spA8;
    Mtx4F sp68;
    f32 var_ft4;
    f32 sp60;
    f32 sp5C;
    f32 pad_sp58;
    f32 sp54;
    f32 sp50;
    Camera* sp4C;
    u8 sp4B;
    u8 sp4A;
    u8 sp49;
    u8 sp48;
    f32 sp3C;
    f32 sp38;

    uvEnvProps(D_80362690->envId, 3, 0.0f, 0);
    uvMat4SetIdentity(&spA8);
    sp4C = D_80362690->unkC[D_80362690->unk9C].unk70;
    uvMat4Copy(&sp68, &sp4C->unk108);
    sp154.x = sp68.m[1][0];
    sp154.y = sp68.m[1][1];
    sp154.z = sp68.m[1][2];
    sp130.x = sp68.m[0][0];
    sp130.y = sp68.m[0][1];
    sp130.z = 0.0f;
    uvVec3Cross(&sp13C, &sp130, &sp154);
    uvVec3Normal(&sp13C, &sp13C);
    spF4 = sp68.m[3][0] + ((0.875f * sp4C->unk40) * sp154.x);
    spF8 = sp68.m[3][1] + ((0.875f * sp4C->unk40) * sp154.y);
    spFC = sp68.m[3][2] + ((0.875f * sp4C->unk40) * sp154.z);
    spE8 = ((0.875f * sp4C->unk40) * sp13C.x) + spF4;
    spEC = ((0.875f * sp4C->unk40) * sp13C.y) + spF8;
    var_fa1 = ((0.875f * sp4C->unk40) * sp13C.z) + spFC;
    sp60 = spE8 - spF4;
    sp5C = spEC - spF8;
    var_fv0 = var_fa1 - spFC;
    if (var_fv0 < (sp4C->unk40 * 0.1)) {
        uvEnvProps(D_80362690->envId, 3, 0.996f, 0);
        return 0;
    }

    if (var_fv0 == 0.0f) {
        sp54 = 0.0f;
    } else {
        sp54 = -spFC / var_fv0;
    }
    sp16C = (sp54 * sp60) + spF4;
    sp170 = (sp54 * sp5C) + spF8;
    spF4 = sp68.m[3][0] + (sp4C->unk40 * sp154.x);
    spF8 = sp68.m[3][1] + (sp4C->unk40 * sp154.y);
    spFC = sp68.m[3][2] + (sp4C->unk40 * sp154.z);
    spE8 = (sp4C->unk40 * sp13C.x) + spF4;
    spEC = (sp4C->unk40 * sp13C.y) + spF8;
    var_fa1 = (sp4C->unk40 * sp13C.z) + spFC;
    if (var_fa1 == spFC) {
        sp54 = 0.0f;
    } else {
        sp54 = -spFC / (var_fa1 - spFC);
    }
    var_fa1 = 1.0f / sp4C->unk20;
    var_ft4 = (sp4C->unk30 * (var_fa1));
    sp38 = 2.0f * (sp4C->unk40 * var_ft4);
    sp148 = sp154.y * sp38;
    sp14C = -sp154.x * sp38;
    sp38 = sp68.m[3][2] / 15.0f;
    if (sp38 < 15.0f) {
        sp50 = 15.0f;
    } else {
        sp50 = sp38;
    }
    uvEnvProps2(D_80362690->envId, 1, &sp4B, &sp4A, &sp49, &sp48, 0);
    uvGfxStatePush();
    uvGfxSetFlags(GFX_STATE_XLU | GFX_STATE_AA | GFX_STATE_GOURAUD | GFX_STATE_TEXTURE_NONE);
    uvGfxClearFlags(GFX_STATE_DECAL | GFX_STATE_ZBUFFER);
    uvGfx_802236CC(&spA8);
    uvVtxBeginPoly();
    sp3C = ((0, sp54) * (spE8 - spF4)) + spF4;
    sp38 = ((0, sp54) * (spEC - spF8)) + spF8;
    uvVtx((sp3C + sp148), (sp38 + sp14C), sp50, 0, 0, sp4B, sp4A, sp49, 0xFF);
    uvVtx((sp3C - sp148), (sp38 - sp14C), sp50, 0, 0, sp4B, sp4A, sp49, 0xFF);
    sp3C = 0.0f;
    uvVtx((sp16C - sp148), (sp170 - sp14C), sp3C, 0, 0, sp4B, sp4A, sp49, 0);
    uvVtx((sp16C + sp148), (sp170 + sp14C), sp3C, 0, 0, sp4B, sp4A, sp49, 0);
    uvVtxEndPoly();
    uvGfxMtxViewPop();
    uvGfxStatePop();
    uvEnvProps(D_80362690->envId, 3, 0.996f, 0);
    return 0;
}

void envInit(void) {
    Vec3F sp24;

    sp24.f[0] = 0.0f;
    sp24.f[1] = 0.0f;
    sp24.f[2] = 0.0f;
    env_802E14E8(&sp24, 0.0f, 0.0f, 0.0f, 0.0f);
}

void envLoad(void) {
    TaskObjects_Unk10* temp_v0;

    temp_v0 = taskGet_80345AEC();
    env_802E14E8(&temp_v0->unk0, temp_v0->unkC, temp_v0->unk10, temp_v0->unk14, temp_v0->unk18);
}

s32 envGetCurrentId(void) {
    u8* temp_v0;
    s32 ret;

    ret = 22;
    temp_v0 = taskGet_80345CB0();
    switch (D_80362690->map) {
    case MAP_HOLIDAY_ISLAND:
        switch (*temp_v0) {
        case 0:
            ret = 2;
            break;
        case 1:
            ret = 3;
            break;
        case 2:
            ret = 4;
            break;
        case 4:
            ret = 5;
            break;
        case 5:
            ret = 6;
            break;
        }
        break;
    case MAP_CRESCENT_ISLAND:
        switch (*temp_v0) {
        case 0:
            ret = 7;
            break;
        case 1:
            ret = 8;
            break;
        case 2:
            ret = 9;
            break;
        case 3:
            ret = 10;
            break;
        case 5:
            ret = 11;
            break;
        }
        break;
    case MAP_LITTLE_STATES:
        switch (*temp_v0) {
        case 0:
            ret = 12;
            break;
        case 1:
            ret = 13;
            break;
        case 2:
            ret = 14;
            break;
        case 3:
            ret = 15;
            break;
        case 4:
            ret = 16;
            break;
        case 5:
            ret = 17;
            break;
        }
        break;
    case MAP_EVER_FROST_ISLAND:
        switch (*temp_v0) {
        case 3:
        case 4:
            break;
        case 0:
            ret = 18;
            break;
        case 1:
            ret = 19;
            break;
        case 2:
            ret = 20;
            break;
        case 5:
            ret = 21;
            break;
        }
        break;
    }
    return ret;
}

void env_802E1444(s32 envId) {
    u8* temp_v0;

    temp_v0 = taskGet_80345CB0();
    if (envId == 22) {
        _uvDebugPrintf("env : bad environment specification  lev:%d cond:%d\n", D_80362690->map, *temp_v0);
        return;
    }

    env_802E1A80(envId);
    env_802E1C1C(envId);
    uvChanEnv(D_80362690->unkC[D_80362690->unk9C].unk70->unk22C, envId);
    D_80362690->envId = envId;
}

void env_802E14E8(Vec3F* arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    D_80359D80.unk0.f[0] = arg0->f[0];
    D_80359D80.unk0.f[1] = arg0->f[1];
    D_80359D80.unk0.f[2] = arg0->f[2];
    D_80359D80.unk10 = uvVec3Len(arg0);
    if (D_80359D80.unk10 > 0.0f) {
        D_80359D80.unkC = uvAtan2F(-arg0->f[1] / D_80359D80.unk10, arg0->f[0] / D_80359D80.unk10) - 1.5707963f;
    } else {
        D_80359D80.unkC = 0.0f;
    }
    D_80359D80.unk14 = arg1;
    D_80359D80.unk18 = arg2;
    D_80359D80.unk1C = D_80359D80.unk10 - D_80359D80.unk14;
    D_80359D80.unk20 = D_80359D80.unk10 + D_80359D80.unk14;
    D_80359D80.unk24 = arg3 * 0.01745329f;
    D_80359D80.unk28 = arg4 * 0.01745329f;
    D_80359D80.unk2C = D_80359D80.unkC - D_80359D80.unk24;
    D_80359D80.unk30 = D_80359D80.unkC + D_80359D80.unk24;
}

void env_802E15F0(void) {
    f32 var_fv1;

    var_fv1 = (demoRandF() - 0.5f) * D_80359D80.unk18 * D_8034F854;
    if ((D_80359D80.unk20 < D_80359D80.unk10) && (var_fv1 > 0.0f)) {
        var_fv1 = -var_fv1;
    }
    if ((D_80359D80.unk10 < D_80359D80.unk1C) && (var_fv1 < 0.0f)) {
        var_fv1 = -var_fv1;
    }
    D_80359D80.unk10 += var_fv1;
    var_fv1 = (demoRandF() - 0.5f) * D_80359D80.unk28 * D_8034F854;
    if ((D_80359D80.unk30 < D_80359D80.unkC) && (var_fv1 > 0.0f)) {
        var_fv1 = -var_fv1;
    }
    if ((D_80359D80.unkC < D_80359D80.unk2C) && (var_fv1 < 0.0f)) {
        var_fv1 = -var_fv1;
    }
    D_80359D80.unkC += var_fv1;
    D_80359D80.unk0.f[0] = uvSinF(D_80359D80.unkC) * D_80359D80.unk10;
    D_80359D80.unk0.f[1] = uvCosF(D_80359D80.unkC) * D_80359D80.unk10;
    env_802E2060();
    env_802E23E0();
}

void env_802E1754(f32 arg0, f32 arg1, f32 arg2, Vec3F* arg3) {
    Vec3F sp44;
    Vec3F sp38;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    ParsedUVTR* temp_v0;
    f32 temp_fv0;

    wind_8034D550(arg0, arg1, arg2, &sp44);
    therm_80346C08(arg0, arg1, arg2, &sp38);
    sp34 = 0.0f;
    sp30 = 0.0f;
    sp2C = 0.0f;
    temp_v0 = uvTerraGetBox(D_80362690->terraId);
    if (temp_v0 == NULL) {
        _uvDebugPrintf("env : no bbox for terra [%d]\n", D_80362690->terraId);
    } else {
        temp_fv0 = (temp_v0->unk0.unk0 - 2050.0f) - arg0;
        if (temp_fv0 > 0.0f) {
            sp2C = (50.0f * temp_fv0) / 2050.0f;
        }
        temp_fv0 = arg0 - (temp_v0->unk0.unkC + 2050.0f);
        if (temp_fv0 > 0.0f) {
            sp2C = (-50.0f * temp_fv0) / 2050.0f;
        }
        temp_fv0 = (temp_v0->unk0.unk4 - 2050.0f) - arg1;
        if (temp_fv0 > 0.0f) {
            sp30 = (50.0f * temp_fv0) / 2050.0f;
        }
        temp_fv0 = arg1 - (temp_v0->unk0.unk10 + 2050.0f);
        if (temp_fv0 > 0.0f) {
            sp30 = (-50.0f * temp_fv0) / 2050.0f;
        }
    }

    if (D_80362690->unkC[D_80362690->unk9C].unk8 == 0) {
        arg3->x = sp44.x + sp38.x + D_80359D80.unk0.x + sp2C;
        arg3->y = sp44.y + sp38.y + D_80359D80.unk0.y + sp30;
        arg3->z = sp44.z + sp38.z + D_80359D80.unk0.z + sp34;
    } else {
        arg3->x = sp44.x + sp38.x;
        arg3->y = sp44.y + sp38.y;
        arg3->z = sp44.z + sp38.z;
    }
}

void envLoadTerrainPal(s32 envId) {
    u8* temp_v0;

    temp_v0 = taskGet_80345CB0();
    if (envId == 22) {
        _uvDebugPrintf("env : bad environment specification  lev:%d cond:%d\n", D_80362690->map, *temp_v0);
    }
    switch (envId) {
    case 6:
        uvMemLoadPal(0);
        break;
    case 11:
        uvMemLoadPal(1);
        break;
    case 17:
        uvMemLoadPal(2);
        break;
    case 18:
        uvMemLoadPal(5);
        break;
    case 19:
        uvMemLoadPal(5);
        break;
    case 20:
        uvMemLoadPal(4);
        break;
    case 21:
        uvMemLoadPal(3);
        break;
    case 2:
    case 3:
    case 4:
    case 5:
    case 7:
    case 8:
    case 9:
    case 10:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 22:
        break;
    default:
        _uvDebugPrintf("env_loadtpal : unknown environment %d\n", envId);
        break;
    }
}

void env_802E1A80(s32 envId) {
    switch (envId) {
    case 22:
        uvLevelAppend(0x86);
        break;
    case 2:
        uvLevelAppend(0x72);
        break;
    case 3:
        uvLevelAppend(0x73);
        break;
    case 4:
        uvLevelAppend(0x74);
        break;
    case 5:
        uvLevelAppend(0x75);
        break;
    case 6:
        uvLevelAppend(0x76);
        break;
    case 7:
        uvLevelAppend(0x77);
        break;
    case 8:
        uvLevelAppend(0x78);
        break;
    case 9:
        uvLevelAppend(0x79);
        break;
    case 10:
        uvLevelAppend(0x7A);
        break;
    case 11:
        uvLevelAppend(0x7B);
        break;
    case 12:
        uvLevelAppend(0x7C);
        break;
    case 13:
        uvLevelAppend(0x7D);
        break;
    case 14:
        uvLevelAppend(0x7E);
        break;
    case 15:
        uvLevelAppend(0x7F);
        break;
    case 16:
        uvLevelAppend(0x80);
        break;
    case 17:
        uvLevelAppend(0x81);
        break;
    case 18:
        uvLevelAppend(0x82);
        break;
    case 19:
        uvLevelAppend(0x83);
        break;
    case 20:
        uvLevelAppend(0x84);
        break;
    case 21:
        uvLevelAppend(0x85);
        break;
    default:
        _uvDebugPrintf("error : unknown environment %d\n", envId);
        break;
    }
}

void env_802E1C1C(s32 envId) {
    switch (envId) {
    case 4:
        func_8020F99C(1, 1.0f, 0.0f, 0.0f);
        func_8020F5A4(1, 0.0f, 0.5f, 0.2f);
        break;
    case 5:
        func_8020F99C(0, 0.75f, 0.4f, 0.2f);
        func_8020F5A4(0, 0.3f, 0.3f, 0.3f);
        func_8020F99C(1, 1.0f, 0.0f, 0.0f);
        func_8020F5A4(1, 0.0f, 0.5f, 0.2f);
        break;
    case 6:
        func_8020F99C(0, 0.7f, 0.7f, 1.0f);
        func_8020F630(0);
        func_8020F99C(1, 1.0f, 0.0f, 0.0f);
        func_8020F5A4(1, 0.0f, 0.5f, 0.0f);
        break;
    case 9:
        func_8020F99C(1, 1.0f, 0.0f, 0.0f);
        func_8020F5A4(1, 0.0f, 0.5f, 0.2f);
        break;
    case 10:
        func_8020F99C(1, 1.0f, 0.0f, 0.0f);
        func_8020F5A4(1, 0.0f, 0.5f, 0.2f);
        break;
    case 11:
        func_8020F99C(0, 0.7f, 0.7f, 1.0f);
        func_8020F630(0);
        func_8020F99C(1, 1.0f, 0.0f, 0.0f);
        func_8020F5A4(1, 0.0f, 0.5f, 0.15f);
        break;
    case 14:
        func_8020F99C(1, 1.0f, 0.0f, 0.0f);
        func_8020F5A4(1, 0.0f, 0.5f, 0.2f);
        break;
    case 15:
        func_8020F99C(1, 1.0f, 0.0f, 0.0f);
        func_8020F5A4(1, 0.0f, 0.5f, 0.2f);
        break;
    case 16:
        func_8020F99C(0, 0.75f, 0.4f, 0.2f);
        func_8020F5A4(0, 0.3f, 0.3f, 0.3f);
        func_8020F99C(1, 1.0f, 0.0f, 0.0f);
        func_8020F5A4(1, 0.0f, 0.5f, 0.2f);
        break;
    case 17:
        func_8020F99C(0, 0.7f, 0.7f, 1.0f);
        func_8020F630(0);
        func_8020F99C(1, 1.0f, 0.0f, 0.0f);
        func_8020F5A4(1, 0.0f, 0.5f, 0.2f);
        break;
    case 20:
        func_8020F99C(1, 1.0f, 0.0f, 0.0f);
        func_8020F5A4(1, 0.0f, 0.5f, 0.2f);
        break;
    case 21:
        func_8020F99C(0, 0.4f, 0.4f, 1.0f);
        func_8020F630(0);
        func_8020F99C(1, 1.0f, 0.0f, 0.0f);
        func_8020F5A4(1, 0.0f, 0.8f, 0.2f);
        break;
    case 2:
    case 3:
    case 7:
    case 8:
    case 12:
    case 13:
    case 18:
    case 19:
    case 22:
        break;
    default:
        _uvDebugPrintf("error : unknown environment %d\n", envId);
        break;
    }
}

void env_802E2060(void) {
    Camera* camera;
    f32 var_fa1;
    f32 var_fa0;
    s32 i;
    u8* temp_v0;
    u8 temp1, temp2, temp3;

    if ((D_80362690->envId == 5) || (D_80362690->envId == 16)) {
        camera = D_80362690->unkC[D_80362690->unk9C].unk70;
        if (camera->unk108.m[0][0] == 0.0f) {
            var_fa0 = 0.0f;
        } else {
            var_fa0 = uvAtan2F(camera->unk108.m[0][1], camera->unk108.m[0][0]);
        }
        var_fa0 *= RADIAN_TO_ANGLE_FACTOR;
        for (i = 0; i < ARRAY_COUNT(D_8034EEFC) - 1; i++) {
            if (D_8034EEFC[i] < var_fa0 && var_fa0 <= D_8034EEFC[i + 1]) {
                break;
            }
        }
        temp_v0 = D_8034EEE0[i];
        var_fa1 = (var_fa0 - D_8034EEFC[i]) / (D_8034EEFC[i + 1] - D_8034EEFC[i]);
        temp1 = ((temp_v0[3] - temp_v0[0]) * var_fa1) + temp_v0[0];
        temp2 = ((temp_v0[4] - temp_v0[1]) * var_fa1) + temp_v0[1];
        temp3 = ((temp_v0[5] - temp_v0[2]) * var_fa1) + temp_v0[2];
        uvEnvProps(D_80362690->envId, 1, temp1, temp2, temp3, 0xFF, 0);
    }
}

void env_802E23E0(void) {
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv1;
    Unk80362690_Unk0* temp;

    if ((D_80362690->terraId == 0) && (D_80359DB4 == 0)) {
        temp = &D_80362690->unkC[D_80362690->unk9C];
        temp_fv0 = temp->unk2C.m[3][0] - -82.0f;
        temp_fv1 = temp->unk2C.m[3][1] - 250.0f;
        temp_fa1 = temp->unk2C.m[3][2] - 51.0f;
        if (uvSqrtF(SQ(temp_fv0) + SQ(temp_fv1) + SQ(temp_fa1)) < 6.0f) {
            D_80362690->envId = 6;
            D_80359DB4 = 1;
            sndPlaySfx(0x6FU);
            func_8033FB14();
            uvEventPost(0x12, 0);
            func_8033FB14();
            uvEventPost(0x17, 0);
            env_802E2504();
            uvEventPost(0x18, 0);
            uvEventPost(0x13, 0);
        }
    }
}

void env_802E2504(void) {
    Unk80362690_Unk0* temp_s0;
    s32 sp28;
    s32 sp24;
    HangGliderData* hgData;
    GyrocopterData* gcData;
    RocketBeltData* rbData;
    CannonballData* cbData;
    SkyDivingData* sdData;
    JumbleHopperData* jhData;
    BirdmanData* bmData;

    temp_s0 = &D_80362690->unkC[D_80362690->unk9C];
    level_8030BA60();
    taskDeinitLevel();
    windObjDeinit();
    proxAnimDispatchEvent2();
    cannon_802D8A40(1U, temp_s0->vehicleData);
    switch (temp_s0->veh) {
    case VEHICLE_GYROCOPTER:
        gcData = temp_s0->vehicleData;
        sp28 = gcData->objId;
        sp24 = gcData->unk2;
        break;
    case VEHICLE_HANG_GLIDER:
        hgData = temp_s0->vehicleData;
        sp28 = hgData->objId;
        sp24 = hgData->unk2;
        break;
    case VEHICLE_ROCKET_BELT:
        rbData = temp_s0->vehicleData;
        sp28 = rbData->objId;
        sp24 = rbData->unk2;
        break;
    case VEHICLE_CANNONBALL:
        cbData = temp_s0->vehicleData;
        sp28 = cbData->objId;
        sp24 = cbData->unk2;
        break;
    case VEHICLE_SKY_DIVING:
        sdData = temp_s0->vehicleData;
        sp28 = sdData->objId;
        sp24 = sdData->unk2;
        break;
    case VEHICLE_JUMBLE_HOPPER:
        jhData = temp_s0->vehicleData;
        sp28 = jhData->objId;
        sp24 = jhData->unk2;
        break;
    case VEHICLE_BIRDMAN:
        bmData = temp_s0->vehicleData;
        sp28 = bmData->objId;
        sp24 = bmData->unk2;
        break;
    }
    uvDobjState(sp28, 0);
    shadow_803343D8(0);
    uvLevelInit();
    levelLoad(D_80362690->map, temp_s0->pilot, temp_s0->veh, 1);
    shadow_803343D8(1);
    uvDobjState(sp28, sp24);
    proxAnimDispatchEvent3();
    windObjLoad();
    taskLoad();
    cannon_802D8A40(0U, temp_s0->vehicleData);
    hudInit();
}
