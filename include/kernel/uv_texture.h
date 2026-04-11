#ifndef UV_TEXTURE_H
#define UV_TEXTURE_H

#include <PR/ultratypes.h>

void uvMemInitBlockHdr(void);
void* uvMemLoadDS(u32 tag, s32 palette);
void uvMemLoadPal(s32 palette);
void uvLevelAppend(s32 levelId);
void uvConsumeBytes(void* dst, u8** ptr, s32 size);

#endif // UV_TEXTURE_H
