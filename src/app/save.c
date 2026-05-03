#include "common.h"
#include <uv_font.h>
#include <uv_graphics.h>
#include <uv_memory.h>
#include <uv_system.h>
#include <uv_texture.h>
#include <uv_util.h>
#include "code_B2900.h"
#include "credits.h"
#include "save.h"
#include "snap.h"
#include "task.h"

typedef union {
    struct {
        u8 magic[2];
        u8 unk02[0xFD];
        u8 checksum;
    };
    u8 raw[0x100];
} PilotwingsSaveFile;

STATIC_DATA PilotwingsSaveFile sSaveFiles[2];
STATIC_DATA PilotwingsSaveFile sSaveFilesMirror[2];

STATIC_FUNC void saveFilePack(u8* data, s32* bits, s32* result, s32 bitCount) {
    s32 shift;
    u8* var_v1;
    s32 i;

    *result = 0;
    for (i = 0; i < bitCount; i++) {
        var_v1 = &data[*bits / 8];
        shift = *bits % 8;
        *result |= ((*var_v1 & (1 << shift)) >> shift) << i;
        (*bits)++;
    }
}

STATIC_FUNC void saveBitScramble(u8* data, s32* bitOffset, s32 bits, s32 bitCount) {
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
STATIC_FUNC void saveFatalError(char* msg) {
    s32 xScreen;

    uvLevelAppend(0x2E);
    uvFontSet(0);
    uvFontScale(1.0, 1.0);
    uvFontColor(0xFF, 0xFF, 0x00, 0xFF);
    xScreen = (SCREEN_WIDTH / 2) - (uvFontWidth(msg) / 2);
    for (;;) {
        uvGfxBegin();
        uvGfxClearScreen(0x00, 0x00, 0x00, 0x00);
        uvFontPrintStr(xScreen, 100, msg);
        uvFontGenDlist();
        uvGfxEnd();
    }
}

s32 saveFileInit(s32 fileIdx) {
    uvMemSet(sSaveFiles[fileIdx].raw, 0, sizeof(PilotwingsSaveFile));

    sSaveFiles[(u32)fileIdx].magic[0] = 'p';
    sSaveFiles[(u32)fileIdx].magic[1] = 'w';

    // cast sizeof to int/u16 to match?
    return uvFileWrite(sSaveFiles[fileIdx].raw, fileIdx * (int)sizeof(PilotwingsSaveFile), sizeof(PilotwingsSaveFile)) != sizeof(PilotwingsSaveFile);
}

void saveModuleInit(void) {
    if (uvFileRead(sSaveFiles, 0, sizeof(sSaveFiles)) != sizeof(sSaveFiles)) {
        saveFatalError("EEPROM CHECK FAILED");
    } else {
        if (((sSaveFiles[0].magic[0] != 'P') || (sSaveFiles[0].magic[1] != 'W')) && ((sSaveFiles[0].magic[0] != 'p') || (sSaveFiles[0].magic[1] != 'w'))) {
            _uvDebugPrintf("EEProm file 1 initializing...\n");
            if (saveFileInit(0) != 0) {
                saveFatalError("FILE 1 WRITE FAILED");
            }
        }
        if (((sSaveFiles[1].magic[0] != 'P') || (sSaveFiles[01].magic[1] != 'W')) && ((sSaveFiles[1].magic[0] != 'p') || (sSaveFiles[1].magic[1] != 'w'))) {
            _uvDebugPrintf("EEProm file 2 initializing...\n");
            if (saveFileInit(1) != 0) {
                saveFatalError("FILE 2 WRITE FAILED");
            }
        }
    }
    _uvMediaCopy(sSaveFilesMirror, &sSaveFiles, sizeof(sSaveFiles));
}

s32 saveFileWrite(s32 fileIdx) {
    PilotwingsSaveFile* saveFile;
    s32 bits;
    Unk80364210* results;
    s32 testCount;
    s32 v;
    s32 c;
    s32 t;
    s32 i;
    u32 sum;
    s32 val;
    u8* sp4C;

    saveFile = &sSaveFiles[fileIdx];
    results = &D_80364210[D_80362690->unk9C];
    uvMemSet(saveFile->raw, 0, 0x100);
    bits = 0x10;
    saveFile->magic[0] = 'P';
    saveFile->magic[1] = 'W';

    for (v = 0; v < VEHICLE_COUNT; v++) {
        for (c = 0; c < (IS_BONUS_VEHICLE(v) ? 3 : 4); c++) {
            testCount = taskGetTestCount(c, v);
            for (t = 0; t < testCount; t++) {
                val = results->unk40[c].unk0[t][v].unk2C;
                saveBitScramble(saveFile->raw, &bits, val, 7);
            }
        }
    }

    func_8033E860((Unk8033F050**)&sp4C);

    for (i = 0; i < 0x408; i++) {
        saveBitScramble(saveFile->raw, &bits, (s32)(sp4C[i / 8] & (1 << (i & 7))) >> (i & 7), 1);
    }

    sum = 0;
    for (i = 0; i < 0xFF; i += 1) {
        sum += saveFile->raw[i];
    }
    saveFile->raw[0xFF] = sum & 0xFF;
    if (uvMemCmp(saveFile->raw, sSaveFilesMirror[fileIdx].raw, sizeof(saveFile->raw)) != 0) {
        _uvMediaCopy(sSaveFilesMirror[fileIdx].raw, saveFile->raw, sizeof(saveFile->raw));
        if (uvFileWrite(saveFile->raw, fileIdx * 0x100, sizeof(saveFile->raw)) == 0) {
            return 0;
        }
    }
    return 1;
}

s32 saveFileLoad(s32 fileIdx) {
    PilotwingsSaveFile* saveFile;
    s32 bits;
    s32 val;
    u8 cksum;
    s32 testCount;
    s32 i;
    s32 t;
    s32 c;
    s32 v;
    s32 sum;
    u8 data[0x81];
    Unk80364210* results;

    results = &D_80364210[D_80362690->unk9C];
    if ((fileIdx < 0) || (fileIdx > 1)) {
        _uvDebugPrintf("file_load: bad file handle %d\n", fileIdx);
        return 0;
    }

    func_8032B3D0(&D_80364210[D_80362690->unk9C]);
    func_80337D50();

    saveFile = &sSaveFiles[fileIdx];
    sum = 0;
    for (i = 0; i < 0xFF; i++) {
        sum += saveFile->raw[i];
    }
    cksum = sum & 0xFF;
    if (cksum != sSaveFiles[fileIdx].checksum) {
        _uvDebugPrintf("file_load: checksum failure\n");
        return 0;
    }

    //! @bug likely intended `||` to check if either 'P' or 'W' were not present
    if ((saveFile->magic[0] != 'P') && (saveFile->magic[1] != 'W')) {
        return 0;
    }

    bits = 0x10;
    for (v = 0; v < VEHICLE_COUNT; v++) {
        for (c = 0; c < (IS_BONUS_VEHICLE(v) ? 3 : 4); c++) {
            testCount = taskGetTestCount(c, v);
            for (t = 0; t < testCount; t++) {
                saveFilePack(saveFile->raw, &bits, &val, 7);
                results->unk40[c].unk0[t][v].unk2C = val;
            }
        }
    }

    uvMemSet(&data, 0, sizeof(data));
    for (i = 0; i < 0x408; i++) {
        saveFilePack(saveFile->raw, &bits, &val, 1);
        data[i / 8] |= val << (i & 7);
    }
    func_8033F050(&data);
    D_80362690->unkA8 = credits_8030CC48();
    return 1;
}

// if returns s32, regalloc issues?
int saveFileHasData(s32 fileIdx) {
    return (sSaveFiles[fileIdx].magic[0] == 'P') && (sSaveFiles[fileIdx].magic[1] == 'W');
}

s32 saveFile_802E89D4(s32 fileIdx) {
    s32 sp1C;

    uvMemSet(&sSaveFiles[fileIdx], 0, sizeof(PilotwingsSaveFile));
    func_8032B3D0(&D_80364210[D_80362690->unk9C]);
    func_80337D50();
    sp1C = saveFileInit(fileIdx);
    D_80362690->unkA8 = credits_8030CB60(0);
    return sp1C;
}
