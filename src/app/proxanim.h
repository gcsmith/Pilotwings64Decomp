#ifndef APP_PROXANIM_H
#define APP_PROXANIM_H

#include <PR/ultratypes.h>
#include <uv_vector.h>

typedef struct {
    u8 pad0[0x14];
    s32 unk14;
} Unk803216A4; // size = unknown, >= 0x18

void func_80321100(void);
s32 func_80321210(s32 (*)(s32, s32, s32), s32 (*)(s32, s32, s32), Vec3F, f32, f32, s32);
void func_803212DC(s32);
f32 func_80321420(s32);
void func_8032150C(void);
Unk803216A4* func_803216A4(void);
void func_803213E0(void);
void func_80321400(void);
void func_803214E4(void);

#endif // APP_PROXANIM_H
