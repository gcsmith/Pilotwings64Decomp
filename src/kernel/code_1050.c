#include <uv_audio.h>
#include <uv_matrix.h>

typedef struct UnkStruct_80200144 {
    Mtx4F_t mat;
    float vec[4];
} UnkStruct_80200144_t;

typedef struct UnkStruct_80200308 {
    f32 unk[0x14];
} UnkStruct_80200308_t;

extern UnkStruct_80200308_t D_80250EC4[];
extern UnkStruct_80200144_t D_80250E80[];

void func_802000DC(u16);
void uvEmitterFlush(u16);

void func_802000A0(void) {
    s32 var_s0;

    for (var_s0 = 0; var_s0 <= 0; var_s0 = (var_s0 + 1) & 0xFFFF) {
        func_802000DC(var_s0);
    }
}

void func_802000DC(u16 arg0) {
    Mtx4F_t mIdent;
    UnkStruct_80200144_t* temp_a0;

    temp_a0 = &D_80250E80[arg0];

    Mat4_SetIdentity(mIdent);
    Mat4_Copy(temp_a0->mat, mIdent);
    *(u32*)&temp_a0->vec[3] = 2;
    temp_a0->vec[0] = 1.0f;
    temp_a0->vec[1] = 1.0f;
}

void func_80200144(u16 arg0, Mtx4F_t arg1) {
    Mat4_Copy(D_80250E80[arg0].mat, arg1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/code_1050/func_80200180.s")

void func_80200308(u16 arg0) {
    uvEmitterFlush(arg0);
    uvaSeqSetVol(D_80250EC4[arg0].unk[0]);
}
