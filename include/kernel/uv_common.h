#ifndef PILOTWINGS64_UV_COMMON_H
#define PILOTWINGS64_UV_COMMON_H

#include <PR/ultratypes.h>

#define UV_KERNEL_VERSION 0xD

// technically part of uv_system but used everywhere
void _uvDebugPrintf(char* fmt, ...);
void _uvAssertMsg(const char* expr, const char* filename, int line);

#endif // PILOTWINGS64_UV_COMMON_H

