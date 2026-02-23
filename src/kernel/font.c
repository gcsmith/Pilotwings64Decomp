#include "common.h"
#include <uv_filesystem.h>
#include <uv_memory.h>
#include <uv_font.h>
#include <uv_string.h>

Bitmap D_8026A040[44];
Gfx D_8026A300[7944 * 2];
Unk80289380 D_80289380[30];

// clang-format off
static Sprite D_80248E20 = { 
    0, 0, 0, 0, 1.0f, 1.0f, 0, 0, 1, 0x1234, 255, 255, 255, 255, 0, 0, NULL, 0, 1, 660, 7944, 15, 128,
    G_IM_FMT_IA, G_IM_SIZ_4b, D_8026A040, D_8026A300, NULL, 0, 0
};

static u8 D_80248E64 = 0xFF;
static u8 D_80248E68 = 0xFF;
static u8 D_80248E6C = 0xFF;
static u8 D_80248E70 = 0xFF;
static u8 D_80248E74 = 0x00;
static u8 D_80248E78 = 0x00;

static f32 D_80248E7C = 1;
static f32 D_80248E80 = 1;
static u32 D_80248E84 = 0;
static u32 D_80248E88 = 8;
static s32 D_80248E8C = 0;
// clang-format on

ParsedUVFT* uvParseTopUVFT(s32 arg0) {
    ParsedUVFT* ret;
    s32 temp_v0;
    u32 nbytes;
    s32* srcAddr;
    s32 i;
    s32 imagCount;
    s32 bitmCount;
    u32 tag;

    imagCount = 0;
    ret = (ParsedUVFT*)_uvMemAlloc(sizeof(ParsedUVFT), 4);
    temp_v0 = uvFileReadHeader(gUVBlockOffsets.UVFT[arg0]);
    while ((tag = uvFileReadBlock(temp_v0, &nbytes, (void**)&srcAddr, 1)) != NULL) {
        switch (tag) {
        case 'STRG':
            ret->str = _uvMemAlloc(nbytes, 4);
            _uvMediaCopy((void*)ret->str, srcAddr, nbytes);
            break;
        case 'FRMT':
            ret->bmfmt = srcAddr[0];
            ret->bmsiz = srcAddr[1];
            break;
        case 'BITM':
            bitmCount = nbytes / sizeof(Bitmap);
            ret->bitmap = (Bitmap*)_uvMemAlloc(nbytes, 8);
            _uvMediaCopy((void*)ret->bitmap, srcAddr, nbytes);
            break;
        case 'IMAG':
            ret->imag[imagCount] = _uvMemAlloc(nbytes, 8);
            _uvMediaCopy((void*)ret->imag[imagCount], srcAddr, nbytes);
            imagCount++;
            break;
        default:
            break;
        }
    }

    uvFile_80223F30(temp_v0);
    // update indexes to pointers allocated above
    for (i = 0; i < bitmCount; i++) {
        ret->bitmap[i].buf = ret->imag[(u32)ret->bitmap[i].buf];
    }
    return ret;
}

void uvFontSet(s32 arg0) {
    if (gGfxUnkPtrs->fonts[arg0] != NULL) {
        D_80248E84 = arg0;
    } else {
        _uvDebugPrintf("uvFontSet ( %d ) -- font does not exist in level\n", arg0);
    }
    D_80248E88 = gGfxUnkPtrs->fonts[D_80248E84]->bitmap->width;
}

void uvFont_80219550(f64 arg0, f64 arg1) {
    D_80248E7C = (f32)arg0;
    D_80248E80 = (f32)arg1;
}

void uvFont_8021956C(u8 arg0, u8 arg1, u8 arg2, u8 arg3) {
    D_80248E64 = arg0;
    D_80248E68 = arg1;
    D_80248E6C = arg2;
    D_80248E70 = arg3;
}

s32 func_802195A0(s16* arg0) {
    s32 i;

    i = 0;
    while (i < 44 && arg0[i] != -1) {
        i++;
    }
    return i;
}

s32 func_802195DC(ParsedUVFT* arg0, s16* arg1) {
    s32 temp_v0;
    s32 i;
    s32 var_v1;
    s32 j;

    temp_v0 = func_802195A0(arg1);

    var_v1 = 0;
    for (i = 0, j = 0; i < temp_v0; i++, j++) {
        if (arg1[j] == -1) {
            return var_v1;
        }
        if ((arg1[j] >= 0) && (arg1[j] != 0xFFF) && (arg1[j] != 0xFFE)) {
            var_v1 += arg0->bitmap[arg1[j]].width;
        } else {
            var_v1 += D_80248E88;
        }
    }

    return var_v1 * D_80248E7C;
}

s32 func_802196B0(s16* arg0) {
    return func_802195DC(gGfxUnkPtrs->fonts[D_80248E84], arg0);
}

s32 func_802196EC(ParsedUVFT* arg0, char* arg1) {
    s32 temp_v0;
    char* temp_v0_2;
    s32 var_s0;
    s32 i;
    s32 j;

    temp_v0 = uvStrlen(arg1);

    var_s0 = 0;
    for (i = 0, j = 0; i < temp_v0; i++, j++) {
        if (arg1[j] == 0) {
            return var_s0;
        }
        if (arg1[j] == '\n') {
            continue;
        }
        temp_v0_2 = uvStrchr(arg0->str, arg1[j]);
        if (temp_v0_2 != 0) {
            var_s0 += arg0->bitmap[temp_v0_2 - arg0->str].width;
        } else {
            var_s0 += D_80248E88;
        }
    }

    return var_s0 * D_80248E7C;
}

s32 uvFontWidth(char* arg0) {
    return func_802196EC(gGfxUnkPtrs->fonts[D_80248E84], arg0);
}

s32 func_80219828(void) {
    ParsedUVFT* temp_v1 = gGfxUnkPtrs->fonts[D_80248E84];
    return temp_v1->bitmap[1].actualHeight * D_80248E80;
}

s32 func_80219874(s32 arg0, s32 arg1, s16* arg2, s32 arg3, s32 arg4) {
    s32 var_a0;
    s32 i;
    s32 sp24;
    s32 ret;
    ParsedUVFT* temp_v1;
    s32 temp_s3 = arg4;

    temp_v1 = gGfxUnkPtrs->fonts[D_80248E84];

    arg1 += (s32)(temp_v1->bitmap[1].actualHeight * D_80248E80);
    arg1 = SCREEN_HEIGHT - arg1;
    D_80289380[D_80248E8C].x = arg0;
    D_80289380[D_80248E8C].y = arg1;
    D_80289380[D_80248E8C].r = D_80248E64;
    D_80289380[D_80248E8C].g = D_80248E68;
    D_80289380[D_80248E8C].b = D_80248E6C;
    D_80289380[D_80248E8C].a = D_80248E70;
    D_80289380[D_80248E8C].scaleX = D_80248E7C;
    D_80289380[D_80248E8C].scaleY = D_80248E80;
    D_80289380[D_80248E8C].unk6C = gGfxUnkPtrs->fonts[D_80248E84];
    if (arg3 > 44) {
        arg3 = 44;
    }
    var_a0 = 0;
    i = 0;
    sp24 = FALSE;
    if (arg2[var_a0] == 0xFD) {
        // FAKE
        if (arg2[var_a0 + 1]) { }
        D_80289380[D_80248E8C].x = arg2[var_a0 + 1];
        var_a0 += 3;
    }

    while (i < arg3) {
        if (arg2[var_a0] == temp_s3) {
            D_80289380[D_80248E8C].unk14[i] = -1;
            var_a0++;
            i++;
            break;
        }

        if (arg2[var_a0] == 0xFD) {
            D_80289380[D_80248E8C].unk14[i] = -1;
            D_80248E8C++;
            D_80289380[D_80248E8C].r = D_80248E64;
            D_80289380[D_80248E8C].g = D_80248E68;
            D_80289380[D_80248E8C].b = D_80248E6C;
            D_80289380[D_80248E8C].a = D_80248E70;
            D_80289380[D_80248E8C].scaleX = D_80248E7C;
            D_80289380[D_80248E8C].scaleY = D_80248E80;
            D_80289380[D_80248E8C].x = arg2[var_a0 + 1];
            D_80289380[D_80248E8C].y = arg1;
            D_80289380[D_80248E8C].unk6C = gGfxUnkPtrs->fonts[D_80248E84];
            i = 0;
            var_a0 += 3;
        } else {
            D_80289380[D_80248E8C].unk14[i] = arg2[var_a0];
            if (arg2[var_a0] == -1) {
                sp24 = TRUE;
                break;
            }
            var_a0++;
            i++;
        }
    }
    if (var_a0 == arg3) {
        D_80289380[D_80248E8C].unk14[i] = -1;
    }
    D_80248E8C++;
    if (sp24) {
        ret = -1;
    } else {
        ret = var_a0;
    }
    return ret;
}

void uvFont_80219ACC(s32 x, s32 y, char* arg2) {
    char* temp_v0_3;
    s32 var_s7;
    ParsedUVFT* temp_s3;
    s32 i;

    temp_s3 = gGfxUnkPtrs->fonts[D_80248E84];
    y += (s32)(temp_s3->bitmap[1].actualHeight * D_80248E80);
    y = SCREEN_HEIGHT - y;

    D_80289380[D_80248E8C].x = x;
    D_80289380[D_80248E8C].y = y;
    D_80289380[D_80248E8C].r = D_80248E64;
    D_80289380[D_80248E8C].g = D_80248E68;
    D_80289380[D_80248E8C].b = D_80248E6C;
    D_80289380[D_80248E8C].a = D_80248E70;
    D_80289380[D_80248E8C].scaleX = D_80248E7C;
    D_80289380[D_80248E8C].scaleY = D_80248E80;
    var_s7 = uvStrlen(arg2);
    if (var_s7 > 44) {
        arg2[44] = '\0';
        var_s7 = 44;
    }

    for (i = 0; i < var_s7; i++) {
        temp_v0_3 = uvStrchr(temp_s3->str, arg2[i]);
        if (temp_v0_3 != 0) {
            D_80289380[D_80248E8C].unk14[i] = temp_v0_3 - temp_s3->str;
        } else {
            D_80289380[D_80248E8C].unk14[i] = -2;
        }
    }

    D_80289380[D_80248E8C].unk14[var_s7] = -1;
    D_80289380[D_80248E8C].unk6C = gGfxUnkPtrs->fonts[D_80248E84];
    D_80248E8C++;
}

s32 func_80219CC0(Sprite* arg0, s16* arg1, ParsedUVFT* arg2) {
    s32 var_a3;
    s32 i;
    Bitmap* bitmap;

    bitmap = arg0->bitmap;
    for (i = 0, var_a3 = 0; arg1[i] != -1; i++) {
        if ((arg1[i] == -2) || (arg1[i] == -3)) {
            bitmap[i] = arg2->bitmap[0];
            bitmap[i].buf = NULL;
            var_a3 += arg2->bitmap[0].width;
        } else {
            bitmap[i] = arg2->bitmap[arg1[i]];
            var_a3 += arg2->bitmap[arg1[i]].width;
        }
    }
    arg0->nbitmaps = i;
    return var_a3;
}

void func_80219DA4(Unk80289380* arg0) {
    Gfx* dlist;
    Sprite* sprite = &D_80248E20;

    sprite->height = arg0->unk6C->bitmap[1].actualHeight;
    sprite->width = func_80219CC0(sprite, arg0->unk14, arg0->unk6C);
    sprite->bmfmt = arg0->unk6C->bmfmt;
    sprite->bmsiz = arg0->unk6C->bmsiz;
    spMove(sprite, arg0->x, arg0->y);
    spColor(sprite, arg0->r, arg0->g, arg0->b, arg0->a);
    spScale(sprite, arg0->scaleX, arg0->scaleY);
    dlist = spDraw(sprite);
    if (dlist != NULL) {
        gSPDisplayList(gGfxDisplayListHead++, dlist);
    }
    gGfxStateStackData = (gGfxStateStackData & ~0xFFF) | 0xFFE;
    D_8029926C = 0xFFE;
}

void uvFont_80219EA8(void) {
    static s32 D_80248E90 = 0;
    static s32 D_80248E94 = 0;
    Unk80289380* var_s1;
    s32 i;

    if (D_80248E8C == 0) {
        return;
    }

    if (D_80248E94 != gGfxFbIndex) {
        D_80248E90 = 0;
        D_80248E94 = gGfxFbIndex;
    }
    spInit(&gGfxDisplayListHead);
    D_80248E20.rsp_dl_next = &D_80248E20.rsp_dl[(gGfxFbIndex * 7944) + D_80248E90];

    for (i = 0; i < D_80248E8C; i++) {
        func_80219DA4(&D_80289380[i]);
    }
    spFinish(&gGfxDisplayListHead);
    gGfxDisplayListHead--;
    D_80248E90 += D_80248E8C;
    D_80248E8C = 0;
}
