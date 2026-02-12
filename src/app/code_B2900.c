#include "common.h"
#include <uv_level.h>
#include "code_52230.h"
#include "code_59D80.h"
#include "code_6ACE0.h"
#include "code_82520.h"
#include "code_915B0.h"
#include "code_B2900.h"
#include "code_CB7C0.h"
#include "rings.h"

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_B2900/func_8032B3D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_B2900/func_8032B508.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_B2900/func_8032B560.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_B2900/func_8032BD20.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_B2900/func_8032BE10.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_B2900/func_8032BE1C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_B2900/func_8032BE8C.s")

u8 func_8032BF54(void) {
    void* tmp;

    tmp = NULL;
    if (levelGet_80346364() != 2) {
        return 0;
    }
    return (func_80324AF4() != levelDataGetRNGS(&tmp) || func_803448F4() != levelDataGetTARG(&tmp) || func_802CC15C() == 0 ||
            func_8030A080() != levelDataGetHPAD(&tmp) || func_802E57C4() != D_8035A5F0 || func_802D30B4() != levelDataGetBTGT((LevelBTGT**)&tmp) ||
            func_802FB5A0() != levelDataGetHOPD((LevelHOPD**)&tmp));
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_B2900/func_8032C080.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_B2900/func_8032C174.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_B2900/func_8032C27C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_B2900/func_8032C3C4.s")
