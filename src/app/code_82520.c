#include "common.h"
#include <uv_texture.h>
#include "code_72B70.h"
#include "code_82520.h"
#include "app/task.h"
#include "app/hud.h"
#include "app/snd.h"
#include "app/code_9A960.h"

Unk80368B80 D_80368B80[5];

u8 D_8034F3A0 = 0;

void func_802FAF80(void) {
    s32 i;

    D_8034F3A0 = 0;

    for (i = 0; i < 5; i++) {
        D_80368B80[i].unk4 = 0xFFFF;
        D_80368B80[i].unk6 = 0;
        D_80368B80[i].unk7 = 0;
    }
}

void func_802FAFF0(void) {
    s32 i;

    for (i = 0; i < D_8034F3A0; i++) {
        if (D_80362690->unk0[D_80362690->unk9C].unkC.unk8 == D_80368B80[i].unk0->unk0) {
            D_80368B80[i].unk7 = 1;
            if (D_80368B80[i].unk4 != 0xFFFF) {
                uvDobjSetState(D_80368B80[i].unk4, 2);
            }
        } else {
            D_80368B80[i].unk7 = 0;
            if (D_80368B80[i].unk4 != 0xFFFF) {
                uvDobjClearState(D_80368B80[i].unk4, 2);
            }
        }
    }
}

void func_802FB0DC(Unk80368B80* arg0) {
    Mtx4F sp30;
    s32 var_a1;

    if (arg0->unk4 != 0xFFFF) {
        uvDobjModel(arg0->unk4, 0xFFFF);
    }
    arg0->unk4 = uvDobjAllocIdx();
    if (arg0->unk6 != 0) {
        var_a1 = 0xD1;
    } else {
        var_a1 = 0x109;
    }
    uvDobjModel(arg0->unk4, var_a1);
    uvMat4SetIdentity(&sp30);
    sp30.m[0][0] = arg0->unk0->scale;
    sp30.m[1][1] = arg0->unk0->scale;
    sp30.m[2][2] = arg0->unk0->height;
    sp30.m[3][0] = arg0->unk0->pos.x;
    sp30.m[3][1] = arg0->unk0->pos.y;
    sp30.m[3][2] = arg0->unk0->pos.z;
    uvDobjProps(arg0->unk4, 3, arg0->unk0->scale, 0);
    uvDobjState(arg0->unk4, 2);
    uvDobjPosm(arg0->unk4, 0, &sp30);
}

void func_802FB1D8(Unk80368B80* arg0) {
    Mtx4F sp18;

    uvDobjGetPosm(arg0->unk4, 0, &sp18);
    uvMat4RotateAxis(&sp18, 0.52359897f, 'z');
    uvDobjPosm(arg0->unk4, 0, &sp18);
}

void func_802FB22C(void) {
    s32 i;
    LevelHOPD* hopd;

    if (D_80362690->unkA0 != 0) {
        D_8034F3A0 = taskGetHOPD(&hopd);
        if (D_8034F3A0 > 5) {
            _uvDebugPrintf("hmgoal : too many hmgoal defined in level [%d]\n", D_8034F3A0);
            D_8034F3A0 = 0;
            return;
        }
        if (D_8034F3A0 != 0) {
            uvLevelAppend(0x19);

            for (i = 0; i < D_8034F3A0; i++) {
                if (D_80368B80[i].unk6 == 0) {
                    D_80368B80[i].unk0 = &hopd[i]; // <-+ this might be a bug:
                    func_802FB0DC(&D_80368B80[i]); //   | incrementing pointer
                } //                                    | *and* using index [i]
                hopd++; // -----------------------------+
            }
            func_802FAFF0();
        }
    }
}

s32 func_802FB308(JumbleHopperData* arg0) {
    s32 i;
    s32 sp38;
    f32 temp_fa1;

    sp38 = 0;
    if (D_80362690->unkA0 == 0) {
        return 0;
    }

    for (i = 0; i < D_8034F3A0; i++) {
        if (D_80368B80[i].unk6 != 0) {
            D_80368B80[i].unk10 += D_8034F854;
            if (D_80368B80[i].unk10 > 0.5) {
                D_80368B80[i].unk10 = 0.0;
                func_802FB1D8(&D_80368B80[i]);
            }
        }
    }
    if ((arg0->unk50 != 0) || (arg0->unk4C == 6)) {
        return 0;
    }

    for (i = 0; i < D_8034F3A0; i++) {
        if ((D_80368B80[i].unk4 != 0xFFFF) && (D_80368B80[i].unk7 != 0) && (D_80368B80[i].unk6 == 0)) {
            temp_fa1 = SQ(arg0->unkF4.x - D_80368B80[i].unk0->pos.x) + SQ(arg0->unkF4.y - D_80368B80[i].unk0->pos.y);
            if (SQ(D_80368B80[i].unk0->scale) > temp_fa1) {
                hudText_8031D8E0(0x15D, 1.5f, 8.0f);
                D_80368B80[i].unk6 = 1;
                D_80368B80[i].unk10 = 0.0;
                snd_play_sfx(0x11);
                func_8033F748(0x18);
                func_8033F964(0);
                uvDobjModel(D_80368B80[i].unk4, 0xFFFF);
                func_802FB0DC(&D_80368B80[i]);
                if (D_80368B80[i].unk0->unk10 == 1) {
                    sp38 = 1;
                }
                break;
            }
        }
    }
    return sp38;
}

void func_802FB518(void) {
    s32 i;

    for (i = 0; i < D_8034F3A0; i++) {
        if (D_80368B80[i].unk4 != 0xFFFF) {
            uvDobjModel(D_80368B80[i].unk4, 0xFFFF);
            D_80368B80[i].unk4 = 0xFFFF;
        }
        D_80368B80[i].unk6 = 0;
    }
}

u8 func_802FB5A0(void) {
    s32 i;
    u8 ret;

    ret = 0;
    for (i = 0; i < D_8034F3A0; i++) {
        ret += (D_80368B80[i].unk6 != 0) ? 1 : 0;
    }
    return ret;
}

s16 func_802FB5FC(void) {
    s32 i;
    s32 ret;

    ret = 0;
    for (i = 0; i < D_8034F3A0; i++) {
        ret += (D_80368B80[i].unk6 != 0) ? D_80368B80[i].unk8 : 0;
    }
    return ret;
}
