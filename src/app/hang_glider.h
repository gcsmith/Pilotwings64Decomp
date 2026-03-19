#ifndef APP_HANG_GLIDER_H
#define APP_HANG_GLIDER_H

#include <PR/ultratypes.h>
#include "code_72EF0.h"

typedef struct {
    u16 objId;
    u8 unk2;
    u8 pad3[0xD];
    Mtx4F unk10;
    u8 pad50[0x2DC];
} HangGliderData;

void hangGliderEnterLeave(HangGliderData*);
void hangGliderMovementFrame(HangGliderData*, u8);

#endif // APP_HANG_GLIDER_H
