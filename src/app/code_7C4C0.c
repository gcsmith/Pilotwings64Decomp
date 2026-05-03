#include "common.h"
#include <uv_audio.h>
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

void func_802F4F98(GyrocopterData* gcData) {
    gcData->unk660 = func_8021EFF0(3);
    uvModelGet(gcData->unk660, 3);
    gcData->unk661 = func_8021EFF0(3);
    uvModelGet(gcData->unk661, 3);
    // clang-format off
    uvFxProps(
        gcData->unk660,
        FX_PROP_5(gcData->unk578, gcData->unk57C, gcData->unk580, 1.0f),
        FX_PROP_3(gcData->unk594, gcData->unk594, gcData->unk594),
        FX_PROP_END
    );
    uvFxProps(
        gcData->unk661,
        FX_PROP_5(gcData->unk584, gcData->unk588, gcData->unk58C, 1.0f),
        FX_PROP_3(gcData->unk5A8, gcData->unk5A8, gcData->unk5A8),
        FX_PROP_END
    );
    // clang-format on
    gcData->unk662 = 0;
    gcData->unk663 = 0;
    gcData->unkE4 = -1.0f;
    gcData->unk664 = 0.0f;
}

void func_802F50CC(GyrocopterData* gcData) {
    Mtx4F sp28;
    f32 sp24;

    if (gcData->objId != 0xFFFF) {
        func_802F5358(gcData);
        sp24 = (gcData->unkAC * 0.5f) + (0.5f * gcData->unk9C);
        uvModelGetPosm(gcData->modelId, gcData->unk570, &sp28);
        uvMat4RotateAxis(&sp28, 1.0471975f * sp24, 'z');
        uvDobjPosm(gcData->objId, gcData->unk570, &sp28);
        sp24 = gcData->unkA0;
        uvModelGetPosm(gcData->modelId, gcData->unk571, &sp28);
        uvMat4RotateAxis(&sp28, 0.3490658f * sp24, 'x');
        uvDobjPosm(gcData->objId, gcData->unk571, &sp28);
        func_80200EC0(gcData->objId, gcData->unk590, (gcData->unkA0 + 1.0f) * 0.5f, (gcData->unk9C + 1.0f) * 0.5f);
        uvModelGetPosm(gcData->modelId, gcData->unk572, &sp28);
        uvMat4RotateAxis(&sp28, (gcData->unk9C * -0.5f) + gcData->unkB8, 'z');
        uvMat4RotateAxis(&sp28, (gcData->unkA0 * 0.5f) + gcData->unkBC, 'x');
        uvDobjPosm(gcData->objId, gcData->unk572, &sp28);
        if ((gcData->unkC0 != 3) && ((gcData->unkC1 == 8) || (gcData->unkC1 == 1)) && (gcData->unk1A8 > 4.0f) && ((D_8034F850 - gcData->unkE4) > 1.0f)) {
            func_802F8B0C(gcData->unk10.m[3][0], gcData->unk10.m[3][1], gcData->unk10.m[3][2], 4.0f);
            gcData->unkE4 = D_8034F850;
        }
    }
}

void func_802F5304(GyrocopterData* gcData) {
    uvModelGet(gcData->unk660, 0xFF);
    gcData->unk660 = 0xFF;
    uvModelGet(gcData->unk661, 0xFF);
    gcData->unk661 = 0xFF;
    gcData->unk662 = 0;
}

void func_802F5358(GyrocopterData* gcData) {
    Mtx4F sp50;
    f32 var_fs0;

    gcData->unkF4 += gcData->unkF0 * D_8034F854;
    gcData->unkEC += gcData->unkE8 * D_8034F854;
    if (gcData->unk5D == 0) {
        var_fs0 = 0.0f;
    } else {
        var_fs0 = (gcData->unkE8 - 15.0f) / 10.0f;
        if (var_fs0 < 0.0f) {
            var_fs0 = 0.0f;
        } else if (var_fs0 > 1.0f) {
            var_fs0 = 1.0f;
        }
    }

    uvMat4Copy(&sp50, &gcData->unk10);
    uvMat4LocalTranslate(&sp50, gcData->unk59C.x, gcData->unk59C.y, gcData->unk59C.z);
    uvMat4RotateAxis(&sp50, gcData->unk598, 'x');
    uvFxProps(gcData->unk660, FX_PROP_5(gcData->unk578, gcData->unk57C, gcData->unk580, (var_fs0 * 0.6f)), FX_PROP_END);
    func_8021A4D8(gcData->unk660, &sp50);
    uvModelGetPosm(gcData->modelId, gcData->unk573, &sp50);
    uvMat4RotateAxis(&sp50, gcData->unkEC, 'z');
    uvDobjPosm(gcData->objId, gcData->unk573, &sp50);
    if (var_fs0 > 0.95f) {
        uvDobjProps(gcData->objId, 5, gcData->unk573, 0);
    } else {
        uvDobjProps(gcData->objId, 4, gcData->unk573, 0);
    }
    if (gcData->unk5D == 0) {
        var_fs0 = 0.0f;
    } else {
        var_fs0 = (gcData->unkF0 - 15.0f) / 10.0f;
        if (var_fs0 < 0.0f) {
            var_fs0 = 0.0f;
        } else if (var_fs0 > 1.0f) {
            var_fs0 = 1.0f;
        }
    }
    uvMat4Copy(&sp50, &gcData->unk10);
    uvMat4LocalTranslate(&sp50, gcData->unk5B0, gcData->unk5B4, gcData->unk5B8);
    uvMat4RotateAxis(&sp50, gcData->unk5AC, 'x');
    uvFxProps(gcData->unk661, FX_PROP_5(gcData->unk584, gcData->unk588, gcData->unk58C, (var_fs0 * 0.6f)), FX_PROP_END);
    func_8021A4D8(gcData->unk661, &sp50);
    if (var_fs0 > 0.95f) {
        uvDobjProps(gcData->objId, 5, gcData->unk574, 0);
    } else {
        uvDobjProps(gcData->objId, 4, gcData->unk574, 0);
    }
    uvModelGetPosm(gcData->modelId, gcData->unk574, &sp50);
    uvMat4RotateAxis(&sp50, -gcData->unkF4, 'y');
    uvDobjPosm(gcData->objId, gcData->unk574, &sp50);
}

void func_802F56B4(GyrocopterData* gcData, u8 arg1) {
    static f32 D_8034F370 = 0.0f;
    static f32 D_8034F374 = 0.5f;
    f32 var_fa1;
    u8 sp23;

    if ((fdr_802E6B5C() == 3) || (fdr_802E6B5C() == 4)) {
        gcData->usingFuel = FALSE;
        gcData->unkF0 = 0.0f;
        gcData->unkE8 = 0.0f;
        func_802F5358(gcData);
        return;
    }
    if (gcData->unk663 == 0) {
        if (arg1 != 0) {
            gcData->unk663 = 2;
        } else {
            gcData->unk663 = 1;
        }
        gcData->unk664 = 0.0f;
        D_8034F370 = 0.0f;
        D_8034F374 = 2.0f;
        uvDobj_802180DC(gcData->objId, &D_80368370);
    }

    var_fa1 = gcData->unk664 / 3.0f;
    // clang-format off
    if (var_fa1 < 0.0f) { var_fa1 = 0.0f; } else if (var_fa1 > 1.0f) { var_fa1 = 1.0f; }
    // clang-format on

    gcData->unk664 += D_8034F854;
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

    switch (gcData->unk663) {
    case 2:
        sp23 = gcData->unk591;
        break;
    case 1:
        sp23 = gcData->unk592;
        break;
    }

    uvJanimPoseLine(&D_80368520, sp23, D_8034F370);
    func_802006FC(&D_803686D0, &D_80368370, &D_80368520, var_fa1);
    func_80200638(gcData->objId, &D_803686D0);
    gcData->usingFuel = FALSE;
    gcData->unkE8 = func_80313AF4(0.0f, gcData->unkE8, 0.5f);
    gcData->unkF0 = func_80313AF4(0.0f, gcData->unkF0, 0.5f);
    func_802F5358(gcData);
}

void func_802F5910(GyrocopterData* gcData) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv0;

    temp_fa0 = gcData->unk10.m[3][0];
    temp_fa1 = gcData->unk10.m[3][1];
    temp_fv0 = gcData->unk10.m[3][2];
    if (gcData->unk662 == 0) {
        gcData->unk662 = 1;
        if (gcData->unkD0 != 0) {
            sndPlaySfx(SFX_WATER_SPLASH);
            uvEventPost(0x12, 0);
            func_802F8AB8(temp_fa0, temp_fa1, temp_fv0, 6.0f, &gcData->unk19C);
            gcData->unk2 |= 8;
            gcData->camera->unk6 = gcData->unk2;
            uvDobjState(gcData->objId, gcData->unk2 | 8);
            shadow_803343D8(0);
        } else {
            func_802F9638(temp_fa0, temp_fa1, temp_fv0, 10.0f);
        }
    }
    gcData->usingFuel = FALSE;
    gcData->unkF0 = 0.0f;
    gcData->unkE8 = 0.0f;
    func_802F50CC(gcData);
}
