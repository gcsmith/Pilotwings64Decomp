#ifndef APP_RINGS_H
#define APP_RINGS_H

#include <PR/ultratypes.h>
#include <uv_matrix.h>

typedef struct {
    u16 unk0;
    u8 pad2[2];
    Mtx4F unk4;
    Mtx4F unk44;
    Mtx4F unk84;
    u8 padC4[0x144 - 0xC4];
    u8 unk144;
    u8 unk145;
    u8 unk146;
    u8 unk147;
    u8 unk148;
    u8 unk149;
    u8 pad14A[2];
    s32 unk14C[5]; // TODO: size
    u8 unk160;
    u8 pad161[3];
    s32 unk164[5]; // TODO: size
    u8 unk178;
    u8 pad179[3];
    f32 unk17C;
    f32 unk180;
    u8 unk184;
    u8 pad185[3];
    f32 unk188;
    f32 unk18C;
    u8 unk190;
    u8 pad191[3];
    f32 unk194;
    f32 unk198;
    f32 unk19C;
    u8 unk1A0;
    u8 pad1A1[3];
    f32 unk1A4;
    f32 unk1A8;
    f32 unk1AC;
    f32 unk1B0;
    u8 unk1B4;
    u8 unk1B5;
    u8 pad1B6[1];
    u8 unk1B7;
    u8 unk1B8;
    u8 unk1B9;
    u8 unk1BA;
    char unk1BB[0xF]; // TODO: size?
    u8 unk1CA;
    u8 pad1CB[1];
} ParsedRing; // size = 0x1CC

extern ParsedRing D_8036DA78[30];

void ringsInit(void);
void func_80323364(void);
void ringsLoad(void);
s32 func_803243D8(Mtx4F*);
void ringsDeinit(void);
u8 func_80324AF4(void);
s16 func_80324B60(void*);

#endif // APP_RINGS_H
