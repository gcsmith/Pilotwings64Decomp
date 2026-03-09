#ifndef APP_CODE_72B70_H
#define APP_CODE_72B70_H

#include <uv_level.h>
#include <uv_matrix.h>

extern Unk80364210 D_80364210[];

typedef struct {
    u8 testCount;
    u8 pad1[0x157];
} Unk80367710;

// D_3067708 is pointer to this struct passed to other functions
typedef struct {
    u16 unk0;
    u8 unk2;
    u16 unk4;
    u8 pad6[0x8-6];
    f32 unk8;
    u16 controller;
    u8 padE[2];
    Mtx4F unk10;
    Mtx4F unk50;
    Mtx4F unk90;
    f32 unkD0;
    Unk802D3658_Arg0* unkD4;
    u8 unkD8;
    u8 padD9[3];
    f32 unkDC;
    u8 unkE0;
    u8 padE1[3];
    f32 unkE4;
    f32 unkE8;
    f32 unkEC;
    f32 unkF0;
    u8 padF4[0x10];
    u8 unk104;
    u8 unk105;
    u8 unk106;
    u8 unk107;
    u8 unk108[4]; // unknown size
    u8 pad10C[0x140 - 0x10C];
    f32 unk140[4]; // unknown size
    Vec3F unk150;
    u8 unk15C;
    f32 unk160;
    f32 unk164;
    f32 unk168;
    f32 unk16C;
    s32 unk170;
    f32 unk174;
    f32 unk178;
    f32 unk17C;
    Mtx4F unk180;
    Mtx4F unk1C0;
    Vec3F unk200;
    Vec3F unk20C;
    Vec3F unk218;
    f32 unk224;
    Vec3F unk228;
    Vec3F unk234;
    f32 unk240;
    f32 unk244;
    f32 unk248;
    f32 unk24C;
    Vec3F unk250;
    Vec3F unk25C;
    Vec3F unk268;
    Vec3F unk274;
    f32 unk280;
    u8 pad284[0x290 - 0x284];
    u8 unk290;
    u8 pad291[0x294 - 0x291];
    Vec3F unk294;
    f32 unk2A0;
    f32 unk2A4;
    f32 unk2A8;
    f32 unk2AC;
    f32 unk2B0;
    f32 unk2B4;
    u8 unk2B8;
    u8 pad2B9[3];    
    f32 unk2BC;
    u8 unk2C0;
    u8 pad2C1[3];
    f32 unk2C4;
    f32 unk2C8;
    u8 unk2CC;
    u8 pad2CD[3];
    f32 unk2D0;
    f32 unk2D4;
    f32 unk2D8;
    f32 unk2DC;
    f32 unk2E0;
    f32 unk2E4;
    f32 unk2E8;
    f32 unk2EC;
    u8 unk2F0;
    u8 pad2F1[0x2F8 - 0x2F1];
    u8 unk2F8;
    u8 unk2F9;  
    u8 pad2FA[0x2FC - 0x2FA];  
    f32 unk2FC;
    f32 unk300;
    f32 unk304;
    f32 unk308;
    u8 pad30C[0x320 - 0x30C];
    Vec3F unk320;
    Vec3F unk32C;
    Vec3F unk338;
    Vec3F unk344;
    s32 unk350;
    f32 unk354;
    f32 unk358;
    f32 unk35C;
    f32 unk360;
    f32 unk364;
    f32 unk368;
    f32 unk36C;
    f32 unk370;
    f32 unk374;
    f32 unk378;
    f32 unk37C;
    f32 unk380;
    f32 unk384;
    f32 unk388;
    f32 unk38C;
    f32 unk390;
    f32 unk394;
    f32 unk398;
    f32 unk39C;
    f32 unk3A0;
    f32 unk3A4;
    f32 unk3A8;
    f32 unk3AC;
    f32 unk3B0;
    f32 unk3B4;
    f32 unk3B8;
    f32 unk3BC;
    f32 unk3C0;
    u8 pad3C4[0x3F4 - 0x3C4];
    u16 unk3F4;
    u8 unk3F6;
    u8 unk3F7;
    u8 unk3F8;
    u8 unk3F9;
    u8 pad3FA[0x3FE - 0x3FA];
    u8 unk3FE;
    u8 unk3FF;
    Vec3F unk400;
    s32 unk40C;
    s32 unk410;
    u8 unk414;
    u8 unk415;
    u8 pad416[0x41C - 0x416];
    f32 unk41C;
    f32 unk420;
} VehicleData;

void func_802EB9C0(void);
void func_802EBBB8(void);
void func_802EBC30(void);
void func_802EDDEC(Mtx4F*);
void func_802EDAF0(void*, Mtx4F*, s32, s32, f32, f32, f32, u32, s32, s32, s32);
void func_802EE14C(s32);

#endif // APP_CODE_72B70_H
