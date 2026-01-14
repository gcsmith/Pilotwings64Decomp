#include "common.h"
#include <uv_graphics.h>
#include <uv_memory.h>

typedef struct {
    u16 unk0;
    u16 unk4;
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
} Unk80219270_3C;

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
} Unk802255A0_10;

typedef struct {
    u16 count;
    u16 unk2;
    u16* unk4;
    u16* unk8;
} Unk80226FD0_C;

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
} Unk802270BC_2C;

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
    Gfx* unk8;
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
    void* unk0;
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
} Unk80225FBC_0x2C;

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
} Unk80227260_0x18;

// forward declarations
void* _uvExpandTexture(void*);
void* _uvExpandTextureCpy(void*);
void* _uvExpandTextureImg(u8*);
void* func_80219270(s32);
void func_80225394(void* dst, u8** ptr, s32 size);
void* func_80225470(u8*);
Unk80219270_3C* func_802254B0(u8*);
Unk802255A0_10* func_802255A0(u8*);
void* func_802256B8(u8*);
Unk80226FD0_C* func_80226FD0(u8*);
Unk802270BC_2C* func_802270BC(u8*);
Unk80227260_0x18* func_80227260(u8*);
Unk80225FBC_0x2C* func_80227804(s32);
Unk80219270_3C* func_802278C0(s32);
void* func_80227938(s32);
Unk80226FD0_C* func_802279B0(s32);
void* func_80227A28(s32);
void* func_80227AA0(s32);
Unk802270BC_2C* func_80227B5C(s32);
void* func_80227BD4(s32);
void* func_80227C84(s32);
void* func_80227D34(s32);
Unk802255A0_10* func_80227DE4(s32);
void* uvJanimLoad(s32);

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
    void* sp58;
    u32 var_a1;
    u8* romOffset;
    s32 tag;
    UVBlockHeader* var_a0;

    uvMemSet(&gUVBlockCounts, 0, sizeof(gUVBlockCounts));
    sp64 = func_80223E80(D_DE720);
    romOffset = D_DF5B0;

    while ((tag = func_80223F7C(sp64, &sp5C, &sp58, 1)) != 0) {
        if (tag == 'TABL') {
            for (var_a1 = 0, var_a0 = (UVBlockHeader*)sp58; var_a1 < sp5C; var_a1 += 8, var_a0++) {
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
            ret = func_80227DE4(palette);
            break;
        case 'UVEN':
            ret = func_802278C0(palette);
            break;
        case 'UVTR':
            ret = func_80227B5C(palette);
            break;
        case 'UVCT':
            ret = func_80227804(palette);
            break;
        case 'UVLV':
            ret = func_80227938(palette);
            break;
        case 'UVMD':
            ret = func_80227AA0(palette);
            break;
        case 'UVTX':
            ret = func_80227BD4(palette);
            break;
        case 'UVTI':
            ret = func_80227C84(palette);
            break;
        case 'UVLT':
            ret = func_80227A28(palette);
            break;
        case 'UVAN':
            ret = uvJanimLoad(palette);
            break;
        case 'UVFT':
            ret = func_80219270(palette);
            break;
        case 'UVBT':
            ret = func_80227D34(palette);
            break;
        case 'UVTP':
            ret = func_802279B0(palette);
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

void func_80225394(void* dst, u8** ptr, s32 size) {
    switch (size) {
    case 1:
        *(s8*)dst = uvMemRead(*ptr, size);
        *(u8**)ptr += 1;
        break;
    case 2:
        *(s16*)dst = uvMemRead(*ptr, size);
        *(u8**)ptr += 2;
        break;
    case 4:
        *(s32*)dst = uvMemRead(*ptr, size);
        *(u8**)ptr += 4;
        break;
    default:
        _uvMediaCopy(dst, *ptr, size);
        *(u8**)ptr += size;
        break;
    }
}

void* func_80225470(u8* arg0) {
    void* ret;
    ret = (void*)_uvMemAlloc(4, 4);
    func_80225394(ret, &arg0, 4);
    return ret;
}

Unk80219270_3C* func_802254B0(u8* arg0) {
    Unk80219270_4* temp_s3;
    u8 count;
    s32 var_s0;
    Unk80219270_3C* temp_v0;

    func_80225394(&count, &arg0, 1);
    temp_s3 = (Unk80219270_4*)_uvMemAlloc(count * 4, 4);

    for (var_s0 = 0; var_s0 < (s32)count; var_s0++) {
        func_80225394(&temp_s3[var_s0].unk0, &arg0, 2);
        func_80225394(&temp_s3[var_s0].unk4, &arg0, 1);
    }

    temp_v0 = (Unk80219270_3C*)_uvMemAlloc(sizeof(Unk80219270_3C), 4);
    func_80225394(temp_v0, &arg0, sizeof(Unk80219270_3C));
    temp_v0->count = count;
    temp_v0->unk38 = 0;
    temp_v0->unk30 = (temp_v0->count) ? temp_s3 : NULL;
    return temp_v0;
}

Unk802255A0_10* func_802255A0(u8* arg0) {
    u16 idx;
    u8 count;
    Unk802255A0_8* temp_s3;
    Unk802255A0_10* temp_v0;

    func_80225394(&count, &arg0, 1);
    temp_s3 = (Unk802255A0_8*)_uvMemAlloc(count * 8, 4);

    for (idx = 0; idx < (s32)count; idx++) {
        func_80225394(&temp_s3[idx].unk0, &arg0, 2);
        func_80225394(&temp_s3[idx].unk4, &arg0, 4);
        temp_s3[idx].unk2 = 0xFF;
    }

    temp_v0 = (Unk802255A0_10*)_uvMemAlloc(sizeof(Unk802255A0_10), 4);
    func_80225394(&temp_v0->unk8, &arg0, 1);
    func_80225394(&temp_v0->unk9, &arg0, 1);
    func_80225394(&temp_v0->unkC, &arg0, 4);
    temp_v0->unk4 = temp_s3;
    temp_v0->count = count;
    return temp_v0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/texture/func_802256B8.s")

Unk80225FBC_0x2C* func_80225FBC(u8* arg0) {
    Vtx* spAC;
    Vtx* tempVtx;
    Gfx* spA4;
    Unk80225FBC_0x28* spA0;
    Unk80225FBC_0x18* tempSp98;
    Unk80225FBC_0x18* sp98;
    Unk80225FBC_0x28* tempSpA0;
    Gfx* dl;
    Unk80225FBC_0x2C* temp_v0;
    u16 sp8A;
    u16 sp88;
    u16 sp86;
    s32 i;
    s32 j;
    u8 sp7B;
    u8 sp7A;
    u16 sp78;
    u16 sp76;
    u16 sp74;

    func_80225394(&sp78, &arg0, 2);
    func_80225394(&sp8A, &arg0, 2);
    func_80225394(&sp86, &arg0, 2);
    func_80225394(&sp88, &arg0, 2);

    spAC = (Vtx*)_uvMemAlloc(sp78 * sizeof(Vtx), 8);
    _uvMediaCopy(spAC, arg0, sp78 * sizeof(Vtx));
    arg0 += sp78 * sizeof(Vtx);

    spA4 = _uvMemAlloc(sp8A * sizeof(Gfx), 4);
    _uvMediaCopy((void*)spA4, arg0, sp8A * sizeof(Gfx));
    arg0 += sp8A * sizeof(Gfx);

    sp98 = (Unk80225FBC_0x18*)_uvMemAlloc(sp86 * sizeof(Unk80225FBC_0x18), 4);
    for (i = 0; i < sp86; i++) {
        tempSp98 = &sp98[i];
        func_80225394(&sp7B, &arg0, 1);
        tempSp98->unk4 = _uvMemAlloc(sp7B * 64, 4);
        func_80225394(tempSp98->unk4, &arg0, sp7B * 64);

        func_80225394(&tempSp98->unk0, &arg0, 2);
        func_80225394(&tempSp98->unk8, &arg0, 4);
        func_80225394(&tempSp98->unkC, &arg0, 4);
        func_80225394(&tempSp98->unk10, &arg0, 4);
        func_80225394(&tempSp98->unk14, &arg0, 2);
        func_80225394(&tempSp98->unk16, &arg0, 2);
    }

    spA0 = (Unk80225FBC_0x28*)_uvMemAlloc(sp88 * sizeof(Unk80225FBC_0x28), 4);
    for (i = 0; i < sp88; i++) {
        tempSpA0 = &spA0[i];
        func_80225394(&tempSpA0->unk0, &arg0, 4);
        func_80225394(&tempSpA0->unk4, &arg0, 2);
        func_80225394(&tempSpA0->unk6, &arg0, 2);
        func_80225394(&sp76, &arg0, 2);
        dl = (Gfx*)_uvMemAlloc((sp76 + 1) * sizeof(Gfx), 8); // +1 for END
        for (j = 0; j < sp76; j++) {
            func_80225394(&sp74, &arg0, 2);
            if (sp74 & 0x4000) {
                gSP1Triangle(&dl[j], (sp74 & 0xF00) >> 8, (sp74 & 0xF0) >> 4, sp74 & 0xF, 0);
            } else {
                func_80225394(&sp7A, &arg0, 1);
                tempVtx = &spAC[sp74 & 0x3FFF];
                gSPVertex(&dl[j], (u32)OS_PHYSICAL_TO_K0(tempVtx), ((sp7A & 0xF0) >> 4) + 1, sp7A & 0xF);
            }
        }

        gSPEndDisplayList(&dl[j]); // G_ENDDL = 0xB8
        tempSpA0->unk8 = dl;

        func_80225394(&sp74, &arg0, 2);
        tempSpA0->unkC = &spA4[sp74];

        func_80225394(&sp74, &arg0, 2);
        tempSpA0->unk10 = sp74;

        func_80225394(&tempSpA0->unk12, &arg0, 2);
        func_80225394(&tempSpA0->unk14, &arg0, 2);
        func_80225394(&tempSpA0->unk18, &arg0, 4);
        func_80225394(&tempSpA0->unk1C, &arg0, 4);
        func_80225394(&tempSpA0->unk20, &arg0, 4);
        func_80225394(&tempSpA0->unk24, &arg0, 4);
    }

    temp_v0 = (Unk80225FBC_0x2C*)_uvMemAlloc(sizeof(Unk80225FBC_0x2C), 4);
    temp_v0->unk0 = spAC;
    temp_v0->unk4 = sp78;
    temp_v0->unk8 = spA0;
    temp_v0->unkC = sp88;
    temp_v0->unk10 = sp98;
    temp_v0->unk14 = sp86;
    func_80225394(&temp_v0->unk18, &arg0, 4);
    func_80225394(&temp_v0->unk1C, &arg0, 4);
    func_80225394(&temp_v0->unk20, &arg0, 4);
    func_80225394(&temp_v0->unk24, &arg0, 4);
    func_80225394(&temp_v0->unk28, &arg0, 4);
    return temp_v0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/texture/_uvExpandTexture.s")

void* _uvExpandTextureImg(u8* arg0) {
    void* retBuf;
    u16 sp32;
    u16 size;
    u16 sp2E;
    u16 sp2C;
    u16 sp2A;
    u16 sp28;

    func_80225394(&size, &arg0, 2);
    if (size > 0x1000) {
        _uvDebugPrintf("_uvExpandTextureImg: txt image too big %d bytes (4096 max)\n", size);
        size = 0x1000;
    }
    func_80225394(&sp32, &arg0, 2);
    func_80225394(&sp2C, &arg0, 4);
    func_80225394(&sp28, &arg0, 4);
    func_80225394(&sp2C, &arg0, 4);
    func_80225394(&sp28, &arg0, 4);
    retBuf = (void*)_uvMemAlloc(size, 8);
    _uvMediaCopy(retBuf, arg0, size);
    return retBuf;
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/texture/_uvExpandTextureCpy.s")

Unk80226FD0_C* func_80226FD0(u8* arg0) {
    Unk80226FD0_C* temp_s2;
    u16 idx;
    u16 count;

    func_80225394(&count, &arg0, 2);
    temp_s2 = (Unk80226FD0_C*)_uvMemAlloc(sizeof(Unk80226FD0_C), 4);
    temp_s2->unk4 = (u16*)_uvMemAlloc(count * 2, 4);
    temp_s2->unk8 = (u16*)_uvMemAlloc(count * 2, 4);

    for (idx = 0; idx < count; idx++) {
        func_80225394(&temp_s2->unk4[idx], &arg0, 2);
        func_80225394(&temp_s2->unk8[idx], &arg0, 2);
    }
    temp_s2->count = count;
    return temp_s2;
}

Unk802270BC_2C* func_802270BC(u8* arg0) {
    Unk802270BC_48* ptr;
    Unk802270BC_2C* temp_v0;
    s32 count;
    s32 idx;
    u8 sp47;
    u16 sp44;

    temp_v0 = (Unk802270BC_2C*)_uvMemAlloc(sizeof(Unk802270BC_2C), 4);
    func_80225394(&temp_v0->unk0, &arg0, 0x18);
    func_80225394(&temp_v0->unk18, &arg0, 1);
    func_80225394(&temp_v0->unk19, &arg0, 1);
    func_80225394(&temp_v0->unk1C, &arg0, 4);
    func_80225394(&temp_v0->unk20, &arg0, 4);
    func_80225394(&temp_v0->unk24, &arg0, 4);
    count = temp_v0->unk18 * temp_v0->unk19;
    temp_v0->unk28 = (Unk802270BC_48*)_uvMemAlloc(count * sizeof(Unk802270BC_48), 4);

    for (idx = 0; idx < count; idx++) {
        ptr = &temp_v0->unk28[idx];
        func_80225394(&sp47, &arg0, 1);
        if (sp47 == 0) {
            uvMemSet(ptr->unk0, 0, 0x48);
        } else {
            func_80225394(&ptr->unk0, &arg0, 0x40);
            func_80225394(&ptr->unk44, &arg0, 1);
            func_80225394(&sp44, &arg0, 2);
            ptr->unk40 = *(s32*)(initialize_emu_text_0000 + (sp44 * 4) + 0x70C);
        }
    }
    return temp_v0;
}

Unk80227260_0x18* func_80227260(u8* arg0) {
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
    Unk80227260_0x18* ret;
    s32 sp74;
    s32 sp70;
    Unk80227260_0x8* temp_v0_3;
    s32 temp;

    remainder2 = 0;
    remainder1 = 0;

    _uvMediaCopy(&sp80, arg0, 4);
    sp80 >>= 32;
    sp9A = (sp80 & 0xFFFF0000) >> 16;
    sp98 = sp80;
    arg0 += 4;

    _uvMediaCopy(&sp80, arg0, 4);
    sp80 >>= 32;
    sp96 = (sp80 & 0xFFFF0000) >> 16;
    sp94 = sp80;
    arg0 += 4;

    _uvMediaCopy(&sp80, arg0, 4);
    sp80 >>= 32;
    sp92 = (sp80 & 0xFFFF0000) >> 16;
    sp90 = sp80;
    arg0 += 4;

    _uvMediaCopy(&sp80, arg0, 4);
    sp80 >>= 32;
    temp = (sp80 & 0xFFFF0000) >> 16;
    // fake, probably used to assign sp8C here as well
    sp8E = temp & 0xFFFF & 0xFFFF & 0xFFFF;
    arg0 += 2;

    ret = _uvMemAlloc(sizeof(Unk80227260_0x18), 4);
    ret->unk2 = sp9A;
    ret->unk4 = sp98;
    ret->unk6 = sp96;
    ret->unk8 = sp92;
    ret->unkA = sp90;
    ret->unkC = sp8E;

    ret->unk10 = _uvMemAlloc((sp94 * sp92 * sp98) / 8, 8);
    func_80225394((void*)ret->unk10, &arg0, (sp94 * sp92 * sp98) / 8);

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
    ret->unk14 = _uvMemAllocAlign8(ret->unkE * sizeof(Unk80227260_0x8));

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

Unk80225FBC_0x2C* func_80227804(s32 arg0) {
    s32 idx;
    s32 tag;
    u32 sp3C;
    void* sp38;
    Unk80225FBC_0x2C* ret;

    ret = NULL;
    idx = func_80223E80(D_802B5A34[arg0]);
    while ((tag = func_80223F7C(idx, &sp3C, &sp38, 1)) != 0) {
        switch (tag) {
        case 'COMM':
            ret = func_80225FBC(sp38);
            break;
        default:
            break;
        }
    }
    func_80223F30(idx);
    return ret;
}

Unk80219270_3C* func_802278C0(s32 palette) {
    s32 sp2C;
    s32 sp28;
    void* sp24;
    Unk80219270_3C* ret;

    ret = NULL;
    sp2C = func_80223E80(D_802B6404);
    if (func_80224170(sp2C, &sp28, &sp24, 'COMM', palette, 1) != 0) {
        ret = func_802254B0(sp24);
    }
    func_80223F30(sp2C);
    return ret;
}

void* func_80227938(s32 palette) {
    s32 idx;
    s32 sp28;
    void* sp24;
    void* ret;

    ret = NULL;
    idx = func_80223E80(D_802B64E4);
    if (func_80224170(idx, &sp28, &sp24, 'COMM', palette, 1) != 0) {
        ret = _uvExpandTextureCpy(sp24);
    }
    func_80223F30(idx);
    return ret;
}

Unk80226FD0_C* func_802279B0(s32 palette) {
    s32 idx;
    s32 sp28;
    void* sp24;
    Unk80226FD0_C* ret;

    ret = NULL;
    idx = func_80223E80(D_802B6E2C);
    if (func_80224170(idx, &sp28, &sp24, 'COMM', palette, 1) != 0) {
        ret = func_80226FD0(sp24);
    }
    func_80223F30(idx);
    return ret;
}

void* func_80227A28(s32 palette) {
    s32 idx;
    s32 sp28;
    void* sp24;
    void* ret;

    ret = NULL;
    idx = func_80223E80(D_802B6484);
    if (func_80224170(idx, &sp28, &sp24, 'COMM', palette, 1) != 0) {
        ret = func_80225470(sp24);
    }
    func_80223F30(idx);
    return ret;
}

void* func_80227AA0(s32 arg0) {
    s32 idx;
    s32 tag;
    u32 sp3C;
    void* sp38;
    void* ret;

    ret = NULL;
    idx = func_80223E80(D_802B53F4[arg0]);
    while ((tag = func_80223F7C(idx, &sp3C, &sp38, 1)) != 0) {
        switch (tag) {
        case 'COMM':
            ret = func_802256B8(sp38);
            break;
        default:
            break;
        }
    }
    func_80223F30(idx);
    return ret;
}

Unk802270BC_2C* func_80227B5C(s32 arg0) {
    s32 idx;
    s32 sp28;
    void* sp24;
    Unk802270BC_2C* ret;

    ret = NULL;
    idx = func_80223E80(D_802B6494);
    if (func_80224170(idx, &sp28, &sp24, 'COMM', arg0, 1) != 0) {
        ret = func_802270BC(sp24);
    }
    func_80223F30(idx);
    return ret;
}

void* func_80227BD4(s32 arg0) {
    s32 idx;
    s32 tag;
    u32 sp34;
    void* sp30;
    void* ret;

    idx = func_80223E80(D_802B5C34[arg0]);
    while ((tag = func_80223F7C(idx, &sp34, &sp30, 1)) != 0) {
        switch (tag) {
        case 'COMM':
            ret = _uvExpandTexture(sp30);
            break;
        default:
            break;
        }
    }
    func_80223F30(idx);
    return ret;
}

void* func_80227C84(s32 arg0) {
    s32 idx;
    s32 tag;
    u32 sp34;
    void* sp30;
    void* ret;

    idx = func_80223E80(D_802B5C34[arg0]);

    while ((tag = func_80223F7C(idx, &sp34, &sp30, 1)) != 0) {
        switch (tag) {
        case 'COMM':
            ret = _uvExpandTextureImg(sp30);
            break;
        default:
            break;
        }
    }
    func_80223F30(idx);
    return ret;
}

void* func_80227D34(s32 arg0) {
    s32 idx;
    s32 tag;
    u32 sp3C;
    void* sp38;
    void* ret;

    idx = func_80223E80(D_802B6A34[arg0]);
    while ((tag = func_80223F7C(idx, &sp3C, &sp38, 0)) != 0) {
        switch (tag) {
        case 'COMM':
            ret = func_80227260(sp38);
            break;
        default:
            break;
        }
    }
    func_80223F30(idx);
    return ret;
}

Unk802255A0_10* func_80227DE4(s32 palette) {
    s32 idx;
    s32 sp28;
    void* sp24;
    Unk802255A0_10* ret;

    ret = NULL;
    idx = func_80223E80(D_802B64BC);
    if (func_80224170(idx, &sp28, &sp24, 'COMM', palette, 1) != 0) {
        ret = func_802255A0(sp24);
    }
    func_80223F30(idx);
    return ret;
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/texture/func_80227E5C.s")
