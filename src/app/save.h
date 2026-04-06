#ifndef APP_SAVE_H
#define APP_SAVE_H

#include <PR/ultratypes.h>

s32 saveFileInit(s32 fileIdx);
void saveModuleInit(void);
s32 saveFileWrite(s32 fileIdx);
s32 saveFileLoad(s32 fileIdx);
int saveFileHasData(s32 fileIdx);
s32 save_802E89D4(s32 fileIdx);
s32 saveFile_802E89D4(s32 fileIdx);

#endif // APP_SAVE_H
