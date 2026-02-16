#ifndef UV_EVENT_H
#define UV_EVENT_H

#include <PR/ultratypes.h>

typedef void (*EventCallback_t)(s32, s32, s32);

typedef struct EventCallbackInfo {
    EventCallback_t unk0;
    s32 unk4;
} EventCallbackInfo;

typedef struct UserEventCallbackInfo {
    EventCallbackInfo unk0[4];
    s32 count;
} UserEventCallbackInfo;

typedef struct SystemEventCallbackInfo {
    EventCallbackInfo unk0[10];
    s32 count;
} SystemEventCallbackInfo;

void func_80203434(s32, s32, s32);
void func_802035AC(s32, s32, s32);
void func_80203724(s32, s32, s32);

void uvEventPost(s32, s32);

#endif // UV_EVENT_H
