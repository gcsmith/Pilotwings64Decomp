#ifndef APP_CODE_B6580_H
#define APP_CODE_B6580_H

#include <PR/ultratypes.h>
#include <uv_matrix.h>

typedef struct {
    u16 unk0;
    u8 pad2[0x10-0x2];
    Mtx4F unk10;
    u8 pad50[0x5C-0x50];
    f32 unk5C;
    f32 unk60;
    u8 pad64[0x70-0x64];
    u8 unk70;
    u8 pad71[0xB9-0x71];
    u8 unkB9;
    u8 padBA[0x1A0-0xBA];
    u16 unk1A0;
    u16 unk1A2;
    u16 unk1A4;
    u16 unk1A6;
    u16 unk1A8;
    u16 pad1AA;
    f32 unk1AC;
    f32 unk1B0;
    u8 pad1B4[0x1C0-0x1B4];
    u16 unk1C0;
    u8 pad1C2[0x21E - 0x1C2];
    u8 unk21E;
    u8 unk21F;
    u8 unk220;
    u8 unk221;
    u8 unk222;
    u8 unk223;
    u8 pad224[0x226-0x224];
    u8 unk226;
    u8 pad227;
    u8 unk228;
    u8 unk229;
    u8 unk22A;
    u8 unk22B;
    u8 unk22C;
    u8 unk22D;
    u8 pad22E[0x268-0x22E];
    f32 unk268;
    s32 pad26C;
    f32 unk270;
    u8 pad274[0x278-0x274];
    u16 unk278;
    u16 unk27A;
    u8 pad27C[0x288-0x27C];
    f32 unk288;
    u8 pad28C[0x29C-0x28C];
    f32 unk29C;
    u8 unk2A0[0x2C8-0x2A0];
    f32 unk2C8;
    f32 unk2CC;
    Mtx4F unk2D0;
} Unk8032F050; // size = unknown, at least 0x310

void func_8032F3DC(Unk8032F050*);
void func_8032F47C(Unk8032F050*);

#endif // APP_CODE_B6580_H
