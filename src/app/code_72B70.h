#ifndef APP_CODE_72B70_H
#define APP_CODE_72B70_H

#include <uv_level.h>
#include <uv_matrix.h>

typedef struct {
    u8 testCount;
    u8 pad1[0x157];
} Unk80367710;

void func_802EB9C0(void);
void func_802EBC30(void);
void func_802EDDEC(Mtx4F*);
void func_802EDAF0(void*, Mtx4F*, s32, s32, f32, f32, f32, u32, s32, s32, s32);

#endif // APP_CODE_72B70_H
