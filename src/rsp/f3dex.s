#include "asm.h"

.section .text, "ax"

LEAF(gspF3DEX_fifoTextStart)
.incbin "rsp/f3dex.textbin.bin"
END(gspF3DEX_fifoTextStart)
EXPORT(gspF3DEX_fifoTextEnd)

.section .rodata, "a"

SYM_START(gspF3DEX_fifoDataStart)
.incbin "rsp/f3dex.databin.bin"
SYM_END(gspF3DEX_fifoDataStart)
EXPORT(gspF3DEX_fifoDataEnd)
