#include <uv_graphics.h>
#include <uv_memory.h>
#include <uv_sprite.h>
#include <libc/stdarg.h>
#include "common.h"

unk_UVTX_1C D_802C5FD0[10];
u16 D_802C60E8[500];
s32 gSprtUnkIndex;
unk_UVTX_1C* gSprtUnkTable[1000];
uvSprite_t gSprtTable1[31];

extern Gfx* gGfxDisplayListHead;
extern u16 gGfxFbIndex;
extern s32 gGfxStateStackData;
extern s32 D_8029926C;

void uvSprt_80230130(void) {
    s32 i;

    for (i = 0; i < 10; i++) {
        D_802C5FD0[i].unk18 = 0;
        D_802C5FD0[i].unk0 = D_802C5FD0[i].unk4 = D_802C5FD0[i].unk8 = D_802C5FD0[i].unkC = D_802C5FD0[i].unk10 = D_802C5FD0[i].unk14 = 0.0f;
    }

    // clang-format off
    for (i = 0; i < 500; i++) { D_802C60E8[i] = 255; }
    // clang-format on

    gSprtUnkIndex = 0;
}

void uvSprt_802301A4(void) {
    unk_UVTX_1C* var_v0;
    s32 i;
    f32 temp_fv0;

    temp_fv0 = uvGfxGetUnkStateF();

    for (i = 0; i < gSprtUnkIndex + 10; i++) {
        if (i < 10) {
            var_v0 = &D_802C5FD0[i];
        } else {
            var_v0 = gSprtUnkTable[i - 10];
        }

        if (var_v0->unk18 == 0) {
            continue;
        }

        var_v0->unk10 += var_v0->unk8 * temp_fv0;
        if (var_v0->unk8 > 0.0f) {
            if (var_v0->unk10 >= 1.0f) {
                var_v0->unk10 -= 1.0f;
            }
        }
        if (var_v0->unk8 < 0.0f) {
            if (var_v0->unk10 <= 0) {
                var_v0->unk10 += 1.0f;
            }
        }

        var_v0->unk14 += var_v0->unkC * temp_fv0;
        if (var_v0->unkC > 0.0f) {
            if (var_v0->unk14 >= 1.0f) {
                var_v0->unk14 -= 1.0f;
            }
        }
        if (var_v0->unkC < 0.0f) {
            if (var_v0->unk14 <= 0) {
                var_v0->unk14 += 1.0f;
            }
        }
    }
}

void _uvTxtDraw(s32 textureId) {
    unk_UVTX_1C* temp_a1;
    uvGfxUnkStructTexture* temp_a2;
    s32 temp_a3;
    s32 temp_t1;
    s32 temp_ft1;
    s32 temp_ft0;

    temp_a2 = gGfxUnkPtrs->unk910[textureId];
    if (temp_a2 == NULL) {
        _uvDebugPrintf("_uvTxtDraw: texture id %d not in current level\n", textureId);
        return;
    }

    gSPDisplayList(gGfxDisplayListHead++, OS_PHYSICAL_TO_K0(temp_a2->unk4));

    if (temp_a2->unk18 != NULL) {
        temp_a1 = temp_a2->unk18;
        if (temp_a1->unk18 != 0) {
            temp_ft1 = temp_a1->unk10 * temp_a2->width * 4.0f;
            temp_ft0 = temp_a1->unk14 * temp_a2->height * 4.0f;
            gDPSetTileSize(gGfxDisplayListHead++, 1, temp_ft1, temp_ft0, (((temp_a2->width * 4) + temp_ft1) - 1), (((temp_a2->height * 4) + temp_ft0) - 1));
        }
    }

    if (temp_a2->unk1C != NULL) {
        temp_a1 = temp_a2->unk1C;
        if (temp_a1->unk18 != 0) {
            temp_a3 = gGfxUnkPtrs->unk910[temp_a2->unk14]->width;
            temp_t1 = gGfxUnkPtrs->unk910[temp_a2->unk14]->height;

            temp_ft1 = temp_a1->unk10 * temp_a3 * 4.0f;
            temp_ft0 = temp_a1->unk14 * temp_t1 * 4.0f;

            gDPSetTileSize(gGfxDisplayListHead++, 0, temp_ft1, temp_ft0, (((temp_a3 * 4) + temp_ft1) - 1), (((temp_t1 * 4) + temp_ft0) - 1));
        }
    }

    if (D_802C60E8[textureId] != 0xFF) {
        temp_a1 = &D_802C5FD0[D_802C60E8[textureId]];
        if (temp_a1->unk18 != 0) {
            temp_ft1 = temp_a1->unk10 * temp_a2->width * 4.0f;
            temp_ft0 = temp_a1->unk14 * temp_a2->height * 4.0f;

            gDPSetTileSize(gGfxDisplayListHead++, 0, temp_ft1, temp_ft0, ((temp_a2->width + temp_ft1) - 1), ((temp_a2->height + temp_ft0) - 1));
        }
    }
}

void uvSprtFromBitmap(uvSprite_t* arg0, uvGfxUnkStructTexture* arg1) {
    if (arg0->textureId == 0xFFFF) {
        _uvDebugPrintf("Warning: Bitmap sprite switched to texture sprite w/o uvMemReset\n");
        arg0->bitmap = NULL;
    }
    if (arg0->bitmap == 0) {
        arg0->bitmap = _uvMemAlloc(sizeof(Bitmap), 4);
    }
    if (arg0->unk58[0] == NULL) {
        arg0->unk58[0] = _uvMemAlloc((1 + 2) * 0xC * sizeof(Gfx), 8);
        arg0->unk58[1] = _uvMemAlloc((1 + 2) * 0xC * sizeof(Gfx), 8);
    }
    arg0->bitmap->width = arg1->width - 1;
    arg0->bitmap->width_img = arg1->width;
    arg0->bitmap->s = 0;
    arg0->bitmap->t = 0;
    arg0->bitmap->buf = arg1->unk0;
    arg0->bitmap->actualHeight = arg1->height;
    arg0->bitmap->LUToffset = 0;
}

void uvSprt_80230750(uvSprite_t* arg0, uvGfxUnkStructTexture* arg1) {
    Sprite* sprite = &arg0->sprite;

    if (arg1 != NULL) {
        sprite->width = arg1->width - 1;
        sprite->height = arg1->height - 1;
        sprite->bmheight = arg1->height - 1;
        sprite->bmHreal = arg1->height;
        sprite->bmfmt = 0;
        sprite->bmsiz = 2;
        sprite->attr = SP_TEXSHUF;
        if (arg1->unk22 != 1) {
            sprite->attr |= SP_TRANSPARENT;
        }
        if (arg1->unk22 == 1) {
            sprite->bmfmt = G_IM_FMT_I;
        } else if (arg1->unk22 == 2) {
            sprite->bmfmt = G_IM_FMT_IA;
        } else {
            sprite->bmfmt = G_IM_FMT_RGBA;
        }

        if (arg1->unkE == 4) {
            sprite->bmsiz = G_IM_SIZ_4b;
        } else if (arg1->unkE == 8) {
            sprite->bmsiz = G_IM_SIZ_8b;
        } else {
            sprite->bmsiz = G_IM_SIZ_16b;
        }
        sprite->scalex = 1.0f;
        sprite->scaley = 1.0f;
    }

    sprite->expx = 0;
    sprite->expy = 0;
    sprite->zdepth = 0x1234;
    sprite->red = 255;
    sprite->green = 255;
    sprite->blue = 255;
    sprite->alpha = 255;
    sprite->startTLUT = 0;
    sprite->nTLUT = 0;
    sprite->LUT = NULL;
    sprite->istart = 0;
    sprite->istep = 1;
    sprite->nbitmaps = 1;
    sprite->ndisplist = (1 + 2) * 0xC;
    sprite->scalex = 1.0f;
    sprite->scaley = 1.0f;
    sprite->bitmap = arg0->bitmap;
    sprite->frac_s = 0;
    sprite->frac_t = 0;
}

s32 uvSprt_80230898(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gSprtTable1); i++) {
        if (gSprtTable1[i].unk0 == 0) {
            return i;
        }
    }

    return 0xFF;
}

void uvSprtInit(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gSprtTable1); i++) {
        gSprtTable1[i].unk0 = 0;
        gSprtTable1[i].unk1 = 0;
        gSprtTable1[i].width = gSprtTable1[i].height = 0;
        gSprtTable1[i].unk6 = gSprtTable1[i].unk8 = 0;
        gSprtTable1[i].red = 255;
        gSprtTable1[i].green = 255;
        gSprtTable1[i].blue = 255;
        gSprtTable1[i].alpha = 255;
        gSprtTable1[i].textureId = 0xFFF;
        gSprtTable1[i].bitmap = NULL;
        gSprtTable1[i].unk58[0] = NULL;
        gSprtTable1[i].unk58[1] = NULL;
    }
}

void uvSprtDisplayList(uvSprite_t* arg0) {
    Gfx* dlist;
    f32 temp_fv0;
    f32 temp_fv1;
    Sprite* sprite = &arg0->sprite;

    sprite->rsp_dl = arg0->unk58[gGfxFbIndex];
    sprite->rsp_dl_next = sprite->rsp_dl;

    if (arg0->textureId != 0xFFFF) {
        temp_fv0 = (f32)arg0->width / gGfxUnkPtrs->unk910[arg0->textureId]->width;
        temp_fv1 = (f32)arg0->height / gGfxUnkPtrs->unk910[arg0->textureId]->height;
        spScale(sprite, temp_fv0, temp_fv1);
    } else {
        spScale(sprite, 1.0f, 1.0f);
    }
    sprite->red = arg0->red;
    sprite->green = arg0->green;
    sprite->blue = arg0->blue;
    sprite->alpha = arg0->alpha;
    spMove(sprite, arg0->unk6, (s16)(SCREEN_HEIGHT - arg0->unk8));
    dlist = spDraw(sprite);
    if (dlist != NULL) {
        gSPDisplayList(gGfxDisplayListHead++, dlist);
    }
    gGfxStateStackData = (gGfxStateStackData & ~0xFFF) | 0xFFE;
    D_8029926C = 0xFFE;
}

void uvSprtDrawAll(void) {
    uvSprite_t* var_s0;
    uvSprite_t* var_s1;

    spInit(&gGfxDisplayListHead);
    // clang-format off: must preserve same line assignments
    var_s0 = &gSprtTable1[0]; var_s1 = &gSprtTable1[ARRAY_COUNT(gSprtTable1)];
    // clang-format on
    do {
        if ((var_s0->unk0 != 0) && (var_s0->unk1 != 0) && (var_s0->textureId != 0xFFF)) {
            uvSprtDisplayList(var_s0);
        }
        var_s0++;
    } while (var_s0 != var_s1);
    spFinish(&gGfxDisplayListHead);
    gGfxDisplayListHead--;
}

void uvSprtDraw(s32 sprite_id) {
    uvSprite_t* sprite;

    if (sprite_id >= ARRAY_COUNT(gSprtTable1)) {
        _uvDebugPrintf("uvSprtDraw: invalid sprite id %d\n", sprite_id);
        return;
    }
    sprite = &gSprtTable1[sprite_id];
    if (sprite->textureId != 0xFFF) {
        spInit(&gGfxDisplayListHead);
        uvSprtDisplayList(sprite);
        spFinish(&gGfxDisplayListHead);
        gGfxDisplayListHead--;
    }
}

void uvSprtSetBlit(uvSprite_t* arg0, s32 arg1) {
    uvGfxUnkStructBlit* var_v1;
    Sprite* sprite = &arg0->sprite;

    var_v1 = gGfxUnkPtrs->unk1410[arg1];
    if ((arg0->textureId == 0xFFFF) || (arg0->textureId != 0xFFF)) {
        if (arg0->width != var_v1->width || arg0->height != var_v1->height) {
            _uvDebugPrintf("uvSprtSetBlit: Warning: sprite %d size change, dl space leaked\n", gSprtTable1 - arg0);
            arg0->unk58[0] = NULL;
            arg0->unk58[1] = NULL;
        }
    }
    arg0->sprite.bitmap = var_v1->bitmap;
    arg0->textureId = 0xFFFF;
    arg0->width = var_v1->width;
    arg0->height = var_v1->height;
    arg0->sprite.width = var_v1->width;
    arg0->sprite.height = var_v1->height;
    arg0->sprite.bitmap = var_v1->bitmap;
    arg0->sprite.nbitmaps = var_v1->nbitmaps;
    arg0->sprite.ndisplist = (var_v1->nbitmaps + 2) * 0xC;
    arg0->sprite.bmheight = var_v1->texelHeight;
    arg0->sprite.bmHreal = var_v1->texelHeight;
    arg0->sprite.bmfmt = var_v1->bmfmt;

    switch (var_v1->bitdepth) {
    case 4:
        arg0->sprite.bmsiz = G_IM_SIZ_4b;
        break;
    case 8:
        arg0->sprite.bmsiz = G_IM_SIZ_8b;
        break;
    case 16:
        arg0->sprite.bmsiz = G_IM_SIZ_16b;
        break;
    case 32:
        arg0->sprite.bmsiz = G_IM_SIZ_32b;
        break;
    }
    arg0->sprite.istart = 0;
    arg0->sprite.istep = 1;
    if (arg0->unk58[0] == NULL) {
        arg0->unk58[0] = (Gfx*)_uvMemAlloc(((var_v1->nbitmaps + 2) * 0xC * sizeof(Gfx)), 8);
    }
    if (arg0->unk58[1] == NULL) {
        arg0->unk58[1] = (Gfx*)_uvMemAlloc(((var_v1->nbitmaps + 2) * 0xC * sizeof(Gfx)), 8);
    }

    switch (var_v1->bmfmt) {
    case G_IM_FMT_RGBA:
        if (var_v1->bitdepth == 16) {
            sprite->attr = SP_TEXSHUF | SP_FASTCOPY | SP_CUTOUT;
        } else {
            sprite->attr = SP_CUTOUT;
        }
        break;
    case G_IM_FMT_IA:
        sprite->attr = SP_TEXSHUF | SP_CUTOUT;
        break;
    case G_IM_FMT_I:
        sprite->attr = SP_TEXSHUF;
        break;
    default:
        _uvDebugPrintf("Sprite Format %d is not supported.\n", var_v1->bmfmt);
        sprite->attr = SP_TEXSHUF | SP_FASTCOPY | SP_CUTOUT;
        break;
    }

    sprite->expx = 0;
    sprite->expy = 0;
    sprite->zdepth = 0x1234;
    sprite->red = 255;
    sprite->green = 255;
    sprite->blue = 255;
    sprite->alpha = 255;
    sprite->startTLUT = 0;
    sprite->nTLUT = 0;
    sprite->LUT = NULL;
    sprite->frac_s = 0;
    sprite->frac_t = 0;
    sprite->scalex = 1.0f;
    sprite->scaley = 1.0f;
}

s16 uvSprtGetWidth(s32 sprite_id) {
    return gSprtTable1[sprite_id].width;
}

s16 uvSprtGetHeight(s32 sprite_id) {
    return gSprtTable1[sprite_id].height;
}

void uvSprtProps(s32 sprite_id, ...) {
    uvGfxUnkStructTexture* temp_s2;
    uvSprite_t* temp_s1;
    va_list args;
    s32 token;

    if (sprite_id >= ARRAY_COUNT(gSprtTable1)) {
        _uvDebugPrintf("uvSprtProps: invalid sprite id %d\n", sprite_id);
        return;
    }

    temp_s1 = &gSprtTable1[sprite_id];
    va_start(args, sprite_id);

    while (TRUE) {
        token = va_arg(args, s32);
        switch (token) {
        case 0:
            return;
        case 1:
            temp_s1->width = va_arg(args, s32);

            if (temp_s1->width <= 0) {
                temp_s1->width = 1;
            }

            temp_s1->height = va_arg(args, s32);
            if (temp_s1->height <= 0) {
                temp_s1->height = 1;
            }
            break;
        case 2:
            temp_s1->unk6 = va_arg(args, s32);
            temp_s1->unk8 = va_arg(args, s32);
            break;
        case 7:
            temp_s1->red = va_arg(args, s32);
            temp_s1->green = va_arg(args, s32);
            temp_s1->blue = va_arg(args, s32);
            temp_s1->alpha = va_arg(args, s32);
            break;
        case 3:
            temp_s1->unk0 = va_arg(args, s32);
            break;
        case 9:
            uvSprtSetBlit(temp_s1, va_arg(args, s32));
            break;
        case 8:
            _uvDebugPrintf("uvSprtProps: bitmaps are replaced by blits.\n");
            break;
        case 5:
            temp_s1->textureId = va_arg(args, s32);
            if (temp_s1->textureId != 0xFFF) {
                temp_s2 = gGfxUnkPtrs->unk910[temp_s1->textureId];
                if (temp_s2 == NULL) {
                    _uvDebugPrintf(" uvSprtProps: texture id %d not in level\n", temp_s1->textureId);
                    temp_s1->textureId = 0xFFF;
                } else {
                    uvSprtFromBitmap(temp_s1, temp_s2);
                    uvSprt_80230750(temp_s1, temp_s2);
                }
            }
            break;
        case 10:
            if (va_arg(args, s32) == 0) {
                temp_s1->sprite.attr &= ~SP_FASTCOPY;
            } else {
                temp_s1->sprite.attr |= SP_FASTCOPY;
            }
            break;
        case 11:
            if (va_arg(args, s32) == 0) {
                temp_s1->sprite.attr &= ~SP_TRANSPARENT;
            } else {
                temp_s1->sprite.attr |= SP_TRANSPARENT;
            }
            break;
        default:
            _uvDebugPrintf("uvSprtProps: unknown token %d in args\n", token);
            break;
        }
    }
}

void uvSprtUpdateUnk(ParsedUVTX* arg0) {
    if (arg0->unk18 != NULL) {
        gSprtUnkTable[gSprtUnkIndex] = arg0->unk18;
        gSprtUnkIndex += 1;
    }
    if (arg0->unk1C != NULL) {
        gSprtUnkTable[gSprtUnkIndex] = arg0->unk1C;
        gSprtUnkIndex += 1;
    }
}

void uvSprtResetUnk(void) {
    gSprtUnkIndex = 0;
}

