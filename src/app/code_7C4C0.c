#include "common.h"
#include <uv_event.h>
#include <uv_fx.h>
#include <uv_janim.h>
#include <uv_model.h>
#include "code_7C4C0.h"
#include "app/fdr.h"
#include "app/shadow.h"
#include "app/snd.h"
#include "app/code_7FE00.h"
#include "app/code_9A960.h"

Unk80371120 D_80368370;
Unk80371120 D_80368520;
Unk80371120 D_803686D0;

void func_802F5358(GyrocopterData*);

void func_802F4F90(void) {
}

void func_802F4F98(GyrocopterData* arg0) {
    arg0->unk660 = func_8021EFF0(3);
    uvModelGet(arg0->unk660, 3);
    arg0->unk661 = func_8021EFF0(3);
    uvModelGet(arg0->unk661, 3);
    // clang-format off
    uvFxProps(
        arg0->unk660,
        FX_PROP_5(arg0->unk578, arg0->unk57C, arg0->unk580, 1.0f),
        FX_PROP_3(arg0->unk594, arg0->unk594, arg0->unk594),
        FX_PROP_END
    );
    uvFxProps(
        arg0->unk661,
        FX_PROP_5(arg0->unk584, arg0->unk588, arg0->unk58C, 1.0f),
        FX_PROP_3(arg0->unk5A8, arg0->unk5A8, arg0->unk5A8),
        FX_PROP_END
    );
    // clang-format on
    arg0->unk662 = 0;
    arg0->unk663 = 0;
    arg0->unkE4 = -1.0f;
    arg0->unk664 = 0.0f;
}

void func_802F50CC(GyrocopterData* arg0) {
    Mtx4F sp28;
    f32 sp24;

    if (arg0->objId != 0xFFFF) {
        func_802F5358(arg0);
        sp24 = (arg0->unkAC * 0.5f) + (0.5f * arg0->unk9C);
        uvModelGetPosm(arg0->modelId, arg0->unk570, &sp28);
        uvMat4RotateAxis(&sp28, 1.0471975f * sp24, 'z');
        uvDobjPosm(arg0->objId, arg0->unk570, &sp28);
        sp24 = arg0->unkA0;
        uvModelGetPosm(arg0->modelId, arg0->unk571, &sp28);
        uvMat4RotateAxis(&sp28, 0.3490658f * sp24, 'x');
        uvDobjPosm(arg0->objId, arg0->unk571, &sp28);
        func_80200EC0(arg0->objId, arg0->unk590, (arg0->unkA0 + 1.0f) * 0.5f, (arg0->unk9C + 1.0f) * 0.5f);
        uvModelGetPosm(arg0->modelId, arg0->unk572, &sp28);
        uvMat4RotateAxis(&sp28, (arg0->unk9C * -0.5f) + arg0->unkB8, 'z');
        uvMat4RotateAxis(&sp28, (arg0->unkA0 * 0.5f) + arg0->unkBC, 'x');
        uvDobjPosm(arg0->objId, arg0->unk572, &sp28);
        if ((arg0->unkC0 != 3) && ((arg0->unkC1 == 8) || (arg0->unkC1 == 1)) && (arg0->unk1A8 > 4.0f) && ((D_8034F850 - arg0->unkE4) > 1.0f)) {
            func_802F8B0C(arg0->unk10.m[3][0], arg0->unk10.m[3][1], arg0->unk10.m[3][2], 4.0f);
            arg0->unkE4 = D_8034F850;
        }
    }
}

void func_802F5304(GyrocopterData* arg0) {
    uvModelGet(arg0->unk660, 0xFF);
    arg0->unk660 = 0xFF;
    uvModelGet(arg0->unk661, 0xFF);
    arg0->unk661 = 0xFF;
    arg0->unk662 = 0;
}

void func_802F5358(GyrocopterData* arg0) {
    Mtx4F sp50;
    f32 var_fs0;

    arg0->unkF4 += arg0->unkF0 * D_8034F854;
    arg0->unkEC += arg0->unkE8 * D_8034F854;
    if (arg0->unk5D == 0) {
        var_fs0 = 0.0f;
    } else {
        var_fs0 = (arg0->unkE8 - 15.0f) / 10.0f;
        if (var_fs0 < 0.0f) {
            var_fs0 = 0.0f;
        } else if (var_fs0 > 1.0f) {
            var_fs0 = 1.0f;
        }
    }

    uvMat4Copy(&sp50, &arg0->unk10);
    uvMat4LocalTranslate(&sp50, arg0->unk59C.x, arg0->unk59C.y, arg0->unk59C.z);
    uvMat4RotateAxis(&sp50, arg0->unk598, 'x');
    uvFxProps(arg0->unk660, FX_PROP_5(arg0->unk578, arg0->unk57C, arg0->unk580, (var_fs0 * 0.6f)), FX_PROP_END);
    func_8021A4D8(arg0->unk660, &sp50);
    uvModelGetPosm(arg0->modelId, arg0->unk573, &sp50);
    uvMat4RotateAxis(&sp50, arg0->unkEC, 'z');
    uvDobjPosm(arg0->objId, arg0->unk573, &sp50);
    if (var_fs0 > 0.95f) {
        uvDobjProps(arg0->objId, 5, arg0->unk573, 0);
    } else {
        uvDobjProps(arg0->objId, 4, arg0->unk573, 0);
    }
    if (arg0->unk5D == 0) {
        var_fs0 = 0.0f;
    } else {
        var_fs0 = (arg0->unkF0 - 15.0f) / 10.0f;
        if (var_fs0 < 0.0f) {
            var_fs0 = 0.0f;
        } else if (var_fs0 > 1.0f) {
            var_fs0 = 1.0f;
        }
    }
    uvMat4Copy(&sp50, &arg0->unk10);
    uvMat4LocalTranslate(&sp50, arg0->unk5B0, arg0->unk5B4, arg0->unk5B8);
    uvMat4RotateAxis(&sp50, arg0->unk5AC, 'x');
    uvFxProps(arg0->unk661, FX_PROP_5(arg0->unk584, arg0->unk588, arg0->unk58C, (var_fs0 * 0.6f)), FX_PROP_END);
    func_8021A4D8(arg0->unk661, &sp50);
    if (var_fs0 > 0.95f) {
        uvDobjProps(arg0->objId, 5, arg0->unk574, 0);
    } else {
        uvDobjProps(arg0->objId, 4, arg0->unk574, 0);
    }
    uvModelGetPosm(arg0->modelId, arg0->unk574, &sp50);
    uvMat4RotateAxis(&sp50, -arg0->unkF4, 'y');
    uvDobjPosm(arg0->objId, arg0->unk574, &sp50);
}

void func_802F56B4(GyrocopterData* arg0, u8 arg1) {
    static f32 D_8034F370 = 0.0f;
    static f32 D_8034F374 = 0.5f;
    f32 var_fa1;
    u8 sp23;

    if ((fdr_802E6B5C() == 3) || (fdr_802E6B5C() == 4)) {
        arg0->usingFuel = FALSE;
        arg0->unkF0 = 0.0f;
        arg0->unkE8 = 0.0f;
        func_802F5358(arg0);
        return;
    }
    if (arg0->unk663 == 0) {
        if (arg1 != 0) {
            arg0->unk663 = 2;
        } else {
            arg0->unk663 = 1;
        }
        arg0->unk664 = 0.0f;
        D_8034F370 = 0.0f;
        D_8034F374 = 2.0f;
        uvDobj_802180DC(arg0->objId, &D_80368370);
    }

    var_fa1 = arg0->unk664 / 3.0f;
    // clang-format off
    if (var_fa1 < 0.0f) { var_fa1 = 0.0f; } else if (var_fa1 > 1.0f) { var_fa1 = 1.0f; }
    // clang-format on

    arg0->unk664 += D_8034F854;
    D_8034F370 += D_8034F374 * D_8034F854;
    if (D_8034F370 >= 1.0f) {
        if (D_8034F374 > 0.0f) {
            D_8034F374 = -D_8034F374;
            D_8034F370 = 1.0f;
        }
    }

    if (D_8034F370 <= 0.0f) {
        if (D_8034F374 < 0.0f) {
            D_8034F370 = 0.0f;
            D_8034F374 = -D_8034F374;
        }
    }

    switch (arg0->unk663) {
    case 2:
        sp23 = arg0->unk591;
        break;
    case 1:
        sp23 = arg0->unk592;
        break;
    }

    uvJanimPoseLine(&D_80368520, sp23, D_8034F370);
    func_802006FC(&D_803686D0, &D_80368370, &D_80368520, var_fa1);
    func_80200638(arg0->objId, &D_803686D0);
    arg0->usingFuel = FALSE;
    arg0->unkE8 = func_80313AF4(0.0f, arg0->unkE8, 0.5f);
    arg0->unkF0 = func_80313AF4(0.0f, arg0->unkF0, 0.5f);
    func_802F5358(arg0);
}

void func_802F5910(GyrocopterData* arg0) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv0;

    temp_fa0 = arg0->unk10.m[3][0];
    temp_fa1 = arg0->unk10.m[3][1];
    temp_fv0 = arg0->unk10.m[3][2];
    if (arg0->unk662 == 0) {
        arg0->unk662 = 1;
        if (arg0->unkD0 != 0) {
            sndPlaySfx(0x1A);
            uvEventPost(0x12, 0);
            func_802F8AB8(temp_fa0, temp_fa1, temp_fv0, 6.0f, &arg0->unk19C.x);
            arg0->unk2 |= 8;
            arg0->unk58->unk6 = arg0->unk2;
            uvDobjState(arg0->objId, arg0->unk2 | 8);
            shadow_803343D8(0);
        } else {
            func_802F9638(temp_fa0, temp_fa1, temp_fv0, 10.0f);
        }
    }
    arg0->usingFuel = FALSE;
    arg0->unkF0 = 0.0f;
    arg0->unkE8 = 0.0f;
    func_802F50CC(arg0);
}
