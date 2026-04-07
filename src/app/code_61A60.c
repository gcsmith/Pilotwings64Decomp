#include "common.h"
#include <uv_controller.h>
#include <uv_dobj.h>
#include <uv_sobj.h>
#include <uv_event.h>
#include <uv_font.h>
#include <uv_janim.h>
#include <uv_memory.h>
#include <uv_math.h>
#include <uv_texture.h>
#include <uv_vector.h>
#include "kernel/code_8170.h"
#include "kernel/code_30EA0.h"
#include "code_61A60.h"
#include "code_9A960.h"
#include "code_B3A70.h"
#include "code_C9B60.h"
#include "code_D2B10.h"
#include "demo.h"
#include "env_sound.h"
#include "game.h"
#include "hud.h"
#include "level.h"
#include "snd.h"
#include "text_data.h"

s32 D_8034EA40 = 0;
u16 D_8034EA44 = 0xFFFF;
s32 D_8034EA48 = 0;

// This struct should be used for Unk8034EA4C */
typedef struct {
    Vec3F unk0;
    f32 unkC;
    f32 unk10;
    f32 unk14;
} Unk8034EA4C;
Unk8034EA4C D_8034EA4C = {
    { -68.08f, -302.14f, 10.74f },
    -0.0174533f, 0.1f, 0.0f
};

s32 D_8034EA64[] = { PILOT_LARK, PILOT_KIWI, PILOT_GOOSE, PILOT_IBIS, PILOT_HAWK, PILOT_ROBIN };
s32 D_8034EA7C[] = { 0x35, 0x14C, 0x9C, 0x1A7, 0x85, 0x128 };
s32 D_8034EA94[] = { 2, 2, 2, 2, 2, 2 };
Unk803599D0 D_8034EAAC = { 8, 0.36f, 0.0f, 0.412f, 0.1f, 0.465f, 0.25f, 0.517f, 0.475f, 0.568f, 0.5f, 0.62f, 0.475f, 0.673f, 0.25f, 0.725f, 0.0f, 0, 0, 0, 0 };

// .bss
extern f32 D_80359C40;
extern s32 D_80359C44;
extern Mtx4F D_80359C48;
extern f32 D_80359C88;

// forward declarations
void func_802DA6E0(Unk80362690*, s32);
void func_802DA9E0(void);
s32 func_802DAA34(void);
void func_802DAB18(Camera*);
s32 func_802DB38C(Unk802D3658_Unk1228*, Vec3F*, Vec3F*);
s32 func_802DB6D4(Unk802D3658_Unk1228*, Vec3F*, Vec3F*);
s32 func_802DBCB0(Unk802D3658_Unk1228*, Vec3F*, Vec3F*);
void func_802DBE10(Unk802D3658_Unk1228*, s32, s32, f32, Vec3F*, Vec3F*);

s32 func_802DA530(void) {
    return D_8034EA64[D_8034EA40];
}

void func_802DA54C(void) {
    D_8034EA40++;
    if (D_8034EA40 >= 6) {
        D_8034EA40 = 0;
    }
}

s32 func_802DA574(Unk80362690* arg0) {
    s32 gameState;
    Unk80362690_Unk0* temp_s0;

    temp_s0 = &arg0->unkC[arg0->unk9C];
    func_802DA6E0(arg0, D_8034EA64[D_8034EA40]);
    while ((gameState = func_802DAA34()) == GAME_STATE_DEMO_PILOT) {
        uvGfxBegin();
        func_802DAB18(temp_s0->unk70);
        uvGfxEnd();
    }
    func_8032D51C(0);
    func_802DA9E0();
    return gameState;
}

s32 func_802DA628(u32 pilot) {
    switch (pilot) {
    case PILOT_LARK:
        return 0x55;
    case PILOT_GOOSE:
        return 0x56;
    case PILOT_HAWK:
        return 0x57;
    case PILOT_KIWI:
        return 0x58;
    case PILOT_IBIS:
        return 0x59;
    case PILOT_ROBIN:
        return 0x5A;
    default:
        return 0;
    }
}

s32 func_802DA684(u32 pilot) {
    switch (pilot) {
    case PILOT_LARK:
        return MODEL_PILOT_LARK;
    case PILOT_GOOSE:
        return MODEL_PILOT_GOOSE;
    case PILOT_HAWK:
        return MODEL_PILOT_HAWK;
    case PILOT_KIWI:
        return MODEL_PILOT_KIWI;
    case PILOT_IBIS:
        return MODEL_PILOT_IBIS;
    case PILOT_ROBIN:
        return MODEL_PILOT_ROBIN;
    default:
        return 0;
    }
}

void func_802DA6E0(Unk80362690* arg0, s32 pilot) {
    Camera* temp_s0;

    temp_s0 = arg0->unkC[arg0->unk9C].unk70;
    D_8034EA48 = 0;
    D_80359C88 = 0.0f;
    envSoundInit();
    arg0->map = 1;
    arg0->terraId = 0;
    arg0->envId = (u16)D_8034EA94[D_8034EA40];
    levelLoad(1, pilot, 0, 1);
    uvLevelAppend(func_802DA628(pilot));
    func_80204BD4(temp_s0->unk22C, 1, 1.0f);
    func_80204A8C(temp_s0->unk22C, 3);
    uvChanTerra(temp_s0->unk22C, arg0->terraId);
    uvLevelAppend(func_802DA628(pilot));
    uvChanEnv(temp_s0->unk22C, arg0->envId);
    func_8034B5E0(temp_s0->unk22C, temp_s0);
    func_80204A8C(temp_s0->unk22C, 3);
    uvMat4SetIdentity(&temp_s0->unk108);
    uvMat4RotateAxis(&temp_s0->unk108, D_8034EA4C.unkC, 'z');
    uvMat4RotateAxis(&temp_s0->unk108, D_8034EA4C.unk10, 'x');
    uvMat4RotateAxis(&temp_s0->unk108, D_8034EA4C.unk14, 'y');
    temp_s0->unk108.m[3][0] = D_8034EA4C.unk0.x;
    temp_s0->unk108.m[3][1] = D_8034EA4C.unk0.y;
    temp_s0->unk108.m[3][2] = D_8034EA4C.unk0.z;
    func_80204B34(temp_s0->unk22C, &temp_s0->unk108);
    D_8034EA44 = uvDobjAllocIdx();
    uvDobjModel(D_8034EA44, func_802DA684((u32)pilot));
    uvMat4SetIdentity(&D_80359C48);
    if (pilot != PILOT_KIWI) {
        uvMat4RotateAxis(&D_80359C48, 0.2f, 'z');
    }
    uvMat4RotateAxis(&D_80359C48, 0.2f, 'x');
    uvMat4RotateAxis(&D_80359C48, 0.0f, 'y');
    D_80359C48.m[3][0] = 0.0f;
    D_80359C48.m[3][1] = 5.0f;
    D_80359C48.m[3][2] = -1.2f;
    uvMat4MulBA(&D_80359C48, &temp_s0->unk108, &D_80359C48);
    uvDobjPosm(D_8034EA44, 0, &D_80359C48);
    hudGetState()->renderFlags = 0;
    switch (pilot) {
    case PILOT_LARK:
        D_80359C44 = 0x6D;
        break;
    case PILOT_GOOSE:
        D_80359C44 = 0x6E;
        break;
    case PILOT_HAWK:
        D_80359C44 = 0x6F;
        break;
    case PILOT_KIWI:
        D_80359C44 = 0x70;
        break;
    case PILOT_IBIS:
        D_80359C44 = 0x71;
        break;
    case PILOT_ROBIN:
        D_80359C44 = 0x72;
        break;
    default:
        D_80359C44 = 0x6D;
        break;
    }
    D_80359C40 = 0.0f;
}

void func_802DA9E0(void) {
    uvEventPost(0xD, 0);
    uvDobjModel(D_8034EA44, MODEL_WORLD);
    D_8034EA44 = 0xFFFF;
    level_8030BA60();
    uvLevelInit();
    func_802EBBB8();
}

// func_802DAA34 returns:
//  - 0: A/B/Start button was pressed
//  - 9: 5 second time exceeded?
//  - 8: none of the above
s32 func_802DAA34(void) {
    demo_80323020();
    func_80313D74();
    D_80359C40 += D_8034F854;
    if (D_80359C40 >= 5.0f) {
        return GAME_STATE_DEMO_TEST_SETUP;
    }
    if (uvControllerButtonPress(D_80362690->unk9C, A_BUTTON | B_BUTTON | START_BUTTON)) {
        func_80344258(0);
        if (uvControllerButtonPress(D_80362690->unk9C, A_BUTTON | START_BUTTON)) {
            sndPlaySfx(SFX_UI_CONFIRM);
        } else if (uvControllerButtonPress(D_80362690->unk9C, B_BUTTON)) {
            sndPlaySfx(0x01);
        }
        return GAME_STATE_TITLE;
    }
    return GAME_STATE_DEMO_PILOT;
}

void func_802DAB18(Camera* arg0) {
    f32 var_fs0;
    Mtx4F spC4;
    Mtx4F sp84;
    Mtx4F sp44;
    u32 pilot;

    var_fs0 = (D_80359C40 - 1.0f) / 4;
    if (var_fs0 < 0.0) {
        var_fs0 = 0.0f;
    }
    pilot = func_802DA530();
    switch (pilot) {
    case PILOT_LARK:
        if ((D_80359C88 > 0.45f) && (var_fs0 < 0.54f) && ((D_8034EA48 & 1) == 0)) {
            sndPlaySfx(SFX_PILOT_LARK_SELECT);
            D_8034EA48 |= 1;
        }
        var_fs0 *= 2.55;
        break;
    case PILOT_GOOSE:
        if ((D_80359C88 > 0.0f) && (var_fs0 < 0.1f) && ((D_8034EA48 & 2) == 0)) {
            sndPlaySfx(SFX_PILOT_GOOSE_SELECT);
            D_8034EA48 |= 2;
        }
        break;
    case PILOT_HAWK:
        if ((D_80359C88 > 0.0f) && (var_fs0 < 0.5f) && ((D_8034EA48 & 3) == 0)) {
            sndPlaySfx(SFX_PILOT_HAWK_SELECT);
            D_8034EA48 |= 3;
        }
        break;
    case PILOT_KIWI:
        if ((D_80359C88 > 0.5f) && (var_fs0 < 0.8f) && ((D_8034EA48 & 4) == 0)) {
            sndPlaySfx(SFX_PILOT_KIWI_SELECT);
            D_8034EA48 |= 4;
        }
        var_fs0 *= 1.5;
        break;
    case PILOT_IBIS:
        if ((D_80359C88 > 0.5f) && (var_fs0 < 1.0f) && ((D_8034EA48 & 5) == 0)) {
            sndPlaySfx(SFX_PILOT_IBIS_SELECT);
            D_8034EA48 |= 5;
        }
        var_fs0 *= 1.5;
        break;
    case PILOT_ROBIN:
        if ((D_80359C88 > 0.25f) && (var_fs0 < 0.75f) && !(D_8034EA48 & 6)) {
            sndPlaySfx(SFX_PILOT_ROBIN_SELECT);
            D_8034EA48 |= 6;
        }
        break;
    }
    if (var_fs0 > 1.0) {
        var_fs0 = 1.0f;
    }
    if (D_80359C44 == 0x6D) {
        uvMat4Copy(&spC4, &D_80359C48);
        uvMat4LocalTranslate(&spC4, 0.0f, 0.0f, func_80313F08(&D_8034EAAC, var_fs0));
        uvDobjPosm(D_8034EA44, 0, &spC4);
    }
    func_80200B00(D_8034EA44, D_80359C44, var_fs0);
    func_80204B34(arg0->unk22C, &arg0->unk108);
    uvGfxSetViewport(0, 0, 0x140, 0, 0xF0);
    uvMat4SetOrtho(&sp84, 0.0f, 319.0f, 0.0f, 239.0f);
    uvGfxMtxProjPushF(&sp84);
    uvMat4SetIdentity(&sp44);
    uvGfxMtxViewLoad(&sp44, 1);
    uvFontSet(6);
    uvFontScale(1, 1);
    uvFontColor(0xFF, 0xFF, 0xFF, 0xFF);
    func_80219874(140, 25, textGetDataByIdx(D_8034EA7C[D_8034EA40]), 100, 0xFFE);
    func_80204FC4(arg0->unk22C);
    func_80313D74();
    D_80359C88 = var_fs0;
}

s32 func_802DB050(Unk802D3658_Unk111C* arg0, Unk802D3658_Unk1224* arg1, u16 arg2, u8 arg3, Mtx4F* arg4) {
    Unk802D3658_Unk1120* var_s5;
    Vec3F* var_s4;
    s32 i;
    Unk802D3658_Unk1228* temp_s0;

    if ((arg2 != 0xFFFF) && (arg3 & 1)) {
        uvDobjState(arg2, arg3 - 1);
    }
    arg1->unk0 = 0;
    for (i = 0; i < arg0->unk0; i++) {
        var_s5 = &arg0->unk4[i];
        if (var_s5->unk0 != 0) {
            uvMat4LocalToWorld(arg4, &var_s5->unk4, &var_s5->unk1C);
            uvMat4LocalToWorld(arg4, &var_s5->unk10, &var_s5->unk28);
        }
        var_s4 = &var_s5->unk4;
        temp_s0 = &arg1->unk4[arg1->unk0];
        if (func_802DB6D4(temp_s0, &var_s5->unk10, var_s4) != 0) {
            temp_s0->unk0 = i;
            arg1->unk0++;
        } else if (func_802DB9B8(temp_s0, &var_s5->unk10, var_s4) != 0) {
            temp_s0->unk0 = i;
            arg1->unk0++;
        } else if (func_802DB38C(temp_s0, &var_s5->unk10, var_s4) != 0) {
            temp_s0->unk0 = i;
            arg1->unk0++;
        } else if (func_802DBCB0(temp_s0, &var_s5->unk10, var_s4) != 0) {
            temp_s0->unk0 = i;
            arg1->unk0++;
        }
    }
    if (arg2 != 0xFFFF) {
        uvDobjState(arg2, (s32)arg3);
    }
    return arg1->unk0;
}

s32 func_802DB224(Unk802D3658_Unk1224* arg0, u16 arg1, u16 arg2, u8 arg3, Vec3F* arg4, Vec3F* arg5) {
    u8 a1_lsb = arg1;
    if ((arg2 != 0xFFFF) && (arg3 & 1)) {
        uvDobjState(arg2, arg3 - 1);
    }
    arg0->unk0 = 0;
    if (a1_lsb & 2) {
        if (func_802DB6D4(&arg0->unk4[arg0->unk0], arg4, arg5)) {
            arg0->unk0 += 1;
        }
    }
    if (a1_lsb & 8) {
        if (func_802DB9B8(&arg0->unk4[arg0->unk0], arg4, arg5)) {
            arg0->unk0 += 1;
        }
    }
    if (a1_lsb & 1) {
        if (func_802DB38C(&arg0->unk4[arg0->unk0], arg4, arg5)) {
            arg0->unk0 += 1;
        }
    }
    if ((a1_lsb & 4) && func_802DBCB0(&arg0->unk4[arg0->unk0], arg4, arg5)) {
        arg0->unk0 += 1;
    }
    if (arg2 != 0xFFFF) {
        uvDobjState(arg2, arg3);
    }
    return arg0->unk0;
}

s32 func_802DB38C(Unk802D3658_Unk1228* arg0, Vec3F* arg1, Vec3F* arg2) {
    s32 count;
    s32* spA8;
    f32* spA4;
    s32 spA0;
    f32 sp9C;
    Vec3F sp90;
    f32 x;
    s32 temp_v1;
    f32 sp84;
    f32 sp80;
    f32 sp7C;
    f32 sp78;
    f32 y;
    s32 sp70;
    s32 var_s0;
    Vec3F sp60;
    u16 sp5E;
    s32 i;

    sp5E = 0;
    count = uvTerraGetSeg(D_80362690->terraId, arg1->x, arg1->y, arg1->z, arg2->x, arg2->y, arg2->z, &spA8, &spA4);
    if (count == 0) {
        return count;
    }

    sp70 = 0;
    var_s0 = 0;
    for (i = 0; i < count; i++) {
        temp_v1 = uvTerraGetState(D_80362690->terraId, spA8[var_s0]) & 0xFFF;
        if ((temp_v1 == 0x28) || (temp_v1 == 0x30)) {
            sp70 += 1;
        }
        var_s0++;
    }
    if (sp70 == count) {
        return 0;
    }

    sp80 = arg2->x - arg1->x;
    sp7C = arg2->y - arg1->y;
    sp78 = arg2->z - arg1->z;

    sp9C = 1.0f;
    for (i = 0; i < count; i++) {
        if (spA4[i] <= sp9C) {
            spA0 = spA8[i];
            sp9C = spA4[i];
        }
    }

    for (i = 0; i < count; i++) {
        if (func_802DC8E4(spA8[i]) != 0) {
            sp5E = 4;
            break;
        }
    }
    if (i == count) {
        sp5E = 1;
    }

    x = arg1->x + (sp80 * sp9C);
    sp60.x = x;
    y = arg1->y + (sp7C * sp9C);
    sp60.y = y;
    sp84 = arg1->z + (sp78 * sp9C);
    sp60.z = sp84;
    uvTerraGetPlane(D_80362690->terraId, spA0, sp60.x, sp60.y, &sp84, &sp90);
    func_802DBE10(arg0, sp5E, spA0, sp9C, &sp60, &sp90);
    return count;
}

s32 func_802DB6D4(Unk802D3658_Unk1228* arg0, Vec3F* arg1, Vec3F* arg2) {
    s32 count;
    s32* sp80;
    f32* sp7C;
    Vec3F* sp78;
    s32 sp74;
    s32 pad;
    Vec3F sp64;
    Vec3F sp58;
    f32 minVal;
    s32 i;

    count = func_8021215C(arg1->x, arg1->y, arg1->z, arg2->x, arg2->y, arg2->z, &sp80, &sp7C, &sp78);
    if (count == 0) {
        return 0;
    }

    minVal = 1.0f;
    for (i = 0; i < count; i++) {
        if (sp7C[i] <= minVal) {
            minVal = sp7C[i];
            sp74 = sp80[i];
            sp58.x = sp78[i].x;
            sp58.y = sp78[i].y;
            sp58.z = sp78[i].z;
        }
    }

    sp64.x = arg1->x + ((arg2->x - arg1->x) * minVal);
    sp64.y = arg1->y + ((arg2->y - arg1->y) * minVal);
    sp64.z = arg1->z + ((arg2->z - arg1->z) * minVal);
    func_802DBE10(arg0, 2, sp74, minVal, &sp64, &sp58);
    return count;
}

s32 func_802DB9B8(Unk802D3658_Unk1228* arg0, Vec3F* arg1, Vec3F* arg2) {
    s32 count;
    s32* sp80;
    f32* sp7C;
    Vec3F* sp78;
    s32 sp74;
    s32 pad;
    Vec3F sp64;
    Vec3F sp58;
    f32 minVal;
    s32 i;

    count = uvSobjGetSeg(D_80362690->terraId, arg1->x, arg1->y, arg1->z, arg2->x, arg2->y, arg2->z, &sp80, &sp7C, &sp78);
    if (count == 0) {
        return 0;
    }

    minVal = 1.0f;
    for (i = 0; i < count; i++) {
        if (sp7C[i] <= minVal) {
            minVal = sp7C[i];
            sp74 = sp80[i];
            sp58.x = sp78[i].x;
            sp58.y = sp78[i].y;
            sp58.z = sp78[i].z;
        }
    }

    sp64.x = arg1->x + ((arg2->x - arg1->x) * minVal);
    sp64.y = arg1->y + ((arg2->y - arg1->y) * minVal);
    sp64.z = arg1->z + ((arg2->z - arg1->z) * minVal);
    func_802DBE10(arg0, 8, sp74, minVal, &sp64, &sp58);
    return count;
}

s32 func_802DBCB0(Unk802D3658_Unk1228* arg0, Vec3F* arg1, Vec3F* arg2) {
    f32 temp_fv1;
    f32 var_ft4;
    Vec3F sp44;
    Vec3F sp38;
    s32 pad;

    if ((arg2->z > 0.0f) && (arg1->z > 0.0f)) {
        return 0;
    }
    if ((arg2->z < 0.0f) && (arg1->z < 0.0f)) {
        var_ft4 = 0.0f;
    } else {
        temp_fv1 = arg2->z - arg1->z;
        if (temp_fv1 != 0.0f) {
            if (arg2->z <= 0.0f) {
                var_ft4 = -arg1->z / temp_fv1;
            }
            if (arg1->z <= 0.0f) {
                var_ft4 = 1.0f - (arg2->z / temp_fv1);
            }
        } else {
            var_ft4 = 0.0f;
        }
    }
    sp44.x = arg1->x + ((arg2->x - arg1->x) * var_ft4);
    sp44.y = arg1->y + ((arg2->y - arg1->y) * var_ft4);
    sp44.z = arg1->z + ((arg2->z - arg1->z) * var_ft4);
    sp38.x = 0.0f;
    sp38.y = 0.0f;
    sp38.z = 1.0f;
    func_802DBE10(arg0, 4, -1, var_ft4, &sp44, &sp38);
    return 1;
}

void func_802DBE10(Unk802D3658_Unk1228* arg0, s32 collisionType, s32 surfaceId, f32 arg3, Vec3F* arg4, Vec3F* arg5) {
    arg0->collisionType = collisionType;
    arg0->surfaceId = surfaceId;
    arg0->unk18 = arg3;
    uvVec3Copy(&arg0->unk1C, arg5);
    uvVec3Copy(&arg0->unkC, arg4);
}

void func_802DBE64(Unk802D3658_Unk111C* arg0, Unk802D3658_Unk1224* arg1, s32 idx, Mtx4F* arg3) {
    Unk802D3658_Unk1228* unk1228;
    Vec3F* unk2C;
    Vec3F* unk20;

    unk1228 = &arg1->unk4[idx];
    unk2C = &arg0->unk4[unk1228->unk0].unk28;
    unk20 = &arg0->unk4[unk1228->unk0].unk1C;

    unk1228->unk28.x = unk2C->x + ((unk20->x - unk2C->x) * unk1228->unk18);
    unk1228->unk28.y = unk2C->y + ((unk20->y - unk2C->y) * unk1228->unk18);
    unk1228->unk28.z = unk2C->z + ((unk20->z - unk2C->z) * unk1228->unk18);
    uvMat4LocalToWorld(arg3, &unk1228->unk34, &unk1228->unk1C);
}

s32 func_802DBF10(Unk802D3658_Unk111C* arg0, Unk802D3658_Unk1224* arg1, Vec3F* arg2, Vec3F* arg3) {
    s32 pad[8];
    s32 ret;
    Unk802D3658_Unk1228* unk4;
    Vec3F* temp_v0;
    Vec3F* temp_v1;
    f32 temp_fa1;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fs2;
    f32 temp_ft4;
    f32 temp_fv0;
    f32 curLen;
    f32 emp_fv1;
    f32 minLen;
    s32 i;

    minLen = 1000000.0f;

    for (i = 0; i < arg1->unk0; i++) {
        unk4 = &arg1->unk4[i];
        temp_fv0 = unk4->unk18;
        temp_v0 = &arg0->unk4[unk4->unk0].unk10;
        temp_v1 = &arg0->unk4[unk4->unk0].unk4;
        temp_fs0 = temp_v0->x + ((temp_v1->x - temp_v0->x) * temp_fv0);
        temp_fs1 = temp_v0->y + ((temp_v1->y - temp_v0->y) * temp_fv0);
        temp_fs2 = temp_v0->z + ((temp_v1->z - temp_v0->z) * temp_fv0);
        curLen = uvSqrtF(SQ(temp_fs0) + SQ(temp_fs1) + SQ(temp_fs2));
        if (curLen < minLen) {
            ret = i;
            arg2->x = temp_fs0;
            arg2->y = temp_fs1;
            arg2->z = temp_fs2;
            minLen = curLen;
            arg3->x = unk4->unk1C.x;
            arg3->y = unk4->unk1C.y;
            arg3->z = unk4->unk1C.z;
        }
    }
    return ret;
}

f32 func_802DC074(Mtx4F* arg0, Vec3F* arg1, Vec3F* arg2, Vec3F* arg3, f32 arg4) {
    Vec3F sp2C;
    f32 var_fa1;

    var_fa1 = uvVec3Dot(arg1, arg3);
    if (var_fa1 < 0.0f) {
        arg1->x -= (2.0f * var_fa1) * arg3->x;
        arg1->y -= (2.0f * var_fa1) * arg3->y;
        arg1->z -= (2.0f * var_fa1) * arg3->z;
        arg1->x *= arg4;
        arg1->y *= arg4;
        arg1->z *= arg4;

        uvMat4LocalToWorld(arg0, &sp2C, arg3);
        arg2->x -= (2.0f * var_fa1) * sp2C.x;
        arg2->y -= (2.0f * var_fa1) * sp2C.y;
        arg2->z -= (2.0f * var_fa1) * sp2C.z;
        arg2->x *= arg4;
        arg2->y *= arg4;
        arg2->z *= arg4;
    }

    return FABS(var_fa1);
}

f32 func_802DC1DC(Vec3F* arg0, Vec3F* arg1, Vec3F* arg2, f32 arg3, f32 arg4, f32 arg5) {
    f32 var_fa1;
    f32 var_fv1;
    f32 temp_ft0;
    Vec3F sp38;
    Vec3F sp2C;
    f32 x;
    f32 y;
    f32 z;

    if (uvVec3Len(arg1) < 0.0001f) {
        return 0.0f;
    }
    uvVec3Normal(&sp38, arg1);
    var_fa1 = uvVec3Dot(arg2, &sp38);
    if (!(var_fa1 > 0.0f)) {
        var_fa1 = -var_fa1;
    }
    x = arg2->x - (var_fa1 * sp38.x);
    y = arg2->y - (var_fa1 * sp38.y);
    z = arg2->z - (var_fa1 * sp38.z);
    sp2C.x = ((arg1->y * z) - (arg1->z * y)) * arg3;
    sp2C.y = ((arg1->z * x) - (arg1->x * z)) * arg4;
    sp2C.z = ((arg1->x * y) - (arg1->y * x)) * arg5;
    arg0->x += sp2C.x;
    arg0->y += sp2C.y;
    arg0->z += sp2C.z;
    if (uvVec3Len(&sp2C) > 0.0f) {
        var_fv1 = uvVec3Len(&sp2C);
    } else {
        var_fv1 = -uvVec3Len(&sp2C);
    }
    return var_fv1;
}

void func_802DC380(s32 arg0, Mtx4F* arg1, Vec3F* arg2, Vec3F* arg3, Vec3F* arg4, Vec3F* arg5, Vec3F* arg6, Vec3F* arg7, Vec3F* arg8, f32 arg9, f32 arg10,
                   f32 arg11, f32 arg12, f32 arg13, f32 arg14) {
    Vec3F spFC;
    s32 i;
    s32 j;
    Vec3F spDC[2];
    Vec3F spC4[2];
    Vec3F spAC[2];
    f32 spA4[2];
    f32 var_fs0;
    f32 tmp;
    f32 temp_fv0;
    f32 sp88[2][2];
    f32 sp80[2];

    uvVec3Copy(&spDC[0], arg5);
    uvVec3Copy(&spC4[0], arg7);
    spA4[0] = arg9;
    uvVec3Copy(&spDC[1], arg6);
    uvVec3Copy(&spC4[1], arg8);
    spA4[1] = arg10;
    if (arg0 > 2) {
        return;
    }

    for (i = 0; i < arg0; i++) {
        uvVec3Cross(&spFC, arg4, &spC4[i]);
        spFC.x += arg2->x;
        spFC.y += arg2->y;
        spFC.z += arg2->z;
        var_fs0 = -uvVec3Dot(&spFC, &spDC[i]);
        if (var_fs0 < 0.0) {
            var_fs0 = 0.0f;
        }
        uvVec3Cross(&spAC[i], &spC4[i], &spDC[i]);
        spAC[i].x *= arg12;
        spAC[i].y *= arg13;
        spAC[i].z *= arg14;
        sp80[i] = (spA4[i] + 1.0f) * var_fs0;
    }

    for (i = 0; i < arg0; i++) {
        for (j = 0; j < i; j++) {
            uvVec3Cross(&spFC, &spAC[j], &spDC[i]);
            var_fs0 = uvVec3Dot(&spDC[i], &spDC[j]);
            sp88[j][i] = sp88[i][j] = uvVec3Dot(&spDC[i], &spFC) + (var_fs0 * arg11);
        }
        uvVec3Cross(&spFC, &spAC[i], &spC4[i]);
        sp88[i][i] = uvVec3Dot(&spDC[i], &spFC) + arg11;
    }

    if (arg0 == 1) {
        sp80[0] /= sp88[0][0];
    } else {
        temp_fv0 = ((sp88[0][0] * sp88[1][1]) - (sp88[0][1] * sp88[1][0]));
        tmp = ((sp80[0] * sp88[1][1]) - (sp80[1] * sp88[0][1])) / temp_fv0;
        sp80[1] = ((sp80[1] * sp88[0][0]) - (sp80[0] * sp88[1][0])) / temp_fv0;
        sp80[0] = tmp;
    }

    for (i = 0; i < arg0; i++) {
        uvVec3Mul(&spFC, &spDC[i], sp80[i] * arg11);
        uvVec3Add(arg2, arg2, &spFC);
        uvVec3Mul(&spFC, &spAC[i], sp80[i]);
        uvVec3Add(arg4, arg4, &spFC);
    }
    uvMat4LocalToWorld(arg1, arg3, arg2);
}

void func_802DC784(Mtx4F* arg0, Vec3F* arg1, Vec3F* arg2, Vec3F* arg3, f32 arg4) {
    Vec3F sp24;

    uvVec3Cross(&sp24, arg2, arg3);
    uvVec3Cross(arg2, &sp24, arg3);
    arg2->x = -arg4 * arg2->x;
    arg2->y = -arg4 * arg2->y;
    arg2->z = -arg4 * arg2->z;
    uvMat4LocalToWorld(arg0, arg1, arg2);
}

s32 func_802DC814(Unk802D3658_Unk1228* arg0, Vec3F* arg1) {
    f32 len;
    Vec3F sp20;
    f32 dot;

    sp20.x = arg0->unkC.x - arg1->x;
    sp20.y = arg0->unkC.y - arg1->y;
    sp20.z = arg0->unkC.z - arg1->z;
    len = uvVec3Len(&sp20);
    if (len < 0.02f) {
        return 0;
    }
    dot = uvVec3Dot(&sp20, &arg0->unk1C);
    if (dot > 0.0f) {
        arg0->unk1C.x = -arg0->unk1C.x;
        arg0->unk1C.y = -arg0->unk1C.y;
        arg0->unk1C.z = -arg0->unk1C.z;
        return 1;
    }
    return 0;
}

s32 func_802DC8E4(s32 surfaceId) {
    u16 state;
    state = uvTerraGetState(D_80362690->terraId, surfaceId) & 0xFFF;
    if (func_802300F0(state) == 4) {
        return 1;
    }
    return 0;
}

s32 func_802DC930(s32 surfaceId) {
    u16 state;
    state = uvTerraGetState(D_80362690->terraId, surfaceId) & 0xFFF;
    if (func_802300F0(state) == 0x20) {
        return 0;
    }
    return 1;
}

s32 func_802DC97C(u32 soid) {
    u16 modelId;

    modelId = uvSobj_8022D1E4(soid);
    if (MODEL_IS_TREE(modelId) || (modelId == MODEL_ROW_OF_5X_TREES) || (modelId == MODEL_TREE_SNOW_BILLBOARD)) {
        return TRUE;
    } else {
        return FALSE;
    }
}

s32 func_802DCA00(s32 surfaceId) {
    s32 state;

    if (surfaceId == -1) {
        return 0;
    }
    state = uvTerraGetState(D_80362690->terraId, surfaceId);
    if (((state & 0x100000) == 0) && ((state & 0x80000) == 0)) {
        return 1;
    }

    return 0;
}

void func_802DCA5C(Vec3F* arg0, Vec3F* arg1, Vec3F* arg2, Vec3F* arg3, Vec3F* arg4) {
    Vec3F sp2C;
    f32 temp_fa0;
    f32 var_fv1;
    f32 sp20;
    Vec3F* var_v0;

    sp2C.x = arg1->x - arg0->x;
    sp2C.y = arg1->y - arg0->y;
    sp2C.z = arg1->z - arg0->z;
    sp20 = uvVec3Len(&sp2C);
    temp_fa0 = uvVec3Dot(&sp2C, arg3) / sp20;
    var_fv1 = temp_fa0;
    if (temp_fa0 > 0.0f) {
        var_v0 = arg0;
    } else {
        var_fv1 = -temp_fa0;
        var_v0 = arg1;
    }
    arg4->x = (arg2->x - var_v0->x) * var_fv1;
    arg4->y = (arg2->y - var_v0->y) * var_fv1;
    arg4->z = (arg2->z - var_v0->z) * var_fv1;
}
