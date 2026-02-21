#include "common.h"
#include <uv_util.h>
#include <uv_dobj.h>
#include <uv_level.h>
#include <uv_matrix.h>
#include <uv_model.h>
#include "code_68220.h"
#include "code_9A960.h"
#include <uv_math.h>

#define WIND_OBJECT_COUNT 0x10
#define INITIAL_MODEL_ID 0xFFFF

// size: 0xCC
typedef struct {
    u16 modelId;
    u16 pad2;
    Mtx4F unk4;
    Mtx4F unk44;
    Mtx4F unk84;
    f32 unkC4;
    f32 unkC8;
} WindObject;

// size: 0x10
typedef struct {
    Vec3F pos;
    u8 unkC; // id or type? value between 0 and 2
} WindObjectData;

// .bss
extern WindObjectData* sWindObjectsData;
extern u8 sWindObjectsInLevel;
extern WindObject sWindObjects[WIND_OBJECT_COUNT];

// windObjectsInit initializes / resets the model ID for all wind objects
void windObjectsInit(void) {
    s32 i;

    // clang-format off: needs to be on one line to match
    for (i = 0; i < WIND_OBJECT_COUNT; i++) { sWindObjects[i].modelId = INITIAL_MODEL_ID; }
    // clang-format on
}

// func_8034E0B4 loads models for wind objects in level?
void func_8034E0B4(void) {
    WindObjectData* windObjectData;
    WindObject* windObject;
    s32 i;

    sWindObjectsInLevel = levelGetWOBJ((void**)&sWindObjectsData);
    if (sWindObjectsInLevel > WIND_OBJECT_COUNT) {
        _uvDebugPrintf("wobjs : too many wind objects defined in level [%d]\n", sWindObjectsInLevel);
        sWindObjectsInLevel = 0;
        return;
    }

    for (i = 0; i < sWindObjectsInLevel; i++) {
        windObject = &sWindObjects[i];
        windObjectData = &sWindObjectsData[i];
        windObject->modelId = uvDobjAllocIdx();
        switch (windObjectData->unkC) {
        case 0:
            uvDobjModel(windObject->modelId, 0x40);
            uvModelGetPosm(0x40, 1, &windObject->unk44);
            uvModelGetPosm(0x40, 2, &windObject->unk84);
            windObject->unkC8 = 0.0f;
            windObject->unkC4 = 0.0f;
            break;
        case 1:
            uvDobjModel(windObject->modelId, 0x53);
            uvModelGetPosm(0x53, 1, &windObject->unk44);
            uvModelGetPosm(0x53, 2, &windObject->unk84);
            windObject->unkC4 = 0.0f;
            break;
        case 2:
            uvDobjModel(windObject->modelId, 0x40);
            break;
        }
        uvMat4SetIdentity(&windObject->unk4);
        windObject->unk4.m[3][0] = windObjectData->pos.f[0];
        windObject->unk4.m[3][1] = windObjectData->pos.f[1];
        windObject->unk4.m[3][2] = windObjectData->pos.f[2];
        uvDobjPosm(windObject->modelId, 0, &sWindObjects[i].unk4);
    }
}

void func_8034E274(void) {
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
        func_802E1754(windObject->unk4.m[3][0], windObject->unk4.m[3][1], windObject->unk4.m[3][2], &spEC);
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
        switch (sWindObjectsData[i].unkC) { /* irregular */
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
            uvDobjPosm(windObject->modelId, 1, &spA0);
            uvMat4Copy(&spA0, &windObject->unk84);
            uvMat4RotateAxis(&spA0, windObject->unkC8, 'x');
            uvDobjPosm(windObject->modelId, 2, &spA0);
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
            uvDobjPosm(windObject->modelId, 1, &spA0);
            uvMat4RotateAxis(&windObject->unk84, 3.0f * temp_fv0_2 * D_8034F854, 'y');
            uvDobjPosm(windObject->modelId, 2, &windObject->unk84);
            break;
        }
    }
}

void func_8034E628(void) {
    WindObject* windObject;
    s32 i;

    for (i = 0; i < sWindObjectsInLevel; i++) {
        windObject = &sWindObjects[i];
        if (windObject->modelId != INITIAL_MODEL_ID) {
            uvDobjModel(windObject->modelId, INITIAL_MODEL_ID);
            windObject->modelId = INITIAL_MODEL_ID;
        }
    }
}

s32 func_8034E6AC(s32 modelId) {
    s32 i;

    for (i = 0; i < sWindObjectsInLevel; i++) {
        if (sWindObjects[i].modelId != INITIAL_MODEL_ID && modelId == sWindObjects[i].modelId) {
            return 1;
        }
    }

    return 0;
}
