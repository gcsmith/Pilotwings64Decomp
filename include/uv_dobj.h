#ifndef UV_DOBJ_H
#define UV_DOBJ_H

#include <PR/ultratypes.h>

// size: 0x40
typedef struct {
    u16 unk0;
    u8 pad2[0x34-0x2];
    s8 unk34;
    f32 unk38;
    s32 unk3C;
} Unk80263780;

extern Unk80263780 D_80263780[8];

u16 func_8021731C(void);
void uvDobjModel(s32, s32);
void uvDobjPosm(u16, s32, void*);
void uvDobjState(s32, s32);
void uvDobjProps(s32 arg0, ...);

#endif // UV_DOBJ_H
