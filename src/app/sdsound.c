#include "common.h"
#include "demo.h"
#include "snd.h"
#include <uv_event.h>

typedef struct {
    u8 pad0[0x160];
    Vec3F unk160;
    u8 pad16C[0x240 - 0x16C];
    s32 unk240;
    u8 unk244;
    u8 unk245;
    u16 pad246;
    f32 unk248;
} UnkSdSound;

// .bss
extern EventCallbackInfo D_80371CB0;

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
} Unk80371CB8; // size = 0x50 - 0x58
extern Unk80371CB8 D_80371CB8;

// foward declarations
void func_803339C4(s32, void*, s32);

void func_803338B0(UnkSdSound* arg0) {
    arg0->unk248 = 0.0f;
    D_80371CB8.unk0 = 4;
    D_80371CB8.unk4 = 0 /*.0f*/;
    D_80371CB8.unk8 = 0.0f;
    D_80371CB8.unkC = 0.01f;
    D_80371CB8.unk10 = 0.4f;
    D_80371CB8.unk14 = 9.0f;
    D_80371CB8.unk18 = 0.8f;
    D_80371CB8.unk1C = 10.0f;
    D_80371CB8.unk20 = 1.0f;
    arg0->unk244 = snd_makedev(0x13);
    arg0->unk245 = snd_makedev(0x13);
    D_80371CB0.cb = &func_803339C4;
    D_80371CB0.arg = arg0;
    arg0->unk240 = -0x40;
    uvEventMaxCb(D_80371CB0, 1, 0xD, 0x12, 0x13, 0x10, 0xC, 0x16, 0x24);
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/sdsound/func_803339C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/sdsound/func_80333D80.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/sdsound/func_80333DDC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/sdsound/func_80333DF0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/sdsound/func_80333F68.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/sdsound/func_80334258.s")
