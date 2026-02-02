#include "common.h"
#include <uv_matrix.h>
#include "code_72010.h"

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_72010/func_802EAAE0.s")

void func_802EABAC(Unk802D3658_Unk230* arg0, f32 arg1, Mtx4F* arg2) {
    Unk802D3658_Unk230* var_s0;
    s32 var_s1;

    var_s0 = arg0;
    for (var_s1 = 0; var_s1 < 50; var_s1++) {
        uvMat4Copy(&var_s0->unk0, arg2);
        var_s0->unk40 = arg1;
        var_s0 = var_s0->unk44;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_72010/func_802EAC18.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_72010/func_802EAC9C.s")
