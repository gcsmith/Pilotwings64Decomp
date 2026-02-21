#ifndef UV_DOBJ_H
#define UV_DOBJ_H

#include <PR/ultratypes.h>
#include <uv_graphics.h>
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

void uvDobjModel(s32 objId, s32 mdlId);
void uvDobjProps(s32 objId, ...);
void uvDobjPosm(s32 objId, s32 part, Mtx4F* src);
void uvDobjGetPosm(s32 objId, s32, Mtx4F* dst);
void uvDobjState(s32, s32);
void uvDobjSetState(s32 objId, s32 flags);
void uvDobjClearState(s32 objId, s32 flags);
s32 uvDobjAllocIdx(void);
void uvDobjInit(void);
void uvDobj_8021771C(UnkStruct_80204D94*);
u8 uvDobj_80217AB4(uvGfxUnkStructModel*, f32);
s32 uvDobj_80217B34(s32**);
void uvDobj_80217B4C(Unk80263780*, uvGfxUnkStructModel*, u8);
void uvDobj_80217E24(Unk80263780*, uvGfxUnkStructModel*, u8, f32, f32);
void uvDobj_802180DC(s32, Unk80371120*);

#endif // UV_DOBJ_H
