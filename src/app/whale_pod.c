#include "common.h"
#include <uv_dobj.h>
#include <uv_janim.h>
#include <uv_matrix.h>
#include <uv_model.h>
#include "code_9A960.h"
#include "proxanim.h"
#include "whale_pod.h"

typedef struct {
    s32 objId0;
    s32 objId4;
    Vec3F pos;
    f32 translateX;
    f32 state;
    f32 pathAngle;
    f32 depth;
} Whale; // size = 0x24

// .data
static s32 sWhalePodProxId = 0;
static s32 padD_803509F4 = 0;
static Vec3F sWhalePodInitPos = { 1156.66f, 1770.82f, 0.0f };

// .bss
static Whale gWhalePod[5];

STATIC_FUNC void whalePodUpdateWhale(s32 idx) {
    Mtx4F pose;
    s32 v1;
    s32 v0;
    f32 scale;

    uvMat4SetIdentity(&pose);
    uvMat4LocalTranslate(&pose, gWhalePod[idx].pos.x, gWhalePod[idx].pos.y, gWhalePod[idx].pos.z);
    uvMat4LocalTranslate(&pose, 0.0f, 0.0f, gWhalePod[idx].depth);
    uvMat4RotateAxis(&pose, gWhalePod[idx].pathAngle * 0.01745329f, 'z'); // almost DEG_TO_RAD(1)
    uvMat4LocalTranslate(&pose, gWhalePod[idx].translateX, 0.0f, 0.0f);
    uvDobjPosm(gWhalePod[idx].objId0, 0, &pose);
    if (gWhalePod[idx].objId4 != 0xFFFF) {
        uvMat4SetIdentity(&pose);
        uvMat4LocalTranslate(&pose, gWhalePod[idx].pos.x, gWhalePod[idx].pos.y, gWhalePod[idx].pos.z);
        uvMat4RotateAxis(&pose, gWhalePod[idx].pathAngle * 0.01745329f, 'z'); // almost DEG_TO_RAD(1)
        uvMat4LocalTranslate(&pose, gWhalePod[idx].translateX, 0.0f, 0.0f);
        uvDobjPosm(gWhalePod[idx].objId4, 0, &pose);
    }

    v0 = ((gWhalePod[idx].pathAngle + 15.0f) / 30);
    v1 = (s32)(gWhalePod[idx].pathAngle + 15.0f) % 30;

    if (v0 % 2) {
        scale = (30.0f - v1) / 30.0f;
    } else {
        scale = v1 / 30.0f;
    }
    func_80200B00(gWhalePod[idx].objId0, 0, 1.0f - scale);
    uvModelGetPosm(0xD7, 1, &pose);
    uvMat4Scale(&pose, 2.0 * scale, 2.0 * scale, 2.0 * scale);
    uvDobjPosm(gWhalePod[idx].objId0, 1, &pose);
}

STATIC_FUNC void whalePodUpdate(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gWhalePod); i++) {
        if (gWhalePod[i].state == 1.0f) {
            gWhalePod[i].depth += 4.0f * D_8034F854;
            if (gWhalePod[i].depth > 0.0f) {
                gWhalePod[i].state = 2.0f;
                gWhalePod[i].depth = 0.0f;
            }
            gWhalePod[i].pathAngle += 10.0f * D_8034F854;
            if (gWhalePod[i].pathAngle > 360.0f) {
                gWhalePod[i].pathAngle -= 360.0f;
            }
            whalePodUpdateWhale(i);
        } else if (gWhalePod[i].state == 2.0f) {
            gWhalePod[i].depth -= 4.0f * D_8034F854;
            if (gWhalePod[i].depth < -25.0f) {
                gWhalePod[i].state = 1.0f;
            }
            gWhalePod[i].pathAngle += 10.0f * D_8034F854;
            if (gWhalePod[i].pathAngle > 360.0f) {
                gWhalePod[i].pathAngle -= 360.0f;
            }
            whalePodUpdateWhale(i);
        }
    }
}

STATIC_FUNC s32 whalePodProxEventCb(UNUSED s32 proxId, s32 eventType, UNUSED s32 clientData) {
    Whale* whale;
    s32 i;

    switch (eventType) {
    case 0:
        for (i = 0; i < ARRAY_COUNT(gWhalePod); i++) {
            whale = &gWhalePod[i];
            uvDobjState(whale->objId0, 3);
            if (whale->objId4 != 0xFFFF) {
                uvDobjState(whale->objId4, 0x22);
            }
        }
        break;
    case 2:
        for (i = 0; i < ARRAY_COUNT(gWhalePod); i++) {
            whale = &gWhalePod[i];
            uvDobjState(whale->objId0, 0);
            if (whale->objId4 != 0xFFFF) {
                uvDobjState(whale->objId4, 0);
            }
        }
        break;
    case 3:
        for (i = 0; i < ARRAY_COUNT(gWhalePod); i++) {
            whale = &gWhalePod[i];
            uvDobjState(whale->objId0, 3);
            if (whale->objId4 != 0xFFFF) {
                uvDobjState(whale->objId4, 0x22);
            }
        }
        break;
    }
    return 0;
}

STATIC_FUNC s32 whalePodProxAnimCb(s32 proxId, UNUSED f32 timeout, UNUSED s32 clientData) {
    f32 dist;
    s32 ret;

    ret = 0;
    dist = proxAnimGetRange(proxId);
    if (dist > 1750.0f) {
        ret = 2;
    } else {
        whalePodUpdate();
    }
    return ret;
}

void whalePodInit(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gWhalePod); i++) {
        switch (i) {
        case 0:
            gWhalePod[i].pathAngle = 10.0f;
            gWhalePod[i].depth = -25.0f;
            gWhalePod[i].state = 1.0f;
            break;
        case 1:
            gWhalePod[i].pathAngle = 20.0f;
            gWhalePod[i].depth = -5.0f;
            gWhalePod[i].state = 1.0f;
            break;
        case 2:
            gWhalePod[i].pathAngle = 50.0f;
            gWhalePod[i].depth = 0.0f;
            gWhalePod[i].state = 1.0f;
            break;
        case 3:
            gWhalePod[i].pathAngle = 85.0f;
            gWhalePod[i].depth = -15.0f;
            gWhalePod[i].state = 1.0f;
            break;
        case 4:
            gWhalePod[i].pathAngle = 110.0f;
            gWhalePod[i].depth = -15.0f;
            gWhalePod[i].state = 2.0f;
            break;
        }
        gWhalePod[i].objId0 = 0xFFFF;
        gWhalePod[i].objId4 = 0xFFFF;
    }
}

void whalePodLoad(void) {
    s32 i;
    Vec3F pos = sWhalePodInitPos;

    sWhalePodProxId = proxAnimAddCallback(whalePodProxAnimCb, whalePodProxEventCb, pos, 1750.0f, 0.0f, 0);
    for (i = 0; i < ARRAY_COUNT(gWhalePod); i++) {
        gWhalePod[i].objId4 = uvDobjAllocIdx();
        if (gWhalePod[i].objId4 != 0xFFFF) {
            uvDobjModel(gWhalePod[i].objId4, MODEL_BROWN_BOX);
            uvDobjState(gWhalePod[i].objId4, 0);
        }
        gWhalePod[i].objId0 = uvDobjAllocIdx();
        if (gWhalePod[i].objId0 == 0xFFFF) {
            if (gWhalePod[i].objId4 != 0xFFFF) {
                uvDobjModel(gWhalePod[i].objId4, MODEL_WORLD);
                gWhalePod[i].objId4 = 0xFFFF;
            }
        } else {
            uvDobjModel(gWhalePod[i].objId0, MODEL_GREY_WHALE);
            uvDobjState(gWhalePod[i].objId0, 0);
            switch (i) {
            case 0:
                gWhalePod[i].translateX = 195.0f;
                gWhalePod[i].pos.x = 1156.66f;
                gWhalePod[i].pos.y = 1770.82f;
                gWhalePod[i].pos.z = 0.0f;
                break;
            case 1:
                gWhalePod[i].translateX = 220.0f;
                gWhalePod[i].pos.x = 1156.66f;
                gWhalePod[i].pos.y = 1770.82f;
                gWhalePod[i].pos.z = 0.0f;
                break;
            case 2:
                gWhalePod[i].translateX = 230.0f;
                gWhalePod[i].pos.x = 1156.66f;
                gWhalePod[i].pos.y = 1770.82f;
                gWhalePod[i].pos.z = 0.0f;
                break;
            case 3:
                gWhalePod[i].translateX = 180.0f;
                gWhalePod[i].pos.x = 1156.66f;
                gWhalePod[i].pos.y = 1770.82f;
                gWhalePod[i].pos.z = 0.0f;
                break;
            case 4:
                gWhalePod[i].translateX = 210.0f;
                gWhalePod[i].pos.x = 1156.66f;
                gWhalePod[i].pos.y = 1770.82f;
                gWhalePod[i].pos.z = 0.0f;
                break;
            }
        }
    }
}

void whalePodDeinit(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gWhalePod); i++) {
        if (gWhalePod[i].objId0 != 0xFFFF) {
            uvDobjModel(gWhalePod[i].objId0, MODEL_WORLD);
            gWhalePod[i].objId0 = 0xFFFF;
            if (gWhalePod[i].objId4 != 0xFFFF) {
                uvDobjModel(gWhalePod[i].objId4, MODEL_WORLD);
                gWhalePod[i].objId4 = 0xFFFF;
            }
        }
    }
    proxAnimDeleteCallback(sWhalePodProxId);
    sWhalePodProxId = 0;
}

void whalePodGetObjState(s32 whaleIdx, s32* objId, f32* interval, Vec3F* pos) {
    Mtx4F pose;
    Whale* whale;

    if (gWhalePod[whaleIdx].objId0 != 0xFFFF) {
        *objId = gWhalePod[whaleIdx].objId0;
        *interval = gWhalePod[whaleIdx].pathAngle / 360.0f;
        uvDobjGetPosm(*objId, 0, &pose);
        pos->x = pose.m[3][0];
        pos->y = pose.m[3][1];
        pos->z = pose.m[3][2];
    } else {
        *objId = 0xFFFF;
        *interval = 0.0f;
        pos->x = 0.0f;
        pos->y = 0.0f;
        pos->z = 0.0f;
    }
}

void whalePodSetInterval(s32 whaleIdx, f32 interval) {
    if (gWhalePod[whaleIdx].objId0 == 0xFFFF) {
        return;
    }

    uvDobjState(gWhalePod[whaleIdx].objId0, 3);
    if (gWhalePod[whaleIdx].objId4 != 0xFFFF) {
        uvDobjState(gWhalePod[whaleIdx].objId4, 0x22);
    }
    gWhalePod[whaleIdx].pathAngle = interval * 360.0f;
    whalePodUpdateWhale(whaleIdx);
}
