#include "common.h"
#include <uv_level.h>
#include "code_52230.h"
#include "code_59D80.h"
#include "code_6ACE0.h"
#include "code_82520.h"
#include "code_915B0.h"
#include "code_94E60.h"
#include "code_B2900.h"
#include "code_CB7C0.h"
#include "rings.h"

s32 D_8034FBD0 = 0;
u16 D_8034FBD4[][3] = {
    { 0x0046, 0x0050, 0x005A },
    { 0x008C, 0x00A0, 0x00B4 },
    { 0x00D2, 0x00F0, 0x010E },
    { 0x00D2, 0x00F0, 0x010E },
    { 0x0046, 0x0050, 0x005A },
    { 0x0046, 0x0050, 0x005A },
    { 0x0046, 0x0050, 0x005A },
    { 0x0000, 0x0000, 0x0000 },
    { 0x0000, 0x0000, 0x0000 },
    { 0x0000, 0x0000, 0x0000 }
};

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

s32 func_8032C174(s32* arg0, u16 arg1, u8 arg2) {
    Unk80362690_Unk0_UnkC* unkC;
    s32 i;
    u16 val;

    unkC = &D_80362690->unk0[D_80362690->unk9C].unkC;

    for (i = 0; i < 3; i++) {
        val = D_8034FBD4[arg2][i];
        if (val > arg1) {
            break;
        }
    }

    if (i == 3) {
        if (unkC->veh < 3) {
            *arg0 = 100 * levelGetTestCount(arg2, unkC->veh) - arg1;
        } else {
            *arg0 = 100 - arg1;
        }
        return 3;
    } else {
        *arg0 = val - arg1;
        return i;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_B2900/func_8032C27C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_B2900/func_8032C3C4.s")
