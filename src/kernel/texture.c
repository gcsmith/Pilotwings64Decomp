#include "common.h"
#include <uv_clocks.h>
#include <uv_filesystem.h>
#include <uv_graphics.h>
#include <uv_janim.h>
#include <uv_memory.h>
#include <uv_sched.h>
#include <uv_sprite.h>
#include <uv_texture.h>

typedef struct {
    u16 unk0;
    u8 unk4;
    u8 pad6;
} Unk80219270_4;

typedef struct {
    s32 unk0[4];
    s32 unk10[4];
    s32 unk20[4];
    void* unk30;
    u8 count;
    s8 unk35;
    s8 unk36;
    s8 unk37;
    s32 unk38;
} ParsedUVEN;

typedef struct {
    s16 unk0;
    u8 unk2;
    u8 pad;
    s32 unk4;
} Unk802255A0_8;

typedef struct {
    u8 count;
    u8 pad[3];
    Unk802255A0_8* unk4;
    u8 unk8;
    u8 unk9;
    u8 unkA;
    u8 unkB;
    s32 unkC;
} ParsedUVSQ;

typedef struct {
    u16 count;
    u16 unk2;
    u16* unk4;
    u16* unk8;
} ParsedUVTP;

typedef struct {
    s32 unk0[16];
    s32 unk40;
    u8 unk44;
    u8 unk45;
    u8 unk46;
    u8 unk47;
} Unk802270BC_48;

typedef struct {
    s32 unk0[6];
    u8 unk18;
    u8 unk19;
    u16 unk1A;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    Unk802270BC_48* unk28;
} ParsedUVTR;

typedef struct {
    s32 tag;
    s32 size;
} UVBlockHeader;

typedef struct {
    u16 unk0;
    u16 pad2;
    void* unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    u16 unk14;
    u16 unk16;
} Unk80225FBC_0x18;

typedef struct {
    s32 unk0;
    u16 unk4;
    u16 unk6;
    Gfx* dlist;
    Gfx* unkC;
    u16 unk10;
    u16 unk12;
    u16 unk14;
    u16 pad16;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
} Unk80225FBC_0x28;

typedef struct {
    void* vtx;
    u16 unk4;
    u16 pad6;
    void* unk8;
    u16 unkC;
    u16 padE;
    void* unk10;
    u16 unk14;
    u16 pad16;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
} ParsedUVCT;

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s32 unk8; // pointer?
    s16 unkC;
    s16 unkE;
} Unk80227260_0x8;

typedef struct {
    u16 pad0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    void* unk10;
    Unk80227260_0x8* unk14;
} ParsedUVBT;

typedef struct unk_UVMD_24 {
    u8 unk0;
    u8 unk4[0x1B];
    u16 unk1C;
    s32 unk20;
} unk_UVMD_24; // size = 0x24

typedef struct unk_UVMD_C {
    s32 unk0;
    u16 unk4;
    u16 unk6;
    Gfx* unk8;
} unk_UVMD_C; // size = 0xC

typedef struct unk_UVMD_10 {
    unk_UVMD_C* unk0;
    u8 unk4;
    u8 unk5;
    u8 unk6;
    unk_UVMD_24* unk8;
    u8 unkC;
    u8 unkD;
} unk_UVMD_10; // size = 0x10

typedef struct unk_UVMD_8 {
    unk_UVMD_10* unk0;
    u8 unk4;
    u8 unk5;
} unk_UVMD_8; // size = 0x8

typedef struct unk_UVMD_6 {
    u16 unk0;
    u16 unk2;
    u16 unk4;
} unk_UVMD_6; // size = 0x6

typedef struct ParsedUVMD {
    Vtx* unk0;
    u16 unk4;
    unk_UVMD_8* unk8;
    s32* unkC;
    u8 unk10;
    u8 unk11;
    Mtx* unk14; // this is a guess
    u8 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
} ParsedUVMD; // size = 0x28

// forward declarations
void* uvParseTopUVFT(s32);
ParsedUVCT* uvParseTopUVCT(s32);
ParsedUVEN* uvParseTopUVEN(s32);
ParsedUVLV* uvParseTopUVLV(s32);
ParsedUVTP* uvParseTopUVTP(s32);
void* uvParseTopUVLT(s32);
void* uvParseTopUVMD(s32);
ParsedUVTR* uvParseTopUVTR(s32);
ParsedUVTX* uvParseTopUVTX(s32);
void* uvParseTopUVTI(s32);
void* uvParseTopUVBT(s32);
ParsedUVSQ* uvParseTopUVSQ(s32);

ParsedUVTX* _uvExpandTexture(u8*);
ParsedUVLV* _uvExpandTextureCpy(u8*);
void* _uvExpandTextureImg(u8*);
void* _uvParseUVLT(u8*);
ParsedUVEN* _uvParseUVEN(u8*);
ParsedUVSQ* _uvParseUVSQ(u8*);
ParsedUVMD* _uvParseUVMD(u8*);
ParsedUVTP* _uvParseUVTP(u8*);
ParsedUVTR* _uvParseUVTR(u8*);
ParsedUVBT* _uvParseUVBT(u8*);

// ROM offsets for file system data
extern u8 D_DE720[];
extern u8 D_DF5B0[];

extern u32 D_802B892C;

extern u32 D_802B8934;

extern u16 D_802B7600[1000];
extern u16* D_802B7DD0;
extern ParsedUVLV* D_802B7DD4;

void uvMemInitBlockHdr(void) {
    s32 sp64;
    s32 temp_v0;
    u32 sp5C;
    void* src;
    u32 var_a1;
    u8* romOffset;
    u32 tag;
    UVBlockHeader* var_a0;

    uvMemSet(&gUVBlockCounts, 0, sizeof(gUVBlockCounts));
    sp64 = uvFileReadHeader(D_DE720);
    romOffset = D_DF5B0;

    while ((tag = uvFileReadBlock(sp64, &sp5C, &src, 1)) != 0) {
        if (tag == 'TABL') {
            for (var_a1 = 0, var_a0 = (UVBlockHeader*)src; var_a1 < sp5C; var_a1 += 8, var_a0++) {
                switch (var_a0->tag) {
                case 0:
                    break;
                case 'UVSY':
                    gUVBlockOffsets.UVSY[0] = romOffset;
                    break;
                case 'UVAN':
                    gUVBlockOffsets.UVAN[gUVBlockCounts.UVAN++] = romOffset;
                    break;
                case 'UVFT':
                    gUVBlockOffsets.UVFT[gUVBlockCounts.UVFT++] = romOffset;
                    break;
                case 'UVBT':
                    gUVBlockOffsets.UVBT[gUVBlockCounts.UVBT++] = romOffset;
                    break;
                case 'UVMD':
                    gUVBlockOffsets.UVMD[gUVBlockCounts.UVMD++] = romOffset;
                    break;
                case 'UVCT':
                    gUVBlockOffsets.UVCT[gUVBlockCounts.UVCT++] = romOffset;
                    break;
                case 'UVTX':
                    gUVBlockOffsets.UVTX[gUVBlockCounts.UVTX++] = romOffset;
                    break;
                case 'UVEN':
                    gUVBlockOffsets.UVEN[gUVBlockCounts.UVEN++] = romOffset;
                    break;
                case 'UVLT':
                    gUVBlockOffsets.UVLT[gUVBlockCounts.UVLT++] = romOffset;
                    break;
                case 'UVLV':
                    gUVBlockOffsets.UVLV[gUVBlockCounts.UVLV++] = romOffset;
                    break;
                case 'UVSQ':
                    gUVBlockOffsets.UVSQ[gUVBlockCounts.UVSQ++] = romOffset;
                    break;
                case 'UVTR':
                    gUVBlockOffsets.UVTR[gUVBlockCounts.UVTR++] = romOffset;
                    break;
                case 'UVTP':
                    gUVBlockOffsets.UVTP[gUVBlockCounts.UVTP++] = romOffset;
                    break;
                case 'UVSX':
                    gUVBlockOffsets.UVSX[gUVBlockCounts.UVSX++] = romOffset;
                    break;
                default:
                    gUVBlockOffsets.unk1838[gUVBlockCounts.unk1C++] = romOffset;
                    break;
                }
                romOffset += var_a0->size;
            }
        }
    }
    uvFile_80223F30(sp64);
    uvLevelInit();
}

void* uvMemLoadDS(u32 tag, s32 palette) {
    void* ret;

    ret = NULL;
    _uvJumpHeap(&D_802B892C);
    do {
        switch (tag) {
        case 'UVSQ':
            ret = uvParseTopUVSQ(palette);
            break;
        case 'UVEN':
            ret = uvParseTopUVEN(palette);
            break;
        case 'UVTR':
            ret = uvParseTopUVTR(palette);
            break;
        case 'UVCT':
            ret = uvParseTopUVCT(palette);
            break;
        case 'UVLV':
            ret = uvParseTopUVLV(palette);
            break;
        case 'UVMD':
            ret = uvParseTopUVMD(palette);
            break;
        case 'UVTX':
            ret = uvParseTopUVTX(palette);
            break;
        case 'UVTI':
            ret = uvParseTopUVTI(palette);
            break;
        case 'UVLT':
            ret = uvParseTopUVLT(palette);
            break;
        case 'UVAN':
            ret = uvJanimLoad(palette);
            break;
        case 'UVFT':
            ret = uvParseTopUVFT(palette);
            break;
        case 'UVBT':
            ret = uvParseTopUVBT(palette);
            break;
        case 'UVTP':
            ret = uvParseTopUVTP(palette);
            break;
        default:
            break;
        }
    } while (_uvJumpHeap(&D_802B892C) == 0);
    return ret;
}

void uvMemLoadPal(s32 palette) {
    if (palette == 0xFFFF) {
        D_802B53C0 = NULL;
    } else {
        D_802B53C0 = uvMemLoadDS('UVTP', palette);
        if (D_802B53C0 == NULL) {
            _uvDebugPrintf("uvMemLoadPal: palette %d not in dbase\n", palette);
        }
    }
}

void uvLevelAppend(s32 levelId) {
    s32 i;
    s32 j;
    s32 id;
    s32 var_s3;
    s32 spA4;
    ParsedUVLV* level;
    ParsedUVLV sp50;

    uvGfxWaitForMesg();
    uvClkReset(5);
    func_8022BEB8(0);
    D_802B7DD0 = D_802B7600;
    D_802B7DD4 = &sp50;
    level = gLevelData.level = uvMemLoadDS('UVLV', levelId);
    if (level == NULL) {
        _uvDebugPrintf("uvLevelAppend: level %d not in dbase\n", levelId);
        return;
    }

    if (level->lightCount > LEVEL_LIGHT_COUNT) {
        _uvDebugPrintf("uvMemLoadDS: too many lights %d\n", level->lightCount);
    }

    if (level->environmentCount > LEVEL_ENVIRONMENT_COUNT) {
        _uvDebugPrintf("uvMemLoadDS: too many environments %d\n", level->environmentCount);
    }

    if (level->modelCount > LEVEL_MODEL_COUNT) {
        _uvDebugPrintf("uvMemLoadDS: too many models %d\n", level->modelCount);
    }

    if (level->contourCount > LEVEL_CONTOUR_COUNT) {
        _uvDebugPrintf("uvMemLoadDS: too many contours %d\n", level->contourCount);
    }

    if (level->textureCount > LEVEL_TEXTURE_COUNT) {
        _uvDebugPrintf("uvMemLoadDS: too many textures %d\n", level->textureCount);
    }

    if (level->terraCount > LEVEL_TERRA_COUNT) {
        _uvDebugPrintf("uvMemLoadDS: too many terras %d\n", level->terraCount);
    }

    if (level->animationCount > LEVEL_ANIMATION_COUNT) {
        _uvDebugPrintf("uvMemLoadDS: too many animations\n", level->animationCount);
    }

    if (level->blitCount > LEVEL_BLIT_COUNT) {
        _uvDebugPrintf("uvMemLoadDS: too many blits\n", level->blitCount);
    }

    spA4 = D_802B892C;

    for (i = 0; i < level->textureCount; i++) {
        id = level->textureIds[i];
        var_s3 = id;
        if (D_802B53C0 != NULL) {
            for (j = 0; j < D_802B53C0->unk0; j++) {
                if (id == D_802B53C0->unk4[j]) {
                    var_s3 = D_802B53C0->unk8[j];
                    break;
                }
            }
        }

        if (D_802B6E30[id] == NULL) {
            if (D_802B6E30[var_s3] != NULL) {
                D_802B6E30[id] = D_802B6E30[var_s3];
            } else {
                D_802B6E30[id] = uvMemLoadDS('UVTI', var_s3);
            }
        }
    }
    _uvMemGetBlocks(spA4, D_802B892C);

    for (i = 0; i < level->lightCount; i++) {
        id = level->lightIds[i];
        if (gLevelData.lights[id] == NULL) {
            gLevelData.lights[id] = uvMemLoadDS('UVLT', id);
        }
    }

    gLevelData.lightCount = level->lightCount;

    for (i = 0; i < level->environmentCount; i++) {
        id = level->environmentIds[i];
        if (gLevelData.environments[id] == NULL) {
            gLevelData.environments[id] = uvMemLoadDS('UVEN', id);
        }
    }
    gLevelData.environmentCount = level->environmentCount;

    for (i = 0; i < level->modelCount; i++) {
        id = level->modelIds[i];
        if (gLevelData.models[id] == NULL) {
            gLevelData.models[id] = uvMemLoadDS('UVMD', id);
        }
    }
    gLevelData.modelCount = level->modelCount;

    for (i = 0; i < level->contourCount; i++) {
        id = level->contourIds[i];
        if (gLevelData.contours[id] == NULL) {
            gLevelData.contours[id] = uvMemLoadDS('UVCT', id);
        }
    }
    gLevelData.contourCount = level->contourCount;

    for (i = 0; i < level->textureCount; i++) {
        id = level->textureIds[i];
        var_s3 = id;
        if (D_802B53C0 != NULL) {
            for (j = 0; j < D_802B53C0->unk0; j++) {
                if (id == D_802B53C0->unk4[j]) {
                    var_s3 = D_802B53C0->unk8[j];
                    break;
                }
            }
        }

        if (gLevelData.textures[id] == NULL) {
            gLevelData.textures[id] = uvMemLoadDS('UVTX', var_s3);
            uvSprtUpdateUnk(gLevelData.textures[id]);
        }
    }
    gLevelData.textureCount = level->textureCount;

    for (i = 0; i < level->terraCount; i++) {
        id = level->terraIds[i];
        if (gLevelData.terras[id] == NULL) {
            gLevelData.terras[id] = uvMemLoadDS('UVTR', id);
        }
    }
    gLevelData.terraCount = level->terraCount;

    for (i = 0; i < level->sequenceCount; i++) {
        id = level->sequenceIds[i];
        if (gLevelData.sequences[id] == NULL) {
            gLevelData.sequences[id] = uvMemLoadDS('UVSQ', id);
        }
    }
    gLevelData.sequenceCount = level->sequenceCount;

    for (i = 0; i < level->animationCount; i++) {
        id = level->animationIds[i];
        if (gLevelData.animations[id] == NULL) {
            gLevelData.animations[id] = uvMemLoadDS('UVAN', id);
        }
    }

    for (i = 0; i < level->fontCount; i++) {
        id = level->fontIds[i];
        if (gLevelData.fonts[id] == NULL) {
            gLevelData.fonts[id] = uvMemLoadDS('UVFT', id);
        }
    }

    for (i = 0; i < level->blitCount; i++) {
        id = level->blitIds[i];
        if (gLevelData.blits[id] == NULL) {
            gLevelData.blits[id] = uvMemLoadDS('UVBT', id);
        }
    }

    if (D_802B8934 != 0) {
        _uvDebugPrintf("uvMemLoadDS: into txt img data by %d bytes\n", D_802B8934);
    }
    func_8022BEB8(1);
}

void uvConsumeBytes(void* dst, u8** ptr, s32 size) {
    switch (size) {
    case 1:
        *(s8*)dst = uvMemRead(*ptr, size);
        *ptr += 1;
        break;
    case 2:
        *(s16*)dst = uvMemRead(*ptr, size);
        *ptr += 2;
        break;
    case 4:
        *(s32*)dst = uvMemRead(*ptr, size);
        *ptr += 4;
        break;
    default:
        _uvMediaCopy(dst, *ptr, size);
        *ptr += size;
        break;
    }
}

void* _uvParseUVLT(u8* arg0) {
    void* ret;
    ret = (void*)_uvMemAlloc(4, 4);
    uvConsumeBytes(ret, &arg0, 4);
    return ret;
}

ParsedUVEN* _uvParseUVEN(u8* src) {
    Unk80219270_4* temp_s3;
    u8 count;
    s32 i;
    ParsedUVEN* ret;

    uvConsumeBytes(&count, &src, 1);
    temp_s3 = (Unk80219270_4*)_uvMemAlloc(count * sizeof(Unk80219270_4), 4);

    for (i = 0; i < (s32)count; i++) {
        uvConsumeBytes(&temp_s3[i].unk0, &src, sizeof(temp_s3[i].unk0));
        uvConsumeBytes(&temp_s3[i].unk4, &src, sizeof(temp_s3[i].unk4));
    }

    ret = (ParsedUVEN*)_uvMemAlloc(sizeof(ParsedUVEN), 4);
    uvConsumeBytes(ret, &src, sizeof(ParsedUVEN));
    ret->count = count;
    ret->unk38 = 0;
    ret->unk30 = (ret->count) ? temp_s3 : NULL;
    return ret;
}

ParsedUVSQ* _uvParseUVSQ(u8* src) {
    u16 i;
    u8 count;
    Unk802255A0_8* temp_s3;
    ParsedUVSQ* ret;

    uvConsumeBytes(&count, &src, 1);
    temp_s3 = (Unk802255A0_8*)_uvMemAlloc(count * sizeof(Unk802255A0_8), 4);

    for (i = 0; i < (s32)count; i++) {
        uvConsumeBytes(&temp_s3[i].unk0, &src, sizeof(temp_s3[i].unk0));
        uvConsumeBytes(&temp_s3[i].unk4, &src, sizeof(temp_s3[i].unk4));
        temp_s3[i].unk2 = 0xFF;
    }

    ret = (ParsedUVSQ*)_uvMemAlloc(sizeof(ParsedUVSQ), 4);
    uvConsumeBytes(&ret->unk8, &src, sizeof(ret->unk8));
    uvConsumeBytes(&ret->unk9, &src, sizeof(ret->unk9));
    uvConsumeBytes(&ret->unkC, &src, sizeof(ret->unkC));
    ret->unk4 = temp_s3;
    ret->count = count;
    return ret;
}

ParsedUVMD* _uvParseUVMD(u8* src) {
    Vtx* vtx;
    ParsedUVMD* ret;
    unk_UVMD_8* spB4;
    Gfx* dlist;
    unk_UVMD_24* var_s6;
    unk_UVMD_10* spA8;
    s32* spA4;
    Vtx* tempVtx;
    s32 var_s0;
    unk_UVMD_24* var_s0_4;
    Mtx* mtx;
    unk_UVMD_C* sp58;
    unk_UVMD_6* sp8C;
    s32 i;
    s32 j;
    s32 k;
    unk_UVMD_6* temp_v0_12;
    u8 sp7B;
    u8 sp7A;
    u8 sp79;
    u8 sp78;
    u8 sp77;
    u8 sp76;
    u16 vtxCount;
    u16 gfxCount;
    u16 sp70;
    u16 sp6E;

    uvConsumeBytes(&vtxCount, &src, sizeof(u16));
    uvConsumeBytes(&sp79, &src, sizeof(u8));
    uvConsumeBytes(&sp7B, &src, sizeof(u8));
    uvConsumeBytes(&sp7A, &src, sizeof(u8));
    uvConsumeBytes(&sp77, &src, sizeof(u8));
    uvConsumeBytes(&sp6E, &src, sizeof(u16));
    vtx = (Vtx*)_uvMemAlloc(vtxCount * sizeof(Vtx), 8);
    _uvMediaCopy(vtx, src, vtxCount * sizeof(Vtx));
    src += vtxCount * sizeof(Vtx);
    spA4 = (s32*)_uvMemAlloc(sp79 * sizeof(s32), 4);
    spB4 = (unk_UVMD_8*)_uvMemAlloc(sp79 * sizeof(unk_UVMD_8), 4);

    for (i = 0; i < sp79; i++) {
        uvConsumeBytes(&spB4[i].unk4, &src, sizeof(u8));
        uvConsumeBytes(&spB4[i].unk5, &src, sizeof(u8));
        spA8 = (unk_UVMD_10*)_uvMemAlloc(spB4[i].unk4 * sizeof(unk_UVMD_10), 4);

        for (j = 0; j < spB4[i].unk4; j++) {
            sp76 = 0;
            uvConsumeBytes(&spA8[j].unk4, &src, sizeof(u8));
            uvConsumeBytes(&spA8[j].unk5, &src, sizeof(u8));
            uvConsumeBytes(&spA8[j].unk6, &src, sizeof(u8));
            spA8[j].unk0 = (unk_UVMD_C*)_uvMemAlloc(spA8[j].unk4 * sizeof(unk_UVMD_C), 8);
            sp58 = spA8[j].unk0;
            for (k = 0; k < spA8[j].unk4; k++) {
                uvConsumeBytes(&sp58[k].unk0, &src, sizeof(s32));
                uvConsumeBytes(&sp58[k].unk4, &src, sizeof(u16));
                uvConsumeBytes(&sp58[k].unk6, &src, sizeof(u16));
                uvConsumeBytes(&gfxCount, &src, sizeof(u16));
                if (sp58[k].unk0 & 0x08000000) {
                    sp76 = 1;
                }

                dlist = (Gfx*)_uvMemAlloc((gfxCount + 1) * sizeof(Gfx), 8);
                if (1) { }
                sp58[k].unk8 = OS_PHYSICAL_TO_K0(dlist);
                for (var_s0 = 0; var_s0 < gfxCount; var_s0++) {
                    uvConsumeBytes(&sp70, &src, sizeof(u16));
                    if (sp70 & 0x4000) {
                        gSP1Triangle(&dlist[var_s0], (sp70 & 0xF00) >> 8, (sp70 & 0xF0) >> 4, sp70 & 0xF, 0);
                    } else {
                        uvConsumeBytes(&sp78, &src, sizeof(u8));
                        tempVtx = &vtx[sp70 & 0x3FFF];
                        gSPVertex(&dlist[var_s0], OS_PHYSICAL_TO_K0(tempVtx), ((sp78 & 0xF0) >> 4) + 1, sp78 & 0xF);
                    }
                }
                gSPEndDisplayList(&dlist[var_s0]);
            }
            spA8[j].unkD = sp76;
        }
        spB4[i].unk0 = spA8;
        uvConsumeBytes(&spA4[i], &src, 4);
    }

    mtx = (Mtx*)_uvMemAlloc(sp7B * sizeof(Mtx), 4);
    uvConsumeBytes(mtx, &src, sp7B * sizeof(Mtx));
    if (sp7A) {
        var_s6 = (unk_UVMD_24*)_uvMemAlloc(sp7A * sizeof(unk_UVMD_24), 4);

        for (i = 0; i < sp7A; i++) {
            uvConsumeBytes(&var_s6[i], &src, sizeof(unk_UVMD_24));
        }
    } else {
        var_s6 = NULL;
    }
    ret = (ParsedUVMD*)_uvMemAlloc(sizeof(ParsedUVMD), 4);
    uvConsumeBytes(&ret->unk1C, &src, sizeof(s32));
    uvConsumeBytes(&ret->unk20, &src, sizeof(s32));
    uvConsumeBytes(&ret->unk24, &src, sizeof(s32));
    temp_v0_12 = (unk_UVMD_6*)_uvMemAlloc(sp6E * sizeof(unk_UVMD_6), 4);

    for (i = 0; i < sp6E; i++) {
        uvConsumeBytes(&temp_v0_12[i].unk0, &src, sizeof(u16));
        uvConsumeBytes(&temp_v0_12[i].unk2, &src, sizeof(u16));
        uvConsumeBytes(&temp_v0_12[i].unk4, &src, sizeof(u16));
    }

    k = 0;
    for (i = 0; i < sp7A; i++) {
        var_s0_4 = &var_s6[i];
        if (i == 0) {
            if (var_s0_4->unk1C != 0) {
                var_s0_4->unk20 = temp_v0_12;
            } else {
                var_s0_4->unk20 = NULL;
            }
            k = var_s0_4->unk1C;
            sp8C = &temp_v0_12[var_s0_4->unk1C];
        } else {
            var_s0_4->unk20 = sp8C;
            var_s0_4->unk1C -= k;
            k += var_s0_4->unk1C;
            sp8C += var_s0_4->unk1C;
        }
    }

    ret->unk0 = vtx;
    ret->unk4 = vtxCount;
    ret->unk8 = spB4;
    ret->unkC = spA4;
    ret->unk10 = sp79;
    ret->unk14 = mtx;
    ret->unk18 = sp7B;

    ret->unk11 = 0;
    if (sp7A != 0) {
        ret->unk11 |= 2;
    }
    if (sp77 != 0) {
        ret->unk11 |= 1;
    }
    for (i = 0; i < ret->unk8->unk4; i++) {
        for (j = 0; j < sp7A; j++) {
            if (i == var_s6[j].unk0) {
                break;
            }
        }
        k = j;
        if (j == sp7A) {
            ret->unk8->unk0[i].unk8 = 0;
            ret->unk8->unk0[i].unkC = 0;
        } else {
            for (k = j; k < sp7A; k++) {
                if ((i + 1) == var_s6[k].unk0) {
                    break;
                }
            }
            ret->unk8->unk0[i].unk8 = &var_s6[j];
            ret->unk8->unk0[i].unkC = k - j;
        }
    }
    return ret;
}

ParsedUVCT* _uvParseUVCT(u8* src) {
    Vtx* vtx;
    Vtx* tempVtx;
    Gfx* spA4;
    Unk80225FBC_0x28* spA0;
    Unk80225FBC_0x18* tempSp98;
    Unk80225FBC_0x18* sp98;
    Unk80225FBC_0x28* tempSpA0;
    Gfx* dlist;
    ParsedUVCT* ret;
    u16 sp8A;
    u16 sp88;
    u16 sp86;
    s32 i;
    s32 j;
    u8 sp7B;
    u8 sp7A;
    u16 vtxCount;
    u16 gfxCount;
    u16 elem;

    uvConsumeBytes(&vtxCount, &src, 2);
    uvConsumeBytes(&sp8A, &src, 2);
    uvConsumeBytes(&sp86, &src, 2);
    uvConsumeBytes(&sp88, &src, 2);

    vtx = (Vtx*)_uvMemAlloc(vtxCount * sizeof(Vtx), 8);
    _uvMediaCopy(vtx, src, vtxCount * sizeof(Vtx));
    src += vtxCount * sizeof(Vtx);

    spA4 = (void*)_uvMemAlloc(sp8A * sizeof(Gfx), 4);
    _uvMediaCopy((void*)spA4, src, sp8A * sizeof(Gfx));
    src += sp8A * sizeof(Gfx);

    sp98 = (Unk80225FBC_0x18*)_uvMemAlloc(sp86 * sizeof(Unk80225FBC_0x18), 4);
    for (i = 0; i < sp86; i++) {
        tempSp98 = &sp98[i];
        uvConsumeBytes(&sp7B, &src, 1);
        tempSp98->unk4 = (void*)_uvMemAlloc(sp7B * 64, 4);
        uvConsumeBytes(tempSp98->unk4, &src, sp7B * 64);

        uvConsumeBytes(&tempSp98->unk0, &src, sizeof(tempSp98->unk0));
        uvConsumeBytes(&tempSp98->unk8, &src, sizeof(tempSp98->unk8));
        uvConsumeBytes(&tempSp98->unkC, &src, sizeof(tempSp98->unkC));
        uvConsumeBytes(&tempSp98->unk10, &src, sizeof(tempSp98->unk10));
        uvConsumeBytes(&tempSp98->unk14, &src, sizeof(tempSp98->unk14));
        uvConsumeBytes(&tempSp98->unk16, &src, sizeof(tempSp98->unk16));
    }

    spA0 = (Unk80225FBC_0x28*)_uvMemAlloc(sp88 * sizeof(Unk80225FBC_0x28), 4);
    for (i = 0; i < sp88; i++) {
        tempSpA0 = &spA0[i];
        uvConsumeBytes(&tempSpA0->unk0, &src, sizeof(tempSpA0->unk0));
        uvConsumeBytes(&tempSpA0->unk4, &src, sizeof(tempSpA0->unk4));
        uvConsumeBytes(&tempSpA0->unk6, &src, sizeof(tempSpA0->unk6));
        uvConsumeBytes(&gfxCount, &src, sizeof(gfxCount));
        dlist = (Gfx*)_uvMemAlloc((gfxCount + 1) * sizeof(Gfx), 8); // +1 for G_ENDDL
        for (j = 0; j < gfxCount; j++) {
            uvConsumeBytes(&elem, &src, 2);
            if (elem & 0x4000) {
                gSP1Triangle(&dlist[j], (elem & 0xF00) >> 8, (elem & 0xF0) >> 4, elem & 0xF, 0);
            } else {
                uvConsumeBytes(&sp7A, &src, sizeof(sp7A));
                tempVtx = &vtx[elem & 0x3FFF];
                gSPVertex(&dlist[j], (u32)OS_PHYSICAL_TO_K0(tempVtx), ((sp7A & 0xF0) >> 4) + 1, sp7A & 0xF);
            }
        }

        gSPEndDisplayList(&dlist[j]); // G_ENDDL = 0xB8
        tempSpA0->dlist = dlist;

        uvConsumeBytes(&elem, &src, 2);
        tempSpA0->unkC = &spA4[elem];

        uvConsumeBytes(&elem, &src, 2);
        tempSpA0->unk10 = elem;

        uvConsumeBytes(&tempSpA0->unk12, &src, sizeof(tempSpA0->unk12));
        uvConsumeBytes(&tempSpA0->unk14, &src, sizeof(tempSpA0->unk14));
        uvConsumeBytes(&tempSpA0->unk18, &src, sizeof(tempSpA0->unk18));
        uvConsumeBytes(&tempSpA0->unk1C, &src, sizeof(tempSpA0->unk1C));
        uvConsumeBytes(&tempSpA0->unk20, &src, sizeof(tempSpA0->unk20));
        uvConsumeBytes(&tempSpA0->unk24, &src, sizeof(tempSpA0->unk24));
    }

    ret = (ParsedUVCT*)_uvMemAlloc(sizeof(ParsedUVCT), 4);
    ret->vtx = vtx;
    ret->unk4 = vtxCount;
    ret->unk8 = spA0;
    ret->unkC = sp88;
    ret->unk10 = sp98;
    ret->unk14 = sp86;
    uvConsumeBytes(&ret->unk18, &src, sizeof(ret->unk18));
    uvConsumeBytes(&ret->unk1C, &src, sizeof(ret->unk1C));
    uvConsumeBytes(&ret->unk20, &src, sizeof(ret->unk20));
    uvConsumeBytes(&ret->unk24, &src, sizeof(ret->unk24));
    uvConsumeBytes(&ret->unk28, &src, sizeof(ret->unk28));
    return ret;
}

ParsedUVTX* _uvExpandTexture(u8* src) {
    void* sp6C;
    unk_UVTX_8* sp68;
    ParsedUVTX* temp_v0;
    s32 i;
    s32 var_a0;
    s32 id;
    u8 temp_v0_2;
    u16 sp54;
    u16 size;
    unk_UVTX_1C* sp4C;
    unk_UVTX_1C* sp48;
    f32 sp44;
    f32 sp40;
    unk_UVTX_8* temp_v1;
    u16 temp_t2;
    u32 temp_t0;

    uvConsumeBytes(&size, &src, sizeof(u16));
    if (size > 0x1000) {
        _uvDebugPrintf("_uvExpandTexture: txt image too big %d bytes (4096 max)\n", size);
        size = 0x1000;
    }
    uvConsumeBytes(&sp54, &src, sizeof(u16));
    uvConsumeBytes(&sp44, &src, sizeof(f32));
    uvConsumeBytes(&sp40, &src, sizeof(f32));
    if ((sp44 != 0.0f) || (sp40 != 0.0f)) {
        sp4C = (unk_UVTX_1C*)_uvMemAlloc(sizeof(unk_UVTX_1C), 4);
        sp4C->unk0 = 1.0f;
        sp4C->unk4 = 1.0f;
        sp4C->unk8 = sp44;
        sp4C->unkC = sp40;
        sp4C->unk10 = 0.0f;
        sp4C->unk14 = 0.0f;
        sp4C->unk18 = 1;
    } else {
        sp4C = NULL;
    }
    uvConsumeBytes(&sp44, &src, 4);
    uvConsumeBytes(&sp40, &src, 4);
    if ((sp44 != 0.0f) || (sp40 != 0.0f)) {
        sp48 = (unk_UVTX_1C*)_uvMemAlloc(sizeof(unk_UVTX_1C), 4);
        sp48->unk0 = 1.0f;
        sp48->unk4 = 1.0f;
        sp48->unk8 = sp44;
        sp48->unkC = sp40;
        sp48->unk10 = 0.0f;
        sp48->unk14 = 0.0f;
        sp48->unk18 = 1;
    } else {
        sp48 = NULL;
    }
    src += size;
    sp68 = (unk_UVTX_8*)_uvMemAlloc(sp54 * sizeof(unk_UVTX_8), 8);

    uvConsumeBytes(sp68, &src, sp54 * sizeof(unk_UVTX_8));

    temp_v0 = (ParsedUVTX*)_uvMemAlloc(sizeof(ParsedUVTX), 4);
    uvConsumeBytes(&temp_v0->unkA, &src, sizeof(u16));
    uvConsumeBytes(&temp_v0->unkC, &src, sizeof(u16));
    uvConsumeBytes(&temp_v0->unkE, &src, sizeof(u8));
    uvConsumeBytes(&temp_v0->unkF, &src, sizeof(u8));
    uvConsumeBytes(&temp_v0->unk10, &src, sizeof(u8));
    uvConsumeBytes(&temp_v0->unk12, &src, sizeof(u16));
    uvConsumeBytes(&temp_v0->unk14, &src, sizeof(u16));
    uvConsumeBytes(&temp_v0->unk20, &src, sizeof(u16));
    uvConsumeBytes(&temp_v0->unk22, &src, sizeof(u8));
    uvConsumeBytes(&temp_v0->unk23, &src, sizeof(u8));
    uvConsumeBytes(&temp_v0->unk24, &src, sizeof(u8));
    uvConsumeBytes(&temp_v0->unk25, &src, sizeof(u8));
    uvConsumeBytes(&temp_v0->unk26, &src, sizeof(u8));
    uvConsumeBytes(&temp_v0->unk28, &src, sizeof(s32));
    temp_v0->size = size;
    temp_t2 = temp_v0->unk12;
    id = temp_v0->unk12 & 0xFFF;

    if (D_802B53C0 != NULL) {
        for (i = 0; i < D_802B53C0->unk0; i++) {
            if (id == D_802B53C0->unk8[i]) {
                id = D_802B53C0->unk4[i];
                break;
            }
        }
    }

    sp6C = D_802B6E30[id];
    if (sp6C == NULL) {
        _uvDebugPrintf("_uvExpandTexture: texture %d not in level. State: 0x%x\n", id, temp_t2);
    }
    temp_v0->unk4 = sp68;
    temp_v0->unk0 = sp6C;
    temp_v0->unk18 = sp4C;
    temp_v0->unk1C = sp48;
    var_a0 = 0;
    temp_v0_2 = 0;

    temp_t0 = (u32)sp6C;
    for (i = 0; i < sp54; i++) {
        temp_v1 = &sp68[i];

        temp_v0_2 = temp_v1->unk0;
        if (temp_v0_2 == 0xFD) {
            if (var_a0 == 0) {
                temp_v1->unk4 |= (u32)OS_PHYSICAL_TO_K0(temp_t0);
            } else {
                temp_v1->unk4 |= (u32)OS_PHYSICAL_TO_K0(D_802B6E30[temp_v0->unk14]);
            }
            var_a0++;
        }
    }

    return temp_v0;
}

void* _uvExpandTextureImg(u8* src) {
    void* retBuf;
    u16 sp32;
    u16 size;
    u32 sp2C;
    u32 sp28;

    uvConsumeBytes(&size, &src, 2);
    if (size > 0x1000) {
        _uvDebugPrintf("_uvExpandTextureImg: txt image too big %d bytes (4096 max)\n", size);
        size = 0x1000;
    }
    uvConsumeBytes(&sp32, &src, sizeof(sp32));
    uvConsumeBytes(&sp2C, &src, sizeof(sp2C));
    uvConsumeBytes(&sp28, &src, sizeof(sp28));
    uvConsumeBytes(&sp2C, &src, sizeof(sp2C));
    uvConsumeBytes(&sp28, &src, sizeof(sp28));
    retBuf = (void*)_uvMemAlloc(size, 8);
    _uvMediaCopy(retBuf, src, size);
    return retBuf;
}

ParsedUVLV* _uvExpandTextureCpy(u8* src) {
    ParsedUVLV* level;

    level = D_802B7DD4;

    uvConsumeBytes(&level->terraCount, &src, sizeof(u16));
    level->terraIds = D_802B7DD0;

    D_802B7DD0 += level->terraCount;
    if (D_802B7DD0 >= &D_802B7600[LEVEL_OBJECT_COUNT]) {
        _uvDebugPrintf("bump up NLV_E\n");
    }
    _uvMediaCopy(level->terraIds, src, level->terraCount * sizeof(u16));
    src += level->terraCount * sizeof(u16);

    uvConsumeBytes(&level->lightCount, &src, sizeof(u16));
    level->lightIds = D_802B7DD0;

    D_802B7DD0 += level->lightCount;
    if (D_802B7DD0 >= &D_802B7600[LEVEL_OBJECT_COUNT]) {
        _uvDebugPrintf("bump up NLV_E\n");
    }
    _uvMediaCopy(level->lightIds, src, level->lightCount * sizeof(u16));
    src += level->lightCount * sizeof(u16);

    uvConsumeBytes(&level->environmentCount, &src, sizeof(u16));
    level->environmentIds = D_802B7DD0;

    D_802B7DD0 += level->environmentCount;
    if (D_802B7DD0 >= &D_802B7600[LEVEL_OBJECT_COUNT]) {
        _uvDebugPrintf("bump up NLV_E\n");
    }
    _uvMediaCopy(level->environmentIds, src, level->environmentCount * sizeof(u16));
    src += level->environmentCount * sizeof(u16);

    uvConsumeBytes(&level->modelCount, &src, sizeof(u16));
    level->modelIds = D_802B7DD0;

    D_802B7DD0 += level->modelCount;
    if (D_802B7DD0 >= &D_802B7600[LEVEL_OBJECT_COUNT]) {
        _uvDebugPrintf("bump up NLV_E\n");
    }
    _uvMediaCopy(level->modelIds, src, level->modelCount * sizeof(u16));
    src += level->modelCount * sizeof(u16);

    uvConsumeBytes(&level->contourCount, &src, sizeof(u16));
    level->contourIds = D_802B7DD0;

    D_802B7DD0 += level->contourCount;
    if (D_802B7DD0 >= &D_802B7600[LEVEL_OBJECT_COUNT]) {
        _uvDebugPrintf("bump up NLV_E\n");
    }
    _uvMediaCopy(level->contourIds, src, level->contourCount * sizeof(u16));
    src += level->contourCount * sizeof(u16);

    uvConsumeBytes(&level->textureCount, &src, sizeof(u16));
    level->textureIds = D_802B7DD0;

    D_802B7DD0 += level->textureCount;
    if (D_802B7DD0 >= &D_802B7600[LEVEL_OBJECT_COUNT]) {
        _uvDebugPrintf("bump up NLV_E\n");
    }
    _uvMediaCopy(level->textureIds, src, level->textureCount * sizeof(u16));
    src += level->textureCount * sizeof(u16);

    uvConsumeBytes(&level->sequenceCount, &src, sizeof(u16));
    level->sequenceIds = D_802B7DD0;

    D_802B7DD0 += level->sequenceCount;
    if (D_802B7DD0 >= &D_802B7600[LEVEL_OBJECT_COUNT]) {
        _uvDebugPrintf("bump up NLV_E\n");
    }
    _uvMediaCopy(level->sequenceIds, src, level->sequenceCount * sizeof(u16));
    src += level->sequenceCount * sizeof(u16);

    uvConsumeBytes(&level->animationCount, &src, sizeof(u16));
    level->animationIds = D_802B7DD0;

    D_802B7DD0 += level->animationCount;
    if (D_802B7DD0 >= &D_802B7600[LEVEL_OBJECT_COUNT]) {
        _uvDebugPrintf("bump up NLV_E\n");
    }
    _uvMediaCopy(level->animationIds, src, level->animationCount * sizeof(u16));
    src += level->animationCount * sizeof(u16);

    uvConsumeBytes(&level->fontCount, &src, sizeof(u16));
    level->fontIds = D_802B7DD0;

    D_802B7DD0 += level->fontCount;
    if (D_802B7DD0 >= &D_802B7600[LEVEL_OBJECT_COUNT]) {
        _uvDebugPrintf("bump up NLV_E\n");
    }
    _uvMediaCopy(level->fontIds, src, level->fontCount * sizeof(u16));
    src += level->fontCount * sizeof(u16);

    uvConsumeBytes(&level->blitCount, &src, sizeof(u16));
    level->blitIds = D_802B7DD0;

    D_802B7DD0 += level->blitCount;
    if (D_802B7DD0 >= &D_802B7600[LEVEL_OBJECT_COUNT]) {
        _uvDebugPrintf("bump up NLV_E\n");
    }
    _uvMediaCopy(level->blitIds, src, level->blitCount * sizeof(u16));
    src += level->blitCount * sizeof(u16);

    return level;
}

ParsedUVTP* _uvParseUVTP(u8* src) {
    ParsedUVTP* temp_s2;
    u16 i;
    u16 count;

    uvConsumeBytes(&count, &src, 2);
    temp_s2 = (ParsedUVTP*)_uvMemAlloc(sizeof(ParsedUVTP), 4);
    temp_s2->unk4 = (u16*)_uvMemAlloc(count * 2, 4);
    temp_s2->unk8 = (u16*)_uvMemAlloc(count * 2, 4);

    for (i = 0; i < count; i++) {
        uvConsumeBytes(&temp_s2->unk4[i], &src, sizeof(temp_s2->unk4[i]));
        uvConsumeBytes(&temp_s2->unk8[i], &src, sizeof(temp_s2->unk8[i]));
    }
    temp_s2->count = count;
    return temp_s2;
}

ParsedUVTR* _uvParseUVTR(u8* src) {
    Unk802270BC_48* ptr;
    ParsedUVTR* temp_v0;
    s32 count;
    s32 i;
    u8 sp47;
    u16 sp44;

    temp_v0 = (ParsedUVTR*)_uvMemAlloc(sizeof(ParsedUVTR), 4);
    uvConsumeBytes(&temp_v0->unk0, &src, sizeof(temp_v0->unk0));
    uvConsumeBytes(&temp_v0->unk18, &src, sizeof(temp_v0->unk18));
    uvConsumeBytes(&temp_v0->unk19, &src, sizeof(temp_v0->unk19));
    uvConsumeBytes(&temp_v0->unk1C, &src, sizeof(temp_v0->unk1C));
    uvConsumeBytes(&temp_v0->unk20, &src, sizeof(temp_v0->unk20));
    uvConsumeBytes(&temp_v0->unk24, &src, sizeof(temp_v0->unk24));
    count = temp_v0->unk18 * temp_v0->unk19;
    temp_v0->unk28 = (Unk802270BC_48*)_uvMemAlloc(count * sizeof(Unk802270BC_48), 4);

    for (i = 0; i < count; i++) {
        ptr = &temp_v0->unk28[i];
        uvConsumeBytes(&sp47, &src, 1);
        if (sp47 == 0) {
            uvMemSet(ptr->unk0, 0, 0x48);
        } else {
            uvConsumeBytes(&ptr->unk0, &src, sizeof(ptr->unk0));
            uvConsumeBytes(&ptr->unk44, &src, sizeof(ptr->unk44));
            uvConsumeBytes(&sp44, &src, 2);
            ptr->unk40 = gLevelData.contours[sp44];
        }
    }
    return temp_v0;
}

ParsedUVBT* _uvParseUVBT(u8* src) {
    s32 var_a1; // pointer?
    u16 sp9A;
    u16 sp98;
    u16 sp96;
    u16 sp94;
    u16 sp92;
    u16 sp90;
    u16 sp8E;
    s8 remainder2;
    s8 remainder1;
    s32 j;
    u64 sp80;
    s32 i;
    ParsedUVBT* ret;
    s32 sp74;
    s32 sp70;
    Unk80227260_0x8* temp_v0_3;
    s32 temp;

    remainder2 = 0;
    remainder1 = 0;

    _uvMediaCopy(&sp80, src, 4);
    sp80 >>= 32;
    sp9A = (sp80 & 0xFFFF0000) >> 16;
    sp98 = sp80;
    src += 4;

    _uvMediaCopy(&sp80, src, 4);
    sp80 >>= 32;
    sp96 = (sp80 & 0xFFFF0000) >> 16;
    sp94 = sp80;
    src += 4;

    _uvMediaCopy(&sp80, src, 4);
    sp80 >>= 32;
    sp92 = (sp80 & 0xFFFF0000) >> 16;
    sp90 = sp80;
    src += 4;

    _uvMediaCopy(&sp80, src, 4);
    sp80 >>= 32;
    temp = (sp80 & 0xFFFF0000) >> 16;
    // fake, probably used to assign sp8C here as well
    sp8E = temp & 0xFFFF & 0xFFFF & 0xFFFF;
    src += 2;

    ret = (ParsedUVBT*)_uvMemAlloc(sizeof(ParsedUVBT), 4);
    ret->unk2 = sp9A;
    ret->unk4 = sp98;
    ret->unk6 = sp96;
    ret->unk8 = sp92;
    ret->unkA = sp90;
    ret->unkC = sp8E;

    ret->unk10 = (void*)_uvMemAlloc((sp94 * sp92 * sp98) / 8, 8);
    uvConsumeBytes(ret->unk10, &src, (sp94 * sp92 * sp98) / 8);

    sp74 = sp96 / sp90;
    sp70 = sp92 / sp8E;
    if (sp96 % sp90) {
        sp74++;
        remainder1 = 1;
    }
    if (sp92 % sp8E) {
        sp70++;
        remainder2 = 1;
    }
    ret->unkE = sp74 * sp70;
    ret->unk14 = (Unk80227260_0x8*)_uvMemAllocAlign8(ret->unkE * sizeof(Unk80227260_0x8));

    var_a1 = ret->unk10;
    for (i = 0; i < sp70; i++) {
        for (j = 0; j < sp74; j++) {
            temp_v0_3 = &ret->unk14[j + i * sp74];
            temp = i + 1;
            if (remainder2 && sp70 == temp) {
                temp_v0_3->unkC = sp92 % sp8E;
            } else {
                temp_v0_3->unkC = sp8E;
            }
            temp = j + 1;
            if (remainder1 && sp74 == temp) {
                temp_v0_3->unk0 = sp96 - (sp90 * (sp74 - 1));
            } else {
                temp_v0_3->unk0 = sp90;
            }
            temp_v0_3->unkE = 0;
            temp_v0_3->unk6 = temp_v0_3->unkE;
            temp_v0_3->unk4 = temp_v0_3->unkE;
            temp_v0_3->unk2 = sp90;
            temp_v0_3->unk8 = var_a1;
            var_a1 += (temp_v0_3->unkC * sp90 * sp98) / 8;
        }
    }
    return ret;
}

ParsedUVCT* uvParseTopUVCT(s32 arg0) {
    s32 idx;
    u32 tag;
    u32 sp3C;
    void* src;
    ParsedUVCT* ret;

    ret = NULL;
    idx = uvFileReadHeader(gUVBlockOffsets.UVCT[arg0]);
    while ((tag = uvFileReadBlock(idx, &sp3C, &src, 1)) != 0) {
        switch (tag) {
        case 'COMM':
            ret = _uvParseUVCT(src);
            break;
        default:
            break;
        }
    }
    uvFile_80223F30(idx);
    return ret;
}

ParsedUVEN* uvParseTopUVEN(s32 palette) {
    s32 idx;
    s32 sp28;
    void* src;
    ParsedUVEN* ret;

    ret = NULL;
    idx = uvFileReadHeader(gUVBlockOffsets.UVEN[0]);
    if (uvFile_80224170(idx, &sp28, &src, 'COMM', palette, 1) != 0) {
        ret = _uvParseUVEN(src);
    }
    uvFile_80223F30(idx);
    return ret;
}

ParsedUVLV* uvParseTopUVLV(s32 palette) {
    s32 idx;
    s32 sp28;
    void* src;
    void* ret;

    ret = NULL;
    idx = uvFileReadHeader(gUVBlockOffsets.UVLV[0]);
    if (uvFile_80224170(idx, &sp28, &src, 'COMM', palette, 1) != 0) {
        ret = _uvExpandTextureCpy(src);
    }
    uvFile_80223F30(idx);
    return ret;
}

ParsedUVTP* uvParseTopUVTP(s32 palette) {
    s32 idx;
    s32 sp28;
    void* src;
    ParsedUVTP* ret;

    ret = NULL;
    idx = uvFileReadHeader(gUVBlockOffsets.UVTP[0]);
    if (uvFile_80224170(idx, &sp28, &src, 'COMM', palette, 1) != 0) {
        ret = _uvParseUVTP(src);
    }
    uvFile_80223F30(idx);
    return ret;
}

void* uvParseTopUVLT(s32 palette) {
    s32 idx;
    s32 sp28;
    void* src;
    void* ret;

    ret = NULL;
    idx = uvFileReadHeader(gUVBlockOffsets.UVLT[0]);
    if (uvFile_80224170(idx, &sp28, &src, 'COMM', palette, 1) != 0) {
        ret = _uvParseUVLT(src);
    }
    uvFile_80223F30(idx);
    return ret;
}

void* uvParseTopUVMD(s32 arg0) {
    s32 idx;
    u32 tag;
    u32 sp3C;
    void* src;
    void* ret;

    ret = NULL;
    idx = uvFileReadHeader(gUVBlockOffsets.UVMD[arg0]);
    while ((tag = uvFileReadBlock(idx, &sp3C, &src, 1)) != 0) {
        switch (tag) {
        case 'COMM':
            ret = _uvParseUVMD(src);
            break;
        default:
            break;
        }
    }
    uvFile_80223F30(idx);
    return ret;
}

ParsedUVTR* uvParseTopUVTR(s32 arg0) {
    s32 idx;
    s32 sp28;
    void* src;
    ParsedUVTR* ret;

    ret = NULL;
    idx = uvFileReadHeader(gUVBlockOffsets.UVTR[0]);
    if (uvFile_80224170(idx, &sp28, &src, 'COMM', arg0, 1) != 0) {
        ret = _uvParseUVTR(src);
    }
    uvFile_80223F30(idx);
    return ret;
}

ParsedUVTX* uvParseTopUVTX(s32 arg0) {
    s32 idx;
    u32 tag;
    u32 sp34;
    void* src;
    ParsedUVTX* ret;

    idx = uvFileReadHeader(gUVBlockOffsets.UVTX[arg0]);
    while ((tag = uvFileReadBlock(idx, &sp34, &src, 1)) != 0) {
        switch (tag) {
        case 'COMM':
            ret = _uvExpandTexture(src);
            break;
        default:
            break;
        }
    }
    uvFile_80223F30(idx);
    return ret;
}

void* uvParseTopUVTI(s32 arg0) {
    s32 idx;
    u32 tag;
    u32 sp34;
    void* src;
    void* ret;

    idx = uvFileReadHeader(gUVBlockOffsets.UVTX[arg0]);

    while ((tag = uvFileReadBlock(idx, &sp34, &src, 1)) != 0) {
        switch (tag) {
        case 'COMM':
            ret = _uvExpandTextureImg(src);
            break;
        default:
            break;
        }
    }
    uvFile_80223F30(idx);
    return ret;
}

void* uvParseTopUVBT(s32 arg0) {
    s32 idx;
    u32 tag;
    u32 sp3C;
    void* src;
    void* ret;

    idx = uvFileReadHeader(gUVBlockOffsets.UVBT[arg0]);
    while ((tag = uvFileReadBlock(idx, &sp3C, &src, 0)) != 0) {
        switch (tag) {
        case 'COMM':
            ret = _uvParseUVBT(src);
            break;
        default:
            break;
        }
    }
    uvFile_80223F30(idx);
    return ret;
}

ParsedUVSQ* uvParseTopUVSQ(s32 palette) {
    s32 idx;
    s32 sp28;
    void* src;
    ParsedUVSQ* ret;

    ret = NULL;
    idx = uvFileReadHeader(gUVBlockOffsets.UVSQ[0]);
    if (uvFile_80224170(idx, &sp28, &src, 'COMM', palette, 1) != 0) {
        ret = _uvParseUVSQ(src);
    }
    uvFile_80223F30(idx);
    return ret;
}

s32 func_80227E5C(s32 arg0, s32 arg1) {
    void* var_v0 = NULL;

    switch (arg0) {
    case 1:
        var_v0 = gGfxUnkPtrs->unk4[arg1];
        break;
    case 2:
        var_v0 = gGfxUnkPtrs->unk30[arg1];
        break;
    case 3:
        var_v0 = gGfxUnkPtrs->unk44[arg1];
        break;
    case 4:
        var_v0 = gGfxUnkPtrs->unkC8[arg1];
        break;
    case 5:
        var_v0 = gGfxUnkPtrs->unk910[arg1];
        break;
    case 6:
        var_v0 = gGfxUnkPtrs->unk10E4[arg1];
        break;
    }
    if (var_v0 != NULL) {
        return TRUE;
    }
    return FALSE;
}

