#ifndef APP_SNAP_H
#define APP_SNAP_H

#include <PR/ultratypes.h>
#include "game.h"

#define PHOTO_COUNT_MAX 6

typedef struct Unk8033F050 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u8 unk6;
    u8 unk7;
    u8 unk8;
    u32 unk9_0 : 2;
    u32 unk9_2 : 2;
    u32 unk9_4 : 4;
    u32 unk9_8 : 4;
    u32 unk9_12 : 4;
    u32 unk9_16 : 4;
    u32 unk9_20 : 4;
    u8 unkC;
    u8 unkD;
    u8 unkE;
    u8 unkF;
    u8 unk10;
    u8 unk11;
    u32 unk12_0 : 4;
    u32 unk12_4 : 3;
    u32 unk12_7 : 3;
    u32 unk12_10 : 3;
    u32 unk12_13 : 3;
    u32 unk12_16 : 3;
    u32 unk12_19 : 3;
    u32 unk12_22 : 3;
    u32 unk12_25 : 3;
} Unk8033F050; // size = 0x18

void func_80337D50(void);
void snapInit(void);
void snapDeinit(void);
void func_80339C8C(HangGliderData*);
void func_80339E1C(BirdmanData*);
s32 func_8033E3A8(s32);
void func_8033E860(Unk8033F050**);
void func_8033F050(void*);
s32 func_8033F62C(void);
s32 snapGetPhotoCount(void);
s32 func_80338614(void);

#endif // APP_SNAP_H
