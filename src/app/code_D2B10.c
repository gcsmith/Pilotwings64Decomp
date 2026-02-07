#include <uv_debug.h>
#include <uv_level.h>
#include "code_9F2D0.h"
#include "code_C8990.h"
#include "code_D2B10.h"

// forward declarations
void func_8034B688(void);

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_D2B10/func_8034B5E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_D2B10/func_8034B624.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_D2B10/func_8034B688.s")

void func_8034B6F8(void) {
    s32 var_v0;

    func_803415C8();
    func_8034B688();
    var_v0 = D_80362690->unk0[0].debugFlag;
    if (var_v0 < 5) {
        func_803182A0();
        var_v0 = D_80362690->unk0[0].debugFlag;
    }
    switch (var_v0) {
    case 1:
        uvDbg_8023345C(7, 1, 1);
        break;
    case 2:
        uvDbg_8023345C(7, 2, 2);
        uvDbgCnt(0x1F, 2);
        break;
    case 3:
        uvDbg_8023345C(7, 1, 1);
        uvDbg_8023345C(7, 2, 2);
        uvDbgCnt(0x1F, 2);
        break;
    case 4:
    case 5:
        uvDbg_8023345C(6, 3, 1);
        uvDbgCnt(3, 3);
        break;
    case 6:
        uvDbg_80233590();
        D_80362690->unk0[0].debugFlag -= 1;
        break;
    }
}

