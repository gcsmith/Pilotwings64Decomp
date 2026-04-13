#include <uv_debug.h>
#include <uv_graphics.h>
#include <uv_geometry.h>
#include "camera.h"
#include "code_D2B10.h"
#include "hud.h"
#include "splash.h"

void func_8034B5E0(u8 arg0, Camera* camera) {
    func_802D3170(arg0, camera);
    func_80204AB0(camera->unk22C, 1, func_8034B6F8);
}

void func_8034B624(Camera* camera) {
    func_802D3444(camera);
    func_802D50D0(camera);
    func_80204B34(camera->unk22C, &camera->unk108);
    func_80204BD4(camera->unk22C, 1, camera->unk20);
    func_80204BD4(camera->unk22C, 0, camera->unk20);
    func_80204FC4(camera->unk22C);
}

void func_8034B688(void) {
    uvGfxBindTexture(GFX_STATE_TEXTURE_NONE);
    uvVtxRect(0, 18, 319, 0);
    uvVtxRect(0, 239, 319, 232);
    uvVtxRect(0, 232, 10, 18);
    uvVtxRect(310, 232, 319, 18);
}

void func_8034B6F8(void) {
    splashDraw();
    func_8034B688();
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
