#include "common.h"
#include <uv_math.h>
#include <uv_matrix.h>
#include <uv_vector.h>
#include "gyrocopter.h"
#include "app/balls.h"
#include "app/demo.h"
#include "app/demo_attitude.h"
#include "app/environment.h"
#include "app/hud.h"
#include "app/pads.h"
#include "app/smoke.h"
#include "app/snd.h"
#include "app/targets.h"
#include "app/task.h"
#include "app/code_61A60.h"
#include "app/code_66160.h"
#include "app/code_9A960.h"
#include "app/code_B2900.h"

void func_80304738(GyrocopterData*);
void func_80304B98(GyrocopterData*);
void func_80305BE8(GyrocopterData*);
s32 func_80305DC0(GyrocopterData*);
void func_80307A9C(GyrocopterData*);
void func_80307BAC(GyrocopterData*);
void func_80307E2C(GyrocopterData*);
void func_80307EA8(GyrocopterData*);
void func_80308478(GyrocopterData*);
void func_8030877C(GyrocopterData*);
void func_80308F1C(GyrocopterData*);
void func_80309090(GyrocopterData*);

Unk802D3658_Unk111C D_80369070;
Unk802D3658_Unk1224 D_80369178;
Unk803599D0 D_803692C0;
Unk803599D0 D_80369318;
Unk803599D0 D_80369370;
Unk803599D0 D_803693C8;
Unk803599D0 D_80369420;
Unk803599D0 D_80369478;
Unk803599D0 D_803694D0;
Unk803599D0 D_80369528;
u16 D_8036957C;
u16 D_8036957E;

void func_80303230(GyrocopterData* arg0) {
    s32 pad;
    f32 sp78;
    f32 temp_fv1;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_ft4;
    u16 sp66;
    u16 sp64;

    D_80369070.unk0 = 2;
    D_80369070.unk4[0].unk0 = 1;
    D_80369070.unk4[0].unk1C.x = arg0->unk5BC.x;
    D_80369070.unk4[0].unk1C.y = arg0->unk5BC.y;
    D_80369070.unk4[0].unk1C.z = arg0->unk5BC.z;
    D_80369070.unk4[0].unk28.x = arg0->unk5C8.x;
    D_80369070.unk4[0].unk28.y = arg0->unk5C8.y;
    D_80369070.unk4[0].unk28.z = arg0->unk5C8.z;
    D_80369070.unk4[1].unk0 = 1;
    D_80369070.unk4[1].unk1C.x = arg0->unk59C.x;
    D_80369070.unk4[1].unk1C.y = arg0->unk59C.y - (0.5f * arg0->unk594);
    D_80369070.unk4[1].unk1C.z = arg0->unk59C.z;
    D_80369070.unk4[1].unk28.x = arg0->unk59C.x;
    D_80369070.unk4[1].unk28.y = arg0->unk59C.y + (0.5f * arg0->unk594);
    D_80369070.unk4[1].unk28.z = arg0->unk59C.z;
    D_803692C0.unk0 = 5;
    D_803692C0.unk4 = 0.0f;
    D_803692C0.unk8 = 0.f;
    D_803692C0.unkC = 10.0f;
    D_803692C0.unk10 = 0.15f;
    D_803692C0.unk14 = 20.0f;
    D_803692C0.unk18 = 0.4f;
    D_803692C0.unk1C = 50.0f;
    D_803692C0.unk20 = 1.2f;
    D_803692C0.unk24 = 100.0f;
    D_803692C0.unk28 = 1.5f;
    D_80369370.unk0 = 2;
    D_80369370.unk4 = 0.0f;
    D_80369370.unk8 = -0.5f;
    D_80369370.unkC = 5.0f;
    D_80369370.unk10 = 1.00f;
    D_803694D0.unk0 = 3;
    D_803694D0.unk4 = 0.0f;
    D_803694D0.unk8 = 0.001f;
    D_803694D0.unkC = 0.5f;
    D_803694D0.unk10 = 0.002f;
    D_803694D0.unk14 = 1.f;
    D_803694D0.unk18 = 0.005f;
    D_80369318.unk0 = 5;
    D_80369318.unk4 = 0.0f;
    D_80369318.unk8 = 0.f;
    D_80369318.unkC = 5.0f;
    D_80369318.unk14 = 10.0f;
    D_80369318.unk1C = 20.0f;
    D_80369318.unk18 = 0.4f;
    D_80369318.unk10 = 0.250f;
    D_80369318.unk20 = 0.20f;
    D_80369318.unk24 = 50.0f;
    D_80369318.unk28 = 0.1f;
    D_80369478.unk0 = 6;
    D_80369478.unk4 = 0.f;
    D_80369478.unk8 = 0.00f;
    D_80369478.unkC = 0.25f;
    D_80369478.unk10 = 0.18f;
    D_80369478.unk14 = 0.50f;
    D_80369478.unk18 = 0.40f;
    D_80369478.unk1C = 1.00f;
    D_80369478.unk20 = 1.000f;
    D_80369478.unk24 = 2.0f;
    D_80369478.unk28 = 2.0f;
    D_80369478.unk2C = 10.00f, D_80369478.unk30 = 10.00f;
    D_803693C8.unk0 = 2;
    D_803693C8.unkC = 1.00f;
    D_803693C8.unk8 = 1.000f;
    D_803693C8.unk10 = 1.000f;
    D_803693C8.unk4 = 0.f;
    D_80369420.unk0 = 2;
    D_80369420.unkC = 1.00f;
    D_80369420.unk8 = 1.000f;
    D_80369420.unk4 = 0.f;
    D_80369420.unk10 = 0.000f;
    arg0->unk3B0[0].unk40 = 0.2f;
    arg0->unk3B0[1].unk40 = 0.2f;
    arg0->unk3B0[2].unk40 = 0.2f;
    arg0->unk3B0[3].unk40 = 0.2f;
    arg0->unk3B0[0].unk44 = 0.0f;
    arg0->unk3B0[1].unk44 = 0.0f;
    arg0->unk3B0[2].unk44 = 0.0f;
    arg0->unk3B0[3].unk44 = 0.0f;
    D_80369528.unk0 = 3;
    D_80369528.unk4 = 0.f;
    D_80369528.unk8 = 0.0f;
    D_80369528.unkC = 2661.2188f;
    D_80369528.unk10 = 4.2f;
    D_80369528.unk14 = 6944.389f;
    D_80369528.unk18 = 7.5599995f;

    temp_fv1 = arg0->unk5EC[0].x - arg0->unk5EC[2].x;
    temp_fa0 = arg0->unk5EC[1].y - arg0->unk5EC[2].y;
    temp_fa1 = arg0->unk5EC[0].y - arg0->unk5EC[2].y;
    temp_ft4 = arg0->unk5EC[1].x - arg0->unk5EC[2].x;
    sp78 = (temp_fv1 * temp_fa0) - (temp_fa1 * temp_ft4);
    arg0->unk3B0[0].unk48 = (((arg0->unk538.x - arg0->unk5EC[2].x) * temp_fa0) - ((arg0->unk538.y - arg0->unk5EC[2].y) * temp_ft4)) / sp78;
    arg0->unk3B0[1].unk48 = (((arg0->unk538.y - arg0->unk5EC[2].y) * temp_fv1) - ((arg0->unk538.x - arg0->unk5EC[2].x) * temp_fa1)) / sp78;
    arg0->unk3B0[2].unk48 = (1.0000f - arg0->unk3B0[0].unk48) - arg0->unk3B0[1].unk48;
    arg0->unk3B0[3].unk48 = 0.0f;
    temp_fv1 = arg0->unk5EC[3].x - arg0->unk5EC[1].x;
    temp_fa0 = arg0->unk5EC[2].y - arg0->unk5EC[1].y;
    temp_fa1 = arg0->unk5EC[3].y - arg0->unk5EC[1].y;
    temp_ft4 = arg0->unk5EC[2].x - arg0->unk5EC[1].x;
    sp78 = (temp_fv1 * temp_fa0) - (temp_fa1 * temp_ft4);
    arg0->unk3B0[3].unk4C = (((arg0->unk538.x - arg0->unk5EC[1].x) * temp_fa0) + ((arg0->unk538.y + arg0->unk5EC[1].y) * temp_ft4)) / sp78;
    arg0->unk3B0[2].unk4C = -(((arg0->unk538.y + arg0->unk5EC[1].y) * temp_fv1) + ((arg0->unk538.x - arg0->unk5EC[1].x) * temp_fa1)) / sp78;
    arg0->unk3B0[1].unk4C = (1.0f - arg0->unk3B0[3].unk4C) - arg0->unk3B0[2].unk4C;
    arg0->unk3B0[0].unk4C = 0.0f;
    arg0->unk96 = 0xFF;
    func_80303714(arg0);
    arg0->unk4 = D_8036957C = 0xF7F8;
    taskGetClsVehTest(&D_8036957E, &sp66, &sp64);
}

void func_80303714(GyrocopterData* arg0) {
    s32 i;
    f32 sp88;
    f32 sp84;
    f32 sp80;
    Vec3F sp74;

    arg0->unk19C.x = 0.0f;
    arg0->unk19C.y = 0.0f;
    arg0->unk19C.z = 0.0f;
    arg0->unk1AC.x = 0.0f;
    arg0->unk1AC.y = 0.0f;
    arg0->unk1AC.z = 0.0f;
    arg0->unk1B8.x = 0.0f;
    arg0->unk1B8.y = 0.0f;
    arg0->unk1B8.z = 0.0f;
    arg0->unk1C8.x = 0.0f;
    arg0->unk1C8.y = 0.0f;
    arg0->unk1C8.z = 0.0f;
    arg0->unk1E0 = 0.0f;
    arg0->unk1E4 = 0.0f;
    arg0->unk1E8 = 0.0f;
    arg0->unk1EC = 0.0f;
    arg0->unk1F0 = 0.0f;
    arg0->unk1F4 = 0.0f;
    arg0->unk1F8 = 0.0f;
    arg0->unk1FC = 0.0f;
    arg0->unk200 = 0.0f;
    arg0->unk364.x = 0.0f;
    arg0->unk364.y = 0.0f;
    arg0->unk364.z = 0.0f;
    arg0->unk340 = 0.0f;
    arg0->unk344 = 0.0f;
    arg0->unk348 = 1.0f;
    arg0->unk100.x = 0.0f;
    arg0->unk100.y = 0.0f;
    arg0->unk100.z = 1.0f;
    arg0->unk358.x = 0.0f;
    arg0->unk358.y = 0.0f;
    arg0->unk358.z = -9.8f;
    arg0->unkC1 = 0;
    arg0->unkD0 = 0;
    arg0->unk10C = 0xFF;
    arg0->unk50 = -1;
    arg0->unk31C.x = 0.0f;
    arg0->unk31C.y = 0.0f;
    arg0->unk31C.z = 0.0f;
    arg0->unk328.x = 0.0f;
    arg0->unk328.y = 0.0f;
    arg0->unk328.z = 0.0f;
    arg0->unk334.x = 0.0f;
    arg0->unk334.y = 0.0f;
    arg0->unk334.z = 0.0f;
    arg0->unk1A8 = 0.0f;
    arg0->unk1C4 = 0.0f;
    arg0->unkE0 = 0.0f;
    arg0->unk9C = 0.0f;
    arg0->unkA0 = 0.0f;
    arg0->unkAC = 0.0f;
    arg0->unkE8 = 0.0f;
    arg0->unkEC = 1.5707963f;
    arg0->unkF4 = 0.0f;
    arg0->unk54 = 0.0f;
    arg0->unk70 = 0.0f;
    arg0->unk90 = 0.0f;
    arg0->unk8C = 4.0f;
    arg0->fuelEmpty = FALSE;
    arg0->unk6C = 0;
    arg0->unk6E = 0;
    arg0->unk98 = 0xFF;
    arg0->unk9A = 0xFF;
    arg0->unk94 = 0xFF;
    if (arg0->unk96 != 0xFF) {
        smoke_props(arg0->unk96, SMOKE_FX_8(0), SMOKE_FX_END);
    }

    uvMat4Copy(&arg0->unk150, &arg0->unk10);
    arg0->unk150.m[3][0] = arg0->unk150.m[3][1] = arg0->unk150.m[3][2] = 0.0f;
    uvMat4LocalToWorld(&arg0->unk150, &arg0->unk19C, &arg0->unk190);

    for (i = 0; i < 4; i++) {
        // FAKE
        if (0) { }
        sp74.x = arg0->unk5EC[i].x;
        sp74.y = arg0->unk5EC[i].y;
        sp74.z = 0.0f;
        uvMat4LocalToWorld(&arg0->unk10, &arg0->unk3B0[i].unk0, &sp74);
        arg0->unk3B0[i].unkC = 1;
    }
    arg0->unk674 = 1;
    arg0->unk668.x = arg0->unk10.m[3][0];
    arg0->unk668.y = arg0->unk10.m[3][1];
    arg0->unk668.z = arg0->unk10.m[3][2];
    func_80313570(&arg0->unk10, &sp88, &sp84, &sp80, &arg0->unk1EC, &arg0->unk1F0, &arg0->unk1F4);
}

extern f32 D_8034F850;
extern f32 D_8034F854;
extern u16 D_8036957C;

void func_8030399C(GyrocopterData* arg0) {
    f32 spFC;
    f32 spF8;
    f32 spF4;
    f32 temp_fv0;
    f32 spEC;
    f32 spE8;
    f32 spE4;
    f32 spE0;
    f32 spDC;
    s32 pad;
    u16 spD6;
    f32 spD0;

    arg0->unk31C.x = 0.0f;
    arg0->unk31C.y = 0.0f;
    arg0->unk31C.z = 0.0f;
    arg0->unk328.x = 0.0f;
    arg0->unk328.y = 0.0f;
    arg0->unk328.z = 0.0f;
    arg0->unk334.x = 0.0f;
    arg0->unk334.y = 0.0f;
    arg0->unk334.z = 0.0f;
    func_80307A9C(arg0);
    func_80307E2C(arg0);
    func_80308478(arg0);
    func_80307BAC(arg0);
    func_80307EA8(arg0);

    switch (arg0->unkC0) {
    case 0:
        func_80304738(arg0);
        break;
    case 1:
    case 4:
        func_80304B98(arg0);
        break;
    case 2:
        func_80305BE8(arg0);
        break;
    case 3:
        return;
    default:
        break;
    }
    func_80309090(arg0);
    if ((arg0->unkC0 == 0) && (arg0->unk190.z < arg0->unk190.y) && (arg0->unk6D == 0)) {
        arg0->unk1B8.x = (arg0->unk1AC.x - (arg0->unk190.y * arg0->unk1C8.z)) + (arg0->unk190.z * arg0->unk1C8.y);
        arg0->unk1B8.y = (arg0->unk1AC.y - (arg0->unk190.z * arg0->unk1C8.x)) + (arg0->unk190.x * arg0->unk1C8.z);
        arg0->unk1B8.z = (arg0->unk1AC.z - (arg0->unk190.x * arg0->unk1C8.y)) + (arg0->unk190.y * arg0->unk1C8.x);
        uvMat4LocalToWorld(&arg0->unk150, &arg0->unk1B8, &arg0->unk1B8);
    } else {
        if (arg0->unkC0 == 1) {
            uvMat4LocalToWorld(&arg0->unk150, &arg0->unk1B8, &arg0->unk1AC);
            arg0->unk1AC.x += (arg0->unk190.y * arg0->unk1C8.z) - (arg0->unk190.z * arg0->unk1C8.y);
            arg0->unk1AC.y += (arg0->unk190.z * arg0->unk1C8.x) - (arg0->unk190.x * arg0->unk1C8.z);
            arg0->unk1AC.z += (arg0->unk190.x * arg0->unk1C8.y) - (arg0->unk190.y * arg0->unk1C8.x);
        } else {
            uvMat4LocalToWorld(&arg0->unk150, &arg0->unk1B8, &arg0->unk1AC);
        }
    }

    if (arg0->unkC0 == 0) {
        arg0->unk1C8.x = arg0->unk1D4;
        arg0->unk1C8.y = arg0->unk1D8;
        arg0->unk1C8.z = arg0->unk1DC;
        arg0->unk1EC += D_8034F854 * arg0->unk1F8;
        arg0->unk1F0 += D_8034F854 * arg0->unk1FC;
        arg0->unk1F4 += D_8034F854 * arg0->unk200;
    } else {
        arg0->unk1C8.x += D_8034F854 * arg0->unk1E0;
        arg0->unk1C8.y += D_8034F854 * arg0->unk1E4;
        arg0->unk1C8.z += D_8034F854 * arg0->unk1E8;
        if (arg0->unkC0 != 2) {
            spE4 = uvSinF(arg0->unk1F4);
            spE0 = uvCosF(arg0->unk1F4);
            spDC = uvSinF(arg0->unk1F0);
            arg0->unk1F8 = ((arg0->unk1C8.z * spE0) - (arg0->unk1C8.x * spE4)) / uvCosF(arg0->unk1F0);
            arg0->unk1FC = (arg0->unk1C8.x * spE0) + (arg0->unk1C8.z * spE4);
            arg0->unk200 = arg0->unk1C8.y - (arg0->unk1F8 * spDC);
            arg0->unk1EC += D_8034F854 * arg0->unk1F8;
            arg0->unk1F0 += D_8034F854 * arg0->unk1FC;
            arg0->unk1F4 += D_8034F854 * arg0->unk200;
        }
    }
    spF4 = arg0->unk10.m[3][0];
    spF8 = arg0->unk10.m[3][1];
    spFC = arg0->unk10.m[3][2];
    if (arg0->unkC0 == 2) {
        arg0->unk10.m[3][2] = 0.0f;
        arg0->unk10.m[3][1] = 0.0f;
        arg0->unk10.m[3][0] = 0.0f;
        uvMat4RotateAxis(&arg0->unk10, arg0->unk1C8.z * D_8034F854, 'z');
        uvMat4RotateAxis(&arg0->unk10, arg0->unk1C8.x * D_8034F854, 'x');
        uvMat4RotateAxis(&arg0->unk10, arg0->unk1C8.y * D_8034F854, 'y');
    } else {
        func_80313640(0.0f, 0.0f, 0.0f, arg0->unk1EC, arg0->unk1F0, arg0->unk1F4, &arg0->unk10);
    }
    uvMat4Copy(&arg0->unk150, &arg0->unk10);
    uvMat4InvertTranslationRotation(&arg0->unk110, &arg0->unk150);
    if (arg0->unkC0 == 1) {
        arg0->unk190.x += D_8034F854 * arg0->unk1AC.x;
        arg0->unk190.y += D_8034F854 * arg0->unk1AC.y;
        arg0->unk190.z += D_8034F854 * arg0->unk1AC.z;
        uvMat4LocalToWorld(&arg0->unk150, &arg0->unk19C, &arg0->unk190);
    } else {
        arg0->unk19C.x += D_8034F854 * arg0->unk1B8.x;
        arg0->unk19C.y += D_8034F854 * arg0->unk1B8.y;
        arg0->unk19C.z += D_8034F854 * arg0->unk1B8.z;
        uvMat4LocalToWorld(&arg0->unk110, &arg0->unk190, &arg0->unk19C);
    }

    arg0->unk10.m[3][0] = (arg0->unk19C.x * D_8034F854) + spF4;
    arg0->unk10.m[3][1] = (arg0->unk19C.y * D_8034F854) + spF8;
    arg0->unk10.m[3][2] = (arg0->unk19C.z * D_8034F854) + spFC;
    if (arg0->unkC0 == 3) {
        return;
    }

    if (arg0->unkC0 == 0) {
        func_80313640(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, arg0->unk1F4, &arg0->unk25C);
        func_80313640(0.0f, 0.0f, 0.0f, 0.0f, arg0->unk1F0, arg0->unk1F4, &arg0->unk29C);
        func_80313640(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -arg0->unk1F4, &arg0->unk21C);
        uvMat4InvertTranslationRotation(&arg0->unk2DC, &arg0->unk29C);
    } else {
        temp_fv0 = uvSqrtF(1.0f - SQ(arg0->unk10.m[1][2]));
        spEC = arg0->unk10.m[2][2] / temp_fv0;
        spE8 = -arg0->unk10.m[0][2] / temp_fv0;
        uvMat4SetIdentity(&arg0->unk25C);
        arg0->unk25C.m[2][0] = spE8;
        arg0->unk25C.m[0][2] = -spE8;
        arg0->unk25C.m[2][2] = spEC;
        arg0->unk25C.m[0][0] = spEC;
        uvMat4SetIdentity(&arg0->unk21C);
        arg0->unk21C.m[0][0] = spEC;
        arg0->unk21C.m[2][2] = spEC;
        arg0->unk21C.m[2][0] = -spE8;
        arg0->unk21C.m[0][2] = spE8;
    }
    func_80308F1C(arg0);
    if (arg0->unkC0 == 3) {
        return;
    }
    func_8030877C(arg0);
    if (arg0->unkC0 == 3) {
        return;
    }
    func_80305DC0(arg0);

    if (arg0->unkC0 == 3) {
        return;
    }
    if (arg0->unkC0 == 0) {
        if ((ABS_NOEQ(arg0->unk1C8.z) < 0.0001f) &&
            (((arg0->unk31C.x > 0.f) && (arg0->unk190.x < 0.f)) || ((arg0->unk31C.x < 0.f) && (arg0->unk190.x > 0.f)))) {
            arg0->unk190.x = func_80313AF4(0.f, arg0->unk190.x, 6.0f);
            uvMat4LocalToWorld(&arg0->unk150, &arg0->unk19C, &arg0->unk190);
        }
    }
    arg0->unk1A8 = uvVec3Len(&arg0->unk19C);
    arg0->unk1C4 = uvVec3Len(&arg0->unk1B8);
    if ((arg0->unk1A8 < 0.1f) || ((arg0->unkC0 == 1) && (arg0->fuel == 0.0f) && (arg0->unk190.y < 0.1f))) {
        arg0->unkC0 = 4;
        if (arg0->unk6C == 0) {
            arg0->unk4 = D_8036957C;
            if (arg0->unk50 == 1) {
                hudText_8031D8E0(0xA2, 1.5f, 8.0f);
            }
        } else if (arg0->unk50 == 1) {
            if (arg0->unk4 != D_8036957C) {
                hudText_8031D8E0(0x12A, 1.5f, 8.0f);
            } else {
                hudText_8031D8E0(0xA2, 1.5f, 8.0f);
            }
        }
    }

    if ((ABS_NOEQ(arg0->unk1F0) > 0.8028515f) || (ABS_NOEQ(arg0->unk1F4) > 1.0646509f)) {
        if (arg0->unkC0 != 2) {
            arg0->unkC0 = 2;
            arg0->unk96 = smoke_create();
            smoke_props(arg0->unk96, SMOKE_FX_1(0, 0, 0), SMOKE_FX_2(20.0f), SMOKE_FX_3(2.0f), SMOKE_FX_5(0.0f, 0.0f, 0.0f), SMOKE_FX_END);
        }
    }
    if (arg0->unkC0 == 2) {
        smoke_props(arg0->unk96, SMOKE_FX_6(arg0->unk10.m[3][0], arg0->unk10.m[3][1], arg0->unk10.m[3][2]), SMOKE_FX_END);
    } else {
        if ((arg0->unk98 != -1) && (arg0->unk98 != 0xFF)) {
            smoke_getprops(arg0->unk98, 8, &spD6, 0);
            if (spD6 != 0) {
                smoke_props(arg0->unk98, SMOKE_FX_6(arg0->unk10.m[3][0], arg0->unk10.m[3][1], arg0->unk10.m[3][2]), SMOKE_FX_END);
                smoke_props(arg0->unk9A, SMOKE_FX_6(arg0->unk10.m[3][0], arg0->unk10.m[3][1], arg0->unk10.m[3][2]), SMOKE_FX_END);
            } else {
                arg0->unk98 = -1;
                arg0->unk9A = -1;
            }
        }
        if (arg0->unk94 != 0xFF) {
            smoke_getprops(arg0->unk94, 8, &spD6, 0);
            if (spD6 != 0) {
                if ((arg0->unkC0 == 1) && (arg0->unk1A8 > 5.952f) && (arg0->unk6C == 0) && (func_802DC930(arg0->unkF8) != 0)) {
                    smoke_getprops(arg0->unk94, 4, &spD0, 0);
                    smoke_props(arg0->unk94,
                                SMOKE_FX_6(((arg0->unk3B0[1].unk0.x + arg0->unk3B0[2].unk0.x) * 0.5f), (arg0->unk3B0[1].unk0.y + arg0->unk3B0[2].unk0.y) * 0.5f,
                                           arg0->unk3B0[1].unk0.z),
                                SMOKE_FX_4(spD0 + D_8034F854), SMOKE_FX_7(1), SMOKE_FX_END);
                } else {
                    smoke_props(arg0->unk94, SMOKE_FX_4(0.0f), SMOKE_FX_END);
                }
            } else {
                arg0->unk94 = 0xFF;
            }
        } else if ((arg0->unkC0 == 1) && (arg0->unk1A8 > 5.952f) && (arg0->unk50 >= 0) && (arg0->unk6C == 0) && (func_802DC930(arg0->unkF8) != 0)) {
            arg0->unk94 = smoke_create();
            smoke_props(arg0->unk94, SMOKE_FX_1(160, 120, 70), SMOKE_FX_2(4.0f), SMOKE_FX_3(3.0f), SMOKE_FX_4(1.0f),
                        SMOKE_FX_5(-arg0->unk10.m[1][0], -arg0->unk10.m[1][1], 0.5f),
                        SMOKE_FX_6((arg0->unk3B0[1].unk0.x + arg0->unk3B0[2].unk0.x) * 0.5f, (arg0->unk3B0[1].unk0.y + arg0->unk3B0[2].unk0.y) * 0.5f,
                                   arg0->unk3B0[1].unk0.z),
                        SMOKE_FX_7(1), SMOKE_FX_END);
        }
    }
    if (D_80362690->unkA4 != 0) {
        demoAttUpdate(D_8034F850, &arg0->unk10);
    }
}

void func_80304738(GyrocopterData* arg0) {
    f32 temp_fv1;
    f32 var_ft4;
    f32 temp_fv0;
    f32 var_fa1;
    f32 var_ft4_2;
    f32 temp_fv1_3;
    f32 var_fa1_3;
    f32 temp_fa1;

    arg0->unk204 = uvSinF(arg0->unk1EC);
    arg0->unk208 = uvCosF(arg0->unk1EC);
    arg0->unk20C = uvSinF(arg0->unk1F0);
    arg0->unk210 = uvCosF(arg0->unk1F0);
    arg0->unk214 = uvSinF(arg0->unk1F4);
    arg0->unk218 = uvCosF(arg0->unk1F4);
    temp_fv1 = arg0->unk9C - arg0->unkA4;
    var_ft4 = ABS_NOEQ(temp_fv1);

    if ((var_ft4 / D_8034F854) > 5.0f) {
        arg0->unk9C = arg0->unkA4 + ((5.0f * D_8034F854 * temp_fv1) / var_ft4);
    }

    temp_fv0 = arg0->unkA0 - arg0->unkA8;
    var_fa1 = ABS_NOEQ(temp_fv0);
    if ((var_fa1 / D_8034F854) > 5.0f) {
        arg0->unkA0 = arg0->unkA8 + ((5.0f * D_8034F854 * temp_fv0) / var_fa1);
    }

    if (var_ft4 >= 0.0f) {
        arg0->unk200 = (ABS_NOEQ(arg0->unk9C) * arg0->unk9C) - (arg0->unk1F4 / 1.0471976f);
    } else {
        arg0->unk200 = ((ABS_NOEQ(arg0->unk9C) * arg0->unk9C) - (arg0->unk1F4 / 1.0471976f)) * 104.0f;
    }

    arg0->unkA4 = arg0->unk9C;
    if (arg0->unk190.y > 39.68254f) {
        var_ft4_2 = 1.0f - (((arg0->unk190.y - 39.68254f) * 0.3f) / 39.68254f);
    } else {
        var_ft4_2 = (((39.68254f - arg0->unk190.y) * 1.5f) / 39.68254f) + 1.0f;
    }
    if (arg0->unk190.y > 0.0f) {
        arg0->unk1F8 = (-arg0->unk190.y * var_ft4_2 * arg0->unk214) / arg0->unk640;
    } else {
        arg0->unk1F8 = 0.0f;
    }
    temp_fv1_3 = 15.873016f;
    if ((temp_fv1_3 * 3.0f) < arg0->unk190.y) {
        var_ft4_2 = 1.0f - (((arg0->unk190.y - (temp_fv1_3 * 3.0f)) * 0.3f) / (2.0f * temp_fv1_3));
    } else {
        var_ft4_2 = ((((temp_fv1_3 * 3.0f) - arg0->unk190.y) * 0.5f) / (temp_fv1_3 * 3.0f)) + 1.0f;
    }
    if (var_fa1 >= 0.0f) {
        var_fa1_3 = ABS_NOEQ(arg0->unk190.y);
        arg0->unk1FC = ((ABS_NOEQ(arg0->unkA0) * arg0->unkA0) + (arg0->unk1F0 / 0.7853982f)) * (-0.0064f * var_ft4_2 * var_fa1_3 * arg0->unk218);
    } else {
        var_fa1_3 = ABS_NOEQ(arg0->unk190.y);
        arg0->unk1FC = ((ABS_NOEQ(arg0->unkA0) * arg0->unkA0) + (arg0->unk1F0 / 0.7853982f)) * (-90.0f * var_ft4_2 * var_fa1_3 * arg0->unk218);
    }

    temp_fa1 = arg0->unk1F8 * arg0->unk210;
    arg0->unkA8 = arg0->unkA0;
    arg0->unk1D4 = (arg0->unk1FC * arg0->unk218) - (temp_fa1 * arg0->unk214);
    arg0->unk1D8 = arg0->unk200 + (arg0->unk1F8 * arg0->unk20C);
    arg0->unk1DC = (arg0->unk1FC * arg0->unk214) + (temp_fa1 * arg0->unk218);
}

void func_80304B98(GyrocopterData* arg0) {
    s32 i;
    s32 j;
    s32 sp184;
    s32 temp_s2;
    f32 sp170[4];
    f32 temp_fs0;
    f32 temp_fs0_3;
    f32 sp164;
    f32 temp_fs1;
    f32 temp_fv0_2;
    f32 temp_fv0_4;
    f32 temp_fv0_6;
    f32 sp150;
    f32 temp_fv1;
    f32 temp_ft5;
    f32 var_fv1;
    f32 temp_fa0_2;
    f32 sp13C;
    f32 sp138;
    f32 temp_fv1_2;
    f32 sp130;
    f32 sp12C;
    f32 sp128;
    Vec3F sp11C;
    Vec3F sp110;
    Vec3F sp104;
    Vec3F spF8;
    Vec3F spEC;
    Vec3F spE0;
    Vec3F spD4;
    Mtx4F sp94;

    if (arg0->unk8C < 4.0f) {
        if (arg0->unk510 > 0) {
            for (i = 0; i < arg0->unk510; i++) {
                sp184 = arg0->unk514[i];
                if (i == 0) {
                    uvVec3Copy(&sp110, &arg0->unk3B0[sp184].unk10);
                } else {
                    uvVec3Add(&sp110, &sp110, &arg0->unk3B0[sp184].unk10);
                }
            }
            uvVec3Mul(&sp110, &sp110, 1.0f / arg0->unk510);
            uvVec3Normal(&sp110, &sp110);
        } else {
            sp110.x = 0.0f;
            sp110.y = 0.0f;
            sp110.z = 1.0f;
            uvMat4LocalToWorld(&arg0->unk110, &sp110, &sp110);
        }
        if (arg0->unk8C > 2.0f) {
            uvVec3Mul(&sp11C, &sp110, (uvVec3Dot(&sp110, &arg0->unk334) * (arg0->unk8C - 4.0f)) / 2);
        } else {
            uvVec3Mul(&sp11C, &sp110, -uvVec3Dot(&sp110, &arg0->unk334));
        }

        uvVec3Add(&arg0->unk31C, &arg0->unk31C, &sp11C);
        arg0->unk8C += D_8034F854;
    }
    arg0->unk524 = 0;

    for (i = 0; i < arg0->unk510; i++) {
        sp184 = arg0->unk514[i];
        uvVec3Cross(&sp11C, &arg0->unk1C8, &arg0->unk5EC[sp184]);
        uvVec3Cross(&sp11C, &arg0->unk1C8, &sp11C);
        sp170[arg0->unk524] = -uvVec3Dot(&sp11C, &arg0->unk3B0[sp184].unk10);
        sp170[arg0->unk524] -= uvVec3Dot(&arg0->unk31C, &arg0->unk3B0[sp184].unk10);
        if ((arg0->unk3B0[sp184].unk54 < 0.01f) && ((arg0->unk8C <= 2.0f) || ((arg0->unk8C > 2.0f) && (sp170[arg0->unk524] > 0.0f)))) {
            arg0->unk528[arg0->unk524++] = sp184;
        }
    }

    if (arg0->unk524 == 0) {
        return;
    }

    if (arg0->unk524 < 3) {
        for (i = 0; i < arg0->unk524; i++) {
            sp184 = arg0->unk528[i];
            for (j = 0; j < i; j++) {
                temp_s2 = arg0->unk528[j];
                uvVec3Cross(&sp11C, &arg0->unk3B0[temp_s2].unk28, &arg0->unk5EC[sp184]);
                sp94.m[j][i] = sp94.m[i][j] =
                    (uvVec3Dot(&arg0->unk3B0[sp184].unk10, &arg0->unk3B0[temp_s2].unk10) / 250.0f) + uvVec3Dot(&arg0->unk3B0[sp184].unk10, &sp11C);
            }

            uvVec3Cross(&sp11C, &arg0->unk3B0[sp184].unk28, &arg0->unk5EC[sp184]);
            sp94.m[i][i] = uvVec3Dot(&arg0->unk3B0[sp184].unk10, &sp11C) + 0.004f;
        }
        for (i = 0; i < arg0->unk524; i++) {
            sp184 = arg0->unk528[i];
            for (j = 0; j < arg0->unk524; j++) {
                temp_s2 = arg0->unk528[j];
                if (i == j) {
                    uvVec3Cross(&sp11C, &arg0->unk3B0[sp184].unk34, &arg0->unk5EC[sp184]);
                    sp94.m[i][j] += -uvVec3Dot(&arg0->unk3B0[sp184].unk10, &sp11C) * arg0->unk3B0[temp_s2].unk40;
                } else {
                    uvVec3Cross(&sp11C, &arg0->unk3B0[temp_s2].unk34, &arg0->unk5EC[sp184]);
                    sp94.m[i][j] +=
                        -((uvVec3Dot(&arg0->unk3B0[sp184].unk10, &arg0->unk3B0[temp_s2].unk1C) / 250.0f) + uvVec3Dot(&arg0->unk3B0[sp184].unk10, &sp11C)) *
                        arg0->unk3B0[temp_s2].unk40;
                }
            }
        }
    }
    if (arg0->unk524 < 3) {
        if (arg0->unk524 == 1) {
            sp170[0] /= sp94.m[0][0];
        } else {
            temp_fv0_2 = (sp94.m[0][0] * sp94.m[1][1]) - (sp94.m[0][1] * sp94.m[1][0]);
            temp_fv1_2 = ((sp170[0] * sp94.m[1][1]) - (sp170[1] * sp94.m[0][1])) / temp_fv0_2;
            sp170[1] = ((sp170[1] * sp94.m[0][0]) - (sp170[0] * sp94.m[1][0])) / temp_fv0_2;
            sp170[0] = temp_fv1_2;
        }

        for (i = 0; i < arg0->unk524; i++) {
            sp184 = arg0->unk528[i];
            uvVec3Mul(&sp11C, &arg0->unk3B0[sp184].unk1C, -arg0->unk3B0[sp184].unk40);
            uvVec3Add(&sp11C, &arg0->unk3B0[sp184].unk10, &sp11C);
            uvVec3Mul(&sp11C, &sp11C, sp170[i] / 250.0f);
            uvVec3Add(&arg0->unk31C, &arg0->unk31C, &sp11C);
            uvVec3Mul(&sp11C, &arg0->unk3B0[sp184].unk34, -arg0->unk3B0[sp184].unk40);
            uvVec3Add(&sp11C, &arg0->unk3B0[sp184].unk28, &sp11C);
            uvVec3Mul(&sp11C, &sp11C, sp170[i]);
            uvVec3Add(&arg0->unk328, &arg0->unk328, &sp11C);
        }
    } else {
        for (i = 0; i < arg0->unk524; i++) {
            sp184 = arg0->unk528[i];
            if (i == 0) {
                sp164 = arg0->unk3B0[sp184].unk40;
                uvVec3Copy(&sp110, &arg0->unk3B0[sp184].unk10);
            } else {
                sp164 += arg0->unk3B0[sp184].unk40;
                uvVec3Add(&sp110, &sp110, &arg0->unk3B0[sp184].unk10);
            }
        }
        if (uvVec3Dot(&arg0->unk31C, &sp110) < 0.0f) {
            uvVec3Mul(&sp110, &sp110, 1.0f / arg0->unk524);
            uvVec3Normal(&sp110, &sp110);
            uvVec3Cross(&sp104, &sp110, &arg0->unk190);
            uvVec3Cross(&sp104, &sp104, &sp110);
            sp13C = uvSqrtF(SQ(sp110.y) + SQ(sp110.z));
            sp138 = sp110.z / sp13C;
            sp130 = -sp110.y / sp13C;
            sp12C = sp110.x * sp130;
            sp128 = sp110.x * sp138;
            spEC.x = sp13C;
            spEC.y = sp12C;
            spEC.z = -sp128;
            spF8.x = 0.0f;
            spF8.y = sp138;
            spF8.z = sp130;
            temp_fv0_4 = uvVec3Dot(&sp104, &spF8);
            var_fv1 = (1.0f - arg0->unkB4) * temp_fv0_4 * 0.3f;
            if (arg0->unk6C != 0) {
                var_fv1 *= 0.8f;
            }
            if (temp_fv0_4 < 2.0f) {
                var_fv1 *= 1.0f + (4.0f * (2.0f - temp_fv0_4));
            }
            uvVec3Mul(&spD4, &spF8, -var_fv1);

            for (i = 0; i < 3; i++) {
                sp184 = arg0->unk528[i];
                if ((sp184 == 0) || (sp184 == 3)) {
                    if (arg0->unk6C == 0) {
                        sp150 = (arg0->unkAC + arg0->unk9C) * -0.2617994f;
                    } else {
                        if (((arg0->unk190.y * 0.7f) > 40.0f) && ((arg0->unk190.y * 0.7f) <= 45.0f)) {
                            sp150 = ((arg0->unkAC + arg0->unk9C) * -0.0872665f * ((arg0->unk190.y * 0.7f) - 40.0f)) / 5.0f;
                        } else if (((arg0->unk190.y * 0.7f) > 45.0f) && ((arg0->unk190.y * 0.7f) < 50.0f)) {
                            sp150 = ((arg0->unkAC + arg0->unk9C) * -0.0872665f * (50.0f - (arg0->unk190.y * 0.7f))) / 5.0f;
                        } else {
                            sp150 = 0.0f;
                        }
                    }
                    if (sp184 == 3) {
                        sp150 = -sp150;
                    }
                    temp_fs0_3 = uvCosF(sp150);
                    temp_fv0_6 = uvSinF(sp150);
                    spEC.x = temp_fs0_3 * sp13C;
                    spEC.y = (temp_fs0_3 * sp12C) + (temp_fv0_6 * sp138);
                    spEC.z = (-temp_fs0_3 * sp128) + (temp_fv0_6 * sp130);
                    spF8.x = -temp_fv0_6 * sp13C;
                    spF8.y = (-temp_fv0_6 * sp12C) + (temp_fs0_3 * sp138);
                    spF8.z = (temp_fv0_6 * sp128) + (temp_fs0_3 * sp130);
                } else {
                    spEC.x = sp13C;
                    spEC.y = sp12C;
                    spEC.z = -sp128;
                    spF8.x = 0.0f, spF8.y = sp138, spF8.z = sp130;
                }

                temp_fs1 = arg0->unk3B0[sp184].unk50 * uvVec3Dot(&arg0->unk3B0[sp184].unk1C, &spF8);
                temp_fa0_2 = arg0->unk3B0[sp184].unk50 * uvVec3Dot(&arg0->unk3B0[sp184].unk1C, &spEC);
                if (arg0->unk528[0] == 0) {
                    temp_fv1 = arg0->unk3B0[sp184].unk48 * temp_fs1 * 0.35f;
                    temp_fs0 = arg0->unk3B0[sp184].unk48 * 0.5f * temp_fa0_2 * 2.4f;
                } else {
                    temp_fv1 = arg0->unk3B0[sp184].unk4C * temp_fs1 * 0.35f;
                    temp_fs0 = arg0->unk3B0[sp184].unk4C * 0.5f * temp_fa0_2 * 2.4f;
                }
                if ((arg0->unk6C == 0) && (arg0->unk50 != -1)) {
                    temp_fv1 *= 1.1f;
                    temp_fs0 *= 1.1f;
                }
                uvVec3Mul(&spF8, &spF8, -temp_fv1);
                uvVec3Add(&spD4, &spD4, &spF8);
                uvVec3Mul(&spEC, &spEC, -temp_fs0);
                uvVec3Add(&spD4, &spD4, &spEC);
                spE0.x = arg0->unk5EC[sp184].x - arg0->unk538.x;
                if (arg0->unk528[0] == 0) {
                    spE0.y = arg0->unk5EC[sp184].y - arg0->unk538.y;
                } else {
                    spE0.y = arg0->unk5EC[sp184].y + arg0->unk538.y;
                }
                spE0.z = arg0->unk5EC[sp184].z - arg0->unk538.z;
                uvVec3Cross(&spE0, &sp110, &spE0);
                uvVec3Cross(&spE0, &spE0, &sp110);
                uvVec3Cross(&spF8, &spE0, &spF8);
                uvVec3Add(&arg0->unk328, &arg0->unk328, &spF8);
                uvVec3Cross(&spEC, &spE0, &spEC);
                uvVec3Add(&arg0->unk328, &arg0->unk328, &spEC);
            }
            uvVec3Cross(&arg0->unk31C, &sp110, &arg0->unk31C);
            uvVec3Cross(&arg0->unk31C, &arg0->unk31C, &sp110);
            uvVec3Add(&arg0->unk31C, &arg0->unk31C, &spD4);
            uvVec3Mul(&arg0->unk328, &sp110, uvVec3Dot(&arg0->unk328, &sp110));
        }
    }
}

void func_80305BE8(GyrocopterData* arg0) {
    f32 var_fs0;

    if (arg0->unkE0 == 0.0f) {
        if (uvVec3Len(&arg0->unk1C8) < 0.78539807f) {
            var_fs0 = (demoRandF() + 1.0f) * 21.8f;
            if (demoRandF() < 0.5f) {
                var_fs0 = -var_fs0;
            }
            arg0->unk1E0 = var_fs0 * 0.4f;
            var_fs0 = (demoRandF() + 1.0f) * 21.8f;
            if (demoRandF() < 0.5f) {
                var_fs0 = -var_fs0;
            }
            arg0->unk1E4 = var_fs0 * 0.4f;
            var_fs0 = (demoRandF() + 1.0f) * 10.9f;
            if (demoRandF() < 0.5f) {
                var_fs0 = -var_fs0;
            }
            arg0->unk1E8 = var_fs0 * 0.8f;
        }
        arg0->unkE0 = D_8034F850;
    }
    arg0->unk1C8.x = func_80313AF4(0.0f, arg0->unk1C8.x, 0.2f);
    arg0->unk1C8.y = func_80313AF4(0.0f, arg0->unk1C8.y, 0.2f);
    arg0->unk1C8.z = func_80313AF4(0.0f, arg0->unk1C8.z, 0.2f);
    if ((D_8034F850 - arg0->unkE0) > 3.75f) {
        arg0->unkC0 = 3;
    }
}

s32 func_80305DC0(GyrocopterData* arg0) {
    u8 sp2FF;
    f32 sp2F8;
    s32 var_s6;
    Vec3F sp2E8;
    Vec3F sp2DC;
    Vec3F sp2D0;
    Vec3F sp2C4;
    s32 sp2C0;
    s32 i;
    s32 j;
    s32 sp2B4;
    s32 temp_s2;
    s32 var_s5_4;
    Vec3F sp27C[4];
    Vec3F sp24C[4];
    u8 temp_s0;
    u8 pad;
    u8 sp249;
    s32 sp244;
    f32 var_fs0;
    f32 sp23C;
    s32 sp238;
    s32 sp228[4];
    s32 sp218[4];
    s32 var_v0;
    s32 var_v1;
    Vec3F sp204;
    f32 var_fs1;
    Vec3F sp1F4;
    Vec3F* temp_v0_2;
    Vec3F sp1E4;
    f32 sp1D4[4];
    Vec3F sp1C8;
    f32 temp_fv1;
    s32 sp1C0;
    Mtx4F sp180;
    f32 sp17C;
    f32 var_fv1;
    f32 temp_fv1_4;
    f32 temp_fs0_3;
    f32 sp16C;
    f32 sp168;
    f32 sp164;
    f32 temp_fv0;
    Mtx4F sp120;
    f32 sp110[4];

    sp2FF = 0;
    sp244 = 0;
    sp23C = 0.0f;
    arg0->unk6C = 0;
    var_s6 = 0;
    var_fs1 = 0.0f;

    func_80317978(arg0->unk10.m[3][0], arg0->unk10.m[3][1], arg0->unk10.m[3][2], &arg0->unk6C);

    for (i = 0; i < 4; i++) {
        uvMat4LocalToWorld(&arg0->unk10, &sp27C[i], &arg0->unk5EC[i]);
        sp2D0.x = arg0->unk5EC[i].x;
        sp2D0.y = arg0->unk5EC[i].y;
        sp2D0.z = 0.0f;
        uvMat4LocalToWorld(&arg0->unk10, &sp24C[i], &sp2D0);
    }

    arg0->unkDC = 1000000.0f;
    arg0->unk10C = 0xFF;
    sp1C0 = arg0->unk510;
    arg0->unk510 = 0;
    sp2B4 = 0;

    for (i = 0; i < 4; i++) {
        sp238 = arg0->unk3B0[i].unkC;
        temp_s0 = db_getgnd(&arg0->unk3B0[i].unk0, &sp24C[i], &sp238, &sp2C0, &sp2F8, &sp2E8);
        if (temp_s0 == 4) {
            if (arg0->unkC0 == 2) {
                smoke_props((s32)arg0->unk96, SMOKE_FX_8(0), SMOKE_FX_END);
            }
            arg0->unkC0 = 3;
            arg0->unkD0 = 1;
            arg0->unk544 = 1;
            arg0->unk547[0] = 1;
            uvVec3Copy(&arg0->unk54C[0], &sp27C[i]);
            arg0->unk3B0[i].unkC = sp238;
            return 1;
        }
        var_fs0 = sp27C[i].z - sp2F8;
        if ((temp_s0 == 2) && (targets_8034473C(sp2C0, 1) == 0.0f)) {
            var_s6 = 1;
        }
        if ((var_s6 != 0) || ((temp_s0) && (sp2E8.z < 0.0f)) || ((temp_s0 == 0) && (var_fs0 <= 0.0f))) {
            if ((var_s6 == 0) && (temp_s0) && (sp2E8.z < 0.0f)) {
                var_v0 = func_802DFB48(2, sp24C[i].x, sp24C[i].y, sp24C[i].z, &sp2C0, &sp2F8, &sp2DC);
            } else {
                var_v0 = func_802DFB48(2, sp24C[i].x, sp24C[i].y, sp24C[i].z, &sp2C0, &sp2F8, &sp2E8);
            }
            if (var_v0 != 0) {
                var_fs0 = sp27C[i].z - sp2F8;
            } else {
                var_fs0 = sp27C[i].z;
            }
            sp238 = 1;
        }
        if ((temp_s0) && (var_s6 == 0)) {
            temp_v0_2 = func_802E02EC();
            sp2D0.x = temp_v0_2->x - sp24C[i].x;
            sp2D0.y = temp_v0_2->y - sp24C[i].y;
            sp2D0.z = temp_v0_2->z - sp24C[i].z;
            temp_fv1 = uvVec3Dot(&sp2D0, &sp2E8);
            if (sp238 == 1) {
                sp238 = 2;
            } else if (sp238 == 2) {
                sp238 = 1;
            }
            if (var_fs1 < temp_fv1) {
                var_fs1 = temp_fv1;
                uvVec3Mul(&sp204, &sp2E8, temp_fv1);
            }
            if (sp2E8.z < 0.0f) {
                uvVec3Copy(&sp2E8, &sp2DC);
            }
        }
        if ((var_fs0 <= 0.0f) || ((i == arg0->unk528[sp2B4]) && (sp2B4 < arg0->unk524))) {
            if (i == arg0->unk528[sp2B4]) {
                sp2B4++;
            }
            sp2FF++;
            uvVec3Copy(&arg0->unk3B0[i].unk10, &sp2E8);
            arg0->unk514[arg0->unk510] = i;
            if (temp_s0) {
                sp218[arg0->unk510] = temp_s0;
            } else {
                sp218[arg0->unk510] = func_802E02F8();
            }
            arg0->unk510++;
        }
        arg0->unk3B0[i].unk54 = var_fs0;
        arg0->unk3B0[i].unkC = sp238;
        if (var_fs0 < arg0->unkDC) {
            arg0->unkDC = var_fs0;
            arg0->unkF8 = sp2C0;
            arg0->unkFC = sp2F8;
            arg0->unk100.x = sp2E8.x;
            arg0->unk100.y = sp2E8.y;
            arg0->unk100.z = sp2E8.z;
            arg0->unk10C = i;
            sp249 = temp_s0;
        }
    }

    if ((sp2FF != 0) && (sp249 != 2) && (sp249 != 8)) {
        if ((arg0->unkF8 == -1) || ((arg0->unkF8 != -1) && (func_802DC8E4(arg0->unkF8) != 0))) {
            if (arg0->unkC0 == 2) {
                smoke_props(arg0->unk96, SMOKE_FX_8(0), SMOKE_FX_END);
            }
            arg0->unkC0 = 3;
            arg0->unkD0 = 1;
            arg0->unk544 = 1;
            arg0->unk547[0] = 1;
            uvVec3Copy(&arg0->unk54C[0], &sp27C[arg0->unk10C]);
            return 1;
        }
    }

    if (var_fs1 > 0.0f) {
        arg0->unk10.m[3][0] += sp204.x;
        arg0->unk10.m[3][1] += sp204.y;
        arg0->unk10.m[3][2] += sp204.z;
        arg0->unk668.x = arg0->unk10.m[3][0];
        arg0->unk668.y = arg0->unk10.m[3][1];
        arg0->unk668.z = arg0->unk10.m[3][2];
        for (i = 0; i < 4; i++) {
            arg0->unk3B0[i].unk54 += sp204.z;
            uvMat4LocalToWorld(&arg0->unk10, &sp27C[i], &arg0->unk5EC[i]);
            sp2D0.x = arg0->unk5EC[i].x;
            sp2D0.y = arg0->unk5EC[i].y;
            sp2D0.z = 0.0f;
            uvMat4LocalToWorld(&arg0->unk10, &sp24C[i], &sp2D0);
        }
    }
    if (sp2FF) {
        if (arg0->unk510 > 3) {
            var_v1 = 0;
            var_fv1 = arg0->unk3B0[0].unk54;
            for (i = 1; i < arg0->unk510; i++) {
                if (var_fv1 < arg0->unk3B0[i].unk54) {
                    var_fv1 = arg0->unk3B0[i].unk54;
                    var_v1 = i;
                }
            }

            arg0->unk510 = 3;
            for (i = var_v1; i < 3; i++) {
                arg0->unk514[i] = arg0->unk514[i + 1];
            }
        }
        sp1F4.x = 0.0f;
        sp1F4.y = 0.0f;
        sp1F4.z = 1.0f;

        if (arg0->unk510 == 1) {
            sp2B4 = arg0->unk514[0];
            sp164 = arg0->unk3B0[sp2B4].unk54;
        }

        if (arg0->unk510 > 1) {
            for (i = 0; i < arg0->unk510; i++) {
                sp2B4 = arg0->unk514[i];
                if (i == 0) {
                    uvVec3Copy(&sp2E8, &arg0->unk3B0[sp2B4].unk10);
                    uvVec3Copy(&sp1C8, &arg0->unk5EC[sp2B4]);
                    sp164 = arg0->unk3B0[sp2B4].unk54;
                } else {
                    uvVec3Add(&sp2E8, &sp2E8, &arg0->unk3B0[sp2B4].unk10);
                    uvVec3Add(&sp1C8, &sp1C8, &arg0->unk5EC[sp2B4]);
                    sp164 += arg0->unk3B0[sp2B4].unk54;
                }
            }
            var_fs1 = 1.0f / arg0->unk510;
            uvVec3Mul(&sp2E8, &sp2E8, var_fs1);
            uvVec3Normal(&sp2E8, &sp2E8);
            uvMat4LocalToWorld(&arg0->unk150, &sp2E8, &sp2E8);
            uvVec3Mul(&sp1C8, &sp1C8, var_fs1);
            sp164 *= var_fs1;
        }
        if ((sp164 < -0.1f) && ((sp1C0 < arg0->unk510) || ((arg0->unk510 == sp1C0) && (arg0->unk510 == arg0->unk524)))) {
            uvVec3Mul(&sp1F4, &sp1F4, -sp164);
            arg0->unk10.m[3][0] += sp1F4.x;
            arg0->unk10.m[3][1] += sp1F4.y;
            arg0->unk10.m[3][2] += sp1F4.z;
            arg0->unk668.x = arg0->unk10.m[3][0];
            arg0->unk668.y = arg0->unk10.m[3][1];
            arg0->unk668.z = arg0->unk10.m[3][2];
            switch (arg0->unk510) {
            case 1:
                for (i = 0; i < 4; i++) {
                    uvVec3Add(&arg0->unk3B0[i].unk0, &sp24C[i], &sp1F4);
                }
                break;
            case 2:
                sp2B4 = arg0->unk514[0];
                temp_s2 = arg0->unk514[1];
                sp2D0.x = sp27C[sp2B4].x - sp27C[temp_s2].x;
                sp2D0.y = sp27C[sp2B4].y - sp27C[temp_s2].y;
                sp2D0.z = sp27C[sp2B4].z - sp27C[temp_s2].z;
                temp_fs0_3 = uvVec3Len(&sp2D0);
                if (temp_fs0_3 > 0.0f) {
                    sp17C = uvVec3Dot(&sp2D0, &sp2E8) / temp_fs0_3;
                    if (sp17C < 0.0f) {
                        uvVec3Mul(&sp2D0, &sp2D0, -1.0f);
                        sp17C = -sp17C;
                    }
                    if (sp17C >= 1.0f) {
                        sp17C = 0.0f;
                    } else {
                        sp17C = uvSqrtF(1.0f - SQ(sp17C));
                    }
                    uvVec3Cross(&sp1E4, &sp2E8, &sp2D0);
                    uvVec3Normal(&sp1E4, &sp1E4);
                } else {
                    sp17C = 1.0f;
                }
                break;
            case 3:
                sp2B4 = arg0->unk514[0];
                temp_s2 = arg0->unk514[1];
                sp2D0.x = sp27C[sp2B4].x - sp27C[temp_s2].x;
                sp2D0.y = sp27C[sp2B4].y - sp27C[temp_s2].y;
                sp2D0.z = sp27C[sp2B4].z - sp27C[temp_s2].z;
                temp_s2 = arg0->unk514[2];
                sp2C4.x = sp27C[sp2B4].x - sp27C[temp_s2].x;
                sp2C4.y = sp27C[sp2B4].y - sp27C[temp_s2].y;
                sp2C4.z = sp27C[sp2B4].z - sp27C[temp_s2].z;
                uvVec3Cross(&sp2D0, &sp2D0, &sp2C4);
                temp_fs0_3 = uvVec3Len(&sp2D0);
                if (temp_fs0_3 > 0.0f) {
                    sp17C = uvVec3Dot(&sp2D0, &sp2E8) / temp_fs0_3;
                    if (sp17C < 0.0f) {
                        uvVec3Mul(&sp2D0, &sp2D0, -1.0f);
                        sp17C = -sp17C;
                    }
                    uvVec3Cross(&sp1E4, &sp2E8, &sp2D0);
                    uvVec3Normal(&sp1E4, &sp1E4);
                } else {
                    sp17C = 1.0f;
                }
                break;
            case 0:
            default:
                for (i = 0; i < 4; i++) {
                    uvVec3Copy(&arg0->unk3B0[i].unk0, &sp24C[i]);
                }
                break;
            }

            if ((arg0->unk510 >= 2) && (sp17C < 0.999f)) {
                sp1D4[3] = uvSqrtF((1.0f + sp17C) * 0.5f);
                sp1D4[0] = sp1D4[1] = sp1D4[2] = uvSqrtF((1.0f - sp17C) * 0.5f);
                uvMat4LocalToWorld(&arg0->unk110, &sp1E4, &sp1E4);
                sp1D4[0] *= sp1E4.x;
                sp1D4[1] *= sp1E4.y;
                sp1D4[2] *= sp1E4.z;
                uvMat4SetQuaternionRotation(&sp180, sp1D4[0], sp1D4[1], sp1D4[2], sp1D4[3]);
                sp180.m[3][0] = sp180.m[3][0] = sp180.m[3][1] = sp180.m[3][2] = 0.0f;
                sp180.m[0][3] = sp180.m[0][3] = sp180.m[1][3] = sp180.m[2][3] = 0.0f;
                sp180.m[3][3] = 1.0f;
                sp2C4.x = arg0->unk10.m[3][0];
                sp2C4.y = arg0->unk10.m[3][1];
                sp2C4.z = arg0->unk10.m[3][2];
                uvMat4LocalToWorld(&arg0->unk110, &arg0->unk1B8, &arg0->unk1B8);
                uvMat4LocalToWorld(&arg0->unk150, &sp2D0, &sp1C8);
                uvVec3Add(&sp2C4, &sp2D0, &sp2C4);
                uvMat4MulBA(&arg0->unk10, &arg0->unk150, &sp180);
                uvMat4Copy(&arg0->unk150, &arg0->unk10);
                uvMat4InvertTranslationRotation(&arg0->unk110, &arg0->unk150);
                uvMat4LocalToWorld(&arg0->unk150, &sp2D0, &sp1C8);
                sp2C4.x -= sp2D0.x;
                sp2C4.y -= sp2D0.y;
                sp2C4.z -= sp2D0.z;
                arg0->unk10.m[3][0] = sp2C4.x;
                arg0->unk10.m[3][1] = sp2C4.y;
                arg0->unk10.m[3][2] = sp2C4.z;
                uvVec3Copy(&arg0->unk668, &sp2C4);
                for (i = 0; i < 4; i++) {
                    sp2D0.x = arg0->unk5EC[i].x;
                    sp2D0.y = arg0->unk5EC[i].y;
                    sp2D0.z = 0.0f;
                    uvMat4LocalToWorld(&arg0->unk10, &arg0->unk3B0[i].unk0, &sp2D0);
                    arg0->unk3B0[i].unk54 += arg0->unk3B0[i].unk0.z - sp24C[i].z;
                }
                uvMat4LocalToWorld(&arg0->unk150, &arg0->unk1B8, &arg0->unk1B8);
                uvMat4LocalToWorld(&arg0->unk150, &arg0->unk19C, &arg0->unk190);
            }
        } else {
            for (i = 0; i < 4; i++) {
                uvVec3Copy(&arg0->unk3B0[i].unk0, &sp24C[i]);
            }
        }
        var_s5_4 = 0;
        for (i = 0; i < arg0->unk510; i++) {
            sp2B4 = arg0->unk514[i];
            uvMat4LocalToWorld(&arg0->unk110, &arg0->unk3B0[sp2B4].unk10, &arg0->unk3B0[sp2B4].unk10);
            uvVec3Cross(&sp2D0, &arg0->unk1C8, &arg0->unk5EC[sp2B4]);
            sp2D0.x += arg0->unk190.x;
            sp2D0.y += arg0->unk190.y;
            sp2D0.z += arg0->unk190.z;
            temp_fv1_4 = -uvVec3Dot(&sp2D0, &arg0->unk3B0[sp2B4].unk10);
            if (sp23C < temp_fv1_4) {
                sp23C = temp_fv1_4;
            }
            uvVec3Cross(&sp2D0, &arg0->unk3B0[sp2B4].unk10, &sp2D0);
            uvVec3Cross(&arg0->unk3B0[sp2B4].unk1C, &sp2D0, &arg0->unk3B0[sp2B4].unk10);
            arg0->unk3B0[sp2B4].unk50 = uvVec3Len(&arg0->unk3B0[sp2B4].unk1C);
            uvVec3Normal(&arg0->unk3B0[sp2B4].unk1C, &arg0->unk3B0[sp2B4].unk1C);
            uvVec3Cross(&arg0->unk3B0[sp2B4].unk28, &arg0->unk5EC[sp2B4], &arg0->unk3B0[sp2B4].unk10);
            arg0->unk3B0[sp2B4].unk28.x /= 100.0f;
            arg0->unk3B0[sp2B4].unk28.y /= 100.0f;
            arg0->unk3B0[sp2B4].unk28.z /= 100.0f;
            uvVec3Cross(&arg0->unk3B0[sp2B4].unk34, &arg0->unk5EC[sp2B4], &arg0->unk3B0[sp2B4].unk1C);
            arg0->unk3B0[sp2B4].unk34.x /= 100.0f;
            arg0->unk3B0[sp2B4].unk34.y /= 100.0f;
            arg0->unk3B0[sp2B4].unk34.z /= 100.0f;
            if ((sp244 < 2) && (temp_fv1_4 > 0.0f)) {
                sp110[sp244] = (f32)((arg0->unk3B0[sp2B4].unk44 + 1.0f) * temp_fv1_4);
            }
            if (temp_fv1_4 > 0.0f) {
                sp228[sp244++] = sp2B4;
            }
            if ((sp2B4 != arg0->unk528[var_s5_4]) || (var_s5_4 >= arg0->unk524)) {
                if (arg0->unk564[arg0->unk544] < temp_fv1_4) {
                    uvVec3Copy(&arg0->unk54C[arg0->unk544], &sp27C[sp2B4]);
                    arg0->unk545[arg0->unk544] = sp218[sp2B4];
                    arg0->unk564[arg0->unk544] = temp_fv1_4;
                }
            }
            if (sp2B4 == arg0->unk528[var_s5_4]) {
                var_s5_4++;
            }
        }
        if (arg0->unk564[arg0->unk544] > 0.0f) {
            arg0->unk547[arg0->unk544] = 1;
            arg0->unk544++;
        }
        if (arg0->unkC0 == 0) {
            if (sp23C >= 12.698f) {
                arg0->unkC1 = 1;
            } else if (sp23C >= 7.937f) {
                if ((arg0->unk50 == 0) && (arg0->unk6C == 0)) {
                    arg0->unkC1 = 1;
                }
            } else if (sp23C > 1.0f) {
                arg0->unk8C = D_8034F854;
            }
            if ((arg0->unk94 == 0xFF) && (arg0->unk50 >= 0) && (arg0->unk6C == 0) && (arg0->unk1A8 > 5.952f) && (func_802DC930(arg0->unkF8) != 0)) {
                arg0->unk94 = smoke_create();
                smoke_props(arg0->unk94, SMOKE_FX_1(160, 120, 70), SMOKE_FX_2(4.0f), SMOKE_FX_3(3.0f), SMOKE_FX_4(1.0f),
                            SMOKE_FX_5(-arg0->unk10.m[1][0], -arg0->unk10.m[1][1], 0.5f),
                            SMOKE_FX_6((sp27C[1].x + sp27C[2].x) * 0.5f, (sp27C[1].y + sp27C[2].y) * 0.5f, sp27C[1].z), SMOKE_FX_7(1), SMOKE_FX_END);
            }
            if ((arg0->unk50 == 0) && (sp23C < 12.698f)) {
                func_8032BE10()->unkC = func_80317978(arg0->unk10.m[3][0], arg0->unk10.m[3][1], arg0->unk10.m[3][2], &arg0->unk6C);
                arg0->unk50 = 1;
                arg0->unk54 = sp23C;
                if (arg0->unk6C != 0) {
                    arg0->unk4 = 0xFFFF;
                }
            }
        }
        if (sp244 != 0) {
            if (sp244 < 3) {
                for (i = 0; i < sp244; i++) {
                    sp2B4 = sp228[i];
                    for (j = 0; j < i; j++) {
                        temp_s2 = sp228[j];
                        uvVec3Cross(&sp2D0, &arg0->unk3B0[temp_s2].unk28, &arg0->unk5EC[sp2B4]);
                        sp120.m[j][i] = sp120.m[i][j] =
                            (uvVec3Dot(&arg0->unk3B0[sp2B4].unk10, &arg0->unk3B0[temp_s2].unk10) / 250.0f) + uvVec3Dot(&arg0->unk3B0[sp2B4].unk10, &sp2D0);
                    }
                    uvVec3Cross(&sp2D0, &arg0->unk3B0[sp2B4].unk28, &arg0->unk5EC[sp2B4]);
                    sp120.m[i][i] = uvVec3Dot(&arg0->unk3B0[sp2B4].unk10, &sp2D0) + 0.004f;
                }
                for (i = 0; i < sp244; i++) {
                    sp2B4 = sp228[i];
                    for (j = 0; j < sp244; j++) {
                        temp_s2 = sp228[j];
                        if (i == j) {
                            uvVec3Cross(&sp2D0, &arg0->unk3B0[sp2B4].unk34, &arg0->unk5EC[sp2B4]);
                            sp120.m[i][j] += -uvVec3Dot(&arg0->unk3B0[sp2B4].unk10, &sp2D0) * arg0->unk3B0[temp_s2].unk40;
                        } else {
                            uvVec3Cross(&sp2D0, &arg0->unk3B0[temp_s2].unk34, &arg0->unk5EC[sp2B4]);
                            sp120.m[i][j] += -((uvVec3Dot(&arg0->unk3B0[sp2B4].unk10, &arg0->unk3B0[temp_s2].unk1C) / 250.0f) +
                                               uvVec3Dot(&arg0->unk3B0[sp2B4].unk10, &sp2D0)) *
                                             arg0->unk3B0[temp_s2].unk40;
                        }
                    }
                }
            }
            if (sp244 < 3) {
                if (sp244 == 1) {
                    sp110[0] /= sp120.m[0][0];
                } else {
                    temp_fs0_3 = (sp120.m[0][0] * sp120.m[1][1]) - (sp120.m[0][1] * sp120.m[1][0]);
                    temp_fv0 = ((sp110[0] * sp120.m[1][1]) - (sp110[1] * sp120.m[0][1])) / temp_fs0_3;
                    sp110[1] = ((sp110[1] * sp120.m[0][0]) - (sp110[0] * sp120.m[1][0])) / temp_fs0_3;
                    sp110[0] = temp_fv0;
                }
                for (i = 0; i < sp244; i++) {
                    sp2B4 = sp228[i];
                    uvVec3Mul(&sp2D0, &arg0->unk3B0[sp2B4].unk1C, -arg0->unk3B0[sp2B4].unk40);
                    uvVec3Add(&sp2D0, &arg0->unk3B0[sp2B4].unk10, &sp2D0);
                    uvVec3Mul(&sp2D0, &sp2D0, sp110[i] / 250.0f);
                    uvVec3Add(&arg0->unk190, &arg0->unk190, &sp2D0);
                    uvVec3Mul(&sp2D0, &arg0->unk3B0[sp2B4].unk34, -arg0->unk3B0[sp2B4].unk40);
                    uvVec3Add(&sp2D0, &arg0->unk3B0[sp2B4].unk28, &sp2D0);
                    uvVec3Mul(&sp2D0, &sp2D0, sp110[i]);
                    uvVec3Add(&arg0->unk1C8, &arg0->unk1C8, &sp2D0);
                }
            } else {
                for (i = 0; i < sp244; i++) {
                    sp2B4 = sp228[i];
                    if (i == 0) {
                        sp16C = arg0->unk3B0[sp2B4].unk44;
                        sp168 = arg0->unk3B0[sp2B4].unk40;
                        uvVec3Copy(&sp2E8, &arg0->unk3B0[sp2B4].unk10);
                    } else {
                        sp16C += arg0->unk3B0[sp2B4].unk44;
                        sp168 += arg0->unk3B0[sp2B4].unk40;
                        uvVec3Add(&sp2E8, &sp2E8, &arg0->unk3B0[sp2B4].unk10);
                    }
                }
                sp168 /= sp244;
                sp16C /= sp244;
                uvVec3Mul(&sp2E8, &sp2E8, 1.0f / sp244);
                uvVec3Normal(&sp2E8, &sp2E8);
                uvVec3Cross(&sp2C4, &sp2E8, &arg0->unk190);
                uvVec3Cross(&sp2C4, &sp2C4, &sp2E8);
                uvVec3Normal(&sp2C4, &sp2C4);
                var_fs0 = uvVec3Dot(&arg0->unk190, &sp2E8);
                sp110[0] = (-(1.0f + sp16C) * var_fs0) / (1.0f - (uvVec3Dot(&sp2C4, &sp2E8) * sp168));
                uvVec3Mul(&sp2D0, &sp2C4, -sp168);
                uvVec3Add(&sp2D0, &sp2E8, &sp2D0);
                uvVec3Mul(&sp2D0, &sp2D0, sp110[0]);
                uvVec3Add(&arg0->unk190, &arg0->unk190, &sp2D0);
                uvVec3Mul(&arg0->unk1C8, &sp2E8, uvVec3Dot(&arg0->unk1C8, &sp2E8));
            }
        }
    } else {
        for (i = 0; i < 4; i++) {
            uvVec3Copy(&arg0->unk3B0[i].unk0, &sp24C[i]);
        }
        if (arg0->unkDC > 3.0f) {
            arg0->unk50 = 0;
        }
    }
    if ((arg0->unkC0 == 1) && (arg0->unk6C != 0) && ((arg0->unk190.y * 0.7f <= 40.0f) || (arg0->unk190.y * 0.7f >= 50.0f) || (arg0->unk9C == 0.0f))) {
        arg0->unk1C8.x = func_80313AF4(0.0f, arg0->unk1C8.x, 6.0f);
        arg0->unk1C8.y = func_80313AF4(0.0f, arg0->unk1C8.y, 6.0f);
        arg0->unk1C8.z = func_80313AF4(0.0f, arg0->unk1C8.z, 6.0f);
    }
    if (arg0->unkD0 != 0) {
        return 1;
    }

    if ((arg0->unkC0 == 1) && (arg0->unk524 == 0) && (arg0->unk8C >= 4.0f)) {
        arg0->unkC0 = 0;
        return 0;
    }

    if ((arg0->unkC0 != 1) && (arg0->unkC0 != 2) && (arg0->unkC0 != 3) && (arg0->unk510 > 0)) {
        arg0->unkC0 = 1;
        return 1;
    }
    if (arg0->unk510 > 0) {
        return 1;
    }
    return 0;
}

void func_80307A9C(GyrocopterData* arg0) {
    Vec3F sp24;

    sp24.x = func_80313F08(&D_80369528, SQ(arg0->unk364.x));
    if (arg0->unk364.x < 0.0f) {
        sp24.x = -sp24.x;
    }

    sp24.y = func_80313F08(&D_80369528, SQ(arg0->unk364.y));
    if (arg0->unk364.y < 0.0f) {
        sp24.y = -sp24.y;
    }

    sp24.z = func_80313F08(&D_80369528, SQ(arg0->unk364.z));
    if (arg0->unk364.z < 0.0f) {
        sp24.z = -sp24.z;
    }
    arg0->unk31C.x += sp24.x;
    arg0->unk31C.y += sp24.y;
    arg0->unk31C.z += sp24.z;
}

void func_80307BAC(GyrocopterData* arg0) {
    f32 sp54;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 sp48;
    s32 pad;
    f32 var_fv1;
    Vec3F sp34;
    f32 var_ft4;
    f32 var_fv1_2;

    sp48 = uvSinF(arg0->unkEC);
    temp_fv0 = uvCosF(arg0->unkEC);
    temp_fv1 = arg0->unk594 * 0.5f;
    D_80369070.unk4[1].unk0 = 1;
    D_80369070.unk4[1].unk1C.x = arg0->unk59C.x - sp48 * temp_fv1;
    D_80369070.unk4[1].unk1C.y = arg0->unk59C.y + temp_fv0 * temp_fv1;
    D_80369070.unk4[1].unk1C.z = arg0->unk59C.z;
    D_80369070.unk4[1].unk28.x = arg0->unk59C.x + sp48 * temp_fv1;
    D_80369070.unk4[1].unk28.y = arg0->unk59C.y - temp_fv0 * temp_fv1;
    D_80369070.unk4[1].unk28.z = arg0->unk59C.z;
    if ((arg0->unkC1 != 0) || (arg0->unkC0 == 2)) {
        arg0->unkE8 = func_80313AF4(0.0f, arg0->unkE8, 0.5f);
        return;
    }
    uvMat4LocalToWorld(&arg0->unk25C, &sp34, &arg0->unk364);
    sp54 = -(0.3f * sp34.z * sp34.z);
    if (-sp34.z < 0.0f) {
        sp54 = -sp54;
        if (sp54 < -10.0f) {
            sp54 = -10.0f;
        }
        if (sp54 > 200.0f) {
            sp54 = 200.0f;
        }
    }

    var_fv1 = SQ(arg0->unk364.y) / 25.0f;
    if (var_fv1 < 0.05f) {
        var_fv1 = 0.05f;
    } else if (var_fv1 > 1.0f) {
        var_fv1 = 1.0f;
    }
    sp34.x = 0.0f;
    sp34.y = 0.0f;
    sp34.z = sp54 * var_fv1;
    uvMat4LocalToWorld(&arg0->unk21C, &sp34, &sp34);
    arg0->unk31C.x += sp34.x;
    arg0->unk31C.y += sp34.y;
    arg0->unk31C.z += sp34.z;
    arg0->unk334.x += sp34.x;
    arg0->unk334.y += sp34.y;
    arg0->unk334.z += sp34.z;

    var_ft4 = ABS_NOEQ(sp54);
    var_fv1_2 = ABS_NOEQ(arg0->unk364.y);

    arg0->unkE8 = func_80313AF4((var_fv1_2 + var_ft4) * 3.0f, arg0->unkE8, 0.5f);
}

void func_80307E2C(GyrocopterData* arg0) {
    Vec3F sp1C;

    sp1C.x = 0.0f;
    sp1C.y = 0.0f;
    sp1C.z = -9.8f;
    uvMat4LocalToWorld(&arg0->unk110, &arg0->unk358, &sp1C);
    arg0->unk31C.x += arg0->unk358.x;
    arg0->unk31C.y += arg0->unk358.y;
    arg0->unk31C.z += arg0->unk358.z;
}

void func_80307EA8(GyrocopterData* arg0) {
    Vec3F spDC;
    f32 spD8;
    f32 temp_fv0;
    Vec3F spC8;

    if ((arg0->unkC1 != 0) || (arg0->unkC0 == 2)) {
        arg0->unkF0 = func_80313AF4(0.0f, arg0->unkF0, 0.5f);
        return;
    }
    if (D_8036957E == CLASS_B) {
        if (func_802E08F4(arg0->unk10.m[3][0], arg0->unk10.m[3][1], arg0->unk10.m[3][2]) != 0) {
            if (arg0->unk67E == 0) {
                arg0->unk67E = 1;
                snd_play_sfx(0x6D);
            }
            hudWarningText(-1, 0.0f, 0.0f);
            arg0->hasLowFuel = FALSE;
            arg0->fuelEmpty = FALSE;
            arg0->fuel = 1.0f;
        } else {
            arg0->unk67E = 0;
        }
    }
    if ((arg0->fuel > 0.0f) && arg0->usingFuel) {
        arg0->fuel -= func_80313F08(&D_803694D0, arg0->unkB4) * D_8034F854;
        if (arg0->fuel <= 0.0f) {
            arg0->usingFuel = FALSE;
        }
        if (arg0->fuel < 0.0f) {
            arg0->fuel = 0.0f;
        } else if (arg0->fuel > 1.0f) {
            arg0->fuel = 1.0f;
        }
    }

    if (arg0->unk10.m[3][2] > 700.0f) {
        spD8 = 1.0f - ((arg0->unk10.m[3][2] - 700.0f) / 100.0f);
        if (spD8 < 0.0f) {
            spD8 = 0.0f;
        }
    } else {
        spD8 = 1.0f;
    }
    if (arg0->usingFuel) {
        temp_fv0 = func_80313F08(&D_803692C0, -arg0->unk364.y);
        spDC.x = 0.0f;
        spDC.y = arg0->unkB4 * 0.24f * spD8 * 35.0f;
        spDC.z = arg0->unkB4 * 0.76f * spD8 * temp_fv0 * 35.0f;
        uvMat4LocalToWorld(&arg0->unk21C, &spDC, &spDC);
        if ((arg0->unk1F0 < 0.0f) && (arg0->unk190.y > 0.0f) && (arg0->unk7C == 0)) {
            spDC.y *= 0.9f;
        } else if ((arg0->unk1F0 > 0.0f) && (arg0->unk190.y > 0.0f) && (arg0->unk7C == 0)) {
            spDC.y *= 0.9f;
        }
        arg0->unk31C.x += spDC.x;
        arg0->unk31C.y += spDC.y;
        arg0->unk31C.z += spDC.z;
        arg0->unk334.x += spDC.x;
        arg0->unk334.y += spDC.y;
        arg0->unk334.z += spDC.z;
    }
    if (arg0->usingFuel) {
        arg0->unkF0 = func_80313AF4((arg0->unkB4 * 94.24764f) + 10.47196f, arg0->unkF0, 1.0f);
        if (arg0->unk98 == 0xFF) {
            spC8.x = -0.707f;
            spC8.y = -0.707f;
            spC8.z = 0.2f;
            uvMat4LocalToWorld(&arg0->unk150, &spC8, &spC8);
            arg0->unk98 = smoke_create();
            smoke_props(arg0->unk98, SMOKE_FX_1(200, 200, 200), SMOKE_FX_2(1.8f), SMOKE_FX_3(1.0f), SMOKE_FX_4(2.0f), SMOKE_FX_5(spC8.x, spC8.y, spC8.z),
                        SMOKE_FX_6(arg0->unk10.m[3][0], arg0->unk10.m[3][1], arg0->unk10.m[3][2]), SMOKE_FX_7(1), SMOKE_FX_END);
            spC8.x = 0.707f;
            spC8.y = -0.707f;
            spC8.z = 0.2f;
            uvMat4LocalToWorld(&arg0->unk150, &spC8, &spC8);
            arg0->unk9A = smoke_create();
            smoke_props(arg0->unk9A, SMOKE_FX_1(200, 200, 200), SMOKE_FX_2(1.8f), SMOKE_FX_3(1.0f), SMOKE_FX_4(2.0f), SMOKE_FX_5(spC8.x, spC8.y, spC8.z),
                        SMOKE_FX_6(arg0->unk10.m[3][0], arg0->unk10.m[3][1], arg0->unk10.m[3][2]), SMOKE_FX_7(1), SMOKE_FX_END);
        }
    } else {
        arg0->unkF0 = func_80313AF4(0.0f, arg0->unkF0, 0.5f);
    }
}

void func_80308478(GyrocopterData* arg0) {
    Vec3F sp44;
    Vec3F sp38;
    f32 temp_fv0;

    if (arg0->unkC0 == 0) {
        func_802E1754(arg0->unk10.m[3][0], arg0->unk10.m[3][1], arg0->unk10.m[3][2], &sp38);
        uvMat4LocalToWorld(&arg0->unk110, &sp44, &sp38);
        if ((uvVec3Len(&sp38) == 0.0f) && (arg0->unkB4 == 0.5) && (ABS_NOEQ(arg0->unk1FC) < 0.001f) && (ABS_NOEQ(arg0->unk200) < 0.001f) &&
            (ABS_NOEQ(arg0->unk1F0) < 0.001f) && (ABS_NOEQ(arg0->unk1F4) < 0.001f) && (arg0->unkA0 == 0.0f) && (arg0->unk9C == 0.0f) && (arg0->fuel > 0.0f)) {
            if (arg0->unk7C == 0) {
                arg0->unk7C = 1;
            }
        } else {
            arg0->unk7C = 0;
        }
    } else {
        sp44.x = sp44.y = sp44.z = 0.0f;
        sp38.x = sp38.y = sp38.z = 0.0f;
        arg0->unk7C = 0;
    }

    if (arg0->unk1A8 < 51.587303f) {
        temp_fv0 = arg0->unk1A8 / 51.587303f;
        temp_fv0 = SQ(temp_fv0);
        sp44.x *= temp_fv0;
        sp44.y *= temp_fv0;
        sp44.z *= temp_fv0;
        sp38.x *= temp_fv0;
        sp38.y *= temp_fv0;
        sp38.z *= temp_fv0;
    }
    arg0->unk364.x = sp44.x - arg0->unk190.x;
    arg0->unk364.y = sp44.y - arg0->unk190.y;
    arg0->unk364.z = sp44.z - arg0->unk190.z;
    arg0->unk31C.x += 0.21f * sp44.x;
    arg0->unk31C.y += 0.21f * sp44.y;
    arg0->unk31C.z += 0.21f * sp44.z;
    arg0->unk1B8.x += 0.21f * sp38.x;
    arg0->unk1B8.y += 0.21f * sp38.y;
    arg0->unk1B8.z += 0.21f * sp38.z;
}

void func_8030877C(GyrocopterData* arg0) {
    Vec3F sp2E4[3];
    Vec3F sp2C0[3];
    Vec3F sp2B4;
    Vec3F sp2A8;
    Vec3F sp29C;
    Mtx4F sp25C;
    f32 sp250[3] = { 0.0f, 0.0f, 0.0f };
    Unk802D3658_Unk1228* temp_s3;
    Unk802D3658_Unk1120* temp_v0_3;
    u8 sp247;
    u8 var_s0;
    u8 i;
    u8 j;
    f32 sp240;
    f32 temp_fv0;
    f32 var_fa0;
    f32 sp234;
    Unk802D3658_Unk1224 spF0;

    var_s0 = 0;
    arg0->unk544 = 0;

    for (i = 0; i < 2; i++) {
        arg0->unk564[i] = 0.0f;
        arg0->unk545[i] = 0;
    }
    arg0->unkC1 = 0;
    arg0->unkD0 = 0;
    sp247 = func_802DB050(&D_80369070, &D_80369178, arg0->objId, arg0->unk2, &arg0->unk10);

    for (i = 0; i < sp247; i++) {
        func_802DBE64(&D_80369070, &D_80369178, i, &arg0->unk110);
        temp_s3 = &D_80369178.unk4[i];
        if ((temp_s3->unk4 == 2) && (targets_8034473C(temp_s3->surfaceId, 1) == 0.0f)) {
            return;
        }
        if (temp_s3->unk0 == 0) {
            temp_v0_3 = &D_80369070.unk4[temp_s3->unk0];
            func_802DCA5C(&temp_v0_3->unk28, &temp_v0_3->unk1C, &temp_s3->unk28, &temp_s3->unk34, &sp2B4);
            sp2A8.x = arg0->unk10.m[3][0];
            sp2A8.y = arg0->unk10.m[3][1];
            sp2A8.z = arg0->unk10.m[3][2];
            uvMat4Copy(&sp25C, &arg0->unk10);
            uvMat4LocalTranslate(&sp25C, sp2B4.x, sp2B4.y, sp2B4.z);
            sp29C.x = sp25C.m[3][0];
            sp29C.y = sp25C.m[3][1];
            sp29C.z = sp25C.m[3][2];
            func_802DB224(&spF0, 0xFF, arg0->objId, arg0->unk2, &sp2A8, &sp29C);
            if (spF0.unk0 > 0) {
                for (j = 0; j < spF0.unk0; j++) {
                    if (spF0.unk4[j].unk4 == 2) {
                        var_s0++;
                    }
                }
                if (spF0.unk0 != var_s0) {
                    arg0->unkC0 = 3;
                    _uvDebugPrintf("hmot : you got stuck - forcing an instant crash\n");
                    return;
                }
            }

            uvMat4Copy(&arg0->unk10, &sp25C);
            arg0->unk668.x = arg0->unk10.m[3][0];
            arg0->unk668.y = arg0->unk10.m[3][1];
            arg0->unk668.z = arg0->unk10.m[3][2];
        }
    }

    for (i = 0; i < sp247; i++) {
        temp_s3 = &D_80369178.unk4[i];
        if ((temp_s3->unk4 != 2) || ((temp_s3->unk4 == 2) && (balls_802CC0D4(temp_s3->surfaceId) == 0))) {
            func_802DC814(&D_80369178.unk4[i], (Vec3F*)arg0->unk10.m[3]);
        }
        uvVec3Copy(&sp2E4[i], &temp_s3->unk28);
        uvVec3Copy(&sp2C0[i], &temp_s3->unk34);
        temp_fv0 = uvVec3Dot(&arg0->unk190, &sp2C0[i]);
        if (arg0->unk564[arg0->unk544] < temp_fv0) {
            uvVec3Copy(&arg0->unk54C[arg0->unk544], &temp_s3->unkC);
            arg0->unk545[arg0->unk544] = temp_s3->unk4;
            arg0->unk564[arg0->unk544] = temp_fv0;
        }

        switch (temp_s3->unk4) {
        case 2:
            sp240 = ballsPopped(temp_s3->surfaceId, &arg0->unk19C, &D_80369178);
            if (sp240 == 0.0f) {
                return;
            }
            break;
        case 4:
            if (arg0->unkC0 == 2) {
                smoke_props(arg0->unk96, SMOKE_FX_8(0), SMOKE_FX_END);
            }
            arg0->unkC0 = 3;
            arg0->unkD0 = 1;
            return;
        case 1:
        case 8:
            if (temp_s3->unk0 == 0) {
                sp240 = 0.4f;
            } else {
                sp240 = 1.0f;
            }
            break;
        default:
            break;
        }
        sp250[i] = sp240;
        temp_fv0 = uvVec3Dot(&arg0->unk19C, &temp_s3->unk1C);
        switch (temp_s3->unk0) {
        case 0:
            sp234 = 31.7f;
            break;
        case 1:
            sp234 = 19.8f;
            break;
        case 2:
            sp234 = 19.8f;
            break;
        }

        if (ABS_NOEQ(temp_fv0) > sp234) {
            if (arg0->unkC0 != 2) {
                arg0->unk96 = smoke_create();
                smoke_props(arg0->unk96, SMOKE_FX_1(0, 0, 0), SMOKE_FX_2(20.0f), SMOKE_FX_3(2.0f), SMOKE_FX_5(0.0f, 0.0f, 0.0f), SMOKE_FX_END);
            }
            arg0->unkC0 = 2;
        } else {
            if (arg0->unk1A8 > 0.0f) {
                var_fa0 = ABS_NOEQ(temp_fv0 / arg0->unk1A8);
                if (var_fa0 > 0.707f) {
                    if (arg0->unkC0 != 2) {
                        arg0->unk96 = smoke_create();
                        smoke_props(arg0->unk96, SMOKE_FX_1(0, 0, 0), SMOKE_FX_2(20.0f), SMOKE_FX_3(2.0f), SMOKE_FX_5(0.0f, 0.0f, 0.0f), SMOKE_FX_END);
                    }
                    arg0->unkC0 = 2;
                } else if (arg0->unkC0 != 2) {
                    arg0->unkC1 = temp_s3->unk4;
                }
            } else if (arg0->unkC0 != 2) {
                arg0->unkC1 = temp_s3->unk4;
            }
        }
    }

    if (sp247 > 2) {
        _uvDebugPrintf("Heli has more than 2 hits\n");
    } else if (sp247 > 0) {
        func_802DC380(sp247, &arg0->unk150, &arg0->unk190, &arg0->unk19C, &arg0->unk1C8, &sp2C0[0], &sp2C0[1], &sp2E4[0], &sp2E4[1], sp250[0], sp250[1], 0.004f,
                      0.01f, 0.01f, 0.01f);
    }

    if (arg0->unk564[arg0->unk544] > 0.0f) {
        arg0->unk547[arg0->unk544++] = 0;
    }
}

void func_80308F1C(GyrocopterData* arg0) {
    f32 sp54;
    Vec3F sp48;
    s32 sp44;
    Vec3F* sp2C;
    s32 pad[2];
    u8 sp37;

    sp2C = (Vec3F*)arg0->unk10.m[3];
    sp37 = db_getgnd(&arg0->unk668, sp2C, &arg0->unk674, &sp44, &sp54, &sp48);
    uvVec3Copy(&arg0->unkC4, func_802E02EC());

    if (((sp44 == -1) && (sp54 > 0.0f) && (sp37 != 0) && (arg0->unk10.m[3][2] > 0.0f)) || ((sp37 == 2) && (targets_8034473C(sp44, 1) == 0.0f))) {
        sp37 = 0;
    }
    if (sp37) {
        if (sp37 == 4) {
            if (arg0->unkC0 == 2) {
                smoke_props((s32)arg0->unk96, SMOKE_FX_8(0), SMOKE_FX_END);
            }
            arg0->unkD0 = 1;
            arg0->unkC0 = 3;
        }
        func_802E05CC(&arg0->unk10, func_802E02EC(), &sp48, 0);
        if (arg0->unk674 == 2) {
            arg0->unk674 = 1;
        } else {
            arg0->unk674 = 2;
        }
    }
    arg0->unk668.x = sp2C->x;
    arg0->unk668.y = sp2C->y;
    arg0->unk668.z = sp2C->z;
}

void func_80309090(GyrocopterData* arg0) {
    Vec3F sp4C;
    Vec3F sp40;
    f32 sp3C;
    f32 sp38;
    f32 temp_fv0;

    if (arg0->unkC0 != 0) {
        arg0->unk1AC.x = arg0->unk31C.x;
        arg0->unk1AC.y = arg0->unk31C.y;
        arg0->unk1AC.z = arg0->unk31C.z;
        arg0->unk1E0 = arg0->unk328.x;
        arg0->unk1E4 = arg0->unk328.y;
        arg0->unk1E8 = arg0->unk328.z;
        return;
    }

    arg0->unk1AC.x = arg0->unk31C.x;
    arg0->unk1AC.y = arg0->unk31C.y;
    arg0->unk1AC.z = arg0->unk31C.z;

    uvMat4LocalToWorld(&arg0->unk29C, &sp4C, &arg0->unk190);
    if ((sp4C.z < 0.0f) && (arg0->unkA0 < 0.0f) && (sp4C.y < 7.5f) && (((arg0->unk6D == 0) && (arg0->unk6E == 0)) || (arg0->unk6D == 1))) {
        if (sp4C.z > -40.0f) {
            uvMat4LocalToWorld(&arg0->unk29C, &sp40, &arg0->unk1AC);
            sp40.x = 0.0f;
            if (arg0->unk6D == 0) {
                arg0->unk70 = sp40.y;
                arg0->unk74 = ABS_NOEQ(sp40.y / sp4C.y);
            }
            if (sp4C.y > 0.0f) {
                if (arg0->unk70 != 0.0f) {
                    arg0->unk70 = func_80313AF4(0.0f, arg0->unk70, arg0->unk74);
                    if (ABS_NOEQ(arg0->unk70) < 0.00001f) {
                        arg0->unk70 = 0.0f;
                    }
                }
            } else {
                arg0->unk70 = -sp4C.y / D_8034F854;
            }
            sp40.y = arg0->unk70;
            sp40.z = (((0.5 - arg0->unkB4) * 0.20000000298023224) + .5) * (-9.800000190734863);
            uvMat4LocalToWorld(&arg0->unk2DC, &arg0->unk1AC, &sp40);
        } else {
            arg0->unk1AC.x = 0.0f;
            arg0->unk1AC.y = 0.0f;
            arg0->unk1AC.z = 0.0f;
        }
        arg0->unk1FC = (arg0->unk218 * -0.5f * arg0->unk1F0) / 0.7853982f;
        arg0->unk6D = 1;
        arg0->unk1F8 = -arg0->unk644 * arg0->unk214;
    } else {
        if (arg0->unk6D == 1) {
            arg0->unk6E = 1;
            arg0->unk78 = 0.0f;
        }
        arg0->unk6D = 0;
        if (arg0->unk6E != 0) {
            uvMat4LocalToWorld(&arg0->unk29C, &sp40, &arg0->unk1AC);
            if ((sp4C.z < -2.0f) && (arg0->unkA0 == 0.0f)) {
                sp38 = arg0->unk78;
                // FAKE
                sp3C = (0, sp40.z) + (sp4C.z / 3.0f);
                arg0->unk78 = func_80313AF4(1.0f, arg0->unk78, 6.0f);
                sp3C *= (sp38 * arg0->unk78);
                sp40.z -= sp3C;
                if (sp4C.y < 0.0f) {
                    sp40.y = -sp4C.y / D_8034F854;
                } else if (sp40.y < 0.0f) {
                    sp40.y = 0.0f;
                }
                uvMat4LocalToWorld(&arg0->unk2DC, &arg0->unk1AC, &sp40);
            } else {
                arg0->unk6E = 0;
            }
        }
    }
    if ((arg0->unk6D == 0) && (arg0->unk6E == 0)) {
        if (arg0->unk7C != 0) {
            if (ABS_NOEQ(arg0->unk1AC.y) < 0.08f) {
                if (arg0->unk7C == 1) {
                    arg0->unk80 = arg0->unk1AC.y;
                    arg0->unk84 = arg0->unk1AC.z;
                    arg0->unk88 = (arg0->unk1AC.z + ((4.0f * sp4C.z) / (100.0f * D_8034F854))) * -0.5f;
                } else if (arg0->unk7C > 100) {
                    arg0->unk7C = 1;
                    arg0->unk80 = 0.0f;
                    arg0->unk84 = 0.0f;
                    arg0->unk88 = (-2.0f * sp4C.z) / (100.0f * D_8034F854);
                }
                if (arg0->unk7C < 50.0f) {
                    temp_fv0 = arg0->unk7C / 50.0f;
                    arg0->unk1AC.z = arg0->unk84 + ((arg0->unk88 - arg0->unk84) * temp_fv0);
                } else if (arg0->unk7C < 100) {
                    temp_fv0 = (1.0f - ((arg0->unk7C - 50.0f) / 50.0f));
                    arg0->unk1AC.z = arg0->unk88 * temp_fv0;
                } else {
                    arg0->unk1AC.y = 0.0f;
                    arg0->unk1AC.z = 0.0f;
                }
                if (arg0->unk7C < 100) {
                    if (arg0->unk80 > 0.0f) {
                        temp_fv0 = arg0->unk7C / 100.0f;
                        arg0->unk1AC.y = arg0->unk80 * (1.0f - temp_fv0);
                    }
                    arg0->unk7C++;
                } else {
                    if (ABS_NOEQ(arg0->unk190.z) > 0.00001f) {
                        arg0->unk7C++;
                    }
                }
            }
        }
    }
    if ((arg0->unk6D == 0) && (arg0->unk6E == 0) && (arg0->unk7C == 0)) {
        if (arg0->unk190.y > 97.222f) {
            if (arg0->unk90 < arg0->unk1AC.y) {
                if (arg0->unk90 == 0.0f) {
                    arg0->unk90 = arg0->unk1AC.y;
                    arg0->unk74 = arg0->unk1AC.y / (99.206f - arg0->unk190.y);
                }
                if (arg0->unk190.y < 99.206f) {
                    if (arg0->unk90 != 0.0f) {
                        arg0->unk90 = func_80313AF4(0.0f, arg0->unk90, arg0->unk74);
                        if (arg0->unk1AC.y < arg0->unk90) {
                            arg0->unk90 = arg0->unk1AC.y;
                        }
                        if (ABS_NOEQ(arg0->unk90) < 0.00001f) {
                            arg0->unk90 = 0.0f;
                        }
                    }
                } else {
                    arg0->unk90 = 0.0f;
                }
                arg0->unk1AC.y = arg0->unk90;
                return;
            }
        }
    }
    arg0->unk90 = 0.0f;
}
