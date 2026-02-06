#ifndef CODE_5A6A0_H
#define CODE_5A6A0_H

#include <uv_matrix.h>
#include <uv_vector.h>

typedef struct {
    s32 unk0;
    f32 unk4;
    f32 unk8;
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
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    f32 unk40;
} Unk803599D0;

typedef struct Unk802D3658_Unk230 {
    Mtx4F unk0;
    f32 unk40;
    struct Unk802D3658_Unk230* unk44;
    u8 unk48[4];
} Unk802D3658_Unk230;

typedef struct {
    s32 unk0;
    u8 pad4[0x18];
    Vec3F unk1C;
    Vec3F unk28;
} Unk802D3658_Unk1120;

typedef struct {
    s32 unk0;
    u8 pad4[0x24];
    Vec3F unk28;
    Vec3F unk34;
} Unk802D3658_Unk1228;

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
    f32 unk68;
    f32 unk6C;
    f32 unk70;
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

    s32 unk111C;
    Unk802D3658_Unk1120 unk1120[5]; // 1120:1223

    s32 unk1224;
    Unk802D3658_Unk1228 unk1228[5]; // 1228:1367

    f32 unk1368;
    f32 unk136C;
    f32 unk1370;
    f32 unk1374;
    f32 unk1378;
    s32 unk137C;
    f32 unk1380;
} Unk802D3658_Arg0;

typedef struct {
    u16 unk0;
    u8 unk2;
    u8 pad3;
    s32 pad4;
    f32 unk8;
    u16 unkC;
    u16 unkE;
    u16 unk10;
    u16 pad12;
    Mtx4F unk14;
    u16 unk54;
    u8 unk56;
    u8 pad57;
    Mtx4F unk58;
    f32 unk98;
    union {
        f32 zxAxis[2];
        struct {
            f32 zAxis; // rotation intended here
            f32 xAxis;
        };
    };
    f32 unkA4;
    u8 padA8[0xB0 - 0xA8];
    Unk802D3658_Arg0* unkB0;
    u8 unkB4;
    u8 padB5[3];
    f32 unkB8;
    f32 unkBC;
    f32 unkC0;
    u8 unkC4;
    u8 padC5[3];
    f32 unkC8;
    f32 unkCC;
    f32 unkD0;
    u8 unkD4;
    u8 padD5[0x11C - 0xD5];
    u8 unk11C;
    s8 unk11D;
    f32 unk120;
    u8 pad124[0x12C - 0x124];
    f32 unk12C;
    f32 unk130;
    f32 unk134;
    u8 pad138[0x1B8 - 0x138];
    f32 unk1B8;
    f32 unk1BC;
    f32 unk1C0;
    f32 unk1C4;
    f32 unk1C8;
    f32 unk1CC;
    f32 unk1D0;
    u8 pad1D4[0x220 - 0x1D4];
    u16 unk220;
    u8 pad222[0x4A];
    f32 unk26C;
    f32 unk270;
    f32 unk274;
    u8 pad278[0x280 - 0x278];
    f32 unk280;
    u8 pad284[0x293 - 0x284];
    u8 unk293;
    u8 pad294[0x2B4 - 0x294];
    u8 unk2B4;
} Unk802D5C5C_Arg0;

void func_802D45C4(Unk802D3658_Arg0*, f32);
s32 func_802D472C(Unk802D3658_Arg0*, Mtx4F*);
s32 func_802D4A30(Unk802D3658_Arg0*, Mtx4F*);
void func_802D5884(Unk802D3658_Arg0*, u8);

#endif // CODE_5A6A0_H
