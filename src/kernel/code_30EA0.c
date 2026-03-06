#include "common.h"
#include <uv_graphics.h>
#include <uv_math.h>
#include "kernel/code_58E0.h"
#include "kernel/code_8170.h"

void func_802300D0(Unk80225FBC_0x28* arg0);

void func_8022FEF0(UnkStruct_80204D94* arg0, u16 arg1, uvUnkTileStruct* arg2, Unk80225FBC_0x28* arg3, u16 arg4, u8 arg5) {
    Unk80225FBC_0x28* var_s0;
    u32 i;
    f32 spAC;
    f32 spA8;
    f32 spA4;
    f32 spA0;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fs2;
    f32 temp_fs3;
    f32 temp_fv1;
    s16 var_s1;

    for (i = 0; i < arg4; i++) {
        var_s0 = &arg3[i];
        if (!(arg1 & var_s0->unk12)) {
            continue;
        }
        spA4 = arg0->unk1D0 - arg2->unk0.m[3][0];
        spA0 = arg0->unk1D4 - arg2->unk0.m[3][1];
        temp_fs3 = arg0->unk1D8 - arg2->unk0.m[3][2];
        func_80214840(arg5, &spA4, &spA0);
        var_s1 = arg5;
        temp_fs0 = var_s0->unk18 - spA4;
        temp_fs1 = var_s0->unk1C - spA0;
        temp_fs2 = var_s0->unk20 - temp_fs3;
        spAC = temp_fs0;
        spA8 = temp_fs1;
        func_80214840(-var_s1, &spAC, &spA8);
        if (func_80206F64(arg0->unk2E0, spAC, spA8, temp_fs2, var_s0->unk24) == 0) {
            continue;
        }
        if ((var_s0->unk24 / (uvSqrtF(SQ(temp_fs0) + SQ(temp_fs1) + SQ(temp_fs2)) + var_s0->unk24)) < 0.1f) {
            uvGfxSetUnkState0(1);
        } else {
            uvGfxSetUnkState0(0);
        }
        func_802300D0(var_s0);
    }
}

void func_802300D0(Unk80225FBC_0x28* arg0) {
    uvGfxStateDraw(&arg0->unk0);
}

u16 func_802300F0(s32 arg0) {
    ParsedUVTX* temp_v1;

    if (arg0 == 0xFFF) {
        return 0xFFF;
    }
    temp_v1 = gGfxUnkPtrs->textures[arg0];
    if (temp_v1 != NULL) {
        return temp_v1->unk20;
    }
    return 0xFFF;
}
