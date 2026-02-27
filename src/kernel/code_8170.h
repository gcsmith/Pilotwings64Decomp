#ifndef CODE_8170_H
#define CODE_8170_H

#include <uv_graphics.h>
#include <uv_sobj.h>

#define HIT_COUNT 32

ParsedUVTR* uvTerraGetBox(s32 terraId);
void uvTerraGetColor(s32 terraId, u32 surfaceId, u8* arg2, u8* arg3, u8* arg4);
void uvTerraGetPlane(s32 terraId, u32 surfaceId, f32 px, f32 py, f32* arg4, Vec3F* arg5);
u32 uvTerraGetPt(s32 terraId, f32 arg1, f32 arg2, s32** arg3);
s32 uvTerraGetSeg(s32 terraId, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, s32** arg7, f32** arg8);
s32 uvTerraGetState(s32 terraId, u32 surfaceId);

s32 func_80212480(f32, f32, Vtx*, u16, u16, u16, f32);
s32 func_80212FF4(ParsedUVTR*, f32, f32, f32, f32*, f32*, f32*, u16*, u16*, u8);
s32 _uvSurfGetNorm(Vtx*, s32, s32, s32, Vec3F*);
void func_80214840(s16, f32*, f32*);
void func_80215E7C(ParsedUVMD*);
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
