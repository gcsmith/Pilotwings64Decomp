#ifndef PILOTWINGS64_UV_TERRAIN_H
#define PILOTWINGS64_UV_TERRAIN_H

#include <uv_common.h>

void uvTerra_8022EE90(UnkStruct_80204D94* arg0, ParsedUVTR* arg1, f32 arg2);
void uvTerra_8022EFB4(UnkStruct_80204D94* arg0, ParsedUVTR* arg1, f32 arg2);
void _uvTerraDraw(UnkStruct_80204D94* arg0, u8 arg1);
void uvComputeLineEndP(s16*, s16*, u16*, f32, f32, f32, f32, f32, f32, f32, u8, f32, f32);
s32  uvTerra_8022F62C(s32, s16, s16, u8);

#endif // PILOTWINGS64_UV_TERRAIN_H

