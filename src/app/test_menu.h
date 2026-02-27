#ifndef APP_TEST_MENU_H
#define APP_TEST_MENU_H

#include <PR/ultratypes.h>
#include "code_72B70.h"

extern s32 gCurTestIdx;
extern s32 D_8037DC84;
extern const char* gClassShortNames[];
extern const char* gVehShortNames[];

void testMenuInitText(s32 testIdx);
void testMenuDraw(s32, u8, u8);
u8 testMenuHandler(Unk80367710*);
void testMenu_8034A428(void);

#endif // APP_TEST_MENU_H
