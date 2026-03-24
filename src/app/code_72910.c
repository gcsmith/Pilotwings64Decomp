#include "common.h"
#include <uv_audio.h>
#include <uv_dobj.h>
#include <uv_fx.h>
#include <uv_math.h>
#include "kernel/code_8170.h"
#include "app/fire_effects.h"
#include "app/game.h"
#include "app/smoke.h"
#include "app/snd.h"
#include "app/splash.h"
#include "app/code_9B960.h"

extern s16 D_8034EE30[VEHICLE_COUNT][PILOT_COUNT];
extern u8 D_80359DB4;

s16 D_8034F150 = 0;
s16 D_8034F154[6] = { 0 };

void func_802EB3E0(void) {
    func_802E9FD0();
    func_80341CB0();
    func_803365A0();
    func_80314430();
    D_8034F150 = 0;
    D_80359DB4 = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_72910/func_802EB424.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_72910/func_802EB598.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_72910/func_802EB5E4.s")

s32 func_802EB640(Unk80362690_Unk0* arg0, u16 arg1) {
    GyrocopterData* temp_v0;
    f32 spC8;
    f32 spC4;
    f32 spC0;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 temp_fa1;
    f32 spB0;
    f32 spAC;
    f32 spA8;
    f32 var_fv0;
    f32 spA0;
    f64 temp_fv0_2;
    u8 temp_s0;
    u16 modelId;
    s32 sp90;
    f32 sp8C;

    uvFxGetProps(arg1, 10, &spC8, &spC4, &spC0, 3, &spB0, &spAC, &spA8, 0);
    if (spAC < spB0) {
        var_fv0 = spB0;
    } else {
        var_fv0 = spAC;
    }
    if (var_fv0 < spA8) {
        spA0 = spA8;
    } else {
        spA0 = var_fv0;
    }
    temp_fv0 = spC8 - arg0->unk2C.m[3][0];
    temp_fv1 = spC4 - arg0->unk2C.m[3][1];
    temp_fa1 = (spC0 - arg0->unk2C.m[3][2]) + spA0 * 0.5;
    if (spA0 * 0.5 < uvSqrtF(SQ(temp_fv0) + SQ(temp_fv1) + SQ(temp_fa1))) {
        // FAKE
        if (spA0) { }
        return 0;
    }
    if (D_8034F150 == 0) {
        modelId = D_8034EE30[arg0->veh][arg0->pilot];
        uvDbColorModel(modelId, 0.0f, 0.0f, 0.0f, 0.5f);
        if (arg0->veh == VEHICLE_GYROCOPTER) {
            temp_v0 = arg0->vehicleData;
            temp_v0->unk578 *= 0.2;
            temp_v0->unk57C *= 0.2;
            temp_v0->unk580 *= 0.2;
            temp_v0->unk584 *= 0.2;
            temp_v0->unk588 *= 0.2;
            temp_v0->unk58C *= 0.2;
        }
        D_8034F150 = 1;
    }

    if (arg0->unk88 == -1) {
        arg0->unk88 = smoke_create();
        smoke_props(arg0->unk88, 1, 0, 0, 0, 2, 3.0f, 3, 2.0f, 5, 0.0f, 0.0f, 0.5f, 4, 5.0f, 7, 1, 0);
        temp_s0 = uvEmitterLookup();
        snd_getpilot(&sp90, &sp8C);
        uvEmitterFromModel(temp_s0, sp90);
        uvEmitterSetUnk70(temp_s0, 1.0f);
        uvEmitterSetUnk74(temp_s0, sp8C);
        uvEmitterProp(temp_s0, 1, 0.0f, 2, 5000.0f, 5, 0x30, 0);
        uvEmitterTrigger(temp_s0);
        snd_play_sfx(0x5A);
        return 1;
    }
    return 0;
}
