#ifndef APP_CODE_D19D0_H
#define APP_CODE_D19D0_H

#include <PR/ultratypes.h>
#include <uv_vector.h>
#include "code_A6000.h"

// size: 0x2DC
// it's possible unk190 is part of a different struct, will have to adjust func_8034A950 if so
typedef struct {
    Vec4F unk0;
    u8 pad10[0x190-0x10];
    Vec3F unk190;
    u8 pad[0x2DC-0x19C];
} Unk8034A950;

extern Unk8037DCA0 D_8037DCA0[6];
extern s32 D_8037F098; // size of 0x2E8, might be array


Unk8037DCA0* func_8034A4F8(s32 arg0);
void func_8034A840(s32 path);
void func_8034A8B0(Unk8037DCA0* arg0, u8 arg1, f32 arg2);
// arg0 is the actual struct and not a pointer to it
void func_8034A950(Unk8034A950 arg0, f32* arg183);

#endif // APP_CODE_D19D0_H
