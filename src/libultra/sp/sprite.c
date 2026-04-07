/*
 * Copyright 1995, Silicon Graphics, Inc.
 * ALL RIGHTS RESERVED
 * UNPUBLISHED -- Rights reserved under the copyright laws of the United
 * States.   Use of a copyright notice is precautionary only and does not
 * imply publication or disclosure.
 * U.S. GOVERNMENT RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to restrictions
 * as set forth in FAR 52.227.19(c)(2) or subparagraph (c)(1)(ii) of the Rights
 * in Technical Data and Computer Software clause at DFARS 252.227-7013 and/or
 * in similar or successor clauses in the FAR, or the DOD or NASA FAR
 * Supplement.  Contractor/manufacturer is Silicon Graphics, Inc.,
 * 2011 N. Shoreline Blvd. Mountain View, CA 94039-7311.
 *
 * THE CONTENT OF THIS WORK CONTAINS CONFIDENTIAL AND PROPRIETARY
 * INFORMATION OF SILICON GRAPHICS, INC. ANY DUPLICATION, MODIFICATION,
 * DISTRIBUTION, OR DISCLOSURE IN ANY FORM, IN WHOLE, OR IN PART, IS STRICTLY
 * PROHIBITED WITHOUT THE PRIOR EXPRESS WRITTEN PERMISSION OF SILICON
 * GRAPHICS, INC.
 */
#include <assert.h>
#include <sp.h>
#include <PR/os_version.h>
// TODO: this comes from a header
#ident "$Revision: 1.17 $"


static int *prev_bmbuf = NULL;

static u16 sp_attr = 0;

static s32 scissor_xmax;
static s32 scissor_ymax;

static s32 scissor_xmin;
static s32 scissor_ymin;


void
spFinish( Gfx **glistp )
{
    Gfx *gl;

    gl = *glistp;

    /* Turn off texturing */
    gSPTexture ( gl++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_OFF);
    gDPSetCombineMode ( gl++, G_CC_SHADE, G_CC_SHADE);

    if (sp_attr & SP_TRANSPARENT) {
	/* Turn off transparency */
	gDPSetRenderMode( gl++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    }

    if (sp_attr & SP_CUTOUT) {
	/* Turn off Alpha write enable */
	gDPSetAlphaCompare ( gl++, G_AC_NONE) ;
    }

    gSPEndDisplayList ( gl++ );

    *glistp = gl;
}

#pragma GLOBAL_ASM("asm/nonmatchings/libultra/sp/sprite/drawbitmap.s")

#pragma GLOBAL_ASM("asm/nonmatchings/libultra/sp/sprite/spDraw.s")

void
spInit( Gfx **glistp )
{
    Gfx		*gl;

    gl = *glistp;

#ifdef DEBUG
    emPrintf("spInit ()\n" );
#endif
    sp_attr = 0;

    scissor_xmin = 0;
    scissor_ymin = 0;

    scissor_xmax = 320;
    scissor_ymax = 240;

    /* Turn on texturing */
    gDPPipeSync         ( gl++ );
    gDPSetCycleType     ( gl++, G_CYC_1CYCLE);
    gSPTexture          ( gl++, 0x8000, 0x8000, 0,  G_TX_RENDERTILE, G_ON);
    gDPSetAlphaCompare  ( gl++, G_AC_NONE   );
    gDPSetTexturePersp  ( gl++, G_TP_NONE   );
    gDPSetTextureFilter ( gl++, G_TF_BILERP );
    gDPSetTextureConvert( gl++, G_TC_FILT   );
    gDPSetTextureDetail ( gl++, G_TD_CLAMP  );
    gDPSetTextureLOD    ( gl++, G_TL_TILE   );
    gDPSetTextureLUT    ( gl++, G_TT_NONE   );

#define SPRITE_SURF	G_RM_TEX_EDGE
#define SPRITE_SURF2	G_RM_TEX_EDGE2

    gDPSetRenderMode( gl++, SPRITE_SURF, SPRITE_SURF2);

    *glistp = gl;
}

/*
 * spScissor()
 *
 *   Sets the scissoring box to be used for subsequent Sprite Drawing
 */
void 
spScissor (s32 xmin, s32 xmax, s32 ymin, s32 ymax )
{
    scissor_xmin = xmin;
    scissor_ymin = ymin;

    scissor_xmax = xmax;
    scissor_ymax = ymax;
}

/*
 * spMove()
 *
 *   Moves a sprite on the screen.
 */
void 
spMove (Sprite *sp, s32 x, s32 y)
{

#ifdef DEBUG
    emPrintf("spMove (Sprite 0x%08x, (%d,%d))\n", sp, x, y );
#endif

    sp->x = (s16)x;
    sp->y = (s16)y;
}

