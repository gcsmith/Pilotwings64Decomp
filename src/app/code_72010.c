#include "common.h"
#include <uv_matrix.h>
#include "camera.h"
#include "code_72010.h"
#include "code_9A960.h"

void func_802EAAE0(Unk802D3658_Unk230* arg0) {
    s32 i;

    arg0->unkED8 = arg0->unk0;

    // setup next pointers
    for (i = 0; i < ARRAY_COUNT(arg0->unk0) - 1; i++) {
        arg0->unk0[i].next = &arg0->unk0[i + 1];
        uvMat4SetIdentity(&arg0->unk0[i].unk0);
    }
    arg0->unk0[i].next = &arg0->unk0[0];

    // setup prev pointers
    for (i = ARRAY_COUNT(arg0->unk0) - 1; i > 0; i--) {
        arg0->unk0[i].prev = &arg0->unk0[i - 1];
    }
    arg0->unk0[i].prev = &arg0->unk0[49];

    arg0->unkEDC = 0;
    arg0->unkEE0 = 0;
}

// init all matrices/vals to one provided
void func_802EABAC(Unk802D3658_Unk230* arg0, f32 arg1, Mtx4F* arg2) {
    Unk802D3658_Unk230_Unk0* it;
    s32 i;

    for (it = arg0->unk0, i = 0; i < ARRAY_COUNT(arg0->unk0); i++, it = it->next) {
        uvMat4Copy(&it->unk0, arg2);
        it->unk40 = arg1;
    }
}

// add matrix
void func_802EAC18(Unk802D3658_Unk230* arg0, f32 arg1, Mtx4F* arg2) {
    arg0->unkEE0++;
    arg0->unkED8 = arg0->unkED8->next;
    arg0->unkED8->unk40 = arg1;
    uvMat4Copy(&arg0->unkED8->unk0, arg2);
    if (arg0->unkEDC == 0) {
        func_802EABAC(arg0, arg1, arg2);
        arg0->unkEDC = 1;
    }
}

s32 func_802EAC9C(Unk802D3658_Unk230* arg0, f32 arg1, Mtx4F* arg2) {
    Unk802D3658_Unk230_Unk0* next;
    Unk802D3658_Unk230_Unk0* prev;
    f32 var_fv0;
    s32 i;

    if (arg0->unkEDC != 1) {
        return 0;
    }

    prev = arg0->unkED8->prev;
    for (i = 0; i < ARRAY_COUNT(arg0->unk0); i++) {
        if (arg1 > prev->unk40) {
            break;
        }
        prev = prev->prev;
    }

    next = prev->next;
    if (i == ARRAY_COUNT(arg0->unk0)) {
        uvMat4Copy(arg2, &arg0->unk0[0].unk0);
    } else {
        if (next->unk40 == prev->unk40) {
            var_fv0 = 0.0f;
        } else {
            var_fv0 = (arg1 - prev->unk40) / (next->unk40 - prev->unk40);
            if ((var_fv0 < 0.0f) || (var_fv0 > 1.0f)) {
                return 0;
            }
        }
        func_803138A0(arg2, &prev->unk0, &next->unk0, var_fv0);
    }

    return 1;
}
