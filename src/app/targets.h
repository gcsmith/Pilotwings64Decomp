#ifndef APP_TARGETS_H
#define APP_TARGETS_H

#include <PR/ultratypes.h>
#include <uv_level.h>
#include <uv_matrix.h>

typedef struct {
    u16 unk0; // alloc index?
    u8 pad2[0x4-0x2];
    Mtx4F unk4;
    u8 unk44;
    u8 unk45;
    u8 unk46;
    u8 unk47;
    u8 unk48;
    u8 pad49[0x4C - 0x49];
} Unk80378CF8; // size = 0x4C

extern Unk80378CF8 D_80378CF8[40];

void func_80344290(void);
void func_803442F8(void);
void func_8034450C(Mtx4F*);
void func_8034467C(void);
u8 func_803448F4(void);
f32 func_8034473C(s32, s32);
s16 func_80344948(void);

#endif // APP_TARGETS_H
