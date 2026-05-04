#ifndef PILOTWINGS64_UV_TEXTURE_H
#define PILOTWINGS64_UV_TEXTURE_H

#include <uv_common.h>

void uvMemInitBlockHdr(void);
void* uvMemLoadDS(u32 tag, s32 palette);
void uvMemLoadPal(s32 palette);
void uvLevelAppend(s32 levelId);
void uvConsumeBytes(void* dst, u8** ptr, s32 size);

#endif // PILOTWINGS64_UV_TEXTURE_H

