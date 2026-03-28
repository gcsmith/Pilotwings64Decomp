#ifndef APP_BOATS_H
#define APP_BOATS_H

#include <PR/ultratypes.h>
#include <uv_matrix.h>

void boatsLoadCrescent(void);
void boatsLoadHoliday(void);
s32 boatsGetPose(s32 boatId, Mtx4F* pose);
void boatsDeinit(void);
void boatsInit(void);
void boatsGetObjData(s32 boatId, s32* objId, f32* interval, Vec3F* pos);
void boatsUpdateInterval(s32 boatId, f32 interval);

#endif // APP_BOATS_H
