#ifndef APP_WIND_OBJECTS_H
#define APP_WIND_OBJECTS_H

#include <PR/ultratypes.h>

void windObjInit(void);
void windObjLoad(void);
void windObjFrameUpdate(void);
void windObjDeinit(void);
s32 windObjIsLoadedId(s32 objId);

#endif // APP_WIND_OBJECTS_H
