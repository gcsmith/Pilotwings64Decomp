#ifndef UV_FILESYSTEM_H
#define UV_FILESYSTEM_H

#include <PR/ultratypes.h>

s32 uvFileReadHeader(s32 addr);
void uvFile_80223F30(s32 idx);
u32 uvFileGetCurLength(s32 idx);
u32 uvFileGetCurTag(s32 idx);
u32 uvFileReadBlock(s32 idx, u32* sizeOut, void** arg2, s32 arg3);
u32 uvFile_80224170(s32 idx, void* arg1, void** arg2, u32 tag, s32 palette, s32 arg5);
void uvFile_8022427C(s32 idx);

#endif // UV_FILESYSTEM_H
