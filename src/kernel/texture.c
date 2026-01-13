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
    Unk802270BC_48 *unk28;
} Unk802270BC_2C;

typedef struct {
    s32 tag;
    s32 size;
} UVBlockHeader;

// forward declarations
void* _uvExpandTexture(void*);
void* _uvExpandTextureCpy(void*);
void* _uvExpandTextureImg(void*);
void* func_80219270(s32);
void func_80225394(void* dst, void** ptr, s32 size);
void* func_80225470(void*);
void* func_802254B0(void*);
void* func_802255A0(void*);
void* func_802256B8(void*);
void* func_80225FBC(void*);
void* func_80226FD0(void*);
void* func_802270BC(void*);
void* func_80227260(void*);
void* func_80227804(s32);
void* func_802278C0(s32);
void* func_80227938(s32);
void* func_802279B0(s32);
void* func_80227A28(s32);
void* func_80227AA0(s32);
void* func_80227B5C(s32);
void* func_80227BD4(s32);
void* func_80227C84(s32);
void* func_80227D34(s32);
void* func_80227DE4(s32);
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
    s32 var_v0; // tag
    UVBlockHeader* var_a0;

    uvMemSet(&gUVBlockCounts, 0, sizeof(gUVBlockCounts));
    sp64 = func_80223E80(D_DE720);
    romOffset = D_DF5B0;

    while ((var_v0 = func_80223F7C(sp64, &sp5C, &sp58, 1)) != 0) {
        if (var_v0 == 'TABL') { // 0x5441424C
            for (var_a1 = 0, var_a0 = (UVBlockHeader*)sp58; var_a1 < sp5C; var_a1 += 8, var_a0++) {
                switch (var_a0->tag) {
                    case 0:
                        break;
                    case 'UVSY': // 0x55565359
                        gUVBlockOffsets.UVSY = romOffset;
                        break;
                    case 'UVAN': // 0x5556414E
                        gUVBlockOffsets.UVAN[gUVBlockCounts.UVAN++] = romOffset;
                        break;
                    case 'UVFT': // 0x55564654
                        gUVBlockOffsets.UVFT[gUVBlockCounts.UVFT++] = romOffset;
                        break;
                    case 'UVBT': // 0x55564254
                        gUVBlockOffsets.UVBT[gUVBlockCounts.UVBT++] = romOffset;
                        break;
                    case 'UVMD': // 0x55564D44
                        gUVBlockOffsets.UVMD[gUVBlockCounts.UVMD++] = romOffset;
                        break;
                    case 'UVCT': // 0x55564354
                        gUVBlockOffsets.UVCT[gUVBlockCounts.UVCT++] = romOffset;
                        break;
                    case 'UVTX': // 0x55565458
                        gUVBlockOffsets.UVTX[gUVBlockCounts.UVTX++] = romOffset;
                        break;
                    case 'UVEN': // 0x5556454E
                        gUVBlockOffsets.UVEN[gUVBlockCounts.UVEN++] = romOffset;
                        break;
                    case 'UVLT': // 0x55564C54
                        gUVBlockOffsets.UVLT[gUVBlockCounts.UVLT++] = romOffset;
                        break;
                    case 'UVLV': // 0x55564C56
                        gUVBlockOffsets.UVLV[gUVBlockCounts.UVLV++] = romOffset;
                        break;
                    case 'UVSQ': // 0x55565351
                        gUVBlockOffsets.UVSQ[gUVBlockCounts.UVSQ++] = romOffset;
                        break;
                    case 'UVTR': // 0x55565452
                        gUVBlockOffsets.UVTR[gUVBlockCounts.UVTR++] = romOffset;
                        break;
                    case 'UVTP': // 0x55565450
                        gUVBlockOffsets.UVTP[gUVBlockCounts.UVTP++] = romOffset;
                        break;
                    case 'UVSX': // 0x55565358
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

void* func_80224A90(u32 tag, s32 arg1) {
    void* ret;

    ret = NULL;
    _uvJumpHeap(&D_802B892C);
    do {
        if (1) {} // fakematch
        switch (tag) {
            case 'UVSQ': // 0x55565351
                ret = func_80227DE4(arg1);
                break;
            case 'UVEN': // 0x5556454E
                ret = func_802278C0(arg1);
                break;
            case 'UVTR': // 0x55565452
                ret = func_80227B5C(arg1);
                break;
            case 'UVCT': // 0x55564354
                ret = func_80227804(arg1);
                break;
            case 'UVLV': // 0x55564C56
                ret = func_80227938(arg1);
                break;
            case 'UVMD': // 0x55564D44
                ret = func_80227AA0(arg1);
                break;
            case 'UVTX': // 0x55565458
                ret = func_80227BD4(arg1);
                break;
            case 'UVTI': // 0x55565449
                ret = func_80227C84(arg1);
                break;
            case 'UVLT': // 0x55564C54
                ret = func_80227A28(arg1);
                break;
            case 'UVAN': // 0x5556414E
                ret = uvJanimLoad(arg1);
                break;
            case 'UVFT': // 0x55564654
                ret = func_80219270(arg1);
                break;
            case 'UVBT': // 0x55564254
                ret = func_80227D34(arg1);
                break;
            case 'UVTP': // 0x55565450
                ret = func_802279B0(arg1);
                break;
        }
    } while (_uvJumpHeap(&D_802B892C) == 0);
    return ret;
}

void uvMemLoadPal(s32 arg0) {
    u32 temp_v0;

    if (arg0 == 0xFFFF) {
       D_802B53C0 = NULL;
    } else {
        D_802B53C0 = func_80224A90('UVTP', arg0); // 0x55565450
        if (D_802B53C0 == NULL) {
            _uvDebugPrintf("uvMemLoadPal: palette %d not in dbase\n", arg0);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/texture/uvMemLoadDS.s")

void func_80225394(void* dst, void** ptr, s32 size) {
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

void* func_80225470(void* arg0) {
    void* ret;
    ret = (void*)_uvMemAlloc(4, 4);
    func_80225394(ret, &arg0, 4);
    return ret;
}

void* func_802254B0(void* arg0) {
    Unk80219270_4* temp_s3;
    u8 count;
    s32 var_s0;
    Unk80219270_3C* temp_v0;

    func_80225394(&count, &arg0, 1);
    temp_s3 = (Unk80219270_4*)_uvMemAlloc(count * 4, 4);

    for(var_s0 = 0; var_s0 < (s32) count; var_s0++) {
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

void* func_802255A0(void* arg0) {
    u16 idx;
    u8 count;
    Unk802255A0_8* temp_s3;
    Unk802255A0_10* temp_v0;

    func_80225394(&count, &arg0, 1);
    temp_s3 = (Unk802255A0_8*)_uvMemAlloc(count * 8, 4);

    for(idx = 0; idx < (s32) count; idx++) {
        func_80225394(&temp_s3[idx].unk0, &arg0, 2);
        func_80225394(&temp_s3[idx].unk4, &arg0, 4);
        temp_s3[idx].unk2 = 0xFF;
    }

    temp_v0 = (Unk802255A0_10*)_uvMemAlloc(0x10, 4);
    func_80225394(&temp_v0->unk8, &arg0, 1);
    func_80225394(&temp_v0->unk9, &arg0, 1);
    func_80225394(&temp_v0->unkC, &arg0, 4);
    temp_v0->unk4 = temp_s3;
    temp_v0->count = count;
    return temp_v0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/texture/func_802256B8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/texture/func_80225FBC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/texture/_uvExpandTexture.s")

void* _uvExpandTextureImg(void* arg0) {
    void* retBuf;
    u16 sp32;
    u16 size;
    u16 sp2E;
    u16 sp2C;
    u16 sp2A;
    u16 sp28;

    func_80225394(&size, &arg0, 2);
    if (size >= 0x1001) {
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

void* func_80226FD0(void* arg0) {
    Unk80226FD0_C* temp_s2;
    u16 idx;
    u16 count;

    func_80225394(&count, &arg0, 2);
    temp_s2 = (Unk80226FD0_C*)_uvMemAlloc(0xC, 4);
    temp_s2->unk4 = (u16*)_uvMemAlloc(count * 2, 4);
    temp_s2->unk8 = (u16*)_uvMemAlloc(count * 2, 4);

    for(idx = 0; idx < count; idx++) {
        func_80225394(&temp_s2->unk4[idx], &arg0, 2);
        func_80225394(&temp_s2->unk8[idx], &arg0, 2);
    }
    temp_s2->count = count;
    return temp_s2;
}

void* func_802270BC(void* arg0) {
    Unk802270BC_48 *ptr;
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

    for(idx = 0; idx < count; idx++) {
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

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/texture/func_80227260.s")

void* func_80227804(s32 arg0) {
    s32 idx;
    s32 tag;
    u32 sp3C;
    void* sp38;
    void* ret;

    ret = NULL;
    idx = func_80223E80(D_802B5A34[arg0]);
    while ((tag = func_80223F7C(idx, &sp3C, &sp38, 1)) != 0) {
        if (tag == 'COMM') { // 0x434F4D4D
            if (1) {} // fakematch
            ret = func_80225FBC(sp38);
        }
    }
    func_80223F30(idx);
    return ret;
}

void* func_802278C0(s32 arg0) {
    s32 sp2C;
    s32 sp28;
    void* sp24;
    void* ret;

    ret = NULL;
    sp2C = func_80223E80(D_802B6404);
    if (func_80224170(sp2C, &sp28, &sp24, 'COMM', arg0, 1) != 0) { // 0x434F4D4D
        ret = func_802254B0(sp24);
    }
    func_80223F30(sp2C);
    return ret;
}

void* func_80227938(s32 arg0) {
    s32 idx;
    s32 sp28;
    void* sp24;
    void* ret;

    ret = NULL;
    idx = func_80223E80(D_802B64E4);
    if (func_80224170(idx, &sp28, &sp24, 'COMM', arg0, 1) != 0) { // 0x434F4D4D
        ret = _uvExpandTextureCpy(sp24);
    }
    func_80223F30(idx);
    return ret;
}

void* func_802279B0(s32 arg0) {
    s32 idx;
    s32 sp28;
    void* sp24;
    void* ret;

    ret = NULL;
    idx = func_80223E80(D_802B6E2C);
    if (func_80224170(idx, &sp28, &sp24, 'COMM', arg0, 1) != 0) { // 0x434F4D4D
        ret = func_80226FD0(sp24);
    }
    func_80223F30(idx);
    return ret;
}

void* func_80227A28(s32 arg0) {
    s32 idx;
    s32 sp28;
    void* sp24;
    void* ret;

    ret = NULL;
    idx = func_80223E80(D_802B6484);
    if (func_80224170(idx, &sp28, &sp24, 'COMM', arg0, 1) != 0) { // 0x434F4D4D
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
        if (tag == 'COMM') { // 0x434F4D4D
            if (1) {} // fakematch
            ret = func_802256B8(sp38);
        }
    }
    func_80223F30(idx);
    return ret;
}

void* func_80227B5C(s32 arg0) {
    s32 idx;
    s32 sp28;
    void* sp24;
    void* ret;

    ret = NULL;
    idx = func_80223E80(D_802B6494);
    if (func_80224170(idx, &sp28, &sp24, 'COMM', arg0, 1) != 0) { // 0x434F4D4D
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
        if (tag == 'COMM') { // 0x434F4D4D
            if (1) {} // fakematch
            ret = _uvExpandTexture(sp30);
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
        if (tag == 'COMM') { // 0x434F4D4D
            if (1) {} // fakematch
            ret = _uvExpandTextureImg(sp30);
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
        if (tag == 'COMM') { // 0x434F4D4D
            if (1) {} // fakematch
            ret = func_80227260(sp38);
        }
    }
    func_80223F30(idx);
    return ret;
}

void* func_80227DE4(s32 arg0) {
    s32 idx;
    s32 sp28;
    void* sp24;
    void* ret;

    ret = NULL;
    idx = func_80223E80(D_802B64BC);
    if (func_80224170(idx, &sp28, &sp24, 'COMM', arg0, 1) != 0) { // 0x434F4D4D
        ret = func_802255A0(sp24);
    }
    func_80223F30(idx);
    return ret;
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/texture/func_80227E5C.s")
