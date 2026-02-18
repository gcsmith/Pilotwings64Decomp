#include "common.h"
#include <uv_janim.h>
#include <uv_matrix.h>
#include <uv_model.h>

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/janim/uvJanimLoad.s")

void func_80200638(s32 arg0, Unk80371120* arg1) {
    Mtx4F sp58;
    s32 temp_s4;
    s32 i;
    s32 temp_s5;
    Unk8022B0A0* var_s1;

    temp_s4 = arg1->unk1AC;
    temp_s5 = D_80263780[arg0].unk0;
    var_s1 = arg1->unk0;

    for (i = 0; i < temp_s4; i++, var_s1++) {
        uvModelGetPosm(temp_s5, arg1->unk190[i], &sp58);
        uvMat4SetUnk4(&sp58, var_s1->unk0, var_s1->unk4, var_s1->unk8, var_s1->unkC);
        uvDobjPosm(arg0, arg1->unk190[i], &sp58);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/janim/func_802006FC.s")

void func_80200B00(s32 arg0, s32 arg1, f32 arg2) {
    Unk80371120 sp18;

    uvJanimPoseLine(&sp18, arg1, arg2);
    func_80200638(arg0, &sp18);
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/janim/uvJanimPoseLine.s")

void func_80200EC0(s32 arg0, s32 arg1, f32 arg2, f32 arg3) {
    Unk80371120 sp18;

    uvJanimPoseGrid(&sp18, arg1, arg2, arg3);
    func_80200638(arg0, &sp18);
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/janim/uvJanimPoseGrid.s")
