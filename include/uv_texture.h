#ifndef UV_TEXTURE_H
#define UV_TEXTURE_H

#include <PR/ultratypes.h>

#define UVTX_MAX_BYTES 0x1000

void uvConsumeBytes(void* dst, u8** ptr, s32 size);

#endif // UV_TEXTURE_H
