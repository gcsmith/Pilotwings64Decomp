#ifndef UV_ENVIRONMENT_H
#define UV_ENVIRONMENT_H

#include <PR/ultratypes.h>
#include <uv_dobj.h>

#define ENV_PROPID_END                  0
#define ENV_PROPID_FOG_COLOR            1 // type:s32,s32,s32,s32
#define ENV_PROPID_SCREEN_COLOR         2 // type:s32,s32,s32,s32
#define ENV_PROPID_FOG_FACTOR           3 // type:f64
#define ENV_PROPID_UNUSED               4 // type:s32,s32,s32,s32

#define ENV_PROP_END                    ENV_PROPID_END
#define ENV_PROP_FOG_COLOR(r,g,b,a)     ENV_PROPID_FOG_COLOR, (r), (g), (b), (a)
#define ENV_PROP_SCREEN_COLOR(r,g,b,a)  ENV_PROPID_SCREEN_COLOR, (r), (g), (b), (a)
#define ENV_PROP_FOG_FACTOR(x)          ENV_PROPID_FOG_FACTOR, (x)
#define ENV_PROP_UNUSED(r,g,b,a)        ENV_PROPID_UNUSED, (r), (g), (b), (a)

void uvEnvProps(s32 envId, ...);
void uvEnvGetProps(s32 envId, ...);
void uvEnvFunc(s32 envId, s32 flag, s32 (*arg2)(void));
void func_80218700(void);
void _uvEnvDraw(s32 arg0, s32 arg1);

#endif // UV_ENVIRONMENT_H
