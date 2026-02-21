#include "common.h"
#include "code_D4290.h"
#include "code_69BF0.h"
#include <uv_util.h>
#include <uv_dobj.h>
#include <uv_level.h>
#include <uv_math.h>
#include <uv_dobj.h>
#include <uv_math.h>

// size: 0xA8
typedef struct {
    u16 unk0;
    Mtx4F unk4;
    Mtx4F unk44;
    Vec3F unk84;
    Vec3F unk90;
    Vec3F unk9C;
} Unk8037F518;

// size: 0x54
typedef struct {
    Vec3F unk0;
    Vec3F unkC;
    Vec3F unk18;
    Vec3F unk24;
    Vec3F unk30;
    s32 unk3C;
    Vec3F unk40;
    f32 unk4C;
    u8 unk50;
    u8 unk51;
} Unk8037F510;

// bss
extern Unk8037F510* D_8037F510;
extern u8 D_8037F514;
extern Unk8037F518 D_8037F518[6];

// forward declarations
static void func_8034D6D4(Unk8037F510*, Unk8037F518*);
static void func_8034D90C(f32, f32, f32, Unk8037F510*, Unk8037F518*, Vec3F*);
static void func_8034DA4C(f32, f32, f32, Unk8037F510*, Unk8037F518*, Vec3F*);
static void func_8034DD18(f32, f32, f32, Unk8037F510*, Unk8037F518*, Vec3F*);
static void func_8034DF58(Unk8037F510*, f32, Vec3F*);
static f32 func_8034DFC4(u8, f32);

void func_8034CD60(void) {
}

void wind_render(void) {
    s32 i;
    Unk8037F518* var_s1;
    Unk8037F510* temp_s0;
    Unk802E27A8_Arg0 spD4;
    f32 temp_fs0;
    f32 var_fv1;
    Vec3F spC0;
    Vec3F spB4;
    Vec3F spA8;
    Vec3F sp9C;
    Vec3F* s2;

    if (D_80362690->unkA0 == 0) {
        return;
    }

    D_8037F514 = levelDataGetLWIN((void**)&D_8037F510);
    if (D_8037F514 >= 7) {
        _uvDebugPrintf("wind : too many local winds defined in level [%d]\n", D_8037F514);
        D_8037F514 = 0;
        return;
    }
    for (i = 0; i < D_8037F514; i++) {
        var_s1 = &D_8037F518[i];
        temp_s0 = &D_8037F510[i];
        uvMat4SetIdentity(&var_s1->unk4);
        uvMat4SetIdentity(&spD4.unk0);
        spD4.unk0.m[3][0] = temp_s0->unk0.f[0];
        spD4.unk0.m[3][1] = temp_s0->unk0.f[1];
        spD4.unk0.m[3][2] = temp_s0->unk0.f[2];
        spD4.unk58 = 0xB;
        spD4.unk5C = 1.0f;
        spD4.unk64 = 0;
        spD4.unk68 = temp_s0->unk4C;
        spD4.unk6C = spD4.unk68;
        spD4.unk70 = temp_s0->unk3C;
        spD4.unk60 = uvSqrtF(SQ(temp_s0->unk40.x) + SQ(temp_s0->unk40.y) + SQ(temp_s0->unk40.z)) + 0.9f;
        if (spD4.unk60 < 0.0f) {
            spD4.unk60 = 0.0f;
        } else if (spD4.unk60 > 1.0f) {
            spD4.unk60 = 1.0f;
        }
        s2 = &temp_s0->unkC;
        if (temp_s0->unk50 == 0) {
            uvMat4UnkOp3(&var_s1->unk4, temp_s0->unk4C, temp_s0->unk4C, temp_s0->unk4C);
            var_s1->unk4.m[3][0] = temp_s0->unk0.f[0];
            var_s1->unk4.m[3][1] = temp_s0->unk0.f[1];
            var_s1->unk4.m[3][2] = temp_s0->unk0.f[2];
            var_s1->unk0 = uvDobjAllocIdx();
            uvDobjModel(var_s1->unk0, 0xD5U);
            uvDobjPosm(var_s1->unk0, 0, &var_s1->unk4);
            uvDobjState(var_s1->unk0, 2U);
            uvDobjProps(var_s1->unk0, 3, temp_s0->unk4C, 0);
            spD4.unk74 = 8;
            spD4.unk40 = temp_s0->unk0;
            spD4.unk4C = temp_s0->unkC;
        } else if (temp_s0->unk50 == 1) {
            spB4.f[0] = s2->f[0] - temp_s0->unk0.f[0];
            spB4.f[1] = s2->f[1] - temp_s0->unk0.f[1];
            spB4.f[2] = s2->f[2] - temp_s0->unk0.f[2];
            temp_fs0 = uvVec3Len(&spB4);
            if (spB4.f[0] > 0.0f) {
                var_fv1 = spB4.f[0];
            } else {
                var_fv1 = -spB4.f[0];
            }
            if (var_fv1 > 0.01f || (spB4.f[1] > 0.0f ? spB4.f[1] : -spB4.f[1]) > /*0*/ .01f) {
                sp9C.f[0] = 0.0f;
                sp9C.f[1] = 0.0f;
                sp9C.f[2] = 1.0f;
                uvVec3Normal(&spB4, &spB4);
                uvVec3Cross(&spC0, &spB4, &sp9C);
                uvVec3Normal(&spC0, &spC0);
                uvVec3Cross(&spA8, &spC0, &spB4);
                uvVec3Normal(&spA8, &spA8);
                var_s1->unk4.m[0][0] = spC0.f[0];
                var_s1->unk4.m[0][1] = spC0.f[1];
                var_s1->unk4.m[0][2] = spC0.f[2];
                var_s1->unk4.m[1][0] = -spA8.f[0];
                var_s1->unk4.m[1][1] = -spA8.f[1];
                var_s1->unk4.m[1][2] = -spA8.f[2];
                var_s1->unk4.m[2][0] = spB4.f[0];
                var_s1->unk4.m[2][1] = spB4.f[1];
                var_s1->unk4.m[2][2] = spB4.f[2];
            }
            uvMat4UnkOp3(&var_s1->unk4, temp_s0->unk4C, temp_s0->unk4C, temp_fs0);
            var_s1->unk4.m[3][0] = (temp_s0->unk0.f[0] + s2->f[0]) * 0.5;
            var_s1->unk4.m[3][1] = (temp_s0->unk0.f[1] + s2->f[1]) * 0.5;
            var_s1->unk4.m[3][2] = (temp_s0->unk0.f[2] + s2->f[2]) * 0.5;
            var_s1->unk0 = uvDobjAllocIdx();
            uvDobjModel(var_s1->unk0, 0xD5U);
            uvDobjPosm(var_s1->unk0, 0, &var_s1->unk4);
            uvDobjState(var_s1->unk0, 2U);
            if (temp_fs0 < temp_s0->unk4C) {
                var_fv1 = temp_s0->unk4C;
            } else {
                var_fv1 = temp_fs0;
            }
            uvDobjProps(var_s1->unk0, 3, var_fv1, 0);
            spD4.unk74 = 0xA;
            spD4.unk40 = temp_s0->unk0;
            spD4.unk4C = temp_s0->unkC;
        } else if (temp_s0->unk50 == 2) {
            uvMat4RotateAxis(&var_s1->unk4, temp_s0->unk24.f[0] * 0.0174533f, 'z'); // almost DEG_TO_RAD(1)
            uvMat4RotateAxis(&var_s1->unk4, temp_s0->unk24.f[1] * 0.0174533f, 'x'); // almost DEG_TO_RAD(1)
            uvMat4RotateAxis(&var_s1->unk4, temp_s0->unk24.f[2] * 0.0174533f, 'y'); // almost DEG_TO_RAD(1)
            var_s1->unk4.m[3][0] = temp_s0->unk18.f[0];
            var_s1->unk4.m[3][1] = temp_s0->unk18.f[1];
            var_s1->unk4.m[3][2] = temp_s0->unk18.f[2];
            uvMat4UnkOp4(&var_s1->unk44, &var_s1->unk4);
            var_s1->unk4.m[3][0] = 0;
            var_s1->unk4.m[3][1] = 0;
            var_s1->unk4.m[3][2] = 0;
            uvMat4UnkOp3(&var_s1->unk4, temp_s0->unk30.f[0], temp_s0->unk30.f[1], temp_s0->unk30.f[2]);
            var_s1->unk4.m[3][0] = temp_s0->unk18.f[0];
            var_s1->unk4.m[3][1] = temp_s0->unk18.f[1];
            var_s1->unk4.m[3][2] = temp_s0->unk18.f[2];
            var_s1->unk9C.f[0] = temp_s0->unk30.f[0];
            var_s1->unk9C.f[1] = temp_s0->unk30.f[1];
            var_s1->unk9C.f[2] = temp_s0->unk30.f[2];
            var_s1->unk0 = uvDobjAllocIdx();
            uvDobjModel(var_s1->unk0, 0xD6U);
            uvDobjPosm(var_s1->unk0, 0, &var_s1->unk4);
            uvDobjState(var_s1->unk0, 2U);
            if (temp_s0->unk30.f[1] < temp_s0->unk30.f[0]) {
                var_fv1 = temp_s0->unk30.f[0];
            } else {
                var_fv1 = temp_s0->unk30.f[1];
            }
            uvDobjProps(var_s1->unk0, 3, var_fv1, 0);
            spD4.unk74 = 0xA;
            spD4.unk40.f[0] = temp_s0->unk18.f[0];
            spD4.unk40.f[1] = temp_s0->unk18.f[1];
            spD4.unk40.f[2] = temp_s0->unk18.f[2];
            spD4.unk4C.f[0] = temp_s0->unk30.f[0];
            spD4.unk4C.f[1] = temp_s0->unk30.f[1];
            spD4.unk4C.f[2] = temp_s0->unk30.f[2];
            spD4.unk6C = spD4.unk68 = uvSqrtF(SQ(temp_s0->unk30.x) + SQ(temp_s0->unk30.y) + SQ(temp_s0->unk30.z)) * 0.50;
        } else {
            _uvDebugPrintf("wind : unknown wind shape [%d]\n", temp_s0->unk50);
            return;
        }
        func_8034D6D4(temp_s0, var_s1);
        func_802E27A8(&spD4);
    }
}

void func_8034D4AC(void) {
    Unk8037F518* var_s0;
    s32 i;

    for (i = 0; i < D_8037F514; i++) {
        var_s0 = &D_8037F518[i];
        if (var_s0->unk0 != 0xFFFF) {
            uvDobjModel(var_s0->unk0, 0xFFFF);
        }
        var_s0->unk0 = 0xFFFF;
    }
}

void func_8034D548(void) {
}

void func_8034D550(f32 arg0, f32 arg1, f32 arg2, Vec3F* arg3) {
    s32 i;
    Unk8037F510* temp_a3;

    arg3->f[0] = 0.0f;
    arg3->f[1] = 0.0f;
    arg3->f[2] = 0.0f;
    for (i = 0; i < D_8037F514; i++) {
        temp_a3 = &D_8037F510[i];
        switch (temp_a3->unk50) {
        case 0:
            func_8034D90C(arg0, arg1, arg2, temp_a3, &D_8037F518[i], arg3);
            break;
        case 1:
            func_8034DA4C(arg0, arg1, arg2, temp_a3, &D_8037F518[i], arg3);
            break;
        case 2:
            func_8034DD18(arg0, arg1, arg2, temp_a3, &D_8037F518[i], arg3);
            break;
        }
    }
}

static void func_8034D6D4(Unk8037F510* arg0, Unk8037F518* arg1) {
    switch (arg0->unk50) {
    case 0:
        arg1->unk84.f[0] = arg0->unk0.f[0] - arg0->unk4C;
        arg1->unk90.f[0] = arg0->unk0.f[0] + arg0->unk4C;
        arg1->unk84.f[1] = arg0->unk0.f[1] - arg0->unk4C;
        arg1->unk90.f[1] = arg0->unk0.f[1] + arg0->unk4C;
        arg1->unk84.f[2] = arg0->unk0.f[2] - arg0->unk4C;
        arg1->unk90.f[2] = arg0->unk0.f[2] + arg0->unk4C;
        return;
    case 1:
        if (arg0->unk0.f[0] < arg0->unkC.f[0]) {
            arg1->unk84.f[0] = arg0->unk0.f[0] - arg0->unk4C;
            arg1->unk90.f[0] = arg0->unkC.f[0] + arg0->unk4C;
        } else {
            arg1->unk84.f[0] = arg0->unkC.f[0] - arg0->unk4C;
            arg1->unk90.f[0] = arg0->unk0.f[0] + arg0->unk4C;
        }

        if (arg0->unk0.f[1] < arg0->unkC.f[1]) {
            arg1->unk84.f[1] = arg0->unk0.f[1] - arg0->unk4C;
            arg1->unk90.f[1] = arg0->unkC.f[1] + arg0->unk4C;
        } else {
            arg1->unk84.f[1] = arg0->unkC.f[1] - arg0->unk4C;
            arg1->unk90.f[1] = arg0->unk0.f[1] + arg0->unk4C;
        }

        if (arg0->unk0.f[2] < arg0->unkC.f[2]) {
            arg1->unk84.f[2] = arg0->unk0.f[2] - arg0->unk4C;
            arg1->unk90.f[2] = arg0->unkC.f[2] + arg0->unk4C;
        } else {
            arg1->unk84.f[2] = arg0->unkC.f[2] - arg0->unk4C;
            arg1->unk90.f[2] = arg0->unk0.f[2] + arg0->unk4C;
        }
        return;
    case 2:
        arg0->unk4C = uvSqrtF(SQ(arg0->unk30.x) + SQ(arg0->unk30.y) + SQ(arg0->unk30.z));
        arg1->unk84.f[0] = arg0->unk18.f[0] - arg0->unk4C;
        arg1->unk90.f[0] = arg0->unk18.f[0] + arg0->unk4C;
        arg1->unk84.f[1] = arg0->unk18.f[1] - arg0->unk4C;
        arg1->unk90.f[1] = arg0->unk18.f[1] + arg0->unk4C;
        arg1->unk84.f[2] = arg0->unk18.f[2] - arg0->unk4C;
        arg1->unk90.f[2] = arg0->unk18.f[2] + arg0->unk4C;
        return;
    }
}

static void func_8034D90C(f32 arg0, f32 arg1, f32 arg2, Unk8037F510* arg3, Unk8037F518* arg4, Vec3F* arg5) {
    f32 f0;
    f32 f12;
    f32 f14;
    f32 temp_fv0;
    Vec3F sp1C;

    if (arg0 < arg4->unk84.x) {
        return;
    }
    if (arg4->unk90.x < arg0) {
        return;
    }
    if (arg1 < arg4->unk84.y) {
        return;
    }
    if (arg4->unk90.y < arg1) {
        return;
    }
    if (arg2 < arg4->unk84.z) {
        return;
    }
    if (arg4->unk90.z < arg2) {
        return;
    }

    f0 = arg0 - arg3->unk0.x;
    f12 = arg1 - arg3->unk0.y;
    f14 = arg2 - arg3->unk0.z;

    temp_fv0 = uvLength3D(f0, f12, f14);
    if (!(arg3->unk4C < temp_fv0)) {
        func_8034DF58(arg3, temp_fv0, &sp1C);
        arg5->f[0] += sp1C.f[0];
        arg5->f[1] += sp1C.f[1];
        arg5->f[2] += sp1C.f[2];
    }
}

static void func_8034DA4C(f32 arg0, f32 arg1, f32 arg2, Unk8037F510* arg3, Unk8037F518* arg4, Vec3F* arg5) {
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp24;
    f32 temp_fv0_3;
    f32 sp40;
    Vec3F sp34;

    if (arg0 < arg4->unk84.x) {
        return;
    }
    if (arg4->unk90.x < arg0) {
        return;
    }
    if (arg1 < arg4->unk84.y) {
        return;
    }
    if (arg4->unk90.y < arg1) {
        return;
    }
    if (arg2 < arg4->unk84.z) {
        return;
    }
    if (arg4->unk90.z < arg2) {
        return;
    }

    sp6C = arg3->unkC.f[0] - arg3->unk0.f[0];
    sp68 = arg3->unkC.f[1] - arg3->unk0.f[1];
    sp64 = arg3->unkC.f[2] - arg3->unk0.f[2];
    sp60 = arg0 - arg3->unk0.f[0];
    sp5C = arg1 - arg3->unk0.f[1];
    sp58 = arg2 - arg3->unk0.f[2];
    if (((sp6C * sp60) + (sp68 * sp5C) + (sp64 * sp58)) < 0.0f) {
        return;
    }

    sp6C = -sp6C;
    sp68 = -sp68;
    sp64 = -sp64;
    sp60 = arg0 - arg3->unkC.f[0];
    sp5C = arg1 - arg3->unkC.f[1];
    sp58 = arg2 - arg3->unkC.f[2];
    sp24 = (sp6C * sp60) + (sp68 * sp5C) + (sp64 * sp58);
    if (sp24 < 0.0f) {
        return;
    }

    sp40 = uvSqrtF(SQ(sp6C) + SQ(sp68) + SQ(sp64));
    if (sp40 > 0.00001f) {
        temp_fv0_3 = sp24 / sp40;
        sp54 = (arg3->unkC.f[0] + ((sp6C / sp40) * temp_fv0_3)) - arg0;
        sp50 = (arg3->unkC.f[1] + ((sp68 / sp40) * temp_fv0_3)) - arg1;
        sp4C = (arg3->unkC.f[2] + ((sp64 / sp40) * temp_fv0_3)) - arg2;
        sp24 = uvSqrtF(SQ(sp54) + SQ(sp50) + SQ(sp4C));
    } else {
        sp24 = 0.0f;
    }

    if (arg3->unk4C < sp24) {
        return;
    }

    func_8034DF58(arg3, sp24, &sp34);
    arg5->f[0] += sp34.f[0];
    arg5->f[1] += sp34.f[1];
    arg5->f[2] += sp34.f[2];
}

static void func_8034DD18(f32 arg0, f32 arg1, f32 arg2, Unk8037F510* arg3, Unk8037F518* arg4, Vec3F* arg5) {
    Vec3F sp5C;
    Vec3F sp50;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_fa0;
    f32 var_fv1;
    s32 pad[4];

    if (arg0 < arg4->unk84.x) {
        return;
    }
    if (arg4->unk90.x < arg0) {
        return;
    }
    if (arg1 < arg4->unk84.y) {
        return;
    }
    if (arg4->unk90.y < arg1) {
        return;
    }
    if (arg2 < arg4->unk84.z) {
        return;
    }
    if (arg4->unk90.z < arg2) {
        return;
    }

    sp5C.f[0] = arg0;
    sp5C.f[1] = arg1;
    sp5C.f[2] = arg2;
    uvMat4UnkOp5(&arg4->unk44, &sp50, &sp5C);
    temp_fv0 = arg4->unk9C.f[0] * 0.5f;
    if (sp50.f[0] < -temp_fv0) {
        return;
    }
    if (temp_fv0 < sp50.f[0]) {
        return;
    }

    temp_fv0 = arg4->unk9C.f[1] * 0.5f;
    if ((sp50.f[1] < -temp_fv0)) {
        return;
    }
    if (temp_fv0 < sp50.f[1]) {
        return;
    }

    temp_fv0 = arg4->unk9C.f[2] * 0.5f;

    if ((sp50.f[2] < -temp_fv0)) {
        return;
    }
    if (temp_fv0 < sp50.f[2]) {
        return;
    }

    temp_fv0 = (2.0f * sp50.f[0]) / arg4->unk9C.f[0];
    temp_fv1 = (2.0f * sp50.f[1]) / arg4->unk9C.f[1];
    temp_fa1 = (2.0f * sp50.f[2]) / arg4->unk9C.f[2];
    var_fv1 = uvSqrtF(SQ(temp_fv0) + SQ(temp_fv1) + SQ(temp_fa1));
    if (var_fv1 < 0.0f) {
        var_fv1 = 0.0f;
    } else if (var_fv1 > 1.0f) {
        var_fv1 = 1.0f;
    }
    temp_fv0 = func_8034DFC4(arg3->unk51, var_fv1);
    var_fv1 = arg3->unk40.f[0] * temp_fv0;
    var_fa0 = arg3->unk40.f[1] * temp_fv0;
    temp_fa1 = arg3->unk40.f[2] * temp_fv0;
    arg5->f[0] += var_fv1;
    arg5->f[1] += var_fa0;
    arg5->f[2] += temp_fa1;
}

static void func_8034DF58(Unk8037F510* arg0, f32 arg1, Vec3F* arg2) {
    f32 temp_fv0;

    temp_fv0 = arg1 / arg0->unk4C;
    temp_fv0 = func_8034DFC4(arg0->unk51, temp_fv0);
    arg2->f[0] = arg0->unk40.f[0] * temp_fv0;
    arg2->f[1] = arg0->unk40.f[1] * temp_fv0;
    arg2->f[2] = arg0->unk40.f[2] * temp_fv0;
}

static f32 func_8034DFC4(u8 arg0, f32 arg1) {
    f32 var_fv1;

    switch (arg0) {
    case 1:
        var_fv1 = 1.0f - arg1;
        break;
    case 2:
        var_fv1 = 1.0f - SQ(arg1);
        break;
    case 0:
        var_fv1 = 1.0f;
        break;
    case 3:
        if (arg1 < 0.8f) {
            var_fv1 = 1.0f;
        } else {
            var_fv1 = 1.0f - ((arg1 - 0.8f) / 0.19999999f);
        }
        break;
    }
    return var_fv1;
}
