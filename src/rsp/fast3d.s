#include "asm.h"

.section .text, "ax"

LEAF(gspFast3DTextStart)
.incbin "rsp/fast3d.textbin.bin"
END(gspFast3DTextStart)
EXPORT(gspFast3DTextEnd)

.section .rodata, "a"

SYM_START(gspFast3DDataStart)
.incbin "rsp/fast3d.databin.bin"
SYM_END(gspFast3DDataStart)
EXPORT(gspFast3DDataEnd)
