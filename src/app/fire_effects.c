#include "common.h"
#include "fire_effects.h"
#include "game.h"
#include <uv_seq.h>
#include <uv_model.h>
#include <uv_fx.h>

s32 D_8034F120 = 0xFFFFFFFF;

s32 D_80362500[8];
s32 D_80362520[64];
s32 D_80362620;
s32 D_80362624;

// forward declarations
void fx_create_fire(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);

void func_802E9FD0(void) {
    D_80362620 = 0;
    D_80362624 = 0;
}

void func_802E9FE4(void) {
    if (D_8034F120 != D_80362690->terraId) {
        func_802EA824();
        fx_create();
        D_8034F120 = D_80362690->terraId;
    }
}

void fx_create(void) {
    switch (D_80362690->terraId) {
    case 1:
        fx_create_fire(-1329.05f, 1232.9f, 6.0f, 5.0f, 5.0f);
        fx_create_fire(-837.0f, 715.2f, 280.57f, 2.0f, 2.0f);
        fx_create_fire(-770.56f, 736.44f, 264.73f, 2.0f, 2.0f);
        fx_create_fire(-733.55f, 767.73f, 251.62f, 2.0f, 2.0f);
        fx_create_fire(-724.08f, -692.91f, 288.29f, 2.0f, 2.0f);
        fx_create_fire(-713.94f, -674.26f, 288.08f, 2.0f, 2.0f);
        fx_create_fire(-733.11f, -661.0f, 290.84f, 2.0f, 2.0f);
        fx_create_fire(-746.82f, -672.43f, 292.02f, 2.0f, 2.0f);
        return;
    case 2:
        fx_create_fire(-837.0f, 715.2f, 280.57f, 2.0f, 2.0f);
        fx_create_fire(-770.56f, 736.44f, 264.73f, 2.0f, 2.0f);
        fx_create_fire(-733.55f, 767.73f, 251.62f, 2.0f, 2.0f);
        fx_create_fire(-642.13f, 746.5f, 242.78f, 2.0f, 2.0f);
        fx_create_fire(-617.17f, 772.03f, 239.67f, 2.0f, 2.0f);
        fx_create_fire(-628.55f, 873.54f, 236.18f, 2.0f, 2.0f);
        fx_create_fire(-610.74f, 865.28f, 256.96f, 2.0f, 2.0f);
        fx_create_fire(-598.96f, 857.81f, 257.23f, 2.0f, 2.0f);
        fx_create_fire(-580.66f, 844.82f, 215.96f, 2.0f, 2.0f);
        fx_create_fire(-638.68f, 930.47f, 225.59f, 2.0f, 2.0f);
        fx_create_fire(-622.2f, 960.48f, 221.53f, 2.0f, 2.0f);
        fx_create_fire(-591.5f, 960.13f, 218.54f, 2.0f, 2.0f);
        fx_create_fire(-575.53f, 930.53f, 217.59f, 2.0f, 2.0f);
        fx_create_fire(-582.33f, 888.75f, 216.78f, 2.0f, 2.0f);
        fx_create_fire(-297.95f, 942.72f, 115.58f, 2.0f, 2.0f);
        fx_create_fire(-320.42f, 938.52f, 114.73f, 2.0f, 2.0f);
        fx_create_fire(-286.23f, 855.1f, 76.46f, 2.0f, 2.0f);
        fx_create_fire(-299.11f, 846.29f, 77.05f, 2.0f, 2.0f);
        fx_create_fire(-295.22f, 839.95f, 76.8f, 2.0f, 2.0f);
        fx_create_fire(-281.23f, 848.97f, 76.37f, 2.0f, 2.0f);
        fx_create_fire(-234.07f, 785.09f, 73.3f, 2.0f, 2.0f);
        fx_create_fire(-223.94f, 803.74f, 73.08f, 2.0f, 2.0f);
        fx_create_fire(-243.11f, 817.0f, 75.84f, 2.0f, 2.0f);
        fx_create_fire(-256.82f, 805.57f, 77.02f, 2.0f, 2.0f);
        fx_create_fire(-504.93f, 872.51f, 215.89f, 4.0f, 4.0f);
        fx_create_fire(-500.84f, 912.06f, 214.71f, 4.0f, 4.0f);
        fx_create_fire(-478.91f, 971.75f, 214.64f, 4.0f, 4.0f);
        fx_create_fire(-440.64f, 1002.58f, 217.07f, 4.0f, 4.0f);
        fx_create_fire(-361.85f, 1012.32f, 215.73f, 4.0f, 4.0f);
        fx_create_fire(-313.42f, 983.83f, 215.65f, 4.0f, 4.0f);
        fx_create_fire(-294.02f, 943.14f, 217.08f, 4.0f, 4.0f);
        fx_create_fire(-294.24f, 903.16f, 217.11f, 4.0f, 4.0f);
        fx_create_fire(-332.27f, 865.19f, 213.61f, 4.0f, 4.0f);
        fx_create_fire(-370.13f, 856.82f, 214.84f, 4.0f, 4.0f);
        fx_create_fire(-413.83f, 850.75f, 214.1f, 4.0f, 4.0f);
        fx_create_fire(-448.45f, 802.51f, 213.5f, 4.0f, 4.0f);
        fx_create_fire(-496.0f, 797.84f, 213.02f, 4.0f, 4.0f);
        return;
    case 3:
        fx_create_fire(2960.13f, -1086.35f, 90.9f, 10.0f, 20.0f);
        fx_create_fire(3337.07f, -548.42f, 90.9f, 10.0f, 20.0f);
        fx_create_fire(1955.46f, -2033.42f, 90.9f, 10.0f, 20.0f);
        fx_create_fire(3305.1f, 744.0f, 81.0f, 4 /*.0f*/, 8.0f);
        return;
    case 7:
        fx_create_fire(-888.0f, -1935.05f, 90.9f, 10.0f, 20.0f);
        fx_create_fire(-871.63f, 1427.31f, 90.9f, 10.0f, 20.0f);
        return;
        break;
    case 8:
    case 9:
    case 0:
        break;
    default:
        _uvDebugPrintf("error : fx_create -> unknown terra %d\n", D_80362690->terraId);
        break;
    }
}

void func_802EA824(void) {
    s32 i;

    for (i = 0; i < D_80362620; i++) {
        uvFxProps(D_80362520[i], FX_PROP_11(0), FX_PROP_END);
    }

    if (D_80362624 > 0) {
        for (i = 0; i < 8; i++) {
            uvSeqProps(D_80362500[i], SEQ_PROP_1(0), SEQ_PROP_END);
        }
    }

    D_80362620 = 0;
    D_80362624 = 0;
}

void fx_create_fire(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    s32 i;

    if (D_80362624 == 0) {
        for (i = 0; i < ARRAY_COUNT(D_80362500); i++) {
            D_80362500[i] = func_80218F88();
            uvSeqModel(D_80362500[i], 0);
            // clang-format off
            uvSeqProps(
                D_80362500[i],
                SEQ_PROP_4(20.0f),
                SEQ_PROP_3(i * 2),
                SEQ_PROP_END
            );
            // clang-format on
        }
    }

    if (D_80362620 >= ARRAY_COUNT(D_80362520)) {
        _uvDebugPrintf("error : fx_create_fire -> out of fire effects\n");
        return;
    }

    D_80362520[D_80362620] = func_8021EFF0(6);
    uvModelGet(D_80362520[D_80362620], 6);

    // clang-format off
    uvFxProps(
        D_80362520[D_80362620],
        FX_PROP_10(arg0, arg1, arg2),
        FX_PROP_13(D_80362500[D_80362624 % ARRAY_COUNT(D_80362500)]),
        FX_PROP_1(1e+20),
        FX_PROP_16(1),
        FX_PROP_3(arg3, 1.0, arg4),
        FX_PROP_END
    );
    // clang-format on

    D_80362624++;
    D_80362620++;
}
