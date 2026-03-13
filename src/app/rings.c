#include "common.h"
#include <uv_dobj.h>
#include <uv_string.h>
#include <uv_texture.h>
#include "code_9A960.h"
#include "hud.h"
#include "rings.h"
#include "task.h"

void func_803234A4(ParsedRing*);
void func_80323720(ParsedRing*);

extern LevelRNGS* D_8036DA70;
extern u8 D_8036DA74; // count of rings stored in D_8036DA78
// extern ParsedRing D_8036DA78[30]; // stored here, exported in header
extern u8 D_80371060[5];

void ringsInit(void) {
    ParsedRing* var_v1;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_8036DA78); i++) {
        var_v1 = &D_8036DA78[i];
        var_v1->unk0 = 0xFFFF;
        var_v1->unk1B4 = 0;
        var_v1->unk1B7 = 0;
        var_v1->unk1B5 = 0;
        var_v1->unk180 = 0.0f;
        var_v1->unk1B8 = 0;
        var_v1->unk1B9 = 0;
        var_v1->unk1CA = 0xFF;
    }

    for (i = 0; i < ARRAY_COUNT(D_80371060); i++) {
        D_80371060[i] = 0xFF;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/rings/func_80323364.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/rings/func_803234A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/rings/func_80323720.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/rings/func_80323864.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/rings/func_8032390C.s")

void ringsLoad(void) {
    ParsedRing* ring;
    LevelRNGS* rngs;
    s32 var_a0;
    s32 i;
    s32 j;
    u8 unk72;

    if (D_80362690->unkA0 == 0) {
        return;
    }

    D_8036DA74 = taskGetRNGS(&D_8036DA70);
    if (D_8036DA74 > ARRAY_COUNT(D_8036DA78)) {
        _uvDebugPrintf("rings : too many rings defined in level [%d]\n", D_8036DA74);
        D_8036DA74 = 0;
        return;
    }

    if (D_8036DA74 == 0) {
        return;
    }

    uvLevelAppend(0xE);
    for (i = 0; i < D_8036DA74; i++) {
        rngs = &D_8036DA70[i];
        ring = &D_8036DA78[i];
        if (ring->unk1B4 != 0) {
            continue;
        }

        if (ring->unk1B5 == 0) {
            ring->unk144 = rngs->unk71;
            if (rngs->unk72 > 3) {
                rngs->unk72 = 3;
            }
            unk72 = rngs->unk72;
            ring->unk147 = ring->unk146 = unk72;
            ring->unk184 = rngs->size;
            ring->unk1B7 = rngs->unk55;
            ring->unk149 = rngs->unk1D;
            if (ring->unk1B7 && (ring->unk149 > 0)) {
                ring->unk1B9 = 1;
            }
            ring->unk160 = (u8)rngs->unk34;
            for (j = 0; j < ring->unk149; j++) {
                ring->unk14C[j] = rngs->unk20[j];
            }

            for (j = 0; j < ring->unk160; j++) {
                ring->unk164[j] = rngs->unk38[j];
            }
            if ((ring->unk1B7 == 0) || (ring->unk149 != 0)) {
                ring->unk145 = 1;
            } else {
                ring->unk145 = 0;
            }
            ring->unk178 = rngs->unk4D;
            ring->unk17C = rngs->unk50;
            ring->unk180 = 0.0f;
            ring->unk148 = rngs->unk4C;
            ring->unk1AC = 1000000.0f;
            ring->unk1B0 = 1000000.0f;
            ring->unk1A8 = 0.0f;
            ring->unk1A4 = 0.0f;
            ring->unk188 = rngs->unk58;
            ring->unk18C = rngs->unk5C;
            ring->unk190 = rngs->unk60;
            ring->unk194 = rngs->unk64;
            ring->unk198 = rngs->unk68;
            ring->unk19C = rngs->unk6C;
            ring->unk1A0 = rngs->axis; // unk70
            ring->unk1BA = rngs->unk73;
            uvSprintf(ring->unk1BB, "%s", rngs->unk74);
            func_80313640(rngs->pos.x, rngs->pos.y, rngs->pos.z, rngs->angle.x * 0.0174533f, rngs->angle.y * 0.0174533f, rngs->angle.z * 0.0174533f,
                          &ring->unk4);
            uvMat4Copy(&ring->unk44, &ring->unk4);
            ring->unk44.m[3][0] = 0.0f;
            ring->unk44.m[3][1] = 0.0f;
            ring->unk44.m[3][2] = 0.0f;
            uvMat4Copy(&ring->unk84, &ring->unk4);
            ring->unk1B5 = 1;
        }
        if ((ring->unk1B7 != 0) && (ring->unk147 != 2)) {
            ring->unk1CA = hudAddWaypoint(rngs->pos.x, rngs->pos.y, rngs->pos.z);
        }
        func_803234A4(ring);
        if ((ring->unk180 != 0) && (ring->unk1B7 != 0)) {
            uvDobjProps(ring->unk0, 4, (ring->unk144 == 0) ? 2 : 5, 0);
            uvDobjProps(ring->unk0, 4, (ring->unk144 == 0) ? 3 : 6, 0);
            func_80323720(ring);
        }
    }
    func_80323364();
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/rings/func_80323DCC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/rings/func_80323FFC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/rings/func_803243D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/rings/ringsDeinit.s")

u8 func_80324AF4(void) {
    u8 ret;
    s32 i;

    ret = 0;
    for (i = 0; i < D_8036DA74; i++) {
        ret += (D_8036DA78[i].unk1B4 != 0) ? 1 : 0;
    }
    return ret;
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/rings/func_80324B60.s")
