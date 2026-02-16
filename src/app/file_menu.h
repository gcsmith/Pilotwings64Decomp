#ifndef APP_FILE_MENU_H
#define APP_FILE_MENU_H

#include <PR/ultratypes.h>

s32 fileMenuTopRender(void);
void fileMenu_802E8AF0(void);
void fileMenu_802E8FF4(s32);
void fileMenuSetup(s32 menu);
void fileMenuSetProps(void);
s32 fileMenuSetText(void);
s32 fileMenuEraseFile(void);
void fileMenu_802E94E0(void);
s32 fileMenuChoose(void);
s32 fileMenu_802E9890(void);
s32 fileMenu_802E9980(void);
s32 fileMenuSubRender(void);
void fileMenuColorLerp(f32 v, f32 x1, f32 y1, f32 z1, f32 x2, f32 y2, f32 z2, f32* xout, f32* yout, f32* zout);
void fileMenu_802E9AE0(void);

#endif // APP_FILE_MENU_H
