#include "common.h"
#include <uv_dobj.h>
#include <uv_math.h>
#include <uv_texture.h>
#include "code_9A960.h"
#include "env_sound.h"
#include "game.h"
#include "hud.h"
#include "level.h"
#include "task.h"
#include "text_data.h"
#include "thermals.h"

#define THERM_ENABLE_DURATION (4 * 60) // 4 minutes in sec
#define THERM_WEAKEN_DURATION (10)
#define THERM_DISABLE_TIME (THERM_ENABLE_DURATION + THERM_WEAKEN_DURATION)

STATIC_DATA s32 sThermShouldDisable = 0; // true when test disables thermals after THERM_ENABLE_DURATION

// unused / leftover .data
f32 pad_D_80350800[] = { 0.0f, 0.0f, 0.0f,  0.0f,  0.0f, 0.0f, 0.0f, 1.0f,  5.0f,  0.05f, 0.0f, 0.0f,  0.975f, 5.5f,  0.06f, 0.04f, 0.03f, 0.88f, 6.0f,  0.0f,
                         0.0f, 0.0f, 0.0f,  17.0f, 0.0f, 0.0f, 0.0f, 0.0f,  18.0f, 0.0f,  0.0f, 0.01f, 0.15f,  18.5f, 0.0f,  0.01f, 0.03f, 0.25f, 19.0f, 0.0f,
                         0.0f, 0.0f, 0.65f, 19.5f, 0.0f, 0.0f, 0.0f, 0.96f, 20.0f, 0.0f,  0.0f, 0.0f,  0.99f,  24.0f, 0.0f,  0.0f,  0.0f,  1.0f,  0.0f };

STATIC_DATA TaskTHER* sTaskTHER;
u8 gThermalCount;
Thermal gThermals[16];
u8 gThermReady;

// forward declarations
STATIC_FUNC void therm_80346E04(TaskTHER* therm, f32 x, f32 y, f32 z, f32 dist, Vec3F* dst);

void thermInit(void) {
    s32 i;
    for (i = 0; i < ARRAY_COUNT(gThermals); i++) {
        gThermals[i].unk0 = 0xFFFF;
    }
    gThermReady = 1;
}

void thermLoad(void) {
    Thermal* therm;
    s32 pad;
    Unk80362690_Unk0* temp_v1_2;
    TaskTHER* taskTherm;
    LevelESND esnd;
    f32 maxDim;
    f32 ratio;
    s32 i;

    if (D_80362690->unkC[D_80362690->unk9C].unk7B == 0) {
        gThermalCount = taskGetTHER(&sTaskTHER);
        if (gThermalCount > ARRAY_COUNT(gThermals)) {
            _uvDebugPrintf("thermals : too many thermals defined in level [%d]\n", gThermalCount);
            gThermalCount = 0;
            return;
        }

        if (gThermalCount != 0) {
            uvLevelAppend(0x16);

            for (i = 0; i < gThermalCount; i++) {
                taskTherm = &sTaskTHER[i];
                therm = &gThermals[i];
                therm->unk0 = uvDobjAllocIdx();
                uvDobjModel(therm->unk0, MODEL_HG_THERMAL_CYLINDER);
                uvDobjState(therm->unk0, 2);
                uvVec3Copy(&gThermals[i].pos, &taskTherm->pos);
                if (taskTherm->height < taskTherm->scale) {
                    maxDim = taskTherm->scale;
                } else {
                    maxDim = taskTherm->height;
                }
                uvDobjProps(therm->unk0, 3, maxDim, 0);
                therm->scale = taskTherm->scale;
                ratio = (f32)i / gThermalCount;
                therm->height = 3.1415927f * ratio;
                uvMat4SetIdentity(&esnd.unk0);
                esnd.unk0.m[3][0] = 0.0f;
                esnd.unk0.m[3][1] = 0.0f;
                esnd.unk0.m[3][2] = 0.0f;
                esnd.sndId = 2;
                esnd.unk5C = 1.0f;
                esnd.unk64 = 0;
                esnd.unk68 = maxDim;
                esnd.unk6C = maxDim;
                esnd.unk70 = (s8)taskTherm->unk14;
                esnd.unk60 = (taskTherm->unk20 * 0.9f) + 0.9f;
                esnd.unk74 = 10;
                esnd.unk40.x = taskTherm->pos.x;
                esnd.unk40.y = taskTherm->pos.y;
                esnd.unk40.z = (f32)(taskTherm->pos.z + (taskTherm->height * 0.5));
                esnd.unk4C.x = taskTherm->pos.x;
                esnd.unk4C.y = taskTherm->pos.y;
                esnd.unk4C.z = (f32)(taskTherm->pos.z - (taskTherm->height * 0.5));
                envSoundLoad(&esnd);
            }
            sThermShouldDisable = 0;
            temp_v1_2 = &D_80362690->unkC[D_80362690->unk9C];
            if ((temp_v1_2->veh == VEHICLE_HANG_GLIDER) && (temp_v1_2->cls == 3) && (temp_v1_2->test == 0)) {
                sThermShouldDisable = 1;
            }
        }
    }
}

void therm_8034695C(void) {
    f32 var_fs0;
    Thermal* therm;
    TaskTHER* taskTherm;
    Mtx4F sp74;
    s32 i;

    var_fs0 = 1.0f;
    // after 4 min, 10 sec, disable thermals, if the test calls for it
    if ((D_8034F850 >= THERM_DISABLE_TIME) && (gThermalCount != 0) && sThermShouldDisable) {
        thermDeinit();
        gThermalCount = 0;
        gThermReady = 0;
        hudWarningText(TEXT_THERM_OFF, 1.5f, 8.0f);
    }

    for (i = 0; i < gThermalCount; i++) {
        therm = &gThermals[i];
        taskTherm = &sTaskTHER[i];
        // for the first 10 seconds after 4 minutes, reduce the scale of thermal, if test calls for it
        if ((D_8034F850 >= THERM_ENABLE_DURATION) && (gThermalCount != 0) && sThermShouldDisable) {
            var_fs0 = (f32)(1.0 - (f64)((D_8034F850 - THERM_ENABLE_DURATION) / THERM_WEAKEN_DURATION));
        }
        therm->height += taskTherm->unk20 * D_8034F854;
        uvMat4SetIdentity(&sp74);
        sp74.m[0][0] = taskTherm->scale * var_fs0;
        sp74.m[1][1] = taskTherm->scale * var_fs0;
        sp74.m[2][2] = taskTherm->height;
        uvMat4RotateAxis(&sp74, therm->height, 'z');
        sp74.m[3][0] = therm->pos.x;
        sp74.m[3][1] = therm->pos.y;
        sp74.m[3][2] = therm->pos.z;
        if (therm->unk0 != 0xFFFF) {
            uvDobjPosm(therm->unk0, 0, &sp74);
        }
    }
}

void thermDeinit(void) {
    s32 i;

    for (i = 0; i < gThermalCount; i++) {
        if (gThermals[i].unk0 != 0xFFFF) {
            uvDobjModel(gThermals[i].unk0, MODEL_WORLD);
            gThermals[i].unk0 = 0xFFFF;
        }
    }
}

void therm_80346C08(f32 x, f32 y, f32 z, Vec3F* dst) {
    f32 dz;
    f32 dx;
    f32 dy;
    f32 dist;
    TaskTHER* taskTherm;
    Thermal* therm;
    Vec3F vec;
    s32 i;

    dst->x = 0.0f;
    dst->y = 0.0f;
    dst->z = 0.0f;

    for (i = 0; i < gThermalCount; i++) {
        therm = &gThermals[i];
        taskTherm = &sTaskTHER[i];
        if (therm->unk0 == 0xFFFF) {
            continue;
        }

        dx = x - therm->pos.x;
        dy = y - therm->pos.y;
        dz = z - therm->pos.z;
        dist = uvLength2D(dx, dy);

        if (taskTherm->scale < dist) {
            continue;
        }
        if (taskTherm->height < dz) {
            continue;
        }
        if (dz < 0.0f) {
            continue;
        }

        therm_80346E04(taskTherm, dx, dy, dz, dist, &vec);
        dst->x += vec.x;
        dst->y += vec.y;
        dst->z += vec.z;

        if (1) { } // fakematch
    }
}

void therm_80346E04(TaskTHER* therm, f32 x, f32 y, f32 z, f32 dist, Vec3F* dst) {
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
