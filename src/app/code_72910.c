#include "common.h"

s16 D_8034F150[8] = { 0 };

extern func_802E9FD0();                                  /* extern */
extern func_80314430();                                  /* extern */
extern func_803365A0();                                  /* extern */
extern func_80341CB0();                                  /* extern */
extern s8 D_80359DB4;

void func_802EB3E0(void) {
    func_802E9FD0();
    func_80341CB0();
    func_803365A0();
    func_80314430();
    *D_8034F150 = 0;
    D_80359DB4 = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_72910/func_802EB424.s")

void func_802EB598(void) {
    void* sp1C;

    sp1C = levelGet_80345CB0();
    fx_create();
    smoke_create_terra();
    if (((u8*)sp1C)[1] == 1) {
        func_803405C0();
    }
}

void func_802EB5E4(void) {
    void* sp1C;

    sp1C = levelGet_80345CB0();
    func_802EA824();
    func_80341E30();
    func_80337114();
    func_80314AE0();

    if (((u8*)sp1C)[1] == 1) {
        func_803405E4();
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_72910/D_80352300.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_72910/D_80352308.s")
