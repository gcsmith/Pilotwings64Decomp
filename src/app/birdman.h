#ifndef APP_BIRDMAN_H
#define APP_BIRDMAN_H

#include "code_72B70.h"

typedef struct {
    u16 objId;
    u8 pad2[0xA];
    u16 unkC;
} Unk802CC51C;

void bird_802CC1B0(void);
void bird_802CC270(u8, u8 pilot, Unk80367704*, Unk802D3658_Arg0*);
void bird_802CC39C(Unk80367704*);
void bird_802CC51C(Unk802CC51C*);
void bird_802CC55C(Unk80367704*, u8);
void bird_802CD0F8(Unk80367704*);
void bird_802CE190(Unk80367704*, u8);
void bird_802CEA60(Unk80367704*);
void bird_802CEBA0(Unk80367704*);
void bird_802CECB8(Unk80367704*);
void bird_802CEDF8(Unk80367704*);

#endif // APP_BIRDMAN_H
