#include "common.h"
#include <uv_math.h>
#include <uv_texture.h>
#include "code_72B70.h"
#include "demo.h"
#include "falco.h"
#include "task.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    f32 unkC;
    u8 pad10[0x80 - 0x10];
    f32 unk80;
    f32 unk84;
    f32 unk88;
    u8 pad8C[0xA4 - 0x8C];
    f32 unkA4;
    u8 padA8[0xB0 - 0xA8];
    f32 unkB0;
    u8 padB4[8];
    f32 unkBC;
    u8 padC0[4];
    f32 unkC4;
    f32 unkC8;
    f32 unkCC;
    u8 padD0[4];
    f32 unkD4;
    f32 unkD8;
    f32 unkDC;
    f32 unkE0;
    f32 unkE4;
    f32 unkE8;
    f32 unkEC;
    f32 unkF0;
    f32 unkF4;
    f32 unkF8;
    f32 unkFC;
    f32 unk100;
    f32 unk104;
    f32 unk108;
    f32 unk10C;
    f32 unk110;
    f32 unk114;
    f32 unk118;
    f32 unk11C;
    f32 unk120;
    f32 unk124;
    f32 unk128;
    f32 unk12C;
    f32 unk130;
    f32 unk134;
    f32 unk138;
    f32 unk13C;
    f32 unk140;
    f32 unk144;
    f32 unk148;
    f32 unk14C;
    f32 unk150;
    f32 unk154;
    f32 unk158;
    f32 unk15C;
    f32 unk160;
    f32 unk164;
    f32 unk168;
    u8 pad16C[0x230 - 0x16C];
    f32 unk230;
    f32 unk234;
    f32 unk238;
    s32 unk23C;
    u8 pad240[4];
    f32 unk244;
    s32 unk248;
    s32 unk24C;
    f32 unk250;
    u8 unk254;
    u8 unk255;
    u8 unk256;
    u8 pad257[1];
} Falco; // size = 0x258

typedef struct {
    s32 unk0;
    void* unk4; // maybe f32 pointer
    s32 unk8;   // always 0, maybe a pointer to something?
} Unk8034EFB0;

typedef struct {
    Vec3F unk0;
    f32 unkC;
} Unk8035A858;

typedef struct {
    s32 unk0;
    u8 pad4[0x60 - 0x4];
} Unk8035A920; // size = 0x60

// .data
f32 D_8034EFA0 = 0.0f;
s32 padD_8034EFA4[3] = { 0 };

extern TaskFALC* gRefFALC;

extern f32 D_8035AF30;
extern f32 D_8035AF34;
extern f32 D_8035AF38;
extern f32 D_8035AF3C;

// referenced in D_8034F03C
Unk8034EFB0 D_8034EFB0 = { 0xA, &D_8035AF30, 0 };
Unk8034EFB0 D_8034EFBC = { 0x5, &D_8035AF34, 0 };
Unk8034EFB0 D_8034EFC8 = { 0x6, &D_8035AF30, 0 };
Unk8034EFB0 D_8034EFD4 = { 0x9, &D_8035AF38, 0 };
Unk8034EFB0 D_8034EFE0 = { 0x8, &D_8035AF3C, 0 };
Unk8034EFB0 D_8034EFEC = { 0x7, &D_8035AF3C, 0 };
Unk8034EFB0 D_8034EFF8 = { 0x4, &D_8035AF3C, 0 };
Unk8034EFB0 D_8034EF04 = { 0x3, &D_8035AF3C, 0 };

// .bss
extern Falco gFalcos[1];
extern s32 gFalcoCount;
extern Unk8035A858 D_8035A858[];
extern s32 D_8035A918;
extern Unk8035A920 D_8035A920[16];

// forward declarations
void falco_802E38F0(Falco*, TaskFALC*);
void falco_802E478C(Falco*, Unk8035A858*);

void falcoInit(void) {
    Falco* falco;
    s32 i;

    if (D_80362690->unkA4 != 0) {
        uvRandSeed(13);
    } else {
        uvRandSeed((s32)(demoRandF() * 32768.0f) | 1);
    }

    for (i = 0; i < ARRAY_COUNT(gFalcos); i++) {
        falco = &gFalcos[i];
        falco->unk0 = 0xFFFF;
        falco->unk4 = 0xFFFF;
        falco->unk8 = 0xFFFF;
        falco->unk23C = 0;
        falco->unk244 = 0.0f;
        falco->unk255 = 0;
        falco->unk254 = 0;
        falco->unkC4 = 0.0f;
        falco->unkC8 = 50.0f;
        falco->unkCC = 27.63f;
        falco->unk256 = 0;
        falco->unk230 = 0.0f;
        falco->unk234 = 0.0f;
        falco->unk238 = 1.0f;
        falco->unkA4 = 0.0f;
        falco->unkB0 = 0.0f;
        falco->unkBC = 0.0f;
        falco->unk88 = 0.0f;
        falco->unk80 = 0.0f;
        falco->unk84 = 0.0f;
        falco->unk24C = 0;
    }

    for (i = 0; i < ARRAY_COUNT(D_8035A920); i++) {
        D_8035A920[i].unk0 = 0xFFFF;
    }

    gFalcoCount = D_8035A918 = D_8035A5F0 = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/falco_802E38F0.s")

void falcoLoad(void) {
    Falco* pFalco;
    TaskFALC* falc;
    Unk8035A858* var_s2;
    s32 falcoCount;
    s32 i;

    if (D_80362690->unkA0 == 0) {
        return;
    }

    gFalcoCount = taskGetFALC(&gRefFALC);
    if (gFalcoCount > 12) {
        _uvDebugPrintf("falcos : too many falcos domains defined in level [%d]\n", gFalcoCount);
        gFalcoCount = 0;
        return;
    }

    if (gFalcoCount > 0) {
        D_8035A5F0 = 1;
        uvLevelAppend(0x14);

        falcoCount = 0;
        for (i = 0; i < gFalcoCount; i++) {
            falc = &gRefFALC[i];
            var_s2 = &D_8035A858[i];
            if (falcoCount < ARRAY_COUNT(gFalcos)) {
                pFalco = &gFalcos[falcoCount];
            } else {
                _uvDebugPrintf("ERROR: too many falcos defined in task.  Max of %d falcos\n", 1);
                pFalco = &gFalcos[0];
            }
            uvVec3Copy(&var_s2->unk0, &falc->unk0);
            var_s2->unkC = falc->unkC;
            if (falc->unk10 != 0) {
                if (pFalco->unk255 == 0) {
                    falco_802E478C(pFalco, var_s2);
                }
                falco_802E38F0(pFalco, falc);
                pFalco->unk255 = 1;
                pFalco->unkD4 = falc->unk11 / 100.0f;
                pFalco->unkD8 = (falc->unk12 + falc->unk11) / 100.0f;
                pFalco->unkDC = (falc->unk12 + falc->unk11 + falc->unk13) / 100.0f;
                pFalco->unkE0 = falc->unk18;
                pFalco->unkE4 = falc->unk1C - falc->unk18;
                pFalco->unkE8 = falc->unk20;
                pFalco->unkEC = falc->unk24 - falc->unk20;
                pFalco->unkF0 = falc->unk28;
                pFalco->unkF4 = falc->unk2C - falc->unk28;
                pFalco->unkF8 = falc->unk30;
                pFalco->unkFC = falc->unk34 - falc->unk30;
                pFalco->unk100 = falc->unk38;
                pFalco->unk104 = falc->unk3C - falc->unk38;
                pFalco->unk108 = falc->unk40;
                pFalco->unk10C = falc->unk44 - falc->unk38;
                pFalco->unk110 = falc->unk48;
                pFalco->unk114 = falc->unk4C - falc->unk48;
                pFalco->unk118 = falc->unk50;
                pFalco->unk11C = falc->unk54 - falc->unk50;
                pFalco->unk120 = falc->unk58;
                pFalco->unk124 = falc->unk5C - falc->unk58;
                pFalco->unk128 = falc->unk60;
                pFalco->unk12C = falc->unk64 - falc->unk60;
                pFalco->unk130 = falc->unk68;
                pFalco->unk134 = falc->unk6C - falc->unk68;
                pFalco->unk138 = falc->unk70;
                pFalco->unk13C = falc->unk74 - falc->unk70;
                pFalco->unk140 = falc->unk78;
                pFalco->unk144 = falc->unk7C - falc->unk78;
                pFalco->unk148 = falc->unk80;
                pFalco->unk14C = falc->unk84 - falc->unk80;
                pFalco->unk150 = falc->unk88;
                pFalco->unk154 = falc->unk8C - falc->unk88;
                pFalco->unk158 = falc->unk90;
                pFalco->unk15C = falc->unk94;
                pFalco->unk248 = falc->unkA4;
                pFalco->unk160 = falc->unk98;
                pFalco->unk160 = falc->unk98;
                pFalco->unk164 = falc->unk9C;
                pFalco->unk168 = falc->unkA0;
                if (falc->unkA8 == 0.0f) {
                    pFalco->unk250 = 0.2f;
                } else {
                    pFalco->unk250 = 1.0f / falc->unkA8;
                }
                falcoCount++;
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/falcoDeinit.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/falcoFrameUpdate.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/falco_802E43C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/falco_802E45B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/falco_802E478C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/falco_802E4794.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/falco_802E49B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/falco_802E4AA8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/falco_802E4E70.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/falco_802E51E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/falco_802E55A0.s")

s32 falco_802E57C4(void) {
    s32 ret;
    s32 i;

    ret = 0;
    for (i = 0; i < D_8035A5F0; i++) {
        ret += gFalcos[i].unk254;
    }
    return ret;
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/falco_802E5818.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/falco_802E587C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/falco_802E5AFC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/falco_802E5BF8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/falco_802E5D78.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/falco_802E5F44.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/falco_802E5F90.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/falco_802E60A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/falco_802E60E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/falco_802E6128.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/falco_802E6184.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/falco_802E61E4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/falco_802E6224.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/falco_802E6284.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/falco_802E62E4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/falco_802E6344.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/falco_802E6380.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/falco_802E63BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/falco/falco_802E64E0.s")
