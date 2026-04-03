#ifndef APP_SPLASH_H
#define APP_SPLASH_H

#include <uv_matrix.h>

void splashDraw(void);
void splashAdd(Mtx4F* pos, f32 size);
void splashUpdate(void);
void splashInit(void);
void splashClear(void);

#endif // APP_SPLASH_H
