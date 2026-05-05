#include "common.h"
#include <uv_filesystem.h>
#include <uv_fx.h>
#include <uv_graphics.h>
#include <uv_memory.h>
#include <libc/stdarg.h>

typedef struct uvSeqState {
    u8 active;
    u8 currFrame;
    f32 frameTime;
    ParsedUVSQ uvsq;
} uvSeqState; // size = 0x18

uvSeqState gSeqStateTable[10];

void uvSeqInit(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gSeqStateTable); i++) {
        gSeqStateTable[i].active = FALSE;
        gSeqStateTable[i].currFrame = 0;
        gSeqStateTable[i].frameTime = 0;
        gSeqStateTable[i].uvsq.frameCount = 0;
        gSeqStateTable[i].uvsq.frameTable = NULL;
        gSeqStateTable[i].uvsq.mode = UVSQ_MODE_REPEAT;
        gSeqStateTable[i].uvsq.reverse = FALSE;
        gSeqStateTable[i].uvsq.framerate = 1.0f;
    }
}

void uvSeqUpdateAll(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gSeqStateTable); i++) {
        if (gSeqStateTable[i].active != FALSE) {
            uvSeqUpdate(i);
        }
    }
}

void uvSeqModel(s32 seqId, s32 index) {
    uvSeqState* seq;
    ParsedUVSQ* uvsq = gGfxUnkPtrs->sequences[index];

    if (uvsq == NULL) {
        _uvDebugPrintf("uvSeqModel: sequence %d not in level\n", index);
        return;
    }
    seq = &gSeqStateTable[seqId];
    seq->active = TRUE;
    if (uvsq->reverse == TRUE) {
        seq->currFrame = uvsq->frameCount - 1;
    } else {
        seq->currFrame = 0;
    }
    if (uvsq->frameCount != 0) {
        seq->frameTime = uvsq->frameTable[seq->currFrame].frameTime;
    }
    _uvMediaCopy(&seq->uvsq, uvsq, sizeof(ParsedUVSQ));
}

void uvSeqProps(s32 seqId, ...) {
    uvSeqState* seq;
    s32 currFrame;
    s32 propId;
    ParsedUVSQ* uvsq;
    va_list args;

    seq = &gSeqStateTable[seqId];
    uvsq = &seq->uvsq;
    if ((seq == NULL) || (uvsq == NULL)) {
        _uvDebugPrintf("uvSeqProps: invalid object id %d\n", seqId);
        return;
    }
    va_start(args, seqId);
    while (TRUE) {
        propId = va_arg(args, s32);
        switch (propId) {
        case SEQ_PROPID_END:
            return;
        case SEQ_PROPID_ACTIVE:
            seq->active = va_arg(args, s32);
            break;
        case SEQ_PROPID_CURR_FRAME:
            currFrame = va_arg(args, s32);
            if (currFrame >= uvsq->frameCount) {
                // FAKE
                if (uvsq) { }
                _uvDebugPrintf("uvSeqProps: CURFRM past bounds\n");
            } else {
                seq->currFrame = currFrame;
            }
            break;
        case SEQ_PROPID_MODE:
            uvsq->mode = va_arg(args, s32);
            break;
        case SEQ_PROPID_REVERSE:
            uvsq->reverse = va_arg(args, s32);
            seq->currFrame = uvsq->frameCount - 1;
            break;
        case SEQ_PROPID_FRAMERATE:
            uvsq->framerate = va_arg(args, f64);
            break;
        default:
            _uvDebugPrintf("uvSeqProps: property has unknown type (%d)\n", propId);
            break;
        }
    }
}

s32 uvSeqFindFree(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gSeqStateTable); i++) {
        if (gSeqStateTable[i].active == FALSE) {
            return i;
        }
    }

    return 0xFF;
}

void uvSeqUpdate(s32 seqId) {
    uvSeqState* seq;
    ParsedUVSQ* uvsq;

    seq = &gSeqStateTable[seqId];
    uvsq = &seq->uvsq;
    seq->frameTime -= uvsq->framerate * uvGfxGetFrameTime();

    if (seq->frameTime > 0.0f) {
        return;
    }

    while (seq->frameTime <= 0.0f) {
        switch (uvsq->mode) {
        case UVSQ_MODE_REPEAT:
            if (uvsq->reverse == FALSE) {
                seq->currFrame = (seq->currFrame + 1) % uvsq->frameCount;
            } else {
                seq->currFrame = ((seq->currFrame + uvsq->frameCount) - 1) % uvsq->frameCount;
            }
            break;
        case UVSQ_MODE_ONESHOT:
            if (uvsq->reverse == FALSE) {
                seq->currFrame++;
                if (seq->currFrame == uvsq->frameCount) {
                    seq->active = FALSE;
                    return;
                }
            } else {
                if (seq->currFrame == 0) {
                    seq->active = FALSE;
                    return;
                }
                seq->currFrame--;
            }

            break;
        case UVSQ_MODE_STROBE:
            if (uvsq->reverse == FALSE) {
                seq->currFrame++;
                if (seq->currFrame + 1 == uvsq->frameCount) {
                    uvsq->reverse = TRUE;
                }
            } else {
                seq->currFrame--;
                if (seq->currFrame == 0) {
                    uvsq->reverse = FALSE;
                }
            }
            break;
        default:
            break;
        }
        seq->frameTime += uvsq->frameTable[seq->currFrame].frameTime;
    }
}

u16 uvSeqGetTextureId(s32 seqId) {
    uvSeqState* seq = &gSeqStateTable[seqId];
    return seq->uvsq.frameTable[seq->currFrame].textureId;
}

