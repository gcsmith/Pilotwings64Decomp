#ifndef PILOTWINGS64_UV_CHAN_H
#define PILOTWINGS64_UV_CHAN_H

#include <uv_common.h>
#include <uv_graphics.h>

typedef struct UnkSortAdd {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    void* unk10; // Unk80263780*, UnkFxStruct* or UnkSobjDraw*
    u16 unk14;
    Mtx4F* unk18;
} UnkSortAdd;

extern u8 D_80263060[];

void func_80205BFC(void);
void func_80205CE4(UnkStruct_80204D94*, s32, f32, f32);
void _uvSortAdd(s32, f32, void*, UnkStruct_80204D94*, f32, f32, ...);

#endif // PILOTWINGS64_UV_CHAN_H

