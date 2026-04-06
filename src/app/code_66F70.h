#ifndef APP_CODE_66F70_H
#define APP_CODE_66F70_H

#include <uv_matrix.h>
#include <uv_vector.h>

void db_getstart(Mtx4F*, Vec3F*, u8*, f32*);
s32 func_802DFB48(s32, f32, f32, f32, s32*, f32*, Vec3F*);
u8 db_getgnd(Vec3F*, Vec3F*, s32*, s32*, f32*, Vec3F*);
Vec3F* func_802E02EC(void);
u32 func_802E02F8(void);
void func_802E05CC(Mtx4F*, Vec3F*, Vec3F*, u16);
u8 func_802E06AC(Mtx4F*);
u8 func_802E07D8(Mtx4F*);
s32 func_802E08F4(f32, f32, f32);
u8 func_802E0C30(u8, s32);
void func_802E0484(Mtx4F*, Mtx4F*, f32);
f32 func_802DFA40(f32, f32);

#endif // APP_CODE_66F70_H
