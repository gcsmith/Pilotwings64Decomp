#include "common.h"
#include <uv_audio.h>
#include <uv_dobj.h>
#include <uv_texture.h>
#include "code_9A960.h"
#include "game.h"
#include "hover_pads.h"
#include "hud.h"
#include "snd.h"
#include "task.h"

#define INVALID_OBJECT_ID 0xFFFF

s32 gHoverPadModels[2] = { MODEL_RB_HOVERPAD_LARGE, MODEL_RB_HOVERPAD_STANDARD };

STATIC_DATA TaskHPAD* sRefHPAD;
STATIC_DATA u8 sHoverPadCount;
HoverPad gHoverPads[20];

// forward declarations
void hoverPadObjSetup(HoverPad*);

void hoverPadInit(void) {
    HoverPad* hover;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gHoverPads); i++) {
        hover = &gHoverPads[i];
        hover->objId = INVALID_OBJECT_ID;
        hover->wasLandedOn = FALSE;
        hover->active = FALSE;
        hover->unk6C = 0;
        hover->initialized = FALSE;
        hover->unk64 = 0.0f;
    }
}

void hoverPad_80309868(void) {
    s32 i;

    for (i = 0; i < sHoverPadCount; i++) {
        if (D_80362690->unkC[D_80362690->unk9C].unk8 == sRefHPAD[i].unk18) {
            gHoverPads[i].unk6A = TRUE;
            if (gHoverPads[i].objId != INVALID_OBJECT_ID) {
                uvDobjSetState(gHoverPads[i].objId, 3);
            }
            if (gHoverPads[i].radarIdx != 0xFF) {
                hud_8031A874(gHoverPads[i].radarIdx);
            }
        } else {
            gHoverPads[i].unk6A = FALSE;
            if (gHoverPads[i].objId != INVALID_OBJECT_ID) {
                uvDobjClearState(gHoverPads[i].objId, 3);
            }
            if (gHoverPads[i].radarIdx != 0xFF) {
                hud_8031A810(gHoverPads[i].radarIdx);
            }
        }
    }
}

void hoverPadObjSetup(HoverPad* hover) {
    hover->objId = uvDobjAllocIdx();
    if (hover->active) {
        if (hover->type > 1) {
            _uvDebugPrintf("Bad hpad type %d\n", hover->type);
            hover->type = 1;
        }
        uvDobjModel(hover->objId, gHoverPadModels[hover->type]);
    } else {
        uvDobjModel(hover->objId, MODEL_RB_HOVERPAD_LOCKED);
    }
    uvDobjState(hover->objId, (hover->unk6A) ? 3 : 0);
    uvDobjPosm(hover->objId, 0, &hover->pose);
}

void hoverPadLoad(void) {
    HoverPad* hover;
    TaskHPAD* hpad;
    s32 i;
    s32 j;

    if (D_80362690->unkA0 == 0) {
        return;
    }

    sHoverPadCount = taskGetHPAD(&sRefHPAD);
    if (sHoverPadCount > ARRAY_COUNT(gHoverPads)) {
        _uvDebugPrintf("hpads : too many hpads defined in level [%d]\n", sHoverPadCount);
        sHoverPadCount = 0;
        return;
    }

    if (sHoverPadCount == 0) {
        return;
    }

    uvLevelAppend(0x13);
    for (i = 0; i < sHoverPadCount; i++) {
        hover = &gHoverPads[i];
        hpad = &sRefHPAD[i];
        if (hover->wasLandedOn) {
            continue;
        }
        if (!hover->initialized) {
            hover->type = hpad->type;
            hover->active = hpad->active;
            hover->nextHoverPadCount = hpad->nextHpadCount;
            hover->points = hpad->points;
            hover->fuelAdded = hpad->fuelAdded;

            for (j = 0; j < hover->nextHoverPadCount; j++) {
                hover->nextHoverPads[j] = hpad->nextHpads[j];
            }

            if ((hover->active) && (hover->nextHoverPadCount > 0)) {
                hover->unk6C = 1;
            }
            func_80313640(hpad->pos.x, hpad->pos.y, hpad->pos.z, hpad->rot.x * 0.0174533f, hpad->rot.y * 0.0174533f, hpad->rot.z * 0.0174533f,
                          &hover->pose); // DEG_TO_RAD(1)
            hover->initialized = TRUE;
            if (hover->active) {
                hover->radarIdx = hudAddWaypoint(hpad->pos.x, hpad->pos.y, hpad->pos.z);
            }
        }
        hoverPadObjSetup(hover);
    }
    hoverPad_80309868();
}

void hoverPadActivateNext(s32 hoverIdx) {
    HoverPad* hover;
    HoverPad* nextHover;
    s32 i;
    s32 idx;

    hover = &gHoverPads[hoverIdx];
    hover->unk6C = 0;
    for (i = 0; i < hover->nextHoverPadCount; i++) {
        idx = hover->nextHoverPads[i];
        nextHover = &gHoverPads[idx];
        if (nextHover->active) {
            continue;
        }

        if (nextHover->wasLandedOn) {
            continue;
        }

        nextHover->active = TRUE;
        nextHover->unk6C = 1;
        if (nextHover->objId != INVALID_OBJECT_ID) {
            uvDobjModel(nextHover->objId, 0xFFFF);
        }
        hoverPadObjSetup(nextHover);
        nextHover->radarIdx = hudAddWaypoint(nextHover->pose.m[3][0], nextHover->pose.m[3][1], nextHover->pose.m[3][2]);
    }
}

void hoverPadFrameUpdate(UNUSED Mtx4F* arg0) {
}

void hoverPadLanded(s32 hoverIdx) {
    u8 emitterId;
    HoverPad* hover;

    hover = &gHoverPads[hoverIdx];
    if (hover->objId != INVALID_OBJECT_ID) {
        emitterId = uvEmitterLookup();
        uvEmitterFromModel(emitterId, 0x3E);
        // clang-format off
        uvEmitterProps(emitterId,
            EMITTER_PROP_NEAR(0.0f),
            EMITTER_PROP_FAR(500.0f),
            EMITTER_PROP_ATTR(EMITTER_ATTR_INIT | EMITTER_ATTR_ONESHOT | EMITTER_ATTR_8),
            EMITTER_PROP_END
        );
        // clang-format on
        uvEmitterSetMatrix(emitterId, &hover->pose);
        uvEmitterTrigger(emitterId);
        uvDobjModel(hover->objId, 0xFFFF);
        hover->objId = INVALID_OBJECT_ID;
        hover->wasLandedOn = TRUE;
        hover->active = FALSE;
    }
    if (hover->radarIdx != 0xFF) {
        hud_8031A8E0(hover->radarIdx);
        hover->radarIdx = 0xFF;
    }
}

f32 hoverPadGetAltitude(s32 hoverIdx) {
    if (gHoverPads[hoverIdx].objId == INVALID_OBJECT_ID) {
        return 0.0f;
    } else {
        return gHoverPads[hoverIdx].pose.m[3][2];
    }
}

f32 hoverPadGetFuel(s32 hoverIdx) {
    if (gHoverPads[hoverIdx].objId == INVALID_OBJECT_ID) {
        return 0.0f;
    } else {
        sndPlaySfx(SFX_UI_FUEL_ADDED);
        return gHoverPads[hoverIdx].fuelAdded;
    }
}

s32 hoverPadGetLandedIdx(s32 objId, UNUSED f32 arg1) {
    HoverPad* hover;
    Unk80362690_Unk0* unkC;
    s32 i;
    s32 hoverIdx;
    f32 dx, dy, dz;
    f32 sum;

    hoverIdx = -1;
    unkC = &D_80362690->unkC[D_80362690->unk9C];
    for (i = 0; i < sHoverPadCount; i++) {
        hover = &gHoverPads[i];
        if ((hover->objId != INVALID_OBJECT_ID) && (objId == hover->objId)) {
            dx = hover->pose.m[3][0] - unkC->unk2C.m[3][0];
            dy = hover->pose.m[3][1] - unkC->unk2C.m[3][1];
            dz = hover->pose.m[3][2] - unkC->unk2C.m[3][2];
            sum = dx * hover->pose.m[2][0] + dy * hover->pose.m[2][1] + dz * hover->pose.m[2][2];
            if (sum < 0.0f) {
                if (hover->active) {
                    hoverIdx = i;
                }
                break;
            }
        }
    }
    return hoverIdx;
}

void hoverPadDeinit(void) {
    s32 i;
    for (i = 0; i < sHoverPadCount; i++) {
        if (gHoverPads[i].objId != INVALID_OBJECT_ID) {
            uvDobjModel(gHoverPads[i].objId, 0xFFFF);
            gHoverPads[i].objId = INVALID_OBJECT_ID;
        }
    }
}

u8 hoverPadGetCount(void) {
    u8 ret;
    s32 i;

    ret = 0;
    for (i = 0; i < sHoverPadCount; i++) {
        ret += (gHoverPads[i].wasLandedOn) ? 1 : 0;
    }
    return ret;
}

s16 hoverPadGetPoints(void) {
    s32 points;
    s32 i;

    points = 0;
    for (i = 0; i < sHoverPadCount; i++) {
        points += (gHoverPads[i].wasLandedOn) ? gHoverPads[i].points : 0;
    }
    return points;
}

