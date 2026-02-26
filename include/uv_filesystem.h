#ifndef UV_FILESYSTEM_H
#define UV_FILESYSTEM_H

#include <PR/ultratypes.h>
#include <uv_vector.h>

typedef struct UnkPartStruct_Unk8 {
    Vec4F unk0;
    s16 unk10;
    u16 pad12_0 : 4;
    u16 unk12_4 : 1;
    u16 unk12_5 : 3;
    u16 pad12_8 : 8;
} UnkPartStruct_Unk8; // size = 0x14

typedef struct UnkPartStruct {
    s32 count;
    s32 unk4;
    UnkPartStruct_Unk8 unk8[1];
} UnkPartStruct;

typedef struct UnkQuatStruct_Unk8 {
    Vec4F unk0;
    s32 unk10;
    u8 pad14[0x4];
} UnkQuatStruct_Unk8; // size = 0x18
typedef struct UnkQuatStruct {
    s32 count;
    s32 unk4;
    UnkQuatStruct_Unk8 unk8[1];
} UnkQuatStruct;

typedef struct UnkTranslatStruct_Unk8 {
    Vec3F unk0;
    s32 unkC;
} UnkTranslatStruct_Unk8; // size = 0x10
typedef struct UnkTranslatStruct {
    s32 count;
    s32 unk4;
    UnkTranslatStruct_Unk8 unk8[1];
} UnkTranslatStruct;

typedef struct UnkCommStruct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s16 unk14;
} UnkCommStruct;

s32 uvFileReadHeader(s32 addr);
void uvFile_80223F30(s32 idx);
u32 uvFileGetCurLength(s32 idx);
u32 uvFileGetCurTag(s32 idx);
u32 uvFileReadBlock(s32 idx, u32* sizeOut, void** arg2, s32 arg3);
u32 uvFile_80224170(s32 idx, void* arg1, void** arg2, u32 tag, s32 palette, s32 arg5);
void uvFile_8022427C(s32 idx);

#endif // UV_FILESYSTEM_H
