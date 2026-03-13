#include "common.h"
#include "jumble_hopper.h"
#include <uv_memory.h>
#include <uv_model.h>
#include "app/hud.h"
#include "app/demo.h"
#include "app/fdr.h"
#include "app/shadow.h"
#include "app/snd.h"
#include "app/task.h"
#include "app/code_5A6A0.h"
#include "app/code_9A960.h"
#include "app/code_D1ED0.h"

extern Unk803599D0 D_80368B20;

void func_802FA7A0(u8 arg0, JumbleHopperData* arg1);

void func_802F9F60(void) {
    D_80368B20.unk0 = 8;
    D_80368B20.unk4 = 0.0f;
    D_80368B20.unk8 = 0.0f;
    D_80368B20.unkC = 0.2f;
    D_80368B20.unk10 = 0.04f;
    D_80368B20.unk14 = 0.4f;
    D_80368B20.unk18 = 0.16f;
    D_80368B20.unk1C = 0.6f;
    D_80368B20.unk20 = 0.36f;
    D_80368B20.unk24 = 0.7f;
    D_80368B20.unk28 = 0.49f;
    D_80368B20.unk2C = 0.8f;
    D_80368B20.unk30 = 0.64f;
    D_80368B20.unk34 = 0.9f;
    D_80368B20.unk38 = 0.81f;
    D_80368B20.unk40 = 1.0f;
    D_80368B20.unk3C = 1.0f;
}

void func_802FA020(u8 arg0, u8 arg1, JumbleHopperData* arg2, Unk802D3658_Arg0* arg3) {
    uvMemSet(arg2, 0, sizeof(JumbleHopperData));
    func_802FA7A0(arg1, arg2);
    arg2->objId = uvDobjAllocIdx();
    arg2->unk2 = 2;
    uvDobjModel(arg2->objId, arg2->modelId);
    uvDobjPosm(arg2->objId, 0, &arg2->unk74);
    uvDobjState(arg2->objId, arg2->unk2);
    func_80334454(0xFFFF, 0x151);
    func_803342F0(0.0f);
    func_803342FC(0.0f);
    arg2->unkC = arg0;
    arg2->unk18 = arg3;
    arg2->unk65E[0] = 0;
    arg2->unk4 = 0xFFFF;
    arg2->unk664 = 0.0f;
    arg2->unk66C = 0.0f;
    arg2->unk668 = 0.0f;
    arg2->unk3C = 0.0f;
    arg2->unk40 = 0.0f;
    func_802FD038(arg2);
}

void jumbleHopperEnterLeave(JumbleHopperData* arg0) {
    func_802FD114(arg0);
    arg0->unk4C = 0;
    arg0->unk2 = 2;
    arg0->unk534 = 0;
    arg0->unk538 = 0;
    arg0->unk3C = 0.0f;
    arg0->unk40 = 0.0f;
    arg0->unk8 = 0.0f;
    arg0->unk48 = 0.7f;
    arg0->unk44 = 9;
    arg0->unk18->unk108.m[3][2] = 0.0f;
    arg0->unk18->unk1380 = 0.0f;
    arg0->unk18->unk1374 = 5.0f;
    arg0->unk18->unk137C = 0;
    arg0->unk18->unk1 = arg0->unk44;
    arg0->unk18->unk4 = arg0->objId;
    arg0->unk18->unk6 = arg0->unk2;
    arg0->unk18->unk0 = 0x68;
    arg0->unk18->unk1B4 = 6.0f;
    uvModelGetProps(arg0->modelId, 1, &arg0->unk18->unk8, 0);
    arg0->unk18->unk68.x = arg0->unk630.x;
    arg0->unk18->unk68.y = arg0->unk630.y;
    arg0->unk18->unk68.z = arg0->unk630.z;
    arg0->unk18->unk74 = 0.0f;
    arg0->unk18->unk5C = 0;
    arg0->unk18->unk60 = -5.0f;
    arg0->unk18->unk64 = 0;
    arg0->unk18->unk54 = 2.0f;
    arg0->unk18->unk58 = 6.0f;
    arg0->unk18->unk48 = 0.1f;
    arg0->unk18->unk4C = 1.0f;
    arg0->unk18->unk50 = 0.0f;
    func_802D45C4(arg0->unk18, arg0->unk48);
}

void func_802FA290(JumbleHopperData* arg0) {
    uvDobjModel(arg0->objId, 0xFFFF);
    arg0->unkC = 0xFFFF;
    arg0->objId = 0xFFFF;
    func_80334C70();
}

void jumbleHopperMovementFrame(JumbleHopperData* arg0, u8 arg1) {
    f32 sp84;
    f32 sp80;
    f32 var_fa0;
    s32 sp78;
    HUDState* sp74;
    Mtx4F sp34;

    if (func_802E6B5C() != 4) {
        if (arg1 == 6) {
            func_802E65AC(&arg0->unk74, &D_80362690->unk0[0].terraId, &sp84, &sp80, &sp78);
        } else {
            sp84 = demoGetInputs(arg0->unkC, INPUT_AXIS_X);
            sp80 = demoGetInputs(arg0->unkC, INPUT_AXIS_Y);
            sp78 = demoGetButtons(arg0->unkC);
        }
        arg0->unk8 += D_8034F854;
        arg0->unk10 = func_80313F08(&D_80368B20, FABS(sp80));
        if (sp80 < 0) {
            arg0->unk10 = -arg0->unk10;
        }
        arg0->unk14 = func_80313F08(&D_80368B20, FABS(sp84));
        if (sp84 < 0) {
            arg0->unk14 = -arg0->unk14;
        }
        if ((sp78 & A_BUTTON) && ((arg0->unk50 == 0) || (arg0->unk19C != 0))) {
            arg0->unk19C = 1;
        } else {
            arg0->unk19C = 0;
        }
        if (arg1 != 6) {
            func_80303028(arg0);
        }
        if (sp78 & L_CBUTTONS) {
            var_fa0 = 1.5707963f;
        } else if (sp78 & R_CBUTTONS) {
            var_fa0 = -1.5707963f;
        } else {
            var_fa0 = 0.0f;
        }
        arg0->unk3C = func_80313AF4(var_fa0, arg0->unk3C, 2.0f);
        if (sp78 & 4) {
            var_fa0 = 1.5707963f;
        } else if (sp78 & 8) {
            var_fa0 = -1.5707963f;
        } else {
            var_fa0 = 0.0f;
        }
        arg0->unk40 = func_80313AF4(var_fa0, arg0->unk40, 2.0f);
        if (demoButtonPress(arg0->unkC, 0x10) != 0) {
            if ((arg0->unk44 == 9) && (arg0->unk18->unk137C == 0)) {
                func_8033F758(0x6A, 1.0f, 0.5f, 0.0f);
                arg0->unk44 = 9;
                arg0->unk18->unk137C = 1;
            } else {
                func_8033F758(0x6A, 1.0f, 0.5f, 0.0f);
                arg0->unk44 = 9;
                arg0->unk18->unk137C = 0;
            }
        }
        if (arg1 != 6) {
            arg0->unk18->unk4 = arg0->objId;
            arg0->unk18->unk6 = arg0->unk2;
            arg0->unk18->unk7C = arg0->unk40;
            arg0->unk18->unk78 = arg0->unk3C;
            arg0->unk18->unk228 = arg0->unk64;
            func_8034AD6C(arg0->unk140.x, 0.0f, 0.0f, &sp34);
            sp34.m[3][0] = arg0->unkF4.x;
            sp34.m[3][1] = arg0->unkF4.y;
            sp34.m[3][2] = arg0->unkF4.z + 1.0f;
            uvMat4Copy(&arg0->unk18->unk80, &sp34);
            arg0->unk18->unkC0 = arg0->unk140.x;
            arg0->unk18->unkC4 = arg0->unk15C.z;
            if ((arg0->unk4C == 5) || (arg0->unk4C == 9) || (arg0->unk4C == 4) || (arg0->unk4C == 6) || (arg0->unk4C == 7) || (arg0->unk4C == 8)) {
                func_802D5884(arg0->unk18, 6);
            } else {
                func_802D5884(arg0->unk18, arg0->unk44);
            }
            func_802D45C4(arg0->unk18, arg0->unk48);
        }
        if (arg1 != 6) {
            sp74 = hudGetState();
            uvMat4Copy(&sp74->unk28, &arg0->unk74);
            sp74->renderFlags = HUD_RENDER_JUMBLE_HOPPER;
            sp74->att.heading = arg0->unk74.m[3][2];
            sp74->elapsedTime = arg0->unk8;
            sp74->unk8C = arg0->unk15C.z * 4.0f * 0.7f;
            sp74->altitude = arg0->unk64 * 0.7f;
            sp74->altSeaLevel = arg0->unk74.m[3][2] * 0.7f;
            sp74->speed = arg0->unk180 * 3.6f * 0.7f;
        }
        if (arg1 != 6) {
            if (arg0->unk4C == 6) {
                func_802E66DC();
            }
            func_802E65AC(&arg0->unk74, &D_80362690->unk0[0].terraId, &sp84, &sp80, &sp78);
        }
    }
}

void func_802FA7A0(u8 arg0, JumbleHopperData* arg1) {
    switch (arg0) {
    case 0:
        arg1->unk5E8.x = 0.0f, arg1->unk5E8.y = 0.0f, arg1->unk5E8.z = 0.7f;
        arg1->unk5F4.x = 0.0f, arg1->unk5F4.y = 0.0f, arg1->unk5F4.z = -0.745f;
        arg1->unk600.x = 0.0f, arg1->unk600.y = 0.45f, arg1->unk600.z = 0.0f;
        arg1->unk60C.x = 0.0f, arg1->unk60C.y = -0.25f, arg1->unk60C.z = 0.0f;
        arg1->unk618.x = -0.3f, arg1->unk618.y = 0.0f, arg1->unk618.z = 0.0f;
        arg1->unk624.x = 0.3f, arg1->unk624.y = 0.0f, arg1->unk624.z = 0.0f;
        arg1->unk630.x = -0.025f, arg1->unk630.y = 0.307f, arg1->unk630.z = 0.478f;
        arg1->unk63C = 0.504f;
        arg1->unk640 = 0.206f;
        arg1->unk644 = 0.169f;
        arg1->unk648 = 0.2f;
        arg1->unk64C = 0.6f;
        arg1->modelId = 0x150;
        arg1->unk65C = 7;
        arg1->unk65B = 1;
        arg1->unk650 = 5;
        arg1->unk651 = 3;
        arg1->unk652 = 6;
        arg1->unk653 = 4;
        arg1->unk654 = 8;
        arg1->unk655 = 9;
        arg1->unk656 = 10;
        arg1->unk657 = 11;
        arg1->unk658 = 12;
        arg1->unk659 = 13;
        arg1->unk65A = 2;
        break;
    case 1:
        arg1->unk5E8.x = 0.0f, arg1->unk5E8.y = 0.0f, arg1->unk5E8.z = 0.8f;
        arg1->unk5F4.x = 0.0f, arg1->unk5F4.y = 0.0f, arg1->unk5F4.z = -1.336f;
        arg1->unk600.x = 0.0f, arg1->unk600.y = 0.6f, arg1->unk600.z = 0.0f;
        arg1->unk60C.x = 0.0f, arg1->unk60C.y = 0.35f, arg1->unk60C.z = 0.0f;
        arg1->unk618.x = -0.35f, arg1->unk618.y = 0.0f, arg1->unk618.z = 0.0f;
        arg1->unk624.x = 0.35f, arg1->unk624.y = 0.0f, arg1->unk624.z = 0.0f;
        arg1->unk630.x = 0.0f, arg1->unk630.y = 0.315f, arg1->unk630.z = 0.603f;
        arg1->unk63C = 0.18100001f;
        arg1->unk640 = 0.527f;
        arg1->unk644 = 0.476f;
        arg1->unk648 = 0.5f;
        arg1->unk64C = 0.6f;
        arg1->modelId = 0x152;
        arg1->unk65C = 7;
        arg1->unk65B = 1;
        arg1->unk650 = 5;
        arg1->unk651 = 3;
        arg1->unk652 = 6;
        arg1->unk653 = 4;
        arg1->unk654 = 11;
        arg1->unk655 = 12;
        arg1->unk656 = 13;
        arg1->unk657 = 8;
        arg1->unk658 = 9;
        arg1->unk659 = 10;
        arg1->unk65A = 2;
        break;
    case 2:
        arg1->unk5E8.x = 0.0f, arg1->unk5E8.y = 0.0f, arg1->unk5E8.z = 0.7f;
        arg1->unk5F4.x = 0.0f, arg1->unk5F4.y = 0.0f, arg1->unk5F4.z = -1.0f;
        arg1->unk600.x = 0.0f, arg1->unk600.y = 0.65f, arg1->unk600.z = 0.0f;
        arg1->unk60C.x = 0.0f, arg1->unk60C.y = -0.3f, arg1->unk60C.z = 0.0f;
        arg1->unk618.x = -0.5f, arg1->unk618.y = 0.0f, arg1->unk618.z = 0.0f;
        arg1->unk624.x = 0.5f, arg1->unk624.y = 0.0f, arg1->unk624.z = 0.0f;
        arg1->unk630.x = 0.002f, arg1->unk630.y = 0.325f, arg1->unk630.z = 0.52f;
        arg1->unk63C = 0.186f;
        arg1->unk640 = 0.381f;
        arg1->unk644 = 0.378f;
        arg1->unk648 = 0.3f;
        arg1->unk64C = 0.6f;
        arg1->modelId = 0x153;
        arg1->unk65C = 7;
        arg1->unk65B = 1;
        arg1->unk650 = 3;
        arg1->unk651 = 5;
        arg1->unk652 = 4;
        arg1->unk653 = 6;
        arg1->unk654 = 8;
        arg1->unk655 = 9;
        arg1->unk656 = 10;
        arg1->unk657 = 11;
        arg1->unk658 = 12;
        arg1->unk659 = 13;
        arg1->unk65A = 2;
        break;
    case 3:
        arg1->unk5E8.x = 0.0f, arg1->unk5E8.y = 0.0f, arg1->unk5E8.z = 0.7f;
        arg1->unk5F4.x = 0.0f, arg1->unk5F4.y = 0.0f, arg1->unk5F4.z = -1.0f;
        arg1->unk600.x = 0.0f, arg1->unk600.y = 0.45f, arg1->unk600.z = 0.0f;
        arg1->unk60C.x = 0.0f, arg1->unk60C.y = -0.3f, arg1->unk60C.z = 0.0f;
        arg1->unk618.x = -0.3f, arg1->unk618.y = 0.0f, arg1->unk618.z = 0.0f;
        arg1->unk624.x = 0.3f, arg1->unk624.y = 0.0f, arg1->unk624.z = 0.0f;
        arg1->unk630.x = 0.002f, arg1->unk630.y = 0.308f, arg1->unk630.z = 0.473f;
        arg1->unk63C = 0.334f;
        arg1->unk640 = 0.233f;
        arg1->unk644 = 0.297f;
        arg1->unk648 = .3f;
        arg1->unk64C = 0.6f;
        arg1->modelId = 0x154;
        arg1->unk65C = 9;
        arg1->unk65B = 1;
        arg1->unk650 = 7;
        arg1->unk651 = 5;
        arg1->unk652 = 8;
        arg1->unk653 = 6;
        arg1->unk654 = 13;
        arg1->unk655 = 14;
        arg1->unk656 = 15;
        arg1->unk657 = 10;
        arg1->unk658 = 11;
        arg1->unk659 = 12;
        arg1->unk65A = 2;
        break;
    case 4:
        arg1->unk5E8.x = 0.0f, arg1->unk5E8.y = 0.0f, arg1->unk5E8.z = 0.8f;
        arg1->unk5F4.x = .0f, arg1->unk5F4.y = 0.0f, arg1->unk5F4.z = -1.0f;
        arg1->unk600.x = 0.0f, arg1->unk600.y = 0.55f, arg1->unk600.z = 0.0f;
        arg1->unk60C.x = 0.0f, arg1->unk60C.y = -0.45f, arg1->unk60C.z = 0.0f;
        arg1->unk618.x = -0.35f, arg1->unk618.y = 0.0f, arg1->unk618.z = 0.0f;
        arg1->unk624.x = 0.35f, arg1->unk624.y = 0.0f, arg1->unk624.z = 0.0f;
        arg1->unk630.x = 0.0f, arg1->unk630.y = 0.212f, arg1->unk630.z = 0.599f;
        arg1->unk63C = 0.71500003f;
        arg1->unk640 = 0.526f;
        arg1->unk644 = 0.427f;
        arg1->unk648 = .3f;
        arg1->unk64C = 0.6f;
        arg1->modelId = 0x155;
        arg1->unk65C = 7;
        arg1->unk65B = 1;
        arg1->unk650 = 3;
        arg1->unk651 = 5;
        arg1->unk652 = 4;
        arg1->unk653 = 6;
        arg1->unk654 = 11;
        arg1->unk655 = 12;
        arg1->unk656 = 13;
        arg1->unk657 = 8;
        arg1->unk658 = 9;
        arg1->unk659 = 10;
        arg1->unk65A = 2;
        break;
    case 5:
        arg1->unk5E8.x = 0.0f, arg1->unk5E8.y = 0.0f, arg1->unk5E8.z = 0.85f;
        arg1->unk5F4.x = 0.0f, arg1->unk5F4.y = 0.0f, arg1->unk5F4.z = -1.0f;
        arg1->unk600.x = 0.0f, arg1->unk600.y = 0.5f, arg1->unk600.z = 0.0f;
        arg1->unk60C.x = 0.0f, arg1->unk60C.y = -0.45f, arg1->unk60C.z = 0.0f;
        arg1->unk618.x = -0.35f, arg1->unk618.y = 0.0f, arg1->unk618.z = 0.0f;
        arg1->unk624.x = 0.35f, arg1->unk624.y = 0.0f, arg1->unk624.z = 0.0f;
        arg1->unk630.x = 0.0f, arg1->unk630.y = 0.217f, arg1->unk630.z = 0.621f;
        arg1->unk63C = 0.502f;
        arg1->unk640 = 0.508f;
        arg1->unk644 = 0.28f;
        arg1->unk648 = .3f;
        arg1->unk64C = 0.6f;
        arg1->modelId = 0x156;
        arg1->unk65C = 7;
        arg1->unk65B = 1;
        arg1->unk650 = 3;
        arg1->unk651 = 5;
        arg1->unk652 = 4;
        arg1->unk653 = 6;
        arg1->unk654 = 8;
        arg1->unk655 = 9;
        arg1->unk656 = 10;
        arg1->unk657 = 11;
        arg1->unk658 = 12;
        arg1->unk659 = 13;
        arg1->unk65A = 2;
        break;
    default:
        break;
    }
}
