#include <uv_graphics.h>
#include <uv_math.h>

// from kernel/code_7150
void func_802061A0(void*);
s32 func_80206F64(void*, f32, f32, f32, f32);

typedef struct {
    s32 unk0;
    s32 unk4;
    u8 pad0[0x3C];
    s32 unk44;
} uvChanUnk_t;

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_58E0/func_80204930.s")

void func_80204A8C(s32 arg0, s32 arg1) {
    D_80261730[arg0].unk0 = arg1;
}

void func_80204AB0(s32 arg0, s32 arg1, s32 arg2) {
    if (arg1 != 0) {
        if (arg1 == 1) {
            *(s32*)&D_80261ACC[arg0] = arg2;
        }
    } else {
        *(s32*)&D_80261AC8[arg0] = arg2;
    }
}

void func_80204B08(s32 arg0, s32 arg1, s32 arg2) {
    *((s16*)&D_80261736[arg0] + arg1) = arg2;
}

void func_80204B34(s32 arg0, Mtx4F* arg1) {
    UnkStruct_80204D94* temp_s0;

    temp_s0 = &D_80261730[arg0];
    uvMat4Copy(&temp_s0->unk110, arg1);
    func_802057F4(&temp_s0->unk190, arg1);
    uvMat4CopyF2L(&temp_s0->unk150, &temp_s0->unk190);
    temp_s0->unk1D0 = arg1->m[3][0];
    temp_s0->unk1D4 = arg1->m[3][1];
    temp_s0->unk1D8 = arg1->m[3][2];
    temp_s0->unk1DC = arg1->m[1][0];
    temp_s0->unk1E0 = arg1->m[1][1];
    temp_s0->unk1E4 = arg1->m[1][2];
}

void func_80204BD4(s32 arg0, s32 arg1, f32 arg2) {
    switch (arg1) {
    case 0:
        *(f32*)&D_80261930[arg0] = 1.0f / arg2;
        break;
    case 1:
        *(f32*)&D_80261934[arg0] = 1.0f / arg2;
        break;
    }
}

void func_80204C54(s32 arg0, Mtx4F* arg1) {
    uvMat4Copy(&D_80261730[arg0].unk10, arg1);
}

void func_80204C94(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    UnkStruct_80204D94* temp_s0;
    temp_s0 = &D_80261730[arg0];
    temp_s0->unk1E8 = arg1;
    temp_s0->unk1EC = arg2;
    temp_s0->unk1F0 = arg3;
    temp_s0->unk1F4 = arg4;
    temp_s0->unk1F8 = arg5;
    temp_s0->unk1FC = arg6;
    uvMat4SetUnk2(&temp_s0->unk10, arg1, arg2, arg3, arg4, arg5, arg6);
    uvMat4CopyF2L(&temp_s0->unk50, &temp_s0->unk10);
    uvMat4SetUnk2(&temp_s0->unk90, arg1, arg2, arg3, arg4, arg5, 27000.0f);
    uvMat4CopyF2L(&temp_s0->unkD0, &temp_s0->unk90);
    func_802061A0(temp_s0);
}

void func_80204D94(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    UnkStruct_80204D94* temp_v0;
    temp_v0 = &D_80261730[arg0];
    temp_v0->unk38C = arg1;
    temp_v0->unk38E = arg2;
    temp_v0->unk390 = arg3;
    temp_v0->unk392 = arg4;
    uvGfxClipViewport(arg0, arg1, arg2, arg3, arg4);
}

void uvChanEnv(s32 arg0, s32 arg1) {
    if ((arg1 != 0xFFFF) && (gGfxUnkPtrs->unk44[arg1] == NULL)) {
        _uvDebugPrintf("uvChanEnv: environment %d not in level\n", arg1);
        return;
    }
    *(s16*)&D_80261732[arg0] = arg1;
}

void uvChanTerra(s32 arg0, s32 arg1) {
    if (gGfxUnkPtrs->unk4[arg1] == NULL) {
        _uvDebugPrintf("uvChanTerra: terra %d not in level\n");
        return;
    }
    *(s16*)&D_80261734[arg0] = arg1;
}

s32 func_80204EC0(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    f32 x, y, z, w;
    UnkStruct_80204D94* temp_v0;

    temp_v0 = &D_80261730[arg0];
    x = arg1 - temp_v0->unk110.m[3][0];
    y = arg2 - temp_v0->unk110.m[3][1];
    z = arg3 - temp_v0->unk110.m[3][2];
    w = arg4;
    if ((temp_v0->unk1FC + w) < uvSqrtF(x * x + y * y + z * z)) {
        return 0;
    }
    return func_80206F64(temp_v0->unk2E0, x, y, z, w);
}

u8* func_80204F9C(s32 arg0) {
    return (u8*)&D_80261730[arg0].unk374;
}

void func_80204FC4(s32 arg0) {
    func_80204FE4(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_58E0/func_80204FE4.s")

void func_80205724(s32 arg0, s32 arg1, Mtx4F* arg2) {
    switch (arg1) {
    case 1:
        uvMat4Copy(arg2, &D_80261730[arg0].unk110);
        return;
    case 2:
        uvMat4Copy(arg2, &D_80261730[arg0].unk10);
        return;
    case 3:
        uvMat4Copy(arg2, &D_80261730[arg0].unk190);
        return;
    }
}

void func_802057F4(Mtx4F* arg0, Mtx4F* arg1) {
    uvMat4UnkOp4(arg0, arg1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_58E0/_uvSortAdd.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_58E0/func_80205BFC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_58E0/func_80205CE4.s")
