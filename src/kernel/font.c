#include "common.h"
#include <uv_filesystem.h>
#include <uv_graphics.h>
#include <uv_memory.h>
#include <uv_font.h>
#include <uv_string.h>

#define FONT_MAX_MSG_LEN 44

// struct containing a printed string's font data
// contains position, scale, color, string, pointer to font
typedef struct Unk80289380 {
    s32 x;
    s32 y;
    f32 scaleX;
    f32 scaleY;
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    s16 str16[FONT_MAX_MSG_LEN];
    ParsedUVFT* font;
} FontMessage; // size = 0x70

STATIC_DATA Bitmap sFontBitmaps[FONT_MAX_MSG_LEN];
STATIC_DATA Gfx sFontDList[7944 * 2];
STATIC_DATA FontMessage sFontMessages[30];

STATIC_DATA Sprite sFontSprite = {
    0,            // x
    0,            // y
    0,            // width
    0,            // height
    1.0f,         // scalex
    1.0f,         // scaley
    0,            // expx
    0,            // expy
    1,            // attr
    0x1234,       // zdepth
    255,          // red
    255,          // green
    255,          // blue
    255,          // alpha
    0,            // startTLUT
    0,            // nTLUT
    NULL,         // LUT
    0,            // istart
    1,            // istep
    660,          // nbitmaps
    7944,         // ndisplist
    15,           // bmheight
    128,          // bmHreal
    G_IM_FMT_IA,  // bmfmt
    G_IM_SIZ_4b,  // bmsiz
    sFontBitmaps, // bitmap
    sFontDList,   // rsp_dl
    NULL,         // rsp_dl_next
    0,            // frac_s
    0             // frac_t
};

STATIC_DATA u8 sFontColorR = 0xFF;
STATIC_DATA u8 sFontColorG = 0xFF;
STATIC_DATA u8 sFontColorB = 0xFF;
STATIC_DATA u8 sFontColorA = 0xFF;
STATIC_DATA UNUSED s32 D_80248E74 = 0;
STATIC_DATA UNUSED s32 D_80248E78 = 0;

STATIC_DATA f32 sFontScaleX = 1.0f;
STATIC_DATA f32 sFontScaleY = 1.0f;
STATIC_DATA u32 sFontCurId = 0;
STATIC_DATA u32 sFontCurWidth = 8;
STATIC_DATA s32 sFontMsgCount = 0;

ParsedUVFT* uvParseTopUVFT(s32 arg0) {
    ParsedUVFT* ret;
    s32 idx;
    u32 nbytes;
    s32* srcAddr;
    s32 i;
    s32 imagCount;
    s32 bitmCount;
    u32 tag;

    imagCount = 0;
    ret = (ParsedUVFT*)_uvMemAlloc(sizeof(ParsedUVFT), 4);
    idx = uvFileReadHeader(gUVBlockOffsets.UVFT[arg0]);
    while ((tag = uvFileReadBlock(idx, &nbytes, (void**)&srcAddr, 1)) != NULL) {
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

    uvFile_80223F30(idx);
    // update indexes to pointers allocated above
    for (i = 0; i < bitmCount; i++) {
        ret->bitmap[i].buf = ret->imag[(u32)ret->bitmap[i].buf];
    }
    return ret;
}

void uvFontSet(s32 fontId) {
    if (gGfxUnkPtrs->fonts[fontId] != NULL) {
        sFontCurId = fontId;
    } else {
        _uvDebugPrintf("uvFontSet ( %d ) -- font does not exist in level\n", fontId);
    }
    sFontCurWidth = gGfxUnkPtrs->fonts[sFontCurId]->bitmap->width;
}

void uvFontScale(f64 x, f64 y) {
    sFontScaleX = x;
    sFontScaleY = y;
}

void uvFontColor(u8 r, u8 g, u8 b, u8 a) {
    sFontColorR = r;
    sFontColorG = g;
    sFontColorB = b;
    sFontColorA = a;
}

STATIC_FUNC s32 uvFontStrLen(s16* str16) {
    s32 len;

    len = 0;
    while (len < FONT_MAX_MSG_LEN && str16[len] != -1) {
        len++;
    }
    return len;
}

// returns scaled width of 16-bit string for a given font
STATIC_FUNC s32 uvFontStr16WidthFont(ParsedUVFT* font, s16* str16) {
    s32 len;
    s32 i;
    s32 pixWidth;
    s32 j;

    len = uvFontStrLen(str16);

    pixWidth = 0;
    for (i = 0, j = 0; i < len; i++, j++) {
        if (str16[j] == -1) {
            return pixWidth;
        }
        if ((str16[j] >= 0) && (str16[j] != 0xFFF) && (str16[j] != 0xFFE)) {
            pixWidth += font->bitmap[str16[j]].width;
        } else {
            pixWidth += sFontCurWidth;
        }
    }

    return pixWidth * sFontScaleX;
}

// returns scaled width of 16-bit string for the current font
s32 uvFontStr16Width(s16* str16) {
    return uvFontStr16WidthFont(gGfxUnkPtrs->fonts[sFontCurId], str16);
}

// returns scaled width of ASCII string for a given font
STATIC_FUNC s32 uvFontStrWidth(ParsedUVFT* font, const char* str) {
    s32 len;
    char* ch;
    s32 width;
    s32 i;
    s32 j;

    len = uvStrlen(str);

    width = 0;
    for (i = 0, j = 0; i < len; i++, j++) {
        if (str[j] == 0) {
            return width;
        }
        if (str[j] == '\n') {
            continue;
        }
        ch = uvStrchr(font->str, str[j]);
        if (ch != 0) {
            width += font->bitmap[ch - font->str].width;
        } else {
            width += sFontCurWidth;
        }
    }

    return width * sFontScaleX;
}

// returns scaled width of ASCII string for the current font
s32 uvFontWidth(const char* str) {
    return uvFontStrWidth(gGfxUnkPtrs->fonts[sFontCurId], str);
}

// returns scaled height for the current font
s32 uvFontHeight(void) {
    ParsedUVFT* font = gGfxUnkPtrs->fonts[sFontCurId];
    return font->bitmap[1].actualHeight * sFontScaleY;
}

// adds str16 to messages using current font settings
s32 uvFontPrintStr16(s32 x, s32 y, s16* str16, s32 strLen, s32 end) {
    s32 i16;
    s32 i;
    s32 sp24;
    s32 ret;
    ParsedUVFT* temp_v1;
    s32 endCh = end;

    temp_v1 = gGfxUnkPtrs->fonts[sFontCurId];

    y += (s32)(temp_v1->bitmap[1].actualHeight * sFontScaleY);
    y = SCREEN_HEIGHT - y;
    sFontMessages[sFontMsgCount].x = x;
    sFontMessages[sFontMsgCount].y = y;
    sFontMessages[sFontMsgCount].r = sFontColorR;
    sFontMessages[sFontMsgCount].g = sFontColorG;
    sFontMessages[sFontMsgCount].b = sFontColorB;
    sFontMessages[sFontMsgCount].a = sFontColorA;
    sFontMessages[sFontMsgCount].scaleX = sFontScaleX;
    sFontMessages[sFontMsgCount].scaleY = sFontScaleY;
    sFontMessages[sFontMsgCount].font = gGfxUnkPtrs->fonts[sFontCurId];
    if (strLen > FONT_MAX_MSG_LEN) {
        strLen = FONT_MAX_MSG_LEN;
    }
    i16 = 0;
    i = 0;
    sp24 = FALSE;
    if (str16[i16] == 0xFD) {
        // FAKE
        if (str16[i16 + 1]) { }
        sFontMessages[sFontMsgCount].x = str16[i16 + 1];
        i16 += 3;
    }

    while (i < strLen) {
        if (str16[i16] == endCh) {
            sFontMessages[sFontMsgCount].str16[i] = -1;
            i16++;
            i++;
            break;
        }

        if (str16[i16] == 0xFD) {
            sFontMessages[sFontMsgCount].str16[i] = -1;
            sFontMsgCount++;
            sFontMessages[sFontMsgCount].r = sFontColorR;
            sFontMessages[sFontMsgCount].g = sFontColorG;
            sFontMessages[sFontMsgCount].b = sFontColorB;
            sFontMessages[sFontMsgCount].a = sFontColorA;
            sFontMessages[sFontMsgCount].scaleX = sFontScaleX;
            sFontMessages[sFontMsgCount].scaleY = sFontScaleY;
            sFontMessages[sFontMsgCount].x = str16[i16 + 1];
            sFontMessages[sFontMsgCount].y = y;
            sFontMessages[sFontMsgCount].font = gGfxUnkPtrs->fonts[sFontCurId];
            i = 0;
            i16 += 3;
        } else {
            sFontMessages[sFontMsgCount].str16[i] = str16[i16];
            if (str16[i16] == -1) {
                sp24 = TRUE;
                break;
            }
            i16++;
            i++;
        }
    }
    if (i16 == strLen) {
        sFontMessages[sFontMsgCount].str16[i] = -1;
    }
    sFontMsgCount++;
    if (sp24) {
        ret = -1;
    } else {
        ret = i16;
    }
    return ret;
}

void uvFontPrintStr(s32 x, s32 y, const char* str) {
    char* chrPos;
    s32 strLen;
    ParsedUVFT* temp_s3;
    s32 i;

    temp_s3 = gGfxUnkPtrs->fonts[sFontCurId];
    y += (s32)(temp_s3->bitmap[1].actualHeight * sFontScaleY);
    y = SCREEN_HEIGHT - y;

    sFontMessages[sFontMsgCount].x = x;
    sFontMessages[sFontMsgCount].y = y;
    sFontMessages[sFontMsgCount].r = sFontColorR;
    sFontMessages[sFontMsgCount].g = sFontColorG;
    sFontMessages[sFontMsgCount].b = sFontColorB;
    sFontMessages[sFontMsgCount].a = sFontColorA;
    sFontMessages[sFontMsgCount].scaleX = sFontScaleX;
    sFontMessages[sFontMsgCount].scaleY = sFontScaleY;
    strLen = uvStrlen(str);
    if (strLen > FONT_MAX_MSG_LEN) {
        ((char*)str)[FONT_MAX_MSG_LEN] = '\0';
        strLen = FONT_MAX_MSG_LEN;
    }

    for (i = 0; i < strLen; i++) {
        chrPos = uvStrchr(temp_s3->str, str[i]);
        if (chrPos != NULL) {
            sFontMessages[sFontMsgCount].str16[i] = chrPos - temp_s3->str;
        } else {
            sFontMessages[sFontMsgCount].str16[i] = -2;
        }
    }

    sFontMessages[sFontMsgCount].str16[strLen] = -1;
    sFontMessages[sFontMsgCount].font = gGfxUnkPtrs->fonts[sFontCurId];
    sFontMsgCount++;
}

STATIC_FUNC s32 uvFontSpriteWidth(Sprite* sprite, s16* str16, ParsedUVFT* font) {
    s32 width;
    s32 i;
    Bitmap* bitmap;

    bitmap = sprite->bitmap;
    for (i = 0, width = 0; str16[i] != -1; i++) {
        if ((str16[i] == -2) || (str16[i] == -3)) {
            bitmap[i] = font->bitmap[0];
            bitmap[i].buf = NULL;
            width += font->bitmap[0].width;
        } else {
            bitmap[i] = font->bitmap[str16[i]];
            width += font->bitmap[str16[i]].width;
        }
    }
    sprite->nbitmaps = i;
    return width;
}

// generate font dlist for one string of text
STATIC_FUNC void uvFontMsgGenDlist(FontMessage* msg) {
    Gfx* dlist;
    Sprite* sprite = &sFontSprite;

    sprite->height = msg->font->bitmap[1].actualHeight;
    sprite->width = uvFontSpriteWidth(sprite, msg->str16, msg->font);
    sprite->bmfmt = msg->font->bmfmt;
    sprite->bmsiz = msg->font->bmsiz;
    spMove(sprite, msg->x, msg->y);
    spColor(sprite, msg->r, msg->g, msg->b, msg->a);
    spScale(sprite, msg->scaleX, msg->scaleY);
    dlist = spDraw(sprite);
    if (dlist != NULL) {
        gSPDisplayList(gGfxDisplayListHead++, dlist);
    }
    gGfxStateStackData = (gGfxStateStackData & ~0xFFF) | 0xFFE;
    gGfxBoundTexture = 0xFFE;
}

void uvFontGenDlist(void) {
    static s32 D_80248E90 = 0;
    static s32 D_80248E94 = 0;
    s32 i;

    if (sFontMsgCount == 0) {
        return;
    }

    if (D_80248E94 != gGfxFbIndex) {
        D_80248E90 = 0;
        D_80248E94 = gGfxFbIndex;
    }
    spInit(&gGfxDisplayListHead);
    sFontSprite.rsp_dl_next = &sFontSprite.rsp_dl[(gGfxFbIndex * 7944) + D_80248E90];

    for (i = 0; i < sFontMsgCount; i++) {
        uvFontMsgGenDlist(&sFontMessages[i]);
    }
    spFinish(&gGfxDisplayListHead);
    gGfxDisplayListHead--;
    D_80248E90 += sFontMsgCount;
    sFontMsgCount = 0;
}
