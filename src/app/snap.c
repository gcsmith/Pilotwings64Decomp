#include "common.h"
#include "snap.h"
#include <uv_clocks.h>
#include <uv_graphics.h>
#include <uv_vector.h>
#include "app/demo.h"
#include "app/snd.h"

typedef struct Unk80373060 {
    u8 pad0[0x30];
    u16 unk30;
    u16 unk32;
    u16 unk34;
    u8 unk36;
    u8 pad37[0x9];
    s16 unk40;
    u8 unk42;
    u8 unk43[6];
    u8 pad49[0x27];
} Unk80373060; // size 0x70

extern Unk80373060 D_80373060[];
extern Unk80373060 D_80373390[];

void func_8033A128(s32, Unk80373060*);
void func_8033A244(s32, Unk80373060*);
void func_8033A610(s32, s32, s32, s32);
void func_8033A6B8(void);
void func_8033ADD4(s32, Unk80373060*, s32, s32);

s32 D_80350510[] = { 0x4, 0x3, 0x1, 0x2, 0x6, 0x5 };
s32 D_80350528 = 0;
s32 D_8035052C[] = { 0, 0xFFFF };
s32 D_80350534 = 0;
s32 D_80350538 = 2;
s32 D_8035053C = 3;
s32 D_80350540 = 1;
u8 D_80350544 = 0;
s32 D_80350548 = 0;
u8 D_8035054C = 0; // might be array of up to 4 elements
s32 D_80350550 = 0;
Vec3F D_80350554 = { 0.0f, 1.0f, 0.0f };
s32 D_80350560[] = { 0x1C, 0x7D, 0x74, 0x7D, 0xCC, 0x7D, 0x1C, 0x33, 0x74, 0x33, 0xCC, 0x33 };
s32 D_80350590 = 0;
s32 D_80350594 = 0;
s32 D_80350598 = 0xFFFFFFFF;
s32 D_8035059C = 0xFFFFFFFF;
s32 D_803505A0 = 0xFFFFFFFF;
f32 D_803505A4 = 0.0f;
f32 D_803505A8 = 0.025f;

void func_80337D50(void) {
    s32 i;
    s32 j;

    for (i = 0; i < 6; i++) {
        D_80373060[i].unk40 = -1;
        D_80373060[i].unk42 = 0;
        D_80373060[i].unk36 = 0;
        for (j = 0; j < 6; j++) {
            D_80373390[i].unk43[j] = 0;
        }
    }

    D_80350528 = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/snap/func_80337DB8.s")

void func_803383FC(void) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/snap/func_80338404.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/snap/func_80338614.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/snap/func_8033869C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/snap/func_803386A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/snap/func_80338964.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/snap/func_80338A14.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/snap/func_80339C8C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/snap/func_80339E1C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/snap/func_80339F9C.s")

void func_8033A020(s32 arg0) {
    if (D_80350590 == 0) {
        return;
    }

    D_80350590 = 0;
    
    if ((arg0 == 0) || (D_80350594 != 0)) {
        func_802ECE94(D_80362690);
        D_80362690->unkA2 = 0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/snap/func_8033A078.s")

void func_8033A128(s32 arg0, Unk80373060* arg1) {
    Unk80362690_Unk0_UnkC* temp_v1;

    if ((arg0 != 0) && (D_80350594 == 0)) {
        return;
    }

    if (arg1 == NULL) {
        return;
    }

    if (arg1->unk43[0] == 0) {
        return;
    }

    temp_v1 = &D_80362690->unk0[D_80362690->unk9C].unkC;

    if ((D_80350598 != arg1->unk34) || (D_8035059C != arg1->unk30) || (D_803505A0 != arg1->unk32)) {
        func_8033A020(arg0);
        D_80350590 = 1;
        temp_v1->veh = arg1->unk34;
        temp_v1->cls = arg1->unk30;
        temp_v1->test = arg1->unk32;
        D_80350598 = temp_v1->veh;
        D_8035059C = temp_v1->cls;
        D_803505A0 = temp_v1->test;
        D_80362690->unkA2 = 1;
        func_802EC50C(D_80362690);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/snap/func_8033A244.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/snap/func_8033A610.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/snap/func_8033A664.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/snap/func_8033A6B8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/snap/func_8033A72C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/snap/func_8033ADD4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/snap/func_8033BF00.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/snap/func_8033CBD0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/snap/func_8033D3EC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/snap/func_8033DCD0.s")

s32 func_8033DDD8(s32 arg0, Unk80373060* arg1, s32* arg2) {
    s32 sp2C;
    s32 sp28;

    sp28 = *arg2;
    func_8033A6B8();
    uvGfxSetUnkStateF(0.00001f);
    func_8033ADD4(1, &arg1[sp28], sp28, arg0);
    func_8033ADD4(1, &arg1[sp28], sp28, arg0);
    uvClkReset(4);
    while (uvClkGetSec(4) < 0.1) { }
    func_8033A610(0x3A, 0x101, 0x31, 0xC6);
    func_8033A128(1, &arg1[sp28]);
    uvCopyFrameBuf(0);
    func_8033A244(1, &arg1[sp28]);
    func_8033A244(1, &arg1[sp28]);
    func_8033A244(1, &arg1[sp28]);
    uvGfxBegin();
    uvGfxEnd();
    sp2C = 0;

    while (TRUE) {
        demo_80323020();
        uvGfxBegin();
        uvGfxEnd();
        if (demoButtonPress(0, B_BUTTON) != 0) {
            snd_play_sfx(1);
            sp2C = 1;
            break;
        } else if (demoButtonPress(0, L_CBUTTONS) != 0) {
            if (*arg2 > 0) {
                (*arg2)--;
                func_8033F758(0x6A, 1.0f, 0.5f, 0.0f);
                break;
            }
        } else if ((demoButtonPress(0, R_CBUTTONS) != 0)) {
            if (*arg2 < (arg0 - 1)) {
                (*arg2)++;
                func_8033F758(0x6A, 1.0f, 0.5f, 0.0f);
                break;
            }
        }
    }
    func_8033A6B8();
    return sp2C;
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/snap/func_8033DFD0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/snap/func_8033E3A8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/snap/func_8033E784.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/snap/func_8033E810.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/snap/func_8033E860.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/snap/func_8033F050.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/snap/snapGetPhotoCount.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/snap/func_8033F62C.s")
