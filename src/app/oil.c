#include "common.h"
#include <uv_dobj.h>
#include <uv_vector.h>
#include "code_9A960.h"
#include "oil.h"
#include "proxanim.h"

static s32 sOilObjId = 0xFFFF;
static f32 sOilScale = 0.0f;
static s32 sOilState = 0;
static s32 sOilActive = FALSE;
static Vec3F sOilInitPos = { -73.8f, 575.7f, 88.3f };

static Mtx4F gOilPos;
static s32 sOilProxId;

STATIC_FUNC void oilUpdatePos(void) {
    Mtx4F scaleMtx;
    Mtx4F pose;

    uvMat4SetIdentity(&scaleMtx);
    uvMat4Scale(&scaleMtx, sOilScale, sOilScale, sOilScale);
    uvDobjProps(sOilObjId, 3, sOilScale, 0);
    uvMat4Mul(&pose, &scaleMtx, &gOilPos);
    uvDobjPosm(sOilObjId, 0, &pose);
}

STATIC_FUNC void oilUpdate(void) {
    if (sOilState == 1) {
        sOilScale += 0.5f * D_8034F854;
        if (sOilScale > 1.0f) {
            sOilState = 0;
            sOilScale = 1.0f;
        }
        oilUpdatePos();
    } else if (sOilState == 2) {
        sOilScale -= 0.5f * D_8034F854;
        if (sOilScale < 0.0) {
            sOilState = 3;
            sOilScale = 0.0f;
        }
        oilUpdatePos();
    } else if (sOilState == 0) {
        oilUpdatePos();
    }
}

STATIC_FUNC s32 oil_80315BB8(s32 arg0, s32 arg1, s32 arg2) {
    switch (arg1) {
    case 0:
        sOilActive = FALSE;
        uvDobjState(sOilObjId, 2);
        sOilState = 1;
        uvMat4SetIdentity(&gOilPos);
        uvMat4LocalTranslate(&gOilPos, -73.8f, 575.7f, 88.3f);
        oilUpdatePos();
        break;
    case 2:
        uvDobjState(sOilObjId, 0);
        break;
    case 3:
        uvDobjState(sOilObjId, 2);
        break;
    }
    return 0;
}

STATIC_FUNC s32 oil_80315C84(s32 arg0, f32 arg1, s32 arg2) {
    f32 dist;
    s32 ret;

    ret = 0;
    dist = proxAnimGetRange(arg0);
    if (dist > 300.0f) {
        if (sOilActive) {
            sOilState = 2;
            oilUpdate();
            if (sOilState == 3) {
                sOilActive = FALSE;
            }
        } else {
            ret = 2;
            uvDobjState(sOilObjId, 0);
        }
    } else {
        if ((sOilState == 2) || !sOilActive) {
            sOilActive = TRUE;
            sOilState = 1;
            uvDobjState(sOilObjId, 2);
        }
        oilUpdate();
    }
    return ret;
}

void oilInit(void) {
    Vec3F pos;

    pos = sOilInitPos;
    sOilObjId = uvDobjAllocIdx();
    if (sOilObjId != 0xFFFF) {
        uvDobjModel(sOilObjId, MODEL_OIL_SPRAY);
        uvDobjState(sOilObjId, 0);
        sOilProxId = proxAnimAddCallback(oil_80315C84, oil_80315BB8, pos, 300.0f, 0.0f, 0);
        sOilScale = 0.0f;
    }
}

void oilDeinit(void) {
    if (sOilObjId != 0xFFFF) {
        uvDobjModel(sOilObjId, 0xFFFF);
        sOilObjId = 0xFFFF;
        proxAnimDeleteCallback(sOilProxId);
    }
}
