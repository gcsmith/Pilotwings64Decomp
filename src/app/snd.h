#ifndef APP_SND_H
#define APP_SND_H

#include <PR/ultratypes.h>
#include <uv_matrix.h>

extern u16 D_803505B0;

void sndInit(void);
void func_8033F6F8(Mtx4F*, Mtx4F*);
void func_8033F748(u16);
void func_8033F758(u8, f32, f32, f32);
void sndPlaySfx(u8);
u8 sndMakeDev(s32);
u8 func_8033F8CC(u8);
void func_8033F904(u8, f32, f32, f32);
void func_8033F964(s32);
void func_8033FA88(f32);
void func_8033FAD4(f32);
void func_8033FB14(void);
void sndGetPilot(s32*, f32*);
void func_8033FCD0(u16);
void func_8033FA88(f32);
void func_8033FD94(s32, f32, f32);

#endif // APP_SND_H
