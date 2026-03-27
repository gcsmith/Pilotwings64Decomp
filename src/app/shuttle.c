#include "common.h"
#include "code_9A960.h"
#include "code_D1ED0.h"
#include "env_sound.h"
#include "game.h"
#include "hud.h"
#include "smoke.h"
#include "proxanim.h"
#include <uv_fx.h>
#include <uv_matrix.h>
#include <uv_model.h>
#include <uv_seq.h>
#include <uv_vector.h>

f32 pad_D_80350480[] = { 0.0f, 0.0f, 1.0f, 0.0f };
s32 D_80350490 = 0;
s32 D_80350494 = 0; // some state? values between 1 and 4
f32 D_80350498 = 0.0f;
f32 D_8035049C = 0.0f;
f32 D_803504A0 = 55.0f;
f64 D_803504A8 = 0.0;
s32 D_803504B0 = 0;
s32 D_803504B4 = 0xFFFF; // dobj id
s32 D_803504B8 = 0xFFFF;
s32 sShuttleRadarIdx = 0xFF;
s32 D_803504C0 = 0;
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
f32 D_80371D90;
f32 D_80371D94;
s32 D_80371D98;
s32 D_80371D9C;
f64 D_80371DA0;

// forward declarations
STATIC_FUNC void shuttle_80335130(void);

s32 shuttle_80334CC0(void) {
    return D_80350490;
}

STATIC_FUNC void shuttle_80334CCC(void) {
    Mtx4F sp80;
    Mtx4F sp40;

    shuttle_80335130();
    uvDobjState(D_803504B4, D_803504B0);
    if (D_80350494 == 2) {
        uvMat4SetIdentity(&sp80);
        uvMat4RotateAxis(&sp80, 3.1415923f, 'z');
        uvMat4LocalTranslate(&sp80, 0.0f, 0.0f, D_8035049C);
        uvMat4Mul(&D_80371D50, &sp80, &D_80371D10);
        uvDobjPosm(D_803504B4, 0, &D_80371D50);
        if (D_803504D0 != 0xFF) {
            uvFxProps(D_803504D0, FX_PROPS_3(40.0f, 40.0f, 40.0f), FX_END);
        }
        if (D_803504D4 != 0xFF) {
            uvFxProps(D_803504D4, FX_PROPS_3(40.0f, 40.0f, 40.0f), FX_END);
        }
        if (D_803504E4 != 0xFF) {
            uvFxProps(D_803504E4, FX_PROPS_3(15.0f, 1.0f, -25.0f), FX_END);
        }
        if (D_803504E0 != 0xFF) {
            uvFxProps(D_803504E0, FX_PROPS_3(15.0f, 1.0f, -25.0f), FX_END);
        }
        if (D_803504C4 >= 0) {
            smokeProps(D_803504C4, SMOKE_PROPS_2(D_803504A0), SMOKE_FX_END);
        }
    } else if (D_80350494 == 1) {
        D_8035049C = 0 /*.0f*/;
        D_80350498 = 0 /*.0f*/;
        uvMat4SetIdentity(&sp40);
        uvMat4RotateAxis(&sp40, 3.1415923f, 'z');
        uvMat4SetIdentity(&D_80371D10);
        uvMat4LocalTranslate(&D_80371D10, 2870.0f, -2230.0f, 57.51f);
        uvMat4Mul(&D_80371D50, &sp40, &D_80371D10);
        uvDobjPosm(D_803504B4, 0, &D_80371D50);
        if (D_803504C4 >= 0) {
            smokeProps(D_803504C4, SMOKE_PROPS_2(D_803504A0), SMOKE_FX_END);
        }
    }
    if (D_80350494 != 4) {
        uvMat4Copy(&sp40, &D_80371D50);
        uvMat4LocalTranslate(&sp40, -10.0f, 0.0f, -24.0f);
        uvMat4RotateAxis(&sp40, 1.5707961f, 'x');
        uvMat4RotateAxis(&sp40, 0.08726645f, 'y');
        if (D_803504D0 != 0xFF) {
            func_8021A4D8(D_803504D0, &sp40);
        }
        if (D_803504C8 >= 0) {
            smokeProps(D_803504C8, SMOKE_PROPS_6(sp40.m[3][0], sp40.m[3][1], sp40.m[3][2]), SMOKE_FX_END);
        }
        if (D_803504E4 != 0xFF) {
            func_8021A4D8(D_803504E4, &sp40);
        }
        uvMat4Copy(&sp40, &D_80371D50);
        uvMat4LocalTranslate(&sp40, 10.0f, 0.0f, -24.0f);
        uvMat4RotateAxis(&sp40, 1.5707961f, 'x');
        uvMat4RotateAxis(&sp40, 0.08726645f, 'y');
        if (D_803504D4 != 0xFF) {
            func_8021A4D8(D_803504D4, &sp40);
        }
        if (D_803504CC >= 0) {
            smokeProps(D_803504CC, SMOKE_PROPS_6(sp40.m[3][0], sp40.m[3][1], sp40.m[3][2]), SMOKE_FX_END);
        }
        if (D_803504E0 != 0xFF) {
            func_8021A4D8(D_803504E0, &sp40);
        }
    }
}

STATIC_FUNC void shuttle_80335130(void) {
    if (D_803504D0 == 0xFF) {
        D_803504D0 = func_8034B464(2);
    }

    if (D_803504D0 != 0xFF) {
        uvFxProps(D_803504D0, FX_PROPS_3(0.0f, 0.0f, 0.0f), FX_PROPS_5(1.0f, 0.925f, 0.709f, 0.75f), FX_PROPS_6(1.0f, 1.0f, 1.0f, 0.0f),
                  FX_PROPS_4(1.0f, 1.0f, 1.0f), FX_PROPS_1(1e+20), FX_END);
    }

    if (D_803504D4 == 0xFF) {
        D_803504D4 = func_8034B464(2);
    }

    if (D_803504D4 != 0xFF) {
        uvFxProps(D_803504D4, FX_PROPS_3(0.0f, 0.0f, 0.0f), FX_PROPS_5(1.0f, 0.925f, 0.709f, 0.75f), FX_PROPS_6(1.0f, 1.0f, 1.0f, 0.0f),
                  FX_PROPS_4(1.0f, 1.0f, 1.0f), FX_PROPS_1(1e+20), FX_END);
    }

    if (D_803504DC == 0xFF) {
        D_803504DC = func_80218F88();
        if (D_803504DC != 0xFF) {
            uvSeqModel(D_803504DC, 0);
            uvSeqProps(D_803504DC, SEQ_PROPS_4(60.0f), SEQ_PROPS_END);
            D_803504E4 = func_8034B464(6);
            if (D_803504E4 != 0xFF) {
                uvFxProps(D_803504E4, FX_PROPS_13(D_803504DC), FX_PROPS_1(1e+20), FX_PROPS_3(0.0f, 0.0f, 0.0f), FX_END);
            }
        }
    }

    if (D_803504D8 == 0xFF) {
        D_803504D8 = func_80218F88();
        if (D_803504D8 != 0xFF) {
            uvSeqModel(D_803504D8, 0);
            uvSeqProps(D_803504D8, SEQ_PROPS_4(60.0f), SEQ_PROPS_END);
            D_803504E0 = func_8034B464(6);
            if (D_803504E0 != 0xFF) {
                uvFxProps(D_803504E0, FX_PROPS_13(D_803504D8), FX_PROPS_1(1e+20), FX_PROPS_3(0.0f, 0.0f, 0.0f), FX_END);
            }
        }
    }

    if (D_803504C4 == -1) {
        D_803504C4 = smokeCreate();
    }

    if (D_803504C4 >= 0) {
        smokeProps(D_803504C4, SMOKE_PROPS_5(0.0f, 0.0f, 0.0f), SMOKE_PROPS_3(10.0f), SMOKE_PROPS_4(1000.0f), SMOKE_PROPS_2(0.0f),
                    SMOKE_PROPS_6(2870.0f, -2230.0f, 27.509998f), SMOKE_PROPS_7(0), SMOKE_FX_END);
    }

    if (D_803504C8 == -1) {
        D_803504C8 = smokeCreate();
    }

    if (D_803504C8 >= 0) {
        smokeProps(D_803504C8, SMOKE_PROPS_5(0.0f, 0.0f, -1.0f), SMOKE_PROPS_3(3.0f), SMOKE_PROPS_4(1000.0f), SMOKE_PROPS_9(80.0f, 80.0f, 160.0f), SMOKE_PROPS_7(1),
                    SMOKE_FX_END);
    }

    if (D_803504CC == -1) {
        D_803504CC = smokeCreate();
    }

    if (D_803504CC >= 0) {
        smokeProps(D_803504CC, SMOKE_PROPS_5(0.0f, 0.0f, -1.0f), SMOKE_PROPS_3(3.0f), SMOKE_PROPS_4(1000.0f), SMOKE_PROPS_9(80.0f, 80.0f, 160.0f), SMOKE_PROPS_7(1),
                    SMOKE_FX_END);
    }
}

STATIC_FUNC void shuttle_80335700(void) {
    if (D_803504E4 != 0xFF) {
        uvModelGet(D_803504E4, 0xFF);
        uvFxProps(D_803504E4, FX_PROPS_11(0), FX_END);
        D_803504E4 = 0xFF;
    }

    if (D_803504E0 != 0xFF) {
        uvModelGet(D_803504E0, 0xFF);
        uvFxProps(D_803504E0, FX_PROPS_11(0), FX_END);
        D_803504E0 = 0xFF;
    }

    if (D_803504DC != 0xFF) {
        uvSeqProps(D_803504DC, SEQ_PROPS_1(0), SEQ_PROPS_END);
        D_803504DC = 0xFF;
    }

    if (D_803504D8 != 0xFF) {
        uvSeqProps(D_803504D8, SEQ_PROPS_1(0), SEQ_PROPS_END);
        D_803504D8 = 0xFF;
    }

    if (D_803504D0 != 0xFF) {
        uvModelGet(D_803504D0, 0xFF);
        uvFxProps(D_803504D0, FX_PROPS_11(0), FX_END);
        D_803504D0 = 0xFF;
    }

    if (D_803504D4 != 0xFF) {
        uvModelGet(D_803504D4, 0xFF);
        uvFxProps(D_803504D4, FX_PROPS_11(0), FX_END);
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
    if (D_80350494 == 2) {
        D_80350498 += D_8034F854 * 0.5f;
        D_8035049C += D_80350498;
        if (D_803504A0 > 0.0f) {
            D_803504A0 -= 5.0f;
        } else {
            D_803504A0 = 0.0f;
        }
        if (D_8035049C > 2048.0f) {
            D_80350494 = 3;
            // @fake? should just assign 0 instead
            D_803504B0 *= 0;
            uvDobjState(D_803504B4, 0);
            D_803504A8 = 0.0;
        }
        shuttle_80334CCC();
    } else if (D_80350494 == 1) {
        D_803504A8 += D_8034F854;
        D_803504A0 += 5.0f;
        if (D_803504A8 > 7.0) {
            D_80350494 = 2;
        }
        shuttle_80334CCC();
    } else if (D_80350494 == 3) {
        D_803504A8 += D_8034F854;
        if ((12.0f * D_8034F854) < D_803504A8) {
            D_80350494 = 4;
            shuttle_80335700();
        }
        shuttle_80335130();
        uvDobjState(D_803504B4, D_803504B0);
    } else {
        shuttle_80335130();
        uvDobjState(D_803504B4, D_803504B0);
    }
}

STATIC_FUNC s32 shuttle_80335AE0(s32 arg0, s32 arg1, s32 arg2) {
    return 0;
}

STATIC_FUNC s32 shuttle_80335AF4(s32 arg0, s32 arg1, s32 arg2) {
    s32 pad;
    s32 sp18 = 0;

    shuttle_80335130();
    uvDobjState(D_803504B4, D_803504B0);
    if (func_80321420(arg0) > 750.0f && (D_80350494 == 4 || D_80350494 == 1)) {
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
    D_80350494 = 1;
    D_803504A8 = 0.0;
    D_803504A0 = 0.0f;
    D_8035049C = 0.0f;
    D_80350498 = 0.0f;
    D_803504B0 = 3;
}

void shuttle_80335BE4(void) {
    LevelESND sp88;
    u16 classIdx;
    u16 vehIdx;
    u16 testIdx;
    s32 shouldAddPhotoWaypoint;
    Vec3F sp70 = { 2870.0f, -2230.0f, 57.51f };
    Mtx4F sp30;

    D_803504B8 = uvDobjAllocIdx();
    if (D_803504B8 != 0xFFFF) {
        uvDobjModel(D_803504B8, MODEL_BIG_RED_SQUARE);
        uvDobjState(D_803504B8, 0x22);
        uvMat4SetIdentity(&sp30);
        uvMat4LocalTranslate(&sp30, 2870.0f, -2230.0f, 57.51f);
        uvDobjPosm(D_803504B8, 0, &sp30);
    }
    D_803504B4 = uvDobjAllocIdx();
    if (D_803504B4 == 0xFFFF) {
        return;
    }

    uvDobjModel(D_803504B4, MODEL_SPACE_SHUTTLE);
    uvDobjState(D_803504B4, D_803504B0);
    D_803504C0 = func_80321210(shuttle_80335AF4, shuttle_80335AE0, sp70, 750.0f, 0.0f, 1);
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
    shouldAddPhotoWaypoint = (testIdx == 0 && classIdx == CLASS_A && vehIdx == VEHICLE_HANG_GLIDER) ||
                             (testIdx == 1 && classIdx == CLASS_B && vehIdx == VEHICLE_HANG_GLIDER) ||
                             (testIdx == 2 && classIdx == CLASS_PILOT && vehIdx == VEHICLE_HANG_GLIDER);
    if (shouldAddPhotoWaypoint != 0) {
        sShuttleRadarIdx = hudAddWaypoint(D_80371D50.m[3][0], D_80371D50.m[3][1], D_80371D50.m[3][2]);
    } else {
        sShuttleRadarIdx = 0xFF;
    }
}

void shuttle_80335E44(void) {
    if (D_803504B8 != 0xFFFF) {
        uvDobjModel(D_803504B8, MODEL_WORLD);
        D_803504B8 = 0xFFFF;
    }

    if (D_803504B4 != 0xFFFF) {
        uvDobjModel(D_803504B4, MODEL_WORLD);
        D_803504B4 = 0xFFFF;
        shuttle_80335700();
        func_803212DC(D_803504C0);
        D_803504C0 = 0;
        if (sShuttleRadarIdx != 0xFF) {
            hud_8031A8E0(sShuttleRadarIdx);
        }
        sShuttleRadarIdx = 0xFF;
    }
}

f32 shuttle_80335EE4(void) {
    f32 var_fv1;

    var_fv1 = D_8035049C;
    if (var_fv1 > 512.0f) {
        var_fv1 = 512.0f;
    }
    return (var_fv1 * 0.5f) / 255.0f;
}

void shuttle_80335F24(Vec3F* arg0) {
    if (D_803504B4 == 0xFFFF) {
        arg0->f[0] = 2870.0f;
        arg0->f[1] = -2230.0f;
        arg0->f[2] = 57.51f;
    } else {
        arg0->f[0] = D_80371D50.m[3][0];
        arg0->f[1] = D_80371D50.m[3][1];
        arg0->f[2] = D_80371D50.m[3][2];
    }
}

s32 shuttle_80335F84(void) {
    Unk80362690_Unk0* temp = &D_80362690->unkC[D_80362690->unk9C];

    if (temp->unkA == 4 || temp->unkA == 5) {
        return 4;
    }

    return D_80350494;
}

void shuttle_80335FD8(f32 arg0) {
    if (D_803504B4 == 0xFFFF) {
        return;
    }

    shuttle_80335130();
    D_80350494 = 1;
    D_803504B0 = 3;
    D_803504A8 = 0.0;
    shuttle_80334CCC();
    D_80350494 = 2;
    D_8035049C = 2.0f * arg0 * 255.0f;
    shuttle_80334CCC();
}

void shuttle_80336064(void) {
    if (D_803504B4 != 0xFFFF) {
        shuttle_80335700();
    }
}

void shuttle_80336094(void) {
    D_80371D90 = D_8035049C;
    D_80371D98 = D_80350494;
    D_80371D94 = D_80350498;
    D_80371D9C = D_803504B0;
    D_80371DA0 = D_803504A8;
}

void shuttle_803360E8(void) {
    D_8035049C = D_80371D90;
    D_80350494 = D_80371D98;
    D_80350498 = D_80371D94;
    D_803504B0 = D_80371D9C;
    D_803504A8 = D_80371DA0;
}
