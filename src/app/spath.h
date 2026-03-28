#ifndef APP_SPATH_H
#define APP_SPATH_H

#include <PR/ultratypes.h>
#include <uv_matrix.h>
#include <uv_vector.h>

// loads file index userFile and returns path ID
s32 spathLoadFile(s32 userFile);

// frees up path ID previously obtained from spathLoadFile
void spathFree(s32 pathId);

// creates pose matrix from interpolating points in path pathId
// mtx: resulting pose matrix of interpolated (x,y,z)+(h,p,r)
// time: desired time to interpolate pose
// posScale: scales position data
// timeScale: scales time diff between adjacent points
void spathScaleUpdate(Mtx4F* pose, s32 pathId, f32 time, f32 posScale, f32 timeScale);

// creates pose matrix from interpolating points in path pathId
// mtx: resulting pose matrix of interpolated (x,y,z)+(h,p,r)
// time: desired time to interpolate pose
// posScale: scales position data
void spathUpdate(Mtx4F* pose, s32 pathId, f32 time, f32 posScale);

// creates vector and angles from interpolating points in path pathId at given time
void spathInterpolate(Vec3F* vecOut, f32* angOut1, f32* angOut2, s32 pathId, f32 time);

#endif // APP_SPATH_H
