#include "common.h"

#include <uv_audio.h>
#include <uv_controller.h>
#include <uv_dobj.h>
#include <uv_event.h>
#include <uv_level.h>
#include <uv_math.h>
#include <uv_matrix.h>
#include <uv_memory.h>
#include <uv_model.h>
#include "cannonball.h"
#include "cbsound.h"
#include "code_5A6A0.h"
#include "code_60020.h"
#include "code_66160.h"
#include "code_72010.h"
#include "code_72B70.h"
#include "code_7FED0.h"
#include "code_9A960.h"
#include "code_9F2D0.h"
#include "code_A9D00.h"
#include "fdr.h"
#include "save.h"
#include "snd.h"

// .data likely owned by this file
extern f32 D_8034E9F0;
extern u8 D_8034E9F4;
extern s32 D_8034E9F8;
extern f32 D_8034E9FC;
extern u8 D_80359A84;
extern f32 D_80359AB0;
extern f32 D_80359AB4;
extern f32 D_80359AB8;
extern f32 D_80359AC0;
extern f32 D_80359AC4;
extern f32 D_80359AC8;

// .bss likely owned by this file
extern Unk803599D0 D_80359A30;

void cannon_802D5A90(void) {
    D_80359A30.unk0 = 8;
    D_80359A30.unk4 = 0.0f;
    D_80359A30.unk8 = 0.0f;
    D_80359A30.unkC = 0.2f;
    D_80359A30.unk10 = 0.04f;
    D_80359A30.unk14 = 0.4f;
    D_80359A30.unk18 = 0.16f;
    D_80359A30.unk1C = 0.6f;
    D_80359A30.unk20 = 0.36f;
    D_80359A30.unk24 = 0.7f;
    D_80359A30.unk28 = 0.49f;
    D_80359A30.unk2C = 0.8f;
    D_80359A30.unk30 = 0.64f;
    D_80359A30.unk34 = 0.9f;
    D_80359A30.unk38 = 0.81f;
    D_80359A30.unk40 = 1.0f;
    D_80359A30.unk3C = 1.0f;
}

// cannonLoadLevel is invoked when loading cannonball level
void cannonLoadLevel(u8 arg0, u8 pilot, Unk802D5B50_Arg2* arg2, Unk802D3658_Arg0* arg3) {
    uvMemSet(arg2, 0, sizeof(*arg2));
    cannonLoadPilot(pilot, arg2);
    arg2->unk0 = func_8021731C();
    arg2->unk2 = 2;
    uvDobjModel(arg2->unk0, arg2->unk220);
    uvDobjPosm(arg2->unk0, 0, &arg2->unk14);
    uvDobjState(arg2->unk0, arg2->unk2);
    arg2->unk54 = func_8021731C();
    arg2->unk56 = 2;
    uvDobjModel(arg2->unk54, 0x105);
    uvDobjPosm(arg2->unk54, 0, &arg2->unk58);
    uvDobjState(arg2->unk54, arg2->unk56);
    arg2->unkB0 = arg3;
    arg3->unk40 += 100.0f;
    arg2->unk10 = arg0;
    arg2->unkA4 = 0.0f;
    arg2->unk293 = 0;
    arg2->unk4 = 2;
    func_802D9430(arg2);
    func_802D9CB0(arg2);
}

// cannon_802D5C5C is invoked when loading and exiting cannonball level
void cannon_802D5C5C(Unk802D5C5C_Arg0* arg0) {
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;

    if (arg0->unkE == 0) {
        db_getstart(&arg0->unk58, &arg0->unk1B8, 0, 0);
        uvDobjPosm(arg0->unk54, 0, &arg0->unk58);
        func_80313570(&arg0->unk58, &sp54, &sp50, &sp4C, &sp48, &sp44, &sp40);
        arg0->unk98 = sp48;
        arg0->unkA0 = 0.52359873f;
        arg0->unk9C = 0.0f;
    }
    uvMat4Copy(&arg0->unk14, &arg0->unk58);
    uvDobjPosm(arg0->unk0, 0, &arg0->unk14);
    func_802D94EC(arg0);
    arg0->unkCC = 0.0f;
    arg0->unkD0 = 0.0f;
    arg0->unkD4 = 0;
    arg0->unkC4 = 0;
    arg0->unkC8 = 0.0f;
    arg0->unk293 = 0;
    arg0->unk8 = 0.0f;
    arg0->unk2 = 2;
    arg0->unk56 = 2;
    uvDobjState(arg0->unk0, 2 & 0xFF);
    uvDobjState(arg0->unk54, arg0->unk56);
    arg0->unkB4 = 5;
    arg0->unkB8 = 1.0f;
    arg0->unkB0->unk1 = arg0->unkB4;
    arg0->unkB0->unk4 = arg0->unk54;
    arg0->unkB0->unk6 = arg0->unk56;
    arg0->unkB0->unk0 = 0x20;
    arg0->unkB0->unk68 = arg0->unk26C;
    arg0->unkB0->unk6C = arg0->unk270;
    arg0->unkB0->unk70 = arg0->unk274;
    arg0->unkB0->unk74 = 0.0f;
    arg0->unkB0->unk5C = 0;
    arg0->unkB0->unk60 = -1.0f;
    arg0->unkB0->unk64 = -2.0f;
    arg0->unkB0->unk54 = 2.0f;
    arg0->unkB0->unk58 = 6.0f;
    arg0->unkB0->unk48 = 0.06f;
    arg0->unkB0->unk4C = 1;
    arg0->unkB0->unk50 = 0.0f;
    arg0->unkB0->unk228 = 0.0f;
    uvModelGetProps(arg0->unk220, 1, &arg0->unkB0->unk8, 0);
    func_802D45C4(arg0->unkB0, arg0->unkB8);
    D_8034E9F0 = 4.712389f;
    D_8034E9F4 = 0;
    D_8034E9F8 = 0;
}

// cannonEndTarget is invoked at the end of a cannonball target
void cannonEndTarget(Unk802D5B50_Arg2* arg0) {
    uvDobjModel(arg0->unk0, 0xFFFF);
    uvDobjModel(arg0->unk54, 0xFFFF);
    arg0->unk10 = 0xFFFF;
    arg0->unk0 = 0xFFFF;
    arg0->unk54 = 0xFFFF;
    arg0->unkB0->unk40 -= 100.0f;
}

// cannonMovementFrame called every frame while aiming cannon and while in flight
void cannonMovementFrame(Unk802D5C5C_Arg0* arg0, u8 arg1);
#pragma GLOBAL_ASM("asm/nonmatchings/app/cannonball/cannonMovementFrame.s")

// cannonAimingFrame does not initialize sp34, likely need CC_CHECK ignores
#if defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsometimes-uninitialized"
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif
// cannonAimingFrame called every frame while inside cannon
// controls the rate of rotation and Z-button presses
void cannonAimingFrame(Unk802D5C5C_Arg0* arg0);
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/app/cannonball/cannonAimingFrame.s")

// cannonShoot called when firing the cannon
void cannonShoot(Unk802D5C5C_Arg0* arg0) {
    Mtx4F sp50;

    uvMat4Copy(&sp50, &arg0->unk58);
    uvMat4RotateAxis(&sp50, arg0->unk9C, 'z');
    uvMat4RotateAxis(&sp50, arg0->unkA0, 'x');
    uvMat4UnkOp2(&sp50, 0.0f, 6.0f, 0.0f);
    func_802F9BF8(2, sp50.m[3][0], sp50.m[3][1], sp50.m[3][2], 20.0f, 0.3f, 0.0f, 1.0f, 0.8f, 0.0f, 1.0f);
    func_8033F7F8(0x4B);
    uvEmitterTrigger(arg0->unk2B4);
    arg0->unkD4 = 1;
    arg0->unk1B8 = 0.0f;
    arg0->unk1BC = 0.0f;
    arg0->unk1C0 = (arg0->unkA4 * 271.4f * arg0->unk280) + 2.5f;
    uvMat4Copy(&arg0->unk14, &sp50);
    uvMat4RotateAxis(&arg0->unk14, -1.5707963f, 'x');
    uvDobjState(arg0->unk0, arg0->unk2);
    D_80359A84 = 0;
    func_802D9430(arg0);
}

#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/nonmatchings/app/cannonball/cannonPilotLand.s")
#else
// cannonPilotLand called when pilot lands on surface after being shot from cannon
void cannonPilotLand(Unk802D5C5C_Arg0* arg0) {
    Unk802D3658_Arg0* temp_v0;
    f32 temp_fv0_2;
    f32 var_fv1;
    f32 spB8;
    f32 z;
    Mtx4F sp74;
    Mtx4F sp34;

    if (arg0->unk293 == 0) {
        arg0->unk293 = 1;
        if (arg0->unk11C != 0) {
            z = arg0->unk14.m[3][2]; // forces going through f0, instead of a2 direct
            func_802F8AB8(arg0->unk14.m[3][0], arg0->unk14.m[3][1], z, 1.0f, &arg0->unk1C4);
            arg0->unkB0->unk6 = 0;
            arg0->unk2 = arg0->unkB0->unk6;
            uvDobjState(arg0->unk0, arg0->unk2);
            uvMat4Copy(&arg0->unkB0->unk80, &arg0->unk14);
        }
        uvMat4Copy(&arg0->unkB0->unk80, &arg0->unk14);
        temp_v0 = arg0->unkB0;
        D_80359AB0 = temp_v0->unk108.m[3][0];
        D_80359AB4 = temp_v0->unk108.m[3][1];
        D_80359AB8 = temp_v0->unk108.m[3][2];
        D_80359AC0 = arg0->unk14.m[3][0] + (arg0->unk12C * 100.0f);
        D_80359AC4 = arg0->unk14.m[3][1] + (arg0->unk130 * 100.0f);
        D_80359AC8 = arg0->unk14.m[3][2] + (arg0->unk134 * 100.0f);
        D_8034E9FC = 0.0f;
    }
    arg0->unkB4 = 5;
    func_802D5884((Unk802D3658_Arg0*)arg0->unkB0, arg0->unkB4);

    spB8 = D_8034E9FC * 0.5f;
    if (spB8 < 0.0f) {
        spB8 = 0.0f;
    } else if (spB8 > 0.99f) {
        spB8 = 0.99f;
    }
    D_8034E9FC += D_8034F854;
    uvMat4SetIdentity(&sp34);
    temp_fv0_2 = (1.0f - spB8);
    sp34.m[3][0] = (spB8 * D_80359AC0) + (temp_fv0_2 * D_80359AB0);
    sp34.m[3][1] = (spB8 * D_80359AC4) + (temp_fv0_2 * D_80359AB4);
    sp34.m[3][2] = (spB8 * D_80359AC8) + (temp_fv0_2 * D_80359AB8);
    uvMat4UnkOp6(&sp74, &arg0->unk14, &sp34);
    if (func_802D472C(arg0->unkB0, &sp34) != 0) {
        uvMat4UnkOp6(&sp74, &arg0->unk14, &sp34);
    }
    (void)func_802D4A30(arg0->unkB0, &sp74);
    uvMat4Copy(&arg0->unkB0->unk108, &sp74);
    func_80318294()->unk0 = 0;
    func_802D9220(arg0);
}
#endif

// cannonLoadPilot is invoked when loading cannonball level
void cannonLoadPilot(u8 pilot, Unk802D5B50_Arg2* arg1) {
    switch (pilot) {
    case PILOT_LARK:
        arg1->unk224 = -0.025f;
        arg1->unk228 = 0.097f;
        arg1->unk22C = 0.675f;
        arg1->unk234 = 0.0f;
        arg1->unk230 = 0.0f;
        arg1->unk238 = -0.745f;
        arg1->unk23C = -0.027f;
        arg1->unk240 = 0.442f;
        arg1->unk244 = 0.012f;
        arg1->unk248 = -0.024f;
        arg1->unk24C = -0.27f;
        arg1->unk250 = 0.101f;
        arg1->unk254 = -0.54f;
        arg1->unk258 = -0.156f;
        arg1->unk25C = 0.105f;
        arg1->unk260 = 0.486f;
        arg1->unk264 = -0.156f;
        arg1->unk268 = 0.105f;
        arg1->unk26C = -0.025f;
        arg1->unk270 = 0.307f;
        arg1->unk274 = 0.478f;
        arg1->unk278 = 0.96f;
        arg1->unk280 = 0.8f;
        arg1->unk27C = 5.88f;
        arg1->unk220 = 0x135;
        arg1->unk292 = 1;
        arg1->unk285 = 0xA;
        arg1->unk286 = 0xB;
        arg1->unk287 = 8;
        arg1->unk288 = 9;
        arg1->unk289 = 2;
        arg1->unk28A = 3;
        arg1->unk28B = 4;
        arg1->unk28C = 5;
        arg1->unk28D = 6;
        arg1->unk28E = 7;
        arg1->unk291 = 0xC;
        arg1->unk284 = 0x3E;
        break;
    case PILOT_GOOSE:
        arg1->unk224 = -0.001f;
        arg1->unk228 = 0.172f;
        arg1->unk22C = 0.782f;
        arg1->unk234 = 0.0f;
        arg1->unk230 = 0.0f;
        arg1->unk238 = -1.336f;
        arg1->unk23C = 0.001f;
        arg1->unk240 = 0.647f;
        arg1->unk244 = -0.002f;
        arg1->unk248 = -0.001f;
        arg1->unk24C = -0.341f;
        arg1->unk250 = 0.19f;
        arg1->unk254 = -0.722f;
        arg1->unk258 = -0.178f;
        arg1->unk25C = 0.148f;
        arg1->unk260 = 0.73f;
        arg1->unk264 = -0.178f;
        arg1->unk268 = 0.148f;
        arg1->unk26C = 0.0f;
        arg1->unk270 = 0.315f;
        arg1->unk274 = 0.603f;
        arg1->unk278 = 0.8f;
        arg1->unk280 = 1.0f;
        arg1->unk27C = 9.8f;
        arg1->unk220 = 0x136;
        arg1->unk292 = 6;
        arg1->unk285 = 2;
        arg1->unk286 = 3;
        arg1->unk287 = 4;
        arg1->unk288 = 5;
        arg1->unk289 = 0xA;
        arg1->unk28A = 0xB;
        arg1->unk28B = 0xC;
        arg1->unk28C = 7;
        arg1->unk28D = 8;
        arg1->unk28E = 9;
        arg1->unk291 = 1;
        arg1->unk284 = 0x3F;
        break;
    case PILOT_HAWK:
        arg1->unk224 = 0.003f;
        arg1->unk228 = 0.187f;
        arg1->unk22C = 0.634f;
        arg1->unk234 = 0.0f;
        arg1->unk230 = 0.0f;
        arg1->unk238 = -1.221f;
        arg1->unk23C = -0.01f;
        arg1->unk240 = 0.698f;
        arg1->unk244 = -0.013f;
        arg1->unk248 = -0.004f;
        arg1->unk24C = -0.43f;
        arg1->unk250 = -0.117f;
        arg1->unk254 = -0.819f;
        arg1->unk258 = -0.245f;
        arg1->unk25C = 0.069f;
        arg1->unk260 = 0.837f;
        arg1->unk264 = -0.245f;
        arg1->unk268 = 0.069f;
        arg1->unk26C = 0.002f;
        arg1->unk270 = 0.325f;
        arg1->unk274 = 0.52f;
        arg1->unk278 = 0.64f;
        arg1->unk280 = 1.2f;
        arg1->unk27C = 13.72f;
        arg1->unk220 = 0x137;
        arg1->unk292 = 6;
        arg1->unk285 = 1;
        arg1->unk286 = 2;
        arg1->unk287 = 3;
        arg1->unk288 = 4;
        arg1->unk289 = 0xA;
        arg1->unk28A = 0xB;
        arg1->unk28B = 0xC;
        arg1->unk28C = 7;
        arg1->unk28D = 8;
        arg1->unk28E = 9;
        arg1->unk291 = 5;
        arg1->unk284 = 0x40;
        break;
    case PILOT_KIWI:
        arg1->unk224 = 0.002f;
        arg1->unk228 = 0.084f;
        arg1->unk22C = 0.706f;
        arg1->unk234 = 0.0f;
        arg1->unk230 = 0.0f;
        arg1->unk238 = -0.828f;
        arg1->unk23C = 0.0f;
        arg1->unk240 = 0.426f;
        arg1->unk244 = 0.03f;
        arg1->unk248 = 0.0f;
        arg1->unk24C = -0.261f;
        arg1->unk250 = 0.107f;
        arg1->unk254 = -0.479f;
        arg1->unk258 = -0.153f;
        arg1->unk25C = 0.079f;
        arg1->unk260 = 0.489f;
        arg1->unk264 = -0.153f;
        arg1->unk268 = 0.079f;
        arg1->unk26C = 0.002f;
        arg1->unk270 = 0.308f;
        arg1->unk274 = 0.473f;
        arg1->unk278 = 0.96f;
        arg1->unk280 = 0.8f;
        arg1->unk27C = 5.88f;
        arg1->unk220 = 0x138;
        arg1->unk292 = 8;
        arg1->unk285 = 1;
        arg1->unk286 = 2;
        arg1->unk287 = 3;
        arg1->unk288 = 4;
        arg1->unk289 = 9;
        arg1->unk28A = 0xA;
        arg1->unk28B = 0xB;
        arg1->unk28C = 0xC;
        arg1->unk28D = 0xD;
        arg1->unk28E = 0xE;
        arg1->unk291 = 5;
        arg1->unk284 = 0x41;
        break;
    case PILOT_IBIS:
        arg1->unk224 = -0.002f;
        arg1->unk228 = 0.085f;
        arg1->unk22C = 0.799f;
        arg1->unk234 = 0.0f;
        arg1->unk230 = 0; // float, but needs other zero literal to match
        arg1->unk238 = -1.36f;
        arg1->unk23C = 0.0f;
        arg1->unk240 = 0.586f;
        arg1->unk244 = -0.034f;
        arg1->unk248 = 0.0f;
        arg1->unk24C = -0.314f;
        arg1->unk250 = 0.091f;
        arg1->unk254 = -0.666f;
        arg1->unk258 = -0.164f;
        arg1->unk25C = 0.141f;
        arg1->unk260 = 0.678f;
        arg1->unk264 = -0.164f;
        arg1->unk268 = 0.141f;
        arg1->unk26C = 0.0f;
        arg1->unk270 = 0.212f;
        arg1->unk274 = 0.599f;
        arg1->unk278 = 0.8f;
        arg1->unk280 = 1.0f;
        arg1->unk27C = 9.8f;
        arg1->unk220 = 0x139;
        arg1->unk292 = 6;
        arg1->unk285 = 2;
        arg1->unk286 = 3;
        arg1->unk287 = 4;
        arg1->unk288 = 5;
        arg1->unk289 = 0xA;
        arg1->unk28A = 0xB;
        arg1->unk28B = 0xC;
        arg1->unk28C = 7;
        arg1->unk28D = 8;
        arg1->unk28E = 9;
        arg1->unk291 = 1;
        arg1->unk284 = 0x42;
        break;
    case PILOT_ROBIN:
        arg1->unk224 = -0.001f;
        arg1->unk228 = 0.095f;
        arg1->unk22C = 0.844f;
        arg1->unk234 = 0.0f;
        arg1->unk230 = 0.0f;
        arg1->unk238 = -1.076f;
        arg1->unk23C = 0.0f;
        arg1->unk240 = 0.563f;
        arg1->unk244 = -0.018f;
        arg1->unk248 = 0.0f;
        arg1->unk24C = -0.433f;
        arg1->unk250 = 0.155f;
        arg1->unk254 = -0.737f;
        arg1->unk258 = -0.266f;
        arg1->unk25C = 0.112f;
        arg1->unk260 = 0.751f;
        arg1->unk264 = -0.266f;
        arg1->unk268 = 0.112f;
        arg1->unk26C = 0.0f;
        arg1->unk270 = 0.217f;
        arg1->unk274 = 0.621f;
        arg1->unk278 = 0.64f;
        arg1->unk280 = 1.2f;
        arg1->unk27C = 13.72f;
        arg1->unk220 = 0x13A;
        arg1->unk292 = 6;
        arg1->unk285 = 2;
        arg1->unk286 = 3;
        arg1->unk287 = 4;
        arg1->unk288 = 5;
        arg1->unk289 = 7;
        arg1->unk28A = 8;
        arg1->unk28B = 9;
        arg1->unk28C = 0xA;
        arg1->unk28D = 0xB;
        arg1->unk28E = 0xC;
        arg1->unk291 = 1;
        arg1->unk284 = 0x43;
        break;
    }
}

// cannonLoad802D77D8 is invoked when loading cannonball level
#pragma GLOBAL_ASM("asm/nonmatchings/app/cannonball/cannonLoad802D77D8.s")

// cannonFrame802D7B7C called every frame while aiming cannon and while in flight before landing
#pragma GLOBAL_ASM("asm/nonmatchings/app/cannonball/cannonFrame802D7B7C.s")

// cannonLandedFrame called every frame after landing from cannon shot
#pragma GLOBAL_ASM("asm/nonmatchings/app/cannonball/cannonLandedFrame.s")

// cannonEndShot called once after landing before the cannon is reset for next shot
#pragma GLOBAL_ASM("asm/nonmatchings/app/cannonball/cannonEndShot.s")

// cannonEndAllTgts called once after all four cannon targets are complete
#pragma GLOBAL_ASM("asm/nonmatchings/app/cannonball/cannonEndAllTgts.s")

void cannon_802D8A40(u8 arg0, Unk802D5C5C_Arg0* arg1) {
    u16* unkC;
    unkC = D_80362690->unk0[D_80362690->unk9C].unkC;
    if (unkC[1] == 3) {
        if (arg0 == 1) {
            uvDobjState(arg1->unk0, 0);
            uvDobjState(arg1->unk54, 0);
        } else {
            uvDobjState(arg1->unk0, arg1->unk2);
            uvDobjState(arg1->unk54, arg1->unk56);
        }
    }
}
