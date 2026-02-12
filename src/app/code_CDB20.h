#ifndef APP_CODE_CDB20_H
#define APP_CODE_CDB20_H

#include <PR/ultratypes.h>

typedef struct {
    u8 pad0[4];
    f32 unk4;
    f32 unk8;
    f32 unkC;
    u8 pad10[4];
    f32 unk14;
} Unk8037AB58;

extern u8 D_8037AB54; // count of D_8037AB58, related to objects shown on radar
extern Unk8037AB58 D_8037AB58[]; // rings?

void func_803465F0(void);
void func_8034662C(void);
void func_8034695C(void);
void func_80346B84(void);

#endif // APP_CODE_CDB20_H
