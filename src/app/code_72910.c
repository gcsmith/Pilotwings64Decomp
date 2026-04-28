#include "common.h"
#include <uv_audio.h>
#include <uv_dobj.h>
#include <uv_fx.h>
#include <uv_math.h>
#include "kernel/code_8170.h"
#include "app/environment.h"
#include "app/fire_effects.h"
#include "app/game.h"
#include "app/mist.h"
#include "app/smoke.h"
#include "app/snd.h"
#include "app/snow.h"
#include "app/splash.h"
#include "app/task.h"
#include "app/code_64730.h"

s16 D_8034F150 = 0;
s16 D_8034F154[6] = { 0 };

// forward declarations
s32 func_802EB640(Unk80362690_Unk0*, u16);

void func_802EB3E0(void) {
    fireFxInit();
    splashInit();
    smokeInit();
    mistInit();
    D_8034F150 = 0;
    D_80359DB4 = 0;
}

void func_802EB424(Mtx4F* arg0, f32 arg1) {
    u8* temp_s0;
    Unk80362690_Unk0* temp_s0_2;
    s32 sp44;
    f32 sp40;
    s32 sp3C;

    temp_s0 = taskGet_80345CB0();
    sp3C = 0;
    sp40 = 0.0f;
    fireFxUpdate();
    splashUpdate();
    mistUpdate(arg0, arg1);
    if (temp_s0[1] == 1) {
        snowUpdate();
    }
    temp_s0_2 = &D_80362690->unkC[D_80362690->unk9C];
    sp44 = func_8021A304(temp_s0_2->unk2C.m[3][0], temp_s0_2->unk2C.m[3][1], temp_s0_2->unk2C.m[3][2], 1);
    if (temp_s0_2->smokeId != -1) {
        smokeGetProps(temp_s0_2->smokeId, SMOKE_PROP_8(&sp3C), SMOKE_PROP_END);
    }
    if ((sp44 != 0xFF) && (sp3C == 0)) {
        sp3C = func_802EB640(temp_s0_2, sp44);
    }
    if (sp3C != 0) {
        if (temp_s0_2->veh == 0) {
            sp40 = -0.5f;
        }
        smokeProps(temp_s0_2->smokeId, SMOKE_PROP_6(arg0->m[3][0], arg0->m[3][1], (arg0->m[3][2] + sp40)), SMOKE_PROP_END);
    } else {
        temp_s0_2->smokeId = -1;
    }
    func_80336600();
}

void func_802EB598(void) {
    u8* sp1C;

    sp1C = taskGet_80345CB0();
    fireFxCreateAll();
    smokeCreateTerra();
    if (sp1C[1] == 1) {
        snowEnable();
    }
}

void func_802EB5E4(void) {
    u8* sp1C;

    sp1C = taskGet_80345CB0();
    fireFxDeinit();
    splashClear();
    smokeDeleteAll();
    mistDeinit();

    if (sp1C[1] == 1) {
        snowDisable();
    }
}

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
    u8 emitterId;
    u16 modelId;
    s32 sfxId;
    f32 pitch;

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

    if (arg0->smokeId == -1) {
        arg0->smokeId = smokeCreate();
        smokeProps(arg0->smokeId, 1, 0, 0, 0, 2, 3.0f, 3, 2.0f, 5, 0.0f, 0.0f, 0.5f, 4, 5.0f, 7, 1, 0);
        emitterId = uvEmitterLookup();
        sndGetPilotScream(&sfxId, &pitch);
        uvEmitterFromModel(emitterId, sfxId);
        uvEmitterSetVol(emitterId, 1.0f);
        uvEmitterSetPitch(emitterId, pitch);
        // clang-format off
        uvEmitterProps(emitterId,
            EMITTER_PROP_NEAR(0.0f),
            EMITTER_PROP_FAR(5000.0f),
            EMITTER_PROP_ATTR(EMITTER_ATTR_INIT | EMITTER_ATTR_ONESHOT),
            EMITTER_PROP_END
        );
        // clang-format on
        uvEmitterTrigger(emitterId);
        sndPlaySfx(0x5A);
        return 1;
    }
    return 0;
}

