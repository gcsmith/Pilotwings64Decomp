#ifndef UV_DOBJ_H
#define UV_DOBJ_H

#include <PR/ultratypes.h>
#include <uv_matrix.h>
#include <uv_sched.h>

// size: 0x40
typedef struct {
    u16 unk0;
    u16 unk2[1]; // unknown size, might take up everything till unk34
    u8 pad4[0x34-0x4];
    u8 unk34;
    f32 unk38;
    s32 unk3C;
} Unk80263780;

typedef struct Unk80371120 {
    Unk8022B0A0 unk0[1];
    u8 pad10[0x180];
    u8 unk190[1];
    u8 pad191[0x1B];
    s32 unk1AC;
} Unk80371120; // size: 0x1B0

extern Unk80263780 D_80263780[100];

s32 func_8021731C(void);
// arg1 might be the model id? 0xFFFF / -1 is..?
void uvDobjModel(s32, s32);
void uvDobjPosm(s32, s32, Mtx4F*);
void uvDobjState(s32, s32);
void uvDobjProps(s32 arg0, ...);
void uvDobjGetPosm(s32, s32, Mtx4F*);

#endif // UV_DOBJ_H
