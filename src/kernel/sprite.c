#include <uv_sprite.h>
#include "common.h"

extern Gfx* gGfxDisplayListHead;
extern s32 gSprtUnkIndex;
extern s32 gSprtUnkTable[];
extern uvSprite_t gSprtTable1[];
extern uvSprite_t gSprtTable2[];
extern uvSprite_t gSprtTable3[];

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/sprite/uvSprt_80230130.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/sprite/uvSprt_802301A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/sprite/_uvTxtDraw.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/sprite/uvSprtFromBitmap.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/sprite/uvSprt_80230750.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/sprite/uvSprt_80230898.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/sprite/uvSprtInit.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/sprite/uvSprtDisplayList.s")

void uvSprtDrawAll(void) {
    uvSprite_t* var_s0;
    uvSprite_t* var_s1;

    spInit(&gGfxDisplayListHead);
    var_s0 = &gSprtTable1[0]; var_s1 = &gSprtTable1[0x1F];
    do {
        if ((var_s0->unk0 != 0) && (var_s0->unk1 != 0) && (var_s0->unkA != 0xFFF)) {
            uvSprtDisplayList(var_s0);
        }
        var_s0 ++;
    } while (var_s0 != var_s1);
    spFinish(&gGfxDisplayListHead);
    gGfxDisplayListHead --;
}

void uvSprtDraw(s32 sprite_id) {
    uvSprite_t* sprite;

    if (sprite_id >= 0x1F) {
        _uvDebugPrintf("uvSprtDraw: invalid sprite id %d\n", sprite_id);
        return;
    }
    sprite = &gSprtTable1[sprite_id];
    if (sprite->unkA != 0xFFF) {
        spInit(&gGfxDisplayListHead);
        uvSprtDisplayList(sprite);
        spFinish(&gGfxDisplayListHead);
        gGfxDisplayListHead--;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/sprite/uvSprtSetBlit.s")

s16 uvSprtGetUnk0(s32 sprite_id) {
    return *(s16*)&gSprtTable2[sprite_id].unk0;
}

s16 uvSprtGetUnk1(s32 sprite_id) {
    return *(s16*)&gSprtTable3[sprite_id].unk0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/sprite/uvSprtProps.s")

void uvSprtUpdateUnk(uvSprite_t* sprite) {
    if (sprite->unk18 != 0) {
        gSprtUnkTable[gSprtUnkIndex] = sprite->unk18;
        gSprtUnkIndex += 1;
    }
    if (sprite->unk1C != 0) {
        gSprtUnkTable[gSprtUnkIndex] = sprite->unk1C;
        gSprtUnkIndex += 1;
    }
}

void uvSprtResetUnk(void) {
    gSprtUnkIndex = 0;
}

