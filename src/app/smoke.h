#ifndef APP_SMOKE_H
#define APP_SMOKE_H

#include <PR/ultratypes.h>

#define SMOKE_PROP_1(x, y, z) 1, (x), (y), (z)
#define SMOKE_PROP_2(x) 2, (x)
#define SMOKE_PROP_3(x) 3, (x)
#define SMOKE_PROP_4(x) 4, (x)
#define SMOKE_PROP_5(x, y, z) 5, (x), (y), (z)
#define SMOKE_PROP_6(x, y, z) 6, (x), (y), (z)
#define SMOKE_PROP_7(x) 7, (x)
#define SMOKE_PROP_8(x) 8, (x)
#define SMOKE_PROP_9(x, y, z) 9, (x), (y), (z)
#define SMOKE_PROP_END 0

void smokeInit(void);
s32 smokeCreate(void);
void smokeProps(s32, ...);
void smokeGetProps(s32, ...);
void smokeDelete(s32);
void smokeDeleteAll(void);
void func_80336600(void);

#endif // APP_SMOKE_H
