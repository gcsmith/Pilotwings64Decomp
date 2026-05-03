#include "common.h"
#include <uv_font.h>
#include <uv_geometry.h>
#include <uv_graphics.h>
#include <uv_math.h>
#include <uv_matrix.h>
#include "code_66160.h"

// draw quad/poly
void func_802DEC30(s32 x0, s32 y0, s32 x1, s32 y1, s32 x2, s32 y2, s32 x3, s32 y3, s32 r0, s32 g0, s32 b0, s32 r1, s32 g1, s32 b1) {
    uvVtxBeginPoly();
    uvVtx(x0, y0, 0, 0, 0, r0, g0, b0, 0xFF);
    uvVtx(x1, y1, 0, 0, 0, r0, g0, b0, 0xFF);
    uvVtx(x2, y2, 0, 0, 0, r1, g1, b1, 0xFF);
    uvVtx(x3, y3, 0, 0, 0, r1, g1, b1, 0xFF);
    uvVtxEndPoly();
}

// draw rect
void screenDrawBox(s32 x0, s32 y0, s32 x1, s32 y1, u8 r, u8 g, u8 b, u8 a) {
    uvVtxBeginPoly();
    uvVtx(x0, y0, 0, 0, 0, r, g, b, a);
    uvVtx(x1, y0, 0, 0, 0, r, g, b, a);
    uvVtx(x1, y1, 0, 0, 0, r, g, b, a);
    uvVtx(x0, y1, 0, 0, 0, r, g, b, a);
    uvVtxEndPoly();
}

// draw outlined rect?
void func_802DEE44(s32 x, s32 y, s32 width, s32 height, s32 size, s32 r0, s32 g0, s32 b0, s32 r1, s32 g1, s32 b1) {
    s32 x1 = x + width;
    s32 y1 = y + height;
    s32 xpos = x + size;
    s32 yneg = y1 - size;
    s32 xneg = x1 - size;
    s32 ypos = y + size;

    uvGfxStatePush();
    uvGfxSetFlags(GFX_STATE_XLU | GFX_STATE_TEXTURE_NONE);
    uvGfxClearFlags(GFX_STATE_AA | GFX_STATE_ZBUFFER | GFX_STATE_CULL_BACK);
    func_802DEC30(x1, y1, x, y1, xpos, yneg, xneg, yneg, r0, g0, b0, r1, g1, b1);
    func_802DEC30(xneg, yneg, xneg, ypos, x1, y, x1, y1, r0, g0, b0, r1, g1, b1);
    func_802DEC30(xneg, ypos, xpos, ypos, x, y, x1, y, r0, g0, b0, r1, g1, b1);
    func_802DEC30(x, y1, x, y, xpos, ypos, xpos, yneg, r0, g0, b0, r1, g1, b1);
    uvGfxStatePop();
}

void screenDrawBox2(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, char* str, s32 arg6, s32 arg7) {
    s32 spA4;
    s32 spA0;
    s32 sp9C;
    s32 sp98;
    s32 sp84;
    s32 temp_v0;
    s32 temp_v1;
    s32 pad;

    screenDrawBoxSetup();
    if (str != NULL) {
        temp_v0 = uvFontWidth(str);

        // hack operand order workaround
        sp9C = arg4 * 2;
        sp9C = temp_v0 + sp9C + 2;

        spA4 = (((arg2 - temp_v0) / 2) + arg0) - arg4;
        temp_v1 = uvFontHeight() + arg4 * 2;
        sp98 = temp_v1 + 2;
        spA0 = (arg1 + arg3 - (sp98 / 2)) - (arg4 / 2);
        screenDrawBox(spA4 + arg4, arg1 + arg3 - arg4, (spA4 + sp9C) - arg4, ((spA0 + temp_v1) - arg4) + 2, 0, 0, 0, arg6);
    }

    screenDrawBox(arg0 + arg4, arg1 + arg4, arg0 + arg2 - arg4, arg1 + arg3 - arg4, 0, 0, 0, arg6);
    if (str != NULL) {
        func_802DEE44(spA4 - 1, spA0 - 1, sp9C + 2, sp98 + 2, arg4 + 2, 0, 0, 0, 0, 0, 0);
        func_802DEE44(spA4, spA0, sp9C, sp98, arg4, 0x14, 0xAA, 0xFF, 0, 0xF, 0xA0);
        uvFontColor(0xB4, 0xB4, 0x00, 0xFF);
        uvFontPrintStr(spA4 + arg4 + 1, spA0 + arg4, str);
        func_802DEC30(spA4, arg1 + arg3 + 1, arg0 - 1, arg1 + arg3 + 1, arg0 + arg4, arg1 + arg3 - arg4 - 1, spA4, arg1 + arg3 - arg4 - 1, 0, 0, 0, 0, 0, 0);
        func_802DEC30(arg0 + arg2 + 1, arg1 + arg3 + 1, spA4 + sp9C, arg1 + arg3 + 1, spA4 + sp9C, arg1 + arg3 - arg4 - 1, arg0 + arg2 - arg4,
                      arg1 + arg3 - arg4 - 1, 0, 0, 0, 0, 0, 0);
        func_802DEC30(spA4, arg1 + arg3, arg0, arg1 + arg3, arg0 + arg4, arg1 + arg3 - arg4, spA4, arg1 + arg3 - arg4, 0x14, 0xAA, 0xFF, 0, 0xF, 0xA0);
        func_802DEC30(arg0 + arg2, arg1 + arg3, spA4 + sp9C, arg1 + arg3, spA4 + sp9C, arg1 + arg3 - arg4, arg0 + arg2 - arg4, arg1 + arg3 - arg4, 0x14, 0xAA,
                      0xFF, 0, 0xF, 0xA0);
    } else {
        func_802DEC30(arg0 + arg2 + 1, arg1 + arg3 + 1, arg0 - 1, arg1 + arg3 + 1, arg0 + arg4, arg1 + arg3 - arg4 - 1, arg0 + arg2 - arg4,
                      arg1 + arg3 - arg4 - 1, 0, 0, 0, 0, 0, 0);
        func_802DEC30(arg0 + arg2, arg1 + arg3, arg0, arg1 + arg3, arg0 + arg4, arg1 + arg3 - arg4, arg0 + arg2 - arg4, arg1 + arg3 - arg4, 0x14, 0xAA, 0xFF, 0,
                      0xF, 0xA0);
    }

    func_802DEC30(arg0 - 1, arg1 + arg3, arg0 - 1, arg1, arg0 + arg4 + 1, arg1 + arg4 + 1, arg0 + arg4 + 1, arg1 + arg3 - arg4 - 1, 0, 0, 0, 0, 0, 0);
    func_802DEC30(arg0 + arg2 - arg4 - 1, arg1 + arg3 - arg4 - 1, arg0 + arg2 - arg4 - 1, arg1 + arg4 + 1, arg0 + arg2 + 1, arg1, arg0 + arg2 + 1,
                  arg1 + arg3 + 1, 0, 0, 0, 0, 0, 0);
    func_802DEC30(arg0 + arg2 - arg4, arg1 + arg4 + 1, arg0 + arg4 + 1, arg1 + arg4 + 1, arg0 - 1, arg1 - 1, arg0 + arg2 + 1, arg1 - 1, 0, 0, 0, 0, 0, 0);
    func_802DEC30(arg0, arg1 + arg3, arg0, arg1, arg0 + arg4, arg1 + arg4, arg0 + arg4, arg1 + arg3 - arg4, 0x14, 0xAA, 0xFF, 0, 0xF, 0xA0);
    func_802DEC30(arg0 + arg2 - arg4, arg1 + arg3 - arg4, arg0 + arg2 - arg4, arg1 + arg4, arg0 + arg2, arg1, arg0 + arg2, arg1 + arg3, 0x14, 0xAA, 0xFF, 0,
                  0xF, 0xA0);
    func_802DEC30(arg0 + arg2 - arg4, arg1 + arg4, arg0 + arg4, arg1 + arg4, arg0, arg1, arg0 + arg2, arg1, 0x14, 0xAA, 0xFF, 0, 0xF, 0xA0);

    sp84 = (((arg3 / 2) + arg1) - (arg4 * 1.5f));
    if (arg7 != 0) {
        // hack operand order workaround
        temp_v0 = arg4 * 6;
        temp_v0 = sp84 + temp_v0 + 2;

        sp98 = arg4 * 4;

        uvVtxBeginPoly();
        uvVtx(arg0 + arg4 + 1, sp84 - 2, 0, 0, 0, 0, 0, 0, 0xFF);
        uvVtx(arg0 + arg4 + 1, temp_v0, 0, 0, 0, 0, 0, 0, 0xFF);
        uvVtx(arg0 + arg4 - sp98 - 1, (arg4 * 6 / 2) + sp84, 0, 0, 0, 0, 0, 0, 0xFF);
        uvVtxEndPoly();
        uvVtxBeginPoly();
        uvVtx(arg0 + arg4, sp84, 0, 0, 0, 0, 0xB4, 0, 0xFF);
        uvVtx(arg0 + arg4, sp84 + arg4 * 6, 0, 0, 0, 0, 0xB4, 0, 0xFF);
        uvVtx(arg0 + arg4 - sp98, (arg4 * 6 / 2) + sp84, 0, 0, 0, 0, 0xB4, 0, 0xFF);
        uvVtxEndPoly();
        uvVtxBeginPoly();
        uvVtx(arg0 + arg2 - arg4 - 1, sp84 - 2, 0, 0, 0, 0, 0, 0, 0xFF);
        uvVtx(arg0 + arg2 - arg4 + sp98 + 1, (arg4 * 6 / 2) + sp84, 0, 0, 0, 0, 0, 0, 0xFF);
        uvVtx(arg0 + arg2 - arg4 - 1, sp84 + arg4 * 6 + 2, 0, 0, 0, 0, 0, 0, 0xFF);
        uvVtxEndPoly();
        uvVtxBeginPoly();
        uvVtx(arg0 + arg2 - arg4, sp84, 0, 0, 0, 0, 0xB4, 0, 0xFF);
        uvVtx(arg0 + arg2 - arg4 + sp98, (arg4 * 6 / 2) + sp84, 0, 0, 0, 0, 0xB4, 0, 0xFF);
        uvVtx(arg0 + arg2 - arg4, sp84 + arg4 * 6, 0, 0, 0, 0, 0xB4, 0, 0xFF);
        uvVtxEndPoly();
    }
    func_802DFA18();
}

void screenDrawBoxSetup(void) {
    Mtx4F sp60;
    Mtx4F sp20;

    uvGfxStatePush();
    uvGfxSetFlags(GFX_STATE_XLU);
    uvGfxClearFlags(GFX_STATE_AA | GFX_STATE_ZBUFFER);
    uvGfxSetViewport(0, 0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);
    uvMat4SetOrtho(&sp20, 0.0f, SCREEN_WIDTH - 1, 0.0f, SCREEN_HEIGHT - 1);
    uvGfxMtxProjPushF(&sp20);
    uvMat4SetIdentity(&sp60);
    uvGfxMtxViewLoad(&sp60, 1);
}

void func_802DFA18(void) {
    uvGfxMtxViewPop();
    uvGfxStatePop();
}
