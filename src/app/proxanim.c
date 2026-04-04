#include "common.h"
#include <uv_math.h>
#include "code_9A960.h"
#include "game.h"
#include "proxanim.h"

static ProxAnim sProxAnimSlots[40];

void proxAnimInit(void) {
    s32 i;
    ProxAnim* prox;

    for (i = 0; i < ARRAY_COUNT(sProxAnimSlots); i++) {
        prox = &sProxAnimSlots[i];
        prox->animCb = NULL;
        prox->eventCb = NULL;
        prox->dist = 0.0f;
        prox->timeout = 0.0f;
        prox->clientData = 0;
    }
}

STATIC_FUNC s32 proxAnimFreeSlot(void) {
    ProxAnim* prox;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sProxAnimSlots); i++) {
        prox = &sProxAnimSlots[i];
        if (prox->dist == 0.0f) {
            return i;
        }
    }
    return -1;
}

static const char unused00[] = "Proxanm: Initializing\n";

s32 proxAnimAddCallback(s32 (*animCb)(s32, f32, s32), s32 (*eventCb)(s32, s32, s32), Vec3F pos, f32 dist, f32 timeout, s32 arg) {
    ProxAnim* prox;
    s32 idx;

    idx = proxAnimFreeSlot();
    if (idx == -1) {
        _uvDebugPrintf("Proxanim: No more animation slots left (max is %d)\n", ARRAY_COUNT(sProxAnimSlots));
        return -1;
    }
    if (animCb == NULL) {
        _uvDebugPrintf("Proxanim: NULL anim proc\n");
        return -1;
    }
    prox = &sProxAnimSlots[idx];
    prox->animCb = animCb;
    prox->active = FALSE;
    prox->eventCb = eventCb;
    prox->dist = dist;
    prox->timeout = timeout;
    prox->clientData = arg;
    prox->pos = pos;
    return idx;
}

// unused strings after "\n":
static const char unused0[] = "Proxanim: Added anim %d\n";

void proxAnimDeleteCallback(s32 proxId) {
    ProxAnim* prox;

    if ((proxId < 0) || (proxId >= ARRAY_COUNT(sProxAnimSlots))) {
        _uvDebugPrintf("Proxanim: Invalid ID %d deleted\n", proxId);
        return;
    }
    prox = &sProxAnimSlots[proxId];
    if (prox->eventCb != NULL) {
        prox->eventCb(proxId, 1, prox->clientData);
    }
    prox->active = FALSE;
    prox->dist = 0.0f;
}

// TODO: where do these best belong?
static const char unused1[] = "Proxanim: Deleting %d\n";
static const char unused2[] = "Proxanim: Sending message %d to active panims\n";

STATIC_FUNC void proxAnimDispatchEvent(s32 eventType) {
    ProxAnim* prox;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sProxAnimSlots); i++) {
        prox = &sProxAnimSlots[i];
        if (prox->active) {
            if (prox->eventCb != NULL) {
                prox->eventCb(i, eventType, prox->clientData);
            }
        }
    }
}

void proxAnimDispatchEvent2(void) {
    proxAnimDispatchEvent(2);
}

void proxAnimDispatchEvent3(void) {
    proxAnimDispatchEvent(3);
}

f32 proxAnimGetRange(s32 proxId) {
    Unk80362690_Unk0* temp_v1;
    ProxAnim* prox;
    f32 dx, dy, dz;

    temp_v1 = &D_80362690->unkC[D_80362690->unk9C];
    prox = &sProxAnimSlots[proxId];

    if ((proxId < 0) || (proxId >= ARRAY_COUNT(sProxAnimSlots)) || (prox->dist == 0.0f)) {
        _uvDebugPrintf("Proxanim: Bad id %d passed to panm_getrange\n", proxId);
        return 0.0f;
    }

    dx = temp_v1->unk2C.m[3][0] - prox->pos.x;
    dy = temp_v1->unk2C.m[3][1] - prox->pos.y;
    dz = temp_v1->unk2C.m[3][2] - prox->pos.z;
    return uvLength3D(dx, dy, dz);
}

// TODO: where do these best belong?
static const char unused3[] = "Proxanim: Activating animation %d\n";
static const char unused4[] = "Proxanim: Init for anim %d requested deactivation\n";
static const char unused5[] = "Proxanim: Calling anim proc for %d, time %f\n";
static const char unused6[] = "Proxanim: Anim %d is done.\n";
static const char unused7[] = "Proxanim: Anim %d is deactivating.\n";

void proxAnimDispatchInit(void) {
    proxAnimDispatchEvent(1);
    proxAnimInit();
}

void proxAnimUpdate(void) {
    ProxAnim* prox;
    s32 res;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sProxAnimSlots); i++) {
        prox = &sProxAnimSlots[i];
        if (prox->dist == 0.0f) {
            continue;
        }

        if (!prox->active) {
            if (proxAnimGetRange(i) < prox->dist) {
                prox->active = TRUE;
                if (prox->eventCb == NULL) {
                    continue;
                }
                res = prox->eventCb(i, 0, prox->clientData);
                if (res != -1) {
                    if (res == 2) {
                        prox->active = FALSE;
                    }
                } else {
                    proxAnimDeleteCallback(i);
                }
            }
        } else {
            if (prox->timeout < 0.0f) {
                proxAnimDeleteCallback(i);
            } else {
                if (prox->timeout > 0.0f) {
                    prox->timeout -= D_8034F854;
                }
                res = prox->animCb(i, prox->timeout, prox->clientData);
                switch (res) {
                case 1:
                    proxAnimDeleteCallback(i);
                    break;
                case 2:
                    prox->active = FALSE;
                    break;
                }
            }
        }
    }
}

ProxAnim* proxAnimGetHandle(s32 proxId) {
    ProxAnim* prox;
    prox = &sProxAnimSlots[proxId];
    if ((proxId < 0) || (proxId >= ARRAY_COUNT(sProxAnimSlots)) || (prox->dist == 0.0f)) {
        return NULL;
    }
    return prox;
}
