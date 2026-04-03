#include "common.h"
#include "code_51E30.h"
#include "code_61A60.h"
#include "code_66160.h"
#include "code_9A960.h"
#include <uv_math.h>
#include <uv_texture.h>
#include <uv_janim.h>
#include "game.h"
#include "demo.h"
#include "falco.h"
#include "hud.h"
#include "snd.h"
#include "splash.h"
#include "task.h"
#include "text_data.h"
#include <uv_fx.h>
#include <uv_model.h>

typedef struct {
    Vec3F unk0;
    f32 unkC;
} FalcoDomain;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    FalcoDomain* domain;
    u8 pad14[0x80 - 0x14];
    f32 unk80;
    f32 unk84;
    f32 unk88;
    Vec3F unk8C;
    f32 unk98;
    Vec3F unk9C;
    Vec3F unkA8;
    Vec3F unkB4;
    u8 padC0[4];
    f32 unkC4;
    f32 unkC8;
    f32 unkCC;
    f32 unkD0;
    f32 unkD4;
    f32 unkD8;
    f32 unkDC;
    f32 unkE0;
    f32 unkE4;
    f32 unkE8;
    f32 unkEC;
    f32 unkF0;
    f32 unkF4;
    f32 unkF8;
    f32 unkFC;
    f32 unk100;
    f32 unk104;
    f32 unk108;
    f32 unk10C;
    f32 unk110;
    f32 unk114;
    f32 unk118;
    f32 unk11C;
    f32 unk120;
    f32 unk124;
    f32 unk128;
    f32 unk12C;
    f32 unk130;
    f32 unk134;
    f32 unk138;
    f32 unk13C;
    f32 unk140;
    f32 unk144;
    f32 unk148;
    f32 unk14C;
    f32 unk150;
    f32 unk154;
    f32 unk158;
    f32 unk15C;
    f32 unk160;
    f32 unk164;
    f32 unk168;
    Mtx4F unk16C;
    Mtx4F unk1AC;
    Mtx4F unk1EC;
    s32 pad22C;
    Vec3F unk230;
    s32 unk23C;
    s32 unk240;
    f32 unk244;
    s32 unk248;
    s32 unk24C;
    f32 unk250;
    u8 unk254;
    u8 unk255;
    u8 unk256;
    u8 pad257[1];
} Falco; // size = 0x258

typedef struct {
    s32 unk0;
    s32 radarIdx; // maybe u8
    Mtx4F unk8;
    Vec3F unk48;
    f32 unk54;
    f32 unk58;
    u8 pad5C;
    u8 unk5D;
    u8 pad5E;
    u8 pad5F;
} Unk8035A920; // size = 0x60

// .bss
extern s32 D_8035A5F0;
extern Falco sFalcos[1];
extern FalcoDomain sFalcoDomains[12];
extern s32 sFalcoCount;
extern s32 D_8035A918;
extern Unk8035A920 D_8035A920[16];
extern TaskFALC* sRefFALC;
extern f32 D_8035AF30;
extern f32 D_8035AF34;
extern f32 D_8035AF38;
extern f32 D_8035AF3C;
extern f32 D_8035AF40;
extern f32 D_8035AF44;
extern f32 D_8035AF48;
extern f32 D_8035AF4C;
extern f32 D_8035AF50;
extern f32 D_8035AF54;
extern f32 D_8035AF58;

// forward declarations
void falco_802E38F0(Falco*, TaskFALC*);
void falco_802E478C(Falco*, FalcoDomain*);
void falco_802E5F44(Unk8035A920*);
void falco_802E43C4(Falco*);
void falco_802E4AA8(Falco*);
void falco_802E4E70(Falco*);
void falco_802E55A0(Falco*);
void falco_802E587C(Falco*);
void falco_802E5D78(Unk8035A920*);
void falco_802E63BC(Falco*, Mtx4F*);
Unk8035A920* falco_802E5AFC(void);
void falco_802E5BF8(Unk8035A920*, Falco*);
void falco_802E61E4(Falco*);
void falco_802E62E4(Falco*);
void falco_802E6380(Falco*);
void falco_802E6344(Falco*);
void falco_802E5F90(Unk8035A920*);
void falco_802E6284(Falco*);
void falco_802E6184(Falco*);

void falcoInit(void) {
    Falco* falco;
    s32 i;

    if (D_80362690->unkA4 != 0) {
        uvRandSeed(13);
    } else {
        uvRandSeed((s32)(demoRandF() * 32768.0f) | 1);
    }

    for (i = 0; i < ARRAY_COUNT(sFalcos); i++) {
        falco = &sFalcos[i];
        falco->unk0 = 0xFFFF;
        falco->unk4 = 0xFFFF;
        falco->unk8 = 0xFFFF;
        falco->unk23C = 0;
        falco->unk244 = 0.0f;
        falco->unk255 = 0;
        falco->unk254 = 0;
        falco->unkC4 = 0.0f;
        falco->unkC8 = 50.0f;
        falco->unkCC = 27.63f;
        falco->unk256 = 0;
        falco->unk230.x = 0.0f;
        falco->unk230.y = 0.0f;
        falco->unk230.z = 1.0f;
        falco->unk9C.z = 0.0f;
        falco->unkA8.z = 0.0f;
        falco->unkB4.z = 0.0f;
        falco->unk88 = 0.0f;
        falco->unk80 = 0.0f;
        falco->unk84 = 0.0f;
        falco->unk24C = 0;
    }

    for (i = 0; i < ARRAY_COUNT(D_8035A920); i++) {
        D_8035A920[i].unk0 = 0xFFFF;
    }

    sFalcoCount = D_8035A918 = D_8035A5F0 = 0;
}

void falco_802E38F0(Falco* falco, TaskFALC* arg1) {
    if (falco->unk255 == 0) {
        falco->unk240 = 1;
        uvMat4SetIdentity(&falco->unk1AC);
        uvMat4SetIdentity(&falco->unk16C);
        falco->unk16C.m[3][0] = arg1->unk0.x;
        falco->unk16C.m[3][1] = arg1->unk0.y;
        falco->unk16C.m[3][2] = arg1->unk0.z;
        falco->unk1AC.m[3][0] = arg1->unk0.x;
        falco->unk1AC.m[3][1] = arg1->unk0.y;
        falco->unk1AC.m[3][2] = 0.0f;
    }
    falco->unk4 = uvDobjAllocIdx();
    uvDobjModel(falco->unk4, MODEL_GIANT_TRANSPARENT_MECCA_HAWK);
    uvDobjPosm(falco->unk4, 0, &falco->unk16C);
    uvDobjState(falco->unk4, falco->unk256 != 0 ? 2 : 0);
    falco->unk8 = uvDobjAllocIdx();
    uvDobjModel(falco->unk8, MODEL_GIANT_RED_THING);
    uvDobjPosm(falco->unk8, 0, &falco->unk1AC);
    uvDobjState(falco->unk8, falco->unk256 != 0 ? 0x22 : 0);
    falco->unk0 = uvDobjAllocIdx();
    uvDobjModel(falco->unk0, MODEL_MECCA_HAWK);
    uvDobjPosm(falco->unk0, 0, &falco->unk16C);
    uvDobjState(falco->unk0, 3);
    if (falco->unk254 == 0) {
        falco->unkC = hudAddWaypoint(arg1->unk0.x, arg1->unk0.y, arg1->unk0.z);
    }
}

void falcoLoad(void) {
    Falco* pFalco;
    TaskFALC* falc;
    FalcoDomain* falcoDomain;
    s32 falcoCount;
    s32 i;

    if (D_80362690->unkA0 == 0) {
        return;
    }

    sFalcoCount = taskGetFALC(&sRefFALC);
    if (sFalcoCount > ARRAY_COUNT(sFalcoDomains)) {
        _uvDebugPrintf("falcos : too many falcos domains defined in level [%d]\n", sFalcoCount);
        sFalcoCount = 0;
        return;
    }

    if (sFalcoCount <= 0) {
        return;
    }

    D_8035A5F0 = 1;
    uvLevelAppend(0x14);

    falcoCount = 0;
    for (i = 0; i < sFalcoCount; i++) {
        falc = &sRefFALC[i];
        falcoDomain = &sFalcoDomains[i];
        if (falcoCount < ARRAY_COUNT(sFalcos)) {
            pFalco = &sFalcos[falcoCount];
        } else {
            _uvDebugPrintf("ERROR: too many falcos defined in task.  Max of %d falcos\n", ARRAY_COUNT(sFalcos));
            pFalco = sFalcos;
        }
        uvVec3Copy(&falcoDomain->unk0, &falc->unk0);
        falcoDomain->unkC = falc->unkC;
        if (falc->unk10 != 0) {
            if (pFalco->unk255 == 0) {
                falco_802E478C(pFalco, falcoDomain);
            }
            falco_802E38F0(pFalco, falc);
            pFalco->unk255 = 1;
            pFalco->unkD4 = falc->unk11 / 100.0f;
            pFalco->unkD8 = (falc->unk12 + falc->unk11) / 100.0f;
            pFalco->unkDC = (falc->unk12 + falc->unk11 + falc->unk13) / 100.0f;
            pFalco->unkE0 = falc->unk18;
            pFalco->unkE4 = falc->unk1C - falc->unk18;
            pFalco->unkE8 = falc->unk20;
            pFalco->unkEC = falc->unk24 - falc->unk20;
            pFalco->unkF0 = falc->unk28;
            pFalco->unkF4 = falc->unk2C - falc->unk28;
            pFalco->unkF8 = falc->unk30;
            pFalco->unkFC = falc->unk34 - falc->unk30;
            pFalco->unk100 = falc->unk38;
            pFalco->unk104 = falc->unk3C - falc->unk38;
            pFalco->unk108 = falc->unk40;
            pFalco->unk10C = falc->unk44 - falc->unk38;
            pFalco->unk110 = falc->unk48;
            pFalco->unk114 = falc->unk4C - falc->unk48;
            pFalco->unk118 = falc->unk50;
            pFalco->unk11C = falc->unk54 - falc->unk50;
            pFalco->unk120 = falc->unk58;
            pFalco->unk124 = falc->unk5C - falc->unk58;
            pFalco->unk128 = falc->unk60;
            pFalco->unk12C = falc->unk64 - falc->unk60;
            pFalco->unk130 = falc->unk68;
            pFalco->unk134 = falc->unk6C - falc->unk68;
            pFalco->unk138 = falc->unk70;
            pFalco->unk13C = falc->unk74 - falc->unk70;
            pFalco->unk140 = falc->unk78;
            pFalco->unk144 = falc->unk7C - falc->unk78;
            pFalco->unk148 = falc->unk80;
            pFalco->unk14C = falc->unk84 - falc->unk80;
            pFalco->unk150 = falc->unk88;
            pFalco->unk154 = falc->unk8C - falc->unk88;
            pFalco->unk158 = falc->unk90;
            pFalco->unk15C = falc->unk94;
            pFalco->unk248 = falc->unkA4;
            pFalco->unk160 = falc->unk98;
            pFalco->unk160 = falc->unk98;
            pFalco->unk164 = falc->unk9C;
            pFalco->unk168 = falc->unkA0;
            if (falc->unkA8 == 0.0f) {
                pFalco->unk250 = 0.2f;
            } else {
                pFalco->unk250 = 1.0f / falc->unkA8;
            }
            falcoCount++;
        }
    }
}

void falcoDeinit(void) {
    Falco* currentFalco;
    s32 i;

    currentFalco = sFalcos;
    for (i = 0; i < D_8035A5F0; i++, currentFalco++) {
        if (currentFalco->unk0 != MODEL_WORLD) {
            uvDobjModel(currentFalco->unk0, MODEL_WORLD);
            uvDobjModel(currentFalco->unk4, MODEL_WORLD);
            uvDobjModel(currentFalco->unk8, MODEL_WORLD);
            currentFalco->unk0 = MODEL_WORLD;
            currentFalco->unk4 = MODEL_WORLD;
            currentFalco->unk8 = MODEL_WORLD;
        }
        if (currentFalco->unkC != -1) {
            hud_8031A8E0(currentFalco->unkC);
            currentFalco->unkC = -1;
        }
    }

    for (i = 0; i < D_8035A918; i++) {
        falco_802E5F44(&D_8035A920[i]);
    }

    D_8035A918 = 0;
    D_8035A5F0 = 0;
}

void falcoFrameUpdate(void) {
    Falco* currentFalco;
    f32 temp_fv0_2;
    f32 temp_fv1;
    f32 var_fv0;
    s32 i;
    Mtx4F sp9C;
    Mtx4F sp5C;

    if (D_80362690->unkC[0].unk79 != 0) {
        return;
    }

    for (i = 0; i < D_8035A5F0; i++) {
        currentFalco = &sFalcos[i];
        if (currentFalco->unk0 != 0xFFFF) {
            falco_802E43C4(currentFalco);
            falco_802E4AA8(currentFalco);
            falco_802E4E70(currentFalco);
            if (currentFalco->unk244 > 1.0f) {
                // remove integer of unk244
                currentFalco->unk244 -= (f32)(s32)currentFalco->unk244;
            }
            uvDobjState(currentFalco->unk0, 0);
            falco_802E55A0(currentFalco);
            uvDobjState(currentFalco->unk0, 3);
            falco_802E587C(currentFalco);
            if (currentFalco->unk88 != 0.0f) {
                var_fv0 = currentFalco->unk88;
                if ((3.1415927f * D_8034F854) < var_fv0) {
                    var_fv0 = (3.1415927f * D_8034F854);
                }
                if (var_fv0 < (-3.1415927f * D_8034F854)) {
                    var_fv0 = (-3.1415927f * D_8034F854);
                }
                currentFalco->unk88 -= var_fv0;
                uvMat4RotateAxis(&currentFalco->unk16C, var_fv0, 'z');
            }
            if (currentFalco->unk23C == 5 || currentFalco->unk23C == 6) {
                currentFalco->unk84 = -1.5707964f;
            } else {
                currentFalco->unk84 = 0.0f;
            }
            if (currentFalco->unk23C == 9 || currentFalco->unk23C == 0xA) {
                temp_fv1 = currentFalco->unk244;
                temp_fv0_2 = 1.0f - temp_fv1;
                sp9C.m[0][3] = 0.0f;
                sp9C.m[1][3] = 0.0f;
                sp9C.m[2][3] = 0.0f;
                sp9C.m[3][3] = 1.0f;
                sp9C.m[0][0] = (currentFalco->unk1EC.m[0][0] * temp_fv1) + (currentFalco->unk16C.m[0][0] * temp_fv0_2);
                sp9C.m[0][1] = (currentFalco->unk1EC.m[0][1] * temp_fv1) + (currentFalco->unk16C.m[0][1] * temp_fv0_2);
                sp9C.m[0][2] = (currentFalco->unk1EC.m[0][2] * temp_fv1) + (currentFalco->unk16C.m[0][2] * temp_fv0_2);
                sp9C.m[1][0] = (currentFalco->unk1EC.m[1][0] * temp_fv1) + (currentFalco->unk16C.m[1][0] * temp_fv0_2);
                sp9C.m[1][1] = (currentFalco->unk1EC.m[1][1] * temp_fv1) + (currentFalco->unk16C.m[1][1] * temp_fv0_2);
                sp9C.m[1][2] = (currentFalco->unk1EC.m[1][2] * temp_fv1) + (currentFalco->unk16C.m[1][2] * temp_fv0_2);
                sp9C.m[2][0] = (currentFalco->unk1EC.m[2][0] * temp_fv1) + (currentFalco->unk16C.m[2][0] * temp_fv0_2);
                sp9C.m[2][1] = (currentFalco->unk1EC.m[2][1] * temp_fv1) + (currentFalco->unk16C.m[2][1] * temp_fv0_2);
                sp9C.m[2][2] = (currentFalco->unk1EC.m[2][2] * temp_fv1) + (currentFalco->unk16C.m[2][2] * temp_fv0_2);
                sp9C.m[3][0] = (currentFalco->unk1EC.m[3][0] * temp_fv1) + (currentFalco->unk16C.m[3][0] * temp_fv0_2);
                sp9C.m[3][1] = (currentFalco->unk1EC.m[3][1] * temp_fv1) + (currentFalco->unk16C.m[3][1] * temp_fv0_2);
                sp9C.m[3][2] = (currentFalco->unk1EC.m[3][2] * temp_fv1) + (currentFalco->unk16C.m[3][2] * temp_fv0_2);
                uvVec3Normal((Vec3F*)&sp9C.m[0], (Vec3F*)&sp9C.m[0]);
                uvVec3Normal((Vec3F*)&sp9C.m[1], (Vec3F*)&sp9C.m[1]);
                uvVec3Normal((Vec3F*)&sp9C.m[2], (Vec3F*)&sp9C.m[2]);
                falco_802E63BC(currentFalco, &sp9C);
            } else if (currentFalco->unk23C == 8) {
                uvMat4Copy(&sp5C, &currentFalco->unk16C);
                uvMat4RotateAxis(&sp5C, currentFalco->unk244 * 8.0f * 3.1415927f, 'z');
                falco_802E63BC(currentFalco, &sp5C);
            } else {
                falco_802E63BC(currentFalco, &currentFalco->unk16C);
            }
            if (currentFalco->unk256 != 0) {
                currentFalco->unk1AC.m[3][0] = currentFalco->unk16C.m[3][0];
                currentFalco->unk1AC.m[3][1] = currentFalco->unk16C.m[3][1];
                currentFalco->unk1AC.m[3][2] = 0.0f;
                uvDobjPosm(currentFalco->unk8, 0, &currentFalco->unk1AC);
            }
            if (currentFalco->unkC != -1) {
                hudMoveWaypoint(currentFalco->unkC, currentFalco->unk16C.m[3][0], currentFalco->unk16C.m[3][1], currentFalco->unk16C.m[3][2]);
            }
        }
    }
    for (i = 0; i < ARRAY_COUNT(D_8035A920); i++) {
        falco_802E5D78(&D_8035A920[i]);
    }
}

void falco_802E43C4(Falco* falco) {
    Mtx4F* temp_v0_2;
    Mtx4F* temp_a1;
    Vec3F* temp_v0;
    f32 var_fv0;
    f32* temp_v1;

    temp_a1 = &D_80362690->unkC[0].unk2C;
    falco->unk8C.f[0] = temp_a1->m[3][0] - falco->unk16C.m[3][0];
    falco->unk8C.f[1] = temp_a1->m[3][1] - falco->unk16C.m[3][1];
    falco->unk8C.f[2] = temp_a1->m[3][2] - falco->unk16C.m[3][2];
    temp_v1 = &falco->unk98;
    *temp_v1 = uvSqrtF(SQ(falco->unk8C.f[0]) + SQ(falco->unk8C.f[1]) + SQ(falco->unk8C.f[2]));
    temp_v0 = &falco->unk8C;
    if (*temp_v1 != 0.0f) {
        temp_v0->f[0] /= *temp_v1;
        temp_v0->f[1] /= *temp_v1;
        temp_v0->f[2] /= *temp_v1;
    }
    temp_v0_2 = &falco->unk16C;
    // @fake
    if (temp_v0_2) { }
    falco->unk9C.f[0] = temp_v0_2->m[1][0];
    falco->unk9C.f[1] = temp_v0_2->m[1][1];
    var_fv0 = uvSqrtF(SQ(falco->unk9C.f[0]) + SQ(falco->unk9C.f[1]));
    if (var_fv0 != 0.0f) {
        falco->unk9C.f[0] /= var_fv0;
        falco->unk9C.f[1] /= var_fv0;
    }
    falco->unkA8.f[0] = falco->unk8C.f[0];
    falco->unkA8.f[1] = falco->unk8C.f[1];
    var_fv0 = uvSqrtF(SQ(falco->unk8C.f[0]) + SQ(falco->unk8C.f[1]));
    if (var_fv0 != 0.0f) {
        falco->unkA8.f[0] /= var_fv0;
        falco->unkA8.f[1] /= var_fv0;
    }
    falco->unkB4.f[0] = temp_a1->m[1][0];
    falco->unkB4.f[1] = temp_a1->m[1][1];
    var_fv0 = uvSqrtF(SQ(falco->unkB4.f[0]) + SQ(falco->unkB4.f[1]));
    if (var_fv0 != 0.0f) {
        falco->unkB4.f[0] /= var_fv0;
        falco->unkB4.f[1] /= var_fv0;
    }
}

void falco_802E45B0(Falco* falco) {
    static f32 D_8034EFA0 = 0.0f;
    static f32 pad_D_8034EFA4 = 0.0f;
    static f32 pad_D_8034EFA8 = 0.0f;
    static f32 pad_D_8034EFAC = 0.0f;
    Mtx4F* temp_v1;
    Vec3F* temp_v0;
    f32 temp_fv0;
    f32 var_fv0;
    Vec3F sp24;
    f32 temp_fa0;

    temp_v1 = &D_80362690->unkC[0].unk2C;
    if (D_8034EFA0 > 0.0f) {
        D_8034EFA0 -= D_8034F854;
        if (D_8034EFA0 < 0.0f) {
            D_8034EFA0 = 0.0f;
        }
    }
    temp_v0 = &falco->unk8C;
    // @fake
    if (temp_v0) { }
    temp_fa0 = -((temp_v0->f[0] * temp_v1->m[1][0]) + (temp_v0->f[1] * temp_v1->m[1][1]) + (temp_v0->f[2] * temp_v1->m[1][2]));
    var_fv0 = (falco->unk9C.f[0] * falco->unkA8.f[0]) + (falco->unk9C.f[1] * falco->unkA8.f[1]);
    if (var_fv0 < 0.99f) {
        uvVec3Cross(&sp24, &falco->unk9C, &falco->unkA8);
        if (sp24.f[2] < 0.0f) {
            var_fv0 = -3.0f;
        } else {
            var_fv0 = 3.0f;
        }
        uvMat4RotateAxis(&falco->unk16C, var_fv0 * D_8034F854, 'z');
        return;
    }
    if ((falco->unk23C != 3) && (falco->unkCC >= 0 /*.0f*/)) {
        temp_fv0 = falco->unk98;
        if ((falco->unk158 < temp_fv0) && (temp_fv0 < falco->unk15C) && (temp_fa0 > 0.965f) && (D_8034EFA0 == 0.0f)) {
            D_8034EFA0 = falco->unk160;
            falco->unk23C = 3;
            falco->unk244 = 0.0f;
        }
    }
}

void falco_802E478C(Falco* falco, FalcoDomain* arg1) {
    falco->domain = arg1;
}

s32 falco_802E4794(Falco* falco) {
    Vec3F sp6C;
    FalcoDomain* domain;
    f32 temp_fa1;
    f32 temp_fv0;
    s32 pad;
    f32 temp_fv1;
    f32 var_fv0;
    f32 sp50;
    s32 i;
    Vec3F* temp_s1;
    Vec3F sp3C;

    domain = falco->domain;
    sp6C.f[0] = domain->unk0.f[0] - falco->unk16C.m[3][0];
    sp6C.f[1] = domain->unk0.f[1] - falco->unk16C.m[3][1];
    sp6C.f[2] = 0.0f;
    temp_fv0 = uvSqrtF(SQ(sp6C.f[0]) + SQ(sp6C.f[1]));
    if (temp_fv0 > 0.0f) {
        sp6C.f[0] /= temp_fv0;
        sp6C.f[1] /= temp_fv0;
    }
    if (falco->domain->unkC < temp_fv0) {
        temp_s1 = (Vec3F*)&falco->unk16C.m[3];
        for (i = 0; i < sFalcoCount; i++) {
            temp_fv0 = sFalcoDomains[i].unk0.f[0] - temp_s1->x;
            temp_fv1 = sFalcoDomains[i].unk0.f[1] - temp_s1->y;
            temp_fa1 = sFalcoDomains[i].unk0.f[2] - temp_s1->z;
            if (uvSqrtF(SQ(temp_fv0) + SQ(temp_fv1) + SQ(temp_fa1)) < sFalcoDomains[i].unkC) {
                falco_802E478C(falco, &sFalcoDomains[i]);
                return 1;
            }
        }
        sp50 = (falco->unk9C.f[0] * sp6C.f[0]) + (falco->unk9C.f[1] * sp6C.f[1]);
        if (sp50 < 0.99f) {
            uvVec3Cross(&sp3C, &sp6C, &falco->unk9C);
            if (sp50 < 0.99f) {
                if (sp3C.f[2] < 0.0f) {
                    var_fv0 = 3.0f;
                } else {
                    var_fv0 = -3.0f;
                }
                falco->unk88 += var_fv0 * D_8034F854;
            }
            return 0;
        }
    }
    return 1;
}

void falco_802E49B0(Falco* falco) {
    f32 var_fv0_2;
    f32 sp30;

    if (falco->unk256 != 0) {
        sp30 = -1.0f;
    } else {
        sp30 = -24.63f;
    }
    uvMat4SetIdentity(&falco->unk1EC);
    falco->unk1EC.m[3][0] = falco->unk16C.m[3][0];
    falco->unk1EC.m[3][1] = falco->unk16C.m[3][1];
    falco->unk1EC.m[3][2] = falco->unk16C.m[3][2] + sp30;
    if (falco->unk256 != 0) {
        var_fv0_2 = -1.0f;
    } else {
        var_fv0_2 = 1.0f;
    }
    falco->unk1EC.m[1][0] = falco->unk230.x * var_fv0_2;
    falco->unk1EC.m[1][1] = falco->unk230.y * var_fv0_2;
    falco->unk1EC.m[1][2] = falco->unk230.z * var_fv0_2;
    uvVec3Cross((Vec3F*)falco->unk1EC.m[2], (Vec3F*)falco->unk16C.m[0], (Vec3F*)falco->unk1EC.m[1]);
    uvVec3Cross((Vec3F*)falco->unk1EC.m[0], (Vec3F*)falco->unk1EC.m[1], (Vec3F*)falco->unk1EC.m[2]);
    falco->unk23C = 9;
    falco->unk244 = 0.0f;
}

void falco_802E4AA8(Falco* falco) {
    f32 temp_fv1;
    f32 sp28;
    f32 sp24;
    f32 var_fv0;
    s32 sp1C;

    switch (falco->unk23C) {
    case 4:
    case 5:
    case 6:
        falco->unk16C.m[3][0] += D_8034F854 * falco->unkC8 * falco->unk16C.m[1][0];
        falco->unk16C.m[3][1] += D_8034F854 * falco->unkC8 * falco->unk16C.m[1][1];
        falco->unk16C.m[3][2] = falco->unkCC;
        falco_802E4794(falco);
        if (falco->unk23C == 5) {
            var_fv0 = 50.0f;
        } else {
            var_fv0 = 30.0f;
        }
        falco->unk244 += (D_8034F854 * falco->unkC8) / var_fv0;
        break;
    case 0:
    case 1:
    case 7:
        falco->unk16C.m[3][0] += D_8034F854 * falco->unkC8 * falco->unk16C.m[1][0];
        falco->unk16C.m[3][1] += D_8034F854 * falco->unkC8 * falco->unk16C.m[1][1];
        falco->unk16C.m[3][2] -= 0.1f * D_8034F854;
        falco_802E4794(falco);
        temp_fv1 = falco->unk244;
        if (falco->unk23C == 1) {
            var_fv0 = 50.0f;
        } else {
            var_fv0 = 30.0f;
        }
        falco->unk244 += ((D_8034F854 * falco->unkC8) / var_fv0);
        if (((falco->unk256 == 0) && (temp_fv1 <= 0.5f) && (falco->unk244 >= 0.5f)) || ((temp_fv1 <= 1.0f) && (falco->unk244 >= 1.0f))) {
            sp24 = 1.0f - ((falco->unk98 - 300.0f) * 0.001f);
            if (sp24 > 0.0f) {
                if (sp24 > 1.0f) {
                    sp24 = 1.0f;
                }
                sp28 = (falco->unkA8.f[0] * falco->unkB4.f[1]) - (falco->unkA8.f[1] * falco->unkB4.f[0]);
                if (falco->unk244 >= 1.0f) {
                    sp1C = 0x4E;
                } else {
                    sp1C = 0x4F;
                }
                func_8033F758(sp1C, sp24, (uvRandF_LCG() * 0.2f) + 0.45f, sp28);
                break;
            }
        }
        break;
    case 2:
        falco_802E45B0(falco);
        break;
    case 3:
        falco_802E45B0(falco);
        falco->unk244 += D_8034F854;
        break;
    case 8:
        falco->unk244 += 0.2f * D_8034F854 * (falco->unkD0 + 1.0f);
        falco->unk16C.m[3][0] += D_8034F854 * falco->unkC8 * falco->unk16C.m[1][0];
        falco->unk16C.m[3][1] += D_8034F854 * falco->unkC8 * falco->unk16C.m[1][1];
        falco->unk16C.m[3][2] -= 0.1f * D_8034F854;
        break;
    case 9:
        falco->unk244 += D_8034F854;
        break;
    case 10:
        break;
    }
}

void falco_802E4E70(Falco* falco) {
    f32 temp_fv0;
    Unk8035A920* temp_v0;
    s32 sp64;
    s32 v0_2;

    switch (falco->unk23C) {
    case 9:
        if (falco->unk244 >= 1.0f) {
            falco->unk244 = 1.0f;
            falco->unk23C = 10;
            func_8033F758(0x46U, 1.0f, 1.0f, 0 /*.0f*/);
            return;
        }
    case 10:
    default:
        return;
    case 3:
        if (falco->unk244 >= 1.0f) {
            falco->unk23C = 2;
            temp_fv0 = uvRandF_LCG();
            falco->unkD0 = (temp_fv0 * falco->unk114) + falco->unk110;
            temp_v0 = falco_802E5AFC();
            if (temp_v0 != NULL) {
                falco_802E5BF8(temp_v0, falco);
                return;
            }
        }
        break;
    case 8:
        v0_2 = falco->unkD0;
        falco->unkD0 -= D_8034F854;
        if (v0_2 != (s32)falco->unkD0) {
            sp64 = func_8021EFF0(8);
            if (sp64 != 0xFF) {
                uvModelGet(sp64, 8);
                // clang-format off
                uvFxProps(
                    sp64,
                    FX_PROP_10(falco->unk16C.m[3][0], falco->unk16C.m[3][1], falco->unk16C.m[3][2]),
                    FX_PROP_5(1.0f, 1.0f, 0.0f, 1.0f),
                    FX_PROP_END
                );
                // clang-format on
            }
        }
        if (falco->unkD0 <= 0.0f) {
            falco->unkD0 = 0.0f;
            if (falco->unk244 >= 1.0f) {
                falco_802E49B0(falco);
                return;
            }
        }
        break;
    case 0:
    case 1:
    case 2:
    case 4:
    case 5:
    case 6:
    case 7:
        falco->unkD0 -= D_8034F854;
        if (falco->unk256 != 0) {
            if ((s32)(falco->unkD0 * 2.5f) != (s32)((falco->unkD0 + D_8034F854) * 2.5f)) {
                falco->unk1AC.m[3][2] += 2.0f;
                splash_8034170C(&falco->unk1AC, 80.0f);
                falco->unk1AC.m[3][2] -= 2.0f;
            }
        }
        if (falco->unkD0 <= 0.0f) {
            temp_fv0 = uvRandF_LCG();
            if (temp_fv0 < falco->unkD4) {
                falco_802E6344(falco);
            } else if ((falco->unk23C == 2) || (temp_fv0 < falco->unkD8)) {
                falco_802E6380(falco);
            } else if ((falco->unk256 != 0) && (temp_fv0 < falco->unkDC)) {
                falco_802E62E4(falco);
            } else {
                falco_802E61E4(falco);
            }
            switch (falco->unk23C) {
            case 0:
            case 1:
            case 4:
            case 5:
            case 6:
                falco->unk88 += 2.0f * (uvRandF_LCG() - 0.5f) * 3.1415927f;
                break;
            }
        }
        break;
    }
}

s32 falco_802E51E8(s32 falco, f32 arg1, f32 arg2, f32 arg3) {
    Falco* curFalco;
    Unk8035A920* var_s0_2;
    f32 temp_fv0;
    f32 temp_fv1;
    f64 temp_fs0;
    s32 temp_a0;
    s32 temp_s1;
    s32 temp_v0_2;
    s32 i;
    s32 ret;

    ret = FALSE;
    curFalco = sFalcos;
    for (i = 0; i < D_8035A5F0; i++, curFalco++) {
        if (falco == curFalco->unk0) {
            ret = TRUE;
            if (curFalco->unk23C == 10 || curFalco->unk23C == 9) {
                continue;
            }

            if (curFalco->unk23C != 8) {
                curFalco->unk24C += curFalco->unk248;
                curFalco->unkC4 += curFalco->unk250;
            }

            if (curFalco->unkC4 >= 1.0f) {
                curFalco->unk23C = 8;
                curFalco->unkD0 = 2.1f;
                splashAdd(&curFalco->unk1AC, 60.0f);
                func_8033F758(0x44U, 1.0f, 1.0f, 0.0f);
                hudText_8031D8E0(0x174, 1.5f, 8.0f);
                if (curFalco->unk256 == 0) {
                    curFalco->unk16C.m[0][0] = -curFalco->unkB4.f[1];
                    curFalco->unk16C.m[0][1] = curFalco->unkB4.f[0];
                    curFalco->unk16C.m[0][2] = 0.0f;
                    curFalco->unk16C.m[1][0] = curFalco->unkB4.f[0];
                    curFalco->unk16C.m[1][1] = curFalco->unkB4.f[1];
                    curFalco->unk16C.m[1][2] = 0.0f;
                    curFalco->unk16C.m[2][0] = 0.0f;
                    curFalco->unk16C.m[2][1] = 0.0f;
                    curFalco->unk16C.m[2][2] = 1.0f;
                    curFalco->unkC8 = D_80362690->unkC[0].unk20 * 1.5f;
                }
                curFalco->unk244 = 0.0f;
                curFalco->unk254 = 1;
                if (curFalco->unkC != -1) {
                    hud_8031A8E0(curFalco->unkC);
                    curFalco->unkC = -1;
                }
            } else {
                temp_s1 = textGetDataByIdx(0x158); // "Shots to go:"
                func_8033F758(0x3BU, 1.0f, (uvRandF_LCG() * 0.2) + 0.800000011920929, 0.0f);
                hudText_8031D8E0(0x164, 1.5f, 8.0f); // "Hit"
                textFmtIntAt(temp_s1, ((1.0f - curFalco->unkC4) / curFalco->unk250) + 0.5, 1, 0xE);
                hudWarningText(0x158, 1.5f, 8.0f);
                curFalco->unk23C = 7;
                temp_fv0 = uvRandF_LCG();
                curFalco->unkC8 = (curFalco->unk13C * temp_fv0) + curFalco->unk138;
                temp_fv0 = uvRandF_LCG();
                curFalco->unkD0 = (curFalco->unk104 * temp_fv0) + curFalco->unk100;
            }
            temp_v0_2 = func_8021EFF0(8);
            if (temp_v0_2 != 0xFF) {
                uvModelGet(temp_v0_2, 8);
                // clang-format off
                uvFxProps(
                    temp_v0_2,
                    FX_PROP_10(arg1, arg2, arg3),
                    FX_PROP_5(1.0f, 1.0f, 0.0f, 1.0f),
                    FX_PROP_END
                );
                // clang-format on
            }
        }
    }
    for (i = 0; i < D_8035A918; i++) {
        if (falco == D_8035A920[i].unk0) {
            falco_802E5F90(&D_8035A920[i]);
        }
    }
    return ret;
}

void falco_802E55A0(Falco* falco) {
    f32 sp5C;
    s32 sp58;
    u8 sp57;
    Vec3F sp48;
    Vec3F sp3C;
    Vec3F* temp_v0_3;
    f32 var_fv0;
    s32 temp;

    if (falco->unk256 != 0) {
        switch (falco->unk23C) {
        case 5:
            var_fv0 = -3.0f;
            break;
        case 6:
            var_fv0 = -9.0f;
            break;
        default:
            var_fv0 = 1.0f;
            break;
        }
        falco->unkCC = (0.2f * var_fv0) + (0.8f * falco->unkCC);
    } else {
        falco->unkCC = (falco->unkCC * 0.8f) + 5.526f;
    }
    sp48.f[0] = falco->unk16C.m[3][0];
    sp48.f[1] = falco->unk16C.m[3][1];
    sp48.f[2] = falco->unk16C.m[3][2];
    if (sp48.f[2] < 1.0f) {
        sp48.f[2] = 1.0f;
    }
    sp3C.f[0] = sp48.f[0] + falco->unk16C.m[1][0];
    sp3C.f[1] = sp48.f[1] + falco->unk16C.m[1][1];
    sp3C.f[2] = sp48.f[2] + falco->unk16C.m[1][2];
    temp = sp57 = db_getgnd(&sp48, &sp3C, &falco->unk240, &sp58, &sp5C, &falco->unk230);
    if (sp57 != 2) {
        if (sp57 == 8) { }
        temp = sp57;
    } else if (sp57) {
        if (sp57) { }
        temp = sp57;
    }

    if (!temp) {
        falco->unk16C.m[3][2] = sp5C + falco->unkCC;
    } else {
        temp_v0_3 = func_802E02EC();
        if (sp57 != 4) {
            falco->unk16C.m[3][0] = temp_v0_3->f[0];
            falco->unk16C.m[3][1] = temp_v0_3->f[1];
        }
        falco->unk16C.m[3][2] = temp_v0_3->f[2] + falco->unkCC;
    }
    if ((sp5C <= 0.0f) && (falco->unk256 == 0)) {
        falco_802E6284(falco);
        return;
    }
    if (((sp57 == 1) || (sp5C > 0.0f)) && (falco->unk256 != 0)) {
        falco_802E6184(falco);
    }
}

s32 falco_802E57C4(void) {
    s32 ret;
    s32 i;

    ret = 0;
    for (i = 0; i < D_8035A5F0; i++) {
        ret += sFalcos[i].unk254;
    }
    return ret;
}

s32 falco_802E5818(void) {
    s32 ret;
    s32 i;

    ret = 0;
    for (i = 0; i < D_8035A5F0; i++) {
        if (sFalcos[i].unk254 != 0) {
            ret += sFalcos[i].unk24C;
        }
    }
    return ret;
}

void falco_802E587C(Falco* falco) {
    static Unk802CAC48 D_8034EFB0 = { 0, 10, &D_8035AF30, NULL };
    static Unk802CAC48 D_8034EFBC = { 0, 5, &D_8035AF34, NULL };
    static Unk802CAC48 D_8034EFC8 = { 0, 6, &D_8035AF30, NULL };
    static Unk802CAC48 D_8034EFD4 = { 0, 9, &D_8035AF38, NULL };
    static Unk802CAC48 D_8034EFE0 = { 0, 8, &D_8035AF3C, NULL };
    static Unk802CAC48 D_8034EFEC = { 0, 7, &D_8035AF3C, NULL };
    static Unk802CAC48 D_8034EFF8 = { 0, 4, &D_8035AF3C, NULL };
    static Unk802CAC48 D_8034EF04 = { 0, 3, &D_8035AF3C, NULL };
    static Unk802CAC48 D_8034F010 = { 0, 1, &D_8035AF3C, NULL };
    static Unk8034E788 D_8034F01C = { 1, 0, &D_8035AF40, &D_8034EFE0, &D_8034EFEC };
    static Unk8034E788 D_8034F02C = { 1, 0, &D_8035AF40, &D_8034EFF8, &D_8034EF04 };
    static Unk8034E788 D_8034F03C = { 1, 0, &D_8035AF44, &D_8034EFBC, &D_8034EFB0 };
    static Unk8034E788 D_8034F04C = { 1, 0, &D_8035AF48, &D_8034EFC8, &D_8034EFD4 };
    static Unk8034E788 D_8034F05C = { 1, 0, &D_8035AF4C, &D_8034F01C, &D_8034F02C };
    static Unk8034E788 D_8034F06C = { 1, 0, &D_8035AF50, &D_8034F05C, &D_8034F03C };
    static Unk8034E788 D_8034F07C = { 1, 0, &D_8035AF54, &D_8034F06C, &D_8034F04C };
    static Unk8034E788 D_8034F08C = { 1, 0, &D_8035AF58, &D_8034F07C, &D_8034F010 };
    static Unk8034E788* D_8034F09C = &D_8034F08C;
    Unk80371120 sp20;
    s32 sp1C;
    f32 var_fa0;

    sp1C = falco->unk23C;
    D_8035AF3C = falco->unk244;
    D_8035AF30 = falco->unk244;
    D_8035AF34 = falco->unk244;
    D_8035AF38 = falco->unk244;
    if ((sp1C == 5) || (sp1C == 4)) {
        var_fa0 = 1.0f;
    } else {
        var_fa0 = 0.0f;
    }
    D_8035AF4C = func_80313AF4(var_fa0, D_8035AF4C, 1.0f);
    if ((sp1C == 8) || (sp1C == 9) || (sp1C == 0xA)) {
        var_fa0 = 1.0f;
    } else {
        var_fa0 = 0.0f;
    }
    D_8035AF48 = func_80313AF4(var_fa0, D_8035AF48, 4.0f);
    if ((sp1C == 0) || (sp1C == 4)) {
        var_fa0 = 1.0f;
    } else {
        var_fa0 = 0.0f;
    }
    D_8035AF40 = func_80313AF4(var_fa0, D_8035AF40, 1.0f);
    if (sp1C == 3) {
        var_fa0 = 1.0f;
    } else {
        var_fa0 = 0.0f;
    }
    D_8035AF44 = func_80313AF4(var_fa0, D_8035AF44, 2.0f);
    if ((sp1C == 7) || (sp1C == 3) || (sp1C == 8)) {
        var_fa0 = 1.0f;
    } else {
        var_fa0 = 0.0f;
    }
    D_8035AF50 = func_80313AF4(var_fa0, D_8035AF50, 5.0f);
    if ((sp1C == 2) || (sp1C == 0xA) || (sp1C == 9)) {
        var_fa0 = 1.0f;
    } else {
        var_fa0 = 0.0f;
    }
    D_8035AF54 = func_80313AF4(var_fa0, D_8035AF54, 10.0f);
    if (sp1C == 6) {
        var_fa0 = 1.0f;
    } else {
        var_fa0 = 0.0f;
    }
    D_8035AF58 = func_80313AF4(var_fa0, D_8035AF58, 10.0f);
    func_802CAAC8(D_8034F09C, &sp20);
    func_80200638(falco->unk0, &sp20);
    if (falco->unk256 != 0) {
        func_80200638(falco->unk4, &sp20);
    }
}

Unk8035A920* falco_802E5AFC(void) {
    Unk8035A920* var_v1;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_a0_4;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_8035A920); i++) {
        if (D_8035A920[i].unk0 == 0xFFFF) {
            if (D_8035A918 < (i + 1)) {
                D_8035A918 = i + 1;
            }
            return &D_8035A920[i];
        }
    }
    return 0;
}

void falco_802E5BF8(Unk8035A920* falco, Falco* arg1) {
    f32 fv0;

    falco->unk0 = uvDobjAllocIdx();
    if (falco->unk0 != 0xFFFF) {
        func_8033F758(0x3DU, 1.0f, (uvRandF_LCG() * 0.2f) + 0.4f, 0.0f);
        falco->unk5D = arg1->unk256;
        if (falco->unk5D) {
            uvDobjModel(falco->unk0, 0x100);
        } else {
            uvDobjModel(falco->unk0, 0xFF);
        }
        uvMat4SetIdentity(&falco->unk8);
        fv0 = uvRandF_LCG();
        falco->unk58 = (arg1->unk14C * fv0) + arg1->unk148;
        fv0 = uvRandF_LCG();
        falco->unk54 = (arg1->unk154 * fv0) + arg1->unk150;
        falco->unk48.f[0] = arg1->unk8C.f[0] * falco->unk58;
        falco->unk48.f[1] = arg1->unk8C.f[1] * falco->unk58;
        falco->unk48.f[2] = arg1->unk8C.f[2] * falco->unk58;
        falco->unk8.m[3][0] = arg1->unk16C.m[3][0] + (arg1->unk8C.f[0] * 15.0f);
        falco->unk8.m[3][1] = arg1->unk16C.m[3][1] + (arg1->unk8C.f[1] * 15.0f);
        falco->unk8.m[3][2] = arg1->unk16C.m[3][2] + (arg1->unk8C.f[2] * 15.0f);
        falco->radarIdx = hudAddWaypoint(falco->unk8.m[3][0], falco->unk8.m[3][1], falco->unk8.m[3][2]);
        uvDobjState(falco->unk0, 3);
        uvDobjPosm(falco->unk0, 0, &falco->unk8);
    }
}

void falco_802E5D78(Unk8035A920* falco) {
    Vec3F sp174;
    Unk802D3658_Unk1224 sp30;

    if (falco->unk0 == 0xFFFF) {
        return;
    }

    falco->unk54 -= D_8034F854;
    if (falco->unk54 <= 0.0f) {
        falco->unk54 = 0.0f;
        falco_802E5F44(falco);
        return;
    }

    sp174.f[0] = falco->unk8.m[3][0];
    sp174.f[1] = falco->unk8.m[3][1];
    sp174.f[2] = falco->unk8.m[3][2];
    falco->unk8.m[3][0] += falco->unk48.f[0] * D_8034F854;
    falco->unk8.m[3][1] += falco->unk48.f[1] * D_8034F854;
    falco->unk8.m[3][2] += falco->unk48.f[2] * D_8034F854;
    func_802DB224(&sp30, 9U, 0xFFFFU, 0U, &sp174, (Vec3F*)falco->unk8.m[3]);
    if (sp30.unk0 != 0) {
        falco_802E5F90(falco);
        func_8033F758(0x30U, 1.0f, 1.0f, 0.0f);
        return;
    }
    uvMat4RotateAxis(&falco->unk8, 2.0f * (D_8034F854 * 1.3f) * 3.1415927f, 'x');
    uvMat4RotateAxis(&falco->unk8, 2.0f * (D_8034F854 * 0.3f) * 3.1415927f, 'z');
    uvDobjPosm(falco->unk0, 0, &falco->unk8);
    hudMoveWaypoint(falco->radarIdx, falco->unk8.m[3][0], falco->unk8.m[3][1], falco->unk8.m[3][2]);
}

void falco_802E5F44(Unk8035A920* falco) {
    if (falco->unk0 != 0xFFFF) {
        uvDobjModel(falco->unk0, 0xFFFF);
        falco->unk0 = 0xFFFF;
        hud_8031A8E0(falco->radarIdx);
    }
}

void falco_802E5F90(Unk8035A920* falco) {
    s32 sp44;

    sp44 = func_8021EFF0(8);
    if (sp44 != 0xFF) {
        uvModelGet(sp44, 8);
        uvFxProps(sp44, FX_PROP_10(falco->unk8.m[3][0], falco->unk8.m[3][1], falco->unk8.m[3][2]), FX_PROP_END);
        if (falco->unk5D != 0) {
            uvFxProps(sp44, FX_PROP_5(1.0f, 1.0f, 1.0f, 1.0f), FX_PROP_END);
        } else {
            uvFxProps(sp44, FX_PROP_5(0.3f, 0.2f, 0.1f, 1.0f), FX_PROP_END);
        }
    }
    falco_802E5F44(falco);
}

void falco_802E60A4(Falco* falco) {
    falco->unk256 = 1;
    uvDobjState(falco->unk8, 0x22);
    uvDobjState(falco->unk4, 2);
}

void falco_802E60E8(Falco* falco) {
    falco->unk256 = 0;
    uvDobjState(falco->unk8, 0);
    uvDobjState(falco->unk4, 0);
}

void falco_802E6128(Falco* falco) {
    f32 temp;

    falco_802E60E8(falco);
    falco->unk23C = 0;
    temp = uvRandF_LCG();
    falco->unkD0 = (falco->unkE4 * temp) + falco->unkE0;
    temp = uvRandF_LCG();
    falco->unkC8 = (falco->unk11C * temp) + falco->unk118;
}

void falco_802E6184(Falco* falco) {
    f32 temp;

    falco_802E60E8(falco);
    falco->unk23C = 1;
    temp = uvRandF_LCG();
    falco->unkD0 = (falco->unkEC * temp) + falco->unkE8;
    temp = uvRandF_LCG();
    falco->unkC8 = (falco->unk124 * temp) + falco->unk120;
}

void falco_802E61E4(Falco* falco) {
    f32 temp;

    falco->unk23C = 2;
    temp = uvRandF_LCG();
    falco->unkD0 = (falco->unk114 * temp) + falco->unk110;
}

void falco_802E6224(Falco* falco) {
    f32 temp;

    falco_802E60A4(falco);
    falco->unk23C = 4;
    temp = uvRandF_LCG();
    falco->unkD0 = (falco->unkF4 * temp) + falco->unkF0;
    temp = uvRandF_LCG();
    falco->unkC8 = (falco->unk12C * temp) + falco->unk128;
}

void falco_802E6284(Falco* falco) {
    f32 temp;

    falco_802E60A4(falco);
    falco->unk23C = 5;
    temp = uvRandF_LCG();
    falco->unkD0 = (falco->unkFC * temp) + falco->unkF8;
    temp = uvRandF_LCG();
    falco->unkC8 = (falco->unk134 * temp) + falco->unk130;
}

void falco_802E62E4(Falco* falco) {
    f32 temp;

    falco_802E60A4(falco);
    falco->unk23C = 6;
    temp = uvRandF_LCG();
    falco->unkD0 = (falco->unk10C * temp) + falco->unk108;
    temp = uvRandF_LCG();
    falco->unkC8 = (falco->unk144 * temp) + falco->unk140;
}

void falco_802E6344(Falco* falco) {
    if (falco->unk256 != 0) {
        falco_802E6224(falco);
        return;
    }
    falco_802E6128(falco);
}

void falco_802E6380(Falco* falco) {
    if (falco->unk256 != 0) {
        falco_802E6284(falco);
        return;
    }
    falco_802E6184(falco);
}

void falco_802E63BC(Falco* falco, Mtx4F* arg1) {
    f32 var_fv0;
    Mtx4F sp34;

    if (falco->unk84 != falco->unk80) {
        var_fv0 = falco->unk84 - falco->unk80;
        if ((3.1415927f * D_8034F854) < var_fv0) {
            var_fv0 = (3.1415927f * D_8034F854);
        }
        if (var_fv0 < (-3.1415927f * D_8034F854)) {
            var_fv0 = -3.1415927f * D_8034F854;
        }
        falco->unk80 += var_fv0;
    }
    if (falco->unk80 != 0.0f) {
        uvMat4Copy(&sp34, arg1);
        uvMat4RotateAxis(&sp34, falco->unk80, 'x');
        if (falco->unk256 != 0) {
            uvDobjPosm(falco->unk4, 0, &sp34);
        }
        uvDobjPosm(falco->unk0, 0, &sp34);
        return;
    }
    if (falco->unk256 != 0) {
        uvDobjPosm(falco->unk4, 0, arg1);
    }
    uvDobjPosm(falco->unk0, 0, arg1);
}

void falco_802E64E0(s32 falco, Mtx4F* arg1) {
    Falco* sp18;

    sp18 = &sFalcos[falco];
    uvMat4Copy(arg1, &sp18->unk16C);
    if (sp18->unk80 != 0.0f) {
        uvMat4RotateAxis(arg1, sp18->unk80, 'x');
    }
}

