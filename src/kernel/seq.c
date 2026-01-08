#include <uv_audio.h>
#include <uv_clocks.h>
#include <uv_util.h>

extern ALSeqPlayer* D_80248C90;
extern ALSeqPlayer* D_80248C90;

#if 1
#pragma GLOBAL_ASM("asm/nonmatchings/kernel/seq/uvaSeqNew.s")
#else
void _uvMediaCopy(void*, void*, s32);                      /* extern */
void uvaSeqStop(void);                                     /* extern */
extern ALSeqPlayer* D_80248C90;
extern ALBank* D_80261210;
extern u8* D_8026121C;
extern u8* D_80261220;
extern ALCSeq D_80261230;
void uvaSeqNew(s32 arg0) {
    s32 seq_count;
    s32 seq_align;

    seq_count = ((ALSeqFile*)(D_8026121C + arg0 * 8))->seqArray[0].len;
    seq_align = seq_count;
    if (seq_count & 1) {
        seq_align = seq_count + 1;
    }

    if (alSeqpGetState(D_80248C90) != 0) {
        uvaSeqStop();
    }
    _uvMediaCopy(D_80261220, ((ALSeqFile*)(D_8026121C + arg0 * 8))->seqArray[0].offset, seq_align);
    alCSeqNew(&D_80261230, D_80261220);
    alSeqpSetBank(D_80248C90, D_80261210);
    alSeqpSetSeq(D_80248C90, (ALSeq* ) &D_80261230);
}
#endif

// #pragma GLOBAL_ASM("asm/nonmatchings/kernel/seq/uvaSeqPlay.s")
void uvaSeqPlay(void) {
    if (alSeqpGetState(D_80248C90) != 0) {
        uvaSeqStop();
    }
    alSeqpPlay(D_80248C90);
}

// #pragma GLOBAL_ASM("asm/nonmatchings/kernel/seq/uvaSeqSetTempo.s")
void uvaSeqSetTempo(f32 arg0) {
    if (alSeqpGetState(D_80248C90) != 0) {
        alSeqpSetTempo(D_80248C90, (s32) (60000000.0 / (f64) arg0));
    }
}

// #pragma GLOBAL_ASM("asm/nonmatchings/kernel/seq/uvaSeqSetVol.s")
void uvaSeqSetVol(f32 arg0) {
    if (alSeqpGetState(D_80248C90) != 0) {
        alSeqpSetVol(D_80248C90, (s16) (arg0 * 32767.0f));
    }
}

// #pragma GLOBAL_ASM("asm/nonmatchings/kernel/seq/uvaSeqStop.s")
void uvaSeqStop(void) {
    alSeqpStop(D_80248C90);
    func_80206150(7);
    if (alSeqpGetState(D_80248C90) != 0) {
        do {
            if (uvClkGetSec(7) > 2.0) {
                _uvDebugPrintf("uvaSeqStop timed out\n");
                return;
            }
        }
        while (alSeqpGetState(D_80248C90) != 0);
    }
}

