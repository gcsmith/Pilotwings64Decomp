#include <uv_debug.h>
#include <uv_level.h>
#include <uv_graphics.h>
#include <uv_geometry.h>
#include "code_5A6A0.h"
#include "code_C8990.h"
#include "code_D2B10.h"
#include "hud.h"

// forward declarations
void func_8034B6F8(void);

void func_8034B5E0(u8 arg0, Unk802D3658_Arg0* arg1) {
    func_802D3170(arg0, arg1);
    func_80204AB0(arg1->unk22C, 1, func_8034B6F8);
}

void func_8034B624(Unk802D3658_Arg0* arg0) {
    func_802D3444(arg0);
    func_802D50D0(arg0);
    func_80204B34(arg0->unk22C, &arg0->unk108);
    func_80204BD4(arg0->unk22C, 1, arg0->unk20);
    func_80204BD4(arg0->unk22C, 0, arg0->unk20);
    func_80204FC4(arg0->unk22C);
}

void func_8034B688(void) {
    uvGfx_80223A28(0xFFF);
    uvVtxRect(0, 0x12, 0x13F, 0);
    uvVtxRect(0, 0xEF, 0x13F, 0xE8);
    uvVtxRect(0, 0xE8, 0xA, 0x12);
    uvVtxRect(0x136, 0xE8, 0x13F, 0x12);
}

void func_8034B6F8(void) {
    func_803415C8();
    func_8034B688();
    if (D_80362690->unk0[0].debugFlag < 5) {
        hudMainRender();
    }

    switch (D_80362690->unk0[0].debugFlag) {
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
        D_80362690->unk0[0].debugFlag -= 1;
        break;
    }
}

