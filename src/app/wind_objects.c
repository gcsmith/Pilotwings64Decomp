#include "common.h"
#include <uv_dobj.h>
#include <uv_math.h>
#include <uv_matrix.h>
#include <uv_model.h>
#include "code_9A960.h"
#include "environment.h"
#include "level.h"

#define WIND_OBJECT_COUNT 0x10
#define INITIAL_OBJECT_ID 0xFFFF

// size: 0xCC
typedef struct {
    u16 objId;
    u16 pad2;
    Mtx4F unk4;
    Mtx4F unk44;
    Mtx4F unk84;
    f32 unkC4;
    f32 unkC8;
} WindObject;

// .bss
STATIC_DATA LevelWOBJ* sWindObjectsData;
STATIC_DATA u8 sWindObjectsInLevel;
STATIC_DATA WindObject sWindObjects[WIND_OBJECT_COUNT];

// windObjInit initializes / resets the model ID for all wind objects
void windObjInit(void) {
    s32 i;

    // clang-format off: needs to be on one line to match
    for (i = 0; i < WIND_OBJECT_COUNT; i++) { sWindObjects[i].objId = INITIAL_OBJECT_ID; }
    // clang-format on
}

// windObjectsLoad loads models for wind objects in level
void windObjLoad(void) {
    LevelWOBJ* windObjectData;
    WindObject* windObject;
    s32 i;

    sWindObjectsInLevel = levelGetWOBJ(&sWindObjectsData);
    if (sWindObjectsInLevel > WIND_OBJECT_COUNT) {
        _uvDebugPrintf("wobjs : too many wind objects defined in level [%d]\n", sWindObjectsInLevel);
        sWindObjectsInLevel = 0;
        return;
    }

    for (i = 0; i < sWindObjectsInLevel; i++) {
        windObject = &sWindObjects[i];
        windObjectData = &sWindObjectsData[i];
        windObject->objId = uvDobjAllocIdx();
        switch (windObjectData->type) {
        case WIND_OBJ_WINDSOCK_JOINTED:
            uvDobjModel(windObject->objId, MODEL_WIND_SOCK_YELLOW_BLUE);
            uvModelGetPosm(MODEL_WIND_SOCK_YELLOW_BLUE, 1, &windObject->unk44);
            uvModelGetPosm(MODEL_WIND_SOCK_YELLOW_BLUE, 2, &windObject->unk84);
            windObject->unkC8 = 0.0f;
            windObject->unkC4 = 0.0f;
            break;
        case WIND_OBJ_TURBINE:
            uvDobjModel(windObject->objId, MODEL_WIND_TURBINE);
            uvModelGetPosm(MODEL_WIND_TURBINE, 1, &windObject->unk44);
            uvModelGetPosm(MODEL_WIND_TURBINE, 2, &windObject->unk84);
            windObject->unkC4 = 0.0f;
            break;
        case WIND_OBJ_WINDSOCK_SIMPLE:
            uvDobjModel(windObject->objId, MODEL_WIND_SOCK_YELLOW_BLUE);
            break;
        }
        uvMat4SetIdentity(&windObject->unk4);
        windObject->unk4.m[3][0] = windObjectData->pos.f[0];
        windObject->unk4.m[3][1] = windObjectData->pos.f[1];
        windObject->unk4.m[3][2] = windObjectData->pos.f[2];
        uvDobjPosm(windObject->objId, 0, &sWindObjects[i].unk4);
    }
}

void windObjFrameUpdate(void) {
    WindObject* windObject;
    f32 temp_fa0;
    Vec3F spEC;
    Vec3F spE0;
    Mtx4F spA0;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 var_fs0;
    f32 var_fs2;
    s32 i;

    for (i = 0; i < sWindObjectsInLevel; i++) {
        windObject = &sWindObjects[i];
        env_802E1754(windObject->unk4.m[3][0], windObject->unk4.m[3][1], windObject->unk4.m[3][2], &spEC);
        spE0.f[0] = spEC.f[0];
        spE0.f[1] = spEC.f[1];
        spE0.f[2] = 0.0f;
        temp_fv0 = uvVec3Len(&spE0);
        if (temp_fv0 != 0.0f) {
            var_fs2 = uvAtan2F(spE0.f[1] / temp_fv0, spE0.f[0] / temp_fv0) - 1.5707963f;
        } else {
            var_fs2 = 0.0f;
        }
        temp_fv0_2 = uvVec3Len(&spEC);
        if (temp_fv0_2 != 0 /*.0f*/) {
            var_fs0 = temp_fv0 / 3.0f;
        } else {
            var_fs0 = 0.0f;
        }
        if (var_fs0 < 0.0f) {
            var_fs0 = 0.0f;
        } else if (var_fs0 > 1.0f) {
            var_fs0 = 1.0f;
        }
        switch (sWindObjectsData[i].type) { /* irregular */
        case 2:
            break;
        case 0:
            // clang-format off:ifs needs to be on one line to match
            // 1.5707963f is almost DEG_TO_RAD(90)
            // 6.2831855f matches DEG_TO_RAD(360)
            if ((var_fs2 - windObject->unkC4) > 1.5707963f) { windObject->unkC4 += 6.2831855f; }

            // -1.5707963f is almost -DEG_TO_RAD(90)
            // 6.2831855f matches DEG_TO_RAD(360)
            if ((var_fs2 - windObject->unkC4) < -1.5707963f) { windObject->unkC4 -= 6.2831855f; }
            // clang-format on

            windObject->unkC4 = func_80313AF4(var_fs2, windObject->unkC4, 3.0f * var_fs0);
            windObject->unkC8 = func_80313AF4((1.0471975f * var_fs0) + -0.1745329f, windObject->unkC8, 3.0f);
            uvMat4Copy(&spA0, &windObject->unk44);
            uvMat4RotateAxis(&spA0, windObject->unkC4, 'z');
            uvDobjPosm(windObject->objId, 1, &spA0);
            uvMat4Copy(&spA0, &windObject->unk84);
            uvMat4RotateAxis(&spA0, windObject->unkC8, 'x');
            uvDobjPosm(windObject->objId, 2, &spA0);
            break;
        case 1:
            // clang-format off:ifs needs to be on one line to match
            temp_fa0 = var_fs2 + 3.1415927f; // PI or DEG_TO_RAD(180)
            // 1.5707963f is almost DEG_TO_RAD(90)
            // 6.2831855f matches DEG_TO_RAD(360)
            if ((temp_fa0 - windObject->unkC4) > 1.5707963f) { windObject->unkC4 += 6.2831855f; }
            // -1.5707963f is almost -DEG_TO_RAD(90)
            // 6.2831855f matches DEG_TO_RAD(360)
            if ((temp_fa0 - windObject->unkC4) < -1.5707963f) { windObject->unkC4 -= 6.2831855f; }
            // clang-format on

            windObject->unkC4 = func_80313AF4(temp_fa0, windObject->unkC4, 0.3f);
            uvMat4Copy(&spA0, &windObject->unk44);
            uvMat4RotateAxis(&spA0, windObject->unkC4, 'z');
            uvDobjPosm(windObject->objId, 1, &spA0);
            uvMat4RotateAxis(&windObject->unk84, 3.0f * temp_fv0_2 * D_8034F854, 'y');
            uvDobjPosm(windObject->objId, 2, &windObject->unk84);
            break;
        }
    }
}

void windObjDeinit(void) {
    WindObject* windObject;
    s32 i;

    for (i = 0; i < sWindObjectsInLevel; i++) {
        windObject = &sWindObjects[i];
        if (windObject->objId != INITIAL_OBJECT_ID) {
            uvDobjModel(windObject->objId, MODEL_WORLD);
            windObject->objId = INITIAL_OBJECT_ID;
        }
    }
}

s32 windObjIsLoadedId(s32 objId) {
    s32 i;

    for (i = 0; i < sWindObjectsInLevel; i++) {
        if (sWindObjects[i].objId != INITIAL_OBJECT_ID && objId == sWindObjects[i].objId) {
            return TRUE;
        }
    }

    return FALSE;
}
