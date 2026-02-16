#ifndef UV_DOBJ_H
#define UV_DOBJ_H

#include <PR/ultratypes.h>
#include <uv_matrix.h>

// size: 0x40
typedef struct {
    u16 unk0;
    u16 unk2[1]; // unknown size, might take up everything till unk34
    u8 pad4[0x34-0x4];
    s8 unk34;
    f32 unk38;
    s32 unk3C;
} Unk80263780;

extern Unk80263780 D_80263780[100];

s32 func_8021731C(void);
// arg1 might be the model id? 0xFFFF / -1 is..?
void uvDobjModel(s32, s32);
void uvDobjPosm(s32, s32, Mtx4F*);
void uvDobjState(s32, s32);
void uvDobjProps(s32 arg0, ...);
void uvDobjGetPosm(s32, s32, Mtx4F*);

#endif // UV_DOBJ_H
