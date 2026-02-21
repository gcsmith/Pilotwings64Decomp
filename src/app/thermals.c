#include "common.h"
#include <uv_dobj.h>
#include <uv_level.h>
#include <uv_math.h>
#include "code_69BF0.h"
#include "code_9A960.h"
#include "hud.h"
#include "thermals.h"

#define THERM_ENABLE_DURATION (4 * 60) // 4 minutes in sec
#define THERM_WEAKEN_DURATION (10)
#define THERM_DISABLE_TIME (THERM_ENABLE_DURATION + THERM_WEAKEN_DURATION)

s32 gThermShouldDisable = 0; // true when test disables thermals after THERM_ENABLE_DURATION

static LevelTHER* gLevelTHER;
u8 gThermalCount;
Thermal gThermals[16];
s8 gThermReady;

// forward declarations
static void therm_80346E04(LevelTHER* therm, f32 x, f32 y, f32 z, f32 dist, Vec3F* dst);

void thermInit(void) {
    s32 i;
    for (i = 0; i < ARRAY_COUNT(gThermals); i++) {
        gThermals[i].unk0 = 0xFFFF;
    }
    gThermReady = 1;
}

void therm_8034662C(void) {
    Thermal* therm;
    s32 pad;
    Unk80362690_Unk0_UnkC* temp_v1_2;
    LevelTHER* levlTher;
    Unk802E27A8_Arg0 sp90;
    f32 maxDim;
    f32 ratio;
    s32 i;

    if (D_80362690->unk0[D_80362690->unk9C].unkC.unk7B == 0) {
        gThermalCount = levelDataGetTHER(&gLevelTHER);
        if (gThermalCount > ARRAY_COUNT(gThermals)) {
            _uvDebugPrintf("thermals : too many thermals defined in level [%d]\n", gThermalCount);
            gThermalCount = 0;
            return;
        }

        if (gThermalCount != 0) {
            uvLevelAppend(0x16);

            for (i = 0; i < gThermalCount; i++) {
                levlTher = &gLevelTHER[i];
                therm = &gThermals[i];
                therm->unk0 = uvDobjAllocIdx();
                uvDobjModel(therm->unk0, 0x101);
                uvDobjState(therm->unk0, 2);
                uvVec3Copy(&gThermals[i].pos, &levlTher->pos);
                if (levlTher->height < levlTher->scale) {
                    maxDim = levlTher->scale;
                } else {
                    maxDim = levlTher->height;
                }
                uvDobjProps(therm->unk0, 3, maxDim, 0);
                therm->scale = levlTher->scale;
                ratio = (f32)i / gThermalCount;
                therm->height = 3.1415927f * ratio;
                uvMat4SetIdentity(&sp90.unk0);
                sp90.unk0.m[3][0] = 0.0f;
                sp90.unk0.m[3][1] = 0.0f;
                sp90.unk0.m[3][2] = 0.0f;
                sp90.unk58 = 2;
                sp90.unk5C = 1.0f;
                sp90.unk64 = 0;
                sp90.unk68 = maxDim;
                sp90.unk6C = maxDim;
                sp90.unk70 = (s8)levlTher->unk14;
                sp90.unk60 = (levlTher->unk20 * 0.9f) + 0.9f;
                sp90.unk74 = 10;
                sp90.unk40.x = levlTher->pos.x;
                sp90.unk40.y = levlTher->pos.y;
                sp90.unk40.z = (f32)(levlTher->pos.z + (levlTher->height * 0.5));
                sp90.unk4C.x = levlTher->pos.x;
                sp90.unk4C.y = levlTher->pos.y;
                sp90.unk4C.z = (f32)(levlTher->pos.z - (levlTher->height * 0.5));
                func_802E27A8(&sp90);
            }
            gThermShouldDisable = 0;
            temp_v1_2 = &D_80362690->unk0[D_80362690->unk9C].unkC;
            if ((temp_v1_2->unk2 == 0) && (temp_v1_2->unk4 == 3) && (temp_v1_2->unk6 == 0)) {
                gThermShouldDisable = 1;
            }
        }
    }
}

void therm_8034695C(void) {
    f32 var_fs0;
    Thermal* therm;
    LevelTHER* levlTher;
    Mtx4F sp74;
    s32 i;

    var_fs0 = 1.0f;
    // after 4 min, 10 sec, disable thermals, if the test calls for it
    if ((D_8034F850 >= THERM_DISABLE_TIME) && (gThermalCount != 0) && gThermShouldDisable) {
        therm_80346B84();
        gThermalCount = 0;
        gThermReady = 0;
        hudWarningText(0xF, 1.5f, 8.0f);
    }

    for (i = 0; i < gThermalCount; i++) {
        therm = &gThermals[i];
        levlTher = &gLevelTHER[i];
        // for the first 10 seconds after 4 minutes, reduce the scale of thermal, if test calls for it
        if ((D_8034F850 >= THERM_ENABLE_DURATION) && (gThermalCount != 0) && gThermShouldDisable) {
            var_fs0 = (f32)(1.0 - (f64)((D_8034F850 - THERM_ENABLE_DURATION) / THERM_WEAKEN_DURATION));
        }
        therm->height += levlTher->unk20 * D_8034F854;
        uvMat4SetIdentity(&sp74);
        sp74.m[0][0] = levlTher->scale * var_fs0;
        sp74.m[1][1] = levlTher->scale * var_fs0;
        sp74.m[2][2] = levlTher->height;
        uvMat4RotateAxis(&sp74, therm->height, 'z');
        sp74.m[3][0] = therm->pos.x;
        sp74.m[3][1] = therm->pos.y;
        sp74.m[3][2] = therm->pos.z;
        if (therm->unk0 != 0xFFFF) {
            uvDobjPosm(therm->unk0, 0, &sp74);
        }
    }
}

void therm_80346B84(void) {
    s32 i;

    for (i = 0; i < gThermalCount; i++) {
        if (gThermals[i].unk0 != 0xFFFF) {
            uvDobjModel(gThermals[i].unk0, 0xFFFF);
            gThermals[i].unk0 = 0xFFFF;
        }
    }
}

void therm_80346C08(f32 x, f32 y, f32 z, Vec3F* dst) {
    f32 dz;
    f32 dx;
    f32 dy;
    f32 dist;
    LevelTHER* levlTher;
    Thermal* therm;
    Vec3F vec;
    s32 i;

    dst->x = 0.0f;
    dst->y = 0.0f;
    dst->z = 0.0f;

    for (i = 0; i < gThermalCount; i++) {
        therm = &gThermals[i];
        levlTher = &gLevelTHER[i];
        if (therm->unk0 == 0xFFFF) {
            continue;
        }

        dx = x - therm->pos.x;
        dy = y - therm->pos.y;
        dz = z - therm->pos.z;
        dist = uvLength2D(dx, dy);

        if (levlTher->scale < dist) {
            continue;
        }
        if (levlTher->height < dz) {
            continue;
        }
        if (dz < 0.0f) {
            continue;
        }

        therm_80346E04(levlTher, dx, dy, dz, dist, &vec);
        dst->x += vec.x;
        dst->y += vec.y;
        dst->z += vec.z;

        if (1) { } // fakematch
    }
}

void therm_80346E04(LevelTHER* therm, f32 x, f32 y, f32 z, f32 dist, Vec3F* dst) {
    f32 temp_fv0;
    f32 var_fa0;
    f32 var_fv1;

    temp_fv0 = therm->scale * 0.5f;
    if (dist > 1.0f) {
        if (dist < temp_fv0) {
            var_fa0 = temp_fv0 - dist;
        } else {
            var_fa0 = -(temp_fv0 - dist);
        }
        var_fv1 = 1.0f - ((2.0f * var_fa0) / therm->scale);
        dst->x = therm->unk20 * var_fv1 * dist * (y / dist);
        dst->y = -var_fv1 * therm->unk20 * dist * (x / dist);
    } else {
        dst->x = dst->y = 0.0f;
    }
    var_fv1 = uvSqrtF((therm->scale - dist) / therm->scale);
    if (var_fv1 > 1.0f) {
        var_fv1 = 1.0f;
    }
    if (var_fv1 < 0.0f) {
        var_fv1 = 0.0f;
    }
    dst->z = therm->unk24 * var_fv1;
    if (z < therm->unk18) {
        var_fv1 = 1.0f - ((therm->unk18 - z) / therm->unk18);
    } else if (therm->unk1C < z) {
        var_fv1 = 1.0f - ((z - therm->unk1C) / (therm->height - therm->unk1C));
    } else {
        var_fv1 = 1.0f;
    }
    dst->x *= var_fv1;
    dst->y *= var_fv1;
    dst->z *= var_fv1;
}
