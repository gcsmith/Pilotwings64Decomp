#ifndef APP_ENVIRONMENT_H
#define APP_ENVIRONMENT_H

#include <PR/ultratypes.h>
#include <uv_vector.h>

extern u8 D_80359DB4; // 0x00 = day, 0x01 = night

void envInit(void);
void envLoadTerrainPal(s32);
void envLoad(void);
s32 env_802E0CF0(void);
s32 envGetCurrentId(void);
void env_802E1444(s32);
void env_802E14E8(Vec3F*, f32, f32, f32, f32);
void env_802E15F0(void);
void env_802E1754(f32, f32, f32, Vec3F*);
void env_802E2060(void);

#endif // APP_ENVIRONMENT_H
