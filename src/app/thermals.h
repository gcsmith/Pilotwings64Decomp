#ifndef APP_THERMALS_H
#define APP_THERMALS_H

#include <PR/ultratypes.h>
#include <uv_vector.h>

typedef struct {
    u16 unk0;
    u8 pad2[2];
    Vec3F pos;
    f32 height;
    f32 scale;
} Thermal;

extern u8 gThermalCount; // count of gThermals
extern Thermal gThermals[16]; // parsed thermal data, also parts copied to HUD

void func_803465F0(void);
void func_8034662C(void);
void func_8034695C(void);
void func_80346B84(void);

#endif // APP_THERMALS_H
