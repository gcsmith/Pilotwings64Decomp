#ifndef UV_FX_H
#define UV_FX_H

#include <PR/ultratypes.h>
#include <uv_graphics.h>
#include <uv_matrix.h>
#include <uv_vector.h>

typedef struct UnkModelTrail_Unk0 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
} UnkModelTrail_Unk0; // size = 0x18

typedef struct UnkModelTrail {
    UnkModelTrail_Unk0 unk0[10];
    Vec3F unkF0[10];
    f32 unk168[10];
    Vec3F unk190;
    u8 pad19C[0x18];
    Vec3F unk1B4;
    u8 pad1C0[0x4];
    Vec3F unk1C4;
    f32 unk1D0;
    f32 unk1D4;
    Vec3F unk1D8;
    s16 unk1E4;
    s16 unk1E6;
    s32 unk1E8;
    u8 unk1EC;
} UnkModelTrail; // size = 0x1F0

typedef struct UnkModelDebrisStructure {
    Vec3F unk0[20];
    Vec3F unkF0[20];
    f32 unk1E0[20];
    f32 unk230[20];
    f32 unk280[20];
    u8 unk2D0[20];
    u8 unk2E4;
} UnkModelDebrisStructure; // size = 0x2E8

typedef struct {
    u8 unk0;
    u8 type;
    u16 unk2;
    u8 unk4;
    u8 unk5;
    u8 unk6;
    u8 unk7;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    u8 pad2C[0x4];
    f32 unk30;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    f32 unk40;
    f32 unk44;
    f32 unk48;
    f32 unk4C;
    u16 unk50;
    u8 unk52;
    u8 unk53;
    u8 unk54;
    u8 unk55;
    u8 unk56;
    u8 unk57;
    u8 unk58;
    u8 unk59;
    u8 ditherProperty;
    u8 pad5B[0x1];
    u16 unk5C;
    u8 pad5E[0x2];
    s32 unk60;
    s32 unk64;
    Mtx4F unk68;
    void* unkA8; // UnkModelTrail* or UnkModelDebrisStructure*
    f32 unkAC;
} UnkFxStruct; // size = 0xB0

extern UnkModelDebrisStructure D_8028A0A0[4];
extern UnkModelTrail D_8028AC40[4];
extern UnkFxStruct D_8028B400[120];

#define FX_PROPS_1(x) 1, (x)
#define FX_PROPS_2(x) 2, (x)
#define FX_PROPS_3(x, y, z) 3, (x), (y), (z)
#define FX_PROPS_4(x, y, z) 4, (x), (y), (z)
#define FX_PROPS_5(x, y, z, w) 5, (x), (y), (z), (w)
#define FX_PROPS_6(x, y, z, w) 6, (x), (y), (z), (w)
#define FX_PROPS_7(x) 7, (x)
#define FX_PROPS_8(x) 8, (x)
#define FX_PROPS_9(x) 9, (x)
#define FX_PROPS_10(x, y, z) 10, (x), (y), (z)
#define FX_PROPS_11(x) 11, (x)
#define FX_PROPS_12(x, y, z) 12, (x), (y), (z)
#define FX_PROPS_13(x) 13, (x)
#define FX_PROPS_14(x) 14, (x)
#define FX_PROPS_15(x) 15, (x)
#define FX_PROPS_16(x) 16, (x)
#define FX_PROPS_17(x) 17, (x)
#define FX_PROPS_18(x) 18, (x)
#define FX_PROPS_19(x) 19, (x)
#define FX_END 0

void func_8021A038(UnkModelTrail* arg0);
s32 func_8021A334(f32 arg0, f32 arg1, f32 arg2, f32 arg3, u16 arg4);
void func_8021A4D8(s32 fxId, Mtx4F* arg1);
void func_8021BE28(u16 fxId, Mtx4F* arg1);
void func_8021EA38(UnkStruct_80204D94* arg0);
void _uvFxDraw(u16 fxId, UnkStruct_80204D94* arg1);
s32 func_8021EFF0(s32 type);
void uvFxProps(s32 fxId, ...);

#endif // UV_FX_H
