#include <uv_audio.h>
#include <uv_clocks.h>
#include <uv_util.h>

extern ALSeqPlayer* gSeqPlayer;

#if 1
#pragma GLOBAL_ASM("asm/nonmatchings/kernel/seq/uvaSeqNew.s")
#else
void _uvMediaCopy(void*, void*, s32); /* extern */
void uvaSeqStop(void);                /* extern */
extern ALSeqPlayer* gSeqPlayer;
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

    if (alSeqpGetState(gSeqPlayer) != 0) {
        uvaSeqStop();
    }
    _uvMediaCopy(D_80261220, ((ALSeqFile*)(D_8026121C + arg0 * 8))->seqArray[0].offset, seq_align);
    alCSeqNew(&D_80261230, D_80261220);
    alSeqpSetBank(gSeqPlayer, D_80261210);
    alSeqpSetSeq(gSeqPlayer, (ALSeq*)&D_80261230);
}
#endif

void uvaSeqPlay(void) {
    if (alSeqpGetState(gSeqPlayer) != 0) {
        uvaSeqStop();
    }
    alSeqpPlay(gSeqPlayer);
}

void uvaSeqSetTempo(f32 tempo) {
    if (alSeqpGetState(gSeqPlayer) != 0) {
        alSeqpSetTempo(gSeqPlayer, (s32)(60000000.0 / (f64)tempo));
    }
}

void uvaSeqSetVol(f32 vol) {
    if (alSeqpGetState(gSeqPlayer) != 0) {
        alSeqpSetVol(gSeqPlayer, (s16)(vol * 32767.0f));
    }
}

void uvaSeqStop(void) {
    alSeqpStop(gSeqPlayer);
    func_80206150(7);
    while (alSeqpGetState(gSeqPlayer)) {
        if (uvClkGetSec(7) > 2.0) {
            _uvDebugPrintf("uvaSeqStop timed out\n");
            return;
        }
    }
}
