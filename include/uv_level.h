#ifndef UV_LEVEL_H
#define UV_LEVEL_H

#include <PR/ultratypes.h>


typedef struct {
    s32 unk0[4];
} LevelTOYS;

typedef struct {
    u8 unk0;
    u8 countWOBJ;
    u8 countLPAD;
    u8 countTOYS;
    u8 countTPTS;
    u8 countAPTS;
    u8 countBNUS;
    u8 pad7;
    void* dataWOBJ;
    void* dataLPAD;
    void* dataTPTS;
    LevelTOYS* dataTOYS;
    void* dataAPTS;
    void* dataBNUS;
} LevelObjects;

void func_8030B6C0(u8 arg0, u8 arg1, u8 arg2, s32 arg3);
void func_8030B868(void);
void func_8030B964(void);
void func_8030BA60(void);
void func_8030BA98(u8 arg0, u8 arg1);
void func_8030BD20(void);
u8 levelGetWOBJ(void** data);
u8 levelGetTPTS(void** data);
u8 levelGetAPTS(void** data);
u8 levelGetLPAD(void** data);
u8 levelGetBNUS(void** data);
LevelObjects* func_8030BDC8(u8 arg0);

#endif // UV_LEVEL_H
