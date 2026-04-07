#ifndef APP_HANG_GLIDER_H
#define APP_HANG_GLIDER_H

#include <PR/ultratypes.h>
#include "game.h"

typedef struct {
    u8 pad0[0x6];
    u8 unk6;
    u8 pad7[0x80-0x7];
    Mtx4F unk80;
} HangGliderData_Unk50;

typedef struct {
    u16 objId;
    u8 unk2;
    u8 pad3[0x1];
    u16 unk4;
    u8 pad6[0x2];
    f32 unk8;
    u8 padC[0x4];
    Mtx4F unk10;
    HangGliderData_Unk50 *unk50;
    u8 pad54[0x5C - 0x54];
    u8 unk5C;
    u8 pad5D[3];
    f32 unk60;
    f32 unk64;
    f32 unk68;
    f32 unk6C;
    u8 pad70[0x80 - 0x70];
    u8 unk80;
    u8 pad81[0x88 - 0x81];
    f32 unk88;
    u8 unk8C;
    u8 unk8D;
    u8 unk8E;
    u8 pad8F[0x91 - 0x8F];
    u8 unk91[4];
    u8 unk95[4];
    u8 pad99[3];
    Vec3F unk9C[4];
    f32 unkCC[4];
    u8 padDC[0xE8 - 0xDC];
    u8 unkE8;
    u8 padE9[0xF0 - 0xE9];
    f32 unkF0;
    u8 padF4[4];
    f32 unkF8;
    u8 padFC[0x190 - 0xFC];
    f32 unk190;
    u8 pad194[0x1A4-0x194];
    Vec3F unk1A4;
    f32 unk1B0;
    u8 pad1B4[0x200 - 0x1B4];
    Vec3F unk200;
    f32 unk20C;
    s32 pad210;
    s32 pad214;
    s32 pad218;
    u8 unk21C;
    u8 pad21D;
    u8 pad21E;
    u8 pad21F;
    f32 unk220;
    f32 unk224;
    f32 unk228;
    f32 unk22C;
    f32 unk230;
    f32 unk234;
    f32 unk238;
    f32 unk23C;
    f32 unk240;
    s32 pad244;
    s32 pad248;
    s32 pad24C;
    u8 unk250;
    u8 unk251;
    u8 pad252[0x254 - 0x252];
    f32 unk254;
    u8 pad258[0x2DC - 0x258];
    f32 unk2DC;
    u16 unk2E0;
    u16 pad2E2;
    u8 unk2E4;
    u8 unk2E5;
    u8 unk2E6;
    u8 unk2E7;
    u8 pad2E8[0x2ED-0x2E8];
    u8 unk2ED;
    u8 unk2EE;
    u8 pad2EF[0x308-0x2EF];
    Vec3F unk308;
    s32 pad314;
    s32 unk318;
    s32 unk31C;
    u8 pad320[1];
    u8 unk321;
    u8 unk322;
    u8 unk323;
    f32 unk324;
    f32 unk328;
} HangGliderData;

void hangGliderInit(void);
void func_802EEB00(HangGliderData*, u8);
void func_802EF238(u8 contIdx, u8 pilot, HangGliderData* arg2, Camera* arg3);
void func_802EF328(HangGliderData*);
void hangGliderEnterLeave(HangGliderData*);
void hangGliderMovementFrame(HangGliderData*, u8);
void func_802F03C4(HangGliderData*);
void func_802F041C(HangGliderData*);

#endif // APP_HANG_GLIDER_H
