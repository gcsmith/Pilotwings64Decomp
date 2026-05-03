#include "common.h"
#include "code_51E30.h"
#include "code_7FE00.h"
#include "code_9A960.h"
#include "fdr.h"
#include "hang_glider.h"
#include "snd.h"
#include <uv_audio.h>
#include <uv_janim.h>
#include <uv_math.h>
#include <uv_model.h>

Unk80371120 D_80367A40;
Unk80371120 D_80367BF0;
Unk80371120 D_80367DA0;

// forward declarations
void func_802EF058(HangGliderData*, Unk80371120*, s32, Mtx4F*);

void func_802EE530(HangGliderData* hgData) {
    hgData->unk220 = 0.0f;
    hgData->unk224 = 0.0f;
    hgData->unk22C = 0.0f;
    hgData->unk228 = 1.0f;
    func_802CAA00(0, &hgData->unk220);
    func_802CAA00(1, &hgData->unk224);
    func_802CAA00(3, &hgData->unk22C);
    func_802CAA00(2, &hgData->unk228);
    func_802CAA00(4, &hgData->unk234);
    func_802CAA00(5, &hgData->unk240);
    func_802CAA00(6, &hgData->unk23C);
    func_802CAA00(7, &hgData->unk238);
    switch (hgData->unk8C) {
    case 0:
    case 2:
    case 3:
        hgData->unk21C = 3;
        hgData->unk20C = 0.0f;
        hgData->unk228 = 1.0f;
        break;
    case 1:
    case 4:
        hgData->unk21C = 1;
        hgData->unk20C = 1.0f;
        break;
    }
    hgData->unk234 = 0.0f;
    hgData->unk230 = 0.0f;
    hgData->unk238 = 0.0f;
    hgData->unk23C = 0.0f;
    hgData->unk240 = 0.0f;
    hgData->unk250 = 0;
}

void func_802EE640(HangGliderData* hgData) {
    f32 var_fa0;
    f32 var_fv0;
    s32 sp74;
    Mtx4F sp34;
    f32 var_fv1;

    sp74 = hgData->unk21C;
    if (hgData->unkF8 > 3 /*.0f*/ && hgData->unk80 == 0) {
        sp74 = 3;
    }
    if (hgData->unk88 > 0.05f && hgData->unkF8 > 3 /*.0f*/) {
        sp74 = 4;
    }
    if (hgData->unk88 > 0.95f && hgData->unkF8 < 3 /*.0f*/) {
        sp74 = 1;
        var_fa0 = (hgData->unk2DC * hgData->unk18C.y * D_8034F854);
        if (var_fa0 < 0.2f) {
            sp74 = 0;
        }
        if (hgData->unk18C.y < 0.5f) {
            sp74 = 5;
        }
    }
    hgData->unk21C = sp74;
    if (sp74 != 4) {
        if (hgData->unk220 != 0.0f) {
            hgData->unk220 = func_80313AF4(0.0f, hgData->unk220, 7.3f);
        }
    }
    if (sp74 != 0) {
        if (hgData->unk224 != 0.0f) {
            hgData->unk224 = func_80313AF4(0.0f, hgData->unk224, 3.0f);
        }
    }
    if (sp74 == 0 || sp74 == 1) {
        if (hgData->unk228 != 0.0f) {
            hgData->unk228 = func_80313AF4(0.0f, hgData->unk228, 6.0f);
        }
    }
    if (sp74 != 5) {
        if (hgData->unk22C != 0.0f) {
            hgData->unk22C = func_80313AF4(0.0f, hgData->unk22C, 7.3f);
        }
    }
    switch (sp74) {
    case 4:
        hgData->unk220 = func_80313AF4(1.0f, hgData->unk220, 7.3f);
        break;
    case 0:
        hgData->unk224 = func_80313AF4(1.0f, hgData->unk224, 3.0f);
        break;
    case 3:
        hgData->unk228 = func_80313AF4(1.0f, hgData->unk228, 6.0f);
        break;
    case 5:
        hgData->unk22C = func_80313AF4(1.0f, hgData->unk22C, 7.3f);
        break;
    }
    hgData->unk238 = (hgData->unk60 + 1.0f) * (1.0f / 2.0f);
    hgData->unk23C = (hgData->unk64 + 1.0f) * (1.0f / 2.0f);
    if (sp74 == 4) {
        var_fa0 = hgData->unk240 + (3.0f * D_8034F854);
        if (var_fa0 > 0.999f) {
            var_fa0 = 0.999f;
        }
        hgData->unk240 = func_80313AF4(var_fa0, hgData->unk240, 7.3f);
    } else {
        var_fa0 = hgData->unk240 - (3.0f * D_8034F854);
        if (var_fa0 < 0.0f) {
            var_fa0 = 0.0f;
        }
        hgData->unk240 = func_80313AF4(var_fa0, hgData->unk240, 7.3f);
    }
    var_fv1 = ABS_NOEQ(hgData->unk18C.y);
    var_fa0 = (var_fv1 * D_8034F854) / hgData->unk2DC;
    if (var_fa0 > 0.17f) {
        var_fa0 = 0.17f;
    }
    hgData->unk230 += var_fa0;
    while (hgData->unk230 > 2.0f) {
        hgData->unk230 -= 2.0f;
    }
    if (hgData->unk230 <= 1.0f) {
        hgData->unk234 = hgData->unk230;
    } else {
        hgData->unk234 = 2.0f - hgData->unk230;
    }
    func_802CAA90(hgData->objId);
    uvModelGetPosm(hgData->modelId, hgData->unk2E4, &sp34);
    uvMat4RotateAxis(&sp34, (hgData->unk60 * -1.0f) + hgData->unk68, 'z');
    uvMat4RotateAxis(&sp34, (hgData->unk64 * (1.0f / 5.0f)) + (1.0f / 5.0f) + hgData->unk6C, 'x');
    uvDobjPosm(hgData->objId, hgData->unk2E4, &sp34);
}

void func_802EEB00(HangGliderData* hgData, u8 arg1) {
    static f32 D_8034F1B0 = 0.0f;
    static f32 D_8034F1B4 = 1.0f;
    Mtx4F spB8;
    Mtx4F sp78;
    Mtx4F sp38;
    f32 sp34;
    Unk80362690_Unk0* sp30;

    sp30 = &D_80362690->unkC[D_80362690->unk9C];
    if (hgData->unk8C == 3) {
        func_802F041C(hgData);
        return;
    }
    if (fdr_802E6B5C() == 3) {
        return;
    }
    if (fdr_802E6B5C() == 4) {
        return;
    }

    if (hgData->unk251 == 0) {
        if (arg1 != 0) {
            hgData->unk251 = 2;
            func_8033F748(5);
            func_8033F964(0);
            func_8033FCD0(sp30->veh);
            uvEventPost(0x12, 0);
        } else {
            hgData->unk251 = 1;
            if (hgData->unk5C != 0) {
                func_8033F748(5);
            } else {
                func_8033F748(6);
            }
            func_8033F964(0);
            func_8033FCD0(sp30->veh);
            uvEventPost(0x12, 0);
        }
        hgData->unk254 = 0.0f;
        D_8034F1B0 = 0.0f;
        uvDobj_802180DC(hgData->objId, &D_80367A40);
    }
    sp34 = hgData->unk254 / 3.0f;

    // clang-format off
    if (sp34 < 0.0f) { sp34 = 0.0f; } else if (sp34 > 1.0f) { sp34 = 1.0f; }
    // clang-format on

    hgData->unk254 += D_8034F854;
    switch (hgData->unk251) {
    case 2:
        D_8034F1B0 += D_8034F1B4 * D_8034F854;
        if ((D_8034F1B0 >= 1.0f) && (D_8034F1B4 > 0.0f)) {
            D_8034F1B4 = -D_8034F1B4;
            D_8034F1B0 = 1.0f;
        }
        if (D_8034F1B0 <= 0.0f && D_8034F1B4 < 0.0f) {
            D_8034F1B4 = -D_8034F1B4;
            D_8034F1B0 = 0.0f;
        }
        uvJanimPoseLine(&D_80367BF0, hgData->unk2ED, D_8034F1B0);
        func_802006FC(&D_80367DA0, &D_80367A40, &D_80367BF0, sp34);
        func_802EF058(hgData, &D_80367DA0, hgData->unk2E5, &sp78);
        uvMat4SetIdentity(&sp38);
        uvMat4LocalTranslate(&sp38, sp78.m[3][0], sp78.m[3][1], sp78.m[3][2]);
        uvMat4RotateAxis(&sp38, 1.57f, 'x');
        uvMat4LocalTranslate(&sp38, -sp78.m[3][0], -sp78.m[3][1], -sp78.m[3][2]);
        uvMat4MulBA(&sp78, &sp38, &sp78);
        uvDobjPosm(hgData->objId, hgData->unk2E5, &sp78);
        func_802EF058(hgData, &D_80367DA0, hgData->unk2E6, &sp78);
        uvDobjPosm(hgData->objId, hgData->unk2E6, &sp78);
        func_802EF058(hgData, &D_80367DA0, hgData->unk2E7, &sp78);
        uvDobjPosm(hgData->objId, hgData->unk2E7, &sp78);
        break;
    case 1:
        uvModelGetPosm(hgData->modelId, hgData->unk2E4, &spB8);
        uvMat4RotateAxis(&spB8, -0.2f, 'x');
        uvMat4RotateAxis(&spB8, uvCosF(2.0f * hgData->unk254), 0x7A);
        uvDobjPosm(hgData->objId, hgData->unk2E4, &spB8);
        uvDobj_802180DC(hgData->objId, &D_80367BF0);
        func_802006FC(&D_80367DA0, &D_80367A40, &D_80367BF0, sp34);
        func_80200638(hgData->objId, &D_80367DA0);
        break;
    }
}

void func_802EEF0C(HangGliderData* hgData) {
    static f32 D_80367F50;
    f32 var_fa0;
    f32 var_fa1;
    f32 var_fv0;
    Unk80371120 sp34;
    Unk80362690_Unk0* sp30;

    sp30 = &D_80362690->unkC[D_80362690->unk9C];
    if (hgData->unk250 == 0) {
        hgData->unk250 = 1;
        var_fa0 = hgData->unk10.m[3][0];
        var_fa1 = hgData->unk10.m[3][1];
        var_fv0 = hgData->unk10.m[3][2];
        if (hgData->unkE8 != 0) {
            func_802F8AB8(var_fa0, var_fa1, var_fv0, 8.0f, &hgData->unk1A4);
            hgData->camera->unk6 = hgData->unk2 = 0;
            uvDobjState(hgData->objId, hgData->unk2);
            uvMat4Copy(&hgData->camera->unk80, &hgData->unk10);
            sndPlaySfx(SFX_WATER_SPLASH);
            if (!(hgData->unk318 & 0x10)) {
                func_8033F748(7U);
                func_8033F964(0);
                func_8033FCD0(sp30->veh);
            }
            uvEventPost(0x12, 0);
        }
        D_80367F50 = 0.0f;
    }
    if (hgData->unkE8 == 0) {
        D_80367F50 += 0.25f * D_8034F854;
        uvJanimPoseLine(&sp34, hgData->unk2EE, D_80367F50);
        func_80200638(hgData->objId, &sp34);
    }
}

void func_802EF058(HangGliderData* hgData, Unk80371120* arg1, s32 partId, Mtx4F* arg3) {
    s32 sp2C;
    s32 i;

    sp2C = -1;
    for (i = 0; i < ARRAY_COUNT(arg1->unk190) && sp2C == -1; i++) {
        if (partId == arg1->unk190[i]) {
            sp2C = i;
        }
    }
    if (partId != arg1->unk190[sp2C]) {
        _uvDebugPrintf("Part ID Mismatch %d != %d\n", arg1->unk190[sp2C], hgData->unk2E5);
        uvMat4SetIdentity(arg3);
        return;
    }
    uvModelGetPosm(hgData->modelId, partId, arg3);
    uvMat4SetQuaternionRotation(arg3, arg1->unk0[sp2C].unk0, arg1->unk0[sp2C].unk4, arg1->unk0[sp2C].unk8, arg1->unk0[sp2C].unkC);
}
