#include "common.h"
#include <uv_memory.h>
#include <uv_util.h>
#include "mem.h"

// .bss
STATIC_DATA u8 sLevelObjHeap[5000];

// .data
STATIC_DATA u8* sLevelObjHeapPtr = sLevelObjHeap;

void* mem_get(s32 size) {
    u8* ret;

    ret = sLevelObjHeapPtr;
    if (size == 0) {
        return NULL;
    }
    // align to 8 bytes
    size = (size + 7) & ~7;
    sLevelObjHeapPtr += size;
    if ((u32)(sLevelObjHeapPtr - &sLevelObjHeap[0]) < sizeof(sLevelObjHeap)) {
        return ret;
    } else {
        _uvDebugPrintf("mem_get: out of bss in mem.c, trying to get %d bytes\n", size);
        return NULL;
    }
}

void mem_init(void) {
    sLevelObjHeapPtr = &sLevelObjHeap[0];
    uvMemSet(&sLevelObjHeap[0], 0, sizeof(sLevelObjHeap));
}

s32 mem_remaining(void) {
    return sLevelObjHeapPtr - &sLevelObjHeap[0];
}
