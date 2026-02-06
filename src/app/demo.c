#include "common.h"
#include <uv_controller.h>
#include <uv_math.h>
#include <uv_memory.h>
#include <uv_util.h>
#include "code_9A960.h"
#include "code_A7F20.h"
#include "demo.h"

typedef struct {
    s32 unk0;
    u8 pad4[4];
    s32 unk8;
    s32 unkC;
    s32 unk10;
} RHDR;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    u32 unkC;
} RPKT;

typedef struct Unk8036DA30 {
    struct Unk8036DA30* unk0;
    DemoRecordingEntry entries[0x708];
} DemoRecording;

extern s32 D_8034FAD0;
extern DemoRecording* D_8036DA30;
extern f32 D_8036DA34;
extern f32 D_8036DA38;
extern s32 D_8036DA3C;
extern s32 D_8036DA40;
extern s32 D_8036DA44;
extern s32 D_8036DA48;
extern RHDR D_8036DA50;

f32 demoRecGetStickX(DemoRecordingEntry* entry) {
    return (f32)(((f32)((entry->inputs & 0xFF000000) >> 24) / 127.0) - 1.0);
}

f32 demoRecGetStickY(DemoRecordingEntry* entry) {
    return (f32)(((f32)((entry->inputs & 0x00FF0000) >> 16) / 127.0) - 1.0);
}

u32 demoRecGetButtons(DemoRecordingEntry* entry) {
    return entry->inputs & 0x0000FFFF;
}

void demoPackInputs(DemoRecordingEntry* entry, f32 stickX, f32 stickY, u32 buttons) {
    entry->inputs = (u32)(((u32)((stickX + 1.0) * 127.0) << 0x18) | ((u32)((1.0 + stickY) * 127.0) << 0x10) | buttons);
}

s32 demo_803229EC(s32 arg0, s32 arg1) {
    if (arg1 < 0) {
        switch (arg0) {
        case 0:
            return 0x55;
        case 1:
            return 0x57;
        case 2:
            return 0x59;
        case 3:
            return 0x56;
        case 4:
            return 0x58;
        case 5:
            return 0x5A;
        default:
            return 0x55;
        }
    }

    switch (arg1) {
    case 0:
        switch (arg0) {
        case 0:
            return 0x5B;
        case 1:
            return 0x5D;
        case 2:
            return 0x5F;
        case 3:
            return 0x5C;
        case 4:
            return 0x5E;
        case 5:
            return 0x60;
        default:
            return 0x5B;
        }
    case 1:
        switch (arg0) {
        case 0:
            return 0x61;
        case 1:
            return 0x63;
        case 2:
            return 0x65;
        case 3:
            return 0x62;
        case 4:
            return 0x64;
        case 5:
            return 0x66;
        default:
            return 0x61;
        }
    default:
        switch (arg0) {
        case 0:
            return 0x67;
        case 1:
            return 0x69;
        case 2:
            return 0x6B;
        case 3:
            return 0x68;
        case 4:
            return 0x6A;
        case 5:
            return 0x6C;
        default:
            return 0x67;
        }
    }
}

s32 demoGet_80322B60(void) {
    return D_8036DA50.unk8;
}

s32 demoGet_80322B6C(void) {
    return D_8036DA50.unkC;
}

s32 demoGet_80322B78(void) {
    return D_8036DA50.unk10;
}

s32 demoGet_80322B84(void) {
    return D_8036DA50.unk0;
}

void demoAllocate(void) {
    DemoRecording* temp_v0;

    if ((D_8036DA30 == NULL) || (D_8036DA30 != D_8036DA30->unk0)) {
        temp_v0 = (DemoRecording*)_uvMemAllocAlign8(sizeof(DemoRecording));
        D_8036DA30 = temp_v0;
        D_8036DA30->unk0 = D_8036DA30;
    }
}

void demoInit(void) {
    DemoRecordingEntry* entry;
    s32 temp_s4;
    s32 idx;
    s32 done;
    u32 size;
    u32 tag;
    void* data;
    RPKT pkt;

    idx = 0;
    done = 0;
    demoAllocate();
    temp_s4 = func_80223E80((s32)func_802314D0(demo_803229EC(D_8036DA44, D_8036DA48), 2));
    uvMemSet(D_8036DA30->entries, 0, sizeof(D_8036DA30->entries));
    uvMemSet(&D_8036DA50, 0, sizeof(D_8036DA50));

    do {
        tag = func_80223F7C(temp_s4, &size, &data, 1);
        switch (tag) {
        case 'RPKT': // 0x52504B54
            _uvMediaCopy(&pkt, data, size);
            D_8036DA30->entries[idx].time = pkt.unk0;
            entry = &D_8036DA30->entries[idx];
            demoPackInputs(entry, pkt.unk4, pkt.unk8, pkt.unkC);
            idx++;
            break;
        case 'RHDR': // 0x52484452
            _uvMediaCopy(&D_8036DA50, data, size);
            break;
        case 0:
            if (tag && tag) { } // fakematch
            done = 1;
            break;
        }
    } while ((!done) && (idx < ARRAY_COUNT(D_8036DA30->entries)));
    func_80223F30(temp_s4);
}

s32 demo_80322D60(s32 arg0, s32 arg1) {
    s32 idx;
    D_8036DA44 = arg0;
    D_8036DA48 = arg1;
    demoInit();
    idx = demo_803229EC(D_8036DA44, D_8036DA48);
    return func_803209F0(idx);
}

void demoSetRecMode(s32 mode) {
    switch (mode) {
    case 1:
        _uvDebugPrintf("Beginning input recording\n");
        D_8036DA34 = D_8034F850;
        D_8036DA38 = D_8034F850 + 60.0f;
        D_8034FAD0 = mode;
        break;
    case 2:
        D_8036DA3C = 0;
        D_8036DA40 = 0;
        D_8036DA34 = D_8034F850;
        D_8036DA38 = D_8034F850 + 60.0f;
        D_8034FAD0 = mode;
        break;
    case 0:
        if (D_8034FAD0 == 1) {
            _uvDebugPrintf("End of recording\n");
        }
        D_8034FAD0 = mode;
        break;
    }
    D_8034FAD0 = mode;
    if (D_8034FAD0 != 0) {
        uvRandSeed(0xABCD2356);
    }
}

s32 demoGetRecMode(void) {
    return D_8034FAD0;
}

void demoLogInput(void) {
    if (D_8034FAD0 == 1) {
        _uvDebugPrintf("%.10f(%.10f, %.10f)0x%x\n", D_8034F850 - D_8036DA34, uvControllerGetStick(0, 0), uvControllerGetStick(0, 1), uvControllerGetButton(0));
    }
    if (D_8036DA38 <= D_8034F850) {
        demoSetRecMode(0);
    }
}

s32 demoGetEntryIndex(f32 curTime) {
    f32 temp_fv0;
    s32 var_v1;

    var_v1 = 0;
    temp_fv0 = curTime - D_8036DA34;

    for (var_v1 = 0; var_v1 < ARRAY_COUNT(D_8036DA30->entries); var_v1++) {
        if (temp_fv0 <= D_8036DA30->entries[var_v1].time) {
            return var_v1;
        }
    }
    return ARRAY_COUNT(D_8036DA30->entries) - 1;
}

s32 demo_80323020(void) {
    s32 idx;
    if (D_8034FAD0 == 2) {
        if ((D_8036DA30 == NULL) || (D_8036DA30 != D_8036DA30->unk0)) {
            demoInit();
        }
        D_8036DA3C = D_8036DA40;
        idx = demoGetEntryIndex(D_8034F850);
        D_8036DA40 = demoRecGetButtons(&D_8036DA30->entries[idx]);
    }
    return uvIOUpdate();
}

f32 demoGetInputs(s32 contIdx, s32 axis) {
    s32 idx;
    if (D_8034FAD0 == 2) {
        if ((D_8036DA30 == NULL) || (D_8036DA30 != D_8036DA30->unk0)) {
            demoInit();
        }
        if (axis == INPUT_AXIS_0) {
            idx = demoGetEntryIndex(D_8034F850);
            return demoRecGetStickX(&D_8036DA30->entries[idx]);
        } else {
            idx = demoGetEntryIndex(D_8034F850);
            return demoRecGetStickY(&D_8036DA30->entries[idx]);
        }
    } else {
        return uvControllerGetStick(contIdx, axis);
    }
}

s32 demoGetButtons(s32 contIdx) {
    if (D_8034FAD0 == 2) {
        return D_8036DA40;
    }
    return uvControllerGetButton(contIdx);
}

s32 demoButtonCheck(s32 contIdx, s32 buttonMask) {
    if (D_8034FAD0 == 2) {
        return buttonMask & D_8036DA40;
    }
    return uvControllerButtonCheck(contIdx, buttonMask);
}

int demoButtonPress(s32 contIdx, s32 buttonMask) {
    if (D_8034FAD0 == 2) {
        return demoButtonCheck(contIdx, buttonMask) == 0 && (buttonMask & D_8036DA3C) != 0;
    }
    return uvControllerButtonPress(contIdx, buttonMask);
}

int demoButtonRelease(s32 idx, s32 button) {
    if (D_8034FAD0 == 2) {
        return demoButtonCheck(idx, button) == 0 && (button & D_8036DA3C) != 0;
    }
    return uvControllerButtonRelease(idx, button);
}

f32 demoRandF(void) {
    f32 rng;
    if (D_8034FAD0 != 0) {
        rng = uvRandF_LCG();
    } else {
        rng = uvRandF_RANLUX();
    }
    return rng;
}
