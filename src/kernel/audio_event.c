#include <libc/stdarg.h>
#include <uv_audio.h>
#include "common.h"

UserEventCallbackInfo D_8025BF00[30];
UNUSED UserEventCallbackInfo D_8025C338[5];
SystemEventCallbackInfo D_8025C3F0[5];
EventCallbackInfo D_8025C598;
EventCallbackInfo D_8025C5A0;
EventCallbackInfo D_8025C5A8;

// forward declarations
void uvEvent_80203434(s32, void*, s32);
void uvEvent_802035AC(s32, void*, s32);
void uvEvent_80203724(s32, void*, s32);

void uvEventInit(void) {
    s32 i;
    s32 j;

    for (i = 0; i < ARRAY_COUNT(D_8025BF00); i++) {
        for (j = 0; j < ARRAY_COUNT(D_8025BF00[i].unk0); j++) {
            D_8025BF00[i].unk0[j].cb = NULL;
            D_8025BF00[i].unk0[j].arg = 0;
        }
        D_8025BF00[i].count = 0;
    }

    for (i = 0; i < ARRAY_COUNT(D_8025C3F0); i++) {
        for (j = 0; j < ARRAY_COUNT(D_8025C3F0[i].unk0); j++) {
            D_8025C3F0[i].unk0[j].cb = NULL;
            D_8025C3F0[i].unk0[j].arg = 0;
            D_8025C3F0[i].count = 0;
        }
    }

    D_8025C598.cb = uvEvent_80203434;
    D_8025C598.arg = NULL;
    D_8025BF00[0].unk0[D_8025BF00[0].count] = D_8025C598;
    D_8025BF00[0].count++;

    D_8025C5A0.cb = uvEvent_802035AC;
    D_8025C5A0.arg = NULL;
    D_8025BF00[1].unk0[D_8025BF00[1].count] = D_8025C5A0;
    D_8025BF00[1].count++;

    D_8025C5A8.cb = uvEvent_80203724;
    D_8025C5A8.arg = NULL;
    D_8025BF00[2].unk0[D_8025BF00[2].count] = D_8025C5A8;
    D_8025BF00[2].count++;
}

void uvEventMaxCb(EventCallbackInfo arg0, ...) {
    s32 temp_a1;
    SystemEventCallbackInfo* temp_v0;
    UserEventCallbackInfo* temp_v0_2;
    va_list args;

    va_start(args, arg0);

    while (TRUE) {
        temp_a1 = va_arg(args, s32);
        if (temp_a1 == 36 || temp_a1 >= 36) {
            break;
        }
        if (temp_a1 < 5) {
            temp_v0 = &D_8025C3F0[temp_a1];
            if (temp_v0->count < 10) {
                temp_v0->unk0[temp_v0->count] = arg0;
                temp_v0->count++;
            } else {
                _uvDebugPrintf("Event %d: Max System Event Callbacks exceeded\n", temp_a1);
            }
        } else {
            temp_v0_2 = &D_8025BF00[temp_a1];
            if (temp_v0_2->count < 4) {
                temp_v0_2->unk0[temp_v0_2->count] = arg0;
                temp_v0_2->count++;
            } else {
                _uvDebugPrintf("Event %d:Max User Event Callbacks exceeded\n", temp_a1);
            }
        }
    }
}

void uvEventPost(s32 arg0, s32 arg1) {
    UserEventCallbackInfo* temp_t3;
    s32 count;
    s32 i;
    EventCallbackInfo sp64[4];

    if (arg0 >= 0x23) {
        _uvDebugPrintf("unknown event posted\n");
        return;
    }

    temp_t3 = &D_8025BF00[arg0];
    count = temp_t3->count;

    for (i = 0; i < count; i++) {
        sp64[i] = temp_t3->unk0[i];
    }

    for (i = 0; i < count; i++) {
        sp64[i].cb(arg0, sp64[i].arg, arg1);
    }
}

void uvEventRemoveCb(EventCallbackInfo arg0, ...) {
    SystemEventCallbackInfo* var_a3;
    UserEventCallbackInfo* var_a1;
    EventCallbackInfo* var_v1;
    s32 i;
    s32 j;
    s32 temp_v0;
    s32 count;
    va_list args;

    va_start(args, arg0);

    while (TRUE) {
        temp_v0 = va_arg(args, s32);
        if (temp_v0 == 0x24) {
            break;
        }
        if (temp_v0 >= 0x24) {
            _uvDebugPrintf("removing callback to unknown event\n");
            return;
        }

        if (temp_v0 < 5) {
            var_a3 = &D_8025C3F0[temp_v0];
            for (i = 0; i < var_a3->count; i++) {
                if ((arg0.cb == var_a3->unk0[i].cb) && (arg0.arg == var_a3->unk0[i].arg)) {
                    for (j = i; j < var_a3->count - 1; j++) {
                        var_a3->unk0[j].cb = var_a3->unk0[j + 1].cb;
                        var_a3->unk0[j].arg = var_a3->unk0[j + 1].arg;
                    }
                    var_a3->unk0[var_a3->count].cb = NULL;
                    var_a3->unk0[var_a3->count].arg = NULL;
                    var_a3->count--;
                }
            }
        } else {
            var_a1 = &D_8025BF00[temp_v0];
            for (i = 0; i < var_a1->count; i++) {
                if ((arg0.cb == var_a1->unk0[i].cb) && (arg0.arg == var_a1->unk0[i].arg)) {
                    for (j = i; j < var_a1->count - 1; j++) {
                        var_a1->unk0[j].cb = var_a1->unk0[j + 1].cb;
                        var_a1->unk0[j].arg = var_a1->unk0[j + 1].arg;
                    }
                    var_a1->unk0[var_a1->count].cb = NULL;
                    var_a1->unk0[var_a1->count].arg = NULL;
                    var_a1->count--;
                }
            }
        }
    }
}

void uvEvent_80203434(s32 arg0, void* arg1, s32 arg2) {
    SystemEventCallbackInfo* temp_t3;
    s32 count;
    s32 i;
    EventCallbackInfo sp64[10];

    temp_t3 = &D_8025C3F0[arg0];
    count = temp_t3->count;

    for (i = 0; i < count; i++) {
        sp64[i] = temp_t3->unk0[i];
    }

    for (i = 0; i < count; i++) {
        sp64[i].cb(arg0, sp64[i].arg, arg2);
    }
}

void uvEvent_802035AC(s32 arg0, void* arg1, s32 arg2) {
    SystemEventCallbackInfo* temp_t3;
    s32 count;
    s32 i;
    EventCallbackInfo sp64[10];

    temp_t3 = &D_8025C3F0[arg0];
    count = temp_t3->count;

    for (i = 0; i < count; i++) {
        sp64[i] = temp_t3->unk0[i];
    }

    for (i = 0; i < count; i++) {
        sp64[i].cb(arg0, sp64[i].arg, arg2);
    }
}

void uvEvent_80203724(s32 arg0, void* arg1, s32 arg2) {
    SystemEventCallbackInfo* temp_t3;
    s32 count;
    s32 i;
    EventCallbackInfo sp64[10];

    temp_t3 = &D_8025C3F0[arg0];
    count = temp_t3->count;

    for (i = 0; i < count; i++) {
        sp64[i] = temp_t3->unk0[i];
    }

    for (i = 0; i < count; i++) {
        sp64[i].cb(arg0, sp64[i].arg, arg2);
    }
}

