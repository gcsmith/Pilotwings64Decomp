#include "common.h"

#include <uv_filesystem.h>
#include <uv_graphics.h>
#include <uv_memory.h>

void* uvUserFileRead(s32 userFileIdx, MemType request) {
    UNUSED s32 pad;
    void* sp38;
    void* sp34;
    s32 sp30;
    s32 sp2C;
    UNUSED s32 pad2;

    sp38 = gUVBlockOffsets.userFiles[userFileIdx];
    uvGfxWaitForMesg();
    if (userFileIdx >= ARRAY_COUNT(gUVBlockOffsets.userFiles)) {
        _uvDebugPrintf("Too many user files\n");
        return NULL;
    }
    sp30 = uvFileReadHeader((s32)sp38);
    sp2C = uvFileGetCurLength(sp30);
    if (uvFileGetCurTag(sp30) == 'UVRW') {                 // 0x55565257
        uvFile_80224170(sp30, &sp2C, &sp38, 'COMM', 0, 0); // 0x434F4D4DU
    }
    uvFile_80223F30(sp30);
    if (request == MEM_ROM_OFFSET) {
        return sp38;
    }
    if (request == MEM_ALLOCATE) {
        sp34 = (void*)_uvMemAlloc(sp2C, 8);
    } else {
        sp34 = (void*)0x803DA800;
    }
    _uvMediaCopy(sp34, sp38, sp2C);
    return sp34;
}
