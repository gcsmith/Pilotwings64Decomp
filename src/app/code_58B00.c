#include "common.h"
#include <uv_dobj.h>
#include <uv_math.h>
#include <uv_matrix.h>
#include <uv_model.h>
#include "code_58B00.h"
#include "code_9A960.h"
#include "env_sound.h"
#include "level.h"
#include "proxanim.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    f32 unk10;
    f32 unk14;
    Vec3F unk18;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    s32 unk40;
    s32 unk44;
} Unk803596A0;

Unk803596A0 D_803596A0[2];

// forward declarations
void func_802D15D0(s32);
s32 func_802D1900(s32, s32, s32);
s32 func_802D19A4(s32, s32, s32);
void func_802D1F58(s32);
s32 func_802D2018(s32, Mtx4F*);

void func_802D15D0(s32 arg0) {
    Mtx4F sp80;
    Unk803596A0* ptr;
    Mtx4F sp3C;
    f32 sp38;

    ptr = &D_803596A0[arg0];
    if ((f32)ptr->unkC >= 0.0f) {
        ptr->unk38 = (f32)(ptr->unk38 - (9.8 * D_8034F854 * 0.75));
        ptr->unk34 += ptr->unk38 * D_8034F854 * 0.75f;
        if (ptr->unk34 <= 0.0f) {
            ptr->unk38 = uvRandF_RANLUX() * ptr->unk3C;
            ptr->unk34 = 0;
        }
        if (ptr->unk38 > 0.0f) {
            sp38 = ((2.0f * ptr->unk34) / ptr->unk30) * ptr->unk2C;
            if (ptr->unk2C < sp38) {
                sp38 = ptr->unk2C;
            }
        } else {
            sp38 = (ptr->unk34 / ptr->unk30) * ptr->unk2C;
            if (ptr->unk2C < sp38) {
                sp38 = ptr->unk2C;
            }
        }
        uvModelGetPosm(ptr->unk4, ptr->unkC, &sp3C);
        if (ptr->unk14 > 0.0f) {
            uvMat4RotateAxis(&sp3C, sp38 * 0.01745329f, 'x'); // almost DEG_TO_RAD(1)
        } else {
            uvMat4RotateAxis(&sp3C, -sp38 * 0.01745329f, 'x'); // almost DEG_TO_RAD(1)
        }
        uvMat4LocalTranslate(&sp3C, 0.0f, 0.0f, ptr->unk34);
        uvDobjPosm(ptr->unk0, ptr->unkC, &sp3C);
    }
    ptr->unk10 += ptr->unk14 * D_8034F854;
    if (ptr->unk10 > 360.0) {
        ptr->unk10 = (f32)(ptr->unk10 - 360.0);
    }
    uvMat4SetIdentity(&sp80);
    uvMat4LocalTranslate(&sp80, ptr->unk18.x, ptr->unk18.y, ptr->unk18.z);
    uvMat4RotateAxis(&sp80, ptr->unk10 * 0.01745329f, 'z'); // almost DEG_TO_RAD(1)
    uvMat4LocalTranslate(&sp80, ptr->unk24, 0.0f, 0.0f);

    if (FABS(ptr->unk28) > 0.0f) {
        uvMat4RotateAxis(&sp80, ptr->unk28 * 0.01745329f, 'y'); // almost DEG_TO_RAD(1)
    }
    if (ptr->unk0 != 0xFFFF) {
        uvDobjPosm(ptr->unk0, 0, &sp80);
    }
    if (ptr->unk8 != 0xFFFF) {
        uvDobjPosm(ptr->unk8, 0, &sp80);
    }
}

// used as function pointer to func_80321210
s32 func_802D1900(s32 arg0, s32 arg1, s32 arg2) {
    s32 i;
    switch (arg1) {
    case 0:
        break;
    case 2:
        for (i = 0; i < ARRAY_COUNT(D_803596A0); i++) {
            uvDobjState(D_803596A0[i].unk0, 0);
        }
        break;
    case 3:
        for (i = 0; i < ARRAY_COUNT(D_803596A0); i++) {
            uvDobjState(D_803596A0[i].unk0, 3);
        }
        break;
    }
    return 0;
}

// used as function pointer to func_80321210
s32 func_802D19A4(s32 arg0, s32 arg1, s32 arg2) {
    Unk803216A4* tmp;
    s32 idx;
    s32 res;
    s32 pad;
    Unk803596A0* temp_v0;

    res = 0;
    tmp = func_803216A4();
    idx = tmp->unk14;
    temp_v0 = &D_803596A0[idx];
    if (func_80321420(arg0) > 1500.0f) {
        if (temp_v0->unk44 != 0) {
            func_802D15D0(idx);
            temp_v0->unk44 = 0;
        } else {
            res = 2;
        }
    } else {
        if (temp_v0->unk44 == 0) {
            temp_v0->unk44 = 1;
        }
        func_802D15D0(idx);
    }
    return res;
}

void func_802D1A74(void) {
    Unk803596A0* var_s0;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_803596A0); i++) {
        var_s0 = &D_803596A0[i];
        switch (i) {
        case 0:
            var_s0->unk8 = uvDobjAllocIdx();
            if (var_s0->unk8 != 0xFFFF) {
                uvDobjModel(var_s0->unk8, 2);
                uvDobjState(var_s0->unk8, 0x22);
            }
            break;
        case 1:
            var_s0->unk8 = 0xFFFF;
            break;
        }
        var_s0->unk0 = uvDobjAllocIdx();
        if (var_s0->unk0 != 0xFFFF) {
            var_s0->unk3C = 0.0f;
            switch (i) {
            case 0:
                var_s0->unk4 = 3;
                var_s0->unk3C = 7.0f;
                var_s0->unk38 = 7.0f;
                var_s0->unk34 = 0.0f;
                var_s0->unkC = 1;
                var_s0->unk14 = -4.0f;
                var_s0->unk30 = 1.5f;
                var_s0->unk2C = 10.0f;
                var_s0->unk28 = -5.0f;
                uvDobjModel(var_s0->unk0, 3);
                uvDobjState(var_s0->unk0, 3);
                var_s0->unk24 = 400.0f;
                var_s0->unk18.f[0] = 400.0f;
                var_s0->unk18.f[2] = 0.0f;
                var_s0->unk18.f[1] = -300.0f;
                break;
            case 1:
                var_s0->unk4 = 0x29;
                var_s0->unk14 = 2.0f;
                var_s0->unkC = -1;
                var_s0->unk28 = 0.0f;
                uvDobjModel(var_s0->unk0, 0x29);
                uvDobjState(var_s0->unk0, 3);
                var_s0->unk24 = 275.0f;
                var_s0->unk18.f[2] = 0.0f;
                var_s0->unk18.f[0] = 300.0f;
                var_s0->unk18.f[1] = -200.0f;
                break;
            }
            var_s0->unk40 = func_80321210(func_802D19A4, func_802D1900, var_s0->unk18, 1500.0f, 0.0f, i);
            func_802D15D0(i);
            func_802D1F58(i);
        }
    }
}

void func_802D1CE8(void) {
    Unk803596A0* var_s0;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_803596A0); i++) {
        var_s0 = &D_803596A0[i];
        switch (i) {
        case 0:
            var_s0->unk8 = uvDobjAllocIdx();
            if (var_s0->unk8 != 0xFFFF) {
                uvDobjModel(var_s0->unk8, 2);
                uvDobjState(var_s0->unk8, 0x22);
            }
            break;
        case 1:
            var_s0->unk8 = 0xFFFF;
            break;
        }
        var_s0->unk0 = uvDobjAllocIdx();
        if (var_s0->unk0 != 0xFFFF) {
            var_s0->unk3C = 0.0f;
            switch (i) {
            case 0:
                var_s0->unk4 = 3;
                var_s0->unk3C = 7.0f;
                var_s0->unk38 = 7.0f;
                var_s0->unk34 = 0.0f;
                var_s0->unkC = 1;
                var_s0->unk14 = -4.0f;
                var_s0->unk30 = 1.5f;
                var_s0->unk2C = 10.0f;
                var_s0->unk28 = -5.0f;
                uvDobjModel(var_s0->unk0, 3);
                uvDobjState(var_s0->unk0, 3);
                var_s0->unk24 = 300.0f;
                var_s0->unk18.x = -600.0f;
                var_s0->unk18.y = -600.0f;
                var_s0->unk18.z = 0.0f;
                break;
            case 1:
                var_s0->unk4 = 1;
                var_s0->unk14 = 2.0f;
                var_s0->unkC = -1;
                var_s0->unk28 = 15.0f;
                uvDobjModel(var_s0->unk0, 1);
                uvDobjState(var_s0->unk0, 3);
                var_s0->unk24 = 300.0f;
                var_s0->unk18.z = 0.0f;
                var_s0->unk18.x = 700.0f;
                var_s0->unk18.y = -500.0f;
                break;
            }
            var_s0->unk40 = func_80321210(func_802D19A4, func_802D1900, var_s0->unk18, 1500.0f, 0.0f, i);
            func_802D15D0(i);
            func_802D1F58(i);
        }
    }
}

void func_802D1F58(s32 arg0) {
    LevelESND esnd;
    Unk803596A0* temp_v0;
    s32 temp_v0_2;

    temp_v0 = &D_803596A0[arg0];
    if (temp_v0->unk0 != 0xFFFF) {
        if (temp_v0->unk4 == 0x29) {
            esnd.sndId = 0x16;
            esnd.unk5C = 1.6f;
        } else if (temp_v0->unk4 == 3) {
            esnd.sndId = 0x15;
            esnd.unk5C = 2.0f;
        } else {
            return;
        }
        temp_v0_2 = func_802D2018(arg0, &esnd.unk0);
        esnd.unk64 = 0;
        esnd.unk74 = 8;
        esnd.unk70 = 0;
        esnd.unk60 = 1.0f;
        esnd.unk68 = 0.0f;
        esnd.unk6C = 200.0f;
        if (temp_v0_2 != 0) {
            envSoundLoad(&esnd);
        }
    }
}

s32 func_802D2018(s32 arg0, Mtx4F* arg1) {
    s32 temp_a3;
    temp_a3 = D_803596A0[arg0].unk0;
    if (temp_a3 == 0xFFFF) {
        return 0;
    } else {
        uvDobjGetPosm(temp_a3, 0, arg1);
        return 1;
    }
}

void func_802D206C(void) {
    s32 i;
    for (i = 0; i < ARRAY_COUNT(D_803596A0); i++) {
        if (D_803596A0[i].unk8 != 0xFFFF) {
            uvDobjModel(D_803596A0[i].unk8, MODEL_WORLD);
            D_803596A0[i].unk8 = 0xFFFF;
        }
        if (D_803596A0[i].unk0 != 0xFFFF) {
            uvDobjModel(D_803596A0[i].unk0, MODEL_WORLD);
            D_803596A0[i].unk0 = 0xFFFF;
            func_803212DC(D_803596A0[i].unk40);
        }
    }
}

void func_802D20F0(void) {
    s32 i;
    for (i = 0; i < ARRAY_COUNT(D_803596A0); i++) {
        D_803596A0[i].unk10 = 0.0f;
        D_803596A0[i].unk0 = 0xFFFF;
        D_803596A0[i].unk8 = 0xFFFF;
    }
}

void func_802D2124(s32 arg0, s32* arg1, f32* arg2, Vec3F* arg3) {
    Mtx4F sp28;
    Unk803596A0* temp_v0;

    temp_v0 = &D_803596A0[arg0];
    if (temp_v0->unk0 != 0xFFFF) {
        *arg1 = temp_v0->unk0;
        *arg2 = temp_v0->unk10 / 360.0f;
        uvDobjGetPosm(*arg1, 0, &sp28);
        arg3->x = sp28.m[3][0];
        arg3->y = sp28.m[3][1];
        arg3->z = sp28.m[3][2];
    } else {
        *arg1 = 0xFFFF;
        *arg2 = 0.0f;
        arg3->x = 0.0f;
        arg3->y = 0.0f;
        arg3->z = 0.0f;
    }
}

void func_802D21D8(s32 arg0, f32 arg1) {
    if (D_803596A0[arg0].unk0 != 0xFFFF) {
        uvDobjState(D_803596A0[arg0].unk0, 3);
        if (D_803596A0[arg0].unk8 != 0xFFFF) {
            uvDobjState(D_803596A0[arg0].unk8, 0x22);
        }
        D_803596A0[arg0].unk10 = (f32)(arg1 * 360.0f);
        D_803596A0[arg0].unk34 = 1.0f;
        D_803596A0[arg0].unk38 = (f32)(D_8034F854 * 9.8 * 0.75);
        func_802D15D0(arg0);
    }
}
