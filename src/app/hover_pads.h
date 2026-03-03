#ifndef APP_HOVER_PADS_H
#define APP_HOVER_PADS_H

#include <PR/ultratypes.h>

typedef struct {
    u8 pad0[0x68];
    u8 unk68;
    u8 pad69[0x70 - 0x69];
} Unk80369588;

extern u8 D_80369584;
extern Unk80369588 D_80369588[];

u8 func_8030A080(void);

#endif // APP_HOVER_PADS_H
