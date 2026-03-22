#include "common.h"
#include "code_72B70.h"
#include "shadow.h"
#include <uv_dobj.h>
#include <uv_model.h>

// .data
extern s32 D_80350460;
extern s32 D_80350464;
extern u16 D_80350466;
extern s32 D_80350468;
extern u16 D_8035046A;
extern s32 D_8035046C;
extern s32 D_80350470;
extern f32 D_80350474;
extern f32 D_80350478;

// forward declarations
void func_803347D0(Mtx4F*);
f32 func_80334A38(Vec3F*);

void func_803342F0(f32 arg0) {
    D_80350474 = arg0;
}

void func_803342FC(f32 arg0) {
    D_80350478 = arg0;
}

void func_80334308(u16 modelId) {
    if (D_8035046C == modelId) {
        return;
    }
    D_8035046C = modelId;
    if (modelId == 0xFFFF) {
        if (D_80350470 != 0xFFFF) {
            uvDobjModel(D_80350470, 0xFFFF);
            D_80350470 = 0xFFFF;
        }
    } else {
        if (D_80350470 == 0xFFFF) {
            D_80350470 = uvDobjAllocIdx();
        }
        if (D_80350470 == 0xFFFF) {
            _uvDebugPrintf("shad_models: shadow couldn't allocate dobj id\n");
            return;
        }
        uvDobjModel(D_80350470, modelId);
        uvDobjState(D_80350470, D_80350460);
    }
}

void func_803343D8(s32 arg0) {
    if (D_80350470 != 0xFFFF) {
        if (arg0 != 0) {
            if (D_80350460 == 0) {
                uvDobjState(D_80350470, 2);
            }
            D_80350460 = 2;
        } else {
            if (D_80350460 != 0) {
                uvDobjState(D_80350470, 0);
            }
            D_80350460 = 0;
        }
    }
}

void func_80334454(u16 arg0, u16 arg1) {
    D_80350468 = arg0;
    D_80350464 = arg1;
    if (arg0 != 0xFFFF) {
        func_80334308(arg0);
    } else if (arg1 != 0xFFFF) {
        func_80334308(arg1);
    }
}

void func_803344BC(Mtx4F* arg0, f32 arg1) {
    u16 var_v0;
    u8 sp1D;

    if (D_80350470 == 0xFFFF || D_80350460 == 0) {
        return;
    }

    if (D_80362690->unk0 == 6) {
        var_v0 = D_80350466;
    } else {
        var_v0 = D_8035046A;
    }

    if (var_v0 == 0xFFFF) {
        return;
    }

    sp1D = 0;
    if (D_80350468 == var_v0) {
        uvModelGetProps(var_v0, 5, &sp1D, 0);
    }

    if (sp1D != 0) {
        func_803347D0(arg0);
    } else {
        func_80334578(arg0, arg1);
    }
}

void func_80334578(Mtx4F* arg0, f32 arg1) {
    Vec3F sp9C;
    Vec3F sp90;
    Vec3F sp84;
    Vec3F sp78;
    f32 temp_fa0;
    f32 var_fv0;
    f32 var_fv1;
    Mtx4F sp2C;
    s32 pad;

    if (D_80350470 == 0xFFFF) {
        return;
    }

    if (arg1 < 5.0f) {
        var_fv0 = 0.0f;
    } else {
        var_fv0 = (arg1 - 5.0f) / 5.0f;
        if (var_fv0 < 1.0f) {
            var_fv1 = var_fv0;
        } else {
            var_fv1 = 1.0f;
        }
        var_fv0 = var_fv1 * D_80350474 * arg1;
    }

    sp9C.f[0] = arg0->m[3][0] + (arg0->m[1][0] * var_fv0);
    sp9C.f[1] = arg0->m[3][1] + (arg0->m[1][1] * var_fv0);
    sp9C.f[2] = arg0->m[3][2];
    uvVec3Copy(&sp78, &sp9C);
    sp9C.f[2] = func_80334A38(&sp78);
    sp90.f[0] = arg0->m[0][0];
    sp90.f[1] = arg0->m[0][1];
    sp90.f[2] = arg0->m[0][2];
    uvVec3Cross(&sp84, &sp78, &sp90);
    uvVec3Normal(&sp84, &sp84);
    uvVec3Cross(&sp90, &sp84, &sp78);
    uvVec3Normal(&sp90, &sp90);
    sp2C.m[0][0] = sp90.f[0];
    sp2C.m[0][1] = sp90.f[1];
    sp2C.m[0][2] = sp90.f[2];
    sp2C.m[0][3] = 0 /*.0f*/;
    sp2C.m[1][0] = sp84.f[0];
    sp2C.m[1][1] = sp84.f[1];
    sp2C.m[1][2] = sp84.f[2];
    sp2C.m[1][3] = 0 /*.0f*/;
    sp2C.m[2][0] = sp78.f[0];
    sp2C.m[2][1] = sp78.f[1];
    sp2C.m[2][2] = sp78.f[2];
    sp2C.m[2][3] = 0 /*.0f*/;
    sp2C.m[3][0] = sp9C.f[0];
    sp2C.m[3][1] = sp9C.f[1];
    sp2C.m[3][2] = sp9C.f[2] + 0.1;
    sp2C.m[3][3] = 1.0f;
    if (arg0->m[3][2] < 2.0f) {
        temp_fa0 = arg0->m[3][2] * 0.5f;
        if (temp_fa0 > 0.01f) {
            var_fv0 = temp_fa0;
        } else {
            var_fv0 = 0.01f;
        }
        uvMat4Scale(&sp2C, var_fv0, var_fv0, var_fv0);
    }
    func_80334308(D_80350466);
    uvDobjPosm(D_80350470, 0, &sp2C);
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/shadow/func_803347D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/shadow/func_80334A38.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/shadow/func_80334C70.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/shadow/func_80334CC0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/shadow/func_80334CCC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/shadow/func_80335130.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/shadow/func_80335700.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/shadow/func_803358D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/shadow/func_80335AE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/shadow/func_80335AF4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/shadow/shadowInit.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/shadow/func_80335BE4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/shadow/func_80335E44.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/shadow/func_80335EE4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/shadow/func_80335F24.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/shadow/func_80335F84.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/shadow/func_80335FD8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/shadow/func_80336064.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/shadow/func_80336094.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/shadow/func_803360E8.s")
