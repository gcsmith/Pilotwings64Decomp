#include "common.h"
#include "snap.h"
#include <uv_clocks.h>
#include <uv_dobj.h>
#include <uv_event.h>
#include <uv_font.h>
#include <uv_geometry.h>
#include <uv_graphics.h>
#include <uv_level.h>
#include <uv_vector.h>
#include "app/demo.h"
#include "app/file_menu.h"
#include "app/hud.h"
#include "app/snd.h"
#include "app/text_data.h"
#include "app/code_D1ED0.h"

typedef struct Unk8033F050 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u8 unk6;
    u8 unk7;
    u8 unk8;
    u32 unk9_0 : 2;
    u32 unk9_2 : 2;
    u32 unk9_4 : 4;
    u32 unk9_8 : 4;
    u32 unk9_12 : 4;
    u32 unk9_16 : 4;
    u32 unk9_20 : 4;
    u8 unkC;
    u8 unkD;
    u8 unkE;
    u8 unkF;
    u8 unk10;
    u8 unk11;
    u32 unk12_0 : 4;
    u32 unk12_4 : 3;
    u32 unk12_7 : 3;
    u32 unk12_10 : 3;
    u32 unk12_13 : 3;
    u32 unk12_16 : 3;
    u32 unk12_19 : 3;
    u32 unk12_22 : 3;
    u32 unk12_25 : 3;
} Unk8033F050;

typedef struct Unk80373060 {
    Vec3F unk0;
    Vec3F unkC;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    u16 unk30;
    u16 unk32;
    u16 unk34;
    u8 unk36;
    u8 pad37[0x1];
    f32 unk38;
    f32 unk3C;
    s16 unk40;
    u8 unk42;
    u8 unk43[6];
    f32 unk4C[6];
    u8 unk64[6];
    s32 unk6C;
} Unk80373060; // size 0x70

extern Unk80373060 D_80373060[];
extern Unk8033F050 D_80373300[];
extern Unk80373060 D_80373390[];
extern Unk80373060 D_80373630[];
extern Unk80373060 D_803738D0[];
extern Unk80373060 D_80373B70[];
extern f32 D_80373E10;
extern f32 D_80373E14;
extern s32 D_80373E18;
extern s32 D_80373E1C;

void func_8033A6B8(void);

void func_802EB368(void);
void func_8034C25C(void);
void func_803154C0(void);
void func_80336094(void);
void func_802E7D58(void);
void func_802EB328(f32);
void func_8034C1CC(f32);
void func_80315418(f32);
void func_80335FD8(f32);
void func_802E7D18(f32);
void func_8034CCC4(s32, f32);
void func_802D21D8(s32, f32);
void func_802F2110(s32, f32);
void func_80320900(s32, f32);
void func_8032150C(void);
void func_802EB38C(void);
void func_8034C298(void);
void func_80315508(void);
void func_803360E8(void);
void func_80336064(void);
void func_802E7D6C(void);

s32 D_80350510[] = { 0x4, 0x3, 0x1, 0x2, 0x6, 0x5 };
s32 D_80350528 = 0;
s32 D_8035052C = 0;
UNUSED s32 D_80350530 = 0xFFFF;
s32 D_80350534 = 0;
s32 D_80350538 = 2;
s32 D_8035053C = 3;
s32 D_80350540 = 1;
u8 D_80350544 = 0;
u8 D_80350548 = 0;
u8 D_8035054C = 0; // might be array of up to 4 elements
s32 D_80350550 = 0;
Vec3F D_80350554 = { 0.0f, 1.0f, 0.0f };
s32 D_80350560[][2] = {
    {  28, 125 },
    { 116, 125 },
    { 204, 125 },
    {  28,  51 },
    { 116,  51 },
    { 204,  51 }
};
s32 D_80350590 = 0;
s32 D_80350594 = 0;
s32 D_80350598 = 0xFFFFFFFF;
s32 D_8035059C = 0xFFFFFFFF;
s32 D_803505A0 = 0xFFFFFFFF;

void func_80337D50(void) {
    s32 i;
    s32 j;

    for (i = 0; i < 6; i++) {
        D_80373060[i].unk40 = -1;
        D_80373060[i].unk42 = 0;
        D_80373060[i].unk36 = 0;
        for (j = 0; j < 6; j++) {
            D_80373390[i].unk43[j] = 0;
        }
    }

    D_80350528 = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/snap/func_80337DB8.s")

void func_803383FC(void) {
}

void func_80338404(void) {
    s32 i;
    s32 j;

    for (i = D_80350528 - 1; i >= 0; i--) {
        if (D_80373060[i].unk43[0] == 0) {
            if (i < 5) {
                for (j = i; j < 5; j++) {
                    D_80373060[j] = D_80373060[j + 1];
                }
            }
            D_80350528--;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/snap/func_80338614.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/snap/func_8033869C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/snap/func_803386A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/snap/func_80338964.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/snap/func_80338A14.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/snap/func_80339C8C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/snap/func_80339E1C.s")

s32 func_80339F9C(void) {
    Unk80362690_Unk0_UnkC* temp_v1;
    u16 var_a0;

    temp_v1 = &D_80362690->unk0[D_80362690->unk9C].unkC;

    switch (temp_v1->veh) {
    case 6:
        var_a0 = *temp_v1->unk6C;
        break;
    case 0:
        var_a0 = *temp_v1->unk6C;
        break;
    default:
        _uvDebugPrintf("photos_getmodel: non photogenic vehicle\n");
        var_a0 = 0xFFFF;
        break;
    }

    return var_a0;
}

void func_8033A020(s32 arg0) {
    if (D_80350590 == 0) {
        return;
    }

    D_80350590 = 0;

    if ((arg0 == 0) || (D_80350594 != 0)) {
        func_802ECE94(D_80362690);
        D_80362690->unkA2 = 0;
    }
}

void func_8033A078(s32 arg0) {
    u8* ptr;

    ptr = levelGet_80345CB0();
    if ((D_80362690->unk0[0].unk0 != 7) && (ptr[1] == 1)) {
        func_803405C0();
    }
    if (D_80350590 != 0) {
        D_80350590 = 0;
        if ((arg0 == 0) || (D_80350594 != 0)) {
            func_802ECE94(D_80362690);
            D_80362690->unkA2 = 0;
        }
    }
    D_8035059C = -1;
    D_80350598 = -1;
    D_803505A0 = -1;
}

void func_8033A128(s32 arg0, Unk80373060* arg1) {
    Unk80362690_Unk0_UnkC* temp_v1;

    if ((arg0 != 0) && (D_80350594 == 0)) {
        return;
    }

    if (arg1 == NULL) {
        return;
    }

    if (arg1->unk43[0] == 0) {
        return;
    }

    temp_v1 = &D_80362690->unk0[D_80362690->unk9C].unkC;

    if ((D_80350598 != arg1->unk34) || (D_8035059C != arg1->unk30) || (D_803505A0 != arg1->unk32)) {
        func_8033A020(arg0);
        D_80350590 = 1;
        temp_v1->veh = arg1->unk34;
        temp_v1->cls = arg1->unk30;
        temp_v1->test = arg1->unk32;
        D_80350598 = temp_v1->veh;
        D_8035059C = temp_v1->cls;
        D_803505A0 = temp_v1->test;
        D_80362690->unkA2 = 1;
        func_802EC50C(D_80362690);
    }
}

void func_8033A244(s32 arg0, Unk80373060* arg1) {
    Mtx4F sp90;
    s32 i;
    Unk80362690_Unk0* var_v1;
    Mtx4F* sp40;
    Mtx4F sp44;

    if (arg1 != NULL) {
        var_v1 = &D_80362690->unk0[D_80362690->unk9C];
        sp40 = &var_v1->unkC.unk2C;
        uvMat4Copy(&sp44, sp40);
        func_8034B210(arg1->unk0, arg1->unkC, &sp90);
        uvMat4Copy(sp40, &sp90);
        uvEventPost(0x12, 0);

        for (i = 0; i < arg1->unk42; i++) {
            switch (arg1->unk43[i]) {
            case 5:
                func_802EB368();
                break;
            case 4:
                func_8034C25C();
                break;
            case 3:
                func_803154C0();
                break;
            case 1:
                func_80336094();
                break;
            case 2:
                func_802E7D58();
                break;
            }
        }
        func_8032150C();
        for (i = 0; i < arg1->unk42; i++) {
            switch (arg1->unk43[i]) {
            case 5:
                func_802EB328(arg1->unk4C[i]);
                break;
            case 4:
                func_8034C1CC(arg1->unk4C[i]);
                break;
            case 3:
                func_80315418(arg1->unk4C[i]);
                break;
            case 1:
                func_80335FD8(arg1->unk4C[i]);
                break;
            case 2:
                func_802E7D18(arg1->unk4C[i]);
                break;
            case 7:
                func_8034CCC4(arg1->unk64[i], arg1->unk4C[i]);
                break;
            case 10:
                func_802D21D8(arg1->unk64[i], arg1->unk4C[i]);
                break;
            case 9:
                func_802F2110(arg1->unk64[i], arg1->unk4C[i]);
                break;
            case 8:
                func_80320900(arg1->unk64[i], arg1->unk4C[i]);
                break;
            }
        }
        uvGfxBegin();
        func_80204C94(0, arg1->unk18, arg1->unk1C, arg1->unk24, arg1->unk20, arg1->unk28, arg1->unk2C);
        func_80204B34(0, &sp90);
        uvChanTerra(0, D_80362690->unk0[0].unk6);
        func_80204A8C(0, 11);
        func_80204FC4(0);
        uvGfxEnd();
        if (arg1->unk43[0] != 11 && arg1->unk43[0] != 0) {
            switch (arg1->unk43[0]) {
            case 5:
                func_802EB38C();
                break;
            case 4:
                func_8034C298();
                break;
            case 3:
                func_80315508();
                break;
            case 1:
                func_803360E8();
                func_80336064();
                break;
            case 2:
                func_802E7D6C();
                break;
            }
        }
        uvMat4Copy(sp40, &sp44);
    } else {
        uvGfxBegin();
        uvGfxClearScreen(80, 80, 80, 255);
        uvGfxEnd();
    }
}

void func_8033A610(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    arg0 += 5;
    arg1 -= 5;
    arg2 += 5;
    arg3 -= 5;
    func_80204D94(0, arg0, arg1, arg2, arg3);
}

void func_8033A664(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    arg0 += 5;
    arg1 -= 5;
    arg2 += 5;
    arg3 -= 5;
    uvGfxSetViewport(0, arg0, arg1, arg2, arg3);
}

void func_8033A6B8(void) {
    func_8033A664(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);
    uvGfxBegin();
    uvGfxClearScreen(0, 0, 0, 255);
    uvGfxEnd();
    uvGfxBegin();
    uvGfxClearScreen(0, 0, 0, 255);
    uvGfxEnd();
}

void func_8033A72C(void) {
    Mtx4F sp98;
    Mtx4F sp58;
    f32 var_fs0;
    s32 i;

    func_8033A664(0, SCREEN_WIDTH - 1, 0, SCREEN_HEIGHT - 1);
    uvGfxBegin();
    uvMat4SetOrtho(&sp98, 0.0f, SCREEN_WIDTH - 1, 0.0f, SCREEN_HEIGHT - 1);
    uvGfxMtxProjPushF(&sp98);
    uvMat4SetIdentity(&sp58);
    uvGfxMtxViewLoad(&sp58, 1);
    uvVtxBeginPoly();
    uvVtx(28, 44, 0, 0, 0, 0, 0, 100, 255);
    uvVtx(284, 44, 0, 0, 0, 0, 0, 100, 255);
    uvVtx(285, 45, 0, 0, 0, 0, 0, 100, 255);
    uvVtx(28, 45, 0, 0, 0, 0, 0, 100, 255);
    uvVtxEndPoly();
    uvVtxBeginPoly();
    uvVtx(28, 117, 0, 0, 0, 0, 0, 100, 255);
    uvVtx(284, 117, 0, 0, 0, 0, 0, 100, 255);
    uvVtx(284, 119, 0, 0, 0, 0, 0, 100, 255);
    uvVtx(28, 119, 0, 0, 0, 0, 0, 100, 255);
    uvVtxEndPoly();
    uvVtxBeginPoly();
    uvVtx(28, 191, 0, 0, 0, 0, 0, 100, 255);
    uvVtx(284, 191, 0, 0, 0, 0, 0, 100, 255);
    uvVtx(284, 213, 0, 0, 0, 0, 0, 100, 255);
    uvVtx(28, 213, 0, 0, 0, 0, 0, 100, 255);
    uvVtxEndPoly();
    var_fs0 = 1.0f;
    for (i = 0; i < 43; i++) {
        uvVtxBeginPoly();
        uvVtx(28.0f + var_fs0, 47, 0, 0, 0, 0, 0, 100, 255);
        uvVtx(30.0f + var_fs0, 47, 0, 0, 0, 0, 0, 100, 255);
        uvVtx(30.0f + var_fs0, 49, 0, 0, 0, 0, 0, 100, 255);
        uvVtx(28.0f + var_fs0, 49, 0, 0, 0, 0, 0, 100, 255);
        uvVtxEndPoly();
        uvVtxBeginPoly();
        uvVtx(28.0f + var_fs0, 113, 0, 0, 0, 0, 0, 100, 255);
        uvVtx(30.0f + var_fs0, 113, 0, 0, 0, 0, 0, 100, 255);
        uvVtx(30.0f + var_fs0, 115, 0, 0, 0, 0, 0, 100, 255);
        uvVtx(28.0f + var_fs0, 115, 0, 0, 0, 0, 0, 100, 255);
        uvVtxEndPoly();
        uvVtxBeginPoly();
        uvVtx(28.0f + var_fs0, 121, 0, 0, 0, 0, 0, 100, 255);
        uvVtx(30.0f + var_fs0, 121, 0, 0, 0, 0, 0, 100, 255);
        uvVtx(30.0f + var_fs0, 123, 0, 0, 0, 0, 0, 100, 255);
        uvVtx(28.0f + var_fs0, 123, 0, 0, 0, 0, 0, 100, 255);
        uvVtxEndPoly();
        uvVtxBeginPoly();
        uvVtx(28.0f + var_fs0, 187, 0, 0, 0, 0, 0, 100, 255);
        uvVtx(30.0f + var_fs0, 187, 0, 0, 0, 0, 0, 100, 255);
        uvVtx(30.0f + var_fs0, 189, 0, 0, 0, 0, 0, 100, 255);
        uvVtx(28.0f + var_fs0, 189, 0, 0, 0, 0, 0, 100, 255);
        uvVtxEndPoly();
        var_fs0 += 6.0f;
    }
    uvGfxMtxViewPop();
    uvGfxEnd();
}

void func_8033ADD4(s32 arg0, Unk80373060* arg1, s32 arg2, s32 arg3) {
    Mtx4F spA0;
    Mtx4F sp60;
    s32 sp5C;
    u8 pad4C[0x10];
    s32 sp34;
    s16 pad46;
    s16 sp44;
    s32 var_v1;
    s32 sp3C;

    uvLevelAppend(0x1B);
    func_8033A664(0, SCREEN_WIDTH - 1, 0, SCREEN_HEIGHT - 1);
    uvGfxBegin();
    uvMat4SetOrtho(&spA0, 0.0f, SCREEN_WIDTH - 1, 0.0f, SCREEN_HEIGHT - 1);
    uvGfxMtxProjPushF(&spA0);
    uvMat4SetIdentity(&sp60);
    uvGfxMtxViewLoad(&sp60, 1);
    uvVtxBeginPoly();
    uvVtx(32, 25, 0, 0, 0, 255, 255, 255, 255);
    uvVtx(283, 25, 0, 0, 0, 255, 255, 255, 255);
    uvVtx(283, 224, 0, 0, 0, 255, 255, 255, 255);
    uvVtx(32, 224, 0, 0, 0, 255, 255, 255, 255);
    uvVtxEndPoly();
    uvVtxBeginPoly();
    uvVtx(31, 24, 0, 0, 0, 0, 0, 100, 255);
    uvVtx(284, 24, 0, 0, 0, 0, 0, 100, 255);
    uvVtx(284, 47, 0, 0, 0, 0, 0, 100, 255);
    uvVtx(31, 47, 0, 0, 0, 0, 0, 100, 255);
    uvVtxEndPoly();
    uvVtxBeginPoly();
    uvVtx(31, 201, 0, 0, 0, 0, 0, 100, 255);
    uvVtx(284, 201, 0, 0, 0, 0, 0, 100, 255);
    uvVtx(284, 225, 0, 0, 0, 0, 0, 100, 255);
    uvVtx(31, 225, 0, 0, 0, 0, 0, 100, 255);
    uvVtxEndPoly();
    uvVtxBeginPoly();
    uvVtx(31, 47, 0, 0, 0, 0, 0, 100, 255);
    uvVtx(55, 47, 0, 0, 0, 0, 0, 100, 255);
    uvVtx(55, 201, 0, 0, 0, 0, 0, 100, 255);
    uvVtx(31, 201, 0, 0, 0, 0, 0, 100, 255);
    uvVtxEndPoly();
    uvVtxBeginPoly();
    uvVtx(259, 47, 0, 0, 0, 0, 0, 100, 255);
    uvVtx(284, 47, 0, 0, 0, 0, 0, 100, 255);
    uvVtx(284, 201, 0, 0, 0, 0, 0, 100, 255);
    uvVtx(259, 201, 0, 0, 0, 0, 0, 100, 255);
    uvVtxEndPoly();
    if (arg0 == 0) {
        if (D_80350528) {
            uvGfxStatePush();
            uvGfxSetFlags(GFX_STATE_800000);
            uvGfxClearFlags(GFX_STATE_400000 | GFX_STATE_200000);
            uvGfx_80223A28(0x13E);
            sp5C = 108;
            D_80373E1C = sp5C;
            sp5C += 12;
            D_80373E10 = sp5C;
            uvVtxBeginPoly();
            uvVtx(120, 30, 0, 0, 0, 255, 255, 255, 255);
            uvVtx(150, 30, 0, 0x3C0, 0, 255, 255, 255, 255);
            uvVtx(150, 44, 0, 0x3C0, 0x1C0, 255, 255, 255, 255);
            uvVtx(120, 44, 0, 0, 0x1C0, 255, 255, 255, 255);
            uvVtxEndPoly();
            uvGfx_80223A28(0x13F);
            sp5C += 31;
            D_80373E18 = sp5C + 3;
            sp5C += 14;
            D_80373E14 = sp5C;
            uvVtxBeginPoly();
            uvVtx(sp5C, 30, 0, 0, 0, 255, 255, 255, 255);
            sp34 = sp5C + 77;
            uvVtx(sp34, 30, 0, 0x9A0, 0, 255, 255, 255, 255);
            uvVtx(sp34, 44, 0, 0x9A0, 0x1C0, 255, 255, 255, 255);
            uvVtx(sp5C, 44, 0, 0, 0x1C0, 255, 255, 255, 255);
            uvVtxEndPoly();
            uvGfxStatePop();
        }
    } else if (arg0 == 2) {
        if (6 - D_80350528) {
            uvGfxStatePush();
            uvGfxSetFlags(GFX_STATE_800000);
            uvGfxClearFlags(GFX_STATE_400000 | GFX_STATE_200000);
            uvGfx_80223A28(0x140);
            sp5C = 111;
            uvVtxBeginPoly();
            uvVtx(36, 30, 0, 0, 0, 255, 255, 255, 255);
            uvVtx(111, 30, 0, 0x960, 0, 255, 255, 255, 255);
            uvVtx(111, 41, 0, 0x960, 0x160, 255, 255, 255, 255);
            uvVtx(36, 41, 0, 0, 0x160, 255, 255, 255, 255);
            uvVtxEndPoly();
            uvGfx_80223A28(0x142);
            sp5C += 10;
            D_80373E18 = sp5C + 5;
            sp5C += 15;
            D_80373E10 = sp5C;
            uvVtxBeginPoly();
            uvVtx(sp5C, 28, 0, 0, 0, 255, 255, 255, 255);
            sp34 = sp5C + 17;
            uvVtx(sp34, 28, 0, 0x220, 0, 255, 255, 255, 255);
            uvVtx(sp34, 42, 0, 0x220, 0x1C0, 255, 255, 255, 255);
            uvVtx(sp5C, 42, 0, 0, 0x1C0, 255, 255, 255, 255);
            uvVtxEndPoly();
            uvGfx_80223A28(0x143);
            sp5C += 17;
            D_80373E1C = sp5C + 5;
            sp5C += 15;
            D_80373E14 = sp5C;
            uvVtxBeginPoly();
            uvVtx(sp5C, 28, 0, 0, 0, 255, 255, 255, 255);
            sp34 = sp5C + 13;
            uvVtx(sp34, 28, 0, 0x1A0, 0, 255, 255, 255, 255);
            uvVtx(sp34, 42, 0, 0x1A0, 0x1C0, 255, 255, 255, 255);
            uvVtx(sp5C, 42, 0, 0, 0x1C0, 255, 255, 255, 255);
            uvVtxEndPoly();
            uvGfxStatePop();
        }
        uvGfxStatePush();
        uvGfxSetFlags(GFX_STATE_800000);
        uvGfxClearFlags(GFX_STATE_400000 | GFX_STATE_200000);
        uvGfx_80223A28(0x145);
        uvVtxBeginPoly();
        uvVtx(200, 30, 0, 0, 0, 255, 255, 255, 255);
        uvVtx(259, 30, 0, 0x760, 0, 255, 255, 255, 255);
        uvVtx(259, 41, 0, 0x760, 0x160, 255, 255, 255, 255);
        uvVtx(200, 41, 0, 0, 0x160, 255, 255, 255, 255);
        uvVtxEndPoly();
        uvGfxStatePop();
        uvFontSet(6);
        uvFontColor(255, 255, 255, 255);
        uvFontScale(1.0, 1.0);
        textFmtInt(&sp44, 6 - D_80350528, 3);
        func_80219874(0xF5, 0x19, &sp44, 3, 0xFFE);

        var_v1 = (((arg1->unk32 == 0) && (arg1->unk30 == 1)) || ((arg1->unk32 == 1) && (arg1->unk30 == 2)) || ((arg1->unk32 == 2) && (arg1->unk30 == 3))) &&
                 (arg1->unk34 != 6);

        if (var_v1 != 0) {
            if ((arg1->unk3C * arg1->unk38) > 0.0f) {
                uvFontSet(6);
                uvFontScale(1.0, 1.0);
                uvFontColor(255, 255, 255, 255);
                textFmtInt(&sp44, func_8034AD14(arg1->unk3C * arg1->unk38), 3);
                func_80219874(194, 200, &sp44, 3, 0xFFE);
                func_80219874(230, 200, textGetDataByIdx(0xF5), 100, 0xFFE);
                if (arg1->unk6C != 0) {
                    uvFontColor(255, 240, 0, 255);
                    func_80219874(54, 200, textGetDataByIdx(0xD), 100, 0xFFE);
                } else {
                    func_80219874(54, 200, textGetDataByIdx(0xA4), 100, 0xFFE);
                }
            } else {
                uvFontSet(6);
                uvFontColor(255, 0, 0, 255);
                uvFontScale(1.0, 1.0);
                func_80219874(54, 200, textGetDataByIdx(0x136), 100, 0xFFE);
            }
        }
    } else if (arg0 == 1) {
        uvFontSet(6);
        uvFontScale(1.0, 1.0);
        uvFontColor(255, 255, 255, 255);
        sp3C = func_802196B0(textGetDataByIdx(arg1->unk40));
        func_80219874(160 - (sp3C / 2), 200, textGetDataByIdx(arg1->unk40), 0x16, 0xFFE);
        uvGfxStatePush();
        uvGfxSetFlags(GFX_STATE_800000);
        uvGfxClearFlags(GFX_STATE_400000 | GFX_STATE_200000);
        uvGfx_80223A28(0x11B);
        if (arg2 > 0) {
            uvVtxBeginPoly();
            uvVtx(0x28, 206, 0, 0, 0, 255, 240, 0, 255);
            uvVtx(0x37, 206, 0, 0x1E0, 0, 255, 240, 0, 255);
            uvVtx(0x37, 221, 0, 0x1E0, 0x1E0, 255, 240, 0, 255);
            uvVtx(0x28, 221, 0, 0, 0x1E0, 255, 240, 0, 255);
            uvVtxEndPoly();
        }
        if (arg2 < (arg3 - 1)) {
            uvVtxBeginPoly();
            uvVtx(257, 206, 0, 0x1E0, 0, 255, 240, 0, 255);
            uvVtx(272, 206, 0, 0, 0, 255, 240, 0, 255);
            uvVtx(272, 221, 0, 0, 0x1E0, 255, 240, 0, 255);
            uvVtx(257, 221, 0, 0x1E0, 0x1E0, 255, 240, 0, 255);
            uvVtxEndPoly();
        }
        uvGfxStatePop();
    }
    uvFontGenDlist();
    uvGfxMtxViewPop();
    uvGfxEnd();
}

void func_8033BF00(s32 arg0, s32 arg1, s32 arg2) {
    Mtx4F sp88;
    Mtx4F sp48;
    s32 sp44;
    s32 sp40;
    f32 sp3C;

    uvLevelAppend(0x1B);
    func_8033A664(0, SCREEN_WIDTH - 1, 0, SCREEN_HEIGHT - 1);
    uvGfxBegin();
    uvMat4SetOrtho(&sp88, 0.0f, SCREEN_WIDTH - 1, 0.0f, SCREEN_HEIGHT - 1);
    uvGfxMtxProjPushF(&sp88);
    uvMat4SetIdentity(&sp48);
    uvGfxMtxViewLoad(&sp48, 1);
    if (arg2 != 0) {
        uvGfxStatePush();
        uvGfxSetFlags(GFX_STATE_800000);
        uvGfxClearFlags(GFX_STATE_400000 | GFX_STATE_200000);
        if (arg1 != 0) {
            sp44 = D_80373E18;
            sp40 = D_80373E18 + 9;
        } else {
            sp44 = D_80373E1C;
            sp40 = D_80373E1C + 9;
        }
        uvVtxBeginPoly();
        uvVtx(sp44, 31, 0, 0, 0, 0, 0, 100, 255);
        uvVtx(sp40, 31, 0, 0, 0, 0, 0, 100, 255);
        uvVtx(sp40, 44, 0, 0, 0, 0, 0, 100, 255);
        uvVtx(sp44, 44, 0, 0, 0, 0, 0, 100, 255);
        uvVtxEndPoly();
        if (arg0 == 2) {
            if (arg1 != 0) {
                sp3C = D_80373E10;
                uvGfx_80223A28(0x142);
                uvVtxBeginPoly();
                uvVtx(sp3C, 28, 0, 0, 0, 255, 255, 255, 255);
                uvVtx(sp3C + 17.0f, 28, 0, 0x220, 0, 255, 255, 255, 255);
                uvVtx(sp3C + 17.0f, 42, 0, 0x220, 0x1C0, 255, 255, 255, 255);
                uvVtx(sp3C, 42, 0, 0, 0x1C0, 255, 255, 255, 255);
                uvVtxEndPoly();
            } else {
                sp3C = D_80373E14;
                uvGfx_80223A28(0x143);
                uvVtxBeginPoly();
                uvVtx(sp3C, 28, 0, 0, 0, 255, 255, 255, 255);
                uvVtx(sp3C + 13.0f, 28, 0, 0x1A0, 0, 255, 255, 255, 255);
                uvVtx(sp3C + 13.0f, 42, 0, 0x1A0, 0x1C0, 255, 255, 255, 255);
                uvVtx(sp3C, 42, 0, 0, 0x1C0, 255, 255, 255, 255);
                uvVtxEndPoly();
            }
        } else if (arg1 != 0) {
            sp3C = D_80373E10;
            uvGfx_80223A28(0x13E);
            uvVtxBeginPoly();
            uvVtx(sp3C, 30, 0, 0, 0, 0, 255, 255, 255);
            uvVtx(sp3C + 30.0f, 30, 0, 0x3C0, 0, 0, 255, 255, 255);
            uvVtx(sp3C + 30.0f, 44, 0, 0x3C0, 0x1C0, 0, 255, 255, 255);
            uvVtx(sp3C, 44, 0, 0, 0x1C0, 0, 255, 255, 255);
            uvVtxEndPoly();
        } else {
            sp3C = D_80373E14;
            uvGfx_80223A28(0x13F);
            uvVtxBeginPoly();
            uvVtx(sp3C, 30, 0, 0, 0, 0, 255, 255, 255);
            uvVtx(sp3C + 77.0f, 30, 0, 0x9A0, 0, 0, 255, 255, 255);
            uvVtx(sp3C + 77.0f, 44, 0, 0x9A0, 0x1C0, 0, 255, 255, 255);
            uvVtx(sp3C, 44, 0, 0, 0x1C0, 0, 255, 255, 255);
            uvVtxEndPoly();
        }
        uvGfxStatePop();
    } else {
        uvGfxStatePush();
        uvGfxSetFlags(GFX_STATE_800000);
        uvGfxClearFlags(GFX_STATE_400000 | GFX_STATE_200000);
        if (arg1 != 0) {
            sp40 = D_80373E18 + 7;
            sp44 = D_80373E18;
            if (arg0 == 2) {
                sp3C = D_80373E10;
                uvGfx_80223A28(0x142);
                uvVtxBeginPoly();
                uvVtx(sp3C, 28, 0, 0, 0, 0, 255, 255, 255);
                uvVtx(sp3C + 17.0f, 28, 0, 0x220, 0, 0, 255, 255, 255);
                uvVtx(sp3C + 17.0f, 42, 0, 0x220, 0x1C0, 0, 255, 255, 255);
                uvVtx(sp3C, 42, 0, 0, 0x1C0, 0, 255, 255, 255);
                uvVtxEndPoly();
            } else {
                sp3C = D_80373E10;
                uvGfx_80223A28(0x13E);
                uvVtxBeginPoly();
                uvVtx(sp3C, 30, 0, 0, 0, 255, 255, 255, 255);
                uvVtx(sp3C + 30.0f, 30, 0, 0x3C0, 0, 255, 255, 255, 255);
                uvVtx(sp3C + 30.0f, 44, 0, 0x3C0, 0x1C0, 255, 255, 255, 255);
                uvVtx(sp3C, 44, 0, 0, 0x1C0, 255, 255, 255, 255);
                uvVtxEndPoly();
            }
        } else {
            sp40 = D_80373E1C + 7;
            sp44 = D_80373E1C;
            if (arg0 == 2) {
                sp3C = D_80373E14;
                uvGfx_80223A28(0x143);
                uvVtxBeginPoly();
                uvVtx(sp3C, 28, 0, 0, 0, 0, 255, 255, 255);
                uvVtx(sp3C + 13.0f, 28, 0, 0x1A0, 0, 0, 255, 255, 255);
                uvVtx(sp3C + 13.0f, 42, 0, 0x1A0, 0x1C0, 0, 255, 255, 255);
                uvVtx(sp3C, 42, 0, 0, 0x1C0, 0, 255, 255, 255);
                uvVtxEndPoly();
            } else {
                sp3C = D_80373E14;
                uvGfx_80223A28(0x13F);
                uvVtxBeginPoly();
                uvVtx(sp3C, 30, 0, 0, 0, 255, 255, 255, 255);
                uvVtx(sp3C + 77.0f, 30, 0, 0x9A0, 0, 255, 255, 255, 255);
                uvVtx(sp3C + 77.0f, 44, 0, 0x9A0, 0x1C0, 255, 255, 255, 255);
                uvVtx(sp3C, 44, 0, 0, 0x1C0, 255, 255, 255, 255);
                uvVtxEndPoly();
            }
        }
        uvGfx_80223A28(0x141);
        uvVtxBeginPoly();
        uvVtx(sp44, 31, 0, 0, 0, 255, 255, 255, 255);
        uvVtx(sp40, 31, 0, 0xE0, 0, 255, 255, 255, 255);
        uvVtx(sp40, 42, 0, 0xE0, 0x160, 255, 255, 255, 255);
        uvVtx(sp44, 42, 0, 0, 0x160, 255, 255, 255, 255);
        uvVtxEndPoly();
        uvGfxStatePop();
    }
    uvGfxMtxViewPop();
    uvGfxEnd();
}

void func_8033CBD0(s32 arg0, s32 arg1) {
    Mtx4F sp80;
    Mtx4F sp40;

    func_8033A664(0, SCREEN_WIDTH - 1, 0, SCREEN_HEIGHT - 1);
    uvGfxBegin();
    uvMat4SetOrtho(&sp80, 0.0f, SCREEN_WIDTH - 1, 0.0f, SCREEN_HEIGHT - 1);
    uvGfxMtxProjPushF(&sp80);
    uvMat4SetIdentity(&sp40);
    uvGfxMtxViewLoad(&sp40, 1);
    if (arg1 != 0) {
        uvVtxBeginPoly();

        uvVtx(D_80350560[arg0][0] - 2, D_80350560[arg0][1] - 2, 0, 0, 0, 0, 0, 0, 255);
        uvVtx(D_80350560[arg0][0] + 82, D_80350560[arg0][1] - 2, 0, 0, 0, 0, 0, 0, 255);
        uvVtx(D_80350560[arg0][0] + 82, D_80350560[arg0][1], 0, 0, 0, 0, 0, 0, 255);
        uvVtx(D_80350560[arg0][0] - 2, D_80350560[arg0][1], 0, 0, 0, 0, 0, 0, 255);
        uvVtxEndPoly();
        uvVtxBeginPoly();
        uvVtx(D_80350560[arg0][0] - 2, D_80350560[arg0][1] + 60, 0, 0, 0, 0, 0, 0, 255);
        uvVtx(D_80350560[arg0][0] + 82, D_80350560[arg0][1] + 60, 0, 0, 0, 0, 0, 0, 255);
        uvVtx(D_80350560[arg0][0] + 82, D_80350560[arg0][1] + 62, 0, 0, 0, 0, 0, 0, 255);
        uvVtx(D_80350560[arg0][0] - 2, D_80350560[arg0][1] + 62, 0, 0, 0, 0, 0, 0, 255);
        uvVtxEndPoly();
        uvVtxBeginPoly();
        uvVtx(D_80350560[arg0][0] - 2, D_80350560[arg0][1], 0, 0, 0, 0, 0, 0, 255);
        uvVtx(D_80350560[arg0][0], D_80350560[arg0][1], 0, 0, 0, 0, 0, 0, 255);
        uvVtx(D_80350560[arg0][0], D_80350560[arg0][1] + 60, 0, 0, 0, 0, 0, 0, 255);
        uvVtx(D_80350560[arg0][0] - 2, D_80350560[arg0][1] + 60, 0, 0, 0, 0, 0, 0, 255);
        uvVtxEndPoly();
        uvVtxBeginPoly();
        uvVtx(D_80350560[arg0][0] + 80, D_80350560[arg0][1], 0, 0, 0, 0, 0, 0, 255);
        uvVtx(D_80350560[arg0][0] + 82, D_80350560[arg0][1], 0, 0, 0, 0, 0, 0, 255);
        uvVtx(D_80350560[arg0][0] + 82, D_80350560[arg0][1] + 60, 0, 0, 0, 0, 0, 0, 255);
        uvVtx(D_80350560[arg0][0] + 80, D_80350560[arg0][1] + 60, 0, 0, 0, 0, 0, 0, 255);
        uvVtxEndPoly();
    } else {
        uvVtxBeginPoly();
        uvVtx(D_80350560[arg0][0] - 2, D_80350560[arg0][1] - 2, 0, 0, 0, 255, 240, 0, 255);
        uvVtx(D_80350560[arg0][0] + 82, D_80350560[arg0][1] - 2, 0, 0, 0, 255, 240, 0, 255);
        uvVtx(D_80350560[arg0][0] + 82, D_80350560[arg0][1], 0, 0, 0, 255, 240, 0, 255);
        uvVtx(D_80350560[arg0][0] - 2, D_80350560[arg0][1], 0, 0, 0, 255, 240, 0, 255);
        uvVtxEndPoly();
        uvVtxBeginPoly();
        uvVtx(D_80350560[arg0][0] - 2, D_80350560[arg0][1] + 60, 0, 0, 0, 255, 240, 0, 255);
        uvVtx(D_80350560[arg0][0] + 82, D_80350560[arg0][1] + 60, 0, 0, 0, 255, 240, 0, 255);
        uvVtx(D_80350560[arg0][0] + 82, D_80350560[arg0][1] + 62, 0, 0, 0, 255, 240, 0, 255);
        uvVtx(D_80350560[arg0][0] - 2, D_80350560[arg0][1] + 62, 0, 0, 0, 255, 240, 0, 255);
        uvVtxEndPoly();
        uvVtxBeginPoly();
        uvVtx(D_80350560[arg0][0] - 2, D_80350560[arg0][1], 0, 0, 0, 255, 240, 0, 255);
        uvVtx(D_80350560[arg0][0], D_80350560[arg0][1], 0, 0, 0, 255, 240, 0, 255);
        uvVtx(D_80350560[arg0][0], D_80350560[arg0][1] + 60, 0, 0, 0, 255, 240, 0, 255);
        uvVtx(D_80350560[arg0][0] - 2, D_80350560[arg0][1] + 60, 0, 0, 0, 255, 240, 0, 255);
        uvVtxEndPoly();
        uvVtxBeginPoly();
        uvVtx(D_80350560[arg0][0] + 80, D_80350560[arg0][1], 0, 0, 0, 255, 240, 0, 255);
        uvVtx(D_80350560[arg0][0] + 82, D_80350560[arg0][1], 0, 0, 0, 255, 240, 0, 255);
        uvVtx(D_80350560[arg0][0] + 82, D_80350560[arg0][1] + 60, 0, 0, 0, 255, 240, 0, 255);
        uvVtx(D_80350560[arg0][0] + 80, D_80350560[arg0][1] + 60, 0, 0, 0, 255, 240, 0, 255);
        uvVtxEndPoly();
    }
    uvGfxMtxViewPop();
    uvGfxEnd();
}

s32 func_8033D3EC(s32 arg0, s32 arg1, Unk80373060* arg2, s32* arg3, s32* arg4) {
    static f32 D_803505A4 = 0.0f;
    static f32 D_803505A8 = 0.025f;
    s32 pad[2];
    s32 i;
    s32 spC0;
    s32 spBC;
    f32 temp_fs0;
    f32 temp_fv0;
    f32 spB0;
    f32 spAC;
    f32 spA8;
    s32 var_s6;

    spC0 = FALSE;
    spBC = FALSE;
    while (!spBC && !spC0) {
        spBC = FALSE;
        var_s6 = FALSE;
        func_8033A6B8();
        uvGfxSetUnkStateF(0.00001f);
        func_8033A72C();
        func_8033A72C();
        for (i = *arg3; i < *arg3 + 6; i++) {
            uvClkReset(4);
            while (uvClkGetSec(4) < 0.1) { }
            if ((i < arg1) && (arg2[i].unk43[0] != 0)) {
                func_8033A610(D_80350560[i % 6][0], D_80350560[i % 6][0] + 80, D_80350560[i % 6][1], D_80350560[i % 6][1] + 59);
                func_8033A128(arg0, &arg2[i]);
                snd_play_sfx(0x54);
                func_8033FB14();
                uvCopyFrameBuf(0);
                func_8033A244(arg0, &arg2[i]);
                func_8033A244(arg0, &arg2[i]);
                func_8033A244(arg0, &arg2[i]);
            } else {
                func_80204D94(0, D_80350560[i % 6][0], D_80350560[i % 6][0] + 80, D_80350560[i % 6][1] - 1, D_80350560[i % 6][1] + 59);
                func_8033A128(arg0, NULL);
                snd_play_sfx(0x54);
                func_8033FB14();
                uvCopyFrameBuf(0);
                func_8033A244(arg0, NULL);
                func_8033A244(arg0, NULL);
                func_8033A244(arg0, NULL);
            }
        }
        uvGfxBegin();
        uvGfxEnd();
        if (arg1 != 0) {
            func_8033CBD0(*arg4, 0);
            func_8033CBD0(*arg4, 0);
        }
        D_803505A4 = 0.0f;

        while (!spBC) {
            demo_80323020();
            uvGfxBegin();

            D_803505A4 += D_803505A8;
            if (D_803505A4 > 1.0f) {
                D_803505A4 = 1.0f;
                D_803505A8 = -D_803505A8;
            } else if (D_803505A4 < 0) {
                D_803505A4 = 0;
                D_803505A8 = -D_803505A8;
            }

            fileMenuColorLerp(D_803505A4, 44.0f, 214.0f, 44.0f, 145.0f, 183.0f, 255.0f, &spB0, &spAC, &spA8);
            uvFontSet(6);
            uvFontColor((s32)spB0, (s32)spAC, (s32)spA8, 255);
            uvFontScale(1.0, 1.0);
            func_80219874(70, 190, textGetDataByIdx(0x139), 100, 0xFFE);
            uvFontGenDlist();
            uvGfxEnd();
            if ((demoButtonPress(0, B_BUTTON) != 0) || ((arg1 == 0) && (demoButtonPress(0, START_BUTTON) != 0))) {
                spBC = TRUE;
                snd_play_sfx(1);
                break;
            }
            if ((arg1 != 0) && (demoButtonPress(0, A_BUTTON | START_BUTTON) != 0)) {
                if ((((arg0 == 0) && (*arg4 < D_80350528)) || ((arg0 == 2) && (*arg4 < D_8035052C))) && (arg2[*arg4].unk43[0] != 0)) {
                    spC0 = TRUE;
                    snd_play_sfx(0x6E);
                    break;
                }
                snd_play_sfx(1);
            }

            if (arg1 != 0) {
                temp_fs0 = demoGetInputs(0, 0);
                temp_fv0 = demoGetInputs(0, 1);
                if (!var_s6 && (FABS2(temp_fs0) >= 0.3 || FABS2(temp_fv0) >= 0.3)) {
                    var_s6 = TRUE;
                    i = *arg4;
                    if (FABS2(temp_fv0) >= 0.3 && FABS2(temp_fs0) >= 0.3) {
                        if ((temp_fs0 > 0.0f) && (temp_fv0 > 0.0f)) {
                            i -= 2;
                            if (i < 0) {
                                i += 6;
                            } else if (i == 3) {
                                i = 0;
                            } else if (i == 0) {
                                i = 3;
                            }
                        } else if ((temp_fs0 > 0.0f) && (temp_fv0 < 0.0f)) {
                            i += 4;
                            if (i >= 6) {
                                i -= 6;
                            }
                        } else if ((temp_fs0 < 0.0f) && (temp_fv0 > 0.0f)) {
                            i -= 4;
                            if (i < 0) {
                                i += 6;
                            }
                        } else {
                            i += 2;
                            if (i >= 6) {
                                i -= 6;
                            } else {
                                if (i == 2) {
                                    i = 5;
                                } else if (i == 5) {
                                    i = 3;
                                }
                            }
                        }
                    } else {
                        if (FABS2(temp_fv0) >= 0.3) {
                            if (temp_fv0 > 0.0f) {
                                i -= 3;
                                if (i < 0) {
                                    i += 6;
                                }
                            } else {
                                i += 3;
                                if (i >= 6) {
                                    i -= 6;
                                }
                            }
                        } else {
                            if (temp_fs0 > 0.0f) {
                                i += 1;
                                if (i == 3) {
                                    i = 0;
                                } else if (i == 6) {
                                    i = 3;
                                }
                            } else {
                                i -= 1;
                                if (i == -1) {
                                    i = 2;
                                } else if (i == 2) {
                                    i = 5;
                                }
                            }
                        }
                    }

                    if (i != *arg4) {
                        func_8033F758(0, 1.0f, 1.03f, 0);
                        func_8033CBD0(*arg4, 1);
                        func_8033CBD0(*arg4, 1);
                        *arg4 = i;
                        func_8033CBD0(*arg4, 0);
                        func_8033CBD0(*arg4, 0);
                    }
                } else {
                    if (var_s6) {
                        if (FABS2(temp_fs0) < 0.3) {
                            if (FABS2(temp_fv0) < 0.3) {
                                var_s6 = FALSE;
                            }
                        }
                    }
                }
            }
        }
    }
    func_8033A6B8();
    return spBC;
}

void func_8033DCD0(Unk80373060* arg0, Unk80373060* arg1) {
    s32 i;

    arg0->unk0.x = arg1->unk0.x;
    arg0->unk0.y = arg1->unk0.y;
    arg0->unk0.z = arg1->unk0.z;
    arg0->unkC.x = arg1->unkC.x;
    arg0->unkC.y = arg1->unkC.y;
    arg0->unkC.z = arg1->unkC.z;
    arg0->unk18 = arg1->unk18;
    arg0->unk1C = arg1->unk1C;
    arg0->unk20 = arg1->unk20;
    arg0->unk24 = arg1->unk24;
    arg0->unk28 = arg1->unk28;
    arg0->unk2C = arg1->unk2C;
    arg0->unk30 = arg1->unk30;
    arg0->unk32 = arg1->unk32;
    arg0->unk34 = arg1->unk34;
    arg0->unk38 = arg1->unk38;
    arg0->unk3C = arg1->unk3C;

    if (arg1->unk42 == 0) {
        arg0->unk43[0] = 11;
    } else {
        arg0->unk42 = arg1->unk42;
        for (i = 0; i < arg1->unk42; i++) {
            arg0->unk43[i] = arg1->unk43[i];
            arg0->unk4C[i] = arg1->unk4C[i];
            arg0->unk64[i] = arg1->unk64[i];
        }
    }
    arg0->unk36 = arg1->unk36;
}

s32 func_8033DDD8(s32 arg0, Unk80373060* arg1, s32* arg2) {
    s32 sp2C;
    s32 sp28;

    sp28 = *arg2;
    func_8033A6B8();
    uvGfxSetUnkStateF(0.00001f);
    func_8033ADD4(1, &arg1[sp28], sp28, arg0);
    func_8033ADD4(1, &arg1[sp28], sp28, arg0);
    uvClkReset(4);
    while (uvClkGetSec(4) < 0.1) { }
    func_8033A610(58, 257, 49, 198);
    func_8033A128(1, &arg1[sp28]);
    uvCopyFrameBuf(0);
    func_8033A244(1, &arg1[sp28]);
    func_8033A244(1, &arg1[sp28]);
    func_8033A244(1, &arg1[sp28]);
    uvGfxBegin();
    uvGfxEnd();
    sp2C = 0;

    while (TRUE) {
        demo_80323020();
        uvGfxBegin();
        uvGfxEnd();
        if (demoButtonPress(0, B_BUTTON) != 0) {
            snd_play_sfx(1);
            sp2C = 1;
            break;
        } else if (demoButtonPress(0, L_CBUTTONS) != 0) {
            if (*arg2 > 0) {
                (*arg2)--;
                func_8033F758(0x6A, 1.0f, 0.5f, 0.0f);
                break;
            }
        } else if ((demoButtonPress(0, R_CBUTTONS) != 0)) {
            if (*arg2 < (arg0 - 1)) {
                (*arg2)++;
                func_8033F758(0x6A, 1.0f, 0.5f, 0.0f);
                break;
            }
        }
    }
    func_8033A6B8();
    return sp2C;
}

void func_8033DFD0(s32 arg0, Unk80373060* arg1, s32 arg2) {
    s32 var_s1;
    s32 var_s2;
    f32 temp_fv0;

    func_8033A6B8();
    uvGfxSetUnkStateF(0.00001f);
    func_8033ADD4(arg0, &arg1[arg2], 0, 0);
    func_8033ADD4(arg0, &arg1[arg2], 0, 0);
    uvClkReset(4);
    while (uvClkGetSec(4) < 0.1) { }
    func_8033A610(58, 257, 49, 198);
    func_8033A128(arg0, &arg1[arg2]);
    uvCopyFrameBuf(0);
    func_8033A244(arg0, &arg1[arg2]);
    func_8033A244(arg0, &arg1[arg2]);
    func_8033A244(arg0, &arg1[arg2]);
    uvGfxBegin();
    uvGfxEnd();

    if (arg0 == 0) {
        var_s2 = 0;
        func_8033BF00(arg0, 1, 1);
        func_8033BF00(arg0, 1, 1);
        func_8033BF00(arg0, 0, 0);
        func_8033BF00(arg0, 0, 0);
    } else if (arg0 == 2) {
        var_s2 = 0;
        if (6 - D_80350528) {
            func_8033BF00(arg0, 0, 0);
            func_8033BF00(arg0, 0, 0);
            var_s2 = 0;
        }
    }

    var_s1 = 0;
    while (TRUE) {
        demo_80323020();
        uvGfxBegin();
        uvGfxEnd();
        if (demoButtonPress(0, B_BUTTON) != 0) {
            snd_play_sfx(1);
            break;
        }
        if (demoButtonPress(0, A_BUTTON | START_BUTTON) != 0) {
            snd_play_sfx(0x6E);
            if (arg0 == 0) {
                if (var_s2) {
                    D_80373060[arg2].unk43[0] = 0;
                    D_80373060[arg2].unk36 = 0;
                    D_80350550 = 1;
                }
            } else if ((arg0 == 2) && (var_s2) && (6 - D_80350528)) {
                func_8033DCD0(&D_80373060[D_80350528], &arg1[arg2]);
                D_80350528++;
                D_80350550 = 1;
            }
            break;
        }
        if ((arg0 == 0) || (6 - D_80350528)) {
            temp_fv0 = demoGetInputs(0, 0);
            if (var_s1 == 0 && FABS2(temp_fv0) >= 0.3) {
                var_s1 = 1;
                func_8033F758(0, 1.0f, 1.03f, 0);
                var_s2 = !var_s2;
                func_8033BF00(arg0, !var_s2, 1);
                func_8033BF00(arg0, !var_s2, 1);
                func_8033BF00(arg0, var_s2, 0);
                func_8033BF00(arg0, var_s2, 0);
            } else {
                if (var_s1 != 0) {
                    if (FABS2(temp_fv0) < 0.3) {
                        var_s1 = 0;
                    }
                }
            }
        }
    }
    func_8033A6B8();
}

s32 func_8033E3A8(s32 arg0) {
    s32 spC4;
    s32 var_s0;
    s32 spBC;
    s32 spB8;
    f32 spB4;
    f32 spB0;
    f32 spAC;
    f32 spA8;
    f32 spA4;
    f32 spA0;
    Mtx4F sp60;
    Unk802D3658_Arg0* temp_s4;
    s32 renderFlags;
    u8* ptr;
    u16 sp52;
    u16 sp50;
    u16 sp4E;

    temp_s4 = D_80362690->unk0[D_80362690->unk9C].unkC.unk70;
    ptr = levelGet_80345CB0();
    D_80350550 = 0;
    if ((D_80362690->unk0[0].unk0 != 7) && (ptr[1] == 1)) {
        func_803405E4();
    }
    if (arg0 == 3) {
        arg0 = 1;
        D_80350594 = 1;
    }
    if ((arg0 == 0) || (D_80350594 != 0)) {
        func_80338404();
        uvLevelInit();
        uvLevelAppend(0x1B);
        textLoadBlock(0x42);
    } else {
        spC4 = func_80339F9C();
        uvDobjState(spC4, 0);
        spB4 = temp_s4->unk2C;
        spB0 = temp_s4->unk30;
        spAC = temp_s4->unk34;
        spA8 = temp_s4->unk38;
        spA4 = temp_s4->unk3C;
        spA0 = temp_s4->unk40;
        uvMat4Copy(&sp60, &temp_s4->unk108);
    }
    spBC = 0;
    spB8 = 0;
    var_s0 = 0;
    while (var_s0 == 0) {
        // FAKE
        if (1) { }
        if (arg0 == 0) {
            var_s0 = func_8033D3EC(arg0, D_80350528, D_80373060, &spBC, &spB8);
            if (var_s0 == 0) {
                func_8033DFD0(arg0, D_80373060, spB8);
            }
        } else if (arg0 == 1) {
            renderFlags = hudGetState()->renderFlags;
            hudGetState()->renderFlags = HUD_RENDER_DISABLE;
            switch (D_80362690->unk0[0].map) {
            case 3:
                var_s0 = func_8033DDD8(D_80350538, D_80373630, &spB8);
                break;
            case 5:
                var_s0 = func_8033DDD8(D_8035053C, D_803738D0, &spB8);
                break;
            case 10:
                var_s0 = func_8033DDD8(D_80350540, D_80373B70, &spB8);
                break;
            default:
                var_s0 = 1;
                break;
            }
            if (var_s0 != 0) {
                hudGetState()->renderFlags = renderFlags;
            }
        } else {
            var_s0 = func_8033D3EC(arg0, D_8035052C, D_80373390, &spBC, &spB8);
            if (var_s0 == 0) {
                func_8033DFD0(arg0, D_80373390, spB8);
            }
        }
    }
    if ((arg0 != 0) && (D_80350594 == 0)) {
        uvDobjState(spC4, 2);
        temp_s4->unk2C = spB4;
        temp_s4->unk30 = spB0;
        temp_s4->unk34 = spAC;
        temp_s4->unk38 = spA8;
        temp_s4->unk3C = spA4;
        temp_s4->unk40 = spA0;
        uvMat4Copy(&temp_s4->unk108, &sp60);
        func_80204C94(0, temp_s4->unk2C, temp_s4->unk30, temp_s4->unk34, temp_s4->unk38, temp_s4->unk3C, temp_s4->unk40);
        func_80204B34(0, &sp60);
    }
    uvGfxSetUnkStateF(-1.0f);
    func_80204D94(0, temp_s4->unk24, temp_s4->unk26, temp_s4->unk28, temp_s4->unk2A);
    func_80204A8C(0, 3);
    uvGfxSetViewport(0, 0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);
    func_8033A078(arg0);
    if ((arg0 == 0) || (D_80350594 != 0)) {
        func_802EBBB8();
    }
    D_80350594 = 0;
    levelGetClsVehTest(&sp52, &sp50, &sp4E);
    func_8033FCD0(sp50);
    return D_80350550;
}

void func_8033E784(Unk8033F050* arg0, s32 arg1, s32 arg2) {
    if (arg2 != 0) {
        ((u8*)arg0)[arg1 / 8] |= 1 << (arg1 % 8);
    } else {
        ((u8*)arg0)[arg1 / 8] &= ~(1 << (arg1 % 8));
    }
}

s32 func_8033E810(Unk8033F050* arg0, s32 arg1) {
    if (((u8*)arg0)[arg1 / 8] & (1 << (arg1 % 8))) {
        return 1;
    }
    return 0;
}

void func_8033E860(Unk8033F050** arg0) {
    Unk8033F050* var_s1;
    Unk8033F050 sp6C;
    s32 i;
    s32 j;
    s32 var_s5;

    var_s5 = 0;
    *arg0 = D_80373300;
    func_80338404();

    for (i = 0; i < 6; i++) {
        var_s1 = &sp6C;
        if ((i < D_80350528) && (D_80373060[i].unk43[0] != 0)) {
            var_s1->unk0 = func_8034AD14(D_80373060[i].unk0.x);
            var_s1->unk2 = func_8034AD14(D_80373060[i].unk0.y);
            var_s1->unk4 = func_8034AD14(D_80373060[i].unk0.z);
            var_s1->unk6 = func_8034AD14(D_80373060[i].unkC.x * (6.4 / 9.0));
            var_s1->unk7 = func_8034AD14(D_80373060[i].unkC.y * (6.4 / 9.0));
            var_s1->unk8 = func_8034AD14(D_80373060[i].unkC.z * (6.4 / 9.0));
            var_s1->unk9_2 = D_80373060[i].unk30;
            var_s1->unk9_0 = D_80373060[i].unk32;
            var_s1->unk12_4 = D_80373060[i].unk34;
            var_s1->unk12_7 = D_80373060[i].unk42;

            if (var_s1->unk12_7 == 0) {
                var_s1->unk9_4 = 11;
            } else {
                for (j = 0; j < D_80373060[i].unk42; j++) {
                    switch (j) {
                    case 0:
                        var_s1->unk9_4 = D_80373060[i].unk43[j];
                        var_s1->unkC = D_80373060[i].unk4C[j] * 255.0f;
                        var_s1->unk12_10 = D_80373060[i].unk64[j];
                        break;
                    case 1:
                        var_s1->unk9_8 = D_80373060[i].unk43[j];
                        var_s1->unkD = D_80373060[i].unk4C[j] * 255.0f;
                        var_s1->unk12_13 = D_80373060[i].unk64[j];
                        break;
                    case 2:
                        var_s1->unk9_12 = D_80373060[i].unk43[j];
                        var_s1->unkE = D_80373060[i].unk4C[j] * 255.0f;
                        var_s1->unk12_16 = D_80373060[i].unk64[j];
                        break;
                    case 3:
                        var_s1->unk9_16 = D_80373060[i].unk43[j];
                        var_s1->unkF = D_80373060[i].unk4C[j] * 255.0f;
                        var_s1->unk12_19 = D_80373060[i].unk64[j];
                        break;
                    case 4:
                        var_s1->unk9_20 = D_80373060[i].unk43[j];
                        var_s1->unk10 = D_80373060[i].unk4C[j] * 255.0f;
                        var_s1->unk12_22 = D_80373060[i].unk64[j];
                        break;
                    case 5:
                        var_s1->unk12_0 = D_80373060[i].unk43[j];
                        var_s1->unk11 = D_80373060[i].unk4C[j] * 255.0f;
                        var_s1->unk12_25 = D_80373060[i].unk64[j];
                        break;
                    }
                }
            }
        } else {
            var_s1->unk0 = 0;
            var_s1->unk2 = 0;
            var_s1->unk4 = 0;
            var_s1->unk6 = 0;
            var_s1->unk7 = 0;
            var_s1->unk8 = 0;
            var_s1->unk9_2 = 0;
            var_s1->unk9_0 = 0;
            var_s1->unk12_4 = 0;
            var_s1->unk12_7 = 0;
            var_s1->unk9_4 = 0;
            var_s1->unkC = 0;
        }

        for (j = 0; j < 172; j++) {
            func_8033E784(*arg0, var_s5, func_8033E810(&sp6C, j));
            var_s5++;
        }
    }
}

void func_8033F050(s32 arg0) {
    Unk8033F050* var_s1;
    Unk8033F050 sp84;
    Unk802D3658_Arg0* temp_s4;
    Unk80362690_Unk0_UnkC* var_v1;
    s32 i;
    s32 j;
    s32 var_s3;
    s32 pad;

    var_v1 = &D_80362690->unk0[D_80362690->unk9C].unkC;
    temp_s4 = var_v1->unk70;
    D_80350528 = 0;
    var_s3 = 0;

    for (i = 0; i < 6; i++) {
        var_s1 = &sp84;
        for (j = 0; j < 172; j++) {
            func_8033E784(var_s1, j, func_8033E810(arg0, var_s3));
            var_s3++;
        }
        if (var_s1->unk9_4) {
            D_80373060[D_80350528].unk0.x = var_s1->unk0;
            D_80373060[D_80350528].unk0.y = var_s1->unk2;
            D_80373060[D_80350528].unk0.z = var_s1->unk4;
            D_80373060[D_80350528].unkC.x = var_s1->unk6 * 1.40625;
            D_80373060[D_80350528].unkC.y = var_s1->unk7 * 1.40625;
            D_80373060[D_80350528].unkC.z = var_s1->unk8 * 1.40625;
            D_80373060[D_80350528].unk28 = temp_s4->unk3C;
            D_80373060[D_80350528].unk2C = temp_s4->unk40;
            D_80373060[D_80350528].unk18 = (temp_s4->unk2C * temp_s4->unk3C) * 0.45;
            D_80373060[D_80350528].unk1C = (temp_s4->unk30 * temp_s4->unk3C) * 0.45;
            D_80373060[D_80350528].unk20 = (temp_s4->unk38 * temp_s4->unk3C) * 0.45;
            D_80373060[D_80350528].unk24 = (temp_s4->unk34 * temp_s4->unk3C) * 0.45;
            D_80373060[D_80350528].unk18 = temp_s4->unk2C * 0.45;
            D_80373060[D_80350528].unk1C = temp_s4->unk30 * 0.45;
            D_80373060[D_80350528].unk20 = temp_s4->unk38 * 0.45;
            D_80373060[D_80350528].unk24 = temp_s4->unk34 * 0.45;
            D_80373060[D_80350528].unk30 = var_s1->unk9_2;
            D_80373060[D_80350528].unk34 = var_s1->unk12_4;
            D_80373060[D_80350528].unk32 = var_s1->unk9_0;
            D_80373060[D_80350528].unk42 = var_s1->unk12_7;
            if (var_s1->unk12_7 == 0) {
                D_80373060[D_80350528].unk43[0] = 11;
            } else {
                for (j = 0; j < var_s1->unk12_7; j++) {
                    switch (j) {
                    case 0:
                        D_80373060[D_80350528].unk43[j] = var_s1->unk9_4;
                        D_80373060[D_80350528].unk4C[j] = var_s1->unkC / 255.0f;
                        D_80373060[D_80350528].unk64[j] = var_s1->unk12_10;
                        break;
                    case 1:
                        D_80373060[D_80350528].unk43[j] = var_s1->unk9_8;
                        D_80373060[D_80350528].unk4C[j] = var_s1->unkD / 255.0f;
                        D_80373060[D_80350528].unk64[j] = var_s1->unk12_13;
                        break;
                    case 2:
                        D_80373060[D_80350528].unk43[j] = var_s1->unk9_12;
                        D_80373060[D_80350528].unk4C[j] = var_s1->unkE / 255.0f;
                        D_80373060[D_80350528].unk64[j] = var_s1->unk12_16;
                        break;
                    case 3:
                        D_80373060[D_80350528].unk43[j] = var_s1->unk9_16;
                        D_80373060[D_80350528].unk4C[j] = var_s1->unkF / 255.0f;
                        D_80373060[D_80350528].unk64[j] = var_s1->unk12_19;
                        break;
                    case 4:
                        D_80373060[D_80350528].unk43[j] = var_s1->unk9_20;
                        D_80373060[D_80350528].unk4C[j] = var_s1->unk10 / 255.0f;
                        D_80373060[D_80350528].unk64[j] = var_s1->unk12_22;
                        break;
                    case 5:
                        D_80373060[D_80350528].unk43[j] = var_s1->unk12_0;
                        D_80373060[D_80350528].unk4C[j] = var_s1->unk11 / 255.0f;
                        D_80373060[D_80350528].unk64[j] = var_s1->unk12_25;
                        break;
                    }
                }
            }
            D_80350528++;
        }
    }
}

s32 snapGetPhotoCount(void) {
    return 6 - D_8035052C;
}

s32 func_8033F62C(void) {
    return D_8035052C;
}
