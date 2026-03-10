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

void uvSprtFromBitmap(uvSprite_t* sp, ParsedUVTX* uvtx) {
    if (sp->textureId == 0xFFFF) {
        _uvDebugPrintf("Warning: Bitmap sprite switched to texture sprite w/o uvMemReset\n");
        sp->bitmap = NULL;
    }
    if (sp->bitmap == 0) {
        sp->bitmap = _uvMemAlloc(sizeof(Bitmap), 4);
    }
    if (sp->unk58[0] == NULL) {
        sp->unk58[0] = _uvMemAlloc((1 + 2) * 0xC * sizeof(Gfx), 8);
        sp->unk58[1] = _uvMemAlloc((1 + 2) * 0xC * sizeof(Gfx), 8);
    }
    sp->bitmap->width = uvtx->width - 1;
    sp->bitmap->width_img = uvtx->width;
    sp->bitmap->s = 0;
    sp->bitmap->t = 0;
    sp->bitmap->buf = uvtx->unk0;
    sp->bitmap->actualHeight = uvtx->height;
    sp->bitmap->LUToffset = 0;
}

void uvSprt_80230750(uvSprite_t* sp, ParsedUVTX* uvtx) {
    Sprite* sprite = &sp->sprite;

    if (uvtx != NULL) {
        sprite->width = uvtx->width - 1;
        sprite->height = uvtx->height - 1;
        sprite->bmheight = uvtx->height - 1;
        sprite->bmHreal = uvtx->height;
        sprite->bmfmt = 0;
        sprite->bmsiz = 2;
        sprite->attr = SP_TEXSHUF;
        if (uvtx->unk22 != 1) {
            sprite->attr |= SP_TRANSPARENT;
        }
        if (uvtx->unk22 == 1) {
            sprite->bmfmt = G_IM_FMT_I;
        } else if (uvtx->unk22 == 2) {
            sprite->bmfmt = G_IM_FMT_IA;
        } else {
            sprite->bmfmt = G_IM_FMT_RGBA;
        }

        if (uvtx->unkE == 4) {
            sprite->bmsiz = G_IM_SIZ_4b;
        } else if (uvtx->unkE == 8) {
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
    sprite->bitmap = sp->bitmap;
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

void uvSprtDisplayList(uvSprite_t* sp) {
    Gfx* dlist;
    f32 temp_fv0;
    f32 temp_fv1;
    Sprite* sprite = &sp->sprite;

    sprite->rsp_dl = sp->unk58[gGfxFbIndex];
    sprite->rsp_dl_next = sprite->rsp_dl;

    if (sp->textureId != 0xFFFF) {
        temp_fv0 = (f32)sp->width / gGfxUnkPtrs->textures[sp->textureId]->width;
        temp_fv1 = (f32)sp->height / gGfxUnkPtrs->textures[sp->textureId]->height;
        spScale(sprite, temp_fv0, temp_fv1);
    } else {
        spScale(sprite, 1.0f, 1.0f);
    }
    sprite->red = sp->red;
    sprite->green = sp->green;
    sprite->blue = sp->blue;
    sprite->alpha = sp->alpha;
    spMove(sprite, sp->unk6, (s16)(SCREEN_HEIGHT - sp->unk8));
    dlist = spDraw(sprite);
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

void uvSprtSetBlit(uvSprite_t* sp, s32 blit_id) {
    ParsedUVBT* uvbt = gGfxUnkPtrs->blits[blit_id];
    Sprite* sprite = &sp->sprite;

    if ((sp->textureId == 0xFFFF) || (sp->textureId != 0xFFF)) {
        if (sp->width != uvbt->width || sp->height != uvbt->height) {
            _uvDebugPrintf("uvSprtSetBlit: Warning: sprite %d size change, dl space leaked\n", gSprtTable1 - sp);
            sp->unk58[0] = NULL;
            sp->unk58[1] = NULL;
        }
    }
    sp->sprite.bitmap = uvbt->bitmap;
    sp->textureId = 0xFFFF;
    sp->width = uvbt->width;
    sp->height = uvbt->height;
    sp->sprite.width = uvbt->width;
    sp->sprite.height = uvbt->height;
    sp->sprite.bitmap = uvbt->bitmap;
    sp->sprite.nbitmaps = uvbt->nbitmaps;
    sp->sprite.ndisplist = (uvbt->nbitmaps + 2) * 0xC;
    sp->sprite.bmheight = uvbt->texelHeight;
    sp->sprite.bmHreal = uvbt->texelHeight;
    sp->sprite.bmfmt = uvbt->bmfmt;

    switch (uvbt->bitdepth) {
    case 4:
        sp->sprite.bmsiz = G_IM_SIZ_4b;
        break;
    case 8:
        sp->sprite.bmsiz = G_IM_SIZ_8b;
        break;
    case 16:
        sp->sprite.bmsiz = G_IM_SIZ_16b;
        break;
    case 32:
        sp->sprite.bmsiz = G_IM_SIZ_32b;
        break;
    }
    sp->sprite.istart = 0;
    sp->sprite.istep = 1;
    if (sp->unk58[0] == NULL) {
        sp->unk58[0] = (Gfx*)_uvMemAlloc(((uvbt->nbitmaps + 2) * 0xC * sizeof(Gfx)), 8);
    }
    if (sp->unk58[1] == NULL) {
        sp->unk58[1] = (Gfx*)_uvMemAlloc(((uvbt->nbitmaps + 2) * 0xC * sizeof(Gfx)), 8);
    }

    switch (uvbt->bmfmt) {
    case G_IM_FMT_RGBA:
        if (uvbt->bitdepth == 16) {
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
        _uvDebugPrintf("Sprite Format %d is not supported.\n", uvbt->bmfmt);
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
    ParsedUVTX* uvtx;
    uvSprite_t* sp;
    va_list args;
    s32 token;

    if (sprite_id >= ARRAY_COUNT(gSprtTable1)) {
        _uvDebugPrintf("uvSprtProps: invalid sprite id %d\n", sprite_id);
        return;
    }

    sp = &gSprtTable1[sprite_id];
    va_start(args, sprite_id);

    while (TRUE) {
        token = va_arg(args, s32);
        switch (token) {
        case 0:
            return;
        case 1:
            sp->width = va_arg(args, s32);

            if (sp->width <= 0) {
                sp->width = 1;
            }

            sp->height = va_arg(args, s32);
            if (sp->height <= 0) {
                sp->height = 1;
            }
            break;
        case 2:
            sp->unk6 = va_arg(args, s32);
            sp->unk8 = va_arg(args, s32);
            break;
        case 7:
            sp->red = va_arg(args, s32);
            sp->green = va_arg(args, s32);
            sp->blue = va_arg(args, s32);
            sp->alpha = va_arg(args, s32);
            break;
        case 3:
            sp->unk0 = va_arg(args, s32);
            break;
        case 9:
            uvSprtSetBlit(sp, va_arg(args, s32));
            break;
        case 8:
            _uvDebugPrintf("uvSprtProps: bitmaps are replaced by blits.\n");
            break;
        case 5:
            sp->textureId = va_arg(args, s32);
            if (sp->textureId != 0xFFF) {
                uvtx = gGfxUnkPtrs->textures[sp->textureId];
                if (uvtx == NULL) {
                    _uvDebugPrintf(" uvSprtProps: texture id %d not in level\n", sp->textureId);
                    sp->textureId = 0xFFF;
                } else {
                    uvSprtFromBitmap(sp, uvtx);
                    uvSprt_80230750(sp, uvtx);
                }
            }
            break;
        case 10:
            if (va_arg(args, s32) == 0) {
                sp->sprite.attr &= ~SP_FASTCOPY;
            } else {
                sp->sprite.attr |= SP_FASTCOPY;
            }
            break;
        case 11:
            if (va_arg(args, s32) == 0) {
                sp->sprite.attr &= ~SP_TRANSPARENT;
            } else {
                sp->sprite.attr |= SP_TRANSPARENT;
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

