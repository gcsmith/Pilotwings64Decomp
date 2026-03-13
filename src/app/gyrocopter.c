#include "common.h"
#include <uv_math.h>
#include <uv_matrix.h>
#include <uv_vector.h>
#include "gyrocopter.h"
#include "app/demo_attitude.h"
#include "app/hud.h"
#include "app/smoke.h"
#include "app/task.h"
#include "app/code_61A60.h"
#include "app/code_9A960.h"

s32 D_8034F3E0[4] = { 0 };

// 0x58
// 0x73C

typedef struct UnkGyrocopterStruct_Unk3B0 {
    Vec3F unk0;
    s32 unkC;
    u8 pad10[0x48];
} UnkGyrocopterStruct_Unk3B0;

typedef struct UnkGyrocopterStruct {
    u8 pad0[0x4];
    u16 unk4;
    u8 pad6[0xA];
    Mtx4F unk10;
    s32 unk50;
    f32 unk54;
    u8 pad58[0x14];
    u8 unk6C;
    u8 unk6D;
    u8 unk6E;
    f32 unk70;
    u8 pad74[0x18];
    f32 unk8C;
    f32 unk90;
    s16 unk94;
    s16 unk96;
    s16 unk98;
    s16 unk9A;
    f32 unk9C;
    f32 unkA0;
    u8 padA4[0x8];
    f32 unkAC;
    u8 padB0[0x10];
    u8 unkC0;
    u8 unkC1;
    u8 padC2[0xE];
    u8 unkD0;
    u8 padD1[0x2];
    u8 unkD3;
    u8 padD4[0x4];
    f32 unkD8;
    u8 padDC[0x4];
    f32 unkE0;
    u8 padE4[0x4];
    f32 unkE8;
    f32 unkEC;
    u8 padF0[0x4];
    f32 unkF4;
    s32 unkF8;
    u8 padFC[0x4];
    f32 unk100;
    f32 unk104;
    f32 unk108;
    u8 unk10C;
    u8 pad10D[0x3];
    Mtx4F unk110;
    Mtx4F unk150;
    Vec3F unk190;
    Vec3F unk19C;
    f32 unk1A8;
    Vec3F unk1AC;
    Vec3F unk1B8;
    f32 unk1C4;
    f32 unk1C8;
    f32 unk1CC;
    f32 unk1D0;
    f32 unk1D4;
    f32 unk1D8;
    f32 unk1DC;
    f32 unk1E0;
    f32 unk1E4;
    f32 unk1E8;
    f32 unk1EC;
    f32 unk1F0;
    f32 unk1F4;
    f32 unk1F8;
    f32 unk1FC;
    f32 unk200;
    u8 pad204[0x18];
    Mtx4F unk21C;
    Mtx4F unk25C;
    Mtx4F unk29C;
    Mtx4F unk2DC;
    f32 unk31C;
    f32 unk320;
    f32 unk324;
    f32 unk328;
    f32 unk32C;
    f32 unk330;
    f32 unk334;
    f32 unk338;
    f32 unk33C;
    f32 unk340;
    f32 unk344;
    f32 unk348;
    u8 pad34C[0xC];
    f32 unk358;
    f32 unk35C;
    f32 unk360;
    f32 unk364;
    f32 unk368;
    f32 unk36C;
    u8 pad370[0x40];
    UnkGyrocopterStruct_Unk3B0 unk3B0[4];
    u8 pad510[0xDC];
    Vec3F unk5EC[4];
    u8 pad61C[0x4C];
    Vec3F unk668;
    s32 unk674;
    u8 pad678[0xC4];
} UnkGyrocopterStruct;

void func_80304738(UnkGyrocopterStruct*);
void func_80304B98(UnkGyrocopterStruct*);
void func_80305BE8(UnkGyrocopterStruct*);
s32 func_80305DC0(UnkGyrocopterStruct*);
void func_80307A9C(UnkGyrocopterStruct*);
void func_80307BAC(UnkGyrocopterStruct*);
void func_80307E2C(UnkGyrocopterStruct*);
void func_80307EA8(UnkGyrocopterStruct*);
void func_80308478(UnkGyrocopterStruct*);
void func_8030877C(UnkGyrocopterStruct*);
void func_80308F1C(UnkGyrocopterStruct*);
void func_80309090(UnkGyrocopterStruct*);

#pragma GLOBAL_ASM("asm/nonmatchings/app/gyrocopter/func_80303230.s")

void func_80303714(UnkGyrocopterStruct* arg0) {
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
    arg0->unk1C8 = 0.0f;
    arg0->unk1CC = 0.0f;
    arg0->unk1D0 = 0.0f;
    arg0->unk1E0 = 0.0f;
    arg0->unk1E4 = 0.0f;
    arg0->unk1E8 = 0.0f;
    arg0->unk1EC = 0.0f;
    arg0->unk1F0 = 0.0f;
    arg0->unk1F4 = 0.0f;
    arg0->unk1F8 = 0.0f;
    arg0->unk1FC = 0.0f;
    arg0->unk200 = 0.0f;
    arg0->unk364 = 0.0f;
    arg0->unk368 = 0.0f;
    arg0->unk36C = 0.0f;
    arg0->unk340 = 0.0f;
    arg0->unk344 = 0.0f;
    arg0->unk348 = 1.0f;
    arg0->unk100 = 0.0f;
    arg0->unk104 = 0.0f;
    arg0->unk108 = 1.0f;
    arg0->unk358 = 0.0f;
    arg0->unk35C = 0.0f;
    arg0->unk360 = -9.8f;
    arg0->unkC1 = 0;
    arg0->unkD0 = 0;
    arg0->unk10C = 0xFF;
    arg0->unk50 = -1;
    arg0->unk31C = 0.0f;
    arg0->unk320 = 0.0f;
    arg0->unk324 = 0.0f;
    arg0->unk328 = 0.0f;
    arg0->unk32C = 0.0f;
    arg0->unk330 = 0.0f;
    arg0->unk334 = 0.0f;
    arg0->unk338 = 0.0f;
    arg0->unk33C = 0.0f;
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
    arg0->unkD3 = 0;
    arg0->unk6C = 0;
    arg0->unk6E = 0;
    arg0->unk98 = 0xFF;
    arg0->unk9A = 0xFF;
    arg0->unk94 = 0xFF;
    if (arg0->unk96 != 0xFF) {
        smoke_props(arg0->unk96, 8, 0, 0);
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

void func_8030399C(UnkGyrocopterStruct* arg0) {
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

    arg0->unk31C = 0.0f;
    arg0->unk320 = 0.0f;
    arg0->unk324 = 0.0f;
    arg0->unk328 = 0.0f;
    arg0->unk32C = 0.0f;
    arg0->unk330 = 0.0f;
    arg0->unk334 = 0.0f;
    arg0->unk338 = 0.0f;
    arg0->unk33C = 0.0f;
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
        arg0->unk1B8.x = (arg0->unk1AC.x - (arg0->unk190.y * arg0->unk1D0)) + (arg0->unk190.z * arg0->unk1CC);
        arg0->unk1B8.y = (arg0->unk1AC.y - (arg0->unk190.z * arg0->unk1C8)) + (arg0->unk190.x * arg0->unk1D0);
        arg0->unk1B8.z = (arg0->unk1AC.z - (arg0->unk190.x * arg0->unk1CC)) + (arg0->unk190.y * arg0->unk1C8);
        uvMat4LocalToWorld(&arg0->unk150, &arg0->unk1B8, &arg0->unk1B8);
    } else {
        if (arg0->unkC0 == 1) {
            uvMat4LocalToWorld(&arg0->unk150, &arg0->unk1B8, &arg0->unk1AC);
            arg0->unk1AC.x += (arg0->unk190.y * arg0->unk1D0) - (arg0->unk190.z * arg0->unk1CC);
            arg0->unk1AC.y += (arg0->unk190.z * arg0->unk1C8) - (arg0->unk190.x * arg0->unk1D0);
            arg0->unk1AC.z += (arg0->unk190.x * arg0->unk1CC) - (arg0->unk190.y * arg0->unk1C8);
        } else {
            uvMat4LocalToWorld(&arg0->unk150, &arg0->unk1B8, &arg0->unk1AC);
        }
    }

    if (arg0->unkC0 == 0) {
        arg0->unk1C8 = arg0->unk1D4;
        arg0->unk1CC = arg0->unk1D8;
        arg0->unk1D0 = arg0->unk1DC;
        arg0->unk1EC += D_8034F854 * arg0->unk1F8;
        arg0->unk1F0 += D_8034F854 * arg0->unk1FC;
        arg0->unk1F4 += D_8034F854 * arg0->unk200;
    } else {
        arg0->unk1C8 += D_8034F854 * arg0->unk1E0;
        arg0->unk1CC += D_8034F854 * arg0->unk1E4;
        arg0->unk1D0 += D_8034F854 * arg0->unk1E8;
        if (arg0->unkC0 != 2) {
            spE4 = uvSinF(arg0->unk1F4);
            spE0 = uvCosF(arg0->unk1F4);
            spDC = uvSinF(arg0->unk1F0);
            arg0->unk1F8 = ((arg0->unk1D0 * spE0) - (arg0->unk1C8 * spE4)) / uvCosF(arg0->unk1F0);
            arg0->unk1FC = (arg0->unk1C8 * spE0) + (arg0->unk1D0 * spE4);
            arg0->unk200 = arg0->unk1CC - (arg0->unk1F8 * spDC);
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
        uvMat4RotateAxis(&arg0->unk10, arg0->unk1D0 * D_8034F854, 'z');
        uvMat4RotateAxis(&arg0->unk10, arg0->unk1C8 * D_8034F854, 'x');
        uvMat4RotateAxis(&arg0->unk10, arg0->unk1CC * D_8034F854, 'y');
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
        if ((FABS(arg0->unk1D0) < 0.0001f) && (((arg0->unk31C > 0.f) && (arg0->unk190.x < 0.f)) || ((arg0->unk31C < 0.f) && (arg0->unk190.x > 0.f)))) {
            arg0->unk190.x = func_80313AF4(0.f, arg0->unk190.x, 6.0f);
            uvMat4LocalToWorld(&arg0->unk150, &arg0->unk19C, &arg0->unk190);
        }
    }
    arg0->unk1A8 = uvVec3Len(&arg0->unk19C);
    arg0->unk1C4 = uvVec3Len(&arg0->unk1B8);
    if ((arg0->unk1A8 < 0.1f) || ((arg0->unkC0 == 1) && (arg0->unkD8 == 0.0f) && (arg0->unk190.y < 0.1f))) {
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
    
    if ((FABS(arg0->unk1F0) > 0.8028515f) || (FABS(arg0->unk1F4) > 1.0646509f)) {
        if (arg0->unkC0 != 2) {
            arg0->unkC0 = 2;
            arg0->unk96 = smoke_create();
            smoke_props(arg0->unk96, 1, 0, 0, 0, 2, 20.0f, 3, 2.0f, 5, 0.0f, 0.0f, 0.0f, 0);
        }
    }
    if (arg0->unkC0 == 2) {
        smoke_props(arg0->unk96, 6, arg0->unk10.m[3][0], arg0->unk10.m[3][1], arg0->unk10.m[3][2], 0);
    } else {
        if ((arg0->unk98 != -1) && (arg0->unk98 != 0xFF)) {
            smoke_getprops(arg0->unk98, 8, &spD6, 0);
            if (spD6 != 0) {
                smoke_props(arg0->unk98, 6, arg0->unk10.m[3][0], arg0->unk10.m[3][1], arg0->unk10.m[3][2], 0);
                smoke_props(arg0->unk9A, 6, arg0->unk10.m[3][0], arg0->unk10.m[3][1], arg0->unk10.m[3][2], 0);
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
                    smoke_props(arg0->unk94, 6, ((arg0->unk3B0[1].unk0.x + arg0->unk3B0[2].unk0.x) * 0.5f), (arg0->unk3B0[1].unk0.y + arg0->unk3B0[2].unk0.y) * 0.5f, arg0->unk3B0[1].unk0.z, 4, spD0 + D_8034F854, 7, 1, 0);
                } else {
                    smoke_props(arg0->unk94, 4, 0.0f, 0);
                }
            } else {
                arg0->unk94 = 0xFF;
            }
        } else if ((arg0->unkC0 == 1) && (arg0->unk1A8 > 5.952f) && (arg0->unk50 >= 0) && (arg0->unk6C == 0) && (func_802DC930(arg0->unkF8) != 0)) {
            arg0->unk94 = smoke_create();
            smoke_props(arg0->unk94, 1, 160, 120, 70, 2, 4.0f, 3, 3.0f, 4, 1.0f, 5, -arg0->unk10.m[1][0], -arg0->unk10.m[1][1], 0.5f, 6, (arg0->unk3B0[1].unk0.x + arg0->unk3B0[2].unk0.x) * 0.5f, (arg0->unk3B0[1].unk0.y + arg0->unk3B0[2].unk0.y) * 0.5f, arg0->unk3B0[1].unk0.z, 7, 1, 0);
        }
    }
    if (D_80362690->unkA4 != 0) {
        demoAttUpdate(D_8034F850, &arg0->unk10);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/gyrocopter/func_80304738.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/gyrocopter/func_80304B98.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/gyrocopter/func_80305BE8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/gyrocopter/func_80305DC0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/gyrocopter/func_80307A9C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/gyrocopter/func_80307BAC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/gyrocopter/func_80307E2C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/gyrocopter/func_80307EA8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/gyrocopter/func_80308478.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/gyrocopter/func_8030877C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/gyrocopter/func_80308F1C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/gyrocopter/func_80309090.s")
