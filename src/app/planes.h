#ifndef APP_PLANES_H
#define APP_PLANES_H

#include <uv_vector.h>

// get x,y,z of plane index
void planesGetPos(s32 planeIdx, Vec3F* vec);

// load plane models and paths
void planesLoad(void);

// unload models and paths
void planesDeinit(void);

// initialize planes data
void planesInit(void);

// get objId and position information from plane
// if plane not loaded, sets obId to 0xFFFF
void planesGetObjData(s32 planeIdx, s32* objId, f32*, Vec3F* vec);

void planesUpdateInterval(s32 planeIdx, f32 interval);

#endif // APP_PLANES_H
