#include "common.h"
#include <uv_filesystem.h>
#include <uv_math.h>
#include <uv_memory.h>
#include "code_9A960.h"
#include "code_D1ED0.h"
#include "spath.h"

typedef struct {
    f32 time;
    f32 val;
} PathTimeVal; // size = 0x8

typedef struct {
    u32 count;
    PathTimeVal v[40];
} PathAxis; // size = 0x144

typedef struct {
    PathAxis scpx;
    PathAxis scpy;
    PathAxis scpz;
    PathAxis scph;
    PathAxis scpp;
    PathAxis scpr;
    u8 inUse;
    u8 pad799[3];
} SPath; // size = 0x79C

static SPath sSpathData[6];

static f32 sSpathCoef[4][4] = {
    {  2.0f, -2.0f,  1.0f,  1.0f },
    { -3.0f,  3.0f, -2.0f, -1.0f },
    {  0.0f,  0.0f,  1.0f,  0.0f },
    {  1.0f,  0.0f,  0.0f,  0.0f }
};

// forward declarations
f32 spath_80340CB8(PathAxis*, f32);
f32 spath_80340E7C(PathAxis*, f32, u32, f32, f32);

s32 spathCreate(void) {
    s32 i;
    for (i = 0; i < ARRAY_COUNT(sSpathData); i++) {
        if (sSpathData[i].inUse == FALSE) {
            return i;
        }
    }
    _uvDebugPrintf("SPath : Too many outstanding paths\n");
    return -1;
}

s32 spathLoadFile(s32 userFile) {
    SPath* spath;
    u32 tag;
    s32 pathId;
    u32 size;
    s32 fileIdx;
    void* src;

    pathId = spathCreate();
    if (pathId == -1) {
        return -1;
    }

    spath = &sSpathData[pathId];
    spath->inUse = TRUE;
    fileIdx = uvFileReadHeader(uvUserFileRead(userFile, MEM_ROM_OFFSET));
    while ((tag = uvFileReadBlock(fileIdx, &size, &src, 1)) != 0) {
        switch (tag) {
        case 'SCPX':
            _uvMediaCopy(&spath->scpx, src, size);
            break;
        case 'SCPY':
            _uvMediaCopy(&spath->scpy, src, size);
            break;
        case 'SCPZ':
            _uvMediaCopy(&spath->scpz, src, size);
            break;
        case 'SCPH':
            _uvMediaCopy(&spath->scph, src, size);
            break;
        case 'SCPP':
            _uvMediaCopy(&spath->scpp, src, size);
            break;
        case 'SCPR':
            _uvMediaCopy(&spath->scpr, src, size);
            break;
        }
    }
    uvFile_80223F30(fileIdx);
    return pathId;
}

void spathFree(s32 pathId) {
    if (sSpathData[pathId].inUse != TRUE) {
        _uvDebugPrintf("Spath: Freed unused path %d\n", pathId);
        return;
    }
    sSpathData[pathId].inUse = FALSE;
}

void spathScaleUpdate(Mtx4F* pose, s32 pathId, f32 time, f32 posScale, f32 timeScale) {
    SPath* spath;
    f32 x;
    f32 y;
    f32 z;
    f32 heading;
    f32 pitch;
    f32 roll;
    s32 prevIdx;
    Vec3F p1;
    Vec3F p2;
    s32 idx;
    u32 nextIdx;
    f32 sp40;

    if ((pathId < 0) || (pathId >= ARRAY_COUNT(sSpathData))) {
        _uvDebugPrintf("spath_update: pathid invalid  <%d>\n");
        return;
    }
    spath = &sSpathData[pathId];

    for (idx = 1; (u32)idx < spath->scpx.count && spath->scpx.v[idx].time < time; idx++) { }

    // four indexes in this order: [(idx-2), (idx-1), idx, (idx+1)]
    // idx is the index with time >= time requested
    nextIdx = idx + 1;
    if (nextIdx >= spath->scpx.count) {
        nextIdx = 0;
    }
    prevIdx = idx - 2;
    if (prevIdx < 0) {
        prevIdx = spath->scpx.count - 1;
    }
    p1.x = spath->scpx.v[idx - 1].val - spath->scpx.v[prevIdx].val;
    p1.y = spath->scpy.v[idx - 1].val - spath->scpy.v[prevIdx].val;
    p1.z = spath->scpz.v[idx - 1].val - spath->scpz.v[prevIdx].val;
    func_8034B2B0(&p1);
    sp40 = FABS(spath->scpx.v[idx].time - spath->scpx.v[idx - 1].time) * 0.01f * timeScale;
    p1.x *= sp40;
    p1.y *= sp40;
    p1.z *= sp40;

    p2.x = spath->scpx.v[nextIdx].val - spath->scpx.v[idx].val;
    p2.y = spath->scpy.v[nextIdx].val - spath->scpy.v[idx].val;
    p2.z = spath->scpz.v[nextIdx].val - spath->scpz.v[idx].val;
    func_8034B2B0(&p2);
    p2.x *= sp40;
    p2.y *= sp40;
    p2.z *= sp40;

    x = spath_80340E7C(&spath->scpx, time, idx, p1.x, p2.x) * posScale;
    y = spath_80340E7C(&spath->scpy, time, idx, p1.y, p2.y) * posScale;
    z = spath_80340E7C(&spath->scpz, time, idx, p1.z, p2.z) * posScale;
    heading = spath_80340CB8(&spath->scph, time) * 0.01745329f;
    pitch = spath_80340CB8(&spath->scpp, time) * 0.01745329f;
    roll = spath_80340CB8(&spath->scpr, time) * 0.01745329f;
    func_80313640(x, y, z, heading, pitch, roll, pose);
}

void spathUpdate(Mtx4F* pose, s32 pathId, f32 time, f32 posScale) {
    SPath* spath;
    f32 x;
    f32 y;
    f32 z;
    f32 h;
    f32 p;
    f32 r;

    if ((pathId < 0) || (pathId >= ARRAY_COUNT(sSpathData))) {
        _uvDebugPrintf("spath_update: pathid invalid  <%d>\n", pathId);
        return;
    }

    spath = &sSpathData[pathId];
    x = spath_80340CB8(&spath->scpx, time) * posScale;
    y = spath_80340CB8(&spath->scpy, time) * posScale;
    z = spath_80340CB8(&spath->scpz, time) * posScale;
    h = spath_80340CB8(&spath->scph, time) * 0.01745329f;
    p = spath_80340CB8(&spath->scpp, time) * 0.01745329f;
    r = spath_80340CB8(&spath->scpr, time) * 0.01745329f;
    func_80313640(x, y, z, h, p, r, pose);
}

// some sort of cubic interpolation with only time input
f32 spath_80340CB8(PathAxis* path, f32 time) {
    PathTimeVal* valsEnd;
    PathTimeVal* valsPt;
    f32 sp50[4];
    f32 coef[4];
    PathTimeVal* vals;
    f32 t1;
    f32 tpow[2];
    f32 pad;
    s32 j;
    s32 pathCount;
    s32 i;
    s32 idx;

    vals = &path->v[0];
    pathCount = path->count;
    if (time <= vals[0].time) {
        return vals[0].val;
    }
    valsEnd = vals;
    valsEnd += pathCount;
    if (time >= valsEnd[-1].time) {
        return valsEnd[-1].val;
    }

    for (idx = 1; idx < pathCount && vals[idx].time < time; idx++) { }

    valsPt = vals;
    valsPt += idx;
    t1 = (time - valsPt[-1].time) / (valsPt[0].time - valsPt[-1].time);
    sp50[0] = valsPt[-1].val;
    sp50[1] = valsPt[0].val;
    sp50[2] = 1.0f;
    sp50[3] = -1.0f;
    tpow[1] = SQ(t1);
    tpow[0] = CUBE(t1);

    for (i = 0; i < ARRAY_COUNT(sSpathCoef); i++) {
        coef[i] = sSpathCoef[i][0] * sp50[0];
        for (j = 1; j < ARRAY_COUNT(sSpathCoef[i]); j++) {
            coef[i] += sSpathCoef[i][j] * sp50[j];
        }
    }
    return (tpow[0] * coef[0]) + (tpow[1] * coef[1]) + (t1 * coef[2]) + (1 * coef[3]);
}

// some sort of cubic interpolation with time and input values
f32 spath_80340E7C(PathAxis* path, f32 time, u32 idx, f32 ptA, f32 ptB) {
    PathTimeVal* vals = path->v;
    s32 pathCount = path->count;
    f32 sp48[4];
    f32 coef[4];
    f32 t1;
    f32 pad;
    f32 tpow[2];
    s32 i;
    s32 j;
    PathTimeVal* valsEnd;
    PathTimeVal* valsPt;

    if (time <= vals[0].time) {
        return vals[0].val;
    }
    valsEnd = vals;
    valsEnd += pathCount;
    if (time >= valsEnd[-1].time) {
        return valsEnd[-1].val;
    }

    valsPt = vals;
    valsPt += idx;
    t1 = (time - valsPt[-1].time) / (valsPt[0].time - valsPt[-1].time);
    sp48[0] = valsPt[-1].val;
    sp48[1] = valsPt[0].val;
    sp48[2] = ptA;
    sp48[3] = ptB;
    tpow[1] = SQ(t1);
    tpow[0] = CUBE(t1);

    for (i = 0; i < ARRAY_COUNT(sSpathCoef); i++) {
        coef[i] = sSpathCoef[i][0] * sp48[0];
        for (j = 1; j < ARRAY_COUNT(sSpathCoef[i]); j++) {
            coef[i] += sSpathCoef[i][j] * sp48[j];
        }
    }
    return (tpow[0] * coef[0]) + (tpow[1] * coef[1]) + (t1 * coef[2]) + (1 * coef[3]);
}

void spathInterpolate(Vec3F* vecOut, f32* angOut1, f32* angOut2, s32 pathId, f32 time) {
    PathTimeVal* posAxis;
    PathTimeVal* valsPt;
    f32 dTime;
    PathTimeVal* posVals;
    Vec3F spDC;
    Vec3F spD0;
    f32 spC0[4];
    f32 coef[4];
    f32 t[4];
    f32 dt[4];
    SPath* temp_ra;
    f32 sp88;
    f32 t1;
    s32 i, j, k;
    s32 idx;
    s32 pathCount;
    PathTimeVal* rotVals;
    PathAxis* rotAxis;
    f32 len;
    f32 temp_fv1;

    temp_ra = &sSpathData[pathId];
    pathCount = temp_ra->scpx.count;
    posAxis = temp_ra->scpx.v;

    for (idx = 1; idx < pathCount && posAxis[idx].time < time; idx++) { }

    valsPt = posAxis;
    valsPt += idx;
    dTime = (valsPt[0].time - valsPt[-1].time);
    t1 = (time - valsPt[-1].time) / dTime;
    // t are powers of time (t^0, t^1, t^2, t^3)
    t[3] = 1;
    t[2] = t1;
    t[1] = SQ(t1);
    t[0] = CUBE(t1);
    // dt are derivatives
    dt[3] = 0.0f;
    dt[2] = 1;
    dt[1] = 2 * t1;
    dt[0] = 3.0f * t1 * t1;

    for (i = 0; i < 3; i++) {
        switch (i) {
        case 0:
            rotAxis = &temp_ra->scph;
            break;
        case 1:
            posAxis = temp_ra->scpy.v;
            rotAxis = &temp_ra->scpp;
            break;
        case 2:
            posAxis = temp_ra->scpz.v;
            rotAxis = &temp_ra->scpr;
            break;
        default:
            break;
        }
        posVals = posAxis;
        posVals += idx;
        rotVals = rotAxis->v + idx;
        spC0[0] = posVals[-1].val;
        spC0[1] = posVals->val;
        spC0[2] = rotVals[-1].val * dTime;
        spC0[3] = rotVals->val * dTime;

        for (j = 0; j < ARRAY_COUNT(sSpathCoef); j++) {
            coef[j] = sSpathCoef[j][0] * spC0[0];
            for (k = 1; k < 4; k++) {
                coef[j] += sSpathCoef[j][k] * spC0[k];
            }
        }

        switch (i) {
        case 0:
            spDC.z = (t[0] * coef[0]) + (t[1] * coef[1]) + (t1 * coef[2]) + (coef[3] * 1);
            spD0.z = ((dt[0] * coef[0]) + (dt[1] * coef[1]) + (coef[2] * 1)) / dTime;
            break;
        case 1:
            spDC.y = (t[0] * coef[0]) + (t[1] * coef[1]) + (t1 * coef[2]) + (coef[3] * 1);
            spD0.y = ((dt[0] * coef[0]) + (dt[1] * coef[1]) + (coef[2] * 1)) / dTime;
            break;
        case 2:
            spDC.x = (t[0] * coef[0]) + (t[1] * coef[1]) + (t1 * coef[2]) + (coef[3] * 1);
            spD0.x = ((dt[0] * coef[0]) + (dt[1] * coef[1]) + (coef[2] * 1)) / dTime;
            break;
        }
    }

    len = uvSqrtF(SQ(spD0.z) + SQ(spD0.y));
    *angOut1 = uvAtan2F(-spD0.z / len, spD0.y / len);
    temp_fv1 = (spDC.z * spD0.z) + (spDC.y * spD0.y);
    sp88 = FABS(temp_fv1) / uvSqrtF(SQ(spDC.z) + SQ(spDC.y));
    len = uvSqrtF(SQ(spD0.x) + SQ(sp88));
    *angOut2 = uvAtan2F(spD0.x / len, sp88 / len);
    vecOut->x = spDC.z;
    vecOut->y = spDC.y;
    vecOut->z = spDC.x;
}
