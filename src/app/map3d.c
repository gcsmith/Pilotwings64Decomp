#include <uv_graphics.h>
#include "demo.h"

s32 D_8034F7F0 = 0xFFFF0000;
s32 D_8034F7F4 = 0;
u16 D_8034F7F8[2] = { 0 };
f32 D_8034F7FC = 0.0f;
f32 D_8034F800 = 0.0f;
f32 D_8034F804 = 0.0f;
f32 D_8034F808 = 0.0f;
f32 D_8034F80C = 0.6603981256f;
f32 D_8034F810 = 0.6603981256f;
f32 D_8034F814 = 0.0f;
f32 D_8034F818 = 0.0f;
f32 D_8034F81C = 0.0f;
f32 D_8034F820 = 0.0f;
f32 D_8034F824 = 0.0f;
f32 D_8034F828 = 0.0f;
f32 D_8034F82C = 0.0f;
f32 D_8034F830 = 0.0f;
f32 D_8034F834 = 0.0f;
f32 D_8034F838 = 0.0f;
u8 D_8034F83C = 0;

void func_8022E2D4(s32);
void func_802EB9C0(void);
void func_802EBC30(void);
s32 func_80311660(s32, s32);
void func_80311C68(s32, s32);
void func_803122B4(s32, s32);
void uvGfxEnableGamma(s32);
void uvSysInit(s32);
void map3d(void);

void app_entrypoint(void) {
    uvSysInit(0);
    uvGfxEnableGamma(0);
    func_802EB9C0();
    while (demo_80323020() != 0) {
        func_802EBC30();
    }
    func_8022E2D4(0);
}

void func_8030FE80(s32 arg0, s32 arg1) {
    map3d();
    while (func_80311660(0, arg1) != 0) {
        uvGfxBegin();
        func_80311C68(arg0, arg1);
        uvGfxEnd();
    }
    func_803122B4(arg0, arg1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/map3d/map3d.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/map3d/func_80311660.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/map3d/func_80311C68.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/map3d/func_803122B4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/map3d/func_803123C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/map3d/func_80312514.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/map3d/map3d_mslot.s")
