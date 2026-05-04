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

void uvChanInit(void);
void uvChan_80204A8C(s32 arg0, s32 arg1);
void uvChan_80204AB0(s32 arg0, s32 arg1, void (*arg2)(void));
void uvChan_80204B08(s32 arg0, s32 arg1, s32 arg2);
void uvChan_80204B34(s32 arg0, Mtx4F* arg1);
void uvChan_80204BD4(s32 arg0, s32 arg1, f32 arg2);
void uvChan_80204C54(s32 arg0, Mtx4F *arg1);
void uvChan_80204C94(s32, f32, f32, f32, f32, f32, f32);
void uvChan_80204D94(s32 vpId, s32 x0, s32 x1, s32 y0, s32 y1);
void uvChanEnv(s32 arg0, s32 arg1);
void uvChanTerra(s32, s32);
s32  uvChan_80204EC0(s32, f32, f32, f32, f32);
u8*  uvChan_80204F9C(s32 arg0);
void uvChan_80204FC4(s32 arg0);
void uvChan_80204FE4(s32 arg0);
void uvChan_80205724(s32, s32, Mtx4F*);
void uvChan_802057F4(Mtx4F *arg0, Mtx4F *arg1);
void _uvSortAdd(s32, f32, void*, UnkStruct_80204D94*, f32, f32, ...);
void uvChan_80205BFC(void);
void uvChan_80205CE4(UnkStruct_80204D94*, s32, f32, f32);

#endif // PILOTWINGS64_UV_CHAN_H

