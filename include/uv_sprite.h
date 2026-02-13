#ifndef PILOTWINGS64_UV_SPRITE
#define PILOTWINGS64_UV_SPRITE

#include <PR/sp.h>
#include <uv_util.h>
#include <uv_graphics.h>

typedef struct unk_UVTX_1C {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    u8 unk18;
} unk_UVTX_1C; // size = 0x1C

typedef struct unk_UVTX_8 {
    u8 unk0;
    s32 unk4;
} unk_UVTX_8; // size = 0x8

typedef struct ParsedUVTX {
    void* unk0;
    unk_UVTX_8* unk4;
    u16 size;
    u16 unkA;
    u16 unkC;
    u8 unkE;
    u8 unkF;
    u8 unk10;
    u16 unk12;
    u16 unk14;
    unk_UVTX_1C* unk18;
    unk_UVTX_1C* unk1C;
    u16 unk20;
    u8 unk22;
    u8 unk23;
    u8 unk24;
    u8 unk25;
    u8 unk26;
    s32 unk28;
} ParsedUVTX; // size = 0x2C

typedef struct {
/* 00 */ u8 unk0;
/* 01 */ u8 unk1;
/* 02 */ s16 width;
/* 04 */ s16 height;
/* 06 */ s16 unk6;
/* 08 */ s16 unk8;
/* 0A */ u16 textureId;
/* 0C */ u8 red;
/* 0D */ u8 green;
/* 0E */ u8 blue;
/* 0F */ u8 alpha;
/* 10 */ Bitmap* bitmap;
/* 14 */ Sprite sprite;
/* 58 */ Gfx* unk58[2];
} uvSprite_t; // size 0x60

void uvSprt_80230130(void);
void uvSprt_802301A4(void);
void _uvTxtDraw(s32 arg0);
void uvSprtFromBitmap(uvSprite_t* arg0, uvGfxUnkStruct2* arg1);
void uvSprt_80230750(uvSprite_t* arg0, uvGfxUnkStruct2* arg1);
s32  uvSprt_80230898(void);
void uvSprtInit(void);
void uvSprtDisplayList(uvSprite_t* arg0);
void uvSprtDrawAll(void);
void uvSprtDraw(s32 sprite_id);
void uvSprtSetBlit(uvSprite_t* sprite, s32 arg1);
s16  uvSprtGetWidth(s32 sprite_id);
s16  uvSprtGetHeight(s32 sprite_id);
void uvSprtProps(s32 sprite_id, ...);
void uvSprtUpdateUnk(ParsedUVTX* arg0);
void uvSprtResetUnk(void);

#endif // PILOTWINGS64_UV_SPRITE

