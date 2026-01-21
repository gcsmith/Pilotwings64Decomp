#include "common.h"
#include <uv_janim.h>
#include <uv_graphics.h>
#include <uv_memory.h>
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

// forward declarations
void* uvParseTopUVFT(s32);
ParsedUVCT* uvParseTopUVCT(s32);
ParsedUVEN* uvParseTopUVEN(s32);
void* uvParseTopUVLV(s32);
ParsedUVTP* uvParseTopUVTP(s32);
void* uvParseTopUVLT(s32);
void* uvParseTopUVMD(s32);
ParsedUVTR* uvParseTopUVTR(s32);
void* uvParseTopUVTX(s32);
void* uvParseTopUVTI(s32);
void* uvParseTopUVBT(s32);
ParsedUVSQ* uvParseTopUVSQ(s32);

void* _uvExpandTexture(void*);
void* _uvExpandTextureCpy(void*);
void* _uvExpandTextureImg(u8*);
void* _uvParseUVLT(u8*);
ParsedUVEN* _uvParseUVEN(u8*);
ParsedUVSQ* _uvParseUVSQ(u8*);
void* _uvParseUVMD(u8*);
ParsedUVTP* _uvParseUVTP(u8*);
ParsedUVTR* _uvParseUVTR(u8*);
ParsedUVBT* _uvParseUVBT(u8*);

// ROM offsets for file system data
extern u8 D_DE720[];
extern u8 D_DF5B0[];

extern u8 initialize_emu_text_0000[];
extern u32 D_802B53F4[];
extern u32 D_802B5A34[];
extern u32 D_802B5C34[];
extern u32 D_802B6404;
extern u32 D_802B6484;
extern u32 D_802B6494;
extern u32 D_802B64BC;
extern u32 D_802B64E4;
extern u32 D_802B6A34[];
extern u32 D_802B6E2C;
extern u32 D_802B892C;

void func_802246A0(void) {
    s32 sp64;
    s32 temp_v0;
    u32 sp5C;
    void* src;
    u32 var_a1;
    u8* romOffset;
    u32 tag;
    UVBlockHeader* var_a0;

    uvMemSet(&gUVBlockCounts, 0, sizeof(gUVBlockCounts));
    sp64 = func_80223E80(D_DE720);
    romOffset = D_DF5B0;

    while ((tag = func_80223F7C(sp64, &sp5C, &src, 1)) != 0) {
        if (tag == 'TABL') {
            for (var_a1 = 0, var_a0 = (UVBlockHeader*)src; var_a1 < sp5C; var_a1 += 8, var_a0++) {
                switch (var_a0->tag) {
                case 0:
                    break;
                case 'UVSY':
                    gUVBlockOffsets.UVSY = romOffset;
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
    func_80223F30(sp64);
    uvLevelInit();
}

void* func_80224A90(u32 tag, s32 palette) {
    void* ret;

    ret = NULL;
    _uvJumpHeap(&D_802B892C);
    do {
        if (1) { } // fakematch
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
        }
    } while (_uvJumpHeap(&D_802B892C) == 0);
    return ret;
}

void uvMemLoadPal(s32 palette) {
    if (palette == 0xFFFF) {
        D_802B53C0 = NULL;
    } else {
        D_802B53C0 = func_80224A90('UVTP', palette);
        if (D_802B53C0 == NULL) {
            _uvDebugPrintf("uvMemLoadPal: palette %d not in dbase\n", palette);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/texture/uvMemLoadDS.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/texture/_uvParseUVMD.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/texture/_uvExpandTexture.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/texture/_uvExpandTextureCpy.s")

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
            ptr->unk40 = *(s32*)(initialize_emu_text_0000 + (sp44 * 4) + 0x70C);
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
    idx = func_80223E80(D_802B5A34[arg0]);
    while ((tag = func_80223F7C(idx, &sp3C, &src, 1)) != 0) {
        switch (tag) {
        case 'COMM':
            ret = _uvParseUVCT(src);
            break;
        default:
            break;
        }
    }
    func_80223F30(idx);
    return ret;
}

ParsedUVEN* uvParseTopUVEN(s32 palette) {
    s32 idx;
    s32 sp28;
    void* src;
    ParsedUVEN* ret;

    ret = NULL;
    idx = func_80223E80(D_802B6404);
    if (func_80224170(idx, &sp28, &src, 'COMM', palette, 1) != 0) {
        ret = _uvParseUVEN(src);
    }
    func_80223F30(idx);
    return ret;
}

void* uvParseTopUVLV(s32 palette) {
    s32 idx;
    s32 sp28;
    void* src;
    void* ret;

    ret = NULL;
    idx = func_80223E80(D_802B64E4);
    if (func_80224170(idx, &sp28, &src, 'COMM', palette, 1) != 0) {
        ret = _uvExpandTextureCpy(src);
    }
    func_80223F30(idx);
    return ret;
}

ParsedUVTP* uvParseTopUVTP(s32 palette) {
    s32 idx;
    s32 sp28;
    void* src;
    ParsedUVTP* ret;

    ret = NULL;
    idx = func_80223E80(D_802B6E2C);
    if (func_80224170(idx, &sp28, &src, 'COMM', palette, 1) != 0) {
        ret = _uvParseUVTP(src);
    }
    func_80223F30(idx);
    return ret;
}

void* uvParseTopUVLT(s32 palette) {
    s32 idx;
    s32 sp28;
    void* src;
    void* ret;

    ret = NULL;
    idx = func_80223E80(D_802B6484);
    if (func_80224170(idx, &sp28, &src, 'COMM', palette, 1) != 0) {
        ret = _uvParseUVLT(src);
    }
    func_80223F30(idx);
    return ret;
}

void* uvParseTopUVMD(s32 arg0) {
    s32 idx;
    u32 tag;
    u32 sp3C;
    void* src;
    void* ret;

    ret = NULL;
    idx = func_80223E80(D_802B53F4[arg0]);
    while ((tag = func_80223F7C(idx, &sp3C, &src, 1)) != 0) {
        switch (tag) {
        case 'COMM':
            ret = _uvParseUVMD(src);
            break;
        default:
            break;
        }
    }
    func_80223F30(idx);
    return ret;
}

ParsedUVTR* uvParseTopUVTR(s32 arg0) {
    s32 idx;
    s32 sp28;
    void* src;
    ParsedUVTR* ret;

    ret = NULL;
    idx = func_80223E80(D_802B6494);
    if (func_80224170(idx, &sp28, &src, 'COMM', arg0, 1) != 0) {
        ret = _uvParseUVTR(src);
    }
    func_80223F30(idx);
    return ret;
}

void* uvParseTopUVTX(s32 arg0) {
    s32 idx;
    u32 tag;
    u32 sp34;
    void* src;
    void* ret;

    idx = func_80223E80(D_802B5C34[arg0]);
    while ((tag = func_80223F7C(idx, &sp34, &src, 1)) != 0) {
        switch (tag) {
        case 'COMM':
            ret = _uvExpandTexture(src);
            break;
        default:
            break;
        }
    }
    func_80223F30(idx);
    return ret;
}

void* uvParseTopUVTI(s32 arg0) {
    s32 idx;
    u32 tag;
    u32 sp34;
    void* src;
    void* ret;

    idx = func_80223E80(D_802B5C34[arg0]);

    while ((tag = func_80223F7C(idx, &sp34, &src, 1)) != 0) {
        switch (tag) {
        case 'COMM':
            ret = _uvExpandTextureImg(src);
            break;
        default:
            break;
        }
    }
    func_80223F30(idx);
    return ret;
}

void* uvParseTopUVBT(s32 arg0) {
    s32 idx;
    u32 tag;
    u32 sp3C;
    void* src;
    void* ret;

    idx = func_80223E80(D_802B6A34[arg0]);
    while ((tag = func_80223F7C(idx, &sp3C, &src, 0)) != 0) {
        switch (tag) {
        case 'COMM':
            ret = _uvParseUVBT(src);
            break;
        default:
            break;
        }
    }
    func_80223F30(idx);
    return ret;
}

ParsedUVSQ* uvParseTopUVSQ(s32 palette) {
    s32 idx;
    s32 sp28;
    void* src;
    ParsedUVSQ* ret;

    ret = NULL;
    idx = func_80223E80(D_802B64BC);
    if (func_80224170(idx, &sp28, &src, 'COMM', palette, 1) != 0) {
        ret = _uvParseUVSQ(src);
    }
    func_80223F30(idx);
    return ret;
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/texture/func_80227E5C.s")
