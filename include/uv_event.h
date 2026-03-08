#ifndef UV_EVENT_H
#define UV_EVENT_H

#include <PR/ultratypes.h>

typedef void (*EventCallback_t)(s32, void*, s32);

typedef struct EventCallbackInfo {
    EventCallback_t cb;
    void* arg;
} EventCallbackInfo;

typedef struct UserEventCallbackInfo {
    EventCallbackInfo unk0[4];
    s32 count;
} UserEventCallbackInfo;

typedef struct SystemEventCallbackInfo {
    EventCallbackInfo unk0[10];
    s32 count;
} SystemEventCallbackInfo;

void func_80202DA0(void);
void uvEventMaxCb(EventCallbackInfo arg0, ...);
void uvEventRemoveCb(EventCallbackInfo arg0, ...);
void uvEventPost(s32, s32);

#endif // UV_EVENT_H
