#ifndef APP_HUD_H
#define APP_HUD_H

#include <uv_matrix.h>

typedef struct {
    u16 unk0;
    s16 pad2;
    s32 unk4;
    s8 unk8;
    s8 pad9[0xC - 9];
    s32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    s32 pad1C;
    f32 unk20;
    f32 unk24;
    Mtx4F unk28;
    f32 unk68;
    f32 unk6C;
    f32 unk70;
    f32 unk74;
    f32 unk78;
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    f32 unk88;
    f32 unk8C;
    f32 unk90;
    u8 pad94[0xB38 - 0x94];
    f32 unkB38;
    f32 unkB3C;
    s16 unkB40[0x3C];
    f32 unkBB8;
    f32 unkBBC;
    f32 unkBC0;
    f32 unkBC4;
    f32 unkBC8;
    u8 unkBCC;
    u8 padBCD;
    s16 unkBCE;
    s16 unkBD0[0x3C];
    f32 unkC48;
    f32 unkC4C;
    f32 unkC50;
    f32 unkC54;
    f32 unkC58;
    u8 unkC5C;
    u8 padC5D;
    s16 unkC5E;
    u8 unkC60;
    u8 padC61[3];
    f32 unkC64;
    f32 unkC68;
    f32 unkC6C;
    f32 unkC70;
    s8 unkC74;
    u8 padC75[3];
    u8 showController;
} HUDState;

void hudInit(void);
HUDState* hudGetState(void);
void hudMainRender(void);
void hudText_8031D8E0(s16, f32, f32);
void hudWarningText(s16, f32, f32);
void hudDemoControllerEn(u8 enable);

#endif // APP_HUD_H
