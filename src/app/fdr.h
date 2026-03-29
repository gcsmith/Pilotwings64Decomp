#ifndef APP_FDR_H
#define APP_FDR_H

#include <uv_matrix.h>

void fdrInit(void);
void fdr_802E68B0(u8);
u8 fdr_802E6B5C(void);
void fdr_802E65AC(Mtx4F*, u16*, f32*, f32*, s32*);
void fdr_802E66DC(void);
void fdrSetblen(f32);
void fdr_802E682C(f32*, u8 count, u8);
void fdr_802E6870(f32*, u8 count, u8*);
f32 fdr_802E6B68(void);
s32 fdr_802E7278(Mtx4F*, u16*);

#endif // APP_FDR_H
