#include "common.h"
#include "code_51E30.h"
#include <uv_anim.h>

// .bss
f32 D_803571F0;
f32 D_803571F4;
f32 D_803571F8;
f32 D_803571FC;
f32 D_80357200;
f32 D_80357204;
f32 D_80357208;
f32 D_8035720C;

// .data
u32 D_8034E710[] = { 11, 18, 25, 33, 40, 47 };
u32 D_8034E728[] = { 12, 19, 26, 35, 42, 49 };
u32 D_8034E740[] = { 13, 20, 27, 36, 43, 50 };
u32 D_8034E758[] = { 15, 22, 29, 32, 39, 46 };
u32 D_8034E770[] = { 14, 21, 28, 34, 41, 48 };

Unk802CAC48 D_8034E788 = { 0, 11, &D_803571F0, NULL };
Unk802CAC48 D_8034E794 = { 0, 12, &D_803571F4, NULL };
Unk802CAC48 D_8034E7A0 = { 0, 13, &D_803571F4, NULL };
Unk802CAC48 D_8034E7AC = { 0, 15, &D_803571F8, &D_803571FC };
Unk802CAC48 D_8034E7B8 = { 0, 14, NULL, NULL };
Unk8034E788 D_8034E7C4 = { 1, 0, &D_80357200, &D_8034E794, &D_8034E7A0 };
Unk8034E788 D_8034E7D4 = { 1, 0, &D_80357204, &D_8034E7C4, &D_8034E7AC };
Unk8034E788 D_8034E7E4 = { 1, 0, &D_80357208, &D_8034E7D4, &D_8034E788 };
Unk8034E788 D_8034E7F4 = { 1, 0, &D_8035720C, &D_8034E7E4, &D_8034E7B8 };
Unk8034E788* D_8034E804 = &D_8034E7F4;

// forward declarations
STATIC_FUNC void func_802CAC48(Unk802CAC48*, Unk80371120*);

void app_firstfunc(s32 arg0) {
    D_8034E788.animationIndex = D_8034E710[arg0];
    D_8034E794.animationIndex = D_8034E728[arg0];
    D_8034E7A0.animationIndex = D_8034E740[arg0];
    D_8034E7AC.animationIndex = D_8034E758[arg0];
    D_8034E7B8.animationIndex = D_8034E770[arg0];
}

void func_802CAA00(u32 arg0, f32* arg1) {
    switch (arg0) {
    case 0:
        D_8034E7E4.unk4 = arg1;
        return;
    case 1:
        D_8034E7C4.unk4 = arg1;
        return;
    case 2:
        D_8034E7D4.unk4 = arg1;
        return;
    case 3:
        D_8034E7F4.unk4 = arg1;
        return;
    case 4:
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Waddress"
#endif
        // @fake
        if (&D_8034E794) { }
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif
        D_8034E794.unk4 = arg1;
        D_8034E7A0.unk4 = arg1;
        return;
    case 5:
        D_8034E788.unk4 = arg1;
        return;
    case 6:
        D_8034E7AC.unk4 = arg1;
        return;
    case 7:
        D_8034E7AC.unk8 = arg1;
        return;
    }
}

void func_802CAA90(s32 arg0) {
    Unk80371120 sp18;

    func_802CAAC8(D_8034E804, &sp18);
    uvJanim_80200638(arg0, &sp18);
}

void func_802CAAC8(Unk8034E788* arg0, Unk80371120* arg1) {
    Unk80371120 sp1E8;
    Unk80371120 sp38;
    Unk8034E788* var_s0;
    Unk8034E788* var_s1;

    var_s0 = NULL;
    var_s1 = NULL;
    if (*arg0->unk4 < 1.0f) {
        var_s0 = arg0->unk8;
        if (var_s0->unk0_0 == 0) {
            func_802CAC48((Unk802CAC48*)var_s0, &sp1E8);
        } else {
            func_802CAAC8(var_s0, &sp1E8);
        }
    }
    if (*arg0->unk4 > 0.0f) {
        var_s1 = arg0->unkC;
        if (var_s1->unk0_0 == 0) {
            func_802CAC48((Unk802CAC48*)var_s1, &sp38);
        } else {
            func_802CAAC8(var_s1, &sp38);
        }
    }
    if (var_s0 != NULL && var_s1 != NULL) {
        uvJanim_802006FC(arg1, &sp1E8, &sp38, *arg0->unk4);
        return;
    }
    if (var_s0 != NULL) {
        *arg1 = sp1E8;
    } else if (var_s1 != NULL) {
        *arg1 = sp38;
    }
}

STATIC_FUNC void func_802CAC48(Unk802CAC48* arg0, Unk80371120* arg1) {
    f32 var_fv0;

    if (arg0->unk8 != NULL) {
        if (arg0->unk4 != NULL) {
            var_fv0 = *arg0->unk4;
        } else {
            var_fv0 = 0.0f;
        }
        uvJanimPoseGrid(arg1, arg0->animationIndex, var_fv0, *arg0->unk8);
    } else {
        if (arg0->unk4 != NULL) {
            var_fv0 = *arg0->unk4;
        } else {
            var_fv0 = 0.0f;
        }
        uvJanimPoseLine(arg1, arg0->animationIndex, var_fv0);
    }
}
