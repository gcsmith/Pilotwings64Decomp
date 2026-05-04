#ifndef PILOTWINGS64_UV_SYSTEM_H
#define PILOTWINGS64_UV_SYSTEM_H

#include <uv_common.h>

s32 uvFileWrite(u8* dst, s32 offs, s32 nbytes);
s32 uvFileRead(void* dst, s32 offs, s32 nbytes);
s32 uvSysInit(s32);
s32 uvSysUnknownStub(s32);
void uvWaitForMesg(char msg_type);
void uvSetVideoMode(void);

#endif // PILOTWINGS64_UV_SYSTEM_H

