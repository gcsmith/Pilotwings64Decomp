#ifndef APP_CODE_51E30_H
#define APP_CODE_51E30_H

#include <PR/ultratypes.h>
#include <uv_dobj.h>

typedef struct {
    u32 unk0_0 : 1;
    u32 animationIndex : 31;
    f32 *unk4;
    f32 *unk8;
} Unk802CAC48;

typedef struct Unk8034E788 {
    u32 unk0_0 : 1;
    u32 animationIndex : 31;
    f32 *unk4;
    void *unk8;
    void *unkC;        
} Unk8034E788;

void app_firstfunc(s32);
void func_802CAA00(u32, s32);
void func_802CAAC8(Unk8034E788*, Unk80371120*);
void func_802CAA90(s32 arg0);
void func_802CAAC8(Unk8034E788 *arg0, Unk80371120* arg1);

#endif // APP_CODE_51E30_H
