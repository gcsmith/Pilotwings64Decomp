#ifndef APP_HANG_GLIDER_H
#define APP_HANG_GLIDER_H

#include <PR/ultratypes.h>
#include "game.h"

typedef struct {
    u16 objId;
    u8 unk2;
    u8 pad3[0x1];
    u16 unk4;
    u8 pad6[0x2];
    f32 unk8;
    u8 padC[0x4];
    Mtx4F unk10;
    u8 pad50[0x3C];
    u8 unk8C;
    u8 unk8D;
    u8 pad8E[0x5A];
    u8 unkE8;
    u8 padE9[0xC7];
    f32 unk1B0;
    u8 pad1B4[0x154];
    Vec3F unk308;
    u8 pad314[0x18];
} HangGliderData;

void hangGliderInit(void);
void func_802EEB00(HangGliderData*, u8);
void func_802EF238(u8 contIdx, u8 pilot, HangGliderData* arg2, Unk802D3658_Arg0* arg3);
void func_802EF328(HangGliderData*);
void hangGliderEnterLeave(HangGliderData*);
void hangGliderMovementFrame(HangGliderData*, u8);
void func_802F03C4(HangGliderData*);
void func_802F041C(HangGliderData*);

#endif // APP_HANG_GLIDER_H
