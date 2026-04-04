#ifndef APP_BONUS_H
#define APP_BONUS_H

#include <uv_matrix.h>

void bonusInit(void);
void bonusUpdateState(void);
void bonusLoad(void);
void bonusFrameUpdate(Mtx4F*);
void bonusDeinit(void);

#endif // APP_BONUS_H
