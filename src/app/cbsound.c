#include "common.h"
#include "cbsound.h"
#include <uv_audio.h>
#include <uv_event.h>
#include "app/cannonball.h"
#include "app/snd.h"

extern EventCallbackInfo D_80359BE0;
extern Unk803599D0 D_80359BE8;
void func_802D9E68(s32 eventType, void* arg1, s32 eventData);

void cbSoundInit(CannonballData* arg0) {
    s32 pad;
    s32 sp48;
    f32 sp44;

    arg0->unk2A8 = 1.0f;
    arg0->unk2B8 = 0.0f;
    arg0->unk2A4 = 75.0f;
    D_80359BE8.unk0 = 4;
    D_80359BE8.unk4 = 0.f;
    D_80359BE8.unk8 = 0.0f;
    D_80359BE8.unkC = 0.01f;
    D_80359BE8.unk10 = 0.4f;
    D_80359BE8.unk14 = 9.0f;
    D_80359BE8.unk18 = 0.8f;
    D_80359BE8.unk1C = 10.0f;
    D_80359BE8.unk20 = 1.0f;
    arg0->unk2B0 = sndMakeDev(0x13);
    arg0->unk2B1 = sndMakeDev(0x13);
    arg0->unk2B4 = uvEmitterLookup();
    sndGetPilot(&sp48, &sp44);
    uvEmitterFromModel(arg0->unk2B4, sp48);
    uvEmitterSetUnk70(arg0->unk2B4, 1.0f);
    uvEmitterSetUnk74(arg0->unk2B4, sp44);
    uvEmitterProp(arg0->unk2B4, 1, 0.0f, 2, 5000.0f, 5, 0x10, 0);
    arg0->unk2B5 = sndMakeDev(0x4C);
    D_80359BE0.cb = func_802D9E68;
    D_80359BE0.arg = arg0;
    arg0->unk2AC = ~0x3F;
    uvEventMaxCb(D_80359BE0, 1, 0xD, 0x12, 0x13, 0x10, 0xC, 0x16, 0x19, 0x24);
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/cbsound/func_802D9E68.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/cbsound/func_802DA1A8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/cbsound/func_802DA228.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/cbsound/func_802DA23C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/cbsound/func_802DA354.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/cbsound/func_802DA474.s")
