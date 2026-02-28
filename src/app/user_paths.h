#ifndef APP_USER_PATHS_H
#define APP_USER_PATHS_H

#include <PR/ultratypes.h>
#include <uv_vector.h>
#include "code_A6000.h"

void userPathInit(void);
Unk8037DCA0* userPath_8034A4F8(s32 arg0);
void userPathFree(s32 path);
void userPath_8034A8B0(Unk8037DCA0* arg0, u8 arg1, f32 arg2);
// arg0 is the actual struct and not a pointer to it
void userPath_8034A950(Unk8037DCA0_Unk4C arg0, f32* arg183);

#endif // APP_USER_PATHS_H
