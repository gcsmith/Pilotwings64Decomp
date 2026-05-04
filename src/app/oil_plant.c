#include "common.h"
#include <uv_fx.h>
#include <uv_model.h>
#include <uv_vector.h>
#include "hud.h"
#include "oil_plant.h"
#include "proxanim.h"
#include "task.h"

STATIC_DATA s32 sOilPlantRadarId = 0xFF;
STATIC_DATA s32 sOilPlantProximity = 0;
STATIC_DATA Vec3F sOilPlantPos = { -368.0f, 648.0f, 106.0f };

STATIC_DATA s32 sOilPlantProxId;
STATIC_DATA s32 sOilPlantSeqId;
STATIC_DATA s32 sOilPlantFxId;

void oilPlantInit(void) {
    sOilPlantProximity = FALSE;
}

s32 oilPlantInProximity(void) {
    return sOilPlantProximity;
}

STATIC_FUNC s32 oilPlantEventCb(UNUSED s32 proxId, s32 eventType, UNUSED s32 clientData) {
    switch (eventType) {
    case 0:
        break;
    case 2:
        if (sOilPlantRadarId != 0xFF) {
            hud_8031A874(sOilPlantRadarId);
        }
        uvFxProps(sOilPlantFxId, FX_PROP_3(0.0f, 0.0f, 0.0f), FX_PROP_END);
        break;
    case 3:
        if (sOilPlantRadarId != 0xFF) {
            hud_8031A874(sOilPlantRadarId);
        }
        uvFxProps(sOilPlantFxId, FX_PROP_3(25.0f, 1.0f, 35.0f), FX_PROP_END);
        break;
    }
    return 0;
}

STATIC_FUNC s32 oilPlantAnimCb(s32 proxId, UNUSED f32 timeout, UNUSED s32 clientData) {
    f32 range;
    s32 ret;

    ret = 0;
    range = proxAnimGetRange(proxId);
    if (range > 500.0f) {
        sOilPlantProximity = FALSE;
        ret = 2;
        uvFxProps(sOilPlantFxId, FX_PROP_3(0.0f, 0.0f, 0.0f), FX_PROP_END);
    } else {
        sOilPlantProximity = TRUE;
        uvFxProps(sOilPlantFxId, FX_PROP_3(25.0f, 1.0f, 35.0f), FX_PROP_END);
    }
    return ret;
}

void oilPlantLoad(void) {
    u16 cls;
    u16 veh;
    u16 test;
    s32 showHudWaypoint;
    Vec3F pos;

    pos = sOilPlantPos;
    sOilPlantSeqId = uvSeqFindFree();
    uvSeqModel(sOilPlantSeqId, 0);
    uvSeqProps(sOilPlantSeqId, SEQ_PROP_FRAMERATE(20.0f), SEQ_PROP_END);
    sOilPlantFxId = uvFx_8021EFF0(6);
    uvModelGet(sOilPlantFxId, 6);
    // clang-format off
    uvFxProps(sOilPlantFxId,
        FX_PROP_10(-368.0f, 648.0f, 106.0f),
        FX_PROP_13(sOilPlantSeqId),
        FX_PROP_1(1e20),
        FX_PROP_16(1),
        FX_PROP_3(0.0f, 0.0f, 0.0f),
        FX_PROP_END
    );
    // clang-format on
    sOilPlantProxId = proxAnimAddCallback(oilPlantAnimCb, oilPlantEventCb, pos, 500.0f, 0.0f, 6);
    taskGetClsVehTest(&cls, &veh, &test);
    showHudWaypoint = (test == 0 && cls == CLASS_A && veh == VEHICLE_HANG_GLIDER) || (test == 1 && cls == CLASS_B && veh == VEHICLE_HANG_GLIDER) ||
                      (test == 2 && cls == CLASS_PILOT && veh == VEHICLE_HANG_GLIDER);
    if (showHudWaypoint) {
        sOilPlantRadarId = hudAddWaypoint(-368.0f, 648.0f, 106.0f);
        return;
    }
    sOilPlantRadarId = 0xFF;
}

void oilPlantDeinit(void) {
    if (sOilPlantRadarId != 0xFF) {
        hud_8031A8E0(sOilPlantRadarId);
    }
    sOilPlantRadarId = 0xFF;
    uvSeqProps(sOilPlantSeqId, SEQ_PROP_ACTIVE(FALSE), SEQ_PROP_END);
    uvModelGet(sOilPlantFxId, 0xFF);
    uvFxProps(sOilPlantFxId, FX_PROP_11(0), FX_PROP_END);
    proxAnimDeleteCallback(sOilPlantProxId);
}

void oilPlantGetPos(Vec3F* pos) {
    pos->x = -368.0f;
    pos->y = 648.0f;
    pos->z = 118.0f;
}
