#ifndef APP_CODE_99D40_H
#define APP_CODE_99D40_H

#include <PR/ultratypes.h>

// function pointer to draw menu item
extern void (*gFcnDrawMenuItem)(s16, s16, s16);

void func_80312810(s32, s32, s32, f32, f32, s32, s32 itemCount);
void func_80312908(void);
void func_80312B50(void);
void func_80312B5C(void);
void func_80312F38(void);
void func_80312F44(s32);

#endif // APP_CODE_99D40_H
