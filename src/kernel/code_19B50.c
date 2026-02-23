#include "common.h"
#include <uv_filesystem.h>
#include <uv_graphics.h>
#include <uv_memory.h>
#include <libc/stdarg.h>

typedef struct Unk80269F50 {
    u8 unk0;
    u8 unk1;
    f32 unk4;
    ParsedUVSQ unk8;
} Unk80269F50;

void func_8021902C(s32);

Unk80269F50 D_80269F50[10];

void func_80218BA0(void) {
    s32 i;

    for (i = 0; i < 10; i++) {
        D_80269F50[i].unk0 = 0;
        D_80269F50[i].unk1 = 0;
        D_80269F50[i].unk4 = 0;
        D_80269F50[i].unk8.count = 0;
        D_80269F50[i].unk8.unk4 = NULL;
        D_80269F50[i].unk8.unk8 = 0;
        D_80269F50[i].unk8.unk9 = 0;
        D_80269F50[i].unk8.unkC = 1.0f;
    }
}

void func_80218CA4(void) {
    s32 i;

    for (i = 0; i < 10; i++) {
        if (D_80269F50[i].unk0 != 0) {
            func_8021902C(i);
        }
    }
}

void uvSeqModel(s32 arg0, s32 seqId) {
    Unk80269F50* temp_v0;
    ParsedUVSQ* temp_a3;

    temp_a3 = gGfxUnkPtrs->sequences[seqId];
    if (temp_a3 == NULL) {
        _uvDebugPrintf("uvSeqModel: sequence %d not in level\n", seqId);
        return;
    }
    temp_v0 = &D_80269F50[arg0];
    temp_v0->unk0 = 1;
    if (temp_a3->unk9 == 1) {
        temp_v0->unk1 = temp_a3->count - 1;
    } else {
        temp_v0->unk1 = 0;
    }
    if (temp_a3->count != 0) {
        temp_v0->unk4 = temp_a3->unk4[temp_v0->unk1].unk4;
    }
    _uvMediaCopy(&temp_v0->unk8, temp_a3, sizeof(ParsedUVSQ));
}

void uvSeqProps(s32 arg0, ...) {
    Unk80269F50* temp_s3;
    s32 temp_v0;
    s32 temp_a1;
    ParsedUVSQ* temp_v1;
    va_list args;

    temp_s3 = &D_80269F50[arg0];
    temp_v1 = &temp_s3->unk8;
    if ((temp_s3 == NULL) || (temp_v1 == NULL)) {
        _uvDebugPrintf("uvSeqProps: invalid object id %d\n", arg0);
        return;
    }
    va_start(args, arg0);
    while (TRUE) {
        temp_a1 = va_arg(args, s32);
        switch (temp_a1) {
        case 0:
            return;
        case 1:
            temp_s3->unk0 = va_arg(args, s32);
            break;
        case 3:
            temp_v0 = va_arg(args, s32);
            if (temp_v0 >= temp_v1->count) {
                // FAKE
                if (temp_v1) { }
                _uvDebugPrintf("uvSeqProps: CURFRM past bounds\n");
            } else {
                temp_s3->unk1 = temp_v0;
            }
            break;
        case 2:
            temp_v1->unk8 = va_arg(args, s32);
            break;
        case 5:
            temp_v1->unk9 = va_arg(args, s32);
            temp_s3->unk1 = temp_v1->count - 1;
            break;
        case 4:
            temp_v1->unkC = va_arg(args, f64);
            break;
        default:
            _uvDebugPrintf("uvSeqProps: property has unknown type (%d)\n", temp_a1);
            break;
        }
    }
}

s32 func_80218F88(void) {
    s32 i;

    for (i = 0; i < 10; i++) {
        if (D_80269F50[i].unk0 == 0) {
            return i;
        }
    }

    return 0xFF;
}

void func_8021902C(s32 arg0) {
    Unk80269F50* temp_a0;
    ParsedUVSQ* temp_a1;

    temp_a0 = &D_80269F50[arg0];
    temp_a1 = &temp_a0->unk8;
    temp_a0->unk4 -= temp_a1->unkC * uvGfxGetUnkStateF();

    if (temp_a0->unk4 > 0.0f) {
        return;
    }

    while (temp_a0->unk4 <= 0.0f) {
        switch (temp_a1->unk8) {
        case 0:
            if (temp_a1->unk9 == 0) {
                temp_a0->unk1 = (temp_a0->unk1 + 1) % temp_a1->count;
            } else {
                temp_a0->unk1 = ((temp_a0->unk1 + temp_a1->count) - 1) % temp_a1->count;
            }
            break;
        case 1:
            if (temp_a1->unk9 == 0) {
                temp_a0->unk1++;
                if (temp_a0->unk1 == temp_a1->count) {
                    temp_a0->unk0 = 0;
                    return;
                }
            } else {
                if (temp_a0->unk1 == 0) {
                    temp_a0->unk0 = 0;
                    return;
                }
                temp_a0->unk1--;
            }

            break;
        case 2:
            if (temp_a1->unk9 == 0) {
                temp_a0->unk1++;
                if (temp_a0->unk1 + 1 == temp_a1->count) {
                    temp_a1->unk9 = 1;
                }
            } else {
                temp_a0->unk1--;
                if (temp_a0->unk1 == 0) {
                    temp_a1->unk9 = 0;
                }
            }
            break;
        default:
            break;
        }
        temp_a0->unk4 += temp_a1->unk4[temp_a0->unk1].unk4;
    }
}

u16 func_80219240(s32 arg0) {
    Unk80269F50* temp_v1;

    temp_v1 = &D_80269F50[arg0];
    return temp_v1->unk8.unk4[temp_v1->unk1].unk0;
}
