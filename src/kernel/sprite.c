#include <uv_graphics.h>
#include <uv_memory.h>
#include <uv_sprite.h>
#include <libc/stdarg.h>
#include "common.h"

UnkUVTX_1C D_802C5FD0[10];
u16 D_802C60E8[500];
s32 gSprtUnkIndex;
UnkUVTX_1C* gSprtUnkTable[1000];
uvSprite_t gSprtTable1[31];

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
    UnkUVTX_1C* var_v0;
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
    UnkUVTX_1C* temp_a1;
    ParsedUVTX* uvtx;
    s32 temp_a3;
    s32 temp_t1;
    s32 temp_ft1;
    s32 temp_ft0;

    uvtx = gGfxUnkPtrs->textures[textureId];
    if (uvtx == NULL) {
        _uvDebugPrintf("_uvTxtDraw: texture id %d not in current level\n", textureId);
        return;
    }

    gSPDisplayList(gGfxDisplayListHead++, OS_PHYSICAL_TO_K0(uvtx->unk4));

    if (uvtx->unk18 != NULL) {
        temp_a1 = uvtx->unk18;
        if (temp_a1->unk18 != 0) {
            temp_ft1 = temp_a1->unk10 * uvtx->width * 4.0f;
            temp_ft0 = temp_a1->unk14 * uvtx->height * 4.0f;
            gDPSetTileSize(gGfxDisplayListHead++, 1, temp_ft1, temp_ft0, (((uvtx->width * 4) + temp_ft1) - 1), (((uvtx->height * 4) + temp_ft0) - 1));
        }
    }

    if (uvtx->unk1C != NULL) {
        temp_a1 = uvtx->unk1C;
        if (temp_a1->unk18 != 0) {
            temp_a3 = gGfxUnkPtrs->textures[uvtx->unk14]->width;
            temp_t1 = gGfxUnkPtrs->textures[uvtx->unk14]->height;

            temp_ft1 = temp_a1->unk10 * temp_a3 * 4.0f;
            temp_ft0 = temp_a1->unk14 * temp_t1 * 4.0f;

            gDPSetTileSize(gGfxDisplayListHead++, 0, temp_ft1, temp_ft0, (((temp_a3 * 4) + temp_ft1) - 1), (((temp_t1 * 4) + temp_ft0) - 1));
        }
    }

    if (D_802C60E8[textureId] != 0xFF) {
        temp_a1 = &D_802C5FD0[D_802C60E8[textureId]];
        if (temp_a1->unk18 != 0) {
            temp_ft1 = temp_a1->unk10 * uvtx->width * 4.0f;
            temp_ft0 = temp_a1->unk14 * uvtx->height * 4.0f;

            gDPSetTileSize(gGfxDisplayListHead++, 0, temp_ft1, temp_ft0, ((uvtx->width + temp_ft1) - 1), ((uvtx->height + temp_ft0) - 1));
        }
    }
}

void uvSprtFromBitmap(uvSprite_t* sprite, ParsedUVTX* uvtx) {
    if (sprite->textureId == 0xFFFF) {
        _uvDebugPrintf("Warning: Bitmap sprite switched to texture sprite w/o uvMemReset\n");
        sprite->bitmap = NULL;
    }
    if (sprite->bitmap == 0) {
        sprite->bitmap = _uvMemAlloc(sizeof(Bitmap), 4);
    }
    if (sprite->unk58[0] == NULL) {
        sprite->unk58[0] = _uvMemAlloc((1 + 2) * 0xC * sizeof(Gfx), 8);
        sprite->unk58[1] = _uvMemAlloc((1 + 2) * 0xC * sizeof(Gfx), 8);
    }
    sprite->bitmap->width = uvtx->width - 1;
    sprite->bitmap->width_img = uvtx->width;
    sprite->bitmap->s = 0;
    sprite->bitmap->t = 0;
    sprite->bitmap->buf = uvtx->unk0;
    sprite->bitmap->actualHeight = uvtx->height;
    sprite->bitmap->LUToffset = 0;
}

void uvSprt_80230750(uvSprite_t* sprite, ParsedUVTX* uvtx) {
    Sprite* sp = &sprite->sprite;

    if (uvtx != NULL) {
        sp->width = uvtx->width - 1;
        sp->height = uvtx->height - 1;
        sp->bmheight = uvtx->height - 1;
        sp->bmHreal = uvtx->height;
        sp->bmfmt = 0;
        sp->bmsiz = 2;
        sp->attr = SP_TEXSHUF;
        if (uvtx->unk22 != 1) {
            sp->attr |= SP_TRANSPARENT;
        }
        if (uvtx->unk22 == 1) {
            sp->bmfmt = G_IM_FMT_I;
        } else if (uvtx->unk22 == 2) {
            sp->bmfmt = G_IM_FMT_IA;
        } else {
            sp->bmfmt = G_IM_FMT_RGBA;
        }

        if (uvtx->unkE == 4) {
            sp->bmsiz = G_IM_SIZ_4b;
        } else if (uvtx->unkE == 8) {
            sp->bmsiz = G_IM_SIZ_8b;
        } else {
            sp->bmsiz = G_IM_SIZ_16b;
        }
        sp->scalex = 1.0f;
        sp->scaley = 1.0f;
    }

    sp->expx = 0;
    sp->expy = 0;
    sp->zdepth = 0x1234;
    sp->red = 255;
    sp->green = 255;
    sp->blue = 255;
    sp->alpha = 255;
    sp->startTLUT = 0;
    sp->nTLUT = 0;
    sp->LUT = NULL;
    sp->istart = 0;
    sp->istep = 1;
    sp->nbitmaps = 1;
    sp->ndisplist = (1 + 2) * 0xC;
    sp->scalex = 1.0f;
    sp->scaley = 1.0f;
    sp->bitmap = sprite->bitmap;
    sp->frac_s = 0;
    sp->frac_t = 0;
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

void uvSprtDisplayList(uvSprite_t* sprite) {
    Gfx* dlist;
    f32 temp_fv0;
    f32 temp_fv1;
    Sprite* sp = &sprite->sprite;

    sp->rsp_dl = sprite->unk58[gGfxFbIndex];
    sp->rsp_dl_next = sp->rsp_dl;

    if (sprite->textureId != 0xFFFF) {
        temp_fv0 = (f32)sprite->width / gGfxUnkPtrs->textures[sprite->textureId]->width;
        temp_fv1 = (f32)sprite->height / gGfxUnkPtrs->textures[sprite->textureId]->height;
        spScale(sp, temp_fv0, temp_fv1);
    } else {
        spScale(sp, 1.0f, 1.0f);
    }
    sp->red = sprite->red;
    sp->green = sprite->green;
    sp->blue = sprite->blue;
    sp->alpha = sprite->alpha;
    spMove(sp, sprite->unk6, (s16)(SCREEN_HEIGHT - sprite->unk8));
    dlist = spDraw(sp);
    if (dlist != NULL) {
        gSPDisplayList(gGfxDisplayListHead++, dlist);
    }
    gGfxStateStackData = (gGfxStateStackData & ~0xFFF) | 0xFFE;
    gGfxBoundTexture = 0xFFE;
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

void uvSprtDraw(s32 spriteId) {
    uvSprite_t* sprite;

    if (spriteId >= ARRAY_COUNT(gSprtTable1)) {
        _uvDebugPrintf("uvSprtDraw: invalid sprite id %d\n", spriteId);
        return;
    }
    sprite = &gSprtTable1[spriteId];
    if (sprite->textureId != 0xFFF) {
        spInit(&gGfxDisplayListHead);
        uvSprtDisplayList(sprite);
        spFinish(&gGfxDisplayListHead);
        gGfxDisplayListHead--;
    }
}

void uvSprtSetBlit(uvSprite_t* sprite, s32 blitId) {
    ParsedUVBT* uvbt = gGfxUnkPtrs->blits[blitId];
    Sprite* sp = &sprite->sprite;

    if ((sprite->textureId == 0xFFFF) || (sprite->textureId != 0xFFF)) {
        if (sprite->width != uvbt->width || sprite->height != uvbt->height) {
            _uvDebugPrintf("uvSprtSetBlit: Warning: sprite %d size change, dl space leaked\n", gSprtTable1 - sprite);
            sprite->unk58[0] = NULL;
            sprite->unk58[1] = NULL;
        }
    }
    sprite->sprite.bitmap = uvbt->bitmap;
    sprite->textureId = 0xFFFF;
    sprite->width = uvbt->width;
    sprite->height = uvbt->height;
    sprite->sprite.width = uvbt->width;
    sprite->sprite.height = uvbt->height;
    sprite->sprite.bitmap = uvbt->bitmap;
    sprite->sprite.nbitmaps = uvbt->nbitmaps;
    sprite->sprite.ndisplist = (uvbt->nbitmaps + 2) * 0xC;
    sprite->sprite.bmheight = uvbt->texelHeight;
    sprite->sprite.bmHreal = uvbt->texelHeight;
    sprite->sprite.bmfmt = uvbt->bmfmt;

    switch (uvbt->bitdepth) {
    case 4:
        sprite->sprite.bmsiz = G_IM_SIZ_4b;
        break;
    case 8:
        sprite->sprite.bmsiz = G_IM_SIZ_8b;
        break;
    case 16:
        sprite->sprite.bmsiz = G_IM_SIZ_16b;
        break;
    case 32:
        sprite->sprite.bmsiz = G_IM_SIZ_32b;
        break;
    }
    sprite->sprite.istart = 0;
    sprite->sprite.istep = 1;
    if (sprite->unk58[0] == NULL) {
        sprite->unk58[0] = (Gfx*)_uvMemAlloc(((uvbt->nbitmaps + 2) * 0xC * sizeof(Gfx)), 8);
    }
    if (sprite->unk58[1] == NULL) {
        sprite->unk58[1] = (Gfx*)_uvMemAlloc(((uvbt->nbitmaps + 2) * 0xC * sizeof(Gfx)), 8);
    }

    switch (uvbt->bmfmt) {
    case G_IM_FMT_RGBA:
        if (uvbt->bitdepth == 16) {
            sp->attr = SP_TEXSHUF | SP_FASTCOPY | SP_CUTOUT;
        } else {
            sp->attr = SP_CUTOUT;
        }
        break;
    case G_IM_FMT_IA:
        sp->attr = SP_TEXSHUF | SP_CUTOUT;
        break;
    case G_IM_FMT_I:
        sp->attr = SP_TEXSHUF;
        break;
    default:
        _uvDebugPrintf("Sprite Format %d is not supported.\n", uvbt->bmfmt);
        sp->attr = SP_TEXSHUF | SP_FASTCOPY | SP_CUTOUT;
        break;
    }

    sp->expx = 0;
    sp->expy = 0;
    sp->zdepth = 0x1234;
    sp->red = 255;
    sp->green = 255;
    sp->blue = 255;
    sp->alpha = 255;
    sp->startTLUT = 0;
    sp->nTLUT = 0;
    sp->LUT = NULL;
    sp->frac_s = 0;
    sp->frac_t = 0;
    sp->scalex = 1.0f;
    sp->scaley = 1.0f;
}

s16 uvSprtGetWidth(s32 spriteId) {
    return gSprtTable1[spriteId].width;
}

s16 uvSprtGetHeight(s32 spriteId) {
    return gSprtTable1[spriteId].height;
}

void uvSprtProps(s32 spriteId, ...) {
    ParsedUVTX* uvtx;
    uvSprite_t* sprite;
    va_list args;
    s32 token;

    if (spriteId >= ARRAY_COUNT(gSprtTable1)) {
        _uvDebugPrintf("uvSprtProps: invalid sprite id %d\n", spriteId);
        return;
    }

    sprite = &gSprtTable1[spriteId];
    va_start(args, spriteId);

    while (TRUE) {
        token = va_arg(args, s32);
        switch (token) {
        case 0:
            return;
        case 1:
            sprite->width = va_arg(args, s32);

            if (sprite->width <= 0) {
                sprite->width = 1;
            }

            sprite->height = va_arg(args, s32);
            if (sprite->height <= 0) {
                sprite->height = 1;
            }
            break;
        case 2:
            sprite->unk6 = va_arg(args, s32);
            sprite->unk8 = va_arg(args, s32);
            break;
        case 7:
            sprite->red = va_arg(args, s32);
            sprite->green = va_arg(args, s32);
            sprite->blue = va_arg(args, s32);
            sprite->alpha = va_arg(args, s32);
            break;
        case 3:
            sprite->unk0 = va_arg(args, s32);
            break;
        case 9:
            uvSprtSetBlit(sprite, va_arg(args, s32));
            break;
        case 8:
            _uvDebugPrintf("uvSprtProps: bitmaps are replaced by blits.\n");
            break;
        case 5:
            sprite->textureId = va_arg(args, s32);
            if (sprite->textureId != 0xFFF) {
                uvtx = gGfxUnkPtrs->textures[sprite->textureId];
                if (uvtx == NULL) {
                    _uvDebugPrintf(" uvSprtProps: texture id %d not in level\n", sprite->textureId);
                    sprite->textureId = 0xFFF;
                } else {
                    uvSprtFromBitmap(sprite, uvtx);
                    uvSprt_80230750(sprite, uvtx);
                }
            }
            break;
        case 10:
            if (va_arg(args, s32) == 0) {
                sprite->sprite.attr &= ~SP_FASTCOPY;
            } else {
                sprite->sprite.attr |= SP_FASTCOPY;
            }
            break;
        case 11:
            if (va_arg(args, s32) == 0) {
                sprite->sprite.attr &= ~SP_TRANSPARENT;
            } else {
                sprite->sprite.attr |= SP_TRANSPARENT;
            }
            break;
        default:
            _uvDebugPrintf("uvSprtProps: unknown token %d in args\n", token);
            break;
        }
    }
}

void uvSprtUpdateUnk(ParsedUVTX* uvtx) {
    if (uvtx->unk18 != NULL) {
        gSprtUnkTable[gSprtUnkIndex] = uvtx->unk18;
        gSprtUnkIndex += 1;
    }
    if (uvtx->unk1C != NULL) {
        gSprtUnkTable[gSprtUnkIndex] = uvtx->unk1C;
        gSprtUnkIndex += 1;
    }
}

void uvSprtResetUnk(void) {
    gSprtUnkIndex = 0;
}

