#ifndef APP_CODE_72B70_H
#define APP_CODE_72B70_H

#include <uv_level.h>
#include <uv_matrix.h>

typedef struct {
    u8 unk0;
    u8 pad1;
    s16 scores[15];
} TestResult; // size = 0x20

typedef struct {
    u8 unk0[0x8];
    s32 unk8;
    s16 points;
    u8 padE[2];
    TestResult result;
} Unk80364210_Unk0_Unk0; // size = 0x30

typedef struct {
    Unk80364210_Unk0_Unk0 unk0[MAX_TESTS][VEHICLE_COUNT]; // guess
    s32 unk690;
} Unk80364210_Unk0; // size = 0x694

typedef struct {
    Unk80364210_Unk0 unk0[MAX_CLASSES]; // guess
    u8 unk34A0[0x40];
} Unk80364210; // size = 0x34E0

extern Unk80364210 D_80364210[];

typedef struct {
    u8 testCount;
    u8 pad1[0x157];
} Unk80367710;

void func_802EB9C0(void);
void func_802EBC30(void);
void func_802EDDEC(Mtx4F*);
void func_802EDAF0(void*, Mtx4F*, s32, s32, f32, f32, f32, u32, s32, s32, s32);

#endif // APP_CODE_72B70_H
