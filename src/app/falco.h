#ifndef APP_FALCO_H
#define APP_FALCO_H

#include <PR/ultratypes.h>

extern s32 D_8035A5F0;

void falcoInit(void);
void falcoLoad(void);
void falcoDeinit(void);
void falcoFrameUpdate(void);
s32 falco_802E51E8(s32, f32, f32, f32);
s32 falco_802E57C4(void);
s32 falco_802E5818(void);
void falco_802E64E0(s32, Mtx4F*);

#endif // APP_FALCO_H
