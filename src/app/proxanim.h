#ifndef APP_PROXANIM_H
#define APP_PROXANIM_H

#include <PR/ultratypes.h>
#include <uv_vector.h>

typedef struct {
    s32 (*animCb)(s32, f32, s32);
    s32 (*eventCb)(s32, s32, s32);
    u8 active;
    u8 pad9[3];
    f32 dist;
    f32 timeout;
    s32 clientData;
    Vec3F pos;
} ProxAnim; // size = 0x24

void proxAnimInit(void);
s32 proxAnimAddCallback(s32 (*animCb)(s32, f32, s32), s32 (*eventCb)(s32, s32, s32), Vec3F pos, f32 dist, f32 timeout, s32 arg);
void proxAnimDeleteCallback(s32 proxId);
void proxAnimDispatchEvent2(void);
void proxAnimDispatchEvent3(void);
f32 proxAnimGetRange(s32);
void proxAnimDispatchInit(void);
void proxAnimUpdate(void);
ProxAnim* proxAnimGetHandle(s32 proxId);

#endif // APP_PROXANIM_H
