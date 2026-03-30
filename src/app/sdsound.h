#ifndef APP_SDSOUND_H
#define APP_SDSOUND_H

#include <PR/ultratypes.h>
#include <uv_vector.h>

typedef struct {
    u8 pad0[0x70];
    u8 unk70;
    u8 unk71;
    u8 unk72;
    u8 unk73[3];
    u8 unk76[3];
    u8 pad79[0x7C - 0x79];
    Vec3F unk7C[3];
    f32 unkA0[3];
    u8 padAC[0xB8 - 0xAC];
    u8 unkB8;
    u8 padB9[0x160 - 0xB9];
    Vec3F unk160;
    u8 pad16C[0x240 - 0x16C];
    s32 unk240;
    u8 unk244;
    u8 unk245;
    u16 pad246;
    f32 unk248;
    u8 pad24C[0x25E - 0x24C];
    u16 unk25E;
    u8 pad260[0x2CC - 0x260];
    f32 unk2CC;
} UnkSdSound;

void sdsound_803338B0(UnkSdSound* arg0);

#endif // APP_SDSOUND_H
