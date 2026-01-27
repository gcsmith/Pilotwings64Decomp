#include "common.h"
#include "uv_memory.h"
#include "uv_util.h"

extern u8* gLevelObjHeapPtr;
extern u8 gLevelObjHeap[5000];

void* mem_get(s32 size) {
    u8* ret;

    ret = gLevelObjHeapPtr;
    if (size == 0) {
        return NULL;
    }
    // align to 8 bytes
    size = (size + 7) & ~7;
    gLevelObjHeapPtr += size;
    if ((u32)(gLevelObjHeapPtr - &gLevelObjHeap[0]) < sizeof(gLevelObjHeap)) {
        return ret;
    } else {
        _uvDebugPrintf("mem_get: out of bss in mem.c, trying to get %d bytes\n", size);
        return NULL;
    }
}

void mem_init(void) {
    gLevelObjHeapPtr = &gLevelObjHeap[0];
    uvMemSet(&gLevelObjHeap[0], 0, sizeof(gLevelObjHeap));
}

s32 mem_remaining(void) {
    return gLevelObjHeapPtr - &gLevelObjHeap[0];
}
