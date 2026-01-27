#include "common.h"
#include "uv_graphics.h"
#include "uv_level.h"
#include "uv_memory.h"
#include "uv_util.h"

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
    Unk80364210_Unk0_Unk0 unk0[MAX_TESTS * MAX_VEHICLES]; // guess
    s32 unk690;
} Unk80364210_Unk0;

typedef struct {
    Unk80364210_Unk0 unk0[MAX_CLASSES]; // guess
    u8 unk34A0[0x40];
} Unk80364210;

extern PilotwingsSaveFile D_803620E0[2];
extern PilotwingsSaveFile D_803622E0[2];

extern Unk80364210 D_80364210[];

void uvFontSet(s32);
void func_80219550(f64, f64);
void func_8021956C(u8, u8, u8, u8);
s32 func_802197EC(char*);
void func_80219EA8(void);
void func_80219ACC(s32, s32, char*);
s32 func_8030CB60(s32);
void func_8032B3D0(void*);
void func_80337D50(void);

// forward declarations
void func_802E81BC(char* arg0);
s32 func_802E8294(s32);

void func_802E7FA0(u8* arg0, s32* arg1, s32 arg2, s32 bitCount) {
    u8* bytePtr;
    s32 bitMask;
    s32 shift;
    s32 i;

    bitMask = (0xFF >> (8 - bitCount));
    arg2 = arg2 & bitMask;
    for (i = 0; i < bitCount; i++) {
        bytePtr = &arg0[*arg1 / 8];
        shift = (*arg1 % 8);
        *bytePtr |= ((arg2 & (1 << i)) >> i) << shift;
        *arg1 += 1;
    }
}

// fatal error handler: attempts to render message and infinite loops
void func_802E81BC(char* arg0) {
    s32 temp_s0;

    uvMemLoadDS(0x2E);
    uvFontSet(0);
    func_80219550(1.0, 1.0);
    func_8021956C(0xFF, 0xFF, 0x00, 0xFF);
    temp_s0 = 160 - (func_802197EC(arg0) / 2);
    for (;;) {
        uvGfxBegin();
        func_802228F0(0, 0, 0, 0);
        func_80219ACC(temp_s0, 100, arg0);
        func_80219EA8();
        uvGfxEnd();
    }
}

#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/nonmatchings/app/save/func_802E8294.s")
#else
s32 func_802E8294(s32 arg0) {
    uvMemSet(D_803620E0[arg0].raw, 0, sizeof(PilotwingsSaveFile));

    /* i don't even know. this *should* be something more like:
    D_803620E0[arg0].magic[0] = 'p';
    D_803620E0[arg0].magic[1] = 'w';
    */

    D_803620E0[0].raw[arg0 * sizeof(PilotwingsSaveFile) + 0] = 'p';
    D_803620E0[0].raw[arg0 * sizeof(PilotwingsSaveFile) + 1] = 'w';

    // cast sizeof to int/u16 to match?
    return uvFileWrite(D_803620E0[arg0].raw, arg0 * (int)sizeof(PilotwingsSaveFile), sizeof(PilotwingsSaveFile)) != sizeof(PilotwingsSaveFile);
}
#endif

void func_802E8304(void) {
    if (uvFileRead(D_803620E0, 0, sizeof(D_803620E0)) != sizeof(D_803620E0)) {
        func_802E81BC("EEPROM CHECK FAILED");
    } else {
        if (((D_803620E0[0].magic[0] != 'P') || (D_803620E0[0].magic[1] != 'W')) && ((D_803620E0[0].magic[0] != 'p') || (D_803620E0[0].magic[1] != 'w'))) {
            _uvDebugPrintf("EEProm file 1 initializing...\n");
            if (func_802E8294(0) != 0) {
                func_802E81BC("FILE 1 WRITE FAILED");
            }
        }
        if (((D_803620E0[1].magic[0] != 'P') || (D_803620E0[01].magic[1] != 'W')) && ((D_803620E0[1].magic[0] != 'p') || (D_803620E0[1].magic[1] != 'w'))) {
            _uvDebugPrintf("EEProm file 2 initializing...\n");
            if (func_802E8294(1) != 0) {
                func_802E81BC("FILE 2 WRITE FAILED");
            }
        }
    }
    _uvMediaCopy(D_803622E0, &D_803620E0, sizeof(D_803620E0));
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/save/func_802E8424.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/save/func_802E86C0.s")

// if returns s32, regalloc issues?
int func_802E899C(s32 fileIdx) {
    return (D_803620E0[fileIdx].magic[0] == 'P') && (D_803620E0[fileIdx].magic[1] == 'W');
}

s32 func_802E89D4(s32 fileIdx) {
    s32 sp1C;

    uvMemSet(&D_803620E0[fileIdx], 0, sizeof(PilotwingsSaveFile));
    func_8032B3D0(&D_80364210[D_80362690->unk9C]);
    func_80337D50();
    sp1C = func_802E8294(fileIdx);
    D_80362690->unkA8 = func_8030CB60(0);
    return sp1C;
}
