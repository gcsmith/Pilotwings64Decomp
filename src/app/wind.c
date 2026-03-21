#include "common.h"
#include <uv_dobj.h>
#include <uv_math.h>
#include <uv_util.h>
#include "code_69BF0.h"
#include "game.h"
#include "task.h"
#include "wind.h"

typedef struct {
    u16 unk0;
    u8 pad2[2];
    Mtx4F unk4;
    Mtx4F unk44;
    Vec3F unk84;
    Vec3F unk90;
    Vec3F unk9C;
} LocalWind; // size = 0xA8

// bss
LevelLWIN* sRefLWIN;
u8 sLocalWindCount;
LocalWind sLocalWinds[6];

// forward declarations
STATIC_FUNC void wind_8034D6D4(LevelLWIN*, LocalWind*);
STATIC_FUNC void wind_8034D90C(f32, f32, f32, LevelLWIN*, LocalWind*, Vec3F*);
STATIC_FUNC void wind_8034DA4C(f32, f32, f32, LevelLWIN*, LocalWind*, Vec3F*);
STATIC_FUNC void wind_8034DD18(f32, f32, f32, LevelLWIN*, LocalWind*, Vec3F*);
STATIC_FUNC void wind_8034DF58(LevelLWIN*, f32, Vec3F*);
STATIC_FUNC f32 wind_8034DFC4(u8, f32);

void windInit(void) {
}

void windLoad(void) {
    s32 i;
    LocalWind* wind;
    LevelLWIN* lwin;
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

    sLocalWindCount = taskGetLWIN(&sRefLWIN);
    if (sLocalWindCount > ARRAY_COUNT(sLocalWinds)) {
        _uvDebugPrintf("wind : too many local winds defined in level [%d]\n", sLocalWindCount);
        sLocalWindCount = 0;
        return;
    }
    for (i = 0; i < sLocalWindCount; i++) {
        wind = &sLocalWinds[i];
        lwin = &sRefLWIN[i];
        uvMat4SetIdentity(&wind->unk4);
        uvMat4SetIdentity(&spD4.unk0);
        spD4.unk0.m[3][0] = lwin->unk0.f[0];
        spD4.unk0.m[3][1] = lwin->unk0.f[1];
        spD4.unk0.m[3][2] = lwin->unk0.f[2];
        spD4.unk58 = 0xB;
        spD4.unk5C = 1.0f;
        spD4.unk64 = 0;
        spD4.unk68 = lwin->unk4C;
        spD4.unk6C = spD4.unk68;
        spD4.unk70 = lwin->unk3C;
        spD4.unk60 = uvSqrtF(SQ(lwin->unk40.x) + SQ(lwin->unk40.y) + SQ(lwin->unk40.z)) + 0.9f;
        if (spD4.unk60 < 0.0f) {
            spD4.unk60 = 0.0f;
        } else if (spD4.unk60 > 1.0f) {
            spD4.unk60 = 1.0f;
        }
        s2 = &lwin->unkC;
        if (lwin->unk50 == 0) {
            uvMat4Scale(&wind->unk4, lwin->unk4C, lwin->unk4C, lwin->unk4C);
            wind->unk4.m[3][0] = lwin->unk0.f[0];
            wind->unk4.m[3][1] = lwin->unk0.f[1];
            wind->unk4.m[3][2] = lwin->unk0.f[2];
            wind->unk0 = uvDobjAllocIdx();
            uvDobjModel(wind->unk0, MODEL_WIND_WAVE_1);
            uvDobjPosm(wind->unk0, 0, &wind->unk4);
            uvDobjState(wind->unk0, 2U);
            uvDobjProps(wind->unk0, 3, lwin->unk4C, 0);
            spD4.unk74 = 8;
            spD4.unk40 = lwin->unk0;
            spD4.unk4C = lwin->unkC;
        } else if (lwin->unk50 == 1) {
            spB4.f[0] = s2->f[0] - lwin->unk0.f[0];
            spB4.f[1] = s2->f[1] - lwin->unk0.f[1];
            spB4.f[2] = s2->f[2] - lwin->unk0.f[2];
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
                wind->unk4.m[0][0] = spC0.f[0];
                wind->unk4.m[0][1] = spC0.f[1];
                wind->unk4.m[0][2] = spC0.f[2];
                wind->unk4.m[1][0] = -spA8.f[0];
                wind->unk4.m[1][1] = -spA8.f[1];
                wind->unk4.m[1][2] = -spA8.f[2];
                wind->unk4.m[2][0] = spB4.f[0];
                wind->unk4.m[2][1] = spB4.f[1];
                wind->unk4.m[2][2] = spB4.f[2];
            }
            uvMat4Scale(&wind->unk4, lwin->unk4C, lwin->unk4C, temp_fs0);
            wind->unk4.m[3][0] = (lwin->unk0.f[0] + s2->f[0]) * 0.5;
            wind->unk4.m[3][1] = (lwin->unk0.f[1] + s2->f[1]) * 0.5;
            wind->unk4.m[3][2] = (lwin->unk0.f[2] + s2->f[2]) * 0.5;
            wind->unk0 = uvDobjAllocIdx();
            uvDobjModel(wind->unk0, MODEL_WIND_WAVE_1);
            uvDobjPosm(wind->unk0, 0, &wind->unk4);
            uvDobjState(wind->unk0, 2);
            if (temp_fs0 < lwin->unk4C) {
                var_fv1 = lwin->unk4C;
            } else {
                var_fv1 = temp_fs0;
            }
            uvDobjProps(wind->unk0, 3, var_fv1, 0);
            spD4.unk74 = 0xA;
            spD4.unk40 = lwin->unk0;
            spD4.unk4C = lwin->unkC;
        } else if (lwin->unk50 == 2) {
            uvMat4RotateAxis(&wind->unk4, lwin->unk24.f[0] * 0.0174533f, 'z'); // almost DEG_TO_RAD(1)
            uvMat4RotateAxis(&wind->unk4, lwin->unk24.f[1] * 0.0174533f, 'x'); // almost DEG_TO_RAD(1)
            uvMat4RotateAxis(&wind->unk4, lwin->unk24.f[2] * 0.0174533f, 'y'); // almost DEG_TO_RAD(1)
            wind->unk4.m[3][0] = lwin->unk18.f[0];
            wind->unk4.m[3][1] = lwin->unk18.f[1];
            wind->unk4.m[3][2] = lwin->unk18.f[2];
            uvMat4InvertTranslationRotation(&wind->unk44, &wind->unk4);
            wind->unk4.m[3][0] = 0;
            wind->unk4.m[3][1] = 0;
            wind->unk4.m[3][2] = 0;
            uvMat4Scale(&wind->unk4, lwin->unk30.f[0], lwin->unk30.f[1], lwin->unk30.f[2]);
            wind->unk4.m[3][0] = lwin->unk18.f[0];
            wind->unk4.m[3][1] = lwin->unk18.f[1];
            wind->unk4.m[3][2] = lwin->unk18.f[2];
            wind->unk9C.f[0] = lwin->unk30.f[0];
            wind->unk9C.f[1] = lwin->unk30.f[1];
            wind->unk9C.f[2] = lwin->unk30.f[2];
            wind->unk0 = uvDobjAllocIdx();
            uvDobjModel(wind->unk0, MODEL_WIND_WAVE_2);
            uvDobjPosm(wind->unk0, 0, &wind->unk4);
            uvDobjState(wind->unk0, 2U);
            if (lwin->unk30.f[1] < lwin->unk30.f[0]) {
                var_fv1 = lwin->unk30.f[0];
            } else {
                var_fv1 = lwin->unk30.f[1];
            }
            uvDobjProps(wind->unk0, 3, var_fv1, 0);
            spD4.unk74 = 0xA;
            spD4.unk40.f[0] = lwin->unk18.f[0];
            spD4.unk40.f[1] = lwin->unk18.f[1];
            spD4.unk40.f[2] = lwin->unk18.f[2];
            spD4.unk4C.f[0] = lwin->unk30.f[0];
            spD4.unk4C.f[1] = lwin->unk30.f[1];
            spD4.unk4C.f[2] = lwin->unk30.f[2];
            spD4.unk6C = spD4.unk68 = uvSqrtF(SQ(lwin->unk30.x) + SQ(lwin->unk30.y) + SQ(lwin->unk30.z)) * 0.50;
        } else {
            _uvDebugPrintf("wind : unknown wind shape [%d]\n", lwin->unk50);
            return;
        }
        wind_8034D6D4(lwin, wind);
        func_802E27A8(&spD4);
    }
}

void windDeinit(void) {
    LocalWind* var_s0;
    s32 i;

    for (i = 0; i < sLocalWindCount; i++) {
        var_s0 = &sLocalWinds[i];
        if (var_s0->unk0 != 0xFFFF) {
            uvDobjModel(var_s0->unk0, MODEL_WORLD);
        }
        var_s0->unk0 = 0xFFFF;
    }
}

void wind_8034D548(void) {
}

void wind_8034D550(f32 arg0, f32 arg1, f32 arg2, Vec3F* arg3) {
    s32 i;
    LevelLWIN* lwin;

    arg3->x = 0.0f;
    arg3->y = 0.0f;
    arg3->z = 0.0f;
    for (i = 0; i < sLocalWindCount; i++) {
        lwin = &sRefLWIN[i];
        switch (lwin->unk50) {
        case 0:
            wind_8034D90C(arg0, arg1, arg2, lwin, &sLocalWinds[i], arg3);
            break;
        case 1:
            wind_8034DA4C(arg0, arg1, arg2, lwin, &sLocalWinds[i], arg3);
            break;
        case 2:
            wind_8034DD18(arg0, arg1, arg2, lwin, &sLocalWinds[i], arg3);
            break;
        }
    }
}

STATIC_FUNC void wind_8034D6D4(LevelLWIN* arg0, LocalWind* arg1) {
    switch (arg0->unk50) {
    case 0:
        arg1->unk84.x = arg0->unk0.x - arg0->unk4C;
        arg1->unk90.x = arg0->unk0.x + arg0->unk4C;
        arg1->unk84.y = arg0->unk0.y - arg0->unk4C;
        arg1->unk90.y = arg0->unk0.y + arg0->unk4C;
        arg1->unk84.z = arg0->unk0.z - arg0->unk4C;
        arg1->unk90.z = arg0->unk0.z + arg0->unk4C;
        break;
    case 1:
        if (arg0->unk0.x < arg0->unkC.x) {
            arg1->unk84.x = arg0->unk0.x - arg0->unk4C;
            arg1->unk90.x = arg0->unkC.x + arg0->unk4C;
        } else {
            arg1->unk84.x = arg0->unkC.x - arg0->unk4C;
            arg1->unk90.x = arg0->unk0.x + arg0->unk4C;
        }

        if (arg0->unk0.y < arg0->unkC.y) {
            arg1->unk84.y = arg0->unk0.y - arg0->unk4C;
            arg1->unk90.y = arg0->unkC.y + arg0->unk4C;
        } else {
            arg1->unk84.y = arg0->unkC.y - arg0->unk4C;
            arg1->unk90.y = arg0->unk0.y + arg0->unk4C;
        }

        if (arg0->unk0.z < arg0->unkC.z) {
            arg1->unk84.z = arg0->unk0.z - arg0->unk4C;
            arg1->unk90.z = arg0->unkC.z + arg0->unk4C;
        } else {
            arg1->unk84.z = arg0->unkC.z - arg0->unk4C;
            arg1->unk90.z = arg0->unk0.z + arg0->unk4C;
        }
        break;
    case 2:
        arg0->unk4C = uvSqrtF(SQ(arg0->unk30.x) + SQ(arg0->unk30.y) + SQ(arg0->unk30.z));
        arg1->unk84.x = arg0->unk18.x - arg0->unk4C;
        arg1->unk90.x = arg0->unk18.x + arg0->unk4C;
        arg1->unk84.y = arg0->unk18.y - arg0->unk4C;
        arg1->unk90.y = arg0->unk18.y + arg0->unk4C;
        arg1->unk84.z = arg0->unk18.z - arg0->unk4C;
        arg1->unk90.z = arg0->unk18.z + arg0->unk4C;
        break;
    }
}

STATIC_FUNC void wind_8034D90C(f32 arg0, f32 arg1, f32 arg2, LevelLWIN* arg3, LocalWind* arg4, Vec3F* arg5) {
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
        wind_8034DF58(arg3, temp_fv0, &sp1C);
        arg5->x += sp1C.x;
        arg5->y += sp1C.y;
        arg5->z += sp1C.z;
    }
}

STATIC_FUNC void wind_8034DA4C(f32 arg0, f32 arg1, f32 arg2, LevelLWIN* arg3, LocalWind* arg4, Vec3F* arg5) {
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

    sp6C = arg3->unkC.x - arg3->unk0.x;
    sp68 = arg3->unkC.y - arg3->unk0.y;
    sp64 = arg3->unkC.z - arg3->unk0.z;
    sp60 = arg0 - arg3->unk0.x;
    sp5C = arg1 - arg3->unk0.y;
    sp58 = arg2 - arg3->unk0.z;
    if (((sp6C * sp60) + (sp68 * sp5C) + (sp64 * sp58)) < 0.0f) {
        return;
    }

    sp6C = -sp6C;
    sp68 = -sp68;
    sp64 = -sp64;
    sp60 = arg0 - arg3->unkC.x;
    sp5C = arg1 - arg3->unkC.y;
    sp58 = arg2 - arg3->unkC.z;
    sp24 = (sp6C * sp60) + (sp68 * sp5C) + (sp64 * sp58);
    if (sp24 < 0.0f) {
        return;
    }

    sp40 = uvSqrtF(SQ(sp6C) + SQ(sp68) + SQ(sp64));
    if (sp40 > 0.00001f) {
        temp_fv0_3 = sp24 / sp40;
        sp54 = (arg3->unkC.x + ((sp6C / sp40) * temp_fv0_3)) - arg0;
        sp50 = (arg3->unkC.y + ((sp68 / sp40) * temp_fv0_3)) - arg1;
        sp4C = (arg3->unkC.z + ((sp64 / sp40) * temp_fv0_3)) - arg2;
        sp24 = uvSqrtF(SQ(sp54) + SQ(sp50) + SQ(sp4C));
    } else {
        sp24 = 0.0f;
    }

    if (arg3->unk4C < sp24) {
        return;
    }

    wind_8034DF58(arg3, sp24, &sp34);
    arg5->x += sp34.x;
    arg5->y += sp34.y;
    arg5->z += sp34.z;
}

STATIC_FUNC void wind_8034DD18(f32 arg0, f32 arg1, f32 arg2, LevelLWIN* arg3, LocalWind* arg4, Vec3F* arg5) {
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

    sp5C.x = arg0;
    sp5C.y = arg1;
    sp5C.z = arg2;
    uvMat4LocalToWorld(&arg4->unk44, &sp50, &sp5C);
    temp_fv0 = arg4->unk9C.x * 0.5f;
    if (sp50.x < -temp_fv0) {
        return;
    }
    if (temp_fv0 < sp50.x) {
        return;
    }

    temp_fv0 = arg4->unk9C.y * 0.5f;
    if ((sp50.y < -temp_fv0)) {
        return;
    }
    if (temp_fv0 < sp50.y) {
        return;
    }

    temp_fv0 = arg4->unk9C.z * 0.5f;

    if ((sp50.z < -temp_fv0)) {
        return;
    }
    if (temp_fv0 < sp50.z) {
        return;
    }

    temp_fv0 = (2.0f * sp50.x) / arg4->unk9C.x;
    temp_fv1 = (2.0f * sp50.y) / arg4->unk9C.y;
    temp_fa1 = (2.0f * sp50.z) / arg4->unk9C.z;
    var_fv1 = uvSqrtF(SQ(temp_fv0) + SQ(temp_fv1) + SQ(temp_fa1));
    if (var_fv1 < 0.0f) {
        var_fv1 = 0.0f;
    } else if (var_fv1 > 1.0f) {
        var_fv1 = 1.0f;
    }
    temp_fv0 = wind_8034DFC4(arg3->unk51, var_fv1);
    var_fv1 = arg3->unk40.x * temp_fv0;
    var_fa0 = arg3->unk40.y * temp_fv0;
    temp_fa1 = arg3->unk40.z * temp_fv0;
    arg5->x += var_fv1;
    arg5->y += var_fa0;
    arg5->z += temp_fa1;
}

STATIC_FUNC void wind_8034DF58(LevelLWIN* arg0, f32 arg1, Vec3F* arg2) {
    f32 temp_fv0;

    temp_fv0 = arg1 / arg0->unk4C;
    temp_fv0 = wind_8034DFC4(arg0->unk51, temp_fv0);
    arg2->x = arg0->unk40.x * temp_fv0;
    arg2->y = arg0->unk40.y * temp_fv0;
    arg2->z = arg0->unk40.z * temp_fv0;
}

STATIC_FUNC f32 wind_8034DFC4(u8 arg0, f32 arg1) {
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
