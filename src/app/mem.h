#ifndef APP_MEM_H
#define APP_MEM_H

#include <PR/ultratypes.h>

void mem_init(void);
void* mem_get(s32 size);
s32 mem_remaining(void);

#endif // APP_MEM_H
