#ifndef APP_SNAP_H
#define APP_SNAP_H

#include <PR/ultratypes.h>
#include "code_72B70.h"

#define PHOTO_COUNT_MAX 6

void func_80337D50(void);
void snapInit(void);
void snapDeinit(void);
void func_80339E1C(VehicleData*);
s32 func_8033E3A8(s32);
s32 func_8033F62C(void);
s32 snapGetPhotoCount(void);
s32 func_80338614(void);

#endif // APP_SNAP_H
