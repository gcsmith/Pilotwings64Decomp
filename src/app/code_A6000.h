#ifndef APP_CODE_A6000_H
#define APP_CODE_A6000_H

#include <PR/ultratypes.h>
#include <uv_filesystem.h>
#include <uv_graphics.h>
#include <uv_vector.h>

typedef struct {
    Vec4F unk0;
    u8 pad10[0x190-0x10];
    Vec3F unk190;
    u8 pad[0x2DC-0x19C];
} Unk8037DCA0_Unk4C; // size = 0x2DC

typedef struct {
    s32 unk0;
    s16 unk4;
    u16 pad6;
    s32 unk8;
    Unk8037DCA0_UnkC *unkC;
    s32 unk10;
    s16 unk14;
    u16 pad16;
    s32 unk18;
    UnkTranslatStruct_Unk8* unk1C;
    u16 unk20;
    s8 unk22;
    s8 unk23;
    u8 unk24;
    u8 pad25[0x38-0x25];
    s32 unk38;
    s32 modelId;
    s8 unk40;
    u8 pad41[0x44-0x41];
    f32 unk44;
    f32 unk48;
    Unk8037DCA0_Unk4C unk4C;
    u8 pad328[0x350-0x328];
    u8 allocated;
    u8 pad351;
    u16 unk352;
} Unk8037DCA0; // size = 0x354

typedef struct {
    Vec4F unk0[25];
    Vec3F unk190[25];
    u8 unk2BC[25];
    u8 pad2D5[3];
    s32 unk2D8;
    u8 pad2DC[0xC];
} Unk8037F098; // size = 0x2E8

void uvPathPoseLine(Unk8037F098*, Unk8037DCA0*, f32);
void func_8031EF60(Unk8037DCA0*, s32);
void func_8031EF68(Unk8037DCA0*);
void func_8031EE48(s32, Unk8037F098*, f32, f32, f32);

#endif // APP_CODE_A6000_H
