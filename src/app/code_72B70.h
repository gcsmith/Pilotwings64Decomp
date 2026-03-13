#ifndef APP_CODE_72B70_H
#define APP_CODE_72B70_H

#include <uv_matrix.h>
#include <uv_dobj.h>
#include "level.h"
#include "save.h"

extern Unk80364210 D_80364210[];

typedef struct {
    u8 testCount;
    u8 pad1[0x157];
} Unk80367710;

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
} Unk802D3658_Arg0;

typedef struct Unk80362690_Unk0_UnkC_Unk6C {
    u16 objId;
    u8 unk2;
    u16 unk4;
    u8 pad6[0x2];
    f32 unk8;
    u16 unkC;
    u8 padE[0x2];
    f32 unk10;
    f32 unk14;
    Unk802D3658_Arg0* unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    Vec3F unk30;
    f32 unk3C;
    f32 unk40;
    u8 unk44;
    u8 pad45[0x3];
    f32 unk48;
    u8 unk4C;
    u8 unk4D;
    u8 pad4E[0x1];
    u8 unk4F;
    u8 unk50;
    u8 pad51[0xF];
    s32 unk60;
    f32 unk64;
    f32 unk68;
    f32 unk6C;
    f32 unk70;
    Mtx4F unk74;
    Mtx4F unkB4;
    Vec3F unkF4;
    Vec3F unk100;
    Vec3F unk10C;
    Vec3F unk118;
    Vec3F unk124;
    f32 unk130;
    Vec3F unk134;
    Vec3F unk140;
    Vec3F unk14C;
    f32 unk158;
    Vec3F unk15C;
    Vec3F unk168;
    Vec3F unk174;
    f32 unk180;
    Vec3F unk184;
    f32 unk190;
    f32 unk194;
    s32 unk198;
    s32 unk19C;
    s32 unk1A0;
    s32 unk1A4;
    f32 unk1A8;
    s32 unk1AC;
    s32 unk1B0;
    u8 pad1B4[0x4];
    f64 unk1B8;
    f64 unk1C0;
    f64 unk1C8;
    f32 unk1D0;
    Unk80371120 unk1D4;
    Unk80371120 unk384;
    s32 unk534;
    s32 unk538;
    f32 unk53C;
    f32 unk540;
    f32 unk544;
    f32 unk548;
    f32 unk54C;
    f32 unk550;
    f32 unk554;
    f32 unk558;
    u8 unk55C;
    f32 unk560;
    f32 unk564;
    f32 unk568;
    u8 unk56C;
    f32 unk570;
    f32 unk574;
    f32 unk578;
    u8 unk57C;
    f32 unk580;
    f32 unk584;
    f32 unk588;
    u8 unk58C;
    f32 unk590;
    f32 unk594;
    f32 unk598;
    s16 unk59C;
    f32 unk5A0;
    s16 unk5A4;
    f32 unk5A8;
    s16 unk5AC;
    f32 unk5B0;
    s16 unk5B4;
    f32 unk5B8;
    s16 unk5BC;
    f32 unk5C0;
    f32 unk5C4;
    s16 unk5C8;
    f32 unk5CC;
    s16 unk5D0;
    f32 unk5D4;
    f32 unk5D8;
    f32 unk5DC;
    f32 unk5E0;
    u16 modelId;
    Vec3F unk5E8;
    Vec3F unk5F4;
    Vec3F unk600;
    Vec3F unk60C;
    Vec3F unk618;
    Vec3F unk624;
    Vec3F unk630;
    f32 unk63C;
    f32 unk640;
    f32 unk644;
    f32 unk648;
    f32 unk64C;
    u8 unk650;
    u8 unk651;
    u8 unk652;
    u8 unk653;
    u8 unk654;
    u8 unk655;
    u8 unk656;
    u8 unk657;
    u8 unk658;
    u8 unk659;
    u8 unk65A;
    u8 unk65B;
    u8 unk65C;
    u8 unk65D;
    u8 unk65E[0x6];
    f32 unk664;
    f32 unk668;
    f32 unk66C;
    Vec3F unk670;
    s32 unk67C;
} Unk80362690_Unk0_UnkC_Unk6C;

typedef struct {
    u16 pilot; // PilotId
    u16 veh; // VehicleId
    u16 cls; // ClassId: Beg/A/B/Pilot (or level for bonus)
    u16 test; // test number (or target for CB)
    u16 unk8;
    u8 unkA;
    u8 padB[0x20 - 0xB];
    f32 unk20;
    u8 pad24[0x2C-0x24];
    Mtx4F unk2C;
    void* vehicleData;
    Unk802D3658_Arg0 *unk70;
    Unk80364210 *unk74;
    u8 pad78[0x7B - 0x78];
    u8 unk7B;
    u8 pad7C[0x8C-0x7C-0xC]; // fill out space to reach 0x8C size in parent struct
} Unk80362690_Unk0_UnkC;

typedef struct {
    s32 unk0;
    u16 map;
    u16 terraId;
    u16 unk8;
    u8 debugFlag;
    u8 unkB;
    Unk80362690_Unk0_UnkC unkC;
} Unk80362690_Unk0;

typedef struct {
    Unk80362690_Unk0 unk0[1];
    s32 unk8C;
    s32 unk90;
    s32 unk94;
    s32 unk98;
    s32 unk9C;
    u8 unkA0;
    u8 unkA1;
    u8 unkA2;
    u8 unkA3;
    u8 unkA4;
    u8 padA5[3];
    s32 unkA8;
} Unk80362690;

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
    Vec3F unk174;
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

extern Unk80362690* D_80362690;

void func_802EB9C0(void);
void func_802EBBB8(void);
void func_802EBC30(void);
s32 func_802EC50C(Unk80362690*);
s32 func_802ECE94(Unk80362690*);
void func_802EDDEC(Mtx4F*);
void func_802EDAF0(void*, Mtx4F*, s32, s32, f32, f32, f32, u32, s32, s32, s32);
void func_802EE14C(s32);

#endif // APP_CODE_72B70_H
