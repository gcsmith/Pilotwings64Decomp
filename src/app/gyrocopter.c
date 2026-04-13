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
#include "app/code_66F70.h"
#include "app/code_9A960.h"
#include "app/code_B2900.h"

void func_80304738(GyrocopterData* gcData);
void func_80304B98(GyrocopterData* gcData);
void func_80305BE8(GyrocopterData* gcData);
s32 func_80305DC0(GyrocopterData* gcData);
void func_80307A9C(GyrocopterData* gcData);
void func_80307BAC(GyrocopterData* gcData);
void func_80307E2C(GyrocopterData* gcData);
void func_80307EA8(GyrocopterData* gcData);
void func_80308478(GyrocopterData* gcData);
void func_8030877C(GyrocopterData* gcData);
void func_80308F1C(GyrocopterData* gcData);
void func_80309090(GyrocopterData* gcData);

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
u16 D_8036957E; // holds a class value

void func_80303230(GyrocopterData* gcData) {
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
    D_80369070.unk4[0].unk1C.x = gcData->unk5BC.x;
    D_80369070.unk4[0].unk1C.y = gcData->unk5BC.y;
    D_80369070.unk4[0].unk1C.z = gcData->unk5BC.z;
    D_80369070.unk4[0].unk28.x = gcData->unk5C8.x;
    D_80369070.unk4[0].unk28.y = gcData->unk5C8.y;
    D_80369070.unk4[0].unk28.z = gcData->unk5C8.z;
    D_80369070.unk4[1].unk0 = 1;
    D_80369070.unk4[1].unk1C.x = gcData->unk59C.x;
    D_80369070.unk4[1].unk1C.y = gcData->unk59C.y - (0.5f * gcData->unk594);
    D_80369070.unk4[1].unk1C.z = gcData->unk59C.z;
    D_80369070.unk4[1].unk28.x = gcData->unk59C.x;
    D_80369070.unk4[1].unk28.y = gcData->unk59C.y + (0.5f * gcData->unk594);
    D_80369070.unk4[1].unk28.z = gcData->unk59C.z;

    D_803692C0.count = 5;
    D_803692C0.unk4[0].x = 0.0f, D_803692C0.unk4[0].y = 0.f;
    D_803692C0.unk4[1].x = 10.0f, D_803692C0.unk4[1].y = 0.15f;
    D_803692C0.unk4[2].x = 20.0f, D_803692C0.unk4[2].y = 0.4f;
    D_803692C0.unk4[3].x = 50.0f, D_803692C0.unk4[3].y = 1.2f;
    D_803692C0.unk4[4].x = 100.0f, D_803692C0.unk4[4].y = 1.5f;

    D_80369370.count = 2;
    D_80369370.unk4[0].x = 0.0f, D_80369370.unk4[0].y = -0.5f;
    D_80369370.unk4[1].x = 5.0f, D_80369370.unk4[1].y = 1.00f;

    D_803694D0.count = 3;
    D_803694D0.unk4[0].x = 0.0f, D_803694D0.unk4[0].y = 0.001f;
    D_803694D0.unk4[1].x = 0.5f, D_803694D0.unk4[1].y = 0.002f;
    D_803694D0.unk4[2].x = 1.f, D_803694D0.unk4[2].y = 0.005f;

    D_80369318.count = 5;
    D_80369318.unk4[0].x = 0.0f, D_80369318.unk4[0].y = 0.f;
    D_80369318.unk4[1].x = 5.0f, D_80369318.unk4[1].y = 0.250f;
    D_80369318.unk4[2].x = 10.0f, D_80369318.unk4[2].y = 0.4f;
    D_80369318.unk4[3].x = 20.0f, D_80369318.unk4[3].y = 0.20f;
    D_80369318.unk4[4].x = 50.0f, D_80369318.unk4[4].y = 0.1f;

    D_80369478.count = 6;
    D_80369478.unk4[0].x = 0.f, D_80369478.unk4[0].y = 0.00f;
    D_80369478.unk4[1].x = 0.25f, D_80369478.unk4[1].y = 0.18f;
    D_80369478.unk4[2].x = 0.50f, D_80369478.unk4[2].y = 0.40f;
    D_80369478.unk4[3].x = 1.00f, D_80369478.unk4[3].y = 1.000f;
    D_80369478.unk4[4].x = 2.0f, D_80369478.unk4[4].y = 2.0f;
    D_80369478.unk4[5].x = 10.00f, D_80369478.unk4[5].y = 10.00f;

    D_803693C8.count = 2;
    D_803693C8.unk4[0].x = 0.f, D_803693C8.unk4[0].y = 1.000f;
    D_803693C8.unk4[1].x = 1.00f, D_803693C8.unk4[1].y = 1.000f;

    D_80369420.count = 2;
    D_80369420.unk4[0].x = 0.f, D_80369420.unk4[0].y = 1.000f;
    D_80369420.unk4[1].x = 1.00f, D_80369420.unk4[1].y = 0.000f;

    gcData->unk3B0[0].unk40 = 0.2f;
    gcData->unk3B0[1].unk40 = 0.2f;
    gcData->unk3B0[2].unk40 = 0.2f;
    gcData->unk3B0[3].unk40 = 0.2f;
    gcData->unk3B0[0].unk44 = 0.0f;
    gcData->unk3B0[1].unk44 = 0.0f;
    gcData->unk3B0[2].unk44 = 0.0f;
    gcData->unk3B0[3].unk44 = 0.0f;

    D_80369528.count = 3;
    D_80369528.unk4[0].x = 0.f, D_80369528.unk4[0].y = 0.0f;
    D_80369528.unk4[1].x = 2661.2188f, D_80369528.unk4[1].y = 4.2f;
    D_80369528.unk4[2].x = 6944.389f, D_80369528.unk4[2].y = 7.5599995f;

    temp_fv1 = gcData->unk5EC[0].x - gcData->unk5EC[2].x;
    temp_fa0 = gcData->unk5EC[1].y - gcData->unk5EC[2].y;
    temp_fa1 = gcData->unk5EC[0].y - gcData->unk5EC[2].y;
    temp_ft4 = gcData->unk5EC[1].x - gcData->unk5EC[2].x;
    sp78 = (temp_fv1 * temp_fa0) - (temp_fa1 * temp_ft4);
    gcData->unk3B0[0].unk48 = (((gcData->unk538.x - gcData->unk5EC[2].x) * temp_fa0) - ((gcData->unk538.y - gcData->unk5EC[2].y) * temp_ft4)) / sp78;
    gcData->unk3B0[1].unk48 = (((gcData->unk538.y - gcData->unk5EC[2].y) * temp_fv1) - ((gcData->unk538.x - gcData->unk5EC[2].x) * temp_fa1)) / sp78;
    gcData->unk3B0[2].unk48 = (1.0000f - gcData->unk3B0[0].unk48) - gcData->unk3B0[1].unk48;
    gcData->unk3B0[3].unk48 = 0.0f;
    temp_fv1 = gcData->unk5EC[3].x - gcData->unk5EC[1].x;
    temp_fa0 = gcData->unk5EC[2].y - gcData->unk5EC[1].y;
    temp_fa1 = gcData->unk5EC[3].y - gcData->unk5EC[1].y;
    temp_ft4 = gcData->unk5EC[2].x - gcData->unk5EC[1].x;
    sp78 = (temp_fv1 * temp_fa0) - (temp_fa1 * temp_ft4);
    gcData->unk3B0[3].unk4C = (((gcData->unk538.x - gcData->unk5EC[1].x) * temp_fa0) + ((gcData->unk538.y + gcData->unk5EC[1].y) * temp_ft4)) / sp78;
    gcData->unk3B0[2].unk4C = -(((gcData->unk538.y + gcData->unk5EC[1].y) * temp_fv1) + ((gcData->unk538.x - gcData->unk5EC[1].x) * temp_fa1)) / sp78;
    gcData->unk3B0[1].unk4C = (1.0f - gcData->unk3B0[3].unk4C) - gcData->unk3B0[2].unk4C;
    gcData->unk3B0[0].unk4C = 0.0f;
    gcData->unk96 = 0xFF;
    func_80303714(gcData);
    gcData->unk4 = D_8036957C = 0xF7F8;
    taskGetClsVehTest(&D_8036957E, &sp66, &sp64);
}

void func_80303714(GyrocopterData* gcData) {
    s32 i;
    f32 sp88;
    f32 sp84;
    f32 sp80;
    Vec3F sp74;

    gcData->unk19C.x = 0.0f;
    gcData->unk19C.y = 0.0f;
    gcData->unk19C.z = 0.0f;
    gcData->unk1AC.x = 0.0f;
    gcData->unk1AC.y = 0.0f;
    gcData->unk1AC.z = 0.0f;
    gcData->unk1B8.x = 0.0f;
    gcData->unk1B8.y = 0.0f;
    gcData->unk1B8.z = 0.0f;
    gcData->unk1C8.x = 0.0f;
    gcData->unk1C8.y = 0.0f;
    gcData->unk1C8.z = 0.0f;
    gcData->unk1E0 = 0.0f;
    gcData->unk1E4 = 0.0f;
    gcData->unk1E8 = 0.0f;
    gcData->unk1EC = 0.0f;
    gcData->unk1F0 = 0.0f;
    gcData->unk1F4 = 0.0f;
    gcData->unk1F8 = 0.0f;
    gcData->unk1FC = 0.0f;
    gcData->unk200 = 0.0f;
    gcData->unk364.x = 0.0f;
    gcData->unk364.y = 0.0f;
    gcData->unk364.z = 0.0f;
    gcData->unk340 = 0.0f;
    gcData->unk344 = 0.0f;
    gcData->unk348 = 1.0f;
    gcData->unk100.x = 0.0f;
    gcData->unk100.y = 0.0f;
    gcData->unk100.z = 1.0f;
    gcData->unk358.x = 0.0f;
    gcData->unk358.y = 0.0f;
    gcData->unk358.z = -9.8f;
    gcData->unkC1 = 0;
    gcData->unkD0 = 0;
    gcData->unk10C = 0xFF;
    gcData->unk50 = -1;
    gcData->unk31C.x = 0.0f;
    gcData->unk31C.y = 0.0f;
    gcData->unk31C.z = 0.0f;
    gcData->unk328.x = 0.0f;
    gcData->unk328.y = 0.0f;
    gcData->unk328.z = 0.0f;
    gcData->unk334.x = 0.0f;
    gcData->unk334.y = 0.0f;
    gcData->unk334.z = 0.0f;
    gcData->unk1A8 = 0.0f;
    gcData->unk1C4 = 0.0f;
    gcData->unkE0 = 0.0f;
    gcData->unk9C = 0.0f;
    gcData->unkA0 = 0.0f;
    gcData->unkAC = 0.0f;
    gcData->unkE8 = 0.0f;
    gcData->unkEC = 1.5707963f;
    gcData->unkF4 = 0.0f;
    gcData->unk54 = 0.0f;
    gcData->unk70 = 0.0f;
    gcData->unk90 = 0.0f;
    gcData->unk8C = 4.0f;
    gcData->fuelEmpty = FALSE;
    gcData->unk6C = 0;
    gcData->unk6E = 0;
    gcData->unk98 = 0xFF;
    gcData->unk9A = 0xFF;
    gcData->unk94 = 0xFF;
    if (gcData->unk96 != 0xFF) {
        smokeProps(gcData->unk96, SMOKE_PROP_8(0), SMOKE_PROP_END);
    }

    uvMat4Copy(&gcData->unk150, &gcData->unk10);
    gcData->unk150.m[3][0] = gcData->unk150.m[3][1] = gcData->unk150.m[3][2] = 0.0f;
    uvMat4LocalToWorld(&gcData->unk150, &gcData->unk19C, &gcData->unk190);

    for (i = 0; i < 4; i++) {
        // FAKE
        if (0) { }
        sp74.x = gcData->unk5EC[i].x;
        sp74.y = gcData->unk5EC[i].y;
        sp74.z = 0.0f;
        uvMat4LocalToWorld(&gcData->unk10, &gcData->unk3B0[i].unk0, &sp74);
        gcData->unk3B0[i].unkC = 1;
    }
    gcData->unk674 = 1;
    gcData->unk668.x = gcData->unk10.m[3][0];
    gcData->unk668.y = gcData->unk10.m[3][1];
    gcData->unk668.z = gcData->unk10.m[3][2];
    func_80313570(&gcData->unk10, &sp88, &sp84, &sp80, &gcData->unk1EC, &gcData->unk1F0, &gcData->unk1F4);
}

extern f32 D_8034F850;
extern f32 D_8034F854;
extern u16 D_8036957C;

void func_8030399C(GyrocopterData* gcData) {
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

    gcData->unk31C.x = 0.0f;
    gcData->unk31C.y = 0.0f;
    gcData->unk31C.z = 0.0f;
    gcData->unk328.x = 0.0f;
    gcData->unk328.y = 0.0f;
    gcData->unk328.z = 0.0f;
    gcData->unk334.x = 0.0f;
    gcData->unk334.y = 0.0f;
    gcData->unk334.z = 0.0f;
    func_80307A9C(gcData);
    func_80307E2C(gcData);
    func_80308478(gcData);
    func_80307BAC(gcData);
    func_80307EA8(gcData);

    switch (gcData->unkC0) {
    case 0:
        func_80304738(gcData);
        break;
    case 1:
    case 4:
        func_80304B98(gcData);
        break;
    case 2:
        func_80305BE8(gcData);
        break;
    case 3:
        return;
    default:
        break;
    }
    func_80309090(gcData);
    if ((gcData->unkC0 == 0) && (gcData->unk190.z < gcData->unk190.y) && (gcData->unk6D == 0)) {
        gcData->unk1B8.x = (gcData->unk1AC.x - (gcData->unk190.y * gcData->unk1C8.z)) + (gcData->unk190.z * gcData->unk1C8.y);
        gcData->unk1B8.y = (gcData->unk1AC.y - (gcData->unk190.z * gcData->unk1C8.x)) + (gcData->unk190.x * gcData->unk1C8.z);
        gcData->unk1B8.z = (gcData->unk1AC.z - (gcData->unk190.x * gcData->unk1C8.y)) + (gcData->unk190.y * gcData->unk1C8.x);
        uvMat4LocalToWorld(&gcData->unk150, &gcData->unk1B8, &gcData->unk1B8);
    } else {
        if (gcData->unkC0 == 1) {
            uvMat4LocalToWorld(&gcData->unk150, &gcData->unk1B8, &gcData->unk1AC);
            gcData->unk1AC.x += (gcData->unk190.y * gcData->unk1C8.z) - (gcData->unk190.z * gcData->unk1C8.y);
            gcData->unk1AC.y += (gcData->unk190.z * gcData->unk1C8.x) - (gcData->unk190.x * gcData->unk1C8.z);
            gcData->unk1AC.z += (gcData->unk190.x * gcData->unk1C8.y) - (gcData->unk190.y * gcData->unk1C8.x);
        } else {
            uvMat4LocalToWorld(&gcData->unk150, &gcData->unk1B8, &gcData->unk1AC);
        }
    }

    if (gcData->unkC0 == 0) {
        gcData->unk1C8.x = gcData->unk1D4;
        gcData->unk1C8.y = gcData->unk1D8;
        gcData->unk1C8.z = gcData->unk1DC;
        gcData->unk1EC += D_8034F854 * gcData->unk1F8;
        gcData->unk1F0 += D_8034F854 * gcData->unk1FC;
        gcData->unk1F4 += D_8034F854 * gcData->unk200;
    } else {
        gcData->unk1C8.x += D_8034F854 * gcData->unk1E0;
        gcData->unk1C8.y += D_8034F854 * gcData->unk1E4;
        gcData->unk1C8.z += D_8034F854 * gcData->unk1E8;
        if (gcData->unkC0 != 2) {
            spE4 = uvSinF(gcData->unk1F4);
            spE0 = uvCosF(gcData->unk1F4);
            spDC = uvSinF(gcData->unk1F0);
            gcData->unk1F8 = ((gcData->unk1C8.z * spE0) - (gcData->unk1C8.x * spE4)) / uvCosF(gcData->unk1F0);
            gcData->unk1FC = (gcData->unk1C8.x * spE0) + (gcData->unk1C8.z * spE4);
            gcData->unk200 = gcData->unk1C8.y - (gcData->unk1F8 * spDC);
            gcData->unk1EC += D_8034F854 * gcData->unk1F8;
            gcData->unk1F0 += D_8034F854 * gcData->unk1FC;
            gcData->unk1F4 += D_8034F854 * gcData->unk200;
        }
    }
    spF4 = gcData->unk10.m[3][0];
    spF8 = gcData->unk10.m[3][1];
    spFC = gcData->unk10.m[3][2];
    if (gcData->unkC0 == 2) {
        gcData->unk10.m[3][2] = 0.0f;
        gcData->unk10.m[3][1] = 0.0f;
        gcData->unk10.m[3][0] = 0.0f;
        uvMat4RotateAxis(&gcData->unk10, gcData->unk1C8.z * D_8034F854, 'z');
        uvMat4RotateAxis(&gcData->unk10, gcData->unk1C8.x * D_8034F854, 'x');
        uvMat4RotateAxis(&gcData->unk10, gcData->unk1C8.y * D_8034F854, 'y');
    } else {
        func_80313640(0.0f, 0.0f, 0.0f, gcData->unk1EC, gcData->unk1F0, gcData->unk1F4, &gcData->unk10);
    }
    uvMat4Copy(&gcData->unk150, &gcData->unk10);
    uvMat4InvertTranslationRotation(&gcData->unk110, &gcData->unk150);
    if (gcData->unkC0 == 1) {
        gcData->unk190.x += D_8034F854 * gcData->unk1AC.x;
        gcData->unk190.y += D_8034F854 * gcData->unk1AC.y;
        gcData->unk190.z += D_8034F854 * gcData->unk1AC.z;
        uvMat4LocalToWorld(&gcData->unk150, &gcData->unk19C, &gcData->unk190);
    } else {
        gcData->unk19C.x += D_8034F854 * gcData->unk1B8.x;
        gcData->unk19C.y += D_8034F854 * gcData->unk1B8.y;
        gcData->unk19C.z += D_8034F854 * gcData->unk1B8.z;
        uvMat4LocalToWorld(&gcData->unk110, &gcData->unk190, &gcData->unk19C);
    }

    gcData->unk10.m[3][0] = (gcData->unk19C.x * D_8034F854) + spF4;
    gcData->unk10.m[3][1] = (gcData->unk19C.y * D_8034F854) + spF8;
    gcData->unk10.m[3][2] = (gcData->unk19C.z * D_8034F854) + spFC;
    if (gcData->unkC0 == 3) {
        return;
    }

    if (gcData->unkC0 == 0) {
        func_80313640(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, gcData->unk1F4, &gcData->unk25C);
        func_80313640(0.0f, 0.0f, 0.0f, 0.0f, gcData->unk1F0, gcData->unk1F4, &gcData->unk29C);
        func_80313640(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -gcData->unk1F4, &gcData->unk21C);
        uvMat4InvertTranslationRotation(&gcData->unk2DC, &gcData->unk29C);
    } else {
        temp_fv0 = uvSqrtF(1.0f - SQ(gcData->unk10.m[1][2]));
        spEC = gcData->unk10.m[2][2] / temp_fv0;
        spE8 = -gcData->unk10.m[0][2] / temp_fv0;
        uvMat4SetIdentity(&gcData->unk25C);
        gcData->unk25C.m[2][0] = spE8;
        gcData->unk25C.m[0][2] = -spE8;
        gcData->unk25C.m[2][2] = spEC;
        gcData->unk25C.m[0][0] = spEC;
        uvMat4SetIdentity(&gcData->unk21C);
        gcData->unk21C.m[0][0] = spEC;
        gcData->unk21C.m[2][2] = spEC;
        gcData->unk21C.m[2][0] = -spE8;
        gcData->unk21C.m[0][2] = spE8;
    }
    func_80308F1C(gcData);
    if (gcData->unkC0 == 3) {
        return;
    }
    func_8030877C(gcData);
    if (gcData->unkC0 == 3) {
        return;
    }
    func_80305DC0(gcData);

    if (gcData->unkC0 == 3) {
        return;
    }
    if (gcData->unkC0 == 0) {
        if ((ABS_NOEQ(gcData->unk1C8.z) < 0.0001f) &&
            (((gcData->unk31C.x > 0.f) && (gcData->unk190.x < 0.f)) || ((gcData->unk31C.x < 0.f) && (gcData->unk190.x > 0.f)))) {
            gcData->unk190.x = func_80313AF4(0.f, gcData->unk190.x, 6.0f);
            uvMat4LocalToWorld(&gcData->unk150, &gcData->unk19C, &gcData->unk190);
        }
    }
    gcData->unk1A8 = uvVec3Len(&gcData->unk19C);
    gcData->unk1C4 = uvVec3Len(&gcData->unk1B8);
    if ((gcData->unk1A8 < 0.1f) || ((gcData->unkC0 == 1) && (gcData->fuel == 0.0f) && (gcData->unk190.y < 0.1f))) {
        gcData->unkC0 = 4;
        if (gcData->unk6C == 0) {
            gcData->unk4 = D_8036957C;
            if (gcData->unk50 == 1) {
                hudText_8031D8E0(0xA2, 1.5f, 8.0f);
            }
        } else if (gcData->unk50 == 1) {
            if (gcData->unk4 != D_8036957C) {
                hudText_8031D8E0(0x12A, 1.5f, 8.0f);
            } else {
                hudText_8031D8E0(0xA2, 1.5f, 8.0f);
            }
        }
    }

    if ((ABS_NOEQ(gcData->unk1F0) > 0.8028515f) || (ABS_NOEQ(gcData->unk1F4) > 1.0646509f)) {
        if (gcData->unkC0 != 2) {
            gcData->unkC0 = 2;
            gcData->unk96 = smokeCreate();
            // clang-format off
            smokeProps(
                gcData->unk96,
                SMOKE_PROP_1(0, 0, 0),
                SMOKE_PROP_2(20.0f),
                SMOKE_PROP_3(2.0f),
                SMOKE_PROP_5(0.0f, 0.0f, 0.0f),
                SMOKE_PROP_END
            );
            // clang-format on
        }
    }
    if (gcData->unkC0 == 2) {
        smokeProps(gcData->unk96, SMOKE_PROP_6(gcData->unk10.m[3][0], gcData->unk10.m[3][1], gcData->unk10.m[3][2]), SMOKE_PROP_END);
    } else {
        if ((gcData->unk98 != -1) && (gcData->unk98 != 0xFF)) {
            smokeGetProps(gcData->unk98, 8, &spD6, 0);
            if (spD6 != 0) {
                smokeProps(gcData->unk98, SMOKE_PROP_6(gcData->unk10.m[3][0], gcData->unk10.m[3][1], gcData->unk10.m[3][2]), SMOKE_PROP_END);
                smokeProps(gcData->unk9A, SMOKE_PROP_6(gcData->unk10.m[3][0], gcData->unk10.m[3][1], gcData->unk10.m[3][2]), SMOKE_PROP_END);
            } else {
                gcData->unk98 = -1;
                gcData->unk9A = -1;
            }
        }
        if (gcData->unk94 != 0xFF) {
            smokeGetProps(gcData->unk94, 8, &spD6, 0);
            if (spD6 != 0) {
                if ((gcData->unkC0 == 1) && (gcData->unk1A8 > 5.952f) && (gcData->unk6C == 0) && (func_802DC930(gcData->unkF8) != 0)) {
                    smokeGetProps(gcData->unk94, 4, &spD0, 0);
                    // clang-format off
                    smokeProps(
                        gcData->unk94,
                        SMOKE_PROP_6(((gcData->unk3B0[1].unk0.x + gcData->unk3B0[2].unk0.x) * 0.5f), (gcData->unk3B0[1].unk0.y + gcData->unk3B0[2].unk0.y) * 0.5f, gcData->unk3B0[1].unk0.z),
                        SMOKE_PROP_4(spD0 + D_8034F854),
                        SMOKE_PROP_7(1),
                        SMOKE_PROP_END
                    );
                    // clang-format on
                } else {
                    smokeProps(gcData->unk94, SMOKE_PROP_4(0.0f), SMOKE_PROP_END);
                }
            } else {
                gcData->unk94 = 0xFF;
            }
        } else if ((gcData->unkC0 == 1) && (gcData->unk1A8 > 5.952f) && (gcData->unk50 >= 0) && (gcData->unk6C == 0) && (func_802DC930(gcData->unkF8) != 0)) {
            gcData->unk94 = smokeCreate();
            // clang-format off
            smokeProps(
                gcData->unk94,
                SMOKE_PROP_1(160, 120, 70),
                SMOKE_PROP_2(4.0f),
                SMOKE_PROP_3(3.0f),
                SMOKE_PROP_4(1.0f),
                SMOKE_PROP_5(-gcData->unk10.m[1][0], -gcData->unk10.m[1][1], 0.5f),
                SMOKE_PROP_6((gcData->unk3B0[1].unk0.x + gcData->unk3B0[2].unk0.x) * 0.5f, (gcData->unk3B0[1].unk0.y + gcData->unk3B0[2].unk0.y) * 0.5f, gcData->unk3B0[1].unk0.z),
                SMOKE_PROP_7(1),
                SMOKE_PROP_END
            );
            // clang-format on
        }
    }
    if (D_80362690->unkA4) {
        demoAttUpdate(D_8034F850, &gcData->unk10);
    }
}

void func_80304738(GyrocopterData* gcData) {
    f32 temp_fv1;
    f32 var_ft4;
    f32 temp_fv0;
    f32 var_fa1;
    f32 var_ft4_2;
    f32 temp_fv1_3;
    f32 var_fa1_3;
    f32 temp_fa1;

    gcData->unk204 = uvSinF(gcData->unk1EC);
    gcData->unk208 = uvCosF(gcData->unk1EC);
    gcData->unk20C = uvSinF(gcData->unk1F0);
    gcData->unk210 = uvCosF(gcData->unk1F0);
    gcData->unk214 = uvSinF(gcData->unk1F4);
    gcData->unk218 = uvCosF(gcData->unk1F4);
    temp_fv1 = gcData->unk9C - gcData->unkA4;
    var_ft4 = ABS_NOEQ(temp_fv1);

    if ((var_ft4 / D_8034F854) > 5.0f) {
        gcData->unk9C = gcData->unkA4 + ((5.0f * D_8034F854 * temp_fv1) / var_ft4);
    }

    temp_fv0 = gcData->unkA0 - gcData->unkA8;
    var_fa1 = ABS_NOEQ(temp_fv0);
    if ((var_fa1 / D_8034F854) > 5.0f) {
        gcData->unkA0 = gcData->unkA8 + ((5.0f * D_8034F854 * temp_fv0) / var_fa1);
    }

    if (var_ft4 >= 0.0f) {
        gcData->unk200 = (ABS_NOEQ(gcData->unk9C) * gcData->unk9C) - (gcData->unk1F4 / 1.0471976f);
    } else {
        gcData->unk200 = ((ABS_NOEQ(gcData->unk9C) * gcData->unk9C) - (gcData->unk1F4 / 1.0471976f)) * 104.0f;
    }

    gcData->unkA4 = gcData->unk9C;
    if (gcData->unk190.y > 39.68254f) {
        var_ft4_2 = 1.0f - (((gcData->unk190.y - 39.68254f) * 0.3f) / 39.68254f);
    } else {
        var_ft4_2 = (((39.68254f - gcData->unk190.y) * 1.5f) / 39.68254f) + 1.0f;
    }
    if (gcData->unk190.y > 0.0f) {
        gcData->unk1F8 = (-gcData->unk190.y * var_ft4_2 * gcData->unk214) / gcData->unk640;
    } else {
        gcData->unk1F8 = 0.0f;
    }
    temp_fv1_3 = 15.873016f;
    if ((temp_fv1_3 * 3.0f) < gcData->unk190.y) {
        var_ft4_2 = 1.0f - (((gcData->unk190.y - (temp_fv1_3 * 3.0f)) * 0.3f) / (2.0f * temp_fv1_3));
    } else {
        var_ft4_2 = ((((temp_fv1_3 * 3.0f) - gcData->unk190.y) * 0.5f) / (temp_fv1_3 * 3.0f)) + 1.0f;
    }
    if (var_fa1 >= 0.0f) {
        var_fa1_3 = ABS_NOEQ(gcData->unk190.y);
        gcData->unk1FC = ((ABS_NOEQ(gcData->unkA0) * gcData->unkA0) + (gcData->unk1F0 / 0.7853982f)) * (-0.0064f * var_ft4_2 * var_fa1_3 * gcData->unk218);
    } else {
        var_fa1_3 = ABS_NOEQ(gcData->unk190.y);
        gcData->unk1FC = ((ABS_NOEQ(gcData->unkA0) * gcData->unkA0) + (gcData->unk1F0 / 0.7853982f)) * (-90.0f * var_ft4_2 * var_fa1_3 * gcData->unk218);
    }

    temp_fa1 = gcData->unk1F8 * gcData->unk210;
    gcData->unkA8 = gcData->unkA0;
    gcData->unk1D4 = (gcData->unk1FC * gcData->unk218) - (temp_fa1 * gcData->unk214);
    gcData->unk1D8 = gcData->unk200 + (gcData->unk1F8 * gcData->unk20C);
    gcData->unk1DC = (gcData->unk1FC * gcData->unk214) + (temp_fa1 * gcData->unk218);
}

void func_80304B98(GyrocopterData* gcData) {
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

    if (gcData->unk8C < 4.0f) {
        if (gcData->unk510 > 0) {
            for (i = 0; i < gcData->unk510; i++) {
                sp184 = gcData->unk514[i];
                if (i == 0) {
                    uvVec3Copy(&sp110, &gcData->unk3B0[sp184].unk10);
                } else {
                    uvVec3Add(&sp110, &sp110, &gcData->unk3B0[sp184].unk10);
                }
            }
            uvVec3Mul(&sp110, &sp110, 1.0f / gcData->unk510);
            uvVec3Normal(&sp110, &sp110);
        } else {
            sp110.x = 0.0f;
            sp110.y = 0.0f;
            sp110.z = 1.0f;
            uvMat4LocalToWorld(&gcData->unk110, &sp110, &sp110);
        }
        if (gcData->unk8C > 2.0f) {
            uvVec3Mul(&sp11C, &sp110, (uvVec3Dot(&sp110, &gcData->unk334) * (gcData->unk8C - 4.0f)) / 2);
        } else {
            uvVec3Mul(&sp11C, &sp110, -uvVec3Dot(&sp110, &gcData->unk334));
        }

        uvVec3Add(&gcData->unk31C, &gcData->unk31C, &sp11C);
        gcData->unk8C += D_8034F854;
    }
    gcData->unk524 = 0;

    for (i = 0; i < gcData->unk510; i++) {
        sp184 = gcData->unk514[i];
        uvVec3Cross(&sp11C, &gcData->unk1C8, &gcData->unk5EC[sp184]);
        uvVec3Cross(&sp11C, &gcData->unk1C8, &sp11C);
        sp170[gcData->unk524] = -uvVec3Dot(&sp11C, &gcData->unk3B0[sp184].unk10);
        sp170[gcData->unk524] -= uvVec3Dot(&gcData->unk31C, &gcData->unk3B0[sp184].unk10);
        if ((gcData->unk3B0[sp184].unk54 < 0.01f) && ((gcData->unk8C <= 2.0f) || ((gcData->unk8C > 2.0f) && (sp170[gcData->unk524] > 0.0f)))) {
            gcData->unk528[gcData->unk524++] = sp184;
        }
    }

    if (gcData->unk524 == 0) {
        return;
    }

    if (gcData->unk524 < 3) {
        for (i = 0; i < gcData->unk524; i++) {
            sp184 = gcData->unk528[i];
            for (j = 0; j < i; j++) {
                temp_s2 = gcData->unk528[j];
                uvVec3Cross(&sp11C, &gcData->unk3B0[temp_s2].unk28, &gcData->unk5EC[sp184]);
                sp94.m[j][i] = sp94.m[i][j] =
                    (uvVec3Dot(&gcData->unk3B0[sp184].unk10, &gcData->unk3B0[temp_s2].unk10) / 250.0f) + uvVec3Dot(&gcData->unk3B0[sp184].unk10, &sp11C);
            }

            uvVec3Cross(&sp11C, &gcData->unk3B0[sp184].unk28, &gcData->unk5EC[sp184]);
            sp94.m[i][i] = uvVec3Dot(&gcData->unk3B0[sp184].unk10, &sp11C) + 0.004f;
        }
        for (i = 0; i < gcData->unk524; i++) {
            sp184 = gcData->unk528[i];
            for (j = 0; j < gcData->unk524; j++) {
                temp_s2 = gcData->unk528[j];
                if (i == j) {
                    uvVec3Cross(&sp11C, &gcData->unk3B0[sp184].unk34, &gcData->unk5EC[sp184]);
                    sp94.m[i][j] += -uvVec3Dot(&gcData->unk3B0[sp184].unk10, &sp11C) * gcData->unk3B0[temp_s2].unk40;
                } else {
                    uvVec3Cross(&sp11C, &gcData->unk3B0[temp_s2].unk34, &gcData->unk5EC[sp184]);
                    sp94.m[i][j] += -((uvVec3Dot(&gcData->unk3B0[sp184].unk10, &gcData->unk3B0[temp_s2].unk1C) / 250.0f) +
                                      uvVec3Dot(&gcData->unk3B0[sp184].unk10, &sp11C)) *
                                    gcData->unk3B0[temp_s2].unk40;
                }
            }
        }
    }
    if (gcData->unk524 < 3) {
        if (gcData->unk524 == 1) {
            sp170[0] /= sp94.m[0][0];
        } else {
            temp_fv0_2 = (sp94.m[0][0] * sp94.m[1][1]) - (sp94.m[0][1] * sp94.m[1][0]);
            temp_fv1_2 = ((sp170[0] * sp94.m[1][1]) - (sp170[1] * sp94.m[0][1])) / temp_fv0_2;
            sp170[1] = ((sp170[1] * sp94.m[0][0]) - (sp170[0] * sp94.m[1][0])) / temp_fv0_2;
            sp170[0] = temp_fv1_2;
        }

        for (i = 0; i < gcData->unk524; i++) {
            sp184 = gcData->unk528[i];
            uvVec3Mul(&sp11C, &gcData->unk3B0[sp184].unk1C, -gcData->unk3B0[sp184].unk40);
            uvVec3Add(&sp11C, &gcData->unk3B0[sp184].unk10, &sp11C);
            uvVec3Mul(&sp11C, &sp11C, sp170[i] / 250.0f);
            uvVec3Add(&gcData->unk31C, &gcData->unk31C, &sp11C);
            uvVec3Mul(&sp11C, &gcData->unk3B0[sp184].unk34, -gcData->unk3B0[sp184].unk40);
            uvVec3Add(&sp11C, &gcData->unk3B0[sp184].unk28, &sp11C);
            uvVec3Mul(&sp11C, &sp11C, sp170[i]);
            uvVec3Add(&gcData->unk328, &gcData->unk328, &sp11C);
        }
    } else {
        for (i = 0; i < gcData->unk524; i++) {
            sp184 = gcData->unk528[i];
            if (i == 0) {
                sp164 = gcData->unk3B0[sp184].unk40;
                uvVec3Copy(&sp110, &gcData->unk3B0[sp184].unk10);
            } else {
                sp164 += gcData->unk3B0[sp184].unk40;
                uvVec3Add(&sp110, &sp110, &gcData->unk3B0[sp184].unk10);
            }
        }
        if (uvVec3Dot(&gcData->unk31C, &sp110) < 0.0f) {
            uvVec3Mul(&sp110, &sp110, 1.0f / gcData->unk524);
            uvVec3Normal(&sp110, &sp110);
            uvVec3Cross(&sp104, &sp110, &gcData->unk190);
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
            var_fv1 = (1.0f - gcData->unkB4) * temp_fv0_4 * 0.3f;
            if (gcData->unk6C != 0) {
                var_fv1 *= 0.8f;
            }
            if (temp_fv0_4 < 2.0f) {
                var_fv1 *= 1.0f + (4.0f * (2.0f - temp_fv0_4));
            }
            uvVec3Mul(&spD4, &spF8, -var_fv1);

            for (i = 0; i < 3; i++) {
                sp184 = gcData->unk528[i];
                if ((sp184 == 0) || (sp184 == 3)) {
                    if (gcData->unk6C == 0) {
                        sp150 = (gcData->unkAC + gcData->unk9C) * -0.2617994f;
                    } else {
                        if (((gcData->unk190.y * 0.7f) > 40.0f) && ((gcData->unk190.y * 0.7f) <= 45.0f)) {
                            sp150 = ((gcData->unkAC + gcData->unk9C) * -0.0872665f * ((gcData->unk190.y * 0.7f) - 40.0f)) / 5.0f;
                        } else if (((gcData->unk190.y * 0.7f) > 45.0f) && ((gcData->unk190.y * 0.7f) < 50.0f)) {
                            sp150 = ((gcData->unkAC + gcData->unk9C) * -0.0872665f * (50.0f - (gcData->unk190.y * 0.7f))) / 5.0f;
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

                temp_fs1 = gcData->unk3B0[sp184].unk50 * uvVec3Dot(&gcData->unk3B0[sp184].unk1C, &spF8);
                temp_fa0_2 = gcData->unk3B0[sp184].unk50 * uvVec3Dot(&gcData->unk3B0[sp184].unk1C, &spEC);
                if (gcData->unk528[0] == 0) {
                    temp_fv1 = gcData->unk3B0[sp184].unk48 * temp_fs1 * 0.35f;
                    temp_fs0 = gcData->unk3B0[sp184].unk48 * 0.5f * temp_fa0_2 * 2.4f;
                } else {
                    temp_fv1 = gcData->unk3B0[sp184].unk4C * temp_fs1 * 0.35f;
                    temp_fs0 = gcData->unk3B0[sp184].unk4C * 0.5f * temp_fa0_2 * 2.4f;
                }
                if ((gcData->unk6C == 0) && (gcData->unk50 != -1)) {
                    temp_fv1 *= 1.1f;
                    temp_fs0 *= 1.1f;
                }
                uvVec3Mul(&spF8, &spF8, -temp_fv1);
                uvVec3Add(&spD4, &spD4, &spF8);
                uvVec3Mul(&spEC, &spEC, -temp_fs0);
                uvVec3Add(&spD4, &spD4, &spEC);
                spE0.x = gcData->unk5EC[sp184].x - gcData->unk538.x;
                if (gcData->unk528[0] == 0) {
                    spE0.y = gcData->unk5EC[sp184].y - gcData->unk538.y;
                } else {
                    spE0.y = gcData->unk5EC[sp184].y + gcData->unk538.y;
                }
                spE0.z = gcData->unk5EC[sp184].z - gcData->unk538.z;
                uvVec3Cross(&spE0, &sp110, &spE0);
                uvVec3Cross(&spE0, &spE0, &sp110);
                uvVec3Cross(&spF8, &spE0, &spF8);
                uvVec3Add(&gcData->unk328, &gcData->unk328, &spF8);
                uvVec3Cross(&spEC, &spE0, &spEC);
                uvVec3Add(&gcData->unk328, &gcData->unk328, &spEC);
            }
            uvVec3Cross(&gcData->unk31C, &sp110, &gcData->unk31C);
            uvVec3Cross(&gcData->unk31C, &gcData->unk31C, &sp110);
            uvVec3Add(&gcData->unk31C, &gcData->unk31C, &spD4);
            uvVec3Mul(&gcData->unk328, &sp110, uvVec3Dot(&gcData->unk328, &sp110));
        }
    }
}

void func_80305BE8(GyrocopterData* gcData) {
    f32 var_fs0;

    if (gcData->unkE0 == 0.0f) {
        if (uvVec3Len(&gcData->unk1C8) < 0.78539807f) {
            var_fs0 = (demoRandF() + 1.0f) * 21.8f;
            if (demoRandF() < 0.5f) {
                var_fs0 = -var_fs0;
            }
            gcData->unk1E0 = var_fs0 * 0.4f;
            var_fs0 = (demoRandF() + 1.0f) * 21.8f;
            if (demoRandF() < 0.5f) {
                var_fs0 = -var_fs0;
            }
            gcData->unk1E4 = var_fs0 * 0.4f;
            var_fs0 = (demoRandF() + 1.0f) * 10.9f;
            if (demoRandF() < 0.5f) {
                var_fs0 = -var_fs0;
            }
            gcData->unk1E8 = var_fs0 * 0.8f;
        }
        gcData->unkE0 = D_8034F850;
    }
    gcData->unk1C8.x = func_80313AF4(0.0f, gcData->unk1C8.x, 0.2f);
    gcData->unk1C8.y = func_80313AF4(0.0f, gcData->unk1C8.y, 0.2f);
    gcData->unk1C8.z = func_80313AF4(0.0f, gcData->unk1C8.z, 0.2f);
    if ((D_8034F850 - gcData->unkE0) > 3.75f) {
        gcData->unkC0 = 3;
    }
}

s32 func_80305DC0(GyrocopterData* gcData) {
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
    gcData->unk6C = 0;
    var_s6 = 0;
    var_fs1 = 0.0f;

    padsLandedPadStrip(gcData->unk10.m[3][0], gcData->unk10.m[3][1], gcData->unk10.m[3][2], &gcData->unk6C);

    for (i = 0; i < 4; i++) {
        uvMat4LocalToWorld(&gcData->unk10, &sp27C[i], &gcData->unk5EC[i]);
        sp2D0.x = gcData->unk5EC[i].x;
        sp2D0.y = gcData->unk5EC[i].y;
        sp2D0.z = 0.0f;
        uvMat4LocalToWorld(&gcData->unk10, &sp24C[i], &sp2D0);
    }

    gcData->unkDC = 1000000.0f;
    gcData->unk10C = 0xFF;
    sp1C0 = gcData->unk510;
    gcData->unk510 = 0;
    sp2B4 = 0;

    for (i = 0; i < 4; i++) {
        sp238 = gcData->unk3B0[i].unkC;
        temp_s0 = db_getgnd(&gcData->unk3B0[i].unk0, &sp24C[i], &sp238, &sp2C0, &sp2F8, &sp2E8);
        if (temp_s0 == 4) {
            if (gcData->unkC0 == 2) {
                smokeProps((s32)gcData->unk96, SMOKE_PROP_8(0), SMOKE_PROP_END);
            }
            gcData->unkC0 = 3;
            gcData->unkD0 = 1;
            gcData->unk544 = 1;
            gcData->unk547[0] = 1;
            uvVec3Copy(&gcData->unk54C[0], &sp27C[i]);
            gcData->unk3B0[i].unkC = sp238;
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
        if ((var_fs0 <= 0.0f) || ((i == gcData->unk528[sp2B4]) && (sp2B4 < gcData->unk524))) {
            if (i == gcData->unk528[sp2B4]) {
                sp2B4++;
            }
            sp2FF++;
            uvVec3Copy(&gcData->unk3B0[i].unk10, &sp2E8);
            gcData->unk514[gcData->unk510] = i;
            if (temp_s0) {
                sp218[gcData->unk510] = temp_s0;
            } else {
                sp218[gcData->unk510] = func_802E02F8();
            }
            gcData->unk510++;
        }
        gcData->unk3B0[i].unk54 = var_fs0;
        gcData->unk3B0[i].unkC = sp238;
        if (var_fs0 < gcData->unkDC) {
            gcData->unkDC = var_fs0;
            gcData->unkF8 = sp2C0;
            gcData->unkFC = sp2F8;
            gcData->unk100.x = sp2E8.x;
            gcData->unk100.y = sp2E8.y;
            gcData->unk100.z = sp2E8.z;
            gcData->unk10C = i;
            sp249 = temp_s0;
        }
    }

    if ((sp2FF != 0) && (sp249 != 2) && (sp249 != 8)) {
        if ((gcData->unkF8 == -1) || ((gcData->unkF8 != -1) && (func_802DC8E4(gcData->unkF8) != 0))) {
            if (gcData->unkC0 == 2) {
                smokeProps(gcData->unk96, SMOKE_PROP_8(0), SMOKE_PROP_END);
            }
            gcData->unkC0 = 3;
            gcData->unkD0 = 1;
            gcData->unk544 = 1;
            gcData->unk547[0] = 1;
            uvVec3Copy(&gcData->unk54C[0], &sp27C[gcData->unk10C]);
            return 1;
        }
    }

    if (var_fs1 > 0.0f) {
        gcData->unk10.m[3][0] += sp204.x;
        gcData->unk10.m[3][1] += sp204.y;
        gcData->unk10.m[3][2] += sp204.z;
        gcData->unk668.x = gcData->unk10.m[3][0];
        gcData->unk668.y = gcData->unk10.m[3][1];
        gcData->unk668.z = gcData->unk10.m[3][2];
        for (i = 0; i < 4; i++) {
            gcData->unk3B0[i].unk54 += sp204.z;
            uvMat4LocalToWorld(&gcData->unk10, &sp27C[i], &gcData->unk5EC[i]);
            sp2D0.x = gcData->unk5EC[i].x;
            sp2D0.y = gcData->unk5EC[i].y;
            sp2D0.z = 0.0f;
            uvMat4LocalToWorld(&gcData->unk10, &sp24C[i], &sp2D0);
        }
    }
    if (sp2FF) {
        if (gcData->unk510 > 3) {
            var_v1 = 0;
            var_fv1 = gcData->unk3B0[0].unk54;
            for (i = 1; i < gcData->unk510; i++) {
                if (var_fv1 < gcData->unk3B0[i].unk54) {
                    var_fv1 = gcData->unk3B0[i].unk54;
                    var_v1 = i;
                }
            }

            gcData->unk510 = 3;
            for (i = var_v1; i < 3; i++) {
                gcData->unk514[i] = gcData->unk514[i + 1];
            }
        }
        sp1F4.x = 0.0f;
        sp1F4.y = 0.0f;
        sp1F4.z = 1.0f;

        if (gcData->unk510 == 1) {
            sp2B4 = gcData->unk514[0];
            sp164 = gcData->unk3B0[sp2B4].unk54;
        }

        if (gcData->unk510 > 1) {
            for (i = 0; i < gcData->unk510; i++) {
                sp2B4 = gcData->unk514[i];
                if (i == 0) {
                    uvVec3Copy(&sp2E8, &gcData->unk3B0[sp2B4].unk10);
                    uvVec3Copy(&sp1C8, &gcData->unk5EC[sp2B4]);
                    sp164 = gcData->unk3B0[sp2B4].unk54;
                } else {
                    uvVec3Add(&sp2E8, &sp2E8, &gcData->unk3B0[sp2B4].unk10);
                    uvVec3Add(&sp1C8, &sp1C8, &gcData->unk5EC[sp2B4]);
                    sp164 += gcData->unk3B0[sp2B4].unk54;
                }
            }
            var_fs1 = 1.0f / gcData->unk510;
            uvVec3Mul(&sp2E8, &sp2E8, var_fs1);
            uvVec3Normal(&sp2E8, &sp2E8);
            uvMat4LocalToWorld(&gcData->unk150, &sp2E8, &sp2E8);
            uvVec3Mul(&sp1C8, &sp1C8, var_fs1);
            sp164 *= var_fs1;
        }
        if ((sp164 < -0.1f) && ((sp1C0 < gcData->unk510) || ((gcData->unk510 == sp1C0) && (gcData->unk510 == gcData->unk524)))) {
            uvVec3Mul(&sp1F4, &sp1F4, -sp164);
            gcData->unk10.m[3][0] += sp1F4.x;
            gcData->unk10.m[3][1] += sp1F4.y;
            gcData->unk10.m[3][2] += sp1F4.z;
            gcData->unk668.x = gcData->unk10.m[3][0];
            gcData->unk668.y = gcData->unk10.m[3][1];
            gcData->unk668.z = gcData->unk10.m[3][2];
            switch (gcData->unk510) {
            case 1:
                for (i = 0; i < 4; i++) {
                    uvVec3Add(&gcData->unk3B0[i].unk0, &sp24C[i], &sp1F4);
                }
                break;
            case 2:
                sp2B4 = gcData->unk514[0];
                temp_s2 = gcData->unk514[1];
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
                sp2B4 = gcData->unk514[0];
                temp_s2 = gcData->unk514[1];
                sp2D0.x = sp27C[sp2B4].x - sp27C[temp_s2].x;
                sp2D0.y = sp27C[sp2B4].y - sp27C[temp_s2].y;
                sp2D0.z = sp27C[sp2B4].z - sp27C[temp_s2].z;
                temp_s2 = gcData->unk514[2];
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
                    uvVec3Copy(&gcData->unk3B0[i].unk0, &sp24C[i]);
                }
                break;
            }

            if ((gcData->unk510 >= 2) && (sp17C < 0.999f)) {
                sp1D4[3] = uvSqrtF((1.0f + sp17C) * 0.5f);
                sp1D4[0] = sp1D4[1] = sp1D4[2] = uvSqrtF((1.0f - sp17C) * 0.5f);
                uvMat4LocalToWorld(&gcData->unk110, &sp1E4, &sp1E4);
                sp1D4[0] *= sp1E4.x;
                sp1D4[1] *= sp1E4.y;
                sp1D4[2] *= sp1E4.z;
                uvMat4SetQuaternionRotation(&sp180, sp1D4[0], sp1D4[1], sp1D4[2], sp1D4[3]);
                sp180.m[3][0] = sp180.m[3][0] = sp180.m[3][1] = sp180.m[3][2] = 0.0f;
                sp180.m[0][3] = sp180.m[0][3] = sp180.m[1][3] = sp180.m[2][3] = 0.0f;
                sp180.m[3][3] = 1.0f;
                sp2C4.x = gcData->unk10.m[3][0];
                sp2C4.y = gcData->unk10.m[3][1];
                sp2C4.z = gcData->unk10.m[3][2];
                uvMat4LocalToWorld(&gcData->unk110, &gcData->unk1B8, &gcData->unk1B8);
                uvMat4LocalToWorld(&gcData->unk150, &sp2D0, &sp1C8);
                uvVec3Add(&sp2C4, &sp2D0, &sp2C4);
                uvMat4MulBA(&gcData->unk10, &gcData->unk150, &sp180);
                uvMat4Copy(&gcData->unk150, &gcData->unk10);
                uvMat4InvertTranslationRotation(&gcData->unk110, &gcData->unk150);
                uvMat4LocalToWorld(&gcData->unk150, &sp2D0, &sp1C8);
                sp2C4.x -= sp2D0.x;
                sp2C4.y -= sp2D0.y;
                sp2C4.z -= sp2D0.z;
                gcData->unk10.m[3][0] = sp2C4.x;
                gcData->unk10.m[3][1] = sp2C4.y;
                gcData->unk10.m[3][2] = sp2C4.z;
                uvVec3Copy(&gcData->unk668, &sp2C4);
                for (i = 0; i < 4; i++) {
                    sp2D0.x = gcData->unk5EC[i].x;
                    sp2D0.y = gcData->unk5EC[i].y;
                    sp2D0.z = 0.0f;
                    uvMat4LocalToWorld(&gcData->unk10, &gcData->unk3B0[i].unk0, &sp2D0);
                    gcData->unk3B0[i].unk54 += gcData->unk3B0[i].unk0.z - sp24C[i].z;
                }
                uvMat4LocalToWorld(&gcData->unk150, &gcData->unk1B8, &gcData->unk1B8);
                uvMat4LocalToWorld(&gcData->unk150, &gcData->unk19C, &gcData->unk190);
            }
        } else {
            for (i = 0; i < 4; i++) {
                uvVec3Copy(&gcData->unk3B0[i].unk0, &sp24C[i]);
            }
        }
        var_s5_4 = 0;
        for (i = 0; i < gcData->unk510; i++) {
            sp2B4 = gcData->unk514[i];
            uvMat4LocalToWorld(&gcData->unk110, &gcData->unk3B0[sp2B4].unk10, &gcData->unk3B0[sp2B4].unk10);
            uvVec3Cross(&sp2D0, &gcData->unk1C8, &gcData->unk5EC[sp2B4]);
            sp2D0.x += gcData->unk190.x;
            sp2D0.y += gcData->unk190.y;
            sp2D0.z += gcData->unk190.z;
            temp_fv1_4 = -uvVec3Dot(&sp2D0, &gcData->unk3B0[sp2B4].unk10);
            if (sp23C < temp_fv1_4) {
                sp23C = temp_fv1_4;
            }
            uvVec3Cross(&sp2D0, &gcData->unk3B0[sp2B4].unk10, &sp2D0);
            uvVec3Cross(&gcData->unk3B0[sp2B4].unk1C, &sp2D0, &gcData->unk3B0[sp2B4].unk10);
            gcData->unk3B0[sp2B4].unk50 = uvVec3Len(&gcData->unk3B0[sp2B4].unk1C);
            uvVec3Normal(&gcData->unk3B0[sp2B4].unk1C, &gcData->unk3B0[sp2B4].unk1C);
            uvVec3Cross(&gcData->unk3B0[sp2B4].unk28, &gcData->unk5EC[sp2B4], &gcData->unk3B0[sp2B4].unk10);
            gcData->unk3B0[sp2B4].unk28.x /= 100.0f;
            gcData->unk3B0[sp2B4].unk28.y /= 100.0f;
            gcData->unk3B0[sp2B4].unk28.z /= 100.0f;
            uvVec3Cross(&gcData->unk3B0[sp2B4].unk34, &gcData->unk5EC[sp2B4], &gcData->unk3B0[sp2B4].unk1C);
            gcData->unk3B0[sp2B4].unk34.x /= 100.0f;
            gcData->unk3B0[sp2B4].unk34.y /= 100.0f;
            gcData->unk3B0[sp2B4].unk34.z /= 100.0f;
            if ((sp244 < 2) && (temp_fv1_4 > 0.0f)) {
                sp110[sp244] = (f32)((gcData->unk3B0[sp2B4].unk44 + 1.0f) * temp_fv1_4);
            }
            if (temp_fv1_4 > 0.0f) {
                sp228[sp244++] = sp2B4;
            }
            if ((sp2B4 != gcData->unk528[var_s5_4]) || (var_s5_4 >= gcData->unk524)) {
                if (gcData->unk564[gcData->unk544] < temp_fv1_4) {
                    uvVec3Copy(&gcData->unk54C[gcData->unk544], &sp27C[sp2B4]);
                    gcData->unk545[gcData->unk544] = sp218[sp2B4];
                    gcData->unk564[gcData->unk544] = temp_fv1_4;
                }
            }
            if (sp2B4 == gcData->unk528[var_s5_4]) {
                var_s5_4++;
            }
        }
        if (gcData->unk564[gcData->unk544] > 0.0f) {
            gcData->unk547[gcData->unk544] = 1;
            gcData->unk544++;
        }
        if (gcData->unkC0 == 0) {
            if (sp23C >= 12.698f) {
                gcData->unkC1 = 1;
            } else if (sp23C >= 7.937f) {
                if ((gcData->unk50 == 0) && (gcData->unk6C == 0)) {
                    gcData->unkC1 = 1;
                }
            } else if (sp23C > 1.0f) {
                gcData->unk8C = D_8034F854;
            }
            if ((gcData->unk94 == 0xFF) && (gcData->unk50 >= 0) && (gcData->unk6C == 0) && (gcData->unk1A8 > 5.952f) && (func_802DC930(gcData->unkF8) != 0)) {
                gcData->unk94 = smokeCreate();
                // clang-format off
                smokeProps(
                    gcData->unk94,
                    SMOKE_PROP_1(160, 120, 70),
                    SMOKE_PROP_2(4.0f),
                    SMOKE_PROP_3(3.0f),
                    SMOKE_PROP_4(1.0f),
                    SMOKE_PROP_5(-gcData->unk10.m[1][0], -gcData->unk10.m[1][1], 0.5f),
                    SMOKE_PROP_6((sp27C[1].x + sp27C[2].x) * 0.5f, (sp27C[1].y + sp27C[2].y) * 0.5f, sp27C[1].z),
                    SMOKE_PROP_7(1),
                    SMOKE_PROP_END
                );
                // clang-format on
            }
            if ((gcData->unk50 == 0) && (sp23C < 12.698f)) {
                func_8032BE10()->landedDist = padsLandedPadStrip(gcData->unk10.m[3][0], gcData->unk10.m[3][1], gcData->unk10.m[3][2], &gcData->unk6C);
                gcData->unk50 = 1;
                gcData->unk54 = sp23C;
                if (gcData->unk6C != 0) {
                    gcData->unk4 = 0xFFFF;
                }
            }
        }
        if (sp244 != 0) {
            if (sp244 < 3) {
                for (i = 0; i < sp244; i++) {
                    sp2B4 = sp228[i];
                    for (j = 0; j < i; j++) {
                        temp_s2 = sp228[j];
                        uvVec3Cross(&sp2D0, &gcData->unk3B0[temp_s2].unk28, &gcData->unk5EC[sp2B4]);
                        sp120.m[j][i] = sp120.m[i][j] = (uvVec3Dot(&gcData->unk3B0[sp2B4].unk10, &gcData->unk3B0[temp_s2].unk10) / 250.0f) +
                                                        uvVec3Dot(&gcData->unk3B0[sp2B4].unk10, &sp2D0);
                    }
                    uvVec3Cross(&sp2D0, &gcData->unk3B0[sp2B4].unk28, &gcData->unk5EC[sp2B4]);
                    sp120.m[i][i] = uvVec3Dot(&gcData->unk3B0[sp2B4].unk10, &sp2D0) + 0.004f;
                }
                for (i = 0; i < sp244; i++) {
                    sp2B4 = sp228[i];
                    for (j = 0; j < sp244; j++) {
                        temp_s2 = sp228[j];
                        if (i == j) {
                            uvVec3Cross(&sp2D0, &gcData->unk3B0[sp2B4].unk34, &gcData->unk5EC[sp2B4]);
                            sp120.m[i][j] += -uvVec3Dot(&gcData->unk3B0[sp2B4].unk10, &sp2D0) * gcData->unk3B0[temp_s2].unk40;
                        } else {
                            uvVec3Cross(&sp2D0, &gcData->unk3B0[temp_s2].unk34, &gcData->unk5EC[sp2B4]);
                            sp120.m[i][j] += -((uvVec3Dot(&gcData->unk3B0[sp2B4].unk10, &gcData->unk3B0[temp_s2].unk1C) / 250.0f) +
                                               uvVec3Dot(&gcData->unk3B0[sp2B4].unk10, &sp2D0)) *
                                             gcData->unk3B0[temp_s2].unk40;
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
                    uvVec3Mul(&sp2D0, &gcData->unk3B0[sp2B4].unk1C, -gcData->unk3B0[sp2B4].unk40);
                    uvVec3Add(&sp2D0, &gcData->unk3B0[sp2B4].unk10, &sp2D0);
                    uvVec3Mul(&sp2D0, &sp2D0, sp110[i] / 250.0f);
                    uvVec3Add(&gcData->unk190, &gcData->unk190, &sp2D0);
                    uvVec3Mul(&sp2D0, &gcData->unk3B0[sp2B4].unk34, -gcData->unk3B0[sp2B4].unk40);
                    uvVec3Add(&sp2D0, &gcData->unk3B0[sp2B4].unk28, &sp2D0);
                    uvVec3Mul(&sp2D0, &sp2D0, sp110[i]);
                    uvVec3Add(&gcData->unk1C8, &gcData->unk1C8, &sp2D0);
                }
            } else {
                for (i = 0; i < sp244; i++) {
                    sp2B4 = sp228[i];
                    if (i == 0) {
                        sp16C = gcData->unk3B0[sp2B4].unk44;
                        sp168 = gcData->unk3B0[sp2B4].unk40;
                        uvVec3Copy(&sp2E8, &gcData->unk3B0[sp2B4].unk10);
                    } else {
                        sp16C += gcData->unk3B0[sp2B4].unk44;
                        sp168 += gcData->unk3B0[sp2B4].unk40;
                        uvVec3Add(&sp2E8, &sp2E8, &gcData->unk3B0[sp2B4].unk10);
                    }
                }
                sp168 /= sp244;
                sp16C /= sp244;
                uvVec3Mul(&sp2E8, &sp2E8, 1.0f / sp244);
                uvVec3Normal(&sp2E8, &sp2E8);
                uvVec3Cross(&sp2C4, &sp2E8, &gcData->unk190);
                uvVec3Cross(&sp2C4, &sp2C4, &sp2E8);
                uvVec3Normal(&sp2C4, &sp2C4);
                var_fs0 = uvVec3Dot(&gcData->unk190, &sp2E8);
                sp110[0] = (-(1.0f + sp16C) * var_fs0) / (1.0f - (uvVec3Dot(&sp2C4, &sp2E8) * sp168));
                uvVec3Mul(&sp2D0, &sp2C4, -sp168);
                uvVec3Add(&sp2D0, &sp2E8, &sp2D0);
                uvVec3Mul(&sp2D0, &sp2D0, sp110[0]);
                uvVec3Add(&gcData->unk190, &gcData->unk190, &sp2D0);
                uvVec3Mul(&gcData->unk1C8, &sp2E8, uvVec3Dot(&gcData->unk1C8, &sp2E8));
            }
        }
    } else {
        for (i = 0; i < 4; i++) {
            uvVec3Copy(&gcData->unk3B0[i].unk0, &sp24C[i]);
        }
        if (gcData->unkDC > 3.0f) {
            gcData->unk50 = 0;
        }
    }
    if ((gcData->unkC0 == 1) && (gcData->unk6C != 0) && ((gcData->unk190.y * 0.7f <= 40.0f) || (gcData->unk190.y * 0.7f >= 50.0f) || (gcData->unk9C == 0.0f))) {
        gcData->unk1C8.x = func_80313AF4(0.0f, gcData->unk1C8.x, 6.0f);
        gcData->unk1C8.y = func_80313AF4(0.0f, gcData->unk1C8.y, 6.0f);
        gcData->unk1C8.z = func_80313AF4(0.0f, gcData->unk1C8.z, 6.0f);
    }
    if (gcData->unkD0 != 0) {
        return 1;
    }

    if ((gcData->unkC0 == 1) && (gcData->unk524 == 0) && (gcData->unk8C >= 4.0f)) {
        gcData->unkC0 = 0;
        return 0;
    }

    if ((gcData->unkC0 != 1) && (gcData->unkC0 != 2) && (gcData->unkC0 != 3) && (gcData->unk510 > 0)) {
        gcData->unkC0 = 1;
        return 1;
    }
    if (gcData->unk510 > 0) {
        return 1;
    }
    return 0;
}

void func_80307A9C(GyrocopterData* gcData) {
    Vec3F sp24;

    sp24.x = func_80313F08(&D_80369528, SQ(gcData->unk364.x));
    if (gcData->unk364.x < 0.0f) {
        sp24.x = -sp24.x;
    }

    sp24.y = func_80313F08(&D_80369528, SQ(gcData->unk364.y));
    if (gcData->unk364.y < 0.0f) {
        sp24.y = -sp24.y;
    }

    sp24.z = func_80313F08(&D_80369528, SQ(gcData->unk364.z));
    if (gcData->unk364.z < 0.0f) {
        sp24.z = -sp24.z;
    }
    gcData->unk31C.x += sp24.x;
    gcData->unk31C.y += sp24.y;
    gcData->unk31C.z += sp24.z;
}

void func_80307BAC(GyrocopterData* gcData) {
    f32 sp54;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 sp48;
    s32 pad;
    f32 var_fv1;
    Vec3F sp34;
    f32 var_ft4;
    f32 var_fv1_2;

    sp48 = uvSinF(gcData->unkEC);
    temp_fv0 = uvCosF(gcData->unkEC);
    temp_fv1 = gcData->unk594 * 0.5f;
    D_80369070.unk4[1].unk0 = 1;
    D_80369070.unk4[1].unk1C.x = gcData->unk59C.x - sp48 * temp_fv1;
    D_80369070.unk4[1].unk1C.y = gcData->unk59C.y + temp_fv0 * temp_fv1;
    D_80369070.unk4[1].unk1C.z = gcData->unk59C.z;
    D_80369070.unk4[1].unk28.x = gcData->unk59C.x + sp48 * temp_fv1;
    D_80369070.unk4[1].unk28.y = gcData->unk59C.y - temp_fv0 * temp_fv1;
    D_80369070.unk4[1].unk28.z = gcData->unk59C.z;
    if ((gcData->unkC1 != 0) || (gcData->unkC0 == 2)) {
        gcData->unkE8 = func_80313AF4(0.0f, gcData->unkE8, 0.5f);
        return;
    }
    uvMat4LocalToWorld(&gcData->unk25C, &sp34, &gcData->unk364);
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

    var_fv1 = SQ(gcData->unk364.y) / 25.0f;
    if (var_fv1 < 0.05f) {
        var_fv1 = 0.05f;
    } else if (var_fv1 > 1.0f) {
        var_fv1 = 1.0f;
    }
    sp34.x = 0.0f;
    sp34.y = 0.0f;
    sp34.z = sp54 * var_fv1;
    uvMat4LocalToWorld(&gcData->unk21C, &sp34, &sp34);
    gcData->unk31C.x += sp34.x;
    gcData->unk31C.y += sp34.y;
    gcData->unk31C.z += sp34.z;
    gcData->unk334.x += sp34.x;
    gcData->unk334.y += sp34.y;
    gcData->unk334.z += sp34.z;

    var_ft4 = ABS_NOEQ(sp54);
    var_fv1_2 = ABS_NOEQ(gcData->unk364.y);

    gcData->unkE8 = func_80313AF4((var_fv1_2 + var_ft4) * 3.0f, gcData->unkE8, 0.5f);
}

void func_80307E2C(GyrocopterData* gcData) {
    Vec3F sp1C;

    sp1C.x = 0.0f;
    sp1C.y = 0.0f;
    sp1C.z = -9.8f;
    uvMat4LocalToWorld(&gcData->unk110, &gcData->unk358, &sp1C);
    gcData->unk31C.x += gcData->unk358.x;
    gcData->unk31C.y += gcData->unk358.y;
    gcData->unk31C.z += gcData->unk358.z;
}

void func_80307EA8(GyrocopterData* gcData) {
    Vec3F spDC;
    f32 spD8;
    f32 temp_fv0;
    Vec3F spC8;

    if ((gcData->unkC1 != 0) || (gcData->unkC0 == 2)) {
        gcData->unkF0 = func_80313AF4(0.0f, gcData->unkF0, 0.5f);
        return;
    }
    if (D_8036957E == CLASS_B) {
        if (func_802E08F4(gcData->unk10.m[3][0], gcData->unk10.m[3][1], gcData->unk10.m[3][2]) != 0) {
            if (gcData->unk67E == 0) {
                gcData->unk67E = 1;
                sndPlaySfx(0x6D);
            }
            hudWarningText(-1, 0.0f, 0.0f);
            gcData->hasLowFuel = FALSE;
            gcData->fuelEmpty = FALSE;
            gcData->fuel = 1.0f;
        } else {
            gcData->unk67E = 0;
        }
    }
    if ((gcData->fuel > 0.0f) && gcData->usingFuel) {
        gcData->fuel -= func_80313F08(&D_803694D0, gcData->unkB4) * D_8034F854;
        if (gcData->fuel <= 0.0f) {
            gcData->usingFuel = FALSE;
        }
        if (gcData->fuel < 0.0f) {
            gcData->fuel = 0.0f;
        } else if (gcData->fuel > 1.0f) {
            gcData->fuel = 1.0f;
        }
    }

    if (gcData->unk10.m[3][2] > 700.0f) {
        spD8 = 1.0f - ((gcData->unk10.m[3][2] - 700.0f) / 100.0f);
        if (spD8 < 0.0f) {
            spD8 = 0.0f;
        }
    } else {
        spD8 = 1.0f;
    }
    if (gcData->usingFuel) {
        temp_fv0 = func_80313F08(&D_803692C0, -gcData->unk364.y);
        spDC.x = 0.0f;
        spDC.y = gcData->unkB4 * 0.24f * spD8 * 35.0f;
        spDC.z = gcData->unkB4 * 0.76f * spD8 * temp_fv0 * 35.0f;
        uvMat4LocalToWorld(&gcData->unk21C, &spDC, &spDC);
        if ((gcData->unk1F0 < 0.0f) && (gcData->unk190.y > 0.0f) && (gcData->unk7C == 0)) {
            spDC.y *= 0.9f;
        } else if ((gcData->unk1F0 > 0.0f) && (gcData->unk190.y > 0.0f) && (gcData->unk7C == 0)) {
            spDC.y *= 0.9f;
        }
        gcData->unk31C.x += spDC.x;
        gcData->unk31C.y += spDC.y;
        gcData->unk31C.z += spDC.z;
        gcData->unk334.x += spDC.x;
        gcData->unk334.y += spDC.y;
        gcData->unk334.z += spDC.z;
    }
    if (gcData->usingFuel) {
        gcData->unkF0 = func_80313AF4((gcData->unkB4 * 94.24764f) + 10.47196f, gcData->unkF0, 1.0f);
        if (gcData->unk98 == 0xFF) {
            spC8.x = -0.707f;
            spC8.y = -0.707f;
            spC8.z = 0.2f;
            uvMat4LocalToWorld(&gcData->unk150, &spC8, &spC8);
            gcData->unk98 = smokeCreate();
            // clang-format off
            smokeProps(
                gcData->unk98,
                SMOKE_PROP_1(200, 200, 200),
                SMOKE_PROP_2(1.8f),
                SMOKE_PROP_3(1.0f),
                SMOKE_PROP_4(2.0f),
                SMOKE_PROP_5(spC8.x, spC8.y, spC8.z),
                SMOKE_PROP_6(gcData->unk10.m[3][0], gcData->unk10.m[3][1], gcData->unk10.m[3][2]),
                SMOKE_PROP_7(1),
                SMOKE_PROP_END
            );
            // clang-format on
            spC8.x = 0.707f;
            spC8.y = -0.707f;
            spC8.z = 0.2f;
            uvMat4LocalToWorld(&gcData->unk150, &spC8, &spC8);
            gcData->unk9A = smokeCreate();
            // clang-format off
            smokeProps(
                gcData->unk9A,
                SMOKE_PROP_1(200, 200, 200),
                SMOKE_PROP_2(1.8f),
                SMOKE_PROP_3(1.0f),
                SMOKE_PROP_4(2.0f),
                SMOKE_PROP_5(spC8.x, spC8.y, spC8.z),
                SMOKE_PROP_6(gcData->unk10.m[3][0], gcData->unk10.m[3][1], gcData->unk10.m[3][2]),
                SMOKE_PROP_7(1),
                SMOKE_PROP_END
            );
            // clang-format on
        }
    } else {
        gcData->unkF0 = func_80313AF4(0.0f, gcData->unkF0, 0.5f);
    }
}

void func_80308478(GyrocopterData* gcData) {
    Vec3F sp44;
    Vec3F sp38;
    f32 temp_fv0;

    if (gcData->unkC0 == 0) {
        env_802E1754(gcData->unk10.m[3][0], gcData->unk10.m[3][1], gcData->unk10.m[3][2], &sp38);
        uvMat4LocalToWorld(&gcData->unk110, &sp44, &sp38);
        if ((uvVec3Len(&sp38) == 0.0f) && (gcData->unkB4 == 0.5) && (ABS_NOEQ(gcData->unk1FC) < 0.001f) && (ABS_NOEQ(gcData->unk200) < 0.001f) &&
            (ABS_NOEQ(gcData->unk1F0) < 0.001f) && (ABS_NOEQ(gcData->unk1F4) < 0.001f) && (gcData->unkA0 == 0.0f) && (gcData->unk9C == 0.0f) &&
            (gcData->fuel > 0.0f)) {
            if (gcData->unk7C == 0) {
                gcData->unk7C = 1;
            }
        } else {
            gcData->unk7C = 0;
        }
    } else {
        sp44.x = sp44.y = sp44.z = 0.0f;
        sp38.x = sp38.y = sp38.z = 0.0f;
        gcData->unk7C = 0;
    }

    if (gcData->unk1A8 < 51.587303f) {
        temp_fv0 = gcData->unk1A8 / 51.587303f;
        temp_fv0 = SQ(temp_fv0);
        sp44.x *= temp_fv0;
        sp44.y *= temp_fv0;
        sp44.z *= temp_fv0;
        sp38.x *= temp_fv0;
        sp38.y *= temp_fv0;
        sp38.z *= temp_fv0;
    }
    gcData->unk364.x = sp44.x - gcData->unk190.x;
    gcData->unk364.y = sp44.y - gcData->unk190.y;
    gcData->unk364.z = sp44.z - gcData->unk190.z;
    gcData->unk31C.x += 0.21f * sp44.x;
    gcData->unk31C.y += 0.21f * sp44.y;
    gcData->unk31C.z += 0.21f * sp44.z;
    gcData->unk1B8.x += 0.21f * sp38.x;
    gcData->unk1B8.y += 0.21f * sp38.y;
    gcData->unk1B8.z += 0.21f * sp38.z;
}

void func_8030877C(GyrocopterData* gcData) {
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
    gcData->unk544 = 0;

    for (i = 0; i < 2; i++) {
        gcData->unk564[i] = 0.0f;
        gcData->unk545[i] = 0;
    }
    gcData->unkC1 = 0;
    gcData->unkD0 = 0;
    sp247 = func_802DB050(&D_80369070, &D_80369178, gcData->objId, gcData->unk2, &gcData->unk10);

    for (i = 0; i < sp247; i++) {
        func_802DBE64(&D_80369070, &D_80369178, i, &gcData->unk110);
        temp_s3 = &D_80369178.unk4[i];
        if ((temp_s3->collisionType == 2) && (targets_8034473C(temp_s3->surfaceId, 1) == 0.0f)) {
            return;
        }
        if (temp_s3->unk0 == 0) {
            temp_v0_3 = &D_80369070.unk4[temp_s3->unk0];
            func_802DCA5C(&temp_v0_3->unk28, &temp_v0_3->unk1C, &temp_s3->unk28, &temp_s3->unk34, &sp2B4);
            sp2A8.x = gcData->unk10.m[3][0];
            sp2A8.y = gcData->unk10.m[3][1];
            sp2A8.z = gcData->unk10.m[3][2];
            uvMat4Copy(&sp25C, &gcData->unk10);
            uvMat4LocalTranslate(&sp25C, sp2B4.x, sp2B4.y, sp2B4.z);
            sp29C.x = sp25C.m[3][0];
            sp29C.y = sp25C.m[3][1];
            sp29C.z = sp25C.m[3][2];
            func_802DB224(&spF0, 0xFF, gcData->objId, gcData->unk2, &sp2A8, &sp29C);
            if (spF0.unk0 > 0) {
                for (j = 0; j < spF0.unk0; j++) {
                    if (spF0.unk4[j].collisionType == 2) {
                        var_s0++;
                    }
                }
                if (spF0.unk0 != var_s0) {
                    gcData->unkC0 = 3;
                    _uvDebugPrintf("hmot : you got stuck - forcing an instant crash\n");
                    return;
                }
            }

            uvMat4Copy(&gcData->unk10, &sp25C);
            gcData->unk668.x = gcData->unk10.m[3][0];
            gcData->unk668.y = gcData->unk10.m[3][1];
            gcData->unk668.z = gcData->unk10.m[3][2];
        }
    }

    for (i = 0; i < sp247; i++) {
        temp_s3 = &D_80369178.unk4[i];
        if ((temp_s3->collisionType != 2) || ((temp_s3->collisionType == 2) && !ballsObjIdExists(temp_s3->surfaceId))) {
            func_802DC814(&D_80369178.unk4[i], (Vec3F*)gcData->unk10.m[3]);
        }
        uvVec3Copy(&sp2E4[i], &temp_s3->unk28);
        uvVec3Copy(&sp2C0[i], &temp_s3->unk34);
        temp_fv0 = uvVec3Dot(&gcData->unk190, &sp2C0[i]);
        if (gcData->unk564[gcData->unk544] < temp_fv0) {
            uvVec3Copy(&gcData->unk54C[gcData->unk544], &temp_s3->unkC);
            gcData->unk545[gcData->unk544] = temp_s3->collisionType;
            gcData->unk564[gcData->unk544] = temp_fv0;
        }

        switch (temp_s3->collisionType) {
        case 2:
            sp240 = ballsPopped(temp_s3->surfaceId, &gcData->unk19C, &D_80369178);
            if (sp240 == 0.0f) {
                return;
            }
            break;
        case 4:
            if (gcData->unkC0 == 2) {
                smokeProps(gcData->unk96, SMOKE_PROP_8(0), SMOKE_PROP_END);
            }
            gcData->unkC0 = 3;
            gcData->unkD0 = 1;
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
        temp_fv0 = uvVec3Dot(&gcData->unk19C, &temp_s3->unk1C);
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
            if (gcData->unkC0 != 2) {
                gcData->unk96 = smokeCreate();
                // clang-format off
                smokeProps(
                    gcData->unk96,
                    SMOKE_PROP_1(0, 0, 0),
                    SMOKE_PROP_2(20.0f),
                    SMOKE_PROP_3(2.0f),
                    SMOKE_PROP_5(0.0f, 0.0f, 0.0f),
                    SMOKE_PROP_END
                );
                // clang-format on
            }
            gcData->unkC0 = 2;
        } else {
            if (gcData->unk1A8 > 0.0f) {
                var_fa0 = ABS_NOEQ(temp_fv0 / gcData->unk1A8);
                if (var_fa0 > 0.707f) {
                    if (gcData->unkC0 != 2) {
                        gcData->unk96 = smokeCreate();
                        // clang-format off
                        smokeProps(
                            gcData->unk96,
                            SMOKE_PROP_1(0, 0, 0),
                            SMOKE_PROP_2(20.0f),
                            SMOKE_PROP_3(2.0f),
                            SMOKE_PROP_5(0.0f, 0.0f, 0.0f),
                            SMOKE_PROP_END
                        );
                        // clang-format on
                    }
                    gcData->unkC0 = 2;
                } else if (gcData->unkC0 != 2) {
                    gcData->unkC1 = temp_s3->collisionType;
                }
            } else if (gcData->unkC0 != 2) {
                gcData->unkC1 = temp_s3->collisionType;
            }
        }
    }

    if (sp247 > 2) {
        _uvDebugPrintf("Heli has more than 2 hits\n");
    } else if (sp247 > 0) {
        func_802DC380(sp247, &gcData->unk150, &gcData->unk190, &gcData->unk19C, &gcData->unk1C8, &sp2C0[0], &sp2C0[1], &sp2E4[0], &sp2E4[1], sp250[0], sp250[1],
                      0.004f, 0.01f, 0.01f, 0.01f);
    }

    if (gcData->unk564[gcData->unk544] > 0.0f) {
        gcData->unk547[gcData->unk544++] = 0;
    }
}

void func_80308F1C(GyrocopterData* gcData) {
    f32 sp54;
    Vec3F sp48;
    s32 sp44;
    Vec3F* sp2C;
    s32 pad[2];
    u8 sp37;

    sp2C = (Vec3F*)gcData->unk10.m[3];
    sp37 = db_getgnd(&gcData->unk668, sp2C, &gcData->unk674, &sp44, &sp54, &sp48);
    uvVec3Copy(&gcData->unkC4, func_802E02EC());

    if (((sp44 == -1) && (sp54 > 0.0f) && (sp37 != 0) && (gcData->unk10.m[3][2] > 0.0f)) || ((sp37 == 2) && (targets_8034473C(sp44, 1) == 0.0f))) {
        sp37 = 0;
    }
    if (sp37) {
        if (sp37 == 4) {
            if (gcData->unkC0 == 2) {
                smokeProps(gcData->unk96, SMOKE_PROP_8(0), SMOKE_PROP_END);
            }
            gcData->unkD0 = 1;
            gcData->unkC0 = 3;
        }
        func_802E05CC(&gcData->unk10, func_802E02EC(), &sp48, 0);
        if (gcData->unk674 == 2) {
            gcData->unk674 = 1;
        } else {
            gcData->unk674 = 2;
        }
    }
    gcData->unk668.x = sp2C->x;
    gcData->unk668.y = sp2C->y;
    gcData->unk668.z = sp2C->z;
}

void func_80309090(GyrocopterData* gcData) {
    Vec3F sp4C;
    Vec3F sp40;
    f32 sp3C;
    f32 sp38;
    f32 temp_fv0;

    if (gcData->unkC0 != 0) {
        gcData->unk1AC.x = gcData->unk31C.x;
        gcData->unk1AC.y = gcData->unk31C.y;
        gcData->unk1AC.z = gcData->unk31C.z;
        gcData->unk1E0 = gcData->unk328.x;
        gcData->unk1E4 = gcData->unk328.y;
        gcData->unk1E8 = gcData->unk328.z;
        return;
    }

    gcData->unk1AC.x = gcData->unk31C.x;
    gcData->unk1AC.y = gcData->unk31C.y;
    gcData->unk1AC.z = gcData->unk31C.z;

    uvMat4LocalToWorld(&gcData->unk29C, &sp4C, &gcData->unk190);
    if ((sp4C.z < 0.0f) && (gcData->unkA0 < 0.0f) && (sp4C.y < 7.5f) && (((gcData->unk6D == 0) && (gcData->unk6E == 0)) || (gcData->unk6D == 1))) {
        if (sp4C.z > -40.0f) {
            uvMat4LocalToWorld(&gcData->unk29C, &sp40, &gcData->unk1AC);
            sp40.x = 0.0f;
            if (gcData->unk6D == 0) {
                gcData->unk70 = sp40.y;
                gcData->unk74 = ABS_NOEQ(sp40.y / sp4C.y);
            }
            if (sp4C.y > 0.0f) {
                if (gcData->unk70 != 0.0f) {
                    gcData->unk70 = func_80313AF4(0.0f, gcData->unk70, gcData->unk74);
                    if (ABS_NOEQ(gcData->unk70) < 0.00001f) {
                        gcData->unk70 = 0.0f;
                    }
                }
            } else {
                gcData->unk70 = -sp4C.y / D_8034F854;
            }
            sp40.y = gcData->unk70;
            sp40.z = (((0.5 - gcData->unkB4) * 0.20000000298023224) + .5) * (-9.800000190734863);
            uvMat4LocalToWorld(&gcData->unk2DC, &gcData->unk1AC, &sp40);
        } else {
            gcData->unk1AC.x = 0.0f;
            gcData->unk1AC.y = 0.0f;
            gcData->unk1AC.z = 0.0f;
        }
        gcData->unk1FC = (gcData->unk218 * -0.5f * gcData->unk1F0) / 0.7853982f;
        gcData->unk6D = 1;
        gcData->unk1F8 = -gcData->unk644 * gcData->unk214;
    } else {
        if (gcData->unk6D == 1) {
            gcData->unk6E = 1;
            gcData->unk78 = 0.0f;
        }
        gcData->unk6D = 0;
        if (gcData->unk6E != 0) {
            uvMat4LocalToWorld(&gcData->unk29C, &sp40, &gcData->unk1AC);
            if ((sp4C.z < -2.0f) && (gcData->unkA0 == 0.0f)) {
                sp38 = gcData->unk78;
                // FAKE
                sp3C = (0, sp40.z) + (sp4C.z / 3.0f);
                gcData->unk78 = func_80313AF4(1.0f, gcData->unk78, 6.0f);
                sp3C *= (sp38 * gcData->unk78);
                sp40.z -= sp3C;
                if (sp4C.y < 0.0f) {
                    sp40.y = -sp4C.y / D_8034F854;
                } else if (sp40.y < 0.0f) {
                    sp40.y = 0.0f;
                }
                uvMat4LocalToWorld(&gcData->unk2DC, &gcData->unk1AC, &sp40);
            } else {
                gcData->unk6E = 0;
            }
        }
    }
    if ((gcData->unk6D == 0) && (gcData->unk6E == 0)) {
        if (gcData->unk7C != 0) {
            if (ABS_NOEQ(gcData->unk1AC.y) < 0.08f) {
                if (gcData->unk7C == 1) {
                    gcData->unk80 = gcData->unk1AC.y;
                    gcData->unk84 = gcData->unk1AC.z;
                    gcData->unk88 = (gcData->unk1AC.z + ((4.0f * sp4C.z) / (100.0f * D_8034F854))) * -0.5f;
                } else if (gcData->unk7C > 100) {
                    gcData->unk7C = 1;
                    gcData->unk80 = 0.0f;
                    gcData->unk84 = 0.0f;
                    gcData->unk88 = (-2.0f * sp4C.z) / (100.0f * D_8034F854);
                }
                if (gcData->unk7C < 50.0f) {
                    temp_fv0 = gcData->unk7C / 50.0f;
                    gcData->unk1AC.z = gcData->unk84 + ((gcData->unk88 - gcData->unk84) * temp_fv0);
                } else if (gcData->unk7C < 100) {
                    temp_fv0 = (1.0f - ((gcData->unk7C - 50.0f) / 50.0f));
                    gcData->unk1AC.z = gcData->unk88 * temp_fv0;
                } else {
                    gcData->unk1AC.y = 0.0f;
                    gcData->unk1AC.z = 0.0f;
                }
                if (gcData->unk7C < 100) {
                    if (gcData->unk80 > 0.0f) {
                        temp_fv0 = gcData->unk7C / 100.0f;
                        gcData->unk1AC.y = gcData->unk80 * (1.0f - temp_fv0);
                    }
                    gcData->unk7C++;
                } else {
                    if (ABS_NOEQ(gcData->unk190.z) > 0.00001f) {
                        gcData->unk7C++;
                    }
                }
            }
        }
    }
    if ((gcData->unk6D == 0) && (gcData->unk6E == 0) && (gcData->unk7C == 0)) {
        if (gcData->unk190.y > 97.222f) {
            if (gcData->unk90 < gcData->unk1AC.y) {
                if (gcData->unk90 == 0.0f) {
                    gcData->unk90 = gcData->unk1AC.y;
                    gcData->unk74 = gcData->unk1AC.y / (99.206f - gcData->unk190.y);
                }
                if (gcData->unk190.y < 99.206f) {
                    if (gcData->unk90 != 0.0f) {
                        gcData->unk90 = func_80313AF4(0.0f, gcData->unk90, gcData->unk74);
                        if (gcData->unk1AC.y < gcData->unk90) {
                            gcData->unk90 = gcData->unk1AC.y;
                        }
                        if (ABS_NOEQ(gcData->unk90) < 0.00001f) {
                            gcData->unk90 = 0.0f;
                        }
                    }
                } else {
                    gcData->unk90 = 0.0f;
                }
                gcData->unk1AC.y = gcData->unk90;
                return;
            }
        }
    }
    gcData->unk90 = 0.0f;
}
