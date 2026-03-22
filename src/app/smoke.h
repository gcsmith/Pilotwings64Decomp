#ifndef APP_SMOKE_H
#define APP_SMOKE_H

#include <PR/ultratypes.h>

#define SMOKE_FX_1(x, y, z) 1, (x), (y), (z)
#define SMOKE_FX_2(x) 2, (x)
#define SMOKE_FX_3(x) 3, (x)
#define SMOKE_FX_4(x) 4, (x)
#define SMOKE_FX_5(x, y, z) 5, (x), (y), (z)
#define SMOKE_FX_6(x, y, z) 6, (x), (y), (z)
#define SMOKE_FX_7(x) 7, (x)
#define SMOKE_FX_8(x) 8, (x)
#define SMOKE_FX_9(x, y, z) 9, (x), (y), (z)
#define SMOKE_FX_END 0

s16 smoke_create(void);
void smoke_props(s32, ...);
void smoke_getprops(s32, ...);

#endif // APP_SMOKE_H
