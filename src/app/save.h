#ifndef APP_SAVE_H
#define APP_SAVE_H

#include <PR/ultratypes.h>
#include <uv_level.h>

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

extern Unk80364210 D_80364210[];

void saveBitScramble(u8* data, s32* bitOffset, s32 bits, s32 bitCount);
void saveFatalError(char* msg);
s32 saveFileInit(s32 fileIdx);
void saveModuleInit(void);
void saveFileWrite(s32 fileIdx);
s32 saveFileLoad(s32 fileIdx);
int saveFileHasData(s32 fileIdx);
s32 save_802E89D4(s32 fileIdx);
s32 saveFile_802E89D4(s32 fileIdx);

#endif // APP_SAVE_H
