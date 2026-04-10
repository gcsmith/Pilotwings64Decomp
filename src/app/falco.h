#ifndef APP_FALCO_H
#define APP_FALCO_H

#include <PR/ultratypes.h>
#include <uv_matrix.h>
#include <uv_vector.h>
#include "app/task.h"

typedef struct {
    Vec3F unk0;
    f32 unkC;
} FalcoDomain;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    FalcoDomain* domain;
    u8 pad14[0x80 - 0x14];
    f32 unk80;
    f32 unk84;
    f32 unk88;
    Vec3F unk8C;
    f32 unk98;
    Vec3F unk9C;
    Vec3F unkA8;
    Vec3F unkB4;
    u8 padC0[4];
    f32 unkC4;
    f32 unkC8;
    f32 unkCC;
    f32 unkD0;
    f32 unkD4;
    f32 unkD8;
    f32 unkDC;
    f32 unkE0;
    f32 unkE4;
    f32 unkE8;
    f32 unkEC;
    f32 unkF0;
    f32 unkF4;
    f32 unkF8;
    f32 unkFC;
    f32 unk100;
    f32 unk104;
    f32 unk108;
    f32 unk10C;
    f32 unk110;
    f32 unk114;
    f32 unk118;
    f32 unk11C;
    f32 unk120;
    f32 unk124;
    f32 unk128;
    f32 unk12C;
    f32 unk130;
    f32 unk134;
    f32 unk138;
    f32 unk13C;
    f32 unk140;
    f32 unk144;
    f32 unk148;
    f32 unk14C;
    f32 unk150;
    f32 unk154;
    f32 unk158;
    f32 unk15C;
    f32 unk160;
    f32 unk164;
    f32 unk168;
    Mtx4F unk16C;
    Mtx4F unk1AC;
    Mtx4F unk1EC;
    s32 pad22C;
    Vec3F unk230;
    s32 unk23C;
    s32 unk240;
    f32 unk244;
    s32 unk248;
    s32 unk24C;
    f32 unk250;
    u8 unk254;
    u8 unk255;
    u8 unk256;
    u8 pad257[1];
} Falco; // size = 0x258

typedef struct {
    s32 unk0;
    s32 radarIdx; // maybe u8
    Mtx4F unk8;
    Vec3F unk48;
    f32 unk54;
    f32 unk58;
    u8 pad5C;
    u8 unk5D;
    u8 pad5E;
    u8 pad5F;
} Unk8035A920; // size = 0x60

extern s32 D_8035A5F0;
extern Falco sFalcos[1];
extern s32 sFalcoCount;
extern FalcoDomain sFalcoDomains[12];
extern s32 D_8035A918;
extern Unk8035A920 D_8035A920[16];
extern TaskFALC* sRefFALC;

void falcoInit(void);
void falcoLoad(void);
void falcoDeinit(void);
void falcoFrameUpdate(void);
s32 falco_802E51E8(s32, f32, f32, f32);
s32 falco_802E57C4(void);
s32 falco_802E5818(void);
void falco_802E64E0(s32, Mtx4F*);

#endif // APP_FALCO_H
