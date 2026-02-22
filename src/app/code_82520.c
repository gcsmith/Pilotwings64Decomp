#include "common.h"
#include <uv_level.h>
#include "code_82520.h"

u8 D_8034F3A0 = 0;

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_82520/func_802FAFF0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_82520/func_802FB0DC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_82520/func_802FB1D8.s")

void func_802FB22C(void) {
    s32 i;
    LevelHOPD* hopd;

    if (D_80362690->unkA0 != 0) {
        D_8034F3A0 = levelDataGetHOPD(&hopd);
        if (D_8034F3A0 > 5) {
            _uvDebugPrintf("hmgoal : too many hmgoal defined in level [%d]\n", D_8034F3A0);
            D_8034F3A0 = 0;
            return;
        }
        if (D_8034F3A0 != 0) {
            uvLevelAppend(0x19);

            for (i = 0; i < D_8034F3A0; i++) {
                if (D_80368B80[i].unk6 == 0) {
                    D_80368B80[i].unk0 = &hopd[i]; // <-+ this might be a bug:
                    func_802FB0DC(&D_80368B80[i]); //   | incrementing pointer
                } //                                    | *and* using index [i]
                hopd++; // -----------------------------+
            }
            func_802FAFF0();
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_82520/func_802FB308.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_82520/func_802FB518.s")

u8 func_802FB5A0(void) {
    s32 i;
    u8 ret;

    ret = 0;
    for (i = 0; i < D_8034F3A0; i++) {
        ret += (D_80368B80[i].unk6 != 0) ? 1 : 0;
    }
    return ret;
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_82520/func_802FB5FC.s")
