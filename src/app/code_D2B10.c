#include <uv_debug.h>
#include <uv_graphics.h>
#include <uv_geometry.h>
#include "camera.h"
#include "code_D2B10.h"
#include "hud.h"
#include "splash.h"

void func_8034B5E0(u8 arg0, Camera* camera) {
    cameraInit(arg0, camera);
    uvChan_80204AB0(camera->unk22C, 1, func_8034B6F8);
}

void func_8034B624(Camera* camera) {
    camera_802D3444(camera);
    camera_802D50D0(camera);
    uvChan_80204B34(camera->unk22C, &camera->unk108);
    uvChan_80204BD4(camera->unk22C, 1, camera->unk20);
    uvChan_80204BD4(camera->unk22C, 0, camera->unk20);
    uvChan_80204FC4(camera->unk22C);
}

void drawScreenBorder(void) {
    uvGfxBindTexture(GFX_STATE_TEXTURE_NONE);
    uvVtxRect(0, SUBSCREEN_Y0, SCREEN_WIDTH - 1, 0);
    uvVtxRect(0, SCREEN_HEIGHT - 1, SCREEN_WIDTH - 1, SUBSCREEN_Y1);
    uvVtxRect(0, SUBSCREEN_Y1, SUBSCREEN_X0, SUBSCREEN_Y0);
    uvVtxRect(SUBSCREEN_X1, SUBSCREEN_Y1, SCREEN_WIDTH - 1, SUBSCREEN_Y0);
}

void func_8034B6F8(void) {
    splashDraw();
    drawScreenBorder();
    if (D_80362690->debugFlag < 5) {
        hudMainRender();
    }

    switch (D_80362690->debugFlag) {
    case 1:
        uvDbg_8023345C(7, 1, 1);
        break;
    case 2:
        uvDbg_8023345C(7, 2, 2);
        uvDbgCnt(0x1F, 2);
        break;
    case 3:
        uvDbg_8023345C(7, 1, 1);
        uvDbg_8023345C(7, 2, 2);
        uvDbgCnt(0x1F, 2);
        break;
    case 4:
    case 5:
        uvDbg_8023345C(6, 3, 1);
        uvDbgCnt(3, 3);
        break;
    case 6:
        uvDbg_80233590();
        D_80362690->debugFlag -= 1;
        break;
    }
}
