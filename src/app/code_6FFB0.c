#include <uv_graphics.h>

void func_802E92E4(void);
void func_802E94E0(void);
s32 fileSelectRender(void);
void func_802E9AE0(void);

s32 func_802E8A80(void) {
    s32 temp_v0;

    func_802E94E0();
    uvGfxBegin();
    func_802E9AE0();
    uvGfxEnd();
    do {
        uvGfxBegin();
        func_802E9AE0();
        uvGfxEnd();
        temp_v0 = fileSelectRender();
    } while (temp_v0 == -1);
    func_802E92E4();
    return temp_v0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_6FFB0/func_802E8AF0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_6FFB0/func_802E8FF4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_6FFB0/fileSelectSetup.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_6FFB0/func_802E92E4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_6FFB0/fileSelectPrintText.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_6FFB0/func_802E93E4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_6FFB0/fileSelectEraseFile.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_6FFB0/func_802E94E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_6FFB0/func_802E97A0.s")
