#ifndef APP_CAMERA_H
#define APP_CAMERA_H

#include <uv_matrix.h>
#include <uv_vector.h>

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 surfaceId;
    Vec3F unkC;
    f32 unk18;
    Vec3F unk1C;
    Vec3F unk28;
    Vec3F unk34;
} Unk802D3658_Unk1228; // size = 0x40

typedef struct {
    s32 unk0;
    Unk802D3658_Unk1228 unk4[5];
} Unk802D3658_Unk1224; // size = 0x144

typedef struct Unk802D3658_Unk230 {
    Mtx4F unk0;
    f32 unk40;
    struct Unk802D3658_Unk230* unk44;
    u8 unk48[4];
} Unk802D3658_Unk230;

typedef struct {
    s32 unk0;
    Vec3F unk4;
    Vec3F unk10;
    Vec3F unk1C;
    Vec3F unk28;
} Unk802D3658_Unk1120; // size = 0x34

typedef struct {
    s32 unk0;
    Unk802D3658_Unk1120 unk4[5];
} Unk802D3658_Unk111C; // size = 0x108

typedef struct {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u16 unk4;
    u8 unk6;
    u8 pad7;
    f32 unk8;
    u8 unkC;
    u8 unkD;
    u8 unkE;
    u8 unkF;
    u8 pad10[0x14 - 0x10];
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    s16 unk24;
    s16 unk26;
    s16 unk28;
    s16 unk2A;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    f32 unk40;
    f32 unk44;
    f32 unk48;
    f32 unk4C;
    f32 unk50;
    f32 unk54;
    f32 unk58;
    f32 unk5C;
    f32 unk60;
    f32 unk64;
    Vec3F unk68;
    f32 unk74;
    f32 unk78;
    f32 unk7C;
    Mtx4F unk80; //  80: BF
    f32 unkC0;
    f32 unkC4;
    Mtx4F unkC8;  //  C8:107
    Mtx4F unk108; // 108:147
    u8 unk148;
    u8 pad149[3];
    Mtx4F unk14C; // 14C:18B
    f32 unk18C;
    f32 unk190;
    f32 unk194;
    f32 unk198;
    f32 unk19C;
    f32 unk1A0;
    f32 unk1A4;
    f32 unk1A8;
    f32 unk1AC;
    f32 unk1B0;
    f32 unk1B4;
    f32 unk1B8;
    Mtx4F unk1BC; // 1BC:1FB
    f32 unk1FC;
    f32 unk200;
    Vec3F unk204;
    Vec3F unk210;
    f32 unk21C;
    f32 unk220;
    f32 unk224;
    f32 unk228;
    u8 unk22C;
    u8 pad22D[0x230 - 0x22D];
    Unk802D3658_Unk230 unk230[50]; // 230:1107
    u8 pad1108[0x1114 - 0x1108];
    u8 unk1114;
    u8 pad1115[0x111C - 0x1115];
    Unk802D3658_Unk111C unk111C;
    Unk802D3658_Unk1224 unk1224;
    f32 unk1368;
    f32 unk136C;
    f32 unk1370;
    f32 unk1374;
    f32 unk1378;
    s32 unk137C;
    f32 unk1380;
} Camera;

void func_802D45C4(Camera*, f32);
s32 func_802D472C(Camera*, Mtx4F*);
s32 func_802D4A30(Camera*, Mtx4F*);
void func_802D4ECC(Camera*, Mtx4F*);
void func_802D5884(Camera*, u8);
void func_802D4DE8(Camera*, u8);
void func_802D3170(u8, Camera*);
void func_802D3444(Camera*);
void func_802D50D0(Camera*);
void func_802D4514(Camera*);

#endif // APP_CAMERA_H
