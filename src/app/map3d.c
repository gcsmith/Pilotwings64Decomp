#include <uv_graphics.h>

void func_8022E2D4(s32);
void func_802EB9C0(void);
void func_802EBC30(void);
s32 func_80311660(s32, s32);
void func_80311C68(s32, s32);
void func_803122B4(s32, s32);
s32 func_80323020(void);
void uvGfxEnableGamma(s32);
void uvSysInit(s32);
void map3d(void);

void app_entrypoint(void) {
    uvSysInit(0);
    uvGfxEnableGamma(0);
    func_802EB9C0();
    while (func_80323020() != 0) {
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
