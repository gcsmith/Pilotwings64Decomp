#ifndef APP_RINGS_H
#define APP_RINGS_H

#include <PR/ultratypes.h>
#include <uv_level.h>
#include <uv_matrix.h>

typedef struct {
    u8 pad0[0x1B4];
    u8 unk1B4;
    u8 pad1B5[0x1CC - 0x1B5];
} Unk8036DA78;

extern Unk8036DA78 D_8036DA78[];

void func_803232F0(void);
void func_80323364(void);
void func_803239B4(void);
s32 func_803243D8(Mtx4F*);
void func_80324A34(void);
u8 func_80324AF4(void);

#endif // APP_RINGS_H
