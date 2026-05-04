#include "common.h"
#include "game.h"
#include "code_9A960.h"
#include "code_D1ED0.h"
#include "env_sound.h"
#include "game.h"
#include "hud.h"
#include "smoke.h"
#include "shuttle.h"
#include "proxanim.h"
#include <uv_fx.h>
#include <uv_matrix.h>
#include <uv_model.h>
#include <uv_vector.h>

f32 pad_D_80350480[] = { 0.0f, 0.0f, 1.0f, 0.0f };
s32 D_80350490 = 0;
s32 sShuttleState = SHUTTLE_STATE_0;
f32 sShuttleThrust = 0.0f;
f32 sShuttleAltitude = 0.0f;
f32 D_803504A0 = 55.0f;
f64 sShuttleFlightTime = 0.0;
s32 sShuttleObjState = 0;
s32 sShuttleObjId = 0xFFFF;
s32 sShuttleObjId2 = 0xFFFF;
s32 sShuttleRadarIdx = 0xFF;
s32 sShuttleProxId = 0;
s16 D_803504C4 = 0xFFFF;
s16 D_803504C8 = 0xFFFF;
s16 D_803504CC = 0xFFFF;
s32 D_803504D0 = 0xFF;
s32 D_803504D4 = 0xFF;
s32 D_803504D8 = 0xFF;
s32 D_803504DC = 0xFF;
s32 D_803504E0 = 0xFF;
s32 D_803504E4 = 0xFF;

Mtx4F D_80371D10;
Mtx4F D_80371D50;
f32 sShuttleAltitudeCopy;
f32 sShuttleThrustCopy;
s32 sShuttleStateCopy;
s32 sShuttleObjStateCopy;
f64 sShuttleFlightTimeCopy;

// forward declarations
STATIC_FUNC void shuttle_80335130(void);

s32 shuttle_80334CC0(void) {
    return D_80350490;
}

STATIC_FUNC void shuttle_80334CCC(void) {
    Mtx4F sp80;
    Mtx4F sp40;

    shuttle_80335130();
    uvDobjState(sShuttleObjId, sShuttleObjState);
    if (sShuttleState == SHUTTLE_STATE_2) {
        uvMat4SetIdentity(&sp80);
        uvMat4RotateAxis(&sp80, 3.1415923f, 'z');
        uvMat4LocalTranslate(&sp80, 0.0f, 0.0f, sShuttleAltitude);
        uvMat4Mul(&D_80371D50, &sp80, &D_80371D10);
        uvDobjPosm(sShuttleObjId, 0, &D_80371D50);
        if (D_803504D0 != 0xFF) {
            uvFxProps(D_803504D0, FX_PROP_3(40.0f, 40.0f, 40.0f), FX_PROP_END);
        }
        if (D_803504D4 != 0xFF) {
            uvFxProps(D_803504D4, FX_PROP_3(40.0f, 40.0f, 40.0f), FX_PROP_END);
        }
        if (D_803504E4 != 0xFF) {
            uvFxProps(D_803504E4, FX_PROP_3(15.0f, 1.0f, -25.0f), FX_PROP_END);
        }
        if (D_803504E0 != 0xFF) {
            uvFxProps(D_803504E0, FX_PROP_3(15.0f, 1.0f, -25.0f), FX_PROP_END);
        }
        if (D_803504C4 >= 0) {
            smokeProps(D_803504C4, SMOKE_PROP_2(D_803504A0), SMOKE_PROP_END);
        }
    } else if (sShuttleState == SHUTTLE_STATE_1) {
        sShuttleAltitude = 0 /*.0f*/;
        sShuttleThrust = 0 /*.0f*/;
        uvMat4SetIdentity(&sp40);
        uvMat4RotateAxis(&sp40, 3.1415923f, 'z');
        uvMat4SetIdentity(&D_80371D10);
        uvMat4LocalTranslate(&D_80371D10, 2870.0f, -2230.0f, 57.51f);
        uvMat4Mul(&D_80371D50, &sp40, &D_80371D10);
        uvDobjPosm(sShuttleObjId, 0, &D_80371D50);
        if (D_803504C4 >= 0) {
            smokeProps(D_803504C4, SMOKE_PROP_2(D_803504A0), SMOKE_PROP_END);
        }
    }
    if (sShuttleState != SHUTTLE_STATE_4) {
        uvMat4Copy(&sp40, &D_80371D50);
        uvMat4LocalTranslate(&sp40, -10.0f, 0.0f, -24.0f);
        uvMat4RotateAxis(&sp40, 1.5707961f, 'x');
        uvMat4RotateAxis(&sp40, 0.08726645f, 'y');
        if (D_803504D0 != 0xFF) {
            uvFx_8021A4D8(D_803504D0, &sp40);
        }
        if (D_803504C8 >= 0) {
            smokeProps(D_803504C8, SMOKE_PROP_6(sp40.m[3][0], sp40.m[3][1], sp40.m[3][2]), SMOKE_PROP_END);
        }
        if (D_803504E4 != 0xFF) {
            uvFx_8021A4D8(D_803504E4, &sp40);
        }
        uvMat4Copy(&sp40, &D_80371D50);
        uvMat4LocalTranslate(&sp40, 10.0f, 0.0f, -24.0f);
        uvMat4RotateAxis(&sp40, 1.5707961f, 'x');
        uvMat4RotateAxis(&sp40, 0.08726645f, 'y');
        if (D_803504D4 != 0xFF) {
            uvFx_8021A4D8(D_803504D4, &sp40);
        }
        if (D_803504CC >= 0) {
            smokeProps(D_803504CC, SMOKE_PROP_6(sp40.m[3][0], sp40.m[3][1], sp40.m[3][2]), SMOKE_PROP_END);
        }
        if (D_803504E0 != 0xFF) {
            uvFx_8021A4D8(D_803504E0, &sp40);
        }
    }
}

STATIC_FUNC void shuttle_80335130(void) {
    if (D_803504D0 == 0xFF) {
        D_803504D0 = func_8034B464(2);
    }

    if (D_803504D0 != 0xFF) {
        // clang-format off
        uvFxProps(
            D_803504D0,
            FX_PROP_3(0.0f, 0.0f, 0.0f),
            FX_PROP_5(1.0f, 0.925f, 0.709f, 0.75f),
            FX_PROP_6(1.0f, 1.0f, 1.0f, 0.0f),
            FX_PROP_4(1.0f, 1.0f, 1.0f),
            FX_PROP_1(1e+20),
            FX_PROP_END
        );
        // clang-format on
    }

    if (D_803504D4 == 0xFF) {
        D_803504D4 = func_8034B464(2);
    }

    if (D_803504D4 != 0xFF) {
        // clang-format off
        uvFxProps(
            D_803504D4,
            FX_PROP_3(0.0f, 0.0f, 0.0f),
            FX_PROP_5(1.0f, 0.925f, 0.709f, 0.75f),
            FX_PROP_6(1.0f, 1.0f, 1.0f, 0.0f),
            FX_PROP_4(1.0f, 1.0f, 1.0f),
            FX_PROP_1(1e+20),
            FX_PROP_END
        );
        // clang-format on
    }

    if (D_803504DC == 0xFF) {
        D_803504DC = uvSeqFindFree();
        if (D_803504DC != 0xFF) {
            uvSeqModel(D_803504DC, 0);
            uvSeqProps(D_803504DC, SEQ_PROP_FRAMERATE(60.0f), SEQ_PROP_END);
            D_803504E4 = func_8034B464(6);
            if (D_803504E4 != 0xFF) {
                // clang-format off
                uvFxProps(
                    D_803504E4,
                    FX_PROP_13(D_803504DC),
                    FX_PROP_1(1e+20),
                    FX_PROP_3(0.0f, 0.0f, 0.0f),
                    FX_PROP_END
                );
                // clang-format on
            }
        }
    }

    if (D_803504D8 == 0xFF) {
        D_803504D8 = uvSeqFindFree();
        if (D_803504D8 != 0xFF) {
            uvSeqModel(D_803504D8, 0);
            uvSeqProps(D_803504D8, SEQ_PROP_FRAMERATE(60.0f), SEQ_PROP_END);
            D_803504E0 = func_8034B464(6);
            if (D_803504E0 != 0xFF) {
                // clang-format off
                uvFxProps(
                    D_803504E0,
                    FX_PROP_13(D_803504D8),
                    FX_PROP_1(1e+20),
                    FX_PROP_3(0.0f, 0.0f, 0.0f),
                    FX_PROP_END
                );
                // clang-format on
            }
        }
    }

    if (D_803504C4 == -1) {
        D_803504C4 = smokeCreate();
    }

    if (D_803504C4 >= 0) {
        // clang-format off
        smokeProps(
            D_803504C4,
            SMOKE_PROP_5(0.0f, 0.0f, 0.0f),
            SMOKE_PROP_3(10.0f),
            SMOKE_PROP_4(1000.0f),
            SMOKE_PROP_2(0.0f),
            SMOKE_PROP_6(2870.0f, -2230.0f, 27.509998f),
            SMOKE_PROP_7(0),
            SMOKE_PROP_END
        );
        // clang-format on
    }

    if (D_803504C8 == -1) {
        D_803504C8 = smokeCreate();
    }

    if (D_803504C8 >= 0) {
        // clang-format off
        smokeProps(
            D_803504C8,
            SMOKE_PROP_5(0.0f, 0.0f, -1.0f),
            SMOKE_PROP_3(3.0f),
            SMOKE_PROP_4(1000.0f),
            SMOKE_PROP_9(80.0f, 80.0f, 160.0f),
            SMOKE_PROP_7(1),
            SMOKE_PROP_END
        );
        // clang-format on
    }

    if (D_803504CC == -1) {
        D_803504CC = smokeCreate();
    }

    if (D_803504CC >= 0) {
        // clang-format off
        smokeProps(
            D_803504CC,
            SMOKE_PROP_5(0.0f, 0.0f, -1.0f),
            SMOKE_PROP_3(3.0f),
            SMOKE_PROP_4(1000.0f),
            SMOKE_PROP_9(80.0f, 80.0f, 160.0f),
            SMOKE_PROP_7(1),
            SMOKE_PROP_END
        );
        // clang-format on
    }
}

STATIC_FUNC void shuttle_80335700(void) {
    if (D_803504E4 != 0xFF) {
        uvModelGet(D_803504E4, 0xFF);
        uvFxProps(D_803504E4, FX_PROP_11(0), FX_PROP_END);
        D_803504E4 = 0xFF;
    }

    if (D_803504E0 != 0xFF) {
        uvModelGet(D_803504E0, 0xFF);
        uvFxProps(D_803504E0, FX_PROP_11(0), FX_PROP_END);
        D_803504E0 = 0xFF;
    }

    if (D_803504DC != 0xFF) {
        uvSeqProps(D_803504DC, SEQ_PROP_ACTIVE(0), SEQ_PROP_END);
        D_803504DC = 0xFF;
    }

    if (D_803504D8 != 0xFF) {
        uvSeqProps(D_803504D8, SEQ_PROP_ACTIVE(0), SEQ_PROP_END);
        D_803504D8 = 0xFF;
    }

    if (D_803504D0 != 0xFF) {
        uvModelGet(D_803504D0, 0xFF);
        uvFxProps(D_803504D0, FX_PROP_11(0), FX_PROP_END);
        D_803504D0 = 0xFF;
    }

    if (D_803504D4 != 0xFF) {
        uvModelGet(D_803504D4, 0xFF);
        uvFxProps(D_803504D4, FX_PROP_11(0), FX_PROP_END);
        D_803504D4 = 0xFF;
    }

    if (D_803504C4 >= 0) {
        smokeProps(D_803504C4, 8, 0, 0);
        D_803504C4 = -1;
    }

    if (D_803504C8 >= 0) {
        smokeProps(D_803504C8, 8, 0, 0);
        D_803504C8 = -1;
    }

    if (D_803504CC >= 0) {
        smokeProps(D_803504CC, 8, 0, 0);
        D_803504CC = -1;
    }
}

STATIC_FUNC void shuttle_803358D4(void) {
    if (sShuttleState == SHUTTLE_STATE_2) {
        sShuttleThrust += D_8034F854 * 0.5f;
        sShuttleAltitude += sShuttleThrust;
        if (D_803504A0 > 0.0f) {
            D_803504A0 -= 5.0f;
        } else {
            D_803504A0 = 0.0f;
        }
        if (sShuttleAltitude > 2048.0f) {
            sShuttleState = SHUTTLE_STATE_3;
            // @fake? should just assign 0 instead
            sShuttleObjState *= 0;
            uvDobjState(sShuttleObjId, 0);
            sShuttleFlightTime = 0.0;
        }
        shuttle_80334CCC();
    } else if (sShuttleState == SHUTTLE_STATE_1) {
        sShuttleFlightTime += D_8034F854;
        D_803504A0 += 5.0f;
        if (sShuttleFlightTime > 7.0) {
            sShuttleState = SHUTTLE_STATE_2;
        }
        shuttle_80334CCC();
    } else if (sShuttleState == SHUTTLE_STATE_3) {
        sShuttleFlightTime += D_8034F854;
        if ((12.0f * D_8034F854) < sShuttleFlightTime) {
            sShuttleState = SHUTTLE_STATE_4;
            shuttle_80335700();
        }
        shuttle_80335130();
        uvDobjState(sShuttleObjId, sShuttleObjState);
    } else {
        shuttle_80335130();
        uvDobjState(sShuttleObjId, sShuttleObjState);
    }
}

STATIC_FUNC s32 shuttleProxEventCb(UNUSED s32 proxId, UNUSED s32 eventType, UNUSED s32 clientData) {
    return 0;
}

STATIC_FUNC s32 shuttleProxAnimCb(s32 proxId, UNUSED f32 timeout, UNUSED s32 clientData) {
    s32 pad;
    s32 sp18 = 0;

    shuttle_80335130();
    uvDobjState(sShuttleObjId, sShuttleObjState);
    if (proxAnimGetRange(proxId) > 750.0f && (sShuttleState == SHUTTLE_STATE_4 || sShuttleState == SHUTTLE_STATE_1)) {
        D_80350490 = 0;
        sp18 = 2;
    } else {
        D_80350490 = 1;
        shuttle_803358D4();
    }
    return sp18;
}

void shuttleInit(void) {
    D_80350490 = 0;
    sShuttleState = SHUTTLE_STATE_1;
    sShuttleFlightTime = 0.0;
    D_803504A0 = 0.0f;
    sShuttleAltitude = 0.0f;
    sShuttleThrust = 0.0f;
    sShuttleObjState = 3;
}

void shuttleLoad(void) {
    LevelESND sp88;
    u16 classIdx;
    u16 vehIdx;
    u16 testIdx;
    s32 showHudWaypoint;
    Vec3F sp70 = { 2870.0f, -2230.0f, 57.51f };
    Mtx4F sp30;

    sShuttleObjId2 = uvDobjAllocIdx();
    if (sShuttleObjId2 != 0xFFFF) {
        uvDobjModel(sShuttleObjId2, MODEL_BIG_RED_SQUARE);
        uvDobjState(sShuttleObjId2, 0x22);
        uvMat4SetIdentity(&sp30);
        uvMat4LocalTranslate(&sp30, 2870.0f, -2230.0f, 57.51f);
        uvDobjPosm(sShuttleObjId2, 0, &sp30);
    }
    sShuttleObjId = uvDobjAllocIdx();
    if (sShuttleObjId == 0xFFFF) {
        return;
    }

    uvDobjModel(sShuttleObjId, MODEL_SPACE_SHUTTLE);
    uvDobjState(sShuttleObjId, sShuttleObjState);
    sShuttleProxId = proxAnimAddCallback(shuttleProxAnimCb, shuttleProxEventCb, sp70, 750.0f, 0.0f, 1);
    shuttle_80334CCC();
    uvMat4SetIdentity(&sp88.unk0);
    sp88.sndId = 0x14;
    sp88.unk64 = 0;
    sp88.unk74 = 8;
    sp88.unk70 = 0;
    sp88.unk5C = 1.0f;
    sp88.unk60 = 1.0f;
    sp88.unk0.m[3][0] = 2870.0f;
    sp88.unk0.m[3][1] = -2230.0f;
    sp88.unk0.m[3][2] = 57.51f;
    sp88.unk68 = 500.0f;
    sp88.unk6C = 1500.0f;
    envSoundLoad(&sp88);
    taskGetClsVehTest(&classIdx, &vehIdx, &testIdx);
    showHudWaypoint = (testIdx == 0 && classIdx == CLASS_A && vehIdx == VEHICLE_HANG_GLIDER) ||
                      (testIdx == 1 && classIdx == CLASS_B && vehIdx == VEHICLE_HANG_GLIDER) ||
                      (testIdx == 2 && classIdx == CLASS_PILOT && vehIdx == VEHICLE_HANG_GLIDER);
    if (showHudWaypoint != 0) {
        sShuttleRadarIdx = hudAddWaypoint(D_80371D50.m[3][0], D_80371D50.m[3][1], D_80371D50.m[3][2]);
    } else {
        sShuttleRadarIdx = 0xFF;
    }
}

void shuttleDeinit(void) {
    if (sShuttleObjId2 != 0xFFFF) {
        uvDobjModel(sShuttleObjId2, MODEL_WORLD);
        sShuttleObjId2 = 0xFFFF;
    }

    if (sShuttleObjId != 0xFFFF) {
        uvDobjModel(sShuttleObjId, MODEL_WORLD);
        sShuttleObjId = 0xFFFF;
        shuttle_80335700();
        proxAnimDeleteCallback(sShuttleProxId);
        sShuttleProxId = 0;
        if (sShuttleRadarIdx != 0xFF) {
            hud_8031A8E0(sShuttleRadarIdx);
        }
        sShuttleRadarIdx = 0xFF;
    }
}

f32 shuttle_80335EE4(void) {
    f32 var_fv1;

    var_fv1 = sShuttleAltitude;
    if (var_fv1 > 512.0f) {
        var_fv1 = 512.0f;
    }
    return (var_fv1 * 0.5f) / 255.0f;
}

void shuttle_80335F24(Vec3F* arg0) {
    if (sShuttleObjId == 0xFFFF) {
        arg0->f[0] = 2870.0f;
        arg0->f[1] = -2230.0f;
        arg0->f[2] = 57.51f;
    } else {
        arg0->f[0] = D_80371D50.m[3][0];
        arg0->f[1] = D_80371D50.m[3][1];
        arg0->f[2] = D_80371D50.m[3][2];
    }
}

s32 shuttleGetState(void) {
    Unk80362690_Unk0* temp = &D_80362690->unkC[D_80362690->unk9C];

    if (temp->unkA == 4 || temp->unkA == 5) {
        return SHUTTLE_STATE_4;
    }

    return sShuttleState;
}

void shuttle_80335FD8(f32 arg0) {
    if (sShuttleObjId == 0xFFFF) {
        return;
    }

    shuttle_80335130();
    sShuttleState = SHUTTLE_STATE_1;
    sShuttleObjState = 3;
    sShuttleFlightTime = 0.0;
    shuttle_80334CCC();
    sShuttleState = SHUTTLE_STATE_2;
    sShuttleAltitude = 2.0f * arg0 * 255.0f;
    shuttle_80334CCC();
}

void shuttle_80336064(void) {
    if (sShuttleObjId != 0xFFFF) {
        shuttle_80335700();
    }
}

void shuttleStateSave(void) {
    sShuttleAltitudeCopy = sShuttleAltitude;
    sShuttleStateCopy = sShuttleState;
    sShuttleThrustCopy = sShuttleThrust;
    sShuttleObjStateCopy = sShuttleObjState;
    sShuttleFlightTimeCopy = sShuttleFlightTime;
}

void shuttleStateRestore(void) {
    sShuttleAltitude = sShuttleAltitudeCopy;
    sShuttleState = sShuttleStateCopy;
    sShuttleThrust = sShuttleThrustCopy;
    sShuttleObjState = sShuttleObjStateCopy;
    sShuttleFlightTime = sShuttleFlightTimeCopy;
}
