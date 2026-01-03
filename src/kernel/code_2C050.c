#include <uv_memory.h>

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2C050/func_8022B0A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2C050/_uvScDoneGfx.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2C050/_uvScDoneAud.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2C050/_uvScRunAud.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2C050/_uvScRunGfx.s")

// #pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2C050/_uvScDlistRecover.s")

extern u8 D_802B9C69;
extern u8 D_802B9C6A;
extern OSMesgQueue D_802C38E8;

void _uvScDlistRecover(void) {
    _uvDebugPrintf("Recovered from a bad display list\n");
    IO_WRITE(SP_STATUS_REG, 0x2902);
    if (D_802B9C69 != 0) {
        osSendMesg(&D_802C38E8, (void *)0x29B, 0);
    }
    if (D_802B9C6A != 0) {
        osSendMesg(&D_802C38E8, (void *)0x29C, 0);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2C050/func_8022B6CC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2C050/func_8022B8A8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2C050/osScGetCmdQ.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2C050/__scMain.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2C050/_uvScHandleRetrace.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2C050/_uvScHandleRSP.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2C050/func_8022BE2C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2C050/func_8022BE8C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2C050/func_8022BEB8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2C050/_uvScLogCpuEvent.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2C050/_uvScLogIntoRing.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2C050/func_8022C34C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_2C050/func_8022C3C0.s")
