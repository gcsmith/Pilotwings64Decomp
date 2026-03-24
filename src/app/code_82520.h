#ifndef APP_CODE_82520_H
#define APP_CODE_82520_H

#include <PR/ultratypes.h>
#include "jumble_hopper.h"
#include "task.h"

typedef struct {
    TaskHOPD* unk0;
    u16 objId;
    u8 unk6;
    u8 unk7;
    s32 unk8;
    u8 padC[0x4];
    f64 unk10;
} Unk80368B80;

extern u8 D_8034F3A0;
extern Unk80368B80 D_80368B80[];

void func_802FAFF0(void);
void func_802FB0DC(Unk80368B80*);
void func_802FB22C(void);
s32 func_802FB308(JumbleHopperData*);
void func_802FB518(void);
u8 func_802FB5A0(void);
s16 func_802FB5FC(void);

#endif // APP_CODE_82520_H
