#ifndef APP_BALLS_H
#define APP_BALLS_H

#include <PR/ultratypes.h>

typedef struct {
    u8 pad0[0x94];
    u8 unk94;
    u8 pad95[0x1AC - 0x95];
} Unk80357218;

extern u8 D_80357210;
extern u8 D_80357211;
extern Unk80357218 D_80357218[];

void func_802CAD00(void);
void func_802CAF50(void);
void func_802CB094(void);
void func_802CB35C(void);
void func_802CB3F8(void);
u8 func_802CC15C(void);

#endif // APP_BALLS_H
