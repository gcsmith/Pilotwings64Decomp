#include "common.h"
#include "code_BD670.h"
#include "spath.h"
#include "proxanim.h"
#include <uv_vector.h>
#include <uv_dobj.h>

typedef struct {
    s32 objId;
    f32 unk4;
} Unk80371DB0;
Unk80371DB0 D_80371DB0[20];
s32 D_80371E50;
s32 D_80371E54;
s32 D_80371E58;

STATIC_FUNC void func_80336140(void) {
    s32 i;
    Mtx4F sp64;

    for (i = 0; i < ARRAY_COUNT(D_80371DB0); i++) {
        if (D_80371DB0[i].objId != 0xFFFF) {
            D_80371DB0[i].unk4 += 0.03f;
            if (D_80371DB0[i].unk4 >= 100.0f) {
                D_80371DB0[i].unk4 -= 100.0f;
            }
            spath_update2(&sp64, D_80371E58, D_80371DB0[i].unk4, 1.0f, 512.0f);
            uvDobjPosm(D_80371DB0[i].objId, 0, &sp64);
        }
    }
}

STATIC_FUNC s32 func_80336248(s32 arg0, s32 arg1, s32 arg2) {
    s32 i;

    switch (arg1) {
    case 0:
        break;
    case 2:
        for (i = 0; i < ARRAY_COUNT(D_80371DB0); i++) {
            uvDobjState(D_80371DB0[i].objId, 0);
        }
        break;
    case 3:
        for (i = 0; i < ARRAY_COUNT(D_80371DB0); i++) {
            uvDobjState(D_80371DB0[i].objId, 3);
        }
        break;
    }

    return 0;
}

STATIC_FUNC s32 func_803362EC(s32 arg0, s32 arg1, s32 arg2) {
    s32 i;
    s32 sp20;

    sp20 = 0;
    if (func_80321420(arg0) > 1500.0f) {
        if (D_80371E54 != 0) {
            func_80336140();
            D_80371E54 = 0;
        } else {
            sp20 = 2;
            for (i = 0; i < ARRAY_COUNT(D_80371DB0); i++) {
                uvDobjState(D_80371DB0[i].objId, 0);
            }
        }
    } else {
        if (D_80371E54 == 0) {
            D_80371E54 = 1;
            for (i = 0; i < ARRAY_COUNT(D_80371DB0); i++) {
                uvDobjState(D_80371DB0[i].objId, 3);
            }
        }
        func_80336140();
    }
    return sp20;
}

void func_803363E0(void) {
    Unk80371DB0* var_s0;
    Vec3F sp50 = { -207.927f, -897.804f, 112.643f };
    s32 i;

    D_80371E58 = func_80340668(4);
    D_80371E50 = func_80321210(func_803362EC, func_80336248, sp50, 1500.0f, 0.0f, 0);
    for (i = 0; i < ARRAY_COUNT(D_80371DB0); i++) {
        D_80371DB0[i].objId = uvDobjAllocIdx();
        if (D_80371DB0[i].objId != 0xFFFF) {
            D_80371DB0[i].unk4 = (i / 20.0f) * 100.0f;
            uvDobjModel(D_80371DB0[i].objId, 0xA7);
            uvDobjState(D_80371DB0[i].objId, 3);
            func_80336140();
        }
    }
}

void func_8033651C(void) {
    s32 i;

    spath_free(D_80371E58);
    func_803212DC(D_80371E50);
    for (i = 0; i < ARRAY_COUNT(D_80371DB0); i++) {
        if (D_80371DB0[i].objId != 0xFFFF) {
            uvDobjModel(D_80371DB0[i].objId, MODEL_WORLD);
            D_80371DB0[i].objId = 0xFFFF;
        }
    }
}

