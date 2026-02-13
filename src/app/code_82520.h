#ifndef APP_CODE_82520_H
#define APP_CODE_82520_H

#include <PR/ultratypes.h>

typedef struct {
    void* unk0;
    u8 pad1[2];
    u8 unk6;
    u8 pad7[0x11];
} Unk80368B80;

extern u8 D_8034F3A0;
extern Unk80368B80 D_80368B80[];

void func_802FAFF0(void);
void func_802FB0DC(Unk80368B80*);
void func_802FB22C(void);
s32 func_802FB308(s32);
void func_802FB518(void);
u8 func_802FB5A0(void);

#endif // APP_CODE_82520_H
