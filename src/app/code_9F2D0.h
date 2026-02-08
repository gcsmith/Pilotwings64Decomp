#ifndef APP_CODE_9F2D0_H
#define APP_CODE_9F2D0_H

#include <uv_matrix.h>

typedef struct {
    u16 unk0; // Maybe some button mask?
    s16 pad2;
    s32 pad4;
    s8 unk8;
    s8 pad9[0xC - 9];
    s32 padC;
    f32 unk10;
    s32 pad14;
    f32 unk18;
    s32 pad1C;
    f32 unk20;
    f32 unk24;
    Mtx4F unk28;
    u8 pad68[0x70 - 0x68];
    f32 unk70;
    u8 pad74[0x80 - 0x74];
    f32 unk80;
    f32 unk84;
    f32 unk88;
    f32 unk8C;
    u8 pad90[0xC6C - 0x90];
    f32 unkC6C;
    f32 unkC70;
    s8 unkC74;
} HUDData;

HUDData* getHUDPtr(void);
void func_803182A0(void);
void func_8031D8E0(s32, s32, f32);

#endif // APP_CODE_9F2D0_H
