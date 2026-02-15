#ifndef CODE_5A6A0_H
#define CODE_5A6A0_H

#include <uv_matrix.h>
#include <uv_vector.h>
#include <uv_level.h>

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

typedef struct {
    u16 unk0;
    u8 unk2;
    u8 pad3;
    u16 unk4;
    u16 pad6;
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
    u8 unkD5;
    u8 padD6[0x11C - 0xD6];
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
void func_802D4DE8(Unk802D3658_Arg0*, u8);
void func_802D3170(u8, Unk802D3658_Arg0*);
void func_802D3444(Unk802D3658_Arg0*);
void func_802D50D0(Unk802D3658_Arg0*);
void func_802D4514(Unk802D3658_Arg0*);
void func_802D45C4(Unk802D3658_Arg0*, f32);
s32 func_802D472C(Unk802D3658_Arg0*, Mtx4F*);

#endif // CODE_5A6A0_H
