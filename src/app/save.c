#include "common.h"
#include <uv_graphics.h>
#include <uv_level.h>
#include <uv_memory.h>
#include <uv_util.h>
#include "code_B2900.h"
#include "credits.h"
#include "save.h"
#include "snap.h"

typedef union {
    struct {
        u8 magic[2];
        u8 unk02[0xFD];
        u8 checksum;
    };
    u8 raw[0x100];
} PilotwingsSaveFile;

typedef struct {
    u8 unk0[0xC];
    s16 unkC;
    u8 padE[0x22];
} Unk80364210_Unk0_Unk0;

typedef struct {
    Unk80364210_Unk0_Unk0 unk0[MAX_TESTS * VEHICLE_COUNT]; // guess
    s32 unk690;
} Unk80364210_Unk0;

typedef struct {
    Unk80364210_Unk0 unk0[MAX_CLASSES]; // guess
    u8 unk34A0[0x40];
} Unk80364210;

extern PilotwingsSaveFile D_803620E0[2];
extern PilotwingsSaveFile D_803622E0[2];

extern Unk80364210 D_80364210[];

void saveBitScramble(u8* data, s32* bitOffset, s32 bits, s32 bitCount) {
    u8* bytePtr;
    s32 bitMask;
    s32 shift;
    s32 i;

    bitMask = (0xFF >> (8 - bitCount));
    bits = bits & bitMask;
    for (i = 0; i < bitCount; i++) {
        bytePtr = &data[*bitOffset / 8];
        shift = (*bitOffset % 8);
        *bytePtr |= ((bits & (1 << i)) >> i) << shift;
        *bitOffset += 1;
    }
}

// fatal error handler: attempts to render message and infinite loops
void saveFatalError(char* msg) {
    s32 temp_s0;

    uvLevelAppend(0x2E);
    uvFontSet(0);
    uvFont_80219550(1.0, 1.0);
    uvFont_8021956C(0xFF, 0xFF, 0x00, 0xFF);
    temp_s0 = 160 - (uvFontWidth(msg) / 2);
    for (;;) {
        uvGfxBegin();
        uvGfxClearScreen(0, 0, 0, 0);
        uvFont_80219ACC(temp_s0, 100, msg);
        uvFont_80219EA8();
        uvGfxEnd();
    }
}

#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/nonmatchings/app/save/saveFileInit.s")
#else
s32 saveFileInit(s32 fileIdx) {
    uvMemSet(D_803620E0[fileIdx].raw, 0, sizeof(PilotwingsSaveFile));

    /* i don't even know. this *should* be something more like:
    D_803620E0[fileIdx].magic[0] = 'p';
    D_803620E0[fileIdx].magic[1] = 'w';
    */

    D_803620E0[0].raw[fileIdx * sizeof(PilotwingsSaveFile) + 0] = 'p';
    D_803620E0[0].raw[fileIdx * sizeof(PilotwingsSaveFile) + 1] = 'w';

    // cast sizeof to int/u16 to match?
    return uvFileWrite(D_803620E0[fileIdx].raw, fileIdx * (int)sizeof(PilotwingsSaveFile), sizeof(PilotwingsSaveFile)) != sizeof(PilotwingsSaveFile);
}
#endif

void saveModuleInit(void) {
    if (uvFileRead(D_803620E0, 0, sizeof(D_803620E0)) != sizeof(D_803620E0)) {
        saveFatalError("EEPROM CHECK FAILED");
    } else {
        if (((D_803620E0[0].magic[0] != 'P') || (D_803620E0[0].magic[1] != 'W')) && ((D_803620E0[0].magic[0] != 'p') || (D_803620E0[0].magic[1] != 'w'))) {
            _uvDebugPrintf("EEProm file 1 initializing...\n");
            if (saveFileInit(0) != 0) {
                saveFatalError("FILE 1 WRITE FAILED");
            }
        }
        if (((D_803620E0[1].magic[0] != 'P') || (D_803620E0[01].magic[1] != 'W')) && ((D_803620E0[1].magic[0] != 'p') || (D_803620E0[1].magic[1] != 'w'))) {
            _uvDebugPrintf("EEProm file 2 initializing...\n");
            if (saveFileInit(1) != 0) {
                saveFatalError("FILE 2 WRITE FAILED");
            }
        }
    }
    _uvMediaCopy(D_803622E0, &D_803620E0, sizeof(D_803620E0));
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/save/saveFileWrite.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/save/saveFileLoad.s")

// if returns s32, regalloc issues?
int saveFileHasData(s32 fileIdx) {
    return (D_803620E0[fileIdx].magic[0] == 'P') && (D_803620E0[fileIdx].magic[1] == 'W');
}

s32 saveFile_802E89D4(s32 fileIdx) {
    s32 sp1C;

    uvMemSet(&D_803620E0[fileIdx], 0, sizeof(PilotwingsSaveFile));
    func_8032B3D0(&D_80364210[D_80362690->unk9C]);
    func_80337D50();
    sp1C = saveFileInit(fileIdx);
    D_80362690->unkA8 = func_8030CB60(0);
    return sp1C;
}
