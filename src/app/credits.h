#ifndef APP_CREDITS_H
#define APP_CREDITS_H

#include <PR/ultratypes.h>

extern u8 D_8034F420[][4];
extern u8 D_8034F43C[];
extern s32 D_8036A8B0;

s32  credits_8030CB60(s32);
s32  credits_8030CC48(void);
s32  creditsMainRender(void);
void credits_8030CDA0(s32);
void credits_8030D1D4(void);
s32  credits_8030D208(void);
void creditsScene(void);

#endif //  APP_CREDITS_H
