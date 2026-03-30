#include "common.h"
#include <uv_math.h>
#include <uv_memory.h>
#include "code_9A960.h"
#include "environment.h"
#include "game.h"
#include "snow.h"

#define SNOWFLAKE_COUNT 800

typedef struct SnowData {
    struct SnowData* self;
    Vec3F unk4[SNOWFLAKE_COUNT];
    u8 unk2584[SNOWFLAKE_COUNT];
    u32 fbIdx[SNOWFLAKE_COUNT]; // array of framebuffer indexes to draw snow
    s32 unk3524;
    u32* endPtr; // pointer inside fbIdx
} SnowData;      // size = 0x352C

typedef struct {
    Vec3F min;
    Vec3F max;
} MinMaxVals;

static s32 D_80350610 = 0xD; // unused
static MinMaxVals sSnowBounds[] = {
    {   { 310.0f, 34.0f, 151.0f },  { 350.6f, 62.64f, 167.0f } },
    { { 240.0f, 123.0f, 121.47f }, { 344.58f, 154.2f, 159.3f } }
};

static SnowData* sSnowData;
static Vec3F D_80373EF8;

// forward declarations
STATIC_FUNC s32 snowCheckRange(Mtx4F*);

STATIC_FUNC void snowCreate(void) {
    s32 i;

    if ((sSnowData == NULL) || (sSnowData != sSnowData->self)) {
        sSnowData = (SnowData*)_uvMemAllocAlign8(sizeof(SnowData));
        sSnowData->self = sSnowData;
        sSnowData->endPtr = NULL;
        sSnowData->unk3524 = FALSE;
        for (i = 0; i < SNOWFLAKE_COUNT; i++) {
            sSnowData->unk4[i].x = uvRandF_RANLUX() * 200.0f;
            sSnowData->unk4[i].y = uvRandF_RANLUX() * 200.0f;
            sSnowData->unk4[i].z = uvRandF_RANLUX() * 200.0f;
            sSnowData->unk2584[i] = TRUE;
        }
    }
}

STATIC_FUNC s32 snowDraw(void* fb, UNUSED s32 arg1) {
    u32* endPtr;
    u32* idxPtr;
    u16* fb16 = fb;

    if ((sSnowData == NULL) || (sSnowData != sSnowData->self)) {
        snowCreate();
    } else {
        endPtr = sSnowData->endPtr;
        idxPtr = sSnowData->fbIdx;
        if (endPtr != NULL) {
            for (idxPtr = sSnowData->fbIdx; idxPtr < endPtr; idxPtr++) {
                fb16[*idxPtr] = 0xFFFF;
            }
        }
    }
    return 0;
}

void snowUpdate(void) {
    s32 i;
    Mtx4F spD4;
    Mtx4F sp94;
    Vec3F sp88;
    Vec3F* temp_a2;
    Vec3F sp78;
    u32* idxPtr;
    Vec3F sp68;
    Vec3F sp5C;
    f32 sp58;
    f32 zLim[2];
    f32 yLim[2];
    f32 xLim[2];
    Vec3F sp34;
    s32 x32;
    s32 z32;

    sp58 = D_8034F854 * 15.0f;
    if ((sSnowData == NULL) || (sSnowData != sSnowData->self)) {
        snowCreate();
    }

    uvGfxSetCallback(snowDraw);
    sSnowData->endPtr = idxPtr = sSnowData->fbIdx;
    func_80205724(0, 3, &spD4);
    uvMat4InvertTranslationRotation(&sp94, &spD4);
    sSnowData->unk3524 = snowCheckRange(&sp94);
    sp88.f[0] = sp94.m[3][0] + (sp94.m[1][0] * 100.f); // TODO f[] vs .x
    sp88.f[1] = sp94.m[3][1] + (sp94.m[1][1] * 100.f);
    sp88.f[2] = sp94.m[3][2] + (sp94.m[1][2] * 100.f);
    sp68.x = D_80373EF8.x - sp94.m[3][0];
    D_80373EF8.x = sp94.m[3][0];
    sp68.y = D_80373EF8.y - sp94.m[3][1];
    D_80373EF8.y = sp94.m[3][1];
    sp68.z = D_80373EF8.z - sp94.m[3][2];
    D_80373EF8.z = sp94.m[3][2];

    func_802E1754(sp88.x, sp88.y, sp88.z, &sp78);

    sp5C.x = (sp78.x * sp58) + (sp68.x * 3.0f);
    sp5C.y = (sp78.y * sp58) + (sp68.y * 3.0f);
    sp5C.z = sp68.z - sp58;
    xLim[0] = sp88.x - 100.0f - 1.0f;
    xLim[1] = sp88.x + 100.0f + 1.0f;
    yLim[0] = sp88.y - 100.0f - 1.0f;
    yLim[1] = sp88.y + 100.0f + 1.0f;
    zLim[0] = sp88.z - 100.0f - 1.0f;
    zLim[1] = sp88.z + 100.0f + 1.0f;

    for (i = 0; i < ARRAY_COUNT(sSnowData->unk4); i++) {
        temp_a2 = &sSnowData->unk4[i];
        temp_a2->x += sp5C.x;
        temp_a2->y += sp5C.y;
        temp_a2->z += sp5C.f[2]; // TODO f[] vs .z

        if (!(temp_a2->x > xLim[0]) || !(temp_a2->x < xLim[1]) || !(temp_a2->y > yLim[0]) || !(temp_a2->y < yLim[1]) || !(temp_a2->z > zLim[0]) ||
            !(temp_a2->z < zLim[1])) {
            while (temp_a2->x < xLim[0]) {
                temp_a2->x += 200.0f;
            }
            while (temp_a2->x > xLim[1]) {
                temp_a2->x -= 200.0f;
            }
            while (temp_a2->y < yLim[0]) {
                temp_a2->y += 200.0f;
            }
            while (temp_a2->y > yLim[1]) {
                temp_a2->y -= 200.0f;
            }
            while (temp_a2->z < zLim[0]) {
                temp_a2->z += 200.0f;
            }
            while (temp_a2->z > zLim[1]) {
                temp_a2->z -= 200.0f;
            }

            // @fakematch to force D_80373EF0->unk3524 into v1
            if (!sSnowData->unk3524) { }
            sSnowData->unk2584[i] = sSnowData->unk3524 == FALSE;

        } else if (sSnowData->unk2584[i]) {
            uvMat4LocalToWorld(&spD4, &sp34, temp_a2);
            if (sp34.y < 0.0f) {
                continue;
            }

            sp34.x *= 200.0f / sp34.y;
            sp34.z *= 200.0f / sp34.y;
            if (sp34.x > -150.0f && sp34.x < 150.0f && sp34.z > -102.0f && sp34.z < 112.0f) {
                x32 = (s32)sp34.x;
                z32 = (s32)sp34.z;
                *idxPtr++ = (x32 - (z32 * 320)) + 0x96A0;
            }
        }
    }
    sSnowData->endPtr = idxPtr;
}

STATIC_FUNC s32 snowCheckRange(Mtx4F* arg0) {
    MinMaxVals* var_a1;
    f32 x;
    f32 y;
    f32 z;
    s32 i;
    s32 ret;

    ret = FALSE;

    if (D_80362690->unkC[D_80362690->unk9C].unk8 != 0) {
        ret = TRUE;
    } else {
        x = arg0->m[3][0];
        y = arg0->m[3][1];
        z = arg0->m[3][2];
        for (i = 0; i < ARRAY_COUNT(sSnowBounds); i++) {
            var_a1 = &sSnowBounds[i];
            if ((x > var_a1->min.x) && (x < var_a1->max.x) && (y > var_a1->min.y) && (y < var_a1->max.y) && (z > var_a1->min.z) && (z < var_a1->max.z)) {
                ret = TRUE;
                break;
            }
        }
    }
    return ret;
}

void snowEnable(void) {
    uvGfxSetCallback(snowDraw);
}

void snowDisable(void) {
    uvGfxSetCallback(NULL);
}
