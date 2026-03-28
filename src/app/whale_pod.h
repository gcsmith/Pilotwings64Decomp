#ifndef APP_WHALE_POD_H
#define APP_WHALE_POD_H

#include <uv_vector.h>
#include <PR/ultratypes.h>

void whalePodInit(void);
void whalePodLoad(void);
void whalePodDeinit(void);
void whalePodGetObjState(s32 whaleIdx, s32* objId, f32* interval, Vec3F* pos);
void whalePodSetInterval(s32 whaleIdx, f32 interval);

#endif // APP_WHALE_POD_H
