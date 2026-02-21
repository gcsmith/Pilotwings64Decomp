#include "common.h"
#include <uv_util.h>
#include <uv_memory.h>
#include <uv_filesystem.h>
#include <uv_vector.h>
#include "code_9A960.h"
#include "code_A6000.h"
#include "code_D19D0.h"

static s32 func_8034A4A0(void) {
    s32 i;

    for (i = 0; i < 6; i++) {
        if (D_8037DCA0[i].unk350 == 0) {
            return i;
        }
    }

    _uvDebugPrintf("UserPaths : Too many outstanding paths\n");
    return -1;
}

Unk8037DCA0* func_8034A4F8(s32 arg0) {
    Unk8037DCA0* temp_s0;
    s32 temp_v0;
    u32 sp8C;
    void* sp88;
    s32 temp_v0_2;
    s32 pad;
    s32 var_s3;
    s32 j;
    s32 var_v0;
    UnkTranslatStruct_Unk8* var_a1;
    UnkQuatStruct_Unk8* var_v1;
    UnkCommStruct* temp1;
    UnkQuatStruct* temp2;
    UnkTranslatStruct* temp3;
    s32 i;
    s32 temp_v1;

    var_s3 = 0;
    temp_v0 = func_8034A4A0();
    if (temp_v0 == -1) {
        return NULL;
    }
    temp_s0 = &D_8037DCA0[temp_v0];
    temp_s0->unk38 = temp_v0;
    temp_s0->unk350 = 1;
    temp_v0_2 = uvFileReadHeader(func_802314D0(arg0, 2));
    var_v0 = uvFileReadBlock(temp_v0_2, &sp8C, &sp88, 1);
    while (var_v0) {
        switch (var_v0) {
        case 'COMM':
            temp1 = sp88;
            var_s3 = temp1->unk0;
            temp_v1 = temp1->unk4;
            temp_s0->unk22 = temp1->unkC;
            temp_s0->unk3C = temp1->unk10;
            temp_s0->unk20 = (temp_v1 - var_s3) + 1;
            temp_s0->unk24 = temp1->unk14;
            temp_s0->unk23 = temp_s0->unk20;
            break;
        case 'QUAT':
            temp2 = sp88;
            temp_s0->unk8 = temp2->count;
            temp_s0->unk4 = temp2->unk4;
            temp_s0->unk0 = 0;
            temp_s0->unkC = _uvMemAllocAlign8(temp_s0->unk8 * 0x14);

            var_v1 = temp2->unk8;
            for (i = 0; i < temp_s0->unk8; i++) {
                temp_s0->unkC[i].unk0.x = var_v1[i].unk0.x;
                temp_s0->unkC[i].unk0.y = var_v1[i].unk0.y;
                temp_s0->unkC[i].unk0.z = var_v1[i].unk0.z;
                temp_s0->unkC[i].unk0.w = var_v1[i].unk0.w;
                temp_s0->unkC[i].unk10_0 = var_v1[i].unk10 - var_s3;
                temp_s0->unkC[i].unk10_15 = 1;
                if (temp_s0->unk20 <= (var_v1[i].unk10 - var_s3) + 1) {
                    temp_s0->unk20 = (var_v1[i].unk10 - var_s3) + 1;
                }
            }
            break;
        case 'XLAT':
            temp3 = sp88;
            temp_s0->unk18 = temp3->count;
            temp_s0->unk14 = temp3->unk4;
            temp_s0->unk10 = 0;
            temp_s0->unk1C = _uvMemAllocAlign8(temp_s0->unk18 * 0x10);
            var_a1 = temp3->unk8;
            for (i = 0; i < temp_s0->unk18; i++) {
                temp_s0->unk1C[i].unk0.x = var_a1[i].unk0.x;
                temp_s0->unk1C[i].unk0.y = var_a1[i].unk0.y;
                temp_s0->unk1C[i].unk0.z = var_a1[i].unk0.z;
                temp_s0->unk1C[i].unkC = var_a1[i].unkC - var_s3;
                if (i == 0) {
                    for (j = 0; j < 3; j++) {
                        temp_s0->unk1DC.f[j] = var_a1[i].unk0.f[j];
                    }
                }

                if (temp_s0->unk20 <= (var_a1[i].unkC - var_s3) + 1) {
                    temp_s0->unk20 = (var_a1[i].unkC - var_s3) + 1;
                }
            }
            break;
        default:
            break;
        }
        var_v0 = uvFileReadBlock(temp_v0_2, &sp8C, &sp88, 1);
    }
    uvFile_80223F30(temp_v0_2);
    return temp_s0;
}

void func_8034A840(s32 path) {
    if (D_8037DCA0[path].unk350 != 1) {
        _uvDebugPrintf("UserPaths: Freed unused path %d\n", path);
        return;
    }
    D_8037DCA0[path].unk350 = 0;
}

void func_8034A8B0(Unk8037DCA0* arg0, u8 arg1, f32 arg2) {
    if (arg1) {
        arg0->unk40 = 1;
    } else {
        arg0->unk40 = 0;
        arg0->unk44 = 0.0f;
        arg0->unk48 = 0.0f;
    }
    arg0->unk44 += D_8034F854;
    arg0->unk48 = arg2;
    uvPathPoseLine(&D_8037F098, arg0, arg2);
    func_8031EE48(arg0->unk352, &D_8037F098, 1.0f, 1.0f, 1.0f);
}

void func_8034A950(Unk8034A950 arg0, f32* arg183) {
    arg183[0] = arg0.unk190.f[0];
    arg183[1] = arg0.unk190.f[1];
    arg183[2] = arg0.unk190.f[2];
    arg183[3] = arg0.unk0.f[0];
    arg183[4] = arg0.unk0.f[1];
    arg183[5] = arg0.unk0.f[2];
    arg183[6] = arg0.unk0.f[3];
}
