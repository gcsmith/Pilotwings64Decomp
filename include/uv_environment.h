#ifndef UV_ENVIRONMENT_H
#define UV_ENVIRONMENT_H

#include <PR/ultratypes.h>
#include <uv_dobj.h>

void uvEnvProps(s32 arg0, ...);
void uvEnvProps2(s32 arg0, ...);
void uvEnvFunc(s32 envId, s32 flag, void (*arg2)(void));
void func_80218700(void);
void _uvEnvDraw(s32 arg0, s32 arg1);

#endif // UV_ENVIRONMENT_H
