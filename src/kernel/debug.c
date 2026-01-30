#include "common.h"
#include <uv_controller.h>
#include <uv_geometry.h>
#include <uv_graphics.h>
#include <uv_matrix.h>
#include <uv_util.h>
#include <uv_debug.h>

typedef struct {
    f64 unk0;
    s32 unk8;
    u8 padC[4];
} Unk802B92A0_Unk0;

typedef struct {
    Unk802B92A0_Unk0 unk0[30];
} Unk802B92A0;

extern Unk802B92A0 D_802B8940[];
extern Unk802B92A0 D_802B92A0[];
extern s32 gSchedRingIdx;
extern s32 D_802B9C00[];
extern s32 D_802B9C18[];
extern double D_802B9C30[];
extern s16 D_802C8020;
extern s16 D_802C8022;
extern f32 D_802C8024;
extern f32 D_802C8028;
extern s16 D_802C802C;
extern s16 D_802C802E;
extern s32 D_802C8030;

extern u16 D_8024B2D0[]; // 50 chars supported ['*'-'Z'], u16 per char
extern u8 D_8024B334[];  // 50 chars supported, u8 per char

extern Vtx_t D_8024B348[];

extern Gfx D_8024B5A8[];
/* .data contents:
{
    gsSPVertex(D_8024B348, 14, 0),
    gsSPEndDisplayList(),
};
*/
extern Gfx D_8024B5B8[];
/* .data contents:
{
    gsSPVertex(D_8024B428, 15, 0),
    gsSPVertex(D_8024B518, 1, 15),
    gsSPEndDisplayList(),
};
*/
extern Gfx D_8024B5D0[];
/* .data contents:
{
    gsSPVertex(D_8024B528, 8, 0),
    gsSPEndDisplayList(),
};
*/

extern Gfx D_8024B5E0[];
/* .data contents:
{
    gsSP1Triangle(10, 11, 1, 0),
    gsSP1Triangle(10, 1, 0, 0),
    gsSPEndDisplayList(),
};
*/

extern Gfx D_8024B5F8[];
/* .data contents:
{
    gsSP1Triangle(11, 8, 2, 0),
    gsSP1Triangle(11, 2, 1, 0),
    gsSPEndDisplayList(),
};
*/

extern Gfx D_8024B610[];
/* .data contents:
{
    gsSP1Triangle(8, 12, 4, 0),
    gsSP1Triangle(8, 4, 3, 0),
    gsSPEndDisplayList(),
};
*/

extern Gfx D_8024B628[];
/* .data contents:
{
    gsSP1Triangle(12, 13, 5, 0),
    gsSP1Triangle(12, 5, 4, 0),
    gsSPEndDisplayList(),
};
*/

extern Gfx D_8024B640[];
/* .data contents:
{
    gsSP1Triangle(13, 9, 6, 0),
    gsSP1Triangle(13, 6, 5, 0),
    gsSPEndDisplayList(),
};
*/

extern Gfx D_8024B658[];
/* .data contents:
{
    gsSP1Triangle(9, 10, 0, 0),
    gsSP1Triangle(9, 0, 7, 0),
    gsSPEndDisplayList(),
};
*/

extern Gfx D_8024B670[];
/* .data contents:
{
    gsSP1Triangle(6, 9, 7, 0),
    gsSP1Triangle(2, 6, 7, 0),
    gsSP1Triangle(2, 3, 6, 0),
    gsSP1Triangle(2, 8, 3, 0),
    gsSPEndDisplayList(),
};
*/

extern Gfx D_8024B698[];
/* .data contents:
{
    gsSP1Triangle(0, 9, 11, 0),
    gsSP1Triangle(0, 11, 7, 0),
    gsSPEndDisplayList(),
};
*/

extern Gfx D_8024B6B0[];
/* .data contents:
{
    gsSP1Triangle(2, 9, 11, 0),
    gsSP1Triangle(2, 11, 1, 0),
    gsSPEndDisplayList(),
};
*/

extern Gfx D_8024B6C8[];
/* .data contents:
{
    gsSP1Triangle(4, 11, 9, 0),
    gsSP1Triangle(4, 9, 3, 0),
    gsSPEndDisplayList(),
};
*/

extern Gfx D_8024B6E0[];
/* .data contents:
{
    gsSP1Triangle(6, 11, 9, 0),
    gsSP1Triangle(6, 9, 5, 0),
    gsSPEndDisplayList(),
};
*/

extern Gfx D_8024B6F8[];
/* .data contents:
{
    gsSP1Triangle(12, 13, 15, 0),
    gsSP1Triangle(12, 15, 14, 0),
    gsSPEndDisplayList(),
};
*/

extern Gfx D_8024B710[];
/* .data contents:
{
    gsSP1Triangle(0, 2, 1, 0),
    gsSP1Triangle(0, 3, 2, 0),
    gsSPEndDisplayList(),
};
*/

extern Gfx D_8024B728[];
/* .data contents:
{
    gsSP1Triangle(4, 5, 7, 0),
    gsSP1Triangle(4, 7, 6, 0),
    gsSPEndDisplayList(),
};
*/

extern Gfx* D_8024B740[];
/* array of 14 DL pointers, used by the for loops in func_80233DB8
{
    D_8024B5E0,
    D_8024B5F8,
    D_8024B610,
    D_8024B628,
    D_8024B640,
    D_8024B658,
    D_8024B670,
    D_8024B698,
    D_8024B6B0,
    D_8024B6C8,
    D_8024B6E0,
    D_8024B6F8,
    D_8024B710,
    D_8024B728,
};
*/

// forward declarations
f64 func_80231AC0(void);
f64 func_80231C10(void);
f64 func_80231C9C(void);
void func_80231F04(f32, f32, s16, u8, u8, u8);
void func_8023217C(u8, u8);
void func_80233310(void);
void func_802323A8(u8, u8);
void func_80232554(u8);
void func_80232738(u8);
void func_8023286C(void);
void func_80232EBC(void);
void func_80232ECC(s32, s32, u16, u8, u8, u8);
void func_80233310(void);
void func_802333AC(u8);
void func_80233878(s16, s16);
void func_802338A8(f32, f32);
void func_802339B0(u8 r, u8 g, u8 b, u8 a);
void func_80233A40(s32, u16);
void func_80233D04(u16);
void func_80233DB8(char ch);
void func_80233FC8(char* fmt, s32 arg1, ...);

f64 func_80231AC0(void) {
    Unk802B92A0_Unk0* sp14;
    s32 sp10;
    s32 spC;
    s32 sp8;
    f64 sp0;

    spC = (gSchedRingIdx + 1) % 5;
    sp8 = 0;
    for (sp10 = 0; sp10 < D_802B9C18[spC]; sp10++) {
        sp14 = &D_802B92A0[spC].unk0[sp10];
        if (sp8 == 0) {
            if (sp14->unk8 == 0x2A) {
                sp8 = 1;
                sp0 = sp14->unk0;
            }
        } else {
            if ((sp8 != 0) && (sp14->unk8 == 0x30)) {
                return sp14->unk0 - sp0;
            }
        }
    }
    return 0.0;
}

f64 func_80231C10(void) {
    s32 sp4;
    s32 sp0;

    sp4 = (gSchedRingIdx + 1) % 5;
    sp0 = (gSchedRingIdx + 2) % 5;
    return D_802B9C30[sp0] - D_802B9C30[sp4];
}

f64 func_80231C9C(void) {
    Unk802B92A0_Unk0* sp2C;
    s32 sp28;
    s32 sp24;
    s32 sp20;
    s32 sp1C;
    f64 sp10;
    f64 sp8;
    f64 sp0;

    sp24 = (gSchedRingIdx + 1) % 5;
    sp20 = (gSchedRingIdx + 2) % 5;
    sp1C = 0;
    sp8 = 0.0;
    sp10 = 0.0;

    for (sp28 = 0; sp28 < D_802B9C00[sp24]; sp28++) {
        sp2C = &D_802B8940[sp24].unk0[sp28];
        sp0 = sp2C->unk0 - D_802B9C30[sp24];
        if (sp1C == 0) {
            if (sp2C->unk8 == 0x2A) {
                sp1C = 1;
                sp10 = sp0;
            }
            if (sp2C->unk8 == 0x2B) {
                sp8 += sp0;
            }
        } else if ((sp1C != 0) && (sp2C->unk8 == 0x2B)) {
            sp1C = 0;
            sp8 += sp0 - sp10;
        }
    }
    if (sp1C != 0) {
        sp8 += (D_802B9C30[sp20] - D_802B9C30[sp24]) - sp10;
    }
    return sp8;
}

void func_80231F04(f32 arg0, f32 arg1, s16 arg2, u8 arg3, u8 arg4, u8 arg5) {
    s16 sp36;
    s16 sp34;
    s16 sp32;

    sp36 = arg2 + 6;
    sp34 = (s16)((arg0 * 1000.0f * 2.0f) + 85.0f);
    sp32 = (s16)((arg1 * 1000.0f * 2.0f) + 85.0f);
    if (arg0 < 0.0f) {
        return;
    }
    if (sp32 < sp34) {
        return;
    }
    if (sp34 > 320) {
        return;
    }
    if (sp32 >= 320) {
        sp32 = 319;
    }
    if (sp34 == sp32) {
        sp32 = sp34 + 1;
    }
    uvVtxBeginPoly();
    uvVtx(sp34, arg2, 0, 0, 0, arg3, arg4, arg5, 0xFF);
    uvVtx(sp32, arg2, 0, 0, 0, arg3, arg4, arg5, 0xFF);
    uvVtx(sp32, sp36, 0, 0, 0, arg3, arg4, arg5, 0xFF);
    uvVtx(sp34, sp36, 0, 0, 0, arg3, arg4, arg5, 0xFF);
    uvVtxEndPoly();
}

const char D_8024F350[] = "start: %f  (%d)   finish: %f (%d)\n";

void func_8023217C(u8 arg0, u8 arg1) {
    s32 val;
    s16 xPos;
    s16 yPos;
    f64 multiplier;

    xPos = 20;
    yPos = 34;
    if (arg1 == 1) {
        multiplier = 1000.0;
    } else {
        multiplier = 1000000.0;
    }
    func_802339B0(0xFF, 0xFF, 0x00, 0xFF);
    func_802338A8(6.0f, 8.0f);
    if (arg0 & 0x01) {
        val = func_80231C10() * multiplier;
        func_80233878(xPos, yPos);
        func_80233FC8("r: %d", val);
        yPos += 14;
    }
    if (arg0 & 0x02) {
        val = func_80231AC0() * multiplier;
        func_80233878(xPos, yPos);
        func_80233FC8("g: %d", val);
        yPos += 14;
    }
    if (arg0 & 0x04) {
        val = func_80231C9C() * multiplier;
        func_80233878(xPos, yPos);
        func_80233FC8("c: %d", val);
        yPos += 14;
    }
}

void func_802323A8(u8 arg0, u8 arg1) {
    s32 sp24;
    f64 sp18;

    if (arg1 == 1) {
        sp18 = 1000.0;
    } else {
        sp18 = 1000000.0;
    }
    if (arg0 & 0x01) {
        sp24 = func_80231C10() * sp18;
        _uvDebugPrintf("retrace: %d       ", sp24);
    }
    if (arg0 & 0x04) {
        sp24 = func_80231C9C() * sp18;
        _uvDebugPrintf("cpu: %d       ", sp24);
    }
    if (arg0 & 0x02) {
        sp24 = func_80231AC0() * sp18;
        _uvDebugPrintf("gfx: %d       ", sp24);
    }
    if (arg0 != 0) {
        _uvDebugPrintf("\n");
    }
}

void func_80232554(u8 arg0) {
    s16 xPos;
    s16 yPos;

    xPos = 20;
    yPos = 80;
    func_802339B0(0xFF, 0xFF, 0, 0xFF);
    func_802338A8(6.0f, 8.0f);
    if (arg0 & 0x01) {
        func_80233878(xPos, yPos);
        func_80233FC8("v: %d", uvGfxGetCnt(0));
        yPos += 14;
    }
    if (arg0 & 0x02) {
        func_80233878(xPos, yPos);
        func_80233FC8("p: %d", uvGfxGetCnt(1));
        yPos += 14;
    }
    if (arg0 & 0x04) {
        func_80233878(xPos, yPos);
        func_80233FC8("l: %d", uvGfxGetCnt(2));
        yPos += 14;
    }
    if (arg0 & 0x10) {
        func_80233878(xPos, yPos);
        func_80233FC8("t: %d", uvGfxGetCnt(4));
        yPos += 14;
    }
    if (arg0 & 0x08) {
        func_80233878(xPos, yPos);
        func_80233FC8("m: %d", uvGfxGetCnt(3));
    }
}

void func_80232738(u8 arg0) {
    if (arg0 & 0x02) {
        _uvDebugPrintf("tris: %d   ", uvGfxGetCnt(1));
    }
    if (arg0 & 0x01) {
        _uvDebugPrintf("vtx xfms: %d   ", uvGfxGetCnt(0));
    }
    if (arg0 & 0x04) {
        _uvDebugPrintf("mtx loads: %d   ", uvGfxGetCnt(2));
    }
    if (arg0 & 0x10) {
        func_80233FC8("txt loads: %d   ", uvGfxGetCnt(4));
    }
    if (arg0 & 0x08) {
        _uvDebugPrintf("mtx load-mults: %d   ", uvGfxGetCnt(3));
    }
    if (arg0 != 0x00) {
        _uvDebugPrintf("\n");
    }
}

// unused strings after "\n":
static const char unused0[] = "frame time %f\n";
static const char unused1[] = "started at %f\n";
static const char unused2[] = "finished at %f\n";
static const char unused3[] = "\n\n";

void func_8023286C(void) {
    s16 sp36;

    sp36 = 0x55;
    uvGfxStatePush();
    uvGfxSetFlags(0xFFF);
    uvGfxClearFlags(0x80F00000);

    uvBeginTmesh();
    uvVtx(sp36, 0x3C, 0, 0, 0, 0, 0, 0, 0xFF);
    uvVtx(sp36, 0x1E, 0, 0, 0, 0, 0, 0, 0xFF);
    sp36 = 0x75;
    uvVtx(sp36, 0x3C, 0, 0, 0, 0, 0, 0, 0xFF);
    uvVtx(sp36, 0x1E, 0, 0, 0, 0, 0, 0, 0xFF);
    uvEndTmesh();

    uvBeginTmesh();
    uvVtx(sp36, 0x3C, 0, 0, 0, 0x28, 0x28, 0x28, 0xFF);
    uvVtx(sp36, 0x1E, 0, 0, 0, 0x28, 0x28, 0x28, 0xFF);
    sp36 = 0x97;
    uvVtx(sp36, 0x3C, 0, 0, 0, 0x28, 0x28, 0x28, 0xFF);
    uvVtx(sp36, 0x1E, 0, 0, 0, 0x28, 0x28, 0x28, 0xFF);
    uvEndTmesh();

    uvBeginTmesh();
    uvVtx(sp36, 0x3C, 0, 0, 0, 0, 0, 0, 0xFF);
    uvVtx(sp36, 0x1E, 0, 0, 0, 0, 0, 0, 0xFF);
    sp36 = 0xB9;
    uvVtx(sp36, 0x3C, 0, 0, 0, 0, 0, 0, 0xFF);
    uvVtx(sp36, 0x1E, 0, 0, 0, 0, 0, 0, 0xFF);
    uvEndTmesh();

    uvBeginTmesh();
    uvVtx(sp36, 0x3C, 0, 0, 0, 0x28, 0x28, 0x28, 0xFF);
    uvVtx(sp36, 0x1E, 0, 0, 0, 0x28, 0x28, 0x28, 0xFF);
    sp36 = 0xD9;
    uvVtx(sp36, 0x3C, 0, 0, 0, 0x28, 0x28, 0x28, 0xFF);
    uvVtx(sp36, 0x1E, 0, 0, 0, 0x28, 0x28, 0x28, 0xFF);
    uvEndTmesh();

    uvBeginTmesh();
    uvVtx(sp36, 0x3C, 0, 0, 0, 0, 0, 0, 0xFF);
    uvVtx(sp36, 0x1E, 0, 0, 0, 0, 0, 0, 0xFF);
    sp36 = 0xFB;
    uvVtx(sp36, 0x3C, 0, 0, 0, 0, 0, 0, 0xFF);
    uvVtx(sp36, 0x1E, 0, 0, 0, 0, 0, 0, 0xFF);
    uvEndTmesh();

    uvBeginTmesh();
    uvVtx(sp36, 0x3C, 0, 0, 0, 0x28, 0x28, 0x28, 0xFF);
    uvVtx(sp36, 0x1E, 0, 0, 0, 0x28, 0x28, 0x28, 0xFF);
    sp36 = 0x11D;
    uvVtx(sp36, 0x3C, 0, 0, 0, 0x28, 0x28, 0x28, 0xFF);
    uvVtx(sp36, 0x1E, 0, 0, 0, 0x28, 0x28, 0x28, 0xFF);
    uvEndTmesh();

    uvBeginTmesh();
    uvVtx(sp36, 0x3C, 0, 0, 0, 0, 0, 0, 0xFF);
    uvVtx(sp36, 0x1E, 0, 0, 0, 0, 0, 0, 0xFF);
    sp36 = 0x13D;
    uvVtx(sp36, 0x3C, 0, 0, 0, 0, 0, 0, 0xFF);
    uvVtx(sp36, 0x1E, 0, 0, 0, 0, 0, 0, 0xFF);
    uvEndTmesh();
    uvGfxStatePop();
}

void func_80232EBC(void) {
}

void func_80232ECC(s32 arg0, s32 arg1, u16 arg2, u8 arg3, u8 arg4, u8 arg5) {
    Unk802B92A0_Unk0* sp4C;
    s32 sp48;
    s32 sp44;
    s32 sp40;
    s32 sp3C;
    s32* sp38;
    s32 sp34;
    s32 sp30;
    f64 sp28;
    f64 sp20;

    sp44 = (gSchedRingIdx + 1) % 5;
    sp28 = D_802B9C30[sp44];
    if (arg0 == 0) {
        sp38 = D_802B9C00;
    } else {
        sp38 = D_802B9C18;
    }

    if (arg1 == 0x29) {
        sp34 = 0x29;
        sp30 = 0x2C;
    } else {
        sp34 = 0x2A;
        sp30 = 0x2B;
    }

    sp48 = -1;
    sp3C = 0;
    for (;;) {
        sp48 += 1;
        if (sp48 > sp38[sp44]) {
            sp3C += 1;
            sp48 = 0;
            sp44 = (sp44 + 1) % 5;
        }
        if (sp3C >= 5) {
            break;
        }
        if (arg0 == 0) {
            sp4C = &D_802B8940[sp44].unk0[sp48];
        } else {
            sp4C = &D_802B92A0[sp44].unk0[sp48];
        }
        if (sp4C->unk8 == sp34) {
            break;
        }
        if (sp4C->unk8 == sp30) {
            func_80231F04(0.0f, (f32)(sp4C->unk0 - sp28), arg2, arg3, arg4, arg5);
            break;
        }
    }

    sp48 = -1;
    sp3C = 0;
    sp40 = -1;
    sp44 = (gSchedRingIdx + 1) % 5;

    for (;;) {
        sp48 += 1;
        if (sp48 > sp38[sp44]) {
            sp3C += 1;
            sp48 = 0;
            sp44 = (sp44 + 1) % 5;
        }
        if (sp3C >= 4) {
            break;
        }
        if (arg0 == 0) {
            sp4C = &D_802B8940[sp44].unk0[sp48];
        } else {
            sp4C = &D_802B92A0[sp44].unk0[sp48];
        }
        if (sp40 != sp34) {
            if (sp4C->unk8 == sp34) {
                sp40 = sp34;
                sp20 = sp4C->unk0;
            }
        } else if (sp4C->unk8 != sp30) {
        } else {
            func_80231F04((f32)(sp20 - sp28), (f32)(sp4C->unk0 - sp28), arg2, arg3, arg4, arg5);
            sp40 = -1;
        }
    }
}

void func_80233310(void) {
    func_80232ECC(0, 0x2A, 0x34, 0x00, 0x00, 0xFF);
    func_80232ECC(0, 0x29, 0x2D, 0xFF, 0x00, 0xFF);
    func_80232ECC(1, 0x2A, 0x26, 0x00, 0xFF, 0x00);
    func_80232ECC(1, 0x29, 0x1E, 0xFF, 0x00, 0x00);
}

void func_802333AC(UNUSED u8 arg0) {
    Mtx4F sp60;
    Mtx4F sp20;

    arg0 += 1;
    uvMat4Viewport(&sp20, 0.0f, 320.0f, 0.0f, 240.0f);
    func_80222100(&sp20);
    uvMat4SetIdentity(&sp60);
    func_8022345C(&sp60, 1);
    func_8023286C();
    uvGfxStatePush();
    uvGfxSetFlags(0xFFF);
    uvGfxClearFlags(0xF00000);
    func_80232EBC();
    func_80233310();
    uvGfxStatePop();
    func_802236A8();
}

void func_8023345C(u8 arg0, u8 arg1, u8 arg2) {
    if (arg1 == 1) {
        func_802333AC(arg0);
    } else if (arg1 == 2) {
        func_8023217C(arg0, arg2);
    } else {
        func_802323A8(arg0, arg2);
    }
}

void uvDbgCnt(u8 arg0, u8 arg1) {
    if (arg0 == 0) {
        return;
    } else {
        if (arg1 == 1) {
            _uvDebugPrintf("uvDbgCnt: bar count not supported\n");
        } else if (arg1 == 2) {
            func_80232554(arg0);
        } else if (arg1 == 3) {
            func_80232738(arg0);
        }
    }
}

void func_80233590(void) {
    u8* sp2C;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    f32 sp1C;

    sp2C = (u8*)0x80200000;
    sp20 = 0.0f;
    sp1C = 0.0f;
    while (uvIOUpdate() != 0) {
        sp28 = uvControllerGetStick(0, 0);
        sp24 = uvControllerGetStick(0, 1);
        sp20 += sp28 * sp28 * sp28 * 8.0f;
        sp1C += sp24 * sp24 * sp24 * 128.0f;
        if (sp20 > 40.0f) {
            sp20 = 0.0f, sp1C += 1.0f;
        }
        if (sp20 < 0.0f) {
            sp20 = 40.0f, sp1C -= 1.0f;
        }
        if (sp1C < 0.0f) {
            sp1C = 0.0f;
        }
        if (sp1C > 6553.6f) {
            sp1C = 6553.6f;
        }
        sp2C = ((u8*)0x80000000) + ((s32)sp20 * 0x10) + ((s32)sp1C * 0x140 * 2);
        uvGfxBegin();
        uvGfxEnd();
        osViSwapBuffer(sp2C);
        if (uvControllerButtonPress(0, Z_TRIG) != 0) {
            break;
        }
        if (uvControllerButtonPress(0, START_BUTTON) != 0) {
            break;
        }

        if (uvControllerButtonPress(0, A_BUTTON) != 0) {
            _uvDebugPrintf("Address: 0x%x\n", sp2C);
        }
    }
}

void func_80233810(void) {
    D_802C8024 = 0.0f;
    D_802C8028 = 0.0f;
    D_802C802C = 12;
    D_802C802E = 16;
    D_802C8020 = 0;
    D_802C8022 = 240 - D_802C802E;
    D_802C8030 = 0;
}

void func_80233878(s16 arg0, s16 arg1) {
    D_802C8020 = arg0;
    D_802C8022 = arg1;
}

void func_802338A8(f32 arg0, f32 arg1) {
    D_802C8024 = (f32)(arg0 / 10.0);
    D_802C8028 = (f32)(arg1 / 14.0);
    D_802C802C = (s16)((D_802C8024 + 0.25) * 10.0);
    D_802C802E = (s16)((D_802C8028 + 0.25) * 14.0);
}

void func_802339B0(u8 r, u8 g, u8 b, u8 a) {
    s32 idx;
    for (idx = 0; idx < 0x26; idx++) {
        D_8024B348[idx].cn[0] = r;
        D_8024B348[idx].cn[1] = g;
        D_8024B348[idx].cn[2] = b;
        D_8024B348[idx].cn[3] = a;
    }
}

void func_80233A40(s32 arg0, u16 arg1) {
    Mtx4F sp70;
    Mtx4F sp30;
    s32 sp2C;
    u16 sp2A;
    u16 sp28;
    u16 sp26;

    D_802C8030 = 0;
    uvMat4Viewport(&sp70, 0.0f, 320.0f, 0.0f, 240.0f);
    func_80222100(&sp70);
    uvMat4SetIdentity(&sp30);
    sp30.m[0][0] = D_802C8024;
    sp30.m[1][1] = D_802C8028;
    if (arg0 < 0) {
        sp26 = 1;
        arg0 = -arg0;
    } else {
        sp26 = 0;
    }
    sp28 = 0;
    sp2C = 1;
    if (arg0 != 0) {
        while (arg0 >= sp2C) {
            sp2C *= arg1;
            sp28 += 1;
        }
    } else {
        sp28 = 1;
    }
    sp30.m[3][0] = (f32)(D_802C8020 + ((sp28 + sp26) * D_802C802C));
    sp30.m[3][1] = (f32)D_802C8022;

    for (sp2C = 0; sp2C < sp28; sp2C++) {
        sp2A = (u16)(arg0 % arg1);
        func_8022345C(&sp30, 0);
        func_80233D04(sp2A);
        sp30.m[3][0] -= (f32)D_802C802C;
        arg0 = (s32)(arg0 - sp2A) / arg1;
    }
    if (sp26 != 0) {
        func_8022345C(&sp30, 0);
        func_802210C4(D_8024B670);
    }
    D_802C8020 += D_802C802C * sp28;
}

void func_80233D04(u16 arg0) {
    u8 sp1F;
    u8 idx;

    sp1F = D_8024B334[arg0];
    if (D_802C8030 != 1) {
        func_802210C4(D_8024B5A8);
    }

    for (idx = 0; idx < 7; idx++) {
        if ((1 << idx) & sp1F) {
            func_802210C4(D_8024B740[idx]);
        }
    }
}

void func_80233DB8(char ch) {
    u16 sp1E;
    u16 idx;

    if (ch >= 'a') {
        ch -= 0x20;
    }
    if ((ch >= '*') && (ch <= 'Z')) {
        ch -= '*';
    } else {
        return;
    }
    sp1E = D_8024B2D0[(int)ch];

    if (D_802C8030 != 1) {
        func_802210C4(D_8024B5A8);
    }
    for (idx = 0; idx < 7; idx++) {
        if ((1 << idx) & sp1E) {
            func_802210C4(D_8024B740[idx]);
        }
    }

    if (D_802C8030 != 2) {
        func_802210C4(D_8024B5B8);
    }
    for (idx = 7; idx < 12; idx++) {
        if ((1 << idx) & sp1E) {
            func_802210C4(D_8024B740[idx]);
        }
    }

    if (D_802C8030 != 3) {
        func_802210C4(D_8024B5D0);
    }
    for (idx = 12; idx < 14; idx++) {
        if ((1 << idx) & sp1E) {
            func_802210C4(D_8024B740[idx]);
        }
    }
}

void func_80233FC8(char* fmt, s32 arg1, ...) {
    s32* spB4;
    s32 idx;
    s32 base;
    char ch;
    Mtx4F sp68;
    Mtx4F sp28;
    u8* sp24;
    s32 sp20;

    D_802C8030 = 0;
    uvMat4Viewport(&sp68, 0.0f, 320.0f, 0.0f, 240.0f);
    func_80222100(&sp68);
    uvMat4SetIdentity(&sp28);
    sp28.m[0][0] = D_802C8024;
    sp28.m[1][1] = D_802C8028;
    sp28.m[3][0] = (f32)D_802C8020;
    sp28.m[3][1] = (f32)D_802C8022;
    spB4 = &arg1;
    idx = 0;
    ch = fmt[idx];
    while (ch != 0) {
        func_8022345C(&sp28, 0);
        if (ch == '%') {
            idx++;
            ch = fmt[idx];
            base = 0;
            if (ch == 'x') {
                base = 16;
            } else if (ch == 'd') {
                base = 10;
            } else if (ch == 'b') {
                base = 2;
            } else if (ch == 'f') {
            } else if (ch == 's') {
                sp24 = (u8*)*spB4;
                sp20 = 0;
                sp28.m[0][0] = D_802C8024;
                sp28.m[1][1] = D_802C8028;
                while (sp24[sp20] != 0) {
                    func_8022345C(&sp28, 0);
                    sp28.m[3][0] += (f32)D_802C802C;
                    func_80233DB8(sp24[sp20]);
                    sp20 += 1;
                }
                sp28.m[3][0] -= (f32)D_802C802C;
            }
            if (base != 0) {
                D_802C8020 = (s16)(sp28.m[3][0] - (f32)D_802C802C);
                D_802C8022 = (s16)sp28.m[3][1];
                func_80233A40(*spB4, base);
                sp28.m[3][0] = (f32)D_802C8020;
                sp28.m[3][1] = (f32)D_802C8022;
            }
            spB4 += 1;
        } else if (ch == '\n') {
            sp28.m[3][0] = (f32)-D_802C802C;
            sp28.m[3][1] -= (f32)D_802C802E;
            D_802C8022 += D_802C802E;
        } else {
            func_80233DB8(ch);
        }
        idx += 1;
        ch = fmt[idx];
        sp28.m[3][0] += (f32)D_802C802C;
    }
    D_802C8020 = (s16)sp28.m[3][0];
    D_802C8022 = (s16)sp28.m[3][1];
}
