#ifndef APP_CODE_CB7C0_H
#define APP_CODE_CB7C0_H

#include <uv_level.h>

typedef struct {
    u8 pad0[0x46];
    u8 unk46;
    u8 pad47[0x4C - 0x47];
} Unk80378CF8;

extern Unk80378CF8 D_80378CF8[];

void func_80344290(void);
void func_803442F8(void);
void func_8034450C(Unk80345464_Arg0*);
void func_8034467C(void);
u8 func_803448F4(void);

#endif // APP_CODE_CB7C0_H
