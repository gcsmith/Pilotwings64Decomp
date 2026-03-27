#ifndef UV_SEQ_H
#define UV_SEQ_H

#include <PR/ultratypes.h>

#define SEQ_PROPS_1(x) 1, (x)
#define SEQ_PROPS_2(x) 2, (x)
#define SEQ_PROPS_3(x) 3, (x)
#define SEQ_PROPS_4(x) 4, (x)
#define SEQ_PROPS_5(x) 5, (x)
#define SEQ_PROPS_END 0

void func_80218BA0(void);
void func_80218CA4(void);
void uvSeqModel(s32, s32);
void uvSeqProps(s32, ...);
s32 func_80218F88(void);
s32 func_80219240(s32);

#endif // UV_SEQ_H
