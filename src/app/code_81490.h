#ifndef APP_CODE_81490_H
#define APP_CODE_81490_H

#include <PR/ultratypes.h>
#include <uv_matrix.h>

typedef struct {
    u16 unk0;
    u8 unk2;
    u8 unk3[0x74-0x3];
    Mtx4F unk74;
} JumbleHopperData;

void func_802FAF80(void);
void jumbleHopperEnterLeave(JumbleHopperData*);
void jumbleHopperMovementFrame(JumbleHopperData*, u8);

#endif // APP_CODE_81490_H
