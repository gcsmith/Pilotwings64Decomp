#include "common.h"
#include "code_9A960.h"
#include "fdr.h"

#define FDR_SIZE 200

typedef struct Unk8035B5B0 {
    f32 unk0;
    f32 xStickData;
    f32 yStickData;
    struct Unk8035B5B0* next;
} Unk8035B5B0; // size = 0x10

typedef struct Unk8035C238 {
    f32 unk0;
    Mtx4F unk4;
    u16 unk44;
    struct Unk8035C238* next;
} Unk8035C238; // size = 0x4C

typedef struct Unk8035FDA0 {
    f32 unk0;
    f32 unk4[7];
    struct Unk8035FDA0* next;
} Unk8035FDA0; // size = 0x24

typedef struct {
    f32 unk0;
    s32 unk4;
} Unk8035AF70; // size = 0x8

typedef struct {
    f32 unk0;
    u8 unk4;
} Unk803619C8; // size = 0x8

s32 D_8034F0A0 = 0; // some bool flag
s32 D_8034F0A4 = 0; // index for D_8035AF70
s32 D_8034F0A8 = 0;
s32 D_8034F0AC = 0;
f32 pad_D_8034F0B0 = 1.0f;

s32 D_8035AF60; // vehicle id?
u8 D_8035AF64;  // state
f32 D_8035AF68;
Unk8035AF70 D_8035AF70[FDR_SIZE];
Unk8035B5B0 D_8035B5B0[FDR_SIZE];
Unk8035B5B0* D_8035C230;
Unk8035C238 D_8035C238[FDR_SIZE];
Unk8035C238* D_8035FD98;
Unk8035FDA0 D_8035FDA0[FDR_SIZE];
Unk8035FDA0* D_803619C0;
Unk803619C8 D_803619C8[FDR_SIZE];
s32 D_80362008;

STATIC_FUNC void fdrControls(f32, f32);
STATIC_FUNC s32 fdrGetControls(f32*, f32*);
STATIC_FUNC void fdr_802E7214(Mtx4F*, u16);
STATIC_FUNC void fdr_802E73BC(s32);
STATIC_FUNC s32 fdr_802E7424(s32*);
STATIC_FUNC f32 fdrInterp(s32, f32, f32, f32, f32, f32);
STATIC_FUNC s32 fdr_802E6FB8(f32* arg0, u8 arg1);
STATIC_FUNC s32 fdr_802E75C0(u8*);
STATIC_FUNC void fdr_802E7550(u8 arg0);
STATIC_FUNC void fdr_802E6EE4(f32* arg0, u8 arg1);

void fdrInit(void) {
    D_8035AF64 = 0;
    D_8035AF68 = 0.0f;
    fdrSetBlen(1.0f);
}

void fdr_802E65AC(Mtx4F* arg0, u16* arg1, f32* arg2, f32* arg3, s32* arg4) {
    if (D_8035AF64 == 0) {
        return;
    }

    if (D_8035AF64 != 4) {
        D_8035AF68 += D_8034F854;
    }

    if (D_8035AF64 == 1) {
        D_8035AF60++;
        if (D_8035AF60 >= 2) {
            D_8034F0A0 = 1;
        } else {
            D_8034F0A0 = 0;
        }
        if (D_8034F0A0 != 0) {
            fdr_802E7214(arg0, *arg1);
            fdrControls(*arg2, *arg3);
            D_8035AF60 = 0;
        } else {
            D_8034F0A0 = 0;
        }
        fdr_802E73BC(*arg4);
        return;
    }
    if (D_8035AF64 == 3 || D_8035AF64 == 4) {
        fdrGetControls(arg2, arg3);
        fdr_802E7424(arg4);
        if (fdr_802E7278(arg0, arg1) == 0) {
            D_8035AF64 = 4;
        }
    }
}

void fdr_802E66DC(void) {
    D_8035AF60 = 1;
    D_8034F0A0 = 1;
}

void fdrSetBlen(f32 arg0) {
    s32 temp_ft5;
    s32 i;

    if (arg0 <= 0.0f || arg0 > 1.0f) {
        _uvDebugPrintf("fdr_setblen : invalid relative length [%f]\n", arg0);
        return;
    }
    temp_ft5 = arg0 * FDR_SIZE;
    for (i = 0; i < (temp_ft5 - 1); i++) {
        D_8035B5B0[i].next = &D_8035B5B0[i + 1];
        D_8035C238[i].next = &D_8035C238[i + 1];
        D_8035FDA0[i].next = &D_8035FDA0[i + 1];
    }
    D_8035C238[i].next = D_8035C238;
    D_8035B5B0[i].next = D_8035B5B0;
    D_8035FDA0[i].next = D_8035FDA0;
}

void fdr_802E682C(f32* arg0, u8 count, u8 arg2) {
    if (D_8034F0A0 != 0) {
        fdr_802E6EE4(arg0, count);
    }
    fdr_802E7550(arg2);
}

void fdr_802E6870(f32* arg0, u8 count, u8* arg2) {
    fdr_802E6FB8(arg0, count);
    if (arg2 != NULL) {
        fdr_802E75C0(arg2);
    }
}

void fdr_802E68B0(u8 arg0) {
    f32 var_fv0;
    s32 var_a0_2;
    s32 i;

    switch (arg0) {
    case 1:
        D_8035AF64 = 1;
        D_8035AF68 = 0.0f;
        D_8034F0A4 = 0;
        D_8034F0A8 = 0;
        D_80362008 = 0;
        D_8034F0AC = 0;
        D_8035FD98 = D_8035C238;
        D_8035C230 = D_8035B5B0;
        D_803619C0 = D_8035FDA0;
        D_8035AF60 = 2;
        for (i = 0; i < ARRAY_COUNT(D_8035FDA0); i++) {
            D_8035C238[i].unk0 = 1000000.0f;
            D_8035B5B0[i].unk0 = 1000000.0f;
            D_8035FDA0[i].unk0 = 1000000.0f;
        }
        for (i = 0; i < ARRAY_COUNT(D_8035AF70); i++) {
            D_8035AF70[i].unk0 = 1000000.0f;
        }
        return;
    case 3:
        var_fv0 = 1000000.0f;
        D_8035AF64 = 3;
        for (i = 0; i < ARRAY_COUNT(D_8035C238); i++) {
            if (D_8035C238[i].unk0 < var_fv0) {
                var_fv0 = D_8035C238[i].unk0;
                var_a0_2 = i;
            }
        }
        D_8035FD98 = &D_8035C238[var_a0_2]; // possible UB if var_a0_2 is never set
        D_8035C230 = &D_8035B5B0[var_a0_2];
        D_803619C0 = &D_8035FDA0[var_a0_2];
        D_8035AF68 = D_8035FD98->unk0;
        for (i = 0; i < ARRAY_COUNT(D_8035AF70) - 1; i++) {
            if ((D_8035AF70[i].unk0 <= var_fv0) && (var_fv0 <= D_8035AF70[i + 1].unk0)) {
                var_a0_2 = i;
                break;
            }
        }
        if (i >= ARRAY_COUNT(D_8035AF70) - 1) {
            var_a0_2 = 0;
        }
        D_8034F0A4 = var_a0_2;
        D_8034F0A8 = 0;
        for (i = 0; i < ARRAY_COUNT(D_803619C8) - 1; i++) {
            if ((D_803619C8[i].unk0 <= var_fv0) && (var_fv0 <= D_803619C8[i + 1].unk0)) {
                var_a0_2 = i;
                break;
            }
        }
        if (i >= ARRAY_COUNT(D_803619C8) - 1) {
            var_a0_2 = 0;
        }
        D_80362008 = var_a0_2;
        D_8034F0AC = 0;
        return;
    }
}

u8 fdr_802E6B5C(void) {
    return D_8035AF64;
}

f32 fdr_802E6B68(void) {
    return D_8035AF68;
}

STATIC_FUNC void fdrControls(f32 xStickData, f32 yStickData) {
    D_8035C230->unk0 = D_8035AF68;
    D_8035C230->xStickData = xStickData;
    D_8035C230->yStickData = yStickData;
    if (xStickData < -1.0f || xStickData > 1.0f) {
        _uvDebugPrintf("fdr_controls : bad x stick data :%f\n", xStickData);
    }
    if (yStickData < -1.0f || yStickData > 1.0f) {
        _uvDebugPrintf("fdr_controls : bad y stick data :%f\n", yStickData);
    }
    D_8035C230 = D_8035C230->next;
}

STATIC_FUNC s32 fdrGetControls(f32* xStickData, f32* yStickData) {
    Unk8035B5B0* next;
    Unk8035B5B0* current;
    s32 i;

    for (i = 0, current = D_8035C230; i < 201; i++) {
        if (D_8035AF68 < current->next->unk0) {
            break;
        }
        current = current->next;
    }

    D_8035C230 = current;
    next = current->next;
    if (i >= 201 || next->unk0 < current->unk0 || next->unk0 == 1000000.0f) {
        *xStickData = D_8035C230->xStickData;
        *yStickData = D_8035C230->yStickData;
        if (*xStickData < -1.0f || *xStickData > 1.0f) {
            _uvDebugPrintf("fdr_getcontrols(1) : bad x stick data :%f\n", *xStickData);
        }
        if (*yStickData < -1.0f || *yStickData > 1.0f) {
            _uvDebugPrintf("fdr_getcontrols(1) : bad y stick data :%f\n", *yStickData);
        }
        return 0;
    }
    *xStickData = fdrInterp(0, D_8035AF68, current->unk0, current->xStickData, next->unk0, next->xStickData);
    *yStickData = fdrInterp(1, D_8035AF68, current->unk0, current->yStickData, next->unk0, next->yStickData);
    if (*xStickData < -1.0f || *xStickData > 1.0f) {
        _uvDebugPrintf("fdr_getcontrols(1) : bad x stick data :%f\n", *xStickData);
    }
    if (*yStickData < -1.0f || *yStickData > 1.0f) {
        _uvDebugPrintf("fdr_getcontrols(1) : bad y stick data :%f\n", *yStickData);
    }

    return 1;
}

STATIC_FUNC void fdr_802E6EE4(f32* arg0, u8 arg1) {
    s32 i;

    D_803619C0->unk0 = D_8035AF68;
    for (i = 0; i < arg1; i++) {
        D_803619C0->unk4[i] = arg0[i];
    }
    D_803619C0 = D_803619C0->next;
}

STATIC_FUNC s32 fdr_802E6FB8(f32* arg0, u8 arg1) {
    Unk8035FDA0* current;
    Unk8035FDA0* next;
    s32 i; // sp44

    if (D_803619C0->unk0 < D_803619C0->next->unk0) {
        for (i = 0, current = D_803619C0; i < 201; i++, current = current->next) {
            // @fake
            if (1) { }
            if (D_8035AF68 < current->next->unk0) {
                break;
            }
        }
        D_803619C0 = current;
        next = current->next;
    } else {
        current = D_803619C0;
        next = current->next;
    }

    if (i >= 201 || next->unk0 < current->unk0 || next->unk0 == 1000000.0f) {
        for (i = 0; i < arg1; i++) {
            arg0[i] = D_803619C0->unk4[i];
        }
        return 0;
    }

    for (i = 0; i < arg1; i++) {
        arg0[i] = fdrInterp(2, D_8035AF68, current->unk0, current->unk4[i], next->unk0, next->unk4[i]);
    }
    return 1;
}

STATIC_FUNC void fdr_802E7214(Mtx4F* arg0, u16 arg1) {
    D_8035FD98->unk0 = D_8035AF68;
    D_8035FD98->unk44 = arg1;
    uvMat4Copy(&D_8035FD98->unk4, arg0);
    D_8035FD98 = D_8035FD98->next;
}

s32 fdr_802E7278(Mtx4F* arg0, u16* arg1) {
    Unk8035C238* next;
    Unk8035C238* current;
    s32 i;
    f32 temp;

    if (D_8035FD98->unk0 < D_8035FD98->next->unk0) {
        for (i = 0, current = D_8035FD98; i <= FDR_SIZE; i++, current = current->next) {
            if (D_8035AF68 < current->next->unk0) {
                break;
            }
        }
        D_8035FD98 = current;
        next = current->next;
    } else {
        current = D_8035FD98;
        next = current->next;
    }
    if ((i > FDR_SIZE) || next->unk0 < current->unk0 || next->unk0 == 1000000.0f) {
        uvMat4Copy(arg0, &D_8035FD98->unk4);
        *arg1 = D_8035FD98->unk44;
        return 0;
    }
    temp = (D_8035AF68 - current->unk0) / (next->unk0 - current->unk0);
    func_803138A0(arg0, &current->unk4, &next->unk4, temp);
    *arg1 = next->unk44;
    return 1;
}

STATIC_FUNC void fdr_802E73BC(s32 arg0) {
    Unk8035AF70* temp_v1;
    if (arg0 == D_8034F0A8) {
        return;
    }

    D_8034F0A8 = arg0;
    // @fake
    if (1) { }
    if (D_8034F0A4 == ARRAY_COUNT(D_8035AF70)) {
        D_8034F0A4 = 0;
        return;
    }

    temp_v1 = &D_8035AF70[D_8034F0A4];
    temp_v1->unk0 = D_8035AF68;
    temp_v1->unk4 = arg0;
    D_8034F0A4++;
}

STATIC_FUNC s32 fdr_802E7424(s32* arg0) {
    Unk8035AF70* current;
    Unk8035AF70* next;
    s32 i;

    current = &D_8035AF70[D_8034F0A4];
    if (D_8034F0A4 < 199) {
        next = &D_8035AF70[D_8034F0A4 + 1];
    } else {
        next = D_8035AF70;
    }

    if (current->unk0 == 1000000.0f) {
        *arg0 = 0;
        return 0;
    }

    if (next->unk0 < current->unk0) {
        *arg0 = 0;
        return 0;
    }

    if (D_8035AF68 < current->unk0) {
        *arg0 = D_8034F0A8;
        return 1;
    }

    for (i = D_8034F0A4; i < ARRAY_COUNT(D_8035AF70); i++) {
        if ((D_8035AF70[i].unk0 <= D_8035AF68)) {
            break;
        }
    }

    if (i == ARRAY_COUNT(D_8035AF70)) {
        D_8034F0A4 = 0;
    } else {
        D_8034F0A4++;
        D_8034F0A8 = D_8035AF70[i].unk4;
        *arg0 = D_8034F0A8;
    }

    return 1;
}

STATIC_FUNC void fdr_802E7550(u8 arg0) {
    Unk803619C8* temp_v1;
    if (D_8034F0AC == arg0) {
        return;
    }
    // @fake
    if (1) {
        D_8034F0AC = arg0;
    }
    if (D_80362008 == ARRAY_COUNT(D_803619C8)) {
        D_80362008 = 0;
        return;
    }
    temp_v1 = &D_803619C8[D_80362008];
    temp_v1->unk0 = D_8035AF68;
    temp_v1->unk4 = arg0;
    D_80362008 += 1;
}

STATIC_FUNC s32 fdr_802E75C0(u8* arg0) {
    Unk803619C8* current;
    Unk803619C8* next;
    s32 i;

    current = &D_803619C8[D_80362008];
    if (D_80362008 < ARRAY_COUNT(D_803619C8) - 1) {
        next = &D_803619C8[D_80362008 + 1];
    } else {
        next = D_803619C8;
    }

    if (current->unk0 == 1000000.0f) {
        *arg0 = 0;
        return 0;
    }

    if (D_8035AF68 < current->unk0) {
        *arg0 = D_8034F0AC;
        return 1;
    }

    if (next->unk0 < current->unk0) {
        *arg0 = current->unk4;
        return 0;
    }

    for (i = D_80362008; i < ARRAY_COUNT(D_803619C8); i++) {
        if ((D_803619C8[i].unk0 <= D_8035AF68)) {
            break;
        }
    }

    if (i == ARRAY_COUNT(D_803619C8)) {
        D_80362008 = 0;
    } else {
        D_80362008++;
        D_8034F0AC = D_803619C8[i].unk4;
        *arg0 = D_8034F0AC;
    }

    return 1;
}

STATIC_FUNC f32 fdrInterp(s32 arg0, f32 ct, f32 pt, f32 arg3, f32 nt, f32 arg5) {
    f32 temp_fv1;

    if ((ct < pt) || (nt < ct)) {
        _uvDebugPrintf("fdr_interp [%d] -- alpha out of range [ pt:%f ct:%f nt:%f ]\n", arg0, pt, ct, nt);
    }

    temp_fv1 = (ct - pt) / (nt - pt);
    return (temp_fv1 * arg5) + ((1.0f - temp_fv1) * arg3);
}
