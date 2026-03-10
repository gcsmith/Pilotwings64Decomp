#include "common.h"
#include <uv_math.h>
#include <uv_graphics.h>
#include <uv_vector.h>
#include "kernel/code_7150.h"

void func_802061A0(UnkStruct_80204D94* arg0) {
    Vec3F* temp_s1;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv1;
    u8 i;
    Vec3F* temp_s0;

    temp_fa1 = (arg0->unk1E8 / arg0->unk1F8) * arg0->unk1FC;
    temp_fa0 = (arg0->unk1EC / arg0->unk1F8) * arg0->unk1FC;
    temp_ft4 = (arg0->unk1F0 / arg0->unk1F8) * arg0->unk1FC;
    temp_ft5 = (arg0->unk1F4 / arg0->unk1F8) * arg0->unk1FC;
    arg0->unk208[0].x = temp_fa0;
    arg0->unk208[0].y = arg0->unk1FC;
    arg0->unk208[0].z = temp_ft4;
    arg0->unk208[1].x = temp_fa0;
    arg0->unk208[1].y = arg0->unk1FC;
    arg0->unk208[1].z = temp_ft5;
    arg0->unk208[2].x = temp_fa1;
    arg0->unk208[2].y = arg0->unk1FC;
    arg0->unk208[2].z = temp_ft5;
    arg0->unk208[3].x = temp_fa1;
    arg0->unk208[3].y = arg0->unk1FC;
    arg0->unk208[3].z = temp_ft4;
    arg0->unk238.x = 0.0f;
    arg0->unk238.y = arg0->unk1FC;
    arg0->unk238.z = 0.0f;
    arg0->unk244.x = 0.0f;
    arg0->unk244.y = 0.0f;
    arg0->unk244.z = 0.0f;
    for (i = 0; i < 4; i++) {
        temp_s1 = &arg0->unk298[i];
        uvVec3Cross(temp_s1, &arg0->unk208[(i + 1) % 4], &arg0->unk208[i]);
        uvVec3Normal(temp_s1, temp_s1);
    }
    temp_s0 = &arg0->unk2C8;
    uvVec3Copy(temp_s0, &arg0->unk238);
    uvVec3Normal(temp_s0, temp_s0);
    arg0->unk2D4.x = -temp_s0->x;
    arg0->unk2D4.y = -temp_s0->y;
    arg0->unk2D4.z = -temp_s0->z;
}

void func_80206318(UnkStruct_80204D94* arg0) {
    s32 temp_v0;
    Vec3F* temp_a2;
    Vec3F* sp94[5];
    Mtx4F sp54;
    u8 i;
    u8 sp52;

    uvMat4Copy(&sp54, &arg0->unk110);

    for (i = 0; i < 6; i++) {
        uvMat4LocalToWorld(&sp54, &arg0->unk250[i], &arg0->unk208[i]);
    }

    sp54.m[3][0] = sp54.m[3][1] = sp54.m[3][2] = 0.0f;
    for (i = 0; i < 6; i++) {
        uvMat4LocalToWorld(&sp54, &arg0->unk2E0[i], &arg0->unk298[i]);
    }

    if (gGfxUnkPtrs->terras[arg0->unk4] == NULL) {
        return;
    }

    temp_a2 = arg0->unk250;

    if (FABS(arg0->unk190.m[1][2]) <= 0.0001f) {
        temp_v0 = func_80206594(&temp_a2[0], &temp_a2[1], &temp_a2[2], &temp_a2[3]);
        switch (temp_v0) {
        case 0:
            sp94[0] = &temp_a2[5];
            sp94[1] = &temp_a2[1];
            sp94[2] = &temp_a2[3];
            break;
        case 1:
            sp94[0] = &temp_a2[5];
            sp94[1] = &temp_a2[2];
            sp94[2] = &temp_a2[0];
            break;
        case 2:
            sp94[0] = &temp_a2[5];
            sp94[1] = &temp_a2[3];
            sp94[2] = &temp_a2[1];
            break;
        case 3:
            sp94[0] = &temp_a2[5];
            sp94[1] = &temp_a2[0];
            sp94[2] = &temp_a2[2];
            break;
        }
        sp52 = 3;
    } else {
        sp94[0] = &temp_a2[0];
        sp94[1] = &temp_a2[1];
        sp94[2] = &temp_a2[2];
        sp94[3] = &temp_a2[3];
        sp94[4] = &temp_a2[5];
        sp52 = 5;
        func_80206610(gGfxUnkPtrs->terras[arg0->unk4], &temp_a2[5], &temp_a2[0], &temp_a2[1], &temp_a2[2], &temp_a2[3]);
        func_80206B58(sp94, &sp52);
    }

    for (i = 0; i < sp52; i++) {
        arg0->unk328[i].x = sp94[i]->x;
        arg0->unk328[i].y = sp94[i]->y;
    }
    arg0->unk370 = sp52;
}

u16 func_80206594(Vec3F* arg0, Vec3F* arg1, Vec3F* arg2, Vec3F* arg3) {
    f32 var_fv1;
    f32 var_fv0;
    u16 var_v1;

    var_fv0 = 1000000.0f;
    var_v1 = 0;

    var_fv1 = arg0->z;
    if (var_fv1 < var_fv0) {
        var_fv0 = var_fv1;
    }

    var_fv1 = arg1->z;
    if (var_fv1 < var_fv0) {
        var_fv0 = var_fv1;
        var_v1 = 1;
    }

    var_fv1 = arg2->z;
    if (var_fv1 < var_fv0) {
        var_fv0 = var_fv1;
        var_v1 = 2;
    }
    var_fv1 = arg3->z;
    if (var_fv1 < var_fv0) {
        var_v1 = 3;
    }
    return var_v1;
}

void func_80206610(ParsedUVTR* arg0, Vec3F* arg1, Vec3F* arg2, Vec3F* arg3, Vec3F* arg4, Vec3F* arg5) {
    s32 var_v0;
    s32 var_v1;
    f32 var_fv0;
    f32 var_fv1;

    var_fv0 = arg0->unk0.unk14;
    var_fv1 = arg0->unk0.unk8;
    var_v0 = 0;
    var_v1 = 0;
    if (var_fv0 <= arg2->z) {
        var_v1++;
    } else if (arg2->z <= var_fv1) {
        var_v0++;
    }
    if (var_fv0 <= arg3->z) {
        var_v1++;
    } else if (arg3->z <= var_fv1) {
        var_v0++;
    }
    if (var_fv0 <= arg4->z) {
        var_v1++;
    } else if (arg4->z <= var_fv1) {
        var_v0++;
    }
    if (var_fv0 <= arg5->z) {
        var_v1++;
    } else if (arg5->z <= var_fv1) {
        var_v0++;
    }

    if (var_fv0 < arg1->z) {
        if (!((var_fv0 <= arg2->z) && (var_fv0 <= arg3->z) && (var_fv0 <= arg4->z) && (var_fv0 <= arg5->z)) && (var_v0 == 4)) {
            if (arg2->z <= var_fv1) {
                func_80206A9C(arg1, var_fv1, arg2);
            }
            if (arg3->z <= var_fv1) {
                func_80206A9C(arg1, var_fv1, arg3);
            }
            if (arg4->z <= var_fv1) {
                func_80206A9C(arg1, var_fv1, arg4);
            }
            if (arg5->z <= var_fv1) {
                func_80206A9C(arg1, var_fv1, arg5);
            }
        }
    } else if (arg1->z < var_fv1) {
        if (!((arg2->z <= var_fv1) && (arg3->z <= var_fv1) && (arg4->z <= var_fv1) && (arg5->z <= var_fv1)) && (var_v1 == 4)) {
            if (var_fv0 <= arg2->z) {
                func_80206A9C(arg1, var_fv0, arg2);
            }
            if (var_fv0 <= arg3->z) {
                func_80206A9C(arg1, var_fv0, arg3);
            }
            if (var_fv0 <= arg4->z) {
                func_80206A9C(arg1, var_fv0, arg4);
            }
            if (var_fv0 <= arg5->z) {
                func_80206A9C(arg1, var_fv0, arg5);
            }
        }
    } else if ((var_v1 == 0) || (var_v0 == 0)) {
        if (var_v1 == 4) {
            if (var_fv0 <= arg2->z) {
                func_80206A9C(arg1, var_fv0, arg2);
            }
            if (var_fv0 <= arg3->z) {
                func_80206A9C(arg1, var_fv0, arg3);
            }
            if (var_fv0 <= arg4->z) {
                func_80206A9C(arg1, var_fv0, arg4);
            }
            if (var_fv0 <= arg5->z) {
                func_80206A9C(arg1, var_fv0, arg5);
            }
        } else if (var_v0 == 4) {
            if (arg2->z <= var_fv1) {
                func_80206A9C(arg1, var_fv1, arg2);
            }
            if (arg3->z <= var_fv1) {
                func_80206A9C(arg1, var_fv1, arg3);
            }
            if (arg4->z <= var_fv1) {
                func_80206A9C(arg1, var_fv1, arg4);
            }
            if (arg5->z <= var_fv1) {
                func_80206A9C(arg1, var_fv1, arg5);
            }
        }
    }
}

void func_80206A9C(Vec3F* arg0, f32 arg1, Vec3F* arg2) {
    f32 temp_fv0;
    Vec3F sp18;

    sp18.x = arg2->x - arg0->x;
    sp18.y = arg2->y - arg0->y;
    sp18.z = arg2->z - arg0->z;
    uvVec3Normal(&sp18, &sp18);
    temp_fv0 = (arg1 - arg0->z) / sp18.z;
    arg2->x = arg0->x + (sp18.x * temp_fv0);
    arg2->y = arg0->y + (sp18.y * temp_fv0);
    arg2->z = arg0->z + (sp18.z * temp_fv0);
}

void func_80206B58(Vec3F** arg0, u8* arg1) {
    Vec3F* sp104[5] = { NULL, NULL, NULL, NULL, NULL };
    Vec3F* temp_v0;
    Vec3F* var_s4;
    Vec3F spC0[5];
    Vec3F spB4;
    Vec3F spA8 = { 0 };
    s32 spA4;
    s32 var_s1;
    f32 temp_fv0;
    u8 sp9B;
    u8 temp_v1;
    f32 var_fs0;
    s32 var_fp;
    s32 sp7C[5];
    Vec3F* temp_v1_2;

    var_fp = 0;
    var_fs0 = 1000000.0f;
    temp_v1 = *arg1;
    // FAKE should chain assign all 5
    sp7C[0] = sp7C[1] = sp7C[2] = sp7C[3] = 0;
    sp7C[4] = 0;

    for (spA4 = 0; spA4 < temp_v1; spA4++) {
        var_s4 = arg0[spA4];
        if (var_s4->x < var_fs0) {
            var_fs0 = var_s4->x;
            var_fp = spA4;
        }
    }

    var_s4 = arg0[var_fp];
    sp104[0] = var_s4;
    spB4.x = 0.0f;
    spB4.y = 1.0f;
    spB4.z = 0.0f;

    sp9B = 1;
    for (spA4 = 1; spA4 < temp_v1; spA4++) {
        var_fs0 = 1000000.0f;

        for (var_s1 = 0; var_s1 < temp_v1; var_s1++) {
            if (sp7C[var_s1] != 0) {
                continue;
            }
            temp_v0 = arg0[var_s1];
            spA8.x = temp_v0->x - var_s4->x;
            spA8.y = temp_v0->y - var_s4->y;
            spA8.z = 0.0f;
            if (uvVec3Normal(&spC0[var_s1], &spA8) != 0) {
                temp_fv0 = uvVec2Dot(&spB4, &spC0[var_s1]);
                if (temp_fv0 < var_fs0) {
                    var_fs0 = temp_fv0;
                    var_fp = var_s1;
                }
            }
        }

        temp_v1_2 = arg0[var_fp];
        if (temp_v1_2 == sp104[0]) {
            break;
        }

        var_s4 = sp104[spA4] = temp_v1_2;
        sp7C[var_fp] = 1;

        spB4.x = -spC0[var_fp].x;
        spB4.y = -spC0[var_fp].y;
        spB4.z = 0.0f;
        sp9B++;
    }

    for (spA4 = 0; spA4 < sp9B; spA4++) {
        arg0[spA4] = sp104[spA4];
    }

    *arg1 = sp9B;
}

s32 func_80206F64(Vec3F* arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    f32 temp_fv0;
    u16 var_v0;
    u16 i;
    Vec3F* temp_a1;

    var_v0 = 0;
    for (i = 0; i < 5; i++) {
        temp_a1 = &arg0[i];
        temp_fv0 = (temp_a1->x * arg1) + (temp_a1->y * arg2) + (temp_a1->z * arg3);
        if ((temp_fv0 + arg4) < 0.0f) {
            return 0;
        }
        if (arg4 < temp_fv0) {
            var_v0++;
        }
    }
    if (var_v0 == 5) {
        return 2;
    }
    return 1;
}

s32 func_80207028(Vec3F* arg0, Vec3F* arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    f32 temp_fv0;
    f32 temp_fv1;
    f32 temp_ft4;
    f32 temp_ft5;
    Vec3F* vec;

    temp_fv0 = (arg2 - arg0[4].x);
    temp_fv1 = (arg3 - arg0[4].y);
    temp_ft4 = (arg4 - arg0[4].z);

    vec = &arg1[4];

    temp_ft5 = (vec->x * temp_fv0) + (vec->y * temp_fv1) + (vec->z * temp_ft4);
    if (arg5 < temp_ft5) {
        return 0;
    }
    if ((temp_ft5 + arg5) < 0.0f) {
        return 2;
    }
    return 1;
}

void func_802070B8(UnkStruct_80204D94* arg0, UnkStruct_80204D94_Unk374* arg1) {
    Vec3F* temp_a0;
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;
    u16 i;
    s32 temp_a2;

    temp_a0 = arg0->unk328;
    i = 0;
    temp_a2 = arg0->unk370;

    arg1->unk0 = arg1->unk4 = arg1->unk8 = 1e10f;
    arg1->unkC = arg1->unk10 = arg1->unk14 = -1e10f;
    while (i < temp_a2) {
        temp_fv0 = temp_a0[i].x;
        temp_fv1 = temp_a0[i].y;
        temp_fa0 = temp_a0[i].z;
        if (arg1->unk0 > temp_fv0) {
            arg1->unk0 = temp_fv0;
        }
        if (arg1->unkC < temp_fv0) {
            arg1->unkC = temp_fv0;
        }
        if (arg1->unk4 > temp_fv1) {
            arg1->unk4 = temp_fv1;
        }
        if (arg1->unk10 < temp_fv1) {
            arg1->unk10 = temp_fv1;
        }
        if (arg1->unk8 > temp_fa0) {
            arg1->unk8 = temp_fa0;
        }
        if (arg1->unk14 < temp_fa0) {
            arg1->unk14 = temp_fa0;
        }
        i++;
    }
}
