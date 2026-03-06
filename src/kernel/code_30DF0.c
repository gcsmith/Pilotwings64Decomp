#include "common.h"
#include <uv_graphics.h>
#include <uv_sobj.h>
#include "kernel/code_30DF0.h"

void func_8022FE40(UnkStruct_80204D94* arg0, uvUnkTileStruct* arg1, u16 arg2, u16 arg3, s32 arg4) {
    ParsedUVCT* temp_v0;

    if (arg1->unk40 != NULL) {
        uvGfx_802236CC(&arg1->unk0);
        func_8022FEF0(arg0, arg2, arg1, arg1->unk40->unk8, arg1->unk40->unkC, arg1->unk44);
        uvSobjsDraw(arg0, &arg1->unk0, arg2, arg3, arg1->unk40->unk10, arg1->unk40->unk14, arg1->unk44, arg4);
        uvGfxMtxViewPop();
    }
}
