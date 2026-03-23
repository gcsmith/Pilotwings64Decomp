#ifndef UV_SEQ_H
#define UV_SEQ_H

#include <PR/ultratypes.h>

#define FX_SEQ_1(x) 1, (x)
#define FX_SEQ_2(x) 2, (x)
#define FX_SEQ_3(x) 3, (x)
#define FX_SEQ_4(x) 4, (x)
#define FX_SEQ_5(x) 5, (x)
#define FX_SEQ_END 0

void func_80218BA0(void);
void func_80218CA4(void);
void uvSeqModel(s32, s32);
void uvSeqProps(s32, ...);
s32 func_80218F88(void);
s32 func_80219240(s32);

#endif // UV_SEQ_H
