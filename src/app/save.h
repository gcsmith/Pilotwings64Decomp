#ifndef APP_SAVE_H
#define APP_SAVE_H

#include <PR/ultratypes.h>

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
