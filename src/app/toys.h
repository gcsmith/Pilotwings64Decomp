#ifndef APP_TOYS_H
#define APP_TOYS_H

#include "game.h"
#include "level.h"

void toyInit(void);
void toyLoad(LevelTOYS*);
void toyDeinit(void);
void toy_80348418(s32, f32, f32, f32, s32);

#endif // APP_TOYS_H
