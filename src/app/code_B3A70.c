#include "common.h"
#include "birdman.h"
#include "cannonball.h"
#include "code_9A960.h"
#include "code_B3A70.h"
#include "code_D1ED0.h"
#include "code_D2D50.h"
#include "demo.h"
#include "environment.h"
#include "hud.h"
#include "fdr.h"
#include "map3d.h"
#include "shadow.h"
#include "snd.h"
#include "wind_objects.h"
#include <uv_font.h>
#include <uv_dobj.h>
#include <uv_event.h>
#include <uv_vector.h>

s32 D_8034FC10[] = { 0xDC, 0x14E, 0x12F, 0x1D };
s32 D_8034FC20[] = { 0xDC, 0x1D };
s32 D_8034FC28[] = { 0xDC, 0x14E, 0x1D };
Vec3F D_8034FC34 = { 0.0f, 0.0f, 1.0f };

f32 func_802E6B68(void);                                /* fdr.h */
void func_802E7278(Mtx4F*, u16*);                      /* fdr.h */
void func_802EF368(void*);                 /* code_76670.h */
void func_802EF5B0(void*, u8);             /* code_76670.h */
void func_802F5BF0(void*);                 /* code_7CF30.h */
void func_802F604C(void*, u8);             /* code_7CF30.h */
void func_802FA108(void*);                 /* code_81490.h */
void func_802FA2D0(void*, u8);             /* code_81490.h */
f32 func_8031385C(Mtx4F*, Mtx4F*, Unk802D3658_Arg0*); /* code_9A960.h */
void func_8032150C(void);                                  /* proxanim.h */
void func_80324EC4(void*);                 /* code_AC1A0.h */
void func_80325160(void*, u8);             /* code_AC1A0.h */
void func_8032D33C(Mtx4F*, Mtx4F*, f32, s32);            /* static */
void func_8032FC08(void*);                 /* skydiving.h */
void func_803308C4(void*, u8);             /* skydiving.h */
void func_803213E0(void);                                  /* proxanim.h */
void func_80321400(void);                                  /* proxanim.h */


#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/nonmatchings/app/code_B3A70/func_8032C540.s")
#else
// .rodata diff?
void func_8032C540(Unk80362690* arg0) {
    f32 var_fs3;
    Unk80367704* sp1E0;
    Unk80367704* sp1DC;
    Unk80367704* sp1D8;
    Unk80367704* sp1D4;
    Unk80367704* sp1D0;
    Unk80367704* sp1CC;
    Unk80367704* sp1C8;
    Mtx4F sp188;
    Mtx4F sp148;
    Mtx4F sp108;
    Mtx4F spC8;
    Mtx4F sp88;
    u8 sp87;
    u8 var_s4;
    Unk80362690_Unk0_UnkC* temp_s0;
    f32 temp_fa0;
    f32 var_fs0;
    f32 var_fs2;
    f32 temp_fv0;
    f32 sp6C;
    u16 pad_sp6A;
    u16 sp68;
    u16 sp66;
    u16 sp64;

    temp_s0 = &arg0->unk0[arg0->unk9C].unkC;
    var_s4 = 0;
    var_fs3 = 0.0f;
    var_fs0 = 0.0f;
    var_fs2 = 0.0f;
    uvEventPost(0x12, 0);
    switch (temp_s0->veh) {
    case VEHICLE_HANG_GLIDER:
        sp1E0 = temp_s0->unk6C;
        func_802EF368(sp1E0);
        sp87 = sp1E0->unk0;
        sp1E0->unk2 &= ~8;
        break;
    case VEHICLE_GYROCOPTER:
        sp1DC = temp_s0->unk6C;
        func_802F5BF0(sp1DC);
        sp87 = sp1DC->unk0;
        sp1DC->unk2 &= ~8;
        break;
    case VEHICLE_ROCKET_BELT:
        sp1D8 = temp_s0->unk6C;
        func_80324EC4(sp1D8);
        sp87 = sp1D8->unk0;
        sp1D8->unk2 &= ~8;
        break;
    case VEHICLE_CANNONBALL:
        sp1D4 = temp_s0->unk6C;
        cannon_802D5C5C((Unk802D5B50_Arg2*)sp1D4);
        sp87 = sp1D4->unk0;
        sp1D4->unk2 &= ~8;
        break;
    case VEHICLE_SKY_DIVING:
        sp1D0 = temp_s0->unk6C;
        func_8032FC08(sp1D0);
        sp87 = sp1D0->unk0;
        sp1D0->unk2 &= ~8;
        break;
    case VEHICLE_JUMBLE_HOPPER:
        sp1CC = temp_s0->unk6C;
        func_802FA108(sp1CC);
        sp87 = sp1CC->unk0;
        sp1CC->unk2 &= ~8;
        break;
    case VEHICLE_BIRDMAN:
        sp1C8 = temp_s0->unk6C;
        bird_802CC39C((Unk80367704* ) sp1C8);
        sp87 = sp1C8->unk0;
        sp1C8->unk2 &= ~8;
        break;
    }
    uvDobjState(sp87, 2);
    uvMat4Copy(&sp148, &temp_s0->unk2C);
    func_8032D33C(&sp188, &sp148, temp_s0->unk70->unk8, 0);
    func_802D5884(temp_s0->unk70, 5U);
    temp_s0->unk70->unk1A0 = 2.0f;
    temp_s0->unk70->unk0 = 0x70;
    func_802E68B0(3);
    hudGetState()->renderFlags = 0;
    uvEventPost(0x10, 0);
    func_80313E0C(func_802E6B68());
    sp6C = -100.0f;
    sp68 = arg0->unk0[0].unk6;
    sp64 = 0xFFFF;
    func_802E7278(&sp108, &sp66);
    func_8032D33C(&sp108, &sp108, temp_s0->unk70->unk8, 1);
    temp_s0->unk70->unk8 = 1.0f;
    while (var_fs2 == 0.0f || D_8034F850 < var_fs2) {
        var_fs0 += D_8034F854;
        if (func_802E6B5C() == 4 && var_fs2 == 0.0f) {
            var_fs2 = var_fs0 + 0.2f;
        }
        demo_80323020();
        if (demoButtonPress(arg0->unk9C, A_BUTTON|START_BUTTON|B_BUTTON) != 0) {
            if (demoButtonPress(arg0->unk9C, A_BUTTON|START_BUTTON) != 0) {
                snd_play_sfx(0x6EU);
            } else if (demoButtonPress(arg0->unk9C, B_BUTTON) != 0) {
                snd_play_sfx(1U);
            }
            break;
        }

        switch (temp_s0->veh) {
        case VEHICLE_HANG_GLIDER:
            sp1E0 = temp_s0->unk6C;
            func_802EF5B0(sp1E0, arg0->unk0->unk0);
            uvMat4Copy(&sp148, &sp1E0->unk10);
            break;
        case VEHICLE_GYROCOPTER:
            sp1DC = temp_s0->unk6C;
            func_802F604C(sp1DC, arg0->unk0->unk0);
            uvMat4Copy(&sp148, &sp1DC->unk10);
            break;
        case VEHICLE_ROCKET_BELT:
            sp1D8 = temp_s0->unk6C;
            func_80325160(sp1D8, arg0->unk0->unk0);
            uvMat4Copy(&sp148, &sp1D8->unk10);
            break;
        case VEHICLE_CANNONBALL:
            sp1D4 = temp_s0->unk6C;
            cannonMovementFrame((Unk802D5B50_Arg2*)sp1D4, arg0->unk0->unk0);
            uvMat4Copy(&sp148, (Mtx4F*) &((f32*)sp1D4)[5]);
            break;
        case VEHICLE_SKY_DIVING:
            sp1D0 = temp_s0->unk6C;
            func_803308C4(sp1D0, arg0->unk0->unk0);
            uvMat4Copy(&sp148, &sp1D0->unk10);
            break;
        case VEHICLE_JUMBLE_HOPPER:
            sp1CC = temp_s0->unk6C;
            func_802FA2D0(sp1CC, arg0->unk0->unk0);
            uvMat4Copy(&sp148, (Mtx4F* ) &((u8*)sp1CC)[0x74]);
            break;
        case VEHICLE_BIRDMAN:
            sp1C8 = temp_s0->unk6C;
            bird_802CC55C((Unk80367704* ) sp1C8, arg0->unk0->unk0);
            uvMat4Copy(&sp148, &sp1C8->unk10);
            break;
        }
        sp66 = arg0->unk0[0].unk6;
        if (sp66 != sp64) {
            uvChanTerra(temp_s0->unk70->unk22C, sp66);
            level_80345A24();
            sp64 = sp66;
        }
        if (sp66 != sp68) {
            uvMat4Copy(&spC8, &sp108);
        } else {
            uvMat4Copy(&spC8, &sp188);
        }
        uvMat4Copy(&temp_s0->unk70->unk80, &sp148);
        if ((var_fs0 - sp6C) < 3.0f) {
            uvMat4Copy(&spC8, &sp88);
        } else if (func_802D472C(temp_s0->unk70, &spC8) & 0xFF) {
            sp6C = var_fs0;
            uvMat4Copy(&sp88, &spC8);
        }
        uvMat4UnkOp6(&temp_s0->unk70->unk108, &sp148, &spC8);
        temp_fv0 = func_8031385C(&temp_s0->unk70->unk108, &temp_s0->unk70->unk80, temp_s0->unk70);
        temp_fa0 = 0.5f + (0.2f * temp_fv0);
        if (temp_fa0 < 1.0f) {
            temp_fa0 = 1.0f;
        } else if (temp_fa0 > 4.0f) {
            temp_fa0 = 4.0f;
        }
        func_802D45C4(temp_s0->unk70, temp_fa0);
        func_802D4A30(temp_s0->unk70, &temp_s0->unk70->unk108);
        func_802D3444(temp_s0->unk70);
        level_80345464(&sp148, 0.0f);
        func_8032150C();
        uvFontSet(0);
        uvFontScale(1.0, 0.800000011920929);
        uvGfxBegin();
        func_8034B624(temp_s0->unk70);
        if (var_fs3 > 0.5f) {
            var_fs3 = 0.0f;
            var_s4 = var_s4 == 0;
        }
        if (var_s4) {
            uvFontColor(0xFF, 0xFF, 0U, 0xFF);
            uvFontPrintStr(20, 200, "REPLAY");
            uvFontGenDlist();
        }
        uvGfxEnd();
        func_80313D74();
        func_802E15F0();
        func_8034E274();
        var_fs3 += D_8034F854;
    }
    uvEventPost(0xC, 0);
    func_8033F964(2);
}
#endif

void func_8032CC44(Unk80362690* arg0) {
    Unk80362690_Unk0_UnkC* sp2C;
    s32 sp28;
    s32 sp24;
    s32 sp20;
    s32 sp1C;
    u8 sp1B;
    Unk802D5B50_Arg2* temp_v0;

    sp2C = &arg0->unk0[arg0->unk9C].unkC;
    sp1B = 1;
    func_8032D51C(0);
    func_8034C25C();
    level_8030BA60();
    if (arg0->unkA0 == 0) {
        sp1B = 0;
    }
    level_8034536C();
    func_8034E628();
    func_803213E0();
    cannon_802D8A40(1U, (Unk802D5B50_Arg2*)sp2C->unk6C);
    sp20 = 0xFFFF;
    sp1C = 0;
    switch (sp2C->veh) {
    case VEHICLE_GYROCOPTER:
        temp_v0 = (Unk802D5B50_Arg2*) sp2C->unk6C;
        sp28 = temp_v0->unk0;
        sp24 = temp_v0->unk2;
        break;
    case VEHICLE_HANG_GLIDER:
        temp_v0 = (Unk802D5B50_Arg2*) sp2C->unk6C;
        sp28 = temp_v0->unk0;
        sp24 = temp_v0->unk2;
        break;
    case VEHICLE_ROCKET_BELT:
        temp_v0 = (Unk802D5B50_Arg2*) sp2C->unk6C;
        sp1C = 0x22;
        sp28 = temp_v0->unk0;
        sp24 = temp_v0->unk2;
        sp20 = temp_v0->pad6;
        break;
    case VEHICLE_CANNONBALL:
        temp_v0 = (Unk802D5B50_Arg2*) sp2C->unk6C;
        sp28 = temp_v0->unk0;
        sp24 = temp_v0->unk2;
        break;
    case VEHICLE_SKY_DIVING:
        temp_v0 = (Unk802D5B50_Arg2*) sp2C->unk6C;
        sp28 = temp_v0->unk0;
        sp24 = temp_v0->unk2;
        break;
    case VEHICLE_JUMBLE_HOPPER:
        temp_v0 = (Unk802D5B50_Arg2*) sp2C->unk6C;
        sp28 = temp_v0->unk0;
        sp24 = temp_v0->unk2;
        break;
    case VEHICLE_BIRDMAN:
        temp_v0 = (Unk802D5B50_Arg2*) sp2C->unk6C;
        sp28 = temp_v0->unk0;
        sp24 = temp_v0->unk2;
    }
    uvDobjState(sp28, 0);
    if (sp20 != 0xFFFF) {
        uvDobjState(sp20, 0);
    }
    func_803343D8(0);
    uvLevelInit();
    switch (arg0->unk0[0].map) {
    case 1:
        uvLevelAppend(0);
        break;
    case 3:
        uvLevelAppend(2);
        break;
    case 5:
        uvLevelAppend(4);
        break;
    case 10:
        uvLevelAppend(9);
        break;
    }
    uvLevelAppend(0xB);
    uvLevelAppend(0x87);
    func_8030FE80(arg0, 1);
    func_8032D51C(0);
    uvLevelInit();
    levelLoad(arg0->unk0->map, sp2C->pilot, sp2C->veh, 1);
    func_803343D8(1);
    uvDobjState(sp28, sp24);
    if (sp20 != 0xFFFF) {
        uvDobjState(sp20, sp1C);
    }
    func_80321400();
    func_8034E0B4();
    if (sp1B != 0) {
        arg0->unkA0 = 1;
    }
    level_8034528C();
    cannon_802D8A40(0U, (Unk802D5B50_Arg2*) sp2C->unk6C);
    hudInit();
    func_8034C298();
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_B3A70/func_8032CF28.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_B3A70/func_8032D33C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_B3A70/func_8032D51C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_B3A70/func_8032D90C.s")
