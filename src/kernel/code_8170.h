#ifndef CODE_8170_H
#define CODE_8170_H

#include <uv_graphics.h>
#include <uv_sobj.h>

#define HIT_COUNT 32

s32 func_80212480(f32, f32, Vtx*, u16, u16, u16, f32);
s32 func_80212FF4(ParsedUVTR*, f32, f32, f32, f32*, f32*, f32*, u16*, u16*, u8);
s32 _uvSurfGetNorm(Vtx*, s32, s32, s32, Vec3F*);
void func_80214840(s16, f32*, f32*);
u8 func_80213364(f32, f32, f32, f32, f32, f32, f32);
s32 func_802134F8(f32, f32, f32, UnkSobjDraw*);
s32 func_80213790(f32, f32, f32, Unk80263780*);
s32 func_802139C8(f32, f32, f32, f32, f32, f32, Unk80263780*);
u8 func_80214C64(f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32*);
void func_80215BC4(f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, Vec3F*);
s32 func_80215CBC(f32, f32, f32, UnkUVMD_24_Unk4*);
s32 _uvSegInMboxs(f32, f32, f32, f32, f32, f32, Mtx4F*, UnkUVMD_24*, u8, ParsedUVMD*);
u16 func_80214B3C(f32, f32, uvUnkTileStruct*, f32, f32);
void func_80215D7C(Mtx4F*, s16, Vec3F*);
u8 func_802153D8(f32, f32, f32, f32, f32, f32, UnkUVMD_24_Unk4*, f32*, f32*, s16*, s16*);
u16 func_80214900(f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, uvUnkTileStruct*);
s32 func_802140BC(f32, f32, f32, f32, f32, f32, f32, f32);
void func_802141CC(f32*, f32*, f32*, f32*, f32, f32, f32, f32);
s32 func_80213C24(f32, f32, f32, f32, f32, f32, UnkSobjDraw*);
s32 func_802129B0(f32, f32, f32, f32, f32, f32, Vtx*, u16, u16, u16, f32, f32*);
void func_80214450(f32*, f32*, f32*, f32*, f32*, f32*, f32, f32, f32, f32);

#endif // CODE_8170_H
