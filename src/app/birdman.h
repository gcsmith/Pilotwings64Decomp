#ifndef APP_BIRDMAN_H
#define APP_BIRDMAN_H

#include "code_72B70.h"

typedef struct {
    u16 objId;
    u8 pad2[0xA];
    u16 unkC;
} Unk802CC51C;

void bird_802CC1B0(void);
void bird_802CC270(u8, u8 pilot, VehicleData*, Unk802D3658_Arg0*);
void birdEnterLeave(VehicleData*);
void bird_802CC51C(Unk802CC51C*);
void birdMovementFrame(VehicleData*, u8);
void bird_802CD0F8(VehicleData*);
void bird_802CE190(VehicleData*, u8);
void bird_802CEA60(VehicleData*);
void bird_802CEBA0(VehicleData*);
void bird_802CECB8(VehicleData*);
void bird_802CEDF8(VehicleData*);

#endif // APP_BIRDMAN_H
