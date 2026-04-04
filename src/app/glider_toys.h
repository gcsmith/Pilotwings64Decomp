#ifndef APP_GLIDER_TOY_H
#define APP_GLIDER_TOY_H

#include <uv_vector.h>

void gliderToyLoadCrescent(void);
void gliderToyLoadLStates(void);
void gliderToyLoadHoliday(void);
void gliderToyLoadEFrost(void);
void gliderToyInit(void);
void gliderToyDeinit(void);
void gliderToyGetObjData(s32 idx, s32* objId, f32* interval, Vec3F* pos);
void gliderToySetInterval(s32 idx, f32 interval);

#endif // APP_GLIDER_TOY_H
