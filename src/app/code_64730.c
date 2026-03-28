#include "common.h"
#include "task.h"
#include "code_64730.h"
#include <uv_dobj.h>

s8 D_8034EDA0 = 0;
s8 D_8034EDA4[] = { 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

f32 D_8034EDBC = 0.0f;

u8 D_8034EDC0 = 0xFF;
u8 D_8034EDC4 = 0xFF;
s32 D_8034EDC8 = 0xFFFF;
s32 D_8034EDCC = 0xFFFF;
s32 D_8034EDD0 = 0;
s32 D_8034EDD4 = 0;
s32 D_8034EDD8 = 0;

Unk803599D0 D_8034EDDC[] = {
    8, 0.36f, 0.0f, 0.412f, 0.1f, 0.465f, 0.25f, 0.517f, 0.475f, 0.568f, 0.5f, 0.62f, 0.475f, 0.673f, 0.25f, 0.725f, 0.0f, 0, 0, 0, 0
};

s16 D_8034EE30[VEHICLE_COUNT][PILOT_COUNT] = {
    {               MODEL_HG_LARK,               MODEL_HG_GOOSE,               MODEL_HG_HAWK,               MODEL_HG_KIWI,               MODEL_HG_IBIS,MODEL_HG_ROBIN                                                                                                                                                       },
    {               MODEL_RB_LARK,               MODEL_RB_GOOSE,               MODEL_RB_HAWK,               MODEL_RB_KIWI,               MODEL_RB_IBIS,        MODEL_RB_ROBIN },
    {             MODEL_GYRO_LARK,             MODEL_GYRO_GOOSE,             MODEL_GYRO_HAWK,             MODEL_GYRO_KIWI,             MODEL_GYRO_IBIS,      MODEL_GYRO_ROBIN },
    { MODEL_CANNONB_LARK_LAUNCHED, MODEL_CANNONB_GOOSE_LAUNCHED, MODEL_CANNONB_HAWK_LAUNCHED, MODEL_CANNONB_KIWI_LAUNCHED, MODEL_CANNONB_IBIS_LAUNCHED,
     MODEL_CANNONB_ROBIN_LAUNCHED                                                                                                                                            },
    {        MODEL_PARACHUTE_LARK,        MODEL_PARACHUTE_GOOSE,        MODEL_PARACHUTE_HAWK,        MODEL_PARACHUTE_KIWI,        MODEL_PARACHUTE_IBIS, MODEL_PARACHUTE_ROBIN },
    {          MODEL_JUMBLEH_LARK,          MODEL_JUMBLEH_GOOSE,          MODEL_JUMBLEH_HAWK,          MODEL_JUMBLEH_KIWI,          MODEL_JUMBLEH_IBIS,   MODEL_JUMBLEH_ROBIN },
    {          MODEL_BIRDMAN_LARK,          MODEL_BIRDMAN_GOOSE,          MODEL_BIRDMAN_HAWK,          MODEL_BIRDMAN_KIWI,          MODEL_BIRDMAN_IBIS,   MODEL_BIRDMAN_ROBIN },
};

u8 D_8034EE84[8] = {
    0x4C, 0x4D, 0x4B, 0x51, 0x50, 0x4F, 0x4E, 0x00,
};

f32 D_8034EE8C[] = {
    -0.745f, -1.336f, -1.221f, -0.828f, -1.36f, -1.076f, -0.745f, -1.336f, -1.0f, -1.0f, -1.0f, -1.0f,
};

f32 D_8034EEBC[] = {
    -0.745f, -1.336f, -1.221f, -0.828f, -1.36f, -1.076f,
};

f32 D_8034EED4 = 0.0f;
f32 D_8034EED8 = 1.6f;

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_64730/func_802DD200.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_64730/func_802DD42C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_64730/func_802DD44C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_64730/func_802DD57C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_64730/func_802DD8E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_64730/func_802DE5B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/app/code_64730/func_802DE964.s")
