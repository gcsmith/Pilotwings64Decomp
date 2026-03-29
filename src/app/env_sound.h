#ifndef APP_ENV_SOUND_H
#define APP_ENV_SOUND_H

#include <uv_matrix.h>
#include "level.h"

void envSoundInit(void);
void envSoundLoad(LevelESND*);
void envSoundFrameUpdate(Mtx4F*);

#endif // APP_ENV_SOUND_H
