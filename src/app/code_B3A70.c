#include "common.h"
#include <uv_dobj.h>
#include <uv_event.h>
#include <uv_font.h>
#include <uv_geometry.h>
#include <uv_memory.h>
#include <uv_texture.h>
#include <uv_vector.h>
#include "birdman.h"
#include "cannonball.h"
#include "code_66F70.h"
#include "jumble_hopper.h"
#include "code_9A960.h"
#include "code_B3A70.h"
#include "code_D1ED0.h"
#include "code_D2B10.h"
#include "demo.h"
#include "environment.h"
#include "fdr.h"
#include "gyrocopter.h"
#include "hang_glider.h"
#include "hud.h"
#include "map3d.h"
#include "menu.h"
#include "menu_utils.h"
#include "proxanim.h"
#include "rocket_belt.h"
#include "shadow.h"
#include "skydiving.h"
#include "snd.h"
#include "snow.h"
#include "task.h"
#include "text_data.h"
#include "whale.h"
#include "wind_objects.h"

s32 sShutterBugTestItems[] = { TEXT_CONTINUE_SGI, TEXT_CHECKMAP_SGI, TEXT_CHECK_PHOTOS_SGI, TEXT_QUIT_SGI };
s32 sSkyDivingItems[] = { TEXT_CONTINUE_SGI, TEXT_QUIT_SGI };
s32 sOtherItems[] = { TEXT_CONTINUE_SGI, TEXT_CHECKMAP_SGI, TEXT_QUIT_SGI };

STATIC_FUNC void func_8032D33C(Mtx4F*, Mtx4F*, f32, u8);

void func_8032C540(Unk80362690* arg0) {
    f32 var_fs3;
    HangGliderData* hgData;
    GyrocopterData* gcData;
    RocketBeltData* rbData;
    CannonballData* cbData;
    SkyDivingData* sdData;
    JumbleHopperData* jhData;
    BirdmanData* bmData;
    Mtx4F sp188;
    Mtx4F sp148;
    Mtx4F sp108;
    Mtx4F spC8;
    Mtx4F sp88;
    u8 sp87;
    u8 var_s4;
    Unk80362690_Unk0* temp_s0;
    f32 temp_fa0;
    f32 var_fs0;
    f32 var_fs2;
    f32 temp_fv0;
    f32 sp6C;
    u16 pad_sp6A;
    u16 sp68;
    u16 sp66;
    u16 sp64;

    temp_s0 = &arg0->unkC[arg0->unk9C];
    var_s4 = 0;
    var_fs3 = 0.0f;
    var_fs0 = 0.0f;
    var_fs2 = 0.0f;
    uvEventPost(0x12, 0);
    switch (temp_s0->veh) {
    case VEHICLE_HANG_GLIDER:
        hgData = temp_s0->vehicleData;
        hangGliderEnterLeave(hgData);
        sp87 = hgData->objId;
        hgData->unk2 &= ~8;
        break;
    case VEHICLE_GYROCOPTER:
        gcData = temp_s0->vehicleData;
        gyrocopterEnterLeave(gcData);
        sp87 = gcData->objId;
        gcData->unk2 &= ~8;
        break;
    case VEHICLE_ROCKET_BELT:
        rbData = temp_s0->vehicleData;
        rocketBeltEnterLeave(rbData);
        sp87 = rbData->objId;
        rbData->unk2 &= ~8;
        break;
    case VEHICLE_CANNONBALL:
        cbData = temp_s0->vehicleData;
        cannonLevelEnterLeave(cbData);
        sp87 = cbData->objId;
        cbData->unk2 &= ~8;
        break;
    case VEHICLE_SKY_DIVING:
        sdData = temp_s0->vehicleData;
        skydivingEnterLeave(sdData);
        sp87 = sdData->objId;
        sdData->unk2 &= ~8;
        break;
    case VEHICLE_JUMBLE_HOPPER:
        jhData = temp_s0->vehicleData;
        jumbleHopperEnterLeave(jhData);
        sp87 = jhData->objId;
        jhData->unk2 &= ~8;
        break;
    case VEHICLE_BIRDMAN:
        bmData = temp_s0->vehicleData;
        birdEnterLeave(bmData);
        sp87 = bmData->objId;
        bmData->unk2 &= ~8;
        break;
    }
    uvDobjState(sp87, 2);
    uvMat4Copy(&sp148, &temp_s0->unk2C);
    func_8032D33C(&sp188, &sp148, temp_s0->unk70->unk8, 0);
    func_802D5884(temp_s0->unk70, 5U);
    temp_s0->unk70->unk1A0 = 2.0f;
    temp_s0->unk70->unk0 = 0x70;
    fdr_802E68B0(3);
    hudGetState()->renderFlags = 0;
    uvEventPost(0x10, 0);
    func_80313E0C(fdr_802E6B68());
    sp6C = -100.0f;
    sp68 = arg0->terraId;
    sp64 = 0xFFFF;
    fdr_802E7278(&sp108, &sp66);
    func_8032D33C(&sp108, &sp108, temp_s0->unk70->unk8, 1);
    temp_s0->unk70->unk8 = 1.0f;
    while (var_fs2 == 0.0f || D_8034F850 < var_fs2) {
        var_fs0 += D_8034F854;
        if (fdr_802E6B5C() == 4 && var_fs2 == 0.0f) {
            var_fs2 = var_fs0 + 0.2f;
        }
        demo_80323020();
        if (demoButtonPress(arg0->unk9C, A_BUTTON | START_BUTTON | B_BUTTON) != 0) {
            if (demoButtonPress(arg0->unk9C, A_BUTTON | START_BUTTON) != 0) {
                sndPlaySfx(SFX_UI_CONFIRM);
            } else if (demoButtonPress(arg0->unk9C, B_BUTTON) != 0) {
                sndPlaySfx(SFX_UI_CANCEL);
            }
            break;
        }

        switch (temp_s0->veh) {
        case VEHICLE_HANG_GLIDER:
            hgData = temp_s0->vehicleData;
            hangGliderMovementFrame(hgData, arg0->state);
            uvMat4Copy(&sp148, &hgData->unk10);
            break;
        case VEHICLE_GYROCOPTER:
            gcData = temp_s0->vehicleData;
            gyrocopterMovementFrame(gcData, arg0->state);
            uvMat4Copy(&sp148, &gcData->unk10);
            break;
        case VEHICLE_ROCKET_BELT:
            rbData = temp_s0->vehicleData;
            rocketBeltMovementFrame(rbData, arg0->state);
            uvMat4Copy(&sp148, &rbData->unk10);
            break;
        case VEHICLE_CANNONBALL:
            cbData = temp_s0->vehicleData;
            cannonMovementFrame(cbData, arg0->state);
            uvMat4Copy(&sp148, &cbData->unk14);
            break;
        case VEHICLE_SKY_DIVING:
            sdData = temp_s0->vehicleData;
            skydivingMovementFrame(sdData, arg0->state);
            uvMat4Copy(&sp148, &sdData->unk10);
            break;
        case VEHICLE_JUMBLE_HOPPER:
            jhData = temp_s0->vehicleData;
            jumbleHopperMovementFrame(jhData, arg0->state);
            uvMat4Copy(&sp148, &jhData->unk74);
            break;
        case VEHICLE_BIRDMAN:
            bmData = temp_s0->vehicleData;
            birdMovementFrame(bmData, arg0->state);
            uvMat4Copy(&sp148, &bmData->unk10);
            break;
        }
        sp66 = arg0->terraId;
        if (sp66 != sp64) {
            uvChanTerra(temp_s0->unk70->unk22C, sp66);
            taskUpdateState();
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
        temp_fv0 = func_8031385C(&temp_s0->unk70->unk108, &temp_s0->unk70->unk80);
        temp_fa0 = 0.5f + (0.02f * temp_fv0);
        if (temp_fa0 < 1.0f) {
            temp_fa0 = 1.0f;
        } else if (temp_fa0 > 4.0f) {
            temp_fa0 = 4.0f;
        }
        func_802D45C4(temp_s0->unk70, temp_fa0);
        func_802D4A30(temp_s0->unk70, &temp_s0->unk70->unk108);
        func_802D3444(temp_s0->unk70);
        taskFrameUpdate(&sp148, 0.0f);
        proxAnimUpdate();
        uvFontSet(0);
        uvFontScale(1.0, 0.800000011920929);
        uvGfxBegin();
        func_8034B624(temp_s0->unk70);
        if (var_fs3 > 0.5f) {
            var_fs3 = 0.0f;
            var_s4 = var_s4 == 0;
        }
        if (var_s4) {
            uvFontColor(0xFF, 0xFF, 0x00, 0xFF);
            uvFontPrintStr(20, 200, "REPLAY");
            uvFontGenDlist();
        }
        uvGfxEnd();
        func_80313D74();
        env_802E15F0();
        windObjFrameUpdate();
        var_fs3 += D_8034F854;
    }
    uvEventPost(0xC, 0);
    func_8033F964(2);
}

void func_8032CC44(Unk80362690* arg0) {
    Unk80362690_Unk0* sp2C;
    s32 sp28;
    s32 sp24;
    s32 sp20;
    s32 sp1C;
    u8 sp1B;
    CannonballData* cbData;

    sp2C = &arg0->unkC[arg0->unk9C];
    sp1B = 1;
    func_8032D51C(0);
    whaleStateSave();
    level_8030BA60();
    if (arg0->unkA0 == 0) {
        sp1B = 0;
    }
    taskDeinitLevel();
    windObjDeinit();
    proxAnimDispatchEvent2();
    cannon_802D8A40(1U, (CannonballData*)sp2C->vehicleData);
    sp20 = 0xFFFF;
    sp1C = 0;
    switch (sp2C->veh) {
    case VEHICLE_GYROCOPTER:
        cbData = (CannonballData*)sp2C->vehicleData;
        sp28 = cbData->objId;
        sp24 = cbData->unk2;
        break;
    case VEHICLE_HANG_GLIDER:
        cbData = (CannonballData*)sp2C->vehicleData;
        sp28 = cbData->objId;
        sp24 = cbData->unk2;
        break;
    case VEHICLE_ROCKET_BELT:
        cbData = (CannonballData*)sp2C->vehicleData;
        sp1C = 0x22;
        sp28 = cbData->objId;
        sp24 = cbData->unk2;
        sp20 = cbData->pad6;
        break;
    case VEHICLE_CANNONBALL:
        cbData = (CannonballData*)sp2C->vehicleData;
        sp28 = cbData->objId;
        sp24 = cbData->unk2;
        break;
    case VEHICLE_SKY_DIVING:
        cbData = (CannonballData*)sp2C->vehicleData;
        sp28 = cbData->objId;
        sp24 = cbData->unk2;
        break;
    case VEHICLE_JUMBLE_HOPPER:
        cbData = (CannonballData*)sp2C->vehicleData;
        sp28 = cbData->objId;
        sp24 = cbData->unk2;
        break;
    case VEHICLE_BIRDMAN:
        cbData = (CannonballData*)sp2C->vehicleData;
        sp28 = cbData->objId;
        sp24 = cbData->unk2;
    }
    uvDobjState(sp28, 0);
    if (sp20 != 0xFFFF) {
        uvDobjState(sp20, 0);
    }
    shadow_803343D8(0);
    uvLevelInit();
    switch (arg0->map) {
    case MAP_HOLIDAY_ISLAND:
        uvLevelAppend(0);
        break;
    case MAP_CRESCENT_ISLAND:
        uvLevelAppend(2);
        break;
    case MAP_LITTLE_STATES:
        uvLevelAppend(4);
        break;
    case MAP_EVER_FROST_ISLAND:
        uvLevelAppend(9);
        break;
    }
    uvLevelAppend(0xB);
    uvLevelAppend(0x87);
    map3dMain(arg0, 1);
    func_8032D51C(0);
    uvLevelInit();
    levelLoad(arg0->map, sp2C->pilot, sp2C->veh, 1);
    shadow_803343D8(1);
    uvDobjState(sp28, sp24);
    if (sp20 != 0xFFFF) {
        uvDobjState(sp20, sp1C);
    }
    proxAnimDispatchEvent3();
    windObjLoad();
    if (sp1B != 0) {
        arg0->unkA0 = 1;
    }
    taskLoad();
    cannon_802D8A40(0, (CannonballData*)sp2C->vehicleData);
    hudInit();
    whaleStateRestore();
}

s32 func_8032CF28(Unk80362690* arg0) {
    Unk80362690_Unk0* sp6C;
    Camera* sp68;
    HUDState* hud;
    s32 var_s0;
    s32 var_s1;
    u8 sp5B;
    s32 pad[4];
    s32 sp40;

    sp6C = &arg0->unkC[arg0->unk9C];
    sp68 = sp6C->unk70;
    sndPlaySfx(4U);
    var_s0 = 0x4C;
    hud = hudGetState();
    sp5B = hud->renderFlags;
    hud->renderFlags = HUD_RENDER_DISABLE;
    sp40 = sp6C->veh == VEHICLE_HANG_GLIDER &&
           ((sp6C->test == 0 && sp6C->cls == CLASS_A) || (sp6C->test == 1 && sp6C->cls == CLASS_B) || (sp6C->test == 2 && sp6C->cls == CLASS_PILOT));
    if (sp6C->unk8 != 0 || (sp6C->veh == VEHICLE_SKY_DIVING && ((BirdmanData*)sp6C->vehicleData)->unk25C.z == 1 /*.0f*/)) {
        menuCreateItems(99, 72, 6, 1.0f, 1.0f, sSkyDivingItems, 2);
        var_s0 = 0x38;
    } else if (sp40 != 0) {
        menuCreateItems(99, 72, 6, 1.0f, 1.0f, sShutterBugTestItems, 4);
        var_s0 = 0x5B;
    } else {
        menuCreateItems(99, 72, 6, 1.0f, 1.0f, sOtherItems, 3);
    }
    menuUtilSetButtonMode(1);
    do {
        uvGfxSetUnkStateF(0.000001f);
        var_s1 = menuCheckInputs();
        while (var_s1 != -2 && demoButtonCheck(arg0->unk9C, A_BUTTON) != 0) {
            demo_80323020();
        }
        uvGfxBegin();
        func_80204FC4(sp68->unk22C);
        func_80314154();
        uvVtxBeginPoly();
        uvVtx(90, 82, 0, 0, 0, 0, 0, 0, 0x7F);
        uvVtx(230, 82, 0, 0, 0, 0, 0, 0, 0x7F);
        uvVtx(230, var_s0 + 82, 0, 0, 0, 0, 0, 0, 0x7F);
        uvVtx(90, var_s0 + 82, 0, 0, 0, 0, 0, 0, 0x7F);
        uvVtxEndPoly();
        func_803141E4();
        menuRender();
        uvFontGenDlist();
        uvGfxEnd();
    } while (var_s1 == -2 || var_s1 == -3);
    uvGfxSetUnkStateF(0.0f);
    menuUtilSetButtonMode(0);
    if (sp40 == 0 && var_s1 == 2) {
        var_s1 = 3;
    }
    if ((sp6C->unk8 != 0) || ((sp6C->veh == VEHICLE_SKY_DIVING) && (((BirdmanData*)sp6C->vehicleData)->unk25C.z == 1 /*.0f*/))) {
        if (var_s1 == 0) {
            var_s1 = 0;
        }
        if (var_s1 == 1) {
            var_s1 = 3;
        }
    }
    hud->renderFlags = sp5B;
    if (var_s1 == -1) {
        var_s1 = 0;
    }
    if (var_s1 != 0 && (taskGet_80345CB0()[1] == 1)) {
        snowDisable();
    }
    return var_s1;
}

STATIC_FUNC void func_8032D33C(Mtx4F* arg0, Mtx4F* arg1, f32 arg2, u8 arg3) {
    Vec3F spA4 = { 0.0f, 0.0f, 1.0f };
    Mtx4F sp64;
    Mtx4F sp24;
    f32 sp20;

    sp20 = 4.0f * arg2;
    if (sp20 < 1.0f) {
        sp20 = 1.0f;
    } else if (sp20 > 8.0f) {
        sp20 = 8.0f;
    }
    uvMat4Copy(&sp24, arg1);
    func_80313E18(&spA4, &sp24);
    uvMat4SetIdentity(&sp64);
    sp64.m[3][0] = sp24.m[3][0];
    sp64.m[3][1] = sp24.m[3][1];
    sp64.m[3][2] = sp24.m[3][2];
    if (!arg3) {
        sp64.m[3][0] += ((0.894f * sp20) * sp24.m[0][0]);
        sp64.m[3][1] += ((0.894f * sp20) * sp24.m[0][1]);
        sp64.m[3][2] += ((0.894f * sp20) * sp24.m[0][2]);
        sp64.m[3][0] += ((0.447f * sp20) * sp24.m[1][0]);
        sp64.m[3][1] += ((0.447f * sp20) * sp24.m[1][1]);
        sp64.m[3][2] += ((0.447f * sp20) * sp24.m[1][2]);
    } else {
        sp64.m[3][0] -= ((0.447f * sp20) * sp24.m[0][0]);
        sp64.m[3][1] -= ((0.447f * sp20) * sp24.m[0][1]);
        sp64.m[3][2] -= ((0.447f * sp20) * sp24.m[0][2]);
        sp64.m[3][0] -= ((0.894f * sp20) * sp24.m[1][0]);
        sp64.m[3][1] -= ((0.894f * sp20) * sp24.m[1][1]);
        sp64.m[3][2] -= ((0.894f * sp20) * sp24.m[1][2]);
    }
    uvMat4UnkOp6(arg0, &sp24, &sp64);
    if (!arg3) {
        func_802E0484(arg0, &sp24, 1.6f);
    }
}

void func_8032D51C(s32 fadeoutType) {
    f32 var_fs0;
    f32 var_fs3;
    u8 sp87;
    u8 sp86;
    u8 sp85;
    u8 sp84;
    f32 var_fs1;
    s32 i;

    var_fs1 = var_fs0 = 0.0f;
    switch (fadeoutType) {
    case 0:
        var_fs3 = 0.5f;
        sp87 = sp86 = sp85 = 0;
        break;
    case 1:
        var_fs3 = 4.0f;
        sp87 = sp86 = sp85 = 0xFF;
        break;
    default:
        _uvDebugPrintf("screen_fadeout ( %d ) unknown type\n", fadeoutType);
        break;
    }
    uvGfxWaitForMesg();
    uvCopyFrameBuf(0);
    while (var_fs3 > var_fs1 && var_fs0 < 1.0f) {
        if ((0.38f * var_fs3) < var_fs1) {
            var_fs1 = var_fs3;
        }
        uvGfxBegin();
        var_fs0 = (2.0f * var_fs1) / var_fs3;
        if (var_fs0 < 0.0f) {
            var_fs0 = 0.0f;
        } else if (var_fs0 > 1.0f) {
            var_fs0 = 1.0f;
        }
        sp84 = 255.0f * var_fs0;
        func_80314154();
        uvGfxSetFlags(GFX_STATE_AA);
        uvVtxBeginPoly();
        uvVtx(9, 17, 0, 0, 0, sp87, sp86, sp85, sp84);
        uvVtx(311, 17, 0, 0, 0, sp87, sp86, sp85, sp84);
        uvVtx(311, 233, 0, 0, 0, sp87, sp86, sp85, sp84);
        uvVtx(9, 233, 0, 0, 0, sp87, sp86, sp85, sp84);
        uvVtxEndPoly();
        func_803141E4();
        uvGfxEnd();
        var_fs1 += (1.0f / 60.0f);
    }
    func_80314154();
    for (i = 0; i < 2; i++) {
        uvGfxBegin();
        uvVtxBeginPoly();
        uvVtx(9, 17, 0, 0, 0, sp87, sp86, sp85, sp84);
        uvVtx(311, 17, 0, 0, 0, sp87, sp86, sp85, sp84);
        uvVtx(311, 233, 0, 0, 0, sp87, sp86, sp85, sp84);
        uvVtx(9, 233, 0, 0, 0, sp87, sp86, sp85, sp84);
        uvVtxEndPoly();
        uvGfxEnd();
    }
    func_803141E4();
}

void func_8032D90C(void) {
    f32 var_fs0;
    f32 r;
    f32 g;
    f32 b;
    s16* msg2;
    s16* msg3;
    s16* msg4;
    s16* msg1;
    u8 r2, g2, b2;

    var_fs0 = 0.0f;
    uvLevelAppend(0x2E);
    textLoadBlock(0x42);
    msg1 = textGetDataByIdx(TEXT_NO_CNT);
    msg2 = textGetDataByIdx(TEXT_NO_CNT2);
    msg3 = textGetDataByIdx(TEXT_NO_CNT3);
    msg4 = textGetDataByIdx(TEXT_NO_CNT4);
    while (1) {
        var_fs0 += 0.003f;
        if (var_fs0 > 1.0f) {
            var_fs0 -= 1.0f;
        }
        func_8031420C(var_fs0, 1.0f, 1.0f, &r, &g, &b);
        r2 = 255.0f * r;
        g2 = 255.0f * g;
        b2 = 255.0f * b;
        uvGfxBegin();
        uvGfxClearScreen(0x00, 0x00, 0x00, 0xFF);
        func_80314154();
        uvGfxSetFlags(GFX_STATE_AA);
        uvFontSet(6);
        uvFontScale(1.0, 1.0);
        uvFontColor(r2, g2, b2, 0xFF);
        uvFontPrintStr16((SCREEN_WIDTH / 2) - ((uvFontStr16Width(msg1) - 16) / 2), 155, msg1, 0x3C, 0xFFE);
        uvFontPrintStr16((SCREEN_WIDTH / 2) - ((uvFontStr16Width(msg2) - 16) / 2), 135, msg2, 0x3C, 0xFFE);
        uvFontPrintStr16((SCREEN_WIDTH / 2) - ((uvFontStr16Width(msg3) - 16) / 2), 115, msg3, 0x3C, 0xFFE);
        uvFontPrintStr16((SCREEN_WIDTH / 2) - ((uvFontStr16Width(msg4) - 16) / 2), 95, msg4, 0x3C, 0xFFE);
        uvFontGenDlist();
        func_803141E4();
        uvGfxEnd();
    }
}
