#ifndef APP_CODE_66160_H
#define APP_CODE_66160_H

#include <uv_matrix.h>
#include <uv_vector.h>

void func_802DEC30(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 arg10, s32 arg11, s32 arg12, s32 arg13);
void func_802DEE44(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 arg10);
void screenDrawBox(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7);
void screenDrawBox2(s32, s32, s32, s32, s32, s32, s32, s32);
void screenDrawBoxSetup(void);
void db_getstart(Mtx4F*, Vec3F*, u8*, f32*);
void func_802DFA18(void);
u8 db_getgnd(Vec3F*, Vec3F*, s32*, s32*, f32*, Vec3F*);
Vec3F* func_802E02EC(void);
void func_802E05CC(Mtx4F*, Vec3F*, Vec3F*, s32);
s32 func_802E06AC(Mtx4F*);
void func_802E07D8(Mtx4F*);
u8 func_802E0C30(u8, s32);
void func_802E0484(Mtx4F*, Mtx4F*, f32);

#endif // APP_CODE_66160_H
