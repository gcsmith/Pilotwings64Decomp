#include "common.h"
#include <uv_filesystem.h>
#include <uv_memory.h>
#include <uv_string.h>
#include "text_data.h"

// unsure why one fewer data than text pointers
static s16* sTextName[440];
static s16* sTextData[439];
static s32 sTextDataCount;
static s32 sTextNameCount;

void textLoadBlock(s32 id) {
    s32 block;
    u32 tag;
    s32 i;
    u32 size;
    s32 pad;
    void* data;
    s32 ch;
    s32 newCh;

    block = uvFileReadHeader((s32)func_802314D0(id, 2));
    sTextNameCount = 0;
    sTextDataCount = 0;

    while ((tag = uvFileReadBlock(block, &size, &data, 1)) != 0) {
        switch (tag) {
        case 'SIZE': // 0x53495A45
            break;
        case 'NAME': // 0x4E414D45
            sTextName[sTextNameCount] = (s16*)_uvMemAllocAlign8(size);
            _uvMediaCopy(sTextName[sTextNameCount], data, size);
            sTextNameCount++;
            break;
        case 'DATA': // 0x44415441
            sTextData[sTextDataCount] = (s16*)_uvMemAllocAlign8(size + 2);
            _uvMediaCopy(sTextData[sTextDataCount], data, size);
            for (i = 0; (u32)i < size; i++) {
                ch = sTextData[sTextDataCount][i];
                if (ch == 0xFE) {
                    sTextData[sTextDataCount][i] = 0xFFE;
                } else {
                    newCh = ch == 0xFF ? -1 : ch;
                    sTextData[sTextDataCount][i] = newCh;
                }
            }
            sTextDataCount++;
            break;
        }
    }
    uvFile_80223F30(block);
}

s16* textGetDataByName(s16* needle) {
    s16* dataStr;
    s32 i;

    dataStr = NULL;
    for (i = 0; i < sTextNameCount; i++) {
        if (uvStrcmp((char*)sTextName[i], (char*)needle) == 0) {
            dataStr = sTextData[i];
            break;
        }
    }
    return dataStr;
}

s16* textGetDataByIdx(s32 idx) {
    if ((idx >= 0) && (idx < sTextDataCount)) {
        return sTextData[idx];
    }
    return NULL;
}

s32 textFmtInt(s16* dst, s32 val, s32 length) {
    s32 digits;
    s32 fill;
    s32 i;

    if (val >= 100) {
        digits = 3;
    } else if (val >= 10) {
        digits = 2;
    } else {
        digits = 1;
    }

    for (i = 0; i < length - digits; i++) {
        dst[i] = 0xFFFD;
    }

    dst[length] = 0xFFE;
    dst[length + 1] = 0xFFFF;

    for (i = 0; i < digits; i++) {
        dst[2 - i] = (val % 10) + 0x60; // 0x60 offset for bolded font
        val /= 10;
    }

    return digits * 0x10;
}

s32 textFmtIntAt(s16* dst, s32 val, s32 length, s32 dstOffset) {
    s32 digits;
    s32 fill;
    s32 i;

    if (val >= 100) {
        digits = 3;
    } else if (val >= 10) {
        digits = 2;
    } else {
        digits = 1;
    }

    dst += dstOffset;
    for (i = 0; i < length - digits; i++) {
        dst[i] = 0xFFFD;
    }

    dst += length - digits;
    for (i = 0; i < digits; i++) {
        dst[digits - 1 - i] = (val % 10) + 0x60; // 0x60 offset for bolded font
        val /= 10;
    }

    return digits * 0x10;
}
